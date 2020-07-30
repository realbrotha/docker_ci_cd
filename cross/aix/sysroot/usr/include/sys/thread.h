/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/thread.h 1.35.8.8                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1993,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)55       1.35.8.8  src/bos/kernel/sys/thread.h, sysproc, bos53X, x2009_31B0 7/15/09 09:57:01 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: MAYBE_TID
 *              THREADMASK
 *              THREADPTR
 *              VALIDATE_TID
 *
 *   ORIGINS: 27, 83
 *
 *
 * LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_THREAD
#define _H_THREAD

#include <sys/types.h>
#include <sys/mstsave.h>
#include <sys/processor.h>
#include <sys/lock_def.h>
#include <sys/var.h>
#include <sys/atomic_op.h>
#include <sys/context.h>
#include <sys/time.h>
#include <sys/timer.h>
#include <sys/cred.h>
#include <sys/resource.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Avoid including ras.h by defining eye catcher type as below:
 */
typedef unsigned long	thread_eye_catch_t;

/*
 *  One structure allocated per active thread.  Entries that are
 *  in use are pinned to avoid page faults in kernel critical sections.
 *
 *  This structure contains per-thread information that may be used by
 *  other threads in the process. Private per-thread data is kept in
 *  in the uthread structure, <sys/uthread.h>.
 *
 *  When changes are made here, be sure to update the assembler version
 *  in kernel/ml/thread.m4, too.
 */

#ifdef _LARGE_THREADS
#define MAXTHREADS	32767		/* max number of additional threads   */
					/* per process.  This number + 1 must */
					/* be a multiple of 128 	      */
#else
#define MAXTHREADS	512		/* max number of threads per process, */
					/* MUST be a multiple of 128, assuming*/
					/* uthread is padded to 32 bytes and a*/
					/* page is 4096-byte long 	      */
#endif

/*
 * We use a bit mask to represent which (cpus, rqs, nodes) are available
 * in the (rq, node, system).  In particular, the cpus available to run
 * a thread on its SRAD, t_allowed_cpus, is an mrq_mask_t.  The datatype
 * is defined here, and picked up by run_queue.h (which is not exported).
 *
 * To support >64 cpus per node, we use an array.  The view is of a string
 * of sequentially numbered bits.  We bury the array in a structure so that
 * the assignment operator can be used to copy these things conveniently.
 * The structure became a union to provide size-invariant views of the array.
 *
 * Most operations on a mrq_mask_t must be done using macros in run_queue.h.
 * Note that changing MRQ_WORDS_IN_MASK *will* require changes to those of
 * the MRQ macros in run_queue.h that return values through compound if (the
 * ? operator), as those macros can not use "for" loops.
 */
#define MRQ_WORDS_IN_MASK	2
#define MRQ_INTS_IN_MASK	(MRQ_WORDS_IN_MASK * 2)

typedef union	{
			unsigned long long mrq_mask_word[MRQ_WORDS_IN_MASK];
			unsigned int mrq_mask_int[MRQ_INTS_IN_MASK];
		} mrq_mask_t;

/*
 * Generate the thread structure, but...
 * If the special _32KER_64VMM flag is set (for vmm modules that must
 * run in real 64bit mode in the 32bit kernel), we cannot generate a
 * correct thread structure.
 * So we don't generate one at all.
 */
#ifndef _32KERMODE

struct	thread {

	/* identifier fields */
	tid_t		t_tid;		/* unique thread identifier	*/
	tid_t		t_vtid;		/* Virtual tid                  */

	/* frequently referenced context management fields */
	vmhandle_t	t_kthreadseg;	/* kernel thread segment value	*/
	ulong 		t_atomic;	/* thread flags	(atomic op's)	*/
	uint 		t_flags;	/* thread flags 		*/
        uint 		t_flags2;       /* thread flags                 */
	ushort 		t_lockcount;	/* number of locks held		*/
	short		t_suspend;	/* suspend signal nesting level */

	/* related data structures	*/
        struct pvthread *t_pvthreadp;   /* my pvthread struct           */
	struct proc	*t_procp;	/* owner process		*/
	struct t_uaddress {
	    struct uthread *uthreadp;	/* local data			*/
	    struct user	*userp;		/* owner process' ublock (const)*/
	}		t_uaddress;

	/* user addresses */
#ifndef __64BIT_KERNEL
        uint           	t_ulock64;      /* high order 32-bits           */
        uint		t_ulock;        /* user addr - lock or cv       */
        uint           	t_uchan64;      /* high order 32-bits           */
        uint		t_uchan;        /* key of user addr             */
	uint		t_userdata64;	/* high order 32-bits if 64-bit mode */
	int		t_userdata;	/* user-owned data		*/
	uint		t_cv64;		/* high order 32-bits if 64-bit mode */
	int		t_cv;		/* User condition variable      */
	uint		t_stackp64;	/* high order 32-bits if 64bit mode */
	char		*t_stackp;	/* saved user stack pointer	*/
	uint		t_scp64;	/* high order 32-bits if 64bit mode */
	struct sigcontext *t_scp;	/* sigctx location in user space*/
#else
        long		t_ulock;        /* user addr - lock or cv       */
        long		t_uchan;        /* key of user addr             */
	long		t_userdata;	/* user-owned data		*/
	long		t_cv;		/* User condition variable      */
	char		*t_stackp;	/* saved user stack pointer	*/
	struct sigcontext *t_scp;	/* sigctx location in user space*/
#endif

