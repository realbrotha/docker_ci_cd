/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/j2/include/j2_logmgr.h 1.39.1.4                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1999,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)93     1.39.1.4  src/bos/kernel/j2/include/j2_logmgr.h, sysj2, bos53V, v2008_49B5 10/23/08 14:42:04 */

/* @(#)93	1.35  src/bos/kernel/j2/include/j2_logmgr.h, sysj2, bos53H 10/25/05 14:23:20 */
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

#ifndef	_H_J2_LOGMGR
#define _H_J2_LOGMGR	
/*
 * FUNCTION: log manager
 */

#include <j2/j2_types.h>
#include <j2/j2_filsys.h>


/*
 *	log manager configuration parameters
 */
/*
 * log logical volumes start with this standard prefix.
 * this will be determined from an ODM query as will the log type 
 */
#define	LOGNAME_PREFIX	"log"
#define	LOGTYPE		"j2"

#define	MAXNLOG		256	/* max number of logs */
#define	LOGMINOR	8	/* reserved minor dev_t for log */

/* log page size */
#define	LOGPSIZE	4096	
#define	L2LOGPSIZE	12

#define L2MEGABYTE      20
#define KB_256			( 1 << 18 )
#define KB_512			( 1 << 19 )
#define MEGABYTE     ( 1 << L2MEGABYTE)
#define MEGABYTE2		( 1 << 21 )
#define MEGABYTE8		( 1 << 23 )
#define MEGABYTE32     (1 << 25 )
#define MEGABYTE64     (1 << 26)
#define MEGABYTE128     (1 << 27)
#define MEGABYTE512		( 1 << 29 )
#define GEGABYTE		( 1 << 30 )
#define GEGABYTE2	((int64)1 << 31 )
#define GEGABYTE128	((int64)1 << 37 )
#define GEGABYTE512	((int64)1 << 39 )
#define TERABYTE		((int64)1 << 40 )


#define GETLOGSIZE(number_of_bytes, LogSize) \
{\
	if ( number_of_bytes  < MEGABYTE32 )\
		LogSize = KB_256;\
	else if ( number_of_bytes >= MEGABYTE32 &&\
		number_of_bytes < MEGABYTE64 )\
		LogSize = KB_512;\
	else if ( number_of_bytes >= MEGABYTE64 &&\
		number_of_bytes < MEGABYTE128 )\
		LogSize =  MEGABYTE;\
	else if ( number_of_bytes == MEGABYTE128 )\
		LogSize = MEGABYTE2;\
	else if ( number_of_bytes > MEGABYTE128 && \
		number_of_bytes <= GEGABYTE )\
	{\
		LogSize = number_of_bytes >> 7;\
		LogSize = (LogSize + MEGABYTE - 1) & ~(MEGABYTE - 1);\
	}\
	else if ( number_of_bytes > GEGABYTE && \
		number_of_bytes <= GEGABYTE2 )\
		LogSize = MEGABYTE8;\
	else if ( number_of_bytes > GEGABYTE2 &&\
		number_of_bytes <= GEGABYTE128 )\
	{\
		LogSize = number_of_bytes >> 8;\
		LogSize = (LogSize + MEGABYTE - 1) & ~(MEGABYTE - 1);\
	}\
	else if ( number_of_bytes > GEGABYTE128 &&\
		number_of_bytes <= GEGABYTE512 )\
		LogSize = MEGABYTE512;\
	else if ( number_of_bytes > GEGABYTE512 )\
	{\
		LogSize = number_of_bytes >> 10;\
		LogSize = (LogSize + MEGABYTE - 1) & ~(MEGABYTE - 1);\
	}\
}


/*
 *	lbuf buffer cache (lCache) control
 */
/* log buffer manager pageout control (cumulative, inclusive) */
#define	LB_READ		0x1000
#define	LB_WRITE	0x2000	/* enqueue at tail of write queue;
				 * init pageout if at head of queue;
				 */
