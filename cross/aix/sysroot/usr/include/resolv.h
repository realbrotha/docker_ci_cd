/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53A src/bos/usr/include/resolv.h 1.4.2.6                            */
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
/* @(#)75       1.4.2.6  src/bos/usr/include/resolv.h, sockinc, bos53A, a2004_39D8 8/24/04 16:03:39 */
#ifndef _H_RESOLV
#define _H_RESOLV

#include <sys/param.h>
#include <sys/types.h>
#include <sys/cdefs.h>
#include <stdio.h>
#include <netinet/in.h>

#ifdef _POWER_PROLOG_
/*
 *   COMPONENT_NAME: SOCKINC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 26,27,71
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#endif /* _POWER_PROLOG_ */

/*
 *
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */

/*
 * Portions Copyright (c) 1996-1999 by Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL INTERNET SOFTWARE
 * CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#ifdef _USE_IRS
#define IRS_CONST_UCHAR const u_char
#define IRS_CONST_CHAR const char
#else /* _USE_IRS */
#define IRS_CONST_UCHAR char
#define IRS_CONST_CHAR char
#endif /* _USE_IRS */

/*
 * NOTE: MAXDNAME is also defined in <arpa/nameser_compat.h>
 *       and <arpa/onameser_compat.h> files.
 *       If the values changed in any one of the above 2 files,
 *       we need to change the constant value here to keep
 *       it consistant.
 */

/*undef before redefining to get rid of the warnings*/
#ifdef MAXDNAME
#undef MAXDNAME
#endif

#ifdef _USE_IRS
#define MAXDNAME  1025
#else /* _USE_IRS */
#define MAXDNAME  256
#endif /* _USE_IRS */

/*
 * Revision information.  This is the release date in YYYYMMDD format.
 * It can change every day so the right thing to do with it is use it
 * in preprocessor commands such as "#if (__RES > 19931104)".  Do not
 * compare for equality; rather, use it to determine whether your resolver
 * is new enough to contain a certain feature.
 */

#define	__RES			19991006

/*
 * Resolver configuration file.
 * Normally not present, but may contain the address of the
 * inital name server(s) to query and the domain search list.
 */

#ifndef _PATH_RESCONF
#define _PATH_RESCONF        "/etc/resolv.conf"
#endif

typedef enum { res_goahead, res_nextns, res_modified, res_done, res_error }
	res_sendhookact;

typedef res_sendhookact (*res_send_qhook)(struct sockaddr_in **ns,
	const u_char **query,
	int *querylen,
	u_char *ans,
	int anssiz,
	int *resplen);

typedef res_sendhookact (*res_send_rhook)(struct sockaddr_in *ns,
	const u_char *query,
	int querylen,
	u_char *ans,
	int anssiz,
	int *resplen);

struct	res_sym {
	int	number;		/* Identifying number, like T_MX */
	char	*name;		/* Its symbolic name, like "MX" */
	char	*humanname;	/* Its fun name, like "mail exchanger" */
};

/*
 * Global defines and variables for resolver stub.
 */
#define	MAXNS			3	/* max # name servers we'll track */
#define	MAXDFLSRCH		3	/* # default domain levels to try */
#define	MAXDNSRCH		6	/* max # domains in search path */
#define	LOCALDOMAINPARTS 	2	/* min levels in name that is "local" */

#define	RES_TIMEOUT		5	/* min. seconds between retries */
#define	MAXRESOLVSORT		10	/* number of net to sort on */
#define	RES_MAXNDOTS		15	/* should reflect bit field size */
#define RES_MAXRETRANS		30	/* only for resolv.conf/RES_OPTIONS */
#define RES_MAXRETRY		5	/* only for resolv.conf/RES_OPTIONS */
#define RES_DFLRETRY		2	/* Default #/tries. */
#define RES_MAXTIME             65535   /* Infinity, in milliseconds. */

union res_sockaddr_union {
        struct sockaddr_in      sin;
        struct sockaddr_in6     sin6;
};

