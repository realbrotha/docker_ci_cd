/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/usr/include/time.h 1.29.3.36                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1985,2007              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)72  1.29.3.36  src/bos/usr/include/time.h, libctime, bos53Q, q2008_05B1 3/21/07 05:31:46 */
/*
 * COMPONENT_NAME: (LIBCTIME) Standard C Library Time Management Functions
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27,71
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */

#ifndef _H_TIME
#define _H_TIME

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *
 *      The ANSI standard requires that certain values be in time.h.
 *      It also requires that if _ANSI_C_SOURCE is defined then ONLY these
 *      values are present.
 *
 *      This header includes all the ANSI required entries.  In addition
 *      other entries for the AIX system are included.
 *
 */
#ifdef _ANSI_C_SOURCE

/* The following definitions are required to be in time.h by ANSI */

#ifndef NULL
#define NULL	0			/* p79268 */
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long 	size_t;
#endif

#ifndef _CLOCK_T
#define _CLOCK_T
typedef int		clock_t;
#endif

#ifndef _TIME_T
#define _TIME_T
#ifdef	_LINUX_SOURCE_COMPAT
typedef long int	time_t;
#else	/* !_LINUX_SOURCE_COMPAT */
#ifdef __64BIT__
typedef long		time_t;
#else
typedef int		time_t;
#endif 
#endif	/* !_LINUX_SOURCE_COMPAT */
#endif

#ifndef CLOCKS_PER_SEC
#define CLOCKS_PER_SEC	1000000		/* microseconds in sec */
#endif

struct	tm {	/* see ctime(3) */
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
};

#ifdef _NO_PROTO
    extern size_t 	strftime();
    extern clock_t 	clock();
    extern double 	difftime();
    extern time_t 	mktime();
#ifndef _KERNEL
    extern time_t 	time();
#endif /* _KERNEL */
    extern char 	*asctime();
    extern char 	*ctime();
    extern struct tm    *gmtime();
    extern struct tm    *localtime();

/* REENTRANT FUNCTIONS */
#if defined(_THREAD_SAFE) || (_XOPEN_SOURCE >= 500)
/* See comments in stdlib.h on _AIX32_THREADS */
#if _AIX32_THREADS
    extern int 	asctime_r();
    extern int	ctime_r();
    extern int 	gmtime_r();
    extern int 	localtime_r();
#else	/* POSIX 1003.1c prototype */
    extern char 	*asctime_r();
    extern char		*ctime_r();
    extern struct tm	*gmtime_r();
    extern struct tm	*localtime_r();
#endif /* _AIX32_THREADS */
#endif /* _THREAD_SAFE or _XOPEN_SOURCE>=500 */

#else	/* use POSIX required prototypes */
    extern size_t 	strftime(char *__restrict__, size_t, const char *__restrict__, const struct tm *__restrict__);
    extern clock_t 	clock(void);
    extern double 	difftime(time_t, time_t);
    extern time_t 	mktime(struct tm *);
#ifndef _KERNEL
    extern time_t 	time(time_t *);
#endif /* _KERNEL */
    extern char 	*asctime(const struct tm *);
    extern char 	*ctime(const time_t *);
    extern struct tm *gmtime(const time_t *);
    extern struct tm *localtime(const time_t *);

/* REENTRANT FUNCTIONS */
#if defined(_THREAD_SAFE) || (_XOPEN_SOURCE >= 500)
#if _AIX32_THREADS
    extern int 	asctime_r(const struct tm *, char *, int);
    extern int	ctime_r(const time_t *, char *, int);
    extern int	gmtime_r(const time_t *, struct tm *);
    extern int 	localtime_r(const time_t *, struct tm *);
#else	/* POSIX 1003.1c prototypes */
    extern char		*asctime_r(const struct tm *__restrict__, char *__restrict__);
    extern char		*ctime_r(const time_t *, char *);
    extern struct tm	*gmtime_r(const time_t *__restrict__, struct tm *__restrict__);
    extern struct tm	*localtime_r(const time_t *__restrict__, struct tm *__restrict__);
#endif /* _AIX32_THREADS */
#endif	/* _THREAD_SAFE or _XOPEN_SOURCE>=500 */
#endif /* _NO_PROTO */

#endif /*_ANSI_C_SOURCE */
 
/*
 *   The following are values that have historically been in time.h.
 *
 *   They are NOT part of the ANSI defined time.h and therefore are
 *   not included when _ANSI_C_SOURCE is defined.
 *
 */

#ifdef _POSIX_SOURCE

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>

#if (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE<200112L) || defined(_ALL_SOURCE)
#ifndef CLK_TCK
#define CLK_TCK   100       /* clock ticks/second, >= 10 */
#endif
#endif

extern char *tzname[];

#ifdef _NO_PROTO
    extern void tzset();
#else
    extern void tzset(void);
#endif /* _NO_PROTO */

