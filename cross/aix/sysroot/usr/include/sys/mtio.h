/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/mtio.h 1.5                                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2001,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)94       1.5  src/bos/kernel/sys/mtio.h, incstd, bos530 9/27/02 16:41:13 */
/*
 * Linux compatibility header.
 * Include sys/tape.h.
 * Define a struct mtop, which is same as the struct stop
 * in sys/tape.h.
 */

#ifndef	_H_MTIO
#define	_H_MTIO

#ifdef _LINUX_SOURCE_COMPAT

#include <sys/types.h>
#include <sys/tape.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mtop {
	short	st_op;		/* operations defined in sys/tape.h */
	daddr_t	st_count;	/* how many of them */
};

/*
 * Map AIX functions to Linux names.
 */
#define MTOFFL		STOFFL		/* Rewind and offline */
#define MTREW		STREW		/* Rewind */
#define	MTERASE		STERASE		/* Erase tape */
#define	MTRETEN		STRETEN		/* Retension tape */
#define	MTWEOF		STWEOF		/* Write EOF */
#define	MTFSF		STFSF		/* Forward space filemark */
#define MTBSF		STRSF		/* Backward space filemark */
#define	MTFSR		STFSR		/* Forward space record */
#define MTBSR		STRSR		/* Backward space record */
#define MTLOAD		STINSRT		/* Load tape */
#define	MTUNLOAD	STEJECT		/* Eject tape */

#ifdef __cplusplus
}
#endif

#else	/* _LINUX_SOURCE_COMPAT */

/*
 *   Change Activity
 *
 *    Date     Who         Reason
 *    -------- ----------- ---------------------------------------------------
 *    02/27/99 airola      Create file.  Modified from the original for PCI
 *                         Snow Goose project.
 *    05/20/99 airola      Added IOCTL command to change trace levels, as per
 *                         defect 275242.
 *    07/09/99 airola      Modified search path for including mtextend.h, as
 *                         per defect 280907.
 *
 */


/*****************************************************************************/
/*                                                                           */
/*  COMPONENT_NAME: (MTIO.H) Magnetic Tape User Include File                 */
/*                                                                           */
/*  FUNCTIONS: NONE                                                          */
/*                                                                           */
/*  (C) COPYRIGHT International Business Machines Corp. 1988, 1989           */
/*  All Rights Reserved                                                      */
/*  Licensed Materials - Property of IBM                                     */
/*                                                                           */
/*  US Government Users Restricted Rights - Use, duplication or              */
/*  disclosure restricted by GSA ADP Schedule Contract with IBM Corp.        */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  This file is intended for use with devices which are driven by the       */
/*  magnetic tape device driver which is part of AIX/ESA | AIX/RS6000        */
/*                                                                           */
/*  Note: the symbols that start with "mt" are the normal symbols.           */
/*        the symbols that start with "st" are for compatibility with        */
/*        small systems (stands for "streaming tape," in its small           */
/*        system context).                                                   */
/*                                                                           */
/*****************************************************************************/
#include <sys/types.h>
#include <sys/tape.h>

#ifndef _MTEXTEND_H
  #include <sys/mtextend.h>
#endif

/*
 * 4-byte recording format code which uniquely identifies a recording
 * format, as defined by AIX/ESA | AIX/RS6000
 */
typedef  int     recfmt_t;

/*****************************************************************************/
/*                                                                           */
/*      VARIOUS CONSTANTS FOR TAPE IOCTL'S                                   */
/*                                                                           */
/*****************************************************************************/

/*
 *  Constants for mt_type byte
 */
#define MT_ISTS 01
#define MT_ISHT 02

#define LDMAXMSGLN 8

/*
 * LDDISP Function codes
 */
#define LDMOTION   0
#define LDREMOVE   32
#define LDLOAD     64
#define LDNOOP     96
#define LDALL      225
#define LDSINGLE   0
#define LDDOUBLE   16
#define LDBLINK    8
#define LDNOBLINK  0
#define LDLOW      0
#define LDHIGH     4
#define LDAUTOLD   1
#define LDNOAUTOLD 0

