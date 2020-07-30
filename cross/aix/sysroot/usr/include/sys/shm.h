/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/shm.h 1.65                                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1987,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)13     1.65  src/bos/kernel/sys/shm.h, sysipc, bos53L, l2006_41B2 10/6/06 10:30:15 */
/*
 * COMPONENT_NAME: (SYSIPC) IPC Shared Memory Facility
 *
 * ORIGINS: 3,27
 *
 */

#ifndef _H_SHM
#define _H_SHM

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifndef _H_IPC
#include <sys/ipc.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ALL_SOURCE
#include <sys/seg.h>
#endif /* _ALL_SOURCE */

#ifdef _XOPEN_SOURCE

#ifndef _H_TYPES
#include <sys/types.h>
#endif

/*
 *	Implementation Constants.
 */

#define SHMLBA  (0x10000000)	/* segment low boundary address multiple */
				/* (SHMLBA must be a power of 2) */
#define SHMLBA_EXTSHM	(0x1000)	/* for use when env var EXTSHM=ON */

/*
 *	Operation Flags.
 */
#define SHM_SHMAT       0x80000000      /* shmat() file */

#define	SHM_RDONLY	010000	/* attach read-only (else read-write) */
#define	SHM_RND		020000	/* round attach address to SHMLBA */

/* 
 * shmget flag - pin the region and use large pages  - advisory only
 */ 
#define SHM_PIN         004000 
#define SHM_LGPAGE	020000000000	/* only available with SHM_PIN */

/*
 *	Structure Definitions.
 */

/*
 *      There is a shared mem id data structure for each shared memory
 *      and mapped file segment in the system.
 */


#ifdef __64BIT__
typedef unsigned long	shmatt_t;
#else
typedef unsigned short	shmatt_t;
#endif

struct shmid_ds {
	struct ipc_perm	shm_perm;	/* operation permission struct */
	size_t		shm_segsz;	/* segment size */
	pid_t		shm_lpid;	/* pid of last shmop */
	pid_t		shm_cpid;	/* pid of creator */
	shmatt_t	shm_nattch;	/* current # attached */
#ifdef _ALL_SOURCE
	shmatt_t	shm_cnattch;	/* in memory # attached */
#else
	shmatt_t	__shm_cnattch;	/* in memory # attached */
#endif
	time_t		shm_atime;	/* last shmat time */
	time_t		shm_dtime;	/* last shmdt time */
	time_t		shm_ctime;	/* last change time */
#ifdef _ALL_SOURCE
	__ulong32_t	shm_handle;	/* segment identifier */
	int		shm_extshm;	/* page granularity shmat */
	int64_t         shm_pagesize;   /* page size backing shm region */
	uint64_t        shm_lba;	/* segment low boundary address */
	int64_t         shm_reserved0;
	int64_t         shm_reserved1;
#else
	__ulong32_t	__shm_handle;	/* segment identifier */
	int		__shm_extshm;	/* page granularity shmat */
	int64_t         __shm_pagesize; /* page size backing shm region */
	uint64_t        __shm_lba;	/* segment low boundary address */
	int64_t         __shm_reserved0;
	int64_t         __shm_reserved1;
#endif
};


#ifdef _NO_PROTO
extern int   shmget();
extern void *shmat();
extern int   shmdt();
extern int   shmctl();
#else
extern int   shmget(key_t, size_t, int);
extern void *shmat(int, const void *, int);
extern int   shmdt(const void *);
extern int   shmctl(int, int, struct shmid_ds *);
#endif /* _NO_PROTO */

#endif /* _XOPEN_SOURCE */

#ifdef _ALL_SOURCE

#ifdef _NO_PROTO
extern int disclaim();
extern int disclaim64();
#else
extern int disclaim(char *, unsigned int, unsigned int);
extern int disclaim64(void *, size_t, unsigned long);
#endif /* _NO_PROTO */
#define ZERO_MEM		1		/* for disclaim		*/
#define DISCLAIM_ZEROMEM	ZERO_MEM	/* for disclaim		*/

#define SHM_MAP         004000  /* map a file instead of share a segment */
#define SHM_FMAP        002000  /* fast file map			 */
#define SHM_COPY	040000	/* deferred update. Should use O_DEFER	 */

#define SHM_CLEAR	0	/* this is going away			*/

#define SHMHISEG        (14u)
#define SHMDSAHISEG	(15u)
#define SHMLOSEG        (3u)
#define NSHMSEGS        (SHMHISEG-SHMLOSEG)	/* segment 13 unavailable */
						/* used for shared libs */

#ifndef _H_M_SHM
#include <sys/m_shm.h>	/* machine-dependent definitions */
#endif /* _H_M_SHM */

/*
 *	ipc_perm Mode Definitions.
 */
#define	SHM_R		IPC_R	/* read permission */
#define	SHM_W		IPC_W	/* write permission */
#define	SHM_DEST	02000	/* destroy segment when # attached = 0 */


struct	shminfo {
	unsigned long long shmmax;	/* max shared memory segment size */
	int		shmmin,	/* min shared memory segment size */
			shmmni;	/* # of shared memory identifiers */
};
#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif
#endif /* _H_SHM */
