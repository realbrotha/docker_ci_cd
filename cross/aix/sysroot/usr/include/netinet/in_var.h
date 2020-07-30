/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernext/inet/in_var.h 1.29                              */
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
/* @(#)50       1.29  src/bos/kernext/inet/in_var.h, sockinc, bos530 10/28/03 12:26:32 */
/*
 *   COMPONENT_NAME: SYSXINET
 *
 *   FUNCTIONS: IA_SIN
 *		IFP_TO_IA
 *		INADDR_TO_IFP
 *		INIFADDR_LOCKINIT
 *		INIFADDR_READ_LOCK
 *		INIFADDR_UNLOCK
 *		INIFADDR_WRITE_LOCK
 *		IN_FIRST_MULTI
 *		IN_LOOKUP_MULTI
 *		IN_LOOKUP_MULTI_NOLOCK
 *		IN_NEXT_MULTI
 *		UNLOCK_LAST_MULTI
 *		
 *
 *   ORIGINS: 26,27,85,89,127,196
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
 * Copyright (c) 1985, 1986 Regents of the University of California.
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
 *	Base:	in_var.h	7.4 (Berkeley) 4/22/89
 *	Merged:	in_var.h	7.6 (Berkeley) 6/28/90
 */

#ifndef _IN_VAR_H_
#define _IN_VAR_H_

/* We start with the hash chain infrastructure to manipulte
 * the interface address structure linked list as an array
 * of hashed entries
 */

struct inifaddr_hash {
        struct inifaddr_hash       *next;
        struct inifaddr_hash       *prev;
};

#define iahashtoinifaddr(hp)         \
        (struct in_ifaddr *)((char *)(hp) - offsetof(struct in_ifaddr, ia_hash))
#define inifaddrtohash(ia)        (&(ia->ia_hash))
#define INIFADDR_HASHSZ            29

#define INIFADDR_HASH(addr) ((addr) % INIFADDR_HASHSZ)

struct inifaddr_hash_table {
        struct inifaddr_hash	head;
};

extern struct inifaddr_hash_table inifaddr_hash_table[INIFADDR_HASHSZ];

/* Hash table chain head lock */
#if     defined(_KERNEL)
extern  struct	rw_lock      *inifaddr_hashchn_lock[INIFADDR_HASHSZ];
#endif

#define NET_CACHELINESIZE       128
/*
 * Including net_globals.h (where NET_CACHELINESIZE is defined) breaks nfs.
 * Hence we redefine NET_CACHELINESIZE here. These should be kept consistent.
 * This is also defined in route.h & in_pbc.h (because of build breaks
 * encountered when included through net_globals.h).
 */

/*
 * Interface address, Internet version.  One of these structures
 * is allocated for each interface with an Internet address.
 * The ifaddr structure contains the protocol-independent part
 * of the structure and is assumed to be first.
 */
struct in_ifaddr {
	struct	ifaddr ia_ifa;		/* protocol-independent info */
#define	ia_ifp		ia_ifa.ifa_ifp
#define ia_flags	ia_ifa.ifa_flags
					/* ia_{,sub}net{,mask} in host order */
	u_long	ia_net;			/* network number of interface */
	u_long	ia_netmask;		/* mask of net part */
	u_long	ia_subnet;		/* subnet number, including net */
	u_long	ia_subnetmask;		/* mask of subnet part */
	struct	in_addr ia_netbroadcast; /* to recognize net broadcasts */
	struct	in_ifaddr *ia_next;	/* next in list of internet addresses */
	struct	sockaddr_in ia_addr;	/* reserve space for interface name */
	struct	sockaddr_in ia_dstaddr; /* reserve space for broadcast addr */
#define	ia_broadaddr	ia_dstaddr
	struct	sockaddr_in ia_sockmask; /* reserve space for general netmask */
        struct 	inifaddr_hash ia_hash;  /* hash links                   */
};

