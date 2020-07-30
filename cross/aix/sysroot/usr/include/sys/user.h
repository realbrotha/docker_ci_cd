/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/user.h 1.51.17.7                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1985,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)93       1.51.17.7  src/bos/kernel/sys/user.h, sysproc, bos53V, v2009_12B2 2/25/09 09:45:37 */

#ifndef _H_USER
#define _H_USER

#ifdef __cplusplus
extern "C" {
#endif

/*
 *			User Structure (u-block)
 *
 * FUNCTION:
 *	The user structure is also called the user area or u-block.
 *	There is one allocated per process, including kernel processes.
 *	It is protected to disallow any access to it by user-mode code.
 *
 *	The u-block contains information about the process that
 *	need not be in memory when the process is swapped out.
 *	It is pinned when the process is swapped into memory, and
 *	unpinned out when the process is swapped out.
 *
 * NOTES:
 *	The size of the u-block directly affects the #define's in
 *	include/sys/pseg.h.  If the size of the u-block is changed,
 *	these values should be checked to see if they need to be
 *	updated.  The initial portion of the u-block is also defined
 *	in ml/POWER/32/user.m4. Changes to the beginning of the user
 *	structure must be refected there, too.
 */

#include <sys/types.h>
#include <sys/param.h>
#include <sys/limits.h>
#include <sys/dir.h>
#include <uinfo.h>
#include <sys/seg.h>
#include <sys/signal.h>
#ifndef _KERNSYS
#include <a.out.h>
#endif
#include <sys/mstsave.h>
#include <sys/proc.h>
#include <sys/vnode.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/timer.h>
#include <sys/cred.h>
#include <sys/sem.h>
#include <sys/xmem.h>
#include <sys/uprintf.h>
#include <sys/low.h>
#include <sys/pmzone.h>
#include <sys/uthread.h>
#include <sys/uio.h>
#include <sys/wlm.h>
#include <stddef.h>

/*
 * The definition of struct prof64, corresponding to struct prof from
 * mon.h compiled in 64-bit mode, is required for U_prof.
 * Due to name conflicts, we can't include mon.h in the kernel, so the
 * prof64 structure is defined here.  It is only needed by the kernel
 * profiling support to describe how we save profiling arguments.
 * It isn't needed on the user side at all, since the standard struct prof
 * produces this result automatically when compiled in 64-bit mode.
 * However, it must always be produced to satisfy the compiler.
 */
struct prof64 {
        unsigned long long p_low;	/* low sampling address */
        unsigned long long p_high;	/* high sampling address */
        unsigned long long p_buff;	/* address of sampling buffer */
        int		   p_bufsize;	/* buffer size - monitor/HISTCOUNTERs,
					 * profil/bytes 
					 */
        uint		   p_scale;	/* scale factor */
};

struct profdata {
	unsigned long long pr_base; 	/* user addr of prof buff */
	unsigned long long pr_off;  	/* pc offset, start prof'd range */
	uint		   pr_size;	/* size of profiling buffer */
	uint		   pr_scale;	/* pc scaling, <= 0xffff */
	/*
	 * pr_special is non-NULL when non-traditional args are used.
	 * This is indicated on the user side with a buffer size of -1.
	 *
	 * Note that the prof_spc structure is not a true mapping
	 * of the storage xmalloc'd in the kernel to save the non-
	 * traditional profiling arguments.  There will actually be
	 * 2 or more prof64 structures (the list is terminated by
	 * pr_array[last+1].p_high being zero).
	 * However, it is essential that pr_array be dimensioned at
	 * 1 to agree with the code that xmalloc's struct prof_spc.
	 * The number of bytes allocated is
	 *
	 *   sizeof(struct prof_spc) + (last * sizeof(struct prof64))
	 *
	 * The reference count, pr_ref, indicates the number of
	 * processes currently sharing the copied arguments, which
	 * are inherited over fork.
	 */
	struct prof_spc {
		int		pr_ref;		/* reference count for range */
		struct prof64 	pr_array[1];	/* >= 2 range descriptors */
	} *pr_special;
	uint		pr_flags;	/* Profiling flags */
	ushort		pr_bufcount;	/* PC Buffer count */
	unsigned long long *pr_pinned;	/* Pinned PC buffer */	
	tid_t		pr_synch;	/* Event List for Profiling */
};

/* Defines for profdata.pr_flags (these are protected by U.U_timer_lock)
 * and the U_handy_lock (need both to update, any one to read)
 * The __PC_PINNED_MASK is PC buffer specific and so can be set for the
 * thread-level buffer also
 */

#define __PROF_ON_MASK		0x0001
#define __PROF_NORM_MASK	0x0002
#define __PROF_ADV_MASK		0x0004
#define __PROF_PROCESS_MASK	0x0008
#define __PROF_THREAD_MASK	0x0010
#define __PROF_OFF_MASK		0x0020	/* serializes (t)profil without locks */

#define __PC_PINNED_MASK	0x0100	/* Valid pinned PC buffer */

/* 
 * These are flags on the buffer state and are buffer-specific, these
 * are protected by the U_handy_lock (never checked by the interrupt
 * handler). Also, the __PC_FLUSH_MASK is
 * updated only in context (so can be read without any locks by curthread).
 * These are defined only for thread-level profiling buffers
 * __PC_FLUSH_MASK : Serializes profilx_off() and flush_PC_buffer()
 * __PC_PINNED_MASK: Lets timer know it can call addupc (for threads)
 * __PC_HISTOGRAM_MASK: Lets kernel know that it is valid to flush PCs
 */
#define __PC_FLUSH_MASK		0x0200	/* PC buffer being flushed */
#define __PC_PENDOFF_MASK	0x0400	/* PC being disabled */
#define __PC_HISTOGRAM_MASK	0x0800  /* Valid histogram buffer (thread) */

#define __PROFILING_ON()	(U.U_prof.pr_flags & __PROF_ON_MASK)
#define __PROFILING_NORM()	(U.U_prof.pr_flags & __PROF_NORM_MASK)
#define __PROFILING_ADV()	(U.U_prof.pr_flags & __PROF_ADV_MASK)
#define __PROFILING_PROCESS()	(U.U_prof.pr_flags & __PROF_PROCESS_MASK)
#define __PROFILING_THREAD()	(U.U_prof.pr_flags & __PROF_THREAD_MASK)
#define __PROFILING_OFF()	(U.U_prof.pr_flags & __PROF_OFF_MASK)

/* The following macros are buffer specific and the flags are set 
 * at the thread level (see tv_pr_flags in thread.h)
 */
#define __PC_VALID_PINNED(__pr_flags)    ((__pr_flags) & __PC_PINNED_MASK)
#define __PC_VALID_HISTOGRAM(__pr_flags) ((__pr_flags) & __PC_HISTOGRAM_MASK)
#define __PC_FLUSHING(__pr_flags)	 ((__pr_flags) & __PC_FLUSH_MASK)
#define __PC_PENDING_OFF(__pr_flags)	 ((__pr_flags) & __PC_PENDOFF_MASK)

/*
 * User address space lock structure.
 * Lock Policy : U_adspace_lock must be taken before U_handy_lock
 */
struct vmmlock {
	vmm_lock_t	lock_word;	/* per-process U_adspace lock */
	struct thread	*vmm_lock_wait;	/* wait list for lock waiters */
};

/* 
 * User's file descriptor table 
 */
struct ufd {
	struct file *	fp;
	unsigned short	flags;
	unsigned short	count;
#ifdef __64BIT_KERNEL
	unsigned int 	reserved;
#endif /* __64BIT_KERNEL */
};

struct fdblock {
	struct ufd *	ufd_block;	/* block of file descriptors */
	uint32_t	ufd_free;  	/* count of free FDs in block */
	uint32_t	ufd_lowfd;  	/* lowest free file descriptor */
	uint32_t	ufd_maxfd;  	/* highest allocated file descriptor */
#ifdef __64BIT_KERNEL
	uint_t 		reserved;
#endif /* __64BIT_KERNEL */
};

typedef struct {    /* file descriptor lock cacheline */
	Simple_lock     u_fd_slock;
	char            cache_pad[128-sizeof(Simple_lock)];
} fd_lock_t;


/* Memory placement policies for user memory objects
 */
typedef union umem_policy {
	struct  _obj_policy {
		unsigned _unused	:18;
		unsigned _text		:2;
		unsigned _stack		:2;
		unsigned _data		:2;
		unsigned _shm_named	:2;
		unsigned _shm_anon	:2;
		unsigned _mapped_file	:2;
		unsigned _unmapped_file	:2;
	} obj_policy;
	uint policybits;
} umem_policy_t;

/*
 * command limits for exec files:
 *	SHSIZE is the limit for the #! line in an interpreted file
 *	MAXCOMLEN is the size limit for the base name of the exec file
 *		that is saved in the u-block.
 */
#define SHSIZE		32		/* short form exec size */
#define	MAXCOMLEN	32		/* <= MAXNAMLEN, >= sizeof(ac_comm) */

#define NUM_PMSEGS	16		/* number of thread data segements */

#define NISIG		4

struct ckpt_ipcid;
struct _mmapent;
struct rt_ipc_user;
struct mlock_entry;
struct user {

	/* swappable process context */
	unsigned long long U_chk_paddr; /* address of checkpnt_pending var */
	struct saioq_head *U_saioq_head;/* anchor for async socket queue */
	uid_t		   U_sv_sgid;   /* set group identifier at exec time */
	int 		   U_num_pmsegs;/* number of PM segments */
	vmhandle_t 	   *U_pm_segs;	/* PM segments */
	vmhandle_t 	   U_pm_space;	/* space for first PM segment */
	vmhandle_t 	   U_text_vmh;	/* text seg vmhandle for memusage */
        unsigned long long U_cancel_func;/* cancelation user entry point */
        unsigned long long U_cancel_toc;/* cancelation user entry point */
	struct proc	*U_procp;	/* pointer to proc structure */
	Simple_lock	U_handy_lock;	/* self preservation lock */

#ifdef __64BIT_KERNEL
#ifdef _POWER
	/* U_segs32 must be pinned and must not cross a page boundary */
        void            *U_segs32_raddr; /* real addr of U_segs32 */
        vmhandle_t      U_segs32[NSEGS]; /* shadow of first 4Gb for resume() */
#endif /* _POWER */
#endif /* __64BIT_KERNEL */

	/* signal management */
	void		(*U_signal[NSIG32+NISIG])(int);/* disposition of sigs */
	sigset32_t	U_sigmask[NSIG32+NISIG];       /* sig's to be blocked */
#ifdef __64BIT_KERNEL
	uint		U_sigflags[NSIG+NISIG];	
#else
	ushort		U_sigflags[NSIG64+NISIG];/* ushort-save space for now*/
#endif /* __64BIT_KERNEL */

	/* user-mode address space mapping */
#ifndef __64BIT_KERNEL
	adspace_t	U_adspace;	/* user-mode address space */
	struct segstate U_segst[NSEGS]; /* info on use of each segment */
#else
#ifdef _POWER
        void *    	U_uastrtp;      /* strt addr for V_USERACC */
	vmsize_t  	U_uasize;       /* size of the V_USERACC buf */
#endif /* _POWER */
	struct asalloc  U_snode;	/* segment node allocation */
	struct asalloc  U_unode;	/* uadspace node allocation */
        struct uadnode  U_adspace32[NADNODES]; /* usr adspace 32bit process */
        struct segnode  U_segnode[NSEGNODES]; /* segnode for 32bit processes */
#endif /* __64BIT_KERNEL */
	struct vmmlock 	U_adspace_lock;
	int		U_vmmflags;	/* vmm process state flags */

#define	U_lock_word	U_adspace_lock.lock_word
#define U_vmm_lock_wait	U_adspace_lock.vmm_lock_wait

	/* auditing stuff */
	int		U_auditstatus;	/* auditing RESUME or SUSPEND */

	/* address map (mmap) */
	char		*U_map;

	/* current exec file information */
 	char		U_comm[MAXCOMLEN+1]; /* basename of exec file */

	int		U_ncargs;	     /* ARGMAX value during exec */

	/*
	 * Program model information, 64bit and 32bit, small and large data.
	 * The 'max' values are the maximums allowed by the model, which
	 * may be smaller than the current resource limits.
	 * These fields are filled in during exec.
	 *
	 * There is no U_stksize field.  The stack is allowed whatever it can
	 * get, subject to resource limits, model limits (possibly set from
	 * the a.out header during exec), and, in 32-bit mode, the PRIVSEG
	 * data break address.  The get_stack_size routine will return the
	 * current maximum effective size of the stack.
	 *
	 * Other fields:
	 *   U_breakhiwater: the high water mark for the break value
	 *   U_minbreak: the smallest permitted break value
	 *   U_min_mmap: If non-zero, smallest address allowed for mmap()
	 *		or shmat() at a user-specified address.
	 */
	unsigned long long U_tstart;	/* start of text	*/
	unsigned long long U_tsize;	/* text size (bytes)	*/
	unsigned long long U_datastart;	/* start of data	*/
	unsigned long long U_datasize;	/* Current data size (bytes)	*/

	/* DABR watchpoint information */
	unsigned long long U_wp_dabr;	/* DABR value for ptrace watchpoint */
	unsigned long long U_wp_value;	/* current value at watched address */

	/* System call table information */
	void		*U_svc_table;	/* svc table address  */
	int		U_max_svcnum;	/* max allowed svc number for process */
	char		U_textl2psize;	/* log 2 page size of text segment */
	char		U_datal2psize;	/* log 2 page size of future data */
	char            U_stackl2psize; /* log 2 page size of stack */

#define U_DR_MEM_PERCENT_DEFAULT	100
	char 		U_dr_mem_percent;    /* percentage of DR mem request */

	char		U_shml2psize;	/* log 2 page size of shared memory */
#ifdef __64BIT_KERNEL
	char		U_pad2[3];
	struct pathname *U_cdirpnp;	/* Current directory name */
	char            *U_rdir_pathp;	/* path name of root directory */
#else
	char		U_pad2[11];
	struct pathname *U_cdirpnp;	/* Current directory name */
	char            *U_rdir_pathp;	/* path name of root directory */
#endif
	long long	U_dscr_reg;	/* Data Streams Control Register */

	unsigned long long U_datamax;	/* Maximum data size (bytes)	*/
	unsigned long long U_minbreak;	/* minimum/initial break address */
	unsigned long long U_breakhiwater; /* Largest break address so far */
	unsigned long long U_min_mmap;	/* Minimum shmat/mmap address allowed */

	uint		U_brkseg;	/* segment number of U_breakhiwater */
	uint		U_stkseg;	/* Lowest segment number of stack */

	unsigned long long U_stkstart;	/* stack start (grows downwards) */
	unsigned long long U_stkmax;	/* stack max (bytes)	*/

	/*
	 * The following macros compute some commonly required values
	 * about the addressing model.
	 *
	 * U_BIGDATA	Tells you whether the 32-bit large data model
	 *		is in effect.
	 * U_PDATASIZE	Is the current data size for a 32-bit process
	 *		in the private segment (hence the P).
	 *		Note - this is always the PRIVSEG data size; with
	 *		the large data model, the general data size is
	 *		separate, as data begins in the BDATASEG.
	 * U_PDATABRK	Is the current data break address of a 32-bit process
	 *		in the private segment (see above).
	 * U_DATABRK	Is the general data break address in all cases.
	 * U_DSIZE	Is for compatibility only.  Use it to fill in fields
	 *		that previously were copies of U_dsize, which is now
	 *		obsolete.
	 */
#define U_BIGDATA(U)	((U)->U_datastart == BDATAORG)
#define U_PDATASIZE(U)	((U_BIGDATA(U) || SLPDATA_SET(U)) ? (U)->U_sdsize \
                                                       : (uint)(U)->U_datasize)
#define U_PDATABRK(U)	(PRIVORG_LO + U_PDATASIZE(U))

#define U_DATABRK(U)	((U)->U_datastart + (U)->U_datasize)	/* 1st inval */

#define	U_DSIZE(U)	((uint)(U)->U_datastart + (uint)(U)->U_datasize \
			- PRIVORG_LO)

	unsigned int	U_sdsize;	/* Size of data for privately loaded
					   modules, if the bigdata model is
					   being used. */
	short		U_lock; 	/* process/text locking flags */
	char		U_64bit;	/* 0 if 32-bit process, 0x1 if 64-bit */
	char		U_emul;		/* emulation type (UW7, etc.) */
	struct mlock_entry **U_memlock; /* real time memory lock */

	/* user identification and authorization */
	Simple_lock	U_cr_lock;	/* credentials lock */
        struct ucred    * volatile U_cred; /* user credentials (uid, gid, etc) */

