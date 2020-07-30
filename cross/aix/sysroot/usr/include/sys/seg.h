/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/sys/seg.h 1.73                                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)52     1.73  src/bos/kernel/sys/seg.h, sysvmm, bos53H, h2005_39C6 9/11/05 03:07:50 */
/*
 *   COMPONENT_NAME: (SYSVMM) Virtual Memory Manager
 *
 *   FUNCTIONS:
 *
 *   ORIGINS: 27, 83
 *
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */

#ifndef _H_SEG
#define _H_SEG

#include <sys/types.h>
#include <sys/inode.h>

#ifdef __cplusplus
/* avoid c++ compilers complaing about forward references
 */
struct shmid_ds;
#endif /* __cplusplus */

/*
 * Memory management addresses and bits
 */

#ifndef __64BIT_KERNEL
		/* extract sid from sreg value */
#define SRTOSID(srval) ( (srval) & 0xffffff )

		/* extract key from sreg value */
#define SRTOKEY(srval) ( ((srval) >> 30) & 0x1 )

/*
 * The SRVAL macro should only be used in the base kernel but the _KERNSYS
 * define wasn't used previously to enforce this.  Uses of SRVAL outside of
 * the base kernel continue to get the old definition.
 */
#ifdef _KERNSYS
extern int32long64_t key_value;
#define	SRVAL(sid,key,special)	( (sid) | ((key) ? key_value : 0) )
#else
#define SRVAL(sid,key,special)	( (sid) | (key) << 30 )
#endif /* _KERNSYS */

#else /* __64BIT_KERNEL */
#ifdef _KERNSYS
#define SRVAL(sid,key,special)	(vm_handle((vmid_t)(sid), (int32long64_t)(key)))
#endif /* _KERNSYS */
#endif /* !__64BIT_KERNEL */


/*
 * if changing L2SIDLIMIT  update NUM_SCBSIDS in vmdefs.h to reflect additional 
 * scb segments needed and reserve additional global kernel esid space in 
 * ipl64.exp.  note, 64bk L2SIDLIMIT is "VM_L2_MAXARCH_VSID-2".
 */
#ifdef __64BIT_KERNEL
#define L2SIDLIMIT      35
#define SIDMAX          ((1ULL << L2SIDLIMIT) - 1)
#else
#define L2SIDLIMIT      23
#define SIDMAX          ((1 << L2SIDLIMIT) - 1)
#endif


#define INVLSID         SIDMAX             /* generic invalid sid */
#define INVLVMID	((vmid_t)SIDMAX)
#ifndef __64BIT_KERNEL
#define INVLKVMID	((kvmid_t)SIDMAX)
#endif

#ifdef __64BIT_KERNEL
#define UNKNSID		(SIDMAX-2)
#define INVALIDSID(sid)		\
	((sid) == INVLSID || (sid) == RSVDSID || (sid) == UNKNSID)
#else /* __64BIT_KERNEL */
#define INVALIDSID(sid)	((sid) == INVLSID || (sid) == RSVDSID)
#endif /* __64BIT_KERNEL */

#define	NSEGS		16		    /* number of segment regs */
#define SEGSHIFT	28		    /* segment reg shift count */
#define SEGOFFSET(x)	(((ulong)(x))& 0x0fffffff) /* get segment offset */
/* segment number from eaddr or file offset  */
#define SEGNUMBER(x)    ((ulong)(((unsigned long long)(x))>>28))
#define	SEGSIZE		(1<<28)		    /* segment size */
#define NULLSEGID	INVLSID		    /* generic invalid sid */
#define NULLSEGVAL	SRVAL(NULLSEGID,0,0)   /* null segreg value */
#define KERNELSEGID	0x0		    /* kernel segment ID */
#define KERNELSEGVAL	SRVAL(KERNELSEGID,0,0) /* kernel segreg value */

/*
 *  This is a temporary situation until the loader is sorted out.
 */

/*
 *  BASE is lowest addr in seg, TOP is highest, 0x?FFFFFFF
 */
#define BASE(seg) ((seg)<<SEGSHIFT)
#define TOP(seg)  ((BASE((seg)+1))-1)
#define LASTLONG(seg)	((BASE(seg+1))-4)

#define	KERNELORG	0x00000000		/* kernel segment origin */
#define KERNELSEG	0			/* kernel segment register */
#define	KERNEXORG	0xE0000000		/* kernel extension seg org */
#define	KERNEXSEG	14			/* kernel extension seg reg */
#define KX2ORG		0x10000000		/* kernel ext seg 2 origin */
#define KX2SEG		1			/* kernel ext seg 2 register */
#define KX3ORG		0x30000000		/* kernel ext seg 3 origin */
#define KX3SEG		3			/* kernel ext seg 3 register */
#define	TEXTORG		0x10000000		/* text segment origin */
#define	TEXTSEG		1			/* text segment register */
   /* NOTE: PRIVSEG should eventually replace DATASEG */
