/*************************************************************************
 *                                                                       *
 * Copyright (c) 2021 Howard M. Harte                                    *
 * https://github.com/hharte                                             *
 *                                                                       *
 * Module Description:                                                   *
 *     IBC/Integrated Business Computers MCC ST-506 Hard Disk Controller *
 * Emulation for the Z80 SSD.                                            *
 *                                                                       *
 * WARNING!!!!!!                                                         *
 * =============                                                         *
 * Before installing this board, the built-in controller's address       *
 * decoder needs to be disabled in order to free up I/O ports 0x40-0x4F. *
 * To do this, remove the PAL12L6 (marked DMP020) from the disk          *
 * controller board (location J-13.)  Use a 20-pin IC socket (stamped    *
 * pins, not machined) and bend out pin 1 (CPU_IORD#) from the socket.   *
 * Use a short length of 30ga wire to connect this pin 1 to pin 20 (VCC) *
 * in order to tie the PAL's IORD# input high.  Plug the PAL into this   *
 * socket, and then plug the socket into J-13.  Make sure to insulate    *
 * properly so as not to short out the disk controller board's IORQ      *
 * line.                                                                 *
 *                                                                       *
 * Performance:                                                          *
 * With debug printing disabled, the OASIS 5.6 VERIFY command can        *
 * verify the 16MB S partition in less than four minutes.  With          *
 * debug printing enabled, this slows to 6 minutes.                      *
*                                                                       *
 * MPLAB-X IDE v5.50                                                     *
 * MPLAB Code Configurator v5.2.4                                        *
 *************************************************************************/

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "mcc_generated_files/mcc.h"

/* Debug flags */
#define DEBUG_INFO      (1 << 0)
#define DEBUG_READ      (1 << 1)
#define DEBUG_WRITE     (1 << 2)
#define DEBUG_FORMAT    (1 << 3)
#define DEBUG_REGWR     (1 << 4)
#define DEBUG_REGRD     (1 << 5)
#define DEBUG_FIFO      (1 << 6)
#define DEBUG_ERROR     (1 << 7)

#define DEBUG
uint8_t debug = (DEBUG_ERROR);// | DEBUG_INFO | DEBUG_REGWR | DEBUG_READ | DEBUG_WRITE | DEBUG_FORMAT);
#ifdef DEBUG
#define debug_print(dbglevel, x) do { if (debug & dbglevel) printf x; } while (0)
#else
#define debug_print(dbglevel, x) {}
#endif

#define IBC_HDC_MAX_DRIVES          4       /* Maximum number of drives supported */
#define IBC_HDC_MAX_SECLEN          256     /* Maximum of 256 bytes per sector */
#define IBC_HDC_FORMAT_FILL_BYTE    0xe5    /* Real controller uses 0, but we
                                               choose 0xe5 so the disk shows
                                               up as blank under CP/M. */
#define IBC_HDC_FORMAT_CHUNK_LEN    2048
#define IBC_HDC_MAX_CYLS            1024
#define IBC_HDC_MAX_HEADS           16
#define IBC_HDC_MAX_SPT             256

#define DEV_NAME    "IBCHDC"

/* Task File Register Offsets */
#define TF_CSEC     0
#define TF_HEAD     1
#define TF_NSEC     2
#define TF_SA3      3
#define TF_CMD      4
#define TF_DRIVE    5
#define TF_TRKL     6
#define TF_TRKH     7
#define TF_FIFO     8

#define IBC_HDC_STATUS_BUSY         (1 << 7)
#define IBC_HDC_STATUS_READY        (1 << 6)
#define IBC_HDC_STATUS_WRITE_FAULT  (1 << 5)
#define IBC_HDC_STATUS_SEEK_COMPL   (1 << 4)
#define IBC_HDC_STATUS_DRQ          (1 << 3)
#define IBC_HDC_STATUS_ERROR        (1 << 0)

#define IBC_HDC_ERROR_ID_NOT_FOUND  (1 << 4)