	/* event sleep fields */
	char		*t_wchan2;	/* VMM wait channel		*/
	char		*t_wchan1;	/* wait identifier - real	*/
	struct thread	*t_eventlist;	/* subscribers to event list	*/
	ulong 		t_pevent;	/* pending events		*/
	ulong 		t_wevent;	/* awaited events		*/
        vmhandle_t      t_usid;    	/* SID of user addr             */

	/* simple lock sleepers list fields */
	char		*t_swchan;	/* simple/complex lock channel	*/
	struct thread	*t_slist;	/* threads waiting for a slock	*/
        struct thread   *t_lockowner;   /* thread to be boosted         */

	vmhandle_t	t_wchan1sid;    /* SID of lock eaddr (wchan1)   */
	uint		t_wchan1offset; /* OFFSET of lock eaddr (wchan1)*/
	int		t_fsflags;	/* iowait flags from vmuser.h   */
	int		t_result;	/* wait result			*/
	int		t_polevel;	/* page out wait level		*/

	/* dispatcher fields */
	__ptr64		t_threadcontrolp; /* user addr: control_word_t	*/
	struct thread	*t_prior;	/* running list	             	*/
	struct thread	*t_next;	/* running/wait list		*/
	void		*t_graphics;    /* graphics user address state  */
	struct run_queue *t_run_queue;	/* Currently assigned RQ	*/

	u_longlong_t	t_time_start;	/* purr time thread dispatched  */
	u_longlong_t	t_spurr_time_start;/* spurr time thread dispatched */
	time_t		t_affinity_ts; 	/* affinity time stamp 		*/

	ulong 		t_dispct;	/* number of dispatches		*/
	ulong 		t_fpuct;	/* number of FP unavail ints.	*/
	mrq_mask_t	t_allowed_cpus;	/* node's cpus allowed by eff rset */
	ushort		t_adsp_flags;	/* adspace lock bits for vmm use*/
	ushort 		t_ticks;	/* # of ticks since dispatched	*/
	char		t_pri_band;	/* pri band for load balancing	*/
	char		t_savsigno;	/* saved signo			*/
	cpu_t		t_prefunnel_cpu;/* cpu to use after unfunnel	*/

	/* scheduler fields */
	cpu_t		t_cpuid;	/* processor on which I'm bound */
	cpu_t		t_scpuid;	/* saved last t_cpuid for funnel*/
	ushort		t_cpu2;		/* processor usage in last sec. */
	ushort		t_cpu;		/* processor usage		*/
                                        /* NOTE: the bounds for t_cpu   */
                                        /* 0 <= t_cpu <= T_CPU_MAX      */
	char		t_norun_secs;	/* seconds found undispatched	*/
	char		t_policy;	/* scheduling policy		*/
#define T_CPU_MAX       20+HZ           /* maximum value for t_cpu      */
        char 		t_lockpri;	/* lock priority boost count 	*/
        char		t_wakepri;	/* wakeup priority for the thread */
                                        /* NOTE: this field is set when   */
                                        /* the thread goes to sleep, and  */
                                        /* is reset to PIDL by 'setrq'.   */ 
	uchar 		t_time;		/* resident time for scheduling */
	char 		t_sav_pri;	/* Original, unboosted priority */
	char            t_ceiling;      /* Mutex ceiling                */
	char		t_nice;		/* nice for cpu usage		*/

	/* signal information */
	char		t_sigproc;	/* is current signal process based */
	char		t_cursig;	/* current/last signal taken    */
	char		t_whystop;	/* procfs thread stop reason    */

	unsigned char	t_dispatch_hist;/* records if we follow another thread
					 * in same process at dispatch time */
#ifdef __64BIT_KERNEL
	sigset_t	t_sig;		/* pending signals		*/
	sigset_t	t_sigmask;	/* current signal mask		*/
#else
	sigset64_t	t_sig;		/* pending signals		*/
	sigset64_t	t_sigmask;	/* current signal mask		*/
#endif

	/* miscellaneous fields */
	int		t_chkblock;	/* Block advanced handler       */
	ushort		t_whatstop;	/* procfs thread stop reason detail */
	ushort		t_chkerror;	/* errno return from checkpoint */
	pid_t		t_wlm_charge;	/* Tell WLM that the resources used by
					 * the thread must be accounted to
					 * the charged process class 
					 */
        struct timestruc_t t_starttime;      /* Time of thread creation */