#define PRIVSEG32       2
#ifndef __64BIT_KERNEL
#define PRIVORG 	0x20000000		/* private segment origin */
#define PRIVSEG 	2			/* private segment reg. */
#else
#ifdef _POWER
#define PRIVORG         0xf000000020000000ul    /* private seg origin */
#define PRIVSEG         0xf00000002ul           /* private esid */
#endif /* _POWER */
#endif /* __64BIT_KERNEL */

#define PRIVORG_LO 	0x20000000  		/* user privseg org */
#define PRIVSEG_LO 	2			/* user private esid */
#define	DATAORG		0x20000000		/* data segment origin */
#define	DATASEG		2			/* data segment register */
#define	STACKSEG	2			/* stack segment register */
#define	BDATASEG	3			/* big data segment number */
#define	BDATAORG	0x30000000		/* big data segment origin */
#define	BDATASEGMAX	11			/* max seg # for big data */
#define	TEMPORG		0xC0000000		/* temp segment origin */
#define	TEMPSEG		12			/* temp segment register */
#define	SHTEXTORG	0xD0000000		/* shared text segment origin */
#define	SHTEXTSEG	13			/* shared text seg reg */
#define DSASEGMAX	13			/* max segs for DSA apps */

#ifndef __64BIT_KERNEL
#define KTHREADORG	0xF0000000		/* kernel thread origin */
#define KTHREADSEG	15			/* kernel thread segment */
#else
#ifdef _POWER
#define KTHREADORG	0xF000000030000000ul	/* kernel thread origin */
#define KTHREADSEG	0xF00000003ul		/* kernel thread segment */
#endif /* _POWER */
#endif /* __64BIT_KERNEL */

#define	IOORG		0xF0000000		/* I/O bus origin */
#define	IOSEG		15			/* I/O segment register */
#define SHDATAORG	0xF0000000		/* shared data segment origin */
#define SHDATASEG	15			/* shared data seg reg */

#define MBUF1ORG 	(0x70000000)		/* mbuf seg 1 origin */
#define MBUFSEG1	(7)
#define MBUF2ORG 	(0x80000000)		/* mbuf seg 2 origin */
#define MBUFSEG2 	(8)
#define MBUF3ORG	(0x90000000)		/* mbuf seg 3 origin */
#define MBUFSEG3 	(9)
#define MBUF4ORG 	(0xA0000000)		/* mbuf seg 4 origin */
#define MBUFSEG4 	(10)


#ifdef __64BIT_KERNEL
#ifdef _POWER
extern unsigned long user_alias_addr;
extern unsigned long loader_alias_addr;

#define USERALIAS (user_alias_addr)
#define LOADERALIAS (loader_alias_addr)
#define USERALIAS_LO    (USERALIAS >> 28)    /* user alias on bridge machines*/
#define LOADERALIAS_LO  (LOADERALIAS >> 28)	/* loader alias start */
#endif /* _POWER */
#endif /* __64BIT_KERNEL */

#ifdef __64BIT_KERNEL
#define NEW_ADSPACE  0xF000                     /* sreg allocation bit vect */
#else
extern uint 		g_adspaceval;
#define NEW_ADSPACE 	(g_adspaceval)		/* sreg allocation bit vect */
#endif

/*
 *  Masks for creating segments.
 */
#define PRIV_SEG_OPTS	0x80000000	/* process private seg w/ key=R/W */
#define TEXT_SEG_OPTS	0x40000000	/* text seg */

#define READ_ACC    1	/** segment access   **/
#define WRITE_ACC   2


/*
 * The segstate struct is used by the shared memory services to mark
 * the usage of allocated segments.  Segments can be used for mapped
 * files or shared memory.
 *
 * For both mapped files and shared memory the following basic schemes
 * are used, for multiple esid mappings, which differ between the 
 * 32 and 64-bit kernels:
 *
 * 32-bit kernel -
 *     one segstate struct is allocated for each esid of the mapping.
 *     num_segs in the first segstate struct contains the number of 
 *     esids in the entire mapping. all other esids covering this
 *     mapping will have num_segs set to -1.
 *
 * 64-bit kernel -
 *     only one segstate struct is used for the entire mapping.
 *     num_segs contains the number of esids in the entire mapping.
 */

