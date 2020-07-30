/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/POWER/mstsave.h 1.19.6.10                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)30  1.19.6.10  src/bos/kernel/sys/POWER/mstsave.h, sysproc, bos53V, v2009_13A8 3/25/09 16:32:55 */
/*
 *   LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_MSTSAVE
#define _H_MSTSAVE

#ifndef _H_STANDARDS
#include <standards.h>
#endif

/*
 *		Machine State Save Area -- R2 platform
 *
 *  Machine state save area. The fields for the segment registers,
 *  general purpose registers, and floating point registers are
 *  aligned to minimize the number of cache lines that contain them.
 *  Therefore this structure should be aligned on a cache line
 *  boundary.
 */

#include <sys/m_param.h>		/* for machine dependent defines*/
#include <sys/m_types.h>		/* for machine dependent typedefs */



/*
 * XPG4.2 requires structure elements to be defined such that they do not 
 * pollute the namespace.  Additional elements to these structures should
 * be added after the "#endif", and always prepended with "__".
 */

struct
#ifdef _ALL_SOURCE
mstsave
#else /* _ALL_SOURCE */
__mstsave
#endif /* _ALL_SOURCE */
{
#ifdef _ALL_SOURCE
	struct mstsave *prev;		/* previous save area		*/
	label_t		*kjmpbuf;	/* pointer to saved context	*/
	char		*stackfix;	/* stack fix pointer		*/
	char		intpri; 	/* interrupt priority		*/
	char		backt;		/* back-track flag		*/
	char		rsvd[2];	/* reserved			*/
	pid_t		curid;		/* copy of curid		*/

	int		excp_type;	/* exception type for debugger	*/
	ulong_t		iar;		/* instruction address register	*/
	ulong_t		msr;		/* machine state register	*/
	ulong_t		cr;		/* condition register		*/
	ulong_t		lr;		/* link register		*/
	ulong_t		ctr;		/* count register		*/
	ulong_t		xer;		/* fixed point exception	*/
	ulong_t		mq;		/* multiply/quotient register	*/
 	ulong_t		tid;		/* tid register			*/
	ulong_t		fpscr;		/* floating point status reg	*/
	char		fpeu;		/* floating point ever used	*/
	char            fpinfo;         /* floating point status flags  */
	uchar		fpscr24_31;	/* bits 24-31 of 64-bit FPSCR   */
	char            pad[1];         /* res - pad to dword boundary  */
	ulong_t         except[5];	/* exception structure          */
	char            pad1[4];        /* old bus field                */
	ulong_t         o_iar;          /* old iar (for longjmp excpt)  */
	ulong_t         o_toc;          /* old toc (for longjmp excpt)  */
	ulong_t         o_arg1;         /* old arg1 (for longjmp excpt) */
	ulong_t		excbranch;	/* if not NULL, address to branch
					 * to on exception.  Used by
					 * assembler routines for low
					 * cost exception handling*/
	ulong_t         fpscrx;         /* software extension to fpscr  */
	ulong_t         o_vaddr;        /* Saved vaddr for vmexception  */
	ulong_t		cachealign[7];	/* reserved			*/
	adspace_t	as;		/* segment registers            */
	ulong_t		gpr[_NGPRS];	/* general purpose registers	*/
	double		fpr[_NFPRS];	/* floating point registers	*/
#else /* _ALL_SOURCE */
	struct __mstsave *__prev;	/* previous save area		*/
	label_t		*__kjmpbuf;	/* pointer to saved context	*/
	char		*__stackfix;	/* stack fix pointer		*/
	char		__intpri; 	/* interrupt priority		*/
	char		__backt;	/* back-track flag		*/
	char		__rsvd[2];	/* reserved			*/
	pid_t		__curid;	/* copy of curid		*/

	int		__excp_type;	/* exception type for debugger	*/
	ulong_t		__iar;		/* instruction address register	*/
	ulong_t		__msr;		/* machine state register	*/
	ulong_t		__cr;		/* condition register		*/
	ulong_t		__lr;		/* link register		*/
	ulong_t		__ctr;		/* count register		*/
	ulong_t		__xer;		/* fixed point exception	*/
	ulong_t		__mq;		/* multiply/quotient register	*/
 	ulong_t		__tid;		/* tid register			*/
	ulong_t		__fpscr;	/* floating point status reg	*/
	char		__fpeu;		/* floating point ever used	*/
	char            __fpinfo;       /* floating point status flags  */
	uchar_t		__fpscr24_31;	/* bits 24-31 of 64-bit FPSCR   */
	char            __pad[1];       /* res - pad to dword boundary  */
	ulong_t         __except[5];	/* exception structure          */
	char            __pad1[4];      /* old bus field                */
	ulong_t         __o_iar;        /* old iar (for longjmp excpt)  */
	ulong_t         __o_toc;        /* old toc (for longjmp excpt)  */
	ulong_t         __o_arg1;       /* old arg1 (for longjmp excpt) */
	ulong_t		__excbranch;	/* if not NULL, address to branch
					 * to on exception.  Used by
					 * assembler routines for low
					 * cost exception handling*/
	ulong_t         __fpscrx;       /* software extension to fpscr  */
	ulong_t         __o_vaddr;      /* Saved vaddr for vmexception  */
	ulong_t		__cachealign[7];/* reserved			*/
	adspace_t	__as;		/* segment registers            */
	ulong_t		__gpr[_NGPRS];	/* general purpose registers	*/
	double		__fpr[_NFPRS];	/* floating point registers	*/
#endif /* _ALL_SOURCE */
};

