/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/usr/include/float.h 1.33                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)87       1.33  src/bos/usr/include/float.h, sysfp, bos53L, l2007_16B2 4/18/07 00:37:50 */
/*
 * COMPONENT_NAME: (SYSFP) floating point header file
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

#ifndef _H_FLOAT
#define _H_FLOAT

#ifndef _H_STANDARDS
#include <standards.h>
#endif

/*
 *  Only a subset of the values in this header are required
 *  by the ANSI standard. The values not required will not be
 *  included if _ANSI_C_SOURCE is defined (for strict conformance).
 *
 *  ANSI required:
 *
 *      FLT_ROUNDS      Macro that returns current rounding mode value
 *      FLT_RADIX       Exponent radix
 *
 *               Values for "float" numbers
 *
 *      FLT_MANT_DIG    Number of bits in the significand
 *      FLT_EPSILON     1ulp when exponent = 0
 *      FLT_DIG         Number of decimal digits of precision
 *      FLT_MIN_EXP     Exponent of smallest NORMALIZED float number
 *      FLT_MIN         Smallest NORMALIZED float number
 *      FLT_MIN_10_EXP  Minimum base 10 exponent of NORMALIZED float
 *      FLT_MAX_EXP     Exponent of largest NORMALIZED float number
 *      FLT_MAX         Largest NORMALIZED float number
 *      FLT_MAX_10_EXP  Largest base 10 exponent of NORMALIZED float
 *
 *               Values for "double" numbers
 *
 *      DBL_MANT_DIG    Number of bits in the significand
 *      DBL_EPSILON     1ulp when exponent = 0
 *      DBL_DIG         Number of decimal digits of precision
 *      DBL_MIN_EXP     Exponent of smallest NORMALIZED double number
 *      DBL_MIN         Smallest NORMALIZED double number
 *      DBL_MIN_10_EXP  Minimum base 10 exponent of NORMALIZED double
 *      DBL_MAX_EXP     Exponent of largest NORMALIZED double number
 *      DBL_MAX         Largest NORMALIZED double number
 *      DBL_MAX_10_EXP  Largest base 10 exponent of NORMALIZED double
 *
 *                Values for "long double" numbers
 *
 *      LDBL_MANT_DIG   Number of bits in the significand
 *      LDBL_EPSILON    1ulp when unbiased exponent = 0
 *      LDBL_DIG        Number of decimal digits of precision
 *      LDBL_MIN_EXP    Exponent of smallest NORMALIZED long double number
 *      LDBL_MIN        Smallest NORMALIZED long double number
 *      LDBL_MIN_10_EX  Minimum base 10 exponent of NORMALIZED long double
 *      LDBL_MAX_EXP    Exponent of largest NORMALIZED long double number
 *      LDBL_MAX        Largest NORMALIZED long double number
 *      LDBL_MAX_10_EXP Largest base 10 exponent of NORMALIZED long double
 *
 *  Not required for ANSI compatibility:
 *
 *      FLT_INFINITY    Float Infinity
 *      DBL_INFINITY    Double Infinity
 *      LDBL_INFINITY   Long Double Infinity
 *      DBL_QNAN        Double QNaN
 *      FLT_QNAN        Float QNaN
 *      DBL_SNAN        Double SNaN
 *      FLT_SNAN        Float SNaN
 *      FP_RND_xx       Floating Point Rounding Mode Constants
 *      FP_xx           Floating Point Class Function Return Values
 *
 */

#ifdef _ANSI_C_SOURCE

#ifndef FLT_MAX
#define FLT_MAX	    3.4028234663852886e+38F   /* max decimal value of a float */
#endif

#ifndef FLT_MIN
#define FLT_MIN	    1.1754943508222875e-38F   /* min decimal value of a float */
#endif

#ifndef FLT_DIG
#define FLT_DIG		6
#endif

#ifndef DBL_MAX
#define DBL_MAX	    1.7976931348623158e+308  /* max decimal value of a double */
#endif

