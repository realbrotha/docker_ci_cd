/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/lib_lock.h 1.18                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1992,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)01	1.18  src/bos/usr/include/lib_lock.h, libcthrd, bos530 4/27/04 10:58:03 */
/*
 *   COMPONENT_NAME: LIBCTHRD
 *
 *   FUNCTIONS: LIB_LOCK_FUNCTION
 *		LIB_LOCK_FUNCTION_TRYLOCK
 *		lib_mutex_create
 *		lib_mutex_delete
 *		lib_mutex_lock
 *		lib_mutex_trylock
 *		lib_mutex_unlock
 *		lib_spinlock_create
 *		lib_spinlock_delete
 *		lib_spinlock_lock
 *		lib_spinlock_trylock
 *		lib_spinlock_unlock
 *		lib_thread_id
 *
 *   ORIGINS: 27,71
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1992,1994
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 */
/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/* lib_lock.h,v $ $Revision: 1.4 $ (OSF) */

/*
 * Library locking functions provided by a threads package usable by a library
 */

#include <sys/time.h>
#include <sys/types.h>
#include <sys/context.h>	/* mcontext_t */
#include <sys/signal.h>		/* siginfo_t */

#ifndef _LIB_LOCK_H_
#define _LIB_LOCK_H_

struct sched_param;
typedef	void	*lib_mutex_t;
typedef	void	*lib_spinlock_t;
typedef void	*lib_threadid_t;
typedef void	*lib_rwlock_t;

typedef	int		(*lib_mutex_func_t)(lib_mutex_t *);
typedef	int		(*lib_spinlock_func_t)(lib_spinlock_t *);
typedef	lib_threadid_t	(*lib_threadid_func_t)(void);
typedef void		(*lib_cleanup_push_t)(void (*)(), void *);	
typedef void		(*lib_cleanup_pop_t)(int);	
typedef	int		(*lib_atfork_t)(void (*)(void), void (*)(void), void(*)(void));
typedef	int		(*lib_atfork_np_t)(void *, void (*)(void), void (*)(void), void(*)(void));
typedef	int		(*lib_atfork_unregister_t)(void *, void (*)(void), void (*)(void), void(*)(void), int);
typedef	void		(*lib_thread_exit_t)(void *);
typedef void *		(*lib_getspecific_t)(unsigned int);
typedef int		(*lib_setspecific_t)(unsigned int, const void *);
typedef int		(*lib_key_create_t)(unsigned int *, void (*)(void *));
typedef int		(*lib_key_delete_t)(unsigned int);
typedef int		(*lib_once_t)(void *, void (*)(void));
typedef	int		(*lib_nsleep_t)(struct timestruc_t *, struct timestruc_t *);
typedef	int		(*lib_pause_t)(void);
typedef	int		(*lib_raise_t)(int);
typedef int		(*lib_sigaction_t)(int, struct sigaction *, struct sigaction *);
typedef	int		(*lib_sigpending_t)(sigset_t *);
typedef	int		(*lib_sigsuspend_t)(sigset_t *);
typedef	int		(*lib_sigtimedwait_t)(const sigset_t *,
					siginfo_t *, const struct timespec *);
typedef int		(*lib_create_notification_t)(struct sigevent *,
					pthread_t *, tid_t *);
