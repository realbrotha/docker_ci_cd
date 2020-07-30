/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/usr/include/stdlib.h 1.31.10.2                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)89       1.31.10.2  src/bos/usr/include/stdlib.h, incstd, bos53L, l2006_45A4 10/30/06 07:32:55 */
/*
 * COMPONENT_NAME: (INCSTD) Standard Include Files
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27,71
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 2001
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */

#ifndef _H_STDLIB
#define _H_STDLIB

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The ANSI standard requires that certain values be in stdlib.h.
 * It also requires if _ANSI_C_SOURCE is defined then ONLY these
 * values are present. This header includes all the ANSI required entries.
 * In addition other entries for the XIX system are included.
 */
 
#ifdef _ANSI_C_SOURCE

/*
 * The following 3 definitions are included in <sys/types.h>.  They are
 * also included here to comply with ANSI standards.
 */

#ifndef NULL
#define	NULL	0
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned long	size_t;
#endif

#ifndef	_WCHAR_T
#define _WCHAR_T
#ifdef __64BIT__
typedef unsigned int	wchar_t;
#else
typedef unsigned short	wchar_t;
#endif
#endif

typedef struct div_t  {	        /* struct returned from div	*/
	int quot;               /* quotient                     */
	int rem;                /* remainder                    */
} div_t;

typedef struct ldiv_t  {	/* struct returned from ldiv	*/
	long int quot;          /* quotient                     */
	long int rem;           /* remainder                    */
} ldiv_t;

#define EXIT_FAILURE   (1)		/* exit function failure	*/
#define EXIT_SUCCESS	0		/* exit function success	*/

#define RAND_MAX	32767		/* max value returned by rand	*/

extern size_t __getmbcurmax (void);
extern int __getmaxdispwidth (void);

#define MB_CUR_MAX		(__getmbcurmax())
#define __max_disp_width	(__getmaxdispwidth())

#ifdef _NO_PROTO
        extern double   strtod();
        extern long int strtol();
        extern unsigned long int strtoul();
#else
        extern double   strtod(const char * __restrict__, char ** __restrict__);        extern long int strtol(const char * __restrict__, char ** __restrict__,
int);
        extern unsigned long int strtoul(const char * __restrict__, char ** __restrict__, int);
#endif

/*
 * C99 Functions
 */
#ifdef _ISOC99_SOURCE
#ifdef _NO_PROTO
	extern void		_Exit();
	extern float		strtof();
#else
	extern void     	_Exit(int);
	extern float    	strtof(const char * __restrict__, char ** __restrict__);
#endif

/*
 * Support for 64-bit integers, called long long int and unsigned long long int
 */
#if defined(_LONG_LONG) 
 
typedef struct lldiv_t {
     long long int quot; /* quotient  */
     long long int rem ; /* remainder */
} lldiv_t;
 
#ifdef _NO_PROTO
extern long long int    atoll(); 
extern long long int llabs( );
extern lldiv_t lldiv( );
extern long long int strtoll( );
extern unsigned long long int strtoull( );
 
#else /* ifdef _NO_PROTO */
extern long long int    atoll(const char *);  
extern long long int llabs( long long int );
extern lldiv_t lldiv( long long int, long long int ); /* First arg / second arg
*/
extern long long int strtoll(
     const char * __restrict__, /* String to convert */
     char ** __restrict__,      /* Pointer to update */
     int );                     /* Base to use */
extern unsigned long long int strtoull(
     const char * __restrict__, /* String to convert */
     char ** __restrict__,      /* Pointer to update */
     int );                     /* Base to use */
 
#endif /* ifdef _NO_PROTO */
#endif /* if defined(_LONG_LONG)  */

#ifndef _STRTOLD
#define _STRTOLD
#if defined(__LONGDOUBLE128) || defined(__LONGDOUBLE80)
extern long double strtold(const char * __restrict__, char ** __restrict__);
#else
static long double 
strtold(const char * __restrict__ __a, char ** __restrict__ __b) {
	return ((long double)strtod (__a, __b));
}
#endif
#endif

#endif /* _ISOC99_SOURCE */

/*
 * Functions that are methods
 */
#ifdef   _NO_PROTO
	extern int		mblen();
	extern size_t 	mbstowcs();
	extern int		mbtowc();
	extern size_t	wcstombs();
	extern int		wctomb();