        /* thread statistics */
        ulong           t_minflt;       /* page fault count - no I/O    */
        ulong           t_majflt;       /* page fault count - I/O needed*/
	uint		t_wlmevtcnt;	/* WLM event count */
	uint		t_trcgenct;	/* trace generation count. */
	uint		t_cpu_tb;	/* tbs accumulating towards a tick */
	cpu_t		t_ldispcpu;	/* last (cpu + 1) to run dispatcher */

	uint            t_rt_ticks;     /* posix RT thread cpu-time clock */

	unsigned long long t_interval_start;	/* TOD in TBs, rel to boot */
	/*
	 * Thread cpu times.
	 * 
	 * These are updated in-context by the dispatcher and
	 * can be read safely in-context at INTMAX or cross-
	 * context under tv_lock_d.
	 */
	unsigned long long t_cputime;		/* monotonic cpu time TBs */
	unsigned long long t_scputime;		/* monotonic sys cpu time TBs */
        unsigned long long pth_utime;		/* pthread's user time */
        unsigned long long pth_stime;		/* pthread's system time */

	cred_t		*t_credp;	/* Thread credentials pointer */

	/*
	 * The "home" cpu is used by the vmm to determine which storage
	 * pool to use to back the current page fault of the running thread.
	 * It can change if a thread is load balanced to another node, and
	 * it can be -1 if the thread is on the system global run queue.
	 *
	 * The "home" node is set when the thread is created, and never
	 * changes.  As above, it can be -1 if the thread has no home node.
	 * (Perhaps created with striped page allocation.)
	 */
	cpu_t		t_homecpu;	/* hint for local page placement */
	short		t_homenode;	/* node thread created on, or -1 */
	void		*t_rs_attinfo;	/* R_THREAD rset attachment */
        void            *t_nft_dabr;    /* address for kernel stack errinject */
        void            *t_nft_descr;   /* error injection descriptor */

	void		*t_ulock_listp;	/* Linked list of user locks */

	unsigned long   t_ipc_data;
	
#ifndef __64BIT_KERNEL
	uint		t_procfslr64;	/* saved link register for procfs */
	uint		t_procfslr;	/* saved link register for procfs */
#endif

	/* 
	 * Eye-catcher: this field must be the last field 
	 * of the structure. Please insert new fields above it.
	 */
	thread_eye_catch_t	t_eyec;		/* thread eye-catcher */
};

/*
 * The size of this structure must be a power of 2
 */
struct	pvthread {

	/* identifier fields */
	tid_t		tv_tid;		/* unique thread identifier	*/
	tid_t		tv_vtid;	/* Virtual tid                  */

	/* related data structures	*/
        struct thread 	*tv_threadp;   	/* my pvthread struct           */
	struct pvproc	*tv_pvprocp;	/* owner process (global data)	*/

	struct {
	    struct pvthread *prevthread;/* previous thread		*/
	    struct pvthread *nextthread;/* next thread			*/
	}		tv_threadlist;	/* circular doubly linked list	*/

	Simple_lock	tv_lock_d;	/* disabled thread lock		*/
	tid_t		tv_synch;	/* event list for suspension 	*/

	tid_t		tv_tsleep;	/* event list for thread_tsleep	*/
	char		*tv_wchan;	/* wait identifier - hashed	*/

	uint 		tv_flags;	/* thread flags 		*/
        uint 		tv_flags2;     	/* thread flags                 */

	/*
	 * Thread CPU times.
	 *
	 * Protected by tv_lock_d, accumulated at the process
	 * level and zeroed:
	 *	-each second by the swapper
	 *	-in schedcpu() when the thread takes a tick
	 *	-in thread_terminate() (not last thread)
	 *	-in kextix()/acctexit() (last thread)
	 */
	u_longlong_t	tv_totalcputime;  /* tot time for thread */
        u_longlong_t	tv_totalscputime; /* sys time for thread */


        int		tv_boosted;    	/* boosted count                */
	cpu_t		tv_affinity;	/* processor on which I last ran*/
	char		tv_state;	/* thread state 		*/
	char		tv_wtype;	/* type of thread wait		*/

	void		*tv_pmcontext;	/* perf monitor context pointer */
	char 		tv_pri;		/* current effective priority   */

	/*
	 * Note that there is implied padding here, since we haven't
	 * filled up the preceeding word (32bit) or doubleword (64bit).
	 * We want tv_pri in the first cache line for performance
	 * reasons in the 64bit kernel.  The following fields should
	 * not be performance critical, as they lie in or near the second
	 * cache line, which should contain relatively low use items.
	 */

	struct vnode 	*tv_procfsvn;	/* procfs thread vnode pointer  */
	void		*tv_chkfile;	/* chkfile for C/R caller       */
	
	/* Profiling fields */
	unsigned long long tv_prbase;	/* Profiling histogram buffer base */
	unsigned long long *tv_prpinned; /* Pinned PC buffer */	
        ushort          tv_prflags;	/* Profiling flags */
	ushort		tv_prbufcount;	/* PC Buffer count */
	uint		tv_ptid;	/* pthread id */

