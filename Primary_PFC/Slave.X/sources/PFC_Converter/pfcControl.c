/*******************************************************************************
Microchip's products.  Microchip and its licensors retain all ownership and
intellectual property rights in the accompanying software and in all
derivatives here to.

This software and any accompanying information is for suggestion only. It
does not modify Microchip's standard warranty for its products. You agree
that you are solely responsible for testing the software and determining its
suitability. Microchip has no obligation to modify, test, certify, or
support the software.

THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
PURPOSE APPLY TO THIS SOFTWARE, ITS INTERACTION WITH MICROCHIP?S PRODUCTS,
COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

IN NO EVENT, WILL MICROCHIP BE LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT
(INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), STRICT LIABILITY,
INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE,
EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF
ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWSOEVER CAUSED, EVEN IF
MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.
TO THE FULLEST EXTENT ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF
FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF
THESE TERMS.
*******************************************************************************/

#include "pfcControl.h"
#include "defines.h"
#include "stdbool.h"
#include "pin_manager.h"

volatile PFC_FAULTS pfcFaultFlags;
volatile PFC_FLAGS  pfcStateFlags;

extern volatile uint16_t __attribute__((near)) criticalISRDone;

static uint8_t vacScalerDCM = 0;

/******************************************************************************* 
Function: Current_Reference_Calculation
Description: This function calculates the Current reference based on Voltage compensator output
 * Current Reference = VoltagePIOuptut *CurrScaler
 * FeedForward Correction is constant at light loads and increases linearly and then constant towards the half load and Full load
 * FeedForward Correction and The current reference offset is varied to get Good THD and PF at all loading conditions 
 * 
****************************************************************************** */
void inline __attribute__((optimize(1))) Current_Reference_Calculation(void)
{
    #if ((DACOUT == ENABLED) && (DACFUNCT == VOLTCOMPOUT))
        DAC1DATH = pfcVoltCompOutput >> 3;  // Scale down the voltage compensation output by dividing by 8
    #endif

    pfcCurrentRef = __builtin_divud(__builtin_muluu(vacFiltered, pfcVoltCompOutput), denCurrRefCalc_Avg); // Current reference calculation

    // Limit the current reference to a maximum allowed value
    if (pfcCurrentRef > (uint16_t)(CURRENT_REFERENCE_MAX << 3))
    {
        pfcCurrentRef = (uint16_t)(CURRENT_REFERENCE_MAX << 3); // Clamp the current reference to max allowed value
    }
    
    #if ((DACOUT == ENABLED) && (DACFUNCT == REFCURR))
        DAC1DATH = pfcCurrentRef >> 3;
    #endif
}
/*******************************************************************************
Function: VRMS Calculation
Description:  Vac Peak voltage is detected first and VRMS is calculated there after 
*******************************************************************************/

