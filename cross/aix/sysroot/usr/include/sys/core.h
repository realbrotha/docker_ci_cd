/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/core.h 1.3.5.4                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1985,1993              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)96     1.3.5.4  src/bos/kernel/sys/core.h, sysproc, bos53V, v2009_03B2 1/12/09 15:53:52 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: CDATA_ADDR
 *		CSTACK_ADDR
 *		
 *   ORIGINS: 3, 27, 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1985,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_SYS_CORE
#define _H_SYS_CORE

/*
 * IMPORTANT NOTE:
 *
 * The default core file format is being changed in AIX 4.3.  For 
 * compatibility with older systems, the system can be made to produce
 * the old core file format via the command smit, although the old 
 * format cannot be used to represent 64-bit processes.  The system
 * will always utilize the new format when dumping 64-bit processes.
 *
 * The core file begins with either struct core_dump or core_dumpx.  
 * The first three elements of these structures are the same.  The 
 * field c_entries can be used to determine which format was used 
 * when the file was created. 
 *
 * If c_entries == 0, then the new core file format is evident and 
 * struct core_dumpx should be used.  Otherwise struct core_dump should
 * be used.  
 *
 * While the old format is limited to 32-bit processes, the new format
 * supports both 32-bit and 64-bit processes.  dbx will be updated to
 * support the new format in its entirety.  It will continue to support
 * the old format as well.
 *
 * We could have limited the new format to 64-bit processes, but we 
 * wanted to provide additional information describing the kernel state 
 * that is not included in the old format.  This information should be 
 * helpful in debugging multi-threaded applications. 
 *
 * The IS_PROC64() macro can be used to distinquish between 32-bit and
 * 64-bit processes.
 */

#include <sys/user.h>
#include <procinfo.h>
#include <sys/resource.h>

#ifndef __64BIT__  /* { */

/* provides information on vm regions */
struct vm_info {
        void *vminfo_addr;              /* effective address of region */
        int vminfo_size;                /* size of memory region */
        int vminfo_offset;              /* offset in core file of region */
};

/* This is required for compatability with old (4.1) 32-bit core files */

struct pm_heap41 {
	int		lock;           /* zone lock */
	uint            lastin;         /* last freed entry */
	uint            highwater;      /* just beyond last used (monotonic) */
	uint            start;          /* beginning of the zone */
	uint            end;            /* just beyond end of the zone */
	unsigned short  size;           /* size of an element */
	unsigned short  link;           /* offset of link word in an element */
	int		flags;          /* zone flags */
	uint		base;           /* base address (PM_GLOBAL only) */
};

/*
 * 4.1 user structure (u-block)  - Valid only when compiled in 32-bit mode.
 * Moreover, the AIX 4.2 core structure is only valid when user41 is valid.
 */
struct user41 {
	struct pm_heap41 U_uthread_cb;
	struct pm_heap41 U_cancel_cb;
	struct proc	*U_procp;
	Simple_lock	U_handy_lock;
#define NSIG41 64
	void		(*U_signal[NSIG41])(int);
	sigset_t	U_sigmask[NSIG41];
	char		U_sigflags[NSIG41];
	adspace_t	U_adspace;
#define NSEGS41 16
	struct segstate	U_segst[NSEGS41];
	struct vmmlock	U_adspace_lock;
	int		U_auditstatus;
	char		*U_map;
#define MAXCOMLEN41 32
	char		U_comm[MAXCOMLEN41+1];
	char		*U_tstart;
	short		U_lock;
	short		U_pad1;
	Simple_lock	U_cr_lock;
	struct ucred    *U_cred;
	uinfo_t 	U_uinfo;
	int		U_compatibility;
	struct sem_undo	*U_semundo;
	time_t		U_start;
	time_t		U_ticks;
	struct profdata41 {		/* profile arguments */
	    short       *pr_base;	/* buffer base */
	    unsigned    pr_size;	/* buffer size */
	    unsigned    pr_off;		/* pc offset */
	    unsigned    pr_scale;	/* pc scaling */
	} U_prof;
	short		U_acflag;
	struct rusage	U_ru;
	struct rusage	U_cru;
	unsigned	U_tsize;
#define RLIM_NLIMITS41 6
	struct rlimit	U_rlimit[RLIM_NLIMITS41];
	long		U_ioch;
	Simple_lock	U_timer_lock;
#define NTIMERS41 9
	struct trb	*U_timer[NTIMERS41];
	pid_t		*U_ttysid;
	pid_t		*U_ttyp;
	dev_t		U_ttyd;
	off_t		U_ttympx;
	unsigned	*U_ttys;
	int		U_ttyid;
	int		(*U_ttyf)();
	struct upfbuf	*U_message;
	int		U_dsize;
	int		U_sdsize;
	struct pinprof *U_pprof;
	struct xmem	*U_dp;
	struct vnode	*U_cdir;
	struct vnode	*U_rdir;
	short		U_cmask;
	Simple_lock	U_fso_lock;
	long		U_lockflag;
	long		U_fdevent;
	long long	U_irss;
	struct pinu_block *U_pinu_block;
	tid_t		U_ulocks;
	long		U_loader[64];
	short		U_maxofile;
	Simple_lock	U_fd_lock;
#define OPEN_MAX41 2000
	struct ufd	U_ufd[OPEN_MAX41];
};

