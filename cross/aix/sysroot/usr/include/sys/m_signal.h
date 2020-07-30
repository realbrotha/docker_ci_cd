/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/POWER/m_signal.h 1.4                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)68       1.4  src/bos/kernel/sys/POWER/m_signal.h, sysproc, bos530 7/25/02 19:28:15 */

#define _STACK_FLOOR	256		/* see <sys/reg.h> */

#define MINSIGSTKSZ     ((sizeof (ucontext_t))+2*_STACK_FLOOR)	/* min size...*/
#define SIGSTKSZ        4096	/* useful size... for alternate signal stack  */

