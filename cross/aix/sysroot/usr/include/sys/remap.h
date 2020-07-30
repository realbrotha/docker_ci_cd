/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/remap.h 1.10                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2000          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)58	1.10  src/bos/kernel/sys/remap.h, incsys, bos530 10/19/00 11:53:39  */
/*
 *   COMPONENT_NAME: INCSYS
 *
 *   ORIGINS: 27
 *
 */

#ifndef _REMAP_H
#define _REMAP_H

#ifdef _KERNEL

#ifdef __64BIT_KERNEL
#define saveretval64(a) (a)
#define get64bitparm(a,b) (a)
#else
extern unsigned long long saveretval64(unsigned long long);
extern unsigned long long get64bitparm(unsigned long, int);
extern int		  as_remap64(unsigned long long, unsigned int,
				     unsigned int *);
extern unsigned long long as_unremap64(char *);
#endif /* __64BIT_KERNEL */

#endif /* _KERNEL */
#endif /* _REMAP_H */
