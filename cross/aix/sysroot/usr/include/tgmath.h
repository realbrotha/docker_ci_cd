/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/tgmath.h 1.3                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2002               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)74  1.3  src/bos/usr/include/tgmath.h, libm, bos530 9/6/02 16:37:53 */

/*
 * COMPONENT_NAME: (INCSTD) Standard Include Files
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 2002
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


#ifndef _H_TGMATH
#define _H_TGMATH 1

#include <standards.h>
#include <complex.h>
#include <math.h>


#undef acos
#undef acosh
#undef asin
#undef asinh
#undef atan
#undef atan2
#undef atanh
#undef carg
#undef cbrt
#undef ceil
#undef cimag
#undef conj
#undef copysign
#undef cos
#undef cosh
#undef cproj
#undef creal
#undef erf
#undef erfc
#undef exp
#undef exp2
#undef expm1
#undef fabs
#undef fdim
#undef floor
#undef fma
#undef fmax
#undef fmin
#undef fmod
#undef frexp
#undef hypot
#undef ilogb
#undef ldexp
#undef lgamma
#undef llrint
#undef llround
#undef log
#undef log10
#undef log1p
#undef log2
#undef logb
#undef lrint
#undef lround
#undef nearbyint
#undef nextafter
#undef nexttoward
#undef pow
#undef remainder
#undef remquo
#undef rint
#undef round
#undef scalbln
#undef scalbn
#undef sin
#undef sinh
#undef sqrt
#undef tan
#undef tanh
#undef tgamma
#undef trunc

#ifdef __IBMC__
/* Functions from math.h and complex.h */
#define acos(__x)            __tg_builtin("acos", __x)
#define asin(__x)            __tg_builtin("asin", __x)
#define atan(__x)            __tg_builtin("atan", __x)
#define acosh(__x)           __tg_builtin("acosh", __x)
#define asinh(__x)           __tg_builtin("asinh", __x)
#define atanh(__x)           __tg_builtin("atanh", __x)
#define cos(__x)             __tg_builtin("cos", __x)
#define sin(__x)             __tg_builtin("sin", __x)
#define tan(__x)             __tg_builtin("tan", __x)
#define cosh(__x)            __tg_builtin("cosh", __x)
#define sinh(__x)            __tg_builtin("sinh", __x)
#define tanh(__x)            __tg_builtin("tanh", __x)
#define exp(__x)             __tg_builtin("exp", __x)
#define log(__x)             __tg_builtin("log", __x)
#define pow(__x, __y)        __tg_builtin("pow", __x, __y)
#define sqrt(__x)            __tg_builtin("sqrt", __x)
#define fabs(__x)            __tg_builtin("fabs", __x)

/* Functions from math.h only */
#define atan2(__x, __y)      __tg_builtin("atan2", __x, __y)
#define cbrt(__x)            __tg_builtin("cbrt", __x)
#define ceil(__x)            __tg_builtin("ceil", __x)
#define copysign(__x, __y)   __tg_builtin("copysign", __x, __y)
#define erf(__x)             __tg_builtin("erf", __x)
#define erfc(__x)            __tg_builtin("erfc", __x)
#define exp2(__x)            __tg_builtin("exp2", __x)
#define expm1(__x)           __tg_builtin("expm1", __x)
#define fdim(__x, __y)       __tg_builtin("fdim", __x, __y)
#define floor(__x)           __tg_builtin("floor", __x)
#define fma(__x, __y, __z)   __tg_builtin("fma", __x, __y, __z)
#define fmax(__x, __y)       __tg_builtin("fmax", __x, __y)
#define fmin(__x, __y)       __tg_builtin("fmin", __x, __y)
#define fmod(__x, __y)       __tg_builtin("fmod", __x, __y)
#define frexp(__x, __y)      __tg_builtin("frexp", __x, __y)
#define hypot(__x, __y)      __tg_builtin("hypot", __x, __y)
#define ilogb(__x)           __tg_builtin("ilogb", __x)
#define ldexp(__x, __y)      __tg_builtin("ldexp", __x, __y)
#define lgamma(__x)          __tg_builtin("lgamma", __x)
#define llrint(__x)          __tg_builtin("llrint", __x)
#define llround(__x)         __tg_builtin("llround", __x)
#define log10(__x)           __tg_builtin("log10", __x)
#define log1p(__x)           __tg_builtin("log1p", __x)
#define log2(__x)            __tg_builtin("log2", __x)
#define logb(__x)            __tg_builtin("logb", __x)
#define lrint(__x)           __tg_builtin("lrint", __x)
#define lround(__x)          __tg_builtin("lround", __x)
#define nearbyint(__x)       __tg_builtin("nearbyint", __x)
#define nextafter(__x, __y)  __tg_builtin("nextafter", __x, __y)
#define nexttoward(__x, __y) __tg_builtin("nexttoward", __x, __y)
#define remainder(__x, __y)  __tg_builtin("remainder", __x, __y)
#define remquo(__x,__y,__z)  __tg_builtin("remquo", __x, __y, __z)
#define rint(__x)            __tg_builtin("rint", __x)
#define round(__x)           __tg_builtin("round", __x)
#define scalbn(__x, __y)     __tg_builtin("scalbn", __x, __y)
#define scalbln(__x, __y)    __tg_builtin("scalbln", __x, __y)
#define tgamma(__x)          __tg_builtin("tgamma", __x)
#define trunc(__x)           __tg_builtin("trunc", __x)

/* Functions from complex.h only */
#define carg(__x)            __tg_builtin("carg", __x)
#define cimag(__x)           __tg_builtin("cimag", __x)
#define conj(__x)            __tg_builtin("conj", __x)
#define cproj(__x)           __tg_builtin("cproj", __x)
#define creal(__x)           __tg_builtin("creal", __x)

#endif




#endif /* tgmath.h */
