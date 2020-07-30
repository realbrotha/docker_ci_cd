/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53S src/bos/kernel/net/if.h 1.16.3.51                               */
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
/* @(#)39	1.16.3.51  src/bos/kernel/net/if.h, sockinc, bos53S, s2008_31A6 7/15/08 05:28:35 */
/*
 *   COMPONENT_NAME: SYSNET
 *
 *   FUNCTIONS: IFMULTI_INITLOCK
 *		IFMULTI_LOCK
 *		IFMULTI_LOCK_RECURSIVE
 *		IFMULTI_LOCKINIT
 *		IFMULTI_UNLOCK_RECURSIVE
 *		IFQ_LOCK
 *		IFQ_LOCKINIT
 *		IFQ_UNLOCK
 *		IF_DEQUEUE
 *		IF_DEQUEUE_NOLOCK
 *		IF_DROP
 *		IF_ENQUEUE
 *		IF_ENQUEUE_NOLOCK
 *		IF_PREPEND
 *		IF_PREPEND_NOLOCK
 *		IF_QFULL
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
 * 
 * (c) Copyright 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 * 
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
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
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
 *	Base:	if.h	7.6 (Berkeley) 9/20/89
 *	Merged: if.h	7.9 (Berkeley) 6/28/90
 */

/*
 * Structures defining a network interface, providing a packet
 * transport mechanism (ala level 0 of the PUP protocols).
 *
 * Each interface accepts output datagrams of a specified maximum
 * length, and provides higher level routines with input datagrams
 * received from its medium.
 *
 * Output occurs when the routine if_output is called, with four parameters:
 *	(*ifp->if_output)(ifp, m, dst, ro)
 * Here m is the mbuf chain to be sent and dst is the destination address.
 * The output routine encapsulates the supplied datagram if necessary,
 * and then transmits it on its medium.
 *
 * On input, each interface unwraps the data received by it, and either
 * places it on the input queue of a internetwork datagram routine
 * and posts the associated software interrupt, or passes the datagram to a raw
 * packet input routine.
 *
 * Routines exist for locating interfaces by their addresses
 * or for locating a interface on a certain network, as well as more general
 * routing and gateway routines maintaining information used to locate
 * interfaces.  These routines live in the files if.c and route.c
 */
#ifndef _NET_IF_H
#define _NET_IF_H
#include <standards.h>

#ifdef _ALL_SOURCE

#if	defined(_KERNEL)
#include <net/net_globals.h>
#endif

#ifdef __cplusplus
struct mbuf;
struct ifaddr;
struct sockaddr;
struct rtentry;
#endif

#include <sys/queue.h>
#include <sys/socket.h>

#ifndef	_TIME_
#ifdef	_KERNEL
#include "sys/time.h"
#else
#include <sys/time.h>
#endif
#endif

#include <netinet/in.h>

#ifdef _KERNEL
#include <sys/aacct.h>
#endif /* KERNEL */

struct ifnet;

#include "net/route.h"

/*
 * Used to specify interface specific network
 * options.
 */
struct if_netopts {
	u_long  flags;
	u_long  tcp_sendspace;
	u_long  tcp_recvspace;
	int     tcp_mssdflt;
	int     tcp_nodelay;
	int     rfc1323;
	u_long  tcp_low_rto;
	u_long  spare[10];
};
#define ISNO_DISABLE          0x80000000
#define ISNO_ALL              0x7FFFFFFF

#define ISNO_TCP_SENDSPACE    0x00000001  /* interface specific tcp_sendspace */
#define ISNO_TCP_RECVSPACE    0x00000002
#define ISNO_TCP_MSSDFLT      0x00000008
#define ISNO_TCP_NODELAY      0x00000010
#define ISNO_RFC1323          0x00000020
#define ISNO_TCP_LOW_RTO      0x00000040

#define ISNO_OPT_IS_SET(flags, opt) (((flags & ISNO_ALL) & opt ) == opt)

