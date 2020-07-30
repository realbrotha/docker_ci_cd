/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernel/sys/vnode.h 1.36.1.52                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)05     1.36.1.52  src/bos/kernel/sys/vnode.h, syslfs, bos53J, j2006_18D5 5/3/06 13:24:42 */

/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 */
#ifndef _H_VNODE
#define _H_VNODE

/* 
 * Copyright (c) 1988 by Sun Microsystems, Inc.
 */

/*
 *
 * vnode, gnode and vnode operations structures and defines
 *
 * defines:
 *	struct vnode
 *	struct gnode
 *	struct vnodeops
 *	vnodeops calling macros
 *	struct exec_data
 *	struct open_data
 *	struct create_data
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/lockl.h>
#include <sys/uio.h>
#include <sys/rset.h>
#ifdef _KERNEL
#include <sys/vfs.h>
#include <sys/errno.h>
#endif /* _KERNEL */
#include <sys/acl.h>

struct vfs;
struct gnode;
struct vnodeops;
struct filock;
struct ucred;
struct vattr;
struct buf;
struct eflock;
extern int audit_flag;

/*
 * vnode ("virtual inode") structure
 *	vnodes are used to keep the name and place of an object in the
 * filesystem straight, so there may be more than one vnode per object.
 * A "gnode" is used to abstract the object itself.
 * NOTE: there is always at least one vnode per gnode.
 */
struct vnode {
        ushort	v_flag;		/* see definitions below		*/
	ushort	v_flag2;	/* Stolen for NFS version 4             */
        ulong32int64_t v_count;	/* the use count of this vnode		*/
	int	v_vfsgen;	/* generation number for the vfs	*/
	Simple_lock v_lock;     /* lock on the structure		*/
        struct vfs *v_vfsp;	/* pointer to the vfs of this vnode	*/
        struct vfs *v_mvfsp;	/* pointer to vfs which was mounted over this */
				/* vnode; NULL if no mount has occurred */
	struct gnode *v_gnode;	/* ptr to implementation gnode		*/
	struct vnode *v_next;	/* ptr to other vnodes that share same gnode */
	struct vnode *v_vfsnext; /* ptr to next vnode on list off of vfs */
	struct vnode *v_vfsprev; /* ptr to prev vnode on list off of vfs */
	union v_data {
		void *		_v_socket;	 /* vnode associated data */
		struct vnode *	_v_pfsvnode;	 /* vnode in pfs for spec */
	} _v_data;
	char *	v_audit; 	 /* ptr to audit object			*/
};
typedef struct vnode vnode_t;

#define v_socket	_v_data._v_socket
#define v_pfsvnode	_v_data._v_pfsvnode

/*
 * Definitions for v_flag field
 * of vnode structure.
 */
#define V_ROOT		0x01		/* vnode is the root of a vfs	*/
#ifndef	VROOT
#define VROOT V_ROOT
#endif

#define V_MOUNTING	0x02		/* mount in progress over vnode */

#define V_UNUSED04	0x04
#define V_UNUSED08	0x08
#define V_UNUSED10	0x10
#define V_UNUSED20	0x20
#define V_UNUSED40	0x40
#define V_UNUSED80	0x80
#define V_SPEC         0x100		/* special device - deprecated */
#define V_ACCESS       0x200		/* indicates the file has been  */
					/* accessed since last timestamp*/
#define V_UPDATE       0x400		/* indicates the file has been  */
					/* updated since last timestamp */
#define V_LAZYTS       0x800		/* indicates the lazy access or */
					/* update option is turned on.  */
#define V_NBC         0x1000		/* this vnode is cached in NBC  */
#define V_SNAPSHOT    0x2000		/* this vnode is a snapshot     */

#define __V_MAX       0xFFFF		/* nothing above here */
	
/* The following are provided for source compatability, but are
 * deprecated flags. They have no known uses.
 *
 * Note: V_SPEC is also deprecated, but is set in specfs (just not
 * read anywhere). It will be deleted later.
 */
#define V_INTRANSIT	0x04
#define V_DMA		0x08
#define V_TEXT		0x10
#define V_RMDC		0x20
#define V_RENAME	0x40
#define V_LOCK		0x80

/*
 * Definitions for v_flag2 field of vnode structure.
 * These are specific to NFS.
 */
