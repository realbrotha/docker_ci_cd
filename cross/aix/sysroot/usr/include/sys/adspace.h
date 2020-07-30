/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/adspace.h 1.66                               */
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
/*
 * COMPONENT_NAME: (SYSVMM) Virtual Memory Management
 *
 * FUNCTIONS: Address-space manipulation macros.
 *
 * ORIGINS: 27
 *
 */
/* @(#)92     1.66  src/bos/kernel/sys/adspace.h, sysvmm, bos53D, d2005_15B5 4/6/05 17:16:02 */

#ifndef _H_ADSPACE
#define _H_ADSPACE

/*
 *       NOTE:  See <sys/m_types.h> for definition of address space.
 */

#include  <sys/types.h>
#include  <sys/seg.h>
#include  <sys/systemcfg.h>

#ifdef	_KERNEL

struct ublock;
struct xmem;

/* 
 * These are the adspace services that must be used in
 * the 64-bit kernel and should be used, when possible, in
 * the 32-bit kernel as well.
 */

int		as_det64(ptr64);
vmhandle_t	as_geth64(ptr64);
int		as_puth64(ptr64, vmhandle_t);
int		as_seth64(ptr64, vmhandle_t);
vmhandle_t	as_getsrval64(ptr64);

#ifdef __64BIT_KERNEL
ptr64	as_att64(vmhandle_t, caddr_t);
#else
ptr64	as_att64(vmhandle_t, int);
#endif /* __64BIT_KERNEL */

/*
 *  Definitions for setting key bits in vmhandles:
 */
#ifdef __64BIT_KERNEL

#define	VM_PRIV		(vmkey_t) 0	/* Ks = 0, Kp = 0 privileged access */
#define	VM_UNPRIV	(vmkey_t) 1	/* Ks = 1, Kp = 1 unprivileged access */
#define	VM_KEY10	(vmkey_t) 2	/* Ks = 1, Kp = 0 access */
#define	VM_KEY01	(vmkey_t) 3	/* Ks = 0, Kp = 1 access */

#else

#define	VM_PRIV		0		/* Ks = 0, Kp = 0 privileged access */
#define	VM_UNPRIV	1		/* Ks = 1, Kp = 1 unprivileged access */

#endif /* __64BIT_KERNEL */

/*  vm_getkey -- Virtual memory get key
 *              Parameters:  (1) vmhandle_t  Handle from which to extract key
 *              Returns:         vmkey_t     Key
 * 
 */

#ifndef __64BIT_KERNEL
#define vm_getkey(k) ((((ulong)k)>>30)&0x00000001)
#else
vmkey_t vm_getkey(vmhandle_t);
#endif /* !__64BIT_KERNEL */

/*  vm_vmid -- Compute vmid from vmhandle.
 *              Parameters:  (1) vmhandle_t  vm handle 
 *              Returns:         vmid_t      vmid computed from handle
 *
 */

#ifndef _KERNSYS
extern vmid_t	vm_vmid(vmhandle_t);
#endif

/*  vm_setkey -- Virtual memory set key
 *              Parameters:  (1) vmhandle_t  Handle into which to set key
 *                           (2) vmkey_t     Key
 *              Returns:         vmhandle_t  Handle, with new key set
 *
 * Obsolete.  Use vm_handle(vm_vmid(h),k).
 */

#if !defined(__64BIT_KERNEL) && !defined(_KERNSYS)
#define vm_setkey(h,k) ((vmhandle_t)(((((ulong)k)&0x00000001)<<30)| \
                                      (((ulong)h)&0xBFFFFFFF)))
#endif /* !__64BIT_KERNEL && !_KERNSYS */

/*  Routines that "attach" an addressable object to the kernel's address
 *  space.
 *
 *  These routines:
 *     (1) Allocate a segment register or address space entry
 *     (2) Load the register or entry with the specified vmhandle_t
 *     (3) Modify the specifed virtual address so that it will select the
 *           proper segment register/address space entry
 *     (4) Return the modified address for direct use.
 */

/*  vm_att -- Virtual memory attach
 *              Parameters:  (1) vmhandle_t  Handle to use
 *                           (2) caddr_t     Offset of object (can be passed 
 *					     in as a address; high bits are 
 *					     ignored)
 *              Returns:         caddr_t     effective address to use to 
 *					     address object
 */

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
caddr_t vm_att(vmhandle_t, caddr_t);
#else
caddr_t vm_att();
#endif

