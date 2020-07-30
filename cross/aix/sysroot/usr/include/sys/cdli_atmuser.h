/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/cdli_atmuser.h 1.21                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1993,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)98  1.21  src/bos/kernel/sys/cdli_atmuser.h, sysxatm, bos530 10/29/02 14:20:29 */
/*
 * COMPONENT_NAME: SYSXATM
 *
 * FUNCTIONS: none.
 *
 * ORIGINS: 27
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
 */

#ifndef _H_CDLI_ATMUSER
#define _H_CDLI_ATMUSER

#include <sys/ndd.h>
#include <sys/call_ie.h>

/*
 * ATM Device Driver common definitions
 */
#define ATM_PHYSADDR_LEN        6       /* length of ATM physical address */

#define ATM_MAX_MTU             65535
#define ATM_MIN_MTU             1

/*
 * ATM specific control operations
 */
#define ATM_VC_OPEN     NDD_DEVICE_SPECIFIC     /* open a VC */
#define ATM_VC_CLOSE    ATM_VC_OPEN + 1         /* close a VC */
#define ATM_VC_ACK      ATM_VC_CLOSE + 1        /* acknowledge on a VC */
#define ATM_VC_LOCAL    ATM_VC_ACK + 1          /* open 2 local VC's */
#define ATM_TXBUF_REG   ATM_VC_LOCAL + 1        /* register for tx buffer */
#define ATM_TXBUF_GET   ATM_TXBUF_REG + 1       /* get a tx buffer */
#define ATM_VS_Q_LEN    ATM_TXBUF_GET + 1       /* max vs xmit queue len */

/* ATM device specific control operations */
#define ATM_DEVICE_SPECIFIC     NDD_DEVICE_SPECIFIC + 100

/*
 * ATM specific Status block codes for ndd_statblk_t
 * NOTE: The use of the NDD_STAT_BLOCK bit for the first 4 status codes is
 * different than the common status code definition defined in sys/ndd.h.
 */

#define ATM_VC_OPEN_DONE        NDD_STAT_BLOCK          /* a VC is opened */
#define ATM_VC_CLOSE_DONE       ATM_VC_OPEN_DONE + 1    /* a VC is closed */
#define ATM_VC_LOCAL_DONE       ATM_VC_CLOSE_DONE + 1   /* local VC opened */
#define ATM_VC_ACK_DONE         ATM_VC_LOCAL_DONE + 1   /* a VC_ACK is done */

/*
 * Additional flags for the ndd_flags field in the ndd.h file
 */
#define NDD_NO_HANDLE_0         (NDD_SPECFLAGS) /* don't user handle of zero */



/****************************************************************************/
/*  Structures for ATM control operations                                   */
/****************************************************************************/
struct atm_vc_open_req {
    int                   vc_handle;    /* VC handle */
    uint                  flags;        /* PVC, SVC, etc. */
    aal_parm_t            aal_parm;     /* AAL parameter */
    traffic_des_t         traffic_des;  /* Traffic Descriptor */
    atm_conn_id_t         conn_id;      /* ATM Connection ID */
    ushort                checksum_prot;/* checksum protocol control */
    ushort                checksum_type;/* checksum Transmit/Receive control */
};
typedef struct atm_vc_open_req  atm_vc_open_req_t;

/* values for flags field in atm_vc_open_req */
#define VCOPEN_SVC      0x00000001      /* SVC connection */
#define VCOPEN_CID      0x00000002      /* connection ID is defined */

/* definitions for checksum_prot values */
/* Will keep these values the same as for the adapter, for direct mapping */
#define NO_CHECKSUM       0     /* 0 - No checksum checking.            */
#define MPOA_CHECKSUM     1     /* 1 - MPOA header                      */
#define CIP_CHECKSUM      2     /* 2 - Native Ip                        */
                                /* 3 - Reserved, no checksum checking.  */
#define LANE_ETH_CHECKSUM 4     /* 4 - LANE Eth header                  */
                                /* 5 - Raw Ethernet header              */
#define LANE_TOK_CHECKSUM 6     /* 6 - LANE Token Ring header           */
                                /* Note: Values 3 and 5 are not used    */

/* definitions for checksum_type flags */
#define TX_CHECKSUM       1     /* do checksumming in the transmit direction */
#define RX_CHECKSUM       2     /* do checksumming in the receive direction  */


