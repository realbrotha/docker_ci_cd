/*  DO NOT EDIT THIS FILE.

    It has been auto-edited by fixincludes from:

	"/opt/cross/aix/sysroot/usr/include/wchar.h"

    This had to be done to correct non-standard usages in the
    original, manufacturer supplied header file.  */

/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/usr/include/wchar.h 1.13.4.2                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)33       1.13.4.2  src/bos/usr/include/wchar.h, libcnls, bos53L, l2006_45A4 10/30/06 07:32:54 */
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

#ifndef _H_WCHAR
#define _H_WCHAR

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#include <strict_stdtypes.h>

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#include <end_strict_stdtypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_ISOC99_SOURCE) || defined(_XOPEN_SOURCE)

#ifndef _H_STDIO
#include <stdio.h>
#endif

#ifndef _H_TIME
#include <time.h>
#endif

#ifndef WEOF
#define WEOF    (-1)
#endif          /* WEOF */

#ifndef NULL
#define NULL    (0)
#endif

#if _XOPEN_SOURCE >= 500 || defined(_ISOC99_SOURCE)
typedef char *   mbstate_t;     /* conversion state holder ISO C MSE */
#ifndef _WCHAR_MAX
#define _WCHAR_MAX
#ifdef __64BIT__
#define WCHAR_MAX       (4294967295U)
#else
#define WCHAR_MAX       (65535)
#endif
#define WCHAR_MIN       (0)
#endif
#endif /* _XOPEN_SOURCE >= 500 || defined(_ISOC99_SOURCE) */

#endif /* defined(_ISOC99_SOURCE) || defined(_XOPEN_SOURCE) */

#ifdef _ISOC99_SOURCE

#ifndef _H_STDIO
#include <stdio.h> /* needed for FILE */
#endif

#ifndef _WINT_T
#define _WINT_T
typedef int	wint_t;
#endif

#ifdef _NO_PROTO
extern int	vfwscanf();
extern int	vswscanf();
extern int	vwscanf();
extern long double wcstold();
extern float wcstof();
#else
extern int	vfwscanf(FILE * __restrict__, const wchar_t * __restrict__, __gnuc_va_list);
extern int	vswscanf(const wchar_t * __restrict__, const wchar_t * __restrict__, __gnuc_va_list);
extern int	vwscanf(const wchar_t * __restrict__, __gnuc_va_list);
extern long double wcstold(const wchar_t * __restrict__, wchar_t ** __restrict__);
extern float wcstof(const wchar_t * __restrict__, wchar_t ** __restrict__);
#endif

/*
 * 64-bit integers, known as long long and unsigned long long
 */
#if defined(_LONG_LONG) 
#ifdef _NO_PROTO
 
extern long long int wcstoll( );
extern unsigned long long int wcstoull( );
 
#else /* ifdef _NO_PROTO */
 
extern long long int wcstoll(
     const wchar_t * __restrict__,              /* String to convert */
     wchar_t ** __restrict__,           /* Pointer to update */
     int );                     /* Base to use */
extern unsigned long long int wcstoull(
     const wchar_t * __restrict__,              /* String to convert */
     wchar_t ** __restrict__,           /* Pointer to update */
     int );                     /* Base to use */
 
#endif /* ifdef _NO_PROTO */
#endif /* if defined(_LONG_LONG) */

#endif /* _ISOC99_SOURCE */


#if defined(_XOPEN_SOURCE) || defined(_ISOC99_SOURCE)

#ifdef	_NO_PROTO

extern wint_t fgetwc();
extern wchar_t *fgetws();
extern wint_t fputwc();
extern int fputws();
extern wint_t getwc();
extern wint_t getwchar();

#if (!(defined(__H_CTYPE) && defined(_ILS_MACROS)))
extern int iswalnum();
extern int iswalpha();
extern int iswcntrl();
extern int iswdigit();
extern int iswgraph();
extern int iswlower();
extern int iswprint();
extern int iswpunct();
extern int iswspace();
extern int iswupper();
extern int iswxdigit();
extern int iswctype();
extern int towlower();
extern int towupper();
#endif /* (!(defined(__H_CTYPE) && defined(_ILS_MACROS))) */

