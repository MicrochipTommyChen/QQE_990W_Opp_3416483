/*
 * Implementation file for: Semi_Bridgeless_PFC_990W_converter_RT-BOX
 * Generated with         : PLECS 4.9.6
 *                          PLECS RT Box 3 3.1.4
 * Generated on           : 4 Sep 2025 14:25:21
 */
#include "Semi_Bridgeless_PFC_990W_converter_RT_BOX.h"
#ifndef PLECS_HEADER_Semi_Bridgeless_PFC_990W_converter_RT_BOX_h_
#error The wrong header file "Semi_Bridgeless_PFC_990W_converter_RT_BOX.h"
#error was included. Please check your include path to see whether this
#error file name conflicts with the name of another header file.
#endif /* PLECS_HEADER_Semi_Bridgeless_PFC_990W_converter_RT_BOX_h_ */
#if defined(__GNUC__) && (__GNUC__ > 4)
#   define _ALIGNMENT 16
#   define _RESTRICT __restrict
#   define _ALIGN __attribute__((aligned(_ALIGNMENT)))
#   if defined(__clang__)
#      if __has_builtin(__builtin_assume_aligned)
#         define _ASSUME_ALIGNED(a) __builtin_assume_aligned(a, _ALIGNMENT)
#      else
#         define _ASSUME_ALIGNED(a) a
#      endif
#   else
#      define _ASSUME_ALIGNED(a) __builtin_assume_aligned(a, _ALIGNMENT)
#   endif
#else
#   ifndef _RESTRICT
#      define _RESTRICT
#   endif
#   ifndef _ALIGN
#      define _ALIGN
#   endif
#   ifndef _ASSUME_ALIGNED
#      define _ASSUME_ALIGNED(a) a
#   endif
#endif
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "plexim/PhysicalModel.h"
#include "plexim/DigitalIn.h"
#include "plexim/Nanostep.h"
#include "plexim/AnalogOut.h"
#include "plexim/hw_wrapper.h"
#include "plexim/DigitalOut.h"
#include "plexim/AnalogIn.h"
#include "plexim/SFP.h"
#include "plexim/HIL_Framework.h"
#include "plexim/DigitalOverride.h"
#include "plexim/DataCapture.h"
#include "plexim/ProgrammableValue.h"
#include "plexim/ToFile.h"
#define PLECSRunTimeError(msg) \
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_errorStatus = msg
#define Semi_Bridgeless_PFC_990W_converter_RT_BOX_UNCONNECTED 0
static double Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double[2];
static uint32_t Semi_Bridgeless_PFC_990W_converter_RT_BOX_tickLo;
static int32_t Semi_Bridgeless_PFC_990W_converter_RT_BOX_tickHi;
/* Block outputs */
static double Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_Min_Max1; /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/Min/Max1 */
static double Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_Min_Max2; /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/Min/Max2 */
static double Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_Min_Max; /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/Min/Max */
static double Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_V_ac; /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/V_ac */
static bool Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn1; /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/Digital In1 */
static bool Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_AC_POWER_SW; /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/AC_POWER_SW */
static bool Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_LogicalOperator; /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/Logical Operator */
static bool Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn3; /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/Digital In3 */
static bool Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn4; /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/Digital In4 */
static bool Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_PWM1H; /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/PWM1H */
static double Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_x1_3NanostepSolver[4
];                                                                               /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/Boost1/Configurable Subsystem/Nanostep/1/3 Nanostep Solver */
static bool Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_PWM2H; /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/PWM2H */
static double Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_x1_3NanostepSolver_1
[4];                                                                               /* Semi_Bridgeless_PFC_990W_converter_RT-BOX/Boost2/Configurable Subsystem/Nanostep/1/3 Nanostep Solver */

/* Model states */
static double
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_X_Semi_Bridgeless_PFC_990W_conver_PM0_x
[2];                                                                                                /* Semi_Bridgeless_PFC_990W_converter_RT-BOX */

#if defined(EXTERNAL_MODE) && EXTERNAL_MODE
const double * const Semi_Bridgeless_PFC_990W_converter_RT_BOX_ExtModeSignals
[] = {

};
#endif /* defined(EXTERNAL_MODE) */
const char * Semi_Bridgeless_PFC_990W_converter_RT_BOX_errorStatus;
const double Semi_Bridgeless_PFC_990W_converter_RT_BOX_sampleTime =
   1.79999999999999992e-06;
