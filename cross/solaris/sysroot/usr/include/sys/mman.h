/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any	*/
/*	actual or intended publication of such source code.	*/

/*
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *		PROPRIETARY NOTICE (Combined)
 *
 * This source code is unpublished proprietary information
 * constituting, or derived under license from AT&T's UNIX(r) System V.
 * In addition, portions of such source code were derived from Berkeley
 * 4.3 BSD under license from the Regents of the University of
 * California.
 *
 *
 *
 *		Copyright Notice
 *
 * Notice of copyright on this source code product does not indicate
 * publication.
 *
 *	Copyright (c) 1983,1984,1985,1986,1987,1988,1989  AT&T.
 *		All rights reserved.
 *
 */

#ifndef	_SYS_MMAN_H
#define	_SYS_MMAN_H

#pragma ident	"@(#)mman.h	1.45	05/05/17 SMI"

#include <sys/feature_tests.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Protections are chosen from these bits, or-ed together.
 * Note - not all implementations literally provide all possible
 * combinations.  PROT_WRITE is often implemented as (PROT_READ |
 * PROT_WRITE) and (PROT_EXECUTE as PROT_READ | PROT_EXECUTE).
 * However, no implementation will permit a write to succeed
 * where PROT_WRITE has not been set.  Also, no implementation will
 * allow any access to succeed where prot is specified as PROT_NONE.
 */
#define	PROT_READ	0x1		/* pages can be read */
#define	PROT_WRITE	0x2		/* pages can be written */
#define	PROT_EXEC	0x4		/* pages can be executed */

#ifdef	_KERNEL
#define	PROT_USER	0x8		/* pages are user accessable */
#define	PROT_ZFOD	(PROT_READ | PROT_WRITE | PROT_EXEC | PROT_USER)
#define	PROT_ALL	(PROT_READ | PROT_WRITE | PROT_EXEC | PROT_USER)
#endif	/* _KERNEL */

#define	PROT_NONE	0x0		/* pages cannot be accessed */

/* sharing types:  must choose either SHARED or PRIVATE */
#define	MAP_SHARED	1		/* share changes */
#define	MAP_PRIVATE	2		/* changes are private */
#define	MAP_TYPE	0xf		/* mask for share type */

/* other flags to mmap (or-ed in to MAP_SHARED or MAP_PRIVATE) */
#define	MAP_FIXED	0x10		/* user assigns address */
#define	MAP_NORESERVE	0x40		/* don't reserve needed swap area */
#define	MAP_ANON	0x100		/* map anonymous pages directly */
#define	MAP_ANONYMOUS	MAP_ANON	/* (source compatibility) */
#define	MAP_ALIGN	0x200		/* addr specifies alignment */
#define	MAP_TEXT	0x400		/* map code segment */
#define	MAP_INITDATA	0x800		/* map data segment */

/* these flags not yet implemented */
#define	MAP_RENAME	0x20		/* rename private pages to file */

#if	(_POSIX_C_SOURCE <= 2) && !defined(_XPG4_2)
/* these flags are used by memcntl */
#define	PROC_TEXT	(PROT_EXEC | PROT_READ)
#define	PROC_DATA	(PROT_READ | PROT_WRITE | PROT_EXEC)
#define	SHARED		0x10
#define	PRIVATE		0x20
#define	VALID_ATTR  (PROT_READ|PROT_WRITE|PROT_EXEC|SHARED|PRIVATE)
#endif	/* (_POSIX_C_SOURCE <= 2) && !defined(_XPG4_2) */

#if	(_POSIX_C_SOURCE <= 2) || defined(_XPG4_2)
#ifdef	_KERNEL
#define	PROT_EXCL	0x20
#define	_MAP_LOW32	0x80	/* force mapping in lower 4G of address space */
#endif	/* _KERNEL */

/*
 * For the sake of backward object compatibility, we use the _MAP_NEW flag.
 * This flag will be automatically or'ed in by the C library for all
 * new mmap calls.  Previous binaries with old mmap calls will continue
 * to get 0 or -1 for return values.  New mmap calls will get the mapped
 * address as the return value if successful and -1 on errors.  By default,
 * new mmap calls automatically have the kernel assign the map address
 * unless the MAP_FIXED flag is given.
 */
#define	_MAP_NEW	0x80000000	/* users should not need to use this */
#endif	/* (_POSIX_C_SOURCE <= 2) */

#if	!defined(_ASM) && !defined(_KERNEL)

#include <sys/types.h>

/*
 * large file compilation environment setup
 *
 * In the LP64 compilation environment, map large file interfaces
 * back to native versions where possible.
 */

#if !defined(_LP64) && _FILE_OFFSET_BITS == 64
#ifdef	__PRAGMA_REDEFINE_EXTNAME
#pragma redefine_extname	mmap	mmap64
#else
#define	mmap			mmap64
#endif
#endif /* !_LP64 && _FILE_OFFSET_BITS == 64 */

