/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/usr/include/reloc.h 1.3.1.7                             */
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
/* @(#)48	1.3.1.7  src/bos/usr/include/reloc.h, cmdld, bos53L, l2007_17A8 4/12/07 11:06:08 */
#ifndef	_H_RELOC
#define _H_RELOC
/*
 * COMPONENT_NAME: cmdld
 *
 * STRUCTURES: reloc, reloc_64
 *
 * ORIGINS: 3, 27
 *
 */

#include <xcoff32_64.h>

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
   In hybrid mode, the following names should be used:

   ============================================================================
   | Basic field or macro name  | 32-bit name          | 64-bit name          |
   ============================================================================
   | r_vaddr                    | r_vaddr32            | r_vaddr64            |
   | r_symndx                   | r_symndx32           | r_symndx64           |
   | r_type                     | r_type32             | r_type64             |
   | r_rsize                    | r_rsize32            | r_rsize64            |
   | r_rtype                    | r_rtype32            | r_rtype64            |
   | RELSZ                      | RELSZ_32             | RELSZ_64             |
   ============================================================================
*/

#ifndef __XCOFF_HYBRID__

#ifdef __XCOFF32__

typedef struct reloc {
	_ULONG32	r_vaddr;	/* (virtual) address of reference */
	_ULONG32	r_symndx;	/* index into symbol table */
	union {
		unsigned short _r_type;	/* old style coff relocation type */
		struct {
			char	_r_rsize; /* sign and reloc bit len */
			char	_r_rtype; /* toc relocation type */
		} _r_r;
	} _r;
} RELOC;
#define	RELSZ	(10)	/* Do not use sizeof(RELOC) */

#endif /* __XCOFF32__ */

#ifdef __XCOFF64__

typedef struct _S_(reloc) {
	unsigned long long	r_vaddr; /* (virtual) address of reference */
	unsigned int		r_symndx; /* index into symbol table */
	union {
		unsigned short _r_type;	/* old style coff relocation type */
		struct {
			char	_r_rsize; /* sign and reloc bit len */
			char	_r_rtype; /* toc relocation type */
		} _r_r;
	} _r;
} _S_(RELOC);

#ifdef __XCOFF_32_64__
#define	RELSZ_64	(14)	/* Do not use sizeof(RELOC_64) */
#else
#define	RELSZ		(14)	/* Do not use sizeof(RELOC) */
#endif

#endif /* __XCOFF32__ */

#define r_type	_r._r_type		/* old style field name */
#define r_rsize	_r._r_r._r_rsize	/* extract sign and bit len */
#define r_rtype	_r._r_r._r_rtype	/* extract toc relocation type */

#else /* __XCOFF_HYBRID__ */

typedef struct reloc {
	union {
		struct _r32 {
			_ULONG32 _vaddr32;	/* virtual addr of reference */
			_ULONG32 _symndx32;	/* index into symbol table */
		} _s32;
		unsigned long long _vaddr64; /* virtual addr of reference */
	} _u;
	union {
		unsigned int	_symndx64;	/* index into symbol table */
		unsigned short _r_type;	/* old style coff relocation type */
		struct {
			char	_r_rsize; /* sign and reloc bit len */
			char	_r_rtype; /* toc relocation type */
		} _r_r;
	} _r;
	union {
		unsigned short _r_type;	/* old style coff relocation type */
		struct {
			char	_r_rsize; /* sign and reloc bit len */
			char	_r_rtype; /* toc relocation type */
		} _r_r;
	} _r64;
} RELOC;

#define	RELSZ_32	(10)
#define	RELSZ_64	(14)	/* Do not use sizeof(RELOC) */

#define r_vaddr32	_u._s32._vaddr32
#define r_symndx32	_u._s32._symndx32
#define r_type32	_r._r_type
#define r_rsize32	_r._r_r._r_rsize
#define r_rtype32	_r._r_r._r_rtype

#define r_vaddr64	_u._vaddr64
#define r_symndx64	_r._symndx64
#define r_type64	_r64._r_type
#define r_rsize64	_r64._r_r._r_rsize
#define r_rtype64	_r64._r_r._r_rtype

