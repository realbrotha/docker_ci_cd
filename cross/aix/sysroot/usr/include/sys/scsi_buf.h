/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/scsi_buf.h 1.61.1.4                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1995,2011              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)72       1.61.1.4  src/bos/kernel/sys/scsi_buf.h, sysxfcp, bos53X, x2011_14B1 1/11/11 17:04:58 */

#ifndef _H_SCSIBUF
#define _H_SCSIBUF
/*
 * COMPONENT_NAME: (SYSXSCSI) IBM SCSI-3 Header File
 *
 * FUNCTIONS:	IBM SCSI-3  Header File.  
 *		
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1995, 2009
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


/*****************************************************************************/
/*  SCSI-3 adapter driver IOCTL command options                              */
/*****************************************************************************/
#define SCIOLSTART	899	 /* Causes the adapter driver to allocate 
				   resources for the device with SCSI ID 
				   and Lun specified in the scsi_sciolst 
				   structure. For this operation you must 
				   specify the "arg" parameter with the 
				   address of a data area which is defined 
				   by the scsi_sciolst structure. */


#define SCIOLSTOP	898	/* Causes the adapter to release resources
				   for the device with SCSI ID and Lun 
				   specified in the scsi_sciolst structure.
				   For this operation you must specify
				   the "arg" parameter with the address of
				   a data area which is defined by the
				   scsi_sciolst structure. */

#define	SCIOLINQU       897	/* cause adapter driver to run a SCSI device
				   inquiry command to the IDLUN device. For
				   this operation, you must specify the "arg"
				   parameter with the address of a data area
				   which is defined by the scsi_inquiry 
				   structure */

#define SCIOLSTUNIT	896	/* cause adapter driver to run a SCSI device
				   start unit command to an id/lun.  The "arg"
				   parameter specifies the address of the data
				   area defined by the scsi_startunit 
				   structure */
#define SCIOLTUR	895	/* cause adapter driver to run a SCSI device
				   test unit ready command to an id/lun.  The
				   "arg" parameter specifies the address of
				   the data area defined by the scsi_ready
				   structure */
#define	SCIOLREAD	894	/* cause adapter driver to run a SCSI device
				   read command to the IDLUN device to read
				   a single block.  For this operation, you
				   must specify the "arg" parameter with the
				   address of a data area which is defined
				   by the scsi_readblk structure */

#define	SCIOLEVENT	893	/* registers an async event notification 
				   with the adapter driver for this device */



#define SCIOLCMD	892     /* Causes the adapter driver to issue the
				   SCSI command contained in the scsi_iocmd
				   argument to the id/lun. For this
				   operation you must specify the "arg"
				   parameter with the address of the data 
				   area which is defined by the 
				   scsi_iocmd structure.	*/


#define SCIOLHALT      	891     /* Causes the adapter driver to issue
				   an abort task set for the device with 
				   SCSI ID and Lun specified in the scsi_siolst 
				   structure. For this operation you must 
				   specify the "arg" parameter with the 
				   address of a data area which is defined 
				   by the scsi_sciolst structure. */

#define SCIOLRESET     	890     /* Causes the adapter driver to issue
				   a target reset (BDR) for the device with 
				   SCSI ID and Lun specified in the scsi_sciolst 
				   structure. For this operation you must 
				   specify the "arg" parameter with the 
				   address of a data area which is defined 
				   by the scsi_sciolst structure.*/

#define SCIOLNMSRV     	889     /* Causes the adapter driver to issue
				   a request to the name server 
				   requesting a list of all known SCSI IDs
				   For this operation you must
				   specify the "arg" parameter with the 
				   address of a data area which is defined
				   by the scsi_nmserv structure. */

#define SCIOLQWWN     	888     /* Causes the adapter driver to issue
				   a request to the name server 
				   requesting the SCSI ID of the specified
				   world wide name.
				   For this operation you must
				   specify the "arg" parameter with the 
				   address of a data area which is defined
				   by the scsi_qry_wwn structure. */

#define SCIOLPAYLD      887      /* Causes the adapter driver to issue
                                    a caller specified payload via the
                                    hardware transport layer to the specified
                                    SCSI ID. For this operation you must
                                    specify the "arg" parameter with the 
                                    address of a data area which is defined
                                    by the scsi_trans_payld structure. 
                                    For FCP devices this will create
                                    a single exchange, transmit one
                                    sequence, then transfer sequence 
                                    initiative to the recipient to issue one
                                    response sequence.*/

#define SCIOLPASSTHRUHBA 886     /* Causes the adapter driver to issue
                                    a passthru command to the FC adapter */

#define SCIOLCHBA        885     /* Causes the adapter driver to get the
                                    port statistics, get RNID data, or set
                                    RNID data from or on the FC adapter. */

#define SCIOLAUTHSET     884     /* set up one authentication entry  */

#define SCIOLAUTHCLR     883     /* clear all authentication entries */

#define SCIOLSTARTTGT    882     /* Causes the adapter driver to allocate
                                   resources and enable buffers and ids for
                                   target mode devices. The "arg" parameter 
                                   for this ioctl should be set to the 
                                   address of an scsi_strt_tgt structure.*/

#define SCIOLSTOPTGT     881    /* Causes the adapter to release target  
                                   mode resources. The "arg" parameter
                                   for this ioctl should be set to the
                                   address of an scsi_stop_tgt structure.*/

#define SCIOLADAPEVENTLOG 880     /* Causes the adapter driver to issue
                                     command to read errorlog buffer. The
                                     ioctl uses the scsi_adap_event log 
                                     struct.*/

/* 860 through 865 are reserved for use of SAS Devices. */
/* 801 thru 804 are reserved */

/*****************************************************************************/
/*  FC SCSI Connection defines  					     */
/*****************************************************************************/
#define FC_CON_NONE   0x0       /* This adapter is not connected.          */
#define FC_CON_PT_PT  0x1       /* This adapter is connected point to      */
                                /* point.                                  */
#define FC_CON_FABRIC 0x2       /* This adapter is connected to Fabric     */
#define FC_CON_AL     0x3       /* This adapter connected to a Loop        */

/*****************************************************************************/
/*  SCSI-3 structures							     */
/*****************************************************************************/

/* refer to the SCSI-3 ANSI X3T10/994D for information         */

struct scsi_cdb {		     /* structure of the SCSI cmd block */
	uchar	scsi_op_code;	     /* first byte of SCSI cmd block    */
	uchar	scsi_bytes[15];	     /* other bytes of SCSI cmd block   */
};

struct scsi_cmd {
	uchar	scsi_length;	/* byte length of scsi cmd (6,10,12,16) */
	uchar	flags;		/* flags for use with the 		*/
				/* physical scsi command 		*/
				/* See scsi struct in scsi.h for valid  */
				/* defines.				*/

	struct scsi_cdb	scsi_cmd;/* the actual SCSI cmd                 */
};
/*****************************************************************************/
/*  Version numbers of structures in this file.				     */
/*****************************************************************************/

#define SCSI_VERSION_0	 0x00           /* First version of the structure. */
#define SCSI_VERSION_1	 0x01           /* Second version of the structure.*/
#define SCSI_VERSION_2	 0x02           /* Third version of the structure. */




/*
 * scsi_buf structure used by SCSI device driver to communicate with
 * the SCSI adapter driver.  This is passed to the adapter driver
 * strategy routine entry point.
 */
struct scsi_buf {
	struct buf	bufstruct;	/* buffer structure containing   */
					/* request for device            */
	struct buf	*bp;		/* pointer back to original      */
					/* buffer structure list for     */
					/* command coalescing            */
	ushort          version;	/* The version number of this    */
					/* structure.  This allows the   */
					/* structure to expand in the    */
					/* future.                       */
/*  For this structure the version field must have a value of            */
/*  SCSI_VERSION_2                                                       */
	struct scsi_cmd	scsi_command;	/* the information relating      */
					/* strictly to the scsi command  */
					/* itself 			 */
        ushort io_priority;             /* I/O Priority for task         */
	union {
		ushort retry_delay_code; /* this value is filled in by the */
					/* protocol driver to inform the head */
					/* driver how long to hold off I/O if */
					/* the device can’t process a cm code */
					/* definition -  0x0001-0xffef  time */
					/* delay value */
					/* each tick represents 100 msec */
#define RETRY_TIME_MAX	0xffef
					/* SC_BUSY  0xfff0-0xfffd reserved  */
					/*          0xfffe stop sending cmds */
					/*          0xffff unable to process cmd */
					/* SC_QUEUE_FULL  0xfff0-0xffff reserved */
		ushort reserved;              /* reserved for future use */

	} un;

	uint	timeout_value;		/* timeout value for the command,*/ 
					/* in units of seconds           */
	uchar	status_validity; 	/* least significant bit - scsi_status
					   valid, next least significant bit -
					   adapter status valid */
					/* see sc_buf in scsi.h for defines */

	uchar	scsi_status;            /* returned SCSI status            */
					/* see defines in sc_buf's         */
					/* scsi_status field in scsi.h for */
					/* valid values                    */

	uchar	adapter_status;         /* generic FCP adapter status byte */

#define SCSI_HOST_IO_BUS_ERR      0x01	/* indicates a Host I/O Bus error  */
					/* condition. 			   */  

#define SCSI_TRANSPORT_FAULT      0x02  /* indicates a failure of the      */
					/* transport layer.  		   */

#define SCSI_CMD_TIMEOUT          0x03  /* the command did not complete    */
					/* before timeout_value units      */
					/* expired. 			   */

#define SCSI_NO_DEVICE_RESPONSE   0x04  /* the target device did not       */
					/* respond to attempts to select it*/

#define SCSI_ADAPTER_HDW_FAILURE  0x05  /* the adapter is indicating a     */
					/* hardware failure.               */

#define SCSI_ADAPTER_SFW_FAILURE  0x06  /* the adapter is indicating a     */
					/* microcode failure. 		   */

#define SCSI_WW_NAME_CHANGE       0x07  /* the adapter detected that the   */
					/* device at this SCSI id has a new*/
					/* world wide name. This is for FCS*/
					/* SCSI only.   		   */

#define SCSI_FUSE_OR_TERMINAL_PWR  0x08 /* the adapter is indicating a     */
					/* blown fuse or bad termination.  */

#define SCSI_TRANSPORT_RESET	   0x09 /* the adapter detected an external*/
					/* SCSI bus reset. 		   */

#define SCSI_TRANSPORT_BUSY	   0x0a /* the transport layer is busy     */

#define SCSI_TRANSPORT_DEAD        0x0b /* the transport layer is          */
					/* currently inoperative and is    */
					/* likely to remain this way for an*/
					/* extended time.                  */ 

#define SCSI_VERIFY_DEVICE         0x0c /* the adapter is indicating that  */
                                        /* the target driver should redrive*/
                                        /* the open sequence.              */   
#define SCSI_TRANSPORT_MIGRATED    0x0d /* transport migrated              */
#define SCSI_ERROR_NO_RETRY        0x0e /* An error occured, do not retry  */
#define SCSI_ERROR_DELAY_LOG       0x0f /* An error occured, only log an   */
                                        /* error if max_retries exceeded   */

	uchar  add_device_status;       /* Additional device status.       */
					/* For FCP devices, this field     */
					/* contains the FCP response code. */
					/* For P1394 devices, this field   */
					/* contains the SBP status         */
			
	ushort add_adap_status;      /* Additional adapter status	   */
#define SCSI_ADAP_STAT_NO_RETRY  0x1 /* The adapter driver is indicating   */
				     /* that a retry of this command will  */
				     /* most likely fail.                  */

#define SCSI_ADAP_STAT_NO_DELAY  0x2 /* The adapter driver is indicating   */
				     /* that no delays should be injected  */
				     /* between retries of this command.   */
#define SCSI_UPDATE_RESERVES     0x3 /* The adapter driver is indicating   */
				     /* that an event has occurred that    */
				     /* requires the caller to             */
				     /* reestablishing any reservations    */
#define SCSI_ADAP_NOT_PATH_ERR   0x4 /* The adapter driver is indicating   */
                                     /* that this adapter reported error   */
                                     /* is actually a hardware/media error */
                                     /* with the target device.  This is   */
                                     /* not a path or transport related    */
                                     /* issue.  Do not count this error    */
                                     /* as a path related error.           */


	uchar  adap_q_status;        /* adapter's device queue status. This*/
				     /* specifies whether or not the SCSI  */
				     /* adapter driver and SCSI adapter    */
				     /* cleared their queues for this 	   */
				     /* device or not.  A value of 0       */
				     /* indicates that the queue has been  */
				     /* cleared.			   */
				     /* See sc_buf in scsi.h for some      */
				     /* valid defines.			   */
	     
	uchar	     q_tag_msg;	     /* Queue Tag Message Field- Specifies */
				     /* whether or not the SCSI device should*/
				     /* queue this command and if so what   */
				     /* type of queuing it should use.	    */
				     /* See sc_buf in scsi.h for            */
				     /* valid defines.			    */


	uchar        flags;	     /* flags to SCSI adapter driver        */
				     /* See sc_buf in scsi.h for            */
				     /* some valid defines.	            */
	ushort        dev_flags;     /* flags to the SCSI adapter driver    */

#define SCSI_BURST_SIZE_VALID  0x80  /* This indicates that the             */
				     /* dev_burst_len field is valid.       */
#define FC_DFLT         0x0;         /* Use the SCSI adapter driver's   */
				     /* default FC class for this       */
				     /* command.                        */
#define FC_CLASS1	0x1          /* Use FC Class 1 for this command.*/
#define FC_CLASS2	0x2          /* Use FC Class 2 for this command.*/
#define FC_CLASS3	0x3          /* Use FC Class 3 for this command.*/
#define FC_CLASS4	0x4          /* Use FC Class 4 for this command.*/


	uchar     adap_set_flags;    /* These flags are set by the SCSI */
				     /* adapter driver when a command   */
				     /* is returned.			*/
/* SC_AUTOSENSE_DATA_VALID= 0x1 defined in scsi.h                       */
				     /* This indicates the SCSI adapter */
				     /* driver has placed the autosense */
				     /* data for this command failure   */
				     /* in the buffer referenced by the */
				     /* field autosense_buffer_ptr.	*/
/* SC_RET_ID=               0x2 defined in scsi.h                       */  
				     /* The scsi_id of this device is   */
				     /* different than the scsi_id      */
				     /* provided by the caller. The     */
				     /* scsi_id field has been updated  */
				     /* with current scsi_id for the    */
				     /* device with this world wide name*/

	ushort	autosense_length;    /* This specifies the maximum size */
				     /* in bytes of the SCSI head's     */
				     /* autosense buffer referenced by  */
				     /* the autosense_buffer_ptr field.	*/

	char   *autosense_buffer_ptr;/* A pointer to the SCSI head's    */
				     /* autosense buffer for this SCSI	*/
				     /* command.			*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns autosense,  */
				     /* then the adapter driver will 	*/
				     /* throw away the autosense data.	*/

	ushort	add_status_length;   /* This specifies the maximum size */
				     /* in bytes of the SCSI head's     */
				     /* additional status buffer        */
				     /* referenced by the               */
				     /* add_status_buffer_ptr field.	*/

	char   *add_status_buffer_ptr;/* A pointer to the SCSI head's   */
				     /* additional status buffer for    */
				     /* this SCSI command.		*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns additional  */
				     /* status then the adapter driver  */
				     /* will throw away the additional  */
				     /* status data.	                */

	uint     dev_burst_len;      /* This is devices maximum burst   */
				     /* size (in bytes)for this command.*/
				     /* For FCP if this is set, then    */
				     /* the SCSI adapter will not use   */
				     /* FCP_XFER_RDYs on writes, but    */
				     /* instead set the write burst size*/
				     /* to this value.  Otherwise       */
				     /* FCP_XFER_RDYs will be used on   */
				     /* FCP writes.                     */
	struct   scsi_buf *next;     /* If the hardware, as well as     */
				     /* both the SCSI head and SCSI     */
				     /* adapter support the chaining    */
				     /* of commands, this field can be  */
				     /* used to chain SCSI commands.    */

	struct   scsi_buf *prev;     /* If the hardware, as well as     */
				     /* both the SCSI head and SCSI     */
				     /* adapter support the chaining    */
				     /* of commands, this field can be  */
				     /* used to chain SCSI commands.    */
        unsigned long long adap_work;/* This field is reserved for the  */
				     /* adapter driver's use.           */
        unsigned long long adap_work2;/* This field is reserved for the */
				     /* adapter driver's use.           */


	unsigned long long scsi_id;  /* This is the 64-bit SCSI ID for  */
				     /* the device.			*/

	unsigned long long lun_id;   /* This is the 64-bit lun ID for   */
				     /* the device.			*/
        void *kernext_handle;        /* This is a handle that a kernel  */
				     /* extension can be set to the     */
				     /* kernext_handle returned from    */
				     /* SCIOLSTART if one was returned. */
        uint variable_cdb_length;    /* variable CDB length.		*/
        char *variable_cdb_ptr;      /* pointer to the variable CDB.    */
};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * scsi_bufv0 structure used by SCSI device driver to communicate with
 * legacy SCSI adapter drivers.  This is passed to the adapter driver
 * strategy routine entry point.
 */
struct scsi_bufv0 {
	struct buf	bufstruct;	/* buffer structure containing   */
					/* request for device            */
	struct buf	*bp;		/* pointer back to original      */
					/* buffer structure list for     */
					/* command coalescing            */
	ushort          version;	/* The version number of this    */
					/* structure.  This allows the   */
					/* structure to expand in the    */
					/* future.                       */

/*  For this structure the version field must have a value of            */
/*  SCSI_VERSION_0                                                       */
	struct scsi_cmd	scsi_command;	/* the information relating      */
					/* strictly to the scsi command  */
					/* itself 			 */
        ushort io_priority;             /* I/O Priority for task         */
	union {
		ushort retry_delay_code; /* this value is filled in by the */
					/* protocol driver to inform the head */
					/* driver how long to hold off I/O if */
					/* the device can’t process a cm code */
					/* definition -  0x0001-0xffef  time */
					/* delay value */
					/* each tick represents 100 msec */
#define RETRY_TIME_MAX	0xffef
					/* SC_BUSY  0xfff0-0xfffd reserved  */
					/*          0xfffe stop sending cmds */
					/*          0xffff unable to process cmd */
					/* SC_QUEUE_FULL  0xfff0-0xffff reserved */
		ushort reserved;              /* reserved for future use */

	} un;

	uint	timeout_value;		/* timeout value for the command,*/ 
					/* in units of seconds           */
	uchar	status_validity; 	/* least significant bit - scsi_status
					   valid, next least significant bit -
					   adapter status valid */
					/* see sc_buf in scsi.h for defines */

	uchar	scsi_status;            /* returned SCSI status            */
					/* see defines in sc_buf's         */
					/* scsi_status field in scsi.h for */
					/* valid values                    */

	uchar	adapter_status;         /* generic FCP adapter status byte */
					/* See defines under adapter_status*/
					/* field in scsi_buf struct        */

	uchar  add_device_status;       /* Additional device status.       */
					/* For FCP devices, this field     */
					/* contains the FCP response code. */
					/* For P1394 devices, this field   */
					/* contains the SBP status         */
			
	ushort add_adap_status;      /* Additional adapter status	   */
				     /* See defines under                  */
				     /* add_adap_status field in scsi_buf  */
				     /* struct                             */  
	uchar  adap_q_status;        /* adapter's device queue status. This*/
				     /* specifies whether or not the SCSI  */
				     /* adapter driver and SCSI adapter    */
				     /* cleared their queues for this 	   */
				     /* device or not.  A value of 0       */
				     /* indicates that the queue has been  */
				     /* cleared.			   */
				     /* See sc_buf in scsi.h for some      */
				     /* valid defines.			   */
	     
	uchar	     q_tag_msg;	     /* Queue Tag Message Field- Specifies */
				     /* whether or not the SCSI device should*/
				     /* queue this command and if so what   */
				     /* type of queuing it should use.	    */
				     /* See sc_buf in scsi.h for            */
				     /* valid defines.			    */


	uchar        flags;	     /* flags to SCSI adapter driver        */
				     /* See sc_buf in scsi.h for            */
				     /* some valid defines.	            */
	ushort        dev_flags;     /* flags to the SCSI adapter driver    */
				     /* See defines under dev_flags         */
				     /* field in scsi_buf struct            */
	

	uchar     adap_set_flags;    /* These flags are set by the SCSI */
				     /* adapter driver when a command   */
				     /* is returned.			*/
/* SC_AUTOSENSE_DATA_VALID= 0x1 defined in scsi.h                       */
				     /* This indicates the SCSI adapter */
				     /* driver has placed the autosense */
				     /* data for this command failure   */
				     /* in the buffer referenced by the */
				     /* field autosense_buffer_ptr.	*/

	ushort	autosense_length;    /* This specifies the maximum size */
				     /* in bytes of the SCSI head's     */
				     /* autosense buffer referenced by  */
				     /* the autosense_buffer_ptr field.	*/

	char   *autosense_buffer_ptr;/* A pointer to the SCSI head's    */
				     /* autosense buffer for this SCSI	*/
				     /* command.			*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns autosense,  */
				     /* then the adapter driver will 	*/
				     /* throw away the autosense data.	*/

	ushort	add_status_length;   /* This specifies the maximum size */
				     /* in bytes of the SCSI head's     */
				     /* additional status buffer        */
				     /* referenced by the               */
				     /* add_status_buffer_ptr field.	*/

	char   *add_status_buffer_ptr;/* A pointer to the SCSI head's   */
				     /* additional status buffer for    */
				     /* this SCSI command.		*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns additional  */
				     /* status then the adapter driver  */
				     /* will throw away the additional  */
				     /* status data.	                */

	uint     dev_burst_len;      /* This is devices maximum burst   */
				     /* size (in bytes)for this command.*/
				     /* For FCP if this is set, then    */
				     /* the SCSI adapter will not use   */
				     /* FCP_XFER_RDYs on writes, but    */
				     /* instead set the write burst size*/
				     /* to this value.  Otherwise       */
				     /* FCP_XFER_RDYs will be used on   */
				     /* FCP writes.                     */
	struct   scsi_buf *next;     /* If the hardware, as well as     */
				     /* both the SCSI head and SCSI     */
				     /* adapter support the chaining    */
				     /* of commands, this field can be  */
				     /* used to chain SCSI commands.    */

