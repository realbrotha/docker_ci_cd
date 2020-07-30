/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernel/sys/types.h 1.52.1.95                            */
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
/* @(#)55       1.52.1.95  src/bos/kernel/sys/types.h, incstd, bos53J, j2006_21B0 5/15/06 07:19:40 */
/*
 *   COMPONENT_NAME: (INCSTD) Standard Include Files
 *
 *   FUNCTIONS:
 *
 *   ORIGINS: 3, 26, 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1985, 1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */
/*
 *   Copyright (c) 1982, 1986 Regents of the University of California.
 *   All rights reserved.  The Berkeley software License Agreement
 *   specifies the terms and conditions for redistribution.
 *
 *      (#)types.h     7.1 (Berkeley) 6/4/86
 */

#ifndef _H_TYPES
#define _H_TYPES

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__64BIT_KERNEL) && defined(__64BIT__) && defined(_KERNEL) && !defined(_32KERMODE)
#define __64BIT_KERNEL
#endif

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#include <strict_stdtypes.h>

#ifndef _H_INTTYPES_TYPE_TS
#include <sys/inttypes.h>
#endif

#include <end_strict_stdtypes.h>

#ifndef __ALIGN
#define __align(x)
#endif

/*
 *
 *      The ANSI and POSIX standards require that certain values be in types.h.
 *      It also requires that if _ANSI_C_SOURCE or _POSIX_SOURCE is defined
 *	then ONLY those values are present. This header includes all the ANSI
 *	and POSIX required entries.
 *
 *      Other entries are included in _ALL_SOURCE.
 *
 */

#ifdef   _ANSI_C_SOURCE
/*
 * ANSI C required typedefs
 */

#ifndef	_PTRDIFF_T
#define _PTRDIFF_T
typedef long		ptrdiff_t;
#endif

#ifndef	_WCHAR_T
#define _WCHAR_T
#ifdef __64BIT__
typedef unsigned int	wchar_t;
#else
typedef unsigned short	wchar_t;
#endif /* __64BIT__ */
#endif

#ifndef _WCTYPE_T
#define _WCTYPE_T
typedef unsigned int	wctype_t;
#endif

#ifndef _FPOS_T
#define	_FPOS_T

#ifdef _LARGE_FILES
typedef long long fpos_t;
#else
typedef long	fpos_t;
#endif /* _LARGE_FILES */

#ifdef _LARGE_FILE_API
typedef long long fpos64_t;
#endif /* _LARGE_FILE_API */

#endif /* _FPOS_T */

#ifndef	_TIME_T
#define _TIME_T
#ifdef	_LINUX_SOURCE_COMPAT
typedef long int	time_t;
#else	/* !_LINUX_SOURCE_COMPAT */
#ifdef __64BIT__
typedef long		time_t;
#else
typedef int		time_t;
#endif
#endif	/* !_LINUX_SOURCE_COMPAT */
#endif

#ifndef	_CLOCK_T
#define _CLOCK_T
typedef int		clock_t;
#endif

#ifndef	_SIZE_T
#define _SIZE_T
typedef	unsigned long	size_t;
#endif

#endif   /* _ANSI_C_SOURCE */

#ifdef   _POSIX_SOURCE
/*
 * shorthand type definitions for unsigned storage classes
 */
#ifndef _UCHAR_T
#define _UCHAR_T
typedef	unsigned char	uchar_t;
#endif /*_UCHAR_T */

typedef	unsigned short	ushort_t;
typedef	unsigned int	uint_t;
typedef unsigned long	ulong_t;

#ifndef	_SSIZE_T
#define _SSIZE_T
typedef	signed long	ssize_t;
#endif

/*
 * standard AIX type definitions
 */
