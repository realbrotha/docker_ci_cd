/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/re_comp.h 1.2                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1991,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)47	1.2  src/bos/usr/include/re_comp.h, libcpat, bos530 8/20/97 17:14:29 */

/*
 * COMPONENT_NAME: (LIBCPAT) Standard C Library Regular Expression
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1991, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_RE_COMP
#define _H_RE_COMP

#ifndef _H_STANDARDS
#include <standards.h>
#endif /* _H_STANDARDS */



#if _XOPEN_SOURCE_EXTENDED==1

#ifdef _NO_PROTO
extern char	*re_comp();
extern int	re_exec();
#else /* _NO_PROTO */
extern char	*re_comp(const char *);
extern int	re_exec(const char *);
#endif /* _NO_PROTO */

#ifdef _THREAD_SAFE

#define	ESIZE	512
#define	NBRA	9

#ifndef _H_REGEX
typedef	struct regex_data {
	char	expbuf[ESIZE],
		*braslist[NBRA],
		*braelist[NBRA],
		circf;
} REGEXD;
#endif /* _H_REGEX */

#ifdef	_NO_PROTO
extern	char	*re_comp_r();
extern	int	re_exec_r();
#else /* _NO_PROTO */
extern	char	*re_comp_r(const char *sp, REGEXD *rd);
extern	int	re_exec_r(const char *p1, REGEXD *rd);
#endif	/* _NO_PROTO */

#endif /* _THREAD_SAFE */

#endif /* _XOPEN_SOURCE_EXTENDED */

#endif /* _H_RE_COMP */
