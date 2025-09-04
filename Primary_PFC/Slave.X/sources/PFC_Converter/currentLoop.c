
#include "currentLoop.h"

void inline __attribute__((optimize(1))) Current_Compensator(void)
{
    volatile uint16_t dutyOut1 = 0;  // Initialize duty cycle output variable
    
//    // Check if High Line is active
//    if(pfcStateFlags.HighLineActive == ENABLED)
//    {
//        // Scale the PFC current using DCM correction factor
//        pfcCurrentScaled = __builtin_mulss(pfcCurrent, dcmCorrFactor) >> 15;
//    }
//    else
//    {
//        // Use unscaled PFC current
//        pfcCurrentScaled = pfcCurrent;
//    }
    
    /* PID compensator */
    CloopPID.controlReference = pfcCurrentRef;    // Set the reference input for the controller
    CloopPID.measuredOutput = pfcCurrent;         // Set the measured output (plant response)
    
    PID(&CloopPID);   // Execute PID control
    
    // Limit control output to maximum value
    if(CloopPID.controlOutput >= MAXLIMITQ15)
    {
        CloopPID.controlOutput = MAXLIMITQ15;
    }
    
#if(FEATURE_DUTY_RATIO_FEED_FORWARD == ENABLED)
    // Limit control output to minimum value
    if(CloopPID.controlOutput <= -32767)
    {
        CloopPID.controlOutput = -32767;
    }
#else
    // Limit control output to minimum value
    if(CloopPID.controlOutput <= 0)
    {
        CloopPID.controlOutput = 0;
    }    
#endif
    
    // Update control output variables
    pfcCurrCompOutput = CloopPID.controlOutput;
    currentControlOutput = pfcCurrCompOutput;

#if(FEATURE_DUTY_RATIO_FEED_FORWARD == ENABLED)
    
    currentControlOutput = __builtin_mulus(PG1PER, currentControlOutput) >> 15;
    
	int16_t deltaV = 0; 
	int32_t temp = 0;
	int16_t duty_ratio_ff_temp = 0;
	
	deltaV = (int16_t)outputBulkVoltage - (int16_t)vacFiltered;
    
	if(deltaV > 0)
	{
		temp = __builtin_mulsu(deltaV, PG1PER);
		duty_ratio_ff_temp = __builtin_divsd(temp, outputBulkVoltage);
	}
	  
	currentControlOutput = currentControlOutput + duty_ratio_ff_temp;
    
    if(currentControlOutput > (int16_t)PG1PER)
        currentControlOutput = (int16_t)PG1PER;
    
    if(currentControlOutput < 0)
        currentControlOutput = 0;
    
    dutyOut1 = (uint16_t)currentControlOutput;
    
    if(dutyOut1 < 0)
        dutyOut1 = 0;
    
#else
    // Calculate duty cycle output
    dutyOut1 = __builtin_mulus(PG1PER, currentControlOutput) >> 15;
#endif
    
//    // Calculate duty cycle output
//    dutyOut1 = __builtin_muluu(PG1PER, currentControlOutput) >> 15;
    
    /* Duty output limit */
    if(dutyOut1 >= PWM_DUTY_MAX)
       dutyOut1 = PWM_DUTY_MAX;
    
    #if (VOLTAGE_LOOP_ONLY != ENABLED)
    // Reset duty output when Vout reset flag is set
    if(pfcStateFlags.PfcVoutReset == ENABLED)
    {
        pfcStateFlags.PfcVoutReset = DISABLED;
        dutyOut1 = 0;
    }
    #endif

    #if (VOLTAGE_LOOP_ONLY != ENABLED)
        // Set PWM trigger and duty cycle for PWM1 phase operation           
        PG1DC = dutyOut1;
        PG1TRIGA = dutyOut1 >> 1;
        PG2DC = PG1DC;
        PG2TRIGA = PG1TRIGA;      
    #endif
}

void inline __attribute__((optimize(1))) Current_Compensator_Two(void)
{
    volatile uint16_t dutyOut2 = 0;  // Initialize duty cycle output variable
    
    // Check if High Line is active
    if(pfcStateFlags.HighLineActive == ENABLED)
    {
        // Scale the PFC current using DCM correction factor
        pfcCurrent2Scaled = __builtin_mulss(pfcCurrent2, dcmCorrFactor) >> 15;
    }
    else
    {
        // Use unscaled PFC current
        pfcCurrent2Scaled = pfcCurrent2;
    }
    
    /* PID compensator */
    C2loopPID.controlReference = pfcCurrentRef;  // Set the reference input for the controller
    C2loopPID.measuredOutput = pfcCurrent2;      // Set the measured output (plant response)
    
    PID(&C2loopPID);  // Execute PID control
	
    // Limit control output to maximum value
    if(C2loopPID.controlOutput >= MAXLIMITQ15)
    {
        C2loopPID.controlOutput = MAXLIMITQ15;
    }
	
    // Limit control output to minimum value
    if(C2loopPID.controlOutput <= 0)
    {
        C2loopPID.controlOutput = 0;
    }    
    
    // Update control output variables
    pfcCurr2CompOutput = C2loopPID.controlOutput;
    current2ControlOutput = pfcCurr2CompOutput;
	
    // Calculate duty cycle output
    dutyOut2 = __builtin_muluu(PG2PER, current2ControlOutput) >> 15;
    
    /* Duty output limit */
    if(dutyOut2 >- PWM_DUTY_MAX)
        dutyOut2 = PWM_DUTY_MAX;
    
    #if (VOLTAGE_LOOP_ONLY != ENABLED)
    // Reset duty output when Vout reset flag is set
    if(pfcStateFlags.PfcVoutReset == ENABLED)
    {
        pfcStateFlags.PfcVoutReset = DISABLED;
//        dutyOut2 = 0;
    }
    #endif

    #if (VOLTAGE_LOOP_ONLY != ENABLED)
        #if (FEATURE_SINGLE_PHASE_PWM2 == ENABLED)
            // Set PWM trigger and duty cycle for single-phase operation
            PG2TRIGA = dutyOut2 >> 1;
            PG2DC = dutyOut2;
        #else
            // Disable PWM outputs
            PG2TRIGA = 0;
            PG2DC = 0;
        #endif
    #endif
}
