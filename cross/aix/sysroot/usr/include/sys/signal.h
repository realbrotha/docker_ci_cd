/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/signal.h 1.40.8.1                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1985,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)90       1.40.8.1  src/bos/kernel/sys/signal.h, sysproc, bos53Q, q2008_15A5 4/1/08 10:24:06 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: LOW_SIG
 *		SIGADDSET
 *		SIGDELSET
 *		SIGFILLSET
 *		SIGINITSET
 *		SIGISMEMBER
 *		SIGMASK
 *		SIGMASKHI
 *		SIGMASKLO
 *		SIGMASKSET
 *		SIGORSET
 *		SIGANDSET
 *		SIG_PENDING
 *		SIGSETEMPTY
 *		_clronstack
 *		_setnewstyle
 *		_setoldstyle
 *		_setonstack
 *		_testonstack
 *		_teststyle
 *		sigmask
 *		signal
 *		
 *
 *   ORIGINS: 27, 71, 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1985, 1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_SYS_SIGNAL
#define _H_SYS_SIGNAL

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 *      The ANSI standard requires that certain values be in signal.h.
 *	The ANSI standard allows additional signals and pointers to 
 *	undeclarable functions with macro definitions beginning with
 * 	the letters SIG or SIG_ and an upper case letter.
 *      However, it also requires that if _ANSI_C_SOURCE is defined then 
 *      no other function definitions are present
 *
 *      This header includes all the ANSI required entries.  In addition
 *      other entries for the AIX system are included.
 *
 */

#ifdef _ANSI_C_SOURCE	/* { */

#ifdef	_NONSTD_TYPES	/* { */

#ifndef _MBI			/* signals might be ints or voids */
#define _MBI int		/* use -D_MBI=void for void signal handlers */
#endif /* _MBI */
extern _MBI (*signal())();

#else	/* ~_NONSTD_TYPES } { */

#ifdef	_NO_PROTO 
extern void (*signal())();
#else	/* ~_NO_PROTO */
extern void (*signal(int, void (*)(int)))(int);
#endif	/*  _NO_PROTO */

#endif	/* _NONSTD_TYPES } */

#ifdef	_NO_PROTO
extern int raise();
#else /* ~ _NO_PROTO */
extern int raise(int);
#endif /* _NO_PROTO */

typedef volatile int sig_atomic_t; /* accessable as an atomic entity (ANSI) */
/*
 * maximum signal number, 0 is not used
 */
#define SIGMAX64 255
#define SIGMAX32 63

#ifdef __64BIT__
#define SIGMAX SIGMAX64
#else
#define SIGMAX SIGMAX32
#endif
/*
 * valid signal values: all undefined values are reserved for future use 
 * note: POSIX requires a value of 0 to be used as the null signal in kill()
 */
#define	SIGHUP	   1	/* hangup, generated when terminal disconnects */
#define	SIGINT	   2	/* interrupt, generated from terminal special char */
#define	SIGQUIT	   3	/* (*) quit, generated from terminal special char */
#define	SIGILL	   4	/* (*) illegal instruction (not reset when caught)*/
#define	SIGTRAP	   5	/* (*) trace trap (not reset when caught) */
#define	SIGABRT    6	/* (*) abort process */
#define SIGEMT	   7	/* EMT intruction */
#define	SIGFPE	   8	/* (*) floating point exception */
#define	SIGKILL	   9	/* kill (cannot be caught or ignored) */
#define	SIGBUS	  10	/* (*) bus error (specification exception) */
#define	SIGSEGV	  11	/* (*) segmentation violation */
#define	SIGSYS	  12	/* (*) bad argument to system call */
#define	SIGPIPE	  13	/* write on a pipe with no one to read it */
#define	SIGALRM	  14	/* alarm clock timeout */
#define	SIGTERM	  15	/* software termination signal */
#define	SIGURG 	  16	/* (+) urgent contition on I/O channel */
#define	SIGSTOP	  17	/* (@) stop (cannot be caught or ignored) */
#define	SIGTSTP	  18	/* (@) interactive stop */
#define	SIGCONT	  19	/* (!) continue (cannot be caught or ignored) */
#define SIGCHLD   20	/* (+) sent to parent on child stop or exit */
#define SIGTTIN   21	/* (@) background read attempted from control terminal*/
#define SIGTTOU   22	/* (@) background write attempted to control terminal */
#define SIGIO	  23	/* (+) I/O possible, or completed */
#define SIGXCPU	  24	/* cpu time limit exceeded (see setrlimit()) */
#define SIGXFSZ	  25	/* file size limit exceeded (see setrlimit()) */
#define SIGMSG    27	/* input data is in the ring buffer */
#define SIGWINCH  28	/* (+) window size changed */
#define SIGPWR    29	/* (+) power-fail restart */
#define SIGUSR1   30	/* user defined signal 1 */
#define SIGUSR2   31	/* user defined signal 2 */
#define SIGPROF   32	/* profiling time alarm (see setitimer) */
#define SIGDANGER 33	/* system crash imminent; free up some page space */
#define SIGVTALRM 34	/* virtual time alarm (see setitimer) */
#define SIGMIGRATE 35	/* migrate process */
#define SIGPRE	  36	/* programming exception */
#define SIGVIRT   37	/* AIX virtual time alarm */
#define SIGALRM1  38	/* m:n condition variables - RESERVED - DON'T USE */
#define SIGTALRM  38	/* per-thread alarm clock */
#define SIGWAITING 39	/* m:n scheduling - RESERVED - DON'T USE */
#define SIGRECONFIG 58 	/* Reserved for Dynamic Reconfiguration Operations */
#define SIGCPUFAIL 59	/* Predictive De-configuration of Processors - */
			/*	RESERVED - DON'T USE */
