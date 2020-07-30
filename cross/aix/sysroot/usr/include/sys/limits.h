/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/limits.h 1.103.3.1                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)85     1.103.3.1  src/bos/kernel/sys/limits.h, incstd, bos53L, l2007_17A6 4/13/07 16:47:53 */
/*
 * COMPONENT_NAME: (INCSTD) Standard Include Files
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_LIMITS
#define _H_LIMITS

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _H_STANDARDS
#include <standards.h>
#endif

/*
 *
 *      The ANSI and POSIX standards require that certain values be in limits.h.
 *      They also require that if _ANSI_C_SOURCE or _POSIX_SOURCE is
 *      defined then ONLY those standard specific values are present.
 *      This header includes all the ANSI and POSIX required entries.
 *      In addition other entries for the AIX system are included.
 *
 */
#ifdef _ANSI_C_SOURCE

/*  C LANGUAGE LIMITS */
#define	CHAR_BIT	(8)

#if defined(__ia64) && !defined(_CHAR_UNSIGNED)
#define CHAR_MAX	127
#define CHAR_MIN	(-128)
#else
#define CHAR_MAX	UCHAR_MAX
#define CHAR_MIN	(0)
#endif /* __ia64 && !_CHAR_UNSIGNED */

#define INT_MAX		(2147483647)
#define	INT_MIN		(-INT_MAX - 1)
#ifdef __64BIT__
#define LONG_MAX     (9223372036854775807L)
#define LONG_MIN     (-LONG_MAX - 1)
#define ULONG_MAX    (18446744073709551615UL)
#else /* __64BIT__ */
#define LONG_MAX	(2147483647L)
#define LONG_MIN	(-LONG_MAX - 1)
#define ULONG_MAX	(4294967295UL)
#endif /* __64BIT__ */

#ifdef _ISOC99_SOURCE
#if defined(_LONG_LONG) || defined(__64BIT__)
#define LLONG_MAX	(9223372036854775807LL)
#define LLONG_MIN	(-9223372036854775807LL -1LL)
#define ULLONG_MAX	(18446744073709551615ULL)
#else
#define LLONG_MAX       LONG_MAX
#define LLONG_MIN       LONG_MIN
#define ULLONG_MAX      ULONG_MAX
#endif
#endif /* _ISOC99_SOURCE */

#define SCHAR_MAX	(127)
#define SCHAR_MIN	(-SCHAR_MAX - 1)
#define SHRT_MAX	(32767)
#define SHRT_MIN	(-SHRT_MAX - 1)
#define UCHAR_MAX	(255)
#define UINT_MAX	(4294967295U)
#define USHRT_MAX	(65535)

#define	MB_LEN_MAX	4 		/* maximum bytes in multibyte char */

#endif /* _ANSI_C_SOURCE */

#ifdef _POSIX_SOURCE

/*
 *   The following are values that have historically been in limits.h.
 *
 *   They are a part of the POSIX defined limits.h and therefore are
 *   included when _POSIX_SOURCE is defined.
 *
 */

/* limits on a system conforming to the POSIX standard */

#define _POSIX_ARG_MAX			4096
#define _POSIX_CHILD_MAX		25
#define _POSIX_HOST_NAME_MAX		255
#define _POSIX_SYMLINK_MAX		255
#define _POSIX_SYMLOOP_MAX		8
#define _POSIX_LINK_MAX			8
#define _POSIX_MAX_CANON		255
#define _POSIX_NAME_MAX			14
#define _POSIX_NGROUPS_MAX		8
#define _POSIX_MAX_INPUT		255
#define _POSIX_OPEN_MAX			20
#define _POSIX_PATH_MAX			256
#define _POSIX_PIPE_BUF			512
#define _POSIX_SSIZE_MAX		32767
#define _POSIX_STREAM_MAX		8
#define _POSIX_THREAD_KEYS_MAX		128
#if defined(_ALL_SOURCE)
#define _POSIX_THREAD_DATAKEYS_MAX	_POSIX_THREAD_KEYS_MAX
#endif
#define _POSIX_THREAD_THREADS_MAX	64
#define _POSIX_TZNAME_MAX		6
#define _POSIX_LOGIN_NAME_MAX		9
#define _POSIX_TTY_NAME_MAX		9
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS  4
#define	_POSIX_CLOCKRES_MIN		20000000
#define	_POSIX_AIO_LISTIO_MAX		2
#define _POSIX_AIO_MAX			1
#define	_POSIX_DELAYTIMER_MAX		32
#define	_POSIX_MQ_OPEN_MAX		8
#define	_POSIX_MQ_PRIO_MAX		32
#define _POSIX_RTSIG_MAX		8
#define	_POSIX_SEM_NSEMS_MAX		256
#define _POSIX_SEM_VALUE_MAX		32767
#define	_POSIX_SIGQUEUE_MAX		32
#define	_POSIX_TIMER_MAX		32

