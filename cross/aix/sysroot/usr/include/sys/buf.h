/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/sys/buf.h 1.38                                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)05     1.38  src/bos/kernel/sys/buf.h, sysios, bos53H, h2005_33B9 8/6/05 19:37:48 */
#ifndef _H_BUF
#define _H_BUF
/*
 * COMPONENT_NAME: (SYSIOS) Buffer Header structure
 *
 * ORIGINS: 3, 27, 83
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 *   LEVEL 1,  5 Years Bull Confidential Information
 */

/*
 *  Buffer cache buffer header
 *  A buffer header contains all the information required to perform block
 *  I/O.  It is the primary interface to the bottom half of block device
 *  drivers.  These drivers are needed for all file system and paging
 *  devices.  In AIX version 3, the traditional strategy() interface is
 *  extended as follows:
 *
 *    1.   The device driver strategy() routine is called with a
 *	   list of buf structures, chained using the av_forw pointer.
 *	   The last entry in this list has a NULL av_forw pointer.
 *
 *    2.   When the operation is completed, and the driver calls
 *	   iodone(), the b_iodone function is scheduled to run as a
 *	   INTIODONE software interrupt handler.  This function is
 *	   passed the buf struct address as its argument.
 *
 *  Buf structures are allocated by I/O requesters, and contain fields
 *  representing the state of some associated data page.  The device driver
 *  must leave most of the fields in this structure intact.  It is allowed
 *  to use av_forw and av_back to queue active requests, and it must set
 *  b_resid on return.	If there was an error, it sets B_ERROR in b_flags,
 *  and returns an errno value in b_error.
 *
 *  The buf struct and its associated data page must be pinned before
 *  calling the strategy() routine.  Block driver bottom halves run
 *  without access to user process context, and are not allowed to page
 *  fault.
 *
 *		    Kernel buffer cache management
 *
 * The block I/O routines use a pool of buf structures to manage
 * the kernel buffer cache.  Each buffer in the pool is usually
 * doubly linked into 2 lists:
 *
 *   1)  a hash list if it has useful contents, and
 *   2)  a list of blocks available for allocation.
 *
 * A buffer is on the available list, and can be reassigned to another
 * disk block, if and only if it is not marked BUSY.  When a buffer
 * is busy, the available-list pointers can be used for other purposes.
 * Most drivers use the forward ptr as a link in their I/O active queue.
 * A buffer header contains all the information required to perform I/O.
 * Most of the routines which manipulate these things are in bio.c.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/xmem.h>
#include <sys/time.h>
#include <sys/ras.h>

#ifdef __cplusplus
struct vnode;
#endif

struct buf {				/* buffer header		 */
	__long64_t b_flags;		/* flag word (see defines below) */

	struct	buf *b_forw;		/* hash list forward link	 */
	struct	buf *b_back;		/* hash list backward link	 */
	struct	buf *av_forw;		/* free list forward link	 */
	struct	buf *av_back;		/* free list backward link	 */

	void	(*b_iodone)();		/* ptr to iodone routine	 */
	struct	vnode *b_vp;		/* vnode associated with block	 */
	dev_t	b_dev;			/* major+minor device name	 */
	daddr_t b_blkno;		/* block # on device or in file  */

	union {
	    caddr_t  b_addr;		/* buffer address		 */
	} b_un;

	__ulong64_t  b_bcount;		/* transfer count, OR		  */
					/* #blks in list (bfreelist only) */
	char	     b_error;		/* returned after I/O		  */
	__ulong64_t  b_resid;		/* words not xferred after error  */
	__long64_t   b_work;		/* work area for device drivers   */
	int	     b_options; 	/* readx/writex extension options */
	tid_t	     b_event;		/* anchor for event list	  */
	struct timestruc_t b_start;	/* request start time		  */
	struct	     xmem b_xmemd;	/* xmem descriptor		  */
};

#define	b_baddr		b_un.b_addr	/* address of data		  */

/*
 * These flags are kept in b_flags.
 */
#define B_WRITE 	(long)0x0000	/* non-read pseudo-flag */
#define B_READ		(long)0x0001	/* read when I/O occurs */
#define B_DONE	 	(long)0x0002	/* I/O complete */
#define B_ERROR 	(long)0x0004	/* error detected */
#define B_BUSY		(long)0x0008	/* in use or I/O in progress */
#define B_WLM_UNMNGD	(long)0x0010	/* not managed by WLM regulation */
#define B_INFLIGHT	(long)0x0020	/* this request is in-flight */
#define B_LOGDEV        (long)0x0040    /* request to/from the log device */
#define B_AGE		(long)0x0080	/* put at hd of freelst when released */
#define B_ASYNC 	(long)0x0100	/* don't wait for I/O completion */
#define B_DELWRI	(long)0x0200	/* don't write till blk is reassigned */
#define B_NOHIDE	(long)0x0400	/* don't hide pages during dma xfer */
#define B_STALE 	(long)0x0800	/* data in buffer is no longer valid */
#define B_MORE_DONE	(long)0x1000	/* more buffers to be processed */
#define B_PFSTORE 	(long)0x2000	/* store operation */
#define B_PFPROT 	(long)0x4000	/* protection violation */
#define B_SPLIT 	(long)0x8000	/* ok to enable split read/write */
#define B_PFEOF 	(long)0x10000	/* check for ref. beyond end-of-file */

				/* write of smudged page (async client seg) */
