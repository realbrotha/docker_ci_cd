/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/j2/include/j2_xtree.h 1.25                       */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)01       1.25  src/bos/kernel/j2/include/j2_xtree.h, sysj2, bos53H, h2006_09B5 2/23/06 14:25:27 */
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

#ifndef _H_J2_XTREE
#define	_H_J2_XTREE
/*
 * FUNCTION: extent allocation descriptor B+-tree manager
 */

#include <j2/j2_btree.h>

/* xad is defined in j2_types.h */

/* xad list */
typedef struct {
	int16	maxnxad;
	int16	nxad;
	xad_t	*xad;
} xadlist_t;


/* possible values for maxentry */
#define	XTROOTMAXSLOT	18
#define	XTPAGEMAXSLOT	256
#define	XTENTRYSTART	2

/*
 *	xtree page:
 */
typedef union {
	struct xtheader {
		int64	next;		/* 8: */
		int64	prev;		/* 8: */

		uint8	flag;		/* 1: */
		uint8	rsrvd1;		/* 1: */
		int16	nextindex;	/* 2: next index = # of entries */
		int16	maxentry;	/* 2: max number of entries */
		int16	rsrvd2;		/* 2: */

		pxd_t	self;		/* 8: self */
	} header;				/* (32) */

	xad_t		xad[XTPAGEMAXSLOT];	/* 16 * maxentry: xad array */
} xtpage_t;

#ifdef	_KERNEL
/*
 *	external declaration
 */
extern int32 xtLookup(
	inode_t		*ip,
	int64 		lstart,
	int32		llen,
	uint32		*pflag,
	int64		*paddr,
	int32		*plen,
	uint32		flag);

void xtInitRoot(
	int32		tid,
	inode_t		*ip);

extern int32 xtInsert(
	int32		tid,
	inode_t		*ip,
	uint8		xflag,
	int64		xoff,
	int32		xlen,
	int64		*xaddrp,
	uint32		flag);

extern int32 xtExtend(
	int32		tid,
	inode_t		*ip,
	int64		xoff,
	int32		xlen,
	uint32		flag);

extern int32 xtTailgate(
	int32		tid,
	inode_t		*ip,
	int64		xoff,
	int32		xlen,
	int64		xaddr,
	uint32		flag);

extern xtUpdate(
	int32		tid,
	inode_t		*ip,
	struct xad	*nxad,
	struct xad	*oxad);

extern int32 xtTruncate(
	int32		tid,
	inode_t		*ip,
	int64		newsize,
	int32		type,
	void		*lrd);

extern int32 xtClear(
	int32		tid,
	inode_t		*ip, 
	int64		offset,
	int64   	nbytes,
	int32		commitType);

extern int32 xtRelocateFile(int32 tid, inode_t *ip, int64 xfence,
	int64 *nBlockToMove, int64 *nBlockMoved, struct ucred *crp);
extern int32 xtRelocateExtent(int32 tid, inode_t *ip, xad_t *sxad,
	int64 dxaddr, int32 xtype, struct ucred *crp);
extern int32 xtRelocate(int32 tid, inode_t *ip, int64 pbn,
	int32 index, int64 dxaddr, int32 xtype, struct ucred *crp);

extern int32 xtAppend(
	int32		tid,
	inode_t		*ip,
	uint8		xflag,
	int64		xoff,
	int64    nBlocks,
	int32		*xlenp,		/* (in/out) */
	int64		*xaddrp,	/* (in/out) */
	uint32		flag);

int32 xtGetMap(
	inode_t		*ip,
	uint32   	lstart,
	uint64    	*llen,
	struct uio	*uiop);

int32 xtUpdateRange(
	int32           tid,
	inode_t		*ip,
	uint64   	lstart,
	uint64    	*llen,
	uint32          newflag,
	uint32          newflagmask,
	boolean_t       forced,
	struct uio	*uiop,
	int             *err);

reg_t xtReserve(
	inode_t	*ip,
	int32	*nSplit,
	int32	*nXad);