#define ISNO_SBRESERVE( sb, cc ) {                       \
	sb_max = MAX( cc, sb_max);			 \
	sb.sb_hiwat = cc;                                \
        sb.sb_mbmax = (cc * 2);                          \
        if (MCLBYTES >= 2048)                            \
                sb.sb_mbmax *= (MCLBYTES / 2048);        \
        if (sb.sb_lowat > sb.sb_hiwat)                   \
                sb.sb_lowat = sb.sb_hiwat;               \
}


/*
 * Structure defining a queue for a network interface.
 */

struct ifnet {
	char	*if_name;		/* name, e.g. ``en'' or ``lo'' */
	short	if_unit;		/* sub-unit for lower level driver */
	u_long	if_mtu;			/* maximum transmission unit */
	u_long	if_flags;		/* up/down, broadcast, etc. */
	short	if_timer;		/* time 'til if_watchdog called */
	int	if_metric;		/* routing metric (external only) */
	struct	ifaddr *if_addrlist;	/* linked list of addresses per if */
/* procedure handles */
#ifdef	_KERNEL
	int	(*if_init)(int);
	int	(*if_output)(struct ifnet *, struct mbuf *,
				struct sockaddr *, struct rtentry *);
	int	(*if_start)(struct ifnet *);
	int	(*if_done)(struct ifnet *);
	int	(*if_ioctl)(struct ifnet *, int, caddr_t);
	int	(*if_reset)(int, int);
	int	(*if_watchdog)(int);
#else
	int	(*if_init)();		/* init routine */
	int	(*if_output)();		/* output routine (enqueue) */
	int	(*if_start)();		/* initiate output routine */
	int	(*if_done)();		/* output complete routine */
	int	(*if_ioctl)();		/* ioctl routine */
	int	(*if_reset)();		/* bus reset routine */
	int	(*if_watchdog)();	/* timer routine */
#endif
/* generic interface statistics */
	int	if_ipackets;		/* packets received on interface */
	int	if_ierrors;		/* input errors on interface */
	int	if_opackets;		/* packets sent on interface */
	int	if_oerrors;		/* output errors on interface */
	int	if_collisions;		/* collisions on csma interfaces */
/* end statistics */
	struct	ifnet *if_next;
	u_char	if_type;		/* ethernet, tokenring, etc */
	u_char	if_addrlen;		/* media address length */
	u_char	if_hdrlen;		/* media header length */
	u_char	if_index;		/* numeric abbreviation for this if  */
/* SNMP statistics */
	struct	timeval if_lastchange;	/* last updated */
	int	if_ibytes;		/* total number of octets received */
	int	if_obytes;		/* total number of octets sent */
	int	if_imcasts;		/* packets received via multicast */
	int	if_omcasts;		/* packets sent via multicast */
	int	if_iqdrops;		/* dropped on input, this interface */
	int	if_noproto;		/* destined for unsupported protocol */
	int	if_baudrate;		/* linespeed */
/* netstat -D statistics */
	u_long	if_arpdrops;		/* dropped because no arp response */
	u_int   if_ifbufminsize;        /* Minimum size for interface specific buffers */
	u_short	if_site6;		/* IPv6 Site index */
	u_char if_reserveds;
        u_char ipv6_sug_hlim;           /*suggested IPv6 hop limit for this interface*/
	int	if_reserved[3];		/* reserved for future use */
	int	if_auto_cksum;		/* counter to keep track of TCP dynamic cksum_offload */
	struct  if_netopts *if_isno;
	int	if_options;		/* more flags, but not settable with
					 * ifconfig
					 */
/* stuff for device driver */
        dev_t   devno;                  /* device number */
        chan_t  chan;                   /* channel of mpx device */
	struct	in_multi *if_multiaddrs; /* list of IPv4 multicast addresses */
	int	(*if_tap)();		/* packet tap */
	caddr_t if_tapctl;              /* link for tap (ie BPF) */
	int	(*if_arpres)();		/* arp resolver routine */
	int	(*if_arprev)();		/* Reverse-ARP input routine */
	int	(*if_arpinput)();	/* arp input routine */
	struct	ifqueue {
		struct	mbuf *ifq_head;
		struct	mbuf *ifq_tail;
		long	ifq_len;
		long	ifq_maxlen;
		int	ifq_drops;
#ifndef	_KERNEL
#define simple_lock_data_t long
#define lock_data_t      struct { int a; int b; } 
#endif
		simple_lock_data_t	ifq_slock;
	} if_snd;			/* output queue */
	simple_lock_data_t	if_slock;	/* statistics lock */
        simple_lock_data_t	if_multi_lock;
        simple_lock_data_t	if6_multi_lock;
        simple_lock_data_t	if_addrlist_lock;
	struct gidstruct *if_gidlist;

