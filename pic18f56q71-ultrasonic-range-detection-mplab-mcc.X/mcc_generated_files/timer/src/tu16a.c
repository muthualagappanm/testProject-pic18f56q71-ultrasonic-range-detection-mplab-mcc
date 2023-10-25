/**
 * TU16A Generated Driver File
 *
 * @file tu16a.c
 *  
 * @ingroup tu16a
 *
 * @brief This file contains the API definitions for the TU16A module.
 *
 * @version TU16A Driver Version 2.1.0
 */

 /*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include <xc.h>
#include "../tu16a.h"

const struct TMR_INTERFACE COUNTER = {
    .Initialize = COUNTER_Initialize,
    .Start = COUNTER_Start,
    .Stop = COUNTER_Stop,
    .PeriodCountSet = COUNTER_Write,
    .TimeoutCallbackRegister = NULL,
    .Tasks = NULL
};

void COUNTER_Initialize(void)
{
    //Stop Timer
    TU16ACON0bits.ON = 0;

    //CIF disabled; ZIF disabled; PRIF disabled; CAPT disabled; LIMIT disabled; CLR disabled; OSEN disabled;  
    TU16ACON1 = 0x0;
    //STOP At PR Match; RESET ERS level = 0 or PR match; START Rising ERS edge; CSYNC disabled; EPOL inverted;  
    TU16AHLT = 0xA7;
    //CLK HFINTOSC;   
    TU16ACLK = 0x3;
    //ERS PWM2_OUT1;  
    TU16AERS = 0x6;
    //PS 20;  
    TU16APS = 0x14;
    //PRH 255; 
    TU16APRH = 0xFF;
    //PRL 244; 
    TU16APRL = 0xF4;
    //TMRH 0; 
    TU16ATMRH = 0x0;
    //TMRL 0; 
    TU16ATMRL = 0x0;

    //disable TUI interrupt
    PIE5bits.TU16AIE = 0;

    //CIE disabled; ZIE disabled; PRIE disabled; RDSEL read; OPOL low; OM pulse mode; CPOL rising edge; ON enabled;  
    TU16ACON0 = 0xC0;
}

void COUNTER_Start(void)
{
    TU16ACON0bits.ON = 1;
}

void COUNTER_Stop(void)
{
    TU16ACON0bits.ON = 0;
}

uint16_t COUNTER_CaptureValueRead(void)
{
    TU16ACON0bits.RDSEL = 0;
    return (uint16_t)(((uint16_t)TU16ACRHbits.CRH<< 8) | TU16ACRLbits.CRL);
}

uint16_t COUNTER_OnCommandCapture(void)
{
    TU16ACON1bits.CAPT = 1;
    while(TU16ACON1bits.CAPT == 1);
    return COUNTER_CaptureValueRead();
}

uint16_t COUNTER_Read(void)
{
    bool onVal = TU16ACON0bits.ON;
    TU16ACON0bits.ON = 0;
    TU16ACON0bits.RDSEL = 1;
    uint16_t tmrVal = (uint16_t)(((uint16_t)TU16ATMRHbits.TMRH << 8) | TU16ATMRLbits.TMRL);
    TU16ACON0bits.ON = onVal;
    return tmrVal;
}

void COUNTER_Write(size_t timerVal)
{
    uint16_t timerValGet = (uint16_t) timerVal;
    bool onVal = TU16ACON0bits.ON;
    TU16ACON0bits.ON = 0;
    TU16ATMRHbits.TMRH = (uint8_t) (timerValGet >> 8);
    TU16ATMRLbits.TMRL = (uint8_t) (timerValGet & 0xFF);
    TU16ACON0bits.ON = onVal;
}

void COUNTER_CounterClear(void)
{
    TU16ACON1bits.CLR = 1;
    while(TU16ACON1bits.CLR == 1);
}

void COUNTER_PeriodValueSet(uint16_t prVal)
{
    TU16APRHbits.PRH = (uint8_t)((prVal >> 8) & 0xFF);
    TU16APRLbits.PRL = (uint8_t)(prVal & 0xFF);
}

void COUNTER_PRMatchInterruptEnable(void)
{
    TU16ACON0bits.PRIE = 1;
}

void COUNTER_PRMatchInterruptDisable(void)
{
    TU16ACON0bits.PRIE = 0;
}

void COUNTER_ZeroInterruptEnable(void)
{
    TU16ACON0bits.ZIE = 1;
}

void COUNTER_ZeroInterruptDisable(void)
{
    TU16ACON0bits.ZIE = 0;
}

void COUNTER_CaptureInterruptEnable(void)
{
    TU16ACON0bits.CIE = 1;
}

void COUNTER_CaptureInterruptDisable(void)
{
    TU16ACON0bits.CIE = 0;
}

bool COUNTER_HasPRMatchOccured(void)
{
    return TU16ACON1bits.PRIF;
}

bool COUNTER_HasResetOccured(void)
{
    return TU16ACON1bits.ZIF;
}

bool COUNTER_HasCaptureOccured(void)
{
    return TU16ACON1bits.CIF;
}

bool COUNTER_IsTimerRunning(void)
{
    return TU16ACON1bits.RUN;
}

void COUNTER_InterruptEnable(void)
{
    PIE5bits.TU16AIE = 1;
}

void COUNTER_InterruptDisable(void)
{
    PIE5bits.TU16AIE = 0;
}

bool COUNTER_IsInterruptEnabled(void)
{
    return PIE5bits.TU16AIE;
}

void COUNTER_InterruptFlagsClear(void)
{
    TU16ACON1bits.PRIF = 0;
    TU16ACON1bits.ZIF = 0;
    TU16ACON1bits.CIF = 0;
}