#if defined(_LP64) && defined(_LARGEFILE64_SOURCE)
#ifdef	__PRAGMA_REDEFINE_EXTNAME
#pragma	redefine_extname	mmap64	mmap
#else
#define	mmap64			mmap
#endif
#endif	/* _LP64 && _LARGEFILE64_SOURCE */

/*
 * Except for old binaries mmap() will return the resultant
 * address of mapping on success and (caddr_t)-1 on error.
 */
#ifdef	__STDC__
#if (_POSIX_C_SOURCE > 2) || defined(_XPG4_2)
extern void *mmap(void *, size_t, int, int, int, off_t);
extern int munmap(void *, size_t);
extern int mprotect(void *, size_t, int);
extern int msync(void *, size_t, int);
#if (!defined(_XPG4_2) || (_POSIX_C_SOURCE > 2)) || defined(__EXTENSIONS__)
extern int mlock(const void *, size_t);
extern int munlock(const void *, size_t);
extern int shm_open(const char *, int, mode_t);
extern int shm_unlink(const char *);
#endif	/* (!defined(_XPG4_2) || (_POSIX_C_SOURCE > 2))... */
/* transitional large file interface version */
#if	defined(_LARGEFILE64_SOURCE) && !((_FILE_OFFSET_BITS == 64) && \
	    !defined(__PRAGMA_REDEFINE_EXTNAME))
extern void *mmap64(void *, size_t, int, int, int, off64_t);
#endif	/* _LARGEFILE64_SOURCE... */
#else	/* (_POSIX_C_SOURCE > 2) || defined(_XPG4_2) */
extern caddr_t mmap(caddr_t, size_t, int, int, int, off_t);
extern int munmap(caddr_t, size_t);
extern int mprotect(caddr_t, size_t, int);
extern int msync(caddr_t, size_t, int);
extern int mlock(caddr_t, size_t);
extern int munlock(caddr_t, size_t);
extern int mincore(caddr_t, size_t, char *);
extern int memcntl(caddr_t, size_t, int, caddr_t, int, int);
extern int madvise(caddr_t, size_t, int);
#if !defined(__XOPEN_OR_POSIX) || defined(__EXTENSIONS__)
extern int getpagesizes(size_t *, int);
/* guard visibility of uint64_t */
#if defined(_INT64_TYPE)
extern int meminfo(const uint64_t *, int, const uint_t *, int, uint64_t *,
	uint_t *);
#endif /* defined(_INT64_TYPE) */
#endif /* !defined(__XOPEN_OR_POSIX) || defined(__EXTENSIONS__) */
/* transitional large file interface version */
#ifdef	_LARGEFILE64_SOURCE
extern caddr_t mmap64(caddr_t, size_t, int, int, int, off64_t);
#endif
#endif	/* (_POSIX_C_SOURCE > 2)  || defined(_XPG4_2) */

#if (!defined(_XPG4_2) || (_POSIX_C_SOURCE > 2)) || defined(__EXTENSIONS__)
extern int mlockall(int);
extern int munlockall(void);
#endif

/* mmap failure value */
#define	MAP_FAILED	((void *) -1)

#else	/* __STDC__ */
extern caddr_t mmap();
extern int munmap();
extern int mprotect();
extern int mincore();
extern int memcntl();
extern int msync();
extern int madvise();
extern int getpagesizes();
extern int mlock();
extern int mlockall();
extern int munlock();
extern int munlockall();
extern int meminfo();
/* transitional large file interface version */
#if	defined(_LARGEFILE64_SOURCE) && !((_FILE_OFFSET_BITS == 64) && \
	    !defined(__PRAGMA_REDEFINE_EXTNAME))
extern caddr_t mmap64();
#endif	/* _LARGEFILE64_SOURCE... */
#endif	/* __STDC__ */


#endif	/* !_ASM && !_KERNEL */

#if !defined(__XOPEN_OR_POSIX) || defined(__EXTENSIONS__)
#if !defined(_ASM)
/*
 * structure for memcntl hat advise operations.
 */
struct memcntl_mha {
	uint_t 		mha_cmd;	/* command(s) */
	uint_t		mha_flags;
	size_t		mha_pagesize;
};

#if defined(_SYSCALL32)
struct memcntl_mha32 {
	uint_t 		mha_cmd;	/* command(s) */
	uint_t		mha_flags;
	size32_t	mha_pagesize;
};
#endif	/* _SYSCALL32 */
#endif	/* !defined(_ASM) */
#endif	/* !defined(__XOPEN_OR_POSIX) || defined(__EXTENSIONS__) */

#if	(_POSIX_C_SOURCE <= 2) && !defined(_XPG4_2) || defined(__EXTENSIONS__)
/* advice to madvise */
#define	MADV_NORMAL		0	/* no further special treatment */
#define	MADV_RANDOM		1	/* expect random page references */
#define	MADV_SEQUENTIAL		2	/* expect sequential page references */
#define	MADV_WILLNEED		3	/* will need these pages */
#define	MADV_DONTNEED		4	/* don't need these pages */
#define	MADV_FREE		5	/* contents can be freed */
#define	MADV_ACCESS_DEFAULT	6	/* default access */
#define	MADV_ACCESS_LWP		7	/* next LWP to access heavily */
#define	MADV_ACCESS_MANY	8	/* many processes to access heavily */
#endif	/* (_POSIX_C_SOURCE <= 2) && !defined(_XPG4_2) ...  */

