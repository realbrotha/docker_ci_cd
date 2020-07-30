/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/lfs/quota_common.h 1.6                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2003,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)02     1.6  src/bos/kernel/lfs/quota_common.h, syslfs, bos53L, l2007_04A5 1/14/07 09:55:26 */

#ifndef _H_JFS_QUOTA_COMMON
#define _H_JFS_QUOTA_COMMON

/* The following constants define the default length of time given a
 * user before the soft limits are treated as hard limits (usually
 * resulting in an allocation failure). The timer is started when the
 * user crosses their soft limit, it is reset when they go below their
 * soft limit.
 */
#define	MAX_IQ_TIME	(7*24*60*60)	/* 1 week */
#define	MAX_DQ_TIME	(7*24*60*60)	/* 1 week */


/* The following constants define the usage of the quota file array
 * in the jfsmount structure and dquot array in the inode structure.
 * The semantics of the elements of these arrays are defined in the
 * routine getinoquota; the remainder of the quota code treats them
 * generically and need not be inspected when changing the size of
 * the array.
 */
#define	MAXQUOTAS	2
#define	USRQUOTA	0	/* element used for user quotas */
#define	GRPQUOTA	1	/* element used for group quotas */


/* Definitions for the default names of the quotas files. */
#define INITQFNAMES { \
        "user",         /* USRQUOTA */ \
        "group",        /* GRPQUOTA */ \
        "undefined", \
};


#ifndef _KERNEL
/* Declarations for libc quota file stuff.
 */
extern char *qfname;
extern char *qfextension[];
extern char *quotagroup;
#endif /* _KERNEL */


/* External Interface: How quotas appear to the outside world. 64bit
 * size-invariant so that apps see the same structure no matter how
 * they're compiled and no manipulation has to be done in the kernel.
 */
typedef struct {
	uint64_t  bhard;	/* absolute limit on disk blks 		*/
	uint64_t  bsoft;	/* preferred limit on disk blks 	*/
	uint64_t  ihard;	/* maximum # allocated inodes 		*/
	uint64_t  isoft;	/* preferred inode limit		*/
	uint64_t  bused;	/* current 1k-byte block count		*/
	uint64_t  iused;	/* current # allocated inodes		*/
	time64_t  btime;	/* deadline for excessive disk use	*/
	time64_t  itime;	/* deadline for excessive files		*/
} quota64_t;			/* 64 bytes 				*/


/* Command definitions for the 'quotactl' system call.
 * The commands are broken into a main command defined below
 * and a subcommand that is used to convey the type of
 * quota that is being manipulated (see above).
 */
#define SUBCMDMASK	0x00ff
#define QCMD(__cmd, __type) ((__cmd) | ((__type) & SUBCMDMASK))

/* common commands */
#define	Q_QUOTAON	0x0100	/* enable quotas */
#define	Q_QUOTAOFF	0x0200	/* disable quotas */

/* JFS-specific commands */
#define	Q_GETQUOTA	0x0300	/* get limits and usage */
#ifndef _LINUX_SOURCE_COMPAT
 /* Standard AIX definitions of quota commands */
#define	Q_SETQUOTA	0x0400	/* set limits */
#define Q_SETQLIM	Q_SETQUOTA
#else
 /* Alternate definitions, for Linux Affinity */
#define	Q_SETQLIM	0x0400	/* set limits */
#define	Q_SETQUOTA	0x0700	/* set limits and usage */
#endif
#define	Q_SETUSE	0x0500	/* set usage */
#define	Q_SYNC		0x0600	/* sync disk copy of a filesystems quotas */

/* JFS2-specific commands */
#define	Q_J2GETQUOTA	0x1000	/* get Usage/Limit/Grace combo */
#define	Q_J2PUTQUOTA	0x1100	/* update Usage Record from quota64_t */
#define	Q_J2GETLIMIT	0x1200	/* get Limits Record */
#define	Q_J2NEWLIMIT	0x1300	/* new Limits Record */
#define	Q_J2PUTLIMIT	0x1400	/* put Limits Record */
#define	Q_J2RMVLIMIT	0x1500	/* remove/delete Limits Record */
#define	Q_J2DEFLIMIT	0x1600	/* set Limits Record to be the default */
#define	Q_J2USELIMIT	0x1700	/* associate Limits Class with usage record */
#define	Q_J2GETNEXTQ	0x1800	/* get next highest id with a usage record */
#define Q_J2INITFILE	0x1900	/* initialize an empty quota file */
#define Q_J2QUOTACHK	0x1A00	/* perform maintenance on the quota file */
#define Q_J2QENABLE	0x1B00	/* enable quota management */
#define Q_J2QDISABLE	0x1C00	/* disable quota management */

/* prototype for quotactl */
int quotactl(char *, int, int, caddr_t);

#endif /* _H_JFS_QUOTA_COMMON */
