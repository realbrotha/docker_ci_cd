/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/cdli_entuser.scent.h 1.11                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2001,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)85       1.11  src/bos/kernel/sys/cdli_entuser.scent.h, pciscent, bos53D, d2005_06A5 1/24/05 14:37:12 */

#ifndef _H_CDLI_ENTUSER_SCENT
#define _H_CDLI_ENTUSER_SCENT

/* device_type field in scent_stats_t holds one of the following values */
#define ENT_SCENT_PCI	0x00000012    	/* 10/100 Mbps Ethernet PCI II Adapter*/

/* 10/100 Mbps Ethernet PCI Adapter II (1410ff01) device specific statistics */
struct scent_stats {
	uint	tx_timeout_rtn;		/* # of entries to TX timeout routine */
	uint	link_status;		/* negotiated link status 	*/
#ifndef	LINK_UP
#define LINK_UP		(1)		/* Link is UP 			*/
#define LINK_DOWN	(0)		/* Link is DOWN 		*/
#define LINK_LIMBO      (2)             /* Link is LIMBO                */
#endif
	uint	speed_selected;		/* speed and mode selected by user */
	uint	speed_negotiated;	/* speed and mode negotiated by card */
#ifndef	MEDIA_10_HALF
#define MEDIA_10_HALF	(0)		/* 10 Mbps Half Duplex 		*/
#define MEDIA_10_FULL	(1)		/* 10 Mbps Full Duplex 		*/
#define MEDIA_100_HALF	(2)		/* 100 Mbps Half Duplex 	*/
#define MEDIA_100_FULL	(3)		/* 100 Mbps Full Duplex 	*/
#define MEDIA_AUTO	(4)		/* Autonegotiation 		*/
#endif
	uint	coll_freq[16];		/* Frequency of number of collissions */
	uint	rxbuf_pool_size;	/* Total number of mbufs pre-allocated
					 * to the RX buffer pool 	*/
	uint	mapped_rxbuf_err;	/* Number of times the receive handler
					 * had to get an mbuf from system */
	uint	rxbuf_too_small_err;	/* RX buffer too small error 	*/
	uint	ipsec_xmit_msw;		/* IPSec TX packets (msw) */
	uint	ipsec_xmit_lsw;		/* IPSec TX packets (lsw) */
	uint	ipsec_xmit_drop_msw;	/* IPSec TX packets dropped (msw) */
	uint	ipsec_xmit_drop_lsw;	/* IPSec TX packets dropped (lsw) */
	uint	ipsec_rx_msw;		/* IPSec RX packets (msw) */
	uint	ipsec_rx_lsw;		/* IPSec RX packets (lsw) */
	uint	ipsec_rx_drop_msw;	/* IPSec RX packets dropped (msw) */
	uint	ipsec_rx_drop_lsw;	/* IPSec RX packets dropped (lsw) */
	uint	ipsec_rx_sa_cnt;	/* Number of RX SAs offloaded */
	uint	ls_xmit_msw;		/* Large Send packets TX (msw) */
	uint	ls_xmit_lsw;		/* Large Send packets TX (lsw) */
	uint	ls_drop_msw;		/* Large Send packets dropped (msw) */
	uint	ls_drop_lsw;		/* Large Send packets dropped (lsw) */
	uint	device_type;
};
typedef struct scent_stats scent_stats_t;

struct scent_all_stats {
	struct ndd_genstats ent_ndd_stats;	/* network generic stats */
	struct ent_genstats ent_gen_stats;	/* ethernet generic stats */
	struct scent_stats  scent_stats;	/* device specific stats */
};
typedef struct scent_all_stats scent_all_stats_t;

/* used by the IPsec driver to identify the adapter type */
#define SCENT_IPSEC_DEVID	0x1410ff01	/* device id for IPsec */

/* IPsec device dependent structure */
struct scent_ipsec_dds {
	uchar	*key_ipad;		/* Digested IPAD key */
	uchar	*key_opad;		/* Digested OPAD key */
};
typedef struct scent_ipsec_dds scent_ipsec_dds_t;

/* trace hook numbers */
#define HKWD_SCENT_XMIT		0x470	/* transmit events 		*/
#define	HKWD_SCENT_RECV		0x471	/* receive events 		*/
#define HKWD_SCENT_OTHER	0x472	/* other events 		*/

#endif	/* _H_CDLI_ENTUSER_SCENT */