#define GETEUID()	U.U_cred->cr_uid
#define GETRUID()	U.U_cred->cr_ruid

#define U_uid		U_cred->cr_uid
#define U_ruid		U_cred->cr_ruid
#define U_suid		U_cred->cr_suid
#define U_luid		U_cred->cr_luid
#define U_acctid	U_cred->cr_acctid
#define U_gid		U_cred->cr_gid
#define U_rgid		U_cred->cr_rgid
#define U_sgid		U_cred->cr_sgid
#define U_groups	U_cred->cr_groups
#define U_epriv		U_cred->cr_epriv
#define U_ipriv		U_cred->cr_ipriv
#define U_bpriv		U_cred->cr_bpriv
#define U_mpriv		U_cred->cr_mpriv

	uinfo_t 	U_uinfo;	/* usrinfo() buffer */
	uinfox_t 	*U_uinfoxp;	/* extended usrinfo pointer */
	int		U_compatibility;/* compatibility/user mode bit masks */

	/* defines for u.u_compatibility bit mask */
#define PROC_RAWDIR	1	/* read directories raw mode, no */
				/* translation to dirents 	 */

	struct sem_undo	*U_semundo;	/* semaphore undo struct pointer */

	/* accounting and profiling data */
	time_t		U_start;
	time_t		U_ticks;
	struct profdata U_prof;
	short		U_acflag;	/* accounting flag */
	struct trusage64 U_ru;		/* this process resource usage value */
	struct trusage64 U_cru;		/* accumulated children's resources */
        /*
         * The kernel uses U_ru & U_cru to keep track of the time used by
         * the process and its children.
         * Even though the ru_utime & ru_stime fields within U_ru & U_cru are
         * struct timeval, their granularity within the kernel is nanoseconds,
         * not microseconds. This is the granularity returned by getprocs().
         * Other syscalls and library functions convert this to microseconds.
         */

