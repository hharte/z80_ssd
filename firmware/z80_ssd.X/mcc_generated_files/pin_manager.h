/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F47Q43
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set CPU_A0 aliases
#define CPU_A0_TRIS                 TRISAbits.TRISA0
#define CPU_A0_LAT                  LATAbits.LATA0
#define CPU_A0_PORT                 PORTAbits.RA0
#define CPU_A0_WPU                  WPUAbits.WPUA0
#define CPU_A0_OD                   ODCONAbits.ODCA0
#define CPU_A0_ANS                  ANSELAbits.ANSELA0
#define CPU_A0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define CPU_A0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define CPU_A0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define CPU_A0_GetValue()           PORTAbits.RA0
#define CPU_A0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define CPU_A0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define CPU_A0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define CPU_A0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define CPU_A0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define CPU_A0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define CPU_A0_SetAnalogMode()      do { ANSELAbits.ANSELA0 = 1; } while(0)
#define CPU_A0_SetDigitalMode()     do { ANSELAbits.ANSELA0 = 0; } while(0)

// get/set CPU_A1 aliases
#define CPU_A1_TRIS                 TRISAbits.TRISA1
#define CPU_A1_LAT                  LATAbits.LATA1
#define CPU_A1_PORT                 PORTAbits.RA1
#define CPU_A1_WPU                  WPUAbits.WPUA1
#define CPU_A1_OD                   ODCONAbits.ODCA1
#define CPU_A1_ANS                  ANSELAbits.ANSELA1
#define CPU_A1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define CPU_A1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define CPU_A1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define CPU_A1_GetValue()           PORTAbits.RA1
#define CPU_A1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define CPU_A1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define CPU_A1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define CPU_A1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define CPU_A1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define CPU_A1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define CPU_A1_SetAnalogMode()      do { ANSELAbits.ANSELA1 = 1; } while(0)
#define CPU_A1_SetDigitalMode()     do { ANSELAbits.ANSELA1 = 0; } while(0)

// get/set CPU_A2 aliases
#define CPU_A2_TRIS                 TRISAbits.TRISA2
#define CPU_A2_LAT                  LATAbits.LATA2
#define CPU_A2_PORT                 PORTAbits.RA2
#define CPU_A2_WPU                  WPUAbits.WPUA2
#define CPU_A2_OD                   ODCONAbits.ODCA2
#define CPU_A2_ANS                  ANSELAbits.ANSELA2
#define CPU_A2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define CPU_A2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define CPU_A2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define CPU_A2_GetValue()           PORTAbits.RA2
#define CPU_A2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define CPU_A2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define CPU_A2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define CPU_A2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define CPU_A2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define CPU_A2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define CPU_A2_SetAnalogMode()      do { ANSELAbits.ANSELA2 = 1; } while(0)
#define CPU_A2_SetDigitalMode()     do { ANSELAbits.ANSELA2 = 0; } while(0)

// get/set CPU_A3 aliases
#define CPU_A3_TRIS                 TRISAbits.TRISA3
#define CPU_A3_LAT                  LATAbits.LATA3
#define CPU_A3_PORT                 PORTAbits.RA3
#define CPU_A3_WPU                  WPUAbits.WPUA3
#define CPU_A3_OD                   ODCONAbits.ODCA3
#define CPU_A3_ANS                  ANSELAbits.ANSELA3
#define CPU_A3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define CPU_A3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define CPU_A3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define CPU_A3_GetValue()           PORTAbits.RA3
#define CPU_A3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define CPU_A3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define CPU_A3_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define CPU_A3_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define CPU_A3_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define CPU_A3_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define CPU_A3_SetAnalogMode()      do { ANSELAbits.ANSELA3 = 1; } while(0)
#define CPU_A3_SetDigitalMode()     do { ANSELAbits.ANSELA3 = 0; } while(0)

