/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernext/inet/in.h 1.60.2.1                              */
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
/* @(#)47	1.60.2.1  src/bos/kernext/inet/in.h, sockinc, bos53J, j2006_21D6 5/4/06 09:54:40 */
/*
 *   COMPONENT_NAME: SYSXINET
 *
 *   FUNCTIONS: IN_BADCLASS
 *		IN_CLASSA
 *		IN_CLASSB
 *		IN_CLASSC
 *		IN_CLASSD
 *		IN_EXPERIMENTAL
 *		IN_MULTICAST
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
 *      Base:   in.h    7.8 (Berkeley) 9/13/89
 *      Merged: in.h    7.10 (Berkeley) 6/28/90
 */

#ifndef	_NETINET_IN_H_
#define	_NETINET_IN_H_

#include <standards.h>			/* for standards macros */


#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>

/*
 * socklen_t also has a similar definition in sys/socket.h
 * If we need to change this typedef, it must be changed
 * in sys/socket.h also
 */
#ifndef __SOCKLEN_T
#define __SOCKLEN_T
typedef __ulong32_t socklen_t;
#endif

/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981.
 */

#if _XOPEN_SOURCE_EXTENDED == 1

/*
 * COSE defines the following types here, arpa/inet.h and netdb.h.
 * The define will ensure that an application only defines it once.
 */
#ifndef _IP_TYPES_T
typedef uint16_t	in_port_t;	/* unsigned 16 bit integral */ 
typedef uint32_t	in_addr_t;	/* unsigned 32 bit integral */
#define _IP_TYPES_T
#endif /* _IP_TYPES_T */

/*
 * Internet address (a structure for historical reasons)
 */

#ifndef _IN_ADDR_STRUCT 
struct in_addr {
	in_addr_t	s_addr;
};
#define _IN_ADDR_STRUCT
#endif /* _IN_ADDR_STRUCT */

#if !defined(_ALL_SOURCE)
/*
* IPv6 address
*/
#ifndef _IN6_ADDR_STRUCT
struct in6_addr {
	union {
		uint32_t s6_addr32[4];
#ifdef notyet
		uint64_t s6_addr64[2];
#endif /* notyet */
		uint16_t s6_addr16[8];
		uint8_t  s6_addr8[16];
	} s6_addr;
};
#define s6_addr32       s6_addr.s6_addr32
#ifdef notyet
#define s6_addr64       s6_addr.s6_addr64
#endif /* notyet */
#define s6_addr16       s6_addr.s6_addr16
#define s6_addr8        s6_addr.s6_addr8
#define s6_addr         s6_addr.s6_addr8
#define INET6_ADDRSTRLEN        46
#define _IN6_ADDR_STRUCT
#endif /* _IN6_ADDR_STRUCT */

#ifndef _KERNEL
extern const struct in6_addr in6addr_any, in6addr_loopback;
#endif
#endif /* !ALL_SOURCE */
		
#ifndef _SA_FAMILY_T
#define _SA_FAMILY_T
typedef uchar_t sa_family_t;
#endif

/*
 * Socket address, internet style.
 */
struct sockaddr_in {
	uchar_t	       sin_len;
	sa_family_t    sin_family;
	in_port_t      sin_port;
	struct in_addr sin_addr;
	uchar_t	       sin_zero[8];
};

#if !defined(_ALL_SOURCE)

/*
 * Socket address, IPv6 style.
 */
struct sockaddr_in6 {
	uchar_t          sin6_len;
	uchar_t          sin6_family;
	uint16_t       sin6_port;
	uint32_t       sin6_flowinfo;
	struct          in6_addr        sin6_addr;
	uint32_t        sin6_scope_id;  /* set of interfaces for a scope */
};
#endif /* !ALL_SOURCE */


/*
 * Protocols
 */
