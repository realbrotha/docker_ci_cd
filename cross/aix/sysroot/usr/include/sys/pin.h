/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/pin.h 1.10                                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)67     1.10  src/bos/kernel/sys/pin.h, sysvmm, bos530 3/6/01 18:26:23 */

/*
 * COMPONENT_NAME: (SYSVMM) Virtual Memory Manager
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_PIN
#define _H_PIN

/*
**	PIN kernel service
*/

int
pincode(int (*func)());

#define PIN_SUCC	 0 		/*  return value if successful        */
#define MEM_INSUFF	ENOMEM		/*  insufficient memory avail.        */
#define MEM_INVAL	EINVAL		/*  specified range of memory invalid
					 *  or length parameter negative      */

/*
**	UNPIN kernel service -- additional defines
*/

int
unpincode(int (*func)());

#define UNPIN_SUCC	 0		/*  return value if successful        */
#define UNPIN_UNDERFL	EINVAL		/*  one or pages were not pinned      */

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
int ltpin(void * vaddr, long nbytes);
int ltunpin(void * vaddr, long nbytes);
int pin(void * vaddr, long nbytes);
int unpin(void * vaddr, long nbytes);
#endif

#ifdef _KERNEL
    int vm_pinp (vmid_t, vpn_t, vpn_t, uint);
    int vm_unpinp(vmid_t, vpn_t, vpn_t);
#endif


#endif	/* _H_PIN */
