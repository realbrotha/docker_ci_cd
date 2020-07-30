/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernext/inet/igmp_var.h 1.4                             */
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
/* @(#)88       1.4  src/bos/kernext/inet/igmp_var.h, sysxinet, bos530 11/10/00 13:59:02 */
/*
 *   COMPONENT_NAME: SYSXINET
 *
 *   FUNCTIONS: IGMP_RANDOM_DELAY
 *		
 *
 *   ORIGINS: 26,27,85,89
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * 
 * (c) Copyright 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 * 
 */
/*
 * OSF/1 1.2
 */
/*
 * Internet Group Management Protocol (IGMP),
 * implementation-specific definitions.
 *
 * Written by Steve Deering, Stanford, May 1988.
 *
 * MULTICAST 1.1
 */

struct igmpstat {
	u_int	igps_rcv_total;		/* total IGMP messages received    */
	u_int	igps_rcv_tooshort;	/* received with too few bytes     */
	u_int	igps_rcv_badsum;	/* received with bad checksum      */
	u_int	igps_rcv_queries;	/* received membership queries     */
	u_int	igps_rcv_badqueries;	/* received invalid queries        */
	u_int	igps_rcv_reports;	/* received membership reports     */
	u_int	igps_rcv_badreports;	/* received invalid reports        */
	u_int	igps_rcv_ourreports;	/* received reports for our groups */
	u_int	igps_snd_reports;	/* sent membership reports         */
#if	defined(_KERNEL) && LOCK_NETSTATS
	simple_lock_data_t igps_lock;	/* statistics lock */
#endif
};

/* distributed igmp stat structure; assembled later */

struct dist_igmpstat {
	u_int	igps_rcv_total;		/* total IGMP messages received    */
	u_int	igps_rcv_tooshort;	/* received with too few bytes     */
	u_int	igps_rcv_badsum;	/* received with bad checksum      */
	u_int	igps_rcv_queries;	/* received membership queries     */
	u_int	igps_rcv_badqueries;	/* received invalid queries        */
	u_int	igps_rcv_reports;	/* received membership reports     */
	u_int	igps_rcv_badreports;	/* received invalid reports        */
	u_int	igps_rcv_ourreports;	/* received reports for our groups */
	u_int	igps_snd_reports;	/* sent membership reports         */
#if	defined(_KERNEL) && LOCK_NETSTATS
	simple_lock_data_t igps_lock;	/* statistics lock */
#endif
	char    dummy[((sizeof(struct igmpstat) < IP_CACHE_LINE_SIZE) ?
		IP_CACHE_LINE_SIZE - sizeof(struct igmpstat) :
	 IP_CACHE_LINE_SIZE - (sizeof(struct igmpstat) % IP_CACHE_LINE_SIZE))];
};

#ifdef _KERNEL
extern struct igmpstat igmpstat;
extern struct dist_igmpstat *dist_igmpstat[];

/*
 * Macro to compute a random timer value. 
 */
#define IGMP_RANDOM_DELAY(X) ((int) random_num_gen() % (X) + 1)

#endif