#define	IPPROTO_IP		0		/* dummy for IP */
#define	IPPROTO_HOPOPTS		0		/* IPv6 Hop-by-Hop options */
#define	IPPROTO_ICMP		1		/* control message protocol */
#define	IPPROTO_IGMP		2		/* group mgmt protocol */
#define	IPPROTO_GGP		3		/* gateway^2 (deprecated) */
#define IPPROTO_IPIP		4		/* IP inside IP */
#define	IPPROTO_TCP		6		/* tcp */
#define	IPPROTO_EGP		8		/* exterior gateway protocol */
#define	IPPROTO_PUP		12		/* pup */
#define	IPPROTO_UDP		17		/* user datagram protocol */
#define	IPPROTO_IDP		22		/* xns idp */
#define	IPPROTO_TP		29 		/* tp-4 w/ class negotiation */
#define	IPPROTO_IPV6		41 		/* IPv6 into IPv4 */
#define IPPROTO_ROUTING		43		/* IPv6 Routing header */
#define IPPROTO_FRAGMENT	44		/* IPv6 fragmentation header */
#define IPPROTO_QOS		45		/* Quality of Service */
#define	IPPROTO_RSVP		46 		/* resource reservation */
#define IPPROTO_GRE		47
#define	IPPROTO_ESP		50 		/* encap security payload */
#define	IPPROTO_AH		51 		/* authentication header */
#define	IPPROTO_ICMPV6		58 		/* ICMPv6/IGMPv6/NDPv6 */
#define	IPPROTO_NONE		59		/* IPv6 no next header */
#define	IPPROTO_DSTOPTS		60		/* IPv6 Destination options */
#define	IPPROTO_LOCAL		63		/* any local network */
#define	IPPROTO_EON		80		/* ISO cnlp */
#define IPPROTO_BIP		0x53		/* Banyan Vines */
#define IPPROTO_SCTP    132			/* SCTP */
#define IPPROTO_MH		135		/* IPv6 Mobility Header */
#define	IPPROTO_RAW		255		/* raw IP packet */
#define	IPPROTO_MAX		256

#define	INADDR_ANY		(uint32_t)0x00000000
#define	INADDR_BROADCAST	(uint32_t)0xffffffff	/* must be masked */
#ifndef _KERNEL
#define	INADDR_NONE		0xffffffff		/* -1 return */
#endif

/*
 * Local port number conventions:
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).
 * Ports > IPPORT_USERRESERVED are reserved
 * for servers, not necessarily privileged.
 */
#define	IPPORT_RESERVED		1024
#define	IPPORT_USERRESERVED	5000
#define IPPORT_TIMESERVER       37

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */
#define	IN_CLASSA(i)		(((int32_t)(i) & 0x80000000) == 0)
#define	IN_CLASSA_NET		0xff000000
#define	IN_CLASSA_NSHIFT	24
#define	IN_CLASSA_HOST		0x00ffffff
#define	IN_CLASSA_MAX		128

#define	IN_CLASSB(i)		(((int32_t)(i) & 0xc0000000) == 0x80000000)
#define	IN_CLASSB_NET		0xffff0000
#define	IN_CLASSB_NSHIFT	16
#define	IN_CLASSB_HOST		0x0000ffff
#define	IN_CLASSB_MAX		65536

#define	IN_CLASSC(i)		(((int32_t)(i) & 0xe0000000) == 0xc0000000)
#define	IN_CLASSC_NET		0xffffff00
#define	IN_CLASSC_NSHIFT	8
#define	IN_CLASSC_HOST		0x000000ff

#define	IN_CLASSD(i)		(((int32_t)(i) & 0xf0000000) == 0xe0000000)
#define	IN_MULTICAST(i)		IN_CLASSD(i)

#define	IN_CLASSD_NET		0xf0000000	/* These ones aren't really */
#define	IN_CLASSD_NSHIFT	28		/* net and host fields, but */
#define	IN_CLASSD_HOST		0x0fffffff	/* routing needn't know.    */
#define	INADDR_UNSPEC_GROUP	(uint32_t)0xe0000000	/* 224.0.0.0   */
#define	INADDR_ALLHOSTS_GROUP	(uint32_t)0xe0000001	/* 224.0.0.1   */
#define	INADDR_ALLRTRS_GROUP	(uint32_t)0xe0000002	/* 224.0.0.2   */
#define	INADDR_MAX_LOCAL_GROUP 	(uint32_t)0xe00000ff	/* 224.0.0.255 */

#define	IN_EXPERIMENTAL(i)	(((int32_t)(i) & 0xe0000000) == 0xe0000000)
#define	IN_BADCLASS(i)		(((int32_t)(i) & 0xf0000000) == 0xf0000000)


#define	IN_LOOPBACKNET		127			/* official! */


/*
 * Options for use with [gs]etsockopt at the IP level.
 * First word of comment is data type; bool is stored in int.
 */