typedef int		(*lib_cancel_notification_t)(pthread_t);
typedef	int		(*lib_yield_t)(void);
typedef int		(*lib_equal_t)(pthread_t, pthread_t);
typedef int		(*lib_setcancelstate_t)(int, int *);
typedef int		(*lib_create_t)(pthread_t *, pthread_attr_t *, void*(*)(void *), void *);
typedef int		(*lib_join_t)(pthread_t, void **);
typedef void		(*lib_testcancel_t)(void);
typedef int		(*lib_setcanceltype_t)(int, int *);
typedef int		(*lib_cancel_t)(pthread_t);
typedef int		(*lib_detach_t)(pthread_t);
typedef int		(*lib_mutex_init_t)(pthread_mutex_t **, pthread_mutexattr_t *);
typedef int		(*lib_cond_init_t)(pthread_cond_t *, pthread_condattr_t *);
typedef int		(*lib_cond_destroy_t)(pthread_cond_t *);
typedef int		(*lib_cond_wait_t)(pthread_cond_t *, pthread_mutex_t *);
typedef int		(*lib_cond_broadcast_t)(pthread_cond_t *);
typedef int		(*lib_cond_signal_t)(pthread_cond_t *);
typedef int		(*lib_chkpnt_t)(char *, id_t, unsigned int, void *, char *);
typedef int		(*lib_chkpnt_commit_t)(unsigned int, void *, void *, void *);
typedef int		(*lib_chkpnt_fail_t)(void *);
typedef int		(*lib_chkpnt_register_t)(void *, void *);
typedef int		(*lib_attr_init_t)(pthread_attr_t *);
typedef int		(*lib_attr_destroy_t)(pthread_attr_t *);
typedef int		(*lib_attr_setdetachstate_t)(pthread_attr_t *, int);
typedef int		(*lib_attr_setstacksize_t)(pthread_attr_t *, size_t);
typedef int		(*lib_attr_setinheritsched_t)(pthread_attr_t *, int);
typedef int		(*lib_attr_getinheritsched_t)(pthread_attr_t *, int *);
typedef int		(*lib_attr_setschedparam_t)(pthread_attr_t *, struct sched_param *);
typedef int		(*lib_attr_getschedparam_t)(pthread_attr_t *, struct sched_param *);
typedef int		(*lib_attr_setscope_t)(pthread_attr_t *, int);
typedef int		(*lib_attr_getscope_t)(pthread_attr_t *, int *);
typedef int		(*lib_suspend_others_t)(void);
typedef int		(*lib_continue_others_t)(void);
typedef int		(*lib_getsigcontext_t)(uint *, pthread_t *, uint *, uint *, mcontext_t *);
typedef int 	(*lib_rwlock_func_t)(pthread_rwlock_t *);
typedef int     (*lib_rwlock_init_t)(lib_rwlock_t *);
typedef void    	(*lib_pth_monstartup)(void);
typedef int		(*lib_tct_clock_getset_t)(clockid_t, struct timestruc_t *, int);

typedef struct lib_lock_functions {
	lib_mutex_func_t	mutex_create;
	lib_mutex_func_t	mutex_delete;
	lib_mutex_func_t	mutex_lock;
	lib_mutex_func_t	mutex_unlock;
	lib_mutex_func_t	mutex_trylock;
	lib_spinlock_func_t	spinlock_create;
	lib_spinlock_func_t	spinlock_delete;
	lib_spinlock_func_t	spinlock_lock;
	lib_spinlock_func_t	spinlock_unlock;
	lib_spinlock_func_t	spinlock_trylock;
	lib_threadid_func_t	thread_id;
	lib_cleanup_push_t	cleanup_push;
	lib_cleanup_pop_t	cleanup_pop;
	lib_atfork_t		atfork;
	lib_thread_exit_t	thread_exit;
	lib_getspecific_t	getspecific;
	lib_setspecific_t	setspecific;
	lib_key_create_t	key_create;
	lib_key_delete_t	key_delete;
	lib_once_t		once;
	lib_nsleep_t		nsleep;
	lib_pause_t		pause;
	lib_raise_t		raise;
	lib_sigaction_t		sigaction;
	lib_sigpending_t	sigpending;
	lib_sigsuspend_t	sigsuspend;
	lib_yield_t		yield;
	lib_equal_t		equal;
	lib_setcancelstate_t	setcancelstate;
	lib_create_t		create;
	lib_join_t		join;
        lib_testcancel_t	testcancel;
	lib_setcanceltype_t	setcanceltype;
	lib_cancel_t		cancel;
	lib_detach_t		detach;
	lib_mutex_init_t	mutex_init;
	lib_cond_init_t		cond_init;
	lib_cond_destroy_t	cond_destroy;
	lib_cond_wait_t		cond_wait;
	lib_cond_broadcast_t	cond_broadcast;
	lib_cond_signal_t	cond_signal;
	lib_chkpnt_t		chkpnt;
	lib_chkpnt_commit_t	chkpnt_commit;
	lib_chkpnt_fail_t	chkpnt_fail;
	lib_chkpnt_register_t	chkpnt_register;
	lib_attr_init_t		attr_init;
	lib_attr_destroy_t	attr_destroy;
	lib_attr_setdetachstate_t	attr_setdetachstate;
	lib_attr_setstacksize_t	attr_setstacksize;
	lib_attr_setinheritsched_t	attr_setinheritsched;
	lib_attr_getinheritsched_t	attr_getinheritsched;
	lib_attr_setschedparam_t	attr_setschedparam;
	lib_attr_getschedparam_t	attr_getschedparam;
	lib_attr_setscope_t	attr_setscope;
	lib_attr_getscope_t	attr_getscope;
	lib_suspend_others_t	suspend_others;
	lib_continue_others_t	continue_others;
	lib_getsigcontext_t	getsigcontext;
	lib_atfork_np_t		atfork_np;
	lib_atfork_unregister_t	atfork_unregister_np;
	lib_sigtimedwait_t	sigtimedwait;
	lib_create_notification_t create_notification_thread;
	lib_cancel_notification_t cancel_notification_thread;
	lib_rwlock_init_t	rwlock_init;
	lib_rwlock_init_t	rwlock_destroy;
	lib_rwlock_func_t	rwlock_wrlock;
	lib_rwlock_func_t	rwlock_trywrlock;
	lib_rwlock_func_t	rwlock_rdlock;
	lib_rwlock_func_t	rwlock_tryrdlock;
	lib_rwlock_func_t   rwlock_unlock;
	lib_pth_monstartup      pth_monstartup;
	lib_tct_clock_getset_t	tct_clock_getset;

} lib_lock_functions_t;

