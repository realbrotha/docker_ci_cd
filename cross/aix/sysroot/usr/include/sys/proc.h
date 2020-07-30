/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/proc.h 1.57.16.6                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1985,2010              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)86       1.57.16.6  src/bos/kernel/sys/proc.h, sysproc, bos53X, x2010_50A5 7/9/10 02:30:32 */
/*
 *   COMPONENT_NAME: SYSPROC 
 *
 *   FUNCTIONS: EXTRACT_NICE
 *              MAYBE_PID
 *              PROCMASK
 *              PROCPTR
 *              SET_NICE
 *              PID_VALIDATE
 *
 *   ORIGINS: 3, 27, 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1985, 1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_PROC
#define _H_PROC

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/timer.h>
#include <sys/resource.h>
#include <sys/m_param.h>
#include <sys/pri.h>
#include <sys/lockl.h>
#include <sys/limits.h>
#include <sys/var.h>
#include <sys/thread.h>

/*
 * Avoid including ras.h by defining eye catcher type as below:
 */
typedef unsigned long	proc_eye_catch_t;

/* 
 *  One structure allocated per uid.  This structure contains the 
 *  pointers to the uidinfo list, uid of the process and current 
 *  number of processes refering to the structure. 
 */
struct uidinfo {
	struct uidinfo	*pu_next;	/* next uidinfo structure */
	struct uidinfo	*pu_prev;	/* previous uidinfo structure */
	uid_t		pu_uid;		/* uid of process */
	long		pu_cnt;		/* # of refering processes */
	int		pu_pad[4];	/* future use */
};
extern struct uidinfo	*get_uidinfo (uid_t uid);
extern void		free_uidinfo (struct uidinfo *uidinfo);

/*
 *  One structure allocated per active process.  Entries that are
 *  in use are pinned to avoid page faults in kernel critical sections.
 *
 *  This structure contains per-process information that is needed
 *  when the process is swapped out.  The per-process data
 *  that is not needed when the process is swapped out is located
 *  in the processes u-block, <sys/user.h>.
 *  If threads are enabled, per-thread data is located in the thread and
 *  uthread structures, <sys/thread.h> and <sys/uthread.h>.
 *
 *  When changes are made here, be sure to update the assembler version
 *  in kernel/ml/proc.m4, too.
 */

#define max_pvproc ((struct pvproc *)v.ve_proc)

struct kernext_svc {
	void    (*kernext_svc_cleanup)(void *);
};

/*
 * Incrementing (interval) fields for advanced accounting records.
 * These are fields that can be summed for aggregation, and cleared
 * at the start of each interval, such as cpu time.
 * This structure is used in struct proc below, and in the process
 * accounting structures.
 *
 * See aacct.h to find out what is represented in each array element,
 * how each is serialized, etc.
 */
#define TRP_NUM_COUNTS	10
struct proc_counts {
		unsigned long long	trp_count[TRP_NUM_COUNTS];
	};

/*
 * Generate the proc structure, but...
 * If the special _32KER_64VMM flag is set (for vmm modules that must
 * run in real 64bit mode in the 32bit kernel), we cannot generate a
 * correct proc structure.
 * So we don't generate one at all.
 */
#ifndef _32KERMODE

struct	proc {

	struct pvproc 	*p_pvprocp;	/* my global process data 	*/
	pid_t		p_pid;		/* unique process identifier	*/
	uint		p_flag;		/* process flags		*/
	uint		p_flag2;	/* More flags			*/
	uint 		p_int;		/* process flags		*/
	uint		p_atomic;	/* process flags                */ 

	/* thread fields */
#ifndef __64BIT_KERNEL
	ushort 		p_threadcount;	/* number of threads		*/
	ushort		p_active;     	/* number of active threads	*/
	ushort		p_suspended;  	/* number of suspended threads  */
	ushort		p_terminating;	/* number of terminating threads*/
	ushort		p_local;      	/* number of "local" threads 	*/
#else 
        uint            p_threadcount;	/* number of threads      	*/
        uint            p_active;     	/* number of active threads	*/
        uint            p_suspended;  	/* number of suspended threads 	*/
        uint            p_terminating;	/* number of terminating threads*/
        uint            p_local;      	/* number of "local" threads 	*/
#endif

        /* fields used by process migration */
        ulong 		p_rss;          /* n of private data pages	*/
        short	  	p_sradassign;  	/* srad assignment		*/ 
        ushort 		p_boundcount;   /* number of bound threads. 	*/
	void 		*p_rs_attinfo;	/* rset attachment 		*/

	/* dispatcher fields */ 
	ulong 		p_pevent;	/* pending events 		*/
	vmhandle_t	p_adspace;	/* process address space	*/

#ifdef __64BIT_KERNEL
#ifdef __ia64
	uint		p_privregions;	/* bitmap of private regions	*/
        ulong           p_rr[3];        /* user regions 0-2             */
        ulong           p_pkr[15];      /* user protection keys 1-15    */
        ulong           p_pkrlru;       /* lru cursor for pkeys         */
#endif /* __ia64 */
#ifdef _POWER
        vmhandle_t      p_adspace_ldr;  /* loader perprocess le segment */

        ulong           p_adtable;      /* process address space        */
#endif /* _POWER */
#endif

	/* signal information */
#ifdef __64BIT_KERNEL
	sigset_t	p_sig;		/* pending signals		*/
	sigset_t	p_sigignore;	/* signals being ignored	*/
	sigset_t	p_sigcatch;	/* signals being caught		*/
	sigset_t	p_siginfo;	/* keep siginfo_t for these	*/
#else
	sigset64_t	p_sig;		/* pending signals		*/
	sigset64_t	p_sigignore;	/* signals being ignored	*/
	sigset64_t	p_sigcatch;	/* signals being caught		*/
	sigset64_t	p_siginfo;	/* keep siginfo_t for these	*/
#endif
	struct ksiginfo	*p_infoq;	/* queue of siginfo_t's		*/

	/* process statistics */
	unsigned long long p_size;	/* size of image (pages)        */
	unsigned long long p_minflt;	/* page fault count - no I/O    */
	unsigned long long p_majflt;	/* page fault count - I/O needed*/
	long long	p_repage;	/* repaging count		*/
	uint 		p_pctcpu;       /* cpu percentage               */
	int	 	p_sched_count;	/* watchdog suspension count 	*/ 
	short		p_cpticks;	/* ticks of cpu time in last sec*/
	short		p_msgcnt;	/* uprintf message count	*/
	uint 		p_majfltsec;	/* maj flts in the last sec     */