#define	LB_RELEASE	0x4000	/* remove from write queue
				 * at completion of full-page pageout;
				 * do not free/recycle it yet:
				 * caller will free it;
				 */
#define LB_FREE		0x8000	/* return to freeList
				 * at completion of pageout;
				 * the buffer may be recycled;
				 */
#define	LB_GC	0x0100
#define	LB_EOP	0x0200

#define	LB_PAGEIN		0x0001
#define	LB_PAGEOUT		0x0002
#define	LB_IODONE		0x0004
#define	LB_IOERROR		0x0008


/*
 *	log logical volume
 *
 * a log is used to make the commit operation on journalled 
 * files within the same logical volume group atomic.
 * a log is implemented with a logical volume.
 * there is one log per logical volume group. 
 *
 * block 0 of the log logical volume is not used (ipl etc).
 * block 1 contains a log "superblock" and is used by logFormat(),
 * lmLogInit(), lmLogShutdown(), and logRedo() to record status 
 * of the log but is not otherwise used during normal processing. 
 * blocks 2 - (N-1) are used to contain log records.
 *
 * when a volume group is varied-on-line, logRedo() must have 
 * been executed before the file systems (logical volumes) in 
 * the volume group can be mounted.
 */
/*
 *	log superblock (block 1 of logical volume)
 */
#define	LOGSUPER_B	1
#define	LOGSTART_B	2

#define	LOGMAGIC	"J2XL"	/* external log identifier */
#define	LOGVERSION	1

/*
 * log superblock has space to adress devices with minor numbers
 * < 4K.  An arbitrary number of 3K being chosen as the limit  
 * and leaving * some rsrvd space for any future use.
 * crfs and mount will enforce this limit and advise users 
 * to use INLINE logs for the devices with > 3K minor number.
 *
 */
#define MAXFSMINOR      3072 /* 3K filesystems per log */


typedef struct {
	char	magic[4];	/* 4: log lv identifier */
	int32	version;	/* 4: version number */
	int32	serial;		/* 4: log open/mount counter */
	int32	size;		/* 4: size in number of LOGPSIZE blocks */

	uint32	flag;		/* 4: option */ 
	uint32	state;		/* 4: state - see below */

	int32	end;		/* 4: address of last log record set by logredo() */
	uint32	active[96];	/* 32: active file systems bit vector */
	int32	rsrvd[25];
} logsuper_t;				

/* log flag: commit option (see j2_filsys.h) */

/* 
 * Persistent Log States
 */
/* log mounted by lmLogInit() */
#define	LOGMOUNT	0x00000000
/* log shutdown by lmLogShutdown(). log redo completed by logRedo() */
#define LOGREDONE	0x00000001
/* log wrapped */
#define LOGWRAP		0x00000002
/* log i/o error detected */
#define LOGIOERROR	0x00000004
/* log is stale: do not play log at recovery: */
#define	LOGNOREDO	0x00000010

/* 
 * Transient Log States
 */
/* synchronize log shutdown with log sync */
#define LOGSHUTDOWN	0x80000000

/*
 *	log logical page
 *
 * (this comment should be rewritten !)
 * the header and trailer structures (h,t) will normally have 
 * the same page and eor value.
 * An exception to this occurs when a complete page write is not 
 * accomplished on a power failure. Since the hardware may "split write"
 * sectors in the page, any out of order sequence may occur during powerfail 
 * and needs to be recognized during log replay.  The xor value is
 * an "exclusive or" of all log words in the page up to eor.  This
 * 32 bit eor is stored with the top 16 bits in the header and the
 * bottom 16 bits in the trailer.  logredo can easily recognize pages
 * that were not completed by reconstructing this eor and checking 
 * the log page.
 *
 * Previous versions of the operating system did not allow split 
 * writes and detected partially written records in logredo by 
 * ordering the updates to the header, trailer, and the move of data 
 * into the logdata area.  The order: (1) data is moved (2) header 
 * is updated (3) trailer is updated.  In logredo, when the header 
 * differed from the trailer, the header and trailer were reconciled 
 * as follows: if h.page != t.page they were set to the smaller of 
 * the two and h.eor and t.eor set to 8 (i.e. empty page). if (only) 
 * h.eor != t.eor they were set to the smaller of their two values.
 */
