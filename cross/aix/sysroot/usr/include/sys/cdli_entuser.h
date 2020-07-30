/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/cdli_entuser.h 1.28                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1993,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*  @(#)13      1.28  src/bos/kernel/sys/cdli_entuser.h, sysxent, bos530 6/10/04 17:08:07 */
/*
 * COMPONENT_NAME: SYSXENT
 *
 * FUNCTIONS: none.
 *
 * ORIGINS: 27, 83
 *
 *                  -- (                            when
 * combined with the aggregated modules for this product)
 * OBJECT CODE ONLY SOURCE MATERIALS
 *
 * (C) COPYRIGHT International Business Machines Corp. 1993
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * LEVEL 1, 5 Years Bull Confidential Information
 */

#ifndef _H_CDLI_ENTUSER
#define _H_CDLI_ENTUSER

#include <sys/ndd.h>

/*
 *  Miscellaneous definitions
 */
#define ENT_NADR_LENGTH		(6)      /* Ethernet address byte length */
#define ENT_MAX_MTU             (1514)   /* max packet data size */
#define ENT_MIN_MTU             (60)     /* min packet data size */
#define ENT_HEADER_SIZE         (14)     /* max Ethernet frame header size */
#define ENT_FSC_LENGTH          (4)      /* max Ethernet FSC length */


/* 
 *  Additional flags for the ndd_flags field in the ndd.h file
 */
#define ENT_RCV_BAD_FRAME	(NDD_SPECFLAGS)	/* rcv bad frames mode */
#define ENT_DATA_RATE		(2*NDD_SPECFLAGS) /* The reserved1 field in */
						/* ent_genstats_t contains */
						/* adapter data rate below */
#define ENT_DATA_RATE_10_HALF	(10)		/* 10 Mbps half duplex */
#define ENT_DATA_RATE_10_FULL	(20)		/* 10 Mbps full duplex */
#define ENT_DATA_RATE_100_HALF	(100)		/* 100 Mbps half duplex */
#define ENT_DATA_RATE_100_FULL	(200)		/* 100 Mbps full duplex */
#define ENT_DATA_RATE_1000_HALF	(1000)		/* 1000 Mbps half duplex */
#define ENT_DATA_RATE_1000_FULL	(2000)		/* 1000 Mbps full duplex */
#define	ENT_DATA_RATE_10Gb	(20000)		/* 10 Gbps full duplex */

#define NDD_ENT_LARGE_SEND	(4*NDD_SPECFLAGS) /* H/W large send enabled */
#define NDD_IPSEC_OFFLOAD       (8*NDD_SPECFLAGS) /* supports ipsec offload */

/*
 *  Ethernet device generic statistics 
 */

struct ent_genstats {
  __ulong32_t device_type;	/* flags for interpreting the device specific*/
			  	/* statistics extension 		    */
  __ulong32_t dev_elapsed_time; /* time in seconds since last reset	    */
  __ulong32_t ndd_flags;	/* a copy of ndd_flags field defined in ndd.h */
  char  ent_nadr[ENT_NADR_LENGTH];	/* Ethernet network address	    */

/* receive statistics */
  __ulong32_t mcast_rx_ok;      /* no. of multicast packets received	    */
  __ulong32_t bcast_rx_ok;      /* no. of broadcast packets received	    */
  __ulong32_t fcs_errs;         /* Frame Check Sequence error count         */
  __ulong32_t align_errs;       /* Alignment error count                    */
  __ulong32_t overrun;          /* Receive overrun count                    */
  __ulong32_t short_frames;     /* Packet too short error count             */
  __ulong32_t long_frames;      /* Packet too long error count              */
  __ulong32_t no_resources;     /* Receive out of resources count           */
  __ulong32_t rx_collisions;	/* Receive collisions error count 	    */
  __ulong32_t rx_drop;   	/* Packets discarded by adapter
				- not supported by ENT_IEN_ISA		    */
  __ulong32_t start_rx;   	  /* no. of times that receiver was started    
				- not supported by ENT_IEN_ISA		    */

/* transmit statistics */
  __ulong32_t mcast_tx_ok;      /* no. of multicast packets transmitted	    */
  __ulong32_t bcast_tx_ok;      /* no. of broadcast packets transmitted	    */
  __ulong32_t carrier_sense;    /* Lost Carrier Sense signal count          */
  __ulong32_t underrun;         /* Transmit underrun error count            */
  __ulong32_t cts_lost;         /* Lost Clear-To-Send signal count 
				- not supported by ENT_IEN_ISA		    */
  __ulong32_t excess_collisions;/* Maximum collisions exceeded error count  */
  __ulong32_t late_collisions;  /* Collision after the slot time error count 
				- not supported by ENT_3COM, ENT_IEN_ISA    */
  __ulong32_t tx_timeouts;      /* Transmit timeout count                   */
  __ulong32_t sqetest;	  /* SQE test 
				- not supported by ENT_3COM, ENT_IEN_ISA    */
  __ulong32_t defer_tx;	  /* Transmit deferred count 
				- not supported by ENT_3COM, ENT_IEN_ISA    */
  __ulong32_t s_coll_frames; 	  /* Transmit with single collision count   */
  __ulong32_t m_coll_frames;    /* Transmit with multiple collision count   */
  __ulong32_t sw_txq_len;       /* Current sw transmit queue length	    */
  __ulong32_t hw_txq_len;       /* Current hw transmit queue length
				- not supported by ENT_IEN_ISA		    */
  __ulong32_t restart_count;    /* times the adapter error recovery ran     */

  __ulong32_t reserved1;	  /* reserved for future use		    */
  __ulong32_t reserved2;	  /* reserved for future use		    */
  __ulong32_t reserved3;	  /* reserved for future use		    */
  __ulong32_t reserved4;	  /* reserved for future use		    */
};

typedef struct ent_genstats ent_genstats_t;

/* 
 * flags for the device type field in the ent_genstats.
 */
#define ENT_3COM	0x00000001	/* for the en3com_stats extension */
#define ENT_IENT	0x00000002	/* for the ient_stats   extension */
#define ENT_IEN_ISA	0x00000003	/* for the ien_isa_stats extension */
#define ENT_LCE		0x00000004	/* for the enlce_stats  extension */
#define ENT_KEN_PCI	0x00000005	/* for the kent_stats  extension */
#define ENT_LSA         0x00000006	/* for the lent_stats  extension */
#define ENT_IEN_PCMCIA  0x00000007	/* for the ien_pcmcia_stats extension*/

/*
 * Ethernet device all generic statistics (for NDD_GET_STATS)
 */
struct ent_ndd_stats {
	struct  ndd_genstats ent_ndd_genstats;     /* network neneric stats */
	struct  ent_genstats ent_ent_genstats;	/* ethernet generic stats */
};
typedef struct ent_ndd_stats ent_ndd_stats_t;


/*
 *  Ethernet device specific statistics (for NDD_GET_ALL_STATS)
 */

/* High Performance Ethernet adapter (3com) specific statistics */
struct en3com_stats {
  __ulong32_t multi_promis_mode;   /* Receive in promiscuous mode due to
			        extended multicast support		    */
  __ulong32_t rv_pool_size;	  /* driver's no. of receive buffers	    */
  __ulong32_t tx_pool_size;	  /* driver's no. of transmit buffers (hw Q) */
  __ulong32_t host_rcv_eol;     /* Host side End-of-List bit seen           */
  __ulong32_t adpt_rcv_eol;     /* Adapter/586 End-of-List bit seen         */
  __ulong32_t adpt_rcv_pack;    /* adpt rec packets to be uploaded to host  */
  __ulong32_t rcv_dma_to;       /* Receive DMA time outs due to lock up     */
  ushort reserved[5];     /* 3com internal use only state variables  - HEX  */
};
typedef struct en3com_stats en3com_stats_t;

struct en3com_all_stats {
	struct  ndd_genstats ent_ndd_stats;     /* network neneric stats */
	struct  ent_genstats ent_gen_stats;	/* ethernet generic stats */
	struct  en3com_stats en3com_stats;	/* device specific stats */
};
typedef struct en3com_all_stats en3com_all_stats_t;


/* Integrated Ethernet adapter specific statistics */
struct ient_stats{
  int coll_freq[16];		/* Frequency of no. of collisions */
};
typedef struct ient_stats ient_stats_t;

struct ient_all_stats{
        struct  ndd_genstats ent_ndd_stats;     /* network neneric stats */
        struct  ent_genstats ent_gen_stats;     /* ethernet generic stats */
        struct  ient_stats ient_stats;      	/* device specific stats */
};
typedef struct ient_all_stats ient_all_stats_t;


/* IBM ISA Ethernet adapter specific statistics */
typedef struct {
  __ulong32_t multi_promis_mode; /* Receive in promiscuous mode due to
                                   extended multicast support		*/
  int coll_freq[16]; 		/* Frequency of no. of collisions 	*/
} ien_isa_stats_t;

typedef struct {
  	struct  ndd_genstats ent_ndd_stats;     /* network generic stats */
  	struct  ent_genstats ent_gen_stats;     /* ethernet generic stats */
  	ien_isa_stats_t      ien_isa_stats;     /* device specific stats */
} ien_isa_all_stats_t;


/* Low Cost High Performance Ethernet adapter (LCE) specific statistics */
typedef struct {
  char adapter_type;      /* AUI/10baseT or 10base2            		    */
  int media_selection;    /* AUI/10baseT or 10base2            		    */
  int mace_version;       /* Version number of the MACE chip   		    */
  int mcnet_version;      /* Version number of the McNet chip  		    */
  __ulong32_t rx_fifo_full;     /* number of times McNet recv. fifo is full */
  __ulong32_t rx_timeout;	  /* number of interval timer expires       */
  __ulong32_t excessive_deferral;/* # packets that experience excess deferral */
  __ulong32_t total_collisions; /* network collisions                       */
  __ulong32_t coll_freq[16];    /* frequency of collisions for each (1 - 15) */
  __ulong32_t babble;           /* transmit 1519 or more bytes in packet    */
  __ulong32_t jabber;           /* 10BaseT; attempted xmit for excessive time */
  ushort reserved;        /* internal use only                              */
} enlce_stats_t;

/*
 * Flags for  for LCE adapter type
 */
#define AUI_BASET 0       /* Adapter with AUI and 10baseT ports   */
#define BASE2_ONLY 1      /* Adapter with 10base2 port only       */

/*
 * Flags for LCE media selection
 */
#define AUI   0           /* Adapter is using the AUI port        */
#define BASET 1           /* Adapter is using 10baseT port        */
#define BASE2 2           /* Adapter is using the 10base2 port    */
#define AUTO  3           /* Adapter is in autosense mode         */

typedef struct {
	struct  ndd_genstats ent_ndd_stats;     /* network neneric stats */
	struct  ent_genstats ent_gen_stats;	/* ethernet generic stats */
	enlce_stats_t        enlce_stats;	/* device specific stats */
} enlce_all_stats_t;


/* IBM PCI Ethernet adapter specific statistics */
struct kent_stats{
  int coll_freq[16];	      	/* Frequency of no. of collisions */
  char chip_rev;                /* Used to hold the version id of the */
                                /* AMD chip */
};
typedef struct kent_stats kent_stats_t;

struct kent_all_stats{
        struct  ndd_genstats ent_ndd_stats;     /* network neneric stats */
        struct  ent_genstats ent_gen_stats;     /* ethernet generic stats */
        struct  kent_stats kent_stats;      	/* device specific stats */
};
typedef struct kent_all_stats kent_all_stats_t;


/* Ethernet part of the LSA adapter specific statistics */
struct lent_stats {
    int             rv_pool_size;	/* driver's no. of receive buffers   */
    int             tx_pool_size;	/* driver's no. of transmit buffers  */
    int             coll_freq[16];	/* Frequency of no. of collisions    */
};
typedef struct lent_stats lent_stats_t;

struct lent_all_stats {
    struct ndd_genstats ent_ndd_stats;	/* network neneric stats             */
    struct ent_genstats ent_gen_stats;	/* ethernet generic stats            */
    struct lent_stats lent_dev_stats;	/* device specific stats             */
};
typedef struct lent_all_stats lent_all_stats_t;


/* IBM PCMCIA Ethernet adapter specific statistics */
typedef struct {
  __ulong32_t multi_promis_mode; /* Receive in promiscuous mode due to
                                   extended multicast support		*/
  int coll_freq[16]; 		/* Frequency of no. of collisions 	*/
} ien_pcmcia_stats_t;

typedef struct {
  	struct  ndd_genstats ent_ndd_stats;     /* network generic stats */
  	struct  ent_genstats ent_gen_stats;     /* ethernet generic stats */
  	ien_pcmcia_stats_t   ien_pcmcia_stats;  /* device specific stats */
} ien_pcmcia_all_stats_t;




/*
 * Ethernet incoming bad packet error code
 * These error code is used in the NDD_BAD_PKTS asynchronous status block
 * option[0] as reason of the bad packet.
 */
#define ENT_RCV_CRC_ERR		NDD_REASON_CODE + 1	/* CRC error */
#define ENT_RCV_OVRUN_ERR	NDD_REASON_CODE + 2	/* FIFO overrun */
#define ENT_RCV_ALIGN_ERR	NDD_REASON_CODE + 3	/* Alignment error */
#define ENT_RCV_RSC_ERR		NDD_REASON_CODE + 4	/* No resource error */
#define ENT_RCV_SHORT_ERR	NDD_REASON_CODE + 5	/* Packet too short */
#define ENT_RCV_LONG_ERR	NDD_REASON_CODE + 6	/* Packet too long */
#define ENT_RCV_COLL		NDD_REASON_CODE + 7     /* late collision */

/*
 * Ethernet error code returned in the status blocks and system error logs.
 */
#define ENT_NOBUFS	NDD_REASON_CODE + 8	/* buffer/memory not 
						   available */
#define ENT_DMA_FAIL	NDD_REASON_CODE + 9	/* DMA operation failure */
#define ENT_PARITY_ERR	NDD_REASON_CODE + 10	/* parity error */

/*
 *  Trace hook numbers
 */

/* High Performance Ethernet adapter (3com) trace hook numbers */
#define HKWD_EN3COM_XMIT	0x351		/* transmit events */
#define HKWD_EN3COM_RECV	0x352		/* receive events  */
#define HKWD_EN3COM_OTHER	0x353		/* other events    */
#define HKWD_EN3COM_ERR		0x354		/* error events	   */

/* Integrated Ethernet adapter trace hook numbers */
#define HKWD_IENT_XMIT		0x320      	/* transmit events */
#define HKWD_IENT_RECV		0x321      	/* receive events  */
#define HKWD_IENT_OTHER		0x322      	/* other events    */
#define HKWD_IENT_ERR		0x323      	/* error events    */

/* Low Cost High Performance Ethernet adapter (LCE) trace hook numbers */

#define HKWD_CDLI_LCE_RECV	0x327		/* receive events  */
#define HKWD_CDLI_LCE_OTHER	0x328		/* other events    */
#define HKWD_CDLI_LCE_XMIT	0x27D		/* transmit events */
#define HKWD_CDLI_LCE_ERR	0x27E		/* error events    */

/* IBM ISA 16 bit ethernet adapter (ient) trace hook numbers */

#define HKWD_IEN_ISA_XMIT          0x330           /* transmit events */
#define HKWD_IEN_ISA_RECV          0x331           /* receive events  */
#define HKWD_IEN_ISA_OTHER         0x332           /* other events    */
#define HKWD_IEN_ISA_ERR           0x333           /* error events    */

/* IBM PCI ethernet adapter (kent) trace hook numbers */

#define HKWD_KEN_PCI_XMIT	0x2A4		/* transmit events */
#define HKWD_KEN_PCI_RECV	0x2A5		/* receive events */
#define HKWD_KEN_PCI_OTHER	0x2A6		/* other events */

/* Ethernet part of the LSA adapter (lent) trace hook numbers */
 
#define HKWD_LENT_XMIT		0x324	        /* transmit events */
#define HKWD_LENT_RECV		0x325	        /* receive events  */
#define HKWD_LENT_OTHER		0x326	        /* other events    */
#define HKWD_LENT_ERR		0x329	        /* error events    */

/*
 * Structures that are used by the device driver and the AIX IPsec
 * modules to perform IPsec offload onto the adapter.
 */

/*
 * The following constants are defined in the ipsp.h file located in the 
 * src/ipscrypto/usr/include/ipsec directory. They have been replicated 
 * here for convenience.
 */
#define ESP_3DES_CBC_ID			3
#define ESP_NULL_ID			11
#define ESP_DES_CBC_8_ID		18
#define AH_HMAC_MD5_ID			38
#define AH_HMAC_SHA_ID			39

typedef struct _ipsec_offload_query_characteristics
{
	uint32_t	ipsec_dev_id;	/* used to identify the adapter */
        uint32_t        general_ipv4;
#define         AH_RECEIVE                              (1L<<0)
#define         ESP_RECEIVE                             (1L<<1)
#define         AH_ESP_RECEIVE                          (1L<<2)
#define		ESP_AH_RECEIVE				(1L<<3)
#define         TRANSPORT_TUNNEL_COMBINED_RECEIVE       (1L<<8)
#define         V4_OPTIONS_RECEIVE                      (1L<<9)
#define         STRIPS_HEADERS                          (1L<<10)
#define		AH_ESP_AUTH_COMBINED_RECEIVE		(1L<<11)
#define         AH_TRANSMIT                             (1L<<16)
#define         ESP_TRANSMIT                            (1L<<17)
#define         AH_ESP_TRANSMIT                         (1L<<18)
#define		ESP_AH_TRANSMIT				(1L<<19)
#define         TRANSPORT_TUNNEL_COMBINED_TRANSMIT      (1L<<24)
#define         V4_OPTIONS_TRANSMIT                     (1L<<25)
#define         CONSTRUCTS_HEADERS                      (1L<<26)
#define		AH_ESP_AUTH_COMBINED_TRANSMIT		(1L<<27)
        uint32_t        general_ipv6;  /* same #define as above, */
                                       /* except V4_OPTIONS */
        uint32_t        onthefly_ipv4; /* same #define as above */
        uint32_t        onthefly_ipv6; /* same #define as above */
                                       /* except V4_OPTIONS */
        uint32_t        ah;
#define         MD5_SUPPORTED                           (1L<<8)
#define         SHA_1_SUPPORTED                         (1L<<9)
#define         TRANSPORT_SUPPORTED                     (1L<<16)
#define         TUNNEL_SUPPORTED                        (1L<<17)
        uint32_t        esp;
#define         NULL_ESP_SUPPORTED                      (1L<<0)
#define         DES_SUPPORTED                           (1L<<1)
#define         TRIPLE_DES_SUPPORTED                    (1L<<2)
#define         AES_SUPPORTED                           (1L<<3)
/* Use same #define's above */
/* #define         MD5_SUPPORTED                           (1L<<8) */
/* #define         SHA_1_SUPPORTED                         (1L<<9) */
/* #define         TRANSPORT_SUPPORTED                     (1L<<16)*/
/* #define         TUNNEL_SUPPORTED                        (1L<<17)*/
        uint32_t        sa_table_info;
#define         HAS_INBOUND_SA_TABLE                    (1L<<0)
#define         HAS_OUTBOUND_SA_TABLE                   (1L<<1)
#define         HAS_COMBINED_SA_TABLE                   (1L<<2)
        ushort_t        num_inbound_sa_entries; /* Also used for COMBINED */
        ushort_t        num_outbound_sa_entries;
        ushort_t        reserved[10];
} ipsec_offload_query_characteristics, *ipsec_offload_query_characteristics_p;

typedef struct _ipsec_offload_add_sa
{
        ushort_t        entry_num;
        ushort_t        sa_table; /* This is undefined if the adapter */
                                  /* has a COMBINED_SA_TABLE */
#define         INBOUND_SA_TABLE                        (1L<<0)
#define         OUTBOUND_SA_TABLE                       (1L<<1)
        uint32_t        dst_ip_addr;
        uint32_t        src_tunnel_addr;
        uint32_t        dst_tunnel_addr;
        uint32_t        policy_flags;
/*
 * The following constants are defined in the ipsp_policy.h file located in 
 * the src/ipscrypto/usr/include/ipsec directory. They have been replicated 
 * here for convenience.
 */
#define IPSP_MY_MAC_FIRST		0x00000010
#define IPSP_HIS_MAC_FIRST		0x00000200
	uint32_t        ah_spi;
        uint32_t        esp_spi;
        uint32_t        enc_alg;
#define         IPSO_NULL		ESP_NULL_ID
#define         IPSO_DES		ESP_DES_CBC_8_ID
#define         IPSO_3DES		ESP_3DES_CBC_ID
#define         IPSO_AES		4
        ushort_t        enc_key_len;
        void *          enc_key;
        uint32_t        enc_mac_alg;
#define         IPSO_MD5		AH_HMAC_MD5_ID
#define         IPSO_SHA_1		AH_HMAC_SHA_ID
        ushort_t        enc_mac_key_len;
        void *          enc_mac_key;
        uint32_t        mac_alg;
/* Use same #define's above */
/* #define         IPSO_MD5                                1 */
/* #define         IPSO_SHA_1                              2 */
        ushort_t        mac_key_len;
        void *          mac_key;
	void *		device_dep_data;
        uint32_t        reserved[10];
} ipsec_offload_add_sa, *ipsec_offload_add_sa_p;

/*
 * Flags to identify the type of the SA structure that is being
 * passed in the mbuf. These flags are used for debug purposes.
 */
#define IPSO_SA_TYPE                    1
#define IPSO_DECRYPT_INFO_TYPE          2

typedef struct _ipsec_offload_SA
{
        uint32_t        ipso_type;      /* to identify offload SA structure */
                                        /* type (for debug purpose only)    */
        uint32_t        esp_spi;
        uint32_t        ah_spi;
        uint32_t        policy_flags;   /* same as in "ipsec_offload_add_sa" */
        uint32_t        enc_alg;
        ushort_t        enc_key_len;
        void *          enc_key;
        uint32_t        enc_mac_alg;
        ushort_t        enc_mac_key_len;
        void *          enc_mac_key;
        uint32_t        mac_alg;
        ushort_t        mac_key_len;
        void *          mac_key;
        uint32_t        iv0;
        uint32_t        iv1;
        uint32_t        auth_offset;
        uint32_t        auth_len;
        uint32_t        auth_result_offset;
        uint32_t        encr_offset;
        uint32_t        encr_len;
	uint32_t        ip_header_offset;
	uint32_t        protocol_header_offset;
	uint32_t	protocol_payload_len;
	uint32_t	tid;
	void *		device_dep_data;
        uint32_t        reserved[20];
} ipsec_offload_SA, *ipsec_offload_SA_p;

typedef struct _ipsec_offload_decrypt_info
{
        uint32_t        ipso_type;      /* to idenfify offload decrypt info */
                                        /* structure type (for debug only)  */
        ushort_t        entry_num;
        ushort_t        status;
#define         IPSO_SIG_OK                     (1L<<0)
#define         IPSO_ESP_DONE                   (1L<<1)
#define         IPSO_HASH_DONE                  (1L<<2)
#define         IPSO_ESP_DETECTED               (1L<<3)
#define         IPSO_AH_DETECTED                (1L<<4)
#define         IPSO_LEN_MISMATCH               (1L<<5)
#define         IPSO_PROT_MISMATCH              (1L<<6)
        uint32_t        reserved[10];
}ipsec_offload_decrypt_info, *ipsec_offload_decrypt_info_p;

typedef struct  _ipsec_offload_delete_sa
{
        ushort_t        entry_num;
        ushort_t        sa_table; /* This is undefined if the adapter */
                                  /* has a COMBINED_SA_TABLE */
} ipsec_offload_delete_sa, *ipsec_offload_delete_sa_p;

typedef struct  _ipsec_offload_clear_all_sas
{
        ushort_t        sa_table; /* This is undefined if the adapter */
                                  /* has a COMBINED_SA_TABLE */
} ipsec_offload_clear_all_sas, *ipsec_offload_clear_all_sas_p;

#endif  /* _H_CDLI_ENTUSER */