struct segstate {
	ushort	segflag;			/* type of segment	*/

#ifdef __64BIT_KERNEL
	ushort  uadflag;			/* info about uadnode use */
	uint    num_segs;			/* number of segments	*/
#else
	ushort  num_segs;			/* number of segments	*/
#endif /* __64BIT_KERNEL */

	union {
		uint             mfileno;	/* file descriptor	*/
		uint             attr;          /* attributes: SEG_WORKING */
		esid_t           nsegs;	        /* nsegs if SEG_AVAIL */

#ifdef __64BIT__
		/* for the 64bit kernel shmptr is an index & a 32-bit val */
		__ptr32          shmptr;	/* shared memory descriptor */
#else
#ifdef _KERNSYS
                struct shmid_ds_kernel *shmptr; /* shared memory descriptor */
#else
		struct shmid_ds *shmptr;        /* shared memory descriptor */
#endif /* _KERNSYS */
#endif

#ifndef __64BIT_KERNEL
		vmhandle_t      srval;	        /* unused field */
#endif  /* !__64BIT_KERNEL */
	} u_ptrs;
};

#define shm_ptr u_ptrs.shmptr
#define segfileno u_ptrs.mfileno
#define ss_attr  u_ptrs.attr
#define av_nsegs u_ptrs.nsegs

#ifndef __64BIT_KERNEL
#define	ss_srval u_ptrs.srval
#endif 

/*
 * segflag values
 */

#define SEG_AVAIL	0x0000		/* unused segment		*/
#define SEG_SHARED	0x0001		/* shared memory segment	*/
#define SEG_MAPPED	0x0002		/* mapped file			*/
#define SEG_MRDWR	0x0004		/* file mapped read write	*/
#define SEG_DEFER	0x0008		/* defered update		*/
#define SEG_MMAP	0x0010		/* mmap segment			*/
#define SEG_WORKING	0x0020		/* working storage		*/
#define SEG_RMMAP	0x0040		/* RMMAP region segment		*/
#define SEG_OTHER	0x0080		/* other segments		*/
#define SEG_EXTSHM	0x0100		/* extended shm segments     */ 
#define SEG_TEXT	0x0200		/* text or shared-lib code seg  */
#define SEG_RTSHM       0x0400          /* real time shared memory seg  */
#define SEG_RESERVE     0x0800          /* reserved for lw pool  */

#define SEGST_NSEGS(ssptr) ((ssptr)->segflag == SEG_AVAIL ? \
			    (ssptr)->av_nsegs : (ssptr)->num_segs)
/*
 * attr values
 * - currently the attr field is only valid for SEG_WORKING segments.
 *   there are cases where SEG_WORKING segments are treated as SEG_WORKING
 *   in most places, but the loader really has text in them.
 * Note that the attribute fields are defined from bit0, so as not to
 * conflict on a shm_insert() call with the segflags. (you can or these
 * together with 16-bit segflags). attr is a 16-bit field, really.
 */
#define SEGATTR_TEXT    0x40000000      /* segment has text in it       */

#ifdef _POWER
#define VM_MAXADDR	((unsigned)0x0fffffff)	/* max addr in units of 2**32 */
#define MAXSRNO64	((unsigned)0xffffffff)	/* max valid sreg number      */
                                        /* 64 bit max address */
#if defined(_LONG_LONG) && defined(_KERNEL)
#define VM_MAXADDR64    ((unsigned long long)(((1ull)<<60)-1))
#endif /* _LONG_LONG && _KERNEL */
#endif /* _POWER */

/* valid 32-bit address ?
 */
#ifdef _LONG_LONG
#define ISVALID32(a)	(((unsigned long long)(a) >> 32) ? 0 : 1)
#else
#ifdef __64BIT__
#define ISVALID32(a)	(((unsigned long)(a) >> 32) ? 0 : 1)
#else
#define ISVALID32(a)	(1)
#endif /* __64BIT__ */
#endif /* _LONG_LONG */

/* valid 64-bit address ?
 */
#if defined(_LONG_LONG) && defined(_KERNEL)
#define ISVALID64(a)	(((unsigned long long)(a) > VM_MAXADDR64) ? 0 : 1)
#endif /* _LONG_LONG && _KERNEL */

/* for 64-bit processes, the allocation status of its adspace from
 * the standpoint of segments is represented by a list of segnode
 * structures. a segnode represents a continguous range of segments
 * with both allocated and free space explicitly represented.
 */