typedef struct {
	struct {		/* header */ 
		uint32	page;	/* 4: log sequence page number */
		int16	rsrvd;	/* 2: */
		int16	eor;	/* 2: end-of-log, rec offset of last record 
				 *    written within this page */
	} h;

	int32	data[LOGPSIZE/4 - 4];	/* log record area */

	struct {		/* trailer */
		uint32	page;	/* 4: normally the same as h.page */
		int16	rsrvd;	/* 2: */
		int16	eor;	/* 2: normally the same as h.eor */
	} t;
} logpage_t;

#define LOGPHDRSIZE	8	/* log page header size */
#define LOGPTLRSIZE	8	/* log page trailer size */

/*
 *	log physical page (tbd: split/out-of-order write detection)
 */
typedef struct {
	struct {
		int16	data[255];
		int16	timestamp;
	} sector[8];
} ppage_t;

 
/*
 *	log record
 *
 * (this comment should be rewritten !)
 * j2 uses only "after" log records (only a single writer is allowed
 * in a  page, pages are written to temporary paging space if
 * if they must be written to disk before commit, and i/o is
 * scheduled for modified pages to their home location after
 * the log records containing the after values and the commit 
 * record is written to the log on disk, undo discards the copy
 * in main-memory.)
 *
 * a log record consists of a data area of variable length followed by 
 * a descriptor of fixed size LOGRDSIZE bytes.
 * the  data area is rounded up to an integral number of 4-bytes and 
 * must be no longer than LOGPSIZE.
 * the descriptor is of size of multiple of 4-bytes and aligned on a 
 * 4-byte boundary. 
 * records are packed one after the other in the data area of log pages.
 * the longest record is placed on at most two pages.
 * the field eor in page header/trailer points to the byte following 
 * the last record on a page.
 */

/* log record types */
#define LOG_COMMIT		0x8000
#define LOG_SYNCPT		0x4000
#define LOG_MOUNT		0x2000
#define LOG_FSSYNCPT  		LOG_MOUNT /* MOUNT used as per fs syncpt */
#define LOG_REDOPAGE		0x0800
#define LOG_NOREDOPAGE		0x0080
#define LOG_UPDATEMAP		0x0008
#define LOG_XDTABLE		0x0004
#define LOG_NOREDOFREE		0x0002
#define LOG_NOREDOFILE		0x0001
#define LOG_AIMAP		0x0040	/* Aggregate inode alloc/free */
#define LOG_ALLOCINOEXT		0x0020	/* defunct */

/* REDOPAGE/NOREDOPAGE log record data type */
#define	LOG_INODE		0x0001
#define	LOG_XTREE		0x0002
#define	LOG_DTREE		0x0004
#define	LOG_BTROOT		0x0010
#define	LOG_EA			0x0020
#define	LOG_ACL			0x0040
#define	LOG_SYMLINK		0x0080
#define	LOG_NEW			0x0100
#define	LOG_EXTEND		0x0200
#define LOG_RELOCATE		0x0400

/* UPDATEMAP log record descriptor type */
#define	LOG_ALLOCXADLIST	0x0080
#define	LOG_ALLOCPXDLIST	0x0040
#define	LOG_ALLOCXAD		0x0020
#define	LOG_ALLOCPXD		0x0010
#define	LOG_FREEXADLIST		0x0008
#define	LOG_FREEPXDLIST		0x0004
#define	LOG_FREEXAD		0x0002
#define	LOG_FREEPXD		0x0001