struct __res_state_ext {
        union res_sockaddr_union nsaddrs[MAXNS];
};


/*
 * This header file has been munged some from the ISC distribution
 * to support previous programs that have defined or interacted with
 * _res as a "struct state" rather than a "struct __res_state".
 * A further complication is the name of the routine __res_state(),
 * which returns the address of the thread's resolver context.
 * Macros are defined herein so that the "struct __res_state"definition
 * and _res macro to refer to the thread's resolver context work
 * for previously written programs and new ports, however, a direct
 * call to __res_state() is not possible without defining
 * BIND_8_RESSTATE before including this header.
 */
#ifdef BIND_8_RESSTATE
struct __res_state
#else
#define __res_state state
struct state
#endif
{
	int	retrans;	 	/* retransmition time interval */
	int	retry;			/* number of times to retransmit */
	__ulong32_t options;		/* option flags - see below. */
	int	nscount;		/* number of name servers */
	struct	sockaddr_in
		nsaddr_list[MAXNS];	/* address of name server */
#define	nsaddr	nsaddr_list[0]		/* for backward compatibility */
	u_short	id;			/* current message id */
	char	olddefdname[256];	/* default domain */
	char	*dnsrch[MAXDNSRCH+1];	/* components of domain to search */
	__ulong32_t pfcode;             /* RES_PRF_ flags - see below. */
	unsigned ndots:4;               /* threshold for initial abs. query */
	unsigned nsort:4;               /* number of elements in sort_list[] */
	char    unused[3];
	struct {
		struct in_addr	addr;
		__ulong32_t	mask;
	} sort_list[MAXRESOLVSORT];
	int	sizeof_defdname;
	char	defdname[MAXDNAME];	/* default domain */
	res_send_qhook qhook;		/* query hook */
	res_send_rhook rhook;		/* response hook */
	int	res_h_errno;		/* last one set for this context */
	int	_sock;			/* PRIVATE: for res_send i/o */
	u_int	_flags;			/* PRIVATE: see below */
        struct {
                u_int16_t		nscount;
                u_int16_t		nstimes[MAXNS]; /* ms. */
                int                     nssocks[MAXNS];
                struct __res_state_ext ext;    /* extention for IPv6 */
        } _ext;
};

typedef struct __res_state *res_state;


/*
 * Resolver flags (used to be discrete per-module static ints).
 */
#define RES_F_VC	0x00000001	/* socket is TCP */
#define RES_F_CONN	0x00000002	/* socket is connected */

/* res_findzonecut() options */
#define RES_EXHAUSTIVE	0x00000001	/* always do all queries */

/*
 * Resolver options
 */
#define RES_INIT	0x00000001	/* address initialized */
#define RES_DEBUG	0x00000002	/* print debug messages */
#define RES_AAONLY	0x00000004	/* authoritative answers only (!IMPL)*/
#define RES_USEVC	0x00000008	/* use virtual circuit */
#define RES_PRIMARY	0x00000010	/* query primary server only (!IMPL) */
#define RES_IGNTC	0x00000020	/* ignore trucation errors */
#define RES_RECURSE	0x00000040	/* recursion desired */
#define RES_DEFNAMES	0x00000080	/* use default domain name */
#define RES_STAYOPEN	0x00000100	/* Keep TCP socket open */
#define RES_DNSRCH	0x00000200	/* search up local domain tree */
#define RES_INSECURE1	0x00000400	/* type 1 security disabled */
#define RES_INSECURE2	0x00000800	/* type 2 security disabled */
#define RES_NOALIASES	0x00001000	/* shuts off HOSTALIASES feature */
#define RES_MAPINET6	0x00002000
#define RES_MAPINET4	0x00004000
#define RES_MAPSIT	0x00008000
#define RES_NOFALL6	0x00010000
#define RES_USE_INET6	0x00020000	/* use/map IPv6 in gethostbyname() */
#define RES_ROTATE	0x00040000	/* rotate ns list after each query */
#define RES_NOCHECKNAME	0x00080000	/* do not check names for sanity */
#define RES_KEEPTSIG	0x00100000	/* do not strip TSIG records */
#define RES_BLAST       0x00200000      /* blast all recursive servers */
#define RES_NO_NIBBLE   0x00400000      /* disable IPv6 nibble mode reverse */
#define RES_NO_BITSTRING 0x0800000      /* disable IPv6 bitstring mode reverse */
#define RES_NOTLDQUERY  0x01000000      /* don't unqualified name as a tld */
#define RES_USE_DNSSEC  0x02000000      /* use DNSSEC using OK bit in OPT */
/* KAME extensions: use higher bit to avoid conflict with ISC use */
#define RES_USE_DNAME   0x10000000      /* use DNAME */
#define RES_USE_A6      0x20000000      /* use A6 */
#define RES_USE_EDNS0   0x40000000      /* use EDNS0 if configured */
#define RES_NO_NIBBLE2  0x80000000      /* disable alternate nibble lookup */

