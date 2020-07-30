/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/arpa/onameser_compat.h 1.4                  */
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
/* @(#)47	1.1  src/bos/usr/include/arpa/nameser.h, ipv6, ipv6 9/27/96 09:55:04 */
/* @(#)40	1.10.1.5  src/bos/usr/include/arpa/nameser.h, sockinc, bos420, 9613T 8/17/95 11:40:16 */
#ifndef _H_ARPA_ONAMESER_COMPAT
#define _H_ARPA_ONAMESER_COMPAT
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

#define PACKETSZ	512		/* maximum packet size */
#define MAXDNAME	256		/* maximum domain name */
#define MAXCDNAME	255		/* maximum compressed domain name */
#define MAXLABEL	63		/* maximum length of domain label */
#define HFIXEDSZ        12              /* #/bytes of fixed data in header */
#define QFIXEDSZ        4               /* #/bytes of fixed data in query */
#define RRFIXEDSZ       10              /* #/bytes of fixed data in r record */
#define INT32SZ         4               /* for systems without 32-bit ints */
#define INT16SZ         2               /* for systems without 16-bit ints */
#define INADDRSZ        4               /* for sizeof(struct inaddr) != 4 */
#define IN6ADDRSZ       16              /* for sizeof(struct inaddr6) != 16 */

/*
 * Internet nameserver port number
 */
#define NAMESERVER_PORT	53

/*
 * Currently defined opcodes
 */
#define QUERY		0x0		/* standard query */
#define IQUERY		0x1		/* inverse query */
#define STATUS		0x2		/* nameserver status query */
/*#define xxx		0x3		   0x3 reserved */
#define NS_NOTIFY_OP    0x4             /* notify secondary of SOA change */
#ifdef ALLOW_UPDATES
	/* non standard - supports ALLOW_UPDATES stuff from Mike Schwartz */
# define UPDATEA	0x9		/* add resource record */
# define UPDATED	0xa		/* delete a specific resource record */
# define UPDATEDA	0xb		/* delete all nemed resource record */
# define UPDATEM	0xc		/* modify a specific resource record */
# define UPDATEMA	0xd		/* modify all named resource record */
# define ZONEINIT       0xe             /* initial zone transfer */
# define ZONEREF	0xf		/* incremental zone referesh */
#endif

#ifdef DYNDNS
	/* non standard - supports ALLOW_UPDATES stuff from Mike Schwartz */
# define UPDATEA	0x9		/* add resource record */
# define UPDATED	0xa		/* delete a specific resource record */
# define UPDATEDA	0xb		/* delete all nemed resource record */
# define UPDATEM	0xc		/* modify a specific resource record */
# define UPDATEMA	0xd		/* modify all named resource record */
# define ZONEINIT       0xe             /* initial zone transfer */
# define ZONEREF	0xf		/* incremental zone referesh */
# define UPDATE		0x5		/* dyndns updates */
					/* NOTE! opcode not assigned yet */
					/*       arbitrary value used !! */

/* sub-opcodes for UPDATE message */
#define TYPE_DELETE     1
#define TYPE_ADDNEW     2
#define TYPE_ADDEXIST   3
#define TYPE_ADD        4
#define TYPE_ZONENAME   5

/* number of bytes of fixed header in an UPDATE */
#define UFIXEDSZ        4

#endif /* ifdef DNS_SECURITY */

/*
 * Currently defined response codes
 */
#define NOERROR		0		/* no error */
#define FORMERR		1		/* format error */
#define SERVFAIL	2		/* server failure */
#define NXDOMAIN	3		/* non existent domain */
#define NOTIMP		4		/* not implemented */
#define REFUSED		5		/* query refused */
#ifdef ALLOW_UPDATES
	/* non standard */
# define NOCHANGE	0xf		/* update failed to change db */
#endif

#ifdef DYNDNS
#define UPD_ALIAS	6		/* domain name specified in an update */
					/* is an alias */
