/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/msgbuf.h 1.8                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1987,1990          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)09	1.8  src/bos/kernel/sys/msgbuf.h, sysipc, bos530 2/28/97 08:08:03 */
/*
 * COMPONENT_NAME:
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27 26
 *
 * (C) COPYRIGHT International Business Machines Corp. 1987, 1990
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _H_MSGBUF
#define _H_MSGBUF

/*
 * BSD to AIX compatibility <sys/msgbuf.h> include file
 * COPYRIGHT 1987 IBM CORP.
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	(#)msgbuf.h	7.1 (Berkeley) 6/4/86
 */

#define	MSG_MAGIC	0x063061
#define	MSG_BSIZE	(4096 - 3 * sizeof (int))
struct	msgbuf {
#ifdef __64BIT__
	int	msg_magic;
	int	msg_bufx;
	int	msg_bufr;
#else
	long	msg_magic;
	long	msg_bufx;
	long	msg_bufr;
#endif
	char	msg_bufc[MSG_BSIZE];
};
#ifdef _BSD
#ifdef _KERNEL
struct	msgbuf msgbuf;
#endif
#endif /* _BSD */
 
#endif /* _H_MSGBUF */
