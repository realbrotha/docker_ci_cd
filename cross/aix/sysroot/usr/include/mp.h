/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/usr/include/mp.h 1.5                                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1993              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)67	1.5  src/bos/usr/include/mp.h, libbsd, bos53X, x2009_24A6 5/21/09 06:11:54 */
/*
 * COMPONENT_NAME: (LIBBSD) System header files
 *
 * FUNCTIONS:
 *                                                                    
 * ORIGINS: 26, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988,1993
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */                                                                   

/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */
#ifndef _H_MP
#define _H_MP

#ifdef _BSD_PROTO
#include <stdio.h>
#endif

#define MINT struct mint
MINT
{	int len;
	short *val;
};

#define FREE(x) {if(x.len!=0) {free((void *)x.val); x.len=0;}}
#define shfree(u) free((void *)u)

struct half
{	short high;
	short low;
};

#ifdef _NO_PROTO
extern MINT *itom();
extern short *xalloc();

#ifdef _BSD_PROTO
extern madd();
extern msub();
extern mult();
extern mdiv();
extern pow();
extern gcd();
extern invert();
extern rpow();
extern msqrt();
extern mcmp();
extern move();
extern min();
extern omin();
extern fmin();
extern m_in();
extern mout();
extern omout();
extern fmout();
extern m_out();
extern sdiv();
#endif		/* _BSD_PROTO */

#else
extern MINT *itom(int);
extern short *xalloc(int, char*);

#ifdef _BSD_PROTO
extern madd(MINT*, MINT*, MINT*);
extern msub(MINT*, MINT*, MINT*);
extern mult(MINT*, MINT*, MINT*);
extern mdiv(MINT*, MINT*, MINT*,MINT*);
extern pow(MINT*, MINT*, MINT*,MINT*);
extern gcd(MINT*, MINT*, MINT*);
extern invert(MINT*, MINT*, MINT*);
extern rpow(MINT*, int, MINT*);
extern msqrt(MINT*, MINT*, MINT*);
extern mcmp(MINT*, MINT*);
extern move(MINT*, MINT*);
extern min(MINT*);
extern omin(MINT*);
extern fmin(MINT*, FILE*);
extern m_in(MINT*, int, FILE*);
extern mout(MINT*);
extern omout(MINT*);
extern fmout(MINT*, FILE*);
extern m_out(MINT*, int, FILE*);
extern sdiv(MINT*, short, MINT*, short*);
#endif 		/* _BSD_PROTO */

#endif

#ifdef lint
extern xv_oid;
#define VOID xv_oid =
#else
#define VOID
#endif
#endif
