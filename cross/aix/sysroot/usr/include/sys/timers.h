/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/timers.h 1.12                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1990          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)29	1.12  src/bos/kernel/sys/timers.h, incstd, bos530 4/27/04 10:37:16 */
/*
 * COMPONENT_NAME: (INCSTD) Standard Include Files
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27, 65
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1990
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */
/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 Release 1.0
 */

#ifndef _H_TIMERS
#define _H_TIMERS
#include <sys/time.h>

#if _XOPEN_SOURCE>=500
#ifdef _KERNEL
#define timespec timestruc_t		/* same struct, diff name */
#define itimerspec itimerstruc_t	/* same struct, diff name */
#define CLOCK_REALTIME           ((clockid_t)TIMEOFDAY) /* 1003.4 */
#define CLOCK_MONOTONIC          10LL                   /* 1003.4 */
#define CLOCK_PROCESS_CPUTIME_ID 11LL                   /* 1003.4 */
#define CLOCK_THREAD_CPUTIME_ID  12LL                   /* 1003.4 */
#define TIMER_ABSTIME  999
#else       /* _KERNEL */
#include <time.h>
#endif      /* _KERNEL */
#else  /* _XOPEN_SOURCE>=500 */
#define timespec timestruc_t		/* same struct, diff name */
#define itimerspec itimerstruc_t	/* same struct, diff name */
#define CLOCK_REALTIME           ((clockid_t)TIMEOFDAY) /* 1003.4 */
#define CLOCK_MONOTONIC          10LL                   /* 1003.4 */
#define CLOCK_PROCESS_CPUTIME_ID 11LL                   /* 1003.4 */
#define CLOCK_THREAD_CPUTIME_ID  12LL                   /* 1003.4 */
#define TIMER_ABSTIME  999
#endif /* _XOPEN_SOURCE>=500 */

#define gettimer(a,b) (getinterval(a,b))

struct itimercb {
	int		itcb_count;	/* timer "overrun" count */
};


/*
 * Notification types
 */
#define DELIVERY_SIGNALS	0	/* same as in sys/events.h */

/*
 * Functions
 */
#ifdef _NO_PROTO
int getclock();
int setclock();
timer_t mktimer();
int rmtimer();
int getinterval();
int reltimer();
#else
int getclock(int, struct timespec *);
int setclock(int, struct timespec *);
timer_t mktimer(int, int, struct itimercb *);
int rmtimer(timer_t);
int getinterval(timer_t, struct itimerspec *);
int reltimer(timer_t, struct itimerspec *, struct itimerspec *);
#endif

#endif	/* _H_TIMERS */