#endif /* __XCOFF_HYBRID__ */

#define R_LEN	0x3F		/* extract bit-length field */
#define R_SIGN	0x80		/* extract sign of relocation */
#define R_FIXUP	0x40		/* extract code-fixup bit */

#define RELOC_RLEN(x)	((x)._r._r_r._r_rsize & R_LEN)
#define RELOC_RSIGN(x)	((x)._r._r_r._r_rsize & R_SIGN)
#define RELOC_RFIXUP(x)	((x)._r._r_r._r_rsize & R_FIXUP)
#define RELOC_RTYPE(x)	((x)._r._r_r._r_rtype)

/*
 *	POWER and PowerPC - relocation types
 */
#define	R_POS	0x00	/* A(sym) Positive Relocation	*/
#define R_NEG	0x01	/* -A(sym) Negative Relocation	*/
#define R_REL	0x02	/* A(sym-*) Relative to self	*/
#define	R_TOC	0x03	/* A(sym-TOC) Relative to TOC	*/
#define R_TRL	0x12	/* A(sym-TOC) TOC Relative indirect load. */
			/*            modifiable instruction */
#define R_TRLA	0x13	/* A(sym-TOC) TOC Rel load address. modifiable inst */
#define R_GL	0x05	/* A(external TOC of sym) Global Linkage */
#define R_TCL	0x06	/* A(local TOC of sym) Local object TOC address */
#define R_RL	0x0C	/* A(sym) Pos indirect load. modifiable instruction */
#define R_RLA	0x0D	/* A(sym) Pos Load Address. modifiable instruction */
#define R_REF	0x0F	/* AL0(sym) Non relocating ref. No garbage collect */
#define R_BA	0x08	/* A(sym) Branch absolute. Cannot modify instruction */
#define R_RBA	0x18	/* A(sym) Branch absolute. modifiable instruction */
#define	R_BR	0x0A	/* A(sym-*) Branch rel to self. non modifiable */
#define R_RBR	0x1A	/* A(sym-*) Branch rel to self. modifiable instr */

#define R_TLS		0x20	/* General-dynamic reference to TLS symbol */
#define R_TLS_IE	0x21	/* Initial-exec reference to TLS symbol */
#define R_TLS_LD	0x22	/* Local-dynamic reference to TLS symbol */
#define R_TLS_LE	0x23	/* Local-exec reference to TLS symbol */
#define R_TLSM		0x24	/* Module reference to TLS symbol */
#define R_TLSML		0x25	/* Module reference to local (own) module */

#define R_TOCU		0x30	/* Relative to TOC - high order bits */
#define R_TOCL		0x31	/* Relative to TOC - low order bits */

/* UNUSED */
#define	R_RBAC	0x19	/* A(sym) Branch absolute constant. modifiable instr */
#define R_RBRC	0x1B	/* A(sym-*) Branch absolute const. */
			/* 		modifiable to R_RBR */
#define R_RTB	0x04	/* A((sym-*)/2) RT IAR Rel Branch. non modifiable */
#define R_RRTBI	0x14	/* A((sym-*)/2) RT IAR Rel Br. modifiable to R_RRTBA */
#define R_RRTBA	0x15	/* A((sym-*)/2) RT absolute br. modifiable to R_RRTBI */

/*
 *	original style - relocation types from coff
 *	UNUSED: The #defines retained for compatability
 */
#define R_ABS		0
#define	R_OFF8		07
#define R_OFF16		010
#define	R_SEG12		011
#define	R_AUX		013
#define R_DIR16	01
#define R_REL16	02
#define R_IND16	03
#define R_DIR24	04
#define R_REL24	05
#define R_OPT16	014
#define R_IND24	015
#define R_IND32	016
#define	R_DIR10		025
#define R_REL10		026
#define R_REL32		027
#define R_DIR32S	012
#define R_RELBYTE	017
#define R_RELWORD	020
#define R_RELLONG	021
#define R_PCRBYTE	022
#define R_PCRWORD	023
#define R_PCRLONG	024

#ifdef __cplusplus
}
#endif

#endif /* _H_RELOC */
