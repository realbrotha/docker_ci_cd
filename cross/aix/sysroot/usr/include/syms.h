/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/usr/include/syms.h 1.14                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)20       1.14  src/bos/usr/include/syms.h, cmdld, bos53L, l2007_09A2 2/6/07 13:40:54 */
#ifndef	_H_SYMS
#define _H_SYMS
/*
 * COMPONENT_NAME: cmdld
 *
 * STRUCTURES: syment, syment_64, auxent, auxent_64
 *
 * ORIGINS: 3, 27
 *
 */

#include <xcoff32_64.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Storage Classes are defined in <storclass.h> */
#include <storclass.h>

#define	SYMNMLEN	8  /* Number of characters in a symbol name */
#define	FILNMLEN	14 /* Number of characters in a file name */
#ifdef __XCOFF32__
#define	DIMNUM		4  /* Number of array dimensions in auxiliary entry */
#endif

/*
   The following field names are conventionally used for structures defined
   in this file. Where an entry is blank, the name is not applicable to
   its respective file type, whether hybrid names are used or not.

 ===============================================================================
 | Basic field or macro name      | XCOFF32 Name        | XCOFF64 Name         |
 |=============================================================================|
 |                                SYMENT                                       |
 |-----------------------------------------------------------------------------|
 | n_name                         | n_name32            |                      |
 | n_zeroes                       | n_zeroes32          |                      |
 | n_offset                       | n_offset32          | n_offset64           |
 | n_nptr                         | n_nptr32 (Note 1)   | n_nptr64 (Note 1)    |
 | n_value                        | n_value32           | n_value64            |
 | n_scnum                        | same                | same                 |
 | n_type (Note 2)                | same                | same                 |
 | n_lang                         | same                | same                 |
 | n_cputype                      | same                | same                 |
 | n_sclass                       | same                | same                 |
 | n_numaux                       | same                | same                 |
 | SYMESZ                         | SYMESZ_32           | SYMESZ_64            |
 |-----------------------------------------------------------------------------|
 |                                AUXENT                                       |
 |-----------------------------------------------------------------------------|
 | x_sym.x_exptr                  | x_sym32.x_exptr     | See x_except.x_exptr |
 | x_sym.x_misc.x_fsize           | x_sym32.x_misc.x_** | See x_fcn.x_fsize    |
 | x_sym.x_misc.x_lnsz.x_lnno     | x_sym32.x_misc.x_** | x_sym64.x_misc.x_l** |
 | x_sym.x_fcnary.x_fcn.x_lnnoptr | x_sym32.x_fcnary.** | See x_fcn.x_lnnoptr  |
 | x_sym.x_fcnary.x_fcn.s_endndx  | x_sym32.x_fcnary.** | See x_fcn.x_endndx   |
 | x_sym.x_auxtype (Note 3)       |                     | x_sym64.x_auxtype    |
 | x_file.x_fname                 | same                | same                 |
 | x_file._x.x_zeroes             | same                | same                 |
 | x_file._x.x_offset             | same                | same                 |
 | x_file._x.x_ftype              | same                | same                 |
 | x_file._x.x_auxtype (Note 3)   |                     | x_file.x_auxtype64   |
 | x_scn.x_scnlen                 | x_scn32.x_scnlen    |                      |
 | x_scn.x_nreloc                 | x_scn32.x_nreloc    |                      |
 | x_scn.x_nlinno                 | x_scn32.x_nlinno    |                      |
 | x_csect.x_scnlen               | x_csect.x_scnlen32  | (Note 4)             |
 | x_csect.x_scnlen_lo            |                     | x_csect.x_scnlen_lo64|
 | x_csect.x_parmhash             | same                | same                 |
 | x_csect.x_snhash               | same                | same                 |
 | x_csect.x_smtyp                | same                | same                 |
 | x_csect.x_smclas               | same                | same                 |
 | x_csect.x_scnlen_hi            |                     | x_csect.x_scnlen_hi64|
 | x_csect.x_auxtype (Note 3)     |                     | x_csect.x_auxtype64  |
 | x_csect.x_stab                 | x_csect.x_stab32    |                      |
 | x_csect.x_snstab               | x_csect.x_snstab32  |                      |
 | x_except.x_exptr               |                     | x_except64.x_exptr   |
 | x_except.x_fsize    (Note 5)   |                     | x_except64.x_fsize   |
 | x_except.x_endndx   (Note 5)   |                     | x_except64.x_endndx  |
 | x_except.x_auxtype  (Note 3)   |                     | x_except64.x_auxtype |
 | x_fcn.x_lnnoptr                |                     | x_fcn64.x_lnnoptr    |
 | x_fcn.x_fsize       (Note 5)   |                     | x_fcn64.x_fsize64    |
 | x_fcn.x_endndx      (Note 5)   |                     | x_fcn64.x_endndx     |
 | x_fcn.x_auxtype     (Note 3)   |                     | x_fcn64.x_auxtype    |
 | x_auxtype.x_auxtype (Note 3)   |                     | x_auxtype64.x_auxtype|
 | AUXESZ                         | AUXESZ_32           | AUXESZ_64            |
 ===============================================================================

 Note 1: When both __XCOFF32__ and __XCOFF64__ are defined, but
	__XCOFF_HYBRID__ is not, the macro "n_nptr" is not defined.
	The n_nptr definition is not very useful when compiling in
	64-bit mode.

 Note 2: For an XCOFF64 file, the n_type field may only have the values
	0 (if the symbol is not a function) or 0x0020 (if the symbol
	is a function).

 Note 3: All the fields containing "x_auxtype" refer to the same byte
	of the auxiliary symbol table entry.

 Note 4: The XCOFF64 equivalent for x_csect.x_scnlen is the concatenation
	of x_csect.x_scnlen_hi and x_csect.x_scnlen_lo.

 Note 5: When _AUX_EXCEPT and  _AUX_FCN	auxiliary symbol table entries 
	exist for the same primary symbol table entry, the x_fsize and
	x_endndx fields of the two entries should have the same values.

 Note 6: Field names not listed in the table above are obsolete and are
	not used in the current release of AIX.
*/

