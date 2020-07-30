/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/jfs/quota.h 1.13                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,2003          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)91       1.13  src/bos/usr/include/jfs/quota.h, syspfs, bos530 10/13/03 14:29:58 */
/*
 * COMPONENT_NAME: (SYSPFS) Physical File System
 *
 * FUNCTIONS: quota.h
 *
 * ORIGINS: 26, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 2000
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_JFS_QUOTA
#define _H_JFS_QUOTA

#include <sys/types.h>
#include <sys/param.h>
#include <sys/vmuser.h>
#include <sys/fs/quota_common.h>

/*  Range of valid disk quota ids is MINDQID - MAXDQID
 */
#define	MINDQID		0	
#define	MAXDQID		((MAXFSIZE / sizeof (struct dqblk)) - 1)

/*
 * The following structure defines the format of the disk quota file
 * (as it appears on disk) - the file is an array of these structures
 * indexed by user or group number.  The quotactl system call establishes
 * the vnode for each quota file (a pointer is retained in the jfsmount
 * structure).
 */

#ifdef __64BIT_KERNEL
struct	dqblk {
	int	  dqb_bhardlimit;	/* absolute limit on disk blks alloc */
	int	  dqb_bsoftlimit;	/* preferred limit on disk blks */
	int	  dqb_curblocks;	/* current block count */
	int	  dqb_ihardlimit;	/* maximum # allocated inodes + 1 */
	int	  dqb_isoftlimit;	/* preferred inode limit */
	int	  dqb_curinodes;	/* current # allocated inodes */
	time32_t  dqb_btime;	/* time limit for excessive disk use */
	time32_t  dqb_itime;	/* time limit for excessive files */
};
#else  /* __64BIT_KERNEL */
struct	dqblk {
	u_long	dqb_bhardlimit;	/* absolute limit on disk blks alloc */
	u_long	dqb_bsoftlimit;	/* preferred limit on disk blks */
	u_long	dqb_curblocks;	/* current block count */
	u_long	dqb_ihardlimit;	/* maximum # allocated inodes + 1 */
	u_long	dqb_isoftlimit;	/* preferred inode limit */
	u_long	dqb_curinodes;	/* current # allocated inodes */
	time_t	dqb_btime;	/* time limit for excessive disk use */
	time_t	dqb_itime;	/* time limit for excessive files */
};
#endif  /* __64BIT_KERNEL */

/* disk quota data block size.
 */
#define	DQBSIZE		1024

/* miscellanous defines for dealing with partial blocks.
 */
#define DQCBIT		0x80000000
#define DQCARRY(c)	((uint)(c) >> 31)
#define DQBTIME(t)	((uint)(t) & (~DQCBIT))
#define DQSBTIME(c,t)	(((uint)(c) << 31) | ((uint)(t) & (~DQCBIT)))

#ifdef _KERNEL

#include <jfs/jfsmount.h>
#include <jfs/fsparam.h>

/*
 * The following structure records disk usage for a user or group on a
 * filesystem. There is one allocated for each quota that exists on any
 * filesystem for the current user or group. A cache is kept of recently
 * used entries.
 */

struct	dquot {
	struct	dquot *	dq_forw;	/* hash chain forward */
	struct	dquot *	dq_back;	/* hash chain backword */
	struct	dquot *	dq_next;	/* next on cache list */
	struct	dquot *	dq_prev;	/* previous on cache list */
	int		dq_lock;	/* VMM bit lock */
	short		dq_flags;	/* flags, see below */
	short		dq_type;	/* quota type of this dquot */
	ulong32int64_t	dq_cnt;		/* count of active references */
	uid_t		dq_id;		/* identifier this applies to */
	dev_t		dq_dev;		/* filesystem that this is taken from*/
	struct jfsmount *dq_jmp;	/* mount structure pointer */
	struct dqblk	dq_dqb;		/* actual usage & quotas */
	tid_t		dq_event;	/* event list for quota activity */
};

/*
 * dq_lock bits used by v_dqlock() and v_dqunlock()
 */
#define	DQ_LOCK		0x01		/* this quota locked (no MODS) */
#define	DQ_WANT		0x02		/* wakeup on unlock */

/*
 * dq_flag values
 */
#define	DQ_MOD		0x04		/* this quota modified since read */
#define	DQ_FAKE		0x08		/* no limits here, just usage */
#define	DQ_BLKS		0x10		/* has been warned about blk limit */
#define	DQ_INODS	0x20		/* has been warned about inode limit */
#define	DQ_QFLOCK	0x40		/* this quota is transforming */
#define	DQ_QFWANT	0x80		/* wakeup on transform complete */
#define	DQ_IOERROR	0x100		/* error reading this quota */

/*
 * Shorthand notation.
 */
#define	dq_bhardlimit	dq_dqb.dqb_bhardlimit
#define	dq_bsoftlimit	dq_dqb.dqb_bsoftlimit
#define	dq_curblocks	dq_dqb.dqb_curblocks
#define	dq_ihardlimit	dq_dqb.dqb_ihardlimit
#define	dq_isoftlimit	dq_dqb.dqb_isoftlimit
#define	dq_curinodes	dq_dqb.dqb_curinodes
#define	dq_btime	dq_dqb.dqb_btime
#define	dq_itime	dq_dqb.dqb_itime

/*
 * If the system has never checked for a quota for this file,
 * then it is set to NODQUOT. Once a write attempt is made
 * the inode pointer is set to reference a dquot structure.
 */
#define	NODQUOT		((struct dquot *) 0)

#define	JFSTODQ(BLKS)	((BLKS) * (BSIZE/DQBSIZE))

/*
 * Hash anchors for dquot table.
 */
struct hdquot {	
	struct dquot *dqh_forw;
	struct dquot *dqh_back;
};

/* 
 * Hash table size and marco for hash function.
 */
# define	NHDQUOT		PAGESIZE/sizeof (struct hdquot)
# define	DQHASH(DEV,ID) \
		(&hdquot[(((int)((DEV))) + ((int)((ID)))) & (NHDQUOT-1)])

/* valid disk quota id.
 */
# define	DQVALID(ID) \
		(((int)((ID))) >= MINDQID && ((int)((ID))) <= MAXDQID ? 1 : 0)

#endif /* _KERNEL */

#endif /* _H_JFS_QUOTA */
