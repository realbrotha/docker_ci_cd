/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/ide.h 1.26                                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)72       1.26  src/bos/kernel/sys/ide.h, sysxide, bos53V, v2009_06B4 11/18/08 15:30:14 */
#ifndef _H_ATA_IDE
#define _H_ATA_IDE
/*
 * COMPONENT_NAME: (ISAIDE) IBM ATA/IDE Header File
 *
 * FUNCTIONS: NONE
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 2006
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#include <sys/scsi.h>


#define IDE_COMMAND_REG_SPACE_SIZE       8  /* bytes per IDE channel
                                             * for command registers.
											 * Mapped via different
											 * PCI cfg BARs.
                                             */
#define IDE_CONTROL_BLOCK_REG_SPACE_SIZE 4  /* bytes per IDE channel
                                             * for control registers.
											 * Mapped via different
											 * PCI cfg BARs.
                                             */
#define IDE_BUS_MASTER_REG_SPACE_SIZE   16  /* bytes for both IDE channels
                                             * for bus master registers.
											 * Mapped via one
											 * PCI cfg BAR.
                                             */

#define IDE_MAX_RESET_TIME    30    /* Max. seconds per IDE spec to complete
                                     * a hard or soft reset.
                                     */

/*
 * PIO mode (and above) at which IORDY signal is to be employed.
 */
#define IDE_PIO_MODE_THRESHOLD_FOR_IORDY        3

/*
 * Ultra DMA mode (and above) which requires 80-conductor cable.
 */
#define IDE_UDMA_MODE_THRESHOLD_FOR_80C_CABLE   3

  /*
   * There are two interfaces involved here...the one from the processor
   * to the adapter (called ATA) and the one between the adapter and the
   * drive (called IDE).  Programmers always deal with ATA, and Engineers
   * worry about IDE, it's just different ends of the same mule.  Since
   * this is a Programming interface to IDE devices, its proper name is
   * ATA/IDE.  Within this code, ATA is used when dealing with the adapter/
   * port in general, and IDE is used to refer to one of possibly 2 IDE
   * devices connected to an ATA port.  A further wrinkle is the ATAPI
   * programming interface which is a SCSI-like extension of the basic
   * ATA programming interface.  Both ATA and ATAPI compatible devices
   * can be connected to a single ATA port.
  
   * A simple subset of the ANSI ATA-2 Task File command opcodes:
   * (in alphabetical order)
   */

#define ATA_ACKNOWLEDGE_MEDIA_CHANGE            0xDB
#define ATA_ATAPI_IDENTIFY_DEVICE		0xA1
#define ATA_ATAPI_PACKET_COMMAND		0xA0
#define ATA_ATAPI_SOFT_RESET			0x08
#define ATA_BOOT_POST_BOOT			0xDC
#define ATA_BOOT_PRE_BOOT			0xDD
#define ATA_CHECK_POWER_MODE			0xE5
#define ATA_DOOR_LOCK				0xDE
#define ATA_DOOR_UNLOCK   			0xDF
#define ATA_DOWNLOAD_MICROCODE			0x92
#define ATA_EXECUTE_DEVICE_DIAGNOSTIC		0x90
#define ATA_FLUSH_CACHE                         0xE7
#define ATA_FORMAT_TRACK			0x50
#define ATA_IDENTIFY_DEVICE			0xEC
#define ATA_IDLE				0xE3
#define ATA_IDLE_IMMEDIATE			0xE1
#define ATA_INITIALIZE_DEVICE_PARAMETERS	0x91
#define ATA_NOP					0x00
#define ATA_READ_BUFFER				0xE4
#define ATA_READ_DMA_RETRY			0xC8
#define ATA_READ_DMA				0xC9
#define ATA_READ_LONG_RETRY			0x22
#define ATA_READ_LONG				0x23
#define ATA_READ_MULTIPLE			0xC4
#define ATA_READ_SECTOR_RETRY			0x20
#define ATA_READ_SECTOR				0x21
#define ATA_READ_VERIFY_SECTOR_RETRY		0x40
#define ATA_READ_VERIFY_SECTOR			0x41
#define ATA_RECALIBRATE				0x10
#define ATA_SEEK				0x70
#define ATA_SET_FEATURES			0xEF
#define ATA_SET_FEATURE_DISABLE_WRITE_CACHE    0x82
#define ATA_SET_FEATURE_ENABLE_WRITE_CACHE     0x02
#define ATA_SET_FEATURE_SET_TRANSFER_MODE      0x03
#define ATA_SET_FEATURE_PIO_DEFAULT_TRANSFER_MODE    0x00
#define ATA_SET_FEATURE_PIO_NO_IORDY_TRANSFER_MODE   0x01
#define ATA_SET_FEATURE_PIO_IORDY_TRANSFER_MODE      0x08
#define ATA_SET_FEATURE_DMA_TRANSFER_MODE            0x20
#define ATA_SET_FEATURE_UDMA_TRANSFER_MODE           0x40
#define ATA_SET_MULTIPLE_MODE			0xC6
#define ATA_SLEEP				0xE6
#define ATA_STANDBY				0xE2
#define ATA_STANDBY_IMMEDIATE			0xE0
#define ATA_WRITE_BUFFER			0xE8
#define ATA_WRITE_DMA_RETRY			0xCA
#define ATA_WRITE_DMA				0xCB
#define ATA_WRITE_LONG_RETRY			0x32
#define ATA_WRITE_LONG				0x33
#define ATA_WRITE_MULTIPLE			0xC5
#define ATA_WRITE_SAME				0xE9
#define ATA_WRITE_SECTOR_RETRY			0x30
#define ATA_WRITE_SECTOR			0x31
#define ATA_WRITE_VERIFY			0x3C
#define ATA_SMART                   0xB0
#define ATA_SMART_RETURN_STATUS    (ATA_SMART)
#define ATA_SMART_CYLLO_LBAMID_INPUT    0x4F
#define ATA_SMART_RS_CYLLO_LBAMID_INPUT  (ATA_SMART_CYLLO_LBAMID_INPUT)
#define ATA_SMART_CYLHI_LBAHI_INPUT     0xC2
#define ATA_SMART_RS_CYLHI_LBAHI_INPUT   (ATA_SMART_CYLHI_LBAHI_INPUT)