#define V_PFS		0x1		/* this vnode is covered */
#define V_EXPORT	0x2		/* this vnode is an export root */
#define V_REFERRAL	0x4		/* this vnode is a referral object */
#define V_VCM		0x8		/* this vnode created with VCM active */


/* this is only used as a template for per vfs data attached to gnodes */
struct gn_vfsdata {
	struct gn_vfsdata *gnv_next;	/* next in chain, NULL ends chain */
	struct gnode	*gnv_gnode;	/* pointer back to gnode */
	int	gn_gfstype;		/* gfs type of this vfs */
	/* vfs specific stuff here */
};

/*
 * gnode types
 * DO NOT rearrange/redefine these first 10!
 * VNON means no type.
 */
enum vtype { VNON, VREG, VDIR, VBLK, VCHR, VLNK, VSOCK, VBAD, VFIFO, VMPC };
#define VUNDEF	VNON		/* undefined is same as nothing */
typedef enum vtype vtype_t;

/*
 * gnode structure - represents a real object in the file system;
 * i.e. there is a 1:1 correspondance between an gnode and a file on a disk.
 */
struct gnode {
	enum vtype gn_type;		/* type of object: VDIR,VREG,... */
	short	gn_flags;		/* attributes of object		*/
	vmid_t	gn_seg;			/* segment into which file is mapped */
	long32int64_t	gn_mwrcnt;	/* count of map for write	*/
	long32int64_t	gn_mrdcnt;	/* count of map for read	*/
	long32int64_t	gn_rdcnt;	/* total opens for read		*/
	long32int64_t	gn_wrcnt;	/* total opens for write	*/
	long32int64_t	gn_excnt;	/* total opens for exec		*/
	long32int64_t	gn_rshcnt;	/* total opens for read share	*/
	struct vnodeops *gn_ops;
	struct vnode *gn_vnode;	/* ptr to list of vnodes per this gnode */
	dev_t	gn_rdev;	/* for devices, their "dev_t" */
	chan_t	gn_chan;	/* for devices, their "chan", minor's minor */

	Simple_lock	gn_reclk_lock;  /* lock for filocks list        */
	int		gn_reclk_event; /* event list for file locking  */
	struct filock  *gn_filocks;     /* locked region list           */

	caddr_t	gn_data;	/* ptr to private data (usually contiguous) */
};

/*
 * definitions of gn_flags
 */
#define	GNF_TCB		0x0001	/* gnode corresponds to a file in the TCB */
#define	GNF_WMAP	0x0002	/* mapped for writing at some time	*/
#define GNF_NSHARE	0x0004	/* opened non share			*/
#define GNF_NWRITEMOUNT 0x0008  /* disallow writing while mounted       */
#define GNF_UIOMOVE	0x0010  /* all accesses to file go through vm_uiomove
				 * (unless GNF_WMAP is set)       */
#define GNF_ATTACH	0x0100  /* gnode corresponds to an attached file */
#define GNF_SNAPSHOT    0x2000  /* open snapshot device */
#define GNF_NORDAWRB    0x4000  /* no read ahead or write behind        */
#define GNF_XPAGER	0x8000  /* external pager callout operations enabled */

/*
 * some defines so old things keep working
 */
#define gn_segcnt	gn_mwrcnt
#define v_type		v_gnode->gn_type
#define v_vntype	v_gnode->gn_type
#define v_rdev		v_gnode->gn_rdev
#define v_data		v_gnode->gn_data

/*
 * track device opens for mount with gnode exec count.
 */
#define gn_mntcnt	gn_excnt

/*
 * Structure containing operations vector
 */
