/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/pseg.h 1.13.2.20                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)42	1.13.2.20  src/bos/kernel/sys/pseg.h, sysproc, bos530 3/8/04 09:51:14 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 27, 83
 *
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */

#ifndef	_H_PSEG
#define	_H_PSEG

/*
 *	For AIX, most of the regions of a 32-bit process are packaged into
 *	a single virtual memory segment, called the process-private segment.
 *	This arrangement is convenient, and avoids wasting lots of address
 *	space giving each region a separate segment.  Other machines might
 *	not want to use this scheme.  Nothing fundamental depends on it.
 */

#include <sys/param.h>
#include <sys/user.h>
#include <sys/seg.h>

/*	The format of the process private segment (PRIVSEG) for
	a 32-bit process on the 32-bit kernel is as follows:

		 _______________________ _      	===
PRIVSEG	     -> | user r/w data and text| |     	   |
                |  u_dsize <= u_dmax    | |                |
		 -----------------------  |                |
		|	unused		| |                |
		 -----------------------  | U_STKDATA_SIZE = U_REGION_SIZE
		| stack for user mode	| |                |
		|  u_ssize <= u_smax	| |                |
USTACK_TOP   ->  -----------------------  |                |
ERRNO	     ->	| standard syscall errno| |                |
		 -----------------------  |                |
		| pointer to std errno  | |                |
        	 ======================= _ <-USRSTACK   ===
		| standard kernel stack |       --	   |
U_BLOCK	     ->  -----------------------  --	  | one    |
		| standard uthread block|   |	  | pinned |
		 -----------------------    |	  | page   | K_REGION_SIZE
		| user structure	|   |	--	   |
		| swappable proc info	|   | ublock	   |
		 -----------------------    |	  	   |
		| 64-bit user (unused)  |   |              |
               	 -----------------------  -- <-KLDRHEAPORG |
		| loader heap           |   |              |
		| (loader entries)      |   | KLDRHEAPSIZE |
SEGSIZE	     ->  -----------------------  --		=== 

        The format of the process private segment (PRIVSEG) for
	a 32-bit process on the 64-bit kernel is as follows:

		 _______________________ _              ===
PRIVSEG	     -> | user r/w data and text| |                |
		|  u_dsize <= u_dmax	| |     	   |
		 -----------------------  |     	   |
		|	unused		| |     	   |
		 -----------------------  | U_STKDATA_SIZE |
		| stack for user mode	| |     	   |
		|  u_ssize <= u_smax	| |     	   |
USTACK_TOP   ->  -----------------------  |     	   |
ERRNO	     ->	| standard syscall errno| |     	   | U_REGION_SIZE
		 -----------------------  |     	   |
		| pointer to std errno  | |     	   |
		 ----------------------- _ <-USRSTACK      |
                | unused space for >4K  | |                |
		| page size alignment   | | U_PSIZE_PAD    |
		 ======================= -              ===
		| standard kernel stack |       --	   |
U_BLOCK	     ->  -----------------------  --      | one    |
		| standard uthread block|   |	  | pinned |
		 -----------------------    |	  | page   | K_REGION_SIZE
		| user structure	|   |	--	   |
		| swappable proc info	|   | ublock	   |
		 -----------------------    |	  	   |
		| 64-bit user (unused)  |   |              |
               	 -----------------------  -- <-KLDRHEAPORG |
		| loader heap           |   |              |
		| (loader entries)      |   | KLDRHEAPSIZE |
SEGSIZE	     ->  -----------------------  --    	===

  	The format of the process private segment (PRIVSEG) for
	64-bit processes on the 32-bit kernel is as follows:

		 _______________________	  	   ===
PRIVORG      -> |      user args        | <- U_ARGS_ORG64     |
ERRNO64	     ->	| 64-bit syscall errno  |		      |
USTACK_TOP64 ->	 -----------------------|              	      | U_REGION_SIZE64
		| loader heap           |		      |
		| (loader entries)      |		      |
		 =======================  -- <-KHEAPORG64-- ==
		|  loader heap header   |   | LDRHDRSIZE64 |  |
		 -----------------------  -- <-SNODEORG64  |  |
		|     snode heap        |   | SNODESIZE64  |KHEAPSIZE64
		 -----------------------  -- <-UNODEORG64  |  |
		|     unode heap        |   | UNODESIZE64  |  |
		 -----------------------  -- <-KHEAPEND64--   |   
		| standard kernel stack |	_	      |
U_BLOCK	     ->  -----------------------  --	  | one       |
		| standard uthread block|   |	  | pinned    |
		 -----------------------    |	  | page      | K_REGION_SIZE64
		| user structure	|   |	--	      |
		| swappable proc info	|   | ublock	      |
		 -----------------------    |	--	      |
		| 64-bit user struct    |   |	  | pinned    |
		 ----------------------- -- |	--	      |
		| loader heap or unused |		      |
SEGSIZE	     ->  -----------------------		   ===

  	The process private segment (PRIVSEG) for 64-bit processes
	on the 64-bit kernel contains nothing but kernel data.  The
        segment is not mapped into the user address space.  ERRNO64
	is in the user stack segment.
							      U_REGION_SIZE64=0
PRIVORG		 _______________________  -- <-SNODEORG64=KHEAPORG64
0	     ->	|     snode heap        |   | SNODESIZE64  \ KHEAPSIZE64
		 -----------------------  -- <-UNODEORG64  |  |
		|     unode heap        |   | UNODESIZE64  |  |
		 -----------------------  -- <-KHEAPEND64--   |   
		| standard kernel stack |	_	      |
U_BLOCK	     ->  -----------------------  --	  | one       |
		| standard uthread block|   |	  | pinned    |
		 -----------------------    |	  | page      | K_REGION_SIZE64
		| user structure	|   |	--	      | (entire segment)
		| swappable proc info	|   | ublock	      |
		 -----------------------    |--		      |
		| 64-bit user struct    |   |  | pinned	      |
		 ----------------------- -- |--<- KLDRHEAPORG |
		| loader heap or unused |      | KLDRHEAPSIZE |
SEGSIZE	     ->  -----------------------     --		   ---

 *  The addresses of the u-block and of the standard and 64-bit errno
 *  are exported by ipl.exp  All code should use these values rather
 *  than other constants.  Everything defined here is derived from them.
 */

