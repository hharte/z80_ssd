 /**
   CLC2 Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     clc2.c
 
   @Summary
     This is the generated driver implementation file for the CLC2 driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for CLC2.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
         Device            :  PIC18F47Q43
         Driver Version    :  1.0.0
     The generated drivers are tested against the following:
         Compiler          :  XC8 2.31 and above or later
         MPLAB             :  MPLAB X 5.45
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
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include "clc2.h"
#include "interrupt_manager.h"

/**
  Section: CLC2 APIs
*/

void CLC2_Initialize(void)
{
    // Set the CLC2 to the options selected in the User Interface
    
    // SLCT 1; 
    CLCSELECT = 0x01;
    // G1POL inverted; G2POL inverted; G3POL not_inverted; G4POL not_inverted; POL not_inverted; 
    CLCnPOL = 0x03;
    // D1S CLCIN2 (CLCIN2PPS); 
    CLCnSEL0 = 0x02;
    // D2S CLC1_OUT; 
    CLCnSEL1 = 0x33;
    // D3S CLCIN6 (CLCIN6PPS); 
    CLCnSEL2 = 0x06;
    // D4S CLCIN7 (CLCIN7PPS); 
    CLCnSEL3 = 0x07;
    // G1D3N enabled; G1D2N disabled; G1D4N disabled; G1D1T enabled; G1D3T disabled; G1D2T disabled; G1D4T disabled; G1D1N disabled; 
    CLCnGLS0 = 0x12;
    // G2D2N disabled; G2D1N disabled; G2D4N disabled; G2D3N enabled; G2D2T enabled; G2D1T disabled; G2D4T disabled; G2D3T disabled; 
    CLCnGLS1 = 0x18;
    // G3D1N disabled; G3D2N disabled; G3D3N disabled; G3D4N disabled; G3D1T disabled; G3D2T disabled; G3D3T disabled; G3D4T disabled; 
    CLCnGLS2 = 0x00;
    // G4D1N disabled; G4D2N disabled; G4D3N disabled; G4D4N disabled; G4D1T disabled; G4D2T disabled; G4D3T disabled; G4D4N enabled; 
    CLCnGLS3 = 0x40;
    // CLC2OUT 0; 
    CLCDATA = 0x00;
    // EN enabled; INTN enabled; INTP disabled; MODE 1-input D flip-flop with S and R; 
    CLCnCON = 0x8C;

    // Clear the CLC interrupt flag
    PIR6bits.CLC2IF = 0;
    // Enabling CLC2 interrupt.
    PIE6bits.CLC2IE = 1;
}

#if 0
void __interrupt(irq(CLC2),base(8)) CLC2_ISR()
{
    // Clear the CLC interrupt flag
    PIR6bits.CLC2IF = 0;
}
#endif
bool CLC2_OutputStatusGet(void)
{
    return(CLCDATAbits.CLC2OUT);
}
/**
 End of File
*/