	/* NDP support on IPv6 */
	/* HW independent functions */
	int     (*if_ip6tomcast)();       /* map IPv6 addrs to hw */
					  /* multicast addrs*/
	int     (*if_ndp_bcopy)();        /* copy hw addrs */
	int     (*if_ndp_bcmp)();         /* compare hw addrs */
	u_int	if_ndtype;		  /* IPv6 neighbor discovery type */
	LIST_HEAD(if_multiaddrs6, in6_multi) if_multiaddrs6;
					 /* list of IPv6 multicast addresses */
	u_long	if_desired_mtu;		/* desired maximum transmission unit */
        struct ifnet *if_vipaxface;       /* pointer to vipa interface  */
#ifdef _KERNEL
	tran_netif_t	tran_netif;	/* adv acct netif stats */
#else
	long long	tran_netif[4]; /* tran_netif_t is 32 bytes on 32-bit & 64-bit */
#endif /* _KERNEL */
	ulong	if_htoken;		/* adv acct registration token */
					/*  on the ifnet */

	/* Information about offload capabilities of the adapter */
	union {			            
    		u_long      offload_flags;  /* Bit flags */
    		caddr_t     offload_ptr;    /* Future ptr to external struct */
	} if_offload_info;		  
#define if_offld_flags if_offload_info.offload_flags
};


#define IFMULTI_LOCK_DECL()	  int 	_ifml;
#define IFMULTI_LOCK(ifp)	  _ifml = disable_lock(PL_IMP, &(ifp)->if_multi_lock)
#define IFMULTI_UNLOCK(ifp)       unlock_enable(_ifml, &(ifp)->if_multi_lock)
#define IFMULTI_INITLOCK(ifp) {						\
	lock_alloc(&(ifp)->if_multi_lock, LOCK_ALLOC_PIN, \
		IFMULTI_LOCK_FAMILY, (short32uint64_t)ifp); \
	simple_lock_init(&(ifp)->if_multi_lock); 			\
} 
#define IFMULTI_LOCK_RECURSIVE(ifp)	  IFMULTI_LOCK(ifp)
#define IFMULTI_UNLOCK_RECURSIVE(ifp)     IFMULTI_UNLOCK(ifp)
#define IF6MULTI_LOCK_DECL()	  int 	_if6ml;
#define IF6MULTI_LOCK(ifp)	  _if6ml = disable_lock(PL_IMP, &(ifp)->if6_multi_lock)
#define IF6MULTI_UNLOCK(ifp)       unlock_enable(_if6ml, &(ifp)->if6_multi_lock)
#define IF6MULTI_INITLOCK(ifp) {			\
	lock_alloc(&(ifp)->if6_multi_lock, LOCK_ALLOC_PIN, \
		IF6MULTI_LOCK_FAMILY, (short32uint64_t)ifp); \
	simple_lock_init(&(ifp)->if6_multi_lock); 			\
} 
#define IF6MULTI_LOCK_RECURSIVE(ifp)	  IF6MULTI_LOCK(ifp)
#define IF6MULTI_UNLOCK_RECURSIVE(ifp)     IF6MULTI_UNLOCK(ifp)
#define IFADDRLIST_LOCK_DECL()	  int 	_ifal;
#define IFADDRLIST_WRITE_LOCK(ifp)	  _ifal = disable_lock(PL_IMP, &(ifp)->if_addrlist_lock)
#define IFADDRLIST_READ_LOCK(ifp)	  _ifal = disable_lock(PL_IMP, &(ifp)->if_addrlist_lock)
#define IFADDRLIST_UNLOCK(ifp)       unlock_enable(_ifal, &(ifp)->if_addrlist_lock)
#define IFADDRLIST_INITLOCK(ifp) {			\
	lock_alloc(&(ifp)->if_addrlist_lock, LOCK_ALLOC_PIN, \
		IFADDRLIST_LOCK_FAMILY, (short32uint64_t)ifp); \
	simple_lock_init(&(ifp)->if_addrlist_lock); 			\
} 

