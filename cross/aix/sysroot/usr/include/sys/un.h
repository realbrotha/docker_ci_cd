/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernel/sys/un.h 1.23                                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)73	1.23  src/bos/kernel/sys/un.h, sockinc, bos53J, j2006_21C0 3/27/06 08:30:53 */
/*
 *   COMPONENT_NAME: SOCKINC
 *
 *   FUNCTIONS: SUN_LEN
 *		
 *
 *   ORIGINS: 26,27,85
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1993,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * 
 * (c) Copyright 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 * 
 */
/*
 * OSF/1 1.2
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Base:	un.h	7.4 (Berkeley) 9/4/89
 *	Merged: un.h	7.7 (Berkeley) 6/28/90
 */

#ifndef	_SYS_UN_H_
#define	_SYS_UN_H_

#include <standards.h>                  /* define _*_SOURCE* macros */

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>
/*
 * Definitions for UNIX IPC domain.
 */

#if _XOPEN_SOURCE_EXTENDED == 1

/*
 * Family typedef
 */
#ifndef _SA_FAMILY_T
#define _SA_FAMILY_T
typedef uchar_t sa_family_t;
#endif

/* Change _SS_MAXSIZE (socket.h) if the size of sockaddr_un struct increases */

#if defined(COMPAT_43) && !defined(_KERNEL)
struct	sockaddr_un {
	ushort_t	sun_family;	/* AF_UNIX */
	char        sun_path[1024]; /* changed from 104 to PATH_MAX to support long user names. This value should be changed manually if PATH_MAX changes in future */
};
#else
struct	sockaddr_un {
	uchar_t	    sun_len;		/* sockaddr len including null */
	sa_family_t sun_family;		/* AF_UNIX */
	char        sun_path[1023]; /* changed from 104 to PATH_MAX to support long user names. This value should be changed manually if PATH_MAX changes in future */
};
#endif /* COMPAT_43 && !_KERNEL */

#endif /* _XOPEN_SOURCE_EXTENDED == 1 */

#ifdef _ALL_SOURCE

/* actual length of an initialized sockaddr_un */
#define SUN_LEN(su) \
	(sizeof(*(su)) - sizeof((su)->sun_path) + strlen((su)->sun_path))

#endif /* _ALL_SOURCE */

#endif /* _SYS_UN_H */

