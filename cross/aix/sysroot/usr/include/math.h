/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/usr/include/math.h 1.28.9.7                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* "@(#)30  1.28.9.7  src/bos/usr/include/math.h, libm, bos53Q, q2008_03B5 1/7/08 08:01:12" */

/*
 * COMPONENT_NAME: (LIBM) math header file
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 2006
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_MATH
#define _H_MATH

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 *      The ANSI standard requires that certain values be in math.h.
 *      It also requires that if _ANSI_C_SOURCE is defined then ONLY these
 *      values are present.
 *
 *      This header includes all the ANSI required entries. In addition
 *      other entries for the AIX system are included.
 *
 */

/*
 *      ANSI required entries in math.h
 *
 */
#ifdef _ANSI_C_SOURCE

extern  unsigned _DBLINF[2];
static  const unsigned int _SINFINITY = 0x7f800000;
static  const unsigned int _SQNAN = 0x7fc00000;

#define HUGE_VAL (*((double *)(_DBLINF)))

#ifdef _ISOC99_SOURCE
/* The types float_t and double_t are intended to be the implementation's
 * most efficient types at least as wide as float and double, respectively.
 * That's double for POWER.
 */
typedef double float_t;
typedef double double_t;

#define INFINITY  (*((float *)(&_SINFINITY)))
#define NAN       (*((float *)(&_SQNAN)))
#define HUGE_VALF INFINITY
#define HUGE_VALL HUGE_VAL

#ifndef _H_FLOAT
#define FP_PLUS_NORM      0
#define FP_MINUS_NORM     1
#define FP_PLUS_ZERO      2
#define FP_MINUS_ZERO     3
#define FP_PLUS_INF       4
#define FP_MINUS_INF      5
#define FP_PLUS_DENORM    6
#define FP_MINUS_DENORM   7
#define FP_SNAN           8
#define FP_QNAN           9
#endif

#define FP_INFINITE	  FP_PLUS_INF
#define FP_NAN		  FP_QNAN
#define FP_NORMAL	  FP_PLUS_NORM
#define FP_SUBNORMAL	  FP_PLUS_DENORM
#define FP_ZERO		  FP_PLUS_ZERO

#define FP_ILOGB0	  (-2147483647 - 1)     /* INT_MIN */
#define FP_ILOGBNAN	  (2147483647)          /* INT_MAX */

#define MATH_ERRNO	  1
#define MATH_ERREXCEPT	  2
#define math_errhandling  MATH_ERRNO

#endif

#ifdef _NO_PROTO

extern  double acos();
extern  double asin();
extern  double atan();
extern  double atan2();
extern  double ceil();
extern  double copysign();
extern  double cos();
extern  double cosh();
extern  double exp();
extern  double fabs();
extern  double floor();
extern  double fmod();
extern  double frexp();
extern  double ldexp();
extern  double log();
extern  double log10();
extern  double modf();
extern  double pow();
extern  double sin();
extern  double sinh();
extern  double sqrt();
extern  double tan();
extern  double tanh();
extern  double trunc();

/* Symbols new in C99 */
#ifdef _ISOC99_SOURCE
extern float        acosf();
extern float        acoshf();
extern long double  acoshl();
extern float        asinf();
extern float        asinhf();
extern long double  asinhl();
extern float        atan2f();
extern long double  atan2l();
extern float        atanf();
extern float        atanhf();
extern long double  atanhl();
extern float        cbrtf();
extern long double  cbrtl();
extern float        ceilf();
extern float        copysignf();
extern long double  copysignl();
extern float        cosf();
extern float        coshf();
extern float        erfcf();
extern float        erff();
extern double       exp2();
extern float        exp2f();
extern long double  exp2l();
extern float        expf();
extern float        expm1f();
extern long double  expm1l();
extern float        fabsf();
extern double       fdim();
extern float        fdimf();
extern long double  fdiml();
extern float        floorf();
extern double       fma();
extern float        fmaf();
extern long double  fmal();
extern double       fmax();
extern float        fmaxf();
extern long double  fmaxl();
extern double       fmin();
extern float        fminf();
extern long double  fminl();
extern float        fmodf();
extern float        frexpf();
extern float        hypotf();
extern long double  hypotl();
extern int          ilogbf();
extern int          ilogbl();
extern float        ldexpf();
extern float        lgammaf();
#ifdef _LONG_LONG
extern long long int llrint();
extern long long int llrintf();
extern long long int llrintl();
extern long long int llround();
extern long long int llroundf();
extern long long int llroundl();
#endif
extern float        log10f();
extern long double  log10l();
extern float        log1pf();
extern long double  log1pl();
extern float        log2f();
extern double       log2();
extern long double  log2l();
extern float        logbf();
extern long double  logbl();
extern float        logf();
extern long int     lrint();
extern long int     lrintf();
extern long int     lrintl();
extern long int     lround();
extern long int     lroundf();
extern long int     lroundl();
extern float        modff();
extern double       nan();
extern float        nanf();
extern long double  nanl();
extern double       nearbyint();
extern float        nearbyintf();
extern long double  nearbyintl();
extern float        nextafterf();
extern long double  nextafterl();
extern double       nexttoward();
extern float        nexttowardf();
extern long double  nexttowardl();
extern float        powf();
extern float        remainderf();
extern long double  remainderl();
extern double       remquo();
extern float        remquof();
extern long double  remquol();
extern float        rintf();
extern long double  rintl();
extern double       round();
extern float        roundf();
extern long double  roundl();
extern double       scalbln();
extern float        scalblnf();
extern long double  scalblnl();
extern double       scalbn();
extern float        scalbnf();
extern long double  scalbnl();
extern float        sinf();
extern float        sinhf();
extern float        sqrtf();
extern float        tanf();
extern float        tanhf();
extern double       tgamma();
extern float        tgammaf();
extern long double  tgammal();
extern float        truncf();
extern long double  truncl();
#endif

/*
 * The following interfaces are available only for the
 * non-default 128-bit long double mode.  By default long
 * double is the same as double (64-bit) and should use the
 * the double precision versions of these routines.
 *
 * Many of these routine may not actually exist.  The standards interfaces
 * are redefined in 128-mode later in this file.  The redefinitions are
 * are added here to cause link errors rather than runtime errors  
 * when attempting to use these routines in 128-bit long double mode.
 * Without these redefinitions the 64-bit versions in the libraries  
 * would be invoked at runtime.
 */
#ifdef __LONGDOUBLE128
long double __acosl128();
long double __asinl128();
long double __atanl128();
long double __atan2l128();
long double __cosl128();
long double __coshl128();
long double __sinl128();
long double __sinhl128();
long double __tanl128();
long double __tanhl128();
long double __expl128();
long double __logl128();
long double __log10l128();
long double __powl128();
long double __sqrtl128();
long double __ceill128();
long double __fabsl128();
long double __floorl128();
long double __fmodl128();
long double frexpl();
long double ldexpl();
long double modfl();
#endif /* #ifdef __LONGDOUBLE128 */

#else  /*_NO_PROTO */			/* Use ANSI C required prototyping */

extern  double acos(double);
extern  double asin(double);
extern  double atan(double);
extern  double atan2(double,double);
extern  double ceil(double);
extern  double copysign(double, double);
extern  double cos(double);
extern  double cosh(double);
extern  double exp(double);
extern  double fabs(double);
extern  double floor(double);
extern  double fmod(double, double);
extern  double frexp(double, int *);
extern  double ldexp(double, int);
extern  double log(double);
extern  double log10(double);
extern  double modf(double, double *);
extern  double pow(double, double);
extern  double sin(double);
extern  double sinh(double);
extern  double sqrt(double);
extern  double tan(double);
extern  double tanh(double);
extern  double trunc(double);