/* XDTABLE log record descriptor type (ref. tlckXDTABLE flag) */
/* iag inode extent table */
#define	LOG_ALLOCIX	0x0001
#define	LOG_FREEIX	0x0002
#define	LOG_RELOCIX	0x0004
/* bit reserved for use in 5.4 */
#define LOG_FILESET	0x0800
/* file/directory extent relocation */
#define	LOG_RELOCXTREE	0x0010
#define	LOG_RELOCEAv1	0x0040
#define LOG_RELOCDTREE	0x0080
/* snapshot group map extent table */
#define LOG_ALLOCMX	0x0100
#define LOG_FREEMX	0x0200
#define LOG_RELOCMX	0x0400

/* aiMap allocation/free */
#define	LOG_ALLOCAI	0x0001
#define	LOG_FREEAI	0x0002

typedef struct lrd {
	/*
	 * type independent area
	 */
	int32	logtid;		/* 4: log transaction identifier */
	int32	backchain;	/* 4: ptr to prev record of same transaction */
	dev64_t	aggregate;	/* 8: file system lv/aggregate */
	uint16	type;		/* 2: record type */
	int16	length;		/* 2: length of data in record (in byte) */
                                /*    it does not include the length of  */
                                /*    the lrd itself                     */   
	int32   logpad;		/* 4: XXX alignment  */
				/* (24) */

	/*
	 * type dependent area (32)
	 */
	union {

		/*
		 *	COMMIT: commit
		 *
		 * transaction commit: no type-dependent information;
		 */

		/* In the following, 
		 * REDOPAGE, NOREDOPAGE, NOREDOFREE and UPDATEMAP 
		 * must be same format;
		 */

		/*
		 *	REDOPAGE: after-image
		 *
		 * apply after-image;
		 *
		 */
		struct {
			ino64_t	inode;		/* 8: inode number */
			pxd_t	pxd;		/* 8: on-disk page pxd */
			uint32	fileset;	/* 4: fileset number */
			uint16	type;		/* 2: REDOPAGE record type */
			int16	l2linesize;	/* 2: log2 of line size */
			int64   logpad;         /* 8: pad */
		} redopage;			/* (32) */

		/*
		 *	NOREDOPAGE: the page is freed
		 *
		 * do not apply after-image records which precede this record
		 * in the log with the same page block number to this page.
		 */
		struct {
			ino64_t	inode;		/* 8: inode number */
			pxd_t   pxd;            /* 8: on-disk page pxd */
			uint32	fileset;	/* 4: fileset number */
			uint16	type;		/* 2: NOREDOPAGE record type */
			int16	rsrvd;		/* 2: reserved */
			int64   logpad;         /* 8: pad */
		} noredopage;			/* (32) */

		/*
		 *	NOREDOFREE: the meta data page extent is freed 
		 *
		 * do not apply after-image records which precede this record
		 * in the log with the same page block number to this page.
		 * and also update the blk map to show the freed extent
		 *
		 * Note: this log rec is a combined LOG_NOREDOPAGE and
		 *       LOG_UPDATEMAP with the simplist updatemap case, 
		 *       i.e. FREEPXD
		 */
		struct {
			ino64_t	inode;		/* 8: inode number */
			pxd_t   pxd;            /* 8: on-disk page pxd */
			uint32	fileset;	/* 4: fileset number */
			uint16	type;		/* 2: NOREDOFREE record type */
			int16	rsrvd;		/* 2: reserved */
			int64   logpad;         /* 8: pad */
		} noredofree;			/* (32) */


		/*
		 *	UPDATEMAP: update block allocation map
		 *
		 * either in-line PXD,
		 * or	  out-of-line  XADLIST;
		 */
		struct {
			ino64_t	inode;		/* 8: inode number */
			pxd_t	pxd;		/* 8: pxd */
			uint32	fileset;	/* 4: fileset number */
			uint16	type;		/* 2: UPDATEMAP record type */
			int16	nxd;		/* 2: number of extents */
			int64   logpad;         /* 8: pad */
		} updatemap;			/* (32) */

		/*
		 *	XDTABLE: alloc/free/relocate extent specified 
		 *	by an xd entry of embedded xd table;
		 *
		 * update xd table entry, establish noRedoPage filter and
		 * update bMap according to the specific subtype;
		 */
		struct {
			pxd_t	pxd;		/* 8: parent page pxd */
			int32	page;		/* 4: parent page index */
			int16	index;		/* 2: parent xd table entry index */
			uint16	type;		/* 2: subtype */
			pxd_t	spxd;		/* 8: source pxd */
			pxd_t	dpxd;		/* 8: destination pxd */
		} xdTable;			/* (32) */

		/*
		 *	NOREDOINOEXT: the inode extent is freed
		 *
		 * do not apply after-image records which precede this 
		 * record in the log with any of the 4 page block numbers
		 * in this inode extent. 
		 * 
	   	 * NOTE: The fileset and pxd fields MUST remain in 
	   	 * 	 the same fields in the REDOPAGE record format.
		 *
		 */
		struct {	/* defunct - to be replaced */
			ino64_t	iagnum;		/* 8: IAG number     */
			pxd_t	pxd;		/* 8: on-disk page pxd */
			uint32	fileset;	/* 4: fileset number */
			int32   logpad;         /* 4: pad */
			ino64_t inoext_idx;     /* 8: inode extent index */
		} noredoinoext;			/* (32) */

		struct {	/* defunct - to be replaced */
			ino64_t	iagnum;		/* 8: IAG number     */
			pxd_t	pxd;		/* 8: on-disk page pxd */
			uint32	fileset;	/* 4: fileset number */
			int32   logpad;         /* 4: pad */
			ino64_t inoext_idx;     /* 8: inode extent index */
		} allocinoext;			/* (32) */

		/*
		 *	SYNCPT: log sync point
		 *
		 * replay log upto syncpt address specified;
		 */
		struct {
			int32	sync;		/* 4: syncpt address (0 = here) */
			int32   logpad;         /* 4: pad */
			int64   logpad3[3];     /* 24: pad */
		} syncpt;			/* (32) */

		/*
		 *	MOUNT: file system mount
		 *
		 * file system mount: no type-dependent information;
		 */

		/*
		 *	NOREDOFILE: this file is freed
		 *
		 * do not apply records which precede this record in the log
		 * with the same inode number.
		 *
		 * NOREDILE must be the first to be written at commit
		 * (last to be read in logredo()) - it prevents
		 * replay of preceding updates of all preceding generations
		 * of the inumber esp. the on-disk inode itself, 
		 * but does NOT prevent
		 * replay of the 
		 */
		struct {
			ino64_t	inode;		/* 8: inode number */
			int64   rsrvd1;		/* 8: reserved space */
			uint32	fileset;	/* 4: fileset number */
			int32   logpad;         /* 4: pad */
			int64   logpadx;        /* 8: pad */
		} noredofile;			/* (32) */

		/*
		 *	AIMAP: alloc/free inode from aiMap 
		 */
		struct {
			int16	type;
			int16	rsrvd1;
			int32	rsrvd2;
			ino64_t	inode;		/* 8: inode number */
			pxd_t	iagpxd;		/* 8: iag pxd */
			pxd_t	ixpxd;		/* 8: inode extent; */
		} aiMap;		/* (32) */	

	      } log;
} lrd_t;				/* (56) */