#ifndef ESUCCESS
#define ESUCCESS	0
#endif

#ifndef NO_THREAD
#define NO_THREAD	(lib_threadid_t)0
#endif

/*
 * One argument
 */
#define	LIB_LOCK_FUNCTION(lockstruct, operation, arg) \
	((lockstruct).operation ? (*(lockstruct).operation)(arg) : ESUCCESS)
/*
 * Zero arguments
 */
#define	LIB_LOCK_FUNCTION0(lockstruct, operation) \
	((lockstruct).operation ? (*(lockstruct).operation)() : ESUCCESS)

/*
 * Two arguments
 */
#define	LIB_LOCK_FUNCTION2(lockstruct, operation, arg1, arg2) \
	((lockstruct).operation ? (*(lockstruct).operation)(arg1, arg2) : ESUCCESS)
/*
 * Three arguments
 */
#define	LIB_LOCK_FUNCTION3(lockstruct, operation, arg1, arg2, arg3) \
	((lockstruct).operation ? (*(lockstruct).operation)(arg1, arg2, arg3) : ESUCCESS)

/*
 * Four arguments
 */
#define	LIB_LOCK_FUNCTION4(lockstruct, operation, arg1, arg2, arg3, arg4) \
	((lockstruct).operation ? (*(lockstruct).operation)(arg1, arg2, arg3, arg4) \
                                : ESUCCESS)

/*
 * Five arguments
 */
#define	LIB_LOCK_FUNCTION5(lockstruct, operation, arg1, arg2, arg3, arg4, arg5) \
	((lockstruct).operation ? (*(lockstruct).operation)(arg1, arg2, arg3, arg4, arg5) \
                                : ESUCCESS)

/**********
special case for trylock. if the operations does 
not exist, then return 1
**********/
#define	LIB_LOCK_FUNCTION_TRYLOCK(lockstruct, operation, arg) \
	((lockstruct).operation ? (*(lockstruct).operation)(arg) : 1)


#define lib_mutex_create(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, mutex_create, lock)

#define lib_mutex_delete(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, mutex_delete, lock)

#define lib_mutex_lock(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, mutex_lock, lock)

#define lib_mutex_unlock(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, mutex_unlock, lock)

#define lib_mutex_trylock(lockstruct, lock) \
		LIB_LOCK_FUNCTION_TRYLOCK(lockstruct, mutex_trylock, lock)

#define lib_spinlock_create(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, spinlock_create, lock)

