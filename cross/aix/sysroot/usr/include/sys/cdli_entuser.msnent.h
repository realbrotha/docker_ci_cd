/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/cdli_entuser.msnent.h 1.5                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2009                   */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)83        1.5  src/bos/kernel/sys/cdli_entuser.msnent.h, pcimsnent, bos53X, x2009_37A5 9/9/09 14:55:51 */
/*                                */
/* COMPONENT : pcimsnent          */
/*                                */
/**************************************************************************/
/*                                                                        */
/*       QLogic 10GbE PCIe FCoCEE Adapter Ethernet Device Driver          */
/*                                                                        */
/**************************************************************************/

#ifndef _H_CDLI_ENTUSER_MSNENT
#define _H_CDLI_ENTUSER_MSNENT

/* device_type field in msnent_stats_t holds one of the following values.
 * the values you define depend on the device(s) your driver will support. 
 */
#define ENT_MSNENT_PCI_10G_SR    0x00000001    /* 10Gb SR PCIe Adapter           */
#define ENT_MSNENT_PCI_10G_LR    0x00000002    /* 10Gb LR PCIe Adapter           */
#define ENT_MSNENT_PCI_10G_MN    0x00000003    /* 10Gb Blade PCIe Adapter        */

/* Miscellaneous definitions */
#define MSNENT_JUMBO_MAX_MTU    (9014)         /* jumbo packet max data size     */

/* device specific statistics */
#ifndef LINK_UP
#define LINK_UP		 (1)		   /* Link is UP                      */
#define LINK_DOWN	 (0)		   /* Link is DOWN 		      */
#define LINK_RESET	 (2)		   /* Link is being RESET             */
#define MEDIA_10_HALF	 (0)		   /* 10 Mbps Half Duplex             */
#define MEDIA_10_FULL	 (1)		   /* 10 Mbps Full Duplex             */
#define MEDIA_100_HALF	 (2)		   /* 100 Mbps Half Duplex            */
#define MEDIA_100_FULL	 (3)		   /* 100 Mbps Full Duplex            */
#define MEDIA_1000_FULL	 (4)		   /* 1000 Mbps Full Duplex           */
#define MEDIA_10000_FULL (5)		   /* 10 Gbps Full Duplex             */
#define MEDIA_AUTO	 (6)		   /* Autonegotiation                 */
#endif

struct msnent_dcbx_cblk {
    uint32_t hw_cfg_flags;                 /* Hardware config and flags     */
    uint32_t tlv_pg;                       /* priority group TLV            */
    uint16_t pg_flags;                     /* Priority group flags          */
    uint16_t pgid_03;                      /* Priority group Ids: pri 0-3   */
    uint16_t pgid_47;                      /* Priority group Ids: pri 4-7   */
    uint16_t pgbw_01;                      /* Bandwith percent for Ids 0, 1 */
    uint16_t pgbw_23;                      /* Bandwith percent for Ids 2, 3 */
    uint16_t pgbw_45;                      /* Bandwith percent for Ids 4, 5 */
    uint16_t pgbw_67;                      /* Bandwith percent for Ids 6, 7 */
    uint16_t pg_num_tc;                    /* Number of traffic classes     */
    uint32_t tlv_pfc;                      /* PFC TLV                       */
    uint32_t pfc_flags;                    /* PFC Flags                     */
    uint32_t tlv_app;                      /* Application protocol TLV      */
    uint16_t app_flags;                    /* Application protocol flags    */
    uint16_t app_prot_id;                  /* Application protocol Id       */
    uint32_t oui_fc_map;                   /* App proto OUI and user map    */
    uint32_t rsvd[5];
};
typedef struct msnent_dcbx_cblk msnent_dcbx_cblk_t;

struct msnent_ls_info {
    uint32_t cause;                        /* Link down cause                */
    uint32_t hw_cfg;                       /* hardware configuration         */
    uint32_t dcbx_frc;                     /* DCBX frame count               */
    uint32_t chng_ct;                      /* # of times cfg changes occured */
}; 
typedef struct msnent_ls_info msnent_ls_info_t;

struct msnent_stats {
	uint32_t link_status;		/* negotiated link status             */
	uint32_t speed_selected;	/* speed/mode selected by user        */
	uint32_t speed_negotiated;	/* speed/mode negotiated by card      */
	uint32_t device_type;		/* Device type to display (LR/SR/etc) */
					/* or Fiber adapter statistics        */
	uint32_t functions;		/* TXFLOW/RXFLOW/JUMBOF/TCPSEG        */

