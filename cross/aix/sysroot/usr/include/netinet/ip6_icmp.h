/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53A src/bos/kernext/inet/ip6_icmp.h 1.10                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)20  1.10  src/bos/kernext/inet/ip6_icmp.h, sockinc, bos53A, a2004_33C3 7/20/04 15:45:55 */
/*	$NetBSD: ip_icmp.h,v 1.6 1994/06/29 06:38:18 cgd Exp $	*/

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
 *	@(#)ip_icmp.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _NETINET_IP6_ICMP_H_
#define _NETINET_IP6_ICMP_H_

/*
 * Interface Control Message Protocol Definitions.
 * Per not yet RFC xxxx
 */

/*
 * Structure of an ICMPv6 header.
 */
struct icmpv6 {
	u_int8_t	icmp6_type;	/* type of message, see below */
	u_int8_t	icmp6_code;	/* type sub code */
	u_int16_t	icmp6_cksum;	/* checksum */
	union {
	    n_long	 ih6_pmtu;	    /* next MTU (for discovery) */
	    n_long	 ih6_pptr;	    /* bad parameter pointer */
	    n_long	 ih6_flags;	    /* reserved/flags field */
	    struct ih6_idseq {		    /* echo */
		n_short	  icd6_id;
		n_short	  icd6_seq;
	    } ih6_idseq;
	    struct ih6_gmm {
		n_short	  igm6_mrd;	    /* maximum response delay */
		n_short	  igm6_spare;
	    } ih6_gmm;
	    struct ih6_rtad {
		u_int8_t  irta_mhlim;
		u_int8_t  irta_aflg;
		u_int16_t irta_life;
	    } ih6_rtad;
	    struct ih6_rtrn {
		u_int8_t  irtn_rseg;
		u_int8_t  irtn_rflg;
		u_int16_t irtn_rkey;
	    } ih6_rtrn;
	} icmp6_hun;
#define icmp6_pmtu	icmp6_hun.ih6_pmtu
#define icmp6_pptr	icmp6_hun.ih6_pptr
#define icmp6_flags	icmp6_hun.ih6_flags
#define icmp6_id	icmp6_hun.ih6_idseq.icd6_id
#define icmp6_seq	icmp6_hun.ih6_idseq.icd6_seq
#define icmp6_mrd	icmp6_hun.ih6_gmm.igm6_mrd
#define icmp6_mhlim	icmp6_hun.ih6_rtad.irta_mhlim
#define icmp6_aflg	icmp6_hun.ih6_rtad.irta_aflg
#define icmp6_life	icmp6_hun.ih6_rtad.irta_life
#define icmp6_rseg      icmp6_hun.ih6_rtrn.irtn_rseg
#define icmp6_rflg      icmp6_hun.ih6_rtrn.irtn_rflg
#define icmp6_rkey      icmp6_hun.ih6_rtrn.irtn_rkey
	union {
	    struct in6_addr id6_grp;	    /* group address */
	    struct id6_addr {
		struct in6_addr  id6_tgt;     /* target address */
		struct in6_addr  id6_rdst;    /* (redirect) destination */
	    } id6_addr;
	    struct id6_nud {
		u_int32_t	 id6_reach;   /* reachable time */
		u_int32_t	 id6_retrans; /* retrans timer */
	    } id6_nud;
	    struct ir6_nud {
		u_int16_t        ir6_authlen; /* authentication length */
		u_int16_t        ir6_authoff; /* authentication offset */
		u_int32_t        ir6_rtrnseq; /* (router renum) seq number */
	    } ir6_nud;
	    struct ip6_extid {
		n_short	  magic_number;
		n_short	  subid;
	 	n_long    pktid;
	    } ip6_extid;
	    struct ipv6	    id6_ip;	    /* header of packet in error */
	    int8_t	    id6_data[1];    /* echo packet data */
	} icmp6_dun;
#define icmp6_grp	icmp6_dun.id6_grp
#define icmp6_tgt	icmp6_dun.id6_addr.id6_tgt
#define icmp6_rdst	icmp6_dun.id6_addr.id6_rdst
#define icmp6_reach	icmp6_dun.id6_nud.id6_reach
#define icmp6_retrans	icmp6_dun.id6_nud.id6_retrans
#define icmp6_authlen   icmp6_dun.ir6_nud.ir6_authlen
#define icmp6_authoff   icmp6_dun.ir6_nud.ir6_authoff
#define icmp6_rtrnseq   icmp6_dun.ir6_nud.ir6_rtrnseq
#define icmp6_ip	icmp6_dun.id6_ip
#define icmp6_data	icmp6_dun.id6_data
#define icmp6_magic_number	icmp6_dun.ip6_extid.magic_number
#define icmp6_subid	icmp6_dun.ip6_extid.subid
#define icmp6_pktid	icmp6_dun.ip6_extid.pktid
};

#define ICMP6_MAGIC_NUMBER 	0x7676
#define ICMP6_EXTID		(1)

#define ICMP6_MINLEN	8		/* abs minimum */
#define ICMP6_MLDLEN	24		/* multicast listener discovery */
#define ICMP6_GRPLEN	ICMP6_MLDLEN	/* group stuff */
#define ICMP6_RSLEN	8		/* router solicitation */
#define ICMP6_RALEN	16		/* router advertisement */
#define ICMP6_NSLEN	24		/* neighbor solicitation */
#define ICMP6_NALEN	24		/* neighbor advertisement */
#define ICMP6_RDLEN	40		/* redirect */
#define ICMP6_RTRNLEN	16		/* router renumbering */
#define ICMP6_HAREQLEN	8		/* HAAD request */
#define ICMP6_HAREPLEN	8		/* HAAD reply */
#define ICMP6_PSLEN	8		/* prefix solicitation */
#define ICMP6_PALEN	8		/* prefix advertisement */

/*
 * Definition of type and code field values.
 */
#define ICMP6_UNREACH		1	/* dest unreachable, codes: */
#define  ICMP6_UNREACH_NOROUTE	  0	 /* no route to destination */
#define  ICMP6_UNREACH_ADMIN	  1	 /* administratively prohibited */
#define  ICMP6_UNREACH_RTFAIL	  2	 /* not a neighbor */
#define  ICMP6_UNREACH_ADDRESS	  3	 /* address unreachable */
#define  ICMP6_UNREACH_PORT	  4	 /* port unreachable */
#define ICMP6_PKTTOOBIG		2	/* packet too big */
#define ICMP6_TIMXCEED		3	/* time exceeded, code: */
#define  ICMP6_TIMXCEED_INTRANS	  0	 /* ttl==0 in transit */
#define  ICMP6_TIMXCEED_REASS	  1	 /* ttl==0 in reass */
#define ICMP6_PARAMPROB		4	/* ip header bad */
#define  ICMP6_PARAMPROB_HDR	  0      /* erroneous header field */
#define  ICMP6_PARAMPROB_NH	  1      /* unrecognized next header */
#define  ICMP6_PARAMPROB_OPT	  2      /* unrecognized option */
#define ICMP6_OLDREDIRECT	5	/* old redirect */
#define ICMP6_ECHO		128	/* echo service */
#define ICMP6_ECHOREPLY		129	/* echo reply */
#define ICMP6_MLD_QUERY         130     /* multicast listener query */
#define ICMP6_MLD_REPORT        131     /* multicast listener report */
#define ICMP6_MLD_DONE          132     /* multicast listener done */
#define ICMP6_GROUPMEM_QUERY    ICMP6_MLD_QUERY
#define ICMP6_GROUPMEM_REPORT   ICMP6_MLD_REPORT
#define ICMP6_GROUPMEM_TERM     ICMP6_MLD_DONE
#define ICMP6_SOLICITATION_RT	133	/* router solicitation */
#define ICMP6_ADVERTISEMENT_RT	134	/* router advertisment */
#define ICMP6_SOLICITATION_ND	135	/* neighbor solicitation */
#define ICMP6_ADVERTISEMENT_ND	136	/* neighbor advertisment */
#define ICMP6_REDIRECT		137	/* redirect */
#define ICMP6_RTRENUM           138     /* router renumbering */
#define ICMP6_HAAD_REQUEST      144	/* home agent address discovery request */
#define ICMP6_HAAD_REPLY        145	/* home agent address discovery reply */
#define ICMP6_SOLICITATION_PREF 146	/* mobile prefix solicitation */
#define ICMP6_ADVERTISEMENT_PREF 147	/* mobile prefix advertisement */

#define  ICMP6_RTRENUM_CMD        0      /* renumbering command */
#define  ICMP6_RTRENUM_RSLT       1      /* renumbering result */

#define	ICMP6_INFOTYPE(type)	((type) >= ICMP6_ECHO)

#define ICMP6_ND_HOPS		255	/* hop count for ND */
#define ICMP6_ND_PRIORITY	IPV6_PRIORITY_15

/* IPSec flags */

#define ICMP6SEC_ERRORS         1       /* auth error types */
#define ICMP6SEC_REQUESTS       2       /* auth echo requests */
#define ICMP6SEC_GROUPS         4       /* auth group management */
#define ICMP6SEC_NEIGHBORS      8       /* auth neighbor management */

#if defined(_KERNEL)

#define ICMP6_TIMER_SCALE	1000
#define ICMP6_TIMER2HZ(mrd)	(ntohs(mrd) * PR_FASTHZ / ICMP6_TIMER_SCALE)
/*
 * Macro to compute a random timer value between 1 and its argument
 * in countdown period units.  We assume that the routine random()
 * is defined somewhere (and that it returns a positive number).
 */
#define	ICMP6_RANDOM_DELAY(maxdelay)	(inetrandom() % (maxdelay) + 1)
#define ICMP6_DEFAULT_DELAY()		(inetrandom() % (9 * PR_FASTHZ) + 1)

/* Internal flags passed to icmp6 send function */
#define ICMP6_IFMULTI_NOLOCK    0x1     /* Caller holds if_multiaddrs6 lock */

#endif

/* The following filter definitions are included in both ip6_icmp.h and icmp6.h
 * This is because one file is for kernel includes and the other for apps
 * Be sure to make any changes in both files 
 */
#ifndef FILTERDEF
#define FILTERDEF
struct icmp6_filter {           /* ICMPv6 type filtering */
        uint32_t        icmp6_filt[8];          /* 8*32 = 256 bits */
};
 
#define ICMP6_FILTER_SETPASS(type, filterp) \
        (((filterp)->icmp6_filt[(type) >> 5]) |= (1 << ((type) & 31)))
#define ICMP6_FILTER_SETBLOCK(type, filterp) \
        (((filterp)->icmp6_filt[(type) >> 5]) &= ~(1 << ((type) & 31)))
#define ICMP6_FILTER_WILLPASS(type, filterp) \
        ((((filterp)->icmp6_filt[(type) >> 5]) & (1 << ((type) & 31))) != 0)
#define ICMP6_FILTER_WILLBLOCK(type, filterp) \
        ((((filterp)->icmp6_filt[(type) >> 5]) & (1 << ((type) & 31))) == 0)
#define ICMP6_FILTER_SETPASSALL(filterp) \
        memset(filterp, 0xff, sizeof(struct icmp6_filter))
#define ICMP6_FILTER_SETBLOCKALL(filterp) \
        memset(filterp, 0x00, sizeof(struct icmp6_filter))
 
#endif /* FILTERDEF */

#endif
