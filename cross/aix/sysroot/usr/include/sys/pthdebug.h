/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/usr/ccs/lib/libpthdebug/pthdebug.h 1.26.1.2             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1998               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)94       1.26.1.2  src/bos/usr/ccs/lib/libpthdebug/pthdebug.h, libpthdebug, bos53J, j2006_23B0 6/1/06 09:52:05 */

/*
 *
 * COMPONENT_NAME: (LIBPTHDEBUG) - pthread debug library
 *
 * FUNCTIONS:
 *
 *
 * ORIGINS: 27
 *
 */
#ifndef _H_PTHDEBUG_
#define _H_PTHDEBUG_

#ifdef __cplusplus
extern "C" {
#endif

#include <sched.h>		/* struct sched_param */
#include <sys/m_param.h>	/* _NGPRS, _NFPRS */

/* This file contains all the exported definitions available for
 * debuggers from the pthread debug library, libpthdebug.a. This
 * library provides mechanisms for examining application data related
 * to the pthread library.
 */

/* The pthread debug library version number.  This is used to maintain
 * binary compatibility.  The initial release of the pthread debug
 * library in AIX 4.3.2, represented by PTHDB_VERSION_1, was a
 * technology only release and binary compatibility with it is not
 * guaranteed.  It is kept in this file for historical perspective
 * only.
 */
#define PTHDB_VERSION_1	0xa1c432
#define PTHDB_VERSION_2 0xa1c433
#define PTHDB_VERSION_3 0xa1c434

/* The user handle is supplied by the debugger and is intended to
 * provide a convenient mapping from a pthread debug library session
 * to any internal debugger data structure associated with that
 * session.  It is guaranteed to be large enough to hold a pointer
 * type for the debugger.
 */
typedef unsigned long pthdb_user_t;

/* The session handle is supplied by the pthread debug library and is
 * intended to provide a convenient mapping from a pthread debug
 * library session to any internal pthread debug library data
 * structure associated with that session.  It is guaranteed to be
 * large enough to hold a pointer type for the debugger.
 */
typedef unsigned long pthdb_session_t;

/* The object handles are supplied by the pthread debug library to
 * represent unique instances of various pthread library
 * objects. Unless otherwise noted the value zero is considered to
 * represent an invalid value for each of these type.
 */
typedef unsigned long long pthdb_pthread_t; /* different from pthread_t */
typedef unsigned long long pthdb_attr_t;
typedef unsigned long long pthdb_mutex_t;
typedef unsigned long long pthdb_spinlock_t;
typedef unsigned long long pthdb_mutexattr_t;
typedef unsigned long long pthdb_cond_t;
typedef unsigned long long pthdb_condattr_t;
typedef unsigned long long pthdb_barrier_t;
typedef unsigned long long pthdb_barrierattr_t;	
typedef unsigned long long pthdb_rwlock_t;
typedef unsigned long long pthdb_rwlockattr_t;
typedef unsigned long long pthdb_once_t;
typedef unsigned long long pthdb_atfork_t;
typedef unsigned long long pthdb_cleanup_t;
typedef unsigned long long pthdb_key_t;
typedef unsigned long long pthdb_resource_t;

/* The invalid valid for the above object handle types. */
#define PTHDB_INVALID_PTHREAD    ((pthdb_pthread_t)0)
#define PTHDB_INVALID_ATTR       ((pthdb_attr_t)0)
#define PTHDB_INVALID_MUTEX      ((pthdb_mutex_t)0)
#define PTHDB_INVALID_SPINLOCK   ((pthdb_spinlock_t)0)
#define PTHDB_INVALID_MUTEXATTR  ((pthdb_mutexattr_t)0)
#define PTHDB_INVALID_COND       ((pthdb_cond_t)0)
#define PTHDB_INVALID_CONDATTR   ((pthdb_condattr_t)0)
#define PTHDB_INVALID_RWLOCK     ((pthdb_rwlock_t)0)
#define PTHDB_INVALID_RWLOCKATTR ((pthdb_rwlockattr_t)0)
#define PTHDB_INVALID_ONCE       ((pthdb_once_t)0)
#define PTHDB_INVALID_ATFORK     ((pthdb_atfork_t)0)
#define PTHDB_INVALID_CLEANUP    ((pthdb_cleanup_t)0)
#define PTHDB_INVALID_KEY        ((pthdb_key_t)-1)
#define PTHDB_INVALID_PTID       ((pthread_t)0)
#define PTHDB_INVALID_RESOURCE   ((pthdb_resource_t)0)
#define PTHDB_INVALID_BARRIER       ((pthdb_barrier_t)0)
#define PTHDB_INVALID_BARRIERATTR   ((pthdb_barrierattr_t)0)	

#ifdef _PTHDB_2
#define pthdb_tid_t int
#else /* _PTHDB_2 */
typedef unsigned long long pthdb_tid_t;
#endif /* _PTHDB_2 */

#ifdef _PTHDB_2
typedef struct pthdb_sigset
{
	unsigned int losigs;
	unsigned int hisigs;
}
pthdb_sigset_t;
#else /* _PTHDB_2 */
typedef struct pthdb_sigset
{
	unsigned long long ss_set[4];
}
pthdb_sigset_t;
#endif /* _PTHDB_2 */

#define PTHDB_INVALID_TID        ((pthdb_tid_t)0)

/* The pthread debug library handles addresses, machine registers and
 * buffer sizes as 64-bit values for both 32-bit and 64-bit
 * processes. If the debugger knows the debuggee is 32-bits then the
 * top half of these quantities will contain garbage and be ignored.
 */
typedef unsigned long long pthdb_addr_t;
typedef unsigned long long pthdb_reg_t;
typedef unsigned long long pthdb_size_t;

/* pthread execution mode */
typedef enum
{
	PEM_NOTSUP,
	PEM_32BIT,
	PEM_64BIT
}
pthdb_exec_mode_t;

/* symbol name/address */
typedef struct pthdb_symbol
{
	char	       *name;
	pthdb_addr_t	addr;
}
pthdb_symbol_t;

/* pthread context */
/* This must be identical to __pthrdscontext in pthread.h */
typedef struct pthdb_context
{
#ifdef __ia64
        size64_t   __psr;               /* Processor Status Register */
        size64_t   __ip;                /* Instruction Pointer */
        size64_t   __iipa;              /* Interruption Instruction Prev Addr */
        size64_t   __isr;               /* Interruption Status register */
        size64_t   __ifa;               /* Interruption Fault Address Register */
        size64_t   __iim;               /* Interruption immediate register */
        size64_t   __ifs;               /* Interruption Function State */
        size64_t   __rsc;               /* Register Stack Control register */
        size64_t   __bsp;               /* BSP */
        size64_t   __bspstore;          /* BSP store pointer for next spill */
        size64_t   __rnat;              /* RNAT register */
        size64_t   __pfs;               /* Previous function state */
        size64_t   __unat;              /* User NAT collection register */
        size64_t   __preds;             /* Predication registers */
        size64_t   __ccv;               /* CmpXchg Value Register */
        size64_t   __lc;                /* loop count */
        size64_t   __ec;                /* epilog count */
        size64_t   __nats;              /* Address Independent NAT Bitmask */
                                        /* bit1 == r1_nat, bit2 == r2_nat,... */
        size64_t   __fpsr;              /* IA64 FP status register */
        size64_t   __gpr[32];           /* static general registers */
        size64_t   __br[8];             /* branch registers */
        size64_t   __pad1;              /* align __fpr on 16 byte offset */
        __float128_t  __fpr[128];       /* Floating Point Registers */
        size64_t   __ia32fcr;           /* IA32 Floating Point Control Reg */
        size64_t   __ia32eflag;         /* IA32 Eflag register */
        size64_t   __ia32csd;           /* IA32 Code/Data segment descriptor */
        size64_t   __ia32ssd;           /* IA32 Stack segment descriptor */
        size64_t   __ia32cflag;         /* IA32 Cflag register */
        size64_t   __ia32fsr;           /* IA32 flt. pt. status register */
        size64_t   __ia32fir;           /* IA32 flt. pt. instruction register */
        size64_t   __ia32fdr;           /* IA32 flt. pt. data register */
        int        __excp_type;         /* exception type */
        char       __fpeu;              /* floating point ever used */
        char       __fplow_saved;       /* Flag if low FPs were saved */
        char       __fphigh_saved;      /* Flag if high FPs were saved */
        char       __pad2;              /* Reserved pad */
        size64_t   __dirty_part_save;   /* 0 or ptr to dirty partition */
        size64_t   __dirty_part_size;   /* 0 or size of dirty partition */
        size64_t   __pad[5];            /* reserved */
#else
	unsigned long long	gpr[_NGPRS]; 	/* general purpose */
	unsigned long long	msr;		/* machine state */
	unsigned long long	iar;		/* instruction address */
	unsigned long long	lr;		/* link */
	unsigned long long	ctr;		/* count */
	unsigned int		cr;		/* condition */
	unsigned int		xer;		/* exception */
	unsigned int		fpscr;		/* float status and control */
	unsigned int		fpscrx;		/* fpscr software extension */
        unsigned long long      except[1];      /* exception address */
	double  		fpr[_NFPRS];	/* floating point */
	char			fpeu;		/* float ever used */
	char			fpinfo;		/* float info */
	uchar			fpscr24_31;	/* fpscr bits 24-31 */
	char			pad;		/* unused */
	unsigned int		mq;		/* multiply quotient */
        int                     excp_type;      /* exception type */
	__vmx_context_t		vmx;		/* vector state */
#endif /* __ia64 */
}
pthdb_context_t;

/* callback prototypes */

typedef int
(*pthdb_symbols_callback_t)(pthdb_user_t user,
			    pthdb_symbol_t *symbols,
			    int count);
typedef int
(*pthdb_data_callback_t)(pthdb_user_t user,
			 void *buf,
			 pthdb_addr_t addr,
			 size_t len);
typedef int
(*pthdb_regs_callback_t)(pthdb_user_t user,
			 pthdb_tid_t tid,
			 unsigned long long flags,
			 pthdb_context_t *context);
typedef int
(*pthdb_alloc_callback_t)(pthdb_user_t user,
			  size_t len,
			  void **bufp);
typedef int
(*pthdb_realloc_callback_t)(pthdb_user_t user,
			    void *buf,
			    size_t len,
			    void **bufp);
typedef int
(*pthdb_dealloc_callback_t)(pthdb_user_t user,
			    void *buf);
typedef int
(*pthdb_print_callback_t)(pthdb_user_t user,
			  char *str);

/* The pthread debug library uses a series of callbacks into the
 * debugger to access information and resources it does not have
 * immediate access to.
 */
typedef struct pthdb_callbacks
{
	/* Get address of symbols. Not necessary if PTHDB_FLAG_SUSPEND
         * is specified.
	 */
        pthdb_symbols_callback_t symbol_addrs;

	/* Read data from process address space. */
        pthdb_data_callback_t    read_data;

	/* Write data to process address space. Not necessary if
	 * PTHDB_FLAG_HOLD is not specified.
	 */
        pthdb_data_callback_t    write_data;

	/* Read pthread context from kernel thread. Not necessary if
	 * debugger performs this operation itself for pthreads which
	 * have kernel threads.
	 */
        pthdb_regs_callback_t    read_regs;

	/* Write pthread context to kernel thread. Not necessary if
	 * debugger performs this operation itself for pthreads which
	 * have kernel threads.
	 */
        pthdb_regs_callback_t    write_regs;

	/* Memory allocation for pthread debug library. */
        pthdb_alloc_callback_t   alloc;
        pthdb_realloc_callback_t realloc;
        pthdb_dealloc_callback_t dealloc;

	/* Error output. This callback is not supported and is present
         * for internal use only.
	 */
        pthdb_print_callback_t   print;
}
pthdb_callbacks_t;

/* pthread scope */
typedef enum
{
	PS_NOTSUP,
	PS_SYSTEM,
	PS_PROCESS
}
pthdb_scope_t;

/* pthread/kernel thread scheduling policy */
typedef enum
{
	SP_NOTSUP,
	SP_OTHER,
	SP_FIFO,
	SP_RR
}
pthdb_schedpolicy_t;

/* pthread state */
typedef enum
{
	PST_NOTSUP,
	PST_IDLE,	/* being created */
	PST_RUN,	/* running */
	PST_SLEEP,	/* awaiting an event */
	PST_READY,	/* runnable */
	PST_TERM	/* awaiting a join/detach */
}
pthdb_state_t;

/* pthread detach state */
typedef enum
{
	PDS_NOTSUP,
	PDS_DETACHED,
	PDS_JOINABLE
}
pthdb_detachstate_t;

/* pthread suspend state */
typedef enum
{
	PSS_NOTSUP,
	PSS_SUSPENDED,
	PSS_UNSUSPENDED
}
pthdb_suspendstate_t;

/* pthread cancel state */
typedef enum
{
	PCS_NOTSUP,
	PCS_DISABLE,
	PCS_ENABLE
}
pthdb_cancelstate_t;

/* pthread cancel type */
typedef enum
{
	PCT_NOTSUP,
	PCT_DEFERRED,
	PCT_ASYNCHRONOUS
}
pthdb_canceltype_t;

/* pthread hold state */
typedef enum
{
	PHS_NOTSUP,
	PHS_HELD,
	PHS_NOTHELD
}
pthdb_holdstate_t;

/* pthread attr inherit scheduling */
typedef enum
{
	PIS_NOTSUP,
	PIS_INHERIT,
	PIS_EXPLICIT
}
pthdb_inheritsched_t;

/* mutex/cond/rwlock/spinlock/barrier process shared */
typedef enum
{
	PSH_NOTSUP,
	PSH_SHARED,
	PSH_PRIVATE
}
pthdb_pshared_t;

/* mutex state */
typedef enum
{
	MS_NOTSUP,
	MS_LOCKED,
	MS_UNLOCKED
}
pthdb_mutex_state_t;

/* mutex type */
typedef enum
{
	MT_NOTSUP,
	MT_NONRECURSIVE_NP,
	MT_RECURSIVE_NP,
	MT_FAST_NP,
	MT_ERRORCHECK,
	MT_RECURSIVE,
	MT_NORMAL
}
pthdb_mutex_type_t;

/* mutex protocol */
typedef enum
{
        MP_DEFAULT,
	MP_NONE,
	MP_PROTECT,
	MP_INHERIT
}
pthdb_protocol_t;

/* spinlock state */
typedef enum
{
	SL_NOTSUP,
	SL_LOCKED,
	SL_UNLOCKED
}
pthdb_spinlock_state_t;

/* rwlock state */
typedef enum
{
	RS_NOTSUP,
	RS_WRITE,
	RS_READ,
	RS_FREE
}
pthdb_rwlock_state_t;

/* once state */
typedef enum
{
	ON_NOTSUP,
	ON_UNINIT,
	ON_DONE
}
pthdb_once_state_t;

/* atfork type */
typedef enum
{
	AF_NOTSUP,
	AF_POSIX,
	AF_NONPORTABLE
}
pthdb_atfork_type_t;

/* resource type */
typedef enum
{
	RSRC_NOTSUP,
	RSRC_COND,
	RSRC_MUTEX,
	RSRC_RWLOCK,
	RSRC_SPINLOCK,
	RSRC_BARRIER	
}
pthdb_resource_type_t;

/* clock type */
typedef enum
{
	CLK_NOTSUP,
	CLK_REALTIME,
	CLK_MONOTONIC
} 
pthdb_clockid_t;

/* resource handle */
typedef union pthdb_resource_handle
{
	pthdb_cond_t   cond;
	pthdb_mutex_t  mutex;
	pthdb_rwlock_t rwlock;
	pthdb_spinlock_t spinlock;
	pthdb_barrier_t  barrier;
}
pthdb_resource_handle_t;

/* All pthread debug library functions return error status according
 * to the following macros.
 */
#define PTHDB_SUCCESS		0	/* no error */
#define PTHDB_NOSYS		1	/* function not implemented */
#define PTHDB_NOTSUP		2	/* function not supported */
#define PTHDB_BAD_VERSION	3	/* invalid library version */
#define PTHDB_BAD_USER		4	/* invalid user handle */
#define PTHDB_BAD_SESSION	5	/* invalid session handle */
#define PTHDB_BAD_MODE		6	/* invalid execution mode */
#define PTHDB_BAD_FLAGS		7	/* invalid session flags */
#define PTHDB_BAD_CALLBACK	8	/* invalid callback */
#define PTHDB_BAD_POINTER	9	/* invalid pointer */
#define PTHDB_BAD_CMD		10	/* invalid list command */
#define PTHDB_BAD_PTHREAD	11	/* invalid pthread handle */
#define PTHDB_BAD_ATTR		12	/* invalid attr handle */
#define PTHDB_BAD_MUTEX		13	/* invalid mutex handle */
#define PTHDB_BAD_MUTEXATTR	14	/* invalid mutexattr handle */
#define PTHDB_BAD_COND		15	/* invalid cond handle */
#define PTHDB_BAD_CONDATTR	16	/* invalid condattr handle */
#define PTHDB_BAD_RWLOCK	17	/* invalid rwlock handle */
#define PTHDB_BAD_RWLOCKATTR	18	/* invalid rwlockattr handle */
#define PTHDB_BAD_KEY		19	/* invalid key */
#define PTHDB_BAD_PTID		20	/* invalid ptid */
#define PTHDB_BAD_TID		21	/* invalid tid */
#define PTHDB_CALLBACK		22	/* callback failed */
#define PTHDB_CONTEXT		23	/* could not get pthread context */
#define PTHDB_HELD		24	/* pthread is held */
#define PTHDB_NOT_HELD		25	/* pthread is not held */
#define PTHDB_MEMORY		26	/* out of memory */
#define PTHDB_NOT_PTHREADED	27	/* pthread library uninitialized */
#define PTHDB_SYMBOL		28	/* pthread symbol not found */
#define PTHDB_NOT_AVAIL		29	/* information not available */
#define PTHDB_INTERNAL		30	/* internal error */
#define PTHDB_BAD_ONCE		31	/* invalid once handle */
#define PTHDB_BAD_ATFORK	32	/* invalid atfork handle */
#define PTHDB_BAD_CLEANUP	33	/* invalid cleanup handle */
#define PTHDB_BAD_SPINLOCK	34	/* invalid spinlock handle */
#define PTHDB_BAD_BARRIER	35	/* invalid barrier handle */
#define PTHDB_BAD_BARRIERATTR	36	/* invalid barrierattr handle */
#define PTHDB_BAD_TLS_REGION	37	/* invalid tls region number */

/* The pthread debug library relies on a version number to ensure
 * binary compatibility. Initialization of a session should always be
 * done through this macro and never through the associated function.
 */
#ifdef _PTHDB_2
#define pthdb_session_init(user,\
			   exec_mode,\
			   flags,\
			   callbacks,\
			   sessionp)\
	pthdb_session_init_(PTHDB_VERSION_2,\
			    user,\
			    exec_mode,\
			    flags,\
			    callbacks,\
			    sessionp)