#define lib_spinlock_delete(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, spinlock_delete, lock)

#define lib_spinlock_lock(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, spinlock_lock, lock)

#define lib_spinlock_unlock(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, spinlock_unlock, lock)

#define lib_spinlock_trylock(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, spinlock_trylock, lock)

#define lib_rwlock_init(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, rwlock_init, lock) 

#define lib_rwlock_destroy(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, rwlock_destroy, lock)

#define lib_rwlock_wrlock(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, rwlock_wrlock, lock)

#define lib_rwlock_trywrlock(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, rwlock_trywrlock, lock)

#define lib_rwlock_rdlock(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, rwlock_rdlock, lock)

#define lib_rwlock_tryrdlock(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, rwlock_tryrdlock, lock)

#define lib_rwlock_unlock(lockstruct, lock) \
		LIB_LOCK_FUNCTION(lockstruct, rwlock_unlock, lock)

#define lib_thread_id(lockstruct) \
	((lockstruct).thread_id ? (*(lockstruct).thread_id)() : 0)

#define lib_cleanup_push(lockstruct, _function, lock) \
	if ((lockstruct).cleanup_push) { (*(lockstruct).cleanup_push)(_function, lock); }

#define lib_cleanup_pop(lockstruct, _flag) \
	if ((lockstruct).cleanup_pop) { (*(lockstruct).cleanup_pop)(_flag); }

#define lib_atfork(lockstruct, arg1, arg2, arg3) \
         LIB_LOCK_FUNCTION3(lockstruct, atfork, arg1, arg2, arg3)

#define lib_atfork_np(lockstruct, arg1, arg2, arg3 ,arg4) \
         LIB_LOCK_FUNCTION4(lockstruct, atfork, arg1, arg2, arg3, arg4)

#define lib_atfork_unregister_np(lockstruct, arg1, arg2, arg3, arg4, arg5) \
         LIB_LOCK_FUNCTION5(lockstruct, atfork_unregister_np, arg1, arg2, \
                 arg3, arg4, arg5)

#define lib_thread_exit(lockstruct, arg1) \
	if((lockstruct).thread_exit) (*(lockstruct).thread_exit)(arg1)

#define lib_getspecific(lockstruct, arg1) \
         LIB_LOCK_FUNCTION(lockstruct, getspecific, arg1)

#define lib_setspecific(lockstruct, arg1, arg2) \
         LIB_LOCK_FUNCTION2(lockstruct, setspecific, arg1, arg2)

#define lib_key_create(lockstruct, arg1, arg2) \
         LIB_LOCK_FUNCTION2(lockstruct, key_create, arg1, arg2)

#define lib_key_delete(lockstruct, arg1) \
         LIB_LOCK_FUNCTION(lockstruct, key_delete, arg1)

#define lib_once(lockstruct, arg1, arg2) \
         LIB_LOCK_FUNCTION2(lockstruct, once, arg1, arg2)

#define lib_nsleep(lockstruct, arg1, arg2) \
         LIB_LOCK_FUNCTION2(lockstruct, nsleep, arg1, arg2)

#define lib_pause(lockstruct) \
         LIB_LOCK_FUNCTION0(lockstruct, pause)

#define lib_raise(lockstruct, arg1) \
         LIB_LOCK_FUNCTION(lockstruct, raise, arg1)

#define lib_sigaction(lockstruct, arg1, arg2, arg3) \
         LIB_LOCK_FUNCTION3(lockstruct, sigaction, arg1, arg2, arg3)

#define lib_sigpending(lockstruct, arg1) \
         LIB_LOCK_FUNCTION(lockstruct, sigpending, arg1)

#define lib_sigsuspend(lockstruct, arg1) \
         LIB_LOCK_FUNCTION(lockstruct, sigsuspend, arg1)

#define lib_sigtimedwait(lockstruct, arg1, arg2, arg3) \
         LIB_LOCK_FUNCTION3(lockstruct, sigtimedwait, arg1, arg2, arg3)

#define lib_create_notification_thread(lockstruct, arg1, arg2, arg3) \
         LIB_LOCK_FUNCTION3(lockstruct, lib_create_notification_thread, \
							arg1, arg2, arg3)