/* Symbols new in C99 */
#ifdef _ISOC99_SOURCE
extern float        acosf(float);
extern float        acoshf(float);
extern long double  acoshl(long double);
extern long double  acosl(long double);
extern float        asinf(float);
extern float        asinhf(float);
extern long double  asinhl(long double);
extern long double  asinl(long double);
extern float        atan2f(float, float);
extern long double  atan2l(long double, long double);
extern float        atanf(float);
extern float        atanhf(float);
extern long double  atanhl(long double);
extern long double  atanl(long double);
extern float        cbrtf(float);
extern long double  cbrtl(long double);
extern float        ceilf(float);
extern long double  ceill(long double);
extern float        copysignf(float, float);
extern long double  copysignl(long double, long double);
extern float        cosf(float);
extern float        coshf(float);
extern long double  coshl(long double);
extern long double  cosl(long double);
extern float        erfcf(float);
extern long double  erfcl(long double);
extern float        erff(float);
extern long double  erfl(long double);
extern double       exp2(double);
extern float        exp2f(float);
extern long double  exp2l(long double);
extern float        expf(float);
extern long double  expl(long double);
extern float        expm1f(float);
extern long double  expm1l(long double);
extern float        fabsf(float);
extern long double  fabsl(long double);
extern double       fdim(double, double);
extern float        fdimf(float, float);
extern long double  fdiml(long double, long double);
extern float        floorf(float);
extern long double  floorl(long double);
extern double       fma(double, double, double);
extern float        fmaf(float, float, float);
extern long double  fmal(long double, long double, long double);
extern double       fmax(double, double);
extern float        fmaxf(float, float);
extern long double  fmaxl(long double, long double);
extern double       fmin(double, double);
extern float        fminf(float, float);
extern long double  fminl(long double, long double);
extern float        fmodf(float, float);
extern long double  fmodl(long double, long double);
extern float 	    frexpf(float, int *);
extern float        hypotf(float, float);
extern long double  hypotl(long double, long double);
extern int          ilogbf(float);
extern int          ilogbl(long double         );
extern float        ldexpf(float, int);
extern float        lgammaf(float);
extern long double  lgammal(long double);
#ifdef _LONG_LONG
extern long long int llrint(double);
extern long long int llrintf(float);
extern long long int llrintl(long double);
extern long long int llround(double);
extern long long int llroundf(float);
extern long long int llroundl(long double);
#endif
extern float        log10f(float);
extern long double  log10l(long double);
extern float        log1pf(float);
extern long double  log1pl(long double);
extern float        log2f(float);
extern double       log2(double);
extern long double  log2l(long double);
extern float        logbf(float);
extern long double  logbl(long double);
extern float        logf(float);
extern long double  logl(long double);
extern long int     lrint(double);
extern long int     lrintf(float);
extern long int     lrintl(long double);
extern long int     lround(double);
extern long int     lroundf(float);
extern long int     lroundl(long double);
extern float        modff(float, float *);
extern double       nan(const char *);
extern float        nanf(const char *);
extern long double  nanl(const char *);
extern double       nearbyint(double);
extern float        nearbyintf(float);
extern long double  nearbyintl(long double);
extern float        nextafterf(float, float);
extern long double  nextafterl(long double, long double);
extern double       nexttoward(double, long double);
extern float        nexttowardf(float, long double);
extern long double  nexttowardl(long double, long double);
extern float        powf(float, float);
extern long double  powl(long double, long double);
extern float        remainderf(float, float);
extern long double  remainderl(long double, long double);
extern double       remquo(double, double, int *);
extern float        remquof(float, float, int *);
extern long double  remquol(long double, long double, int *);
extern float        rintf(float);
extern long double  rintl(long double);
extern double       round(double);
extern float        roundf(float);
extern long double  roundl(long double);
extern double       scalbln(double, long);
extern float        scalblnf(float, long);
extern long double  scalblnl(long double, long);
extern double       scalbn(double, int);
extern float        scalbnf(float, int);
extern long double  scalbnl(long double, int);
extern float        sinf(float);
extern float        sinhf(float);
extern long double  sinhl(long double);
extern long double  sinl(long double);
extern float        sqrtf(float);
extern long double  sqrtl(long double);
extern float        tanf(float);
extern float        tanhf(float);
extern long double  tanhl(long double);
extern long double  tanl(long double);
extern double       tgamma(double);
extern float        tgammaf(float);
extern long double  tgammal(long double);
extern float        truncf(float);
extern long double  truncl(long double);
#endif

#ifdef __LONGDOUBLE128
long double __acosl128(long double);
long double __asinl128(long double);
long double __atanl128(long double);
long double __atan2l128(long double , long double);
long double __cosl128(long double);
long double __coshl128(long double);
long double __sinl128(long double);
long double __sinhl128(long double);
long double __tanl128(long double);
long double __tanhl128(long double);
long double __expl128(long double);
long double __logl128(long double);
long double __log10l128(long double);
long double __powl128(long double , long double);
long double __sqrtl128(long double);
long double __ceill128(long double);
long double __fabsl128(long double);
long double __floorl128(long double);
long double __fmodl128(long double , long double);

long double frexpl(long double ,   /* value */
		   int *);         /* exponent */
long double ldexpl(long double ,   /* value */
		   int);           /* exponent */
long double modfl(long double ,    /* value */
		  long double *);  /* integer part */
#endif /* #ifdef __LONGDOUBLE128 */

#endif /*_NO_PROTO */

/* 
 * frexpl(), ldexpl(), and modfl() have preexisting shared versions which are 
 * 128-bit only.  64-bit versions must be made available for C99 for the
 * default 64-bit long double.  These cannot simply be macros because the
 * actual routines will be the incorrect form in 64-bit mode if the user
 * forces the actual routines to be used through undef or macro suppression
 * per the standard.
 */
#if defined(_ISOC99_SOURCE) && !defined(__LONGDOUBLE128)
static long double frexpl(long double __x, int *__i)
{
     return (long double) frexp((double) __x, __i);
}

static long double ldexpl(long double __x, int __i)
{
     return (long double) ldexp((double) __x, __i);
}

#ifndef __MODFL
static long double modfl(long double __x, long double *__y)
{
     return (long double) modf((double) __x, (double *) __y);
}
#endif
#endif

/*
 *   The following macro definitions cause the XLC compiler to inline
 *   these functions whenever possible.  __MATH__ is defined by the compiler.
 */
 
#ifdef __MATH__
#define acos(__x)         __acos(__x)
#define asin(__x)         __asin(__x)
#define atan(__x)         __atan(__x)
#define atan2(__x,__y)      __atan2(__x,__y)
#define cos(__x)          __cos(__x)
#define exp(__x)          __exp(__x)
#define fabs(__x)         __fabs(__x)
#define log(__x)          __log(__x)
#define log10(__x)        __log10(__x)
#define sin(__x)          __sin(__x)
#define sqrt(__x)         __sqrt(__x)
#define tan(__x)          __tan(__x)
#ifdef __IBMC__
#if (__xlC__ >= 0x0600) /* VAC version 6 and above */
#define floor(__x)        __floor(__x)
#define ceil(__x)         __ceil(__x)
#endif /* __xlC__ >= 0x0600 */
#endif /* __IBMC__ */
#endif

#ifdef _ISOC99_SOURCE

#ifdef __LONGDOUBLE128

#define acoshl(__x)		__acoshl128((long double) (__x))
#define acosl(__x)		__acosl128((long double) (__x))
#define asinhl(__x)		__asinhl128((long double) (__x))
#define asinl(__x)		__asinl128((long double) (__x))
#define atan2l(__x, __y)	__atan2l128((long double) (__x), (long double) (__y))
#define atanhl(__x)		__atanhl128((long double) (__x))
#define atanl(__x)		__atanl128((long double) (__x))
#define cbrtl(__x)		__cbrtl128((long double) (__x))
#define ceill(__x)		__ceill128((long double) (__x))
#define copysignl(__x, __y)	__copysignl128((long double) (__x), (long double) (__y))
#define coshl(__x)		__coshl128((long double) (__x))
#define cosl(__x)		__cosl128((long double) (__x))
#define erfcl(__x)		__erfcl128((long double) (__x))
#define erfl(__x)		__erfl128((long double) (__x))
#define exp2l(__x)		__exp2l128((long double) (__x))
#define expl(__x)		__expl128((long double) (__x))
#define expm1l(__x)		__expm1l128((long double) (__x))
#define fabsl(__x)		__fabsl128((long double) (__x))
#define fdiml(__x, __y)		__fdiml128((long double) (__x), (long double) (__y))
#define floorl(__x)		__floorl128((long double) (__x))
#define fmal(__x, __y, __z)	__fmal128((long double) (__x), (long double) (__y), (long double) (__z))
#define fmaxl(__x, __y)		__fmaxl128((long double) (__x), (long double) (__y))
#define fminl(__x, __y)		__fminl128((long double) (__x), (long double) (__y))
#define fmodl(__x, __y)		__fmodl128((long double) (__x), (long double) (__y))
#define hypotl(__x, __y)	__hypotl128((long double) (__x), (long double) (__y))
#define ilogbl(__x)		__ilogbl128((long double) (__x))
#define lgammal(__x)		__lgammal128((long double) (__x))
#ifdef _ALL_SOURCE
#define lgammal_r(__x)		__lgammal128_r((long double) (__x))
#endif
#ifdef _LONG_LONG
#define llrintl(__x)		__llrintl128((long double) (__x))
#define llroundl(__x)		__llroundl128((long double) (__x))
#endif
#define log10l(__x)		__log10l128((long double) (__x))
#define log1pl(__x)		__log1pl128((long double) (__x))
#define log2l(__x)		__log2l128((long double) (__x))
#define logbl(__x)		__logbl128((long double) (__x))
#define logl(__x)		__logl128((long double) (__x))
#define lrintl(__x)		__lrintl128((long double) (__x))
#define lroundl(__x)		__lroundl128((long double) (__x))
#define nanl(__x)		__nanl128((long double) (__x))
#define nearbyintl(__x)		__nearbyintl128((long double) (__x))
#define nextafterl(__x, __y)	__nextafterl128((long double) (__x), (long double) (__y))
#define nexttoward(__x, __y)	__nexttoward128((double) (__x), (long double) (__y))
#define nexttowardf(__x, __y)	__nexttowardf128((float) (__x), (long double) (__y))
#define nexttowardl(__x, __y)	__nexttowardl128((long double) (__x), (long double) (__y))
#define powl(__x, __y)		__powl128((long double) (__x), (long double) (__y))
#define remainderl(__x, __y)	__remainderl128((long double) (__x), (long double) (__y))
#define remquol(__x, __y, __z)	__remquol128((long double) (__x), (long double) (__y), __z)
#define rintl(__x)		__rintl128((long double) (__x))
#define roundl(__x)		__roundl128((long double) (__x))
#define scalblnl(__x, __y)	__scalblnl128((long double) (__x), __y)
#define scalbnl(__x, __y)	__scalbnl128((long double) (__x), __y)
#define sinhl(__x)		__sinhl128((long double) (__x))
#define sinl(__x)		__sinl128((long double) (__x))
#define sqrtl(__x)		__sqrtl128((long double) (__x))
#define tanhl(__x)		__tanhl128((long double) (__x))
#define tanl(__x)		__tanl128((long double) (__x))
#define tgammal(__x)		__tgammal128((long double) (__x))
#define truncl(__x)		__truncl128((long double) (__x))

