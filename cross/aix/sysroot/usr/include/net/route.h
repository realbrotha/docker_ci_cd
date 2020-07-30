/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/net/route.h 1.70.1.2                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1993              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)64       1.70.1.2  src/bos/kernel/net/route.h, sysnet_route, bos53X, x2010_07B1 2/10/10 19:52:24 */
/*
 *   COMPONENT_NAME: SYSNET
 *
 *   FUNCTIONS: ROUTE_LOCKINIT
 *		ROUTE_LOCK_DECL
 *		ROUTE_READ_LOCK
 *		ROUTE_READ_UNLOCK
 *		ROUTE_WRITETOREAD_LOCK
 *		ROUTE_WRITE_LOCK
 *		ROUTE_WRITE_UNLOCK
 *		RTFREE
 *		RTTTOPRHZ
 *		RT_ROUNDUP
 *		
 *
 *   ORIGINS: 26,27,85,127,196
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
 *
 */
/*
 * Copyright (c) 1980, 1986 Regents of the University of California.
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
 *	Base:	route.h	7.4 (Berkeley) 6/27/88
 *	Merged:	route.h	7.11 (Berkeley) 6/28/90
 *	Merged:	route.h	7.13 (Berkeley) 4/25/91
 *      Merged: route.h 8.3 (Berkeley) 4/19/94
 */

#include <sys/ras.h>
#ifndef ROUTE_H
#define ROUTE_H

#ifdef __cplusplus
struct rtentry;
struct sockaddr;
struct ifnet;
struct ifaddr;
#endif

/*
 * Kernel resident routing tables.
 *
 * The routing tables are initialized when interface addresses
 * are set by making entries for all directly connected interfaces.
 */
/*
 * For purposes of IPv6, a few of the changes incorporated into FreeBSD will
 * be made in here as well.  Unlike FreeBSD, IPv4 will not be modified.
 * That'll be someone else's job.  (See struct rtentry, and flags values,
 * for details.)
 */


/*
 * A route consists of a destination address and a reference
 * to a routing entry.  These are often held by protocols
 * in their control blocks, e.g. inpcb.
 */
struct route {
	struct	rtentry *ro_rt;
	struct	sockaddr ro_dst;
};

struct ip6_rtexpire_isr {
        struct ip6_rtexpire_isr *next;
        int count;
};

struct pmtu_isr {
	struct pmtu_isr * next;
	int               val;
	struct rtentry  * rtp;
	int		operation;
#define PMTU_ISR_TIMEOUT 0
#define PMTU_ISR_TCP_UPDATE 1
#define PMTU_ISR_UDP_UPDATE 2
};

#define PMTU_RT_DEL     0x01
#define PMTU_USR_DEL    0x02

/*
 * These numbers are used by reliable protocols for determining
 * retransmission behavior and are included in the routing structure.
 */
