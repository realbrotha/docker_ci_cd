/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernel/sys/fcp.h 1.14                                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1995,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)70       1.14  src/bos/kernel/sys/fcp.h, sysxfcp, bos53J, j2006_33A7 8/9/06 12:25:40 */
#ifndef _H_FCP
#define _H_FCP
/*
 * COMPONENT_NAME: (SYSXFCP) IBM FC SCSI (FCP) Header File
 *
 * FUNCTIONS:	IBM SCSI-3 FCP (Fiber Channel Protocol) Header File.  
 *		This header is using FCP revision 12 (ANSI X3.269.199X).
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1995, 2000
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#include <sys/scsi_buf.h>

/*****************************************************************************/
/*  General Defines for FCP                           			     */
/*****************************************************************************/

#define FCP_NPORTID_MASK	0xffffff   /* Mask to extract	  */
					   /* 24-bit NPort ID	  */ 



/*****************************************************************************/
/*  FCP structures							     */
/*****************************************************************************/

/*
 *        FCP COMMAND BLOCK FOR THE PROTOCOL HEAD
 *
 *                      1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *
 * +---------------------------------------------------------------+    
 * |                    FCP:Lun ADDR (lsw)			   | 0  
 * +---------------------------------------------------------------+    
 * |                    FCP:Lun ADDR (msw)		           | 1  
 * +---------------------------------------------------------------+    
 * |  CRN          |R|IO_PRI |ATTR |T C R L 0 c A 0|ADD CDB LEN|r w| 2
 * +---------------------------------------------------------------+    
 * |                    SCSI   CDB                                 | 3  
 * +---------------------------------------------------------------+    
 * |                    SCSI   CDB                                 | 4  
 * +---------------------------------------------------------------+    
 * |                    SCSI   CDB                                 | 5  
 * +---------------------------------------------------------------+    
 * |                    SCSI   CDB                                 | 6  
 * +---------------------------------------------------------------+    
 * |                    SCSI  DATA  LENGTH                         | 7  
 * +---------------------------------------------------------------+    
 *        FCP: SCSI-3 OVER FIBRECHANNEL
 *
 *   NOTE:
 *	  Word 0,1    Device lun id
 *        Word 2      FCP  control flags
 *        Words 3 - 7 used for SCSI CDB & transfer length.
 *
 *
 * NOTES:
 *     CRN - Command Reference Number
 *     ADD CDB LEN - Additional FCP CDB length 
 *
 *     CODING FOR WORD 2 (FCP CNTL) ABOVE :
 *
 *               ATTR: SCSI-3 Task Attributes
 *		       B'000' - SIMPLE QUEUE
 *		       B'001' - HEAD OF QUEUE
 *                     B'010' - ORDERED QUEUE
 *                     B'100' - ACA QUEUE
 *                     B'101' - UNTAGGED
 *                     All other values reserved.
 *
 *		    T: Terminate Task
 *		    C: CLEAR ACA
 *		    R: Target Reset
 *                  L: Logical Unit Reset
 *		    c: CLEAR TASK SET
 *		    A: ABORT TASK SET
 *
 *		    r: Read Data
 *		    w: Write Data
 *
 */

struct fcp_cdb {
    unsigned long long	   lun;		/* Lun ID			     */
    uint                   fcp_cntl;	/* FCP control field		     */
#ifdef __ia64
    				        /* DIRECTION OF I/O FLAGS	     */
#define FCP_WRITE_DATA	       	0x01000000	
					/* Write Data to FCP device          */
#define FCP_READ_DATA	       	0x02000000
					/* Read Data from FCP device  	     */

