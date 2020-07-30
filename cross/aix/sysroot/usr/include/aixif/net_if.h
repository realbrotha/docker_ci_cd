/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/aixif/net_if.h 1.15                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)70	1.15  src/bos/usr/include/aixif/net_if.h, sockinc, bos530 3/12/03 17:36:09 */
/*
 *   COMPONENT_NAME: SYSXAIXIF
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1989,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#include <net/if.h>

#ifdef __cplusplus
struct file;
struct ifnet;
struct mbuf;
#endif

#ifndef _H_NET_IF
#define _H_NET_IF

/*******************************************************************************
* net_if.h -	definitions pertaining to the the network drivers	       *
*******************************************************************************/

struct en_ddi {
	int			reserved;
};

struct ie3_ddi {
	int			reserved;
};

struct ie5_ddi {
	int			reserved;
};

struct x25_ddi {
	int			reserved;
};

struct sl_ddi {
	short			if_connect;	/* auto-disc flag for SLIP  */
};

/*******************************************************************************
*	Device request structure - used to pass configuration information      *
*				   to interface drivers			       *
*******************************************************************************/

#ifndef IFNAMSIZ 		/* Also defined in net/if.h */
#define IFNAMSIZ 16
#endif

struct device_req {
	char			dev_name[IFNAMSIZ];	/* device name        */
	dev_t			devno;		/* device number of interface */
};

#ifdef __64BIT__
struct device_req32 {
	char			dev_name[IFNAMSIZ];	/* device name */
	uint32_t		devno;
};
#else
struct device_req64 {
	char			dev_name[IFNAMSIZ];	/* device name */
	uint64_t		devno;
};
#endif /*__64BIT__*/


#define	MAX_NETIDS	16
/***************************************************************************
 *	netid list used during driver attach
 **************************************************************************/
struct netid_list {
	tid_t		attach_snooze;	/* thing to sleep on		*/
	u_short		start_complete;	/* true if all starts worked	*/
	u_short		complete_count;	/* # of start completes so far	*/
	u_short		id_count;	/* number of netids to start	*/
	u_short		id_length;	/* length of netids		*/
	u_short		id[MAX_NETIDS];	/* list of netids to start	*/
	Simple_lock	slock;		/* locking for starts   	*/
};


/* 
 * queued write paramaters 
 */
struct qwrite {
	struct file 	*netfp;
	struct ifnet	*ifp;
	int		length;
	struct mbuf	*ext;
};

/* 
 * queued ioctl paramaters 
 */
struct qioctl {
	struct file 	*netfp;
	int		cmd;
	struct mbuf	*arg;
	struct mbuf	*ext;
};

/* 
 * header for packet tracing
 */
struct o_packet_trace_header {
	u_short	type;			/* packet type */
	u_char	hlen;			/* length of packet header */
	u_char	unit;			/* unit number of interface */
	char	ifname[IFNAMSIZ];	/* name of interface */
	u_char	iftype;			/* interface type */
	u_char	xmit_pkt;		/* xmit or receive packet? */
};

struct packet_trace_header {
	u_short	type;			/* packet type */
	u_char	hlen;			/* length of packet header */
	u_char	unit;			/* unit number of interface */
	char	ifname[IFNAMSIZ];	/* name of interface */
	u_char	iftype;			/* interface type */
	u_char	xmit_pkt;		/* xmit or receive packet? */
	u_short	rdrops;			/* number dropped since last success */
	struct timestruc_t ts;		/* time packet recveived/transmitted */
};

#endif /* _H_NET_IF */
