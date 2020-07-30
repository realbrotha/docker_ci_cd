/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/POWER/m_procfs.h 1.3                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*****************************************************************************
 *
 *   COMPONENT_NAME: SYSPROC  (m_procfs.h)
 *
 *   Description:  Machine/platform specific fields for PowerPC /proc files.
 *
 ****************************************************************************/
/* @(#)77       1.3  src/bos/kernel/sys/POWER/m_procfs.h, procfs, bos53D, d2005_12B9 3/15/05 14:19:56 */

#ifndef _H_PROCFS_M_PROCFS
#define _H_PROCFS_M_PROCFS

#include <sys/m_param.h>
#include <sys/context.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*****************************************************************************
 *
 * prgregset:  general and special purpose registers
 *
 * Note:  prgregset uses same names and format as the __context64 struct in
 *        context.h except for not containing the floating point registers.
 *        This struct is similar to the ptsprs which is used by ptrace.
 *        All debugging processes, 32-bit and 64-bit, will use one struct
 *        that has 64-bit entries.
 *        The decision to choose the following registers in prgregset struct
 *        is because they are all accessible by user-level software
 *
 ****************************************************************************/

typedef struct prgregset
{
        size64_t   __iar;               /* Instruction Pointer          */
	size64_t   __msr;		/* machine state register	*/
	size64_t   __cr;		/* condition register		*/
	size64_t   __lr;		/* link register		*/
	size64_t   __ctr;		/* count register		*/
	size64_t   __xer;		/* fixed point exception	*/
	size64_t   __fpscr;	        /* floating point status reg	*/
	size64_t   __fpscrx;	        /* extension floating point	*/

        size64_t   __gpr[_NGPRS];       /* static general registers     */

        size64_t   __pad1[8];           /* Reserved for future use      */
} prgregset_t;



/*****************************************************************************
 *
 *  prfpregset:  floating point register set
 *
 ****************************************************************************/

typedef struct prfpregset
{
        double __fpr[_NFPRS];         /* Floating Point Registers        */

} prfpregset_t;

/*****************************************************************************
 *
 *  prvregset:  vector register set
 *
 ****************************************************************************/

typedef struct __vmx_context prvregset_t;

/*****************************************************************************
 *
 *  prextset:  extended context set
 *
 *  NOTE: This must match the layout of the __extctx_t structure 
 *        Future additions to the __extctx_t structure should also be
 *        reflected here if the info is desired on reads of the status
 *        and lwpstatus files
 *
 ****************************************************************************/

typedef struct prextset 
{	
	unsigned int __flags;		/* extended context flags */
	unsigned int __rsvd1[3];	/* reserved */
	prvregset_t  __vrs;		/* vector register state */

} prextset_t;


/*****************************************************************************
 *
 * Machine specific control messages.
 *
 * Note:  These numbers must be larger than PR_FAMILY_START
 *
 ****************************************************************************/

/* There are currently no PowerPC machine specific control messages. */

/*****************************************************************************
 *
 * Family-specific part of /proc/pid#/lwpstatus file.
 *
 ****************************************************************************/
typedef struct pfamily
{
	uint64_t pr_extoff;   /* offset of the prextset relative to the
			       * current status file (status or lwpstatus)
			       * zero if none */
	uint64_t pr_extsize;  /* size of extension, zero if none */
	uint64_t pr_pad[14];  /* reserved for future use.  Sized to allow
                               * for 14 64-bit registers */
} pfamily_t;



#if defined(__cplusplus)
        }
#endif

#endif  /* _H_PROCFS_M_PROCFS */
