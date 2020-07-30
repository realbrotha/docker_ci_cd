/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53N src/bos/usr/include/standards.h 1.10.2.4                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1995,2007              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)44  1.10.2.4  src/bos/usr/include/standards.h, incstd, bos53N, n2007_38A8 9/13/07 12:37:30 */
/*
 * COMPONENT_NAME: (INCSTD) Standard Include Files
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1995,2006
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _H_STANDARDS
#define _H_STANDARDS

#define _AIXVERSION_430  1
#define _AIXVERSION_431  1
#define _AIXVERSION_434  1
#define _AIXVERSION_510  1
#define _AIXVERSION_520  1
#define _AIXVERSION_530  1

/* These directives must be processed in the current order when compiled with 
 * cc or they will not work correctly.
 */

/* If _XOPEN_SOURCE is defined without a value, or with a value less
 * than 500 (UNIX98), then set a value, so that #if statements will 
 * work properly.
 */
#ifdef _XOPEN_SOURCE
#if ((_XOPEN_SOURCE + 0) < 500)
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE	1
#endif
#endif

#if defined(_UNIX03) || (_XOPEN_SOURCE==600)
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE   600
#undef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED     1
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#undef _THREAD_SAFE
#define _THREAD_SAFE
#endif

#if defined(_UNIX98) || (_XOPEN_SOURCE==500)
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE   500
#undef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED     1
#endif

#ifdef _UNIX95
#undef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED     1
#endif

#if (_XOPEN_SOURCE_EXTENDED==1)
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE	1
#endif /* _XOPEN_SOURCE */
#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _XOPEN_SOURCE
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif
#endif

#ifdef _POSIX_SOURCE
#ifndef _ANSI_SOURCE
#define _ANSI_SOURCE
#endif
#endif

#ifdef _ANSI_SOURCE
#ifndef _ANSI_C_SOURCE
#define _ANSI_C_SOURCE
#endif
#endif

#ifdef _ALL_SOURCE
#undef _XOPEN_SOURCE
#define _XOPEN_SOURCE	600
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif
#ifndef _ANSI_SOURCE
#define _ANSI_SOURCE
#endif
#ifndef _ANSI_C_SOURCE
#define _ANSI_C_SOURCE
#endif
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#endif
#ifdef _LONG_LONG
#ifndef _LARGE_FILE_API
#define _LARGE_FILE_API
#endif
#endif
#ifdef __STDC_DEC_FP__
#ifndef __STDC_WANT_DEC_FP__
#define __STDC_WANT_DEC_FP__
#endif
#endif
#endif

#if (defined(__IBMC__) || defined(__IBMCPP__))
#if ((defined(__STDC_WANT_DEC_FP__)) && !(defined(__IBM_DFP__)))
#if defined(__IBM_PP_WARNING)
#warning  The -qdfp option is required to process DFP code in headers.
#else
#error  The -qdfp option is required to process DFP code in headers.
#endif
#endif
#endif

#if (!defined (_XOPEN_SOURCE)) &&  (!defined (_POSIX_SOURCE)) && (!defined (_ANSI_C_SOURCE))
#define _XOPEN_SOURCE  600
#define _XOPEN_SOURCE_EXTENDED 1
#define _POSIX_SOURCE
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif
#define _ANSI_SOURCE
#ifndef _ANSI_C_SOURCE
#define _ANSI_C_SOURCE
#endif
#ifdef _LONG_LONG
#ifndef _LARGE_FILE_API
#define _LARGE_FILE_API
#endif
#endif
#ifndef _ALL_SOURCE
#define _ALL_SOURCE
#endif
#endif

#ifdef _POSIX_SOURCE
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199506L
#endif 
#endif

/* 
 * Handle the use of the restrict keyword in non-C99 compilers
 */
#if ((__STDC_VERSION__ >= 199901L) || defined(__C99_RESTRICT))
#define __restrict__ restrict
#else
#define __restrict__ 
#endif

/* 
 * Determine when C99 interfaces and definitions are allowed to be exposed
 *  - if _POSIX_C_SOURCE is newer than 1995 
 *  - if a C99 compiler is being used outside of the UNIX98 namespace
 */
#if !(defined _ISOC99_SOURCE) && !(defined _NOISOC99_SOURCE)
#if (_POSIX_C_SOURCE > 199506L) || \
    ((__STDC_VERSION__ >= 199901L) && \
     ((!defined _XOPEN_SOURCE) || (_XOPEN_SOURCE > 500)))
#define _ISOC99_SOURCE
#endif 
#endif

/*
 * Determine what type should be used for the boolean type.
 * In C++ the type bool should be used.  If C99 is supported
 * then use _Bool.  Otherwise use unsigned char.
 */
#ifdef __cplusplus
#define __bool__ bool
#elif (__STDC_VERSION__ >= 199901L)
#define __bool__ _Bool
#else
#define __bool__ unsigned char
#endif 


#endif /* _H_STANDARDS */
