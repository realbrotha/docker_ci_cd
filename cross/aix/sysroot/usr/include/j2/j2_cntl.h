/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/j2/include/j2_cntl.h 1.20                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)81     1.20  src/bos/kernel/j2/include/j2_cntl.h, sysj2, bos53H, h2005_41A5 10/4/05 14:56:28 */

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

#ifndef _H_J2_CNTL
#define _H_J2_CNTL

#include <j2/j2_dinode.h>	/* for j2time_t */

/* Commands marked with J2_RESTRICTED are meant to be used by J2
 * commands *only* and are unpublished interfaces. The compile will
 * fail for anyone attempting to use one of these commands,
 * J2_RESTRICTED will only be defined if _J2_INTERNAL is defined.
 */

#ifdef _I_AM_FSHELP
/* All helpers are considered internal. */
#define _J2_INTERNAL
#endif

#ifdef _J2_INTERNAL
/* For internal use only */
#define J2_RESTRICTED		0
#endif

/*
 * Commands.
 *
 * Commands should not be defined above the J2_FSCNTL_MASK.  The mask
 * is meant to specify the command portion. Higher bits can be used
 * for flags to the commands.
 */
#define J2_FSCNTL_MASK		0xFFFF

#define FSCNTL_UNUSED		0x0000 		/* Unavailable, keep empty */
#define FSCNTL_FREEZE		0x0001 		/* see fscntl man page */
#define FSCNTL_REFREEZE		0x0002 		/* see fscntl man page */
#define FSCNTL_THAW		0x0003 		/* see fscntl man page */
#define FSCNTL_RESERVED1	0x0004 		/* Available for use */
#define FSCNTL_EXTENDFS         0x0005|J2_RESTRICTED
#define FSCNTL_DEFRAGFS         0x0006|J2_RESTRICTED
#define FSCNTL_QSFS             0x0007
#define FSCNTL_RESERVED2	0x0008		/* Available for use */
#define FSCNTL_RESERVED3	0x0009		/* Available for use */
#define	FSCNTL_SNAPQUERY	0x000A
#define	FSCNTL_SNAPCOUNT	0x000B
#define	FSCNTL_SNAPDELETE	0x000C
#define	FSCNTL_SNAPCREATE	0x000D
#define FSCNTL_SNAPEXTEND	0x000E
#define FSCNTL_EXTENTINFO	0x000F
#define FSCNTL_J2CONV		0x0010|J2_RESTRICTED
#define FSCNTL_SHRINKFS  	0x0011|J2_RESTRICTED


/* -----------------------------------------------------------------------------
 * Subtypes:
 *	The following are subtypes for the FSCNTL_EXTENTINFO command.
 */
#define	FSCNTL_SNAPINFO	0x1	/* Returns the number of physical extents in a
				 * snapshot storage object
				 */
#define	FSCNTL_SNAPEXTS	0x2	/* For each backed extent in the snapshot
				 * storage object, returns mapping of physical
				 * extents in snappedFS file system to physical
				 * extents in snapshot.  The extent descriptors
				 * will be sorted in order of offset of file
				 * system block numbers.
				 *
				 * Note if querying a current snapshot, new
				 * snapshot extents may be added while requests
				 * are serviced.  Therefore, this may not return
				 * all extents if snappedFS is modified while
				 * this query occurs.
				 */
#define	FSCNTL_USDEXTS	0x3	/* Returns the used physical extents in the file
				 * system.
				 */

/* Snapshot storage object type flags */
#define	SNAPFILE	0x1	/* Snapshot stored in a JFS2 file. */
#define	SNAPDEV		0x2	/* Snapshot stored in a logical volume. */
#define SNAPPEDFS       0x3     /* When querying a snapshot for its information
				 * the snapquery_t will be filled in with the
				 * information about the snapshot, except the
				 * snapshot_loc snapshot_dev field will be
				 * filled in with the device for the snappedFS.
				 * This flag will be used to indicate this
				 */
#define	J2FS		0x4	/* JFS2 file system device */

typedef struct {
	int32	flags;		/* 4: Indicates further information about what
				 *    is being asked for.  Flag could be one of
				 *    the following:
				 *	SNAPDEV: Device specified
				 *	SNAPFILE: File pathname specified
				 *	J2FS: JFS2 file system device specified.
				 *		All other fields are unused, but
				 *		should be cleared.
				 */
	int32	padding;	/* 4: Padding */
	union {
		dev_t	snapshot_dev;	/* Device of snapshot */
#ifdef _KERNEL
		struct {
			int __snapdev32;	/* 32/64 translation */
			int :32;
		};
#endif
		ino64_t	parent_ino;	/* Inode number of parent */
	} _loc;	/* 8: */
	int16	length;		/* 2: Number of bytes in the name */
	char	name[PATH_MAX];	/*    Will be the length specified:
				 *	SNAPFILE: component name
				 *	SNAPDEV: Object full pathname
				 *	J2FS: Not used
				 */
} snapshot_t;

#define snapshot_dev	_loc.snapshot_dev
#define __snapdev32	_loc.__snapdev32
#define parent_ino	_loc.parent_ino

typedef struct {
	j2time_t	snapshot_tm;	/* 16: Timestamp of snapshot */
	int32		snapshot_count;	/* 4: Count of number of snapshots */ 
	uint32		snapshot_state;	/* 4: State of snapshot.
					 *    See j2_snapshot.h
					 */
	int64		size;		/* 8: Current amount of snapshot used */
	int64		maxSize;	/* 8: Maximum size of snapshot */
	int32		l2bsize;	/* 4: l2 block size */
	snapshot_t	snapshot_loc;	/* See structure above. */
} snapquery_t;