#else
#define pthdb_session_init(user,\
			   exec_mode,\
			   flags,\
			   callbacks,\
			   sessionp)\
	pthdb_session_init_(PTHDB_VERSION_3,\
			    user,\
			    exec_mode,\
			    flags,\
			    callbacks,\
			    sessionp)
#endif

/* Each pthread debug library session can be customized using the
 * following flags. The PTHDB_FLAG_HOLD and PTHDB_FLAG_SUSPEND flags
 * are mutually exclusive.
 */
#define PTHDB_FLAG_GPRS       0x0000000000000001LL /* only gprs */
#define PTHDB_FLAG_SPRS       0x0000000000000002LL /* only sprs */
#define PTHDB_FLAG_FPRS       0x0000000000000004LL /* only fprs */
#define PTHDB_FLAG_VRS        0x0000000000000008LL /* only vrs  */
#define PTHDB_FLAG_REGS       0x000000000000000FLL /* all registers */
#define PTHDB_FLAG_HOLD       0x0000000000000010LL /* continue/hold/unhold */
#define PTHDB_FLAG_SUSPEND    0x0000000000000020LL /* suspend/continue */

/* The pthread debug library provides various functions to report
 * object handles one at a time from various lists.
 */
#define PTHDB_LIST_FIRST      1 /* Report first object on list. */
#define PTHDB_LIST_NEXT       2 /* Report next object on list. */