struct atm_vc_ack_req {
    int                 vc_handle;
    atm_conn_id_t       conn_id;
    aal_parm_t          aal_parm;       /* new AAL parameter if changed */
};
typedef struct atm_vc_ack_req  atm_vc_ack_req_t;


struct atm_vc_local_req {
    int                   vc_handle1;   /* first VC handle */
    int                   vc_handle2;   /* seconde VC handle */
};
typedef struct atm_vc_local_req  atm_vc_local_req_t;

struct atm_vc_txq_len {
    short                 handle;       /* handle  */
    int                   max_txq_len;  /* max incomplete xmits */
};
typedef struct atm_vc_txq_len  atm_vc_txq_len_t;

/****************************************************************************/
/* ATM device special configuration attributes                              */
/****************************************************************************/

struct atm_spec_config {
        __ulong32_t   max_xfer_blk;   /* maximum transfer block size         */
        __ulong32_t   max_bandwidth;  /* peak badwidth is Kbps               */
        __ulong32_t   get_intf_mbuf;  /* function ptr to get interface mbufs */
        __ulong32_t   vci;            /* number of vci that adapter support  */
        __ulong32_t   reserved[15];
};
typedef struct atm_spec_config ndd_spec_conf_t;

/*
 *  ATM device generic statistics
 */
typedef enum {
  AUTO_DETECT       = 0,
  UNI_30            = 1,
  UNI_31            = 2,
  UNI_IBM_8282      = 3,    /* IBM 8282 concentrator: SVC is UNI 3.0;
                              Q.SAAL is 3.1. Map to UNI_30.         */
  UNI_40            = 4,    /* Added 8/2/00 -- MEF */
  AUTO_DETECT_UNI_31_RESTRICTED = 9  /* Restrict negotiation to UNI 3.1
                                       as highest version           */
} uni_version;

struct atm_genstats {
  __ulong32_t device_type;      /* flags for interpreting the device specific*/
                          /* statistics extension                           */
  __ulong32_t dev_elapsed_time; /* time in seconds since last reset         */
  __ulong32_t ndd_flags;        /* a copy of ndd_flags field defined in ndd.h */
  char  atm_macadr[ATM_PHYSADDR_LEN];      /* MAC address         */

/* receive statistics */
  __ulong32_t rcv_cells_msw;          /* cells received by adapter */
  __ulong32_t rcv_cells_lsw;          /* cells received by adapter */
  __ulong32_t dropped_cells_msw;      /* rcv cells dropped by adapter */
  __ulong32_t dropped_cells_lsw;      /* rcv cells dropped by adapter */
  __ulong32_t crc_errors;             /* total crc errors */
  __ulong32_t oversized_sdus;         /* total pkts larger than rcv bufs */
  __ulong32_t total_no_rcv_buf;       /* pkts dropped due to no rcv bufs */
  __ulong32_t incomplete_pkts;        /* pkts dropped by reassembly timeout */

/* transmit statistics */
  __ulong32_t xmt_cells_msw;          /* cells transmitted by adapter */
  __ulong32_t xmt_cells_lsw;          /* cells transmitted by adapter */
  __ulong32_t sw_txq_len;             /* Current sw transmit queue length */
  __ulong32_t hw_txq_len;             /* Current hw transmit queue length */
  __ulong32_t total_no_xmt_buf;       /* xmits aborted due to no xmit buffers */

  __ulong32_t loss_of_signal;   /* times the loss of signal detected */
  __ulong32_t restart_count;    /* times the adapter error recovery performed */

/* VC statistics */
  __ulong32_t atm_vc_inuse;   /* vc's currently in use */
  __ulong32_t atm_vc_max;     /* max number of vc ever used */
  __ulong32_t atm_vc_fail;    /* number of failure of vc allocation */
  uni_version uni_ver;        /* UNI version in service */

  __ulong32_t reserved2;        /* reserved for future use */
  __ulong32_t reserved3;        /* reserved for future use */
  __ulong32_t reserved4;        /* reserved for future use */
};
typedef struct atm_genstats atm_genstats_t;

/*
 * flags for the device type field in the atm_genstats.
 */
#define ATM_TW_100      0x00000001      /* for the Turboways 100 extension */
#define ATM_TW_155      0x00000002      /* for the Turboways 155 extension */
#define ATM_TW_25       0x00000003      /* for the Turboways 25 extension */