#ifdef _KERNEL
struct rt_metrics {
#else
struct rt_metrics_new {
#endif
	__ulong32_t	rmx_locks;	/* Kernel must leave these values alone */
	__ulong32_t	rmx_mtu;	/* MTU for this path */
	__ulong32_t	rmx_hopcount;	/* max hops expected */
	__ulong32_t	rmx_expire;	/* lifetime for route, e.g. redirect */
	__ulong32_t	rmx_recvpipe;	/* inbound delay-bandwith product */
	__ulong32_t	rmx_sendpipe;	/* outbound delay-bandwith product */
	__ulong32_t	rmx_ssthresh;	/* outbound gateway buffer limit */
	__ulong32_t	rmx_rtt;	/* estimated round trip time */
	__ulong32_t	rmx_rttvar;	/* estimated rtt variance */
	__ulong32_t     rmx_pksent;	/* packets sent using this route */
};

/* This is the old rt_metrics structure.  It must still be used in	*
 * rt_msghdr for binary compat.						*/
#ifdef _KERNEL
struct rt_metrics_compat {
#else
struct rt_metrics {
#endif
	__ulong32_t	rmx_locks;	/* Kernel must leave these values alone */
	__ulong32_t	rmx_mtu;	/* MTU for this path */
	__ulong32_t	rmx_hopcount;	/* max hops expected */
	__ulong32_t	rmx_expire;	/* lifetime for route, e.g. redirect */
	__ulong32_t	rmx_recvpipe;	/* inbound delay-bandwith product */
	__ulong32_t	rmx_sendpipe;	/* outbound delay-bandwith product */
	__ulong32_t	rmx_ssthresh;	/* outbound gateway buffer limit */
	__ulong32_t	rmx_rtt;	/* estimated round trip time */
	__ulong32_t	rmx_rttvar;	/* estimated rtt variance */
};

/*
 * rmx_rtt and rmx_rttvar are stored as microseconds;
 * RTTTOPRHZ(rtt) converts to a value suitable for use
 * by a protocol slowtimo counter.
 */
#define	RTM_RTTUNIT	1000000	/* units for rtt, rttvar, as units per sec */
#define	RTTTOPRHZ(r)	((r) / (RTM_RTTUNIT / PR_SLOWHZ))

struct gidnode {
        short permission; /* 1 is allowed, 0 is disallowed */
        gid_t gid;
};

#include "sys/limits.h"
struct gidstruct {
        int inuse;
#ifdef __ia64
	int padding;		/* 8 byte alignment */
#endif /* __ia64 */
        struct gidnode gids[NGROUPS_MAX];
};

struct gidstruct_compat {
	int inuse;
#ifdef __ia64
	int padding;		/* 8 byte alignment */
#endif /* __ia64 */
	struct gidnode gids[32];
};

struct policystruct {
	int32_t pinfo_cnt; 	/* Number of routes in duplist */
	int32_t pinfo_policy; /* Routing policy for selecting routes in duplist */
	int32_t pinfo_lu_index; /* Index of last used route: For RR and Weighted RR */
	int32_t lu_index_usecnt; /* Number of times route has been used */
#define MAX_DUPLIST 50
	struct rtentry *pinfo_rtptr[MAX_DUPLIST]; /* Pointers to rtentry structs in duplist */
};
	
/*
 * We distinguish between routes to hosts and routes to networks,
 * preferring the former if available.  For each route we infer
 * the interface to use from the gateway address supplied when
 * the route was entered.  Routes that forward packets through
 * gateways are marked so that the output routines know to address the
 * gateway rather than the ultimate destination.
 */
/* We now allow multiple routes with the same key and netmask.
 * We also look at cost (hopcount) when choosing a route.
 * We try to choose a route based on best cost (hopcount) and if
 * there are multiple routes with the best cost we choose the more
 * specific route.
 * If there are multiple routes with the same cost and are equally
 * specific (same netmask) we will round robin between them.
 */
#ifndef	RNF_NORMAL
#include "net/radix.h"
#endif
struct rtentry {
	struct	radix_node rt_nodes[2];	/* tree glue, and other values */
#define	rt_key(r)	((struct sockaddr *)((r)->rt_nodes->rn_key))
#define	rt_mask(r)	((struct sockaddr *)((r)->rt_nodes->rn_mask))
	struct	sockaddr *rt_gateway;	/* value */
	short	rt_redisctime;		/* Not used.Counter for pmtu rediscovery */
	ushort	rt_refcnt;		/* # held references */
#define RTENTRY_REF(rt) fetch_and_add_h(&(rt)->rt_refcnt, 1);
#define RTENTRY_UNREF(rt) fetch_and_add_h(&(rt)->rt_refcnt, -1);
	u_long	rt_flags;		/* up/down?, host/net */
	struct	ifnet *rt_ifp;		/* the answer: interface to use */
	struct	ifaddr *rt_ifa;		/* the answer: interface to use */
	struct	sockaddr *rt_genmask;	/* for generation of cloned routes */
	caddr_t	rt_llinfo;		/* pointer to link level info cache */
#ifdef _KERNEL
	struct	rt_metrics rt_rmx;	/* metrics used by rx'ing protocols */
#else
	struct  rt_metrics_new rt_rmx;  /* metrics used by rx'ing protocols */
#endif
/* see #define rt_use rt_rmx.rmx_pksent below */
	struct	rtentry *rt_gwroute;	/* implied entry for gatewayed routes */
	short	rt_idle;		/* easy to tell llayer still live */
#ifdef	_AIX
	int     ipRouteAge;             /* SNMP BASE */
#endif
	caddr_t	rt_proto;		/* Not used.Protocol-specific data */
        /* Note:  The rt_gidlist should only be used internally by the kernel.
         * User processes that have a route returned to them should not use
         * the rt_gidlist, as there is no guarantee that it will remain
         * consistent.
         */
        struct  gidstruct *rt_gidlist;  /* gid restrictions for this route */
#ifdef _KERNEL
	simple_lock_data_t rt_lock;	/* protects this rtentry */
#else
	long rt_lock;			/* protects this rtentry */
#endif
	int rt_intr;		/* holds interrupt level when disable_locked */
	/* Duplicate routes (same key) are sorted based on cost and then
	 * based on netmask (more specific first). These are stored in the
	 * list pointed to by rn_dupedkey.
	 * Routes with the same netmask and cost are stored in on a list
	 * pointed to by rt_duplist.
	 * The last used route is pointed to by rt_lu.
	 */
	struct	rtentry *rt_duplist;	/* routes with same cost/netmask */
	struct policystruct *policyinfo; /* contains routing policy info */
	int	rt_timer;		/* No. of mins until cost restored */
	int	rt_cost_config;		/* User-configured cost */
	struct	pmtu_isr rt_pmtuisr;	/* Not used.parameter list for pmtu isr */
	struct ip6_rtexpire_isr rt_ip6expireisr; /* rtentry list to expire */
	tid_t   rt_ip6sleepword;        /* to sleep on neighbor discovery */
	int 	rt_weight;		/* User configured weight used for Weighted RR */
};

#define	rt_cost	rt_rmx.rmx_hopcount
#define IS_DUP(rt)	(((struct radix_node *)(rt))->rn_flags & RNF_DUP)
#define MAX_RT_COST INT_MAX

struct rtentry_plus {
	eye_catch8b_t 	rtp_eyecat;
	struct rtentry 	rtp_rt;
};

#define EYEC_RTENTRYA	0x257274656E747241ull	/*%rtentrA*/
#define EYEC_RTENTRYF	0x257274656E747246ull	/*%rtentrF*/

#define CHECK_RTENTRY(rt)	\
	if((eye_catch8b_t) (((struct rtentry_plus *)((void *) rt - \
		sizeof(eye_catch8b_t)))->rtp_eyecat) != EYEC_RTENTRYA) \
			panic("rtentry eyec not set");

#define rt_to_rtp(rt)	(struct rtentry_plus *)((void *)rt - sizeof(eye_catch8b_t));	

#define FREE_RT(rt)	\
			rtplus = rt_to_rtp(rt); \
			rtplus->rtp_eyecat = EYEC_RTENTRYF; \
			NET_FREE(rtplus, M_RTABLE);



/* This is used in ortentry to store rt_use so that #defines needed
   for rtentry will still work correctly.
*/
struct rt_metrics_dummy {
	__ulong32_t	rmx_pksent;	/* used to hold rt_use for ortentry */
};

/*
 * Following structure necessary for 4.3 compatibility;
 * We should eventually move it to a compat file.
 */
struct ortentry {
	__ulong32_t	rt_hash;	/* to speed lookups */
	struct	sockaddr rt_dst;	/* key */
	struct	sockaddr rt_gateway;	/* value */
	short	rt_flags;		/* up/down?, host/net */
	short	rt_refcnt;		/* # held references */
	struct rt_metrics_dummy rt_rmx;	/* raw # packets forwarded */
#define rt_use rt_rmx.rmx_pksent
	struct	ifnet *rt_ifp;		/* the answer: interface to use */
};

#define	RTF_UP		0x1		/* route useable */
#define	RTF_GATEWAY	0x2		/* destination is a gateway */
#define	RTF_HOST	0x4		/* host entry (net otherwise) */
#define RTF_REJECT	0x8		/* host or net unreachable */
#define	RTF_DYNAMIC	0x10		/* created dynamically (by redirect) */
#define	RTF_MODIFIED	0x20		/* modified dynamically (by redirect) */
#define RTF_DONE	0x40		/* message confirmed */
#define RTF_MASK	0x80		/* subnet mask present */
#define RTF_CLONING	0x100		/* generate new routes on use */
#define RTF_XRESOLVE	0x200		/* external daemon resolves name */
#define RTF_LLINFO	0x400		/* generated by ARP or ESIS */
#define RTF_STATIC      0x800           /* manually added */
#define RTF_BLACKHOLE   0x1000          /* silently drop */
#define	RTF_BUL		0x2000		/* has a binding update list */
#define RTF_PROTO2	0x4000		/* protocol specific routing flag */
#define RTF_PROTO1	0x8000		/* protocol specific routing flag */
#define RTF_CLONE	0x10000		/* protocol requires cloning */
#define RTF_CLONED	0x20000		/* route generated through cloning */
#define RTF_PROTO3	0x40000		/* protocol specific routing flag */
#define	RTF_BCE		0x80000		/* has a binding cache entry */
#define	RTF_PINNED	0x100000	/* future use */
#define	RTF_LOCAL	0x200000 	/* route represents a local address */
#define	RTF_BROADCAST	0x400000	/* route represents a bcast address */
#define	RTF_MULTICAST	0x800000	/* route represents a mcast address */
#define RTF_ACTIVE_DGD  0x1000000       /* active dead gateway detection on */
#define RTF_STOPSRCH    0x2000000       /* stop search option for group routing */
#define RTF_FREE_IN_PROG	0x4000000	/* rtentry free is in progress */

/*
 * New IPv6 routing flags.
 */
#define RTF_SMALLMTU	0x40000		/* MTU is smaller than the minimum */

#define MFC_PACKET_Q_SIZE	5       /* must be between 1 and 10 */
#define MAX_PACKET_Q_SIZE	7       /* fixed for comparison to rtentry */

/*
 * Routing statistics.
 */
struct	rtstat {
	short	rts_badredirect;	/* bogus redirect calls */
	short	rts_dynamic;		/* routes created by redirects */
	short	rts_newgateway;		/* routes modified by redirects */
	short	rts_unreach;		/* lookups which failed */
	short	rts_wildcard;		/* lookups satisfied by a wildcard */
#if	defined(_KERNEL) && LOCK_NETSTATS
	simple_lock_data_t rts_lock;		/* statistics lock */
#endif
};

/*
 * Structure for routing messages.
 */
struct rt_msghdr {
        u_short rtm_msglen;     /* to skip over non-understood messages */
        u_char  rtm_version;    /* future binary compatability */
        u_char  rtm_type;       /* message type */
        u_short rtm_index;      /* index for associated ifp */
	/* the rtm_pid field should be defined as a pid_t, however a */
	/*  pid_t is unfortunately an int in 64 bit app and a long in 64 */
	/*  kernel.  The most information that can be passed between the */
	/*  two is the 32bit quantity.  This needs to be fixed later, */
	/*  when the definition of pid_t settles down. */
        int 	rtm_pid;        /* identify sender */
        int     rtm_addrs;      /* bitmask identifying sockaddrs in msg */
        int     rtm_seq;        /* for sender to identify action */
        int     rtm_errno;      /* why failed */
        int     rtm_flags;      /* flags, incl. kern & message, e.g. DONE */
        int     rtm_use;        /* from rtentry */
        __ulong32_t  rtm_inits;      /* which metrics we are initializing */
#ifdef _KERNEL
        struct  rt_metrics_compat rtm_rmx; /* metrics themselves */
#else
	struct rt_metrics rtm_rmx; /* metrics themselves */
#endif
};

/*
 * Compat structure for routing messages.  Version will be
 * RTM_VERSION_GR_COMPAT.
 */
struct newrt_msghdr_compat {
	u_short	rtm_msglen;	/* to skip over non-understood messages */
	u_char	rtm_version;	/* future binary compatability */
	u_char	rtm_type;	/* message type */
	u_short	rtm_index;	/* index for associated ifp */
	/* JEM : the rtm_pid field should be defined as a pid_t, however a */
	/*  pid_t is unfortunately an int in 64 bit app and a long in 64 */
	/*  kernel.  The most information that can be passed between the */
	/*  two is the 32bit quantity.  This needs to be fixed if there */
	/*  comes a time that pid_t is consistently defined for apps and */
	/*  the kernel.	 A lot of apps need to change also (route, ndp ... */
        int 	rtm_pid;        /* identify sender */
	int	rtm_addrs;	/* bitmask identifying sockaddrs in msg */
	int	rtm_seq;	/* for sender to identify action */
	int	rtm_errno;	/* why failed */
	int	rtm_flags;	/* flags, incl. kern & message, e.g. DONE */
	int	rtm_use;	/* from rtentry */
	__ulong32_t	rtm_inits;	/* which metrics we are initializing */
#ifdef _KERNEL
	struct	rt_metrics_compat rtm_rmx; /* metrics themselves */
#else
	struct	rt_metrics rtm_rmx; /* metrics themselves */
#endif
	struct 	gidstruct_compat rtm_gidlist; /* gid restriction info */
};

/*
 * New structure for routing messages.  Version must be RTM_VERSION_GR.
 * Some apps may exist which use this structure but use version
 * RTM_VERSION_GR_COMPAT.  So there are checks in route_output to figure
 * out which version of the msghdr structure the app is actually using.
 */
struct newrt_msghdr {
	u_short	rtm_msglen;	/* to skip over non-understood messages */
	u_char	rtm_version;	/* future binary compatability */
	u_char	rtm_type;	/* message type */
	u_short	rtm_index;	/* index for associated ifp */
	/* JEM : the rtm_pid field should be defined as a pid_t, however a */
	/*  pid_t is unfortunately an int in 64 bit app and a long in 64 */
	/*  kernel.  The most information that can be passed between the */
	/*  two is the 32bit quantity.  This needs to be fixed if there */
	/*  comes a time that pid_t is consistently defined for apps and */
	/*  the kernel.	 A lot of apps need to change also (route, ndp ... */
        int 	rtm_pid;        /* identify sender */
	int	rtm_addrs;	/* bitmask identifying sockaddrs in msg */
	int	rtm_seq;	/* for sender to identify action */
	int	rtm_errno;	/* why failed */
	int	rtm_flags;	/* flags, incl. kern & message, e.g. DONE */
	int	rtm_use;	/* from rtentry */
	__ulong32_t	rtm_inits;	/* which metrics we are initializing */
#ifdef _KERNEL
	struct	rt_metrics_compat rtm_rmx; /* metrics themselves */
#else
	struct	rt_metrics rtm_rmx; /* metrics themselves */
#endif
	struct 	gidstruct rtm_gidlist; /* gid restriction info */
};


struct rt_msghdr_policy {
	u_short	rtm_msglen;	/* to skip over non-understood messages */
	u_char	rtm_version;	/* future binary compatability */
	u_char	rtm_type;	/* message type */
	u_short	rtm_index;	/* index for associated ifp */
    int 	rtm_pid;        /* identify sender */
	int	rtm_addrs;	/* bitmask identifying sockaddrs in msg */
	int	rtm_seq;	/* for sender to identify action */
	int	rtm_errno;	/* why failed */
	int	rtm_flags;	/* flags, incl. kern & message, e.g. DONE */
	int	rtm_use;	/* from rtentry */
	__ulong32_t	rtm_inits;	/* which metrics we are initializing */
#ifdef _KERNEL
	struct	rt_metrics_compat rtm_rmx; /* metrics themselves */
#else
	struct	rt_metrics rtm_rmx; /* metrics themselves */
#endif
	struct 	gidstruct rtm_gidlist; /* gid restriction info */
	int	rtm_policy; /* Policy to be associated with route */
	int rtm_weight; /* Weight of the route */
};

#ifdef _KERNEL
struct walkarg {
	int     w_op, w_arg, w_given, w_needed, w_tmemsize;
	caddr_t w_where, w_tmem;
	struct xmem *w_xmd;
	struct  {
		struct rt_msghdr m_rtm;
		char    m_sabuf[128];
	} w_m;
#define w_rtm w_m.m_rtm
};

struct walkarg_gr {
	int     w_op, w_arg;
	int     w_given, w_needed, w_tmemsize;
	caddr_t w_where, w_tmem;
	struct xmem *w_xmd;
	struct  {
		struct newrt_msghdr m_rtm;
		char    m_sabuf[128];
	} w_m;
};
#endif /* _KERNEL */

#define K_GIDLIST 0x00010000	/* passed to getkerninfo() to specify
				   newrt_msghdr				*/

#define RTM_VERSION	2	/* Up the ante and ignore older versions */
#define RTM_VERSION_GR_COMPAT  3 /* This rt_msghdr has gid info w/
				    NGROUPS_MAX == 32 or NGROUPS_MAX == 64;
				    have to check length */
#define RTM_VERSION_GR	4	/*  This rt_msghdr has gid info w/
				    NGROUPS_MAX == 64 */
#define RTM_VERSION_POLICY 5 /*  This rt_msghdr has route policy information
							  *  to be used for configurable multipath routing
							  */
#define RTM_ADD		0x1	/* Add Route */
#define RTM_DELETE	0x2	/* Delete Route */
#define RTM_CHANGE	0x3	/* Change Metrics or flags */
#define RTM_GET		0x4	/* Report Metrics */
#define RTM_LOSING	0x5	/* Kernel Suspects Partitioning */
#define RTM_REDIRECT	0x6	/* Told to use different route */
#define RTM_MISS	0x7	/* Lookup failed on this address */
#define RTM_LOCK	0x8	/* fix specified metrics */
#define RTM_OLDADD	0x9	/* caused by SIOCADDRT */
#define RTM_OLDDEL	0xa	/* caused by SIOCDELRT */
#define RTM_RESOLVE	0xb	/* req to resolve dst to LL addr */
#define RTM_NEWADDR	0xc	/* address being added to iface */
#define RTM_DELADDR	0xd	/* address being removed from iface */
#define RTM_IFINFO	0xe	/* iface going up/down etc. */
#define RTM_EXPIRE	0xf	/* Route has Expired */
#define RTM_RTLOST	0x10	/* Router has been Lost */
#define	RTM_GETNEXT	0x11	/* get next route */
#define RTM_SAMEADDR    0x12    /* Trying to set the same addr */
#define RTM_SET		0x13

#define RTV_MTU		0x1	/* init or lock _mtu */
#define RTV_HOPCOUNT	0x2	/* init or lock _hopcount */
#define RTV_EXPIRE	0x4	/* init or lock _hopcount */
#define RTV_RPIPE	0x8	/* init or lock _recvpipe */
#define RTV_SPIPE	0x10	/* init or lock _sendpipe */
#define RTV_SSTHRESH	0x20	/* init or lock _ssthresh */
#define RTV_RTT		0x40	/* init or lock _rtt */
#define RTV_RTTVAR	0x80	/* init or lock _rttvar */

/*
 * Bitmask values for rtm_addr.
 */
#define RTA_DST		0x1	/* destination sockaddr present */
#define RTA_GATEWAY	0x2	/* gateway sockaddr present */
#define RTA_NETMASK	0x4	/* netmask sockaddr present */
#define RTA_GENMASK	0x8	/* cloning mask sockaddr present */
#define RTA_IFP		0x10	/* interface name sockaddr present */
#define RTA_IFA		0x20	/* interface addr sockaddr present */
#define RTA_AUTHOR	0x40	/* sockaddr for author of redirect */
#define RTA_BRD		0x80	/* for NEWADDR, broadcast or p-p dest addr */
#define RTA_DOWNSTREAM	0x100	/* multicast downstream sockaddr present */

#define	RT_ROUNDUP(sa)	((sa)->sa_len > 0 ? \
				(1 + (((sa)->sa_len-1) | (sizeof(int)-1))) : \
				 sizeof(int))

/*
 * Index offsets for sockaddr array for alternate internal encoding.
 */
#define RTAX_DST	0	/* destination sockaddr present */
#define RTAX_GATEWAY	1	/* gateway sockaddr present */
#define RTAX_NETMASK	2	/* netmask sockaddr present */
#define RTAX_GENMASK	3	/* cloning mask sockaddr present */
#define RTAX_IFP	4	/* interface name sockaddr present */
#define RTAX_IFA	5	/* interface addr sockaddr present */
#define RTAX_AUTHOR	6	/* sockaddr for author of redirect */
#define RTAX_BRD	7	/* for NEWADDR, broadcast or p-p dest addr */
#define RTAX_MAX	8	/* size of array to allocate */

struct dgd_arg {
        struct sockaddr *dst;
        int             active;
};

struct rt_addrinfo {
	int	rti_addrs;
	struct	sockaddr *rti_info[RTAX_MAX];
};

struct route_cb {
        int     ip_count;
        int     ns_count;
        int     iso_count;
        int     any_count;
};

#ifdef _KERNEL

#define NET_CACHELINESIZE       128
/*
 * Including net_globals.h (where NET_CACHELINESIZE is defined) breaks nfs.
 * Hence we redefine NET_CACHELINESIZE here. These should be kept consistent.
 */

extern struct rw_lock *route_lock;
extern int _rtl;
#define ROUTE_READ_LOCK_DECL() int _rrl;
#define ROUTE_LOCK_DECL()
#define ROUTE_ISLOCKED()        1
#define ROUTE_LOCKINIT() \
        RW_LOCKINIT(route_lock, 2*NET_CACHELINESIZE, M_LOCKF, M_WAITOK, LOCK_ALLOC_PIN, \
        ROUTE_LOCK_FAMILY, -1)

#define ROUTE_WRITE_LOCK() RW_WRITE_LOCK(route_lock, _rtl, PL_IMP)

#define ROUTE_WRITE_UNLOCK() {				\
	assert(lock_mine(&(route_lock->simple_lock)));  \
	RW_WRITE_UNLOCK(route_lock, _rtl);		\
}

