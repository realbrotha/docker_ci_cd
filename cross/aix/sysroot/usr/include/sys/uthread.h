/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53N src/bos/kernel/sys/uthread.h 1.20.6.2                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1993,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)47       1.20.6.2  src/bos/kernel/sys/uthread.h, sysproc, bos53N, n2007_33A4 8/1/07 19:07:54 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27, 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1993, 1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_UTHREAD
#define _H_UTHREAD

/*
 *	The uthread structure is an extension of the user area or u-block.
 *	There is one allocated per thread, including kernel threads.
 *	It is protected to disallow any access to it by user-mode code.
 *
 *	The uthread contains information about the thread that
 *	is local to the thread and never referenced by other threads.
 *
 */

#include <sys/types.h>
#include <sys/mstsave.h>
#include <sys/timer.h>
#include <sys/ucontext.h>
#include <sys/param.h>
#include <sys/resource.h>
#include <sys/xmem.h>

#ifdef __cplusplus
extern "C" {
#endif

struct buf;
struct thrpgioframe;
struct thrpginfox;

/*
 * The ut_error field is a char in 32bit, but an int in the 64bit kernel.
 * This typedef is used inside the kernel to declare a pointer to an
 * error number.
 */
#ifdef __64BIT_KERNEL
typedef int     ut_error_t;
#else
typedef char    ut_error_t;
#endif

#ifdef _KERNSYS
#ifdef __64BIT_KERNEL
/* Structure for lightweight pool data.  Allocated by
 * lw_pool_alloc.
 */
struct lw_uthread {
	char*    ut_att_map;        /* pointer to bitmap of attachments*/
	esid_t   ut_pool_start;     /* first ESID in the pool */
        uint     ut_cursor;         /* index of next ESID in l-wt pool */ 
	uint     ut_att_count;      /* num ESIDs in pool with attaches */
};
#endif
#endif

struct uthread {
#ifndef __64BIT_KERNEL

#ifdef _KERNEL
	struct kmstsave	ut_save; 	/* machine state save area */
	/* Floating point state used to be in the mst, but it's not
	 * saved for interrupt handlers, so there's no need to reserve
	 * space for it on interrupt stacks.
	 */
	double		ut_fpr[NFPRS];	/* floating point registers	*/
#else
	struct mstsave ut_save;
#endif /* _KERNEL */

	/* system call state .. ut_scsave[] must be aligned on 8 byte
	 * boundary. size of struct mstsave must be multiple of 8.
	 */
	uint		ut_msr64;	/* high 32-bits if 64-bit mode */
	uint		ut_msr;		/* saved user msr */
	uint		ut_errnopp64;   /* high 32-bits if 64-bit mode */
	int		**ut_errnopp;	/* address of pointer to errno */
	uint		ut_scsave[8];	/* save area for system call handler */
	char		*ut_kstack;	/* own kernel stack */
	struct auddata	*ut_audsvc;	/* auditing data */
	ut_error_t	ut_error;	/* return error code */
	char		ut_hw_cpu_id_8_15; /* 2nd byte of hw_cpu_id */
	short		ut_flags;	/* uthread flags */

	/* signal management */
	sigset64_t	ut_oldmask;	/* mask from before sigpause */
	int		ut_code;	/* value for si_code from exception */
	uint		ut_sigsp64;	/* high 32-bits if 64-bit mode */
	char		*ut_sigsp;	/* special signal stack */

	/* miscellaneous */
	uint		ut_fstid;	/* file system transaction ID */
	long		ut_ioctlrv;	/* return value for PSE ioctl's */
	void		*ut_selchn;	/* select control block */
	struct trb	*ut_timer[NTIMERS_THREAD]; /* thread timer array */
	struct uthread	*ut_link;	/* uthread blocks free list */
	void 		*ut_loginfo;	/* loginfo pointer */
	void            *ut_fselchn;    /* fast select control block   */
	ushort          ut_selbuc;      /* atomic queue bucket used in
					   select() */
	cpu_t		ut_corecpu;	/* Core dump cpu id */
#define ut_hw_cpu_id_16_31	ut_corecpu

	uint		ut_context64;	/* high 32-bits if 64-bit mode */
	ucontext_t	*ut_context;	/* user context to restore */
        uint            ut_sigssz64;   	/* high 32-bits if 64-bit mode */
        size_t          ut_sigssz;      /* size of alternate signal stack */

	uint		ut_stkb64;	/* high 32-bits if 64-bit mode */
	void		*ut_stkb;	/* current execution stack base */

	void		*ut_jfscr;	/* pointer to jfs specific cruft */
	int		ut_fd;		/* fd # of file operation */
	void *		ut_pgio_contextp;/* thread pgio context */
	long long	ut_chk_context; /* handler context */
	long long       ut_prsiaddr;    /* procfs si_addr */
	unsigned long long ut_prsivalue;/* procfs si_value for queued signal */
	short		ut_prsigno;     /* procfs si_signo */
	short           ut_prsicode;    /* procfs si_code */
	long            ut_scargs[8];   /* procfs syscall arguments */
	short           ut_scnum;       /* procfs syscall number */
	char            ut_prsigdlvr;   /* procfs PCSSIG delivery number */
        char            ut_pad2;
        int             ut_clockread;
	rpn_t		ut_pgio_tail;	/* vmm nfr iotail (D_THRPGIO) */
	struct buf	*ut_pgio_bplist;/* bufs queued on this thread THRPGIO */
	struct thrpginfox* ut_pgio_infop;  /* thrpginfo of PDT */
	uint		ut_pgio_save[3];/* for v_thrpgio_setup() */
        struct trusage64 ut_ru;         /* this thread resource usage value */
                                        /* If size of trusage64 changes,
                                         * padding needs to be adjust
                                         * accoringly. (currently 144 bytes)
                                         */
	struct xmem	ut_controlxm;	/* x-memory desc for control_word_t */
	struct thrpgioframe * ut_pgio_thrfp;

	uint		ut_lstpagex;	/* last async cli page to read ahead */
	uint		ut_hw_fru_id;	/* Processor ID saved (Part 1)     */
	uint64_t	ut_wp_dabr;	/* watchpoint addr */
	uint64_t	ut_wp_value;	/* watched value */
	
#define UT_PADEND	0		/* amount of end padding */

#define UT_VCSIZE       128             /* uthread cache size boundary */
	
#if UT_PADEND
	char            ut_padend[UT_PADEND]; /* pad to UT_VCSIZE boundary */
#endif

#else   /* __64BIT_KERNEL */
        /* Uthread structure in 64bit kernel. The fields have been
         * rearranged to avoid "holes" between fields.
	 */

#ifdef _KERNEL
	struct kmstsave	ut_save; 	/* machine state save area */
	/* Floating point state used to be in the mst, but it's not
	 * saved for interrupt handlers, so there's no need to reserve
	 * space for it on interrupt stacks.
	 */
        double          ut_fpr[NFPRS];  /* floating point registers     */
#else
	/* XXX - to be removed in 64bit kernel...and all ref to it */
	struct mstsave ut_save;
#endif /* _KERNEL */

	/* system call state .. ut_scsave[] must be aligned on 8 byte
	 * boundary. size of struct mstsave must be multiple of 8.
	 */
	ulong		ut_msr;		/* saved user msr */
	int		**ut_errnopp;	/* address of pointer to errno */
	char		*ut_sigsp;	/* special signal stack */
	ucontext_t	*ut_context;	/* user context to restore */
        size_t          ut_sigssz;      /* size of alternate signal stack */
	void		*ut_stkb;	/* current execution stack base */
	long		ut_scsave[8];	/* save area for system call handler */
	ut_error_t	ut_error;	/* return error code */
	int		ut_flags;	/* uthread flags */

	char		*ut_kstack;	/* own kernel stack */
	struct auddata	*ut_audsvc;	/* auditing data */

	/* signal management */
	sigset_t	ut_oldmask;	/* mask from before sigpause */

	/* miscellaneous */
	uint		ut_fstid;	/* file system transaction ID */
	int		ut_ioctlrv;	/* return value for PSE ioctl's */
	void		*ut_selchn;	/* select control block */
	struct trb	*ut_timer[NTIMERS_THREAD]; /* thread timer array */
	struct uthread	*ut_link;	/* uthread blocks free list */
	void 		*ut_loginfo;	/* loginfo pointer */
	void            *ut_fselchn;    /* fast select control block   */
	ushort          ut_selbuc;      /* atomic queue bucket used in
					   select() */
	int		ut_code;	/* value for si_code from exception */

	void		*ut_jfscr;	/* pointer to jfs specific cruft */
	int		ut_fd;		/* fd # of file operation */
	short		ut_prsigno;     /* procfs si_signo */
	short           ut_prsicode;    /* procfs si_code */
	long            ut_prsiaddr;    /* procfs si_addr */
	unsigned long	ut_prsivalue;	/* procfs si_value for queued signal */
	long            ut_scargs[8];   /* procfs syscall arguments */
	short           ut_scnum;       /* procfs syscall number */
	char            ut_prsigdlvr;   /* procfs PCSSIG delivery number */
        char            ut_pad2;
        int             ut_clockread;
	rpn_t		ut_pgio_tail;	/* vmm nfr iotail (D_THRPGIO) */
        long		ut_chk_context; /* handler context */ 
	struct buf	*ut_pgio_bplist;/* bufs queued on thread (THRPGIO) */
	struct thrpginfox* ut_pgio_infop;/* thrpginfoxp of PDT */
        struct trusage64 ut_ru;         /* this thread resource usage value */
                                        /* If size of trusage64 changes,
                                         * padding needs to be adjust
                                         * accoringly. (currently 144 bytes)
                                         */
	struct xmem	ut_controlxm;	/* x-memory desc for control_word_t */

	ulong		ut_pgio_save[3];/* for v_thrpgio_setup() */
	void            *ut_pgio_contextp;
	struct thrpgioframe * ut_pgio_thrfp;

	struct lw_uthread *ut_lw_uthread; /* pointer to lweight pool data */
	uint		ut_lstpagex;	/* last async cli page to read ahead */

#define SLB_SAVE_BUFSIZE (8 + 44*16)
	char 		ut_slb_save[SLB_SAVE_BUFSIZE]; /* a count and 44 slbs */
	cpu_t		ut_corecpu;	/* CPU core dump exception on */

	ulong		ut_amr;		/* user mode storage key accesses */
	uint64_t	ut_wp_dabr;	/* watchpoint addr */
	uint64_t	ut_wp_value;	/* watched value */
	long long       ut_sig_cfar;    /* CFAR Saved by signal processing */
        uint            ut_hw_fru_id;   /* Processor ID saved (Part 1)     */
        uint            ut_hw_cpu_id;   /* Processor ID saved (Part 2)     */

#define UT_PADEND       32              /* amount of end padding */
#define UT_VCSIZE       128             /* uthread cache size boundary */

#if UT_PADEND
	char            ut_padend[UT_PADEND]; /* pad to UT_VCSIZE boundary */
#endif

#endif /* __64BIT_KERNEL */
};

#if 0   /* cache line size checking can be enabled later */
/*
 * Make sure that the thread structure size is cache-friendly.
 * If not, the following structure will cause a severe compilation error.
 */
struct uthreadsizevalidate{
	char		a[sizeof(struct uthread)% UT_VCSIZE ? -1 : 1];
};
#endif


#ifdef _KERNSYS

/* number of full pages the uthread struct takes
 */
#define UT_PAGES ((sizeof(struct uthread)+PAGESIZE-1)/PAGESIZE)

#endif /* _KERNSYS */

#ifdef __64BIT_KERNEL
#define ut_lw_pool_start ut_lw_uthread->ut_pool_start
#define ut_lw_cursor     ut_lw_uthread->ut_cursor
#define ut_lw_att_count  ut_lw_uthread->ut_att_count
#define ut_lw_att_map    ut_lw_uthread->ut_att_map
#endif /* __64BIT_KERNEL */

/*
 * uthread flags, ut_flags
 */

#define UTSTILLUSED	0x0001		/* albeit freed, entry still in use */
#define UTSIGONSTACK	0x0002		/* thread is on signal stack.  This */
					/* value was put into sc_onstack so */
					/* must keep the same value. */
#define UTNOULIMIT	0x0004		/* bypass ulimit check in kernel mode */
#define UTYIELD		0x0008		/* voluntarily relinquishing processor*/
#define UTSCSIG		0x0010		/* system call to sig_slih path taken */
#define UTSIGSUSP       0x0020          /* sigsuspend in effect */
#define UTASSERTSIG     0x0040          /* flag to e_block_thread */
#define UTINSIGHNDLR	0x0080		/* no Fast Watch across sig handlers */
#define UTLSLICING      0x0100          /* time slicing local thread now */
#define UT32BITFSOP     0x0200          /* 32 bit safe device operation */
#define UTCHKCALLED     0x0400          /* Running app. chkpt handler */
#define UTPROCFSVER     0x0800          /* Guarranty that user registers
                                         * saved on kernel stack through
                                         * /proc and SVC index saved 
                                         * in ut_scnum */
#define UTCHKWAKE	0x1000		/* checkpoint-restartable system call */
#define UTLCENABLE      0x2000          /* enable cancelation after ts */
#define UTISIG		0x4000		/* handling internal signal    */
#define UTISIGSC	0x8000		/* handling internal sig with context */
 

#ifdef __cplusplus
}
#endif

#endif /* _H_UTHREAD */