/*
 * High end tape devices.
 */
#define IBM_3420                1       /* IBM 3420      */
#define IBM_3422                2       /* IBM 3422      */
#define IBM_3430                3       /* IBM 3430      */
#define IBM_3480                4       /* IBM 3480/3490 */
#define IBM_3490                5       /* IBM 3490E     */


/*
 * operations for the MTIOCTOP - mag tape op command
 */
#define ST_LOAD       21      /* Load volume           */
#define ST_FLUSH      22      /* Flush buffer to media */
#ifndef STERASEGAP
  #define STERASEGAP  35
#endif
#ifndef STTUR
  #define STTUR       30
#endif
#define MTWTM   STWEOF       /* write a tape mark    */
#define MTWEOF  MTWTM        /* write a tape mark    */
#define MTFSF   STFSF        /* forward space file   */
#define MTBSF   STRSF        /* backward space file  */
#define MTFSB   STFSR        /* forward space block  */
#define MTFSR   MTFSB        /* forward space block  */
#define MTBSB   STRSR        /* backward space block */
#define MTBSR   MTBSB        /* backward space block */
#define MTREW   STREW        /* rewind               */
#define MTRUN   STOFFL       /* rewind unload        */
#define MTOFFL  MTRUN        /* rewind unload        */
#define STNOP   99
#define MTNOP   STNOP        /* no-op                */
#define MTERG   STERASEGAP   /* erase record gap     */
#define MTTUR   STTUR        /* test unit ready      */

/*
 * 4-byte recording format codes returned by MTIOCFMQ ioctl
 * in "long formats[]" of "struct mtfmqret".
 */

#define  MT_NRZI            0x01000000     /* NRZI format           */
#define  MT_PE              0x02000000     /* PE  format            */
#define  MT_GCR             0x03000000     /* GCR format            */
#define  MT_3480_BAS        0x04000000     /* 3480 basic            */
#define  MT_3480_COMP       0x04800000     /* 3480 compacted        */
#define  MT_3490_BAS        0x05000000     /* 3490 basic            */
#define  MT_3490_COMP       0x05800000     /* 3490 compacted        */

/*
 * 4-byte recording format codes returned by MTIOC_GET_DEVICE_INFO
 * in "read_formats" and "write_formats" of "struct mt_get_device_info",
 * and in "format_loaded" of "struct mt_get_medium_info".
 */
#define IBM_NRZI_FMT            0x10000000         /* NRZI format    */
#define IBM_PE_FMT              0x20000000         /* PE format      */
#define IBM_GCR_FMT             0x40000000         /* GCR format     */
#define IBM_3480BAS_FMT         0x80000000         /* 3480 basic     */
#define IBM_3480COMP_FMT        0x01000000         /* 3480 compacted */
#define IBM_3490BAS_FMT         0x02000000         /* 3490 basic     */
#define IBM_3490COMP_FMT        0x04000000         /* 3490 compacted */

/*
 * Basic media shape values that can be returned by the MTIOCMNT ioctl
 * system call.
 */
#define  MT_OPN_REEL         0x02
#define  MT_3480_CART        0x01

/*
 * medium_type values to be returned for MTIOC_GET_MEDIUM_INFO ioctl
 * NO_VOLUME_MOUNTED is defined in <sys/mt.h>
 */
#define IBM_CART_NO_LENGTH  0x0100 /* 3480/3490 No tape length identification */
                                   /* support                                 */
#define IBM_CART_SLT_CST    0x0110 /* 3490E Short Length Tape or CST          */
#define IBM_CART_MLT_CST    0x0150 /* 3490E Marginal Length Tape and the tape */
                                   /* had been previously initialized as CST  */
                                   /* or is void                              */
#define IBM_CART_EC_CST     0x0190 /* 3490E EC-CST                            */
#define IBM_CART_TTLT       0x01B0 /* 3490E Too-Long Length Tape              */
#define IBM_CART_MLT_EC_CST 0x01D0 /* 3490E Marginal Length Tape and the tape */
                                   /* had been previously initialized as      */
                                   /* EC-CST                                  */