#ifdef _ALL_SOURCE
/*
 * This structure provides the 64-bit and 32-bit kernel with a size 
 * invariant view of a 32-bit mstsave.
 */
struct mstsave32
{
	__ptr32		prev;		/* previous save area		*/
	__ptr32		kjmpbuf;	/* pointer to saved context	*/
	__cptr32	stackfix;	/* stack fix pointer		*/
	char		intpri; 	/* interrupt priority		*/
	char		backt;		/* back-track flag		*/
	char		rsvd[2];	/* reserved			*/
	int		curid;		/* copy of curid		*/

	int		excp_type;	/* exception type for debugger	*/
	uint_t		iar;		/* instruction address register	*/
	uint_t		msr;		/* machine state register	*/
	uint_t		cr;		/* condition register		*/
	uint_t		lr;		/* link register		*/
	uint_t		ctr;		/* count register		*/
	uint_t		xer;		/* fixed point exception	*/
	uint_t		mq;		/* multiply/quotient register	*/
 	uint_t		tid;		/* tid register			*/
	uint_t		fpscr;		/* floating point status reg	*/
	char		fpeu;		/* floating point ever used	*/
	char            fpinfo;         /* floating point status flags  */
	uchar_t		fpscr24_31;	/* bits 24-31 of 64-bit FPSCR   */
	char            pad[1];         /* res - pad to dword boundary  */
	uint_t		except[5];	/* exception structure          */
	char            pad1[4];        /* old bus field                */
	uint_t	     	o_iar;          /* old iar (for longjmp excpt)  */
	uint_t	     	o_toc;          /* old toc (for longjmp excpt)  */
	uint_t	     	o_arg1;         /* old arg1 (for longjmp excpt) */
	uint_t		excbranch;	/* if not NULL, address to branch
					 * to on exception.  Used by
					 * assembler routines for low
					 * cost exception handling*/
	uint_t	     	fpscrx;         /* software extension to fpscr  */
	uint_t     	o_vaddr;        /* Saved vaddr for vmexception  */
	uint_t		cachealign[7];	/* reserved			*/
	adspace32_t	as;		/* segment registers            */
	uint_t		gpr[_NGPRS];	/* general purpose registers	*/
	double		fpr[_NFPRS];	/* floating point registers	*/
};
#endif

/* 
 * Values for mstsave.fpeu
 */

#define _FP_NEVER_USED	0		/* floating point never used	*/
#define _FP_USED	1		/* floating point used	        */

/*
 * Values/fields of mstsave.fpinfo
 *
 * - programming note: This field is intended to be an array of state bits.
 *                     All code accessing `fpinfo' should use a mask.
 */

