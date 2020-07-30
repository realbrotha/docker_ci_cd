/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/net/nh.h 1.9                                     */
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
/* @(#)02	1.9  src/bos/kernel/net/nh.h, sysxinet, bos530 4/10/00 14:02:07 */
/*
 *   COMPONENT_NAME: SYSNET
 *
 *   FUNCTIONS: HTONL
 *		NTOHL
 *		htonl
 *		htons
 *		ntohl
 *		ntohs
 *		
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * Macros for number representation conversion.
 *
 */

#ifndef _NH_H_
#define _NH_H_

#include <sys/machine.h>

#if BYTE_ORDER == BIG_ENDIAN
#ifndef	ntohll
#define ntohll(x)       (x)
#endif
#ifndef	ntohl
#define ntohl(x)        (x)
#endif
#ifndef	ntohs
#define ntohs(x)        (x)
#endif
#ifndef	htonll
#define htonll(x)       (x)
#endif
#ifndef	htonl
#define htonl(x)        (x)
#endif
#ifndef	htons
#define htons(x)        (x)
#endif
#define NTOHLL(x)
#define NTOHL(x)
#define NTOHS(x)
#define HTONLL(x)
#define HTONL(x)
#define HTONS(x)
#endif

#if BYTE_ORDER == LITTLE_ENDIAN

#ifdef	_NO_PROTO

uint16_t ntohs(), htons();
uint32_t  ntohl(), htonl();
uint64_t  ntohll(), htonll();

#else	/* POSIX required prototypes */

uint16_t	ntohs(uint16_t);
uint16_t	htons(uint16_t);
uint32_t	ntohl(uint32_t);
uint32_t	htonl(uint32_t);
uint64_t	ntohll(uint64_t);
uint64_t	htonll(uint64_t);

#endif

#define HTONLL(x)	(x) = htonll((x));
#define HTONL(x)	(x) = htonl((x));
#define HTONS(x)	(x) = htons((x));
#define NTOHLL(x)	(x) = ntohll((x));
#define NTOHL(x)	(x) = ntohl((x));
#define NTOHS(x)	(x) = ntohs((x));

#endif

#endif /* _NH_H_ */