#define IBM_REEL            0x0200 /* Reel tape                               */

/*
 * Defines for "reason_failed" used in MTIOCLDF ioctl
 */
#define MT_LAST_CLR         0x00000000  /* Clear last fail/No last fail  */
                                        /* history flags set.            */
#define MT_LOST_POS         0x00000001  /* Lost position - Volume fenced */
                                        /* Tape position is undefined.   */
#define MT_LOST_MNT         0x00000002  /* Lost volume - lost mount cntl */
                                        /* Volume mounted on device is   */
                                        /* no longer defined. (Manually  */
                                        /* unloaded volume for example). */

#define DEV_PW_SZ         11

/*
 * C macros for the Completion Codes returned by some AIX/ESA ioctl
 * system calls.  The first 4-bytes of each return information area
 * returned by some AIX/ESA ioctl system calls is a completion code.
 * This is a hierarchical completion code with 4 levels -- one byte
 * per level.
 */
#define  SUCCESS              0x00000000      /* System call successful    */
#define  FAILED_IO            0x01010000      /* I/O failed                */
#define  INVALID_FMT          0x02010000      /* Device not capable of     */
                                              /* writing the specified fmt */
#define  NOT_LBOV             0x02020000      /* Tape not positioned at    */
                                              /* LBOV when it should be    */
#define  NOT_READY            0x03010000      /* Device not ready          */
#define  ELSE_WHERE           0x03020000      /* Device assigned elsewhere */
#define  INVALID_LEN          0x04010000      /* Argument body length is   */
                                              /* too small                 */
#define  INVALID_FMT_CODE     0x04020000      /* Recording fmt code value  */
                                              /* specified is not a valid  */
                                              /* recording format          */
#define  INVALID_BLK_SIZE     0x04030000      /* Block size value          */

/*
 * C macros for the first level of the completion codes returned by some
 * AIX/ESA ioctl system calls.  Refer to the completion codes defined above.
 */
#define IOCTL_SUCCESS        0x00  /* ioctl system call was successful       */
#define EXCEPT_SYS_COND      0x01  /* exceptional system conditions exist    */
#define FMT_NOT_POSSIBLE     0x02  /* impossible to select the specified     */
                                   /* recording format                       */
#define DEV_INVALID_STATE    0x03  /* the device is in an invalid state      */
#define ARG_INVALID          0x04  /* The argument body is lexically invalid */

/******************************************************************************
 *
 *      ARGUMENT AND RETURN INFORMATION STRUCTURES FOR TAPE IOCTL'S
 *
 *****************************************************************************/
/*
 * The following structure definitions that are used with the ioctl
 * system calls MTIOCFMS, MTIOCFMQ, MTIOCRST, MTIOCMNT, are for
 * type B ioctl system calls only.
 */

/*
 * The ioctl argument is a pointer to the 3rd parameter passed to an
 * ioctl system call.  The argument is divided into a header and a body
 * as follows:
 *     Bytes 0-B    Header
 *     Bytes 0-3    Length in bytes of the body of the argument
 *     Bytes 4-7    Address of return information area
 *     Bytes 8-B    Length in bytes of the return information area
 *     Bytes C-?    Body (may not exist, i.e. have zero length)
 */

/*
 * Header part of the argument passed to a type B ioctl system call.
 * Note, the third parameter is a pointer to the argument of the ioctl
 * system call.  The length field tells how long the body of the argument
 * is, the return address field tells where the return information
 * from the ioctl system call is to be stored, and the return
 * length field tells how long the return information area is.
 */
struct    mtiochdr {
           int       body_length;       /* Body length of argument    */
           int       *ret_addr;         /* Address of return info area*/
           int       ret_len;           /* Length of return info area */
};

