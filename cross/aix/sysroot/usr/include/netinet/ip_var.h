/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernext/inet/ip_var.h 1.53                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)53       1.53  src/bos/kernext/inet/ip_var.h, sockinc, bos53H, h2005_37A0 8/18/05 09:22:03 */
/*
 *   COMPONENT_NAME: SYSXINET
 *
 *   FUNCTIONS: IPFRAG_LOCK
 *		IPFRAG_LOCKINIT
 *		IPFRAG_UNLOCK
 *		IPMISC_LOCK
 *		IPMISC_LOCKINIT
 *		IPMISC_UNLOCK
 *		
 *
 *   ORIGINS: 26,27,85,89
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1996
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
 *
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
 *	Base:	ip_var.h	7.6 (Berkeley) 9/20/89
 *	Merged:	ip_var.h	7.7 (Berkeley) 6/28/90
 */

#include <netinet/ip.h>

#ifndef	_NETINET_IP_VAR_H
#define	_NETINET_IP_VAR_H

#ifdef __cplusplus
struct mbuf;
struct ifnet;
struct in_multi;
#endif

/*
 * Overlay for ip header used by other protocols (tcp, udp).
 */
struct ipovly {
#ifdef __64BIT__
	union {
		int	spc1i;
		struct {
			u_short s1;
			u_short s2;
		} spc1s;
	} spc1u;
#define spc1	spc1u.spc1i
#define spc1s1	spc1u.spc1s.s1
#define spc1s2	spc1u.spc1s.s2
	int	spc2;
#else
	caddr_t	ih_next, ih_prev;	/* for protocol sequence q's */
#endif /* __64BIT__ */
	u_char	ih_x1;			/* (unused) */
	u_char	ih_pr;			/* protocol */
	u_short	ih_len;			/* protocol length */
	struct	in_addr ih_src;		/* source internet address */
	struct	in_addr ih_dst;		/* destination internet address */
};

/* 
   Size of IP reassembly queue structure; Used for parallelizing
   access to the reassembly queue, else the IPFRAG_LOCK gets hot
   due to serialized access.
*/

#define IPFRAG_QSIZE	101

/*
 * Ip reassembly queue structure.  Each fragment
 * being reassembled is attached to one of these structures.
 * They are timed out after ipq_ttl drops to 0, and may also
 * be reclaimed if memory becomes tight.
 */
struct ipq {
	struct	ipq *next,*prev;	/* to other reass headers */
	struct	ipasfrag *ipq_next,*ipq_prev;
					/* to ip headers of fragments */
	u_char	ipq_ttl;		/* time for reass q to live */
	u_char	ipq_p;			/* protocol of this fragment */
	u_short	ipq_id;			/* sequence id for reassembly */
	struct	in_addr ipq_src,ipq_dst;
#ifdef _KERNEL
	simple_lock_data_t      ip_frag_lock;
#endif
	u_short ipq_nfrags;             /* to limit the number of IP fragments */
};

/*
 * Ip header, when holding a fragment.
 */
struct	ipasfrag {
	struct	ipasfrag *ipf_next,*ipf_prev;	/* fragment queue */
	struct	mbuf *ipf_mbuf;		/* initial mbuf */
	struct	ip ipf_ip;		/* ip header */
#define	ipf_vhl	ipf_ip.ip_vhl
#define	ipf_len	ipf_ip.ip_len
#define	ipf_off	ipf_ip.ip_off
#define	ipf_id	ipf_ip.ip_id
#define	ipf_p	ipf_ip.ip_p
#define	ipf_mff	ipf_ip.ip_sum		/* copied from (ip_off&IP_MF) */
#define	ipf_src	ipf_ip.ip_src
#define	ipf_dst	ipf_ip.ip_dst
};

/*
 * Structure stored in mbuf in inpcb.ip_options
 * and passed to ip_output when ip options are in use.
 * The actual length of the options (including ipopt_dst)
 * is in m_len.
 */
