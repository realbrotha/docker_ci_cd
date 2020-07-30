/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/mqueue.h 1.5                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)54  1.5  src/bos/usr/include/mqueue.h, sysipc, bos530 2/16/04 06:49:44 */

/*
 * COMPONENT_NAME: (SYSIPC) IPC Message Facility
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

#ifndef _H_MQUEUE
#define _H_MQUEUE

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <sys/signal.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int mqd_t;

struct mq_attr
{
	long	mq_flags;
	long	mq_maxmsg;
	long	mq_msgsize;
	long	mq_curmsgs;
};

extern int	mq_close(mqd_t);
extern int	mq_getattr(mqd_t, struct mq_attr *);
extern int	mq_notify(mqd_t, const struct sigevent *);
extern mqd_t	mq_open(const char *, int, ...);
extern ssize_t  mq_receive(mqd_t, char *, size_t, unsigned int *);
extern int	mq_send(mqd_t, const char *, size_t, unsigned int);
extern int	mq_setattr(mqd_t, const struct mq_attr *__restrict__, struct mq_attr *__restrict__);
extern int	mq_unlink(const char *);
extern ssize_t	mq_timedreceive(mqd_t, char *__restrict__, size_t,
		unsigned *__restrict__, const struct timespec *__restrict__);
extern int	mq_timedsend(mqd_t, const char *, size_t, unsigned,
		const struct timespec *);

/* flag for underlying syscall */
#define MQ_WAIT      0x0
#define MQ_TIMEDWAIT 0x1


#ifdef __cplusplus
}
#endif

#endif /* _H_MQUEUE */