    					/* TASK MANAGEMENT FLAGS	     */

#define FCP_TASK_MGM_FLGS_MASK	0x00f60000  
					/* Mask to extract the task 	     */
    					/* management flags from the fcp_cntl*/
    					/* field.			     */

#define FCP_ABORT_TASK_SET	 0x00020000  
					/* Abort Task Set: Causes all        */
    					/* tasks in the task set from the    */
    					/* this initiator to be aborted.     */

#define FCP_CLEAR_TASK_SET	 0x00040000  
					/* Clear Task Set: Causes all        */
					/* tasks from all initiators to be   */
					/* aborted.                          */
#define FCP_LUN_RESET           0x00100000 
					/* Logical Unit Reset: Performs a    */
					/* reset on a Lun.                   */
#define FCP_TARGET_RESET        0x00200000  
					/* Target Reset: Performs a          */
					/* reset to the SCSI device.	     */

#define FCP_CLEAR_ACA	        0x00400000  
					/* Clear ACA: Causes the ACA         */
    					/* (auto contingent allegiance)      */
					/* condition to be cleared on the    */
    					/* device.			     */

#define FCP_TERMINATE_TASK      0x00800000  
					/* Terminate Task: requests that the */
					/* specified task be terminated w/o  */
					/* corrupting the medium.	     */

					/* TASK ATTRIBUTES		     */

#define FCP_TASK_ATTR_MASK	0x00000700 
					/* Mask to extract the task attribute*/
					/* settings from the fcp_cntl field  */

#define FCP_SIMPLE_Q	   	0x00000000 
					/* Simple Queuing.  The device can   */
                                        /* reorder the commands in its queue.*/


#define FCP_HEAD_OF_Q	   	0x00000100
					/* Put at Head of device's Queue     */

#define FCP_ORDERED_Q		0x00000200 
					/* Ordered Queuing.  The device can  */
                                        /* not reorder the commands in its   */
                                        /* queue.  However the system can    */
                                        /* still reorder commands.           */

#define FCP_ACA_Q		0x00000400 
					/* This command is issued when an ACA*/
					/* (auto contingent allegiance)      */
    					/* condition exists at the target.   */
					/* Only one command with FCP_ACA_Q   */
					/* can be queued to the device from  */
					/* this initiator at a time.	     */

#define FCP_UNTAGGED		0x00000500 
					/* No queuing to this target.        */


					/* Command Reference Number          */

#define FCP_CRN_MASK	     0x000000ff /* Mask to extract the task attribute*/
					/* settings from the fcp_cntl field  */
#define FCP_IO_PRIORITY      0x00007800 /* Mask to extract the task priority */
#define FCP_IO_PRIORITY_SHIFT       0xc /* Shift definition for task priority*/

#else /* !__ia64 */
    				        /* DIRECTION OF I/O FLAGS	     */
#define FCP_WRITE_DATA	       	0x1	/* Write Data to FCP device          */
#define FCP_READ_DATA	       	0x2	/* Read Data from FCP device  	     */

    					/* TASK MANAGEMENT FLAGS	     */

#define FCP_TASK_MGM_FLGS_MASK	0xf600  /* Mask to extract the task 	     */
    					/* management flags from the fcp_cntl*/
    					/* field.			     */

#define FCP_ABORT_TASK_SET	 0x200  /* Abort Task Set: Causes all        */
    					/* tasks in the task set from the    */
    					/* this initiator to be aborted.     */

#define FCP_CLEAR_TASK_SET	 0x400  /* Clear Task Set: Causes all        */
					/* tasks from all initiators to be   */
					/* aborted.                          */
#define FCP_LUN_RESET           0x1000  /* Logical Unit Reset: Performs a    */
					/* reset on a Lun.                   */
#define FCP_TARGET_RESET        0x2000  /* Target Reset: Performs a          */
					/* reset to the SCSI device.	     */

#define FCP_CLEAR_ACA	        0x4000  /* Clear ACA: Causes the ACA         */
    					/* (auto contingent allegiance)      */
					/* condition to be cleared on the    */
    					/* device.			     */

#define FCP_TERMINATE_TASK      0x8000  /* Terminate Task: requests that the */
					/* specified task be terminated w/o  */
					/* corrupting the medium.	     */

