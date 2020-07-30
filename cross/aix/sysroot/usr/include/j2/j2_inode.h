/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/j2/include/j2_inode.h 1.67.1.10                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1999,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)91     1.67.1.10  src/bos/kernel/j2/include/j2_inode.h, sysj2, bos53X, x2009_34A1 8/12/09 19:51:46 */

/*
 * COMPONENT_NAME: (SYSJ2) JFS2 Physical File System
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1999
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef	_H_J2_INODE
#define _H_J2_INODE	

/*
 * FUNCTION: in-memory inode/vnode cache manager
 */

/*
 * j2_inode.h in userland is just a wrapper for the disk inode
 */
#include <j2/j2_types.h>
#include <sys/vfs.h>          
#include <j2/j2_dinode.h>


#ifdef _KERNEL

#include <sys/ras.h>
#include <j2/j2_snapshot.h>
#include <j2/j2_lock.h>
#include <j2/j2_quota.h>


/*
 *      inode cache hashClass
 *
 * table of inode hash class anchors  where
 * each hash class anchor contains a header for
 * doubly-linked lists of inodes linked via i_hashList
 */
typedef struct iHashClass {
        LIST_HEADER(inode) hc_hashList;
        uint32          hc_timestamp;
        uint32          hc_rmstamp;
        MUTEXLOCK_T     hc_lock;
} iHashClass_t;

struct pile;
/* iCacheClass */

typedef struct iCacheClass {
	MUTEXLOCK_T	cc_lock;
	int32		cc_nInode;	/* # of inode in cacheList  */
	CDLL_HEADER(inode) cc_cacheList;	/* cacheList header */
	struct pile	*cc_pile;	/* inode pile */
	boolean_t 	pileFull;	/* pile is full */
} iCacheClass_t;


/*
 *	 inode cache (iCache) configuration
 */
struct iCache {
	int32	nInode;			/* # of in-memory inode */
	int16	nCacheClass;		/* # of cacheClass */
	struct iCacheClass *cacheTable;
	int32	nInodePerCacheClass;	/* # of inode per cacheClass */
	int32	nHashClass;		/* # of hashClass - 1 */
	int32	nNewHashClass;		/* # of hashClass - 1 */
	int32	nInodePerHashClass; 	/* # of inode per hashClass */
	struct iHashClass **hashTable;
	int32   nPagesPerCacheClass;    /* # of pile pages per cacheClass */
	int32   nMaxInode;         	/* nInode at initialization time */
};

extern struct iCache	iCache;

extern event_t	SyncEvent;	

#ifdef _J2_WIP_EXTVAL
/* extended flags */
typedef struct {
	uint64 data[8];
} extendedValues_t;
#endif

/* (borrowed from JFS)
 * I_SETTIME is a macro used by imark to set the atime, mtime, and
 * ctime fields in the incore inode.  These timestamps are set using
 * tod variable, which is updated by the clock interrupt.  Since 
 * multiple modifications can occur within a single clock interrupt,
 * it's possible to get a duplicate timestamp. If this happens, just
 * increment the nanoseconds field.  If that goes over a billion
 * (NS_PER_SEC), then roll it over into the next second.  Yuk.
 */
#define	I_SETTIME(ts,t)							\
	if (((ts).tj_sec == (t).tv_sec   &&				\
	     (ts).tj_nsec >= (t).tv_nsec &&				\
	     (t).tv_nsec < (ts).tj_nsec + NS_PER_TICK) ||		\
	    ((ts).tj_sec == (t).tv_sec+1 &&				\
	     (ts).tj_nsec + NS_PER_SEC < (t).tv_nsec + NS_PER_TICK))	\
	{								\
		if (++((ts).tj_nsec) >= NS_PER_SEC)			\
			((ts).tj_sec)++, ((ts).tj_nsec) = 0;		\
	}								\
	else								\
	{								\
		(ts).tj_sec = t.tv_sec;					\
		(ts).tj_nsec = t.tv_nsec;				\
	}