/* The system supports the following utility limit minimum values */

#define _POSIX2_BC_BASE_MAX	99   /* max ibase and obase values for bc     */
#define _POSIX2_BC_DIM_MAX	2048 /* max num elements in array for bc      */
#define _POSIX2_BC_SCALE_MAX	99   /* max scale value allowed by bc         */
#define _POSIX2_BC_STRING_MAX	1000 /* max len of string constant by bc      */
#define _POSIX2_EQUIV_CLASS_MAX	2    /* this define is obsolete               */
#define _POSIX2_COLL_WEIGHTS_MAX 2   /* max num weight for LC_COLLATE order   */
#define _POSIX2_EXPR_NEST_MAX	32   /* max num expression nested for expr    */
#define _POSIX2_LINE_MAX	2048 /* max len of utility input line         */
#define _POSIX2_RE_DUP_MAX	255  /* max num repeated reg for interval not */

#if (_POSIX_C_SOURCE >= 200112L)
#define _POSIX2_CHARCLASS_NAME_MAX 14
#endif

/* The system supports the following symbolic utility limits */

#define BC_BASE_MAX	  _POSIX2_BC_BASE_MAX
#define BC_DIM_MAX	  _POSIX2_BC_DIM_MAX
#define BC_SCALE_MAX	  _POSIX2_BC_SCALE_MAX
#define BC_STRING_MAX	  2048
#define EQUIV_CLASS_MAX	  4		/* EQUIV_CLASS_MAX is obsolete */
#define COLL_WEIGHTS_MAX  4
#define EXPR_NEST_MAX	  _POSIX2_EXPR_NEST_MAX
#define LINE_MAX  	  _POSIX2_LINE_MAX
#ifndef RE_DUP_MAX	  /* NLregexp.h */
#define RE_DUP_MAX	  _POSIX2_RE_DUP_MAX
#endif /* RE_DUP_MAX */

/* RUN-TIME INVARIANT VALUES
   The system supports the following fixed magnitude limitations.
*/
#define	MAX_INPUT	512		/* max bytes in terminal
					   input queue, >= 256+64 */

#define NGROUPS_MAX	128		/* max number of supplementary group IDs
					   per process, >= 0 */
#define SSIZE_MAX	LONG_MAX	/* largest value of ssize_t: LONG_MAX */
#define _SSIZE_MAX	LONG_MAX	/* largest value of ssize_t: LONG_MAX */

/* The following values will be undefined if the system supports a value that
   is equal or greater than the stated minimum AND the supported value is
   indeterminate (e.g. dependent on memory space).
   On AIX, this includes ARG_MAX and CHILD_MAX.  (But if _ALL_SOURCE is
   used, these are defined with their default values).
*/

#ifdef _ALL_SOURCE
/*
 * Max length of arguments for exec() in bytes, including environ data, >= 4096.
 */
#define	ARG_MAX		24576
#define	CHILD_MAX	128		/* maximum processes per uid */
#endif /* _ALL_SOURCE */

#define MAX_CANON	256		/* max bytes in a terminal canonical
					   input line, >= 256 */

#define	OPEN_MAX	65534	        /* max num of files per process */
#define STREAM_MAX	32767		/* This value MUST be the same as
					   FOPEN_MAX in stdio.h */

#define PTHREAD_KEYS_MAX 450 	      	/* MUST be the same as PTHREAD_KEYS_MAX
					   computed in pthread.h */
#ifdef _LARGE_THREADS
#define PTHREAD_THREADS_MAX 32767
#else
#define PTHREAD_THREADS_MAX 512         /* MUST be the same as
					   PTHREAD_THREADS_MAX in pthread.h */