// get/set RA4 procedures
#define RA4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define RA4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define RA4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RA4_GetValue()              PORTAbits.RA4
#define RA4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define RA4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define RA4_SetPullup()             do { WPUAbits.WPUA4 = 1; } while(0)
#define RA4_ResetPullup()           do { WPUAbits.WPUA4 = 0; } while(0)
#define RA4_SetAnalogMode()         do { ANSELAbits.ANSELA4 = 1; } while(0)
#define RA4_SetDigitalMode()        do { ANSELAbits.ANSELA4 = 0; } while(0)

// get/set RA5 procedures
#define RA5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define RA5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define RA5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define RA5_GetValue()              PORTAbits.RA5
#define RA5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define RA5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define RA5_SetPullup()             do { WPUAbits.WPUA5 = 1; } while(0)
#define RA5_ResetPullup()           do { WPUAbits.WPUA5 = 0; } while(0)
#define RA5_SetAnalogMode()         do { ANSELAbits.ANSELA5 = 1; } while(0)
#define RA5_SetDigitalMode()        do { ANSELAbits.ANSELA5 = 0; } while(0)

// get/set RA6 procedures
#define RA6_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define RA6_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define RA6_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define RA6_GetValue()              PORTAbits.RA6
#define RA6_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define RA6_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define RA6_SetPullup()             do { WPUAbits.WPUA6 = 1; } while(0)
#define RA6_ResetPullup()           do { WPUAbits.WPUA6 = 0; } while(0)
#define RA6_SetAnalogMode()         do { ANSELAbits.ANSELA6 = 1; } while(0)
#define RA6_SetDigitalMode()        do { ANSELAbits.ANSELA6 = 0; } while(0)

// get/set RA7 procedures
#define RA7_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define RA7_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define RA7_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define RA7_GetValue()              PORTAbits.RA7
#define RA7_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define RA7_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define RA7_SetPullup()             do { WPUAbits.WPUA7 = 1; } while(0)
#define RA7_ResetPullup()           do { WPUAbits.WPUA7 = 0; } while(0)
#define RA7_SetAnalogMode()         do { ANSELAbits.ANSELA7 = 1; } while(0)
#define RA7_SetDigitalMode()        do { ANSELAbits.ANSELA7 = 0; } while(0)

// get/set CPU_RESET_N aliases
#define CPU_RESET_N_TRIS                 TRISBbits.TRISB0
#define CPU_RESET_N_LAT                  LATBbits.LATB0
#define CPU_RESET_N_PORT                 PORTBbits.RB0
#define CPU_RESET_N_WPU                  WPUBbits.WPUB0
#define CPU_RESET_N_OD                   ODCONBbits.ODCB0
#define CPU_RESET_N_ANS                  ANSELBbits.ANSELB0
#define CPU_RESET_N_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define CPU_RESET_N_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define CPU_RESET_N_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define CPU_RESET_N_GetValue()           PORTBbits.RB0
#define CPU_RESET_N_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define CPU_RESET_N_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define CPU_RESET_N_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define CPU_RESET_N_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define CPU_RESET_N_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define CPU_RESET_N_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define CPU_RESET_N_SetAnalogMode()      do { ANSELBbits.ANSELB0 = 1; } while(0)
#define CPU_RESET_N_SetDigitalMode()     do { ANSELBbits.ANSELB0 = 0; } while(0)

// get/set RB1 procedures
#define RB1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define RB1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define RB1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define RB1_GetValue()              PORTBbits.RB1
#define RB1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define RB1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define RB1_SetPullup()             do { WPUBbits.WPUB1 = 1; } while(0)
#define RB1_ResetPullup()           do { WPUBbits.WPUB1 = 0; } while(0)
#define RB1_SetAnalogMode()         do { ANSELBbits.ANSELB1 = 1; } while(0)
#define RB1_SetDigitalMode()        do { ANSELBbits.ANSELB1 = 0; } while(0)

// get/set RB2 procedures
#define RB2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define RB2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define RB2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define RB2_GetValue()              PORTBbits.RB2
#define RB2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define RB2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define RB2_SetPullup()             do { WPUBbits.WPUB2 = 1; } while(0)
#define RB2_ResetPullup()           do { WPUBbits.WPUB2 = 0; } while(0)
#define RB2_SetAnalogMode()         do { ANSELBbits.ANSELB2 = 1; } while(0)
#define RB2_SetDigitalMode()        do { ANSELBbits.ANSELB2 = 0; } while(0)

