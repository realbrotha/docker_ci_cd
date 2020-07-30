/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/cdli_entuser.kngent.h 1.6                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2005,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */


/*
 * COMPONENT_NAME: pcikngent
 *
 * FUNCTIONS: none.
 */


#ifndef _H_CDLI_ENTUSER_KNGENT
#define _H_CDLI_ENTUSER_KNGENT

/* device_type field in kngent_stats_t holds one of the following values */
#define ENT_KNGENT_LR_PCIX	0x00000017 /* IBM 10 Gigabit-LR Ethernet     */
#define ENT_KNGENT_SR_PCIX	0x00000018 /* IBM 10 Gigabit-SR Ethernet     */

/* Miscellaneous definitions */
#define ENT_KNGENT_JUMBO_MAX_MTU	  9014     /* jumbo packet max data size     */

/* device specific statistics.                                               */
/* We can NOT use LINK_UP & LINK_DOWN ../include/sys/cdli_entuser.ethchan.h  */
/* includes ../include/sys/cdli_entuser.phxent.h and ../cdli_entuser.phxent.h*/
/* redefine LINK_UP & LINK_DOWN (poorly reading from ..phxent.h              */
#define KNGENT_LINK_DOWN			0  /* Link is DOWN 		     */
#define KNGENT_LINK_UP			1  /* Link is UP                     */
#define KNGENT_LINK_RESET			2  /* Link is being RESET            */

#define KNGENT_MAX_FILES_ENTRIES		10
#define KNGENT_FILE_NAME_LEN		20
#define KNGENT_FILE_REVISION_LEN		20
struct kngent_file_revision {
	char	filename[KNGENT_FILE_NAME_LEN];
	char	revision[KNGENT_FILE_REVISION_LEN];
};
typedef struct kngent_file_revision kngent_file_revision_t;

struct kngent_revisions {
	uint	entries;		   /* no. entries in the table       */
	kngent_file_revision_t files[KNGENT_MAX_FILES_ENTRIES]; 
};
typedef struct kngent_revisions kngent_revision_t;

struct kngent_stats {
	uint	tx_tcpseg;		   /* # of TCP TX seg offload pakets */
	uint	tx_tcpseg_err;		   /* # of TCP TX seg errors         */
        uint	rx_tcpseg;		   /* # of TCP RX seg offload        */
        uint	rx_tcpseg_err;		   /* # of TCP RX seg errors         */
        uint    device_type;               /* device type                    */
	uint	vlan_tx;		   /* # of VLAN packets transmitted  */
	uint	vlan_rx;		   /* # of VLAN packets received     */
	uint	jumbo_tx;		   /* # of jumbo frame packets trans.*/
	uint	jumbo_rx;		   /* # of jumbo frame packets recie.*/
	uint    link_status;               /* negotiated link status         */
	uint    functions;                 /* TXFLOW/RXFLOW/JUMBOF/TCPSEG    */
        uint    xonrxc;                    /* # of XON packets received      */
        uint    xontxc;                    /* # of XON packets transmitted   */
        uint    xoffrxc;                   /* # of XOFF packets received     */
        uint    xofftxc;                   /* # of XOFF packets transmitted  */
        uint    pcix_mode;                 /* 1 if pci-x, 0 if pci           */
        uint    pcix_spd;                  /* pci-x bus speed                */
        uint    pci66;                     /* 1 if bus is 66Mhz, 0 if 33Mhz  */
        uint    bus64;                     /* 1 if bus is 64bit, 0 if 32bit  */
        uint    rx_fifo;                   /* determine the rx/tx fifo split */
        uint    fcrth;                     /* flow ctrl rx thresh high       */
        uint    fcrtl;                     /* flow ctrl rx thresh low        */
	uint	cache_line_size;	   /* Cache line sz of PCI cfg space */
	uint	latency_timer;		   /* Latency timer of PCI cfg space */
	kngent_revision_t revision_tbl;      /* Revision of all 'c' files      */
	uint    recvdmt_lsw;		/* lsw of receive descriptor thresh count */
	uint    recvdmt_msw;		/* msw of receive descriptor thresh count */

