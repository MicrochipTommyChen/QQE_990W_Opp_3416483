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
#include "../project_settings.h"

//#define ON   1
//#define OFF  0
                               
#define ENABLED    1
#define DISABLED   0

// Enable/Disable DACOUT feature which is displayed on header pin
#define DACOUT          ENABLED

#define DCMCORR         1
#define REFCURR         2
#define DUTYFF          3
#define RMSCURRENT      4
#define VINSENSEADC     5
#define VINSENSEFILT    6
#define DUTYCYCLE       7
#define VOLTCOMPOUT     8
#define CALCRMSPOWER    9       /* RMS Power that is calculated every ~1AC cycle */
#define MEASCURR        10      /* Raw ADC results */
#define CURRERROR       11      /* Delta between scaled and refernce current*/
#define BULKVOLTADC     12      /* Raw ADC results */
#define BULKVOLTFILT    13      /* Average of four samples */
#define MEASCURRSCALED  14      /* DCM Correction Factor Applied */
#define VACRMS          15
#define CURRCOMPOUT     16      /* Current compensator output scaled and shifted */
#define VPEAKSQUARE     17
#define MEASCT2         18      /* CT2 Raw ADC results */

#if (DACOUT == ENABLED)
#define DACFUNCT    MEASCURR
#else
#endif
                                        
#define F_ACLK                          (uint32_t)(500000000)

/* PWM Period Calculation */
#define PFCPERIOD                       (uint16_t)(F_ACLK / CONVSWITCHFREQ)
#define PFCPERIODLIMIT_ZC               (uint16_t)(F_ACLK / CONVSWITCHFREQLIMIT_ZC)

/* ADC/DAC Resolution Setting */
#define ADCRESOLUTION                   1241      /* 4096 (2^12)/3.3V */
#define DACRESOLUTION                   1241

/* Vrms to Vpeak */
#define SQRT2                           1.414213562
#define SQRT2GAIN                       ((WORD)SQRT2 << 10)
#define VRMS2VPEAK(Vrms)                (((DWORD)Vrms * SQRT2GAIN) >> 10)

/* Input Voltage/Output Voltage /Current Feedback Gains */
#define VACFBGAIN                       0.003533569     /* (Bulk Voltage Divider network) */
#define VBULKFBGAIN                     0.003533569     /* (Input Voltage Divider network) */
#define IINFBGAIN                       0.165

/* IIN Configuration */
#define INPUTVOLTAGE                    11          /* input Voltage threshold in volts for overcurrent protection */
#define INPUTVOLTAGEADC                 (int16_t)(INPUTVOLTAGE * VACFBGAIN * ADCRESOLUTION)
#define REF_IIN_MAX                     17.0
#define REF_IIN_MAX_ADC                 (int16_t)(REF_IIN_MAX * IINFBGAIN * ADCRESOLUTION)
#define CURRENT_REFERENCE_MAX           (uint16_t)REF_IIN_MAX_ADC
#define CBC_SET_POINT                   19
#define CBC_SET_POINT_ADC               (int16_t)(CBC_SET_POINT * IINFBGAIN * ADCRESOLUTION)

#define SHIFT_Q15                       3         /* left shift value to mak Q1.15 format */
#define MULSHIFT                        1         /* Shift used in multiplication (mul.ss) */

#define PWM_DUTY_MAX_PERCENT            96
#define PWM_DUTY_MIN_PERCENT            0

/*Duty Converter*/
#define DUTY2PERIOD(Period, Percent)    (((uint32_t)Period * Percent) / 100)
#define PERIOD2DUTY(Period)             (Period * 100UL / PWM_INIT_PTPER)

/* PWM Frequency Configuration */
#define PWM_FREQ                        66														
#define PWM_TRIG_TIME                   66UL
#define PWM_FREQ_HZ                     (PWM_FREQ * 1000UL)						
#define PWM_INIT_PTPER                  (uint16_t)(((F_ACLK / PWM_FREQ_HZ)))
#define PWM_DUTY_MAX                    (uint16_t)(DUTY2PERIOD(PWM_INIT_PTPER, PWM_DUTY_MAX_PERCENT))
#define PWM_DUTY_MIN                    (uint16_t)(DUTY2PERIOD(PWM_INIT_PTPER, PWM_DUTY_MIN_PERCENT))

/* Soft-Start Configuration */
#define SOFT_START_TIMES                500
#define SOFT_START_CNT_MAX              (uint32_t)(SOFT_START_TIMES * PWM_TRIG_TIME)
#define SOFT_START_COUNT                (uint16_t)(SOFT_START_CNT_MAX / SOFT_START_TIMES)

/* VRMS,OVERCURRENT parameters */
#define VRMS_COUNT_LIMIT                5           /* upcount and downcount limit while calculating the VRMS value */

/* VIN BROWN IN/OUT Configuration */
#define INPUTVOLTAGE                    11          /* input Voltage threshold in volts for overcurrent protection */
#define INPUTVOLTAGEADC                 (int16_t)(INPUTVOLTAGE * VACFBGAIN * ADCRESOLUTION)
#define INPUT_BROWNIN                   87
#define INPUT_BROWNIN_ADC               (int16_t)(INPUT_BROWNIN * VACFBGAIN * ADCRESOLUTION)
#define INPUT_BROWNOUT                  85
#define INPUT_BROWNOUT_ADC              (int16_t)(INPUT_BROWNOUT * VACFBGAIN * ADCRESOLUTION)

#define INPUTVOLTAGEHIGHLINE            150
#define INPUTVOLTAGEHIGHLINEADC         (int16_t)(INPUTVOLTAGEHIGHLINE * VACFBGAIN * ADCRESOLUTION)
#define INPUTVOLTAGEHIGHLINEHYSADC      (int16_t)((INPUTVOLTAGEHIGHLINE + 5) * VACFBGAIN * ADCRESOLUTION)

