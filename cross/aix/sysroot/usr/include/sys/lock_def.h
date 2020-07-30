/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/lock_def.h 1.5.4.19                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1993,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)94       1.5.4.19  src/bos/kernel/sys/lock_def.h, sysproc, bos53L, l2006_50A0 12/6/06 16:17:39 */
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

#ifndef _H_LOCK_DEFINE
#define _H_LOCK_DEFINE

#include <sys/types.h>

/* 
 * Simple_lock control structure for 64-BIT KERNEL is shown below.
 *
 *        +---------------------------------------------------+
 *        |    krlock    |reser-|           |                 |
 *        |     bits     |ved   | I W X X S |    owner_id     |
 *        |              |      |           |                 |
 *        +---------------------------------------------------+
 *        ^             ^      ^                              ^ 
 *        0             23    31                             63
 *
 * If instrumentation is enabled, the above structure is interpretted as a
 * pointer to a secondary lock structure that is allocated above the 4GB
 * line.  
 *
 * Simple_lock control structure for 32-BIT KERNEL is shown below.
 *
 *        +----------------------------+
 *        |             |              |
 *        |  I W X X S  |  owner_id    |
 *        |             |              |
 *        +----------------------------+
 *	  ^                            ^
 *	  0                           31
 *	
 *	I		Interlock bit
 *	W		Waiting bit
 *      S               Secondary structure allocated
 *			(DON'T CHANGE THIS BIT POSITION - instrumentation
 *			 address dependent.  Lock tables are at fixed address)
 *	owner_id	thread_id
 */
typedef	int32long64_t 	simple_lock_data;

/*
 * Complex_lock control structure for 32-BIT and 64-BIT KERNEL is shown below.
 *
 *        +---------------------------+
 *        |             |  thread id  |
 *        | I W WW RD S |-------------|
 *        |             |  read count |
 *        -----------------------------
 *        |             |  recursion  |
 *        |    flags    |             |
 *        |             |    depth    |
 *        +---------------------------+
 *
 *       I               Interlock bit
 *       W               Waiting bit
 *       WW              Want write bit
 *       RD              Read mode bit
 *       S               Secondary structure allocated
 *			(DON'T CHANGE THIS BIT POSITION - instrumentation
 *			 address dependent)
 *       thread id       owner's thread id
 *       read count      readers count
 *       flags           hold recursive bit
 *       recursion depth counter of recursive acquisitions
 *
 * Instrumentation is treated in a similar fashion to that for Simple_locks.
 *
 */
typedef int32long64_t  complex_lock_status;

struct complex_lock_data {
                complex_lock_status   status;
                short   	      flags;
                short   	      recursion_depth;
#ifdef __64BIT_KERNEL
		uint_t 		      reserved;
#else
/*
 * The following code is here to maintain the size of the structure between
 * the 64 bit kernel and the 64 bit application.
 */
#ifdef __64BIT__
		long		      reserved;
#endif
#endif
};


/* 
 * Type definition for lock secondary structure.  Holds the lock control 
 * structure and the instrumentation fields.  Allocated by lock_alloc and
 * freed by lock_free.
 */
struct lock_data_instrumented {

		union {
			simple_lock_data		s_lock;
			struct complex_lock_data 	c_lock;
			struct lock_data_instrumented	*lock_next;
		} lock_control_word;

#define SELECTIVE_TRACE 1
#define LOCK_ALLOCATED  2
		unsigned int    li_flags;       /* lock instrumentation flags*/

#ifndef __64BIT_KERNEL
		union	{			/* lock identifier */
			int 	name;
			struct  {
				short	_id;
				short	occurrence;
			} _lock_id;
		} _lockname;
		int	reserved[4];		/* cache line padding */
#else
                int     reserved[1];            
		union	{			/* lock identifier */
			long	name;
			struct  {
				uint	_id;
				uint	occurrence;
			} _lock_id;
		} _lockname;
#endif /* __64BIT_KERNEL */
#ifdef DEBUG
		int32long64_t	lock_lr;	/* link register of lock */
		int32long64_t	unlock_lr;	/* link register of unlock */
		tid_t 	        lock_caller; 	/* caller of lock */
		tid_t 	        unlock_caller;  /* caller of unlock */
		int 		lock_cpuid;	/* cpu id of lock */
		int		dbg_zero;	/* this word must be zero */
		int 		unlock_cpuid;	/* cpu id of unlock */
		int		dbg_flags;	/* debug flags */
#define LOCK_IS_ALLOCATED 0x80000000    /* this entry is allocated */
#endif /* DEBUG */
	};

/*
*                                       Instrumentation Structure
*
*                                       |                        |
*        LOCK STRUCTURE                 |                        |
*        ---------------------          |------------------------|
*        |                   |--------->| CONTROL STRUCTURE      |
*        ---------------------          |         .              |
*                                       |         .              |
*                                       | Instrumentation word 1 |
*                                       | Instrumentation word n |
*                                       |------------------------|
*                                       |                        |
*                                       |                        |
*
*        LOCK_STRUCTURE 
*        --------------------- 
*        | CONTROL STRUCTURE |
*        --------------------- 
*/

