/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/j2/include/j2_dtree.h 1.16.1.2                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1999,2010              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)87       1.16.1.2  src/bos/kernel/j2/include/j2_dtree.h, sysj2, bos53X, x2010_50A9 10/20/10 17:34:40 */
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

#ifndef _H_J2_DTREE
#define	_H_J2_DTREE

/*
 *	j2_dtree.h: directory B+-tree manager
 */

#define	_H_JFS_DIR	/* AIX: exclude native jfs/dir.h */
#include <sys/dir.h>	/* AIX: for struct dirent */
#include <j2/j2_btree.h>

typedef union {
        ino64_t ino;
        pxd_t   xd;
} ddata_t;


/*
 *      entry segment/slot
 *
 * an entry consists of type dependent head/only segment/slot and
 * additional segments/slots linked via next field;
 * N.B. last/only segment of entry is terminated by next = -1;
 */
/*
 *	directory page slot
 */
typedef struct {
	int8	next;		/* 1: */
	int8	cnt;		/* 1: */
	char	name[30];	/* 30: */
} dtslot_t;			/* (32) */

#define	DTSLOTSIZE	32
#define	L2DTSLOTSIZE	5
#define DTSLOTHDRSIZE	2
#define DTSLOTDATASIZE	30
#define DTSLOTDATALEN	30

/*
 * special entry prototype
 */
/* for consistency */
#define DT_PUTPAGE(BP) BT_PUTPAGE(BP)

/* get page buffer for specified block address */
#define DT_GETPAGE(IP, BN, BP, TYPE, SIZE, P, RC)\
{\
        BT_GETPAGE(IP, BN, BP, TYPE, SIZE, P, RC)\
        if (!(RC))\
        {\
                if (((P)->header.nextindex > (((BN)==0) ? DTROOTMAXSLOT\
                                                        : (P)->header.maxslot))\
                || ((BN) && ((P)->header.maxslot > DTPAGEMAXSLOT)))\
                {\
                        BT_PUTPAGE(BP);\
                        markFilesystemException((IP)->i_ipmnt, FM_FSERROR, ECORRUPT);\
                        RC = ECORRUPT;\
                }\
        }\
}

/*
 *	 internal node entry head/only segment
 */
typedef struct {
	union
	{
		pxd_t	xd;	/* 8: internal node: child extent descriptor */
		ino64_t inumber;/* 8: leaf node: 4-byte aligned inode number*/	 
	};
	int8	next;		/* 1: */
	uint8	namlen;		/* 1: */
	char	name[22];	/* 22: 2-byte aligned */
} dtentry_t;			/* (32) */

/*
 * Note: The code uses idtentry_t and ldtentry in places where it
 * expects the segment to be a particular type, otherwise it uses
 * dtentry_t for a generic type.
 */
typedef dtentry_t idtentry_t;
typedef dtentry_t ldtentry_t;

#define DTHDRSIZE	10
#define DTHDRDATALEN	22

#define DTIHDRSIZE	DTHDRSIZE
#define DTLHDRSIZE	DTHDRSIZE
#define DTIHDRDATALEN	DTHDRDATALEN
#define DTLHDRDATALEN	DTHDRDATALEN

/* compute number of slots for entry */
#define	NDTSLOT(klen)	((DTSLOTDATALEN + (klen) + sizeof(ino64_t) - 1) / DTSLOTDATALEN)

/*
 *	directory root page (in-line in on-disk inode):
 *
 * cf. dtpage_t below.
 */
typedef union {
	struct {
		ino64_t	idotdot;	/* 8: parent inode number */
		int64	rsrvd1;		/* 8: */

		uint8	flag;		/* 1: */
		int8	nextindex;	/* 1: next free entry in stbl */
		int8	freecnt;	/* 1: free count */
		int8	freelist;	/* 1: freelist header */
		int32	rsrvd2;		/* 4: */
		int8	stbl[8];	/* 8: sorted entry index table */
	} header;			/* (32) */

	dtslot_t	slot[9];
} dtroot_t;

#define DTROOTMAXSLOT	9

#define	dtEmpty(IP)	( ((dtroot_t *)&(IP)->i_btroot)->header.nextindex == 0 \
					? 0 : EEXIST)