// get/set RB3 procedures
#define RB3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define RB3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define RB3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define RB3_GetValue()              PORTBbits.RB3
#define RB3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define RB3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define RB3_SetPullup()             do { WPUBbits.WPUB3 = 1; } while(0)
#define RB3_ResetPullup()           do { WPUBbits.WPUB3 = 0; } while(0)
#define RB3_SetAnalogMode()         do { ANSELBbits.ANSELB3 = 1; } while(0)
#define RB3_SetDigitalMode()        do { ANSELBbits.ANSELB3 = 0; } while(0)

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSELB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSELB4 = 0; } while(0)

// get/set SDCard_CS aliases
#define SDCard_CS_TRIS                 TRISBbits.TRISB5
#define SDCard_CS_LAT                  LATBbits.LATB5
#define SDCard_CS_PORT                 PORTBbits.RB5
#define SDCard_CS_WPU                  WPUBbits.WPUB5
#define SDCard_CS_OD                   ODCONBbits.ODCB5
#define SDCard_CS_ANS                  ANSELBbits.ANSELB5
#define SDCard_CS_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define SDCard_CS_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define SDCard_CS_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define SDCard_CS_GetValue()           PORTBbits.RB5
#define SDCard_CS_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define SDCard_CS_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define SDCard_CS_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define SDCard_CS_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define SDCard_CS_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define SDCard_CS_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define SDCard_CS_SetAnalogMode()      do { ANSELBbits.ANSELB5 = 1; } while(0)
#define SDCard_CS_SetDigitalMode()     do { ANSELBbits.ANSELB5 = 0; } while(0)

// get/set RC0 procedures
#define RC0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define RC0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define RC0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define RC0_GetValue()              PORTCbits.RC0
#define RC0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define RC0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define RC0_SetPullup()             do { WPUCbits.WPUC0 = 1; } while(0)
#define RC0_ResetPullup()           do { WPUCbits.WPUC0 = 0; } while(0)
#define RC0_SetAnalogMode()         do { ANSELCbits.ANSELC0 = 1; } while(0)
#define RC0_SetDigitalMode()        do { ANSELCbits.ANSELC0 = 0; } while(0)

// get/set CPU_WR_N aliases
#define CPU_WR_N_TRIS                 TRISCbits.TRISC1
#define CPU_WR_N_LAT                  LATCbits.LATC1
#define CPU_WR_N_PORT                 PORTCbits.RC1
#define CPU_WR_N_WPU                  WPUCbits.WPUC1
#define CPU_WR_N_OD                   ODCONCbits.ODCC1
#define CPU_WR_N_ANS                  ANSELCbits.ANSELC1
#define CPU_WR_N_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define CPU_WR_N_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define CPU_WR_N_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define CPU_WR_N_GetValue()           PORTCbits.RC1
#define CPU_WR_N_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define CPU_WR_N_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define CPU_WR_N_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define CPU_WR_N_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define CPU_WR_N_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define CPU_WR_N_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define CPU_WR_N_SetAnalogMode()      do { ANSELCbits.ANSELC1 = 1; } while(0)
#define CPU_WR_N_SetDigitalMode()     do { ANSELCbits.ANSELC1 = 0; } while(0)