#define	IP_OPTIONS	1	/* buf/ip_opts; set/get IP per-packet options */
#define	IP_HDRINCL	2	/* int; header is included with data (raw) */
#define	IP_TOS		3	/* int; IP type of service and precedence */
#define	IP_TTL		4	/* int; IP time to live */
#define	IP_UNICAST_HOPS		IP_TTL
#define	IP_RECVOPTS	5	/* bool; receive all IP options w/datagram */
#define	IP_RECVRETOPTS	6	/* bool; receive IP options for response */
#define	IP_RECVDSTADDR	7	/* bool; receive IP dst addr w/datagram */
#define	IP_RETOPTS	8	/* ip_opts; set/get IP per-packet options */
#define	IP_MULTICAST_IF		9	/* set/get IP multicast interface  */
#define	IP_MULTICAST_TTL	10	/* set/get IP multicast timetolive */
#define IP_MULTICAST_HOPS	IP_MULTICAST_TTL
#define	IP_MULTICAST_LOOP	11	/* set/get IP multicast loopback   */
#define	IP_ADD_MEMBERSHIP	12	/* add  an IP group membership     */
#define	IP_DROP_MEMBERSHIP	13	/* drop an IP group membership     */
#define IP_RECVMACHDR		14	/* bool; receive MAC hdr w/datagram */
#define IP_RECVIFINFO		15	/* bool; receive IFNET addr */
#define IP_BROADCAST_IF		16	/* set/get IP all points broadcast IF */
#define IP_DHCPMODE		17	/* Used by DHCP */
#define IP_RECVIF		20
#define IP_ADDRFORM		22	/* int; get/set form of returned addrs */
#define	IP_DONTFRAG		25
#define	IP_FINDPMTU		26
#define IP_PMTUAGE		27
/* Options 28 to 31 moved to _ALL_SOURCE block. */
#define IP_RECVINTERFACE        32   /* bool; receive inbound interface */
/* Option 33 moved to _ALL_SOURCE block. */
#define IP_RECVTTL		34   /* int; receive TTL/hlim */
/* Option 35 moved to _ALL_SOURCE block. */

#define	IP_DEFAULT_MULTICAST_TTL   1	/* normally limit m'casts to 1 hop  */
#define	IP_DEFAULT_MULTICAST_LOOP  1	/* normally hear sends if a member  */

#define	IP_INC_MEMBERSHIPS         20	/* ip_max_membership is incremented by this value to support unlimited multicast group per socket */
#define	IP_INIT_MEMBERSHIP         20	/* ip_max_membership is initialized to 20 */

/* 
 * UNIX 98 says thiese should be available here, in addition to in arpa/inet.h.
 */
#if (_XOPEN_SOURCE >= 500)

#ifdef  _NO_PROTO

#ifndef htonl
uint16_t ntohs(), htons();
uint32_t  ntohl(), htonl();
#endif

#else   /* POSIX required prototypes */

#ifndef htonl
uint16_t ntohs(uint16_t);
uint16_t htons(uint16_t);
uint32_t ntohl(uint32_t);
uint32_t htonl(uint32_t);
#endif

#endif /* _NO_PROTO */
#endif /* _XOPEN_SOURCE == 500 */
#endif /* _XOPEN_SOURCE_EXTENDED */


#ifdef _ALL_SOURCE

/* If all source, optimize the big endian code to do nothing. */
#include <sys/machine.h>

/* For all source, define htonll and ntohll macros */
#ifdef  _NO_PROTO

#ifndef htonll
uint64_t  ntohll(), htonll();
#endif

#else   /* POSIX required prototypes */

#ifndef htonll
uint64_t ntohll(uint64_t);
uint64_t htonll(uint64_t);
#endif

#endif /* _NO_PROTO */

#if BYTE_ORDER == BIG_ENDIAN
#ifndef htonll
#define htonll(hostlong) (hostlong)
#endif
#ifndef htonl
#define htonl(hostlong)  (hostlong)
#endif
#ifndef htons
#define htons(hostshort) (unsigned short)(hostshort)
#endif
#ifndef ntohll
#define ntohll(netlong)  (netlong)
#endif
#ifndef ntohl
#define ntohl(netlong)   (netlong)
#endif
#ifndef ntohs
#define ntohs(netshort)  (unsigned short)(netshort)
#endif
#endif

#ifdef	_AIX
#define INADDR_LOOPBACK         (uint32_t)0x7f000001      /* local loopback */
#endif

/* Added for ndpd-router and the like */
#define IPV6_TOKEN_LENGTH	64

/*
 * IPv6 address
 */
