/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/lockf.h 1.10                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)91       1.10  src/bos/kernel/sys/lockf.h, syslfs, bos530 2/15/97 09:19:54 */
/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _H_LOCKF
#define _H_LOCKF

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if _XOPEN_SOURCE_EXTENDED==1

#ifdef _ALL_SOURCE
#ifndef S_ISGID
#include <sys/stat.h>
#endif
#define S_ENFMT S_ISGID
#endif

#define F_ULOCK 0       /* Unlock a previously locked region */
#define F_LOCK  1       /* Lock a region for exclusive use */
#define F_TLOCK 2       /* Test and lock a region for exclusive use */
#define F_TEST  3       /* Test region for other processes locks */

#ifdef _LARGE_FILES
#define lockf lockf64
#endif

#ifdef _NO_PROTO
extern int lockf();
#else
	extern int lockf (int, int, off_t);
#ifdef _LARGE_FILE_API
	extern int lockf64 (int, int, off64_t);
#endif	/* _LARGE_FILE_API */ 

#endif /* _NO_PROTO */

#endif /*_XOPEN_SOURCE_EXTENDED */

#ifdef __cplusplus
}
#endif
#endif /* _H_LOCKF */