        /* Standard pause mode counters */
        uint32_t rx_pause_lo;		/* # of Pause packets received        */
        uint32_t rx_pause_hi;		/* # of Pause packets received        */
        uint32_t tx_pause_lo;		/* # of Pause packets sent            */
        uint32_t tx_pause_hi;		/* # of Pause packets sent            */

        /* CBFC pause mode counters     */
        uint32_t rx_ppri0_lo;		/* # of Pause packets recvd at pri 0  */
        uint32_t rx_ppri0_hi;		/* # of Pause packets recvd at pri 0  */
        uint32_t rx_ppri1_lo;		/* # of Pause packets recvd at pri 1  */
        uint32_t rx_ppri1_hi;		/* # of Pause packets recvd at pri 1  */
        uint32_t rx_ppri2_lo;		/* # of Pause packets recvd at pri 2  */
        uint32_t rx_ppri2_hi;		/* # of Pause packets recvd at pri 2  */
        uint32_t rx_ppri3_lo;		/* # of Pause packets recvd at pri 3  */
        uint32_t rx_ppri3_hi;		/* # of Pause packets recvd at pri 3  */
        uint32_t rx_ppri4_lo;		/* # of Pause packets recvd at pri 4  */
        uint32_t rx_ppri4_hi;		/* # of Pause packets recvd at pri 4  */
        uint32_t rx_ppri5_lo;		/* # of Pause packets recvd at pri 5  */
        uint32_t rx_ppri5_hi;		/* # of Pause packets recvd at pri 5  */
        uint32_t rx_ppri6_lo;		/* # of Pause packets recvd at pri 6  */
        uint32_t rx_ppri6_hi;		/* # of Pause packets recvd at pri 6  */
        uint32_t rx_ppri7_lo;		/* # of Pause packets recvd at pri 7  */
        uint32_t rx_ppri7_hi;		/* # of Pause packets recvd at pri 7  */

        uint32_t tx_ppri0_lo;		/* # of Pause packets sent at pri 0  */
        uint32_t tx_ppri0_hi;		/* # of Pause packets sent at pri 0  */
        uint32_t tx_ppri1_lo;		/* # of Pause packets sent at pri 1  */
        uint32_t tx_ppri1_hi;		/* # of Pause packets sent at pri 1  */
        uint32_t tx_ppri2_lo;		/* # of Pause packets sent at pri 2  */
        uint32_t tx_ppri2_hi;		/* # of Pause packets sent at pri 2  */
        uint32_t tx_ppri3_lo;		/* # of Pause packets sent at pri 3  */
        uint32_t tx_ppri3_hi;		/* # of Pause packets sent at pri 3  */
        uint32_t tx_ppri4_lo;		/* # of Pause packets sent at pri 4  */
        uint32_t tx_ppri4_hi;		/* # of Pause packets sent at pri 4  */
        uint32_t tx_ppri5_lo;		/* # of Pause packets sent at pri 5  */
        uint32_t tx_ppri5_hi;		/* # of Pause packets sent at pri 5  */
        uint32_t tx_ppri6_lo;		/* # of Pause packets sent at pri 6  */
        uint32_t tx_ppri6_hi;		/* # of Pause packets sent at pri 6  */
        uint32_t tx_ppri7_lo;		/* # of Pause packets sent at pri 7  */
        uint32_t tx_ppri7_hi;		/* # of Pause packets sent at pri 7  */

	uint32_t rx_xoff_thresh;	/* rx xoff ctrl FIFO threshhold       */
	uint32_t rx_xon_thresh;	        /* rx xon ctrl FIFO threshhold        */
        uint32_t pcie_mode;		/* PCIe LW/RO/TLP/MRR values          */
        uint32_t tx_tcpseg_maxsize;     /* maximum large send size	      */
        uint32_t rx_tcpaggr_maxpkt;	/* maximum large receive pkts	      */
	uint64_t tx_tcpseg;		/* # of large send offload packets    */
        uint64_t rx_tcpaggr;		/* # of large receive packets 	      */
        uint64_t rx_tcpaggr_pktcount;	/* # of RX TCP packets aggregated     *
					 * into large receive packets         */
        uint64_t rx_tcpaggr_bytecount;	/* # of RX TCP payload bytes          *
					 * aggregated into large receive      *
					 * packets                            */
        uint32_t rx_sbuf_cpool_fail;    /* sbuf cluster pool alloc failures   */
        uint32_t rx_lbuf_cpool_fail;    /* sbuf cluster pool alloc failures   */