					/* TASK ATTRIBUTES		     */

#define FCP_TASK_ATTR_MASK	0x70000 /* Mask to extract the task attribute*/
					/* settings from the fcp_cntl field  */

#define FCP_SIMPLE_Q	   	0x00000 /* Simple Queuing.  The device can   */
                                        /* reorder the commands in its queue.*/


#define FCP_HEAD_OF_Q	   	0x10000 /* Put at Head of device's Queue     */

#define FCP_ORDERED_Q		0x20000 /* Ordered Queuing.  The device can  */
                                        /* not reorder the commands in its   */
                                        /* queue.  However the system can    */
                                        /* still reorder commands.           */

#define FCP_ACA_Q		0x40000 /* This command is issued when an ACA*/
					/* (auto contingent allegiance)      */
    					/* condition exists at the target.   */
					/* Only one command with FCP_ACA_Q   */
					/* can be queued to the device from  */
					/* this initiator at a time.	     */

#define FCP_UNTAGGED		0x50000 /* No queuing to this target.        */


					/* Command Reference Number          */

#define FCP_CRN_MASK	     0xff000000 /* Mask to extract the task attribute*/
					/* settings from the fcp_cntl field  */
#define FCP_IO_PRIORITY      0x00780000 /* Mask to extract the task priority */
#define FCP_IO_PRIORITY_SHIFT      0x13 /* Shift definition for task priority*/

#endif /* !__ia64 */
    struct scsi_cdb        scsi_cmd_blk;/* 16 byte SCSI CDB		     */

    					/* transfer length		     */
    uint                   scsi_data_length;
};

/*
 * Set the Command Reference Number in the fcp_cntl field
 * of the fcp_cdb. This macro assumes the fcp_cntl argument
 * is a uint and that the crn is no larger then a uint.
 */
#ifdef __ia64
#define FCP_SET_CRN(fcp_cntl, crn) 		\
{						\
    (fcp_cntl) &= 0xffffff00;			\
    (fcp_cntl) |= ((crn) & 0xff) 		\
						\
}
#else /* !__ia64 */
#define FCP_SET_CRN(fcp_cntl, crn) 		\
{						\
    (fcp_cntl) &= 0x00ffffff;                   \
    (fcp_cntl) |= ((crn) & 0x000000ff) << 24;	\
						\
}

#endif /* !__ia64 */


/*
 * Get the Command Reference Number in the fcp_cntl field
 * of the fcp_cdb. This macro assumes the fcp_cntl argument
 * is a uint and that the crn is a uchar.
 */
#ifdef __ia64
#define FCP_GET_CRN(fcp_cntl, crn) 				\
{								\
  (crn) = (uchar)((fcp_cntl) & 0x000000ff);			\
								\
}
#else /* !__ia64 */
#define FCP_GET_CRN(fcp_cntl, crn) 				\
{								\
  (crn) = (uchar)(((fcp_cntl) & 0xff000000) >> 24) & 0x000000ff;\
								\
}
#endif /* !__ia64 */

#define MAX_FCP_INFO_LENGTH	256

/*
 *        FCP RESPONSE INFORMATION UNIT
 *
 *                      1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *
 * +---------------------------------------------------------------+   
 * |  			Reserved			           | 0 
 * +---------------------------------------------------------------+    
 * |  			Reserved			           | 1  
 * |---------------------------------------------------------------+    
 * |RESVD          |       RESVD         |C U O S R| SCSI Status   | 2
 * |---------------------------------------------------------------+  
 * |                    Residual Count                             | 3
 * +---------------------------------------------------------------+    
 * |                    Length of autosense data                   | 4  
 * +---------------------------------------------------------------+    
 * |                    Length of response data                    | 5  
 * +---------------------------------------------------------------+    
 * |                    Response data followd by autosense data    | 6  
 *  	                 .
 *                       .
 * +---------------------------------------------------------------+    
 *
 *   NOTES:
 *
 *		FCP Status word
 *
 *
 *
 *		U: FCP RESID UNDERRUN
 *		O: FCP RESID OVERRUN
 *		S: FCP length of autosense data is valid
 *		R: FCP length of response data is valid
 *
 *		SCSI status (see sc_buf in scsi.h for valid values)
 */
