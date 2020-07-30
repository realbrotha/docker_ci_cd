/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernext/inet/ip6_opts.h 1.6.1.2                         */
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
/* @(#)19	1.6.1.2  src/bos/kernext/inet/ip6_opts.h, sockinc, bos53V, v2009_15B2 4/7/09 15:36:33 */
/* Z%19  1.6  src/bos/kernext/inet/ip6_opts.h, sockinc, bos530 5/16/02 10:09:18 */
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

#ifndef _NETINET_IP6_OPTS_H_
#define _NETINET_IP6_OPTS_H_

/*
 * Definitions for IPv6 options.
 */
#define OPT6_PAD_0		0	/* Single Pad */
#define OPT6_PAD_N		1	/* Multiple Pad */
#define OPT6_ROUTER_ALERT	0x05	/* Router Alert */
#define OPT6_JUMBO		194	/* Jumbo-Payload */
#define OPT6_NSAPA		195	/* NSAP Addresses */
#define OPT6_BINDING_UPD        198     /* Binding Update */
#define OPT6_BINDING_ACK        7       /* Binding Acknowledge */
#define OPT6_BINDING_REQ        8       /* Binding Request */
#define OPT6_HOME_ADDR          201     /* Home Address */

#define SUBOPT6_PAD0    0		/* Single Pad */
#define SUBOPT6_PADN    1		/* Multiple Pad */
#define SUBOPT6_UID     2		/* Binding Request Identifier Sub-option*/
#define SUBOPT6_COA     4		/* Care-of-Addrese Sub-option */

#define OPT6_MAX		256	/* Max */

/*
 * Macros on type bits.
 */
#define	OPT6_ACTION(t)		((t)&0xc0)	/* action */
#define OPT6_A_SKIP		0x00		/* skip over */
#define OPT6_A_DISC		0x40		/* discard */
#define OPT6_A_FERR		0x80		/* already send error */
#define OPT6_A_OERR		0xc0		/* send error */
#define OPT6_RTCHANGE(t)	((t)&0x20)	/* change en-route */

/*
 * Options and Extensions layouts.
 */

struct opt6_any {			/* common header */
	u_int8_t	o6any_ext;	/* extension type */
	u_int8_t	o6any_len;	/* length */
};

struct opt6_jbo {			/* Jumbo-Payload */
	u_int16_t	jbo_pad;	/* for alignment */
	u_int8_t	jbo_ext;	/* extension type (194) */
	u_int8_t	jbo_len;	/* length (4) */
	u_int32_t	jbo_plen;	/* payload length */
};

struct opt6_ra {			/* Router-Alert */
	u_int8_t	ra_ext;		/* extension type (TBD) */
	u_int8_t	ra_len;		/* length (2) */
	u_int16_t	ra_code;	/* code */
};
#define OPT6_RA_GROUP	0		/* ICMPv6 Group Membership */
#define OPT6_RA_RSVP	1		/* RSVP */

#ifdef _KERNEL
/*
 * Per option function array
 *  arguments are option, packet, headers and on input router alert pointer.
 */
struct opt6sw {
	u_int8_t op_ext;
	u_short op_type;
	int (*op_input) __P((struct opt6_any *, struct mbuf *,
			     struct mbuf *, int *));
	int (*op_output) __P((struct opt6_any *, struct mbuf *,
			      struct mbuf *));
	/* TODO: add alignment constraints and a check function ?? */
};
#endif /* _KERNEL */

#define OPT6_TYPE_NONE	0
#define OPT6_TYPE_GEN	1
#define OPT6_TYPE_DEF	2
#define OPT6_TYPE_END	3
/*
 * Definitions for Neighbor Discovery extensions.
 */

#define NDX6_LLADDR_SRC		1	/* Source Link-layer Address */
#define NDX6_LLADDR_TGT		2	/* Target Link-layer Address */
#define NDX6_PREF_INFO		3	/* Prefix-Information */
#define NDX6_RDRT_HDR		4	/* Redirected-Header */
#define NDX6_MTU		5	/* Maximum-Transmit-Unit */
#define NDX6_SHCUT_LIM		6	/* Shortcut Limit */

