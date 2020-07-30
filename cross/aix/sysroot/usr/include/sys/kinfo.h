/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/kinfo.h 1.10                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)96	1.10  src/bos/kernel/sys/kinfo.h, incsys, bos530 12/6/00 15:52:55 */
/*
 * COMPONENT_NAME:  Kernel Info Header
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 26 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution is only permitted until one year after the first shipment
 * of 4.4BSD by the Regents.  Otherwise, redistribution and use in source and
 * binary forms are permitted provided that: (1) source distributions retain
 * this entire copyright notice and comment, and (2) distributions including
 * binaries display the following acknowledgement:  This product includes
 * software developed by the University of California, Berkeley and its
 * contributors'' in the documentation or other materials provided with the
 * distribution and in all advertising materials mentioning features or use
 * of this software.  Neither the name of the University nor the names of
 * its contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	(#)kinfo.h	7.4 (Berkeley) 6/28/90
 */

/*
 * Get kernel info
 */

#define ki_op(x)		((x)&0x0000ffff)
#define ki_type(x)		((x)&0x0000ff00)

/* 
 * proc info 
 */
#define	KINFO_PROC		(0<<8)
#define KINFO_PROC_ALL	(KINFO_PROC|0)	/* everything */
#define	KINFO_PROC_PID	(KINFO_PROC|1)	/* by process id */
#define	KINFO_PROC_PGRP	(KINFO_PROC|2)	/* by process group id */
#define	KINFO_PROC_SESSION (KINFO_PROC|3)	/* by session of pid */
#define	KINFO_PROC_TTY	(KINFO_PROC|4)	/* by controlling tty */
#define	KINFO_PROC_UID	(KINFO_PROC|5)	/* by effective uid */
#define	KINFO_PROC_RUID	(KINFO_PROC|6)	/* by real uid */

/*
 * Routing table
 */
#define ki_af(x)		(((x)&0x00ff0000) >> 16)
#define KINFO_RT		(1<<8)
#define KINFO_RT_DUMP		(KINFO_RT|1)	/* dump; may limit to a.f. */
#define KINFO_RT_FLAGS		(KINFO_RT|2)	/* by flags, e.g. RESOLVING */
#define KINFO_RT_IFLIST		(KINFO_RT|3)	/* dump ifnet list */

/*
 * vnodes
 */
#define	KINFO_VNODE		(2<<8)

/*
 * Network Device Drivers
 */
#define	KINFO_NDD		(4<<8)

/* 
 * Reading
 */
#define KINFO_READ		(8<<8)

/* 
 * Writing
 */
#define KINFO_WRITE		(10<<8)

/* 
 * 64 bit version of read and write
 */
#define KINFO_READ64		(20<<8)
#define KINFO_WRITE64		(40<<8)

/*
 * Zero netkmem stats
 */
#define KINFO_ZSTATS		(80<<8)

/* Set interface statistics for netstat -Zs/i */
#define KINFO_SET_IF_STATS     (100<<8)
#define KINFO_SET_DMX_STATS     (200<<8)

/*
 * Locking and stats
 */

struct kinfo_lock {
	int	kl_lock;
	int	kl_want;
	int	kl_locked;
};

#ifdef KERNEL
extern struct kinfo_lock kinfo_lock;
#endif

/*
 * structure used by the KINFO_READ64 and KINFO_WRITE64 to allow a 32 bit
 * program to pass a 64 bit kernel address to a 64 bit kernel.
 */
struct kinfo_addr {
	long long addr;
};

typedef struct kinfo_addr kinfo_addr_t;