typedef int		level_t;
typedef	__long64_t	daddr_t;	/* disk address */
typedef	int		daddr32_t;	/* size invariant 32-bit disk address */
#if defined(__64BIT__) || defined(_LONG_LONG)
typedef	int64_t		daddr64_t;	/* size invariant 64-bit disk address */
#endif
typedef	char *		caddr_t;	/* "core" (i.e. memory) address */
typedef	__ulong64_t	ino_t;		/* inode number (filesystem) */
typedef	uint_t 		ino32_t;	/* size invariant 32-bit inode number */
#if defined(__64BIT__) || defined(_LONG_LONG)
typedef	uint64_t 	ino64_t;	/* size invariant 64-bit inode number */
#endif
typedef short		cnt_t;
#ifdef _32KERMODE
typedef uint_t		dev_t;		/* 32bit size invariant dev_t 
					   for 32bit kernel */
#else
typedef	__ulong64_t	dev_t;		/* device number (major+minor) */
#endif
typedef uint_t 		dev32_t;	/* size invariant 32-bit devno */
#if defined(__64BIT__) || defined(_LONG_LONG)
typedef uint64_t 	dev64_t;	/* size invariant 64-bit devno */
#endif
typedef	int		chan_t;		/* channel number (minor's minor) */
typedef int		time32_t;		/* size invariant 32-bit time */
typedef int		pid32_t;		/* size invariant 32-bit pid */
typedef int		tid32_t;		/* size invariant 32-bit tid */
#if defined(__64BIT__) || defined(_LONG_LONG)
typedef uint64_t     pid64_t;     /* size invariant 64-bit pid  */
typedef uint64_t     tid64_t;     /* size invariant 64-bit tid  */
#ifndef _UNSIGNED_TIME64_T
typedef int64_t      time64_t;    /* size invariant 64-bit time */
#else /* _UNSIGNED_TIME64_T */
typedef uint64_t     time64_t;
#endif /* _UNSIGNED_TIME64_T */
#endif

/* pointer types passed across system calls */
#ifdef __64BIT__
typedef unsigned int __ptr32;
typedef unsigned int __cptr32;
#else
typedef void * __ptr32;
typedef char * __cptr32;
#endif

typedef int soff_t;			/* Unambiguous 32 bit file offset */

#ifndef _OFF_T
#define _OFF_T
#ifdef _LARGE_FILES
typedef	long long	off_t;		/* 64 bit file offset */
#else
typedef long		off_t;		/* file offset (32/64) */
#endif /* _LARGE_FILES */ 
#endif /* _OFF_T */

#ifdef _LARGE_FILE_API
typedef long long 	off64_t;
#endif  

typedef	long		paddr_t;

#ifndef _KEY_T
#define _KEY_T
/* also defined in sys/ipc.h */
typedef	int32long64_t	key_t;
#endif /*  _KEY_T */

#ifndef _TIMER_T
#define _TIMER_T
typedef __long64_t	timer_t;	/* timer id */
#endif  /* _TIMER_T */
typedef int		timer32_t;	/* size invariant 32-bit timer id */
#if defined(__64BIT__) || defined(_LONG_LONG)
typedef int64_t 	timer64_t;	/* size invariant 64-bit timer id */
#endif
typedef	short		nlink_t;

#ifndef _MODE_T
#define _MODE_T
/* also defined in sys/ipc.h */
typedef	uint_t		mode_t;		/* file mode */
#endif /*  _MODE_T */

#ifndef _UID_GID_T
#define _UID_GID_T
/* uid_t and gid_t also defined in pwd.h, and sys/ipc.h */
typedef uint_t		uid_t;		/* user ID */
typedef uint_t		gid_t;		/* group ID */
#endif /* _UID_GID_T */

typedef	__ptr32 	mid_t;		/* module ID	*/

#ifndef _PID_T
#define _PID_T
typedef	int32long64_t	pid_t;		/* process ID */
#endif /* _PID_T */

typedef __long64_t	tid_t;		/* thread ID */
typedef char		slab_t[12];	/* security label */
typedef long		mtyp_t;		/* ipc message type */
typedef int             boolean_t;
typedef int     	crid_t;