#ifndef _IN6_ADDR_STRUCT
struct in6_addr {
	union {
		u_int32_t u6_addr32[4];
#ifdef notyet
		u_int64_t u6_addr64[2];
#endif /* notyet */
		u_int16_t u6_addr16[8];
		u_int8_t  u6_addr8[16];
	} u6_addr;
};
#define s6_addr32	u6_addr.u6_addr32
#ifdef notyet
#define s6_addr64	u6_addr.u6_addr64
#endif /* notyet */
#define s6_addr16	u6_addr.u6_addr16
#define s6_addr8	u6_addr.u6_addr8
#define s6_addr 	u6_addr.u6_addr8
#define INET6_ADDRSTRLEN	46

#define IN6ADDR_ANY_INIT      {0, 0, 0, 0}
#define IPV6ADDR_ANY_INIT     IN6ADDR_ANY_INIT        /* old name */
#if BYTE_ORDER == BIG_ENDIAN
#define IN6ADDR_LOOPBACK_INIT {0, 0, 0, 1}
#else
#define IN6ADDR_LOOPBACK_INIT {0, 0, 0, 0x01000000}
#endif
#define IPV6ADDR_LOOPBACK_INIT        IN6ADDR_LOOPBACK_INIT   /* old name */

#define _IN6_ADDR_STRUCT
#endif /* _IN6_ADDR_STRUCT */

#ifdef _AIX
#define _SOCKADDR_LEN
#endif

#if (_XOPEN_SOURCE_EXTENDED != 1) && !defined(_SOCKADDR_LEN) && !defined(_KERNEL)
struct sockaddr_in {
	u_short	sin_family;
	u_short	sin_port;
	struct	in_addr sin_addr;
	char	sin_zero[8];
};
#endif /* _XOPEN_SOURCE_EXTENDED != 1 && !_SOCKADDR_LEN && !_KERNEL */


#define SIN6_LEN
/*
 * Socket address, IPv6 style.
 */

struct sockaddr_in6 {
	u_char		sin6_len;
	u_char		sin6_family;
	u_int16_t	sin6_port;
	u_int32_t	sin6_flowinfo;
	struct 		in6_addr	sin6_addr;
	uint32_t	sin6_scope_id;	/* set of interfaces for a scope */
};


#ifdef MFC_IMPL
/*
 * Multicast downstream destinations
 */

struct ds_in6addr {
	struct  in6_addr sin6_addr; /* downstream destination */
	u_short hoplimit;       /* min ttl required to forward */
	u_short flags;          /* attributes */
};
#endif /* MFC_IMPL */

struct sockaddr_inds {
	u_char  sin_len;
	u_char  sin_family;
	u_short sin_num;
	char    sin_data[12];
};



/*
 * Structure used to describe IP options.
 * Used to store options internally, to pass them to a process,
 * or to restore options retrieved earlier.
 * The ip_dst is used for the first-hop gateway when using a source route
 * (this gets put into the header proper).
 */

#ifndef __cplusplus
struct ip_opts {
	struct	in_addr ip_dst;		/* first hop, 0 w/o src rt */
	char	ip_opts[40];		/* actually variable in size */
};
#endif

/*
 * Argument structure for IP_ADD_MEMBERSHIP and IP_DROP_MEMBERSHIP.
 */
struct ip_mreq {
	struct in_addr	imr_multiaddr;	/* IP multicast address of group */
	struct in_addr	imr_interface;	/* local IP address of interface */
};
struct ipv6_mreq {
	struct in6_addr ipv6mr_multiaddr; /* IPv6 multicast address of group */
	unsigned int ipv6mr_interface;  /* local IPv6 address of interface */
};
/* old layout */
struct oipv6_mreq {
	struct in6_addr	ipv6mr_multiaddr;	/* IPv6 multicast address of group */
	struct in6_addr	ipv6mr_interface;	/* local IPv6 address of interface */
};

/*
 * Struct used for the IP_RECVIFINFO setsockopt().
 */

#ifndef	IFNAMSIZ
/*
 * Define IFNAMSIZ here to avoid cascading includes...this is really defined
 * in net/if.h...
 */
#define IFNAMSIZ 16
#endif /* IFNAMSIZ */

#ifndef _IF_NAMESIZE_D
#define _IF_NAMESIZE_D
/* Required for Basic Socket Interface Extensions for IPv6 */
#define	IF_NAMESIZE	IFNAMSIZ
#endif

struct if_info {
	char			ifi_name[IFNAMSIZ];
	struct	in_addr		ifi_addr;
	int			ifi_type;
};

