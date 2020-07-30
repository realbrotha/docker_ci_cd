/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/j2/include/j2_imap.h 1.16                        */
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

/* @(#)90     1.16  src/bos/kernel/j2/include/j2_imap.h, sysj2, bos53D, d2005_16C2 4/11/05 17:16:39 */
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

#ifndef	_H_J2_IMAP
#define _H_J2_IMAP	
/*
 * FUNCTION: disk inode allocation map manager
 */

/* Include j2_inode and j2_xtree out of tradition */
#include <j2/j2_inode.h>
#include <j2/j2_xtree.h>

/*
 *	j2_imap.h: disk inode manager
 */

#define	EXTSPERIAG	128	/* number of disk inode extent per iag 	*/
#define IMAPBLKNO	0	/* lblkno of dinomap within inode map	*/
#define SMAPSZ		4	/* number of words per summary map	*/
#define	EXTSPERSUM	32	/* number of extents per summary map entry */
#define	L2EXTSPERSUM	5	/* l2 number of extents per summary map	*/
#define	PGSPERIEXT	4	/* number of 4K pages per dinode extent */
#define	MAXIAGS		((1<<20)-1)	/* maximum number of iags	*/
#define	MAXAG		128	/* maximum number of allocation groups	*/

#define AMAPSIZE	512	/* bytes in the IAG allocation maps */
#define SMAPSIZE	16	/* bytes in the IAG summary maps */

/* convert inode number to iag number */
#define	INOTOIAG(ino)	((ino) >> L2INOSPERIAG)

/* convert iag number to logical block number of the iag page */
#define IAGTOLBLK(iagno,l2nbperpg)	(((iagno) + 1) << (l2nbperpg))

/* get the starting block number of the 4K page of an inode extent
 * that contains ino.
 */
#define INOPBLK(pxd,ino,l2nbperpg)    	(addressPXD((pxd)) +		\
	((((ino) & (INOSPEREXT-1)) >> L2INOSPERPAGE) << (l2nbperpg)))

/* number of backed inodes in inode extent. 0 if PXD address is NULL. */
#define IXnBackedInode(_ixpxd, _l2bsize) \
	( addressPXD(_ixpxd) ? \
 	  (((lengthPXD(_ixpxd) << (_l2bsize)) >> L2jDISIZE)) : 0 )

/* mask of backed inodes in inode extent bit map */
#define IXBitMap(_niix)	\
    	((0xffffffff >> (INOSPEREXT - (_niix))) << (INOSPEREXT - (_niix)))

/* dinode buffer page size */
#define IXPageSize(_ixpxd, _l2bsize) \
	MIN(BPSIZE, (lengthPXD(_ixpxd) << (_l2bsize)))

/*
 *	inode allocation map:
 * 
 * inode allocation map consists of 
 * . the inode map control page dinomap_t and
 * . inode allocation group pages iag_t (per 4096 inodes)
 * which are addressed by standard J2 xtree.
 */
/*
 *	inode allocation group page (per 4096 inodes of an IAG)
 */
typedef struct {
	int64	agstart;	/* 8: starting block of ag		*/
	int32	iagnum;		/* 4: inode allocation group number 	*/
	int32	inofreefwd;	/* 4: ag inode free list forward 	*/
	int32	inofreeback;	/* 4: ag inode free list back 		*/
	int32	extfreefwd;	/* 4: ag inode extent free list forward */
	int32	extfreeback;	/* 4: ag inode extent free list back 	*/
	int32	iagfree;	/* 4: iag free list			*/

	/* summary map: 1 bit per inode extent */
	int32	inosmap[SMAPSZ];/* 16: sum map of mapwords w/ free inodes;
				 *	note: this indicates free and backed
				 *	inodes, if the extent is not backed the
				 *	value will be 1.  if the extent is
				 *	backed but all inodes are being used the
				 *	value will be 1.  if the extent is
				 *	backed but at least one of the inodes is
				 *	free the value will be 0.
				 */
	int32	extsmap[SMAPSZ];/* 16: sum map of mapwords w/ free extents */
	int32	nfreeinos;	/* 4: number of free inodes		*/
	int32	nfreeexts;	/* 4: number of free extents		*/
				/* (72) */
	uint8	pad[1976];		/* 1976: pad to 2048 bytes */

	/* allocation bit map: 1 bit per inode (0 - free, 1 - allocated) */
	uint32	wmap[EXTSPERIAG];	/* 512: working allocation map	*/
	uint32	pmap[EXTSPERIAG];	/* 512: persistent allocation map */
	pxd_t	inoext[EXTSPERIAG];	/* 1024: inode extent addresses */
} iag_t;				/* (4096) */