#define MAX_IPOPTLEN	40

struct ipoption {
	struct	in_addr ipopt_dst;	/* first-hop dst if source routed */
	u_char	ipopt_list[MAX_IPOPTLEN];	/* options proper */
};

#ifdef IP_MULTICAST
/*
 * Structure stored in an mbuf attached to inpcb.ip_moptions and
 * passed to ip_output when IP multicast options are in use.
 */
struct ip_moptions {
	struct	ifnet   *imo_multicast_ifp;  /* ifp for outgoing multicasts */
	u_char	         imo_multicast_ttl;  /* TTL for outgoing multicasts */
	u_char		 imo_multicast_loop; /* 1 => hear sends if a member */
	u_short		 imo_num_memberships;/* no. memberships this socket */
	struct in_multi **imo_membership;
	struct ifnet	*imo_broadcast_ifp;  /* broadcast interface; belongs */
					     /* in struct inpcb */
	struct in6_multi **imo_membership6;
        u_short          imo_num_memberships6;/* no. IPv6 memberships this socket */
	struct in_addr	imo_addrtouse;
};
#endif

/* Source route holding structure (moved here from ip_input.c) */
struct ip_srcrt {
	struct	in_addr dst;			/* final destination */
	char	nop;				/* one NOP to align */
	char	srcopt[IPOPT_OFFSET + 1];	/* OPTVAL, OLEN and OFFSET */
	struct	in_addr route[MAX_IPOPTLEN/sizeof(struct in_addr)];
};

struct	ipstat {
	long	ips_total;		/* total packets received */
	long	ips_badsum;		/* checksum bad */
	long	ips_tooshort;		/* packet too short */
	long	ips_toosmall;		/* not enough data */
	long	ips_badhlen;		/* ip header length < data size */
	long	ips_badlen;		/* ip length < ip header length */
	long	ips_fragments;		/* fragments received */
	long	ips_fragdropped;	/* frags dropped (dups, out of space) */
	long	ips_fragtimeout;	/* fragments timed out */
	long	ips_forward;		/* packets forwarded */
	long	ips_cantforward;	/* packets rcvd for unreachable dest */
	long	ips_redirectsent;	/* packets forwarded on same net */
	long	ips_noproto;		/* unknown or unsupported protocol */
	long	ips_delivered;		/* packets consumed here */
	long	ips_localout;		/* total ip packets generated here */
	long	ips_odropped;		/* lost packets due to nobufs, etc. */
	long	ips_reassembled;	/* total packets reassembled ok */
	long	ips_fragmented;		/* output packets fragmented ok */
	long	ips_ofragments;		/* output fragments created */
	long	ips_cantfrag;		/* don't fragment flag was set, etc. */
        u_long  ips_badoptions;         /* error in option processing */
        u_long  ips_noroute;            /* packets discarded due to no route */
        u_long  ips_badvers;            /* ip version != 4 */
        u_long  ips_rawout;             /* total raw ip packets generated */
        /* SNMP BASE begin */
        u_long  ipInHdrErrors;          /* # of header erros: also add
                                           ips_badsum, ips_tooshort,
                                           ips_toosmall, ips_badhlen and
                                           ips_badlen from above */
        u_long  ipInAddrErrors;         /* # of datagrams with ip addr errors*/
        u_long  ipInDiscards;           /* # of input datagrams discarded */
#ifdef IP_MULTICAST
        u_long  ipInMAddrErrors;         /* # of dropped multicast datagrams 
					    because we are not receiving on 
					    this address */
#endif /* IP_MULTICAST */
        /* SNMP BASE end */
#if	defined(_KERNEL) && LOCK_NETSTATS
	simple_lock_data_t ips_lock;	/* statistics lock */
#endif
	u_long  ips_pmtudisc;		/* Successful PMTU discovery cycles */
	u_long  ips_pmturedisc;		/* PMTU rediscovery attempts */
	u_long  ips_pmtuguesses;	/* PMTU "guesses" due to no response */
	u_long  ips_pmtutimeouts;	/* PMTU first stage timeouts */
	u_long  ips_pmtudecreases;	/* PMTU decreases detected */
	u_long  ips_pmtupackets;	/* PMTU discovery packets sent */
	u_long  ips_pmtunomem;		/* PMTU discovery net_malloc failure */
	u_long  ips_badsource;		/* Invalid IP source address         */
	u_long  ips_thread;		/* packets processed by threads */
	u_long  ips_threaddropped;	/* packets dropped by threads */
	u_long  ips_fullsock;		/* packets dropped by full raw socket */
	u_long  ips_dgdpackets;		/* Active DGD packets sent */
	u_long  ips_dgdnomem;		/* Active DGDs not sent due to no mem */
	u_long  ips_dgdnogw;		/* Gateways not added due to no mem */
};