/*
 *  structure for MTIOCFMQ - return a list of recording formats
 *  the device is capable of writing.  This structure defines the
 *  argument passed to the MTIOCFMQ ioctl system call.  It is made
 *  up of the header of the argument as defined by the structure
 *  "mtiochdr" and an argument body.  The body of the argument consists
 *  solely of a  field reserved for downward compatibility.  The
 *  downward compatibility field must be zero.
 */
struct   mtfmqarg {
          struct mtiochdr  hdr;
          int              version;
};

/*
 * Passed to the MTIOCFMQ ioctl system call, in the header part of the
 * argument, are the return information address and length.
 * The "mtfmqret" data structure defines the return information
 * area AIX/ESA returns after an MTIOCFMQ ioctl system call when
 * the return code is 0 or errno is EIO.  The fields are defined
 * as follows:
 *       Bytes 0-3  A hierarchical completion code, split into w levels
 *       Bytes 4-7  Reserved for upward compatibility -- zero
 *       Bytes 8-B  Number of recording formats the device is capable
 *                  of writing.
 *       Rest       Sequence of 4-byte recording format codes.  Each
 *                  code uniquely identifies a recording format as
 *                  defined by AIX/ESA.  If completion code indicates
 *                  failure(not 0), this field doesn't exist.
 */
struct   mtfmqret {
          int       cc;
          int       up_comp;
          int       n_fmt;
          long      formats[2];
};


/*
 *  structure for MTIOCFMS - set the "current recording format"
 *  This structure defines the argument passed to the MTIOCFMS
 *  ioctl system call.  It is made up of the header of the argument
 *  as defined by the structure "mtiochdr" and an argument body.
 *  The body of the argument consists of a field reserved for
 *  downward compatibility and a field defining a 4-byte recording
 *  format code which uniquely defines a recording format defined
 *  by AIX/ESA.  The downward compatibility field must be zero.
 */
struct   mtfmsarg {
          struct mtiochdr  hdr;
          int              version;
          recfmt_t         rec_fmt;
};


/*
 * Passed to the MTIOCFMS ioctl system call, in the header part of the
 * argument, are the return information address and length.
 * The "mtfmsret" data structure defines the return information
 * area AIX/ESA returns after an MTIOCFMS ioctl system call when
 * the return code is 0 or errno is EIO.  The fields are defined
 * as follows:
 *       Bytes 0-3  A hierarchical completion code, split into 4 levels
 *       Bytes 4-7  Reserved for upward compatibility  -- zero
 *       Bytes Rest depends of completion code.
 *
 *       If the completion code does not indicate I/O failure, there
 *       does not exist any more return information. (8 bytes)
 *
 *       If the completion code indicates abnormal I/O failure,
 *       (0x'0101xxxx') the remainder of the return information is
 *       defined as follows:
 *             Byte  8   Unit status byte associated with failure
 *             Byte  9   Channel status byte associated with failure
 *             Bytes A-29 If failure associated with unit check, this
 *                        is the sense data associated with the unit
 *                        check.
 */
struct   mtfmsret {
          int       cc;
          int       up_comp;
          unsigned char unit_stat;
          unsigned char chan_stat;
          char      sense[32];
};


/*
 * Structure for MTIOCMNT - Get information about the current mount.
 * This structure defines the argument passed to the MTIOCMNT ioctl
 * system call.  It is made up of the header of the argument as
 * defined by the structure "mtiochdr" and an argument body.  The
 * body of the argument consists of a field reserved for downward
 * compatibility.  The downward compatibility field must be zero.
 */
struct  mtmntarg {
         struct mtiochdr  hdr;
         int              version;
};

/*
 * Struct "media_type is the media type code.  This code tells
 * the kind of media that is currently mounted.
 */
struct  media_t {
         unsigned int    undef  : 21;  /* undefined           */
         unsigned int    shape  : 3;   /* basic media shape   */
         unsigned int    length : 8;   /* media length        */
};