/*****************************************************************************/
/* session prototypes                                                        */
/*****************************************************************************/

int
pthdb_session_destroy(pthdb_session_t session);
int
pthdb_session_flags(pthdb_session_t session,
		    unsigned long long *flagsp);
int
pthdb_session_init_(int version,
		    pthdb_user_t user,
		    pthdb_exec_mode_t exec_mode,
		    unsigned long long flags,
		    pthdb_callbacks_t *callbacks,
		    pthdb_session_t *sessionp);
int
pthdb_session_pthreaded(pthdb_user_t user,
			unsigned long long flags,
			pthdb_callbacks_t *callbacks,
			char **namep);
int
pthdb_session_setflags(pthdb_session_t session,
		       unsigned long long flags);
int
pthdb_session_update(pthdb_session_t session);

/*****************************************************************************/
/* global prototypes                                                         */
/*****************************************************************************/

int
pthdb_session_concurrency(pthdb_session_t session,
			  int *concurrencyp);

/*****************************************************************************/
/* pthread prototypes                                                        */
/*****************************************************************************/

int
pthdb_pthread(pthdb_session_t session,
	      pthdb_pthread_t *pthreadp,
	      int cmd);
int
pthdb_pthread_addr(pthdb_session_t session,
		   pthdb_pthread_t pthread,
		   pthdb_addr_t *addrp);
