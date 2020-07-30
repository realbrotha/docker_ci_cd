/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1998,2009          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*
 * Module Name:	ffdc.h
 *
 * Component:	ffdc
 *
 * Description:	Definitions and data types for use by First Failure Data
 *		capture (FFDC) client applications.  This file must be included
 *		by all applications using libffdc.a shared library.
 */

/* @(#)40   1.15.1.1   src/rsct/ffdc/inc/ffdc.h, ffdc, rsct_rhay53, rhay531006a 6/16/08 12:20:05 */

#ifndef	_H_FFDC
#define	_H_FFDC

#ifdef	__cplusplus
extern "C" {
#endif	/* __cplusplus */

#include	<sys/types.h>
#ifdef	_AIX
#include	<sys/err_rec.h>
#endif	/* _AIX */
#include	<nl_types.h>

/*
 * Define AIX Error Log limit for non-AIX compilations.
 */
#ifndef	ERR_REC_MAX
#define	ERR_REC_MAX	2048
#endif

/*
 * FC_VERSION defines the version of the First Failure Data Capture application
 * programming interfaces desired y a client.  If the client has not specified
 * a particular version, version 1 is used.
 */
#ifndef	FC_VERSION
#define	FC_VERSION	1
#endif	/* FC_VERSION */

/*
 * Definition of FFDC Error Identifier data type
 */
#define	FC_EID_LEN	42
typedef char fc_eid_t[FC_EID_LEN + 1];

/*
 * Definition of error table and associated types. These types are used
 * to hold information extracted from AIX Error Log templates, which is then
 * used to format messages for the BSD System Log
 */
typedef enum {
	FC_ERROR_DETAIL_HEX,
	FC_ERROR_DETAIL_DEC,
	FC_ERROR_DETAIL_ALPHA
} fc_err_detail_type_t;

typedef struct {
	int 			length;
	int 			set_number;
	int 			msg_number;
	char			*default_msg;
	fc_err_detail_type_t	detail_type;
} fc_err_detail_t;

typedef struct {
	unsigned int	error_id;
	char		*error_label;
	int 		desc_set_number;
	int 		desc_msg_number;
	char		*desc_default_msg;
	int 		number_detail;
	fc_err_detail_t	*error_detail;
} fc_err_tbl_t;

/*
 * FFDC Event Definitions - used as arguments to the fc_error_log() library
 * routine and the fclogerr command to indicate the severity of the incident
 * being recorded
 */
#define	FFDC_EMERG	0		/* LOG_EMERG in BSD Ssystem Log */
#define	FFDC_ERROR	1		/* LOG_ERR in BSD System Log    */
#define	FFDC_STATE	2		/* LOG_NOTICE in BSD System Log */
#define	FFDC_PERF	3		/* LOG_WARNING in BSD System Log*/
#define	FFDC_TRACE	4		/* LOG_INFO in BSD System Log   */
#define	FFDC_RECOV	5		/* LOG_DEBUG in BSD System Log  */
#define	FFDC_DEBUG	6		/* LOG_DEBUG in BSD System Log  */

/*
 * Options to the fc_init library interface
 */
#define	FC_LOG			0x00	/* Use AIX Error Log / BSD Syslog    */
#define	FC_STACK_CREAT		0x01	/* Always uses an FFDC Error Stack   */
#define	FC_STACK_INHERIT	0x02	/* Use FFDC Stack only when already  */

/*
 * FFDC Library Interface C Language Return Codes
 */
#define	FC_SUCCESS		(int)  0	/* Normal completion         */
#define FC_INHERIT_SUCCESS	(int)  1	/* Successful inheritance of */
						/* FFDC Environment          */
#define	FC_HELP_SUCCESS		(int)  2	/* Help information displayed*/
						/* and processing stopped    */

#define	FC_OPTION_MISSING	(int) 10	/* Required options to the   */
						/* interface are missing     */
#define	FC_NOT_SUPPORTED	(int) 11	/* Option is not supported   */
						/* byt this version of FFDC  */
#define	FC_UNKNOWN_OPTION	(int) 12	/* Unknown option to library */
#define	FC_INHERIT_INV		(int) 13	/* FC_*_INHERIT & FC_*_CREAT */
						/* combined as options       */
#define	FC_ENV_EXIST		(int) 14	/* FFDC Environment already  */
						/* exists for this process   */
#define	FC_NO_FC_ENVIR		(int) 15	/* FFDC Environment does not */
						/* already exist             */
#define	FC_ENV_FAILED		(int) 16	/* Unable to modify the      */
						/* process environment       */
#define	FC_ENV_CORRUPT		(int) 17	/* Problems exist in the FFDC*/
						/* environment               */
#define	FC_NO_MEMORY		(int) 18	/* Memory allocation failed  */
#define	FC_STACK_DIRECTORY	(int) 19	/* FFDC Error Stack Directory*/
						/* /var/adm/ffdc/stacks does */
						/* not exist                 */
#define	FC_STACK_ACCESS		(int) 20	/* FFDC Error Stack File     */
						/* cannot be accessed        */
#define	FC_STACK_RESERVE	(int) 21	/* Unable to reserve an FFDC */
						/* Error Stack file in the   */
						/* FFDC Error Stack directory*/
#define	FC_STACK_LOCK		(int) 22	/* Cannot obtain exclusive   */
						/* use of the FFDC Error     */
						/* Stack                     */
#define	FC_STACK_UNLOCK		(int) 23	/* Cannot release exclusive  */
						/* use of the FFDC Error     */
						/* Stack                     */
#define	FC_STACK_CORRUPT	(int) 24	/* Contents of the FFDC Error*/
						/* Stack appear to have been */
						/* corrupted                 */
#define	FC_STACK_INV		(int) 25	/* FFDC Error Stack file is  */
						/* invalid or corrupt        */
#define	FC_COMBINED_OPTION	(int) 26	/* Mutually exclusive options*/
						/* provided to library call  */
#define	FC_EID_INV		(int) 27	/* FFDC Error Identifier is  */
						/* invalid, or invalid       */
						/* pointer was provided      */
#define	FC_RESOURCE_INV		(int) 28	/* Null or invalid resource  */
						/* name was provided         */
#define	FC_DETECTFILE_INV	(int) 29	/* Missing information on the*/
						/* detecting file (name, lpp,*/
						/* version, or location), or */
						/* invalid information given */
#define	FC_DEFAULTDESC_INV	(int) 30	/* Default description of    */
						/* incident being recorded   */
						/* appears to be invalid     */
#define	FC_DESC_INV		(int) 31	/* Description of incident   */
						/* being recorded appears    */
						/* invalid                   */
#define	FC_COPY_FAILED		(int) 32	/* Unable to copy detailed   */
						/* data file to the FFDC     */
						/* dump directory            */
#define	FC_LOGEVENT_INV		(int) 33	/* Unknown FFDC Log Event    */
						/* was provided              */
#define	FC_LOGMSG_INV		(int) 34	/* Null or empty system log  */
						/* message was provided      */
#define FC_DETAILDATA_INV	(int) 35	/* No detail data provided   */
#define	FC_DETAILLEN_INV	(int) 36	/* Length specified for the  */
						/* detail data missing or    */
						/* invalid                   */
#define	FC_EID_FAILED		(int) 37	/* The FFDC library routine  */
						/* could not generate an FFDC*/
						/* Error Identifier          */
#define	FC_SYSLOG_FAILED	(int) 38	/* Could not record incident */
						/* report to System Log      */
#define	FC_NOT_SOURCED		(int) 39	/* A command was executed in */
						/* its own subshell, not the */
						/* user's shell              */
#define	FC_FILESYS_SPACE	(int) 40	/* Insufficient file system  */
						/* space available           */
#define	FC_IO_FAILED		(int) 41	/* Input/Output failure      */
#define	FC_STACK_DISABLED	(int) 42	/* Use of FFDC Error Stacks  */
						/* has been disbaled in this */
						/* process environment       */
#define	FC_EID_REMOTE		(int) 43	/* FFDC Error Identifier was */
						/* generated on a remote node*/
#define	FC_DATA_TRUNC		(int) 44	/* Data submitted to the FFDC*/
						/* Error Stack exceeded the  */
						/* error stack record limit  */

#define	FC_INTERNAL		(int) 99	/* reserved                  */

/*
 * FFDC limits for Error Stack, AIX Error Log and BSD System Log recordings:
 *
 *	FC_STACK_MAX		The largest record that can be recorded in the
 *				FFDC Error Stack, 1024 bytes.  This record size
 *				limits INCLUDES the data needed to reserve the
 *				detecting file information, the FFDC Failure
 *				Identifier and the associated FFDC Failure
 *				Identifier, time stamps, and process information
 *				as well as the description and detail data
 *				provided by the user.
 *	FC_SYSLOG_MAX		The largest message that syslog() can handle,
 *				1024 chars - 32 chars used by syslog() for a
 *				message prefix
 *	FC_SYSLOG_MSG_MAX	The largest message that fc_log_error() will
 *				pass to the syslog() interface, FC_SYSLOG_MAX
 *				minus space that fc_log_error() uses to record
 *				detecting file information
 *	FC_FILEINFO_LEN		Space reserved to record detecting file info
 *				in the format:
 *				  <LPP_name>,<source_file>,<version>,<line_#>
 *				This is similar to the format ppslog() used,
 *				but excludes the field identifiers to conserve
 *				space
 *	FC_ERRLOG_STDINFO_LEN	The amount of space used in the AIX Error Log
 *				entry for standard information: the file
 *				identification information plus the FFDC Error
 *				Idenfitiers associated with the recording
 *	FC_DETAIL_DATA_MAX	The most bytes of detail data that
 *				fc_log_error() will pass to the errlog()
 *				interface - ERR_REC_MAX minus space reserved
 *				for the detecting file info and the FFDC Error
 *				identifiers associated with the record.
 */
#define	FC_STACK_MAX			1024
#define	FC_SYSLOG_MAX			992
#define	FC_FILEINFO_LEN			46
#define	FC_SYSLOG_MSG_MAX		(FC_SYSLOG_MAX - FC_FILEINFO_LEN)
#define	FC_ERRLOG_STDINFO_LEN		(FC_FILEINFO_LEN + (2 * FC_EID_LEN))
#define	FC_ERRLOG_DETAIL_DATA_MAX	(ERR_REC_MAX - FC_ERRLOG_STDINFO_LEN)

/*
 * The following macros convert references to the generic names of FFDC library
 * routines, like fc_test_stack(), to references to version specific FFDC
 * library routines, like fc_test_stack_1().  The version used during
 * conversion is determined by the value of FC_VERSION.  Note that these
 * macros can deal with the different versions of a routine having different
 * arguments.
 */
#define	fc_init								\
	FC_ROUTINE_VERSION(fc_init, FC_VERSION)
#define	fc_eid_init							\
	FC_ROUTINE_VERSION(fc_eid_init, FC_VERSION)
#define	fc_eid_is_set							\
	FC_ROUTINE_VERSION(fc_eid_is_set, FC_VERSION)
#define	fc_test_stack							\
	FC_ROUTINE_VERSION(fc_test_stack, FC_VERSION)
#define	fc_log_error							\
	FC_ROUTINE_VERSION(fc_log_error, FC_VERSION)
#define	fc_push_stack							\
	FC_ROUTINE_VERSION(fc_push_stack, FC_VERSION)
#define	fc_display_fid							\
	FC_ROUTINE_VERSION(fc_display_fid, FC_VERSION)
#define	fc_mk_syslog_msg						\
	FC_ROUTINE_VERSION(fc_mk_syslog_msg, FC_VERSION)

#define	FC_ROUTINE_VERSION(routinename, versionnumber)			\
	FC_ROUTINE_VERSION_GLUE(routinename, versionnumber)

#define	FC_ROUTINE_VERSION_GLUE(routinename, versionnumber)		\
	routinename ## _ ## versionnumber

/*
 * FFDC Library Interface C Language Prototypes
 */
#if (FC_VERSION == 1) || defined(FC_ALL_VERSIONS)

extern void
fc_mk_syslog_msg_1(			/* format message for BSD syslog      */
	fc_err_tbl_t	*etblp,			/* ptr to error table entry   */
	void		*detail_data,		/* ptr to detail data         */
	int 		detail_data_len,	/* length of detail data      */
	char		*msgbuf,		/* buffer to hold message     */
	int 		msgbufsize,		/* size of buffer             */
	nl_catd		catd			/* descriptor of catalog from */
						/* which to obtain messages   */
);

extern int
fc_display_fid_1(			/* Displays FFDC Error Identifier,   */
					/* using message 2615-000            */
	fc_eid_t fid			/* FFDC Error Identifier to display  */
);

extern int
fc_init_1(				/* Establishes an FFDC Environment   */
	int option_code			/* Options for establishing FFDC Env */
);

#define	fc_eid_init_1(ffdcid)		/* Initializes FFDC Failure ID to a  */\
					/* empty (null) value                */\
	memset((void *) (ffdcid), (int) 0, sizeof(fc_eid_t))

#define	fc_eid_is_set_1(ffdcid)		/* Indicates if an FFDC Failure ID   */\
					/* contains a value                  */\
	(0 == strcmp((ffdcid), "") ? 1 : 0)

extern int
fc_log_error_1(				/* Records incident information to   */
					/* System Log and AIX Error Log      */
	fc_eid_t *fid,			/* Will contain the FFDC Error ID of */
					/* this incident report upon         */
					/* successful completion             */
	fc_eid_t assoc_fid,		/* FFDC Error Identifier of a        */
					/* previously recorded incident that */
					/* caused this incident to occur     */
					/* (optional)                        */
	char *resource,			/* Software component name           */
	char *lpp_name,			/* LPP name (abbreviated to 16 char) */
	char *source_file,		/* File where incident was detected  */
	char *version,			/* Version identifier of in_src_file */
	int line_pos,			/* Location in "in_src_file" where   */
					/* incident was detected or reported */
	void *reserved,			/* For future use                    */
	int in_event,			/* FFDC Log Event Type: FFDC_EMERG,  */
					/* FFDC_ERROR, FFDC_DEBUG, etc.      */
	unsigned template_id,		/* AIX Error Log Template symbolic   */
					/* name                              */
	void *detail_data,		/* Details on failure, written to the*/
					/* Detail Data section of the AIX    */
					/* Error Log entry                   */
	size_t detail_len,		/* Length of "detail_data"           */
	char *detail_file,		/* File with details, when the space */
					/* in the AIX Error Log entry is not */
					/* enough                            */
	char *bsdmsg,			/* Message text to be written to the */
					/* System Log for this incident      */
	...				/* Variable arguments, substituted   */
					/* into "bsdmsg" when recording the  */
					/* message to the System Log         */
);

extern int
fc_push_stack_1(			/* Records incident information to   */
					/* the FFDC Error Stack file estab-  */
					/* lished by fc_init()               */
	fc_eid_t *fid,			/* FFDC Error Identifier for this    */
					/* recording is returned here        */
	fc_eid_t assoc_fid,		/* FFDC Error Identifier of a related*/
					/* incident record, to show that this*/
					/* record is associated with a pre-  */
					/* viously recorded incident         */
	char *resource,			/* Name of the softare component that*/
					/* has detected and reported this    */
					/* incident                          */
	char *lpp_name,			/* Licensed program product name     */
					/* (abbreviated to 16 characters     */
	char *source_file,		/* Name of the source code file that */
					/* detected and reported the incident*/
	char *version,			/* Version of "source file", speci-  */
					/* fied in SID format rr.vv.ll.ff    */
	int line_pos,			/* Position within "source_file"     */
					/* where the incident was detected & */
					/* reported - usually a line number  */
	void *reserved,			/* DO NOT USE - reserved for future  */
	char *detail_data,		/* Details on the incident, intended */
					/* for use by problem investigators  */
					/* and IBM Customer Support          */
	char *detail_file,		/* Same as "detail_data", except it  */
					/* names a file that contains this   */
					/* info (when info is lengthy)       */
	char *msg_catalog,		/* Name of an NLS message catalog    */
					/* that contains a short descriptive */
					/* message on the incident being     */
					/* reported                          */
	int msg_set,			/* Message set within the NLS message*/
					/* catalog that contains the short   */
					/* description message               */
	int msg_number,			/* Specific message that describes   */
					/* the nature of the incident        */
	char *default_msg,		/* ASCII character string that desc- */
					/* ribes the nature of the incident  */
					/* - used when the NLS message cannot*/
					/* be obtained                       */
	...				/* Variable arguments, substituted   */
					/* into the description message      */
);

extern int
fc_test_stack_1(void);			/* Indicates if FFDC Environment has */
					/* been established                  */
#endif	/* (FC_VERION == 1) || defined(FC_ALL_VERSIONS) */

#ifdef	__cplusplus
} // end extern "C"
#endif	/* __cplusplus */

#endif	/* _H_FFDC */
