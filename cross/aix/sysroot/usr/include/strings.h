/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/strings.h 1.5.1.3                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)28  1.5.1.3  src/bos/usr/include/strings.h, libcstr, bos530 10/9/02 14:21:37 */
/*
 * COMPONENT_NAME: (LIBCSTR) Standard C Library String Handling Functions
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_STRINGS
#define _H_STRINGS

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#if _XOPEN_SOURCE_EXTENDED==1

#ifdef _NO_PROTO

extern int bcmp();
extern void bcopy();
extern void bzero();
extern int  ffs();
#ifndef _INDEX_MACROS
extern char *index();
extern char *rindex();
#endif
#ifndef _STRCASECMP_DEF
#define _STRCASECMP_DEF
extern int  strcasecmp();
extern int  strncasecmp();
#endif /* _STRCASECMP_DEF */

#else /* _NO_PROTO */

extern int bcmp(const void *, const void *, size_t);
extern void bcopy(const void *, void *, size_t);
extern void bzero(void *, size_t);
extern int  ffs(int);
#ifndef _INDEX_MACROS
extern char *index(const char *, int);
extern char *rindex(const char *, int);
#endif
#ifndef _STRCASECMP_DEF
#define _STRCASECMP_DEF
extern int  strcasecmp(const char *, const char *);
extern int  strncasecmp(const char *, const char *, size_t);
#endif /* _STRCASECMP_DEF */

#endif /* _NO_PROTO */

#if defined(__STR__) && !defined(__STR31__) && !defined(__cplusplus)
#define _INDEX_MACROS
#define index(__s1,__c) __strchr(__s1,__c)
#define rindex(__s1,__c) __strrchr(__s1,__c)
#endif

#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _ALL_SOURCE
#include <string.h>
#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* _H_STRINGS */