/*
 *	in-memory inode
 *
 * inode resides as part of xnode (vnode + inode) aligned on 8-byte boundary
 * consisting of working area (winode) embedding generic inode (ginode),
 * and on-disk inode area (dinode);
 *
 * for vnode and gnode, ref. sys/vnode.h
 * for dinode, ref. j2_dinode.h
 */
/*
 *	in-memory working area (wInode)
 */
struct wInode {
	LIST_ENTRY(inode)	i_hashList;	/* hashList link */
	union {
		CDLL_ENTRY(inode) i_cacheList;	/* cacheList link */
		struct inode	*i_freeNext;	/* freeList link */
	};
	
	uint32		i_hashClass;
	int16		i_cacheClass;
	eye_catch2b_t	i_eyec;		/* eye-catcher (EYEC_INODE) */

	/*
	 * reference count: note, if you change this, you should
	 * change i_counter32_{1,2} below as they are dio/nondio
	 * counters.
	 */
	uint32		i_count;	
	uint32		i_capability;	/* capability */

	/* AIX gnode embedded: ref. sys/vnode.h */
	struct gnode	i_gnode;

	dev_t		i_dev;		/* device id */
	struct inode	*i_ipmnt;	/* mounted aggregate inode */
	struct inode	*i_ipimap;	/* mounted fileset inode */

	uint16		i_flag;	/* */
	uint16		i_cflag;	/* commit flags */
	uint16		i_xlock;	/* inode event synchronization */
	uint16		i_fsxlock;	/* fs event synchronization */

	event_t		i_event;	/* eventlist for inode activity */
	event_t		i_fsevent;	/* eventlist for fs activity */
	event_t		i_openevent;	/* eventlist for nshare open modes */
	MUTEXLOCK_T	i_nodelock;	/* inode lock */

	int64		i_agstart;	/* start xaddr of ag */

	/*
	 *	file read/write control:
	 */
	RDWRLOCK_T	i_rdwrlock;	/* read/write lock */
	struct pagerObject	*i_pagerObject;/* meta-data memory object */

	/* anonymous tlock list header: N.B. i_atlhead is overlaid as tlock_t ! */
	struct txLock	*i_atlHead;	/* anonymous tlock list head */
	struct txLock	*i_atlTail;	/* anonymous tlock list tail */

	/* pseudo buffer header for btRoot (next 4 fields must be contiguous) */
	uint16	i_bxflag;		/* pb_xflag of pseudo jbuf of btRoot */
	int16	i_bnohomeok;	/* pb_nohomeok of pseudo jbuf of btRoot  */
	int32	i_bflags;		/* pb_flags of pseudo jbuf of btRoot */
	struct txLock	*i_blid;	/* pb_lid of pseudo jbuf of btRoot */

	int64		i_lastCommittedSize;
	time_t		i_synctime;	/* first modified time */
	int32		i_newMeta;	/* new metadata since last commit? */

	/* btree search heuristics */
	int16		i_btorder;	/* access order */		
	int16		i_btindex;	/* btpage entry index */

	/*
	 * File type dependent counters.  For regular files these are
	 * used to track dio/nondio writers. Keep as large as i_count!
	 */
	union {
		struct {
			uint32	i_counter32_1;
			uint32	i_counter32_2;
		};
		struct {
			uint32	i_diocnt;
			uint32	i_nondiocnt;
		};
		struct {
			uint32	i_delTreePages;
		};
	};

	/* extended attributes: ACL */
	struct inode	*i_ipacl;	/* aclObject */

	/* DMAPI */
	void		*i_kdmvp;	/* DMAPI: kdm object for managed fs */
	uint32		i_kdmchange;	/* DMAPI: modification indicator    */

	/* QUOTAS */
	caddr_t		i_quce[MAXQUOTAS];	/* 16: NULL or constant     */

	uint32		i_exception;		/* inode exception */

#ifdef _J2_WIP_EXTVAL
	extendedValues_t *i_extendedValues; /* Rare, extended flags (see below) */
#endif
};

/*
 *	mounted filesystem inode.
 *
 * represented by convention in-memory inode 
 * (dev_t of mounted file system device, i_number = 0)
 */
