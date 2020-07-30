/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/net/net_malloc.h 1.50                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1993              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)15       1.50  src/bos/kernel/net/net_malloc.h, sysnet_netm, bos53V, v2008_44B8 10/24/08 14:52:17 */
/*
 *   COMPONENT_NAME: SYSNET
 *
 *   FUNCTIONS: BUCKETINDX
 *              FREE
 *              MALLOC
 *              NET_FREE
 *              NET_MALLOC
 *              btokup
 *
 *
 *   ORIGINS: 26,27,85,127,196
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1997
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 1.2
 */
/*
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *      Base: malloc.h  7.16 (Berkeley) 6/28/90
 */


#ifndef _NET_NET_MALLOC
#define _NET_NET_MALLOC
#include <sys/lock_def.h>

#define KMEMSTATS

#define SOCKTHRESH 	85
#ifdef __64BIT__
#define NETMAXCPU	(128) 
#else
#define NETMAXCPU	(64)
#endif

#define NETMAXSRADS	1

/*
 * flags to malloc
 */
#define M_WAITOK        0x0000
#define M_NOWAIT        0x0001

/*
 * Types of memory to be allocated.
 */
#define M_FREE          0       /* should be on free list */
#define M_MBUF          1       /* mbuf */
#define M_CLUSTER       2       /* mbuf cluster page */
#define M_SOCKET        3       /* socket structure */
#define M_PCB           4       /* protocol control block */
#define M_RTABLE        5       /* routing tables */
#define M_FTABLE        6       /* fragment reassembly header */
#define M_IFADDR        7       /* interface address */
#define M_SOOPTS        8       /* socket options */
#define M_SONAME        9       /* socket name */
#define M_MBLK          10      /* mblk */
#define M_MBDATA        11      /* mblk data */
#define M_STRHEAD       12      /* Stream head */
#define M_STRQUEUE      13      /* Streams queue pair */
#define M_STRQBAND      14      /* Streams queue band */
#define M_STRMODSW      15      /* Streams modsw */
#define M_STRSIGS       16      /* Streams setsig */
#define M_STRPOLLS      17      /* Streams poll */
#define M_STROSR        18      /* Streams osr */
#define M_STRSQ         19      /* Streams synch queue */
#define M_STREAMS       20      /* misc Streams memory */
#define M_IOV           21      /* large iov's */
#define M_FHANDLE       22      /* network file handle */
#define M_NFSREQ        23      /* NFS request header */
#define M_NFSMNT        24      /* NFS mount structure */
#define M_FILE          25      /* file struct  */
#define M_FILEDESC      26      /* filedesc struct */
#define M_IOCTLOPS      27      /* ioctl data */
#define M_SELPOLL       28      /* select/poll arrays */
#define M_DEVBUF        29      /* device driver memory */
#define M_PATHNAME      30      /* pathname */
#define M_KTABLE        31      /* kernel table */
#define M_MOUNT         32      /* vfs mount struct */
#define M_SUPERBLK      33      /* super block data */
#define M_UFSMNT        34      /* UFS mount structure */
#define M_S5MNT         35      /* S5FS mount structure */
#define M_S5SUPERBLK    36      /* S5FS super block data */
#define M_VSRAD         37      /* dynamically allocated vnodes */
#define M_SPECINFO      38      /* special file information */
#define M_SPECALIAS     39      /* special file alias */
#define M_SPECBUF       40      /* special file buffer */
#define M_LOCKF         41      /* byte-range locking structures */
#define M_DEVSW         42      /* device switch tables */
#define M_IPSEC         43      /* IPsec structure */
/* Available */
#define M_KALLOC        48      /* kalloc - obsolescent */
#define M_TEMP          49      /* misc temporary data buffers */
#define M_IPMOPTS       50      /* internet multicast options */
#define M_IPMADDR       51      /* internet multicast address */
#define M_IFMADDR       52      /* link-level multicast address */
#define M_LAST          53

