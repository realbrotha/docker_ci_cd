/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/usr/include/diag/diag_log.h 1.5.1.10                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1999,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*static char sccsid[] = "@(#)41  1.5.1.10  src/bos/usr/include/diag/diag_log.h, cmddiag, bos53V, v2008_51A9 12/18/08 16:01:15";                        */
/*
 *   COMPONENT_NAME: CMDDIAG
 *
 *   FUNCTIONS: Diag Log header file.
 *
 *   ORIGINS: 27
 *
                                                                            */

#ifndef  _H_DIAGLOG
#define  _H_DIAGLOG

/****************************************************************************/
/* Log Lock Defines                                                         */
/****************************************************************************/

#define  DLOG_LOCK_FILE        "/etc/objrepos/diag_log_lock"
#define  DLOG_LOCK_TIMEOUT       3
#define  DLOG_LOCK            TRUE
#define  DLOG_UNLOCK          FALSE

/****************************************************************************/
/* Display defines                                                          */
/****************************************************************************/

#define  DLOG_MAX_FSIZE 1000000 
#define  DLOG_MIN_FSIZE 100000 
#define  DLOG_INC_FSIZE 100000 
#define  DLOG_DEF_FSIZE 100000
#define  DLOG_DEF_FNAME "/var/adm/ras/diag_log"

/****************************************************************************/
/* Taken from Odiag.h & tm_input.h                                          */
/****************************************************************************/

#define  NAME_SIZE            16 
#define  LOC_SIZE             16
#define  MAX_SRN_SIZE         10
#define  MAX_FRUPN_SIZE       20
#define  MAX_ENTRYID_SIZE      5
#define  LATEST_ENTRY_VER      3


/* Taken from da.h for platform errors */
#define  RPA_LOC_SIZE            80
#define  RPA_FRU_PN_SIZE         8
#define  RPA_FRU_SN_SIZE_NN      13
#define  RPA_PROC_SIZE           8
#define  RPA_CCIN_SIZE_NN        5
#define  RPA_DUMP_FN_SIZE	 40
#define  RPA_REPORT_EXTERNALLY	 0x2000 /* action flag value */

/* Internal SRC defines */
#define  MAX_SRC_SIZE		80	/* buffer for 72 character SRC */
#define  DISPLAY_SRC_SIZE	 8	/* Display 8 digits of the SRC */

/****************************************************************************/
/* Log Types                                                                */
/****************************************************************************/

#define  INFO	'I'
#define  NTF	'N'
#define  ERR	'E'
#define  SRN 	'S'
#define  SA	'A' 
#define  EXER	'X'
#define  RFRU   'F'

/****************************************************************************/
/* Log Events - Controller & DA                                             */
/****************************************************************************/

#define  DC_START	"DC00"
#define  DC_MISS_SRN	"DCF0"
#define  DC_NEW_SRN	"DCF1"
#define  DC_ERR_OTHER	"DCE1"
#define  DA_NTF		"DA00"
#define  DA_MENUGOAL	"DA01"
#define  DA_SRN		"DAF0"
#define  DA_ELA_SRN	"DAFE"
#define  DA_SRN_SRC	"DAFF"	/* SRNs with an platform SRC */
#define  DA_ERR_OPEN	"DAE0"
#define  DA_ERR_OTHER	"DAE1"
#define  REPAIR         "RP00"
#define  DL_CORRUPT     "DL00"

/****************************************************************************/
/* Log Events - Exerciser                                                   */
/****************************************************************************/

#define  EX_START	"EX00"
#define  EX_STOP	"EX99"
#define  EX_MISCOMPARE	"EX01"
#define  EX_HARD_ERR	"EX02"

/****************************************************************************/
/* Miscellaneous                                                            */
/****************************************************************************/

#define  SRN_ERROR          "SRN"
#define  ERROR_FS            -2        /* Unable to change logsize because  
                                          of fs                             */
#define  DCNEW_TMODE_N 0x405           /* Set testmode to normal & new      */
#define  DCNEW_TMODE_S 0x401           /* Set testmode to service & new     */
#define  RTO_DLOG_POS    9             /* DLOG Column in runtime options    
                                          object                            */
