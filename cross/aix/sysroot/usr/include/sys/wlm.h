/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernel/sys/wlm.h 1.43.5.3                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)21       1.43.5.3  src/bos/kernel/sys/wlm.h, sysproc, bos53J, j2006_37A8 9/14/06 17:41:52 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   ORIGINS: 27, 83
 *
 *
 *   This module contains                  code. -- (IBM
 *   Confidential Restricted when combined with the aggregated
 *   modules for this product)
 *   OBJECT CODE ONLY SOURCE MATERIALS
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988, 1995
 *   All Rights Reserved
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */

#ifndef _H_WLM
#define _H_WLM

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/param.h>
#include <sys/lock_def.h>
#include <sys/rset.h>

/* Values common to most interfaces */
#define WLM_VERSION_FIELD 0xF0000000  /* Version is encoded on upper 4 bits */

#define WLM_VERSION_v1 	  0x10000000
#define WLM_VERSION_v2 	  0x20000000
#define WLM_VERSION_v3 	  0x30000000
#define WLM_VERSION_v4 	  0x40000000
#define WLM_VERSION  	  WLM_VERSION_v4
#define WLM_MUTE          0x01000000  /* Request no error message on stdout */

/* Values for wlm_set */
#define WLM_OFF		       0x000
#define WLM_ACTIVE	       0x001
#define WLM_PASSIVE	       0x002
#define WLM_BIND_RSETS	       0x004
#define WLM_CPUONLY	       0x008
#define WLM_TEST_ON	       0x200
#define WLM_PROCTOTAL          0x100	/* Processes total resource */
#define WLM_CLASSTOTAL         0x400	/* Classes total resource */

/* values for wlmcntrl -q */
#define WLM_NO_PROCTOTAL  0x10
#define WLM_NO_CLASSTOTAL 0x20

/* number of superclasses */
#define WLM_NB_CLASS 69

/* number of slots available for subclasses per subclass */
#define WLM_NB_SUBSLOTS 64

#define WLM_MAX_CLASSES    64   /* Maximum number of user-defined Superclasses */
#define WLM_MAX_SUBCLASSES 61   /* Maximum number of user-defined subclasses   */

#define WLM_TIER_MIN 0          /* Minimum and maximum tier values */
#define WLM_TIER_MAX 9

#define WLM_SHARES_UNDEF    (-1)
#define WLM_MIN_UNDEF       (-1)
#define WLM_SOFTMAX_UNDEF   (-1)
#define WLM_UNIT_UNDEF      (-1)
#define WLM_HARDMAX_UNDEF   (-1)

#define WLM_NYC_NAME        "Unclassified"
#define WLM_UNMANAGED_NAME  "Unmanaged"
#define WLM_DEFAULT_NAME    "Default"
#define WLM_SHARED_NAME     "Shared"
#define WLM_SYSTEM_NAME     "System"

/* Values for wlmflags */
#define SWLMTAGINHERITFORK     0x04000  /* inherit tag across fork */
#define SWLMTAGINHERITEXEC     0x08000  /* inherit tag across exec */
#define SWLMRSET               0x40000  /* Process has a WLM real rset */
#define SWLMRSETFAIL           0x80000  /* Attempt to set WLM real rset has failed */

#define TWLMTAGINHERITFORK     0x02000  /* inherit tag across fork */
#define TWLMTAGINHERITEXEC     0x04000  /* inherit tag across exec */
#define TWLMTAGINHERITPTHREAD  0x08000 /* inherit tag across pthread_create */
#define TWLMRSET               0x40000  /* Process has a WLM real rset */
#define TWLMRSETFAIL           0x80000  /* Attempt to set WLM rest has failed */

/* flags for the 'type' field of rules */
#define WLM_TYP_FIXPRI 1
#define WLM_TYP_PLOCK  2
#define WLM_TYP_64BITS 4

/* Tag length for uthread and ublock struct */
#define WLM_TAG_LENGTH 30

struct wlm_bounds {
    int min;
    int shares;
    union { 
        int softmax;
        char unit[3];           /* when total limit is enabled
                                 * (only filled between commands and library).
                                 * The kernel uses ALWAYS default units. */
    } wlmu;
    long long hardmax;
};

