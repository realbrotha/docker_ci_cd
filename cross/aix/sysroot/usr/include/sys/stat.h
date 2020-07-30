/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/stat.h 1.53.2.1                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)06       1.53.2.1  src/bos/kernel/sys/stat.h, syslfs, bos53L, l2007_04A5 1/14/07 09:41:18 */
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
#ifndef _H_STAT
#define _H_STAT

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef _H_MODE
#include <sys/mode.h>
#endif

/*
 * POSIX requires that certain values be included in stat.h.  It also
 * requires that when _POSIX_SOURCE is defined only those standard
 * specific values are present.  This header includes all the POSIX
 * required entries.
 */

#ifdef _POSIX_SOURCE 

#if !defined(_LARGE_FILES) && !defined(_KERNEL)

struct	stat 
{
	dev_t	st_dev;		/* ID of device containing a directory entry 
				 * for this file.  File serial no + device 
				 * ID uniquely identify the file within the 
				 * system 
				 */
	ino_t	st_ino;		/* File serial number */
#ifdef	_NONSTD_TYPES
	ushort	st_mode_ext;
	ushort  st_mode;
#else
	mode_t	st_mode;	/* File mode; see #define's below */
#endif
	nlink_t st_nlink;	/* Number of links */
	ushort_t st_flag;	/* Flag word */
#ifdef	_NONSTD_TYPES
	ushort	st_uid_ext;
	ushort	st_uid;
	ushort	st_gid_ext;
	ushort	st_gid;
#else
	uid_t	st_uid;		/* User ID of the file's owner 	*/
	gid_t	st_gid;		/* Group ID of the file's group	*/
#endif

	dev_t	st_rdev;       	/* ID of device. This entry is defined only for
				 * character or block special files  
				 */
#ifndef __64BIT__
	off_t	st_size;	/* 32 bit file size	*/ 	
#else
	int	st_ssize;	/* 32 bit file size	*/ 	
#endif
	time_t	st_atime;	/* Time of last access 	*/
	int	st_atime_n;
	time_t	st_mtime;	/* Time of last data modification */
	int	st_mtime_n;
	time_t	st_ctime;	/* Time of last file status change */
	int	st_ctime_n;
	blksize_t st_blksize;	/* Optimal blocksize for file system i/o ops */
	blkcnt_t st_blocks;	/* Actual number of blocks allocated
				 * in DEV_BSIZE blocks 
				 */
	int	st_vfstype;	/* Type of fs (see vnode.h) */
	uint_t	st_vfs;		/* Vfs number */
	uint_t	st_type;	/* Vnode type */
	uint_t	st_gen;		/* Inode generation number */

	/* end of information returned by non-large file enabled stat */
	uint_t	st_reserved[9];
#ifdef __64BIT__
	uint_t	st_padto_ll; 
	off_t	st_size;	/* 64 bit file size in bytes */
#endif /* __64BIT__ */
};

#endif /* ! __LARGE_FILES  &&  ! _KERNEL */

#ifdef _KERNEL
struct stat
{
	dev_t	st_dev;		/* ID of device containing a directory entry 
				 * for this file.  File serial no + device 
				 * ID uniquely identify the file within the 
				 * system 
				 */
	ino_t	st_ino;		/* File serial number */
	mode_t	st_mode;	/* File mode; see #define's below */
	nlink_t st_nlink;	/* Number of links */
	ushort_t st_flag;	/* Flag word */
	uid_t	st_uid;		/* User ID of the file's owner 	*/
	gid_t	st_gid;		/* Group ID of the file's group	*/
	dev_t	st_rdev;       	/* ID of device. This entry is defined only for
				 * character or block special files  
				 */
#ifdef __64BIT_KERNEL
	off_t	st_size;	/* 64 bit file size	*/ 	
#else  
	int	st_size;	/* 32 bit file size	*/ 	
#endif  
	time_t	  st_atime;	/* Time of last access 	*/
	int	  st_atime_n;
	time_t	  st_mtime;	/* Time of last data modification */
	int	  st_mtime_n;
	time_t	  st_ctime;	/* Time of last file status change */
	int	  st_ctime_n;
	blksize_t st_blksize;	/* Optimal blocksize for file system i/o ops */
	blkcnt_t  st_blocks;	/* Actual number of blocks allocated
				 * in DEV_BSIZE blocks 
				 */
	int	st_vfstype;	/* Type of fs (see vnode.h) */
	uint_t	st_vfs;		/* Vfs number */
	uint_t	st_type;	/* Vnode type */
	uint_t	st_gen;		/* Inode generation number */