#ifndef IFF_UP
#define	IFF_UP		0x1		/* interface is up */
#endif
#define	IFF_BROADCAST	0x2		/* broadcast address valid */
#define	IFF_DEBUG	0x4		/* turn on debugging */
#define	IFF_LOOPBACK	0x8		/* is a loopback net */
#define	IFF_POINTOPOINT	0x10		/* interface is point-to-point link */
#define	IFF_VIPA	0x80000000	/* interface is virtual interface */
#define	IFF_NOTRAILERS	0x20		/* avoid use of trailers */
#ifndef IFF_RUNNING
#define	IFF_RUNNING	0x40		/* resources allocated */
#endif
#define	IFF_NOARP	0x80		/* no address resolution protocol */
#define	IFF_PROMISC	0x100		/* receive all packets */
#define	IFF_ALLMULTI	0x200		/* receive all multicast packets */
#define	IFF_OACTIVE	0x400		/* transmission in progress */
#define	IFF_SIMPLEX	0x800		/* can't hear own transmissions */

#define IFF_DO_HW_LOOPBACK  0x10000	/* force loopback thru hardware */
#define	IFF_ALLCAST	0x20000		/* global broadcast		 */
#define	IFF_BRIDGE	0x40000		/* receive all bridge packets */
#define	IFF_NOECHO	IFF_SIMPLEX	/* receives echo packets */
#define IFF_BPF		0x8000000	/* bpf is supported for this IF */

/* Device-specific flags */
#define IFF_D1		0x8000
#define IFF_D2		0x4000
#define IFF_D3		0x2000
#define IFF_D4		0x1000
#define IFF_SNAP	IFF_D1		/* Ethernet driver outputs SNAP hdr */

#define	IFF_LINK0	0x100000
#define	IFF_LINK1	0x200000
#define	IFF_LINK2	0x400000

#define IFF_TCP_NOCKSUM	0x1000000	/* TCP: Disable TCP chksums for 
					 * local subnet traffic */
#define	IFF_IFBUFMGT	0x800000	/* Indicates Buf Mgt Support by the 	*/
					/* Interface				*/

#define IFF_GROUP_ROUTING 0x2000000     /* supports group routing */
#define IFF_64BIT       0x4000000       /* 64-bit safe */
#define IFF_CHECKSUM_OFFLOAD 0x10000000	/* Admin requests checksum offload.*/
#define IFF_TCP_DISABLE_CKSUM 0x20000000 /* Disable TCP checksum completely */
#define IFF_PSEG	0x40000000	/* supports private segments */

#define	IFF_MULTICAST	0x80000		/* supports multicast */
/*
 * The IFF_MULTICAST flag indicates that the network can support the
 * transmission and reception of higher-level (e.g., IP) multicast packets.
 * It is independent of hardware support for multicasting; for example,
 * point-to-point links or pure broadcast networks may well support
 * higher-level multicasts.
 */

#define	IFF_CANTCHANGE	\
	(IFF_BROADCAST|IFF_POINTOPOINT|IFF_SIMPLEX|IFF_RUNNING|IFF_OACTIVE|IFF_MULTICAST)

/* IFNET options (if_options field) */
#define	IFO_FLUSH	0x00000001	/* flush packet from cache before
					   calling if_output */
#define	IFO_HIGHFUNC_QOS 0x00000002	/* Full QOS scheduling support */
#define	IFO_MEDFUNC_QOS	 0x00000004	/* Medium QOS scheduling support */
#define	IFO_MINFUNC_QOS	 0x00000008	/* Minimum QOS scheduling support */
#define IFO_QOS		(IFO_HIGHFUNC_QOS|IFO_MEDFUNC_QOS|IFO_MINFUNC_QOS)
					/* This IFNET supports QOS extensions */
