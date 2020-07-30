/*
 * Copyright 2003 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
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
 *	Copyright (c) 1983-1989 by AT&T.
 *	All rights reserved.
 */

#ifndef	_SYS_SHM_H
#define	_SYS_SHM_H

#pragma ident	"@(#)shm.h	1.50	03/12/04 SMI"

#include <sys/ipc.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 *	IPC Shared Memory Facility.
 */

/*
 *	Implementation Constants.
 */
#if (defined(_KERNEL) || defined(_KMEMUSER))

#define	SHMLBA	PAGESIZE	/* segment low boundary address multiple */
				/* (SHMLBA must be a power of 2) */
#else
#include <sys/unistd.h>		/* needed for _SC_PAGESIZE */
extern long _sysconf(int);	/* System Private interface to sysconf() */
#define	SHMLBA	(_sysconf(_SC_PAGESIZE))
#endif	/* defined(_KERNEL) || defined(_KMEMUSER)) */

/*
 *	Permission Definitions.
 */
#define	SHM_R	0400	/* read permission */
#define	SHM_W	0200	/* write permission */

/*
 *	Message Operation Flags.
 */
#define	SHM_RDONLY	010000	/* attach read-only (else read-write) */
#define	SHM_RND		020000	/* round attach address to SHMLBA */
#define	SHM_SHARE_MMU	040000  /* share VM resources such as page table */
#define	SHM_PAGEABLE	0100000 /* pageable ISM */

/*
 * Valid flags bits for shmat shmflag argument.
 */
#define	SHMAT_VALID_FLAGS_MASK		\
	(SHM_R | SHM_W | SHM_RDONLY | SHM_RND | SHM_SHARE_MMU | SHM_PAGEABLE)

typedef unsigned long shmatt_t;

/*
 *	Structure Definitions.
 */
struct shmid_ds {
	struct ipc_perm	shm_perm;	/* operation permission struct */
	size_t		shm_segsz;	/* size of segment in bytes */
#if defined(_LP64) || defined(_XOPEN_SOURCE)
	void		*shm_amp;
#else
	struct anon_map	*shm_amp;	/* segment anon_map pointer */
#endif
	ushort_t	shm_lkcnt;	/* number of times it is being locked */
	pid_t		shm_lpid;	/* pid of last shmop */
	pid_t		shm_cpid;	/* pid of creator */
	shmatt_t	shm_nattch;	/* number of attaches */
	ulong_t		shm_cnattch;	/* number of ISM attaches */
#if defined(_LP64)
	time_t		shm_atime;	/* last shmat time */
	time_t		shm_dtime;	/* last shmdt time */
	time_t		shm_ctime;	/* last change time */
	int64_t		shm_pad4[4];	/* reserve area */
#else	/* _LP64 */
	time_t		shm_atime;	/* last shmat time */
	int32_t		shm_pad1;	/* reserved for time_t expansion */
	time_t		shm_dtime;	/* last shmdt time */
	int32_t		shm_pad2;	/* reserved for time_t expansion */
	time_t		shm_ctime;	/* last change time */
	int32_t		shm_pad3;	/* reserved for time_t expansion */
	int32_t		shm_pad4[4];	/* reserve area  */
#endif	/* _LP64 */
};

/*
 * Shared memory control operations
 */
#define	SHM_LOCK	3	/* Lock segment in core */
#define	SHM_UNLOCK	4	/* Unlock segment */

#if !defined(_KERNEL)
#if defined(__STDC__)
int shmget(key_t, size_t, int);
int shmids(int *, uint_t, uint_t *);
int shmctl(int, int, struct shmid_ds *);
void *shmat(int, const void *, int);
#if defined(_XPG4)
int shmdt(const void *);
#else
int shmdt(char *);
#endif /* defined(_XPG4) */
#else /* __STDC__ */
int shmctl();
int shmget();
int shmids();
void *shmat();
int shmdt();
#endif /* __STDC__ */
#endif /* !defined(_KERNEL) */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_SHM_H */