	struct   scsi_buf *prev;     /* If the hardware, as well as     */
				     /* both the SCSI head and SCSI     */
				     /* adapter support the chaining    */
				     /* of commands, this field can be  */
				     /* used to chain SCSI commands.    */
        unsigned long long adap_work;/* This field is reserved for the  */
				     /* adapter driver's use.           */
        unsigned long long adap_work2;/* This field is reserved for the */
				     /* adapter driver's use.           */


	unsigned long long scsi_id;  /* This is the 64-bit SCSI ID for  */
				     /* the device.			*/

	unsigned long long lun_id;   /* This is the 64-bit lun ID for   */
				     /* the device.			*/

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * scsi_bufv1 structure used by SCSI device driver to communicate with
 * legacy SCSI adapter drivers.  This is passed to the adapter driver
 * strategy routine entry point.
 */

struct scsi_bufv1 {
	struct buf	bufstruct;	/* buffer structure containing   */
					/* request for device            */
	struct buf	*bp;		/* pointer back to original      */
					/* buffer structure list for     */
					/* command coalescing            */
	ushort          version;	/* The version number of this    */
					/* structure.  This allows the   */
					/* structure to expand in the    */
					/* future.                       */
/*  For this structure the version field must have a value of            */
/*  SCSI_VERSION_1                                                       */
	struct scsi_cmd	scsi_command;	/* the information relating      */
					/* strictly to the scsi command  */
					/* itself 			 */
        ushort io_priority;             /* I/O Priority for task         */
	union {
		ushort retry_delay_code; /* this value is filled in by the */
					/* protocol driver to inform the head */
					/* driver how long to hold off I/O if */
					/* the device can’t process a cm code */
					/* definition -  0x0001-0xffef  time */
					/* delay value */
					/* each tick represents 100 msec */
#define RETRY_TIME_MAX	0xffef
					/* SC_BUSY  0xfff0-0xfffd reserved  */
					/*          0xfffe stop sending cmds */
					/*          0xffff unable to process cmd */
					/* SC_QUEUE_FULL  0xfff0-0xffff reserved */
		ushort reserved;              /* reserved for future use */

	} un;

	uint	timeout_value;		/* timeout value for the command,*/ 
					/* in units of seconds           */
	uchar	status_validity; 	/* least significant bit - scsi_status
					   valid, next least significant bit -
					   adapter status valid */
					/* see sc_buf in scsi.h for defines */

	uchar	scsi_status;            /* returned SCSI status            */
					/* see defines in sc_buf's         */
					/* scsi_status field in scsi.h for */
					/* valid values                    */

	uchar	adapter_status;         /* generic FCP adapter status byte */

	uchar  add_device_status;       /* Additional device status.       */
					/* For FCP devices, this field     */
					/* contains the FCP response code. */
					/* For P1394 devices, this field   */
					/* contains the SBP status         */
			
	ushort add_adap_status;      /* Additional adapter status	   */

	uchar  adap_q_status;        /* adapter's device queue status. This*/
				     /* specifies whether or not the SCSI  */
				     /* adapter driver and SCSI adapter    */
				     /* cleared their queues for this 	   */
				     /* device or not.  A value of 0       */
				     /* indicates that the queue has been  */
				     /* cleared.			   */
				     /* See sc_buf in scsi.h for some      */
				     /* valid defines.			   */
	     
	uchar	     q_tag_msg;	     /* Queue Tag Message Field- Specifies */
				     /* whether or not the SCSI device should*/
				     /* queue this command and if so what   */
				     /* type of queuing it should use.	    */
				     /* See sc_buf in scsi.h for            */
				     /* valid defines.			    */


	uchar        flags;	     /* flags to SCSI adapter driver        */
				     /* See sc_buf in scsi.h for            */
				     /* some valid defines.	            */
	ushort        dev_flags;     /* flags to the SCSI adapter driver    */

	uchar     adap_set_flags;    /* These flags are set by the SCSI */
				     /* adapter driver when a command   */
				     /* is returned.			*/
/* SC_AUTOSENSE_DATA_VALID= 0x1 defined in scsi.h                       */
				     /* This indicates the SCSI adapter */
				     /* driver has placed the autosense */
				     /* data for this command failure   */
				     /* in the buffer referenced by the */
				     /* field autosense_buffer_ptr.	*/
/* SC_RET_ID=               0x2 defined in scsi.h                       */  
				     /* The scsi_id of this device is   */
				     /* different than the scsi_id      */
				     /* provided by the caller. The     */
				     /* scsi_id field has been updated  */
				     /* with current scsi_id for the    */
				     /* device with this world wide name*/

	ushort	autosense_length;    /* This specifies the maximum size */
				     /* in bytes of the SCSI head's     */
				     /* autosense buffer referenced by  */
				     /* the autosense_buffer_ptr field.	*/

	char   *autosense_buffer_ptr;/* A pointer to the SCSI head's    */
				     /* autosense buffer for this SCSI	*/
				     /* command.			*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns autosense,  */
				     /* then the adapter driver will 	*/
				     /* throw away the autosense data.	*/

	ushort	add_status_length;   /* This specifies the maximum size */
				     /* in bytes of the SCSI head's     */
				     /* additional status buffer        */
				     /* referenced by the               */
				     /* add_status_buffer_ptr field.	*/

	char   *add_status_buffer_ptr;/* A pointer to the SCSI head's   */
				     /* additional status buffer for    */
				     /* this SCSI command.		*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns additional  */
				     /* status then the adapter driver  */
				     /* will throw away the additional  */
				     /* status data.	                */

	uint     dev_burst_len;      /* This is devices maximum burst   */
				     /* size (in bytes)for this command.*/
				     /* For FCP if this is set, then    */
				     /* the SCSI adapter will not use   */
				     /* FCP_XFER_RDYs on writes, but    */
				     /* instead set the write burst size*/
				     /* to this value.  Otherwise       */
				     /* FCP_XFER_RDYs will be used on   */
				     /* FCP writes.                     */
	struct   scsi_buf *next;     /* If the hardware, as well as     */
				     /* both the SCSI head and SCSI     */
				     /* adapter support the chaining    */
				     /* of commands, this field can be  */
				     /* used to chain SCSI commands.    */

	struct   scsi_buf *prev;     /* If the hardware, as well as     */
				     /* both the SCSI head and SCSI     */
				     /* adapter support the chaining    */
				     /* of commands, this field can be  */
				     /* used to chain SCSI commands.    */
        unsigned long long adap_work;/* This field is reserved for the  */
				     /* adapter driver's use.           */
        unsigned long long adap_work2;/* This field is reserved for the */
				     /* adapter driver's use.           */


	unsigned long long scsi_id;  /* This is the 64-bit SCSI ID for  */
				     /* the device.			*/

	unsigned long long lun_id;   /* This is the 64-bit lun ID for   */
				     /* the device.			*/
        void *kernext_handle;        /* This is a handle that a kernel  */
				     /* extension can be set to the     */
				     /* kernext_handle returned from    */
				     /* SCIOLSTART if one was returned. */
};

#endif  /* ifdef _KERNEL */


#define ISSUE_PRLOGIN     0x1        /* Issue Port Login                */


/* 
 * IPV6 IP address typedef
 */
typedef struct {
      uchar    addr_type;           /* Type of address                  */
#define ISCSI_IPV4_ADDR 0x1         /* IP V4 address                    */
#define ISCSI_IPV6_ADDR 0x2         /* IP V6 address                    */
      uint64_t addr[2];             /* 128-bit IP address               */

} iscsi_ip_addr;


/*
  This structure is used for the SCSI adapter ioctls 
  of SCIOLSTART, SCIOLSTOP, SCIOLHALT, and SCIOLRESET.
*/

struct scsi_sciolst {
	ushort version;		     /* The version number of this      */
				     /* structure.  This allows the     */
				     /* structure to expand in the      */
				     /* future.                         */
/*  For this structure the version field MUST have a value of           */
/*  SCSI_VERSION_1                                                      */
	uchar	  flags;	     /* User set flags			*/
#define ISSUE_LOGIN   ISSUE_PRLOGIN  /* If this is for an SCIOLSTART,	*/
				     /* then this flag will cause the	*/
				     /* FCS adapter to issue an explicit*/
				     /* login with the device.          */
				     /* It will also return back        */
				     /* information on the target at id.*/
				     /* NOTE: A process login to a 	*/
				     /* target flushes all commands to  */
				     /* all luns on the target		*/
				     /* If the FORCED flag is not set   */
				     /* too, then then a process login  */
				     /* will not be sent if other luns  */
				     /* are started at this target.     */
				     /* However the world wide name and */
				     /* device_flags cab still be       */
				     /* retrieved if a previous process */
				     /* login was done.			*/
                                     /* If this is issued to an iSCSI   */
                                     /* adapter driver, then this       */
                                     /* results in an iSCSI login       */
#define FORCED		   0x2	     /* This flag is required if the	*/
				     /* caller wants to issue a process */
				     /* login even if other luns at this*/
				     /* SCSI ID are started.		*/
#define WRITE_XFER_RDY_OFF 0x4       /* This indicates that XFER_RDYs   */
				     /* should not be used on writes.   */
				     /* For FCP, this will cause the    */
				     /* SCSI adapter driver to do a FCP */
				     /* process login (PRLI) asking that*/
				     /* WRITE_XFER_RDY be disabled.  The*/
				     /* caller can then examine the     */
				     /* device_flags on completion to   */
				     /* see if the target accepted this.*/
				     /* If so and if the caller is SCSI */
				     /* head driver, then all scsi_bufs */
				     /* that are writes must have the   */
				     /* dev_burst_len field set to a    */
				     /* non-zero value.                 */ 
#define FC_CLS3_ERR_REC    0x8       /* This flag is only valid for     */
				     /* FC SCSI devices. When set       */
				     /* the adapter driver will         */
				     /* use FC CLASS 3 ERROR            */
				     /* recovery for all class 3        */
				     /* FCP commands.                   */
#define SCSI_RESV_FLG     0x10       /* Reserved for future use.        */
#define SCIOLRESET_LUN_RESET 0x20    /* This define is only valid for   */
				     /* SCIOLRESET ioctl. If not set    */
				     /* then a target reset is done     */
				     /* If set, then a Lun Reset is     */
				     /* done to the device.             */
#define FC_REC_SPT         0x40      /* This flag is only valid for     */ 
				     /*	FC SCSI devices. When set       */
				     /*	we are enabling just REC ELS    */ 
 				     /* support.                        */
#define FCP_TARGET_VALID   0x80      /* This indicates that             */
				     /*	the fcp_target union is valid   */ 
	uchar     adap_set_flags;    /* Flags set by adapter driver	*/
#define WWN_VALID	   0x1	     /* World wide name field is valid	*/
#define DEVFLG_VALID       0x2	     /* Device flags field is valid     */
#define SCSI_MSK_VALID     0x4	     /* setting_mask field is valid     */
#define SCSI_DFLT_VALID    0x8	     /* Dflt_setting field is valid.    */
#define SCSI_DEV_STARTED   0x10	     /* This device is already started. */
#define SCIOL_RET_ID_ALIAS 0x20      /* The scsi_id may contain a       */
				     /* returned alias that can be used */
				     /* to access this device.          */
				     /* In other cases, this may        */
				     /* indicate that the scsi_id of    */
				     /* this device is different than   */
				     /* the scsi_id provided by the     */
				     /* caller and scsi_id field has    */
				     /* been updated with the current   */
				     /* scsi_id for the device with     */
				     /* this world wide name.           */
#define SCIOL_RET_HANDLE   0x40      /* The kernext_handle field has    */
				     /* been set by the adapter driver. */
#define SCIOL_DYNTRK_ENABLED  0x80   /* Dynamic Tracking of FC devices  */
				     /* was successfully enabled for    */
				     /* this lun.                       */
	uchar     add_dev_flags;     /* Additional flags set by the     */
				     /* caller.                         */
	uchar	  device_flags;      /* flags describing the properties */
				     /* of the device.			*/
				     /* For valid FCP values (defines)  */
				     /* see FCP_XXX flags for SCIOLST   */
				     /* in sys/fcp.h.			*/
				     /* This will only be valid on      */
				     /* return of an SCIOLSTART if 	*/
				     /* ISSUE_PRLOGIN was set.		*/
	uchar     dflt_setting;      /* Default settings for this device*/
				     /* For FCP devices, this is the    */
				     /* default FC class used by the    */
				     /* adapter for this device.        */
	/******  8 byte boundary ********/
	ushort    setting_mask;      /* Mask of settings for this device*/
				     /* For FC devices, this is a mask  */
				     /* of FC Classes supported by      */
  				     /* both this adapter and device.   */

#if defined(__ia64) && !defined(__64BIT__)
	uchar	  pad0[6];	     /* padding for IA32 alignment */
#endif /* __ia64  && !__64BIT__ */
				     /* The target's world wide name.   */
				     /* If not set for SCIOLSTART, it   */
				     /* will be filled in upon return.  */
				     /* If it is set, it will be used to*/
				     /* determine the target to address */
				     /* instead of using the scsi_id    */
				     /* field when the version field is */
				     /* set to SCSI_VERSION_1.          */
	/******  8 byte boundary ********/
	unsigned long long world_wide_name;   

				     /* The target's node name.         */
	/******  8 byte boundary ********/
	unsigned long long node_name;   
				     
	/******  8 byte boundary ********/

	uint	  password;	     /* Security password for target.	*/
				     /* This password will  only be used*/
				     /* on an SCIOLSTART if both the 	*/
				     /* ISSUE_PRLOGIN and PASSWD flags  */
				     /* are set.		        */
#if defined(__ia64) && !defined(__64BIT__)
	uchar 	  pad1[4];	     /* Padding for IA32 alignment */
#endif /* __ia64 && !__64BIT__ */
	/******  8 byte boundary ********/

	unsigned long long scsi_id;  /* This is the 64-bit SCSI ID for  */
				     /* the device. For some devices    */
				     /* adapter driver will return a    */
				     /* SCSI ID alias in this field when*/
				     /* the adap_set_flags field has    */
				     /* SCIOL_RET_ID_ALIAS flag set     */

	unsigned long long lun_id;   /* This is the 64-bit lun ID for   */
				     /* the device.			*/
        union {
	    struct { 

              
              char location[256];    /* if applicable this is location  */
                                     /* of the device. This is required */
				     /* for iSCSI                       */
              char name[256];        /* Name for device. In iSCSI this  */
				     /* is the iSCSI name               */
              uint64_t  port_num;    /* Device port numberif applicable.*/
                                     /* In iSCSI this is the TCP port   */
				     /* number                          */
              char *send_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by caller      */
              char *recv_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by adapter     */
                                     /* driver                          */

            } generic;
            struct {    

              ushort flags;         /* Flags for this union.            */
#define SCIOL_ISCSI_LOCATE_IPADDR 1 /* addr union is used.              */
#define SCIOL_SESS_DISC_TYPE      2 /* Discovery type if set, normal if */
	      			    /* not set 				*/

	      uchar status_class;   /* status class returned from login */
	      uchar status_detail;  /* status detail returned from login*/
	      uchar loc_type;       /* location type                    */ 
#define SCIOL_ISCSI_LOC_HOSTNAME  1 /* Hostname location                */
#define SCIOL_ISCSI_LOC_IPV_ADDR  2 /* IP V4/V6 address location        */
	      union {
		 char hostname[256]; /* iSCSI host name of target       */
		 iscsi_ip_addr addr; /* iSCSI ip address of target      */
                 
              } location;
              char name[256];        /* Name for device. In iSCSI this  */
				     /* is the iSCSI name               */
              uint64_t  port_num;    /* Device port numberif applicable.*/
                                     /* In iSCSI this is the TCP port   */
				     /* number                          */
	      uint  size_send_data;  /* Size in bytes of buffer         */
				     /* referenced by send_data_buffer  */
	      uint  size_recv_data;  /* Size in bytes of buffer         */
				     /* referenced by recv_data_buffer  */
	      uint  size_auth_data;  /* Size in bytes of buffer         */
				     /* referenced by auth_data_buffer  */
              char *send_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by caller      */
              char *recv_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by adapter     */
                                     /* driver                          */
              char *auth_data_buffer;/* Pointer to additional           */
                                     /* authentication data buffer      */
	    } iscsi;
	    struct {      
		ushort flags;        /* Flags set by the caller         */
		ushort adap_flags;   /* Flags returned to the caller    */
#define SCSI_FCP_ADAP_FDISC_FAIL 0x1 /* FDISC failed                    */
#define SCSI_FCP_ADAP_SCR_FAIL   0x2 /* SCR failed                      */
#define SCSI_FCP_ADAP_SNS_FAIL   0x4 /* Name server login failed        */
		uchar initr_type;    /* Type of initiator               */
#define SCSI_INITR_TYPE_NONE     0x0 /* There is no information         */
#define SCSI_INITR_TYPE_VIO      0x1 /* This is a VIO initiator         */
                uchar initr_details; /* Caller provides additional      */
				     /* details on the initiator        */
                uchar failure_type;  /* FC Failure type                 */
#define SCSI_FC_FAIL_LS_RJT   0x1    /* LS_RJT failure                  */
#define SCSI_FC_FAIL_P_RJT    0x2    /* P_RJT failure                   */
#define SCSI_FC_FAIL_F_RJT    0x3    /* F_RJT failure                   */
#define SCSI_FC_FAIL_BA_RJT   0x4    /* BA_RJT failure                  */
#define SCSI_FC_FAIL_F_BSY    0x5    /* F_BSY failure                   */
#define SCSI_FC_FAIL_P_BSY    0x6    /* P_BSY failure                   */
                uchar fail_reason_code;/* Reason code for failure       */
                uchar fail_reason_exp;/* Reason explanation for failure */
		uchar einval_arg;    /* If this request is failed with  */
                                     /* an errno of EINVAL due to an    */
                                     /* invalid setting in some field,  */
                                     /* then this field will provide the*/
                                     /* number of that invalid field.   */
		                     /* See defines under einval_arg    */
				     /* for fcp_target union.           */
                uchar    resvd[6];   /* Reserved for future use         */
                uint64_t resvd2;     /* Reserved for future use         */
		void *caller_handle; /* Handle passed by caller to be   */
				     /* used for this initiator         */
	    } fcp;
	    struct {
		ushort flags;        /* Flags set by the caller         */
#define SCSI_FCP_NO_PRLI        0x01 /* Do not issue PRLI for this      */
				     /* SCIOLSTART                      */
#define SCSI_FCP_INITR_WW_VALID 0x02 /* initr_pn and initr_pn valid     */
				     /* below                           */
#define SCSI_FCP_INITR_HANDLE   0x04 /* Initiator handle valid below    */
#define SCSI_FCP_DATA_ILEAVE    0x08 /* FCP data interleaving is valid  */
                                     /* This indicates teh block_size   */
				     /* and header_size below are valid */
#define SCSI_FCP_GET_SERV_PARMS 0x10 /* Get the FC service parameters   */
				     /* from PLOGI.                     */
#define SCSI_TARGET_ONLY        0x20 /* This flag is only valid for     */ 
				     /*	SCIOLSTART and SCIOLSTOPs. It   */
				     /* indicates that only a target    */
				     /*	(not a lun) is affected.        */
                ushort adap_flags;   /* Returned adapter flags          */
#define SCSI_FCP_ADAP_SERV_PARM 0x01 /* FC Service parameters returned  */
                uchar failure_type;  /* FC Failure type                 */
				     /* See defines for failure_type    */
				     /* under the fcp union             */
                uchar fail_reason_code;/* Reason code for failure       */
                uchar fail_reason_exp;/* Reason explanation for failure */
		uchar einval_arg;    /* If this request is failed with  */
                                     /* an errno of EINVAL due to an    */
                                     /* invalid setting in some field,  */
                                     /* then this field will provide the*/
                                     /* number of that invalid field.   */
#define SCSI_SCLST_INV_VERS    0x01  /* The version of the struct is    */
				     /* invalid                         */
#define SCSI_SCLST_INV_HNDL_0  0x02  /* The supplied handle is NULL     */
#define SCSI_SCLST_INV_HNDL    0x03  /* The supplied handle is invalid  */
#define SCSI_SCLST_INV_K_HNDL  0x04  /* The supplied handle is invalid  */
#define SCSI_SCLST_INV_K_HNDL2 0x05  /* The supplied handle is invalid  */
#define SCSI_SCLST_INV_WWN     0x06  /* The world wide name is invald   */
#define SCSI_SCLST_INV_ID      0x07  /* The SCSI ID is invalid          */
#define SCSI_SCLST_INV_ILEAVE  0x08  /* Invalid interleaving setting    */
#define SCSI_SCLST_INV_MIXED_V 0x09  /* Invalid version mixing          */
#define SCSI_SCLST_INV_TARGON  0x0a  /* Incompatible setting of         */
				     /* SCSI_TARGET_ONLY                */
#define SCSI_SCLST_INV_STARTED 0x0b  /* Already started                 */
#define SCSI_SCLST_INV_TARG_0  0x0c  /* The target is  NULL             */
#define SCSI_SCLST_INV_KERN    0x0d  /* The caller is not from kernel   */
				     /* space, but the one who started  */
				     /* was from kernel space.          */
                uchar   resvd[8];    /* Reserved for future use.        */
		uint32_t block_size; /* Data block size for FCP data    */
				     /* interleaving                    */
		uint32_t header_size;/* Header size for FCP data        */
				     /* interleaving                    */
                uint64_t initr_pn;   /* Initiator Port Name             */
                uint64_t initr_nn;   /* Initiator Node Name             */
                union {
		    uint64_t app_handle;
                    void *initr_handle;/* Initiator Handle              */
	        }initiator;
                char service_parms[256];/* Returned service parameters  */
	    } fcp_target;
	}  parms;

	union {