struct segnode {
	snidx_t	sfwd;		/* index of next segnode */
	snidx_t sbwd;		/* index of previous segnode */
	esid_t	base;		/* segment number of first segstate entry */
	esid_t	last;		/* last segment number covered by node */
	short	nvalid;		/* number of valid entries in segst[] */
	short	flags;		/* status flags */
	struct segstate segst[16];  /* segment info */
};

/* segnodes are allocated in the user-private segment. note that
 * the sfwd and sbwd are array indices, rather than pointers. this
 * accomodates code which must compute on the segnodes of another
 * process. the first segnode always has index 0. and the list of
 * segnodes is kept in sort order by base address.
 */

/* u_adspace.
 * The data structure which represents the mapping from a 64-bit
 * address to an srval is a tree.  The tree has radix-4 (i.e.
 * each non-leaf node may have up to 16 children).  The leaves of
 * the tree contain adspace_t's (i.e. the srvals for 16 segments).
 * In general the tree is unbalanced, with the maximum number of
 * nodes between the root and a leaf equal to:
 *	- 8, for a 2**60 byte address space on the 32-bit kernel
 *	- 9, for a 2**64 byte address space on the 64-bit kernel
 *
 * struct uadnode is the declaration for a node in the tree.
 *
 * uadnodes are allocated in the user-private segment.  Note that the
 * childptr[] are array indices, rather than pointers, to facilitate
 * code which must compute on the tree of another process.  The root
 * always has index 0.
 *
 * The level indicates how much effective address space a node covers.
 * Each level covers 1 less nybble of effective address space (16
 * children or 16 vmhandles).  So the the levels cover the following
 * amount of process effective address space on the corresponding
 * kernel:
 *
 *		32bk	64bk
 * -------------------------
 * L0 node	2^60	2^64
 * L3 node	2^48	2^52
 * L5 node	2^40	2^44
 * L7 node	2^32	2^36
 * L8 node	n/a	2^32
 *
 *
 *	- Level 7 is all leafs on the 32-bit kernel, which goes
 *	  up to 2**60.
 *	- Level 8 is all leafs on the 64-bit kernel, which goes
 *	  to 2**64.
 *	- Level 0, which is required, is always the single root block
 *	  containing pointers
 *
 * The uad_clmask field determines whether a given entry is a pointer
 * to a child node, or a vmhandle_t.  Initial support for alternate
 * segment sizes is for 1TB segments only, for 64bk only.  These
 * segments would be at level 5.  The current plan for process
 * effective address space would mean that a node at level 5 is all
 * leaf (i.e. vmhandles) or all children.  This may change in the
 * future.
 */

struct uadnode {
	esid_t		uad_base;	/* first esid covered by node	*/
	int		uad_level;	/* see level discussion above	*/
#ifdef __64BIT_KERNEL
	ushort		uad_valid;	/* bitmask of valid bits	*/
	ushort		uad_clmask;	/* bitmask of leaf vs. child	*/
#endif /* __64BIT_KERNEL */
	adspace_t	uad_adsp;	/* also has uad_child indices
					 * overlapping the vmhandles.	*/
};

#define uad_alloc	uad_adsp.alloc
#define uad_srval	uad_adsp.srval
#define uad_child	uad_adsp.srval


#ifdef __64BIT_KERNEL
#define UAD_BIT(_idx)			(0x8000U >> (_idx))
#define uad_sub_isleaf(_uad,_idx)	((_uad)->uad_clmask & UAD_BIT(_idx))
#define uad_sub_isvalid(_uad,_idx)	((_uad)->uad_valid  & UAD_BIT(_idx))

#ifdef _KERNSYS
#define uad_set_leaf(_uad,_idx)		((_uad)->uad_clmask |= UAD_BIT(_idx))
#define uad_clr_leaf(_uad,_idx)		((_uad)->uad_clmask &=~UAD_BIT(_idx))
#define uad_set_valid(_uad,_idx)	((_uad)->uad_valid  |= UAD_BIT(_idx))

#define CHECK_LEAF_LEVEL(_uad, _l2ssize)			\
	ASSERT((_uad)->uad_level == VM_LEAFLEVEL(_l2ssize))
#endif /* KERNSYS */

struct uadnode_size_changed {
	char v[sizeof(struct uadnode) == 0x98 ? 1 : -1];
};

#else /* ... !__64BIT_KERNEL */

#define uad_sub_isleaf(_uad,_idx)	((_uad)->uad_level == VM_LEAFNODE)
#define uad_sub_isvalid(_uad,_idx)		\
	(uad_sub_isleaf((_uad),(_idx)) || (_uad)->uad_child[(_idx)] != 0)