#define SIGKAP    60    /* keep alive poll from native keyboard */
#define SIGGRANT  SIGKAP /* monitor mode granted */
#define SIGRETRACT 61   /* monitor mode should be relinguished */
#define SIGSOUND  62    /* sound control has completed */
#define SIGSAK    63	/* secure attention key */
/*
 * additional signal names supplied for compatibility, only 
 */
#define SIGIOINT SIGURG	/* printer to backend error signal */
#define SIGAIO	SIGIO	/* base lan i/o */
#define SIGPTY  SIGIO	/* pty i/o */
#define SIGIOT  SIGABRT /* abort (terminate) process */ 
#define	SIGCLD	SIGCHLD	/* old death of child signal */
#define SIGLOST	SIGIOT	/* old BSD signal ?? */
/* 
 * additional signal required by SPEC1170
 */
#define SIGPOLL SIGIO   /* same as in stropts.h, another I/O event */
/*
 * valid signal action values; other values => pointer to handler function 
 */
#ifndef	_NONSTD_TYPES		
#define	SIG_DFL		(void (*)(int))0
#define	SIG_IGN		(void (*)(int))1
#define SIG_HOLD	(void (*)(int))2	/* not valid as argument 
						   to sigaction or sigvec */
#define SIG_CATCH	(void (*)(int))3	/* not valid as argument 
						   to sigaction or sigvec */
#define SIG_ERR		(void (*)(int))-1
#else	/* _NONSTD_TYPES */
#define	SIG_DFL		(_MBI  (*)())0
#define	SIG_IGN		(_MBI  (*)())1
#define SIG_HOLD	(_MBI  (*)())2	
#define SIG_CATCH	(_MBI  (*)())3
#define SIG_ERR		(_MBI  (*)())-1
#endif	/* _NONSTD_TYPES */

/*
 * values of "how" argument to sigprocmask() call
 */
#define SIG_BLOCK	0
#define SIG_UNBLOCK	1
#define SIG_SETMASK	2

#endif /* _ANSI_C_SOURCE  } */

/*
 *   The following are values that have historically been in signal.h.
 *
 *   They are a part of the POSIX defined signal.h and therefore are
 *   included when _POSIX_SOURCE is defined.
 *
 */

#ifdef _POSIX_SOURCE	/* { */

#ifndef _H_TYPES
#include <sys/types.h>		/* Cannot be in ANSI - name space pollutant */
#endif

#if _XOPEN_SOURCE_EXTENDED==1

#if defined(_ALL_SOURCE) || (_XOPEN_SOURCE>=500) /* { */
/*
 * Symbols for IEEE POSIX 1003.1c Realtime option.
 * NOTE WELL that Realtime option is NOT SUPPORTED.
 * But symbols are required.
 *
 */
union sigval
{
#ifdef __64BIT_KERNEL
	__ptr32 sival_ptr;	/* to keep the same size in 64bit kernel */
#else 
        void *  sival_ptr;	/* address of handler */
#endif /* __64BIT_KERNEL */
        int     sival_int;	/* integer signal value */
};

#else /* !_ALL_SOURCE && !UNIX95 } { */
union __sigval
{
        void *  __sival_ptr;	/* pointer signal value */
        int     __sival_int;	/* integer signal value */
};
#endif /* _ALL_SOURCE || _XOPEN_SOURCE >= 500  } */

/*
 * siginfo_t structure used in waitid() system call
 */
typedef struct {
	int si_signo;		/* signal number */
	int si_errno;		/* if non-zero, errno of this signal */
	int si_code;		/* signal code */
#ifdef __ia64
        int si_imm;
#endif

#ifdef __64BIT_KERNEL /* { */
        /*
         * The process id is always 32-bit in this structure
         * for 32-bit and 64-bit platforms
         */
	pid32_t si_pid;		/* sending process id */

#else /* } { */

	pid_t si_pid;		/* sending process id */
#endif /*_64BIT_KERNEL */

	uid_t si_uid;		/* real user id of sending process */

#ifdef __64BIT_KERNEL /* { */
	/*
 	 * We switch the order of si_addr and si_status in 64 bit mode 
	 * to save space 
 	 */
	__ptr32 si_addr;	/* address of faulting instruction */
	int si_status;		/* exit value or signal */
	int si_band;		/* band event for SIGPOLL */
        union sigval si_value;	/* signal value */
        int __si_flags;
        int __pad[6];		/* rfu */

#else /* } { */

	/*
 	 * We switch the order of si_addr and si_status in 64 bit mode 
	 * to save space 
 	 */
#ifdef __64BIT__
	int si_status;		/* exit value or signal */
	void *si_addr;		/* address of faulting instruction */
#else
	void *si_addr;		/* address of faulting instruction */
	int si_status;		/* exit value or signal */
#endif /* __64BIT__ */

	long si_band;		/* band event for SIGPOLL */

#if defined(_ALL_SOURCE) || (_XOPEN_SOURCE>=500)
        union sigval si_value;	/* signal value */
#else
        union __sigval __si_value;
#endif

        int __si_flags;
#ifdef __64BIT__
        int __pad[3];		/* rfu */
#else
        int __pad[6];		/* rfu */
#endif

#endif /* __64BIT_KERNEL } */
} siginfo_t;

#endif	/* _XOPEN_SOURCE_EXTENDED==1 */