/*
 * ATM device all generic statistics (for NDD_GET_STATS)
 */
struct atm_ndd_stats {
        struct  ndd_genstats atm_ndd_genstats;  /* network neneric stats */
        struct  atm_genstats atm_atm_genstats;  /* ATM generic stats */
};
typedef struct atm_ndd_stats atm_ndd_stats_t;


/*
 *  ATM device specific statistics (for NDD_GET_ALL_STATS)
 */

/* Turboways MCA ATM adapter specific statistics */
struct tw100_stats {
  __ulong32_t card_get_sml_fail;     /* rcv pkts dropped; no rcv dma mbufs */
  __ulong32_t card_get_med_fail;     /* rcv pkts dropped; no rcv dma mbufs */
  __ulong32_t card_get_lrg_fail;     /* rcv pkts dropped; no rcv dma mbufs */
  __ulong32_t card_get_rcv_buf_fail; /* recvs aborted; no adapter rcv bufs */
  __ulong32_t card_get_tx_buf_fail;  /* xmits aborted; no adapter xmit bufs */
  __ulong32_t max_hw_txq_len;        /* max tx queue length */
  __ulong32_t sml_xmit_fail;         /* aborted xmit due to no sys xmit bufs */
  __ulong32_t med_xmit_fail;         /* aborted xmit due to no sys xmit bufs */
  __ulong32_t lrg_xmit_fail;         /* aborted xmit due to no sys xmit bufs */
  __ulong32_t hug_xmit_fail;         /* aborted xmit due to no sys xmit bufs */
  __ulong32_t spec_xmit_fail;        /* aborted xmit due to no sys xmit bufs */
  __ulong32_t mbuf_sml_inuse;        /* number of small driver mbufs in use */
  __ulong32_t mbuf_med_inuse;        /* number of medium driver mbufs in use */
  __ulong32_t mbuf_lrg_inuse;        /* number of large driver mbufs in use */
  __ulong32_t mbuf_hug_inuse;        /* number of huge driver mbufs in use */
  __ulong32_t mbuf_spec_inuse;       /* number of special driver mbufs in use */
  __ulong32_t mbuf_sml_max;          /* max num small driver mbufs ever used */
  __ulong32_t mbuf_med_max;          /* max num medium driver mbufs ever used */
  __ulong32_t mbuf_lrg_max;          /* max num large driver mbufs ever used */
  __ulong32_t mbuf_hug_max;          /* max num huge driver mbufs ever used */
  __ulong32_t mbuf_spec_max;         /* max num special driver mbufs ever used*/
  __ulong32_t mbuf_sml_fail;         /* failures on small driver mbuf alloc */
  __ulong32_t mbuf_med_fail;         /* failures on medium driver mbuf alloc */
  __ulong32_t mbuf_lrg_fail;         /* failures on large driver mbuf alloc */
  __ulong32_t mbuf_hug_fail;         /* failures on huge driver mbuf alloc */
  __ulong32_t mbuf_spec_fail;        /* failures on special driver mbuf alloc */
};
typedef struct tw100_stats tw100_stats_t;

struct tw100_all_stats {
        struct ndd_genstats ndd_stats;     /* network neneric stats */
        struct atm_genstats atm_stats;     /* ATM generic stats */
        struct tw100_stats  tw100_stats;   /* device specific stats */
};
typedef struct tw100_all_stats tw100_all_stats_t;