#else /* __LONGDOUBLE128 */

/* Provide direct macros for the long double routines to avoid the 
 * overhead of an extra call.  The actual linkable routines simply reinvoke
 * the routines referenced below.
 */
#define acoshl(__x)		acosh((double) (__x))
#define acosl(__x)		acos((double) (__x))
#define asinhl(__x)		asinh((double) (__x))
#define asinl(__x)		asin((double) (__x))
#define atan2l(__x, __y)	atan2((double) (__x), (double) (__y))
#define atanhl(__x)		atanh((double) (__x))
#define atanl(__x)		atan((double) (__x))
#define cbrtl(__x)		cbrt((double) (__x))
#define ceill(__x)		ceil((double) (__x))
#define copysignl(__x, __y)	copysign((double) (__x), (double) (__y))
#define coshl(__x)		cosh((double) (__x))
#define cosl(__x)		cos((double) (__x))
#define erfcl(__x)		erfc((double) (__x))
#define erfl(__x)		erf((double) (__x))
#define exp2l(__x)		exp2((double) (__x))
#define expl(__x)		exp((double) (__x))
#define expm1l(__x)		expm1((double) (__x))
#define fabsl(__x)		fabs((double) (__x))
#define fdiml(__x, __y)		fdim((double) (__x), (double) (__y))
#define floorl(__x)		floor((double) (__x))
#define fmal(__x, __y, __z)	fma((double) (__x), (double) (__y), (double) (__z))
#define fmaxl(__x, __y)		fmax((double) (__x), (double) (__y))
#define fminl(__x, __y)		fmin((double) (__x), (double) (__y))
#define fmodl(__x, __y)		fmod((double) (__x), (double) (__y))
#define hypotl(__x, __y)	hypot((double) (__x), (double) (__y))
#define ilogbl(__x)		ilogb((double) (__x))
#define lgammal(__x)		lgamma((double) (__x))
#ifdef _ALL_SOURCE
#define lgammal_r(__x)		lgamma_r((double) (__x))
#endif
#ifdef _LONG_LONG
#define llrintl(__x)		llrint((double) (__x))
#define llroundl(__x)		llround((double) (__x))
#endif
#define log10l(__x)		log10((double) (__x))
#define log1pl(__x)		log1p((double) (__x))
#define log2l(__x)		log2((double) (__x))
#define logbl(__x)		logb((double) (__x))
#define logl(__x)		log((double) (__x))
#define lrintl(__x)		lrint((double) (__x))
#define lroundl(__x)		lround((double) (__x))
#define nanl(__x)		nan(__x)
#define nearbyintl(__x)		nearbyint((double) (__x))
#define nextafterl(__x, __y)	nextafter((double) (__x), (double) (__y))
#define nexttowardl(__x, __y)	nexttoward((double) (__x), (long double) (__y))
#define powl(__x, __y)		pow((double) (__x), (double) (__y))
#define remainderl(__x, __y)	remainder((double) (__x), (double) (__y))
#define remquol(__x, __y, __z)	remquo((double) (__x), (double) (__y), __z)
#define rintl(__x)		rint((double) (__x))
#define roundl(__x)		round((double) (__x))
#define scalblnl(__x, __y)	scalbln((double) (__x), __y)
#define scalbnl(__x, __y)	scalbn((double) (__x), __y)
#define sinhl(__x)		sinh((double) (__x))
#define sinl(__x)		sin((double) (__x))
#define sqrtl(__x)		sqrt((double) (__x))
#define tanhl(__x)		tanh((double) (__x))
#define tanl(__x)		tan((double) (__x))
#define tgammal(__x)		tgamma((double) (__x))
#define truncl(__x)		trunc((double) (__x))

#endif /* __LONGDOUBLE128 */

#else /* _ISOC99_SOURCE */

#ifdef __LONGDOUBLE128

/* If not compiling C99, define the __LONGDOUBLE128 routines which
 * existed before C99 to use the 128bit version of the routine.
 */
#define acosl		__acosl128
#define asinl		__asinl128
#define atanl		__atanl128
#define atan2l		__atan2l128
#define cosl		__cosl128
#define coshl		__coshl128
#define sinl		__sinl128
#define sinhl		__sinhl128
#define tanl		__tanl128
#define tanhl		__tanhl128
#define expl		__expl128
#define logl		__logl128
#define log10l		__log10l128
#define powl		__powl128
#define sqrtl		__sqrtl128
#define ceill		__ceill128
#define fabsl		__fabsl128
#define floorl		__floorl128
#define fmodl		__fmodl128

#endif /* __LONGDOUBLE128 */

#endif /* _ISOC99_SOURCE */

#endif /*_ANSI_C_SOURCE */


#if defined(_ISOC99_SOURCE) || defined(_XOPEN_SOURCE)

#ifdef _NO_PROTO

extern     double   erf();
extern     double   erfc();
extern     double   hypot();
extern     double   lgamma();
#ifdef _ALL_SOURCE
extern     double   lgamma_r();
#endif

#ifdef __LONGDOUBLE128
long double __erfl128();
long double __erfcl128();
long double __lgammal128();
#ifdef _ALL_SOURCE
long double __lgammal128_r();
#endif /* _ALL_SOURCE */
#endif /* #ifdef __LONGDOUBLE128 */

#if _XOPEN_SOURCE_EXTENDED==1 || defined(_ISOC99_SOURCE)
extern     double   acosh();
extern     double   asinh();
extern     double   atanh();
extern     double   cbrt();
extern     double   expm1();
extern     int      ilogb();
extern     double   log1p();
extern     double   logb();
extern     double   nextafter();
extern     double   remainder();
extern     double   rint();
#endif /* _XOPEN_SOURCE_EXTENDED */

#else /* _NO_PROTO */

extern     double   erf(double);
extern     double   erfc(double);
extern     double   hypot(double,double);
extern     double   lgamma(double);
#ifdef _ALL_SOURCE
extern     double   lgamma_r(double, int *);
#endif /* _ALL_SOURCE */

#ifdef __LONGDOUBLE128
long double __erfl128(long double);
long double __erfcl128(long double);
long double __lgammal128(long double);
#ifdef _ALL_SOURCE
long double __lgammal128_r(long double, int *);
#endif /* _ALL_SOURCE */
#endif /* #ifdef __LONGDOUBLE128 */

#if _XOPEN_SOURCE_EXTENDED==1 || defined(_ISOC99_SOURCE)
extern     double   acosh(double);
extern     double   asinh(double);
extern     double   atanh(double);
extern     double   cbrt(double);
extern     double   expm1(double);
extern     int      ilogb(double);
extern     double   log1p(double);
extern     double   logb(double);
extern     double   nextafter(double, double);
extern     double   remainder(double, double);
extern     double   rint(double);
#endif /* _XOPEN_SOURCE_EXTENDED==1 || defined(_ISOC99_SOURCE) */

#endif /* _NO_PROTO */

#endif /* _ISOC99_SOURCE || _XOPEN_SOURCE */


/*
 *
 * The following function prototypes define functions available in the
 * AIX system but not required by the ANSI standard. They will not be
 * included if only _ANSI_C_SOURCE is defined (strict ANSI conformance).
 *
 */

#ifdef _XOPEN_SOURCE

extern int signgam;