/*
 * This is the old format describing 32-bit processes.  It can be enabled
 * for all 32-bit processes by the system administrator via SMIT.  The
 * system default is the new format.
 *  
 * The core_dump structure occurs once at the beginning of a core file. 
 */
struct core_dump {
        char            c_signo;        /* signal number (cause of error) */
        char            c_flag;         /* flag to describe core dump type */
        ushort          c_entries;      /* number of core dump modules */
        struct __ld_info32 *c_tab;      /* offset to beginning of core table */
        caddr_t         c_stack;        /* offset of user stack */
        int             c_size;         /* size of user stack */
        struct mstsave  c_mst;      	/* copy of the faulting mst */
	struct user41	c_u;		/* copy of the user structure */
        int             c_nmsts;    	/* number of msts in c_msts */
	struct mstsave  *c_msts;	/* offset to the other threads msts */	
	int		c_datasize;	/* size of data region */
	caddr_t		c_data;		/* offset to user data */
        int             c_vmregions;    /* number of anonymously mapped areas */
        struct vm_info  *c_vmm;         /* offset to start of vm_info table */
};
#else /* __64BIT__: size invariant versions of above */
/* provides information on vm regions */
struct vm_info {
        __ptr32 vminfo_addr;              /* effective address of region */
        int vminfo_size;                /* size of memory region */
        int vminfo_offset;              /* offset in core file of region */
};

/* This is required for compatability with old (4.1) 32-bit core files */

struct pm_heap41 {
	int		lock;           /* zone lock */
	uint            lastin;         /* last freed entry */
	uint            highwater;      /* just beyond last used (monotonic) */
	uint            start;          /* beginning of the zone */
	uint            end;            /* just beyond end of the zone */
	unsigned short  size;           /* size of an element */
	unsigned short  link;           /* offset of link word in an element */
	int		flags;          /* zone flags */
	uint		base;           /* base address (PM_GLOBAL only) */
};

/*
 * 4.1 user structure (u-block)  - Valid only when compiled in 32-bit mode.
 * Moreover, the AIX 4.2 core structure is only valid when user41 is valid.
 */