#define ATA_SMART_RS_CYLLO_LBAMID_FAIL     0xF4
#define ATA_SMART_RS_CYLHI_LBAHI_FAIL      0x2C

#define ATA_SMART_RS_FEATURES       0xDA    /* SMART RETURN STATUS */
#define ATA_SMART_SE_FEATURES       0xD8    /* SMART ENABLE OP     */
#define ATA_SMART_SD_FEATURES       0xD9    /* SMART DISABLE OP    */
#define ATA_SMART_RL_FEATURES       0xD5    /* SMART READ LOG      */
#define ATA_SMART_WL_FEATURES       0xD6    /* SMART WRITE LOG     */
#define ATA_SMART_RD_FEATURES       0xD0    /* SMART READ DATA     */
#define ATA_SMART_AA_FEATURES       0xD2    /* SMART EN/DIS ATTR AUTOSAVE */
#define ATA_SMART_EO_FEATURES       0xD4    /* SMART EXEC OFFLINE IMMED */


/* ATAPI Tape and CD-ROM commands (redefined SCSI commands-see scsi.h) */
/* 
 * As referenced in ATA/ATAPI-5 Rev. 3  29 February 2000, the ATAPI
 * commands are defined in Table B-2 of MMC-2 Rev. 11a  August 30, 1999
 * which list the Multi Media Command set 2, and are (almost) exact
 * instances of SCSI commands)
 */

#define ATAPI_BLANK				0xA1
#define ATAPI_CLOSE_TRACK_SESSION		0x5B
#define ATAPI_ERASE				SCSI_ERASE		/*0x19*/
#define ATAPI_FORMAT_UNIT			SCSI_FORMAT_UNIT	/*0x04*/
#define ATAPI_GET_CONFIGURATION			SCSI_GET_CONFIGURATION	/*0x46*/
#define ATAPI_GET_EVENT/STATUS_NOTIFICATION	0x4A
#define ATAPI_GET_PERFORMANCE			0xAC
#define ATAPI_INQUIRY				SCSI_INQUIRY		/*0x12*/
#define ATAPI_LOAD_UNLOAD			SCSI_LOAD		/*0x1B*/
#define ATAPI_MECHANISM_STATUS			0xBD
#define ATAPI_MODE_SELECT			SCSI_MODE_SELECT	/*0x15*/
#define ATAPI_MODE_SELECT_10			SCSI_MODE_SELECT_10	/*0x55*/
#define ATAPI_MODE_SENSE			SCSI_MODE_SENSE		/*0x1A*/
#define ATAPI_MODE_SENSE_10			SCSI_MODE_SENSE_10	/*0x5A*/
#define ATAPI_PAUSE_RESUME			SCSI_PAUSE_RESUME	/*0x4B*/
#define ATAPI_PLAY_AUDIO			SCSI_PLAY_AUDIO		/*0x45*/
#define ATAPI_PLAY_AUDIO_10			SCSI_PLAY_AUDIO		/*0x45*/
#define ATAPI_PLAY_AUDIO_EXT			SCSI_PLAY_AUDIO_EXT	/*0xA5*/
#define ATAPI_PLAY_AUDIO_12			SCSI_PLAY_AUDIO_EXT	/*0xA5*/
#define ATAPI_PLAY_AUDIO_MSF			SCSI_PLAY_AUDIO_MSF	/*0x47*/
#define ATAPI_PLAY_AUDIO_TRACK_INDEX		SCSI_PLAY_AUDIO_TRK_INDX/*0x48*/
#define ATAPI_PREVENT_ALLOW_REMOVAL		SCSI_PREVENT_ALLOW_REMOVAL /*0x1E*/
#define ATAPI_READ_DISC_INFO			0x51
#define ATAPI_READ_6				SCSI_READ		/*0x08*/
#define ATAPI_READ_EXTENDED			SCSI_READ_EXTENDED	/*0x28*/
#define ATAPI_READ_10				SCSI_READ_EXTENDED	/*0x28*/
#define ATAPI_READ_12				0xA8
#define ATAPI_READ_CAPACITY			SCSI_READ_CAPACITY	/*0x25*/
#define ATAPI_READ_CD				SCSI_READ_CD		/*0xBE*/
#define ATAPI_READ_CD_MSF			0xB9
#define ATAPI_READ_DISC_INFO			0x51
#define ATAPI_READ_DVD_STRUCTURE		0xAD
#define ATAPI_READ_FORMAT_CAPACITIES		0x23
#define ATAPI_READ_HEADER			SCSI_READ_HEADER	/*0x44*/
#define ATAPI_READ_POSITION			0x34
#define ATAPI_READ_SUBCHANNEL			SCSI_READ_SUB_CHANNEL	/*0x42*/
#define ATAPI_READ_TOC				SCSI_READ_TOC		/*0x43*/
#define ATAPI_READ_TRACK_INFO			0x52
#define ATAPI_REQUEST_SENSE			SCSI_REQUEST_SENSE	/*0x03*/
#define ATAPI_RESERVE_TRACK			0x53
#define ATAPI_REWIND				SCSI_REWIND		/*0x01*/
#define ATAPI_REZERO_UNIT			SCSI_REZERO_UNIT	/*0x01*/
#define ATAPI_SEEK_EXTENDED			SCSI_SEEK_EXTENDED	/*0x2B*/
#define ATAPI_SEND_DVD_STRUCTURE		0xBF

#define ATAPI_SET_STREAMING			0xB6
#define ATAPI_SPACE				SCSI_SPACE		/*0x11*/
#define ATAPI_STOP_PLAY_SCAN			0x4E
#define ATAPI_START_STOP_UNIT			SCSI_START_STOP_UNIT	/*0x1B*/
#define ATAPI_SYNCHRONIZE_CACHE			0x35
#define ATAPI_TEST_UNIT_READY			SCSI_TEST_UNIT_READY	/*0x0*/
#define ATAPI_WRITE				SCSI_WRITE		/*0x0A*/
#define ATAPI_WRITE_10				SCSI_WRITE_EXTENDED	/*0x2A*/
#define ATAPI_WRITE_12				0xAA
#define ATAPI_WRITE_AND_VERIFY			SCSI_WRITE_AND_VERIFY	/*0x2E*/
#define ATAPI_WRITE_BUFFER			SCSI_WRITE_BUFFER	/*0x3B*/
#define ATAPI_WRITE_FILEMARK			SCSI_WRITE_FILEMARK	/*0x10*/