#define  MNUM_SIZE     7               /* menu number size*/

/****************************************************************************/
/* FRU information delimeters                                               */
/****************************************************************************/

#define  FRUB_DELIM    "%"
#define  SRN_DELIM     "*"
#define  CAT_DELIM     ":"
#define  SET_DELIM     "/"
#define  MSG_DELIM     ","
#define  FRUs_DELIM    "+"
#define  FCONF_DELIM   "!"
#define  FLOC_DELIM    "@"
#define  FPN_DELIM     "^"
#define  END_DELIM     "#"

/* fru format 
1 FRU: %dname*srn:rcat,rset,rmsg+fname@FLOC!CONF:FCAT,FSET,FMSG^PN#
2 FRUS:%DNAME*SRN:RCAT,RSET,RMSG+FNAME@FLOC!CONF:FCAT,FSET,FMSG^PN#
                                +FNAME@FLOC!CONF:FCAT,FSET,FMSG^PN#
*/
/****************************************************************************/
/* Search Defines                                                           */
/****************************************************************************/

#define  DEVICE_MASK   0x0001
#define  TYPE_MASK     0x0002
#define  LOC_MASK      0x0004
#define  ID_MASK       0x0008
#define  START_MASK    0x0010
#define  END_MASK      0x0020
#define  DLOGSEQ_MASK  0x0040

/****************************************************************************/
/* MACROS */
/****************************************************************************/
#define  DLOG_GET_OLDEST_INDEX(i)\
 ((i->dlAtt->wrapCount)  && (i->dlAtt->lastIndex != i->dlAtt->numEntries-1)) \
?  i->dlAtt->lastIndex+1 : 0                             

#define  DLOG_INCR_EINDEX(dlogInfo,index)  (index != \
dlogInfo->dlAtt->lastIndex) ? ++index : 0

#define  DLOG_DECR_EINDEX(dlogInfo,index)  \
   (index != 0) ? --index : dlogInfo->dlAtt->numEntries-1

/****************************************************************************/
/* Log Structures - Version 1                                               */
/****************************************************************************/

typedef struct resource_v1 {
    char name[NAME_SIZE];
    char location[NAME_SIZE];
    short set;
    short msg;
    char catName[NAME_SIZE];
} resource_t_v1;

typedef struct _logEntry_v1 {
    char type;                         /* Log Type                          */
    char identifier[MAX_ENTRYID_SIZE]; /*                                   */
    int timestamp;                     /*                                   */
    unsigned int seqNum;               /* order in which event is logged    */
    unsigned int session;              /* Diag Session's PID                */
    unsigned int testMode;             /* Diagnostics test mode - hex value */
    resource_t_v1 *res_p;              /* Resource information              */
    int resSize;                       /* Size of resource info             */
    char *errorInfo;                   /* Error information                 */
    int errorSize;                     /* Size of error info                */
} dlEntry_v1;

typedef struct _log_einfo_v1 {
    int version;
    char logType;
    unsigned int size;
    unsigned int offset;
} dl_einfo_v1;

/****************************************************************************/
/* Log Structures - Version 2                                               */
/****************************************************************************/

typedef struct resource {
    char name[NAME_SIZE];
    int locSize;
    char *location;                    /* Logical or Physical               */
    short set;
    short msg;
    char catName[NAME_SIZE];
} resource_t;

typedef struct _logEntry {
    char type;                         /* Log Type                          */
    char identifier[MAX_ENTRYID_SIZE]; /*                                   */
    unsigned int el_identifier;        /* AIX error log identifier          */
    int timestamp;                     /*                                   */
    unsigned int seqNum;               /* order in which event is logged    */
    unsigned int el_seqNum;            /* AIX error log identifier          */
    unsigned int session;              /* Diag Session's PID                */
    unsigned int testMode;             /* Diagnostics test mode - hex value */
    resource_t *res_p;                 /* Resource information              */
    int resSize;                       /* Size of resource info             */
    void *errorInfo;                   /* Error information                 */
    int errorSize;                     /* Size of error info                */
} dlEntry_v2;