/*
 *	directory regular page:
 *
 *	entry slot array of 32 byte slot
 *
 * sorted entry slot index table (stbl):
 * contiguous slots at slot specified by stblindex,
 * 1-byte per entry
 *   512 byte block:  16 entry tbl (1 slot)
 *  1024 byte block:  32 entry tbl (1 slot)
 *  2048 byte block:  64 entry tbl (2 slot)
 *  4096 byte block: 128 entry tbl (4 slot)
 *
 * data area:
 *   512 byte block:  16 - 2 =  14 slot
 *  1024 byte block:  32 - 2 =  30 slot
 *  2048 byte block:  64 - 3 =  61 slot
 *  4096 byte block: 128 - 5 = 123 slot
 *
 * N.B. index is 0-based; index fields refer to slot index
 * except nextindex which refers to entry index in stbl;
 * end of entry stot list or freelist is marked with -1.
 */
typedef union {
	struct {
		int64	next;		/* 8: next sibling */
		int64	prev;		/* 8: previous sibling */

		uint8	flag;		/* 1: */
		int8	nextindex;	/* 1: next entry index in stbl */
		int8	freecnt;	/* 1: */
		int8	freelist;	/* 1: slot index of head of freelist */

		uint8	maxslot;	/* 1: number of slots in page slot[] */
		int8	stblindex;	/* 1: slot index of start of stbl */
		uint8	rsrvd[2];	/* 2: */

		pxd_t	self;		/* 8: self pxd */
	} header;			/* (32) */

	dtslot_t	slot[128];
} dtpage_t;

#define DTPAGEMAXSLOT        128

#define DT8THPGNODEBYTES     512
#define DT8THPGNODETSLOTS      1
#define DT8THPGNODESLOTS      16

#define DTQTRPGNODEBYTES    1024
#define DTQTRPGNODETSLOTS      1
#define DTQTRPGNODESLOTS      32

#define DTHALFPGNODEBYTES   2048
#define DTHALFPGNODETSLOTS     2
#define DTHALFPGNODESLOTS     64

#define DTFULLPGNODEBYTES   4096
#define DTFULLPGNODETSLOTS     4
#define DTFULLPGNODESLOTS    128

#define DTENTRYSTART	1

/* get sorted entry table of the page */
#define DT_GETSTBL(p) ( ((p)->header.flag & BT_ROOT) ?\
	((dtroot_t *)(p))->header.stbl : \
	(int8 *)&(p)->slot[(p)->header.stblindex] )


#ifdef	_KERNEL

#include <sys/libcsys.h>

/*
 * struct dirent (external directory entry format):
 *
 * external format of directory entry used by readdir() is defined by
 * struct dirent in <sys/dir.h>.
 * struct dirent requires name (d_name) terminated with NULL.
 *
 * XPG4.2 include file serial number (d_ino, i.e., inode number) field.
 * also, it restricts that the number of 'bytes' (not characters)
 * preceding the terminating null byte will not exceed NAME_MAX.
 */

/* compute struct dirent size to cover namlen with terminating NULL,
 * rounded up to correct alignment boundary for 32 bit or 64 bit dirents:
 */
#define DIRENTSIZ(namlen) \
	( ((ureg_t)(((struct dirent *)0)->d_name) + ((namlen)+1) \
		+ sizeof(ino_t)-1) & ~(sizeof(ino_t)-1) )

typedef struct {
        uint32 pn;
	uint32 abspn;
        uint32 index;
} dtoffset_t;

/*
 * Cookie form:
 * pn     :25
 * index  :7
 */

#define DTDOTDOTCOOKIE		(1 << 7)
#define DTFIRSTCOOKIE		(2 << 7)
#define DTEOFCOOKIE		(3 << 7)
#define DTOVERFLOWCOOKIE	(4 << 7)

/* dtCookieToRelative translates a readdir cookie
 * into an absolute (page number, index) form.
 */
static _inline void dtCookieToRelative(uint32 cookie, dtoffset_t *real)
{
	real->pn = cookie >> 7;
	real->index = cookie & ((1<<7)-1);
}

/* dtRelativeToCookie does just about the opposite, but use pn,index
 * so the dtoffset doesn't have to be reconstucted
 */
static _inline uint32 dtRelativeToCookie(uint32 pn, uint32 index)
{
	return (pn << 7) | index;
}

