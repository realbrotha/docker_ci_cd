/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53E src/bos/usr/include/filehdr.h 1.19                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)78     1.19  src/bos/usr/include/filehdr.h, cmdld, bos53E, e2005_28C1 4/13/05 12:52:11 */
#ifndef	_H_FHDR 
#define _H_FHDR
/*
 * COMPONENT_NAME: cmdld
 *
 * STRUCTURES: filehdr, filehdr_64
 *
 * ORIGINS: 3, 27
 *
 */

#include <xcoff32_64.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Define the XCOFF header for both 32- and 64-bit XCOFF formats.

   In hybrid mode, the following names should be used:

   ============================================================================
   | Basic field or macro name  | 32-bit name          | 64-bit name          |
   ============================================================================
   | f_magic                    | same                 | same                 |
   | f_nscns                    | same                 | same                 |
   | f_timdat                   | same                 | same                 |
   | f_symptr                   | f_symptr32           | f_symptr64           |
   | f_nsyms                    | f_nsyms32            | f_nsyms64            |
   | f_opthdr                   | same                 | same                 |
   | f_flags                    | same                 | same                 |
   | FILHSZ                     | FILHSZ_32            | FILHSZ_64            |
   ============================================================================
*/
#ifndef __XCOFF_HYBRID__

#ifdef __XCOFF32__

typedef struct filehdr {
	unsigned short	f_magic;	/* magic number */
					/* Target machine on which the
					   object file is executable */
	unsigned short	f_nscns;	/* number of sections */
	_LONG32		f_timdat;	/* time & date stamp:
					   A value of 0 indicates no timestamp.
					   Negative values are reserved for
					   future use and should be treated
					   as 0. */
	_LONG32		f_symptr;	/* File offset to symbol table. */
	_LONG32		f_nsyms;	/* Number of symbol table entries:
					   Negative values are reserved for
					   future use and should be treated
					   as 0. */
	unsigned short	f_opthdr;	/* Size of the auxiliary header */
	unsigned short	f_flags;	/* flags */
} FILHDR;

#endif /* __XCOFF32__ */

#ifdef __XCOFF64__

typedef struct _S_(filehdr) {
	unsigned short	f_magic;	/* magic number */
					/* Target machine on which the
					   object file is executable */
	unsigned short	f_nscns;	/* number of sections */
	int		f_timdat;	/* time & date stamp:
					   A value of 0 indicates no timestamp.
					   Negative values are reserved for
					   future use and should be treated
					   as 0. */
	long long	f_symptr;	/* File offset to symbol table. */
	unsigned short	f_opthdr;	/* Size of the auxiliary header */
	unsigned short	f_flags;	/* flags */
	int		f_nsyms;	/* Number of symbol table entries:
					   Negative values are reserved for
					   future use and should be treated
					   as 0. */
} _S_(FILHDR);

#ifdef __XCOFF32__
#define	FILHSZ_64	sizeof(FILHDR_64)
#endif

#endif /* __XCOFF64__ */

#define	FILHSZ	sizeof(FILHDR)

#else /* __XCOFF_HYBRID__ */

typedef struct filehdr {
	unsigned short	f_magic;	/* magic number */
					/* Target machine on which the
					   object file is executable */
	unsigned short	f_nscns;	/* number of sections */
	_LONG32		f_timdat;	/* time & date stamp:
					   A value of 0 indicates no timestamp.
					   Negative values are reserved for
					   future use and should be treated
					   as 0. */
	union {
		long long	_symptr64; /* File offset to symbol table. */
		struct {
			int	_symptr32;
			int	_nsyms32;
		} _s32;
	} _u;
#define f_symptr32	_u._s32._symptr32
#define f_nsyms32	_u._s32._nsyms32
#define f_symptr64	_u._symptr64

	unsigned short	f_opthdr;	/* Size of the auxiliary header */
	unsigned short	f_flags;	/* flags */
	int		f_nsyms64;	/* Number of symbol table entries:
					   Negative values are reserved for
					   future use and should be treated
					   as 0. */
} FILHDR;