int
pthdb_pthread_arg(pthdb_session_t session,
		  pthdb_pthread_t pthread,
		  pthdb_addr_t *argp);
int
pthdb_pthread_cancelpend(pthdb_session_t session,
			 pthdb_pthread_t pthread,
			 int *cancelpendp);
int
pthdb_pthread_cancelstate(pthdb_session_t session,
			  pthdb_pthread_t pthread,
			  pthdb_cancelstate_t *cancelstatep);
int
pthdb_pthread_canceltype(pthdb_session_t session,
			 pthdb_pthread_t pthread,
			 pthdb_canceltype_t *canceltypep);
int
pthdb_pthread_detachstate(pthdb_session_t session,
			  pthdb_pthread_t pthread,
			  pthdb_detachstate_t *detachstatep);
int
pthdb_pthread_exit(pthdb_session_t session,
		   pthdb_pthread_t pthread,
		   pthdb_addr_t *exitp);
int
pthdb_pthread_func(pthdb_session_t session,
		   pthdb_pthread_t pthread,
		   pthdb_addr_t *funcp);
int
pthdb_pthread_ptid(pthdb_session_t session,
		   pthdb_pthread_t pthread,
		   pthread_t *ptidp);
int
pthdb_pthread_owner_resource(pthdb_session_t session,
			     pthdb_pthread_t pthread,
			     pthdb_resource_t *resourcep,
			     int cmd);
