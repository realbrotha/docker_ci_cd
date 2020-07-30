/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernext/inet/if_ndp6.h 1.9.1.1                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1997,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)70	1.9.1.1  src/bos/kernext/inet/if_ndp6.h, sysxinet_ipv6, bos53V, v2009_12B5 2/17/09 16:19:30 */
/*
 * Copyright (c) 1982, 1986, 1993
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

#ifndef _NETINET_IF_NDP6_H_
#define _NETINET_IF_NDP6_H_

/*
 * Definitions for if_ndtype
 */

#define IFND6_TYPE	0xff000000	/* type of the interface */
#define IFND6_FLAGS	0x00ff0000	/* flags */
#define IFND6_LLOFF	0x0000ff00	/* link-local address offset */
#define IFND6_L2OFF	0x000000ff	/* link-layer address offset */

#define IFND6_UNKNOWN	0x00000000	/* unknown ND type */
#define IFND6_LOOP	0x01000000	/* loopback */
#define IFND6_IEEE	0x02000000	/* IEEE LAN */
#define IFND6_SIT	0x03000000	/* SIT IPv6 over IPv4 */
#define IFND6_TUG	0x04000000	/* TUG IPv6 over IPv6 */
#define IFND6_TUN	0x05000000	/* TUN interface/device */
#define IFND6_PPP	0x06000000	/* PPP serial */
#define IFND6_ATM	0x07000000	/* ATM */
#define	IFND6_VIPA	0x08000000	/* Virtual Interface */
#define IFND6_LLINK	0xff000000	/* link-local pseudo interface */
#define IFND6_IB	0x09000000	/* IP over InfiniBand interface */ 
#define IFND6_IS_LLINK(ifp) \
	(((ifp)->if_ndtype & IFND6_TYPE) == IFND6_LLINK)

#define IFND6_INLL      0x00010000      /* participate to llink */
#define IFND6_ADDRES    0x00020000      /* link layer has physical addrs */
#define IFND6_MTU	0x00040000	/* fancy MTU values */

#define IFND6_LLSET	0x00100000	/* link-local address is set */

#define IPV6_UNDEF_HOPLIMIT 0   /* value of hope limit that is taken to mean undefined or no change*/

#define GETLLADDR(ifp) \
	(struct in6_addr *)((char *)(ifp) + sizeof(struct ifnet) + \
			    (((ifp)->if_ndtype >> 8) & 0xff))

#define GETL2ADDR(ifp) \
	((char *)(ifp) + sizeof(struct ifnet) + ((ifp)->if_ndtype & 0xff))

#ifdef _KERNEL
/*
 * IPv6 Neighbor Discovery Protocol.
 *
 * See RFC xxxx for protocol description.
 */

extern long ndpqsize;

struct llinfo_ndp6 {
	struct	rtentry *ln_rt;
	struct	mbuf *ln_hold;		/* last packet until resolved/timeout */
	long	ln_asked;		/* last time we QUERIED for this addr */
	short	ln_state;		/* state */
	short	ln_flags;		/* flags (is_router) */
	struct	mbuf *ln_hold_last;     /* last packet on ln_hold queue */
	int	ln_hold_count;		/* # of mbufs on ln_hold_queue */
	tid_t	ln_sleepword;		/* Unused - rt_ip6sleepword used instead */
/* deletion time in seconds, 0 == locked */
#define ln_timer ln_rt->rt_rmx.rmx_expire
};
#define LLNDP6_PHASEDOUT	0	/* held very old routes */
#define LLNDP6_INCOMPLETE	1	/* no info yet */
#define LLNDP6_PROBING		2	/* usable, NUD probes it */
#define LLNDP6_REACHABLE	3	/* valid */
#define LLNDP6_BUILTIN		4	/* don't fall into probing */

#define M_NOPROBE		M_BCAST	/* don't trigger NUD probes */

/*
 * Neighbor Discovery specific interface flag.
 */
#define IFA_BOOTING	RTF_XRESOLVE

#endif

#endif
