/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/usr/include/fcntl.h 1.39.1.21                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)69     1.39.1.21  src/bos/usr/include/fcntl.h, syslfs, bos53H, h2006_07C4 2/9/06 10:45:37 */
/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 */
#ifndef _H_FCNTL
#define _H_FCNTL

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>

/*
 * All of the file flags are defined here.  O_ flags and F flags will
 * be defined based on these values.
 */

#define	_FREAD		0x00000001
#define	_FWRITE		0x00000002
#define	_FNONBLOCK	0x00000004
#define	_FAPPEND	0x00000008
#define	_FSYNC		0x00000010
#define	_FEXEC		0x00000020
#define	_FSNAPSHOT	0x00000040
#define	_FCIO		0x00000080
#define	_FCREAT		0x00000100
#define	_FTRUNC		0x00000200
#define	_FEXCL		0x00000400
#define	_FNOCTTY	0x00000800
#define	_FRSHARE	0x00001000
#define	_FDEFER		0x00002000
#define	_FDELAY		0x00004000
#define	_FNDELAY	0x00008000
#define	_FNSHARE	0x00010000
#define	_FASYNC		0x00020000
#define	_FMOUNT		0x00040000
#define	_FSYNCALL	0x00080000
#define	_FNOCACHE	0x00100000
#define	_FREADSYNC	0x00200000
#define	_FDATASYNC	0x00400000
#define	_FDEFERIND	0x00800000
#define	_FDATAFLUSH	0x01000000
#define	_FCLREAD	0x02000000
#define	_FLARGEFILE	0x04000000
#define	_FDIRECT	0x08000000
#define	_FDOCLONE	0x10000000
#define	_FALT		0x20000000
#define	_FKERNEL	0x40000000
#define	_FMSYNC		0x80000000

#define _FMPX		0

/*
 * POSIX requires that certain values be included in fcntl.h and that only
 * these values be present when _POSIX_SOURCE is defined.  This header
 * includes all the POSIX required entries.
 */

#ifdef _POSIX_SOURCE

#ifndef _H_FLOCK
#include <sys/flock.h>     /* for flock structure */
#endif

/* Redefine open and creat for large file enabled programming environment. */

#ifdef _LARGE_FILES
#define open	open64
#define	creat	creat64
#endif

#ifdef _NO_PROTO
extern int open();
extern int creat();
extern int fcntl();

#else 		/* use POSIX required prototypes */
#ifndef _KERNEL
extern int open(const char *, int, ...);
extern int creat(const char *, mode_t);
#ifdef _LARGE_FILE_API
extern int open64(const char *, int, ...);
extern int creat64(const char *, mode_t);
#endif
extern int fcntl(int, int,...);
#endif /* _KERNEL */
#endif /* _NO_PROTO */

/* File access modes for open */
#define	O_RDONLY	0
#define	O_WRONLY	1
#define	O_RDWR		2

/* Mask for use with file access modes */
#define O_ACCMODE	3		

/* File flags accessible to open and fcntl */
#define O_NONBLOCK	_FNONBLOCK	/* POSIX non-blocking I/O	*/
#define	O_APPEND	_FAPPEND  	/* all writes append to the end	*/
 
/* Flag flags accessible only to open */
#define	O_CREAT		_FCREAT		/* open with creation		*/
#define	O_TRUNC		_FTRUNC		/* open with truncation		*/
#define	O_EXCL		_FEXCL		/* exclusive open		*/
#define O_NOCTTY	_FNOCTTY	/* do not assign control tty	*/
#ifdef _LARGE_FILE_API
#define O_LARGEFILE	_FLARGEFILE	/* large file access enabled	*/
#endif 

/* fcntl requests */
#define	 F_DUPFD	0		/* Duplicate file descriptor	*/
#define	 F_GETFD	1		/* Get file descriptor flags	*/
#define	 F_SETFD	2		/* Set file descriptor flags	*/
#define	 F_GETFL	3		/* Get file flags		*/
#define	 F_SETFL	4		/* Set file flags		*/

#if defined(__64BIT_KERNEL) || !(defined(_LARGE_FILES) || defined(__64BIT__))
#define	 F_GETLK	5		/* Get file lock		*/
#define	 F_SETLK	6		/* Set file lock		*/
#define	 F_SETLKW	7		/* Set file lock and wait	*/
#endif

#define	 F_DUP2FD	14		/* Duplicate file descriptor	*/

#define  F_GETLK64	11
#define	 F_SETLK64	12
#define	 F_SETLKW64	13

#if !defined(__64BIT_KERNEL) && (defined(_LARGE_FILES) || defined(__64BIT__))
#define	 F_GETLK	F_GETLK64	/* Get file lock	   */
#define	 F_SETLK	F_SETLK64	/* Set file lock	   */
#define	 F_SETLKW	F_SETLKW64	/* Set file lock and wait  */
#endif 

/* File descriptor flags used for fcntl F_GETFD and F_SETFD */
#define FD_CLOEXEC      1		/* Close this file during exec	*/

#if _POSIX_C_SOURCE >= 200112L
extern int posix_fadvise(int,off_t,off_t,int);
#define POSIX_FADV_NORMAL	1
#define POSIX_FADV_SEQUENTIAL	2
#define POSIX_FADV_RANDOM	3
#define POSIX_FADV_WILLNEED	4
#define POSIX_FADV_DONTNEED	5
#define POSIX_FADV_NOREUSE	6
extern int posix_fallocate(int,off_t,off_t);
#endif /* _POSIX_C_SOURCE >= 200112L */


