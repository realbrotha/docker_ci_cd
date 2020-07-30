/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/tmscsi.h 1.6                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1990,1991          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)11	1.6  src/bos/kernel/sys/tmscsi.h, sysxtm, bos53L, l2007_14A6 3/31/07 14:47:22 */
#ifndef _H_TMSCSI
#define _H_TMSCSI
/*
 * COMPONENT_NAME: (SYSXTM) IBM SCSI Target Mode Header File
 *
 * FUNCTIONS: NONE
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1990, 2007
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/************************************************************************/
/*                                                                      */
/*  SOURCE FILE:        tmscsi.h                                        */
/*                                                                      */
/*  NAME:       SCSI target mode driver header file.                    */
/*                                                                      */
/*  NOTE:       This header file contains the definition of the         */
/*              structures which are passed from the the application	*/
/*		programs to the SCSI target mode device driver.         */
/*                                                                      */
/************************************************************************/

#include <sys/scsi.h>
#include <sys/scsi_buf.h>

#define	TM_MAXRETRY	3

/***********************************************************************
	ioctl commands
************************************************************************/
#define	TMGETSENS	999  /* Request Sense data with argument of    */
                             /* struct tm_get_sens. Only supported on  */
                             /* Initiator Mode devices(tmscsix.im).    */
#define	TMIOCMD		998  /* Issue a user-defined SCSI command      */
                             /* with argument of struct sc_iocmd       */
                             /* defined in scsi.h. Only supported on   */
                             /* Initiator Mode devices(tmscsix.im).    */
#define	TMIOSTAT	997  /* Request IO status information with     */
                             /* argument of struct tm_get_stat.        */
                             /* Only supported on Initiator Mode       */
                             /* devices(tmscsix.im).                   */
#define	TMCHGIMPARM	996  /* Change Initiator Mode parameters with  */
                             /* argument of struct tm_chg_im_parm.     */
                             /* Only supported on Initiator Mode       */
                             /* devices(tmscsix.im).                   */
#define	TMIOEVENT	995  /* Request TM event info with argument of */
                             /* struct tm_event_info                   */
#define	TMIORESET	994  /* Issue Initiator Mode Bus Device Reset  */
                             /* Only supported on Initiator Mode       */
                             /* devices(tmscsix.im).                   */
#define	TMIOASYNC	993  /* Force Iniator Mode device to run async */
                             /* Only supported on Initiator Mode       */
                             /* devices(tmscsix.im).                   */

/************************************************************************
        SCSI-3 ioctl commands
*************************************************************************/
#define TMPASSTHRU      0x17  /* Issue a user-defined SCSI command for  */
                              /* SCSI-3 driver with argument of         */
                              /* struct sc_passthru define in scsi.h    */
                              /* Only supported on Initiator Mode       */
                              /* devices(tmscsix.im).                   */
#define TMIOLSTAT       992   /* Request IO status information with     */
                              /* argument of struct tm_get_scsistat     */
                              /* Only supported on Initiator Mode       */
                              /* devices(tmscsix.im).                   */


/************************************************************************/
/*	structure to be passed to TMGETSENS ioctl 			*/
/************************************************************************/

struct tm_get_sens {
	caddr_t	addr;		/* address of user sense data buffer, */
				/* which is where data will be placed */
	ushort	resvd1;		/* reserved, must be set to 0         */
	uchar	resvd2;		/* reserved, must be set to 0         */
	uchar	len;		/* length, in bytes, of sense data    */
				/*    range: 0 to 255 bytes           */
	uint	resvd3;		/* reserved, must be set to 0         */
};

/*
 * NOTE: This structure is not supported for use by applications. It is only
 *       for internal device driver use.
 *
 * get sense structure passed by pointer to ioctl of adapter driver used
 * internally by driver for support of 64-bit applications.
 */
#ifdef _KERNEL