/*  Turboways 25 ATM adapter specific statistics */
struct tw25_stats {
  ulong card_get_tx_buf_fail;  /* xmits aborted; no adapter xmit bufs */
  ulong mtu_xmit_fail;         /* aborted xmit due to no xmit bufs */
  ulong mbuf_sml_inuse;        /* number of small driver mbufs in use */
  ulong mbuf_med_inuse;        /* number of medium driver mbufs in use */
  ulong mbuf_lrg_inuse;        /* number of large driver mbufs in use */
  ulong mbuf_mtu_inuse;        /* number of huge driver mbufs in use */
  ulong mbuf_sml_max;          /* max number of small driver mbufs ever used */
  ulong mbuf_med_max;          /* max number of medium driver mbufs ever used */
  ulong mbuf_lrg_max;          /* max number of large driver mbufs ever used */
  ulong mbuf_mtu_max;          /* max number of huge driver mbufs ever used */
  ulong mbuf_sml_fail;         /* failures on driver small mbuf alloc */
  ulong mbuf_med_fail;         /* failures on driver medium mbuf alloc */
  ulong mbuf_lrg_fail;         /* failures on driver large mbuf alloc */
  ulong mbuf_mtu_fail;         /* failures on driver MTU mbuf alloc */
/* ANA 5610 specific statistics */
  int dma_fake_error;          /* dma fake error */
  int dma_real_error;          /* dma real error */
  int dma_ovfl_or_xmt_imis;    /* dma overflow or transmit mismatch */
  int reinit;                  /* number of times, card was reinitialized */
  int xmtroom_too_large;       /* transmit room too large */
/* PHY error statistics */
  int tc_cerr;                 /* tc cerr */
  int tc_overrun;              /* tc overrun */
  int invalid_vci;             /* invalid vci */
  int rcv_iden_mismatch;       /* receive identifier mismatch */
  int trash_count;             /* trash cell count */
  int wrong_rcv_buffer_size;   /* invalid receive size */
  int bad_trailer_vci;         /* msg trailer len field is wrong */
  int dma_length_mismatch;     /* DMA PDU length different from card's RAM
                                slave read */
  int crc_err_count;           /* CRC error countered by the board */
  int dma_complete_err;        /* errors reported by the d_complete on
                                receive intr */
};
typedef struct tw25_stats tw25_stats_t;

struct tw25_all_stats {
        struct ndd_genstats ndd_stats;     /* network neneric stats */
        struct atm_genstats atm_stats;     /* ATM generic stats */
        struct tw25_stats  tw25_stats;   /* device specific stats */
};
typedef struct tw25_all_stats tw25_all_stats_t;
 



/****************************************************************************/
/*  Trace hook id                                                           */
/****************************************************************************/
#define HKWD_ATMCM      0x3A000000      /* trace hook id for Call Manager */
#define HKWD_ATMDD_TW   0x33900000      /* trace hook id for Turboways
                                                100/155 DD */
#define HKWD_TW25DD     0x3A600000      /* trace hook id for Turboways 25 DD */



/* starting bo52B, the mapper area will no longer mapped to the reserve  */
/* field of the ndd struct. Instead, all driver will allocate a          */
/* atmdev_ndd struch which consists of the ndd struct plus the extrc     */
/* space for the mapper. And the mapper will map into this extra space   */
/* Note the size and offset of the mapper area vary between 32bit and    */
/* 64 bit                                                                */

/****************************************************************************
 *
 * ndd_atmcm_ks  -> Points to the call_ks structure defined in sys/call_ie.h
 *
 * atm_spec_conf -> Points to the ndd_spec_conf for special configuration
 *                  information defined in sys/cdli_atmuser.h
 *
 * atmcm_map_vc  -> Address of Call Manager's atmcm_map_vc function which
 *                  maps vc_handles to VPI/VCI pairs.  This function is used 
 *                  by iptrace to translate a handle in tx_vc_handle or 
 *                  rx_vc_handle to a VPI/VCI.
 *
 * tx_vc_handle  -> For Transmited packets, the ATM driver fills in the
 *                  vc_handle here.
 *
 * rx_vc_handle  -> For Received packets, the ATM driver fills in the
 *                  vc_handle here.
 *
 ****************************************************************************/

struct reserved_mapper {
    struct call_ks *ndd_atmcm_ks;   /* ndd_reserved[0]  ndd_reserved[0-1]  */
    ndd_spec_conf_t *atm_spec_conf; /* ndd_reserved[1]  ndd_reserved[2-3]  */
    long *atmcm_map_vc;             /* ndd_reserved[2]  ndd_reserved[4-5]  */
    uint tx_vc_handle;              /* ndd_reserved[3]  ndd_reserved[6-7]  */
    uint rx_vc_handle;              /* ndd_reserved[4]  ndd_reserved[8-9]  */
};
typedef struct reserved_mapper reserved_mapper;

struct atmdev_ndd {
    ndd_t                     system_ndd;
    reserved_mapper           ndd_extra;
};
typedef struct atmdev_ndd atmdev_ndd_t;
#endif  /* _H_CDLI_ATMUSER */