extern int errno64;
#ifdef _KERNSYS
extern ptr64 errnop64;
extern ptr64 environ64;
#endif /* _KERNSYS */

#define U_BLOCK		(SEGOFFSET(&__ublock))
#define ERRNO		(SEGOFFSET(&errno))
#define ERRNO64		(SEGOFFSET(&errno64))


/* To support multiple page sizes for a 32-bit process's private
 * segment, the boundary between the user and kernel accessible parts
 * of a process private segment must be aligned to the system's
 * largest supported pageable page size (MAXPGPSIZE).  Thus, in order to
 * support larger than 4K alignments, the size of the user accessible
 * part of a 32-bit process private segment must be increased.
 *
 * However, to maintain backward compatibility with previous AIX
 * versions, the location of a process's errno and errnop variables
 * can't be moved.  So, the stack and data limits stay the same for a
 * 32-bit process (U_STKDATA_SIZE).  But, in reality, the size of the
 * user accessible part of the process private segment on the 64-bit
 * kernel (U_REGION_SIZE) is padded to a 64K page alignment with
 * U_PSIZE_PAD.  Thus, on the 64-bit kernel, there is a
 * small window of memory that a process could access with stray
 * references beyond errnop.
 *
 * On the 32-bit kernel, multiple pageable page sizes aren't
 * supported, so U_STKDATA_SIZE == U_REGION_SIZE.
 */
#define U_STKDATA_SIZE	(ERRNO + 2*sizeof(int))
#define U_REGION_SIZE   ((U_STKDATA_SIZE + MAXPGPSIZE - 1) & ~(MAXPGPSIZE-1))
#define U_PSIZE_PAD     (U_REGION_SIZE - U_STKDATA_SIZE)
#define K_REGION_SIZE	(SEGSIZE - U_REGION_SIZE)