struct tm_get_sens64 {
	ptr64	addr;		/* address of user sense data buffer, */
				/* which is where data will be placed */
	ushort	resvd1;		/* reserved, must be set to 0         */
	uchar	resvd2;		/* reserved, must be set to 0         */
	uchar	len;		/* length, in bytes, of sense data    */
				/*    range: 0 to 255 bytes           */
	uint	resvd3;		/* reserved, must be set to 0         */
};


/* used internally for support of 32 bit applications by 64 bit  kernel */
/* extensions */

struct tm_get_sens32 {
	ptr32	addr;		/* address of user sense data buffer, */
				/* which is where data will be placed */
	ushort	resvd1;		/* reserved, must be set to 0         */
	uchar	resvd2;		/* reserved, must be set to 0         */
	uchar	len;		/* length, in bytes, of sense data    */
				/*    range: 0 to 255 bytes           */
	uint	resvd3;		/* reserved, must be set to 0         */
};



#endif


/*	structure to be passed to TMIOSTAT ioctl */

struct	tm_get_stat {
	uchar	status_validity; 	/* least significant bit - scsi_status
					   valid, next least significant bit -
					   card status valid */
	uchar	scsi_status;          /* refer to <sys/scsi.h> struct sc_buf */
	uchar	general_card_status;  /* refer to <sys/scsi.h> struct sc_buf */
	uchar	b_error;		/* errno value from the command      */
	uint	b_resid;		/* residual count from the command   */
	uint	resvd1;			/* reserved, must be set to 0        */
	uint	resvd2;			/* reserved, must be set to 0        */
};

/*      structure to be passed to TMIOLSTAT ioctl */

struct  tm_get_scsistat {
        uchar   status_validity;        /* least significant bit - scsi_status
                                         * valid, next least significant bit -
                                         * adapter status valid              */
        uchar   scsi_status;    /* refer to <sys/scsi_buf.h> struct scsi_buf */
        uchar   adapter_status; /* refer to <sys/scsi_buf.h> struct scsi_buf */
        uchar   b_error;                /* errno value from the command      */
        uint    b_resid;                /* residual count from the command   */
        uint    resvd1;                 /* reserved, must be set to 0        */
        uint    resvd2;                 /* reserved, must be set to 0        */
};

/*	structure to be passed to TMCHGIMPARM ioctl */

struct	tm_chg_im_parm {
	ushort	chg_option;	/* indicate if retry delay, or send cmd
				   timeout, or both are being changed  */

#define	TM_CHG_RETRY_DELAY	0x01	/* change Send cmd retry delay */
#define	TM_CHG_SEND_TIMEOUT	0x02	/* change Send cmd timeout val */

	uchar	timeout_type;	/* if timeout being changed, this selects
				   which type of timeout to use */

#define	TM_FIXED_TIMEOUT	0x01	/* select fixed value timeout  */
#define	TM_SCALED_TIMEOUT	0x02	/* select scaled type timeout  */

	uchar	new_delay;	/* if retry delay being changed, this sets
				   new delay in seconds, from 0 to 255 */
	ushort	new_timeout;	/* if timeout being changed, this is new
				   timeout val; can be fixed or scaled */
	ushort	resvd1;		/* reserved, must be set to 0          */
	uint	resvd2;		/* reserved, must be set to 0          */
};

/*	structure to be passed to TMIOEVENT ioctl */

struct	tm_event_info {
	int	events;		/* the following events can be reported: */

#define	TM_FATAL_HDW_ERR	SC_FATAL_HDW_ERR
				/* adapter fatal hardware failure     */
#define	TM_ADAP_CMD_FAILED	SC_ADAP_CMD_FAILED
				/* unrecoverable adapter cmd failure  */
#define	TM_SCSI_BUS_RESET	SC_SCSI_RESET_EVENT
				/* SCSI bus reset detected            */
#define	TM_BUFS_EXHAUSTED	SC_BUFS_EXHAUSTED
				/* maximum buffer usage detected      */

	uint	resvd1;		/* reserved, must be set to 0         */
	uint	resvd2;		/* reserved, must be set to 0         */
	uint	resvd3;		/* reserved, must be set to 0         */
};

#endif /* _H_TMSCSI */