#define IBC_HDC_CMD_RESET           0x00
#define IBC_HDC_CMD_READ_SECT       0x01
#define IBC_HDC_CMD_WRITE_SECT      0x02
#define IBC_HDC_CMD_FORMAT_TRK      0x08
#define IBC_HDC_CMD_ACCESS_FIFO     0x0b
#define IBC_HDC_CMD_READ_PARAMETERS 0x10

#define IBC_HDC_REG_STATUS          0x40
#define IBC_HDC_REG_FIFO_STATUS     0x44
#define IBC_HDC_REG_FIFO            0x48
#define IBC_HDC_TEST_LOOPBACK       0x4c
#define IBC_HDC_TEST_INCR           0x4d

#define SCPE_OK						(0)
#define SCPE_IOERR					(-1)

typedef struct {
    uint8_t  readonly;    /* Drive is read-only? */
    uint16_t sectsize;    /* sector size */
    uint16_t nsectors;    /* number of sectors/track */
    uint16_t nheads;      /* number of heads */
    uint16_t ncyls;       /* number of cylinders */
    uint16_t cur_cyl;     /* Current cylinder */
    uint8_t  cur_head;    /* Current Head */
    uint8_t  cur_sect;    /* current starting sector of transfer */
    uint16_t cur_sectsize;/* Current sector size in SA6 register */
    uint16_t xfr_nsects;  /* Number of sectors to transfer */
    uint8_t ready;        /* Is drive ready? */
} IBC_HDC_DRIVE_INFO;

typedef struct {
    uint8_t   sel_drive;  /* Currently selected drive */
    uint8_t   reg_temp_holding[4];
    uint8_t   taskfile[9]; /* ATA Task File Registers */
    volatile uint8_t   status_reg; /* IBC Disk Slave Status Register */
    uint8_t   ndrives;    /* Number of drives attached to the controller */
    IBC_HDC_DRIVE_INFO drive[IBC_HDC_MAX_DRIVES];
} IBC_HDC_INFO;

const char *disk_filenames[4] = {
    "IBCDISK0.dsk",
    "IBCDISK1.dsk",
    "IBCDISK2.dsk",
    "IBCDISK3.dsk",
};

static IBC_HDC_INFO ibc_hdc_info_data = { 0x0 };
static IBC_HDC_INFO *ibc_hdc_info = &ibc_hdc_info_data;

uint8_t   sectbuf[IBC_HDC_MAX_SECLEN*10];
#ifdef DEBUG
static uint8_t test_reg = 0;
#endif /* DEBUG */
volatile uint16_t  secbuf_index;
static uint16_t xfr_len;
static uint32_t file_offset;

uint8_t IBC_HDC_Read(const uint8_t Addr);
uint8_t IBC_HDC_Write(const uint8_t Addr, uint8_t cData);
uint8_t IBC_HDC_doCommand(void);

#define IBC_HDC_NAME    "IBC MCC ST-506 Hard Disk Controller"

volatile extern bool do_command_flag;

static FATFS drive;
static FIL file[IBC_HDC_MAX_DRIVES];
static uint16_t actualLength;

//#define SDTEST
#ifdef SDTEST
#undef  DISK0_FILENAME
#define DISK0_FILENAME  "8mbtest.dsk"
static FIL ofile;
static uint16_t writeLength;
static uint32_t seek_offset;
#endif /* SDTEST */

void IBC_HDC_Hard_Reset(void)
{
    ibc_hdc_info->taskfile[TF_CMD] = 0;
    debug_print(DEBUG_INFO, ("Hard Reset.\n\r"));
}

