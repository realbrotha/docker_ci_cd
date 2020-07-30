/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/sys/extendio.h 1.3                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2005               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)91       1.3  src/bos/kernel/sys/extendio.h, sysios, bos53H, h2005_40A6 9/14/05 17:33:44 */

#ifndef _H_EXTENDIO
#define _H_EXTENDIO

/* Extended buffer cache hints.  Acceptable values 
 * for the bx_cache_hint field of the bufx structure are: 
 */
#define CH_AGE_OUT_FAST         0x0010
#define CH_PAGE_WRITE           0x0020

/* Extended buffer I/O priority.  This is either unset (0)
 * or a ushort value from 1 and 15.  A lower number value 
 * indicates a higher I/O scheduling priority.  1 would 
 * therefore be the top scheduling priority (ie most 
 * important) and 15 would be the bottom scheduling 
 * priority (ie least important).  
 * 
 * I/O priority can be set on a per-I/O basis through aio, 
 * or on a per-process basis through the setiopri and 
 * getiopri interfaces described below.  
 */
#define IOPRIORITY_UNSET        0
#define IOPRIORITY_MIN          IOPRIORITY_UNSET
#define IOPRIORITY_MAX          15
#define IOPRIORITY_MASK		0xF

/* The following system calls provide the interface for 
 * getting and setting I/O priority on a per-process 
 * basis.  
 */
#ifdef _NO_PROTO

short setiopri();
short getiopri();

#else  /* _NO_PROTO */

short setiopri(pid_t, ushort);
short getiopri(pid_t);

#endif /* _NO_PROTO */
#endif /* _H_EXTENDIO */