#define U_utime		U_ru.ru_utime.tv_sec	/* this process user time */
#define U_stime		U_ru.ru_stime.tv_sec	/* this process system time */
#define U_cutime	U_cru.ru_utime.tv_sec	/* sum of children's utimes */
#define U_cstime	U_cru.ru_stime.tv_sec	/* sum of children's stimes */

	char		U_pthru;		/* pthread rusage tracking */

	/* virtualized resource usage values */
	struct trusage64 U_vru;
	struct trusage64 U_vcru;

	/* resource limits and counters */
	unsigned long	U_fsblimit;		/* fs limit in 512 byte-blks */

#if defined(_KERNSYS) || defined(__64BIT_KERNEL)
	/* rlimit32 structure is exposed to only 32/64 kernel 
	 * and 64bit kernel extensions 
	 */
	struct rlimit32	U_rlimit[RLIM_NLIMITS];	/* 32-bit resource limits */
#else
	struct rlimit	U_rlimit[RLIM_NLIMITS];	/* 32-bit resource limits */
#endif
	struct rlimit64 U_saved_rlimit[RLIM_NLIMITS]; /* saved 64-bit limits */
        /*
         * To maximize compatibility with old kernel code, a 32-bit
         * representation of each resource limit is maintained in U_rlimit.
         * Should the limit require a 64-bit representation, the U_rlimit
         * value is set to RLIM_INFINITY, with actual 64-bit limit being
         * stored in U_saved_rlimit.  These flags indicate what
         * the real situation is:
         *
         *   RLFLAG_SML => limit correctly represented in 32-bit U_rlimit
         *   RLFLAG_INF => limit is infinite
         *   RLFLAG_MAX => limit is in 64_bit U_saved_rlimit.rlim_max
         *   RLFLAG_CUR => limit is in 64_bit U_saved_rlimit.rlim_cur
         *
         * These flags are for use by the getrlimit/setrlimit routines only.
         * Kernel code desiring a 64-bit limit must go through kgetrlimit.
         */
        struct {
                uchar rlim_cur;                 /* how to determine rlim_cur */
                uchar rlim_max;                 /* how to determine rlim_max */
	} U_rlimit_flag[RLIM_NLIMITS];

