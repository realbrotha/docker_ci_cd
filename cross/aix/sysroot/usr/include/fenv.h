/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/usr/include/fenv.h 1.6.1.3                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2002,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)73  1.6.1.3  src/bos/usr/include/fenv.h, libm, bos53Q, q2007_49A7 11/2/07 14:43:06 */

#ifndef _H_FENV
#define _H_FENV

#ifndef _H_STANDARDS
#include <standards.h>
#endif

/*
 * These definitions and interfaces are the standard versions of the
 * definitions and interfaces from <fpxcp.h>.
 */

typedef unsigned int fexcept_t;  /* Same as fpflag_t */

typedef struct {
#ifdef _ALL_SOURCE
    unsigned short rmode; /* Floating point rounding mode */
    unsigned int fpstat;	/* Floating point status register */
    unsigned int trapstate; /* Trapping mode */
    unsigned int reserved1; /* Future use */
    unsigned int reserved2; /* Future use */
#else
    /*
     * These identifiers need to conform to the SUSv3 rules of an 
     * implementation defined type.
     */
    unsigned short __rmode; /* Floating point rounding mode */
    unsigned int __fpstat;        /* Floating point status register */
    unsigned int __trapstate; /* Trapping mode */
    unsigned int __reserved1; /* Future use */
    unsigned int __reserved2; /* Future use */
#endif /* _ALL_SOURCE */
    
} fenv_t;

#define FE_DIVBYZERO	0x04000000U
#define FE_INEXACT	0x02000000U
#define FE_INVALID	0x20000000U
#define FE_OVERFLOW	0x10000000U
#define FE_UNDERFLOW	0x08000000U
#define FE_ALL_EXCEPT   0x3E000000U

#define FE_DOWNWARD	3
#define FE_TONEAREST	1
#define FE_TOWARDZERO   0
#define FE_UPWARD	2

const fenv_t __fe_def_env = { FE_TONEAREST, 0, 0, 0, 0 };
#define FE_DFL_ENV 	(&__fe_def_env)

extern int feclearexcept(int);
extern int fegetexceptflag(fexcept_t *, int);
extern int feraiseexcept(int);
extern int fesetexceptflag(const fexcept_t *, int);
extern int fetestexcept(int);
extern int fegetround(void);
extern int fesetround(int);
extern int fegetenv(fenv_t *);
extern int feholdexcept(fenv_t *);
extern int fesetenv(const fenv_t *);
extern int feupdateenv(const fenv_t *);

/*
 *  This section is for Decimal Floating Point (DFP) items.
 *  DFP support is only present if __STDC_WANT_DEC_FP__ is defined.
 */
#ifdef __STDC_WANT_DEC_FP__     /* DFP scope requested */

/* DFP rounding modes */
#define FE_DEC_TONEAREST		0
#define FE_DEC_TOWARDZERO		1
#define FE_DEC_UPWARD			2
#define FE_DEC_DOWNWARD			3
#define FE_DEC_TONEARESTFROMZERO	4
#define FE_DEC_TONEARESTTOWARDZERO	5
#define FE_DEC_AWAYFROMZERO		6
#define FE_DEC_SHORTERPRECISION		7

#ifdef _NO_PROTO
	extern int fe_dec_getround();
	extern int fe_dec_setround();
#else
	extern int fe_dec_getround(void);
	extern int fe_dec_setround(int);
#endif

#endif /* __STDC_WANT_DEC_FP__ */

#endif /* _H_FENV */
