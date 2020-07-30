/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/usr/include/scnhdr.h 1.9                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)79	1.9  src/bos/usr/include/scnhdr.h, cmdld, bos53H, h2006_07A8 2/6/06 14:01:42 */
#ifndef	_H_SCNHDR
#define _H_SCNHDR
/*
 * COMPONENT_NAME: cmdld
 *
 * STRUCTURES: scnhdr, scnhdr_64
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
   | s_name                     | same                 | same                 |
   | s_paddr                    | s_paddr32            | s_paddr64            |
   | s_vaddr                    | s_vaddr32            | s_vaddr64            |
   | s_size                     | s_size32             | s_size64             |
   | s_scnptr                   | s_scnptr32           | s_scnptr64           |
   | s_relptr                   | s_relptr32           | s_relptr64           |
   | s_lnnoptr                  | s_lnnoptr32          | s_lnnoptr64          |
   | s_nreloc                   | s_nreloc32           | s_nreloc64           |
   | s_nlnno                    | s_nlnno32            | s_nlnno64            |
   | s_flags                    | s_flags32            | s_flags64            |
   | SCNHSZ                     | SCNHSZ_32            | SCNHSZ_64            |
   | _OVERFLOW_MARKER           | _OVERFLOW_MARKER_32  | _OVERFLOW_MARKER_64  |
   ============================================================================
*/

#ifndef __XCOFF_HYBRID__

#ifdef __XCOFF32__

typedef struct scnhdr {
	char		s_name[8];	/* section name */
	_ULONG32	s_paddr;	/* physical address */
	_ULONG32	s_vaddr;	/* virtual address */
	_ULONG32	s_size;		/* section size */
	_LONG32		s_scnptr;	/* file ptr to raw data for section */
	_LONG32		s_relptr;	/* file ptr to relocation for section */
	_LONG32		s_lnnoptr;	/* file ptr to line numbers for sect. */
	unsigned short	s_nreloc;	/* number of relocation entries */
	unsigned short	s_nlnno;	/* number of line number entries */
	_LONG32		s_flags;	/* flags */
} SCNHDR;
#define	SCNHSZ	sizeof(SCNHDR)

/* If both s_nreloc and s_nlnno fields are set to _OVERFLOW_MARKER,
   an overflow header contains the real values. */
#define _OVERFLOW_MARKER (65535)

#endif /* __XCOFF32__ */

#ifdef __XCOFF64__

typedef struct _S_(scnhdr) {
	char			s_name[8];	/* section name */
	unsigned long long	s_paddr;	/* physical address */
	unsigned long long	s_vaddr;	/* virtual address */
	unsigned long long	s_size;		/* section size */
	long long		s_scnptr;	/* file ptr to raw data */
	long long		s_relptr;	/* file ptr to relocation */
	long long		s_lnnoptr;	/* file ptr to line numbers */
	unsigned int		s_nreloc;	/* # of relocation entries */
	unsigned int		s_nlnno;	/* # of line number entries */
	int			s_flags;	/* flags */
} _S_(SCNHDR);

/* No section header overflows are possible for XCOFF64.  These macros are
   only defined to allow programs that use _OVERFLOW_MARKER to be compiled to
   understand XCOFF64 files without source code changes. */
#ifdef __XCOFF_32_64__
#define	SCNHSZ_64		sizeof(SCNHDR_64)
#define _OVERFLOW_MARKER_64	(4294967295)
#else
#define	SCNHSZ			sizeof(SCNHDR)
#define _OVERFLOW_MARKER	(4294967295)
#endif

#endif /* __XCOFF64__ */

#else /* __XCOFF_HYBRID__ */

typedef struct scnhdr {
	char		s_name[8];	/* section name */
	union {
		struct {
			_ULONG32	_paddr;	/* physical address */
			_ULONG32	_vaddr;	/* virtual address */
			_ULONG32	_size;	/* section size */
			_LONG32		_scnptr;/* file ptr to scn's raw data */
			_LONG32		_relptr;/* file ptr to relocation */
			_LONG32		_lnnoptr;/* file ptr to line numbers */
			unsigned short	_nreloc;/* # of relocation entries */
			unsigned short	_nlnno;	/* # of line number entries */
			int		_flags;	/* flags */
		} _s32;
		struct {
			unsigned long long _paddr; /* physical address */
			unsigned long long _vaddr; /* virtual address */
			unsigned long long _size;  /* section size */
			long long	_scnptr; /* file ptr to scn's data */
			long long	_relptr; /* file ptr to RLDs */
			long long	_lnnoptr; /* file ptr to line numbers */
			unsigned int	_nreloc; /* # of relocation entries */
			unsigned int	_nlnno; /* # of line number entries */
			int		_flags;	/* flags */
		} _s64;
	} _u;
} SCNHDR;

#define s_paddr32	_u._s32._paddr
#define s_vaddr32	_u._s32._vaddr
#define s_size32	_u._s32._size
#define s_scnptr32	_u._s32._scnptr
#define s_relptr32	_u._s32._relptr
#define s_lnnoptr32	_u._s32._lnnoptr
#define s_nreloc32	_u._s32._nreloc
#define s_nlnno32	_u._s32._nlnno
#define s_flags32	_u._s32._flags

#define	SCNHSZ_32	(40)
#define _OVERFLOW_MARKER_32	(65535)

#define s_paddr64	_u._s64._paddr
#define s_vaddr64	_u._s64._vaddr
#define s_size64	_u._s64._size
#define s_scnptr64	_u._s64._scnptr
#define s_relptr64	_u._s64._relptr
#define s_lnnoptr64	_u._s64._lnnoptr
#define s_nreloc64	_u._s64._nreloc
#define s_nlnno64	_u._s64._nlnno
#define s_flags64	_u._s64._flags

#define	SCNHSZ_64	sizeof(SCNHDR)
#define _OVERFLOW_MARKER_64	(4294967295)

#endif  /* __XCOFF_HYBRID__ */

/*
 * Define constants for names of "special" sections
 */

#define _TEXT	".text"
#define _DATA	".data"
#define _BSS	".bss"
#define _TDATA	".tdata"
#define _TBSS	".tbss"
#define	_PAD	".pad"
#define	_INFO	".info"
#define _LOADER ".loader"
#define _TYPCHK ".typchk"
#define _DEBUG	".debug"
#define _EXCEPT	".except"
#define _OVRFLO	".ovrflo"

/*
 * The low order 16 bits of s_flags is used as section "type"
 */

#define STYP_REG	0x00	/* "regular" section */
#define STYP_PAD	0x08	/* "padding" section */
#define	STYP_TEXT	0x20	/* section contains text only */
#define STYP_DATA	0x40	/* section contains data only */
#define STYP_BSS	0x80	/* section contains bss only */
#define STYP_EXCEPT	0x0100	/* Exception section */
#define STYP_INFO	0x0200	/* Comment section */
#define STYP_TDATA	0x0400	/* Thread-local data section */
#define STYP_TBSS	0x0800	/* Thread-local bss section */
#define STYP_LOADER	0x1000	/* Loader section */
#define STYP_DEBUG	0x2000	/* Debug section */
#define STYP_TYPCHK	0x4000	/* Type check section */
#define STYP_OVRFLO	0x8000	/* Overflow section header 
				   for handling relocation and 
				   line number count overflows */

#ifdef __cplusplus
}
#endif

#endif /* _H_SCNHDR */