#define ROUTE_READ_LOCK() RW_READ_LOCK(route_lock, _rtl, PL_IMP, _rrl)

#define ROUTE_READ_UNLOCK() RW_READ_UNLOCK(route_lock, _rrl)

#define ROUTE_READ_UNLOCK_NO_ENABLE() RW_READ_UNLOCK_NO_ENABLE(route_lock)

#define ROUTE_IS_READ_LOCKED() route_lock->read_cnt

#define RTFREE(rt)              rtfree(rt)

#define RTENTRY_LOCKINIT(rt)    { \
        lock_alloc(&rt->rt_lock, LOCK_ALLOC_PIN, RTENTRY_LOCK_FAMILY, -1); \
        simple_lock_init(&rt->rt_lock); \
}

#define RTENTRY_LOCK(rt)        rt->rt_intr = disable_lock(PL_IMP, &rt->rt_lock);
#define RTENTRY_UNLOCK(rt)      unlock_enable(rt->rt_intr, &rt->rt_lock);

simple_lock_data_t	ipforward_rt_lock;
int			_ipfrl;
#define IPFORWARD_RT_LOCKINIT() { \
	lock_alloc(&ipforward_rt_lock, LOCK_ALLOC_PIN, ROUTE_LOCK_FAMILY, -1); \
	simple_lock_init(&ipforward_rt_lock); \
}
#define IPFORWARD_RT_LOCK()	_ipfrl = disable_lock(PL_IMP, &ipforward_rt_lock);
#define IPFORWARD_RT_UNLOCK()	unlock_enable(_ipfrl, &ipforward_rt_lock);

extern	struct	route_cb route_cb;
extern	struct	rtstat	rtstat;
extern struct  radix_node_head *rt_tables[];
extern long route_expire;
/*
 * Values for additional argument to above two functions.
 */
#define ALL_CLONING 0
#define ONNET_CLONING 1
#define NO_CLONING 2

struct dst_and_mask {
	struct sockaddr *dst;
	struct sockaddr *netmask;
};

#endif /* ifdef _KERNEL */
#endif /* ifndef ROUTE_H */