// get/set CPU_RD_N aliases
#define CPU_RD_N_TRIS                 TRISCbits.TRISC2
#define CPU_RD_N_LAT                  LATCbits.LATC2
#define CPU_RD_N_PORT                 PORTCbits.RC2
#define CPU_RD_N_WPU                  WPUCbits.WPUC2
#define CPU_RD_N_OD                   ODCONCbits.ODCC2
#define CPU_RD_N_ANS                  ANSELCbits.ANSELC2
#define CPU_RD_N_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define CPU_RD_N_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define CPU_RD_N_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define CPU_RD_N_GetValue()           PORTCbits.RC2
#define CPU_RD_N_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define CPU_RD_N_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define CPU_RD_N_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define CPU_RD_N_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define CPU_RD_N_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define CPU_RD_N_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define CPU_RD_N_SetAnalogMode()      do { ANSELCbits.ANSELC2 = 1; } while(0)
#define CPU_RD_N_SetDigitalMode()     do { ANSELCbits.ANSELC2 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSELC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSELC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSELC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSELC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSELC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSELC5 = 0; } while(0)

// get/set RC6 procedures
#define RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define RC6_GetValue()              PORTCbits.RC6
#define RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define RC6_SetPullup()             do { WPUCbits.WPUC6 = 1; } while(0)
#define RC6_ResetPullup()           do { WPUCbits.WPUC6 = 0; } while(0)
#define RC6_SetAnalogMode()         do { ANSELCbits.ANSELC6 = 1; } while(0)
#define RC6_SetDigitalMode()        do { ANSELCbits.ANSELC6 = 0; } while(0)

// get/set UART_TX aliases
#define UART_TX_TRIS                 TRISCbits.TRISC7
#define UART_TX_LAT                  LATCbits.LATC7
#define UART_TX_PORT                 PORTCbits.RC7
#define UART_TX_WPU                  WPUCbits.WPUC7
#define UART_TX_OD                   ODCONCbits.ODCC7
#define UART_TX_ANS                  ANSELCbits.ANSELC7
#define UART_TX_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define UART_TX_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define UART_TX_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define UART_TX_GetValue()           PORTCbits.RC7
#define UART_TX_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define UART_TX_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define UART_TX_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define UART_TX_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define UART_TX_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define UART_TX_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define UART_TX_SetAnalogMode()      do { ANSELCbits.ANSELC7 = 1; } while(0)
#define UART_TX_SetDigitalMode()     do { ANSELCbits.ANSELC7 = 0; } while(0)

// get/set CPU_D0 aliases
#define CPU_D0_TRIS                 TRISDbits.TRISD0
#define CPU_D0_LAT                  LATDbits.LATD0
#define CPU_D0_PORT                 PORTDbits.RD0
#define CPU_D0_WPU                  WPUDbits.WPUD0
#define CPU_D0_OD                   ODCONDbits.ODCD0
#define CPU_D0_ANS                  ANSELDbits.ANSELD0
#define CPU_D0_SetHigh()            do { LATDbits.LATD0 = 1; } while(0)
#define CPU_D0_SetLow()             do { LATDbits.LATD0 = 0; } while(0)
#define CPU_D0_Toggle()             do { LATDbits.LATD0 = ~LATDbits.LATD0; } while(0)
#define CPU_D0_GetValue()           PORTDbits.RD0
#define CPU_D0_SetDigitalInput()    do { TRISDbits.TRISD0 = 1; } while(0)
#define CPU_D0_SetDigitalOutput()   do { TRISDbits.TRISD0 = 0; } while(0)
#define CPU_D0_SetPullup()          do { WPUDbits.WPUD0 = 1; } while(0)
#define CPU_D0_ResetPullup()        do { WPUDbits.WPUD0 = 0; } while(0)
#define CPU_D0_SetPushPull()        do { ODCONDbits.ODCD0 = 0; } while(0)
#define CPU_D0_SetOpenDrain()       do { ODCONDbits.ODCD0 = 1; } while(0)
#define CPU_D0_SetAnalogMode()      do { ANSELDbits.ANSELD0 = 1; } while(0)
#define CPU_D0_SetDigitalMode()     do { ANSELDbits.ANSELD0 = 0; } while(0)