#ifndef __XCOFF_HYBRID__

#ifdef __XCOFF32__

typedef struct syment {
	union {
		char		_n_name[SYMNMLEN]; /* Symbol name (if 8
						      characters or less) */
		struct {
			_LONG32	_n_zeroes;	/* new == 0 */
			_LONG32	_n_offset;	/* offset into string table */
		} _n_n;
#ifndef __64BIT__
		char		*_n_nptr[2];	/* allows for overlaying */
#else
		unsigned int	_n_nptr[2];	/* allows for overlaying */
#endif
	} _n;
	_ULONG32		n_value;	/* value of symbol */
	short			n_scnum;	/* section number */
	union {
		unsigned short	_n_type;	/* type and derived type */
		struct {
			unsigned char _n_lang;	/* source language id	*/
			unsigned char _n_cpu;	/* cputype id		*/
		}_n_lc;
	} _n_tylc;
	char			n_sclass;	/* storage class */
	char			n_numaux;	/* number of aux. entries */
} SYMENT;

#ifndef n_name
#define n_name		_n._n_name
#endif	/* n_name */
#define n_zeroes	_n._n_n._n_zeroes

#ifndef __XCOFF64__
/* If __XCOFF32__ and __XCOFF64__ are defined, a single macro for n_nptr
   cannot work for both structures.  Thus, the macro is not defined. */
#define n_nptr		_n._n_nptr[1]
#endif

#endif /* __XCOFF32__ */

#ifdef __XCOFF64__

