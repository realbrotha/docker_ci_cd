/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernext/inet/in6_var.h 1.12                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)14	1.12  src/bos/kernext/inet/in6_var.h, sockinc, bos53L, l2006_50A8 11/22/06 10:41:53 */
/*	$NetBSD: in_var.h,v 1.8 1994/06/29 06:38:13 cgd Exp $	*/

/*
 * Copyright (c) 1985, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#ifndef _NETINET_IN6_VAR_H_
#define _NETINET_IN6_VAR_H_

#include <sys/queue.h>

#ifndef CONST
#define CONST const
#endif
extern	struct domain inet6domain;
extern	CONST struct protosw inet6sw[];

/* We start with the hash chain infrastructure to manipulte
 * the interface address structure linked list as an array
 * of hashed entries
 */

struct in6ifaddr_hash {
        struct in6ifaddr_hash       *next;
        struct in6ifaddr_hash       *prev;
};

#define ia6hashtoinifaddr(hp)         \
        (struct in6_ifaddr *)((char *)(hp) - offsetof(struct in6_ifaddr, ia_hash))
#define in6ifaddrtohash(ia)        (&(ia->ia_hash))
#define IN6IFADDR_HASHSZ            59

#define IN6IFADDR_HASH(addr) ((addr) % IN6IFADDR_HASHSZ)

struct in6ifaddr_hash_table {
        struct in6ifaddr_hash    head;
};

extern struct in6ifaddr_hash_table in6ifaddr_hash_table[IN6IFADDR_HASHSZ];

/* Hash table chain head lock */
#if     defined(_KERNEL)
extern  struct  rw_lock      *in6ifaddr_hashchn_lock[IN6IFADDR_HASHSZ];
#endif

#define NET_CACHELINESIZE       128
/*
 * Including net_globals.h (where NET_CACHELINESIZE is defined) breaks nfs.
 * Hence we redefine NET_CACHELINESIZE here. These should be kept consistent.
 * This is also defined in route.h, in_var.h & in_pbc.h (because of build breaks
 * encountered when included through net_globals.h).
 */

/*
 * Interface address, IPv6 version.  One of these structures
 * is allocated for each interface with an IPv6 address.
 * The ifaddr structure contains the protocol-independent part
 * of the structure and is assumed to be first.
 */
struct in6_ifaddr {
	struct	ifaddr ia_ifa;		/* protocol-independent info */
#define	ia_ifp		ia_ifa.ifa_ifp
#define ia_flags	ia_ifa.ifa_flags
	TAILQ_ENTRY(in6_ifaddr) ia_list; /* list of IPv6 addresses */
	struct	sockaddr_in6 ia_addr;	/* space for interface name */
	struct	sockaddr_in6 ia_dstaddr; /* space for broadcast addr */
	struct	sockaddr_in6 ia_sockmask; /* space for general netmask */
        struct  in6ifaddr_hash ia_hash;  /* hash links */
};

struct	in6_aliasreq {
	char	ifra_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr_in6 ifra_addr;
	struct	sockaddr_in6 ifra_dstaddr;
	struct	sockaddr_in6 ifra_mask;
};
/* in the sin6_flowinfo field of ifra_addr for SIOCAIFADDR6 */
#define IN6_ADDR_TENTATIVE  0xffffffff

struct in6_ifreq {
	char	ifr_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr_in6 ifr_Addr;
};

/*
 * Given a pointer to an in6_ifaddr (ifaddr),
 * return a pointer to the addr as a sockaddr_in6.
 */
#define	IA_SIN6(ia) (&(((struct in6_ifaddr *)(ia))->ia_addr))
#define	IA_DSTSIN6(ia) (&(((struct in6_ifaddr *)(ia))->ia_dstaddr))