#ifdef _KERNEL
extern	struct domain inetdomain;
struct	in_addr in_makeaddr();
u_long	in_netof(), in_lnaof();
#endif

struct get_mtus {
	int	buf_len;
	int	*mtus_list;
};

typedef struct _mtu_node {
	int	mtu_value;
	struct	_mtu_node *next;
} mtu_node;

/* number representation macros moved to net/nh.h */
#include <net/nh.h>

#define INET_ADDRSTRLEN	16

#define IPNGVERSION	6

/*
 * Defintions for flow labels.
 */
#define IPV6_FLOWINFO_FLOWLABEL         0x00ffffff
#define IPV6_FLOWINFO_PRIORITY          0x0f000000
#define IPV6_FLOWINFO_PRIFLOW           0x0fffffff
#define IPV6_FLOWINFO_SRFLAG            0x10000000
#define IPV6_FLOWINFO_VERSION           0xf0000000

#define IPV6_PRIORITY_UNCHARACTERIZED   0x00000000
#define IPV6_PRIORITY_FILLER            0x01000000
#define IPV6_PRIORITY_UNATTENDED        0x02000000
#define IPV6_PRIORITY_RESERVED1         0x03000000
#define IPV6_PRIORITY_BULK              0x04000000
#define IPV6_PRIORITY_RESERVED2         0x05000000
#define IPV6_PRIORITY_INTERACTIVE       0x06000000
#define IPV6_PRIORITY_CONTROL           0x07000000
#define IPV6_PRIORITY_8                 0x08000000
#define IPV6_PRIORITY_9                 0x09000000
#define IPV6_PRIORITY_10                0x0a000000
#define IPV6_PRIORITY_11                0x0b000000
#define IPV6_PRIORITY_12                0x0c000000
#define IPV6_PRIORITY_13                0x0d000000
#define IPV6_PRIORITY_14                0x0e000000
#define IPV6_PRIORITY_15                0x0f000000

#define IPV6_SRFLAG_STRICT              0x10000000
#define IPV6_SRFLAG_LOOSE               0x00000000

#define IPV6_VERSION                    0x60000000

#define IPV6_GET_FLOWLABEL(x)		(ntohl(x) & 0x00ffffff)
#define IPV6_GET_PRIORITY(x)		((ntohl(x) >> 24) & 0xf)
#define IPV6_GET_VERSION(x)		((*((u_char *)&(x)) >> 4) & 0xf)
#define IPV6_SET_FLOWLABEL(x)		(htonl(x) & IPV6_FLOWINFO_FLOWLABEL)
#define IPV6_SET_PRIORITY(x)            (htonl((x & 0xf) << 24))

/*
 * Definitions for IPv6 addresses.
 */

#define CLR_ADDR6(a) \
	{ \
		(a).s6_addr32[0] = 0; \
		(a).s6_addr32[1] = 0; \
		(a).s6_addr32[2] = 0; \
		(a).s6_addr32[3] = 0; \
	}

#define COPY_ADDR6(from, to) (to) = (from)

#define IA6_TO_ARRAY16(a) \
	(a).s6_addr16[7], (a).s6_addr16[6], \
	(a).s6_addr16[5], (a).s6_addr16[4], \
	(a).s6_addr16[3], (a).s6_addr16[2], \
	(a).s6_addr16[1], (a).s6_addr16[0]

#define SAME_SOCKADDR(a, b) \
	(((a)->sin6_addr.s6_addr32[0] == (b)->sin6_addr.s6_addr32[0]) && \
	 ((a)->sin6_addr.s6_addr32[1] == (b)->sin6_addr.s6_addr32[1]) && \
	 ((a)->sin6_addr.s6_addr32[2] == (b)->sin6_addr.s6_addr32[2]) && \
	 ((a)->sin6_addr.s6_addr32[3] == (b)->sin6_addr.s6_addr32[3]))

#define SAME_ADDR6(a, b) \
	(((a).s6_addr32[0] == (b).s6_addr32[0]) && \
	 ((a).s6_addr32[1] == (b).s6_addr32[1]) && \
	 ((a).s6_addr32[2] == (b).s6_addr32[2]) && \
	 ((a).s6_addr32[3] == (b).s6_addr32[3]))