struct	in_aliasreq {
	char	ifra_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr_in ifra_addr;
	struct	sockaddr_in ifra_broadaddr;
#define ifra_dstaddr ifra_broadaddr
	struct	sockaddr_in ifra_mask;
};
/*
 * Given a pointer to an in_ifaddr (ifaddr),
 * return a pointer to the addr as a sockaddr_in.
 */
#define	IA_SIN(ia) (&(((struct in_ifaddr *)(ia))->ia_addr))

#ifdef	_KERNEL
#define INIFADDR_HASHCHNHEAD_LOCKINIT(index) \
	RW_LOCKINIT(inifaddr_hashchn_lock[index], 2*NET_CACHELINESIZE, M_LOCKF, M_WAITOK, LOCK_ALLOC_PIN, \
	INIFADDR_LOCK_FAMILY, -1);
#define INIFADDR_HASHCHNHEAD_LOCK_DECL()	int	_inifl_h, _inifrl_h;
#define INIFADDR_HASHCHNHEAD_WRITE_LOCK(index) RW_WRITE_LOCK(inifaddr_hashchn_lock[index], _inifl_h, PL_IMP)
#define INIFADDR_HASHCHNHEAD_WRITE_UNLOCK(index) RW_WRITE_UNLOCK(inifaddr_hashchn_lock[index], _inifl_h)
#define INIFADDR_HASHCHNHEAD_READ_LOCK(index) \
	RW_READ_LOCK(inifaddr_hashchn_lock[index], _inifl_h, PL_IMP, _inifrl_h)
#define INIFADDR_HASHCHNHEAD_READ_UNLOCK(index) RW_READ_UNLOCK(inifaddr_hashchn_lock[index], _inifrl_h)
#endif


#ifdef	_KERNEL
extern  struct rw_lock *inifaddr_lock;
#define INIFADDR_LOCKINIT() \
	RW_LOCKINIT(inifaddr_lock, 2*NET_CACHELINESIZE, M_LOCKF, M_WAITOK, LOCK_ALLOC_PIN, \
	INIFADDR_LOCK_FAMILY, -1);
#define INIFADDR_LOCK_DECL()	int	_inifl, _inifrl;
#define INIFADDR_WRITE_LOCK() RW_WRITE_LOCK(inifaddr_lock, _inifl, PL_IMP)
#define INIFADDR_WRITE_UNLOCK() RW_WRITE_UNLOCK(inifaddr_lock, _inifl)
#define INIFADDR_READ_LOCK() \
	RW_READ_LOCK(inifaddr_lock, _inifl, PL_IMP, _inifrl)
#define INIFADDR_READ_UNLOCK() RW_READ_UNLOCK(inifaddr_lock, _inifrl)
extern	struct domain inetdomain;
extern	CONST struct protosw inetsw[];
extern	long inetprintfs;
extern	long ipforwarding;
extern	CONST	struct sockaddr_in in_zeroaddr;
extern	CONST	struct sockaddr_in6 in6_zeroaddr;
extern	struct	in_ifaddr *in_ifaddr;
extern	struct	ifqueue	ipintrq[IFQ_SIZE];	/* ip packet input queue */

#endif
#ifdef IP_MULTICAST
/*
 * Internet multicast address structure.  There is one of these for each IP
 * multicast group to which this host belongs on a given network interface.
 * They are kept in a linked list, rooted at the interface (struct ifnet)
 * structure.
 */
struct in_multi {
	struct in_addr	  inm_addr;	/* IP multicast address             */
	struct ifnet     *inm_ifp;	/* back pointer to ifnet            */
	u_int		  inm_refcount;	/* no. membership claims by sockets */
	u_int		  inm_timer;	/* IGMP membership report timer     */
	struct in_multi  *inm_next;	/* ptr to next multicast address    */
	u_int	inm_state;		/*  state of the membership */
	struct	router_info *inm_rti;	/* router info*/
};

#ifdef _KERNEL
/*
 * Macro for finding the interface (ifnet structure) corresponding to one
 * of our IP addresses.
 */