#ifdef _KERNSYS
#define uad_set_leaf(_uad,_idx)		ASSERT(uad_sub_isleaf((_uad),(_idx)))
#define uad_set_valid(_uad,_idx)	ASSERT(uad_sub_isvalid((_uad),(_idx)))

#define CHECK_LEAF_LEVEL(_uad, _l2ssize)				\
	ASSERT( (_uad)->uad_level == VM_LEAFLEVEL(SEGSHIFT) )
#endif /* KERNSYS */

#ifndef __64BIT__
struct uadnode_size_changed {
	char v[sizeof(struct uadnode) == 0x4C ? 1 : -1];
};
#endif /* __64BIT__ */

#endif /* __64BIT_KERNEL */

/* Convert a index into the child/handle array into the corresponding
 * esid.
 */
#define uad_sub2esid(_uad,_k)		\
	((_uad)->uad_base + ((_k) << LOGNSIZE((_uad)->uad_level + 1)))

/* Convert an esid into the corresponding index.  This REQUIRES the
 * esid to be covered by the node, or it will produce an out-of-bounds
 * index.
 */
#define uad_esid2sub(_uad,_esid)	\
	(((_esid) - (_uad)->uad_base) >> LOGNSIZE((_uad)->uad_level + 1))

/* Last esid covered by a node, inclusive.
 */
#define uad_last_esid(_uad)		\
	((_uad)->uad_base + NODESIZE((_uad)->uad_level) - 1)

/* Determine if a given esid is described by this uadnode or its
 * children.
 */
#define uad_esid_covered(_uad,_esid)	\
	((_esid) >= (_uad)->uad_base && (_esid) <= uad_last_esid(_uad))

struct vmh_is_big_enough {
	char v[sizeof(vmhandle_t) >= sizeof(unidx_t) ? 1 : -1];
};

#ifdef __64BIT_KERNEL
/*
 * POWER
 *	For a 32-bit process there are 2 address ranges established in the
 *	uadnode tree -- one for the 4GB process address space and another
 *	for a loader alias of this same 4GB space.  
 * 
 *	These 2 spaces exist within the same 2**60 range; i.e
 *	the same level 0 child pointer, so an intermediate unode is required.
 */
#define NADNODES	4
#define NSEGNODES	2
#endif /* __64BIT_KERNEL */

/* NODESIZE(level) is the size in segments of a node at a level
 * in the u_adspace tree. note that level must be > 0. 
 * level = 0 is the root which has size 2**VM_ESIDBITS (not a 32-bit 
 * quantity).  On the 32-bit kernel, the result of NODESIZE will fit
 * in a 32-bit number since 0 is invalid input.
 *
 * A leaf has level = VM_LEAFLEVEL(l2ssize).
 */
#ifdef __64BIT_KERNEL
#define VM_LEAFLEVEL(_l2ssz)	(((64 - (_l2ssz)) / 4) - 1)
#define VM_ESIDBITS	(64 - SEGSHIFT)		/* #bits in an esid */
#else
#define VM_LEAFLEVEL(_l2ssz)	(((60 - (_l2ssz)) / 4) - 1)
#define VM_ESIDBITS	(60 - SEGSHIFT)		/* #bits in an esid */
#endif /* __64BIT_KERNEL */
#define VM_LEAFNODE		VM_LEAFLEVEL(SEGSHIFT)
#define LOGNSIZE(level) (VM_ESIDBITS - ((level) << 2))
#define NODESIZE(level) (1L << LOGNSIZE(level))


/* allocation of segnodes and uadnodes are from the user-private
 * segment. the control structure for both allocators is struct
 * asalloc and they are in struct user64.
 */
struct asalloc {
	void        *origin;	/* pointer to first element of array */
	vmnodeidx_t  freeind;	/* index of free array element, < 0 null */
	vmnodeidx_t  nextind;	/* next never used free index */
	vmnodeidx_t  maxind;	/* index of last element of array */
	vmnodeidx_t  hint;	/* allocation hint      */
	int	     size;	/* size of an array element */

};

/* options for as_getadsp64() */
#define VM_MAKEADSP  (1)
#define VM_FINDADSP  (2)
#define VM_MAKEKPROC (3)

/* type of attach/detach for as_att64, as_det64 */
#define LIGHTWEIGHT             (4)
#define HEAVYWEIGHT             (5)

/* options for findspace allocation.
 */
#define UREQUEST		(1)
#define UREQUEST_LOW		(2)
#define KREQUEST		(3)

/* flag for as_lw_pool_init */
#define LW_DEBUG                (1)

#endif /* _H_SEG */