/* Not in MMC-2 #define ATAPI_AUDIO_SCAN		0xD8  */
/* Not in MMC-2 #define ATAPI_LOG_SELECT		0x4C  */
/* Not in MMC-2 #define ATAPI_LOG_SENSE			0x4D  */
/* Not in MMC-2 #define ATAPI_SET_CDROM_SPEED		0xDA  */
/* Not in MMC-2 #define ATAPI_PLAY_TRACK_RELATIVE_10	0x49  */
/* Not in MMC-2 #define ATAPI_PLAY_TRACK_RELATIVE_12	0xA9  */
/* Not in MMC-2 #define ATAPI_PLAY_CDROM_XA		0xAE  */
/* Not in MMC-2 #define ATAPI_LOCATE			SCSI_SEEK_EXTENDED  */

/* ATA Packet (ATAPI) defines for DMA Settings in Feature Register */

/* Setting this bit in the Features register for an ATAPI Packet Command
 * host/drive will use DMA XFER for command
 */
#define ATAPI_FEATURE_DMA_BIT         0x01
/* The DMADIR Bit (DMA Direction) is bit 15 of word 62 of Identify 
 * Packectized Data.  If the DMADIR bit is set, then it is required
 * that the DMADIR bit in the features register is set to 1 for ATAPI Packet
 * Commands, which perform DMA Read transfers (and 0 for write transfers).
 */
#define ATAPI_FEATURE_DMADIR_READ     0x04



/* Refer to the ATA ANSI X3T9.791D-1994 for pre-release information */
/*    or to the ATA ANSI X3.221-19?? standard for final information */
/*    on the AT-Attachment (ATA) interface                          */
/* refer to the SCSI ANSI X3.131-199x standard for SCSI information */
/*   and to the SFF-802x rev. 1.1 documents for ATAPI information   */

struct atpkt_cmd {              /* structure of ATAPI command packet */
	uchar	op_code;	/* first byte of ATAPI cmd packet */
				/* these op codes are essentially */
				/* duplicates of the SCSI commands*/
				/* but don't include all SCSI cmds*/
        uchar	bytes[15];	/* other bytes of ATAPI cmd packet */
				/* the format of these bytes is    */
				/* similar to that of the SCSI Command */
                                /* Descriptor Block (CDB), but different */
				/* enough that SCSI CDBs won't work here.*/
};

struct atapi_command {
	uchar	length;		/* byte length of ATAPI cmd (12 or 16) */
	uchar	resvd;		/* reserved, should be set to zero */
	uchar	resvd1;		/* reserved, should be set to zero */
	uchar	resvd2;		/* reserved, should be set to zero */
	struct atpkt_cmd packet;/* actual ATAPI command packet */
};

union ata_addr {		/* sector/LBA address offset on device */
	struct {		/* Cylinder/Head/Sector version of address */
#ifdef _IA64
		uchar sector;   /* starting sector to be accessed */
		uchar cyl_lo;	/* low portion of cylinder to be accessed */
		uchar cyl_hi;	/* high portion of cylinder to be accessed */
		uchar head;	/* device head to be accessed */
#else
		uchar head;	/* device head to be accessed */
		uchar cyl_hi;	/* high portion of cylinder to be accessed */
		uchar cyl_lo;	/* low portion of cylinder to be accessed */
		uchar sector;   /* starting sector to be accessed */
#endif
	} chs;
	uint	lba;		/* Logical Buffer Address version of address*/
};

struct ata_cmd {		/* ATA command buffer definition */
	uchar	flags;		/* indicate command mode, (mutally exclusive)*/
#define ATA_CHS_MODE     0x00   /* Execute command in CHS mode (not LBA) */
#define ATA_LBA_MODE     0x01   /* Execute command in LBA mode (not CHS) */
#define ATA_BUS_RESET    0x02   /* Reset ATA bus only, ignore command op */

        /* command out section */
	uchar	command;	/* actual ATA command byte */
	uchar	device;		/* 0 - Master device; 1 - Slave device */
	uchar	sector_cnt_cmd;	/* number of sectors affected by command */
	union ata_addr startblk;/* beginning sector/LBA for command operation*/
	uchar	feature;	/* feature code (for ATA_SET_FEATURES command*/
                                /* used by ATAPI to choose DMA (LSB on) or   */
                                /* PIO (LSB off) mode of operation for CMD   */
	/* result return section */
	uchar	status;		/* ATA status Register (return value) */
#define ATA_ERROR		0x01 
	/* indicates an error occured, see 'errval' for details */
#define	ATAPI_CHECK_COND	ATA_ERROR	/* Check Condition	*/

#define ATA_IDX			0x02 
	/* momentary signal indicating passage of media index mark (or hole)*/
#define ATA_CORRECTED_DATA	0x04 
	/* indicates that a recoverable data error occured */
#define ATA_DATA_REQUEST	0x08 
	/* indicates that a Data Transfer sequence is to be initiated */
#define ATA_SEEK_COMPLETE	0x10 
	/* indicates that Device Seek is complete, (heads over desired track)*/
#define ATA_WRITE_FAULT		0x20 
	/* device write fault has occured */
#define ATA_DEVICE_READY	0x40 
	/* Device is ready to accept new command */
#define ATA_BUSY		0x80 
	/* Device is busy, (max 31 seconds following reset, 5 sec all others)*/

	uchar	errval;		/* ATA error Register (return value) */
				/* only valid if ERR bit on in 'status' */
#define ATA_ADDR_MARK_NOT_FND	0x01 
	/* indicates address mark not found after finding correct ID field */
#define ATA_TRK0_NOT_FND	0x02 
	/* indicates Track Zero not found during recalibration command */
#define ATA_ABORTED_CMD		0x04 
	/* indicates command was aborted due to status error or not ready */
#define ATA_MEDIA_CHANGE_REQ	0x08 
	/* device detected media change request (need to issue DOOR_UNLOCK) */
#define ATA_ID_NOT_FND		0x10 
	/* requested sector/LBA ID not found */
#define ATA_MEDIA_CHANGED	0x20 
	/* Media removed or changed since last access */
#define ATA_UNCORRECTABLE_DATA  0x40 
	/* Uncorrectable data error has been found */
#define ATA_BAD_BLOCK_FND	0x80 
	/* requested sector was previously marked as a 'Bad Block' */

