/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/POWER/varargs.h 1.10.1.1                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1992          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)90  1.10.1.1  src/bos/usr/include/POWER/varargs.h, libcgen, bos530 2/12/97 13:24:48 */

/*
 * COMPONENT_NAME: (LIBCGEN) Standard C Library General Functions
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1992
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_VARARGS
#define _H_VARARGS

#ifdef __cplusplus
extern "C" {
#endif

#include <va_list.h>	/* va_list */

#define va_dcl long va_alist;

#define va_start(__list) __list = (char *) &va_alist
#define va_end(__list)
#define va_arg(__list, __mode) ((__mode *)(__list += sizeof(long) > sizeof(__mode) ? sizeof(long) : sizeof(__mode)))[-1]

#ifdef __cplusplus
}
#endif
#endif /* _H_VARARGS */