void inline __attribute__((optimize(1))) VRMS_Calculation(void)
{                    
    /* Find the Peak input voltage to calculate the RMS voltage */
    if((vacFiltered > vacFilteredMax) && (peakDetectFlag == ENABLED))           
    {
        vacFilteredMax = vacFiltered;       
    }
    
    if(vacFiltered > prevVacFiltered)
    {
        downCounter = 0;
        if((++upCounter >= VRMS_COUNT_LIMIT ) && (peakDetectFlag == DISABLED))  
        {
            peakDetectFlag = ENABLED; 
        }
    }
    else {
        upCounter = 0;
        if((++downCounter >= VRMS_COUNT_LIMIT) && (peakDetectFlag == ENABLED))
        {
            peakDetectFlag      = DISABLED ;                                  /* Disable Peak detect flag On the down cycle  */ 
            vacPeak             = vacFilteredMax;
            
            denCurrRefCalc      = (__builtin_mulss(vacPeak,vacPeak) >> 15) ;  /* Den = Vpk*Vpk = (1.15*1.15/1.15) = 1.15 */
            denCurrRefCalc_Sum = denCurrRefCalc_Sum + denCurrRefCalc - denCurrRefCalc_Avg;
            denCurrRefCalc_Avg = denCurrRefCalc_Sum >> 4;
            
            #if((DACOUT == ENABLED) && (DACFUNCT == VPEAKSQUARE))
                DAC1DATH = denCurrRefCalc >> 3;
            #endif            
            
            vacRMS              = (__builtin_mulss(vacPeak,VPK2VRMS) >> 18);  /* VRMS calculation Vpeak(Q1.15) *0.7071 (Q1.15) shifted by 15+3 12-bit*/    
            vacFilteredMax      = 0;         

            vacScalerDCM = (vacRMS < INPUTVOLTAGEHIGHLINEADC) ? DISABLED : ENABLED;     /* Set DCM correction scaler based on Vac */
            
            #if ((DACOUT == ENABLED) && (DACFUNCT == VACRMS))    
                DAC1DATH = vacRMS;
            #endif 
            
            pfcStateFlags.PeakDetect = ENABLED;                                  
            pfcStateFlags.NewInputRMS = ENABLED;
        }
    }
    
    prevVacFiltered = vacFiltered;                                              /* storing the Vac filtered value */    
}
/*******************************************************************************
Function: Voltage_Compensator
Description: The compensator runs per Vac zero cross region
*******************************************************************************/
void inline __attribute__((optimize(1))) Voltage_Compensator(void)
{    
    VloopPID.controlReference = pfcVoltageRef;  // << 3;              /*Set the Reference Input for your controller */
    VloopPID.measuredOutput = pfcBulkVoltageFiltered;   // << 3;       /*Typically the measuredOutput variable is a plant response*/

    PID(&VloopPID);

    if(VloopPID.controlOutput >= MAXLIMITQ15)
    {
        VloopPID.controlOutput = MAXLIMITQ15;
    }
    if(VloopPID.controlOutput <= 0)
    {
        VloopPID.controlOutput = 0;
    }
    pfcVoltCompOutput = VloopPID.controlOutput;

#if (VOLTAGE_LOOP_ONLY == ENABLED)
    
    volatile uint16_t dutyOut = 0;
    dutyOut = __builtin_muluu(PG1PER, pfcVoltCompOutput) >> 15;
    /* Duty output Limit */
    if(dutyOut > PWM_DUTY_MAX)
        dutyOut = PWM_DUTY_MAX;

    if(pfcStateFlags.PfcVoutReset == ENABLED)
    {
        pfcStateFlags.PfcVoutReset = DISABLED;
        dutyOut = 0;
    }
	
    #if (FEATURE_SINGLE_PHASE_PWM1 == ENABLED)
        PG1TRIGA = dutyOut >> 1;
        PG1DC = dutyOut;
    #else
        PG1TRIGA = 0;
        PG1DC = 0;
    #endif

    #if (FEATURE_SINGLE_PHASE_PWM2 == ENABLED)
        PG2TRIGA = dutyOut >> 1;
        PG2DC = dutyOut;
    #else
        PG2TRIGA = 0;
        PG2DC = 0;
    #endif
#endif
    
}
/*******************************************************************************
Function: Average Current Calculation
Description: used to calculate the RMS power 
*******************************************************************************/
void inline __attribute__((optimize(1))) RMSCurrent_Calculation(void)
{
    int16_t avgPFCCurrent;
    
    pfcCurrentsum += pfcCurrent;                      /* Add PFC current to PFC current sum */
    
    if(++avgCurrCounter >= 512)
    {
        avgPFCCurrent = (int)(pfcCurrentsum >> 9);
        avgCurrCounter = 0;
        pfcCurrentsum = 0; 
        
        /* Moving average filter for pfcCurrent (averaged over ~1AC cycle and then filtered (avg) over ~8 AC cycles) */
        avgCurrentSum += (avgPFCCurrent - avgCurrentSample[iacArrayIndex]);          
        avgCurrentSample[iacArrayIndex++] = avgPFCCurrent;
        avgPFCCurrent = (avgCurrentSum >> 3);     /* Find average over the ~8 cycles */                         
        
        rmsPFCCurrent = (__builtin_mulss(AVGTORMS, avgPFCCurrent) >> 17) ;    /* RMS Current (Q4.12) = 1.11(Q2.14) * Avg Current (Q1.15) */
        rmsPower = (__builtin_mulss(vacRMS, rmsPFCCurrent) >> 9);            /* Prms = Vrms *Irms = result stays is 4.12 format */
        
        pfcStateFlags.NewRMSPower = ENABLED;
        
        #if ((DACOUT == ENABLED) && (DACFUNCT == RMSCURRENT))     
        DAC1DATH = rmsPFCCurrent;
        #endif 

        #if ((DACOUT == ENABLED) && (DACFUNCT == CALCRMSPOWER))     
        DAC1DATH = rmsPower;
        #endif 
        
        if(iacArrayIndex > 7) iacArrayIndex = 0;
    }    
}

