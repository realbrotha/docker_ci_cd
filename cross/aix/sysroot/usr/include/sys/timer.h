/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/timer.h 1.32                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)83       1.32  src/bos/kernel/sys/timer.h, sysproc, bos530 4/27/04 10:35:53 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: TIMERID_ISBSD
 *              TIMERID_NOTVALID
 *
 *
 *   ORIGINS: 27,83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_TIMER
#define _H_TIMER
/*
 *  TIMER MANAGEMENT DESIGN:
 *
 *  Each process may make use of up to m timers where m is equal to 1 
 *  timer for the alarm() functionality (AT&T and POSIX alarm(), BSD 
 *  ITIMER_REAL) plus 1 Berkeley user virtual timer (BSD ITIMER_VIRTUAL)
 *  plus 1 Berkeley user and system virtual timer (BSD ITIMER_PROF) 
 *  plus n POSIX 1003.4 realtime timer(s) (POSIX TIMEOFDAY).  The 
 *  u-block contains an array of pointers to timers, one for each of 
 *  the m timers a process may have.  The pointer corresponding to each
 *  timer remains NULL until allocation of that timer (via a call to 
 *  gettimerid()) causes the corresponding pointer to be initialized.
 *
 *  Indices into a process's array of timers are hard-coded.  This
 *  means that for all processes, the first element in the process's
 *  timer array, for example, will serve as the timer slot for, say, 
 *  that process's ITIMER_REAL type timer.
 *
 *  The system maintains a system-wide list of active timer requests.
 *  This is an ordered, doubly-linked, null-terminated list of timer 
 *  requests (trb structures) which have been submitted by all 
 *  processes, device drivers, etc. and have not yet expired.  Any
 *  per-process timer which is active will be on this system-wide 
 *  active list until that timer expires.
 *
 *  When a timeout request expires, it is processed on the timer inter-
 *  rupt level.  For this reason, all per-process timers must be pinned.
 *
 *  At each clock interrupt, the clock timeout routine determines if
 *  there are ITIMER_VIRTUAL and/or ITIMER_PROF timers active for the
 *  current process.  If so, those timers are updated appropriately.  
 *  Since this occurs on the timer interrupt level, these trb's must
 *  also be pinned.
 *
 *
 * u.u_timer___________________
 *________>|                   |___>       \
 *	   |  struct trb       |   .        \ per process timers (pinned)
 *	   |  *trb[NTIMERS]    |   .        /
 *	   |___________________|\_____     /
 *				      |
 *				      |
 *				      |
 *   _________________________________|
 *  |
 *  |
 *  |
 *  |       struct trb
 *  |        _____________________
 *  |______>|                     |
 *	    | struct trb          | \
 *	    | *knext              |  \
 *	    |_____________________|   \  threads through the system active trb
 *	    |                     |   /  list (doubly linked, null terminated)
 *	    | struct trb          |  /
 *	    | *kprev              | /
 *	    |_____________________|
 *	    |                     | process which owns the trb (valid for
 *	    | pid_t               | process timer services, not valid for 
 *	    | pid                 | device driver trb's)
 *	    |_____________________|
 *	    |                     |
 *	    | ulong               | state of the trb
 *	    | flags               |
 *	    |_____________________|
 *	    |                     |
 *	    | ulong		  | user's timer id number
 *	    | timerid		  |
 *	    |_____________________|
 *	    |			  |
 *	    | int		  |
 *	    | eventlist		  |
 *	    |_____________________|
 *          |                     |  .it_interval   timestruc_t
 *          |                     |_______________   time between timeouts
 *          | struct itimerstruc_t|                  for priodic timers
 *	    | timeout             |
 *	    |                     |  .it_value      timestruc_t
 *	    |                     |_______________   absolute time value of
 *	    |_____________________|                  next timeout
 *	    |                     |
 *	    |                     |
 *	    | void                |
 *	    | (*func)()           | timeout function to be called
 *	    |_____________________|
 *	    |                     |
 *	    | {ulong,             |
 *	    |  int,		  |
 *	    |  caddr_t}	 	  |
 *	    | func_data           | parameter to the timeout function
 *	    |_____________________|
 *	    |                     |
 *	    | int                 | interrupt priority level on which to
 *	    | ipri                | call timeout function
 *	    |_____________________|
 *	    |                     |
 *	    | void *              | timeout function
 *	    | tof()               |
 *	    |_____________________|
 *	  
 *	  
 */

