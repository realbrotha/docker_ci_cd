/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/jfs/jfsmount.h 1.3                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1992          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)90	1.3  src/bos/usr/include/jfs/jfsmount.h, syspfs, bos530 12/9/92 08:13:52 */
/*
 * COMPONENT_NAME: (SYSPFS) Physical File System 
 *
 * FUNCTIONS: jfsmount.h
 *
 * ORIGINS: 27, 26
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1990
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_JFS_JFSMOUNT
#define _H_JFS_JFSMOUNT

#include <sys/types.h>
#include <sys/vnode.h>          
#include <sys/cred.h>          
#include <jfs/quota.h>          

struct	jfsmount {
	dev_t	jm_dev;			/* devid block device mounted */
	struct	vnode *jm_quotas[MAXQUOTAS]; /* pointer to quota files */
	struct	ucred *jm_cred[MAXQUOTAS]; /* cred for access to quota file */
	time_t	jm_btime[MAXQUOTAS];	/* block quota time limit */
	time_t	jm_itime[MAXQUOTAS];	/* inode quota time limit */
	char	jm_qflags[MAXQUOTAS];	/* quota specific flags, see below */
};

/*
 * Flags describing the state of quotas.
 */
#define	QTF_OPENING	0x01		/* Q_QUOTAON in progress */
#define	QTF_CLOSING	0x02		/* Q_QUOTAOFF in progress */

#endif /* _H_JFS_JFSMOUNT */