struct vnodeops {
	/* creation/naming/deletion */
	int	(*vn_link)(struct vnode *, struct vnode *, char *,
			struct ucred *);
	int	(*vn_mkdir)(struct vnode *, char *, int32long64_t,
			struct ucred *);
	int	(*vn_mknod)(struct vnode *, caddr_t, int32long64_t,
			dev_t, struct ucred *);
	int	(*vn_remove)(struct vnode *, struct vnode *, char *,
			struct ucred *);
	int	(*vn_rename)(struct vnode *, struct vnode *, caddr_t, 
			struct vnode *,struct vnode *,caddr_t,struct ucred *);
	int	(*vn_rmdir)(struct vnode *, struct vnode *, char *,
			struct ucred *);
	/* lookup,  file handle stuff */
	int	(*vn_lookup)(struct vnode *, struct vnode **, char *,
			int32long64_t, struct vattr *, struct ucred *);
	int	(*vn_fid)(struct vnode *, struct fileid *, struct ucred *);
	/* access to files */
	int	(*vn_open)(struct vnode *, int32long64_t, ext_t, caddr_t *,
			struct ucred *);
	int	(*vn_create)(struct vnode *, struct vnode **, int32long64_t,
			caddr_t, int32long64_t, caddr_t *, struct ucred *);
	int	(*vn_hold)(struct vnode *);
	int	(*vn_rele)(struct vnode *);
	int	(*vn_close)(struct vnode *, int32long64_t, caddr_t,
			struct ucred *);
	int	(*vn_map)(struct vnode *, caddr_t, uint32long64_t,
			uint32long64_t, uint32long64_t, struct ucred *);
	int	(*vn_unmap)(struct vnode *, int32long64_t, struct ucred *);
	/* manipulate attributes of files */
	int	(*vn_access)(struct vnode *, int32long64_t, int32long64_t,
			struct ucred *);
	int	(*vn_getattr)(struct vnode *, struct vattr *, struct ucred *);
	int	(*vn_setattr)(struct vnode *, int32long64_t, int32long64_t,
			int32long64_t, int32long64_t, struct ucred *);
	/* data update operations */
	int	(*vn_fclear)(struct vnode *, int32long64_t, offset_t, offset_t, 
			caddr_t, struct ucred *);
	int	(*vn_fsync)(struct vnode *, int32long64_t, int32long64_t,
			struct ucred *);
	int	(*vn_ftrunc)(struct vnode *, int32long64_t, offset_t, caddr_t,
			struct ucred *);
	int	(*vn_rdwr)(struct vnode *, enum uio_rw, int32long64_t,
			struct uio *, ext_t, caddr_t, struct vattr *,
			struct ucred *);
	int	(*vn_lockctl)(struct vnode *, offset_t, struct eflock *,
			int32long64_t, int (*)(), ulong *, struct ucred *);
	/* extensions */
	int	(*vn_ioctl)(struct vnode *, int32long64_t, caddr_t, size_t,
			ext_t, struct ucred *);
	int	(*vn_readlink)(struct vnode *, struct uio *, struct ucred *);
	int	(*vn_select)(struct vnode *, int32long64_t, ushort, ushort *,
			void (*)(), caddr_t, struct ucred *);
	int	(*vn_symlink)(struct vnode *, char *, char *, struct ucred *);
	int	(*vn_readdir)(struct vnode *, struct uio *, struct ucred *);
	/* buffer ops */
	int	(*vn_strategy)(struct vnode *, struct buf *, struct ucred *);
	/* security things */
	int	(*vn_revoke)(struct vnode *, int32long64_t, int32long64_t,
			struct vattr *, struct ucred *);
	int	(*vn_getacl)(struct vnode *, struct uio *, struct ucred *);
	int	(*vn_setacl)(struct vnode *, struct uio *, struct ucred *);
	int	(*vn_getpcl)(struct vnode *, struct uio *, struct ucred *);
	int	(*vn_setpcl)(struct vnode *, struct uio *, struct ucred *);
	int	(*vn_seek)(struct vnode *, offset_t *, struct ucred *);

