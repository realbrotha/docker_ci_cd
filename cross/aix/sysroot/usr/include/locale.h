/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/usr/include/locale.h 1.25.1.9                           */
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
/* @(#)82  1.25.1.9  src/bos/usr/include/locale.h, libcnls, bos53D, d2005_21A7 5/20/05 07:30:39 */

/*
 * COMPONENT_NAME: (LIBCNLS) Locale Related Data Structures and API
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

#ifndef __H_LOCALE
#define __H_LOCALE

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#undef NULL
#define NULL (0)
#endif

#ifdef _ANSI_C_SOURCE

#ifndef		NULL
#define		NULL	((void *)0)
#endif /* NULL */

struct lconv {
   char *decimal_point;		/* decimal point character		*/
   char *thousands_sep;		/* thousands separator		 	*/
   char *grouping;		/* digit grouping		 	*/
   char *int_curr_symbol;	/* international currency symbol	*/
   char *currency_symbol;	/* national currency symbol		*/
   char *mon_decimal_point;	/* currency decimal point		*/
   char *mon_thousands_sep;	/* currency thousands separator		*/
   char *mon_grouping;		/* currency digits grouping		*/
   char *positive_sign;		/* currency plus sign			*/
   char *negative_sign;		/* currency minus sign		 	*/
   char int_frac_digits;	/* internat currency fractional digits	*/
   char frac_digits;		/* currency fractional digits		*/
   char p_cs_precedes;		/* currency plus location		*/
   char p_sep_by_space;		/* currency plus space ind.		*/
   char n_cs_precedes;		/* currency minus location		*/
   char n_sep_by_space;		/* currency minus space ind.		*/
   char p_sign_posn;		/* currency plus position		*/
   char n_sign_posn;		/* currency minus position		*/

#ifdef _ALL_SOURCE
   char *left_parenthesis;	/* negative currency left paren         */
   char *right_parenthesis;	/* negative currency right paren        */
#else
   char *__left_parenthesis;	/* negative currency left paren         */
   char *__right_parenthesis;	/* negative currency right paren        */
#endif

#ifdef _ISOC99_SOURCE
   char int_p_cs_precedes;      /* int. currency plus location          */
   char int_p_sep_by_space;     /* int. currency plus space ind.        */
   char int_n_cs_precedes;      /* int. currency minus location         */
   char int_n_sep_by_space;     /* int. currency minus space ind.       */
   char int_p_sign_posn;        /* int. currency plus position          */
   char int_n_sign_posn;        /* int. currency minus position         */
#else
   char __int_p_cs_precedes;      /* int. currency plus location          */
   char __int_p_sep_by_space;     /* int. currency plus space ind.        */
   char __int_n_cs_precedes;      /* int. currency minus location         */
   char __int_n_sep_by_space;     /* int. currency minus space ind.       */
   char __int_p_sign_posn;        /* int. currency plus position          */
   char __int_n_sign_posn;        /* int. currency minus position         */
#endif
} ;

#define LC_ALL		-1	/* name of locale's category name 	*/
#define LC_COLLATE	0	/* locale's collation data		*/
#define LC_CTYPE	1	/* locale's ctype handline		*/
#define LC_MONETARY	2	/* locale's monetary handling		*/
#define LC_NUMERIC	3	/* locale's decimal handling		*/
#define LC_TIME		4	/* locale's time handling		*/
#define LC_MESSAGES	5	/* locale's messages handling		*/



#ifdef _NO_PROTO
struct lconv *localeconv();
char   *setlocale();
#else
struct lconv *localeconv(void);
char   *setlocale(int, const char *);
#endif

#endif /* _ANSI_C_SOURCE */

#ifdef _ALL_SOURCE
typedef struct lconv lconv;

#ifdef __MULTILOCALE_API
/* Support for multi-locale processes  */
#include <wchar.h> /* mbstate_t */
#include <langinfo.h>
typedef void*		__xlocale_ptr;