#define SIOCSIFADDR6  (int)_IOW('i', 12, struct in6_ifreq)   /* set ifnet address */
#define SIOCGIFADDR6 (int)_IOWR('i', 33, struct in6_ifreq)   /* get ifnet address */
#define SIOCSIFDSTADDR6  (int)_IOW('i', 14, struct in6_ifreq)/* set p-p address */
#define SIOCGIFDSTADDR6 (int)_IOWR('i', 34, struct in6_ifreq)/* get p-p address */
#define SIOCSIFNETMASK6 (int)_IOW('i', 22, struct in6_ifreq) /* set net addr mask */
#define SIOCGIFNETMASK6 (int)_IOWR('i', 37, struct in6_ifreq)/* get net addr mask */

#define SIOCDIFADDR6  (int)_IOW('i', 25, struct in6_ifreq)   /* delete IF addr */
#define SIOCAIFADDR6  (int)_IOW('i', 26, struct in6_aliasreq)/* add/chg IF alias */
#define SIOCFIFADDR6  (int)_IOW('i', 39, struct in6_ifreq)   /* put IF addr in front */
#define SIOCVIFADDR6  (int)_IOW('i', 40, struct in6_aliasreq) /* does nothing */

#define SIOCGTUGADDR6 (int)_IOW('i', 41, struct in6_ifreq)   /* get TUG real addr */
#define SIOCSTUGADDR6 (int)_IOW('i', 42, struct in6_ifreq)   /* set TUG real addr */

#define SIOCADDANY6   (int)_IOW('i', 43, struct in6_ifreq)   /* add an anycast */
#define SIOCDELANY6   (int)_IOW('i', 44, struct in6_ifreq)   /* delete an anycast */

#define SIOCGIFSITE6  (int)_IOWR('i', 45, struct ifreq)  /* get ifnet site */
#define SIOCSIFSITE6  (int)_IOW('i', 46, struct ifreq)   /* set ifnet site */


#if defined(_KERNEL)

#define IN6IFADDR_HASHCHNHEAD_LOCKINIT(index) 								\
	RW_LOCKINIT(in6ifaddr_hashchn_lock[index], 2*NET_CACHELINESIZE, M_LOCKF, M_WAITOK, 		\
		LOCK_ALLOC_PIN, IN6IFADDR_LOCK_FAMILY, -1);
#define IN6IFADDR_HASHCHNHEAD_LOCK_DECL()      	  int	_in6ifl_h, _in6ifrl_h;
#define IN6IFADDR_HASHCHNHEAD_WRITE_LOCK(index)  							\
	RW_WRITE_LOCK(in6ifaddr_hashchn_lock[index], _in6ifl_h, PL_IMP)
#define IN6IFADDR_HASHCHNHEAD_READ_LOCK(index)   							\
	RW_READ_LOCK(in6ifaddr_hashchn_lock[index], _in6ifl_h, PL_IMP, _in6ifrl_h)
#define IN6IFADDR_HASHCHNHEAD_WRITE_UNLOCK(index)							\
	RW_WRITE_UNLOCK(in6ifaddr_hashchn_lock[index], _in6ifl_h)
#define IN6IFADDR_HASHCHNHEAD_READ_UNLOCK(index) 							\
	RW_READ_UNLOCK(in6ifaddr_hashchn_lock[index], _in6ifrl_h)


extern  simple_lock_data_t     in6ifaddr_lock;
#define IN6IFADDR_LOCKINIT()     {					\
	lock_alloc(&in6ifaddr_lock, LOCK_ALLOC_PIN, IN6IFADDR_LOCK_FAMILY, -1);\
	simple_lock_init(&in6ifaddr_lock);		\
}
#define IN6IFADDR_LOCK_DECL()	int	_in6ifl;
#define IN6IFADDR_WRITE_LOCK()   _in6ifl = disable_lock(PL_IMP, &in6ifaddr_lock)
#define IN6IFADDR_READ_LOCK()    _in6ifl = disable_lock(PL_IMP, &in6ifaddr_lock)
#define IN6IFADDR_UNLOCK()       unlock_enable(_in6ifl, &in6ifaddr_lock)