#endif /* _POSIX_SOURCE */

#ifdef _XOPEN_SOURCE

#ifndef _H_UNISTD
#include <unistd.h>
#endif

#ifndef _H_STAT
#include <sys/stat.h>
#endif

#define O_SYNC		_FSYNC		/* synchronous write option	*/
#endif /* _XOPEN_SOURCE */

#if _XOPEN_SOURCE_EXTENDED == 1
#define	 F_GETOWN	8		/* Get async I/O owner		*/
#define	 F_SETOWN	9		/* Set async I/O owner		*/
#endif

#if _XOPEN_SOURCE >= 500
#define O_DSYNC		_FDATASYNC	/* sync-write, data only	    */
#define O_RSYNC		_FREADSYNC	/* atime synced before read returns */
#endif


#ifdef _ALL_SOURCE

#ifdef _NO_PROTO
extern int openx();
#else
#ifndef _KERNEL
#ifndef __64BIT__
extern int openx(char *path, int oflag, ...);
#else
extern int openx(char *path, int oflag, mode_t, long);
#endif /* __64BIT__ */
#endif /* !_KERNEL */
#endif /* _NO_PROTO */

/* Additional open modes */

#define	O_NONE		3		/* open without read or write	*/
#define O_EXEC		_FEXEC		/* open for exec		*/
#define O_RSHARE	_FRSHARE	/* read shared open		*/
#define O_DEFER		_FDEFER		/* defered update		*/
#define O_DELAY		_FDELAY		/* open with delay		*/
#define O_NDELAY	_FNDELAY	/* Non-blocking I/O		*/
#define O_NSHARE	_FNSHARE	/* read shared open		*/
#define O_NOCACHE	_FNOCACHE	/* file data not cached		*/
#define O_DIRECT	_FDIRECT	/* open for direct io		*/
#define O_SNAPSHOT	_FSNAPSHOT	/* open cooked snapshot         */
#define O_CIO   	_FCIO   	/* open for concurrent io	*/

/* Additional fcntl requests */

#define  F_CLOSEM	10		/* Close multiple files		*/

/* Additional fcntl F_SETFL flags */

#ifndef _KERNEL
#ifdef	_BSD
/* Provide appropriate definition of FNDELAY for BSD */
#define	FNDELAY		_FNONBLOCK
#undef	O_NDELAY
#define	O_NDELAY	_FNONBLOCK
#else	/* System V */
#define	FNDELAY		_FNDELAY
#endif	/* _BSD */
#endif	/* _KERNEL */

#define	FNONBLOCK 	_FNONBLOCK
#define	FAPPEND		_FAPPEND
#define	FSYNC		_FSYNC
#define FASYNC		_FASYNC
#define FSYNCALL	_FSYNCALL

/* File flag values corresponding to file access modes */

#define	FOPEN		(-1)
#define	FREAD		_FREAD
#define	FWRITE		_FWRITE

#ifdef _KERNEL

#define	FMPX		_FMPX		/* multiplexed open, obsolete	*/

/* FFCNTL is all the bits that may be set via fcntl. */
#define	FFCNTL		(FNONBLOCK|FNDELAY|FAPPEND|FSYNC|FASYNC|FLARGEFILE|\
			FDATASYNC|FREADSYNC|FNOCACHE)

/* open only modes */
#define	FCREAT		_FCREAT
#define	FTRUNC		_FTRUNC
#define	FEXCL		_FEXCL

#define FRSHARE 	_FRSHARE
#define FDEFER		_FDEFER
#define FDELAY		_FDELAY
#define FNDELAY		_FNDELAY
#define FNSHARE		_FNSHARE
#define	FLARGEFILE	_FLARGEFILE
#define FREADSYNC	_FREADSYNC
#define FNOCACHE	_FNOCACHE
#define FDIRECT		_FDIRECT
#define FSNAPSHOT	_FSNAPSHOT
#define FCIO   		_FCIO

/* additional modes */
#define	FEXEC		_FEXEC		/* open/close for exec		*/
#define	FNOCTTY		_FNOCTTY	/* do not assign control tty	*/
#define	FMOUNT		_FMOUNT		/* open/close for device mounts */
#define	FKERNEL		_FKERNEL	/* caller is in kernel mode	*/
#define FDOCLONE	_FDOCLONE	/* reserve DDOCLONE for devices	*/
#define	FFILESYNC	_FSYNC		/* another name for FSYNC	*/
#define	FDATASYNC	_FDATASYNC	/* fsync data only		*/
#define	FDEFERIND	_FDEFERIND	/* defer indirect on fsync	*/
#define	FDATAFLUSH	_FDATAFLUSH	/* async flush on write		*/
#define	FCLREAD		_FCLREAD	/* clustered read (temporary)	*/
#define FMSYNC		_FMSYNC		/* msync semantics for 		*/
				 	/*     vnop_fsync_range		*/
#define	FNOWRBEHIND	_FCLREAD	/* do not write behind optimize */
#define FALT		_FALT		/* apply alternate flag meaning	*/

/* FMASK defines the bits that remain in the file flags past the open	*/
#define	FMASK		(FREAD|FWRITE|FNONBLOCK|FAPPEND|FSYNC|FEXEC|FNOCTTY|\
		 FRSHARE|FDEFER|FDELAY|FNDELAY|FNSHARE|FLARGEFILE|FDATASYNC|\
		 FREADSYNC|FNOCACHE|FDIRECT|FCIO)

#endif	/* _KERNEL	*/
#endif	/* _ALL_SOURCE	*/
#endif	/* _H_FCNTL	*/
