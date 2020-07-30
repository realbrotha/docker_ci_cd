/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/usr/include/pwd.h 1.13.1.17                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)29  1.13.1.17  src/bos/usr/include/pwd.h, libcs, bos53J, j2006_18B2 4/27/06 15:53:21 */

#ifdef _POWER_PROLOG_
/*
 * COMPONENT_NAME: (LIBCS) C Library Security Routines
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27,71
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */                                                                   

#endif /* _POWER_PROLOG_ */

/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */

#ifndef _H_PWD
#define _H_PWD

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifndef _H_TYPES
#include <sys/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* The POSIX standard requires that certain elements be included in pwd.h. 
 * It also requires that when _POSIX_SOURCE is defined, only those standard
 * specific elements are made available.  If _THREAD_SAFE is also defined,
 * thread-safe versions of the POSIX names are also made available.
 *
 * This header includes all the POSIX-required entries.
 */

#ifdef _POSIX_SOURCE

struct passwd {
	char	*pw_name;
	char	*pw_passwd;
	uid_t	pw_uid;
	gid_t	pw_gid;
	char    *pw_gecos;
	char	*pw_dir;
	char	*pw_shell;
};

#ifdef _NO_PROTO
	extern struct passwd	*getpwuid();
	extern struct passwd	*getpwnam();
#if _XOPEN_SOURCE_EXTENDED==1
	extern void				 endpwent();
	extern struct passwd	*getpwent();
	extern void				 setpwent();
#endif /* _XOPEN_SOURCE_EXTENDED */
#if (_XOPEN_SOURCE>=500) && !defined(_UNIX95)
	static int getpwuid_r(uid_t __aptr, struct passwd * __bptr, char * __cptr,
					size_t __dint, struct passwd ** __eptr)
	{
		extern int _posix_getpwuid_r();
		return(_posix_getpwuid_r(__aptr, __bptr, __cptr, __dint, __eptr));
	}
	static int getpwnam_r(const char * __fptr, struct passwd * __gptr,
					char * __hptr, size_t __iint, struct passwd ** __jptr)
	{
		extern int _posix_getpwnam_r();
		return(_posix_getpwnam_r(__fptr, __gptr, __hptr, __iint, __jptr));
	}
#else
#if defined(_THREAD_SAFE) && (_XOPEN_SOURCE_EXTENDED==1)
	extern int      getpwuid_r();
	extern int      getpwnam_r();
#endif
#endif /* _XOPEN_SOURCE>=500 */
#if defined(_THREAD_SAFE) && (((_XOPEN_SOURCE_EXTENDED==1) && !(_XOPEN_SOURCE>=500)) || defined(_ALL_SOURCE))
	extern void		endpwent_r();
	extern int		getpwent_r();
	extern int		setpwent_r();
#endif /* _XOPEN_SOURCE_EXTENDED  _THREAD_SAFE */
#else  /* _NO_PROTO */
	extern struct passwd	*getpwuid(uid_t);
	extern struct passwd	*getpwnam(const char *);
#if _XOPEN_SOURCE_EXTENDED==1
	extern void		endpwent(void);
	extern struct passwd	*getpwent(void);
	extern void		setpwent(void);
#endif /* _XOPEN_SOURCE_EXTENDED */
#if (_XOPEN_SOURCE>=500) && !defined(_UNIX95)
	static int getpwuid_r(uid_t __aptr, struct passwd *__bptr, char *__cptr,
						int __dint, struct passwd **__eptr)
	{
		extern int _posix_getpwuid_r(uid_t, struct passwd *, char *,
								int, struct passwd **);
		return(_posix_getpwuid_r(__aptr, __bptr, __cptr, __dint, __eptr));
	}
	static int getpwnam_r(const char *__fptr, struct passwd *__gptr,
					  char *__hptr, int __iint, struct passwd **__jptr)
	{
		extern int _posix_getpwnam_r(const char *, struct passwd *, char *,
						  int, struct passwd **);
		return(_posix_getpwnam_r(__fptr, __gptr, __hptr, __iint, __jptr));
	}
#else
#if defined(_THREAD_SAFE) && (_XOPEN_SOURCE_EXTENDED==1) 
	extern int	getpwuid_r(uid_t, struct passwd *, char *, int);
	extern int	getpwnam_r(const char *, struct passwd *, char *, int);
#endif
#endif /* _XOPEN_SOURCE>=500 */
#if defined(_THREAD_SAFE) && (((_XOPEN_SOURCE_EXTENDED==1) && !(_XOPEN_SOURCE>=500)) || defined(_ALL_SOURCE))
#ifndef _H_STDIO
#include <stdio.h>
#endif
	extern void	endpwent_r(FILE **);
	extern int	getpwent_r(struct passwd *, char *, int, FILE **);
	extern int	setpwent_r(FILE **);
#endif /* _XOPEN_SOURCE_EXTENDED _THREAD_SAFE */
#endif /* _NO_PROTO */
#endif /* _POSIX_SOURCE */

#ifdef _ALL_SOURCE 

#ifndef _H_STDIO
#include <stdio.h>
#endif

#ifdef _NO_PROTO
	extern int		putpwent();
	extern struct passwd *	fgetpwent();
#ifdef _THREAD_SAFE
	extern int		fgetpwent_r();
#endif /*_THREAD_SAFE */
#else  /* _NO_PROTO */
	extern int		putpwent(struct passwd *, FILE *);
	extern struct passwd *	fgetpwent(FILE *);
#ifdef _THREAD_SAFE
	extern int	fgetpwent_r(FILE *, struct passwd *, char *, int);
#endif /* _THREAD_SAFE */

#endif /* _NO_PROTO */

#define pw_etc pw_gecos

#endif /* _ALL_SOURCE */ 

#ifdef __cplusplus
}
#endif

#endif /* _H_PWD */