/* flags to msync */
#define	MS_OLDSYNC	0x0		/* old value of MS_SYNC */
					/* modified for UNIX98 compliance */
#define	MS_SYNC		0x4		/* wait for msync */
#define	MS_ASYNC	0x1		/* return immediately */
#define	MS_INVALIDATE	0x2		/* invalidate caches */

#if	(_POSIX_C_SOURCE <= 2) && !defined(_XPG4_2) || defined(__EXTENSIONS__)
/* functions to mctl */
#define	MC_SYNC		1		/* sync with backing store */
#define	MC_LOCK		2		/* lock pages in memory */
#define	MC_UNLOCK	3		/* unlock pages from memory */
#define	MC_ADVISE	4		/* give advice to management */
#define	MC_LOCKAS	5		/* lock address space in memory */
#define	MC_UNLOCKAS	6		/* unlock address space from memory */
#define	MC_HAT_ADVISE	7		/* advise hat map size */

/* sub-commands for MC_HAT_ADVISE */
#define	MHA_MAPSIZE_VA		0x1	/* set preferred page size */
#define	MHA_MAPSIZE_BSSBRK	0x2	/* set preferred page size */
					/* for last bss adjacent to */
					/* brk area and brk area itself */
#define	MHA_MAPSIZE_STACK	0x4	/* set preferred page size */
					/* processes main stack */

#endif	/* (_POSIX_C_SOURCE <= 2) && !defined(_XPG4_2) ... */

#if (!defined(_XPG4_2) || (_POSIX_C_SOURCE > 2)) || defined(__EXTENSIONS__)
/* flags to mlockall */
#define	MCL_CURRENT	0x1		/* lock current mappings */
#define	MCL_FUTURE	0x2		/* lock future mappings */
#endif /* (!defined(_XPG4_2) || (_POSIX_C_SOURCE)) || defined(__EXTENSIONS__) */

#if !defined(__XOPEN_OR_POSIX) || defined(__EXTENSIONS__)

/* definitions for meminfosys syscall */
#define	MISYS_MEMINFO		0x0

#if !defined(_ASM) && defined(__STDC__)

#if defined(_INT64_TYPE)
/* private structure for meminfo */
typedef struct meminfo {
	const uint64_t *mi_inaddr;	/* array of input addresses */
	const uint_t *mi_info_req;	/* array of types of info requested */
	uint64_t *mi_outdata;		/* array of results are placed */
	uint_t *mi_validity;		/* array of bitwise result codes */
	int mi_info_count;		/* number of pieces of info requested */
} meminfo_t;
#endif /* defined(_INT64_TYPE) */

#if defined(_SYSCALL32)
typedef struct meminfo32 {
	caddr32_t mi_inaddr;	/* array of input addresses */
	caddr32_t mi_info_req;	/* array of types of information requested */
	caddr32_t mi_outdata;	/* array of results are placed */
	caddr32_t mi_validity;	/* array of bitwise result codes */
	int32_t mi_info_count;	/* number of pieces of information requested */
} meminfo32_t;
#endif /* defined(_SYSCALL32) */

#endif /* !defined(_ASM) && defined(__STDC__) */

/*
 * info_req request type definitions for meminfo
 * request types starting with MEMINFO_V are used for Virtual addresses
 * and should not be mixed with MEMINFO_PLGRP which is targeted for Physical
 * addresses
 */
#define	MEMINFO_SHIFT		16
#define	MEMINFO_MASK		(0xFF << MEMINFO_SHIFT)
#define	MEMINFO_VPHYSICAL	(0x01 << MEMINFO_SHIFT)	/* get physical addr */
#define	MEMINFO_VLGRP		(0x02 << MEMINFO_SHIFT) /* get lgroup */
#define	MEMINFO_VPAGESIZE	(0x03 << MEMINFO_SHIFT) /* size of phys page */
#define	MEMINFO_VREPLCNT	(0x04 << MEMINFO_SHIFT) /* no. of replica */
#define	MEMINFO_VREPL		(0x05 << MEMINFO_SHIFT) /* physical replica */
#define	MEMINFO_VREPL_LGRP	(0x06 << MEMINFO_SHIFT) /* lgrp of replica */
#define	MEMINFO_PLGRP		(0x07 << MEMINFO_SHIFT) /* lgroup for paddr */

/* maximum number of addresses meminfo() can process at a time */
#define	MAX_MEMINFO_CNT	256

/* maximum number of request types */
#define	MAX_MEMINFO_REQ	31

#endif /* !defined(__XOPEN_OR_POSIX) || defined(__EXTENSIONS__) */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_MMAN_H */
