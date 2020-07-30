/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/inttypes.h 1.24                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2003          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)42     1.24  src/bos/kernel/sys/inttypes.h, incstd, bos530 6/13/03 14:02:19 */

/*
 *   COMPONENT_NAME: incstd
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1997
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_INTTYPES
#ifndef _STD_TYPES_T /* Just include standard typedefs? */
#define	_H_INTTYPES
#endif /* _STD_TYPES_T */

#ifndef _H_STANDARDS
#include <standards.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _ANSI_C_SOURCE

#ifndef _H_STDINT
#include <stdint.h>
#endif


#ifdef _ISOC99_SOURCE

#ifndef _STD_TYPES_T
typedef struct {
	intmax_t quot;
	intmax_t rem;
} imaxdiv_t;

#if defined(_LONG_LONG) && !defined(__64BIT__)
extern intmax_t __strtollmax(const char * __restrict__, char ** __restrict__, int);
#ifndef __C_STRTOIMAX
static intmax_t
strtoimax (const char * __restrict__ __nptr, char ** __restrict__ __endptr, int __base) {
	return __strtollmax (__nptr, __endptr, __base);
}
#endif
#else /* defined(_LONG_LONG) && !defined(__64BIT__) */
#if !defined(_LONG_LONG) && !defined(__64BIT__)
#define strtoumax _strtoumax32
#define wcstoimax _wcstoimax32
#define wcstoumax _wcstoumax32
#define imaxabs _imaxabs32
#define imaxdiv _imaxdiv32
#endif /*!defined(_LONG_LONG) && !defined(__64BIT__) */
extern intmax_t strtoimax(const char * __restrict__, char ** __restrict__, int);
#endif /* defined(_LONG_LONG) && !defined(__64BIT__) */

#ifdef _NO_PROTO
extern intmax_t imaxabs();
extern imaxdiv_t imaxdiv ();
extern uintmax_t strtoumax();
extern intmax_t wcstoimax();
extern uintmax_t wcstoumax();
#else
extern intmax_t imaxabs(intmax_t);
extern imaxdiv_t imaxdiv (intmax_t, intmax_t); 
extern uintmax_t strtoumax(const char * __restrict__, char ** __restrict__, int);
/* wchar_t is needed for wcsto(iu)max */
#ifndef _WCHAR_T
#define _WCHAR_T
#ifdef __64BIT__
typedef unsigned int    wchar_t;
#else
typedef unsigned short  wchar_t;
#endif
#endif /* _WCHAR_T */
extern intmax_t wcstoimax(const wchar_t * __restrict__, wchar_t ** __restrict__, int );
extern uintmax_t wcstoumax(const wchar_t * __restrict__, wchar_t ** __restrict__, int);
#endif /* _NO_PROTO */
#endif /* _STD_TYPES_T */

#ifndef _H_INTTYPES_TYPE_TS
/* Most efficient types on platform */
#ifdef __64BIT__
typedef int64_t         intfast_t;
typedef uint64_t        uintfast_t;
#else /* 32-bit */
typedef int32_t         intfast_t;
typedef uint32_t        uintfast_t;
#endif
#endif /* _H_INTTYPES_TYPE_TS */

#ifndef _STD_TYPES_T

#if !defined(__cplusplus) || defined(__STDC_FORMAT_MACROS) 
/* printf Macros for format specifiers */

#define PRId8		"hhd"
#define PRId16		"hd"
#define PRId32		"d"
#if defined(__64BIT__)
#define PRId64		"ld"
#else
#if defined(_LONG_LONG)
#define PRId64		"lld"
#endif
#endif

#define PRIdLEAST8	"hhd"
#define PRIdLEAST16	"hd"
#define PRIdLEAST32	"d"
#if defined(__64BIT__)
#define PRIdLEAST64	"ld"
#else
#if defined(_LONG_LONG)
#define PRIdLEAST64	"lld"
#endif
#endif

#define PRIdFAST8	"hhd"
#define PRIdFAST16	"hd"
#define PRIdFAST32	"d"
#if defined(__64BIT__)
#define PRIdFAST64	"ld"
#else
#if defined(_LONG_LONG)
#define PRIdFAST64	"lld"
#endif
#endif

#define PRIi8		"hhi"
#define PRIi16		"hi"
#define PRIi32		"i"
#if defined(__64BIT__)
#define PRIi64		"li"
#else
#if defined(_LONG_LONG)
#define PRIi64		"lli"
#endif
#endif

