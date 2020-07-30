/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/pmzone.h 1.5.2.26                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)54       1.5.2.26  src/bos/kernel/sys/pmzone.h, sysproc, bos53D, d2004_49B2 11/19/04 15:39:19 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   ORIGIN: 27, 83
 *
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_PMZONE
#define _H_PMZONE

#include <sys/lock_def.h>
#include <sys/uthread.h>
#include <sys/thread.h>
#include <sys/proc.h>

/*
 *      A zone is a collection of fixed size blocks for which there
 *      is fast allocation/deallocation access.  Kernel routines can
 *      use zones to manage data structures dynamically, creating a zone
 *      for each type of data structure to be managed.
 *
 *      Note: The link word must be unused when the element is free. Any other
 *      words may be used even when the element is free (like p_stat which
 *      holds SNONE).
 */

#define PM_ZERO         0x00000001L     /* when allocated, an entry is zeroed */
#define PM_FIFO         0x00000002L     /* the allocation scheme is FIFO */
#define PM_GLOBAL       0x00000004L     /* pm_heap is in global memory */
#define PM_PROC         0x00000008L     /* pm_heap is pvproc type */
#define PM_THREAD       0x00000010L     /* pm_heap is pvthread type */
#define PM_PRIMARY      0x00000020L     /* 1st zone with affinity for srad */
#define PM_LAST         0x00000040L     /* last zone in global region */
#define PM_BIGZONE	0x00000080L	/* zone element is > 1 page; e.g.
					 * utzone, so pin only uthread size
					 */
  
#ifdef __64BIT_KERNEL
#define MAXCPUS_SRAD 128
#else
#define MAXCPUS_SRAD 64
#endif

typedef struct pm_heap {
	struct pm_heap  *next;  	/* points to secondary, if any */
	Simple_lock     lock;           /* zone lock */
	Simple_lock     pm_grow_lock;   /* per-srad lock only used in primary*/
	uint            lastin;         /* last freed entry */
	uint            highwater;      /* just beyond last used (monotonic) */
	uint            start;          /* beginning of the zone */
	uint            end;            /* just beyond end of the zone */
	uint		size;           /* size of an element */
	uint		link;           /* offset of link word in an element */
	uint	        flags;          /* zone flags */
	int  		affinity; 	/* primary zone affinity */
	unsigned long   base;           /* base address (PM_GLOBAL only) */
	char   		*highwater_addr; /* address of highwater mark for */
					/* global zones */
	char  		*free_common;   /* common free list for offnode frees*/
	struct pm_heap  *primary;     	/* primary zone for this heap */
	char  *free_anchor[MAXCPUS_SRAD];
					/* per cpu free list - one */
					/* per cpu on a given SRAD */
};

#ifndef _32KERMODE
#ifdef _KERNEL

/*
 * The number of bits it takes to represent a zone must be <= the number
 * of bits allowed for the zone in the index portion of PIDs and TIDs.
 * For simplicity, the same number of bits are used in PIDs, TIDs, and
 * zone IDs.
 */
#define PM_NUMSRAD_BITS TSRADSHIFT
#define PM_NUM_ZONES (1L<<PM_NUMSRAD_BITS)

typedef struct pm_heap_global {
	char *         start;          /* beginning of the zone */
	char *         end;            /* just beyond end of the zone */
	int            size;           /* size of an element */
	int            link;           /* offset of link word in an element */
	long           flags;          /* zone flags */
	long           zoneindex[PM_NUM_ZONES]; /* zone number by srad index */
	struct pm_heap  *primary[PM_NUM_ZONES]; /* pm zone per srad */
};

typedef uint32long64_t  pmbase_t;

/*
 * pvthread/pvproc data structures must be a power of two in size.
 * PM_TZONE_SHIFT is the log 2 of the size of each subzone of the
 * global pvthread region.  
 *
 * Each pvthread element is 2^8 on 64 bit kernel, or 2^7 on 32 bit kernel.
 * For 32 bit kernel, if we use a value of 2^22 for PM_TZONE_SHIFT, we get
 * 2^15 elements per sub-zone. 2^4 subzones will require 2^26 total memory.
 * For 64 bit kernel, if we use a value of 2^23 for PM_TZONE_SHIFT, we get
 * 2^15 elements per sub-zone. 2^4 subzones will require 2^27 total memory.
 *
 * On the 32 bit kernel, this is arranged from EA000000-EE000000.
 * This is a range of 4000000, or 2^26.  On the 64 bit kernel, we
 * have more than enough addressibility to accomodate the requirement.
 *
 * Each pvproc element is 2^10 on 64 bit kernel, or 2^9 on 32 bit kernel.
 * For 64 bit kernel, if we use a value of 2^24 for PM_PZONE_SHIFT,
 * we get 2^14 element per zone.  2^4 subzones will require 2^28
 * total memory, or a segment.
 * 
 * For 32 bit kernel, if we use a value of 2^23 for PM_PZONE_SHIFT,
 * we still get 2^14 elements per zone.  2^4 subzones will require 2^27
 * total memory, or a half a segment.
 * On the 32 bit kernel, this is arranged from E2000000-EA000000.
 * This is a range of 8000000, or 2^27.
 *
 * Note that the maximum number of threads is 2^19, while the maximum
 * number of procs is 2^18, so we need to have twice as many threads
 * in each subzone as we have procs in a subzone as long as we have the
 * same number of thread subzones as proc subzones.
 */