#define B_COMMIT	(long)0x20000 	
#define B_MPSAFE	(long)0x40000 /* Invoker of strategy() is MP safe */

#ifdef _KERNEL
#define B_MPSAFE_INITIAL (long)0x80000 /* devstrat() converts B_MPSAFE into */
				/*	this flag */
#endif /* _KERNEL */

#ifdef _KERNSYS
#define B_COMPACTED	(long)0x100000 /* comapcted coalesce list */
#define	B_DONTUNPIN	(long)0x200000 /* pin() failed - don't unpin buf */

#endif /* _KERNSYS */

#define B_BUSDMA        (long)0x400000
#define B_DONE_ASYNC	(long)0x800000 /* ASYNC write completed */
#define B_SETMOD        (long)0x1000000 /* fs -> VMM: page is modified */

/*
 * LVM lost I/O detection for system hang feature
 */
#define	B_LIOS		(long)0x1000000		/* buf scanned for lost I/O */
#define	B_LIOD		(long)0x2000000		/* buf detected as lost I/O */

/*
 * External pager buffer
 */
#define	B_XPAGER	(long)0x80000000	/* D_XPAGER */
#define	B_XREADONLY	(long)0x40000000	/* read-only page */
/* lvm logical track split flag */
#define	B_XSPLIT	(long)0x30000000	/* split i/o across lt boundary */
#define	B_XSPLIT1	(long)0x10000000	/* split i/o 1st half */
#define	B_XSPLIT2	(long)0x20000000	/* split i/o 1st half */

struct bufx {				/* buffer header		    */
	__long64_t b_flags;		/* flag word (see defines below)    */

	struct	bufx *b_forw;		/* hash list forward link	    */
	struct	bufx *b_back;		/* hash list backward link	    */
	struct	bufx *av_forw;		/* free list forward link	    */
	struct	bufx *av_back;		/* free list backward link	    */

	void	(*b_iodone)();		/* ptr to iodone routine            */
	struct	vnode *b_vp;		/* vnode associated with block	    */
	dev_t	b_dev;			/* major+minor device name	    */
	daddr_t b_blkno;		/* block # on device or in file     */

	union {
	    caddr_t  b_addr;		/* buffer address	            */
	} b_un;

	__ulong64_t  b_bcount;		/* transfer count, OR		    */
					/* #blks in list (bfreelist only)   */
	char	    b_error;		/* returned after I/O		    */
	char	    b_pad[3];		/* 3 bytes of padding		    */
#ifdef __64BIT_KERNEL
	uint	    bx_refptrtop;	/* top half of reference pointer    */
#endif
	__ulong64_t  b_resid;		/* words not xferred after error    */
	__long64_t   b_work;		/* work area for device drivers     */
	int	    b_options;		/* readx/writex extension options   */
#ifdef __64BIT_KERNEL
	uint	    bx_refptrbot;	/* bottom half of reference pointer */
#endif
	tid_t	    b_event;		/* anchor for event list	    */
	struct timestruc_t b_start;	/* request start time		    */
	struct xmem b_xmemd;		/* xmem descriptor		    */
	int	    bx_version;		/* bufx version number		    */
	eye_catch4b_t bx_eyecatcher;	/* eyecatcher ? "bufx"              */
	__long64_t   bx_flags;		/* bufx flags ? This field has been */
					/* added because b_flags is running */
					/* out of bits.      	            */
	__ulong64_t bx_error_detail;	/* additional info about error      */
	__ulong64_t bx_work2;		/* Extra work area                  */
	ushort    bx_io_priority;	/* IO Priority			    */
	ushort    bx_io_cache_hint;	/* IO cache hint		    */
	int	    bx_resvd1;		/* Padding for 8 bytes alignment    */
	__ulong64_t bx_resvd2[7];	/* Padding space reserved for       */
	__ulong64_t bx_resvd3;		/* future extensions.               */
/*
* Add new fields as needed by claiming some of the padding space.
* There should be enough padding space so that it should not be
* necessary to increase the size of the structure in the foreseeable
* future.
*/
};

#define BUFX_VER0		0
#define BUFX_VER0_SIZE (offsetof(struct bufx, bx_resvd3)+sizeof(__ulong64_t))
#define BUFX_VERSION	BUFX_VER0	 /* current version - to be updated  *
					  * when new version is created      */
