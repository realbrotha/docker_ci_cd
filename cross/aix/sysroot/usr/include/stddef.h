/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/stddef.h 1.12.1.5                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)66  1.12.1.5  src/bos/usr/include/stddef.h, incstd, bos530 7/25/02 19:23:59 */

/*
 * COMPONENT_NAME: (INCSTD) Standard Include Files
 *
 * ORIGINS: 27
 *
 */

#ifndef _H_STDDEF 
#define _H_STDDEF 

#ifndef _H_STANDARDS
#include <standards.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif


/*
 *
 *      The ANSI standard requires that certain values be in stddef.h.
 *      It also requires that if _ANSI_C_SOURCE is defined then ONLY these
 *      values are present. This header includes all the ANSI required entries.
 *
 */

#ifdef _ANSI_C_SOURCE

/*
 *	The following definitions are included in <sys/types.h>.  They
 *	are included in <stddef.h> to comply with ANSI.
 */

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
typedef	long		ptrdiff_t;
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef	unsigned long	size_t;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
#ifdef __64BIT__
typedef unsigned int	wchar_t;
#else
typedef unsigned short	wchar_t;
#endif
#endif

#ifndef NULL
#define	NULL	0
#endif

#ifndef offsetof
#ifdef __IBMCPP__
#define offsetof __offsetof
#else
#define offsetof(__s_name, __s_member) (size_t)&(((__s_name *)0)->__s_member)
#endif
#endif

#endif /* _ANSI_C_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* _H_STDDEF */