extern  simple_lock_data_t     flow6_lock;
#define FLOW6_LOCKINIT()     {					\
	lock_alloc(&flow6_lock, LOCK_ALLOC_PIN, FLOW6_LOCK_FAMILY, -1);\
	simple_lock_init(&flow6_lock);		\
}
#define FLOW6_LOCK_DECL()	int	_flow6l;
#define FLOW6_WRITE_LOCK()   _flow6l = disable_lock(PL_IMP, &flow6_lock)
#define FLOW6_READ_LOCK()    _flow6l = disable_lock(PL_IMP, &flow6_lock)
#define FLOW6_LOCK()    _flow6l = disable_lock(PL_IMP, &flow6_lock)
#define FLOW6_UNLOCK()       unlock_enable(_flow6l, &flow6_lock)

#define IN6ANYADDR_HASHCHNHEAD_LOCKINIT(index) {							\
	lock_alloc(&(in6anycast_hashchn_lock[index]._l), LOCK_ALLOC_PIN, IN6ANYA_LOCK_FAMILY, -1);   \
	simple_lock_init(&(in6anycast_hashchn_lock[index]._l));                                        \
}
#define IN6ANYADDR_HASHCHNHEAD_LOCK_DECL()      	  int	_in6anycast;
#define IN6ANYADDR_HASHCHNHEAD_WRITE_LOCK(index)  							\
	_in6anycast = disable_lock(PL_IMP, &(in6anycast_hashchn_lock[index]._l))
#define IN6ANYADDR_HASHCHNHEAD_READ_LOCK(index)   							\
	_in6anycast = disable_lock(PL_IMP, &(in6anycast_hashchn_lock[index]._l))
#define IN6ANYADDR_HASHCHNHEAD_WRITE_UNLOCK(index)							\
	unlock_enable(_in6anycast, &(in6anycast_hashchn_lock[index]._l))
#define IN6ANYADDR_HASHCHNHEAD_READ_UNLOCK(index) 							\
	unlock_enable(_in6anycast, &(in6anycast_hashchn_lock[index]._l))


extern  simple_lock_data_t     in6anyaddr_lock;
#define IN6ANYADDR_LOCKINIT()     {					\
	lock_alloc(&in6anyaddr_lock, LOCK_ALLOC_PIN, IN6ANYA_LOCK_FAMILY, -1);\
	simple_lock_init(&in6anyaddr_lock);		\
}
#define IN6ANYADDR_LOCK_DECL()	int	_in6ifl;
#define IN6ANYADDR_WRITE_LOCK()   _in6ifl = disable_lock(PL_IMP, &in6anyaddr_lock)
#define IN6ANYADDR_READ_LOCK()    _in6ifl = disable_lock(PL_IMP, &in6anyaddr_lock)
#define IN6ANYADDR_UNLOCK()       unlock_enable(_in6ifl, &in6anyaddr_lock)


TAILQ_HEAD(in6_ifaddrhead, in6_ifaddr);
extern  struct  in6_ifaddrhead in6_ifaddr;

extern LIST_HEAD(in6_anyhead, in6_anycast) in6_anyhead;

/*
 * Macro for finding the interface (ifnet structure) corresponding to one
 * of our IPv6 addresses.
 */
#define IN6ADDR_TO_IFP(addr, ifp) \
	/* struct in6_addr addr; */ \
	/* struct ifnet *ifp; */ \
{ \
	register struct in6_ifaddr *ia; \
        struct in6ifaddr_hash *hp;                                           \
        struct in6ifaddr_hash_table *tablep;                                 \
        int index;                                                           \
        IN6IFADDR_HASHCHNHEAD_LOCK_DECL()                                    \
        ifp = NULL;                                                          \
                                                                             \
        index = IN6IFADDR_HASH((addr).s6_addr32[3]);                         \
        IN6IFADDR_HASHCHNHEAD_READ_LOCK(index);                              \
        tablep = &in6ifaddr_hash_table[index];                               \
        for (hp = tablep->head.next; hp != &(tablep->head); hp = hp->next) { \
                ia = ia6hashtoinifaddr(hp);                                  \
                if (SAME_ADDR6(((ia->ia_ifp->if_flags & IFF_POINTOPOINT) ?   \
			IA_DSTSIN6(ia) : IA_SIN6(ia))->sin6_addr, addr)) {   \
                        (ifp) = ia->ia_ifp;                                  \
                        break;                                               \
                }                                                            \
        }                                                                    \
	if (ifp == NULL)                                                     \
          for (hp = tablep->head.next; hp != &(tablep->head); hp = hp->next) { \
                ia = ia6hashtoinifaddr(hp);                                  \
		if (ia->ia_ifp->if_flags & IFF_POINTOPOINT &&                \
		    SAME_ADDR6(IA_SIN6(ia)->sin6_addr, addr)) {              \
                        (ifp) = ia->ia_ifp;                                  \
                        break;                                               \
                }                                                            \
          }                                                                  \
                                                                             \
        IN6IFADDR_HASHCHNHEAD_READ_UNLOCK(index);                            \
}



