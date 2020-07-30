/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/cdli_entuser.elxent.h 1.5.1.1                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2010,2011              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* Copyright © 2010 Emulex. All rights reserved.                          */


#ifndef _H_CDLI_ENTUSER_ELXENT
#define _H_CDLI_ENTUSER_ELXENT

#define ELXENT_PCIE_10G_SR              0x00000001    /* 10G SR           */
#define ELXENT_PCIE_10G_SFP_COP         0x00000002    /* 10G SFP-COPPER   */
#define ELXENT_PCIE_10G_MEZZ            0x00000003    /* 10G 4-port Mezz  */
#define ELXENT_PCIE_10G_SR_OPTICAL      0x00000004    /* 10G SR-OPTICAL   */
#define ELXENT_PCIE_10G_SFP_PLUS_COP    0x00000005    /* 10G SFP+COPPER   */
#define ELXENT_PCIE_1G_BASE_TX          0x00000006    /* 1G  Base-TX      */

/* Miscellaneous definitions */
#define ENT_ELX_JUMBO_MAX_MTU    (9014)        /* jumbo packet max data size  */

/* device specific statistics */
#ifndef LINK_UP
#define LINK_UP             (1)   /* Link is UP                               */
#define LINK_DOWN           (0)   /* Link is DOWN 		              */
#define LINKDOWN_LOCAL      (1)   /* Reason for Link Down                     */
#define LINKDOWN_REMOTE     (2)   /* Reason for Link Down                     */
#define LINKDOWN_UNKNOWN    (0)   /* Reason for Link Down                     */

#define LINK_RESET          (2)   /* Link is being RESET                      */
#define MEDIA_10_HALF       (0)   /* 10 Mbps Half Duplex                      */
#define MEDIA_10_FULL       (1)   /* 10 Mbps Full Duplex                      */
#define MEDIA_100_HALF      (2)   /* 100 Mbps Half Duplex                     */
#define MEDIA_100_FULL      (3)   /* 100 Mbps Full Duplex                     */
#define MEDIA_1000_FULL     (4)   /* 1000 Mbps Full Duplex                    */
#define MEDIA_10000_FULL    (5)   /* 10 Gbps Full Duplex                      */
#define MEDIA_AUTO          (6)   /* Autonegotiation                          */
#endif

/* per Receive Queue (RXQ) statistics                                         */
typedef struct elxent_rxq_stats {
    uint64_t rxq_tcpaggr;           /* # of large receive packets             */
    uint64_t rxq_tcpaggr_pktcount;  /* # of RX TCP packets aggregated into    *
                                     * large receive packets                  */
    uint64_t rxq_tcpaggr_bytecount; /* # of RX TCP payload bytes aggregated   *
                                    * aggregated into large receive packets   */
    uint64_t rxq_sys_mbufs;         /* # of system mbufs allocated for receive*/
    uint64_t rxq_eq_empty;          /* # of interrupts where EQ was empty     */
    uint64_t rxq_recv_intrs;        /* # of receive interrupts                */
    uint64_t rxq_ipackets;          /* # of receive packets                   */
    uint64_t rxq_ibytes;            /* # of receive bytes                     */
    uint32_t rxq_ipackets_drop;     /* # of receive packets dropped           */
    uint32_t rxq_no_mbufs;          /* # of mbuf allocation failures          */
    uint32_t rxq_no_fragments;      /* # of no fragment errors                */
    uint32_t rxq_limit;             /* # of times rx_limit was reached        */
    uint32_t rxq_tcpaggr_maxpkt;    /* maximum large receive packets          */
    uint32_t reserved[32];          /* reserved for future use                */
}elxent_rxq_stats_t;

/* per Transmit Queue (TXQ) statistics                                        */
typedef struct elxent_txq_stats {
    uint64_t txq_ifOutUcastPkts;    /* # of transmit unicast packets          */
    uint64_t txq_ifOutMcastPkts;    /* # of transmit multicast packets        */
    uint64_t txq_ifOutBcastPkts;    /* # of transmit broadcast packets        */
    uint64_t txq_opackets;          /* # of transmit packets                  */
    uint64_t txq_obytes;            /* # of transmit bytes                    */
    uint64_t txq_tcpseg_pkts;       /* # of transmit TCP segmentation packets */
    uint32_t txq_opackets_drop;     /* # of transmit packets dropped          */
    uint32_t txq_xmitque_ovf;       /* # of transmit queue overflows          */
    uint32_t txq_xmitque_max;       /* maximum # of tranmit queue entries     */
    uint32_t txq_tcpseg_maxpkt;     /* maximum TCP segmentation packet size   */
    uint32_t reserved[32];         /* reserved for future use                 */
}elxent_txq_stats_t;