	    uint64_t app_handle;
	    void *kernext_handle;    /* If the caller is kernel         */
                                     /* extension then they may be able */
				     /* to use a handle. For SCIOLSTART,*/
				     /* the kernext_handle may be       */
				     /* returned. If SCIOLSTART returns */
				     /* a kernext_handle (adap_set_flag */
				     /* has SCIOL_RET_HANDLE set), then */
				     /* the kernext_handle field of     */
				     /* scsi_buf must be set to this    */
				     /* value.                          */
	} handle;
  
};


#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * This structure is used for the SCSI adapter ioctls 
 * of SCIOLSTART, SCIOLSTOP, SCIOLHALT, and SCIOLRESET.
 * This structure is used internally by the adapter driver for support
 * 64-bit applications.
 */

struct scsi_sciolst64 {
	ushort version;		     /* The version number of this      */
				     /* structure.  This allows the     */
				     /* structure to expand in the      */
				     /* future.                         */
/*  For this structure the version field MUST have a value of           */
/*  SCSI_VERSION_1                                                      */
	uchar	  flags;	     /* User set flags			*/
				     /* See defines under flags field   */
				     /* in struct scsi_sciolst          */
	uchar     adap_set_flags;    /* Flags set by adapter driver	*/
				     /* See defines under adap_set_flags*/
				     /* field in struct scsi_sciolst    */
	uchar     add_dev_flags;     /* Additional flags set by the     */
				     /* caller.                         */
	uchar	  device_flags;      /* flags describing the properties */
				     /* of the device.			*/
				     /* For valid FCP values (defines)  */
				     /* see FCP_XXX flags for SCIOLST   */
				     /* in sys/fcp.h.			*/
				     /* This will only be valid on      */
				     /* return of an SCIOLSTART if 	*/
				     /* ISSUE_PRLOGIN was set.		*/
	uchar     dflt_setting;      /* Default settings for this device*/
				     /* For FCP devices, this is the    */
				     /* default FC class used by the    */
				     /* adapter for this device.        */
	/******  8 byte boundary ********/
	ushort    setting_mask;      /* Mask of settings for this device*/
				     /* For FC devices, this is a mask  */
				     /* of FC Classes supported by      */
  				     /* both this adapter and device.   */

				     /* The target's world wide name    */
#if defined(__ia64) && !defined(__64BIT__)
	uchar	  pad0[6];	     /* padding for IA32 alignment */
#endif /* __ia64  && !__64BIT__ */
	/******  8 byte boundary ********/
	unsigned long long world_wide_name;   

				     /* The target's node name          */
	/******  8 byte boundary ********/
	unsigned long long node_name;   

				     
	/******  8 byte boundary ********/

	uint	  password;	     /* Security password for target.	*/
				     /* This password will  only be used*/
				     /* on an SCIOLSTART if both the 	*/
				     /* ISSUE_PRLOGIN and PASSWD flags  */
				     /* are set.		        */
#if defined(__ia64) && !defined(__64BIT__)
	uchar 	  pad1[4];	     /* Padding for IA32 alignment */
#endif /* __ia64 && !__64BIT__ */
	/******  8 byte boundary ********/

	unsigned long long scsi_id;  /* This is the 64-bit SCSI ID for  */
				     /* the device. For some devices    */
				     /* adapter driver will return a    */
				     /* SCSI ID alias in this field when*/
				     /* the adap_set_flags field has    */
				     /* SCIOL_RET_ID_ALIAS flag set     */

	unsigned long long lun_id;   /* This is the 64-bit lun ID for   */
				     /* the device.			*/
        union {
	    struct { 

              
              char location[256];    /* if applicable this is location  */
                                     /* of the device. This is required */
				     /* for iSCSI                       */
              char name[256];        /* Name for device. In iSCSI this  */
				     /* is the iSCSI name               */
              uint64_t  port_num;    /* Device port numberif applicable.*/
                                     /* In iSCSI this is the TCP port   */
				     /* number                          */
              ptr64 send_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by caller      */
              ptr64 recv_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by adapter     */
                                     /* driver                          */

            } generic;
            struct {    

              ushort flags;         /* Flags for this union.            */
				    /* See defines under flags field    */
				    /* in struct scsi_sciolst           */

	      uchar status_class;   /* status class returned from login */
	      uchar status_detail;  /* status detail returned from login*/
	      uchar loc_type;       /* location type                    */
				    /* See defines under loc_type field */
				    /* in struct scsi_sciolst           */
	      union {
		 char hostname[256]; /* iSCSI host name of target       */
		 iscsi_ip_addr addr; /* iSCSI ip address of target      */
                 
              } location;
              char name[256];        /* Name for device. In iSCSI this  */
				     /* is the iSCSI name               */
              uint64_t  port_num;    /* Device port numberif applicable.*/
                                     /* In iSCSI this is the TCP port   */
				     /* number                          */
	      uint  size_send_data;  /* Size in bytes of buffer         */
				     /* referenced by send_data_buffer  */
	      uint  size_recv_data;  /* Size in bytes of buffer         */
				     /* referenced by recv_data_buffer  */
	      uint  size_auth_data;  /* Size in bytes of buffer         */
				     /* referenced by auth_data_buffer  */
              ptr64 send_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by caller      */
              ptr64 recv_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by adapter     */
                                     /* driver                          */
              ptr64 auth_data_buffer;/* Pointer to additional           */
                                     /* authentication data buffer      */
	    } iscsi;
	    struct {      
		ushort flags;        /* Flags set by the caller         */
		ushort adap_flags;   /* Flags returned to the caller    */
		uchar initr_type;    /* Type of initiator               */
                uchar initr_details; /* Caller provides additional      */
				     /* details on the initiator        */
                uchar failure_type;  /* FC Failure type                 */
                uchar fail_reason_code;/* Reason code for failure       */
                uchar fail_reason_exp;/* Reason explanation for failure */
		uchar einval_arg;    /* If this request is failed with  */
                                     /* an errno of EINVAL due to an    */
                                     /* invalid setting in some field,  */
                                     /* then this field will provide the*/
                                     /* number of that invalid field.   */
                uchar    resvd[6];   /* Reserved for future use         */
                uint64_t resvd2;     /* Reserved for future use         */
		ptr64 caller_handle; /* Handle passed by caller to be   */
				     /* used for this initiator         */
	    } fcp;
	    struct {
		ushort flags;        /* Flags set by the caller         */

                ushort adap_flags;   /* Returned adapter flags          */
                uchar failure_type;  /* FC Failure type                 */

                uchar fail_reason_code;/* Reason code for failure       */
                uchar fail_reason_exp;/* Reason explanation for failure */
		uchar einval_arg;    /* If this request is failed with  */
                                     /* an errno of EINVAL due to an    */
                                     /* invalid setting in some field,  */
                                     /* then this field will provide the*/
                                     /* number of that invalid field.   */
                uchar   resvd[8];    /* Reserved for future use.        */
		uint32_t block_size; /* Data block size for FCP data    */
				     /* interleaving                    */
		uint32_t header_size;/* Header size for FCP data        */
				     /* interleaving                    */
                uint64_t initr_pn;   /* Initiator Port Name             */
                uint64_t initr_nn;   /* Initiator Node Name             */
                union {
		    uint64_t app_handle;
                    ptr64 initr_handle;/* Initiator Handle              */
	        }initiator;
                char service_parms[256];/* Returned service parameters  */
	    } fcp_target;
	}  parms;

    union {

        uint64_t app_handle;
        ptr64 kernext_handle;        /* If the caller is kernel         */
                                     /* extension then they may be able */
				     /* to use a handle                 */
				     /* For SCIOLSTART, the             */
				     /* kernext_handle may be  returned */
				     /* If the SCIOLSTART returned a    */
				     /* kernext_handle, then it can be  */
				     /* set by the caller for all       */
				     /* other operations that use       */
				     /* scsi_sciolst as well as for     */
				     /* scsi_bufs                       */


    } handle;
  


};


/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * This structure is used for the SCSI adapter ioctls 
 * of SCIOLSTART, SCIOLSTOP, SCIOLHALT, and SCIOLRESET.
 * This structure is used internally by the adapter driver for support
 * 32-bit applications.
 */

struct scsi_sciolst32 {
	ushort version;		     /* The version number of this      */
				     /* structure.  This allows the     */
				     /* structure to expand in the      */
				     /* future.                         */
/*  For this structure the version field MUST have a value of           */
/*  SCSI_VERSION_1                                                      */
	uchar	  flags;	     /* User set flags			*/
				     /* See defines under flags field   */
				     /* in struct scsi_sciolst          */
	uchar     adap_set_flags;    /* Flags set by adapter driver	*/
				     /* See defines under adap_set_flags*/
				     /* field in struct scsi_sciolst    */
	uchar     add_dev_flags;     /* Additional flags set by the     */
				     /* caller.                         */
	uchar	  device_flags;      /* flags describing the properties */
				     /* of the device.			*/
				     /* For valid FCP values (defines)  */
				     /* see FCP_XXX flags for SCIOLST   */
				     /* in sys/fcp.h.			*/
				     /* This will only be valid on      */
				     /* return of an SCIOLSTART if 	*/
				     /* ISSUE_PRLOGIN was set.		*/
	uchar     dflt_setting;      /* Default settings for this device*/
				     /* For FCP devices, this is the    */
				     /* default FC class used by the    */
				     /* adapter for this device.        */
	/******  8 byte boundary ********/
	ushort    setting_mask;      /* Mask of settings for this device*/
				     /* For FC devices, this is a mask  */
				     /* of FC Classes supported by      */
  				     /* both this adapter and device.   */

				     /* The target's world wide name    */
#if defined(__ia64) && !defined(__64BIT__)
	uchar	  pad0[6];	     /* padding for IA32 alignment */
#endif /* __ia64  && !__64BIT__ */
	/******  8 byte boundary ********/
	unsigned long long world_wide_name;   

				     /* The target's node name          */
	/******  8 byte boundary ********/
	unsigned long long node_name;   

				     
	/******  8 byte boundary ********/

	uint	  password;	     /* Security password for target.	*/
				     /* This password will  only be used*/
				     /* on an SCIOLSTART if both the 	*/
				     /* ISSUE_PRLOGIN and PASSWD flags  */
				     /* are set.		        */
#if defined(__ia64) && !defined(__64BIT__)
	uchar 	  pad1[4];	     /* Padding for IA32 alignment */
#endif /* __ia64 && !__64BIT__ */
	/******  8 byte boundary ********/

	unsigned long long scsi_id;  /* This is the 64-bit SCSI ID for  */
				     /* the device. For some devices    */
				     /* adapter driver will return a    */
				     /* SCSI ID alias in this field when*/
				     /* the adap_set_flags field has    */
				     /* SCIOL_RET_ID_ALIAS flag set     */

	unsigned long long lun_id;   /* This is the 64-bit lun ID for   */
				     /* the device.			*/
        union {
	    struct { 

              
              char location[256];    /* if applicable this is location  */
                                     /* of the device. This is required */
				     /* for iSCSI                       */
              char name[256];        /* Name for device. In iSCSI this  */
				     /* is the iSCSI name               */
              uint64_t  port_num;    /* Device port numberif applicable.*/
                                     /* In iSCSI this is the TCP port   */
				     /* number                          */
              ptr32 send_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by caller      */
              ptr32 recv_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by adapter     */
                                     /* driver                          */

            } generic;
            struct {    

              ushort flags;         /* Flags for this union.            */
				    /* See defines under flags field    */
				    /* in struct scsi_sciolst           */

	      uchar status_class;   /* status class returned from login */
	      uchar status_detail;  /* status detail returned from login*/
	      uchar loc_type;       /* location type                    */
				    /* See defines under loc_type field */
				    /* in struct scsi_sciolst           */
	      union {
		 char hostname[256]; /* iSCSI host name of target       */
		 iscsi_ip_addr addr; /* iSCSI ip address of target      */
                 
              } location;
              char name[256];        /* Name for device. In iSCSI this  */
				     /* is the iSCSI name               */
              uint64_t  port_num;    /* Device port numberif applicable.*/
                                     /* In iSCSI this is the TCP port   */
				     /* number                          */
	      uint  size_send_data;  /* Size in bytes of buffer         */
				     /* referenced by send_data_buffer  */
	      uint  size_recv_data;  /* Size in bytes of buffer         */
				     /* referenced by recv_data_buffer  */
	      uint  size_auth_data;  /* Size in bytes of buffer         */
				     /* referenced by auth_data_buffer  */
              ptr32 send_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by caller      */
              ptr32 recv_data_buffer;/* Pointer to additional data      */
                                     /* buffer filled in by adapter     */
                                     /* driver                          */
              ptr32 auth_data_buffer;/* Pointer to additional           */
                                     /* authentication data buffer      */
	    } iscsi;
	    struct {      
		ushort flags;        /* Flags set by the caller         */
		ushort adap_flags;   /* Flags returned to the caller    */
		uchar initr_type;    /* Type of initiator               */
                uchar initr_details; /* Caller provides additional      */
				     /* details on the initiator        */
                uchar failure_type;  /* FC Failure type                 */
                uchar fail_reason_code;/* Reason code for failure       */
                uchar fail_reason_exp;/* Reason explanation for failure */
		uchar einval_arg;    /* If this request is failed with  */
                                     /* an errno of EINVAL due to an    */
                                     /* invalid setting in some field,  */
                                     /* then this field will provide the*/
                                     /* number of that invalid field.   */
		                     /* See defines under einval_arg    */
                uchar    resvd[6];   /* Reserved for future use         */
                uint64_t resvd2;     /* Reserved for future use         */
		ptr32 caller_handle; /* Handle passed by caller to be   */
				     /* used for this initiator         */
	    } fcp;
	    struct {
		ushort flags;        /* Flags set by the caller         */

                ushort adap_flags;   /* Returned adapter flags          */
                uchar failure_type;  /* FC Failure type                 */

                uchar fail_reason_code;/* Reason code for failure       */
                uchar fail_reason_exp;/* Reason explanation for failure */
		uchar einval_arg;    /* If this request is failed with  */
                                     /* an errno of EINVAL due to an    */
                                     /* invalid setting in some field,  */
                                     /* then this field will provide the*/
                                     /* number of that invalid field.   */
                uchar   resvd[8];    /* Reserved for future use.        */
		uint32_t block_size; /* Data block size for FCP data    */
				     /* interleaving                    */
		uint32_t header_size;/* Header size for FCP data        */
				     /* interleaving                    */
                uint64_t initr_pn;   /* Initiator Port Name             */
                uint64_t initr_nn;   /* Initiator Node Name             */
		union {
		    uint64_t app_handle;
                    ptr32 initr_handle;/* Initiator Handle              */
	        }initiator;
                char service_parms[256];/* Returned service parameters  */
	    } fcp_target;
	}  parms;

    union {

        uint64_t app_handle;
        ptr32 kernext_handle;        /* If the caller is kernel         */
                                     /* extension then they may be able */
				     /* to use a handle                 */
				     /* For SCIOLSTART, the             */
				     /* kernext_handle may be  returned */
				     /* If the SCIOLSTART returned a    */
				     /* kernext_handle, then it can be  */
				     /* set by the caller for all       */
				     /* other operations that use       */
				     /* scsi_sciolst as well as for     */
				     /* scsi_bufs                       */


    } handle;
  


};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * This version 0 (legacy) structure structure is used for the SCSI  
 * adapter ioctls of SCIOLSTART, SCIOLSTOP, SCIOLHALT, and SCIOLRESET.
 */
struct scsi_sciolstv0 {
	ushort version;		     /* The version number of this      */
				     /* structure.  This allows the     */
				     /* structure to expand in the      */
				     /* future.                         */

/*  For this structure the version field must have a value of           */
/*  SCSI_VERSION_0                                                      */
	uchar	  flags;	     /* User set flags			*/
				     /* See defines under flags field   */
				     /* in struct scsi_sciolst          */
	uchar     adap_set_flags;    /* Flags set by adapter driver	*/
				     /* See defines under adap_set_flags*/
				     /* field in struct scsi_sciolst    */
	uchar     add_dev_flags;     /* Additional flags set by the     */
				     /* caller.                         */
	uchar	  device_flags;      /* flags describing the properties */
				     /* of the device.			*/
				     /* For valid FCP values (defines)  */
				     /* see FCP_XXX flags for SCIOLST   */
				     /* in sys/fcp.h.			*/
				     /* This will only be valid on      */
				     /* return of an SCIOLSTART if 	*/
				     /* ISSUE_PRLOGIN was set.		*/
	uchar     dflt_setting;      /* Default settings for this device*/
				     /* For FCP devices, this is the    */
				     /* default FC class used by the    */
				     /* adapter for this device.        */
	/******  8 byte boundary ********/
	ushort    setting_mask;      /* Mask of settings for this device*/
				     /* For FC devices, this is a mask  */
				     /* of FC Classes supported by      */
  				     /* both this adapter and device.   */

				     /* The target's world wide name    */
#if defined(__ia64) && !defined(__64BIT__)
	uchar	  pad0[6];	     /* padding for IA32 alignment */
#endif /* __ia64  && !__64BIT__ */
	/******  8 byte boundary ********/
	unsigned long long world_wide_name;   

				     /* The target's node name          */
	/******  8 byte boundary ********/
	unsigned long long node_name;   

				     
	/******  8 byte boundary ********/

	uint	  password;	     /* Security password for target.	*/
				     /* This password will  only be used*/
				     /* on an SCIOLSTART if both the 	*/
				     /* ISSUE_PRLOGIN and PASSWD flags  */
				     /* are set.		        */
#if defined(__ia64) && !defined(__64BIT__)
	uchar 	  pad1[4];	     /* Padding for IA32 alignment */
#endif /* __ia64 && !__64BIT__ */
	/******  8 byte boundary ********/

	unsigned long long scsi_id;  /* This is the 64-bit SCSI ID for  */
				     /* the device.			*/

	unsigned long long lun_id;   /* This is the 64-bit lun ID for   */
				     /* the device.			*/


};
#endif /* _KERNEL */

/*
 * Scsi Inquiry structure passed by pointer to ioctl of adapter driver
 */

struct scsi_inquiry {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_2                                                       */
	uchar get_extended;     /* = TRUE if getting extended inq        */
	uchar inquiry_len;	/* number of bytes to transfer (0 - 255) */
	uchar *inquiry_ptr;	/* pointer to inquiry data buffer        */
	/******  8 byte boundary ********/
	uchar code_page_num;    /* code page # when get_extended=TRUE    */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
         
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	/******  8 byte boundary ********/
	char *autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */
#if defined(__ia64) && !defined(__64BIT__)
	uchar pad[4];		/* Padding for IA64 ILP32 mode */
#endif
	/******  8 byte boundary ********/

	unsigned long long scsi_id;/* This is the 64-bit SCSI ID for     */
				 /* the device.			         */

	unsigned long long lun_id;/* This is the 64-bit lun ID for       */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
        unsigned long long residual;  /* bytes not xferred after error.  */
     	     
};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Inquiry version 0 structure passed by pointer to ioctl of adapter
 * driver.
 * This structure is used internally by the adapter driver for support
 * 64-bit applications.
 */

struct scsi_inquiry64v0 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */
	uchar get_extended;     /* = TRUE if getting extended inq        */
	uchar inquiry_len;	/* number of bytes to transfer (0 - 255) */
	ptr64 inquiry_ptr;	/* inquiry data buffer pointer           */
	uchar code_page_num;    /* code page # when get_extended=TRUE    */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
         
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	ptr64 autosense_buffer_ptr;/* Upper word of autosense pointer    */

				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

	unsigned long long scsi_id;/* This is the 64-bit SCSI ID for     */
				 /* the device.			         */

	unsigned long long lun_id;/* This is the 64-bit lun ID for       */
				 /* the device.			         */
     	     
};


/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Inquiry version 0 structure passed by pointer to ioctl of adapter
 * driver.
 * This structure is used internally by the adapter driver for support
 * 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_inquiry32v0 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */
	uchar get_extended;     /* = TRUE if getting extended inq        */
	uchar inquiry_len;	/* number of bytes to transfer (0 - 255) */
	ptr32 inquiry_ptr;	/* pointer to inquiry data buffer        */
	uchar code_page_num;    /* code page # when get_extended=TRUE    */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
         
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	ptr32  autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

	unsigned long long scsi_id;/* This is the 64-bit SCSI ID for     */
				 /* the device.			         */

	unsigned long long lun_id;/* This is the 64-bit lun ID for       */
				 /* the device.			         */
     	     
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Inquiry structure passed by pointer to ioctl of adapter driver.
 * This structure is used internally by the adapter driver for support
 * 64-bit applications.
 */

struct scsi_inquiry64v1 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */
	uchar get_extended;     /* = TRUE if getting extended inq        */
	uchar inquiry_len;	/* number of bytes to transfer (0 - 255) */
	ptr64 inquiry_ptr;	/* inquiry data buffer pointer           */
	uchar code_page_num;    /* code page # when get_extended=TRUE    */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
         
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	ptr64 autosense_buffer_ptr;/* Upper word of autosense pointer    */

				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

	unsigned long long scsi_id;/* This is the 64-bit SCSI ID for     */
				 /* the device.			         */

	unsigned long long lun_id;/* This is the 64-bit lun ID for       */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
     	     
};


/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Inquiry structure passed by pointer to ioctl of adapter driver.
 * This structure is used internally by the adapter driver for support
 * 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_inquiry32v1 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */
	uchar get_extended;     /* = TRUE if getting extended inq        */
	uchar inquiry_len;	/* number of bytes to transfer (0 - 255) */
	ptr32 inquiry_ptr;	/* pointer to inquiry data buffer        */
	uchar code_page_num;    /* code page # when get_extended=TRUE    */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
         
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	ptr32  autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

	unsigned long long scsi_id;/* This is the 64-bit SCSI ID for     */
				 /* the device.			         */

	unsigned long long lun_id;/* This is the 64-bit lun ID for       */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
     	     
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Inquiry structure passed by pointer to ioctl of adapter driver.
 * This structure is used internally by the adapter driver for support
 * 64-bit applications.
 */

struct scsi_inquiry64 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_2                                                       */
	uchar get_extended;     /* = TRUE if getting extended inq        */
	uchar inquiry_len;	/* number of bytes to transfer (0 - 255) */
	ptr64 inquiry_ptr;	/* inquiry data buffer pointer           */
	uchar code_page_num;    /* code page # when get_extended=TRUE    */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
         
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	ptr64 autosense_buffer_ptr;/* Upper word of autosense pointer    */

				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

	unsigned long long scsi_id;/* This is the 64-bit SCSI ID for     */
				 /* the device.			         */

	unsigned long long lun_id;/* This is the 64-bit lun ID for       */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
        unsigned long long residual;  /* bytes not xferred after error.  */     
};


