/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/scsi.h 1.31.2.45                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)11       1.31.2.45  src/bos/kernel/sys/scsi.h, sysxscsi, bos53V, v2009_12B9 3/16/09 14:38:51 */

#ifndef _H_SCSI
#define _H_SCSI
/*
 * COMPONENT_NAME: (SYSXSCSI) IBM SCSI Header File
 *
 * FUNCTIONS: NONE
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 2008
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#include <sys/buf.h>
#include <sys/err_rec.h>
/*
  A simple subset of the ANSI SCSI command block opcodes:
  (in alphabetical order)
*/


#define SCSI_GET_CONFIGURATION      0x46
#define SCSI_FORMAT_UNIT            0x04
#define SCSI_INQUIRY                0x12
#define SCSI_LOG_SELECT             0x4C
#define SCSI_LOG_SENSE              0x4D
#define SCSI_MEDIUM_SCAN            0x38
#define SCSI_MODE_SELECT            0x15
#define SCSI_MODE_SELECT_10         0x55
#define SCSI_MODE_SENSE             0x1A
#define SCSI_MODE_SENSE_10          0x5A
#define SCSI_OPTICAL_ERASE          0x2C
#define SCSI_OPTICAL_ERASE_10       0xAC
#define SCSI_PAUSE_RESUME           0x4B
#define SCSI_PERSISTENT_RESERVE_IN  0x5E
#define SCSI_PERSISTENT_RESERVE_OUT 0x5F
#define SCSI_PLAY_AUDIO             0x45
#define SCSI_PLAY_AUDIO_EXT         0xA5
#define SCSI_PLAY_AUDIO_MSF         0x47
#define SCSI_PLAY_AUDIO_TRK_INDX    0x48
#define SCSI_PREVENT_ALLOW_REMOVAL  0x1E
#define SCSI_READ                   0x08
#define SCSI_READ_16                0x88
#define SCSI_READ_BUFFER            0x3C
#define SCSI_READ_CAPACITY          0x25
#define SCSI_READ_CD                0xBE
#define SCSI_READ_DEFECT_LIST       0x37
#define SCSI_READ_DISC_INFO         0x51
#define SCSI_READ_EXTENDED          0x28
#define SCSI_READ_HEADER            0x44
#define SCSI_READ_LONG              0xE8
#define SCSI_READ_SUB_CHANNEL       0x42
#define SCSI_READ_TOC               0x43
#define SCSI_REASSIGN_BLOCK            0x07
#define SCSI_RECEIVE_DIAGNOSTIC_RESULTS    0x1C
#define SCSI_RELEASE_UNIT           0x17
#define SCSI_RELEASE_UNIT_10        0x57
#define SCSI_REPORT_LUNS            0xA0
#define SCSI_REQUEST_SENSE          0x03
#define SCSI_RESERVE_UNIT           0x16
#define SCSI_RESERVE_UNIT_10        0x56
#define SCSI_REZERO_UNIT            0x01
#define SCSI_SEEK                   0x0B
#define SCSI_SEEK_EXTENDED          0x2B
#define SCSI_SEND_DIAGNOSTIC        0x1D
#define SCSI_SERVICE_ACTION_IN      0x9E
#define SCSI_SERVICE_ACTION_OUT     0x9F
#define SCSI_START_STOP_UNIT        0x1B
#define SCSI_TEST_UNIT_READY        0x00
#define SCSI_VERIFY                 0x2F
#define SCSI_WRITE                  0x0A
#define SCSI_WRITE_16               0x8A
#define SCSI_WRITE_AND_VERIFY       0x2E
#define SCSI_WRITE_AND_VERIFY_16    0x8E
#define SCSI_WRITE_BUFFER           0x3B
#define SCSI_WRITE_EXTENDED         0x2A
#define SCSI_WRITE_LONG             0xEA

/* tape commands (some are form of normal commands) */
#define SCSI_ERASE                  0x19
#define SCSI_LOAD                   0x1B
#define SCSI_READ_BLK_LIMITS        0x05
#define SCSI_REWIND                 0x01
#define SCSI_SPACE                  0x11
#define SCSI_UNLOAD                 0x1B
#define SCSI_VERIFY_TAPE            0x13
#define SCSI_WRITE_FILEMARK         0x10



/*
  A simple subset of the ANSI SCSI SERVICE ACTION
  IN codes (in alphabetical order)
  */
#define SCSI_READ_CAP16_SRV_ACT_IN  0x10



/*    
    Target mode read buffer info structure.  This is passed by
    pointer to the target mode device driver's recv_func routine.
    Fields which are reserved must not be written to by the target
    mode device driver.  Other fields may be modified, except where
    noted otherwise.
*/
struct    tm_buf {
    __ulong64_t    tm_correlator; /* same as that given to adap driver */
                                  /*  in call to SCIOSTARTTGT ioctl    */
    dev_t      adap_devno;        /* device major/minor of this adapter. */
                                  /*  DO NOT modify this field.        */
    caddr_t    data_addr;         /* kernel space addr where data begins */
    int        data_len;          /* length of valid data */
    ushort     user_flag;         /* except where noted, one or more of the
                                     following may be set: */
#define    TM_HASDATA      0x04   /* set if this is a valid tm_buf */
#define    TM_MORE_DATA    0x08   /* set if more data coming for the Send cmd */
#define    TM_ERROR      0x8000   /* set if any error occurred on this Send
                                    (mutually exclusive with TM_MORE_DATA) */
    uchar      user_id;           /* SCSI id which sent this data. */
                                  /*  DO NOT modify this field. */
    uchar      resvd1;            /* reserved for use by adapter driver */
    uchar      status_validity;   /* valid values below */
/* #define    SC_ADAPTER_ERROR    2    general_card_status is valid */
    uchar      general_card_status;    /* defined under struct sc_buf. */
                                  /*  Note that SC_CMD_TIMEOUT will not be */
                                  /*  returned in target mode */
    uchar    resvd2;              /* reserved for future expansion */
    uchar    resvd3;              /* reserved for future expansion */
    uchar    resvd4;              /* reserved for use by adapter driver */
    uchar    resvd5;              /* reserved for use by adapter driver */
    ushort   resvd6;              /* reserved for use by adapter driver */
    __ulong64_t   resvd7;         /* reserved for use by adapter driver */
    __ulong64_t   resvd8;         /* reserved for use by adapter driver */
    __ulong64_t   resvd9;         /* reserved for use by adapter driver */
    __ulong64_t   resvd10;        /* reserved for use by adapter driver */
    __ulong64_t   resvd11;        /* reserved for use by adapter driver */
    __ulong64_t   resvd12;        /* reserved for use by adapter driver */
    struct    tm_buf *next;       /* either NULL or link to next tm_buf */
    __ulong64_t   resvd13;        /* reserved for use by adapter driver */
    __ulong64_t   resvd14;        /* reserved for use by adapter driver */
    __ulong64_t   resvd15;        /* reserved for future expansion */
    __ulong64_t   resvd16;        /* reserved for future expansion */
    __ulong64_t   resvd17;        /* reserved for future expansion */
    __ulong64_t   resvd18;        /* reserved for future expansion */
};

/* refer to the SCSI ANSI X3.131-1986 standard for information */
struct sc_cmd {                 /* structure of the SCSI cmd block */
    uchar    scsi_op_code;      /* first byte of SCSI cmd block */
    uchar    lun;               /* second byte of SCSI cmd block */
    uchar    scsi_bytes[10];    /* other bytes of SCSI cmd block */
};

#define SC_16BYTE_CDB_MASK 0x80 /* group mask for 16 byte CDB op codes */

struct scsi {
    uchar    scsi_length;       /* byte length of scsi cmd (6,10, or 12) */
    uchar    scsi_id;           /* the target SCSI ID */
    uchar    resvd;             /* reserved, should be set to zero */
    uchar    flags;             /* flags for use with the 
                                   physical scsi command */
#define SC_NODISC   0x80        /* don't allow disconnections */
#define SC_ASYNC    0x08        /* asynchronous data xfer */
    struct sc_cmd   scsi_cmd;   /* the actual SCSI cmd */
};

/*
  sc_buf structure used by SCSI device driver to communicate with
  the SCSI adapter driver.  This is passed to the adapter driver
  strategy routine entry point.
  */
struct sc_buf {
    struct buf    bufstruct;       /* buffer structure containing request
                                      for device */
    struct buf    *bp;             /* pointer back to original buffer
                                      structure list for command 
                                      coalescing */
    struct scsi   scsi_command;    /* the information relating strictly
                                      to the scsi command itself */
    __ulong64_t   resvd1;          /* when not zero it is a pointer to   
                                      uio struct for gathered writes  */
    __ulong64_t   target_driver_flags;/* Flags set by target device  */
                                   /* driver                         */
#define SC_SCSI_CDB16    0x1       /* Indicates 16-byte CDB in this    
                                      sc_buf, with the last 4 bytes in 
                                      the add_cdb_bytes field. */
    uchar  add_cdb_bytes[4];       /* Additional CDB bytes that are
                                      appended to end of the CDB bytes
                                      in the scsi_command structure.
                                      These bytes are only valid if
                                      the SC_SCSI_CDB16 flag is set. */
#ifdef  __64BIT_KERNEL
    uint   resvd3;                 /* reserved, should be set to zero */
#endif
    __ulong64_t    resvd4;         /* reserved, should be set to zero */
    uint    timeout_value;         /* timeout value for the command, 
                                      in units of seconds */
    uchar    status_validity;      /* least significant bit - scsi_status
                                      valid, next least significant bit -
                                      card status valid */
#define SC_SCSI_ERROR       1      /* scsi status reflects error */
#define SC_ADAPTER_ERROR    2      /* general card status reflects err */

    uchar    scsi_status;          /* returned SCSI Bus status */
#define SCSI_STATUS_MASK    0x1e   /* mask for useful bits */
#define SC_GOOD_STATUS      0x00   /* target completed successfully */
#define SC_CHECK_CONDITION  0x02   /* target is reporting an error, 
                                      exception, or abnormal condition */
#define SC_BUSY_STATUS      0x08   /* target is busy and cannot accept
                                      a command from initiator */
#define SC_INTMD_GOOD       0x10   /* intermediate status good when using
                                      linked commands */

#define SC_RESERVATION_CONFLICT 0x18 /* attempted to access a LUN which is
                                        reserved by another initiator */
#define SC_COMMAND_TERMINATED   0x22 /* Command has been terminated by
                                        the device. */
#define SC_QUEUE_FULL           0x28 /* Device's command queue is full */
#define SC_ACA_ACTIVE           0x30 /* The device has an ACA condition
                                        that requires a Clear ACA task 
                                        management request to clear. */
#define SC_TASK_ABORTED         0x40 /* The device has aborted a command */


    uchar  general_card_status;      /* generic SCSI adapter card status
                                        byte */
#define SC_HOST_IO_BUS_ERR      0x01 /* indicates a Host I/O Bus error 
                                        condition */
#define SC_SCSI_BUS_FAULT       0x02 /* indicates a failure of the SCSI Bus */
#define SC_CMD_TIMEOUT          0x04 /* the command did not complete before
                                        timeout_value units expired */
#define SC_NO_DEVICE_RESPONSE   0x08 /* the target device did not respond 
                                        to attempts to select it */
#define SC_ERROR_NO_RETRY       0x0e /* An error occured, do not retry      */
#define SC_ERROR_DELAY_LOG      0x0f /* An error occured, only log an       */
                                     /* error if max retries exceeded       */
#define SC_ADAPTER_HDW_FAILURE  0x10 /* the adapter is indicating a 
                                        hardware failure */
#define SC_ADAPTER_SFW_FAILURE  0x20 /* the adapter is indicating a 
                                        microcode failure */
#define SC_FUSE_OR_TERMINAL_PWR 0x40 /* the adapter is indicating a 
                                        blown fuse or bad termination */
#define SC_SCSI_BUS_RESET    0x80    /* the adapter detected an external 
                                        SCSI bus reset */

    uchar       adap_q_status;       /* adapter's device queue status. This*/
                                     /* specifies whether or not the SCSI  */
                                     /* adapter driver and SCSI adapter    */
                                     /* cleared their queues for this        */
                                     /* device or not.  A value of 0       */
                                     /* indicates that the queue has been  */
                                     /* cleared.               */
#define SC_DID_NOT_CLEAR_Q      0x1  /* SCSI adapter device driver has not */
                                     /* cleared its queue for this device  */
                                     /* nor has the SCSI adapter.       */

    uchar         lun;               /* This is the target's lun.  If the  */
                                     /* target's lun is greater than 7,this*/
                                     /* field must be used and the 3 lun   */
                                     /* bits (used as lun in SCSI-1) in the*/
                                     /* scsi_command will be ignored.       */
                    
    uchar         resvd7;            /* reserved, should be set to zero */

    uchar         q_tag_msg;        /* Queue Tag Message Field- Specifies */
                                    /* whether or not the SCSI device should */
                                    /* queue this command and if so what */
                                    /* type of queuing it should use.  */
#define SC_NO_Q             0x00    /* No queuing to this device.       */
#define SC_SIMPLE_Q         0x01    /* Simple Queuing.  The device can     */
                                    /* reorder the commands in its queue.  */
#define SC_HEAD_OF_Q        0x02    /* Put at Head of Device's Queue       */
#define SC_ORDERED_Q        0x03    /* Ordered Queuing.  The device can    */
                                    /* not reorder the commands in its     */
                                    /* queue.  However the system can      */
                                    /* still reorder commands.            */
#define SC_ACA_Q            0x04    /* ACA task attribute. The device      */
                                    /* will only accept one command with   */
                                    /* SC_ACA_Q set at a time, when it is  */
                                    /* in an ACA condition.  sc_bufs with  */
                                    /* this q_tag_msg can be used for      */
                                    /* error recovery prior to issuing a   */
                                    /* clear ACA request.                */
                             
    uchar        flags;             /* flags to SCSI adapter driver */
#define SC_RESUME           0x01    /* resume transaction queueing for this
                                      id/lun beginning with this sc_buf */
#define SC_DELAY_CMD        0x02    /* enable delaying this sc_buf following a 
                                       SCSI bus reset or host initiated BDR 
                                       message to device */
#define SC_Q_CLR            0x04    /* SCSI Device Head wants the adapter 
                                       to clear its queue for this device */
#define SC_Q_RESUME         0x08    /* SCSI Head wants the adapter to resume
                                       its queue for this device*/
#define SC_CLEAR_ACA        0x10    /* SCSI Device Head wants the adapter 
                                       driver to issue a Clear ACA task 
                                       request to this device */
#define SC_TARGET_RESET     0x20    /* SCSI Device Head wants the adapter 
                                       driver to issue a Target Reset task 
                                       request to this device */ 
#define SC_DEV_RESTART      0x40    /* SCSI Device Head wants the adapter 
                                       driver to STOP and reSTART device*/
#define SC_LUN_RESET        0x80    /* SCSI Device Head wants the adapter
                                       driver to issue a Lun Reset task
                                       request to this device */
};

/*
  global defines important to every SCSI device driver and adapter driver
*/
#define SC_MAXREQUEST        32768    /* this is the (minimum) maximum 
                                         transfer request size for a 
                                         single SCSI command, i.e., this
                                         is the smallest maximum and thus
                                         must be supported by all SCSI
                                         adapters.
                                       */
/* Modes for OPENX */
#define SC_RESERVED_DO_NOT_USE   0x100   /* Reserved for future use */
#define SC_PR_SHARED_REGISTER    0x80    /* Persistent Reserve shared policy */ 
                                         /* registration flag.               */ 
#define SC_FORCED_OPEN_LUN       0x40    /* use LUN-level reset to break  */
                                         /* any existing device reservation */
#define SC_SINGLE                0x20    /* Open for formatting media  */
#define SC_RESV_05               0x10    /* reserved for future use */
#define SC_NO_RESERVE            0x08    /* Don't reserve device on open */

#define SC_FORCED_OPEN           0x04    /* do not honor device reservation
                                            conflict status */
#define SC_RETAIN_RESERVATION    0x02    /* do not release SCSI device on
                                            close */
#define SC_DIAGNOSTIC            0x01    /* place device in diagnostic mode */


/*
 * calculate the elapsed time by subtracting the start tick counter from
 * the current tick counter (lbolt) and convert it to seconds
 */
#define SC_ELAPSED_TIME(s)     ((lbolt - s) / HZ)

/*
  Macros to handle internal IOCTL commands
  
  */

/*
  SCSI adapter driver IOCTL command options follow.
  Some of the internal IOCTL commands passed to the SCSI adapter driver
  by the SCSI device drivers are invoked with code similar to:
  
  ddioctl(fd,SCIOSTART,IDLUN(scsi_id,scsi_lun));
  */

#define SCIOSTART   999    /* cause adapter driver to allocate internal
                              resources for the IDLUN device */
#define SCIOSTOP    998    /* cause adapter driver to release internal
                              resources for the IDLUN device */
#define SCIOHALT    997    /* cause adapter driver to abort all commands
                              currently running or pending until a
                              transaction with the SC_RESUME bit is set
                              in sc_buf.flags */
#define SCIOINQU    996    /* cause adapter driver to run a SCSI device
                              inquiry command to the IDLUN device. For
                              this operation, you must specify the "arg"
                              parameter with the address of a data area
                              which is defined by the sc_inquiry 
                              structure */
#define SCIORESET    995    /* cause adapter driver to issue a SCSI bus 
                               device reset (BDR) message to the SCSI ID
                               selected.  The LUN in this case must be
                               a LUN on this SCSI ID which was previously
                               started via SCIOSTART */
#define SCIODIAG     994    /* run adapter diagnostics */
#define SCIOTRAM     993    /* run adapter buffer ram diagnostic */
#define SCIODNLD     992    /* download microcode to the adapter */
#define SCIOSTUNIT   991    /* cause adapter driver to run a SCSI device
                               start unit command to an id/lun.  The "arg"
                               parameter specifies the address of the data
                               area defined by the sc_startunit 
                               structure */
#define SCIOTUR      990    /* cause adapter driver to run a SCSI device
                               test unit ready command to an id/lun.  The
                               "arg" parameter specifies the address of
                               the data area defined by the sc_ready
                               structure */
#define SCIOREAD     989    /* cause adapter driver to run a SCSI device
                               read command to the IDLUN device to read
                               a single block.  For this operation, you
                               must specify the "arg" parameter with the
                               address of a data area which is defined
                               by the sc_readblk structure */

#define SCIOEVENT    988    /* registers an async event notification 
                               with the adapter driver for this device */

#define SCIOSTARTTGT 987    /* cause adapter driver to allocate resources
                               and enable buffers and ids for target mode
                               devices */

#define SCIOSTOPTGT  986    /* cause adapter driver to release target
                               mode resources */
#define SCIOHALTTGT  SCIOSTOPTGT
#define SCIOGTHW     985     /* returns 0 if gathered write is supported */
#define SCIOLUNRST   984     /* cause adapter driver to issue a LUN reset to
                                a particular id/lun */


#define SCIOCMD      983     /* Causes the adapter driver to issue the 
                                SCSI command contained in the sc_passthru 
                                argument to the id/lun. For this operation
                                you must specify the "arg" parameter with 
                                the address of the data area which is 
                                defined by the sc_passthru structure  */


/*****************************************************************************/
/*  Version numbers of structures in this file.				     */
/*****************************************************************************/

#define SC_VERSION_0	 0x00           /* First version of the structure.*/
#define SC_VERSION_1	 0x01           /* Second version of the structure.*/
#define SC_VERSION_2	 0x02           /* Third version of the structure.*/