typedef struct _S_(syment) {
	unsigned long long	n_value; /* value of symbol */
	union {
		struct {
			int	_n_offset;	/* offset into string table */
		} _n_n;
#ifndef __64BIT__
		char	* _n_nptr;		/* Allows for overlaying */
#endif
	} _n;
	short			n_scnum;	/* section number */
	union {
		unsigned short	_n_type;	/* type and derived type */
		struct {
			unsigned char _n_lang;	/* source language id	*/
			unsigned char _n_cpu;	/* cputype id		*/
		}_n_lc;
	} _n_tylc;

	char			n_sclass;	/* storage class */
	char			n_numaux;	/* number of aux. entries */
} _S_(SYMENT);

#ifdef __XCOFF_32_64__
#define	SYMESZ_64	(18)		/* Do not use sizeof(SYMENT_64) */
#endif

#ifndef __XCOFF32__
#define	n_nptr		_n._n_nptr
#endif

#endif /* __XCOFF64__ */

#define n_offset	_n._n_n._n_offset

#else /* __XCOFF_HYBRID__ */

typedef struct syment {
	union {
		char		_name32[SYMNMLEN];	/* old COFF version */
		struct {
			_LONG32	_zeroes32;	/* new == 0 */
			_LONG32	_offset32;	/* offset into string table */
		} _n_n;
#ifndef __64BIT__
		char		*_nptr32[2];	/* allows for overlaying */
#else
		unsigned int	_nptr32[2];	/* allows for overlaying */
#endif
		unsigned long long	_value64; /* value of symbol */
	} _n;
#define n_name32	_n._name32
#define n_nptr32	_n._nptr32[1]
#define n_zeroes32	_n._n_n._zeroes32
#define n_value64	_n._value64
#define n_offset32	_n._n_n._offset32

	union {
		unsigned int	_value32; /* value of symbol */
		int		_offset64; /* offset into string table */
#ifndef __64BIT__
		char		*_nptr64; /* Allows for overlaying */
#define n_nptr64	_u2._offset64
#endif
	} _u2;

#define n_value32	_u2._value32
#define n_offset64	_u2._offset64

	short			n_scnum;	/* section number */
	union {
		unsigned short	_n_type;	/* type and derived type */
		struct {
			unsigned char _n_lang;	/* source language id	*/
			unsigned char _n_cpu;	/* cputype id		*/
		}_n_lc;
	} _n_tylc;
	char			n_sclass;	/* storage class */
	char			n_numaux;	/* number of aux. entries */
} SYMENT;

#endif /* __XCOFF_HYBRID__ */

/* include file <nlist.h> also defines n_name and n_type. */
#ifndef n_type
#define n_type		_n_tylc._n_type
#endif	/* n_type */

#define n_cputype	_n_tylc._n_lc._n_cpu
#define n_lang		_n_tylc._n_lc._n_lang

/* Structure size is the same for both XCOFF32 and XCOFF64 */
#define	SYMESZ		(18)	/* Do not use sizeof(SYMENT) */
#ifdef __XCOFF_HYBRID__
#define	SYMESZ_32	(18)
#define	SYMESZ_64	(18)
#endif

/*
 * Relocatable symbols have a section number of the
 * section in which they are defined. Otherwise, section
 * numbers have the following meanings:
 */
#define	N_UNDEF		0 	/* undefined symbol */
#define	N_ABS		-1 	/* value of symbol is absolute */
#define	N_DEBUG		-2 	/* special debugging symbol */

#ifdef __XCOFF32__

/* Obsolete definitions--not defined for XCOFF64. */
/*
 * The fundamental type of a symbol packed into the low
 * 4 bits of the word.
 * Unused in xcoff.
 */

#define	T_NULL		0
#define	T_ARG		1	/* function argument (only used by compiler) */
#define	T_CHAR		2	/* character */
#define	T_SHORT		3	/* short integer */
#define	T_INT		4	/* integer */
#define	T_LONG		5	/* long integer */
#define	T_FLOAT		6	/* floating point */
#define	T_DOUBLE	7	/* double word */
#define	T_STRUCT	8	/* structure */
#define	T_UNION		9	/* union */
#define	T_ENUM		10	/* enumeration */
#define	T_MOE		11	/* member of enumeration */
#define	T_UCHAR		12	/* unsigned character */
#define	T_USHORT	13	/* unsigned short */
#define	T_UINT		14	/* unsigned integer */
#define	T_ULONG		15	/* unsigned long */

