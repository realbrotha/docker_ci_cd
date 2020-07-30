/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/cdli_entuser.kxent.h 1.3                     */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2007               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)72	1.1  src/bos/kernel/sys/cdli_entuser.kxent.h, pcikxent, bos53L 6/25/07 16:20:21 */
#ifndef _H_CDLI_ENTUSER_KXENT
#define _H_CDLI_ENTUSER_KXENT

/* device_type field in kxent_stats_t holds one of the following values */
#define ENT_KXENT_PCI_LR	0x00000011 /* IBM 10Gb LR PCIe Adapter       */
#define ENT_KXENT_PCI_SR	0x00000012 /* IBM 10Gb SR PCIe Adapter       */

/* Miscellaneous definitions */
#define ENT_KX_JUMBO_MAX_MTU    (9014)     /* jumbo packet max data size     */

/* device specific statistics */
#ifndef LINK_UP
#define LINK_UP		(1)		   /* Link is UP                     */
#define LINK_DOWN	(0)		   /* Link is DOWN 		     */
#define LINK_RESET	(2)		   /* Link is being RESET            */
#define MEDIA_10_HALF	(0)		   /* 10 Mbps Half Duplex            */
#define MEDIA_10_FULL	(1)		   /* 10 Mbps Full Duplex            */
#define MEDIA_100_HALF	(2)		   /* 100 Mbps Half Duplex           */
#define MEDIA_100_FULL	(3)		   /* 100 Mbps Full Duplex           */
#define MEDIA_AUTO	(4)		   /* Autonegotiation                */
#define MEDIA_1000_FULL	(5)		   /* 1000 Mbps Full Duplex          */
#define MEDIA_10000_FULL (6)		   /* 10 Gbps Full Duplex            */
#endif

struct kxent_stats {
	uint32_t    	link_status;               /* negotiated link status         */
	uint32_t	speed_selected;		   /* speed/mode selected by user    */
	uint32_t	speed_negotiated;	   /* speed/mode negotiated by card  */
	uint32_t	device_type;		   /* Device type to display UTP     *
					    	    * or Fiber adapter statistics    */
	uint32_t	functions;		   /* TXFLOW/RXFLOW/JUMBOF/TCPSEG    */
        uint32_t	xonrxc;			   /* # of XON packets received      */
        uint32_t	xontxc;			   /* # of XON packets transmitted   */
        uint32_t	xoffrxc;		   /* # of XOFF packets received     */
        uint32_t	xofftxc;		   /* # of XOFF packets transmitted  */
	uint32_t	fcrth;			   /* flow ctrl rx thresh high       */
	uint32_t	fcrtl;			   /* flow ctrl rx thresh low        */
        uint32_t    	pcie_mode;                 /* PCIe LW/RO/TLP/MRR values      */
        uint32_t	tx_tcpseg_maxsize;         /* maximum large send size        */
        uint32_t	rx_tcpaggr_maxpkt;         /* maximum large receive pkts     */
	uint64_t	tx_tcpseg;		   /* # of large send offload packets*/
        uint64_t	rx_tcpaggr;                /* # of large receive packets     */
        uint64_t	rx_tcpaggr_pktcount;       /* # of RX TCP packets aggregated *
                                                    * into large receive packets     */
        uint64_t	rx_tcpaggr_bytecount;      /* # of RX TCP payload bytes      *
                                                    * aggregated into large receive  *
                                                    * packets                        */
	uint64_t 	reserved[128];		   /* reserved for future use	     */
};
typedef struct kxent_stats kxent_stats_t;

/* bitmaps for functions flag in kxent_stats above */
#define	TXFLOW		(0x1)
#define RXFLOW		(0x2)
#define	JUMBOF		(0x4)
#define TCPSEG		(0x8)
#define TCPAGGR		(0x10)

/* bitmaps for pcie_mode in kxent_stats above */
#define	KXENT_PCIE_LW_MASK	(0x000003f0)
#define KXENT_PCIE_LW_X1	(0x00000010)
#define KXENT_PCIE_LW_X2	(0x00000020)
#define KXENT_PCIE_LW_X4	(0x00000040)
#define KXENT_PCIE_LW_X8	(0x00000080)
#define	KXENT_PCIE_RO_MASK	(0x00100000)
#define	KXENT_PCIE_RO_ON	(0x00100000)
#define	KXENT_PCIE_TLP_MASK	(0x00e00000)
#define	KXENT_PCIE_TLP_128	(0x00000000)
#define	KXENT_PCIE_TLP_256	(0x00200000)
#define	KXENT_PCIE_MRR_MASK	(0x70000000)
#define	KXENT_PCIE_MRR_128	(0x00000000)
#define	KXENT_PCIE_MRR_256	(0x10000000)
#define	KXENT_PCIE_MRR_512	(0x20000000)
#define	KXENT_PCIE_MRR_1024	(0x30000000)
#define	KXENT_PCIE_MRR_2048	(0x40000000)
#define	KXENT_PCIE_MRR_4096	(0x50000000)

struct kxent_all_stats {
	struct ndd_genstats ent_ndd_stats;	/* network generic stats     */
	struct ent_genstats ent_gen_stats;	/* ethernet generic stats    */
	struct kxent_stats  kxent_stats;	/* device specific stats     */
};
typedef struct kxent_all_stats kxent_all_stats_t;

/* performance tuning settings for PCI-E adapters */
#define KXENT_RXPBSIZE0         0x80000	/* Single 512KB RX Packet Buffer     */
#define KXENT_RF_FCRTL0         0x10000	/* RX RF flow control XON 64KB       */
#define KXENT_RF_FCRTH0         0x20000	/* RX RF flow control XOFF 128KB     */
#define KXENT_JF_FCRTL0         0x10000	/* RX JF flow control XON 64KB       */
#define KXENT_JF_FCRTH0         0x20000	/* RX JF flow control XOFF 128KB     */

/* trace hook numbers */
#define HKWD_KXENT_XMIT		0x5ED	        /* transmit events	     */
#define	HKWD_KXENT_RECV		0x5EE	        /* receive events            */
#define HKWD_KXENT_OTHER	0x5EF	        /* other events              */

#endif	/* _H_CDLI_ENTUSER_KXENT */
