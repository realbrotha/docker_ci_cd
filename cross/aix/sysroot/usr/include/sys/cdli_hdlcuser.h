/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/cdli_hdlcuser.h 1.7                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996,1997          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)27	1.7  src/bos/kernel/sys/cdli_hdlcuser.h, hdlc_sw, bos530 7/20/97 13:49:14 */
/*
 * COMPONENT_NAME: SYSXHDLC
 *
 * FUNCTIONS: none.
 *
 * ORIGINS: 27
 *
 *                  -- (                            when
 * combined with the aggregated modules for this product)
 * OBJECT CODE ONLY SOURCE MATERIALS
 *
 * (C) COPYRIGHT International Business Machines Corp. 1996
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _H_CDLI_HDLCUSER
#define _H_CDLI_HDLCUSER

#include <sys/ndd.h>

#define NDD_HDLC	0x21 /* NDD_HDLC (NDD_SDLC | NDD_LAPB) */

/**************************************************************************
 *   HDLC NDD_CTL OPERATIONS						  *
 **************************************************************************/
#define	HDLC_CONNECT	NDD_DEVICE_SPECIFIC + 1	/* Connect to network */
#define	HDLC_DISCONNECT	NDD_DEVICE_SPECIFIC + 2	/* Disconnect from network */
#define	HDLC_RESET_LINK	NDD_DEVICE_SPECIFIC + 3	/* Reset/reconnect to network */

/**********************************************************************
 *    Miscellaneous NDD_CTL Defines				      *
 **********************************************************************/
/* The following definitions are used by chg_mask in change parameters and 
   should have the same values as their field select counterparts above.  */

#define	HDLC_CP_POLL_ADDR (int)	0x00000010    /* Poll address bit mask	*/
#define	HDLC_CP_DSR_TMR	  (int)	0x00000020    /* DSR timer bit mask	*/
#define	HDLC_CP_MDM_FLG	  (int)	0x00000040    /* Modem flags bit mask 	*/
					      /* (all fields must be valid */
					      /* with this option since it */
					      /* actually restarts link) */
#define	HDLC_CP_RCV_TMR	  (int)	0x00000080    /* receive timer bit mask	*/


/***************************************************************************
 *		   HDLC	Physical link					   *
 ***************************************************************************/

#define	 HDLC_PL_AUTO		0xcabe	  /* Auto Select by Cable  */
#define	 HDLC_PL_V24		0x0000	  /* EIA232-D/V.24	   */
#define	 HDLC_PL_V35		0x0080	  /* V.35         	   */
#define	 HDLC_PL_V36		0x0100	  /* V.36		   */
#define	 HDLC_PL_X21		0x0180	  /* X.21		   */

/**************************************************************************
 *		   HDLC	data encoding					  *
 **************************************************************************/
#define HDLC_DATA_ENC_NRZ         0x00   /* NRZ */
#define HDLC_DATA_ENC_NRZI        0x01   /* NRZI */
#define HDLC_DATA_ENC_FM0         0x02   /* FM0 */
#define HDLC_DATA_ENC_FM1         0x03   /* FM1 */
#define HDLC_DATA_ENC_MAN         0x04   /* Manchester */
#define HDLC_DATA_ENC_DMAN        0x05   /* Differential Manchester */

/**************************************************************************
 *		   HDLC	data flags					  *
 **************************************************************************/
#define  HDLC_DATA_FLG_FDX              0x02
#define  HDLC_DATA_FLG_HDX              0x04

#define	 HDLC_DATA_FLG_RST_TMR		0x10	  /* Restart Rcv Timer  */
#define	 HDLC_DATA_FLG_C_CARR_ON	0x20	  /* Continuous	Carrier, */
						  /* RTS always ON       */
#define	 HDLC_DATA_FLG_RST_CON		0x40	  /* Auto-restart After Call */

/**************************************************************************
 *	      HDLC Link Types						  *
 **************************************************************************/
#define	 HDLC_LNK_LEASED	0x00 
#define	 HDLC_LNK_LISTEN	0x01  	  /* Wait for DSR on incoming */
					  /* call */
#define	 HDLC_LNK_CDSTL		0x02	  /* Wait for RI or DSR */  	
#define	 HDLC_LNK_V25BIS_LISTEN	0x03
#define	 HDLC_LNK_V25BIS_CALL	0x04 	  /* Use V25bis 108.2 */
#define	 HDLC_LNK_MANUAL_CALL	0x05 	  /* Drive DTR and user */ 
#define  HDLC_LNK_DIRECT_CALL	0x06      /* or modem (v25bis 108.1) */
					  /* makes call */

/* dial string length */
#define  HDLC_SIG_LEN		256

typedef	struct auto_data
{
	unsigned short		len;
	char			sig[HDLC_SIG_LEN];  /*   dial string 	      */
				    /* when using v.25 bis: 		      */
				    /*  SDLC requires address, control fields */
	unsigned short		v25b_tx_timer;  /* delay after DTR before dial*/
						/* data is sent to the modem  */
	unsigned short		v25b_idle_timer;/* delay before reconnecting  */
						/* when autorestart is set    */
} auto_data_t;

