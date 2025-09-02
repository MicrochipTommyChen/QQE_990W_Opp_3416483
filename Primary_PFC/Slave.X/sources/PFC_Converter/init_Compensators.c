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

#include "init_Compensators.h"
#include "pfc_Variables.h"

/*******************************************************************************
Global variables
*******************************************************************************/

tPID VloopPID;
fractional vLoopABCCoefficient[3] __attribute__ ((section (".xbss, bss, xmemory")));
fractional vLoopControlHistory[3] __attribute__ ((section (".ybss, bss, ymemory")));
fractional vLoopKcoeffs[] = {0,0,0};

tPID CloopPID;
fractional cLoopABCCoefficient[3] __attribute__ ((section (".xbss, bss, xmemory")));
fractional cLoopControlHistory[3] __attribute__ ((section (".ybss, bss, ymemory")));
fractional cLoopKcoeffs[] = {0,0,0};

tPID C2loopPID;
fractional c2LoopABCCoefficient[3] __attribute__ ((section (".xbss, bss, xmemory")));
fractional c2LoopControlHistory[3] __attribute__ ((section (".ybss, bss, ymemory")));
fractional c2LoopKcoeffs[] = {0,0,0};
/*******************************************************************************
Function: 	initPFCComp
Description:	Initialize compensators for PFC (PID compensator for both 
  current and voltage Loops)
*******************************************************************************/
void initPFCComp(void)
{
    /* Voltage Loop PID */
    VloopPID.abcCoefficients = &vLoopABCCoefficient[0];     /*Set up pointer to derived coefficients */
    VloopPID.controlHistory = &vLoopControlHistory[0];      /*Set up pointer to controller history samples */
    PIDInit(&VloopPID);                                     /*Clear the controller history and the controller output */
    vLoopKcoeffs[0] = Q15(0.1);
    vLoopKcoeffs[1] = Q15(0.0025);
    vLoopKcoeffs[2] = Q15(0);
    PIDCoeffCalc(&vLoopKcoeffs[0], &VloopPID);              /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    
    /* CT1 Current Loop PID */
    CloopPID.abcCoefficients = &cLoopABCCoefficient[0];     /*Set up pointer to derived coefficients */
    CloopPID.controlHistory = &cLoopControlHistory[0];      /*Set up pointer to controller history samples */
    PIDInit(&CloopPID);                                     /*Clear the controller history and the controller output */
    cLoopKcoeffs[0] = Q15(0.3);
    cLoopKcoeffs[1] = Q15(0.05);
    cLoopKcoeffs[2] = Q15(0);
    PIDCoeffCalc(&cLoopKcoeffs[0], &CloopPID);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    
    /* CT2 Current Loop PID */
    C2loopPID.abcCoefficients = &c2LoopABCCoefficient[0];     /*Set up pointer to derived coefficients */
    C2loopPID.controlHistory = &c2LoopControlHistory[0];      /*Set up pointer to controller history samples */
    PIDInit(&C2loopPID);                                     /*Clear the controller history and the controller output */
    c2LoopKcoeffs[0] = Q15(0.3);
    c2LoopKcoeffs[1] = Q15(0.05);
    c2LoopKcoeffs[2] = Q15(0);
    PIDCoeffCalc(&c2LoopKcoeffs[0], &C2loopPID);             /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */    
}

void PFCCompReset(void)
{
    VloopPID.measuredOutput = 0;
    VloopPID.controlReference = 0;
    VloopPID.controlOutput = 0;
    
    CloopPID.measuredOutput = 0;
    CloopPID.controlReference = 0;
    CloopPID.controlOutput = 0;
    
    C2loopPID.measuredOutput = 0;
    C2loopPID.controlReference = 0;
    C2loopPID.controlOutput = 0;

    pfcVoltCompOutput = 0;
    pfcCurrCompOutput = 0;
    pfcCurr2CompOutput = 0;
    
    pfcVoltageRef = 0;
    pfcCurrentRef = 0;
}
/*******************************************************************************
End of Function
*******************************************************************************/