/*
 * derived types are:
 */

#define DT_NON	0	/* no derived type */
#define DT_PTR	1	/* pointer */
#define DT_FCN	2	/* function */
#define DT_ARY	3	/* array */

/*
 *	type packing constants
 */

#define N_BTMASK	017
#define N_TMASK		060
#define N_TMASK1	0300
#define N_TMASK2	0360
#define N_BTSHFT	4
#define N_TSHIFT	2

#ifndef _COMPILER
/*
 *	MACROS
 */

	/* Basic Type of x */
#define BTYPE(x)	((x) & N_BTMASK)

	/* Is x a pointer? */
#define ISPTR(x)	(((x) & N_TMASK) == (DT_PTR << N_BTSHFT))

	/* Is x a function? */
#define ISFCN(x)	(((x) & N_TMASK) == (DT_FCN << N_BTSHFT))

	/* Is x an array? */
#define ISARY(x)	(((x) & N_TMASK) == (DT_ARY << N_BTSHFT))

	/* Is x a structure, union, or enumeration TAG? */
#define ISTAG(x)	((x)==C_STRTAG || (x)==C_UNTAG || (x)==C_ENTAG)

#define INCREF(x) ((((x)&~N_BTMASK)<<N_TSHIFT)|(DT_PTR<<N_BTSHFT)|(x&N_BTMASK))

#define DECREF(x) ((((x)>>N_TSHIFT)&~N_BTMASK)|((x)&N_BTMASK))

#endif /* _COMPILER */

#endif /* __XCOFF32__ */

#ifdef __XCOFF_32_64__
#define ISFCN_64(x)	((x) & 0x0020)
#endif
#ifdef __XCOFF_64__
#define ISFCN(x)	((x) & 0x0020)
#endif

/*************************************************************************
 *
 *	AUXILIARY ENTRY FORMAT
 *
 *************************************************************************/

/* Structure name and size are the same for both XCOFF32 and XCOFF64. */
#define	AUXESZ	(18)	/* Do not use sizeof(AUXENT) */
#ifdef __XCOFF_HYBRID__
#define	AUXESZ_32	(18)
#define	AUXESZ_64	(18)
#endif

#ifdef __XCOFF_HYBRID__
#define _S32_(name) name ## 32
#else
#define _S32_(name) name
#endif

#ifdef __XCOFF32__