/*
 * sigaction structure used in sigaction() system call 
 */
struct sigaction {
   union {
#ifdef	_NONSTD_TYPES
	_MBI	(*__su_handler)();
#else	/* ~_NONSTD_TYPES */
#ifdef	_NO_PROTO
	void	(*__su_handler)();	/* signal handler, or action value */
#else	/* ~NO_PROTO */
	void	(*__su_handler)(int);	/* signal handler, or action value */
#endif	/* NO_PROTO */
#endif	/* _NONSTD_TYPES */
#if _XOPEN_SOURCE_EXTENDED==1
	void    (*__su_sigaction) (int, siginfo_t *, void *);
#else
	void	(*__pad)();		/* for sizing purposes */
#endif
    } sa_union;
	sigset_t sa_mask;		/* signals to block while in handler */
	int	sa_flags;		/* signal action flags */
};





#define sa_handler sa_union.__su_handler
#if _XOPEN_SOURCE_EXTENDED==1
#define sa_sigaction sa_union.__su_sigaction
#endif



/*
 * valid flag define for sa_flag field of sigaction structure - POSIX
 */
#define SA_NOCLDSTOP	0x00000004	/* do not set SIGCHLD for child stops*/

#endif	/* _POSIX_SOURCE  } */

#if _XOPEN_SOURCE_EXTENDED==1

#include <sys/context.h>

/*
 * sigstack structure used in sigstack() system call 
 */
struct	sigstack {
	void	*ss_sp;			/* signal stack pointer */
	int	ss_onstack;		/* current status */
};

#define	SA_ONSTACK	0x00000001	/* run on special signal stack */
#define SA_RESTART	0x00000008	/* restart system calls on sigs*/
#define SA_RESETHAND    0x00000002      /* signal disposition will be set to
                                         * SIG_DFL on entry to signal handler */
#define SA_SIGINFO      0x00000100      /* pass extra information to signal
                                         * handler upon receipt of signal */
#define SA_NODEFER      0x00000200      /* signal will not automatically be
                                         * blocked on entry to signal handler */
#define SA_NOCLDWAIT    0x00000400      /* zombie will not be created on death
                                         * of child */

#define SS_ONSTACK      0x00000001      /* process is executing on alternate
                                         * signal stack */
#define SS_DISABLE      0x00000002      /* alternate signal stack is disabled */

/*
 * the following are the code macros that are stored in the si_code
 * element of the siginfo_t struct, on a signal-specific basis.
 */

#define SI_USER         0	/* signal sent by another process with kill */
#define SI_UNDEFINED	8	/* siginfo_t contains partial information   */
#define SI_EMPTY	9	/* siginfo_t contains no useful information */
/* SIGBUS */
#define BUS_ADRALN	1
#define BUS_ADRERR	2
#define BUS_OBJERR	3
#define BUS_UEGARD	4
/* SIGCHLD */
#define CLD_EXITED	10
#define CLD_KILLED	11
#define CLD_DUMPED	12
#define CLD_TRAPPED	13
#define CLD_STOPPED	14
#define CLD_CONTINUED	15
/* SIGFPE */
#define FPE_INTDIV	20
#define FPE_INTOVF	21
#define FPE_FLTDIV	22
#define FPE_FLTOVF	23
#define FPE_FLTUND	24
#define FPE_FLTRES	25
#define FPE_FLTINV	26
#define FPE_FLTSUB	27
/* SIGILL */
#define ILL_ILLOPC	30
#define ILL_ILLOPN	31
#define ILL_ILLADR	32
#define ILL_ILLTRP	33
#define ILL_PRVOPC	34
#define ILL_PRVREG	35
#define ILL_COPROC	36
#define ILL_BADSTK	37
/* SIGPOLL */
#define POLL_IN		40
#define POLL_OUT	41
#ifndef POLL_MSG
#define POLL_MSG	-3	/* matches <sys/poll.h> */
#endif
#define POLL_ERR	43
#define POLL_PRI	44
#define POLL_HUP	45
/* SIGSEGV */
#define SEGV_MAPERR	50
#define SEGV_ACCERR	51
#define SEGV_KEYERR	52
/* SIGTRAP */
#define TRAP_BRKPT	60
#define TRAP_TRACE	61
/* GENERAL */
#define SI_QUEUE        71
#define SI_TIMER        72
#define SI_ASYNCIO      73
#define SI_MESGQ        74


/*
 * __si_flags values in siginfo_t structure.
 */
#define SI_WPDABR	1
#define SI_FAST_WATCH	2
#define SI_WP_SYSCALL	3


#if defined(_ALL_SOURCE) || ((_XOPEN_SOURCE != 500) && (_XOPEN_SOURCE != 600))
#ifdef _NO_PROTO
extern int sigmask();
#else /* _NO_PROTO */
extern int sigmask(int);
#endif /* _NO_PROTO */

/*
 * Macro for converting signal number to a mask suitable for
 * sigblock().
 */
#define sigmask(__m)	(1 << ((__m)-1))

#endif  /* (_ALL_SOURCE) || (_XOPEN_SOURCE != 500) */
#endif  /* _XOPEN_SOURCE_EXTENDED */

#ifdef _KERNEL	/* { */

/*
 * kernel declaration for sigval for 64-bit processes.
 */
union sigval64
{
        unsigned long long sival_ptr;      	/* pointer signal value */
        int sival_int;      			/* integer signal value */
};

/* 
 * kernel declaration for sigevent for 64-bit processes.
 * this is based on the unix98 version of the structure.
 */