struct fcp_response_iu {
	uint	   	resvd1;	      	/* reserved for future use  	*/
	uint 		resvd2;		/* reserved for future use  	*/
	uint		fcp_status;	/* FCP status returned by   	*/
					/* device.		    	*/
#ifdef __ia64
#define FCP_CONF_REQ      	0x00100000  
					/* Initiator shall transmit	*/
					/* a FCP_CONF IU                */
#define FCP_RESID_UNDER 	0x00080000  
					/* Data underrun		*/
#define FCP_RESID_OVER		0x00040000  
					/* Data overrun		        */
#define FCP_SNS_LEN_VALID	0x00020000  
					/* sense_length valid		*/
#define FCP_RSP_LEN_VALID	0x00010000  
					/* response_length valid	*/

#define FCP_SCSI_STATUS_MASK	0xff000000  
					/* Mask to extract SCSI status  */
					/* from FCP status.		*/
#define FCP_RETRY_DELAY_CODE_MASK	0x0000ffff
					/* Mask to extract retry_delay_code */
#else /* !__ia64 */
#define FCP_CONF_REQ      	0x1000  /* Initiator shall transmit	*/
					/* a FCP_CONF IU                */
#define FCP_RESID_UNDER 	0x0800  /* Data underrun		*/
#define FCP_RESID_OVER		0x0400  /* Data overrun		        */
#define FCP_SNS_LEN_VALID	0x0200  /* sense_length valid		*/
#define FCP_RSP_LEN_VALID	0x0100  /* response_length valid	*/

#define FCP_SCSI_STATUS_MASK	0x00ff  /* Mask to extract SCSI status  */
					/* from FCP status.		*/
#define FCP_RETRY_DELAY_CODE_MASK	0xffff0000
					/* Mask to extract retry_delay_code */
#endif /* !__ia64 */

        uint 		resid;          /* only valid for data underrun */
					/* or overruns.			*/
        uint		sense_length;   /* Length of autosense data	*/
        uint		response_length;/* Length of response data	*/


        char  data[MAX_FCP_INFO_LENGTH];/* Used for both autosense 	*/
					/* data and response data.	*/
					/* If response_length is non-   */
					/* zero, then the data[0] up to */
					/* and including 		*/
					/* data[response_length-1] is   */
					/* the response data.  		*/
					/* If sense_length is non-zero, */
					/* then data[response_length]   */
					/* up to and including 		*/
					/* data[response_length + 	*/
					/* sense_length -1 ] is the     */
					/* autosense data.		*/
					
};

/*****************************************************************************/
/*  Valid FCP Response Codes						     */
/*****************************************************************************/

/*
 *
 *			FCP Response code word
 *
 *                      1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +---------------------------------------------------------------+
 * |                       RESVD                   |Response Code  | 
 * +---------------------------------------------------------------+
 *
 *
 */
#define	FCP_RSP_CODE_MASK 		0xff /* Mask to extract Response code*/
					     /* from FCP response data.	     */
#define FCP_RSP_SUCCESSFUL		0x00 /* Sucessful completion.	     */
#define FCP_RSP_LENGTH_DIFF		0x01 /* FCP data length different    */
					     /* from burst length	     */
#define FCP_RSP_INVALID_CMD_FIELDS	0x02 /* Invalid fields in FCP_CMND   */
#define FCP_RSP_DATARO_MISMATCH		0x03 /* FCP DATA RO mismatch with    */
					     /* FCP XFER RDY DATA RO.	     */
#define FCP_RSP_TSKMGM_UNSUPPORED	0x04 /* Task management function is  */
					     /* not supported by this device */
#define FCP_RSP_TSKMGM_FAILED           0x05 /* Task management function was */
					     /* not performed by this device,*/
					     /* but it is supported. 	     */


/*
 * FC-PH Optional Expiration Security header
 *
 *  +-------------------------------------------------------+ -----+
 *  |    		  MSW Expiration Time = 0	    |	   |
 *  +-------------------------------------------------------+	   |
 *  |   	          LSW Expiration Time = 0           |   struct 
 *  +-------------------------------------------------------+   fcp_exp_sec_hdr
 *  |S_Type = 0  | Reserved = 0 |  S_length = 0    	    |      |
 *  +-------------------------------------------------------+	   |
 *  |                     Security Password   		    |	   |
 *  +-------------------------------------------------------+ -----|
 *
 */