/*
 * Macro for finding the IPv6 address structure (in6_ifaddr) corresponding
 * to a given interface (ifnet structure).
 */
#define IFP_TO_IA6(ifp, ia) \
	/* struct ifnet *ifp; */ \
	/* struct in6_ifaddr *ia; */ \
{ \
	struct in6ifaddr_hash *hp, *hphead; \
	int index; \
	IN6IFADDR_HASHCHNHEAD_LOCK_DECL() \
\
        for(index = 0; index < IN6IFADDR_HASHSZ; index++) {               \
             if (in6ifaddr_hash_table[index].head.next !=                 \
                  &(in6ifaddr_hash_table[index].head)) {                  \
                    IN6IFADDR_HASHCHNHEAD_READ_LOCK(index);               \
                    hphead = &(in6ifaddr_hash_table[index].head);         \
                    hp = hphead->next;                                    \
                    if ((hp != hphead) && hp) {                           \
                             for(; hp != hphead; hp = hp->next) {         \
                                    (ia) = ia6hashtoinifaddr(hp);         \
                                    if ((ia)->ia_ifp == (ifp)) {          \
                                         IN6IFADDR_HASHCHNHEAD_READ_UNLOCK(index);   \
                                         break;                           \
                                    }                                     \
                              } /* hash chain for loop */                 \
                    }                                                     \
                    if ((ia)->ia_ifp == (ifp))                            \
                             break;                                       \
                    IN6IFADDR_HASHCHNHEAD_READ_UNLOCK(index);             \
               } /* if test for inifaddrs in this chain */                \
        } /* index for loop */                                            \
        if (ia && (ia)->ia_ifp != (ifp))                                  \
                ia = 0;                                                   \
}
#endif


/*
 * IPv6 multicast address structure.  There is one of these for each IPv6
 * multicast group to which this host belongs on a given network interface.
 * They are kept in a linked list, rooted in the interface's in6_ifaddr
 * structure.
 */
struct in6_multi {
	LIST_ENTRY(in6_multi) inm6_entry; /* list glue */ 
	struct	in6_addr inm6_addr;	/* IPv6 multicast address */
	struct	ifnet *inm6_ifp;	/* back pointer to ifnet */
	u_int	inm6_refcount;		/* no. membership claims by sockets */
	u_int	inm6_timer;		/* ICMPv6 membership report timer */
	u_int	inm6_state;		/* state of the membership */
};

#define MULTI6_OTHERMEMBER		1
#define MULTI6_IREPORTEDLAST		2

#if defined(_KERNEL)

/*
 * Structure used by macros below to remember position when stepping through
 * all of the in6_multi records.
 */
struct in6_multistep {
	struct ifnet *i6_if;
	struct ifnet *i6_lastif;
	struct in6_multi *i6_inm;
};

/*
 * Macro for looking up the in6_multi record
 * for a given IPv6 multicast address on a given interface.
 * If no matching record is found, "inm" returns NULL.
 */
#define IN6_LOOKUP_MULTI(addr, ifp, inm) \
	/* struct in6_addr addr; */ \
	/* struct ifnet *ifp; */ \
	/* struct in6_multi *inm; */ \
{ \
	IF6MULTI_LOCK(ifp); \
	for ((inm) = ifp->if_multiaddrs6.lh_first; \
	    (inm) != NULL && !SAME_ADDR6((inm)->inm6_addr, (addr)); \
	     (inm) = inm->inm6_entry.le_next) \
		 continue; \
	IF6MULTI_UNLOCK(ifp); \
}

