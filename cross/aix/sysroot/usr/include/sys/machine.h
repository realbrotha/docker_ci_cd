/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/POWER/machine.h 1.48.1.2                     */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1987,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)96  1.48.1.2  src/bos/kernel/sys/POWER/machine.h, sysml, bos53L, l2007_23B0 5/30/07 16:36:25 */
#ifndef _H_MACHINE
#define _H_MACHINE

/*
 * COMPONENT_NAME: (SYSML) Kernel Assembler
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27, 3
 *
 * (C) COPYRIGHT International Business Machines Corp. 1987, 1994
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 *	     This include file defines mask bits and other special values
 *           for machine-dependent control registers, and other values
 *           specific to the platform.
 *
 *           This version is for R2.
 *
 *           NOTE:  A parallel assembler version of this .h file is in
 *                  .../sys/ml/machine.m4.
 *
 */

/*
 * Definitions for byte order,
 * according to byte significance from low address to high.
 */
#define	LITTLE_ENDIAN	1234	/* least-significant byte first (vax)	      */
#define	BIG_ENDIAN	4321	/* most-significant byte first (IBM, net)     */
#define	PDP_ENDIAN	3412	/* LSB first in word, MSW first in long (pdp) */

#define	BYTE_ORDER	BIG_ENDIAN

/*
 * Default value to place into a register when it isn't supposed
 *    to contain a useful value (killed registers on return from
 *    system call, for example)
 */

#define      DEFAULT_GPR   0xDEADBEEF

/*
 * Machine Status Register (MSR)
 */

#define      MSR_VMX	   0x2000000/* VMX enable			     */
#define      MSR_EE	   0x8000   /* External interrupt enable             */
#define      MSR_PR	   0x4000   /* Problem state                         */
#define      MSR_FP	   0x2000   /* Floating point available              */
#define      MSR_ME	   0x1000   /* Machine check enable                  */
#define      MSR_FE	   0x0800   /* Floating point exception enable (PWR) */
#define      MSR_FE0	   0x0800   /* Floating point xcp mode bit0    (PPC) */
#define      MSR_SE        0x0400   /* Single Step Trace Enable    (RS2/PPC) */
#define      MSR_BE        0x0200   /* Branch Trace Enable         (RS2/PPC) */
#define      MSR_IE        0x0100   /* Flt-pt imprecise int enable     (RS2) */
#define      MSR_FE1       0x0100   /* Floating point xcp mode bit1    (PPC) */
#define      MSR_AL	   0x0080   /* Alignment check enable          (PWR) */
#define      MSR_IP	   0x0040   /* Interrupt prefix active               */
#define      MSR_IR	   0x0020   /* Instruction relocate on               */
#define      MSR_DR	   0x0010   /* Data relocate on                      */
#define      MSR_PM        0x0004   /* Performance Monitoring          (RS2) */
#define	     MSR_RI	   0x0002   /* Recoverable interrupt           (PPC) */
#define	     MSR_HYPERVISOR	0x1000000000000000LL  /* Hypervisor Modr (GP) */

#ifdef __64BIT_KERNEL
#define      MSR_SF	   0x8000000000000000L   
#define	     MSR_ISF	   0x2000000000000000L

#define	     DEFAULT_MSR   (MSR_SF|MSR_ISF|MSR_EE|MSR_ME|MSR_IR|MSR_DR|MSR_RI)
#define	     DEFAULT_USER_MSR  \
			(MSR_ISF|MSR_PR|MSR_EE|MSR_ME|MSR_IR|MSR_DR|MSR_RI)
#define      MSR_SF_H      0xA0000000   /* Upper half of msr for 64-bit PPC */
#else
#define      DEFAULT_MSR          (MSR_EE|MSR_ME|MSR_AL|MSR_IR|MSR_DR|MSR_RI)
#define      DEFAULT_USER_MSR     (DEFAULT_MSR | MSR_PR)
#define      MSR_SF_H      0x80000000   /* Upper half of msr for 64-bit PPC */
#endif




/*
 * Condition Register (CR)
 */

#define      CR_LT	   0x80000000   /* Less Than,        field 0         */
#define      CR_GT	   0x40000000   /* Greater Than,     field 0         */
#define      CR_EQ	   0x20000000   /* Equal,            field 0         */
#define      CR_SO	   0x10000000   /* Summary Overflow, field 0         */
#define      CR_FX	   0x08000000   /* Floating point exception          */
#define      CR_FEX	   0x04000000   /* Floating point enabled exception  */
#define      CR_VX	   0x02000000   /* Floating point invalid operation  */
#define      CR_OX	   0x01000000   /* Copy of FPSCR(OX)                 */

/* Macro to access field n of CR value cr:                                   */

