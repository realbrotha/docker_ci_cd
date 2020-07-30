/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53A src/bos/kernel/sys/statvfs.h 1.12                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1995,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)10	1.12  src/bos/kernel/sys/statvfs.h, libcfs, bos53A, a2004_33D4 8/4/04 15:15:57 */
/*
 *   COMPONENT_NAME: LIBCFS
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 4,27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1993,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_STATVFS
#define _H_STATVFS

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#if _XOPEN_SOURCE_EXTENDED==1

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>

#define _FSTYPSIZ 	16	

#ifdef _ALL_SOURCE
#include <sys/vmount.h>

#define FSTYPSIZ 	_FSTYPSIZ
#endif

/*
 * statvfs system call return structure
 */

struct statvfs {
	ulong_t    f_bsize;	/* preferred file system block size          */
	ulong_t    f_frsize;	/* fundamental file system block size        */
	fsblkcnt_t f_blocks;	/* total # of blocks of f_frsize in fs       */ 
	fsblkcnt_t f_bfree;	/* total # of free blocks 		     */
	fsblkcnt_t f_bavail;	/* # of blocks available to non super user   */
	fsfilcnt_t f_files;	/* total # of file nodes (inode in JFS)      */
	fsfilcnt_t f_ffree;	/* total # of free file nodes		     */
	fsfilcnt_t f_favail;	/* # of nodes available to non super user    */
#ifdef _ALL_SOURCE
	fsid_t	   f_fsid;	/* file system id			     */
#else
	ulong_t	   f_fsid;	/* file system id			     */
#ifndef __64BIT__
	ulong_t	   f_fstype;    /* file system type			     */
#endif
#endif  /* _ALL_SOURCE */
	char       f_basetype[_FSTYPSIZ]; /* Filesystem type name (eg. jfs)  */
	ulong_t    f_flag;	/* bit mask of flags			     */
	ulong_t    f_namemax;	/* maximum filename length	  	     */
	char       f_fstr[32];	/* filesystem-specific string */
	ulong_t    f_filler[16];/* reserved for future use		     */
};

#define ST_NOSUID	0x0040		/* don't maintain SUID capability    */

#define ST_RDONLY	0x0001		/* file system mounted read only     */
#define ST_NODEV	0x0080		/* don't allow device access across  */
					/* this mount		 	     */	

/*
 * Prototypes
 */
#ifdef _NO_PROTO
extern int statvfs();
extern int fstatvfs();
#else
extern int statvfs(const char *__restrict__, struct statvfs *__restrict__);
extern int fstatvfs(int, struct statvfs *);
#endif

/*
 * statvfs64 system call return structure
 */
#ifdef _ALL_SOURCE

struct statvfs64 {
        blksize64_t f_bsize; 	/* preferred file system block size          */
        blksize64_t f_frsize;   /* fundamental file system block size        */
        blkcnt64_t f_blocks;    /* total # of blocks of f_frsize in fs       */
        blkcnt64_t f_bfree;     /* total # of free blocks                    */
        blkcnt64_t f_bavail;    /* # of blocks available to non super user   */
        blkcnt64_t f_files;     /* total # of file nodes (inode in JFS)      */
        blkcnt64_t f_ffree;     /* total # of free file nodes                */
        blkcnt64_t f_favail;    /* # of nodes available to non super user    */
	fsid64_t   f_fsid;	/* file system id			     */
        char       f_basetype[FSTYPSIZ]; /* Filesystem type name (eg. jfs)  */
        ulong_t    f_flag;      /* bit mask of flags                         */
        ulong_t    f_namemax;   /* maximum filename length                   */
        char       f_fstr[32];  /* filesystem-specific string */
        ulong_t    f_filler[16];/* reserved for future use                   */
};

/*
 * Prototypes
 */
#ifdef _NO_PROTO
extern int statvfs64();
extern int fstatvfs64();
#else
extern int statvfs64(const char *__restrict__, struct statvfs64 *__restrict__);
extern int fstatvfs64(int, struct statvfs64 *);
#endif

#endif  /* _ALL_SOURCE */

#endif /* _XOPEN_SOURCE_EXTENDED */
#endif /* _H_STATVFS */
