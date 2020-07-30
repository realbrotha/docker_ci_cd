/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/xti_inet.h 1.3                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,1999          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)81     1.3  src/bos/kernel/sys/xti_inet.h, sysxpse, bos530 5/11/99 12:24:29 */
/*
 *   COMPONENT_NAME: SYSXPSE
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1991,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/* INTERNET-SPECIFIC ENVIRONMENT */

#ifndef _XTI_INET_H
#define _XTI_INET_H

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

#endif /* _XTI_INET_H */
