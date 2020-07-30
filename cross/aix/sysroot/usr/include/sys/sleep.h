/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/sys/sleep.h 1.11.8.1                             */
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
/* @(#)44       1.11.8.1  src/bos/kernel/sys/sleep.h, sysproc, bos53H, h2006_13C6 3/17/06 08:55:14 */
#ifndef _H_SLEEP
#define _H_SLEEP

/*
 * COMPONENT_NAME: SYSPROC 
 *
 * ORIGINS: 3, 27, 83
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#include <sys/types.h>
#include <sys/lock_def.h>

#define	EVENT_NULL	(-1L)		/* null list of subscribers */

#define EVENT_NDELAY	(0ul)		/* wait_mask value to not wait */

/*
 * WARNING: The rightmost 8 bits of a 32-bit wait mask are reserved for the
 * kernel.  In the 64-bit kernel, the leftmost 32 bits of the wait mask are
 * also reserved for the kernel.  Device drivers should only use bits taken
 * from the 24 bits above EVENT_KERNEL.
 */
#define EVENT_KIPC      (0x00000001ul)    /* event bit for thread post/wait */
#define EVENT_THRPGIO   (0x00000002ul) 	  /* thread level pg fault handling */
#define EVENT_SHARED    (0x00000004ul)    /* event bit for shared event */
#define EVENT_QUEUE     (0x00000008ul)    /* event bit for queued event */
#define EVENT_SYNC	(0x00000010ul)	/* event bit for synchronous event */
#define EVENT_CHILD	(0x00000020ul)	/* event bit for child death */
#define EVENT_THREAD    (0x00000040ul)    /* event bit for thread activation */
#define EVENT_RESTART   (0x00000080ul)    /* event bit for restart waiters */
#define EVENT_KERNEL    (0x000000FFul)    /* event bit for kernel event */

	/* e_sleep flag values: */
#define	EVENT_SHORT	(0ul)		/* short wait, inhibit signals */
#define	EVENT_SIGWAKE	(2ul)		/* wake on signal */
#define	EVENT_SIGRET	(4ul)		/* return on signal */

	/* return codes: */
#define	EVENT_SUCC	(1)		/* success, waitq */
#define	EVENT_SIG	(0)		/* process signalled, e_sleep & waitq */

	/* e_wakeupx option values */
#define E_WKX_NO_PREEMPT	(0)	/* do not preempt calling process */
#define E_WKX_PREEMPT		(1)	/* preempt calling process */
#define E_WKX_PREEMPT_MASK	0xF	/* preempt flag mask */
#define E_WKX_FIFO		0x10	/* wake up thread in FIFO manner*/

	/* flags for e_thread_sleep */
#define INTERRUPTIBLE		(1ul)	/* sleep is interruptible */
#define LOCK_HANDLER		(2ul)	/* lock used by interrupt handlers */
#define LOCK_READ		(4ul)   /* complex lock read mode specified */
#define LOCK_SIMPLE		(8ul)   /* simple lock specified */
#define LOCK_WRITE		(16ul)  /* complex lock write mode specified */

	/* flags for wakeup_lock */
#define WAKEUP_LOCK_SIMPLE	(1)	/* wakeup for simple locks */
#define WAKEUP_LOCK_ALL		(2)	/* wakeup all waiters */
#define WAKEUP_LOCK_WRITER_OR_READERS (3)  /* wakeup one writer or all readers */
#define WAKEUP_LOCK_READERS     (4)    /* wakeup all readers or nobody */
#define WAKEUP_LOCK_UPGRADER    (5)    /* wakeup the upgrader */

	/* return values from e_thread_block */
#define THREAD_AWAKENED		(1)	/* normal wakeup value */
#define THREAD_TIMED_OUT	(2)	/* sleep timed out */
#define THREAD_INTERRUPTED	(4)	/* sleep interrupted by signal */
#define THREAD_OTHER		(4096)	/* Beginning of subsystem values */


#ifdef _KERNEL
#ifdef _AIXV3_POSTWAIT

/*
 * DO NOT USE THE FOLLOWING MACROS.  They are likely to disappear in
 * the near future.  They are included so that V4 kernel extensions
 * that have not upgraded their code correctly to support multiple
 * threads will continue to work for mono-threaded processes.  When 
 * the last of these drivers has been updated, these macros will 
 * disappear.  The use of these macros can result in hung processes 
 * or a hung system.
 */
#define e_wait(x,y,z)   et_wait((x),(y),(z))
#define e_post(x,y)     et_post((x),getptid(y))
#endif
#endif

/*
 * Entry points for process execution control
 */

#ifndef __FULL_PROTO

