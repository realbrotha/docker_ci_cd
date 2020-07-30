/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernel/sys/vfs.h 1.19.1.43                              */
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
/* @(#)53	1.19.1.43  src/bos/kernel/sys/vfs.h, syslfs, bos53J, j2006_16A4 4/11/06 11:02:40 */

#ifndef _H_VFS
#define _H_VFS

/* COMPONENT_NAME: SYSLFS - Logical File System
 */

#include <sys/types.h>
#include <sys/gfs.h>
#include <sys/vnode.h>
#include <sys/vmount.h>
#include <sys/statfs.h>
#include <sys/limits.h>
#include <sys/cred.h>
#include <sys/aacct.h>
#include <sys/ras.h>

extern Complex_lock vfs_list_lock;	/* global vfs list lock */

/*
** where vfs data is stored (VFSfile)
** where the helpers reside (VFSdir) by default
** where to find filesystem data (from IN/FSdefs.h)
*/

#define VFSfile "/etc/vfs"
#define VFSdir  "/sbin/helpers/"
#define FSfile  FSYSname

/*
** struct vfs_ent discribes an entry in the VFSfile
**
** these are returned by various getvfsent(), etc. routines.
**
** many of the vfs_ prefixes are disguises for gfs objects
** so be careful about naming when using this header file
*/

struct vfs_ent
{
  char *vfsent_name;      /* name (ie. "aix3", "nfs", etc.) */
  int   vfsent_type;      /* in vmount.h */
  int   vfsent_flags;
  char *vfsent_mnt_hlpr;  /* mount helper pathname */ 
  char *vfsent_fs_hlpr;   /* filesystem helper pathname */
};

#if defined(__64BIT__)
extern struct vfs_ent *getvfsent(void);
extern struct vfs_ent *getvfsbytype(int );
extern struct vfs_ent *getvfsbyname(char *);
extern struct vfs_ent *getvfsbyflag(int);
#endif

/*
** no helper string
*/  

#define NO_HELPER "none"

/*
** as keyed by the %default VFSfile control directive
*/

#define VFS_DFLT_LOCAL     0x1
#define VFS_DFLT_REMOTE    0x2

/*
 * the vfs structure represents a virtual file system.
 *	One of them is created for each mounted file-system/object.
 */
struct vfs {
	struct vfs	*vfs_next;	/* vfs's are a linked list */
	struct gfs	*vfs_gfs;	/* ptr to gfs of vfs */
	struct vnode	*vfs_mntd;	/* pointer to mounted vnode, */
					/*	the root of this vfs */
	struct vnode	*vfs_mntdover;	/* pointer to mounted-over */
					/*	vnode		 */
	struct vnode	*vfs_vnodes;	/* all vnodes in this vfs */
	int		vfs_count;	/* number of users of this vfs */
	caddr_t		vfs_data;	/* private data area pointer */
	unsigned int	vfs_number;	/* serial number to help */
					/*  distinguish between */
					/*  different mounts of the */
					/*  same object */
	int		vfs_bsize;	/* native block size */
#ifdef	_SUN
	short		vfs_exflags;	/* for SUN, exported fs flags */
	unsigned short	vfs_exroot;	/* for SUN, " fs uid 0 mapping */
#else
	short		vfs_rsvd1;	/* Reserved */
	unsigned short	vfs_rsvd2;	/* Reserved */
#endif	/* _SUN */
	struct vmount	*vfs_mdata;	/* record of mount arguments */
	Simple_lock	vfs_lock;	/* lock to serialize vnode list */
	ras_block_t	vfs_rasb;	/* Per-FS RAS block */
};
typedef struct vfs vfs_t;

/* these defines are for backwards compatibility */
#define vfs_fsid	vfs_mdata->vmt_fsid 
#define vfs_date	vfs_mdata->vmt_time 
#define vfs_flag	vfs_mdata->vmt_flags
#define vfs_type	vfs_gfs->gfs_type 
#define vfs_ops		vfs_gfs->gfs_ops 

/* advanced accounting data for system statistic 
 *
 * when sysproc to provide acct_add_LL and acct_zero_LL
 * for atomic addition or read&reset operations for
 * unsigned long long value,
 * the following struct assumed. But I don't have to 
 * use it since it is hidden from the caller
 *
 *	typedef struct {
 *       unsigned long long aData_lock:1;
 *       unsigned long long numBytes:63;
 * } atomicData_t;
 *
 * the following definition is moved to aacct.h in
 * def 415154, and change name to be tran_filesystem
 */