struct sigevent64 {
        union sigval64      sigev_value;    	   /* signal value */
        int                 sigev_signo;
        int                 sigev_notify;   	   /* notification type */
        unsigned long long  sigev_notify_function; /* notification func */
        unsigned long long  sigev_notify_attributes;
};

/*
 * kernel declaration for siginfo_t for 64-bit processes. 
 */
typedef struct {
        int si_signo;           	/* signal number */
        int si_errno;           	/* if non-zero, errno of this signal */
        int si_code;            	/* signal code */
#ifdef __ia64
	int si_imm;
#endif /* __ia64 */
        pid32_t si_pid;         	/* sending process id */
        uid_t si_uid;           	/* real user id of sending process */
        int si_status;          	/* exit value or signal */
        unsigned long long si_addr; 	/* address of faulting instruction */
        long long si_band;  		/* band event for SIGPOLL */
        union sigval64 si_value;  	/* signal value */
        int __si_flags;
        int __pad[3];			/* rfu */
} siginfo64_t;

#endif /* _KERNEL  } */

#ifdef _KERNSYS

/*
 * Kernel declaration for sender info saved during kill(), sigqueue().
 * Note that si_value must be long enough to contain a union sigval64.
 *
 * This structure defines a element on the p_infoq queue which keeps track
 * of signal information for use by SA_SIGINFO signal handlers.
 * The queue element for this purpose is flagged KSI_STATIC, and remains
 * enqueued for the life of the SA_SGINFO-aware handler action definition.
 * Its si_code will be set to SI_EMPTY rather than it being dequeued.
 *
 * These elements are also used to queue POSIX realtime queued signals.
 * When the signal is delivered, the element is dequeued, and generally
 * xmfree'd as well.
 */
typedef struct ksiginfo {
	struct ksiginfo*   si_next;	/* link pointer */
	long	si_band;		/* band event SIGPOLL */
        pid_t	si_pid;           	/* sending process id (kill, SIGCHLD) */
        uid_t	si_uid;           	/* sending process real user id */
	int	si_status;		/* exit value SIGCHLD */
        short	si_signo;           	/* signal number */
        short	si_code;            	/* signal code (SI_EMPTY, SI_USER...) */
	unsigned long long si_value;	/* real-time signal's "value" */
	int	si_flags;
} ksiginfo_t;

#define KSI_STATIC	1		/* static element for SA_SIGINFO use */
#define KSI_COUNTED	2		/* counts against pv_sigs_queued limit*/
#define KSI_KEEP	4		/* don't xmfree element after dequeue */
#define KSI_ACTIVE	8		/* element is in use */

/* 
 * kernel declaration for sigaction for 32-bit process. 
 */
struct sigaction32 {
    union {
	unsigned int 	__su_handler;  /* addr of user signal handler */
	unsigned int 	__su_sigaction;
    } sa_union;
	sigset32_t	sa_mask;	/* signals to block while in handler */
	int 		sa_flags;	/* signal action flags */
};

/* 
 * kernel declaration for sigaction for 64-bit process. 
 */
struct sigaction64 {
    union {
	unsigned long long __su_handler;  /* addr of user signal handler */
	unsigned long long __su_sigaction;
    } sa_union;
	sigset64_t sa_mask;		/* signal mask */
	int 	sa_flags;		/* signal flags */
};
	
/* 
 * kernel uses a union sigact to cover both 32-bit and 64-bit processes.
 * (see sigaction() service).
 */
union sigact {
	struct sigaction32 a32;		/* 32-bit */
	struct sigaction64 a64;		/* 64-bit */
};

/* 
 * kernel declaration for sigstack for 32-bit process.
 */
struct	sigstack32 {
	unsigned int ss_sp;		/* signal stack pointer */
	int ss_onstack;			/* current status */
};

/* 
 * kernel declaration for sigstack for 64-bit process.
 */
struct	sigstack64 {
	unsigned long long ss_sp;	/* signal stack pointer */
	int ss_onstack;			/* current status */
};

/* 
 * kernel uses a union sigstk to cover both 32-bit and 64-bit processes.
 * (see sigstack() service).
 */
union sigstk {
	struct sigstack32 s32;		/* 32-bit */
	struct sigstack64 s64;		/* 64-bit */
};

/* 
 * kernel uses a union sigaltstk to cover both 32-bit and 64-bit processes.
 * (see sigaltstack() service).
 */
union sigaltstk {
	stack_t   s32;			/* 32-bit */
	stack64_t s64;			/* 64-bit */
};

/*
 * kernel prototypes that differ from libc.a because of 64-bit
 * implementation
 */
#ifdef _NO_PROTO
extern int sigaction();
extern int sigaltstack();
extern int sigstack();
#else /* _NO_PROTO */
extern int sigaction(int, union sigact *, union sigact *);
extern int sigaltstack(const union sigaltstk *, union sigaltstk *);
extern int sigstack(union sigstk *, union sigstk *);
#endif /* _NO_PROTO */

#endif /* _KERNSYS */

#if _XOPEN_SOURCE_EXTENDED==1

#include <sys/m_signal.h>

#if (_XOPEN_SOURCE>=500)
/*
 * sigevent structure, referred to (but not used) in asynchronous i/o.
 *
 * WARNING: The unix98 sigevent is available to user programs, but this
 *	    does not itself guarantee that the kernel supports unix98 aio.
 *
 */
struct sigevent {
	union sigval		sigev_value;
	int			sigev_signo;
	int			sigev_notify;
#ifdef __64BIT_KERNEL
	__ptr32			sigev_notify_function;
	__ptr32 		sigev_notify_attributes;
#else
	void			(*sigev_notify_function)(union sigval);
	pthread_attr_t *	sigev_notify_attributes;
#endif
};