/* These define how fpinfo is interpreted for "Classic" Power platforms. */
#define _FP_IMP_INT	0x01            /* run in imprecise mode        */
#define _FP_SYNC_TASK	0x08            /* if set, run task at MSR(FE)=1*/

/* these define how fpinfo is interpreted for PowerPC platforms */
#define _PPC_OFF 	0x0		/* FP trapping OFF */
#define _PPC_IMP 	0x1		/* FP trapping Imprecise mode */
#define _PPC_IMP_REC 	0x8	/* FP trapping Imprecise recoverable mode */
#define _PPC_PRECISE 	0x9		/* FP trapping Precise mode */

/* This bit is used to indicate that a floating point interrupt
   was imprecise */
#define _FP_INT_TYPE	0x02		/* type of fp interrrupt        */

#define _FP_SYNC_IMP_S	8		/* shift between bits in FPINFO & MSR */

/*
 *  interrupt handler mstsave and stack pool
 */
#ifdef __64BIT_KERNEL
#define _FRAMESIZE              13312    /* mstsave stack frame size */
#else
#define _FRAMESIZE               7168    /* mstsave stack frame size */
#endif

#define _FRAME_OVBUF_SIZE	 1024    /* mstsave stack overflow buf size */
#define _FRAME_OVBUF_CHAR	 0x11    /* fill character for overflow buf */
#define _FRAME_OVBUF_ULL	 0x1111111111111111ULL  /* fill ULL for buf */

/* size of V=R pmap stack. 2x to support 1 level deep recursion.
 * Keep these defines in sync with dsis_flih.m4
 */
#ifdef DEBUG
#define _PMAP_STK_SIZE		 (4096*2)
#else
#define _PMAP_STK_SIZE		 (3072*2)
#endif

#define _PMAP_OVBUF_SIZE	 768     /* PMAP stack overflow buf size */
#define _PMAP_OVBUF_CHAR	 0x11    /* fill character for overflow buf */
#define _PMAP_OVBUF_ULL		 0x1111111111111111ULL  /* fill ULL for buf */

/* size of SLB flih save area
 * 12 registers, 1 level of recursion, 1 level for dump
 */
#define _SLB_SAVE_SIZE		 (12*3)	 /* 3 areas of 12 registers */

extern char __pmap_stack[];

#define _NUMBER_OF_FRAMES        11      /* Number of Frames per MST stack */


#define _FRAME_1(__cpu_id) 	((_NUMBER_OF_FRAMES*(__cpu_id+1)) - 1)


#ifdef _ALL_SOURCE
#define FP_NEVER_USED		_FP_NEVER_USED
#define FP_USED			_FP_USED
#define FP_IMP_INT		_FP_IMP_INT
#define FP_SYNC_TASK		_FP_SYNC_TASK
#define PPC_OFF			_PPC_OFF
#define PPC_IMP			_PPC_IMP
#define PPC_IMP_REC		_PPC_IMP_REC
#define PPC_PRECISE		_PPC_PRECISE
#define FP_INT_TYPE		_FP_INT_TYPE
#define FP_SYNC_IMP_S		_FP_SYNC_IMP_S
#define FRAMESIZE		_FRAMESIZE
#define FRAME_OVBUF_SIZE	_FRAME_OVBUF_SIZE
#define FRAME_OVBUF_CHAR	_FRAME_OVBUF_CHAR
#define FRAME_OVBUF_ULL		_FRAME_OVBUF_ULL
#define NUMBER_OF_FRAMES	_NUMBER_OF_FRAMES
#define FRAME_1			_FRAME_1
#define PMAP_STK_SIZE		_PMAP_STK_SIZE
#define PMAP_OVBUF_SIZE		_PMAP_OVBUF_SIZE
#define PMAP_OVBUF_CHAR		_PMAP_OVBUF_CHAR
#define PMAP_OVBUF_ULL		_PMAP_OVBUF_ULL
#define SLB_SAVE_SIZE		_SLB_SAVE_SIZE
#define pmap_stack		__pmap_stack
#endif /* _ALL_SOURCE */

#ifdef _KERNEL
#ifdef __64BIT_KERNEL

