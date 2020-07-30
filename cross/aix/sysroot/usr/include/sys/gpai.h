/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53J src/bos/kernel/sys/gpai.h 1.15                                  */
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
/* @(#)21	1.15  src/bos/kernel/sys/gpai.h, syslfs, bos53J, j2006_22B5 6/1/06 17:01:21 */

#ifndef _H_GPAI
#define _H_GPAI

/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#include "sys/types.h"
#include "sys/lock_def.h"

#ifdef __64BIT_KERNEL
#include "sys/ltypes.h"
#include "sysinfo.h"

/*
 * Description of the extra word that is allocated along with each
 * gpai object.  If the object is on a free list, then this word is
 * a pointer to the next item on the free list.  If this object has
 * been allocated, then this word contains a magic number and a node
 * identifier to indicate which node specific free list it was allocated
 * from.
 */
typedef
union gpai_link {
	union gpai_link *n_free;	/* pointer to next free */
	struct {
		uint32		g_mag;	/* Magic to indicate allocated */
		sradid_t	g_srad;	/* srad identifier */
	} g_mag_id;
} gpai_link_t;

/*
 * Given a pointer to a GPAI item, determine what node it was allocated on
 */
#define GPAI_ITEM_TO_SRAD(gp) \
	((sradid_t) \
	((gpai_link_t *)((caddr_t)gp - sizeof(gpai_link_t)))->g_mag_id.g_srad)
#endif /* __64BIT_KERNEL */

/*
 * When an object is allocated from a gpai pool...
 * ... in 64-bit kernel, this is the g_mag field;
 * ... in 32-bit kernel, this value replaces the next pointer.
 */
#define GPAI_ALLOCATED_MAGIC 0x47504149	/* "GPAI" */

struct galloc
{
	/* The fields down to a_freeobj are set up with static */
	/* initialization before the call to gpai_init.        */
	ushort      a_osz;	    /* object size             */
	ushort      a_pas;          /* primary allocation size */
	/* The following fields are used for lock allocation   */
	/* and initialization.                                 */
	int         a_lkoffset;     /* offset in struct to per-struct lock *
				     * (a value of zero indicates no lock) */
	int         a_lktype;       /* lock type: 0=simple, 1=complex      */
	short       a_lkclass;      /* lock class for lock_alloc           */
#ifndef __64BIT_KERNEL
	short       a_lkoccur;      /* lock occurrence / allocation count  */
	/* The remaining fields are used at runtime.           */
	caddr_t     a_freeobj;      /* pointer to first free obj */
	caddr_t     a_sat;          /* allocation pool ptr */
	Simple_lock a_lock;         /* serialization lockword */
	uint        a_inuse;        /* number of objects currently in use  */
#else /* __64BIT_KERNEL */
	short       a_lkoccur;      /* lock occurrence */
	/* The remaining fields are used at runtime.           */
	char        a_cache_pad[112];  /* pad to cache line boundary */
	struct {
		gpai_link_t a_freeobj;      /* pointer to first free obj */
		caddr_t	    a_sat;          /* allocation pool ptr */
		Simple_lock a_lock;         /* serialization lockword */
		uint        a_inuse;        /* number of objects in use  */
		short       a_lkoccur;      /* lock occurrence */
		char        a_cache_pad[82];  /* pad to cache line boundary */
	} pnfl[MAXSRADS];
#endif /* __64BIT_KERNEL */
};

#ifdef __64BIT_KERNEL
#define objsize(x)	((ulong)((x)->a_osz)+sizeof(gpai_link_t))
#define freeobj(x,n)	((x)->pnfl[(n)].a_freeobj.n_free)
#else /* __64BIT_KERNEL */
#define objsize(x)      ((ulong)((x)->a_osz)+sizeof(caddr_t))
#define freeobj(x)      ((x)->a_freeobj)
#endif /* __64BIT_KERNEL */

/* Lock type defines */
#define GPA_SIMPLE	0
#define GPA_COMPLEX	1

/* gpai function prototypes */
void     gpai_init(struct galloc *);  /* pointer to allocation structure */

caddr_t *gpai_alloc(struct galloc *); /* pointer to allocation structure */

void     gpai_free(struct galloc *,   /* pointer to allocation structure */
		   void *);	      /* pointer to object to be freed   */

char    *gpai_srch(struct galloc *,   /* pointer to pool anchor */
		 int,                 /* specific type of object in list */
		 int,                 /* offset in bytes to type in object */
		 int (*)(),           /* pointer to caller's search routine */
		 void *);             /* pointer to search routine args */


#endif /* _H_GPAI */