/* IDLUN builds the combination of the scsi id and scsi lun
   value required for SCIOSTART and similar ioctl's used
   by the SCSI device drivers when communicating with the
   SCSI adapter driver.
   (i) is the target SCSI ID value (0-15);
   (l) is the LUN value for the selected target SCSI ID.
   */
#define    IDLUN(i,l)    (__long64_t) ( ( ( (i) & 0x0F ) << 8 ) | ( (l) & 0x3F) )


/*
  Definitions for SCSI device driver to application level tasks.
  */

/*
  SCSI Read/Write with Sense Ioctl Structure
  */
struct sc_rdwrt {
    uint    logical_blk_addr;    /* Logical block address
                                    (0 for sequential devices) */
    uint    data_length;         /* Data transfer length in bytes */
    char    *buffer;             /* Pointer to data transfer buffer */
    uchar   adap_q_status;       /* used to return back whether or  */
                                 /* or not the SCSI adapter driver  */
                                 /* and SCSI adapter cleared their  */
                                 /* queue for this device or not.   */
                                 /* A value of zero implies that    */
                                 /* the device's queue at the       */ 
                                 /* adapter is cleared.             */
                                 /* A value of SC_DID_NOT_CLEAR_Q,  */
                                 /* defined in sc_buf, implies that */
                                 /* the device's queue at the       */
                                 /* adapter has not be cleared.       */
    uchar   resvd2;              /* reserved, should be set to zero */
    uchar   resvd3;              /* reserved, should be set to zero */
    uchar   req_sense_length;    /* Length of request sense data buffer
                                    in bytes */
    char    *request_sense_ptr;  /* Pointer to request sense buffer */
    uint    timeout_value;       /* Timeout value for the command, 
                                    in seconds */
    uchar   status_validity;     /* 0 = no valid status           */
    /* SC_SCSI_ERROR and SC_ADAPTER_ERROR defined in sc_buf
       1 = valid SCSI bus status only
       2 = valid adapter status only        */
#define SC_VALID_SENSE      4    /* valid sense data for read/write
                                    with sense */
    uchar    scsi_bus_status;    /* SCSI bus status */
    uchar    adapter_status;     /* Adapter return status, refer to 
                                    sc_buf definition */
    uchar   resvd4;              /* reserved, should be set to zero */
    uchar   resvd5;              /* reserved, should be set to zero */
    uchar   resvd6;              /* reserved, should be set to zero */
    uchar   q_tag_msg;           /* Used to pass down Queue Tag     */
                                 /* message fields of SC_NO_Q,      */
                                 /* SC_SIMPLE_Q, SC_HEAD_OF_Q,      */
                                 /* SC_ORDERED_Q, or SC_ACA_Q,      */
                                 /* defined above in sc_buf's       */
                                 /* definition.                   */

    uchar   q_flags;             /* Used to tell the SCSI adapter   */
                                 /* driver, and SCSI adapter whether*/
                                 /* or not it should clear or resume*/
                                 /* its queue. This is done via the */
                                 /* defines SC_Q_CLR, SC_Q_RESUME   */
                                 /* or SC_CLEAR_ACA defined above in*/
                                 /* sc_buf.                       */

};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read/Write with Sense Ioctl Structure used internally by device driver 
 * to support 64-bit applications
 */


struct sc_rdwrt64 {
    uint    logical_blk_addr;    /* Logical block address
                                    (0 for sequential devices) */
    uint    data_length;         /* Data transfer length in bytes */
    ptr64   buffer;              /* Pointer to data transfer buffer */
    uchar   adap_q_status;       /* used to return back whether or  */
                                 /* or not the SCSI adapter driver  */
                                 /* and SCSI adapter cleared their  */
                                 /* queue for this device or not.   */
                                 /* A value of zero implies that    */
                                 /* the device's queue at the       */ 
                                 /* adapter is cleared.             */
                                 /* A value of SC_DID_NOT_CLEAR_Q,  */
                                 /* defined in sc_buf, implies that */
                                 /* the device's queue at the       */
                                 /* adapter has not be cleared.       */
    uchar   resvd2;              /* reserved, should be set to zero */
    uchar   resvd3;              /* reserved, should be set to zero */
    uchar   req_sense_length;    /* Length of request sense data buffer
                                    in bytes */
    ptr64   request_sense_ptr;   /* Pointer to request sense buffer  */
    uint    timeout_value;       /* Timeout value for the command, 
                                    in seconds */
    uchar   status_validity;     /* See sc_rdwrt64 for defines.     */
    /* SC_SCSI_ERROR and SC_ADAPTER_ERROR defined in sc_buf
       1 = valid SCSI bus status only
       2 = valid adapter status only        */

    uchar   scsi_bus_status;     /* SCSI bus status */
    uchar   adapter_status;      /* Adapter return status, refer to 
                                    sc_buf definition */
    uchar   resvd4;              /* reserved, should be set to zero */
    uchar   resvd5;              /* reserved, should be set to zero */
    uchar   resvd6;              /* reserved, should be set to zero */
    uchar   q_tag_msg;           /* Used to pass down Queue Tag     */
                                 /* message fields of SC_NO_Q,      */
                                 /* SC_SIMPLE_Q, SC_HEAD_OF_Q,      */
                                 /* SC_ORDERED_Q, or SC_ACA_Q,      */
                                 /* defined above in sc_buf's       */
                                 /* definition.                   */

    uchar   q_flags;             /* Used to tell the SCSI adapter   */
                                 /* driver, and SCSI adapter whether*/
                                 /* or not it should clear or resume*/
                                 /* its queue. This is done via the */
                                 /* defines SC_Q_CLR, SC_Q_RESUME   */
                                 /* or SC_CLEAR_ACA defined above in*/
                                 /* sc_buf.                       */

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read/Write with Sense Ioctl Structure used internally by device driver 
 * to support 32-bit applications by 64-bit kernel extension
 */
struct sc_rdwrt32 {
    uint    logical_blk_addr;    /* Logical block address
                                   (0 for sequential devices) */
    uint    data_length;         /* Data transfer length in bytes */
    ptr32   buffer;              /* Pointer to data transfer buffer */
    uchar   adap_q_status;       /* used to return back whether or  */
                                 /* or not the SCSI adapter driver  */
                                 /* and SCSI adapter cleared their  */
                                 /* queue for this device or not.   */
                                 /* A value of zero implies that    */
                                 /* the device's queue at the       */ 
                                 /* adapter is cleared.             */
                                 /* A value of SC_DID_NOT_CLEAR_Q,  */
                                 /* defined in sc_buf, implies that */
                                 /* the device's queue at the       */
                                 /* adapter has not be cleared.       */
    uchar   resvd2;              /* reserved, should be set to zero */
    uchar   resvd3;              /* reserved, should be set to zero */
    uchar   req_sense_length;    /* Length of request sense data buffer
                                    in bytes */
    ptr32   request_sense_ptr;   /* Pointer to request sense buffer   */
    uint    timeout_value;       /* Timeout value for the command, 
                                    in seconds */
    uchar   status_validity;     /* See sc_rdwrt64 for defines.     */
    /* SC_SCSI_ERROR and SC_ADAPTER_ERROR defined in sc_buf
       1 = valid SCSI bus status only
       2 = valid adapter status only        */

    uchar   scsi_bus_status;     /* SCSI bus status */
    uchar   adapter_status;      /* Adapter return status, refer to 
                                    sc_buf definition */
    uchar   resvd4;              /* reserved, should be set to zero */
    uchar   resvd5;              /* reserved, should be set to zero */
    uchar   resvd6;              /* reserved, should be set to zero */
    uchar   q_tag_msg;           /* Used to pass down Queue Tag     */
                                 /* message fields of SC_NO_Q,      */
                                 /* SC_SIMPLE_Q, SC_HEAD_OF_Q,      */
                                 /* SC_ORDERED_Q, or SC_ACA_Q,      */
                                 /* defined above in sc_buf's       */
                                 /* definition.                   */

    uchar   q_flags;             /* Used to tell the SCSI adapter   */
                                 /* driver, and SCSI adapter whether*/
                                 /* or not it should clear or resume*/
                                 /* its queue. This is done via the */
                                 /* defines SC_Q_CLR, SC_Q_RESUME   */
                                 /* or SC_CLEAR_ACA defined above in*/
                                 /* sc_buf.                       */

};
#endif

/*
  SCSI Read/Write with Sense Ioctl Structure which
  allows up to 16 byte CDBs.
  */
struct sc_rdwrt16 {
   ushort version;            /* The version number of this      */
                              /* structure. This allows the      */
                              /* structure to expand in the      */
                              /* future.  Currently only         */
                              /* version 0 supported.            */
   ushort  resvd1;            /* reserved, should be set to zero */
   uchar   adap_q_status;     /* used to return back whether or  */
                              /* or not the SCSI adapter driver  */
                              /* and SCSI adapter cleared their  */
                              /* queue for this device or not.   */
                              /* A value of zero implies that    */
                              /* the device's queue at the       */ 
                              /* adapter is cleared.             */
                              /* A value of SC_DID_NOT_CLEAR_Q,  */
                              /* defined in sc_buf, implies that */
                              /* the device's queue at the       */
                              /* adapter has not be cleared.       */
   uchar   status_validity;   /* 0 = no valid status             */
    /* SC_SCSI_ERROR and SC_ADAPTER_ERROR defined in sc_buf
       1 = valid SCSI bus status only
       2 = valid adapter status only 
       4 = valid sense data          */
   uchar   scsi_bus_status;   /* SCSI bus status                 */
   uchar   adapter_status;    /* Adapter return status, refer to 
                                 sc_buf definition */
   uchar   resvd2;            /* reserved, should be set to zero */
   uchar   resvd3;            /* reserved, should be set to zero */
   uchar   resvd4;            /* reserved, should be set to zero */
   uchar   q_tag_msg;         /* Used to pass down Queue Tag     */
                              /* message fields of SC_NO_Q,      */
                              /* SC_SIMPLE_Q, SC_HEAD_OF_Q,      */
                              /* SC_ORDERED_Q, or SC_ACA_Q,      */
                              /* defined above in sc_buf's       */
                              /* definition.                   */

   uchar   q_flags;           /* Used to tell the SCSI adapter   */
                              /* driver, and SCSI adapter whether*/
                              /* or not it should clear or resume*/
                              /* its queue. This is done via the */
                              /* defines SC_Q_CLR, SC_Q_RESUME   */
                              /* or SC_CLEAR_ACA defined above in*/
                              /* sc_buf.                       */
    uchar  req_sense_length;  /* Length of request sense data buffer
                                 in bytes */
    uint   timeout_value;     /* Timeout value for the command, 
                                 in seconds */
    uint64_t logical_blk_addr;    /* Logical block address
                                     (0 for sequential devices)      */
    uint64_t data_length;         /* Data transfer length in bytes   */
    char    *buffer;              /* Pointer to data transfer buffer */
    char    *request_sense_ptr;   /* Pointer to request sense buffer */
};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read/Write with Sense Ioctl Structure used internally by device driver 
 * to support 64-bit applications for up to 16 byte CDBs.
 */


struct sc_rdwrt16_64 {
    ushort version;            /* The version number of this      */
                               /* structure. This allows the      */
                               /* structure to expand in the      */
                               /* future.  Currently only         */
                               /* version 0 supported.            */
    ushort  resvd1;            /* reserved, should be set to zero */
    uchar   adap_q_status;     /* used to return back whether or  */
                               /* or not the SCSI adapter driver  */
                               /* and SCSI adapter cleared their  */
                               /* queue for this device or not.   */
                               /* A value of zero implies that    */
                               /* the device's queue at the       */ 
                               /* adapter is cleared.             */
                               /* A value of SC_DID_NOT_CLEAR_Q,  */
                               /* defined in sc_buf, implies that */
                               /* the device's queue at the       */
                               /* adapter has not be cleared.       */
    uchar   status_validity;   /* 0 = no valid status             */
    /* SC_SCSI_ERROR and SC_ADAPTER_ERROR defined in sc_buf
       1 = valid SCSI bus status only
       2 = valid adapter status only 
       4 = valid sense data          */
    uchar    scsi_bus_status;  /* SCSI bus status                 */
    uchar    adapter_status;   /* Adapter return status, refer to 
                                  sc_buf definition */
    uchar   resvd2;            /* reserved, should be set to zero */
    uchar   resvd3;            /* reserved, should be set to zero */
    uchar   resvd4;            /* reserved, should be set to zero */
    uchar   q_tag_msg;         /* Used to pass down Queue Tag     */
                               /* message fields of SC_NO_Q,      */
                               /* SC_SIMPLE_Q, SC_HEAD_OF_Q,      */
                               /* SC_ORDERED_Q, or SC_ACA_Q,      */
                               /* defined above in sc_buf's       */
                               /* definition.                   */

    uchar   q_flags;           /* Used to tell the SCSI adapter   */
                               /* driver, and SCSI adapter whether*/
                               /* or not it should clear or resume*/
                               /* its queue. This is done via the */
                               /* defines SC_Q_CLR, SC_Q_RESUME   */
                               /* or SC_CLEAR_ACA defined above in*/
                               /* sc_buf.                       */
    uchar   req_sense_length;  /* Length of request sense data buffer
                                  in bytes */
    uint    timeout_value;     /* Timeout value for the command, 
                                  in seconds */
    uint64_t logical_blk_addr; /* Logical block address
                                  (0 for sequential devices)      */
    uint64_t data_length;      /* Data transfer length in bytes   */
    ptr64    buffer;          /* Pointer to data transfer buffer */
    ptr64    request_sense_ptr;    /* Pointer to request sense buffer */
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read/Write with Sense Ioctl Structure used internally by device driver 
 * to support 32-bit applications by 64-bit kernel extension for up to 16 
 * byte CDBs
 */
struct sc_rdwrt16_32 {
    ushort version;            /* The version number of this      */
                               /* structure. This allows the      */
                               /* structure to expand in the      */
                               /* future.  Currently only         */
                               /* version 0 supported.            */
    ushort  resvd1;            /* reserved, should be set to zero */
    uchar   adap_q_status;     /* used to return back whether or  */
                               /* or not the SCSI adapter driver  */
                               /* and SCSI adapter cleared their  */
                               /* queue for this device or not.   */
                               /* A value of zero implies that    */
                               /* the device's queue at the       */ 
                               /* adapter is cleared.             */
                               /* A value of SC_DID_NOT_CLEAR_Q,  */
                               /* defined in sc_buf, implies that */
                               /* the device's queue at the       */
                               /* adapter has not be cleared.       */
    uchar   status_validity;   /* 0 = no valid status             */
    /* SC_SCSI_ERROR and SC_ADAPTER_ERROR defined in sc_buf
       1 = valid SCSI bus status only
       2 = valid adapter status only 
       4 = valid sense data          */
    uchar    scsi_bus_status;  /* SCSI bus status                 */
    uchar    adapter_status;   /* Adapter return status, refer to 
                                  sc_buf definition */
    uchar   resvd2;            /* reserved, should be set to zero */
    uchar   resvd3;            /* reserved, should be set to zero */
    uchar   resvd4;            /* reserved, should be set to zero */
    uchar   q_tag_msg;         /* Used to pass down Queue Tag     */
                               /* message fields of SC_NO_Q,      */
                               /* SC_SIMPLE_Q, SC_HEAD_OF_Q,      */
                               /* SC_ORDERED_Q, or SC_ACA_Q,      */
                               /* defined above in sc_buf's       */
                               /* definition.                   */

    uchar   q_flags;           /* Used to tell the SCSI adapter   */
                               /* driver, and SCSI adapter whether*/
                               /* or not it should clear or resume*/
                               /* its queue. This is done via the */
                               /* defines SC_Q_CLR, SC_Q_RESUME   */
                               /* or SC_CLEAR_ACA defined above in*/
                               /* sc_buf.                       */
    uchar   req_sense_length;  /* Length of request sense data buffer
                                  in bytes */
    uint    timeout_value;     /* Timeout value for the command, 
                                  in seconds */
    uint64_t logical_blk_addr; /* Logical block address
                                  (0 for sequential devices)      */
    uint64_t data_length;      /* Data transfer length in bytes   */
    ptr32    buffer;          /* Pointer to data transfer buffer */
    ptr32    request_sense_ptr;    /* Pointer to request sense buffer */
};
#endif

/*
  SCSI Pass-through Ioctl Structure
  */
struct sc_iocmd {
    uint   data_length;          /* Bytes of data to be transfered */
    char   *buffer;              /* Pointer to transfer data buffer */
    uint   timeout_value;        /* In seconds */
    uchar  status_validity;      /* 0 = no valid status */
                                 /* 1 = valid SCSI bus status only       */
                                 /* 2 = valid adapter status only        */
    uchar  scsi_bus_status;      /* SCSI bus status (if valid) */
    uchar  adapter_status;       /* Adapter status (if valid), refer to 
                                    sc_buf definition */
    uchar  resvd1;               /* reserved, should be set to zero */
    uchar  resvd2;               /* reserved, should be set to zero */    
    uchar  adap_q_status;        /* used to return back whether or  */
                                 /* or not the SCSI adapter driver  */
                                 /* and SCSI adapter cleared their  */
                                 /* queue for this device or not.   */
                                 /* A value of zero implies that    */
                                 /* the device's queue at the       */ 
                                 /* adapter is cleared.             */
                                 /* A value of SC_DID_NOT_CLEAR_Q,  */
                                 /* defined in sc_buf, implies that */
                                 /* the device's queue at the       */
                                 /* adapter has not be cleared.    */
    uchar  q_tag_msg;            /* Used to pass down Queue Tag     */
                                 /* message fields of SC_NO_Q,      */
                                 /* SC_SIMPLE_Q, SC_HEAD_OF_Q,     */
                                 /* SC_ORDERED_Q, or SC_ACA_Q,      */
                                 /* defined above in sc_buf's       */
                                 /* definition.                */

    uchar  flags;                /* SC_NODISC, SC_ASYNC, B_READ,    */
                                 /* B_WRITE             */
    uchar  q_flags;              /* Used to tell the SCSI adapter   */
                                 /* driver, and SCSI adapter whether*/
                                 /* or not it should clear or resume*/
                                 /* its queue. This is done via the */
                                 /* defines SC_Q_CLR, SC_Q_RESUME   */
                                 /* or SC_CLEAR_ACA defined above in*/
                                 /* sc_buf.                    */
    uchar  lun;                  /* This is the target's lun.  If   */
                                 /* the  target's lun is greater     */
                                 /* than 7, this field must be used */
                                 /* and the 3 lun bits (used a lun  */
                                 /* in SCSI-1) in the scsi_command  */
                                 /* will be ignored.           */

    uchar  resvd7;               /* reserved, should be set to zero */


