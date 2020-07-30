/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/time.h 1.41.6.3                              */
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
/* @(#)15       1.41.6.3  src/bos/kernel/sys/time.h, sysproc, bos53X, x2009_51A8 9/10/09 04:27:02 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: ADD_NS_TO_TIMEVAL
 *		ADD_TO_NS
 *		ntimeradd
 *		ntimerclear
 *		ntimercmp
 *		ntimerisset
 *		ntimersub
 *		timerclear
 *		timercmp
 *		timerisset
 *		
 *
 *   ORIGINS: 26,27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1985,2001
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


#ifndef _H_SYS_TIME
#define _H_SYS_TIME

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#if _XOPEN_SOURCE_EXTENDED==1

/*
 * The base timer services are based on the POSIX realtime extensions.
 * These timers services support one or more timers per process and
 * a very fine timer granularity.
 */

/*
 * The following are the BSD labels for the timer types.
 */
#define	ITIMER_REAL		0		/* Per-process real time */
#define	ITIMER_VIRTUAL		1		/* Per-process time */
#define	ITIMER_PROF		2		/* Per-process user time */

/* 
 * The following are the AIX labels for the timer types.
 */
#define	ITIMER_VIRT		3		/* Per-process time */
#define ITIMER_REAL1		20		/* Per-thread real time */
#define ITIMER_REAL_TH ITIMER_REAL1             /* Per-thread real time */

/*
 * The following is the BSD equivalent of the timerstruc. The main
 * difference is that the maximum resolution is specificed in microseconds
 * instead of nanoseconds.
 *
 * The #ifdef-ing for tv_usec resolves an incompatibility between the
 * unix95 and the unix98 standards:  We want tv_usec (and tv_sec) to be
 * an "int" so it will be the correct size when compiled in 64-bit mode.
 * Unfortunately, unix95 requires a "long," so we must compile with "long"
 * in 32-bit mode to be compliant, even though "int" is the same size.
 *
 * In 64-bit mode, which is only unix98 compliant, and in 32-bit mode
 * when unix98 is specifically requested, we compile with "suseconds_t,"
 * which is equivalent to "int."
 */
struct timeval {
	time_t		tv_sec;			/* seconds */
#if defined(__64BIT__) || (_XOPEN_SOURCE >= 500)
	suseconds_t	tv_usec;		/* microseconds */
#else
	long		tv_usec;		/* microseconds */
#endif
};

#ifdef _ALL_SOURCE
/* 32-bit size invariant timeval
 */
struct timeval32 {
    int32_t tv_sec;     /* 32bit time_t value */
    int32_t tv_usec; 
};

#define CP_TIMEVAL(__tsrc, __tdest)   \
        (__tdest).tv_sec  = (__tsrc).tv_sec;  \
        (__tdest).tv_usec = (__tsrc).tv_usec

#ifdef _LONG_LONG
struct timeval64 {
    int64_t tv_sec;	/* 64bit time_t value */
    int32_t tv_usec;
#if defined(__ia64) && !defined(__64BIT__)
    int32_t tv_pad1;    /* padding if needed */
#endif
};
#endif

/*
 * The following provides a way to convert the current time in GMT
 * to a local time.
 */
struct timezone {
	int		tz_minuteswest;	/* minutes west of Greenwich */
	int		tz_dsttime;	/* type of dst correction */
};
#define	DST_NONE		0	/* not on dst */
#define	DST_USA			1	/* USA style dst */
#define	DST_AUST		2	/* Australian style dst */
#define	DST_WET			3	/* Western European dst */
#define	DST_MET			4	/* Middle European dst */
#define	DST_EET			5	/* Eastern European dst */
#define	DST_CAN			6	/* Canada */

#endif /* _ALL_SOURCE */

/*
 * The following is the BSD equivalent of the itimerstruc_t.
 */
struct	itimerval {
	struct		timeval it_interval; 	/* timer interval */
	struct		timeval it_value; 	/* current value */
};