#endif /* _LARGE_THREADS */

#ifdef _ALL_SOURCE
#define PTHREAD_DATAKEYS_MAX	PTHREAD_KEYS_MAX
#endif /* _ALL_SOURCE */
					
#define TZNAME_MAX	255

#define TTY_NAME_MAX	PATH_MAX	/* max len TTY name */

/* These are the runtime limit names for POSIX 1003.1c Realtime */
#define AIO_LISTIO_MAX		4096
#define AIO_MAX			4096
#define AIO_PRIO_DELTA_MAX	20
#define DELAYTIMER_MAX	_POSIX_DELAYTIMER_MAX
#define MQ_OPEN_MAX	        32768
#define MQ_PRIO_MAX	        128
#define RTSIG_MAX	_POSIX_RTSIG_MAX
#define SEM_NSEMS_MAX	        32768
#define SEM_VALUE_MAX	_POSIX_SEM_VALUE_MAX
#define SIGQUEUE_MAX	_POSIX_SIGQUEUE_MAX
#define TIMER_MAX	_POSIX_TIMER_MAX

/* PATH NAME VARIABLE VALUES */

/* The value of NAME_MAX must be retrieved by a call to the pathconf() or
 * fpathconf() functions.
 */

#undef	NAME_MAX			/* max bytes in a file name (not a
					   string length; does not include a
					   terminating null)  */

#if _POSIX_C_SOURCE >= 200112L && !(defined _ALL_SOURCE) || defined(_PATHMAX_HAS_NULL)	
#define	PATH_MAX	1024		/* max number of bytes in a pathname.
					   includes a terminating null */
#else
#define PATH_MAX	1023
#endif
	
/* RUN-TIME INCREASABLE VALUES
   The following values are the minimum supported by this system.  A specific
   instance of this system may support larger values.
*/
#define	LINK_MAX	SHRT_MAX	/* max of a file's ilink counts, >= 8 */

#define LOGIN_NAME_MAX	9		/* max login name inc. null */

#define	PIPE_BUF	32768		/* max number of bytes that is
					   guaranteed to be atomic when writing
					   to a pipe, >= 512	*/

#define HOST_NAME_MAX	256
#undef SYMLINK_MAX	/* must be retrieved by a call to (f)pathconf() */
#define SYMLOOP_MAX	20

#endif /* _POSIX_SOURCE */

#ifdef _XOPEN_SOURCE

/* Some of the value in <float.h> are required in limits.h by XPG3, but
   are not allowed by Posix.1.  The include must remain in _XOPEN_SOURCE.
*/
#ifdef _ALL_SOURCE

#ifndef _H_FLOAT
#include <float.h>	/* FLT_MAX, FLT_MIN, DBL_MAX, FLT_DIG, DBL_DIG */
#endif
			/* SFPMIN, SFPMAX, DFPMAX, DBL_MIN, DFPMIN */
#else

#ifndef DBL_DIG
#define DBL_DIG         15
#endif

#ifndef FLT_DIG
#define FLT_DIG         6
#endif

#ifndef DBL_MAX
#define DBL_MAX     1.7976931348623158e+308  /* max decimal value of a double */
#endif

#ifndef FLT_MAX
#define FLT_MAX     3.4028234663852886e+38F   /* max decimal value of a float */
#endif

#if (_XOPEN_SOURCE < 500)
#ifndef DBL_MIN
#define DBL_MIN     2.2250738585072014e-308
#endif

#ifndef FLT_MIN
#define FLT_MIN     1.1754943508222875e-38F   /* min decimal value of a float */
#endif
#endif /* _XOPEN_SOURCE < 500 */

#endif /* _ALL_SOURCE */

/* ANSI C requires TMP_MAX to be in stdio.h, however, XOPEN requires it to be
 * in limits.h.
 */

#ifndef TMP_MAX
#define TMP_MAX		16384		/* The number of unique names generated by the
					   tmpnam() function */
#endif /* TMP_MAX */

/* defines for message catalog usage */

#define NL_ARGMAX       9               /* max number of printf args */

#define NL_MSGMAX       65535           /* max number of messages per set */

#define NL_SETMAX       65535           /* max number of set per catalog */

#define NL_TEXTMAX      8192            /* max message length in bytes */

