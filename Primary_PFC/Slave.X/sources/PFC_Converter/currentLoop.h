/* 
 * File:   currentLoop.h
 * Author: A50807
 *
 * Created on May 11, 2022, 9:50 AM
 */

#ifndef CURRENTLOOP_H
#define	CURRENTLOOP_H

#include <xc.h>

#include "defines.h"
#include "init_Compensators.h"
#include "pfc_Variables.h"
#include "pfcControl.h"

void inline __attribute__((optimize(1))) Current_Compensator(void);
void inline __attribute__((optimize(1))) Current_Compensator_Two(void);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* CURRENTLOOP_H */

