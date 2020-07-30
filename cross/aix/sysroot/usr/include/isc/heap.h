/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/isc/heap.h 1.3                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)10 1.3 src/bos/usr/include/isc/heap.h, sockinc, bos530 3/13/02 07:12:50 */
/*
 * Copyright (C) 1997-2001  Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM
 * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 * INTERNET SOFTWARE CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* $Id: heap.h,v 1.16 2001/01/09 21:56:57 bwelling Exp $ */
#ifndef BIND9
/*Use BIND8*/

typedef int (*heap_higher_priority_func)(void *, void *);
typedef void (*heap_index_func)(void *, int);
typedef void (*heap_for_each_func)(void *, void *);

typedef struct heap_context {
	int array_size;
	int array_size_increment;
	int heap_size;
	void **heap;
	heap_higher_priority_func higher_priority;
	heap_index_func index;
} *heap_context;

#define heap_new	__heap_new
#define heap_free	__heap_free
#define heap_insert	__heap_insert
#define heap_delete	__heap_delete
#define heap_increased	__heap_increased
#define heap_decreased	__heap_decreased
#define heap_element	__heap_element
#define heap_for_each	__heap_for_each

heap_context	heap_new(heap_higher_priority_func, heap_index_func, int);
int		heap_free(heap_context);
int		heap_insert(heap_context, void *);
int		heap_delete(heap_context, int);
int		heap_increased(heap_context, int);
int		heap_decreased(heap_context, int);
void *		heap_element(heap_context, int);
int		heap_for_each(heap_context, heap_for_each_func, void *);

#else
/*Use BIND9 */
#ifndef ISC_HEAP_H
#define ISC_HEAP_H 1

#include <isc/lang.h>
#include <isc/types.h>

ISC_LANG_BEGINDECLS

/*
 * The comparision function returns ISC_TRUE if the first argument has
 * higher priority than the second argument, and ISC_FALSE otherwise.
 */
typedef isc_boolean_t (*isc_heapcompare_t)(void *, void *);

typedef void (*isc_heapindex_t)(void *, unsigned int);
typedef void (*isc_heapaction_t)(void *, void *);

typedef struct isc_heap isc_heap_t;

isc_result_t	isc_heap_create(isc_mem_t *, isc_heapcompare_t,
				isc_heapindex_t, unsigned int, isc_heap_t **);
void		isc_heap_destroy(isc_heap_t **);
isc_result_t	isc_heap_insert(isc_heap_t *, void *);
void		isc_heap_delete(isc_heap_t *, unsigned int);
void		isc_heap_increased(isc_heap_t *, unsigned int);
void		isc_heap_decreased(isc_heap_t *, unsigned int);
void *		isc_heap_element(isc_heap_t *, unsigned int);
void		isc_heap_foreach(isc_heap_t *, isc_heapaction_t, void *);

ISC_LANG_ENDDECLS

#endif /* ISC_HEAP_H */

#endif /*BIND9 */
