/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/j2/include/j2_filsys.h 1.26.1.1                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)89     1.26.1.1  src/bos/kernel/j2/include/j2_filsys.h, sysj2, bos53L, l2007_13C0 2/8/07 11:12:55 */
/*
 * COMPONENT_NAME: (SYSJ2) JFS2 Physical File System
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 */

#ifndef _H_J2_FILSYS
#define _H_J2_FILSYS

#include <j2/j2_types.h>


/* Minimum number of bytes required  for a J2 file system */
#define MINJ2		0x1000000

/*
 *	pager cache configuration
 */
/* data page, ref. of PSIZE:  kernel/vmm/vmdefs.h */

#ifndef PSIZE
#define	PSIZE		4096		/* page size (in byte) */
#define	L2PSIZE		12			/* log2(PSIZE) */
#define	POFFSET		4095		/* offset within page */
#endif

/* meta data page */
#define jBPSIZE		4096		/* buffer page size (in byte) */	
#define BPSIZE		jBPSIZE
#define	L2jBPSIZE	12			/* log2(jBPSIZE) */
#define L2BPSIZE	L2jBPSIZE
#define	BPOFFSET	4095		/* offset within buffer page */

/*
 *	fs fundamental size
 *
 * PSIZE >= file system block size >= DBSIZE >= DISIZE
 */
/* physical block size, ref. of DBSIZE:  kernel/sys/dasd.h */
#ifndef DBSIZE
#define	DBSIZE		512		/* physical block size (in byte) */
#define	L2DBSIZE	9		/* log2(PBSIZE) */
#endif

#define MIN_FS_BLKSIZE		DBSIZE
#define MAX_FS_BLKSIZE		PSIZE

   /* the MAX_FILESIZE is calculated in the following way:
    *  xd_t has 40 bit for fsblk address. the max fsblk
    *  size is (1<<12), so the MAX file size is (1<<52)
    *
    * This VMM has its own limit on the size of a client file, which is
    * 2^44 - PSIZE. For consistency, the VMM limit is used here as well.
    */
#ifdef __64BIT_KERNEL
#define	MAX_FILESIZE			(0xFFFFFFFF000LL)
#else
#define	MAX_FILESIZE			(0xFFFFFFF000LL)
#endif
#define	MAX_DATAPAGE_NUM		((MAX_FILESIZE >> L2PSIZE) - 1)

#define jDISIZE		512		/* on-disk inode size (in byte) */
#define L2jDISIZE	9		/* log2(DISIZE) */

#define IDATASIZE	256		/* inode inline data size */
#define	IEASIZE		128		/* inode inline extended attribute size */

#define MAX_LOG_SIZE            ((2 << 30) - (1 << 20))
#define MAX_LOG_SIZE_MEG        (MAX_LOG_SIZE >> 20)

/*	directory configuration */
#define J2_NAME_MAX	255
#define J2_PATH_MAX	jBPSIZE

/*
 * SUPERBLK_SIZE defines the total amount of space reserved on disk for the
 * superblock.  This is not the same as the superblock structure, since all of
 * this space is not currently being used.
 */
#define SUPERBLK_SIZE	jBPSIZE

/*
 * IAG_SIZE and INODE_MAP_PAGE_SIZE defines the amount of disk space 
 * reserved for each page of the inode allocation map (to hold an iag)
 */
#define IAG_SIZE        	4096
#define INODE_MAP_PAGE_SIZE	IAG_SIZE
#define IAG_EXTENT_SIZE 	IAG_SIZE

#define	INOSPERIAG	4096		/* number of disk inodes per iag */
#define	L2INOSPERIAG	12		/* l2 number of disk inodes per iag */
#define INOSPEREXT	32		/* number of disk inode per extent */
#define L2INOSPEREXT	5		/* l2 number of disk inode per extent */
#define	INODE_EXTENT_SIZE (jDISIZE * INOSPEREXT)	/* inode extent size */
#define	INOSPERPAGE	8		/* number of disk inodes per jBPSIZE */
#define	L2INOSPERPAGE	3		/* log2(INOSPERPAGE) */

/* #define	IAGFREELIST_LWM	64 	What is this ? */

/*
 * fixed byte offset address
 */