#define KMEMNAMSZ       12
#define INITKMEMNAMES { \
	"free",         /* 0 M_FREE */ \
	"mbuf",         /* 1 M_MBUF */ \
	"mcluster",     /* 2 M_CLUSTER */ \
	"socket",       /* 3 M_SOCKET */ \
	"pcb",          /* 4 M_PCB */ \
	"routetbl",     /* 5 M_RTABLE */ \
	"fragtbl",      /* 6 M_FTABLE */ \
	"ifaddr",       /* 7 M_IFADDR */ \
	"soopts",       /* 8 M_SOOPTS */ \
	"soname",       /* 9 M_SONAME */ \
	"mblk",         /* 10 M_MBLK */ \
	"mblkdata",     /* 11 M_MBDATA */ \
	"strhead",      /* 12 M_STRHEAD */ \
	"strqueue",     /* 13 M_STRQUEUE */ \
	"strqband",     /* 14 M_STRQBAND */ \
	"strmodsw",     /* 15 M_STRMODSW */ \
	"strsigs",      /* 16 M_STRSIGS */ \
	"strpoll",      /* 17 M_STRPOLLS */ \
	"strosr",       /* 18 M_STROSR */ \
	"strsyncq",     /* 19 M_STRSQ */ \
	"streams",      /* 20 M_STREAMS */ \
	"iov",          /* 21 M_IOV */ \
	"fhandle",      /* 22 M_FHANDLE */ \
	"NFS req",      /* 23 M_NFSREQ */ \
	"NFS mount",    /* 24 M_NFSMNT */ \
	"file",         /* 25 M_FILE */ \
	"file desc",    /* 26 M_FILEDESC */ \
	"ioctlops",     /* 27 M_IOCTLOPS */ \
	"select/poll",  /* 28 M_SELPOLL */ \
	"devbuf",       /* 29 M_DEVBUF */ \
	"pathname",     /* 30 M_PATHNAME */ \
	"kernel table", /* 31 M_KTABLE */ \
	"mount",        /* 32 M_MOUNT */ \
	"superblock",   /* 33 M_SUPERBLK */ \
	"UFS mount",    /* 34 M_UFSMNT */ \
	"S5FS mount",   /* 35 M_S5MNT */ \
	"S5FS superbk", /* 36 M_S5SUPERBLK */ \
	"vnode",        /* 37 M_VNODE */ \
	"spec info",    /* 38 M_SPECINFO */ \
	"spec alias",   /* 39 M_SPECALIAS */ \
	"spec buf",     /* 40 M_SPECBUF */ \
	"locking",      /* 41 M_LOCKF */ \
	"devsw",        /* 42 M_DEVSW */ \
	"", "", "", "", "", \
	"kalloc",       /* 48 M_KALLOC */ \
	"temp",         /* 49 M_TEMP */ \
	"mcast opts",   /* 50 M_IPMOPTS */ \
	"mcast addrs",  /* 51 M_IPMADDR */ \
	"ll mc addrs",  /* 52 M_IFMADDR */ \
}

#ifdef  _KERNEL
#ifdef  _AIX_FULLOSF
#include <kern/lock.h>
#else
#include <sys/param.h>
#endif
#endif

#define MINBUCKET       5                       /* param.h in osf */
#define MAXBUCKET	(MINBUCKET+12)
#define BUCKETSPERCPU	(MAXBUCKET+1)

/*
 * Allocations for sizes > MAXALLOCSAVE are handled in a separate bucket
 * (not in per-cpu buckets). To identify memory allocated to these buckets
 * through kmemusage,we use LARGEBUCKETCPU.
 */
#define LARGEBUCKETCPU	(-3)
#define MAXLARGEBUCKET 	(MAXBUCKET+10) 
#define LARGEBUCKETS 	(BUCKETSPERCPU+10) 

struct ostd_mem_rec {
   u_int   pre_idx;                /* previous record's idx in ostd_mem_list */
   u_int   nxt_idx;                /* next record's index in ostd_mem_list */
   void    *addr;                  /* Memory address of chunk 'o mem */
   size_t  size;                   /* Size being allocated */
   int     memtype;                /* Type of memory.  EG: M_CLUSTER */
   char    cpu;                    /* CPU that logs event */
   char    pading[3];              /* Alignment */
   void    *callers[16];           /* callers of net_malloc */
};

#define OSTD_ARRAY      11
#define OSTDIDX(addr)   ((u_long)(addr) % OSTD_ARRAY)

/* d_expand flag */
#define OSTD_ALLOW_EXP	0
#define OSTD_NEED_EXP	1
#define OSTD_DOING_EXP	2	

