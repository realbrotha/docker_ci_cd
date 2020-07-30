/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53N src/bos/kernel/j2/include/j2_snapshot.h 1.14.1.1                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2002,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)76	1.14.1.1  src/bos/kernel/j2/include/j2_snapshot.h, sysj2, bos53N, n2007_31B8 7/3/07 12:47:28 */
#ifndef	_H_J2_SNAPSHOT
#define _H_J2_SNAPSHOT	
/*
 *	j2_snapshot.h
 */

#include <j2/j2_filsys.h>

#define	_J2_SNAPSHOT	1

/*
 *	snapshot superblock
 * (at fixed offset of 4 Kbyte in snapshotStorage)
 */
#define J2SNAPSHOT	"J2SS" 	/* magic */
#define J2SNAPSHOTVERSION	1	/* version 1 */
#define SNAPSHOT_NONPERSISTENT	J2SNAPSHOTVERSION
#define	SNAPSHOT_PERSISTENT	2	/* version 2: Persistent snapshots */


typedef struct snapSuperblock {
	/* self descriptor */
	char	snapshotMagic[4];	/* 4: J2SS */
	int32	rsrvd1;	/* 4: */
	int32	snapshotVersion;	/* 4: */
	int32	snapshotGeneration;	/* 4: snapshotSeries generation number */
	uint32	snapshotAttribute;	/* 4: */
	uint32	snapshotState;	/* 4: */
	dev64_t	snapshotDevice;	/* 8: */
	ino64_t	snapshotInumber;	/* 8: */
	uint32	snapshotIgeneration;	/* 4: */
	uint32	snapshotType;	/* 4: */
	j2time_t	snapshotTimestamp;	/* 16: creation time */
	int64	snapshotStorageSize;	/* 8: current storageObject size in fsBlock */
	int64	maxSnapshotStorage;	/* 8: max/limit storageObject size in fsBlock */

	/* base file system descriptor; */
	dev64_t	fileSystemDevice;	/* 8: */
	ino64_t	fileSystemInumber;	/* 8: */
	uint32	fileSystemIgeneration;	/* 4: */
	int32	fileSystemL2BlockSize;	/* 4: */
	int64	fileSystemSize;		/* 8: */

	/* bMapMap descriptor */
	int64	bMapMap;	/* 8: bMapMap start address */

	/* ssTable descriptor; */
	int64	ssTable;		/* 8: ssTable start address */
	int32	ssTableSize;	/* 4: */
	int32	sTableGroupSize;/* 4: */

	/* sTable descriptor; */

	/* sSegment descriptor; */
	int64	segmentListHead;	/* 8: segment list head address */
	int64	segmentListTail;	/* 8: segment list tail address */
	int32	segmentSize;	/* 4: */
	int32	trackSize;		/* 4: */
	int64	nBID;			/* 8: number of beforeImage extents */
} snapshotSuperblock_t;

#define	SNAPSHOT_SUPERBLOCK_OFFSET	BPSIZE
#define	SNAPSHOT_ITABLE_OFFSET	SNAPSHOT_SUPERBLOCK_OFFSET + BPSIZE

/* snapshot attribute */
#define	SS_SSLV		0x00000001
#define	SS_SSVDF	0x00000002

/* snapshot state */
#define	SNAPSHOT_DIP	0x00000001	/* delete-in-progress */
#define	SNAPSHOT_PIP	0x00000002	/* This value has different meanings
					 * dependent on the base file system
					 * superblock s_snapshotVersion field
					 * value:
					 * SNAPSHOT_NONPERSISTENT: indicates an
					 *	invalid snapshot, the only
					 *	action allowed should be to
					 *	delete the snapshot.
					 * SNAPSHOT_PERSISTENT: indicates a
					 *	normal snapshot which is
					 *	recoverable, the snapshot should
					 *	only be deleted on prior
					 *	releases that don't support
					 *	recoverable snapshots
					 */
#define	SNAPSHOT_CUR	0x00000004	/* current snapshot */
#define	SNAPSHOT_AIP	0x00000008
		/* abort-in-progress:
		 *	s_snapshotState has this bit set when current snapshot
		 *		is aborted.  When current snapshot is aborted
		 *		all snapshots are aborted.
		 *	state in sSeries has this bit set for each snapshot
		 *		which is aborted.
		 */