#define IN6_LOOKUP_MULTI_NOLOCK(addr, ifp, inm) \
	/* struct in6_addr addr; */ \
	/* struct ifnet *ifp; */ \
	/* struct in6_multi *inm; */ \
{ \
	for ((inm) = ifp->if_multiaddrs6.lh_first; \
	    (inm) != NULL && !SAME_ADDR6((inm)->inm6_addr, (addr)); \
	     (inm) = inm->inm6_entry.le_next) \
		 continue; \
}

#define UNLOCK_LAST_MULTI6(step) \
       if((step).i6_lastif) IF6MULTI_UNLOCK_RECURSIVE((step).i6_lastif)

/*
 * Macro to step through all of the in6_multi records, one at a time.
 * The current position is remembered in "step", which the caller must
 * provide.  IN6_FIRST_MULTI(), below, must be called to initialize "step"
 * and get the first record.  Both macros return a NULL "inm" when there
 * are no remaining records.
 */
#define IN6_NEXT_MULTI(step, inm) \
	/* struct in6_multistep  step; */ \
	/* struct in6_multi *inm; */ \
{ \
	if (((inm) = (step).i6_inm) != NULL) \
		(step).i6_inm = (inm)->inm6_entry.le_next; \
	else \
		while ((step).i6_if != NULL) { \
			UNLOCK_LAST_MULTI6(step); \
			IF6MULTI_LOCK_RECURSIVE((step).i6_if); \
			(inm) = (step).i6_if->if_multiaddrs6.lh_first; \
			(step).i6_lastif = (step).i6_if; \
			(step).i6_if = (step).i6_if->if_next; \
			if ((inm) != NULL) { \
				(step).i6_inm = (inm)->inm6_entry.le_next; \
				break; \
			} \
		} \
}

#define IN6_FIRST_MULTI(step, inm) \
	/* struct in6_multistep step; */ \
	/* struct in6_multi *inm; */ \
{ \
	(step).i6_if = ifnet; \
	(step).i6_inm = NULL; \
	(step).i6_lastif = NULL; \
	IN6_NEXT_MULTI((step), (inm)); \
}

#endif


/* hash chain structure ot enocde the ipv6 anycast addresses
 * in a linked list as well as an array of hashed entries
 */

struct in6anycast_hash {
        struct in6anycast_hash       *next;
        struct in6anycast_hash       *prev;
};

#define ia6hashtoanycast(hp)         \
        (struct in6_anycast *)((char *)(hp) - offsetof(struct in6_anycast, ia_hash))
#define in6anycasttohash(ia)        (&(ia->ia_hash))
#define IN6ANYADDR_HASHSZ            29

#define IN6ANYADDR_HASH(addr) ((addr) % IN6ANYADDR_HASHSZ)

struct in6anycast_hash_table {
        struct in6anycast_hash    head;
};

extern struct in6anycast_hash_table in6anycast_hash_table[IN6ANYADDR_HASHSZ];

struct aligned_in6anycast_lock {
	simple_lock_data_t	_l; 
	char			dummy[NET_CACHELINESIZE - sizeof(simple_lock_data_t)];
};

/* Hash table chain head lock */
#if     defined(_KERNEL)
extern  struct  aligned_in6anycast_lock      in6anycast_hashchn_lock[IN6ANYADDR_HASHSZ];
#endif


/*
 * Anycast address structure.
 */

struct in6_anycast {
#ifdef _KERNEL
    LIST_ENTRY(in6_anycast) ina6_list;  /* list glue */
#endif
    struct  in6_addr ina6_addr; /* IPv6 anycast address */
    u_int   ina6_refcount;      /* reference count */
    u_int   ina6_flags;         /* flags */
    struct  in6anycast_hash ia_hash;  /* hash links */
};
#define IP6ANY_VALID        1       /* valid entry */
#define IP6ANY_ROUTER       2       /* router anycast */
#define IP6ANY_ALLWAYS      3       /* allways get it! */

#endif