int
pthdb_pthread_schedparam(pthdb_session_t session,
			 pthdb_pthread_t pthread,
			 struct sched_param *schedparamp);
int
pthdb_pthread_schedpolicy(pthdb_session_t session,
			  pthdb_pthread_t pthread,
			  pthdb_schedpolicy_t *schedpolicyp);
int
pthdb_pthread_schedpriority(pthdb_session_t session,
			    pthdb_pthread_t pthread,
			    int *schedpriorityp);
int
pthdb_pthread_scope(pthdb_session_t session,
		    pthdb_pthread_t pthread,
		    pthdb_scope_t *scopep);
int
pthdb_pthread_sigmask(pthdb_session_t session,
		      pthdb_pthread_t pthread,
		      pthdb_sigset_t *sigsetp);
int
pthdb_pthread_sigpend(pthdb_session_t session,
		      pthdb_pthread_t pthread,
		      pthdb_sigset_t *sigsetp);
int
pthdb_pthread_sigwait(pthdb_session_t session,
		      pthdb_pthread_t pthread,
		      pthdb_sigset_t *sigsetp);
int
pthdb_pthread_state(pthdb_session_t session,
		    pthdb_pthread_t pthread,
		    pthdb_state_t *statep);
int
pthdb_pthread_suspendstate(pthdb_session_t session,
			   pthdb_pthread_t pthread,
			   pthdb_suspendstate_t *suspendstatep);
int
pthdb_pthread_tid(pthdb_session_t session,
		  pthdb_pthread_t pthread,
		  pthdb_tid_t *tidp);
int
pthdb_pthread_waiter_resource(pthdb_session_t session,
			      pthdb_pthread_t pthread,
			      pthdb_resource_t *resourcep);

int
pthdb_ptid_pthread(pthdb_session_t session,
		   pthread_t ptid,
		   pthdb_pthread_t *pthreadp);

/*****************************************************************************/
/* pthread context prototypes                                                */
/*****************************************************************************/

int
pthdb_pthread_context(pthdb_session_t session,
		      pthdb_pthread_t pthread,
		      pthdb_context_t *context);