/* time-range structure */
typedef struct {
    unsigned int
            bday:3,             /* begin day: 0-6 */
            eday:3,             /* end day: 0-6 */
            bhour:5,            /* begin hour: 0-23 */
            ehour:5,            /* end hour: 0-23 (24) */
            bmin:6,             /* begin minute: 0-59 */
            emin:6;             /* end minute: 0-59 */
} timerange_t;

/* length of class name element (NOT including final '\0') */
#define WLM_CLASSNAME_LENGTH 16

/* length of eWLM subclass name element (NOT including final '\0') */
#define EWLM_CLASSNAME_LENGTH 27

/* Maximum number of characters in a rule */
#define WLM_RULE_LEN 4096

/* separator of superclass and subclass (as a char) */
#define WLM_SEPARATOR '.'

/*****************************/
/* Resources managed by WLM  */
/*****************************/

#define WLM_RES_CPU 0           /* CPU */
#define WLM_RES_MEM 1           /* Physical Memory */
#define WLM_RES_BIO 2           /* Block IO */
#define WLM_RES_TOTALCPU 3      /* total CPU for a process */
#define WLM_RES_TOTALDISKIO 4   /* total DISKIO for a process */
#define WLM_RES_TOTALCONNECT 5  /* Connection time  */
#define WLM_RES_TOTALPROC 6     /* total Processes */
#define WLM_RES_TOTALTHRD 7     /* total Threads */
#define WLM_RES_TOTALLOGIN 8    /* total Logins */
#define WLM_RES_TOTALRMEM 9	/* Real Memory Limit */
#define WLM_RES_TOTALVMEM 10	/* Virtual Memory Limit */
#define WLM_RES_TOTALLRGPG 11	/* Large Page Limit */
#define WLM_RES_PROCVMEM 12     /* Process Virtual Mem Limit */

/* # of resources */
#define WLM_RES_NB_v1  3  
#define WLM_RES_NB_v2  9
#define WLM_RES_NB_v3  12
#define WLM_RES_NB_v4  13
#define WLM_RES_NB   WLM_RES_NB_v4

/* Accounting data */
typedef uint64_t wlm_key_t;

struct class_descr {
    int tier;
    int inheritance;            /* used as a bit */
    uid_t assign_uid;           /* uid that can assign procs to this class */
    gid_t assign_gid;           /* gid that can assign procs to this class */
    uid_t admin_uid;            /* uid that can administrate subclasses */
    gid_t admin_gid;	        /* gid that can administrate subclasses */
                                /* full class name length is 2*element + '.' + '\0' */
    char name[WLM_CLASSNAME_LENGTH*2+2];
    char localshm;              /* avoid transfer of segments to shared classes */
    char delshm;                /* delete shared segments if process killed */
				/* for virtual memory limit */
    int perm_flag;              /* reserved flag, for classes created in .running */
    uint wlmsched_act;	        /* reserved flag, for cumuled statistics usage: 
                                 * Number of time the wlm statistics have been updated
                                 * since the system has started. */
    wlm_key_t key;              /* class name hash code (used in accounting records) */
    char vmenforce;		/* virtual memory enforcement bit */
    char pad3[3];		/* for future use */
    int pad2[3];		/* for future use */
    struct wlm_bounds res[WLM_RES_NB]; /* per-resources data */
};

#define WLM_NOGUID -1           /* Indicates that no user/group is authorized */

struct class_data {
    struct class_descr descr;
    char rset_name[2*(RSET_NAME_SIZE+1)];
};

struct class_definition {
    struct class_data data;
    char descr_field[1024];
};

struct wlm_args {
    int versflags;              /* careful: versflags moved vs old wlm_args */
    struct class_definition cl_def;
    char confdir[MAXPATHLEN];
};

/* wlm_get_info parameters */
#define WLM_SUB_ONLY       0x01
#define WLM_SUPER_ONLY     0x02
#define WLM_VERBOSE_MODE   0x04
#define WLM_BIO_CLASS_INFO 0x08
#define WLM_BIO_DEV_INFO   0x10
#define WLM_BIO_ALL_DEV	   0x20
#define WLM_BIO_ALL_MINOR  0x40
#define WLM_NOSTAT	   0x80 /* Do not want coherent statistics.
				 * Only class descriptions are wanted */
#define WLM_EWLM_INFO	  0x100 /* EWLM class info */