#ifndef DBL_MIN
#define DBL_MIN     2.2250738585072014e-308
#endif

#ifndef DBL_DIG
#define DBL_DIG		15
#endif


/*
 *      General definitions
 */

#define FLT_ROUNDS         ( fp_read_rnd() )
#define FLT_RADIX          2

#ifdef _ISOC99_SOURCE
#define FLT_EVAL_METHOD  1
#endif

/*
 *      Float definitions
 */

#define FLT_MANT_DIG       24
#define FLT_EPSILON	   1.1920928955078125e-7F
#define FLT_MIN_EXP        -125
#define FLT_MIN_10_EXP     -37
#define FLT_MAX_EXP        128
#define FLT_MAX_10_EXP     38

/*
 *      Double definitions
 */

#define DBL_MANT_DIG       53
#define DBL_EPSILON	   2.2204460492503131e-16
#define DBL_MIN_EXP        -1021
#define DBL_MIN_10_EXP     -307
#define DBL_MAX_EXP        1024
#define DBL_MAX_10_EXP     308

/*
 * Long Double definitions
 *
 * On POWER:
 *      By default long double is the same as double (64 bits).
 *      An optional mode with 128-bit long double is available,
 *      and when this mode is in effect the compiler will define
 *      __LONGDOUBLE128.
 *
 * On IA64:
 *      Only 80bit long double is currenlty supported, and the compiler
 *      will define __LONGDOUBLE80.
 */

#ifdef __LONGDOUBLE128

/* POWER 128 bit long double */
#define LDBL_MANT_DIG      106
#define LDBL_EPSILON	   0.24651903288156618919116517665087070E-31L
#define LDBL_DIG           31
#define LDBL_MIN_EXP       DBL_MIN_EXP
#define LDBL_MIN           ((long double) DBL_MIN)
#define LDBL_MIN_10_EXP    DBL_MIN_10_EXP
#define LDBL_MAX_EXP       DBL_MAX_EXP
#define LDBL_MAX           0.1797693134862315807937289714053023E+309L
#define LDBL_MAX_10_EXP    DBL_MAX_10_EXP

#elif defined(__LONGDOUBLE80)

/* IA64 80 bit long double */
#define LDBL_MANT_DIG      64
#define LDBL_EPSILON	   1.0842021724855044340075E-19L
#define LDBL_DIG           18
#define LDBL_MIN_EXP       (-16381)
#define LDBL_MIN           3.36210314311209350626e-4932L
#define LDBL_MIN_10_EXP    (-4931)
#define LDBL_MAX_EXP       16384
#define LDBL_MAX           1.18973149535723176502e+4932L
#define LDBL_MAX_10_EXP    4932

#else 

/* default 64 bit long double */
#define LDBL_MANT_DIG      DBL_MANT_DIG
#define LDBL_EPSILON       DBL_EPSILON
#define LDBL_DIG           DBL_DIG
#define LDBL_MIN_EXP       DBL_MIN_EXP
#define LDBL_MIN           DBL_MIN
#define LDBL_MIN_10_EXP    DBL_MIN_10_EXP
#define LDBL_MAX_EXP       DBL_MAX_EXP
#define LDBL_MAX           DBL_MAX
#define LDBL_MAX_10_EXP    DBL_MAX_10_EXP

#endif /* __LONGDOUBLE128 */

#ifdef _ISOC99_SOURCE
#define DECIMAL_DIG        17
#endif


#endif /* ANSI_C_SOURCE */

/* ******************************************************************
 *
 *      Non-ANSI definitions. The "old" definitions must be strict
 *      constants.
 */

#ifdef _ALL_SOURCE

#ifndef _H_LIMITS
#include <sys/limits.h>
#endif

#define DINFINITY _DBLINF

	extern  unsigned   int SINFINITY;
	extern  unsigned   int _DBLINF[2];
	extern  unsigned   int SQNAN;
	extern  unsigned   int DQNAN[2];
	extern  unsigned   int SSNAN;
	extern  unsigned   int DSNAN[2];

