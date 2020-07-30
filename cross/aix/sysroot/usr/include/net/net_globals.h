/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/net/net_globals.h 1.48.1.4                       */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1993              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)14	1.48.1.4  src/bos/kernel/net/net_globals.h, sysnet, bos53X, x2010_10B4 3/10/10 10:26:47 */
/*
 *   COMPONENT_NAME: SYSNET
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 27,85
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * Global #defines for OSF/1 networking.
 *
 * Ugly as this file is, it makes the code a lot cleaner!
 *
 */

#ifndef	_NET_GLOBALS_H_
#define _NET_GLOBALS_H_

#include <sys/lock_def.h>
#ifdef	_KERNEL
#include <sys/sleep.h>
#include <sys/user.h>
#include <net/spl.h>
#include <sys/syspest.h>
#include <sys/lockname.h>
#include <sys/lock_alloc.h>
#include <strings.h>
#endif	/* _KERNEL */

void NET_LWSYNC(void);
#pragma mc_func         NET_LWSYNC  { "7c2004ac" }  /* lwsync  */
#pragma reg_killed_by   NET_LWSYNC

/* 
 * Stuff to fix #defines in if.h.
 */
#ifdef simple_lock_data_t
#undef simple_lock_data_t
#endif
#ifdef lock_data_t
#undef lock_data_t
#endif
typedef	Simple_lock	simple_lock_data_t;
typedef	Complex_lock	lock_data_t;
typedef	int *task_t;

#define	lock_init2(lp, s, type)	lock_init(lp, s)

#define NETNHSQUE       128
#define netsqhash(X)    (&nethsque[( ((long)(X) >> 12) + ((long)(X) >> 8) + (long)(X) ) & (NETNHSQUE-1)])
extern	tid_t            nethsque[];

#define	assert_wait(addr, intr) 				\
	e_assert_wait(netsqhash(addr), intr)

#define	assert_wait_mesg(addr, intr, msg) 			\
	e_assert_wait(netsqhash(addr), intr)

#define	clear_wait(thread, result, flag)			\
	e_clear_wait((thread)->t_tid, result)

#define	wakeup_one(addr)	 				\
	e_wakeup_one(netsqhash(addr))

#define	wakeup(addr)	 					\
	e_wakeup(netsqhash(addr))

#define	thread_wakeup(addr)					\
	e_wakeup(netsqhash(addr))

#define	current_thread()	(curthread)
#define	thread_block()		e_block_thread()
#define	thread_swappable(a, b)

#define	PAGE_SIZE	4096
#define	MAXALLOCSAVE	(32 * PAGE_SIZE)	/* param.h in osf */
#define THEWALL_MAX_64BIT (MAXNETKMEM<<SEGSHIFT)
#define THEWALL_MAX_4SEG        (4*256*1024*1024) /* 1 Gig */
#define THEWALL_MAX_1SEG        (256*1024*1024) /* 256 Meg */
#define THEWALL_MAX	(128*1024*1024)	/* 128 Meg */
#define MAX_INITIAL_PIN	((4*512*1024)/ MAXALLOCSAVE)
#define	NNETTHREADS	4
#define MAXHUGESIZE	(128*1024)	/* 128K */

#ifndef NET_ALIGN4
#define NET_ALIGN4_SIZE             sizeof(int)
#define NET_ALIGN4_ALIGNMENT(p)     ((uint)(p) % NET_ALIGN4_SIZE)
#define NET_ALIGN4(p)   (uint)((caddr_t)(p) + NET_ALIGN4_SIZE - 1 - \
                         NET_ALIGN4_ALIGNMENT((caddr_t)(p) + NET_ALIGN4_SIZE - \
                         1))
#endif /* NET_ALIGN4 */

/*
 * So everyone sees the same structures (ifnet, etc)...
 */
#ifndef IP_MULTICAST
#define IP_MULTICAST
#endif

/* These are for OSF compat. Not actually used. */
#define	LTYPE_RAW	1
#define	LTYPE_ROUTE	2
#define	LTYPE_SOCKET	3
#define	LTYPE_SOCKBUF	4
#define	LTYPE_DOMAIN	5
#define LTYPE_ARPTAB	6

#define	STATS_ACTION(lock, action)	action

#define	queue_init(q)   ((q)->next = (q)->prev = q)