#define BUFX_SIZE	sizeof(struct bufx)

/* b_flags value for bufx */
#define B_BUFX		(long)0x4000000	 /* structure is a bufx */
#define B_BUFX_INITIAL	(long)0x8000000	 /* structure is a bufx */


#ifdef __64BIT_KERNEL

#define BUFX_ADDR(bufxp)						 \
	(((unsigned long)(((struct bufx *)bufxp)->bx_refptrtop) << 32) | \
		(unsigned long)(((struct bufx *)bufxp)->bx_refptrbot))

#define IS_BUFX(bufxp)							\
	((((struct bufx *)bufxp)->b_flags & (B_BUFX | B_BUFX_INITIAL)) 	\
	&& (BUFX_ADDR(bufxp) == (unsigned long)bufxp)			\
	&& (((struct bufx *)bufxp)->bx_eyecatcher == EYEC_BUFX))

#define BUFX_VALIDATE (bufxp)						   \
	if ((((struct bufx *)bufxp)->b_flags & (B_BUFX | B_BUFX_INITIAL))  \
			&& !(IS_BUFX(bufxp)))				   \
		((struct bufx *)bufxp)->b_flags &= ~(B_BUFX | B_BUFX_INITIAL)

#else/* !__64BIT_KERNEL */

#define BUFX_ADDR(bufxp)	NULL
#define IS_BUFX(bufxp)		0
#define BUFX_VALIDATE(bufxp)	\
	((struct buf *)bufxp)->b_flags &= ~(B_BUFX | B_BUFX_INITIAL)

#endif /* __64BIT_KERNEL */

#define BUF_INIT(bufp)		memset((void *)bufp, 0, sizeof(struct buf))
#define BUF_INVALIDATE(bufp)	memset((void *)bufp, 0, sizeof(struct buf))

/*
 * The following services provide the interface to the buffer cache
 * and block I/O.
 */

#ifdef _KERNEL
#ifndef _NO_PROTO

struct buf * getblk(		/* allocate uninitialized buffer to block */
	dev_t dev,		/* the device containing block */
	daddr_t blkno);		/* the block to be allocated */

struct buf *geteblk(void);	/* allocate uninitialized buffer	*/

struct buf *bread( 		/* allocate buffer to block and read it */
	dev_t dev,		/* the device containing block */
	daddr_t blkno);		/* the block to be allocated */

struct buf *breada( 		/* allocate buffer to block and read it */
	dev_t dev,		/* the device containing block */
	daddr_t blkno,		/* the block to be allocated */
	daddr_t rablkno);	/* read ahead block */

void brelse(	 		/* free buffer; no I/O implied */
	struct buf *bp); 	/* buffer to be released */

int bwrite(	 		/* write buffer; then free it */
	struct buf *bp); 	/* buffer to be written */

void bdwrite(	 		/* mark buffer for delayed write and free it */
	struct buf *bp); 	/* buffer to be written */

int bawrite(	 		/* async write buffer; then free it */
	struct buf *bp); 	/* buffer to be written */

void bflush(	 		/* flush all delayed write blocks */
	dev_t dev);		/* the device containing blocks */

int blkflush(			/* flush the delayed write block */
	dev_t dev,		/* the device containing block */
	daddr_t blkno);		/* the block to be flushed */

void binval(	 		/* invalidate all blocks */
	dev_t dev);		/* the device containing blocks */

int iowait(			/* wait for I/O completion */
	struct buf *bp); 	/* buffer to wait for completion of */

void iodone(	 		/* call the requester's I/O done routine */
	struct buf *bp); 	/* buffer with completed operation */

long bufx_init(			/* Initializes extended buf */
	struct bufx *bufxp,
	int version);

void bufx_invalidate (		/* Invalidates extended buf */
	struct bufx *bufxp);

long buf_copy(			/* copies extended/legacy buf/bufx */
	void *src_bufp,		/* into extended/legacy buf	   */
	void *dest_bufp);

#else

struct buf *getblk();
struct buf *geteblk();
struct buf *bread();
struct buf *breada();
void brelse();
int bwrite();
void bdwrite();
int bawrite();
void bflush();
int blkflush();
void binval();
int iowait();
void iodone();
long bufx_init();
void bufx_invalidate();
long buf_copy();

#endif /* not _NO_PROTO */

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)

void clrbuf(                    /* zero buffers memory */
        struct buf *bp);        /* buffer to clear */

int geterror(                   /* get completion status of a buffer */
        struct buf *bp);        /* buffer for which to check status */
                                /* returns 0 or errno value */

void purblk(                    /* Purge a block from the buffer cache */
        dev_t dev,              /* device containing the block */
        daddr_t blkno);         /* block to be purged */

#endif /* (__64BIT_KERNEL) || (__FULL_PROTO) */

#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* _H_BUF */
