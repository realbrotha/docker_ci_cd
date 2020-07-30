/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53E src/bos/usr/include/stdbool.h 1.4                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2002,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)40     1.4  src/bos/usr/include/stdbool.h, incstd, bos53E, e2005_26C7 6/28/05 13:03:12 */
/*
 * COMPONENT_NAME: (INCSTD) Standard Include Files
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 */

#ifndef _H_STDBOOL
#define _H_STDBOOL

#include <standards.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ANSI_C_SOURCE

#ifndef __cplusplus
#ifndef _BOOL
#define _BOOL
#define bool 	_Bool
#endif
#endif

#ifndef _TRUE
#define _TRUE
#define true	1
#endif
#ifndef _FALSE
#define _FALSE
#define false	0
#endif

#define __bool_true_false_are_defined	1

#endif /* _ANSI_C_SOURCE */

#ifdef __cplusplus
}
#endif
#endif /* _H_STDBOOL */