// get/set CPU_D1 aliases
#define CPU_D1_TRIS                 TRISDbits.TRISD1
#define CPU_D1_LAT                  LATDbits.LATD1
#define CPU_D1_PORT                 PORTDbits.RD1
#define CPU_D1_WPU                  WPUDbits.WPUD1
#define CPU_D1_OD                   ODCONDbits.ODCD1
#define CPU_D1_ANS                  ANSELDbits.ANSELD1
#define CPU_D1_SetHigh()            do { LATDbits.LATD1 = 1; } while(0)
#define CPU_D1_SetLow()             do { LATDbits.LATD1 = 0; } while(0)
#define CPU_D1_Toggle()             do { LATDbits.LATD1 = ~LATDbits.LATD1; } while(0)
#define CPU_D1_GetValue()           PORTDbits.RD1
#define CPU_D1_SetDigitalInput()    do { TRISDbits.TRISD1 = 1; } while(0)
#define CPU_D1_SetDigitalOutput()   do { TRISDbits.TRISD1 = 0; } while(0)
#define CPU_D1_SetPullup()          do { WPUDbits.WPUD1 = 1; } while(0)
#define CPU_D1_ResetPullup()        do { WPUDbits.WPUD1 = 0; } while(0)
#define CPU_D1_SetPushPull()        do { ODCONDbits.ODCD1 = 0; } while(0)
#define CPU_D1_SetOpenDrain()       do { ODCONDbits.ODCD1 = 1; } while(0)
#define CPU_D1_SetAnalogMode()      do { ANSELDbits.ANSELD1 = 1; } while(0)
#define CPU_D1_SetDigitalMode()     do { ANSELDbits.ANSELD1 = 0; } while(0)

// get/set CPU_D2 aliases
#define CPU_D2_TRIS                 TRISDbits.TRISD2
#define CPU_D2_LAT                  LATDbits.LATD2
#define CPU_D2_PORT                 PORTDbits.RD2
#define CPU_D2_WPU                  WPUDbits.WPUD2
#define CPU_D2_OD                   ODCONDbits.ODCD2
#define CPU_D2_ANS                  ANSELDbits.ANSELD2
#define CPU_D2_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define CPU_D2_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define CPU_D2_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define CPU_D2_GetValue()           PORTDbits.RD2
#define CPU_D2_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define CPU_D2_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define CPU_D2_SetPullup()          do { WPUDbits.WPUD2 = 1; } while(0)
#define CPU_D2_ResetPullup()        do { WPUDbits.WPUD2 = 0; } while(0)
#define CPU_D2_SetPushPull()        do { ODCONDbits.ODCD2 = 0; } while(0)
#define CPU_D2_SetOpenDrain()       do { ODCONDbits.ODCD2 = 1; } while(0)
#define CPU_D2_SetAnalogMode()      do { ANSELDbits.ANSELD2 = 1; } while(0)
#define CPU_D2_SetDigitalMode()     do { ANSELDbits.ANSELD2 = 0; } while(0)

// get/set CPU_D3 aliases
#define CPU_D3_TRIS                 TRISDbits.TRISD3
#define CPU_D3_LAT                  LATDbits.LATD3
#define CPU_D3_PORT                 PORTDbits.RD3
#define CPU_D3_WPU                  WPUDbits.WPUD3
#define CPU_D3_OD                   ODCONDbits.ODCD3
#define CPU_D3_ANS                  ANSELDbits.ANSELD3
#define CPU_D3_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define CPU_D3_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define CPU_D3_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define CPU_D3_GetValue()           PORTDbits.RD3
#define CPU_D3_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define CPU_D3_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define CPU_D3_SetPullup()          do { WPUDbits.WPUD3 = 1; } while(0)
#define CPU_D3_ResetPullup()        do { WPUDbits.WPUD3 = 0; } while(0)
#define CPU_D3_SetPushPull()        do { ODCONDbits.ODCD3 = 0; } while(0)
#define CPU_D3_SetOpenDrain()       do { ODCONDbits.ODCD3 = 1; } while(0)
#define CPU_D3_SetAnalogMode()      do { ANSELDbits.ANSELD3 = 1; } while(0)
#define CPU_D3_SetDigitalMode()     do { ANSELDbits.ANSELD3 = 0; } while(0)

