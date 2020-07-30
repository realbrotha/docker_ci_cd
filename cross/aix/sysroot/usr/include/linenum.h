/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/linenum.h 1.8                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)65	1.8  src/bos/usr/include/linenum.h, cmdld, bos530 2/4/97 08:35:34 */
#ifndef	_H_LNUM 
#define _H_LNUM
/*
 * COMPONENT_NAME: cmdld
 *
 * STRUCTURES: lineno, lineno_64
 *
 * ORIGINS: 3, 27
 *
 */

/* There is one line number entry for every 
 * source file line that has associated code.
 * Line numbers are grouped by function.
 * The first entry in a function grouping
 * will have l_lnno == 0 and in place of physical
 * address will be the symbol table index of
 * the symbol for the function.

   In hybrid mode, the following names should be used:

   ============================================================================
   | Basic field or macro name  | 32-bit name          | 64-bit name          |
   ============================================================================
   | l_addr.l_symndx            | l_addr32.l_symndx    | l_addr64.l_symndx    |
   | l_addr.l_paddr             | l_addr32.l_paddr     | l_addr64.l_paddr     |
   | l_lnno                     | l_lnno32             | l_lnno64             |
   | LINESZ                     | LINESZ_32            | LINESZ_64            |
   ============================================================================
 */

#include <xcoff32_64.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __XCOFF_HYBRID__

#ifdef __XCOFF32__

typedef struct lineno {
	union {
		_LONG32	l_symndx;	/* symbol table index of function
					   if l_lnno == 0 */
		_LONG32	l_paddr;	/* address of instruction corresponding
					   to line number */
	} l_addr;
	unsigned short	l_lnno;		/* line number */
} LINENO;
#define	LINESZ	(6)			/* Do not use sizeof(LINENO) */

#endif /* __XCOFF32__ */

#ifdef __XCOFF64__

typedef struct _S_(lineno) {
	union  {
		int l_symndx;		/* symbol table index of function
					   if l_lnno == 0 */
		long long l_paddr;	/* address of instruction corresponding
					   to line number */
	} l_addr;
	unsigned int	l_lnno;		/* line number */
} _S_(LINENO);

#ifdef __XCOFF_32_64__
#define	LINESZ_64	(12)		/* Do not use sizeof(LINENO_64) */
#else
#define	LINESZ		(12)		/* Do not use sizeof(LINENO) */
#endif

#endif /* __XCOFF64__ */

#else /* __XCOFF_HYBRID__ */

typedef struct lineno {
	union {
		struct {
			union {
				_LONG32	l_symndx; /* symbol table index of
						     function if l_lnno == 0 */
				_LONG32	l_paddr; /* address of instruction
						    corresponding to line */
			} _addr32;
			unsigned short	_lnno32; /* line number */
		} _s32;
		struct {
			union {
				int l_symndx; /* symbol table index of
						 function if l_lnno == 0 */
				long long l_paddr; /* address of instruction
						      corresponding to line */
			} _addr64;
			unsigned int	_lnno64; /* line number */
		} _s64;
	} _u;
} LINENO;

#define l_addr32	_u._s32._addr32
#define l_lnno32	_u._s32._lnno32

#define l_addr64	_u._s64._addr64
#define l_lnno64	_u._s64._lnno64

#define	LINESZ_32	(6)
#define	LINESZ_64	(12)

#endif /* __XCOFF_HYBRID__ */

#ifdef __cplusplus
}
#endif

#endif	/* _H_LNUM  */
