/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/timeb.h 1.10                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)35	1.10  src/bos/kernel/sys/timeb.h, sysproc, bos530 2/19/03 10:33:57 */

/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 26,27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 *
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef _H_TIMEB
#define _H_TIMEB

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#if _XOPEN_SOURCE_EXTENDED==1

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>

struct timeb {
	time_t		time;		/* Seconds */
	unsigned short	millitm;	/* milliseconds */
	short		timezone;	/* Local timezone in minutes */
	short		dstflag;	/* TRUE if DST is in effect */
};

#ifdef _NO_PROTO
extern int ftime();
#else /* _NO_PROTO */
extern int ftime(struct timeb *);
#endif /* _NO_PROTO */

#endif /* _XOPEN_SOURCE_EXTENDED */

#endif /* _H_TIMEB */
