/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/cur04.h 1.9                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1988          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)52	1.9  src/bos/usr/include/cur04.h, libcurses, bos530 5/14/91 17:17:51 */
#ifndef _H_CUR04
#define _H_CUR04
/*
 * COMPONENT_NAME: (LIBCUR) Extended Curses Library
 *
 * FUNCTIONS: cur04.h
 *
 * ORIGINS: 10, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1988
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

extern char *_unctrl[];

#define	unctrl(ch)	(_unctrl[(unsigned) ch])

#endif				/* _H_CUR04 */