void IBC_HDC_Reset(void)
{
    char VolLabel[12];
    uint32_t sn;
    
    memset(ibc_hdc_info, 0, sizeof(IBC_HDC_INFO));
    ibc_hdc_info->ndrives = IBC_HDC_MAX_DRIVES;
    do_command_flag = 0;

    ibc_hdc_info->drive[0].ncyls = 680;
    ibc_hdc_info->drive[0].nheads = 15;
    ibc_hdc_info->drive[0].nsectors = 32;
    ibc_hdc_info->drive[0].sectsize = 256;

    ibc_hdc_info->drive[1].ncyls = 615;
    ibc_hdc_info->drive[1].nheads = 4;
    ibc_hdc_info->drive[1].nsectors = 32;
    ibc_hdc_info->drive[1].sectsize = 256;

    ibc_hdc_info->drive[2].ncyls = 615;
    ibc_hdc_info->drive[2].nheads = 4;
    ibc_hdc_info->drive[2].nsectors = 32;
    ibc_hdc_info->drive[2].sectsize = 256;

    ibc_hdc_info->drive[3].ncyls = 612;
    ibc_hdc_info->drive[3].nheads = 2;
    ibc_hdc_info->drive[3].nsectors = 32;
    ibc_hdc_info->drive[3].sectsize = 256;

    if (SD_SPI_IsMediaPresent() == false)
    {
        puts("Error, no media in sdcard slot.\n\r");
        ibc_hdc_info->status_reg |= IBC_HDC_STATUS_ERROR;
        return;
    }

    if (f_close(&file[0]) == FR_OK) {
        printf("Closed %s\n\r", disk_filenames[0]);
    }

    if (f_close(&file[3]) == FR_OK) {
        printf("Closed %s\n\r", disk_filenames[3]);
    }

    if (f_unmount("0:") == FR_OK)
    {
    }

    if (f_mount(&drive,"0:",1) == FR_OK)
    {
        /* Get volume label of the default drive */
        f_getlabel("", VolLabel, &sn);

        printf("Volume Label: %s\nSerial number: %08lX\n\r", VolLabel, sn);

        if (f_open(&file[0], disk_filenames[0], FA_READ | FA_WRITE) == FR_OK)
        {
            printf("Opened %s.\n\r", disk_filenames[0]);

#ifdef SDTEST
            if (f_open(&ofile, "filecopy.bin", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
            {
                printf("Created output file.\n\r");

                seek_offset = 0;
                /* Copy source to destination */
                for (;;) {
                    f_read(&file[ibc_hdc_info->sel_drive], sectbuf, sizeof(sectbuf), &actualLength); /* Read a chunk of data from the source file */
                    printf("R[%05lu]\n\r", seek_offset);
                    if (actualLength == 0) {
                        printf("Error reading.\n\r");
                        break; /* error or eof */
                    }
                    f_lseek(&ofile, seek_offset);
                    seek_offset += actualLength;
                    f_write(&ofile, sectbuf, actualLength, &writeLength);           /* Write it to the destination file */
                    putchar('W');
                    if (writeLength < actualLength) {
                        printf("Error writing %d bytes.\n\r", actualLength);
                        break; /* error or disk full */
                    }
                }

                /* Close open files */
                f_close(&file[ibc_hdc_info->sel_drive]);
                f_close(&ofile);
                f_unmount("0:");
                printf("File copy complete.\n\r");
                while(1);
            }
#endif /* SDTEST */
        } else {
            printf("Could not open %s\n\r", disk_filenames[0]);
            ibc_hdc_info->status_reg |= IBC_HDC_STATUS_ERROR;
        }

        if (f_open(&file[3], disk_filenames[3], FA_OPEN_ALWAYS | FA_READ | FA_WRITE) == FR_OK)
        {
            printf("Opened %s.\n\r", disk_filenames[3]);
        } else {
            printf("Could not open %s\n\r", disk_filenames[3]);
            ibc_hdc_info->status_reg |= IBC_HDC_STATUS_ERROR;
        }
    } else {
        printf("Mount SD card failed.\n\r");
    }

    puts("IBC SSD: Reset Complete.\n\r");
}

/* I/O Write to IBC Disk Slave Task File */
uint8_t IBC_HDC_Write(const uint8_t Addr, uint8_t cData)
{
    IBC_HDC_DRIVE_INFO *pDrive;

    pDrive = &ibc_hdc_info->drive[ibc_hdc_info->sel_drive];

#ifdef DEBUG
    INTERRUPT_GlobalInterruptHighDisable();
    debug_print(DEBUG_REGWR, ("WR:%02x=%02x\n\r", Addr, cData));
    INTERRUPT_GlobalInterruptHighEnable();
#endif /* DEBUG */

    switch(Addr) {
    case 0x40:
        ibc_hdc_info->reg_temp_holding[0] = cData;
        if (cData & 0x80) {
            ibc_hdc_info->taskfile[TF_CMD] = ibc_hdc_info->reg_temp_holding[0];
            ibc_hdc_info->taskfile[TF_DRIVE] = ibc_hdc_info->reg_temp_holding[1];
            ibc_hdc_info->taskfile[TF_TRKL] = ibc_hdc_info->reg_temp_holding[2];
            ibc_hdc_info->taskfile[TF_TRKH] = ibc_hdc_info->reg_temp_holding[3];
            if ((ibc_hdc_info->taskfile[TF_CMD] & 0x80) != IBC_HDC_CMD_READ_PARAMETERS) {
                ibc_hdc_info->sel_drive = ibc_hdc_info->taskfile[TF_DRIVE] & 0x03;
            }
            ibc_hdc_info->status_reg = 0x30;
        }
        else {
            ibc_hdc_info->taskfile[TF_CSEC] = ibc_hdc_info->reg_temp_holding[0];
            ibc_hdc_info->taskfile[TF_HEAD] = ibc_hdc_info->reg_temp_holding[1];
            ibc_hdc_info->taskfile[TF_NSEC] = ibc_hdc_info->reg_temp_holding[2];
            ibc_hdc_info->taskfile[TF_SA3] = ibc_hdc_info->reg_temp_holding[3];
            ibc_hdc_info->status_reg = 0x20;
            if (do_command_flag == 1) {
                /* Ignore multiple resets as the front panel reset switch
                 * generates more than one.
                 */
                if (ibc_hdc_info->taskfile[TF_CMD] != IBC_HDC_CMD_RESET) {
                    printf("ERROR: command already in progress.\n\r");
                }
            } else {
                ibc_hdc_info->status_reg = 0x10;    /* HDC is busy */
                do_command_flag = 1;
            }
        }
        break;
        /* Fall through */
    case 0x41:
    case 0x42:
    case 0x43:
        ibc_hdc_info->reg_temp_holding[Addr & 0x03] = cData;
        break;
    case IBC_HDC_REG_FIFO_STATUS:
        secbuf_index = 0;
        break;
    case IBC_HDC_REG_FIFO:
        sectbuf[secbuf_index++] = cData;
        break;
#ifdef DEBUG
    case IBC_HDC_TEST_LOOPBACK:
        test_reg = cData;
        printf("TEST: Write 0x%02x\n\r", cData);
        break;
    case IBC_HDC_TEST_INCR:
        test_reg = cData;
        printf("TEST: Write (incr) 0x%02x\n\r", cData);
        break;
#endif /* DEBUG */
    default:
        debug_print(DEBUG_ERROR, ("Unhandled WR:%02x=%02x\n\r", Addr, cData));
        break;
    }

    return 0;
}


/* I/O Read from IBC Disk Slave Task File */
uint8_t IBC_HDC_Read(const uint8_t Addr)
{
    IBC_HDC_DRIVE_INFO* pDrive;
    uint8_t cData = 0xFF;

    pDrive = &ibc_hdc_info->drive[ibc_hdc_info->sel_drive];

    switch (Addr) {
    case IBC_HDC_REG_STATUS:
        cData = ibc_hdc_info->status_reg;
        debug_print(DEBUG_REGRD, ("RD STATUS=0x%02x\n\r", cData));
        break;
    case IBC_HDC_REG_FIFO:
        cData = sectbuf[secbuf_index];

        debug_print(DEBUG_FIFO, ("RD FIFO[%02x]=0x%02x\n\r", secbuf_index, cData));
        secbuf_index++;
        break;
    case IBC_HDC_REG_FIFO_STATUS:
        break;
#ifdef DEBUG
    case IBC_HDC_TEST_LOOPBACK:
        cData = test_reg;
        printf("TEST: Read 0x%02x\n\r", cData);
        break;
    case IBC_HDC_TEST_INCR:
        cData = ++test_reg;
        printf("TEST: Read (incr) 0x%02x\n\r", cData);
        break;
#endif /* DEBUG */
    default:
        debug_print(DEBUG_ERROR, ("Unhandled RD 0x%02x=0x%02x\n\r", Addr, cData));
        break;
    }
    return (cData);
}

/* Validate that Cyl, Head, Sector, Sector Length are valid for the current
 * disk drive geometry.
 */
static int IBC_HDC_Validate_CHSN(IBC_HDC_DRIVE_INFO* pDrive)
{
    int status = SCPE_OK;

    /* Check to make sure we're operating on a valid C/H/S/N. */
    if ((pDrive->cur_cyl >= pDrive->ncyls) ||
        (pDrive->cur_head >= pDrive->nheads) ||
        (pDrive->cur_sect >= pDrive->nsectors) ||
        (pDrive->cur_sectsize != pDrive->sectsize))
    {
        /* Set error bit in status register. */
        ibc_hdc_info->status_reg |= IBC_HDC_STATUS_ERROR;

        printf("Drive %d: C:%d/H:%d/S:%d/N:%d: ID Not Found (check disk geometry.)\n\r",
            ibc_hdc_info->sel_drive,
            pDrive->cur_cyl,
            pDrive->cur_head,
            pDrive->cur_sect,
            pDrive->cur_sectsize);

        status = SCPE_IOERR;
    }
    else {
        /* Clear ID_NOT_FOUND bit in error register. */
        ibc_hdc_info->status_reg &= ~IBC_HDC_STATUS_ERROR;
    }

    return (status);
}


/* 85MB Fixed Disk Drive 0: C:680/H:15/N:32/L:256
 * 10MB Removable Cartridge Drive 3: C:612/H:2/N:32/L:256
 */
unsigned char HDParameters[108] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x00
    0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00,   // 0x08 0088=136
    0x00, 0x10, 0x01, 0x00, 0x00, 0x98, 0x01, 0x00,   // 0x10 0110=272, 0198=408
    0x00, 0x20, 0x02, 0x00, 0x03, 0x00, 0x00, 0x00,   // 0x18 0220=544
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x61, 0x62,   // 0x20
    0x20, 0x00, 0x61, 0x02, 0x02, 0x00, 0x00, 0x00,   // 0x28
    0x0F, 0x00, 0x88, 0x00, 0x20, 0x00, 0x1D, 0x03,   // 0x30=#heads
    0x0F, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x38
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x40
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x02, 0x00,   // 0x48
    0x61, 0x62, 0x20, 0x00, 0x61, 0x02, 0x02, 0x00,   // 0x50
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x58
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // 0x60
    0xFF, 0xFF, 0xFF, 0xFF                            // 0x68
};

/* Perform IBC Disk Controller Command */
uint8_t IBC_HDC_doCommand(void)
{
    uint8_t fstatus = FR_OK;
    IBC_HDC_DRIVE_INFO* pDrive;
    uint8_t cmd = ibc_hdc_info->taskfile[TF_CMD];

    pDrive = &ibc_hdc_info->drive[ibc_hdc_info->sel_drive];

    pDrive->cur_cyl    = (uint16_t)ibc_hdc_info->taskfile[TF_TRKH] << 8;
    pDrive->cur_cyl   |= ibc_hdc_info->taskfile[TF_TRKL];
    cmd                = ibc_hdc_info->taskfile[TF_CMD] & 0x7F;
    pDrive->xfr_nsects = ibc_hdc_info->taskfile[TF_NSEC];
    pDrive->cur_head   = ibc_hdc_info->taskfile[TF_HEAD];
    pDrive->cur_sect   = ibc_hdc_info->taskfile[TF_CSEC];
    pDrive->cur_sectsize = 256;
    if (pDrive->xfr_nsects == 0) {
        pDrive->xfr_nsects = 1;
    }

    switch (cmd) {
    case IBC_HDC_CMD_RESET:  /* Reset */
        INTERRUPT_GlobalInterruptHighDisable();
        debug_print(DEBUG_INFO, ("RESET COMMAND 0x%02x\n\r", cmd));
        IBC_HDC_Reset();
        ibc_hdc_info->status_reg = 0x00;
        INTERRUPT_GlobalInterruptHighEnable();
        break;
    case IBC_HDC_CMD_READ_SECT:
    case IBC_HDC_CMD_WRITE_SECT:
    {
#ifdef DEBUG
        INTERRUPT_GlobalInterruptHighDisable();
#endif /* DEBUG */

        /* Abort the read/write operation if C/H/S/N is not valid. */
        if (IBC_HDC_Validate_CHSN(pDrive) != SCPE_OK) break;

        /* Calculate file offset */
        file_offset  = ((uint32_t)pDrive->cur_cyl * (uint32_t)pDrive->nheads * (uint32_t)pDrive->nsectors);   /* Full cylinders */
        file_offset += ((uint32_t)pDrive->cur_head * (uint32_t)pDrive->nsectors);   /* Add full heads */
        file_offset += ((uint32_t)pDrive->cur_sect);  /* Add sectors for current request */
        file_offset <<= 8; //*= (uint32_t)pDrive->sectsize;    /* Convert #sectors to byte offset */

        xfr_len = pDrive->xfr_nsects * pDrive->sectsize;

        f_lseek(&file[ibc_hdc_info->sel_drive], file_offset);

        if (cmd == IBC_HDC_CMD_READ_SECT) { /* Read */
            putchar('R');
            f_read(&file[ibc_hdc_info->sel_drive], sectbuf, xfr_len, &actualLength);
            debug_print(DEBUG_READ, ("Drive %d: READ SECTOR  C:%04d/H:%d/S:%04d/#:%2d, offset=%lx, len=%4d\n\r",
                ibc_hdc_info->sel_drive,
                pDrive->cur_cyl, pDrive->cur_head,
                pDrive->cur_sect, pDrive->xfr_nsects, file_offset, xfr_len));

            if (actualLength != xfr_len) {
                printf("Error: tried to read %d but got %d\n\r", xfr_len, actualLength);
                ibc_hdc_info->status_reg |= IBC_HDC_STATUS_ERROR;
            }
            ibc_hdc_info->status_reg = 0x60;
        }
        else { /* Write */
            putchar('W');
            debug_print(DEBUG_WRITE, ("Drive %d: WRITE SECTOR C:%04d/H:%d/S:%04d/#:%2d, offset=%lx, len=%4d, ix=%d, file=%p\n\r",
                ibc_hdc_info->sel_drive,
                pDrive->cur_cyl, pDrive->cur_head,
                pDrive->cur_sect, pDrive->xfr_nsects, file_offset, xfr_len,
                secbuf_index,
                &file));

            if ((fstatus = f_write(&file[ibc_hdc_info->sel_drive], sectbuf, xfr_len, &actualLength)) != FR_OK) {
                printf("Error 0x%02x writing.\n\r", fstatus);
            }
            if (actualLength != xfr_len) {
                printf("Error: tried to write %d but got %d\n\r", xfr_len, actualLength);
                ibc_hdc_info->status_reg |= IBC_HDC_STATUS_ERROR;
            }

            f_close(&file[ibc_hdc_info->sel_drive]);

            /* For some reason the first reopen always fails. */
            for (uint8_t i = 0;i<10;i++) {
                if (f_open(&file[ibc_hdc_info->sel_drive], disk_filenames[ibc_hdc_info->sel_drive], FA_READ | FA_WRITE) == FR_OK)
                {
                    break;
                }
            }
        }
        ibc_hdc_info->status_reg = 0x40;
#ifdef DEBUG
        INTERRUPT_GlobalInterruptHighEnable();
#endif /* DEBUG */
        break;
    }
    case IBC_HDC_CMD_FORMAT_TRK:
    {
        uint16_t data_len;

        data_len = pDrive->nsectors * pDrive->sectsize;

        /* Abort the read/write operation if C/H/S/N is not valid. */
        if (IBC_HDC_Validate_CHSN(pDrive) != SCPE_OK) break;

        putchar('F');

        /* Calculate file offset, formatting always handles a full track at a time. */
        file_offset = ((uint32_t)pDrive->cur_cyl * (uint32_t)pDrive->nheads * (uint32_t)pDrive->nsectors);   /* Full cylinders */
        file_offset += ((uint32_t)pDrive->cur_head * (uint32_t)pDrive->nsectors);   /* Add full heads */
        file_offset <<= 8; //*= pDrive->sectsize;    /* Convert #sectors to byte offset */

        debug_print(DEBUG_FORMAT, ("Drive %d: FORMAT TRACK: C:%d/H:%d/Fill=0x%02x/Len=%d, offset=%lx\n\r",
        ibc_hdc_info->sel_drive,
        pDrive->cur_cyl,
        pDrive->cur_head, IBC_HDC_FORMAT_FILL_BYTE, data_len, file_offset));

        INTERRUPT_GlobalInterruptHighDisable();
        memset(sectbuf, IBC_HDC_FORMAT_FILL_BYTE, IBC_HDC_FORMAT_CHUNK_LEN);
        f_lseek(&file[ibc_hdc_info->sel_drive], file_offset);
        for (uint16_t bytesFormatted = 0; bytesFormatted < data_len; bytesFormatted += IBC_HDC_FORMAT_CHUNK_LEN) {
            f_write(&file[ibc_hdc_info->sel_drive], sectbuf, IBC_HDC_FORMAT_CHUNK_LEN, &actualLength );
            if (actualLength != IBC_HDC_FORMAT_CHUNK_LEN) {
                printf("Error: tried to write %d but got %d\n\r", IBC_HDC_FORMAT_CHUNK_LEN, actualLength);
            }
            ibc_hdc_info->status_reg |= IBC_HDC_STATUS_ERROR;
        }

        f_close(&file[ibc_hdc_info->sel_drive]);
        /* For some reason the first reopen always fails. */
        for (uint8_t i = 0;i<10;i++) {
            if (f_open(&file[ibc_hdc_info->sel_drive], disk_filenames[ibc_hdc_info->sel_drive], FA_READ | FA_WRITE) == FR_OK)
            {
                    break;
            }
        }
        INTERRUPT_GlobalInterruptHighEnable();
        ibc_hdc_info->status_reg = 0x20;

        break;
    }
    case IBC_HDC_CMD_ACCESS_FIFO: /* Access FIFO */
        debug_print(DEBUG_INFO, ("ACCESS FIFO  %d blocks.\n\r",
            ibc_hdc_info->taskfile[TF_NSEC]));
        secbuf_index = 0;
        ibc_hdc_info->status_reg = 0x20;
        break;
    case IBC_HDC_CMD_READ_PARAMETERS:  /* Read Drive Parameters */
        debug_print(DEBUG_INFO, ("READ DRIVE PARAMETERS C:%0d/H:%d/S:%2d\n\r",
            pDrive->cur_cyl, pDrive->cur_head, pDrive->cur_sect));

        for (uint8_t i = 0; i < IBC_HDC_MAX_DRIVES; i++) {
            debug_print(DEBUG_INFO, ("Drive %d: C:%d/H:%d/S:%d/N:%d\n\r",
                    i,
                    ibc_hdc_info->drive[i].ncyls,
                    ibc_hdc_info->drive[i].nheads,
                    ibc_hdc_info->drive[i].nsectors,
                    ibc_hdc_info->drive[i].sectsize));
        }

        memcpy(sectbuf, HDParameters, sizeof(HDParameters));
        ibc_hdc_info->status_reg = 0x60;
        break;
    default:
        printf("UNKNOWN COMMAND 0x%02x\n\r",
            cmd);
        ibc_hdc_info->status_reg = 0x60;
        break;
    }
    return SCPE_OK;
}

void dump_hex(uint8_t *buff, uint16_t xfr_len)
{
    uint16_t i;

    for (i = 0; i < xfr_len; i++)
    {
        if (i % 16 == 0) printf("\n\r%04x: ", i);
        printf("%02x ", buff[i]);
    }
}