#define	IFO_THREAD	0x00000020	/* thread processing support */
#define	IFO_LARGESEND	0x00000040	/* galaxy largesend support */
#define	IFO_PKTCHAIN	0x00000080	/* packet chain support */
#define IFO_AACCT	0x00000100	/* Advanced accounting is set on ifp */
#define IFO_MONITOR	0x00000200	/* Link Status monitoring is set on i/f */
#define IFO_VIRTUAL_ETHERNET 0x00000400  /* Underlying adapter is Virtual Ethernet */

/*
 * Multiprocessor queue locking.
 *
 * Note that the IF_QFULL and IF_DROP macros become racy in an mp environment.
 * The exact number of ifq_drops probably isn't important; on the other hand,
 * it is possible that an unlocked ifq could grow larger than its declared
 * ifq_maxlen as processors race between IF_QFULL and IF_ENQUEUE.  However,
 * it is still ABSOLUTELY NECESSARY that modification of ifq_len be locked!
 *
 */
#define IFQ_LOCK_DECL()		int	_qs;
#define IFQ_LOCKINIT(ifq) {						\
	lock_alloc(&((ifq)->ifq_slock), LOCK_ALLOC_PIN, IFQ_LOCK_FAMILY, \
		(short32uint64_t)(ifq));\
	simple_lock_init(&((ifq)->ifq_slock));				\
}
#define IFQ_LOCK(ifq)		_qs = disable_lock(PL_IMP ,&((ifq)->ifq_slock))
#define IFQ_UNLOCK(ifq)		unlock_enable(_qs, &((ifq)->ifq_slock))

/*
 * Output queues (ifp->if_snd) and internetwork datagram level (pup level 1)
 * input routines have queues of messages stored on ifqueue structures
 * (defined above).  Entries are added to and deleted from these structures
 * by these macros, which should be called with ipl raised to splimp().
 */
#define	IF_QFULL(ifq)		((ifq)->ifq_len >= (ifq)->ifq_maxlen)
#define	IF_DROP(ifq)		((ifq)->ifq_drops++)
#define	IF_ENQUEUE_NOLOCK(ifq, m) { \
	(m)->m_nextpkt = 0; \
	if ((ifq)->ifq_tail == 0) \
		(ifq)->ifq_head = m; \
	else \
		(ifq)->ifq_tail->m_nextpkt = m; \
	(ifq)->ifq_tail = m; \
	(ifq)->ifq_len++; \
}
#define	IF_ENQUEUE(ifq, m) { \
	IFQ_LOCK(ifq); \
	IF_ENQUEUE_NOLOCK(ifq, m); \
	IFQ_UNLOCK(ifq); \
}
#define	IF_PREPEND_NOLOCK(ifq, m) { \
	(m)->m_nextpkt = (ifq)->ifq_head; \
	if ((ifq)->ifq_tail == 0) \
		(ifq)->ifq_tail = (m); \
	(ifq)->ifq_head = (m); \
	(ifq)->ifq_len++; \
}
#define	IF_PREPEND(ifq, m) { \
	IFQ_LOCK(ifq); \
	IF_PREPEND_NOLOCK(ifq, m); \
	IFQ_UNLOCK(ifq); \
}
#define	IF_DEQUEUE_NOLOCK(ifq, m) { \
	(m) = (ifq)->ifq_head; \
	if (m) { \
		if (((ifq)->ifq_head = (m)->m_nextpkt) == 0) \
			(ifq)->ifq_tail = 0; \
		(m)->m_nextpkt = 0; \
		(ifq)->ifq_len--; \
	} \
}
#define	IF_DEQUEUE(ifq, m) { \
	IFQ_LOCK(ifq); \
	IF_DEQUEUE_NOLOCK(ifq, m); \
	IFQ_UNLOCK(ifq); \
}