#ifdef __64BIT_KERNEL
#define U_REGION_SIZE64	(0)
#else
#define U_REGION_SIZE64	(SEGSIZE/2)
#endif /* __64BIT_KERNEL */

#define K_REGION_SIZE64	(SEGSIZE - U_REGION_SIZE64)

/*  U_ARGS_SIZE64:
 *
 *  execargs max buffer size for 64-bit applications.
 *
 *  - ARG_MAX (<sys/limits.h>) and NCARGS (<sys/param.h>) dictate
 *    the statically compiled in max size which must be less then this.
 *
 *  - U_ARGS_ORG64 assumes that errno64 is placed near the end of the
 *    4Mb buffer, contained within it. 
 *    
 *    In the 32-bit kernel, the last 4K of the execargs buf is reserved
 *    for loader entries. errno64 is immediately beneath these.
 *    errno64 is defined in ipl.imp for 32bit kernel and in ipl64.imp for
 *    64-bit kernel.
 *
 */

#define U_ARGS_SIZE64	NCARGS_MAX

#ifdef __64BIT_KERNEL
#define U_ARGS_ORG64    ( (unsigned long long)&errno64 & \
		         ~((unsigned long long)(U_ARGS_SIZE64-1)) )
#else
#define U_ARGS_ORG64    (PRIVORG)
#endif /* __64BIT_KERNEL */

/*
 *  The following defines are calculated from the preceeding values.
 * 
 *  USRSTACK is for 32-bit applications.
 *
 *  KLDRHEAPORG32, KLDRHEAPORG64 and KLDRHEAPSIZE define the layout of the
 *  memory where the loader heap will be.  This memory is used for loader
 *  entries for the shlap and all 32-bit processes.  For 64-bit processes
 *  other than the shlap, this memory is reserved for use by the loader.
 * 
 *  KHEAPORG64, KHEAPSIZE64 and KHEAPEND64 refer to the additional kernel
 *  storage used to hold structures for a 64-bit process, consisting of address
 *  space structures (segnodes and uadnodes) and loader xmalloc heap 
 *  header structures for the 32-bit kernel. 
 */

#define USRSTACK	(PRIVORG_LO + U_STKDATA_SIZE)

#ifdef _POWER
/* Start of loader heap in process-private segment for 32-bit processes.
 */
#ifdef __64BIT_KERNEL
#define KLDRHEAPORG32	((uintptr_t)&U64+(__power_sslb()?0:PAGESIZE))
#else
#define KLDRHEAPORG32	(uintptr_t)&U64
#endif
/* Start of loader heap in process-private segment for shlap.
 */
#define KLDRHEAPORG64	(((uintptr_t)(&__ublock+1) \
			  + (MAXPGPSIZE-1))&~(MAXPGPSIZE-1))
#define KLDRHEAPSIZE(s_addr) (SEGSIZE - SEGOFFSET((s_addr)))

#define KHEAPSIZE64     ((ulong)((ulong)U_REGION_SIZE -  \
				 (ulong)U_REGION_SIZE64) & 0x0FFFFFFFUL)
#define KHEAPORG64      (PRIVORG + U_REGION_SIZE64)
#define KHEAPEND64      (KHEAPORG64 + KHEAPSIZE64)

/*
 *  The loader entries for 64-bit applications live in different places
 *  depending on whether this is the 32-bit kernel/64-bit app model,
 *  which has PRIVSEG (2) mapped into the user address space, or whether
 *  this is the 64-bit kernel/64-bit app case where PRIVSEG is not mapped
 *  into the user address space.
 *
 *  In the 32-bit kernel, the memory between errno64 and KHEAPORG64 is
 *  used for loader entries.  (This memory is included in U_REGION_SIZE64.)
 *  If the loader needs to create an xmalloc heap to manage this memory,
 *  LDRHDRSIZE64 bytes are used from KHEAPORG64 to maintain the heap data
 *  structure.
 *
 *  In the 64-bit kernel, U_REGION_SIZE64 is 0, and loader entries are
 *  allocated from segments managed by the loader.
 *
 */