#define IS_ANYSOCKADDR(a) \
	(((a)->sin6_addr.s6_addr32[0] == 0) && \
	 ((a)->sin6_addr.s6_addr32[1] == 0) && \
	 ((a)->sin6_addr.s6_addr32[2] == 0) && \
	 ((a)->sin6_addr.s6_addr32[3] == 0))

#define IS_ANYADDR6(a) \
	(((a).s6_addr32[0] == 0) && \
	 ((a).s6_addr32[1] == 0) && \
	 ((a).s6_addr32[2] == 0) && \
	 ((a).s6_addr32[3] == 0))

#define IS_COMPATSOCKADDR(a) \
	(((a)->sin6_addr.s6_addr32[0] == 0) && \
	 ((a)->sin6_addr.s6_addr32[1] == 0) && \
	 ((a)->sin6_addr.s6_addr32[2] == 0) && \
	 ((a)->sin6_addr.s6_addr8[12] != 0))

#define IS_COMPATADDR6(a) \
	(((a).s6_addr32[0] == 0) && \
	 ((a).s6_addr32[1] == 0) && \
	 ((a).s6_addr32[2] == 0) && \
	 ((a).s6_addr8[12] != 0))

#if BYTE_ORDER == BIG_ENDIAN
#define IS_LOOPSOCKADDR(a) \
	(((a)->sin6_addr.s6_addr32[0] == 0) && \
	 ((a)->sin6_addr.s6_addr32[1] == 0) && \
	 ((a)->sin6_addr.s6_addr32[2] == 0) && \
	 ((a)->sin6_addr.s6_addr32[3] == 1))

#define IS_LOOPADDR6(a) \
	(((a).s6_addr32[0] == 0) && \
	 ((a).s6_addr32[1] == 0) && \
	 ((a).s6_addr32[2] == 0) && \
	 ((a).s6_addr32[3] == 1))

#define IS_IPV4SOCK_ANYADDR(a) \
	(((a)->sin6_addr.s6_addr32[0] == 0) && \
	 ((a)->sin6_addr.s6_addr32[1] == 0) && \
	 ((a)->sin6_addr.s6_addr32[2] == 0x0000ffff) && \
	 ((a)->sin6_addr.s6_addr32[3] == 0))

#define IS_IPV4SOCKADDR(a) \
	(((a)->sin6_addr.s6_addr32[0] == 0) && \
	 ((a)->sin6_addr.s6_addr32[1] == 0) && \
	 ((a)->sin6_addr.s6_addr32[2] == 0x0000ffff) && \
	 ((a)->sin6_addr.s6_addr32[3] != 0))

#define IS_IPV4ADDR6(a) \
	(((a).s6_addr32[0] == 0) && \
	 ((a).s6_addr32[1] == 0) && \
	 ((a).s6_addr32[2] == 0x0000ffff) && \
	 ((a).s6_addr32[3] != 0))
#else
#define IS_LOOPSOCKADDR(a) \
	(((a)->sin6_addr.s6_addr32[0] == 0) && \
	 ((a)->sin6_addr.s6_addr32[1] == 0) && \
	 ((a)->sin6_addr.s6_addr32[2] == 0) && \
	 ((a)->sin6_addr.s6_addr32[3] == 0x01000000))

#define IS_LOOPADDR6(a) \
	(((a).s6_addr32[0] == 0) && \
	 ((a).s6_addr32[1] == 0) && \
	 ((a).s6_addr32[2] == 0) && \
	 ((a).s6_addr32[3] == 0x01000000))

#define IS_IPV4SOCK_ANYADDR(a) \
	(((a)->sin6_addr.s6_addr32[0] == 0) && \
	 ((a)->sin6_addr.s6_addr32[1] == 0) && \
	 ((a)->sin6_addr.s6_addr32[2] == 0xffff0000) && \
	 ((a)->sin6_addr.s6_addr32[3] == 0))

#define IS_IPV4SOCKADDR(a) \
	(((a)->sin6_addr.s6_addr32[0] == 0) && \
	 ((a)->sin6_addr.s6_addr32[1] == 0) && \
	 ((a)->sin6_addr.s6_addr32[2] == 0xffff0000) && \
	 ((a)->sin6_addr.s6_addr32[3] != 0))

#define IS_IPV4ADDR6(a) \
	(((a).s6_addr32[0] == 0) && \
	 ((a).s6_addr32[1] == 0) && \
	 ((a).s6_addr32[2] == 0xffff0000) && \
	 ((a).s6_addr32[3] != 0))
#endif /* BE */

#define IS_LOCALADDR6(a)        ((a).s6_addr8[0] == 0xfe)