/*
 * Passed to the MTIOCMNT ioctl system call, in the header part of the
 * argument, are the return information address and its length.
 * The "mtmntret" data structure defines the return information
 * area AIX/ESA returns after an MTIOCMNT ioctl system call when
 * the return code is 0 or errno is EIO.  The fields are defined
 * as follows:
 *       Bytes 0-3  A hierarchical completion code, split into 4 levels
 *       Bytes 4-7  Reserved for upward compatibility  -- zero
 *       Bytes 8-11 Media type code:
 */
struct  mtmntret {
         int       cc;
         int       up_comp;
         struct    media_t media_type;
};


/*
 *  structure for MTIOCRST - reset the device image to a basic
 *  known state.  Until now, the only particular part of the device
 *  image that gets reset is the "current recording format" .  In
 *  the future, function may be added to reset more. This structure
 *  defines the argument passed to the MTIOCRST ioctl system call.
 *  It is made up solely of the header of the argument as defined by the
 *  structure "mtiochdr".
 */
struct   mtrstarg {
          struct    mtiochdr  hdr;
};

/*
 * Passed to the MTIOCRST ioctl system call, in the header part of the
 * argument, are the return information address and length.
 * The "mtrstret" data structure defines the return information
 * area AIX/ESA returns after an MTIOCRST ioctl system call when
 * the return code is 0 or errno is EIO.  The fields are defined
 * as follows:
 *       Bytes 0-3  Completion code, This is always x'00000000'
 *                  Note: future levels of AIX/ESA, it may have other
 *                        values
 *       Bytes 4-7  Reserved for upward compatibility -- zero
 */
struct   mtrstret {
          int       cc;
          int       up_comp;
};

/*****************************************************************************/
/*
 * structure for MTIOCGET - magnetic tape get status command
 */
struct mtget {
  short   mt_type;        /* type of magtape device           */
  short   mt_dsreg;       /* ``drive status'' register        */
  short   mt_erreg;       /* ``error'' register               */
  ushort  mt_resid;       /* residual count                   */
  daddr_t mt_fileno;      /* file number of current position  */
  daddr_t mt_blkno;       /* block number of current position */
};

/*
 *************************
 **
 ** MTIOC_DISPLAY_MSG
 **
 *************************
 * Structure definition for the MTIOC_DISPLAY_MSG ioctl command.
 * This ioctl is used to display a message on the operator's message
 * display.
 */
#ifndef _MT_DISPLAY_MSG
#define _MT_DISPLAY_MSG

#define LDMAXMSGLN      8

struct ldcmd {
   char ld_func;                           /* Function Code */
   char ld_msg1[LDMAXMSGLN];
   char ld_msg2[LDMAXMSGLN];
};

/*
 * io control command for the ioctl system call that does a display
 * operation.
 */
#define MTIOCLD   (('m'<<8)|3)

#endif  /* _MT_DISPLAY_MSG */

#define MTIOC_DISPLAY_MSG       MTIOCLD

/*
 * The Function Code (ld_func) in ldcmd structure is made up of a Function
 * Select * and a Message Control.  To select a Function Code, bit-wise OR one
 * of the Function * Select values with one of the Message Control values
 * defined below.
 */

/*** Function Select ***/

#define GENERAL_STATUS_MSG  0x00 /* General Status Message
                            * Message 1 and/or Message 2 is displayed as
                            * specified by the Message Control field, until
                            * the drive initiates tape motion or the message
                            * is updated with a new message.
                            */

#define DEMOUNT_MSG         0x20 /* Demount Message
                            * Message 1 and/or Message 2 is displayed as
                            * specified by the Message Control field, until
                            * the current volume is unloaded.  If the device
                            * is currently unloaded, the message display is
                            * not changed.
                            */

#define MOUNT_ACTION_MSG    0x40 /* Mount with Action Indicator Message
                            * Message 1 and/or Message 2 is displayed as
                            * specified by the Message Control field, until
                            * the device is loaded.  If the device is
                            * currently loaded, the message display is not
                            * changed.  The attention indicator is activated.
                            */

