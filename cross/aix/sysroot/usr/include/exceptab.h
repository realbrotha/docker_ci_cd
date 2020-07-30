/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/exceptab.h 1.3                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)65	1.3  src/bos/usr/include/exceptab.h, cmdld, bos530 2/4/97 08:34:54 */
#ifndef	_H_EXCEPTAB
#define _H_EXCEPTAB
/*
 * COMPONENT_NAME: cmdld
 *
 * STRUCTURES: exceptab, exceptab_64 (Exception table structure)
 *
 * ORIGINS: 27
 *
 */

/********************************************************************** 
 *
 *	Structure used to define the .except section of the object file.
 *
 **********************************************************************/

/* When generated, there is one exception table entry for each
 * trap instruction in the executable code.
 * Exception entries are grouped by function.
 * The first entry in a function grouping
 * will have e_reason = 0 and in place of physical
 * address will be the symbol table index of
 * the symbol for the function.

   In hybrid mode, the following names should be used:

   ============================================================================
   | Basic field or macro name  | 32-bit name          | 64-bit name          |
   ============================================================================
   | e_addr.e_symndx            | e_addr32.e_symndx    | e_addr64.e_symndx    |
   | e_addr.e_paddr             | e_addr32.e_paddr     | e_addr64.e_paddr     |
   | e_lang                     | e_lang32             | e_lang64             |
   | e_reason                   | e_reason32           | e_reason64           |
   | EXCEPTSZ                   | EXCEPTSZ_32          | EXCEPTSZ_64          |
   ============================================================================
*/

#include <xcoff32_64.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __XCOFF_HYBRID__

#ifdef __XCOFF32__

typedef struct exceptab {
	union {
		_LONG32	e_symndx;	/* sym. table index of function
					   if e_reason == 0	*/
		_LONG32	e_paddr;	/* address of trap inst */
	} e_addr;
	char	e_lang;			/* compiler language id code */
	char	e_reason;		/* exception reason code */
} EXCEPTAB;

#define	EXCEPTSZ	(6)		/* Do not use sizeof(EXCEPTAB) */

#endif /* __XCOFF32__ */

#ifdef __XCOFF64__

typedef struct _S_(exceptab) {
	union {
		int	 e_symndx;	/* sym. table index of function
					   if e_reason == 0	*/
		long long e_paddr;	/* address of trap inst */
	} e_addr;
	char	e_lang;			/* compiler language id code */
	char	e_reason;		/* exception reason code */
} _S_(EXCEPTAB);

#ifdef __XCOFF_32_64__
#define	EXCEPTSZ_64	(10)	/* Do not use sizeof(EXCEPTAB_64) */
#else
#define	EXCEPTSZ	(10)	/* Do not use sizeof(EXCEPTAB) */
#endif

#endif /* __XCOFF64__ */

#else /* __XCOFF_HYBRID__ */

typedef struct exceptab {
	union {
		struct {
			union {
				_LONG32	e_symndx; /* symbol table index of
						     function if e_reason==0 */
				_LONG32	e_paddr; /* address of trap inst */
			} _addr32;
			char	_lang32;	/* compiler language id code */
			char	_reason32;	/* exception reason code */
		} _s32;
		struct {
			union {
				int e_symndx; /* sym. table index of
						       function name if
						       e_reason == 0 */
				long long e_paddr; /* address of trap inst */
			} _addr64;
			char	_lang64;	/* compiler language id code */
			char	_reason64;	/* exception reason code */
		} _s64;
	} _u;
} EXCEPTAB;

#define	EXCEPTSZ_32	(6)
#define	EXCEPTSZ_64	(10)	/* Do not use sizeof(EXCEPTAB) */

#define e_addr32	_u._s32._addr32
#define e_lang32	_u._s32._lang32
#define e_reason32	_u._s32._reason32

#define e_addr64	_u._s64._addr64
#define e_lang64	_u._s64._lang64
#define e_reason64	_u._s64._reason64

#endif /* __XCOFF_HYBRID__ */

#ifdef __cplusplus
}
#endif
#endif	/* _H_EXCEPTAB  */