#ifndef	_J2_UTILITY
/*
 *	prototypes for per file system global services
 */
int32 syncFS(struct vfs *vfsp, uint32 quiesce);
void resumeFS(struct vfs *vfsp);
#endif	/* _J2_UTILITY */

/* j2 specific ioctls */
#define l_IOC_OUT         0x40000000      /* copy out parameters */
#define l_IOC_IN          (0x40000000<<1) /* copy in parameters */
#define l_IOCPARM_MASK    0x7f            /* parameters must be < 128 bytes */
#define l_IOW(x,y,t)     (l_IOC_IN|((sizeof(t)&l_IOCPARM_MASK)<<16)|(x<<8)|y)
#define l_IOR(x,y,t)     (l_IOC_OUT|((sizeof(t)&l_IOCPARM_MASK)<<16)|(x<<8)|y)

#define J2_METAMAP      l_IOW('f', 119, int)     /* set EA */

/* j2 metamap ioctl specific structs and flags { */
typedef struct extent {
	uint32	status;	  /* ABNR, other relevant flags... */
	uint32	reserved; /* future use and padding */
	uint64	offset;   /* logical offset */
	uint64  length;   /* logical length */
	uint64  blkaddr;  /* physical address */
} extent_t;

/* status flags: */
#define MM_EXT_ABNR    0x1 /* extent is ABNR */

typedef struct metamap {
        uint64   mode;       /* One of the modes below */
        uint64   offset;     /* logical block offset of start */
        uint64   length;     /* logical length in blocks */
#ifdef __64BIT__
        extent_t *buf;       /* buffer for returning extents */
#else
	extent_t *buf;
	uint32   reserved3;
#endif
	uint64   bufsize;
	int32    err;        /* work was done, error encountered */
	int32    reserved1;  /* future use */
	uint64   endsize;
} metamap_t;

/* last 8 bits specify mode, the top specify "arguments" (masks) */
#define MM_QUERY       0x00
#define MM_ALLOC       0x01
#define MM_RECORD      0x02
#define MM_SETPROP     0x03
#define MM_GETPROP     0x04
#define MM_MODEMASK    0xFF

/* masks for MM_QUERY: NONE */

/* masks for MM_ALLOC, MM_RECORD: MM_NONBLOCK and */
#define MM_UN          0x0100  /* reverse the request */
#define MM_FORCE       0x0200  /* force through */
#define MM_ENDSIZE     0x0400  /* force end size down */

/* masks for MM_GET/SETPROP: MM_UN, MM_NONBLOCK and: */
#define MM_ALIGNMENT   0x0800 /* units communicated in */

/* } (j2 metamap ioctl specifics) */

/* extentInfo_t: Used for FSCNTL_EXTENTINFO command. */
typedef struct {
	uint32		cmdType;	/* Input: Specifies one of the subtypes
					 * of the FSCNTL_EXTENTINFO command.
					 * Indicates type of extent information
					 * being queried.
					 */
	/* numExtents: Differs depending on cmdType:
	 *	FSCNTL_SNAPINFO: Output - filled in by fscntl() call with number
	 *			 of extents stored by snapshot storage object
	 *	FSCNTL_SNAPEXTS: Input - passed in by caller to indicate number
	 *			 of extent_t structures are here to fill in
	 *	FSCNTL_USDEXTS: Input - same as FSCNTL_SNAPEXTS
	 */
	int32		numExtents;

	snapshot_t	storageObj;	/* Input: Specifies storage object to
					 * query
					 */
	union {
		extent_t	*extBuffer;
					/* Caller needs to allocate space for
					 * the header part of this structure and
					 * enough extent_t structures to be
					 * filled in as numExtents indicates.
					 *
					 * On call, if first extent_t structure
					 * has non-zero offset, then it
					 * indicates the offset to start from.
					 *
					 * On return, if length of extent_t
					 * structure has 0 value, then it
					 * indicates there are no more extents
					 * to return.
					 */
		int32		l2LVBlockSize;
					/* FSCNTL_SNAPINFO: Output */
	};
} extentInfo_t;


/* j2conv_t: Used for FSCNTL_J2CONV command.
 *	Caller must set all unused parts of structure to 0.
 */
#define CONVMASK	0xE000	/* Mask for version part of flag field */
#define	CONVDISABLE	0x0001	/* Disable the feature */
typedef struct {
	uint32	j2c_version;	/* 4: New version number for the fs */
	uint32	j2c_type;	/* 4: Specifies type of feature to enable.
				 *    One of:
				 *	J2COMPAT:	s_feature_compat
				 *	J2RDONLY:	s_feature_rdonly
				 *	J2INCOMPAT:	s_feature_incompat
				 */
	uint64	j2c_feature;	/* 8: Bitmask of feature to enable in the fs */
	uint32	j2c_flag;	/* 4: CONVDISABLE, enabled if this not set */
	uint32:32;		/* 4: padding */
} j2conv_t;

#ifdef	_KERNEL

int j2_metaMap(
	struct vnode     *vp,
	long             flags,
	metamap_t        *mm,
	struct ucred     *crp);

#endif /* _KERNEL */

#endif /* _H_J2_CNTL */