	/* scheduler fields */
	char		p_nice;		/* nice for cpu usage		*/
					/* NOTE: PUSER is added into	*/
					/* this field for processes that*/
					/* do not have a fixed priority */
	char		p_sched_pri;	/* most favored swapped thrd pri*/

	/* misc fields */

	int		p_chkblock;	/* n of checkpnt handler blocks */
	void		*p_chkfile;	/* Ptr to chkfile structure 	*/
	void 		*p_prtrcset;	/* procfs trace set 		*/
#ifndef __64BIT_KERNEL
	void 		*p_lgpage;	/* for shmat SHM_LGPAGE	option	*/
#endif

	struct posix_tmr *p_rt_timer[_POSIX_TIMER_MAX]; /* posix rt timers */
	struct cputime_clock p_clock;   /* posix process cpu-time clock */
	ushort p_io_priority;		/* per-process I/O priority */

	/*
	 * Relatively static fields for advanced accounting.
	 * These are protected by the pv_lock_d.
	 */
	time_t			p_memory_lbolt;   /* lbolt at get_mem_stats */
	unsigned long long	p_interval_start; /* interval start, TBs */

	struct proc_counts p_acct;		/* accounting counters	*/

        struct diskiostat {
            unsigned long long      inbytes;    /* bytes of input disk I/0 */
            unsigned long long      outbytes;   /* bytes of output disk I/0 */
            unsigned long long      logbytes;   /* bytes of I/O to/from log device */
            unsigned long long      logops;     /* number of log I/O operations */
            unsigned long long      inops;      /* number of disk in operations */
            unsigned long long      outops;     /* number of disk out operations */
        } p_diskiostat;
	int	p_wlmthrds;	     /* no. of threads in proc's wlm class */
        int     p_wlmocthrds;        /* no. of threads not in proc's wlm class */
	int	p_thrsetcnt;	     /* no. of threads with rset attachment*/

	void	*p_ptbpt;		/* ptrace brkpnt control block */
	tid_t	p_ptsynch;		/* synch for trap handling */

	/* Process creation time */
	unsigned long long		p_forktime;
	/* 
	 * Eye-catcher: this field must be the last field 
	 * of the structure. Please insert new fields above it.
	 */
	proc_eye_catch_t           	p_eyec;		/* proc eye-catcher */
};

/* shortcuts to the per-process disk I/O statistics */
#define p_dkinbytes  p_diskiostat.inbytes
#define p_dkoutbytes p_diskiostat.outbytes
#define p_dklogbytes p_diskiostat.logbytes
#define p_dklogops   p_diskiostat.logops
#define p_dkinops    p_diskiostat.inops
#define p_dkoutops   p_diskiostat.outops

struct	pvproc {

        /* identifier fields */
        pid_t           pv_pid;         /* unique process identifier    */
        pid_t           pv_ppid;        /* parent process identifier    */
        pid_t           pv_sid;         /* session identifier           */
        pid_t           pv_pgrp;        /* process group leader pid     */
        uid_t           pv_uid;         /* real user identifier         */
        uid_t           pv_suid;        /* set user identifier          */
	class_id_t	pv_class;	/* wlm class 			*/

        /* 
	 * identifier fields for checkpoint/restart.  Virtual ids are
	 * only used for restarted processes.
	 */
        pid_t           pv_vpid;        /* virtual process id 		*/
        pid_t           pv_vppid;       /* virtual parent id            */
        pid_t           pv_vsid;        /* virtual session identifier   */
        pid_t           pv_vpgrp;       /* virtual pgrp leader pid   	*/
        crid_t          pv_crid;        /* crid of process 		*/
        uint            pv_crid_token;  /* token for primary process 	*/

        /* zombie process information (doubleword aligned) */
        struct trusage64 pv_ru;         /* Rusage structure for exit()  */

	ulong		pv_spare[1];	/* read-only spare fields 	*/

	Simple_lock	pv_lock;	/* proc lock for enabled cs	*/

	/* process execution state */
	char		pv_stat;	/* process state		*/
	char		pv_sigs_queued;	/* number of signals I've q'd	*/
	ushort		pv_xstat;	/* exit status:
					 *	8 bit return value 
					 *	8 bit termination signal
					 * see also pv_flag2 SCOREFILE.
					 */
	uint		pv_atomic;	/* process flags		*/
	uint		pv_flag;	/* process flags		*/
	uint		pv_flag2;	/* More flags			*/
	int		pv_wlm;		/* wlm flags 			*/
	uint 		pv_auditmask;	/* Auditing stuff		*/

	/* user scheduler fields */
	Simple_lock	pv_usched_lock;	/* disabled user scheduler lock */
	struct pvthread	*pv_uschedp;	/* user scheduler thread ptr 	*/

	/* ptrace link pointers */
	struct ptipc	*pv_ipc;	/* ipc when being debugged	*/
	struct pvproc	*pv_dblist;	/* processes being debugged	*/
	struct pvproc	*pv_dbnext;	/* next in p_dblist		*/

	/* procfs fields */
	struct vnode *	pv_procfsvn;	/* procfs process vnode address */

	/* swapout queue link pointers */ 
	struct pvproc	*pv_sched_next;	/* next process in swap queues  */
	struct pvproc	*pv_sched_back;	/* previous process in swap q   */

	/* main process link pointers */
	struct proc 	*pv_procp;	/* my global process data 	*/
	struct pvproc	*pv_child;	/* head of list of children	*/
	struct pvproc	*pv_siblings;	/* NULL terminated sibling list */
	struct uidinfo	*pv_uidinfo;	/* uid information structure	*/
                                        /* The process group list is a NULL  */
					/* terminated doubly linked list.    */
					/* It only exists if pv_pgrp != 0    */ 
	struct pvproc	*pv_ganchor;	/* anchor for pv_pgrp 		     */
        struct pvproc   *pv_pgrpl;      /* forward link for pv_pgrp  	     */
        struct pvproc   *pv_pgrpb;      /* back link for pv_pgrp 	     */
        struct pvproc   *pv_ttyl;       /* circular list of process groups   */
                                        /* in the same session (p_sid).      */
                                        /* If the session has a controlling  */
                                        /* tty (u.u_ttyp), the processes     */
                                        /* (process groups) in the session   */
                                        /* have the same controlling tty.    */
                                        /* NOTE: p_ttyl links one process of */
                                        /* each process group in the session */
        struct pvproc   *pv_cridnext;   /* Next process in C/R group 	     */

