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

#include "xc.h"
#include "pfcSystem.h"
#include "defines.h"
#include "pfc_Variables.h"
#include "pin_manager.h"
#include <stdbool.h>
#include "init_Compensators.h"

uint16_t inputVoltageGoodCnt = 0;
PWR_CTRL_STATE_e pwr_ctrl_state = 1;

/*******************************************************************************
Function: 		SoftStart
Description:	Converter SoftStart (SystemState-1)
*******************************************************************************/
void inline __attribute__((optimize(1))) SoftStart(void) 
{
    if(sftStrtInitVoltage == 0)
    {
        sftStartTimer = 0;
        // Set initial voltage for the soft start
        sftStrtInitVoltage = pfcBulkVoltageFiltered;
        // Calculate the voltage increment for each soft start step
        sftStrtVoltageDelta = __builtin_divsd(((int16_t)PFCVOLTAGEREFADC - (int16_t)pfcBulkVoltageFiltered), SOFT_START_TIMES);
        // Set the initial voltage reference for the soft start
        pfcVoltageRef = pfcBulkVoltageFiltered + sftStrtVoltageDelta;
                
        if(sftStrtVoltageDelta <= 0)
        {
            // Ensure the voltage increment is not negative
            sftStrtVoltageDelta = 0;
        }  
    }
    
    // Increment the soft start timer
    sftStartTimer++;
    
    if(sftStartTimer >= SOFT_START_COUNT)
    {
        // Reset the soft start timer
        sftStartTimer = 0;
        if(pfcVoltageRef <= PFCVOLTAGEREFADC)
        {
            // Increment the voltage reference by the voltage delta
            pfcVoltageRef = pfcVoltageRef + sftStrtVoltageDelta;
        }
    }
    // If the voltage reference has reached or exceeded the target voltage
    // or if the filtered bulk voltage is greater than or equal to the target voltage
    if((pfcVoltageRef >= PFCVOLTAGEREFADC) || (pfcBulkVoltageFiltered >= PFCVOLTAGEREFADC))
    //if(pfcVoltageRef >= PFCVOLTAGEREFADC)
    {         
        pfcVoltageRef = PFCVOLTAGEREFADC;           // Set the voltage reference to the target voltage
        pfcStateFlags.SoftStartActive = DISABLED;   // Disable the soft start flag                             
        pfcStateFlags.RegulationMode = ENABLED;     // Enable the regulation mode
    }
}