        /* ATAPI definition for error register */
#define ATAPI_ERROR_SENSE_KEY	0xF0	/* Sense Key			*/
#define ATAPI_ERROR_MCR		0x08	/* Media Change Requested	*/
#define ATAPI_ERROR_ABRT	0x04	/* Aborted Command		*/
#define ATAPI_ERROR_EOM		0x02	/* End Of Memory		*/
#define ATAPI_ERROR_ILI		0x01	/* Illegal Length Indication	*/

	uchar	sector_cnt_ret;	/* number of sectors not processed by command*/
	union ata_addr endblk;  /* completion sector/LBA (return value) */
	struct atapi_command atapi;  /* optional atapi command portion */
};

/* Command Structure used for ATA Extended Commands 
 * ATA Extended Commands should always be in LBA Mode 
 */
struct ata_cmd_ext {
       uchar  version; /* structure versioning field */
       uchar  status;  /* ATA Status returned after command completion
                        * Flags are defined under struct ata_cmd         */
       uchar  errval;  /* ATA Error returned after command completion
                        * Flags are defined under struct ata_cmd         */
       uchar  rsv0;    /* reserved field should be set to zero           */
       
       /* For the extended registers which follow, the higher order byte
        * is the byte that is written(or read) under "Previous" (first) 
        * in the ATA/ATAPI-7 V1 Standard                                 */ 
       uchar  feature_ext[2]; /* 2 byte extended feature register        */
       uchar  sector_cnt_cmd_ext[2]; /* 2 byte sector count register     */ 
       uchar  lba_high_ext[2]; /* 2 byte lba high register               */
       uchar  lba_mid_ext[2];  /* 2 byte lba mid register                */
       uchar  lba_low_ext[2];  /* 2 byte lba low register                */
       
       uchar  device;          /* device register                        */
       uchar  command;         /* command register or opcode for extended 
                                * ata (48-bit Address) command           */
       uchar  sector_cnt_ret_ext[2]; /* number of sectors not processed by 
                                        command*/
       uchar  endblk_ext[6];         /* completion sector/LBA (return value) */
};





/*
   * ataide_buf structure used by IDE device driver to communicate
   * with the IDE adapter driver.  This is passed to the adapter
   * driver strategy routine entry point.
   */
struct ataide_buf {
	struct buf	bufstruct;	/* buffer structure containing request
					   for device */
	struct buf	*bp;		/* pointer back to original buffer
					   structure list for command 
					   coalescing */
	struct ata_cmd  ata;     	/* the information relating strictly
					   to the ataide command itself */
	uint	sg_ptr;			/* when not zero it is a pointer to   
                                           uio struct for gathered writes  */
	uint	timeout_value;		/* timeout value for the command, 
					   in units of seconds */
	uchar	status_validity; 	/* least significant bit - ata_status
					   valid, next least significant bit -
					   card status valid */
#define	ATA_IDE_STATUS		1	/* ata.status is valid */
#define ATA_ERROR_VALID		2	/* ata.error reflects error */
#define ATA_DIAGNOSTICS_ERROR	4	/* adapter diagnostics reflects error*/
#define ATA_SMART_VALID    ATA_DIAGNOSTICS_ERROR
#define ATA_CMD_TIMEOUT		0x08	/* adapter timeout of command	*/
#define ATA_NO_DEVICE_RESPONSE	0x10	/* device continually busy	*/
#define ATA_IDE_BUS_RESET	0x20	/* adapter reset the bus	*/
#define ATA_IDE_DMA_ERROR	0x40	/* DMA error occurred   	*/
#define ATA_IDE_DMA_NORES	0x80	/* DMA Resource error occured   */


	uchar	adapter_diagnostics;    /* generic ATA Diagnostics return
					   byte */
#define ATA_DIAGNOSTICS_OK      0x01
	/* indicates Diagnostics ran OK */
#define ATA_FORMATTER_ERR       0x02
	/* indicates a formatter device error */
#define ATA_SECTOR_BUFFER_ERR   0x03
	/* indicates a failure in the sector buffer */
#define ATA_ECC_CIRCUIT_ERR     0x04
	/* indicates a failure in the error correcting code circuitry */
#define ATA_PROCESSOR_ERR       0x05
	/* indicates a failure of the microprocessor */
#define ATA_ERROR_NO_RETRY      0x40
        /* indicates a command failed and should not be retried */
#define ATA_DEVICE1_ERR		0x80
	/* indicates the slave device (device 1) reported an error */

        uchar      q_flags;     /* queue control flags                  */
#define ATA_RESUME      0x01    /* resume transaction queuing for this  */
                                /* ATA port begining with this buf      */
        uchar        version;   /* This field was previously reserved.  
                                   If set to zero (ATA_BUF_VERSION1), then
                                   the ataide_buf definition stops at resvd0.
                                   ATA_BUF_VERSION2 adds fields for support
                                   of SATA Devices. */
#define ATA_BUF_VERSION1 0x00
#define ATA_BUF_VERSION2 0x10
        /* if version is set to ATA_BUF_VERSION2 (or above)
           then the fields below this point are valid */
        unsigned long long sata_address; /* 64 Bit Address field used 
                                             to address SATA devices. */
#define ATA_ADAPTER_SET_VALID     0x0001 /* adapter_set_flags valid   */
#define ATA_DEVICE_RESET_OCCURRED 0x0002 /* device was reset by adapter */ 
#define ATA_ADAPTER_HDW_FAILURE   0x0004 /* adapter hardware failure    */
#define ATA_ADAPTER_SFW_FAILURE   0x0008 /* adapter software failure    */
        ushort adapter_set_flags;        /* flags set by the adapter */
#define ATA_DMA_XFER 0x01                /* Adapter should attempt to use DMA*/
#define ATA_PIO_XFER 0x02                /* Adapter should use PIO */ 
#define ATA_EXT_CMD  0x04                /* Command is ATA Extended Command
                                          * use ata_cmd_ext instead of ata_cmd
                                          * Only valid for use with ata 
                                          * extended commands. ATAPI and 
                                          * non-extended ATA commands should
                                            always use ata_cmd.              */
/* 0x10 and 0x20 are reserved values for xfer_flag. Used for internal driver
   use only.                                                                 */
        uchar  xfer_flag;                /* flags for data transfers */
#define SATA_STATUS_VALID  0x01          /* serial_ata_status field is valid */
#define SATA_ERROR_VALID   0x02          /* serial_ata_error field is valid  */
#define SATA_CONTROL_VALID 0x04          /* serial_ata_control field is valid*/
        uchar  serial_ata_validity;      /* serial ata register validity flag*/
        uint   serial_ata_status;        /* 32 Bit Serial ATA Status Register*/
        uint   serial_ata_error;         /* 32 Bit Serial ATA Error Register */
        uint   serial_ata_control;       /* 32 Bit Serial ATA Control Register*/
        unsigned long long kernext_handle;/* handle passed to adapter        */
        struct ata_cmd_ext ata_cmd_ext;  /* fields used for extended ata cmds*/
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * ataide_bufv1 structure used by IDE device driver to communicate with 
 * legacy IDE adapter drivers.  This is passed to the adapter driver
 * strategy routine entry point.
 */
struct ataide_bufv1 {
        struct buf      bufstruct;      /* buffer structure containing request
                                           for device */
        struct buf      *bp;            /* pointer back to original buffer
                                           structure list for command 
                                           coalescing */
        struct ata_cmd  ata;            /* the information relating strictly
                                           to the ataide command itself */
        uint    sg_ptr;                 /* when not zero it is a pointer to
                                           uio struct for gathered writes  */
        uint    timeout_value;          /* timeout value for the command,
                                           in units of seconds */
        uchar   status_validity;        /* least significant bit - ata_status
                                           valid, next least significant bit -
                                           card status valid */
        uchar   adapter_diagnostics;    /* generic ATA Diagnostics return
                                           byte */
        uchar      q_flags;     /* queue control flags                  */
        uchar        resvd0;    /* reserved should be set to zero */ 
};



/* Modes for OPENX */
#define ATA_DIAGNOSTIC		SC_DIAGNOSTIC

