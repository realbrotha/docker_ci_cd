/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/POWER/low.h 1.17                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)71       1.17  src/bos/kernel/sys/POWER/low.h, sysproc, bos530 10/14/98 18:30:29 */
#ifndef _H_LOW
#define _H_LOW
/*
 * COMPONENT_NAME: SYSPROC 
 *
 * ORIGINS: 27, 83
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1993
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 *   LEVEL 1,  5 Years Bull Confidential Information
 */

#ifdef _KERNSYS
#include <sys/ppda.h>	/* csa, curthread macros */
#endif

/*
 * Kernel global low memory variables.
 */

/* number of machine dependent ranges to free.  For now this is one --
 * Power or Power PC
 */
#define NUM_RANGES 1

struct mach_range{
	int num_ranges;			/* number of ranges to free */
	struct {
		caddr_t machdep_start;	/* starting address of text to free */
		caddr_t machdep_end;	/* address of last byte to free */
	}range[NUM_RANGES];
};
extern struct mach_range free_range;

/* these variables give the range of code for vmsi() to pin.  This is
 * the architecture dependent object code
 */
extern caddr_t machpin_start;		/* starting address of text to pin */
extern caddr_t machpin_end;		/* address of last byte to pin */

extern caddr_t machcom_start;		/* first byte of common to pin */
extern caddr_t machcom_end;		/* last byte of common to pin */

/*
 * These symbols are defined in sys/ml/fcp.m4.
 */

extern char g_sysid[32];			/* system time stamp	*/
extern char g_copyr[224];			/* copyright		*/
extern pid_t curid;				/* current proc. id	*/
#ifndef __64BIT_KERNEL
extern caddr_t g_toc;				/* Kernel TOC @		*/
#endif

extern struct trtScon {				/* Trace pointers.	*/
			caddr_t trace_start;
			caddr_t trace_end;
			caddr_t trace_current;
		} trtScon;

#endif /* _H_LOW */
