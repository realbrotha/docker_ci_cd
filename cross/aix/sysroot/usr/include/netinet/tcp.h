/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernext/inet/tcp.h 1.8.1.19                             */
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
/* @(#)54	1.8.1.19  src/bos/kernext/inet/tcp.h, sysxinet_tcp, bos53H, h2006_09B5 2/21/06 16:09:51 */
/*
 *   COMPONENT_NAME: SYSXINET
 *
 *   FUNCTIONS:
 *
 *   ORIGINS: 26,27,85,90
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1993
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
 *      Base:   tcp.h   7.5 (Berkeley) 6/29/88
 *      Merged: tcp.h   7.7 (Berkeley) 6/28/90
 */

#ifndef _NETINET_TCP_H
#define _NETINET_TCP_H

#include <standards.h>

#ifdef _ALL_SOURCE
/* The only definition allowed in the standard namespace is TCP_NODELAY */

#define _IP_FIRSTFOUR_ONLY
#include <netinet/ip.h>
#undef _IP_FIRSTFOUR_ONLY

typedef __ulong32_t  tcp_seq;

/*
 * TCP header.
 * Per RFC 793, September, 1981.
 */
#ifndef _TCPHDR
#define _TCPHDR
struct tcphdr {
        u_short th_sport;               /* source port */
        u_short th_dport;               /* destination port */
        tcp_seq th_seq;                 /* sequence number */
        tcp_seq th_ack;                 /* acknowledgement number */
        struct  ip_firstfour ip_ff;     /* see <netinet/ip.h> */
#define th_off          ip_v            /* offset */
#define th_x2           ip_hl           /* unused */
#define th_xoff         ip_vhl          /* offset+unused */
#define th_flags        ip_tos          /* flags */
#define th_win          ip_ff.ip_fwin   /* window (unsigned) */
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20
#define TH_ECN_ECHO  0x40		/* receiver received a CE packet */
#define TH_CWR  0x80			/* Congestion Window Reduced (ECN) */
        u_short th_sum;                 /* checksum */
        u_short th_urp;                 /* urgent pointer */
};
#endif /* _TCPHDR */

#include <netinet/ip.h>

#define TCPOPT_EOL              0
#define TCPOPT_NOP              1
#define TCPOPT_MAXSEG           2
#define TCPOPT_WINDOWSCALE      3       /* RFC 1323 window scale option */
#define TCPOPT_SACK_PERMITTED   4       /* RFC 2018 (SACK) */
#define TCPOPT_SACK             5       /* RFC 2018 (SACK) */
#define TCPOPT_TIMESTAMP        8       /* RFC 1323 timestamp option */
#define TCPOPT_ALTCKSUM			14		/* RFC 1146 TCP alternate checksum */
#define TCPOPT_AH               194     /* 0xC2 authentication header */

#define TCP_MAXWINDOWSCALE      14      /* RFC 1323 max shift factor */

/*
 * RFC 1323 - this define is used for fast timstamp option parsing...
 */
#define TCP_FASTNAME                    0x0101080A
#define TCP_TIMESTAMP_OPTLEN            12

/*
 * RFC 1323 - Used by PAWS algorithm.
 */
#define TCP_24DAYS_WORTH_OF_SLOWTICKS   (24 * 24 * 60 * 60 * PR_SLOWHZ)

/* 
 * RFC 2018
 */
# define TCPOLEN_SACK_PERMITTED  2
# define TCPOPT_SACK_PERMIT_HDR  \
(TCPOPT_NOP<<24|TCPOPT_NOP<<16|TCPOPT_SACK_PERMITTED<<8|TCPOLEN_SACK_PERMITTED)

# define TCPOPT_SACK_HDR (TCPOPT_NOP<<24|TCPOPT_NOP<<16|TCPOPT_SACK<<8)

/* TCPOLEN_SACK = 2 * sizeof(tcp_seq): length of a sack block */
# define TCPOLEN_SACK     8 
# define TCP_MAX_SACK     4

/*
 * Default maximum segment size for TCP.
 * With an IP MSS of 576, this is 536,
 * but 512 is probably more convenient.
 * This should be defined as MIN(512, IP_MSS - sizeof (struct tcpiphdr)).
 */
#define TCP_MSS 1460

#define TCP_MAXWIN      65535           /* largest value for window */

/*
 * User-settable options (used with setsockopt).
 * TCP_NODELAY also defined in the !ALL_SOURCE section near end of file
 */
#define TCP_NODELAY     0x01    /* don't delay send to coalesce packets */
#define TCP_MAXSEG      0x02    /* set maximum segment size */
#define TCP_RFC1323     0x04    /* Use RFC 1323 algorithms/options */
#define TCP_STDURG      0x10    /* RFC 1122-compliant urgent pointer handling */
#define TCP_KEEPIDLE	0x11	/* Keep alive timer idle time */
#define TCP_KEEPINTVL	0x12	/* Keep alive timer interval */
#define TCP_KEEPCNT 	0x13	/* Keep alive probes count */
#define TCP_NODELAYACK 	0x14	/* don't delay ACKs */

/*
 * DACinet administration messages (used with setsockopt / getsockopt
 */
#define TCP_LUID        0x20    /* get login UID of peer */
#define TCP_ACLFLUSH    0x21    /* clear all DACinet ACLs */
#define TCP_ACLCLEAR    0x22    /* clear DACinet ACL */
#define TCP_ACLADD      0x23    /* Add to DACinet ACL */
#define TCP_ACLDEL      0x24    /* Delete from DACinet ACL */
#define TCP_ACLLS       0x25    /* List DACinet ACL */
#define TCP_ACLBIND     0x26    /* Set port number for TCP_ACLLS */
#define TCP_SETPRIV     0x27    /* Make port privileged */
#define TCP_UNSETPRIV   0x28    /* Make port unprivileged */
#define TCP_LSPRIV      0x29    /* List privileged ports */

/*
 * Access control parameter for TCP_ACLADD and TCP_ACLDEL
 */
struct tcpdac {
        uint16_t        port;           /* port # for this ACL record */
        uint16_t        flags;          /* TCP_ACL falgs  */
        uid_t           id;             /* user/group id */
        struct in6_addr host;           /* host or subnet */
        struct in6_addr netmask;        /* netmask if "host" is a subnet */
};

/*
 * Bit positions for tcpdac::flags
 */
#define TCP_ACLGID      0x01    /* id being added to ACL is a gid */
#define TCP_ACLUID      0x02    /* id being added to ACL is a gid */
#define TCP_ACLSUBNET   0x04    /* address being added to ACL is a subnet */
#define TCP_ACLDENY     0x08    /* this ACL entry is for denying access */

/*
 * For delayackport no option
 */
#define TCP_DELAY_ACK_SYN       0x01    /* Delay ack the received SYN */
#define TCP_DELAY_ACK_FIN       0x02    /* Delay ack the received FIN */
/*
 * To limit the maximum back to back segments that can be sent.
 * It is used only when tcp_newreno (rfc2582) is turned on.
*/
#define	TCP_MAXBURST	8   /* Maximum back to back segments that can be sent*/
#else   /* _ALL_SOURCE */
#define TCP_NODELAY     0x01    /* don't delay send to coalesce packets */
#endif  /* _ALL_SOURCE */

#endif