    uchar  command_length;       /* Length of SCSI command block */
    uchar  scsi_cdb[12];         /* SCSI command descriptor block */
};


#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Pass-through Ioctl Structure used internally by device driver 
 * to support 64-bit applications
 */

struct sc_iocmd64 {
    uint   data_length;          /* Bytes of data to be transfered */
    ptr64  buffer;               /* Pointer to transfer data buffer */
    uint   timeout_value;        /* In seconds */
    uchar  status_validity;      /* 0 = no valid status */
                                 /* 1 = valid SCSI bus status only       */
                                 /* 2 = valid adapter status only        */
    uchar  scsi_bus_status;      /* SCSI bus status (if valid) */
    uchar  adapter_status;       /* Adapter status (if valid), refer to 
                                    sc_buf definition */
    uchar  resvd1;               /* reserved, should be set to zero */
    uchar  resvd2;               /* reserved, should be set to zero */    
    uchar  adap_q_status;        /* used to return back whether or  */
                                 /* or not the SCSI adapter driver  */
                                 /* and SCSI adapter cleared their  */
                                 /* queue for this device or not.   */
                                 /* A value of zero implies that    */
                                 /* the device's queue at the       */ 
                                 /* adapter is cleared.             */
                                 /* A value of SC_DID_NOT_CLEAR_Q,  */
                                 /* defined in sc_buf, implies that */
                                 /* the device's queue at the       */
                                 /* adapter has not be cleared.    */
    uchar  q_tag_msg;            /* Used to pass down Queue Tag     */
                                 /* message fields of SC_NO_Q,      */
                                 /* SC_SIMPLE_Q, SC_HEAD_OF_Q,     */
                                 /* SC_ORDERED_Q, or SC_ACA_Q,      */
                                 /* defined above in sc_buf's       */
                                 /* definition.                */

    uchar  flags;                /* SC_NODISC, SC_ASYNC, B_READ,    */
                                 /* B_WRITE             */
    uchar  q_flags;              /* Used to tell the SCSI adapter   */
                                 /* driver, and SCSI adapter whether*/
                                 /* or not it should clear or resume*/
                                 /* its queue. This is done via the */
                                 /* defines SC_Q_CLR, SC_Q_RESUME   */
                                 /* or SC_CLEAR_ACA defined above in*/
                                 /* sc_buf.                    */
    uchar  lun;                  /* This is the target's lun.  If   */
                                 /* the  target's lun is greater     */
                                 /* than 7, this field must be used */
                                 /* and the 3 lun bits (used a lun  */
                                 /* in SCSI-1) in the scsi_command  */
                                 /* will be ignored.           */

    uchar  resvd7;               /* reserved, should be set to zero */


    uchar  command_length;       /* Length of SCSI command block */
    uchar  scsi_cdb[12];         /* SCSI command descriptor block */
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Pass-through Ioctl Structure used internally by device driver 
 * to support 32-bit applications by 64-bit kernel extension
 */

struct sc_iocmd32 {
    uint   data_length;          /* Bytes of data to be transfered */
    ptr32  buffer;               /* Pointer to transfer data buffer */
    uint   timeout_value;        /* In seconds */
    uchar  status_validity;      /* 0 = no valid status */
                                 /* 1 = valid SCSI bus status only       */
                                 /* 2 = valid adapter status only        */
    uchar  scsi_bus_status;      /* SCSI bus status (if valid) */
    uchar  adapter_status;       /* Adapter status (if valid), refer to 
                                    sc_buf definition */
    uchar  resvd1;               /* reserved, should be set to zero */
    uchar  resvd2;               /* reserved, should be set to zero */    
    uchar  adap_q_status;        /* used to return back whether or  */
                                 /* or not the SCSI adapter driver  */
                                 /* and SCSI adapter cleared their  */
                                 /* queue for this device or not.   */
                                 /* A value of zero implies that    */
                                 /* the device's queue at the       */ 
                                 /* adapter is cleared.             */
                                 /* A value of SC_DID_NOT_CLEAR_Q,  */
                                 /* defined in sc_buf, implies that */
                                 /* the device's queue at the       */
                                 /* adapter has not be cleared.    */
    uchar  q_tag_msg;            /* Used to pass down Queue Tag     */
                                 /* message fields of SC_NO_Q,      */
                                 /* SC_SIMPLE_Q, SC_HEAD_OF_Q,     */
                                 /* SC_ORDERED_Q, or SC_ACA_Q,      */
                                 /* defined above in sc_buf's       */
                                 /* definition.                */

    uchar  flags;                /* SC_NODISC, SC_ASYNC, B_READ,    */
                                 /* B_WRITE             */
    uchar  q_flags;              /* Used to tell the SCSI adapter   */
                                 /* driver, and SCSI adapter whether*/
                                 /* or not it should clear or resume*/
                                 /* its queue. This is done via the */
                                 /* defines SC_Q_CLR, SC_Q_RESUME   */
                                 /* or SC_CLEAR_ACA defined above in*/
                                 /* sc_buf.                    */
    uchar  lun;                  /* This is the target's lun.  If   */
                                 /* the  target's lun is greater     */
                                 /* than 7, this field must be used */
                                 /* and the 3 lun bits (used a lun  */
                                 /* in SCSI-1) in the scsi_command  */
                                 /* will be ignored.           */

    uchar  resvd7;               /* reserved, should be set to zero */


    uchar  command_length;       /* Length of SCSI command block */
    uchar  scsi_cdb[12];         /* SCSI command descriptor block */
};
#endif

/*
  SCSI Pass-through (16-Byte CDB) Ioctl Structure
  */
struct sc_iocmd16cdb {
    uint   data_length;          /* Bytes of data to be transfered */
    char   *buffer;              /* Pointer to transfer data buffer */
    uint   timeout_value;        /* In seconds */
    uchar  status_validity;      /* 0 = no valid status */
                                 /* 1 = valid SCSI bus status only       */
                                 /* 2 = valid adapter status only        */
    uchar  scsi_bus_status;      /* SCSI bus status (if valid) */
    uchar  adapter_status;       /* Adapter status (if valid), refer to 
                                    sc_buf definition */
    uchar  resvd1;               /* reserved, should be set to zero */
    uchar  resvd2;               /* reserved, should be set to zero */    
    uchar  adap_q_status;        /* used to return back whether or  */
                                 /* or not the SCSI adapter driver  */
                                 /* and SCSI adapter cleared their  */
                                 /* queue for this device or not.   */
                                 /* A value of zero implies that    */
                                 /* the device's queue at the       */ 
                                 /* adapter is cleared.             */
                                 /* A value of SC_DID_NOT_CLEAR_Q,  */
                                 /* defined in sc_buf, implies that */
                                 /* the device's queue at the       */
                                 /* adapter has not be cleared.    */
    uchar  q_tag_msg;            /* Used to pass down Queue Tag     */
                                 /* message fields of SC_NO_Q,      */
                                 /* SC_SIMPLE_Q, SC_HEAD_OF_Q,     */
                                 /* SC_ORDERED_Q, or SC_ACA_Q,      */
                                 /* defined above in sc_buf's       */
                                 /* definition.                */

    uchar  flags;                /* SC_NODISC, SC_ASYNC, B_READ,    */
                                 /* B_WRITE             */
    uchar  q_flags;              /* Used to tell the SCSI adapter   */
                                 /* driver, and SCSI adapter whether*/
                                 /* or not it should clear or resume*/
                                 /* its queue. This is done via the */
                                 /* defines SC_Q_CLR, SC_Q_RESUME   */
                                 /* or SC_CLEAR_ACA defined above in*/
                                 /* sc_buf.                    */
    uchar  lun;                  /* This is the target's lun.  If   */
                                 /* the  target's lun is greater     */
                                 /* than 7, this field must be used */
                                 /* and the 3 lun bits (used a lun  */
                                 /* in SCSI-1) in the scsi_command  */
                                 /* will be ignored.           */

    uchar  resvd7;               /* reserved, should be set to zero */


    uchar  command_length;       /* Length of SCSI command block */
    uchar  scsi_cdb[16];         /* SCSI command descriptor block */
};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI (16-Byte CDB) Pass-through Ioctl Structure used internally by device driver 
 * to support 64-bit applications
 */

struct sc_iocmd16cdb64 {
    uint   data_length;          /* Bytes of data to be transfered */
    ptr64  buffer;               /* Pointer to transfer data buffer */
    uint   timeout_value;        /* In seconds */
    uchar  status_validity;      /* 0 = no valid status */
                                 /* 1 = valid SCSI bus status only       */
                                 /* 2 = valid adapter status only        */
    uchar  scsi_bus_status;      /* SCSI bus status (if valid) */
    uchar  adapter_status;       /* Adapter status (if valid), refer to 
                                    sc_buf definition */
    uchar  resvd1;               /* reserved, should be set to zero */
    uchar  resvd2;               /* reserved, should be set to zero */    
    uchar  adap_q_status;        /* used to return back whether or  */
                                 /* or not the SCSI adapter driver  */
                                 /* and SCSI adapter cleared their  */
                                 /* queue for this device or not.   */
                                 /* A value of zero implies that    */
                                 /* the device's queue at the       */ 
                                 /* adapter is cleared.             */
                                 /* A value of SC_DID_NOT_CLEAR_Q,  */
                                 /* defined in sc_buf, implies that */
                                 /* the device's queue at the       */
                                 /* adapter has not be cleared.    */
    uchar  q_tag_msg;            /* Used to pass down Queue Tag     */
                                 /* message fields of SC_NO_Q,      */
                                 /* SC_SIMPLE_Q, SC_HEAD_OF_Q,     */
                                 /* SC_ORDERED_Q, or SC_ACA_Q,      */
                                 /* defined above in sc_buf's       */
                                 /* definition.                */

    uchar  flags;                /* SC_NODISC, SC_ASYNC, B_READ,    */
                                 /* B_WRITE             */
    uchar  q_flags;              /* Used to tell the SCSI adapter   */
                                 /* driver, and SCSI adapter whether*/
                                 /* or not it should clear or resume*/
                                 /* its queue. This is done via the */
                                 /* defines SC_Q_CLR, SC_Q_RESUME   */
                                 /* or SC_CLEAR_ACA defined above in*/
                                 /* sc_buf.                    */
    uchar  lun;                  /* This is the target's lun.  If   */
                                 /* the  target's lun is greater     */
                                 /* than 7, this field must be used */
                                 /* and the 3 lun bits (used a lun  */
                                 /* in SCSI-1) in the scsi_command  */
                                 /* will be ignored.           */

    uchar  resvd7;               /* reserved, should be set to zero */


    uchar  command_length;       /* Length of SCSI command block */
    uchar  scsi_cdb[16];         /* SCSI command descriptor block */
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI (16-Byte CDB) Pass-through Ioctl Structure used internally by device driver 
 * to support 32-bit applications by 64-bit kernel extension
 */

struct sc_iocmd16cdb32 {
    uint   data_length;          /* Bytes of data to be transfered */
    ptr32  buffer;               /* Pointer to transfer data buffer */
    uint   timeout_value;        /* In seconds */
    uchar  status_validity;      /* 0 = no valid status */
                                 /* 1 = valid SCSI bus status only       */
                                 /* 2 = valid adapter status only        */
    uchar  scsi_bus_status;      /* SCSI bus status (if valid) */
    uchar  adapter_status;       /* Adapter status (if valid), refer to 
                                    sc_buf definition */
    uchar  resvd1;               /* reserved, should be set to zero */
    uchar  resvd2;               /* reserved, should be set to zero */    
    uchar  adap_q_status;        /* used to return back whether or  */
                                 /* or not the SCSI adapter driver  */
                                 /* and SCSI adapter cleared their  */
                                 /* queue for this device or not.   */
                                 /* A value of zero implies that    */
                                 /* the device's queue at the       */ 
                                 /* adapter is cleared.             */
                                 /* A value of SC_DID_NOT_CLEAR_Q,  */
                                 /* defined in sc_buf, implies that */
                                 /* the device's queue at the       */
                                 /* adapter has not be cleared.    */
    uchar  q_tag_msg;            /* Used to pass down Queue Tag     */
                                 /* message fields of SC_NO_Q,      */
                                 /* SC_SIMPLE_Q, SC_HEAD_OF_Q,     */
                                 /* SC_ORDERED_Q, or SC_ACA_Q,      */
                                 /* defined above in sc_buf's       */
                                 /* definition.                */

    uchar  flags;                /* SC_NODISC, SC_ASYNC, B_READ,    */
                                 /* B_WRITE             */
    uchar  q_flags;              /* Used to tell the SCSI adapter   */
                                 /* driver, and SCSI adapter whether*/
                                 /* or not it should clear or resume*/
                                 /* its queue. This is done via the */
                                 /* defines SC_Q_CLR, SC_Q_RESUME   */
                                 /* or SC_CLEAR_ACA defined above in*/
                                 /* sc_buf.                    */
    uchar  lun;                  /* This is the target's lun.  If   */
                                 /* the  target's lun is greater     */
                                 /* than 7, this field must be used */
                                 /* and the 3 lun bits (used a lun  */
                                 /* in SCSI-1) in the scsi_command  */
                                 /* will be ignored.           */

    uchar  resvd7;               /* reserved, should be set to zero */


    uchar  command_length;       /* Length of SCSI command block */
    uchar  scsi_cdb[16];         /* SCSI command descriptor block */
};
#endif

/*
  SCSI Pass-through Ioctl Structure
  */
#define SC_PASSTHRU_CDB_LEN     64   /* Length of CDB array in           */
				     /* sc_passthru                      */
struct sc_passthru {

      ushort version;                /* The version number of this       */
                                     /* structure. This allows the       */
                                     /* structure to expand in the       */
                                     /* future.                          */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_2                                                       */

      uchar status_validity;         /* 0 = no valid status              */
                                     /* Valid values for this are defined*/
                                     /* under the status_validity field  */
                                     /* of the sc_buf structure.         */
                                     /* 1 = valid SCSI bus status only   */
                                     /* 2 = valid adapter status only    */
      uchar scsi_bus_status;         /* SCSI bus status (if valid)       */
                                     /* Valid values for this are defined*/
                                     /* under the scsi_bus_status field  */
                                     /* of the sc_buf structure          */
      uchar adap_status_type;        /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. It indicates the       */
                                     /* type of adapter error            */
#define SC_ADAP_SC_ERR 0x1           /* The adapter status is from an    */
                                     /* parallel SCSI adapter            */
#define SC_ADAP_SAM_ERR 0x2          /* The adapter status is from an    */
                                     /* SAM (SCSI-3 Architecture Model)  */
                                     /* compliant adapter                */
      uchar adapter_status;          /* Adapter status (if valid)        */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SC_ERR then see scsi.h   */
                                     /* for sc_buf general_card_status   */
                                     /* definition                       */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SAM_ERR then see         */
                                     /* scsi_buf.h for scsi_buf          */
                                     /* adapter_status definitions       */

      uchar adap_set_flags;          /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned.                        */
#define SC_AUTOSENSE_DATA_VALID 0x1  /* This indicates the device        */
                                     /* driver has placed the autosense  */
                                     /* data for this command failure    */
                                     /* in the buffer referenced by the  */
                                     /* field autosense_buffer_ptr.      */
#define SC_RET_ID               0x2  /* The scsi_id of this device is    */
				     /* different than the scsi_id       */
				     /* provided by the caller. The      */
				     /* scsi_id field has been updated   */
				     /* with current scsi_id for the     */
				     /* device with this world wide name.*/

      uchar add_device_status;       /* Additional device status.        */
                                     /* For FCP devices, this field      */
                                     /* contains the FCP response code.  */

      uchar adap_q_status;           /* used to return back whether or   */
                                     /* or not the SCSI adapter driver   */
                                     /* and SCSI adapter cleared their   */
                                     /* queue for this device or not.    */
                                     /* A value of zero implies that     */
                                     /* the device's queue at the        */
                                     /* adapter is cleared.              */
                                     /* A value of SC_DID_NOT_CLEAR_Q,   */
                                     /* defined in scsi.h, implies that  */
                                     /* the device's queue at the        */
                                     /* adapter has not be cleared.      */
      uchar q_tag_msg;               /* Used to pass down Queue Tag      */
                                     /* message fields of SC_NO_Q,       */
                                     /* SC_SIMPLE_Q, SC_HEAD_OF_Q,       */
                                     /* SC_ORDERED_Q, or SC_ACA_Q,       */
                                     /* defined above in sc_buf's        */
                                     /* definition.                      */
      uchar flags;                   /* Valid values are B_READ, B_WRITE */
                                     /* (defined in buf.h) and SC_NODISC */
                                     /* SC_ASYNC (defined in the scsi    */
                                     /* struct above)                    */
      uchar devflags;                /* device flags set by caller       */
#define SC_QUIESCE_IO 0x0            /* Quiesce device before issuing    */
                                     /* this passthru command.           */
#define SC_MIX_IO     0x1            /* Do not quiesce device before     */
                                     /* issuing this command. Instead    */
                                     /* allow command to be mixed with   */
                                     /* other I/O requests               */
      uchar q_flags;                 /* Used to tell the SCSI adapter    */
                                     /* driver, and SCSI adapter whether */
                                     /* or not it should clear or resume */
                                     /* its queue. This is done via the  */
                                     /* defines SC_Q_CLR,SC_Q_RESUME,    */
                                     /* or SC_CLEAR_ACA defined above    */
                                     /* in sc_buf.                       */
      ushort command_length;         /* Length of SCSI command block     */

      ushort einval_arg;             /* If this request is failed with   */
                                     /* an errno of EINVAL due to an     */
                                     /* invalid setting in some field,   */
                                     /* then this field will provide the */
                                     /* number of that invalid field.    */
#define SC_PASSTHRU_INV_VERS       1 /* Version field is invalid         */
#define SC_PASSTHRU_INV_Q_TAG_MSG  9 /* q_tag_msg field is invalid       */
#define SC_PASSTHRU_INV_FLAGS     10 /* flags field is invalid           */
#define SC_PASSTHRU_INV_DEVFLAGS  11 /* devflags field is invalid        */
#define SC_PASSTHRU_INV_Q_FLAGS   12 /* q_flags field is invalid         */
#define SC_PASSTHRU_INV_CDB_LEN   13 /* command_length field is invalid  */
#define SC_PASSTHRU_INV_AS_LEN    15 /* autosense_length field is invalid*/
#define SC_PASSTHRU_INV_CDB       16 /* scsi_cdb field is invalid        */
#define SC_PASSTHRU_INV_TO        17 /* timeout_value field is invalid   */
#define SC_PASSTHRU_INV_D_LEN     18 /* data_length field is invalid     */
#define SC_PASSTHRU_INV_SID       19 /* scsi_id field is invalid         */
#define SC_PASSTHRU_INV_LUN       20 /* lun_id field is invalid          */
#define SC_PASSTHRU_INV_BUFF      21 /* buffer field is invalid          */
#define SC_PASSTHRU_INV_AS_BUFF   22 /* autosense_buffer_ptr is invalid  */
#define SC_PASSTHRU_INV_VAR_CDB_LEN 23 /* varialbe_cdb_length field is   */
                                     /* invalid                          */
#define SC_PASSTHRU_INV_VAR_CDB   24 /* variable_cdb_ptr field is invalid*/

      ushort autosense_length;       /* This specifies the maximum size  */
                                     /* in bytes of the auto sense       */
                                     /* buffer referenced by the         */
                                     /* autosense_buffer_ptr field.      */

      uint timeout_value;            /* Time-out value in seconds        */


      unsigned long long data_length;/* Bytes of data to be transferred  */
      unsigned long long scsi_id;    /* This is the 64-bit SCSI ID for   */
                                     /* the device.                      */

      unsigned long long lun_id;     /* This is the 64-bit lun ID for    */
                                     /* the device.                      */
      char *buffer;                  /* Pointer to transfer data buffer  */
      char *autosense_buffer_ptr;    /* A pointer to the caller's        */
                                     /* autosense buffer for this SCSI   */
                                     /* command.                         */
                                     /* NOTE: if this is NULL            */
                                     /* then the adapter driver will     */
                                     /* throw away the sense data.       */
      uchar scsi_cdb[SC_PASSTHRU_CDB_LEN];/* SCSI command descriptor     */
				     /* block                            */
                                     /* The target's world wide name     */
      unsigned long long world_wide_name;   

