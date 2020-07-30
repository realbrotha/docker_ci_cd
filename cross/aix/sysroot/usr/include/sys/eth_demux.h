/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/eth_demux.h 1.10                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1993,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)21  1.10  src/bos/kernel/sys/eth_demux.h, sysxdmx, bos53Q, q2008_08B7 2/14/08 10:36:03 */
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
#ifndef _NET_ETH_DEMUX_H
#define _NET_ETH_DEMUX_H

#include <net/nd_lan.h>

#define	ETHDMX_HASH		18
#define VLAN_HASH               19

/*
 * The eth_user struct allows for a linked list of ethertype users
 * that hash into the same cell.
 */
struct eth_user {
	struct eth_user		*next;
	struct eth_user		*prev;
	struct ns_user 		user;
	struct ns_8022 		filter;
};

struct vlan_user {
	struct vlan_user	*next;
	struct vlan_user	*prev;
	struct ns_user 		user;
	struct ns_vlan 		filter;
};

struct eth_dmx_stats {
	__ulong32_t	nd_ethertype_accepts;	/* # ethertypes accepted */
	__ulong32_t	nd_ethertype_rejects;	/* # ethertypes rejected */
};

/*
 * The eth_dmx_ctl struct contains all the ethertype users in a hash table,
 * as well as the single tap user.
 */
struct eth_dmx_ctl {
	struct eth_user		hash_heads[ETHDMX_HASH];
	struct ns_user 		tap_user;
	struct eth_dmx_stats	stats;
	int			n_users;
        struct vlan_user        vlan_hash_heads [VLAN_HASH];
	int			read_cnt;	/* used to make the demuxer 
						 * lock a rw lock */
};

typedef struct eth_dmx_ctl eth_dmx_ctl_t;

#define ETHDMX_WRITE_LOCK(ndd) 	\
{ \
	_dmx_s = disable_lock(PL_IMP, &(ndd)->ndd_demux_lock); \
	if (((ndd)->ndd_specdemux) != NULL)	\
	{ \
		volatile int *myvalptr = &((eth_dmx_ctl_t *)((ndd)->ndd_specdemux))->read_cnt; \
		while (*myvalptr); \
	} \
}

#define ETHDMX_WRITE_UNLOCK(ndd) \
	unlock_enable(_dmx_s, &(ndd)->ndd_demux_lock); 

/* In ETHDMX_READ_LOCK if the ndd_specdemux has not been allocated, then the 
 * lock cannot be obtained as a READ_LOCK.  In this case it will function as
 * a WRITE_LOCK (keeping the disable lock).  The calling routine can determine
 * this by looking at the p_dmx returned (NULL meaning this is a write lock).
 * The same p_dmx returned needs to be passed to the READ_UNLOCK to determine 
 * what needs to be undone.
 */
#define ETHDMX_READ_LOCK(ndd, p_dmx) \
{ \
	int read_pri;	\
	_dmx_s = i_disable(PL_IMP); \
	read_pri = disable_lock(PL_IMP, &(ndd)->ndd_demux_lock); \
	(p_dmx) = (eth_dmx_ctl_t *)((ndd)->ndd_specdemux); \
	if (p_dmx) \
	{		\
		fetch_and_add(&((p_dmx)->read_cnt), 1); \
		unlock_enable(read_pri, &(ndd)->ndd_demux_lock); \
	}		\
}

#define ETHDMX_READ_UNLOCK(ndd, p_dmx) { \
	if (p_dmx)	\
	{	\
		fetch_and_add(&(((eth_dmx_ctl_t *)((ndd)->ndd_specdemux))->read_cnt), -1); \
		i_enable(_dmx_s); \
	}	\
	else	\
	{	\
		unlock_enable(_dmx_s, &(ndd)->ndd_demux_lock); \
	}	\
}

/* large receive control flags, passed in the ctl argument of the
 * eth_large_receive() function.
 */
#define LR_VIOENT     0x00000001 /* indicates caller is the virtual ethernet 
                                  * device driver */
#define LR_TRUSTED    0x00000002 /* indicates caller has passed in a packet
                                  * chain containing ONLY DIX/IPV4/TCP packets
                                  * with RX TCP checksums that been validated 
                                  * as good */

/* The lr_stat struct contains the large receive statistics maintained
 * by the eth_large_receive() function.  The caller of eth_large_receive()
 * can choose to use or ignore these statistics as desired.
 */
typedef struct lr_stat {
    uint32_t      rx_tcpaggr;          /* # of TCP large receive packets 
                                        * created */
    uint32_t      rx_tcpaggr_pktcount; /* # of packets aggregated into TCP
                                        * large receive packets */
    uint32_t      rx_tcpaggr_bytecount;/* # of TCP payload bytes aggregated
                                        * into TCP large receive packets */
    uint32_t      rx_tcpaggr_maxpkt;   /* maximum # of packets that were
                                        * aggregated into a TCP large receive
                                        * packet */
    uint32_t      reserved[28];         /* reserved for future use */
} lr_stat_t;

/* The lr_info struct contains required information that is passed to 
 * the eth_large_receive() function via the workspace argument.
 */
typedef struct lr_info {
        lr_stat_t lrstat;       /* large receive statistics */
        int32_t   bufsize;      /* size in bytes of workspace buffer (min is
                                 * 4096 bytes of pinned kernel memory) */
        uint32_t  reserved[31]; /* reserved for future use */
} lr_info_t;


#endif
