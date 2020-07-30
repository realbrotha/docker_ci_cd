/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/ccs/lib/libxcurses/unctrl.h 1.1.1.1                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1994,1997          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)77	1.1.1.1  src/bos/usr/ccs/lib/libxcurses/unctrl.h, libcurses, bos530 9/6/97 15:23:20  */
/*
 *   COMPONENT_NAME: LIBCURSES
 *
 *   FUNCTIONS: unctrl
 *
 *   ORIGINS: 27, 110
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1994,1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*      Copyright (c) 1984 AT&T
 *        All Rights Reserved
 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T
 *      The copyright notice above does not evidence any
 *      actual or intended publication of such source code.
 */

/*
 * unctrl.h
 *
 */

#ifndef UNCTRL_H
#define	UNCTRL_H

extern char	*_unctrl[];

#if	!defined(NOMACROS) && !defined(lint)

#define	unctrl(ch)	(((ch&0x7f)==ch)? _unctrl[ch]:NULL)

#endif	/* NOMACROS && lint */

#endif	/* UNCTRL_H */