#define PRIiLEAST8	"hhi"
#define PRIiLEAST16	"hi"
#define PRIiLEAST32	"i"
#if defined(__64BIT__)
#define PRIiLEAST64	"li"
#else
#if defined(_LONG_LONG)
#define PRIiLEAST64	"lli"
#endif
#endif

#define PRIiFAST8	"hhi"
#define PRIiFAST16	"hi"
#define PRIiFAST32	"i"
#if defined(__64BIT__)
#define PRIiFAST64	"li"
#else
#if defined(_LONG_LONG)
#define PRIiFAST64	"lli"
#endif
#endif

#define PRIo8		"hho"
#define PRIo16		"ho"
#define PRIo32		"o"
#if defined(__64BIT__)
#define PRIo64		"lo"
#else
#if defined(_LONG_LONG)
#define PRIo64		"llo"
#endif
#endif

#define PRIoLEAST8	"ho"
#define PRIoLEAST16	"ho"
#define PRIoLEAST32	"o"
#if defined(__64BIT__)
#define PRIoLEAST64	"lo"
#else
#if defined(_LONG_LONG)
#define PRIoLEAST64	"llo"
#endif
#endif

#define PRIoFAST8	"hho"
#define PRIoFAST16	"ho"
#define PRIoFAST32	"o"
#if defined(__64BIT__)
#define PRIoFAST64	"lo"
#else
#if defined(_LONG_LONG)
#define PRIoFAST64	"llo"
#endif
#endif

#define PRIx8		"hhx"
#define PRIx16		"hx"
#define PRIx32		"x"
#if defined(__64BIT__)
#define PRIx64		"lx"
#else
#if defined(_LONG_LONG)
#define PRIx64		"llx"
#endif
#endif

#define PRIxLEAST8	"hhx"
#define PRIxLEAST16	"hx"
#define PRIxLEAST32	"x"
#if defined(__64BIT__)
#define PRIxLEAST64	"lx"
#else
#if defined(_LONG_LONG)
#define PRIxLEAST64	"llx"
#endif
#endif

#define PRIxFAST8	"hhx"
#define PRIxFAST16	"hx"
#define PRIxFAST32	"x"
#if defined(__64BIT__)
#define PRIxFAST64	"lx"
#else
#if defined(_LONG_LONG)
#define PRIxFAST64	"llx"
#endif
#endif

#define PRIX8		"hhX"
#define PRIX16		"hX"
#define PRIX32		"X"
#if defined(__64BIT__)
#define PRIX64		"lX"
#else
#if defined(_LONG_LONG)
#define PRIX64		"llX"
#endif
#endif

#define PRIXLEAST8	"hhX"
#define PRIXLEAST16	"hX"
#define PRIXLEAST32	"X"
#if defined(__64BIT__)
#define PRIXLEAST64	"lX"
#else
#if defined(_LONG_LONG)
#define PRIXLEAST64	"llX"
#endif
#endif

#define PRIXFAST8	"hhX"
#define PRIXFAST16	"hX"
#define PRIXFAST32	"X"
#if defined(__64BIT__)
#define PRIXFAST64	"lX"
#else
#if defined(_LONG_LONG)
#define PRIXFAST64	"llX"
#endif
#endif

#define PRIu8		"hhu"
#define PRIu16		"hu"
#define PRIu32		"u"
#if defined(__64BIT__)
#define PRIu64		"lu"
#else
#if defined(_LONG_LONG)
#define PRIu64		"llu"
#endif
#endif

#define PRIuLEAST8	"hhu"
#define PRIuLEAST16	"hu"
#define PRIuLEAST32	"u"
#if defined(__64BIT__)
#define PRIuLEAST64	"lu"
#else
#if defined(_LONG_LONG)
#define PRIuLEAST64	"llu"
#endif
#endif

#define PRIuFAST8	"hhu"
#define PRIuFAST16	"hu"
#define PRIuFAST32	"u"
#if defined(__64BIT__)
#define PRIuFAST64	"lu"
#else
#if defined(_LONG_LONG)
#define PRIuFAST64	"llu"
#endif
#endif


/* scanf Macros for format specifiers */

#define SCNd8		"hhd"
#define SCNd16		"hd"
#define SCNd32		"d"
#if defined(__64BIT__)
#define SCNd64		"ld"
#else
#if defined(_LONG_LONG)
#define SCNd64		"lld"
#endif
#endif

#define SCNdLEAST8      "hhd"
#define SCNdLEAST16     "hd"
#define SCNdLEAST32     "d"
#if defined(__64BIT__)
#define SCNdLEAST64     "ld"
#else
#if defined(_LONG_LONG)
#define SCNdLEAST64     "lld"
#endif
#endif