#define IPL_B           0

 /* 32k reserved bytes at the front of an aggregate. It is not used by
  * JFS2. AIX LVM uses the first block.  */
#define AGGR_RSVD_BYTES		0x8000

   /* primary superblock directly follows the reserved blocks  */
#define SUPER1_OFF		AGGR_RSVD_BYTES

   /* Control page of aggregate inode allocation map,
    *  followed by 1st extent of map */
#define AIMAP_OFF	(SUPER1_OFF + SUPERBLK_SIZE)

   /*  1st extent of aggregate inode table. 
    *  Ahead of it are the control page of the aggre. inode alloc. map 
    *  and  the 1st extent of map
    */
#define AITBL_OFF	(AIMAP_OFF + (IAG_SIZE << 1))

/*
 * The following defines the byte offset for the first inode extent in
 * the aggregate inode table.  This allows us to find the self inode to find the
 * rest of the table. 
 */
#define AGGR_INODE_TABLE_START	AITBL_OFF

	/*  secondary superblock */
#define SUPER2_OFF	(AITBL_OFF + INODE_EXTENT_SIZE)

	/*  block allocation map */
#define BMAP_OFF	(SUPER2_OFF + SUPERBLK_SIZE)


/*
 *	fixed reserved inode number
 */
/* aggregate inodes in the 1st extent of aggre. inode table  */
#define AGGR_RESERVED_I	0		/* aggregate inode (reserved) */
#define	AGGREGATE_I	1		/* aggregate inode map inode */
#define	BMAP_I		2		/* aggregate block allocation map inode */
#define	LOG_I		3		/* aggregate inline log inode */
#define BADBLOCK_I	4		/* aggregate bad block inode */
#define	ZOMBIE_I	5		/* aggregate zombie inode */
#define	FILESYSTEM_I	16		/* 1st/only fileset inode in ait:
					 * fileset inode map inode
					 */
/* aggregate inodes in the 2nd extent of aggre. inode table,
 * which are duplicate of the 1st extent 
 */
#define AGGR_RESERVED_I2	AGGR_RESERVED_I + INOSPEREXT
#define	AGGREGATE_I2		AGGREGATE_I + INOSPEREXT
#define	BMAP_I2			BMAP_I + INOSPEREXT
#define	LOG_I2			LOG_I + INOSPEREXT
#define BADBLOCK_I2		BADBLOCK_I + INOSPEREXT
#define	ZOMBIE_I2		(ZOMBIE_I + INOSPEREXT)
#define	FILESYSTEM_I2		FILESYSTEM_I + INOSPEREXT	


/* per fileset inode */
#define FILESET_RSVD_I	0		/* fileset inode (reserved) */
#define FILESET_EXT_I	1		/* fileset inode extension */
#define	ROOT_I		((ino64_t)2)	/* fileset root inode     */

#define FILESET_OBJECT_I 3  /* the first fileset inode available for a file
                             * or directory or link...
                             */
#define FIRST_FILESET_INO 16 /* the first aggregate inode which describes
                             * an inode.  (To fsck this is also the first
                             * inode in part 2 of the agg inode table.)
                             */

/*
 *	file system type (platform dependent)
 */
#define	MNT_JFS2	0

/*
 *	 file system option (superblock s_flag)
 *	 (attempt to keep these in more or less descending order so
 *	  we can tell what's been used or not...)
 */
/* platform option (conditional compilation) */
#define J2_AIX		0x80000000	/* AIX support */
/*	POSIX name/directory  support */

#define J2_OS2		0x40000000	/* OS/2 support */
/*	case-insensitive name/directory support */

#define J2_DFS		0x20000000	/* DCE DFS LFS support */
#define	J2_SNAPSHOT	0x10000000	/* snapshot bound */
#define	MAXNUMSNAPSHOT	15
#define	SNAPSHOT_I	FILESYSTEM_I + 1

/* Quota Management ENABLED for specific quota types */
#define J2_USERQUOTA	0x08000000
#define J2_GROUPQUOTA	0x04000000

#define J2_OBSOLETE	0x00020000	/* Was J2_SPARSE, no longer used */

/* ? Secondary aggregate inode table */
#define J2_BAD_SAIT	0x00010000	/* current secondary ait is bad */

