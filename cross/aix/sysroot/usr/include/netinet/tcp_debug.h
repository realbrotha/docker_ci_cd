/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernext/inet/tcp_debug.h 1.17                           */
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
/* @(#)36	1.17  src/bos/kernext/inet/tcp_debug.h, sysxinet_tcp, bos53D, d2005_09B1 2/17/05 02:30:31 */
/*
 *   COMPONENT_NAME: SYSXINET
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 26,27,85,127,196
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1997
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * OSF/1 1.2
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *	Base:	tcp_debug.h	7.3 (Berkeley) 6/29/88
 *	Merged:	tcp_debug.h	7.4 (Berkeley) 6/28/90
 */

#ifndef _TCP_DEBUG_H_
#define _TCP_DEBUG_H_

#define MAX_TCPOPT_LEN   64

struct tcp_opt {
  char opt_len;
  u_char opt[MAX_TCPOPT_LEN];
};

struct	tcp_debug {
	n_time	td_time;
	short	td_act;
	short	td_ostate;
	caddr_t	td_tcb;
	char	family;
          short   td_trclev;
	union {
		struct tcpiphdr		td_ti;
		struct tcpip6hdr	td_ti6;
	} tiboth ;
#define td_ti tiboth.td_ti
#define td_ti6 tiboth.td_ti6
	short	td_req;
	struct	tcpcb td_cb;
          struct tcp_opt tcpopt;
};

#define	TA_INPUT 	0
#define	TA_OUTPUT	1
#define	TA_USER		2
#define	TA_RESPOND	3
#define	TA_DROP		4

#ifndef	CONST
#define	CONST
#endif

#ifdef TANAMES
CONST	char	*tanames[] =
    { "input", "output", "user", "respond", "drop" };
#endif

extern long tcp_ndebug;
extern	struct	tcp_debug *tcp_debug;
extern	int	tcp_debx;

#endif /* _TCP_DEBUG_H_ */