#define U_smax          U_rlimit[RLIMIT_STACK].rlim_cur /* soft limit max stack */
/* since vmm does not maintain current stack size we use the max */
#define U_ssize         U_rlimit[RLIMIT_STACK].rlim_cur /* current stack size */
#define U_dmax          U_rlimit[RLIMIT_DATA].rlim_cur 	/* soft data limit */
#define U_minflt        U_ru.ru_minflt          /* minimum page fault count */
#define U_majflt        U_ru.ru_majflt          /* major page fault count */
#define U_ior		U_ru.ru_inblock		/* block read count */
#define U_iow           U_ru.ru_oublock         /* block write count */

	unsigned long long U_ioch; 		/* I/O character count */

	/* timers */
	Simple_lock	 U_timer_lock;
	struct trb	 *U_timer[NTIMERS];	     /* per process timers */

	/* controlling tty info */
  	pid_t		*U_ttysid;	/* ptr to session leader id in tty */
	pid_t		*U_ttyp;	/* ptr to controlling tty pgrp field */
	dev_t		U_ttyd; 	/* controlling tty dev */
	long		U_ttympx;	/* mpx value for controlling tty */
	unsigned	*U_ttys;	/* pointer to t_state in tty struct */
	int32long64_t	U_ttyid;	/* tty id */
	int		(*U_ttyf)();	/* tty query function pointer */

	struct upfbuf	*U_message;	/* uprintf buffer pointer */
	struct trb *   	U_trb;		/* trb for user scheduler */
	struct pvthread	*U_chktv;	/* pointer to adv handler pvthread */

	/* file system state */
	vmid_t		U_pn_segno;	/* sid of chkpt/restart pathname seg*/
	Simple_lock	U_pnseg_lock;	/* lock of chkpt/restart pathname seg*/
	struct vnode	*U_cdir;	/* current directory of process */
	struct vnode	*U_rdir;	/* root directory of process */
	short		U_cmask;	/* mask for file creation */
	Simple_lock	U_fso_lock;	/* other file system fields lock */
	long		U_lockflag;	/* process has done file locks */
	long		U_fdevent;	/* fd lock event list */

        long long       U_irss;         /* accumulator for memory integral */
	struct pinu_block *U_pinu_block;/* list of control structs for pinu */
	tid_t		U_ulocks;	/* event list for user locks */
	int32long64_t	U_rmmap;	/* anchor of rmmap list	*/

	unsigned long long U_loader[84]; /* loader area */
	Simple_lock     U_aio_susp_lock; /* aio lock used in aio_suspend */
	unsigned int    U_fdfree[2];    /* file descriptor management */

	unsigned int    U_cannot_chpt;  /* process unable to checkpoint */
	unsigned int	U_maxofile;	/* maximum u_ofile index in use */
	unsigned int	U_freefile;	/* first available u_ofile index */

	/* WLM data */
	dev64_t		U_dev;		/* device of exec'ed file */
	ino64_t		U_ino;		/* inode */
	uint_t		U_gen;		/* generation number */
	char		U_tag[WLM_TAG_LENGTH+1]; /* WLM tag: user settable string */

	/*  structures added for VMM checkpoint/restart support */
        struct ckpt_ipcid *U_ckptshm;   /* ptr to shmid blocks for checkpoint   */
        struct ckpt_ipcid *U_ckptsem;   /* ptr to semid blocks for checkpoint   */
        struct ckpt_ipcid *U_ckptmsg;   /* ptr to msgid blocks for checkpoint   */
        struct _mmapent   *U_mapent;    /* ptr to mmap entry structure used for restart */
	ut_error_t	   U_ckpterr;   /* u_error saved during ckpt processing */

