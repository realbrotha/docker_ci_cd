/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/arpa/nameser_compat.h 1.5                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2000          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)06	1.5  src/bos/usr/include/arpa/nameser_compat.h, sockinc, bos530 1/23/00 22:32:31 */
#ifndef _H_ARPA_NAMESER_COMPAT_
#define _H_ARPA_NAMESER_COMPAT_
#ifdef _POWER_PROLOG_
/*
 *   COMPONENT_NAME: SOCKINC
 *
 *   FUNCTIONS: GETLONG, GETSHORT, PUTLONG, PUTSHORT
 *
 *   ORIGINS: 26,27
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1985,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#endif /* _POWER_PROLOG_ */

/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#include <sys/machine.h>

/*
 * Define constants based on rfc883
 */

#define PACKETSZ        NS_PACKETSZ
#define MAXDNAME        NS_MAXDNAME
#define MAXCDNAME       NS_MAXCDNAME
#define MAXLABEL        NS_MAXLABEL
#define HFIXEDSZ        NS_HFIXEDSZ
#define QFIXEDSZ        NS_QFIXEDSZ
#define RRFIXEDSZ       NS_RRFIXEDSZ
#define INT32SZ         NS_INT32SZ
#define INT16SZ         NS_INT16SZ
#define INADDRSZ        NS_INADDRSZ
#define IN6ADDRSZ       NS_IN6ADDRSZ
#define INDIR_MASK      NS_CMPRSFLGS
#define NAMESERVER_PORT NS_DEFAULTPORT

#ifdef OSECURE_UPDATE
/* constants for non-standard update protocol. */
#define UFIXEDSZ	NS_UFIXEDSZ
#endif

/*
 * Currently defined opcodes
 */
#define S_ZONE          ns_s_zn
#define S_PREREQ        ns_s_pr
#define S_UPDATE        ns_s_ud
#define S_ADDT          ns_s_ar

#define QUERY           ns_o_query
#define IQUERY          ns_o_iquery
#define STATUS          ns_o_status
#define NS_NOTIFY_OP    ns_o_notify
#define NS_UPDATE_OP    ns_o_update

#define NOERROR         ns_r_noerror
#define FORMERR         ns_r_formerr
#define SERVFAIL        ns_r_servfail
#define NXDOMAIN        ns_r_nxdomain
#define NOTIMP          ns_r_notimpl
#define REFUSED         ns_r_refused
#define YXDOMAIN        ns_r_yxdomain
#define YXRRSET         ns_r_yxrrset
#define NXRRSET         ns_r_nxrrset
#define NOTAUTH         ns_r_notauth
#define NOTZONE         ns_r_notzone

#define DELETE          ns_uop_delete
#define ADD             ns_uop_add

#define T_A             ns_t_a
#define T_NS            ns_t_ns
#define T_MD            ns_t_md
#define T_MF            ns_t_mf
#define T_CNAME         ns_t_cname
#define T_SOA           ns_t_soa
#define T_MB            ns_t_mb
#define T_MG            ns_t_mg
#define T_MR            ns_t_mr
#define T_NULL          ns_t_null
#define T_WKS           ns_t_wks
#define T_PTR           ns_t_ptr
#define T_HINFO         ns_t_hinfo
#define T_MINFO         ns_t_minfo
#define T_MX            ns_t_mx
#define T_TXT           ns_t_txt
#define T_RP            ns_t_rp
#define T_AFSDB         ns_t_afsdb
#define T_X25           ns_t_x25
#define T_ISDN          ns_t_isdn
#define T_RT            ns_t_rt
#define T_NSAP          ns_t_nsap
#define T_NSAP_PTR      ns_t_nsap_ptr
#define T_SIG           ns_t_sig
#define T_KEY           ns_t_key
#define T_PX            ns_t_px
#define T_GPOS          ns_t_gpos
#define T_AAAA          ns_t_aaaa
#define T_LOC           ns_t_loc
#define T_NXT           ns_t_nxt
#define T_EID           ns_t_eid
#define T_NIMLOC        ns_t_nimloc
#define T_SRV           ns_t_srv
#define T_ATMA          ns_t_atma
#define T_NAPTR         ns_t_naptr
#define T_TSIG		ns_t_tsig
#define T_IXFR          ns_t_ixfr
#define T_AXFR          ns_t_axfr
#define T_MAILB         ns_t_mailb
#define T_MAILA         ns_t_maila
#define T_ANY           ns_t_any
#ifdef _AIX
#define T_UINFO		ns_t_uinfo
#define T_UID		ns_t_uid
#define T_GID		ns_t_gid
#define T_UNSPEC	ns_t_unspec
#endif

