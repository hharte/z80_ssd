

# z80_ssd: Z-80 Solid-State Drive


## Introduction

This project implements a solid-state disk controller for the Z80.  The board plugs into the Z80 CPU socket and the Z80 CPU plugs into the board.  A [Microchip PIC18F47Q43](https://www.microchip.com/en-us/product/PIC18F47Q43) microcontroller implements the controller and SD Memory card interface using SPI.

While the z80_ssd could implement almost any hard disk controller that uses I/O ports for data transfer, the particular controller implemented mimics the IBC/Integrated Business Computers MCC Hard Disk Controller.

The original controller supports four ST-506 drives.  Drive 0 is the boot drive, and Drive 3 is a 5- or 10MB removable cartridge drive.  The other two drives were unused in the standard [IBC MultiStar](https://github.com/hharte/integrated-business-computers/tree/master/MultiStar) computer.

![alt_text](https://raw.githubusercontent.com/hharte/z80_ssd/master/doc/z80_ssd.jpg "image_tooltip")


## Architecture


### I/O Access Handling

The z80_ssd piggybacks on the Z80 CPU socket to gain access to all of the Z80 CPU’s signals.  The PIC18F47Q43 was chosen because it has a relatively large amount of RAM (8K) and FLASH (128K.)  To minimize the number of components required, and to facilitate maximum flexibility, the MCU’s Configurable Logic Cells (CLCs) are used:

CLC1 - Decodes CPU_A[7:4] to allow the z80_ssd to respond to a block of 16 I/O addresses.  The current design uses one 4-input AND gate to decode address 40h-4Fh, like the original disk controller.  There are three spare 4-input AND gates in CLC1, so the design could be expanded to decode up to four blocks of 16 I/O ports if desired.

This schematic diagram illustrates three address ranges decoded by the z80_ssd: 40h-4Fh, 0C0h-0CFh, 0D0h-0DFh.

![alt_text](https://raw.githubusercontent.com/hharte/z80_ssd/master/doc/IBC_MCC_HDC_CLC1.png "image_tooltip")

CLC2 - Uses the output of CLC1 along with CPU_M1# and CPU_IORQ# to set a flip-flop when the requested I/O access is performed by the CPU.  The output of this flip-flop pulls down the CPU_WAIT# pin via an open-collector output from the MCU.  CLC2 generates an interrupt to the MCU, and MCU then processes the I/O read or write.  After the MCU finishes processing the I/O access, it de-asserts WAIT# by resetting the flip-flop in CLC2.

![alt_text](https://raw.githubusercontent.com/hharte/z80_ssd/master/doc/IBC_MCC_HDC_CLC2.png "image_tooltip")

CLC3 - Although not strictly required, the z80_ssd employs a 74ABTH245 bus transceiver for the CPU data bus to ensure proper timing.  The MCU’s CLC3 drives the bus transceiver’s output enable.

![alt_text](https://raw.githubusercontent.com/hharte/z80_ssd/master/doc/IBC_MCC_HDC_CLC3.png "image_tooltip")

Due to the piggyback nature of the z80_ssd, it is fabricated on a 0.4mm thick PCB, and uses a machined Mill-Max long-pin DIP socket.  To raise the z80_ssd above other components on the computer’s motherboard, the long-pin DIP is plugged into a stamped 40-pin DIP socket which is then inserted into the original Z80 CPU socket.


### SD Memory Card

The SD memory card is connected to the MCU’s SPI interface.  It uses the [FatFs library](http://elm-chan.org/fsw/ff/00index_e.html) and Microchip’s SD-SPI library.  The activity LED on the z80_ssd is driven by the SD memory card’s CS# pin.

The SPI clock runs at 8MHz, and is in polled mode.  It may be possible to increase the throughput by using interrupt-driven DMA mode, but I have not tried that.

Running OASIS 5.6, a 16MB disk partition can be verified (read) in 3 minutes, 35 seconds.  While the I/O interface is much slower than the hardware-driven FIFO of the original disk controller design, the overall performance feels about the same: solid-state disks do not have seek or rotational latency overhead, which makes these aspects of the disk faster than the original.


```
>HDPERF

>SHOW TIME
05:33:00 Friday, October 22, 1993

>VERIFY S

Cylinder: 132 Head: 14

>SHOW TIME
05:36:33 Friday, October 22, 1993

D(8) Label: "REMOVBKU",
     Archived from disk "HOWARD1 " on 10/23/83 14:13,
     Capacity: 9,744K bytes (609-2-32),
     Available: 0K bytes (0%),
     Largest area: 0K bytes,
     1 file in use (out of 16).

S(3) Label: "HOWARD1 ",
     Archived to disk "REMOVBKU" on 10/23/83 14:13,
     Capacity: 15,960K bytes (133-15-32),
     Available: 14,884K bytes (93%),
     Largest area: 14,879K bytes,
     188 files in use (out of 1,944).
```



### Debugging Facilities

The z80_ssd includes a 5V TTL UART for console I/O as well as a standard Microchip ICSP port on a 1x6 0.1” header.

Jumper JP1 can be removed to block CPU_WAIT# from being asserted.  This can be useful for debugging.  JP1 should be installed for normal operation.


## Other Uses

The z80_ssd hardware and MCU can be used to implement other types of I/O devices or different kinds of disk controllers.  One thing to be aware of is that **_no other hardware in the system should drive the bus when the z80_ssd registers are accessed_**.  For use in an S-100 bus system, additional logic would be needed to prevent the bus drivers on the S-100 board from driving against the z80_ssd.  In the IBC MultiStar machine where I use the z80_ssd, I had to disable the on-board ST-506 controller.  This was accomplished by removing the PAL that does the address decoding for the disk controller, tying one of the inputs inactive, and then placing the PAL back into the system.
