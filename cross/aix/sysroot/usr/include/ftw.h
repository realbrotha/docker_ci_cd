/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/ftw.h 1.15.1.3                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)08  1.15.1.3  src/bos/usr/include/ftw.h, libcgen, bos530 7/25/02 19:30:04 */

/*
 * COMPONENT_NAME: LIBCGEN
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *	Codes for the third argument to the user-supplied function
 *	which is passed as the second argument to ftw
 */
#ifndef _H_FTW
#define _H_FTW

#ifndef _H_STANDARDS
#include <standards.h>
#endif /* _H_STANDARDS */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _XOPEN_SOURCE

#ifndef _H_STAT
#include <sys/stat.h>
#endif /* _H_STAT */

#define	FTW_F	0	/* file */
#define	FTW_D	1	/* directory */
#define	FTW_DNR	2	/* directory without read permission */
#define	FTW_NS	3	/* unknown type, stat failed */

#if _XOPEN_SOURCE_EXTENDED==1 
#define FTW_SL    4	/* symlink points to existing file */
#define FTW_SLN   5	/* symlink points to non-existing file */
#define FTW_DP    6	/* directory with subdirs already visited */

                              /* For 4th Arg of nftw: */
#define FTW_PHYS  0x00000001  /* Physical Walk, does not follow symlinks */
#define FTW_MOUNT 0x00000002  /* Do not cross mount points */
#define FTW_DEPTH 0x00000004  /* Visit all sub-dirs B4 the directory itself */
#define FTW_CHDIR 0x00000008  /* Change to each dir before reading it */

struct FTW  {
	int base;
	int level;
};
#endif /* _XOPEN_SOURCE_EXTENDED or _XOPEN_SOURCE=500 */

#ifdef _LARGE_FILES
#define ftw ftw64
#define nftw nftw64
#endif /* _LARGE_FILES */

#ifdef _NO_PROTO
extern int ftw();
#if _XOPEN_SOURCE_EXTENDED==1
extern int nftw();
#endif /* _XOPEN_SOURCE_EXTENDED */
#else /* _NO_PROTO */
extern int ftw(const char *, int (*)(const char *,const struct stat *, int),
	       int);
#if _XOPEN_SOURCE_EXTENDED==1
extern int nftw(const char *, int (*)(const char *, const struct stat *, int, 
		struct FTW*), int, int);
#endif /* _XOPEN_SOURCE_EXTENDED */
#endif /* _NO_PROTO */

#endif /* _XOPEN_SOURCE */

#ifdef _ALL_SOURCE
extern int ftw64(const char *, int (*)(const char *,const struct stat64 *, int),
		 int);
extern int nftw64(const char *, int (*)(const char *, const struct stat64 *, int, 
					struct FTW*), int, int);
#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* _H_FTW */