/****************************************************************
*
*
*
****************************************************************/
void inline __attribute__((optimize(1))) ZeroCrossCheck(uint16_t Vac) 
{ 
    static uint8_t VacState = STATE_VAC_NORMAL;         // Initialize voltage state to normal
    static bool IsZero = false;                         // Flag to indicate if zero crossing has been detected
    static uint16_t VacCnt = 0;                         // Counter for voltage cycles
    
    /* Regular operations */
    VacCnt++;                                           // Increment the voltage counter
    
    switch (VacState)
    {   
        case STATE_VAC_ZERO:
            // Transition from zero state to normal state
            VacState = STATE_VAC_NORMAL;           
            IsZero = true;                              // Set zero crossing flag
            pfcStateFlags.ZeroCrossDetect = ENABLED;    // Update zero-cross detection flag
            
            /* Reset counter */
            VacCnt = 0;                                 // Reset the voltage counter
        break;

        case STATE_VAC_NORMAL:
            /* Detect Zero Crossing */                        
            if (Vac <= INPUTVOLTAGE_ZERO_ADC)           // If voltage is below zero threshold
            {
                if(!IsZero)
                {
                    VacState = STATE_VAC_ZERO;          // Change state to zero crossing
                }
            }
            else
            {                   
                if(VacCnt > VAC_44HZ_CNT)               // If counter exceeds 44Hz threshold
                {
                    VacState = STATE_VAC_ZERO;          // Force state change to zero crossing
                }
            }
            
            if(VacCnt >= VAC_CROSS_CNT)
            {
                IsZero = false;                         // Reset zero crossing flag after max count
            }
        break;
            
        default:
            // Do nothing...
        break;

    }

    pfcVacState = VacState;                        // Update the voltage state variable
    
}
/****************************************************************
*
*
*
****************************************************************/
void inline __attribute__((optimize(1))) VacRectify(uint16_t vLine, uint16_t vNeutral) 
{
	int16_t iVac = 0;
	static uint16_t u16LineCnt = 0;
	static uint16_t u16NeutralCnt = 0;
    
	if(vLine > vNeutral)
	{
		u16NeutralCnt = 0;
        pfcStateFlags.IsNeutral = false;
		iVac = (vLine - vNeutral);
		if(iVac > INPUTVOLTAGE_ZERO_ADC)
		{
            if(u16LineCnt > ZERO_CROSS_BLANK_COUNT)
            {
                if(pfcStateFlags.IsLine == false)
                {
                    pfcStateFlags.IsLine = true;
                }
            }
            else
            {
                u16LineCnt++;
            }			
		}
		else
		{
			u16LineCnt = 0;
			pfcStateFlags.IsLine = false;
		}
	}
	else
	{
		u16LineCnt = 0;
		pfcStateFlags.IsLine = false;
		
		iVac = (vNeutral - vLine);
		if(iVac > INPUTVOLTAGE_ZERO_ADC)
		{
            if(u16NeutralCnt > ZERO_CROSS_BLANK_COUNT)
            {
                if(pfcStateFlags.IsNeutral == false)
                {
                    pfcStateFlags.IsNeutral = true;
                }
            }
            else
            {
                u16NeutralCnt++;
            }	
		}
		else
		{
			u16NeutralCnt = 0;
			pfcStateFlags.IsNeutral = false;
		}	
	}
}
/****************************************************************
*
*
*
****************************************************************/
void inline __attribute__((optimize(1))) SRControl(void)
{   
    /*	SR Slow Switch Control */
    if(pwr_ctrl_state == PCS_NORMAL || pwr_ctrl_state == PCS_SOFT_START)
    {
        if(pfcStateFlags.IsLine == true && pfcStateFlags.IsNeutral == false)
        {
            // Line State
            PG1IOCONLbits.SWAP = 1;
            PG1IOCONLbits.OVRENL = 0;
        }
        else if(pfcStateFlags.IsLine == false && pfcStateFlags.IsNeutral == true)
        {
            // Neutral Sate
            PG1IOCONLbits.SWAP = 0;
            PG1IOCONLbits.OVRENH = 0;		
        }
        else
        {
            PG1IOCONLbits.OVRENL = 1;
            PG1IOCONLbits.OVRENH = 1;
        }
    }
}