	/* 421 extensions */
	int	(*vn_fsync_range)(struct vnode *, int32long64_t, int32long64_t,
			offset_t, offset_t, struct ucred *);
	int	(*vn_create_attr)(struct vnode *, struct vnode **,
			int32long64_t, char *, struct vattr *, int32long64_t,
			caddr_t *, struct ucred *);
	int	(*vn_finfo)(struct vnode *, int32long64_t, void *,
			size_t, struct ucred *);
	int	(*vn_map_lloff)(struct vnode *, caddr_t, offset_t, offset_t,
			uint32long64_t, uint32long64_t, struct ucred *);
	int	(*vn_readdir_eofp)(struct vnode *, struct uio *, int *,
			struct ucred *);
	int	(*vn_rdwr_attr)(struct vnode *, enum uio_rw, int32long64_t,
			struct uio *, ext_t , caddr_t, struct vattr *,
			struct vattr *, struct ucred *);
	int	(*vn_memcntl)(struct vnode *,int, void *, struct ucred *);
	int	(*vn_getea)(struct vnode *, const char *, struct uio *,
			       struct ucred *);
	int	(*vn_setea)(struct vnode *, const char*, struct uio *, 
			       int flags, struct ucred *);
	int	(*vn_listea)(struct vnode *, struct uio *, struct ucred *);
	int	(*vn_removeea)(struct vnode *, const char *, struct ucred *);
	int	(*vn_statea)(struct vnode *, const char *, struct vattr *,
				struct ucred *);
	int	(*vn_getxacl)(struct vnode *, uint64_t, acl_type_t *, struct uio *, size_t *, mode_t *, struct ucred *);
	int	(*vn_setxacl)(struct vnode *, uint64_t, acl_type_t, struct uio *, mode_t,  struct ucred *);
	int	(*vn_spareE)();
	int	(*vn_spareF)();

	/*
	 * External pager callout operation
	 */
	int     (*pagerBackRange)(struct gnode *, offset_t, caddr_t, size_t *,
			size_t *, uint *);
	int64_t	(*pagerGetFileSize)(struct gnode *);
	void	(*pagerReadAhead)(struct gnode *, vpn_t, vpn_t *,
			vpn_t *, vpn_t *, boolean_t);
	void	(*pagerReadWriteBehind)(struct gnode *, int64_t, int64_t, uint);
	void    (*pagerEndCopy)(struct gnode *, offset_t, size_t, size_t, uint);

};
typedef struct vnodeops vnodeops_t;

#ifdef _KERNEL

/*
 * Macros for the vnode operations.
 */
#define VNOP_ACCESS(vp, mode, who, ucred) \
	vnop_access(vp, mode, who, ucred)
#define VNOP_CLOSE(vp, flags, vinfo, ucred) \
	vnop_close(vp, flags, vinfo, ucred)
#define VNOP_CREATE(dp, vpp, flags, name, mode, vinfo, ucred) \
	vnop_create(dp, vpp, flags, name, mode, vinfo, ucred)
#define VNOP_FCLEAR(vp, flags, offset, length, vinfo, ucred) \
	vnop_fclear(vp, flags, offset, length, vinfo, ucred)
#define VNOP_FID(vp, fid, ucred) \
	vnop_fid(vp, fid, ucred)
#define VNOP_FSYNC(vp, flags, vinfo, ucred) \
	vnop_fsync(vp, flags, vinfo, ucred)
#define VNOP_FTRUNC(vp, flags, length, vinfo, ucred) \
	vnop_ftrunc(vp, flags, length, vinfo, ucred)
#define VNOP_GETACL(vp, uiop, ucred) \
	vnop_getacl(vp, uiop, ucred)
#define VNOP_GETATTR(vp, vattrp, ucred) \
	vnop_getattr(vp, vattrp, ucred)
#define VNOP_GETPCL(vp, uiop, ucred) \
	vnop_getpcl(vp, uiop, ucred)
#define VNOP_HOLD(vp) \
	vnop_hold(vp)
#define VNOP_IOCTL(vp, cmd, arg, flags, ext, ucred) \
	vnop_ioctl(vp, cmd, arg, flags, ext, ucred)
#define VNOP_LINK(vp, dp, target, ucred) \
	vnop_link(vp, dp, target, ucred)
#define VNOP_LOCKCTL(vp, offset, lckdat, cmd, retry_fcn, retry_id, ucred) \
	vnop_lockctl(vp, offset, lckdat, cmd, retry_fcn, retry_id, ucred)
#define VNOP_LOOKUP(dp, vpp, nam, flags, vattrp, ucred) \
	vnop_lookup(dp, vpp, nam, flags, vattrp, ucred)
#define VNOP_MAP(vp, addr, length, offset, flags, ucred) \
	vnop_map(vp, addr, length, offset, flags, ucred)
#define VNOP_MKDIR(vp, name, mode, ucred) \
	vnop_mkdir(vp, name, mode, ucred)
#define VNOP_MKNOD(vp, name, mode, dev, ucred) \
	vnop_mknod(vp, name, mode, dev, ucred)
#define VNOP_OPEN(vp, flags, ext, vinfop, ucred) \
	vnop_open(vp, flags, ext, vinfop, ucred)