#define      CR_FIELD(n,cr)   ((cr << (n << 2)) & 0xF0000000)


/*
 * Fixed Point Exception Register (XER)
 */

#define      XER_SO	   0x80000000   /* Summary overflow                  */
#define      XER_OV	   0x40000000   /* Overflow                          */
#define      XER_CA	   0x20000000   /* Carry                             */

/* Macros to access comparison byte and length for lsx, lscbx, stsx          */

#define      XER_COMP_BYTE(xer)  ((xer >> 8) & 0x000000FF)
#define      XER_LENGTH(xer)     (xer & 0x0000007F)


/*
 * Data Storage Interrupt Status Register (DSISR)
 */

#define      DSISR_IO      0x80000000   /* I/O exception                     */
#define      DSISR_PFT     0x40000000   /* No valid PFT for page             */
#define      DSISR_LOCK    0x20000000   /* Access denied: data locking (PWR) */
#define      DSISR_FPIO    0x10000000   /* FP load/store to I/O space  (PWR) */
#define      DSISR_PROT    0x08000000   /* Protection exception              */
#define      DSISR_LOOP    0x04000000   /* PFT search > 127 entries    (RS1) */
#define      DSISR_DRST    0x04000000   /* lwarx, etc to Direct Store  (PPC) */
#define      DSISR_ST      0x02000000   /* 1 => store, 0 => load             */
#define      DSISR_SEGB    0x01000000   /* Crosses segment boundary,   (PWR) */
                                        /*   from T=0 to T=1                 */
#define      DSISR_DAC     0x00400000   /* Data Address Cmp/ACCR (PPC < P5++)*/
#define      DSISR_DABR    0x00400000   /* DABR exception          (RS2/PPC) */
#define      DSISR_STAB    0x00200000   /* stab fault	         (PPC < P5++)*/
#define      DSISR_SKEY    0x00200000   /* Storage Key Violation       (P5++)*/
#define      DSISR_EAR     0x00100000   /* eciwx with EAR enable = 0   (PPC) */

/*
 * System Recall Register 1 (SRR1)
 *
 * Note:  This register is used for various purposes, depending on the
 *        type of interrupt, thus the prefix of the name will vary.
 */

#define      SRR_IS_PFT    0x40000000   /* No valid PFT for page             */
#define      SRR_IS_ISPEC  0x20000000   /* I-fetch from special segmnt (PWR) */
#define      SRR_IS_IIO    0x10000000   /* I-fetch from I/O space            */
#define      SRR_IS_GUARD  0x10000000   /* I-fetch from guarded storage      */
#define      SRR_IS_PROT   0x08000000   /* Protection exception              */
#define      SRR_IS_LOOP   0x04000000   /* PFT search > 127 entries    (RS1) */

#define      SRR_PR_FPEN   0x00100000   /* FP Enabled Interrupt exception    */
#define      SRR_PR_INVAL  0x00080000   /* Invalid operation                 */
#define      SRR_PR_PRIV   0x00040000   /* Privileged instruction            */
#define      SRR_PR_TRAP   0x00020000   /* Trap instruction                  */
#define      SRR_PR_IMPRE  0x00010000   /* Imprecise Interrupt         (PPC) */

/*
 * VMX Status and Control Register
 */
#define	     VSCR_SAT	   0x00000001	/* VMX Saturation sticky bit         */
#define	     VSCR_NJ	   0x00010000	/* VMX Non-Java Mode	             */

/**************************************************************
 *
 * Data Streams Control Register (DSCR) - Power6 and later CPUs
 * ============================================================
 *
 * +----------------------------------------------------------+---+----+
 * |                         ///                              |SSE|DPFD|
 * +----------------------------------------------------------+---+----+
 * (0                                                      59  60    63)
 *
 * _Bit(s) Name    Description_
 *
 *    60   SSE     Store Stream Enable
 *                 Enables hardware detection and initiation of store
 *                 streams.
 *
 *  61:63  DPFD    Default Prefetch Depth
 *                 Depth value applied for hardware-detected streams
 *                 and software-defined streams for which a dcbt with
 *                 TH=1010 is _not_ used in their description.  Values
 *                 and their meanings are as follows.
 */

#define	 DPFD_DEFAULT             0
#define	 DPFD_NONE                1
#define	 DPFD_SHALLOWEST          2
#define	 DPFD_SHALLOW             3
#define	 DPFD_MEDIUM              4
#define	 DPFD_DEEP                5
#define	 DPFD_DEEPER              6
#define	 DPFD_DEEPEST             7

#define	 DSCR_SSE                 8

#define  DSCR_MASK		0xF	/* Only for bits valid in DSCR */

/*
 * Structures used to query the Data Streams Properties
 */

