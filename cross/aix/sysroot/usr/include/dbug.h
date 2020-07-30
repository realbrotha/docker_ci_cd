/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/dbug.h 1.5                                  */
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
/* @(#)70	1.5  src/bos/usr/include/dbug.h, cmdld, bos530 2/4/97 08:32:15 */
#ifndef _H_DBUG
#define _H_DBUG
/*
 * COMPONENT_NAME: cmdld
 *
 * ORIGINS: 27
 *
 */

#include <xcoff32_64.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
   The XCOFF .debug section contains the symbolic debugger stabstrings.
   No C-language structures are defined for stabstrings.

   Each string in the .debug section consists of a length field followed
   by a null-terminated string.  References from the symbol table into
   the .debug section are offsets within the .debug section to the first
   byte of the appropriate stabstring, not its length field. Stabstrings
   may contain embedded null characters, so the length field should be
   used to determine how long each stabstring is.  The length includes the
   terminating null byte. Multiple symbol table entries may point to a
   single stabstring in the .debug section.

   Macros are defined in this file to simplify writing code to process
   stabstrings in both XCOFF32 and XCOFF64 object files.

   Basic names:
	_STABSTRING_LEN    _STABSTRING_LEN_TYPE

   Names defined when both __XCOFF32__ and __XCOFF64__ are defined:
	_STABSTRING_LEN    _STABSTRING_LEN_TYPE
	_STABSTRING_LEN_64 _STABSTRING_LEN_TYPE_64

   Names defined when __XCOFF_HYBRID__ is defined:
	_STABSTRING_LEN_32 _STABSTRING_LEN_TYPE_32
	_STABSTRING_LEN_64 _STABSTRING_LEN_TYPE_64
   
 */

#ifdef __XCOFF32__
/* The length field of a stabstring is 2 bytes long.  Thus, stabstrings
   longer than 2^16-1 bytes must use multiple symbol table entries. */
#endif

#ifdef __XCOFF64__
/* The length field of a stabstring is 4 bytes long.  Thus, stabstrings
   longer than 2^32-1 bytes must use multiple symbol table entries. */
#endif

#if defined (__XCOFF_32__)
#	define _STABSTRING_LEN		(2)
#	define _STABSTRING_LEN_TYPE	unsigned short
#elif defined (__XCOFF_64__)
#	define _STABSTRING_LEN		(4)
#	define _STABSTRING_LEN_TYPE	unsigned int
#elif defined (__XCOFF_32_64__)
#	define _STABSTRING_LEN		(2)
#	define _STABSTRING_LEN_TYPE	unsigned short
#	define _STABSTRING_LEN_64	(4)
#	define _STABSTRING_LEN_TYPE_64	unsigned int
#else /* defined (__XCOFF_HYBRID__) */
#	define _STABSTRING_LEN_32	(2)
#	define _STABSTRING_LEN_64	(4)
#	define _STABSTRING_LEN_TYPE_32	unsigned short
#	define _STABSTRING_LEN_TYPE_64	unsigned int
#endif

#ifdef __cplusplus
}
#endif

#endif /* _H_DBUG */