#ifdef _NO_PROTO
extern int getitimer();
extern int setitimer();
extern int gettimeofday();
#ifdef _ALL_SOURCE
extern int settimeofday();
#endif /* _ALL_SOURCE */
extern int utimes();
#else /* _NO_PROTO */
extern int getitimer(int, struct itimerval *);
extern int setitimer(int, const struct itimerval *__restrict__, struct itimerval *__restrict__);
extern int gettimeofday(struct timeval *__restrict__, void *__restrict__);
#ifdef _ALL_SOURCE
extern int settimeofday(struct timeval *, struct timezone *);
#endif /* _ALL_SOURCE */
extern int utimes(const char *, const struct timeval *);
#endif /* _NO_PROTO */

/*
 * Select uses bit masks of file descriptors.
 * These macros manipulate such bit fields.
 * FD_SETSIZE may be defined by the user to the maximum valued file
 * descriptor to be selected.
 */
#ifndef FD_SETSIZE
#define FD_SETSIZE     65534
#endif

/* Number of bits per fds_bits entry */
#define __NFDBITS  (sizeof(long) * 8)	/* bits per mask */
/* Number of entries needed for FD_SETSIZE open files */
#define __NUM_ENTRIES  (FD_SETSIZE/__NFDBITS+1)

typedef struct 
#ifdef _ALL_SOURCE
fd_set
#endif /* _ALL_SOURCE */
{
        long fds_bits[__NUM_ENTRIES];  /* bitmask for open file descriptors */
} fd_set;


#if _XOPEN_SOURCE>=500
#ifndef _TIMESPEC
#define _TIMESPEC
struct timespec {
    time_t tv_sec;         /* seconds */
    long   tv_nsec;        /* and nanoseconds */
};
#endif
#ifdef _NO_PROTO
extern int pselect();
#else
extern int pselect(int, void *__restrict__, void *__restrict__, void *__restrict__, const struct timespec *__restrict__, const sigset_t *__restrict__);
#endif
#endif

#ifdef _NO_PROTO
#ifndef _MSGQSUPPORT
extern int __fd_select();
static int select()
		{
			return __fd_select();
		}
#else
extern int select();
#endif /* _MSGQSUPPORT */
#else   /* _NO_PROTO */
#ifndef _KERNEL
/* The first parameter was changed from unsigned long to int because
 * that is what XPG4.2 requires.
 */
#ifndef _MSGQSUPPORT
extern int __fd_select(int, fd_set *__restrict__, fd_set *__restrict__, 
			fd_set *__restrict__, struct timeval *__restrict__);
static int select(int __fds, 
		fd_set *__restrict__ __readlist,
		fd_set *__restrict__ __writelist,
		fd_set *__restrict__ __exceptlist,
		struct timeval *__restrict__ __timeout)  
		{
			return __fd_select(__fds, __readlist, __writelist,
						__exceptlist, __timeout);
		}
#else
extern int select(int, fd_set *__restrict__, fd_set *__restrict__, fd_set *__restrict__, struct timeval *__restrict__);
#endif /* _MSGQSUPPORT */
#else /* _KERNEL */
#ifndef _MSGQSUPPORT
extern int __fd_select(uint, void *, void *, void *, struct timeval *);
static int select(uint __fds, void *__readlist, void *__writelist, 
		void *__exceptlist, struct timeval *__timeout)
		{
			return __fd_select(__fds, __readlist, __writelist,
						__exceptlist, __timeout);
		}
#else
extern  int select(uint, void *, void *, void *, struct timeval *);
#endif /* _MSGQSUPPORT */
#endif /* _KERNEL */
#endif /* _NO_PROTO */

/*
 * This prototype must match the one in string.h.
 */
#if defined(__cplusplus) && !defined(_H_STRING)
#ifdef	_NO_PROTO
extern void	*memset();
#else
extern void     *memset(void *, int, size_t);
#endif	/* _NO_PROTO */
#endif	/* __cplusplus */

#ifndef _ALL_SOURCE
#ifdef _NO_PROTO

extern void FD_SET();
extern void FD_CLR();
extern int FD_ISSET();

#else /* _NO_PROTO */

extern void FD_SET(int,fd_set *);
extern void FD_CLR(int,fd_set *);
extern int FD_ISSET(int,fd_set *);

#endif /* _NO_PROTO */