/* Values for sigev_notify */
#define SIGEV_NONE      1
#define SIGEV_SIGNAL    2
#define SIGEV_THREAD    3

/*
 * Define range for POSIX real-time signals.
 * There must be at least RTSIG_MAX == _POSIX_RTSIG_MAX of these,
 * and they must not overlap POSIX required signals like SIGUSR1.
 */
#define SIGRTMIN        50
#define SIGRTMAX        57

#endif /* _XOPEN_SOURCE>=500 */
#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _ALL_SOURCE /* { */
/*
 * Old sigevent structure from aix 4.2.
 */
struct osigevent {
#ifdef __64BIT_KERNEL
	__ptr32		sevt_value;
#else
	void		*sevt_value;
#endif
	signal_t	sevt_signo;
};

/*
 * valid signal action values; other values => pointer to handler function 
 */
#define BADSIG		SIG_ERR

/*
 * valid flags define for sa_flag field of sigaction structure 
 */
#define SA_OLDSTYLE 	SA_RESETHAND	/* old "unreliable" UNIX semantics */
#define SA_NODUMP       0x00000010	/* core file not created for signal */  
#define SA_PARTDUMP     0x00000020	/* create partial core for this signal*/
#define SA_FULLDUMP     0x00000040	/* create a full core with data areas */
#define SA_SIGSETSTYLE  0x00000080	/* new system V sigset type semantics */

/*
 * Information pushed on stack when a signal is delivered.
 * This is used by the kernel to restore state following
 * execution of the signal handler.  It is also made available
 * to the handler to allow it to properly restore state if
 * a non-standard exit is performed.
 */
#define sigcontext __sigcontext

/*
 * flag bits defined for parameter to psig and sendsig; bits indicate
 * what context (where and how much) should be saved on signal delivery
 */       
#define	NO_VOLATILE_REGS	0x0001
#define	USE_SAVE_AREA		0x0002
#if !defined(__64BIT__) && !defined(_KERNSYS_)
/* 
 * macros to manipulate signal sets
 */
#define	SIGMASKLO(__s)	( 1 << ((__s) - 1) )
#define SIGMASKHI(__s)	( 1 << (((__s)-32) - 1) )
#define LOW_SIG(__s)	((__s) <= 32 )
#define SIGMASK(__s)    (1<<(((__s)-1)%32))

#define	SIGFILLSET(__set)	\
{	(__set).losigs = ~0;	\
	(__set).hisigs = ~0;	\
}

#define SIGDELSET(__set,__s)        \
	{*((&(__set).losigs)+(((__s)-1)/32)) &= ~(1<<(((__s)-1)%32));}

#define SIGADDSET(__set,__s)        \
	{*((&(__set).losigs)+(((__s)-1)/32)) |= (1<<(((__s)-1)%32));}

#define SIGSETEMPTY(__set)	\
	(!((__set).losigs) && !((__set).hisigs))

#define SIGISMEMBER(__set,__s) \
	( (*((&(__set).losigs)+(((__s)-1)/32)) >> (((__s)-1)%32) ) & 1 )

/* SIG_PENDING will report inadequate results if _THREADS */
#define SIG_PENDING(__p)						\
	((								\
	  (__p)->p_sig.losigs &						\
		~((__p)->p_sigignore.losigs | (__p)->p_sigmask.losigs)	\
	 ) || (								\
	  (__p)->p_sig.hisigs &						\
		~((__p)->p_sigignore.hisigs | (__p)->p_sigmask.hisigs)	\
	))

#define	SIGINITSET(__set)	\
{	(__set).losigs = 0;	\
	(__set).hisigs = 0;	\
}
#define SIGMASKSET(__dest, __mask) \
{	(__dest).losigs &= ~(__mask).losigs; \
	(__dest).hisigs &= ~(__mask).hisigs; \
}

#define SIGORSET(__dest, __mask) \
{	(__dest).losigs |= (__mask).losigs; \
	(__dest).hisigs |= (__mask).hisigs; \
}

#define SIGANDSET(__dest, __m1, __m2) \
{	(__dest).losigs = (__m1).losigs & (__m2).losigs; \
	(__dest).hisigs = (__m1).hisigs & (__m2).hisigs; \
}
#endif

/*
 * The existing 64 bit signal set is a structure containing
 * 2 32 bit integers.  Signal numbers 1-32 are in the 
 * lower address word and signal number 33-64 are in 
 * the higher address word.   
 *
 *                Big Endian             Little Endian
 * offset	0	4              0      4 
 * signo	32    1  64    33      1     32 33    64 
 * 		-----------------      -----------------
 * 		|	|       |      |       |       |
 * 		-----------------      -----------------
 * 		 losigs   hisigs        losigs  hisigs
 *
 * The 256 bit signal set is an array of 4 64 bit long longs.
 * The signal numbers are repesented as follows:
 *
 *                Big Endian             Little Endian   
 * offset	0	4              0       4
 * signo	64		1      1               64
 *		-----------------      ----------------- 
 *   ss_set[0]	|	|	|      |       |       |
 * 		-----------------      -----------------
 * signo	128		65     65              128
 * 		-----------------      -----------------
 *   ss_set[1]	|	|	|      |       |       |
 * 		-----------------      -----------------
 * signo	192		129    129             192
 * 		-----------------      -----------------
 *   ss_set[2]	|	|	|      |       |       | 
 * 		-----------------      -----------------
 * signo	256		193    193             256
 * 		-----------------      -----------------
 *   ss_set[3]	|	|	|      |       |       | 
 * 		-----------------      -----------------
 */