#define PASS_MAX	255		/* max number of bytes in a password
					   (not a string length; doesn't include
					   terminating null) */
#define NL_LANGMAX	14		/* max number of of bytes in a LANG name */

#define NL_NMAX 	10		/* max number of bytes in N-to-1 mapping
					   characters */

#ifndef NZERO
#define NZERO		20		/* default process priority */
#endif /* NZERO */

#ifdef __64BIT__
#define LONG_BIT	64		/* number of bits in a long     */
#else
#define LONG_BIT	32		/* number of bits in a long     */
#endif
#define WORD_BIT	32		/* number of bits in a "word" or int */

#define CHARCLASS_NAME_MAX	14	/* Maximum # of bytes in a character
					   class name */
#if _XOPEN_SOURCE_EXTENDED==1
#define ATEXIT_MAX	2048		/* max num of registered functions for
					   atexit() function, also defined
					   in stdlib.h */
#define _XOPEN_IOV_MAX		16	/* Maximum number of iov's on readv() */
					/* or writev()			      */
#ifndef IOV_MAX				/* Also Defined in sys/uio.h	      */
#define IOV_MAX		_XOPEN_IOV_MAX
#endif /* IOV_MAX */

#define PAGE_SIZE	4096		/* page size granularity of memory */
#ifndef PAGESIZE
#define PAGESIZE	PAGE_SIZE
#endif /* PAGESIZE */

#if _XOPEN_SOURCE>=500

#undef FILESIZEBITS		/* # bits needed to hold file offset,
				   undef means must get from pathconf() */
#ifndef PTHREAD_STACK_MIN
#ifdef _AIX_PTHREADS_D7
#define PTHREAD_STACK_MIN	( PAGESIZE * 24 ) /* Must be a multiple of 16k */
#else  /* _AIX_PTHREADS_D7 */
#ifdef __64BIT__
#define PTHREAD_STACK_MIN	( 2 * PAGESIZE * 2 )
#else  /* __64BIT__ */
#define PTHREAD_STACK_MIN	( PAGESIZE * 2 )
#endif /* __64BIT */
#endif /* _AIX_PTHREADS_D7 */
#endif /* PTHREAD_STACK_MIN */


#define PTHREAD_DESTRUCTOR_ITERATIONS _POSIX_THREAD_DESTRUCTOR_ITERATIONS
					/* # tries to destroy thread-
					   specific data values on exit */
#endif /* _XOPEN_SOURCE>=500 */

#endif /* _XOPEN_SOURCE_EXTENDED */

#if  (_XOPEN_SOURCE>=600)
#define _XOPEN_NAME_MAX  255
#define _XOPEN_PATH_MAX  1024
#endif

#endif /* _XOPEN_SOURCE */


#ifdef _ALL_SOURCE

/*  Asynchronous I/O limits.
 */
#define AIO_PRIO_DFL		1
#define AIO_PRIO_MAX		1
#define AIO_PRIO_MIN		1
#define AIO_LISTIO_MAX_SIZE	AIO_LISTIO_MAX

#define PID_MAX		INT_MAX		/* max value for a process ID,
					   >=30000	*/
#define UID_MAX		UINT_MAX	/* max value for a user or group ID */

#ifdef _LONG_LONG
/*
 * Support for 64-bit integers, called long long int and unsigned long long int
 * -(2**63)  =  -9,223,372,036,854,775,808
 * 2**63 - 1 =  +9,223,372,036,854,775,807
 * 2**64 - 1 = +18,446,744,073,709,551,616
 */

#define LONGLONG_MAX  (0x7fffffffffffffffLL)
#define LONGLONG_MIN  (-LONGLONG_MAX - 1)
#define ULONGLONG_MAX (0xffffffffffffffffuLL)

/*
 * File offset limits.
 */

/* DEV_OFF_MAX is not intended to be used by user applications */
#ifdef __64BIT_KERNEL
#define DEV_OFF_MAX LONGLONG_MAX
#else
#define	DEV_OFF_MAX	0xffffffffffLL	
#endif

#endif /* _LONG_LONG */

#define	OFF_MAX		0x7fffffff	/* Max size of a regular file 2^31 -1 */

#endif /*_ALL_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* _H_LIMITS */