#define	SNAPSHOT_NODEV	0x00000010
		/* No device: If the snapshot device is not available, or the
		 * snapshot superblock doesn't match, then the snapshot is
		 * marked as SNAPSHOT_AIP and SNAPSHOT_NODEV.  This allows
		 * snapshots which follow the unavailable one to still remain
		 * available.
		 */

/* SNAPGENOK: Validate the generation number for a snapshot with the snappedFS
 *      superblock.  The generation number must be in the range of in-use
 *      snapshots owned by the snappedFS and its device must match.
 */
#define SNAPGENOK(SNAPSB, FSSB, RC) \
	{\
		int32   first, last, sGen;\
		first = (FSSB).s_snapshotSeries.first;\
		last = (FSSB).s_snapshotSeries.last;\
		sGen = (SNAPSB).snapshotGeneration;\
	/* Device should match and generation should be in use */\
		RC = (((FSSB).s_snapshotSeries.generation[sGen].device ==\
			(SNAPSB).snapshotDevice)\
			&& ((first <= last && sGen >= first && sGen <= last)\
				|| (first > last &&\
					(sGen >= first || sGen <= last))));\
	}

/*
 *	snapshotSeries generation summary
 * (defined in base file system superblock)
 */
typedef struct snapshotSummary {
	uint32	attribute;	/* 4: */
	uint32	state;	/* 4: */
	j2time_t	timestamp;	/* 16: */
	dev64_t	device;	/* 8: */
	ino64_t	iNumber;	/* 8: */
	uint32	gNumber;	/* 4: */
	uint32	type;	/* 4: */
	/* transient binding */
	union	{
		uint64	storageObject;
		struct file	*fpDevice;
		struct inode	*ipVDF;
	} snapshotStorageObject;	/* 8: */
	union	{
		uint64	snapshotObject;
		struct inode	*ipSnapshot;
	} snapshotObject;	/* 8: */
} sSummary_t; /* 64: */

/*
 *	snapshot series table
 * (defined in base file system superblock)
 */
typedef struct snapshotSeries {
	int32	nSnapshot;	/* 4: */
	int32	first;	/* 4: */
	int32	last;	/* 4: */
	int32	rsrvd[5];	/* 20: */
	struct snapshotSummary	generation[MAXNUMSNAPSHOT]; /* 64 * 15 */
} sSeries_t;	/* 992 */


#ifdef _KERNEL

#include <j2/j2_lock.h>

/*
 *	snapshotObject 
 * (wrapped as an ipmnt aka ipSnapshot: ref. j2_inode.h)
 * per active snapshot
 */
struct snapshotObject {
	/* bfs binding */
	struct inode	*ipFileSystem;	/* 8: baseFileSystem ipmnt */
	int64	fsSize;	/* 8: baseFileSystem size */
	/* snapshot attributes */
	int32	version;	/* 4: */
	int32	generation;	/* 4: */
	uint32	attribute;	/* 4: */
	uint32	state;	/* 4: */
	dev_t	device;	/* 8: storageObject */
	ino64_t	iNumber;	/* 8: storageObject */
	uint32	gNumber;	/* 4: storageObject */
	uint32	type;	/* 4: storageObject*/
	j2time_t	timestamp;	/* 16: */
	int64	size;	/* 8: current storageObject size in fsBlock */
	int64	maxSize;	/* 8: max/limit storageObject size in fsBlock */
	int64	ssTable;	/* 8: ssTable start address */ 
	int64	segmentListHead;	/* 8: segmentList head address */ 
	int64	segmentListTail;	/* 8: segmentList tail address */ 
	struct snapshotSeries	*series; /* 8: */
	struct vnode	*vpStorageObject;	/* 8: storageObject */
	struct file	*fpDevice;	/* 8: storageObject */
	struct inode	*ipVDF;	/* 8: storageObject */
	struct inode	*ipBMapMap; /* 8: */
	struct snapshotSegmentDescriptor	*wipSegment;	/* 8: */	
	event_t	liWait;	/* 8: event wait for lazy initialization */
	event_t	freeWait;	/* 8: event wait for free segment spece */
	MUTEXLOCK_T	lock;	/* 8: */
	int32	segmentSize;	/* 4: */
	int32	rsrvd;	/* 4: */
	int32	cowip;	/* 4: */
	int32	codip;	/* 4: */
	event_t	copyWait;	/* 8: event wait for cow quiesce */
	char	*cowAG;	/* 8: cow ssd/buffer allocationGroup */
	int64	nBID;	/* 8: nummber of beforeImage extents */
};