 /* Macros to handle internal IOCTL commands */

 /*
  ATA/IDE adapter driver IOCTL command options follow.
  Some of the internal IOCTL commands passed to the ATA/IDE adapter driver
  by the ATA/IDE device drivers are invoked with code similar to:
  
  ddioctl(fd, IDEIOSTART, ide_device);

  NOTE:
  IOCTL calls are assumed to be from the kernel or a 32 bit application.
  */

#define IDEIOSTART	SCIOSTART
                          	/* cause adapter driver to allocate internal
				   resources for the IDE device */
#define	IDEIOSTOP	SCIOSTOP
                                /* cause adapter driver to release internal
				   resources for the IDE device */
#define IDEIOHALT	SCIOHALT
                                /* not currently supported - returns EINVAL*/
				/* cause adapter driver to abort all commands
				   currently running or pending until a
				   transaction with the ATA_RESUME bit is set
				   in ataide_buf.q_flags */
#define IDEIOINQU	SCIOINQU
				/* cause adapter driver to run an ATAPI device
				   inquiry command to the IDE device.  ATA
				   devices will not respond to this command.
				   For this operation, you must specify the
				   "arg" parameter with the address of a data
				   area which is defined by the ide_inquiry 
				   structure */
#define IDEIOIDENT	980     /* cause adapter driver to run an ATA Identify
				   device command to the IDE device.  ATAPI
				   devices will not respond to this command.
				   For this operation, you must specify the
				   "arg" parameter with the address of a data
				   area which is defined by the ide_identify
				   structure */

#define IDEIORESET	SCIORESET
                                /* not currently supported - returns EINVAL*/
				/* cause adapter driver to issue an ATA bus 
				   device reset message to the ATA device
				   selected.  The IDE device in this case must
				   be an IDE device on this ATA port which was
				   previously started via IDEIOSTART */
#define IDEIOSTUNIT	SCIOSTUNIT
				/* cause adapter driver to run an ATAPI device
				   start unit command to an ide device.  The
				   "arg" parameter specifies the address of
				   the data area defined by the ide_startunit 
				   structure */
#define IDEIOTUR	SCIOTUR
				/* cause adapter driver to run an ATAPI device
				   test unit ready command to an ide device.
				   The "arg" parameter specifies the address of
				   the data area defined by the ide_ready
				   structure */
#define IDEIOREAD	SCIOREAD
				/* cause adapter driver to run an IDE device
				   read command to the IDE device to read
				   a single block.  For this operation, you
				   must specify the "arg" parameter with the
				   address of a data area which is defined
				   by the ide_readblk structure */
#define IDEDNLD		SCSIDNLD
				/* cause adapter driver to download microcode
				   to a specific ATA/ATAPI device type. */
#define IDEPASSTHRU	979
				/* cause adapter driver to PASSTHRU an ATAPI
				   command to the specified device. */
#define IDEVENDORSPEC   978	/* cause adapter driver to perform vendor
                                   specific operations. */
#define IDEHARDRESET    977 /* cause adapter driver to issue a
							   hard-reset on a specified IDE channel
                               if supported by the particular controller. */

/*940 - 910 reserved for SATA IOCTL's */
#define SATAPASSTHRU    940
#define SATAIOSTART     937
#define SATAIOSTOP      936


/*
  Definitions for ATA/IDE device driver from kernel/application level tasks.
  These are used by the HEAD drivers, the adapter driver doesn't use them.
  */

/*
  IDI Read/Write with Sense Ioctl Structure
  */
struct ide_rdwrt {
	uint	logical_blk_addr;	/* Logical block address
					   (0 for sequential devices) */
	uint	data_length;		/* Data transfer length in bytes */
	char	*buffer;		/* Pointer to data transfer buffer */
	uchar   resvd1;			/* reserved, should be set to zero */
	uchar   resvd2;			/* reserved, should be set to zero */
	uchar   resvd3;			/* reserved, should be set to zero */
	uchar	req_sense_length;	/* Length of request sense data buffer
					   in bytes */
	char	*request_sense_ptr;	/* Pointer to request sense buffer */
	uint	timeout_value;		/* Timeout value for the command, 
					   in seconds */
        uchar   status_validity;	/* 0 = no valid status           */
	/* ATA_IDE_STATUS, ATA_ERROR and ATA_DIAGNOSTICS_ERROR 
	   are defined in ataide_buf
	   1 = valid ata_status only
	   2 = valid ata_error
	   4 = valid adapter_diagnostics	*/
#define ATAPI_VALID_SENSE	8	/* valid sense data for read/write
					   with sense */
	uchar	ata_status;		/* returned ata status */
	uchar	ata_error;		/* returned ata error, refer to 
					   ataide_buf definition */
	uchar   adapter_diagnostics;	/* generic ata diagnostics return  */
	uchar   resvd5;			/* reserved, should be set to zero */
	uchar   resvd6;			/* reserved, should be set to zero */
	uchar   resvd7;			/* reserved, should be set to zero */
	uchar	q_flags;		/* Used to tell the ATA/IDE adapter*/
					/* driver whether or not it should */
					/* resume its queue.  This is done */
					/* via ATA_Q_CLR and ATA_Q_RESUME  */
					/* defines in ataide_buf           */

};


/*
  ATAPI/SCSI Inquiry structure passed by pointer to ioctl of adapter driver
  */
struct ide_inquiry {
	uchar ide_device;	/* target device id */
	uchar rsv2;		/* reserved, should be set to zero */
	uchar get_extended;     /* = TRUE if getting extended inq */
	uchar inquiry_len;	/* number of bytes to transfer (0 - 255) */
	uchar *inquiry_ptr;	/* pointer to inquiry data buffer */
	uchar code_page_num;    /* code page # when get_extended=TRUE */
	uchar ata_status;	/* contains the ata/ide status reg value */
	uchar ata_error;	/* dontains the ata/ide error reg value  */
	uchar flags;		/* flags:  see 'flags' in struct ata_cmd */
	uint  rsv5;		/* reserved, should be set to zero */
};



struct identify_device {