/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Inquiry structure passed by pointer to ioctl of adapter driver.
 * This structure is used internally by the adapter driver for support
 * 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_inquiry32 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_2                                                       */
	uchar get_extended;     /* = TRUE if getting extended inq        */
	uchar inquiry_len;	/* number of bytes to transfer (0 - 255) */
	ptr32 inquiry_ptr;	/* pointer to inquiry data buffer        */
	uchar code_page_num;    /* code page # when get_extended=TRUE    */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
         
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	ptr32  autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

	unsigned long long scsi_id;/* This is the 64-bit SCSI ID for     */
				 /* the device.			         */

	unsigned long long lun_id;/* This is the 64-bit lun ID for       */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
        unsigned long long residual;  /* bytes not xferred after error.  */
     	     
};

#endif

/*
  SCSI Read structure passed by pointer to ioctl of adapter driver
  (This uses the 10-byte SCSI Read command.)
*/

struct scsi_readblk {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_2                                                       */
	short blklen;		/* number of bytes in device block       */
#if defined(__ia64) && !defined(__64BIT__)
	uchar pad1[4];		/* Padding for IA64 ILP32 mode */
#endif
	/******  8 byte boundary ********/
	unsigned long long blkno;/* block number on device to read       */
	/******  8 byte boundary ********/
	uint  timeout_value;	/* timeout value for command, in secs.   */
	uchar *data_ptr;	/* pointer to buffer for read data       */
	/******  8 byte boundary ********/
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */

	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	/******  8 byte boundary ********/

	char *autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

#if defined(__ia64) && !defined(__64BIT__)
	uchar pad2[4];		/* Padding for IA64 ILP32 mode */
#endif
	/******  8 byte boundary ********/

	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
        unsigned long long residual;  /* bytes not xferred after error.  */

};


#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read version 0 structure passed by pointer to ioctl of adapter driver
 *(This uses the 10-byte SCSI Read command.)
 * This structure is used internally by the adapter driver for support
 * 64-bit applications.
 */

struct scsi_readblk64v0 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */
	short blklen;		/* number of bytes in device block       */
	unsigned long long blkno;/* block number on device to read       */
	uint  timeout_value;	/* timeout value for command, in secs.   */
        ptr64 data_ptr;         /* Low word of pointer to buffer for     */
	                        /* read data                             */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */

	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 
	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */


	ptr64 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */


	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read version 0 structure passed by pointer to ioctl of adapter driver
 *(This uses the 10-byte SCSI Read command.)
 * This structure is used internally by the adapter driver for support
 * 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_readblk32v0 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */
	short blklen;		/* number of bytes in device block       */
	unsigned long long blkno;/* block number on device to read       */
	uint  timeout_value;	/* timeout value for command, in secs.   */
        ptr32 data_ptr;         /* Low word of pointer to buffer for     */
	                        /* read data                             */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */

	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 
	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */


	ptr32 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */


	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read structure passed by pointer to ioctl of adapter driver
 *(This uses the 10-byte SCSI Read command.)
 * This structure is used internally by the adapter driver for support
 * 64-bit applications.
 */

struct scsi_readblk64v1 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */
	short blklen;		/* number of bytes in device block       */
	unsigned long long blkno;/* block number on device to read       */
	uint  timeout_value;	/* timeout value for command, in secs.   */
        ptr64 data_ptr;         /* Low word of pointer to buffer for     */
	                        /* read data                             */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */

	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 
	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */


	ptr64 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */


	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read structure passed by pointer to ioctl of adapter driver
 *(This uses the 10-byte SCSI Read command.)
 * This structure is used internally by the adapter driver for support
 * 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_readblk32v1 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */
	short blklen;		/* number of bytes in device block       */
	unsigned long long blkno;/* block number on device to read       */
	uint  timeout_value;	/* timeout value for command, in secs.   */
        ptr32 data_ptr;         /* Low word of pointer to buffer for     */
	                        /* read data                             */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */

	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 
	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */


	ptr32 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */


	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read structure passed by pointer to ioctl of adapter driver
 *(This uses the 10-byte SCSI Read command.)
 * This structure is used internally by the adapter driver for support
 * 64-bit applications.
 */

struct scsi_readblk64 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_2                                                       */
	short blklen;		/* number of bytes in device block       */
	unsigned long long blkno;/* block number on device to read       */
	uint  timeout_value;	/* timeout value for command, in secs.   */
        ptr64 data_ptr;         /* Low word of pointer to buffer for     */
	                        /* read data                             */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */

	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 
	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */


	ptr64 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */


	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
        unsigned long long residual;  /* bytes not xferred after error.  */     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read structure passed by pointer to ioctl of adapter driver
 *(This uses the 10-byte SCSI Read command.)
 * This structure is used internally by the adapter driver for support
 * 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_readblk32 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_2                                                       */
	short blklen;		/* number of bytes in device block       */
	unsigned long long blkno;/* block number on device to read       */
	uint  timeout_value;	/* timeout value for command, in secs.   */
        ptr32 data_ptr;         /* Low word of pointer to buffer for     */
	                        /* read data                             */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */

	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 
	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */


	ptr32 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */


	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
        unsigned long long residual;  /* bytes not xferred after error.  */     	     

};
#endif

/*
 * SCSI Start Unit structure passed by pointer to ioctl of adapter driver
 */

struct scsi_startunit  {
	ushort version;		/* The version number of this            */
				/* structure.  This allows the           */
				/* structure to expand in the            */
				/* future.                               */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */

	uchar start_flag;	/* must be set to TRUE for starting,     */
				/* FALSE to stop device                  */
	uchar immed_flag;	/* if set to TRUE, command completes     */
				/* immediately (if supported by device)  */
				/* if FALSE, command does not return until*/
				/* device has completed the command.     */
	uint   timeout_value;	/* timeout value for command, in secs.   */
	/******  8 byte boundary ********/
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	/******  8 byte boundary ********/
	char *autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

#if defined(__ia64) && !defined(__64BIT__)
	uchar pad[4];		/* Padding for IA64 ILP32 mode */
#endif

	/******  8 byte boundary ********/
	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	/******  8 byte boundary ********/
	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
     	     

};


#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * 
 * SCSI Start Unit version 0 structure passed by pointer to ioctl of adapter driver.
 * This structure is used internally by the adapter driver for support
 * 64-bit applications.
 */

struct scsi_startunit64v0  {
	ushort version;		/* The version number of this            */
				/* structure.  This allows the           */
				/* structure to expand in the            */
				/* future.                               */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */

	uchar start_flag;	/* must be set to TRUE for starting,     */
				/* FALSE to stop device                  */
	uchar immed_flag;	/* if set to TRUE, command completes     */
				/* immediately (if supported by device)  */
				/* if FALSE, command does not return until*/
				/* device has completed the command.     */
	uint   timeout_value;	/* timeout value for command, in secs.   */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */

