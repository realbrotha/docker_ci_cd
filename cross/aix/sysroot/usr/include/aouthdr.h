/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/usr/include/aouthdr.h 1.16.1.2                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)17       1.16.1.2  src/bos/usr/include/aouthdr.h, cmdld, bos53Q, q2008_19B0 4/22/08 10:19:41 */
#ifndef	_H_AHDR
#define _H_AHDR
/*
 * COMPONENT_NAME: cmdld
 *
 * STRUCTURES: aouthdr, aouthdr_64
 *
 * ORIGINS: 3, 27
 *
 */

#include <xcoff32_64.h>

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Define the auxiliary header of an XCOFF file.  In general, the auxiliary
   header can be any size, and the length of the auxiliary in any particular
   object file is specified in the f_opthdr field of the XCOFF header.

   Some AIX programs generate auxiliary headers for 32-bit object files that
   end after the data_start field.  The macro _AOUTHSZ_SHORT defines the
   length of such a header.  No auxiliary header is required for an object
   file that is not an executable.

   Executables, however, must have auxiliary headers that include the
   full structure definitions.  The macro _AOUTHSZ_EXEC defines the length
   the auxiliary header must have for an executable.

   In hybrid mode, the following names should be used:

   ============================================================================
   | Basic field or macro name  | 32-bit name          | 64-bit name          |
   ============================================================================
   | magic or o_mflag           | same                 | same                 |
   | vstamp or o_vstamp         | same                 | same                 |
   | tsize or o_tsize           | o_tsize32            | o_tsize64            |
   | dsize or o_dsize           | o_dsize32            | o_dsize64            |
   | bsize or o_bsize           | o_bsize32            | o_bsize64            |
   | entry or o_entry           | o_entry32            | o_entry64            |
   | text_start or o_text_start | o_text_start32       | o_text_start64       |
   | data_start or o_data_start | o_data_start32       | o_data_start64       |
   | o_toc                      | o_toc32              | o_toc64              |
   | o_snentry                  | same                 | same                 |
   | o_sntext                   | same                 | same                 |
   | o_sndata                   | same                 | same                 |
   | o_sntoc                    | same                 | same                 |
   | o_snloader                 | same                 | same                 |
   | o_snbss                    | same                 | same                 |
   | o_sntdata                  | o_sntdata32          | o_sntdata64          |
   | o_sntbss                   | o_sntbss32           | o_sntbss64           |
   | o_algntext                 | same                 | same                 |
   | o_algndata                 | same                 | same                 |
   | o_modtype                  | same                 | same                 |
   | o_cpuflag                  | same                 | same                 |
   | o_cputype                  | same                 | same                 |
   | o_maxstack                 | o_maxstack32         | o_maxstack64         |
   | o_maxdata                  | o_maxdata32          | o_maxdata64          |
   | o_debugger                 | o_debugger32         | o_debugger64         |
   | o_textpsize                | o_textpsize32        | o_textpsize64        |
   | o_datapsize                | o_datapsize32        | o_datapsize32        |
   | o_stackpsize               | o_stackpsize32       | o_stackpsize32       |
   | o_flags                    | o_flags32            | o_flags64            |
   | _AOUTHSZ_SHORT             | _AOUTHSZ_SHORT_32    | none                 |
   | _AOUTHSZ_EXEC              | _AOUTHSZ_EXEC_32     | _AOUTHSZ_EXEC_64     |
   ============================================================================
*/


#ifndef __XCOFF_HYBRID__

#ifdef __XCOFF32__

