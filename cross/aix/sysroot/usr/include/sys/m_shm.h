/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/POWER/m_shm.h 1.3                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)01     1.3  src/bos/kernel/sys/POWER/m_shm.h, sysipc, bos530 7/11/02 14:03:02 */
/*
 * COMPONENT_NAME: (SYSIPC) IPC Shared Memory Facility
 *
 * FUNCTIONS:
 *
 * ORIGINS: 3,27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1987, 1993
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _H_M_SHM
#define _H_M_SHM

/*
 * POWER definitions for shm.h.
 */

#define SHMLOSEG64      (0x70000000u)
#define SHMHISEG64      (0x7fffffffu)

/* maximum number of shared memory segments a 64-bit process can
 * attach using undirected shmat()
 */
#define NSHMSEGS64      (SHMHISEG64 - SHMLOSEG64 + 1)

#endif /* _H_M_SHM */