        msnent_ls_info_t link_info;     /* MPI link status / SFP+ presence    */
        msnent_dcbx_cblk_t dcbx_info;   /* DCBX control block from MPI        */

        uint32_t priority_collisions;   /* DCBX priority collision counter    */

        uint32_t fw_ver;                /* MPI firmware version               */
        uint32_t fw_status;             /* MPI status                         */

	uint32_t fcoe_priority;         /* FCoE VLAN priority value           */

        uint32_t reserved[48];          /* reserved for future use. structure *
                                         * is padded to consume a total of    *
                                         * 128 32-bit words                   */
};
typedef struct msnent_stats msnent_stats_t;

/* bitmaps for functions field in msnent_stats above */
#define	TXFLOW		(0x1)
#define RXFLOW		(0x2)
#define	STDFLOW		(0x1)
#define PPFLOW		(0x2)
#define	JUMBOF		(0x4)
#define TCPSEG		(0x8)
#define TCPAGGR		(0x10)
#define DCBX            (0x20)

/* bitmaps for pcie_mode in msnent_stats above */
#define	MSNENT_PCIE_LW_MASK	(0x000003f0)
#define MSNENT_PCIE_LW_X1	(0x00000010)
#define MSNENT_PCIE_LW_X2	(0x00000020)
#define MSNENT_PCIE_LW_X4	(0x00000040)
#define MSNENT_PCIE_LW_X8	(0x00000080)
#define	MSNENT_PCIE_RO_MASK	(0x00100000)
#define	MSNENT_PCIE_RO_ON	(0x00100000)
#define	MSNENT_PCIE_TLP_MASK	(0x00e00000)
#define	MSNENT_PCIE_TLP_128	(0x00000000)
#define	MSNENT_PCIE_TLP_256	(0x00200000)
#define	MSNENT_PCIE_MRR_MASK	(0x70000000)
#define	MSNENT_PCIE_MRR_128	(0x00000000)
#define	MSNENT_PCIE_MRR_256	(0x10000000)
#define	MSNENT_PCIE_MRR_512	(0x20000000)
#define	MSNENT_PCIE_MRR_1024	(0x30000000)
#define	MSNENT_PCIE_MRR_2048	(0x40000000)
#define	MSNENT_PCIE_MRR_4096	(0x50000000)
#define	MSNENT_PCIE_LSPD_MASK	(0x00000007)
#define	MSNENT_PCIE_LSPD_25	(0x00000001)
#define	MSNENT_PCIE_LSPD_50	(0x00000002)
#define	MSNENT_PCIE_MPS_MASK	(0x00E00000)
#define	MSNENT_PCIE_MPS_128	(0x00000000)
#define	MSNENT_PCIE_MPS_256	(0x00200000)
#define	MSNENT_PCIE_MPS_512	(0x00400000)
#define	MSNENT_PCIE_MPS_1024	(0x00600000)


struct msnent_all_stats {
	ndd_genstats_t ent_ndd_stats;	/* network generic stats     */
	ent_genstats_t ent_gen_stats;	/* ethernet generic stats    */
	msnent_stats_t msnent_stats;	/* device specific stats     */
};
typedef struct msnent_all_stats msnent_all_stats_t;

/* sample TX/RX FIFO and flow control settings for a sample adapter */
#define MSNENT_RF_RX_FIFO        32768	/* RX FIFO size, non-jumbo mode (RF) */
#define MSNENT_RF_TX_FIFO        32768	/* TX FIFO size, non-jumbo mode (RF) */
#define MSNENT_JF_RX_FIFO        49152	/* RX FIFO size, jumbo mode (JF)     */
#define MSNENT_JF_TX_FIFO        16384	/* TX FIFO size, jumbo mode (JF)     */
#define MSNENT_RF_RX_XOFF_THRESH 16384	/* RX RF flow control XOFF threshhold*/
#define MSNENT_JF_RX_XOFF_THRESH 24576	/* RX JF flow control XOFF threshhold*/
#define MSNENT_RF_RX_XON_THRESH  8192	/* RX RF flow control XON threshhold */
#define MSNENT_JF_RX_XON_THRESH  8192	/* RX JF flow control XON threshhold */

/* trace hook numbers */
#define HKWD_MSNENT_XMIT		0x63D 	/* transmit events	     */
#define	HKWD_MSNENT_RECV		0x63E   /* receive events            */
#define HKWD_MSNENT_OTHER		0x63F	/* other events              */


#endif	/* _H_CDLI_ENTUSER_MSNENT */