#define VNOP_SELECT(vp, correl, reqevents, rtnevents, notify, vinfo, ucred) \
	vnop_select(vp, correl, reqevents, rtnevents, notify, vinfo, ucred)
#define VNOP_RDWR(vp, op, flags, uiop, ext, vinfo, vattrp, ucred) \
	vnop_rdwr(vp, op, flags, uiop, ext, vinfo, vattrp, ucred)
#define VNOP_READDIR(vp, uiop, ucred) \
	vnop_readdir(vp, uiop, ucred)
#define VNOP_READLINK(vp, uiop, ucred) \
	vnop_readlink(vp, uiop, ucred)
#define VNOP_RELE(vp) \
	vnop_rele(vp)
#define VNOP_REMOVE(dp, vp, name, ucred) \
	vnop_remove(dp, vp, name, ucred)
#define VNOP_RENAME(vp, dp, name, tvp, tdp, tname, ucred) \
	vnop_rename(vp, dp, name, tvp, tdp, tname, ucred)
#define VNOP_REVOKE(vp, cmd, flags, vattrp, ucred) \
	vnop_revoke(vp, cmd, flags, vattrp, ucred)
#define VNOP_RMDIR(vp, dp, name, ucred) \
	vnop_rmdir(vp, dp, name, ucred)
#define VNOP_SETACL(vp, uiop, ucred) \
	vnop_setacl(vp, uiop, ucred)
#define VNOP_SETATTR(vp, op, arg1, arg2, arg3, ucred) \
	vnop_setattr(vp, op, arg1, arg2, arg3, ucred)
#define VNOP_SETPCL(vp, uiop, ucred) \
	vnop_setpcl(vp, uiop, ucred)
#define VNOP_STRATEGY(vp, bp, ucred) \
	vnop_strategy(vp, bp, ucred)
#define VNOP_SYMLINK(vp, name, target, ucred) \
	vnop_symlink(vp, name, target, ucred)
#define VNOP_UNMAP(vp, addr, ucred) \
	vnop_unmap(vp, addr, ucred)
#define VNOP_SEEK(vp, off, ucred) \
	vnop_seek(vp, off, ucred)

#define VNOP_FSYNC_RANGE(vp, flags, vinfo, off, len, ucred) \
	vnop_fsync_range(vp, flags, vinfo, off, len, ucred)
#define VNOP_CREATE_ATTR(dp, vpp, flags, name, vap, vcf, vinfo, ucred) \
	vnop_create_attr(dp, vpp, flags, name, vap, vcf, vinfo, ucred)
#define	VNOP_FINFO(vp, cmd, p, len, ucred) \
	vnop_finfo(vp, cmd, p, len, ucred)
#define	VNOP_MAP_LLOFF(vp, a, len, off, mf, ff, ucred) \
	vnop_map_lloff(vp, a, len, off, mf, ff, ucred)
#define	VNOP_READDIR_EOFP(vp, uiop, eofp, ucred) \
	vnop_readdir_eofp(vp, uiop, eofp, ucred)
#define VNOP_RDWR_ATTR(vp, rw, ff, uio, x, vi, pre, post, ucred) \
	vnop_rdwr_attr(vp, rw, ff, uio, x, vi, pre, post, ucred)

#define VNOP_MEMCNTL(vp,cmd,arg,ucred) \
	vnop_memcntl(vp,cmd,arg,ucred)

#define VNOP_GETEA(vp, eaName, uiop, crp) \
        vnop_getea(vp, eaName, uiop, crp)
#define VNOP_SETEA(vp, eaName, uiop, flag, crp) \
	vnop_setea(vp, eaName, uiop, flag, crp)
#define VNOP_LISTEA(vp, uiop, crp) \
        vnop_listea(vp, uiop, crp)
#define VNOP_REMOVEEA(vp, eaName, crp)\
        vnop_removeea(vp, eaName, crp)
#define VNOP_STATEA(vp, eaName, vattrp, crp) \
	vnop_statea(vp, eaName, vattrp, crp)
#define VNOP_SETXACL(vp,ctl_flags,acl_type,uiop,mode,crp) \
	vnop_setxacl(vp,ctl_flags,acl_type,uiop,mode,crp) 
