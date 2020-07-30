/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/tok_demux.h 1.5                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1993,1997          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)25	1.5  src/bos/kernel/sys/tok_demux.h, sysxdmx, bos530 7/2/97 15:03:33 */
/*
 *   COMPONENT_NAME: SYSXDMX
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _NET_TOK_DEMUX_H
#define _NET_TOK_DEMUX_H

struct tok_dmx_stats {
	__ulong32_t	nd_mac_accepts;		/* # MAC frames accepted */
	__ulong32_t	nd_mac_rejects;		/* # MAC frames rejected */
};

/*
 * Token Ring demuxer supports one MAC user and one TAP user.
 */
struct tok_dmx_ctl {
	ns_user_t 		mac_user;
	ns_user_t 		tap_user;
	struct tok_dmx_stats	stats;
	int			n_users;
};

typedef struct tok_dmx_ctl tok_dmx_ctl_t;

#define	TOK_DEMUX_MAC	(NS_LAST_FILTER + 1)	/* Mac user filter type */

#endif
