/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/cdli_entuser.hea.h 1.18                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2005,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)93	1.18  src/bos/kernel/sys/cdli_entuser.hea.h, gxhea, bos53Q, q2008_11B1 3/5/08 16:35:22 */






/*******************************************************************************
 *	COMPONENT NAME: hea
 *
 *      Host Ethernet Adapter (HEA) CDLI  Header File
 *
 ******************************************************************************/
#ifndef _H_CDLI_ENTUSER_HEA
#define _H_CDLI_ENTUSER_HEA

/*----------------------------------------------------------------------------*/
/*      HEA device specific ndd_flags bits                                    */
/*----------------------------------------------------------------------------*/
#define NDD_HEA_LPORT_DOWN      (16 * NDD_SPECFLAGS) /* logical port is down  */
#define NDD_HEA_PPORT_DOWN      (32 * NDD_SPECFLAGS) /* physical port is down */


/*----------------------------------------------------------------------------*/
/*      HEA Speed values as per Cat0/Cat4 hardware specifications             */
/*----------------------------------------------------------------------------*/
#define HEA_MEDIA_10_HALF	(1)	   /* 10 Mbps Half Duplex             */
#define HEA_MEDIA_10_FULL	(2)	   /* 10 Mbps Full Duplex             */
#define HEA_MEDIA_100_HALF	(3)	   /* 100 Mbps Half Duplex            */
#define HEA_MEDIA_100_FULL	(4)	   /* 100 Mbps Full Duplex            */
#define HEA_MEDIA_1000_FULL	(6)	   /* 1000 Mbps Full Duplex           */
#define HEA_MEDIA_10000_FULL	(8)	   /* 10000 Mbps Full Duplex          */
#define HEA_MEDIA_AUTO	        (0)	   /* Autonegotiation                 */

/*----------------------------------------------------------------------------*/
/*      HEA Coalescing Values                                                 */
/*----------------------------------------------------------------------------*/
#define HEA_MEDIA_COALESCE_NONE   0        /* No Interrupt Coalescing         */
#define HEA_MEDIA_COALESCE_1000   1        /* 1GbE Interrupt Coalescing       */
#define HEA_MEDIA_COALESCE_10000  2        /* 10GbE Interrupt Coalescing      */

/*----------------------------------------------------------------------------*/
/*      HEA Trace Hook Words                                                  */
/*----------------------------------------------------------------------------*/
#define HKWD_HEADD_XMT          0x5DF      /* Transmit Tracing                */
#define HKWD_HEADD_RCV          0x5E0      /* Receive Tracing                 */
#define HKWD_HEADD_GEN          0x5E1      /* General Tracing                 */


/*----------------------------------------------------------------------------*/
/*      HEA Maximum Multicore Scaling Value                                   */
/*----------------------------------------------------------------------------*/
#define MAX_MCS_NUM             16