				     /* The target's node name           */
      unsigned long long node_name; 

      uint variable_cdb_length;      /* length of variable cdb referring */
                                     /* to the variable_cdb_ptr.         */

      char *variable_cdb_ptr;        /* pointer to a buffer which holds  */
                                     /* the variable SCSI cdb.           */

      unsigned long long residual;   /* bytes not xferred after error.   */

};



#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Pass-through Ioctl Structure used internally by device driver 
 * to support 64-bit applications
 */
struct sc_passthru64v0 {

      ushort version;                /* The version number of this       */
                                     /* structure. This allows the       */
                                     /* structure to expand in the       */
                                     /* future.                          */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */

      uchar status_validity;         /* 0 = no valid status              */
                                     /* Valid values for this are defined*/
                                     /* under the status_validity field  */
                                     /* the sc_buf structure.            */
                                     /* 1 = valid SCSI bus status only   */
                                     /* 2 = valid adapter status only    */
      uchar scsi_bus_status;         /* SCSI bus status (if valid)       */
      uchar adap_status_type;        /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. It indicates the       */
                                     /* type of adapter error            */
      uchar adapter_status;          /* Adapter status (if valid)        */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SC_ERR then see scsi.h   */
                                     /* for sc_buf general_card          */
                                     /* definition                       */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SAM_ERR then see         */
                                     /* scsi_buf.h for scsi_buf          */
                                     /* adapter_status definitions       */

      uchar adap_set_flags;          /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. See scsi_buf.h         */
                                     /* for valid values that are        */
                                     /* defined under the adap_set_flags */
                                     /* field of the scsi_buf structure  */

      uchar add_device_status;       /* Additional device status.        */
                                     /* For FCP devices, this field      */
                                     /* contains the FCP response code.  */

      uchar adap_q_status;           /* used to return back whether or   */
                                     /* or not the SCSI adapter driver   */
                                     /* and SCSI adapter cleared their   */
                                     /* queue for this device or not.    */
                                     /* A value of zero implies that     */
                                     /* the device's queue at the        */
                                     /* adapter is cleared.              */
                                     /* A value of SC_DID_NOT_CLEAR_Q,   */
                                     /* defined in scsi.h, implies that  */
                                     /* the device's queue at the        */
                                     /* adapter has not be cleared.      */
      uchar q_tag_msg;               /* Used to pass down Queue Tag      */
                                     /* message fields of SC_NO_Q,       */
                                     /* SC_SIMPLE_Q, SC_HEAD_OF_Q,       */
                                     /* SC_ORDERED_Q, or SC_ACA_Q,       */
                                     /* defined above in sc_buf's        */
                                     /* definition.                      */
      uchar flags;                   /* Valid values are B_READ, B_WRITE */
                                     /* (defined in buf.h) and SC_NODISC */
                                     /* SC_ASYNC (defined in the scsi    */
                                     /* struct above)                    */
      uchar devflags;                /* device flags set by caller       */
      uchar q_flags;                 /* Used to tell the SCSI adapter    */
                                     /* driver, and SCSI adapter whether */
                                     /* or not it should clear or resume */
                                     /* its queue. This is done via the  */
                                     /* defines SC_Q_CLR,SC_Q_RESUME,    */
                                     /* or SC_CLEAR_ACA defined above    */
                                     /* in sc_buf.                       */
      ushort command_length;          /* Length of SCSI command block     */

      ushort einval_arg;             /* If this request is failed with   */
                                     /* an errno of EINVAL due to an     */
                                     /* invalid setting in some field of */
                                     /* then this field will provide the */
                                     /* number of that invalid field.    */

      ushort autosense_length;       /* This specifies the maximum size  */
                                     /* in bytes of the auto sense       */
                                     /* buffer referenced by the         */
                                     /* autosense_buffer_ptr field.      */

      uint timeout_value;            /* In seconds                       */


      unsigned long long data_length;/* Bytes of data to be transferred  */
      unsigned long long scsi_id;    /* This is the 64-bit SCSI ID for   */
                                     /* the device.                      */

      unsigned long long lun_id;     /* This is the 64-bit lun ID for    */
                                     /* the device.                      */
      ptr64 buffer;                  /* Pointer to transfer data buffer  */
      ptr64 autosense_buffer_ptr;    /* A pointer to the caller's        */
                                     /* autosense buffer for this SCSI   */
                                     /* command.                         */
                                     /* NOTE: if this is NULL            */
                                     /* then the adapter driver will     */
                                     /* throw away the sense data.       */
      uchar scsi_cdb[SC_PASSTHRU_CDB_LEN];/*SCSI command descriptor block*/
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Pass-through Ioctl Structure used internally by device driver 
 * to support 32-bit applications by 64-bit kernel extension
 */
struct sc_passthru32v0 {

      ushort version;                /* The version number of this       */
                                     /* structure. This allows the       */
                                     /* structure to expand in the       */
                                     /* future.                          */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */

      uchar status_validity;         /* 0 = no valid status              */
                                     /* Valid values for this are defined*/
                                     /* under the status_validity field  */
                                     /* the sc_buf structure.            */
                                     /* 1 = valid SCSI bus status only   */
                                     /* 2 = valid adapter status only    */
      uchar scsi_bus_status;         /* SCSI bus status (if valid)       */
      uchar adap_status_type;        /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. It indicates the       */
                                     /* type of adapter error            */
      uchar adapter_status;          /* Adapter status (if valid)        */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SC_ERR then see scsi.h   */
                                     /* for sc_buf general_card          */
                                     /* definition                       */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SAM_ERR then see         */
                                     /* scsi_buf.h for scsi_buf          */
                                     /* adapter_status definitions       */

      uchar adap_set_flags;          /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. See scsi_buf.h         */
                                     /* for valid values that are        */
                                     /* defined under the adap_set_flags */
                                     /* field of the scsi_buf structure  */

      uchar add_device_status;       /* Additional device status.        */
                                     /* For FCP devices, this field      */
                                     /* contains the FCP response code.  */

      uchar adap_q_status;           /* used to return back whether or   */
                                     /* or not the SCSI adapter driver   */
                                     /* and SCSI adapter cleared their   */
                                     /* queue for this device or not.    */
                                     /* A value of zero implies that     */
                                     /* the device's queue at the        */
                                     /* adapter is cleared.              */
                                     /* A value of SC_DID_NOT_CLEAR_Q,   */
                                     /* defined in scsi.h, implies that  */
                                     /* the device's queue at the        */
                                     /* adapter has not be cleared.      */
      uchar q_tag_msg;               /* Used to pass down Queue Tag      */
                                     /* message fields of SC_NO_Q,       */
                                     /* SC_SIMPLE_Q, SC_HEAD_OF_Q,       */
                                     /* SC_ORDERED_Q, or SC_ACA_Q,       */
                                     /* defined above in sc_buf's        */
                                     /* definition.                      */
      uchar flags;                   /* Valid values are B_READ, B_WRITE */
                                     /* (defined in buf.h) and SC_NODISC */
                                     /* SC_ASYNC (defined in the scsi    */
                                     /* struct above)                    */
      uchar devflags;                /* device flags set by caller       */
      uchar q_flags;                 /* Used to tell the SCSI adapter    */
                                     /* driver, and SCSI adapter whether */
                                     /* or not it should clear or resume */
                                     /* its queue. This is done via the  */
                                     /* defines SC_Q_CLR,SC_Q_RESUME,    */
                                     /* or SC_CLEAR_ACA defined above    */
                                     /* in sc_buf.                       */
      ushort command_length;         /* Length of SCSI command block     */

      ushort einval_arg;             /* If this request is failed with   */
                                     /* an errno of EINVAL due to an     */
                                     /* invalid setting in some field of */
                                     /* then this field will provide the */
                                     /* number of that invalid field.    */

      ushort autosense_length;       /* This specifies the maximum size  */
                                     /* in bytes of the auto sense       */
                                     /* buffer referenced by the         */
                                     /* autosense_buffer_ptr field.      */

      uint timeout_value;            /* In seconds                       */


      unsigned long long data_length;/* Bytes of data to be transferred  */
      unsigned long long scsi_id;    /* This is the 64-bit SCSI ID for   */
                                     /* the device.                      */

      unsigned long long lun_id;     /* This is the 64-bit lun ID for    */
                                     /* the device.                      */
      ptr32 buffer;                  /* Pointer to transfer data buffer  */
      ptr32 autosense_buffer_ptr;    /* A pointer to the caller's        */
                                     /* autosense buffer for this SCSI   */
                                     /* command.                         */
                                     /* NOTE: if this is NULL            */
                                     /* then the adapter driver will     */
                                     /* throw away the sense data.       */
      uchar scsi_cdb[SC_PASSTHRU_CDB_LEN];/*SCSI command descriptor block*/
};
#endif

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Pass-through Ioctl Structure used internally by device driver 
 * to support 64-bit applications
 */
struct sc_passthru64v1 {

      ushort version;                /* The version number of this       */
                                     /* structure. This allows the       */
                                     /* structure to expand in the       */
                                     /* future.                          */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */

      uchar status_validity;         /* 0 = no valid status              */
                                     /* Valid values for this are defined*/
                                     /* under the status_validity field  */
                                     /* the sc_buf structure.            */
                                     /* 1 = valid SCSI bus status only   */
                                     /* 2 = valid adapter status only    */
      uchar scsi_bus_status;         /* SCSI bus status (if valid)       */
      uchar adap_status_type;        /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. It indicates the       */
                                     /* type of adapter error            */
      uchar adapter_status;          /* Adapter status (if valid)        */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SC_ERR then see scsi.h   */
                                     /* for sc_buf general_card          */
                                     /* definition                       */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SAM_ERR then see         */
                                     /* scsi_buf.h for scsi_buf          */
                                     /* adapter_status definitions       */

      uchar adap_set_flags;          /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. See scsi_buf.h         */
                                     /* for valid values that are        */
                                     /* defined under the adap_set_flags */
                                     /* field of the scsi_buf structure  */

      uchar add_device_status;       /* Additional device status.        */
                                     /* For FCP devices, this field      */
                                     /* contains the FCP response code.  */

      uchar adap_q_status;           /* used to return back whether or   */
                                     /* or not the SCSI adapter driver   */
                                     /* and SCSI adapter cleared their   */
                                     /* queue for this device or not.    */
                                     /* A value of zero implies that     */
                                     /* the device's queue at the        */
                                     /* adapter is cleared.              */
                                     /* A value of SC_DID_NOT_CLEAR_Q,   */
                                     /* defined in scsi.h, implies that  */
                                     /* the device's queue at the        */
                                     /* adapter has not be cleared.      */
      uchar q_tag_msg;               /* Used to pass down Queue Tag      */
                                     /* message fields of SC_NO_Q,       */
                                     /* SC_SIMPLE_Q, SC_HEAD_OF_Q,       */
                                     /* SC_ORDERED_Q, or SC_ACA_Q,       */
                                     /* defined above in sc_buf's        */
                                     /* definition.                      */
      uchar flags;                   /* Valid values are B_READ, B_WRITE */
                                     /* (defined in buf.h) and SC_NODISC */
                                     /* SC_ASYNC (defined in the scsi    */
                                     /* struct above)                    */
      uchar devflags;                /* device flags set by caller       */
      uchar q_flags;                 /* Used to tell the SCSI adapter    */
                                     /* driver, and SCSI adapter whether */
                                     /* or not it should clear or resume */
                                     /* its queue. This is done via the  */
                                     /* defines SC_Q_CLR,SC_Q_RESUME,    */
                                     /* or SC_CLEAR_ACA defined above    */
                                     /* in sc_buf.                       */
      ushort command_length;          /* Length of SCSI command block     */

      ushort einval_arg;             /* If this request is failed with   */
                                     /* an errno of EINVAL due to an     */
                                     /* invalid setting in some field of */
                                     /* then this field will provide the */
                                     /* number of that invalid field.    */

      ushort autosense_length;       /* This specifies the maximum size  */
                                     /* in bytes of the auto sense       */
                                     /* buffer referenced by the         */
                                     /* autosense_buffer_ptr field.      */

      uint timeout_value;            /* In seconds                       */


      unsigned long long data_length;/* Bytes of data to be transferred  */
      unsigned long long scsi_id;    /* This is the 64-bit SCSI ID for   */
                                     /* the device.                      */

      unsigned long long lun_id;     /* This is the 64-bit lun ID for    */
                                     /* the device.                      */
      ptr64 buffer;                  /* Pointer to transfer data buffer  */
      ptr64 autosense_buffer_ptr;    /* A pointer to the caller's        */
                                     /* autosense buffer for this SCSI   */
                                     /* command.                         */
                                     /* NOTE: if this is NULL            */
                                     /* then the adapter driver will     */
                                     /* throw away the sense data.       */
      uchar scsi_cdb[SC_PASSTHRU_CDB_LEN];/*SCSI command descriptor block*/
                                     /* The target's world wide name     */
      unsigned long long world_wide_name;   

				     /* The target's node name           */
      unsigned long long node_name; 
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Pass-through Ioctl Structure used internally by device driver 
 * to support 32-bit applications by 64-bit kernel extension
 */
struct sc_passthru32v1 {

      ushort version;                /* The version number of this       */
                                     /* structure. This allows the       */
                                     /* structure to expand in the       */
                                     /* future.                          */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */

      uchar status_validity;         /* 0 = no valid status              */
                                     /* Valid values for this are defined*/
                                     /* under the status_validity field  */
                                     /* the sc_buf structure.            */
                                     /* 1 = valid SCSI bus status only   */
                                     /* 2 = valid adapter status only    */
      uchar scsi_bus_status;         /* SCSI bus status (if valid)       */
      uchar adap_status_type;        /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. It indicates the       */
                                     /* type of adapter error            */
      uchar adapter_status;          /* Adapter status (if valid)        */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SC_ERR then see scsi.h   */
                                     /* for sc_buf general_card          */
                                     /* definition                       */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SAM_ERR then see         */
                                     /* scsi_buf.h for scsi_buf          */
                                     /* adapter_status definitions       */

      uchar adap_set_flags;          /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. See scsi_buf.h         */
                                     /* for valid values that are        */
                                     /* defined under the adap_set_flags */
                                     /* field of the scsi_buf structure  */

      uchar add_device_status;       /* Additional device status.        */
                                     /* For FCP devices, this field      */
                                     /* contains the FCP response code.  */

      uchar adap_q_status;           /* used to return back whether or   */
                                     /* or not the SCSI adapter driver   */
                                     /* and SCSI adapter cleared their   */
                                     /* queue for this device or not.    */
                                     /* A value of zero implies that     */
                                     /* the device's queue at the        */
                                     /* adapter is cleared.              */
                                     /* A value of SC_DID_NOT_CLEAR_Q,   */
                                     /* defined in scsi.h, implies that  */
                                     /* the device's queue at the        */
                                     /* adapter has not be cleared.      */
      uchar q_tag_msg;               /* Used to pass down Queue Tag      */
                                     /* message fields of SC_NO_Q,       */
                                     /* SC_SIMPLE_Q, SC_HEAD_OF_Q,       */
                                     /* SC_ORDERED_Q, or SC_ACA_Q,       */
                                     /* defined above in sc_buf's        */
                                     /* definition.                      */
      uchar flags;                   /* Valid values are B_READ, B_WRITE */
                                     /* (defined in buf.h) and SC_NODISC */
                                     /* SC_ASYNC (defined in the scsi    */
                                     /* struct above)                    */
      uchar devflags;                /* device flags set by caller       */
      uchar q_flags;                 /* Used to tell the SCSI adapter    */
                                     /* driver, and SCSI adapter whether */
                                     /* or not it should clear or resume */
                                     /* its queue. This is done via the  */
                                     /* defines SC_Q_CLR,SC_Q_RESUME,    */
                                     /* or SC_CLEAR_ACA defined above    */
                                     /* in sc_buf.                       */
      ushort command_length;         /* Length of SCSI command block     */

      ushort einval_arg;             /* If this request is failed with   */
                                     /* an errno of EINVAL due to an     */
                                     /* invalid setting in some field of */
                                     /* then this field will provide the */
                                     /* number of that invalid field.    */

      ushort autosense_length;       /* This specifies the maximum size  */
                                     /* in bytes of the auto sense       */
                                     /* buffer referenced by the         */
                                     /* autosense_buffer_ptr field.      */

      uint timeout_value;            /* In seconds                       */


      unsigned long long data_length;/* Bytes of data to be transferred  */
      unsigned long long scsi_id;    /* This is the 64-bit SCSI ID for   */
                                     /* the device.                      */

      unsigned long long lun_id;     /* This is the 64-bit lun ID for    */
                                     /* the device.                      */
      ptr32 buffer;                  /* Pointer to transfer data buffer  */
      ptr32 autosense_buffer_ptr;    /* A pointer to the caller's        */
                                     /* autosense buffer for this SCSI   */
                                     /* command.                         */
                                     /* NOTE: if this is NULL            */
                                     /* then the adapter driver will     */
                                     /* throw away the sense data.       */
      uchar scsi_cdb[SC_PASSTHRU_CDB_LEN];/*SCSI command descriptor block*/
                                     /* The target's world wide name     */
      unsigned long long world_wide_name;   

				     /* The target's node name           */
      unsigned long long node_name; 
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Pass-through Ioctl Structure used internally by device driver 
 * to support 64-bit applications
 */

struct sc_passthru64 {

      ushort version;                /* The version number of this       */
                                     /* structure. This allows the       */
                                     /* structure to expand in the       */
                                     /* future.                          */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_2                                                       */

      uchar status_validity;         /* 0 = no valid status              */
                                     /* Valid values for this are defined*/
                                     /* under the status_validity field  */
                                     /* the sc_buf structure.            */
                                     /* 1 = valid SCSI bus status only   */
                                     /* 2 = valid adapter status only    */
      uchar scsi_bus_status;         /* SCSI bus status (if valid)       */
      uchar adap_status_type;        /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. It indicates the       */
                                     /* type of adapter error            */
      uchar adapter_status;          /* Adapter status (if valid)        */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SC_ERR then see scsi.h   */
                                     /* for sc_buf general_card          */
                                     /* definition                       */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SAM_ERR then see         */
                                     /* scsi_buf.h for scsi_buf          */
                                     /* adapter_status definitions       */

      uchar adap_set_flags;          /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. See scsi_buf.h         */
                                     /* for valid values that are        */
                                     /* defined under the adap_set_flags */
                                     /* field of the scsi_buf structure  */

      uchar add_device_status;       /* Additional device status.        */
                                     /* For FCP devices, this field      */
                                     /* contains the FCP response code.  */

      uchar adap_q_status;           /* used to return back whether or   */
                                     /* or not the SCSI adapter driver   */
                                     /* and SCSI adapter cleared their   */
                                     /* queue for this device or not.    */
                                     /* A value of zero implies that     */
                                     /* the device's queue at the        */
                                     /* adapter is cleared.              */
                                     /* A value of SC_DID_NOT_CLEAR_Q,   */
                                     /* defined in scsi.h, implies that  */
                                     /* the device's queue at the        */
                                     /* adapter has not be cleared.      */
      uchar q_tag_msg;               /* Used to pass down Queue Tag      */
                                     /* message fields of SC_NO_Q,       */
                                     /* SC_SIMPLE_Q, SC_HEAD_OF_Q,       */
                                     /* SC_ORDERED_Q, or SC_ACA_Q,       */
                                     /* defined above in sc_buf's        */
                                     /* definition.                      */
      uchar flags;                   /* Valid values are B_READ, B_WRITE */
                                     /* (defined in buf.h) and SC_NODISC */
                                     /* SC_ASYNC (defined in the scsi    */
                                     /* struct above)                    */
      uchar devflags;                /* device flags set by caller       */
      uchar q_flags;                 /* Used to tell the SCSI adapter    */
                                     /* driver, and SCSI adapter whether */
                                     /* or not it should clear or resume */
                                     /* its queue. This is done via the  */
                                     /* defines SC_Q_CLR,SC_Q_RESUME,    */
                                     /* or SC_CLEAR_ACA defined above    */
                                     /* in sc_buf.                       */
      ushort command_length;          /* Length of SCSI command block     */