#define VNOP_GETXACL(vp,ctl_flag,acl_typep,uiop,sizep,modep,crp) \
	vnop_getxacl(vp,ctl_flag,acl_typep,uiop,sizep,modep,crp) 


/*
 * Macro to determine if VMM read-ahead and write-behind algorithms are
 *  enabled.
 */
#define gn_rdawrb(gp)           (! ((gp)->gn_flags & GNF_NORDAWRB))

/* 
 * macros for external pager call out operations
 */
#define PagerCallOut(gp) ((gp)->gn_flags & GNF_XPAGER)

#define XPAGER_RA_TRIGGER	0x00000001

/* flags set in PagerBackRange() for use by VMM */
#define XPAGER_OVERWRITE        0x00000001   /* overwrite */
#define XPAGER_HOLE		0x00000002   /* page hole */
#define XPAGER_EXTEND		0x00000004   /* extend partially backed page */
#define XPAGER_APPEND		0x00000008  /* append new page */
#define XPAGER_MAPPED		0x00000010   /* shared with mapper */
#define XPAGER_MMAPPED		0x00000020   /* shared with mmapper */

#define XPAGER_RESERVED		0x0000FF00 /* Reserved for VMM use. */

/* return values set by VMM passed to PagerEndCopy() */
#define XPAGER_COPY_SUCCESS     0x00000000	/* range copy successful     */
#define XPAGER_COPY_FAILURE     0x00010000	/* range copy failed	     */

/* page fault type */
#define	XPAGER_MMAP	0x00000010
#define	XPAGER_STORE	0x00000020
#define	XPAGER_PROTECT	0x00000040

/* ReadWriteBehind types */
#define XPAGER_READ	0x00000001
#define XPAGER_WRITE	0x00000002
#define XPAGER_RELEASE  0x00000004

#define PagerBackRange(gp, offset, dest, nBytesOfRange, nBytesBacked, flags) \
	(*(gp)->gn_ops->pagerBackRange) \
		(gp, offset, dest, nBytesOfRange, nBytesBacked, flags) 
#define PagerEndCopy(gp, offset, nBytesMoved, nBytesBacked, flags) \
	(*(gp)->gn_ops->pagerEndCopy) \
		(gp, offset, nBytesMoved, nBytesBacked, flags)
#define PagerGetFileSize(gp) (*(gp)->gn_ops->pagerGetFileSize)(gp)
#define PagerReadAhead(gp, pFault, pFirst, nPage, pTripWire, tripWire) \
	(*(gp)->gn_ops->pagerReadAhead) \
		(gp, pFault, pFirst, nPage, pTripWire, tripWire)
#define PagerReadWriteBehind(gp, offset, length, flags) \
	(*(gp)->gn_ops->pagerReadWriteBehind)(gp, offset, length, flags)

/*
 * Function prototypes for vnode op wrapper functions.
 */
int
vnop_access(
	struct vnode *,
	int32long64_t,
	int32long64_t,
	struct ucred *);

int
vnop_close(
	struct vnode *,
	int32long64_t,
	caddr_t,
	struct ucred *);

int
vnop_create(
	struct vnode *,
	struct vnode **,
	int32long64_t,
	char *,
	int32long64_t,
	caddr_t *,
	struct ucred *);

int
vnop_fclear(
	struct vnode *,
	int32long64_t,
	offset_t,
	offset_t,
	char *,
	struct ucred *);

int
vnop_fid(
	struct vnode *,
	struct fileid *,
	struct ucred *);

int
vnop_fsync(
	struct vnode *,
	int32long64_t,
	int32long64_t,
	struct ucred *);

int
vnop_ftrunc(
	struct vnode *,
	int32long64_t,
	offset_t,
	caddr_t,
	struct ucred *);

int
vnop_getacl(
	struct vnode *,
	struct uio *,
	struct ucred *);

int
vnop_getattr(
	struct vnode *,
	struct vattr *,
	struct ucred *);

int
vnop_getpcl(
	struct vnode *,
	struct uio *,
	struct ucred *);

int
vnop_getea(
	struct vnode *,
	const char *,
	struct uio *,
	struct ucred *);

int
vnop_hold(
	struct vnode *);

int
vnop_ioctl(
	struct vnode *,
	int32long64_t, 
	caddr_t, 
	size_t,
	ext_t,
	struct ucred *);