#define	IFQ_MAXLEN	50
#define IFQ_SIZE	23
#define IFQ_QARRAY_SIZE	((2 * IFQ_MAXLEN * IFQ_SIZE) + 1)
/* The queue of ipintrqs can't have more than MAXLEN elements at
   any time for each queue; hence no need to allocate too much
   more - htis assumes we do a dequeue for every insert and so
   forth - has to be done carefully in the presence of off level
   interrupt handlers which coalesces operations (i.e. doesn't
   scheudle one) if one is already running.
*/
#define	IFNET_SLOWHZ	1		/* granularity is 1 second */


/* lock for manipulating the array which keeps track of the next
   index of the ifq that will process the next packet for loopback
*/
extern simple_lock_data_t	ipintrq_qarray_lock;

/* actual array which keeps track of the index of ifq to which last
   packet was queued
*/
extern long * ipintrq_qarray;

/* size of queue-array */
extern long ifq_qarray_size;

/* front & back & overlap of queue-array */
extern long ipintrq_qarray_front;
extern long ipintrq_qarray_rear;
extern long ipintrq_qarray_overflow;


#define IFQ_QARRAY_LOCK_DECL()		int	_qarray;
#define IFQ_QARRAY_LOCKINIT() {						\
	simple_lock_init(&(ipintrq_qarray_lock));			\
}
#define IFQ_QARRAY_LOCK(ipintrq_qarray_lock)	_qarray = disable_lock(PL_IMP , \
		&(ipintrq_qarray_lock))
#define IFQ_QARRAY_UNLOCK(ipintrq_qarray_lock)	unlock_enable(_qarray, \
		&(ipintrq_qarray_lock))



/*
 * The ifaddr structure contains information about one address
 * of an interface.  They are maintained by the different address families,
 * are allocated and attached when an address is set, and are linked
 * together so all addresses for an interface can be located.
 */
struct ifaddr {
	struct	sockaddr *ifa_addr;	/* address of interface */
	struct	sockaddr *ifa_dstaddr;	/* other end of p-to-p link */
#define	ifa_broadaddr	ifa_dstaddr	/* broadcast address interface */
	struct	sockaddr *ifa_netmask;	/* used to determine subnet */
	struct	ifnet *ifa_ifp;		/* back-pointer to interface */
	struct	ifaddr *ifa_next;	/* next address for interface */
#ifdef	_KERNEL
	void	(*ifa_rtrequest)(int, struct rtentry *, struct sockaddr *);
#else
	void	(*ifa_rtrequest)();	/* check or clean routes (+ or -)'d */
#endif
	struct	rtentry *ifa_rt;	/* ??? for ROUTETOIF */
	u_short	ifa_flags;		/* mostly rt_flags for cloning */
	short	ifa_refcnt;		/* extra to malloc for link info */
};

/*
 * Message format for use in obtaining information about interfaces
 * from getkerninfo and the routing socket
 */
struct if_msghdr {
        u_short ifm_msglen;     /* to skip over non-understood messages */
        u_char  ifm_version;    /* future binary compatability */
        u_char  ifm_type;       /* message type */
        int     ifm_addrs;      /* like rtm_addrs */
        int     ifm_flags;      /* value of if_flags */
        u_short ifm_index;      /* index for associated ifp */
	u_char	ifm_addrlen;	/* MAC address length */
};

/*
 * Message format for use in obtaining information about interface addresses
 * from getkerninfo and the routing socket
 */
struct ifa_msghdr {
        u_short ifam_msglen;    /* to skip over non-understood messages */
        u_char  ifam_version;   /* future binary compatability */
        u_char  ifam_type;      /* message type */
        int     ifam_addrs;     /* like rtm_addrs */
        int     ifam_flags;     /* value of ifa_flags */
        u_short ifam_index;     /* index for associated ifp */
};

#define IFA_ROUTE	RTF_UP		/* route installed */
/*
 * Interface request structure used for socket
 * ioctl's.  All interface ioctl's must have parameter
 * definitions which begin with ifr_name.  The
 * remainder may be interface specific.
 */