#ifdef _32KERMODE
typedef int		blkcnt_t; /* 32bit size-invariant for 32bit kernel*/
#else
#if defined(__64BIT__) || (_XOPEN_SOURCE >= 500)
typedef __long64_t	blkcnt_t; /* number of blocks in the file */
#else
typedef long		blkcnt_t; /* number of blocks in the file */
#endif
#endif /* _32KERMODE */
#if defined(__64BIT__) || (_XOPEN_SOURCE >= 500)
typedef __long64_t	blksize_t; /* used for block sizes */
#else
typedef long		blksize_t; /* used for block sizes */
#endif

typedef int		blkcnt32_t; /* size invariant 32-bit block count  */
typedef int		blksize32_t; /* size invariant 32-bit block size  */
#if defined(__64BIT__) || defined(_LONG_LONG)
typedef uint64_t	blkcnt64_t; /* size invariant 64-bit block count  */
typedef uint64_t	blksize64_t; /* size invariant 64-bit block size  */
#endif


typedef ulong_t 	fsblkcnt_t;	/* number of blocks in the FS */
typedef ulong_t		fsfilcnt_t;	/* number of files */

#ifndef _WINT_T
#define _WINT_T
	typedef	int		wint_t;		/* Wide character */
#endif

#if _XOPEN_SOURCE_EXTENDED==1
typedef uint32long64_t	id_t;		/* General ID */
typedef unsigned int	useconds_t;	/* time in microseconds */
typedef signed   int	suseconds_t;	/* signed time in microseconds */
#ifndef _CLOCKID_T
#define _CLOCKID_T
#ifdef _LONG_LONG
typedef long long       clockid_t;      /* clock ID type */
#else
typedef struct {unsigned int __a[2];} clockid_t;
#endif  /* _LONG_LONG */
#endif /* _CLOCKID_T */
#endif /* XOPEN_SOURCE_EXTENDED */

/* typedef and structure for signal mask */
/* This must correspond to the "struct sigset" structure in _ALL_SOURCE below */
typedef struct sigset_t	{
#ifdef __64BIT__
#ifdef _ALL_SOURCE
	unsigned long ss_set[4];
#else
	unsigned long __ss_set[4];
#endif
#else /* !__64BIT__ */
#ifdef _ALL_SOURCE
	unsigned int losigs;
	unsigned int hisigs;
#else
	unsigned int __losigs;
	unsigned int __hisigs;
#endif
#endif /* __64BIT__ */
} sigset_t;

typedef struct {
#ifdef _ALL_SOURCE
	unsigned int losigs, hisigs;
#else
	unsigned int __losigs, __hisigs;
#endif
} sigset32_t;

#if defined(_ALL_SOURCE) && (defined(__64BIT__) || defined(_LONG_LONG))
typedef struct {
	uint64_t ss_set[4];
} sigset64_t;
#else  /* _ALL_SOURCE && (__64BIT__ || _LONG_LONG) */
#if defined(_XOPEN_SOURCE) && defined(__64BIT__)
typedef struct {
	unsigned long __ss_set[4];
} sigset64_t;
#endif /* _XOPEN_SOURCE && __64BIT__ */
#endif /* _ALL_SOURCE && (__64BIT__ || _LONG_LONG) */

typedef int signal_t;

/* typedef for the File System Identifier (fsid).  This must correspond 
 * to the "struct fsid" structure in _ALL_SOURCE below.
 */
typedef struct fsid_t {
#ifdef __64BIT_KERNEL
	unsigned long val[2];
#else  /* __64BIT_KERNEL */
#ifdef _ALL_SOURCE
	unsigned int val[2];
#else  /* _ALL_SOURCE */
	unsigned int __val[2];
#endif /* _ALL_SOURCE */
#endif /* __64BIT_KERNEL */
} fsid_t;

#ifdef _KERNEL
typedef struct fsid32_t {
	unsigned int val[2];
} fsid32_t;
#endif /* __64BIT_KERNEL */

typedef struct fsid64_t {
#if defined(_ALL_SOURCE) && (defined(__64BIT__) || defined(_LONG_LONG))
	uint64_t val[2];
#else /* _ALL_SOURCE */
	uint32_t __val[4];
#endif /* _ALL_SOURCE */
} fsid64_t;