/* The following macros copy and convert a 64-bit sigset_t 
 * into the first long long of a 256-bit sigset and 
 * vice versa.  The syntax of the macros are:
 *
 *     SIGSETTOLONG(src, dest); 
 *     LLONGTOSIGSET(src, dest);
 *
 * For big endian, the macros swap the high and low
 * words during the copy.  For little endian, there is
 * no need to swap the words and they are simply copied.
 */

#ifdef __ia64

#define SIGSETTOLLONG(__set, __ll)			\
	{						\
		*(int *)&(__ll) = (__set).losigs;	\
		*((int *)&(__ll)+1) = (__set).hisigs;	\
        }

#define LLONGTOSIGSET(__ll, __set)			\
	{						\
		(__set).losigs = *(int *)&(__ll);	\
		(__set).hisigs = *((int *)&(__ll)+1);	\
        }

#else /* __ia64 */

#define SIGSETTOLLONG(__set, __ll)			\
	{						\
		*(int *)&(__ll) = (__set).hisigs;	\
		*((int *)&(__ll)+1) = (__set).losigs;	\
        }

#define LLONGTOSIGSET(__ll, __set)			\
	{						\
		(__set).hisigs = *(int *)&(__ll);	\
		(__set).losigs = *((int *)&(__ll)+1);	\
        }

#endif /* __ia64 */

#if defined(__64BIT__) || defined(_KERNSYS_)

/*
 * defines so 64 bit app/kernel can use existing macro names
 */
#define SIGFILLSET(__set)	SIGFILLSET64(__set)
#define SIGDELSET(__set,__s) 	SIGDELSET64(__set,__s)
#define SIGADDSET(__set,__s) 	SIGADDSET64(__set,__s)
#define SIGSETEMPTY(__set)	SIGSETEMPTY64(__set)
#define SIGISMEMBER(__set,__s)	SIGISMEMBER64(__set,__s)
#define SIG_PENDING(__p)		SIG_PENDING64(__p)
#define SIGINITSET(__set)		SIGINITSET64(__set)
#define SIGMASKSET(__dest,__mask)	SIGMASKSET64(__dest,__mask)
#define SIGORSET(__dest,__mask)		SIGORSET64(__dest,__mask)
#define SIGANDSET(__dest,__m1,__m2)	SIGANDSET64(__dest,__m1,__m2)

#endif
/* 
 * macros to manipulate signal sets
 */

/* XXX These need some work for __64LDT__
 *
#define	SIGMASKLO(__s)	(1UL<<((__s)-1) )
#define SIGMASKHI(__s)	(1UL<<(((__s)-64)- 1) )
#define LOW_SIG(__s)	((__s)<=64)
#define SIGMASK(__s)    (1UL<<(((__s)-1)%64))
*/

#define	SIGFILLSET64(__set)			\
{	*(__set).ss_set = ~(0ULL);		\
	*((__set).ss_set + 1) = ~(0ULL);	\
	*((__set).ss_set + 2) = ~(0ULL);	\
	*((__set).ss_set + 3) = ~(0ULL);	\
}
#define	SIGINITSET64(__set)	\
{	*(__set).ss_set = 0ULL;	\
	*((__set).ss_set + 1) = 0ULL;	\
	*((__set).ss_set + 2) = 0ULL;	\
	*((__set).ss_set + 3) = 0ULL;	\
}

#define SIGDELSET64(__set,__s)        \
	{*((__set).ss_set+(((__s)-1)/64)) &= ~(1ULL<<(((__s)-1)%64));}

#define SIGADDSET64(__set,__s)        \
	{*((__set).ss_set+(((__s)-1)/64)) |= (1ULL<<(((__s)-1)%64));}

#define SIGSETEMPTY64(__set)	\
	(!*(__set).ss_set && !*((__set).ss_set + 1) \
	 && !*((__set).ss_set + 2) && !*((__set).ss_set + 3))

#define SIGISMEMBER64(__set,__s) \
	((*((__set).ss_set+(((__s)-1)/64)) >> (((__s)-1)%64))&1ULL)

/* SIG_PENDING will report inadequate results if _THREADS */
#define SIG_PENDING64(__p)						\
	((								\
	  *(__p)->p_sig &						\
		~(*(__p)->p_sigignore.ss_set |				\
		*(__p)->p_sigmask.ss_set)				\
	 )								\
	 || (								\
	  *((__p)->p_sig + 1) &						\
		~(*((__p)->p_sigignore.ss_set + 1) |			\
		*((__p)->p_sigmask.ss_set + 1)))			\
	 || (								\
	  *((__p)->p_sig + 2) &						\
		~(*((__p)->p_sigignore.ss_set + 2) |			\
		*((__p)->p_sigmask.ss_set + 2)))			\
	 || (								\
	  *((__p)->p_sig + 3) &						\
		~(*((__p)->p_sigignore.ss_set + 3) |			\
		*((__p)->p_sigmask.ss_set + 3)))			\
	 )

#define SIGMASKSET64(__dest, __mask) \
{	*(__dest).ss_set &= ~*(__mask).ss_set; \
	*((__dest).ss_set + 1) &= ~*((__mask).ss_set + 1); \
	*((__dest).ss_set + 2) &= ~*((__mask).ss_set + 2); \
	*((__dest).ss_set + 3) &= ~*((__mask).ss_set + 3); \
}

