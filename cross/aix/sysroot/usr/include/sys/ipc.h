/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/sys/ipc.h 1.26                                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1987,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)17       1.26  src/bos/kernel/sys/ipc.h, sysipc, bos53H, h2005_39C6 9/12/05 15:06:49 */
/*
 * COMPONENT_NAME: (SYSIPC) IPC Message Facility
 *
 * FUNCTIONS:
 *
 * ORIGINS: 3,27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1987, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _H_IPC
#define _H_IPC

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _XOPEN_SOURCE

#ifndef _H_TYPES
#include <sys/types.h>
#endif

/* Common IPC Structures */
struct ipc_perm {
	uid_t		uid;		/* owner's user id	*/
	gid_t		gid;		/* owner's group id	*/
	uid_t		cuid;		/* creator's user id	*/
	gid_t		cgid;		/* creator's group id	*/
	mode_t		mode;		/* access modes		*/
	unsigned short	seq;		/* slot usage sequence number */
	key_t		key;		/* key			*/
};

/* common IPC operation flag definitions */

#define	IPC_CREAT	0020000		/* create entry if key doesn't exist*/

#define	IPC_EXCL	0002000		/* fail if key exists */
#define	IPC_NOWAIT	0004000		/* error if request must wait */

/* Keys. */
#define	IPC_PRIVATE	(key_t)-1	/* private key */

/* Control Commands. */
#define	IPC_RMID	0	/* remove identifier */
#define	IPC_SET		101	/* set options */
#define IPC_STAT	102	/* get options */


#if _XOPEN_SOURCE_EXTENDED==1
#ifdef _NO_PROTO
key_t	ftok();
#else /* _NO_PROTO */
key_t	ftok(const char *, int);
#endif /* _NO_PROTO */
#endif /* _XOPEN_SOURCE_EXTENDED */

#endif /* _XOPEN_SOURCE */

#ifdef _ALL_SOURCE

/* Common ipc_perm mode Definitions. */
#define	IPC_ALLOC	0100000		/* entry currently allocated        */
#define	IPC_R		0000400		/* read or receive permission       */
#define	IPC_W		0000200		/* write or send permission	    */

/* common IPC operation flag definitions */
#define IPC_NOERROR	0010000		/* truncates a message if too long */

/*
 * control commands specific to shared memory;
 * commands [200,299] are reserved for shared memory options to shmctl()
 */
#define SHM_SIZE	6       /* change segment size (shared mem only)*/
#define SHM_PAGESIZE    200     /* change a shm region's page size */
#define SHM_LOCK        201     /* pin the pages in a shm region */
#define SHM_UNLOCK      202     /* unpin the pages in a shm region */
#define SHM_GETLBA	203	/* query the SHMLBA needed for shm region */

#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif
#endif /* _H_IPC */
