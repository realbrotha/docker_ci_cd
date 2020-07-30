/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/usr/ccs/lib/libthread/synch.h 1.4                       */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2002,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)23        1.4  src/bos/usr/ccs/lib/libthread/synch.h, libth, bos53J, j2006_16B9 4/18/06 03:48:50 */
/* Copyright (C) 1995 Sun Microsystems, Inc.                              */
/* Copyright (C) 1994 Sun Microsystems, Inc.                              */

#ifndef	_SYNCH_H_
#define	_SYNCH_H_

#ifdef __cplusplus
extern "C" {
#endif
  
#include <standards.h>
  
#include <pthread.h>
  
#define _THREAD_SAFE	  1
  
  typedef pthread_mutex_t mutex_t;
  typedef pthread_cond_t cond_t;
  typedef pthread_rwlock_t rwlock_t;
  typedef struct{
    pthread_mutex_t lock;
    pthread_cond_t waiters;
    #ifdef __64BIT__
	char pad[16];
    #else
	char pad[8];
    #endif
    int count;
  } sema_t;

#ifdef _NO_PROTO
#define __(args)	()
#else /* _NO_PROTO */
#define __(args)	args
#endif /* _NO_PROTO */
  
  extern int 
  mutex_init __((mutex_t *, int, void *));
  
  extern int 
  mutex_destroy __((mutex_t *));
  
  extern int 
  mutex_trylock __((mutex_t *));
  
  extern int 
  mutex_lock __((mutex_t *));
  
  extern int 
  mutex_unlock __((mutex_t *));

  extern int 
  cond_init __((cond_t *, int, void*));

  extern int 
  cond_destroy __((cond_t *));

  extern int 
  cond_wait __((cond_t *, mutex_t *));

  extern int
  cond_timedwait __((cond_t*, mutex_t*, struct timestruc_t*));

  extern int 
  cond_signal __((cond_t *));

  extern int 
  cond_broadcast __((cond_t *));

  extern int
  sema_init __((sema_t *, unsigned int, int, void *));

  extern int 
  sema_destroy __((sema_t *));

  extern int 
  sema_wait __((sema_t *));

  extern int 
  sema_trywait __((sema_t *));

  extern int
  sema_post __((sema_t *));

  extern int 
  rwlock_init __((rwlock_t *, int, void*));

  extern int 
  rwlock_destroy __((rwlock_t *));

  extern int 
  rw_rdlock __((rwlock_t *));

  extern int 
  rw_wrlock __((rwlock_t *));

  extern int 
  rw_unlock __((rwlock_t *));

  extern int 
  rw_tryrdlock __((rwlock_t *));
  
  extern int 
  rw_trywrlock __((rwlock_t *));



#define USYNC_PROCESS 1
#define USYNC_THREAD 2
  
#ifdef __cplusplus
}
#endif

#endif /* _SYNCH_H_ */