/* type definition for simple_lock */
union _simple_lock{
	simple_lock_data		_slock;
	struct lock_data_instrumented	*_slockp;
};	

/* type definition for complex_lock */
union _complex_lock{
	struct complex_lock_data	_clock;
	struct lock_data_instrumented	*_clockp;
};	

typedef	union _simple_lock	Simple_lock;
typedef union _complex_lock	Complex_lock;

/* type definition for lock pointers */
typedef  Simple_lock	*simple_lock_t;
typedef  Complex_lock	*complex_lock_t;

/* v3 lockl definition */
typedef int32long64_t	lock_t;

/* Initial available definitions */
#define SIMPLE_LOCK_AVAIL		((simple_lock_data)0)
#define COMPLEX_LOCK_AVAIL		SIMPLE_LOCK_AVAIL 
#define LOCK_AVAIL  			((lock_t) -1)    /* lockl locks */

/* This macro is no longer compatible with AIXv3 */
#define LOCKL_OWNER_MASK	0x3fffffff 	
#ifdef _KERNSYS
#define IS_LOCKED(x)    ((tid_t)(*(x) & LOCKL_OWNER_MASK) == curthread->t_tid)
#else
#define IS_LOCKED(x)    \
  ((*(x) != LOCK_AVAIL) && ((tid_t)(*(x) & LOCKL_OWNER_MASK) == thread_self()))
#endif /* _KERNSYS */

/* lockl flags values: */
#define LOCK_SHORT      (0)             /* short wait, inhibit signals */
#define LOCK_NDELAY     (1)             /* do not wait, if unavailable */
#define LOCK_SIGWAKE    (2)             /* wake on signal */
#define LOCK_SIGRET     (4)             /* return on signal */

/* lockl return codes: */
#define LOCK_SUCC       (0)             /* success */
#define LOCK_NEST       (1)             /* already locked by this process */
#define LOCK_FAIL       (-1)            /* lock not available */
#define LOCK_SIG        (-2)            /* process signalled */

#ifdef _NO_PROTO

/* simple lock routines */
void simple_lock();
void simple_lock_hot();
void simple_unlock();
void simple_unlock_hot();
void simple_unlock_mem();
boolean_t simple_lock_try();

/* synchronization for interrupt/interrupt and
 * thread/interrupt critical section
 */
int disable_lock();
void unlock_enable();
void unlock_enable_mem();

/* complex lock basic routines */
void lock_init();
void lock_write();
void lock_read();
void lock_done();
void lock_done_mem();

/* complex lock upgrade/downgrade routines */
boolean_t lock_read_to_write();
void lock_write_to_read();

/* complex lock non blocking routines */
boolean_t lock_try_write();
boolean_t lock_try_read();
boolean_t lock_try_read_to_write();

/* complex lock routines for recursion management */
void lock_set_recursive();
void lock_clear_recursive();
int lock_islocked();

/* lockl routines */
/* - lockl_mine is not exported */
int lockl();
void unlockl();                 
boolean_t lockl_mine();	

#else /* _NO_PROTO */

/* simple lock routines */
void simple_lock(simple_lock_t);
void simple_lock_hot(simple_lock_t);
void simple_unlock(simple_lock_t);
void simple_unlock_mem(simple_lock_t);
void simple_unlock_hot(simple_lock_t);
boolean_t simple_lock_try(simple_lock_t);

/* synchronization for interrupt/interrupt and thread/interrupt critical section
 */
int disable_lock(int,simple_lock_t);
void unlock_enable(int,simple_lock_t);
void unlock_enable_mem(int,simple_lock_t);

/* complex lock basic routines */
void lock_init(complex_lock_t , boolean_t);
void lock_write(complex_lock_t);
void lock_read(complex_lock_t);
void lock_done(complex_lock_t);
void lock_done_mem(complex_lock_t);

/* complex lock upgrade/downgrade routines */
boolean_t lock_read_to_write(complex_lock_t);
void lock_write_to_read(complex_lock_t);

/* complex lock non blocking routines */
boolean_t lock_try_write(complex_lock_t);
boolean_t lock_try_read(complex_lock_t);
boolean_t lock_try_read_to_write(complex_lock_t);

/* complex lock routines for recursion management */
void lock_set_recursive(complex_lock_t);
void lock_clear_recursive(complex_lock_t);
int lock_islocked(complex_lock_t);

/* lockl routines */
/* - lockl_mine is not exported */
int lockl(lock_t *,int);
void unlockl(lock_t *);                
boolean_t lockl_mine(lock_t *);	

#endif /* _NO_PROTO */

#if defined(_POWER_MP) || !defined(_KERNSYS)

#ifdef _NO_PROTO
void simple_lock_init();
#else /* _NO_PROTO */
void simple_lock_init(simple_lock_t);
#endif /* _NO_PROTO */
#else /* _POWER_MP || !_KERNSYS */

