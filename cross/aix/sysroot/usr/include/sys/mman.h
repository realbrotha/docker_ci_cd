/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/mman.h 1.21                                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1991,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)35       1.21  src/bos/kernel/sys/mman.h, sysvmm, bos530 2/6/04 08:29:36 */
/*
 * COMPONENT_NAME: (SYSVMM) Virtual Memory Manager
 *
 * FUNCTIONS:
 *
 * ORIGINS: 65 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1991, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * (c) Copyright 1990, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * OSF/1 Release 1.0
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)mman.h	7.1 (Berkeley) 6/4/86
 */
#ifndef	_H_MMAN
#define _H_MMAN

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>	
	
#ifdef _POSIX_SOURCE
	
#if _POSIX_C_SOURCE >= 200112L
extern int posix_madvise(void *,size_t,int);
#define POSIX_MADV_NORMAL       1
#define POSIX_MADV_SEQUENTIAL   2
#define POSIX_MADV_RANDOM       3
#define POSIX_MADV_WILLNEED     4
#define POSIX_MADV_DONTNEED     5
#endif /* _POSIX_C_SOURCE >= 200112L */	
	
#endif
	
#if _XOPEN_SOURCE_EXTENDED==1
#include <sys/types.h>

#ifdef _LARGE_FILES
#define mmap 	mmap64
#endif	/* _LARGE_FILES */

/* protections are chosen from these bits, or-ed together */
/* flags contain sharing type, mapping type, and options */
/* protections are chosen from these bits, or-ed together */
#define PROT_NONE	0		/* no access to these pages */
#define PROT_READ	0x1		/* pages can be read */
#define PROT_WRITE	0x2		/* pages can be written */
#define PROT_EXEC	0x4		/* pages can be executed */

/* mapping visibility: choose either SHARED or PRIVATE */
#define MAP_SHARED	0x1		/* share changes */
#define MAP_PRIVATE	0x2		/* changes are private */

/* mapping placement: choose either FIXED or VARIABLE */
#define	MAP_FIXED	0x100		/* map addr must be exactly as specified */
#define	MAP_VARIABLE	0x00		/* system can place new region */

/* msync flags */
#define MS_ASYNC	0x10	/* Asynchronous cache flush */
#define MS_SYNC		0x20	/* Synchronous cache flush */
#define MS_INVALIDATE	0x40	/* Invalidate cached pages */
#define MS_EINTR     	0x80    /* Flag for EINTR return code*/

/* For the IEEE POSIX 1003.1c Realtime option */
#define MCL_CURRENT	0x00000100
#define MCL_FUTURE	0x00000200
#define MAP_FAILED      ((void *)-1)

#if defined(_NO_PROTO)
	extern int      mlock();
	extern int      munlock();
	extern int      mlockall();
	extern int      munlockall();
#else
	extern int      mlock(const void *, size_t);
	extern int      munlock(const void *, size_t);
	extern int      mlockall(int);
	extern int      munlockall(void);
#endif

#if defined(_NO_PROTO) || defined(_KERNEL)

#ifdef _KERNEL
	extern caddr_t	mmap();
#else
	extern void	*mmap();
#endif	/* _KERNEL */

	extern int	mprotect();
	extern int	msync();
	extern int	munmap();
	extern int      shm_open();
	extern int      shm_unlink();
#else
	extern void	*mmap(void *, size_t, int, int, int, off_t);
	extern int	mprotect(void *, size_t, int);
	extern int	msync(void *, size_t, int);
	extern int	munmap(void *, size_t);
#ifdef _LARGE_FILE_API
	extern void	*mmap64(void *, size_t, int, int, int, off64_t);
#endif
	extern int      shm_open(const char *, int, mode_t);
	extern int      shm_unlink(const char *);
#endif /* _NO_PROTO */
#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _ALL_SOURCE

/* flags contain sharing type, mapping type, and options */
/* mapping region: choose either FILE or ANONYMOUS */
#define	MAP_FILE	0x00		/* map from a file */
#define	MAP_ANONYMOUS	0x10		/* map an unnamed region */
#define	MAP_ANON	0x10		/* map an unnamed region */
#define	MAP_TYPE	0xf0		/* the type of the region */


/* advice to madvise */
#define MADV_NORMAL	0		/* no further special treatment */
#define MADV_RANDOM	1		/* expect random page references */
#define MADV_SEQUENTIAL	2		/* expect sequential page references */
#define MADV_WILLNEED	3		/* will need these pages */
#define MADV_DONTNEED	4		/* dont need these pages */
#define	MADV_SPACEAVAIL	5		/* ensure that resources are available */

/* msem conditions and structure */
typedef struct {
	int msem_state;		/* The semaphore is locked if non-zero. */
	int msem_wanted;	/* Processes are waiting on the semaphore. */
}msemaphore;

#define MSEM_UNLOCKED 	0	/* Initialize the semaphore to unlocked */
#define MSEM_LOCKED 	1	/* Initialize the semaphore to locked */
#define MSEM_IF_NOWAIT	2	/* Do not wait if semaphore is locked */
#define MSEM_IF_WAITERS	3	/* Unlock only if there are waiters */
#define MSEM_REMOVED	4	/* The semaphore is being removed */

#if !defined(_NO_PROTO) && !defined(_KERNEL)

	extern int		madvise(caddr_t, size_t, int);
	extern int		mincore(caddr_t, size_t, char *);
	extern msemaphore 	*msem_init(msemaphore *, int);
	extern int		msem_lock(msemaphore *, int);
	extern int		msem_remove(msemaphore *);
	extern int		msem_unlock(msemaphore *, int);

#else /* _NO_PROTO || _KERNEL */

	extern int		madvise();
	extern int		mincore();
	extern msemaphore 	*msem_init();
	extern int		msem_lock();
	extern int		msem_remove();
	extern int		msem_unlock();

#endif /* _NO_PROTO || _KERNEL */

#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif

#endif	/* _H_MMAN */