#define _NTSEGS 4			/* number of temporary segments */

/*
 * Do not change this structure without carefully examinig cache alignment
 */
struct kmstsave	{
	struct kmstsave	*prev;		/* previous save area		*/
	void		*stackfix;	/* stack fix pointer		*/
	label_t		*kjmpbuf;	/* pointer to saved context	*/
	ulong_t		excbranch;	/* if not NULL, address to branch */

	/*
	 * intpri and backt are accessed as one short in places
	 */
	char		intpri; 	/* interrupt priority		*/
	char		backt;		/* back-track flag		*/
	ushort_t	flags;		/* misc. flags - defines below	*/
	uint_t		mq;		/* Power Emulation only		*/

	ulong_t		msr;		/* machine state register	*/
	ulong_t		iar;		/* instruction address register	*/
	ulong_t		lr;		/* link register		*/
	ulong_t		ctr;		/* count register		*/
	uint_t		cr;		/* condition register		*/
	uint_t		xer;		/* fixed point exception	*/

	uchar		kfpscr0_7;	/* upper 32-bits of 64-bit fpscr*/
	uchar		kfpscr8_15;
	uchar		kfpscr16_23;
	uchar		kfpscr24_31;
	uint_t		fpscr;		/* floating point status reg	*/
	uint_t		fpscrx;		/* software extension to fpscr  */
	/*
	 * fpowner and fpeu are accessed as on "short" in places
	 */
	char		fpowner;	/* floating point state in regs */
	char		fpeu;		/* floating point ever used	*/
	char            fpinfo;         /* floating point status flags  */
	char		intnesting;	/* interrupt-nesting depth.	*/
	/*
	 * alloc is accessed as a word or even a doubleword in places
	 */
	ushort_t	alloc;		/* temporary segment allocation */
	char		alloc_pad[6];	/* do not use this storage */
	char		no_pfault;	/* 1 => page faults not allowed	*/
	char		vmxstate;	/* 0 => VMX never used */ 
					/* 1 => VMX used but not active */
					/* 2 => VMX in use (owner) */
	/*
	 * We count the number of disabled ticks here.
	 * Because big ticks and slow ticks can degrade the accuracy
	 * of what we're doing, we also count the number of actual
	 * decrementer interrupts involved.  This lets us require
	 * not only that int_ticks exceed a threshold, but also that
	 * a minimum number of physical interrupts were taken.
	 *
	 * Because we don't want to change the size of the mst in the
	 * 32 bit kernel version below, we subdivide this field.
	 * The top two bits of int_ticks will be used as the event count,
	 * while the low-order 6 bits will be the timer.
	 */
	char		int_ticks;	/* count consecutive ticks	*/

	char		pad2[5];
	ulong_t		sr[_NTSEGS];

	ulong_t         except[5];	/* exception structure          */
	ulong_t         o_vaddr;        /* Saved vaddr for vmexception  */
	ulong_t         o_iar;          /* old iar (for longjmp excpt)  */
	ulong_t         o_toc;          /* old toc (for longjmp excpt)  */
	ulong_t         o_arg1;         /* old arg1 (for longjmp excpt) */
	void            *kmst_krlockp;  /* pointer to spinning krlock.  */
	uint_t		kvrsave;	/* VMX VRsave register          */
	int		excp_type;	/* exception type               */

	/*
	 * For 64 bit kernel, reuse nft fields to store processor
	 * identification info when not doing fault injection. When doing
	 * fault injection we don't care about processor identification.
	 */

        union _KMSTSAVE_KMSTU1 {
            struct _KMSTSAVE_ST1 {
                uint_t      knft_cycles;  /* Cycles to crash for NFT errinj.  */
                uint_t      knft_instrs;  /* Instr. to crash for NFT errinj.  */
            } st1;
            struct _KMSTSAVE_ST2 {
                uint_t      khw_fru_id;   /* Part 1 of processor ID info      */
                uint_t      khw_cpu_id;   /* Part 2 of processor ID info      */
            } st2;
        } kmstu1;

#define nft_cycles      kmstu1.st1.knft_cycles
#define nft_instrs      kmstu1.st1.knft_instrs
#define ksave_hw_fru_id kmstu1.st2.khw_fru_id
#define ksave_hw_cpu_id kmstu1.st2.khw_cpu_id