#define FILHSZ_32 ((size_t)&(((FILHDR *)0)->f_nsyms64))
#define FILHSZ_64 sizeof(FILHDR)

#endif

/*
 *	Bits for f_flags: (Most were defined for original COFF)
 *
 *	F_RELFLG	relocation info stripped from file
 *	F_EXEC		file is executable (i.e., it has a loader section)
 *	F_LNNO		line numbers stripped from file
 *	F_LSYMS		local symbols stripped from file
 *	F_FDPR_PROF	File was profiled with FDPR
 *	F_FDPR_OPTI	File was reordered with FDPR
 *      F_DSA           file uses Dynamic Segment Allocation (32-bit only)
 *	F_DEP_1		Data Execution Protection bit 1
 *	F_LPTEXT	executable requires large pages for text
 *	F_LPDATA	executable requires large pages for data
 *	F_DYNLOAD	file is dynamically loadable and executable
 *				(equivalent to F_EXEC on AIX)
 *	F_SHROBJ	file is a shared object
 *	F_LOADONLY	file can be loaded by the system loader, but it is
 *			ignored by the linker if it is a member of an archive.
 *	F_DEP_2		Data Execution Protection bit 2
 *	F_VARPG		executable requests using variable size pages
 *	F_NONEXEC	read/write sections of the file are non-executable.
 *				(deprecated)
 *	F_AR16WR	this file has the byte ordering of an AR16WR machine
 *				(e.g. 11/70) (deprecated)
 *	F_AR32WR	this file has the byte ordering of an AR32WR machine
 *				(e.g. vax) (deprecated)
 *	F_AR32W		this file has the byte ordering of an AR32W machine 
 *				(e.g. S370,POWER,3b,maxi)
 *
 */

#define	F_RELFLG	0x0001
#define	F_EXEC		0x0002
#define	F_LNNO		0x0004
#define	F_LSYMS		0x0008
#define F_FDPR_PROF	0x0010
#define F_FDPR_OPTI	0x0020
#define F_DSA		0x0040
#define	F_DEP_1		0x0080
#define	F_VARPG		0x0100
#define F_LPTEXT	0x0400
#define F_LPDATA	0x0800
#define	F_DYNLOAD	0x1000
#define	F_SHROBJ	0x2000
#define	F_LOADONLY	0x4000
#define	F_DEP_2		0x8000

/* Deprecated f_flags - do not use */
#define	F_AR16WR	F_DEP_1
#define	F_NONEXEC	F_DEP_2
#define	F_AR32WR	F_VARPG

/* Unused f_flags values */
#define	F_AR32W		0x0200


#define DEP_SYSTEM	0	/* let the system determine protection      */
#define DEP_EXEMPT	1	/* execute permission in data required      */
#define DEP__SYSTEM	2	/* alias to system (DEP_SYSTEM)		    */
#define DEP_REQUEST	3	/* non-execute permission in data preferred */

#define DEP_FLAGS(f)	( (((f) & F_DEP_1) >>  7) \
			| (((f) & F_DEP_2) >> 14) )

/*
 *	Magic Numbers
 */

/* IBM POWER and PowerPC */
#define	U802TOCMAGIC	0737	/* readonly text segments and TOC */
#define	U803TOCMAGIC	0747	/* Obsolete 64-bit XCOFF--not used */
#define	U803XTOCMAGIC	0757	/* Discontinued AIX 64-bit XCOFF */
#define	U64_TOCMAGIC	0767	/* AIX 64-bit XCOFF */

/* Other magic numbers--not used on AIX */
#define	X386MAGIC	0514
#define	U802WRMAGIC	0730	/* writeable text segments */
#define	U802ROMAGIC	0735	/* readonly sharable text segments */

	/* IBM RT */
#define	U800TOCMAGIC	0637	/* readonly text segments and TOC */
#define	U800WRMAGIC	0630	/* writeable text segments */
#define	U800ROMAGIC	0635	/* readonly sharable text segments */

#ifdef __cplusplus
}
#endif

#endif	/* _H_FHDR  */