#ifndef __64BIT_KERNEL
#define	LDRHDRSIZE64	(35 * PAGESIZE)
#else
#define	LDRHDRSIZE64	0
#endif

#endif /* _POWER */

#define SNODEORG64	(KHEAPORG64 + LDRHDRSIZE64)
/* Round SNODESIZE64 down to a multiple of the page size. */
#define SNODESIZE64     ((KHEAPSIZE64-LDRHDRSIZE64)/2 & ~((ulong)(MAXPGPSIZE-1)))
#define UNODEORG64      (SNODEORG64 + SNODESIZE64)
#define UNODESIZE64     (SNODESIZE64)

/*
 *  The following defines are offsets in a process private segment
 *  to the appropriate data area. They can be used in pointer assignment
 *  in addressing portions of the process private segment
 */
#define USTACK_TOP	ERRNO
#define USTACK_TOP64	ERRNO64

#define STACKTOUCH	(2 * 1024)		/* don't touch next segment */
#define STACKTOUCH_U    STACKTOUCH		/* touch above */
#define STACKTOUCH_M    -STACKTOUCH		/* touch middle */
#define STACKTOUCH_L    -(6 * 1024)		/* touch below */
#define KSTACKBLOCK	(96 * 1024)		/* size of uthr and kstack  */
						/* actual kstack bytes	    */
#define KSTACKSIZE	(KSTACKBLOCK - sizeof(struct uthread))

/*
 * mininum initial stack frame is STKMIN. this is machine dependent.
 */
#ifdef __64BIT__
#define STKMIN		56*2
#define STKMINALIGN 	112
#else
#define STKMIN		56
#define STKMINALIGN 	64
#endif /* __64BIT__ */

#ifdef _KERNEL
#define STKMIN64 	112
#define STKMINALIGN64 	112
#endif /* _KERNEL */

#ifdef _KERNSYS

/*
 * The user stack address of the 64bit process.
 *
 *   For the case of no privseg, must adjust below execargs.
 *
 *   STKTOP64 is the top of the stack + 1.
 *
 *   STKFLOOR64 is the lowest address to which the stack
 *   can grow architecturally. The implementation may limit
 *   it to a higher address than this. 
 *
 *   INITSTACK64 is the initial stack pointer (r1) value for
 *   an application for the case of no execargs in the stackseg.
 *   if execargs reside in the stackseg, r1 is computed at runtime
 *   and this is not used.
 *
 *   MAXSTACK64 is the default size for how big we allow the stack
 *   to grow. The rlimit may be unlimited, or bigger, but this is
 *   how far we will actually let em go, unless the process defines
 *   its own maxstack.
 *
 *   HARDMAXSTK64 is the hard limit on the total stack that we will
 *   allow a 64-bit process to consume. This is a kernel-specific
 *   size.
 */

#ifdef _POWER
#define STKTOP64	((unsigned long long)(VM_MAXADDR + 1) << 32)
#define STKFLOOR64      (0x0F00000000000000ull)
#define MAXSTACK64      (SEGSIZE * 16ll)
#endif /* _POWER */
#ifdef __ia64
#define STKTOP64	(VM_MAXPRIV + 1)
#define STKFLOOR64      (0x0003000000000000ull)
#define MAXSTACK64      (SEGSIZE * 16ll)
#endif /* __ia64 */
#define HARDMAXSTK64    v.v_hardstack

#ifndef __NO64PRIVSEG
#define INITSTACK64	(STKTOP64)
#endif /* !__NO64PRIVSEG */


