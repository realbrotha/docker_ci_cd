/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/vmuser.h 1.96                                */
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
/* @(#)82	1.96  src/bos/kernel/sys/vmuser.h, sysvmm, bos53D, d2005_13C0 3/24/05 15:04:11 */

#ifndef _H_VMUSER
#define _H_VMUSER
/*
 * COMPONENT_NAME: (SYSVMM) Virtual Memory Manager
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27 83
 *
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */

/*
 * FUNCTION: definitions for users within the kernel of VMM
 */

/*
 * parameters for vms_create() and/or vm_galloc()
 */

#include <sys/rset.h>
#include <sys/buf.h>
#include <sys/uio.h>

#define V_WORKING	0x1
#define V_CLIENT	0x2
#define V_PERSISTENT	0x4
#define V_JOURNAL	0x8
#define V_DEFER 	0x10
#define V_SYSTEM	0x20
#define V_LOGSEG	0x40
#define V_UREAD 	0x80
#define V_PTASEG	0x100
#define V_PRIVSEG	0x200
#define V_INTRSEG	0x400
#define V_MAPPING	0x800
#define V_PSEARLYALLOC  0x1000 
#define V_SHRLIB	0x2000
#define V_SPARSE	0x4000
#define V_LARGE		0x8000
#define V_LRGEXT	0x10000
#define V_RMMAP		0x20000
#define V_ASYNC		0x40000
#define V_STACKSEG      0x80000
#define V_FREEZE        0x100000
#define V_RMMAPIO       0x200000
#define V_PERMFREEZE    0x400000
#define V_ACCT		0x800000  /* accounting is desired */
#define V_ATTACH	0x1000000 /* attachment is desired */
#define V_TEXTCOPY	0x2000000
#ifdef __64BIT_KERNEL
#define V_USERACC	0x4000000	/* global sid access in user mode */
#endif /* __64BIT_KERNEL */
#define V_PIN		0x8000000	/* pin all pages segment */
#define V_LGPAGE	0x10000000	/* back with large pages */
#define V_SHMSEG        0x20000000      /* segment is for shared memory */
#ifdef __64BIT_KERNEL
#define V_RSVD_VSID     0x40000000      /* use a reserved vsid */
#define V_NOEXEC        0x80000000      /* default no-execute policy */
#endif /* __64BIT_KERNEL */

/*
 * parameters for vm_write
 */

#define V_NOFORCE	0x0
#define V_FORCE 	0x1
#define V_FORCE_SYNC	0x2
#define V_ASYNC_FLAG	0x4
#define V_COMMIT	0x8

/*
 * parameters for vm_read
 */

#define	V_IOWAIT	0x1
#define	V_ALLDONE	0x2

/*
 * parameters for vm_release
 */

#define V_NOKEEP	0
#define V_KEEP		1
#define V_CHECKXPT	2
#define V_CHECKPIN	4

/*
 * options for v_getxpt
 */
#define V_TOUCH 	1
#define V_NOTOUCH	0

/*
 * parameters for vm_protect
 */

#define KERKEY		0
#define UBLKKEY		0
#define FILEKEY		1
#define UTXTKEY		1
#define UDATAKEY	2
#define RDONLY		3
#define NOACCESS        64

/*
 * parameters for vm_ioaccessp
 */

#define VM_IOACCESSP_MAKE       0x0001
#define VM_IOACCESSP_FLUSH      0x0002
#define VM_IOACCESSP_PGINWAIT   0x0004
#define VM_IOACCESSP_PGOUTWAIT  0x0008
#define VM_IOACCESSP_WAITONLY   0x0010

/*
 * parameters for vm_mvc
 */

#define VM_MVC_ZERO     1
#define VM_MVC_READ     2
#define VM_MVC_WRITE    3
#define VM_MVC_PROTZERO 4

/* 
 * flags for vms_iowaitf
 */
#define V_WAITERR	0
#define V_WAITALL	1
#define	V_IOERROR	2
/* V_HADEXCEPTION is an internal flag, not legal to pass it into a call */
#define V_HADEXCEPTION  4

/*
 * parameters for vm_mount and PDT routines
 */
#define D_PAGING	1
#define D_FILESYSTEM	2
#define D_REMOTE	4
#define D_LOGDEV	8
#define D_SERVER	16
#define D_LOCALCLIENT	32

/*
 * optional flag bits for the "type" parameter for vm_mount and PDT
 * routines.
 */
