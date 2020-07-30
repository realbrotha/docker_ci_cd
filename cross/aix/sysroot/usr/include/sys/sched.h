/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/sys/sched.h 1.4.1.10                             */
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
/* @(#)58       1.4.1.10  src/bos/kernel/sys/sched.h, sysproc, bos53H, h2005_33B9 8/12/05 10:53:38 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


#ifndef _H_SYS_SCHED
#define _H_SYS_SCHED

#include <standards.h>

#ifdef _ALL_SOURCE
#include <sys/pri.h>   
#include <sys/m_param.h>   
#include <sys/time.h>

#define PRIORITY_MIN PSWP        /* minumum priority */     
#define PRIORITY_MAX PIDLE       /* maximum priority */

#define RR_INTERVAL HZ           /* time interval for round robin (SCHED_RR)
                                    scheduling policy */

#define PTHREAD_PRIO_MIN 1       /* minimum priority for pthreads */
#define PTHREAD_PRIO_MAX 127     /* maximum priority for pthreads */
#endif


#define SCHED_OTHER  0           /* default AIX scheduling policy */
#define SCHED_FIFO   1           /* first in-first out scheduling policy */
#define SCHED_RR     2           /* round robin scheduling policy */
#define SCHED_LOCAL  3           /* local thread scope scheduling policy */
#define SCHED_GLOBAL 4           /* global thread scope scheduling policy */
#define SCHED_FIFO2  5           /* FIFO with RQHEAD after short sleep */
#define SCHED_FIFO3  6           /* FIFO with RQHEAD all the time */
#define SCHED_FIFO4  7           /* FIFO with weak preempt */

#ifdef __cplusplus
extern "C" {
#endif
	
struct sched_param
{
        int      sched_priority;
        int      sched_policy;
        int      sched_reserved[6];
};

struct timespec;

int      sched_get_priority_max(int);
int      sched_get_priority_min(int);
int      sched_getparam(pid_t, struct sched_param *);
int      sched_getscheduler(pid_t);
int      sched_rr_get_interval(pid_t, struct timespec *);
int      sched_setparam(pid_t, const struct sched_param *);
int      sched_setscheduler(pid_t, int, const struct sched_param *);
int 	 sched_yield(void);	

#ifdef __cplusplus
}
#endif

#endif /* _H_SYS_SCHED */