        /* Thread wlm */
        /* These are protected by the process' pv_lock */
	int		tv_wlm;		/* wlm flags 			*/
	class_id_t	tv_class;	/* wlm class 			*/
        void 		*tv_rset;	/* real rset (s/w partition) 	*/
        char            *tv_ptag;       /* WLM tag           */

	/* 
	 * Eye-catcher: this field must be the last field 
	 * of the structure. Please insert new fields above it.
	 */
	thread_eye_catch_t	tv_eyec;	/* pvthread eye-catcher */
/*
 * When deciding on a pad amount for the tvproc structure, be sure that the
 * final size is not only a cache multiple, but a power of 2 as well.
 * This is a requirement for the NUMA sub-zones support in pmzone.c.
 * Change the value of TV_LOGSIZE to the new power of 2, for use by pmzone.h.
 */
#ifdef __64BIT_KERNEL
#define TV_PAD          56
#define TV_LOGSIZE	8
#else
#define TV_PAD          0
#define TV_LOGSIZE	7
#endif

#if TV_PAD
	char		tv_pad[TV_PAD];	/* pad to 128 byte boundary	*/
#endif
};


#endif	/* _32KERMODE */

#define tv_link		tv_prevthread	/* any field not used when free */

#define t_uthreadp	t_uaddress.uthreadp
#define t_userp		t_uaddress.userp

#define tv_prevthread	tv_threadlist.prevthread
#define tv_nextthread	tv_threadlist.nextthread

/*
 * IMPORTANT NOTE :
 *
 * Thread flags (tv_flags, tv_flags2, t_flags, t_flags2, t_atomic) are 
 * logically or'd together and reported by getthrds().   The serialization
 * strategy for these fields, excluding t_atomic, is the same.  One must
 * have the tv_lock_d to update them.  t_atomic is updated with
 * atomic primitives.
 *
 * pvthread flags, tv_flags. 
 *
 * Some flags are set in t_flags also.  They are TKTHREAD.
 */
#define TKTHREAD	0x00001000	/* kernel thread		    */

/*
 * pvthread flags, tv_flags2
 *	
 * Some flags are set in t_flags2 also.  They are <none>. 
 */

#define TCHKCALLER      	0x00000400      /* Thread has invoked C/R     */

/*
 * thread flags, t_flags (must be different from the t_atomic flags)
 *
 * This field can be updated only if the caller is disabled to INTMAX
 * and holds the tv_lock_d. 
 */
#define TTERM		0x00000001	/* thread should be terminated	    */
#define TSUSP		0x00000002	/* setstate/asynch cancel available */
#define TSIGAVAIL	0x00000004	/* signal available for delivery    */
#define TINTR		0x00000008	/* deferred cancelation available   */  
#define TLOCAL		0x00000010	/* does not account for SIGWAITING  */
#define	TTRCSIG		0x00000040	/* thread identification for ptrace */
#define TPROCFS		0x00000080	/* with TSUSP, procfs stop          */
#define TOMASK		0x00000100	/* restore old mask after signal    */
#define	TWAKEONSIG	0x00000400	/* signal will abort the sleep	    */
#define SWAKEONSIG	0x00000800	/* does not really belong here, but */
					/* was used as a p_flag and in	    */
					/* xxx_sleep interfaces, so must    */
					/* still exist with the same value  */
					/* Must NOT be equal to PCATCH!     */
					/* Both PCATCH and SWAKEONSIG must  */
					/* be greater than PMASK            */
#define TFUNNELLED	0x00002000	/* thread is funnelled		    */
#define TSETSTATE	0x00004000	/* a state change is in progress    */
#define TGETREGS        0x00008000      /* with TSUSP, getregs stop         */
#define TWAKEONCHKPT	0x00010000	/* checkpoint will abort sleep      */	
#define TSIGWAIT        0x00020000    	/* tsleeping with unblocked signals */
#define TCRED	        0x00040000    	/* per-thread credentials	    */	
#define TCANCEL		0x00200000	/* cancelation pending		    */	
#define TCDEFER		0x00400000	/* cancelation type deferred        */	
#define	TCDISABLE	0x00800000	/* cancelation mode disabled	    */
#define TSYNCH		0x01000000	/* synchronous setstate pending	    */ 
#define TUSCHED		0x02000000    	/* dedicated usched thread          */
#define TLMTSIGS	0x04000000	/* pending limit sigs		    */
#define TEVTPROC	0x08000000	/* event process scope 	    	    */
#define	TPTHSUSP	0x10000000	/* pending pthread suspend	    */
#define	TPTHSTOPPED	0x20000000	/* pthread suspended		    */
#define	TPTHCONT	0x40000000	/* pending pthread continue	    */

/* 
 * flags triggering call to sig_slih:
 *
 * When changing these flags, one must also change thread.m4.  Moreover,
 * the bits must be consecutive to work with rlinm.
 */
#define TSIGSLIH	(TTERM|TSUSP|TSIGAVAIL)	
#define TSIGINTR	(TSIGSLIH|TINTR)	

