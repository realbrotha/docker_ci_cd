/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/wait.h 1.25.1.13                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)32       1.25.1.13  src/bos/kernel/sys/wait.h, sysproc, bos530 3/20/03 04:31:09 */

/*
 * COMPONENT_NAME: SYSPROC 
 *
 * FUNCTIONS:
 *
 * ORIGINS: 3, 27 
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_WAIT
#define _H_WAIT

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#if _XOPEN_SOURCE_EXTENDED==1
#ifndef _H_RESOURCE
#include <sys/resource.h>  /* included for struct rusage */
#endif

#ifndef _H_SYS_SIGNAL
#include <sys/signal.h>	   /* included for siginfo_t */
#endif
#endif /* _XOPEN_SOURCE_EXTENDED */


/*
 * This file holds definitions relevent to the waitpid(), wait(), and wait3()
 * system calls.  The rusage option is only available with the wait3() call.
 * The options field in wait3() and waitpid() determines the behavior of the
 * call, while the process ID field in the waitpid() call determines which
 * group of children to search.
 */

/*
 * POSIX requires that certain values be included in wait.h.  It also
 * requires that when _POSIX_SOURCE is defined only those standard
 * specific values are present.  This header includes all the POSIX
 * required entries.
 */

#ifdef _POSIX_SOURCE

/*
 * The option field for wait3() and waitpid() is defined as follows:
 * WNOHANG causes the wait to not hang if there are no stopped or terminated
 * processes, rather returning an error indication in this case (pid==0).
 * WUNTRACED indicates that the caller should receive status about untraced
 * children which stop due to signals.  If children are stopped and a wait
 * without this option is done, it is as though they were still running...
 * nothing about them is returned.
 */
#define WNOHANG		0x1	/* dont hang in wait			 */
#define WUNTRACED	0x2	/* tell about stopped, untraced children */

/*
 * Stopped process status.  Returned only for traced children unless requested
 * with the WUNTRACED option bit.  Lower byte gives the reason, next byte is
 * the last signal received, i.e. p->p_cursig.
 */
#define	_W_STOPPED	0x00000040	/* bit set if stopped		*/

/*
 * The following stop values are set when a process stops while traced.
 * The _W_STOPPED bit must be included in all these values.
 */
#define	_W_SLWTED	0x0000007c	/* value if stopped after load	*/
#define	_W_SEWTED	0x0000007d	/* value if stopped after exec	*/
#define	_W_SFWTED	0x0000007e	/* value if stopped after fork	*/
#define	_W_STRC		0x0000007f	/* value if stopped after trace	*/

/*
 * MACRO defines for application interfacing to waitpid(), wait(), and wait3()
 *
 * WIFSTOPPED  - returns non-zero if status returned for a stopped child
 * WSTOPSIG    - returns signal that caused child to stop
 * WIFEXITED   - returns non-zero if normal termination
 * WEXITSTATUS - returns low-order 8 bits of child exit status
 * WIFSIGNALED - returns non-zero if abnormal termination
 * WTERMSIG    - returns signal that caused child to terminate
 */
#define	WIFSTOPPED(__x)	 ((__x) & _W_STOPPED)
#define	WSTOPSIG(__x)	 (int)(WIFSTOPPED(__x) ? ((((unsigned int)__x) >> 8) & 0xff) : -1)
#define	WIFEXITED(__x)	 (!((__x) & 0xff))
#define	WEXITSTATUS(__x) (int)(WIFEXITED(__x) ? ((((unsigned int)__x) >> 8) & 0xff) : -1)
#define	WIFSIGNALED(__x) (!WIFEXITED(__x) && !WIFSTOPPED(__x))
#define	WTERMSIG(__x)	 (int)(WIFSIGNALED(__x) ? ((((unsigned int)__x) >> 16) & 0xff) : -1)

#if _XOPEN_SOURCE_EXTENDED==1

#define WEXITED		  0x04
#define WSTOPPED	  _W_STOPPED
#define	_W_OCONTINUED	  0x00000008	/* compatibility bit set if continued */

#define WCONTINUED	  0x01000000
#define WNOWAIT		  0x10

/* evaluates to non-zero if status was returned for a continued child */
#define WIFCONTINUED(__x) ((__x) & WCONTINUED)

#ifdef WIFSIGNALED
#undef WIFSIGNALED
#endif
#define	WIFSIGNALED(__x) (!WIFEXITED(__x) && !WIFSTOPPED(__x) && !WIFCONTINUED(__x))

/*
 * argument types for waitid
 */
typedef enum {P_ALL, P_PID, P_PGID} idtype_t;

#endif /* _XOPEN_SOURCE_EXTENDED */
#endif /* _POSIX_SOURCE */

#if defined(_ALL_SOURCE) && defined(_BSD)
#include <sys/m_wait.h>
#endif

#ifdef _POSIX_SOURCE
#ifndef _NONSTD_TYPES
#ifdef _NO_PROTO
extern pid_t wait();
extern pid_t waitpid();
#else
#if defined(_ALL_SOURCE) && defined(_BSD)
extern pid_t wait(union wait *);
#else
extern pid_t wait(int *);
#endif
extern pid_t waitpid(pid_t, int *, int);
#endif /* _NO_PROTO */
#endif /* _NONSTD_TYPES */
#endif /* _POSIX_SOURCE */

#if _XOPEN_SOURCE_EXTENDED==1

#ifndef	_NONSTD_TYPES
#ifdef _NO_PROTO
extern int waitid();
#if _XOPEN_SOURCE<600 || defined(_ALL_SOURCE)
extern pid_t wait3();
#endif
#else 
extern int waitid(idtype_t, id_t, siginfo_t *, int);
#if _XOPEN_SOURCE<600 || defined(_ALL_SOURCE)
#if defined(_ALL_SOURCE) && defined(_BSD)
extern pid_t wait3(union wait *, int, struct rusage *);
#else
extern pid_t wait3(int *, int, struct rusage *);
#endif 
#endif

#ifdef _ALL_SOURCE
extern pid_t kwaitpid(int *, pid_t, int, struct rusage *, siginfo_t *);
#if defined(_LONG_LONG)
extern pid_t kwaitpid64(int *, pid_t, int, struct rusage64 *, siginfo_t *);
#ifdef _BSD
extern pid_t wait364(union wait *, int, struct rusage64 *);
#else
extern pid_t wait364(int *, int, struct rusage64 *);
#endif /* BSD */
#endif /* _LONG_LONG */
#endif /* _ALL_SOURCE */

#endif /* _NO_PROTO */
#endif /* _NONSTD_TYPES */

#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef	_ALL_SOURCE
#ifdef	_NO_PROTO
extern pid_t wait4();
#else	/* _NO_PROTO */
extern pid_t wait4(pid_t, int *, int, struct rusage *);
#endif	/* _NO_PROTO */
#endif	/* _ALL_SOURCE */

#ifdef _ALL_SOURCE
#define	W_STOPPED	_W_STOPPED
#define	W_SLWTED 	_W_SLWTED
#define	W_SEWTED 	_W_SEWTED
#define	W_SFWTED 	_W_SFWTED
#define	W_STRC    	_W_STRC

/* define for BSD compatibility					*/

#ifndef WSTOPPED
#define	WSTOPPED	_W_STOPPED
#endif /* WSTOPPED */

#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif
#endif /* _H_WAIT */
