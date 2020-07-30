/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _STDIO_IMPL_H
#define	_STDIO_IMPL_H

#pragma ident	"@(#)stdio_impl.h	1.14	04/06/17 SMI"

#include <sys/isa_defs.h>

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	_LP64

#ifndef	_FILE64_H

struct __FILE_TAG {
	long	__pad[16];
};

#endif	/* _FILE64_H */

#else

struct __FILE_TAG	/* needs to be binary-compatible with old versions */
{
#ifdef _STDIO_REVERSE
	unsigned char	*_ptr;	/* next character from/to here in buffer */
	int		_cnt;	/* number of available characters in buffer */
#else
	int		_cnt;	/* number of available characters in buffer */
	unsigned char	*_ptr;	/* next character from/to here in buffer */
#endif
	unsigned char	*_base;	/* the buffer */
	unsigned char	_flag;	/* the state of the stream */
	unsigned char	_file;	/* UNIX System file descriptor */
	unsigned	__orientation:2; /* the orientation of the stream */
	unsigned	__ionolock:1;	/* turn off implicit locking */
	unsigned	__seekable:1;	/* is file seekable? */
	unsigned	__filler:4;
};

#endif	/*	_LP64	*/

#ifdef	__cplusplus
}
#endif

#endif	/* _STDIO_IMPL_H */
