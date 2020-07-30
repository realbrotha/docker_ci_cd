/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/usr/include/loader.h 1.11                               */
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
/* @(#)75       1.11  src/bos/usr/include/loader.h, cmdld, bos53H, h2006_07A8 2/6/06 14:12:06 */
#ifndef	_H_LOADER
#define	_H_LOADER
/*
 * COMPONENT_NAME: cmdld
 *
 * STRUCTURES: ldhdr, ldsym, ldrel, ldhdr_64, ldsym_64, ldrel_64
 *
 * ORIGINS: 27
 *
 */

#include <xcoff32_64.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <syms.h>
#include <reloc.h>

/* Header portion */

/*
   In hybrid mode, the following names should be used:

   =============================================================================
   | Basic field/macro name| 32-bit name             | 64-bit name             |
   ============================================================================|
   | l_version             | same                    | same                    |
   | l_nsyms               | same                    | same                    |
   | l_nreloc              | same                    | same                    |
   | l_istlen              | same                    | same                    |
   | l_nimpid              | same                    | same                    |
   | l_impoff              | l_impoff32              | l_impoff64              |
   | l_stlen               | l_stlen32               | l_stlen64               |
   | l_stoff               | l_stoff32               | l_stoff64               |
   | l_symoff              | n/a                     | l_symoff64              |
   | l_rldoff              | n/a                     | l_rldoff64              |
   | LDHDRSZ               | LDHDRSZ_32              | LDHDRSZ_64              |
   | _CURRENT_LDR_VERSION  | _CURRENT_LDR_VERSION_32 | _CURRENT_LDR_VERSION_64 |
   =============================================================================
*/

#ifndef __XCOFF_HYBRID__

#ifdef __XCOFF32__

typedef struct ldhdr {
	_LONG32		l_version;	/* Loader section version number */
#define _CURRENT_LDR_VERSION	(1)
	_LONG32		l_nsyms;	/* Qty of loader Symbol table entries */
	_LONG32		l_nreloc;	/* Qty of loader relocation table
					   entries */
	_ULONG32	l_istlen;	/* Length of loader import file id
					   strings */
	_LONG32		l_nimpid;	/* Qty of loader import file ids. */
	_ULONG32	l_impoff;	/* Offset to start of loader import
					   file id strings */
	_ULONG32	l_stlen;	/* Length of loader string table */
	_ULONG32	l_stoff;	/* Offset to start of loader string
					   table */
} LDHDR;

#endif /* __XCOFF32__ */

#ifdef __XCOFF64__

typedef struct _S_(ldhdr) {
	_LONG32		l_version;	/* Loader section version number */

#ifdef __XCOFF32__
#define _CURRENT_LDR_VERSION_64	(2)
#else
#define _CURRENT_LDR_VERSION	(2)
#endif

	_LONG32		l_nsyms;	/* Qty of loader Symbol table entries */
	_LONG32		l_nreloc;	/* Qty of loader relocation table
					   entries */
	_ULONG32	l_istlen;	/* Length of loader import file id
					   strings */
	_LONG32		l_nimpid;	/* Qty of loader import file ids. */
	_ULONG32	l_stlen;	/* Length of loader string table */
	unsigned long long l_impoff;	/* Offset to start of loader import
					   file id strings */
	unsigned long long l_stoff;	/* Offset to start of loader string
					   table */
	unsigned long long l_symoff;	/* Offset to start of loader symbol
					   table */
	unsigned long long l_rldoff;	/* Offset to start of loader rlds */
} _S_(LDHDR);

#ifdef __XCOFF32__
#define	LDHDRSZ_64	sizeof(LDHDR_64)
#endif

#endif /* __XCOFF64__ */

#define	LDHDRSZ	sizeof(LDHDR)

#else /* __XCOFF_HYBRID__ */

typedef struct ldhdr {
	_LONG32		l_version;	/* Loader section version number */
#define _CURRENT_LDR_VERSION_32	(1)
#define _CURRENT_LDR_VERSION_64	(2)
	_LONG32		l_nsyms;	/* Qty of loader Symbol table entries */
	_LONG32		l_nreloc;	/* Qty of loader relocation table
					   entries */
	_ULONG32	l_istlen;	/* Length of loader import file id
					   strings */
	_LONG32		l_nimpid;	/* Qty of loader import file ids. */
	union {
		_ULONG32 _impoff32;	/* Offset to start of loader
					   import file id strings */
		_ULONG32 _stlen64;	/* Length of loader string
					   table */
	} _u1;
#define l_impoff32	_u1._impoff32
#define l_stlen64	_u1._stlen64
	union {
		struct {
			_ULONG32  _stlen32;	/* Length of loader string
						   table */
			_ULONG32 _stoff32;	/* Offset to start of loader
						   string table */
		} _x;
		unsigned long long _impoff64; /* Offset to start of loader
						 import file id strings */
	} _u2;
#define l_stoff32	_u2._x._stoff32
#define l_stlen32	_u2._x._stlen32
#define l_impoff64	_u2._impoff64

	unsigned long long l_stoff64;	/* Offset to start of loader
					   import file id strings */
	unsigned long long l_symoff64;	/* Offset to start of loader symbol
					   table */
	unsigned long long l_rldoff64;	/* Offset to start of loader rlds */
} LDHDR;