#define IS_LINKLADDR6(a) \
	(IS_LOCALADDR6(a) && ((a).s6_addr8[1] == 0x80))

#define IS_SITELADDR6(a) \
	(IS_LOCALADDR6(a) && ((a).s6_addr8[1] == 0xc0))

#define IS_MULTIADDR6(a)        ((a).s6_addr8[0] == 0xff)

#define MADDR6_FLAGS(a)         ((a).s6_addr8[1] >> 4)

#define MADDR6_FLG_WK           0       /* "well-known" multicast address */
#define MADDR6_FLG_TS           1       /* "transient" multicast address */

#define MADDR6_SCOPE(a)         ((a).s6_addr8[1] & 0x0f)

#define MADDR6_SCP_NODE         0x1     /* node-local scope */
#define MADDR6_SCP_LINK         0x2     /* link-local scope */
#define MADDR6_SCP_SITE         0x5     /* site-local scope */
#define MADDR6_SCP_ORG          0x8     /* organization-local scope */
#define MADDR6_SCP_GLO          0xe     /* global scope */

#define MADDR6_ALLNODES         1       /* all-nodes groups */
#define MADDR6_ALLROUTERS       2       /* all-routers groups */
#define MADDR6_ALLHOSTS         3       /* all-hosts groups */

/*
 * New IPv6 address macros of BSD API
 */

#define IN6_IS_ADDR_UNSPECIFIED(p)	IS_ANYADDR6(*p)
#define IN6_IS_ADDR_LOOPBACK(p)		IS_LOOPADDR6(*p)
#define IN6_IS_ADDR_MULTICAST(p)	IS_MULTIADDR6(*p)
#define IN6_IS_ADDR_LINKLOCAL(p)	IS_LINKLADDR6(*p)
#define IN6_IS_ADDR_SITELOCAL(p)	IS_SITELADDR6(*p)
#define IN6_IS_ADDR_V4MAPPED(p)		IS_IPV4ADDR6(*p)
#define IN6_IS_ADDR_V4COMPAT(p)		IS_COMPATADDR6(*p)

#define IN6_IS_ADDR_MC_NODELOCAL(p) \
	(IS_MULTIADDR6(*p) && (MADDR6_SCOPE(*p) == MADDR6_SCP_NODE))
#define IN6_IS_ADDR_MC_LINKLOCAL(p) \
	(IS_MULTIADDR6(*p) && (MADDR6_SCOPE(*p) == MADDR6_SCP_LINK))
#define IN6_IS_ADDR_MC_SITELOCAL(p) \
	(IS_MULTIADDR6(*p) && (MADDR6_SCOPE(*p) == MADDR6_SCP_SITE))
#define IN6_IS_ADDR_MC_ORGLOCAL(p) \
	(IS_MULTIADDR6(*p) && (MADDR6_SCOPE(*p) == MADDR6_SCP_ORG))
#define IN6_IS_ADDR_MC_GLOBAL(p) \
	(IS_MULTIADDR6(*p) && (MADDR6_SCOPE(*p) == MADDR6_SCP_GLO))

#define IN6_ARE_ADDR_EQUAL(pa,pb)	SAME_ADDR6(*pa,*pb)

/* My own extension (:-) */

#define IN6_ADDR_V6_TO_V4(a)	((struct in_addr *)&(a)->s6_addr[12])

#ifndef _KERNEL
extern const struct in6_addr in6addr_any, in6addr_loopback;
#endif