typedef void *pthread_attr_t;
typedef	void *pthread_condattr_t;	
typedef	void *pthread_mutexattr_t;

#if (_XOPEN_SOURCE >= 500)
typedef	void *pthread_rwlockattr_t;
#endif

#if (_XOPEN_SOURCE >= 600)	
typedef	void *pthread_barrierattr_t;
#endif 	
	
typedef unsigned int pthread_t;
typedef unsigned int pthread_key_t;

typedef struct
{
#ifdef __64BIT__
	long	__mt_word[8];
#else
	int	__mt_word[13];
#endif /* __64BIT__ */
}
pthread_mutex_t;

typedef struct
{
#ifdef __64BIT__
	long	__cv_word[6];
#else
	int	__cv_word[11];
#endif /* __64BIT__ */
}
pthread_cond_t;

typedef struct
{
#ifdef __64BIT__
        long    __on_word[9];
#else
        int     __on_word[28];
#endif /* __64BIT__ */
}
pthread_once_t;

#if (_XOPEN_SOURCE >= 600)
typedef struct
{
#ifdef __64BIT__
	long	__sp_word[3];
#else
	int	__sp_word[6];
#endif /* __64BIT__ */
}
pthread_spinlock_t;

typedef struct
{
#ifdef __64BIT__
	long	__br_word[5];
#else
	int	__br_word[8];
#endif /* __64BIT__ */
}
pthread_barrier_t;
#endif /* _XOPEN_SOURCE >= 600 */

#if (_XOPEN_SOURCE >= 500)
typedef struct
{
#ifdef __64BIT__
	long	__rw_word[10];
#else
	int	__rw_word[52];
#endif /* __64BIT__ */
}
pthread_rwlock_t;
#endif /* _XOPEN_SOURCE >= 500 */

#endif /* _POSIX_SOURCE */

#ifdef _ALL_SOURCE

typedef struct  _quad { int val[2]; } quad;


#ifndef _H_M_TYPES
#include <sys/m_types.h>		/* machine-dependent type definitions */
#endif

#ifndef	_VA_LIST
#define _VA_LIST
typedef char *		va_list;
#endif

#ifndef NULL
#define	NULL	0
#endif

#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif

#ifdef _KERNEL
/*
 * use PTR64 for non-adjacent addresses.
 * use P64 for adjacent addresses for performance.
 */
#ifdef __64BIT__
typedef void * ptr64;
typedef char * cptr64;
#else
typedef unsigned long long ptr64;
typedef unsigned long long cptr64;
#define PTR64(x,y)  (((ptr64)(x) << 32)  + (uint)(y))
#define P64(X)      ( *((ptr64 *)&(X)) )
#endif /* __64BIT__ */

#ifdef __64BIT__
typedef unsigned int ptr32;
typedef unsigned int cptr32;
#else
typedef void * ptr32;
typedef char * cptr32;
#endif /* __64BIT__ */

#endif /* _KERNEL */

#ifdef __64BIT__
typedef void * __ptr64;
typedef char * __cptr64;
#else
#ifdef	_LONG_LONG
typedef unsigned long long __ptr64;
typedef unsigned long long __cptr64;
#endif
#endif

/*
 * type definition for Unicode character code.
 */
typedef ushort_t	UniChar;
typedef uint_t		UTF32Char;

/*
 * shorthand type definitions for unsigned storage classes
 */
typedef	uchar_t		uchar;
typedef	ushort_t	ushort;
typedef	uint_t		uint;
typedef ulong_t		ulong;

typedef	struct { int r[1]; } *	physadr_t;
typedef	physadr_t	physadr;

/* typedefs for BSD unsigned things */
typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;

typedef	int	swblk_t;

#define	NBBY	8		/* number of bits in a byte */

/* The sigset structure must correspond to sigset_t in _POSIX_SOURCE above */
struct sigset	{
#ifdef __64BIT__
	unsigned long ss_set[4];
#else
	unsigned int losigs;
	unsigned int hisigs;
#endif
};