typedef	struct aouthdr {
	short	magic;		/* flags - how to execute		*/
				/* 0x010B: text & data may be paged	*/
	short	vstamp;		/* version stamp			*/
				/* 1 is only valid value		*/
	_LONG32	tsize;		/* text size in bytes			*/
	_LONG32	dsize;		/* data size in bytes			*/
	_LONG32	bsize;		/* bss size in bytes			*/
	_LONG32	entry;		/* entry point descriptor address	*/
	_ULONG32 text_start;	/* virtual address of beginning of text	*/
	_ULONG32 data_start;	/* virtual address of beginning of data	*/
	/* A short 32-bit auxiliary header can end here. */

	_ULONG32 o_toc;		/* address of TOC			*/
	short	o_snentry;	/* section number for entry point	*/
	short	o_sntext;	/* section number for text		*/
	short	o_sndata;	/* section number for data		*/
	short	o_sntoc;	/* section number for toc		*/
	short	o_snloader;	/* section number for loader		*/
	short	o_snbss;	/* section number for bss		*/
	short	o_algntext;	/* log (base 2) of max text alignment	*/
	short	o_algndata;	/* log (base 2) of max data alignment	*/
	char	o_modtype[2];	/* Module type field, 1L, RE, RO	*/
	uchar	o_cpuflag;	/* bit flags - cputypes of objects	*/
	uchar	o_cputype;	/* executable cpu type identification	*/
	_ULONG32 o_maxstack;	/* max stack size allowed (bytes)	*/
	_ULONG32 o_maxdata;	/* max data size allowed (bytes)	*/
	unsigned int o_debugger;/* Reserved for use by debugger if it	*/
				/* needs a location for a breakpoint.	*/
	uchar	o_textpsize;	/* size of pages for the exec text	*/
	uchar	o_datapsize;	/* size of pages for the exec data	*/
	uchar	o_stackpsize;	/* size of pages for the stack		*/
	uchar	o_flags;	/* Flags and .tdata alignment:		*/
				/* Bit 0: Set if TLS local-exec code was*/
				/*         generated.			*/
				/* Bits 1-3: Reserved--must be 0   	*/
				/* Bits 4-7: Max .tdata alignment (0-10)*/
	short	o_sntdata;	/* section number for tdata section */
	short	o_sntbss;	/* section number for tbss section */
} AOUTHDR;

#define _AOUTHSZ_SHORT		(size_t)&(((AOUTHDR *)0)->o_toc)
#define _AOUTHSZ_EXEC		sizeof(AOUTHDR)

#endif /* __XCOFF32__ */

#ifdef __XCOFF64__

typedef	struct _S_(aouthdr) {
	short	magic;		/* flags - how to execute		*/
				/* 0x010B: text & data may be paged	*/
	short	vstamp;		/* version stamp			*/
				/* 1 is only valid value		*/
	unsigned int o_debugger;/* Reserved for use by debugger if it	*/
				/* needs a location for a breakpoint.	*/
	unsigned long long text_start;	/* virtual address of text	*/
	unsigned long long data_start;	/* virtual address of data	*/
	unsigned long long o_toc; /* TOC address */
	short	o_snentry;	/* section number for entry point	*/
	short	o_sntext;	/* section number for text		*/
	short	o_sndata;	/* section number for data		*/
	short	o_sntoc;	/* section number for toc		*/
	short	o_snloader;	/* section number for loader		*/
	short	o_snbss;	/* section number for bss		*/
	short	o_algntext;	/* log (base 2) of max text alignment	*/
	short	o_algndata;	/* log (base 2) of max data alignment	*/
	char	o_modtype[2];	/* Module type field, 1L, RE, RO	*/
	unsigned char o_cpuflag;/* bit flags - cputypes of objects	*/
	unsigned char o_cputype;/* executable cpu type identification	*/
	uchar	o_textpsize;	/* size of pages for the exec text	*/
	uchar	o_datapsize;	/* size of pages for the exec data	*/
	uchar	o_stackpsize;	/* size of pages for the stack		*/
	uchar	o_flags;	/* Flags and .tdata alignment:		*/
				/* Bit 0: Set if TLS local-exec code was*/
				/*         generated.			*/
				/* Bits 1-3: Reserved--must be 0   	*/
				/* Bits 4-7: Max .tdata alignment (0-10)*/
	long long	tsize;	/* text size in bytes	*/
	long long	dsize;	/* data size in bytes	*/
	long long	bsize;	/* bss size in bytes	*/
	long long	entry;	/* entry point address */
	unsigned long long o_maxstack;	/* max stack size allowed */
	unsigned long long o_maxdata;	/* max data size allowed */
	short	o_sntdata;	/* section number for tdata section */
	short	o_sntbss;	/* section number for tbss section */
	int		o_resv3[3];	/* Reserved */
} _S_(AOUTHDR);

#ifdef __XCOFF32__
#define _AOUTHSZ_EXEC_64	sizeof(_S_(AOUTHDR))
#else
#define _AOUTHSZ_EXEC		sizeof(_S_(AOUTHDR))
#endif

#endif /* __XCOFF64__ */

/* Defines to provide the original COFF field names */
#define	o_tsize		tsize
#define	o_dsize		dsize
#define	o_bsize		bsize
#define	o_entry		entry
#define	o_text_start	text_start
#define	o_data_start	data_start