struct fcp_exp_security_header {
	uint		expiration_time_msw; /* Most significant word of    */
                                             /* time expiration.            */
	uint		expiration_time_lsw; /* Least significant word of   */
                                             /* time expiration.            */
	uchar		s_type;		     /* Security type		    */
	uchar 		resvd;		     /* Reserved for future use	    */
	ushort		s_length;	     /* Security length		    */
	uint		security_passwd;     /* Security password	    */
};

/* 
 * FCP service parameter page used for the process login (PRLI) requests and
 * accepts.
 */

struct fcp_service_parms {
	uchar		type_code;	    /* FCP type 		   */
#define FCP_SCSI	0x08		    /* This device is an FCS SCSI  */
					    /* device.			   */
	uchar		type_code_ext;	    /* FCP type extension. Reserved*/
	uchar		flags;		    /* Flags for the target	   */
#define FCP_CREATE_IMAGE_PAIR	      0x20  /* Establish an image pair.    */
#define FCP_SUCCESS_RESP              0x01  /* This is set in the PRLI     */
					    /* accept payload when the PRLI*/
					    /* was accepted.               */
	uchar 		resvd1;		    /* Reserved for future use.	   */
	uint		orig_proc_assoc;    /* Originator Process 	   */
					    /* associator		   */
	uint		resp_proc_assoc;    /* Responder Process 	   */
					    /* associator		   */
	ushort		resvd2;		    /* Reserved for future use.	   */ 
	ushort		dev_flags;	    /* Device flags.		   */
/*
 * These macros are meant for use with a 16 bit fcp device flags only.
 * The scsi_buf interfaces where a 8 bit flag is used (SCIOLST) must
 * use the backward compatible 8 bit version of the macros defined later
 * in this file.
 */
#ifdef __ia64
#define FCP_DEV_REC_SPT		     0x0004 /* When set indicates REC ELS  */
					    /* is supported                */
#define FCP_DEV_TASK_RETRY_ID        0x0002 /* When set indicates the      */
					    /* Task Retry Identifier is    */
					    /* supported.                  */
#define FCP_DEV_RETRY_CMD            0x0001 /* When set indicates the      */
					    /* device supports retries	   */
                                            /* and sequence retransmission */
					    /* request (SRR) ELS           */
#define FCP_DEV_CONF_COMPLETE        0x8000 /* When set indicates the      */
					    /* device supports the         */
					    /* confirmed completion        */
					    /* protocol                    */
#define FCP_DEV_DATA_OVERLAY	     0x4000 /* When set, Data overlay is   */
					    /* allowed.			   */
#define FCP_DEV_INITIATOR_FCN	     0x2000 /* This device is a SCSI 	   */
					    /* Initiator.		   */
#define FCP_DEV_TARGET_FCN	     0x1000 /* This device is a SCSI 	   */
					    /* Target.		           */
#define FCP_DEV_MIXED_CMD_DATA	     0x0800 /* Command/Data mix allowed	   */
#define FCP_DEV_MIXED_DATA_RSP	     0x0400 /* Data/response mix allowed   */
#define FCP_DEV_READ_XFER_RDY_DISABLED   0x0200 
					    /* When set, FCP_XFER_RDY can  */
					    /* be used for SCSI reads.	   */
#define FCP_DEV_WRITE_XFER_RDY_DISABLED  0x0100 
					    /* When set, FCP_XFER_RDY can  */
					    /* be used for SCSI writes.	   */
#else /* !__ia64 */
#define FCP_DEV_REC_SPT		     0x0400 /* When set indicates REC ELS  */
					    /* is supported                */
#define FCP_DEV_TASK_RETRY_ID        0x0200 /* When set indicates the      */
					    /* Task Retry Identifier is    */
					    /* supported.                  */
#define FCP_DEV_RETRY_CMD            0x0100 /* When set indicates the      */
					    /* device supports retries	   */
                                            /* and sequence retransmission */
					    /* request (SRR) ELS           */
#define FCP_DEV_CONF_COMPLETE        0x0080 /* When set indicates the      */
					    /* device supports the         */
					    /* confirmed completion        */
					    /* protocol                    */
#define FCP_DEV_DATA_OVERLAY	     0x0040 /* When set, Data overlay is   */
					    /* allowed.			   */
#define FCP_DEV_INITIATOR_FCN	     0x0020 /* This device is a SCSI 	   */
					    /* Initiator.		   */
#define FCP_DEV_TARGET_FCN	     0x0010 /* This device is a SCSI 	   */
					    /* Target.		           */
#define FCP_DEV_MIXED_CMD_DATA	     0x0008 /* Command/Data mix allowed	   */
#define FCP_DEV_MIXED_DATA_RSP	     0x0004 /* Data/response mix allowed   */
#define FCP_DEV_READ_XFER_RDY_DISABLED   0x0002 
					    /* When set, FCP_XFER_RDY can  */
					    /* be used for SCSI reads.	   */
#define FCP_DEV_WRITE_XFER_RDY_DISABLED  0x0001 
					    /* When set, FCP_XFER_RDY can  */
					    /* be used for SCSI writes.	   */
#endif /* !__ia64 */
};