void xtException(inode_t *_ip,
		 jbuf_t *_bp,
		 int32 _flag,
		 char *_file,
		 uint32 _line);

extern int32 xtFreeMap(int32 tid, inode_t *ip, int32 commitType);

reg_t xtValidatePage(inode_t *ip, int64 bn, xtpage_t *p, reg_t full);

#ifdef	_J2_DEBUG
int32	xtDisplayTree(inode_t *ip);
void	xtDisplayPage(inode_t *ip, int64 bn, xtpage_t *p, int *more);
#endif	/* _J2_DEBUG */

#ifdef DEBUG
#undef _J2_PARANOID_XTREE
#define _J2_PARANOID_XTREE 1
#endif

/* write a xad entry */
#ifdef _J2_PARANOID_XTREE
#define	XT_PUTENTRY(XAD, FLAG, OFF, LEN, ADDR)\
{\
	if ( (ADDR) == 0 ) \
		assert(0); \
	(XAD)->flag = (FLAG);\
	XADoffset((XAD), (OFF));\
	XADlength((XAD), (LEN));\
	XADaddress((XAD), (ADDR));\
}
#else
#define	XT_PUTENTRY(XAD, FLAG, OFF, LEN, ADDR)\
{\
	(XAD)->flag = (FLAG);\
	XADoffset((XAD), (OFF));\
	XADlength((XAD), (LEN));\
	XADaddress((XAD), (ADDR));\
}
#endif

/* Validate the page by either calling xtValidatePage
 * or just checking the header, depending on how
 * paranoid we are.
 */
static __inline int xtValidateThunk(inode_t	*ip,
				     int64	bn,
				     xtpage_t	*p,
				     reg_t	full)
{
#ifdef _J2_PARANOID_XTREE
	return xtValidatePage(ip, bn, p, 0);
#else
	if (p->header.nextindex < XTENTRYSTART)
		return 1;

	if (p->header.nextindex > p->header.maxentry)
		return 1;

	if (p->header.maxentry > ((bn==0)?
				  XTROOTMAXSLOT
				  :XTPAGEMAXSLOT))
		return 1;

	return 0;
#endif
}

#define XTEXCEPTION(IP, BP, FLAG) \
	xtException(IP, BP, FLAG, __FILE__, __LINE__);

/* get xtPage buffer for specified block address */
#define XT_GETPAGEF(IP, BN, BP, TYPE, SIZE, P, RC, FLAG)\
{\
	BT_GETPAGE_CORE(IP, BN, BP, TYPE, SIZE, P, RC, FLAG|bmREAD_BLOCK)\
	if (!(RC))\
	{\
		if (xtValidateThunk(IP, BN, P, 0))\
		{\
			if (CSA->prev != NULL) /* PAGER_VCS */ \
			{\
				BT_PUTPAGE(BP);\
				RC = -1; /* PAGER_VM_WAIT */ \
			}\
			else\
			{\
				XTEXCEPTION(IP, BP, 0);\
				BT_PUTPAGE(BP);\
				RC = ECORRUPT;\
			}\
		}\
	}\
}
#define XT_GETPAGE(IP, BN, BP, TYPE, SIZE, P, RC)\
	XT_GETPAGEF(IP, BN, BP, TYPE, SIZE, P, RC, 0)


/* release xtPage buffer */
#ifdef _J2_PARANOID_XTREE
_inline void XT_PUTPAGE(pbuf_t *bp)
{
	if (bp->pb_xflag & PB_BUFFER)
		xtValidatePage(bp->pb_ip, 1, (xtpage_t *) bp->pb_data, 0);
	else {
		inode_t *ip = (inode_t *) ((char *) bp - (reg_t) &((inode_t *) NULL)->i_bxflag);
		xtValidatePage(ip, 0, (xtpage_t *) &ip->i_btroot, 0);
	}
	BT_PUTPAGE(bp);
}
#else
#define XT_PUTPAGE(BP) BT_PUTPAGE(BP)
#endif


#endif	/* _KERNEL */

#endif /* !_H_J2_XTREE */
