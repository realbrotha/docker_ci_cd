/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/diag/bit_def.h 1.5                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1992          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)19	1.5  src/bos/usr/include/diag/bit_def.h, cmddiag, bos530 7/15/97 10:27:04 */
/*
 *   COMPONENT_NAME: CMDDIAG
 *
 *   FUNCTIONS: Diagnostic header file.
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1989,1991,1992
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */


#ifndef da_bits 
#define da_bits

/* diagnostic application mode bit definitions */

#define   DA_EXENV_IPL		0x00000001
#define   DA_EXENV_STD		0x00000002
#define   DA_EXENV_REGR		0x00000004
#define   DA_EXENV_CONC		0x00000008
#define   DA_ADVANCED_TRUE	0x00000010
#define   DA_ADVANCED_FALSE	0x00000020
#define   DA_SYSTEM_TRUE	0x00000040
#define   DA_SYSTEM_FALSE	0x00000080
#define   DA_DMODE_ELA		0x00000100
#define   DA_DMODE_PD		0x00000200
#define   DA_DMODE_REPAIR	0x00000400
#define   DA_DMODE_MS1		0x00000800
#define   DA_DMODE_MS2		0x00001000
#define   DA_DMODE_FREELANCE	0x00002000
#define   DA_LOOPMODE_NOTLM	0x00004000
#define   DA_LOOPMODE_ENTERLM	0x00008000
#define   DA_LOOPMODE_INLM	0x00010000
#define   DA_LOOPMODE_EXITLM	0x00020000
#define   DA_CONSOLE_TRUE	0x00040000
#define   DA_CONSOLE_FALSE	0x00080000
#define   DA_EXENV_SYSX		0x00100000
#define	  DA_DMODE_ALL_SIBLINGS_MISSING 0x00200000

#endif