struct ndx6_any {			/* common header */
	u_int8_t	x6any_ext;	/* extension type */
	u_int8_t	x6any_len;	/* length */
	u_int16_t	x6any_res1;	/* reserved */
	u_int32_t	x6any_res2;	/* reserved */
};

struct ndx6_lladdr {			/* Link-layer Address */
	u_int8_t	lla_ext;	/* extension type (1 or 2) */
	u_int8_t	lla_len;	/* length (>=1) */
	u_int8_t	lla_addr[6];	/* media address */
};

struct ndx6_lladdrib { 			/* InfiniBand Link-layer Address */
	u_int8_t	lla_ext;	/* extension type (1 or 2) */
	u_int8_t	lla_len;	/* length (>=1) */
	u_int8_t	lla_addr[22];	/* media address */
};

struct ndx6_pref {			/* Prefix-Information */
	u_int8_t	pref_ext;	/* extension type (3) */
	u_int8_t	pref_len;	/* length (4) */
	u_int8_t	pref_plen;	/* prefix size (0..128) */
	u_int8_t	pref_flg;	/* flags */
	u_int32_t	pref_ilife;	/* invalidation lifetime */
	u_int32_t	pref_dlife;	/* deprecation lifetime */
	u_int32_t	pref_res2;
	struct in6_addr	pref_pref;	/* prefix */
};
#define	NDX6_PREF_FLG_L	0x80		/* On-link flag */
#define	NDX6_PREF_FLG_A	0x40		/* Address-configuration flag */

struct ndx6_mtu {			/* Maximum-Transmit-Unit */
	u_int8_t	mtu_ext;	/* extension type (5) */
	u_int8_t	mtu_len;	/* length (1) */
	u_int16_t	mtu_res;	/* reserved (0) */
	u_int32_t	mtu_mtu;	/* MTU value */
};

struct ndx6_sclim {			/* Shortcut Limit */
	u_int8_t	scl_ext;	/* extension type (6) */
	u_int8_t	scl_len;	/* length (1) */
	u_int8_t	scl_scl;	/* shortcut limit */
	u_int8_t	scl_res1;	/* reserved */
	u_int32_t	scl_res2;	/* reserved */
};

/*
* mobility extension for neighbor discovery
*/
#define NDX6_ADVINT     7               /* Advertisement interval (IANA)*/

struct ndx6_advint {
    u_int8_t advint_ext;                /* extension type (7) */
    u_int8_t advint_len;                /* length (1) */
    u_int16_t advint_res;               /* reserved (0) */
    u_int32_t advint_advint;            /* Advertisement value */
};

#define NDX6_ADVINF     8               /* Advertisement information (IANA)*/

struct ndx6_advinf {
    u_int8_t advinf_ext;                /* extension type (8) */
    u_int8_t advinf_len;                /* length (1) */
    u_int16_t advinf_res;               /* reserved (0) */
    u_int16_t advinf_pref;              /* Home Agent Preference */
    u_int16_t advinf_lifetime;          /* Home Agent Life Time */
};
#define NDX6_PREF_FLG_R 0x20            /* Router Address flag */
/* ======================================================================
  Mobile IPv6 Destination Options
====================================================================== */
struct opt6_homeaddr {
    u_int8_t ha_ext;
    u_int8_t ha_len;
    u_int8_t ha_padn;
    u_int8_t ha_padn_len;
    u_int8_t ha_pad[2];
    u_int8_t ha_otype;
    u_int8_t ha_olen;
    struct in6_addr ha_addr;
};

struct opt6_binding_upd {
    u_int8_t bu_ext;
    u_int8_t bu_len;
    u_int8_t bu_otype;
    u_int8_t bu_olen;
    u_int8_t bu_flags;
#define BU_DBIT 0x10
#define BU_RBIT 0x20
#define BU_HBIT 0x40
#define BU_ABIT 0x80
    u_int8_t bu_preflen;
    u_int16_t bu_seqno;
    u_int32_t bu_lifetime;
};