struct mntInode {
	/* following 3 fields must match dinode struct */
	ino64_t	iNumber;	/* 8: inode number, aka file serial number */
	uint32	gNumber;	/* 4: inode generation number */
	uint32	fileset;	/* 4: fileset #, inode # of inode map file */

	uint32	i_mntflag;	/* 4: flags */
	int32	i_mntstate;	/* 4: state */

	/* vfs linkage */
	struct vfs	*i_vfs;			/* 8: corresponding vfs */
	CDLL_ENTRY(inode)	i_mountList;	/* 16: mount list link */

	/* device parameters */
	struct file	*i_devfp;		/* 8: fs device file */
	struct pagerDevice *i_pagerDevice;	/* 8: pager device */

	uint64	i_blocks;	/* 8: file system size in 512 byte blks */
	int32	i_bsize;	/* 4: file system block size in byte */
	int16	i_l2bsize;	/* 2: log2(bsize) */
	int16	i_pbsize;	/* 2: physical block size in bytes */
	int16	i_l2pbsize;	/* 2: log2(pbsize) */
	int16	i_l2bfactor;	/* 2: log2(bsize/pbsize) */
	int16	i_nbperpage;	/* 2: PSIZE/s_bsize */
	int16	i_l2nbperpage;	/* 2: log2(pfactor) */

	/* meta-data files */
	struct inode	*i_ipaimap;	/* 8: primary aggregate imap */
	struct inode	*i_ipbmap;	/* 8: block alloc map */

	struct inode	*i_iplog;	/* 8: log inode */
	dev_t	i_logdev;		/* 8: log device */
	pxd_t	i_logpxd;		/* 8: inline log pxd */

	/* per filesystem resource */
	int32	i_fsTid;		/* 4: fs reserved tid */
	uint32	i_errlog;		/* 4: error log flag */

	MUTEXLOCK_T	i_renamelock;	/* 8: rename lock */
	MUTEXLOCK_T	i_cursorLock; 	/* 8: vnode cursor use lock */

	/* extension linkage */
	struct inode	*i_ipSnapshot;	/* 8: current/active snapshot */	

	void		*i_kdmfset;	/* 8: DMAPI fset */

	void		*i_qctl;	/* 8: quota ctl */
	RDWRLOCK_T	i_qlock;	/* 8: quota ctl */
	RDWRLOCK_T	i_qcachelock;	/* 8: quota ctl */

	struct inode	*i_ipzombie;	/* 8: Pointer to EAv2 Zombie dir */

	event_t		i_quiesceEvent;	/* 8: eventlist for quiesce */
	struct trb	*i_trb;		/* 8: timer */

	ras_block_t	i_rasbFS;	/* 8: per FS parent component */
	ras_block_t	i_rasbMeta;	/* 8: per FS metadata component */
	ras_block_t	i_rasbUser;	/* 8: per FS userdata component */
	ras_block_t	i_rasbSnap;	/* 8: per FS snapshot component */

	/* snapshot (only present on ISNAPSHOT inodes) */
	struct snapshotObject	i_snapshot;
};

/* mntInodeParanoia -
 *  If you see a compiler error on the following line, it means that
 *  the mntInode structure is greater in size than the dinode
 *  structure, which means all the inodes on the system are growing
 *  because of a bloated mntInode.
 */
struct mntInodeParanoia {
	char paranoia[ (sizeof(struct dinode) >= sizeof(struct mntInode)) ? 1 : -1 ];
};

/*
 *	in-memory inode
 */
struct inode {
	struct wInode;	/* in-memory working information */
	union {
		struct dinode i_dinode;   /* on-disk persistent information */
		struct mntInode; /* file system global information */
	};
};

typedef struct inode	inode_t;

/*
 *	in-memory working inode
 */

