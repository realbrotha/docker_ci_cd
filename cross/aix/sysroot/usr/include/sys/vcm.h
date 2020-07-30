/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/sys/vcm.h 1.5                                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2003               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)73     1.5  src/bos/kernel/sys/vcm.h, sysvcm, bos53H, h2005_50B2 12/11/05 13:12:00 */
#ifndef _H_VCM
#define _H_VCM

#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/vfs.h>
#include <sys/vattr.h>
#include <sys/cred.h>

/*
 * Basic VCM types used in various VCM APIs.
 */
typedef uint16_t vcm_opRights_t;
typedef uint32_t vcm_clientHandle_t;
typedef void * vcm_vfsHandle_t;
typedef void * vcm_peerHandle_t;
typedef uint64_t vcm_opHandle_t;
typedef void * vcm_createTag_t;
typedef void * vcm_openTag_t;


#define VCM_VERSION_1		1
#define VCM_LATEST_VERSION	VCM_VERSION_1

#define VCM_MAX_CLIENTS 4
#define VCM_MAX_CLIENTS_PER_VFS VCM_MAX_CLIENTS

/*
 * VCM operation rights values
 */
#define VCM_OR_OPEN_R		0x0001	/* open for read */
#define VCM_OR_OPEN_W		0x0002	/* open for write */
#define VCM_OR_OPEN_DENY_R	0x0004	/* open and deny others from reading */
#define VCM_OR_OPEN_DENY_W	0x0008	/* open and deny others from writing */
#define VCM_OR_OBJ_R		0x0010  /* object data and attrs read */
#define VCM_OR_OBJ_W		0x0020	/* object data and attrs write */

#define VCM_OR_NUM_RIGHTS	6	/* number of defined VCM rights.
					 * must be updated if rights are added.
					 */

/*
 * Helpful defines
 */
#define VCM_OR_OPEN_RIGHTS \
    (VCM_OR_OPEN_R | VCM_OR_OPEN_W | VCM_OR_OPEN_DENY_R | VCM_OR_OPEN_DENY_W)

#define VCM_OR_OBJ_MASK	(VCM_OR_OBJ_R | VCM_OR_OBJ_W)

#define VCM_OR_ALL_RIGHTS (VCM_OR_OPEN_RIGHTS | VCM_OR_OBJ_MASK)

#define VCM_OR_DENY_RIGHTS (VCM_OR_OPEN_DENY_R | VCM_OR_OPEN_DENY_W)


/*
 * Types and definitions related the VCM client registration
 */
typedef struct vcm_clientIinfo {
    int version;
    uint32_t client_flags;
    int (*revoke_fcn)(vcm_opHandle_t, vcm_opRights_t, uint64_t, uint32_t);
} vcm_clientInfo_t;

/*
 * useFlags for vcm_openVFS()
 */
#define VCM_OVFS_RO		0x0001

/*
 * vfsFlags returned by vcm_openVFS()
 */
#define VCM_VFS_F_RTN_OPENS	0x0001	/* promptly return open rights
					   when not needed */
#define VCM_VFS_VREG		0x0002	/* VCM rights are monintored and
					 * enforced on files for this
					 *  VFS */
#define VCM_VFS_VDIR		0x0004	/* VCM rights are monintored and
					 * enforced for on dirs for this
					 *  VFS */
#define VCM_VFS_VLNK		0x0008	/* VCM rights are monintored and
					 * enforced for on symlinks for this
					 *  VFS */

/*
 * Helpful define for processing
 */
#define VCM_VFS_OBJTYPES    (VCM_VFS_VREG | VCM_VFS_VDIR | VCM_VFS_VLNK)


/* 
 * Request flags for vcm_getOpRights()
 */
#define VCM_GR_OPHANDLE		0x0001	/* Caller is providing a valid
					 * op handle from a previous call */
#define VCM_GR_OPT_GRANT	0x0002	/* Its ok to optimistacally grant
					 * addtional rights. */
