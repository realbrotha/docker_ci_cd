/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/resource.h 1.16.3.5                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)59       1.16.3.5  src/bos/kernel/sys/resource.h, sysproc, bos53V, v2009_03B2 1/15/09 15:30:54 */

/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 26,27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	(#)resource.h	7.1 (Berkeley) 6/4/86
 *
 * Function:
 *		The rusage structure is included into both the proc
 *	structure and the user structure.  The rlimit structure is
 *	included into the user structure only.  The rusage and rlimit
 * 	structures exist to keep an accounting of resources on a per
 *	process basis.
 *
 */

#ifndef _H_RESOURCE
#define _H_RESOURCE

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>

#if _XOPEN_SOURCE_EXTENDED==1

#define	PRIO_PROCESS	0
#define	PRIO_PGRP	1
#define	PRIO_USER	2

/*
 * Process priority specifications to get/setpriority.
 */
#define	PRIO_MIN	-20
#define	PRIO_MAX	 20

/*
 * Resource utilization information.
 */

#define	RLIM_NLIMITS	8		/* number of resource limits 	*/

#if defined(__64BIT__) && !defined(__64BIT_KERNEL)
#define RLIM_INFINITY	0x7fffffffffffffffL
#else
#define RLIM_INFINITY	0x7FFFFFFF
#endif /* __64BIT__ */

#define RLIM_SAVED_MAX	(RLIM_INFINITY-1)
#define RLIM_SAVED_CUR	(RLIM_INFINITY-2)

typedef unsigned long 	rlim_t;	
struct rlimit {
	rlim_t		rlim_cur;	/* current (soft) limit */
	rlim_t		rlim_max;	/* maximum value for rlim_cur */
};

#if (defined(_ALL_SOURCE) && defined(_LONG_LONG))

#define RLIM64_INFINITY (0x7fffffffffffffffLL)
/*
 * File size soft limit infinity value
 */
typedef unsigned int 	rlim32_t;	
struct rlimit32 {
	rlim32_t	rlim_cur;	/* current (soft) limit */
	rlim32_t	rlim_max;	/* maximum value for rlim_cur */
};
#ifdef __64BIT__
#define RLIM_FSB_INFINITY	0xFFFFFFFFFFFFFFFFUL	/* 64bit kernel */
#else
#define RLIM_FSB_INFINITY	0xFFFFFFFFU
#endif /* __64BIT__ */

typedef unsigned long long rlim64_t;
struct rlimit64 {
	rlim64_t	rlim_cur;	/* current (soft) limit */
	rlim64_t	rlim_max;	/* maximum value for rlim_cur */
};
#endif /* _ALL_SOURCE && _LONG_LONG */

#ifdef _KERNSYS
/*
 * RLFLAG_... definitions are for kernel use
 */
#define RLFLAG_INF      0               /* limit is infinite            */
#define RLFLAG_MAX      1               /* limit in U_saved_rlimit rlim_max */
#define RLFLAG_CUR      2               /* limit in U_saved_rlimit rlim_cur */
#define RLFLAG_SML      3               /* 32-bit limit in U_rlimit     */

#define RLCUR           0               /* refers to rlim_cur value */
#define RLMAX           1               /* refers to rlim_max value */

/*
 * RUSAGE_INCR definition is for kernel-only atomic increments of
 * 64-bit rusage fields.
 */
#define RUSAGE_INCR(llp, amount) {				\
		unsigned int prev;				\
		prev = fetch_and_add((int *)llp + 1, amount);	\
        	if (prev + amount < prev)			\
                	fetch_and_add((int *)llp, 1);		\
	}

#endif /* _KERNSYS */

#define	RUSAGE_SELF	0
#define	RUSAGE_CHILDREN	-1
#define	RUSAGE_THREAD	1
#define	RUSAGE_TIMES	2

/* ru_first, ru_last are convenience defines used in loops, e.g., see ruadd  */
#define	ru_first	ru_ixrss
#define	ru_last		ru_nivcsw

/*
 * struct rusage should have the same fields as struct rusage64.
 */
struct	rusage
{
	struct timeval 	ru_utime;	/* user time used */
	struct timeval 	ru_stime;	/* system time used */
	long		ru_maxrss;
	long		ru_ixrss;	/* integral shared memory size */
	long		ru_idrss;	/* integral unshared data " */
	long		ru_isrss;	/* integral unshared stack " */
	long		ru_minflt;	/* page reclaims */
	long		ru_majflt;	/* page faults */
	long		ru_nswap;	/* swaps */
	long		ru_inblock;	/* block input operations */
	long		ru_oublock;	/* block output operations */
	long		ru_msgsnd;	/* messages sent */
	long		ru_msgrcv;	/* messages received */
	long		ru_nsignals;	/* signals received */
	long		ru_nvcsw;	/* voluntary context switches */
	long		ru_nivcsw;	/* involuntary " */

};

