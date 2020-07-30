/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/libgen.h 1.2.1.3                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1995,2003          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)92       1.2.1.3  src/bos/usr/include/libgen.h, libPW, bos530 1/8/03 05:29:28 */

/*
 *   COMPONENT_NAME: LIBPW
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_LIBGEN
#define _H_LIBGEN

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if _XOPEN_SOURCE_EXTENDED==1

#if _XOPEN_SOURCE < 600 || defined(_ALL_SOURCE)
extern char * __loc1;
#ifdef _NO_PROTO
	extern char *regcmp();
	extern char *regex();
#else /* _NO_PROTO */
	extern char *regcmp(const char *, ...);
	extern char *regex(const char *, const char *, ...);
#endif /* _NO_PROTO */
#endif /* _XOPEN_SOURCE */

#ifdef _NO_PROTO
extern char *basename();
extern char *dirname();
#else /* _NO_PROTO */
extern char *basename(char *);
extern char *dirname(char *);
#endif /* _NO_PROTO */

#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef __cplusplus
}
#endif

#endif /* _H_LIBGEN */
