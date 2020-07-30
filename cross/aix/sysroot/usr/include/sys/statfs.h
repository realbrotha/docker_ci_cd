/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53A src/bos/kernel/sys/statfs.h 1.17                                */
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
/* @(#)17	1.17  src/bos/kernel/sys/statfs.h, syslfs, bos53A, a2004_33D4 7/7/04 16:16:30  */
/*
 * COMPONENT_NAME: (SYSLFS) Logical File System
 *
 * FUNCTIONS: statfs header
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

#ifndef _H_STATFS
#define _H_STATFS

#include <sys/types.h>

/*
 * statfs.h - statfs system call return structure
 */

/*
 * file system statistics
 * NOTE: f_version is UNUSED NOW, but should be set to 0!
 * NOTE: all other reserved fields should be cleared by the vfs implementation
 */
struct statfs {
	int f_version;		/* version/type of statfs, 0 for now */
	int f_type;		/* type of info, zero for now */
	ulong_t f_bsize;	/* optimal file system block size */
	fsblkcnt_t f_blocks;	/* total data blocks in file system */
	fsblkcnt_t f_bfree;	/* free block in fs */
	fsblkcnt_t f_bavail;	/* free blocks avail to non-superuser */
	fsfilcnt_t f_files;	/* total file nodes in file system */
	fsfilcnt_t f_ffree;	/* free file nodes in fs */
#if !defined(_KERNEL) && defined(__64BIT__)
	fsid64_t f_fsid;	/* file system id */
#else
	fsid_t f_fsid;		/* file system id */
#endif
	int f_vfstype;		/* what type of vfs this is */
	ulong_t f_fsize;	/* fundamental file system block size */
	int f_vfsnumber;	/* vfs indentifier number */
	int f_vfsoff;		/* reserved, for vfs specific data offset */
	int f_vfslen;		/* reserved, for len of vfs specific data */
	int f_vfsvers;		/* reserved, for vers of vfs specific data */
	char f_fname[32];	/* file system name (usually mount pt.) */
	char f_fpack[32];	/* file system pack name */
	int f_name_max;	/* maximum component name length for posix */
};

/* This is a view of the 32-bit program statfs structure inside 64BK.
 */
#if defined(_KERNEL) && defined(__64BIT_KERNEL)
struct statfs32 {
        int       f_version;    /* version/type of statfs, 0 for now */
        int       f_type;       /* type of info, zero for now */
        uint      f_bsize;      /* optimal file system block size */
        uint      f_blocks;     /* total data blocks in file system */
        uint      f_bfree;      /* free block in fs */
        uint      f_bavail;     /* free blocks avail to non-superuser */
        uint      f_files;      /* total file nodes in file system */
        uint      f_ffree;      /* free file nodes in fs */
        fsid32_t  f_fsid;       /* file system id */
        int       f_vfstype;    /* what type of vfs this is */
        uint      f_fsize;      /* fundamental file system block size */
        int       f_vfsnumber;  /* vfs indentifier number */
        int       f_vfsoff;     /* reserved, for vfs specific data offset */
        int       f_vfslen;     /* reserved, for len of vfs specific data */
        int       f_vfsvers;    /* reserved, for vers of vfs specific data */
        char      f_fname[32];  /* file system name (usually mount pt.) */
        char      f_fpack[32];  /* file system pack name */
        int       f_name_max;   /* maximum component name length for posix */
};
#endif /* _KERNEL && __64BIT_KERNEL */

/* This statfs64 structure providing invariant 64-bit fields.
 */
struct statfs64 {
        int         f_version;   /* version/type of statfs, 0 for now */
        int         f_type;      /* type of info, zero for now */
        blksize64_t f_bsize;     /* optimal file system block size */
        blkcnt64_t  f_blocks;    /* total data blocks in file system */
        blkcnt64_t  f_bfree;     /* free block in fs */
        blkcnt64_t  f_bavail;    /* free blocks avail to non-superuser */
        uint64_t    f_files;     /* total file nodes in file system */
        uint64_t    f_ffree;     /* free file nodes in fs */
        fsid64_t    f_fsid;      /* file system id */
        int         f_vfstype;   /* what type of vfs this is */
        blksize64_t f_fsize;     /* fundamental file system block size */
        int         f_vfsnumber; /* vfs indentifier number */
        int         f_vfsoff;    /* reserved, for vfs specific data offset */
        int         f_vfslen;    /* reserved, for len of vfs specific data */
        int         f_vfsvers;   /* reserved, for vers of vfs specific data */
        char        f_fname[32]; /* file system name (usually mount pt.) */
        char        f_fpack[32]; /* file system pack name */
        int         f_name_max;  /* maximum component name length for posix */
};

#ifndef _KERNEL
#ifdef _NO_PROTO
extern int statfs();
extern int fstatfs();
extern int statfs64();
extern int fstatfs64();
#else
extern int statfs(char *, struct statfs *);
extern int fstatfs(int, struct statfs *);
extern int statfs64(char *, struct statfs64 *);
extern int fstatfs64(int, struct statfs64 *);
#endif /* _NO_PROTO */
#endif /* _KERNEL */

#endif /* _H_STATFS */