	ulong_t		amr;		/* AMR (only in 64-bit kernel)	*/
	long long       save_cfar;      /* P6 and up: CFAR save area    */

	/*
	 * There will be functional problems if this is not cache aligned
	 */
	ulong_t		gpr[_NGPRS];	/* general purpose registers	*/
};

#define ksave_cfar      save_cfar

#else	/* !__64BIT_KERNEL */
#define	NUM_KERNEL_BATS	3		/* number of BATS used in kernel mode */
struct kmstsave	{

	struct kmstsave	*prev;		/* previous save area		*/
	label_t		*kjmpbuf;	/* pointer to saved context	*/
	char		*stackfix;	/* stack fix pointer		*/
	char		intpri; 	/* interrupt priority		*/
	char		backt;		/* back-track flag		*/
	uchar		flags;		/* misc. flags - defines below	*/
	/*
	 * We count the number of disabled ticks here.
	 * Because big ticks and slow ticks can degrade the accuracy
	 * of what we're doing, we also count the number of actual
	 * decrementer interrupts involved.  This lets us require
	 * not only that int_ticks exceed a threshold, but also that
	 * a minimum number of physical interrupts were taken.
	 *
	 * Because we don't want to change the size of the mst here,
	 * the top two bits of int_ticks will be used as the event count,
	 * while the low-order 6 bits will be the timer.
	 */
	char		int_ticks;	/* count consecutive ticks	*/

	pid_t		curid;		/* copy of curid		*/

	int		excp_type;	/* exception type for debugger	*/
	ulong_t		iar;		/* instruction address register	*/
	ulong_t		msr;		/* machine state register	*/
	ulong_t		cr;		/* condition register		*/
	ulong_t		lr;		/* link register		*/
	ulong_t		ctr;		/* count register		*/
	ulong_t		xer;		/* fixed point exception	*/
	ulong_t		mq;		/* multiply/quotient register	*/
        ulong_t         tid;            /* tid register                 */
/*
 *  TID register is no longer supported on PPC.
 *  Reuse field for part of the processor identification info
 */
#define khw_fru_id	tid     /* Part1 of processor ID info   */

	/* floating point related information now in uthread struct */
	ulong_t		fpscr;		/* floating point status reg	*/
	char		fpeu;		/* floating point ever used	*/
	char            fpinfo;     	/* floating point status flags  */
	char            no_pfault;	/* 1 => page faults not allowed	*/
	char		vmxstate;	/* 0 => VMX never used */ 
					/* 1 => VMX used but not active */
					/* 2 => VMX in use (owner) */
	ulong_t         except[5];	/* exception structure          */
	ulong           mstext;         /* offset to mstsave64 or NULL */

	ulong_t         o_iar;          /* old iar (for longjmp excpt)  */
	ulong_t         o_toc;          /* old toc (for longjmp excpt)  */
	ulong_t         o_arg1;         /* old arg1 (for longjmp excpt) */

	ulong_t		excbranch;	/* if not NULL, address to branch
					 * to on exception.  Used by
					 * assembler routines for low
					 * cost exception handling*/
	ulong_t         fpscrx;		/* software extension to fpscr  */
	ulong_t         o_vaddr;        /* Saved vaddr for vmexception  */
	ulong_t		ioalloc;	/* ioallocation mask */
	union _KMSTSAVE_KMSTU {
	    struct {
		ulong_t batu;
		ulong_t batl;
	    } dbats[NUM_KERNEL_BATS];	/* Save area for bats		*/
	    struct _KMSTSAVE_S1 {	/* BATS and VMX/DFP dont coexist*/
					/* on any processor             */
		uint_t	vrsave;		/* VMX VRsave register          */
		uchar	fpscr24_31;	/* bits 24-31 of 64-bit FPSCR   */
		char	hw_cpu_id[3];	/* bits 8-31 of HW cpu ident.   */

/*
 * For part 2 of processor identification on 32 bit kernel, we have
 * a problem: the processor ID on the FRU (MCM, for instance) is a
 * 4 byte value and there is only 3 bytes of padding left in the MST.
 * We'll assume that for the foreseeable future the ID is going to fit
 * on 3 bytes and that's all we'll save anyway.
 * Worst that can happen is an incomplete ID. Still better than nothing.
 */
#define khw_cpu_id      kmstu.s1.fpscr24_31
#define HW_CPU_ID_32_MASK	0x00ffffff	/* Masks off fpscr24_31 */