// get/set CPU_D4 aliases
#define CPU_D4_TRIS                 TRISDbits.TRISD4
#define CPU_D4_LAT                  LATDbits.LATD4
#define CPU_D4_PORT                 PORTDbits.RD4
#define CPU_D4_WPU                  WPUDbits.WPUD4
#define CPU_D4_OD                   ODCONDbits.ODCD4
#define CPU_D4_ANS                  ANSELDbits.ANSELD4
#define CPU_D4_SetHigh()            do { LATDbits.LATD4 = 1; } while(0)
#define CPU_D4_SetLow()             do { LATDbits.LATD4 = 0; } while(0)
#define CPU_D4_Toggle()             do { LATDbits.LATD4 = ~LATDbits.LATD4; } while(0)
#define CPU_D4_GetValue()           PORTDbits.RD4
#define CPU_D4_SetDigitalInput()    do { TRISDbits.TRISD4 = 1; } while(0)
#define CPU_D4_SetDigitalOutput()   do { TRISDbits.TRISD4 = 0; } while(0)
#define CPU_D4_SetPullup()          do { WPUDbits.WPUD4 = 1; } while(0)
#define CPU_D4_ResetPullup()        do { WPUDbits.WPUD4 = 0; } while(0)
#define CPU_D4_SetPushPull()        do { ODCONDbits.ODCD4 = 0; } while(0)
#define CPU_D4_SetOpenDrain()       do { ODCONDbits.ODCD4 = 1; } while(0)
#define CPU_D4_SetAnalogMode()      do { ANSELDbits.ANSELD4 = 1; } while(0)
#define CPU_D4_SetDigitalMode()     do { ANSELDbits.ANSELD4 = 0; } while(0)

// get/set CPU_D5 aliases
#define CPU_D5_TRIS                 TRISDbits.TRISD5
#define CPU_D5_LAT                  LATDbits.LATD5
#define CPU_D5_PORT                 PORTDbits.RD5
#define CPU_D5_WPU                  WPUDbits.WPUD5
#define CPU_D5_OD                   ODCONDbits.ODCD5
#define CPU_D5_ANS                  ANSELDbits.ANSELD5
#define CPU_D5_SetHigh()            do { LATDbits.LATD5 = 1; } while(0)
#define CPU_D5_SetLow()             do { LATDbits.LATD5 = 0; } while(0)
#define CPU_D5_Toggle()             do { LATDbits.LATD5 = ~LATDbits.LATD5; } while(0)
#define CPU_D5_GetValue()           PORTDbits.RD5
#define CPU_D5_SetDigitalInput()    do { TRISDbits.TRISD5 = 1; } while(0)
#define CPU_D5_SetDigitalOutput()   do { TRISDbits.TRISD5 = 0; } while(0)
#define CPU_D5_SetPullup()          do { WPUDbits.WPUD5 = 1; } while(0)
#define CPU_D5_ResetPullup()        do { WPUDbits.WPUD5 = 0; } while(0)
#define CPU_D5_SetPushPull()        do { ODCONDbits.ODCD5 = 0; } while(0)
#define CPU_D5_SetOpenDrain()       do { ODCONDbits.ODCD5 = 1; } while(0)
#define CPU_D5_SetAnalogMode()      do { ANSELDbits.ANSELD5 = 1; } while(0)
#define CPU_D5_SetDigitalMode()     do { ANSELDbits.ANSELD5 = 0; } while(0)