int
pthdb_pthread_setcontext(pthdb_session_t session,
			 pthdb_pthread_t pthread,
			 pthdb_context_t *context);

/*****************************************************************************/
/* pthread signal context prototypes                                         */
/*****************************************************************************/
#define PTHDB_SIGCTX_BASE	((int)-1)

int
pthdb_pthread_sigcontext(pthdb_session_t session,
			 pthdb_pthread_t pthread,
			 int *siglevelp,
			 int *frame_countp,
			 pthdb_context_t *context);

/*****************************************************************************/
/* pthread control prototypes                                                */
/*****************************************************************************/

int
pthdb_session_committed(pthdb_session_t session,
			char **namep);
int
pthdb_session_commit_tid(pthdb_session_t session,
			 pthdb_tid_t *tidp,
			 int cmd);
int
pthdb_session_continue_tid(pthdb_session_t session,
			   pthdb_tid_t *tidp,
			   int cmd);
int
pthdb_session_stop_tid(pthdb_session_t session,
		       pthdb_tid_t tid);
int
pthdb_pthread_holdstate(pthdb_session_t session,
			pthdb_pthread_t pthread,
			pthdb_holdstate_t *holdstatep);
int
pthdb_pthread_hold(pthdb_session_t session,
		   pthdb_pthread_t pthread);
int
pthdb_pthread_unhold(pthdb_session_t session,
		     pthdb_pthread_t pthread);

/*****************************************************************************/
/* kernel thread prototypes                                                  */
/*****************************************************************************/

int
pthdb_tid_pthread(pthdb_session_t session,
		  pthdb_tid_t tid,
		  pthdb_pthread_t *pthreadp);

/*****************************************************************************/
/* attr prototypes                                                           */
/*****************************************************************************/

int
pthdb_attr(pthdb_session_t session,
	   pthdb_attr_t *attrp,
	   int cmd);
int
pthdb_attr_addr(pthdb_session_t session,
		pthdb_attr_t attr,
		pthdb_addr_t *addrp);
int
pthdb_attr_detachstate(pthdb_session_t session,
		       pthdb_attr_t attr,
		       pthdb_detachstate_t *detachstatep);
int
pthdb_attr_guardsize(pthdb_session_t session,
		     pthdb_attr_t attr,
		     pthdb_size_t *guardsizep);
int
pthdb_attr_inheritsched(pthdb_session_t session,
			pthdb_attr_t attr,
			pthdb_inheritsched_t *inheritschedp);
int
pthdb_attr_schedparam(pthdb_session_t session,
		      pthdb_attr_t attr,
		      struct sched_param *schedparamp);
int
pthdb_attr_schedpolicy(pthdb_session_t session,
		       pthdb_attr_t attr,
		       pthdb_schedpolicy_t *schedpolicyp);
int
pthdb_attr_schedpriority(pthdb_session_t session,
			 pthdb_attr_t attr,
			 int *schedpriorityp);
int
pthdb_attr_scope(pthdb_session_t session,
		 pthdb_attr_t attr,
		 pthdb_scope_t *scopep);
int
pthdb_attr_stackaddr(pthdb_session_t session,
		     pthdb_attr_t attr,
		     pthdb_addr_t *stackaddrp);
int
pthdb_attr_stacksize(pthdb_session_t session,
		     pthdb_attr_t attr,
		     pthdb_size_t *stacksizep);
int
pthdb_attr_suspendstate(pthdb_session_t session,
			pthdb_attr_t attr,
			pthdb_suspendstate_t *suspendstatep);

/*****************************************************************************/
/* mutex prototypes                                                          */
/*****************************************************************************/

int
pthdb_mutex(pthdb_session_t session,
	    pthdb_mutex_t *mutexp,
	    int cmd);
int
pthdb_mutex_addr(pthdb_session_t session,
		 pthdb_mutex_t mutex,
		 pthdb_addr_t *addrp);
int
pthdb_mutex_lock_count(pthdb_session_t session,
		       pthdb_mutex_t mutex,
		       int *lock_countp);
int
pthdb_mutex_owner(pthdb_session_t session,
		  pthdb_mutex_t mutex,
		  pthdb_pthread_t *ownerp);
int
pthdb_mutex_pshared(pthdb_session_t session,
		    pthdb_mutex_t mutex,
		    pthdb_pshared_t *psharedp);
int
pthdb_mutex_prioceiling(pthdb_session_t session,
			pthdb_mutex_t mutex,
			int *prioceilingp);
int
pthdb_mutex_protocol(pthdb_session_t session,
		     pthdb_mutex_t mutex,
		     pthdb_protocol_t *protocolp);
int
pthdb_mutex_state(pthdb_session_t session,
		  pthdb_mutex_t mutex,
		  pthdb_mutex_state_t *statep);
int
pthdb_mutex_type(pthdb_session_t session,
		 pthdb_mutex_t mutex,
		 pthdb_mutex_type_t *typep);
int
pthdb_mutex_waiter(pthdb_session_t session,
		   pthdb_mutex_t mutex,
		   pthdb_pthread_t *waiterp,
		   int cmd);

/*****************************************************************************/
/* spinlock prototypes                                                          */
/*****************************************************************************/