	Simple_lock pv_session_lock;	/* pgrp and session lock - disabled  */
	Simple_lock pv_parent_lock; 	/* parent-child-sibling  - disabled  */
	Simple_lock pv_lock_d; 		/* process lock          - disabled  */

	/* thread fields */
	struct pvthread	*pv_threadlist;	/* head of list of threads	     */
	tid_t		pv_synch;	/* event list for threads waiting    */
				   	/* for this process to be suspended  */

	/* dispatcher fields */ 
	uint64_t 	pv_mempools[1];	/* memory pools 		*/
	void 		*pv_rset;	/* real rset (s/w partition) 	*/

	/* process statistics */
	unsigned long long pv_nframes;	/* accounting page frames	*/
	unsigned long long pv_npsblks;	/* accounting paging space blocks */
	unsigned long long pv_nvpages;	/* accounting virtual mem pages */

	/* misc fields */
	struct kernext_svc *pv_asyncio;
	tid_t		pv_chksynch;	/* event list for checkpoint   */
	struct pvthread *pv_chktv;	/* pointer to adv handler pvthread */

	/*
	 * Process CPU times.
	 *
	 * The pv_totalcputime and pv_totalscputime fields represent the total
	 * and system cpu times for the process.  These are updated once per
	 * second by the swapper, by storing the total then system time, in
	 * order.  The 32-bit kernel also uses primitives to atomically load
	 * and store them since they are double words.  Storing these in order
	 * allows readers to read them in the opposite order, which ensures
	 * that they will never see an updated system time with a corresponding
	 * stale total time.  These are known as the 'enabled' counters since
	 * they can read by enabled code, in order.
	 * 
	 * The pv_xcputime and pv_xscputime are the 'disabled' cpu counters
	 * and are updated under pv_lock_d by terminating threads and
	 * schedcpu().  They are called disabled counters because they
	 * managed under a disabled lock, not because they represent disabled
	 * cpu time.  These are added to the related 'enabled' counters
	 * every second by the swapper. These fields exist so disabled code
	 * that updates proc level counters does not have to serialize
	 * with base level readers.  Disabled readers can use the sum of the
	 * 'enabled' and 'disabled' counters to get a relatively up-to-date
	 * snapshot of accumulated cpu time.
	 */
	unsigned long long     pv_totalcputime;	 /* cpu time for proc */
        unsigned long long     pv_totalscputime; /* sys time for proc */
        unsigned long long     pv_xcputime;      /* 'disabled' cpu time */
        unsigned long long     pv_xscputime;     /* 'disabled' sys time */

	unsigned long long     pv_totaldiskio;   /* 512 bytes blocks */
	time_t                 pv_termtime;
	void		      *pv_gcipc;       /* gencore IPC      */

	/* scheduler fields */
	char pv_pri;                  /* process fixed priority */
	char pv_policy;               /* process policy */
	
	/* Fields for advanced accounting */
	short			pv_acctflags;
	int			pv_projid;	/* project ID */
	unsigned long long	pv_subproj;	/* load leveler subproject */
	int			pv_sprojid;	/* Saved project ID */
	int			pv_pad1;	/* Pad */

	dev64_t			pv_app_dev;	/* application id: device no */
	ino64_t			pv_app_ino;	/*	inode number */
	uint_t			pv_app_gen;	/*	generation number */
	void			*pv_ewlmproc;	/* pointer to ewlm proc block */
	struct prochr		*pv_handlers;	/* per-process handlers */

	void			*pv_cached_credp;/* Pointed to cached creds */ 
	Simple_lock		pv_handlers_lock;/* per-process handlers lock*/

	unsigned long long      pv_wlm_nvpages;  /* wlm virtual pg accounting*/

#ifdef __64BIT_KERNEL
	ushort			pv_bopflags;    /* BOP flags */
	ushort			pv_bopmcnt;     /* BOP violation counts */
	int			pv_pad2;	/* Pad */
	void			*pv_p11_ctx;/* used by PKCS#11 device driver */ 
#endif


	uint			pv_flag3;	/* Yet more flags		*/
	int			pv_pad3;

	/* 
	 * Eye-catcher: this field must be the last field 
	 * of the structure. Please insert new fields above it.
	 */
	 proc_eye_catch_t		pv_eyec;	/* pvproc eye-catcher */

	/*
	 * When deciding on a pad amount for the pvproc structure, be sure
	 * that the final size is not only a cache multiple, but a power of
	 * 2 as well.  This is a requirement of the NUMA sub-zone support.
	 * This value is defined as PV_LOGSIZE for use by pmzone.h.
	 */

#ifdef _POWER
#ifdef __64BIT_KERNEL
#define	PV_PAD		84
#define PV_LOGSIZE	10
#else 
#define	PV_PAD		1
#define PV_LOGSIZE	9
#endif
#endif /* _POWER */

#if PV_PAD 
	int		pv_pad[PV_PAD];
#endif

};

#ifdef _KERNSYS
/*
 * Make sure that the pvproc structure is really the correct power of 2 size.
 * 
 * For the 32 bit kernel, if the size of the pvproc struct grows over 0x200,
 * we can change pmzone.h to allow that MAX_PZONE_SIZE is the same as the
 * entire segment, so that we only need one sub zone to contain the 
 * entire zone.
 */
struct procsizevaliditycheck {
	char    b[(sizeof(struct pvproc) == (1 << PV_LOGSIZE)) ? 1 : -1];
#ifndef __64BIT_KERNEL
	/* 
	 * PV_LOGSIZE should never grow past 9 on the 32 bit kernel.  The implication if it
	 * does is that we will suddenly support only 1/2 as many processes as we once did 
	 * To change this, you have to solve the problem of having only 1/2 segment for the
	 * proc table.  Many items targeted for the pv_proc structure can really go to the
	 * proc structure instead, which is xmalloced.
	 */
	char    c[(PV_LOGSIZE <= 9) ? 1 : -1];
#endif
};
#endif
  