/*
 * Macro to extract important flags into a 8 bit quantity. The current
 * scsi buf interface allows only a 8 bit device flag. So, this macro
 * extracts the most important device flags into a char.
 */
#ifdef __ia64
#define FCP_GET_DEV_FLAGS(dev_flags)	\
		((uchar)((((ushort)(dev_flags)) >> 8) & 0xff)) 
#else /* !__ia64 */
#define FCP_GET_DEV_FLAGS(dev_flags)	((uchar)((dev_flags) & 0xff))
#endif /* !__ia64 */

/*
 * These backward compatible macros are to be used with the device_flags 
 * returned during SCIOLST. They must be extracted from the device_flags as
 * defined in FCP protocol (see FCP_DEV_XXX flags). For IA64, it
 * is the higher order byte, for POWER it is the lower order byte.
 */
#define FCP_RETRY_CMD       	0x0100 
				     /* When set indicates the      	*/
				     /* This flag is only for 		*/
				     /* backward compatibility. It 	*/
				     /* shouldn't be used with		*/
				     /* device_flags in SCIOLST.	*/

#define FCP_CONF_COMPLETE	0x80 /* When set indicates the          */
				     /* device supports the         	*/
			    	     /* confirmed completion        	*/
				     /* protocol                    	*/
#define FCP_DATA_OVERLAY	0x40 /* When set, Data overlay is   	*/
				     /* allowed.		   	*/
#define FCP_INITIATOR_FCN	0x20 /* This device is a SCSI 	   	*/
			 	     /* Initiator.		   	*/
#define FCP_TARGET_FCN	       	0x10 /* This device is a SCSI 	   	*/
				     /* Target.		           	*/
#define FCP_MIXED_CMD_DATA	0x08 /* Command/Data mix allowed   	*/
#define FCP_MIXED_DATA_RSP	0x04 /* Data/response mix allowed   	*/
#define FCP_READ_XFER_RDY_DISABLED   0x02 
				     /* When set, FCP_XFER_RDY can  	*/
				     /* be used for SCSI reads.	   	*/
#define FCP_WRITE_XFER_RDY_DISABLED  0x01 
				     /* When set, FCP_XFER_RDY can  	*/
				     /* be used for SCSI writes.   	*/

/* 
 * FCP Process Login (PRLI) Requests and Accept Payload
 */
struct fcp_prli {
	uchar  cmd_code;		    /* Command code                */
#define FCP_PRLI_CMD   0x20		    /* FCP Process Login           */
#define FCP_PRLO_CMD   0x21		    /* FCP Process Logout          */
	uchar  page_len;		    /* Page Length                 */
	ushort payload_len;		    /* Payload Length              */
	struct fcp_service_parms parms;     /* Service Parameters          */  
};
#endif /* _H_FCP */