struct ostd_mem {
   struct ostd_mem_rec  *d_list;    /* ostd memory record link list */
   u_int                *d_idx_que; /* index queue */
   u_int                d_cnt;      /* count of records */
   u_int                d_size;     /* Total size of link list */
   u_int                d_last_idx; /* last index used in link list */
   u_int                d_first_idx;/* fisrt index used in link list */
#ifdef _KERNEL
   simple_lock_data_t   d_lock;    /* simple lock for this bucket */
#else
   long			d_lock;
#endif
   int			d_savpri;   /* saved priority for this bucket */
   u_int                d_expand;   /* flag, see definitions above */ 
} ostd[OSTD_ARRAY];

/* +6 is for 32K through 1Meg buckets. Indicies 1 through MAXBUCKET aren't used */

struct kmemstats {
	long    ks_inuse;       /* # of packets of this type currently in use */
	long    ks_calls;       /* total packets of this type ever allocated */
	long    ks_memuse;      /* total memory held in bytes */
	long    ks_limblocks;   /* number of times blocked for hitting limit */
	long    ks_mapblocks;   /* number of times blocked for kernel map */
	long    ks_maxused;     /* maximum number ever used */
	long    ks_limit;       /* most that are allowed to exist */
	long    ks_failed;      /* total failed allocations */
	long 	ks_delayed;	/* total delayed allocations */
#ifdef  _KERNEL
	simple_lock_data_t      ks_lock;
#else
	long			ks_lock;
#endif
};

/*
 * Array of descriptors that describe the contents of each page
 *
 * int ku_noguardpgs; - This is set only for net_malloc of MAXALLOCSAVE
 * size. In the net_free() path, this variable  determines whether
 * 1. <= (MAXALLOCSAVE/2) allocation has been promoted and has guard pages
 *		OR
 * 2. it is a MAXALLOCSAVE allocations and no guard pages
 * ku_noguardpgs = 0 ==> allocations >= PAGESIZE have guard pages (default)
 * ku_noguardpgs = 1 ==> This is a net_malloc() of MAXALLOCSAVE size with
 *			 no guard pages
 */

struct kmemusage {
	short ku_indx;          /* bucket index */
	union {
	        u_short freecnt;/* for small allocations, free pieces in page */
	        u_short pagecnt;/* for large allocations, pages alloced */
	} ku_un;
	int ku_cpu;             /* Indicates which bucket array to free on */
#ifdef  _KERNEL
	simple_lock_data_t ku_lock; /* Serialize ku_cpu access */
#else
	long ku_lock;
#endif
	int ku_noguardpgs;
	int ku_flags;
};
#define ku_freecnt ku_un.freecnt
#define ku_pagecnt ku_un.pagecnt

/* ku_flags */
#define NMD_HIDDEN      0x00000004 /* The page is hidden */

/*
 * Set of buckets for each size of memory block that is retained
 */
struct kmembuckets {
	void *  kb_next;        /* list of free blocks */
	long    kb_calls;       /* total calls to allocate this size */
	long    kb_total;       /* total number of blocks allocated */
	long    kb_totalfree;   /* # of free elements in this bucket */
	long    kb_elmpercl;    /* # of elements in this sized allocation */
	long    kb_highwat;     /* high water mark */
	long    kb_couldfree;   /* over high water mark and could free */
	long    kb_failed;      /* total failed allocations */
	long 	kb_delayed;	/* total delayed allocations */
#ifdef  _KERNEL
	simple_lock_data_t      kb_lock;
#else
	long			kb_lock;
#endif
	int     delta;          /* For kmeminuse quantum */
};

/*
 * Part of policing the users is to keep a list of past malloc/frees.
 * Memory for police_events is allocated when net_malloc_police is turned
 * on via the no command.  The array consists of this struct:
 */
struct police_event {
        char     cpu;                   /* CPU that logs event */
        char    type;                   /* 'M'=net_malloc, 'F'=net_free */
        short   padding;                /* Alignment */
        int     memtype;                /* Type of memory.  EG: M_CLUSTER */
	size_t	size;			/* Size being allocated */
        void    *addr;                  /* Memory address of chunk 'o mem */
        void    *callers[16];             /* callers of net_malloc/net_free */
	long	reserved[3];		/* Room to grow */
};