typedef union auxent {
	struct {
		_LONG32		x_tagndx;	/* str, un, or enum tag indx */
						/* exception table offset */
#define 		x_exptr	x_tagndx
		union {
			struct {
				unsigned short	x_lnno;	
						/* declaration line number */
				unsigned short	x_size;	
						/* str, union, array size */
			} x_lnsz;
			_LONG32	x_fsize;	/* size of function */
		} x_misc;
		union {
			struct {		/* if ISFCN, tag, or .bb */
				_LONG32	x_lnnoptr;	/* ptr to fcn line # */
				_LONG32	x_endndx;	
						/* entry ndx past block end */
			} x_fcn;
			struct {		/* if ISARY, up to 4 dimen. */
				unsigned short	x_dimen[DIMNUM];
			} x_ary;
		} x_fcnary;
		unsigned short	x_tvndx;		/* tv index */
	} _S32_(x_sym);

#ifdef  __XCOFF_HYBRID__
	struct {
		struct {
			struct {
				int	x_lnno; /* declaration line number */
			} x_lnsz;
		} x_misc;
		char		pad[13];
		char		x_auxtype;	/* Auxiliary symbol type */
	} x_sym64;
#endif /* __XCOFF_HYBRID__ */

	union {
		char	x_fname[FILNMLEN];
		struct {
			_LONG32		x_zeroes;
			_LONG32		x_offset;
			char		x_pad[FILNMLEN-8];
			unsigned char	x_ftype;
#ifdef __XCOFF_HYBRID__
			struct {
				char	pad[2];
				struct {
				char	_auxtype; /* Auxiliary symbol type */
				} _xt;
			} _x;
#define x_auxtype64 _x._xt._auxtype
#endif
		} _x;
	} x_file;
	struct {
		_LONG32		x_scnlen; /* section length */
		unsigned short	x_nreloc; /* number of relocation entries */
		unsigned short	x_nlinno; /* number of line numbers */
	} _S32_(x_scn);

	/* CSECT auxiliary entry */
	struct {
#ifdef __XCOFF_HYBRID__
		union {
			_LONG32 _scnlen32; /* csect length */
			_ULONG32 _scnlen_lo64;
		} _u;
#else
		_LONG32 _S32_(x_scnlen);	/* csect length */
#endif
		_LONG32		x_parmhash;	/* parm type hash index */
		unsigned short	x_snhash;	/* sect num with parm hash */
		unsigned char	x_smtyp;	/* symbol align and type */
						/* 0-4 - Log 2 of alignment */
						/* 5-7 - symbol type */
		unsigned char	x_smclas;	/* storage mapping class */
		_LONG32		_S32_(x_stab);	/* dbx stab info index */
#ifdef __XCOFF_HYBRID__
		union {
			struct {
				char	pad;
				char _auxtype;
			} _xt;
			unsigned short	_snstab;/* sect num with dbx stab */
		} _x;			
#else
		unsigned short	_S32_(x_snstab);/* sect num with dbx stab */
#endif
	} x_csect;
#ifdef __XCOFF_HYBRID__
#	define x_snstab32	_x._snstab
#	define x_scnlen32	_u._scnlen32
#	define x_scnlen_lo64	_u._scnlen_lo64
#	define x_scnlen_hi64	x_stab32
#endif

#ifdef __XCOFF_HYBRID__
	struct {
		long long	x_exptr;	/* exception table offset */
		int		x_fsize;	/* size of function */
		int		x_endndx;	/* entry ndx past block end */
		char		pad;
		char		x_auxtype;
	} x_except64;
	struct {
		long long	x_lnnoptr;	/* line number entry offset */
		int		x_fsize;	/* size of function */
		int		x_endndx;	/* entry ndx past block end */
		char		pad;
		char		x_auxtype;
	} x_fcn64;
	struct {
		struct {
			struct {
				char x_pad[AUXESZ-1];
				char x_auxtype;
			} _auxtype;
		} _xt;
	} _x;
#endif
} AUXENT;

#endif /* __XCOFF32__ */

#if defined(__XCOFF64__) && ! defined(__XCOFF_HYBRID__)
typedef union _S_(auxent) {
	struct {
		struct {
			struct {
				int	x_lnno; /* declaration line number */
			} x_lnsz;
		} x_misc;
		char		pad[13];
		char		x_auxtype;	/* Auxiliary symbol type */
	} x_sym;

	union {
		char	x_fname[FILNMLEN];
		struct {
			int		x_zeroes;
			int		x_offset;
			char		x_pad[FILNMLEN-8];
			unsigned char	x_ftype;
			char		pad[2];
			char		x_auxtype; /* Auxiliary symbol type */
		} _x;
	} x_file;

	/* CSECT auxiliary entry */
	struct {
		unsigned int	x_scnlen_lo;	/* csect length */
		_LONG32		x_parmhash;	/* parm type hash index */
		unsigned short	x_snhash;	/* sect num with parm hash */
		unsigned char	x_smtyp;	/* symbol align and type */
						/* 0-4 - Log 2 of alignment */
						/* 5-7 - symbol type */
		unsigned char	x_smclas;	/* storage mapping class */
		int		x_scnlen_hi;
		char		pad;
		char		x_auxtype;	/* Auxiliary symbol type */
	} x_csect;
	struct {
		long long	x_exptr;	/* exception table offset */
		int		x_fsize;	/* size of function */
		int		x_endndx;	/* entry ndx past block end */
		char		pad;
		char		x_auxtype;	/* Auxiliary symbol type */
	} x_except;
	struct {
		long long	x_lnnoptr;	/* line number entry offset */
		int		x_fsize;	/* size of function */
		int		x_endndx;	/* entry ndx past block end */
		char		pad;
		char		x_auxtype;	/* Auxiliary symbol type */
	} x_fcn;
	struct {
		char x_pad[AUXESZ-1];
		char x_auxtype;
	} x_auxtype;
} _S_(AUXENT);