/*
 * thread flags, t_atomic (must be different from the t_flags flags)
 *
 * This field should be updated only with an atomic primitive. 
 */
#define TSLWTED		0x00000020UL	/* trace stop for load/unload       */
#define TSIGDELIVERY	0x00000080UL	/* setup of signal delivery underway*/
#define TSEWTED		0x00000200UL	/* trace stop for exec              */
#define TSELECT		0x00008000UL	/* selecting: wakeup/waiting danger */
#define TWPDABR		0x00010000UL	/* hit watchpoint via DABR          */
#define TWPSYSCALL	0x00020000UL	/* hit watchpoint while in syscall  */
#define TSTEP		0x00040000UL	/* thread is being single-stepped   */
#define TFASTWATCH	0x00080000UL	/* thread is handling a fast watch */
#define TSFWTED		0x00100000UL	/* trace stop for fork              */
#define TCHKERROR	0x80000000UL	/* Checkpoint error                 */

/*
 * t_flags2
 * Thread exemption control
 * TUEXEMPT		Thread is authorized for exemptions
 * TPREEMPT_GRANT	Thread has been granted exemption from preemption
 * TNOVALIDATE          In RQ_THREAD_VALIDATE(), do not validate thread to
 *                      ensure it is running on its assigned runqueue, as
 *                      it has been moved to a new runqueue cross-context.
 *                      This will be unflagged when thread is undispatched.
 * TISIGINTR		Thread sleep was aborted by checkpoint/profiling
 *						(internal signal)
 * TCHKPNT		Thread has a pending checkpoint operation (like
 *			SCHKPNT but operates at thread-level).
 * TCHKPNT_BLOCK	Don't set TCHKPNT on this thread.
 * TCHKPNT_STOPPED	Thread is currently stopped during or after a
 *			checkpoint, but is still in the handler.
 * TLSLICE		local time slice pending
 * TPROFIL		Thread profiling
 * TMIGRATE		Thread migration
 * TDISSTK		Disable stack execution
 * TFINTR		Forced interrupt
 * TTRAPSTOP		Thread is stopped for trap handling
 * TTHRDTRAP		Thread-level trap has been hit
 */
#define TUEXEMPT		0x00000001
#define TTIMESLICE_GRANT	0x00000002
#define TNOVALIDATE		0x00000004
#define TISIGINTR    		0x00000010
#define TCHKPNT			0x00000020
#define TCHKPNT_BLOCK		0x00000040
#define TCHKPNT_PROCESS		0x00000080
#define TCHKPNT_SLEEP		0x00000100
#define TCHKPTSTOP		0x00000200
#define TCORE			0x00000400
#define TLSLICE			0x00000800
#define TPROFIL			0x00001000
#define	TMIGRATE		0x00002000
#define	TDISSTK			0x00004000
#define TFINTR			0x00008000
#define TTRAPSTOP		0x00010000
#define TTHRDTRAP		0x00020000
#define TCHKPNT_STOPPED		0x00800000

/*
 * thread states, tv_state
 */
#define TSNONE		0		/* slot is available    */
#define TSIDL		1		/* being created	*/
#define TSRUN		2		/* runnable		*/
#define TSSLEEP		3		/* awaiting an event    */
#define TSSWAP		4		/* swapped		*/
#define TSSTOP		5		/* stopped		*/
#define TSZOMB		6		/* being deleted	*/

/*
 * types of thread waits, tv_wtype 
 */
#define TNOWAIT		0
#define TWEVENT		1		/* waiting for event(s) 	    */
#define TWLOCK		2		/* waiting for complex lock W 	    */
#define TWTIMER		3		/* waiting for timer 		    */
#define TWCPU		4		/* waiting for CPU (in ready queue) */
#define TWPGIN		5		/* waiting for page in 		    */
#define TWPGOUT		6		/* waiting for page out level 	    */
#define TWPLOCK		7		/* waiting for physical lock 	    */
#define TWFREEF		8       	/* waiting for a free page frame    */
#define TWMEM		9		/* waiting for memory 		    */
#define TWLOCKREAD	10		/* waiting for complex lock R 	    */
#define TWUEXCEPT	11		/* waiting for user exception	    */
#define TWZOMB          12              /* waiting for zombie transition    */
#define TWLOCK_WX       13		/* waiting for serialization lock W */
					/* and own lock in R mode 	    */
#define TWVMMWAIT	14		/* waiting in vmm daemon	    */
#define TWSLOCK		15		/* waiting for simple lock	    */
/*
 * Defines and macros for use with thread table entries
 * Note that TSRADSHIFT affects the internal layout of both TIDs and PIDs,
 * as well as the number of sub-zones defined in pmzone.h.
 */
#define TIDRESERVED	5		/* number of bits reserved in tid */
#define THREADSHIFT	19		/* number of bits in thread index */
#define TGENSHIFT	8		/* thread index offset		  */
#define TGENMASK	((1<<TGENSHIFT)-1)
#define NTHREAD		(1<<THREADSHIFT)
#define TIDMASK		((NTHREAD-1)<<TGENSHIFT)
                                        /* bits of thread index split */
