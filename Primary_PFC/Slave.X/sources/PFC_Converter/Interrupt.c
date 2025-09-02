/*
 * File:   Interrupt.c
 * Author: User
 *
 * Created on 2022?5?5?, ?? 4:55
 */

#include "xc.h"
#include "defines.h"
#include "pfc_Variables.h"
#include "pfcControl.h"
#include "pfcSystem.h"
#include "pin_manager.h"
#include "currentLoop.h"

/****************************************************************
 *
 *	ADC AN0 Interrupt, for AN0
 *
 ****************************************************************/
void __attribute__((__interrupt__, auto_psv)) _ADCAN0Interrupt(void) {
    
    /* Sampling CT1 Current */
    pfcCurrent = ADCBUF0 << SHIFT_Q15;
    
    #if((DACOUT == ENABLED) && (DACFUNCT == MEASCURR))
        DAC1DATH = ADCBUF0;
    #endif
    
    vacFiltered = (vacAvg << SHIFT_Q15);
    
    // vacFiltered is set after calling one of the above functions 
    #if ((DACOUT == ENABLED) && (DACFUNCT == VINSENSEFILT))
        DAC1DATH = vacFiltered >> 3;
    #endif

    if (pwr_ctrl_state == PCS_NORMAL || pwr_ctrl_state == PCS_SOFT_START) {
        /* reset the PWM duty */
        if (pfcBulkVoltageFiltered > PFCVOUTRESETADC) {
            pfcStateFlags.PfcVoutReset = ENABLED;
            CloopPID.controlOutput = 0;
            C2loopPID.controlOutput = 0;           
        }

        if(pwr_ctrl_state == PCS_SOFT_START)
        {
            SoftStart();
        }
        
        Current_Compensator();
        
#if 1
        if (pfcVacState == STATE_VAC_ZERO) {
            Voltage_Compensator();    
        }
#else
        /* 10KHz */
        if(v_cnt >= 9)
        {
            v_cnt = 0;
            Voltage_Compensator();    
        }
        else
        {
            v_cnt++;
        }
#endif        
    } else {
        PG1DC = 0;
        PG1TRIGA = 0;
        PG1STATbits.UPDREQ = 1;
    }

    RMSCurrent_Calculation();

    // These functions rely on AC filtered data so called after reading system voltages
    if (pwr_ctrl_state == PCS_SOFT_START || pwr_ctrl_state == PCS_NORMAL) {
        Current_Reference_Calculation(); /* Current reference calculation */
        pfcStateFlags.ZeroCrossDetect = DISABLED; /* Routines below do not need ZC information */
    }

    ++isrCnt;
    if ((isrCnt & 3) == DISABLED) {
        VRMS_Calculation();
        pfcStateFlags.NewRMSPower = DISABLED; /* Clear flags now that all functions in this ISR had a chance to act on it */
    }

    /*******************************************************************************
    Functionality: Output Over Voltage Fault
    Description: When output voltage > 44V, system will enter in Fault mode
     *******************************************************************************/
    if (pfcBulkVoltageFiltered > PFCVOUTMAXADC) {
        if (++outputOverVoltageFaultCounter >= 1000) {
            pfcFaultFlags.OutputOverVoltage = ENABLED;
        }
    } else {
        outputOverVoltageFaultCounter = DISABLED;
    }
    
    //clear the channel_AN0 interrupt flag
    IFS5bits.ADCAN0IF = 0;
}

///****************************************************************
// *
// *	ADC AN1 Interrupt, for AN1
// *
// ****************************************************************/
//void __attribute__((__interrupt__, auto_psv)) _ADCAN1Interrupt(void) {
//    //LED1_SetHigh();
//    /* Sampling CT2 Current */
//    pfcCurrent2 = ADCBUF1 << SHIFT_Q15;
//
//    #if((DACOUT == ENABLED) && (DACFUNCT == MEASCT2))
//        DAC1DATH = ADCBUF1;
//    #endif
//
//    if (pwr_ctrl_state == PCS_NORMAL || pwr_ctrl_state == PCS_SOFT_START) {
//        /* reset the PWM duty */
//        if (pfcBulkVoltageFiltered > PFCVOUTRESETADC) {
//            pfcStateFlags.PfcVoutReset = ENABLED;
//            C2loopPID.controlOutput = 0;           
//        }
//        
//        Current_Compensator_Two();
//        
//    } else {
//        PG2DC = 0;
//        PG2TRIGA = 0;
//        PG2STATbits.UPDREQ = 1;
//    }
//    
//    IFS5bits.ADCAN1IF = 0;
//    //LED1_SetLow();
//}

/****************************************************************
 *
 *	ADCAN11 Interrupt, for AN2, AN5, AN6, AN8 and AN11
 *
 ****************************************************************/
void __attribute__((__interrupt__, auto_psv)) _ADCAN7Interrupt(void) {

    /* Sampling AC Input Voltage */
    
    vacLine = ADCBUF1;
    vacNeutral = ADCBUF4;
    
    if(vacLine > vacNeutral)
    {
        vac_raw = vacLine;
    }
    else
    {
        vac_raw = vacNeutral;
    }
    
	vacSum = vacSum + vac_raw - vacAvg;
	vacAvg = vacSum >> 2;
    
    vacFiltered = vacAvg << SHIFT_Q15;
    
    /* Sampling PFC Bulk Voltage */
    pfcBulkVoltage = ADCBUF5;
    
    #if ((DACOUT == ENABLED) && (DACFUNCT == BULKVOLTADC))
        DAC1DATH = pfcBulkVoltage;
    #endif

    pfcBulkVoltageSum = pfcBulkVoltageSum + pfcBulkVoltage - pfcBulkVoltageFiltered;
    pfcBulkVoltageFiltered = pfcBulkVoltageSum >> 2;

    outputBulkVoltage = pfcBulkVoltageFiltered << SHIFT_Q15;

    /* Sampling Temperature */
    temp_pri = ADCBUF6;
    
    /* Sampling Aux 13V */
    aux_13v = ADCBUF7;

    temp_pri_sum = temp_pri_sum + temp_pri - temp_pri_filter;
    temp_pri_filter = temp_pri_sum >> 2;

    //clear the channel_S1AN7 interrupt flag
    IFS6bits.ADCAN7IF = 0;
}