/*
 *      Useful mathmatical constants:
 *
 * M_E          -- e
 * M_LOG2E      -- log2(e)
 * M_LOG10E     -- log10(e)
 * M_LN2        -- ln(2)
 * M_PI         -- pi
 * M_PI_2       -- pi/2
 * M_PI_4       -- pi/4
 * M_1_PI       -- 1/pi
 * M_2_PI       -- 2/pi
 * M_2_SQRTPI   -- 2/(sqrt(pi))
 * M_SQRT2      -- sqrt(2)
 * M_SQRT1_2    -- 1/sqrt(2)
 *
 * These constants are provided to more significant digits
 * than is necessary for a 64-bit double precision number; they 
 * may be used for other purposes where the extra precision
 * is necessary or useful.
 */

#define M_E         2.71828182845904523536028747135266250
#define M_LOG2E     1.44269504088896340735992468100189214
#define M_LOG10E    0.434294481903251827651128918916605082
#define M_LN2       0.693147180559945309417232121458176568
#define M_LN10      2.30258509299404568401799145468436421
#define M_PI        3.14159265358979323846264338327950288
#define M_PI_2      1.57079632679489661923132169163975144
#define M_PI_4      0.785398163397448309615660845819875721
#define M_1_PI      0.318309886183790671537767526745028724
#define M_2_PI      0.636619772367581343075535053490057448
#define M_2_SQRTPI  1.12837916709551257389615890312154517
#define M_SQRT2     1.41421356237309504880168872420969808
#define M_SQRT1_2   0.707106781186547524400844362104849039

/* MAXFLOAT is also defined in values.h */
#ifndef MAXFLOAT
extern unsigned int _SFPMAX;
#define MAXFLOAT            (*((float *) (&_SFPMAX)))
#endif

#ifdef _NO_PROTO

#if (_XOPEN_SOURCE<600) || defined(_ALL_SOURCE)
extern     int      isnan();
extern     double   gamma();
extern     double   gamma_r();
#endif
extern     double   j0();
extern     double   j1();
extern     double   jn();
extern     double   y0();
extern     double   y1();
extern     double   yn();

#if _XOPEN_SOURCE_EXTENDED==1
extern     double   scalb();
#endif /* _XOPEN_SOURCE_EXTENDED */

#else /* _NO_PROTO */

#if (_XOPEN_SOURCE<600) || defined(_ALL_SOURCE)
extern     int      isnan(double);
extern     double   gamma(double);
extern     double   gamma_r(double, int *);
#endif
extern     double   j0(double);
extern     double   j1(double);
extern     double   jn(int, double);
extern     double   y0(double);
extern     double   y1(double);
extern     double   yn(int, double);

#if _XOPEN_SOURCE_EXTENDED==1
extern     double   scalb(double, double);
#endif /* _XOPEN_SOURCE_EXTENDED */

#endif /* _NO_PROTO */

#if (!defined(_ISOC99_SOURCE)) && defined(__LONGDOUBLE128)
/* If not compiling C99, define the __LONGDOUBLE128 routines which
 * existed before C99 to use the 128bit version of the routine.
 */
#define erfl		__erfl128
#define erfcl		__erfcl128
#define lgammal		__lgammal128
#ifdef _ALL_SOURCE
#define lgammal_r	__lgammal128_r
#endif
#endif /* !_ISOC99_SOURCE && __LONGDOUBLE128 */

#endif /* _XOPEN_SOURCE */

#ifdef _ALL_SOURCE

#define DINFINITY _DBLINF

#ifndef	_BSD
#ifndef _H_STDLIB
#include <stdlib.h>
#endif
#else	/* _BSD */
/*
 *	Any changes to the below declaration must be verified with
 *	changes to the same function declaration in <stdlib.h>
 */
#ifndef	_NO_PROTO
extern double   atof(const char *);
#else	/* _NO_PROTO */
extern double   atof();
#endif	/* _NO_PROTO */
#endif	/* _BSD */

/*
 * C99 defines a conflicting version of cabs from AIX versions
 * prior to AIX 5.2.  The previous version is renamed to _cabshypot
 * since it is the non-standard version and is only available as a
 * statically linked routine.
 */
#if (!defined(_ISOC99_SOURCE)) || defined(_HYPOTCABS)
#define cabs _cabshypot
#endif

#ifdef _NO_PROTO

extern     double   _cabshypot();
extern     double   drem();
extern     double   exp__E();
extern     double   log__L();
extern     double   nearest();
extern     double   rsqrt();
#ifndef    __cplusplus
extern     int      class();
#else
extern     int      _class();
#endif
extern     int      finite();
extern     int      itrunc();
extern     int      unordered();
extern     unsigned  uitrunc();
extern     int      isinf();
#ifdef _POWER
extern     int      dtoi();
#endif

#else /* _NO_PROTO */			/* Use ANSI C required prototyping */

     struct dbl_hypot {
         double x, y;
     };

extern     double   _cabshypot(struct dbl_hypot);
extern     double   drem(double, double);
extern     double   exp__E(double, double);
extern     double   log__L(double);
extern     double   nearest(double);
extern     double   rsqrt(double);
extern     int      finite(double);
extern     int      itrunc(double);
extern     int      unordered(double, double);
extern     unsigned  uitrunc(double);
extern     int      isinf(double);
#ifdef _POWER
extern     int      dtoi(double);
     /* The POWER wants arguments in both GPR's and FPR's
      * By not specifying a prototype of double, the compiler
      * will put the argument in both types of registers.
      */
#ifndef    __cplusplus
extern     int      class();
#else
     /* _class does nothing but calls class subroutine
      * internally. So prototyping like this will
      * still work and avoid compilation errors
      */
extern     int      _class(double);
#endif
#else
#ifndef    __cplusplus
extern     int      class(double);
#else
extern     int      _class(double);
#endif
#endif


#endif /* _NO_PROTO */

#ifndef    __cplusplus
struct exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};
#else
struct __exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};
#endif /* __cplusplus */

#define 	DOMAIN		01
#define		SING		02
#define		OVERFLOW	03
#define		UNDERFLOW	04
#define		TLOSS		05
#define		PLOSS		06


/*
 *      Useful mathmatical constants:
 *
 * HUGE         - +infinity
 * M_2PI        - 2*pi
 *
 */
#define HUGE       HUGE_VAL
#define M_2PI      6.2831853071795862320E0  /*Hex  2^ 2 * 1.921FB54442D18 */

/* This is the nearest number to the cube root of MAXDOUBLE that   */
/*      doesn't cause the cube of it to overflow.                  */
/* In double precision hex this constant is: 554428a2 f98d728a     */
#define CUBRTHUGE      5.6438030941223618e102
#define INV_CUBRTHUGE  1.7718548704178434e-103

#endif /* ALL_SOURCE */

#ifdef _ISOC99_SOURCE

/* 
 * This section contains a series of "real-floating-type" macros as
 * prescribed by C99
 */
extern     int   _class(double);
extern     int   _classf(float);
extern     int   _isfinite(double);
extern     int   _isfinitef(float);
extern     int   _isinf(double);
extern     int   _isinff(float);
extern     int   _isnan(double);
extern     int   _isnanf(float);
extern     int   _isnormal(double);
extern     int   _isnormalf(float);
extern     int   _signbit(double);
extern     int   _signbitf(float);

#ifdef __LONGDOUBLE128
extern     int   _classl128(long double);
extern     int   _isfinitel128(long double);
extern     int   _isinfl128(long double);
extern     int   _isnanl128(long double);
extern     int   _isnormall128(long double);
extern     int   _signbitl128(long double);
#endif

#ifdef __STDC_WANT_DEC_FP__
#define __dfp_iszero(__x)   ((sizeof(__x)== 4 || sizeof(__x)==8) ? __d64_iszero(__x)   : __d128_iszero(__x))
#define __dfp_isfinite(__x) ((sizeof(__x)== 4 || sizeof(__x)==8) ? __d64_isfinite(__x) : __d128_isfinite(__x))
#define __dfp_isinf(__x)    ((sizeof(__x)== 4 || sizeof(__x)==8) ? __d64_isinf(__x)    : __d128_isinf(__x))
#define __dfp_isnan(__x)    ((sizeof(__x)== 4 || sizeof(__x)==8) ? __d64_isnan(__x)    : __d128_isnan(__x))
#define __dfp_issigned(__x) ((sizeof(__x)== 4 || sizeof(__x)==8) ? __d64_issigned(__x) : __d128_issigned(__x))

#ifndef _H_FLOAT
#define DEC32_MIN       1E-95DF
#define DEC32_MAX       9.999999E96DF
#endif
#define __d32_isnormal(__x) \
        (__d64_isnan(__x) ? 0 : \
         (((_Decimal32)(__x) >= DEC32_MIN) && ((_Decimal32)(__x) <= DEC32_MAX)) || \
         (((_Decimal32)(__x) <= -DEC32_MIN) && ((_Decimal32)(__x) >= -DEC32_MAX)))
