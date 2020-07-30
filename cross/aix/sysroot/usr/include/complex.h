/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/complex.h 1.2                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2002,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)75  1.2  src/bos/usr/include/complex.h, libm, bos530 2/6/04 15:46:53 */

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


#ifndef _H_COMPLEX
#define _H_COMPLEX	1

#include <standards.h>

#ifdef __cplusplus
extern "C" {
#endif


#define complex		_Complex

/* 
 * a constant expression of type const float _Complex with the
 * value of the imaginary unit. (a number i such that i**2 =-1).
 * __I is provided by the AIX xlc C99 compiler.
 * WARNING: DO NOT USE __I DIRECTLY in an application. Always
 * use _Complex_I .
 */
#define _Complex_I	__I

/*
 * _Imaginary_I should be a constant expression of type
 * const float _Imaginary with the value of the imaginary unit.
 * This is optional in C99.
 * This is not supported in the AIX xlc C99 compiler.
 */

/* 
 * C99 requires this definition of the
 * very common variable "I", to use as a simpler way
 * to say _Complex_I. Mathematicians who would say
 * "3i" will now say in C "3 * I".
 */
#undef I
#define I _Complex_I


extern  double              cabs(double complex);
extern  float               cabsf(float complex);
extern  double complex      cacos(double complex);
extern  float complex       cacosf(float complex);
extern  double complex      cacosh(double complex);
extern  float complex       cacoshf(float complex);
extern  double              carg(double complex);
extern  float               cargf(float complex);
extern  double complex      casin(double complex);
extern  float complex       casinf(float complex);
extern  double complex      casinh(double complex);
extern  float complex       casinhf(float complex);
extern  double complex      catan(double complex);
extern  float complex       catanf(float complex);
extern  double complex      catanh(double complex);
extern  float complex       catanhf(float complex);
extern  double complex      ccos(double complex);
extern  float complex       ccosf(float complex);
extern  double complex      ccosh(double complex);
extern  float complex       ccoshf(float complex);
extern  double complex      cexp(double complex);
extern  float complex       cexpf(float complex);
extern  double              cimag(double complex);
extern  float               cimagf(float complex);
extern  double complex      __clog(double complex);
extern  float complex       clogf(float complex);
extern  double complex      conj(double complex);
extern  float complex       conjf(float complex);
extern  double complex      cpow(double complex, double complex);
extern  float complex       cpowf(float complex, float complex);
extern  double complex      cproj(double complex);
extern  float complex       cprojf(float complex);
extern  double              creal(double complex);
extern  float               crealf(float complex);
extern  double complex      csin(double complex);
extern  float complex       csinf(float complex);
extern  double complex      csinh(double complex);
extern  float complex       csinhf(float complex);
extern  double complex      csqrt(double complex);
extern  float complex       csqrtf(float complex);
extern  double complex      ctan(double complex);
extern  float complex       ctanf(float complex);
extern  double complex      ctanh(double complex);
extern  float complex       ctanhf(float complex);

/*
 * There are two forms of long double on AIX.  The default
 * form of long double is the same as a double - 64 bits.  There
 * is a 128-bit form available with some compilers.  If that compiler
 * defines __LONGDOUBLE128, then long doubles are 128-bit instead of
 * 64-bit.  Since the same library routine cannot be used for 128-bit
 * and 64-bit values, the 128-bit routines are renamed and macros are
 * used to manage the name spaces.  It is not necessarily the case that
 * all of the 128-bit versions are available, but the macros are defined
 * intentionally since the 64-bit versions can provide incorrect results
 * when long double values were expected.  If 64-bit versions are required
 * in 128-bit mode, then the code needs to invoke the double routines a
 * rather than the long double routines.
 */

#ifdef __LONGDOUBLE128
/* 64-bit long double routines */
extern  double         cabsl(double complex);
extern  double complex cacoshl(double complex);
extern  double complex cacosl(double complex);
extern  double         cargl(double complex);
extern  double complex casinhl(double complex);
extern  double complex casinl(double complex);
extern  double complex catanhl(double complex);
extern  double complex catanl(double complex);
extern  double complex ccoshl(double complex);
extern  double complex ccosl(double complex);
extern  double complex cexpl(double complex);
extern  double         cimagl(double complex);
extern  double complex clogl(double complex);
extern  double complex conjl(double complex);
extern  double complex cpowl(double complex, double complex);
extern  double complex cprojl(double complex);
extern  double         creall(double complex);
extern  double complex csinhl(double complex);
extern  double complex csinl(double complex);
extern  double complex csqrtl(double complex);
extern  double complex ctanhl(double complex);
extern  double complex ctanl(double complex);

/* 128-bit routines */
#define cabsl(__ldc1) __cabsl128(__ldc1)
#define cacoshl(__ldc1) __cacoshl128(__ldc1)
#define cacosl(__ldc1) __cacosl128(__ldc1)
#define cargl(__ldc1) __cargl128(__ldc1)
#define casinhl(__ldc1) __casinhl128(__ldc1)
#define casinl(__ldc1) __casinl128(__ldc1)
#define catanhl(__ldc1) __catanhl128(__ldc1)
#define catanl(__ldc1) __catanl128(__ldc1)
#define ccoshl(__ldc1) __ccoshl128(__ldc1)
#define ccosl(__ldc1) __ccosl128(__ldc1)
#define cexpl(__ldc1) __cexpl128(__ldc1)
#define cimagl(__ldc1) __cimagl128(__ldc1)
#define clogl(__ldc1) __clogl128(__ldc1)
#define conjl(__ldc1) __conjl128(__ldc1)
#define cpowl(__ldc1, __ldc2) __cpowl128(__ldc1, __ldc2)
#define cprojl(__ldc1) __cprojl128(__ldc1)
#define creall(__ldc1) __creall128(__ldc1)
#define csinhl(__ldc1) __csinhl128(__ldc1)
#define csinl(__ldc1) __csinl128(__ldc1)
#define csqrtl(__ldc1) __csqrtl128(__ldc1)
#define ctanhl(__ldc1) __ctanhl128(__ldc1)
#define ctanl(__ldc1) __ctanl128(__ldc1)

extern  long double         __cabsl128(long double complex);
extern  long double complex __cacoshl128(long double complex);
extern  long double complex __cacosl128(long double complex);
extern  long double         __cargl128(long double complex);
extern  long double complex __casinhl128(long double complex);
extern  long double complex __casinl128(long double complex);
extern  long double complex __catanhl128(long double complex);
extern  long double complex __catanl128(long double complex);
extern  long double complex __ccoshl128(long double complex);
extern  long double complex __ccosl128(long double complex);
extern  long double complex __cexpl128(long double complex);
extern  long double         __cimagl128(long double complex);
extern  long double complex __clogl128(long double complex);
extern  long double complex __conjl128(long double complex);
extern  long double complex __cpowl128(long double complex, long double complex);
extern  long double complex __cprojl128(long double complex);
extern  long double         __creall128(long double complex);
extern  long double complex __csinhl128(long double complex);
extern  long double complex __csinl128(long double complex);
extern  long double complex __csqrtl128(long double complex);
extern  long double complex __ctanhl128(long double complex);
extern  long double complex __ctanl128(long double complex);
#else
extern  long double         cabsl(long double complex);
extern  long double complex cacoshl(long double complex);
extern  long double complex cacosl(long double complex);
extern  long double         cargl(long double complex);
extern  long double complex casinhl(long double complex);
extern  long double complex casinl(long double complex);
extern  long double complex catanhl(long double complex);
extern  long double complex catanl(long double complex);
extern  long double complex ccoshl(long double complex);
extern  long double complex ccosl(long double complex);
extern  long double complex cexpl(long double complex);
extern  long double         cimagl(long double complex);
extern  long double complex clogl(long double complex);
extern  long double complex conjl(long double complex);
extern  long double complex cpowl(long double complex, long double complex);
extern  long double complex cprojl(long double complex);
extern  long double         creall(long double complex);
extern  long double complex csinhl(long double complex);
extern  long double complex csinl(long double complex);
extern  long double complex csqrtl(long double complex);
extern  long double complex ctanhl(long double complex);
extern  long double complex ctanl(long double complex);
#endif

#if __IBMC__ || __IBMCPP__

    extern double complex clog(double complex);
    #pragma map(clog, "__clog")             /* maps clog to __clog */

#else

    static double complex clog(double complex z)
    {
        return (__clog(z));
    }

#endif

#ifdef __cplusplus
}
#endif

#endif /* complex.h */
