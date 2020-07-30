/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/ustat.h 1.5.1.4                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
#ifndef _H_USTAT
#define _H_USTAT

/* @(#)86	1.5.1.4  src/bos/usr/include/ustat.h, cmdfs, bos530 7/25/02 19:29:41 */
/*
 * SYSLFS: Logical Filesystem
 *
 * FUNCTIONS: ustat header
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1993
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifdef DFS

#include "sys/ustat.h"

#else

struct  ustat
{
	daddr_t	f_tfree;	/* total free */
	ino_t	f_tinode;	/* total inodes free */
	char	f_fname[6];	/* filsys name */
	char	f_fpack[6];	/* filsys pack name */
};

#ifndef _KERNEL
#ifdef _NO_PROTO
extern int ustat();
#else 
extern int ustat(dev_t, struct ustat *);
#endif /* _NO_PROTO */
#endif /* _KERNEL */

#endif /* DFS */
#endif /* _H_USTAT */