#define SIGORSET64(__dest, __mask) \
{	*(__dest).ss_set |= *(__mask).ss_set; \
	*((__dest).ss_set + 1) |= *((__mask).ss_set + 1); \
	*((__dest).ss_set + 2) |= *((__mask).ss_set + 2); \
	*((__dest).ss_set + 3) |= *((__mask).ss_set + 3); \
}

#define SIGANDSET64(__dest, __m1, __m2) \
{	*(__dest).ss_set = *(__m1).ss_set & *(__m2).ss_set; \
	*((__dest).ss_set + 1) = *((__m1).ss_set + 1) & *((__m2).ss_set + 1); \
	*((__dest).ss_set + 2) = *((__m1).ss_set + 2) & *((__m2).ss_set + 2); \
	*((__dest).ss_set + 3) = *((__m1).ss_set + 3) & *((__m2).ss_set + 3); \
}
/* macros for manipulating old (small) sigset_t */
#define	SIGMASKLO32(__s)	( 1 << ((__s) - 1) )
#define SIGMASKHI32(__s)	( 1 << (((__s)-32) - 1) )
#define LOW_SIG32(__s)	((__s) <= 32 )
#define SIGMASK32(__s)    (1<<(((__s)-1)%32))

#define	SIGFILLSET32(__set)	\
{	(__set).losigs = ~0;	\
	(__set).hisigs = ~0;	\
}

#define SIGDELSET32(__set,__s)        \
	{*((&(__set).losigs)+(((__s)-1)/32)) &= ~(1<<(((__s)-1)%32));}

#define SIGADDSET32(__set,__s)        \
	{*((&(__set).losigs)+(((__s)-1)/32)) |= (1<<(((__s)-1)%32));}

#define SIGSETEMPTY32(__set)	\
	(!((__set).losigs) && !((__set).hisigs))

#define SIGISMEMBER32(__set,__s) \
	( (*((&(__set).losigs)+(((__s)-1)/32)) >> (((__s)-1)%32) ) & 1 )

/* SIG_PENDING will report inadequate results if _THREADS */
#define SIG_PENDING32(__p)						\
	((								\
	  (__p)->p_sig.losigs &						\
		~((__p)->p_sigignore.losigs | (__p)->p_sigmask.losigs)	\
	 ) || (								\
	  (__p)->p_sig.hisigs &						\
		~((__p)->p_sigignore.hisigs | (__p)->p_sigmask.hisigs)	\
	))

#define	SIGINITSET32(__set)	\
{	(__set).losigs = 0;	\
	(__set).hisigs = 0;	\
}
#define SIGMASKSET32(__dest, __mask) \
{	(__dest).losigs &= ~(__mask).losigs; \
	(__dest).hisigs &= ~(__mask).hisigs; \
}

#define SIGORSET32(__dest, __mask) \
{	(__dest).losigs |= (__mask).losigs; \
	(__dest).hisigs |= (__mask).hisigs; \
}

#define SIGANDSET32(__dest, __m1, __m2) \
{	(__dest).losigs = (__m1).losigs & (__m2).losigs; \
	(__dest).hisigs = (__m1).hisigs & (__m2).hisigs; \
}


/*
 * sigvec structure used in sigvec compatibility interface.
 */
struct	sigvec {

#ifdef __64BIT_KERNEL /* { */
   union {
	__ptr32 sv_handler;	/* signal handler */
        __ptr32 sv_sigaction;
   } sv_union;
	int     sv_mask;        /* signal mask to apply */
	int     sv_flags;

#else /* } { */

   union {
#ifdef	_NONSTD_TYPES
	_MBI	(*sv_handler)();	/* signal handler */
#else	/* ~_NONSTD_TYPES */	
#ifdef	_NO_PROTO
	void    (*sv_handler)();	/* signal handler */
#else	/* ~_NO_PROTO */
	void    (*sv_handler)(int);	/* signal handler */
#endif	/* _NO_PROTO */
#endif	/* _NONSTD_TYPES */
        /* ptr to SysV-style sig hndlr func */
        void    (*sv_sigaction) (int, siginfo_t *, void *);
   } sv_union;
	int     sv_mask;        /* signal mask to apply */
	int     sv_flags;
#endif /* __64BIT_KERNEL } */
};                           
#define	sv_onstack	sv_flags
#define sv_handler sv_union.sv_handler
#define sv_sigaction sv_union.sv_sigaction

/*
 * values in sv_flags are interpreted identically to values in
 * sa_flags for sigaction(), except SV_INTERRUPT has the opposite
 * meaning as SA_RESTART.  The following additional names are
 * names are defined for values in sv_flags to be compatible with
 * old usage of sigvec() 
 */
#define NSIG64		(SIGMAX64+1)
#define NSIG32		(SIGMAX32+1)
#ifdef __64BIT__
#define NSIG		NSIG64
#else
#define NSIG		NSIG32
#endif
#define SIG_STK		SA_ONSTACK	/* bit for using sigstack stack */
#define SIG_STD		SA_OLDSTYLE	/* bit for old style signals */
#define SV_ONSTACK	SA_ONSTACK	/* bit for using sigstack stack */
#define SV_INTERRUPT	SA_RESTART	/* bit for NOT restarting syscalls */