#define __dfp_isnormal(__x) \
        (sizeof(__x)== 4 ? __d32_isnormal(__x) :\
         sizeof(__x)== 8 ? __d64_isnormal(__x) :\
         __d128_isnormal(__x))

#define __dfp_fpclassify(__x) \
        (__dfp_isinf(__x)    ? FP_INFINITE :\
         __dfp_isnan(__x)    ? FP_NAN      :\
         __dfp_iszero(__x)   ? FP_ZERO     :\
         __dfp_isnormal(__x) ? FP_NORMAL   :\
         FP_SUBNORMAL)

/* If __x is binary floating point, returns 1, otherwise 0   */
#define  __bfp_compatible(__x) (0, __extension__ (_Decimal128)1/(_Decimal128)10 != \
                              (_Decimal128)((__typeof(__x))1/(__typeof(__x))10))

#else
#define __dfp_iszero(__x)     (0)
#define __dfp_isfinite(__x)   (0)
#define __dfp_isinf(__x)      (0)
#define __dfp_isnan(__x)      (0)
#define __dfp_isnormal(__x)   (0)
#define __dfp_issigned(__x)   (0)
#define __dfp_fpclassify(__x) (0)
#define __bfp_compatible(__x) (1)

#endif /* __STDC_WANT_DEC_FP__ */

#ifndef __LONGDOUBLE128
#define __bfp_fpclassify(__x)   \
    (sizeof(__x) == sizeof(float) ?  \
        ((_classf(__x) == FP_SNAN) || (_classf(__x) == FP_QNAN) ? \
            FP_QNAN : \
            (_classf(__x) & 0x00000001 ? \
                _classf(__x) - 1 : \
                _classf(__x)) ) : \
        ((_class(__x) == FP_SNAN) || (_class(__x) == FP_QNAN) ? \
            FP_QNAN : \
            (_class(__x)  & 0x00000001 ? \
                _class(__x) - 1 : \
                _class(__x))))

#define __bfp_isfinite(__x)     \
        ((sizeof(__x) == sizeof(float))  ?  _isfinitef(__x) : _isfinite(__x))

#define __bfp_isinf(__x)        \
        ((sizeof(__x) == sizeof(float))  ?  _isinff(__x) : _isinf(__x))

#define __bfp_isnan(__x)        \
        ((sizeof(__x) == sizeof(float))  ?  _isnanf(__x) : _isnan(__x))

#define __bfp_isnormal(__x)     \
        ((sizeof(__x) == sizeof(float))  ?  _isnormalf(__x) : _isnormal(__x))

#define __bfp_signbit(__x)      \
        ((sizeof(__x) == sizeof(float))  ?  _signbitf(__x) : _signbit(__x))

#else
#define __bfp_fpclassify(__x)   \
 (sizeof(__x) == sizeof(float) ?  \
        ((_classf(__x) == FP_SNAN) || (_classf(__x) == FP_QNAN) ? \
            FP_QNAN : \
            (_classf(__x) & 0x00000001 ? \
                _classf(__x) - 1 : \
                _classf(__x)))  :\
    (sizeof(__x) == sizeof(double) ? \
        ((_class(__x) == FP_SNAN) || (_class(__x) == FP_QNAN) ? \
            FP_QNAN : \
            (_class(__x)  & 0x00000001 ? \
                _class(__x) - 1 : \
                _class(__x))) :\
    ((_classl128(__x) == FP_SNAN) || (_classl128(__x) == FP_QNAN) ? \
            FP_QNAN: \
            (_classl128(__x) & 0x00000001 ? \
                _classl128(__x) - 1 : \
                _classl128(__x)))))

#define __bfp_isfinite(__x)     \
        ((sizeof(__x) == sizeof(float))  ?  _isfinitef(__x) : \
         (sizeof(__x) == sizeof(double)) ?  _isfinite(__x) : \
                                       _isfinitel128(__x))
#define __bfp_isinf(__x)        \
        ((sizeof(__x) == sizeof(float))  ?  _isinff(__x) : \
         (sizeof(__x) == sizeof(double)) ?  _isinf(__x) : \
                                       _isinfl128(__x))
#define __bfp_isnan(__x)        \
        ((sizeof(__x) == sizeof(float))  ?  _isnanf(__x) : \
         (sizeof(__x) == sizeof(double)) ?  _isnan(__x) : \
                                       _isnanl128(__x))
#define __bfp_isnormal(__x)     \
        ((sizeof(__x) == sizeof(float))  ?  _isnormalf(__x) : \
         (sizeof(__x) == sizeof(double)) ?  _isnormal(__x) : \
                                       _isnormall128(__x))
#define __bfp_signbit(__x)      \
        ((sizeof(__x) == sizeof(float))  ?  _signbitf(__x) : \
         (sizeof(__x) == sizeof(double)) ?  _signbit(__x) : \
                                       _signbitl128(__x))
#endif

/* The compiler needs to define the required compiler BIFs (e.g. __d64_iszero)
 * to use the below macros if __STDC_WANT_DEC_FP__ macro is defined.
 */
#define fpclassify(__x)  (__bfp_compatible(__x)  ? __bfp_fpclassify(__x): __dfp_fpclassify(__x))
#define isfinite(__x)    (__bfp_compatible(__x)  ? __bfp_isfinite(__x)  : __dfp_isfinite(__x))
#define isinf(__x)       (__bfp_compatible(__x)  ? __bfp_isinf(__x)     : __dfp_isinf(__x))
#define isnan(__x)       (__bfp_compatible(__x)  ? __bfp_isnan(__x)     : __dfp_isnan(__x))
#define isnormal(__x)    (__bfp_compatible(__x)  ? __bfp_isnormal(__x)  : __dfp_isnormal(__x))
#define signbit(__x)     (__bfp_compatible(__x)  ? __bfp_signbit(__x)   : __dfp_issigned(__x))

/* Comparison macros which do not raise floating point e__xceptions */
#define isgreater(__x, __y) \
        ((isnan(__x) || isnan(__y)) ? 0 : (__x) > (__y))

#define isgreaterequal(__x, __y) \
        ((isnan(__x) || isnan(__y)) ? 0 : (__x) >= (__y))

#define isless(__x, __y) \
        ((isnan(__x) || isnan(__y)) ? 0 : (__x) < (__y))

#define islessequal(__x, __y) \
        ((isnan(__x) || isnan(__y)) ? 0 : (__x) <= (__y))

#define islessgreater(__x, __y) \
        ((isnan(__x) || isnan(__y)) ? 0 : (__x) != (__y))

#define isunordered(__x, __y) \
        (isnan(__x) || isnan(__y))

#endif


/*
 * 64-bit integer support, known as long long int and unsigned long long int
 */
#if (defined(_LONG_LONG) && defined(_ALL_SOURCE))
#ifdef _NO_PROTO

extern long long int __multi64( );
extern long long int __divi64( );
extern unsigned long long int __divu64( );
extern long long int __maxi64( );
extern long long int __mini64( );
extern long long int __f64toi64rz( );
extern unsigned long long int __f64tou64rz( );

#ifdef __LONGDOUBLE128
extern long long int __f128toi64rz( );
extern unsigned long long int __f128tou64rz( );
#endif /* __LONGDOUBLE128 */

#else /* ifdef _NO_PROTO */

extern long long int __multi64( long long int, long long int );
extern long long int __divi64( long long int, long long int );
extern unsigned long long int __divu64( unsigned long long int, 
					unsigned long long int );
extern long long int __maxi64( long long int, long long int );
extern long long int __mini64( long long int, long long int );
extern long long int __f64toi64rz( double );
extern unsigned long long int __f64tou64rz( double );

#ifdef __LONGDOUBLE128
extern long long int __f128toi64rz( long double );
extern unsigned long long int __f128tou64rz( long double );
#endif /* __LONGDOUBLE128 */

#endif /* _NO_PROTO */
#endif /* if defined(_LONG_LONG) && defined(_ALL_SOURCE) */

/*
 *   __XLC121__ is automatically defined by the XLC 1.2.1 compiler so that
 *   the compiler can inline the following function when possible.
 */

 
#if (defined (__MATH__) &&  defined (__XLC121__) && defined (_ALL_SOURCE) )
#define copysign(x,y)     __copysign(x,y)
#endif

/*
 *  This section is for Decimal Floating Point (DFP) items.
 *  DFP support is only present if __STDC_WANT_DEC_FP__ is defined.
 */
#ifdef __STDC_WANT_DEC_FP__

static const unsigned int _DEC_QNAN = 0x7C000000;
static const unsigned int _DEC_INF = 0x78000000;

