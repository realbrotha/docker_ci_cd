/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/ccs/lib/libthread/thread.h 1.2                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2002               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)67        1.2  src/bos/usr/ccs/lib/libthread/thread.h, libth, bos530 10/2/02 13:40:18 */
/* Copyright (C) 1995 Sun Microsystems, Inc.                              */
/* Copyright (C) 1994 Sun Microsystems, Inc.                              */

#ifndef	_THREAD_H_
#define	_THREAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <standards.h>

#include <pthread.h>

#define _THREAD_SAFE	  1

typedef pthread_t thread_t;

typedef pthread_key_t thread_key_t;

#ifdef _NO_PROTO
#define __(args)	()
#else /* _NO_PROTO */
#define __(args)	args
#endif /* _NO_PROTO */

extern int 
thr_create __((void*, size_t, void *(*)(void *), 
	       void*, long, thread_t *));
extern int 
thr_getprio __((thread_t, int *));

extern int 
thr_setprio __((thread_t, int));

extern int 
thr_continue __((thread_t ));

extern int 
thr_join __((thread_t, thread_t *, void**));

extern int
thr_keycreate __((thread_key_t *, void (*) (void *)));

extern int 
thr_setspecific __((thread_key_t, void *));

extern int 
thr_getspecific __((thread_key_t, void**));

extern void 
thr_exit __((void *));

extern void 
thr_yield __((void));

extern thread_t 
thr_self __((void));

extern int 
thr_suspend __((thread_t ));

extern int 
thr_setconcurrency __((int ));

extern int
thr_getconcurrency __((void));

extern int
thr_kill __((thread_t, int));

extern int
thr_sigsetmask __((int, sigset_t*, sigset_t*));

#define THR_BOUND 1
#define THR_SUSPEND 2
#define THR_DETACHED 3
#define THR_DAEMON 4
#define THR_NEW_LWP 5

#ifdef __cplusplus
}
#endif

#endif /* _THREAD_H_ */