/* typedef for the File System Identifier (fsid) */
struct fsid {
#ifndef __64BIT_KERNEL
	unsigned int	val[2];
#else
	unsigned long	val[2];
#endif
};
#define	fsid_dev	val[0]
#define	fsid_type	val[1]

#ifndef _FID_64_BYTES 

#define FHSIZE		32
#define MAXFIDSZ	20

struct fileid {			/* this is for servers only! */
	uint_t	fid_len;
	ino32_t	fid_ino;
	uint_t	fid_gen;
	char	fid_x[MAXFIDSZ - (sizeof(ino32_t) + 2) - sizeof(uint_t)];
};

#else   /* ifndef _FID_64_BYTES */

#define FHSIZE          32
#define MAXFIDSZ        64

struct fileid {			/* this is for servers only! */
	uint_t	fid_len;
	ino32_t	fid_ino;
	uint_t	fid_gen;
	char	fid_x[MAXFIDSZ - sizeof(ino32_t) - sizeof(uint_t)];
};

#endif  /* ifndef _FID_64_BYTES */

struct fid {
	uint_t	fid_len;
	char	fid_data[MAXFIDSZ];
};
typedef struct fid fid_t;

/* typedef for the File Handle (fhandle) */
struct fhandle {
	char x[FHSIZE];		/* allows structure assignments */
};
typedef struct fhandle fhandle_t;

struct filehandle {			/* this is for servers only! */
	fsid_t		fh_fsid;		/* filesystem id */
	struct fileid	fh_fid;			/* file id */
};

#define fh_dev	fh_fsid.fsid_dev
#define fh_type	fh_fsid.fsid_type
#define fh_len	fh_fid.fid_len
#define fh_ino	fh_fid.fid_ino
#define fh_gen	fh_fid.fid_gen

/* structure and typedef for volume group IDs and physical volume IDs */
struct unique_id {
       __ulong32_t word1;
       __ulong32_t word2;
       __ulong32_t word3;
       __ulong32_t word4;
};
typedef struct unique_id unique_id_t;

#ifdef	_BSD			/* Berkeley source compatibility */

#ifndef _H_SELECT
#include <sys/select.h>
#endif

/*
 * The following macros, major(), minor() and makedev() are identical
 * to the macros in <sys/sysmacros.h>.  Any changes to either need to
 * be reflected in the other.
 */
/* major part of a device */
#define major(__x)        (int)((unsigned)(__x)>>16)

/* minor part of a device */
#define minor(__x)        (int)((__x)&0xFFFF)

/* make a device number */
#define makedev(__x,__y)    (dev_t)(((__x)<<16) | (__y)) 


#endif /* _BSD */

#ifdef _LONG_LONG
typedef	long long  offset_t;		/* Unambiguous 64 bit file offset */
#else
#ifdef __64BIT__
typedef long offset_t;
#else
typedef quad	offset_t;
#endif
#endif	/* _LONG_LONG */

#ifdef _LONG_LONG
typedef long long ssize64_t;
#else
typedef quad	ssize64_t;
#endif  /* _LONG_LONG */

#ifdef _LONG_LONG
typedef long long longlong_t;         
typedef unsigned long long u_longlong_t;
#endif /* _LONG_LONG */

typedef unsigned int class_id_t;


/* some data types used by vdevices and others */
typedef uint_t          liobn_t;       /* Logical I/O Bus Number of a vdevice */
#ifdef _LONG_LONG
typedef unsigned long long unit_addr_t;   /* Unit address of the vdevice      */
#else
typedef quad	unit_addr_t;		/* Unit address of the vdevice	*/
#endif /* _LONG_LONG */
#endif   /* _ALL_SOURCE */

#ifdef _LONG_LONG
typedef unsigned long long size64_t;    
#else
typedef struct {unsigned int __a[2];} size64_t;
#endif  /* _LONG_LONG */


#ifdef __cplusplus
}
#endif

#endif /* _H_TYPES */