struct opt6_binding_ack {
    u_int8_t ba_ext;
    u_int8_t ba_len;
    u_int8_t ba_pad0;
    u_int8_t ba_otype;
    u_int8_t ba_olen;
    u_int8_t ba_status;
#define ENOREASON       128  /* Reason Unspecified */
#define EADMINPRO       130  /* Administratively prohibited */
#define ENORESRC        131  /* Insufficient resources */
#define ENOHOMEREG      132  /* Home registration not supported */
#define ENOTHOMENET     133  /* Not home network */
#define EPREFLEN        136  /* Incorrect Prefix Length */
#define ENOTHOMEAG      137  /* not home agent for this  node */
#define EDADFAIL	138  /* Duplicate Address Detection failed */
    u_int16_t ba_seqno;
    u_int32_t ba_lifetime;
    u_int32_t ba_refresh;
};

struct opt6_binding_req {
    u_int8_t br_ext;
    u_int8_t br_len;
    u_int8_t br_otype;
    u_int8_t br_olen;
    u_int8_t br_padn;
    u_int8_t br_padn_len;
    u_int8_t br_pad[2];
};
/*
 * Definitions for Router Renumbering operations
 */

#define RTRN6_FLG_TEST		0x80	/* Test message flag */
#define RTRN6_FLG_RSLT		0x40	/* Result wanted flag */
#define RTRN6_FLG_ALL		0x20	/* All interfaces flag */
#define RTRN6_FLG_SITE		0x10	/* in Site only flag */
#define RTRN6_FLG_PROC		0x08	/* Processes flag */
#define RTRN6_FLG_ERR		0x04	/* Error flag */

#define RTRN6_PRFOP_ADD		1	/* Prefix Add operation */
#define RTRN6_PRFOP_CHANGE	2	/* Prefix Change operation */
#define RTRN6_PRFOP_SETGLB	3	/* Prefix Set-Global operation */

#define RTRN6_UFLG_V	0x80000000	/* valid lifetime in real time */
#define RTRN6_UFLG_P	0x40000000	/* preferred lifetime in real time */

struct rtrn6_match {			/* Match-Prefix */
	u_int8_t	match_code;	/* opcode (RTRN6_PRFOP_*) */
	u_int8_t	match_len;	/* length (4N+3) */
	u_int8_t	match_ord;	/* ordinal */
	u_int8_t	match_plen;	/* prefix match length (0..128) */
	u_int32_t	match_res;	/* reserved */
	struct in6_addr	match_pref;	/* prefix */
};

struct rtrn6_use {			/* Use-Prefix */
	u_int8_t	use_plen;	/* prefix use length (0..128) */
	u_int8_t	use_klen;	/* prefix keep length (0..128) */
	u_int8_t	use_flgmsk;	/* flag mask (for RA) */
	u_int8_t	use_ramsk;	/* flags (for RA) */
	u_int32_t	use_ilife;	/* (in)valid lifetime */
	u_int32_t	use_dlife;	/* (deprecation) preferred lifetime */
	u_int32_t	use_flags;	/* flags (RTRN6_UFLG_?) */
	struct in6_addr	use_pref;	/* prefix */
};

struct rtrn6_report {			/* Match-Report */
	u_int16_t	rep_res;	/* reserved */
	u_int8_t	rep_ord;	/* ordinal */
	u_int8_t	rep_plen;	/* matched prefix length */
	u_int32_t	rep_ifidx;	/* interface index (SNMP IfGroup) */
	struct in6_addr	rep_pref;	/* matched prefix */
};

#ifdef _KERNEL
int	opt6_pad0_input __P((struct opt6_any *,
		struct mbuf *, struct mbuf *, int *));

int	opt6_padn_input __P((struct opt6_any *,
		struct mbuf *, struct mbuf *, int *));

int	opt6_rtalert_input __P((struct opt6_any *,
		struct mbuf *, struct mbuf *, int *));

int	opt6_skip_input __P((struct opt6_any *,
		struct mbuf *, struct mbuf *, int *));

int	opt6_disc_input __P((struct opt6_any *,
		struct mbuf *, struct mbuf *, int *));

int	opt6_ferr_input __P((struct opt6_any *,
		struct mbuf *, struct mbuf *, int *));

int	opt6_oerr_input __P((struct opt6_any *,
		struct mbuf *, struct mbuf *, int *));

int	opt6_pad0_output __P((struct opt6_any *,
		struct mbuf *, struct mbuf *));


int	opt6_gen_output __P((struct opt6_any *,
		struct mbuf *, struct mbuf *));
#endif
#endif
