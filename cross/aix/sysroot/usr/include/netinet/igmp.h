/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernext/inet/igmp.h 1.3                                 */
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
/* @(#)90       1.3  src/bos/kernext/inet/igmp.h, sysxinet, bos530 2/4/03 14:16:20 */
/*
 *   COMPONENT_NAME: SYSXINET
 *
 *   FUNCTIONS: 
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
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 1.2
 */
/*
 * Internet Group Management Protocol (IGMP) definitions.
 *
 * Written by Steve Deering, Stanford, May 1988.
 *
 * MULTICAST 1.1
 */

/*
 * IGMP packet format.
 */
struct igmp {
	u_char		igmp_type;	/* version & type of IGMP message  */
	u_char		igmp_code;	/* unused, should be zero          */
	u_short		igmp_cksum;	/* IP-style checksum               */
	struct in_addr	igmp_group;	/* group address being reported    */
};					/*  (zero for queries)             */

#define IGMP_MINLEN		     8

#define IGMP_HOST_MEMBERSHIP_QUERY   0x11  /* message types, incl. version */
#define IGMP_HOST_MEMBERSHIP_REPORT  0x12
#define IGMP_DVMRP		     0x13  /* for experimental multicast   */
					   /*  routing protocol            */
#define IGMP_HOST_NEW_MEMBERSHIP_REPORT 0x16
#define IGMP_HOST_LEAVE_MESSAGE      0x17
#define IGMP_MTRACE		     0x1f  /* mcast traceroute messages    */
#define IGMP_MTRACE_RESP	     0x1e  /* traceroute resp. (to sender) */

#define IGMP_MAX_HOST_REPORT_DELAY   10    /* max delay for response to    */
					   /*  query (in seconds)          */
#define IGMP_TIMER_SCALE     10	    /* denotes that the igmp->timer filed */
				    /*specifies time in 10th os seconds */

#define IGMP_DELAYING_MEMBER                     1
#define IGMP_IDLE_MEMBER                         2
#define IGMP_LAZY_MEMBER                         3
#define IGMP_SLEEPING_MEMBER                     4
#define IGMP_AWAKENING_MEMBER                    5


#define IGMP_OLD_ROUTER                          0
#define IGMP_NEW_ROUTER                          1

#define IGMP_AGE_THRESHOLD		         540

#ifdef IGMP_STATES
static char *tostate[]={"","DELAYING_MEMBER","IDLE","LAZY","SLEEPING",
			"AWAKENING" };
#endif /* IGMP_STATES */

#ifdef _KERNEL
#ifdef IP_MULTICAST
void igmp_init();
void igmp_input(struct mbuf *, int);
void igmp_joingroup(struct in_multi *);
void igmp_leavegroup(struct in_multi *);
void igmp_fasttimo();
void igmp_slowtimo();
struct router_info* find_rti(struct ifnet *);
int fill_rti(struct in_multi *);
void igmp_sendpkt(struct in_multi *, int);
void igmp_sendleave(struct in_multi *);
#endif /* IP_MULTICAST */
 
extern	simple_lock_data_t         rti_lock; /* lock for rti list */
#define RTI_LOCKINIT()     {	\
	lock_alloc(&rti_lock, LOCK_ALLOC_PIN, RTI_LOCK_FAMILY, -1);	\
	simple_lock_init(&rti_lock);	\
}
#define RTI_LOCK_DECL()    int	_rtil;
#define RTI_LOCK()         _rtil = disable_lock(PL_IMP, &rti_lock)
#define RTI_UNLOCK()       unlock_enable(_rtil, &rti_lock)

#endif /* _KERNEL */