#include <sys/time.h>
#include <sys/types.h>
#include <sys/processor.h>

#define T_TIMEOUT	0xABABABAB	/* timeout/untimeout trb	*/

/*
 *  Flags for the timer request block (trb)
 */
#define	T_PENDING	0x01		/* timer is on the system list	*/
#define	T_ACTIVE	0x02		/* timer is in use	        */
#define	T_ABSOLUTE	0x04		/* timeout is an absolute value */
#define	T_INCINTERVAL	0x10		/* timer is an incinterval one	*/
#define	T_COMPLETE	0x20		/* timeout occurred and trb has	*/
					/* been taken off active list	*/
#define T_MPSAFE        0x40            /* used from mp safe driver     */
#define T_LOWRES	0x80		/* timer can be rounded to next */
					/* clock tick 			*/

struct	trb  {
	struct trb 	*to_next;	/* for the timeout() routines	*/
	struct trb 	*knext;		/* next timer in kernel chain	*/
	struct trb 	*kprev;		/* previous timer in kern. chain*/
	ulong		id;		/* owner process, dev drvrs = -1*/
	volatile cpu_t  cpunum; 	/* owning processor             */
	unsigned short  flags;          /* operation flags              */
	ulong		timerid;	/* timer identifier		*/
	tid_t		eventlist;	/* anchor for awaited event	*/
	struct itimerstruc_t timeout;	/* timer request		*/
	void		(*func)();	/* completion handler		*/
	union  parmunion  {		/* data for completion handler	*/
		ulong	data;		/* handler unsigned data	*/
		int	sdata;		/* handler signed data		*/
		caddr_t	addr;		/* handler address		*/
	}  t_union;
	int		ipri;		/* int. priority for func()	*/
	void		(*tof)();	/* timeout function		*/
};

#ifndef  _LINUX_SOURCE_COMPAT
#define	func_data	t_union.data
#endif
#define	t_func_data	t_union.data
#define	t_func_sdata	t_union.sdata
#define	t_func_addr	t_union.addr

#define	TIMERID_ISBSD(timerid)						\
	(((timerid) == ITIMER_VIRTUAL) ||				\
	 ((timerid) == ITIMER_VIRT) ||					\
	 ((timerid) == ITIMER_PROF))

#ifdef _KERNEL

#define TIMERID_PROC(timerid)						\
       (((int)(timerid) >= 0) &&                                        \
        ((int)(timerid) < NTIMERS) &&                                   \
        (U.U_timer[timerid] != NULL))

#define TIMERID_THREAD(timerid)                                         \
       (((int)(timerid) >= TIMERID_REAL1) &&                            \
        ((int)(timerid) < TIMERID_REAL1 + NTIMERS_THREAD) &&            \
        (u.u_th_timer[timerid - TIMERID_REAL1] != NULL))

#define	TIMERID_NOTVALID(timerid)					\
	(!(TIMERID_PROC((timerid)) || TIMERID_THREAD((timerid))))

/*
 * Function prototypes for 64bit kernel only
 */
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
extern struct trb *talloc(void);
extern void	tfree(struct trb *);
extern void	tstart(struct trb *);
extern int	tstop(struct trb *);

extern int      delay(int ticks);
extern int	resched(void);
#else
extern struct trb * talloc();
extern void         tstart();
extern int          tstop();
extern void         tfree();
extern int          delay();
#endif /* !(__64BIT_KERNEL || __FULL_PROTO) */

#endif  /* _KERNEL */


/*
 * Structures used for POSIX Realtime timers.
 */