/*
 * log logical volume option
 */
#define	J2_INLINELOG	0x00000800	/* inline log within file system */

/* commit option */
#define	J2_COMMIT	0x00000300	/* commit option mask */
#define	J2_GROUPCOMMIT	0x00000100	/* group (of 1) commit */
#define	J2_LAZYCOMMIT	0x00000200	/* lazy commit */
#define	J2_TMPFS	0x00000400	/* temporary file system - 
					 * do not log/commit:
					 */
/* directory option */
#define J2_UNICODE	0x00000001	/* unicode name */


/*
 *	file system state (superblock s_state)
 *
 * unmount: reset (FM_LOGERROR | FM_LOGNOREDO) unless FM_FSERROR;
 *
 * recovery/repair: logRedo() unless FM_NOLOGREDO, and then fsck()
 * if (FM_FSERROR || FM_LOGERROR || FM_LOGREDOERROR)
 *	
 */
#define FM_RESET 0x80000000	/* parameter directive to reset state */

/* offLine - file system is unmounted and clean */
#define FM_CLEAN 0x00000000

/* onLine - file system is mounted cleanly;
 * offLine - file system crashed: logRedo()/fsck() required;
 */
#define FM_MOUNT 0x00000001

/* onLine/offLine - file system meta-data exception detected
 * (i/o error or consistency violation):
 * logRedo()+fsck() required (persist at unmount();
 */
#define FM_DIRTY 0x00000002
#define FM_FSERROR FM_DIRTY

/* offLine - logRedo() failed: fsck() required; */
#define	FM_LOGREDO 0x00000004
#define	FM_LOGREDOERROR FM_LOGREDO

/* onLine/offLine - file system resize in progress:
 * special handling by logRedo() required
 */
#define	FM_EXTENDFS 0x00000008	/* extendfs() in progress */
#define	FM_MOVEINLINELOG 0x00000010	/* inLineLog is moving */
#define	FM_SHRINKFS 0x00000020	/* shrinkfs() in progress */
#define	FM_RESIZEFS (FM_EXTENDFS | FM_SHRINKFS)

/* onLine/offLine - spot log i/o error: logRedo()+fsck() required
 * (reset at unmount());
 */ 
#define	FM_LOGERROR	0x00000040

/* onLine/offLine - persistent log i/o error: skip logRedo()
 * but fsck() required (reset at unmount() if !(FM_FSERROR|FM_LOGERROR);
 */ 
#define	FM_LOGNOREDO	0x00000080	/* log offLine - fsck */

/* onLine - filesystem is quiesced, frozen and contains temp objects
 * offLine - logRedo() should rebuild the maps but not replay
 * 		any log records.
 * Note: a quiesced, frozen fs w/o temp objects has a state of FM_CLEANQUIESCED
 *	 and does not need logredo to rebuild maps
 * This flag is never set in the ipmnt
 */
#define FM_QUIESCED		0x00002000
#define FM_CLEANQUIESCED	0x00001000

/* 
 * These flags get set in ipmnt and NOT in the superblock.
 */
#define FM_INTFROZEN	0x00000100	/* internal frozen (chfs/shrinkfs) */
#define FM_EXTFROZEN	0x00000200	/* external frozen (freeze/thaw) */
#define FM_UNMOUNTING	0x00000400	/* file system is unmounting */

/*
 * helper macro
 */
/* file system block size */
#define LBSIZE(ipmnt)		((ipmnt)->i_bsize)
/* log2(file system block size) */
#define L2LBSIZE(ipmnt)		((ipmnt)->i_l2bsize)
#define LBOFFSET(ipmnt, x)	((x) & ((ipmnt)->i_bsize - 1))
#define LBNUMBER(ipmnt, x)	((x) >> (ipmnt)->i_l2bsize)
#define	LBLK2PBLK(ipmnt, b)	((b) << (ipmnt)->i_l2bfactor)
#define	PBLK2LBLK(ipmnt, b)	((b) >> (ipmnt)->i_l2bfactor)
/* size in byte -> last page number */
#define	SIZE2PN(size) ( ((int64)((size) - 1)) >> (L2PSIZE) )
/* size in byte -> last file system block number */
#define	SIZE2BN(size, l2bsize) ( ((int64)((size) - 1)) >> (l2bsize) )