#define U_FDBLKS 4			/* file descriptor blocks in ublock */

#ifdef __64BIT_KERNEL
	void		  *U_pollcache; /* pollcache list */
	Simple_lock	   U_pollcache_lock; /* pollcache list lock */
	fd_lock_t	  *U_fdlockarray;  /* file descriptor lock array */
	int		   U_fdlockcount;  /* number of file desc locks */
	uint32_t	   U_maxusedfd[U_FDBLKS]; /* highest file descriptor
						     ever in use for a block */
	char		   cacheline_pad[80]; /* keep 1st cacheline aligned */
#else
	vmlpghandle_t   U_lpgsegs32[NSEGS]; /* lgpg handles for 32bit processes */
	void		  *U_pollcache; /* pollcache list */
	Simple_lock	   U_pollcache_lock; /* pollcache list lock */
	fd_lock_t	  *U_fdlockarray;  /* file descriptor lock array */
	int		   U_fdlockcount;  /* number of file desc locks */
	uint32_t	   U_maxusedfd[U_FDBLKS]; /* highest file descriptor
						     ever in use for a block */
	char		   cacheline_pad[32];  /* keep 1st cacheline aligned */
#endif /* __64BIT_KERNEL */

	/* CHANGES FROM HERE ON DO NOT AFFECT ASSEMBLER CODE
	   (see ml/POWER/32user.m4) */

	/* file descriptor lock cacheline array */
#define U_FD_LCK_CNT 16	/* must be a power of 2; see U_fd_slock */
	fd_lock_t	U_fd_slcks[U_FD_LCK_CNT];