/* DTMAXABSPN doesn't represent the maximum cookie page number.  It
 * represents the maxmimum page number after i_delTreePages is taken
 * into account, for wraparound purposes.  It also essentially
 * represents the largest directory tree that readdir can easily
 * handle (in leaf pages).
 */
#define DTMAXABSPN	(1 << 24)
#define DTMAXCOOKIEPN	(1 << 25)


/* dtMoveNameSlots:
 *
 *   Given dtree page "dtpage" and slot pointer "slot", move the name
 *   and continuations from slot into "buf". Assumes buf is large
 *   enough! NULL terminates buf.
 */
static __inline int dtMoveNameSlots(
	dtpage_t	*dtpage,
	ldtentry_t	*dtentry,
	char		*buf)
{
	int32 namlen, len, next, rc = 0;
	dtslot_t *dtslot;

	namlen = dtentry->namlen;

	/* not a valid entry name len */
	if (!namlen || namlen > J2_NAME_MAX)
		return ECORRUPT;
	
	/* copy the name of head/only segment */
	len = MIN(namlen, DTLHDRDATALEN);
	bcopy(dtentry->name, buf, len);

	buf += len;
	namlen -= len;

	next = dtentry->next;
	while (next >= 0)
	{
		if (namlen > 0)
		{

			dtslot = (dtslot_t *)&dtpage->slot[next];

			len = MIN(namlen, DTSLOTDATALEN);
			bcopy(dtslot->name, buf, len);

			buf += len;
			namlen -= len;

			next = dtslot->next;
		}
		else {
			rc = ECORRUPT; /* too many slots for name */
			break;
		}
	}

	if (namlen)
		rc = ECORRUPT; /* incorrect number of slots for name */

	buf[0] = '\0';

	return rc;
}


/*
 *	dtGetKey()
 *
 * function: get key of the entry
 */
static __inline int dtGetKey(
	dtpage_t	*p,
	int32		i,	/* entry index */
	component_t	*key)
{
	int32		si;
	int8		*stbl;
	ldtentry_t	*lh;

	/* get entry */
	stbl = DT_GETSTBL(p);
	si = stbl[i];

	lh = (ldtentry_t *)&p->slot[si];

	key->namlen = lh->namlen;

	return dtMoveNameSlots(p, lh, key->name);
}


/*
 *	external declarations
 */
void dtInitRoot(
	int32	tid,
	inode_t	*ip,
	ino64_t	idotdot);

int32 dtSearch(
	inode_t		*ip,
	component_t	*key,
	ino64_t		*data,
	btstack_t	*btstack,
	uint32		flag);

int32 dtInsert(
	int32		tid,
	inode_t		*ip,
	component_t 	*key,
	ino64_t		*ino,
	btstack_t	*btstack);

int32 dtDelete(
	int32		tid,
	inode_t		*ip,
	component_t	*key,
	ino64_t		*data,
	uint32 		flag);

int32 dtRelocateDirectory(int32 tid, inode_t *ip, int64 xfence,
	int64 *nBlockToMove, int64 *nBlockMoved);

int32 dtRelocateExtent(int32 tid, inode_t *ip, int64 key,
	pxd_t *spxd, int64 dxaddr);

int32 dtModify(
	int32		tid,
	inode_t		*ip,
	component_t	*key,
	ino64_t		*orig_ino,
	ino64_t		new_ino,
	uint32 		flag);

void dtModifyParent(
	int32           tid,
	inode_t         *ip,
	ino64_t         newparent);

int32 dtRead(
	inode_t		*ip,
	int32		*offset,
	int32		ubytes,
	int32		*tbytes,
	struct dirent	*tdp);

int32 dtReadSort(
	inode_t		*ip,
	int32		*offset,
	int32		ubytes,
	int32		*tbytes,
	struct dirent	*last_read,
	struct dirent	*tdp);

int32 dtReadFirst(
        inode_t         *ip,
        btstack_t       *btstack);

int32 dtReadNext(
        inode_t         *ip,
        dtoffset_t      *dtoffset,
        btstack_t       *btstack);

#ifdef  _J2_DEBUG
int32 dtDisplayTree(
        inode_t         *ip);

int32 dtDisplayPage(
        inode_t         *ip,
        int64           bn,
        dtpage_t        *p);
#endif  /* _J2_DEBUG */
#endif  /* _KERNEL */

#endif /* !_H_J2_DTREE */
