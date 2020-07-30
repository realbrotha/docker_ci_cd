/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernext/inet/in_pcb.h 1.52.3.1                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)48       1.52.3.1  src/bos/kernext/inet/in_pcb.h, sockinc, bos53Q, q2008_08C3 2/5/08 16:03:42 */
/*
 *   COMPONENT_NAME: SYSXINET
 *
 *   FUNCTIONS: INHEAD_LOCKINIT
 *		INHEAD_LOCK
 *		INHEAD_UNLOCK
 *		INUDP_HASHCHNHEAD_LOCK_DECL
 *		INUDP_HASHCHNHEAD_LOCK_INIT
 *		INUDP_HASHCHNHEAD_LOCK
 *		INUDP_HASHCHNHEAD_UNLOCK
 *		sotoinpcb
 *		sotorawinpcb
 *		so2inpcb
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
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 1.2
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
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
 *      Base:   in_pcb.h        7.4 (Berkeley) 4/22/89
 *      Merged: in_pcb.h        7.6 (Berkeley) 6/28/90
 */

#ifndef _IN_PCBHASH_H_
#define _IN_PCBHASH_H_

#ifdef __cplusplus
struct socket;
struct mbuf;
#endif

/*
 * Internet protocol hash queue structure
 */
struct inpcb_hash {
	struct inpcb_hash	*next;
	struct inpcb_hash	*prev;
};

#include <stddef.h>

struct inpcb_timewait {
	struct inpcb_timewait   *next;
	struct inpcb_timewait   *prev;
};

#define intimewaittopcb(hp)             \
	(struct inpcb *)((char *)(hp) - \
		offsetof(struct inpcb, inp_timewait))
#define inpcbtotimewait(inp)    (&(inp->inp_timewait))

#define	inhashtopcb(hp)		\
	(struct inpcb *)((char *)(hp) - offsetof(struct inpcb, inp_hash))
#define inpcbtohash(inp)	(&(inp->inp_hash))
#define INPCB_HASHSZ		24499
#define MAX_INPCB_HASHSZ	        999999
#define TCP_INPCB_HASHSZ		24499
#define UDP_INPCB_HASHSZ		24499

#define INPCB_TCPHASH(faddr, fport, laddr, lport) \
	((((faddr) + (laddr)) + (fport) + (lport)) % tcp_inpcb_hashsz)

#define INPCB_UDPHASH(lport) ((lport) % udp_inpcb_hashsz)

#define HSIZE_PORT              1024

#define LPORT_HASH(lport)      ((lport) % HSIZE_PORT)

struct inpcb_hash_table {
	struct inpcb_hash 	head;
	struct inpcb_hash	*cache;
};

extern struct inpcb_hash_table * tcp_pcb_hash_table;
extern struct inpcb_hash_table * udp_pcb_hash_table;

/* Define PCB hash bit lists. */
#define __NPCBBITS (sizeof(int) * 8)
#define __NPCBBITS_MASK (__NPCBBITS - 1)
#define __NPCBINTS ((TCP_INPCB_HASHSZ + __NPCBBITS - 1) / __NPCBBITS)

/* before dynamically sized hash table the __NCPBINTS was used */
extern int __npcbints;

/*
 * Hash macros.  Pass in a bit number and a hash prefix, and these macros
 * access the right part of the right array.
 */
#define HASH_SET(bit, hash) \
	((void) fetch_and_or(&hash##_hash_bits[(bit)/__NPCBBITS], \
		  (1 << ((bit) & __NPCBBITS_MASK))))