/* 
 * Each process may make use of up to _POSIX_TIMER_MAX POSIX timers.
 * Each created timers is based on one of the POSIX clocks : 
 * CLOCK_REALTIME, CLOCK_MONOTONIC, CLOCK_PROCESS_CPUTIME_ID or 
 * CLOCK_THREAD_CPUTIME_ID.
 *
 * Characteristics of the timers are stored in posix_tmr structures.
 *
 * The proc struct contains an array of pointers to posix_tmr, one for each of
 * the _POSIX_TIMER_MAX timers a process may have. The pointer corresponding
 * to each timer remains NULL until allocation of that timer (via a call to 
 * timer_create()) causes the corresponding pointer to be initialized.
 *
 * Indices into a process's array of timers represent the timer ID returned
 * by timer_create() and then used in the subsequent timer_*() calls.
 *
 * Active timer requests are handle differently depending on their clock.
 *
 * For timers based on realtime and monotonic clocks :
 *     - The trb mechanism is used (see sys/timer.h)
 *     - Timers based on monotonic clock are enqueued as relative 
 *       realtime timers. Thus, the trb mechanism can be used "as is"
 *       to handle them. Setting the realtime clock has no effect on them
 *       since they are relative timers.
 * 
 * For timers based on process or thread cpu-time clocks :
 *     - Structures representing cpu-time clocks are added to proc and thread
 *       structures : struct cputime_clock. They accumulate the cpu ticks 
 *       consumed by the process (or thread) and keep track of their active 
 *       cpu-time timers in an ordered, doubly-linked, null-terminated list 
 *       of posix_tmr.
 *       
 *     - Some additional fields are added to posix_tmr to store data
 *       needed to handle queueing, updates and expirations of active 
 *       cpu-time timers. They are grouped in a structure similar to a 
 *       compressed trb : struct cputime_tmr.
 *     - When a cpu-time timer is armed, its posix_tmr struct is inserted in
 *       the list of active timers of its reference clock.
 *
 *     - At each sys-timer event, the sys_timer() routine :
 *         - Increments the tick value of :
 *             - the cpu-time clock of the current process 
 *             - the cpu-time clock of the current thread
 *         - Determines if there are active cpu-time timers for these clocks.
 *           If so, those timers are updated appropriately.
 *
 * When a timeout request expires, it is processed on the timer interrupt
 * level. For this reason, all posix_tmr structures must be pinned.
 */

/* 
 * Structure used to store data related to active cpu-time timers.
 * (note: for realtime and monotonic timers, a trb is used).
 */
struct cputime_tmr {
	struct posix_tmr   *next;         /* next active timer in chain     */
	struct posix_tmr   *prev;         /* previous active timer in chain */
	int                id;            /* owner                          */
	timer_t            timerid;       /* timer identifier               */
	unsigned short     flags;         /* to mark if timer is absolute   */
	unsigned int       value;         /* expiration tick value          */
	unsigned int       interval;      /* repetitive interval tick value */
	void		   (*func)();	  /* completion handler	            */
	caddr_t            data;          /* data for completion handler    */ 
};

/* 
 * Structure representing POSIX timers.
 */
struct posix_tmr {
	clockid_t tmr_clockid;               /* clock used for the timer    */
	short     tmr_active_overrun;        /* active overrun count        */
	short     tmr_prev_overrun;          /* previous overrun count      */
	int       tmr_notify;                /* requested notification type */
	union {               /* one of:                                    */
		tid_t  tid;   /* . tid of the permanent thread that handles */
		              /*   the user-specified notification          */
                void  *sip;   /* . address of the ksiginfo_t structure used */
		              /*   in signal notification                   */
        } tmr_notifunion;
	union {                   
		struct trb         *trb;     /* timer based on realtime or  */
		                             /* monotonic clock             */
		struct cputime_tmr cpu_tmr;  /* timer based on process or   */
		                             /* thread cpu-time clock       */
	} tmr_union;
};

#define tmr_tid     tmr_notifunion.tid
#define tmr_sip     tmr_notifunion.sip
#define tmr_trb     tmr_union.trb
#define tmr_cpu_tmr tmr_union.cpu_tmr

/* 
 * Structure representing a POSIX cpu-time clock.
 */
struct cputime_clock {
	uint_t             rt_ticks;      /* count the clock execution time */
	                                  /* units = ticks                  */
	struct posix_tmr   *active_tmrs;  /* list of active cpu-time timers */
	                                  /* attached to that cpu-time clock*/
};

#define CPUTIME_GET 0
#define CPUTIME_SET 1
#define CPUTIME_RES 2

/*
 * Macros for clock IDs 
 */

/* Returns type of the clock stored in the lower-order word of clockid_t */
#define CLOCKID_TYPE(_clockid)     ((long long)(_clockid) & 0xFFFFFFFFLL)

/* Returns instance of the clock stored in the high-order word of clockid_t */
#define CLOCKID_INSTANCE(_clockid) ((long long)(_clockid) >> 32LL)

#endif /* _H_TIMER */