/*
 * struct rusage64 should have the same fields as struct rusage
 * in 32-bit mode. This struct is for compatability with old 32-bit
 * applications looking at a 64-bit process.
 * 
 */
#if defined(_ALL_SOURCE) && defined(_LONG_LONG)
struct	rusage64
{
#ifdef __64BIT__
	struct timeval32 ru_utime;	/* user time used */
	struct timeval32 ru_stime;	/* system time used */
#else
	struct timeval ru_utime;	/* user time used */
	struct timeval ru_stime;	/* system time used */
#endif
	long long	ru_maxrss;
	long long	ru_ixrss;	/* integral shared memory size */
	long long	ru_idrss;	/* integral unshared data " */
	long long	ru_isrss;	/* integral unshared stack " */
	long long	ru_minflt;	/* page reclaims */
	long long	ru_majflt;	/* page faults */
	long long	ru_nswap;	/* swaps */
	long long	ru_inblock;	/* block input operations */
	long long	ru_oublock;	/* block output operations */
	long long	ru_msgsnd;	/* messages sent */
	long long	ru_msgrcv;	/* messages received */
	long long	ru_nsignals;	/* signals received */
	long long	ru_nvcsw;	/* voluntary context switches */
	long long	ru_nivcsw;	/* involuntary " */
};

/*
 * The structure reflects struct rusage in 64-bit mode
 * and is 64-bit size invariant.
 */
struct	trusage64
{
	struct timeval64 ru_utime;	/* user time used */
	struct timeval64 ru_stime;	/* system time used */
	longlong_t	 ru_maxrss;
	longlong_t	 ru_ixrss;	/* integral shared memory size */
	longlong_t	 ru_idrss;	/* integral unshared data " */
	longlong_t	 ru_isrss;	/* integral unshared stack " */
	longlong_t	 ru_minflt;	/* page reclaims */
	longlong_t	 ru_majflt;	/* page faults */
	longlong_t	 ru_nswap;	/* swaps */
	longlong_t	 ru_inblock;	/* block input operations */
	longlong_t	 ru_oublock;	/* block output operations */
	longlong_t	 ru_msgsnd;	/* messages sent */
	longlong_t	 ru_msgrcv;	/* messages received */
	longlong_t	 ru_nsignals;	/* signals received */
	longlong_t	 ru_nvcsw;	/* voluntary context switches */
	longlong_t	 ru_nivcsw;	/* involuntary " */
};

/*
 * The structure reflects struct rusage in 32-bit mode
 * and is 32-bit size invariant.
 */
struct trusage32
{
        struct timeval32 ru_utime;      /* user time used */
        struct timeval32 ru_stime;      /* system time used */
        signed int      ru_maxrss;
        signed int      ru_ixrss;       /* integral shared memory size */
        signed int      ru_idrss;       /* integral unshared data " */
        signed int      ru_isrss;       /* integral unshared stack " */
        signed int      ru_minflt;      /* page reclaims */
        signed int      ru_majflt;      /* page faults */
        signed int      ru_nswap;       /* swaps */
        signed int      ru_inblock;     /* block input operations */
        signed int      ru_oublock;     /* block output operations */
        signed int      ru_msgsnd;      /* messages sent */
        signed int      ru_msgrcv;      /* messages received */
        signed int      ru_nsignals;    /* signals received */
        signed int      ru_nvcsw;       /* voluntary context switches */
        signed int      ru_nivcsw;      /* involuntary " */
};

#define CP_RUSAGE(__tsrc, __tdest) {		\
        (__tdest)->ru_utime.tv_sec   	= (__tsrc)->ru_utime.tv_sec;  	\
        (__tdest)->ru_utime.tv_usec  	= (__tsrc)->ru_utime.tv_usec;  	\
        (__tdest)->ru_stime.tv_sec   	= (__tsrc)->ru_stime.tv_sec;  	\
        (__tdest)->ru_stime.tv_usec  	= (__tsrc)->ru_stime.tv_usec;  	\
        (__tdest)->ru_maxrss   		= (__tsrc)->ru_maxrss;  	\
        (__tdest)->ru_ixrss 		= (__tsrc)->ru_ixrss;  		\
        (__tdest)->ru_idrss 		= (__tsrc)->ru_idrss;  		\
        (__tdest)->ru_isrss 		= (__tsrc)->ru_isrss;  		\
        (__tdest)->ru_minflt 		= (__tsrc)->ru_minflt;  	\
        (__tdest)->ru_majflt 		= (__tsrc)->ru_majflt;  	\
        (__tdest)->ru_nswap 		= (__tsrc)->ru_nswap;  		\
        (__tdest)->ru_inblock 		= (__tsrc)->ru_inblock;  	\
        (__tdest)->ru_oublock 		= (__tsrc)->ru_oublock;  	\
        (__tdest)->ru_msgsnd 		= (__tsrc)->ru_msgsnd;  	\
        (__tdest)->ru_msgrcv 		= (__tsrc)->ru_msgrcv;  	\
        (__tdest)->ru_nsignals 		= (__tsrc)->ru_nsignals;  	\
        (__tdest)->ru_nvcsw 		= (__tsrc)->ru_nvcsw;  		\
        (__tdest)->ru_nivcsw 		= (__tsrc)->ru_nivcsw;		\
		}