/* AIX gnode embedded: ref. sys/vnode.h */
#define	i_memoryObject	i_gnode.gn_seg 
#define i_mwrcnt	i_gnode.gn_mwrcnt
#define	i_mrdcnt	i_gnode.gn_mrdcnt
#define	i_mmapcnt	i_gnode.gn_chan
#define	i_rdcnt		i_gnode.gn_rdcnt
#define	i_wrcnt		i_gnode.gn_wrcnt
#define	i_excnt		i_gnode.gn_excnt
#define	i_rshcnt	i_gnode.gn_rshcnt

/* normal file i_flag */
#define	IACC		0x0001	/* inode access time to be updated */
#define	ICHG		0x0002	/* inode has been changed */
#define	IUPD		0x0004	/* file has been modified */
#define ICIO		0x0008	/* file opened for concurrent i/o */
#define IUNUSED10	0x0010
#define	ISTALE		0x0020	/* stale inode of unmounted file system */
#define	IDIRECT		0x0040	/* file opened for direct i/o */

/* special i_flag, either mount inode or normal */
#define	ISYSTEM		0x1000	/* system/internal file */
#define	ISNAPSHOT	0x2000	/* snapshotFilesystem object */

/* mount inode only i_flag values */
#define	IMNT_EAV2		0x0001	/* EAv2 format file system */
#define IMNT_QUOTASON_UNUSED	0x0002	/* deprecated */
#define IMNT_VIXENABLED		0x0004	/* VIX enabled: sb->s_feature_compat &
					 * J2_COMPAT_VIX */
#define IMNT_VIXPRESENT		0x0008	/* Variable inode extents present on
					 * filesystem: sb->s_feature_incompat &
					 * J2_INCOMPAT_VIX */
#define IMNT_DMAPI		0x0040	/* The DMAPI is enabled for fs, even
					 * if currently mounted w/o a manager.
					 */
#define IMNT_ATIMEOFF           0x0100  /* ATIMEOFF for reads */

#define IMNT_VIX	IMNT_VIXENABLED

/* additional flags passed to iMark, but not put in the inode */
#define ITMPMASK    0xFFFF0000
#define IINVIS	    0x80000000	/* invisible operation, don't set times */
#define INOEV	    0x40000000	/* no event generation on managed fs */

/* i_cflag flags */
#define ICCREATE	0x0001	/* newly created inode   */
#define ICNEW		0x0002	/* no data had been committed */
#define ICNOLINK	0x0004	/* inode committed with zero link count */
#define ICFREEWMAP	0x0008	/* free wMAP at iRemove() */
#define ICEA		0x0010	/* commit EA */
#define ICINLINEDATA	0x0020	/* commit inode inline data. i.e. symlink */
#define ICCLEARXTREE	0x0040	/* commit inode inline data. i.e. symlink */
#define ICMLOCK		0x0100	/* wip: lock memory object */
#define ICFORCE		0x0400	/* force update object */


/* i_xlock flags */
#define	IXLOCK		0x0001	/* inode is in transition */
#define	IXWANT		0x0002	/* some process waiting on lock */
#define	IXSYNC		0x0004	/* sync in progress */
#define	IXHELD		0x0008	/* inode held for iResume */

/* i_fsxlock flags */
#define	FSXLOCK		0x0001	/* fs is in transition */
#define	FSXWANT		0x0002	/* some process waiting on lock */
#define	FSXDMNOSPACE	0x0004	/* inode is pending a DMAPI nospace event */
#define	FSXSNAPSHOT	0x0010	/* bound with snapshot */

/* btree search heuristics */
#define	BT_RANDOM	0x0000
#define	BT_SEQUENTIAL	0x0001
#define	BT_LOOKUP	0x0010
#define	BT_INSERT	0x0020
#define	BT_DELETE	0x0040