#define DMNT_MNT_ACTION_MSG 0xE0 /* Demount/Mount with Action Indicator Message
                            * Message 1 is displayed until the currently
                            * mounted volume, if any, is unloaded.  Message 2
                            * is displayed as specified by the Message Control
                            * field from the time the device is unloaded
                            * (or immediately if the drive is already unloaded)
                            * until another volume is loaded.  The attention
                            * indicator is activated.
                            */

/*** Message Control ***/

#define DISPLAY_MSG1    0x00    /* Display Message 1                 */
#define DISPLAY_MSG2    0x04    /* Display Message 2                 */
#define FLASH_MSG1      0x08    /* Flash Message 1                   */
#define FLASH_MSG2      0x0C    /* Flash Message 2                   */
#define ALT_MESSAGES    0x10    /* Alternate Message 1 and Message 2 */

/*
 * Structure for MTIOCTOP - mag tape op command
 */
struct mtop {
        short   mt_op;      /* operations defined below */
        daddr_t mt_count;   /* how many of them         */
};

/*
 * typedef for MTIOCRDBLKID and MTIOCLOCATE ioctl's
 */
typedef struct blockid {
        unsigned reserved:   1,     /* not currently used      */
                 segnumber:  7,     /* tach count id           */
                 formatmode: 2,     /* uncompressed,compressed */
                 logblock:   22;    /* logical block number    */
};

typedef unsigned int block_id;

#define MTMAXBL  64                            /* buffered log data length   */
#define MTSRBLOP _IOWR('m',0x2D,struct mtsrbl) /* sense or read buffered log */
#define MTSNSOP  1                             /* sense request              */
#define MTRBLOP  2                             /* read buffered log request  */

struct mtsrbl {
        int     resvd;                         /* Reserved                   */
        int     versn;                         /* Version Number field       */
        char    mtsrblinfo[MTMAXBL];           /* Buffered log/sense data    */
        short   mtsrblct;                      /* Length of data returned    */
        char    mtsrblop;                      /* request code: sense or rbl */
};


struct mtrdbuf {
        char   *buffer;                        /* Pointer to buffer          */
        ulong   len;                           /* Length of buffer           */
        ulong   ret_len;                       /* Length of data returned    */
};

/*
 * ioctl define for last-fail history query call MTIOCLDF
 *
 * MTIOCLDF is a ioctl call that allows the user to query a failure history
 * field (reason_failed) defined below. This will allow the user to access
 * mount and position status for a tape device after the device has been
 * accessed to insure mount and position integrity.
 */
struct mtldfarg {
        int     resvd;            /* reserved                           */
        int     versn;            /* Version number field               */
        int     reason_failed;    /* Reason for most recent I/O failure */
};

/*
 * This section defines the MTQUERYPW ioctl structure...
 *
 * MTQUERYPW is an ioctl call that allows the user to query an tapes device's
 * path access password that has been generated by the host's CPU address
 * and ID.  This password is generated and bound to a tape device whenever a
 * ASSIGN ioctl call is issued and reverts to a undefined state if the UNASSIGN
 * ioctl call is invoked on the tape device.
 */

struct mtqrypwret {
        int     up_comp;                /* Upward compatibility - reserved */
        unsigned char device_passwd[DEV_PW_SZ];
};

struct mtqrypwarg {
        int     resvd;                      /* reserved               */
        int     versn;                      /* Version number field   */
        struct  mtqrypwret  mtqrypwret;     /* Return info. struct    */
};

/*************************************************************************/
/* Structures describing log record                                      */
/*************************************************************************/
struct mt_logfile_header
  {
  char owner[16];             /* module that created the file */
  time_t when;                /* time when file created */
  unsigned long count;        /* # of entries in file*/
  unsigned long first;        /* entry # of first entry in wrap queue */
  unsigned long max;          /* maximum # of entries allowed before wrap*/
  unsigned long size;         /* size in bytes of entrys,entry size is fixed*/
  };
struct mt_log_record_header
  {
  time_t when;                /* time when log entry made */
  ushort type;                /* log entry type */
  char device_type[8];        /* device type that made entry */
  char volid[16];             /* volume id of entry */
  char serial[12];            /* serial number of device */
  char reserved[12];          /* serial number of device */
  };