#else /* _NO_PROTO */
	extern int	 	mblen(const char *, size_t);
	extern size_t 	mbstowcs(wchar_t * __restrict__, const char * __restrict__, size_t);
	extern int		mbtowc(wchar_t * __restrict__, const char * __restrict__, size_t);
	extern size_t	wcstombs(char * __restrict__, const wchar_t * __restrict__, size_t);
	extern int		wctomb(char *, const wchar_t);
#endif /* _NO_PROTO */

/*
 * Regular Functions no prototyping
 */
#ifdef _NO_PROTO
	extern double 	atof();
	extern int 	atoi();
	extern long int atol();
	extern int 	rand();
	extern void	srand();
	extern void 	*calloc();
	extern void	free();
	extern void	*malloc();
	extern void 	*realloc();
	extern void	abort();
	extern int	atexit();
	extern void	exit();
	extern char	*getenv();
	extern int 	system();
	extern void 	*bsearch(); 
	extern void 	qsort();
    
/*
 * Undefine conflicting definition in  macros.h 
 */
#ifdef _ALL_SOURCE
#ifdef abs
#undef abs
#endif
#endif /* _ALL_SOURCE */
	extern int 	abs();
	extern struct div_t	div();
	extern long int	labs();
	extern struct ldiv_t 	ldiv();

#ifndef _STRTOLD
#define _STRTOLD
#if defined(__LONGDOUBLE128) || defined(__LONGDOUBLE80)
	long double strtold();
#endif /* #ifdef __LONGDOUBLE128 || __LONGDOUBLE80 */
#endif

/*
 * Regular Functions with prototyping
 */
#else  /* _NO_PROTO */
/*
 * Any changes to the atof() prototype must also be made to the atof()
 * prototype in math.h.
 */
	extern double 	atof(const char *);
	extern int 	atoi(const char *);
	extern long int atol(const char *);
	extern int 	rand(void);
	extern void	srand(unsigned int);
	extern void 	*calloc(size_t, size_t);
	extern void	free(void *);
	extern void	*malloc(size_t);
	extern void 	*realloc(void *, size_t);
	extern void	abort(void);
	extern int	atexit(void (*)(void));
	extern void	exit(int);
	extern char	*getenv(const char *);
	extern int 	system(const char *);
	extern void 	*bsearch(const void *, const void *, size_t, size_t, int(*)(const void *,const void *));
	extern void 	qsort(void *, size_t, size_t, int(*)(const void *,const void *));

/********** 
 * Undefine conflicting definition in  macros.h 
 */
#ifdef _ALL_SOURCE
#ifdef abs
#undef abs
#endif
#endif /* _ALL_SOURCE */
	
	extern int 	abs(int);
	extern struct div_t	div(int, int);
	extern long int	labs(long int);
	extern struct ldiv_t 	ldiv(long int, long int);

#ifndef _STRTOLD
#define _STRTOLD
#if defined(__LONGDOUBLE128) || defined(__LONGDOUBLE80)
/*
 * strtold() is available only for the non-default 128-bit
 * long double mode.  For converting to default (64-bit)
 * long double type, use strtod().
 */
	long double strtold(const char * __restrict__, char ** __restrict__);
#endif /* #ifdef __LONGDOUBLE128 || __LONGDOUBLE80 */
#endif

#  endif /* _NO_PROTO */
#endif /* _ANSI_C_SOURCE */


#ifdef _POSIX_SOURCE

#if _POSIX_C_SOURCE >= 200112L
extern int posix_memalign(void **,size_t,size_t);
#endif /* _POSIX_C_SOURCE >= 200112L */

#endif



/*
 * functions required by XOPEN
 */
#ifdef _XOPEN_SOURCE

#ifndef _H_WAIT
#include <sys/wait.h>   /* WNOHANG, WUNTRACED, WEXITSTATUS(), etc. */
#endif

#if defined(_THREAD_SAFE) && defined(_ALL_SOURCE)
/*
 * The following structure is used by the different thread_safe
 * *rand48_r() functions and must be passed in as an argument.
 */
 typedef struct drand48_data {
        unsigned x[3];                  /* 48 bit integer value */
        unsigned a[3];                  /* mutiplier value */
        unsigned c;                     /* addend value */
        unsigned short lastx[3];        /* previous value of Xi */
        int init;                       /* initialize ? */
} DRAND48D;
#endif	/* _THREAD_SAFE  && _ALL_SOURCE */

#ifdef _NO_PROTO
	extern double 		drand48();
	extern double 		erand48();
	extern long 		jrand48();
	extern void 		lcong48();
	extern long 		lrand48();
	extern long 		mrand48();
	extern long 		nrand48();
	extern unsigned short 	*seed48();
	extern void 		setkey();
	extern void 		srand48();
	extern int 		putenv();