#ifdef OSECURE_UPDATE
#define TYPE_DELETE		ns_ouop_delete
#define TYPE_ADDNEW		ns_ouop_addnew
#define TYPE_ADDEXIST		ns_ouop_addexist
#define TYPE_ADD		ns_ouop_add
#define TYPE_ZONENAME		ns_ouop_zone
#define UPD_ALIAS		ns_ourc_alias
#define UPD_NAME_EXISTS		ns_ourc_yxdomain
#define UPD_RECORD_ERROR	ns_ourc_nxrr
#define UPD_ZONE_ERROR		ns_ourc_zoneerror
#define UPD_VERSION_ERROR	ns_ourc_versionerror
#define NOCHANGE		ns_ourc_nochange
#endif /* OSECURE_UPDATE */

/*
 * Values for class field
 */

#define C_IN            ns_c_in
#define C_CHAOS         ns_c_chaos
#define C_HS            ns_c_hs
/* BIND_UPDATE */
#define C_NONE          ns_c_none
#define C_ANY           ns_c_any

#ifndef BYTE_ORDER
#define LITTLE_ENDIAN   1234    /* least-significant byte first (vax) */
#define BIG_ENDIAN      4321    /* most-significant byte first (IBM, net) */
#define PDP_ENDIAN      3412    /* LSB first in word, MSW first in long (pdp) */

#if defined(vax) || defined(ns32000) || defined(sun386) || defined(i386) || \
    defined(MIPSEL) || defined(_MIPSEL) || defined(BIT_ZERO_ON_RIGHT) || \
    defined(__alpha__) || defined(__alpha) || \
    (defined(__Lynx__) && defined(__x86__))
#define BYTE_ORDER      LITTLE_ENDIAN
#endif

#if defined(sel) || defined(pyr) || defined(mc68000) || defined(sparc) || \
    defined(is68k) || defined(tahoe) || defined(ibm032) || defined(ibm370) || \
    defined(MIPSEB) || defined(_MIPSEB) || defined(_IBMR2) || defined(DGUX) ||\
    defined(apollo) || defined(__convex__) || defined(_CRAY) || \
    defined(RISC6000) || defined(_IBMESA) || defined(aiws) || \
    defined(__hppa) || defined(__hp9000) || \
    defined(__hp9000s300) || defined(__hp9000s700) || \
    defined (BIT_ZERO_ON_LEFT) || defined(m68k) || \
    (defined(__Lynx__) && \
     (defined(__68k__) || defined(__sparc__) || defined(__powerpc__)))
#define BYTE_ORDER      BIG_ENDIAN
#endif

#endif /* BYTE_ORDER */

#ifndef BYTE_ORDER
        /* you must determine what the correct bit order is for your compiler */
#define   UNDEFINED_BIT_ORDER
#endif

/*
 * Structure for query header, the order of the fields is machine and
 * compiler dependent, in our case, the bits within a byte are assignd 
 * least significant first, while the order of transmition is most 
 * significant first.  This requires a somewhat confusing rearrangement.
 */

typedef struct {
	u_short	id;		/* query identification number */
#if BYTE_ORDER == BIG_ENDIAN
			/* fields in third byte */
	u_int	qr:1;		/* response flag */
	u_int	opcode:4;	/* purpose of message */
	u_int	aa:1;		/* authoritive answer */
	u_int	tc:1;		/* truncated message */
	u_int	rd:1;		/* recursion desired */
			/* fields in fourth byte */
	u_int	ra:1;		/* recursion available */
	u_int	ad:1;		/* authentic data from named */
	u_int   cd:1;		/* checking disabled by resolver */
	u_int	unused:1;	/* unused bits */
	u_int	rcode:4;	/* response code */
#endif
#if BYTE_ORDER == LITTLE_ENDIAN
			/* fields in third byte */
	u_int	rd:1;		/* recursion desired */
	u_int	tc:1;		/* truncated message */
	u_int	aa:1;		/* authoritive answer */
	u_int	opcode:4;	/* purpose of message */
	u_int	qr:1;		/* response flag */
			/* fields in fourth byte */
	u_int	rcode:4;	/* response code */
	u_int	cd:1;		/* checking disabled by resolver */
	u_int	ad:1;		/* authentic data from named */
	u_int	unused:1;	/* unused bits */
	u_int	ra:1;		/* recursion available */
#endif
			/* remaining bytes */
	u_short	qdcount;	/* number of question entries */
	u_short	ancount;	/* number of answer entries */
	u_short	nscount;	/* number of authority entries */
	u_short	arcount;	/* number of resource entries */
} HEADER;

#define GETSHORT	NS_GET16
#define GETLONG		NS_GET32
#define PUTSHORT	NS_PUT16
#define PUTLONG		NS_PUT32

#endif  /* _H_ARPA_NAMESER_COMPAT_ */
