/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/POWER/m_except.h 1.10.4.1                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)88     1.10.4.1  src/bos/kernel/sys/POWER/m_except.h, sysproc, bos53Q, q2008_02A6 11/12/07 12:23:05 */
#ifndef _H_M_EXCEPT
#define _H_M_EXCEPT
 
/*
 * COMPONENT_NAME: SYSPROC 
 *
 * ORIGINS: 27 
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1993
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *		Exception Codes and Structures -- R2 platform
 *    This file defines values for machine dependent exceptions and the machine
 *    dependent structure
 * 
 *    NOTE:  A parallel assembler version of this .h file is in
 *           ../../sys/ml/m_except.m4
 */

/*
 *    Code 0 IS NOT VALID as an exception code
 *    Codes 1-127 are errno return values
 *    Codes 128-255 are reserved for non-machine specific exceptions
 *    Codes 256-511 are reserved for machine-specific exceptions
 *    Codes above 512 can be freely used for any purpose
 */

#define EXCEPT_ERRNO        127		/* The highest value for errno */
#define EXCEPT_FLOAT        128		/* Floating Point Exception */
#define EXCEPT_INV_OP       129		/* Invalid Op-code */
#define EXCEPT_PRIV_OP      130		/* Privileged op in user mode */
#define EXCEPT_TRAP         131		/* Trap Instruction */
#define EXCEPT_ALIGN        132		/* Alignment */
#define EXCEPT_INV_ADDR     133		/* Invalid Address */
#define EXCEPT_PROT         134		/* Protection */
#define EXCEPT_IO           135		/* Synchronous I/O */
#define EXCEPT_IO_IOCC	    135
#define EXCEPT_IO_SGA	    136		/* I/O exception from SGA */
#define EXCEPT_IO_SLA	    137		/* I/O exception from SLA  */
#define EXCEPT_IO_SCU	    138		/* I/O exception from SCU  */
#define EXCEPT_EOF	    139		/* Ref beyond end-of-file (mmap) */
#define EXCEPT_FLOAT_IMPRECISE 140	/* Imprecise floating point exception */
#define EXCEPT_ESTALE_I     141		/* stale text segment exception */
#define EXCEPT_ESTALE_D     142		/* stale data segment exception */

/*
 * EXCEPT_PFAULT is not a real (hardware) exception.  It is detected when
 * a page fault occurs at a time when the software can not tolerate the
 * possible loss of control.  This situation is indicated by setting the
 * no_pfault flag in the mst (only INTMAX code would do this).
 * This causes an exception return directly via excbranch before the page
 * fault handler enables.
 *
 * EXCEPT_THRPGIO is also not a hardware exception. It is detected when
 * a page fault occurs for a D_THRPGIO paging device and the no_pfault
 * flag in the mst is set to NO_PFAULT_THRPGIO. This occurs when a user
 * process has set state in the kernel which is incompatible with the
 * THRPGIO environment.
 */
#define EXCEPT_PFAULT		255	/* page fault not allowed */

#define EXCEPT_MACHINE		256	/* Machine dependent exceptions */
#define EXCEPT_IFETCH_IO	256	/* I-fetch from the I/O segment */
#define EXCEPT_IFETCH_SPEC	257	/* I-fetch from special segment */
#define EXCEPT_DRST		261	/* Direct store to W or I storage */
#define EXCEPT_DSI		262	/* Data storage interrupt */
#define EXCEPT_ISI		263	/* Instuction storage interrupt */

#define EXCEPT_GRAPHICS_SID	264	/* special graphics sid exception */
#define EXCEPT_INVAL_EAR	265	/* invalid ear exception */
#define EXCEPT_PT_WATCHP	266	/* hit ptrace watchpoint */
#define EXCEPT_SYSDUMP		267	/* Took system dump */
#define EXCEPT_NOEXEC		268	/* No-execute exception */
#define EXCEPT_RMA		269	/* OS made an out-of-rma reference */
#define EXCEPT_SKEY             270     /* Storage Key exception */

#define EXCEPT_THRPGIO		278	/* page fault in thrpgio-backed seg */

/*
 *		PIO Exception Structure  -- R2 platform
 */


struct pio_except 
{
	ulong pio_csr;			/* channel Status register (IOCC) */
					/* or modified DSIER */
	ulong pio_dsisr;		/* data storage interrupt status reg */
	ulong pio_srval;		/* I/O Segment register value */
	ulong pio_dar;			/* effective address used in I/O access
					 */
	ulong pio_dsirr;		/* data storage int reason register */
};
/* except struct for the getexcept() kernel service */
struct except
{
	ulong except[5];
};

/* Definitions for the channel status register provided in the pio_csr field
of the pio_except structure */

#define	PIO_EXCP_MASK	0xF0000000	/* pio exception status mask */
#define PIO_EXCP_NONE	0x00000000	/* no PIO exception  */
#define PIO_EXCP_INV_OP 0x10000000	/* invalid i/o operation */
#define PIO_EXCP_LIMIT	0x30000000	/* Bus I/O Access Authority Error */
#define PIO_EXCP_PROT	0x50000000	/* Bus Memory Access Authority Error */
#define PIO_EXCP_PFAULT 0x60000000	/* Bus Memory Page Fault */
#define PIO_EXCP_CHNCHK 0x80000000	/* I/O Adapter Channel Check */
#define PIO_EXCP_DPRTY	0x90000000	/* Data Parity Error */
#define PIO_EXCP_NORSP	0xB0000000	/* No Response from I/O Adapter */
#define PIO_EXCP_STECC	0xC0000000	/* System Storage Access through I/O
					   space resulted in storage ECC error
					 */
#define PIO_EXCP_STADR  0xD0000000	/* System Storage Access through I/O
					   space resulted in address error */
#define PIO_EXCP_TPRTY	0xE0000000	/* TCW parity error occurred when
					    accessing System Storage through
					     I/O space or when checking access
					    key for user mode I/O access */
#define PIO_EXCP_IOCC	0xF0000000	/* Internal IOCC error occurred */

/* The pio_dsisr field indicates whether the I/O exception was due to a load
or store operation by testing for the DSISR_ST flag set indicating that a 
storage operation was attempted. */

/* The bus unit id used in the I/O access generating an exception may be
obtained from the BUID field in the pio_srval parameter */

/* The effective address used for the I/O access that resulted in the exception
is provided in the pio_dar field */

#endif /*_H_M_EXCEPT*/