#ifdef __64BIT_KERNEL
	uint            U_lw_pool_size;      /* lt-weight esid pool sz */
	uint            U_lw_num_pools;      /* num avail pools */
#endif

	/* Memory placement policies for user memory objects */
	umem_policy_t 	U_umem_policy;

#define U_umem_text		U_umem_policy.obj_policy._text
#define U_umem_stack    	U_umem_policy.obj_policy._stack
#define U_umem_data     	U_umem_policy.obj_policy._data
#define U_umem_shm_named      	U_umem_policy.obj_policy._shm_named
#define U_umem_shm_anon  	U_umem_policy.obj_policy._shm_anon
#define U_umem_mapped_file    	U_umem_policy.obj_policy._mapped_file
#define U_umem_unmapped_file    U_umem_policy.obj_policy._unmapped_file
#define U_umem_policybits	U_umem_policy.policybits
	
	/* from here on the data is pageable. */
#define U_nonpinned_offs  	 (offsetof(struct ublock, ub_user) + \
				  offsetof(struct user, U_rtipc))
        struct rt_ipc_user *U_rtipc;         /* real time ipc data */

#define FDPERBLOCK	8192		     /* file descriptors per fd block */
#define FDBLOCKS    	(OPEN_MAX+FDPERBLOCK-1)/FDPERBLOCK
				 	     /* number of descriptor blocks   */
#define U_FILEDESC	U_FDBLKS*FDPERBLOCK  /* file descriptors in ublock    */

	struct fdblock	U_fdblks[FDBLOCKS];  /* fdblock control struct table  */
	struct ufd	U_ufds[U_FILEDESC];  /* array of the first U_FDBLKS   */
					     /*	fd blocks that fit in u-block */
};

#define FDBLKNO(fd)  (((unsigned int)(fd))/FDPERBLOCK) /* fd/8192= fd>>13     */
#define FDINBLK(fd)  (((unsigned int)(fd))%FDPERBLOCK) /* fd%8192= fd & 0x1fff*/
#define INBLK2FD(i,b)	((FDPERBLOCK*(b))+(i))  /* convert fd blk index to fd */
#define FDBLKSIZE	(FDPERBLOCK * (sizeof(struct ufd)))

#define U_fdp(x)	U_fdblks[(FDBLKNO((x)))].ufd_block
#define U_ufd(x)	U_fdblks[(FDBLKNO((x)))].ufd_block[(FDINBLK((x)))]
#define U_ofile(x)	U_fdblks[(FDBLKNO((x)))].ufd_block[(FDINBLK((x)))].fp
#define U_pofile(x)	U_fdblks[(FDBLKNO((x)))].ufd_block[(FDINBLK((x)))].flags
#define U_fd_slock(x)   U_fdlockarray[((x) & (U.U_fdlockcount-1))].u_fd_slock


/* These macros are similar as the above but need the target ublock ub_user */
#define U_FDP(x, y)	y->U_fdp(x)
#define U_UFD(x, y)	y->U_ufd(x)
#define U_OFILE(x, y)	y->U_ofile(x)
#define U_POFILE(x, y)	y->U_pofile(x)

#ifdef	_KERNEL
/*
 * struct user64 contains the data necessary for 64-bit processes.
 */
struct remaps {
	ptr64	addr[16];
	int	hiwater;
};

struct mstext {
	struct mstsave64	mst64; 		/* mstsave for 64-bit */
	struct remaps		remaps;		/* remappings */
};


/*
 * The stab is used as follows :
 *  --------------------------------------------------------------------------
 *  |                | 32 bit processes | 64 bit processes		      |
 *  --------------------------------------------------------------------------
 *  | power_sslb     | 0		|64K + 80bytes for pinned slb entries |
 *  |-------------------------------------------------------------------------|
 *  | bridge         | 4K  		|4K				      |
 *  --------------------------------------------------------------------------
 */
#ifdef __64BIT_KERNEL
/* Maximum number large shared memory regions that can have cached
 * esid->vsid mappings.
 */
#define MAX_LGSHM_RGNS  2
#endif /* __64BIT_KERNEL */

struct user64 {
#ifdef _POWER
#ifdef __64BIT_KERNEL
#define U64_STAB_SIZE	65640
	char		stab[U64_STAB_SIZE];	
#else
	char		stab[4096];		/* hardware segment table */	
	Simple_lock	stablock;		/* lock for segment table */
	struct mstext 	mstext;			/* mstsave + remap array */
#endif /* __64BIT_KERNEL */
#endif /* _POWER */
	ptr64  		U_signal[NSIG64+NISIG];	/* pointers to signal handlers*/
	sigset64_t      U_sigmask[NSIG64+NISIG];       /* sig's to be blocked */

#ifdef __64BIT_KERNEL
	struct {
		ulong      ls_start;		/* start addr of lgshm region */
		ulong      ls_end;		/* end addr: of lgshm region */
		vmhandle_t *ls_handles;		/* 4k large shm handles array */
	} lgshm[MAX_LGSHM_RGNS];
	int             num_lgshm;              /* Number of lgshm regions */
#else
	struct asalloc  snode;			/* segment node allocation */
	struct asalloc  unode;			/* uadspace node allocation */
#endif /* __64BIT_KERNEL */
};