#define	LOGRDSIZE	(sizeof(struct lrd))

/*
 *	line vector descriptor
 */
typedef struct {
	int16	offset;
	int16	length;
} lvd_t;

#ifdef _KERNEL

#include <j2/j2_inode.h>
#include <j2/j2_bufmgr.h>
#include <j2/j2_debug.h>

/*
 *	log logical volume inode.
 *
 * represented by convention in-memory inode 
 * (dev_t of log device, i_number = 0)
 *
 * N.B. overlaid on inode;
 */
typedef struct log {
	/*
	 * in-memory inode overlay
	 */
	struct wInode;		/* working area */

	/*
	 * on-disk inode overlay (512 bytes)
	 */
	/* following 3 fields must match dinode struct */
	ino64_t	di_number;	/* inode number, aka file serial number */

	union {
		uint32	di_gen;		/* inode generation number */
		struct {
			uint8 logsyncgen; 	/* logsync attempt */
			uint8 logwritegen;	/* empty commit txn */
			uint16 reserved;
		};
	};
	
	uint32	di_fileset;	/* fileset #, inode # of inode map file */

	LIST_ENTRY(log)	logList;/* active logList link */

	uint32	flag;		/* flag (dup) */
	uint32	state;		/* state */
	struct file	*devfp;	/* log device file */
	struct logx	*logx;	/* extension for pinned data */

	dev_t	dev;		/* log lv number */
	int64	serial;		/* log mount serial number */

	int64	base;		/* log extent address (inline log ) */
	int32	size;		/* log size in log page (in page) */
	int32	bsize;		/* log page/block size in byte */
	int32	pbsize;		/* hardware/LVM block size in bytes */
	int16	l2bsize;	/* log2 of log2(bsize) */
	int16	l2pbsize;	/* log2 of log2(pbsize) */

	MUTEXLOCK_T   logLock;	/* log serialization lock */
	int32	logTid;		/* log tid */

	/* log write */
	struct logBuffer	*bp;	/* current log page buffer */
	int64	lspn;		/* log sequence page number */
	int32	pn;			/* page number of eol page */
	int32	eor;		/* eor of last record in eol page */
	MUTEXLOCK_T   rdwrLock;	/* log read/write serialization lock */

	/* commit */
	struct {		/* FIFO commit queue header */
		struct txBlock	*head;
		struct txBlock	*tail;
	} commitQueue;
	uint32	cflag;		/* */
	int32	gcrtc;		/* GC_READY transaction count */
	struct txBlock	*gclrt;	/* latest GC_READY transaction */
	MUTEXLOCK_T	gcLock;	/* group commit lock */

	/* syncpt */
	int64	nextsync;	/* bytes to write before next syncpt */
	int32	active;		/* */
	int32	syncBarrier;	/* */
	event_t	syncWait;	/* */
	int32	syncTid;	/* reserved txBlock for iLogSync() */

	/* error log flag for jfs2 log */
	uint32	errlog;

	/* statistics */
	reg_t	nTxLog;
	int32	j2LogSyncCount;	/* logwrap: # of times transactions blocked */
	int32	j2LogWrapCount;	/* logwrap: # of times log actually wrapped */
} log_t;