#endif /* _KERNEL */


/*
 *	sMap/ssMap (sMap_t)
 *
 * ssMap is statically allocated at snapshot creation time;
 * sMap is allocated/initialized lazily;
 * a single ssMap entry covers 32 sMap pages of 4 Kbyte each
 * (as allocated by a snapshotSegment), 
 * where each sMap page covers 512 blocks of snapshot;
 */
typedef struct {
	unsigned	flag:8;		/* 1: flags */
	unsigned	rsrvd:8;	/* 1: composit level */
	unsigned	generation:8;	/* 1: snapshot generation with copy */
	unsigned	addr1:8;	/* 1: address in unit of fsblksize */
	uint32		addr2;		/* 4: address in unit of fsblksize */
} sxd_t;					/* - 8 - */

typedef sxd_t sMap_t;

/* sMap extent descriptor (sxd) flag */
#define	SXD_INUSE		0x01
#define	SXD_COPIED		0x02
#define	SXD_INHERITED	0x04
#define	SXD_COMPOSITE	0x08
#define	SXD_INITIALIZED	0x10
#define	SXD_LOCKED		0x20

typedef struct {
	unsigned	flag:8;		/* 1: flags */
	unsigned	rsrvd:8;	/* 1: */
	unsigned	generation:8;	/* 1: snapshot generation with copy */
	unsigned	addr1:8;	/* 1: address in unit of fsblksize */
	uint32		addr2;		/* 4: address in unit of fsblksize */
	uint64	summary;	/* 8: */
} ssxd_t;	/* 16 */

typedef ssxd_t ssMap_t;

#define	sgInUseMask		0x8000000000000000LL
#define	sgCopiedMask	0x4000000000000000LL
#define	nBitPerSGPage	2
#define	nSMapPagePerBMapPage	16

/*
 * block address to sMap page/entry
 */
#define	nBlockPerSMapPage	512
#define	maskBlockPerSMapPage	511
#define	nEntryInSMapPage	nBlockPerSMapPage
#define	l2nEntryInSMapPage	9
#define	l2nBlockPerSMapPage	l2nEntryInSMapPage
#define	l2nSMapPagePerSSMapEntry	5
#define	l2nEntryPerSMapGroup	14
#define	l2nBlockPerSMapGroup	l2nEntryPerSMapGroup
#define	l2nBlockPerSSMapEntry	l2nEntryPerSMapGroup
#define	maskBlockPerSSMapEntry	((1 << 14) - 1)
#define	l2nEntryInSSMapPage		8
#define	l2nBlockPerSSMapPage	22
#define	BadmaskEntryPerSSMapPage 511 	/* This should be 255, but for some reason it was
					 * 511 in smCreate. Leaving at that for now for
					 * regression reasons, but will be fixed in later
					 * releases 
					 */

/* blockAddress to ssMapPage address */
#define	Block2SSMapPage(baddr, l2nBlockPerPage) \
	(((baddr) >> l2nBlockPerSSMapPage) << l2nBlockPerPage)

/* blockAddress to index in ssMapPage */
#define	Block2IndexInSSMapPage(baddr) \
	(((baddr) >> l2nBlockPerSSMapEntry) & 255)

/* blockAddress to sMap page in sMap group */
#define	Block2SMapGroupPageOffset(baddr, l2nBlockPerPage) \
	((((baddr) & maskBlockPerSSMapEntry) >> 9) << l2nBlockPerPage)

#define	Block2SMapGroupPage(baddr) \
	(((baddr) & maskBlockPerSSMapEntry) >> 9)

