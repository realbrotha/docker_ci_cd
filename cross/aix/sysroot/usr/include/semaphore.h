/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/usr/include/semaphore.h 1.8                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)55       1.8  src/bos/usr/include/semaphore.h, sysipc, bos53J, j2006_18A9 5/1/06 10:30:12 */

/*
 * COMPONENT_NAME: (SYSIPC) 
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

/* THIS FILE is for conformance to IEEE POSIX 1003.1c.
 * It describes required symbols for the Realtime option
 * which is NOT SUPPORTED.
 */

#ifndef _H_SEMAPHORE
#define _H_SEMAPHORE

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <fcntl.h>

#ifdef __cplusplus
extern "C" {
#endif

#if _XOPEN_SOURCE>=500

typedef int	sem_t;

extern int sem_close(sem_t *);
extern int sem_destroy(sem_t *);
extern int sem_getvalue(sem_t *__restrict__, int *__restrict__);
extern int sem_init(sem_t *, int, unsigned int);
extern sem_t *sem_open(const char *, int, ...);
extern int sem_post(sem_t *);
extern int sem_trywait(sem_t *);
extern int sem_unlink(const char *);
extern int sem_wait(sem_t *);
struct timespec;
extern int sem_timedwait(sem_t *__restrict__,
			const struct timespec *__restrict__);

#define SEM_FAILED ((sem_t *) -1)

/* flag for underlying syscall */
#define SEM_TRYWAIT   0x1
#define SEM_TIMEDWAIT 0x2

#endif /* _XOPEN_SOURCE>=500 */

#ifdef __cplusplus
}
#endif

#endif /* _H_SEMAPHORE */