#endif	/* _32KERMODE */

#define pv_link		pv_vpgrp	/* any field not used when free */
#define pv_utime	pv_ru.ru_utime.tv_sec
#define pv_stime	pv_ru.ru_stime.tv_sec

#define p_rt_ticks      p_clock.rt_ticks
#define p_active_tmrs   p_clock.active_tmrs

/*
 * IMPORTANT NOTE :
 *
 * Process flags (pv_flag & p_flag, 4 flags of p_atomic (SWTED, SFWTED,
 * SEWTED, SLWTED) and 2 flags of pv_atomic (SORPHANPGRP, SPPNOCLDSTOP) are
 * or'd together and reported via getprocs(). Hence, these 4 p_atomic bits
 * along with bits in p_flag and pv_flags MUST be disjoint sets. Similarly
 * p_flag2 and pv_flag2 bits must also form disjoint sets.  The serialization
 * strategy for pv_flag, pv_flag2, p_flag, and p_flag2 is the same.  These
 * fields can only be updated under the context of the process and if the
 * process is multi-threaded, one must also hold the pv_lock_d. p_atomic is
 * updated through atomic primitives. p_int can be updated across contexts
 * and from the interrupt level. The caller must hold the pv_lock_d while
 * updating p_int.
 *
 * In order to improve readability and the creation of new flags, there are
 * now "RESERVED" comments in the flags of each field where overlapping is
 * problematic. These sets are: 1) (p_flag, pv_flag, p_atomic, and pv_atomic)
 * and 2) (p_flag2 and pv_flag2). The comments only exist in the more commonly
 * modified structures (i.e., not p_atomic and pv_atomic), so if these
 * structures are modified, the other bits must be taken into account. As
 * new flags are added, they should be added into one set of flags (or both
 * if needed), and comments reserving them should be added to the other
 * structure(s). These comments take the form:
 * RESERVED(<name>)	0x<value>  <field>
 * where <name> is the name of the flag, <value> is its hex value, and
 * <field> is the field for which it is reserved.
 *
 * pvproc flags, pv_flag 
 *
 * Some flags are also set in p_flag.  They are SLOAD, SKPROC, STRC, SEXIT.
 */

#define SLOAD		0x00000001	/* user and uthread struct. pinned */
/* RESERVED(SNOSWAP)	0x00000002 pv_flag3 */
/* RESERVED(SFORKSTACK)	0x00000004 p_flag */
#define STRC		0x00000008	/* process being traced		   */
/* RESERVED(SWTED)	0x00000010 p_atomic */
/* RESERVED(SFWTED)	0x00000020 p_atomic */
/* RESERVED(SEWTED)	0x00000040 p_atomic */
/* RESERVED(SLWTED)	0x00000080 p_atomic */
/* RESERVED(SFIXPRI)	0x00000100 pv_flag3 */
#define SKPROC		0x00000200	/* Kernel processes		   */
#define SSIGNOCHLD	0x00000400	/* do send SIGCHLD on child's death*/
/* RESERVED(SSIGSET)	0x00000800 p_flag */
/* RESERVED(SXPG1170)	0x00001000 p_flag */
/* RESERVED(SGETUREGS)	0x00002000 p_flag */
#define STRACING	0x00004000	/* process is a debugger	   */
#define SMPTRACE	0x00008000	/* multi-process debugging	   */
#define SEXIT		0x00010000	/* process is exiting		   */
/* RESERVED(SLPDATA)	0x00020000 p_flag */
/* RES.(SORPHANPGRP) 	0x00040000 pv_atomic */
#define STRCME		0x00080000	/* trace myself 		   */
/* RES.(SPPNOCLDSTOP) 	0x00100000 pv_atomic */
#define SEXECED		0x00200000	/* process has exec'd		   */
/* RESERVED (SHIGHRES)  0x00400000 p_flag */
/* RESERVED(SEXECING)	0x01000000 p_flag */
/* RES.(SPSEARLYALLOC)	0x04000000 p_flag */
/* RESERVED(SCONTINUED)	0x08000000 p_flag */
#define SPLOCK		0x10000000	/* process has plock'ed	memory	   */

/*
 * pvproc flags, pv_flag2
 *
 * Some flags are also set in p_flag2.  They are S64BIT.
 */

#define S64BIT		0x00000001	/* this is a 64-bit process	   */
#define SWAITPROC	0x00000002	/* This is waitproc (one per cpu)  */
/* RESERVED(SFASTTRAP)	0x00000004 p_flag2 */
#define SSCHEDPROC	0x00000008	/* Slave scheduler (one per srad)  */
#define SRESTART        0x00000010      /* restart in progress             */
#define SPRIMARY        0x00000020      /* Primary checkpoint process      */
#define SCHKPNTABLE     0x00000040      /* Checkpointable process (env var)*/
#define SRESTARTED      0x00000080      /* Restarted process               */
#define SRESTARTING	0x00000100      /* Restarting process              */
#define SCHKTRC         0x00000200      /* traced at checkpoint            */
/* RESERVED(SRT_MPC)	0x00000400 p_flag2 */
/* RESERVED(SRT_GRQ)	0x00000800 p_flag2 */
/* RES.(SWP_SIGNALED)	0x00001000 p_flag2 */
#define	SCRED		0x00002000	/* Per-thread credentials	   */	
#define SCOREFILE	0x00004000	/* Core file created               */
#define SCHKHANDLER     0x00008000      /* Has a checkpoint handler        */
/* RESERVED(SDSA)	0x00010000 p_flag2 */
/* RESERVED(SCORENAME)	0x00020000 p_flag2 */
/* RESERVED(SPTHREADED)	0x00040000 p_flag2 */
/* RES.(SLPDATAMUST)	0x00080000 p_flag2 */
/* RESERVED(SMCMMEMAFF)	0x00100000 p_flag2 */
#define SPIDCRIT	0x00200000	/* Critical process - UE GARD	   */
#define SFORKCRIT	0x00400000	/* Critical process - UE GARD	   */
/* RES.(SFCONTINUED)	0x00800000 p_flag2 */
#define SNOCKPTSHM      0x01000000      /* NEVER checkpoint shared memory  */
#define SINHERITED	0x02000000	/* init inherited on parent exit   */
/* RES.(SCORE_MMAP)	0x04000000 p_flag2 */
/* RES.(SCORE_NOSHM)	0x08000000 p_flag2 */
#define SPV_HOLD	0x10000000	/* freeproc will free this slot    */
#define SUKEYAWARE      0x20000000      /* process has user keys enabled   */
#define SMPIJOB		0x40000000	/* MPI job (can use local RQ)      */
#define STRAPSIG	0x80000000	/* ptrace trap handling */