/* True if name is "." or ".."
 */
#define ISDOTS(name)    ((name)[0] == '.' && (((name)[1] == '\0') || \
                        ((name)[1] == '.' && (name)[2] == '\0')))


/*
 *	file system operations
 */
/* vfs operations */
#define J2_CNTL		0x00000101
#define J2_MOUNT	0x00000102
#define J2_ROOT		0x00000103
#define J2_SETLABEL	0x00000106	/* XXX only */
#define J2_STATFS	0x00000104
#define J2_SYNC		0x00000105
#define J2_SYSINFO	0x00000106	/* XXX only */
#define J2_UNMOUNT	0x00000107
#define J2_VGET		0x00000108

/* vnode operations */
#define J2_ACCESS	0x00000001
#define J2_CLOSE	0x00000002
#define	J2_CREATE	0x00000003
#define	J2_FID		0x00000004
#define	J2_FINDDIR	0x00000005	/* XXX only */
#define	J2_FSYNC	0x00000006
#define	J2_FTRUNC	0x00000007
#define J2_GETACL	0x00000008
#define J2_GETATTR	0x00000009
#define J2_GETEXTATTR	0x0000000a	/* XXX only */
#define J2_GROW		0x0000000b
#define J2_HOLD		0x0000000c
#define J2_LINK		0x0000000d
#define J2_LOCKCTL	0x0000000e
#define	J2_LOOKUP	0x0000000f
#define J2_MKDIR	0x00000010
#define J2_OPEN		0x00000020
#define	J2_RDWR		0x00000030
#define	J2_READDIR	0x00000040
#define	J2_READLINK	0x00000050
#define J2_RELE		0x00000060
#define	J2_REMOVE	0x00000070
#define	J2_RENAME	0x00000080
#define	J2_RMDIR	0x00000090
#define	J2_SETACL	0x000000a0
#define	J2_SETATTR	0x000000b0
#define J2_SETEXTATTR	0x000000c0	/* XXX only */
#define	J2_SYMLINK	0x000000d0


#ifdef _KERNEL
/*
 *	configuration state
 */
#define J2_UNCONFIGURED		0
#define J2_INITIALIZING		1
#define J2_TERMINATING		2
#define J2_CONFIGURED		3

/*
 * run time system configuration parameters
 */
/* journaled client file system (jCFS) */

        /* In The following the start addresses of
         * the various  memory ranges allocated during the course
         * of j2_init() are captured; serves as a focal point to get to
         * the different address spaces  that need to de-allocated
         * in case j2_init() fails because of ENOMEM
         */

struct jCFS {
	int32	maxCPU;	/* max # CPUs of system */
	int32	nCPU;	/* # CPUs of system */
	int32	nCPUPerPartition;	/* # CPUs per partition */
	int32	cacheLineSize;	/* L1 data cache line size - 1 */
	int32	memorySize;	/* system memory size in Mbyte */
	int32	realMemorySize; /* real memory size (no maxing or reducing) */
	int32	nCacheClass;	/* # of cache class */
	int32 	nBufferPerCacheClass;   /* # of buffer per cache class */
	int32	rICacheSize;	/* inodes/memory * 1000 */
	int32	rJCacheSize;	/* pgbufs/memory * 1000 */
	int32 	nPagePerFileObject; /* # pages per file obj */
	int32	nFileObject;	/* # of file objects */
	int32	reserved1;
	int32	reserved2;
	int32	reserved3; 
	int32	reserved4;
	int32	reserved5;
	int32   reserved6;
	int32   reserved7;
        caddr_t	ccp;
        caddr_t	hcp;
        caddr_t	cacheTable;
        caddr_t	hashTable;
        caddr_t	hdr;
        caddr_t	bufhdr;
        caddr_t	bccp;
        caddr_t	bhcp;
        caddr_t	pccp;
        caddr_t	diobp;
        caddr_t	TxBlock;
        caddr_t	txLockPile;
	caddr_t perProcessorData;
};
extern struct jCFS	jCFS;

extern int32	j2Mount;	/* mount occurrence major */
#endif /* _KERNEL */

#endif /* _H_J2_FILSYS */
