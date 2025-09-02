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
#ifndef __INIT_COMPENSATORS_H__
#define __INIT_COMPENSATORS_H__

#include "stdint.h"
//#include "dcdt.h"
#include "pfc_Variables.h"

#include <dsp.h>
                        

extern tPID VloopPID;
extern fractional vLoopABCCoefficient[3] __attribute__ ((section (".xbss, bss, xmemory")));
extern fractional vLoopControlHistory[3] __attribute__ ((section (".ybss, bss, ymemory")));
extern fractional vLoopKcoeffs[];

extern tPID CloopPID;
extern fractional cLoopABCCoefficient[3] __attribute__ ((section (".xbss, bss, xmemory")));
extern fractional cLoopControlHistory[3] __attribute__ ((section (".ybss, bss, ymemory")));
extern fractional cLoopKcoeffs[];

extern tPID C2loopPID;
extern fractional c2LoopABCCoefficient[3] __attribute__ ((section (".xbss, bss, xmemory")));
extern fractional c2LoopControlHistory[3] __attribute__ ((section (".ybss, bss, ymemory")));
extern fractional c2LoopKcoeffs[];

void initPFCComp(void)  ;                       /* Initialization of Compensator variables */
void PFCCompReset(void);

#endif

