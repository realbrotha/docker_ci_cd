/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/xti.h 1.4.2.19                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1991,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)46     1.4.2.19  src/bos/kernel/sys/xti.h, sysxpse, bos530 8/5/03 09:35:06 */
/*
 *   COMPONENT_NAME: SYSXPSE
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 18,27,63
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1991,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *   (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC.
 *   All Rights Reserved
 *
 *   Copyright (c) 1989  Mentat Inc.
 *
 */

#ifndef _XTI_H
#define _XTI_H

#ifdef _ALL_SOURCE
#include <stdio.h>
#include <string.h>
#endif

#include <standards.h>
#include <sys/types.h>

#ifndef _T_SCALAR_DEF
#ifdef __64BIT__
typedef signed int      t_scalar_t;
typedef unsigned int    t_uscalar_t;
#else
typedef signed long     t_scalar_t;
typedef unsigned long   t_uscalar_t;
#endif /* __64BIT__ */
#define _T_SCALAR_DEF
#endif

/* Error values */
#define	TBADADDR	1
#define	TBADOPT		2
#define	TACCES		3
#define	TBADF		4
#define	TNOADDR		5
#define	TOUTSTATE	6
#define	TBADSEQ		7
#define TSYSERR		8
#define	TLOOK		9
#define	TBADDATA	10
#define	TBUFOVFLW	11
#define	TFLOW		12
#define	TNODATA		13
#define	TNODIS		14
#define	TNOUDERR	15
#define	TBADFLAG	16
#define	TNOREL		17
#define	TNOTSUPPORT	18
#define	TSTATECHNG	19
#define	TNOSTRUCTYPE	20
#define TBADNAME	21
#define	TBADQLEN	22
#define	TADDRBUSY	23
#define TINDOUT		24
#define TPROVMISMATCH	25
#define TRESQLEN	26
#define TRESADDR	27
#define TQFULL		28
#define TPROTO		29

/* t_look events */
#define	T_LISTEN	0x0001
#define	T_CONNECT	0x0002
#define	T_DATA		0x0004
#define	T_EXDATA	0x0008
#define	T_DISCONNECT	0x0010
#define	T_UDERR		0x0040
#define	T_ORDREL	0x0080
#define	T_GODATA	0x0100
#define	T_GOEXDATA	0x0200
#define	T_EVENTS	0x0400
/*#define	T_ERROR	*/

/* Flag definitions */
#define	T_MORE		0x01
#define	T_EXPEDITED	0x02
#define	T_NEGOTIATE	0x04
#define	T_CHECK		0x08
#define	T_DEFAULT	0x10
#define T_SUCCESS	0x20
#define	T_FAILURE	0x40
#define T_CURRENT	0x0080
#define T_PARTSUCCESS	0x0100
#define T_READONLY	0x0200
#define T_NOTSUPPORT	0x0400
#define T_PUSH		0x0800

/* iov maximum */
#define	T_IOV_MAX	16	/* maximum number of scatter/gather buffers */

struct	t_iovec {
	void    *iov_base;
	size_t  iov_len;
};

struct t_info {
	t_scalar_t	addr;
	t_scalar_t	options;
	t_scalar_t	tsdu;
	t_scalar_t	etsdu;
	t_scalar_t	connect;
	t_scalar_t	discon;
	t_scalar_t	servtype;
	t_scalar_t	flags;
};

/* Flags defines (other info about the transport provider) */
#define T_SENDZERO	0x001	/* supports 0-length TSDUs */
#define T_ORDRELDATA	0x002	/* supports orderly release data */

/* Service types */
#define T_COTS		1	/* Connection-mode service */
#define	T_COTS_ORD	2	/* Connection service with orderly release */
#define	T_CLTS		3	/* Connectionless-mode service */

struct netbuf {
	unsigned int	maxlen;
	unsigned int	len;
#if _XOPEN_SOURCE>=500
	void *		buf;
#else
	char *		buf;
#endif
};

struct t_opthdr { 
	t_uscalar_t len; 	/* total option length- sizeof(struct t_opthdr)
				   + length of option value in bytes */
	t_uscalar_t level;	/* protocol affected */ 
	t_uscalar_t name;	/* option name */
	t_uscalar_t status;	/* status value */
	/* followed by the option value */
};