#ifdef __XCOFF32__
#define	AUXESZ_64	(18)	/* Do not use sizeof(AUXENT_64) */
#endif

#endif /* defined(__XCOFF64__) && ! defined(__XCOFF_HYBRID__) */

#ifdef __XCOFF64__
#define _AUX_EXCEPT	255
#define _AUX_FCN	254
#define _AUX_SYM	253
#define _AUX_FILE	252
#define _AUX_CSECT	251
#endif

/*	Defines for File auxiliary definitions: x_ftype field of x_file */
#define	XFT_FN	0	/* Source File Name */
#define	XFT_CT	1	/* Compile Time Stamp */
#define	XFT_CV	2	/* Compiler Version Number */
#define	XFT_CD	128	/* Compiler Defined Information */

/*	Defines for CSECT auxiliary definitions	*/
/*	Symbol Type (5-7 of x_smtyp field of x_csect) */
#define	XTY_ER	0	/* External Reference */
#define	XTY_SD	1	/* CSECT Section Definition */
#define XTY_LD	2	/* Entry Point - Label Definition */
#define XTY_CM	3	/* Common (BSS) */

#ifdef __XCOFF_32__
/*	Following are unused but retained for source compatability when
	compiling for 32-bit XCOFF files. */
#define XTY_HL	6	/* Hidden Label Definition */

#define XTY_US	5	/* Unset */
#define XTY_EM	4	/* Error Message - Linkedit usage */
#endif

/*	Storage Mapping Class definitions: x_smclas field of x_csect */
/*		READ ONLY CLASSES */
#define	XMC_PR	0	/* Program Code */
#define	XMC_RO	1	/* Read Only Constant */
#define XMC_DB	2	/* Debug Dictionary Table */
#define XMC_GL	6	/* Global Linkage (Interfile Interface Code) */
#define XMC_XO	7	/* Extended Operation (Pseudo Machine Instruction */
#define XMC_SV	8	/* Supervisor Call (32-bit process only) */
#define XMC_SV64   17	/* Supervisor Call for 64-bit process */
#define XMC_SV3264 18	/* Supervisor Call for both 32- and 64-bit processes. */
#define XMC_TI	12	/* Traceback Index csect */
#define XMC_TB	13	/* Traceback table csect */
/*		READ WRITE CLASSES */
#define XMC_RW	5	/* Read Write Data */
#define XMC_TC0 15	/* TOC Anchor for TOC Addressability */
#define XMC_TC	3	/* General TOC item */
#define XMC_TD	16	/* Scalar data item in the TOC */ 
#define XMC_DS	10	/* Descriptor csect */
#define XMC_UA	4	/* Unclassified - Treated as Read Write */
#define XMC_BS	9	/* BSS class (uninitialized static internal) */
#define XMC_UC	11	/* Un-named Fortran Common */

#define XMC_TL	20	/* Initialized thread-local variable */
#define XMC_UL	21	/* Uninitialized thread-local variable */
#define XMC_TE	22	/* Symbol mapped at the end of TOC */

/*	Defines for "special" symbols */

#define _ETEXT	"etext"
#define _EDATA	"edata"
#define _END	"end"

#define	_EF	".ef"

#define _START	"__start"

#ifdef __cplusplus
}
#endif

#endif /* _H_SYMS */
