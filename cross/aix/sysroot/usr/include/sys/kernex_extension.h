/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/include/sys/bestx/kernex_extension.h 1.6         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)21	1.6  src/bos/kernel/include/sys/bestx/kernex_extension.h, syssauth, bos530 4/5/02 15:04:51 */
/*
 *  COMPONENT_NAME: SYSSAUTH
 *
 *  FUNCTIONS: none
 *
 *  ORIGINS: 27, 83
 *
 *  (C) COPYRIGHT International Business Machines Corp. 1997
 *  All Rights Reserved
 *
 *  Copyright (C) Bull S.A 1997
 *
 *  US Government Users Restricted Rights - Use, duplication or
 *  disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * LEVEL 1,5 Years Bull Confidential Information
 */

#ifndef _EXTENSION_H
#define _EXTENSION_H

/* definition of the security level (bit set) returned by os_seclevel */
#define _EXTENSION_NOTLOADED 0x00000000
#define _EXTENSION_C2        0x00000001
#define _EXTENSION_B1        0x00000002
#define _EXTENSION_BSN       0x00000004
#define _EXTENSION_IBM_C2    0x00000008
#define _EXTENSION_IBM_CC    0x00000010

extern int __extension_status;
extern int _extension_loaded(int);

#endif /* _EXTENSION_H */