#define INPUTVOLTAGE_ZERO               10
#define INPUTVOLTAGE_ZERO_ADC           (int16_t)(INPUTVOLTAGE_ZERO * VACFBGAIN * ADCRESOLUTION)
#define ZERO_CROSS_BLANK_COUNT          2

#define BROWNIN_DELAY_CNT               6000                    /* 600ms */
#define BROWNOUT_DELAY_CNT              300                     /* 30ms */

/* Output Voltage reference settings */
#define BULKREDUCTIONLIMIT              2           /* Bulk voltage reduction during Variable DC link voltage     */  
#define PFCVOLTAGEREF                   400          /* PFC output voltage in volts */

#define PFCVOLTAGEREF_LIGHT_LOAD        (PFCVOLTAGEREF - BULKREDUCTIONLIMIT)     /* PFC output voltage in volts (when variable DC_Link is enabled) */

#define PFCVOLTAGEREFADC                (int16_t)(VBULKFBGAIN * ADCRESOLUTION * PFCVOLTAGEREF)

#define PFCVOLTAGEREFADC_LIGHT_LOAD     (int16_t)(VBULKFBGAIN * ADCRESOLUTION * PFCVOLTAGEREF_LIGHT_LOAD)

/* Mains frequency check parameters */  
#define FREQUENCYCOUNT_FILTER           200

#define PFC_TASK_TICK                   100         /* 100us */
#define VAC_CROSS_CNT                   (uint16_t)(5000 / PFC_TASK_TICK)
#define VAC_44HZ_CNT                    (uint16_t)((1000000UL / (44*2)) / PFC_TASK_TICK)

/* PFC Soft Start Parameters */
#define SOFTSTARTTIME                   160          /* value in ms */
#define SOFTSTARTCOUNT                  (uint16_t)((float)SOFTSTARTTIME / (float)0.1)            /* softstart time (ms) */
#define SOFTSTARTSCALER                 (uint16_t) ((32767 / SOFTSTARTCOUNT) << 10)

/*Input Voltage Limits */
#define INPUTUNDERVOLTAGE               85           /* Under Voltage threshold in volts */
#define INPUTUNDERVOLTAGEADC            (uint16_t)(INPUTUNDERVOLTAGE * VACFBGAIN * ADCRESOLUTION)

#define INPUTOVERVOLTAGE                280          /* Over Voltage threshold in volts */
#define INPUTOVERVOLTAGEADC             (uint16_t)(INPUTOVERVOLTAGE * VACFBGAIN * ADCRESOLUTION)

#define INPUTVOLTAGEHYST                3           /* Hysteresis in volts */
#define INPUTVOLTAGEHYSTADC             (uint16_t)(INPUTVOLTAGEHYST * VACFBGAIN * ADCRESOLUTION)

#define INPUTVOLTMINHYST                (INPUTUNDERVOLTAGEADC + INPUTVOLTAGEHYSTADC)
#define INPUTVOLTMAXHYST                (INPUTOVERVOLTAGEADC - INPUTVOLTAGEHYSTADC)

/* Output Voltage Limits */
#define VOUTMAXHYST                     50
#define VOUTRESETHYST                   30
#define VOUTMINHYST                     10
#define PFCVOUTMAX                      (PFCVOLTAGEREF + VOUTMAXHYST)                                 
#define PFCVOUTMAXADC                   (uint16_t)(VBULKFBGAIN * ADCRESOLUTION * PFCVOUTMAX)
#define PFCVOUTRESET                    (PFCVOLTAGEREF + VOUTRESETHYST)                                 
#define PFCVOUTRESETADC                 (uint16_t)(VBULKFBGAIN * ADCRESOLUTION * PFCVOUTRESET)
#define PFCVOUTMIN                      (PFCVOLTAGEREF - VOUTMINHYST)                                 
#define PFCVOUTMINADC                   (uint16_t)(VBULKFBGAIN*ADCRESOLUTION*PFCVOUTMIN)

#define PFC_OK_POINT                    365
#define PFC_OK_POINT_ADC                (uint16_t)(VBULKFBGAIN * ADCRESOLUTION * PFC_OK_POINT)
#define PFC_NOTOK_POINT                 320
#define PFC_NOTOK_POINT_ADC             (uint16_t)(VBULKFBGAIN * ADCRESOLUTION * PFC_NOTOK_POINT)
#define PFC_OK_DELAY_CNT                100                     /* 10 ms */
#define PFC_NOTOK_DELAY_CNT             2                       /* 200 us */

#define MUL_FACTOR                      8
#define VDIFF                           8                       /* Input voltage difference for the relay turn-on */
#define VDIFF_ADC                       (uint16_t)(VDIFF * VBULKFBGAIN * ADCRESOLUTION * MUL_FACTOR)
#define NCPTURNONVOLTAGE                10                      /* Relay Turn on voltage */
#define NCPTURNONVOLTAGE_ADC            (uint16_t)(VBULKFBGAIN * ADCRESOLUTION * NCPTURNONVOLTAGE)
#define RELAY_ON_DELAY_CNT              10                      /* 10ms */
#define RELAY_OFF_DELAY_CNT             20                      /* 20ms */

#define RELAY_ON_WAIT_CNT               2000                    /* 200ms */

/* PFC performance enhancement */
#define VOLTAGE_LOOP_ONLY               DISABLED //DISABLED
#define FEATURE_SINGLE_PHASE_PWM1       ENABLED   
#define FEATURE_SINGLE_PHASE_PWM2       ENABLED
#define FEATURE_DUTY_RATIO_FEED_FORWARD ENABLED    //ENABLED