#define	pfind(pgid)	   		(pgid)
#define	gsignal(pgid, sig)   		pgsignal((pgid), (sig))
#define	psignal(p, sig)   		pidsig((p), (sig))
#define	psignal_inthread(p, sig)   	pidsig((p), (sig))

#define	BM(x)			x
#define	P_UNREF(p)

task_t	first_task;

/*
 * These are default settings. Either or both of locking and spl are valid
 * for 1 or more cpus. However, recommend locks for multis, non-locks for unis.
 * The thread decision is dependent on several things. To configure both
 * sockets and streams to use softnets requires locore or hardware support.
 */
#define NETNCPUS	NCPUS

#define NET_CACHELINESIZE	128

typedef int	spl_t;
#define LOCK_ASSERTL_DECL
#ifdef	DEBUG
#define LOCK_ASSERT(string, cond)	assert(cond)
#else	/* DEBUG */
#define LOCK_ASSERT(string, cond)
#endif	/* DEBUG */
#define LOCK_NETSTATS	 0
#define	LOCK_FREE(lp)			lock_free(lp)

#define NETSPL_DECL(s)		spl_t s;
#define NETSPL(s,level)		s = spl##level()
#define NETSPLX(s)		splx(s)

#define NETSTAT_LOCK_DECL()	int	_stats;
#if	LOCK_NETSTATS
#define NETSTAT_LOCK(lockp)	_stats = disable_lock(PL_IMP, lockp)
#define NETSTAT_UNLOCK(lockp)	unlock_enable(_stats, lockp)
#define NETSTAT_LOCKINIT(lockp)	{					\
	lock_alloc(lockp, LOCK_ALLOC_PIN, IF_SLOCK, (short)lockp);	\
	simple_lock_init(lockp);					\
}

#else
#define NETSTAT_LOCKINIT(lockp)
#define NETSTAT_LOCK(lockp)
#define NETSTAT_UNLOCK(lockp)
#endif

/* ANSI-C compatibility */
#ifndef	CONST
#define CONST		const
#endif
#ifndef	VOLATILE
#define VOLATILE	volatile
#endif

/* types for 64 bit */
#ifdef __64BIT_KERNEL
typedef ulong 		int32ulong64_t;
typedef caddr_t		int32caddr64_t;
typedef uint		short32uint64_t;
#else
typedef int 		int32ulong64_t;
typedef int		int32caddr64_t;
typedef short		short32uint64_t;
#endif

/* Global function prototypes */
#include <sys/types.h>
#include <net/proto_net.h>
#include <net/proto_uipc.h>

#ifdef _KERNEL
#define RTO_DFLT_LOW 1
#define RTO_DFLT_HIGH 64
#define RTO_DFLT_LIMIT 7
#define RTO_DFLT_LENGTH 13
#define RTO_DFLT_SHIFT 7

#ifdef __ia64
#define INET_STACK_DFLT	32
#else
#define INET_STACK_DFLT	16
#endif /* __ia64 */
#endif /* _KERNEL */

struct iftrace {
	int	kmid;
	int	promisc;
};

#define TCP_NDEBUG 100

#define IF_SIZE 256
extern long ifsize;