struct wlm_regul_t {
    long long total;
    long long hwm;
    long long cumpct;
    int consum;
    int desired;
    int rap, srap, urap;
    int srap_low;
    int urap_low;               /* Maximum allowed value for urap */
    int urap_high;              /* Minimum allowed value for urap */
    int reserved[2];            /* reserved for future use */
};

/* update cumulated statistics (used in wlmstat) and hwm */
#define wlm_update_stat_regul(r,current)		\
	(r)->cumpct += (r)->consum;		\
	if ((r)->cumpct < 0) (r)->cumpct = 0;	\
	if (current > (r)->hwm) (r)->hwm = current;

struct wlm_info {
    struct class_descr i_descr;
    struct wlm_regul_t i_regul[WLM_RES_NB];
    int i_class_id;
    int i_cl_pri;
    int i_cl_inuse;
    rpn64_t i_cl_npages;
    int i_cl_change_level;      /* incremented for each ccb entry change */
    int i_cl_nbthreads;    
    int i_cl_nblogins;
    int i_cl_lgpguse;           /* large page memory usage in megabyte units */
    rpn64_t i_cl_nrpages;	/* Num of real memory pages */
    rpn64_t i_cl_nrpagehi;	/* High water mark for real pages */
    cnt64_t i_cl_nvpages;	/* Num of virtual memory pages */
    cnt64_t i_cl_nvpagehi;	/* High water mark for virtual pages */
    int i_cl_state;		/* State of the class */
#define CL_SNONE	0
#define CL_SACTIVE	1
#define CL_SWKILL	2
#define	CL_SKILLING	3
#define CL_SKILLED	4

    int i_cl_event;		/* Event of class */
};

struct wlm_bio_class_info_t {
    union {
        dev_t dev;
        dev32_t d32;
        dev64_t d64;
    } wbc_dev_u;
    class_id_t wbc_cid;
    int wbc_delay;              /* Delay in ms */
    struct wlm_regul_t wbc_regul;
    int reserved[4];            /* reserved for future use */
};
#define wbc_dev		wbc_dev_u.dev

/* Statistics available per device */
#define WBS_RTHRPUT		 0         /* Read Throughput */
#define WBS_WTHRPUT		 1         /* Write Throughput */
#define WBS_REQUESTS             2         /* Nb of request per seconds */
#define WBS_QUEUED               3         /* Nb of request queued */
#define WBS_STARVED              4         /* # of starved requests */
#define WBS_ACTIVITY             5         /* # of starved requests */

#define WBS_MAX                  6

struct wlm_bio_dev_info_t {
    union {
        dev_t dev;
        dev32_t d32;
        dev64_t d64;
    } wbd_dev_u;
    int wbd_active_cntrl;       /* number of active cntrl */
    int wbd_in_queue;           /* number of requests in waiting queue */
    int wbd_max_queued;         /* maximum number of requests in queue */
    int wbd_last[WBS_MAX];      /* Statistics of last second */
    int wbd_max[WBS_MAX];       /* Maximum of last second statistics */
    int wbd_av[WBS_MAX];        /* Average of last second statistics */
    long long wbd_total[WBS_MAX];   /* Total of last second statistics */
    int reserved[4];            /* reserved for future use */
};
#define  wbd_dev	wbd_dev_u.dev

struct wlm_procinfo {
    int version;
    int wlmflags;               /* pv_wlm */
    long long  totalconnecttime;
    long long termtime;
    long long totalcputime;
    long long totaldiskio;
    char classname[2*(WLM_CLASSNAME_LENGTH+1)];
    char tag[WLM_TAG_LENGTH+1];
    long long totalvmem;
};

struct wlm_thrdinfo {
    int version;
    int wlmflags;               /* tv_wlm */
    char classname[2*(WLM_CLASSNAME_LENGTH+1)];
    char tag[WLM_TAG_LENGTH+1];
};


/* operations for wlm_assign() */
#define WLM_ASSIGN_SUPER        1
#define WLM_ASSIGN_SUB          2
#define WLM_ASSIGN_BOTH         (WLM_ASSIGN_SUPER|WLM_ASSIGN_SUB)
#define WLM_UNASSIGN_SUPER      4
#define WLM_UNASSIGN_SUB        8
#define WLM_UNASSIGN_BOTH       (WLM_UNASSIGN_SUPER|WLM_UNASSIGN_SUB)