      ushort einval_arg;             /* If this request is failed with   */
                                     /* an errno of EINVAL due to an     */
                                     /* invalid setting in some field of */
                                     /* then this field will provide the */
                                     /* number of that invalid field.    */

      ushort autosense_length;       /* This specifies the maximum size  */
                                     /* in bytes of the auto sense       */
                                     /* buffer referenced by the         */
                                     /* autosense_buffer_ptr field.      */

      uint timeout_value;            /* In seconds                       */


      unsigned long long data_length;/* Bytes of data to be transferred  */
      unsigned long long scsi_id;    /* This is the 64-bit SCSI ID for   */
                                     /* the device.                      */

      unsigned long long lun_id;     /* This is the 64-bit lun ID for    */
                                     /* the device.                      */
      ptr64 buffer;                  /* Pointer to transfer data buffer  */
      ptr64 autosense_buffer_ptr;    /* A pointer to the caller's        */
                                     /* autosense buffer for this SCSI   */
                                     /* command.                         */
                                     /* NOTE: if this is NULL            */
                                     /* then the adapter driver will     */
                                     /* throw away the sense data.       */

      uchar scsi_cdb[SC_PASSTHRU_CDB_LEN];/*SCSI command descriptor block*/
                                     /* The target's world wide name     */
      unsigned long long world_wide_name;   

				     /* The target's node name           */
      unsigned long long node_name; 

      uint variable_cdb_length;      /* length of variable cdb referring */
                                     /* to the variable_cdb_ptr.         */

      ptr64 variable_cdb_ptr;        /* pointer to a buffer which holds  */
                                     /* the variable SCSI cdb.           */

      unsigned long long residual;   /* bytes not xferred after error.   */   
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Pass-through Ioctl Structure used internally by device driver 
 * to support 32-bit applications by 64-bit kernel extension
 */
struct sc_passthru32 {

      ushort version;                /* The version number of this       */
                                     /* structure. This allows the       */
                                     /* structure to expand in the       */
                                     /* future.                          */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_2                                                       */

      uchar status_validity;         /* 0 = no valid status              */
                                     /* Valid values for this are defined*/
                                     /* under the status_validity field  */
                                     /* the sc_buf structure.            */
                                     /* 1 = valid SCSI bus status only   */
                                     /* 2 = valid adapter status only    */
      uchar scsi_bus_status;         /* SCSI bus status (if valid)       */
      uchar adap_status_type;        /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. It indicates the       */
                                     /* type of adapter error            */
      uchar adapter_status;          /* Adapter status (if valid)        */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SC_ERR then see scsi.h   */
                                     /* for sc_buf general_card          */
                                     /* definition                       */
                                     /* if adap_status_type is           */
                                     /* SC_ADAP_SAM_ERR then see         */
                                     /* scsi_buf.h for scsi_buf          */
                                     /* adapter_status definitions       */

      uchar adap_set_flags;          /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. See scsi_buf.h         */
                                     /* for valid values that are        */
                                     /* defined under the adap_set_flags */
                                     /* field of the scsi_buf structure  */

      uchar add_device_status;       /* Additional device status.        */
                                     /* For FCP devices, this field      */
                                     /* contains the FCP response code.  */

      uchar adap_q_status;           /* used to return back whether or   */
                                     /* or not the SCSI adapter driver   */
                                     /* and SCSI adapter cleared their   */
                                     /* queue for this device or not.    */
                                     /* A value of zero implies that     */
                                     /* the device's queue at the        */
                                     /* adapter is cleared.              */
                                     /* A value of SC_DID_NOT_CLEAR_Q,   */
                                     /* defined in scsi.h, implies that  */
                                     /* the device's queue at the        */
                                     /* adapter has not be cleared.      */
      uchar q_tag_msg;               /* Used to pass down Queue Tag      */
                                     /* message fields of SC_NO_Q,       */
                                     /* SC_SIMPLE_Q, SC_HEAD_OF_Q,       */
                                     /* SC_ORDERED_Q, or SC_ACA_Q,       */
                                     /* defined above in sc_buf's        */
                                     /* definition.                      */
      uchar flags;                   /* Valid values are B_READ, B_WRITE */
                                     /* (defined in buf.h) and SC_NODISC */
                                     /* SC_ASYNC (defined in the scsi    */
                                     /* struct above)                    */
      uchar devflags;                /* device flags set by caller       */
      uchar q_flags;                 /* Used to tell the SCSI adapter    */
                                     /* driver, and SCSI adapter whether */
                                     /* or not it should clear or resume */
                                     /* its queue. This is done via the  */
                                     /* defines SC_Q_CLR,SC_Q_RESUME,    */
                                     /* or SC_CLEAR_ACA defined above    */
                                     /* in sc_buf.                       */
      ushort command_length;         /* Length of SCSI command block     */

      ushort einval_arg;             /* If this request is failed with   */
                                     /* an errno of EINVAL due to an     */
                                     /* invalid setting in some field of */
                                     /* then this field will provide the */
                                     /* number of that invalid field.    */

      ushort autosense_length;       /* This specifies the maximum size  */
                                     /* in bytes of the auto sense       */
                                     /* buffer referenced by the         */
                                     /* autosense_buffer_ptr field.      */

      uint timeout_value;            /* In seconds                       */

      unsigned long long data_length;/* Bytes of data to be transferred  */
      unsigned long long scsi_id;    /* This is the 64-bit SCSI ID for   */
                                     /* the device.                      */

      unsigned long long lun_id;     /* This is the 64-bit lun ID for    */
                                     /* the device.                      */
      ptr32 buffer;                  /* Pointer to transfer data buffer  */
      ptr32 autosense_buffer_ptr;    /* A pointer to the caller's        */
                                     /* autosense buffer for this SCSI   */
                                     /* command.                         */
                                     /* NOTE: if this is NULL            */
                                     /* then the adapter driver will     */
                                     /* throw away the sense data.       */

      uchar scsi_cdb[SC_PASSTHRU_CDB_LEN];/*SCSI command descriptor block*/
                                     /* The target's world wide name     */
      unsigned long long world_wide_name;   

				     /* The target's node name           */
      unsigned long long node_name; 

      uint variable_cdb_length;      /* length of variable cdb referring */
                                     /* to the variable_cdb_ptr.         */

      ptr32 variable_cdb_ptr;        /* pointer to a buffer which holds  */
                                     /* the variable SCSI cdb.           */

      unsigned long long residual;   /* bytes not xferred after error.   */
};


#endif

/**************************************************************************
 * Structure to be used to send LOG SELECT command using DKLOGSELECT ioctl
 **************************************************************************/
typedef struct sc_log_select {
    ushort version;                    /* The version number of this      */
                                       /* structure. This allows the      */
                                       /* structure to expand in the      */
                                       /* future. MUST have a value       */
                                       /* of SCSI_VERSION_0               */
    uchar   page_code;                 /* Requested Log Page Code         */
                                       /* Will also have first byte of    */
                                       /* returned log sense data         */
#define LPAGE_CODE_MASK     0x3F       /* Page Code Mask used to get      */
                                       /* Page Code in the returned data  */

    uchar  subpage_code;               /* Requested Log Subpage code      */
    uchar  pcr;                        /* parameter code reset bit        */
                                       /* Default value is set to zero    */
    uchar  sp;                         /* Save Parameters bit,default zero*/
    uchar  pc;                         /* Page Control, default value 00b */
    ushort param_length;               /* Length of the parameter data    */
    uchar  adapter_status;             /* Adapter error status            */
    uchar  scsi_status;                /* scsi command status             */
    uchar  sense_key;                  /* check condition sense key       */
    uchar  scsi_asc;                   /* Additional Sense Code value     */
    uchar  scsi_ascq;                  /* Additional Sense Code Qualifier */
    char   *log_data;                  /* Data from requested Log Page    */
} log_select_t;

#ifdef _KERNEL
/*
 * NOTE: These structures are not supported for use by applications.
 * It is only for internal device driver use.
 */
typedef struct sc_log_select32 {
    ushort version;                    /* The version number of this      */
                                       /* structure. This allows the      */
                                       /* structure to expand in the      */
                                       /* future.                         */
    uchar  page_code;                  /* Requested Log Page Code         */
    uchar  subpage_code;               /* Requested Log Subpage code      */
    uchar  pcr;                        /* parameter code reset bit        */
                                       /* Default value is set to zero    */
    uchar  sp;                         /* Save Parameters bit,default zero*/
    uchar  pc;                         /* Page Control, default value 00b */
    ushort param_length;               /* Length of the parameter data    */
    uchar  adapter_status;             /* Adapter error status            */
    uchar  scsi_status;                /* scsi command status             */
    uchar  sense_key;                  /* check condition sense key       */
    uchar  scsi_asc;                   /* Additional Sense Code value     */
    uchar  scsi_ascq;                  /* Additional Sense Code Qualifier */
    ptr32  log_data;                   /* Data from requested Log Page    */
} log_select32_t;

typedef struct sc_log_select64 {
    ushort version;                    /* The version number of this      */
                                       /* structure. This allows the      */
                                       /* structure to expand in the      */
                                       /* future.                         */
    uchar  page_code;                  /* Requested Log Page Code         */
    uchar  subpage_code;               /* Requested Log Subpage code      */
    uchar  pcr;                        /* parameter code reset bit        */
                                       /* Default value is set to zero    */
    uchar  sp;                         /* Save Parameters bit,default zero*/
    uchar  pc;                         /* Page Control, default value 00b */
    ushort param_length;               /* Length of the parameter data    */
    uchar  adapter_status;             /* Adapter error status            */
    uchar  scsi_status;                /* scsi command status             */
    uchar  sense_key;                  /* check condition sense key       */
    uchar  scsi_asc;                   /* Additional Sense Code value     */
    uchar  scsi_ascq;                  /* Additional Sense Code Qualifier */
    ptr64  log_data;                   /* Data from requested Log Page    */
} log_select64_t;

#endif

/**************************************************************************
 * Structure to be used to send LOG SENSE command using DKLGOSENSE ioctl  *
 * If allocation Length is set to zero and log_data is set to NULL        *
 * then ioctl will return Log Page Length in the returned_length field    *
 **************************************************************************/

#define LPAGE_HEADER_LEN    0x4  /* Log Page Header Length consisting     */
                                 /* of Page Code and Page Length          */

typedef struct sc_log_sense {
    ushort version;                    /* The version number of this      */
                                       /* structure. This allows the      */
                                       /* structure to expand in the      */
                                       /* future. MUST have a value       */
                                       /* of SCSI_VERSION_0               */
    char   page_code;                  /* Requested Log Page Code         */
                                       /* Will also have first byte of    */
                                       /* returned log sense data         */
#define LPAGE_CODE_MASK     0x3F       /* Page Code Mask used to get      */
                                       /* Page Code in the returned data  */

    uchar  subpage_code;               /* Requested Log Subpage code      */
    uchar  ppc;                        /* parameter pointer bit           */
                                       /* Default value is set to zero    */
    uchar  sp;                         /* Save Parameters bit,default zero*/
    uchar  pc;                         /* Page Control, default value 01b */
#define THRESH_VAL       0x0           /* Threshold values                */
#define CUMUL_VAL        0x1           /* Cumulative values               */
#define DEFLT_THRESH_VAL 0x2           /* Default threshold values        */
#define DEFLT_CUMUL_VAL  0x3           /* Default cumulative values       */
    ushort param_ptr;                  /* parameter ptr, default is zero  */
    ushort allocation_length;          /* Length of the following data    */
    ushort returned_length;            /* page length returned by log sns */
    uchar  adapter_status;             /* Adapter error status            */
    uchar  scsi_status;                /* scsi command status             */
    uchar  sense_key;                  /* check condition sense key       */
    uchar  scsi_asc;                   /* Additional Sense Code value     */
    uchar  scsi_ascq;                  /* Additional Sense Code Qualifier */
    void   *log_data;                  /* Data from requested Log Page    */
                                       /* Doesn't include Log page header */
} log_sense_t;

#ifdef _KERNEL
/*
 * NOTE: These structures are not supported for use by applications.
 * It is only for internal device driver use.
 */
typedef struct sc_log_sense32 {
    ushort version;                    /* The version number of this      */
                                       /* structure. This allows the      */
                                       /* structure to expand in the      */
                                       /* future.                         */
    char   page_code;                  /* Requested Log Page Code         */
    uchar  subpage_code;               /* Requested Log Subpage code      */
    uchar  ppc;                        /* parameter pointer bit           */
                                       /* Default value is set to zero    */
    uchar  sp;                         /* Save Parameters bit,default zero*/
    uchar  pc;                         /* Page Control, default value 01b */
    ushort param_ptr;                  /* parameter ptr, default is zero  */
    ushort allocation_length;          /* Length of the following data    */
    ushort returned_length;            /* number of bytes returned        */
    uchar  adapter_status;             /* Adapter error status            */
    uchar  scsi_status;                /* scsi command status             */
    uchar  sense_key;                  /* check condition sense key       */
    uchar  scsi_asc;                   /* Additional Sense Code value     */
    uchar  scsi_ascq;                  /* Additional Sense Code Qualifier */
    ptr32  log_data;                   /* Data from requested Log Page    */
} log_sense32_t;

typedef struct sc_log_sense64 {
    ushort version;                    /* The version number of this      */
                                       /* structure. This allows the      */
                                       /* structure to expand in the      */
                                       /* future.                         */
    char   page_code;                  /* Requested Log Page Code         */
    uchar  subpage_code;               /* Requested Log Subpage code      */
    uchar  ppc;                        /* parameter pointer bit           */
                                       /* Default value is set to zero    */
    uchar  sp;                         /* Save Parameters bit,default zero*/
    uchar  pc;                         /* Page Control, default value 01b */
    ushort param_ptr;                  /* parameter ptr, default is zero  */
    ushort allocation_length;          /* Length of the following data    */
    ushort returned_length;            /* number of bytes returned        */
    uchar  scsi_status;                /* scsi command status             */
    uchar  adapter_status;             /* Adapter error status            */
    uchar  sense_key;                  /* check condition sense key       */
    uchar  scsi_asc;                   /* Additional Sense Code value     */
    uchar  scsi_ascq;                  /* Additional Sense Code Qualifier */
    ptr64  log_data;                   /* Data from requested Log Page    */
} log_sense64_t;

#endif

#define SCSI_BSR_LOG_PAGE  0x15 /* Background Scan Results(BSR) Log Page  */

/**************************************************************************
 * +======================================================================+
 * | Table 104(SBC3r12) - Background Scanning Status parameter format     |
 * +=====-=======-=======-=======-=======-=======-========-=======-=======+
 * |  Bit|   7   |   6   |   5   |   4   |   3   |   2    |   1   |   0   |
 * |Byte |       |       |       |       |       |        |       |       |
 * |=====+=======+========================================================|
 * | 0   |  (MSB)         Parameter Code (0000h)                          |
 * |-----+--------                                             -----------|
 * | 1   |                                                         (LSB)  |
 * |-----+----------------------------------------------------------------|
 * |     |                Parameter Control Byte                          |
 * | 2   |----------------------------------------------------------------|
 * |     |  DU   |Obs'ete|  TSD  |  ETC  |      TMC       |Format&Linking |
 * |-----+----------------------------------------------------------------|
 * | 3   |                Parameter Length (0Ch)                          |
 * |-----+----------------------------------------------------------------|
 * | 4   |  (MSB)         Accumulated Power On Minutes(000Ch)             |
 * |-----+--------                                             -----------|
 * | 7   |                                                         (LSB)  |
 * |-----+----------------------------------------------------------------|
 * | 8   |                Reserved                                        |
 * |-----+----------------------------------------------------------------|
 * | 9   |                Background Scanning Status                      |
 * |-----+----------------------------------------------------------------|
 * | 10  |  (MSB)         Number Of Background Scans Performed            |
 * |-----+----------                                       ---------------|
 * | 11  |                                                         (LSB)  |
 * |-----+----------------------------------------------------------------|
 * | 12  |  (MSB)         Background Medium Scan Progress                 |
 * |-----+----------                                       ---------------|
 * | 13  |                                                         (LSB)  |
 * |-----+----------------------------------------------------------------|
 * | 14  |  (MSB)         Number of Background Medium Scans Performed     |
 * |-----+----------                                       ---------------|
 * | 15  |                                                         (LSB)  |
 * +======================================================================+
 *
 **************************************************************************/

#define BS_STATUS_LEN       0x10  /* Length of Background Scanning Status */
                                  /* Parameter Data                       */

typedef struct sc_scan_status {
    ushort version;               /* The version number of this structure */
                                  /* This allows structure to expand      */
                                  /* in the future                        */
                                  /* Returned value set to SCSI_VERSION_0 */
    ushort reserved;              /* Reserved Field                       */
    ushort param_code;            /* It will contain 0x0000               */
    uchar param_ctrl_bits;        /* Parameter control bits               */
    uchar param_length;           /* Parameter length ahead               */
    uint  power_age;              /* No of minutes the device been powered*/
                                  /* on since manufacturing at the time   */
                                  /* when Background error occurred       */
    uchar reserved1;
    uchar scan_status;            /* Current Status of Background Scanning*/
#define SC_BS_INACTIVE      0x00  /* No Background Scan(BS) active        */
#define SC_BMS_ACTIVE       0x01  /* Background Medium Scan(BMS) active   */
#define SC_BPS_ACTIVE       0x02  /* Background Pre Scan(BPS) active      */
#define SC_BMS_HLT_FATAL    0x03  /* BMS halted due to Fatal Error        */
#define SC_BMS_HLT_VENDERR  0x04  /* BMS halted due to a                  */
                                  /* Vendor Specific pattern of errors    */
#define SC_BMS_HLT_FMTERR   0x05  /* BMS halted due to                    */
                                  /* Medium Formatted without P-list      */
#define SC_BMS_HLT_VENDSPEC 0x06  /* BMS halted - Vendor Specific Cause   */
#define SC_BMS_HLT_HEAT     0x07  /* BMS halted due to                    */
                                  /* Temperature out of allowed range     */
#define BMS_HALTED_INTVLEXP 0x08  /* BMS halted, waiting for              */
                                  /* Background Medium Interval timer     */
                                  /* expiration                           */

    ushort scan_count;            /* Indicates the number of              */
                                  /* Background scans that have been      */
                                  /* performed since the device was       */
                                  /* originally shipped by manufacturer   */
    ushort scan_progress;         /* % complete indication of BMS.        */
                                  /* Value is a numerator that has 65536  */
                                  /* as its denominator                   */
    ushort bms_count;             /* Indicates the number of Backgorund   */
                                  /* Medium Scans that have been          */
                                  /* performed since the device was       */
                                  /* originally shipped by manufacturer   */
} scan_status_t;

/**************************************************************************
 *  Background Medium Scan parameter format
 * +======================================================================+
 * | Table 107(SBC3r16) - Background Medium Scan parameter format         |
 * +=====-=======-=======-=======-=======-=======-========-=======-=======+
 * |  Bit|   7   |   6   |   5   |   4   |   3   |   2    |   1   |   0   |
 * |Byte |       |       |       |       |       |        |       |       |
 * |=====+=======+========================================================|
 * | 0   |  (MSB)         Parameter Code (0001h - 0800h)                  |
 * |-----+--------                                             -----------|
 * | 1   |                                                         (LSB)  |
 * |-----+----------------------------------------------------------------|
 * |     |                Parameter Control Byte                          |
 * | 2   |----------------------------------------------------------------|
 * |     |  DU   |Obs'ete|  TSD  |  ETC  |      TMC       |Format&Linking |
 * |-----+----------------------------------------------------------------|
 * | 3   |                Parameter Length (14h)                          |
 * |-----+----------------------------------------------------------------|
 * | 4   |  (MSB)         Accumulated Power On Minutes(000Ch)             |
 * |-----+--------                                             -----------|
 * | 7   |                                                         (LSB)  |
 * |-----+----------------------------------------------------------------|
 * | 8   |       Reassign Status         |        Sense Key               |
 * |-----+----------------------------------------------------------------|
 * | 9   |                Additional Sense Code                           |
 * |-----+----------------------------------------------------------------|
 * | 10  |                Additional Sense Code Qualifier                 |
 * |-----+----------------------------------------------------------------|
 * | 11  |  (MSB)         Vendor Specific                                 |
 * |-----+----------                                       ---------------|
 * | 15  |                                                         (LSB)  |
 * |-----+----------------------------------------------------------------|
 * | 16  |  (MSB)         Logical Block Address(LBA)                      |
 * |-----+----------                                       ---------------|
 * | 23  |                                                         (LSB)  |
 * +======================================================================+
 **************************************************************************/

#define BMS_PARAM_ELEM_LEN  0x18  /* Length of Each Element in the        */
                                  /* Background Medium Scan Parameter List*/

typedef struct sc_bms_log_data{
    ushort version;               /* The version number of this structure */
                                  /* This allows structure to expand      */
                                  /* in the future                        */
                                  /* Returned value set to SCSI_VERSION_0 */
    ushort reserved;              /* Reserved Field                       */
    ushort param_code;            /* Parameter codes(0x0001 - 0x0800)     */
    uchar param_ctrl_bits;        /* Parameter control bits               */
    uchar param_length;           /* Parameter length ahead               */
    uint  power_age;              /* No of minutes the device been powered*/
                                  /* on since manufacturing at the time   */
                                  /* when background error occurred       */
    uchar status_snskey;          /* SENSE KEY(Lower Nibble)              */
                                  /* REASSIGN  STATUS(Higher Nibble       */
    uchar asc;                    /* Additional Sense Code(ASC) info      */
    uchar ascq;                   /* ASC Qualifier(ASCQ) info             */
    uchar vendor_data[5];         /* Vendor Specific Data                 */
    unsigned long long lba;       /* Logical Block address(LBA)           */
                                  /* to which this parameter belongs      */
} bms_log_data_t;


/**************************************************************************
 * +======================================================================+
 * | Table 102(SBC3r12) - Background Scan Results Log Page
 * +=====-=======-=======-=======-=======-=======-========-=======-=======+
 * |  Bit|   7   |   6   |   5   |   4   |   3   |   2    |   1   |   0   |
 * |Byte |       |       |       |       |       |        |       |       |
 * |=====+=======+========================================================|
 * | 0   | DS(1) | SPF(0)|              Page Code (15h)                   |
 * |-----+----------------------------------------------------------------|
 * | 1   |                       Reserved                                 |
 * |-----+----------------------------------------------------------------|
 * | 2   |  (MSB)                Page Length (n-3)                        |
 * |-----+--------                                             -----------|
 * | 3   |                                                         (LSB)  |
 * |=====+================================================================+
 * |     |       Background Scan Results log parameters                   |
 * |=====+================================================================+
 * | 4   |               Background Scanning Status parameter             |
 * |-----+-------                                              -----------|
 * | 19  |                      (see table 104 above)                     |
 * |=====+================================================================+
 * |     |       Background Medium Scan parameter list                    |
 * |=====+================================================================+
 * | 20  |               Background Medium Scan parameter(first)          |
 * |-----+-------                                              -----------|
 * | 43  |                      (see table 107 above)                     |
 * |-----+----------------------------------------------------------------|
 * |     |                         .   .   .                              |
 * |     |                         .   .   .                              |
 * |     |                         .   .   .                              |
 * |-----+----------------------------------------------------------------|
 * |n-23 |               Background Medium Scan parameter(last)           |
 * |-----+-------                                              -----------|
 * |  n  |                      (see table 107 above)                     |
 * +======================================================================+
 **************************************************************************/
/* LOG SENSE data for Background Scan Results(BSR)Log Page-Page Code(15h) */
typedef struct sc_bsr_log_data {
    scan_status_t  scan_status;   /* Background Scanning Status           */
                                  /* Parameter data                       */
    bms_log_data_t *bms_log_data; /* Background Medium Scan               */
                                  /* Parameter data                       */
} bsr_log_data_t;

#ifdef _KERNEL
/*
 * NOTE: These structures are not supported for use by applications.
 * It is only for internal device driver use.
 */
typedef struct sc_bsr_log_data32 {
    scan_status_t  scan_status;   /* Background Scanning Status           */
                                  /* Parameter data                       */
    ptr32          bms_log_data;  /* Background Medium Scan               */
                                  /* Parameter data                       */
} bsr_log_data32_t;

typedef struct sc_bsr_log_data64 {
    scan_status_t   scan_status;  /* Background Scanning Status           */
                                  /* Parameter data                       */
    ptr64           bms_log_data; /* Background Medium Scan               */
                                  /* Parameter data                       */
} bsr_log_data64_t;

#endif

/*
 * SCSI Write Buffer/Read Buffer Ioctl Structure
 */
struct sc_rwbuffer {
      