#define SCNdFAST8      "hhd"
#define SCNdFAST16     "hd"
#define SCNdFAST32     "d"
#if defined(__64BIT__)
#define SCNdFAST64     "ld"
#else
#if defined(_LONG_LONG)
#define SCNdFAST64     "lld"
#endif
#endif


#define SCNi8		"hhi"
#define SCNi16		"hi"
#define SCNi32		"i"
#if defined(__64BIT__)
#define SCNi64		"li"
#else
#if defined(_LONG_LONG)
#define SCNi64		"lli"
#endif
#endif

#define SCNiFAST8      "hhi"
#define SCNiFAST16     "hi"
#define SCNiFAST32     "i"
#if defined(__64BIT__)
#define SCNiFAST64     "li"
#else
#if defined(_LONG_LONG)
#define SCNiFAST64     "lli"
#endif
#endif

#define SCNiLEAST8      "hhi"
#define SCNiLEAST16     "hi"
#define SCNiLEAST32     "i"
#if defined(__64BIT__)
#define SCNiLEAST64     "li"
#else
#if defined(_LONG_LONG)
#define SCNiLEAST64     "lli"
#endif
#endif


#define SCNo8		"hho"
#define SCNo16		"ho"
#define SCNo32		"o"
#if defined(__64BIT__)
#define SCNo64		"lo"
#else
#if defined(_LONG_LONG)
#define SCNo64		"llo"
#endif
#endif

#define SCNoFAST8      "hho"
#define SCNoFAST16     "ho"
#define SCNoFAST32     "o"
#if defined(__64BIT__)
#define SCNoFAST64     "lo"
#else
#if defined(_LONG_LONG)
#define SCNoFAST64     "llo"
#endif
#endif

#define SCNoLEAST8      "hho"
#define SCNoLEAST16     "ho"
#define SCNoLEAST32     "o"
#if defined(__64BIT__)
#define SCNoLEAST64     "lo"
#else
#if defined(_LONG_LONG)
#define SCNoLEAST64     "llo"
#endif
#endif


#define SCNu8		"hhu"
#define SCNu16		"hu"
#define SCNu32		"u"
#if defined(__64BIT__)
#define SCNu64		"lu"
#else
#if defined(_LONG_LONG)
#define SCNu64		"llu"
#endif
#endif

#define SCNuFAST8      "hhu"
#define SCNuFAST16     "hu"
#define SCNuFAST32     "u"
#if defined(__64BIT__)
#define SCNuFAST64     "lu"
#else
#if defined(_LONG_LONG)
#define SCNuFAST64     "llu"
#endif
#endif

#define SCNuLEAST8      "hhu"
#define SCNuLEAST16     "hu"
#define SCNuLEAST32     "u"
#if defined(__64BIT__)
#define SCNuLEAST64     "lu"
#else
#if defined(_LONG_LONG)
#define SCNuLEAST64     "llu"
#endif
#endif


#define SCNx8		"hhx"
#define SCNx16		"hx"
#define SCNx32		"x"
#if defined(__64BIT__)
#define SCNx64		"lx"
#else
#if defined(_LONG_LONG)
#define SCNx64		"llx"
#endif
#endif

#define SCNxFAST8      "hhx"
#define SCNxFAST16     "hx"
#define SCNxFAST32     "x"
#if defined(__64BIT__)
#define SCNxFAST64     "lx"
#else
#if defined(_LONG_LONG)
#define SCNxFAST64     "llx"
#endif
#endif

#define SCNxLEAST8	"hhx"
#define SCNxLEAST16	"hx"
#define SCNxLEAST32	"x"
#if defined(__64BIT__)
#define SCNxLEAST64	"lx"
#else
#if defined(_LONG_LONG)
#define SCNxLEAST64     "llx"
#endif
#endif



/* printf/scan macros for intmax, intfast, intptr */

#if defined(_LONG_LONG) && !defined(__64BIT__)
#define PRIdMAX		"lld"
#define PRIiMAX		"lld"
#define PRIoMAX		"llo"
#define PRIxMAX		"llx"
#define PRIXMAX		"llX"
#define PRIuMAX		"llu"
#else
#define PRIdMAX		"ld"
#define PRIiMAX		"ld"
#define PRIoMAX		"lo"
#define PRIxMAX		"lx"
#define PRIXMAX		"lX"
#define PRIuMAX		"lu"
#endif

#define PRIdFAST	"d"
#define PRIoFAST	"o"
#define PRIxFAST	"x"
#define PRIuFAST	"u"
#define PRIdPTR		"ld"
#define PRIiPTR		"ld"
#define PRIoPTR		"lo"
#define PRIxPTR		"lx"
#define PRIXPTR		"lX"
#define PRIuPTR		"lu"