/* per port statistics                                                        */
struct elxent_stats {
    uint64_t xofftxc;              /* # of XOFF packets transmitted           */
    uint64_t xontxc;               /* # of XON packets transmitted            */
    uint64_t xoffrxc;              /* # of XOFF packets received              */
    uint64_t xonrxc;               /* # of XON packets received               */
    uint32_t dev_type;             /* adapter type                            */
    uint32_t link_status;          /* negotiated link status                  */
    uint32_t media_speed;          /* link media speed                        */
    uint32_t pcie_mode;            /* PCIe LW/RO/TLP/MRR values               */
    uint32_t driver_mode;          /* current driver settings                 */
    uint32_t num_rx_queues;        /* # of RX queues currently configured     */
    uint32_t num_tx_queues;        /* # of TX queues currently configured     */
    uint32_t reason_4_linkdown;    /* reason for link down event              */
    elxent_txq_stats_t txq[5];     /* array of per TXQ statistics structs     */
    elxent_rxq_stats_t rxq[5];     /* array of per RXQ statistics structs     */
    uint32_t reserved[32];         /* reserved for future use                 */
};
typedef struct elxent_stats elxent_stats_t;

struct elxent_all_stats {
    ndd_genstats_t ent_ndd_stats;  /* network generic stats                   */
    ent_genstats_t ent_gen_stats;  /* ethernet generic stats                  */
    elxent_stats_t elxent_stats;   /* device specific stats                   */
};
typedef struct elxent_all_stats elxent_all_stats_t;

/* bitmaps for driver_mode in elxent_stats above */
#define ELXENT_MODE_LSO            (0x00000001)
#define ELXENT_MODE_LRO            (0x00000002)
#define ELXENT_MODE_JUMBO          (0x00000004)
#define ELXENT_MODE_FLOW           (0x00000008)

/* bitmaps for pcie_mode in elxent_stats above */
#define ELXENT_PCIE_LINKSPEED_MASK (0x0000000F)
#define ELXENT_PCIE_LINKSPEED_GEN1 (0x00000001)
#define ELXENT_PCIE_LINKSPEED_GEN2 (0x00000002)
#define ELXENT_PCIE_LW_MASK        (0x000003F0)
#define ELXENT_PCIE_LW_X1          (0x00000010)
#define ELXENT_PCIE_LW_X2          (0x00000020)
#define ELXENT_PCIE_LW_X4          (0x00000040)
#define ELXENT_PCIE_LW_X8          (0x00000080)
#define ELXENT_PCIE_LW_X12         (0x000000C0)
#define ELXENT_PCIE_LW_X16         (0x00000100)
#define ELXENT_PCIE_LW_X32         (0x00000200)
#define ELXENT_PCIE_RO_MASK        (0x00100000)
#define ELXENT_PCIE_RO_ON          (0x00100000)
#define ELXENT_PCIE_TLP_MASK       (0x00E00000)
#define ELXENT_PCIE_TLP_128        (0x00000000)
#define ELXENT_PCIE_TLP_256        (0x00200000)
#define ELXENT_PCIE_TLP_512        (0x00400000)
#define ELXENT_PCIE_TLP_1024       (0x00600000)
#define ELXENT_PCIE_TLP_2048       (0x00800000)
#define ELXENT_PCIE_TLP_4096       (0x00A00000)
#define ELXENT_PCIE_MRR_MASK       (0x70000000)
#define ELXENT_PCIE_MRR_128        (0x00000000)
#define ELXENT_PCIE_MRR_256        (0x10000000)
#define ELXENT_PCIE_MRR_512        (0x20000000)
#define ELXENT_PCIE_MRR_1024       (0x30000000)
#define ELXENT_PCIE_MRR_2048       (0x40000000)
#define ELXENT_PCIE_MRR_4096       (0x50000000)

/* trace hook numbers (assigned by IBM) */
#define HKWD_ELXENT_XMIT            0x65D00000   /* transmit events           */
#define HKWD_ELXENT_RECV            0x65E00000   /* receive events            */
#define HKWD_ELXENT_OTHER           0x65F00000   /* other events              */

#endif  /* _H_CDLI_ENTUSER_ELXENT */