int
pthdb_spinlock(pthdb_session_t session,
	       pthdb_spinlock_t *spinlockp,
	       int cmd);
int
pthdb_spinlock_addr(pthdb_session_t session,
		    pthdb_spinlock_t spinlock,
		    pthdb_addr_t *addrp);
int
pthdb_spinlock_owner(pthdb_session_t session,
		     pthdb_spinlock_t spinlock,
		     pthdb_pthread_t *ownerp);
int
pthdb_spinlock_pshared(pthdb_session_t session,
		       pthdb_spinlock_t spinlock,
		       pthdb_pshared_t *psharedp);
int
pthdb_spinlock_state(pthdb_session_t session,
		     pthdb_spinlock_t spinlock,
		     pthdb_spinlock_state_t *statep);

/*****************************************************************************/
/* mutexattr prototypes                                                      */
/*****************************************************************************/

int
pthdb_mutexattr(pthdb_session_t session,
		pthdb_mutexattr_t *mutexattrp,
		int cmd);
int
pthdb_mutexattr_addr(pthdb_session_t session,
		     pthdb_mutexattr_t mutexattr,
		     pthdb_addr_t *addrp);
int
pthdb_mutexattr_prioceiling(pthdb_session_t session,
			    pthdb_mutexattr_t mutexattr,
			    int *prioceilingp);
int
pthdb_mutexattr_protocol(pthdb_session_t session,
			 pthdb_mutexattr_t mutexattr,
			 pthdb_protocol_t *protocolp);
int
pthdb_mutexattr_pshared(pthdb_session_t session,
			pthdb_mutexattr_t mutexattr,
			pthdb_pshared_t *psharedp);
int
pthdb_mutexattr_type(pthdb_session_t session,
		     pthdb_mutexattr_t mutexattr,
		     pthdb_mutex_type_t *typep);

/*****************************************************************************/
/* cond prototypes                                                           */
/*****************************************************************************/

int
pthdb_cond(pthdb_session_t session,
	   pthdb_cond_t *condp,
	   int cmd);
int
pthdb_cond_addr(pthdb_session_t session,
		pthdb_cond_t cond,
		pthdb_addr_t *addrp);
int
pthdb_cond_mutex(pthdb_session_t session,
		 pthdb_cond_t cond,
		 pthdb_mutex_t *mutexp);
int
pthdb_cond_pshared(pthdb_session_t session,
		   pthdb_cond_t cond,
		   pthdb_pshared_t *psharedp);
int
pthdb_cond_waiter(pthdb_session_t session,
		  pthdb_cond_t cond,
		  pthdb_pthread_t *waiterp,
		  int cmd);
int
pthdb_cond_clock(pthdb_session_t session,
		 pthdb_cond_t cond,
		 pthdb_clockid_t *clockp);

/*****************************************************************************/
/* condattr prototypes                                                       */
/*****************************************************************************/

int
pthdb_condattr(pthdb_session_t session,
	       pthdb_condattr_t *condattrp,
	       int cmd);
int
pthdb_condattr_addr(pthdb_session_t session,
		    pthdb_condattr_t condattr,
		    pthdb_addr_t *addrp);
int
pthdb_condattr_pshared(pthdb_session_t session,
		       pthdb_condattr_t condattr,
		       pthdb_pshared_t *psharedp);

int
pthdb_condattr_clock(pthdb_session_t session,
		     pthdb_condattr_t condattr,
		     pthdb_clockid_t *clockp);

/*****************************************************************************/
/* barrier prototypes                                                           */
/*****************************************************************************/

int
pthdb_barrier(pthdb_session_t session,
	   pthdb_barrier_t *barrierp,
	   int cmd);
int
pthdb_barrier_addr(pthdb_session_t session,
		pthdb_barrier_t barrier,
		pthdb_addr_t *addrp);
int
pthdb_barrier_mutex(pthdb_session_t session,
		 pthdb_barrier_t barrier,
		 pthdb_mutex_t *mutexp);
int
pthdb_barrier_pshared(pthdb_session_t session,
		   pthdb_barrier_t barrier,
		   pthdb_pshared_t *psharedp);
int
pthdb_barrier_waiter(pthdb_session_t session,
		  pthdb_barrier_t barrier,
		  pthdb_pthread_t *waiterp,
		  int cmd);

/*****************************************************************************/
/* barrierattr prototypes                                                       */
/*****************************************************************************/

int
pthdb_barrierattr(pthdb_session_t session,
	       pthdb_barrierattr_t *barrierattrp,
	       int cmd);
int
pthdb_barrierattr_addr(pthdb_session_t session,
		    pthdb_barrierattr_t barrierattr,
		    pthdb_addr_t *addrp);
int
pthdb_barrierattr_pshared(pthdb_session_t session,
		       pthdb_barrierattr_t barrierattr,
		       pthdb_pshared_t *psharedp);

/*****************************************************************************/
/* rwlock prototypes                                                         */
/*****************************************************************************/

int
pthdb_rwlock(pthdb_session_t session,
	     pthdb_rwlock_t *rwlockp,
	     int cmd);
int
pthdb_rwlock_addr(pthdb_session_t session,
		  pthdb_rwlock_t rwlock,
		  pthdb_addr_t *addrp);