#define D_FLAGMASK  	0xFFFF0000                   /* Mask for flag bits    */
#define DEVTYPE(x)	(x & ~(D_FLAGMASK))	     /* extract type only     */
#define DEVFLAGS(x)	(x & D_FLAGMASK)	     /* extract flags only    */
#define D_PREXLATE  	0x80000000                   /* pretranslation enabled*/
#define D_THRPGIO       0x40000000                   /* thread page io API    */
#define D_ENHANCEDIO    0x20000000                   /* enhanced I/O aware fs */
#define D_RB_READ	0x10000000		/* Release-behind for reads */
#define D_RB_WRITE	0x08000000		/* Release-behind for writes */
#define D_EXTPAGER	0x04000000		/* external pager API    */


/*
 * maximum file size in bytes (JFS)
 */
#ifdef _LONG_LONG

#define MAX_BFSIZE	(1LL << 36)
#ifdef __64BIT_KERNEL
#define MAX_CBFSIZE	((1LL << 44)-4096) /* One page less than 16 terabytes */
#else
#define MAX_CBFSIZE	(1LL << 40)
#endif

#elif defined(__64BIT__)

#define MAX_BFSIZE	(1L << 36)
#ifdef __64BIT_KERNEL
#define MAX_CBFSIZE	((1L << 44)-4096) /* One page less than 16 terabytes */
#else
#define MAX_CBFSIZE	(1L << 40)
#endif

#endif

#define MAXFSIZE	((uint)(1 << 31))

#ifdef __64BIT_KERNEL
/* flags for vm_guatt(). */
#define VU_INPLACE     0x1
#define VU_ANYWHERE    0x2
#endif /* __64BIT_KERNEL */

/*
 * return codes used within VMM
 * Note that both VM_WAIT and VM_NOWAIT
 * have a definition in ml (cf vmvcs.s)
 */
#define VM_OK		 0
#define VM_WAIT 	-1
#define VM_ECC		-2
#define VM_XMEMCNT	-3
#define VM_EXTMEM	-4
#define VM_NOTIN	-5
#define VM_NOPFAULT	-6
#define VM_UNHIDE	-7
#define VM_NOTMINE	-8
#define VM_NOWAIT 	-9
#define VM_NOSPACE      -10
#define VM_SPARSE	-11
#define VM_NOXPT	-12
#define VM_XMDBG	-13
#define VM_CMDIRTY	-14
#define VM_KPROC      	-15

/* following macros to convert an errno to negative value that is returned
 * from the VMM CS, and convert back in the base level to a positive value 
 * again. Thus we effectively map -129 thru -255 rcs, and allow any errno
 * to be returned. */
#define ERRNO_2_VMERRNO(errno) (((errno) > 0) ? (errno)-256 : (errno))
#define VMERRNO_2_ERRNO(vmerrno) ((vmerrno)+256)


/*
 * flag to check if paging space is defined
 *	0 - paging space defined
 *	nonzero - paging space not defined
 */
extern int ps_not_defined;

/*
 *  vmm_client_info is the structure for passing information between the
 *  creator of an ASYNC client segemnt and the VMM.  The address of this
 *  structure is passed to the VMM on the vms_create() call in the
 *  gnode_ptr->gn_data field.
 */
struct vmm_client_info {
	uint     magic;		/* "ACLI" means structure is valid */
	unsigned async    : 1;	/* ASYNC write supported? */
	unsigned pgahead  : 1;	/* read-ahead supported? */
	unsigned combehind: 1;	/* commit-behind supported? */
	unsigned max_xfer : 3;	/* log base 2 of max xfer size - 12 */
				/*     4K=0, 8K=1, 16K=2, 32K=3, 64K=4 */
	unsigned ncgather : 1;	/* new commit gathering enabled */
	unsigned rbr      : 1;	/* release-behind on read enabled */
	unsigned rsvd_bits: 24;	/* unused */
	short	numclust;	/* # max_xfer size clstrs (wrbehind) */
	short	maxpgahead;	/* max # max_xfer size clstrs to pageahead */
	int     maxrandwrt;	/* threshold to start random write-behind */
	int     wrb_cluster;	/* write-behind history data */
	int     wrb_randcnt;	/* random write-behind history data */
	/* below only valid for magic == "ACPG" */
	int     maxpout;        /* i/o pacing up limit */
	int     minpout;        /* i/o pacing down limit */
};

/*
 * Valid magic field.
 */
#define ASYNC_CLIENT_MAGIC	0x41434C49	/* "ACLI" */
#define ASYNC_CLIENT_MAGIC_2    0x41435047      /* "ACPG" */

/*
 *  Valid values for max_xfer
 */
#define MAX_XFER_4K	0
#define MAX_XFER_8K	1
#define MAX_XFER_16K	2
#define MAX_XFER_32K	3
#define MAX_XFER_64K	4
#define MAX_XFER_128K	5
#define MAX_XFER_256K	6
#define MAX_XFER_512K	7

/*
 *  Macros for converting max_xfer to bytes (MAX_XFERTB)
 *  and pages (MAX_XFERTP).
 */
