/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_MNTFS_MNTDATA_H
#define	_SYS_MNTFS_MNTDATA_H

#pragma ident	"@(#)mntdata.h	1.6	04/04/30 SMI"

#include <sys/vnode.h>
#include <sys/poll.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct mntsnap {
	char	*mnts_text;	/* base address of text in user addr space */
	size_t	mnts_textsize;	/* size of mapped text */
	char	*mnts_metadata;	/* base address of metadata in user space */
	size_t	mnts_metasize;	/* size of mapped metadata */
	uint_t	mnts_count;	/* number of mounts in snapshot */
	timespec_t mnts_time;	/* time when snapshot was taken */
} mntsnap_t;

typedef struct mntnode {
	uint_t mnt_flags;	/* flags */
	vnode_t *mnt_mountvp;	/* vnode mounted on */
	vnode_t *mnt_vnode;	/* vnode for this mntnode */
	mntsnap_t mnt_read;	/* Data for read() */
	mntsnap_t mnt_ioctl;	/* Data for ioctl() */
	uint_t mnt_offset;	/* offset within ioctl() snapshot */
} mntnode_t;

struct zone;

typedef struct mntdata {
	struct zone *mnt_zone;		/* zone for mount point */
	uint_t mnt_nopen;		/* count of vnodes open */
	size_t mnt_size;		/* latest snapshot size for mount */
	struct mntnode mnt_node;	/* embedded mntnode */
} mntdata_t;

/*
 * Conversion macros.
 */
#define	VTOM(vp)	((struct mntnode *)(vp)->v_data)
#define	MTOV(pnp)	((pnp)->mnt_vnode)
#define	MTOD(pnp)	((struct mntdata *)MTOV(pnp)->v_vfsp->vfs_data)

#if defined(_KERNEL)

/*
 * Values for mnt_flags.
 */
#define	MNT_SHOWHIDDEN	0x1	/* Hack to show all mounts, even MS_NOMNTTAB */

extern	struct vnodeops	*mntvnodeops;
extern	void mntfs_getmntopts(struct vfs *, char **, size_t *);

#endif	/* _KERNEL */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_MNTFS_MNTDATA_H */
