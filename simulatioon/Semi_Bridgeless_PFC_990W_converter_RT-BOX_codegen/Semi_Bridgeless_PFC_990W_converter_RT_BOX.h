/*
 * Header file for: Semi_Bridgeless_PFC_990W_converter_RT-BOX
 * Generated with : PLECS 4.9.6
 *                  PLECS RT Box 3 3.1.4
 * Generated on   : 5 Sep 2025 10:49:26
 */
#ifndef PLECS_HEADER_Semi_Bridgeless_PFC_990W_converter_RT_BOX_h_
#define PLECS_HEADER_Semi_Bridgeless_PFC_990W_converter_RT_BOX_h_

#include <stdbool.h>
#include <stdint.h>

/* Model floating point type */
typedef double Semi_Bridgeless_PFC_990W_converter_RT_BOX_FloatType;

/* Model checksum */
extern const char * const Semi_Bridgeless_PFC_990W_converter_RT_BOX_checksum;

/* Model error status */
extern const char * Semi_Bridgeless_PFC_990W_converter_RT_BOX_errorStatus;


/* Model sample time */
extern const double Semi_Bridgeless_PFC_990W_converter_RT_BOX_sampleTime;


#if defined(EXTERNAL_MODE) && EXTERNAL_MODE
/* External mode signals */
#define Semi_Bridgeless_PFC_990W_converter_RT_BOX_NumExtModeSignals 0
extern const double * const
Semi_Bridgeless_PFC_990W_converter_RT_BOX_ExtModeSignals[];
/* Tunable parameters */
#define Semi_Bridgeless_PFC_990W_converter_RT_BOX_NumTunableParameters 0
#endif /* defined(EXTERNAL_MODE) */


/* Entry point functions */
void Semi_Bridgeless_PFC_990W_converter_RT_BOX_initialize(double time);
void Semi_Bridgeless_PFC_990W_converter_RT_BOX_step(void);
void Semi_Bridgeless_PFC_990W_converter_RT_BOX_terminate(void);
void Semi_Bridgeless_PFC_990W_converter_RT_BOX_sync(void);

#endif /* PLECS_HEADER_Semi_Bridgeless_PFC_990W_converter_RT_BOX_h_ */
