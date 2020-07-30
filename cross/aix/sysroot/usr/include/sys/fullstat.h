/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/fullstat.h 1.17                              */
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
/* @(#)69       1.17  src/bos/kernel/sys/fullstat.h, syslfs, bos530 7/25/02 19:29:00 */
/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _H_FULLSTAT
#define _H_FULLSTAT

#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif


/* fullstat(struct fullstat*) is an obsolete stat() interface; it is 
 * maintained for backwards compatibility. Neither the function fullstat()
 * nor struct fullstat are enabled for file larger than 2G.
 */
struct  fullstat {
	dev_t	st_dev;		/* ID of device containing a directory
				 * entry for this file.  File serial
				 * no + device ID uniquely identify
				 * the file within the system 
				 */
	ino_t	 st_ino;	/* File serial number */
	mode_t	 st_mode;	/* File mode; see #define's below */
	nlink_t	 st_nlink;	/* Number of links */
	ushort_t st_flag;	/* Flag word */
	uid_t	 st_uid;	/* User ID of the file's owner */
	gid_t	 st_gid;	/* Group ID of the file's group */
	dev_t	 st_rdev;	/* ID of device. This entry is defined only for
				 * character or block special files 
				 */
	soff_t	st_size;	/* File size in bytes */
	time_t	st_atime;	/* Time of last access */
	int	st_spare1;
	time_t	st_mtime;	/* Time of last data modification */
	int	st_spare2;
	time_t	st_ctime;	/* Time of last file status change */
	int	st_spare3;
	blksize_t	st_blksize;	/* Size of block in file */
	blkcnt_t	st_blocks;	/* Actual number of blocks allocated */
	int	st_vfstype;	/* Type of fs (see vnode.h) */
	uint_t	st_vfs;		/* Vfs number */
	uint_t	st_type;	/* Vnode type */
	uint_t	st_gen;		/* Inode generation number */
	uint_t	st_reserved[9];
#ifdef __64BIT__
	uint_t	st_padto_ll; 
	off_t	st_ssize;	/* 64 bit file size in bytes */
#endif /* __64BIT__ */
};


/* Compatibility macros
 */
#define	fst_type	st_type
#define	fst_vfstype	st_vfstype
#define	fst_vfs		st_vfs
#define	fst_i_gen	st_gen
#define	fst_flag	st_flag

/* The following fields have been removed.  These defines are TEMPORARY. */
#define	fst_nid		st_reserved[0]

/* Defines for fullstat/ffullstat cmd argument
 */
#define	FL_STAT		STX_NORMAL	/* Normal fullstat		*/
#define	FL_NOFOLLOW	STX_LINK	/* Do NOT follow symbolic links	*/
#define FL_STATMASK	0x00FF		/* mask for stat types		*/
#define FULLSTATSIZE	sizeof(struct fullstat)

#ifdef __cplusplus
}
#endif

#endif /* _H_FULLSTAT */
