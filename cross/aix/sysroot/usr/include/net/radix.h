/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/net/radix.h 1.15                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)00	1.1  src/bos/kernel/net/radix.h, ipv6, ipv6 9/27/96 09:38:05 */
/* @(#)98       1.15  src/bos/kernel/net/radix.h, sysnet_route, bos53H, h2005_37B4 8/25/05 14:02:42 */
/*
 *   COMPONENT_NAME: SYSNET
 *
 *   FUNCTIONS: Bcmp
 *		Bcopy
 *		Bzero
 *		Free
 *		MKFree
 *		MKGet
 *		R_Malloc
 *		
 *
 *   ORIGINS: 27,85,127,196
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1997
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * 
 * (c) Copyright 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 * 
 */
/*
 * OSF/1 1.2
 */
/*
 * Copyright (c) 1988, 1989 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Base:	radix.h	7.3 (Berkeley) 4/22/89
 *	Merged:	radix.h	7.4 (Berkeley) 6/28/90
 *	Merged: radix.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _RADIX_H_
#define	_RADIX_H_

#ifndef __P
#define __P(s) s
#endif

/*
 * Radix search tree node layout.
 */

/*  Forward declaration for radix_mask - defect 364829 */
struct radix_mask;

struct radix_node {
	struct	radix_mask *rn_mklist;	/* list of masks contained in subtree */
	struct	radix_node *rn_p;	/* parent */
	short	rn_b;			/* bit offset; -1-index(netmask) */
	char	rn_bmask;		/* node: mask for bit test*/
	u_char	rn_flags;		/* enumerated next */
#define RNF_NORMAL	1		/* leaf contains normal route */
#define RNF_ROOT	2		/* leaf is root leaf for tree */
#define RNF_ACTIVE	4		/* This node is alive (for rtfree) */
/* This is not set if this is the only default route */
#define RNF_DUP		8		/* This is a duplicate route */
 
	union {
		struct {			/* leaf only data: */
			caddr_t	rn_Key;	/* object of search */
			caddr_t	rn_Mask;	/* netmask, if present */
			struct	radix_node *rn_Dupedkey;
		} rn_leaf;
		struct {			/* node only data: */
			int	rn_Off;		/* where to start compare */
			struct	radix_node *rn_L;/* progeny */
			struct	radix_node *rn_R;/* progeny */
		}rn_node;
	}		rn_u;
/* RN_DEBUG_REMOVED */
};

#define rn_dupedkey rn_u.rn_leaf.rn_Dupedkey
#define rn_key rn_u.rn_leaf.rn_Key
#define rn_mask rn_u.rn_leaf.rn_Mask
#define rn_off rn_u.rn_node.rn_Off
#define rn_l rn_u.rn_node.rn_L
#define rn_r rn_u.rn_node.rn_R

/*
 * Annotations to tree concerning potential routes applying to subtrees.
 */

extern struct radix_mask {
	short	rm_b;			/* bit offset; -1-index(netmask) */
	char	rm_unused;		/* cf. rn_bmask */
	u_char	rm_flags;		/* cf. rn_flags */
	struct	radix_mask *rm_mklist;	/* more masks to try */
	union	{
		caddr_t	rmu_mask;		/* the mask */
		struct	radix_node *rmu_leaf;	/* for normal routes */
	}	rm_rmu;
	int	rm_refs;		/* # of references to this struct */
} *rn_mkfreelist;

#define rm_mask rm_rmu.rmu_mask
#define rm_leaf rm_rmu.rmu_leaf		/* extra field would make 32 bytes */

#define MKGet(m) {\
	if (rn_mkfreelist) {\
		m = rn_mkfreelist; \
		rn_mkfreelist = (m)->rm_mklist; \
	} else \
		R_Malloc(m, struct radix_mask *, sizeof (*(m))); }\

#define MKFree(m) { (m)->rm_mklist = rn_mkfreelist; rn_mkfreelist = (m);}

