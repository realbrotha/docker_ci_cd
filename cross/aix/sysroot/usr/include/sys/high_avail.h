/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernel/sys/high_avail.h 1.6.3.1                         */
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
/* "@(#)07  1.6.3.1  src/bos/kernel/sys/high_avail.h, sysproc, bos53J, j2006_30B0 7/24/06 16:59:28" */
/*
 * COMPONENT_NAME: SYSPROC
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 83
 *
 * Copyright (C) Bull S.A. 1999
 * LEVEL 1, 5 Year Bull Confidential Information
 */


#if !defined(_H_HIGH_AVAIL)
#define _H_HIGH_AVAIL


#include <sys/processor.h>
#include <sys/err_rec.h>

/*
 * High-availability related event
 *
 * This structure must be a pinned, dynamically allocated data structure.
 * The kernel needs it for an unpredictable, long period
 * (the kernel will free it) unless "pal_command(PALCMD_HA_REPORT, ...)"
 * returns an error, then this structure is no longer referenced by the kernel,
 * it can be freed.
 *
 * Note: An event is private to a given RPD* procedure if its state is neither
 *       HA_INITIAL nor HA_ABORTED / HA_SUCCESS.
 */
typedef struct _ha_e {
    uint         _magic;        /* Identifies the kind of the event */
	
    volatile int _state;        /* State of the event handling */
    int          _prev_state;   /* Previous state of the event */
    int          _pad;
    char 	 resource_name[ERR_NAMESIZE];   /* For error logging... */
    int 	 (*_fun)(struct _ha_e *);/* "free()" function for event buffer */

#if !defined(__64BIT__)
    int          _pad1;
#endif

    unsigned long long _res1,   /* Reserved for the global event list */
                       _res2;   /* management */
    unsigned long long _res3;
    union {
        struct {                /* Predictive processor failure */
            cpu_t failing_cpu;  /* Physical ID of failing processor */
            cpu_t failing_lcpu; /* Logical ID of failing processor */
            cpu_t repl_cpu;     /* Physical ID of replacing processor */
                                /*      -1 means this field not used or */
                                /*      no replacing processor available */
            cpu_t repl_lcpu;    /* Logical ID of replacing processor */
            ushort it_domain;   /* Interrupt domain for NUID -- */
                                /*      future extension */
            ushort numa_sradid; /* NUMA node ID -- future extension */
        } _cpu; 
	struct {
	    cpu_t capacity;	/* capacity to remove */
	    short nvcpus;	/* # of vcpus to remove if we can't 
				   remove requested capacity */
	    short actual_vcpus;	/* actual number of online vcpus */
	} _shcpu;
	struct {
	    unsigned long long failing_addr; /* failing memory address */
	} _mempage;
        /* ... */               /* Additional kind of events -- */
                                /*      future extension */
    } _u;
} ha_event_t;

/*
 * _magic: kinds of events
 */
#define HA_FREE     	0x46524545  /* "FREE" free HA event structure */
#define HA_CPU_FAIL 	0x43505546  /* "CPUF" */
#define HA_SHCPU_FAIL	0x53485046  /* "SHPF" */
#define HA_MEM_FAIL 	0x4D454D46  /* "MEMF" */
#define HA_CPU_REMOVE  	0x43505552  /* "CPUR" -- DR CPU REMOVE */
#define HA_CPU_ADD  	0x43505541  /* "CPUA" -- DR CPU ADD */
#define HA_CPU_SPARE  	0x43505553  /* "CPUS" -- DR CPU SPARE */
#define HA_CPU_FAILED_AND_REMOVED	0x43415052	/* "CAPR" -- capacity removed */

/*
 * state of the event handling
 */
#define HA_INITIAL      0       /* New event */
#define HA_NONE         -1      /* Not a valid event -- disregard the content */

#if defined(_KERNSYS)
#define HA_STARTED      1       /* RPD* procedure has been started */
#define HA_UNBIND       0x10    /* Starting thread unbind */
#define HA_UNBIND_W     0x18    /* Waiting for thread unbind */
#define HA_UNBIND_DONE  0x1e    /* Thread unbind done */
#define HA_HAEH         0x20    /* Starting HAEHs */
#define HA_HAEH_DONE    0x2e    /* HAEHs done */
#define HA_PHASE_I1     0x30    /* Interrupt re-route phase I1 */
#define HA_PHASE_I1_D   0x3e    /* Interrupt re-route phase I1 done */
#define HA_MK_STOP      0x40    /* Making "stopproc" started */
#define HA_MK_STOP_W    0x48    /* "make_stopproc()" waits */
#define HA_MK_STOP_D    0x4e    /* "make_stopproc()" done */
#define HA_STOPP        0x50    /* "stopproc" started */
#define HA_STOPP_RQ     0x55    /* "stopproc" empties run queue */
#define HA_STOPP_DONE   0x5e    /* "stopproc" done */
#define HA_PHASE_I2     0x80    /* Interrupt re-route phase I2 */
#define HA_PHASE_I2_D   0x8e    /* Interrupt re-route phase I2 done */
#define HA_SWAP         0x90    /* Starting processor swap */
#define HA_SWAP_DONE    0x9e    /* Processor swap done */
#define HA_TRB          0xb0    /* Starting TRB migration */
#define HA_TRB_DONE     0xbe    /* TRB migration done */
#define HA_WD           0xc0    /* Starting watch-dog migration */
#define HA_WD_DONE      0xce    /* Watch-dog migration done */
#define HA_PRE_ABORTED  0xff    /* Failure - event handling cancelled -- */
                                /*      event remains private to procedure */