        /* The following is a copy of the contents of xge_hal_stats_t */
        /* Tx MAC statistics counters. */
	uint32_t tmac_frms;
	uint32_t tmac_data_octets;
	uint64_t tmac_drop_frms;
	uint32_t tmac_mcst_frms;
	uint32_t tmac_bcst_frms;
	uint64_t tmac_pause_ctrl_frms;
	uint32_t tmac_ttl_octets;
	uint32_t tmac_ucst_frms;
	uint32_t tmac_nucst_frms;
	uint32_t tmac_any_err_frms;
	uint64_t tmac_ttl_less_fb_octets;
	uint64_t tmac_vld_ip_octets;
	uint32_t tmac_vld_ip;
	uint32_t tmac_drop_ip;
	uint32_t tmac_icmp;
	uint32_t tmac_rst_tcp;
	uint64_t tmac_tcp;
	uint32_t tmac_udp;
	uint32_t reserved_0;

        /* Rx MAC Statistics counters. */
	uint32_t rmac_vld_frms;
	uint32_t rmac_data_octets;
	uint64_t rmac_fcs_err_frms;
	uint64_t rmac_drop_frms;
	uint32_t rmac_vld_mcst_frms;
	uint32_t rmac_vld_bcst_frms;
	uint32_t rmac_in_rng_len_err_frms;
	uint32_t rmac_out_rng_len_err_frms;
	uint64_t rmac_long_frms;
	uint64_t rmac_pause_ctrl_frms;
	uint64_t rmac_unsup_ctrl_frms;
	uint32_t rmac_ttl_octets;
	uint32_t rmac_accepted_ucst_frms;
	uint32_t rmac_accepted_nucst_frms;
	uint32_t rmac_discarded_frms;
	uint32_t rmac_drop_events;
	uint32_t reserved_1;
	uint64_t rmac_ttl_less_fb_octets;
	uint64_t rmac_ttl_frms;
	uint64_t reserved_2;
	uint32_t reserved_3;
	uint32_t rmac_usized_frms;
	uint32_t rmac_osized_frms;
	uint32_t rmac_frag_frms;
	uint32_t rmac_jabber_frms;
	uint32_t reserved_4;
	uint64_t rmac_ttl_64_frms;
	uint64_t rmac_ttl_65_127_frms;
	uint64_t reserved_5;
	uint64_t rmac_ttl_128_255_frms;
	uint64_t rmac_ttl_256_511_frms;
	uint64_t reserved_6;
	uint64_t rmac_ttl_512_1023_frms;
	uint64_t rmac_ttl_1024_1518_frms;
	uint32_t reserved_7;
	uint32_t rmac_ip;
	uint64_t rmac_ip_octets;
	uint32_t rmac_hdr_err_ip;
	uint32_t rmac_drop_ip;
	uint32_t rmac_icmp;
	uint32_t reserved_8;
	uint64_t rmac_tcp;
	uint32_t rmac_udp;
	uint32_t rmac_err_drp_udp;
	uint64_t rmac_xgmii_err_sym;
	uint64_t rmac_frms_q0;
	uint64_t rmac_frms_q1;
	uint64_t rmac_frms_q2;
	uint64_t rmac_frms_q3;
	uint64_t rmac_frms_q4;
	uint64_t rmac_frms_q5;
	uint64_t rmac_frms_q6;
	uint64_t rmac_frms_q7;
	uint16_t rmac_full_q0;
	uint16_t rmac_full_q1;
	uint16_t rmac_full_q2;
	uint16_t rmac_full_q3;
	uint16_t rmac_full_q4;
	uint16_t rmac_full_q5;
	uint16_t rmac_full_q6;
	uint16_t rmac_full_q7;
	uint32_t rmac_pause_cnt;
	uint32_t reserved_9;
	uint64_t rmac_xgmii_data_err_cnt;
	uint64_t rmac_xgmii_ctrl_err_cnt;
	uint32_t rmac_accepted_ip;
	uint32_t rmac_err_tcp;
        
        /* PCI/PCI-X Read transaction statistics. */
	uint32_t rd_req_cnt;
	uint32_t new_rd_req_cnt;
	uint32_t new_rd_req_rtry_cnt;
	uint32_t rd_rtry_cnt;
	uint32_t wr_rtry_rd_ack_cnt;

