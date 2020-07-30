/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/procfs.h 1.13.1.1                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/**************************************************************************/
/*                                                                        */
/*   COMPONENT_NAME:  PROCFS  (procfs.h)                                  */
/*                                                                        */
/*   Description:  External header file for /proc file system             */
/*                                                                        */
/**************************************************************************/
/* @(#)17       1.13.1.1  src/bos/kernel/sys/procfs.h, procfs, bos53L, l2007_18B5 4/19/07 17:27:14 */

#ifndef _H_PROCFS_PROCFS
#define _H_PROCFS_PROCFS

#if defined(__cplusplus)
extern "C" {
#endif

/* ILP32/LP64 mode size invariant pointer type */
#ifdef __64BIT__
typedef void * prptr64_t;
#else  /* not __64BIT__ */
typedef unsigned long long prptr64_t;
#endif /* __64BIT__ */

#include <sys/types.h>
#include <sys/m_procfs.h>           /* hardware specific /proc fields */

/*****************************************************************************
 *
 * /proc hardware fault set
 *
 * Hardware fault numbers are analogous to signal numbers.  These
 * correspond to hardware faults.  Setting the appropriate bits in
 * a process's set of traced faults via /proc causes the process to
 * stop each time one of the designated faults occurs so that a
 * debugger can take action.  Use praddset() to set the appropriate
 * bits in a fltset_t.
 *
 ****************************************************************************/

typedef struct fltset               /* hardware fault set */
{
   uint64_t flt_set[4];             /* fault set */
} fltset_t;

#define FLTILL          1           /* illegal instruction */
#define FLTPRIV         2           /* privileged instruction */
#define FLTBPT          3           /* breakpoint instruction */
#define FLTTRACE        4           /* trace trap (single-step) */
#define FLTACCESS       5           /* memory access (e.g., alignment) */
#define FLTBOUNDS       6           /* memory bounds (invalid address) */
#define FLTIOVF         7           /* integer overflow */
#define FLTIZDIV        8           /* integer zero divide */
#define FLTFPE          9           /* floating-point exception */
#define FLTSTACK        10          /* unrecoverable stack fault */
#define FLTPAGE         11          /* recoverable page fault (no signal) */

/*****************************************************************************
 *
 * /proc signal information structures:  The following structures provide
 * 32/64 bit mode invariant mappings for signal related information.
 * The variable names correspond to the names used in sigset64_t, siginfo_t,
 * struct sigaction, and stack_t respectively.
 *
 * Applications should use the /proc macros to manipulate and examine the
 * signal number bits in pr_sigset_t instead of the similar signal macros.
 *
 *       /proc macro       signal macro
 *       -----------       ------------
 *       prfillset         SIGFILLSET
 *       premptyset        SIGINITSET
 *       praddset          SIGADDSET
 *       prdelset          SIGDELSET
 *       prismember        SIGISMEMBER
 *
 ****************************************************************************/

typedef struct pr_sigset
{
   uint64_t ss_set[4];              /* signal set */
} pr_sigset_t;

typedef struct pr_siginfo64
{
   int32_t  si_signo;               /* signal number */
   int32_t  si_errno;               /* if non-zero, errno of this signal */
   int32_t  si_code;                /* signal code */
   int32_t  si_imm;                 /* immediate data */
   int32_t  si_status;              /* exit value or signal */
   uint32_t __pad1;                 /* reserved for future use */
   uint64_t si_uid;                 /* real user id of sending process */
   uint64_t si_pid;                 /* sending process id */
   prptr64_t si_addr;               /* address of faulting instruction */
   int64_t  si_band;                /* band event for SIGPOLL */
   union                            /* signal value */
   {
      prptr64_t sival_ptr;          /* pointer signal value */
      int32_t   sival_int;          /* integer signal value */
   } si_value;
   uint32_t __pad[4];               /* reserved for future use */
} pr_siginfo64_t;

typedef struct pr_sigaction64
{
   union
   {
      prptr64_t __su_handler;       /* addr of user signal handler */
      prptr64_t __su_sigaction;
   } sa_union;
                                    /* Note signal.h contains #defines for
                                     * sa_handler to sa_union.__su_handler and
                                     * sa_sigaction to sa_union.__su_sigaction. */
   pr_sigset_t sa_mask;             /* signal mask */
   int32_t sa_flags;                /* signal flags */
   int32_t __pad[5];                /* reserved for future use */
} pr_sigaction64_t;

typedef struct pr_stack64
{
   prptr64_t ss_sp;                 /* stack base or pointer */
   uint64_t ss_size;                /* stack size */
   int32_t  ss_flags;               /* flags */
   int32_t  __pad[5];               /* reserved for future use */
} pr_stack64_t;

typedef struct pr_timestruc64
{
   int64_t  tv_sec;                 /* 64 bit time_t value      */
   int32_t  tv_nsec;                /* 32 bit suseconds_t value */
   uint32_t __pad;                  /* reserved for future use  */  
} pr_timestruc64_t;

/*****************************************************************************
 *
 * lwpstatus file:  This file in /proc/pid#/lwp/tid#/lwpstatus.
 *                  Struct also in /proc/pid#/pstatus file.
 *
 ****************************************************************************/

#define PRCLSZ          8           /* maximum size of scheduling policy name */
#define PRSYSARGS       8           /* maximum number of syscall arguments */

typedef struct lwpstatus
{
   uint64_t pr_lwpid;               /* specific thread id */
   uint32_t pr_flags;               /* thread status flags */
   char     pr__pad1[1];            /* reserved for future use */
   char     pr_state;               /* thread state */
   uint16_t pr_cursig;              /* current signal */
   uint16_t pr_why;                 /* stop reason */
   uint16_t pr_what;                /* more detailed reason */
   uint32_t pr_policy;              /* scheduling policy */
   char     pr_clname[PRCLSZ];      /* printable scheduling policy string */
   pr_sigset_t pr_lwppend;          /* set of signals pending to the thread */
   pr_sigset_t pr_lwphold;          /* set of signals blocked by the thread */
   pr_siginfo64_t pr_info;          /* info associated with signal or fault */
   pr_stack64_t pr_altstack;        /* alternate signal stack info */
   struct pr_sigaction64 pr_action; /* signal action for current signal */
   uint32_t pr__pad2;               /* reserved for future use */
   uint16_t pr_syscall;             /* system call number (if in syscall) */
   uint16_t pr_nsysarg;             /* number of arguments to this syscall */
   uint64_t pr_sysarg[PRSYSARGS];   /* syscall arguments,
				     * pr_sysarg[0] contains syscall return 
				     * value when stopped on PR_SYSEXIT event */
   int32_t  pr_errno;               /* errno from last syscall */  
   uint32_t pr_ptid;                /* pthread id */
    
   uint64_t pr__pad[9];             /* reserved for future use */
   prgregset_t pr_reg;              /* general and special registers */
   prfpregset_t pr_fpreg;           /* floating point registers */
   pfamily_t pr_family;             /* hardware platform specific information */
} lwpstatus_t;

/*****************************************************************************
 *
 * extended lwpstatus file:  This file in /proc/pid#/lwp/tid#/lwpstatus.
 *
 * This represents the contents of the extended lwpstatus file.
 * An extended lwpstatus aware user can request a read of the lwpstatus
 * file for the entire lwpstatusx size, or can read the legacy lwpstatus size
 * and perform an additional read for the extended context (prextset) at the 
 * offset and size pecified in the pr_family member.
 *
 * If the pr_family.pr_extsize field of the legacy context
 * is non-zero it represents the size of the additional context information.
 * The pr_family.pr_extoff field represents the offset within the file to
 * the extended information.  Note that the offset is relative to the 
 * lwpstatus file when reading /proc/pid#/lwp/tid#/lwpstatus.
 *
 * NOTE: When reading a process pstatus file (/proc/pid#/status), the
 * embedded lwpstatus structure is the legacy structure.  The pr_extoff field
 * of the legacy lwpstatus pr_family member can be used to determine the 
 * offset of the pr_extset relative to the status file.  Since the status
 * file information is already variable in size due to the conditional
 * presence of the syscall entry and exit masks, the prextset may or may
 * not be contiguous with the legacy lwpstatus file.
 *
 ****************************************************************************/
typedef struct lwpstatusx
{
   lwpstatus_t  pr_legacy;	    /* legacy lwpstatus described above */
   prextset_t	pr_ext;		    /* extension, if pr_family.pr_extsize
				     * is non-zero */
} lwpstatusx_t;

/*
 * lwpstatus pr_flags, thread status flags
 */
#define PR_STOPPED      0x00000001  /* thread is stopped */
#define PR_ISTOP        0x00000002  /* thread stopped on an event of interest */
#define PR_DSTOP        0x00000004  /* thread has a stop directive in effect */
#define PR_ASLEEP       0x00000008  /* thread is sleep()ing in a system call */
#define PR_NOREGS       0x00000010  /* no register state provided for thread */

/*
 *lwpstatus pr_why, stop reason
 */
#define PR_REQUESTED    1
#define PR_SIGNALLED    2
#define PR_SYSENTRY     3
#define PR_SYSEXIT      4
#define PR_JOBCONTROL   5
#define PR_FAULTED      6

/*****************************************************************************
 *
 * pstatus file:  This file in /proc/pid#/status file.
 *
 ****************************************************************************/

typedef struct pstatus
{
   uint32_t pr_flag;                /* process flags from proc struct p_flag */
   uint32_t pr_flag2;               /* process flags from proc struct p_flag2 */
   uint32_t pr_flags;               /* /proc flags */
   uint32_t pr_nlwp;                /* number of threads in the process */
   char     pr_stat;                /* process state from proc p_stat */
   char     pr_dmodel;              /* data model for the process */
   char     pr__pad1[6];            /* reserved for future use */
   pr_sigset_t pr_sigpend;          /* set of process pending signals */
   prptr64_t pr_brkbase;            /* address of the process heap */
   uint64_t pr_brksize;             /* size of the process heap, in bytes */
   prptr64_t pr_stkbase;            /* address of the process stack */
   uint64_t pr_stksize;             /* size of the process stack, in bytes */
   uint64_t pr_pid;                 /* process id */
   uint64_t pr_ppid;                /* parent process id */
   uint64_t pr_pgid;                /* process group id */
   uint64_t pr_sid;                 /* session id */
   pr_timestruc64_t pr_utime;       /* process user cpu time */
   pr_timestruc64_t pr_stime;       /* process system cpu time */
   pr_timestruc64_t pr_cutime;      /* sum of children's user times */
   pr_timestruc64_t pr_cstime;      /* sum of children's system times */
   pr_sigset_t pr_sigtrace;         /* mask of traced signals */
   fltset_t pr_flttrace;            /* mask of traced hardware faults */
   uint32_t pr_sysentry_offset;     /* offset into pstatus file of sysset_t
                                     * identifying system calls traced on
                                     * entry.  If 0, then no entry syscalls
                                     * are being traced. */
   uint32_t pr_sysexit_offset;      /* offset into pstatus file of sysset_t
                                     * identifying system calls traced on
                                     * exit.  If 0, then no exit syscalls
                                     * are being traced. */
   uint64_t pr__pad[8];             /* reserved for future use */
   lwpstatus_t pr_lwp;              /* "representative" thread status */
} pstatus_t;

/*
 * pstatus pr_flags
 */
#define PR_FORK         0x00000001  /* inherit-on-fork is in effect */
#define PR_KLC          0x00000002  /* kill-on-last-close is in effect */
#define PR_RLC          0x00000004  /* run-on-last-close is in effect */
#define PR_ASYNC        0x00000008  /* asynchronous stop mode is in effect */
#define PR_ISSYS        0x00000010  /* process is a kernel process */
#define PR_PTRACE       0x80000000  /* process controlled by ptrace */

/*
 * pstatus pr_dmodel
 */
#define PR_MODEL_ILP32  0           /* process data model is ILP32 */
#define PR_MODEL_LP64   1           /* process data model is LP64 */

/*****************************************************************************
 *
 * lwpsinfo file:  This file in /proc/pid#/lwp/tid#/lwpsinfo.
 *                 Struct also in /proc/pid#/psinfo file.
 *
 ****************************************************************************/

typedef struct lwpsinfo
{
   uint64_t pr_lwpid;               /* thread id */
   prptr64_t pr_addr;               /* internal address of thread */
   prptr64_t pr_wchan;              /* wait addr for sleeping thread */
   uint32_t pr_flag;                /* thread flags */
   uchar_t  pr_wtype;               /* type of thread wait */
   char     pr_state;               /* thread state */
   char     pr_sname;               /* printable thread state character */ 
   uchar_t  pr_nice;                /* nice for cpu usage */
   int32_t  pr_pri;                 /* priority, high value = high priority*/
   uint32_t pr_policy;              /* scheduling policy */
   char     pr_clname[PRCLSZ];      /* printable scheduling policy string */
   int32_t  pr_onpro;               /* processor on which thread last ran */
   int32_t  pr_bindpro;             /* processor to which thread is bound */
   uint32_t pr_ptid;                /* pthread id */
   uint32_t pr__pad1;               /* reserved for future use */
   uint64_t pr__pad[7];             /* reserved for future use */
} lwpsinfo_t;

/*
 * lwpsinfo pr_sname
 */
#define PR_SNAME_TSIDL   'I'        /* thread being created */  
#define PR_SNAME_TSRUN   'R'        /* thread runnable */
#define PR_SNAME_TSSLEEP 'S'        /* thread waiting on event */
#define PR_SNAME_TSSWAP  'O'        /* thread swapped */
#define PR_SNAME_TSSTOP  'T'        /* thread stopped */
#define PR_SNAME_TSZOMB  'Z'        /* thread being deleted */

/*****************************************************************************
 *
 * psinfo file:  This file in /proc/pid#/psinfo.
 *
 ***************************************************************************/

#define PRFNSZ  16                  /* exec()ed filename field size */
#define PRARGSZ 80                  /* arguments list field size */

typedef struct psinfo
{
   uint32_t pr_flag;                /* process flags from proc struct p_flag */
   uint32_t pr_flag2;               /* process flags from proc struct p_flag2 */
   uint32_t pr_nlwp;                /* number of threads in process */
   uint32_t pr__pad1;               /* reserved for future use */
   uint64_t pr_uid;                 /* real user id */
   uint64_t pr_euid;                /* effective user id */
   uint64_t pr_gid;                 /* real group id */
   uint64_t pr_egid;                /* effective group id */
   uint64_t pr_pid;                 /* unique process id */
   uint64_t pr_ppid;                /* process id of parent */
   uint64_t pr_pgid;                /* pid of process group leader */
   uint64_t pr_sid;                 /* session id */
   uint64_t pr_ttydev;              /* controlling tty device */
   prptr64_t   pr_addr;             /* internal address of proc struct */
   uint64_t pr_size;                /* process image size in KB (1024) units */
   uint64_t pr_rssize;              /* resident set size in KB (1024) units */
   pr_timestruc64_t pr_start;       /* process start time, time since epoch */
   pr_timestruc64_t pr_time;        /* usr+sys cpu time for this process */
   uint32_t pr__pad2;               /* reserved for future use */
   uint32_t pr_argc;                /* initial argument count */
   prptr64_t   pr_argv;             /* address of initial argument vector in
                                     * user process */
   prptr64_t   pr_envp;             /* address of initial environment vector
                                     * in user process */
   char     pr_fname[PRFNSZ];       /* last component of exec()ed pathname*/
   char     pr_psargs[PRARGSZ];     /* initial characters of arg list */
   uint64_t pr__pad[8];             /* reserved for future use */
   struct   lwpsinfo pr_lwp;        /* "representative" thread info */
} psinfo_t;

/*****************************************************************************
 *
 * Control messages:  These values written to /proc/pid#/ctl and
 *                    /proc/pid#/lwp/tid#/lwpctl files.
 *
 ****************************************************************************/

#define PCSTOP          1           /* direct process or thread to stop, */ 
				    /* and wait for it to stop           */
#define PCDSTOP         2           /* direct process or thread to stop */
#define PCWSTOP         3           /* wait for process or thread to stop */
#define PCRUN           4           /* make runnable after a stop */
#define PCSTRACE        5           /* set signal-trace mask */
#define PCSSIG          6           /* set current signal */
#define PCKILL          7           /* send signal to process or thread */
#define PCUNKILL        8           /* delete signal from pending signal set */
#define PCSHOLD         9           /* define set of held signals */
#define PCSFAULT        10          /* define set of traced hardware faults */
#define PCCFAULT        11          /* clear current fault */
#define PCSENTRY        12          /* set syscall entry mask */
#define PCSEXIT         13          /* set syscall exit mask */
#define PCSET           14          /* set modes */
#define PCRESET         15          /* reset modes */
#define PCUNSET         PCRESET     /* reset modes */
#define PCSREG          16          /* set general registers */
#define PCSFPREG        17          /* set FP registers */
#define PCNICE          18          /* set process "nice" value */
#define PCSVREG         19          /* set vector registers */

#define PR_FAMILY_START 10000       /* Starting number for platform specific */
                                    /* control messages */

/*****************************************************************************
 *
 * PCRUN operand flags.
 *
 ****************************************************************************/

#define PRCSIG          0x00000001  /* clear current signal */
#define PRCFAULT        0x00000002  /* clear current fault */
#define PRSTEP          0x00000040  /* single-step the process */
#define PRSABORT        0x00000080  /* abort syscall */
#define PRSTOP          0x00000100  /* set directed stop request */
#define PRBRANCH        0x00000200  /* taken branch the process */

/*****************************************************************************
 *
 * map file:  This file in /proc/pid#/map
 *
 * Notes:  The map file contains an array of prmap structures, each of which
 *         describes a contiguous virtual address region.  The array of prmap
 *         entries starts at offset 0 in the file.  Array entries continue
 *         until an entry with a pr_size field of 0 and invalid pr_mflags occurs.
 *         There is more data in the map file following the last prmap array
 *         entry.
 *
 ****************************************************************************/

#define PRMAPSZ 64

typedef struct prmap
{
   uint64_t pr_size;                /* size of mapping in bytes */
   prptr64_t pr_vaddr;              /* virtual address base */
   char     pr_mapname[PRMAPSZ];    /* name in /proc/pid/object */
   uint64_t pr_off;                 /* offset into mapped object, if any */
   uint32_t pr_mflags;              /* protection and attribute flags */
   uint32_t pr_pathoff;             /* if map entry is for a loaded object,
                                     * offset into the map file to a
                                     * null-terminated path name followed
                                     * by a null-terminated member name.
                                     * If file is not an archive file, the
                                     * member name is null.
                                     * The offset is 0 if map entry is
                                     * not for a loaded object. */
   prptr64_t pr_alias;              /* virtual address base of an alias 
				     * mapping for this region,
				     * address of 0 means no alias mapping */
   prptr64_t pr_gp;                 /* global pointer for loaded object,
				     * address of 0 means no global pointer */
   uint64_t pr__pad[8];             /* reserved for future use */
} prmap_t;

/*
 * prmap pr_mflags - Protection and attribute flags
 */
#define MA_MAINEXEC     0x80000000  /* main executable for the process */
#define MA_KERNTEXT     0x40000000  /* kernel text region */
#define MA_READ         0x00000004  /* readable by the traced process */
#define MA_WRITE        0x00000002  /* writable by the traced process */
#define MA_EXEC         0x00000001  /* executable by the traced process */
#define MA_SHARED       0x00000008  /* changes are shared by mapped object */
#define MA_BREAK        0x00000010  /* grown by brk */
#define MA_STACK        0x00000020  /* grown automatically on stack faults */

/*****************************************************************************
 *
 * cred file:  This file in /proc/pid#/cred.
 *
 ****************************************************************************/

typedef struct prcred
{
   uint64_t pr_euid;                /* effective user id */
   uint64_t pr_ruid;                /* real user id */
   uint64_t pr_suid;                /* saved user id (from exec) */
   uint64_t pr_egid;                /* effective group id */
   uint64_t pr_rgid;                /* real group id */
   uint64_t pr_sgid;                /* saved group id (from exec) */
   uint64_t pr__pad[8];             /* reserved for future use */
   uint32_t pr__pad1;               /* reserved for future use */
   uint32_t pr_ngroups;             /* number of supplementary groups */
   uint64_t pr_groups[1];           /* array of supplementary groups */
} prcred_t;


/*****************************************************************************
 *
 * sysent file:  This file in /proc/pid#/sysent.
 *
 * The sysent file contains information about the system calls provided
 * to a process.  The file consists of a header section followed by an
 * array of prsyscall structures.
 *
 * Notes on this file:
 * 1)  The entries in the pr_syscall array do not have any specific
 *     ordering.  They are neither in number nor name order.
 * 2)  There may be unused syscall numbers.
 * 3)  The set of syscalls may change during system operation.  Syscalls
 *     may be added or deleted while system is runing.
 * 4)  Different processes may have different syscalls. Do not assume the
 *     same syscall names or numbers across processes.
 * 5)  Fields marked reserved for future use are set to zero, but may
 *     become non-zero in future releases.
 *
 ****************************************************************************/

typedef struct prsyscall
{
   uint32_t   pr_number;            /* syscall number */
   uint32_t   pr_nameoff;           /* offset into sysent file to
                                     * null terminated syscall name */
   uint32_t   pr__pad[6];           /* reserved for future use */
} prsyscall_t;

typedef struct prsysent             /* this struct at offset 0 in sysent file */
{
   uint64_t pr__pad[8];             /* reserved for future use */
   uint32_t pr__pad1;               /* reserved for future use */
   uint32_t pr_nsyscalls;           /* number of entries in prsyscall array */
   prsyscall_t pr_syscall[1];       /* array of syscalls */
} prsysent_t;


typedef struct sysset               /* syscall set */
{
   uint64_t pr_size;                /* number of elements in pr_set array */
   uint64_t pr_sysset[1];           /* array of long longs whose bits indicate
                                     * if syscall of corresponding number is
                                     * to be traced */
} sysset_t;

/*****************************************************************************
 *
 * Macros for manipulating syscall number flags in sysset structure.
 * sp must be a pointer to a sysset structure with the sysset.pr_size
 * field initialized to the number of elements in the pr_sysset array.
 *
 ****************************************************************************/

/* turn on all syscall flags in sysset struct */
#define prfillsysset(sp) \
{ \
   uint64_t _ii_ = ((uint64_t*)(sp))[0]; \
   while(_ii_) ((uint64_t*)(sp))[--_ii_+1] = 0xFFFFFFFFFFFFFFFFULL; \
}

/* turn off all syscall flags in sysset struct */
#define premptysysset(sp) \
{ \
   uint64_t _ii_ = ((uint64_t*)(sp))[0]; \
   while(_ii_) ((uint64_t*)(sp))[--_ii_+1] = 0ULL; \
}

/* turn on specified syscall number in sysset struct */
#define praddsysset(sp, num) \
   ((((int64_t)(num) > 0) && \
     ((uint64_t)((num)-1) < 64*((uint64_t*)(sp))[0])) ? \
    (((uint64_t*)(sp))[(((num)-1)/64+1)] |= (1ULL<<(((num)-1)%64))) : 0)

/* turn off specified syscall number in sysset struct */
#define prdelsysset(sp, num) \
   ((((int64_t)(num) > 0) && \
     ((uint64_t)((num)-1) < 64*((uint64_t*)(sp))[0])) ? \
    (((uint64_t*)(sp))[(((num)-1)/64+1)] &= ~(1ULL<<(((num)-1)%64))) : 0)

/* query if specified syscall number is set in sysset struct */
#define prissyssetmember(sp, num) \
   (((int64_t)(num) > 0) && \
    ((uint64_t)((num)-1) < (64*((uint64_t*)(sp))[0])) && \
    (((uint64_t*)(sp))[(((num)-1)/64+1)] & (1ULL<<(((num)-1)%64))))


/*****************************************************************************
 *
 * Macros for manipulating flags in pr_sigset_t and fltset_t structures.
 * sp must be a pointer to one of pr_sigset_t or fltset_t.
 * flag must be a member of the enumeration corresponding to *sp.
 *
 ****************************************************************************/

/* turn on all flags in set */
#define prfillset(sp) \
        { int _i_ = sizeof(*(sp))/sizeof(uint64_t); \
                while(_i_) ((uint64_t*)(sp))[--_i_] = 0xFFFFFFFFFFFFFFFFULL; }

/* turn off all flags in set */
#define premptyset(sp) \
        { int _i_ = sizeof(*(sp))/sizeof(uint64_t); \
                while(_i_) ((uint64_t*)(sp))[--_i_] = 0ULL; }

/* turn on specified flag in set */
#define praddset(sp, flag) \
        (((unsigned)((flag)-1) < 64*sizeof(*(sp))/sizeof(uint64_t)) ? \
        (((uint64_t*)(sp))[((flag)-1)/64] |= (1ULL<<(((flag)-1)%64))) : 0)

/* turn off specified flag in set */
#define prdelset(sp, flag) \
        (((unsigned)((flag)-1) < 64*sizeof(*(sp))/sizeof(uint64_t)) ? \
        (((uint64_t*)(sp))[((flag)-1)/64] &= ~(1ULL<<(((flag)-1)%64))) : 0)

/* query: != 0 iff flag is turned on in set */
#define prismember(sp, flag) \
        (((unsigned)((flag)-1) < 64*sizeof(*(sp))/sizeof(uint64_t)) \
        && (((uint64_t*)(sp))[((flag)-1)/64] & (1ULL<<(((flag)-1)%64))))


#if defined(__cplusplus)
        }
#endif
#endif  /* _H_PROCFS_PROCFS */
