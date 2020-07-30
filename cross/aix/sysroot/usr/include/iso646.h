/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/iso646.h 1.2                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)53       1.2  src/bos/usr/include/iso646.h, incstd, bos530 6/18/97 08:33:50 */
/*
 * COMPONENT_NAME: (INCSTD) Standard Include Files
 *
 * FUNCTIONS:
 * <iso646.h> -- macros for use in place of certain tokens that are
 * 	not expressible in the invariant subset of ISO 646:1991
 * 	complies with the following standard:
 * 		ANSI/ISO 9899:1993 MSE
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _H_ISO646
#define _H_ISO646

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _H_STANDARDS
#include <standards.h>
#endif

/*************************************************************************
	Notes:	The C standard has always required that the following
		trigraphs be supported in translation phase 1:
			??= mapped to #
			??( mapped to [
			??/ mapped to \
			??) mapped to ]
			??' mapped to ^
			??< mapped to {
			??! mapped to |
			??> mapped to }
			??- mapped to ~

		The forthcoming normative addendum to the C standard that
		requires conforming implementations to provide <iso646.h>
		also requires support in translation phases 3..4 for the
		following preprocessing tokens:
			%: alternate spelling for #
			%:%: alternate spelling for ##
		It also requires support in translation phases 3..7 for the
		following preprocessing tokens:
			<% alternate spelling for {
			%> alternate spelling for }
			<: alternate spelling for [
			:> alternate spelling for ]

		The C standard also requires that the "difficult" characters
		be somehow provided in both the basic source and execution
		character sets, regardless of the provision of trigraph,
		digraph, and macro alternatives for these characters.

		It is suggested that all C programmers avoid use of the
		following identifiers in their programs, in case somebody
		later needs to use <iso646.h> in maintaining the programs.
 **************************************************************************/

#define or	||
#define bitor	|
#define or_eq	|=
#define xor	^
#define xor_eq	^=
#define compl	~
#define and	&&
#define bitand	&
#define and_eq	&=
#define not	!
#define not_eq	!=

#ifdef __cplusplus
}
#endif

#endif /* _H_ISO646 */
