/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/dlfcn.h 1.13                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)86       1.13  src/bos/usr/include/dlfcn.h, libld, bos530 4/30/04 15:22:24 */
/*
 *   COMPONENT_NAME: libld
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_DLFCN
#define _H_DLFCN

#include <standards.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Dynamic loading and symbol routines.
 */
#ifdef _NO_PROTO

extern void	*dlopen();
extern void	*dlsym();
extern int	dlclose();
extern char	*dlerror();

#else

extern void	*dlopen(const char *, int);
extern void	*dlsym(void *__restrict__, const char *__restrict__);
extern int	dlclose(void *);
extern char	*dlerror(void);

#endif

/* Values for the flags field to dlopen().
 * One of RTLD_NOW or RTLD_LAZY (same as NOW) must be specified
 * on all calls.  You may logically or in any number
 * of the other values.
 */
#define	RTLD_NOW		0x00000002 /* Load object and dependents now. */
#define	RTLD_LAZY		0x00000004 /* Load object and dependents when
					      symbol is referenced (not
					      implemented) */

#define	RTLD_GLOBAL		0x00010000 /* Make symbols in this module
					      visible to other dlopens. */
#ifdef _ALL_SOURCE
#define	RTLD_NOAUTODEFER	0x00020000 /* Do not allow subsequent loads
					      to satisfy deferred imports
					      in this module. */
#define	RTLD_MEMBER		0x00040000 /* Module name may indicate
					      archive member. */
#endif
#define	RTLD_LOCAL		0x00080000 /* Make symbols in this module
					      private. */
#define	RTLD_DEFAULT	    ((void *)(-1)) /* start dlsym() symbol search from
					      the executable module. */
#define	RTLD_MYSELF	    ((void *)(-2)) /* start dlsym() symbol search from
					      the module calling dlsym(). */
#define	RTLD_NEXT	    ((void *)(-3)) /* start dlsym() symbol search from
					      the module after the module
					      which called dlsym(). */
#define	RTLD_ENTRY    ((const char *)(-1)) /* return the module's entry point
					      from dlsym(). */
#ifdef _ALL_SOURCE
#define	RTLD_UNIX_LATEST	0x00100000 /* Use the latest version of the
					      kernel name space (default is
					      exec name space, which may be
					      different) on dlopen("/unix") */
#endif

#ifdef	__cplusplus
}
#endif

#endif /* _H_DLFCN */