#define VCM_GR_NOWAIT		0x0004  /* Don't wait for rights that may
					 * take extensive processing to get.
				 	 */

#define VCM_GR_FLAGS_MASK \
    (VCM_GR_OPHANDLE | VCM_GR_OPT_GRANT | VCM_GR_NOWAIT)

/*
 * Revoke flags used in client revoke function calls
 */
#define VCM_RVK_NOWAIT	0x1	/* Don't wait if revocation would require
				 * extensive processing such as network
				 * calls. Instead do the revocation
				 * asynchronously
				 */
#define VCM_RVK_FORCE	0x2	/* This is a forced revoke. The caller
				 * will reclaim the rights regardless of the
				 * revokee's response.
				 */
#define VCM_RVK_GC	0x4	/* This revoke is being issued as a result
				 * of low resources by the caller.
				 */

/*
 * openStatusFlags values for vcm_endCreate().
 */
#define VCM_ENDCR_NEW_OPH 0x1	/* The returned op handle represents
				 * newly created state from the begin/end
				 * create sequence and the caller's supplied
				 * revokeTag has been associated with the
				 * op handle. The absence of this flag
				 * indicates VCM found existing state on
				 * the related object for the caller and
				 * is returning an opHandle for the found
				 * state. The caller should not assume its
				 * supplied revoke tag was accepted. It
				 * should use the returned ophandle to find
				 * the existing state it has associated with
				 * the opHandle and update it as appropriate.
				 */

/*
 * ================================================
 * ================================================
 * VCM CLIENT APIS
 * ================================================
 * ================================================
 */
int vcm_clientRegister(vcm_clientInfo_t *clInfop,
	vcm_clientHandle_t *chp, uint32_t *versionp);
int vcm_clientUnregister(vcm_clientHandle_t chandle);
int vcm_openVFS(vcm_clientHandle_t ch, vfs_t *vfsp,
	uint32_t useFlags, vcm_vfsHandle_t *vfsHandle, uint32_t *vfsFlags);
int vcm_closeVFS(vcm_vfsHandle_t vfsHandle);
int vcm_getOpRights(vcm_vfsHandle_t vfsH, struct fileid *ofidp,
	vcm_opRights_t *rightsp, uint32_t requestFlags,
	uint64_t revoke_tag, vcm_opHandle_t *opHandlep);
int vcm_returnOpRights(vcm_opHandle_t opH,
		       struct fileid *ofidp, vcm_opRights_t rights);
int vcm_beginCreate(vcm_vfsHandle_t vfsH, struct fileid *dirFidp,
	char *objName, vcm_opRights_t openRights, uint32_t requestFlags,
	vcm_createTag_t *ctag);
int vcm_endCreate(vcm_vfsHandle_t vfsH, vcm_createTag_t ctag,
	struct fileid *objFidp, uint64_t *revokeTagp, vcm_opHandle_t *ohp,
	vcm_opRights_t *grantedRightsp, uint32_t *openStatusFlagsp);

/*
 * ================================================
 * ================================================
 * VCM peer APIs and related parameter definitions
 * ================================================
 * ================================================
 */

typedef struct peerOpInfo {
    void *objHandle;
    uint64_t peerOpHandle;
    uint32_t requestFlags;
    vcm_opRights_t rights;
    uint64_t revokeTag;
} vcm_peerOpInfo_t;


typedef struct peerCreateReq {
    uint64_t peerTag;
    uint32_t requestFlags;
    vcm_opRights_t *rightsp;
    uint64_t revokeTag;
    void *objHandle;
    uint64_t peerOpHandle;
    uint32_t resultFlags;
} vcm_peerCreateReq_t;

/*
 * Result flags for vcm_peerCreateReq_t
 */
#define VCM_P_CREQ_F_CREATE	0x1 /* peer actually created object */