struct rtreq_parm {
	ulong	flags; /* Currently unused: Will indicate if new parameters are passed */
	struct gidstruct *gidlist; /* Group routing information */
	struct ifnet *ifp; 
	__ulong32_t *cost;
	int policy; /* Specify routing policy for Multipath routing */
	int weight;	/* Weight associated with route - used for Weighted Round Robin */
};

struct radix_node_head {
	struct	radix_node *rnh_treetop;
	int	rnh_addrsize;		/* permit, but not require fixed keys */
	int	rnh_pktsize;		/* permit, but not require fixed keys */
	struct	radix_node *(*rnh_addaddr)	/* add based on sockaddr */
		__P((void *v, void *mask,
		     struct radix_node_head *head, struct radix_node nodes[], void *g, struct rtreq_parm *));
	struct	radix_node *(*rnh_addpkt)	/* add based on packet hdr */
		__P((void *v, void *mask,
		     struct radix_node_head *head, struct radix_node nodes[]));
	struct	radix_node *(*rnh_deladdr)	/* remove based on sockaddr */
		__P((void *v, void *mask, struct radix_node_head *head, struct gidstruct *gidlist, void *g, struct ifnet *ifp, __ulong32_t *cost));
	struct	radix_node *(*rnh_delpkt)	/* remove based on packet hdr */
		__P((void *v, void *mask, struct radix_node_head *head));
	struct	radix_node *(*rnh_matchaddr)	/* locate based on sockaddr */
		__P((void *v, struct radix_node_head *head, struct gidstruct *gidlist));
	struct	radix_node *(*rnh_lookup)	/* locate based on sockaddr */
		__P((void *v, void *mask, struct radix_node_head *head, struct gidstruct *gidlist));
	struct	radix_node *(*rnh_matchpkt)	/* locate based on packet hdr */
		__P((void *v, struct radix_node_head *head));
	int	(*rnh_walktree)			/* traverse tree */
		__P((struct radix_node_head *head, int (*f)(), void *w));
	struct	radix_node rnh_nodes[3];	/* empty tree for common case */
};


#ifndef _KERNEL
#define Bcmp(a, b, n) bcmp(((char *)(a)), ((char *)(b)), (n))
#define Bzero(p, n) bzero((char *)(p), (int)(n));
#define R_Malloc(p, t, n) (p = (t) malloc((unsigned int)(n)))
#define Free(p) free((char *)p);
#else
#define Bcmp(a, b, n) bcmp(((caddr_t)(a)), ((caddr_t)(b)), (unsigned)(n))
#define Bcopy(a, b, n) bcopy(((caddr_t)(a)), ((caddr_t)(b)), (unsigned)(n))
#define Bzero(p, n) bzero((caddr_t)(p), (unsigned)(n));
#define R_Malloc(p, t, n) NET_MALLOC(p, t, n, M_RTABLE, M_NOWAIT)
#define Free(p) NET_FREE(p, M_RTABLE);

#endif /* _KERNEL */

/* These flags are passed to rn_genmask to control its behavior. */
#define RN_EXACT 	0x00000001
#define RN_FIRST 	0x00000002
#define RN_NOMULTIPATH	0x00000004

/*
 * These flags are used for configuring the scheduling policy used
 * for Multipath Routing. Also defined in aix_misc.c (why?)
 */

#define MPR_LIMIT			5 /* Number of policies supported for "no"  */
#define MPR_DEFAULT 		0 /* Default value- user has not changed 	*/
#define MPR_WEIGHTED_RR 	1 /* Weighted Round Robin                   */
#define MPR_RANDOM      	2 /* Random selection                       */
#define	MPR_WEIGHTED_RANDOM 3 /* Weighted Random selection 			    */
#define MPR_LOW_UTIL    	4 /* Lowest Utilization of route            */
#define MPR_HASHED      	5 /* Hash based on IP addr & Port numbers   */
#define DEFAULT_WEIGHT	1 /* Default value of route weight			*/
#endif /* _RADIX_H_ */