/* the di_gen field is now split off into bytes and used to track when the
 * log was last updated
 */

uint8 j2LogSyncGen; 	/* Indicates last time log sync point was
			 * moved by lmLogSyncAll() calling
			 * lmLogSync().  Init'ing to garbage is fine.
			 */

uint8 j2LogWriteGen; 	/* Indicates last time log pages were forced
			 * to disk with empty transaction.
			 * Initializing to garbage is okay.
			 */

/* Make sure the log inode structure fits inside the dinode structure */
J2_FILE_ASSERT(log_t, (sizeof(struct dinode) >=
		(sizeof(struct log) - offsetof(log_t, di_number))));

/* flags for errlog field in log_t */
#define EL_LOGWRAP	0x00000001
#define EL_LOGWRAPSTOP	0x00000002

/*
 * group commit flag
 */
/* log_t */
#define logGC_PAGEOUT	0x00000001

/* tblock_t/lbuf_t */
#define tblkGC_QUEUE		0x0001
#define tblkGC_READY		0x0002
#define tblkGC_COMMIT		0x0004
#define tblkGC_COMMITTED	0x0008
#define tblkGC_EOP		0x0010
#define tblkGC_FREE		0x0020
#define tblkGC_LEADER		0x0040
#define tblkGC_ERROR		0x0080
#define tblkGC_WAIT		0x0100