extern wint_t putwc();
extern wint_t putwchar();
extern wint_t ungetwc();
extern wctype_t wctype();
extern wchar_t *wcscat();
extern wchar_t *wcschr();
extern int wcscmp();
extern int wcscoll();
extern wchar_t *wcscpy();
extern size_t wcscspn();
extern size_t wcsftime();
extern size_t wcslen();
extern wchar_t *wcsncat();
extern int wcsncmp();
extern wchar_t *wcsncpy();
extern wchar_t *wcspbrk();
extern wchar_t *wcsrchr();
extern size_t wcsspn();
extern double wcstod();
extern wchar_t *wcstok();
#if defined(_THREAD_SAFE) && defined(_ALL_SOURCE)
extern wchar_t *wcstok_r();
#endif /* _THREAD_SAFE */
extern long wcstol();
extern unsigned long wcstoul();
#ifdef _XOPEN_SOURCE
extern wchar_t *wcswcs();
extern int wcswidth();
extern int wcwidth();
#endif /* _XOPEN_SOURCE */
extern size_t wcsxfrm();

#else

extern wint_t fgetwc(FILE *);
extern wchar_t *fgetws(wchar_t * __restrict__, int, FILE * __restrict__);
extern int fputws(const wchar_t * __restrict__, FILE * __restrict__);
extern wint_t getwc(FILE *);
extern wint_t getwchar(void);

#if (!(defined(__H_CTYPE) && defined(_ILS_MACROS)))
extern int iswalnum(wint_t);
extern int iswalpha(wint_t);
extern int iswcntrl(wint_t);
extern int iswdigit(wint_t);
extern int iswgraph(wint_t);
extern int iswlower(wint_t);
extern int iswprint(wint_t);
extern int iswpunct(wint_t);
extern int iswspace(wint_t);
extern int iswupper(wint_t);
extern int iswxdigit(wint_t);
extern int iswctype (wint_t, wctype_t);
extern int towlower(wint_t);
extern int towupper(wint_t);
#endif /* (!(defined(__H_CTYPE) && defined(_ILS_MACROS))) */

