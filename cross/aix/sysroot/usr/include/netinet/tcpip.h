/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernext/inet/tcpip.h 1.14                               */
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
/* @(#)56	1.14  src/bos/kernext/inet/tcpip.h, sysxinet_tcp, bos530 9/23/03 16:57:55 */
/*
 *   COMPONENT_NAME: SYSXINET
 *
 *   FUNCTIONS: 
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
 *	Base:	tcpip.h	7.3 (Berkeley) 6/29/88
 *	Merged:	tcpip.h	7.4 (Berkeley) 6/28/90
 */

#ifndef _TCPIP_H_
#define _TCPIP_H_

#include <netinet/ip6.h>
#include <netinet/ip6_var.h>
#include <netinet/tcp.h>

#ifdef __64BIT_KERNEL
struct tcpipreasshdr
{
	caddr_t ta_next;
	caddr_t ta_prev;
	struct mbuf *ta_m;
	struct tcpiphdr *ta_ti;
};
#endif /* __64BIT_KERNEL */

/*
 * Tcp+ip header, after ip options removed.
 */
struct tcpiphdr {
	struct 	ipovly ti_i;		/* overlaid ip structure */
	struct	tcphdr ti_t;		/* tcp header */
};

#ifndef __64BIT__
#define ti_next         ti_i.ih_next
#define ti_prev         ti_i.ih_prev
#endif /* __64BIT__ */

#define ti_x1           ti_i.ih_x1
#define ti_pr           ti_i.ih_pr
#define ti_len          ti_i.ih_len
#define ti_src          ti_i.ih_src
#define ti_dst          ti_i.ih_dst
#define ti_sport        ti_t.th_sport
#define ti_dport        ti_t.th_dport
#define ti_seq          ti_t.th_seq
#define ti_ack          ti_t.th_ack
#define ti_x2           ti_t.th_x2
#define ti_off          ti_t.th_off
#define ti_xoff         ti_t.th_xoff
#define ti_flags        ti_t.th_flags
#define ti_win          ti_t.th_win
#define ti_sum          ti_t.th_sum
#define ti_urp          ti_t.th_urp

/*
 * IPv6+TCP headers.
 */
struct tcpip6hdr {
	struct  ipv6 ti6_i;             /* IPv6 header */
	struct  tcphdr ti6_t;           /* TCP header */
};

struct tcponlyhdr {
	struct  tcphdr ti_t;
};

#define ti6_head        ti6_i.ip6_head
#define ti6_len         ti6_i.ip6_len
#define ti6_nh          ti6_i.ip6_nh
#define ti6_hlim        ti6_i.ip6_hlimit
#define ti6_src         ti6_i.ip6_src
#define ti6_dst         ti6_i.ip6_dst
#define ti6_sport       ti6_t.th_sport
#define ti6_dport       ti6_t.th_dport
#define ti6_seq         ti6_t.th_seq
#define ti6_ack         ti6_t.th_ack
#define ti6_x2          ti6_t.th_x2
#define ti6_x1          ti6_t.th_x1
#define ti6_off         ti6_t.th_off
#define ti6_xoff        ti6_t.th_xoff
#define ti6_flags       ti6_t.th_flags
#define ti6_win         ti6_t.th_win
#define ti6_sum         ti6_t.th_sum
#define ti6_urp         ti6_t.th_urp

/*
 * Same with queue links.
 */
struct tcp6hdrs {
	struct  tcp6hdrs *tr_next, *tr_prev;    /* queue links */
	struct  tcpip6hdr tr_ti6;               /* headers */
};
#define tr_i6           tr_ti6.ti6_i
#define tr_head         tr_ti6.ti6_head
#define tr_len          tr_ti6.ti6_len
#define tr_nh           tr_ti6.ti6_nh
#define tr_hlim         tr_ti6.ti6_hlim
#define tr_src          tr_ti6.ti6_src
#define tr_dst          tr_ti6.ti6_dst
#define tr_t            tr_ti6.ti6_t
#define tr_sport        tr_ti6.ti6_sport
#define tr_dport        tr_ti6.ti6_dport
#define tr_seq          tr_ti6.ti6_seq
#define tr_ack          tr_ti6.ti6_ack
#define tr_x2           tr_ti6.ti6_x2
#define tr_off          tr_ti6.ti6_off
#define tr_xoff         tr_ti6.ti6_xoff
#define tr_flags        tr_ti6.ti6_flags
#define tr_win          tr_ti6.ti6_win
#define tr_sum          tr_ti6.ti6_sum
#define tr_urp          tr_ti6.ti6_urp

/*
 * Dual template for IPv4/IPv6 TCP.
 *
 * Optimized for IPv4
 */
struct tcptemp {
	struct  ipovly tt_i;            /* overlaid ip structure */
	struct  tcphdr tt_t;            /* tcp header */
	struct  ip6ovck tt_i6;          /* IPv6 header^2 */
	struct  in6_addr tt_src6;       /* source address */
	struct  in6_addr tt_dst6;       /* destination address */
};
#define tt_pr           tt_i.ih_pr
#define tt_len          tt_i.ih_len
#define tt_src          tt_i.ih_src
#define tt_dst          tt_i.ih_dst
#define tt_sport        tt_t.th_sport
#define tt_dport        tt_t.th_dport
#define tt_off          tt_t.th_off
#define tt_xoff         tt_t.th_xoff
#define tt_pr6          tt_i6.ih6_pr
#define tt_len6         tt_i6.ih6_len

#endif /* _TCPIP_H_ */