int sleepx();                           /* wait for events to occur */
void wakeup();                          /* wake processes waiting on chan */
unsigned long et_wait();                /* wait for events to occur */
int e_sleep();                          /* add process to event list */
int e_sleepl();                         /* add proc to eventlist & lock */
void et_post();                         /* notify thread of events */
int et_post_rc();                       /* notify thread of events */
void e_wakeup();			/* wakeup subscribers */ 
void e_wakeupx();			/* wakeup subscribers preserve runrun */
void e_wakeup_w_sig();			/* wakeup subscribers with signal */

int e_sleep_thread();			/* block the current thread with lock */
void e_assert_wait();			/* assert that thrd is about to sleep */
void e_assert_wait_userlock();		/* assert that thrd is about to sleep */
void e_clear_wait();			/* clear wait condition */
int e_block_thread();			/* block the current thread */
void e_wakeup_one();			/* wakeup the highest priority sleeper*/
void e_wakeup_some();			/* wakeup n highest priority sleepers */
void e_wakeup_w_result();		/* wakeup threads with result */
void e_interrupt_thread();              /* wakeup specified thread */
char pse_wakeup ();                     /* Get the thread state - used by pse */

#else  /* __FULL_PROTO */

typedef int32long64_t tchan_t;
typedef int32long64_t flags_t;

int sleepx(                             /* wait for events to occur */
        tchan_t  chan,                  /* wait channel             */
        int     pri,                    /* priority                 */
        flags_t flags);                 /* signal control flags     */

void wakeup(                            /* wake processes waiting on chan */
        tchan_t chan);                  /* channel whose processes will wakeup*/

ulong et_wait(                          /* wait for events to occur */
        ulong   wait_mask,              /* mask of events to await  */
        ulong   clear_mask,             /* mask of events to clear  */
        flags_t flags);                 /* wait option flags        */

int e_sleep(                            /* add process to event list */
        tid_t   *event_list,            /* list of subscribers       */
        flags_t flags);                 /* wait option flags         */

int e_sleepl(                           /* add proc to eventlist & lock */
        lock_t  *lock_word,             /* caller's lock word           */
        tid_t   *event_list,            /* list of subscribers          */
        flags_t flags);                 /* wait option flags            */

void et_post(                           /* notify thread of events     */
        ulong   events,                 /* mask of events to be posted */
        tid_t   tid);                   /* thread to be posted         */

struct pvthread;
struct run_queue;
int et_post_rc(                         /* notify thread of events     */
        ulong   events,                 /* mask of events to be posted */
        tid_t   tid,			/* thread to be posted         */
	struct pvthread *tv,		/* thread's slot address       */
	struct run_queue *locked_rq);	/* address of locked run queue */

void e_wakeup(   			/* wakeup subscribers  */ 
  	tid_t	*event_list);		/* list of subscribers */

void e_wakeupx(   			/* wakeup subscribers  */ 
  	tid_t	*event_list,		/* list of subscribers */
	int	option);		/* option to control preemption */

void e_wakeup_w_sig(   			/* wakeup subscribers with signal */ 
  	tid_t	*event_list,		/* list of subscribers */
	int	signo);		        /* signal to be posted */

int e_sleep_thread(			/* block the current thread with lock */
	tid_t 	*event_list,		/* list of subscribers */
	void 	*lockp,			/* lock word */
	flags_t	flags);			/* flags */

void e_assert_wait(			/* register for the wait and continue */
	tid_t 	*event_list,		/* list of subscribers */
	boolean_t interruptible);	/* sleep interruptible by signals */

void e_assert_wait_userlock(		/* register for the wait and continue */
	tid_t 	*event_list);		/* list of subscribers */

void e_clear_wait(			/* clear wait condition */
	tid_t	tid,			/* the target thread */
	int 	result);		/* the wakeup result */

int e_block_thread(void);		/* block the current thread */

void e_wakeup_one(			/* wakeup the highest pri sleeper */
  	tid_t	*event_list);		/* list of subscribers */

void e_wakeup_some(			/* wakeup n highest priority sleepers */
	tid_t	*event_list,		/* list of subscribers */
	int	n);			/* number to wake up */

void e_wakeup_w_result(			/* wakeup threads with result */
	tid_t 	*event_list,		/* list of subscribers */
	int 	result);		/* the wakeup result */

void e_interrupt_thread(                /* interrupt target thread */
        tid_t   tid);                   /* thread to interrupt */

char pse_wakeup(                        /* Get the thread status - used by pse*/
        tid_t *waittid);                /* Thread id */

#endif /* _FULL_PROTO */

#endif /* _H_SLEEP */
