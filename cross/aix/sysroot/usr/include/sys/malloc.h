/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53A src/bos/kernel/sys/malloc.h 1.20                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)33	1.20  src/bos/kernel/sys/malloc.h, sysalloc, bos53A, a2004_33B4 6/28/04 17:00:18 */
/*
 * COMPONENT_NAME: (LIBCGEN) Standard C Library General Functions
 *
 * ORIGINS: 27
 *
 */
#ifndef _H_SYS_MALLOC
#define _H_SYS_MALLOC

#include <sys/types.h>
#include <sys/processor.h>

/* users of heaps declare them this way - so that we don't have to
 * recompile the world whenever the implementation of xmalloc changes
 */

typedef	void *	heapaddr_t;

#ifdef _KERNEL
/* init_heap initializes an area of memory as a heap. The
 * origin address, area, must be page aligned.  The size
 * is in bytes and need not be page aligned.  The minimum size
 * heap is log2 pagesize-3,  which for 4096 pages is 9 pages.
 * heaps are normally expected to be large.  The maximum
 * heap size is 2**32.  Heaps may cross segment boudaries, including
 * the 2**31 boundary.
 *
 * heapp is NULL when initializing a new heap.  If heapp is
 * provided, init_heap returns the heapaddr of the alternate
 * heap for the given heap.  In this case, area and size are ignored
 *
 * Heaps are managed internally with relative addresses.  Thus a segment
 * may be made addressable at different locations and heap calls used
 * to allocate and free storage.  Each call will use the current virtual
 * address of the heap and data.
 */
#ifndef _NO_PROTO
heapaddr_t
init_heap(caddr_t area,uint32long64_t size,heapaddr_t heapp);
heapaddr_t
init_srad_heaps(size_t srad_size, ulong flags, heapaddr_t *altheapp);
#else
heapaddr_t
init_heap();
heapaddr_t
init_srad_heaps();
#endif

/* allocate size bytes.  align specified the required alignment.  However,
 * all allocations are aligned at least to the next largest power of 2.
 * if size < PGSIZE and to a page otherwise - so align can be safely specified as 0.
 * It is a committed feature of the architecture that align 0 will always return
 * allignment to the next power of two, independent of implementation.
 * N.B. xmalloc does NOT clear storage which is allocated - initialize it yourself!
 * When xmalloc has been compiled with the DEBUG option, returned storage is set
 * to the value in xmalloc_pattern, which will normally be a value chosen to
 * break programs which fail to initialize correctly.
 */
#ifndef _NO_PROTO
void *
xmalloc(uint32long64_t size,uint align,heapaddr_t heapp);
#else
void *
xmalloc();
#endif

/* 
 * Same as xmalloc above, but allocate storage on a given srad (for NUMA
 * systems only). If passed an invalid srad number or non-NUMA heap,
 * xmalloc_srad will fail.
 */

#ifndef _NO_PROTO
void *
xmalloc_srad(long req_size,uint align,heapaddr_t heapp,sradid_t srad);
#else
void *
xmalloc_srad();
#endif

/* free a previously allocated piece of storage.  addr must be an address
 * returned by xmalloc.  When xmalloc has been compiled with the DEBUG option
 * freed storage is "ruined" by haveing the value of xmalloc_free copied into it
 */
#ifndef _NO_PROTO
int
xmfree(void * addr,heapaddr_t heapp);
#else
int
xmfree();
#endif

/* xmalloc debug/MODS query routine. possible return values are listed below.
 * Currently there are only two options: off and full. This may or may not
 * change in future releases.
 */
#define XMDBG_OFF  0
#define XMDBG_FULL 1 

#ifndef _NO_PROTO
int
xmdbg_query(void);
#else
int
xmdbg_query();
#endif

/* N.B. these symbols are now heapaddr_t's - so the correct calls are
 * as in the defines below.  Calls which pass &kernel_heap and &pinned_heap
 * will be (at least temporarally) supported - but please fix your code
 */

#define palloc(x,y)	xmalloc( x, y, kernel_heap )
#define malloc(x)	xmalloc( x, 0, kernel_heap )
#define free(x)		xmfree( x, kernel_heap )

#endif

extern heapaddr_t kernel_heap;
extern heapaddr_t pinned_heap;


#endif /* _H_SYS_MALLOC */