struct wlm_assign {
    union { pid_t *_pids; uint64_t pad; }
        wa_pid_u, wa_pgid_u;
    int wa_pid_count;
    int wa_pgid_count;
    int wa_versflags;
    int wa_reserved;
    char wa_classname[WLM_CLASSNAME_LENGTH*2+2];
    char pad[6];
};
#define wa_pids		wa_pid_u._pids
#define wa_pgids	wa_pgid_u._pids

typedef struct {
    char        name[WLM_CLASSNAME_LENGTH*2+2];

#define WLM_EVENT_GLOBAL	0
#define WLM_EVENT_RMEM		1
#define WLM_EVENT_VMEM		2
#define WLM_EVENT_VMEM_PRC	3
    int		event;
} wlm_event_t;

/* Library API prototypes */

int wlm_init_class_definition(struct wlm_args *);
int wlm_initialize(int);
int wlm_create_class(struct wlm_args *);
int wlm_delete_class(struct wlm_args *);
int wlm_change_class(struct wlm_args *);
int wlm_read_classes(struct wlm_args *, struct class_definition *, int *);
int wlm_load(struct wlm_args *);
int wlm_set(int*);
int wlm_get_info(struct wlm_args *, struct wlm_info *, int *);
int wlm_assign(struct wlm_assign *);
int wlm_get_bio_stats(dev_t, void *, int *, char *, int );
int wlm_classify(char *, char *, char *, int *);
int wlm_check(char *);
int wlm_check_rule(char *, char *, char *);
int wlm_set_tag(char *, int *);
int wlm_set_thread_tag(char *, int *);
int wlm_class2key(struct wlm_args *, wlm_key_t *);
int wlm_initkey(struct wlm_args *,void **);
int wlm_key2class(struct wlm_args *, wlm_key_t, void *);
int wlm_endkey(struct wlm_args *, void *);
int wlm_listdupkey(struct wlm_args *,void *,char *);
int wlm_get_procinfo(pid_t, struct wlm_procinfo  *);
int wlm_get_thrdinfo(tid_t, pid_t, struct wlm_thrdinfo  *);

/* Error message numbers */

