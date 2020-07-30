/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/POWER/m_param.h 1.12                         */
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
/* @(#)33	1.12  src/bos/kernel/sys/POWER/m_param.h, sysproc, bos530 10/14/98 18:30:40 */
/*
 * LEVEL 1,  5 Years Bull Confidential Information
 */


#ifndef _H_M_PARAM
#define _H_M_PARAM

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#define _NSRS  16
#define _NGPRS 32
#define _NFPRS 32

/* routines for loading and storing words in faultable critical sections */
#define	_LOADWCS(__x)		(* (volatile tid_t *) (__x))
#define _STORWCS(__x,__y)	(*(__y) = (__x))

#define	_HZ	100		/* ticks per second of the clock	*/
#define	__hz	HZ		/* Berkeley uses lower case hz		*/
#define _CLKTICK 20408		/* microseconds in a clock tick (49 HZ)	*/

#define _MAXSEG	(64*1024)	/* max seg size (in clicks)		*/
/* default max data seg size is linear fn of avail pg space at boot time*/
/*
 * Virtual memory related constants, all in bytes, on page boundries
 */
#define	_MAXTSIZ	(256*256*4096)		/* max text size */
#define	_DFLDSIZ	(128*256*4096)		/* initial data size limit */
#define	_MAXDSIZ	(256*256*4096)		/* max data size */
#define	_DFLSSIZ	( 16*256*4096)		/* initial stack size limit */
#define	_MAXSSIZ	(256*256*4096)		/* max stack size */

#ifdef _ALL_SOURCE
#define NSRS		_NSRS
#define NGPRS		_NGPRS
#define NFPRS		_NFPRS
#define	LOADWCS		_LOADWCS
#define STORWCS		_STORWCS
#define	HZ		_HZ
#define	hz		__hz
#define CLKTICK		_CLKTICK
#define MAXSEG		_MAXSEG
#define	MAXTSIZ		_MAXTSIZ
#define	DFLDSIZ		_DFLDSIZ
#define	MAXDSIZ		_MAXDSIZ
#define	DFLSSIZ		_DFLSSIZ
#define	MAXSSIZ		_MAXSSIZ
#endif /* _ALL_SOURCE */
#endif /*_H_M_PARAM*/