struct user41 {
	struct pm_heap41 U_uthread_cb;
	struct pm_heap41 U_cancel_cb;
	__ptr32   	U_procp;
	__ptr32		U_handy_lock;
#define NSIG41 64
	__ptr32		U_signal[NSIG41];
	sigset32_t	U_sigmask[NSIG41];
	char		U_sigflags[NSIG41];
	adspace32_t	U_adspace;
#define NSEGS41 16
	struct segstate32 {
		ushort  segflag;		/* type of segment      */
		ushort  num_segs;		/* number of segments   */
        	union {
			uint   mfileno;		/* file descriptor      */
			uint   attr;		/* attributes: SEG_WORKING */
			uint   nsegs;		/* nsegs if SEG_AVAIL */
                	__ptr32  shmptr;		/* shared memory descriptor */
                	uint 	srval;		/* unused field */
        	} u_ptrs;
	   }		U_segst[NSEGS41];
	struct vmmlock32 {
		int	lock_word;	/* per-process U_adspace lock */
		__ptr32   vmm_lock_wait;	/* wait list for lock waiters */
	}		U_adspace_lock;
	int		U_auditstatus;
	__ptr32		U_map;
#define MAXCOMLEN41 32
	char		U_comm[MAXCOMLEN41+1];
	__ptr32		U_tstart;
	short		U_lock;
	short		U_pad1;
	__ptr32		U_cr_lock;
	__ptr32           U_cred;
	uinfo_t 	U_uinfo;
	int		U_compatibility;
	__ptr32           U_semundo;
	time32_t	U_start;
	time32_t	U_ticks;
	struct profdata41 {		/* profile arguments */
	    __ptr32       pr_base;	/* buffer base */
	    unsigned    pr_size;	/* buffer size */
	    unsigned    pr_off;		/* pc offset */
	    unsigned    pr_scale;	/* pc scaling */
	} U_prof;
	short		U_acflag;
	struct trusage32 U_ru;
	struct trusage32 U_cru;
	unsigned	U_tsize;
#define RLIM_NLIMITS41 6
	struct rlimit32	U_rlimit[RLIM_NLIMITS41];
	int		U_ioch;
	__ptr32     	U_timer_lock;
#define NTIMERS41 9
	__ptr32		U_timer[NTIMERS41];
	__ptr32		U_ttysid;
	__ptr32		U_ttyp;
	dev32_t		U_ttyd;
	off_t		U_ttympx; /* XXX?? */
	__ptr32	 	U_ttys;
	int		U_ttyid;
	__ptr32		U_ttyf;
	__ptr32    	U_message;
	int		U_dsize;
	int		U_sdsize;
	__ptr32           U_pprof;
	__ptr32		U_dp;
	__ptr32		U_cdir;
	__ptr32		U_rdir;
	short		U_cmask;
	__ptr32		U_fso_lock;
	int		U_lockflag;
	int		U_fdevent;
	long long	U_irss;
	__ptr32		U_pinu_block;
	tid32_t		U_ulocks;
	int		U_loader[64];
	short		U_maxofile;
	__ptr32		U_fd_lock;
#define OPEN_MAX41 2000
	struct fdsinfox U_ufd[OPEN_MAX41];
};

/*
 * This is the old format describing 32-bit processes.  It can be enabled
 * for all 32-bit processes by the system administrator via SMIT.  The
 * system default is the new format.
 *  
 * The core_dump structure occurs once at the beginning of a core file. 
 */
struct core_dump {
        char            c_signo;        /* signal number (cause of error) */
        char            c_flag;         /* flag to describe core dump type */
        ushort          c_entries;      /* number of core dump modules */
        __ptr32         c_tab;          /* offset to beginning of core table */
        __ptr32         c_stack;        /* offset of user stack */
        int             c_size;         /* size of user stack */
        struct mstsave32 c_mst;      	/* copy of the faulting mst */
	struct user41	c_u;		/* copy of the user structure */
        int             c_nmsts;    	/* number of msts in c_msts */
	__ptr32         c_msts;		/* offset to the other threads msts */	
	int		c_datasize;	/* size of data region */
	__ptr32		c_data;		/* offset to user data */
        int             c_vmregions;    /* number of anonymously mapped areas */
        __ptr32         c_vmm;          /* offset to start of vm_info table */
};
#endif

/* User Key exception structure */
struct kukeyctx {
	unsigned long long	u_ukset;
	unsigned long long	u_eaddr;
	int			u_eukey;
};

/* Core file name, header size, maximum loader table size */
#define CHDRSIZE	(sizeof(struct core_dump))
#define CTABSIZE	(sizeof(struct __ld_info32) + MAXPATHLEN + MAXNAMLEN)

/* Macro to determine the starting user address given the length and type */
#define CDATA_ADDR(x)	(PRIVORG)
#define CSTACK_ADDR(x)	(USRSTACK - x)

#define COREFILE	"core"
#define COREFILE_COMP	"core.Z"

/* Values for the c_flag field */
#define FULL_CORE       0x01            /* core contains the data sections */
#define CORE_VERSION_1  0x02            /* 0 = AIX V3, 1 = AIXV4.1 - AIX4.2 */
#define MSTS_VALID      0x04            /* the u_threads have been dumped */
#define CORE_BIGDATA    0x08            /* records big data usage */
#define UBLOCK_VALID    0x10            /* the u_block has been dumped */
#define USTACK_VALID    0x20            /* the user stack has been dumped */
#define LE_VALID        0x40            /* core contains at least 1 module */
#define CORE_TRUNC      0x80            /* core was truncated (see setrlimit) */

/* 
 * The Extended context table is an array of struct thrdectx with 
 * c_n_extctx elements
 */ 
