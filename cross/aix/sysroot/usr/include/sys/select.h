/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/select.h 1.24                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)90	1.24  src/bos/kernel/sys/select.h, sysios, bos530 7/12/00 14:09:16 */
#ifndef _H_SELECT
#define _H_SELECT
/*
 * COMPONENT_NAME: (SYSIOS) Select system call header file
 *
 * ORIGINS: 26, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef _H_STANDARDS
#include <standards.h>
#endif /* _H_STANDARDS */

#ifndef _H_SYS_TIME
#include <sys/time.h>
#endif /* _H_SYS_TIME */

#if _XOPEN_SOURCE_EXTENDED==1
/* Number of fds in one entry and number of entries in fds_bits[] array.
 * (see <sys/time.h>)
 */
typedef long	fd_mask;
#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _ALL_SOURCE
/*
 * Timeout values - used for poll() system call (not for select() system call)
 */
#ifndef NO_TIMEOUT
#define NO_TIMEOUT      0       /* don't wait for a response            */
#endif

#ifndef INF_TIMEOUT
#define INF_TIMEOUT     -1      /* wait until a response is received    */
#endif


/*
 * Number of file descriptors (bits).
 * Apply to nfdsmsgs parameter of SELECT system
 * call &/or return value from SELECT.
 */
#define NFDS(x)		((x) & 0x0000FFFF)

/*
 * Lower half of word.
 * Used in hashing algorithm for devsel_hash chain.
 */
#define	LOW_HALF(x)	NFDS(x)

/*
 * Number of message queues.
 * Apply to nfdsmsgs parameter of SELECT system
 * call &/or return value from SELECT.
 */
#define NMSGS(x)	(((x) >> 16) & 0x0000FFFF)

/*
 * Upper half of word.
 * Used in hashing algorithm for devsel_hash chain.
 */
#define	HIGH_HALF(x)	NMSGS(x)

/*
 * Macro used to define a sellist structure
 * for the SELECT system call.
 */
#define	SELLIST(F,M)		\
struct				\
{				\
	ulong fdsmask[F];	\
	int   msgids[M];	\
}

#define NFDBITS	__NFDBITS
#ifndef howmany
#define	howmany(x, y)	(((x)+((y)-1))/(y))
#endif

#endif /* _ALL_SOURCE */

#endif  /* _H_SELECT */