int
vnop_link(
	struct vnode *,
	struct vnode *,
	char *,
	struct ucred *);

int 
vnop_listea(
	struct vnode *,
	struct uio *,
	struct ucred *);

int
vnop_lockctl(
	struct vnode *,
	offset_t,
	struct eflock *,
	int32long64_t,
	int (*)(),
	ulong *,
	struct ucred *);

int
vnop_lookup(
	struct vnode *,
	struct vnode **,
	char *,
	int32long64_t,
	struct vattr *,
	struct ucred *);

int
vnop_map(
	struct vnode *,
	caddr_t,
	uint32long64_t,
	uint32long64_t,
	uint32long64_t,
	struct ucred *);

int
vnop_mkdir(
	struct vnode *,
	char *,
	int32long64_t,
	struct ucred *);

int
vnop_mknod(
	struct vnode *,
	caddr_t,
	int32long64_t,
	dev_t,
	struct ucred *);

int
vnop_open(
	struct vnode *,
	int32long64_t,
	ext_t,
	caddr_t *,
	struct ucred *);

int
vnop_select(
	struct vnode *,
	int32long64_t,
	ushort,
	ushort *,
	void (*)(),
	caddr_t,
	struct ucred *);

int
vnop_rdwr(
	struct vnode *,
	enum uio_rw,
	int32long64_t,
	struct uio *,
	ext_t,
	caddr_t,
	struct vattr *,
	struct ucred *);

int
vnop_readdir(
	struct vnode *,
	struct uio *,
	struct ucred *);

int
vnop_readlink(
	struct vnode *,
	struct uio *,
	struct ucred *);

int
vnop_rele(
	struct vnode *);

int
vnop_remove(
	struct vnode *,
	struct vnode *,
	char *,
	struct ucred *);

int 
vnop_removeea(
	struct vnode *,
	const char *, 
	struct ucred *);

int
vnop_rename(
	struct vnode *,
	struct vnode *,
	caddr_t,
	struct vnode *,
	struct vnode *,
	caddr_t,
	struct ucred *);

int
vnop_revoke(
	struct vnode *,
	int32long64_t,
	int32long64_t,
	struct vattr *,
	struct ucred *);

int
vnop_rmdir(
	struct vnode *,
	struct vnode *,
	char *,
	struct ucred *);

int
vnop_setacl(
	struct vnode *,
	struct uio *,
	struct ucred *);

int
vnop_setattr(
	struct vnode *,
	int32long64_t,
	int32long64_t,
	int32long64_t,
	int32long64_t,
	struct ucred *);

int
vnop_setpcl(
	struct vnode *,
	struct uio *,
	struct ucred *);

int 
vnop_setea(
	struct vnode *,
	const char *,
	struct uio *,
	int flags,
	struct ucred *);

int 
vnop_statea(
	struct vnode *, 
	const char *, 
	struct vattr *,
	struct ucred *);

int
vnop_strategy(
	struct vnode *,
	struct buf *,
	struct ucred *);

int
vnop_symlink(
	struct vnode *,
	char *,
	char *,
	struct ucred *);

int
vnop_unmap(
	struct vnode *,
	int32long64_t,
	struct ucred *);

int
vnop_seek(
	struct vnode *,
	offset_t *,
	struct ucred *);

int
vnop_fsync_range(
	struct vnode *,
	int32long64_t,
	int32long64_t,
	offset_t,
	offset_t,
	struct ucred *);

int
vnop_create_attr(
	struct vnode *,
	struct vnode **,
	int32long64_t,
	char *,
	struct vattr *,
	int32long64_t,
	caddr_t *,
	struct ucred *);

int
vnop_finfo(
	struct vnode *,
	int32long64_t,
	void *,
	size_t,
	struct ucred *);

int
vnop_map_lloff(
	struct vnode *,
	caddr_t,
	offset_t,
	offset_t,
	uint32long64_t,
	uint32long64_t,
	struct ucred *);

int
vnop_readdir_eofp(
	struct vnode *,
	struct uio *,
	int *,
	struct ucred *);

int
vnop_rdwr_attr(
	struct vnode *,
	enum uio_rw,
	int32long64_t,
	struct uio *,
	ext_t,
	caddr_t,
	struct vattr *,
	struct vattr *,
	struct ucred *);

