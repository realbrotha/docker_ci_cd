/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/POWER/m_types.h 1.21                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)77       1.21  src/bos/kernel/sys/POWER/m_types.h, sysproc, bos530 1/18/01 12:00:21 */

/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1985,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


#ifndef _H_M_TYPES
#define _H_M_TYPES

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#include <sys/vm_types.h>

/*
 * XPG4.2 requires structure elements to be defined such that they do not 
 * pollute the namespace.  Additional elements to these structures should
 * be added after the "#endif", and always prepended with "__".
 */

typedef struct label_t
{					/* kernel jump buffer */
#ifdef _ALL_SOURCE
	struct label_t   *prev;		/* chain to previous */
	ulong_t           iar;		/* resume address */
	ulong_t           stack;	/* stack pointer */
	ulong_t           toc;		/* toc pointer */
	ulong_t           cr;           /* non-volatile part of cr */
	ulong_t           intpri;	/* priority level of the process */
	ulong_t           reg[19];	/* non-volatile regs (13..31) */
#else /* _ALL_SOURCE */
	struct label_t   *__prev;	/* chain to previous */
	ulong_t           __iar;	/* resume address */
	ulong_t           __stack;	/* stack pointer */
	ulong_t           __toc;	/* toc pointer */
	ulong_t           __cr;         /* non-volatile part of cr */
	ulong_t           __intpri;	/* priority level of the process */
	ulong_t           __reg[19];	/* non-volatile regs (13..31) */
#endif /* _ALL_SOURCE */
} label_t;

typedef int32long64_t	ext_t;		/* extended parameters	        */ 

#endif /*_H_M_TYPES*/

