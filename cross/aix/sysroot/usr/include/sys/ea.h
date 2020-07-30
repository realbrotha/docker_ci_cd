/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/ea.h 1.2                                     */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2004               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)39       1.2  src/bos/kernel/sys/ea.h, syslfs, bos530 2/25/04 13:26:40 */

#ifndef _H_EA
#define _H_EA

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/stat.h>

/* exported extended attribute interface */

ssize_t getea(const char *, const char *, void *, size_t);
ssize_t lgetea(const char *, const char *, void *, size_t);
ssize_t fgetea(int, const char *, void *, size_t);

int setea(const char *, const char *, void *, size_t, int);
int lsetea(const char *, const char *, void *, size_t, int);
int fsetea(int, const char *, void *, size_t, int);

ssize_t listea(const char *, const char *, size_t);
ssize_t llistea(const char *, const char *, size_t);
ssize_t flistea(int, const char *, size_t);

int removeea(const char *, const char *);
int lremoveea(const char *, const char *);
int fremoveea(int, const char *);

struct stat;

int statea(const char *, const char *, struct stat64x *);
int lstatea(const char *, const char *, struct stat64x *);
int fstatea(int, const char *, struct stat64x *);

#ifdef __cplusplus
}
#endif

#endif /* _H_EA */
