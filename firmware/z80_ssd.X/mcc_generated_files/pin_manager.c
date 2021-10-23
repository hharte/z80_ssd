/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F47Q43
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB             :  MPLAB X 5.45

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.
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

#include "pin_manager.h"





void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x01;

    /**
    TRISx registers
    */
    TRISE = 0x01;
    TRISA = 0xFF;
    TRISB = 0xCF;
    TRISC = 0x96;
    TRISD = 0xFF;

    /**
    ANSELx registers
    */
    ANSELD = 0x00;
    ANSELC = 0x00;
    ANSELB = 0xC0;
    ANSELE = 0x00;
    ANSELA = 0x00;

    /**
    WPUx registers
    */
    WPUD = 0x00;
    WPUE = 0x01;
    WPUB = 0x04;
    WPUA = 0x00;
    WPUC = 0x01;

    /**
    RxyI2C registers
    */
    RB1I2C = 0x00;
    RB2I2C = 0x00;
    RC3I2C = 0x00;
    RC4I2C = 0x00;

    /**
    ODx registers
    */
    ODCONE = 0x00;
    ODCONA = 0x00;
    ODCONB = 0x00;
    ODCONC = 0x01;
    ODCOND = 0x00;

    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x07;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0x0F;





   
    
	
    CLCIN7PPS = 0x09;   //RB1->CLC1:CLCIN7;    
    RC0PPS = 0x02;   //RC0->CLC2:CLC2;    
    RC3PPS = 0x31;   //RC3->SPI1:SCK1;    
    INT0PPS = 0x08;   //RB0->EXT_INT:INT0;    
    CLCIN6PPS = 0x0A;   //RB2->CLC1:CLCIN6;    
    CLCIN4PPS = 0x06;   //RA6->CLC1:CLCIN4;    
    CLCIN5PPS = 0x07;   //RA7->CLC1:CLCIN5;    
    RB4PPS = 0x03;   //RB4->CLC3:CLC3;    
    U1RXPPS = 0x17;   //RC7->UART1:RX1;    
    SPI1SCKPPS = 0x13;   //RC3->SPI1:SCK1;    
    CLCIN0PPS = 0x04;   //RA4->CLC3:CLCIN0;    
    CLCIN2PPS = 0x0B;   //RB3->CLC3:CLCIN2;    
    CLCIN1PPS = 0x05;   //RA5->CLC3:CLCIN1;    
    RC5PPS = 0x32;   //RC5->SPI1:SDO1;    
    RC6PPS = 0x20;   //RC6->UART1:TX1;    
    SPI1SDIPPS = 0x14;   //RC4->SPI1:SDI1;    
}
  
void PIN_MANAGER_IOC(void)
{   
}

/**
 End of File
*/