#define FD_ZERO(p) { fd_set *__q=p; \
	memset((__q), 0, sizeof(*(__q))); }

#else /* _ALL_SOURCE */

#define FD_SET(n, p) \
	((p)->fds_bits[(n)/__NFDBITS] |= ((long)1 << ((n) % __NFDBITS)))
#define FD_CLR(n, p) \
	((p)->fds_bits[(n)/__NFDBITS] &= ~((long)1 << ((n) % __NFDBITS)))
#define FD_ISSET(n, p) \
	(((p)->fds_bits[(n)/__NFDBITS] & ((long)1 << ((n) % __NFDBITS)))?1:0)
#define FD_ZERO(p)      memset((p), 0, sizeof(*(p)))
#endif /* _ALL_SOURCE */ 

#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _ALL_SOURCE

/* 
 * The following are the Posix labels for the timer types.
 */
#define	TIMEOFDAY		9		/* per process sys clock time */	
/*
 * Constants defining the hard-coded id's for each type of timer.
 */
#define	TIMERID_ALRM	(ITIMER_REAL)		/* alarm() */
#define	TIMERID_REAL	(ITIMER_REAL) 		/* bsd real */
#define	TIMERID_VIRTUAL	(ITIMER_VIRTUAL) 	/* bsd virtual */
#define	TIMERID_PROF	(ITIMER_PROF)		/* bsd profiling */
#define	TIMERID_VIRT	(ITIMER_VIRT)		/* aix virtual */
#define	TIMERID_TOD	(TIMERID_VIRT+1)	/* posix timers */
#define TIMERID_REAL1	(ITIMER_REAL1)		/* aix real1 */
#define TIMERID_REAL_TH  TIMERID_REAL1          /* Per-thread real timerid */

/*
 * Constants defining the number of timers for each timer type.
 *
 * NALRM  	number of per-process alarm and real timers. 
 * NPROF  	number of per-process profiling timers. 
 * NVIRTUAL  	number of per-process virtual timers. 
 * NTIMEOFDAY	number of per-process time of day timers.
 * NTIMERS	total number of per-process timers.
 *
 * NALRMT 	number of per-thread alarm and real timers.
 * NTIMERST	total number of per-thread timers.
 */

#define NALRM           1      
#define NPROF           1    
#define NVIRTUAL        2  
#define NTIMEOFDAY      5 
#define NTIMERS         (NALRM + NPROF + NVIRTUAL + NTIMEOFDAY)

#define NALRM_THREAD	1
#define NTIMERS_THREAD	(NALRM_THREAD)

/*
 *  The Epoch is the time 0 hours, 0 minutes, 0 seconds, January 1, 1970
 *  Coordinated Universal Time. 
 */
#define	MIN_SECS_SINCE_EPOCH	0

/*
 *  System time constants
 */
#define NS_PER_TICK	(NS_PER_SEC/HZ)	/* nanoseconds per clock tick	*/
#define	uS_PER_SECOND	(1000000)	/* # of microseconds in one sec.*/
#define	NS_PER_uS	(1000)		/* # of nanoseconds in one us	*/
#define	MAX_SECS_TO_uS	4000		/* most seconds representable as*/
					/* microseconds in unsigned int	*/
#define	MAX_NS_TO_uS	294967296	/* most ns representable as us	*/
					/* in uint given MAX_SECS_TO_uS	*/
					/* is reached.			*/
#define	NS_PER_SEC	1000000000		/* # of nanosecs in 1 second*/
#define	uS_PER_SEC	(NS_PER_SEC / 1000)	/* # of microsecs in 1 sec  */
#define	NS_PER_MSEC	(NS_PER_SEC / 1000)	/* # of nanosecs in 1 msec  */
#define MS_PER_SEC	1000

#define	MAX_DEC_SECS	2
#define	MAX_DEC_NS	147483647

/*
 * The following is used to hold a timer value.
 */
struct timestruc_t {
        time_t		tv_sec;         /* seconds			*/
        suseconds_t	tv_nsec;        /* and nanoseconds		*/
};

#ifdef	_ALL_SOURCE

/* 32-bit size invariant timestruc_t
 */
