/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/tcb.h 1.5                                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1991          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)01	1.5  src/bos/kernel/sys/tcb.h, syssauth, bos530 6/16/90 00:37:32 */
/*
 * COMPONENT_NAME: (TCBADM) 
 *
 * FUNCTIONS: tcb.h support for the tcb() routine.
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */                                                                   

#ifndef _H_TCB
#define _H_TCB

/*
 * TCB defines...
 */
#define	TCB_ON		0x1	/* enable the TCB attribute */
#define TP_ON		0x3	/* enable TCP and TP attributes */
#define TCB_OFF		0x0	/* disable TCB and TP attributes */
#define	TCB_QUERY	0x4	/* query TCB status */

#endif /* _H_TCB */