typedef struct vcm_peerInfo {
    uint64_t peerTag;
    uint32_t peerFlags;
    struct gfs *peerGFSP;	/* referencing gfs structure used by peer */
    int gfsno;			/* gfsno used by the peer during gfsadd() */
    int (*fidToObjHandle)(uint64_t peerTag, vfs_t *vfsp,
	struct fileid *objFidp,	void **objHandlep);
    int (*releaseObjHandle)(uint64_t peerTag, void *objHandle);
    int (*getOpRights)(uint64_t peerTag, vcm_peerOpInfo_t *opInfop);
    int (*returnOpRights)(uint64_t peerTag, vcm_peerOpInfo_t *opInfop);
    int (*openObject)(vnode_t *vp, int32long64_t flags, ext_t ext,
	caddr_t *vinfop, cred_t *credp, uint64_t peerTag,
	void *objHandle, uint64_t peerOpHandle);
    int (*createObject)(vnode_t *dvp, vnode_t **vpp,
	int32long64_t oflags, char *name, vattr_t *vap,
	int32long64_t vcflags, caddr_t *vinfop, cred_t *credp,
	vcm_peerCreateReq_t *createReqp);
} vcm_peerInfo_t;


/*
 * Flags for vcm_peerRegister()
 */
#define VCM_PRGY_RTN_OPENS	VCM_VFS_F_RTN_OPENS
#define VCM_PRGY_ENF_VREG	VCM_VFS_VREG
#define VCM_PRGY_ENF_VDIR	VCM_VFS_VDIR
#define VCM_PRGY_ENF_VLNK	VCM_VFS_VLNK

#define VCM_PRGY_FLAGS_MASK (VCM_PRGY_RTN_OPENS | \
    VCM_PRGY_ENF_VREG | VCM_PRGY_ENF_VDIR | VCM_PRGY_ENF_VLNK)

/*
 * Flags for getOpRights peer method
 */
#define VCM_P_GR_NOWAIT		0x1

/*
 * Flags for returnOpRights peer method
 */
#define VCM_P_RR_REL_OBJ		0x1

/*
 * Flags for vcm_peerRevoke(). They are direct mappings to the
 * VCM client revoke flags.
 */
/* peer does not want to wait (block) for an extended period. */
#define VCM_P_RVK_NOWAIT   VCM_RVK_NOWAIT

/* peer is reclaiming rights regardless of the revoke status */
#define VCM_P_RVK_FORCE    VCM_RVK_FORCE

/* peer is low on resources */
#define VCM_P_RVK_GC	   VCM_RVK_GC


/* -------------------------------------------------------------------	*/
/* VCM Monitor								*/
/* -------------------------------------------------------------------	*/
#define VCM_MAX_MONITORS	(1)		/* max monitors per VFS */
#define VCM_MON_VFS_UMOUNT	(0x0001)	/* un-mount of VFS pending */

typedef uint64_t vcm_monitorHandle_t;

struct vcm_monitorInfo
{
	uint32_t	version;
	fsid_t		fsdev;		/* the file systems devno */
	uint32_t	monitor_flags;
	uint64_t	monitor_tag;
	void		(*monitor_fcn)(vfs_t *, struct fileid *, 
					uint64_t, uint32_t);
};
typedef struct vcm_monitorInfo vcm_monitorInfo_t;

/*
 * Formal VCM APIs for use by peers
 */
int vcm_peerRegister(vcm_peerInfo_t *peerInfop, vcm_peerHandle_t *phandlep);
int vcm_peerUnregister(vcm_peerHandle_t phandle);
int vcm_peerRevoke(vcm_peerHandle_t phandle, void *objHandle,
		   uint64_t peerOpHandle, uint64_t revokeTag,
		   vcm_opRights_t rights, uint32_t revokeFlags,
		   boolean_t *releaseHandles);

/*
 * VCM_VNOP_... operations. VCM clients should use these macros instead of
 * the base AIX set defined in /usr/include/sys/vnode.h. This set of
 * functions takes into account that the client is managing VCM rights.
 * A VCM client that does not use these defintions, and instead uses the
 * base AIX VNOP_... calls may experience unexpected results including the
 * possibility of infinite hangs. The basic function of the O/S could even
 * be impacted.
 */