/* Routines that save the temp attaches, thereby providing a clean address
 * space for more attaches. A restore must be done to get back to previous
 * address space
 */
void vm_saveatt(vmsratt_t *);           /* save temp attaches */
void vm_restatt(vmsratt_t *);           /* restore temp attaches */

/*  xm_att -- Cross memory attach
 *
 *    This interface is obsolete and should no longer be used.
 *    Use xm_mapin() instead.
 *
 *              Parameters:  (1) struct xmem *  Pointer to xmem descriptor
 *                           (2) caddr_t        Address of buffer to attach 
 *                           (3) int32long64_t/long   length in bytes to map
 *              Returns:         caddr_t     effective address to use to 
 *					     address object
 */
#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
caddr_t xm_att(struct xmem *, caddr_t, int32long64_t);
#else
caddr_t xm_att();
#endif

/*  xm_mapin -- Cross memory attach 
 *
 *       former users of xm_att() should use this.
 *
 *              Parameters:  (1) struct xmem *  Pointer to xmem descriptor
 *                           (2) caddr_t        Address of buffer to attach 
 *                           (3) size_t         length in bytes to map
 *              Returns:     (4) caddr_t        effective address to use to 
 *					        address object
 */
int xm_mapin(struct xmem *, caddr_t, size_t, caddr_t *);

/*  xm_maxmap -- Cross memory attach check
 *
 *	Parameters: (1) struct xmem *	Pointer to xmem descriptor
 *		    (2) void *		Address of buffer to attach 
 *	Returns:    (3) size_t *	Length in bytes that can be mapped
 */
int xm_maxmap(struct xmem *, void *, size_t *);

/*
 *  Routines to release or detach a permanently- or temporarily-allocated 
 *    region, which was allocated via vm_ralloc(), as_ralloc(), vm_att(), 
 *    as_att(), or vm_uatt().
 */

/*  vm_det -- Virtual memory detach
 *              Parameters:  (1) caddr_t     effective address
 *              Returns:         nothing
 */

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
void vm_det(caddr_t);
#else
void vm_det();
#endif

/*  xm_det -- Cross memory detach
 *              Parameters:  (1) caddr_t     effective address
 *                           (2) struct xmem *  ptr to cross mem descriptor
 *              Returns:         nothing
 */
void xm_det(caddr_t, struct xmem *);

#ifndef __64BIT_KERNEL
/* 
 * The following routines do not exist on the 64-bit kernel:
 *
 *	vm_seth, getadsp, as_geth, as_puth, as_seth, as_getsrval,
 *	vm_ralloc, as_ralloc, vm_allocsr,
 *	as_att, vm_uatt, as_det, as_init, as_fork,
 *	BUSIO_ATT, BUSIO_DET, IOCC_ATT, IOCC_DET
 *
 */

/*
 *  Routines that operate on virtual memory handles, moving them into
 *  and out of segment registers.
 */

/*  vm_seth -- Virtual memory set handle
 *              Parameters:  (1) vmhandle_t  Handle to set into segment register
 *                           (2) caddr_t     32-bit virtual address, from which
 *                                             segment register is deduced
 *              Returns:         nothing
 */

#if defined(__FULL_PROTO)
void vm_seth(vmhandle_t, caddr_t);
#else
void vm_seth();
#endif

/*  getadsp() - Get address of process's adspace
 *		Parameters: None
 *
 *		returns:	adspace_t *
 */
#ifdef _NO_PROTO
adspace_t *getadsp();
#else
adspace_t *getadsp(void);
#endif

/*  as_geth -- Address space get handle
 *              Parameters:  (1) adspace_t * Ptr to address space struct
 *                           (2) caddr_t     32-bit virtual address, from which
 *                                             segment register is deduced
 *              Returns:         vmhandle_t  Handle from segment register entry
 */

#if defined(__FULL_PROTO)
vmhandle_t as_geth(adspace_t *, caddr_t);
#else
vmhandle_t as_geth();
#endif

/*  as_puth -- Address space put handle
 *              Parameters:  (1) adspace_t * Ptr to address space struct
 *                           (2) vmhandle_t  handle originally from adspace
 *              Returns:         nothing
 */

#if defined(__FULL_PROTO)
void as_puth(adspace_t *, vmhandle_t);
#else
void as_puth();
#endif

/* as_seth -- Address space set handle
 *              Parameters:  (1) adspace_t * Ptr to address space struct
 *                           (2) vmhandle_t  Handle to set into segment register
 *                           (3) caddr_t     32-bit virtual address, from which
 *                                             segment register is deduced
 *              Returns:         nothing
 */