const char * const Semi_Bridgeless_PFC_990W_converter_RT_BOX_checksum =
   "45eb056be86d525507189c3ed5a09165fa8bad84";
/* Target declarations */
struct PlxDataCaptureRegistry plxDataCaptureRegistry[1];
const int plxUseEthercat = 0;
struct PlxProgrammableValueRegistry plxProgrammableValueRegistry[1];
struct PlxToFileRegistry plxToFileRegistry[1];

void Semi_Bridgeless_PFC_990W_converter_RT_BOX_initialize(double time)
{
   double remainder;
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_errorStatus = NULL;
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_tickHi =
      floor(time/
            (4294967296.0*
             Semi_Bridgeless_PFC_990W_converter_RT_BOX_sampleTime));
   remainder = time - Semi_Bridgeless_PFC_990W_converter_RT_BOX_tickHi*
               4294967296.0*
               Semi_Bridgeless_PFC_990W_converter_RT_BOX_sampleTime;
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_tickLo = floor(
                                                            remainder/Semi_Bridgeless_PFC_990W_converter_RT_BOX_sampleTime +
                                                            .5);
   remainder -= Semi_Bridgeless_PFC_990W_converter_RT_BOX_tickLo*
                Semi_Bridgeless_PFC_990W_converter_RT_BOX_sampleTime;
   if (fabs(remainder) > 1e-6*fabs(time))
   {
      Semi_Bridgeless_PFC_990W_converter_RT_BOX_errorStatus =
         "Start time must be an integer multiple of the base sample time.";
   }

   /* Target pre-initialization */
   plxSetAnalogInputVoltage(0);
   plxSetupDACs(0);
   plxSetDigitalOutVoltage(0);
   plxInitDigitalOut();
   initPWMCapture();
   plxInitDigitalOverride();
   plxSetupAnalogSampling(1, 0, 1.79999999999999992e-06);
   plxSetMaxNumConsecutiveOverruns(5);
   setupSFPSyncMaster(0, 0, 0, 0, 0, 0, 0, 0);
   setupSFPSyncSlave(0, 0, 0);


   /* Initialization for Voltage Source AC : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/V_ac' */
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double[0] = sin(
                                                               314.159265358979326*
                                                               time);
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double[1] = cos(
                                                               314.159265358979326*
                                                               time);

   /* Initialization for Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Digital In1' */
   plxSetupDigitalInput(2, 1);

   /* Initialization for Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/AC_POWER_SW' */
   plxSetupDigitalInput(31, 1);

   /* Initialization for Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Digital In3' */
   plxSetupDigitalInput(30, 1);

   /* Initialization for Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Digital In4' */
   plxSetupDigitalInput(29, 1);

   /* Initialization for Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/PWM1H' */
   plxSetupDigitalInput(0, 1);

   /* Initialization for 1/3 Nanostep Solver : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Boost1/Configurable\nSubsystem/Nanostep/1\/3 Nanostep Solver' */
   {
      nanostep_parameters_t parameters = {
         .A1_11 = 0,
         .A1_14 = 0,
         .B1_11 = 8260,
         .Cx_vec_1 = 0,
         .sampletime = 0.00000180000000000,
         .singlephase = 1,
         .twophase = 0,
         .threephase = 0,
         .psfb = 0,
         .usePhysicalModel = 1,
         .send_iL_vC = 1,
         .clamp_a = {1, 0, 0},
         .clamp_b = {0, 0, 0},
         .sw_a_pos_en = {1, 0, 0, 0, 0, 0},
         .sw_a_neg_en = {0, 1, 0, 0, 0, 0},
         .sw_b_pos_en = {1, 1, 0, 0, 0, 0},
         .sw_b_neg_en = {1, 1, 0, 0, 0, 0},
         .enable_capacitors = {0, 0, 0}
      };
      parameters.switch_mask[0] = 1;
      parameters.switch_mask_val[0] = 0;
      parameters.switch_indices[1] = 0;
      parameters.switch_mask[1] = 0;
      parameters.switch_mask[6] = 1;
      parameters.switch_mask_val[6] = 0;
      parameters.switch_indices[7] = 0;
      parameters.switch_mask[7] = 0;
      parameters.switch_mask[12] = 1;
      parameters.switch_mask_val[12] = 0;
      parameters.switch_mask[13] = 1;
      parameters.switch_mask_val[13] = 1;
      parameters.switch_mask[18] = 1;
      parameters.switch_mask_val[18] = 0;
      parameters.switch_mask[19] = 1;
      parameters.switch_mask_val[19] = 1;
      setupPartialNanostep(0, 0, &parameters);
   };
   FPGAPhysicalModel_setupOutputToNanostep(0, 12, 13);

   /* Initialization for Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/PWM2H' */
   plxSetupDigitalInput(1, 1);

   /* Initialization for 1/3 Nanostep Solver : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Boost2/Configurable\nSubsystem/Nanostep/1\/3 Nanostep Solver' */
   {
      nanostep_parameters_t parameters = {
         .A1_11 = 0,
         .A1_14 = 0,
         .B1_11 = 8260,
         .Cx_vec_1 = 0,
         .sampletime = 0.00000180000000000,
         .singlephase = 1,
         .twophase = 0,
         .threephase = 0,
         .psfb = 0,
         .usePhysicalModel = 1,
         .send_iL_vC = 1,
         .clamp_a = {1, 0, 0},
         .clamp_b = {0, 0, 0},
         .sw_a_pos_en = {1, 0, 0, 0, 0, 0},
         .sw_a_neg_en = {0, 1, 0, 0, 0, 0},
         .sw_b_pos_en = {1, 1, 0, 0, 0, 0},
         .sw_b_neg_en = {1, 1, 0, 0, 0, 0},
         .enable_capacitors = {0, 0, 0}
      };
      parameters.switch_mask[2] = 1;
      parameters.switch_mask_val[2] = 0;
      parameters.switch_indices[3] = 1;
      parameters.switch_mask[3] = 0;
      parameters.switch_mask[8] = 1;
      parameters.switch_mask_val[8] = 0;
      parameters.switch_indices[9] = 1;
      parameters.switch_mask[9] = 0;
      parameters.switch_mask[14] = 1;
      parameters.switch_mask_val[14] = 0;
      parameters.switch_mask[15] = 1;
      parameters.switch_mask_val[15] = 1;
      parameters.switch_mask[20] = 1;
      parameters.switch_mask_val[20] = 0;
      parameters.switch_mask[21] = 1;
      parameters.switch_mask_val[21] = 1;
      setupPartialNanostep(0, 1, &parameters);
   };
   FPGAPhysicalModel_setupOutputToNanostep(1, 12, 14);

   /* Initialization for Analog Out : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Vac Line' */
   setupAnalogOut(2, 3.533569000e-03f, 0.000000000e+00f, 0.000000000e+00,
                  3.300000000e+00);

   /* Initialization for Analog Out : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Vac Neutral' */
   setupAnalogOut(3, -3.533569000e-03f, 0.000000000e+00f, 0.000000000e+00,
                  3.300000000e+00);

   /* Initialization for Analog Out : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Iin' */
   setupAnalogOut(0, 1.650000000e-01f, 0.000000000e+00f, 0.000000000e+00,
                  3.300000000e+00);

   /* Initialization for Analog Out : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Vout' */
   plxSetupMeterOutput(1, 12);
   setupAnalogOut(1, 3.533569000e-03f, 0.000000000e+00f, 0.000000000e+00,
                  3.300000000e+00);


   /* Target post-initialization */

   /* FPGA physical model init code */
   {
      static const int dcs_upper_gate_init[] = {
         0, 0, 0, 0, 0, 0, 0, 0, 0,
      };
      static const int dcs_lower_gate_init[] = {
         1, 1, 1, 1, 0, 0, 0, 0, 0,
      };
      static const int dcs_upper_gate_write_enable[] = {
         0, 0, 0, 0, 1, 1, 1, 1, 1,
      };
      static const int dcs_lower_gate_write_enable[] = {
         0, 0, 0, 0, 1, 1, 1, 1, 1,
      };
      static const int y_ext_indices[] = {
         9, 10, 11, 12, 13, 14,
      };
      static const float x_init[] = {
         0, 0,
      };
      static const int s_init[] = {
         PM_DCS_CONDSTATE_OPEN, PM_DCS_CONDSTATE_OPEN, PM_DCS_CONDSTATE_OPEN,
         PM_DCS_CONDSTATE_OPEN, PM_DCS_CONDSTATE_OPEN, PM_DCS_CONDSTATE_OPEN,
         PM_DCS_CONDSTATE_OPEN, PM_DCS_CONDSTATE_OPEN, PM_DCS_CONDSTATE_OPEN,
      };
      static const int dcs_u_indices[] = {
         0, 1, 2, 3, 7, 8, 9, 10, 13,
      };
      static const int dcs_y_indices[] = {
         0, 1, 2, 3, 4, 5, 6, 7, 8,
      };
      static const int dcs_gated_turn_on[] = {
         1, 1, 1, 1, 1, 1, 1, 1, 1,
      };
      static const int dcs_gated_turn_off[] = {
         0, 0, 0, 0, 1, 1, 1, 1, 1,
      };
      static const double dcs_upper_voltage_init[] = {
         0, 0, 0, 0, 0, 0, 0, 0, 0,
      };
      static const double dcs_lower_voltage_init[] = {
         -0.699999999999999956, -0.699999999999999956, -0.699999999999999956,
         -0.699999999999999956, 0, 0, 0, 0, 0,
      };
      static const double dcs_resonator_freq[] = {
         0, 0, 0, 0, 0, 0, 0, 0, 0,
      };
      static const int mat_A_rowptr[] = {
         0,1,2,
      };
      static const int mat_A_colidx[] = {
         1,1,
      };
      static const double mat_A_data[] = {
         -988.871215867976844,-988.871215867976844,
      };
      static const struct FPGAPhysicalModelMatrix mat_A = {
         .rowptr = &mat_A_rowptr[0],
         .colidx = &mat_A_colidx[0],
         .data   = &mat_A_data[0]
      };
      static const int mat_B_rowptr[] = {
         0,10,20,
      };
      static const int mat_B_colidx[] = {
         0,1,2,3,5,6,10,11,12,13,0,1,2,3,5,6,10,11,12,13,
      };
      static const double mat_B_data[] = {
         489.857500453118178,489.857500453118178,489.857500453118178,
         489.857500453118178,-1469.57250135935442,734.78625067967721,
         -4.57810748087026287,-1469.57250135935442,734.78625067967721,
         -4.57810748087026287,489.857500453118178,489.857500453118178,
         489.857500453118178,489.857500453118178,-1469.57250135935442,
         734.78625067967721,-4.57810748087026287,-1469.57250135935442,
         734.78625067967721,-4.57810748087026287,
      };
      static const struct FPGAPhysicalModelMatrix mat_B = {
         .rowptr = &mat_B_rowptr[0],
         .colidx = &mat_B_colidx[0],
         .data   = &mat_B_data[0]
      };
      static const int mat_C_rowptr[] = {
         0,1,2,3,4,4,4,4,5,6,6,6,6,7,8,9,
      };
      static const int mat_C_colidx[] = {
         1,1,1,1,1,1,1,1,1,
      };
      static const double mat_C_data[] = {
         -0.333333333333333315,-0.333333333333333315,-0.333333333333333315,
         -0.333333333333333315,0.00311526479750778807,0.00311526479750778807,
         1,-0.5,-0.5,
      };
      static const struct FPGAPhysicalModelMatrix mat_C = {
         .rowptr = &mat_C_rowptr[0],
         .colidx = &mat_C_colidx[0],
         .data   = &mat_C_data[0]
      };
      static const int mat_D_rowptr[] = {
         0,10,20,30,40,50,60,70,71,72,82,83,84,84,94,104,
      };
      static const int mat_D_colidx[] = {
         0,1,2,3,4,6,7,8,9,12,0,1,2,3,4,6,7,8,9,12,0,1,2,3,4,6,7,8,9,12,0,1,2,
         3,4,6,7,8,9,12,0,1,2,3,4,6,7,8,9,12,0,1,2,3,4,6,7,8,9,12,0,1,2,3,4,6,
         7,8,9,12,10,13,0,1,2,3,4,6,7,8,9,12,6,12,0,1,2,3,4,6,7,8,9,12,0,1,2,
         3,4,6,7,8,9,12,
      };
      static const double mat_D_data[] = {
         0.406856836748359429,0.2598098299183072,-0.0735235034150261146,
         0.0735235034150261146,0.134793089594214544,0.389714744877460828,
         0.144636400160707113,0.134793089594214544,-0.0122539172358376858,
         0.110285255122539172,0.2598098299183072,0.406856836748359429,
         0.0735235034150261146,-0.0735235034150261146,-0.134793089594214544,
         -0.389714744877460828,-0.144636400160707113,-0.134793089594214544,
         0.0122539172358376858,-0.110285255122539172,-0.0735235034150261146,
         0.0735235034150261146,0.406856836748359429,0.2598098299183072,
         -0.134793089594214544,0.110285255122539172,-0.144636400160707113,
         -0.134793089594214544,0.0122539172358376858,0.389714744877460828,
         0.0735235034150261146,-0.0735235034150261146,0.2598098299183072,
         0.406856836748359429,0.134793089594214544,-0.110285255122539172,
         0.144636400160707113,0.134793089594214544,-0.0122539172358376858,
         -0.389714744877460828,0.144636400160707113,-0.144636400160707113,
         -0.144636400160707113,0.144636400160707113,0.265166733627963058,
         -0.216954600241060669,0.300924065889915604,0.265166733627963058,
         -0.0241060666934511843,0.216954600241060669,0.134793089594214544,
         -0.134793089594214544,-0.134793089594214544,0.134793089594214544,
         0.330453997589393311,-0.202189634391321815,0.265166733627963058,
         0.330453997589393311,0.0608678184009642451,0.202189634391321815,
         -0.0122539172358376858,0.0122539172358376858,0.0122539172358376858,
         -0.0122539172358376858,0.0608678184009642451,0.0183808758537565287,
         -0.0241060666934511843,0.0608678184009642451,0.0853756528726396097,
         -0.0183808758537565287,0.00311526479750778807,0.00311526479750778807,
         -0.279429489754921656,0.279429489754921656,0.279429489754921656,
         -0.279429489754921656,0.404379268782643631,0.419144234632382484,
         0.433909200482121338,0.404379268782643631,-0.0367617517075130573,
         -0.419144234632382484,-1,-1,0.389714744877460828,
         -0.389714744877460828,0.110285255122539172,-0.110285255122539172,
         -0.202189634391321815,-0.584572117316191187,-0.216954600241060669,
         -0.202189634391321815,0.0183808758537565287,-0.165427882683808758,
         0.110285255122539172,-0.110285255122539172,0.389714744877460828,
         -0.389714744877460828,0.202189634391321815,-0.165427882683808758,
         0.216954600241060669,0.202189634391321815,-0.0183808758537565287,
         -0.584572117316191187,
      };
      static const struct FPGAPhysicalModelMatrix mat_D = {
         .rowptr = &mat_D_rowptr[0],
         .colidx = &mat_D_colidx[0],
         .data   = &mat_D_data[0]
      };
      static const int mat_I_rowptr[] = {
         0,1,2,
      };
      static const int mat_I_colidx[] = {
         1,1,
      };
      static const double mat_I_data[] = {
         1,1,
      };
      static const struct FPGAPhysicalModelMatrix mat_I = {
         .rowptr = &mat_I_rowptr[0],
         .colidx = &mat_I_colidx[0],
         .data   = &mat_I_data[0]
      };
      static const int uhb_dcs_indices[] = {
         0
      };
      static const int uhb_widths[] = {
         0
      };
      static const int uhb_voltmeters[] = {
         0
      };
      static const int uhb_current_sources[] = {
         0
      };
      static const int uhb_upper_pwms[] = {
         0
      };
      static const int uhb_lower_pwms[] = {
         0
      };
      static const int uhb_upper_bias[] = {
         0
      };
      static const int uhb_lower_bias[] = {
         0
      };
      static const struct FPGAPhysicalModel model =
      {
         .nx = 2,
         .nu = 14,
         .ny = 15,
         .ndcs = 9,
         .nuhb = 0,
         .ny_ext = 6,
         .y_ext_indices = &y_ext_indices[0],

         .mat_A = &mat_A,
         .mat_B = &mat_B,
         .mat_C = &mat_C,
         .mat_D = &mat_D,
         .mat_I = &mat_I,

         .discretization_method = PM_DISCRETIZATION_METHOD_RADAU,

         .x_init = &x_init[0],
         .s_init = &s_init[0],

         .dcs = {
            .resistance = 1,

            .u_indices = &dcs_u_indices[0],
            .y_indices = &dcs_y_indices[0],

            .gated_turn_on = &dcs_gated_turn_on[0],
            .gated_turn_off = &dcs_gated_turn_off[0],

            .upper_voltage_init = &dcs_upper_voltage_init[0],
            .lower_voltage_init = &dcs_lower_voltage_init[0],

            .upper_gate_init = &dcs_upper_gate_init[0],
            .lower_gate_init = &dcs_lower_gate_init[0],
            .upper_gate_write_enable = &dcs_upper_gate_write_enable[0],
            .lower_gate_write_enable = &dcs_lower_gate_write_enable[0],
            .all_gates_constant = 0,

            .resonator_freq = &dcs_resonator_freq[0]
         },

         .uhb = {
            .dcs_indices = &uhb_dcs_indices[0],
            .widths = &uhb_widths[0],
            .voltmeters = &uhb_voltmeters[0],
            .current_sources = &uhb_current_sources[0],
            .upper_pwms = &uhb_upper_pwms[0],
            .lower_pwms = &uhb_lower_pwms[0],
            .upper_bias = &uhb_upper_bias[0],
            .lower_bias = &uhb_lower_bias[0]

         },

         .cpu_base_period = 1.79999999999999992e-06,
         .sync_steps = 0
      };

      FPGAPhysicalModel_setupInputFromNanostep(1, 1, 4);
      FPGAPhysicalModel_setupInputFromNanostep(1, 0, 3);
      FPGAPhysicalModel_setupInputFromNanostep(0, 1, 2);
      FPGAPhysicalModel_setupInputFromNanostep(0, 0, 1);
      FPGAPhysicalModel_setup(&model);
   }
}