#define TSRADSHIFT      4               /* bits for srad */
#define TIDXSHIFT       (THREADSHIFT-TSRADSHIFT) /* rest of bits for idx */
#define TSRADMASK       ((1L<<TSRADSHIFT)-1)
#define TIDXMASK        ((1L<<TIDXSHIFT)-1)

/* mask for thread table index from tid */
#ifndef __64BIT_KERNEL
#define THREADMASK(tid)   (((tid)&TIDMASK)>>TGENSHIFT)
#else
#define THREADMASK(tid) \
	((((tid) & (TSRADMASK << TGENSHIFT)) << (TIDXSHIFT-TGENSHIFT)) | \
	((ulong)(tid) >> (TGENSHIFT+TSRADSHIFT)))
#endif

/* mask for tid from thread table index */
#ifndef __64BIT_KERNEL
#define TIDGEN(idx)     ((idx)<<TGENSHIFT)
#else
#define TIDGEN(idx)     \
        (((((idx) & (TIDXMASK)) << (TSRADSHIFT)) | \
        (((idx) & (TSRADMASK<<TIDXSHIFT)) >> TIDXSHIFT)) << TGENSHIFT)
#endif


/*
 * Address space lock flags 
 * A thread will have either V_ADSP_R (base) or V_ADSP_CS (intpager) 
 * will be set in a read mode. And the flag V_ADSP_W is set when
 * the lock is taken from base level in write mode.
 */ 
#define V_ADSP_R	0x01	/* holding in read mode - base level */
#define V_ADSP_W	0x02	/* waiting for write mode - base level*/
#define V_ADSP_CS	0x04	/* holding in critical section - read mode*/

/* tid are odd, but 1 is a pid too */
#define MAYBE_TID(tid)	(tid & 1)

/* the null tid */
#define NULL_TID	0

/* swapper's tid (may be any odd number less than 1<<TGENSHIFT) */
#define SWAPPER_TID	3		/* 1 may be confused with init's PID */

#ifdef _KERNEL
extern struct pvthread pvthread[NTHREAD];/* the thread table, itself      */

/* convert tid to thread pointer	*/
#define PVTHREADPTR(tid)	(&pvthread[THREADMASK(tid)])

#define TID_VALIDATE(tid) \
	((((THREADMASK(tid)>>TIDXSHIFT) >= PM_NUM_ZONES) || \
	(PVTHREADPTR(tid) >=  				\
		(struct pvthread *) pvthread_cb.primary 	\
	[THREADMASK(tid)>>TIDXSHIFT]->highwater_addr) || 	\
        (PVTHREADPTR(tid)->tv_tid != (tid))) ?    		\
                 NULL : PVTHREADPTR(tid))
#endif



/*
 * SCHED_OTHER must be defined here in case thread.h is included before
 * sys/proc.h (ios/dispauth_paged.c case). 
 * The defined SCHED_OTHER value will be overwritten when include
 * sys/sched.h.
 */
#define SCHED_OTHER 0
	
#define EXTRACT_T_NICE(t)                                               \
        (((t)->t_policy == SCHED_OTHER) ?                               \
	 ((t)->t_nice - PUSER) : (P_NICE_MAX + 1))			      

#define SET_T_NICE(t,n)                                                 \
{                                                                       \
	if ((t)->t_policy == SCHED_OTHER) {                             \
	(t)->t_nice=(MIN(P_NICE_MAX,MAX(0,(n)))) + PUSER;               \
	}                                                               \
} 
	
/*
 * Constants used by user locks
 */
#define UL_FREE			0x00000000
#define UL_BUSY			0x10000000
#define UL_WAIT			0x20000000
#define UL_WAIT_LOCAL           0x40000000
#define UL_INTERLOCK            0x80000000
#define UL_MASK            	0x0fffffff

/*
 * Flags to thread_twakeup_event.
 */
#define THREAD_TWAKEUP_ALL	0
#define THREAD_TWAKEUP_ONE	1

/*
 * tstate flag values controlling thread states 
 */
#define TSTATE_LOCAL		0x00000001
#define TSTATE_CANCEL_DEFER	0x00000004 
#define TSTATE_CANCEL_DISABLE	0x00000008 
#define TSTATE_CANCEL_PENDING   0x00000010
#define TSTATE_CANCEL_CHKPT     0x00000040

/* 
 * tstate flag values used by thread_setstate() and thread_setstate_fast()
 */ 