#if (_XOPEN_SOURCE>=500) || defined(_THREAD_SAFE)
/*
 * rand_r() was only visible under _XOPEN_SOURCE/_THREAD_SAFE
 * but now needs to be visible under _XOPEN_SOURCE>=500 or _THREAD_SAFE.
 */
	extern  int     rand_r();
#endif /* _XOPEN_SOURCE>=500 or _THREAD_SAFE */

#if defined(_THREAD_SAFE) && defined(_ALL_SOURCE)
	extern int	getopt_r();
	extern  int     drand48_r();
	extern  int     erand48_r();
	extern  int     lrand48_r();
	extern  int     mrand48_r();
	extern  int     srand48_r();
	extern  int     seed48_r();
	extern  int     lcong48_r();
	extern  int     nrand48_r();
	extern  int     jrand48_r();
        extern  int	ecvt_r();
        extern  int	fcvt_r();
#endif	/* _THREAD_SAFE */
#if _XOPEN_SOURCE_EXTENDED==1
	extern long a64l();
	extern char *ecvt();
	extern char *fcvt();
	extern char *gcvt();
	extern int  getsubopt();
	extern int  grantpt();
	extern char *initstate();
	extern char *l64a();
	extern char *mktemp();
	extern int  mkstemp();
#ifdef _LARGE_FILES
#define mkstemp mkstemp64
#endif
#ifdef _LARGE_FILE_API
	extern int  mkstemp64(char *);
#endif
	extern char *ptsname();
	extern long random();
	extern char *realpath();
	extern char *setstate();
	extern void srandom();
	extern int  unlockpt();
#if (_XOPEN_SOURCE < 600)
	/* These functions were removed in SUSv3 */
#define _UNIX03_REMOVED
	extern int  ttyslot();
	extern void *valloc();
#endif
#endif /* _XOPEN_SOURCE_EXTENDED */
#else
	extern double 		drand48(void);
	extern double 		erand48(unsigned short[]);
	extern long 		jrand48(unsigned short[]);
	extern void 		lcong48(unsigned short int *);
	extern long 		lrand48(void);
	extern long 		mrand48(void);
	extern long 		nrand48(unsigned short[]);
	extern unsigned short 	*seed48(unsigned short[]);
	extern void 		setkey(const char *);
	extern void 		srand48(long);
#if (_XOPEN_SOURCE >= 500)
	extern int 		putenv(char *);
#else  /* _XOPEN_SOURCE >= 500 */
	extern int 		putenv(const char *);
#endif /* _XOPEN_SOURCE >= 500 */

#if (_XOPEN_SOURCE>=500) || defined(_THREAD_SAFE)
/*
 * AIX 3.2 used the POSIX 1003.4a Draft 4 interfaces while post 3.2
 * release use the new Draft 7 interfaces.  There is a DCE compatibility
 * library that contains the interfaces that changed, and these are the
 * prototypes for those routines for backward compatibility.
 * Also, rand_r() was only visible under _XOPEN_SOURCE/_THREAD_SAFE
 * but now needs to be visible under _XOPEN_SOURCE>=500 or _THREAD_SAFE.
 */

#if _AIX32_THREADS
	extern	int	rand_r(unsigned int *, int *);
#else	/* POSIX 1003.4a Draft 7 prototype */
	extern	int	rand_r(unsigned int *);
#endif /* _AIX32_THREADS */
#endif /* _XOPEN_SOURCE>=500 or _THREAD_SAFE */

#if defined(_THREAD_SAFE) && defined(_ALL_SOURCE)
	extern int		getopt_r( int, char* const*, const char*, int *,
					  char **, int *, int , int *,
					  int *);
	extern  int     drand48_r(DRAND48D *, double *);
	extern  int     erand48_r(unsigned short [], DRAND48D *,
                          	  double *);
	extern  int     lrand48_r(DRAND48D *, long *);
	extern  int     mrand48_r(DRAND48D *, long *);
	extern  int     srand48_r(long, DRAND48D *);
	extern  int     seed48_r(unsigned short [], DRAND48D *);
	extern  int     lcong48_r(unsigned short [], DRAND48D *);
	extern  int     nrand48_r(unsigned short [], DRAND48D *, 
				  long *);
	extern  int     jrand48_r(unsigned short [], DRAND48D *,
				  long *);
        extern  int	ecvt_r(double, int, int *, int *, char *, int);
        extern  int	fcvt_r(double, int, int *, int *, char *, int);