#ifdef __64BIT_KERNEL
#define UBLOCK_OFFSET	0x600		/* see ipl64.exp */
#else
#define UBLOCK_OFFSET	0x400		/* see ipl.exp */
#endif /* __64BIT_KERNEL */

#define UBPAD_OFFSET	((UBLOCK_OFFSET +		\
			  sizeof(struct uthread) +	\
			  sizeof(struct user)		\
			 ) & (PAGESIZE-1))

#define UBPAD (PAGESIZE - UBPAD_OFFSET)		      

/* the ublock
 */
struct ublock {
	struct uthread	ub_uthr0;	/* default uthread structure  */
	struct user	ub_user;	/* user structure */
	char		ub_pad[UBPAD];	/* pad to page boundary */
	struct	user64  ub_user64;	/* extension for 64-bit process */
};

extern struct ublock	__ublock;	/* fixed place in every address space */

#define uthr0		(__ublock.ub_uthr0)	/* constant */
#define U		(__ublock.ub_user)	/* constant */
#define U64		(__ublock.ub_user64)	/* constant */

#ifndef __64BIT_KERNEL
#define ISUADSPACE(adsp) (KHEAPORG64 <= (uint)(adsp) && (uint)(adsp) < KHEAPEND64)
#else
#define ISUADSPACE(adsp) 1
#endif /* !__64BIT_KERNEL */

/*
 * user64 struct compatibility defines.
 * - base these off of __ublock or cross-memory equivalent.
 */
#ifndef __64BIT_KERNEL
#define u_snode         ub_user64.snode
#define u_unode         ub_user64.unode
#else
#define u_snode         ub_user.U_snode
#define u_unode         ub_user.U_unode
#endif /* !__64BIT_KERNEL */


/* compatibility defines */
#ifndef u
#define u		(curthread->t_uaddress)

#define u_save		uthreadp->ut_save
#define u_error		uthreadp->ut_error
#define u_flags		uthreadp->ut_flags
#define u_oldmask	uthreadp->ut_oldmask
#define u_code		uthreadp->ut_code
#define u_sigsp		uthreadp->ut_sigsp
#define u_fstid		uthreadp->ut_fstid
#define u_ioctlrv	uthreadp->ut_ioctlrv
#define u_th_timer	uthreadp->ut_timer
#define u_loginfo	uthreadp->ut_loginfo
#define u_fd		uthreadp->ut_fd

#define u_procp		userp->U_procp
#define u_signal	userp->U_signal
#define u_sigmask	userp->U_sigmask
#define u_sigflags	userp->U_sigflags

#ifndef __64BIT_KERNEL
#define u_adspace	userp->U_adspace
#define u_segst		userp->U_segst
#endif /* !__64BIT_KERNEL */

#define u_vmmflags	userp->U_vmmflags
#define u_auditstatus	userp->U_auditstatus
#define u_map		userp->U_map
#define u_comm		userp->U_comm
#define u_lock		userp->U_lock
#define u_memlock       userp->U_memlock
#define u_cred		userp->U_cred
#define u_uid		userp->U_uid
#define u_ruid		userp->U_ruid
#define u_suid		userp->U_suid
#define u_luid		userp->U_luid
#define u_acctid	userp->U_acctid
#define u_gid		userp->U_gid
#define u_rgid		userp->U_rgid
#define u_sgid		userp->U_sgid
#define u_groups	userp->U_groups
#define u_epriv		userp->U_epriv
#define u_ipriv		userp->U_ipriv
#define u_bpriv		userp->U_bpriv
#define u_mpriv		userp->U_mpriv
#define u_uinfo		userp->U_uinfo
#define u_compatibility	userp->U_compatibility
#define u_semundo	userp->U_semundo
#define u_start		userp->U_start
#define u_ticks		userp->U_ticks
#define u_prof		userp->U_prof
#define u_acflag	userp->U_acflag
#define u_ru		userp->U_ru
#define u_cru		userp->U_cru
#define u_utime         userp->U_utime
#define u_stime		userp->U_stime
#define u_cutime	userp->U_cutime
#define u_cstime	userp->U_cstime
#define u_tsize		userp->U_tsize
#define u_rlimit	userp->U_rlimit
#define u_timer		userp->U_timer
#define u_smax		userp->U_smax
#define u_ssize		userp->U_ssize
#define u_dmax		userp->U_dmax
#define u_minflt	userp->U_minflt
#define u_majflt	userp->U_majflt
#define u_ior		userp->U_ior
#define u_iow		userp->U_iow
#define u_ioch		userp->U_ioch
#define u_ttysid	userp->U_ttysid
#define u_ttyp		userp->U_ttyp
#define u_ttyd		userp->U_ttyd
#define u_ttympx	userp->U_ttympx
#define u_ttys		userp->U_ttys
#define u_ttyid		userp->U_ttyid
#define u_ttyf		userp->U_ttyf
#define u_message	userp->U_message
#define u_sdsize	userp->U_sdsize
#define u_cdir		userp->U_cdir
#define u_cdirpnp	userp->U_cdirpnp
#define u_rdir		userp->U_rdir
#define u_rdir_pathp	userp->U_rdir_pathp
#define u_cmask		userp->U_cmask
#define u_fso_lock	userp->U_fso_lock
#define u_lockflag	userp->U_lockflag
#define u_fdevent	userp->U_fdevent
#define u_irss		userp->U_irss
#define u_rmmap         userp->U_rmmap
#define u_loader	userp->U_loader
#define u_maxofile	userp->U_maxofile
#define u_fdblks(x)	userp->U_fdp(x)
#define u_ufd(x)	userp->U_ufd(x)
#define u_ofile(x)	userp->U_ofile(x)
#define u_pofile(x)	userp->U_pofile(x)
#endif	/* !u */