#if defined(_LONG_LONG) && !defined(__64BIT__)
#define SCNdMAX		"lld"
#define SCNiMAX		"lld"
#define SCNoMAX		"llo"
#define SCNxMAX		"llx"
#define SCNuMAX		"llu"
#else
#define SCNdMAX		"ld"
#define SCNiMAX		"ld"
#define SCNoMAX		"lo"
#define SCNxMAX		"lx"
#define SCNuMAX		"lu"
#endif

#define SCNdFAST	"d"
#define SCNoFAST	"o"
#define SCNxFAST	"x"
#define SCNuFAST	"u"
#define SCNdPTR		"ld"
#define SCNiPTR		"ld"
#define SCNoPTR		"lo"
#define SCNxPTR		"lx"
#define SCNuPTR		"lu"

#endif /* !__cplusplus */
#endif /* _STD_TYPES_T  */

#endif /* _ISOC99_SOURCE */
#endif /* _ANSI_C_SOURCE */


#ifndef _H_INTTYPES_TYPE_TS
/* These types provide fixed size types that preserve source compatibility
 * for 32 bit interfaces with long types in structures that shouldn't be
 * 64 bits wide in 64 bit compilation mode.
 */
#ifdef __64BIT__
typedef signed int	__long32_t;
typedef unsigned int	__ulong32_t;
#else
typedef signed long	__long32_t;
typedef unsigned long	__ulong32_t;
#endif /* __64BIT__ */

/* These types provide variable size types that preserve source compatibility
 * for 32 bit interfaces with int types in structures that need to be
 * 64 bits wide in 64 bit compilation mode.
 */
#ifndef __LONG64_T
#define __LONG64_T
#ifdef __64BIT__
typedef signed long	__long64_t;
typedef unsigned long	__ulong64_t;
#else
typedef signed int	__long64_t;
typedef unsigned int	__ulong64_t;
#endif /* __64BIT__ */
#endif /* __LONG64_T */

/* These types provide variable size types that preserve source compatibility
 * for 32 and 64 bit application interfaces with int types in structures 
 * that need to be 64 bits wide in 64 bit kernel and/or kernel extensions.
 */
#if defined(__64BIT_KERNEL) && defined(_KERNEL)
typedef signed long	int32long64_t;
typedef unsigned long	uint32long64_t;
#else
typedef signed int	int32long64_t;
typedef unsigned int	uint32long64_t;
#endif /* __64BIT_KERNEL && _KERNEL */

/* These types provide variable size types that preserve source compatibility
 * for 32 and 64 bit application interfaces with long types in structures 
 * that need to be variant for 32 and 64 bit applications, but invariant
 * 32-bit for kernel and kernel extensions.
 */
#if defined(__64BIT_KERNEL) && defined(_KERNEL)
typedef signed int	long32int64_t;
typedef unsigned int	ulong32int64_t;
#else
typedef signed long	long32int64_t;
typedef unsigned long	ulong32int64_t;
#endif /* __64BIT_KERNEL && _KERNEL */
#endif /* _H_INTTYPES_TYPE_TS */

#ifdef _ALL_SOURCE

#define INTFAST_MIN	INT32_MIN
#define INTFAST_MAX	INT32_MAX
#define UINTFAST_MAX	UINT32_MAX

/*
 * BSD fixed-size integer type additions to the above ISO-C types.
 *
 */
typedef signed char		int8;
typedef signed short		int16;
typedef signed int		int32;
#ifdef	__64BIT__
typedef long			int64;
#else	/* _ILP32 */
#if defined(_LONG_LONG)
typedef	signed long long	int64;
#endif
#endif

typedef unsigned char		u_int8;
typedef unsigned char		u_int8_t;
typedef unsigned short		u_int16;
typedef unsigned short		u_int16_t;
typedef unsigned int		u_int32;
typedef unsigned int		u_int32_t;
#ifdef	__64BIT__
typedef unsigned long		u_int64;
typedef unsigned long		u_int64_t;
#else	/* _ILP32 */
#if defined(_LONG_LONG)
typedef unsigned long long	u_int64;
typedef unsigned long long	u_int64_t;
#endif
#endif

#endif  /* _ALL_SOURCE */  

#ifdef _STD_TYPES_T
#ifndef _H_INTTYPES_TYPE_TS
#define _H_INTTYPES_TYPE_TS
#endif  /* _H_STDINT_TYPE_TS */
#endif

#ifdef __cplusplus
}
#endif

#endif /* _H_INTTYPES */