/* if the function simple_lock_init changes, so must this MACRO */
#define simple_lock_init(l) *((simple_lock_data *)l) = SIMPLE_LOCK_AVAIL

#endif /* _POWER_MP || !_KERNSYS */

#if defined( __64BIT_KERNEL) || defined(__FULL_PROTO)

/* simple or complex lock owner test */
boolean_t lock_mine(void *);

#endif /* __64BIT_KERNEL || __FULL_PROTO */


#ifdef _INSTRUMENTATION
#define	lo_next		lock_control_word.lock_next
#define lockname	_lockname.name
#define lock_id		_lockname._lock_id._id
#define _occurrence	_lockname._lock_id.occurrence
#endif /* _INSTRUMENTATION */

#ifdef _KERNSYS

/* Sub-definitions of complex_lock */
#define	_status			_clock.status
#define _flags			_clock.flags
#define _recursion_depth	_clock.recursion_depth

extern unsigned int maxspin;
#define MAXSPIN_MP			0x4000
#define MAXSPIN_UP			0x1

#define SIMPLE_LOCK_AVAIL_WAITERS	WAITING  /* lock available with threads
						  * waiting
						  */
/* bit field defines */
#ifdef __64BIT_KERNEL
#define	KRLOCK_IDX_MASK		0xffff000000000000UL	/* Index of krlock. */
#define KRLOCK_IDX_SHIFT	48			/* KRLOCK_IDX_MASK */
							/*  shift count. */
#define KRLOCK_NUM_SPINNERS	0x0000ff0000000000UL	/* Number of CPUs */
							/*  spinning on */
							/*  krlock structure */
#define KRLOCK_NUM_SPINNERS_INC	0x0000010000000000UL	/* Increment value */
							/*  for # spinners. */
#endif /* __64BIT_KERNEL */
#define OWNER_MASK			0x07ffffffL 	/* mask all status bit*/
#define	INTERLOCK			0x80000000L	/* INTERLOCK BIT */
#define	WAITING				0x40000000L	/* WAITING BIT */
#define	WANT_WRITE			0x20000000L	/* WANT_WRITE BIT */
#define	LOCKBIT				0x20000000L	/* LOCK BIT */
#define RECURSION 			0x10000000L	/* vmm RECURSION BIT */
#define	READ_MODE			0x10000000L	/* READ_MODE BIT */
#define	INSTR_ON			0x08000000L	/* RECURSIVE BIT */
#define READ_COUNT_MASK			OWNER_MASK	/* extract READ COUNT */
#define ONE_READER			0x10000001L	/* set one reader */
#define THREAD_BIT			0x00000001L /* set if owner is a thread */

/* recursive flag define */
#define	RECURSIVE	    1	

/* trace sub-hooks */
#define hkwd_LOCK_TAKEN     1
#define hkwd_LOCK_MISS      2
#define hkwd_LOCK_RECURSIVE 3
#define hkwd_LOCK_BUSY      4
#define hkwd_LOCK_DISABLED  8

#define hkwd_KRLOCK		0x10
#define hkwd_KRLOCK_ALLOC	0x11
#define hkwd_KRLOCK_FREE	0x12
#define hkwd_KRLOCK_ACQUIRE	0x13
#define hkwd_KRLOCK_RELEASE	0x14
#define hkwd_KRLOCK_HANDOFF	0x15
#define hkwd_KRLOCK_CONFER	0x16
#define hkwd_KRLOCK_PROD	0x17
#define hkwd_KRLOCK_SPIN	0x18


#define hkwd_SETRECURSIVE   1
#define hkwd_CLEARRECURSIVE 2

/* other defines: lock operation for traces */
#define LOCK_SWRITE_TRACE		1
#define LOCK_CWRITE_TRACE		2
#define LOCK_READ_TRACE			3
#define LOCK_UPGRADE_TRACE		4
#define LOCK_DOWNGRADE_TRACE		5

/* L_INSTR(lockword_value) 
 * Determines whether this lock (complex or simple)
 * is instrumented or not. For POWER, the lock
 * addresses always have the INSTR_ON bit set (it's just
 * where they are)
 */
#ifdef __ia64
#define L_INSTR(lw)          ((lw) & 0xE000000000000000ul)     
#else
#define L_INSTR(lw)          ((lw) & INSTR_ON)
#endif /* __ia64   */

/* gets caller's return address from the stack (if trace on) */
void *get_stkp(void);
#ifdef __ia64
#define GET_RETURN_ADDRESS(x)
#else
#define GET_RETURN_ADDRESS(x)				\
if (TRC_ISON(0))					\
{							\
	struct stack_frame {				\
		struct stack_frame *next;		\
		int32long64_t       unused;		\
		int32long64_t       link_register;	\
	} *sf;						\
	sf = (struct stack_frame *)get_stkp();		\
	sf = sf->next;					\
	x = sf->link_register;				\
}

#endif  /* __ia64   */
#endif	/* _KERNSYS */

#endif /* _H_LOCK_DEFINE */