#if defined(__FULL_PROTO)
void as_seth(adspace_t *, vmhandle_t, caddr_t);
#else
void as_seth();
#endif

/*  as_getsrval -- Address space get handle without attach count
 *              Parameters:  (1) adspace_t * Ptr to address space struct
 *                           (2) caddr_t     32-bit virtual address, from which
 *                                             segment register is deduced
 *              Returns:         vmhandle_t  Handle from segment register entry
 */

#if defined(__FULL_PROTO)
vmhandle_t as_getsrval(adspace_t *, caddr_t);
#else
vmhandle_t as_getsrval();
#endif

/* 
 *  Routines that permanently allocate regions 
 */

/*  vm_ralloc -- Virtual memory region allocate
 *              Parameters:  (1) caddr_t     32-bit virtual address (start of
 *                                             segment) which is to be allocated
 *              Returns:         int         0 if allocate succeeded
 *                                           ENOMEM if required segment
 *						 register not available
 */

#define vm_ralloc(addr) vm_allocsr(&csa->as,addr)

#if defined(__FULL_PROTO)
int vm_allocsr(adspace_t *, caddr_t);
#else
int vm_allocsr();
#endif


/*  as_ralloc -- Address space region allocate
 *              Parameters:  (1) adspace_t * Ptr to address space structure
 *                           (2) caddr_t     32-bit virtual address (start of
 *                                             segment) which is to be allocated
 *              Returns:         int         0 if allocate succeeded
 *                                           ENOMEM if required segment
 *						 register not available
 */

#define as_ralloc(adsp,addr) vm_allocsr(adsp,addr)

/*  as_att -- Address space attach 
 *              Parameters:  (1) adspace_t * Ptr to address space structure
 *                           (2) vmhandle_t  Handle to use
 *                           (3) caddr_t     Offset of object (can be passed 
 *					     in as an address; high bits are 
 *					     ignored)
 *              Returns:         caddr_t     effective address to use to 
 *					     address object
 */

#if defined(__FULL_PROTO)
caddr_t as_att(adspace_t *, vmhandle_t, caddr_t);
#else
caddr_t as_att();
#endif

/*  vm_uatt -- Virtual memory current user space attach
 *              This routine allows easy access from the kernel to the
 *              user's address space, such as by copyin() and copyout().
 *              Parameters:  (1) caddr_t     address in process address
 *                                           space of the current process
 *              Returns:         caddr_t     address to use to address object
 */

#define vm_uatt(a) (vm_att(as_geth(&U.U_adspace, (a)),(a)))

/*  as_det -- Address space detach
 *              Parameters:  (1) adspace_t * Ptr to address space
 *                           (2) caddr_t     effective address
 *              Returns:       
 *			      0 = successful
 *		 	      EINVAL = detatching invalid address
 */

#if defined(__FULL_PROTO)
int as_det(adspace_t *, caddr_t);
#else
int as_det();
#endif

/*  
 *  Routine to initialize an address space, so that nothing is addressable
 *  and no regions are allocated.
 */

/*  as_init -- Address space initialization
 *              Parameters:  (1) adspace_t * Ptr to address space
 *              Returns:         nothing
 */

#ifdef _POWER           /* POWER version: */
#define as_init(adsp) { int i;                                \
                        for (i=0; i<NSEGS; i++)               \
                            (adsp)->srval[i] = NULLSEGVAL;    \
                        (adsp)->alloc = 0; }   
#endif /* _POWER */

/*  
 *  Routine to copy the current address space, making everything that
 *  is addressable in the current address space addressable in the new
 *  address space.
 */

/*  as_fork -- Copy address space for fork()
 *              Parameters:  (1) adspace_t * Ptr to address space
 *              Returns:         nothing
 */

#define as_fork(a)					\
	((a)->alloc = u.u_save.as.alloc,		\
	forksregs((a)->srval))

/*  
 *  Routines to assist in using segment registers to address I/O space,
 *  for memory-mapped I/O operations.
 */

/*  BUSIO_ATT -- I/O address attach
 *              Parameters:  (1) ulong       Bus ID value for segment register
 *                           (2) ulong       I/O address
 *              Returns:         caddr_t     32-bit "I/O" address
 *
 *  BUSIO_DET -- I/O address detach
 *		Parameters:  (1) ulong	     32-bit "I/O" address
 *		Returns:		     nothing
 */