/*
 * doubly linked list stub. Used by freelists
 * so coalescing can be done without traversing the freelist
 */

struct kmem_dblink {
	void *next;     /* forward pointer */
	void *prev;     /* back pointer */
};

#define KMEM_CACHE_LINE 	(128/sizeof(long))

#ifdef _KERNEL
#ifdef __64BIT__
/* 
 * Note this needs to be changed when the MBUF_POOL range is changed 
 * It really is the #define in the comment, but the ESID's are not defined
 * for user space
 * #define MAXNETKMEM 	(MBUF_POOL_ESID_LAST-MBUF_POOL_ESID_FIRST+1)
 */
#define MAXNETKMEM 	(260L) 

#else /* __64BIT__ */
#define MAXNETKMEM	(4)
#endif /* __64BIT__ */

struct police_usage
{
	ulong pu_freebits[4];
};



/* maximum number of netm heaps */
#define	NETKMEMHEAPS		2

/* primary and secondary heap */
#define NETM_PRIMARY		0
#define NETM_SECONDARY		1	

/*
 * Kernel mbuf memory heap info. An mbuf heap could be backed by 
 * 4K, 64K or 16M page size. 'hp_page_size' specifies the page
 * size backing this mbuf heap
 */
struct netkmem_heap {

#ifdef __64BIT_KERNEL
	psize_t	hp_page_size;			/* page size backing this heap */
#else
	int	hp_page_size;
#endif

        void 	*hp_kmembase;           	/* starting address of this heap*/
	
        void 	*hp_kmemlimit;            	/* address past the last address of this heap */
						/* Note that allocated memory in this heap  */
						/* must be <, not <= to kmemlimit */

        struct 	kmemusage *hp_kmemusage[MAXNETKMEM];
						/* provides 'address to bucket' */
						/* information for this heap */
	
	long	hp_inusepgcnt[MAXNETKMEM];	/* pages in use in a segment */ 

	struct 	police_usage *hp_police_usage[MAXNETKMEM];  
						/* police_usage array for this heap */

        struct 	xmem hp_kmemxmemd[MAXNETKMEM];  /* cross memory descriptors for this heap */

	void 	*hp_hiaddrpinned;		/* highest address pinned in this heap */

	long 	hp_segs_inuse;			/* number of segments in use in this heap */

	ulong 	hp_curr_segindx;		/* Current segment index in this heap */
						/* where we are searching for free pages */

	ulong 	hp_curr_pagindx;		/* points to an index in kmemusage array of */ 
						/* current segment to search for free pages */

	ulong	reserved[4];			/* room to grow */
};

/*
 * netkmem_srad structure contains netm's global variables
 */
struct netkmem_srad
{

	/* add primary and secondary network memory heaps  */

	struct netkmem_heap *	kmemheap[NETKMEMHEAPS];
						/* network memory heaps; secondary is needed */ 
						/* only if primary heap page size is 16M */

	int 			current_heap;	/* heap currently active PRIMARY or SECONDARY  */

	long 			heaps_in_use;	/* total number of heaps */

	long 			kmempages;	/* total good/real memory in units of 4K */

        long 			kmeminuse[KMEM_CACHE_LINE];	
						/* total number of bytes given */
						/* to users from this heap */

        long 			allocated[KMEM_CACHE_LINE];  
						/* running total of memory actually */
						/* available to memory heap */

	long 			thewall;

        void *			kmemfreelater; 	/* linked list of memory */
						/* locations to unpin */

	long			wantkmemmap; 	/* got rid of wantkmemmap */

        tid_t 			kmemtid;       	/* tid of the malloc_thread */
						/* process */

        struct trb *		threadtime;    	/* timer structure for the */
						/* kmemthread proc */ 

        long 			kmemreserve ;  	/* amount of reserved memory; */
						/* used for scaling buckets */ 

        long 			kmemgcintvl;  	/* garbage collection */
						/* interval in seconds */ 

	long 			kmemgcscale;

	/* fields for 'allocated' and 'kmeminuse' are kind of redundant here */
	/* These are stored per-heap basis and could be retrieved from there */

        long 			net_malloc_police; 
						/* flag determining if */
						/* net_malloc_police is enabled*/ 

        struct kmembuckets 	bucket[NETMAXCPU][BUCKETSPERCPU]; 