#ifndef _LITTLE_ENDIAN
static const unsigned int _DEC64_INF[2] = {0x78000000, 0x00000000};
static const unsigned int _DEC128_INF[4] = {0x78000000, 0x00000000, 0x00000000, 0x00000000};
#else
static const unsigned int _DEC64_INF[2] = {0x00000000, 0x78000000};
static const unsigned int _DEC128_INF[4] = {0x00000000, 0x00000000, 0x00000000, 0x78000000};
#endif

#define DEC_NAN		(*((_Decimal32 *)(&_DEC_QNAN)))
#define DEC_INFINITY	(*((_Decimal32 *)(&_DEC_INF)))
#define HUGE_VAL_D32	DEC_INFINITY
#define HUGE_VAL_D64	(*((_Decimal64 *)(&_DEC64_INF)))
#define HUGE_VAL_D128	(*((_Decimal128 *)(&_DEC128_INF)))


#ifdef __IBM_DFP_NATIVE
/* Only native version is requested, which will run only on DFP hardware.
 * In this case all the calls to these DFP math APIs will be replaced
 * by the corresponding native versions.
 */

#define ceild32         ceild32_native
#define ceild64         ceild64_native
#define ceild128        ceild128_native
#define floord32        floord32_native
#define floord64        floord64_native
#define floord128       floord128_native
#define nearbyintd32    nearbyintd32_native
#define nearbyintd64    nearbyintd64_native
#define nearbyintd128   nearbyintd128_native
#define rintd32         rintd32_native
#define rintd64         rintd64_native
#define rintd128        rintd128_native
#define lrintd32        lrintd32_native
#define lrintd64        lrintd64_native
#define lrintd128       lrintd128_native
#define llrintd32       llrintd32_native
#define llrintd64       llrintd64_native
#define llrintd128      llrintd128_native
#define roundd32        roundd32_native
#define roundd64        roundd64_native
#define roundd128       roundd128_native
#define lroundd32       lroundd32_native
#define lroundd64       lroundd64_native
#define lroundd128      lroundd128_native
#define llroundd32      llroundd32_native
#define llroundd64      llroundd64_native
#define llroundd128     llroundd128_native
#define truncd32        truncd32_native
#define truncd64        truncd64_native
#define truncd128       truncd128_native
#define copysignd32     copysignd32_native
#define copysignd64     copysignd64_native
#define copysignd128    copysignd128_native
#define nand32          nand32_native
#define nand64          nand64_native
#define nand128         nand128_native
#define nextafterd32    nextafterd32_native
#define nextafterd64    nextafterd64_native
#define nextafterd128   nextafterd128_native
#define nexttowardd32   nexttowardd32_native
#define nexttowardd64   nexttowardd64_native
#define nexttowardd128  nexttowardd128_native
#define fdimd32         fdimd32_native
#define fdimd64         fdimd64_native
#define fdimd128        fdimd128_native
#define fmaxd32         fmaxd32_native
#define fmaxd64         fmaxd64_native
#define fmaxd128        fmaxd128_native
#define fmind32         fmind32_native
#define fmind64         fmind64_native
#define fmind128        fmind128_native
#define fabsd32         fabsd32_native
#define fabsd64         fabsd64_native
#define fabsd128        fabsd128_native
#define frexpd32        frexpd32_native
#define frexpd64        frexpd64_native
#define frexpd128       frexpd128_native
#define ilogbd32        ilogbd32_native
#define ilogbd64        ilogbd64_native
#define ilogbd128       ilogbd128_native
#define logbd32         logbd32_native
#define logbd64         logbd64_native
#define logbd128        logbd128_native
#define ldexpd32        ldexpd32_native
#define ldexpd64        ldexpd64_native
#define ldexpd128       ldexpd128_native
#define modfd32         modfd32_native
#define modfd64         modfd64_native
#define modfd128        modfd128_native
#define scalbnd32       scalbnd32_native
#define scalbnd64       scalbnd64_native
#define scalbnd128      scalbnd128_native
#define scalblnd32      scalblnd32_native
#define scalblnd64      scalblnd64_native
#define scalblnd128     scalblnd128_native
#define quantized32     quantized32_native
#define quantized64     quantized64_native
#define quantized128    quantized128_native
#define samequantumd32  samequantumd32_native
#define samequantumd64  samequantumd64_native
#define samequantumd128 samequantumd128_native
#define expd32          expd32_native
#define expd64          expd64_native
#define expd128         expd128_native
#define log10d32        log10d32_native
#define log10d64        log10d64_native
#define log10d128       log10d128_native
#define logd32          logd32_native
#define logd64          logd64_native
#define logd128         logd128_native
#define powd32          powd32_native
#define powd64          powd64_native
#define powd128         powd128_native
#define sqrtd32         sqrtd32_native
#define sqrtd64         sqrtd64_native
#define sqrtd128        sqrtd128_native
#define cosd32          cosd32_native
#define cosd64          cosd64_native
#define cosd128         cosd128_native
#define cospid32        cospid32_native
#define cospid64        cospid64_native
#define cospid128       cospid128_native
#define sind32          sind32_native
#define sind64          sind64_native
#define sind128         sind128_native
#define sinpid32        sinpid32_native
#define sinpid64        sinpid64_native
#define sinpid128       sinpid128_native
#define tand32          tand32_native
#define tand64          tand64_native
#define tand128         tand128_native
#define atan2d32        atan2d32_native
#define atan2d64        atan2d64_native
#define atan2d128       atan2d128_native
#define atand32         atand32_native
#define atand64         atand64_native
#define atand128        atand128_native
#define atanpid32       atanpid32_native
#define atanpid64       atanpid64_native
#define atanpid128      atanpid128_native
#define acosd32         acosd32_native
#define acosd64         acosd64_native
#define acosd128        acosd128_native
#define asind32         asind32_native
#define asind64         asind64_native
#define asind128        asind128_native
#define coshd32         coshd32_native
#define coshd64         coshd64_native
#define coshd128        coshd128_native
#define sinhd32         sinhd32_native
#define sinhd64         sinhd64_native
#define sinhd128        sinhd128_native
#define tanhd32         tanhd32_native
#define tanhd64         tanhd64_native
#define tanhd128        tanhd128_native
#define erfcd32         erfcd32_native
#define erfcd64         erfcd64_native
#define erfcd128        erfcd128_native
#define erfd32          erfd32_native
#define erfd64          erfd64_native
#define erfd128         erfd128_native
#define lgammad32       lgammad32_native
#define lgammad64       lgammad64_native
#define lgammad128      lgammad128_native
#define remainderd32    remainderd32_native
#define remainderd64    remainderd64_native
#define remainderd128   remainderd128_native
#define tgammad32       tgammad32_native
#define tgammad64       tgammad64_native
#define tgammad128      tgammad128_native
#define acoshd32        acoshd32_native
#define acoshd64        acoshd64_native
#define acoshd128       acoshd128_native
#define asinhd32        asinhd32_native
#define asinhd64        asinhd64_native
#define asinhd128       asinhd128_native
#define atanhd32        atanhd32_native
#define atanhd64        atanhd64_native
#define atanhd128       atanhd128_native
#define cbrtd32         cbrtd32_native
#define cbrtd64         cbrtd64_native
#define cbrtd128        cbrtd128_native
#define expm1d32        expm1d32_native
#define expm1d64        expm1d64_native
#define expm1d128       expm1d128_native
#define log1pd32        log1pd32_native
#define log1pd64        log1pd64_native
#define log1pd128       log1pd128_native
#define exp2d32         exp2d32_native
#define exp2d64         exp2d64_native
#define exp2d128        exp2d128_native
#define hypotd32        hypotd32_native
#define hypotd64        hypotd64_native
#define hypotd128       hypotd128_native
#define log2d32         log2d32_native
#define log2d64         log2d64_native
#define log2d128        log2d128_native
#define remquod32       remquod32_native
#define remquod64       remquod64_native
#define remquod128      remquod128_native
#define fmodd32         fmodd32_native
#define fmodd64         fmodd64_native
#define fmodd128        fmodd128_native
#define fmad128         fmad128_native

#endif /* __IBM_DFP_NATIVE */