        ushort gen_config;
#define ID_PROTOCOL_SHIFT     14
#define ID_PROTOCOL_MASK      0xC000
#define ID_ATAPI              0x8000

#define ID_DEVICE_TYPE_SHIFT  8
#define ID_DEVICE_TYPE_MASK   0x1f00
#define ID_SEQUENTIAL         0x0100

#define ID_REMOVABLE          0x0080

#define ID_CMD_DRQ_SHIFT      5
#define ID_CMD_DRQ_MASK       0x0060
#define ID_ACCEL_DRQ          0x0040

#define ID_CMD_PCKT_SIZE_MASK 0x0003
#define ID_CMD_PCKT_SIZE_12   0x0000
#define ID_CMD_PCKT_SIZE_16   0x0001

        ushort num_of_cyl;
        ushort reserv2;
        ushort num_of_heads;
	ushort reserv4_5[2];
	ushort sectors_per_track;
	ushort reserv7_9[3];
	ushort ascii_serial_num[10];

        ushort buffer_type;
#define ID_BUF_TYPE_COMPRS    0x8000
#define ID_BUF_TYPE_ECC       0x4000
#define ID_BUF_TYPE_UNLOAD    0x0800
#define ID_BUF_TYPE_PREVENT   0x0400
#define ID_BUF_TYPE_LOCKED    0x0200
#define ID_BUF_TYPE_LOCK      0x0100
#define ID_BUF_TYPE_SLOWB     0x0080
#define ID_BUF_TYPE_BLK1024   0x0003
#define ID_BUF_TYPE_BLK512    0x0002

        ushort buffer_size;              /* 512 byte increments */
        ushort num_ecc_bytes;
        ushort firmware_revision[4];
        ushort model_number[20];
        ushort max_sect_per_intr;
        ushort reserv48;

        ushort capabilities;
#define ID_CAP_DMA           0x0100
#define ID_CAP_LBA           0x0200
#define ID_CAP_IORDY_DISABLE 0x0400
#define ID_CAP_IORDY         0x0800

        ushort reserv50;

#ifdef _PCIIDE			/* according to new ATA/ATAPI-4 spec,
				   these words have new meanings */
        ushort pio_data_xfer_mode;
#define ID_PIO_XFER_MODE    0xff00
#define ID_XFER_MODE_SHIFT  8

        ushort dma_data_xfer_mode;
#define ID_DMA_XFER_MODE    0xff00

#else
        ushort pio_data_xfer_cycle_timing;
#define ID_PIO_XFER_CYCLE    0xff00

        ushort dma_data_xfer_cycle_timing;
#define ID_DMA_XFER_CYCLE    0xff00

#endif  /* _PCIIDE */

        ushort field_validity;
#define ID_VALID_88    0x0004
#define ID_VALID_64_70 0x0002
#define ID_VALID_54_58 0x0001

        ushort num_curr_cylinders;
        ushort num_curr_heads;
        ushort num_curr_sec_track;
        ushort capacity_in_sectors[2];
        ushort reserv59;
        ushort total_num_sectors[2];

        ushort single_word_dma_xfer;
#define ID_SW_DMA_MODE_0    0x0001
#define ID_SW_DMA_MODE_1    0x0002
#define ID_SW_DMA_MODE_2    0x0004
#define ID_SW_DMA_MODE_3    0x0008
#define ID_SW_DMA_MODE_4    0x0010
#define ID_SW_DMA_MODE_5    0x0020
#define ID_SW_DMA_MODE_6    0x0040
#define ID_SW_DMA_MODE_7    0x0080
#define ID_SW_CURR_DMA_MODE 0xff00
#define ID_SW_SUPT_DMA_MODE 0x00ff
#define ID_DMADIR_REQ       0x8000

        ushort multi_word_dma_xfer;
#define ID_MW_DMA_MODE_0    0x0001
#define ID_MW_DMA_MODE_1    0x0002
#define ID_MW_DMA_MODE_2    0x0004
#define ID_MW_DMA_MODE_3    0x0008
#define ID_MW_DMA_MODE_4    0x0010
#define ID_MW_DMA_MODE_5    0x0020
#define ID_MW_DMA_MODE_6    0x0040
#define ID_MW_DMA_MODE_7    0x0080
#define ID_MW_CURR_DMA_MODE 0xff00
#define ID_MW_SUPT_DMA_MODE 0x00ff

        ushort enhanced_pio_mode;
	/* advanced PIO modes in WORD64. One bit each level but
	   support is hierarchical so the bits may be nested.
	   Support for Mode 4 implies support for Mode 3.  */
#define ID_PIO_MODE_3    0x0001
#define ID_PIO_MODE_4    0x0002
#define ID_PIO_ENH_MODE  0x0003
#define ID_CURR_PIO_MODE 0xff00
#define ID_SUPT_PIO_MODE 0x00ff