        /* PCI/PCI-X write transaction statistics. */
	uint32_t wr_req_cnt;
	uint32_t new_wr_req_cnt;
	uint32_t new_wr_req_rtry_cnt;
	uint32_t wr_rtry_cnt;
	uint32_t wr_disc_cnt;
	uint32_t rd_rtry_wr_ack_cnt;

        /* DMA Transaction statistics. */
	uint32_t txp_wr_cnt;
	uint32_t txd_rd_cnt;
	uint32_t txd_wr_cnt;
	uint32_t rxd_rd_cnt;
	uint32_t rxd_wr_cnt;
	uint32_t txf_rd_cnt;
	uint32_t rxf_wr_cnt;

        /* CHANNEL STATISTICS */
        uint32_t out_of_dtrs_cnt;
        uint32_t reserve_free_swaps_cnt;
        uint32_t avg_compl_per_intr_cnt;
        uint32_t total_compl_cnt;
        uint32_t total_posts;
        uint32_t total_posts_many;
        uint32_t total_buffers;
        uint32_t avg_buffers_per_post;
        uint32_t avg_buffer_size;
        uint32_t avg_post_size;
        uint32_t ring_bump_cnt;     

        /* DEVICE ERROR STATISTICS */                
        uint32_t ecc_err_cnt;
        uint32_t parity_err_cnt;
        uint32_t serr_cnt;
        /* uint32_t * rxd_t_code_err_cnt;*/
        /* uint32_t * txd_t_code_err_cnt;*/

        /* Per Device Stats */
        uint32_t not_traffic_intr_cnt;
        uint32_t traffic_intr_cnt;
        uint32_t total_intr_cnt;
        uint32_t soft_reset_cnt;        

        /* Large Receive Statistics */
        uint32_t rx_tcpaggr_maxpkt;      /* Maximum large receive pkts      */
        uint64_t rx_tcpaggr;             /* # of large receive packets      */
        uint64_t rx_tcpaggr_pktcount;    /* # of RX TCP packets aggregated  */
                                         /* into large receive packets      */
        uint64_t rx_tcpaggr_bytecount;   /* # of RX TCP payload bytes       */
                                         /* Aggregated into large receive   */
                                         /* packets                         */
        /* Reserved stats */
        /* These reserved fields are in place to enable adding 
         * additional information in the future without impacting
         * any external applications which may reference this file
         */
         uint64_t reserved_s0;   
         uint64_t reserved_s1;   
         uint64_t reserved_s2;   
         uint64_t reserved_s3;   
         uint32_t reserved_s4;   
};
typedef struct kngent_stats kngent_stats_t;

/* bitmaps for functions flag in kngent_stats above */
#define	TXFLOW		(0x1)
#define RXFLOW		(0x2)
#define	JUMBOF		(0x4)
#define TCPSEG		(0x8)
#define LARGE_RECEIVE	(0x10)

struct kngent_all_stats {
	struct ndd_genstats ent_ndd_stats;	/* network generic stats     */
	struct ent_genstats ent_gen_stats;	/* ethernet generic stats    */
	struct kngent_stats  kngent_stats;	/* device specific stats     */
};
typedef struct kngent_all_stats kngent_all_stats_t;

/* trace hook numbers */
#define HKWD_KNGENT_XMIT		0x598	        /* transmit ekngents	     */
#define	HKWD_KNGENT_RECV		0x599	        /* receive ekngents            */
#define HKWD_KNGENT_OTHER		0x59A	        /* other ekngents              */

/* performance tuning settings */
#define KNGENT_RF_RX_FIFO		48		/* FIFO allocation (48% RX, 52% TX) */
#define KNGENT_RF_FCRTL		204800          /* Flow ctrl rcv threshold High reg */
#define KNGENT_RF_FCRTH		251904          /* Flow ctrl rcv threshold low reg  */
#define KNGENT_JF_RX_FIFO		40              /* FIFO allocation (40% RX, 60% TX) */
#define KNGENT_JF_FCRTL		204800          /* Flow ctrl rcv threshold High reg */
#define KNGENT_JF_FCRTH		251904          /* Flow ctrl rcv threshold low reg  */

#endif	/* _H_CDLI_ENTUSER_KNGENT */
