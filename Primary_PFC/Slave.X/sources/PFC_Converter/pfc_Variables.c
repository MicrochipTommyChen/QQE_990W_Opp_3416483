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

#include <stdint.h>

/*******************************************************************************
Global variables
*******************************************************************************/

/* Current Variables */
uint16_t    pfcCurrent              =   0 ;
uint16_t    pfcCurrentScaled        =   0 ;
int16_t     currentControlOutput    =   0 ;
uint16_t    pfcCurrent2             =   0 ;
uint16_t    pfcCurrent2Scaled       =   0 ;
uint16_t    current2ControlOutput   =   0 ;
int16_t      pfcCurrentRef          =   0 ;
uint16_t    denCurrRefCalc          =   0 ;
uint16_t    pfcShuntCurrent         =   0 ;
uint32_t    denCurrRefCalc_Sum      =   0 ;
uint16_t    denCurrRefCalc_Avg      =   0 ;

/* Output Voltage Variables*/
uint16_t    pfcBulkVoltageFiltered  =   0 ;
uint16_t    outputBulkVoltage       =   0 ;
int16_t     pfcVoltageRef           =   0 ;

/* Compensator Output Variables*/
int16_t     prevpfcVoltCompOutput   =   0 ;
int16_t     pfcVoltCompOutput       =   0 ;
uint16_t    pfcPostShift            =   0 ;
int16_t     pfcCurrCompOutput       =   0 ;
int16_t     pfcCurr2CompOutput      =   0 ;

 /* DCM Correction factor ,Duty feed forward Variables and Current Offset */
int16_t     dcmCorrFactor           = 32767;
int16_t     dcr_Drop                =   0 ;
int16_t     dutyFeedForward        =   0 ;

/* Line Voltage Current /Power Variables    */
int16_t     vacPeak                 =   0 ;
int16_t     peakPFCCurrent          =   0 ;
int16_t     rmsPFCCurrent           =   0 ;
int16_t     rmsPower                =   0 ;
int16_t     avgCurrCounter          =   0 ;
int32_t     pfcCurrentsum           =   0 ;
volatile int16_t upCounter          =   0 ;
volatile int16_t downCounter        =   0 ;
uint16_t    vac_raw                 =   0 ;
uint16_t    vacLine                 =   0 ;
uint16_t    vacNeutral              =   0 ;
uint16_t    vacRMS                  =   0 ;
uint16_t    vacFiltered             =   0 ;
uint16_t    vacSum                  =   0 ;
uint16_t    vacAvg                  =   0 ;

volatile uint16_t vacLineSum        =   0 ;
volatile uint16_t vacNeutralSum     =   0 ;
volatile int32_t avgCurrentSum      =   0 ;
volatile uint16_t vacFilteredMax    =   0 ;
volatile uint16_t prevVacFiltered   =   0 ;
volatile uint16_t pfcBulkVoltage    =   0 ;
volatile uint16_t pfcBulkVoltageSum       =   0 ;
volatile uint16_t vacLineSample[4]  =   {0,0,0,0} ;
volatile uint16_t vacNeutralSample[4] = {0,0,0,0} ;
volatile int16_t  avgCurrentSample[8] = {0,0,0,0,0,0,0,0};
volatile uint16_t peakDetectFlag    =   0 ;
uint16_t isrCnt            =   0 ;
volatile uint16_t vacArrayIndex     =   0;
volatile uint16_t iacArrayIndex     =   0;

/* Soft Start Variables */
int16_t     sftStrtScaler               = 0 ;
uint16_t    sftStartTimer               = 0 ; 
volatile uint16_t sftStrtInitVoltage    = 0 ;
volatile uint16_t sftStrtVoltageDelta   = 0 ;

/* Fault/LED counters*/
int16_t faultLEDToggleCounter           = 0 ;
int16_t faultLEDState                   = 0 ;
uint16_t timerInterruptCounter          = 0 ;
int16_t faultState                      = 0 ;
int16_t scaledFreqValue                 = 0 ;
int16_t drvSupplyFaultCounter           = 0 ;
int16_t inputUnderVoltageFaultCounter   = 0 ;
int16_t inputOverVoltageFaultCounter    = 0 ;
int16_t outputUnderVoltageFaultCounter  = 0 ;
int16_t outputOverVoltageFaultCounter   = 0 ;
int16_t overCurrentFaultCounter         = 0 ;
int16_t mainsFrequencyFaultCounter      = 0 ;


/* Parallel MOSFET on/off variables */
int16_t parellelFEToffCount         = 0 ;


/* Mains Frequency check variables */
uint16_t freqCount                     = 0 ;
volatile uint16_t halfCycleCounts      = 0 ;

int16_t transietModeDisablecount    = 0 ;

/* Temperature sense variables */
uint16_t temp_amb                   = 0;
uint16_t temp_amb_sum               = 0;
uint16_t temp_amb_filter            = 0;
uint16_t temp_pri                   = 0;
uint16_t temp_pri_sum               = 0;
uint16_t temp_pri_filter            = 0;

/* 13V Aux voltage sense variables */
uint16_t aux_13v                    = 0;
uint16_t aux_13v_sum                = 0;
uint16_t aux_13v_filter             = 0;

/* Vin Vac state report variables */
uint16_t pfcVacState                 = 0;