#endif	/* _THREAD_SAFE */
#if _XOPEN_SOURCE_EXTENDED==1
	extern long a64l(const char *);
	extern char *ecvt(double, int, int *, int *);
	extern char *fcvt(double, int, int *, int *);
	extern char *gcvt(double, int, char *);
	extern int  getsubopt(char **, char *const *, char **);
	extern int  grantpt(int);
	extern char *initstate(unsigned, char *, size_t);
	extern char *l64a(long);
	extern char *mktemp(char *);
	extern int  mkstemp(char *);
#ifdef _LARGE_FILES
#define mkstemp mkstemp64
#endif
#ifdef _LARGE_FILE_API
	extern int  mkstemp64(char *);
#endif
	extern char *ptsname(int);
	extern long random(void);
	extern char *realpath(const char *, char *);
	extern char *setstate(const char *);
	extern void srandom(unsigned);
	extern int  unlockpt(int);
#if (_XOPEN_SOURCE < 600)
	/* These functions were removed in SUSv3 */
#define _UNIX03_REMOVED
	extern int  ttyslot(void);
	extern void *valloc(size_t);
#endif 
#endif /* _XOPEN_SOURCE_EXTENDED */
#endif /* _NO_PROTO */

#if (_XOPEN_SOURCE >= 600)
#ifdef _NO_PROTO
	extern int	posix_openpt();
	extern int	setenv();
	extern int	unsetenv();
#else
	extern int  	posix_openpt	(int);
	extern int      setenv		(const char *, const char *, int);
	extern int      unsetenv	(const char *);
#endif
#endif /* _XOPEN_SOURCE >= 600 */

#endif /* _XOPEN_SOURCE */


/*
 * The following macro definitions cause the XLC compiler to inline
 * these functions whenever possible.
 */
 
/*
 * Undefine conflicting definition in  macros.h 
 */

#ifdef _ALL_SOURCE
#ifdef abs
#undef abs
#endif
#endif /* _ALL_SOURCE */

#if (defined (__MATH__) &&  defined (_ANSI_C_SOURCE) )
#define abs(__j)          __abs(__j)
#define labs(__j)         __labs(__j)
#endif /* __MATH__  and _ANSI_C_SOURCE */

/*
 * Definition of functions and structures used by the thread-safe
 * random_r() functions.
 */
#if defined(_ALL_SOURCE) && defined(_THREAD_SAFE)
typedef struct random_data {
        int     *fptr;
        int     *rptr;
        int     *state;
        int     rand_type;
        int     rand_deg;
        int     rand_sep;
        int     *end_ptr;
} RANDOMD;

/* functions */

#ifdef _NO_PROTO
extern  int     srandom_r();
extern  int     initstate_r();
extern  int     setstate_r();
extern  long    random_r();
extern	int	l64a_r();
#else
extern  int     srandom_r(unsigned, RANDOMD *);
extern  int     initstate_r(unsigned, char *, size_t, char **,RANDOMD *);
extern  int     setstate_r(char *, char **,  RANDOMD *);
extern  int     random_r(long *, RANDOMD *);
extern	int	l64a_r(long, char*, int);
#endif /* _NO_PROTO */

#endif /* _ALL_SOURCE && _THREAD_SAFE */

/*
 * The following function prototypes are not defined for programs
 * that are adhering to strict ANSI conformance, but are included
 * for floating point support.
 */

#ifdef _ALL_SOURCE

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#ifndef __H_LOCALEDEF
#include <sys/localedef.h>
#endif

/*
 * Redefine MB_CUR_MAX and __max_disp_width to not call the functions
 */
#undef MB_CUR_MAX
#undef __max_disp_width

#ifdef _THREAD_SAFE
#define MB_CUR_MAX		(__OBJ_DATA(*__lc_charmap_ptr)->cm_mb_cur_max)
#define __max_disp_width	(__OBJ_DATA(*__lc_charmap_ptr)->cm_max_disp_width)
#define __XMB_CUR_MAX(__cmap)	(__OBJ_DATA(*__cmap)->cm_mb_cur_max)
#define __x__max_disp_width(__cmap)	(__OBJ_DATA(*__cmap)->cm_max_disp_width)
#else
#define MB_CUR_MAX              (__OBJ_DATA(__lc_charmap)->cm_mb_cur_max)
#define __max_disp_width        (__OBJ_DATA(__lc_charmap)->cm_max_disp_width)
#endif

extern char *optarg;
extern int optind;
extern int opterr;

/* The following functions are required by the COSE (UU) API. */