struct	ifreq {
#ifndef IFNAMSIZ	/* Also in net_if.h */
#define	IFNAMSIZ	16  
#endif
	char	ifr_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	union {
		struct	sockaddr ifru_addr;
		struct	sockaddr ifru_dstaddr;
		struct	sockaddr ifru_broadaddr;
		__ulong32_t	ifru_flags;
		int	ifru_metric;
		caddr_t	ifru_data;
		u_short	ifru_site6;
		__ulong32_t   ifru_mtu;
		int     ifru_baudrate;
		int	ifru_checksum_offload[2];
	} ifr_ifru;
#define	ifr_addr	ifr_ifru.ifru_addr	/* address */
#define	ifr_dstaddr	ifr_ifru.ifru_dstaddr	/* other end of p-to-p link */
#define	ifr_broadaddr	ifr_ifru.ifru_broadaddr	/* broadcast address */
#define	ifr_flags	ifr_ifru.ifru_flags	/* flags */
#define	ifr_metric	ifr_ifru.ifru_metric	/* metric */
#define	ifr_data	ifr_ifru.ifru_data	/* for use by interface */
#define	ifr_site6	ifr_ifru.ifru_site6	/* IPv6 site index */
#define ifr_mtu         ifr_ifru.ifru_mtu       /* mtu of interface */
#define ifr_isno        ifr_ifru.ifru_data      /* pointer to if_netopts */
#define ifr_baudrate    ifr_ifru.ifru_baudrate  /* baudrate of interface */
#define ifr_checksum_offload    ifr_ifru.ifru_checksum_offload[1]  /* checksum offload active or not */
};

struct ifgidreq {
        char ifrg_name[IFNAMSIZ];               /* if name, e.g. "en0" */
        struct gidstruct ifrg_gidlist;          /* gidlist for incoming pkts */
};

struct ifaliasreq {
	char	ifra_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	struct	sockaddr ifra_addr;
	struct	sockaddr ifra_broadaddr;
	struct	sockaddr ifra_mask;
};

struct  oifreq {
        char    ifr_name[IFNAMSIZ];             /* if name, e.g. "en0" */
        union {
                struct  sockaddr ifru_addr;
                struct  sockaddr ifru_dstaddr;
                struct  sockaddr ifru_broadaddr;
                __long32_t    ifru_flags;
                int     ifru_metric;
                caddr_t ifru_data;
                __ulong32_t  ifru_mtu;
        } ifr_ifru;
        u_char  reserved[8];
};

struct ifvireq {
        char    ifrv_name[IFNAMSIZ];
        u_int   ifrv_numif;
        char    (*ifrv_ifname)[IFNAMSIZ];
};

struct ifibreq {/* For SIOCIF_IB_GET_INFO command */
    char        ifr_name[IFNAMSIZ];
    uint        qkey; /* The Mcast group's QKey */
    uint        pmtu; /*The Mcast groups MTU */
    uchar       res[96];
};


/*
 * Structure used in SIOCGIFCONF request.
 * Used to retrieve interface configuration
 * for machine (useful for programs which
 * must know all networks accessible).
 */
struct	ifconf {
	int	ifc_len;		/* size of associated buffer */
	union {
		caddr_t	ifcu_buf;
		struct	ifreq *ifcu_req;
	} ifc_ifcu;
#define	ifc_buf	ifc_ifcu.ifcu_buf	/* buffer address */
#define	ifc_req	ifc_ifcu.ifcu_req	/* array of structures returned */
};


struct	ifreqaddrs {
	char	ifr_name[IFNAMSIZ];	/* if name, e.g. "en0" */
	int	ifaddrs;		/* returned number of address on if */
	int	naddrs;			/* number of addresses returned in req*/
	union {
		struct sockaddr_in 	addr_in;
		struct sockaddr_in6 	addr_in6;
	} ifrasu[1];
};


#endif /* ALL_SOURCE */

/* The following section covers standard content. */
#if _POSIX_C_SOURCE >= 200112L
/* for IPv6 advanced API */

struct if_nameindex {
	unsigned int	 if_index;	/* 1, 2, ... */
	char		*if_name;	/* null terminated name */
};