#define FLT_INFINITY	(*((float *) (&SINFINITY)))
#define DBL_INFINITY	(*((double *) (_DBLINF)))
#define LDBL_INFINITY	DBL_INFINITY
#define FLT_QNAN 	(*((float *) (&SQNAN)))
#define DBL_QNAN	(*((double *) (DQNAN)))
#define FLT_SNAN	(*((float *) (&SSNAN)))
#define DBL_SNAN	(*((double *) (DSNAN)))


/*
 *
 *      Values for the IEEE Rounding Modes (ANSI Encoding)
 *
 *      RZ = Round toward zero
 *      RN = Round toward nearest (default)
 *      RP = Round toward plus infinity
 *      RM = Round toward minus infinity
 *
 */
#define FP_RND_RZ       0
#define FP_RND_RN       1
#define FP_RND_RP       2
#define FP_RND_RM       3

typedef	unsigned short fprnd_t;

#ifdef _NO_PROTO

fprnd_t fp_read_rnd();
fprnd_t fp_swap_rnd();

#else

fprnd_t fp_read_rnd(void);
fprnd_t fp_swap_rnd(fprnd_t rnd);

#endif


/*
 *
 *      Floating Point Class Function Return Values
 *
 *      These are the values returned by the class function.
 *      The class function is one of the recommended functions in the
 *      IEEE standard.
 *
 */

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


/******************************************************************************
 *  This section is for Decimal Floating Point (DFP) items.
 *  DFP support is only present if __STDC_WANT_DEC_FP__ is defined.
 *****************************************************************************/
#ifdef __STDC_WANT_DEC_FP__

/*
 *  For the values defined here:
 *  A prefix of DEC32_ indicates a type of _Decimal32.
 *  A prefix of DEC64_ indicates a type of _Decimal64.
 *  A prefix of DEC128_ indicates a type of _Decimal128.
 *
 *  MANT_DIG  specifies the number of digits in the coefficient
 *  MIN_EXP   specifies the minimum exponent value
 *  MAX_EXP   specifies the maximum exponent value
 *  MAX       specifies the maximum finite value that can be represented
 *  EPSILON   specifies the epsilon, the least value greater than 1
 *            that can be represented
 *  MIN       specifies the minimum normalized positive value
 *  DEN       specifies the minimum denormalized positive value
 */

/* Constant values relevant to the _Decimal32 floating point data type */
#define DEC32_MANT_DIG	7
#define DEC32_MIN_EXP	-95
#define DEC32_MAX_EXP	96
#define DEC32_MAX	9.999999E96DF
#define DEC32_EPSILON	1E-6DF
#define DEC32_MIN	1E-95DF
#define DEC32_DEN	0.000001E-95DF

/* Constant values relevant to the _Decimal64 floating point data type */
#define DEC64_MANT_DIG	16
#define DEC64_MIN_EXP	-383
#define DEC64_MAX_EXP	384
#define DEC64_MAX	9.999999999999999E384DD
#define DEC64_EPSILON	1E-15DD
#define DEC64_MIN	1E-383DD
#define DEC64_DEN	0.000000000000001E-383DD

/* Constant values relevant to the _Decimal128 floating point data type */
#define DEC128_MANT_DIG	34
#define DEC128_MIN_EXP	-6143
#define DEC128_MAX_EXP	6144
#define DEC128_MAX	9.999999999999999999999999999999999E6144DL
#define DEC128_EPSILON	1E-33DL
#define DEC128_MIN	1E-6143DL
#define DEC128_DEN	0.000000000000000000000000000000001E-6143DL

#ifdef __DEC_EVAL_METHOD__
#define DEC_EVAL_METHOD __DEC_EVAL_METHOD__
#else
#define DEC_EVAL_METHOD -1
#endif

#endif /* __STDC_WANT_DEC_FP__ */


#endif /* ALL_SOURCE */
#endif /* _H_FLOAT */

