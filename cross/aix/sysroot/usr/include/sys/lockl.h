/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/lockl.h 1.12                                 */
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
/* @(#)99	1.12  src/bos/kernel/sys/lockl.h, sysproc, bos530 10/13/98 12:52:44 */
/*
 *   COMPONENT_NAME: SYSPROC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 27, 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988, 1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_LOCKL
#define _H_LOCKL

#include <sys/lock_def.h>

/*
 *  Global kernel locks.
 *
 *  These lock words are pinned.  Other lock words, imbedded in
 *  various kernel structures, need not be.
 *
 *  Locks are defined here in resource order.  The rule is that
 *  lower-order locks must NOT be acquired when a higher-order lock is
 *  already owned.  Following this rule prevents deadlocks.  Declaring
 *  the lock words in ascending resource order allows DEBUG code to
 *  check that the rules are actually being followed.
 */

/*
 *  Since it is not normally held across waits, the kernel non-premption
 *  lock is exempted from the resource ordering rule.
 */
extern lock_t kernel_lock;	/* kernel mode non-preemption lock */

#ifdef _KERNSYS
/*
 * kernel_lock is gone on the 64bit kernel.
 * these macros are here to help ease the number of ifdefs.
 *
 * REL_KERNEL_LOCK and GET_KERNEL_LOCK are intended for places
 * where the kernel lock has to be released then re-acquired.
 * thus, the state is saved on the unlock.
 */
#ifdef __64BIT_KERNEL
#define REL_KERNEL_LOCK(__state) 
#define GET_KERNEL_LOCK(__state)
#else
#define REL_KERNEL_LOCK(__state)                     \
        if (__state = (IS_LOCKED(&kernel_lock)))     \
                unlockl(&kernel_lock);

#define GET_KERNEL_LOCK(__state)                     \
	if (__state)                                 \
		lockl(&kernel_lock,LOCK_SHORT);
#endif /* __64BIT_KERNEL */

#endif /* _KERNSYS */

#endif /* _H_LOCKL */