typedef struct _log_partition {
    int version;
    short callHomeFlg;
    int strSize;                        /* Length of all char * string */
    char *name;                         /* Partition name */
    char *id;                           /* Partition id */
    char *hostname;                     /* hostname - uname -n */
    char *typeModel;			/* machine type and model */
    char *sn;				/* machine serial number */
    char *dev_typeModel;                /* Failing device type and model */
    char *dev_sn;                       /* Failing device sn */
} dl_partition;       

typedef struct _logEntry3 {
    char type;                         /* Log Type                          */
    char identifier[MAX_ENTRYID_SIZE]; /*                                   */
    unsigned int el_identifier;        /* AIX error log identifier          */
    int timestamp;                     /*                                   */
    unsigned int seqNum;               /* order in which event is logged    */
    unsigned int el_seqNum;            /* AIX error log identifier          */
    unsigned int session;              /* Diag Session's PID                */
    unsigned int testMode;             /* Diagnostics test mode - hex value */
    resource_t *res_p;                 /* Resource information              */
    int resSize;                       /* Size of resource info             */
    void *errorInfo;                   /* Error information                 */
    int errorSize;                     /* Size of error info                */
    dl_partition *partition;
} dlEntry;     

/****************************************************************************/
/* Log Structures                                                           */
/****************************************************************************/
/* An array of dl_info structs is used to keep track of                     */
/* all entries in the log file. It is stored in the log file.               */

typedef struct _log_einfo {
    int version;                       /* Entry Version                     */
    char logType;                      /* Log Type - I,S,N,E,X              */
    unsigned int size;                 /* Entry Size                        */
    unsigned int offset;               /* Offset from the file's beginning  */
/* char resourceName[NAME_SIZE];	Name of resource */
} dl_einfo;

typedef struct _log_att {
    int version;                       /* Version                           */
    unsigned int numEntries;           /* number of log entried             */
    unsigned int lastIndex;            /* index of latest entry             */
    unsigned int nextSeqNum;           /* sequence number of next log entry */
    unsigned int maxLogSize;           /* maximum size of log               */
    unsigned int arrayOffset;          /* array offset                      */
    unsigned int wrapCount;            /* number of times file has wrapped  */
} dl_att;

typedef struct _log_info {
    int fd;                            /* File descriptor                   */
    int lockId;                        /* ODM Lock id                       */
    dl_att *dlAtt;                     /* Pointer to log attributes         */
    dl_einfo *dlArray;                 /* Pointer to log array              */
} dl_info;

/****************************************************************************/
/* Structures used for SRN information                                      */
/****************************************************************************/

typedef struct _log_descText {
    char catName[NAME_SIZE];           /* Catalog name                      */
    short set;                         /* set number                        */
    short msg;                         /* message number                    */
} dl_descText;

typedef struct _log_frus {
    char name[NAME_SIZE];              /* fru name                          */
    int conf;                          /* confidence                        */
    int locSize;                       /* size of location code string      */
    char *locCode;                     /* Location code - Logical or        
                                          Physical                          */
    char partNumber[MAX_FRUPN_SIZE];   /* FRU Part number                   */
    dl_descText fruDesc;               /* FRU description                   */
    struct _log_frus *nextfru;         /* Next FRU                          */
} dl_frus;

typedef struct _log_srnDetails {
    char name[NAME_SIZE];              /* max size of dname                 */
    char srn[MAX_SRN_SIZE];            /* SRN                               */
    dl_descText frubDesc;              /* Reason                            */
    dl_frus frus;                      /* FRUs                              */
} dl_srnDetails;

typedef struct _log_mgoal {
    char id[MNUM_SIZE];                /* 6 digit Menu number */
    char *text;                        /* Translated menugoal text */
} dl_mgoal;   

typedef struct _log_fru_src {
    int  type;
    char priority[2];
    char loc[RPA_LOC_SIZE];
    char frupn[RPA_FRU_PN_SIZE]; 
    char frusn[RPA_FRU_SN_SIZE_NN];
    char ccin[RPA_CCIN_SIZE_NN];
    char proc_id[RPA_PROC_SIZE];
    struct _log_fru_src *nextfru;
} dl_fru_src;