/*******************************************************************************
Function: 		Check Vac Input
Description:	Check Brown in / out
*******************************************************************************/
bool inline __attribute__((optimize(1))) CheckVacInputOK(void)
{
    static uint16_t good_cnt = 0;   // Counter for consecutive good voltage readings
    static uint16_t bad_cnt = 0;    // Counter for consecutive bad voltage readings
    static bool bInputOk = false;   // Flag indicating if the input voltage is OK
    
    if(vacRMS > INPUT_BROWNIN_ADC)
    {
        bad_cnt = 0;                // Reset bad voltage counter since voltage is above brown-in threshold
        if(good_cnt > BROWNIN_DELAY_CNT)
        {
            bInputOk = true;        // Input voltage is considered OK after sufficient good readings
        }
        else
        {
            good_cnt++;             // Increment good voltage counter
        }
    }
    else if(vacRMS < INPUT_BROWNOUT_ADC)
    {
        good_cnt = 0;               // Reset good voltage counter since voltage is below brown-out threshold
        if(bad_cnt > BROWNOUT_DELAY_CNT)
        {
            bInputOk = false;       // Input voltage is considered not OK after sufficient bad readings
        }
        else
        {
            bad_cnt++;              // Increment bad voltage counter
        }
    }
    else
    {
        good_cnt = 0;               // Reset counters if voltage is between thresholds
        bad_cnt = 0;
    }
    
    return bInputOk;                // Return the status of the input voltage
}
/*******************************************************************************
Function: 		Check PFC Bulk Voltage
Description:	Check PFC Bulk voltage to output the PFC_OK signal
*******************************************************************************/
void inline __attribute__((optimize(1))) CheckPFCVoltage(void)
{
    static uint16_t ok_cnt = 0;        // Counter for consecutive readings above the OK threshold
    static uint16_t notok_cnt = 0;     // Counter for consecutive readings below the NOT OK threshold
    
    if(pfcBulkVoltageFiltered > PFC_OK_POINT_ADC)
    {
        notok_cnt = 0;                 // Reset the not OK counter since voltage is above OK threshold
        if(pwr_ctrl_state == PCS_NORMAL)
        {
            if(ok_cnt > PFC_OK_DELAY_CNT)
            {
                //PFC_PGD_SetHigh();    // Set PFC Power Good signal high
            }
            else
            {
                ok_cnt++;              // Increment the OK counter
            }
        }
    }
    else if(pfcBulkVoltageFiltered < PFC_NOTOK_POINT_ADC)
    {
        ok_cnt = 0;                    // Reset the OK counter since voltage is below NOT OK threshold
        if(notok_cnt > PFC_NOTOK_DELAY_CNT)
        {
            //PFC_PGD_SetLow();        // Set PFC Power Good signal low
        }
        else
        {
            notok_cnt++;               // Increment the not OK counter
        }
    }
    else
    {
        notok_cnt = 0;                 // Reset both counters if voltage is between thresholds
        ok_cnt = 0;
    }    
}
/*******************************************************************************
Function: 		Relay Control
Description:	Output voltage > 108V (NCP turn-on Voltage) 
                and Output Bulk voltage is equal to peak of the sine wave 
*******************************************************************************/
void inline __attribute__((optimize(1))) RelayControl(void)
{
    static uint16_t on_delay_cnt = 0;   // Counter for relay ON delay
    static uint16_t off_delay_cnt = 0;  // Counter for relay OFF delay
    
    if(CheckVacInputOK() == true)
    {
        off_delay_cnt = 0;  // Reset OFF delay counter when input voltage is OK
        
        if(on_delay_cnt > RELAY_ON_DELAY_CNT)
        {
            Relay_SetHigh();                   // Turn the relay ON
            pfcStateFlags.RelayOn = ENABLED;   // Update relay state flag to enabled
        }
        else
        {
            on_delay_cnt++;  // Increment ON delay counter
        }
    }
    else
    {
        on_delay_cnt = 0;  // Reset ON delay counter when input voltage is not OK
        
        if(off_delay_cnt > RELAY_OFF_DELAY_CNT)
        {
            Relay_SetLow();                    // Turn the relay OFF
            pfcStateFlags.RelayOn = DISABLED;  // Update relay state flag to disabled
        }
        else
        {
            off_delay_cnt++;  // Increment OFF delay counter
        }
    }
}
/*******************************************************************************
Function: 		PFC State Machine
Description:	Converter State Machine (SystemState-1)
*******************************************************************************/
void inline __attribute__((optimize(1))) PwrCtrl_PFC_Task_100us(void)
{
    static uint16_t relay_on_wait_cnt = 0;  // Counter for relay-on wait time
    static bool VinOK = false;              // Flag indicating if input voltage is OK

    VinOK = CheckVacInputOK();  // Check if the input voltage is within acceptable range

    switch (pwr_ctrl_state)
    {
        case PCS_INIT:

            initPFCComp();                // Initialize PFC compensator components
            pwr_ctrl_state = PCS_STANDBY; // Transition to standby state

            break;

        case PCS_STANDBY:

            if(pfcFaultFlags.SystemFaults == 0)  // If there are no system faults
            {
                if(VinOK == true)                // If input voltage is OK
                {
                    pwr_ctrl_state = PCS_RELAYON_WAIT;  // Transition to relay-on wait state
                }
            }
            else
            {
                pwr_ctrl_state = PCS_OFF;  // Transition to off state due to system faults
            }

            sftStrtInitVoltage = DISABLED;            // Disable soft start initial voltage
            PG1DC = 0;                                // Turn off PWM channel 1
            PG2DC = 0;                                // Turn off PWM channel 2
            pfcStateFlags.RegulationMode = DISABLED;  // Disable regulation mode

            PFCCompReset();   // Reset PFC compensator

            relay_on_wait_cnt = 0;  // Reset relay-on wait counter
            break;

        case PCS_RELAYON_WAIT:

            if(pfcStateFlags.RelayOn == ENABLED)  // If the relay is turned on
            {
                if(relay_on_wait_cnt > RELAY_ON_WAIT_CNT)  // If wait time has passed
                {
                    if (pfcVacState == STATE_VAC_ZERO)  // If zero-crossing is detected
                    {
                        pwr_ctrl_state = PCS_SOFT_START;  // Transition to soft start state
                    }
                }
                else
                {
                    relay_on_wait_cnt++;  // Increment relay-on wait counter
                }
            }

            break;

        case PCS_SOFT_START:

            if(pfcFaultFlags.SystemFaults == 0)  // If there are no system faults
            {
                if(VinOK == true)                // If input voltage is OK
                {
                    if(pfcStateFlags.RegulationMode == ENABLED)  // If regulation mode is enabled
                    {
                        pwr_ctrl_state = PCS_NORMAL;  // Transition to normal operation state
                    }
                }
                else
                {
                    pwr_ctrl_state = PCS_STANDBY;  // Transition back to standby state
                }
            }
            else
            {
                pwr_ctrl_state = PCS_OFF;  // Transition to off state due to system faults
            }

            break;

        case PCS_NORMAL:

            if(pfcFaultFlags.SystemFaults == 0)  // If there are no system faults
            {
                if(VinOK == false)               // If input voltage is not OK
                {
                    pwr_ctrl_state = PCS_STANDBY;  // Transition back to standby state
                }
            }
            else
            {
                pwr_ctrl_state = PCS_OFF;  // Transition to off state due to system faults
            }

            break;

        case PCS_OFF:

            PG1DC = 0;                                // Turn off PWM channel 1
            PG2DC = 0;                                // Turn off PWM channel 2
            pfcStateFlags.RegulationMode = DISABLED;  // Disable regulation mode

            break;

        default:
            break;
    }
  
    ZeroCrossCheck(vacAvg);  // Perform zero-cross detection on the average AC voltage
    CheckPFCVoltage();       // Check the PFC voltage level
}