#define TSTATE_INTR		0x00000002	/* provided for compat only. */
#define TSTATE_CANCEL_START	TSTATE_INTR	
#define	TSTATE_EXEMPT		0x00000020	/* uses critical sections */
#define TSTATE_PROFILING_OFF	0x00000080	/* turn off thread profiling */
#define TSTATE_SUSPEND		0x00000100	/* suspend a pthread	     */
#define TSTATE_CONT		0x00000200	/* continue a pthread	     */
#define TSTATE_CREDS		0x00000400	/* set thread credentials    */
#define TSTATE_PROCHANDLERS	0x00000800	/* per-process handlers */
#define TSTATE_ADVH 		0x00001000	/* Advanced handler thread   */
#define TSTATE_SYNCH		0x00002000
#define TSTATE_USCHED		0x00004000
#define TSTATE_DEFAULT_SCHED    0x00008000	/* Enforce SCHED_OTHER policy */
						/*  when attr NULL specfied.  */
#define TSTATE_INHERIT_SCHED	0x00010000	/* Inherit the sched params  */
#define TSTATE_LOCAL_INIT	0x00020000	/* pthread has created */
#define TSTATE_LOCAL_TERM	0x00040000	/* pthread has exited */
#define TSTATE_LOCAL_MCHANGE	0x00080000	/* pthread mode has changed */

/* 
 * tstate flag values used by thread_setmystate()
 */
#define TSTATE_CHANGE_ALL       0xfff00000
#define TSTATE_CHANGE_PTID	0x00100000	
#define TSTATE_CHANGE_PROFILE	0x01000000	
#define TSTATE_CHANGE_SSTACK	0x02000000	
#define TSTATE_CHANGE_ERRNOP	0x04000000	
#define TSTATE_CHANGE_SIGMASK	0x08000000	
#define TSTATE_CHANGE_PSIG	0x10000000	
#define TSTATE_CHANGE_SCHED	0x20000000	
#define TSTATE_CHANGE_FLAGS	0x40000000	
#define TSTATE_CHANGE_USERDATA	0x80000000	

/* Only the following flags are supported by thread_setmystate_fast */
#define TSTATE_MYFAST_ALL	(TSTATE_CHANGE_FLAGS | \
				 TSTATE_SUSPEND      | \
				 TSTATE_PROFILING_OFF)

/*
 * return codes from thread_wait 
 */
#define THREAD_WAIT_OK		 0
#define THREAD_WAIT_TIMEDOUT	 1
#define THREAD_WAIT_ERROR	-1

#define MAX_POSTED_THREADS	512

/*
 * Structure used by thread_cputime
 */
typedef struct {
	uint64_t utime;
	uint64_t stime;
} thread_cputime_t;

/*
 * Structure used by thread_setstate() and thread_setmystate() syscalls.
 */

/* First the application view */
#ifndef _KERNEL
struct tstate {

#ifdef __64BIT__ 
        struct __context64 mst;
        int		**errnop_addr;
#else
	struct mstsave	mst;
	__ptr32		errnop_addr;
#endif	/* __64BIT__ */
        sigset_t        sigmask;
        sigset_t        psig;
        int             policy;
        int             priority;
        int             flags;
        int             flagmask;
        long		userdata;
	uint		fpinfo;
	uint		fpscrx;
	stack_t		sigaltstack;
	__ptr64		thread_control_p;
	void		*prbase;
	void		*credp;
	uint		ptid;
	uint            tct_clock;
	u_longlong_t	ukeyset;
	struct rusage   rusg;
};

#else	/* _KERNEL */

/* Now the kernel view of the structure for 32-bit apps, the kernel view
 * of the tstate structure for 64-bit apps is defined as tstate64
 * for both 32-bit and 64-bit kernels (this is defined inside _KERNSYS
 * to protect the stack64_t structure which is available only with that
 * define).
 */
struct tstate {
	struct mstsave32 mst;
	ptr32		errnop_addr;
	sigset32_t	sigmask;
	sigset32_t	psig;
	int		policy;
	int		priority;
	int		flags;
	int		flagmask;
	int		userdata;
	uint		fpinfo;
	uint		fpscrx;
	stack_t		sigaltstack;
	ptr64		thread_control_p;
	ptr32		prbase;
	ptr32		credp;
	uint		ptid;
	uint            tct_clock;
	u_longlong_t	ukeyset;
	struct trusage32 rusg;
};

#ifdef _KERNSYS
/* kernel definition of struct tstate for a 64-bit process */
struct tstate64 {
        struct __context64 mst;
        unsigned long long errnop_addr;
        sigset64_t	sigmask;
        sigset64_t	psig;
        int             policy;
        int             priority;
        int             flags;
        int             flagmask;
        unsigned long long userdata;
	uint		fpinfo;
	uint		fpscrx;
	stack64_t	sigaltstack;
	ptr64		thread_control_p;
	ptr64		prbase;
	ptr64		credp;
	uint		ptid;
	uint            tct_clock;
	u_longlong_t	ukeyset;
	struct trusage64 rusg;
};

/* kernel definition for union of tstate and tstate64 */
union ts3264 {
        struct tstate ts32;
        struct tstate64 ts64;
};

#endif		/* _KERNSYS */
#endif		/* _KERNEL */

struct func_desc {
	char *entry_point;
	char *toc_ptr;
	char *data_ptr;
};

struct func_desc32 {
	int entry_point;
	int toc_ptr;
	int data_ptr;
};