#define UPD_NAME_EXISTS	7		/* name already exists */
#define UPD_RECORD_ERROR 8		/* resource record does not exist */
#define UPD_ZONE_ERROR	9		/* servernotauthoritative forthe zone */
					/*or update covers more than one zone */
#define UPD_VERSION_ERROR 10            /* time signed in SIG RR is wrong or */
					/* the SIG does not cover the records */
					/* updated */
# define NOCHANGE	0xf		/* update failed to change db */
#endif /* ifdef DYNDNS */

/*
 * Type values for resources and queries
 */
#define T_A		1		/* host address */
#define T_NS		2		/* authoritative server */
#define T_MD		3		/* mail destination */
#define T_MF		4		/* mail forwarder */
#define T_CNAME		5		/* connonical name */
#define T_SOA		6		/* start of authority zone */
#define T_MB		7		/* mailbox domain name */
#define T_MG		8		/* mail group member */
#define T_MR		9		/* mail rename name */
#define T_NULL		10		/* null resource record */
#define T_WKS		11		/* well known service */
#define T_PTR		12		/* domain name pointer */
#define T_HINFO		13		/* host information */
#define T_MINFO		14		/* mailbox information */
#define T_MX		15		/* mail routing information */
#define T_TXT		16		/* text strings */
#define T_RP            17              /* responsible person */
#define T_AFSDB         18              /* AFS cell database */
#define T_X25           19              /* X_25 calling address */
#define T_ISDN          20              /* ISDN calling address */
#define T_RT            21              /* router */
#define T_NSAP          22              /* NSAP address */
#define T_NSAP_PTR      23              /* reverse NSAP lookup (deprecated) */
#define T_SIG           24              /* security signature */
#define T_KEY           25              /* security key */
#define T_PX            26              /* X.400 mail mapping */
#define T_GPOS          27              /* geographical position (withdrawn) */
#define T_AAAA          28              /* IP6 Address */
#define T_LOC           29              /* Location Information */
	/* non standard */
#define T_UINFO		100		/* user (finger) information */
#define T_UID		101		/* user ID */
#define T_GID		102		/* group ID */
#define T_UNSPEC	103		/* Unspecified format (binary data) */
	/* Query type values which do not appear in resource records */
#define T_AXFR		252		/* transfer zone of authority */
#define T_MAILB		253		/* transfer mailbox records */
#define T_MAILA		254		/* transfer mail agent records */
#define T_ANY		255		/* wildcard match */

/*
 * Values for class field
 */

#define C_IN		1		/* the arpa internet */
#define C_CHAOS		3		/* for chaos net at MIT */
#define C_HESIOD	4		/* for Hesiod name server at MIT */
#define C_HS		C_HESIOD	/* for Hesiod name server at MIT */

	/* Query class values which do not appear in resource records */
#define C_ANY		255		/* wildcard match */

/*
 * Status return codes for T_UNSPEC conversion routines
 */
#define CONV_SUCCESS	0
#define CONV_OVERFLOW	(-1)
#define CONV_BADFMT	(-2)
#define CONV_BADCKSUM	(-3)
#define CONV_BADBUFLEN	(-4)

#ifndef BYTE_ORDER
#define LITTLE_ENDIAN   1234    /* least-significant byte first (vax) */
#define BIG_ENDIAN      4321    /* most-significant byte first (IBM, net) */
#define PDP_ENDIAN      3412    /* LSB first in word, MSW first in long (pdp) */

#if defined(vax) || defined(ns32000) || defined(sun386) || \
    defined(BIT_ZERO_ON_RIGHT)
#define BYTE_ORDER      LITTLE_ENDIAN