#ifdef _NO_PROTO
extern _Decimal32       ceild32();
extern _Decimal64       ceild64();
extern _Decimal128      ceild128();
extern _Decimal32       floord32();
extern _Decimal64       floord64();
extern _Decimal128      floord128();
extern _Decimal32       nearbyintd32();
extern _Decimal64       nearbyintd64();
extern _Decimal128      nearbyintd128();
extern _Decimal32       rintd32();
extern _Decimal64       rintd64();
extern _Decimal128      rintd128();
extern long int         lrintd32();
extern long int         lrintd64();
extern long int         lrintd128();
#ifdef _LONG_LONG
extern long long int    llrintd32();
extern long long int    llrintd64();
extern long long int    llrintd128();
#endif
extern _Decimal32       roundd32();
extern _Decimal64       roundd64();
extern _Decimal128      roundd128();
extern long int         lroundd32();
extern long int         lroundd64();
extern long int         lroundd128();
#ifdef _LONG_LONG
extern long long int    llroundd32();
extern long long int    llroundd64();
extern long long int    llroundd128();
#endif
extern _Decimal32       truncd32();
extern _Decimal64       truncd64();
extern _Decimal128      truncd128();
extern _Decimal32       copysignd32();
extern _Decimal64       copysignd64();
extern _Decimal128      copysignd128();
extern _Decimal32       nand32();
extern _Decimal64       nand64();
extern _Decimal128      nand128();
extern _Decimal32       nextafterd32();
extern _Decimal64       nextafterd64();
extern _Decimal128      nextafterd128();
extern _Decimal32       nexttowardd32();
extern _Decimal64       nexttowardd64();
extern _Decimal128      nexttowardd128();
extern _Decimal32       fdimd32();
extern _Decimal64       fdimd64();
extern _Decimal128      fdimd128();
extern _Decimal32       fmaxd32();
extern _Decimal64       fmaxd64();
extern _Decimal128      fmaxd128();
extern _Decimal32       fmind32();
extern _Decimal64       fmind64();
extern _Decimal128      fmind128();
extern _Decimal32       fabsd32();
extern _Decimal64       fabsd64();
extern _Decimal128      fabsd128();
extern _Decimal32       frexpd32();
extern _Decimal64       frexpd64();
extern _Decimal128      frexpd128();
extern int              ilogbd32();
extern int              ilogbd64();
extern int              ilogbd128();
extern _Decimal32       logbd32();
extern _Decimal64       logbd64();
extern _Decimal128      logbd128();
extern _Decimal32       ldexpd32();
extern _Decimal64       ldexpd64();
extern _Decimal128      ldexpd128();
extern _Decimal32       modfd32();
extern _Decimal64       modfd64();
extern _Decimal128      modfd128();
extern _Decimal32       scalbnd32();
extern _Decimal64       scalbnd64();
extern _Decimal128      scalbnd128();
extern _Decimal32       scalblnd32();
extern _Decimal64       scalblnd64();
extern _Decimal128      scalblnd128();
extern _Decimal32       quantized32();
extern _Decimal64       quantized64();
extern _Decimal128      quantized128();
extern __bool__            samequantumd32();
extern __bool__            samequantumd64();
extern __bool__            samequantumd128();
extern _Decimal32       expd32();
extern _Decimal64       expd64();
extern _Decimal128      expd128();
extern _Decimal32       log10d32();
extern _Decimal64       log10d64();
extern _Decimal128      log10d128();
extern _Decimal32       logd32();
extern _Decimal64       logd64();
extern _Decimal128      logd128();
extern _Decimal32       powd32();
extern _Decimal64       powd64();
extern _Decimal128      powd128();
extern _Decimal32       sqrtd32();
extern _Decimal64       sqrtd64();
extern _Decimal128      sqrtd128();
extern _Decimal32       cosd32();
extern _Decimal64       cosd64();
extern _Decimal128      cosd128();
extern _Decimal32       cospid32();
extern _Decimal64       cospid64();
extern _Decimal128      cospid128();
extern _Decimal32       sind32();
extern _Decimal64       sind64();
extern _Decimal128      sind128();
extern _Decimal32       sinpid32();
extern _Decimal64       sinpid64();
extern _Decimal128      sinpid128();
extern _Decimal32       tand32();
extern _Decimal64       tand64();
extern _Decimal128      tand128();
extern _Decimal32       atan2d32();
extern _Decimal64       atan2d64();
extern _Decimal128      atan2d128();
extern _Decimal32       atand32();
extern _Decimal64       atand64();
extern _Decimal128      atand128();
extern _Decimal32       atanpid32();
extern _Decimal64       atanpid64();
extern _Decimal128      atanpid128();
extern _Decimal32       acosd32();
extern _Decimal64       acosd64();
extern _Decimal128      acosd128();
extern _Decimal32       asind32();
extern _Decimal64       asind64();
extern _Decimal128      asind128();
extern _Decimal32       coshd32();
extern _Decimal64       coshd64();
extern _Decimal128      coshd128();
extern _Decimal32       sinhd32();
extern _Decimal64       sinhd64();
extern _Decimal128      sinhd128();
extern _Decimal32       tanhd32();
extern _Decimal64       tanhd64();
extern _Decimal128      tanhd128();
extern _Decimal32       erfcd32();
extern _Decimal64       erfcd64();
extern _Decimal128      erfcd128();
extern _Decimal32       erfd32();
extern _Decimal64       erfd64();
extern _Decimal128      erfd128();
extern _Decimal32       lgammad32();
extern _Decimal64       lgammad64();
extern _Decimal128      lgammad128();
extern _Decimal32       remainderd32();
extern _Decimal64       remainderd64();
extern _Decimal128      remainderd128();
extern _Decimal32       tgammad32();
extern _Decimal64       tgammad64();
extern _Decimal128      tgammad128();
extern _Decimal32       acoshd32();
extern _Decimal64       acoshd64();
extern _Decimal128      acoshd128();
extern _Decimal32       asinhd32();
extern _Decimal64       asinhd64();
extern _Decimal128      asinhd128();
extern _Decimal32       atanhd32();
extern _Decimal64       atanhd64();
extern _Decimal128      atanhd128();
extern _Decimal32       cbrtd32();
extern _Decimal64       cbrtd64();
extern _Decimal128      cbrtd128();
extern _Decimal32       expm1d32();
extern _Decimal64       expm1d64();
extern _Decimal128      expm1d128();
extern _Decimal32       log1pd32();
extern _Decimal64       log1pd64();
extern _Decimal128      log1pd128();
extern _Decimal32       exp2d32();
extern _Decimal64       exp2d64();
extern _Decimal128      exp2d128();
extern _Decimal32       hypotd32();
extern _Decimal64       hypotd64();
extern _Decimal128      hypotd128();
extern _Decimal32       log2d32();
extern _Decimal64       log2d64();
extern _Decimal128      log2d128();
extern _Decimal32       remquod32();
extern _Decimal64       remquod64();
extern _Decimal128      remquod128();
extern _Decimal32       fmodd32();
extern _Decimal64       fmodd64();
extern _Decimal128      fmodd128();
extern _Decimal128      fmad128();