/*
 * pvproc flags, pv_flag3
 *
 * Flags may be used internally when not needing to export pv_flags.
 * SFIXPRI and SNOSWAP are exported flags.
 */

/* InternalUse          0x00000001 */
#define SNOSWAP         0x00000002 /* process can't be swapped out */
/* InternalUse          0x00000004 */
/* InternalUse          0x00000008 */
/* InternalUse          0x00000010 */
/* InternalUse          0x00000020 */
/* InternalUse          0x00000040 */
/* InternalUse          0x00000080 */
#define SFIXPRI         0x00000100 /* fixed priority, ignoring p_cpu */
/* InternalUse          0x00000200 */
/* InternalUse          0x00000400 */
/* InternalUse          0x00000800 */
/* InternalUse          0x00001000 */
/* InternalUse          0x00002000 */
/* InternalUse          0x00004000 */
/* InternalUse          0x00008000 */
/* InternalUse          0x00010000 */
/* InternalUse          0x00020000 */
/* InternalUse          0x00040000 */
/* InternalUse          0x00080000 */
/* InternalUse          0x00100000 */
/* InternalUse          0x00200000 */
/* InternalUse          0x00400000 */
/* InternalUse          0x00800000 */
/* InternalUse          0x01000000 */
/* InternalUse          0x02000000 */
/* InternalUse          0x04000000 */
/* InternalUse          0x08000000 */
/* InternalUse          0x10000000 */

/*
 * process flags, p_flag
 */

#define SLOAD		0x00000001	/* user and uthread struct. pinned */
/* RESERVED(SNOSWAP)	0x00000002 pv_flag */
#define SFORKSTACK	0x00000004	/* special fork stack is allocated */
#define STRC		0x00000008	/* process being traced		   */
/* RESERVED(SWTED)	0x00000010 p_atomic */
/* RESERVED(SFWTED)	0x00000020 p_atomic */
/* RESERVED(SEWTED)	0x00000040 p_atomic */
/* RESERVED(SLWTED)	0x00000080 p_atomic */
/* RESERVED(SFIXPRI)	0x00000100 pv_flag */
#define SKPROC		0x00000200	/* Kernel processes		   */
/* RESERVED(SSIGNOCHLD)	0x00000400 pv_flag */
#define SSIGSET		0x00000800	/* process uses the SVID sigset int*/
#define SXPG1170	0x00001000	/* XPG SPEC1170 behavior assumed   */
#define SGETUREGS	0x00002000	/* state save on svc call	   */
/* RESERVED(STRACING)	0x00004000 pv_flag */
/* RESERVED(SMPTRACE)	0x00008000 pv_flag */
#define SEXIT		0x00010000	/* process is exiting 		   */
#define SLPDATA         0x00020000      /* large page data process         */
/* RES.(SORPHANPGRP) 	0x00040000 pv_atomic */
/* RESERVED STRCME	0x00080000 pv_flag */
/* RES.(SPPNOCLDSTOP) 	0x00100000 pv_atomic */
/* RESERVED(SEXECED)	0x00200000 pv_flag */
#define SHIGHRES	0x00400000 	/* High resolution timer for thread*/
#define SEXECING	0x01000000	/* process is execing		   */
#define SPSEARLYALLOC	0x04000000	/* allocates paging space early	   */
#define SCONTINUED	0x08000000	/* process continued after stop    */
/* RESERVED(SPLOCK)	0x10000000 pv_flag */
#define SFASTWATCH	0x20000000	/* fast wathpoint enabled */

/* There are three slightly overlapping flags for indicating user heap
 * page size: SLPDATA, SLPDATA_MUST, U_datal2psize.
 *
 * U_datal2psize will always indicate the page size that should be
 * used for future heap allocations. This will be set to L2LGPSIZE
 * when SLPDATA is set as well as if new_uheap_psize() is used to set
 * future allocations to said size.
 *
 * SLPDATA indicates that the process was started as a "large page"
 * process, implying a distinct address space model.
 *
 * SLPDATA_MUST indicates that if there are no more large pages for an
 * allocation then fail (rather then silently using 4k pages). It is
 * turned on if new_uheap_psize() is used to set U_datal2psize to
 * L2LGPSIZE, as well as if flagged by the environment process
 * creation time.
 *
 * All of are inherited over fork() but not exec().
 */
	
#define SLPDATA_SET(U)	((U)->U_procp->p_flag & SLPDATA)
#define USE_LPDATA(U)	(SLPDATA_SET(U) || ((U)->U_datal2psize == L2LGPSIZE))
	
/*
 * yet more process flags, p_flag2
 */

#define S64BIT		0x00000001	/* this is a 64-bit process	   */
/* RESERVED(SWAITPROC)	0x00000002 pv_flag2 */
#define SFASTTRAP	0x00000004	/* fast trap capability enabled    */
/* RESERVED(SSCHEDPROC)	0x00000008 pv_flag2 */
/* RESERVED(SRESTART)	0x00000010 pv_flag2 */
/* RESERVED(SPRIMARY)	0x00000020 pv_flag2 */
/* RES.(SCHKPNTABLE)	0x00000040 pv_flag2 */
/* RESERVED(SRESTARTED)	0x00000080 pv_flag2 */
/* RES.(SRESTARTING)	0x00000100 pv_flag2 */
/* RESERVED(SCHKTRC)	0x00000200 pv_flag2 */
#define	SRT_MPC		0x00000400	/* RT kernel: send MPC to preempt  */
#define	SRT_GRQ		0x00000800	/* process stays on global run queue */
#define	SWP_SIGNALED	0x00001000	/* sig posted for watchpoint hit   */
/* RESERVED(SCRED)	0x00002000 pv_flag2 */
/* RESERVED(SCOREFILE)	0x00004000 pv_flag2 */
/* RES.(SCHKHANDLER)	0x00008000 pv_flag2 */
#define SDSA		0x00010000	/* 32-bit Dynamic Segment Allocation */
#define SCORENAME	0x00020000	/* Use new-style core name         */
#define SPTHREADED      0x00040000      /* this is a pthreaded process     */
#define SLPDATAMUST     0x00080000      /* mandatory large page data proc:
					 * applies to POLY_HEAP_PSIZE &
					 * standard large page data procs
					 */
