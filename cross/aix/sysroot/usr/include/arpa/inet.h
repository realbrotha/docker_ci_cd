/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/usr/include/arpa/inet.h 1.25.1.1                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1985,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* aix_sccsid[] = "src/bos/usr/include/arpa/inet.h, sockinc, bos53X, x2011_32B0 AIX 7/29/11 04:41:12" */
/*
 * COMPONENT_NAME: INCPROTO
 *
 * FUNCTIONS:
 *
 * ORIGINS: 26,27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef _ARPA_INET_H
#define _ARPA_INET_H

#include <standards.h>		/* define standards macros */
#include <sys/inttypes.h>
#include <netinet/in.h>

/*
 * External definitions for
 * functions in inet(3N)
 */

#if _XOPEN_SOURCE_EXTENDED == 1

/*
 * COSE defines the following types and structure in netinet/in.h,
 * and netdb.h. The defines will ensure that an application only
 * see them once.
 */
#ifndef _IP_TYPES_T
typedef uint16_t	in_port_t;
typedef	__ulong32_t	in_addr_t;
#define _IP_TYPES_T
#endif /* _IP_TYPES_T */

#ifndef _IN_ADDR_STRUCT
struct in_addr {
	in_addr_t	s_addr;
};
#define _IN_ADDR_STRUCT
#endif /* _IN_ADDR_STRUCT */

#ifdef  _NO_PROTO

#ifndef htonl
uint16_t ntohs(), htons();
uint32_t ntohl(), htonl();
#endif

#else   /* POSIX required prototypes */
 
#ifndef htonl
uint16_t ntohs(uint16_t);
uint16_t htons(uint16_t);
uint32_t ntohl(uint32_t);
uint32_t htonl(uint32_t);
#endif

#endif /* _NO_PROTO */

#ifdef _NO_PROTO
in_addr_t	inet_addr();
in_addr_t	inet_lnaof();
struct in_addr	inet_makeaddr();
in_addr_t	inet_netof();
in_addr_t	inet_network();
int		inet_pton();
const char 	*inet_ntop();
char		*inet_ntoa();
#else
in_addr_t	inet_addr(const char *);
in_addr_t	inet_lnaof(struct in_addr);
struct in_addr	inet_makeaddr(in_addr_t, in_addr_t);
in_addr_t	inet_netof(struct in_addr);
in_addr_t	inet_network(const char *);
char		*inet_ntoa(struct in_addr);
int              inet_pton(int, const char *__restrict__, void *__restrict__);
const char      *inet_ntop(int, const void *__restrict__, char *__restrict__, size_t);
#endif /* _NO_PROTO */

#endif /* _XOPEN_SOURCE_EXTENDED == 1 */

#ifdef _ALL_SOURCE

/* Define performance optimizations for big endian code */
#include <sys/machine.h>
#if BYTE_ORDER == BIG_ENDIAN
#ifndef htonl
#define htonl(hostlong)  (hostlong)
#endif
#ifndef htons
#define htons(hostshort) (hostshort)
#endif
#ifndef ntohl
#define ntohl(netlong)   (netlong)
#endif
#ifndef ntohs
#define ntohs(netshort)  (netshort)
#endif
#endif

#ifndef _IN6_ADDR_STRUCT
struct in6_addr {
        union {
                uint32_t u6_addr32[4];
#ifdef notyet
                uint64_t u6_addr64[2];
#endif
                uint16_t u6_addr16[8];
                uint8_t  u6_addr8[16];
        } u6_addr;
};
#define s6_addr32       u6_addr.u6_addr32
#ifdef notyet
#define s6_addr64       u6_addr.u6_addr64
#endif
#define s6_addr16       u6_addr.u6_addr16
#define s6_addr8        u6_addr.u6_addr8
#define s6_addr         u6_addr.u6_addr8
#define _IN6_ADDR_STRUCT
#endif /* _IN6_ADDR_STRUCT */

#ifdef _NO_PROTO
int		inet_aton();
char		*inet_neta();
char		*inet_net_ntop();
int		inet_net_pton();
int		inet_pton6_zone();
const char 	*inet_ntop6_zone();
u_int		inet_nsap_addr();
char		inet_nsap_ntoa();
int		ether_line();
char		*ether_ntoa();
int		ether_ntoa_r();
struct ether_addr *ether_aton();
int		ether_aton_r();
int		ether_hostton();
int		ether_ntohost();
int		link_addr();
char 		*link_ntoa();
int		link_ntoa_r();
void            **which_inetntoa();
#else
#define _ARPA_INET_ONLY
#include <netinet/if_ether.h>
#undef _ARPA_INET_ONLY
#include <net/if_dl.h>
int		inet_aton(const char *, struct in_addr *);
char 		*inet_neta(in_addr_t, char *, size_t);
char            *inet_net_ntop(int, const void *, int, char *, size_t);
int              inet_net_pton(int, const char *, void *, size_t);
char            *inet_ntoa(struct in_addr);
int              inet_pton6_zone(const char *, void *);
const char      *inet_ntop6_zone(const void *, char *, size_t);
u_int            inet_nsap_addr(const char *, u_char *, int);
char            *inet_nsap_ntoa(int, const u_char *, char *);
int		ether_line(char *, struct ether_addr *, char *);
char		*ether_ntoa(struct ether_addr *);
int		ether_ntoa_r(struct ether_addr *, char *);
struct ether_addr *ether_aton(char *);
int		ether_aton_r(char *, struct ether_addr *);
int		ether_hostton(char *, struct ether_addr *);
int		ether_ntohost(char *, struct ether_addr *);
int		link_addr(char *, struct sockaddr_dl *);
char 		*link_ntoa(const struct sockaddr_dl *);
int		link_ntoa_r(const struct sockaddr_dl *, char *, int);
void            **which_inetntoa(void);
#endif /* _NO_PROTO */

#endif /* _ALL_SOURCE */

#endif /* _ARPA_INET_H */