      ushort version;                /* The version number of this       */
                                     /* structure. This allows the       */
                                     /* structure to expand in the       */
                                     /* future.  Currently only          */
                                     /* version 0 supported.             */
      uchar op;                      /* Issue SCSI Read Buffer or        */
                                     /* Write Buffer command(s)          */
                                     /* Currently only Write Buffer      */
                                     /* supported.                       */
#define SC_WRITE_BUFFER 0x1

      uchar status_validity;         /* 0 = no valid status              */
                                     /* Valid values for this are defined*/
                                     /* under the status_validity field  */
                                     /* in sc_buf structure in scsi.h    */
                                     /* 1 = valid SCSI bus status only   */
                                     /* 2 = valid adapter status only    */
      uchar scsi_status;             /* SCSI status (if valid)           */
                                     /* Valid values for this are defined*/
                                     /* under the scsi_status field of   */
                                     /* the sc_buf structure in scsi.h   */
      uchar adap_status_type;        /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. It indicates the       */
                                     /* type of adapter error            */
                                     /* #defines located in sc_passthru  */
                                     /* struct above.                    */
      uchar adapter_status;          /* Adapter status (if valid).       */
                                     /* If adap_status_type is           */
                                     /* SC_ADAP_SC_ERR then see scsi.h   */
                                     /* for sc_buf general_card_status   */
                                     /* definitions.                     */
                                     /* If adap_status_type is           */
                                     /* SC_ADAP_SAM_ERR then see         */
                                     /* scsi_buf.h for scsi_buf          */
                                     /* adapter_status definitions.      */
      uchar adap_set_flags;          /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned.  See scsi_buf.h        */
                                     /* for valid values that are        */ 
                                     /* defined under the adap_set_flags */
                                     /* field of the scsi_buf structure  */
      uchar add_device_status;       /* Additional device status.        */
                                     /* For FCP devices, this field      */
                                     /* contains the FCP response code.  */
      uchar devflags;                /* Device flags set by caller.      */
#define SC_STOP_START_UNIT       0x1 /* stop and start unit after all    */
                                     /* ucode fragments have been xfered */
#define SC_INCR_BUF_ID           0x2 /* if more than one fragment xfer   */
                                     /* is needed, after the first xfer, */
                                     /* the driver increments the buffer */
                                     /* id by 1 until all fragments are  */
                                     /* xfered                           */
#define SC_INCR_BUF_OFFSET       0x4 /* if more than one fragment xfer   */
                                     /* is needed, after the first xfer, */
                                     /* the driver increments the buffer */
                                     /* offset by the fragment size until*/
                                     /* all fragments are xfered         */
      uchar reserved0;               /* Reserved for future use. Do NOT  */
                                     /* reference this field as it may   */
                                     /* affect future compatibility.     */
                                     /* Use memset() or bzero() to       */
                                     /* initialize these (and all)       */
                                     /* fields to 0.                     */
      uchar mode;                    /* Mode field of SCSI Write Buffer  */
                                     /* CDB. See WRITE BUFFER command in */
                                     /* SPC (7.25) for further details   */
#define SC_DWNLD_UCODE          0x4  /* microcode download not preserved */
                                     /* after reset or power cycle       */
#define SC_DWNLD_UCODE_AND_SAVE 0x5  /* microcode download is preserved  */
                                     /* after reset or power cycle       */
#define SC_DWNLD_UCODE_W_OFFSETS 0x6 /* buffer offset is used as the     */
                                     /* starting location for each xfer  */
                                     /* microcode download not preserved */
                                     /* after reset or power cycle       */
#define SC_DWNLD_UCODE_W_OFFSETS_AND_SAVE 0x7
                                     /* buffer offset is used as the     */
                                     /* starting location for each xfer  */
                                     /* microcode download is preserved  */
                                     /* after reset or power cycle       */
      uchar reserved1;               /* Reserved for future use. Do NOT  */
                                     /* reference this field as it may   */
                                     /* affect future compatibility.     */
                                     /* Use memset() or bzero() to       */
                                     /* initialize these (and all)       */
                                     /* fields to 0.                     */
      ushort buffer_ID;              /* The buffer ID of the device where*/
                                     /* the data transfer is to begin.   */
                                     /* The meaning of this depends on   */
                                     /* mode setting.  See SPC (7.25)    */
      ushort reserved2;              /* Reserved for future use. Do NOT  */
                                     /* reference this field as it may   */
                                     /* affect future compatibility.     */
                                     /* Use memset() or bzero() to       */
                                     /* initialize these (and all)       */
                                     /* fields to 0.                     */
      ushort einval_arg;             /* Currently not used, but put here */
                                     /* as place holder for possible     */
                                     /* future use.                      */
      uint timeout_value;            /* In seconds                       */

      uint autosense_length;         /* This specifies the maximum size  */
                                     /* in bytes of the SCSI driver's    */
                                     /* autosense buffer referenced by   */
                                     /* the autosense_buffer_ptr field.  */
      uint64_t total_fragments;      /* Calculated and set by driver.    */
                                     /* Total number of fragments to     */
                                     /* send, including the fragment for */
                                     /* fragment_size_fraction if        */
                                     /* necessary.                       */
      uint64_t fragments_sent;       /* This is the number of fragments  */
                                     /* transferred successfully. If the */
                                     /* operation fails midway, this will*/
                                     /* contain the number of fragments  */
                                     /* successfully transferred.  If    */
                                     /* all fragments were transferred   */
                                     /* successfully, this is equal to   */
                                     /* total number of fragments.       */
                                     /* If the entire buffer was sent at */
                                     /* once, this will be set to 1.     */
      uint64_t fragment_size;        /* If less than data_length, then   */
                                     /* the buffer will be written to    */
                                     /* the device in fragments of this  */
                                     /* number of bytes.  Shall not      */
                                     /* exceed the max buffer capacity   */
                                     /* that this device supports for    */
                                     /* the WRITE BUFFER command         */
                                     /* (See SPC sect. 7.25 for details).*/
                                     /* A value of equal to data_length  */
                                     /* causes entire buffer to be       */
                                     /* written with a single            */
                                     /* WRITE BUFFER command.            */
                                     /* A value of 0 results in an error */
                                     /* of EINVAL.                       */
      uint64_t fragment_size_fraction; /* For internal driver use.  If the */
                                     /* data_length is not an even       */
                                     /* multiple of fragment_size, then  */
                                     /* this field contains the number of*/
                                     /* bytes in the final fragment,     */
                                     /* otherwise it is set to 0 and not */
                                     /* used.                            */
      uint64_t buffer_offset;        /* Offset within the device buffer  */
                                     /* where data transfer to begin     */
      uint64_t data_length;          /* Total number of bytes of buffer  */
                                     /* to transfer to the device        */ 
      char *buffer;                  /* Pointer to host data buffer      */
      char *autosense_buffer_ptr;    /* A pointer to the caller's        */
                                     /* autosense buffer for this SCSI   */
                                     /* command.                         */
                                     /* NOTE: if this is NULL the        */
                                     /* the adapter driver will throw    */
                                     /* away the sense data.             */
};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Write Buffer/Read Buffer Ioctl Structure used internally by 
 * device driver to support 64-bit applications
 */
struct sc_rwbuffer64 {
      
      ushort version;                /* The version number of this       */
                                     /* structure. This allows the       */
                                     /* structure to expand in the       */
                                     /* future.  Currently only          */
                                     /* version 0 supported.             */
      uchar op;                      /* Issue SCSI Read Buffer or        */
                                     /* Write Buffer command(s)          */
                                     /* Currently only Write Buffer      */
                                     /* supported.                       */
#define SC_WRITE_BUFFER 0x1

      uchar status_validity;         /* 0 = no valid status              */
                                     /* Valid values for this are defined*/
                                     /* under the status_validity field  */
                                     /* in sc_buf structure in scsi.h    */
                                     /* 1 = valid SCSI bus status only   */
                                     /* 2 = valid adapter status only    */
      uchar scsi_status;             /* SCSI status (if valid)           */
                                     /* Valid values for this are defined*/
                                     /* under the scsi_status field of   */
                                     /* the sc_buf structure in scsi.h   */
      uchar adap_status_type;        /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. It indicates the       */
                                     /* type of adapter error            */
                                     /* #defines located in sc_passthru  */
                                     /* struct above.                    */
      uchar adapter_status;          /* Adapter status (if valid).       */
                                     /* If adap_status_type is           */
                                     /* SC_ADAP_SC_ERR then see scsi.h   */
                                     /* for sc_buf general_card_status   */
                                     /* definitions.                     */
                                     /* If adap_status_type is           */
                                     /* SC_ADAP_SAM_ERR then see         */
                                     /* scsi_buf.h for scsi_buf          */
                                     /* adapter_status definitions.      */
      uchar adap_set_flags;          /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned.  See scsi_buf.h        */
                                     /* for valid values that are        */ 
                                     /* defined under the adap_set_flags */
                                     /* field of the scsi_buf structure  */
      uchar add_device_status;       /* Additional device status.        */
                                     /* For FCP devices, this field      */
                                     /* contains the FCP response code.  */
      uchar devflags;                /* Device flags set by caller.      */
/* 
#define SC_STOP_START_UNIT       0x1    stop and start unit after all    
                                        ucode fragments have been xfered 
#define SC_INCR_BUF_ID           0x2    if more than one fragment xfer   
                                        is needed, after the first xfer, 
                                        the driver increments the buffer 
                                        id by 1 until all fragments are  
                                        xfered                           
#define SC_INCR_BUF_OFFSET       0x4    if more than one fragment xfer   
                                        is needed, after the first xfer, 
                                        the driver increments the buffer 
                                        offset by the fragment size until
                                        all fragments are xfered         
*/
      uchar reserved0;               /* Reserved for future use. Do NOT  */
                                     /* reference this field as it may   */
                                     /* affect future compatibility.     */
                                     /* Use memset() or bzero() to       */
                                     /* initialize these (and all)       */
                                     /* fields to 0.                     */
      uchar mode;                    /* Mode field of SCSI Write Buffer  */
                                     /* CDB. See WRITE BUFFER command in */
                                     /* SPC (7.25) for further details   */
/*
#define SC_DWNLD_UCODE          0x4     microcode download not preserved   
                                        after reset or power cycle         
#define SC_DWNLD_UCODE_AND_SAVE 0x5     microcode download is preserved    
                                        after reset or power cycle         
#define SC_DWNLD_UCODE_W_OFFSETS 0x6    buffer offset is used as the         
                                        starting location for each xfer    
                                        microcode download not preserved   
                                        after reset or power cycle         
#define SC_DWNLD_UCODE_W_OFFSETS_AND_SAVE 0x7
                                        buffer offset is used as the         
                                        starting location for each xfer    
                                        microcode download is preserved    
                                        after reset or power cycle         
*/
      uchar reserved1;               /* Reserved for future use. Do NOT  */
                                     /* reference this field as it may   */
                                     /* affect future compatibility.     */
                                     /* Use memset() or bzero() to       */
                                     /* initialize these (and all)       */
                                     /* fields to 0.                     */
      ushort buffer_ID;              /* The buffer ID of the device where*/
                                     /* the data transfer is to begin.   */
                                     /* The meaning of this depends on   */
                                     /* mode setting.  See SPC (7.25)    */
      ushort reserved2;              /* Reserved for future use. Do NOT  */
                                     /* reference this field as it may   */
                                     /* affect future compatibility.     */
                                     /* Use memset() or bzero() to       */
                                     /* initialize these (and all)       */
                                     /* fields to 0.                     */
      ushort einval_arg;             /* Currently not used, but put here */
                                     /* as place holder for possible     */
                                     /* future use.                      */
      uint timeout_value;            /* In seconds                       */

      uint autosense_length;         /* This specifies the maximum size  */
                                     /* in bytes of the SCSI driver's    */
                                     /* autosense buffer referenced by   */
                                     /* the autosense_buffer_ptr field.  */
      uint64_t total_fragments;      /* Calculated and set by driver.    */
                                     /* Total number of fragments to     */
                                     /* send, including the fragment for */
                                     /* fragment_size_fraction if        */
                                     /* necessary.                       */
      uint64_t fragments_sent;       /* This is the number of fragments  */
                                     /* transferred successfully. If the */
                                     /* operation fails midway, this will*/
                                     /* contain the number of fragments  */
                                     /* successfully transferred.  If    */
                                     /* all fragments were transferred   */
                                     /* successfully, this is equal to   */
                                     /* total number of fragments.       */
                                     /* If the entire buffer was sent at */
                                     /* once, this will be set to 1.     */
      uint64_t fragment_size;        /* If less than data_length, then   */
                                     /* the buffer will be written to    */
                                     /* the device in fragments of this  */
                                     /* number of bytes.  Shall not      */
                                     /* exceed the max buffer capacity   */
                                     /* that this device supports for    */
                                     /* the WRITE BUFFER command         */
                                     /* (See SPC sect. 7.25 for details).*/
                                     /* A value of equal to data_length  */
                                     /* causes entire buffer to be       */
                                     /* written with a single            */
                                     /* WRITE BUFFER command.            */
                                     /* A value of 0 results in an error */
                                     /* of EINVAL.                       */
      uint64_t fragment_size_fraction; /* For internal driver use.  If the */
                                     /* data_length is not an even       */
                                     /* multiple of fragment_size, then  */
                                     /* this field contains the number of*/
                                     /* bytes in the final fragment,     */
                                     /* otherwise it is set to 0 and not */
                                     /* used.                            */
      uint64_t buffer_offset;        /* Offset within the device buffer  */
                                     /* where data transfer to begin     */
      uint64_t data_length;          /* Total number of bytes of buffer  */
                                     /* to transfer to the device        */ 
      ptr64 buffer;                  /* Pointer to host data buffer      */
      ptr64 autosense_buffer_ptr;    /* A pointer to the caller's        */
                                     /* autosense buffer for this SCSI   */
                                     /* command.                         */
                                     /* NOTE: if this is NULL the        */
                                     /* the adapter driver will throw    */
                                     /* away the sense data.             */
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Write Buffer/Read Buffer Ioctl Structure used internally by 
 * device driver to support 32-bit applications by 64-bit kernel extension
 */
struct sc_rwbuffer32 {
      