#define RUSAGE_ADD(_dest, _src1, _src2)     \
        (_dest)->ru_minflt = (_src1)->ru_minflt + (_src2)->ru_minflt; \
        (_dest)->ru_majflt = (_src1)->ru_majflt + (_src2)->ru_majflt; \
        (_dest)->ru_nswap = (_src1)->ru_nswap + (_src2)->ru_nswap; \
        (_dest)->ru_nsignals = (_src1)->ru_nsignals + (_src2)->ru_nsignals; \
        (_dest)->ru_nvcsw = (_src1)->ru_nvcsw + (_src2)->ru_nvcsw; \
        (_dest)->ru_nivcsw = (_src1)->ru_nivcsw + (_src2)->ru_nivcsw; \

#define RUSAGE_SUB(_dest, _src1, _src2)     \
        (_dest)->ru_minflt = (_src1)->ru_minflt - (_src2)->ru_minflt; \
        (_dest)->ru_majflt = (_src1)->ru_majflt - (_src2)->ru_majflt; \
        (_dest)->ru_nswap = (_src1)->ru_nswap - (_src2)->ru_nswap; \
        (_dest)->ru_nsignals = (_src1)->ru_nsignals - (_src2)->ru_nsignals; \
        (_dest)->ru_nvcsw = (_src1)->ru_nvcsw - (_src2)->ru_nvcsw; \
        (_dest)->ru_nivcsw = (_src1)->ru_nivcsw - (_src2)->ru_nivcsw; \


#endif /* _ALL_SOURCE */

/*
 * Resource limits
 */
#define	RLIMIT_CPU	0		/* cpu time in milliseconds */
#define	RLIMIT_FSIZE	1		/* maximum file size */
#define	RLIMIT_DATA	2		/* data size */
#define	RLIMIT_STACK	3		/* stack size */
#define	RLIMIT_CORE	4		/* core file size */
#define	RLIMIT_RSS	5		/* resident set size */

#define RLIMIT_AS	6		/* max size proc's total memory--not enforced */
#define RLIMIT_NOFILE   7		/* max # allocated fds--not enforced */

#ifdef _NO_PROTO
extern int getpriority();
extern int getrusage();
extern int setpriority();
extern int getrlimit();
extern int setrlimit();

#if (defined(_KERNEL) || (defined(_ALL_SOURCE) && defined(_LONG_LONG)))
extern int getrlimit64();
extern int setrlimit64();
#endif /* _KERNEL || (_ALL_SOURCE && _LONG_LONG) */

#else /* _NO_PROTO */

extern int getpriority(int, id_t);
extern int setpriority(int, id_t, int);
extern int getrlimit(int, struct rlimit *);
extern int setrlimit(int, const struct rlimit *);

#if (defined(_KERNEL) || (defined(_ALL_SOURCE) && defined(_LONG_LONG)))
extern int getrlimit64(int, struct rlimit64 *);
extern int setrlimit64(int, const struct rlimit64 *);
#endif /* _KERNEL || (_ALL_SOURCE && _LONG_LONG) */

#ifdef _KERNEL
extern void kgetrlimit64(int, struct rlimit64 *);
extern int getrusage(int, struct rusage *);
extern int getrusage64(int, struct rusage64 *);
#else /* _KERNEL */
extern int getrusage(int, struct rusage *);
#if defined(_ALL_SOURCE) && defined(_LONG_LONG)
extern int getrusage64(int, struct rusage64 *);
#endif /* _ALL_SOURCE */
#endif /* _KERNEL_ */

#ifdef _KERNSYS
extern int	xsetrlimit(int, struct rlimit64 *, int);
extern void	set_64bit_rlimit(int, struct rlimit64 *, int, int);
extern rlim64_t kget_fsblimit64(void);
extern rlim64_t get_64bit_rlimit(int, int);
struct user;
extern rlim64_t get_64bit_rlimit_u(int, int, struct user *);
#endif /* _KERNSYS */

#endif /* _NO_PROTO */

#endif /* _XOPEN_SOURCE_EXTENDED */

/*
 * Function prototypes for 64bit kernel only
 */
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
extern offset_t        getfslimit(void);
#endif /* __64BIT_KERNEL || __FULL_PROTO */

#ifdef __cplusplus
}
#endif

#endif /* _H_RESOURCE */