/*
 *	per AG control information (in inode map control page)
 */
typedef struct
{
	int32	inofree;	/* 4: free inode list anchor      	*/
	int32	extfree;	/* 4: free extent list anchor 		*/
	int32	numinos;	/* 4: number of backed inodes 		*/
	int32	numfree;	/* 4: number of free inodes 		*/
} iagctl_t;			/* (16) */

/*
 *	per fileset/aggregate inode map control page
 */
typedef struct
{
	int32		in_freeiag;	 /* 4: free iag list anchor	*/
	int32		in_nextiag;	 /* 4: next free iag number	*/
	int32		in_numinos;	 /* 4: num of backed inodes */
	int32		in_numfree;	 /* 4: num of free backed inodes */
	int32		in_nbperiext;	 /* 4: num of blocks per inode extent */
	int32		in_l2nbperiext;	 /* 4: l2 of in_nbperiext */
	int32		in_diskblock;	 /* 4: for standalone test driver  */
	int32		in_maxag;	 /* 4: for standalone test driver  */
	uint8		pad[2016];	 /* 2016: pad to 2048 */
	iagctl_t	in_agctl[MAXAG]; /* 2048: AG control information */
} dinomap_t;				/* (4096) */


#ifdef _KERNEL

#include <j2/j2_txnmgr.h>

/*
 *	In-core inode map control page
 */
typedef struct inomap
{
	dinomap_t	im_imap;	  /* 4096: inode allocation control */
	inode_t		*im_ipimap;	  /* 8: ptr to inode for imap	*/
	MUTEXLOCK_T	im_freelock;	  /* 8: iag free list lock	*/
	MUTEXLOCK_T	im_aglock[MAXAG]; /* 512: per AG locks		*/
	uint32		*im_DBGdimap;
} imap_t;

#define	im_freeiag	im_imap.in_freeiag
#define	im_nextiag	im_imap.in_nextiag
#define	im_numinos	im_imap.in_numinos
#define	im_numfree	im_imap.in_numfree
#define	im_agctl	im_imap.in_agctl
#define	im_nbperiext	im_imap.in_nbperiext
#define	im_l2nbperiext	im_imap.in_l2nbperiext

/* disk inode allocation request structure */
typedef struct ialloc 
{
	ino64_t	ino;		/* inode number			*/
	pxd_t	ixpxd;		/* inode extent address 	*/
	int64	agstart;	/* start of ag holding inode 	*/
	inode_t	*ip;		/* for diFree() */
} ialloc_t;

/* for standalone testdriver
 */
#define	im_diskblock	im_imap.in_diskblock
#define	im_maxag	im_imap.in_maxag

/* external references */
int32 diMount(inode_t *ipimap);
int32 diUnmount(inode_t *ipimap, uint32	mounterror);
int32 diAlloc(inode_t *pip, boolean_t dir, struct ialloc *iad);
int32 diFree(struct inode *ipimap, struct ialloc *iad);
int32 diFreeExtent(int32 tid, inode_t *ipimap, pbuf_t *bp, int32 ixn);
int32 diRead(inode_t *ip);
int32 diReadSpecial(inode_t *ip, int64 offset);
int32 diWrite(int32 tid, inode_t *ip, struct txLock *ditlck, boolean_t updateData);
int32 diIAGRead(imap_t *imap, int32 iagno, jbuf_t **bpp);
int32 diUpdatePMap(inode_t *ip, ino64_t inum, boolean_t is_free, tblock_t *tblk);
int32 diSync(inode_t *ipimap);
int32 diRelocateIMap(inode_t *ipimap, int64 xfence,
	int64 *nBlockToMove, int64 *nBlockMoved);
int32 diRelocateIAG(int32 tid, inode_t *ipimap, int64 pbn,
	int32 index, int64 dxaddr);
int32 diRelocateExtent(inode_t *ipimap, int32 iagn, int32 ixn,
	inode_t **ixipList, int64 xfence);
int32 diResizeFS(inode_t *ipimap, inode_t *ipbmap, int64 xfence, int32 flag);
int32 diAllocSpecial(inode_t *ipmnt, ino64_t fsno, ino64_t inum, ialloc_t *iap);
#endif /* _KERNEL */

#endif	/* _H_J2_IMAP */