typedef struct auto_data adap_dial_data_t;

/*
 *  HDLC start device data structure Definition
 */
struct hdlc_connect
{
    unsigned short	phys_link;		/* physical link/cable	*/
    unsigned char	data_encode;		/* data encoding        */
    unsigned char	data_flags;		/* protocol flags for data */
    unsigned char	link_type;		/* link type		*/
    unsigned char	poll_addr;		/* poll	address		*/
    unsigned int	baud_rate;		/* connection baud rate	*/
						/* 0 = external clocking*/
    unsigned short	rcv_timeout;		/* receive time	out	*/
    unsigned short	connect_timer;		/* Connect establishment */
    unsigned short	dsr_timer;		/* DSR debounce timer    */
    auto_data_t		auto_data;
};
typedef struct hdlc_connect hdlc_connect_t;

/*
 *  HDLC reset link parameters data structure definition
 */
struct hdlc_reset_link
{
    int		   chg_mask	  ;	    /* mask for	change parms	  */
    unsigned short rcv_timer	  ;	    /* receive timer		  */
    unsigned short connect_timer  ;	    /* connection establishment timer */
    unsigned char  poll_addr	  ;	    /* poll address		  */
    unsigned char  link_type      ;	    /* link type 		  */
};
typedef struct hdlc_reset_link hdlc_reset_link_t;

/*
 *  Miscellaneous definitions
 */
#define HDLC_NADR_LENGTH	(1)      /* HDLC address byte length */
#define HDLC_MAX_MTU            (4096)   /* max packet data size */
#define HDLC_MIN_MTU            (2)      /* min packet data size */


/* 
 *  Additional flags for the ndd_flags field in the ndd.h file
 */
#define HDLC_RCV_BAD_FRAME      (NDD_SPECFLAGS)    /* rcv bad frames mode */
#define HDLC_CONNECTING	        (NDD_SPECFLAGS * 2)/* connecting to network */
#define HDLC_DISCONNECTING      (NDD_SPECFLAGS * 4)/* disconnecting from network */
#define HDLC_CONNECTED       	(NDD_RUNNING)  	   /* waiting for DSR signal */
						   /* to be attached        */
/*
 *  HDLC device generic statistics 
 */
struct hdlc_genstats {
  uint device_type;	 /* flags for interpreting the device specific     */
			 /* statistics extension 			   */
  uint dev_elapsed_time; /* time in seconds since last reset		   */
  uint ndd_flags;	 /* a copy of the ndd_flags field defined in ndd.h */
  char hdlc_nadr[HDLC_NADR_LENGTH];	/* HDLC network address	           */
  ushort cable_type;	 /* flags for interpreting the cable/physical link */
			 /* all 1's no cable attached (for devices with the*/
			 /* ability to autodetect the cable); otherwise,   */
			 /* same as phys_link value in hdlc_connect_t.	   */		  
/* receive statistics */
  uint crc_errs;         /* Frame Check Sequence error count (CRC errors)  */
  uint rx_aborts;        /* Receive abort (7 1s) error count               */
  uint overrun;          /* Receive overrun count                          */
  uint short_frames;     /* Packet too short error count                   */
  uint long_frames;      /* Packet too long error count                    */
  uint no_resources;     /* Receive out of resources count                 */
  uint rx_drop;   	 /* Packets discarded by adapter		   */
  uint start_rx;   	 /* no. of times that receiver was started	   */
  uint rx_timeouts;      /* Receive timeout count                          */

/* transmit statistics */
  uint carrier_loss;     /* Lost Carrier detect signal count               */
  uint underrun;         /* Transmit underrun error count                  */
  uint cts_lost;         /* Lost Clear-To-Send signal count                */
  uint tx_timeouts;      /* Transmit timeout count                         */
  uint defer_tx;         /* Transmit deferred count (EAGAIN)               */
  uint sw_txq_len;       /* Current sw transmit queue length		   */
  uint hw_txq_len;       /* Current hw transmit queue length		   */
  uint restart_count;	 /* times the adapter error recovery performed     */

/* modem statistics   */
  uint cts_timeout;      /* number of clear to send timeout   		   */
  uint cts_on;		 /* number of clear to send already on (controlled)*/
  uint dsr_timeout;      /* number of data set ready timeout               */
  uint dsr_dropped;      /* number of data set ready dropped               */
  uint dsr_on;		 /* number of data set ready already on (switched) */


  uint dataflags;	  /* data flags for the connection                 */
  uint reserved2;	  /* reserved for future use			   */
  uint reserved3;	  /* reserved for future use			   */
  uint reserved4;	  /* reserved for future use			   */
};

typedef struct hdlc_genstats hdlc_genstats_t;

/* 
 * flags for the device type field in the hdlc_genstats.
 */
#define HDLC_DPMP_PCI	0x00000001	/* for the dpmp_stats  extension */