#if 1 /* XXX, will be put in place in final version - #ifdef _KERNEL */

/*
 * Macros for the vnode operations.
 */
#define VCM_VNOP_ACCESS(ch, vp, mode, who, ucred) \
	vcm_vnop_access(ch, vp, mode, who, ucred)
#define VCM_VNOP_CLOSE(ch, vp, flags, vinfo, ucred) \
	vcm_vnop_close(ch, vp, flags, vinfo, ucred)
#define VCM_VNOP_CREATE(ch, dp, vpp, flags, name, mode, vinfo, ucred) \
	vcm_vnop_create(ch, dp, vpp, flags, name, mode, vinfo, ucred)
#define VCM_VNOP_FCLEAR(ch, vp, flags, offset, length, vinfo, ucred) \
	vcm_vnop_fclear(ch, vp, flags, offset, length, vinfo, ucred)
#define VCM_VNOP_FID(ch, vp, fid, ucred) \
	vcm_vnop_fid(ch, vp, fid, ucred)
#define VCM_VNOP_FSYNC(ch, vp, flags, vinfo, ucred) \
	vcm_vnop_fsync(ch, vp, flags, vinfo, ucred)
#define VCM_VNOP_FTRUNC(ch, vp, flags, length, vinfo, ucred) \
	vcm_vnop_ftrunc(ch, vp, flags, length, vinfo, ucred)
#define VCM_VNOP_GETACL(ch, vp, uiop, ucred) \
	vcm_vnop_getacl(ch, vp, uiop, ucred)
#define VCM_VNOP_GETATTR(ch, vp, vattrp, ucred) \
	vcm_vnop_getattr(ch, vp, vattrp, ucred)
#define VCM_VNOP_GETPCL(ch, vp, uiop, ucred) \
	vcm_vnop_getpcl(ch, vp, uiop, ucred)
#define VCM_VNOP_HOLD(ch, vp) \
	vcm_vnop_hold(ch, vp)
#define VCM_VNOP_IOCTL(ch, vp, cmd, arg, flags, ext, ucred) \
	vcm_vnop_ioctl(ch, vp, cmd, arg, flags, ext, ucred)
#define VCM_VNOP_LINK(ch, vp, dp, target, ucred) \
	vcm_vnop_link(ch, vp, dp, target, ucred)
#define VCM_VNOP_LOCKCTL(ch, vp, offset, lckdat, cmd, \
					retry_fcn, retry_id, ucred) \
	vcm_vnop_lockctl(ch, vp, offset, lckdat, cmd, \
					retry_fcn, retry_id, ucred)
#define VCM_VNOP_LOOKUP(ch, dp, vpp, nam, flags, vattrp, ucred) \
	vcm_vnop_lookup(ch, dp, vpp, nam, flags, vattrp, ucred)
#define VCM_VNOP_MAP(ch, vp, addr, length, offset, flags, ucred) \
	vcm_vnop_map(ch, vp, addr, length, offset, flags, ucred)
#define VCM_VNOP_MKDIR(ch, vp, name, mode, ucred) \
	vcm_vnop_mkdir(ch, vp, name, mode, ucred)
#define VCM_VNOP_MKNOD(ch, vp, name, mode, dev, ucred) \
	vcm_vnop_mknod(ch, vp, name, mode, dev, ucred)
#define VCM_VNOP_OPEN(ch, oph, vp, flags, ext, vinfop, ucred) \
	vcm_vnop_open(ch, oph, vp, flags, ext, vinfop, ucred)
#define VCM_VNOP_SELECT(ch, vp, correl, reqevents, \
					rtnevents, notify, vi, credp) \
	vcm_vnop_select(ch, vp, correl, reqevents, \
					rtnevents, notify, vi, credp)
#define VCM_VNOP_RDWR(ch, vp, op, flags, uiop, ext, vinfo, vattrp, ucred) \
	vcm_vnop_rdwr(ch, vp, op, flags, uiop, ext, vinfo, vattrp, ucred)