#ifdef _POWER           /* POWER version: */
#define BUSIO_ATT(bid,io_addr)	io_att((~(0xf) & (bid)),io_addr)
#define BUSIO_DET(addr)		io_det(addr)
#endif /* _POWER */

/*  
 *  Routines to assist in using segment registers to address memory-
 *  mapped I/O space.
 */

/*  BUSMEM_ATT -- I/O Memory address attach
 *              Parameters:  (1) ulong       Bus ID value for segment register
 *                           (2) ulong       I/O memory address
 *					     note:  an actual memory address in
 *					     the range desired must be supplied
 *					     if the most significant nibble is
 *					     non-zero.
 *              Returns:         caddr_t     32-bit "I/O" memory address
 *
 *  BUSMEM_DET -- I/O Memory address detach
 *		Parameters:  (1) ulong	     32-bit "I/O" memory address
 *		Returns:		     nothing
 */

#ifdef _POWER           /* POWER version: */
#define BUSMEM_ATT(bid,mem_addr)			\
	((__power_pc()) ?						\
	(	io_att((~(0xf) & (bid)) | ((mem_addr)>>28), mem_addr))	\
	:								\
	(	io_att((~(0xf) & (bid)) | ((mem_addr)>>28),  		\
		      ((bid) & 0x40) ? 0x04000000 | ((mem_addr) & 0x00ffffff) : mem_addr)))
#define BUSMEM_DET(addr)		io_det(addr)
#endif /* _POWER */

/*  
 *  Routines to assist in using segment registers to address IOCC
 *  address space.
 */

/*  IOCC_ATT -- IOCC address attach
 *              Parameters:  (1) ulong       Bus ID value for segment register
 *                           (2) ulong       IOCC address
 *              Returns:         caddr_t     32-bit IOCC address
 *
 *  IOCC_DET -- IOCC address detach
 *		Parameters:  (1) ulong	     32-bit IOCC address
 *		Returns:		     nothing
 */

#ifdef _POWER           /* POWER version: */
#define IOCC_ATT(bid,iocc_addr)			\
		io_att(((0x1ff00000 & (bid)) | 0x800c00e0), iocc_addr)
#define IOCC_DET(addr)			io_det(addr)
#endif /* _POWER */

/*  io_att -- (T=1) I/O address attach (T=1 access)
 *              Parameters:  (1) ulong       Value for segment register
 *                           (2) ulong       Offset within segment
 *              Returns:         caddr_t     32-bit "I/O" address
 */
caddr_t io_att();


/*  io_det -- (T=1) I/O address detach
 *		Parameters: (1) ulong        32-bit "I/O" address
 *		Returns:		     nothing
 */
void io_det();

#endif /* ! __64BIT_KERNEL */

/*  iomem_att -- (T=0) I/O address attach (T=0 access)
 *		Parameters:  (1) struct io_map * IO map structure
 *              Returns:         void *     effective "I/O" address
 */
struct io_map {
	int key;			/* structure version number */
	int flags;			/* flags for mapping */
	int32long64_t size;		/* size of address space needed */
	int bid;			/* bus ID */
	long long busaddr;		/* bus address */
};

/*
 * Definitions for the "key" field of the io_map structure
 */
#define	IO_MEM_MAP			1	/* structure version number */

/*
 * Definitions for the "flags" field of the io_map structure
 */
#define IOM_RDONLY			0x0001	/* read only mapping        */
#define IOM_SGSAFE			0x0002	/* internal use only	    */
#ifdef __64BIT_KERNEL
#define	IOM_HIDDEN_MEMORY		0x08000	/* CPSSMEM hidden memory    */
#define	IOM_LGPAGE			0x10000	/* Large pages wanted for   */
						/* hidden memory	    */
#endif


#ifdef _NO_PROTO
void *iomem_att();
#else
void *iomem_att(struct io_map *iop);
#endif

/*  iomem_det -- (T=0) I/O address detach
 *		Parameters: (1) ulong        32-bit "I/O" address
 *		Returns:		     nothing
 */

#ifdef _NO_PROTO
void iomem_det();
#else
void iomem_det(void *eaddr);
#endif

typedef void * io_handle_t;

io_handle_t io_map_init(struct io_map *, vpn_t, io_handle_t);
void *  io_map(io_handle_t);
void    io_unmap(void *);
void    io_map_clear(io_handle_t);
#ifdef __64BIT_KERNEL
int	io_map_init_global(struct io_map *, ulong *);
int	io_map_remove_global(struct io_map *, void *);
long long io_map_getbusaddr(ulong);
#endif