#endif
#if defined(sel) || defined(pyr) || defined(mc68000) || defined(sparc) || \
    defined(is68k) || defined (tahoe) ||  defined (sun) || \
    defined(RISC6000) || defined(aiws) || defined (_IBMESA) || \
    defined (BIT_ZERO_ON_LEFT) 
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
	u_int	pr:1;		/* primary server required (non standard) */
	u_int	unused:2;	/* unused bits */
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
	u_int	unused:2;	/* unused bits */
	u_int	pr:1;		/* primary server required (non standard) */
	u_int	ra:1;		/* recursion available */
#endif
			/* remaining bytes */
	u_short	qdcount;	/* number of question entries */
	u_short	ancount;	/* number of answer entries */
	u_short	nscount;	/* number of authority entries */
	u_short	arcount;	/* number of resource entries */
} HEADER;

#ifdef DYNDNS
/* for Dynamic Updates, the QUERY header is reused */
typedef struct {
	unsigned        id :16;         /* query identification number */
#if BYTE_ORDER == BIG_ENDIAN
			/* fields in third byte */
	unsigned        qr: 1;          /* response flag */
	unsigned        opcode: 4;      /* purpose of message */
	unsigned        z1: 3;          /* undefined - must be zero */
			/* fields in fourth byte */
	unsigned        z2: 4;          /* undefined - must be zero */
	unsigned        rcode :4;       /* response code */
#endif
#if BYTE_ORDER == LITTLE_ENDIAN || BYTE_ORDER == PDP_ENDIAN
			/* fields in third byte */
	unsigned        z1: 3;          /* undefined - must be zero */
	unsigned        opcode :4;      /* purpose of message */
	unsigned        qr :1;          /* response flag */
			/* fields in fourth byte */
	unsigned        rcode :4;       /* response code */
	unsigned        z2: 4;          /* undefined - must be zero */
#endif
			/* remaining bytes */
	unsigned        delcount :16;   /* number of delete RR's   */
	unsigned        newcount :16;   /* number of addnew RR's   */
	unsigned        oldcount :16;   /* number of addexist RR's */
	unsigned        addcount :16;   /* number of add RR's      */
} DYNDNS_HEADER;
#endif /*ifdef DNS_SECURITY*/

/*
 * Defines for handling compressed domain names
 */
#define INDIR_MASK	0xc0

/*
 * Structure for passing resource records around.
 */
struct rrec {
	short		r_zone;			/* zone number */
	short		r_class;		/* class number */
	short		r_type;			/* type number */
	__ulong32_t 	r_ttl;			/* time to live */
	int		r_size;			/* size of data area */
	char		*r_data;		/* pointer to data */
};

#ifdef _NO_PROTO

extern	u_short		_getshort();
extern	__ulong32_t	_getlong();

#else /* _NO_PROTO */

extern	u_short		_getshort(const u_char *);
extern	__ulong32_t	_getlong(const u_char *);

#endif /* _NO_PROTO */

/*
 * Inline versions of get/put short/long.
 * Pointer is advanced; we assume that both arguments
 * are lvalues and will already be in registers.
 * cp MUST be u_char *.
 */
#define GETSHORT(s, cp) { \
	(s) = *(cp)++ << 8; \
	(s) |= *(cp)++; \
}

#define GETLONG(l, cp) { \
	(l) = *(cp)++ << 8; \
	(l) |= *(cp)++; (l) <<= 8; \
	(l) |= *(cp)++; (l) <<= 8; \
	(l) |= *(cp)++; \
}


#define PUTSHORT(s, cp) { \
	*(cp)++ = (s) >> 8; \
	*(cp)++ = (s); \
}

#define PUTLONG(l, cp) { \
        register __ulong32_t t_l = (__ulong32_t)(l); \
	register u_char *t_cp = (u_char *)(cp); \
	*t_cp++ = t_l >> 24; \
	*t_cp++ = t_l >> 16; \
	*t_cp++ = t_l >> 8; \
	*t_cp   = t_l; \
	(cp) += sizeof(__ulong32_t); \
}

#endif  /* _H_ARPA_ONAMESER_COMPAT */