typedef struct _log_srn_src {
    char name[NAME_SIZE];              /* max size of dname                 */
    char src[MAX_SRC_SIZE]; 	       /* SRC                               */
    char *errorText;		       /* Description of error              */
    dl_descText frubDesc;              /* Source data for errorText         */
    dl_fru_src *frus;                  /* FRUs or Procedure Ids             */
    char crid[2];		       /* Platform log creator id 	    */	
    unsigned int plid;		       /* Platform log id 	 	    */	
    unsigned int action_flags;	       /* Platform error action             */
    unsigned int subsysid;	       /* Subsystem Id			    */
    unsigned int event_sev;	       /* Event Severity		    */
    unsigned int refc2;
    unsigned int refc3;
    unsigned int refc4;
    unsigned int refc5;
    unsigned int refc6;
    unsigned int refc7;
    unsigned int refc8;
    unsigned int refc9;
} dl_srn_src;    

/****************************************************************************/
/* Log Search                                                               */
/****************************************************************************/
typedef struct _log_search {
    int mask;
    char deviceName[NAME_SIZE];
    int type;
    char id[MAX_ENTRYID_SIZE];
    char *location;
    unsigned int startTime;
    unsigned int endTime;
    unsigned int dlogseq;
} dlSearch;

/****************************************************************************/
/* Exerciser Error Structure                                                */
/****************************************************************************/
typedef struct _log_exerciserError {
    short value1;
    short value2;
    short value3;
    short value4;
    short value5;
    short value6;
    short value7;
    short value8;
    char *dlogStr;
} dlExerErr;

typedef struct replacedFRUInfo {
    int dlogSeqNumber;
    int status;
    char name[NAME_SIZE];              /* fru name                          */
    char partNumber[MAX_FRUPN_SIZE];
    unsigned int replacementTime;
    int locSize;
    char *locCode;
    int descSize;
    char *description;
    struct replacedFRUInfo *nextFru;
} dlRfru;

/************************Event Log API structures begin**********************/

typedef struct _log_query_crit {
    char *pathname;             /*Path of diagnostic event log file to search*/
    char type;                  /*Request entries matching a log template*/
    char identifier[5];         /*Request entries matching identifier*/
    char *name;                 /*Request entries matching Resource Name*/
    unsigned int session;       /*Request entries matching Diag Session's PID*/
    char *location;             /*Pointer to logical or physical location code*/
    unsigned int firstSeqNum;   /*Request entries with this sequence number or
                                  higher*/
    unsigned int lastSeqNum;    /*Request entries with this sequence number or
                                  lower*/
    unsigned int el_identifier; /*Request entries matching this error log
                                  identifier*/
    unsigned int elSeqFirst;    /*Request entires with this error log sequence
                                  number or higher*/
    unsigned int elSeqLast;     /*Request entries with this error log
                                  sequence number or lower*/
    unsigned int numDays;       /*Request entries x number of days backward or
                                  forward*/
    struct tm *startDate;       /*Request entries after this date*/
    struct tm *endDate;         /*Request entries before this date*/
    char *srn;                  /*Request entries matching this SRN*/
    char *mgoal;                /*Request entries matching this menugoal*/
    unsigned int maxEntries;    /*Maximum number of entries to return*/
    char *src;			/*Request entries matching this SRC*/
    unsigned int openEvents;	/*Request only entries newer than the last
				  repair action for a given resource. */
    char reserved[100-(sizeof(char*))-(sizeof(unsigned int))];
				/*Reserved for future use*/
} query_log;

typedef struct _log_query_fru {
    char *name;                 /* FRU name */
    int locSize;                /* size of location code string */
    char *locCode;              /* Location code - logical or physical */
    char *partNumber;           /* FRU Part number */
    char *fruDesc;              /* FRU's description text */
    char *refCode;		/* FRU's reference code (NULL if non-existant)*/
    struct _log_query_fru *nextfru;     /* Pointer to next FRU in the list */
} query_fru;