int
pthdb_rwlock_lock_count(pthdb_session_t session,
			pthdb_rwlock_t rwlock,
			int *lock_countp);
int
pthdb_rwlock_owner(pthdb_session_t session,
		   pthdb_rwlock_t rwlock,
		   pthdb_pthread_t *ownerp,
		   int cmd);
int
pthdb_rwlock_pshared(pthdb_session_t session,
		     pthdb_rwlock_t rwlock,
		     pthdb_pshared_t *psharedp);
int
pthdb_rwlock_read_waiter(pthdb_session_t session,
			 pthdb_rwlock_t rwlock,
			 pthdb_pthread_t *waiterp,
			 int cmd);
int
pthdb_rwlock_state(pthdb_session_t session,
		   pthdb_rwlock_t rwlock,
		   pthdb_rwlock_state_t *statep);
int
pthdb_rwlock_write_waiter(pthdb_session_t session,
			  pthdb_rwlock_t rwlock,
			  pthdb_pthread_t *waiterp,
			  int cmd);

/*****************************************************************************/
/* rwlockattr prototypes                                                     */
/*****************************************************************************/

int
pthdb_rwlockattr(pthdb_session_t session,
		 pthdb_rwlockattr_t *rwlockattrp,
		 int cmd);
int
pthdb_rwlockattr_addr(pthdb_session_t session,
		      pthdb_rwlockattr_t rwlockattr,
		      pthdb_addr_t *addrp);
int
pthdb_rwlockattr_pshared(pthdb_session_t session,
			 pthdb_rwlockattr_t rwlockattr,
			 pthdb_pshared_t *psharedp);

/*****************************************************************************/
/* once prototypes                                                           */
/*****************************************************************************/

int
pthdb_once(pthdb_session_t session,
	   pthdb_once_t *oncep,
	   int cmd);
int
pthdb_once_addr(pthdb_session_t session,
		pthdb_once_t once,
		pthdb_addr_t *addrp);
int
pthdb_once_state(pthdb_session_t session,
		 pthdb_once_t once,
		 pthdb_once_state_t *statep);
int
pthdb_once_func(pthdb_session_t session,
		pthdb_once_t once,
		pthdb_addr_t *funcp);

/*****************************************************************************/
/* atfork prototypes                                                         */
/*****************************************************************************/

int
pthdb_atfork(pthdb_session_t session,
	     pthdb_atfork_t *atforkp,
	     int cmd);
int
pthdb_atfork_arg(pthdb_session_t session,
	       pthdb_atfork_t atfork,
	       pthdb_addr_t *argp);
int
pthdb_atfork_child(pthdb_session_t session,
		 pthdb_atfork_t atfork,
		 pthdb_addr_t *funcp);
int
pthdb_atfork_type(pthdb_session_t session,
		  pthdb_atfork_t atfork,
		  pthdb_atfork_type_t *typep);
int
pthdb_atfork_parent(pthdb_session_t session,
		  pthdb_atfork_t atfork,
		  pthdb_addr_t *funcp);
int
pthdb_atfork_prepare(pthdb_session_t session,
		   pthdb_atfork_t atfork,
		   pthdb_addr_t *funcp);

/*****************************************************************************/
/* cleanup prototypes                                                        */
/*****************************************************************************/

int
pthdb_cleanup(pthdb_session_t session,
	      pthdb_pthread_t pthread,
	      pthdb_cleanup_t *cleanupp,
	      int cmd);
int
pthdb_cleanup_func(pthdb_session_t session,
		   pthdb_pthread_t pthread,
		   pthdb_cleanup_t cleanup,
		   pthdb_addr_t *funcp);

int
pthdb_cleanup_arg(pthdb_session_t session,
		  pthdb_pthread_t pthread,
		  pthdb_cleanup_t cleanup,
		  pthdb_addr_t *argp);

/*****************************************************************************/
/* pthread specific data key prototypes                                      */
/*****************************************************************************/

int
pthdb_key(pthdb_session_t session,
	  pthdb_key_t *keyp,
	  int cmd);
int
pthdb_pthread_key(pthdb_session_t session,
		  pthdb_pthread_t pthread,
		  pthdb_key_t *keyp,
		  int cmd);
int
pthdb_pthread_specific(pthdb_session_t session,
		       pthdb_pthread_t pthread,
		       pthdb_key_t key,
		       pthdb_addr_t *specificp);

/*****************************************************************************/
/* resource prototypes						             */
/*****************************************************************************/

int
pthdb_resource_handle(pthdb_session_t session, 
		      pthdb_resource_t resource, 
		      pthdb_resource_handle_t *handlep);

int
pthdb_resource_type(pthdb_session_t session, 
		    pthdb_resource_t resource, 
		    pthdb_resource_type_t *typep);

/*****************************************************************************/
/* thread-local storage prototypes				             */
/*****************************************************************************/

int
pthdb_pthread_tls_region(pthdb_session_t session,
			 pthdb_pthread_t pthread,
			 int region_num,
			 pthdb_addr_t *region_addrp);

#ifdef __cplusplus
}
#endif

#endif /* _H_PTHDEBUG_ */
