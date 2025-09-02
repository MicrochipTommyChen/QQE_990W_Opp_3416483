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
#ifndef __PFCCONTROL_H__
#define __PFCCONTROL_H__

#include "init_Compensators.h"
#include "pfc_Variables.h"

#define MAXLIMITQ15                                 32767       
#define MAXLIMITQ14                                 16383
#define MAXLIMITQ13                                 8191

#define VPK2VRMS                                    23170       /* 2^15 * .7071 (1/sqrt(2)) in Q15 format) */
#define AVGTORMS                                    18198       /* 1.11 in 2.14 format to calculate RMS value from AVG value */

typedef union{

    struct {
        uint16_t MainsVoltage           : 1;
        uint16_t MainsFreq              : 1;
        uint16_t DrvSupply              : 1;
        uint16_t MainsUnderVoltage      : 1;
        uint16_t MainsOverVoltage       : 1;
        uint16_t OutputUnderVoltage     : 1;
        uint16_t OutputOverVoltage      : 1;
        uint16_t OverCurrent            : 1;
        uint16_t DCDCFaultMode          : 1;
        uint16_t Communication          : 1;
        uint16_t ShutDownDCDC           : 1;
        uint16_t LowLineOverPower       : 1;
        uint16_t HW_OutputOverVoltage   : 1;
        uint16_t : 3;
    };
    
    uint16_t SystemFaults;

} PFC_FAULTS;

typedef union {

   struct {
        uint16_t SoftStartActive        : 1;
        uint16_t StartUp                : 1;
        uint16_t RegulationMode         : 1;
        uint16_t NewInputRMS            : 1;
        uint16_t SyncZeroCross          : 1;
        uint16_t LineActive             : 1;
        uint16_t RelayOn                : 1;
        uint16_t BulkVoltageManagement  : 1;
        uint16_t NewRMSPower            : 1;
        uint16_t TransientMode          : 1;
        uint16_t ZeroCrossDetect        : 1;
        uint16_t PfcVoutReset           : 1;
        uint16_t PeakDetect             : 1;            /* Flag is set once AC peak is found, cleared at ZC, used for adaptive freq @ ZC*/
        uint16_t FrequencyADJ           : 1;
        uint16_t DisableDCMCorr         : 1;
        uint16_t HighLineActive         : 1;
        
        uint16_t IsLine                 : 1;
        uint16_t IsNeutral              : 1;
        uint16_t Reserved               : 14;
    };
    uint32_t SystemState;
    

} PFC_FLAGS;

extern volatile PFC_FAULTS pfcFaultFlags;                                   /* Flags for Fault conditions  */
extern volatile PFC_FLAGS pfcStateFlags;                                   /* Flags for System conditions */

extern void SMPS_Controller2P2ZUpdate_HW_Accel(void);               /* Voltage Loop Compensator */

void inline __attribute__((optimize(1))) RMSCurrent_Calculation(void);
void Current_Reference_Calculation(void);
void VRMS_Calculation(void) ;
void inline __attribute__((optimize(1))) Voltage_Compensator(void);
void inline __attribute__((optimize(1))) ZeroCrossCheck(uint16_t Vac);
void inline __attribute__((optimize(1))) VacRectify(uint16_t vLine, uint16_t vNeutral);
void inline __attribute__((optimize(1))) SRControl(void);

#endif