	ptr64 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * 
 * SCSI Start Unit version 0 structure passed by pointer to ioctl of adapter driver.
 * This structure is used internally by the adapter driver for support
 * 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_startunit32v0  {
	ushort version;		/* The version number of this            */
				/* structure.  This allows the           */
				/* structure to expand in the            */
				/* future.                               */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */

	uchar start_flag;	/* must be set to TRUE for starting,     */
				/* FALSE to stop device                  */
	uchar immed_flag;	/* if set to TRUE, command completes     */
				/* immediately (if supported by device)  */
				/* if FALSE, command does not return until*/
				/* device has completed the command.     */
	uint   timeout_value;	/* timeout value for command, in secs.   */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */

	ptr32 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * 
 * SCSI Start Unit structure passed by pointer to ioctl of adapter driver.
 * This structure is used internally by the adapter driver for support
 * 64-bit applications.
 */

struct scsi_startunit64  {
	ushort version;		/* The version number of this            */
				/* structure.  This allows the           */
				/* structure to expand in the            */
				/* future.                               */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */

	uchar start_flag;	/* must be set to TRUE for starting,     */
				/* FALSE to stop device                  */
	uchar immed_flag;	/* if set to TRUE, command completes     */
				/* immediately (if supported by device)  */
				/* if FALSE, command does not return until*/
				/* device has completed the command.     */
	uint   timeout_value;	/* timeout value for command, in secs.   */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */

	ptr64 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * 
 * SCSI Start Unit structure passed by pointer to ioctl of adapter driver.
 * This structure is used internally by the adapter driver for support
 * 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_startunit32  {
	ushort version;		/* The version number of this            */
				/* structure.  This allows the           */
				/* structure to expand in the            */
				/* future.                               */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */

	uchar start_flag;	/* must be set to TRUE for starting,     */
				/* FALSE to stop device                  */
	uchar immed_flag;	/* if set to TRUE, command completes     */
				/* immediately (if supported by device)  */
				/* if FALSE, command does not return until*/
				/* device has completed the command.     */
	uint   timeout_value;	/* timeout value for command, in secs.   */
	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */

	ptr32 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
     	     

};

#endif

/*
 * SCSI Test Unit Ready structure passed by pointer to ioctl of adapter driver
 */

struct scsi_ready  {
	ushort version;		/* The version number of this            */
				/* structure.  This allows the           */
				/* structure to expand in the            */
				/* future.                               */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */

	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	char *autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
     	     

};


#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Test Unit Ready version 0 structure passed by pointer to ioctl of adapter driver.
 * This structure is used internally by the adapter driver for support
 * 64-bit applications.
 */

struct scsi_ready64v0  {
	ushort version;		/* The version number of this            */
				/* structure.  This allows the           */
				/* structure to expand in the            */
				/* future.                               */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */

	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */

        ptr64 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */


	
	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Test Unit Ready version 0 structure passed by pointer to ioctl of
 * adapter driver.
 * This structure is used internally by the adapter driver for support
 * 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_ready32v0  {
	ushort version;		/* The version number of this            */
				/* structure.  This allows the           */
				/* structure to expand in the            */
				/* future.                               */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */

	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */

        ptr32 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */


	
	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Test Unit Ready structure passed by pointer to ioctl of adapter driver.
 * This structure is used internally by the adapter driver for support
 * 64-bit applications.
 */

struct scsi_ready64  {
	ushort version;		/* The version number of this            */
				/* structure.  This allows the           */
				/* structure to expand in the            */
				/* future.                               */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */

	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */

        ptr64 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */


	
	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Test Unit Ready structure passed by pointer to ioctl of adapter driver.
 * This structure is used internally by the adapter driver for support
 * 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_ready32  {
	ushort version;		/* The version number of this            */
				/* structure.  This allows the           */
				/* structure to expand in the            */
				/* future.                               */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */

	uchar status_validity;	/* 0 = no valid status                   */
				/* 1 = valid SCSI bus status only        */
	uchar scsi_status;	/* SCSI bus status (if valid)            */
	uchar adapter_status;   /* Adapter status (if valid) see defines */
				/* in scsi_buf				 */
	uchar flags;		/* flags: See scsi.h                     */
	uchar adap_set_flags;   /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See scsi_buf                */
				/* for valid values		         */ 

	ushort autosense_length;/* This specifies the maximum size       */
				/* in bytes of the SCSI heads auto-      */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */

        ptr32 autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer for this SCSI	 */
				 /* command.			         */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */


	
	unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
				 /* the device.			         */

	unsigned long long lun_id; /* This is the 64-bit lun ID for      */
				 /* the device.			         */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
     	     

};

#endif

/* 
 * The scsi_iscsi_target_info structure is used with scsi_nmserv
 * structure for iSCSI. In this case the scsi_id_list of the
 * the scsi_nmserv struture will point to a buffer that is
 * a list (array) of scsi_iscsi_target_info structures. Also
 * for this case, the size_scsi_id field will be the size of 
 * the structure scsi_iscsi_target_info).
 */

struct scsi_iscsi_target_info {
    ushort  version;            /* Version                              */
    ushort  reserved;           /* Reserved for future use              */
    char name[256];      	/* iSCSI name of target                 */
    iscsi_ip_addr addr;  	/* IP address of target                 */
    uint64_t  port_num;  	/* Device port number                   */
};




/*
 * SCSI Name Server (SCIOLNMSRV) structure passed by pointer to 
 * ioctl of adapter driver. This structure is used to query the 
 * Name Server for all SCSI IDS (targets) that are registered.
 */
struct scsi_nmserv {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
	uchar   flags;          /* Flags for this operation.             */
	uchar   adap_set_flags; /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned.                             */
#define SCSI_NM_LIST_SHORT  0x1 /* This indicates the list supplied by   */
				/* caller was too short for the full     */
				/* list returned by the caller. In this  */
				/* case the list_len field will be       */
				/* update with the length of the list    */
				/* needed by the adapter to return the   */
				/* the full list.                        */
#define SCSI_NM_SZ_ID_WORDS 0x2 /* This indicates the size in the        */
                                /* size_scsi_id fields is a size in      */
                                /* words (4-byte units) and not bytes    */
	uchar   adapter_status; /* Adapter status (if valid), which is   */
				/* set by the adapter driver.            */
	uchar   size_scsi_id;   /* Size of the SCSI ID in the returned   */
				/* scsi_id_list. If SCSI_NM_SZ_ID_WORDS  */
                                /* is set in the adap_set_flags field,   */
				/* then this size is in words (4-byte    */
				/* units).  Otherwise the size is in     */
				/* bytes  This is set by the adaper      */
				/* driver.                               */
	uint    timeout_value;	/* timeout value for command, in secs.   */
				/* This is set by the caller.            */
	uint    list_len;       /* Length (in bytes) of scsi_id_list.    */
				/* This is set by the caller. It can be  */
				/* updated by the adapter driver when    */
				/* there are more ids then will fit in   */
				/* caller's buffer referenced by the     */
				/* scsi_id_list. Thus on completion the  */
				/* caller can determine if it needs to   */
				/* re-issue this ioctl with a larger     */
				/* buffer.                               */
	uint    num_ids;        /* Number of SCSI Ids in the             */
				/* scsi_id_list. This is set by the      */
				/* adapter driver.                       */
	char    *scsi_id_list;  /* Pointer to a buffer allocated         */
				/* by caller for the returned SCSI ID    */
				/* list.  This is set by the caller.     */
};


#ifdef _KERNEL

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Name Server (SCIOLNMSRV) structure passed by pointer to 
 * ioctl of adapter driver.
 *
 * This structure is used internally by the adapter driver for support
 * of 64-bit applications.
 */

struct scsi_nmserv64 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
	uchar   flags;          /* Flags for this operation.             */
	uchar   adap_set_flags; /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See defines for the struct  */
				/* scsi_nmserv.                          */
	uchar   adapter_status; /* Adapter status (if valid).            */
	uchar   size_scsi_id;   /* Size in bytes of a SCSI ID in the     */
				/* returned scsi_id_list.                */
	uint    timeout_value;	/* timeout value for command, in secs.   */
	uint    list_len;       /* Length (in bytes) of scsi_id_list.    */
	uint    num_ids;        /* Number of SCSI Ids in the             */
				/* scsi_id_list                          */
	ptr64   scsi_id_list;   /* Pointer to a buffer allocated by      */
				/* caller for the returned SCSI ID       */
				/* list.                                 */

};
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Name Server (SCIOLNMSRV) structure passed by pointer to 
 * ioctl of adapter driver.
 *
 * This structure is used internally by the adapter driver for support
 * of 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_nmserv32 {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
	uchar   flags;          /* Flags for this operation.             */
	uchar   adap_set_flags; /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned. See defines for the struct  */
				/* scsi_nmserv.                          */
	uchar   adapter_status; /* Adapter status (if valid).            */
	uchar   size_scsi_id;   /* Size in bytes of a SCSI ID in the     */
				/* returned scsi_id_list.                */
	uint    timeout_value;	/* timeout value for command, in secs.   */
	uint    list_len;       /* Length (in bytes) of scsi_id_list.    */
	uint    num_ids;        /* Number of SCSI Ids in the             */
				/* scsi_id_list                          */
	ptr32   scsi_id_list;   /* Pointer to a buffer allocated by      */
				/* caller for the returned SCSI ID       */
				/* list.                                 */

};

#endif /* _KERNEL */


/*
 * SCSI Query World Wide Name(SCIOLQWWN) structure passed by pointer to 
 * ioctl of adapter driver. This structure is used to query the 
 * Name Server for the SCSI ID of the specified world wide name.
 */

struct scsi_qry_wwn {
	ushort version;		/* The version number of this structure  */
				/* This allows the structure to expand   */
				/* in the future.                        */
	uchar   flags;          /* Flags for this operation.             */
	uchar   adap_set_flags; /* These flags are set by the SCSI       */
				/* adapter driver when a command is      */
				/* returned.                             */
	uchar   adapter_status; /* Adapter status (if valid). This is    */
				/* set by the adapter driver.            */
	unsigned long long scsi_id; /* SCSI ID returned by adapter driver*/
				/* for the specified World Wide Name.    */
	unsigned long long world_wide_name;/* World Wide Name set by     */
				/* caller of this ioctl.  This is set by */
				/* the caller.                           */
};

/*
 * SCSI transmit payload (SCIOLPAYLD) structure passed by 
 * pointer to ioctl of adapter driver
 */

struct scsi_trans_payld {
        ushort version;         /* The version number of this structure  */
                                /* This allows the structure to expand   */
                                /* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */
        uchar   flags;          /* Flags for this operation.             */
#define FC_SCSI_TRANS_SEQ   0x0 /* For FC send a FC sequence.            */
#define FC_SCSI_TRANS_ELS   0x1 /* For FC send a FC ELS                  */
#define ISCSI_TRANS_PDU     0x0 /* For iSCSI send an iSCSI PDU. For this */
				/* case the payld_buffer consists of the */
				/* entire iSCSI PDU--including the PDU   */
				/* header                                */
#define ISCSI_TRANS_TEXT    0x1 /* For iSCSI send a Text iSCSI PDU. For  */
				/* this case, the payld_buffer consists  */
				/* of just the text data sent and the    */
				/* response_buffer consists of just the  */
				/* text response data.                   */
#define ISCSI_TRANS_FINAL   0x2 /* For ISCSI text PDU, indicates that the*/
                                /* "F" bit should be set in the text PDU.*/
        uchar   adap_set_flags; /* These flags are set by the SCSI       */
                                /* adapter driver when a command is      */
                                /* returned.                             */
#define SCSI_TRANSPORT_STATUS 0x1/* Indicates the transport_status and   */
                                /* transport_stat_type fields are valid. */
	uchar   payld_type;     /* Payload Type. This is set by the      */
				/* caller.                               */
				/* For FC, this is the FC-4 Type.        */
	uchar   payld_ctl;      /* Transport payload control field.      */
				/* For FC, this is the router control.   */
				/* This is set by the caller.            */
        ushort  dev_flags;      /* flags to the SCSI adapter driver      */
	                        /* For valid FCP values, see the defines */
				/* the dev_flags field in the scsi_buf   */
				/* structure.  This is set by the        */
				/* caller.                               */
        int   transport_stat_type;/* Indicates how to interpret the      */
                                /* transport_status field. This is set   */
				/* by the adapter driver.                */
#define ISCSI_TRANS_GOOD  0x00  /* For ISCSI, indicates transfer worked; */
                                /* transport_status will contain length  */
                                /* of the response.                      */
#define ISCSI_TRANS_ERROR 0x01  /* For ISCSI, indicates text transfer    */
                                /* failed; transport_status will contain */
                                /* error number.                         */
        int   transport_status; /* This contains errors returned at the  */
                                /* tranport layer. This is set by the    */ 
				/* adapter driver.                       */
        unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
                                /* the device. This is set by the caller */
        char *payld_buffer;     /* Pointer to payload buffer created by  */
                                /* caller. This is set by the caller     */
        int payld_size;         /* Size (in bytes) of payload buffer     */
                                /* referenced by the payld_buffer field. */
				/* This is set by the caller.            */
				/* For FCP this buffer must not be larger*/
			        /* then 4096 bytes.                      */
				/* For iSCSI this buffer must not be     */
			        /* larger then 4096 bytes.               */
        char *response_buffer;  /* Pointer to response buffer created by */
                                /* caller. This is set by the caller     */
        int response_size;      /* Size (in bytes) of response buffer    */
                                /* referenced by the payld_buffer field. */
				/* This is set by the caller.            */
				/* For FCP this buffer must not be larger*/
			        /* then 4096 bytes.                      */
				/* For iSCSI this buffer must not be     */
			        /* larger then 4096 bytes.               */
        ushort add_flags;       /* Additional flags set by caller        */

#define SCSI_TRANS_INITR_HANDLE   0x1    /* initr_handle is valid        */
#define SCSI_TRANS_INITR_WW_VALID 0x2    /* initr_ww_name is valid       */
#define SCSI_TRANS_TARG_HANDLE    0x4    /* target_handle is valid       */
#define SCSI_TRANS_TARG_WW_VALID  0x8    /* target_ww_name is valid      */

        ushort add_adap_flags;  /* Additional flags returned             */ 

        uint64_t initr_ww_name; /* Initiator world wide name             */ 

        uint64_t target_ww_name;/* Associated Target' world wide name    */

	union {
	    uint64_t app_handle;
            void  *initr_handle;/* Initiator handle                      */
        } initiator;
	union {
	    uint64_t app_handle;
            void  *target_handle;/* Handle for destination target        */
        } target;
};

#ifdef _KERNEL

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI transmit payload (SCIOLPAYLD) version 0 structure passed 
 * by pointer to ioctl of adapter driver.
 *
 * This structure is used internally by the adapter driver for support
 * of 64-bit applications.
 */

struct scsi_trans_payld64v0 {
        ushort version;         /* The version number of this structure  */
                                /* This allows the structure to expand   */
                                /* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */
        uchar   flags;          /* Flags for this operation.             */
        uchar   adap_set_flags; /* These flags are set by the SCSI       */
                                /* adapter driver when a command is      */
                                /* returned.                             */
#define SCSI_TRANSPORT_STATUS 0x1/* Indicates the transport_status and   */
                                /* transport_stat_type fields are valid. */
	uchar   payld_type;     /* Payload Type                          */
				/* For FC, this is the FC-4 Type.        */
	uchar   payld_ctl;      /* Transport payload control field.      */
				/* For FC, this is the router control.   */
        ushort  dev_flags;      /* flags to the SCSI adapter driver      */
	                        /* For valid FCP values, see the defines */
				/* the dev_flags field in the scsi_buf   */
				/* structure.                            */    
        int   transport_stat_type;/* Indicates how to interpret the      */
                                /* transport_status field.               */
        int   transport_status; /* This contains errors returned at the  */
                                /* tranport layer.                       */
        unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
                                /* the device.                           */
        ptr64 payld_buffer;     /* Pointer to payload buffer created by  */
                                /* caller.                               */
        int payld_size;         /* Size (in bytes) of payload buffer     */
                                /* referenced by the payld_buffer field. */
				/* For FCP this buffer must not be larger*/
			        /* then 4096 bytes.                      */
        ptr64 response_buffer;  /* Pointer to response buffer created by */
                                /* caller.                               */
        int response_size;      /* Size (in bytes) of response buffer    */
                                /* referenced by the payld_buffer field. */
				/* For FCP this buffer must not be larger*/
			        /* then 4096 bytes.                      */
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI transmit payload (SCIOLPAYLD) version 0 structure passed 
 * by pointer to ioctl of adapter driver.
 *
 * This structure is used internally by the adapter driver for suppor
 * of 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_trans_payld32v0 {
        ushort version;         /* The version number of this structure  */
                                /* This allows the structure to expand   */
                                /* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_0                                                       */
        uchar   flags;          /* Flags for this operation.             */
        uchar   adap_set_flags; /* These flags are set by the SCSI       */
                                /* adapter driver when a command is      */
                                /* returned.                             */
#define SCSI_TRANSPORT_STATUS 0x1/* Indicates the transport_status and   */
                                /* transport_stat_type fields are valid. */
	uchar   payld_type;     /* Payload Type                          */
				/* For FC, this is the FC-4 Type.        */
	uchar   payld_ctl;      /* Transport payload control field.      */
				/* For FC, this is the router control.   */
        ushort  dev_flags;      /* flags to the SCSI adapter driver      */
	                        /* For valid FCP values, see the defines */
				/* the dev_flags field in the scsi_buf   */
				/* structure.                            */    
        int   transport_stat_type;/* Indicates how to interpret the      */
                                /* transport_status field.               */
        int   transport_status; /* This contains errors returned at the  */
                                /* tranport layer.                       */
        unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
                                /* the device.                           */
        ptr32 payld_buffer;     /* Pointer to payload buffer created by  */
                                /* caller.                               */
        int payld_size;         /* Size (in bytes) of payload buffer     */
                                /* referenced by the payld_buffer field. */
				/* For FCP this buffer must not be larger*/
			        /* then 4096 bytes.                      */
        ptr32 response_buffer;  /* Pointer to response buffer created by */
                                /* caller.                               */
        int response_size;      /* Size (in bytes) of response buffer    */
                                /* referenced by the payld_buffer field. */
				/* For FCP this buffer must not be larger*/
			        /* then 4096 bytes.                      */
};




/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI transmit payload (SCIOLPAYLD) structure passed by pointer to 
 * ioctl of adapter driver.
 *
 * This structure is used internally by the adapter driver for support
 * of 64-bit applications.
 */

struct scsi_trans_payld64 {
        ushort version;         /* The version number of this structure  */
                                /* This allows the structure to expand   */
                                /* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */
        uchar   flags;          /* Flags for this operation.             */
        uchar   adap_set_flags; /* These flags are set by the SCSI       */
                                /* adapter driver when a command is      */
                                /* returned.                             */
#define SCSI_TRANSPORT_STATUS 0x1/* Indicates the transport_status and   */
                                /* transport_stat_type fields are valid. */
	uchar   payld_type;     /* Payload Type                          */
				/* For FC, this is the FC-4 Type.        */
	uchar   payld_ctl;      /* Transport payload control field.      */
				/* For FC, this is the router control.   */
        ushort  dev_flags;      /* flags to the SCSI adapter driver      */
	                        /* For valid FCP values, see the defines */
				/* the dev_flags field in the scsi_buf   */
				/* structure.                            */    
        int   transport_stat_type;/* Indicates how to interpret the      */
                                /* transport_status field.               */
        int   transport_status; /* This contains errors returned at the  */
                                /* tranport layer.                       */
        unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
                                /* the device.                           */
        ptr64 payld_buffer;     /* Pointer to payload buffer created by  */
                                /* caller.                               */
        int payld_size;         /* Size (in bytes) of payload buffer     */
                                /* referenced by the payld_buffer field. */
				/* For FCP this buffer must not be larger*/
			        /* then 4096 bytes.                      */
        ptr64 response_buffer;  /* Pointer to response buffer created by */
                                /* caller.                               */
        int response_size;      /* Size (in bytes) of response buffer    */
                                /* referenced by the payld_buffer field. */
				/* For FCP this buffer must not be larger*/
			        /* then 4096 bytes.                      */
        ushort add_flags;       /* Additional flags set by caller        */

        /* see defines in scsi_trans_payld struct */

        ushort add_adap_flags;  /* Additional flags returned             */ 

        uint64_t initr_ww_name; /* Initiator world wide name             */ 

        uint64_t target_ww_name;/* Associated Target' world wide name    */

	union {
	    uint64_t app_handle;
            ptr64 initr_handle;/* Initiator handle                      */
        } initiator;
	union {
	    uint64_t app_handle;
            ptr64 target_handle;/* Handle for destination target        */
        } target;
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI transmit payload (SCIOLPAYLD) structure passed by pointer to 
 * ioctl of adapter driver.
 *
 * This structure is used internally by the adapter driver for suppor
 * of 32-bit applications by 64-bit kernel extensions.
 */

struct scsi_trans_payld32 {
        ushort version;         /* The version number of this structure  */
                                /* This allows the structure to expand   */
                                /* in the future.                        */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */
        uchar   flags;          /* Flags for this operation.             */
        uchar   adap_set_flags; /* These flags are set by the SCSI       */
                                /* adapter driver when a command is      */
                                /* returned.                             */
#define SCSI_TRANSPORT_STATUS 0x1/* Indicates the transport_status and   */
                                /* transport_stat_type fields are valid. */
	uchar   payld_type;     /* Payload Type                          */
				/* For FC, this is the FC-4 Type.        */
	uchar   payld_ctl;      /* Transport payload control field.      */
				/* For FC, this is the router control.   */
        ushort  dev_flags;      /* flags to the SCSI adapter driver      */
	                        /* For valid FCP values, see the defines */
				/* the dev_flags field in the scsi_buf   */
				/* structure.                            */    
        int   transport_stat_type;/* Indicates how to interpret the      */
                                /* transport_status field.               */
        int   transport_status; /* This contains errors returned at the  */
                                /* tranport layer.                       */
        unsigned long long scsi_id; /* This is the 64-bit SCSI ID for    */
                                /* the device.                           */
        ptr32 payld_buffer;     /* Pointer to payload buffer created by  */
                                /* caller.                               */
        int payld_size;         /* Size (in bytes) of payload buffer     */
                                /* referenced by the payld_buffer field. */
				/* For FCP this buffer must not be larger*/
			        /* then 4096 bytes.                      */
        ptr32 response_buffer;  /* Pointer to response buffer created by */
                                /* caller.                               */
        int response_size;      /* Size (in bytes) of response buffer    */
                                /* referenced by the payld_buffer field. */
				/* For FCP this buffer must not be larger*/
			        /* then 4096 bytes.                      */
        ushort add_flags;       /* Additional flags set by caller        */

        /* see defines in scsi_trans_payld struct */

        ushort add_adap_flags;  /* Additional flags returned             */  

        uint64_t initr_ww_name; /* Initiator world wide name             */ 

        uint64_t target_ww_name;/* Associated Target' world wide name    */

	union {
	    uint64_t app_handle;
            ptr32 initr_handle;/* Initiator handle                      */
        } initiator;
	union {
	    uint64_t app_handle;
            ptr32 target_handle;/* Handle for destination target        */
        } target;
};
#endif /* _KERNEL */

/*-----------------------------------------------------------------------
 * scsi_fc_link_event_info 
 * Used with SCIOLCHBA/FC_SCSI_EVENT_INFO IOCTL/Command
 *-----------------------------------------------------------------------
 */
typedef struct scsi_fc_link_event_info {
    uint64_t scsi_id;          /* SCSI ID on which this event occurred  */
    uint32_t resvd[4];         /* Reserved                              */
    uint64_t time_stamp;       /* The kernel in-memory lbolt value      */
} scsi_fc_link_event_info_t;

/*-----------------------------------------------------------------------
 * scsi_fc_rscn_event_info 
 * Used with SCIOLCHBA/FC_SCSI_EVENT_INFO IOCTL/Command
 *-----------------------------------------------------------------------
 */
typedef struct scsi_fc_rscn_event_info {
    uint64_t scsi_id;          /* SCSI ID on which this event occurred  */
    uint32_t nport_page;       /* affected port_id pages                */
    uint32_t resvd[3];         /* Reserved                              */
    uint64_t time_stamp;       /* The kernel in-memory lbolt value      */
} scsi_fc_rscn_event_info_t;

/*-----------------------------------------------------------------------
 * scsi_prop_event_info 
 * Used with SCIOLCHBA/FC_SCSI_EVENT_INFO IOCTL/Command
 *-----------------------------------------------------------------------
 */
typedef struct scsi_prop_event_info {
    uint32_t event_type;       /* Event type returned to the caller.    */
                               /* For FC, the values defined are as     */
                               /* follows.                              */
#define FC_SCSI_NDD_HARD_FAIL  0x01 /* A hardware failure occurred      */
#define FC_SCSI_NDD_CONNECTED  0x08 /* Device open successful           */
#define FC_SCSI_PLOGI          0x0C /* Received unsolicited PLOGI       */
#define FC_SCSI_LOGO           0x0D /* Received unsolicited LOGO        */
#define FC_SCSI_PRLO           0x0E /* Received unsolicited PRLO        */
#define FC_SCSI_DEAD_LINK      0x11 /* The adapter link is dead         */
#define FC_SCSI_HALT_ADAP      0x14 /* the adapter is halted            */
#define FC_SCSI_RESUME_ADAP    0x15 /* The adapter is being resumed     */
#define FC_SCSI_RESET_ADAP     0x16 /* The adapter is being reset       */
#define FC_SCSI_FARP           0x17 /* Received unsolicited FARP        */
#define FC_SCSI_DYNTRK         0x18 /* Dynamic tracking event occurred  */
    uint32_t prop_data[3];     /* Remaining proprietary data, is updated*/
                               /* depending on the event_type field     */
                               /* above or the event_code field from the*/
                               /* scsi_event_buf struct.                */
                               /* In case of PLOGI, LOGO, PRLO and FARP */
                               /* event types prop_data[0] will have the*/
                               /* Nx_Port ID of the initiating port.    */
                               /* In case of FC_SCSI_DYNTRK event type, */
                               /* prop_data[0] will have the old Nx_Port*/
                               /* ID and prop_data[1] will have the new */
                               /* Nx_Port ID.                           */
    uint32_t resvd[2];         /* Reserved                              */
    uint64_t time_stamp;       /* The kernel in-memory lbolt value      */
} scsi_prop_event_info_t;


/*-----------------------------------------------------------------------
 * scsi_event_buf 
 * Used with SCIOLCHBA/FC_SCSI_EVENT_INFO IOCTL/Command
 *-----------------------------------------------------------------------
 */
typedef struct scsi_event_buf {
    uint32_t event_code;       /* type of event */
#define FC_SCSI_EVENT_LIP_OCC       1
#define FC_SCSI_EVENT_LINK_UP       2
#define FC_SCSI_EVENT_LINK_DOWN     3
#define FC_SCSI_EVENT_LIP_RST       4
#define FC_SCSI_EVENT_RSCN          5
#define FC_SCSI_EVENT_PROPRIETARY   0xFFFF
    union {
      scsi_fc_link_event_info_t link_event_info;
      scsi_fc_rscn_event_info_t rscn_event_info;
      scsi_prop_event_info_t  prop_event_info;
    } event;
} scsi_event_buf_t;

/*
 * This is a SCSI common HBA structure passed by pointer to IOCTL of
 * the FC adapter for the SCIOLCHBA IOCTL operation.
 * This structure is used for setting/getting FC adapter RNID data 
 * as well as for getting adapter port statistics as defined in the 
 * FC-MI version 1.92 standard for common HBA API. 
 */
struct scsi_chba {
        ushort version;         /* The version number of this structure  */
                                /* This allows the structure to expand   */
                                /* in the future.                        */
        uchar   flags;          /* Flags for this operation.             */
        uchar cmd;              /* Commands for this operation.          */ 
#define FC_SCSI_GET_RNID     0x0  /* For getting adapter's RNID data     */
#define FC_SCSI_SET_RNID     0x1  /* For setting RNID data on the adapter*/
#define FC_SCSI_ADAP_STAT    0x2  /* For getting adapter port statistics */
#define FC_TRAFFIC_STAT      0x3  /* For getting adapter's traffic       */
                                  /* statistics.                         */
                                  /* For FC, this is FC-4 statistics     */
#define FC_SCSI_TRAFFIC_STAT 0x4  /* For getting the FCP traffic         */
                                  /* statistics from the LUN.            */
#define FC_SCSI_EVENT_INFO   0x5  /* For getting adapter's event records */
#define FC_SCSI_DRIVER_INFO  0x6  /* For getting adapter's drivers info  */
                                  /* This option uses the driver_info    */
				  /* union.                              */
#define FC_SCSI_RESET_STAT   0x8  /* For reseting some of the adapter's  */
                                  /* drivers statistics.                 */
#define ISCSI_SCSI_ADAP_STAT 0x2/* For getting the adapter statistics    */
				/* this cmd uses the iscsi_adap_stat     */
				/* union below                           */
#define ISCSI_TRAFFIC_STAT 0x3  /* Fetch traffic statistics data     */
				/* This option uses the traffic_info     */
				/* union.                                */
#define ISCSI_LUN_TRAFFIC_STAT 0x4/* For getting the iSCSI traffic       */
                                  /* statistics from the LUN.            */
#define ISCSI_SCSI_DRIVER_INFO  0x6 /* For getting adapter's drivers info*/
                                /* This option uses the driver_info      */
				/* union.                                */
#define ISCSI_SCSI_PING     0x7 /* Sends network ping to specified       */
				/* address. This option uses the         */
				/* scsi_ping union.                      */
        uchar   adap_set_flags; /* These flags are set by the SCSI       */
                                /* adapter driver when a command is      */
                                /* returned.                             */
        uchar   adapter_status; /* Adapter status (if valid). This is    */
                                /* set by the adapter driver.            */
        union 
        {   /* Adapter RNID data structure                               */
            /* This structure is used if cmd is set as follows ...       */
            /* cmd = FC_SCSI_GET_RNID, or                                */
            /* cmd = FC_SCSI_SET_RNID                                    */
            struct     
            {  
                uint  opcode;        /* Link services code.              */
                uchar node_id_fmt;   /* Node ID format                   */
                uchar com_nid_len;   /* Common Node ID length            */
#define RNID_COM_NID_LEN    16
                uchar resvd1;        /* Reserved for future use          */
                uchar spfc_nid_len;  /* Specific Node ID Length          */
#define RNID_SPFC_NID_LEN   52
                                     /* Common Identification Data       */
                unsigned long long port_name; /* port name (WWN)         */
                unsigned long long node_name; /* node/fabric name        */ 
                                     /* Specific topology discovery data */
	        uint64_t initiator_ww_name; /* World wide name of        */
				     /* virtual initiator                */
                uint64_t vendor_unique;       /* Vendor unique           */
                uint32_t node_type;           /* Type of node            */
#define RNID_TYP_UNKN       0x1      /* Unknown type                     */
#define RNID_TYP_OTHER      0x2      /* Other type                       */
#define RNID_TYP_HUB        0x3      /* Hub type                         */
#define RNID_TYP_SWITCH     0x4      /* Switch type                      */
#define RNID_TYP_GW         0x5      /* Gateway type                     */
#define RNID_TYP_CONVERTER  0x6      /* Converter type                   */
#define RNID_TYP_HBA        0x7      /* Host Bus Adapter                 */
#define RNID_TYP_PROXY      0x8      /* Proxy-agent                      */
#define RNID_TYP_STOR_DEV   0x9      /* Storage device (disk, CD,etc)    */
#define RNID_TYP_HOST       0xa      /* Host                             */
#define RNID_TYP_STOR_SYS   0xb      /* Storage Subsystem (raid,library) */
#define RNID_TYP_MODULE     0xc      /* Module                           */
#define RNID_TYP_SW_DR      0xd      /* Software driver                  */
                uint32_t port_number;         /* Physical port number    */
                                     
                uint32_t num_att_nodes;       /* No. of Attached Nodes   */
                uchar node_mgmt;              /* Node Management         */
#define RNID_MGMT_IP_UDP_SNMP    0x0 /* Protocol IP,UDP,SNMP             */
#define RNID_MGMT_IP_TCP_TELNET  0x1 /* Protocol IP,TCP,Telnet           */
#define RNID_MGMT_IP_TCP_HTTP    0x2 /* Protocol IP,TCP,HTTP             */
#define RNID_MGMT_IP_TCP_HTTPS   0x3 /* Protocol IP,TCP,HTTPS            */
                uchar   ip_version;           /* IP Version              */
#define RNID_IPV4           0x1      /* IP Version 4.                    */
#define RNID_IPV6           0x2      /* IP Version 6.                    */
                ushort   udp_port;            /* UDP Port                */
                uint64_t ip_addr[2]; /* IP address of management entity  */
                uchar    resvd2[2];  /* reserved for future use          */
                ushort   disc_flags; /* topology discovery flags         */
#define RNID_TOP_DISC_SPT   0x1      /* Topology Discovery Support       */
#define RNID_LOOP_POS_VALID 0x2      /* Loop Position Valid              */
            } rnid_data;

            /* Adapter port statistics data structure                    */
            /* This structure is used if cmd = FC_SCSI_ADAP_STAT         */
            struct scsi_chba_adap_stat
            {
                uint64_t secondsSinceLastReset;
                uint64_t TxFrames; /* number of frames transmitted       */     
                uint64_t TxWords;  /* Fibre Channel Kbytes transmitted   */
                uint64_t RxFrames; /* number of frames received          */
                uint64_t RxWords;  /* Fibre Channel Kbytes received      */
                uint64_t LIPCount; /* count of LIP events on FC-AL       */
                uint64_t NOSCount; /* count of NOS events                */
                uint64_t ErrorFrames; /* number of frames received       */
                                      /* with the CRC error              */
                uint64_t DumpedFrames; /* number of lost frames          */
                uint64_t LinkFailureCount;  /* count of link failures    */
                uint64_t LossOfSyncCount;   /* count of loss of sync.    */
                uint64_t LossOfSignalCount; /* count of loss of signal   */
                uint64_t PrimitiveSeqProtocolErrCount; 
                                   /* count of primitive sequence errors */
                uint64_t InvalidTxWordCount; 
                                   /* count of invalid transmission words */
                                   /* received                            */
                uint64_t InvalidCRCCount;
                                   /* count of CRC errors in a received   */
                                   /* frame                               */
                uint LongTermDma;  /* size of the pool needed to map      */
                                   /* control structures and long term    */
                                   /* mapped buffers                      */
                uint SmallXfers;   /* size of the buffer pool used to map */
                                   /* buffers for small transfers         */
                uint NoOfInterrupt;
                                   /* total number of interrupts          */
                uint NoOfSpuriousInterrupts;
                                   /* total no of spurious intrerrupts    */
                uchar AttentionType;
                                   /* link up or down indicator           */
                uchar AlPaGranted; /* AL_PA this ap was given in the LIP  */
                uchar LipAlPs;     /* loop Source Physical Address        */
                uchar LipType;     /* type of LIP: Initialization, Error  */
                                   /* Rst to another port, Rst this port  */
                uchar Topology;    /* either FC-AL (1) or FC-AL (2)       */
                uchar LnkDwnState; /* link Down N_Port State.             */
                uchar LnkDwnTxState;
                                   /* link Down N_Port Transmitter State  */
                uchar LnkDwnRcvState;
                                   /* link Down N_Port Receiver State     */
                uchar LnkDwnLnkSpeed;
                                   /* speed just before link was Down     */
                uchar LnkDwnTf;    /* link down transmitter fault         */
                uchar LnkDwnLu;    /* link down link unusable             */
                uchar CurrLnkState;
                                   /* current N_Port State                */
                uchar CurrLnkTxState;
                                   /* current N_Port Transmitter State    */
                uchar CurrLnkRcvState;
                                   /* current N_Port Receiver State       */
                uchar CurrLnkSpeed;
                                   /* current Link Speed                  */
                uchar CurrTf;      /* current Link transmitter fault      */
                uchar CurrLu;      /* current Link unusable               */
                uint ElasticBufOverrunErrCnt;
                                   /* number of times the link interface  */
                                   /* has had its elastic buffer overrun. */
            } adap_stat;

            /* Adapter port statistics data structure                    */
            /* This structure is used if cmd = ISCSI_SCSI_ADAP_STAT      */
            struct scsi_iscsi_adap_stat
            { 
		uint64_t scsi_id;       /* SCSI ID of the LUN, set by the*/
                                        /* caller if cmd is set to       */
                                        /* FC_SCSI_TRAFFIC_STAT or       */
			                /* ISCSI_LUN_TRAFFIC_STAT        */
		uint64_t lun_id;        /* LUN ID of the LUN, set by the */
                                        /* caller if cmd is set to       */
                                        /* FC_SCSI_TRAFFIC_STAT  or      */
			                /* ISCSI_LUN_TRAFFIC_STAT        */
                uint64_t sec_since_reset;/* Seconds since last adapter   */
					/* reset                         */
		uint64_t link_ups;      /* Number of link up events      */
		uint64_t link_downs;    /* Number of link down events    */
		uint64_t dhcp_expired;  /* Number of times the DHCP      */
					/* lease expired                 */
                uint64_t frames_tx;     /* number of frames transmitted  */     
                uint64_t bytes_tx;      /* Bytes transmitted             */
                uint64_t frames_rcv;    /* number of frames received     */
                uint64_t bytes_rcv;     /* Bytes received                */
                uint64_t crc_err_cnt;   /* CRC error count               */
		uint64_t encode_err_cnt;/* Encoding error count          */
		uint64_t ip_rcv_overlap;/* IP fragment received overlap  */
				        /* count.                        */
		uint64_t tcp_ret_timer_cnt;/* TCP retransmit timer expire*/
				        /* count.                        */
		uint64_t tcp_per_timer_cnt;/* TCP persist timer expire   */
				        /* count.                        */
		uint64_t tcp_rcv_seg_err_cnt;/* TCP receive segment error*/
				        /* count.                        */
		uint64_t iSCSI_PDU_cnt_tx;/* transmitted iSCSI PDU count */
		uint64_t iSCSI_tx_bytes; /* transmitted iSCSI data bytes */
		uint64_t iSCSI_PDU_cnt_rcv;/* receiveded iSCSI PDU count */
		uint64_t iSCSI_rcv_bytes; /* received iSCSI data bytes   */
		uint64_t iSCSI_io_cnt;    /* iSCSI I/O count             */
		uint64_t iSCSI_fmt_err_cnt;/* iSCSI format error count   */
		uint64_t iSCSI_hdr_dig_err_cnt;/* iSCSI header digest    */
					   /* error count                */
		uint64_t iSCSI_data_dig_err_cnt;/* iSCSI data digest     */
					   /* error count                */
		uint64_t iSCSI_seq_err_cnt;/* iSCSI sequence error count */
		uint64_t reserved[12];   /* Reserved for future use      */

		
            } iscsi_adap_stat;

            /* Adapter's traffic statistical counters defined in         */
            /* FC-HBA rev 9 for FC                                       */
            /* This structure is used if cmd = FC_TRAFFIC_STAT           */
            /* or if cmd = FC_SCSI_TRAFFIC_STAT                          */
            struct scsi_chba_traffic_info
            {
              uint trans_type;       /* Transport Type. This is set by   */
                                     /* the caller.                      */
                                     /* For FC, this is the FC-4 Type.   */
#define FC_SCSI_IP_FC_TYPE  0x05     /* FC-4 type for IP over FC         */
#define FC_SCSI_FCP_TYPE    0x08     /* FC-4 type for FCP                */
#define ISCSI_SCSI_TYPE     0x01     /* For iSCSI this is for iSCSI stats*/
              struct scsi_chba_traffic_stat
              {
                uint64_t inp_reqs;   /* Input requests                   */
                uint64_t out_reqs;   /* Output requests                  */
                uint64_t ctrl_reqs;  /* control requests                 */
                uint64_t inp_bytes;  /* input bytes                      */
                uint64_t out_bytes;  /* output bytes                     */
                uint64_t resvd1;     /* Reserved                         */
              } traffic_stat;        /* Traffic  statistics              */
                                     /* For FC, this is FC-4 statistics  */
              uint64_t scsi_id;      /* SCSI ID of the LUN, set by the   */
                                     /* caller if cmd is set to          */
                                     /* FC_SCSI_TRAFFIC_STAT             */
              uint64_t lun_id;       /* LUN ID of the LUN, set by the    */
                                     /* caller if cmd is set to          */
                                     /* FC_SCSI_TRAFFIC_STAT             */
              unsigned long long world_wide_name; /* World wide name of  */
                                     /* the LUN set by the caller if cmd */
                                     /* is set to FC_SCSI_TRAFFIC_STAT   */
              unsigned long long node_name; /* Node name of the LUN set  */
                                     /* by the caller if cmd is set to   */
                                     /* FC_SCSI_TRAFFIC_STAT             */
	      uint64_t initiator_ww_name; /* World wide name of          */
				     /* virtual initiator                */
              uint64_t resvd2;       /* Reserved                         */
            } traffic_info;

            /* Adapter event information data structure.                 */
            /* This structure is used if cmd = FC_SCSI_EVENT_INFO        */
            struct scsi_chba_event_info
            {
              uint32_t event_type;   /* Type of event buffer             */
#define FC_SCSI_EVENT_TYPE   0       /* Event type for FC                */
              uint32_t event_bufs_avail_flag;/* Event requested or events*/
                                     /* available flag. It is a bitmap of*/
                                     /* the various event buffers that   */
                                     /* are available for a specific     */
                                     /* event_type defined above.        */
                                     /* The caller will set this         */
                                     /* appropriately using the #defines */
                                     /* below to request a single event  */
                                     /* buffer. If new data in this event*/
                                     /* buffer is available, it will be  */
                                     /* sent to the caller along with    */
                                     /* this field updated or bitwise    */
                                     /* OR'ed with #define values below  */
                                     /* corresponding to all other event */
                                     /* buffers that are available.      */
                                     /* Based on the value of this field */
                                     /* returned, the caller can request */
                                     /* other event buffer data.         */
#define FC_SCSI_EVENT_BUF  0x01      /* Event buffer as defined for the  */
                                     /* HBA_GetEventBuffer common HBA API*/
                                     /* function defined in FC-HBA rev 9 */
              uint32_t event_count;  /* Number of event records requested*/
                                     /* by the caller.                   */
                                     /* The caller will set this, but    */
                                     /* the FC driver will return the    */
                                     /* actual value back to the caller. */
              unsigned long long event_buf;/* Pointer to the event buffer*/
              int event_size;        /* size of an event record in bytes */
                                     /* In case of FC, 1 record = 10words*/
              uint32_t max_events;   /* maximum number of events in the  */
                                     /* event buffer.                    */
                                     /* The caller will set this, but    */
                                     /* the FC driver will return the    */
                                     /* actual value back to the caller. */
              uint32_t lost_events;  /* Number of events lost since the  */
                                     /* last get events query from the   */
                                     /* caller.                          */
                                     /* This is returned to the caller.  */
              uint64_t resvd;        /* Reserved                         */
            } event_info;

            /* Adapter driver information                                */
            /* This structure is used if cmd = FC_SCSI_DRIVER_INFO       */
            struct scsi_chba_driver_info
            {
              uint trans_type;       /* Transport Type. This is set by   */
                                     /* the caller.                      */
                                     /* For FC, this is the FC-4 Type.   */
              struct {
                uint64_t no_dma_resrc_cnt;  /* Count of DMA failures due */
                                     /* to no DMA resources available.   */
                uint64_t no_adap_elems_cnt; /* Count of failure to       */
                                     /* allocate an adapter command      */
                                     /* element due to no more command   */
                                     /* elements available.              */
                uint64_t resvd1[3];  /* Reserved                         */
              } adap_driver_info;

              uint64_t no_cmd_resrc_cnt;  /* Count of failure to         */
                                     /* allocate a command due to no     */
                                     /* command resources available      */
              uint64_t resvd2[3];    /* Reserved                         */
              struct {
                uint adap_num_act_cmds;
                                     /* Number of active cmds in         */
                                     /* adapter  driver                  */
                uint adap_act_high_water;
                                     /* High water mark of               */
                                     /* Active requests in adap driver   */
                uint adap_num_pend_cmds ;
                                     /* Number of pending cmds           */
                                     /* in adapter driver                */
                uint adap_pend_high_water;
                                     /* High water mark of pending       */
                                     /* requests in adap driver          */
                uint adap_heldoff_num_cmds;
                                     /* Number of commands in the adap   */
                                     /* driver held off queue            */
                uint adap_heldoff_high_water;
                                     /* High water mark of no of cmds in */
                                     /* the adap driver held off queue   */

              } rem_adap_driver_info;

              uint driver_num_act_cmds;
                                     /* Number of active cmds in         */
                                     /* SCSI-FC driver                   */
              uint driver_act_high_water;
                                     /* High water mark of active        */
                                     /* requests in SCSI-FC driver       */
              uint driver_num_pend_cmds;
                                     /* Number of pending cmds in        */
                                     /* SCSI-FC driver                   */
              uint driver_pend_high_water;
                                     /* High water mark of pending       */
                                     /* requets in SCSI-FC driver        */
            } driver_info;
	    /* Send iSCSI PING to specified address                      */
            /* This structure is used if cmd = ISCSI_SCSI_PING           */
            struct scsi_ping
            {
              uint reserved;         /* Reserved for future use.         */
	      
	      union {
		iscsi_ip_addr iscsi_addr;/* iSCSI address                */ 
		uint64_t resvd2[2];  /* reserved for future use.         */
	      }addr_un;
              uint64_t resvd3;       /* Reserved for future use.         */
            } ping;
        } un;
};
/*
 * This structure is used for the ioctl SCIOLADAPEVENTLOG operation.
 */
struct scsi_adap_event_log{

        ushort version;         /* The version number of this structure   */
                                /* This allows the structure to expand    */
                                /* in the future.                         */
        uchar  flags;           /* Flags for this operation.              */
        uchar  cmd;             /* Commands for this operation.           */
#define READ_ADAP_EVENTLOG  0x1 /* Read event log operation               */
        uint   log_buffer_size; /* Size of user allocated buffer size     */
        char   *log_buf_ptr;    /* ptr to user allocated buffer           */
                                /* it will be used to copy back adapter's */
                                /* errorlog                               */
        uint additional_status; /* any error status reported back to user */
};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * This structure is used for the ioctl SCIOLADAPEVENTLOG operation.
 *
 * This structure is used internally by the adapter driver for support
 * of 64-bit applications.
 */
struct scsi_adap_event_log64{

        ushort version;         /* The version number of this structure  */
                                /* This allows the structure to expand   */
                                /* in the future.                        */
        uchar  flags;           /* Flags for this operation.             */
        uchar  cmd;             /* Commands for this operation.          */
        uint   log_buffer_size; /* Size of allocated log buffer          */
        ptr64  log_buf_ptr;     /* ptr to log buffer                     */
        uint additional_status; /* any error status reported back to user */
};
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * This structure is used for the ioctl SCIOLADAPEVENTLOG operation.
 *
 * This structure is used internally by the adapter driver for support
 * of 32-bit applications.
 */
struct scsi_adap_event_log32{

        ushort version;         /* The version number of this structure  */
                                /* This allows the structure to expand   */
                                /* in the future.                        */
        uchar  flags;           /* Flags for this operation.             */
        uchar  cmd;             /* Commands for this operation.          */
        uint   log_buffer_size; /* Size of allocated pel buffer          */
        ptr32  log_buf_ptr;     /* ptr to lopg buffer                    */
        uint additional_status; /* any error status reported back to user */
};
#endif /* _KERNEL */
 

/*
 * This is a generic SCSI HBA structure passed by pointer to ioctl of
 * the FC adapter for the SCIOLPASSTHRUHBA ioctl operation.
 * This structure is used for FC adapter or HBA passthru operations.
 */
struct scsi_passthru_hba {
        ushort version;         /* The version number of this structure  */
                                /* This allows the structure to expand   */
                                /* in the future.                        */
        uchar   flags;          /* Flags for this operation.             */
        uchar cmd;              /* Commands for this operation.          */
#define HBA_EFC_PTHRU_MB   0x0  /* FC adapter passthru mailbox operation */
#define HBA_QLISC_PTHRU_MB 0x1  /* iSCSI adapter passthru mailbox        */
                                /* operation                             */
#define HBA_QLFC_PTHRU_MB   0x2 /* Qlogic FC adapter passthru mailbox    */
                                /* operation                             */
        uchar   adap_set_flags; /* These flags are set by the SCSI       */
                                /* adapter driver when a command is      */
                                /* returned.                             */
        uchar   adapter_status; /* Adapter status (if valid). This is    */
                                /* set by the adapter driver.            */
        uchar data_dir;         /* Direction of data in the data buffer  */
#define HBA_READ     0x0        /* Read from the HBA                     */
#define HBA_WRITE    0x1        /* Write to the HBA                      */
        int  cmd_timeout;       /* The timeout value in seconds. It is   */
                                /* the number of seconds the HBA should  */
                                /* wait for the command to complete.     */
                                /* It is set by the caller.              */ 
#define HBA_EFC_PTHRU_MB_TO  20 /* FC adapter passthru mailbox command   */
                                /* timeout.                              */
#define HBA_QLFC_PTHRU_MB_TO 20 /* FC adapter passthru mailbox command   */
                                /* timeout.                              */
        char *payld_buffer;     /* Pointer to payload buffer created by  */
                                /* caller. This is set by the caller     */
                                /* In case the cmd is HBA_EFC_PTHRU_MB,  */
                                /* the mailbox command code is placed in */
                                /* payld_bufer[1]. The mailbox command   */
                                /* codes are defined in the efc_mailbox  */
                                /* structure in efcdd.h                  */
        int payld_size;         /* Size (in bytes) of payload buffer     */
                                /* referenced by the payld_buffer field. */
                                /* This is set by the caller.            */
                                /* For FCP this buffer must not be larger*/
                                /* then 4096 bytes.                      */
        int64_t payld_data_addr_offset; /* This is an offset in the      */
                                /* payld_buffer that points to the real  */
                                /* bus address of the data_buffer, set   */
                                /* by the caller.                    */
                                /* This is set to -1 by the caller only  */
                                /* if the data buffer is invalid for the */
                                /* intended passthru operation.          */
        char *response_buffer;  /* Pointer to response buffer created by */
                                /* caller. This is set by the caller     */
        int response_size;      /* Size (in bytes) of response buffer    */
                                /* referenced by the payld_buffer field. */
                                /* This is set by the caller.            */
                                /* For FCP this buffer must not be larger*/
                                /* then 4096 bytes.                      */
        char *data_buffer;      /* Pointer to data returned to/from the  */
                                /* HBA. This is created by the caller    */
        int data_size;          /* Size (in bytes) of data buffer        */
                                /* This is set by the caller.            */
                                /* For FCP this buffer must not be larger*/
                                /* then 4096 bytes.                      */
                                /* In case of passthru mailbox, the      */
                                /* caller fills in the data size in the  */
                                /* first BDE location of the payload     */
                                /* buffer.                               */
};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * FC SCSI HBA structure passed by pointer to ioctl of the FC adapter for
 * the SCIOLPASSTHRUHBA ioctl operation.
 *
 * This structure is used internally by the adapter driver for support
 * of 64-bit applications.
 */
struct scsi_passthru_hba64 {
        ushort version;         /* The version number of this structure  */
                                /* This allows the structure to expand   */
                                /* in the future.                        */
        uchar   flags;          /* Flags for this operation.             */
        uchar   cmd;            /* Commands for this operation.          */ 
        uchar   adap_set_flags; /* These flags are set by the SCSI       */
                                /* adapter driver when a command is      */
                                /* returned.                             */
        uchar   adapter_status; /* Adapter status (if valid). This is    */
                                /* set by the adapter driver.            */
        uchar data_dir;         /* Direction of data in the data buffer  */
        int  cmd_timeout;       /* The timeout value in seconds. It is   */
                                /* the number of seconds the HBA should  */
                                /* wait for the command to complete.     */
                                /* It is set by the caller.              */
        ptr64 payld_buffer;     /* Pointer to payload buffer created by  */
                                /* caller. This is set by the caller     */
        int payld_size;         /* Size (in bytes) of payload buffer     */
                                /* referenced by the payld_buffer field. */
                                /* This is set by the caller.            */
                                /* For FCP this buffer must not be larger*/
                                /* then 4096 bytes.                      */
        int64_t payld_data_addr_offset; /* This is a signed offset in    */ 
                                /* the payld_buffer that points to the   */
                                /* real bus address of the data_buffer   */
        ptr64 response_buffer;  /* Pointer to response buffer created by */
                                /* caller. This is set by the caller     */
        int response_size;      /* Size (in bytes) of response buffer    */
                                /* referenced by the payld_buffer field. */
                                /* This is set by the caller.            */
                                /* For FCP this buffer must not be larger*/
                                /* then 4096 bytes.                      */
        ptr64 data_buffer;      /* Pointer to data returned to/from the  */
                                /* HBA. This is created by the caller    */ 
        int data_size;          /* Size (in bytes) of data buffer        */
                                /* This is set by the caller.            */
                                /* For FCP this buffer must not be larger*/
                                /* then 4096 bytes.                      */
                                /* In case of passthru mailbox, the      */
                                /* caller fills in the data size in the  */
                                /* first BDE location of the payload     */
                                /* buffer.                               */
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * FC SCSI HBA structure passed by pointer to ioctl of the FC adapter for
 * the SCIOLPASSTHRUHBA ioctl operation.
 *
 * This structure is used internally by the adapter driver for support
 * of 32-bit applications.
 */
struct scsi_passthru_hba32 {
        ushort version;         /* The version number of this structure  */
                                /* This allows the structure to expand   */
                                /* in the future.                        */
        uchar   flags;          /* Flags for this operation.             */
        uchar   cmd;            /* Commands for this operation.          */ 
        uchar   adap_set_flags; /* These flags are set by the SCSI       */
                                /* adapter driver when a command is      */
                                /* returned.                             */
        uchar   adapter_status; /* Adapter status (if valid). This is    */
                                /* set by the adapter driver.            */
        uchar data_dir;         /* Direction of data in the data buffer  */
        int  cmd_timeout;       /* The timeout value in seconds. It is   */
                                /* the number of seconds the HBA should  */
                                /* wait for the command to complete.     */
                                /* It is set by the caller.              */
        ptr32 payld_buffer;     /* Pointer to payload buffer created by  */
                                /* caller. This is set by the caller     */
        int payld_size;         /* Size (in bytes) of payload buffer     */
                                /* referenced by the payld_buffer field. */
                                /* This is set by the caller.            */
                                /* For FCP this buffer must not be larger*/
                                /* then 4096 bytes.                      */
        int64_t payld_data_addr_offset; /* This is a signed offset in    */ 
                                /* the payld_buffer that points to the   */
                                /* real bus address of the data_buffer   */
        ptr32 response_buffer;  /* Pointer to response buffer created by */
                                /* caller. This is set by the caller     */
        int response_size;      /* Size (in bytes) of response buffer    */
                                /* referenced by the payld_buffer field. */
                                /* This is set by the caller.            */
                                /* For FCP this buffer must not be larger*/
                                /* then 4096 bytes.                      */
        ptr32 data_buffer;      /* Pointer to data returned to/from the  */
                                /* HBA. This is created by the caller    */ 
        int data_size;          /* Size (in bytes) of data buffer        */
                                /* This is set by the caller.            */
                                /* For FCP this buffer must not be larger*/
                                /* then 4096 bytes.                      */
                                /* In case of passthru mailbox, the      */
                                /* caller fills in the data size in the  */
                                /* first BDE location of the payload     */
                                /* buffer.                               */
};
#endif /* _KERNEL */

/*
  structure passed by pointer to SCIOLEVENT ioctl of adapter driver
*/


struct	scsi_event_struct {
	ushort version;		 /* The version number of this           */
				 /* structure.  This allows the          */
				 /* structure to expand in the           */
				 /* future.                              */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */
	ushort autosense_length; /* This specifies the maximum size      */
				 /* in bytes of the SCSI heads auto-     */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	uchar add_device_status; /* Additional device status.            */
				 /* For FCP devices, this field          */
				 /* contains the FCP response code.      */
			
	uchar  adap_set_flags;   /* These flags are set by the SCSI      */
				 /* adapter driver when a command        */
				 /* is returned.			 */
	ushort add_adap_status;  /* Additional adapter status	         */


	/******  8 byte boundary ********/

	char *autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer.	                 */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

#if defined(__ia64) && !defined(__64BIT__)
	uchar pad1[4];		/* Padding for IA64 ILP32 mode */
#endif
	/******  8 byte boundary ********/
	unsigned long long scsi_id;/* target/initiator SCSI ID being     */
				 /* registered                           */
	/******  8 byte boundary ********/
	unsigned long long lun_id;/* target/initiator lun ID being       */
				/* registered                            */
	/******  8 byte boundary ********/
	uchar	mode;		/* indicate if ID is for target or initiator */
#define	SCSI_IM_MODE	0	/* this is an initiator mode ID          */
#define	SCSI_TM_MODE	1	/* this is a target mode ID              */

#if defined(__ia64) && !defined(__64BIT__)
	uchar pad2[7];		/* Padding for IA64 ILP32 mode */
#endif
	/******  8 byte boundary ********/
	unsigned long long async_correlator; /* optional field for use by 
                                           caller. Value in this field 
					   is saved by adapter driver
                                           and passed back to caller's 
                                           async func */
	void	(*async_func)();	/* device drivers's asynchronous
                                           event handler function address */

                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
};


#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI transmit payload (SCIOLPAYLD) structure passed by pointer to 
 * ioctl of adapter driver.
 *
 * This structure is used internally by the adapter driver for support
 * of 64-bit applications.
 */
struct	scsi_event_structv0 {
	ushort version;		 /* The version number of this           */
				 /* structure.  This allows the          */
				 /* structure to expand in the           */
				 /* future.                              */
	ushort autosense_length; /* This specifies the maximum size      */
				 /* in bytes of the SCSI heads auto-     */
				 /* sense buffer referenced by the       */
				 /* autosense_buffer_ptr field.	         */
	uchar add_device_status; /* Additional device status.            */
				 /* For FCP devices, this field          */
				 /* contains the FCP response code.      */
			
	uchar  adap_set_flags;   /* These flags are set by the SCSI      */
				 /* adapter driver when a command        */
				 /* is returned.			 */
	ushort add_adap_status;  /* Additional adapter status	         */


	/******  8 byte boundary ********/

	char *autosense_buffer_ptr;/* A pointer to the SCSI head's       */
				 /* autosense buffer.	                 */
				 /* NOTE: if this is NULL and the        */
				 /* SCSI device returns autosense,       */
				 /* then the adapter driver will 	 */
				 /* throw away the autosense data.	 */

#if defined(__ia64) && !defined(__64BIT__)
	uchar pad1[4];		/* Padding for IA64 ILP32 mode */
#endif
	/******  8 byte boundary ********/
	unsigned long long scsi_id;/* target/initiator SCSI ID being     */
				 /* registered                           */
	/******  8 byte boundary ********/
	unsigned long long lun_id;/* target/initiator lun ID being       */
				/* registered                            */
	/******  8 byte boundary ********/
	uchar	mode;		/* indicate if ID is for target or initiator */
#define	SCSI_IM_MODE	0	/* this is an initiator mode ID          */
#define	SCSI_TM_MODE	1	/* this is a target mode ID              */

#if defined(__ia64) && !defined(__64BIT__)
	uchar pad2[7];		/* Padding for IA64 ILP32 mode */
#endif
	/******  8 byte boundary ********/
	unsigned long long async_correlator; /* optional field for use by 
                                           caller. Value in this field 
					   is saved by adapter driver
                                           and passed back to caller's 
                                           async func */
	void	(*async_func)();	/* device drivers's asynchronous
                                           event handler function address */

};
#endif /* _KERNEL */


/*
 * structure passed by adapter driver to the device driver's async func
 */

struct	scsi_event_info {
	ushort version;		/* The version number of this            */
				/* structure.  This allows the           */
				/* structure to expand in the            */
				/* future.                               */
/*  For this structure the version field MUST have a value of            */
/*  SCSI_VERSION_1                                                       */

	uchar	mode;		/* indicate if ID is for target or initiator
                                   see possible values in scsi_event_struct */

	int	events;		/* event being reported                 */
#define	SCSI_FATAL_HDW_ERR	0x01
				/* adapter fatal hardware failure       */
#define	SCSI_ADAP_CMD_FAILED	0x02
				/* unrecoverable adapter cmd failure    */
#define	SCSI_RESET_EVENT	0x04
				/* SCSI bus reset detected              */
#define	SCSI_BUFS_EXHAUSTED	0x08
				/* maximum buffer usage detected        */
				/* maximum buffer usage detected        */

	dev_t	adap_devno;	/* device major/minor number of adapter */
                                /* reporting this async event information*/

	unsigned long long async_correlator; /* this value is a copy of */
                                 /* the field of the same name passed   */
                                 /* by the caller in the                */
				 /* scsi_event_struct                   */

	unsigned long long scsi_id;/* This is the 64-bit SCSI ID for     */
				 /* the device.			         */

	unsigned long long lun_id;/* This is the 64-bit lun ID for       */
				 /* the device.			         */
                                      /* The target's world wide name    */
	unsigned long long world_wide_name;   

				      /* The target's node name          */
	unsigned long long node_name; 
};


/*
  Definitions for SCSI device driver to application level tasks.
  */

/*
  SCSI Read/Write with Sense Ioctl Structure
  */

struct scsi_rdwrt {
	char	*buffer;		/* Pointer to data transfer buffer */
	uchar   adap_q_status;		/* used to return back whether or  */
					/* or not the SCSI adapter driver  */
					/* and SCSI adapter cleared their  */
					/* queue for this device or not.   */
					/* A value of zero implies that    */
					/* the device's queue at the       */ 
					/* adapter is cleared.             */
					/* A value of SC_DID_NOT_CLEAR_Q,  */
					/* defined in sc_buf, implies that */
					/* the device's queue at the       */
					/* adapter has not be cleared.	   */
        uchar   status_validity;	/* 0 = no valid status           */
	/* SC_SCSI_ERROR and SC_ADAPTER_ERROR defined in sc_buf
	   1 = valid SCSI bus status only
	   2 = valid adapter status only    
           4 = valid sense data.    */
	uchar	scsi_bus_status;	/* SCSI bus status */
	uchar	adapter_status;		/* Adapter return status, refer to 
					   sc_buf definition */
	/******  8 byte boundary ********/
	uchar   q_tag_msg;		/* Used to pass down Queue Tag     */
					/* message fields of SC_NO_Q,      */
					/* SC_SIMPLE_Q, SC_HEAD_OF_Q,      */
					/* SC_ORDERED_Q, or SC_ACA_Q,      */
					/* defined above in sc_buf's       */
					/* definition.		           */

	uchar   q_flags;		/* Used to tell the SCSI adapter   */
					/* driver, and SCSI adapter whether*/
					/* or not it should clear or resume*/
					/* its queue. This is done via the */
				        /* defines SC_Q_CLR, SC_Q_RESUME   */
				        /* or SC_CLEAR_ACA defined above in*/
				        /* sc_buf.        	           */
	uchar	req_sense_length;	/* Length of request sense data buffer
					   in bytes */
	uint	timeout_value;		/* Timeout value for the command, 
					   in seconds */
	/******  8 byte boundary ********/
	char	*request_sense_ptr;	/* Pointer to request sense buffer */
#if defined(__ia64) && !defined(__64BIT__)
	uchar pad[4];		/* Padding for IA64 ILP32 mode */
#endif
	/******  8 byte boundary ********/
	unsigned long long logical_blk_addr;/* Logical block address       */
					/*  (0 for sequential devices)     */
	/******  8 byte boundary ********/
	unsigned long long data_length;	/* Data transfer length in bytes   */


};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * SCSI Read/Write with Sense Ioctl Structure used internally by device driver 
 * to support 64-bit applications
 */


struct scsi_rdwrt64 {
	ptr64   buffer;                 /* Pointer to data transfer buffer */
	uchar   adap_q_status;		/* used to return back whether or  */
					/* or not the SCSI adapter driver  */
					/* and SCSI adapter cleared their  */
					/* queue for this device or not.   */
					/* A value of zero implies that    */
					/* the device's queue at the       */ 
					/* adapter is cleared.             */
					/* A value of SC_DID_NOT_CLEAR_Q,  */
					/* defined in sc_buf, implies that */
					/* the device's queue at the       */
					/* adapter has not be cleared.	   */
        uchar   status_validity;	/* See sc_rdwrt64 for defines.     */
	/* SC_SCSI_ERROR and SC_ADAPTER_ERROR defined in sc_buf
	   1 = valid SCSI bus status only
	   2 = valid adapter status only        */

	uchar	scsi_bus_status;	/* SCSI bus status                 */
	uchar	adapter_status;		/* Adapter return status, refer to 
					   sc_buf definition */
	uchar   q_tag_msg;		/* Used to pass down Queue Tag     */
					/* message fields of SC_NO_Q,      */
					/* SC_SIMPLE_Q, SC_HEAD_OF_Q,      */
					/* SC_ORDERED_Q, or SC_ACA_Q,      */
					/* defined above in sc_buf's       */
					/* definition.		           */

	uchar   q_flags;		/* Used to tell the SCSI adapter   */
					/* driver, and SCSI adapter whether*/
					/* or not it should clear or resume*/
					/* its queue. This is done via the */
				        /* defines SC_Q_CLR, SC_Q_RESUME   */
				        /* or SC_CLEAR_ACA defined above in*/
				        /* sc_buf.        	           */
	uchar	req_sense_length;	/* Length of request sense data buffer
					   in bytes */
	uint	timeout_value;		/* Timeout value for the command, 
					   in seconds */
	ptr64   request_sense_ptr;	/* Pointer to request sense buffer */
	unsigned long long logical_blk_addr;/* Logical block address       */
					/*  (0 for sequential devices)     */
	unsigned long long data_length;	/* Data transfer length in bytes   */

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * This structure is used internally by the adapter driver for support
 * 32-bit applications by 64-bit kernel extensions. 
 */

struct scsi_rdwrt32 {
	ptr32   buffer;                 /* Pointer to data transfer buffer */
	uchar   adap_q_status;		/* used to return back whether or  */
					/* or not the SCSI adapter driver  */
					/* and SCSI adapter cleared their  */
					/* queue for this device or not.   */
					/* A value of zero implies that    */
					/* the device's queue at the       */ 
					/* adapter is cleared.             */
					/* A value of SC_DID_NOT_CLEAR_Q,  */
					/* defined in sc_buf, implies that */
					/* the device's queue at the       */
					/* adapter has not be cleared.	   */
        uchar   status_validity;	/* See sc_rdwrt64 for defines.     */
	/* SC_SCSI_ERROR and SC_ADAPTER_ERROR defined in sc_buf
	   1 = valid SCSI bus status only
	   2 = valid adapter status only        */

	uchar	scsi_bus_status;	/* SCSI bus status                 */
	uchar	adapter_status;		/* Adapter return status, refer to 
					   sc_buf definition */
	uchar   q_tag_msg;		/* Used to pass down Queue Tag     */
					/* message fields of SC_NO_Q,      */
					/* SC_SIMPLE_Q, SC_HEAD_OF_Q,      */
					/* SC_ORDERED_Q, or SC_ACA_Q,      */
					/* defined above in sc_buf's       */
					/* definition.		           */

	uchar   q_flags;		/* Used to tell the SCSI adapter   */
					/* driver, and SCSI adapter whether*/
					/* or not it should clear or resume*/
					/* its queue. This is done via the */
				        /* defines SC_Q_CLR, SC_Q_RESUME   */
				        /* or SC_CLEAR_ACA defined above in*/
				        /* sc_buf.        	           */
	uchar	req_sense_length;	/* Length of request sense data buffer
					   in bytes */
	uint	timeout_value;		/* Timeout value for the command, 
					   in seconds */
	ptr32   request_sense_ptr;	/* Pointer to request sense buffer */
	unsigned long long logical_blk_addr;/* Logical block address       */
					/*  (0 for sequential devices)     */
	unsigned long long data_length;	/* Data transfer length in bytes   */

};


#endif /* KERNEL */

/*
 * Pass-thru SCSI command structure passed by pointer to ioctl of 
 * the SCSI adapter driver.
 */

struct scsi_iocmd {
	ushort version;		     /* The version number of this      */
				     /* structure.  This allows the     */
				     /* structure to expand in the      */
				     /* future.                         */
/*  For this structure the version field MUST have a value of           */
/*  SCSI_VERSION_2                                                      */

        char   *buffer;              /* Pointer to transfer data buffer */
        uint   timeout_value;        /* In seconds 			*/
        uchar  status_validity;      /* 0 = no valid status 		*/

	/* 1 = valid SCSI bus status only       */
	/* 2 = valid adapter status only        */

        uchar  scsi_bus_status;      /* SCSI bus status (if valid) 	*/
        uchar  adapter_status;       /* Adapter status (if valid), refer*/
				     /* to scsi_buf definition 		*/
	uchar  adap_set_flags;       /* These flags are set by the SCSI */
				     /* adapter driver when a command is*/
				     /* returned. See scsi_buf          */
				     /* for valid values		*/ 

	uchar  add_device_status;    /* Additional device status.       */
				     /* For FCP devices, this field     */
				     /* contains the FCP response code. */
			
	uchar  adap_q_status;        /* used to return back whether or  */
				     /* or not the SCSI adapter driver  */
				     /* and SCSI adapter cleared their  */
				     /* queue for this device or not.   */
				     /* A value of zero implies that    */
				     /* the device's queue at the       */ 
				     /* adapter is cleared.             */
				     /* A value of SCSI_DID_NOT_CLEAR_Q,*/
				     /* defined in scsi_buf, implies that*/
				     /* the device's queue at the       */
				     /* adapter has not be cleared.	*/
	uchar  q_tag_msg;	     /* Used to pass down Queue Tag     */
				     /* message fields of SCSI_NO_Q,    */
				     /* SCSI_SIMPLE, SCSI_HEAD_OF_Q, 	*/
				     /* SCSI_ORDERED_Q, or SCSI_ACA_Q,  */
				     /* defined above in scsi_buf's     */
				     /* definition.		        */
        uchar  flags;                /* B_READ, B_WRITE. See scsi.h     */
	uchar  q_flags;		     /* Used to tell the SCSI adapter   */
				     /* driver, and SCSI adapter whether*/
				     /* or not it should clear or resume*/
				     /* its queue. This is done via the */
				     /* defines SCSI_Q_CLR, SCSI_Q_RESUME,*/
				     /* or SCSI_CLEAR_ACA defined above */
				     /* in scsi_buf.        		*/

	ushort autosense_length;     /* This specifies the maximum size */
				     /* in bytes of the SCSI heads auto-*/
				     /* sense buffer referenced by the  */
				     /* autosense_buffer_ptr field.	*/

        uchar  command_length;       /* Length of SCSI command block 	*/
        uchar  scsi_cdb[16];         /* SCSI command descriptor block 	*/


	char   *autosense_buffer_ptr;/* A pointer to the SCSI head's    */
				     /* autosense buffer for this SCSI	*/
				     /* command.			*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns autosense,  */
				     /* then the adapter driver will 	*/
				     /* throw away the autosense data.	*/

        unsigned long long data_length;/* Bytes of data to be transfered*/
	unsigned long long  scsi_id; /* This is the 64-bit SCSI ID for  */
				     /* the device.			*/

	unsigned long long  lun_id;  /* This is the 64-bit lun ID for   */
				     /* the device.			*/

                                      /* The target's world wide name   */
	unsigned long long world_wide_name;   

				      /* The target's node name         */
	unsigned long long node_name;

        uint variable_cdb_length;    /* length of variable cdb referring */
                                     /* to the variable_cdb_ptr.         */

        char *variable_cdb_ptr;      /* pointer to a buffer which holds  */
                                     /* the variable SCSI cdb.           */

        unsigned long long residual;  /* bytes not xferred after error.  */

};

#ifdef _KERNEL
/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * 
 * Pass-thru SCSI version 0 command structure passed by pointer to ioctl of 
 * the SCSI adapter driver.  This structure is used internally by 
 * the adapter driver for support 64-bit applications.
 */

struct scsi_iocmd64v0 {
	ushort version;		     /* The version number of this      */
				     /* structure.  This allows the     */
				     /* structure to expand in the      */
				     /* future.                         */
/*  For this structure the version field MUST have a value of           */
/*  SCSI_VERSION_0                                                      */


        ptr64  buffer;               /* Pointer to transfer data buffer */
        uint   timeout_value;        /* In seconds 			*/
        uchar  status_validity;      /* 0 = no valid status 		*/

	/* 1 = valid SCSI bus status only       */
	/* 2 = valid adapter status only        */

        uchar  scsi_bus_status;      /* SCSI bus status (if valid) 	*/
        uchar  adapter_status;       /* Adapter status (if valid), refer*/
				     /* to scsi_buf definition 		*/
	uchar  adap_set_flags;       /* These flags are set by the SCSI */
				     /* adapter driver when a command is*/
				     /* returned. See scsi_buf          */
				     /* for valid values		*/ 

	uchar  add_device_status;    /* Additional device status.       */
				     /* For FCP devices, this field     */
				     /* contains the FCP response code. */
			
	uchar  adap_q_status;        /* used to return back whether or  */
				     /* or not the SCSI adapter driver  */
				     /* and SCSI adapter cleared their  */
				     /* queue for this device or not.   */
				     /* A value of zero implies that    */
				     /* the device's queue at the       */ 
				     /* adapter is cleared.             */
				     /* A value of SCSI_DID_NOT_CLEAR_Q,*/
				     /* defined in scsi_buf, implies that*/
				     /* the device's queue at the       */
				     /* adapter has not be cleared.	*/
	uchar  q_tag_msg;	     /* Used to pass down Queue Tag     */
				     /* message fields of SCSI_NO_Q,    */
				     /* SCSI_SIMPLE, SCSI_HEAD_OF_Q, 	*/
				     /* SCSI_ORDERED_Q, or SCSI_ACA_Q,  */
				     /* defined above in scsi_buf's     */
				     /* definition.		        */
        uchar  flags;                /* B_READ, B_WRITE. See scsi.h     */
	uchar  q_flags;		     /* Used to tell the SCSI adapter   */
				     /* driver, and SCSI adapter whether*/
				     /* or not it should clear or resume*/
				     /* its queue. This is done via the */
				     /* defines SCSI_Q_CLR, SCSI_Q_RESUME,*/
				     /* or SCSI_CLEAR_ACA defined above */
				     /* in scsi_buf.        		*/

	ushort autosense_length;     /* This specifies the maximum size */
				     /* in bytes of the SCSI heads auto-*/
				     /* sense buffer referenced by the  */
				     /* autosense_buffer_ptr field.	*/

        uchar  command_length;       /* Length of SCSI command block 	*/
        uchar  scsi_cdb[16];         /* SCSI command descriptor block 	*/


	ptr64 autosense_buffer_ptr;  /* A pointer to the SCSI head's    */
				     /* autosense buffer for this SCSI	*/
				     /* command.			*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns autosense,  */
				     /* then the adapter driver will 	*/
				     /* throw away the autosense data.	*/

        unsigned long long data_length;/* Bytes of data to be transfered*/
	unsigned long long  scsi_id; /* This is the 64-bit SCSI ID for  */
				     /* the device.			*/

	unsigned long long  lun_id;  /* This is the 64-bit lun ID for   */
				     /* the device.			*/
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * 
 * Pass-thru SCSI command version 0 structure passed by pointer to ioctl of 
 * the SCSI adapter driver. This structure is used internally by 
 * the adapter driver for support 32-bit applications by 64-bit kernel 
 * extensions.
 */

struct scsi_iocmd32v0 {
	ushort version;		     /* The version number of this      */
				     /* structure.  This allows the     */
				     /* structure to expand in the      */
				     /* future.                         */
/*  For this structure the version field MUST have a value of           */
/*  SCSI_VERSION_0                                                      */


        ptr32  buffer;               /* Pointer to transfer data buffer */
        uint   timeout_value;        /* In seconds 			*/
        uchar  status_validity;      /* 0 = no valid status 		*/

	/* 1 = valid SCSI bus status only       */
	/* 2 = valid adapter status only        */

        uchar  scsi_bus_status;      /* SCSI bus status (if valid) 	*/
        uchar  adapter_status;       /* Adapter status (if valid), refer*/
				     /* to scsi_buf definition 		*/
	uchar  adap_set_flags;       /* These flags are set by the SCSI */
				     /* adapter driver when a command is*/
				     /* returned. See scsi_buf          */
				     /* for valid values		*/ 

	uchar  add_device_status;    /* Additional device status.       */
				     /* For FCP devices, this field     */
				     /* contains the FCP response code. */
			
	uchar  adap_q_status;        /* used to return back whether or  */
				     /* or not the SCSI adapter driver  */
				     /* and SCSI adapter cleared their  */
				     /* queue for this device or not.   */
				     /* A value of zero implies that    */
				     /* the device's queue at the       */ 
				     /* adapter is cleared.             */
				     /* A value of SCSI_DID_NOT_CLEAR_Q,*/
				     /* defined in scsi_buf, implies that*/
				     /* the device's queue at the       */
				     /* adapter has not be cleared.	*/
	uchar  q_tag_msg;	     /* Used to pass down Queue Tag     */
				     /* message fields of SCSI_NO_Q,    */
				     /* SCSI_SIMPLE, SCSI_HEAD_OF_Q, 	*/
				     /* SCSI_ORDERED_Q, or SCSI_ACA_Q,  */
				     /* defined above in scsi_buf's     */
				     /* definition.		        */
        uchar  flags;                /* B_READ, B_WRITE. See scsi.h     */
	uchar  q_flags;		     /* Used to tell the SCSI adapter   */
				     /* driver, and SCSI adapter whether*/
				     /* or not it should clear or resume*/
				     /* its queue. This is done via the */
				     /* defines SCSI_Q_CLR, SCSI_Q_RESUME,*/
				     /* or SCSI_CLEAR_ACA defined above */
				     /* in scsi_buf.        		*/

	ushort autosense_length;     /* This specifies the maximum size */
				     /* in bytes of the SCSI heads auto-*/
				     /* sense buffer referenced by the  */
				     /* autosense_buffer_ptr field.	*/

        uchar  command_length;       /* Length of SCSI command block 	*/
        uchar  scsi_cdb[16];         /* SCSI command descriptor block 	*/


	ptr32 autosense_buffer_ptr;  /* A pointer to the SCSI head's    */
				     /* autosense buffer for this SCSI	*/
				     /* command.			*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns autosense,  */
				     /* then the adapter driver will 	*/
				     /* throw away the autosense data.	*/

        unsigned long long data_length;/* Bytes of data to be transfered*/
	unsigned long long  scsi_id; /* This is the 64-bit SCSI ID for  */
				     /* the device.			*/

	unsigned long long  lun_id;  /* This is the 64-bit lun ID for   */
				     /* the device.			*/
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * 
 * Pass-thru SCSI command version 1 structure passed by pointer to ioctl of 
 * the SCSI adapter driver.  This structure is used internally by 
 * the adapter driver for support 64-bit applications.
 */

struct scsi_iocmd64v1 {
	ushort version;		     /* The version number of this      */
				     /* structure.  This allows the     */
				     /* structure to expand in the      */
				     /* future.                         */
/*  For this structure the version field MUST have a value of           */
/*  SCSI_VERSION_1                                                      */


        ptr64  buffer;               /* Pointer to transfer data buffer */
        uint   timeout_value;        /* In seconds 			*/
        uchar  status_validity;      /* 0 = no valid status 		*/

	/* 1 = valid SCSI bus status only       */
	/* 2 = valid adapter status only        */

        uchar  scsi_bus_status;      /* SCSI bus status (if valid) 	*/
        uchar  adapter_status;       /* Adapter status (if valid), refer*/
				     /* to scsi_buf definition 		*/
	uchar  adap_set_flags;       /* These flags are set by the SCSI */
				     /* adapter driver when a command is*/
				     /* returned. See scsi_buf          */
				     /* for valid values		*/ 

	uchar  add_device_status;    /* Additional device status.       */
				     /* For FCP devices, this field     */
				     /* contains the FCP response code. */
			
	uchar  adap_q_status;        /* used to return back whether or  */
				     /* or not the SCSI adapter driver  */
				     /* and SCSI adapter cleared their  */
				     /* queue for this device or not.   */
				     /* A value of zero implies that    */
				     /* the device's queue at the       */ 
				     /* adapter is cleared.             */
				     /* A value of SCSI_DID_NOT_CLEAR_Q,*/
				     /* defined in scsi_buf, implies that*/
				     /* the device's queue at the       */
				     /* adapter has not be cleared.	*/
	uchar  q_tag_msg;	     /* Used to pass down Queue Tag     */
				     /* message fields of SCSI_NO_Q,    */
				     /* SCSI_SIMPLE, SCSI_HEAD_OF_Q, 	*/
				     /* SCSI_ORDERED_Q, or SCSI_ACA_Q,  */
				     /* defined above in scsi_buf's     */
				     /* definition.		        */
        uchar  flags;                /* B_READ, B_WRITE. See scsi.h     */
	uchar  q_flags;		     /* Used to tell the SCSI adapter   */
				     /* driver, and SCSI adapter whether*/
				     /* or not it should clear or resume*/
				     /* its queue. This is done via the */
				     /* defines SCSI_Q_CLR, SCSI_Q_RESUME,*/
				     /* or SCSI_CLEAR_ACA defined above */
				     /* in scsi_buf.        		*/

	ushort autosense_length;     /* This specifies the maximum size */
				     /* in bytes of the SCSI heads auto-*/
				     /* sense buffer referenced by the  */
				     /* autosense_buffer_ptr field.	*/

        uchar  command_length;       /* Length of SCSI command block 	*/
        uchar  scsi_cdb[16];         /* SCSI command descriptor block 	*/


	ptr64 autosense_buffer_ptr;  /* A pointer to the SCSI head's    */
				     /* autosense buffer for this SCSI	*/
				     /* command.			*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns autosense,  */
				     /* then the adapter driver will 	*/
				     /* throw away the autosense data.	*/

        unsigned long long data_length;/* Bytes of data to be transfered*/
	unsigned long long  scsi_id; /* This is the 64-bit SCSI ID for  */
				     /* the device.			*/

	unsigned long long  lun_id;  /* This is the 64-bit lun ID for   */
				     /* the device.			*/

                                      /* The target's world wide name   */
	unsigned long long world_wide_name;   

				      /* The target's node name         */
	unsigned long long node_name; 
     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * 
 * Pass-thru SCSI command structure version 1 passed by pointer to ioctl of 
 * the SCSI adapter driver. This structure is used internally by 
 * the adapter driver for support 32-bit applications by 64-bit kernel 
 * extensions.
 */

struct scsi_iocmd32v1 {
	ushort version;		     /* The version number of this      */
				     /* structure.  This allows the     */
				     /* structure to expand in the      */
				     /* future.                         */
/*  For this structure the version field MUST have a value of           */
/*  SCSI_VERSION_1                                                      */


        ptr32  buffer;               /* Pointer to transfer data buffer */
        uint   timeout_value;        /* In seconds 			*/
        uchar  status_validity;      /* 0 = no valid status 		*/

	/* 1 = valid SCSI bus status only       */
	/* 2 = valid adapter status only        */

        uchar  scsi_bus_status;      /* SCSI bus status (if valid) 	*/
        uchar  adapter_status;       /* Adapter status (if valid), refer*/
				     /* to scsi_buf definition 		*/
	uchar  adap_set_flags;       /* These flags are set by the SCSI */
				     /* adapter driver when a command is*/
				     /* returned. See scsi_buf          */
				     /* for valid values		*/ 

	uchar  add_device_status;    /* Additional device status.       */
				     /* For FCP devices, this field     */
				     /* contains the FCP response code. */
			
	uchar  adap_q_status;        /* used to return back whether or  */
				     /* or not the SCSI adapter driver  */
				     /* and SCSI adapter cleared their  */
				     /* queue for this device or not.   */
				     /* A value of zero implies that    */
				     /* the device's queue at the       */ 
				     /* adapter is cleared.             */
				     /* A value of SCSI_DID_NOT_CLEAR_Q,*/
				     /* defined in scsi_buf, implies that*/
				     /* the device's queue at the       */
				     /* adapter has not be cleared.	*/
	uchar  q_tag_msg;	     /* Used to pass down Queue Tag     */
				     /* message fields of SCSI_NO_Q,    */
				     /* SCSI_SIMPLE, SCSI_HEAD_OF_Q, 	*/
				     /* SCSI_ORDERED_Q, or SCSI_ACA_Q,  */
				     /* defined above in scsi_buf's     */
				     /* definition.		        */
        uchar  flags;                /* B_READ, B_WRITE. See scsi.h     */
	uchar  q_flags;		     /* Used to tell the SCSI adapter   */
				     /* driver, and SCSI adapter whether*/
				     /* or not it should clear or resume*/
				     /* its queue. This is done via the */
				     /* defines SCSI_Q_CLR, SCSI_Q_RESUME,*/
				     /* or SCSI_CLEAR_ACA defined above */
				     /* in scsi_buf.        		*/

	ushort autosense_length;     /* This specifies the maximum size */
				     /* in bytes of the SCSI heads auto-*/
				     /* sense buffer referenced by the  */
				     /* autosense_buffer_ptr field.	*/

        uchar  command_length;       /* Length of SCSI command block 	*/
        uchar  scsi_cdb[16];         /* SCSI command descriptor block 	*/


	ptr32 autosense_buffer_ptr;  /* A pointer to the SCSI head's    */
				     /* autosense buffer for this SCSI	*/
				     /* command.			*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns autosense,  */
				     /* then the adapter driver will 	*/
				     /* throw away the autosense data.	*/

        unsigned long long data_length;/* Bytes of data to be transfered*/
	unsigned long long  scsi_id; /* This is the 64-bit SCSI ID for  */
				     /* the device.			*/

	unsigned long long  lun_id;  /* This is the 64-bit lun ID for   */
				     /* the device.			*/

                                      /* The target's world wide name   */
	unsigned long long world_wide_name;   

				      /* The target's node name         */
	unsigned long long node_name; 
     	     

};



/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * 
 * Pass-thru SCSI command version 2 structure passed by pointer to ioctl of 
 * the SCSI adapter driver.  This structure is used internally by 
 * the adapter driver for support 64-bit applications.
 */

struct scsi_iocmd64 {
	ushort version;		     /* The version number of this      */
				     /* structure.  This allows the     */
				     /* structure to expand in the      */
				     /* future.                         */
/*  For this structure the version field MUST have a value of           */
/*  SCSI_VERSION_2                                                      */


        ptr64  buffer;               /* Pointer to transfer data buffer */
        uint   timeout_value;        /* In seconds 			*/
        uchar  status_validity;      /* 0 = no valid status 		*/

	/* 1 = valid SCSI bus status only       */
	/* 2 = valid adapter status only        */

        uchar  scsi_bus_status;      /* SCSI bus status (if valid) 	*/
        uchar  adapter_status;       /* Adapter status (if valid), refer*/
				     /* to scsi_buf definition 		*/
	uchar  adap_set_flags;       /* These flags are set by the SCSI */
				     /* adapter driver when a command is*/
				     /* returned. See scsi_buf          */
				     /* for valid values		*/ 

	uchar  add_device_status;    /* Additional device status.       */
				     /* For FCP devices, this field     */
				     /* contains the FCP response code. */
			
	uchar  adap_q_status;        /* used to return back whether or  */
				     /* or not the SCSI adapter driver  */
				     /* and SCSI adapter cleared their  */
				     /* queue for this device or not.   */
				     /* A value of zero implies that    */
				     /* the device's queue at the       */ 
				     /* adapter is cleared.             */
				     /* A value of SCSI_DID_NOT_CLEAR_Q,*/
				     /* defined in scsi_buf, implies that*/
				     /* the device's queue at the       */
				     /* adapter has not be cleared.	*/
	uchar  q_tag_msg;	     /* Used to pass down Queue Tag     */
				     /* message fields of SCSI_NO_Q,    */
				     /* SCSI_SIMPLE, SCSI_HEAD_OF_Q, 	*/
				     /* SCSI_ORDERED_Q, or SCSI_ACA_Q,  */
				     /* defined above in scsi_buf's     */
				     /* definition.		        */
        uchar  flags;                /* B_READ, B_WRITE. See scsi.h     */
	uchar  q_flags;		     /* Used to tell the SCSI adapter   */
				     /* driver, and SCSI adapter whether*/
				     /* or not it should clear or resume*/
				     /* its queue. This is done via the */
				     /* defines SCSI_Q_CLR, SCSI_Q_RESUME,*/
				     /* or SCSI_CLEAR_ACA defined above */
				     /* in scsi_buf.        		*/

	ushort autosense_length;     /* This specifies the maximum size */
				     /* in bytes of the SCSI heads auto-*/
				     /* sense buffer referenced by the  */
				     /* autosense_buffer_ptr field.	*/

        uchar  command_length;       /* Length of SCSI command block 	*/
        uchar  scsi_cdb[16];         /* SCSI command descriptor block 	*/

	ptr64 autosense_buffer_ptr;  /* A pointer to the SCSI head's    */
				     /* autosense buffer for this SCSI	*/
				     /* command.			*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns autosense,  */
				     /* then the adapter driver will 	*/
				     /* throw away the autosense data.	*/

        unsigned long long data_length;/* Bytes of data to be transfered*/
	unsigned long long  scsi_id; /* This is the 64-bit SCSI ID for  */
				     /* the device.			*/

	unsigned long long  lun_id;  /* This is the 64-bit lun ID for   */
				     /* the device.			*/

                                      /* The target's world wide name   */
	unsigned long long world_wide_name;   

				      /* The target's node name         */
	unsigned long long node_name; 

        uint variable_cdb_length;    /* length of variable cdb referring */
                                     /* to the variable_cdb_ptr.         */

        ptr64 variable_cdb_ptr;      /* pointer to a buffer which holds  */
                                     /* the variable SCSI cdb.           */

        unsigned long long residual; /* bytes not xferred after error.   */     	     

};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * 
 * Pass-thru SCSI command structure version 2 passed by pointer to ioctl of 
 * the SCSI adapter driver. This structure is used internally by 
 * the adapter driver for support 32-bit applications by 64-bit kernel 
 * extensions.
 */

struct scsi_iocmd32 {
	ushort version;		     /* The version number of this      */
				     /* structure.  This allows the     */
				     /* structure to expand in the      */
				     /* future.                         */
/*  For this structure the version field MUST have a value of           */
/*  SCSI_VERSION_2                                                      */


        ptr32  buffer;               /* Pointer to transfer data buffer */
        uint   timeout_value;        /* In seconds 			*/
        uchar  status_validity;      /* 0 = no valid status 		*/

	/* 1 = valid SCSI bus status only       */
	/* 2 = valid adapter status only        */

        uchar  scsi_bus_status;      /* SCSI bus status (if valid) 	*/
        uchar  adapter_status;       /* Adapter status (if valid), refer*/
				     /* to scsi_buf definition 		*/
	uchar  adap_set_flags;       /* These flags are set by the SCSI */
				     /* adapter driver when a command is*/
				     /* returned. See scsi_buf          */
				     /* for valid values		*/ 

	uchar  add_device_status;    /* Additional device status.       */
				     /* For FCP devices, this field     */
				     /* contains the FCP response code. */
			
	uchar  adap_q_status;        /* used to return back whether or  */
				     /* or not the SCSI adapter driver  */
				     /* and SCSI adapter cleared their  */
				     /* queue for this device or not.   */
				     /* A value of zero implies that    */
				     /* the device's queue at the       */ 
				     /* adapter is cleared.             */
				     /* A value of SCSI_DID_NOT_CLEAR_Q,*/
				     /* defined in scsi_buf, implies that*/
				     /* the device's queue at the       */
				     /* adapter has not be cleared.	*/
	uchar  q_tag_msg;	     /* Used to pass down Queue Tag     */
				     /* message fields of SCSI_NO_Q,    */
				     /* SCSI_SIMPLE, SCSI_HEAD_OF_Q, 	*/
				     /* SCSI_ORDERED_Q, or SCSI_ACA_Q,  */
				     /* defined above in scsi_buf's     */
				     /* definition.		        */
        uchar  flags;                /* B_READ, B_WRITE. See scsi.h     */
	uchar  q_flags;		     /* Used to tell the SCSI adapter   */
				     /* driver, and SCSI adapter whether*/
				     /* or not it should clear or resume*/
				     /* its queue. This is done via the */
				     /* defines SCSI_Q_CLR, SCSI_Q_RESUME,*/
				     /* or SCSI_CLEAR_ACA defined above */
				     /* in scsi_buf.        		*/

	ushort autosense_length;     /* This specifies the maximum size */
				     /* in bytes of the SCSI heads auto-*/
				     /* sense buffer referenced by the  */
				     /* autosense_buffer_ptr field.	*/

        uchar  command_length;       /* Length of SCSI command block 	*/
        uchar  scsi_cdb[16];         /* SCSI command descriptor block 	*/

	ptr32 autosense_buffer_ptr;  /* A pointer to the SCSI head's    */
				     /* autosense buffer for this SCSI	*/
				     /* command.			*/
				     /* NOTE: if this is NULL and the   */
				     /* SCSI device returns autosense,  */
				     /* then the adapter driver will 	*/
				     /* throw away the autosense data.	*/

        unsigned long long data_length;/* Bytes of data to be transfered*/
	unsigned long long  scsi_id; /* This is the 64-bit SCSI ID for  */
				     /* the device.			*/

	unsigned long long  lun_id;  /* This is the 64-bit lun ID for   */
				     /* the device.			*/

                                      /* The target's world wide name   */
	unsigned long long world_wide_name;   

				      /* The target's node name         */
	unsigned long long node_name; 

        uint variable_cdb_length;    /* length of variable cdb referring */
                                     /* to the variable_cdb_ptr.         */

        ptr32 variable_cdb_ptr;      /* pointer to a buffer which holds  */
                                     /* the variable SCSI cdb.           */

        unsigned long long residual;  /* bytes not xferred after error.  */     	     

};

#endif

/*
  Diagnostic / Error Logging structure used by adapter driver
  */

struct elog_cdb {
    unsigned long long	   lun;		/* Lun ID			     */
    uint                   fcp_cntl;	/* FCP control field		     */
    struct scsi_cdb        scsi_cmd_blk;/* 16 byte SCSI CDB		     */

    					/* transfer length		     */
    uint                   scsi_data_length;
};

#define EFSC_SIZE_OF_BDES   48   /* Size of reply array in error log*/

#define EFSC_SIZE_OF_RPLY   40  /* Size of reply array in error log*/
struct  scsi_rc  {            	/* adapter return code area     */

        uint    errnum;	        /* 4 bytes = unique error num.  */
	uint output_rc;		/* Return code from failed call */
				/* to output or control routine */
				/* of adapter driver.		*/

	uchar   conn_type;      /* How the adapter is connected */
/* #define FC_CON_NONE   0x0 */
/* #define FC_CON_PT_PT  0x1 */
/* #define FC_CON_FABRIC 0x2 */  
/* #define FC_CON_AL     0x3 */ 

        uchar  flags;           /* flags for error log          */
#define FC_VIRT_ID     0x1      /* SCSI ID returned for adapter */
                                /* is for a virtual initiator   */
        uchar reserved[2];
	uint  status;           /* Status returned by adapter   */
				/* driver.                      */
	struct elog_cdb    cdb; /* Failing SCSI command.        */

        unsigned long long scsi_id;/*The SCSI id of this adapter*/
        unsigned long long dev_id;/*The SCSI id of device.      */

	unsigned int cmd_iocb[8]; /* IOCB that failed.          */
	unsigned int reply_iocb[8];/* Reply IOCB for this IOCB. */
	uchar bde_data[EFSC_SIZE_OF_BDES];
	uchar rply[EFSC_SIZE_OF_RPLY]; 
	unsigned long long scsi_struct;/* pointer to scsi_info struct  */

};

#define ERR_REQSNS_LEN      168         /* Length of error log sense    */
/*
  SCSI device driver error log record
*/
struct scsi_error_log_df {
	unsigned int error_id;		/* error type id */
	char	resource_name[ERR_NAMESIZE];	/* ddi resource name */
#ifdef MPIO
        ushort  path_id;                /* path id error occured on   */
#endif
	struct  scsi_cmd scsi_command;	/* command that caused error */
#ifdef MPIO
        uint    reserved1;              /* reserved for future use   */
        ushort  reserved2;              /* reserved for future use   */
#else
	ushort  reserved1;              /* reserved for future use   */
	uint    reserved2;              /* reserved for future use   */
#endif
	uchar	status_validity; 	/* least significant bit - scsi_status
					   valid, next least significant bit -
					   card status valid */
	uchar	scsi_status;            /* returned SCSI Bus status */
	uchar	adapter_status;         /* generic SCSI adapter card status
					   byte */
	uchar	reserved3;		/* reserved */
	uchar	req_sense_data[ERR_REQSNS_LEN];	/* request sense data */
	uint	dd1;		        /* reserved for dd use */
	uint	dd2;		        /* reserved for dd use */
	uint	dd3;		        /* reserved for dd use */
	uint	dd4;			/* reserved for dd use */
	uint	dd5;			/* reserved for dd use */
	uint	dd6;			/* reserved for dd use */
	uint	dd7;			/* reserved for dd use */
	uint	dd8;			/* reserved for dd use */
};

/*
  SCSI device driver error log record
*/
struct scsi_estruct {
#ifdef MPIO
        ushort   path_id;              /* path id error occured on   */
#endif
	struct scsi_cmd scsi_command;	/* command that caused error */
#ifdef MPIO
        uint    reserved1;              /* reserved for future use   */
        ushort  reserved2;              /* reserved for future use   */
#else
	ushort  reserved1;              /* reserved for future use   */
	uint    reserved2;              /* reserved for future use   */
#endif
	uchar	status_validity; 	/* least significant bit - scsi_status
					   valid, next least significant bit -
					   card status valid */
	uchar	scsi_status;            /* returned SCSI Bus status */
	uchar   adapter_status;         /* generic SCSI adapter card status
					   byte */
	uchar	reserved3;		/* reserved */
	uchar	req_sense_data[ERR_REQSNS_LEN];	/* request sense data */
	uint	dd1;		        /* reserved for dd use */
	uint	dd2;		        /* reserved for dd use */
	uint	dd3;		        /* reserved for dd use */
	uint	dd4;			/* reserved for dd use */
	uint	dd5;			/* reserved for dd use */
	uint	dd6;			/* reserved for dd use */
	uint    dd7;			/* reserved for dd use */
	uint	dd8;			/* reserved for dd use */

};

/*
 SCSI device driver initiator/target authentication information.
 This structure is intended to be used with the SCIOLAUTHSET ioctl.
*/
struct scsi_auth_info {

    ushort   version;                      /* Current struct version number */
                                           /* is SCSI_VERSION_0             */
    ushort   flags;                        /* Future use                    */

    union {

       struct {
            char     *iscsi_name;          /* iSCSI name                    */
            uint     iscsi_name_sz;        /* Size of iscsi_name string     */
            char     *host_addr;           /* User defined host address     */
                                           /* in character string form      */
            uint     host_addr_sz;         /* Size of host_addr string      */
            uint64_t port_num;             /* TCP port number               */ 
            uchar    auth_type;            /* Type of address               */
                                           /* Chap(MD5)type authentication  */
#define ISCSI_CHAP_5 0x1                            

            char     *data_I;              /* Initiator string data         */
            uint     data_I_sz;            /* Size of data_I                */
            char     *data_T;              /* Target string data            */
            uint     data_T_sz;            /* Size of data_T                */
            iscsi_ip_addr ip_addr;         /* Local host formed IP address  */
       } iscsi;

    } parms;
};

#ifdef _KERNEL
/*
 SCSI device driver initiator/target authentication information 32bit version
 This structure is intended to be used with the SCIOLAUTHSET ioctl.
*/
struct scsi_auth_info32 {

    ushort   version;                      /* Current struct version number */
                                           /* is SCSI_VERSION_0             */
    ushort   flags;                        /* Future use                    */

    union {

       struct {
            ptr32    iscsi_name;           /* iSCSI name                    */
            uint     iscsi_name_sz;        /* Size of iscsi_name string     */
            ptr32    host_addr;            /* User defined host address     */
                                           /* in character string form      */
            uint     host_addr_sz;         /* Size of host_addr string      */
            uint64_t port_num;             /* TCP port number               */
            uchar    auth_type;            /* Type of address               */

            ptr32    data_I;               /* Initiator string data         */
            uint     data_I_sz;            /* Size of data_I                */
            ptr32    data_T;               /* Target string data            */
            uint     data_T_sz;            /* Size of data_T                */
            iscsi_ip_addr ip_addr;         /* Local host formed IP address  */
       } iscsi;

    } parms;
};

/*
 SCSI device driver initiator/target authentication information 64bit version
 This structure is intended to be used with the SCIOLAUTHSET ioctl.
*/
struct scsi_auth_info64 {

    ushort   version;                      /* Current struct version number */
                                           /* is SCSI_VERSION_0             */
    ushort   flags;                        /* Future use                    */

    union {

       struct {
            ptr64    iscsi_name;           /* iSCSI name                    */
            uint     iscsi_name_sz;        /* Size of iscsi_name string     */
            ptr64    host_addr;            /* User defined host address     */
                                           /* in character string form      */
            uint     host_addr_sz;         /* Size of host_addr string      */
            uint64_t port_num;             /* TCP port number               */ 
            uchar    auth_type;            /* Type of address               */

            ptr64    data_I;               /* Initiator string data         */
            uint     data_I_sz;            /* Size of data_I                */
            ptr64    data_T;               /* Target string data            */
            uint     data_T_sz;            /* Size of data_T                */
            iscsi_ip_addr ip_addr;         /* Local host formed IP address  */
       } iscsi;

    } parms;
};


/*
  start target device structure passed by pointer to ioctl of adapter driver
*/
struct    scsi_strt_tgt {
    ushort          version;    /* The version number of this    */
                                /* structure.  This allows the   */
                                /* structure to expand in the    */
                                /* future.                       */

/*  For this structure the version field must have a value of    */
/*  SCSI_VERSION_0                                               */

    unsigned long long  scsi_id; /* SCSI ID of the SCSI initiator */
    unsigned long long  lun_id;  /* set to zero, as LUN ignored */
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
struct    scsi_stop_tgt {
    ushort          version;    /* The version number of this    */
                                /* structure.  This allows the   */
                                /* structure to expand in the    */
                                /* future.                       */

/*  For this structure the version field must have a value of    */
/*  SCSI_VERSION_0                                               */

    unsigned long long  scsi_id; /* SCSI ID of the SCSI initiator */
    unsigned long long  lun_id;  /* set to zero, as LUN ignored */
    __ulong64_t   resvd1;        /* reserved, should be set to zero */
    __ulong64_t   resvd2;        /* reserved, should be set to zero */
};

#endif /* _KERNEL */

#endif
