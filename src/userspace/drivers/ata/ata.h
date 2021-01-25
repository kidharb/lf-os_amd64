/**
 * Define some constants that are shared across different drivers talking ATA
 *
 * LICense: MIT
 * Author: k4m1  <k4m1@protonmail.com>
 */

#ifndef __ATA_H__
#define __ATA_H__

#define __ATA_DISK_ID_INTERNAL_ATAPI 4
#define __ATA_DISK_ID_INTERNAL_SATA 3
#define __ATA_DISK_ID_INTERNAL_ATA 2
#define __ATA_DISK_ID_INTERNAL_NON_ATA 1

#define __ATA_DISK_ID_STR_NON_ATA "non ata"
#define __ATA_DISK_ID_STR_SATA "sata"
#define __ATA_DISK_ID_STR_ATAPI "atapi"
#define __ATA_DISK_ID_STR_ATA "ata"

#define __ATA_DATA(x)       (x)          // DATA Register
#define __ATA_ERR(x)        (x + 1)      // Error/Feature Register
#define __ATA_SECTOR_CNT(x) (x + 2)      // Sector Count Register
#define __ATA_SECTOR_NUM(x) (x + 3)      // Sector Number Register (LBA low)
#define __ATA_CYL_LO(x)     (x + 4)      // Cylinder low / LMA mid
#define __ATA_CYL_HI(x)     (x + 5)      // cylinder high / LMA high
#define __ATA_DRIVE_HEAD(x) (x + 6)      // drive/head Register
#define __ATA_STAT(x)       (x + 7)      // Status/Command Register

#define __ATA_ASDCR         0x3F6        // Alternate Status 
                                         // & DevICe Control Register
#define __ATA_DAT           0x3F7        // Drive Address Register

// ATA error bit definitions
#define __ATA_ERR_AMNF      0x01         // Address Mark Not Found
#define __ATA_ERR_TKZNF     0x02         // Track Zero Not Fount
#define __ATA_ERR_ABRD      0x04         // Command Aborted
#define __ATA_ERR_MCR       0x08         // Media Change Request
#define __ATA_IDNF          0x10         // ID not found
#define __ATA_MC            0x20         // Media Changed
#define __ATA_UNC           0x40         // Uncorrectable DATA Error
#define __ATA_BBD           0x80         // Bad Block Detected

// status register bit definitions
#define __ATA_STAT_ERR      0x01         // Error
#define __ATA_STAT_IC       0x06         // Index & correced data, always 0
#define __ATA_STAT_RDY      0x08         // Drive has data/is ready to recv
#define __ATA_STAT_OMSR     0x10         // Overlapped Mode ServICe Request
#define __ATA_STAT_DFE      0x20         // Drive fault ERR (does not set ERR!)
#define __ATA_STAT_CDE      0x40         // Clear on error / drive spun down
#define __ATA_STAT_WAIT     0x80         // Drive is preparing for send/recv

// devICe control register bit definitions
#define __ATA_DCR_ZERO      0x01         // Always zero
#define __ATA_DCR_CLI       0x02         // Set to disable intERRupts
#define __ATA_DCR_RST       0x04         // Set to do reset on bus
#define __ATA_DCR_RSVD      0x78         // Reserved
#define __ATA_DCR_HOB       0x80         // Set this to read the High Order Byte
                                         // of the last LBA48 value sent.

// drive address register bit definitions
#define __ATA_DAR_DS0       0x01         // Drive Select 0
#define __ATA_DAR_DS1       0x02         // Drive Select 1
#define __ATA_DAR_CSH       0x3c         // Currently Selected Head
                                         //   as compliment of one.
#define __ATA_DAR_WG        0x40         // Write Gate (0 when write active)
#define __ATA_DAR_RSVD      0x80         // Reserved

#define __ATA_DISK_ID_SATA  0x3c3c
#define __ATA_DISK_ID_ATAPI 0x14eb

/**
 * Helper macro to allow easy access to NOPs for few hundred-thousand
 * nanosecond delays needed by some ATA related operations.
 *
 * This is defined as volatile & 'memory' so that compilers realize
 * not to touch this seemingly useless bit of code.
 *
 */
#define NOP() (asm volatile("nop;"))

/**
 * Function declarations here
 */

/**
 * This function allows user to manually trigger ata reset. This can be 
 * useful eg. in case of crashed and/or buggy disk.
 *
 * \param port short Is a port to IO-base for device to reset.
 */
void ata_sw_reset(short port);


#endif  /* __ATA_H__ */