#define MAX_XFERTB(max_xfer)	(1 << ((max_xfer) + 12))
#define MAX_XFERTP(max_xfer)	(1 << (max_xfer))


#ifdef _KERNEL
/*
 * Extended buf struct used by D_THRPGIO client filesystems.
 */

typedef struct bufthrio		bufthrio_t;

struct bufthrio {
	struct buf	 bt_buf;
	struct thread ** bt_waitlist; 	/* ptr to an existing waitlist */
	tid_t		 bt_event;
	intptr_t         bt_generation;
};

#define UT_PGIO_SAVE_COUNT 3

typedef struct ut_pgio_context	ut_pgio_context_t;

struct ut_pgio_context {
	ut_pgio_context_t	*utpc_next;
	bufthrio_t		*utpc_ioerror_bplist;
	struct buf		*utpc_bplist;
	rpn_t			 utpc_tail;
	intptr_t		 utpc_save[UT_PGIO_SAVE_COUNT];
	void			*utpc_pad[2];
};

/* structure in pdtentry for extra thrpgio FS info. All fields in here
 * must be passed by the caller of the mount routine */
struct thrpginfo {
        vmsize_t  mysize;       /* byte size of this struct */
        vmsize_t  bufstsz;      /* size of buf structs for this PDT entry */
        vmsize_t  numbufs;      /* num of buf structs to be allocated */
        vmsize_t  numwresvd;    /* num of buf structs resvd for write only */
        int       initwrkrs;    /* initial number of vmm worker threads */
        int       buf2thr;      /* ratio of bufs per wrkr thr, 0 for default */
};

struct thrpginfox {
        vmsize_t  num_free;     /* total num buf structs free, reads+writes */
        vmsize_t  numrd_free;   /* num buf structs free for reads and writes */
        int       bufrefs;      /* buf struct references (hold count) */
        void     *strategy;
        struct buf * firstbp;   /* ptr to first buf struct */
        struct thrpginfo args;  /* values passed to vm_mounte() */
};


/*
 * Initialization value for thread's ut_pgio_tail field.
 * Must not be -1, that corresponds to empty list once v_thrpgio_setup()
 * has been invoked once per series of v_pdtqthriox() invocations.
 * Must also be < 0 so that it cannot be confused with a valid nfr value.
 *
 * The value UT_THRPGIOTAIL_INIT, if left in ut_pgio_tail when
 * v_pdtqthriox() is invoked, it will cause an assertion failure.
 * The purpose of the assertion is to ensure that any path that causes
 * v_pdtqthriox() to be invoked has been coded to cause v_getiobp() to
 * get the buf/strategy for the nfrs in the ut_pgio_tail and process
 * them.
 */

#define UT_THRPGIOTAIL_INIT		(-2)
#define UT_THRPGIOTAIL_PFGET		(-3)
#define UT_THRPGIOTAIL_PFPROT		(-4)
#define UT_THRPGIOTAIL_READP		(-5)
#define UT_THRPGIOTAIL_WRITEP		(-6)
#define UT_THRPGIOTAIL_FLUSHP		(-7)
#define UT_THRPGIOTAIL_IOACCESSP	(-8)
#define UT_THRPGIOTAIL_WORKER		(-9)

/*
 * signature for blocking strategy filesystem entry point
 */

typedef void (*thrpgio_t)(struct buf *bp, int flags, int path);

/*
 * thrpgio_t flags argument values (bit flags not enumeration)
 */

#define VM_THRPGIO_USERMODE	0x000000001	/* PFGET and PFPROT only */

#endif 	/* _KERNEL */

/*
 *  Macros for computing page aligned boundaries for store
 *  protection of kernel text
 */
#if defined( __64BIT_KERNEL) || defined(__FULL_PROTO)

/* the address of the first byte of the page we're on */
#define STARTOFPAGE(x)  ((char *)((ulong)x & ~(PAGESIZE-1)))

/* the first byte of the next page */
/* unless x is the first byte of the page */
#define NEXTPAGE(x)     ((char *)(((ulong)x+(PAGESIZE-1)) & (~(PAGESIZE-1))))

#define USER_PROTECT(x,y,a) if (STARTOFPAGE(y) > NEXTPAGE(x))  \
        vm_map(NEXTPAGE(x), ((a)+NEXTPAGE(x)), STARTOFPAGE(y)-NEXTPAGE(x))

#else

/* the address of the first byte of the page we're on */
#define STARTOFPAGE(x)  (x & ~(PAGESIZE-1))

/* the first byte of the next page */
/* unless x is the first byte of the page */
#define NEXTPAGE(x)     ((x+(PAGESIZE-1)) & (~(PAGESIZE-1)))