typedef struct _log_srn {
    char *name;                 /* SRN's device name */
    char *srn;                  /* SRN's number */
    char *errorText;            /* SRN's description text */
    query_fru *frus;            /* Pointer to SRN's fru list */
} dl_srn;

typedef struct _log_menugoal {
    char *id;                   /* 6 digit Menu number */
    char *text;                 /* Translated menugoal text */
} dl_menugoal;

typedef struct _log_query_output {
    char type;
    char identifier[5];
    unsigned int el_identifier; /* AIX Error log identifier */
    char *timestamp;            /* Time event was logged */
    unsigned int seqNum;        /* Diagnostic event log sequence number */
    unsigned int el_seqNum;     /* AIX error log sequence number */
    unsigned int session;       /* Diag Session's PID */
    unsigned int testMode;      /* Diagnostics test mode - hex value */
    char *name;                 /* Resource Name */
    char *location;             /* Logical or Physical location code */
    dl_srn *srn;                /* Pointer to SRN information */
    dl_menugoal *mgoal;         /* Pointer to Menugoal information */
    dl_partition *partition;    /* Pointer to partition information */
    dl_srn_src *srn_src;	/* Pointer to SRN w/ SRC */
    char reserved[100-(sizeof (dl_srn_src *))]; /* Reserved for future use */
} query_output;

typedef struct _log_query_results {
    unsigned int numEntries;    /* Number of entries matching query */
    query_output **entryArray;  /* Pointer to entries matching query */
} query_results;

#define FIRST_SEQUENCE_NUM	0
#define LAST_SEQUENCE_NUM	UINT32_MAX
#define IS_CONSOLE_MODE(x)	(x & 0x0001) 
#define IS_ADVANCED_MODE(x)	((x >> 1) & 0x0001)
#define IS_NORMAL_BOOT(x)	((x >> 2) & 0x0001)
#define IS_NETWORK_BOOT(x)	((x >> 3) & 0x0001)
#define IS_ELA_MODE(x)		((x >> 4) & 0x0001)
#define IS_PD_MODE(x)		((x >> 5) & 0x0001)
#define IS_SYSTEM_CHECK(x)	((x >> 6) & 0x0001)
#define IS_LOOP_MODE(x)		((x >> 7) & 0x0001)
#define IS_PRETEST_MODE(x)	((x >> 8) & 0x0001)
#define IS_MISSING_MODE(x)	((x >> 9) & 0x0001)
#define IS_NEW_MODE(x)		((x >>10) & 0x0001)

#define IS_REPORT_EXTERNALLY(x)	((x & RPA_REPORT_EXTERNALLY)? 1: 0) 
#define IS_CALL_HOME_REQD(x)	((x & RPA_CALL_HOME_REQD)? 1: 0) 

/*************************Event Log API structures end***********************/

#ifdef __FULL_PROTO
extern int dlog_open(char *,dl_info **);
extern int dlog_close(dl_info *);
extern int dlog_find_sequence(dl_info *,uint,dlEntry **);
extern int dlog_find_first(dl_info *,char *,dlSearch *,dlEntry **);
extern int dlog_find_next(dl_info *,int,dlSearch *,dlEntry **);
extern int dlog_same_elogId(dlEntry *,uint);
extern int dlog_freeEntry(int,void*);
/* dlog_same_elogId returns one, TRUE, on match. */
extern char *dlog_formatElogResults(dlEntry *);  
extern int elaFrubAlreadyReported(int);
extern int dlog_numMatches (query_log *);
extern int dlog_query (query_log *, query_results *);
extern int dlog_query_cleanup (query_results *); 
#else /* ! __FULL_PROTO */
extern int dlog_open();
extern int dlog_close();
extern int dlog_find_first();
extern int dlog_find_next();
extern int dlog_find_sequence();
/* dlog_same_elogId returns one, TRUE, on match. */
extern int dlog_same_elogId();
extern int dlog_extract();
extern char *dlog_formatElogResults();
extern int dlog_freeEntry();
extern int elaFrubAlreadyReported();
extern int dlog_numMatches ();
extern int dlog_query ();
extern int dlog_query_cleanup (); 
#endif /* __FULL_PROTO */    

#endif