// get/set CPU_D6 aliases
#define CPU_D6_TRIS                 TRISDbits.TRISD6
#define CPU_D6_LAT                  LATDbits.LATD6
#define CPU_D6_PORT                 PORTDbits.RD6
#define CPU_D6_WPU                  WPUDbits.WPUD6
#define CPU_D6_OD                   ODCONDbits.ODCD6
#define CPU_D6_ANS                  ANSELDbits.ANSELD6
#define CPU_D6_SetHigh()            do { LATDbits.LATD6 = 1; } while(0)
#define CPU_D6_SetLow()             do { LATDbits.LATD6 = 0; } while(0)
#define CPU_D6_Toggle()             do { LATDbits.LATD6 = ~LATDbits.LATD6; } while(0)
#define CPU_D6_GetValue()           PORTDbits.RD6
#define CPU_D6_SetDigitalInput()    do { TRISDbits.TRISD6 = 1; } while(0)
#define CPU_D6_SetDigitalOutput()   do { TRISDbits.TRISD6 = 0; } while(0)
#define CPU_D6_SetPullup()          do { WPUDbits.WPUD6 = 1; } while(0)
#define CPU_D6_ResetPullup()        do { WPUDbits.WPUD6 = 0; } while(0)
#define CPU_D6_SetPushPull()        do { ODCONDbits.ODCD6 = 0; } while(0)
#define CPU_D6_SetOpenDrain()       do { ODCONDbits.ODCD6 = 1; } while(0)
#define CPU_D6_SetAnalogMode()      do { ANSELDbits.ANSELD6 = 1; } while(0)
#define CPU_D6_SetDigitalMode()     do { ANSELDbits.ANSELD6 = 0; } while(0)

// get/set CPU_D7 aliases
#define CPU_D7_TRIS                 TRISDbits.TRISD7
#define CPU_D7_LAT                  LATDbits.LATD7
#define CPU_D7_PORT                 PORTDbits.RD7
#define CPU_D7_WPU                  WPUDbits.WPUD7
#define CPU_D7_OD                   ODCONDbits.ODCD7
#define CPU_D7_ANS                  ANSELDbits.ANSELD7
#define CPU_D7_SetHigh()            do { LATDbits.LATD7 = 1; } while(0)
#define CPU_D7_SetLow()             do { LATDbits.LATD7 = 0; } while(0)
#define CPU_D7_Toggle()             do { LATDbits.LATD7 = ~LATDbits.LATD7; } while(0)
#define CPU_D7_GetValue()           PORTDbits.RD7
#define CPU_D7_SetDigitalInput()    do { TRISDbits.TRISD7 = 1; } while(0)
#define CPU_D7_SetDigitalOutput()   do { TRISDbits.TRISD7 = 0; } while(0)
#define CPU_D7_SetPullup()          do { WPUDbits.WPUD7 = 1; } while(0)
#define CPU_D7_ResetPullup()        do { WPUDbits.WPUD7 = 0; } while(0)
#define CPU_D7_SetPushPull()        do { ODCONDbits.ODCD7 = 0; } while(0)
#define CPU_D7_SetOpenDrain()       do { ODCONDbits.ODCD7 = 1; } while(0)
#define CPU_D7_SetAnalogMode()      do { ANSELDbits.ANSELD7 = 1; } while(0)
#define CPU_D7_SetDigitalMode()     do { ANSELDbits.ANSELD7 = 0; } while(0)

// get/set SDCard_CD aliases
#define SDCard_CD_TRIS                 TRISEbits.TRISE0
#define SDCard_CD_LAT                  LATEbits.LATE0
#define SDCard_CD_PORT                 PORTEbits.RE0
#define SDCard_CD_WPU                  WPUEbits.WPUE0
#define SDCard_CD_OD                   ODCONEbits.ODCE0
#define SDCard_CD_ANS                  ANSELEbits.ANSELE0
#define SDCard_CD_SetHigh()            do { LATEbits.LATE0 = 1; } while(0)
#define SDCard_CD_SetLow()             do { LATEbits.LATE0 = 0; } while(0)
#define SDCard_CD_Toggle()             do { LATEbits.LATE0 = ~LATEbits.LATE0; } while(0)
#define SDCard_CD_GetValue()           PORTEbits.RE0
#define SDCard_CD_SetDigitalInput()    do { TRISEbits.TRISE0 = 1; } while(0)
#define SDCard_CD_SetDigitalOutput()   do { TRISEbits.TRISE0 = 0; } while(0)
#define SDCard_CD_SetPullup()          do { WPUEbits.WPUE0 = 1; } while(0)
#define SDCard_CD_ResetPullup()        do { WPUEbits.WPUE0 = 0; } while(0)
#define SDCard_CD_SetPushPull()        do { ODCONEbits.ODCE0 = 0; } while(0)
#define SDCard_CD_SetOpenDrain()       do { ODCONEbits.ODCE0 = 1; } while(0)
#define SDCard_CD_SetAnalogMode()      do { ANSELEbits.ANSELE0 = 1; } while(0)
#define SDCard_CD_SetDigitalMode()     do { ANSELEbits.ANSELE0 = 0; } while(0)

