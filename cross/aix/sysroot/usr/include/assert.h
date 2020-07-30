/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/assert.h 1.16                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1992          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)34       1.16  src/bos/usr/include/assert.h, sysdb, bos530 1/10/03 15:00:21 */

/*
 * COMPONENT_NAME: (SYSDB) Kernel Debugger
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 */

/*
 *
 *      The ANSI standard requires that certain values be in assert.h.
 *      It also requires that if _ANSI_C_SOURCE is defined then ONLY these
 *      values are present.  This header includes all ANSI required entries.  
 *
 */

#undef assert
#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#ifdef _NO_PROTO
extern void __assert();
extern void __assert_c99();
#else
extern void __assert(const char *, const char *, int);
extern void __assert_c99(const char *, const char *, int, const char *);
#endif /* _NO_PROTO */

/*
 * Determine when the assert macro defined with C99 and SUSV3
 * can be exposed:
 *	- Only if __NO_ASSERT_C99 and _NOISOC99_SOURCE has not been defined
 *	- Only if this is a C99 capable compiler.
 *	- If ALL_SOURCE not defined and either _POSIX_C_SOURCE is not
 *	  defined or defined as at least as new as 2001
 */

#include <standards.h>

#if !defined(__NO_ASSERT_C99) && !defined(_NOISOC99_SOURCE)
#if __STDC_VERSION__ < 199901L && !defined(__C99__FUNC__)
#undef __ASSERT_C99   
#else
#if !defined(_ALL_SOURCE) && (!defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE >= 200112L)
#define __ASSERT_C99
#endif
#endif
#endif

#ifdef __ASSERT_C99

#if __STDC__ == 1
#define assert(__EX) ((__EX) ? ((void)0) : __assert_c99(# __EX, __FILE__, __LINE__, __func__))
#else
#define assert(__EX) ((__EX) ? ((void)0) : __assert_c99("__EX", __FILE__, __LINE__, __func__))
#endif /* __STDC__*/

#else    /*  else if __ASSERT_C99 not defined */

#if __STDC__ == 1
#define assert(__EX) ((__EX) ? ((void)0) : __assert(# __EX, __FILE__, __LINE__))
#else
#define assert(__EX) ((__EX) ? ((void)0) : __assert("__EX", __FILE__, __LINE__))
#endif /* __STDC__*/

#endif   /* __ASSERT_C99 */
#endif /* NDEBUG */