#define	LDHDRSZ_32   ((size_t)&(((LDHDR *)0)->_u2._x._stoff32)+sizeof(_ULONG32))
#define	LDHDRSZ_64   sizeof(LDHDR)

#endif /* __XCOFF_HYBRID__ */

/* Symbol table portion	*/

/*
   In hybrid mode, the following names should be used:

   ============================================================================
   | Basic field or macro name  | 32-bit name          | 64-bit name          |
   ============================================================================
   | l_name                     | l_name32             | n/a                  |
   | l_zeroes                   | l_zeroes32           | n/a                  |
   | l_offset                   | l_offset32           | l_offset64           |
   | l_nptr                     | l_nptr32             | l_nptr64             |
   | l_value                    | l_value32            | l_value64            |
   | l_scnum                    | same                 | same                 |
   | l_smtype                   | same                 | same                 |
   | l_smclas                   | same                 | same                 |
   | l_ifile                    | same                 | same                 |
   | l_parm                     | same                 | same                 |
   | LDSYMSZ                    | LDSYMSZ_32           | LDSYMSZ_64           |
   ============================================================================
*/

#ifndef __XCOFF_HYBRID__

#ifdef __XCOFF32__

typedef struct ldsym {
	union {
		char		_l_name[SYMNMLEN];	/* Symbol name	*/
		struct {
			_LONG32	_l_zeroes;	/* offset if 0		*/
			_LONG32	_l_offset;	/* offset into loader string */
		} _l_l;
#ifdef __64BIT__
		unsigned int	_l_nptr[2];	/* allows for overlaying */
#else
		char		*_l_nptr[2];	/* allows for overlaying */
#endif
	} _l;
	_ULONG32		l_value;	/* Address field	*/
	short			l_scnum;	/* Section number	*/
	char			l_smtype;	/* type and imp/exp/eps	*/
						/* 0	Unused		*/
						/* 1	Import		*/
						/* 2	Entry point	*/
						/* 3	Export		*/
						/* 4	Weak		*/
						/* 5-7	Symbol type	*/
	char			l_smclas;	/* storage class	*/
	_LONG32			l_ifile;	/* import file id	*/
						/*	string offset	*/
	_LONG32			l_parm;		/* type check offset	*/
						/*	into loader string */
} LDSYM;

#define	l_name		_l._l_name
#define	l_zeroes	_l._l_l._l_zeroes

#ifndef __XCOFF64__
/* If __XCOFF32__ and __XCOFF64__ are defined, a single macro for l_nptr
   cannot work for both structures.  Thus, the macro is not defined. */
#define	l_nptr		_l._l_nptr[1]
#endif

#endif /* __XCOFF32__ */

#ifdef __XCOFF64__

typedef struct _S_(ldsym) {
	unsigned long long	l_value;	/* Address field	*/
	union {
		struct {
			_LONG32	_l_offset;	/* offset into loader string */
		} _l_l;
#ifndef __64BIT__
		char	*_l_nptr;	/* Allows for overlaying. */
#endif
	} _l;
	short			l_scnum;	/* Section number	*/
	char			l_smtype;	/* type and imp/exp/eps	*/
						/* 0	Unused		*/
						/* 1	Import		*/
						/* 2	Entry point	*/
						/* 3	Export		*/
						/* 4	Weak		*/
						/* 5-7	Symbol type	*/
	char			l_smclas;	/* storage class	*/
	_LONG32			l_ifile;	/* import file id	*/
						/*	string offset	*/
	_LONG32			l_parm;		/* type check offset	*/
						/*	into loader string */
} _S_(LDSYM);

#ifndef __XCOFF32__
#define	l_nptr		_l._l_nptr
#endif

#ifdef __XCOFF_32_64__
#define	LDSYMSZ_64	sizeof(LDSYM_64)
#endif

#endif /* __XCOFF64__ */

#define	l_offset	_l._l_l._l_offset

#else /* __XCOFF_HYBRID__ */

typedef struct ldsym {
	union {
		char		_l_name32[SYMNMLEN];	/* Symbol name	*/
		unsigned long long	_value64; /* Symbol name	*/
		struct {
			_LONG32	_l_zeroes32;	/* offset if 0		*/
			_LONG32	_l_offset32;	/* offset into loader string */
		} _l_l;
#ifdef __64BIT__
		unsigned int	_l_nptr[2];	/* allows for overlaying */
#else
		char		*_l_nptr[2];	/* allows for overlaying */
#endif
	} _l;
	union {
		unsigned int	_value32;	/* Address field	*/
		int		_offset64;	/* offset into loader string */
#ifndef __64BIT__
		char		*_l_nptr;	/* Allows for overlaying */
#endif
	} _u;
	short			l_scnum;	/* Section number	*/
	char			l_smtype;	/* type and imp/exp/eps	*/
						/* 0	Unused		*/
						/* 1	Import		*/
						/* 2	Entry point	*/
						/* 3	Export		*/
						/* 4	Weak		*/
						/* 5-7	Symbol type	*/
	char			l_smclas;	/* storage class	*/
	_LONG32			l_ifile;	/* import file id	*/
						/*	string offset	*/
	_LONG32			l_parm;		/* type check offset	*/
						/*	into loader string */
} LDSYM;