struct ectxhdr {
	unsigned long long ectx_tid;  /* thread id for this ctx           */
	unsigned long long ectx_size; /* size of the extended ctx info    */
};
struct thrdectx {
	struct ectxhdr h;
	struct ectx {
	    unsigned int	   ectx_flags;	/* __extctx_t __flags field   */
	    unsigned int	   ectx_rsvd[3];/* __extctx_t __rsvd field    */
	    __vmx_context_t	   ectx_vmx;	/* __extctx_t __vmx field     */
	    /* fields added to __extctx_t must also be added here, if they
	     * need to be in the core image
	     */
	}e;
};

/* 
 * The thread context table is an array of struct thrdctx with c_n_thr elements
 */ 
struct thrdctx {
	struct thrdsinfo64 th;		/* general thread info */
	union {
	   	struct __context64 r64; /* hardware context if 64-bit */
	   	struct mstsave32 r32;	/* hardware context if 32-bit */
	} hctx;
};
/*
 * This structure is to provide support for new 64-bit ABI in bos5.0.
 */ 
struct thrdctx64 {
	struct thrdentry64 th;		/* general thread info */
   	struct __context64 r64; 	/* hardware context 64-bit */
};

struct userx {

	/* The sub-fields pi_utime, pi_stime, and pi_cru are not filled out. */
	struct procsinfo64	U_proc;	

	unsigned long long 	U_resvd[16];
};
/*
 * This structure is to provide support for new 64-bit ABI in bos5.0.
 */ 
struct userx64 {
	struct procentry64	U_proc;	
	unsigned long long 	U_resvd[16];
};

/* describes shmat'd regions */
struct segregion {
	unsigned long long addr;	/* start effective address */
	unsigned long long size;	/* size of the region */
	unsigned long long offset;      /* core file offset */
	int       segflags;		/* type of segment (seg.h) */
	int 	  reserved;		/* reserved for future use */
};


/* provides information on vm regions */
struct vm_infox {
        unsigned long long vminfo_addr;    /* effective address of region */
        unsigned long long vminfo_size;    /* size of memory region */
        unsigned long long vminfo_offset;  /* offset in core file of region */
};

/* provides information to vm_map_core() */
struct kvm_infox {
	struct vm_infox infox;
	uint flags;
};

#define	ADDR_VM_INFOX(ptr)	&(ptr->infox)
		
#define _CORE_MAP_ANONYMOUS	0x00
#define _CORE_MAP_FILE          0x01
#define _CORE_MAP_PRIVATE       0x02

#define DUMP_MAP_ANON           0x01
#define DUMP_MAP_FILE           0x02
#define DUMP_MAP_NOSHM          0x04

/*
 * The new core file format bos43 release.
 */ 
struct core_dumpx {

        /*
         * First three elements are the same as the struct core_dump.
         * If the field c_entries == 0, then the core file in question
         * follows the new format.
         */
        char               c_signo;     /* signal number (cause of error) */
        char               c_flag;      /* flag to describe core dump type */
        ushort             c_entries;   /* number of core dump modules */

        int                c_version;   /* core file format number */

	/*
	 * The size of the fdsinfox section in core file can be obtained by
	 * either  1] FD_HW_MARK(&(c_u.U_proc)) * sizeof(fdsinfox)
	 * or      2] c_loader - c_fdsinfox
	 * NOTE: FD_HW_MARK is defined in procinfo.h.
	 */
	unsigned long long c_fdsinfox;	/* offset to fd region in file */

	unsigned long long c_loader;	/* offset to loader region in file */
	unsigned long long c_lsize;	/* size of loader region */

        uint               c_n_thr;     /* number of elements in thread table */
	uint 		   c_reserved0; /* Padding */
        unsigned long long c_thr;       /* offset to thread context table */

	unsigned long long c_segs;	/* n of elements in segregion */
	unsigned long long c_segregion;	/* offset to start of segregion table */

        unsigned long long c_stack;     /* offset of user stack in file */
        unsigned long long c_stackorg;  /* base address of user stack region */
        unsigned long long c_size;      /* size of user stack region */

        unsigned long long c_data;      /* offset to user data region */
        unsigned long long c_dataorg;   /* base address of user data region */
        unsigned long long c_datasize;  /* size of user data region */
        unsigned long long c_sdorg;	/* base address of sdata region */
        unsigned long long c_sdsize;  	/* size of sdata region */