/* object inode i_exception */
#define	IXUDRDERR	0x00000001	/* user-data read error */
#define	IXUDWRERR	0x00000002	/* user-data write error */
#define	IXMDRDERR	0x00000004	/* meta-read error */
#define	IXMDWRERR	0x00000008	/* meta-write error */
#define	IXCORRUPT	0x00000010	/* meta-data consistency violation */
#define	IXQUIESCE	0x00000020	/* block further update */
#define	IXISOLATE	0x00000040	/* block further access */
/* mount inode i_exception */
#define	IXFSERROR	0x00010000	/* fs error - mark to repair */
#define	IXLOGERROR	0x00020000	/* log error - mark to repair */
#define	IXFSLOGNOREDO	0x00040000	/* log stale - skip logredo */
#define	IXFSREPAIR	0x00080000	/* marked for repair */
#define	IXFSQUIESCE	0x00100000	/* block further update */
#define	IXFSISOLATE	0x00200000	/* block further access */

/*
 *	on-disk persistent inode
 */
#define	i_number	i_dinode.di_number
#define	i_gen		i_dinode.di_gen
#define	i_fileset	i_dinode.di_fileset
#define	i_inostamp	i_dinode.di_inostamp
#define	i_ixpxd		i_dinode.di_ixpxd
#define i_size		i_dinode.di_size
#define i_nblocks	i_dinode.di_nblocks
#define i_uid		i_dinode.di_uid
#define i_gid		i_dinode.di_gid
#define i_nlink		i_dinode.di_nlink
#define i_mode		i_dinode.di_mode
#define i_atime		i_dinode.di_atime
#define i_ctime		i_dinode.di_ctime
#define i_mtime		i_dinode.di_mtime
#define i_otime		i_dinode.di_otime

/* extended attributes */
#define i_ea		i_dinode.di_ea
#define i_eaRoot	i_dinode.di_eaRoot
#define i_eaFlag	i_dinode.di_eaFlag
#define i_eaDirectory	i_dinode.di_eaDirectory
#define i_eaACL		i_dinode.di_eaACL
#define i_aclType	i_dinode.di_aclType
#define i_aclOwner	i_dinode.di_aclOwner

/* block allocation map */
#define i_bmap		i_dinode.di_bmap

/* inode allocation map */
#define i_gengen	i_dinode.di_gengen
#define i_imap		i_dinode.di_imap
#define i_ipimap2	i_dinode.di_ipimap2

#define i_dxd		i_dinode.di_dxd
#define i_parent	i_dinode.di_parent
#define i_btroot	i_dinode.di_btroot
#define i_inlinedata	i_dinode.di_inlinedata
#define i_inlineea	i_dinode.di_inlineea

/* device special file */
#define i_rdev		i_dinode.di_rdev

/* symbolic link */
#define i_fastsymlink	i_dinode.di_fastsymlink


/*  get block allocation hint as location of disk inode */
#define 	InodeHome(ip)   \
	(addressPXD(&((ip)->i_ixpxd)) + lengthPXD(&((ip)->i_ixpxd)) - 1)

/*
 * vp <-> ip
 */
#define VP2GP(x)	((struct gnode *)((x)->v_gnode))
#define GP2IP(x)	((struct inode *)(((struct gnode *)(x))->gn_data))
#define VP2IP(x)	(GP2IP(VP2GP(x)))
#define IP2GP(x)	((struct gnode *)(&(((struct inode *)(x))->i_gnode)))
#define IP2VP(x)	((struct vnode *)((x)->i_gnode.gn_vnode))

/* handy boolean typology of inode */
#define isSpecial(ip)	((ip)->i_number < ROOT_I)
#define isAcl(ip)	((ip->i_mode & (S_IXATTR|S_IXACL)) == (S_IXATTR|S_IXACL))
#define isSystem(ip)	((ip)->i_flag & ISYSTEM)
#define isReadOnly(ip) (((ip)->i_ipmnt->i_iplog) ? 0 : 1)

#define mayDie(ip) ( pile_object_wanted(ip, 0) )

/* DMAPI_MANAGED() macro indicates that the file system OBJECT is 
 * actively managed.
 *
 * Note that a "dmapi" file system can be force mounted without a manager,
 * so that a file system marked as managed is not being managed at the
 * moment and thus DMAPI_MANAGED is false for a specific object...
 *
 * DMAPI_MANAGED_FS() macro indicates that the FILE SYSTEM has the DMAPI
 * enabled, even if it is not actively managed.
 */