	/* end of information returned by non-large file enabled stat */
	uint_t	st_reserved[10];
#ifndef __64BIT_KERNEL
	offset_t st_llsize;	/* 64 bit file size in bytes */
#endif
};
#endif /* _KERNEL */


#if defined(_LARGE_FILES) || defined(_LARGE_FILE_API)


/* The large file versions of the stat interfaces use this version of
 * the stat structure.  The stat64 structure must be identical to the
 * stat structure compiled in 64 bit mode.
 */
struct	stat64 
{
	dev_t	st_dev;		/* ID of device containing a directory entry 
				 * for this file.  File serial no + device 
				 * ID uniquely identify the file within the 
				 * system 
				 */
	ino_t	st_ino;		/* File serial number */
	mode_t	st_mode;	/* File mode; see #define's below */
	nlink_t st_nlink;	/* Number of links */
	ushort_t st_flag;	/* Flag word */
	uid_t	st_uid;		/* User ID of the file's owner	*/
	gid_t	st_gid;		/* Group ID of the file's group	*/
	dev_t	st_rdev;       	/* ID of device. This entry is defined only for
				 * character or block special files  
				 */
	soff_t	st_ssize;	/* 32 bit file size */ 	
	time_t	st_atime;	/* Time of last access */
	int	st_atime_n;
	time_t	st_mtime;	/* Time of last data modification */
	int	st_mtime_n;
	time_t	st_ctime;	/* Time of last file status change */
	int	st_ctime_n;
	blksize_t st_blksize;	/* Optimal blocksize for file system i/o ops */
	blkcnt_t st_blocks;	/* Actual number of blocks allocated
				 * in DEV_BSIZE blocks 
				 */
	int	st_vfstype;	/* Type of fs (see vnode.h) */
	uint_t	st_vfs;		/* Vfs number */
	uint_t	st_type;	/* Vnode type */
	uint_t	st_gen;		/* Inode generation number */
	uint_t	st_reserved[10];
#ifdef _LARGE_FILES
	off_t		st_size; /* 64 bit file size on bytes	*/
#else
	off64_t		st_size; /* 64 bit file size in bytes	*/
#endif
};

/* The stat64x structure exists to provide a uniform stat structure
 * that can be returned to any application (32/64) from any kernel
 * (32/64), without reshaping.
 */
struct stat64x
{
	dev64_t		st_dev;		/* 8: ID of device containing
					 * a directory entry for this
					 * file.  File serial no +
					 * device ID uniquely identify
					 * the file within the system
					 */
	ino64_t		st_ino;		/* 8: File serial number */
	mode_t		st_mode;	/* 4: File mode; see #define's below */
	nlink_t		st_nlink;	/* 2: Number of links */
	ushort_t	st_flag;	/* 2: Flag word */
	uid_t		st_uid;		/* 4: User ID of the file's owner */
	gid_t		st_gid;		/* 4: Group ID of the file's group */
	dev64_t		st_rdev;       	/* 8: ID of device. This entry
					 * is defined only for
					 * character or block special
					 * files
					 */
#ifdef _LARGE_FILES
	off_t		st_size;	/* 8: 64-bit file size */
#else
	off64_t		st_size;	/* 8: 64-bit file size */
#endif
	
	time64_t	st_atime;	/* 8: Time of last access */
	int32_t		st_atime_n;	/* 4: nanoseconds */
	int32_t		st_pad1;	/* 4: padding */
	time64_t	st_mtime;	/* 8: Time of last data modification */
	int32_t		st_mtime_n;	/* 4: nanoseconds */
	int32_t		st_pad2;	/* 4: padding */
	time64_t	st_ctime;	/* 8: Time of last file status change */
	int32_t		st_ctime_n;	/* 4: nanoseconds */
	int32_t		st_pad3;	/* 4: padding */
	blksize64_t	st_blksize;	/* 8: Optimal blocksize for file system i/o ops */
	blkcnt64_t	st_blocks;	/* 8: Actual number of blocks allocated
					 * in DEV_BSIZE blocks 
					 */
	int32_t		st_vfstype;	/* 4: Type of fs (see vnode.h) */
	uint32_t	st_vfs;		/* 4: Vfs number */
	uint32_t	st_type;	/* 4: Vnode type */
	uint32_t	st_gen;		/* 4: Inode generation number */
	uint32_t	st_reserved[11];/* 44: reserved */
};					/* 176 total */