/*
 *	logSyncList block
 *
 * common logSyncBlock prefix for jbuf_t and logSyncList cursor
 */
typedef struct logSyncBlock {
	uint16	xflag;			/* pageout control flags */
	int16	nohomeok;	
	int32	flags;
	struct txLock	*lid;

	int64	lsn;			/* log sequence number */
	int64	clsn;			/* commit lsn */
	CDLL_ENTRY(logSyncBlock)	syncList;	/* logSyncList link */
} logSyncBlock_t;

/* 
 *	logx - log inode pinned extension
 */
typedef struct logx {

	uint32		flag;		/* 4: flag (dup) */
	int64		size;		/* 4: log size in byte */
	int32		space;		/* 4: log data area size in byte */
	int64		lsn;		/* 4: eol lsn */
	int64		clsn;		/* 4: commit lsn */

	/* syncpt */
	int64		syncpt;		/* 4: addr of last syncpt record */
	int64		sync;		/* 4: addr from last logsync() */
	IOSPINLOCK_T	syncListLock;	/* syncList lock */
	CDLL_HEADER(logSyncBlock) syncList; /* logSyncList anchor */
	logSyncBlock_t	bmLogSyncCursor;  /* logSyncList cursor */
	logSyncBlock_t	bmLogSyncRCursor; /* logSyncList cursor */

	/* i/o */
	IOSPINLOCK_T	ioLock;		/* i/o lock */
	struct logBuffer *pageOutQueue;	/* log pageout queue */
	struct logBuffer *freeBufferList; /* lbuf freeList header */
	int32		nFreeBuffer;	/* # of free lbuf */

	/* logWrite throttle */
	int32		nBuffer;	/* 2: number of iobuf */
	int32		hwmBuffer;	/* 4: hwm write ahead  */ 
	int32		lwmBuffer;	/* 4: lwm write ahead */ 
	event_t		lwmBufferWait;	
	event_t		freeBufferWait;	

	/* log i/o error monitor */
	int32		count;		/* 2: page count */
	int32		errCount;	/* 2: error page count */
	int32		hwmErrCount;	/* high-water-mark error page count */
	int32		lwmErrCount;	/* low-water-mark error page count */

	/* log ras components */
	ras_block_t	lx_logRASB;	/* per log component */
} logx_t;

/* logx flag */
#define	LOG_BUFFER_HWM	0x00000001

/*
 *		log cache buffer header
 *
 * N.B. overlaid on pbuf_t
 */
typedef struct logBuffer {
	/*
	 * prefix area overlay
	 */
	uint16	pb_xflag;		/* pageout control flags */
	int16	pb_nohomeok;
	uint32	lb_flag;			/* pb_flags: pageout control flags */
	struct txLock	*pb_lid;	/* tlock id */

	int64	lb_lspn;		/* pb_lsn: log sequence number */
	int64	lb_clsn;		/* pb_clsn: commit lsn */
	CDLL_ENTRY(logSyncBlock) pb_syncList;/* logSyncList link */

	struct logx	*pb_logx;	/* log inode pinned extension */
	log_t	*lb_log;		/* pb_ip: inode associated with buffer */

	/*
	 *	base area overlay
	 */
	int32		lb_ceor;			/* pb_count: committed log record eor */
	int32		pb_cacheClass;
	logx_t		*lb_logx;		/* *pb_pagerOBject: log inode extension */
	LIST_ENTRY(logBuffer)	pb_pageList;	/* pageList link */
	LIST_ENTRY(logBuffer)	pb_hashList;	/* hashList link */
	union {
		CDLL_ENTRY(logBuffer)	_cacheList; /* cacheList link */
		struct logBuffer *_freeList;	/* _freeNext: freeList link */
	} _lb_u1;					/* _pb_u1: */
	struct logBuffer *lb_ioNext;	/* *pb_ioNext: ioList link */
	event_t		lb_waitList;	/* checkOut waitList */
	caddr_t		lb_data;		/* pb_data: data page */
	int64		lb_blkno;		/* pb_xoffset: log page block number */
	int32		lb_pn;			/* pb_pxd1: log page number */
	int32		lb_eor;			/* pb_pxd2: log record eor */
	event_t		lb_ioWait;		/* pb_ioWait: i/o done event */
	iobuf_t		*lb_iobp;		/* pb_iobp: i/o buffer */
} lbuf_t;

