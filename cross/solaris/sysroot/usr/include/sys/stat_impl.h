/*
 * Copyright 2003 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_STAT_IMPL_H
#define	_SYS_STAT_IMPL_H

#pragma ident	"@(#)stat_impl.h	1.4	03/12/04 SMI"

#include <sys/feature_tests.h>
#include <sys/types.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * The implementation specific header for <sys/stat.h>
 */

#if !defined(_KERNEL) || defined(_BOOT)

#if defined(__STDC__)

extern int fstat(int, struct stat *);
extern int stat(const char *_RESTRICT_KYWD, struct stat *_RESTRICT_KYWD);
#if !defined(__XOPEN_OR_POSIX) || defined(__EXTENSIONS__) || \
	defined(_ATFILE_SOURCE)
extern int fstatat(int, const char *, struct stat *, int);
#endif /* defined (_ATFILE_SOURCE) */

#if !defined(__XOPEN_OR_POSIX) || defined(_XPG4_2) || defined(__EXTENSIONS__)
extern int lstat(const char *_RESTRICT_KYWD, struct stat *_RESTRICT_KYWD);
extern int mknod(const char *, mode_t, dev_t);
#endif /* (!defined(__XOPEN_OR_POSIX) ... */

#else	/* !__STDC__ */

extern int fstat(), stat();

#if !defined(__XOPEN_OR_POSIX) || defined(__EXTENSIONS__) || \
	defined(_ATFILE_SOURCE)
extern int fstatat();
#endif

#if !defined(__XOPEN_OR_POSIX) || defined(_XPG4_2) || defined(__EXTENSIONS__)
extern int lstat(), mknod();
#endif /* !defined(__XOPEN_OR_POSIX)... */

#endif	/* !__STDC__ */

#endif /* !defined(_KERNEL) || defined(_BOOT) */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_STAT_IMPL_H */