struct dscr_properties {
#define DSCR_PROP_VER0	0x44530000		/* 'D''S'00 */
#define DSCR_PROP_VER	DSCR_PROP_VER0	
	unsigned int	 version;
	unsigned int  number_of_streams;	/* Number of HW streams */
	long long	platform_default_pd;	/* Platform default */
	long long	os_default_pd;		/* Operating System default */
	long long dscr_res[5];			/* Reserved for future use */
};

#define DSCR_PROP_VER0_SIZE	(offsetof(struct dscr_properties, dscr_res))
#define DSCR_PROP_SIZE		(sizeof(struct dscr_properties))

/*
 * Function to read/write the Data Streams Control Register
 */
int dscr_ctl(int op, void *buf_p, int size);

/*
 * The op parameter is one of the values below:
 */

#define	DSCR_WRITE	    1  /* Stores new value from input buffer into    *
                                * process context and in the DSCR.           */
#define	DSCR_READ	    2  /* Reads current value of DSCR and returns it *
                                * in output buffer.                          */
#define	DSCR_GET_PROPERTIES 3  /* Reads number of HW streams,		     *
			        * Firmware default Prefetch Depth	     *
			        * and OS default Prefetch Depth from kernel  *
                                * memory and returns it in output buffer     */
#define DSCR_SET_DEFAULT    4  /* Set Operating System default for DSCR      */


/************************************************************/

#ifdef _KERNEL
/*
 * MACROS to determine the type of RS/6000 machine
 */
extern int mach_model;

#define MACH_RS1() (!(mach_model & 0x06000000))
#define	MACH_RSC() (mach_model & 0x02000000)

extern int fp_ie_impl;                  /* nonzero if ie implemented         */
#define FP_IE_IMPL (fp_ie_impl != 0)

#endif /* _KERNEL */

#ifdef _KERNSYS

#ifdef _POWER_PC

#ifdef _POWER_601

/*
 * The following macro can be used to generate a BUID 7f segment
 * register value given a real address
 */
#define BUID_7F_SRVAL(raddr) (0x87F00000 | (((uint)(raddr)) >> 28))

#endif /* _POWER_601 */

/*
 *	DBATU  Data BAT Upper
 *   +---------------------------------------------------------------+
 *   |     Effective  Address      | rsvd  |      Block Size     |V|V|
 *   |          BEPI               |       |          BL         |S|P|
 *   | | | | | | | | | | |1|1|1|1|1|1|1|1|1|1|2|2|2|2|2|2|2|2|2|2|3|3|
 *   |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|
 *   +---------------------------------------------------------------+
 *
 *	DBATL  Data BAT Lower
 *   +---------------------------------------------------------------+
 *   |        Real Address         | rsvd              |W I M G| |P P|
 *   |          BRPN               |                   |       | |   |
 *   | | | | | | | | | | |1|1|1|1|1|1|1|1|1|1|2|2|2|2|2|2|2|2|2|2|3|3|
 *   |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|
 *   +---------------------------------------------------------------+
 */

/*
 * The following defines are all valid values for the data BAT
 * BL field
 */
#define BT_256M		0x1FFC		/* 256 Meg block */
#define BT_128M		0x0FFC		/* 128 Meg block */
#define BT_64M		0x07FC		/* 64 Meg block */
#define BT_32M		0x03FC		/* 32 Meg block */
#define BT_16M		0x01FC		/* 16 Meg block */
#define BT_8M		0x00FC		/* 8 Meg block */
#define BT_4M		0x007C		/* 4 Meg block */
#define BT_2M		0x003C		/* 2 Meg block */
#define BT_1M		0x001C		/* 1 Meg block */
#define BT_512K		0x000C		/* 512 K block */
#define BT_256K		0x0004		/* 256 K block */
#define BT_128K		0x0000		/* 128 K block */

/*
 * The following defines are for data BAT PP (access protection)
 */
#define BT_NOACCESS	0x0		/* BAT no access */
#define BT_RDONLY	0x1		/* read only access */
#define BT_WRITE	0x2		/* read write access */

/*
 * The following defines are for the data BAT Vs Vp fields
 */
#define BT_VS		0x2		/* BAT valid in kernel mode */
#define BT_VP		0x1		/* BAT valid in user mode */

/*
 * The following values can be used to generate data BAT values
 *	raddr - real address
 *	size - BL field (use BT_XXX defines above)
 *	val - BAT (use BT_XXX defines above)
 *	eaddr - effective address to map
 *	wimg - storage attributes
 * 	pp - access protection (use BT_XXX defines above)
 */