#define TIMER_LOCK(p, ipri)						\
	{								\
		if (p->p_active == 1)					\
			ipri = i_disable(INTTIMER);			\
		else							\
			ipri = disable_lock(INTTIMER, &U.U_timer_lock);	\
	}

#define TIMER_UNLOCK(p, ipri)						\
	{								\
		if (p->p_active == 1)					\
			i_enable(ipri);					\
		else							\
			unlock_enable(ipri, &U.U_timer_lock);		\
	}

#endif	/* _KERNEL */

#ifdef _KERNEL
#ifdef _KERNSYS

#define IS64U		(U.U_64bit)		/* 0 if a 32-bit process */
#define ISLGPTEXT	(U.U_textl2psize == L2LGPSIZE)	/* 24 if large page text */

#define U_DATAPSIZE(up)  (1L << (up)->U_datal2psize)
#define U_STACKPSIZE(up) (1L << (up)->U_stackl2psize)
#define U_TEXTPSIZE(up)  (1L << (up)->U_textl2psize)
#define U_SHMPSIZE(up)	 (1L << (up)->U_shml2psize)

#else	/* !_KERNSYS */

#define IS64U		(_as_is64())		/* 0 if a 32-bit process */
#if defined( __64BIT_KERNEL) || defined(__FULL_PROTO)
extern int _as_is64(void);
#else
extern int _as_is64();
#endif
#endif /* _KERNSYS */
#endif /* _KERNEL */


/* ioflag values: Read/Write, User/Kernel, Ins/Data */
#define U_WUD 0
#define U_RUD 1
#define U_WKD 2
#define U_RKD 3
#define U_WUI 4
#define U_RUI 5

#define EXCLOSE 01

#define UF_EXCLOSE	0x1
#define UF_MAPPED	0x2
#define UF_FDLOCK	0x4
#define UF_AUD_READ	0x8
#define UF_AUD_WRITE	0x10
#define UF_FSHMAT	0x20
#define UF_CLOSING	0x40
#define UF_ALLOCATED	0x80
#define UF_RESERVED	0x100
#define UF_POLLED	0x200

/* U_vmmflags values 
 * UV_PRESERVED_FLAGS are preserved over fork and exec. However some of the
 * flags need to be cleared at exec time and reset only if certain environment
 * variables are present. These are defined in UV_CLEAR_EXEC_FLAGS.
 */
#ifdef __64BIT_KERNEL
#define UV_PRESERVED_FLAGS (UV_EXTSHM | UV_NOSAS | UV_BIGSTAB |	\
			    UV_RSVD_VSID | UV_STRIPE_SHM | UV_EARLYLRU | \
			    UV_POLY_HEAP_PGSZS | UV_1TBSEGS | UV_MPROT_SHM)
#define UV_CLEAR_EXEC_FLAGS \
 	(UV_EXTSHM | UV_EARLYLRU | UV_RSVD_VSID | UV_STRIPE_SHM | \
	 UV_POLY_HEAP_PGSZS | UV_1TBSEGS | UV_MPROT_SHM)
#else
#define UV_PRESERVED_FLAGS (UV_EXTSHM | UV_NOSAS | UV_BIGSTAB | \
			    UV_EARLYLRU | UV_MPROT_SHM)
#define UV_CLEAR_EXEC_FLAGS (UV_EXTSHM | UV_EARLYLRU | UV_MPROT_SHM)
#endif /* __64BIT_KERNEL */
#define UV_NONE		0x0
#define UV_SHMAT	0x1
#define UV_SHMMAP	0x2
#define UV_MMAP		0x4
#define UV_BIGDATA	0x8
#define UV_RMMAP	0x10
#define UV_EXTSHM_1SEG  0x20
#define UV_EXTSHM_MSEG  0x40
#define UV_EXTSHM       (UV_EXTSHM_1SEG | UV_EXTSHM_MSEG)
#ifdef _KERNSYS
#define UV_NOCOALESCE	0x80
#endif /* _KERNSYS */
#define UV_PINSHM	0x100
#define UV_NOSAS	0x200
#define UV_BIGSTAB	0x400
#define UV_LGPAGE	0x800	/* keep in sync with ml/M4/32/user.table */
#ifdef __64BIT_KERNEL
#define UV_RSVD_VSID	0x1000
#define UV_STRIPE_SHM	0x2000
#endif /* __64BIT_KERNEL */
#define UV_LW_DEBUG     0x4000
#ifdef __64BIT_KERNEL
#define UV_POLY_HEAP_PGSZS 0x8000 /* proc has multiple data heap pg sizes */
#endif /* __64BIT_KERNEL */
#define UV_EARLYLRU	0x10000
#define UV_MPROT_SHM    0x20000
#ifdef __64BIT_KERNEL
#define UV_1TBSEGS	0x100000
#endif /* __64BIT_KERNEL */
#ifdef __cplusplus
}
#endif

#endif /* _H_USER */