#define VCM_VNOP_READDIR(ch, vp, uiop, ucred) \
	vcm_vnop_readdir(ch, vp, uiop, ucred)
#define VCM_VNOP_READLINK(ch, vp, uiop, ucred) \
	vcm_vnop_readlink(ch, vp, uiop, ucred)
#define VCM_VNOP_RELE(ch, vp) \
	vcm_vnop_rele(ch, vp)
#define VCM_VNOP_REMOVE(ch, dp, vp, name, ucred) \
	vcm_vnop_remove(ch, dp, vp, name, ucred)
#define VCM_VNOP_RENAME(ch, vp, dp, name, tvp, tdp, tname, ucred) \
	vcm_vnop_rename(ch, vp, dp, name, tvp, tdp, tname, ucred)
#define VCM_VNOP_REVOKE(ch, vp, cmd, flags, vattrp, ucred) \
	vcm_vnop_revoke(ch, vp, cmd, flags, vattrp, ucred)
#define VCM_VNOP_RMDIR(ch, vp, dp, name, ucred) \
	vcm_vnop_rmdir(ch, vp, dp, name, ucred)
#define VCM_VNOP_SETACL(ch, vp, uiop, ucred) \
	vcm_vnop_setacl(ch, vp, uiop, ucred)
#define VCM_VNOP_SETATTR(ch, vp, op, arg1, arg2, arg3, ucred) \
	vcm_vnop_setattr(ch, vp, op, arg1, arg2, arg3, ucred)
#define VCM_VNOP_SETPCL(ch, vp, uiop, ucred) \
	vcm_vnop_setpcl(ch, vp, uiop, ucred)
#define VCM_VNOP_STRATEGY(ch, vp, bp, ucred) \
	vcm_vnop_strategy(ch, vp, bp, ucred)
#define VCM_VNOP_SYMLINK(ch, vp, name, target, ucred) \
	vcm_vnop_symlink(ch, vp, name, target, ucred)
#define VCM_VNOP_UNMAP(ch, vp, addr, ucred) \
	vcm_vnop_unmap(ch, vp, addr, ucred)
#define VCM_VNOP_SEEK(ch, vp, off, ucred) \
	vcm_vnop_seek(ch, vp, off, ucred)

#define VCM_VNOP_FSYNC_RANGE(ch, vp, flags, vinfo, off, len, ucred) \
	vcm_vnop_fsync_range(ch, vp, flags, vinfo, off, len, ucred)
#define VCM_VNOP_CREATE_ATTR(ch, ctag, dp, vpp, flags, \
					name, vap, vcf, vinfo, ucred) \
	vcm_vnop_create_attr(ch, ctag, dp, vpp, flags, \
					name, vap, vcf, vinfo, ucred)
#define	VCM_VNOP_FINFO(ch, vp, cmd, p, len, ucred) \
	vcm_vnop_finfo(ch, vp, cmd, p, len, ucred)
#define	VCM_VNOP_MAP_LLOFF(ch, vp, a, len, off, mf, ff, ucred) \
	vcm_vnop_map_lloff(ch, vp, a, len, off, mf, ff, ucred)
#define	VCM_VNOP_READDIR_EOFP(ch, vp, uiop, eofp, ucred) \
	vcm_vnop_readdir_eofp(ch, vp, uiop, eofp, ucred)
#define VCM_VNOP_RDWR_ATTR(ch, vp, rw, ff, uio, x, vi, pre, post, ucred) \
	vcm_vnop_rdwr_attr(ch, vp, rw, ff, uio, x, vi, pre, post, ucred)

#define VCM_VNOP_MEMCNTL(ch, vp, cmd, arg, ucred) \
	vcm_vnop_memcntl(ch, vp, cmd, arg, ucred)


#define VCM_VNOP_SETXACL(ch, vp, ctl_flags, acl_type, uiop, mode, ucred) \
	vcm_vnop_setxacl(ch, vp, ctl_flags, acl_type, uiop, mode, ucred) 