#define DMAPI_MANAGED(ip) (ip->i_ipmnt->i_kdmfset		\
				&& !(ip->i_mode & S_IXATTR)	\
				&& !isSystem(ip))
#define DMAPI_MANAGED_FS(ip) ((ip)->i_ipmnt->i_flag & IMNT_DMAPI)

/* 
 * Atomic operations for set/clear flag.
 */
#define IX_SET(flag, value) (fetch_and_or((atomic_p)&(flag), value))
#define IX_CLEAR(flag, value) (fetch_and_and((atomic_p)&(flag), ~(value)))
#define IX_ISSET(flag, value) ((flag) & (value))

/* iGet() flags */
#define	iGet_CREATE	0x00000001

/* iGetSpecial() flags */
#define iGS_READ	0x00000001
#define iGS_BIND	0x00000002

/*
 * externed globals
 */
extern int32 j2_syncModifiedMapped;
extern int32 j2_unmarkComp;
extern int32 j2_atimeUpdateSymlink;
extern uint32 j2_syncPageCount;
extern uint32 j2_syncPageLimit;
extern uint32 j2_dirSort;

/*
 *	prototypes for inode cache services
 */
reg_t iInit(void);
void  iInitCleanup(void);
void iMark(inode_t *ip, int32 flag);
void iWriteLockList(int32 n, inode_t **iplist);
int32 iReadLockx(inode_t *ip);
int32 iWriteLockx(inode_t *ip);
void inodeLockx(inode_t *ip);
int32 iReadUnlockx(inode_t *ip);
int32 iWriteUnlockx(inode_t *ip);
void inodeUnlockx(inode_t *ip);
reg_t iGet(struct vfs *vfsp, ino64_t ino, inode_t **ipp, reg_t flag);
reg_t iActivate(inode_t *ip, uint32 capability);
reg_t iRecycle(inode_t *ip, uint32 free);
reg_t iPut(inode_t *ip, struct vfs *vfsp);
reg_t iCreate(struct vfs *vfsp, inode_t *pip, struct vattr *vap, inode_t **ipp,
	struct ucred *crp);
reg_t iHold(inode_t *ip);
void iMarkException(inode_t *ip, int32 exception);
reg_t iVGet(struct vfs *vfsp, dev_t dev, ino64_t ino, inode_t **ipp);
void iCapability(inode_t *ip);
reg_t iGetSpecial(inode_t *ipmnt, inode_t *ipimap, dev_t devno, ino64_t fsno,
		  ino64_t ino, inode_t **ipp, int64 offset, reg_t flag);
reg_t iPutSpecial(inode_t *ip);
void  iSyncAll(void);
void  iSyncPartition(int32 partition, int32 nPartition);
void  iSyncVFS(struct vfs *vfsp);
void  iSyncdAll(void);
void  iSyncdVFS(struct vfs *vfsp);
void  iQuiesce(struct vfs *vfsp, boolean_t *tmpfilefound);
void  iQuiesceAll(int fullstop);
int32  iQuiesceVFS(struct vfs *vfsp);
void iLogSync(struct inode *iplog);
void iResume(struct vfs *vfsp);
void iWriteLogToDiskAll(void);
int32 iWriteLogToDisk(inode_t *ipmnt, int32 tid);
reg_t iUnmount (struct vfs *vfsp, int32 forced);
int32 quiesceFSReportTmp(struct vfs *vfsp, uint32 quiesce,
			 boolean_t *tmpfilefound);
int32 quiesceFS(struct vfs *vfsp, uint32 quiesce);
int32 freezeFS(struct vfs *vfsp, int32 timeout);
int32 refreezeFS(struct vfs *vfsp, int32 timeout);
int32 thawFS(struct vfs *vfsp);
int iReconfigMemory(void);
reg_t iMemSize(void);
reg_t iCreateSpecial(inode_t *ipmnt, dev_t devno, ino64_t fsno, ino64_t ino,
		inode_t **ipp, mode_t mode, struct ucred *crp);

#endif	/* _KERNEL */

#endif /* _H_J2_INODE */