        unsigned long long c_vmregions; /* number of anonymously mapped areas */
        unsigned long long c_vmm;       /* offset to start of vm_infox table */

	int                c_impl;	/* processor implementation */
	unsigned int       c_n_extctx;  /* n of elements in extended ctx table*/
	unsigned long long c_cprs;	/* Checkpoint/Restart offset */
	unsigned long long c_extctx;	/* Extended Context Table offset */
	unsigned long long c_ukeyctx;	/* Offset to user-key exception data */
	unsigned long long c_loader2;	/* offset to loader region in file
					   when a process uses TLS data */
	unsigned long long c_lsize2;	/* size of the above loader region */
	unsigned long long c_reserved[3];

        struct thrdctx     c_flt;       /* faulting thread's context */

        struct userx       c_u;         /* copy of the user structure */
};
/*
 * The new core file header for new 64-bit ABI in bos5.0. The 32-bit 
 * applications in bos5.0 continues to use 43 core file header format
 * as laid out by core_dumpx.
 */ 
struct core_dumpxx {

        /*
         * First three elements are the same as the struct core_dump.
         * If the field c_entries == 0, then the core file in question
         * follows the new format.
         */
        char               c_signo;     /* signal number (cause of error) */
        char               c_flag;      /* flag to describe core dump type */
        ushort             c_entries;   /* number of core dump modules */

        int                c_version;   /* core file format number */

	/*
	 * The size of the fdsinfox section in core file can be obtained by
	 * either  1] FD_HW_MARK(&(c_u.U_proc)) * sizeof(fdsinfox)
	 * or      2] c_loader - c_fdsinfox
	 * NOTE: FD_HW_MARK is defined in procinfo.h.
	 */
	unsigned long long c_fdsinfox;	/* offset to fd region in file */

	unsigned long long c_loader;	/* offset to loader region in file */
	unsigned long long c_lsize;	/* size of loader region */

        uint               c_n_thr;     /* number of elements in thread table */
	uint 		   c_reserved0; /* Padding */
        unsigned long long c_thr;       /* offset to thread context table */

	unsigned long long c_segs;	/* n of elements in segregion */
	unsigned long long c_segregion;	/* offset to start of segregion table */

        unsigned long long c_stack;     /* offset of user stack in file */
        unsigned long long c_stackorg;  /* base address of user stack region */
        unsigned long long c_size;      /* size of user stack region */

        unsigned long long c_data;      /* offset to user data region */
        unsigned long long c_dataorg;   /* base address of user data region */
        unsigned long long c_datasize;  /* size of user data region */
        unsigned long long c_sdorg;	/* base address of sdata region */
        unsigned long long c_sdsize;  	/* size of sdata region */

        unsigned long long c_vmregions; /* number of anonymously mapped areas */
        unsigned long long c_vmm;       /* offset to start of vm_infox table */

	int                c_impl;	/* processor implementation */
	unsigned int       c_n_extctx;  /* n of elements in extended ctx table*/
	unsigned long long c_cprs;	/* Checkpoint/Restart offset */
	unsigned long long c_extctx;	/* Extended Context Table offset */
	unsigned long long c_ukeyctx;	/* Offset to user-key exception data */
	unsigned long long c_loader2;	/* offset to loader region in file
					   when a process uses TLS data */
	unsigned long long c_lsize2;	/* size of the above loader region */
	unsigned long long c_reserved[3];

        struct thrdctx64     c_flt;       /* faulting thread's context */

        struct userx64       c_u;         /* copy of the user structure */
};

#define GENCORE_VERSION_1	0x00000001

struct coredumpinfo {
        int length; 		/* string length of core file name */
#ifdef __64BIT__
	int pad;
#endif 
        char *name;		/* pointer to string containing core file name */
	pid_t pid;
	int flags;
#ifndef __64BIT__
        int reserved[6];	/* FUTURE USE */
#else
	int reserved[4];
#endif
};

struct cprs_info {
	pid_t rpid;
	pid_t vpid;
	unsigned int trans_tid_off;
	unsigned int trans_tid_size;
	unsigned long long reserved[8]; /* Future use */
};

struct trans_tid_table {
	tid_t rtid;
	tid_t vtid;
};

extern int gencore(struct coredumpinfo *);
extern int coredump(struct coredumpinfo *);



#endif  /* _H_SYS_CORE */