#define RES_DEFAULT	(RES_RECURSE | RES_DEFNAMES | RES_DNSRCH)

/*
 * Resolver "pfcode" values.  Used by dig.
 */
#define RES_PRF_STATS	0x00000001
#define RES_PRF_UPDATE	0x00000002 
#define RES_PRF_CLASS 	0x00000004
#define RES_PRF_CMD   	0x00000008
#define RES_PRF_QUES  	0x00000010
#define RES_PRF_ANS   	0x00000020
#define RES_PRF_AUTH  	0x00000040
#define RES_PRF_ADD	0x00000080
#define RES_PRF_HEAD1 	0x00000100
#define RES_PRF_HEAD2 	0x00000200
#define RES_PRF_TTLID 	0x00000400
#define RES_PRF_HEADX 	0x00000800
#define RES_PRF_QUERY 	0x00001000
#define RES_PRF_REPLY 	0x00002000
#define RES_PRF_INIT  	0x00004000
#define RES_PRF_TRUNC   0x00008000
/*                      0x00010000      */


#ifdef BIND_8_RESSTATE
extern struct __res_state *__res_state(void);
#define WHICH_RES_STATE() __res_state()
#else
extern struct __res_state *__which_res_state(void);
#define WHICH_RES_STATE() __which_res_state()
#endif

#define _res (*WHICH_RES_STATE())

#define RES_SET_H_ERRNO(r,x) __h_errno_set(r,x)
void __h_errno_set(struct __res_state *res, int err);

extern int hostalias_r(char *name, char *abuf, int len);
#ifdef _USE_IRS
extern const u_char *hostalias(char *name);
#else /* _USE_IRS */
extern char *hostalias(char *name);
#endif /* _USE_IRS */

extern unsigned long uchar_to_base64(unsigned char *src,
	unsigned long srclength,
	unsigned char *target);

extern unsigned long base64_to_uchar(unsigned char *src,
	unsigned long srclength,
	unsigned char *target);

extern int		res_hnok(const char *);
extern int		res_ownok(const char *);
extern int		res_mailok(const char *);
extern int		res_dnok(const char *);
extern int		sym_ston(const struct res_sym *, const char *, int *);
extern IRS_CONST_CHAR *	sym_ntos(const struct res_sym *, int, int *);
extern IRS_CONST_CHAR *	sym_ntop(const struct res_sym *, int, int *);
extern int		b64_ntop(u_char const *, size_t, char *, size_t);
extern int		b64_pton(char const *, u_char *, size_t);
extern int		loc_aton(const char *ascii, u_char *binary);
extern IRS_CONST_CHAR *	loc_ntoa(const u_char *binary, char *ascii);
extern int 		dn_skipname(const u_char *, const u_char *);
extern void 		fp_query(const u_char *, FILE *);
extern void 		fp_nquery(const u_char *, int, FILE *);
extern void 		putlong(__ulong32_t, u_char *);
extern void 		putshort(uint16_t, u_char *);
extern IRS_CONST_CHAR *	p_class(int);
extern IRS_CONST_CHAR *	p_time(__ulong32_t);
extern IRS_CONST_CHAR *	p_type(int);
extern IRS_CONST_CHAR *	p_rcode(int);
extern void 		p_query(const u_char *);
extern void 		p_queryL(u_char *, int len);
extern IRS_CONST_UCHAR * p_cdnname(const u_char *, const u_char *, int, FILE *);
extern IRS_CONST_UCHAR * p_cdname(const u_char *, const u_char *, FILE *);
extern IRS_CONST_UCHAR * p_fqnname(const u_char *cp, const u_char *msg, int, 
				  char *, int);