#endif /* _POSIX_SOURCE */

#ifdef _XOPEN_SOURCE
    extern long timezone;
    extern int daylight;
#ifdef _NO_PROTO
    extern char         *strptime();
#else /* _NO_PROTO */
    extern char         *strptime(const char *, const char *, struct tm *);
#endif /* _NO_PROTO */
#endif /* _XOPEN_SOURCE */

#if _XOPEN_SOURCE_EXTENDED==1
    extern int getdate_err;
#ifdef _NO_PROTO
    extern struct tm *getdate();
#else /* _NO_PROTO */
    extern struct tm *getdate(const char *);
#endif /* _NO_PROTO */
#endif /* _XOPEN_SOURCE_EXTENDED */

#if _XOPEN_SOURCE>=500
#ifndef _TIMESPEC
#define _TIMESPEC
struct timespec {
    time_t tv_sec;         /* seconds */
    long   tv_nsec;        /* and nanoseconds */
};
#endif

struct itimerspec {
    struct  timespec it_interval; /* timer period */
    struct  timespec it_value;    /* expiration */
};

#define CLOCK_REALTIME	         ((clockid_t) 9)  /* same value as TIMEOFDAY */
#define CLOCK_MONOTONIC          ((clockid_t) 10)
#define CLOCK_PROCESS_CPUTIME_ID ((clockid_t) 11)
#define CLOCK_THREAD_CPUTIME_ID  ((clockid_t) 12)
#define TIMER_ABSTIME	999

extern int clock_getres(clockid_t, struct timespec *);
extern int clock_gettime(clockid_t, struct timespec *);
extern int clock_settime(clockid_t, const struct timespec *);
extern int clock_getcpuclockid(pid_t, clockid_t *);
extern int nanosleep(const struct timespec *, struct timespec *);
#ifdef _H_SYS_SIGNAL
extern int timer_create(clockid_t, struct sigevent *__restrict__, timer_t *__restrict__);
#else /* _H_SYS_SIGNAL */
extern int timer_create(clockid_t, void *__restrict__, timer_t *__restrict__);
#endif /* _H_SYS_SIGNAL */
extern int timer_delete(timer_t);
extern int timer_gettime(timer_t, struct itimerspec *);
extern int timer_getoverrun(timer_t);
extern int timer_settime(timer_t, int, const struct itimerspec *__restrict__, struct itimerspec *__restrict__);
#endif /* _XOPEN_SOURCE>=500 */

#if _XOPEN_SOURCE>=600
extern int clock_nanosleep(clockid_t, int, const struct timespec*, struct timespec*);		
#endif /* _XOPEN_SOURCE>=600 */	
	
#ifdef _ALL_SOURCE

#ifndef _H_STDDEF
#include <stddef.h>
#endif

#define	TIMELEN	26
/*  Suggested default length of time/date buffer */
#   define NLTBMAX	64
#   ifdef _NO_PROTO
    extern unsigned char *NLctime(), *NLasctime();
    extern char *NLstrtime();
#   else /* ~ _NO_PROTO */
    extern unsigned char *NLctime(long *);
    extern unsigned char *NLasctime(struct tm *);
    extern char *NLstrtime(char *, size_t, const char *, const struct tm *);
#   endif /* _NO_PROTO */
#endif /* _ALL_SOURCE */

/* time64 interfaces */
#if defined(_ALL_SOURCE) && defined(_LONG_LONG)
#ifdef _NO_PROTO
    extern char *ctime64();
    extern struct tm *localtime64();
    extern struct tm *gmtime64();
    extern char *asctime64();
    extern time64_t mktime64();
    extern double difftime64();
#if defined(_THREAD_SAFE) || (_XOPEN_SOURCE >= 500)
    extern char *ctime64_r();
    extern struct tm *localtime64_r();
    extern struct tm *gmtime64_r();
    extern char * asctime64_r();
#endif /* _THREAD_SAFE || _XOPEN_SOURCE */
#else /* _NO_PROTO */
    extern char *ctime64(const time64_t *);
    extern struct tm *localtime64(const time64_t *);
    extern struct tm *gmtime64(const time64_t *);
    extern char *asctime64(const struct tm *);
    extern time64_t mktime64(struct tm *);
    extern double difftime64(time64_t, time64_t);
#if defined(_THREAD_SAFE) || (_XOPEN_SOURCE >= 500)
    extern char *ctime64_r(const time64_t *, char *);
    extern struct tm *localtime64_r(const time64_t *__restrict__, 
                                    struct tm *__restrict__);
    extern struct tm *gmtime64_r(const time64_t *__restrict__, 
                                 struct tm *__restrict__);
    extern char *asctime64_r(const struct tm *__restrict__, char *__restrict__);
#endif /* _THREAD_SAFE || _XOPEN_SOURCE */
#endif /* _NO_PROTO */
#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif
#endif /* _H_TIME */