#else /* __XCOFF_HYBRID__ */

typedef	struct aouthdr {
	short	magic;		/* flags - how to execute		*/
				/* 0x010B: text & data may be paged	*/
	short	vstamp;		/* version stamp			*/
				/* 1 is only valid value		*/
	union {
	    int	_tsize32;	/* text size in bytes			*/
	    unsigned int _debugger64;/* Reserved for use by debugger if	*/
				/* it needs a location for a breakpoint.*/
	} _u2;

#define o_tsize32	_u2._tsize32
#define o_debugger64	_u2._debugger64

	union {
		struct {
			_LONG32	_dsize32; /* data size in bytes		*/
			_LONG32	_bsize32; /* bss size in bytes */
			_LONG32	_entry32; /* entry point descriptor address */
			_ULONG32 _text_start32; /* virtual addr of text */
			_ULONG32 _data_start32; /* virtual addr of data */
			/* A short 32-bit auxiliary header can end here. */
			_ULONG32 _toc32;/* address of TOC		*/
		} _s32;
		struct {
			unsigned long long _text_start64; /* addr of text */
			unsigned long long _data_start64; /* addr of data */
			unsigned long long _toc64; /* TOC addr */
		} _s64;
	} _u1;

#define o_dsize32	_u1._s32._dsize32
#define o_bsize32	_u1._s32._bsize32
#define o_entry32	_u1._s32._entry32
#define o_text_start32	_u1._s32._text_start32
#define o_data_start32	_u1._s32._data_start32
#define o_toc32		_u1._s32._toc32

#define o_text_start64	_u1._s64._text_start64
#define o_data_start64	_u1._s64._data_start64
#define o_toc64		_u1._s64._toc64

	short	o_snentry;	/* section number for entry point	*/
	short	o_sntext;	/* section number for text		*/
	short	o_sndata;	/* section number for data		*/
	short	o_sntoc;	/* section number for toc		*/
	short	o_snloader;	/* section number for loader		*/
	short	o_snbss;	/* section number for bss		*/
	short	o_algntext;	/* log (base 2) of max text alignment	*/
	short	o_algndata;	/* log (base 2) of max data alignment	*/
	char	o_modtype[2];	/* Module type field, 1L, RE, RO	*/
	uchar	o_cpuflag;	/* bit flags - cputypes of objects	*/
	uchar	o_cputype;	/* executable cpu type identification	*/
	union {
	    unsigned int _maxstack32; /* max stack size allowed (bytes)	*/
	    struct {
	    	uchar	_textpsize64;	/* size of pages for the exec text */
		uchar	_datapsize64;	/* size of pages for the exec data */
		uchar	_stackpsize64;	/* size of pages for the stack	*/
		uchar	_flags64;	/* Flags and .tdata alignment:	*/
				/* Bit 0: Set if TLS local-exec code    */
				/*         was generated.		*/
				/* Bits 1-3: Reserved--must be 0   	*/
				/* Bits 4-7: Max .tdata alignment (0-10)*/
	    } _s5;

	} _u5;
#define o_maxstack32	_u5._maxstack32
#define o_textpsize64	_u5._s5._textpsize64
#define o_datapsize64	_u5._s5._datapsize64
#define o_stackpsize64	_u5._s5._stackpsize64
#define o_flags64	_u5._s5._flags64
	union {
	    struct {
		_ULONG32 _maxdata32;	/* max data size allowed (bytes)*/
		unsigned int _debugger32;/* Reserved for use by debugger*/
				/* if it needs a location for a breakpoint.*/
	    } _u4;
	    long long	_tsize64;	/* text size in bytes		*/
	} _u3;

#define o_maxdata32	_u3._u4._maxdata32
#define o_debugger32	_u3._u4._debugger32
#define o_tsize64	_u3._tsize64

    union {
	long long	_dsize64;	/* data size in bytes	*/
	struct {
	    uchar	_textpsize32;	/* size of pages for the exec text */
	    uchar	_datapsize32;	/* size of pages for the exec data */
	    uchar	_stackpsize32;	/* size of pages for the stack	*/
	    uchar	_flags32;	/* Flags and .tdata alignment:	*/
				/* Bit 0: Set if TLS local-exec code was*/
				/*         generated.			*/
				/* Bits 1-3: Reserved--must be 0   	*/
				/* Bits 4-7: Max .tdata alignment (0-10)*/
	    short	_sntdata32;	/* section number for tdata section */
	    short	_sntbss32;	/* section number for tbss section */
	} _s6;
    } _u6;
#define o_dsize64	_u6._dsize64
#define o_textpsize32	_u6._s6._textpsize32
#define o_datapsize32	_u6._s6._datapsize32
#define o_stackpsize32	_u6._s6._stackpsize32
#define o_flags32	_u6._s6._flags32
#define o_sntdata32	_u6._s6._sntdata32
#define o_sntbss32	_u6._s6._sntbss32

	/* A 32-bit XCOFF executable must have an auxiliary header that
	   ends here. */
	long long	o_bsize64;	/* bss size in bytes	*/
	long long	o_entry64;	/* entry point address */
	unsigned long long o_maxstack64; /* max stack size allowed */
	unsigned long long o_maxdata64;	 /* max data size allowed */
	short	o_sntdata64;	/* section number for tdata section */
	short	o_sntbss64;	/* section number for tbss section */
	int		o_resv3[3];	 /* Reserved */
	/* A 64-bit XCOFF executable must have an auxiliary header the
	   full size. */
} AOUTHDR;

