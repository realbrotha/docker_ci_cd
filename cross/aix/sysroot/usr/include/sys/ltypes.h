/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/ltypes.h 1.12                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1999          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)71	1.12  src/bos/kernel/sys/ltypes.h, incstd, bos530 2/11/99 16:03:47  */
#ifndef _H_LTYPES
#define _H_LTYPES
/*
 * COMPONENT_NAME: (INCSTD) Standard Include Files
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/* ltypes.h	5.2 87/01/09 18:23:51 */
/*
 * quick set of typedefs -- this version is for the R2 platform
 */
#include <sys/machine.h>


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

#if BYTE_ORDER == BIG_ENDIAN
#define hipart(X) (((uint32 *)&(X))[0])
#define lopart(X) (((uint32 *)&(X))[1])
#else
#define hipart(X) (((uint32 *)&(X))[1])
#define lopart(X) (((uint32 *)&(X))[0])
#endif /* BYTE_ORDER == BIG_ENDIAN */

#ifndef StoQDNaN
#define StoQDNaN(X)	hipart((X)) |= BIT19
#endif  /* StoQDNaN */

#ifndef StoQFNaN
#define StoQFNaN(X)	hipart((X)) |= BIT22
#endif  /* StoQFNaN */

#ifndef _QNaN
#define _QNaN
#if BYTE_ORDER == BIG_ENDIAN
static uint32 FQNaN[] = {0x7fc00000};
static uint32 DQNaN[] = {0x7ff80000, 0x00000000};
#else
static uint32 FQNaN[] = {0x7fc00000};
static uint32 DQNaN[] = {0x00000000,0x7ff80000};
#endif /* BYTE_ORDER == BIG_ENDIAN */
#define _QNaN
#endif  /* _QNaN */

#define NORETBIT        0x08

#define _DOUBLE(x) (*(DOUBLE *)&(x))

#ifndef MIN
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif	/* MIN */
#ifndef MAX
#define MAX(X, Y) ((X) < (Y) ? (Y) : (X))
#endif	/* MAX */

#endif  /* _H_LTYPES */