struct t_bind {
	struct netbuf	addr;
	unsigned int	qlen;
};

struct t_optmgmt {
	struct netbuf	opt;
	t_scalar_t	flags;
};

struct t_discon {
	struct netbuf	udata;
	int		reason;
	int		sequence;
};

struct t_call {
	struct netbuf	addr;
	struct netbuf	opt;
	struct netbuf	udata;
	int		sequence;
};

struct t_unitdata {
	struct netbuf	addr;
	struct netbuf	opt;
	struct netbuf	udata;
};

struct t_uderr {
	struct netbuf	addr;
	struct netbuf	opt;
	t_scalar_t	error;
};

/* t_alloc structure types */
#define	T_BIND		1
#define T_OPTMGMT	2
#define	T_CALL		3
#define	T_DIS		4
#define	T_UNITDATA	5
#define	T_UDERROR	6
#define	T_INFO		7

/* t_alloc field identifiers */
#define	T_ADDR		0x01
#define	T_OPT		0x02
#define	T_UDATA		0x04
#define	T_ALL		0xffff

/* State values */
#define	T_UNBND		1	/* unbound */
#define	T_IDLE		2	/* idle */
#define	T_OUTCON	3	/* outgoing connection pending */
#define	T_INCON		4	/* incoming connection pending */
#define	T_DATAXFER	5	/* data transfer */
#define	T_OUTREL	6	/* outgoing orderly release */
#define	T_INREL		7	/* incoming orderly release */

/* general purpose defines */
#define	T_YES		1
#define	T_NO		0
#define	T_UNUSED	(-1)
#define	T_NULL		0
#define	T_ABSREQ	0x8000
#define T_INFINITE	(-1)
#define T_INVALID	(-2)

/* Definitions for t_sysconf */
#define	_SC_T_IOV_MAX	0


#define T_UNSPEC	(~0 - 2)
#define T_ALLOPT	0
#define T_ALIGN(p)	(((t_uscalar_t) (p) + (sizeof(t_scalar_t) - 1)) \
				& ~(sizeof (t_scalar_t) - 1))

#define _T_USCALAR_ALIGN(p)  (((uintptr_t)(p) + (sizeof (t_scalar_t)-1))\
				& ~(sizeof (t_scalar_t)-1))

#define T_OPT_DATA(tohp) \
	((unsigned char *)(tohp) + sizeof (struct t_opthdr))

#define _T_NEXTHDR(pbuf,buflen,popt) \
		   (((char *)(popt) + _T_USCALAR_ALIGN((popt)->len) + \
			sizeof (struct t_opthdr) <= \
				((char *)(pbuf) + buflen)) ? \
		   (struct t_opthdr *)((char*)(popt) + \
			_T_USCALAR_ALIGN((popt)->len)) :\
		   	(struct t_opthdr *)0)

#define OPT_NEXTHDR(pbuf,buflen,popt)\
		   (((char *)(popt) + T_ALIGN((popt)->len) <\
		   (char *)(pbuf) + buflen) ?\
		   (struct t_opthdr *)((char*)(popt) + T_ALIGN((popt)->len)) :\
		   (struct t_opthdr *)0)

#define T_OPT_FIRSTHDR(nbp) \
    ((((char *)(nbp)->buf + sizeof (struct t_opthdr)) <= \
	    (char *)(nbp)->buf + (nbp)->len) ? \
		    (struct t_opthdr *)(nbp)->buf : (struct t_opthdr *)0)

/*
 * struct t_opthdr *T_OPT_NEXTHDR(struct netbuf *nbp, struct t_opthdr *tohp):
 * Skip to next option header
 * This implementation assumes "sizeof (t_uscalar_t)" 
 * as the alignment size for its option data and option header.
 */
#define T_OPT_NEXTHDR(nbp, tohp)  _T_NEXTHDR((nbp)->buf,(nbp)->len, (tohp))


/* XTI Level */
#define XTI_GENERIC	0xffff

