/* @(#)52       1.7  src/bos/usr/include/wctype.h, incstd, bos530, 0426A_530 6/18/04 15:48:32 */
/*
 * COMPONENT_NAME: (LIBCNLS) Standard C Library National Language Support
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1994
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_WCTYPE
#define _H_WCTYPE

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifndef _H_WCHAR
#include <wchar.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_ISOC99_SOURCE) || (_XOPEN_SOURCE >= 500)
typedef wint_t (*wctrans_t)(wint_t);
#endif

#ifdef _ISOC99_SOURCE 
#ifdef _NO_PROTO
	extern int iswblank();
#else
	extern int iswblank(wint_t);
#endif  /* _NO_PROTO */
#endif  /* _ISOC99_SOURCE */

#if _XOPEN_SOURCE >= 500 || defined(_ISOC99_SOURCE)

extern wint_t towctrans(wint_t, wctrans_t);
extern wctrans_t wctrans(const char *);

#endif	/* _XOPEN_SOURCE || defined(_ISOC99_SOURCE) */

#ifdef __cplusplus
}
#endif

#endif /* _H_WCTYPE */