#define ATEXIT_MAX	2048	/* Max Number of functions that can be
				   registered in the atexit() functions.
				   ATEXIT_MAX IS ALSO DEFINED IN sys/limits.h */

#ifdef _NO_PROTO
	extern float    atoff();
	extern void     imul_dbl();
	extern void     umul_dbl();
	extern int	on_exit();
	extern int      unatexit();
#else /* use prototypes */
	extern float    atoff(char *);
	extern void     imul_dbl(long, long, long *);
	extern void     umul_dbl(unsigned long, unsigned long, unsigned long *);
	extern int	on_exit(void (*)(int, void *), void *);
	extern int      unatexit(void (*)(void));
#endif /* ifdef _NO_PROTO */

#if (defined (__MATH__) &&  defined (__XLC121__) && defined (_ALL_SOURCE) )
#define imul_dbl(__a, __b, __c)   __imul_dbl(__a, __b, __c)
#define umul_dbl(__a, __b, __c)   __umul_dbl(__a, __b, __c)
#endif

#ifdef _NO_PROTO
/*
 * functions that are methods
 */
	extern double			wcstod();
	extern long int			wcstol();
	extern unsigned long int 	wcstoul();

	extern int			rpmatch();
	extern int			clearenv();
	extern int			getopt();
	extern char			*getpass();
#ifndef _UNIX03_REMOVED
	extern int  			ttyslot();
	extern void			*valloc();
#endif
#else
	extern double	 		wcstod(const wchar_t *, wchar_t **);
	extern long int	 		wcstol(const wchar_t *, wchar_t **, int);
	extern unsigned long int 	wcstoul(const wchar_t *, wchar_t **, int);

	extern int			rpmatch(const char *);
	extern int			clearenv(void);
	extern int			getopt(int, char* const*, const char*);
	extern char			*getpass(const char *);
#ifndef _UNIX03_REMOVED
        extern int  			ttyslot(void);
        extern void 			*valloc(size_t);
#endif
#endif /* _NO_PROTO */

#endif /* _ALL_SOURCE */

/*
 * __XLC121__ is automatically defined by the XLC 1.2.1 compiler so that
 * the compiler can inline the following functions when possible.
 */

#if (defined (__MATH__) &&  defined (__XLC121__) && defined (_ANSI_C_SOURCE) )
#define div(__numer,__denom)        __div(__numer,__denom)
#define ldiv(__numer,__denom)       __ldiv(__numer,__denom)
#endif

#if defined(_ALL_SOURCE) && defined(_LINUX_SOURCE_COMPAT)
#ifdef	_NO_PROTO
extern void *__linux_malloc();
extern void *__linux_realloc();
extern void *__linux_calloc();
extern void *__linux_valloc();
#else
extern void *__linux_malloc(size_t);
extern void *__linux_realloc(void *, size_t);
extern void *__linux_calloc(size_t, size_t);
extern void *__linux_valloc(size_t);
#endif
#define malloc __linux_malloc
#define calloc __linux_calloc
#define realloc __linux_realloc
#define valloc __linux_valloc
#endif	/* _LINUX_SOURCE_COMPAT */

#ifdef _ALL_SOURCE
#ifdef	_NO_PROTO
extern void *vec_malloc();
extern void *vec_calloc();
#else
extern void *vec_malloc(size_t);
extern void *vec_calloc(size_t, size_t);
#endif
#define vec_realloc realloc
#define vec_free free
#if defined(__VEC__) || defined(__AIXVEC)
#if defined(__IBMC__) || defined(__IBMCPP__)
#pragma map(malloc,"vec_malloc")
#pragma map(calloc,"vec_calloc")
#else /* __IBMC__ || __IBMCPP__ */
#define malloc vec_malloc
#define calloc vec_calloc
#endif /* __IBMC__ || __IBMCPP__ */
#endif /* __VEC__ || __AIXVEC */
#endif	/* _ALL_SOURCE */

#ifdef __STDC_WANT_DEC_FP__     /* DFP scope requested */

#ifdef _NO_PROTO
	extern _Decimal32 strtod32();
	extern _Decimal64 strtod64();
	extern _Decimal128 strtod128();
#else
	extern _Decimal32 strtod32(const char *, char **);
	extern _Decimal64 strtod64(const char *, char **);
	extern _Decimal128 strtod128(const char *, char **);
#endif /* _NO_PROTO */

#endif /* __STDC_WANT_DEC_FP__ */

#ifdef __cplusplus
}
#endif

#endif /* _H_STDLIB */