#define INADDR_TO_IFP(addr, ifp)                                             \
        /* struct in_addr addr; */                                           \
        /* struct ifnet  *ifp;  */                                           \
{                                                                            \
        register struct in_ifaddr *ia;                                       \
        struct inifaddr_hash *hp;                                            \
        struct inifaddr_hash_table *tablep;                                  \
        int index;                                                           \
        INIFADDR_HASHCHNHEAD_LOCK_DECL()                                     \
	ifp = NULL;                                                          \
                                                                             \
        index = INIFADDR_HASH((addr).s_addr);                                \
        INIFADDR_HASHCHNHEAD_READ_LOCK(index);                               \
                                                                             \
        tablep = &inifaddr_hash_table[index];                                \
        for (hp = tablep->head.next; hp != &(tablep->head); hp = hp->next) { \
                ia = iahashtoinifaddr(hp);                                   \
                if (IA_SIN(ia)->sin_addr.s_addr == (addr).s_addr){           \
        		(ifp) = ia->ia_ifp;                                  \
                        break;                                               \
		}                                                            \
        }                                                                    \
                                                                             \
        INIFADDR_HASHCHNHEAD_READ_UNLOCK(index);                             \
                                                                             \
}

/*
 * Macro for finding the internet address structure (in_ifaddr) corresponding
 * to a given interface (ifnet structure).
 */
#define IFP_TO_IA(ifp, ia)                                                \
        /* struct ifnet     *ifp; */                                      \
        /* struct in_ifaddr *ia;  */                                      \
{                                                                         \
       struct inifaddr_hash *hp, *hphead;                                 \
       int index;                                                         \
       INIFADDR_HASHCHNHEAD_LOCK_DECL()                                   \
									  \
       ia = NULL;                                                         \
       for(index = 0; index < INIFADDR_HASHSZ; index++) {                 \
             if (inifaddr_hash_table[index].head.next !=                  \
                  &(inifaddr_hash_table[index].head)) {                   \
                    INIFADDR_HASHCHNHEAD_READ_LOCK(index);                \
                    hphead = &(inifaddr_hash_table[index].head);          \
                    hp = hphead->next;                                    \
                    if ((hp != hphead) && hp) {                           \
                             for(; hp != hphead; hp = hp->next) {         \
                                    (ia) = iahashtoinifaddr(hp);          \
                                    if ((ia)->ia_ifp == (ifp)) {          \
                                         INIFADDR_HASHCHNHEAD_READ_UNLOCK(index);   \
                                         break;                           \
                                    }                                     \
                              } /* hash chain for loop */                 \
                    }                                                     \
		    if ((ia) && (ia)->ia_ifp == (ifp))                    \
			     break;					  \
                    INIFADDR_HASHCHNHEAD_READ_UNLOCK(index);              \
               } /* if test for inifaddrs in this chain */                \
       } /* index for loop */                                             \
       if ((ia) && (ia)->ia_ifp != (ifp))                                 \
       		ia = 0;                                                   \
}

/*
 * This information should be part of the ifnet structure but we don't wish
 * to change that - as it might break a number of things
 */

struct router_info {
	struct ifnet *ifp;
	int    type; /* type of router which is querier on this interface */
	int    time; /* # of slow timeouts since last old query */
	struct router_info *next;
};

/*
 * Structure used by macros below to remember position when stepping through
 * all of the in_multi records.
 */
struct in_multistep {
	struct ifnet     *i_if;
	struct ifnet     *i_lastif;
	struct in_multi  *i_inm;
};

/*
 * Macro for looking up the in_multi record for a given IP multicast address
 * on a given interface.  If no matching record is found, "inm" returns NULL.
 */