// get/set SDCard_EN aliases
#define SDCard_EN_TRIS                 TRISEbits.TRISE1
#define SDCard_EN_LAT                  LATEbits.LATE1
#define SDCard_EN_PORT                 PORTEbits.RE1
#define SDCard_EN_WPU                  WPUEbits.WPUE1
#define SDCard_EN_OD                   ODCONEbits.ODCE1
#define SDCard_EN_ANS                  ANSELEbits.ANSELE1
#define SDCard_EN_SetHigh()            do { LATEbits.LATE1 = 1; } while(0)
#define SDCard_EN_SetLow()             do { LATEbits.LATE1 = 0; } while(0)
#define SDCard_EN_Toggle()             do { LATEbits.LATE1 = ~LATEbits.LATE1; } while(0)
#define SDCard_EN_GetValue()           PORTEbits.RE1
#define SDCard_EN_SetDigitalInput()    do { TRISEbits.TRISE1 = 1; } while(0)
#define SDCard_EN_SetDigitalOutput()   do { TRISEbits.TRISE1 = 0; } while(0)
#define SDCard_EN_SetPullup()          do { WPUEbits.WPUE1 = 1; } while(0)
#define SDCard_EN_ResetPullup()        do { WPUEbits.WPUE1 = 0; } while(0)
#define SDCard_EN_SetPushPull()        do { ODCONEbits.ODCE1 = 0; } while(0)
#define SDCard_EN_SetOpenDrain()       do { ODCONEbits.ODCE1 = 1; } while(0)
#define SDCard_EN_SetAnalogMode()      do { ANSELEbits.ANSELE1 = 1; } while(0)
#define SDCard_EN_SetDigitalMode()     do { ANSELEbits.ANSELE1 = 0; } while(0)

// get/set IO_RE2 aliases
#define IO_RE2_TRIS                 TRISEbits.TRISE2
#define IO_RE2_LAT                  LATEbits.LATE2
#define IO_RE2_PORT                 PORTEbits.RE2
#define IO_RE2_WPU                  WPUEbits.WPUE2
#define IO_RE2_OD                   ODCONEbits.ODCE2
#define IO_RE2_ANS                  ANSELEbits.ANSELE2
#define IO_RE2_SetHigh()            do { LATEbits.LATE2 = 1; } while(0)
#define IO_RE2_SetLow()             do { LATEbits.LATE2 = 0; } while(0)
#define IO_RE2_Toggle()             do { LATEbits.LATE2 = ~LATEbits.LATE2; } while(0)
#define IO_RE2_GetValue()           PORTEbits.RE2
#define IO_RE2_SetDigitalInput()    do { TRISEbits.TRISE2 = 1; } while(0)
#define IO_RE2_SetDigitalOutput()   do { TRISEbits.TRISE2 = 0; } while(0)
#define IO_RE2_SetPullup()          do { WPUEbits.WPUE2 = 1; } while(0)
#define IO_RE2_ResetPullup()        do { WPUEbits.WPUE2 = 0; } while(0)
#define IO_RE2_SetPushPull()        do { ODCONEbits.ODCE2 = 0; } while(0)
#define IO_RE2_SetOpenDrain()       do { ODCONEbits.ODCE2 = 1; } while(0)
#define IO_RE2_SetAnalogMode()      do { ANSELEbits.ANSELE2 = 1; } while(0)
#define IO_RE2_SetDigitalMode()     do { ANSELEbits.ANSELE2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);




#endif // PIN_MANAGER_H
/**
 End of File
*/