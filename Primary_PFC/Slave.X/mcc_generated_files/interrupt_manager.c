/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the generated driver implementation file for setting up the
    interrupts using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This source file provides implementations for PIC24 / dsPIC33 / PIC32MM MCUs interrupts.
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.5
        Device            :  dsPIC33CH128MP205S1
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB             :  MPLAB X v6.05
*/
/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
    Section: Includes
*/
#include <xc.h>

/**
    void INTERRUPT_Initialize (void)
*/
void INTERRUPT_Initialize (void)
{
    //    ADCAN19: ADC AN19 Convert Done
    //    Priority: 1
        IPC27bits.ADCAN19IP = 1;
    //    ADCAN7: ADC AN7 Convert Done
    //    Priority: 5
        IPC24bits.ADCAN7IP = 5;
    //    ADCAN20: ADC AN20 Convert Done
    //    Priority: 1
        IPC27bits.ADCAN20IP = 1;
    //    ADCAN0: ADC AN0 Convert Done
    //    Priority: 5
        IPC22bits.ADCAN0IP = 5;
    //    ADCAN2: ADC AN2 Convert Done
    //    Priority: 1
        IPC23bits.ADCAN2IP = 1;
    //    UEVTI: UART1 Event
    //    Priority: 1
        IPC47bits.U1EVTIP = 1;
    //    UTXI: UART1 TX
    //    Priority: 1
        IPC3bits.U1TXIP = 1;
    //    UEI: UART1 Error Interrupt
    //    Priority: 1
        IPC12bits.U1EIP = 1;
    //    URXI: UART1 RX
    //    Priority: 1
        IPC2bits.U1RXIP = 1;
    //    TI: Timer 1
    //    Priority: 3
        IPC0bits.T1IP = 3;
}