#else /* _NO_PROTO */
extern _Decimal32	ceild32(_Decimal32);
extern _Decimal64	ceild64(_Decimal64);
extern _Decimal128	ceild128(_Decimal128);
extern _Decimal32	floord32(_Decimal32);
extern _Decimal64	floord64(_Decimal64);
extern _Decimal128	floord128(_Decimal128);
extern _Decimal32	nearbyintd32(_Decimal32);
extern _Decimal64	nearbyintd64(_Decimal64);
extern _Decimal128	nearbyintd128(_Decimal128);
extern _Decimal32	rintd32(_Decimal32);
extern _Decimal64	rintd64(_Decimal64);
extern _Decimal128	rintd128(_Decimal128);
extern long int		lrintd32(_Decimal32);
extern long int		lrintd64(_Decimal64);
extern long int		lrintd128(_Decimal128);
#ifdef _LONG_LONG
extern long long int	llrintd32(_Decimal32);
extern long long int	llrintd64(_Decimal64);
extern long long int	llrintd128(_Decimal128);
#endif
extern _Decimal32	roundd32(_Decimal32);
extern _Decimal64	roundd64(_Decimal64);
extern _Decimal128	roundd128(_Decimal128);
extern long int		lroundd32(_Decimal32);
extern long int		lroundd64(_Decimal64);
extern long int		lroundd128(_Decimal128);
#ifdef _LONG_LONG
extern long long int	llroundd32(_Decimal32);
extern long long int	llroundd64(_Decimal64);
extern long long int	llroundd128(_Decimal128);
#endif
extern _Decimal32	truncd32(_Decimal32);
extern _Decimal64	truncd64(_Decimal64);
extern _Decimal128	truncd128(_Decimal128);
extern _Decimal32	copysignd32(_Decimal32, _Decimal32);
extern _Decimal64	copysignd64(_Decimal64, _Decimal64);
extern _Decimal128	copysignd128(_Decimal128, _Decimal128);
extern _Decimal32	nand32(const char *);
extern _Decimal64	nand64(const char *);
extern _Decimal128	nand128(const char *);
extern _Decimal32	nextafterd32(_Decimal32, _Decimal32);
extern _Decimal64	nextafterd64(_Decimal64, _Decimal64);
extern _Decimal128	nextafterd128(_Decimal128, _Decimal128);
extern _Decimal32	nexttowardd32(_Decimal32, _Decimal128);
extern _Decimal64	nexttowardd64(_Decimal64, _Decimal128);
extern _Decimal128	nexttowardd128(_Decimal128, _Decimal128);
extern _Decimal32	fdimd32(_Decimal32, _Decimal32);
extern _Decimal64	fdimd64(_Decimal64, _Decimal64);
extern _Decimal128	fdimd128(_Decimal128, _Decimal128);
extern _Decimal32	fmaxd32(_Decimal32, _Decimal32);
extern _Decimal64	fmaxd64(_Decimal64, _Decimal64);
extern _Decimal128	fmaxd128(_Decimal128, _Decimal128);
extern _Decimal32	fmind32(_Decimal32, _Decimal32);
extern _Decimal64	fmind64(_Decimal64, _Decimal64);
extern _Decimal128	fmind128(_Decimal128, _Decimal128);
extern _Decimal32	fabsd32(_Decimal32);
extern _Decimal64	fabsd64(_Decimal64);
extern _Decimal128	fabsd128(_Decimal128);
extern _Decimal32	frexpd32(_Decimal32, int *);
extern _Decimal64	frexpd64(_Decimal64, int *);
extern _Decimal128	frexpd128(_Decimal128, int *);
extern int		ilogbd32(_Decimal32);
extern int		ilogbd64(_Decimal64);
extern int		ilogbd128(_Decimal128);
extern _Decimal32	logbd32(_Decimal32);
extern _Decimal64	logbd64(_Decimal64);
extern _Decimal128	logbd128(_Decimal128);
extern _Decimal32	ldexpd32(_Decimal32, int);
extern _Decimal64	ldexpd64(_Decimal64, int);
extern _Decimal128	ldexpd128(_Decimal128, int);
extern _Decimal32	modfd32(_Decimal32, _Decimal32 *);
extern _Decimal64	modfd64(_Decimal64, _Decimal64 *);
extern _Decimal128	modfd128(_Decimal128, _Decimal128 *);
extern _Decimal32	scalbnd32(_Decimal32, int);
extern _Decimal64	scalbnd64(_Decimal64, int);
extern _Decimal128	scalbnd128(_Decimal128, int);
extern _Decimal32	scalblnd32(_Decimal32, long int);
extern _Decimal64	scalblnd64(_Decimal64, long int);
extern _Decimal128	scalblnd128(_Decimal128, long int);
extern _Decimal32	quantized32(_Decimal32, _Decimal32);
extern _Decimal64	quantized64(_Decimal64, _Decimal64);
extern _Decimal128	quantized128(_Decimal128, _Decimal128);
extern __bool__		samequantumd32(_Decimal32, _Decimal32);
extern __bool__		samequantumd64(_Decimal64, _Decimal64);
extern __bool__		samequantumd128(_Decimal128, _Decimal128);
extern _Decimal32       expd32(_Decimal32);
extern _Decimal64       expd64(_Decimal64);
extern _Decimal128      expd128(_Decimal128);
extern _Decimal32       log10d32(_Decimal32);
extern _Decimal64       log10d64(_Decimal64);
extern _Decimal128      log10d128(_Decimal128);
extern _Decimal32       logd32(_Decimal32);
extern _Decimal64       logd64(_Decimal64);
extern _Decimal128      logd128(_Decimal128);
extern _Decimal32       powd32(_Decimal32, _Decimal32);
extern _Decimal64       powd64(_Decimal64, _Decimal64);
extern _Decimal128      powd128(_Decimal128, _Decimal128);
extern _Decimal32       sqrtd32(_Decimal32);
extern _Decimal64       sqrtd64(_Decimal64);
extern _Decimal128      sqrtd128(_Decimal128);
extern _Decimal32       cosd32(_Decimal32);
extern _Decimal64       cosd64(_Decimal64);
extern _Decimal128      cosd128(_Decimal128);
extern _Decimal32       cospid32(_Decimal32);
extern _Decimal64       cospid64(_Decimal64);
extern _Decimal128      cospid128(_Decimal128);
extern _Decimal32       sind32(_Decimal32);
extern _Decimal64       sind64(_Decimal64);
extern _Decimal128      sind128(_Decimal128);
extern _Decimal32       sinpid32(_Decimal32);
extern _Decimal64       sinpid64(_Decimal64);
extern _Decimal128      sinpid128(_Decimal128);
extern _Decimal32       tand32(_Decimal32);
extern _Decimal64       tand64(_Decimal64);
extern _Decimal128      tand128(_Decimal128);
extern _Decimal32       atan2d32(_Decimal32, _Decimal32);
extern _Decimal64       atan2d64(_Decimal64, _Decimal64);
extern _Decimal128      atan2d128(_Decimal128, _Decimal128);
extern _Decimal32       atand32(_Decimal32);
extern _Decimal64       atand64(_Decimal64);
extern _Decimal128      atand128(_Decimal128);
extern _Decimal32       atanpid32(_Decimal32);
extern _Decimal64       atanpid64(_Decimal64);
extern _Decimal128      atanpid128(_Decimal128);
extern _Decimal32       acosd32(_Decimal32);
extern _Decimal64       acosd64(_Decimal64);
extern _Decimal128      acosd128(_Decimal128);
extern _Decimal32       asind32(_Decimal32);
extern _Decimal64       asind64(_Decimal64);
extern _Decimal128      asind128(_Decimal128);
extern _Decimal32       coshd32(_Decimal32);
extern _Decimal64       coshd64(_Decimal64);
extern _Decimal128      coshd128(_Decimal128);
extern _Decimal32       sinhd32(_Decimal32);
extern _Decimal64       sinhd64(_Decimal64);
extern _Decimal128      sinhd128(_Decimal128);
extern _Decimal32       tanhd32(_Decimal32);
extern _Decimal64       tanhd64(_Decimal64);
extern _Decimal128      tanhd128(_Decimal128);
extern _Decimal32       erfcd32(_Decimal32);
extern _Decimal64       erfcd64(_Decimal64);
extern _Decimal128      erfcd128(_Decimal128);
extern _Decimal32       erfd32(_Decimal32);
extern _Decimal64       erfd64(_Decimal64);
extern _Decimal128      erfd128(_Decimal128);
extern _Decimal32       lgammad32(_Decimal32);
extern _Decimal64       lgammad64(_Decimal64);
extern _Decimal128      lgammad128(_Decimal128);
extern _Decimal32       remainderd32(_Decimal32, _Decimal32);
extern _Decimal64       remainderd64(_Decimal64, _Decimal64);
extern _Decimal128      remainderd128(_Decimal128, _Decimal128);
extern _Decimal32       tgammad32(_Decimal32);
extern _Decimal64       tgammad64(_Decimal64);
extern _Decimal128      tgammad128(_Decimal128);
extern _Decimal32       acoshd32(_Decimal32);
extern _Decimal64       acoshd64(_Decimal64);
extern _Decimal128      acoshd128(_Decimal128);
extern _Decimal32       asinhd32(_Decimal32);
extern _Decimal64       asinhd64(_Decimal64);
extern _Decimal128      asinhd128(_Decimal128);
extern _Decimal32       atanhd32(_Decimal32);
extern _Decimal64       atanhd64(_Decimal64);
extern _Decimal128      atanhd128(_Decimal128);
extern _Decimal32       cbrtd32(_Decimal32);
extern _Decimal64       cbrtd64(_Decimal64);
extern _Decimal128      cbrtd128(_Decimal128);
extern _Decimal32       expm1d32(_Decimal32);
extern _Decimal64       expm1d64(_Decimal64);
extern _Decimal128      expm1d128(_Decimal128);
extern _Decimal32       log1pd32(_Decimal32);
extern _Decimal64       log1pd64(_Decimal64);
extern _Decimal128      log1pd128(_Decimal128);
extern _Decimal32       exp2d32(_Decimal32);
extern _Decimal64       exp2d64(_Decimal64);
extern _Decimal128      exp2d128(_Decimal128);
extern _Decimal32       hypotd32(_Decimal32, _Decimal32);
extern _Decimal64       hypotd64(_Decimal64, _Decimal64);
extern _Decimal128      hypotd128(_Decimal128, _Decimal128);
extern _Decimal32       log2d32(_Decimal32);
extern _Decimal64       log2d64(_Decimal64);
extern _Decimal128      log2d128(_Decimal128);
extern _Decimal32       remquod32(_Decimal32, _Decimal32, int*);
extern _Decimal64       remquod64(_Decimal64, _Decimal64, int*);
extern _Decimal128      remquod128(_Decimal128, _Decimal128, int*);
extern _Decimal32       fmodd32(_Decimal32, _Decimal32);
extern _Decimal64       fmodd64(_Decimal64, _Decimal64);
extern _Decimal128      fmodd128(_Decimal128, _Decimal128);
extern _Decimal128      fmad128(_Decimal128, _Decimal128, _Decimal128);

#endif /* _NO_PROTO */

#endif /* __STDC_WANT_DEC_FP__ */

#ifdef __cplusplus
}
#endif

#endif /*_H_MATH */