#define	l_name32	_l._l_name32
#define	l_zeroes32	_l._l_l._l_zeroes32
#define	l_offset32	_l._l_l._l_offset32
#define	l_value64	_l._value64

#define	l_offset64	_u._offset64
#define	l_value32	_u._value32

#define	LDSYMSZ_32	sizeof(LDSYM)
#define	LDSYMSZ_64	sizeof(LDSYM)

#ifndef __64BIT__
#define	l_nptr32	_l._l_nptr[1]
#define	l_nptr64	_u._l_nptr
#endif

#endif

#define	LDSYMSZ	sizeof(LDSYM)

#define	L_WEAK		0x08
#define	L_EXPORT	0x10
#define	L_ENTRY		0x20
#define	L_IMPORT	0x40
#define	LDR_WEAK(x)	((x).l_smtype & L_WEAK)
#define	LDR_EXPORT(x)	((x).l_smtype & L_EXPORT)
#define	LDR_ENTRY(x)	((x).l_smtype & L_ENTRY)
#define	LDR_IMPORT(x)	((x).l_smtype & L_IMPORT)
#define	LDR_TYPE(x)	((x).l_smtype & 0x07)

/* Relocation portion	*/

/*
   In hybrid mode, the following names should be used:

   ============================================================================
   | Basic field or macro name  | 32-bit name          | 64-bit name          |
   ============================================================================
   | l_vaddr                    | l_vaddr32            | l_vaddr64            |
   | l_symndx                   | l_symndx32           | l_symndx64           |
   | l_rtype                    | same                 | same                 |
   | l_rsecnm                   | same                 | same                 |
   | LDRELSZ                    | LDRELSZ_32           | LDRELSZ_64           |
   ============================================================================
*/

#ifndef __XCOFF_HYBRID__

#ifdef __XCOFF32__
typedef struct ldrel
{
	_ULONG32	l_vaddr;	/* Address field		*/
	_LONG32		l_symndx;	/* Loader-section symbol table index
					 * of referenced symbol.. This field
					 * is zero-based, and indices
					 * -2,-1,0,1,2 are implicit references
					 * to tbss,tdata,text,data, and bss.
					 * The first symbol actually in the
					 * symbol table has index 3.
					 */
	unsigned short	l_rtype;	/* relocation type		*/
	short		l_rsecnm;	/* section number being relocated */
					/* one-based index in scnhdr table */
} LDREL;

#endif /* __XCOFF32__ */

#ifdef __XCOFF64__
typedef struct _S_(ldrel)
{
	unsigned long long l_vaddr;	/* Address field		*/
	unsigned short	l_rtype;	/* relocation type		*/
	short		l_rsecnm;	/* section number being relocated */
					/* one-based index in scnhdr table */
	int		l_symndx;	/* Loader-section symbol table index
					 * of referenced symbol.. This field
					 * is zero-based, and indices
					 * -2,-1,0,1,2 are implicit references
					 * to tbss,tdata,text,data, and bss.
					 * The first symbol actually in the
					 * symbol table has index 3.
					 */
} _S_(LDREL);

#endif /* __XCOFF64__ */

#ifdef __XCOFF_32_64__
#define	LDRELSZ_64	sizeof(LDREL_64)
#endif

#define	LDRELSZ	sizeof(LDREL)

#else /* __XCOFF_HYBRID__ */

typedef struct ldrel {
	union {
		struct _ldrel32 {
			unsigned int	_vaddr32; /* Address field	*/
			int		_symndx32; /* Loader-section symbol
					 * table index of referenced symbol.
					 * This field is zero-based, and
					 * indices -2,-1,0,1,2 are implicit
					 * references to tbss,tdata,text,data,
					 * and bss.  The first symbol actually
					 * in the symbol table has index 3.
					 */
		} _s;
		unsigned long long _vaddr64; /* Address field		*/
	} _u;
	unsigned short	l_rtype;	/* relocation type		*/
	short		l_rsecnm;	/* section number being relocated */
					/* one-based index in scnhdr table */
	int		l_symndx64;	/* Loader-section symbol table index
					 * of referenced symbol.. This field
					 * is zero-based, and indices
					 * -2,-1,0,1,2 are implicit references
					 * to tbss,tdata,text,data, and bss.
					 * The first symbol actually in the
					 * symbol table has index 3.
					 */
} LDREL;

#define l_vaddr32	_u._s._vaddr32
#define l_symndx32	_u._s._symndx32
#define l_vaddr64	_u._vaddr64

#define	LDRELSZ_32	(size_t)&(((LDREL *)0)->l_symndx64)
#define	LDRELSZ_64	sizeof(LDREL)

#endif /* __XCOFF_HYBRID__ */

#ifdef __cplusplus
}
#endif

#endif	/* _H_LOADER */