struct timestruc32_t {
    int32_t     tv_sec;         /* 32bit time_t value           */
    int32_t     tv_nsec;        /* 32bit suseconds_t value      */
};

#if defined(_ALL_SOURCE) && (defined(__64BIT__) || defined(_LONG_LONG))
/* 64-bit size invariant timestruc_t
 */
struct timestruc64_t {
    int64_t     tv_sec;         /* 64bit time_t value           */
    int32_t     tv_nsec;        /* 32bit suseconds_t value      */
};
#endif

#define CP_TIMESTRUCT(__tsrc, __tdest)   \
        (__tdest).tv_sec  = (__tsrc).tv_sec;  \
        (__tdest).tv_nsec = (__tsrc).tv_nsec

#endif /* _ALL_SOURCE */

/*
 * The following is used to define a timer.
 */
struct itimerstruc_t {
        struct  timestruc_t it_interval; /* timer interval		*/
        struct  timestruc_t it_value;    /* current value		*/
};

#ifdef	_ALL_SOURCE

/* 32-bit size invariant itimerstruc_t
 */
struct itimerstruc32_t {
    struct  timestruc32_t it_interval; /* timer interval        */
    struct  timestruc32_t it_value;    /* current value         */
};

#if defined(_ALL_SOURCE) && (defined(__64BIT__) || defined(_LONG_LONG))
/* 64-bit size invariant itimerstruc_t
 */
struct itimerstruc64_t {
    struct  timestruc64_t it_interval; /* timer interval        */
    struct  timestruc64_t it_value;    /* current value         */
};
#endif

#define CP_ITIMERSTRUCT(__tsrc, __tdest) \
        (__tdest).it_interval.tv_sec  = (__tsrc).it_interval.tv_sec;  \
        (__tdest).it_interval.tv_nsec = (__tsrc).it_interval.tv_nsec; \
        (__tdest).it_value.tv_sec     = (__tsrc).it_value.tv_sec;     \
        (__tdest).it_value.tv_nsec    = (__tsrc).it_value.tv_nsec


#endif /* _ALL_SOURCE */

typedef struct timebasestruct {
	int		flag;    /* indicats time base or real time */
	unsigned int	tb_high; /* high 32 bits, or seconds */
	unsigned int	tb_low;	 /* low 32 bits, or nanoseconds */
	} timebasestruct_t;	

int read_real_time(timebasestruct_t *, size_t);
int read_wall_time(timebasestruct_t *, size_t);
int time_base_to_time(timebasestruct_t *, size_t);
#define TIMEBASE_SZ (sizeof (struct timebasestruct))

#ifdef _KERNEL
/*
 * External kernel variables 
 */

extern time_t lbolt;              /* number ticks since last boot */
extern time_t time;               /* memory mapped time in secs since Epoch */
extern struct timestruc_t tod; 	  /* memory mapped timer structure */

#endif  /* _KERNEL */

/*
 * Operations on timestruc_t.
 *
 * Note that ntimercmp only works for cmp values of !=, >, and <.
 */
#define	ntimerisset(tvp)	((tvp)->tv_sec || (tvp)->tv_nsec)
#define	ntimerclear(tvp)	(tvp)->tv_sec = (tvp)->tv_nsec = 0
#define	ntimercmp(tvp, fvp, cmp)					\
	((tvp).tv_sec cmp (fvp).tv_sec || 				\
	 (tvp).tv_sec == (fvp).tv_sec && 				\
	 (tvp).tv_nsec cmp (fvp).tv_nsec)
#define	ntimeradd(tvp, svp, rvp)					\
	{								\
		(rvp).tv_sec = (tvp).tv_sec + (svp).tv_sec;		\
		(rvp).tv_nsec = (tvp).tv_nsec + (svp).tv_nsec;		\
		if((rvp).tv_nsec > (NS_PER_SEC - 1))   {		\
			(rvp).tv_nsec -= NS_PER_SEC;			\
			(rvp).tv_sec++;					\
		}							\
		assert((rvp).tv_nsec <= NS_PER_SEC);			\
	}