/* 
 * distributed ipstat structure; to fit in cache lines (2*128) and remove
 * interference
 */

#define IP_CACHE_LINE_SIZE 128

struct	dist_ipstat {
	long	ips_total;		/* total packets received */
	long	ips_badsum;		/* checksum bad */
	long	ips_tooshort;		/* packet too short */
	long	ips_toosmall;		/* not enough data */
	long	ips_badhlen;		/* ip header length < data size */
	long	ips_badlen;		/* ip length < ip header length */
	long	ips_fragments;		/* fragments received */
	long	ips_fragdropped;	/* frags dropped (dups, out of space) */
	long	ips_fragtimeout;	/* fragments timed out */
	long	ips_forward;		/* packets forwarded */
	long	ips_cantforward;	/* packets rcvd for unreachable dest */
	long	ips_redirectsent;	/* packets forwarded on same net */
	long	ips_noproto;		/* unknown or unsupported protocol */
	long	ips_delivered;		/* packets consumed here */
	long	ips_localout;		/* total ip packets generated here */
	long	ips_odropped;		/* lost packets due to nobufs, etc. */
	long	ips_reassembled;	/* total packets reassembled ok */
	long	ips_fragmented;		/* output packets fragmented ok */
	long	ips_ofragments;		/* output fragments created */
	long	ips_cantfrag;		/* don't fragment flag was set, etc. */
        u_long  ips_badoptions;         /* error in option processing */
        u_long  ips_noroute;            /* packets discarded due to no route */
        u_long  ips_badvers;            /* ip version != 4 */
        u_long  ips_rawout;             /* total raw ip packets generated */
        /* SNMP BASE begin */
        u_long  ipInHdrErrors;          /* # of header erros: also add
                                           ips_badsum, ips_tooshort,
                                           ips_toosmall, ips_badhlen and
                                           ips_badlen from above */
        u_long  ipInAddrErrors;         /* # of datagrams with ip addr errors*/
        u_long  ipInDiscards;           /* # of input datagrams discarded */
#ifdef IP_MULTICAST
        u_long  ipInMAddrErrors;         /* # of dropped multicast datagrams 
					    because we are not receiving on 
					    this address */
#endif /* IP_MULTICAST */
        /* SNMP BASE end */
#if	defined(_KERNEL) && LOCK_NETSTATS
	simple_lock_data_t ips_lock;	/* statistics lock */
#endif
	u_long  ips_pmtudisc;		/* Successful PMTU discovery cycles */
	u_long  ips_pmturedisc;		/* PMTU rediscovery attempts */
	u_long  ips_pmtuguesses;	/* PMTU "guesses" due to no response */
	u_long  ips_pmtutimeouts;	/* PMTU first stage timeouts */
	u_long  ips_pmtudecreases;	/* PMTU decreases detected */
	u_long  ips_pmtupackets;	/* PMTU discovery packets sent */
	u_long  ips_pmtunomem;		/* PMTU discovery net_malloc failure */
	u_long  ips_badsource;		/* Invalid IP source address         */
	u_long  ips_thread;		/* packets processed by threads */
	u_long  ips_threaddropped;	/* packets dropped by threads */
	u_long  ips_fullsock;		/* packets dropped by full raw socket */
	u_long  ips_dgdpackets;		/* Active DGD packets sent */
	u_long  ips_dgdnomem;		/* Active DGDs not sent due to no mem */
	u_long  ips_dgdnogw;		/* Gateways not added due to no mem */
	char    dummy[IP_CACHE_LINE_SIZE -
	  (sizeof(struct ipstat) % IP_CACHE_LINE_SIZE)]; /* cache line size */
};