#define lib_cancel_notification_thread(lockstruct, arg1) \
         LIB_LOCK_FUNCTION(lockstruct, lib_cancel_notification_thread, arg1)

#define lib_yield(lockstruct) \
         LIB_LOCK_FUNCTION0(lockstruct, yield)

#define lib_equal(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, equal, arg1, arg2)

#define lib_setcancelstate(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, setcancelstate, arg1, arg2)

#define lib_create(lockstruct, arg1, arg2, arg3, arg4) \
	LIB_LOCK_FUNCTION4(lockstruct, create, arg1, arg2, arg3, arg4)

#define lib_join(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, join, arg1, arg2)

#define lib_testcancel(lockstruct) \
	((lockstruct).testcancel ? (*(lockstruct).testcancel)() : (void)0)

#define lib_setcanceltype(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, setcanceltype, arg1, arg2)

#define lib_cancel(lockstruct, arg1) \
	LIB_LOCK_FUNCTION(lockstruct, cancel, arg1)

#define lib_detach(lockstruct, arg1) \
	LIB_LOCK_FUNCTION(lockstruct, detach, arg1)

#define lib_mutex_init(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, mutex_init, arg1, arg2)

#define lib_cond_init(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, cond_init, arg1, arg2)

#define lib_cond_destroy(lockstruct, arg1) \
	LIB_LOCK_FUNCTION(lockstruct, cond_destroy, arg1)

#define lib_cond_wait(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, cond_wait, arg1, arg2)

#define lib_cond_broadcast(lockstruct, arg1) \
	LIB_LOCK_FUNCTION(lockstruct, cond_broadcast, arg1)

#define lib_cond_signal(lockstruct, arg1) \
	LIB_LOCK_FUNCTION(lockstruct, cond_signal, arg1)
	
#define lib_chkpnt(lockstruct, arg1, arg2, arg3, arg4) \
	LIB_LOCK_FUNCTION4(lockstruct, chkpnt, arg1, arg2, arg3, arg4)

#define lib_chkpnt_commit(lockstruct, arg1, arg2, arg3, arg4) \
	LIB_LOCK_FUNCTION4(lockstruct, chkpnt_commit, arg1, arg2, arg3, arg4)

#define lib_chkpnt_fail(lockstruct, arg1) \
	LIB_LOCK_FUNCTION(lockstruct, chkpnt_fail, arg1)
	
#define lib_chkpnt_register(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, chkpnt_register, arg1, arg2)
	
#define lib_attr_init(lockstruct, arg1) \
	LIB_LOCK_FUNCTION(lockstruct, attr_init, arg1)

#define lib_attr_destroy(lockstruct, arg1) \
	LIB_LOCK_FUNCTION(lockstruct, attr_destroy, arg1)

#define lib_attr_setdetachstate(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, attr_setdetachstate, arg1, arg2)

#define lib_attr_setstacksize(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, attr_setstacksize, arg1, arg2)

#define lib_attr_setinheritsched(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, attr_setinheritsched, arg1, arg2)
	
#define lib_attr_getinheritsched(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, attr_getinheritsched, arg1, arg2)
	
#define lib_attr_setschedparam(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, attr_setschedparam, arg1, arg2)

#define lib_attr_getschedparam(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, attr_setschedparam, arg1, arg2)

#define lib_attr_setscope(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, attr_setscope, arg1, arg2)
	
#define lib_attr_getscope(lockstruct, arg1, arg2) \
	LIB_LOCK_FUNCTION2(lockstruct, attr_getscope, arg1, arg2)
	
#define lib_suspend_others(lockstruct) \
	((lockstruct).suspend_others ? (*(lockstruct).suspend_others)() : 0)

#define lib_continue_others(lockstruct) \
	((lockstruct).continue_others ? (*(lockstruct).continue_others)() : 0)

#define lib_getsigcontext(lockstruct, arg1, arg2, arg3, arg4, arg5) \
	((lockstruct).getsigcontext ? (*(lockstruct).getsigcontext)(arg1, arg2, arg3, arg4, arg5) : -1 /* internal error */)

#endif /* _LIB_LOCK_H_ */

