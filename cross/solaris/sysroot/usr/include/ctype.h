/*	Copyright (c) 1988 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _CTYPE_H
#define	_CTYPE_H

#pragma ident	"@(#)ctype.h	1.35	04/09/28 SMI"

#include <iso/ctype_iso.h>
#include <iso/ctype_c99.h>

/*
 * Allow global visibility for symbols defined in
 * C++ "std" namespace in <iso/ctype_iso.h>.
 */
#if __cplusplus >= 199711L
using std::isalnum;
using std::isalpha;
using std::iscntrl;
using std::isdigit;
using std::isgraph;
using std::islower;
using std::isprint;
using std::ispunct;
using std::isspace;
using std::isupper;
using std::isxdigit;
using std::tolower;
using std::toupper;
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#if defined(__STDC__)

#if defined(__EXTENSIONS__) || \
	((!defined(_STRICT_STDC) && !defined(_POSIX_C_SOURCE)) || \
	defined(_XOPEN_SOURCE))

extern int isascii(int);
extern int toascii(int);
extern int _tolower(int);
extern int _toupper(int);

#endif /* defined(__EXTENSIONS__) || ((!defined(_STRICT_STDC) ... */

#if !defined(__lint)

#if defined(__EXTENSIONS__) || \
	((!defined(_STRICT_STDC) && !defined(_POSIX_C_SOURCE)) || \
	defined(_XOPEN_SOURCE)) || defined(__XPG4_CHAR_CLASS__)
#define	isascii(c)	(!(((int)(c)) & ~0177))
#define	toascii(c)	(((int)(c)) & 0177)
#if defined(__XPG4_CHAR_CLASS__) || defined(_XPG4)
#define	_toupper(c)	(__trans_upper[(int)(c)])
#define	_tolower(c)	(__trans_lower[(int)(c)])
#else
#define	_toupper(c)	((__ctype + 258)[(int)(c)])
#define	_tolower(c)	((__ctype + 258)[(int)(c)])
#endif /* defined(__XPG4_CHAR_CLASS__) || defined(_XPG4) */

#endif /* defined(__EXTENSIONS__) || ((!defined(_STRICT_STDC) ... */

#endif	/* !defined(__lint) */

#else	/* defined(__STDC__) */

#if !defined(__lint)

#define	isascii(c)	(!(((int)(c)) & ~0177))
#define	_toupper(c)	((_ctype + 258)[(int)(c)])
#define	_tolower(c)	((_ctype + 258)[(int)(c)])
#define	toascii(c)	(((int)(c)) & 0177)

#endif	/* !defined(__lint) */

#endif	/* defined(__STDC__) */

#ifdef	__cplusplus
}
#endif

#endif	/* _CTYPE_H */