void Semi_Bridgeless_PFC_990W_converter_RT_BOX_step(void)
{
   if (Semi_Bridgeless_PFC_990W_converter_RT_BOX_errorStatus)
   {
      return;
   }

   /* Voltage Source AC : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/V_ac' */
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_V_ac = 325.21999999999997 *
                                                      (1.*
                                                       Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double
                                                       [0] + 0.*
                                                       Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double
                                                       [1]);

   /* Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Digital In1' */
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn1 = getDigitalIn(2);

   /* Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/AC_POWER_SW' */
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_AC_POWER_SW = getDigitalIn(31);

   /* Logical Operator : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Logical\nOperator' */
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_LogicalOperator =
      !Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_AC_POWER_SW;

   /* Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Digital In3' */
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn3 = getDigitalIn(30);

   /* Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Digital In4' */
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn4 = getDigitalIn(29);

   /* Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/PWM1H' */
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_PWM1H = getDigitalIn(0);

   /* 1/3 Nanostep Solver : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Boost1/Configurable\nSubsystem/Nanostep/1\/3 Nanostep Solver' */
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_x1_3NanostepSolver[0] =
      getNanostepPrimaryCurrent(0,0);
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_x1_3NanostepSolver[1] =
      getNanostepSecondaryCurrent(0,0);
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_x1_3NanostepSolver[2] =
      getNanostepInductorCurrent(0,0);
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_x1_3NanostepSolver[3] =
      getNanostepCapacitorVoltage(0,0);

   /* Digital In : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/PWM2H' */
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_PWM2H = getDigitalIn(1);

   /* 1/3 Nanostep Solver : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Boost2/Configurable\nSubsystem/Nanostep/1\/3 Nanostep Solver' */
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_x1_3NanostepSolver_1[0] =
      getNanostepPrimaryCurrent(0,1);
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_x1_3NanostepSolver_1[1] =
      getNanostepSecondaryCurrent(0,1);
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_x1_3NanostepSolver_1[2] =
      getNanostepInductorCurrent(0,1);
   Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_x1_3NanostepSolver_1[3] =
      getNanostepCapacitorVoltage(0,1);
   /* FPGA physical model output code */
   {}

   /* Minimum / Maximum : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Min\/Max1'
    * incorporates
    *  Voltmeter : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Vm2'
    *  Constant : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Constant'
    */
   {
      double u, y;
      y = FPGAPhysicalModel_getOutput(0);
      u = 0.;
      if (u > y)
         y = u;
      Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_Min_Max1 = y;
   }
   /* Analog Out : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Vac Line' */
   setAnalogOut(2, Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_Min_Max1);
   /* Minimum / Maximum : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Min\/Max2'
    * incorporates
    *  Constant : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Constant'
    *  Voltmeter : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Vm2'
    */
   {
      double u, y;
      y = 0.;
      u = FPGAPhysicalModel_getOutput(0);
      if (u < y)
         y = u;
      Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_Min_Max2 = y;
   }
   /* Analog Out : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Vac Neutral' */
   setAnalogOut(3, Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_Min_Max2);
   /* Minimum / Maximum : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Min\/Max'
    * incorporates
    *  Ammeter : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Am1'
    *  Ammeter : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Am2'
    */
   {
      double u, y;
      y = FPGAPhysicalModel_getOutput(1);
      u = FPGAPhysicalModel_getOutput(2);
      if (u > y)
         y = u;
      Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_Min_Max = y;
   }
   /* Analog Out : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/Iin' */
   setAnalogOut(0, Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_Min_Max);
   if (Semi_Bridgeless_PFC_990W_converter_RT_BOX_errorStatus)
   {
      return;
   }

   /* Update for Voltage Source AC : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX/V_ac' */
   {
      double scaling, scaledX, scaledY;
      scaling = 1. +
                (0.5 *
                 (Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double[0]*
                  Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double[0] +
                  Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double[1]*
                  Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double[1] -
      1.));
      scaledX = Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double[0] /
                scaling;
      scaledY = Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double[1] /
                scaling;
      Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double[0] =
         0.999999840112412941 * scaledX + 0.000565486647508062277 * scaledY;
      Semi_Bridgeless_PFC_990W_converter_RT_BOX_D_double[1] =
         -0.000565486647508062277 * scaledX + 0.999999840112412941 * scaledY;
   }

   /* Update for Subsystem : 'Semi_Bridgeless_PFC_990W_converter_RT-BOX' */

   /* FPGA physical model update code */
   {
      FPGAPhysicalModel_setInput(0,
                                 Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_V_ac);
      FPGAPhysicalModel_setDcsUpperGate(4,
                                        Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn1);
      FPGAPhysicalModel_setDcsLowerGate(4,
                                        Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn1);
      FPGAPhysicalModel_setDcsUpperGate(5,
                                        Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_AC_POWER_SW);
      FPGAPhysicalModel_setDcsLowerGate(5,
                                        Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_AC_POWER_SW);
      FPGAPhysicalModel_setDcsUpperGate(6,
                                        Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_LogicalOperator);
      FPGAPhysicalModel_setDcsLowerGate(6,
                                        Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_LogicalOperator);
      FPGAPhysicalModel_setDcsUpperGate(7,
                                        Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn3);
      FPGAPhysicalModel_setDcsLowerGate(7,
                                        Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn3);
      FPGAPhysicalModel_setDcsUpperGate(8,
                                        Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn4);
      FPGAPhysicalModel_setDcsLowerGate(8,
                                        Semi_Bridgeless_PFC_990W_converter_RT_BOX_B_DigitalIn4);
   }
}

void Semi_Bridgeless_PFC_990W_converter_RT_BOX_terminate(void)
{
}
void Semi_Bridgeless_PFC_990W_converter_RT_BOX_sync(void)
{
   static size_t tick[0] = {  };
}
