/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/alloc/ldata.h 1.4.1.1                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)56  1.4.1.1  src/bos/kernel/alloc/ldata.h, sysalloc, bos53L, l2007_08B9 2/9/07 16:16:23 */

#ifndef _h_LDATA
#define _h_LDATA

#ifdef _KERNEL
#include <sys/types.h>

/* handle for an LData Pool */
typedef void * ldata_t;

/* exported ldata kernel services */
int ldata_create(size_t, long, long, ulong, ldata_t *);
void * ldata_alloc(ldata_t);
void ldata_free(ldata_t, void *);
int ldata_grow(ldata_t, long);
void ldata_destroy(ldata_t);

#ifdef _KERNSYS
void ldata_init(void);
#endif /*_KERNSYS */

#endif /* _KERNEL */
#endif /* _h_LDATA */