/* XTI-level Options */
#define XTI_DEBUG	0x0001
#define XTI_LINGER	0x0080
#define XTI_RCVBUF	0x1002
#define XTI_RCVLOWAT	0x1004
#define XTI_SNDBUF	0x1001
#define XTI_SNDLOWAT	0x1003
#define XTI_ERROR	0x1007

struct t_linger { 
	t_scalar_t	l_onoff; 
	t_scalar_t	l_linger; 
};

/* ISO definitions */
#define	T_CLASS0	0
#define	T_CLASS1	1
#define	T_CLASS2	2
#define	T_CLASS3	3
#define	T_CLASS4	4

/* priorities */
#define	T_PRITOP	0
#define	T_PRIHIGH	1
#define	T_PRIMID	2
#define	T_PRILOW	3
#define	T_PRIDFLT	4

/* protection levels */
#define	T_NOPROTECT		1
#define	T_PASSIVEPROTECT	2
#define	T_ACTIVEPROTECT		4

/* default value for the length of TPDU's */
#define	T_LTPDUDFLT	128

/* rate structure */
struct rate {
	t_scalar_t	targetvalue;
	t_scalar_t	minacceptvalue;
};

/* reqvalue structure */
struct reqvalue {
	struct rate	called;
	struct rate	calling;
};

/* throughput structure */
struct thrpt {
	struct reqvalue	maxthrpt;
	struct reqvalue	avgthrpt;
};

struct transdel { 
	struct reqvalue maxdel; 
	struct reqvalue avgdel; 
};

/* Protocol Levels */

#define T_ISO_TP	0x0100
#define ISO_TP		0x0100

/* ISO-level Options */
#define T_TCO_THROUGHPUT	0x0001
#define TCO_THROUGHPUT		0x0001
#define T_TCO_TRANSDEL		0x0002
#define TCO_TRANSDEL		0x0002
#define T_TCO_RESERRORRATE	0x0003
#define TCO_RESERRORRATE	0x0003
#define T_TCO_TRANSFFAILPROB	0x0004
#define TCO_TRANSFFAILPROB	0x0004
#define T_TCO_ESTFAILPROB	0x0005
#define TCO_ESTFAILPROB		0x0005
#define T_TCO_RELFAILPROB	0x0006
#define TCO_RELFAILPROB		0x0006
#define T_TCO_ESTDELAY		0x0007
#define TCO_ESTDELAY		0x0007
#define T_TCO_RELDELAY		0x0008
#define TCO_RELDELAY		0x0008
#define T_TCO_CONNRESIL		0x0009
#define TCO_CONNRESIL		0x0009
#define T_TCO_PROTECTION	0x000a
#define TCO_PROTECTION		0x000a
#define T_TCO_PRIORITY		0x000b
#define TCO_PRIORITY		0x000b
#define T_TCO_EXPD		0x000c
#define TCO_EXPD		0x000c

#define T_TCL_TRANSDEL		0x000d
#define TCL_TRANSDEL		0x000d
#define T_TCL_RESERRORRATE	T_TCO_RESERRORRATE
#define TCL_RESERRORRATE	T_TCO_RESERRORRATE
#define T_TCL_PROTECTION	T_TCO_PROTECTION
#define TCL_PROTECTION		T_TCO_PROTECTION
#define T_TCL_PRIORITY		T_TCO_PRIORITY
#define TCL_PRIORITY		T_TCO_PRIORITY

#define T_TCO_LTPDU		0x0100
#define TCO_LTPDU		0x0100
#define T_TCO_ACKTIME		0x0200
#define TCO_ACKTIME		0x0200
#define T_TCO_REASTIME		0x0300
#define TCO_REASTIME		0x0300
#define T_TCO_EXTFORM		0x0400
#define TCO_EXTFORM		0x0400
#define T_TCO_FLOWCTRL		0x0500
#define TCO_FLOWCTRL		0x0500
#define T_TCO_CHECKSUM		0x0600
#define TCO_CHECKSUM		0x0600
#define T_TCO_NETEXP		0x0700
#define TCO_NETEXP		0x0700
#define T_TCO_NETRECPTCF	0x0800
#define TCO_NETRECPTCF		0x0800
#define T_TCO_PREFCLASS		0x0900
#define TCO_PREFCLASS		0x0900
#define T_TCO_ALTCLASS1		0x0a00
#define TCO_ALTCLASS1		0x0a00
#define T_TCO_ALTCLASS2		0x0b00
#define TCO_ALTCLASS2		0x0b00
#define T_TCO_ALTCLASS3		0x0c00
#define TCO_ALTCLASS3		0x0c00
#define T_TCO_ALTCLASS4		0x0d00
#define TCO_ALTCLASS4		0x0d00