#define _OLDSTYLE 	(SA_OLDSTYLE)	/* bit for old style signals */
#define _ONSTACK  	(SA_ONSTACK)	/* bit for using sigstack stack */
#define _teststyle(__n)   ((__n) & _OLDSTYLE) /* TRUE if Bell style signals. */
#define _testonstack(__n) ((__n) & _ONSTACK)  /* TRUE if on user-sig stack.  */
#define _setoldstyle(__n) ((__n) | _OLDSTYLE)
#define _setnewstyle(__n) ((__n) & ~_OLDSTYLE)
#define _setonstack(__n)  ((__n) | _ONSTACK)
#define _clronstack(__n)  ((__n) & ~_ONSTACK)

#ifdef _THREAD_SAFE
/**********
 for ssignal and gsignal
**********/

#ifdef _NO_PROTO
void (*ssignal_r())();
int gsignal_r();
#else
void (*ssignal_r(int, void (*)(int), void (*[])(int)))(int);
int gsignal_r(int, void (*[])(int));
#endif

#define MAXSIG	16
#define MINSIG	(-4)
#define TOT_USER_SIG (MAXSIG - MINSIG + 1)
#endif /* THREAD_SAFE */

/*
 * function prototypes for signal functions
 */
#ifdef _NO_PROTO
extern int sigblock();
extern int siglocalmask();
extern int sigvec();
#else  /* _NO_PROTO */
extern int sigblock(int);
extern int siglocalmask(int, const sigset_t *);
extern int sigvec(int, struct sigvec *, struct sigvec *);
#endif /* _NO_PROTO */

#ifndef _KERNEL	/* { */
#ifdef _NO_PROTO
extern int siggetmask();
extern int sigsetmask();
#else  /* _NO_PROTO */
extern int siggetmask(void);
extern int sigsetmask(int);
#endif /* _NO_PROTO */
#endif /* _KERNEL  } */

#endif /* _ALL_SOURCE  } */

#ifdef _POSIX_SOURCE

#ifdef _NO_PROTO
extern int kill();
extern int sigprocmask();
extern int sigsuspend();
extern int sigwait();
#ifndef _KERNSYS
extern int sigaction();
#endif /* _KERNSYS */
extern int sigemptyset();
extern int sigfillset();
extern int sigaddset();
extern int sigdelset();
extern int sigismember();
extern int sigpending();

#if _XOPEN_SOURCE_EXTENDED==1
extern void (*bsd_signal())();
extern int killpg();
extern int sighold();
extern int sigignore();
extern int siginterrupt();
extern int sigpause();
extern int sigrelse();
extern void (*sigset())();
#ifndef _KERNSYS
extern int sigaltstack();
#if  (_XOPEN_SOURCE<600) || defined(_ALL_SOURCE)
extern int sigstack();
#endif
#endif /* _KERNSYS */
#endif /* _XOPEN_SOURCE_EXTENDED */

#else /* _NO_PROTO */

extern int kill(pid_t, int);
extern int sigprocmask(int, const sigset_t *__restrict__, sigset_t *__restrict__);
extern int sigsuspend(const sigset_t *);

#if _AIX32_THREADS
/* See comments in stdlib.h on _AIX32_THREADS */
extern int sigwait(sigset_t *);
#else   /*  !_AIX32_THREADS     POSIX 1003.4a Draft 7 prototype */
extern int sigwait(const sigset_t *__restrict__, int *__restrict__);
#endif  /*  !_AIX32_THREADS     POSIX 1003.4a Draft 7 prototype */

#ifndef _KERNSYS
extern int sigaction(int, const struct sigaction *__restrict__, struct sigaction *__restrict__);
#endif /* _KERNSYS */
extern int sigemptyset(sigset_t *);
extern int sigfillset(sigset_t *);
extern int sigaddset(sigset_t *, int);
extern int sigdelset(sigset_t *, int);
extern int sigismember(const sigset_t *, int);
extern int sigpending(sigset_t *);

#if _XOPEN_SOURCE_EXTENDED==1
extern void (*bsd_signal (int, void (*)(int)))(int); 
extern int killpg(pid_t, int);
extern int sighold(int);
extern int sigignore(int);
extern int siginterrupt(int, int);
extern int sigpause(int);
extern int sigrelse(int);
extern void (*sigset(int, void(*)(int)))(int);
#ifndef _KERNSYS
extern int sigaltstack(const stack_t *__restrict__, stack_t *__restrict__);
#if  (_XOPEN_SOURCE<600) || defined(_ALL_SOURCE)
extern int sigstack(struct sigstack *, struct sigstack *);
#endif
#endif /* _KERNSYS */

#if _XOPEN_SOURCE>=500
extern int pthread_kill(pthread_t, int);
extern int pthread_sigmask(int, const sigset_t *, sigset_t *);
extern int sigqueue(pid_t, int, const union sigval);
struct timespec;
extern int sigtimedwait(const sigset_t *__restrict__, siginfo_t *__restrict__, const struct timespec *__restrict__);
extern int sigwaitinfo(const sigset_t *__restrict__, siginfo_t *__restrict__);
#endif /* _XOPEN_SOURCE>=500 */

#endif /* _XOPEN_SOURCE_EXTENDED */
#endif /* _NO_PROTO */
#endif /* _POSIX_SOURCE */

/*
 * Function prototypes for 64bit kernel only
 */
#ifdef _KERNEL
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
extern void	pgsignal(pid_t pid, int signo);
extern void	kpidsig(pid_t pid, int signo, siginfo64_t *);
extern void 	pidsig(pid_t pid, int signo);
extern int	pause(void);
extern int	sig_chk(void);
extern void 	_sigreturn64(ptr64 scptr);
extern int 	ksetcontext_common(ptr64 ucp);

#endif /* (__64BIT_KERNEL || __FULL_PROTO) */
#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _H_SYS_SIGNAL */
