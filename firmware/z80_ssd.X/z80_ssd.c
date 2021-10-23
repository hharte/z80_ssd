/*************************************************************************
 *                                                                       *
 * Copyright (c) 2021 Howard M. Harte                                    *
 * https://github.com/hharte                                             *
 *                                                                       *
 * Module Description:                                                   *
 *                                                                       *
 * MPLAB-X IDE v5.50                                                     *
 * MPLAB Code Configurator v5.2.4                                        *
 *                                                                       *
 * com.microchip.mcc.mcu8.Mcu8PeripheralLibrary v1.81.7                  *
 * com.microchip.mcc.sdcard.SDCardLibrary v1.1.0                         *
 * com.microchip.mcc.fatfs.FatFsLibrary v1.1.0                           *
 * com.microchip.mcc.foundationservices.library.FoundationServicesLibrary v0.2.2
 *************************************************************************/

#include  <ctype.h>
#include  <stdio.h>
#include  <string.h>
#include  <stdint.h>
#include "mcc_generated_files/mcc.h"

#define CPU_RESET_N         PORTBbits.RB0
#define CLEAR_WAIT          PORTBbits.RB1
#define CPU_IORQ_N          PORTBbits.RB3
#define CPU_WAIT_N          PORTCbits.RC0
#define CPU_WR_N            PORTCbits.RC1
#define CPU_RD_N            PORTCbits.RC2
#define SDCARD_EN           PORTEbits.RE1

volatile bool do_command_flag = 0;

static uint8_t cpu_addr;
static uint8_t cpu_data;
static uint8_t cpu_rd;
static uint8_t cpu_wr;

extern void IBC_HDC_Hard_Reset(void);
extern void IBC_HDC_Reset(void);
extern uint8_t IBC_HDC_Write(const uint8_t Addr, uint8_t cData);
extern uint8_t IBC_HDC_Read(const uint8_t Addr);
extern uint8_t IBC_HDC_doCommand(void);

extern uint8_t   sectbuf[];
volatile extern uint16_t  secbuf_index;

void CPU_RESET_ISR(void)
{
    TRISBbits.TRISB1 = 0; /* Configure CLEAR_WAIT as output */

    TRISA = 0xFF;       /* CPU Address inputs */
    TRISD = 0xFF;       /* CPU Data inputs for now */

    /* Make sure the WAIT# flip flop in CLC2 is clear. */
    CLEAR_WAIT = 0;
    CLEAR_WAIT = 1;

    SDCARD_EN = 1;

    IBC_HDC_Hard_Reset();
}

/* CLC2 Interrupt Handler - WAIT#
 *
 * When an I/O access matches the disk controller's address (0x40-0x4F,)
 * CLC2's flip flop is triggered, asserting WAIT# to the Z80, and triggers
 * this interrupt.
 *
 * This interrupt handler enables a 74HCT245 data bus buffer (is this really
 * needed?) and then reads the address, RD#/WR#, and data bus.
 *
 * I/O to the FIFO is handled directly in the ISR, as it is the most critical
 * for disk controller performance.  Other I/O is handled by the ibc_disk_ctrl
 * module.
 *
 * The timing of the ISR is fairly critical, as holding WAIT# for a very long
 * time can kill the DRAM refresh.
 *
 * Disk controller commands are carried out in the z80_ssd_main() while(1)
 * loop.  These are generally not timing critical, as the disk controller driver
 * will poll the status register to determine when the controller is ready.
 */
void __interrupt(irq(CLC2),base(8)) CLC2_ISR()
{
    cpu_rd = CPU_RD_N;
    /* We don't really need WR#, so save some time by not reading it. */
//    cpu_wr = CPU_WR_N;

    cpu_addr = PORTA;
    
    if (!cpu_rd) {  /* CPU I/O Read (2uS) */
        TRISD = 0x00;    // Data bus is output.

        if (cpu_addr == 0x48) { /* Handle the FIFO as quickly as possible. */
            cpu_data = sectbuf[secbuf_index++];
        } else { /* All other registers */
            cpu_data = IBC_HDC_Read(cpu_addr);
        }
        PORTD = cpu_data;
    } else {  /* CPU I/O Write (1.75uS) */
        cpu_data = PORTD;
        if (cpu_addr == 0x48) { /* Handle the FIFO as quickly as possible. */
            sectbuf[secbuf_index++] = cpu_data;
        } else { /* All other registers */
            IBC_HDC_Write(cpu_addr, cpu_data);
        }
    }

    /* Clear the CLC interrupt flag, before releasing WAIT#.  The order is
     * important!
     */
    PIR6bits.CLC2IF = 0;
    
    /* De-assert WAIT# */
    CLEAR_WAIT = 0;
    CLEAR_WAIT = 1;

    /* Tri-state MCU Port D (Data Bus port) */
    TRISD = 0xFF;       // Data bus is input.
}

void z80_ssd_main(void)
{
    CPU_RESET_ISR();

    /* Delay to allow the power supply to stabilize before writing to UART */
    for (volatile uint32_t i = 0; i < 10000; i++);

    puts("\x1b[2J\x1b[HIBC/Integrated Business Computers Solid-State Disk v1.0\n\r" \
         "(c) 2021 Howard M. Harte - github.com/hharte/z80_ssd\n\r");

    printf("Controller ready.\n\r");
    
    INT0_SetInterruptHandler (CPU_RESET_ISR);
    
    while (1)
    {
        if (do_command_flag == 1) {
            IBC_HDC_doCommand();
            do_command_flag = 0;
        }
    }
}