#ifdef _KERNEL
/* Kernel and Kernel Extensions should get these from one place */
extern CONST u_char	etherbroadcastaddr[6];
extern CONST u_char	ie5_broadcastaddr[6];
extern CONST u_char	fddi_broadcastaddr[6];
#else
/* Others may still need these */
#ifndef etherbroadcastaddr
static CONST u_char    etherbroadcastaddr[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
#endif
#ifndef ie5_broadcastaddr
static CONST u_char    ie5_broadcastaddr[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
#endif
#ifndef fddi_broadcastaddr
static CONST u_char    fddi_broadcastaddr[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
#endif
#endif /* _KERNEL */

struct rw_lock {
	simple_lock_data_t	simple_lock;
	char			dummy1[NET_CACHELINESIZE - sizeof(simple_lock_data_t)];
	int	read_cnt;
	char			dummy2[NET_CACHELINESIZE - sizeof(int)];
};

#define RW_LOCKINIT(lock, size, type, malloc_flags, lock_flags, class, occurrence)\
{ \
	NET_MALLOC((lock), struct rw_lock *, (size), (type), (malloc_flags));\
	lock_alloc(&((lock)->simple_lock), (lock_flags), (class), (occurrence)); \
	simple_lock_init(&((lock)->simple_lock)); \
	(lock)->read_cnt = 0; \
}

#define RW_WRITE_LOCK(lock, old_pri, new_pri) \
{ \
	(old_pri) = disable_lock((new_pri), &((lock)->simple_lock)); \
	{ \
		volatile int *myvalptr = &(lock)->read_cnt; \
		while (*myvalptr); \
	} \
}

#define RW_WRITE_UNLOCK(lock, old_pri) \
	unlock_enable((old_pri), &((lock)->simple_lock));

#define RW_READ_LOCK(lock, old_pri, new_pri, read_pri) \
{ \
	(read_pri) = i_disable(new_pri); \
	(old_pri) = disable_lock((new_pri), &((lock)->simple_lock)); \
	fetch_and_add(&((lock)->read_cnt), 1); \
	unlock_enable((old_pri), &((lock)->simple_lock)); \
}

#define RW_READ_UNLOCK(lock, old_pri) { \
	NET_LWSYNC(); \
	fetch_and_add(&((lock)->read_cnt), -1); \
	i_enable(old_pri); \
}

/* This version of RW_WRITE_LOCK does not spin while holding the lock,
 * but rather continuously releases it and re-acquires it before checking
 * the reference count again; this allows nested readers (i.e. functions
 * that grab the read lock that are called by functions that have grabbed
 * the read lock themselves) to increment the reference count and proceed,
 * even if another thread is trying to grab the same lock as a write lock.
 * Since the lock is released and re-acquired, nested readers have the
 * chance to grab the lock, increment the reference count, and proceed.
 */
#define RW_WRITE_LOCK_RELEASE(lock, old_pri, new_pri)			\
{									\
	(old_pri) = disable_lock((new_pri), &((lock)->simple_lock));	\
	{								\
		volatile int *myvalptr = &(lock)->read_cnt;		\
		while (*myvalptr)					\
		{							\
        	      unlock_enable((old_pri), &((lock)->simple_lock));	\
		      (old_pri) = disable_lock((new_pri),		\
				&((lock)->simple_lock));		\
		}							\
	}								\
}

/* These macros implement read locks *without* disabling interrupts
 * (i.e. issuing "i_disable()" and "i_enable()" calls).
 * They are useful when the code is such that, although a read lock must be
 * held to prevent the state from changing during an operation, interrupts
 * must be enabled to obtain the desired behavior.
 * They must be used with caution because if a thread that is holding a
 * read lock is interrupted by a thread trying to grab the same lock as
 * a write lock, a deadlock situation would occur.
 * Thus, this version of read locks where interrupts are NOT disabled and
 * re-enabled must ONLY be used when the code is such that ALL functions
 * that attempt to grab the write lock are called exclusively in the process
 * context (and NEVER in the interrupt context).
 */
#define RW_READ_LOCK_NO_DISABLE(lock, old_pri, new_pri)			\
{									\
        (old_pri) = disable_lock((new_pri), &((lock)->simple_lock));	\
        fetch_and_add(&((lock)->read_cnt), 1);				\
        unlock_enable((old_pri), &((lock)->simple_lock));		\
}

#define RW_READ_UNLOCK_NO_ENABLE(lock)					\
{									\
        fetch_and_add(&((lock)->read_cnt), -1);				\
}

/* Macro for going from an exclusive write lock to a shared read lock
 * where interrupts are not being disabled for the read lock: the read count
 * is incremented with the lock held, and then the lock is released.
 */
#define RW_WRITE_TO_READ_LOCK_NO_DISABLE(lock, old_pri)			\
{									\
        fetch_and_add(&((lock)->read_cnt), 1);				\
        unlock_enable((old_pri), &((lock)->simple_lock));		\
}

/* Macro for going from a shared read lock to an exclusive write lock 
 * where interrupts are not being re-enabled for the read lock: we decrement
 * the read count and then attempt to grab the write lock for exclusive use
 */
#define RW_READ_TO_WRITE_LOCK_NO_ENABLE(lock, old_pri, new_pri)		\
{									\
	RW_READ_UNLOCK_NO_ENABLE(lock)					\
	RW_WRITE_LOCK_RELEASE(lock, old_pri, new_pri)			\
}

#endif	/* _NET_GLOBALS_H_ */
