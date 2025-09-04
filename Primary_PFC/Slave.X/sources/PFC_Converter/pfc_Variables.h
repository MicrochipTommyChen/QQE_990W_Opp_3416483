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
#ifndef _PFC_VARIABLES_H_
#define	_PFC_VARIABLES_H_

#include "xc.h"
#include <stdint.h>

/*******************************************************************************
Global variables
*******************************************************************************/

 /* Current Variables */

extern int16_t     pfcCurrentRef             ;
extern uint16_t    pfcCurrent                ;
extern uint16_t    pfcCurrentScaled          ;
extern int16_t     currentControlOutput      ;
extern uint16_t    pfcCurrent2               ;
extern uint16_t    pfcCurrent2Scaled         ;
extern uint16_t    current2ControlOutput     ;
extern uint16_t    denCurrRefCalc            ;
extern uint16_t    pfcShuntCurrent           ;
extern uint32_t    denCurrRefCalc_Sum        ;
extern uint16_t    denCurrRefCalc_Avg        ;

/* Output Voltage Variables*/
extern uint16_t    pfcBulkVoltageFiltered    ;
extern uint16_t    outputBulkVoltage         ;
extern int16_t     pfcVoltageRef             ;

/* Compensator Output Variables*/
extern int16_t     prevpfcVoltCompOutput     ;
extern int16_t     pfcVoltCompOutput         ;
extern uint16_t    pfcPostShift              ;
extern int16_t     pfcCurrCompOutput         ;
extern int16_t     pfcCurr2CompOutput        ;

 /* DCM Correction factor ,Duty feed forward Variables and Current Offset */
extern int16_t     dcmCorrFactor             ;
extern int16_t     dcr_Drop                  ;
extern int16_t     dutyFeedForward           ;

/* Line Voltage Current /Power Variables    */
extern int16_t     vacPeak                   ;
extern int16_t     peakPFCCurrent            ;
extern int16_t     rmsPFCCurrent             ;
extern int16_t     rmsPower                  ;
extern int16_t     avgCurrCounter            ;
extern int32_t     pfcCurrentsum             ;
extern uint16_t    vac_raw                   ;
extern uint16_t    vacLine                   ;
extern uint16_t    vacNeutral                ;
extern uint16_t    vacRMS                    ;
extern uint16_t    vacFiltered               ;
extern uint16_t    vacSum                    ;
extern uint16_t    vacAvg                    ;

extern volatile int16_t upCounter            ;
extern volatile int16_t downCounter          ;

extern volatile uint16_t vacLineSum          ;
extern volatile uint16_t vacNeutralSum       ;
extern volatile int32_t  avgCurrentSum       ;
extern volatile uint16_t vacFilteredMax      ;
extern volatile uint16_t prevVacFiltered     ;
extern volatile uint16_t pfcBulkVoltage      ;
extern volatile uint16_t pfcBulkVoltageSum   ;
extern volatile uint16_t vacLineSample[4]    ;
extern volatile uint16_t vacNeutralSample[4] ;
extern volatile int16_t  avgCurrentSample[8] ;
extern volatile uint16_t peakDetectFlag      ;
extern  uint16_t isrCnt                      ;
extern volatile uint16_t vacArrayIndex       ;
extern volatile uint16_t iacArrayIndex       ;

/* Soft Start Variables */
extern int16_t     sftStrtScaler                 ;
extern uint16_t    sftStartTimer                 ; 
extern volatile uint16_t sftStrtInitVoltage      ;
extern volatile uint16_t sftStrtVoltageDelta     ;

/* Fault/LED counters*/
extern int16_t faultLEDToggleCounter             ;
extern int16_t faultState                        ;
extern int16_t faultLEDState                     ;
extern uint16_t timerInterruptCounter            ;
extern int16_t scaledFreqValue                   ;
extern int16_t drvSupplyFaultCounter             ;
extern int16_t inputUnderVoltageFaultCounter     ;
extern int16_t inputOverVoltageFaultCounter      ;
extern int16_t outputUnderVoltageFaultCounter    ;
extern int16_t outputOverVoltageFaultCounter     ;
extern int16_t overCurrentFaultCounter           ;
extern int16_t mainsFrequencyFaultCounter       ;


/* Parallel MOSFET on/off variables */
extern int16_t parellelFEToffCount              ;

/* Temperature sense variables */
extern uint16_t temp_amb                   ;
extern uint16_t temp_amb_sum               ;
extern uint16_t temp_amb_filter            ;
extern uint16_t temp_pri                   ;
extern uint16_t temp_pri_sum               ;
extern uint16_t temp_pri_filter            ;

/* 13V Aux voltage sense variables */
extern uint16_t aux_13v                    ;
extern uint16_t aux_13v_sum                ;
extern uint16_t aux_13v_filter             ;

/* Mains Frequency check variables */
extern uint16_t freqCount                       ;
extern volatile uint16_t halfCycleCounts        ;

extern int16_t transietModeDisablecount         ;

typedef enum
{
  PCS_INIT                  = 1, // Init peripherals that are involved
  PCS_STANDBY               = 2, // standy
  PCS_RELAYON_WAIT          = 3, // Relay_On & wait state        
  PCS_SOFT_START            = 4, // Soft-Start 
  PCS_NORMAL                = 5, // Pfc voltage inregulation
  PCS_OFF                   = 6  // shutting down the controller/reference voltage
} PWR_CTRL_STATE_e;

extern PWR_CTRL_STATE_e pwr_ctrl_state;

typedef enum
{
	STATE_VAC_ZERO = 0,
	STATE_VAC_CROSS,
	STATE_VAC_NORMAL,
	STATE_VAC_INIT,
	STATE_VAC_NONE
	
}STATE_VAC;

/* Vin Vac state report variables */
extern uint16_t pfcVacState;

#endif	//_PFC_VARIABLES_H_