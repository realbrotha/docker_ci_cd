/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53A src/bos/usr/include/isc/memcluster.h 1.3                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1998,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)51	1.3  src/bos/usr/include/isc/memcluster.h, sockinc, bos53A, a2004_39D8 8/18/04 15:01:30 */
/*
 * Copyright (c) 1997,1999 by Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL INTERNET SOFTWARE
 * CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#ifndef MEMCLUSTER_H
#define MEMCLUSTER_H

#include <stdio.h>

#define meminit		__meminit
#ifdef MEMCLUSTER_DEBUG
#define memget(s)	__memget_debug(s, __FILE__, __LINE__)
#define memput(p, s)	__memput_debug(p, s, __FILE__, __LINE__)
#else /*MEMCLUSTER_DEBUG*/
#ifdef MEMCLUSTER_RECORD
#define memget(s)	__memget_record(s, __FILE__, __LINE__)
#define memput(p, s)	__memput_record(p, s, __FILE__, __LINE__)
#else /*MEMCLUSTER_RECORD*/
#define memget		__memget
#define memput		__memput
#endif /*MEMCLUSTER_RECORD*/
#endif /*MEMCLUSTER_DEBUG*/
#define memstats	__memstats
#define memactive	__memactive

int	meminit(size_t, size_t);
void *	__memget(size_t);
void 	__memput(void *, size_t);
void *	__memget_debug(size_t, const char *, int);
void 	__memput_debug(void *, size_t, const char *, int);
void *	__memget_record(size_t, const char *, int);
void 	__memput_record(void *, size_t, const char *, int);
void 	memstats(FILE *);
int     memactive(void);

#endif /* MEMCLUSTER_H */
