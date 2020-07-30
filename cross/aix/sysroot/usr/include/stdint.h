/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53A src/bos/kernel/sys/stdint.h 1.10                                */
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
/* @(#)09     1.10  src/bos/kernel/sys/stdint.h, incstd, bos53A, a2004_31E1 7/21/04 18:53:26 */
/*
 *   COMPONENT_NAME: incstd
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 */

#ifndef _H_STDINT
#ifndef _STD_TYPES_T
#define	_H_STDINT
#endif /*  _STD_TYPES_T */

#include <standards.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ANSI_C_SOURCE
	
#ifndef _H_STDINT_TYPE_TS
/*
 * Basic / Extended integer types
 *
 * The following defines the basic fixed-size integer types.
 *
 */
typedef signed char		int8_t;
typedef signed short		int16_t;
typedef signed int		int32_t;
#ifdef	__64BIT__
typedef signed long		int64_t;
#else	/* _ILP32 */
#if defined(_LONG_LONG)
typedef	signed long long	int64_t;
#endif
#endif

typedef unsigned char		uint8_t;
typedef unsigned short		uint16_t;
typedef unsigned int		uint32_t;
#ifndef _STD_UINT64_T
#ifdef	__64BIT__
typedef unsigned long		uint64_t;
#else	/* _ILP32 */
#if defined(_LONG_LONG)
typedef unsigned long long	uint64_t;
#endif
#endif
#endif /* _STD_UINT64_T */

/*
 * intmax_t and uintmax_t are to be the longest (in number of bits) signed
 * and unsigned integer types supported by the implementation.
 */
#if ( __64BIT__ || defined(_LONG_LONG) )
typedef int64_t			intmax_t;
typedef uint64_t		uintmax_t;
#else
typedef int32_t			intmax_t;
typedef uint32_t		uintmax_t;
#endif

/*
 * intptr_t and uintptr_t are signed and unsigned integer types large enough
 * to hold any data pointer; that is, data pointers can be assigned into or
 * from these integer types without losing precision.
 */
typedef signed long		intptr_t;
typedef unsigned long		uintptr_t;

/*
 * The following define the smallest integer types that can hold the
 * specified number of bits.
 */
typedef signed char		int_least8_t;
typedef signed short		int_least16_t;
typedef signed int		int_least32_t;
#ifdef	__64BIT__
typedef signed long		int_least64_t;
#else	/* _ILP32 */
#if defined(_LONG_LONG)
typedef signed long long	int_least64_t;
#endif
#endif

typedef unsigned char		uint_least8_t;
typedef unsigned short		uint_least16_t;
typedef unsigned int		uint_least32_t;
#ifdef	__64BIT__
typedef unsigned long		uint_least64_t;
#else	/* _ILP32 */
#if defined(_LONG_LONG)
typedef unsigned long long	uint_least64_t;
#endif
#endif
#endif /* _H_STDINT_TYPE_TS */

#ifdef _ISOC99_SOURCE 
/* New typedef's and define's for ISO-c99 standard not a part of c89 */

#ifndef _H_STDINT_TYPE_TS
/* Most efficient types of N or more bytes */
typedef signed char	int_fast8_t;
typedef int16_t		int_fast16_t;
typedef int32_t		int_fast32_t;
typedef unsigned char	uint_fast8_t;
typedef uint16_t	uint_fast16_t;
typedef uint32_t	uint_fast32_t;
#if defined(__64BIT__) || defined(_LONG_LONG)
typedef int64_t		int_fast64_t;
typedef uint64_t	uint_fast64_t;
#endif /* __64BIT__ || _LONG_LONG */
#endif /* _H_STDINT_TYPE_TS */

#ifndef _STD_TYPES_T
/* implementation limits */
#define INT8_MIN	(-128)
#define INT16_MIN	(-32767-1)
#define INT32_MIN	(-2147483647-1)
#if ( __64BIT__ || defined(_LONG_LONG) )
#define INT64_MIN	(INT64_C(-9223372036854775807)-1)
#endif /* __64BIT__ || _LONG_LONG */

#define INT8_MAX	(127)
#define INT16_MAX	(32767)
#define INT32_MAX	(2147483647)
#if ( __64BIT__ || defined(_LONG_LONG) )
#define INT64_MAX	(INT64_C(9223372036854775807))
#endif /* __64BIT__ || _LONG_LONG */

#define UINT8_MAX	(255U)
#define UINT16_MAX	(65535U)
#define UINT32_MAX	(4294967295U)
#if ( __64BIT__ || defined(_LONG_LONG) )
#define UINT64_MAX	(UINT64_C(18446744073709551615))
#endif /* __64BIT__ || _LONG_LONG */

#define INT_LEAST8_MIN	INT8_MIN
#define INT_LEAST16_MIN	INT16_MIN
#define INT_LEAST32_MIN	INT32_MIN
#if ( __64BIT__ || defined(_LONG_LONG) )
#define INT_LEAST64_MIN	INT64_MIN
#endif /* __64BIT__ || _LONG_LONG */