/* Make sure the fields still line up */
J2_FILE_ASSERT( iobppos, offsetof(pbuf_t, pb_iobp) == offsetof(lbuf_t, lb_iobp) );

/* Make sure the ras info is accessible */
J2_FILE_ASSERT( rasinfo, offsetof(pbuf_t, pb_type) >= sizeof(lbuf_t) );
				  
#define	lb_freeList	_lb_u1._freeList


/*
 *	log serialization (per log)
 */
/* LOG_LOCK_ALLOC(log,id)/LOG_LOCK(INIT(log): ref. j2_Logmgr.c */
#define LOG_LOCK(log)		MUTEXHOTLOCK_LOCK(&((log)->logLock))
#define LOG_UNLOCK(log)		MUTEXHOTLOCK_UNLOCK(&((log)->logLock))


/*
 *	logSyncList serialization (per log)
 */
/* LOGSYNC_LOCK_ALLOC(logx,id)/LOGSYNC_LOCK_INIT(logx): ref. j2_logmgr.c */
#define	LOGSYNC_LOCK(logx)		IOSPINLOCK_LOCK(&(logx)->syncListLock)
#define LOGSYNC_LOCK_TRY(logx)		IOSPINLOCK_LOCK_TRY(&(logx)->syncListLock)

#define	LOGSYNC_UNLOCK(logx)	IOSPINLOCK_UNLOCK(&(logx)->syncListLock)
#define	LOGSYNC_DISABLE_LOCK(logx) \
	IOSPINLOCK_DISABLE_LOCK(&(logx)->syncListLock)
#define	LOGSYNC_UNLOCK_ENABLE(xipl, logx)\
	IOSPINLOCK_UNLOCK_ENABLE(xipl, &(logx)->syncListLock)


/* compute the difference in bytes of lsn from sync point */
#define logDifference(diff, lsn, logx)\
{\
	diff = (lsn) - (logx)->syncpt;\
	if (diff < 0)\
		diff += (logx)->size;\
}

static __inline void lmLogSyncRelease(
	logx_t	*lop,
	pbuf_t	*pbp)
{
	CDLL_REMOVE(&lop->syncList, (logSyncBlock_t *)pbp, syncList);
	pbp->pb_syncList.next = NULL;
	
	pbp->pb_xflag &= ~PB_SYNCPT;
	pbp->pb_lsn = 0;
	pbp->pb_clsn = 0;
	pbp->pb_logx = NULL;
}

/*
 *	prototypes for log manager services.
 */
reg_t	lmInit(void);
void    lmInitCleanup(void);
int32	lmLog(log_t *log, struct txBlock *tblk, lrd_t *lrd, struct txLock *tlck);
reg_t	lmLogOpen(inode_t *ipmnt, inode_t **iplog);
reg_t	lmLogClose(inode_t *ipmnt, inode_t *iplog);
int64	lmLogSync(log_t *log, reg_t nosyncwait);
void	lmLogSyncAll(void);
reg_t	lmLogQuiesce(log_t *log);
reg_t	lmLogResume(log_t *log, inode_t *ipmnt);
reg_t	lmLogFormat(inode_t *ipmnt, int64 logAddress, reg_t logSize);
reg_t	lmGroupCommit(log_t *log, struct txBlock *tblk);
void	lmSync(log_t *log);
int32	lmLogException(inode_t *ipmnt, log_t *log, int32 logrc);
#endif	/* _KERNEL */

#endif /* _H_J2_LOGMGR */	