        struct kmembuckets 	largebucket[LARGEBUCKETS]; 

        void *			kbtail[NETMAXCPU][BUCKETSPERCPU];  
						/* Array of tail pointers to */
						/* facilitate FIFO ordering */
						/* of freed memory */ 

        void *			largekbtail[LARGEBUCKETS]; 

#undef alloc_lock
        simple_lock_data_t 	alloc_lock;    	/* lock controls the */
						/* increase/decrease of the */
						/* amount available pinned */
						/* network memory heap */ 

        long 			sock_thresh_size;
						/* # of bytes that can be */
						/* allocated before new */
						/* sockets are not allowed */

	struct kmemstats 	kmemstats[M_LAST]; 	
						/* kmem stats for the */
						/* network memory heap */ 

	int 			(*inet_dr_cpu_remove)(cpu_t);      	
						/* Function pointer for */
						/* dr_cpu_remove operations */
						/* in netinet kernext */

	int 			(*inet_dr_cpu_add)(cpu_t);      	
						/* Function pointer for */
						/* dr_cpu_add operations */
						/* in netinet kernext */
	
	long 			dr_token;	/* reconfig handler sets this */
						/* Used for register/unregister */

	long 			dr_rmcpucnt;	/* flag to indicate cleanup */
						/* is required for an offline */
						/* cpu's buckets */

	int 			dr_cpulist[NETMAXCPU];		
						/* array to mark which cpus */
						/* are offline and needs */
						/* cleanup gone */

	simple_lock_data_t 	dr_lock;	/* To serialize DR cpu */
						/* remove/add */
};

#endif /* _KERNEL */


#ifdef _KERNEL
#define MINALLOCSIZE    (1 << MINBUCKET)
#ifdef _POWER
/* In POWER architecture, we can take advantage of the cntlz instruction */
/* to get a fast log2(size), which is what we're really after here.  The */
/* calculation takes size, subtracts 1, then does cntlz on it.  This     */
/* means that all values between 2**(x-1) + 1 and 2**x will end up with  */
/* the same result, namely, 32-x.  The bucket number we want is x, but   */
/* since we want all values less than or equal to 2**(MINBUCKET+1) to    */
/* end up in the same bucket, we just need make sure we never get a      */
/* bucket number less than MINBUCKET.                                    */
#pragma mc_func cntlz32 { "7C630034" } /* cntlz r3,r3 */
#pragma reg_killed_by cntlz32 gr3
#pragma mc_func cntlz64 { "7C630074" } /* cntlzd r3,r3 */
#pragma reg_killed_by cntlz64 gr3


/*
* C++ files will get the -qisolated_call option passed in which
* generates the same code; it's just that the C++ compiler handles
* the comand line option quite well, but fails on the praga equivalent
*/

#ifdef __64BIT__

#if !defined(__cplusplus)
#pragma isolated_call(cntlz64)
#endif /* __cplusplus */

#define BUCKETINDX(size) \
	( (size) == 512 ? \
	         (MINBUCKET + 4) \
	: (size) ?  \
	        ( cntlz64(size-1) > ( 64 - MINBUCKET) ? \
	                MINBUCKET \
	        : cntlz64(size-1) < ( 64 - (MAXLARGEBUCKET)) ? \
	                 (MAXLARGEBUCKET) \
	        : (64 - cntlz64(size-1)) ) \
	: MINBUCKET )

#else /* not 64 bit kernel */

#if !defined(__cplusplus)
#pragma isolated_call(cntlz32)
#endif /* __cplusplus */

#define BUCKETINDX(size) \
	( (size) == 256 ? \
	         (MINBUCKET + 3) \
	: (size) ?  \
	        ( cntlz32(size-1) > (32 - MINBUCKET) ? \
	                MINBUCKET \
	        : cntlz32(size-1) < (32 - MAXLARGEBUCKET) ? \
	                 MAXLARGEBUCKET \
	        : (32 - cntlz32(size-1)) ) \
	: MINBUCKET )

#endif /* 64 bit kernel */

