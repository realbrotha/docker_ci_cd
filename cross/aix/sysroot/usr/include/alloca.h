/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/alloca.h 1.1                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2001               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)78  1.1  src/bos/usr/include/alloca.h, incsys, bos530 3/6/01 08:38:39 */

#ifndef _H_ALLOCA
#define _H_ALLOCA
#include <sys/types.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifdef  __GNUC__
/* Remove any previous definitions.  */
#undef  alloca

#define alloca(size)   __builtin_alloca (size)

#else /* xlc */

#pragma alloca

#endif /* GCC.  */

#ifdef __cplusplus
}
#endif

#endif /* _H_ALLOCA */