/* Kernel view of thread credentials structure (size-invariant) */
typedef struct thread_credentials {
	uint 		flags;		/* Control structure data */
	cred_ext_t	cred;		/* Credentials to be modified */
	int 		reserved[9];	/* reserved fields for future */
} thread_creds_t;


/* thread_credentials.flags */

#define INHERIT_USER_IDS	0x00000001
#define INHERIT_GROUP_IDS	0x00000010
#define INHERIT_GROUP_SETS	0x00000100
#define INHERIT_CAPABILITIES	0x00001000
#define INHERIT_PRIVILEGES	0x00010000
#define INHERIT_ALL		0x00011111

#ifndef errno
extern int errno;
#endif
extern int *errnop;

/*
 * thread-related routines
 */
#ifdef _NO_PROTO

#ifdef _KERNEL
void	kthread_kill();
tid_t	kthread_self_getpid();
int	kthread_start();
#endif	/* !_KERNEL */

#ifndef _KERNEL
int	thread_cputime();
#endif
tid_t	thread_create();
void	thread_init();
int	thread_kill();
int     thread_sigsend();
int	thread_boostceiling();
int     thread_post();
int     thread_post_many();
tid_t	thread_self();
int	thread_setcredentials();
int	thread_setmystate();
int     thread_setmystate_fast();
int     thread_setmymask_fast();
int	thread_setsched();
int	thread_setstate();
int	thread_setstate_fast();
void	thread_terminate();
int	thread_terminate_ack();
void    thread_terminate_unlock();
int	thread_getregs();
int	thread_getextregs();
int	thread_tsleep();
int	thread_tsleep_chkpnt();
int	thread_tsleep_event();
int	thread_twakeup();
int	thread_twakeup_event();
int     thread_twakeup_unlock();
int	thread_unlock();
long	thread_userdata();
int     thread_wait();
int	thread_waitlock();
int	thread_waitlock_local();
int	thread_waitlock_();
int	thread_waitlock_local_();
int     thread_waitact();
void    threads_runnable();
int	count_event_waiters();
void	thread_callout();

#else /* _NO_PROTO */

#ifdef _KERNEL
void	kthread_kill(tid_t, int);
tid_t	kthread_self_getpid(pid_t *);
int	kthread_start(tid_t, void (*)(void *), void *,size_t,void *,sigset_t *);
#endif	/* !_KERNEL */

#ifndef _KERNEL
int	thread_cputime(tid_t, thread_cputime_t *);
#endif
tid_t	thread_create(void);
#ifdef _KERNEL
#ifdef __64BIT_KERNEL
void	thread_init(ulong, ulong, ulong, ulong);
#else
void	thread_init(unsigned long long, unsigned long long);
#endif /* __64BIT_KERNEL */
#else
void	thread_init(unsigned long long, unsigned long long);
#endif /* _KERNEL */
int	thread_kill(tid_t, int);
int     thread_sigsend(tid_t, int);
int     thread_post(tid_t);
int     thread_post_many(int, tid_t *, tid_t *);
tid_t	thread_self(void);
int	thread_setcredentials(int, struct thread_credentials *);
int	thread_setmystate(struct tstate *, struct tstate *);
#ifdef _KERNEL
int	thread_setmystate_fast(int, ulong, ulong);
int	thread_setmymask_fast(int, int);
#else
int	thread_setmystate_fast(int, int **, ulong);
int	thread_setmymask_fast(sigset_t);
#endif /* _KERNEL */
int     thread_boostceiling(int, int);
int	thread_setsched(tid_t, int, int);
int	thread_setstate(tid_t, struct tstate *, struct tstate *);
int	thread_setstate_fast(tid_t, int);
void	thread_terminate(void);
int	thread_terminate_ack(tid_t);
void    thread_terminate_unlock(atomic_p);
int	thread_getregs(tid_t, mcontext_t *, ulong *, ulong *, int *);
int	thread_getextregs(tid_t, __extctx_t *);
int     thread_tsleep(int, atomic_p, const sigset_t *, struct timestruc_t *);
int     thread_tsleep_chkpnt(int, atomic_p, const sigset_t *);
int     thread_tsleep_event(void *, atomic_p, int, struct timestruc_t *);
int	thread_twakeup(tid_t, int);
int     thread_twakeup_event(void *, int, int);
int     thread_twakeup_unlock(tid_t, int, atomic_p);
int	thread_unlock(atomic_p);
long	thread_userdata(void);
int     thread_wait(int);
int	thread_waitlock(atomic_p);
int	thread_waitlock_local(atomic_p);
int	thread_waitlock_(atomic_p, int, struct timestruc_t *);
int	thread_waitlock_local_(atomic_p, tid_t, struct timestruc_t *);
int     thread_waitact(int);
void    threads_runnable(int);
int	count_event_waiters(void *);
void	thread_callout(tid_t, uint);

#endif /* _NO_PROTO */

#ifdef __cplusplus
}
#endif

#endif  /* _H_THREAD */