#define _AOUTHSZ_SHORT_32	(size_t)&(((_S_(AOUTHDR) *)0)->o_toc32)
#define _AOUTHSZ_EXEC_32	(size_t)&(((AOUTHDR *)0)->o_bsize64)
#define _AOUTHSZ_EXEC_64	sizeof(AOUTHDR)

#endif /* __XCOFF_HYBRID__ */

/* Defines to provide the original COFF field names */
#define	o_mflag		magic
#define	o_vstamp	vstamp

/*
 * Defines for the flags to identify characteristics of a collection
 * of object files link-edited together
 *	Bit-mapped field of the o_cpuflag field above
 */
#define	TOBJ_SAME	0x80	/* All object files have same cputype field. */
#define	TOBJ_COM	0x40	/* All object files are in a valid cputype */
				/*     subset. */
#define	TOBJ_EMULATE	0x20	/* One or more object files are of a  */
				/* cputype that would require emulated */
				/* instructions on the resultant cputype. */
				/* E.g., PWR objects promoted to PPC. */
#define	TOBJ_COMPAT	0x10	/* One or more object files are TCPU_ANY. */
				/* They have been ignored in determining */
				/* the resultant o_cputype value. */

/*
 * Defines for the POWER and PowerPC CPU Types 
 *    The o_cputype field above
 *    The n_cputype field of C_FILE symbol table entry
 */

#define TCPU_INVALID	0	/* Invalid id - assumes POWER for old objects */
#define TCPU_PPC	1	/* PowerPC common architecture 32 bit mode */
#define TCPU_PPC64	2	/* PowerPC common architecture 64 bit mode */
#define TCPU_COM	3	/* POWER and PowerPC architecture common */
#define TCPU_PWR	4	/* POWER common architecture objects */
#define TCPU_ANY	5	/* Mixture of any incompatable POWER */
				/* and PowerPC architecture implementations */
#define TCPU_601	6	/* 601 implementation of PowerPC architecture */
#define TCPU_603	7	/* 603 implementation of PowerPC architecture */
#define TCPU_604	8	/* 604 implementation of PowerPC architecture */
#define TCPU_PWR1	10	/* RS1 implementation of POWER architecture */
#define TCPU_620	16	/* 620  - PowerPC 64-bit architecture */
#define TCPU_A35	17	/* A35  - PowerPC 64-bit architecture */
#define TCPU_PWR5	18	/* PWR5 - PowerPC 64-bit architecture */
#define TCPU_970	19	/* PPC970 - PowerPC 64-bit architecture */
#define TCPU_PWR6	20	/* PWR6 - PowerPC 64-bit architecture */
#define TCPU_VEC	21	/* PowerPC 64-bit arch with Vector Extension */
#define TCPU_PWR5X      22      /* PWR5+ - PowerPC 64-bit architecture */
#define TCPU_PWR6E      23      /* PWR6E - PowerPC 64-bit architecture */
#define TCPU_PWRX	224	/* RS2 implementation of POWER architecture */

    /* Flags for o_flags */
#define _AOUT_TLS_LE	0x80	/* Module can only be main program because */
				/* TLS local-exec code was generated.    */
#define	_AOUT_ALGNTDATA 0xf

#ifdef __cplusplus
}
#endif

#endif	/* _H_AHDR */