#define T_TCL_CHECKSUM		T_TCO_CHECKSUM
#define TCL_CHECKSUM		T_TCO_CHECKSUM

/* INTERNET-SPECIFIC ENVIRONMENT */

/*
 * TCP level
 */

#define T_INET_TCP	0x6
#define INET_TCP	0x6

/*
 * TCP-level options
 */

#define T_TCP_NODELAY	0x01	/* don't delay packets to coalesce */
#define TCP_NODELAY	0x01
#define T_TCP_MAXSEG	0x02	/* get maximum segment size */
#define TCP_MAXSEG	0x02
#define T_TCP_KEEPALIVE	0x8	/* check, if connections are alive */
#define TCP_KEEPALIVE	0x8
#if	defined (_ALL_SOURCE)
#define	T_TCP_STDURG	0x10	/* RFC 1122-compliant urgent pointer handling */
#define	TCP_STDURG	0x10
#endif	/* _ALL_SOURCE */

/*
 * Structure used with TCP_KEEPALIVE option.
 */

#ifndef _T_KPALIVE
struct t_kpalive { 
	t_scalar_t	kp_onoff; 
	t_scalar_t	kp_timeout; 
};
#define _T_KPALIVE
#endif
#define T_GARBAGE	0x02

/*
 * UDP level
 */
#define T_INET_UDP	0x11
#define INET_UDP	0x11

/*
 * UDP-level options
 */
#define T_UDP_CHECKSUM	0x0600	/* checksum computation */
#define UDP_CHECKSUM	0x0600

/*
 * IP level
 */
#define T_INET_IP	0x0
#define INET_IP		0x0

/*
 * IP-level options
 */
#define T_IP_OPTIONS	1	/* IP per-packet options */
#define IP_OPTIONS	1
#define T_IP_TOS	3	/* IP per-packet type of service */
#define IP_TOS		3
#define T_IP_TTL	4	/* IP per-packet time to live */
#define IP_TTL		4
#define T_IP_REUSEADDR	0x8	/* allow local address reuse */
#define IP_REUSEADDR	0x8
#define T_IP_DONTROUTE	0x10	/* just use interface addresses */
#define IP_DONTROUTE	0x10
#define T_IP_BROADCAST	0x20	/* permit sending of broadcast msgs */
#define IP_BROADCAST	0x20
#if	defined (_ALL_SOURCE)
#define T_IP_REUSEPORT	0x40    /* allow local port reuse */
#define IP_REUSEPORT	0x40
#endif	/* _ALL_SOURCE */


/* IP_TOS Precedence Levels */
#define	T_ROUTINE	0
#define	T_PRIORITY	1
#define	T_IMMEDIATE	2
#define	T_FLASH		3
#define	T_OVERRIDEFLASH	4
#define	T_CRITIC_ECP	5
#define	T_INETCONTROL	6
#define	T_NETCONTROL	7

/* IP_TOS type of service */
#define T_NOTOS		0
#define T_LDELAY	(1<<4)
#define T_HITHRPT	(1<<3)
#define T_HIREL		(1<<2)
#define T_LOCOST	(1<<1)

#define SET_TOS(prec,tos)	((0x7 & (prec)) << 5 | (0x1c & (tos)))

#ifndef	_KERNEL
#if (defined(_THREAD_SAFE) && defined(_ALL_SOURCE)) || defined(_THREAD_SAFE_ERRNO)
#define t_errno (*_terrno())
#endif	/* _THREAD_SAFE || _THREAD_SAFE_ERRNO */
extern	int	t_errno;
extern	char *	t_errlist[];
extern	int	t_nerr;
#endif	/* KERNEL */

