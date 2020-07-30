/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/j2/include/j2_btree.h 1.6                        */
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

/* @(#)79	1.6  src/bos/kernel/j2/include/j2_btree.h, sysj2, bos53H, h2006_03B9 1/8/06 21:39:14 */
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

#ifndef	_H_J2_BTREE
#define _H_J2_BTREE	
/*
 *	j2_btree.h: B+-tree
 *
 * J2 B+-tree (dtree and xtree) common definitions
 */

/*
 *	basic btree page - btpage_t
 */
typedef struct {
	int64		next;		/* 8: right sibling bn */
	int64		prev;		/* 8: left sibling bn */

	uint8		flag;		/* 1: */
	uint8		rsrvd[7];	/* 7: type specific */
	int64		self;		/* 8: self address */

	uint8		entry[4064];	/* 4064: */
} btpage_t;				/* (4096) */

/* btpaget_t flag */
#define BT_TYPE		0x07		/* B+-tree index */
#define	BT_ROOT		0x01		/* root page */
#define	BT_LEAF		0x02		/* leaf page */
#define	BT_INTERNAL	0x04		/* internal page */
#define	BT_RIGHTMOST	0x10		/* rightmost page */
#define	BT_LEFTMOST	0x20		/* leftmost page */

#define	MAXTREEHEIGHT		8

#ifdef	_KERNEL

#include <j2/j2_bufmgr.h>

/*
 *	btree page buffer cache access
 */
/* get page from buffer page */
#define BT_PAGE(IP, BP, TYPE)\
	(BP->pb_xflag & PB_BUFFER) ? (TYPE *)BP->pb_data : (TYPE *)&IP->i_btroot

/* get the page buffer and the page for specified block address */
#define BT_GETPAGE_CORE(IP, BN, BP, TYPE, SIZE, P, RC,FLAG)\
{\
	if ((BN) == 0)\
	{\
		BP = (jbuf_t *)&IP->i_bxflag;\
		P = (TYPE *)&IP->i_btroot;\
		RC = 0;\
	}\
	else\
	{\
		RC = bmRead(IP, (BN), (SIZE), FLAG, \
			    PBDT(TYPE), &(BP));  \
		if (RC == 0)\
			P = (TYPE *)BP->pb_data;\
	}\
}

/* get the page buffer and the page for specified block address */
#define BT_GETPAGE(IP, BN, BP, TYPE, SIZE, P, RC)\
        BT_GETPAGE_CORE(IP, BN, BP, TYPE, SIZE, P, RC,bmREAD_BLOCK)

#define BT_GETPAGE_RAW(IP, BN, BP, TYPE, SIZE, P, RC)\
        BT_GETPAGE_CORE(IP, BN, BP, TYPE, SIZE, P, RC,bmREAD_RAW)


/* put the page buffer */
#define BT_PUTPAGE(BP)\
{\
	if ((BP)->pb_xflag & PB_BUFFER)\
		bmRelease(BP);\
}


/*
 *	btree traversal/recovery stack
 *
 * record the path traversed during the search;
 * top frame record the leaf page/entry selected.
 *
 * record recovery information during update
 * traversing up the path of the target leaf;
 */
typedef struct btframe {	/* stack frame */
	int64	bn;		/* */
	int16	index;		/* */
	int16	lastindex;	/* */
	jbuf_t	*bp;		/* */
} btframe_t;			/* */

typedef struct btstack {
	btframe_t	*top;	/* traversal tree grows from low to high */
	int32		nsplit;	/* */
	btframe_t	stack[MAXTREEHEIGHT+1];
	btframe_t	*bottom;	/* recovery tree grows from high to low */
} btstack_t;

#define BT_CLR(btstack)\
{\
	(btstack)->top = (btstack)->stack;\
	(btstack)->bottom = &(btstack)->stack[MAXTREEHEIGHT];\
}

#define BT_PUSH(BTSTACK, BN, INDEX)\
{\
	(BTSTACK)->top->bn = BN;\
	(BTSTACK)->top->index = INDEX;\
	++(BTSTACK)->top;\
}

#define RT_PUSH(BTSTACK, BP, INDEX, LV)\
{\
	(BTSTACK)->bottom->bp = BP;\
	(BTSTACK)->bottom->index = INDEX;\
	(BTSTACK)->bottom->lastindex = LV;\
	--(BTSTACK)->bottom;\
}

#define BT_POP(btstack)\
	( (btstack)->top == (btstack)->stack ? NULL : --(btstack)->top )

#define RT_POP(btstack)\
	( (btstack)->bottom == &(btstack)->stack[MAXTREEHEIGHT] ? NULL : ++(btstack)->bottom )

#define BT_STACK(btstack)\
	( (btstack)->top == (btstack)->stack ? NULL : (btstack)->top )

/* retrieve search results */
#define BT_GETSEARCH(IP, LEAF, BN, BP, TYPE, P, INDEX)\
{\
	BN = (LEAF)->bn;\
	BP = (LEAF)->bp;\
	if (BN)\
		P = (TYPE *)BP->pb_data;\
	else\
		P = (TYPE *)&IP->i_btroot;\
	INDEX = (LEAF)->index;\
}

/* put the page buffer of search */
#define BT_PUTSEARCH(BTSTACK)\
{\
	if ((BTSTACK)->top->bp->pb_xflag & PB_BUFFER)\
		bmRelease((BTSTACK)->top->bp);\
}
#endif	/* _KERNEL */

#endif /* _H_J2_BTREE */
