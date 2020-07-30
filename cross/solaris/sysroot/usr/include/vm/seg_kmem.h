/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _VM_SEG_KMEM_H
#define	_VM_SEG_KMEM_H

#pragma ident	"@(#)seg_kmem.h	1.13	05/06/27 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/vmem.h>
#include <vm/as.h>
#include <vm/seg.h>
#include <vm/page.h>

/*
 * VM - Kernel Segment Driver
 */

#if defined(_KERNEL)

extern char *kernelheap;	/* start of primary kernel heap */
extern char *ekernelheap;	/* end of primary kernel heap */
extern char *heap_lp_base;	/* start of kernel large page heap arena */
extern char *heap_lp_end;	/* end of kernel large page heap arena */
extern struct seg kvseg;	/* primary kernel heap segment */
extern struct seg kvseg_core;	/* "core" kernel heap segment */
extern vmem_t *heap_lp_arena;	/* kernel large page heap arena */
extern vmem_t *heap_arena;	/* primary kernel heap arena */
extern vmem_t *hat_memload_arena; /* HAT translation arena */
extern struct seg kvseg32;	/* 32-bit kernel heap segment */
extern vmem_t *heap32_arena;	/* 32-bit kernel heap arena */
extern vmem_t *heaptext_arena;	/* kernel text arena, from heap */
extern struct ctx *kctx;	/* kernel context */
extern struct as kas;		/* kernel address space */
extern struct vnode kvp;	/* vnode for all segkmem pages */
extern int segkmem_reloc;	/* enable/disable segkmem relocatable pages */
extern vmem_t *static_arena;	/* arena for caches to import static memory */
extern vmem_t *static_alloc_arena;	/* arena for allocating static memory */

extern int segkmem_create(struct seg *);
extern page_t *segkmem_page_create(void *, size_t, int, void *);
extern void *segkmem_xalloc(vmem_t *, void *, size_t, int, uint_t,
	page_t *(*page_create_func)(void *, size_t, int, void *), void *);
extern void *segkmem_alloc(vmem_t *, size_t, int);
extern void *segkmem_alloc_permanent(vmem_t *, size_t, int);
extern void segkmem_free(vmem_t *, void *, size_t);

extern void *boot_alloc(void *, size_t, uint_t);
extern void boot_mapin(caddr_t addr, size_t size);
extern void kernelheap_init(void *, void *, char *, void *, void *);
extern void kernelheap_extend(void *, void *);
extern void segkmem_gc(void);

/*
 * Large page for kmem caches support
 */
typedef struct segkmem_lpcb {
	kmutex_t	lp_lock;
	kcondvar_t	lp_cv;
	uint_t		lp_wait;
	uint_t		lp_uselp;
	ulong_t		lp_throttle;

	/* stats */
	uint64_t	sleep_allocs_failed;
	uint64_t	nosleep_allocs_failed;
	uint64_t	allocs_throttled;
	uint64_t	allocs_limited;
	uint64_t	alloc_bytes_failed;
} segkmem_lpcb_t;

extern void	*segkmem_alloc_lp(vmem_t *, size_t *, int);
extern void	segkmem_free_lp(vmem_t *, void *, size_t);
extern int	segkmem_lpsetup(void);
extern void	segkmem_heap_lp_init(void);

extern size_t segkmem_lpsize;
extern size_t segkmem_heaplp_quantum;
extern size_t segkmem_kmemlp_max;

#define	SEGKMEM_USE_LARGEPAGES (segkmem_lpsize > PAGESIZE)

#define	IS_KMEM_VA_LARGEPAGE(vaddr)				        \
	(((vaddr) >= heap_lp_base) && ((vaddr) < heap_lp_end))

#endif	/* _KERNEL */

#ifdef	__cplusplus
}
#endif

#endif	/* _VM_SEG_KMEM_H */
