/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
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

#ifndef	_VM_SEG_VN_H
#define	_VM_SEG_VN_H

#pragma ident	"@(#)seg_vn.h	1.55	05/05/17 SMI"
/*	From:	SVr4.0	"kernel:vm/seg_vn.h	1.7"		*/

#include <sys/lgrp.h>
#include <vm/anon.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * A pointer to this structure is passed to segvn_create().
 */
typedef struct segvn_crargs {
	struct	vnode *vp;	/* vnode mapped from */
	struct	cred *cred;	/* credentials */
	u_offset_t	offset; /* starting offset of vnode for mapping */
	uchar_t	type;		/* type of sharing done */
	uchar_t	prot;		/* protections */
	uchar_t	maxprot;	/* maximum protections */
	uint_t	flags;		/* flags */
	struct	anon_map *amp;	/* anon mapping to map to */
	uint_t	szc;		/* max preferred page size code */
	uint_t	lgrp_mem_policy_flags;
} segvn_crargs_t;

/*
 * (Semi) private data maintained by the seg_vn driver per segment mapping.
 *
 * The read/write segment lock protects all of segvn_data including the
 * vpage array.  All fields in segvn_data are treated as read-only when
 * the "read" version of the address space and the segment locks are held.
 * The "write" version of the segment lock, however, is required in order to
 * update the following fields:
 *
 *	pageprot
 *	prot
 *	amp
 *	vpage
 *
 * 	softlockcnt
 * is written by acquiring either the readers lock on the segment and
 * freemem lock, or any lock combination which guarantees exclusive use
 * of this segment (e.g., adress space writers lock,
 * address space readers lock + segment writers lock).
 */
typedef struct	segvn_data {
	krwlock_t lock;		/* protect segvn_data and vpage array */
	kmutex_t segp_slock;	/* serialize insertions into seg_pcache */
	uchar_t	pageprot;	/* true if per page protections present */
	uchar_t	prot;		/* current segment prot if pageprot == 0 */
	uchar_t	maxprot;	/* maximum segment protections */
	uchar_t	type;		/* type of sharing done */
	u_offset_t offset;	/* starting offset of vnode for mapping */
	struct	vnode *vp;	/* vnode that segment mapping is to */
	ulong_t	anon_index;	/* starting index into anon_map anon array */
	struct	anon_map *amp;	/* pointer to anon share structure, if needed */
	struct	vpage *vpage;	/* per-page information, if needed */
	struct	cred *cred;	/* mapping credentials */
	size_t	swresv;		/* swap space reserved for this segment */
	uchar_t	advice;		/* madvise flags for segment */
	uchar_t	pageadvice;	/* true if per page advice set */
	ushort_t flags;		/* flags - from sys/mman.h */
	ssize_t	softlockcnt;	/* # of pages SOFTLOCKED in seg */
	lgrp_mem_policy_info_t policy_info; /* memory allocation policy */
} segvn_data_t;

#ifdef _KERNEL

/*
 * Macros for segvn segment driver locking.
 */
#define	SEGVN_LOCK_ENTER(as, lock, type)	rw_enter((lock), (type))
#define	SEGVN_LOCK_EXIT(as, lock)		rw_exit((lock))
#define	SEGVN_LOCK_DOWNGRADE(as, lock)		rw_downgrade((lock))

/*
 * Macros to test lock states.
 */
#define	SEGVN_LOCK_HELD(as, lock)		RW_LOCK_HELD((lock))
#define	SEGVN_READ_HELD(as, lock)		RW_READ_HELD((lock))
#define	SEGVN_WRITE_HELD(as, lock)		RW_WRITE_HELD((lock))

/*
 * Macro used to detect the need to Break the sharing of COW pages
 *
 * The rw == S_WRITE is for the COW case
 * rw == S_READ and type == SOFTLOCK is for the physio case
 * We don't want to share a softlocked page because it can cause problems
 * with multithreaded apps but if rw == S_READ_NOCOW it's ok to not break
 * sharing of COW pages even in SOFTLOCK case.
 */
#define	BREAK_COW_SHARE(rw, type, seg_type) ((rw == S_WRITE || \
	(type == F_SOFTLOCK && rw != S_READ_NOCOW)) && \
	seg_type == MAP_PRIVATE)

#define	SEGVN_ZFOD_ARGS(prot, max)	\
	{ NULL, NULL, 0, MAP_PRIVATE, prot, max, 0, NULL, 0, 0 }

#define	AS_MAP_VNSEGS_USELPGS(crfp, argsp)				\
	((crfp) == (int (*)())segvn_create &&				\
	(((struct segvn_crargs *)(argsp))->flags &			\
	    (MAP_TEXT | MAP_INITDATA)) &&				\
	((struct segvn_crargs *)(argsp))->vp != NULL &&			\
	((struct segvn_crargs *)(argsp))->amp == NULL)


extern void	segvn_init(void);
extern int	segvn_create(struct seg *, void *);

extern	struct seg_ops segvn_ops;

/*
 * Provided as shorthand for creating user zfod segments.
 */
extern	caddr_t zfod_argsp;
extern	caddr_t kzfod_argsp;
extern	caddr_t stack_exec_argsp;
extern	caddr_t stack_noexec_argsp;

#endif	/* _KERNEL */

#ifdef	__cplusplus
}
#endif

#endif	/* _VM_SEG_VN_H */