#define WLM_BADVERS	501
#define WLM_NOTINITED	502
#define WLM_ALREADYINIT	503
#define WLM_UNSUPP	504
#define WLM_OPENERR	505
#define WLM_CREATERR	506
#define WLM_MKDIRERR	507
#define WLM_WRITERR	508
#define WLM_REMERR	509
#define WLM_RENAMERR	510
#define WLM_SYMLERR	511
#define WLM_NOMEM	512
#define WLM_NOCLASS	513
#define WLM_RNOCLASS	514
#define WLM_EXISTS	515
#define WLM_MAXCLASSES	516
#define WLM_RMPREDEF	517
#define WLM_NOSUBS	518
#define WLM_HASSUBS	519
#define WLM_SHAREDSUB	520
#define WLM_SHAREDLIM	521
#define WLM_BADDEFSHR	522
#define WLM_BADDEFLIM	523
#define WLM_BADLIMFMT	524
#define WLM_BADSHRFMT	525
#define WLM_BADTIER	526
#define WLM_BADSHARES	527
#define WLM_BADMIN	528
#define WLM_BADSMAX	529
#define WLM_BADHMAX	530
#define WLM_BADCNAME	531
#define WLM_TOOLONG	532
#define WLM_MINSMAX	533
#define WLM_SMAXHMAX	534
#define WLM_SUMMINS	535
#define WLM_BADINHER	536
#define WLM_LOADERR	537
#define WLM_RULESERR	538
#define WLM_SETERR	539
#define WLM_QUERYERR	540
#define WLM_MANYRULES	541
#define WLM_MANYITEMS	542
#define WLM_RULERR	543
#define WLM_BADLIST	544
#define WLM_BADUSR	545
#define WLM_BADRUSR	546
#define WLM_BADUID	547
#define WLM_BADGRP	548
#define WLM_BADRGRP	549
#define WLM_BADGID	550
#define WLM_BADTAG	551
#define WLM_BADTYP	552
#define WLM_NOSHRRULE	553
#define WLM_NOWILDCRD	554
#define WLM_STATERR	555
#define WLM_EMPTYRULE	556
#define WLM_RUNERR	557
#define WLM_BADCONFIG	558
#define WLM_CLASSMIS	559
#define WLM_EMPTYATTR	560
#define WLM_MULTATTR	561
#define WLM_EXCLATTR	562
#define WLM_ATTERR	563
#define WLM_BADATTUSR	564
#define WLM_BADATTGRP	565
#define WLM_BADATTAPP	566
#define WLM_BADATTTAG	567
#define WLM_BADATTTYP	568
#define WLM_TOOMANYATT	569
#define WLM_WILDCRDATT	570
#define WLM_RUNERRATT	571
#define WLM_BADLISATT	572
#define WLM_TOOLONGATT	573
#define WLM_EFAULT	574
#define WLM_NOTCOMPLETE	575
#define WLM_NOTRUNNING	576
#define WLM_ESRCH	577
#define WLM_TOOMANYPID	578
#define WLM_EPERM	579
#define WLM_CANTASSIGN	580
#define WLM_TAGTOOLONG	581
#define WLM_BADFLAGS	582
#define WLM_CANTSETTAG	583
#define WLM_CANTCHECK	584
#define WLM_TOOSMALL	585
#define WLM_BADRSET	586
#define WLM_CHOWNERR    587
#define WLM_LOCKERR     588
#define WLM_ERRNO       589
#define WLM_BADCLNAME   590
#define WLM_BADSUPER    591
#define WLM_NOTASSGND   592
#define WLM_RULTOOLNG   593
#define WLM_NOADMINSUB  594
#define WLM_UNLOADERR   595
#define WLM_NOSYSMAX    596
#define WLM_DUPKEY    	597
#define WLM_READERR	598
#define WLM_BADLOCALSHM 599
#define WLM_IGNRULE	600
#define WLM_REFRULE	601
#define WLM_RSVDNAME	602
#define WLM_BADATTGP    603
#define WLM_ATTGPTOOLNG 604
#define WLM_MULTATTGP   605
#define WLM_ATTGPMISS   606
#define WLM_BADSUBLIMIT 607
#define WLM_BADHARDTOTALLIMIT 608
#define WLM_ATTGPATTR   609
#define WLM_TOTALLIMITOUTOFRANGE  610
#define WLM_NOCONNECT	611
#define WLM_DAEMONFAIL	612
#define WLM_ISLOCKED	613
#define WLM_NOCONFINSET	614
#define WLM_ONEDEFAULT	615
#define WLM_DAEMONCMD	616
#define WLM_NODAEMON	617
#define WLM_TRGAPS	618
#define WLM_CONFNOTFND	619
#define WLM_ISCONFSET	620
#define WLM_BADRANGEF	621
#define WLM_INVRANGE	622
#define WLM_TROVERLAP	623
#define WLM_TRINDEFAULT	624
#define WLM_SUBINVALID	625
#define WLM_NOTCURRENT	626
#define WLM_CONFNOTINSET 627
#define WLM_NOCONFIG	628
#define WLM_SECDS	629
#define WLM_WEEKS	630
#define WLM_BADVMENFORCE 631
#define WLM_BADDELSHM	632
#define WLM_NOSYSLIM	633
#define WLM_NOSHRLIM	634
#define WLM_CLASSLIMIT	635
#define WLM_INVATTR     636

#ifdef _KERNEL

/*
 * structures for ewlm_sample_pid() kernel service
 */

typedef struct ewlm_sample_pid_data
{
    int64_t     cpu_time;       /* microseconds CPU time accumulated    */
                                /* by all threads in the process        */
    int32_t     num_threads;    /* number of threads in the process     */
    int32_t     th_cpu_running; /* number of threads running on a cpu   */
    int32_t     th_cpu_wait;    /* number of threads ready but waiting  */
                                /* to run on a cpu  */
    int32_t     th_page_wait;   /* number of threads waiting for a page */
                                /* fault to complete    */
    int32_t     th_idle;        /* number of threads awaiting an event  */
                                /* or timer     */
    int32_t     th_other;       /* all other threads in a process that  */
                                /* may be waiting on a lock, zombies... */
} ewlm_sample_pid_data_t;

#define EWLM_SAMPLE_PID_DATA_LEN (sizeof(ewlm_sample_pid_data_t))

extern int ewlm_sample_pid(
/* [in] */  pid_t   pid,
/* [in] */  ewlm_sample_pid_data_t *samp,
/* [i/o]*/  int     *samp_len);

#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* H_WLM */