#define VCM_VNOP_GETXACL(ch, vp, ctl_flag, acl_typep, uiop, sizep, modep, ucred) \
	vcm_vnop_getxacl(ch, vp, ctl_flag, acl_typep, uiop, sizep, modep, ucred) 
#define VCM_VNOP_SETACL(ch, vp, uiop, ucred) \
	vcm_vnop_setacl(ch, vp, uiop, ucred) 				

#define VCM_VNOP_GETACL(ch, vp, uiop, ucred) \
	vcm_vnop_getacl(ch, vp, uiop, ucred) 

/*
 * Function prototypes for VCM vnop wrapper functions.
 */
int vcm_vnop_access(vcm_clientHandle_t, vnode_t *, int32long64_t,
	int32long64_t, cred_t *);

int vcm_vnop_close(vcm_clientHandle_t, vnode_t *, int32long64_t,
	caddr_t, cred_t *);

int vcm_vnop_create(vcm_clientHandle_t, vcm_createTag_t, vnode_t *, vnode_t **,
	int32long64_t, char *, int32long64_t, caddr_t *, cred_t *);

int vcm_vnop_fclear(vcm_clientHandle_t, vnode_t *, int32long64_t,
	offset_t, offset_t, char *, cred_t *);

int vcm_vnop_fid(vcm_clientHandle_t, vnode_t *, struct fileid *, cred_t *);

int vcm_vnop_fsync(vcm_clientHandle_t, vnode_t *, int32long64_t,
	int32long64_t, cred_t *);

int vcm_vnop_ftrunc(vcm_clientHandle_t, vnode_t *, int32long64_t,
	offset_t, caddr_t, cred_t *);

int vcm_vnop_getacl(vcm_clientHandle_t, vnode_t *, struct uio *, cred_t *);

int vcm_vnop_getattr(vcm_clientHandle_t, vnode_t *, struct vattr *, cred_t *);

int vcm_vnop_getpcl(vcm_clientHandle_t, vnode_t *, struct uio *, cred_t *);

int vcm_vnop_hold(vcm_clientHandle_t, vnode_t *);

int vcm_vnop_ioctl(vcm_clientHandle_t, vnode_t *, int32long64_t,
	caddr_t, size_t, ext_t, cred_t *);

int vcm_vnop_link(vcm_clientHandle_t, vnode_t *, vnode_t *,
	char *, cred_t *);

int vcm_vnop_lockctl(vcm_clientHandle_t, vnode_t *,	
	offset_t, struct eflock *,
	int32long64_t, int (*)(), ulong *, cred_t *);

int vcm_vnop_lookup(vcm_clientHandle_t, vnode_t *, vnode_t **, char *,
	int32long64_t, struct vattr *, cred_t *);

int vcm_vnop_map(vcm_clientHandle_t, vnode_t *, caddr_t, uint32long64_t,
	uint32long64_t,	uint32long64_t,	cred_t *);

int vcm_vnop_mkdir(vcm_clientHandle_t, vnode_t *, char *,
	int32long64_t, cred_t *);

int vcm_vnop_mknod(vcm_clientHandle_t, vnode_t *, caddr_t,
	int32long64_t, dev_t, cred_t *);

int vcm_vnop_open(vcm_clientHandle_t, vcm_opHandle_t oph, vnode_t *,
	int32long64_t, ext_t, caddr_t *, cred_t *);

int vcm_vnop_select(vcm_clientHandle_t, vnode_t *, int32long64_t,
	ushort,	ushort *, void (*)(), caddr_t, cred_t *);

int vcm_vnop_rdwr(vcm_clientHandle_t, vnode_t *, enum uio_rw, int32long64_t,
	struct uio *, ext_t, caddr_t, struct vattr *, cred_t *);

int vcm_vnop_readdir(vcm_clientHandle_t, vnode_t *, struct uio *, cred_t *);