#define HASH_CLEARWORD(wordindex, hash) \
	((void) fetch_and_and(&hash##_hash_bits[(wordindex)], 0))

/* Define the macros we use in the code. */
#define TCP_FAST_HASH_SET(bit) HASH_SET(bit, tcp_fast)
#define TCP_FAST_HASH_CLEARWORD(wordindex) HASH_CLEARWORD(wordindex, tcp_fast)
#define TCP_SLOW_HASH_SET(bit) HASH_SET(bit, tcp_slow)
#define TCP_SLOW_HASH_CLEARWORD(wordindex) HASH_CLEARWORD(wordindex, tcp_slow)

/*
 * External references to hash bits.  The fast hash tells us which buckets
 * have work for the fast timeout, and the slow hash tells us which buckets
 * have work for the slow timeout.
 */
extern int *	tcp_fast_hash_bits;
extern int *	tcp_slow_hash_bits;

extern long udp_inpcb_hashsz;
extern long tcp_inpcb_hashsz;

#if	defined(_KERNEL)
#define NET_CACHELINESIZE       128
/*
 * Including net_globals.h (where NET_CACHELINESIZE is defined) breaks nfs.
 * Hence we redefine NET_CACHELINESIZE here. These should be kept consistent.
 * This is also defined in in_var.h & route.h (because of build breaks
 * encountered when included through net_globals.h).
 */

/* done to remove false sharing */
struct hashchn_lock {
        simple_lock_data_t      _l;
        char                    dummy[NET_CACHELINESIZE - sizeof(simple_lock_data_t)];
};


/* Hash table chain head lock */
extern	struct hashchn_lock  *	tcp_pcb_hashchn_lock;
extern	struct hashchn_lock  *	udp_pcb_hashchn_lock;

extern 	simple_lock_data_t	tcp_port_count_lock[HSIZE_PORT];
extern 	simple_lock_data_t	udp_port_count_lock[HSIZE_PORT];
#endif

union route_6 {
    struct route route;
    struct {
	struct  rtentry *space_rt;
	struct  sockaddr_in6 spare_dst;
    } spare_route6;
};
union in_addr_6 {
    struct {
	u_int32_t spare[3];
	struct    in_addr addr;
    } in_addr_4;
    struct  in6_addr addr6;
};


/* IPv6 socket options */
struct ipv6_opts {
	struct  icmp6_filter *v6o_icmp6filter;   /* ICMPv6 filter */
	int v6o_cksumoffset;                     /* IPV6_CHECKSUM offset */
	struct in6_addr *v6o_srcaddr;            /* IPV6_PKTINFO src addr */
	int v6o_tclass;                          /* IPV6_TCLASS socket option */
	int v6o_use_min_mtu;                     /* IPV6_USE_MIN_MTU option */
	struct  in6_addr * v6o_nexthop;          /* IPV6_NEXTHOP option */
};


/*
 * Common structure pcb for internet protocol implementation.
 * Here are stored pointers to local and foreign host table
 * entries, local and foreign socket numbers, and pointers
 * up (to a socket structure) and down (to a protocol-specific)
 * control block.
 */
struct inpcb {
	struct	inpcb *inp_next,*inp_prev;
					/* pointers to other pcb's */
	struct	inpcb *inp_head;	/* pointer back to chain of inpcb's
					   for this protocol */
	u_int32_t inp_iflowinfo;	/* input flow label */
	u_short	inp_fport;		/* foreign port */
	u_int16_t inp_fatype;		/* foreign address type */
	union	in_addr_6 inp_faddr_6;	/* foreign host table entry */
	u_int32_t inp_oflowinfo;	/* output flow label */
	u_short	inp_lport;		/* local port */
	u_int16_t inp_latype;		/* local address type */
	union	in_addr_6 inp_laddr_6;	/* local host table entry */
	struct	socket *inp_socket;	/* back pointer to socket */
	caddr_t	inp_ppcb;		/* pointer to per-protocol pcb */
	union	route_6 inp_route_6;	/* placeholder for routing entry */
	struct ifaddr *inp_ifa;         /* interface address to use */
#define INP_IFA (inp ? inp->inp_ifa : (struct ifaddr *)0)
	int	inp_flags;		/* generic IP/datagram flags */
	/* XXX The following three members replace the inp_ip struct. */
	/* Be aware. Perhaps both are necessary?                      */
	u_int8_t inp_proto;		/* protocol */
	u_int8_t inp_tos;		/* type of service */
	u_int8_t inp_ttl;		/* time to live */
	u_int8_t  inp_rcvttl;		/* received time to live */
	struct ifnet *inp_rcvif;	/* received interface */
	struct	mbuf *inp_options;	/* IP options */
	int	inp_refcnt;		/* reference count */
	struct inpcb_hash inp_hash;	/* hash links			*/
/* inp_hash moved ahead to make netstat -Aan work for udp when
   using hash chains
*/
#if	defined(_KERNEL)
	simple_lock_data_t inp_lock;	/* structure lock */
	int		   _inhl;
	simple_lock_data_t inp_rc_lock;	/* refcnt lock */
#endif
#ifdef IP_MULTICAST
	struct ip_moptions *inp_moptions; /* IP multicast options */
	ushort ip_max_membership; /* Max membership that can be allocated */
	ushort ip_max_membership6; /* Max membership that can be allocated */
#endif
	struct inpcb_timewait   inp_timewait;
	int	inp_lock_hsh_ndx ;
	struct ipv6_opts *inp_v6opts;    /* IPv6 options */
	struct pmtu_entry *inp_pmtu;
};

/* for v4 compat */
#define inp_faddr       inp_faddr_6.in_addr_4.addr
#define inp_laddr       inp_laddr_6.in_addr_4.addr
#define inp_faddr6      inp_faddr_6.addr6
#define inp_laddr6      inp_laddr_6.addr6
#define inp_route       inp_route_6.route

/* address types */
#define IPATYPE_UNBD	0x0	/* unbound address */
#define IPATYPE_IPV4	0x1	/* IPv4 address */
#define IPATYPE_IPV6	0x2	/* IPv6 address */
#define IPATYPE_DUAL	0x3	/* both IPv4 and IPv6 address */


/* flags in inp_flags: */
#define	INP_RECVOPTS		0x01	/* receive incoming IP options */
#define	INP_RECVRETOPTS		0x02	/* receive IP options for reply */
#define	INP_RECVDSTADDR		0x04	/* receive IP dst address */
#define INP_RECVMACHDR		0x08	/* receive MAC hdr for upper layers */
#define	INP_RECVIFINFO		0x10	/* receive IFNET name/addr/type */
#define INP_BROADCAST_IF	0x20	/* User explicitly specifies which IF
						to send bcasts on. */
#define INP_FINDPMTU		0x40	/* PMTU discovery active (udp only) */
#define INP_DONTFRAG		0x80	/* Set IP_DF bit for udp packets */
#define INP_RECVINTERFACE	0x0100	/* receive inbound interface */
#define INP_NOPROBE		0x0200	/* don't trigger NUD probes */
#define INP_COMPATV4		0x0400	/* can be used by IPv4 */
#define INP_COMPATV6		0x0800	/* can be used by IPv6 */
#define INP_COMPATANY		0x0C00	/* can be used by any */
#define	INP_HDRINCL		0x1000	/* user supplies entire IP header */
#define INP_RECVTTL		0x2000	/* receive TTL/hlim info */
#define INP_RECVPKTINFO		0x4000	/* receive packet info */
#define INP_RECVHOPLIMIT        0x8000  /* receive hop limit */
#define INP_RECVTCLASS          0x10000  /* receive traffic class */
#define INP_USE_MIN_MTU         0x20000  /* IPV6_USE_MIN_MTU socket option */
#define INP_DONTFRAG6           0x40000  /* IPV6_DONTFRAG socket option */
#define INP_RECVPATHMTU         0x80000  /* IPV6_RECVPATHMTU socket option */
#define INP_RECVRTHDR           0x100000 /* IPV6_RECVRTHDR socket option */
#define INP_RECVHOPOPTS         0x200000 /* IPV6_RECVHOPOPTS socket option */
#define INP_RECVDSTOPTS         0x400000 /* IPV6_RECVDSTOPTS socket option */
#define INP_AIXRAWSOCKET        0x800000 /* IPV6_AIXRAWSOCKET socket option */
#define INP_CONTROLOPTS         (INP_RECVMACHDR|INP_RECVOPTS| \
                                        INP_RECVRETOPTS|INP_RECVIFINFO| \
                                        INP_BROADCAST_IF|INP_RECVDSTADDR| \
                                        INP_RECVINTERFACE|INP_RECVPKTINFO| \
                                        INP_RECVTTL|INP_RECVHOPLIMIT| \
                                        INP_RECVTCLASS|INP_RECVRTHDR| \
                                        INP_RECVHOPOPTS|INP_RECVDSTOPTS)
#define INP_PCBHASHMOD          0x1000000 /* PCB being hashed */
#define INP_BROADCAST_LADDR     0x2000000 /* User explicitly binds broadcast
					     address as the local address */
#define INP_PCBHASHDEL          0x4000000 /* PCB being deleted */

#ifdef sotorawcb
/*
 * Common structure pcb for raw internet protocol access.
 * Here are internet specific extensions to the raw control block,
 * and space is allocated to the necessary sockaddrs.
 */
struct raw_inpcb {
	struct	rawcb rinp_rcb;	/* common control block prefix */
	struct	mbuf *rinp_options;	/* IP options */
	int	rinp_flags;		/* flags, e.g. raw sockopts */
#define	RINPF_HDRINCL	0x1		/* user supplies entire IP header */
	struct	sockaddr_in rinp_faddr;	/* foreign address */
	struct	sockaddr_in rinp_laddr;	/* local address */
	struct	route rinp_route;	/* placeholder for routing entry */
#ifdef IP_MULTICAST
	struct	mbuf *rinp_moptions;	/* specific multicast options */
#endif
};
#endif

#define	INPLOOKUP_WILDCARD	1
#define	INPLOOKUP_SETLOCAL	2
#define	INPLOOKUP_USECACHE	4

#define INPLOOKUP_CMPV6ADDR     8

#define	sotoinpcb(so)		((struct inpcb *)(so)->so_pcb)

#define	sotorawinpcb(so)	((struct raw_inpcb *)(so)->so_pcb)

#ifdef _KERNEL

extern CONST struct in_addr	zeroin_addr;

#define INPCB_LOCK(inp)         /* unused, but symbol is kept for compat */
#define INPCB_UNLOCK(inp)       /* unused, but symbol is kept for compat */

#define INHEAD_LOCK(head)	(head)->_inhl = disable_lock(PL_IMP, &((head)->inp_lock))
#define	INHEAD_UNLOCK(head) 	unlock_enable((head)->_inhl, &((head)->inp_lock))
#define INHEAD_LOCKINIT(head)	simple_lock_init(&((head)->inp_lock))

#define	INTCP_HASHCHNHEAD_LOCK_DECL()		int	_intcphchnhl;

#define INTCP_HASHCHNHEAD_LOCK_INIT()  { \
        int i ; \
        tcp_pcb_hashchn_lock = (struct hashchn_lock *) \
		xmalloc ( (sizeof(struct hashchn_lock)) * tcp_inpcb_hashsz, 8, pinned_heap ) ; \
	if(!tcp_pcb_hashchn_lock) \
        { \
                return(ENOMEM); \
        } \
        for ( i = 0 ; i < tcp_inpcb_hashsz ; i++ ) { \
                lock_alloc ( &(tcp_pcb_hashchn_lock[i]._l), LOCK_ALLOC_PIN, TCBHCHN_LOCK_FAMILY, i ) ; \
                simple_lock_init ( &(tcp_pcb_hashchn_lock[i]._l) ) ; \
        } \
}