#if	defined(_NO_PROTO) && defined(_ALL_SOURCE)
extern	int	t_accept();
extern	char *	t_alloc();
extern	int	t_bind();
extern	int	t_blocking();
extern	int	t_close();
extern	int	t_connect();
extern	int	t_error();
extern	int	t_free();
extern	int	t_getprotaddr();
extern	int	t_getinfo();
extern	int	t_getstate();
extern	int	t_listen();
extern	int	t_look();
extern	int	t_nonblocking();
extern	int	t_open();
extern	int	t_optmgmt();
extern	int	t_rcv();
extern	int	t_rcvconnect();
extern	int	t_rcvdis();
extern	int	t_rcvrel();
extern	int	t_rcvreldata();
extern	int	t_rcvudata();
extern	int	t_rcvuderr();
extern	int	t_rcvv();
extern	int	t_rcvvudata();
extern	int	t_snd();
extern	int	t_snddis();
extern	int	t_sndrel();
extern	int	t_sndreldata();
extern	int	t_sndudata();
extern	int	t_sndv();
extern	int	t_sndvudata();
extern	char *	t_strerror();
extern	int	t_sync();
extern	int	t_sysconf();
extern	int	t_unbind();
#else
#if _XOPEN_SOURCE>=500
extern	int	t_accept(int, int, const struct t_call *);
extern	void *	t_alloc(int, int, int);
extern	int	t_bind(int, const struct t_bind *, struct t_bind *);
extern	int	t_connect(int, const struct t_call *, struct t_call *);
extern	int	t_error(const char *);
extern	int	t_free(void *, int);
extern	int	t_open(const char *, int, struct t_info *);
extern	int	t_optmgmt(int, const struct t_optmgmt *, struct t_optmgmt *);
extern	int	t_rcv(int, void *, unsigned, int *);
extern	int	t_snd(int, void *, unsigned, int);
extern	int	t_snddis(int, const struct t_call *);
extern	int	t_sndudata(int, const struct t_unitdata *);
extern	const char *t_strerror(int);
#else
extern	int	t_accept(int, int, struct t_call *);
extern	char *	t_alloc(int, int, int);
extern	int	t_bind(int, struct t_bind *, struct t_bind *);
extern	int	t_connect(int, struct t_call *, struct t_call *);
extern	int	t_error(char *);
extern	int	t_free(char *, int);
extern	int	t_open(char *, int, struct t_info *);
extern	int	t_optmgmt(int, struct t_optmgmt *, struct t_optmgmt *);
extern	int	t_rcv(int, char *, unsigned, int *);
extern	int	t_snd(int, char *, unsigned, int);
extern	int	t_snddis(int, struct t_call *);
extern	int	t_sndudata(int, struct t_unitdata *);
extern	char *  t_strerror(int);
#endif
extern	int	t_blocking(int);
extern	int	t_close(int);
extern	int	t_getprotaddr(int, struct t_bind *, struct t_bind *);
extern	int	t_getinfo(int, struct t_info *);
extern	int	t_getstate(int);
extern	int	t_listen(int, struct t_call *);
extern	int	t_look(int);
extern	int	t_nonblocking(int);
extern	int	t_rcvconnect(int, struct t_call *);
extern	int	t_rcvdis(int, struct t_discon *);
extern	int	t_rcvrel(int);
extern	int	t_rcvreldata(int, struct t_discon *);
extern	int	t_rcvudata(int, struct t_unitdata *, int *);
extern	int	t_rcvuderr(int, struct t_uderr *);
extern	int	t_rcvv(int, struct t_iovec *, unsigned int, int *);
extern	int	t_rcvvudata(int, struct t_unitdata *, struct t_iovec *, \
				unsigned int, int *);
extern	int	t_sndrel(int);
extern	int	t_sndreldata(int, struct t_discon *);
extern	int	t_sndv(int, struct t_iovec *, unsigned int, int);
extern	int	t_sndvudata(int, struct t_unitdata *, struct t_iovec *, \
				unsigned int);
extern	int	t_sync(int);
extern	int	t_synconf(int);
extern	int	t_unbind(int);
#endif	/* _NO_PROTO */
#endif	/* _XTI_H */
