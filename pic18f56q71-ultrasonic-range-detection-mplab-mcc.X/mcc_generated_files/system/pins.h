/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.0
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RA1 aliases
#define OPAMP_OUT_TRIS                 TRISAbits.TRISA1
#define OPAMP_OUT_LAT                  LATAbits.LATA1
#define OPAMP_OUT_PORT                 PORTAbits.RA1
#define OPAMP_OUT_WPU                  WPUAbits.WPUA1
#define OPAMP_OUT_OD                   ODCONAbits.ODCA1
#define OPAMP_OUT_ANS                  ANSELAbits.ANSELA1
#define OPAMP_OUT_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define OPAMP_OUT_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define OPAMP_OUT_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define OPAMP_OUT_GetValue()           PORTAbits.RA1
#define OPAMP_OUT_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define OPAMP_OUT_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define OPAMP_OUT_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define OPAMP_OUT_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define OPAMP_OUT_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define OPAMP_OUT_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define OPAMP_OUT_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define OPAMP_OUT_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set RA5 aliases
#define RECEIVE_TRIS                 TRISAbits.TRISA5
#define RECEIVE_LAT                  LATAbits.LATA5
#define RECEIVE_PORT                 PORTAbits.RA5
#define RECEIVE_WPU                  WPUAbits.WPUA5
#define RECEIVE_OD                   ODCONAbits.ODCA5
#define RECEIVE_ANS                  ANSELAbits.ANSELA5
#define RECEIVE_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define RECEIVE_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define RECEIVE_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define RECEIVE_GetValue()           PORTAbits.RA5
#define RECEIVE_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define RECEIVE_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define RECEIVE_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define RECEIVE_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define RECEIVE_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define RECEIVE_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define RECEIVE_SetAnalogMode()      do { ANSELAbits.ANSELA5 = 1; } while(0)
#define RECEIVE_SetDigitalMode()     do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set RB0 aliases
#define DRIVE1_TRIS                 TRISBbits.TRISB0
#define DRIVE1_LAT                  LATBbits.LATB0
#define DRIVE1_PORT                 PORTBbits.RB0
#define DRIVE1_WPU                  WPUBbits.WPUB0
#define DRIVE1_OD                   ODCONBbits.ODCB0
#define DRIVE1_ANS                  ANSELBbits.ANSELB0
#define DRIVE1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define DRIVE1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define DRIVE1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define DRIVE1_GetValue()           PORTBbits.RB0
#define DRIVE1_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define DRIVE1_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define DRIVE1_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define DRIVE1_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define DRIVE1_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define DRIVE1_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define DRIVE1_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define DRIVE1_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 aliases
#define CMP_IN_TRIS                 TRISBbits.TRISB1
#define CMP_IN_LAT                  LATBbits.LATB1
#define CMP_IN_PORT                 PORTBbits.RB1
#define CMP_IN_WPU                  WPUBbits.WPUB1
#define CMP_IN_OD                   ODCONBbits.ODCB1
#define CMP_IN_ANS                  ANSELBbits.ANSELB1
#define CMP_IN_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define CMP_IN_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define CMP_IN_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define CMP_IN_GetValue()           PORTBbits.RB1
#define CMP_IN_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define CMP_IN_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define CMP_IN_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define CMP_IN_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define CMP_IN_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define CMP_IN_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define CMP_IN_SetAnalogMode()      do { ANSELBbits.ANSELB1 = 1; } while(0)
#define CMP_IN_SetDigitalMode()     do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB3 aliases
#define DRIVE2_TRIS                 TRISBbits.TRISB3
#define DRIVE2_LAT                  LATBbits.LATB3
#define DRIVE2_PORT                 PORTBbits.RB3
#define DRIVE2_WPU                  WPUBbits.WPUB3
#define DRIVE2_OD                   ODCONBbits.ODCB3
#define DRIVE2_ANS                  ANSELBbits.ANSELB3
#define DRIVE2_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define DRIVE2_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define DRIVE2_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define DRIVE2_GetValue()           PORTBbits.RB3
#define DRIVE2_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define DRIVE2_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define DRIVE2_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define DRIVE2_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define DRIVE2_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define DRIVE2_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define DRIVE2_SetAnalogMode()      do { ANSELBbits.ANSELB3 = 1; } while(0)
#define DRIVE2_SetDigitalMode()     do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set RB4 aliases
#define UART_TX_TRIS                 TRISBbits.TRISB4
#define UART_TX_LAT                  LATBbits.LATB4
#define UART_TX_PORT                 PORTBbits.RB4
#define UART_TX_WPU                  WPUBbits.WPUB4
#define UART_TX_OD                   ODCONBbits.ODCB4
#define UART_TX_ANS                  ANSELBbits.ANSELB4
#define UART_TX_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define UART_TX_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define UART_TX_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define UART_TX_GetValue()           PORTBbits.RB4
#define UART_TX_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define UART_TX_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define UART_TX_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define UART_TX_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define UART_TX_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define UART_TX_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define UART_TX_SetAnalogMode()      do { ANSELBbits.ANSELB4 = 1; } while(0)
#define UART_TX_SetDigitalMode()     do { ANSELBbits.ANSELB4 = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/