/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/vm_types.h 1.35.1.2                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1999,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)47	1.35.1.2  src/bos/kernel/sys/vm_types.h, sysvmm, bos53V, v2009_13A8 3/25/09 16:31:38 */


#ifndef _H_VM_TYPES
#define _H_VM_TYPES

#ifndef _H_STANDARDS
#include <standards.h>
#endif


#ifdef __64BIT_KERNEL
#if defined(__64BIT__) || defined(_LONG_LONG)
typedef int64           vmid_t;         /* virtual memory object ID     */
typedef u_int64		vmhandle_t;	/* virtual memory handle        */
#endif
#else /* !__64BIT_KERNEL */
#ifndef __64BIT__
typedef long            vmid_t;         /* virtual memory object ID     */
typedef ulong_t		vmhandle_t;	/* virtual memory handle        */
#else
typedef int             vmid_t;         /* virtual memory object ID     */
typedef uint_t		vmhandle_t;	/* virtual memory handle        */
#endif
#endif /* __64BIT_KERNEL */
typedef int             vmid32_t;       /* 32bit size-invariant vmid_t  */
typedef uint_t		vmhandle32_t;	/* 32bit size invariant vmhandle_t*/


#ifndef __64BIT_KERNEL
#ifdef _32KERMODE
typedef uint_t          kvmid_t;        /* kernel's internal version */
typedef uint_t          kvmhandle_t;    /* kernel's internal version */
#else
typedef long32int64_t	kvmid_t;	/* kernel's internal version */
typedef ulong32int64_t	kvmhandle_t;	/* kernel's internal version */
#endif
#endif

#ifdef __64BIT__
typedef long		vmid64_t;
typedef long		rpn64_t;
typedef long            cnt64_t;        /* 64-bit count */
typedef long            psize_t;        /* page size */
#elif defined(_LONG_LONG)
typedef long long	vmid64_t;
typedef long long	rpn64_t;
typedef long long       cnt64_t;        /* 64-bit count */
typedef long long       psize_t;        /* page size */
#elif defined(_ALL_SOURCE)
typedef quad		vmid64_t;
typedef quad		rpn64_t;
typedef quad            cnt64_t;        /* 64-bit count */
typedef quad            psize_t;        /* page size */
#endif

typedef int32long64_t	vmidx_t;	/* index for vm objects */
                                        /* VM_FULL_KEY() -      */
typedef uint32long64_t  vmfkey_t;       /* ..combined: hkey/ppkey/noex */
                                        /* VM_PROT_KEY() -      */
typedef uint32long64_t  vmprkey_t;      /* ..combined: hkey/ppkey/noex */
typedef int32long64_t	vmkey_t;	/* key for vm objects */
typedef int32long64_t	vmhwkey_t;      /* hardware KsKp key */
typedef int32long64_t	vpn_t;		/* virtual page number          */
typedef int32long64_t	rpn_t;		/* real page number             */

typedef unsigned long   ptex_t;         /* page table entry index */
typedef unsigned long   swhatx_t;       /* Software HAT index */

typedef uint32long64_t  esid_t;         /* use this for esids */

#ifdef __64BIT_KERNEL
typedef int		aptx_t;		/* Index into apt, ahat */
#else
typedef ushort_t	aptx_t;		/* Index into apt, ahat */
#endif

typedef int             pdtx_t;         /* pdt index */
typedef short           psx_t;          /* page size index */
typedef ushort_t        pshift_t;       /* page size shift */
typedef ushort_t        sshift_t;       /* segment size shift */

typedef int             unidx_t;        /* unode index */
typedef int             snidx_t;        /* snode index */
typedef int             vmnodeidx_t;    /* generic node index (snode/unode) */

typedef int		kvpn_t;		/* kernel's internal view of vpn*/
#ifndef  __64BIT_KERNEL
   typedef int		krpn_t;		/* kernel's internal view of rpn*/
#endif
typedef int32long64_t   vmsize_t;	/* size param */

typedef int32long64_t   vmm_lock_t;     /* for vmmlock */

#ifdef __ia64
typedef long		vmrid_t;	/* virtual memory region ID     */
typedef uint_t		vmpkey_t;	/* virtual memory protection key */
typedef ulong_t		tlbhandle_t;	/* handle for translation register */
#endif

typedef unsigned long ureg_t;		/* unsigned register type */

#ifdef _KERNEL
/*
 * vaddr_t : for performing arithmetic operations on pointers
 *	Note this typedef cannot be used for 64-bit user pointers
 *	on a 32-bit kernel.
 */