int vcm_vnop_readlink(vcm_clientHandle_t, vnode_t *, struct uio *, cred_t *);

int vcm_vnop_rele(vcm_clientHandle_t, vnode_t *);

int vcm_vnop_remove(vcm_clientHandle_t, vnode_t *, vnode_t *,
	char *,	cred_t *);

int vcm_vnop_rename(vcm_clientHandle_t, vnode_t *, vnode_t *, caddr_t,
	vnode_t *, vnode_t *, caddr_t, cred_t *);

int vcm_vnop_revoke(vcm_clientHandle_t, vnode_t *, int32long64_t,
	int32long64_t, struct vattr *, cred_t *);

int vcm_vnop_rmdir(vcm_clientHandle_t, vnode_t *, vnode_t *, char *, cred_t *);

int vcm_vnop_setacl(vcm_clientHandle_t, vnode_t *, struct uio *, cred_t *);

int vcm_vnop_setattr(vcm_clientHandle_t, vnode_t *, int32long64_t,
	int32long64_t, int32long64_t, int32long64_t, cred_t *);

int vcm_vnop_setpcl(vcm_clientHandle_t, vnode_t *, struct uio *, cred_t *);

int vcm_vnop_strategy(vcm_clientHandle_t, vnode_t *, struct buf *, cred_t *);

int vcm_vnop_symlink(vcm_clientHandle_t, vnode_t *, char *, char *, cred_t *);

int vcm_vnop_unmap(vcm_clientHandle_t, vnode_t *, int32long64_t, cred_t *);

int vcm_vnop_seek(vcm_clientHandle_t, vnode_t *, offset_t *, cred_t *);

int vcm_vnop_fsync_range(vcm_clientHandle_t, vnode_t *, int32long64_t,
	int32long64_t, offset_t, offset_t, cred_t *);

int vcm_vnop_create_attr(vcm_clientHandle_t, vcm_createTag_t,
	vnode_t *, vnode_t **,	int32long64_t, char *, struct vattr *,
	int32long64_t, caddr_t *, cred_t *);

int vcm_vnop_finfo(vcm_clientHandle_t, vnode_t *, int32long64_t,
	void *, size_t, cred_t *);

int vcm_vnop_map_lloff(vcm_clientHandle_t, vnode_t *, caddr_t,
	offset_t, offset_t, uint32long64_t, uint32long64_t, cred_t *);

int vcm_vnop_readdir_eofp(vcm_clientHandle_t, vnode_t *, struct uio *,
	int *, cred_t *);

int vcm_vnop_rdwr_attr(vcm_clientHandle_t, vnode_t *, enum uio_rw,
	int32long64_t, struct uio *, ext_t, caddr_t, struct vattr *,
	struct vattr *, cred_t *);

int vcm_vnop_memcntl(vcm_clientHandle_t, vnode_t *, int, void *, cred_t *);

int vcm_vnop_setxacl(vcm_clientHandle_t ch, vnode_t *vp, uint64_t ctl_flag, acl_type_t acl_type, struct uio *uiop, mode_t mode, cred_t *crp);

int vcm_vnop_getxacl(vcm_clientHandle_t ch, vnode_t *vp, uint64_t ctl_flag, acl_type_t *acl_typep, struct uio *uiop, size_t * acl_szp, mode_t * modep, cred_t *cp);

int vcm_vnop_getacl(vcm_clientHandle_t ch, vnode_t *vp, struct uio *uiop, cred_t *cp);

int vcm_vnop_setacl(vcm_clientHandle_t ch, vnode_t *vp, struct uio *uiop, cred_t *cp);

int vcm_monitorRegister(vcm_monitorInfo_t *, vcm_monitorHandle_t *);
int vcm_monitorUnregister(vcm_monitorHandle_t);
int vcm_start_vfs_monitor(vcm_monitorHandle_t);
int vcm_stop_vfs_monitor(vcm_monitorHandle_t);

#endif /*_KERNEL*/

#endif /* _H_VCM */