                int     sig_cfar_hi;    /* saved by signal processing   */
                int     save_cfar_hi;   /* P6 and up: CFAR save area    */
                                        /* must be 8 byte aligned       */
                                        /* because assembler uses a std */
                int     save_cfar_lo;
                int     sig_cfar_lo;    /* saved by signal processing   */
	    } s1;
	} kmstu;			
#define kvrsave		kmstu.s1.vrsave
#define kfpscr24_31	kmstu.s1.fpscr24_31
#define ksave_cfar      kmstu.s1.save_cfar_hi
#define ksave_cfar_hi   kmstu.s1.save_cfar_hi
#define ksave_cfar_lo   kmstu.s1.save_cfar_lo
#define ksig_cfar_hi    kmstu.s1.sig_cfar_hi
#define ksig_cfar_lo    kmstu.s1.sig_cfar_lo
#define kdbats		kmstu.dbats
#define ksave_hw_fru_id khw_fru_id
#define ksave_hw_cpu_id khw_cpu_id



	adspace_t	as;		/* segment registers            */
	ulong_t		gpr[_NGPRS];	/* general purpose registers	*/
};


#endif /* __64BIT_KERNEL */

extern struct kmstsave lastbackt[];
/* Values for kmstsave.flags field */
#define KMST_FLAGS_DEV_KMEM	(unsigned char)0x80
#define KMST_FLAGS_64BIT	0x40
#ifdef __64BIT_KERNEL
#define KMST_FLAGS_KJMPBUF_SPCL 0x20
#else
#define KMST_FLAGS_RESUME_64	0x20
#endif /* __64BIT_KERNEL */
#define KMST_FLAGS_DPS		0x10
#ifdef __64BIT_KERNEL
#define KMST_FLAGS_NOPREEMPT	0x08
#endif /* __64BIT_KERNEL */
#define KMST_FLAGS_THRPGIO_PROT 0x04
#define KMST_FLAGS_SPARSE_SEG   0x02
#define KMST_FLAGS_XMGETFL	0x01

extern struct mststack  { 
	char stack[FRAMESIZE-sizeof(struct kmstsave)];
	struct kmstsave save;
} mststack[];

/* extension to mstsave for 64-bit processes
 * this structure and context64 and ptxsprs are related. context64
 * begins with mstsave64 but overlays the asr field with (fpscr, fpscrx).
 * ptxsprs consists of the fields msr thru fpscrx. 
 */
struct mstsave64 {
	unsigned long long	gpr[_NGPRS];	/* 64-bit gprs */	
	unsigned long long	msr;		/* msr */
	unsigned long long	iar;		/* iar */
	unsigned long long	lr;		/* LR */
	unsigned long long	ctr;		/* CTR */
	ulong		cr;			/* CR */
	ulong		xer;			/* XER */
	unsigned long long	asr;		/* address space register value */
	unsigned long long	except;		/* exception address */
};

/* offsets of various fields in struct mstsave64 */
#define OFF_GPR    ((uint) &((struct mstsave64 *)0)->gpr[0]) 
#define OFF_MSR    ((uint) &((struct mstsave64 *)0)->msr) 
#define OFF_IAR    ((uint) &((struct mstsave64 *)0)->iar) 
#define OFF_LR     ((uint) &((struct mstsave64 *)0)->lr) 
#define OFF_CTR    ((uint) &((struct mstsave64 *)0)->ctr) 
#define OFF_CR     ((uint) &((struct mstsave64 *)0)->cr) 
#define OFF_XER    ((uint) &((struct mstsave64 *)0)->xer) 

#endif /* _KERNEL */
	

#endif /*_H_MSTSAVE*/
