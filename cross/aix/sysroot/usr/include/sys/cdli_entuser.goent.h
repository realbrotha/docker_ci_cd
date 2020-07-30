/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/cdli_entuser.goent.h 1.7.1.14                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2002,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)05       1.7.1.14  src/bos/kernel/sys/cdli_entuser.goent.h, pcigoent, bos53Q, q2008_08C4 1/18/08 01:52:01 */
#ifndef _H_CDLI_ENTUSER_GOENT
#define _H_CDLI_ENTUSER_GOENT

/* device_type field in goent_stats_t holds one of the following values */
#define ENT_GOENT_PCI_TX	0x00000013 /* IBM 10/100/1000 Base-TX PCI-X  *
					    * Adapter                        */
#define ENT_GOENT_PCI_SX	0x00000014 /* IBM Gigabit Ethernet-SX PCI-X  *
					    * Adapter                        */
#define ENT_DENT_PCI_TX		0x00000015 /* IBM 2-Port 10/100/1000 Base-TX *
					    * PCI-X Adapter 		     */ 
#define ENT_DENT_PCI_SX		0x00000016 /* IBM 2-Port Gigabit Ethernet-SX *
					    * PCI-X Adapter 		     */
#define ENT_CENT_PCI_TX         0x00000017 /* IBM 4-Port 10/100/1000 Base-TX *
                                            * PCI-X Adapter                  */
#define ENT_EPENT_PCI_TX        0x00000018 /* IBM 2-Port 10/100/1000 Base-TX *
                                            * PCI-E Adapter                  */
#define ENT_EPENT_PCI_SX        0x00000019 /* IBM 2-Port Gigabit Ethernet-SX *
                                            * PCI-E Adapter                  */
#define ENT_CLENT_PCI_TX        0x0000001A /* IBM 4-Port 10/100/1000 Base-TX *
                                            * PCI-E Adapter                  */

/* Miscellaneous definitions */
#define ENT_GO_JUMBO_MAX_MTU    (9014)     /* jumbo packet max data size     */

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
#endif

struct goent_stats {
	uint	tx_tcpseg;		   /* # of TCP segmentation offload  *
					    * packets                        */
	uint	tx_tcpseg_err;		   /* # of TCP segmentation errors   */
	uint    link_status;               /* negotiated link status         */
	uint	speed_selected;		   /* speed/mode selected by user    */
	uint	speed_negotiated;	   /* speed/mode negotiated by card  */
	uint	device_type;		   /* Device type to display UTP     *
					    * or Fiber adapter statistics    */
	uint	functions;		   /* TXFLOW/RXFLOW/JUMBOF/TCPSEG    */
        uint	xonrxc;			   /* # of XON packets received      */
        uint	xontxc;			   /* # of XON packets transmitted   */
        uint	xoffrxc;		   /* # of XOFF packets received     */
        uint	xofftxc;		   /* # of XOFF packets transmitted  */
        uint    pcix_mode;                 /* 1 if pci-x, 0 if pci           */
        uint    pcix_spd;                  /* pci-x bus speed                */
        uint    pci66;                     /* 1 if bus is 66Mhz, 0 if 33Mhz  */
        uint    bus64;                     /* 1 if bus is 64bit, 0 if 32bit  */
	uint	fcrth;			   /* flow ctrl rx thresh high       */
	uint	fcrtl;			   /* flow ctrl rx thresh low        */
	uint	rx_fifo;		   /* determines the rx/tx fifo split*/
	uint    cache_line_size;           /* Cache line sz of PCI cfg space */
	uint    latency_timer;             /* Latency timer of PCI cfg space */
        uint    pcie_mode;                 /* PCIe LW/RO/TLP/MRR values      */
};
typedef struct goent_stats goent_stats_t;

/* bitmaps for functions flag in goent_stats above */
#define	TXFLOW		(0x1)
#define RXFLOW		(0x2)
#define	JUMBOF		(0x4)
#define TCPSEG		(0x8)

/* bitmaps for pcie_mode in goent_stats above */
#define	GOENT_PCIE_LW_MASK	(0x000003f0)
#define GOENT_PCIE_LW_X1	(0x00000010)
#define GOENT_PCIE_LW_X2	(0x00000020)
#define GOENT_PCIE_LW_X4	(0x00000040)
#define	GOENT_PCIE_RO_MASK	(0x00100000)
#define	GOENT_PCIE_RO_ON	(0x00100000)
#define	GOENT_PCIE_TLP_MASK	(0x00e00000)
#define	GOENT_PCIE_TLP_128	(0x00000000)
#define	GOENT_PCIE_TLP_256	(0x00200000)
#define	GOENT_PCIE_MRR_MASK	(0x70000000)
#define	GOENT_PCIE_MRR_128	(0x00000000)
#define	GOENT_PCIE_MRR_256	(0x10000000)
#define	GOENT_PCIE_MRR_512	(0x20000000)
#define	GOENT_PCIE_MRR_1024	(0x30000000)
#define	GOENT_PCIE_MRR_2048	(0x40000000)
#define	GOENT_PCIE_MRR_4096	(0x50000000)

#define	JUMBOF		(0x4)
#define TCPSEG		(0x8)

struct goent_all_stats {
	struct ndd_genstats ent_ndd_stats;	/* network generic stats     */
	struct ent_genstats ent_gen_stats;	/* ethernet generic stats    */
	struct goent_stats  goent_stats;	/* device specific stats     */
};
typedef struct goent_all_stats goent_all_stats_t;

/* performance tuning settings for PCI-X adapters */
#define GOENT_RF_RX_FIFO        56	/* FIFO allocation (56KB RX, 8KB TX)*/
#define GOENT_RF_FCRTL          24576	/* RX flow control threshold low     */
#define GOENT_RF_FCRTH          49152	/* RX flow control threshold high    */
#define GOENT_JF_RX_FIFO        40	/* FIFO allocation (40KB RX, 24KB TX)*/
#define GOENT_JF_FCRTL          16384	/* RX flow control threshold low     */
#define GOENT_JF_FCRTH          24576	/* RX flow control threshold high    */

/* performance tuning settings for PCI-E adapters */
#define EPENT_RF_RX_FIFO        44	/* FIFO allocation (44KB RX, 4KB TX)*/
#define EPENT_RF_FCRTL          20480	/* RX flow control threshold low     */
#define EPENT_RF_FCRTH          40960	/* RX flow control threshold high    */
#define EPENT_JF_RX_FIFO        30	/* FIFO allocation (30KB RX, 18KB TX)*/
#define EPENT_JF_FCRTL          10240	/* RX flow control threshold low     */
#define EPENT_JF_FCRTH          18432	/* RX flow control threshold high    */

/* trace hook numbers */
#define HKWD_GOENT_XMIT		0x473	        /* transmit events	     */
#define	HKWD_GOENT_RECV		0x474	        /* receive events            */
#define HKWD_GOENT_OTHER	0x475	        /* other events              */

#endif	/* _H_CDLI_ENTUSER_GOENT */
