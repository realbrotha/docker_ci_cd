/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/cdli_entuser.nment.h 1.6                     */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2010                   */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)09       1.6  src/bos/kernel/sys/cdli_entuser.nment.h, pcinment, bos53X, x2011_14A2 9/15/10 15:04:52 */

#ifndef _H_CDLI_ENTUSER_NMENT
#define _H_CDLI_ENTUSER_NMENT

/* device_type field in nment_stats_t holds one of the following values */
#define ENT_NMENT_PCI_TX	0x00000013 /* IBM 10/100/1000 Base-TX PCI-X  *
					    * Adapter                        */
#define ENT_NMENT_PCI_SX	0x00000014 /* IBM Gigabit Ethernet-SX PCI-X  *
					    * Adapter                        */
#define ENT_COMBO_PCI_TX        0x00000015 /* Qlogic 8G FC adapter with 
                                              Gigabit ethernet               */
#define ENT_MINNOW_PCI_TX       0x00000016 /* Minnow 2-port Gigabit ethernet 
                                              adapter */
#define ENT_FALCON_PCI_TX       0x00000017 /* Falcon 2-port Gigabit ethernet 
                                              adapter */
                                             

#define	NDD_NMENT_LINK_DOWN	(32*NDD_SPECFLAGS) /* link is down */
#define	NDD_NMENT_AUTO_NEG	(64*NDD_SPECFLAGS) /* establish(ed) link by */
						   /* on: autonegotiate link */
						   /* off: force gigabit and */
					           /* full duplex */
/* Miscellaneous definitions */
#define ENT_GO_JUMBO_MAX_MTU    (9014)     /* jumbo packet max data size     */

/* device specific statistics */
#ifndef LINK_UP
#define LINK_UP		(1)		   /* Link is UP                     */
#define LINK_DOWN	(0)		   /* Link is DOWN 		     */
#define LINK_RESET	(2)		   /* Link is being RESET            */
#endif

struct nment_stats {
        uint64_t tx_tcpseg;		   /* # of TCP segmentation offload  *
					    * packets                        */
	uint	tx_tcpseg_err;		   /* # of TCP segmentation errors   */
	uint    link_status;               /* negotiated link status         */
	uint	speed_selected;		   /* speed/mode selected by user    */

#define	NDD_NMENT_LNK_UP	    	0x80000000  /* link is operational    */
#define NDD_NMENT_LNK_ENABLE	    	0x40000000  /* enable link */
#define NDD_NMENT_LNK_NEGOTIATE	    	0x20000000  /* enable autonegotiation */
#define NDD_NMENT_LNK_RX_FLOW_CTL_Y 	0x00800000  /* do RX flow control */
#define NDD_NMENT_LNK_TX_FLOW_CTL_Y 	0x00200000  /* do TX flow control */
#define NDD_NMENT_LNK_HALF_DUPLEX   	0x00100000  /* half duplex */
#define NDD_NMENT_LNK_FULL_DUPLEX   	0x00080000  /* full duplex */
#define NDD_NMENT_LNK_1000MB	    	0x00040000  /* 1000 megabit data rate */
#define NDD_NMENT_LNK_100MB	    	0x00020000  /* 100 megabit data rate */
#define NDD_NMENT_LNK_10MB	    	0x00010000  /* 10 megabit data rate */

#ifndef	MEDIA_10_HALF
#define MEDIA_10_HALF			(0) 	/* 10 Mbps Half Duplex 	*/
#define MEDIA_10_FULL			(1)	/* 10 Mbps Full Duplex 	*/
#define MEDIA_100_HALF  		(2)	/* 100 Mbps Half Duplex */
#define MEDIA_100_FULL			(3) 	/* 100 Mbps Full Duplex */
#define MEDIA_AUTO			(4)	/* Autonegotiation 	*/
#define MEDIA_1000_FULL			(5) 	/* 1000 Mbps Full Duplex*/
#endif
	uint	link_negotiated;	   /* speed/mode negotiated by card  */
	uint	device_type;		   /* Device type to display UTP     *
					    * or Fiber adapter statistics    */
	uint	functions;		   /* TXFLOW/RXFLOW/JUMBOF/TCPSEG    */
        uint	xonrxc;			   /* # of XON packets received      */
        uint	xontxc;			   /* # of XON packets transmitted   */
        uint	xoffrxc;		   /* # of XOFF packets received     */
        uint	xofftxc;		   /* # of XOFF packets transmitted  */
	uint	fcrth;			   /* flow ctrl rx thresh high       */
	uint	fcrtl;			   /* flow ctrl rx thresh low        */
	uint    cache_line_size;           /* Cache line sz of PCI cfg space */
	uint    latency_timer;             /* Latency timer of PCI cfg space */
        uint    pcie_mode;                 /* PCIe LW/RO/TLP/MRR values      */
        uint32_t    rx_tcpaggr_maxpkt;     /* maximum large receive pkts     */
        uint64_t    rx_tcpaggr;            /* # of large receive packets     */
        uint64_t    rx_tcpaggr_pktcount;   /* # of RX TCP packets aggregated *
                                            * into large receive packets     */
        uint64_t    rx_tcpaggr_bytecount;  /* # of RX TCP payload bytes      *
                                            * aggregated into large receive  *
                                            * packets                        */

};
typedef struct nment_stats nment_stats_t;

/* bitmaps for functions flag in nment_stats above */
#define	TXFLOW		(0x1)
#define RXFLOW		(0x2)
#define	JUMBOF		(0x4)
#define TCPSEG		(0x8)
#define TCPAGGR         (0x10)

/* bitmaps for pcie_mode in goent_stats above */
#define	NMENT_PCIE_LW_MASK	(0x000003f0)
#define NMENT_PCIE_LW_X1	(0x00000010)
#define NMENT_PCIE_LW_X2	(0x00000020)
#define NMENT_PCIE_LW_X4	(0x00000040)
#define NMENT_PCIE_LW_X8	(0x00000080)
#define	NMENT_PCIE_RO_MASK	(0x00100000)
#define	NMENT_PCIE_RO_ON	(0x00100000)
#define	NMENT_PCIE_TLP_MASK	(0x00e00000)
#define	NMENT_PCIE_TLP_128	(0x00000000)
#define	NMENT_PCIE_TLP_256	(0x00200000)
#define	NMENT_PCIE_MRR_MASK	(0x70000000)
#define	NMENT_PCIE_MRR_128	(0x00000000)
#define	NMENT_PCIE_MRR_256	(0x10000000)
#define	NMENT_PCIE_MRR_512	(0x20000000)
#define	NMENT_PCIE_MRR_1024	(0x30000000)
#define	NMENT_PCIE_MRR_2048	(0x40000000)
#define	NMENT_PCIE_MRR_4096	(0x50000000)

struct nment_all_stats {
	struct ndd_genstats ent_ndd_stats;	/* network generic stats     */
	struct ent_genstats ent_gen_stats;	/* ethernet generic stats    */
	struct nment_stats  nment_stats;	/* device specific stats     */
};
typedef struct nment_all_stats nment_all_stats_t;

/* trace hook numbers */
#define HKWD_NMENT_XMIT		0x66000000	        /* transmit events	     */
#define	HKWD_NMENT_RECV		0x66100000 	        /* receive events            */
#define HKWD_NMENT_OTHER	0x66200000	        /* other events              */

#endif	/* _H_CDLI_ENTUSER_NMENT */
