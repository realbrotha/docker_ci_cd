/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/file.h 1.34.1.4                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1985,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)93     1.34.1.4  src/bos/kernel/sys/file.h, syslfs, bos53X, x2009_45A2 10/28/09 10:06:59 */
#ifndef _H_FILE
#define _H_FILE

/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27, 3, 26
 *
 */

#include <sys/types.h>
#include <sys/param.h>
#include <sys/access.h>
#include <sys/lock_def.h>
#include <sys/cred.h>
#include <sys/uio.h>
#include <fcntl.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KERNEL
struct f_path {
	short ncindex;
	char  pathstring[1];
};

/*
 * One file structure is allocated for each open/creat/pipe call.
 * Main use is to hold the read/write pointer associated with
 * each open file.
 */
struct	file {
	long	f_flag;		/* see fcntl.h for definitions */
	int	f_count;  	/* reference count */
	short	f_options;	/* file flags not passed through vnode layer */
	short	f_type;		/* descriptor type */
	union {
		struct vnode	*f_uvnode;	/* pointer to vnode structure */
		struct file	*f_unext;	/* next entry in freelist */
	} f_up;
	offset_t f_offset;	/* read/write character pointer */
	off_t	f_dir_off;	/* BSD style directory offsets */
	union {
		struct ucred *f_cpcred;		/* process credentials at */
						/* time of open */
		struct file  *f_cpqmnext;	/* next quick move chunk on */
						/* free list */
	} f_cp;
	Simple_lock f_lock;	/* file structure fields lock */
	Simple_lock f_offset_lock; /* file structure offset field lock */
	caddr_t	f_vinfo;	/* any info vfs needs */ 
	struct fileops
	{
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
		int	(*fo_rw)(struct file *, enum uio_rw, struct uio *, 
					ext_t);
		int	(*fo_ioctl)(struct file *, long, caddr_t, ext_t, long);
		int	(*fo_select)(struct file *, int, ushort, ushort *,
					void (*)());
		int	(*fo_close)(struct file *);
		int	(*fo_fstat)(struct file *, struct stat *);
#else
		int	(*fo_rw)();
		int	(*fo_ioctl)();
		int	(*fo_select)();
		int	(*fo_close)();
		int	(*fo_fstat)();
#endif /* __64BIT_KERNEL || __FULL_PROTO */
	} *f_ops;
	struct f_path	*f_pathp;	/* file's full path for auditing */
};

#define	f_data		f_up.f_uvnode
#define	f_vnode		f_up.f_uvnode
#define	f_next		f_up.f_unext
#define f_cred		f_cp.f_cpcred
#define f_qmnext	f_cp.f_cpqmnext

/* f_type values */

#define	DTYPE_VNODE	1	/* file */
#define	DTYPE_SOCKET	2	/* communications endpoint */
#define	DTYPE_GNODE	3	/* device */
#define	DTYPE_RTSHM	4	/* posix rt shm */
#define	DTYPE_OTHER    -1	/* unknown */

/* defines for f_options -- file flags that don't need to be
 * passed through the vnode layer
 */
#define FAIO		0x0001		/* aio on this fp		*/
#define GCFMARK		0x0002		/* mark during unp_gc()		*/
#define GCFDEFER	0x0004		/* defer during unp_gc()	*/
#define FREVOKED	0x0008		/* file access has been revoked	*/
#define FAIO_FPATH	0x0010		/* Send down aio fast path	*/
#define FAIO_KPROC	0x0020		/* Send aio request to kproc	*/
#define FAIO_FSFP	0x0040		/* Send down aio fs fast path	*/
#define FAIO_FPVPATH	0x0080		/* fast path aio to PV          */
#define FOBIT8		0x0100
#define FOBIT9		0x0200
#define FOBIT10		0x0400
#define FOBIT11		0x0800
#define FOBIT12		0x1000
#define FOBIT13		0x2000
#define FOBIT14		0x4000
#define FZOMBIE		0x8000		/* fp is dead but not yet free	*/

#ifdef __64BIT_KERNEL
extern struct file *file;	/* The file table itself */
#else
extern struct file file[];	/* The file table itself */
#endif /* __64BIT_KERNEL */
extern struct file *ffreelist;	/* Head of freelist pool */
extern Simple_lock ffree_lock;	/* File Table Free List Lock */
#endif /* _KERNEL */

/*
 * Flock call.
 */
#define	LOCK_SH		1	/* shared lock */
#define	LOCK_EX		2	/* exclusive lock */
#define	LOCK_NB		4	/* don't block when locking */
#define	LOCK_UN		8	/* unlock */

/*
 * Lseek call.
 */
#define	L_SET		0	/* absolute offset */
#define	L_INCR		1	/* relative to current offset */
#define	L_XTND		2	/* relative to end of file */




#ifdef _KERNEL
/* Definitions for named opens */
struct named_open_args {
	int		no_magic;	/* Magic number */
	struct vnode	*no_dvp;	/* Directory vnode */
	char		*no_path;	/* (full) Path name */
};
#define NAMED_OPEN_MAGIC 0x1badd00d
#endif

#ifdef _NO_PROTO
extern int flock();
#else
extern int flock(int,int);
#endif /*_NO_PROTO*/


#ifdef __cplusplus
}
#endif

#endif /* _H_FILE */