#ifdef _KERNEL
/* extern	simple_lock_data_t	ip_frag_lock; old lock */
extern	simple_lock_data_t	ip_misc_lock;

#define IPFRAG_LOCKINIT(index)	{					\
	lock_alloc(&(ipq[index].ip_frag_lock), LOCK_ALLOC_PIN, IPFRAG_LOCK_FAMILY, -1);\
	simple_lock_init(&(ipq[index].ip_frag_lock));		\
}
#define IPFRAG_LOCK_DECL()	int	_ipfl;
#define IPFRAG_LOCK(index)		_ipfl = disable_lock(PL_IMP, &(ipq[index].ip_frag_lock))
#define IPFRAG_UNLOCK(index)		unlock_enable(_ipfl, &(ipq[index].ip_frag_lock))

/* flags passed to ip_output as last parameter */
#define	IP_FORWARDING		0x1		/* most of ip header exists */
#define IP_RAWOUTPUT            0x2             /* raw ip header exists */
#ifdef IP_MULTICAST
#define IP_MULTICASTOPTS        0x4             /* multicast opts present */
#define IP_IFMULTI_NOLOCK	0x8		/* Don't grab ifmulti lock */
						/* multicast opts */
#endif
#define	IP_ROUTETOIF		SO_DONTROUTE	/* bypass routing tables - 0x0010 */
#define	IP_ALLOWBROADCAST	SO_BROADCAST	/* can send broadcast packets - 0x0020 */
#define IP_BROADCASTOPTS	0x40 		/* Broadcast opts inside */
#define IP_PMTUOPTS		0x80		/* PMTU discovery options */
#define IP_GROUP_ROUTING        0x100           /* group routing gidlist */
#define IP_ANCILLARY            0x200           /* ancillary data in last argument */ 
#define IP_NOMULTIPATH		SO_NOMULTIPATH	/* always use first matching route - 0x4000 */

extern	CONST u_char inetctlerrmap[];
extern	struct	ipstat	ipstat;
extern	struct	dist_ipstat	*dist_ipstat[];
extern	struct	ipq	ipq[];			/* ip reass. queue */
extern	u_short	ip_id;				/* ip packet ctr, for ids */

#define	INBOUND_FW_NDD		0
#define	INBOUND_FW_MAC		1
#define	INBOUND_FW_RESERVED	2
#define	INBOUND_FW_MAX_ARGS	3

typedef struct {
	void *args[INBOUND_FW_MAX_ARGS];
} inbound_fw_args_t;

extern void (*inbound_fw)(struct ifnet *, struct mbuf *, inbound_fw_args_t *);

#define	OUTBOUND_FW_OPT		0
#define	OUTBOUND_FW_RO		1
#define	OUTBOUND_FW_FLAGS	2
#define	OUTBOUND_FW_MOPTS	3
#define	OUTBOUND_FW_GIDLIST	4
#define	OUTBOUND_FW_RESERVED	5
#define	OUTBOUND_FW_MAX_ARGS	6

typedef struct {
	void *args[OUTBOUND_FW_MAX_ARGS];
} outbound_fw_args_t;

extern int (*outbound_fw)(struct ifnet *ifp, struct mbuf *,
			  outbound_fw_args_t *);

#endif
#endif