#if 0
struct acct_sysfs_data {
   unsigned long long DbytesTrans;  /* 8: total bytes for read & write */
   unsigned long long DnumRdWrs;  /* 8: total number of reads and writes */
   unsigned long long DnumOpens;  /* 8: total number of opens */
   unsigned long long DnumCreates;  /* 8: total number of creates */
   unsigned long long DnumLocks;  /* 8: total number of locks */
   uint Dfstype;    /* 4: fs type, also in vfs.vfs_mdata->vmt_gfstype */
};
#endif

typedef struct tran_filesystem acct_sysfsD_t;

struct supervfs {
	struct vfs vfsD;
	acct_sysfsD_t vfs_acctSysFsD;
};

#define  acct2nameptr(at, len)   ((caddr_t)(((long)(at)) + len) )

#define GET_ACCT_SYSFSDATA(ACCT_SYSFSD, ACCT_SYSFSP)\
{\
     ACCT_SYSFSD->DbytesTrans = acct_zero_LL(&ACCT_SYSFSP->DbytesTrans);\
     ACCT_SYSFSD->DnumRdWrs = acct_zero_LL(&ACCT_SYSFSP->DnumRdWrs);\
     ACCT_SYSFSD->DnumOpens = acct_zero_LL(&ACCT_SYSFSP->DnumOpens);\
     ACCT_SYSFSD->DnumCreates = acct_zero_LL(&ACCT_SYSFSP->DnumCreates);\
     ACCT_SYSFSD->DnumLocks = acct_zero_LL(&ACCT_SYSFSP->DnumLocks);\
     ACCT_SYSFSD->Dfstype = ACCT_SYSFSP->Dfstype;\
}
#define VFS2ACCTFS(VFSP, ACCTFSP)\
{\
	ACCTFSP = ((acct_sysfsD_t *) &(((struct supervfs *)(VFSP))->vfs_acctSysFsD));\
}


/* lock definitions
 */
#define VFS_LOCK(vfsp)		simple_lock(&(vfsp)->vfs_lock)
#define VFS_UNLOCK(vfsp)	simple_unlock(&(vfsp)->vfs_lock)

#ifdef	_SUN
/* the defines are for the SUN style names */
#define vfs_vnodecovered vfs_mntdover
#define vfs_pdata vfs_data
#endif	/* _SUN */

/* note no define for vfs_op, use VFS_func() macros! */

/* Note: vmount.H now contains the definitions for the VFS flags */

/* 
 * Structure containing pointers to routines
 * which implement vfs operations
 */
struct vfsops {
	/* mount a file system */
	int (*vfs_mount)(struct vfs *, struct ucred *);
	/* unmount a file system */
	int (*vfs_unmount)(struct vfs *, int, struct ucred *);
	/* get the root vnode of a file system */
	int (*vfs_root)(struct vfs *, struct vnode **, struct ucred *);
	/* get file system information */
	int (*vfs_statfs)(struct vfs *, struct statfs *, struct ucred *);
	/* sync all file systems of this type */
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
	int (*vfs_sync)(struct gfs *);
#else
	int (*vfs_sync)();
#endif
	/* get a vnode matching a file id */
	int (*vfs_vget)(struct vfs *, struct vnode **, struct fileid *,
			struct ucred *);
	/* do specified command to file system */
	int (*vfs_cntl)(struct vfs *, int, caddr_t, size_t, struct ucred *);
	/* manage file system quotas */
	int (*vfs_quotactl)(struct vfs *, int, uid_t, caddr_t, struct ucred *);
	/* sync specific fs with options */
	int (*vfs_syncvfs)(struct gfs *, struct vfs *, int, struct ucred *);
	/* ACL controls */
	int (*vfs_aclxcntl)(struct vfs *, struct vnode *, int, struct uio *, 
			size_t *, struct ucred *);
	int (*vfs_statfsvp)(struct vfs *, struct vnode *, struct statfs *,
			struct ucred *);
	int (*vn_spare1)();
	int (*vn_spare2)();
	int (*vn_spare3)();
	int (*vn_spare4)();
	int (*vn_spare5)();
};
typedef struct vfsops vfsops_t;

#ifdef	_KERNEL

/*
 * Macros for calls to the VFS switch routines.
 */
#define VFS_MOUNT(vfsp, crp) \
	vfs_mount(vfsp, crp)