#if (_XOPEN_SOURCE >= 500) || defined(_ISOC99_SOURCE)
extern wint_t fputwc(wchar_t, FILE *);
extern wint_t putwc(wchar_t, FILE *);
extern wint_t putwchar(wchar_t);
#else
extern wint_t fputwc(wint_t, FILE *);
extern wint_t putwc(wint_t, FILE *);
extern wint_t putwchar(wint_t);
#endif /* _XOPEN_SOURCE >= 500 || defined(_ISOC99_SOURCE) */
#ifdef __cplusplus98__interface__
extern const wchar_t *wcschr(const wchar_t *,  wchar_t);
extern wchar_t *wcschr(      wchar_t *,  wchar_t);
#else
extern wchar_t *wcschr(const wchar_t *,  wchar_t);
#endif
extern wint_t ungetwc(wint_t, FILE *);
extern wctype_t wctype(const char*);
extern wchar_t *wcscat(wchar_t * __restrict__, const wchar_t *__restrict__);
extern int wcscmp(const wchar_t *, const wchar_t *);
extern int wcscoll(const wchar_t *, const wchar_t *);
extern wchar_t *wcscpy(wchar_t * __restrict__, const wchar_t * __restrict__);
extern size_t wcscspn(const wchar_t *, const wchar_t *);
#if ((_XOPEN_SOURCE >= 500) || defined(_ISOC99_SOURCE)) && !defined(_UNIX95)
static size_t wcsftime(wchar_t *__wcsftime_wcs, size_t __wcsftime_maxsize,
	 const wchar_t *__wcsftime_format,
	 const struct tm *__wcsftime_timptr)
{
    extern size_t __iso_wcsftime(wchar_t *, size_t, const wchar_t *,
				 const struct tm *);
    return __iso_wcsftime(__wcsftime_wcs, __wcsftime_maxsize, __wcsftime_format,
			  __wcsftime_timptr);
}
#else /* _XOPEN_SOURCE */
extern size_t wcsftime(wchar_t * __restrict__, size_t, const char * __restrict__, const struct tm * __restrict__);
#endif /* _XOPEN_SOURCE */
#ifdef __cplusplus98__interface__
extern const wchar_t *wcspbrk(const wchar_t *, const wchar_t *);
extern wchar_t *wcspbrk(     wchar_t *,      wchar_t *);
extern const wchar_t *wcsrchr(const wchar_t *, wchar_t);
extern wchar_t *wcsrchr(      wchar_t *, wchar_t);
#else
extern wchar_t *wcspbrk(const wchar_t *, const wchar_t *);
extern wchar_t *wcsrchr(const wchar_t *, wchar_t);
#endif
extern size_t wcslen(const wchar_t *);
extern wchar_t *wcsncat(wchar_t * __restrict__, const wchar_t * __restrict__, size_t);
extern int wcsncmp(const wchar_t *, const wchar_t *, size_t);
extern wchar_t *wcsncpy(wchar_t * __restrict__, const wchar_t * __restrict__, size_t);
extern size_t wcsspn(const wchar_t *, const wchar_t *);
extern double wcstod(const wchar_t * __restrict__, wchar_t ** __restrict__);
#if ((_XOPEN_SOURCE >= 500) || defined(_ISOC99_SOURCE)) && !defined(_UNIX95)
static wchar_t *wcstok(wchar_t *__wcstok_ws1, const wchar_t *__wcstok_ws2,
		       wchar_t **__wcstok_ptr)
{
    extern wchar_t *__iso_wcstok(wchar_t *, const wchar_t *, wchar_t **);
    return __iso_wcstok(__wcstok_ws1, __wcstok_ws2, __wcstok_ptr);
}
#else /* _XOPEN_SOURCE */
extern wchar_t *wcstok(wchar_t * __restrict__, const wchar_t * __restrict__);
#endif /* _XOPEN_SOURCE */
#if defined(_THREAD_SAFE) && defined(_ALL_SOURCE)
extern wchar_t *wcstok_r(wchar_t *, const wchar_t *, wchar_t **);
#endif /* _THREAD_SAFE */
extern long wcstol(const wchar_t * __restrict__, wchar_t ** __restrict__, int);
extern unsigned long wcstoul(const wchar_t * __restrict__, wchar_t ** __restrict__, int);
#ifdef _XOPEN_SOURCE
extern wchar_t *wcswcs(const wchar_t *, const wchar_t *);
extern int wcswidth(const wchar_t *, size_t);
extern int wcwidth(wchar_t);
#endif /* _XOPEN_SOURCE */
extern size_t wcsxfrm(wchar_t * __restrict__, const wchar_t * __restrict__, size_t);

#if _XOPEN_SOURCE >= 500 || defined(_ISOC99_SOURCE)
extern wint_t btowc(int);
extern int fwprintf(FILE * __restrict__, const wchar_t * __restrict__, ...);
extern int fwscanf(FILE * __restrict__, const wchar_t * __restrict__, ...);
extern int fwide(FILE *, int);
extern int mbsinit(const mbstate_t *);
extern size_t mbrlen(const char * __restrict__, size_t, mbstate_t *__restrict__);
extern size_t mbrtowc(wchar_t * __restrict__, const char * __restrict__, size_t, mbstate_t * __restrict__);
extern size_t mbsrtowcs(wchar_t * __restrict__, const char ** __restrict__, size_t, mbstate_t * __restrict__);
extern int swprintf(wchar_t * __restrict__, size_t, const wchar_t * __restrict__, ...);
extern int swscanf(const wchar_t * __restrict__, const wchar_t * __restrict__, ...);
#ifdef _DUMMY_VA_LIST
extern int vfwprintf(FILE * __restrict__, const wchar_t * __restrict__, __gnuc_va_list);
extern int vwprintf(const wchar_t * __restrict__, __gnuc_va_list);
extern int vswprintf(wchar_t * __restrict__, size_t, const wchar_t * __restrict__, __gnuc_va_list);
#else
#define _HIDDEN_DUMMY_VA_LIST
#include <va_list.h>
extern int vfwprintf(FILE * __restrict__, const wchar_t * __restrict__, __gnuc_va_list);
extern int vwprintf(const wchar_t * __restrict__, __gnuc_va_list);
extern int vswprintf(wchar_t * __restrict__, size_t, const wchar_t * __restrict__, __gnuc_va_list);
#endif /* _DUMMY_VA_LIST */
#ifdef __cplusplus98__interface__
extern const wchar_t * wcsstr(const wchar_t *, const wchar_t *);
extern wchar_t *wcsstr(      wchar_t *,      wchar_t *);
extern const wchar_t * wmemchr(const wchar_t *, wchar_t, size_t);
extern wchar_t *wmemchr(      wchar_t *, wchar_t, size_t);
#else
extern wchar_t *wcsstr(const wchar_t *, const wchar_t *);
extern wchar_t *wmemchr(const wchar_t *, wchar_t, size_t);
#endif 
extern size_t wcrtomb(char * __restrict__, wchar_t, mbstate_t *  __restrict__);
extern size_t wcsrtombs(char * __restrict__, const wchar_t ** __restrict__, size_t, mbstate_t * __restrict__);
extern int wctob(wint_t);
extern wctype_t wctype(const char *);
extern int wmemcmp(const wchar_t *, const wchar_t *, size_t); 
extern wchar_t *wmemcpy(wchar_t * __restrict__, const wchar_t * __restrict__, size_t); 
extern wchar_t *wmemmove(wchar_t *, const wchar_t *, size_t); 
extern wchar_t *wmemset(wchar_t *, wchar_t, size_t); 
extern int wprintf(const wchar_t * __restrict__, ...);
extern int wscanf(const wchar_t * __restrict__, ...);
#endif

