/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/strict_stdtypes.h 1.1                       */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2003               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)28	1.1  src/bos/usr/include/strict_stdtypes.h, incstd, bos530 2/19/03 10:23:14 */
/* 
 * Restrict content from standard headers to the allowable typedefs.
 * This affects sys/types.h, inttypes.h, and stdint.h and any headers 
 * which include those headers.
 *
 * This file should be used in conjunction with <end_strict_stdtypes.h>, which
 * terminates the restricted environment.
 *
 * This has no effect if _ALL_SOURCE is defined.
 */

#ifndef _H_STANDARDS
#include <standards.h>
#endif  

#ifndef _ALL_SOURCE
#ifdef  _STD_TYPES_T
#ifndef _NESTED_STD_TYPES_T
#define _NESTED_STD_TYPES_T
#endif  /* _NESTED_STD_TYPES_T */
#else   /* _STD_TYPES_T */
#define _STD_TYPES_T
#endif  /* _STD_TYPES_T */
#endif  /* _ALL_SOURCE */