#define INTCP_HASHCHNHEAD_LOCK(index) _intcphchnhl = \
					     disable_lock(PL_IMP, \
					     &(tcp_pcb_hashchn_lock[index]._l))

#define INTCP_HASHCHNHEAD_UNLOCK(index) unlock_enable(_intcphchnhl,\
					     &(tcp_pcb_hashchn_lock[index]._l))

#define INTCP_HASHCHNHEAD_LOCK_MINE(index) lock_mine(&tcp_pcb_hashchn_lock[index]._l)

#define	INUDP_HASHCHNHEAD_LOCK_DECL()		int	_inudphchnhl;

#define INUDP_HASHCHNHEAD_LOCK_INIT()  { \
        int i ; \
        udp_pcb_hashchn_lock = (struct hashchn_lock *) \
		xmalloc ( (sizeof(struct hashchn_lock)) * udp_inpcb_hashsz, 8, pinned_heap ) ; \
        for ( i = 0 ; i < udp_inpcb_hashsz ; i++ ) { \
                lock_alloc ( &(udp_pcb_hashchn_lock[i]._l), LOCK_ALLOC_PIN, UDBHCHN_LOCK_FAMILY, i ) ; \
                simple_lock_init ( &(udp_pcb_hashchn_lock[i]._l) ) ; \
        } \
}

