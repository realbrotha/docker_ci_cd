/* @(#)91       1.5  src/bos/usr/include/fmtmsg.h, libcfmt, bos530 7/25/02 19:29:59 */
/*
 *   COMPONENT_NAME: libcfmt
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27,85
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1990,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
#ifndef _H_FMTMSG
#define _H_FMTMSG

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#if _XOPEN_SOURCE_EXTENDED==1

/*
 *  Major Classifications
 */

#define MM_HARD		0x00000001
#define MM_SOFT		0x00000002
#define MM_FIRM		0x00000004
/*
 *  Message Source Sub-classifications
 */
#define MM_APPL		0x00000100
#define MM_UTIL 	0x00000200
#define MM_OPSYS	0x00000400
/*
 *  Display Sub-classifications
 */
#define MM_PRINT	0x00010000
#define MM_CONSOLE	0x00020000
/*
 *  Status sub-classifications
 */
#define MM_RECOVER	0x01000000
#define MM_NRECOV	0x02000000
/*
 *  Severity 
 */
#define MM_NOSEV	0
#define MM_HALT		1
#define MM_ERROR	2
#define MM_WARNING	3
#define MM_INFO		4

/*
 *  Exit Codes
 */
#define MM_OK		1
#define MM_NOTOK	2
#define MM_NOMSG	3
#define MM_NOCON	4
/*
 *  Null Values
 */
#define MM_NULLLBL	(char *)0	/* label */
#define MM_NULLSEV	(int)0 		/* severity */ 
#define MM_NULLMC	(long)0		/* classification */
#define MM_NULLTXT	(char *)0	/* text */
#define MM_NULLACT	(char *)0	/* action */
#define MM_NULLTAG	(char *)0	/* tag */


extern int fmtmsg( long, const char *, int, const char *, const char *, const char *);

#endif /* _XOPEN_SOURCE_EXTENDED */

#endif /* _H_FMTMSG */