/*----------------------------------------------------------------------------*/
/*  HEA extended statistics displayable through entstat -d ent#               */
/*----------------------------------------------------------------------------*/
typedef struct hea_stats {
        /*--------------------------------------------------------------------*/
        /*      Multi-Core Scaling specific stats                             */
        /*--------------------------------------------------------------------*/
        uint64_t RxIntr[MAX_MCS_NUM];     /* Number of RX adapter interrupts  */
        uint64_t RxIntrClsc[MAX_MCS_NUM]; /* Number of RX intr coalesces      */
        uint64_t RxIntrOfflv[MAX_MCS_NUM];/* Number of RX Offlevel intr calls */
        uint64_t RxIntrTimer[MAX_MCS_NUM];/* Number of RX Timer process calls */
        uint64_t RxQ1[MAX_MCS_NUM];       /* RQ1 packets - Low Latency        */
        uint64_t RxQ2[MAX_MCS_NUM];       /* RQ2 packets - Standard           */
        uint64_t RxQ3[MAX_MCS_NUM];       /* RQ3 packets - Jumbo              */
        uint64_t RxTcpAggrMaxPkt[MAX_MCS_NUM]; /* Max large receive pkts      */
	uint64_t RxTcpAggr[MAX_MCS_NUM];  /* # of large receive pkts          */
	uint64_t RxTcpAggrPktCnt[MAX_MCS_NUM];/*# of RX TCP pkts aggregated   */
 	uint64_t RxTcpAggrByteCnt[MAX_MCS_NUM];/* # of RX TCP payload bytes   *
					        * aggregated into large       *
					        * receive packets             */
        uint64_t TxF2[MAX_MCS_NUM];       /* Total Format2 descriptors        */
        uint64_t TxF3[MAX_MCS_NUM];       /* Total Format3 descriptors        */
        uint64_t TxISB[MAX_MCS_NUM];      /* Interface Specific Buff pkt count*/
        uint64_t TxNonISB[MAX_MCS_NUM];   /* Non-ISB paacket count            */
        uint64_t TxMaxWQE[MAX_MCS_NUM];   /* Max WQE per QP                   */
        uint64_t TxMaxMbufCnt[MAX_MCS_NUM];/* Max packet mbuf count           */
        uint64_t reserved_MCS[16];

        /*--------------------------------------------------------------------*/
        /*      Notification Event Statistics                                 */
        /*--------------------------------------------------------------------*/
        uint64_t hea_handle;            /* Logical HEA adapter handle         */
        uint64_t hea_port_no;           /* Logical Port Number                */
        uint64_t NEQ_ilevel;            /* NEQ interrupt level                */
        uint64_t NEQ_bid;               /* NEQ interrupt bus number           */
        uint64_t NEQ_icount;            /* NEQ interrupt count                */
        uint64_t reserved_NEQ[16];

        /*--------------------------------------------------------------------*/
        /*      Memory Migration Statistics                                   */
        /*--------------------------------------------------------------------*/
        uint64_t mm_pages;              /* Number of pages migrated           */
        uint64_t mm_start;              /* Timestamp of last migration        */
        uint64_t mm_end;                /* Timestamp of last migration        */
        uint64_t mm_reserved[16];

        /*--------------------------------------------------------------------*/
        /*      DDS derived attributes/stats                                  */
        /*--------------------------------------------------------------------*/
        uint8_t  large_send;            /* Large Send                         */
        uint8_t  tx_cksum;              /* TX Checksum offload                */
        uint8_t  rx_cksum;              /* RX Checksum offload                */
        uint8_t  jumbo_frames;          /* Jumbo frames                       */
        uint8_t  flow_ctrl;             /* Flow control                       */
        uint8_t  speed_selected;        /* Selected speed or LPAR mode        */
        uint8_t  TxF3Size;              /* Max TX immediate data size         */
        uint8_t  tx_isb;                /* Use TX Interface Spec buffers      */
        uint8_t  rx_clsc;               /* RX interrupt coalescing            */
        uint8_t  large_receive;         /* Large Receive                      */
        uint64_t promisc_qp;            /* Promiscuos QP number               */
        uint32_t device_type;  
        uint64_t reserved_attr[16];

        /*--------------------------------------------------------------------*/
        /*      Query HEA stats.                                              */
        /*--------------------------------------------------------------------*/
	uint32_t  CurrNumQP;		/* Current number of Queue Pairs      */
	uint32_t  CurrNumCQ;		/* Current number of Completion Queues*/
	uint32_t  CurrNumEQ;		/* Current number of Event Queues     */
	uint32_t  CurrNumMR;		/* Current number of Memory Regions   */
        uint32_t  r0;                   /* reserved - stored as binary zeros  */
	uint32_t  MaxNumQP;		/* Max Number of Queue Pairs	      */
	uint32_t  MaxNumCQ;		/* Max Number of Completion Queues    */
	uint32_t  MaxNumEQ;		/* Max Number of Event Queues	      */
	uint32_t  MaxNumMR;		/* Max Number of Memory Regions	      */
	uint32_t  r1;	                /* reserved - stored as binary zeros  */
	uint32_t  IntClockFreq;		/* Internal Clock Frequency in HZ     */
	uint32_t  MaxNumPD;		/* Max Number of Protection Domains   */
	uint32_t  MaxNumAddrHandle;	/* Max Number of Address Handles      */
	uint32_t  MaxCQEperCQ;		/* Max Number of CQEs per CQ	      */
	uint32_t  MaxNumWQE;		/* Max Number of WQEs for any Queue   */
	uint32_t  MaxDataSegRQ1WQE;	/* Max # scatter/gather element in RQ1*/
	uint32_t  MaxDataSegRQ2WQE;	/* Max # scatter/gather element in RQ2*/
	uint32_t  MaxDataSegRQ3WQE;	/* Max # scatter/gather element in RQ3*/
        uint32_t  MRsize32;             /* Access to the entire 32bit field   */
	uint32_t  r3;	                /* reserved - stored as binary zeros  */
	uint64_t  MaxMRsize;		/* Max Memory Region size	      */
	uint32_t  r4;	                /* reserved - stored as binary zeros  */
	uint32_t  NumberOfPorts;	/* # of ports (1<= N <= 2048)	      */
        uint32_t  r5;	                /* reserved - stored as binary zeros  */
        uint64_t  PxLy_RC_MASK;         /* Port-Receive-Control Mask (PxLy_RC)*/
	uint64_t  MaxMcastMACHEAport;	/* Max Mcast MAC reg per hea port     */
	uint64_t  CapIndicatorRes;	/* Specifies capabilities of HEA      */
	uint32_t  MaxNumISN_EQ;		/* Max # of ISNs per EQ/NEQ	      */
	uint32_t  MaxNumNEQ;		/* Max # of NEQ  supported	      */
	uint64_t  MaxVLANs;	        /* Max # of VLAN IDs per HEA port     */
	uint32_t  MaxNumPortGroup;	/* Max # of port groups		      */
	uint32_t  MaxNumPhysPortGroup;  /* Max # phys ports per port group    */
        uint64_t  PortQueryMask;        /* Boolean bit pos to cat correlation */
        uint64_t  PortModifyMask;       /* Boolean bit pos to cat correlation */
        uint64_t  reserved_hea[16];

        /*--------------------------------------------------------------------*/
        /*      Query Port - Category 0                                       */
        /*--------------------------------------------------------------------*/
        /* PxLy_MAC regs */
        uint8_t   EntryValid;
        uint8_t   Port;
        uint64_t  MAC;
        /* PxLy_RC  regs */
        uint8_t   LPortValid;
        uint8_t   VLANextract;
        uint8_t   TCP6tuple;
        uint8_t   UDP6tuple;
        uint8_t   TCP3tuple;
        uint8_t   TCP2tuple;
        uint8_t   LLCSNAP;
        uint8_t   JumboFrm;
        uint8_t   FragIPHndl;
        uint8_t   CkSumErrAct;   
        uint8_t   MACfilter;
        uint8_t   UntagFilter;
        uint8_t   VLANtagFilter;
        /* Remaining Cat 0 statistics */
        uint8_t   PortOperateState;
        uint8_t   PortSpeed;            
        uint8_t   ExtNetSwPortState;
        uint8_t   TxPauseF;
        uint8_t   RxPauseF;
        uint8_t   DfltQPNsPerPort;
        uint64_t  DfltQPNarray[MAX_MCS_NUM];   
        uint64_t  DfltQPNarrayISN[MAX_MCS_NUM];  
        uint64_t  DfltQPNarrayBus[MAX_MCS_NUM];  
        uint64_t  RxPktDropLong;
        uint64_t  reserved_pcs[16]; 
} hea_stats_t;


/*----------------------------------------------------------------------------*/
/*      HEA Statistics Structure for ENT, NDD and ADAP                        */
/*----------------------------------------------------------------------------*/
typedef struct hea_all_stats {
	ndd_genstats_t  ent_ndd_stats;	         /* network generic stats     */
	ent_genstats_t  ent_gen_stats;	         /* ethernet generic stats    */
	hea_stats_t     hea_stats;               /* device specific stats     */
} hea_all_stats_t;



#endif	/* _H_CDLI_ENTUSER_HEA */