#endif /* #if defined(_KERNSYS) */

#define HA_SUCCESS      0x100   /* Event successfully handled */
#define HA_ABORTED      0x200   /* Failure - event handling cancelled */

/*
 * Argument for ioctl(fd, MIOHA, ...)
 */
struct ha_argument {
    uint        event_mask;     /* Mask of the events to be handled */
    uint        retry_mask;     /* Retry aborted/cancelled events */
    uint        cancel_cause;   /* Cause of cancelling event */
    uint	flags;		/* IOCTL commands */
    uint        _reserved[3];
    long long   cancel_data;    /* Details about aborted/cancelled event */
                                /*      if HA_TH_MIGR: process ID */
                                /*      if HA_HAEH_MIGR: resorce name */

    ha_event_t  event;          /* High-availability event */
};

/*
 * flags: Commands to ioctl()
 */
#define	HA_GET_FAIL_RES		1
#define	HA_FAIL_RES_STATUS 	2

/*
 * Events to be handled
 */
#define HA_RPDP 1               /* "RPD of processor" event */
#define HA_RPDM 2               /* "RPD of memory" event */

/*
 * Cause of Aborted/Cancelled events (in error log)
 */
#define HA_DONE         0       /* Event successfully handled */
#define HA_NO_PAL       1       /* Lack of PAL support */
#define HA_TH_MIGR      2       /* A user thread/process won't migrate */
#define HA_HAEH_MIGR    3       /* A HAEH won't migrate */
#define HA_FEW_CPU      4       /* No enough processors left */
#define HA_IT_ERR       5       /* Interrupt re-route fails */
#define HA_SYNC_ERR     6       /* System freeze fails */
#define HA_KTH_MIGR     7       /* A kernel thread/process won't migrate */
#define HA_MTRC_ERR     8       /* Error in mtrc_addcpu */
#define HA_BS_PROC_ERR  9       /* Error in invoke_start_bs_proc */
#define HA_OTHER_ERR    100     /* Other error */

/*
 * The "cancel_cause" field in the error log includes the values from the
 * "cancel_cause" field in the "struct ha_argument". In addition, "ha_star"
 * may use:
 */
#define HA_CPUGUARD_OFF 200     /* Error log for cpuguard disabled */


/*
 * High-availability event handler related definitions.
 */

/* Event descriptor used as input argument for the HAEHs */
typedef struct {
    uint _magic;                /* Identifies the kind of the event */ 
                                /*      (same as for "ha_event_t" above) */
    union { 
        struct {                /* Predictive processor failure */ 
            cpu_t dealloc_cpu;  /* Logical ID of processor to be de-allocated */
                                /* In DR, dealloc_cpu is the last bindID which
				 * is getting deallocated*/
                                
            ushort domain;      /* Interrupt domain -- future extension */ 
            ushort nodeid;      /* CPU node ID -- future extension */ 
            ushort reserved3;   /* Future extension */ 
            uint _reserved[4];  /* Future extension */
        } _cpu; 
        /* ... */               /* Additional kind of events -- */ 
                                /*      future extension */ 
    } _u;
} haeh_event_t;


/* Structure used to register an HA handler */
typedef struct _ha_handler_ext_ {
                                        /* Function to be invoked */
    int         (*_fun)(long long, haeh_event_t *);
    long long   _data;                  /* Private data for (*_fun)() */
    char        _name[sizeof(long long) + 1];
} ha_handler_ext_t;


/* An HA handler should return one of the following codes: */
#define HA_ACCEPTED     0       /* Positive acknowledgement */
#define HA_REFUSED      -1      /* Negative acknowledgement */


#if defined(_KERNSYS)

#define NOBODY  -1              /* For "ha_rpd_pid" */

/* Structure used to keep the HA handler registration inside the kernel */
typedef struct _haeh_ {
    struct _haeh_ *_next;               /* For linking */
                                        /* Function to be invoked */
    int           (*_fun)(long long, haeh_event_t *);
    long long     _data;                /* Private data for (*_fun)() */
    union {
        long long _name8;               /* Component name -- when accessed as */
                                        /*      "_name8", then the ending */
                                        /*      '\0' is not guaranteed */
        char      _name[sizeof(long long) + 1];
    } _u;
} ha_handler_t;

/*
 * Special return codes (when not a process ID is returned) from
 * "migrate_proc_th()" and "look_up_bound_threads()":
 */
#define NO_THREAD       (pid_t) 0       /* No more bound thread */
#define SIGNALED        (pid_t) -1      /* Signal received */
#define OTHER_ERR       (pid_t) -3      /* Other errors... */

#endif /* #if defined(_KERNSYS) */


#endif /*#if !defined(_H_HIGH_AVAIL)*/