      ushort version;                /* The version number of this       */
                                     /* structure. This allows the       */
                                     /* structure to expand in the       */
                                     /* future.  Currently only          */
                                     /* version 0 supported.             */
      uchar op;                      /* Issue SCSI Read Buffer or        */
                                     /* Write Buffer command(s)          */
                                     /* Currently only Write Buffer      */
                                     /* supported.                       */
#define SC_WRITE_BUFFER 0x1

      uchar status_validity;         /* 0 = no valid status              */
                                     /* Valid values for this are defined*/
                                     /* under the status_validity field  */
                                     /* in sc_buf structure in scsi.h    */
                                     /* 1 = valid SCSI bus status only   */
                                     /* 2 = valid adapter status only    */
      uchar scsi_status;             /* SCSI status (if valid)           */
                                     /* Valid values for this are defined*/
                                     /* under the scsi_status field of   */
                                     /* the sc_buf structure in scsi.h   */
      uchar adap_status_type;        /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned. It indicates the       */
                                     /* type of adapter error            */
                                     /* #defines located in sc_passthru  */
                                     /* struct above.                    */
      uchar adapter_status;          /* Adapter status (if valid).       */
                                     /* If adap_status_type is           */
                                     /* SC_ADAP_SC_ERR then see scsi.h   */
                                     /* for sc_buf general_card_status   */
                                     /* definitions.                     */
                                     /* If adap_status_type is           */
                                     /* SC_ADAP_SAM_ERR then see         */
                                     /* scsi_buf.h for scsi_buf          */
                                     /* adapter_status definitions.      */
      uchar adap_set_flags;          /* These flags are set by the SCSI  */
                                     /* adapter driver when a command is */
                                     /* returned.  See scsi_buf.h        */
                                     /* for valid values that are        */ 
                                     /* defined under the adap_set_flags */
                                     /* field of the scsi_buf structure  */
      uchar add_device_status;       /* Additional device status.        */
                                     /* For FCP devices, this field      */
                                     /* contains the FCP response code.  */
      uchar devflags;                /* Device flags set by caller.      */
/* 
#define SC_STOP_START_UNIT       0x1    stop and start unit after all    
                                        ucode fragments have been xfered 
#define SC_INCR_BUF_ID           0x2    if more than one fragment xfer   
                                        is needed, after the first xfer, 
                                        the driver increments the buffer 
                                        id by 1 until all fragments are  
                                        xfered                           
#define SC_INCR_BUF_OFFSET       0x4    if more than one fragment xfer   
                                        is needed, after the first xfer, 
                                        the driver increments the buffer 
                                        offset by the fragment size until
                                        all fragments are xfered         
*/
                                     /* Currently not used, but put here */
                                     /* as place holder for possible     */
                                     /* future use.                      */
      uchar reserved0;               /* Reserved for future use. Do NOT  */
                                     /* reference this field as it may   */
                                     /* affect future compatibility.     */
                                     /* Use memset() or bzero() to       */
                                     /* initialize these (and all)       */
                                     /* fields to 0.                     */
      uchar mode;                    /* Mode field of SCSI Write Buffer  */
                                     /* CDB. See WRITE BUFFER command in */
                                     /* SPC (7.25) for further details   */
/*
#define SC_DWNLD_UCODE          0x4     microcode download not preserved   
                                        after reset or power cycle         
#define SC_DWNLD_UCODE_AND_SAVE 0x5     microcode download is preserved    
                                        after reset or power cycle         
#define SC_DWNLD_UCODE_W_OFFSETS 0x6    buffer offset is used as the         
                                        starting location for each xfer    
                                        microcode download not preserved   
                                        after reset or power cycle         
#define SC_DWNLD_UCODE_W_OFFSETS_AND_SAVE 0x7
                                        buffer offset is used as the         
                                        starting location for each xfer    
                                        microcode download is preserved    
                                        after reset or power cycle         
*/
      uchar reserved1;               /* Reserved for future use. Do NOT  */
                                     /* reference this field as it may   */
                                     /* affect future compatibility.     */
                                     /* Use memset() or bzero() to       */
                                     /* initialize these (and all)       */
                                     /* fields to 0.                     */
      ushort buffer_ID;              /* The buffer ID of the device where*/
                                     /* the data transfer is to begin.   */
                                     /* The meaning of this depends on   */
                                     /* mode setting.  See SPC (7.25)    */
      ushort reserved2;              /* Reserved for future use. Do NOT  */
                                     /* reference this field as it may   */
                                     /* affect future compatibility.     */
                                     /* Use memset() or bzero() to       */
                                     /* initialize these (and all)       */
                                     /* fields to 0.                     */
      ushort einval_arg;             /* Currently not used, but put here */
                                     /* as place holder for possible     */
                                     /* future use.                      */
      uint timeout_value;            /* In seconds                       */

      uint autosense_length;         /* This specifies the maximum size  */
                                     /* in bytes of the SCSI driver's    */
                                     /* autosense buffer referenced by   */
                                     /* the autosense_buffer_ptr field.  */
      uint64_t total_fragments;      /* Calculated and set by driver.    */
                                     /* Total number of fragments to     */
                                     /* send, including the fragment for */
                                     /* fragment_size_fraction if        */
                                     /* necessary.                       */
      uint64_t fragments_sent;       /* This is the number of fragments  */
                                     /* transferred successfully. If the */
                                     /* operation fails midway, this will*/
                                     /* contain the number of fragments  */
                                     /* successfully transferred.  If    */
                                     /* all fragments were transferred   */
                                     /* successfully, this is equal to   */
                                     /* total number of fragments.       */
                                     /* If the entire buffer was sent at */
                                     /* once, this will be set to 1.     */
      uint64_t fragment_size;        /* If less than data_length, then   */
                                     /* the buffer will be written to    */
                                     /* the device in fragments of this  */
                                     /* number of bytes.  Shall not      */
                                     /* exceed the max buffer capacity   */
                                     /* that this device supports for    */
                                     /* the WRITE BUFFER command         */
                                     /* (See SPC sect. 7.25 for details).*/
                                     /* A value of equal to data_length  */
                                     /* causes entire buffer to be       */
                                     /* written with a single            */
                                     /* WRITE BUFFER command.            */
                                     /* A value of 0 results in an error */
                                     /* of EINVAL.                       */
      uint64_t fragment_size_fraction; /* For internal driver use.  If the */
                                     /* data_length is not an even       */
                                     /* multiple of fragment_size, then  */
                                     /* this field contains the number of*/
                                     /* bytes in the final fragment,     */
                                     /* otherwise it is set to 0 and not */
                                     /* used.                            */
      uint64_t buffer_offset;        /* Offset within the device buffer  */
                                     /* where data transfer to begin     */
      uint64_t data_length;          /* Total number of bytes of buffer  */
                                     /* to transfer to the device        */ 
      ptr32 buffer;                  /* Pointer to host data buffer      */
      ptr32 autosense_buffer_ptr;    /* A pointer to the caller's        */
                                     /* autosense buffer for this SCSI   */
                                     /* command.                         */
                                     /* NOTE: if this is NULL the        */
                                     /* the adapter driver will throw    */
                                     /* away the sense data.             */
};
#endif /* _KERNEL */

/*
 * Define Device Structure (DDS) of the SCSI Adapter Driver
 *
 * NOTE: This structure is only supported for IBM created configuration
 * methods and should not be used for by other applications.  It is not
 * supported for 64 bit kernel extensions.
 *
 */
#ifndef  __64BIT_KERNEL
struct adap_ddi {
    ulong      bus_id;             /* adapter I/O bus id value     */
    ushort     bus_type;           /* adapter I/O bus type         */
    uchar      slot;               /* I/O slot number              */
    uchar      card_scsi_id;       /* the adapter's SCSI id        */
    uint       base_addr;          /* adapter base address         */
    char       resource_name[16];  /* resource name for err log*/
    int        battery_backed;     /* TRUE if this adapter and its */
                                   /* SCSI devices are batt-backed */
    int        dma_lvl;            /* dma level                    */
    int        int_lvl;            /* interrupt level              */
    int        int_prior;          /* interrupt priority           */
    int        cmd_delay;          /* delay (in seconds) after a   */
                                   /* reset or BDR before sending  */
                                   /* commands to devices which    */
                                   /* have the SC_DELAY_CMD bit set*/
    ulong      tcw_start_addr;     /* start addr of bus tcw space  */
    int        tcw_length;         /* length (in bytes) of tcw area*/
    char       tm_enabled;         /* true if odm tm variable is   */
                                   /* set to yes                   */
    char       bb_stream;          /* true if we can enable nibble */
                                   /* mode for this model type     */
    char       cmd_queue;          /* true if adapter support cmd  */
                                   /* tag queuing                  */
    char       has_fuse;           /* true if adapter has a fuse   */
                                   /* else PTC is used             */
    int        tm_tcw_percent;     /* percentage of TM_tcw_length  */
    int        tm_tcw_length;      /* target mode tcw length       */
    ulong      tm_tcw_start_addr;  /* TCW start addr for target mode */
};
#endif

/*
  SCSI Inquiry structure passed by pointer to ioctl of adapter driver
  */
struct sc_inquiry {
    uchar scsi_id;       /* target device id */
    uchar lun_id;        /* target device logical unit (lun) */
    uchar get_extended;  /* = TRUE if getting extended inq */
    uchar inquiry_len;   /* number of bytes to transfer (0 - 255) */
    uchar *inquiry_ptr;  /* pointer to inquiry data buffer */
    uchar code_page_num; /* code page # when get_extended=TRUE */
    uchar rsv3;          /* reserved, should be set to zero */
    uchar rsv4;          /* reserved, should be set to zero */
    uchar flags;         /* flags:  SC_ASYNC */
    uint  rsv5;          /* reserved, should be set to zero */
};
#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for applications. It is only
 *       for internal device driver use.
 *
 * SCSI Inquiry structure passed by pointer to ioctl of adapter driver
 * used internally by the adapter driver for support of 64-bit applications.
 */

struct sc_inquiry64 {
    uchar scsi_id;       /* target device id */
    uchar lun_id;        /* target device logical unit (lun) */
    uchar get_extended;  /* = TRUE if getting extended inq */
    uchar inquiry_len;   /* number of bytes to transfer (0 - 255) */
    ptr64 inquiry_ptr;   /* pointer to inquiry data buffer */
    uchar code_page_num; /* code page # when get_extended=TRUE */
    uchar rsv3;          /* reserved, should be set to zero */
    uchar rsv4;          /* reserved, should be set to zero */
    uchar flags;         /* flags:  SC_ASYNC */
    uint  rsv5;          /* reserved, should be set to zero */
};

/*
 * NOTE: This structure is not supported for applications. It is only
 *       for internal device driver use.
 *
 * SCSI Inquiry structure passed by pointer to ioctl of adapter driver
 * used internally by the adapter driver for support of 34-bit applications
 * by 64-bit kernel extension
 */

struct sc_inquiry32 {
    uchar scsi_id;       /* target device id */
    uchar lun_id;        /* target device logical unit (lun) */
    uchar get_extended;  /* = TRUE if getting extended inq */
    uchar inquiry_len;   /* number of bytes to transfer (0 - 255) */
    ptr32 inquiry_ptr;   /* pointer to inquiry data buffer */
    uchar code_page_num; /* code page # when get_extended=TRUE */
    uchar rsv3;          /* reserved, should be set to zero */
    uchar rsv4;          /* reserved, should be set to zero */
    uchar flags;         /* flags:  SC_ASYNC */
    uint  rsv5;          /* reserved, should be set to zero */
};

#endif

/*
  SCSI Read structure passed by pointer to ioctl of adapter driver
  (This uses the 6-byte SCSI Read command.)
  */
struct sc_readblk {
    uchar scsi_id;       /* target device id */
    uchar lun_id;        /* target device logical unit (lun) */
    short blklen;        /* number of bytes in device block */
    int   blkno;         /* block number on device to read */
    uint  timeout_value; /* timeout value for command, in secs. */
    uchar *data_ptr;     /* pointer to buffer for read data */
    uchar rsv1;          /* reserved, should be set to zero */
    uchar rsv2;          /* reserved, should be set to zero */
    uchar rsv3;          /* reserved, should be set to zero */
    uchar flags;         /* flags:  SC_ASYNC, SC_NODISC */
    uint  rsv4;          /* reserved, should be set to zero */
};
#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read structure passed by pointer to ioctl of adapter driver
 * to support 64-bit applications(This uses the 6-byte SCSI Read command.)
 */

struct sc_readblk64 {
    uchar scsi_id;       /* target device id */
    uchar lun_id;        /* target device logical unit (lun) */
    short blklen;        /* number of bytes in device block */
    int   blkno;         /* block number on device to read */
    uint  timeout_value; /* timeout value for command, in secs. */
    ptr64 data_ptr;      /* pointer to buffer for read data */
    uchar rsv1;          /* reserved, should be set to zero */
    uchar rsv2;          /* reserved, should be set to zero */
    uchar rsv3;          /* reserved, should be set to zero */
    uchar flags;         /* flags:  SC_ASYNC, SC_NODISC */
    uint  rsv4;          /* reserved, should be set to zero */
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read structure passed by pointer to ioctl of adapter driver
 * to support 32-bit applications by 64-bit kernel extensions.
 */

struct sc_readblk32 {
    uchar scsi_id;       /* target device id */
    uchar lun_id;        /* target device logical unit (lun) */
    short blklen;        /* number of bytes in device block */
    int   blkno;         /* block number on device to read */
    uint  timeout_value; /* timeout value for command, in secs. */
    ptr32 data_ptr;      /* pointer to buffer for read data */
    uchar rsv1;          /* reserved, should be set to zero */
    uchar rsv2;          /* reserved, should be set to zero */
    uchar rsv3;          /* reserved, should be set to zero */
    uchar flags;         /* flags:  SC_ASYNC, SC_NODISC */
    uint  rsv4;          /* reserved, should be set to zero */
};
#endif
/*
  SCSI Start Unit structure passed by pointer to ioctl of adapter driver
  */
struct sc_startunit  {
    uchar scsi_id;        /* target device id */
    uchar lun_id;         /* target device logical unit (lun) */
    uchar start_flag;     /* must be set to TRUE for starting, */
                          /* FALSE to stop device */
    uchar immed_flag;     /* if set to TRUE, command completes */
                          /* immediately (if supported by device) */
                          /* if FALSE, command does not return until */
                          /* device has completed the command. */
    uint  timeout_value;  /* timeout value for command, in secs. */
    uchar rsv1;           /* reserved, should be set to zero */
    uchar rsv2;           /* reserved, should be set to zero */
    uchar rsv3;           /* reserved, should be set to zero */
    uchar flags;          /* flags:  SC_ASYNC */
    uint  rsv4;           /* reserved, should be set to zero */
};

/*
  SCSI Test Unit Ready structure passed by pointer to ioctl of adapter driver
  */
struct sc_ready  {
    uchar scsi_id;            /* target device id */
    uchar lun_id;             /* target device logical unit (lun) */
    uchar status_validity;    /* 0 = no valid status                  */
                              /* 1 = valid SCSI bus status only       */
    uchar scsi_status;        /* SCSI bus status (if valid)           */
    uchar rsv1;               /* reserved, should be set to zero */
    uchar rsv2;               /* reserved, should be set to zero */
    uchar rsv3;               /* reserved, should be set to zero */
    uchar flags;              /* flags:  SC_ASYNC */
    uint  rsv4;               /* reserved, should be set to zero */
};


/*
  Download structure passed by pointer to ioctl of adapter driver
  */
struct sc_download {
    uchar option;          /* download option flag, see below */
    uchar rsv1;            /* reserved, should be set to zero */
    uchar rsv2;            /* reserved, should be set to zero */
    uchar rsv3;            /* reserved, should be set to zero */
    uint microcode_len;    /* length of microcode in bytes, includes
                              padding to 1 kilobyte boundary */
    uchar *microcode_ptr;  /* pointer to system memory address
                              of microcode to be downloaded, NULL
                              if requesting Version */
    uint version_number;   /* returned version number if requested,
                              or undefined if download */
    uint  rsv4;            /* reserved, should be set to zero */
};

/* download options */
#define SC_DOWNLOAD          1    /* download the microcode */
#define SC_VERSION_NUMBER    2    /* return version number of
                                     current microcode */
#define SC_ENABLE_CMD_Q      3    /* enable the command tag queuing */

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * Download structure passed by pointer to ioctl of adapter driver used
 * internally by driver for support of 64-bit applications.
 */
struct sc_download64 {
    uchar option;        /* download option flag, see below */
    uchar rsv1;          /* reserved, should be set to zero */
    uchar rsv2;          /* reserved, should be set to zero */
    uchar rsv3;          /* reserved, should be set to zero */
    uint microcode_len;  /* length of microcode in bytes, includes
                            padding to 1 kilobyte boundary */
    ptr64 microcode_ptr; /* pointer to system memory address
                            of microcode to be downloaded, NULL
                            if requesting Version */
    uint version_number; /* returned version number if requested,
                            or undefined if download */
    uint  rsv4;          /* reserved, should be set to zero */
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * Download structure passed by pointer to ioctl of adapter driver used
 * internally by 64-bit driver for support of 32-bit applications.
 */
struct sc_download32 {
    uchar option;        /* download option flag, see below */
    uchar rsv1;          /* reserved, should be set to zero */
    uchar rsv2;          /* reserved, should be set to zero */
    uchar rsv3;          /* reserved, should be set to zero */
    uint microcode_len;  /* length of microcode in bytes, includes
                            padding to 1 kilobyte boundary */
    ptr32 microcode_ptr; /* pointer to system memory address
                            of microcode to be downloaded, NULL
                            if requesting Version */
    uint version_number; /* returned version number if requested,
                            or undefined if download */
    uint  rsv4;          /* reserved, should be set to zero */
};
#endif

/*
  structure passed by pointer to SCIOEVENT ioctl of adapter driver
*/

struct    sc_event_struct {
    uchar    id;                 /* target/initiator SCSI ID being registered */
    uchar    lun;                /* LUN of initiator, set to 0 if target */
    uchar    mode;               /* indicate if ID is for target or initiator */
#define    SC_IM_MODE    0       /* this is an initiator mode ID */
#define    SC_TM_MODE    1       /* this is a target mode ID */
    uchar    resvd1;             /* reserved, should be set to zero */
    __ulong64_t  resvd2;         /* reserved, should be set to zero */
    __ulong64_t  async_correlator;  /* optional field for use by caller.
                                       value in this field is saved by
                                       adapter driver and passed back
                                       to caller's async func */
    void    (*async_func)();     /* device drivers's asynchronous
                                    event handler function address */
};

/*
  structure passed by adapter driver to the device driver's async func
*/

struct    sc_event_info {
    uchar    id;                 /* target/initiator ID event info is for */
    uchar    lun;                /* LUN of initiator, 0 if target device */
    uchar    mode;               /* indicate if ID is for target or initiator
                                    see possible values in sc_event_struct */
    uchar    resvd1;             /* reserved, should be set to zero */
    __ulong64_t  resvd2;         /* reserved, should be set to zero */
    int    events;               /* event being reported */
#define SC_FATAL_HDW_ERR    0x01 /* adapter fatal hardware failure     */
#define SC_ADAP_CMD_FAILED  0x02 /* unrecoverable adapter cmd failure  */
#define SC_SCSI_RESET_EVENT 0x04 /* SCSI bus reset detected            */
#define SC_BUFS_EXHAUSTED   0x08 /* maximum buffer usage detected      */
    dev_t    adap_devno;         /* device major/minor number of adapter
                                    reporting this async event information */
    __ulong64_t  async_correlator;  /* this value is a copy of the field
                                       of the same name passed by the
                                       caller in the sc_event_struct */
};

/*    
  start target device structure passed by pointer to ioctl of adapter driver
*/
struct    sc_strt_tgt {
    uchar    id;                 /* SCSI ID of the SCSI initiator */
    uchar    lun;                /* set to zero, as LUN ignored */
    uint    buf_size;            /* size in bytes for receive buffers.
                                    must be 4096 for IBM SCSI adapter */
    uint    num_bufs;            /* number of buffers to allocate */
    __ulong64_t  tm_correlator;  /* optional field for use by caller.
                                    value in this field is saved by
                                    adapter driver and passed back
                                    to caller's recv buf function */
    void    (*recv_func)();      /* address of caller's receive buf function */
    void    (*free_func)();      /* output parm: set to address of adapter
                                    driver's buffer free function */
    __ulong64_t  resvd1;         /* reserved, should be set to zero */
};

/*
  stop target device structure passed by pointer to ioctl of adapter driver
*/
struct    sc_stop_tgt {
    uchar    id;             /* SCSI ID of the SCSI initiator */
    uchar    lun;            /* set to zero, as LUN ignored */
    __ulong64_t   resvd1;    /* reserved, should be set to zero */
    __ulong64_t   resvd2;    /* reserved, should be set to zero */
};

/*
  Diagnostic / Error Logging structure used by adapter driver
  */
struct  rc  {                      /* adapter return code area      */
                                   /*   for all SCSI adapters:      */
    uchar diag_validity;           /*   = 0x00 diag_stat invalid    */
                                   /*   = 0x01 diag_stat valid      */
    uchar ahs_validity;            /*   = 0x00 AHS invalid          */
                                   /*   = 0x01 AHS = Driver Status  */
    uchar diag_stat;               /* Diagnostic Status (0 when     */
                                   /*  error logging)               */
#define SC_DIAG_MISCMPR  0x01      /* Data miscompare during diag   */
                                   /*  (mbox addr holds eff addr)   */
#define SC_DIAG_RECOV_PIO 0x02     /* Recovered PIO err occurred    */
                                   /*  (see AHS for PIO err, and    */
                                   /*   mbox addr for eff addr)     */
#define SC_DIAG_UNRECOV_PIO 0x04   /* Unrecovered PIO err occurred*/
                                   /*  (see AHS for PIO err, and    */
                                   /*   mbox addr for eff addr)     */
    uchar ahs;                     /* Additional Hardware Status    */
                                   /* (lsb)           (AHS)         */
                                   /*  Driver Status:               */
                                   /*  Note: at most, only one of   */
                                   /*    the following will be set  */
                                   /*    when the AHS is valid.     */
#define PIO_RD_OTHR_ERR    0x01    /* Other error on PIO Read op    */
#define PIO_WR_OTHR_ERR    0x02    /* Other error on PIO Write op   */
#define PIO_RD_DATA_ERR    0x04    /* Data parity on PIO Read op    */
#define PIO_WR_DATA_ERR    0x08    /* Data parity on PIO Write op   */
                                   /*  (for the above PIO errs, see */
                                   /*   mb_addr for eff addr, and   */
                                   /*   sys_rc for the csr value)   */
                                   /*  Note: errors during POS reg. */
                                   /*  accesses will have only the  */
                                   /*  mb_addr field filled in.     */
#define DMA_ERROR          0x10    /* Error during the DMA transfer */
                                   /*     (see sys_rc, below)       */
#define UNKNOWN_CARD_ERR   0x20    /* An unknown card error occurred*/
                                   /*     (POS, other regs valid,   */
                                   /*      except for ISR)          */
#define CARD_INTRPT_ERR    0x40    /* An invalid interrupt occurred */
                                   /*     (see ISR contents)        */
#define COMMAND_TIMEOUT    0x80    /* A command timeout occurred    */