#define INUDP_HASHCHNHEAD_LOCK(index) _inudphchnhl = \
					     disable_lock(PL_IMP, \
                                             &(udp_pcb_hashchn_lock[index]._l))

#define INUDP_HASHCHNHEAD_UNLOCK(index) unlock_enable(_inudphchnhl,\
                                             &(udp_pcb_hashchn_lock[index]._l))

#define INUDP_HASHCHNHEAD_LOCK_MINE(index) lock_mine(&udp_pcb_hashchn_lock[index]._l)

/* LPORT LOCK Definitions */

#define LPORT_LOCK_DECL()               int _psl;

#define TCPPORT_LOCK_INIT(index)        simple_lock_init(\
                                                &(tcp_port_count_lock[index]))

#define TCPPORT_LOCK(lport)             disable_lock(PL_IMP,\
                                                &(tcp_port_count_lock[lport]))

#define TCPPORT_UNLOCK(lport)           unlock_enable(_psl,\
                                                &(tcp_port_count_lock[lport]))

#define UDPPORT_LOCK_INIT(index)        simple_lock_init(\
                                                &(udp_port_count_lock[index]))

#define UDPPORT_LOCK(lport)             disable_lock(PL_IMP,\
                                                &(udp_port_count_lock[lport]))

#define UDPPORT_UNLOCK(lport)           unlock_enable(_psl,\
                                                &(udp_port_count_lock[lport]))