#define USER_PROTECT(x,y,a) if (STARTOFPAGE(y) > NEXTPAGE(x))  \
        vm_map((char *)NEXTPAGE(x), (char *)((a)+NEXTPAGE(x)), \
			STARTOFPAGE(y)-NEXTPAGE(x))

#endif /* __64BIT_KERNEL */

#define STORE_PROTECT(x,y) if (STARTOFPAGE(y) > NEXTPAGE(x))  \
        vm_protect(NEXTPAGE(x),STARTOFPAGE(y)-NEXTPAGE(x),RDONLY)
#define UN_PROTECT(x,y) if (STARTOFPAGE(y) > NEXTPAGE(x))  \
        vm_protect(NEXTPAGE(x),STARTOFPAGE(y)-NEXTPAGE(x),KERKEY)

/* Prototypes for kernel services to be used with 64 bit kernel*/
#ifdef _KERNEL

#if defined( __64BIT_KERNEL) || defined(__FULL_PROTO)

int vms_create(vmid_t *vmid, int type, dev_t devno, vmsize_t usize, 
			vmsize_t uplim, vmsize_t downlim);
int vms_delete(vmid_t vmid);

int vms_segtype(vmid_t vmid);

int vms_iowait(vmid_t vmid);

int vms_iowaitf(vmid_t vmid, int flags);

int vms_inactive(vmid_t vmid);

#ifndef _KERNSYS
vmhandle_t vm_handle(vmid_t vmid, vmkey_t key);
#endif

struct gnode;

int vm_makep(vmid_t vmid, vpn_t pno);

int vm_mount(int type, dev_t devid, vmsize_t nbufs);
int vm_mounte(int, dev_t, struct thrpginfo *);

int vm_move(vmid_t vmid, off_t off, vmsize_t limit, enum uio_rw rw, 
		struct uio *uio);

int vm_uiomove(vmid_t vmid, vmsize_t nbytes,  enum uio_rw rw, struct
                uio *uio);

int vm_protect(void *  vaddr, vmsize_t nbytes, int key);

int vm_protectp(vmid_t vmid, vpn_t pfirst, vpn_t npages, int key);

int vm_release(void * vaddr, vmsize_t nbytes);

int vm_releasep(vmid_t vmid,vpn_t pfirst,vpn_t npages);

int vm_qmodify(vmid_t vmid);
vpn_t  vm_qpages(vmid_t);

int vm_write(void * vaddr, vmsize_t nbytes, int force);
int vm_writep(vmid_t vmid, vpn_t pfirst, vpn_t npages);
int vm_xwritep(vmid_t vmid, vpn_t pfirst, vpn_t npages, int flags);
#define VMW_FULLSYNC		0x1
#define VMW_WRITE_BEHIND	0x2

int vm_umount(int type, dev_t devid);
int vm_umountx(int type, dev_t devid, struct buf **);

int vm_flushp(vmid_t vmid, vpn_t pfirst, vpn_t npages);

int vm_ioaccessp(vmid_t vmid, vpn_t pfirst, vpn_t npages, uint modifier);

ut_pgio_context_t * vm_thrpgio_top();
void vm_thrpgio_push(ut_pgio_context_t *tc);
void vm_thrpgio_pop(ut_pgio_context_t *tc);

int vm_segmap(vmid_t basesid, vpn_t pfirst, uint flags, caddr_t *basepp);

/*
 * External pager service
 */
int vm_xpager_bind(vmid_t *, int, dev_t, struct gnode *,
		vmsize_t, uint);

int vm_xpager_mount(dev_t, vmsize_t, int (*)(), uint);

int vm_zeropage(vmid_t, offset_t, size_t);
int vm_touchpage(vmid_t, offset_t);

/*
 * Prototypes for VMM attachment services
 */
int vms_create_attach(vmid_t *vmid, int type, dev_t devno,
		      vmsize_t usize, vmsize_t uplim, vmsize_t downlim,
		      rsethandle_t rset, uint_t policy);
int vm_attach(vmid_t vmid, offset_t offset, vmsize_t size,
	      rsethandle_t rset, uint_t policy);
int vm_detach(vmid_t vmid, offset_t offset, vmsize_t size, int *nb_att);

#endif /* ( __64BIT_KERNEL) || (__FULL_PROTO) */


#ifdef __64BIT_KERNEL

/* 64-bit kernel only interface protos. */

int vm_galloc(int, vmsize_t, ulong *);
int vm_gfree(ulong, vmsize_t);

int vm_guatt(void *, vmsize_t, vmkey_t, long, void **);
int vm_gudet(void *, void *, vmsize_t, long);

/*
 * Prototype for VMM attachement services
 */
int vm_galloc_attach(int, vmsize_t, ulong *, rsethandle_t, uint_t);

#endif /* __64BIT_KERNEL */

#endif /* _KERNEL */

#endif /* _H_VMUSER */