#else /* not _POWER */
#define BUCKETINDX(size) \
	( (size) == 256 ? (MINBUCKET + 3) \
	: (size) == 4096 ? (MINBUCKET + 7) \
	: (size) <= (MINALLOCSIZE * 128) \
	        ? (size) <= (MINALLOCSIZE * 8) \
	                ? (size) <= (MINALLOCSIZE * 2) \
	                        ? (size) <= (MINALLOCSIZE * 1) \
	                                ? (MINBUCKET + 0) \
	                                : (MINBUCKET + 1) \
	                        : (size) <= (MINALLOCSIZE * 4) \
	                                ? (MINBUCKET + 2) \
	                                : (MINBUCKET + 3) \
	                : (size) <= (MINALLOCSIZE* 32) \
	                        ? (size) <= (MINALLOCSIZE * 16) \
	                                ? (MINBUCKET + 4) \
	                                : (MINBUCKET + 5) \
	                        : (size) <= (MINALLOCSIZE * 64) \
	                                ? (MINBUCKET + 6) \
	                                : (MINBUCKET + 7) \
	        : (size) <= (MINALLOCSIZE * 2048) \
	                ? (size) <= (MINALLOCSIZE * 512) \
	                        ? (size) <= (MINALLOCSIZE * 256) \
	                                ? (MINBUCKET + 8) \
	                                : (MINBUCKET + 9) \
	                        : (size) <= (MINALLOCSIZE * 1024) \
	                                ? (MINBUCKET + 10) \
	                                : (MINBUCKET + 11) \
	                : (size) <= (MINALLOCSIZE * 8192) \
	                        ? (size) <= (MINALLOCSIZE * 4096) \
	                                ? (MINBUCKET + 12) \
	                                : (MINBUCKET + 13) \
	                        : (size) <= (MINALLOCSIZE * 16384) \
	                                ? (MINBUCKET + 14) \
	                                : MAXBUCKET )
#endif /* _POWER */

/* 
 * 'netkmembase' array to hold starting address of each heap.
 * 'netkmemheapsz' array stores size of primary/secondary heap range 
 */
extern ulong 			netkmembase[NETKMEMHEAPS];
extern vmsize_t 		netkmemheapsz[NETKMEMHEAPS];

extern struct netkmem_srad *	netkmem;

#ifndef PAGESIZE
#define PAGESIZE 4096
#endif

/*
 * Turn virtual addresses into kmem map indicies
 */

extern int addr2heap (caddr_t);  	
extern int only_mbuf_heap;

/*
 * If only one mbuf heap is in use, only_mbuf_heap stores
 * the heap number.  Otherwise, addr2heap() is called.
 * This is to avoid unnecessary call to function since
 * a2hp() macro is used very often in the code.
 */
#define a2hp(addr) (only_mbuf_heap == -1) ? addr2heap(addr) : only_mbuf_heap

#define KMEMBASE(seg_indx, which_heap) (netkmembase[which_heap] + (ulong) ((seg_indx) * SEGSIZE))  
#define NETKMEMINDX(addr) (SEGNUMBER(addr) - SEGNUMBER(netkmembase[a2hp(addr)]))
#define btokup(addr)    (netkmem->kmemheap[a2hp(addr)]->hp_kmemusage[NETKMEMINDX(addr)]) \  
			 + ((ulong)(SEGOFFSET(addr) / PAGESIZE))

#define addr2pgindx(addr, size) (SEGOFFSET(addr) / size)
#define buddy(addr, size) \
        ((addr2pgindx(addr, size) % 2) ? (addr - size) : (addr + size))

/*
 * Macro versions for the usual cases of malloc/free
 * See malloc source for discussion of operation if !KMEMSTATS.
 */
#define MALLOC(space, cast, size, type, flags) \
	(space) = (cast)net_malloc((u_long)(size), type, flags)
#define MALLOC_SRAD(space, cast, size, type, flags, srad) \
	(space) = (cast)net_malloc((u_long)(size), type, flags)
#define FREE(addr, type) net_free((void *)(addr), type)

extern const char kmemnames[M_LAST][KMEMNAMSZ];

#define NET_MALLOC(p,c,s,t,f)   MALLOC(p,c,s,t,f)
#define NET_MALLOC_SRAD(p,c,s,t,f,g)   MALLOC_SRAD(p,c,s,t,f,g)
#define NET_FREE(p,t)           FREE(p,t)

#endif  /* _KERNEL */
#endif  /* _NET_NET_MALLOC */