        ushort min_multi_word_dma_xfer_time;     /* in nanoseconds */
        ushort recommended_multi_dma_xfer_time;  /* in nanoseconds */
        ushort min_pio_xfer_no_flow_control;     /* in nanoseconds */
        ushort min_pio_xfer_with_flow_control;   /* in nanoseconds */
        ushort reserv69_81[13];
		ushort command_set_supported82;
#define ID_SMART_FEATURE_SET_SUPPORTED     0x0001

        ushort reserv83_84[2];
		ushort command_set_feature_enabled85;
#define ID_SMART_FEATURE_SET_ENABLED       0x0001

		ushort command_set_feature_enabled86;
#define ID_DOWNLOAD_MICROCODE_SUPPORTED    0x0001

		ushort command_set_feature_default87;


        ushort ultra_dma_xfer_mode;  /* format and defines use the same
                                        as for multi_word_dma_xfer */
#define ID_SUPT_UDMA_MODE 0x00ff
        ushort reserv89_255[167];

};


/*
  ATA/IDE Identify structure passed by pointer to ioctl of adapter driver
  */
struct ide_identify {
	uchar ide_device;	/* target device id */
	uchar flags;		/* flags:  see 'flags' in struct ata_cmd */
	ushort identify_len;	/* number of bytes to transfer (0 - 65535) */
	uchar *identify_ptr;	/* pointer to inquiry data buffer */
#define IDE_ID_NODEV	0
#define IDE_ID_ATA      1
#define IDE_ID_ATAPI    2
	uchar ata_atapi;        /* return 0=no device,1=ata;2=atapi */
	uchar ata_status;	/* contains the ata/ide status reg value */
	uchar ata_error;	/* dontains the ata/ide error reg value  */
	uchar rsv0;		/* reserved, should be set to zero */
};


/*
  ATA/IDE Read structure passed by pointer to ioctl of adapter driver
  */
struct ide_readblk {
	uchar ide_device;	/* target device id */
	uchar flags;		/* flags:  see 'flags' in struct ata_cmd */
	short blksize;		/* number of bytes in device's block */
	int   blkno;		/* LBA of first block to read */
	uint  timeout_value;	/* timeout value for command, in secs. */
	uchar *data_ptr;	/* pointer to buffer for read data */
	uchar ata_status;	/* contains the ata/ide status reg value */
	uchar ata_error;	/* dontains the ata/ide error reg value  */
	uchar rsv0;		/* reserved, should be set to zero */
	uchar rsv1;		/* reserved, should be set to zero */
};


/*
  ATA_PASSTHRU structure passed by pointer to ioctl of adapter driver
  */
struct ata_command {
      uchar   features;
      uchar   sector_cnt;
      uchar   lba_low;
      uchar   lba_mid;
      uchar   lba_high;
      uchar   device;
      uchar   command;
};

#define IDE_ATA_PASSTHRU_VERSION_1 0x11110000
struct ide_ata_passthru {
      uint    version;
      uchar   flags;
      uint    buffsize;
      uint    timeout_value;
      uchar   *data_ptr;
      uchar   ata_status;
      uchar   ata_error;
      __ulong64_t resid;
      struct ata_command ata_cmd;
};

/*
  ATAPI_PASSTHRU structure passed by pointer to ioctl of adapter driver
  */

#define IDE_PASSTHRU_VERSION_01 0x01

struct ide_atapi_passthru {
        uchar ide_device;       /* target device id */
        uchar flags;            /* flags:  see 'flags' in struct ata_cmd */
#define IDE_PASSTHRU_READ 0x04  /* Direction of data transfer */
        ushort buffsize;        /* Size in bytes of command/data buffer. */
        uint timeout_value;     /* timeout value in seconds, for command. */
	uchar *data_ptr;	/* pointer to buffer for read data */
        uchar ata_status;       /* Return contents of the ata/ide status reg */
        uchar ata_error;        /* Return contents of ata/ide error reg */
        uchar rsv0;             /* reserved, should be set to zero */
        uchar rsv1;             /* reserved, should be set to zero */
	struct atapi_command atapi_cmd;	/* space for atapi command */

        /* The following 2 field will only be valid if the rsv0 field is
         * Set to indicate version01 of the passthru structure. If the rsv0
         * field is set to IDE_PASSTHRU_VERSION01 */
      
        int sense_data_length; /* Length of sense data required */
        uchar *sense_data;     /* Buffer allocated by caller for */
};

/* struct for issuing a SATAPASSTHRU ioctl */
struct sata_passthru {
      uint    version;                  /* version of structure               */
      uchar   flags;
#define SATA_PASSTHRU_READ 0x04         /* Direction of data transfer         */
      uchar   xfer_flag;                /* flags for data transfers           */
                                        /* see struct ataide_buf for xfer_flag
                                           defintions                         */
      ushort  adapter_set_flags;        /* flags set by the adapter           */
      unsigned long long buffsize;
      unsigned long long resid;
      unsigned long long sata_address;  /* 64 Bit Address field used 
                                             to address SATA devices.         */
      uint    timeout_value;            /* timeout value for passthru command */
      uchar   status_validity;          /* validity of status and error flags 
                                         * flags defined in struct ataide_buf */
      uchar   ata_status;               /* returned ata status value          
                                         * flags defined in struct ataide_buf */
      uchar   ata_error;                /* returned ata error value           
                                         * flags defined in struct ataide_buf */
      uchar   rsv0;                     /* reserved, should be set to 0       */
      uchar   *data_ptr;                /* data buffer used for data transfers*/
      struct ata_cmd     ata_cmd;       /* supports both ata and atapi cmds   */
      struct ata_cmd_ext ata_cmd_ext;   /* fields used for extended ata cmds  */
};

/* SATAIOSTART, and SATAIOSTOP
 * struct for issuing start, stop, and resets to SATA device
 */
struct sataiost {
        uchar  version;
        uchar  rsv0;                    /* reserved should be set to zero   */
        ushort flags;
        uint   rsv1;                    /* reserved should be set to zero   */
        unsigned long long sata_address;
        unsigned long long kernext_handle;
};