#define LOG_SENSE_3480       8
#define LOG_SENSE_3490       9

/******************************************************************************
 *
 *      MACROS FOR TAPE IOCTL'S REQUESTS
 *
 *****************************************************************************/
/*
 * io control command for the ioctl system call that returns a list of
 * recording formats the device is capable of writing.
 */
#define MTIOCFMQ  (('m'<<8)|6)

/*
 * io control command for the ioctl system call that sets the current
 * recording format which will affect future writes to the device.
 */
#define MTIOCFMS  (('m'<<8)|5)

/*
 * io control command for the ioctl system call that gets magnetic
 * tape status
 *
 * This ioctl value changed for AIX v5, adding in the 0x10000.  The
 * code will respond to both the old and the new ioctl value.  If
 * the caller uses the new value, then it is assumed that the program
 * was compiled against AIX 5.1 which uses 64-bit daddr_t.  If the
 * program uses the old ioctl value, it is assumed that the program
 * was compiled against AIX 4.3 which used a 32-bit daddr_t.
 */
#define MTIOCGET  ((('m'<<8)|2) | 0x10000)

/*
 * io control command for the ioctl system call that does a display
 * operation.
 */
#define MTIOCLD   (('m'<<8)|3)

/*
 * io control command for the ioctl system call that gets information
 * about the current mount.  Specifically, it returns the type of
 * medium mounted.
 */
#define MTIOCMNT  (('m'<<8)|7)

/*
 * io control command for the ioctl system call that resets the device
 * image to a basic, known state.  The only part of the device image
 * that gets reset is the "current recording format"
 */
#define MTIOCRST  (('m'<<8)|0x0A) /* Reset device image sys call     */

/*
 * io control command for the ioctl system call that does a magnetic
 * tape operation.
 */
#define MTIOCTOP  STIOCTOP

/*
 * io control command for the ioctl system call that performs the read block
 * id function.
 */
#define MTIOCRDBLKID    (('m'<<8)|0xF0)
/*
 * io control command for the ioctl system call that performs the locate
 * id function.
 */
#define MTIOCLOCATE     (('m'<<8)|0xF1)

/*
 * io control command to assign device to a host.
 */
#define MTASSIGN        _IO('m', 0x28)

/*
 * io control command to unassign a deassign a device from a host.
 */
#define MTUNASSIGN      _IO('m', 0x29)

/*
 * io control command to obtain last device failure status
 */
#define MTIOCLDF        _IOWR( 'm', 0x30, struct mtldfarg)

/*
 * io control command to query a device's password
 */
#define MTIOCQRYPW      _IOWR( 'm', 0x43, struct mtqrypwarg)

/*
 * io control command to cause the tape subsystem to write
 * any buffered write data for the selected device on the
 * recording medium.
 */
#define MTIOCSYNC       _IO('m', 0x44)
/*
 * io control command to return the ESA device number for a device
 */
#define MTDEVICE        _IOR('m', 0x45, int)

/*
 * io control command to return the vital product data for the device
 */
#define MTVPD           _IOR('m', 0x46, int)

/*
 * io control command to control-assign device to a host.
 */
#define MTCASSIGN    (('m'<<8)|0x47)

/*
 * io control command to control-unassign a device from a host.
 */
#define MTCUNASSIGN  (('m'<<8)|0x48)

/*
 * io control command to read buffer from device
 */
#define MTIOCRDBUF   (('m'<<8)|0x49)

/*
 * io control command to invoke diagnostic control function (DCF)
 * for 3590A00 devices.
 */
#define MTIODCF      (('m'<<8)|0x4A)

/*
 * io control command to change the global trace variables trace, debug,
 * mttrace and mtdebug
 */
#define MTSETTRACE   (('m'<<8)|0x4B)

#endif	/* _LINUX_SOURCE_COMPAT */

#endif	/* _H_MTIO */