#define IN_LOOKUP_MULTI(addr, ifp, inm)					    \
	/* struct in_addr  addr; */					    \
	/* struct ifnet    *ifp; */					    \
	/* struct in_multi *inm; */					    \
{									    \
	    IFMULTI_LOCK(ifp);						    \
	    for ((inm) = ifp->if_multiaddrs;				    \
		 (inm) != NULL && (inm)->inm_addr.s_addr != (addr).s_addr;  \
		 (inm) = inm->inm_next);				    \
	    IFMULTI_UNLOCK(ifp);					    \
}

#define IN_LOOKUP_MULTI_NOLOCK(addr, ifp, inm)				    \
	/* struct in_addr  addr; */					    \
	/* struct ifnet    *ifp; */					    \
	/* struct in_multi *inm; */					    \
{									    \
	    for ((inm) = ifp->if_multiaddrs;				    \
		 (inm) != NULL && (inm)->inm_addr.s_addr != (addr).s_addr;  \
		 (inm) = inm->inm_next);				    \
}


#define UNLOCK_LAST_MULTI(step)						\
       if((step).i_lastif) IFMULTI_UNLOCK_RECURSIVE((step).i_lastif)

/*
 * Macro to step through all of the in_multi records, one at a time.
 * The current position is remembered in "step", which the caller must
 * provide.  IN_FIRST_MULTI(), below, must be called to initialize "step"
 * and get the first record.  Both macros return a NULL "inm" when there
 * are no remaining records.
 */
#define IN_NEXT_MULTI(step, inm)					\
	/* struct in_multistep  step; */				\
	/* struct in_multi     *inm;  */				\
{									\
	if (((inm) = (step).i_inm) != NULL) {				\
		(step).i_inm = (inm)->inm_next;				\
	}								\
	else while ((step).i_if != NULL) {				\
		UNLOCK_LAST_MULTI(step);				\
		IFMULTI_LOCK_RECURSIVE((step).i_if);			\
		(inm) = (step).i_if->if_multiaddrs;			\
		(step).i_lastif = (step).i_if;				\
		(step).i_if = (step).i_if->if_next;			\
		if ((inm) != NULL) {					\
			(step).i_inm = (inm)->inm_next;			\
			break;						\
		}							\
	}								\
}


#define IN_FIRST_MULTI(step, inm)					\
	/* struct in_multistep  step; */				\
	/* struct in_multi     *inm;  */				\
{									\
	(step).i_if  = ifnet;		                                \
	(step).i_inm = NULL;						\
	(step).i_lastif = NULL;						\
	IN_NEXT_MULTI((step), (inm));					\
}

struct in_multi *in_addmulti();
#endif /* _KERNEL */
#endif /* IP_MULTICAST */

#define INADDR_HASHSZ   229
#define INADDR_HASH2(addr) ((addr) % INADDR_HASHSZ)

struct in_addr_hash {
        struct in_addr_hash *iah_nxt;
        struct in_addr iah_ia;
        struct ifnet *iah_ifp;
        int iah_flags;
};

extern struct in_addr_hash *in_addr_hash_table[INADDR_HASHSZ];
extern simple_lock_data_t in_addr_hash_lock[NET_CACHELINESIZE / sizeof(simple_lock_data_t)];

/* flags for in_addr_hash */
#define IAH_VALID       0x1
#define IAH_BROADCAST   0x2

#define INADDR_HASH_LOCK_DECL() int _iahl;
#define INADDR_HASH_LOCK_INIT() { \
        lock_alloc(in_addr_hash_lock, \
        LOCK_ALLOC_PIN, INADDR_HASH_LOCK_FAMILY, -1); \
        simple_lock_init(in_addr_hash_lock); \
}

#define INADDR_HASH_READ_LOCK()
#define INADDR_HASH_WRITE_LOCK() _iahl = disable_lock(PL_IMP, \
        in_addr_hash_lock)
#define INADDR_HASH_READ_UNLOCK()
#define INADDR_HASH_WRITE_UNLOCK() unlock_enable(_iahl, \
        in_addr_hash_lock)
#endif /* _IN_VAR_H_ */
