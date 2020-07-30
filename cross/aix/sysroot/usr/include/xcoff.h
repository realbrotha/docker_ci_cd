/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/xcoff.h 1.6                                 */
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
/* @(#)51	1.6  src/bos/usr/include/xcoff.h, cmdld, bos530 2/4/97 08:38:53 */
#ifndef _H_XCOFF
#define _H_XCOFF
/*
 * COMPONENT_NAME: cmdld
 *
 * STRUCTURES: struct xcoffhdr
 *
 * ORIGINS: 3, 27
 *
 */
 /*		eXtended Common Object File Format

	File Organization:

	_________________________________________	INCLUDE FILE
	|_______________HEADER_DATA_____________|
	|					|
	|	File Header			|	"filehdr.h"
	|.......................................|
	|					|
	|	Auxilliary Header Information	|	"aouthdr.h"
	|_______________________________________|
	|	".text" section header		|	"scnhdr.h"
	|.......................................|
	|	".data" section header		|	''
	|.......................................|
	|	".bss" section header		|	''
	|.......................................|
	|	".loader" section header	|	''
	|.......................................|
	|	".typchk" section header	|	''
	|.......................................|
	|	".debug" section header		|	''
	|.......................................|
	|	".except" section header	|	''
	|.......................................|
	|	".info" section header		|	''
	|_______________________________________|
	|______________RAW_DATA_________________|
	|	".text" section data		|
	|.......................................|
	|	optional ".pad" section data	|
	|		(file alignment)	|
	|.......................................|
	|	".data" section data		|
	|.......................................|
	|	".loader" section data		|	"loader.h"
	|.......................................|
	|	".typchk" section data		|	"typchk.h"
	|.......................................|
	|	".debug" section data		|	"dbug.h"
	|.......................................|
	|	".except" section data		|	"exceptab.h"
	|.......................................|
	|	".info" section data		|
	|_______________________________________|
	|____________RELOCATION_DATA____________|
	|					|
	|	".text" section relocation data	|	"reloc.h"
	|					|
	|.......................................|
	|					|
	|	".data" section relocation data	|	''
	|					|
	|_______________________________________|
	|__________LINE_NUMBER_DATA_____________|
	|					|
	|	".text" section line numbers	|	"linenum.h"
	|					|
	|_______________________________________|
	|________________SYMBOL_TABLE___________|
	|					|
	|	".text", ".data" and ".bss"	|	"syms.h"
	|		section symbols		|	"storclass.h"
	|					|
	|_______________________________________|
	|________________STRING_TABLE___________|
	|					|
	|	long symbol names		|
	|_______________________________________|



		OBJECT FILE COMPONENTS

	STANDARD FILE:
			/usr/include/xcoff.h	

	HEADER FILES:				(included by <xcoff.h>)
			/usr/include/filehdr.h
			/usr/include/aouthdr.h
			/usr/include/scnhdr.h
			/usr/include/loader.h
			/usr/include/typchk.h
			/usr/include/dbug.h
			/usr/include/exceptab.h
			/usr/include/reloc.h
			/usr/include/linenum.h
			/usr/include/syms.h
			/usr/include/storclass.h (included by <syms.h>)

	COMPATIBLE FILE:
			/usr/include/a.out.h	(alternate to <xcoff.h>
						  includes <xcoff.h>)

 */

#include <xcoff32_64.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <filehdr.h>
#include <aouthdr.h>
#include <scnhdr.h>
#include <loader.h>
#include <typchk.h>
#include <dbug.h>
#include <exceptab.h>
#include <reloc.h>
#include <linenum.h>
#include <syms.h>

/*
   The 'struct xcoffhdr' can be used to simplify accessing the XCOFF
   and auxiliary headers.

   In hybrid mode, the following names should be used:

   ============================================================================
   | Basic field or macro name  | 32-bit name          | 64-bit name          |
   ============================================================================
   | filehdr                    | same                 | same                 |
   | aouthdr                    | aouthdr32 **         | aouthdr64            |
   ============================================================================

   ** Note that aouthdr32 cannot be used the same way as aouthdr64.

   If 'foo' is a pointer to a 'structure xcoffhdr', you can access a field
   in the auxiliary header with the following expressions:

   foo->aouthdr64.o_sntext		XCOFF64 file
   aouthdr32(foo)->o_sntext		XCOFF32 file

*/
#ifndef __XCOFF_HYBRID__

#ifdef __XCOFF32__
struct xcoffhdr
{
	struct filehdr	filehdr;
	struct aouthdr	aouthdr;
};
#endif

#ifdef __XCOFF64__
struct _S_(xcoffhdr) {
	struct _S_(filehdr)	filehdr;
	struct _S_(aouthdr)	aouthdr;
};
#endif

#else /* __XCOFF_HYBRID__ */

struct xcoffhdr
{
	struct filehdr	filehdr;
	struct aouthdr	aouthdr64;
};
#define aouthdr32(v) ((struct aouthdr *)((char *)&(v) + FILHSZ_32))

#endif /* __XCOFF_HYBRID__ */

#ifdef __cplusplus
}
#endif

#endif	/* _H_XCOFF */