#define VFS_UNMOUNT(vfsp, flags, crp) \
	vfs_unmount(vfsp, flags, crp)
#define VFS_ROOT(vfsp, vpp, crp) \
	vfs_root(vfsp, vpp, crp)
#define VFS_STATFS(vfsp, sfsp, crp) \
	vfs_statfs(vfsp, sfsp, crp)
#define VFS_STATFSVP(vfsp, vp, sfsp, crp) \
	vfs_statfsvp(vfsp, vp, sfsp, crp)
#define VFS_SYNC(gfsp) \
	vfs_sync(gfsp)
#define VFS_SYNCVFS(gfsp, vfsp, cmd, crp) \
        vfs_syncvfs(gfsp, vfsp, cmd, crp)
#define VFS_VGET(vfsp, vpp, fidp, crp) \
	vfs_vget(vfsp, vpp, fidp, crp)
#define VFS_CNTL(vfsp, cmd, arg, argsize, crp) \
	vfs_cntl(vfsp, cmd, arg, argsize, crp)
#define VFS_QUOTACTL(vfsp, cmds, uid, arg, crp) \
	vfs_quotactl(vfsp, cmds, uid, arg, crp)
#define VFS_ACLXCNTL(vfsp, vp, cmd, arg, argsize, crp)\
	vfs_aclxcntl(vfsp, vp, cmd, arg, argsize, crp) 

/* exported interface for vfs list serialization */
#define VFSLIST_UNLOCK          0
#define VFSLIST_READLOCK        1
#define VFSLIST_WRITELOCK       2
void vfsListCtl(int cmd);

/* Function prototypes for adv, accounting handler */
extern int acctfs_sysdata_handler (
   int transid, 
   int cmd, 
   void *arg);
 

#if defined(__64BIT_KERNEL) || defined( __FULL_PROTO)
/*
 * Function prototypes for vfs op wrapper functions.
 */
extern int vfs_mount(struct vfs *,
		struct ucred *);

extern int vfs_unmount(struct vfs *,
		int,
		struct ucred *);

extern int vfs_root(struct vfs *,
		struct vnode **,
		struct ucred *);

extern int vfs_statfs(struct vfs *,
		struct statfs *,
		struct ucred *);

extern int vfs_statfsvp(struct vfs *,
		struct vnode *,
		struct statfs *,
		struct ucred *);

extern int vfs_sync(struct gfs *);

extern int vfs_syncvfs(struct gfs *,
		struct vfs *,
		int,
		struct ucred *);

extern int vfs_vget(struct vfs *,
		struct vnode **,
		struct fileid *,
		struct ucred *);

extern int vfs_cntl(struct vfs *,
		int,
		caddr_t,
		size_t,
		struct ucred *);

extern int vfs_quotactl(struct vfs *,
		int,
		uid_t,
		caddr_t,
		struct ucred *);

extern	int vfs_aclxcntl(struct vfs *,
		struct vnode *,
		int,
		struct uio *,
		size_t *,
		struct ucred *); 

/*
 * Function prototypes for various exported services 
 * that support the vfs/vnode interfaces.
 */

/* release a vfs after all vnodes for it have been closed/deallocated */
extern int vfsrele(struct vfs *);

/* increment the use count of a vfs */
extern void vfs_hold(struct vfs *);

/* decrement the use count of a vfs */
extern void vfs_unhold(struct vfs *);

/* execute a specified function for each vfs in the system */
extern int vfs_search(
	int (*)(),			/* pointer to search function	*/
	caddr_t);			/* arguments to search function	*/

/* allocate a vnode to a vfs */
struct gnode;
extern int vn_get(
	struct vfs *,
	struct gnode *,
	struct vnode **);

/* free a vnode allocated by vn_get */
extern int vn_free(struct vnode *);

/* get a pointer to the vnode associated with a given file id */
extern int fidtovp(
	fsid_t *,			/* pointer to file system id struct */
        struct fileid  *,		/* pointer to the file id struct    */
        struct vnode **,		/* pointer to vnode pointer         */
        struct ucred *);		/* pointer to credentials           */

/* exported lookup interface for loadable file systems.
 * Return a vnode for the given name which must be in SYS space.
 */
extern int lookupvp(
        char *          name,
        int             flags,
        struct vnode ** vpp,
        struct ucred *  crp);

#endif /* __64BIT_KERNEL || __FULL_PROTO */
#endif /* _KERNEL */

#endif /* _H_VFS */
