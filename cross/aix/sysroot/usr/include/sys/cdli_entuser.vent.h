/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/cdli_entuser.vent.h 1.5                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2004               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)88       1.5  src/bos/kernel/sys/cdli_entuser.vent.h, pcivent, bos530 6/10/04 17:07:40 */
/*
 * COMPONENT_NAME: pcivent
 *
 * FUNCTIONS: none.
 */


#ifndef _H_CDLI_ENTUSER_VENT
#define _H_CDLI_ENTUSER_VENT

/* device_type field in vent_stats_t holds one of the following values */
#define ENT_VENT_LR_PCIX	0x00000017 /* IBM 10 Gigabit-LR Ethernet     */
#define ENT_VENT_SR_PCIX	0x00000018 /* IBM 10 Gigabit-SR Ethernet     */

/* Miscellaneous definitions */
#define ENT_VENT_JUMBO_MAX_MTU	  9014     /* jumbo packet max data size     */

/* device specific statistics.                                               */
/* We can NOT use LINK_UP & LINK_DOWN ../include/sys/cdli_entuser.ethchan.h  */
/* includes ../include/sys/cdli_entuser.phxent.h and ../cdli_entuser.phxent.h*/
/* redefine LINK_UP & LINK_DOWN (poorly reading from ..phxent.h              */
#define VENT_LINK_DOWN			0  /* Link is DOWN 		     */
#define VENT_LINK_UP			1  /* Link is UP                     */
#define VENT_LINK_RESET			2  /* Link is being RESET            */

#define VENT_MAX_FILES_ENTRIES		10
#define VENT_FILE_NAME_LEN		20
#define VENT_FILE_REVISION_LEN		20
struct vent_file_revision {
	char	filename[VENT_FILE_NAME_LEN];
	char	revision[VENT_FILE_REVISION_LEN];
};
typedef struct vent_file_revision vent_file_revision_t;

struct vent_revisions {
	uint	entries;		   /* no. entries in the table       */
	vent_file_revision_t files[VENT_MAX_FILES_ENTRIES]; 
};
typedef struct vent_revisions vent_revision_t;

struct vent_stats {
	uint	tx_tcpseg;		   /* # of TCP segmentation offload  */
					   /* packets                        */
	uint	tx_tcpseg_err;		   /* # of TCP segmentation errors   */
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
	vent_revision_t revision_tbl;      /* Revision of all 'c' files      */
	uint    recvdmt_lsw;		/* lsw of receive descriptor thresh count */
	uint    recvdmt_msw;		/* msw of receive descriptor thresh count */
};
typedef struct vent_stats vent_stats_t;

/* bitmaps for functions flag in vent_stats above */
#define	TXFLOW		(0x1)
#define RXFLOW		(0x2)
#define	JUMBOF		(0x4)
#define TCPSEG		(0x8)

struct vent_all_stats {
	struct ndd_genstats ent_ndd_stats;	/* network generic stats     */
	struct ent_genstats ent_gen_stats;	/* ethernet generic stats    */
	struct vent_stats  vent_stats;	/* device specific stats     */
};
typedef struct vent_all_stats vent_all_stats_t;

/* trace hook numbers */
#define HKWD_VENT_XMIT		0x598	        /* transmit events	     */
#define	HKWD_VENT_RECV		0x599	        /* receive events            */
#define HKWD_VENT_OTHER		0x59A	        /* other events              */

/* performance tuning settings */
#define VENT_RF_RX_FIFO		48		/* FIFO allocation (48% RX, 52% TX) */
#define VENT_RF_FCRTL		204800          /* Flow ctrl rcv threshold High reg */
#define VENT_RF_FCRTH		251904          /* Flow ctrl rcv threshold low reg  */
#define VENT_JF_RX_FIFO		40              /* FIFO allocation (40% RX, 60% TX) */
#define VENT_JF_FCRTL		204800          /* Flow ctrl rcv threshold High reg */
#define VENT_JF_FCRTH		251904          /* Flow ctrl rcv threshold low reg  */

#endif	/* _H_CDLI_ENTUSER_VENT */
