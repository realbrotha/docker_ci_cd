/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/monetary.h 1.6                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)98	1.6  src/bos/usr/include/monetary.h, libcfmt, bos530 2/19/03 10:33:09 */

/*
 * COMPONENT_NAME: LIBCFMT
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 1994
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _H_MONETARY
#define _H_MONETARY

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef _XOPEN_SOURCE

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>

#ifdef _NO_PROTO
extern ssize_t strfmon();
#else
extern ssize_t strfmon(char *__restrict__, size_t, const char *__restrict__, ...);
#endif

#endif /* _XOPEN_SOURCE */

#ifdef _ALL_SOURCE

#ifndef _H_STDDEF
#include <stddef.h>
#endif

#endif /* _ALL_SOURCE */

#endif /* _H_MONETARY */