#define PM_TZONE_SHIFT  (15 + TV_LOGSIZE) /* log 2 of pvthread sub-zone size */
#define PM_PZONE_SHIFT  (14 + PV_LOGSIZE) /* log 2 of pvproc sub-zone size */
#define PM_LZONE_SHIFT  28 /* Each zone is within a segment for Local zones */

#define MAX_PM_TZONE   (1L << PM_TZONE_SHIFT)
#define MAX_PM_PZONE   (1L << PM_PZONE_SHIFT)
#define MAX_PM_LZONE   (1L << PM_LZONE_SHIFT)

#define PM_TZONE_OFFSET(_x) ((uint)(_x)  &  (MAX_PM_TZONE-1))
#define PM_PZONE_OFFSET(_x) ((uint)(_x)  &  (MAX_PM_PZONE-1))
#define PM_LZONE_OFFSET(_x) ((uint)(_x)  &  (MAX_PM_LZONE-1))
#define PM_TZONE_BASE(_x)   ((ulong)(_x) & ~(MAX_PM_TZONE-1))
#define PM_PZONE_BASE(_x)   ((ulong)(_x) & ~(MAX_PM_PZONE-1))
#define PM_LZONE_BASE(_x)   ((ulong)(_x) & ~(MAX_PM_LZONE-1))

#define PM_ZONE_OFFSET(_x,flags) ((flags & PM_GLOBAL)?  \
                                ((flags & PM_PROC) ? PM_PZONE_OFFSET(_x) : \
                                                     PM_TZONE_OFFSET(_x)) : \
                                PM_LZONE_OFFSET(_x) )

/* 
 * The following checks are added to ensure that programmers don't change 
 * the various constants that make up the PM_xZONE_SHIFT macros without
 * understanding the other changes that are needed.  Some of the changes are 
 * outlined in the comments above.  Those comments must change, and the pvproc and
 * pvthread regions must be expanded to accomodate the larger element sizes
 * so that we don't unwittingly reduce the total number of threads or processes the
 * system supports.  In addition, if the pvthread or pvproc sub-zones grow on the
 * 64 bit kernel, the code that attaches these regions to their respective SRADs must 
 * be examined and changed, since vm_attach() has a maximum span of one segment.
 * This is done in pm_init_global() and pm_init_global_dr().
 */
struct zonesizevaliditycheck {
#ifdef __64BIT_KERNEL
        char    a[(PM_TZONE_SHIFT == 23) ? 1 : -1];
        char    b[(PM_PZONE_SHIFT == 24) ? 1 : -1];
#else
        char    a[(PM_TZONE_SHIFT == 22) ? 1 : -1];
        char    b[(PM_PZONE_SHIFT == 23) ? 1 : -1];
#endif
};

/*
 * ZONE_BASE(pm_zone *zone)
 * returns the effective base address for a zone
 */
#define ZONE_BASE(_z) ( \
	((_z)->flags & PM_GLOBAL) ?     (_z)->base : \
	                                PM_LZONE_BASE(_z))

extern struct pm_heap_global pvproc_cb;
extern struct pm_heap_global pvthread_cb;

struct pvproc *get_next_pvproc(struct pvproc *);
struct pvthread *get_next_pvthread(struct pvthread *);
struct pvproc *get_next_pvproc_srad(struct pvproc *,sradid_t);
struct pvthread *get_next_pvthread_srad(struct pvthread *,sradid_t);

void pm_balance(void);
int pm_validate_slot(long, long);
int pm_init(struct pm_heap *zone, char *start, char *end, uint size,
            uint link, short _class, uint occurrence, long flags);
void pm_release(struct pm_heap *zone);
void pm_free(struct pm_heap *zone, char *element);
void pm_zero(char *block, int size);
char *pm_alloc(struct pm_heap *zone, ut_error_t *error);
char *pm_alloc_srad(struct pm_heap *zone, ut_error_t *error, int node);
char *pm_allocext(struct pm_heap *zone1, struct pm_heap *zone2, char * elem,
	          ut_error_t *error);

void pm_init_global(struct pm_heap_global *global_zone, 
		    short _class, short occurrence);
void pm_free_global(struct pm_heap_global *global_zone, char *element);
char *pm_alloc_global(struct pm_heap_global *global_zone,
	              ut_error_t *error, sradid_t target_srad);

#ifdef __64BIT_KERNEL
#define pm_alloc_local(n, node)	xmalloc_srad((n), 7, pinned_heap, (node))
#define pm_free_local(n)	xmfree((n), pinned_heap)
#else
#define pm_alloc_local(n, node)	xmalloc((n), 7, pinned_heap0)
#define pm_free_local(n)	xmfree((n), pinned_heap0)
#endif

#define round_down(addr,size)   (char *)((pmbase_t)(addr) & ~(size-1))
#define round_up(addr,size)     round_down((pmbase_t)(addr)+(size)-1,(size))
#endif

#endif  /* !_32KERMODE */
#endif  /* _H_PMZONE */