extern __xlocale_ptr	__xopen_locale(const char *);
extern void 		__xclose_locale(__xlocale_ptr);
extern int 		__xNCcollate(__xlocale_ptr,wchar_t);
extern int 		__xNCcoluniq(__xlocale_ptr,wchar_t);
extern int		__xNCcolval(__xlocale_ptr,wchar_t);
extern int 		__x_NLxcol(__xlocale_ptr,int,unsigned char**,wchar_t**);
extern int		__x_NCxcol(__xlocale_ptr,int,wchar_t**,wchar_t**);
extern int		__x_NLxcolu(__xlocale_ptr,int,unsigned char**,wchar_t**,wchar_t*);
extern int		__x_NCxcolu(__xlocale_ptr,int,wchar_t**,wchar_t**,wchar_t*);
extern int		__x__getmaxdispwidth(__xlocale_ptr);
extern size_t		__x__getmbcurmax(__xlocale_ptr);
extern int		__x__mbstopcs(__xlocale_ptr,wchar_t*,size_t,char*,size_t,int,char**,int*);
extern size_t		__x__mbtopc(__xlocale_ptr,wchar_t*,char*,size_t,int*);
extern int		__x__pcstombs(__xlocale_ptr,char*,size_t,char*,size_t,char**,int*);
extern int		__x__pctomb(__xlocale_ptr,char*,wchar_t*,int,int*);
extern int		__x_tolower(__xlocale_ptr,int);
extern int		__x_toupper(__xlocale_ptr,int);
extern int		__xcsid(__xlocale_ptr,char *);
extern int		__xfnmatch(__xlocale_ptr,const char *,const char*,int);
extern wctype_t		__xget_wctype(__xlocale_ptr,char*);
extern int		__xis_wctype(__xlocale_ptr,wint_t,wctype_t);
extern int		__xisalnum(__xlocale_ptr,int);
extern int		__xisalpha(__xlocale_ptr,int);
extern int		__xisblank(__xlocale_ptr,int);
extern int		__xiscntrl(__xlocale_ptr,int);
extern int		__xisdigit(__xlocale_ptr,int);
extern int		__xisgraph(__xlocale_ptr,int);
extern int		__xislower(__xlocale_ptr,int);
extern int		__xisprint(__xlocale_ptr,int);
extern int		__xispunct(__xlocale_ptr,int);
extern int		__xisspace(__xlocale_ptr,int);
extern int		__xisupper(__xlocale_ptr,int);
extern int		__xiswalnum(__xlocale_ptr,wint_t);
extern int		__xiswalpha(__xlocale_ptr,wint_t);
extern int		__xiswblank(__xlocale_ptr,wint_t);
extern int		__xiswcntrl(__xlocale_ptr,wint_t);
extern int		__xiswctype(__xlocale_ptr,wint_t,wctype_t);
extern int		__xiswdigit(__xlocale_ptr,wint_t);
extern int		__xiswgraph(__xlocale_ptr,wint_t);
extern int		__xiswlower(__xlocale_ptr,wint_t);
extern int		__xiswprint(__xlocale_ptr,wint_t);
extern int		__xiswpunct(__xlocale_ptr,wint_t);
extern int		__xiswspace(__xlocale_ptr,wint_t);
extern int		__xiswupper(__xlocale_ptr,wint_t);
extern int		__xiswxdigit(__xlocale_ptr,wint_t);
extern int		__xisxdigit(__xlocale_ptr,int);
extern struct lconv*	__xlocaleconv(__xlocale_ptr);
extern int		__xmblen(__xlocale_ptr,const char*,size_t);
extern size_t		__xmbrtowc(__xlocale_ptr,wchar_t*,const char*,size_t,mbstate_t*);
extern size_t		__xmbstowcs(__xlocale_ptr,wchar_t*,const char*,size_t);
extern int		__xmbtowc(__xlocale_ptr,wchar_t*,const char*,size_t);
extern char*		__xnl_langinfo(__xlocale_ptr,nl_item);
extern int		__xrpmatch(__xlocale_ptr,const char*);
extern int		__xstrcoll(__xlocale_ptr,const char*,const char*);
extern ssize_t		__xstrfmon(__xlocale_ptr,char*,size_t,const char*,...);
extern size_t		__xstrftime(__xlocale_ptr,char*,size_t,const char*,const struct tm*);
extern int		__xstrncollen(__xlocale_ptr,const char*,const int);
extern char *		__xstrptime(__xlocale_ptr,const char*,const char*, struct tm*);
extern size_t		__xstrxfrm(__xlocale_ptr,char *, const char*, size_t);
extern int		__xtolower(__xlocale_ptr,int);
extern int		__xtoupper(__xlocale_ptr,int);
extern wint_t		__xtowlower(__xlocale_ptr,wint_t);
extern wint_t		__xtowupper(__xlocale_ptr,wint_t);
extern size_t		__xwcrtomb(__xlocale_ptr,char*,wchar_t,mbstate_t*);
extern int		__xwcscoll(__xlocale_ptr,const wchar_t*,const wchar_t*);
extern size_t		__xwcsftime(__xlocale_ptr,wchar_t*,size_t,const char*,const struct tm*);
extern size_t		__x__isowcsftime(__xlocale_ptr,wchar_t*,size_t,const wchar_t*,const struct tm*);
extern int		__xwcsid(__xlocale_ptr,wchar_t);
extern size_t		__xwcstombs(__xlocale_ptr,char*,const wchar_t*,size_t);
extern int		__xwcswidth(__xlocale_ptr,wchar_t*,size_t);
extern size_t		__xwcsxfrm(__xlocale_ptr,wchar_t*,const wchar_t*,size_t);
extern int		__xwctomb(__xlocale_ptr,char*,wchar_t);
extern wctype_t		__xwctype(__xlocale_ptr,char*);
extern int		__xwcwidth(__xlocale_ptr,wchar_t);
#endif /* __MULTILOCALE_API */

#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif

#endif	/* __H_LOCALE */