typedef ulong_t vaddr_t;
#endif /* _KERNEL */

#if !defined(__64BIT__) && !defined(_LONG_LONG) && defined(__64BIT_KERNEL)

/* vmhandle_t is undefined for 32bit apps when __64BIT_KERNEL is
   defined.
*/

#else

typedef struct
#ifdef _ALL_SOURCE
vmaddr_t
#endif /* _ALL_SOURCE */
{		/* long-form virtual address */
#ifdef _ALL_SOURCE
	vmhandle_t	srval;		/* segment reg contents */
	caddr_t		offset;		/* offset within segment */
#else /* _ALL_SOURCE */
	vmhandle_t	__srval;	/* segment reg contents */
	caddr_t		__offset;	/* offset within segment */
#endif /* _ALL_SOURCE */
} vmaddr_t;

#endif /* !defined (__64BIT_KERNEL) && !defined(__LONG_LONG) */

typedef struct
#ifdef _ALL_SOURCE
adspace_t
#endif /* _ALL_SOURCE */
{		/* address space mapping */
#ifdef _ALL_SOURCE
	ulong32int64_t	alloc;		/* allocation flags */
	vmhandle_t	srval[16];	/* contents of all seg regs */
#else /* _ALL_SOURCE */
	ulong32int64_t	__alloc;	/* allocation flags */
	vmhandle_t	__srval[16];	/* contents of all seg regs */
#endif /* _ALL_SOURCE */
} adspace_t;

#ifdef _ALL_SOURCE
#define ADSP_MASK(_x)		((1U << 31) >> (_x))
#define adsp_is_alloc(_a,_x)	((_a)->alloc &   ADSP_MASK(_x))
#ifdef _KERNSYS
#define adsp_set_alloc(_a,_x)	((_a)->alloc |=  ADSP_MASK(_x))
#define adsp_clear_alloc(_a,_x)	((_a)->alloc &= ~ADSP_MASK(_x))
#endif /* _KERNSYS */
#endif /* _ALL_SOURCE */

#ifdef _ALL_SOURCE
/* mstsave32 requires a size invariant placeholder for an adspace_t for
 * 32bit apps. This is ONLY a placeholder and exists for compatibility
 * and is not intended to be used by the kernel. However, it must be
 * available to userspace for 64-bit debuggers to handle 32-bit targets.
 */
typedef struct
adspace32_t
{
        uint_t alloc;
        uint_t srval[16];
} adspace32_t;
#endif

#if defined(_ALL_SOURCE) && defined(_LONG_LONG)

/*
 * Memory Region Management Definitions and Structures
 */
typedef enum _MR_ATTR_TYPE {
  BadAttr = 0,
  VirtAddr = 1
} MR_ATTR_TYPE;

typedef enum _MR_LABEL_TYPE {
  BadMem = 0,
  FreeMem = 1,
  IPLCB = 2,
  RMALLOC = 3,
  PM_HEAP = 4,
  RTAS_HEAP = 5,
  TCE_TABLE = 6,
  IO_SPACE = 7,
  HUGE_PAGE = 8
} MR_LABEL_TYPE;

typedef struct {
	unsigned long long	mr_addr;	/* memory region address */
	unsigned long long	mr_size;	/* memory region length */
	unsigned char	mr_att;			/* memory region attributes */
	unsigned char	mr_label;		/* memory region label */
	unsigned short	mr_nodeid;		/* memory region NUMA node ID */
	char	reserved[4];			/* padding, future use */
} iplcb_map_reg_t;

#endif /* _ALL_SOURCE && _LONG_LONG */


/* structure for vm_saveatt() and vm_restatt() type services */
#ifdef _KERNEL
#ifdef __64BIT_KERNEL   /* runs on PPC only */

struct vmsegatt {
        vmhandle_t vmh0;
        vmhandle_t vmh1;
        vmhandle_t vmh2;
        vmhandle_t vmh3;
        ushort_t allocmask;
};

typedef struct vmsegatt vmsratt_t;

#else                   /* 32bit Kernel runs on PPC and Power architectures */

#define MAXSRNUM        7

typedef struct {
        vmhandle_t vmh[MAXSRNUM];
        ulong_t  allocmask;
} vmsratt_t;

#endif	/* __64BIT_KERNEL */
#endif  /* _KERNEL */

/* special large-page handle for use on 32-bit kernel */
#ifndef __64BIT_KERNEL
typedef vmhandle_t      vmlpghandle_t;    /* large-page virtual memory handle */
#endif /* !__64BIT_KERNEL */

#endif /*_H_VM_TYPES*/
