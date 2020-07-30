/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/cdli_entuser.rrent.h 1.5                     */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2008,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)46	1.5  src/bos/kernel/sys/cdli_entuser.rrent.h, pcirrent, bos53V, v2009_10A9 2/27/09 17:37:35 */

#ifndef _H_CDLI_ENTUSER_RRENT
#define _H_CDLI_ENTUSER_RRENT

/* Miscellaneous definitions */
#define ENT_RR_JUMBO_MAX_MTU    (9014)     /* Jumbo packet max data size    */
#define MAX_QSETS               (8)        /* Device supports up to 8 QSets */

/* Device specific statistics */
#ifndef LINK_UP
#define LINK_UP		 (1)    /* Link is UP            */
#define LINK_DOWN	 (0)    /* Link is DOWN 	 */
#define LINK_UNKNOWN	 (2)    /* Link is UNKNOWN       */
#define MEDIA_10_HALF	 (0)    /* 10 Mbps Half Duplex   */
#define MEDIA_10_FULL	 (1)    /* 10 Mbps Full Duplex   */
#define MEDIA_100_HALF	 (2)    /* 100 Mbps Half Duplex  */
#define MEDIA_100_FULL	 (3)    /* 100 Mbps Full Duplex  */
#define MEDIA_AUTO	 (4)    /* Autonegotiation       */
#define MEDIA_1000_FULL	 (5)    /* 1000 Mbps Full Duplex */
#define MEDIA_10000_FULL (6)    /* 10 Gbps Full Duplex   */
#endif

#define dd_stats_t rrent_stats_t
struct rrent_stats
{
        #define         B_MARK_STATS           (0x4445565354415453LL)/* "DEVSTATS" */
        uint64_t        b_mark;                 /* Begin structure marker          */

        uint8_t         parent_hba[32];         /* Parent hba device, ie: hba0     */
	uint32_t    	link_status;            /* Negotiated link status          */
	uint32_t	media_speed;	        /* Speed negotiated by adapter     */
        uint32_t	tx_tcpseg_maxsize;      /* Maximum large send size         */
        uint32_t	rx_tcpaggr_maxpkt;      /* Maximum large receive pkts      */
        uint32_t        prom_count;             /* Number of promiscuous CDLI users*/
        uint32_t        mcast_count;            /* Number of multicast CDLI users  */
        uint32_t        mcast_addresses;        /* Number of multicast addresses   */
        uint32_t        number_of_qsets_allocated; /* Number of allocated qsets    */
        uint32_t        tx_qset_ofq_packets[MAX_QSETS]; /* Current # of tx ofq pkts*/
        uint32_t        tx_qset_ofq_bytes[MAX_QSETS]; /*Current # of tx ofq bytes  */
        uint64_t        tx_total_ofq_packets;   /* Lifetime number of tx ofq pkts  */
        uint64_t        tx_total_ofq_bytes;     /* Lifetime number of tx ofq bytes */
	uint64_t	functions;		/* JUMBOF/TCPSEG/TCPAGG            */
	uint64_t	tx_tcpseg;		/* # of large send offload packets */
        uint64_t	rx_tcpaggr;             /* # of large receive packets      */
        uint64_t	rx_tcpaggr_pktcount;    /* # of RX TCP packets aggregated  */
                                                /* into large receive packets      */
        uint64_t	rx_tcpaggr_bytecount;   /* # of RX TCP payload bytes       */
                                                /* Aggregated into large receive   */
                                                /* packets                         */
	uint64_t        library_memory_usage;   /* Total # of bytes used in library*/
	uint64_t        driver_memory_usage;    /* Total # of bytes used in NIC    */
	uint64_t 	reserved[128];		/* Reserved for future use	   */

        uint64_t        e_mark;                 /* End structure marker            */
        #define         E_MARK_STATS           (0x6465767374617473LL)/* "devstats" */

};
typedef struct rrent_stats rrent_stats_t;

/* Bitmaps for functions flag in rrent_stats above */
#define	JUMBOF		(0x1)
#define TCPSEG		(0x2)
#define TCPAGGR		(0x4)
#define QSETSRUN        (0x8)

#define dd_all_stats_t  rrent_all_stats_t
struct rrent_all_stats
{
	ndd_genstats_t  ent_nddstats;	            /* Network generic statistics  */
	ent_genstats_t  ent_genstats;	            /* Ethernet generic statistics */
	dd_stats_t      dd_stats;	            /* Device specific statistics  */
};
typedef struct rrent_all_stats rrent_all_stats_t;

/* Trace hooks */
#define HKWD_RRENT_OTHER	(0x644)	        /* Other events    */
#define HKWD_RRENT_XMIT		(0x645)	        /* Transmit events */
#define	HKWD_RRENT_RECV		(0x646)	        /* Receive events  */

#endif	/* _H_CDLI_ENTUSER_RRENT */