#define DBATU(eaddr, size, val)	(((eaddr) & 0xFFFE0000) | (size) | (val))
#define DBATL(raddr, wimg, pp)	(((raddr) & 0xFFFE0000) | ((wimg) << 3) | (pp))

/*
 * The DBATU_D and DBATL_D macros are for access of 64bit I/O
 */
#define DBATU_D(eaddr, size, val)     				\
	((unsigned long long)((unsigned long long)(eaddr) & 	\
	(unsigned long long)0xFFFFFFFFFFFE0000ULL) | 		\
	(unsigned long long)(size) | (unsigned long long)(val))


#define DBATL_D(raddr, wimg, pp)  			\
	((unsigned long long)((((raddr) & 		\
	((unsigned long long)0xFFFFFFFFFFFE0000ULL))) | \
		((unsigned long long)(wimg) << 3) | 	\
		((unsigned long long)(pp))))

/*
 * This macro can returns the segment number that a data BAT maps
 */
#define BAT_ESEG(dbatu) (((uint)(dbatu) >> 28))

#define MIN_BAT_SIZE	0x00020000	/* Minimium BAT size (128K) */
#define MAX_BAT_SIZE	0x10000000	/* Maximium BAT size (256M) */

/*
 *				ASR (Low 32-bits)
 *   +---------------------------------------------------------------+
 *   |                                                              V|
 *   |                                       |                     | |
 *   | | | | | | | | | | |1|1|1|1|1|1|1|1|1|1|2|2|2|2|2|2|2|2|2|2|3|3|
 *   |0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|2|3|4|5|6|7|8|9|0|1|
 *   +---------------------------------------------------------------+
 *
 * Power PC ASR SPR is used to anchor a segment table.  It contains the
 * segment table's real address.  A valid bit enables the segment table
 * lookup to proceed.
 */

#define ASR_VALID	(1LL)

#define	SLB_SIZE_MIN		32	/* min architected slb size */
#define	SLB_SIZE_MAX		64	/* max slb size (for static arrays) */

#define	SLB_SIZE		SLB_SIZE_MAX

#ifndef __64BIT_KERNEL

#define	USER_SLB_START		16	/* First slb index loaded */
#define SLBR_TESID		1	/* temporary ESID used slb_reload */

#else /* ... __64BIT_KERNEL */

#define	MAX_SLB_INDEX		63	/* Last index */
#define SLB_NUM_MASK		0xcff	/* mask for largest architected SLB */
#define SLB_VALID		0x08000000	/* SLB valid bit */
#define SLB_E_RSVD		0x07fffc00	/* reserved bits in slbmte */
#define	SLB_C			0x80	/* Class bit in SLB vsid */
#define SLB_PSIZE_MASK          0x170UL /* mask for SLB page size bits */
#define SLBE(_esid, _index) ((_esid)|SLB_VALID|(_index))

#define VALID_HANDLE_SSLB(_handle) (!((_handle) & 0x0f))
#define HANDLE_CLASS_SSLB		0x80UL	/* C-bit */

#define SLB_TEMP0_INDEX		0xB
#define SLB_TEMP1_INDEX		0xC
#define SLB_TEMP2_INDEX		0xD
#define SLB_TEMP3_INDEX		0xE

/* slbie format:
 *
 *  [ 0:35 esid | 36 class bit | 37:38 seg size bits | 39:63 unused ]

 *   +-------------------------------------------------------------------+
 *   |
 *   |   esid                             |C|ss|   unused 
 *   |          11111111112222222222333333|3|33|3444444444455555555556666
 *   |012345678901234567890123456789012345|6|78|9012345678901234567890123
 *   +-------------------------------------------------------------------+
 */
#define SLBIE(_eaddr, _C, _ssb)			\
	((_eaddr) | ((_C) << (63-36)) | ((_ssb) << (63-38)))

#endif /* !__64BIT_KERNEL */

/*
 * Primitive functions for kernel debugger to do MMIOs
 */
long long read_mmio(long, unsigned long long);
void write_mmio(long, unsigned long long, unsigned long long);

/*
 * Macro to test DSCR support
 */
extern struct dscr_properties dscr_info;
extern int hw_streams_supported;

#endif /* _POWER_PC */

#endif /* _KERNSYS */

/*
 * In IA64, the alignment of a long long differs between 32 and 64 bit.
 * In 64 bit, the alignment is on an 8 byte boundary but in 32 bit
 * the alignment is on a 4 byte boundary.  This causes some structure
 * that are defined both in user space and on the kernel to misalign.
 * The __INTPAD macro is used to force an alignment to the next 4 byte
 * boundary.
 *
 * Note that this problem does not occur on POWER archtecture so this
 * macro generates nothing in the POWER machine.h.
 */
#define __INTPAD(nm)


#endif /* _H_MACHINE */