#define	ntimersub(tvp, svp, rvp)					\
	{								\
		assert((tvp).tv_nsec <= NS_PER_SEC);			\
		assert((svp).tv_nsec <= NS_PER_SEC);			\
		assert(!((tvp).tv_sec == 0 && ((svp).tv_nsec > (tvp).tv_nsec)));\
		if((tvp).tv_sec == (svp).tv_sec)  {			\
			assert((tvp).tv_nsec >= (svp).tv_nsec);		\
		}							\
		else  {							\
			assert((tvp).tv_sec > (svp).tv_sec);		\
		}							\
									\
		if((svp).tv_nsec > (tvp).tv_nsec)  {			\
			assert((tvp).tv_sec > (svp).tv_sec);		\
			(rvp).tv_sec = ((tvp).tv_sec - 1) - (svp).tv_sec;\
			(rvp).tv_nsec = ((int)(((uint)((tvp).tv_nsec) + NS_PER_SEC) - (uint)((svp).tv_nsec)));\
		}							\
		else  {							\
			(rvp).tv_sec = (tvp).tv_sec - (svp).tv_sec;	\
			(rvp).tv_nsec = (tvp).tv_nsec - (svp).tv_nsec;	\
		}							\
									\
		assert((tvp).tv_nsec <= NS_PER_SEC);			\
		assert((svp).tv_nsec <= NS_PER_SEC);			\
		assert((rvp).tv_nsec <= NS_PER_SEC);			\
	}

/*
 * The rest of this file is the interface to the BSD timer services.
 * Most of these services are implemented as subroutines that convert
 * the interface to the corresponding POSIX timer service.
 *
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	(#)time.h	7.1 (Berkeley) 6/4/86
 */

/*
 * The following is the BSD equivalent of the timerstruc. The main
 * difference is that the maximum resolution is specificed in microseconds
 * instead of nanoseconds.
 *
 * struct timeval {
 *       int		tv_sec;         * seconds *
 *       int		tv_usec;        * microseconds *
 * };
 */

/*
 * Operations on timevals.
 *
 * Note that timercmp only works for cmp values of !=, >, and <.
 */

#define	timerisset(tvp)		((tvp)->tv_sec || (tvp)->tv_usec)
#define	timerclear(tvp)		(tvp)->tv_sec = (tvp)->tv_usec = 0
#define	timercmp(tvp, fvp, cmp)						\
	((tvp)->tv_sec cmp (fvp)->tv_sec ||				\
	 (tvp)->tv_sec == (fvp)->tv_sec &&				\
	 (tvp)->tv_usec cmp (fvp)->tv_usec)

#define	ADD_TO_NS(tvp, delta)						\
{									\
	(tvp).tv_nsec += delta;						\
	if((tvp).tv_nsec >= NS_PER_SEC)  {				\
		(tvp).tv_sec++;						\
		(tvp).tv_nsec -= NS_PER_SEC;				\
	}								\
}

/*
 *  Adds a value of nanoseconds to a timeval structure (which traditionally
 *  contains microseconds).
 */
#define	ADD_NS_TO_TIMEVAL(tvp, delta)					\
{									\
	(tvp).tv_usec += delta;						\
	if((tvp).tv_usec >= NS_PER_SEC)  {				\
		(tvp).tv_sec++;						\
		(tvp).tv_usec -= NS_PER_SEC;				\
	}								\
}


#if defined(_BSD_INCLUDES) || defined(_LINUX_SOURCE_COMPAT)
#include <time.h>
#endif	/* _BSD_INCLUDES || _LINUX_SOURCE_COMPAT */

#endif /* _ALL_SOURCE */

/*
 * Function prototypes for 64bit kernel only
 */
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
extern void	curtime (struct timestruc_t *timestruct);
extern int	kgettickd(int32long64_t *tmdelta, 
					int *tickdelta, int *clockset);
extern int	ksettickd(int32long64_t *tmdelta, 
					int *tickdelta, int *clockset);
extern int	ksettimer(struct timestruc_t *);
extern int	nsleep(struct timestruc_t *, struct timestruc_t *);
extern int	kclock_gettime(clockid_t clock_id, struct timestruc_t *tp);
#endif /* __64BIT_KERNEL || __FULL_PROTO */

#ifdef __cplusplus
}
#endif

#endif /* _H_SYS_TIME */