/* IO_MAP_INIT -- This macro can be used to initialize an io_map structure.
 * 	Additional function (smaller mapping granularity, readonly) is
 *	available by filling out individual fields in mapping structure
 *
 *      WARNING: region to map can not cross 256Meg (SEGSIZE) boundary
 */
#define IO_MAP_INIT(iomap, buid, baddr)                               \
{									\
	(iomap)->key = IO_MEM_MAP;					\
	(iomap)->flags = 0;						\
	(iomap)->size = SEGSIZE;					\
	(iomap)->bid = buid;                                            \
	(iomap)->busaddr = baddr;                                       \
}

/*  rmmap_create -- real memory or bus address attach through page table
 *
 *		Parameters:	(1) void **		effective address
 *				(2) struct io_map	I/O map structure
 *				(3) int			protection flags
 *		Returns:
 *				0 = successful
 *				EINVAL = wrong hardware type
 *				ENOSPC = address space conflict
 *				ENOMEM = out of kernel resources
 */

#ifdef _NO_PROTO
int rmmap_create();
#else
int rmmap_create(void **	eaddr,
               struct io_map *	iomp,
               int		flags);
#endif

/* flags for rmmap_create()
 */
#define RMMAP_PAGE_W     0x00000008     /* Page Attribute: Write Through    */
#define RMMAP_PAGE_I     0x00000004     /* Page Attribute: Cache Inhibited  */
#define RMMAP_PAGE_M     0x00000002     /* Page Attribute: Memory Coherency */
#define RMMAP_PAGE_G     0x00000001     /* Page Attribute: Guarded (!601)   */
#define RMMAP_RDONLY     0x00000010     /* Read-Only Page Protection        */
#define RMMAP_RDWR       0x00000020     /* Read-Write Page Protection       */
#define RMMAP_PRELOAD    0x00000040     /* Advise preload HTAB on create    */
#define RMMAP_INHERIT    0x00000080     /* Inherit range on fork()          */
#ifdef __64BIT_KERNEL
#define RMMAP_LGPAGE     0x00000100     /* Limited large page support	    */
#endif

/*  rmmap_remove -- remove real memory or bus address attachment
 *
 *		Parameters:	(1) void **		effective address
 *		Returns:
 *				0 = successful
 *				EINVAL = wrong hardware type
 *				EINVAL = bad effective address
 */

#ifdef _NO_PROTO
int rmmap_remove();
#else
int rmmap_remove(void ** eaddr);
#endif

/*  rmmap_getwimg -- get wimg information for an rmmap'd address range.
 *
 *		Parameters:	(1) unsigned long long   effective address
 *                              (2) uint                 npages
 *                              (3) char          *      results
 *		Returns:
 *				0 = successful
 *				EINVAL = wrong hardware type
 *				EINVAL = bad effective address
 */

int rmmap_getwimg(ptr64 eaddr, uint32long64_t npages, char *results);

#ifndef __64BIT_KERNEL
/* Prototypes for 64-bit application support kernel services for the
 * 32-bit kernel.
 */
int			as_remap64(unsigned long long addr64, uint len,
				uint *addr32);
unsigned long long	as_unremap64(caddr_t addr32);
int			rmmap_create64(unsigned long long * eaddrp,
				struct io_map *iomp, int flags);
int			rmmap_remove64(unsigned long long eaddr);
#endif /* !__64BIT_KERNEL */

#ifdef __64BIT_KERNEL
/* Prototypes for lightweight esid pool kernel services. as_lw_att64
 * and as_lw_det64 only operate on the esids reserved by
 * as_lw_pool_init.  They don't get adspace lock, and lw_detach
 * doesn't do cs_mpc_issue().  The cs_mpc_issue() is only done when the
 * pool has been consumed and needs to be reused.
 */  
int as_lw_pool_init(size_t pool_size, uint flags);
int as_lw_att64(struct xmem *dp, size_t offset, size_t length, ptr64 *addr);
int as_lw_det64(struct xmem *dp, ptr64 addr, size_t length);
#endif /* __64BIT_KERNEL */

/* Barrier Synchronization Register APIs
 */
int bsr_query(int *total_bsr_bytes, unsigned int *supported_windows,
	int *free_bsr_bytes, unsigned int *free_windows);
int bsr_alloc(int bsr_bytes, struct io_map *bsr_map, 
						int *bsr_stride, int *bsr_id);
int bsr_free(int bsr_id);

#endif /* _KERNEL */

#endif /* _H_ADSPACE */