/*
 * The following describes layout of pm_heap segments, for multi-threaded
 * programs.  pm_heap segments contain uthread structures, kernel stacks,
 * and mstext structures.  Each segment is partitioned into zones for
 * allocation of the structures.  The defines for these zones follow



0	 -----------------------
	|			|
	|     uthread    	|
	|			|
	 -----------------------
	|			|
	|    mst extensions	|
	|			|
	 -----------------------
	|			|
	|			|
	|			|
	|			|
	|			|
	|    kernel stack	|
	|			|
	|			|
	|			|
	|			|
	 -----------------------
	|    uthread pm_heap	|
	 -----------------------	
	|    mstext pm_heap	|
	 -----------------------	
	|			|
	|			|
	|    			|
SEGSIZE	 -----------------------	

*/

#define THREADS_PER_SEG 2048		/* must be a multiple of 128 */
#define TS_PAD1 \
	   (PAGESIZE-((THREADS_PER_SEG*(sizeof(struct mstext)))&(PAGESIZE-1)))

/*
 * The kernel stack layout for both 32- and 64-BIT KERNEL. 
 *
 * Note: The kernel stacks for kprocs in 64-bit kernel,
 *       have a separate segment, so they do not get the gratuitous pinned 
 *       stack portion. Since their stacks are in different segment, the stack
 *       space in kthreadseg (below &uth) is unused.
 */
struct uthkstk {
        char kstk[KSTACKSIZE]; 	/* portion of kstack is pinned too. */
       	struct uthread  uth;	/* uth pinned */
};

struct threadseg {

	struct uthkstk	utzone[THREADS_PER_SEG];

#ifndef __64BIT_KERNEL
	struct mstext 	mstzone[THREADS_PER_SEG];
	char 		ts_pad1[TS_PAD1];	/* pad to page boundary */

	struct pm_heap 	mstext_heap;
#endif
	struct pm_heap uthread_heap;

	/* On the 64-bit kernel, there is more space available in a
	 * thread segment.
	 */
};

/*
 * Get the kstack address for this thread...
 */
#define UT_KSTACK_ADDR(_ut) ((void *)(_ut)) 

/* 
 * Kproc's uthread blocks are still maintained in KTHREADSEG as laid
 * out above in threadseg. Kprocs can have only one KTHREADSEG segment. 
 * Kprocs in 64bit kernel have their stack segment same as that of the 64bit
 * user processes. This layout is defined in structure kp64_stackseg below. 
 * A region of KSTACKBLOCK size at the high-end of the stack segment size is 
 * reserved for future use. 
 * Initial stack segment layout for kproc threads in 64bit kernel. The initial 
 * thread gets major piece of the stack segment to allow the ability to set 
 * stack rlimit. The initial thread can even grow the stack beyond one segment.
 */
#define KP64_UTHR0_STKSZ_MAX (ulong)(SEGSIZE - ((THREADS_PER_SEG)*KSTACKBLOCK))

struct kp64_stackseg {
	char kp64_uthr0_kstack[KP64_UTHR0_STKSZ_MAX];	/* primary thread */
	char kstack_zone[THREADS_PER_SEG-1][KSTACKBLOCK];/* other threads */
	char reserved[KSTACKBLOCK];
};


/* 
 * Get the kstack address for the initial thread of a kproc
 */
#define KP64_STACK_ORG	   ((STKTOP64-1) & ~(SEGSIZE-1))
#define KP64_UTHR0_KSTACK  ((void *)					     \
				&((struct kp64_stackseg *)KP64_STACK_ORG)->  \
				kp64_uthr0_kstack[KP64_UTHR0_STKSZ_MAX])

/* 
 * Get the index of this uthread into utzone[] in threadseg 
 */
#define KPUT_INDEX(_ut)      ((SEGOFFSET(_ut) -                              \
                            SEGOFFSET(&((((struct threadseg *)0)->	     \
							utzone[0]).uth)))     \
                            			/sizeof(struct uthkstk))

/*
 * Get the kstack address for this kproc thread...
 */
#define KP64_KSTACK_ADDR(_ut)  ((void *)				      \
			          &((struct kp64_stackseg *)KP64_STACK_ORG)-> \
				kstack_zone[KPUT_INDEX(_ut)][KSTACKBLOCK]) 
#endif /* _KERNSYS */

#endif	/* _H_PSEG */