#define SMCMMEMAFF	0x00100000	/* mcm local memory allocation 	   */
/* RESERVED(SPIDCRIT)	0x00200000 pv_flag2 */
/* RESERVED(SFORKCRIT)	0x00400000 pv_flag2 */
#define SFCONTINUED	0x00800000	/* was force continued 		   */
/* RESERVED(SNOCKPTSHM)	0x01000000 pv_flag2 */
/* RESERVED(SINHERITED)	0x02000000 pv_flag2 */
#define SCORE_MMAP	0x04000000	/* dump non-anonymous mmap regions */
#define SCORE_NOSHM	0x08000000	/* do NOT dump SHM to corefile     */
/* RESERVED(SPV_HOLD)	0x10000000 pv_flag2 */
/* RESERVED(SUKEYAWARE) 0x20000000 pv_flag2 */
/* RESERVED(SMPIJOB)	0x40000000 pv_flag2 */
/* RESERVED(STRAPSIG)	0x80000000 pv_flag2 */

#define SLPDATAMUST_SET(U)	((U)->U_procp->p_flag2 & SLPDATAMUST)

/*
 * process flags, p_int
 */
#define SCORE		0x00000001	/* process is core dumping         */
#define SCORE_DUMP	0x00000002	/* core dump is processing         */
#define SRUNQ           0x00000004      /* runnable pthreads.              */
#define SCHKPNT         0x00000008      /* checkpoint operation pending    */
#define SJOBSTOP	0x00000010	/* used with SSUSP for job stop    */
#define SPROCFS		0x00000020	/* used with SSUSP for procfs stop */
#define SPTRACE		0x00000040	/* used with SSUSP for ptrace stop */
#define SCHKPNTING	0x00000080      /* Process in checkpoint 	   */
#define SPRFORK		0x00000100	/* procfs inherit-on-fork 	   */
#define SPRKLC		0x00000200	/* procfs kill-on-last-close 	   */
#define SPRRLC		0x00000400	/* procfs run-on-last-close 	   */
#define SPRASYNC	0x00000800	/* procfs async thread stop 	   */
#define SPROCTR		0x00001000	/* procfs syscall tracing active   */
#define SPRJOBSIG	0x00002000	/* procfs jobcontrol trace active  */
#define SPROFIL		0x00010000	/* profile buffer filled up	   */
#define SJUSTBACKIN	0x00020000	/* process recently restarted	   */
#define SCHKPTSTOP	0x00040000 	/* used with SSUSP for chkpt stop  */
#define SLOWPSEXCP	0x00080000	/* psmgr chose me for an exception */
#define SWLM            0x00100000  	/* wlm. send a message to the tty  */
#define SWLMRMEM	0x00200000	/* wlm suspend process flag	   */
#define SWLMVMEM	0x00400000	/* wlm suspend process flag	   */
#define SWLMVMEMPROC	0x00800000	/* proc vmem wlm process flag	   */
#define SCORESTOP       0x01000000      /* coredump() called               */
#define SPSMKILL	0x02000000	/* paging space mgr chose me to die*/
#define SNOFCONT	0x04000000	/* do not force continue process   */
/* Bit 0x08000000 is reserved for future use; it will enter sig_slih */
#define STERM		0x10000000	/* process should be terminated	   */
#define SSUSP		0x20000000	/* suspend process in kmode/umode  */
#define SSUSPUM		0x40000000	/* suspend process in umode        */
#define SGETOUT		0x80000000	/* process should be swapped out   */

/*
 * Collect all process-level stops that are reflected in p_int.
 */
#define SALLSTOPS	(SJOBSTOP|SPROCFS|SPTRACE|SCORESTOP|SCHKPTSTOP)

/*
 * This flag triggers a call to sig_slih.  When changing these flags,
 * one must also change proc.m4.  Moreover, the bits have to be consecutive
 * to work with rlinm.
 */
#define SSIGSLIH 	(STERM|SSUSP|SSUSPUM|SGETOUT)

/*
 * process flags, pv_atomic
 */
#define SORPHANPGRP 	0x00040000 	/* orphaned process group    	*/
#define SPPNOCLDSTOP 	0x00100000 	/* Do not send parent process   */
					/*  SIGCHLD when a child stops  */

/*
 * process flags, p_atomic 
 */
#define SWTED		0x00000010	/* stopped while traced		   */
#define SFWTED		0x00000020	/* stopped after fork while traced */
#define SEWTED		0x00000040	/* stopped after exec while traced */
#define SLWTED		0x00000080	/* stopped after load/unload while */
#define UV_SYSCFG	0x00000400	/* syscfg mapping loaded	   */
#define UV_PZERO	0x00000800	/* page zero mapped		   */
#define SWLMTERMSENT    0x00001000	/* wlm: sigterm sent to the process */

/*
 * AACCT flags, pv_acctflags
 */
#define SPROJFIXED	0x0001	/* fixed project assignment */
#define SPROJAPP	0x0002	/* app specific project assignment */
#define SPROJINVOKE	0x0004	/* This process invoked the app */
#define SPROJABS	0x0008	/* This process has an absolute project */

/*
 * process states, pv_stat
 */
#define SNONE		0		/* slot is available	*/
#define SIDL		4		/* process is created	*/
#define SZOMB		5		/* process is dying	*/
#define SSTOP		6		/* process is stopped	*/
#define SACTIVE		7		/* process is active	*/
#define SSWAP		8		/* process is swapped	*/

/*
 * For multiplication of fractions that are stored as integers, including
 * p_pctcpu.  Not allowed to do floating point arithmetic in the kernel.
 */
#define SBITS		16

/*
 * Defines and macros for use with process table entries
 */