 /*
   Vendor specific (Microcode download) structure
   passed by pointer to ioctl of adapter driver
  */
struct ide_vendor_specific {
        uchar ide_device;       /* target device id */
        uchar flags;            /* flags:  see 'flags' in struct ata_cmd */
        uint buffsize;          /* Size in bytes of command/data buffer. */
        uint  timeout_value;    /* timeout value in seconds, for command. */
        uchar *data_ptr;        /* pointer to buffer with microcode. */
        uchar ata_status;       /* Return contents of the ata/ide status reg */
        uchar ata_error;        /* Return contents of ata/ide error reg */
        uchar vendor_code;      /* Specific vendor/product to be accessed. */
        uchar vendor_function;  /* Specific action to be performed. */
	uint  reserved1;	/* Reserved - should be 0.  */
};

 /*
  ATA/IDE Start Unit structure passed by pointer to ioctl of adapter driver
  */
struct ide_startunit  {
	uchar ide_device;	/* target device id */
	uchar flags;		/* flags:  see 'flags' in struct ata_cmd */
	uchar start_flag;	/* must be set to TRUE for starting, */
				/* FALSE to stop device */
	uchar immed_flag;	/* if set to TRUE, command completes */
				/* immediately (if supported by device) */
				/* if FALSE, command does not return until */
				/* device has completed the command. */
	uint   timeout_value;	/* timeout value for command, in secs. */
};

 /*
  ATA/IDE Test Unit Ready structure passed by pointer to ioctl of adapter driver
  */
struct ide_ready  {
	uchar ide_device;	/* target device id */
	uchar flags;		/* flags:  see 'flags' in struct ata_cmd */
	uchar rsv0;		/* reserved, should be set to zero */
	uchar status_validity;	/* 0 = no valid status             */
				/* 1 = valid ATAPI status only     */
	uchar tur_data[128];	/* ATA errors (if valid)           */
};

 /*
  Download structure passed by pointer to ioctl of adapter driver
  Used to download "ata/ide adapter" microcode (not ide device microcode).
  */
struct ide_download {
	uchar option;		/* download option flag, see below */
	uchar rsv1;		/* reserved, should be set to zero */
	uchar rsv2;		/* reserved, should be set to zero */
	uchar rsv3;		/* reserved, should be set to zero */
	uint microcode_len;	/* length of microcode in bytes, includes
				   padding to 1 kilobyte boundary */
	uchar *microcode_ptr;	/* pointer to system memory address
				   of microcode to be downloaded, NULL
				   if requesting Version */
	uint version_number;	/* returned version number if requested,
				   or undefined if download */
	uint  rsv4;		/* reserved, should be set to zero */
};
/* download options */
#define ATA_DOWNLOAD		1	/* download the microcode */
#define ATA_VERSION_NUMBER	2	/* return version number of
					   current microcode */
/*
  structure passed by pointer to IDEIOEVENT ioctl of adapter driver
*/

struct	ide_event_struct {
	uchar   ide_device;	/* target device id */
	uchar   resvd0;		/* reserved, should be set to zero */
	uchar   resvd1;		/* reserved, should be set to zero */
	uchar	resvd2;		/* reserved, should be set to zero */
	uint	resvd3;		/* reserved, should be set to zero */
	uint	async_correlator;	/* optional field for use by caller.
                                           value in this field is saved by
                                           adapter driver and passed back
                                           to caller's async func */
	void	(*async_func)();	/* device drivers's asynchronous
                                           event handler function address */
};

/*
  Diagnostic / Error Logging structure used by adapter driver
  */
struct  ataide_rc  {            /* adapter return code area      */
				/*   for all ATA/IDE adapters:   */
	uchar diag_validity;	/*   = 0x00 diag_stat invalid    */
				/*   = 0x01 diag_stat valid      */
	uchar ahs_validity;	/*   = 0x00 AHS invalid          */
				/*   = 0x01 AHS = Driver Status  */
	uchar diag_stat;	/* Diagnostic Status (0 when     */
				/*  error logging)               */
	uchar ahs;		/* Additional Hardware Status    */
				/* (lsb)	(AHS)            */
				/*  Driver Status:               */
				/*  Note: at most, only one of   */
				/*    the following will be set  */
				/*    when the AHS is valid.     */
#define PIO_RD_OTHR_ERR 0x01    /* Other error on PIO Read op    */
#define PIO_WR_OTHR_ERR 0x02    /* Other error on PIO Write op   */
#define DMA_ERROR	0x10	/* Error during DMA transfer     */
#define UNKNOWN_CARD_ERR 0x20   /* An unknown card error occured */
#define CARD_INTRPT_ERR 0x40	/* An invalid interrupt occured  */
#define COMMAND_TIMEOUT	0x80    /* A command timeout occured     */

	uint sys_rc;		/* failed system call return code*/
	union {
		struct {
                        uint  errnum;
			struct ata_cmd ata; /* original command         */
			uchar cmd_activity_state;
			uchar error_reg;
			uchar seccnt_reg;
			uchar secnum_reg;
			uchar cyllow_reg;
			uchar cylhi_reg;
			uchar drvhd_reg;
			uchar status_reg;
		} card1;
	} un;
};

/*
  Diagnostic structure passed by pointer to ioctl of adapter driver
  */
struct ataide_card_diag  {
	uchar  option;           /* diagnostic option, see below  */
	uchar  rsv1;		 /* reserved, should be set to zero */
	uchar  rsv2;		 /* reserved, should be set to zero */
	uchar  rsv3;		 /* reserved, should be set to zero */
	uint   timeout_value;    /* timeout value for command, in secs. */
	uint   rsv4;		 /* reserved, should be set to zero */
	struct ataide_rc diag_rc; /* adapter return code structure */
				 /* see struct ataide_rc declaration */
};

/* option                  */
#define ATA_CARD_DIAGNOSTICS   SC_CARD_DIAGNOSTICS

/************************************************************************/
/* Disk Error Log Record format                                         */
/************************************************************************/

struct idedisk_error_rec {
	struct err_rec0		entry;		/* defined in sys/err_rec.h 20*/
	uchar			status_validity;/* valid values in sys/ide.h 1*/
	char			b_error;	/* copy of buf ptr b_error   1*/
	ushort			rsvd0;		/* reserved		     2*/
	int			b_flags;	/* copy of buf ptr b_flags   4*/
	caddr_t			b_addr;		/* copy of buf ptr b_addr    4*/
	uint			b_resid;	/* copy of buf ptr b_resid   4*/
	struct ata_cmd		ata;		/* failed command	    36*/
};

#endif /* _H_ATA_IDE */