unsigned int	if_nametoindex (const char *);
char	*if_indextoname (unsigned int, char *);
struct if_nameindex	*if_nameindex (void);
void	if_freenameindex (struct if_nameindex *);

#ifndef _IF_NAMESIZE_D
#define _IF_NAMESIZE_D
#define IF_NAMESIZE     16
#endif
#endif  /* _POSIX_C_SOURCE */

#ifdef _ALL_SOURCE
#ifdef	_KERNEL
#include "net/if_arp.h"
extern struct	ifnet *ifnet, loif;
extern simple_lock_data_t	ifa_refcnt_lock;
#define IFAREFCNT_LOCK_DECL()	int	_ifa_refcnt;
#define IFAREFCNT_LOCK()	_ifa_refcnt = disable_lock(PL_IMP, &ifa_refcnt_lock);
#define IFAREFCNT_UNLOCK()	unlock_enable(_ifa_refcnt, &ifa_refcnt_lock);
extern void ifafree(struct ifaddr *);

#define IFAFREE(ifa) \
	(ifa)->ifa_refcnt--

/*
 * We are commenting this one again, since there is a ifa_refcnt problem where some routes
 * continue to point to the ifa even after it gets freed after the refcnt gets to zero.
#define IFAFREE(ifa) \
	(ifa)->ifa_refcnt--; \
	if (((ifa)->ifa_refcnt) <= 0) \
		NET_FREE((ifa), M_IFADDR);
*/

#else
#include <net/if_arp.h>
#endif

/* 
 * These defines should not be used.  They are here for compatibility with
 * previous releases.  Please use types defined in <net/if_types.h>.
 */
#ifndef _NET_IF_TYPES_H
#include "net/if_types.h"
#endif

#define UCAST_TYPE	1
#define NUCAST_TYPE	2

#define OTHER_TYPE      IFT_OTHER               /* other network type */
#define REGULAR1822     IFT_1822
#define HDH1822         IFT_HDH1822
#define DDN_X25         IFT_X25DDN
#define RFC877_X25      IFT_X25
#define ETHERNET_CSMACD IFT_ETHER
#define ISO88023_CSMACD IFT_ISO88023
#define ISO88024_TOKBUS IFT_ISO88024
#define ISO88025_TOKRNG IFT_ISO88025
#define ISO88026_MAN    IFT_ISO88026
#define STARLAN         IFT_STARLAN
#define PROTEON_10MBIT  IFT_P10
#define PROTEON_80MBIT  IFT_P80
#define HYPERCHANNEL    IFT_HY
#define FDDI            IFT_FDDI
#define LAPB            IFT_LAPB
#define SDLC            IFT_SDLC
#define T1_CARRIER      IFT_T1
#define CEPT            IFT_CEPT              /* European equivalent of T-1 */
#define BASICISDN       IFT_ISDNBASIC
#define PRIMARYISDN     IFT_ISDNPRIMARY
#define PROPPTPSERIAL   IFT_PTPSERIAL              /* Proprietary Serail */

#ifdef _KERNEL

/* 
 * Interface-specific internal-use ioctls.   Note that the first two are
 * declared in sys/cdli.h.  For compatibility, they will remain there.
 */

#ifndef _H_IOCTL
#include <sys/ioctl.h>
#endif

#define IFIOCTL_MREG		_IO('I', 3)   	/* Register for buffer mgmt */
#define IFIOCTL_MGET		_IO('I', 4)   	/* Get buffer from interface */
#define IFIOCTL_QOS		_IO('I', 5)   	/* QOS reservation function */

/*
 * Used for interface-specific buffer management.  Allows socket layer
 * to allocate buffers tuned for high-performance interfaces.
 */
struct ifmgetr {
	int	size;		/* Size requested, size allocated on return */
	struct mbuf *m;		/* Pointer to mbuf allocated */
	int	wait;		/* M_WAIT or M_DONTWAIT */
};
#endif /* _KERNEL */
#endif /* _ALL_SOURCE */
#endif /* _NET_IF_H */

