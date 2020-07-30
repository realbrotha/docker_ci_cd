/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos530 src/gos/2d/XTOP/include/aixXIM.h 1.2                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1991          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)77	1.2  com/XTOP/X11/aixXIM.h, xlib, gos320 5/22/91 10:50:11 */
/*
 *   COMPONENT_NAME: X11
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 16,27,40,42
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1991
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
 
 
/************************************************************************/
/*      _aixXIM.h                                                       */
/************************************************************************/
 
#ifndef	_aixXIM_h
#define	_aixXIM_h
 
#define	STRING_MASK		0x0001
#define	USED_MASK		0x0002
 
#define AIX_XIM_ERROR           0xffff
#define	NOT_USED_AND_NO_STRING	0x0000
#define	NOT_USED_AND_STRING	0x0001
#define	USED_AND_NO_STRING	0x0002
#define USED_AND_STRING		0x0003

#define AIM_TEXT_MAX_WIDTH      1024
 
#define PREFIX '@'
#define EQUAL  '='
typedef	enum	{ NoMore, More, IM } ModifierCategory;
 
typedef	enum	{ IMLookupNone, IMLookupChars, 
		  IMLookupKeysym, IMLookupBoth, IMBufferOverflow } Cstat;
	
#endif	/* _aixXIM_h */