/* Socket options that can't sit in _XOPEN_SOURCE_EXTENDED==1 block. */
#define IPV6_UNICAST_HOPS	IP_TTL
#define	IPV6_MULTICAST_IF	IP_MULTICAST_IF	/* u_int */
#define IPV6_MULTICAST_HOPS	IP_MULTICAST_TTL /* int */
#define	IPV6_MULTICAST_LOOP	IP_MULTICAST_LOOP
#define	IPV6_ADD_MEMBERSHIP	IP_ADD_MEMBERSHIP
#define	IPV6_JOIN_GROUP		IP_ADD_MEMBERSHIP
#define	IPV6_DROP_MEMBERSHIP	IP_DROP_MEMBERSHIP
#define	IPV6_LEAVE_GROUP	IP_DROP_MEMBERSHIP
#define IPV6_ADDRFORM		IP_ADDRFORM
#define IPV6_NOPROBE            28   /* int; don't trigger NUD probes */
#define IPV6_RECVSRCRT          29   /* int; receive source route array */
#define IPV6_RECVIF             30   /* int; receive interface in array */
#define IPV6_SENDIF             31   /* sockaddr; set outgoing iface */
#define IPV6_PKTINFO		33   /* in6_pktinfo; set packet info */
#define IPV6_RECVHOPS		IP_RECVTTL
#define IPV6_RECVPKTINFO	35   /* int; receive packet info */
#define	IPV6_PKTOPTIONS		36   /* ancillary data style */
#define IPV6_V6ONLY             37   /* IPv6 only communication */
#define	FLOW6_RAND		49   /* random generator for flow IDs */
#define ICMP6_FILTER            38   /* ICMPv6 filter socket option */
#define IPV6_CHECKSUM           39   /* IPV6_CHECKSUM socket option */
#define IPV6_HOPLIMIT           40   /* ancillary-only option */
#define IPV6_RECVHOPLIMIT       41   /* receive incoming hop limit */
#define IPV6_RECVTCLASS         42   /* receive incoming traffic class */
#define IPV6_TCLASS             43   /* traffic class ancillary value */
#define IPV6_USE_MIN_MTU        44   /* use min mtu socket option */
#define IPV6_DONTFRAG           45   /* do not fragment outgoing pkts */
#define IPV6_PATHMTU            46   /* check path MTU for a given dst */
#define IPV6_RECVPATHMTU        47   /* recv packet too big notifications */
#define IPV6_NEXTHOP            48   /* next hop socket option */
#define IPV6_RTHDR              50   /* routing header option */
#define IPV6_RECVRTHDR          51   /* receive routing header */
#define IPV6_HOPOPTS            52   /* Hop-by-Hop Header */
#define IPV6_RECVHOPOPTS        53   /* receive hop-by-hop header */
#define IPV6_DSTOPTS            54   /* Destination Opts Header after Rthdr
                                        or when there is no Rthdr */
#define IPV6_RTHDRDSTOPTS       55   /* Destination Opts Header before Rthdr */
#define IPV6_RECVDSTOPTS        56   /* receive both kinds of Dopt hdrs */
#define IPV6_AIXRAWSOCKET       57   /* deliver IPv6 hdr also */


/*
 * packet information
 */
struct in6_pktinfo {
      struct in6_addr ipi6_addr;      /* src/dst IPv6 address */
      int             ipi6_ifindex;   /* send/recv interface index */
};

/*
 * path mtu information
 */
struct ip6_mtuinfo {
        struct sockaddr_in6 ip6m_addr;     /* dst addr including zone id */
        uint32_t                ip6m_mtu;  /* path MTU in host byte order */
};


/* Routing Header Type Definitions */
#define IPV6_RTHDR_TYPE_0       0       /* IPv6 Routing header type 0 */


/* Definitions for RFC 3542 Extended API Functions */
socklen_t	inet6_rth_space(int, int);
void		*inet6_rth_init(void *, socklen_t, int, int);
int		inet6_rth_add(void *, const struct in6_addr *);
int		inet6_rth_reverse(const void *, void *);
int		inet6_rth_segments(const void *);
struct in6_addr *inet6_rth_getaddr(const void *, int);

int             inet6_opt_init(void *, socklen_t);
int		inet6_opt_append(void *, socklen_t, int, uint8_t,
				socklen_t, uint_t, void **);
int		inet6_opt_finish(void *,socklen_t, int);
int		inet6_opt_set_val(void *, int, void *, socklen_t);
int		inet6_opt_next(void *, socklen_t, int, uint8_t *,
				socklen_t *, void **);
int		inet6_opt_find(void *, socklen_t, int, uint8_t,
				socklen_t *, void **);
int		inet6_opt_get_val(void *, int, void *, socklen_t);

#ifdef _KERNEL
struct ifnet; struct mbuf;      /* forward declarations for Standard C */
#define satosin(sa)     ((struct sockaddr_in *)(sa))
#define sintosa(sin)    ((struct sockaddr *)(sin))
#define ifatoia(ifa)    ((struct in_ifaddr *)(ifa))
#define satosin6(sa)    ((struct sockaddr_in6 *)(sa))
#define sin6tosa(sin6)  ((struct sockaddr *)(sin6))
#define ifatoia6(ifa)   ((struct in6_ifaddr *)(ifa))
#endif /* _KERNEL */

#endif /* _ALL_SOURCE */

#endif /* _NETINET_IN_H_ */
