/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/usr/include/spawn.h 1.2                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2004               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
#ifndef _H_SPAWN
#define _H_SPAWN

#include <standards.h>
#include <sys/types.h>
#include <signal.h>
#include <sched.h>

/* #include <spawn.h> */
/*******************************************/
/* Things that could be defined in spawn.h */
/*******************************************/
typedef struct
{
    short posix_attr_flags;
#define POSIX_SPAWN_SETPGROUP       0x1
#define POSIX_SPAWN_SETSIGMASK      0x2
#define POSIX_SPAWN_SETSIGDEF       0x4
#define POSIX_SPAWN_SETSCHEDULER    0x8
#define POSIX_SPAWN_SETSCHEDPARAM   0x10
#define POSIX_SPAWN_RESETIDS        0x20
#define POSIX_SPAWN_FORK_HANDLERS   0x1000
/* This flag is not part of POSIX specification.
 * It forces the call to fork instead of fast-fork in posix_spawn(p).
 * Default is fast fork (i.e. f_fork() routine).
 */
    pid_t posix_attr_pgroup;
    sigset_t posix_attr_sigmask;
    sigset_t posix_attr_sigdefault;
    int posix_attr_schedpolicy;
    struct sched_param posix_attr_schedparam;
}   posix_spawnattr_t;


typedef char *posix_spawn_file_actions_t;


int posix_spawn_file_actions_init(posix_spawn_file_actions_t *);
int posix_spawn_file_actions_destroy(posix_spawn_file_actions_t *);
int posix_spawn_file_actions_addclose(posix_spawn_file_actions_t *, int);
int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t *, int,int);
int posix_spawn_file_actions_addopen(posix_spawn_file_actions_t *__restrict__, 
				     int, const char *__restrict__, int, mode_t);
int posix_spawnattr_init(posix_spawnattr_t *);
int posix_spawnattr_destroy(posix_spawnattr_t *);
int posix_spawnattr_getflags(const posix_spawnattr_t *__restrict__, 
			     short *__restrict__);
int posix_spawnattr_setflags(posix_spawnattr_t *, short);
int posix_spawnattr_getpgroup(const posix_spawnattr_t *__restrict__, 
			      pid_t *__restrict__);
int posix_spawnattr_setpgroup(posix_spawnattr_t *, pid_t );
int posix_spawnattr_getschedpolicy(const posix_spawnattr_t *__restrict__, 
				   int *__restrict__);
int posix_spawnattr_setschedpolicy(posix_spawnattr_t *, int);
int posix_spawnattr_getschedparam(const posix_spawnattr_t *__restrict__, 
				  struct sched_param *__restrict__);
int posix_spawnattr_setschedparam(posix_spawnattr_t *__restrict__, 
				  const struct sched_param *__restrict__);
int posix_spawnattr_getsigmask(const posix_spawnattr_t *__restrict__, 
			       sigset_t *__restrict__);
int posix_spawnattr_setsigmask(posix_spawnattr_t *__restrict__, 
			       const sigset_t *__restrict__);
int posix_spawnattr_getsigdefault(const posix_spawnattr_t *__restrict__, 
				  sigset_t *__restrict__);
int posix_spawnattr_setsigdefault(posix_spawnattr_t *__restrict__, 
				  const sigset_t *__restrict__);
int posix_spawn(pid_t *__restrict__ , 
		const char *__restrict__,
		const posix_spawn_file_actions_t *,
		const posix_spawnattr_t *__restrict__, 
		char *const argv[__restrict__],
		char *const envp[__restrict__]);
int posix_spawnp(pid_t *__restrict__, 
		 const char *__restrict__,
		 const posix_spawn_file_actions_t *,
		 const posix_spawnattr_t *__restrict__, 
		 char *const argv[__restrict__],
		 char *const envp[__restrict__]);

#endif /* _H_SPAWN */