/* 64-bit interfaces */
#ifdef _NO_PROTO
	extern int	stat64x();
	extern int	fstat64x();
	extern int	lstat64x();
#else 
	extern int	stat64x(const char *__restrict__, struct stat64x *__restrict__);
	extern int	fstat64x(int, struct stat64x *__restrict__);
	extern int	lstat64x(const char *__restrict__, struct stat64x *__restrict__);
#endif /* _NO_PROTO */

#endif /* _LARGE_FILES || LARGE_FILE_API */

#define	st_spare1	st_atime_n
#define	st_spare2	st_mtime_n
#define	st_spare3	st_ctime_n
#define	st_Reserved1	st_reserved[0]
#define	st_Reserved2	st_reserved[1]
#define	st_access	st_reserved[2]
#define	st_spare4	st_reserved[3]

#ifndef _KERNEL
#ifndef	_NONSTD_TYPES
#ifdef	_NO_PROTO
	extern mode_t	umask(); 
#else	/* _NO_PROTO */
	extern mode_t	umask(mode_t); 
#endif	/* _NO_PROTO */
#endif	/* _NONSTD_TYPES */
#endif	/* _KERNEL */

#ifdef _LARGE_FILES
#define stat	stat64
#define fstat	fstat64
#if _XOPEN_SOURCE_EXTENDED==1
#define lstat	lstat64
#endif
#endif	/* _LARGE_FILES */

#ifdef _NO_PROTO
#ifndef _KERNEL
	extern int	mkdir(); 
	extern int	stat();
	extern int	fstat();
	extern int	chmod();
#if _XOPEN_SOURCE_EXTENDED==1
	extern int	fchmod();
	extern int	lstat();
	extern int	mknod();
#endif /* _XOPEN_SOURCE_EXTENDED */
#endif /* _KERNEL */
	extern int	mkfifo();
#else				/* use POSIX required prototypes */
#ifndef _KERNEL
	extern int	mkdir(const char *, mode_t); 
	extern int	stat(const char *__restrict__, struct stat *__restrict__);
	extern int	fstat(int, struct stat *);
#ifdef _LARGE_FILE_API
	extern int	stat64(const char *__restrict__, struct stat64 *__restrict__);
	extern int	fstat64(int, struct stat64 *);
#endif /* _LARGE_FILE_API */

	extern int	chmod(const char *, mode_t);

#if _XOPEN_SOURCE_EXTENDED==1
	extern int	fchmod(int, mode_t);
	extern int	lstat(const char *__restrict__, struct stat *__restrict__);
#ifdef _LARGE_FILE_API
	extern int	lstat64(const char *__restrict__, struct stat64 *__restrict__);
#endif /* _LARGE_FILE_API */

	extern int	mknod(const char *, mode_t, dev_t);
#endif /* _XOPEN_SOURCE_EXTENDED */


#endif /* _KERNEL */

	extern int	mkfifo(const char *, mode_t);
#endif /* _NO_PROTO */

#endif /* _POSIX_SOURCE */

#if _XOPEN_SOURCE>=500
#define S_TYPEISMQ(x)	(0)
#define S_TYPEISSEM(x)	(0)
#define S_TYPEISSHM(x)	(0)
#endif

#ifdef _ALL_SOURCE

/*
 *	st_flag values
 */

#define	FS_VMP		01		/* file is vfs root or mounted over */
#define	FS_MOUNT	FS_VMP		/*   (vfs mount point) */
#define FS_REMOTE	02		/* file is remote */

/*
 * st_dev bit definitions
 */
#define SDEV_REMOTE	0x80000000	/* remote `device' if on	*/

/*
 *	statx() cmd arguments
 */

#define	STX_NORMAL	0x00	/* normal statx processing */
#define	STX_LINK	0x01	/* do not traverse final symbolic link */
#define	STX_MOUNT	0x02	/* do not traverse final mount point */
#define	STX_HIDDEN	0x04	/* do not traverse final hidden directory */
#define	STX_64		0x08	/* statx call is of the stat64  flavor */
#define STX_64X		0x10	/* statx call is of the stat64x flavor */

#define STATXSIZE	(sizeof(struct stat))
#define STATSIZE	(sizeof(struct stat))

/* statx and fstatx prototypes */
int statx(char *, struct stat *, int, int);
int fstatx(int, struct stat *, int, int);

#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* _H_STAT */