extern IRS_CONST_UCHAR * p_fqname(const u_char *, const u_char *, FILE *);
extern char *		p_rr(char *, char *, FILE *);
extern IRS_CONST_CHAR *	p_option(__ulong32_t option);
extern char *		p_secstodate(__ulong32_t);
extern int		dn_count_labels(const char *);
extern int 		dn_comp(const char *, u_char *, int, u_char **, 
				u_char **);
extern int 		dn_expand(const u_char *, const u_char *, 
				  const u_char *, char *, int);
extern int 		res_init(void);
extern int 		_res_init(void);
extern u_int		res_randomid(void);
extern int 		res_query(const char *, int, int, u_char *, int);
extern int 		res_search(const char *, int, int, u_char *, int);
extern int 		res_querydomain(const char *, const char *, int, 
					int, u_char *, int);
extern int		res_mkquery(int, const char *, int, int, const u_char *,
				    int, const u_char *, u_char *, int);
extern int		res_send(const u_char *, int, u_char *, int);
extern int		res_isourserver(const struct sockaddr_in *);
extern int		res_nameinquery(const char *, int, int,
					const u_char *, const u_char *);
extern int		res_queriesmatch(const u_char *, const u_char *,
					 const u_char *, const u_char *);
extern void		res_close(void);
extern IRS_CONST_CHAR *	p_section(int section, int opcode);

/* Things involving a resolver context. */

extern int		res_ninit(res_state);
extern int		res_nisourserver(const res_state,
					 const struct sockaddr_in *);
extern void		fp_resstat(const res_state, FILE *);
extern void		fp_npquery(const res_state, const u_char *,
				   int, FILE *);
extern IRS_CONST_CHAR *	res_hostalias(const res_state, const char *, char *,
				      size_t);
extern int		res_nquery(res_state, const char *, int, int,
				   u_char *, int);
extern int		res_nsearch(res_state, const char *, int, int,
				    u_char *, int);
extern int		res_nquerydomain(res_state, const char *, const char *,
					 int, int, u_char *, int);
extern int		res_nmkquery(res_state, int, const char *, int,
				     int, const u_char *, int, const u_char *,
				     u_char *, int);
extern int		res_nsend(res_state, const u_char *, int,
				  u_char *, int);
void			res_nclose(res_state);
void            	res_setservers (res_state, const union res_sockaddr_union *, int);
int             	res_getservers (res_state, union res_sockaddr_union *, int);

#ifdef _ARPA_NAMESER_H_
/* ns_tsig_key and ns_class are defined in nameser.h instead of in here. */
/* someone who needs res_nsendsigned or res_findzonecut will have to     */
/* include that file first.                                              */
extern int		res_nsendsigned(res_state, const u_char *, int,
					ns_tsig_key *, u_char *, int);
extern int		res_findzonecut(res_state, const char *, ns_class, int,
					char *, size_t, struct in_addr *, int);
#endif /* _ARPA_NAMESER_H_ */

extern const struct res_sym __p_key_syms[];
extern const struct res_sym __p_cert_syms[];
extern const struct res_sym __p_class_syms[];
extern const struct res_sym __p_type_syms[];
extern const struct res_sym __p_rcode_syms[];

#define res_init _res_init

#endif /* _H_RESOLV */
