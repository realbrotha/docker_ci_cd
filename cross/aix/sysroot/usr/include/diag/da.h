/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/usr/include/diag/da.h 1.15                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)21	1.15  src/bos/usr/include/diag/da.h, cmddiag, bos53D, d2005_19D9 5/11/05 08:34:03 */
/*
 *   COMPONENT_NAME: CMDDIAG
 *
 *   FUNCTIONS: Diagnostic header file.
 *
 *   ORIGINS: 27
 *
 */


#ifndef _H_DA
#define _H_DA

#include <sys/cfgdb.h>

#define MAXFRUS 4
#define FRUB1	4
#define FRUB2	5
#define FRUB_ENCLDA	6

#define NOT_IN_DB	0
#define DA_NAME		1
#define PARENT_NAME 	2
#define CHILD_NAME 	3
#define	NO_FRU_LOCATION	4

/*	Return codes from diagex routines	*/

#define	CHILD_UNCONFIGURE_ERROR		1 /* Child cannot be unconfigured  */
#define	DEVICE_UNCONFIGURE_ERROR	2 /* Device cannot be unconfigured */
#define	DEVICE_DIAGNOSE_ERROR		3 /* Device cannot be put in       */
					  /* diagnose state.		   */
#define	DEVICE_DEFINE_ERROR		4 /* Device cannot be put in 	   */
					  /* define state.		   */
#define	DEVICE_CONFIGURE_ERROR		5 /* Device cannot be configured   */
#define	CHILD_CONFIGURE_ERROR		6 /* Child cannot be configured    */
#define	DEVICE_ALREADY_IN_DIAGNOSE	7 /* Already in DIAGNOSE state.    */

/* Constants defined in RPA Event/Error Log */
/* NN indicates the RPA definition is "not Null separated", */
/* so the defined constant is one more than the RPA definition. */
#define RPA_SRC_SIZE_NN		33
#define RPA_LOC_SIZE		80
#define	RPA_FRU_PN_SIZE		8
#define	RPA_FRU_SN_SIZE_NN	13
#define	RPA_PROC_SIZE 		8
#define	RPA_CCIN_SIZE_NN	5
#define	RPA_DUMP_FN_SIZE	40
#define	RPA_FRUTYPE_NORMAL	1
#define	RPA_FRUTYPE_CODE	2
#define	RPA_FRUTYPE_C_PROC	3
#define	RPA_FRUTYPE_M_PROC	4
#define	RPA_FRUTYPE_EXT		9
#define	RPA_FRUTYPE_EXT_CODE	10
#define	RPA_FRUTYPE_TOOL	11
#define	RPA_FRUTYPE_SYMBOL	12
#define RPA_MT_MTM_SIZE		8
#define RPA_MT_SN_SIZE		12

/* Action flags defined by RPA Version 6 */
#define RPA_SERVICE_ACTION	0x8000
#define RPA_HIDDEN_ERROR	0x4000
#define RPA_REPORT_EXTERNALLY	0x2000
#define RPA_NOT_HYPERVISOR	0x1000
#define RPA_CALL_HOME_REQD	0x0800
#define RPA_ISOLATION_INCOMPLETE 0x0400

/* Diagnostics overload of Action flag bits for errors reported to the 	*/
/* controller in the fru_bucket_src and frus_src structures. The 	*/
/* flags are only valid when fru_bucket_src.plid == 0, which indicates 	*/
/* the error data is not from a RPA Version 6 Platform Event/Error.	*/

#define NO_FAULT_INDICATOR	0x0080	/* do not turn on the fault 	*/
					/* indicator for this fru_bucket_src */

#define	EXEMPT		3
#define	NONEXEMPT	4

#ifndef 	NULL
#define		NULL	0
#endif

#ifndef 	TRUE
#define		TRUE	1	
#endif

#ifndef _RPA_DEF_ONLY		/* do not include in diagodm.cre */
typedef struct
{
	int	conf;			/* probability of failure	*/
	char	fname[NAMESIZE];	/* FRU name			*/
	char	floc[LOCSIZE];		/* location of fname		*/
	short	fmsg; 			/* text message number for fname*/
	char    fru_flag;		/* flag used by DA		*/
	char	fru_exempt;
}fru_t;

struct	fru_bucket
{
	char	dname[NAMESIZE];	/* device name			*/
	short   ftype;	/* FRU bucket type added to the system       */
	short	sn;	/* Source number of the failure              */
	short	rcode;	/* reason code for the failure               */
	short	rmsg;	/* Failure description                       */
	fru_t 	frus[MAXFRUS];

};

typedef struct frus_src
{
	int	type;			/* RPA FRU type */	
	char	priority[2];		/* RPA FRU/Procedure Priority */
	char	loc[RPA_LOC_SIZE];	/* Physical location code */	
	char	pn[RPA_FRU_PN_SIZE];	/* FRU Part Number, if available */
	char	proc_id[RPA_PROC_SIZE];	/* Procedure Id, if available */
	char	ccin[RPA_CCIN_SIZE_NN];	/* CCIN, if available */
	char	sn[RPA_FRU_SN_SIZE_NN];	/* FRU Serial Number, if available */
	struct frus_src *next_fru;
} frus_src_t;

struct fru_bucket_src
{
        char    dname[NAMESIZE];/* Resource Name */
        char    src[RPA_SRC_SIZE_NN];/* SRC - Primary reference code */
        unsigned int refc2;	/* Extended reference code - word 2 */
        unsigned int refc3;	/* Extended reference code - word 3 */
        unsigned int refc4;	/* Extended reference code - word 4 */
        unsigned int refc5;	/* Extended reference code - word 5 */
        unsigned int refc6;	/* Extended reference code - word 6 */
        unsigned int refc7;	/* Extended reference code - word 7 */
        unsigned int refc8;	/* Extended reference code - word 8 */
        unsigned int refc9;	/* Extended reference code - word 9 */
        int     rmsg; 		/* Failure description */
        char    crid[2];	/* Platform error creator id */
        unsigned int plid;	/* Platform Log Id */
	unsigned int subsysid;	/* Subsystem Id */
	unsigned int event_sev;	/* Event Severity */
        int     action_flags;	/* Error Action Flags */
        int     errlg_seq;	/* Error Log Sequence Number */
        frus_src_t *frus;
};

#endif 	/* ! _RPA_DEF_ONLY */
#endif