/*
 * HDLC device all generic statistics (for NDD_GET_STATS)
 */
struct hdlc_ndd_stats {
	struct  ndd_genstats hdlc_ndd_genstats;     /* network neneric stats */
	struct  hdlc_genstats hdlc_hdlc_genstats;	/* hdlc generic stats */
};
typedef struct hdlc_ndd_stats hdlc_ndd_stats_t;


/*
 *  HDLC device specific statistics (for NDD_GET_ALL_STATS)
 */

struct dpmp_all_stats{
        struct  ndd_genstats hdlc_ndd_stats;     /* network neneric stats */
        struct  hdlc_genstats hdlc_gen_stats;     /* hdlc generic stats */
};
typedef struct dpmp_all_stats dpmp_all_stats_t;

/*************************************************************************
 *    HDLC Status Block	Code Values					 *
 *************************************************************************/
/*
 * HDLC receive error code
 * These error code is used in the NDD_STATUS asynchronous status block
 * option[1] as reason of the NDD_RCV_ERROR in option[0].
 */
#define HDLC_RCV_CRC_ERR	NDD_REASON_CODE + 1	/* CRC error */
#define HDLC_RCV_OVRUN_ERR	NDD_REASON_CODE + 2	/* FIFO overrun */
#define HDLC_RCV_ABORT_ERR	NDD_REASON_CODE + 3	/* Alignment error */
#define HDLC_RCV_RSC_ERR	NDD_REASON_CODE + 4	/* No resource error */
#define HDLC_RCV_SHORT_ERR	NDD_REASON_CODE + 5	/* Packet too short */
#define HDLC_RCV_LONG_ERR	NDD_REASON_CODE + 6	/* Packet too long */

/*
 * HDLC transmit error code
 * These error code is used in the NDD_STATUS asynchronous status block
 * option[1] as reason of the NDD_TX_ERROR in option[0].
 */
#define	HDLC_TX_UNDERRUN	NDD_REASON_CODE + 7
#define	HDLC_CTS_TIMEOUT	NDD_REASON_CODE + 8
#define	HDLC_CTS_UNDERRUN	NDD_REASON_CODE + 9
#define	HDLC_CTS_ALRDY_ON	NDD_REASON_CODE + 10
/*
 * These error codes are used in the NDD_CONNECTED asynchronous status block
 * option[0] as reason of the NDD_CONNECTED status block. Zero in option[0]
 * indicates the connection is established.
 */
#define	HDLC_X21_TIMEOUT	NDD_REASON_CODE + 11	/* X.21	timer expired */
#define HDLC_DSR_ALRDY_ON	NDD_REASON_CODE + 12
#define	HDLC_DSR_ON_TIMEOUT	NDD_REASON_CODE + 13 	/* DSR fails to come on */
#define	HDLC_X21_RETRIES_EXC	NDD_REASON_CODE + 14 	/* Retries exceeded 
					              	 * call not completed  
						      	 */
#define HDLC_NO_CABLE		NDD_REASON_CODE + 15	/* No cable detected */
#define HDLC_RDY_TO_DIAL	NDD_REASON_CODE + 16	/* Ready to dial */
#define HDLC_V25B_PROTOCOL_ERR  NDD_REASON_CODE + 17    
#define HDLC_RCV_INC_CALL	NDD_REASON_CODE + 18	/* incoming call rcvd */
#define HDLC_INV_V25B_CMD	NDD_REASON_CODE + 19    /* V25bis command sent
							 * to modem was invalid
							 */
#define HDLC_V25BIS_CFI		NDD_REASON_CODE + 20	/* Call failure
							 * indication 
							 * (V25bis 108.2) 
							 * option[1] contains
							 * modem error code.
							 */
/*
 * These error codes are used in the NDD_STATUS asynchronous status block
 * option[0] as reason of the NDD_STATUS status block. 
 */
#define	HDLC_DSR_DROPPED	NDD_REASON_CODE + 21
#define	HDLC_RCV_TIMEOUT	NDD_REASON_CODE + 22
#define HDLC_X21_INVALID_CPS    NDD_REASON_CODE + 23
#define HDLC_NOBUFS		NDD_REASON_CODE + 24	/* buffer/memory not 
							 * available 
							 */
#define HDLC_DMA_FAIL		NDD_REASON_CODE + 25	/* DMA operation failed */
#define HDLC_X21_CLEAR		NDD_REASON_CODE + 26	

/*
 * Trace hook numbers 
 */

/* IBM PCI 2-Port Multiprotocol Adapter Hook IDs */
#define HKWD_DPMP_PCI_XMIT	0x3A9		/* transmit events */
#define HKWD_DPMP_PCI_RECV	0x3AA		/* receive events */
#define HKWD_DPMP_PCI_OTHER	0x3AB		/* other events */


/* 
 * HDLC V25bis frame types
 */
#define HDLC_CRN_FRAME  1
#define HDLC_CIC_FRAME  2
#define HDLC_DIC_FRAME  3

#endif  /* _H_CDLI_HDLCUSER */