    uint sys_rc;                   /* failed system call return code*/
                                   /* or, if PIO error, this is the */
                                   /* channel status reg contents.  */
    union {
        struct {
            uint errnum;           /*  4 bytes = unique error num.  */
            uint mb_num;           /*  4 bytes = this mailbox's num.*/
            uint mb_addr;          /*  4 bytes = addr of mbox on adap*/
                                   /*                 or addr of PIO err */
            uint buf_addr;         /*  4 bytes = Sys buf address    */
            int  x_aspace_id;      /* 4 bytes = xmem descr aspace_id  */
            int  x_subspace_id;    /* 4 bytes = xmem descr subspace_id */
            uint scb_ptr;          /*  4 bytes = pointer to sc_buf  */
            uint cmd_state;        /*  4 bytes = mailbox cmd state  */
            uint tcws_allocated;   /*  4 bytes = num tcws allocated    */
            uint tcws_start;       /* 4 bytes = starting tcw num   */
            uint sta_index;        /*  4 bytes = index into sta tab */
                                   /* the following areas give the  */
                                   /* adapter's register or memory  */
                                   /* contents.  refer to the SCSI  */
                                   /* Device Adapter hardware tech- */
                                   /* nical reference manual for the*/
                                   /* detailed description.         */
            char mbox[32];         /* 32 bytes = MBox contents      */
            char mb31_status[8];   /*  8 bytes = MBox 31 Status Area  */
            uint isr_val;          /*  4 bytes = ISR contents       */
            uchar resv[3];         /*  3 bytes = reserved           */
            uchar bcr_val;         /*  1 byte  = BCR contents       */
            uchar pos0_val;        /*  1 byte  = POS byte 0         */
            uchar pos1_val;        /*  1 byte  = POS byte 1         */
            uchar pos2_val;        /*  1 byte  = POS byte 2         */
            uchar pos3_val;        /*  1 byte  = POS byte 3         */
            uchar pos4_val;        /*  1 byte  = POS byte 4         */
            uchar pos5_val;        /*  1 byte  = POS byte 5         */
            uchar pos6_val;        /*  1 byte  = POS byte 6         */
            uchar pos7_val;        /*  1 byte  = POS byte 7         */
        }  card1;
        struct {
            uint errnum;                    /*  4 bytes = unique error num.  */
/* define PIO_RD_OTHR_ERR             0x01 */
/* define PIO_WR_OTHR_ERR             0x02 */
/* define PIO_RD_DATA_ERR             0x04 */
#define XMEM_COPY_ERROR               0x05  /* error occurred on copy    */
#define UNKNOWN_ADAPTER_ERROR         0x06  /* an unknown error occured  */
#define ADAPTER_INT_ERROR             0x07  /* an unknown or unexpected  */
                                            /* interrupt occurred.       */
/* define PIO_WR_DATA_ERR             0x08 */
#define UNEXPECTED_STATUS             0x09  /* rcvd unexp status from    */
                                            /* target scsi device.       */
#define ABORT_FAILED                  0x0a  /* msg error rcvd on abort   */
#define BDR_FAILED                    0x0b  /* msg error rcvd on bdr     */
#define UNINITIALIZED_RESELECT        0x0c  /* bad lun presented on bus  */
#define CHANNEL_CHK_ERROR             0x0d  /* a channel chk has occurred*/
#define BAD_PARITY_DETECTED           0x0e  /* bad parity on the scsi bus*/
#define GROSS_ERROR                   0x0f  /* a scsi gross error rcvd   */
/* define DMA_ERROR                   0x10 */
#define UNKNOWN_RESELECT_ID           0x11  /* invalid scsi id on the bus*/
#define UNKNOWN_MESSAGE               0x12  /* unknown scsi msg received */
#define PHASE_ERROR                   0x13  /* phase error on scsi bus   */
#define ERROR_NOT_EXTENT              0x14  /* ext message expected and  */
                                            /* and not received          */
#define UNEXPECTED_BUS_FREE           0x15  /* target device dropped off */
                                            /* the scsi bus unexpectedly */
#define UNEXPECTED_SELECT_TIMEOUT     0x16  /* a selection timeout occur-*/
                                            /* ed unexpectedly           */
#define SCSI_BUS_RESET                0x17  /* scsi bus reset detected   */
#define TERM_PWR_FAIL                 0x18  /* terminator power failed   */
#define TARGET_MODE_SCSI_ERROR        0x19  /* tgt mode protocol problem */
#define UNSTABLE_BUS_MODE             0x1A  /* lvd/se transition problem */
/* define COMMAND_TIMEOUT 0x80 */
            uchar scsi_cmd[12];             /* 12 bytes last SCSI cmd     */
            uchar target_id;                /* target scsi id         */
            uchar queue_state;
            uchar cmd_activity_state;
            uchar resource_state;
            uint buf_addr;               /*  4 bytes = Sys buf address    */
            int  x_aspace_id;            /* 4 bytes = xmem descr aspace_id */
            int  x_subspace_id;          /* 4 bytes = xmem descr subspace_id */
            uint scb_ptr;                /*  4 bytes = pointer to sc_buf  */
            uint reg_validity;           /* 4 bytes, reg vals invalid     */
                                         /* if this non-zero         */

            uchar istat_val;             /* 1 byte of the ISTAT         */
            uchar dstat_val;             /* 1 byte of DSTAT         */
            uchar sstat0_val;            /* 1 byte of SSTAT0         */
            uchar sstat1_val;            /* 1 byte of SSTAT1         */
            uchar sstat2_val;            /* 1 byte of SSTAT2         */
            uchar sdid_val;              /* 1 byte of SDID         */
            uchar scid_val;              /* 1 byte of SCID         */
            uchar ctest3_val;            /* 1 byte of CTEST3         */
            uint  dbc_val;               /* 4 byte of DBC         */
            uint  dsp_val;               /* 4 bytes of DSP         */
            uint  dsps_val;              /* 4 bytes of DSPS         */

                         /* for PCI SCSI, the following 2 bytes  */
                         /* are the PCI Device ID                */
            uchar pos0_val;              /*  1 byte  = POS byte 0         */
            uchar pos1_val;              /*  1 byte  = POS byte 1         */

                        /* for PCI SCSI, the following 2 bytes  */
                        /* are the Status register in Cfg space */
            uchar pos2_val;              /*  1 byte  = POS byte 2         */
            uchar pos3_val;              /*  1 byte  = POS byte 3         */

                        /* for PCI SCSI, the following byte is   */
                        /* the Revision Id register in Cfg space */
            uchar pos4_val;              /*  1 byte  = POS byte 4         */

                        /* for PCI SCSI, the following byte is   */
                        /* the scsi bus reset reason             */
            uchar pos5_val;              /*  1 byte  = POS byte 5         */


                        /* for PCI SCSI, the following byte is   */
                        /* the SCNTL0 register (arb & chip mode) */
            uchar pos6_val;              /*  1 byte  = POS byte 6         */

            uchar pos7_val;              /*  1 byte  = POS byte 7         */
            uchar sist0_val;             /* SIST0 register (interrupts)     */
            uchar sist1_val;             /* SIST1 register (interrupts)     */
            uchar ssid_val;              /* SSID register (reselector's id) */
            uchar sxfer_val;             /* SXFER register (sync xfers)     */
            uchar scntl2_val;            /* SCNTL2 register (sdu bit)       */
            uchar scntl3_val;            /* SCNTL3 register (sync xfers)    */
            uchar gpreg_val;             /* GPREG register (ckt breaker)    */
            uchar scntl1_val;            /* SCNTL1 register (sync xfers)    */
            uint scratcha_val;           /* SCRATCHA register (tag/flags) */
            uint scratchb_val;           /* SCRATCHB register (tag/flags) */
            uint  dsa_val;               /* 4 bytes of DSA            */
            uchar sbcl_val;              /* SBCL register (bus control)     */
            uchar sfbr_val;              /* SFBR register (first byte recv) */
            uint scratchg_val;           /* SCRATCHG register (set sense) */
            uint scratchh_val;           /* SCRATCHH register (tm flags)  */
            char reserved[2];

        }  card2;
        struct {
            uint errnum;                 /* 4 bytes = unique error num.  */
            uchar reply[0x2C];           /* error/reply element       */
            __ulong32_t adp_struct;      /* addr of adapter struct  */
            __ulong32_t dma_err;         /* d_complete return code  */
            __ulong32_t pio_addr;        /* addr of PIO exception   */
            __ulong32_t pio_size;        /* size of PIO            */
            uchar target_id;             /* target scsi id           */
            uchar io_reg;                /* contents of io register       */
            uchar pos0_val;              /*  1 byte  = POS byte 0        */
            uchar pos1_val;              /*  1 byte  = POS byte 1        */
            uchar pos2_val;              /*  1 byte  = POS byte 2        */
            uchar pos3_val;              /*  1 byte  = POS byte 3        */
            uchar pos4_val;              /*  1 byte  = POS byte 4        */
            uchar pos5_val;              /*  1 byte  = POS byte 5        */
            uchar pos3b_val;             /*  1 byte  = POS byte 3b       */
            uchar pos4b_val;             /*  1 byte  = POS byte 4b       */
        }  card3;
        struct {
            uint errnum;                 /* 4 bytes = unique error num.  */
                 uchar scsi_stat;        /* SCSI status byte             */
                 uchar cmd_err;          /* SCB command error code       */
                 uchar dev_err;          /* SCB device error code        */
                 uchar cdb[36];          /* SCSI command descriptor block*/
                 __ulong32_t scsi_struct;/* pointer to scsi_info struct  */
                } card4;
    } un;
};

/*
  Diagnostic structure passed by pointer to ioctl of adapter driver
  */
struct sc_card_diag  {
    uchar  option;           /* diagnostic option, see below  */
    uchar  rsv1;             /* reserved, should be set to zero */
    uchar  rsv2;             /* reserved, should be set to zero */
    uchar  rsv3;             /* reserved, should be set to zero */
    uint   timeout_value;    /* timeout value for command, in secs. */
    uint   rsv4;             /* reserved, should be set to zero */
    struct rc diag_rc;       /* adapter return code structure */
                             /*     see struct rc declaration */
};

/* option                  */
#define SC_CARD_DIAGNOSTICS    0x00  /* execute card diagnostics       */
#define SC_RESUME_DIAGNOSTICS  0x01  /* resume after diag cmd failure  */
#define SC_CARD_SCSI_WRAP      0x03  /* execute card SCSI wrap tests   */
#define SC_CARD_REGS_TEST      0x04  /* write/read/cmpr card regs      */
#define SC_CARD_POS_TEST       0x05  /* write/read/cmpr card POS regs  */
/*#define SC_SCSI_BUS_RESET */       /* issue SCSI bus reset pulse,    */
				     /* see sc_buf definition          */



/*
  RAM Test structure passed by pointer to ioctl of adapter driver
  */
struct sc_ram_test  {
    uchar  option;           /* test option flag, see below   */
    uchar  rsv1;             /* reserved, should be set to zero */
    uchar  rsv2;             /* reserved, should be set to zero */
    uchar  rsv3;             /* reserved, should be set to zero */
    uint   timeout_value;    /* timeout value for command, in secs. */
    uint   rsv4;             /* reserved, should be set to zero */
    uint   card_buf_addr;    /* card buffer address           */
    uint   buffer_length;    /* length of buffer in bytes     */
    uchar  *buffer_ptr;      /* pointer to buffer             */
    struct rc ram_rc;        /* adapter return code structure */
                             /*     see struct rc declaration */
};

/* option                  */
#define SC_RAM_READ            0x01  /* read the adapter RAM       */
#define SC_RAM_WRITE           0x02  /* write data pattern to RAM  */

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * RAM Test structure passed by pointer to ioctl of adapter driver used
 * internally by driver for support of 64-bit applications.
 */

struct sc_ram_test64  {
    uchar  option;           /* test option flag, see below   */
    uchar  rsv1;             /* reserved, should be set to zero */
    uchar  rsv2;             /* reserved, should be set to zero */
    uchar  rsv3;             /* reserved, should be set to zero */
    uint   timeout_value;    /* timeout value for command, in secs. */
    uint   rsv4;             /* reserved, should be set to zero */
    uint   card_buf_addr;    /* card buffer address           */
    uint   buffer_length;    /* length of buffer in bytes     */
    ptr64  buffer_ptr;       /* pointer to buffer             */
    struct rc ram_rc;        /* adapter return code structure */
                             /*     see struct rc declaration */
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * RAM Test structure passed by pointer to ioctl of adapter driver used
 * internally by 64-bit driver for support of 32-bit applications.
 */

struct sc_ram_test32  {
    uchar  option;           /* test option flag, see below   */
    uchar  rsv1;             /* reserved, should be set to zero */
    uchar  rsv2;             /* reserved, should be set to zero */
    uchar  rsv3;             /* reserved, should be set to zero */
    uint   timeout_value;    /* timeout value for command, in secs. */
    uint   rsv4;             /* reserved, should be set to zero */
    uint   card_buf_addr;    /* card buffer address           */
    uint   buffer_length;    /* length of buffer in bytes     */
    ptr32  buffer_ptr;       /* pointer to buffer             */
    struct rc ram_rc;        /* adapter return code structure */
                             /*     see struct rc declaration */
};

#endif



/*
  SCSI device driver error log record
*/
struct sc_error_log_df {
    unsigned int error_id;         /* error type id    */
    char     resource_name[ERR_NAMESIZE];/* ddi resource name    */
#ifdef MPIO
    ushort   path_id;              /* path id error occured on             */
#endif
    struct scsi scsi_command;      /* command that caused error            */
    uchar status_validity;         /* least significant bit - scsi_status  */
                                   /* valid, next least significant bit -  */
                                   /* card status valid                    */
    uchar scsi_status;             /* returned SCSI Bus status             */
    uchar general_card_status;     /* generic SCSI adapter card status byte*/
    uchar reserved1;               /* reserved                             */
    uchar req_sense_data[128];     /* request sense data                   */
    uint  reserved2;               /* reserved for dd use                  */
    uint  reserved3;               /* reserved for dd use                  */
};

/*
  SCSI device driver error log record
*/
struct sc_estruct {
#ifdef MPIO
    ushort  path_id;               /* path id error occured on              */
#endif
    struct  scsi scsi_command;     /* command that caused error             */
    uchar   status_validity;       /* least significant bit - scsi_status   */
                                   /* valid, next least significant bit -   */
                                   /* card status valid                     */
    uchar   scsi_status;           /* returned SCSI Bus status              */
    uchar   general_card_status;   /* generic SCSI adapter card statusbyte  */
    uchar   reserved1;             /* reserved                              */
    uchar   req_sense_data[128];   /* request sense data                    */
    uint    reserved2;             /* reserved for dd use                   */
    uint    reserved3;             /* reserved for dd use                   */
};

struct sc_error_def {
    struct err_rec0     errhead;    /* error log header info        */
    struct sc_estruct   data;       /* driver dependent err data    */
};

#endif /* _H_SCSI */