#endif	/* _NO_PROTO	*/

#endif	/* _XOPEN_SOURCE  || defined (ISOC99_SOURCE) */

#ifdef _ALL_SOURCE

#define getwchar()	getwc(stdin)

#ifdef	_NO_PROTO
extern wchar_t *getws();
extern int putws();
extern int wsprintf();
extern int vwsprintf();
extern int wcscasecmp();
extern wchar_t *wcsdup();
extern int wcsncasecmp();
extern size_t wcsnlen();
extern size_t wcsnrtombs();
extern size_t mbsnrtowcs();
extern wchar_t *wcpcpy();
extern wchar_t *wcpncpy();
#else
extern wchar_t *getws(wchar_t *);
extern int putws(const wchar_t *);
extern int wsprintf(wchar_t *, const char *, ...);
#ifdef _DUMMY_VA_LIST
extern int vwsprintf(wchar_t *, const char *, __gnuc_va_list);
#else
#define _HIDDEN_DUMMY_VA_LIST
#include <va_list.h>
extern int vwsprintf(wchar_t *, const char *, __gnuc_va_list);
#endif /* _DUMMY_VA_LIST */
extern int wcscasecmp(const wchar_t *, const wchar_t *);
extern wchar_t *wcsdup(const wchar_t *);
extern int wcsncasecmp(const wchar_t *, const wchar_t *, size_t);
extern size_t wcsnlen(const wchar_t *, size_t);
extern size_t wcsnrtombs(char *, const wchar_t **, size_t, size_t, mbstate_t *);
extern size_t mbsnrtowcs(wchar_t *, const char **, size_t, size_t, mbstate_t *);
extern wchar_t *wcpcpy(wchar_t *, const wchar_t *);
extern wchar_t *wcpncpy(wchar_t *, const wchar_t *, size_t);

#endif /* _NO_PROTO */

extern wchar_t *strtows(wchar_t *, char *);
extern char    *wstrtos(char *, wchar_t *);

#ifndef __ia64
#define wstrcat NCstrcat
#define wstrlen NCstrlen
#define wstrdup NCstrdup
#define wstrncat NCstrncat
#define wstrcmp NCstrcmp
#define wstrncmp NCstrncmp
#define wstrcpy NCstrcpy
#define wstrncpy NCstrncpy
#endif

#endif /* _ALL_SOURCE */

#ifdef __STDC_WANT_DEC_FP__     /* DFP scope requested */

#ifdef _NO_PROTO
	extern _Decimal32 wcstod32();
	extern _Decimal64 wcstod64();
	extern _Decimal128 wcstod128();
#else
	extern _Decimal32 wcstod32(const wchar_t *, wchar_t **);
	extern _Decimal64 wcstod64(const wchar_t *, wchar_t **);
	extern _Decimal128 wcstod128(const wchar_t *, wchar_t **);
#endif /* _NO_PROTO */

#endif /* __STDC_WANT_DEC_FP__ */

#ifdef __cplusplus
}
#endif

#endif /* _H_WCHAR */