#define PIDRESERVED	6		/* number of bits reserved in pid */
#define PROCSHIFT	18		/* number of bits in proc index	  */
#define PGENSHIFT	8		/* proc index offset		  */
#define PGENMASK	((1<<PGENSHIFT)-1) /* mask of PGENSHIFT bits	  */
#define NPROC		(1<<PROCSHIFT)	/* mask for bits in proc index	  */
#define PIDMASK		((NPROC-1)<<PGENSHIFT) /* mask for bits in pid	  */
#define PIDMAX		((NPROC<<PGENSHIFT)-1) /* largest possible pid	  */
					/* bits of proc index split */
#define PSRADSHIFT 	TSRADSHIFT  		/* bits for srad */
#define PIDXSHIFT 	(PROCSHIFT-PSRADSHIFT) /* rest of bits for idx */  
#define PSRADMASK 	((1L<<PSRADSHIFT)-1) /* Mask for srad bits in index */
#define PIDXMASK 	((1L<<PIDXSHIFT)-1)  

/* pid are even, but 1 is also a pid */
#define MAYBE_PID(pid)  (!(pid & 1) || (pid == 1))

  
/* mask for process table index from pid */
#ifndef __64BIT_KERNEL
#define PROCMASK(pid)   ((((pid)&PIDMASK)>>PGENSHIFT) | ((pid)&1))
#else
/* 
 * for the 64 bit kernel, PROCMASK re-orders the pid bits by 
 * taking the srad bits and shifting them down, and taking the
 * idx bits and shifting them up.
 */
#define PROCMASK(pid)   \
	((((pid) & (PSRADMASK << PGENSHIFT)) << (PIDXSHIFT-PGENSHIFT)) | \
 	((ulong)(pid) >> (PGENSHIFT+PSRADSHIFT)) | \
 	((pid) & 1))
#endif

/* mask for pid from process table idx */
#ifndef __64BIT_KERNEL
#define PIDGEN(idx) ((idx)<<PGENSHIFT)
#else
#define PIDGEN(idx)     \
	(((((idx) & (PIDXMASK)) << (PSRADSHIFT)) | \
	(((idx) & (PSRADMASK<<PIDXSHIFT)) >> PIDXSHIFT)) << PGENSHIFT)
#endif

#ifdef _KERNEL
extern struct pvproc pvproc[NPROC];	/* the process table, itself      */

/* convert pid to proc pointer	*/
#define PVPROCPTR(pid)	(&pvproc[PROCMASK(pid)])

/* validate whether a process id is valid or not  */
#define PID_VALIDATE(pid) \
	((((PROCMASK(pid)>>PIDXSHIFT) >= PM_NUM_ZONES) || \
	 (PVPROCPTR(pid) >= (struct pvproc *)pvproc_cb.primary \
		[PROCMASK(pid)>>PIDXSHIFT]->highwater_addr) || \
		(PVPROCPTR(pid)->pv_pid != (pid))) ? \
			NULL : PVPROCPTR(pid))
  
/* determine if a process is multi-threaded given a procp or threadp */
#define MTHREAD(p)	( (p)->p_active > 1 )
#define MTHREADT(t)	( (t)->t_procp->p_active > 1 )

/* pv_lock hierarchy based on address */
#define PV_LOCK_2(pv1,pv2)      		\
{         					\
	if ((ulong) pv1 < (ulong) pv2) {    	\
		simple_lock(&pv1->pv_lock);    	\
		simple_lock(&pv2->pv_lock);    	\
	} else if ((ulong) pv2 < (ulong) pv1) { \
		simple_lock(&pv2->pv_lock);    	\
		simple_lock(&pv1->pv_lock);    	\
	} else {       				\
		simple_lock(&pv1->pv_lock);     \
        }      					\
}


#define PV_UNLOCK_2(pv1,pv2)    		\
{                                               \
        if ((ulong) pv1 != (ulong) pv2) {       \
                simple_unlock(&pv1->pv_lock);   \
                simple_unlock(&pv2->pv_lock);   \
        } else {                                \
                simple_unlock(&pv1->pv_lock);   \
        }        				\
}

#endif /* _KERNEL */

#ifdef _KERNSYS
#define CHECKPOINTABLE(_pv)	((_pv)->pv_flag2 & SCHKPNTABLE)
#endif

#define P_NICE_DEFAULT	(NZERO+PUSER)	/* default value for p_nice	*/
#define P_NICE_MAX	40		/* maximum nice value		*/
#define P_NICE_MIN	0		/* minimum nice value		*/

#define EXTRACT_NICE(p)                                                	\
        (((p)->p_pvprocp->pv_flag3 & SFIXPRI) ? 			\
		(P_NICE_MAX + 1) : ((p)->p_nice - PUSER))

#define SET_NICE(p,n)                                                 	\
{                                                                       \
        if (!((p)->p_pvprocp->pv_flag3 & SFIXPRI)) {                    \
                (p)->p_nice = (MIN(P_NICE_MAX,MAX(0,(n)))) + PUSER;   	\
        }                                                               \
}

/* global locks - listed in precedence */
extern Simple_lock crid_lock;
extern Simple_lock ptrace_lock;
extern Complex_lock core_lock;
extern Simple_lock time_lock;	
/* pv_lock */
extern Simple_lock uidinfo_lock;
/* tod_lock */
extern Simple_lock uex_lock;

/* event_list_lock's and slist_list_lock's are peers */
/* p_lock_d's */
extern Simple_lock suspending_q_lock;
/* run_queue_lock's, suspending_q_lock, and vmm wait_list_lock's are peers */

/* 
 * Structures for resource intialization/termination handlers
 */
struct proch 
{
	struct	proch	*next;	/* next pointer */
	void (*handler)();		/* function to be called */
};

/* Defines to pass the resource handlers */
#define	PROCH_INITIALIZE	1
#define PROCH_TERMINATE		2
#define PROCH_SWAPOUT		3   /* process is being swapped out. It's   */
				    /*  u block is still pinned. Interrupts */
				    /*  are enabled                         */
#define PROCH_SWAPIN		4   /* process is being made runnable. It's */
				    /*  u block has been pinned , but it has*/
				    /*  not been put on a 'ready to run'    */
				    /*  queue. Interrupts are enabled.      */
#define	PROCH_EXEC		5
#define	PROCH_LOAD		6   /* load module notification             */
#define	PROCH_UNLOAD		7   /* unload module notification           */
#define THREAD_INITIALIZE      11
#define THREAD_TERMINATE       12
#define PROCH_SETUID           13   /* setuid notification, only supported  */
                                    /* on proch_reg() resource handlers     */