#define INT_LEAST8_MAX	INT8_MAX
#define INT_LEAST16_MAX	INT16_MAX
#define INT_LEAST32_MAX	INT32_MAX
#if ( __64BIT__ || defined(_LONG_LONG) )
#define INT_LEAST64_MAX	INT64_MAX
#endif /* __64BIT__ || _LONG_LONG */

#define UINT_LEAST8_MAX		UINT8_MAX
#define UINT_LEAST16_MAX	UINT16_MAX
#define UINT_LEAST32_MAX	UINT32_MAX
#if ( __64BIT__ || defined(_LONG_LONG) )
#define UINT_LEAST64_MAX	UINT64_MAX
#endif /* __64BIT__ || _LONG_LONG */

#define INT_FAST8_MIN	INT8_MIN
#define INT_FAST16_MIN	INT16_MIN
#define INT_FAST32_MIN	INT32_MIN
#if ( __64BIT__ || defined(_LONG_LONG) )
#define INT_FAST64_MIN	INT64_MIN
#endif /* __64BIT__ || _LONG_LONG */

#define INT_FAST8_MAX	INT8_MAX
#define INT_FAST16_MAX	INT16_MAX
#define INT_FAST32_MAX	INT32_MAX
#if ( __64BIT__ || defined(_LONG_LONG) )
#define INT_FAST64_MAX	INT64_MAX
#endif /* __64BIT__ || _LONG_LONG */

#define UINT_FAST8_MAX	UINT8_MAX
#define UINT_FAST16_MAX	UINT16_MAX
#define UINT_FAST32_MAX	UINT32_MAX
#if ( __64BIT__ || defined(_LONG_LONG) )
#define UINT_FAST64_MAX	UINT64_MAX
#endif /* __64BIT__ || _LONG_LONG */

#if ( __64BIT__ || (defined(_LONG_LONG)) )
#define INTMAX_MIN	INT64_MIN
#define INTMAX_MAX	INT64_MAX
#define UINTMAX_MAX	UINT64_MAX
#else
#define INTMAX_MIN	INT32_MIN
#define INTMAX_MAX	INT32_MAX
#define UINTMAX_MAX	UINT32_MAX
#endif

#if ( __64BIT__ )
#define INTPTR_MIN	INT64_MIN
#define INTPTR_MAX	INT64_MAX
#define UINTPTR_MAX	UINT64_MAX
#else
#define INTPTR_MIN	INT32_MIN
#define INTPTR_MAX	INT32_MAX
#define UINTPTR_MAX	UINT32_MAX
#endif

#if (__64BIT__)
#define PTRDIFF_MIN	INT64_MIN
#define PTRDIFF_MAX	INT64_MAX
#else
#define PTRDIFF_MIN     INT32_MIN
#define PTRDIFF_MAX	INT32_MAX
#endif

#define SIG_ATOMIC_MIN     INT32_MIN
#define SIG_ATOMIC_MAX     INT32_MAX

#ifndef _WCHAR_MAX
#define _WCHAR_MAX
#ifdef __64BIT__
#define WCHAR_MAX       UINT32_MAX
#else
#define WCHAR_MAX       UINT16_MAX
#endif
#define WCHAR_MIN	0
#endif

#define WINT_MIN	INT32_MIN
#define WINT_MAX	INT32_MAX


#if (__64BIT__) 
#define SIZE_MAX	UINT64_MAX
#else
#define SIZE_MAX        UINT32_MAX
#endif

/* Macros for creating constants of the types defined above*/

#define __CONCAT__(A,B) A ## B

#define INT8_C(c)	c
#define INT16_C(c)	c
#define INT32_C(c)	c
#if defined(_LONG_LONG) && !defined(__64BIT__)
#define INT64_C(c)	__CONCAT__(c,LL)
#else
#define INT64_C(c)	__CONCAT__(c,L)
#endif

#define UINT8_C(c)	__CONCAT__(c,U)
#define UINT16_C(c)	__CONCAT__(c,U)
#define UINT32_C(c)	__CONCAT__(c,U)
#if defined(_LONG_LONG) && !defined(__64BIT__)
#define UINT64_C(c)	__CONCAT__(c,ULL)
#else
#define UINT64_C(c)	__CONCAT__(c,UL)
#endif

#if defined(_LONG_LONG) && !defined(__64BIT__)
#define INTMAX_C(c)	__CONCAT__(c,LL)
#define UINTMAX_C(c)	__CONCAT__(c,ULL)
#else
#define INTMAX_C(c)	__CONCAT__(c,L)
#define UINTMAX_C(c)	__CONCAT__(c,UL)
#endif
#endif /* !_STD_TYPES_T */

#endif /* _ISOC99_SOURCE */
#endif /* _ANSI_C_SOURCE */

#ifdef _STD_TYPES_T
#ifndef	_H_STDINT_TYPE_TS
#define	_H_STDINT_TYPE_TS
#endif	/* _H_STDINT_TYPE_TS */
#endif

#ifdef __cplusplus
}
#endif

#endif /* _H_STDINT */
