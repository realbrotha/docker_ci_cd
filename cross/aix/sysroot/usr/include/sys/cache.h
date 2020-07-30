/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/POWER/cache.h 1.7                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1993,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)70	1.7  src/bos/kernel/sys/POWER/cache.h, sysml, bos530 2/20/04 07:22:21 */

#ifndef _H_CACHE
#define _H_CACHE
#include <sys/types.h>

#ifdef _KERNEL

#ifdef _NO_PROTO
extern void _sync_cache_range();
#else
extern void _sync_cache_range(caddr_t eaddr, int32long64_t nbytes);
#endif

#ifdef _KERNSYS

extern void sync_cache_page_ppc(caddr_t raddr);
extern void inval_icache_page_ppc(caddr_t raddr);

#endif /* _KERNSYS */

#ifdef _NO_PROTO
extern int vm_cflush();
extern void cache_inval();
#else
extern int vm_cflush(caddr_t eaddr, int32long64_t nbytes);
extern void cache_inval(caddr_t eaddr, int nbytes);
#endif

#else /* _KERNEL */

#ifdef _NO_PROTO
extern void _sync_cache_range();
#else
extern void _sync_cache_range(caddr_t eaddr, int nbytes);
#endif

#endif /* _KERNEL */

#endif /* _H_CACHE */
