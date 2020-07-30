/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/xcoff32_64.h 1.2                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)17	1.2  src/bos/usr/include/xcoff32_64.h, cmdld, bos530 2/16/97 17:14:02 */
/*
 *   COMPONENT_NAME: cmdld
 *
 *   ORIGINS: 27
 *
 */

#ifndef __XCOFF32_64_H
#define __XCOFF32_64_H

/*
  Define macros used in the XCOFF-related header files.

  Before including this file (or any XCOFF header file), define any subset
  of the following macros:
	__XCOFF32__ __XCOFF64__ __XCOFF_HYBRID__

  Users should not define any of the following macros:
	__XCOFF_32__ __XCOFF_64__ __XCOFF3264__ __XCOFF_32_64__
  These macros are conditionally defined by this header file.

  This table below lists the results of including this header file,
  based on the macros defined when the file is included.

  After including this file, exactly one of __XCOFF_32__, __XCOFF_64__,
  __XCOFF_32_64__, or __XCOFF_HYBRID__ will be defined.

 ==============================================================================
 | Macros Defined             | Comment       | Resulting Macros              |
 |============================================================================|
 | 1) none                    | XCOFF32 only  | __XCOFF_32__    __XCOFF32__   |
 | 2) __XCOFF32__             |               |                               |
 |----------------------------------------------------------------------------|
 | 3) __XCOFF64__             | XCOFF64 only  | __XCOFF_64__    __XCOFF64__   |
 |----------------------------------------------------------------------------|
 | 4) __XCOFF32__ __XCOFF64__ | Both XCOFF32  | __XCOFF_32_64__ __XCOFF32__   |
 |                            | and XCOFF64   |                 __XCOFF64__   |
 |                            | structures.   |                 __XCOFF3264__ |
 |----------------------------------------------------------------------------|
 | 5) __XCOFF_HYBRID__        | Hybrid        | __XCOFF_HYBRID__              |
 | 6) __XCOFF_HYBRID__        | structures for|                 __XCOFF32__   |
 |    __XCOFF32__             | both XCOFF32  |                 __XCOFF64__   |
 | 7) __XCOFF_HYBRID__        | and XCOFF64   |                 __XCOFF3264__ |
 |    __XCOFF64__             |               |                               |
 | 8) __XCOFF_HYBRID__        |               |                               |
 |    __XCOFF32__ __XCOFF64__ |               |                               |
 ==============================================================================

*/

#ifdef __cplusplus
extern "C" {
#endif

#undef __XCOFF_32__
#undef __XCOFF_64__
#undef __XCOFF3264__
#undef __XCOFF_32_64__

#if defined(__XCOFF_HYBRID__) || (defined(__XCOFF32__) && defined(__XCOFF64__))
#	ifndef __XCOFF32__
#	define __XCOFF32__
#	endif

#	ifndef __XCOFF64__
#	define __XCOFF64__
#	endif

#	define __XCOFF3264__
#	if ! defined(__XCOFF_HYBRID__)
#	define __XCOFF_32_64__
#	endif

#elif defined(__XCOFF64__)
#	define __XCOFF_64__

#else /* defined(__XCOFF32__) or no special macros */
#	ifndef __XCOFF32__
#	define __XCOFF32__
#	endif

#	define __XCOFF_32__

#endif

#ifndef _S_

#ifdef __XCOFF_32_64__
#define _S_(name) name ## _64
#else
#define _S_(name) name
#endif

#endif /* _S_ */

/* Define macros to maintain compatibility with earlier releases of AIX when
   specifying 4-byte integers in XCOFF header files.  The types _LONG32
   and _ULONG32 are 4-byte, fixed-width types. */

#ifdef __64BIT__
#define _LONG32 int
#define _ULONG32 unsigned int
#else
#define _LONG32 long
#define _ULONG32 unsigned long
#endif

#ifdef __cplusplus
}
#endif

#endif /* __XCOFF32_64_H */