int
vnop_memcntl(
	struct vnode *,
	int,
	void *,
	struct ucred *);

/*
 * vnop_memcntl command (2nd parameter)
 * gn_common_memcntl command (2nd parameter)
 */
#define F_ATTACH	1
#define F_DETACH	2
#define F_ATTINFO	3

/*
 * vnop_memcntl argument (3rd parameter)
 * gn_common_memcntl argument (3rd parameter)
 * related to F_ATTACH command
 */
typedef struct attach_desc {
	offset_t start;     /* starting byte offset of range */
	size_t nbytes;      /* number of bytes in range      */
	uint policy;        /* memory policy                 */
	rsethandle_t rsetp; /* resource set pointer          */
} attach_desc_t;
	
/*
 * vnop_memcntl argument (3rd parameter)
 * gn_common_memcntl argument (3rd parameter)
 * related to F_DETACH command
 */
typedef struct detach_desc {
	offset_t start;     /* starting byte offset of range */
	size_t nbytes;      /* number of bytes in range      */
	int    nb_att;      /* number of attachments         */
} detach_desc_t;

/*
 * vnop_memcntl argument (3rd parameter)
 * gn_common_memcntl argument (3rd parameter)
 * related to F_ATTINFO command
 */
typedef struct attinfo_desc {
        offset_t start;     /* starting byte offset of range      */
        size_t nbytes;      /* number of bytes in range           */
        ptr64 buf;          /* output buffer for attachment info  */
        size_t *bufsizep;   /* pointer to buffer size in bytes    */
        int adspace;        /* USR / SYS: called from library/kservice */
} attinfo_desc_t;

int
vnop_getxacl(struct vnode *vp,
	uint64_t ctl_flags,
	acl_type_t *acl_type,
	struct uio *uiop,
	size_t *sizep,
	mode_t *modep,
	struct ucred *crp);

int
vnop_setxacl(struct vnode *vp,
	uint64_t ctl_flags,
	acl_type_t acl_type,
	struct uio *uiop,
	mode_t mode,
	struct ucred *crp);

int
vnop_setxacl_common(struct vnode *vp,
	uint64_t ctl_flags,
	acl_type_t acl_type,
	struct uio *uiop,
	mode_t mode,
	struct ucred *crp);

void
gn_opencnt(struct gnode *,
	   long);

void
gn_closecnt(struct gnode *,
	    long);

void
gn_mapcnt(struct gnode *,
	  long);

void
gn_unmapcnt(struct gnode *,
	    long);

int
gn_common_memcntl(struct gnode *,
		  int,
		  void *);

/*
 * Support for NBC caching
 */
int nbc_vnop_hold(struct vnode *);
int nbc_vnop_rele(struct vnode *);
#define NBC_VNODE_MATCH(__v,__k) ((__v)->v_vfsp->vfs_number == *(uint *)(__k))

void bad_vnode_bad_caller(struct vnode *vp);

static __inline void check_vnode(struct vnode *vp)
{
	if (vp == NULL
	    || vp->v_gnode == NULL
	    || vp->v_gnode->gn_ops == NULL)
	{
		/* bad vnode! bad! */
		bad_vnode_bad_caller(vp);
	}
}
	
#endif /*_KERNEL*/


#ifdef _SUN
/* for Sun vnode compatibility, they expect vattr to be in vnode.h */
#include <sys/vattr.h>
enum vcexcl	{ NONEXCL, EXCL};	/* (non)excl create (create) */
typedef enum vcexcl vcexcl_t;
#endif /* _SUN */

/*
 * Convert inode formats to vnode types
 */
extern enum vtype iftovt_tab[];		/* these are located in stat.c */
extern int   vttoif_tab[];

#define IFTOVT(M)	(iftovt_tab[((M) & S_IFMT) >> 12])
#define VTTOIF(T)	(vttoif_tab[(int)(T)])

#define MAKEIMODE(T, M)	(VTTOIF(T) | (M))

#define VTOGP(x)	((struct gnode *)((x)->v_gnode))

/* defines for the vc_flags in vnop_create_attr */
#define	VC_DEFAULT	0
#define	VC_LOOKUP	1
#define	VC_OPEN		2

#ifdef __cplusplus
}
#endif

#endif /* _H_VNODE */