#define LPORT_LOCK(head,lport) _psl = \
        ((head==&tcb) ? TCPPORT_LOCK(lport) : UDPPORT_LOCK(lport))

#define LPORT_UNLOCK(head,lport) \
        ((head==&tcb) ? TCPPORT_UNLOCK(lport) : UDPPORT_UNLOCK(lport))

#include <netinet/in.h>

/*
 * Count the number of port users for ephemeral ports, so we can skip the
 * long lookups.
 *
 * We waste 1024 words (0-1023) for the sake of speed (less arithmetic).
 */
extern struct inpcb tcb;
extern unsigned int tcp_port_count[];
extern unsigned int udp_port_count[];
#define PORT_IN_USE(head, port) \
	((head) == &tcb ? tcp_port_count[port] : udp_port_count[port])
#define PORT_INC(head, port) \
	((head) == &tcb ? fetch_and_add((int *)&tcp_port_count[port],1) : fetch_and_add((int *)&udp_port_count[port],1))
#define PORT_DEC(head, port) \
	((head) == &tcb ? fetch_and_add((int *)&tcp_port_count[port],-1) : fetch_and_add((int *)&udp_port_count[port],-1))

#define so2inpcb(so)						\
		(struct inpcb *) (((caddr_t) (so)) +		\
				sizeof(struct socket))

extern long tcp_ephemeral_low;
extern long tcp_ephemeral_high;
extern long udp_ephemeral_low;
extern long udp_ephemeral_high;
#endif

/* Used for UDP to discover information to create packet header
 * without actually doing a connect and modifying the inpcb.
 */

struct inhdr_info {
        u_short         inhdr_lport;
        u_int16_t       inhdr_latype;
        union in_addr_6 inhdr_laddr_6;
        u_short         inhdr_fport;
        u_int16_t       inhdr_fatype;
        union in_addr_6 inhdr_faddr_6;
        int             inhdr_flags;
/* flowinfo & tos used by v6 only */
        u_int32_t       inhdr_flowinfo;
        u_int8_t        inhdr_tos;
};

#define inhdr_laddr     inhdr_laddr_6.in_addr_4.addr
#define inhdr_faddr     inhdr_faddr_6.in_addr_4.addr
#define inhdr_laddr6    inhdr_laddr_6.addr6
#define inhdr_faddr6    inhdr_faddr_6.addr6


#endif /* _IN_PCBHASH_H_ */