#define PROCH_SETGID           14   /* setgid notification, only supported  */
                                    /* on proch_reg() resource handlers     */
#define PROCH_EXECEXIT         15   /* exec exit notification.  Called      */
				    /* near the end of exec processing when */
				    /* preparing to exit the kernel and     */
				    /* give control to the exec'ed program. */
				    /* Called when the exec has been        */
				    /* successful and the new program has   */
				    /* loaded.  Only supported on           */
				    /* proch_reg() resource handlers.       */ 
#define PROCH_RESTART	       16   /* Called at the end of restart before  */
				    /* the process's checkpointed state is  */
				    /* resumed. The primary process goes    */
				    /* through this first, then all the     */
				    /* secondary processes. Only supported  */
				    /* on proch_reg() resource handlers     */
/* All above are also supported with proch_reg_process resource handlers    */
#define THREAD_LOCAL_INIT      17   /* Called when a pthread first gets     */
				    /* created and dispatched to run on a   */
				    /* kernel thread. Only supported on     */
				    /* proch_reg_process() resource         */
				    /* handlers                             */
#define THREAD_LOCAL_TERM      18   /* Called when an M:N pthread exits     */
				    /* Only supported on proch_reg_process  */
				    /* resource handlers                    */
#define THREAD_LOCAL_DISPATCH  19   /* Called when an M:N pthread has       */
				    /* dispatched to run on a kernel thread */
				    /* Only supported on proch_reg_process  */
				    /* resource handlers                    */
#define THREAD_LOCAL_MCHANGE   20   /* Called when a pthread scope changes  */
				    /* Only supported on proch_reg_process  */
				    /* resource handlers                    */

/* UE-Gard */
#define NONCRITFORK		1

/*
 * You can also register resource handlers with proch_reg(struct prochr*, mask).
 * In this case, you also register for the situations during which your
 * handler is called with a combination of the bits defined here.
 * These bits must be placed in prochr_mask before calling proch_reg().
 * (The defined relationship of the prochr bit being the proch numbered bit
 * in a mask must be preserved here.  The kernel code is based on this.)
 *
 * Do not change the contents of the prochr structure after registering it.
 * It may appear that you can dynamically change the mask, but this is not
 * supported.  Once a prochr structure has been registered, the only valid
 * operation that may be performed upon it is to proch_unreg() it.
 */
struct prochr
{
	struct	prochr	*prochr_next;	/* next pointer */
	void	(*prochr_handler)();	/* function to be called */
	uint	prochr_mask;		/* conditions under which to call */
	int	pad;			/* padding for structure */
};

/*
 * Structure passed by reference to PROCHR_EXECEXIT handler 
 */ 
typedef struct prochr_execexit
{
        int         len;            /* length of prochr_execexit struct */
        dev_t       dev;            /* device id of exec'ed file */
        ino_t       ino;            /* inode number of exec'ed file */
        uint_t      gen;            /* generation number of exec'ed file */
} prochr_execexit_t;        

#define	PROCHR_INITIALIZE	(1UL<<PROCH_INITIALIZE)
#define	PROCHR_TERMINATE	(1UL<<PROCH_TERMINATE)
#define	PROCHR_EXEC		(1UL<<PROCH_EXEC)
#define	PROCHR_THREADINIT	(1UL<<THREAD_INITIALIZE)
#define	PROCHR_THREADTERM	(1UL<<THREAD_TERMINATE)
#define PROCHR_SETUID           (1UL<<PROCH_SETUID)
#define PROCHR_SETGID           (1UL<<PROCH_SETGID)
#define PROCHR_EXECEXIT         (1UL<<PROCH_EXECEXIT)  
#define PROCHR_RESTART          (1UL<<PROCH_RESTART)
#define PROCHR_TLOCAL_INIT      (1UL<<THREAD_LOCAL_INIT)
#define PROCHR_TLOCAL_TERM      (1UL<<THREAD_LOCAL_TERM)
#define PROCHR_TLOCAL_DISPATCH  (1UL<<THREAD_LOCAL_DISPATCH)
#define PROCHR_TLOCAL_MODE      (1UL<<THREAD_LOCAL_MCHANGE)

/*
 * prochadd() only supports the following callouts.  
 */ 
#define PROCHADD_CALLOUTS (PROCHR_INITIALIZE | \
                           PROCHR_TERMINATE  | \
                           PROCHR_EXEC       | \
                           PROCHR_THREADINIT | \
                           PROCHR_THREADTERM)

#ifdef __64BIT_KERNEL
/* Flags (pv_bopflags) for Buffer overflow protection (BOP) */
#define	_PROC_BOP_PROTECT	0x0001  /* process is BOP protected */
#define	_PROC_BOP_COREDUMP	0x0002  /* coredump due to BOP violation */
#endif

/*
 * Function prototypes for kernel extension.
 * The 64bit kernel always defines with full prototypes.
 */
#ifdef _KERNEL
extern int    	proch_reg(struct prochr *);
extern int    	proch_unreg(struct prochr *);
extern int    	proch_reg_process(pid_t, struct prochr *);
extern int    	proch_unreg_process(pid_t, struct prochr *);
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
extern void    	prochadd(struct proch *);
extern void    	prochdel(struct proch *);

extern int      initp(pid_t, int (*)(), 
			char *, int32long64_t, char[]);
extern pid_t    creatp(void);

extern void     freep(pid_t pid);

extern int      setpinit(void);
extern int      setpswap(void);

extern pid_t 	getpid(void);
extern pid_t    getppidx(pid_t pid);

extern int      getuerror(void);
extern int     	setuerror(int errno);

extern int	setjmpx(label_t *);
extern void    	clrjmpx(label_t *);
extern int     	longjmpx(int);

extern void	setsid2(void);

extern int	ue_proc_check(pid_t pid);

#endif /* (__64BIT_KERNEL || __FULL_PROTO) */
#endif /* _KERNEL */

/*
 * p_pctcpu is a floating point number represented as a ulong. It has 
 * a range of [(2 ** 16 ) - 1, (2 ** -16) + 1].  To translate into a 
 * floating point divide by (double)FLT_MODULO.
 */
#define FLT_MODULO		(1<<16)

#ifdef __cplusplus
}
#endif

#endif  /* _H_PROC */