/* blockAddress to index in sMapPage */
#define	Block2IndexInSMapPage(baddr)	((baddr) & 511)


/*
 *	snapshotSegment layout
 */
/* before image descriptor in segment log */
typedef struct {
	unsigned	flag:8;		/* 1: flags */
	unsigned	rsrvd:8;	/* 1: */
	unsigned	len:8;		/* 1: length in unit of fsblksize */
	unsigned	addr1:8;	/* 1: bfs address in unit of fsblksize */
	uint32		addr2;		/* 4: bfs address in unit of fsblksize */
#ifdef __cplusplus
	uint64		crc;		/* 8: */
#else
	uint64		xor;		/* 8: */
#endif
} bid_t;					/* - 16 - */

#define	XDaddress(xd, address64)\
{\
	(xd)->addr1 = (address64) >> 32;\
	(xd)->addr2 = (address64) & 0xffffffff;\
}

#define	addressXD(xd)\
	( ((int64)((xd)->addr1)) << 32 | (xd)->addr2 )

#define	BID_BID	0x80	/* page of bid_t */


/*
 * NAME: GETXOR
 *                                                                    
 * FUNCTION: Compute checksum of specified snapshot segment
 *                                                                    
 * PARAMETERS:
 *	XOR	- Set to checksum
 *	SSD	- Snapshot segment descriptor with extent to get checksum
 *	BCOUNT	- Byte offset into segment of start to compute
 *	FCOUNT	- Number of bytes in this segment
 */
#define	GETXOR(XOR, SSD, BCOUNT, FCOUNT)	{\
			uint64	*XORPTR;\
			int32	IDX;\
			XORPTR = (uint64 *)((SSD)->segment + (BCOUNT));\
			for (IDX = 0, (XOR) = 0;\
					IDX < ((FCOUNT) / sizeof(uint64));\
					IDX++, XORPTR++)\
				(XOR) ^= *XORPTR;\
		}

/* snapshotSegment log: 4 Kbyte */
typedef struct snapshotSegmentLog {
	int64	next;	/* 8: */
	int64	self;	/* 8: */
	int32	nBID;	/* 4: */
	int32	crc;	/* 4: */
	int32	rsrvd[26];	/* 104: */
	bid_t	bidList[248];	/* 3968: 16*248 */
} sSegmentLog_t;

/* snapshot segment layout: 128 Kbyte */
#define	J2SNAPSHOTSEGMENTSIZE	(1 << 17)
typedef struct snapshotSegment {
	sSegmentLog_t	log;	/* 4Kbyte: */
	uint8	segmentData[4096*31];	/* 124KByte: */
} sSegment_t;


#ifdef	_KERNEL

enum pbtype;

/*
 *	prototypes for snapshot manager services.
 */
int32 j2_snapshot(struct vfs *vfsp, int32 cmd, caddr_t arg, size_t argsize,
	struct ucred *crp);
reg_t smCOW(struct buf *bpList, uint32 flag);
reg_t smCOD(struct inode *ipSnapshot, int64 xaddr, int32 xlen, uint32 flag);
reg_t smRead(struct buf *bpList, uint32 flag);
reg_t smRIORead(struct vnode *pvp, struct uio *uiop, struct ucred *crp);
reg_t smPager(struct buf *iobpList, uint32 flag);
reg_t smCreate(struct inode *ipmnt, struct vnode *vpStorage);
reg_t smMount(struct vfs *vfsp, struct vnode *vpStorage,
	struct vnode *vpCovered);
reg_t smUnmount(struct inode *ipmnt, struct vfs *vfspSFS, uint32 flag);
#define	smUnmountPHASE1	0x00000001
#define	smUnmountPHASE2	0x00000002
#define	smUnmountFORCE	0x00000008
reg_t smOpen(struct vnode *vpStorage, struct ucred *crp);
reg_t smClose(struct vnode *vpStorage, struct ucred *crp);
reg_t smReadBMap( struct inode *ipSnapshot, int64 xaddr,
		  struct pagerBuffer **, int64 xoff, enum pbtype buftype );
#endif	/* _KERNEL */

#endif /*_H_J2_SNAPSHOT */	
