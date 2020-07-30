/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/call_ie.h 1.13                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1995,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)99  1.13  src/bos/kernel/sys/call_ie.h, atmsvc, bos530 5/13/02 15:36:00 */
/*
 * COMPONENT_NAME: ATMSVC
 *
 * FUNCTIONS: none.
 *
 * ORIGINS: 27
 *
 *                  -- (                            when
 * combined with the aggregated modules for this product)
 * OBJECT CODE ONLY SOURCE MATERIALS
 *
 * (C) COPYRIGHT International Business Machines Corp. 1995,1998
 * All Rights Reserved
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_CALL_IE
#define _H_CALL_IE



#define  NOT_SPECIFIED_B	0xFF		/* Omit the 1-byte subfield   */
#define  NOT_SPECIFIED_S	0xFFFF		/* Omit the 2-bytes subfield  */
#define  NOT_SPECIFIED_L	0xFFFFFFFF	/* Omit the 4-bytes subfield  */

#define  ATM_ADDR_LEN		20	/* 20 bytes ATM endsystem address     */

struct atm_addr {
	uchar addr[ATM_ADDR_LEN];	/* ATM Endsystem Address/Number */
};
typedef struct atm_addr	atm_addr_t;

struct atm_addr_struct {
	ushort length;
	uchar  plan;
	uchar  address[ 20 ];
        uchar     resvd1;
        uchar     anonymous;
        uchar     screening;
        ushort    resvd2;

};
typedef struct atm_addr_struct atm_addr_struct_t;

/*****************************************************************************/
/*									     */
/*  Information Elements (IE) that are defined by the Call Manager	     */
/*  based on UNI 3.1 Signalling.					     */
/*									     */
/*****************************************************************************/


/*****************************************************************************/
/*   AAL Parameters							     */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/*     aal_5								     */
/*---------------------------------------------------------------------------*/
struct aal_5 {
	ushort  fwd_max_sdu_size;	/* forward max SDU size */
	ushort  bak_max_sdu_size;	/* backward max SDU size */
	ushort  mode;			/* mode */
	uchar  	sscs_type;		/* SSCS type */
};
typedef struct aal_5	aal_5_t;



/*---------------------------------------------------------------------------*/
/*     aal_5_t.mode		     				             */
/*---------------------------------------------------------------------------*/
#define  CM_MESSAGE_MODE    0x0001    /* Message Mode                        */
#define  CM_STREAMING_MODE  0x0002    /* Streaming Mode                      */

/*---------------------------------------------------------------------------*/
/*     aal_5_t.sscs_type		     				     */
/*---------------------------------------------------------------------------*/
#define  CM_NULL_SSCS       0x0000    /* Null                                */
#define  CM_ASSURED         0x0001    /* based on SSCOP (assured operation)  */
#define  CM_NON_ASSURED     0x0002    /* based on SSCOP (non-assured oper.)  */
#define  CM_FRAME_RELAY     0x0004    /* Frame relay SSCS                    */


struct aal_parm {
	short	length;		/* length of actual data in aal_info */
	ushort	aal_type;	/* identify the AAL parameter struct */
	union {
               struct aal_5 	aal5;
	} aal_info;
};
typedef struct aal_parm	aal_parm_t;

/*---------------------------------------------------------------------------*/
/*     aal_parm.aal_type		     				     */
/*---------------------------------------------------------------------------*/
#define CM_AAL_1	0x0001		/* AAL type 1 */
#define	CM_AAL_3_4	0x0002		/* AAL type 3/4 */
#define CM_AAL_5	0x0005		/* AAL type 5 */
#define CM_AAL_U	0x0010		/* User defined AAL */



/*****************************************************************************/
/*   Traffic Descriptor			     				     */
/*****************************************************************************/

struct traffic_des {
	int	fwd_peakrate_hp;   /* in Kbits/sec */
	int  	bak_peakrate_hp;   /* in Kbits/sec */
	int  	fwd_peakrate_lp;   /* in Kbits/sec */
	int 	bak_peakrate_lp;   /* in Kbits/sec */
	int  	fwd_sus_rate_hp;   /* in Kbits/sec */
	int  	bak_sus_rate_hp;   /* in Kbits/sec */
	int  	fwd_sus_rate_lp;   /* in Kbits/sec */
	int  	bak_sus_rate_lp;   /* in Kbits/sec */
	int  	fwd_bur_size_hp;   /* in Bytes     */
	int  	bak_bur_size_hp;   /* in Bytes     */
	int  	fwd_bur_size_lp;   /* in Bytes     */
	int  	bak_bur_size_lp;   /* in Bytes     */
	int  	best_effort;	  /* 0 or 1       */
	int  	tagging_bak;	  /* 0 or 1	  */
	int  	tagging_fwd;	  /* 0 or 1	  */
};
typedef struct traffic_des	traffic_des_t;

#define  CM_MAX_DATA_RATE	0x005FFFFF  /* Maximum data rate in Kb/s */
#define  CM_MAX_BUR_SIZE        0x2FFFFFD0  /* Maximum burst size in bytes */


/*****************************************************************************/
/*   Broadband Bearer Capability			     		     */
/*****************************************************************************/
struct bearer {
	uchar bearer_class;    /* change from uchar to ushort to avoid */
                                /* alignmnet problem                    */
	ushort transfer_cap;
	uchar  clipping;	/* Susceptibility to clipping */
	uchar  connection_cfg;	/* User plane connection configuration*/
                                /* not use by daemon code             */
};
typedef struct bearer	bearer_t;

/*---------------------------------------------------------------------------*/
/*     bearer_t.bearer_class   				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_CLASS_A    0x01   /* Connection Oriented, Constant Bit Rate */
#define  CM_CLASS_C    0x03   /* Connection Oriented, Variable Bit Rate */
#define  CM_CLASS_X    0x10   /* Connection Oriented, User Defined */

/*---------------------------------------------------------------------------*/
/*     bearer_t.traffic_type   				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_CONSTANT_BIT_RATE    0x05   /* Constant bit rate                 */
#define  CM_VARIABLE_BIT_RATE    0x09   /* Variable bit rate                 */

/*---------------------------------------------------------------------------*/
/*     bearer_t.timing         				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_END_TO_END        0x01    /* End to end timing required          */
#define  CM_NO_END_TO_END     0x02    /* End to end timing not required      */

/*---------------------------------------------------------------------------*/
/*     bearer_t.clipping       				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_NOT_SUSCEPTIBLE   0x00    /* Not susceptible to clipping         */
#define  CM_SUSCEPTIBLE       0x01    /* Susceptible to clipping             */

/*---------------------------------------------------------------------------*/
/*     bearer_t.connection_cfg 				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_CON_CFG_PTP		0x00    /* Point to Point		   */
#define  CM_CON_CFG_PTM		0x01    /* Point to Multipoint 		   */


/*****************************************************************************/
/*   Broadband High Layer Information 			     		     */
/*****************************************************************************/

#define CM_BHLI_INFO_SIZE	8	/* size of the High layer information */

struct bhli {
	short length;		/* length of the actual data in info */
	uchar type;		/* High layer information type  */
        uchar resvd;            /* Alignment */
	uchar info[CM_BHLI_INFO_SIZE];	/* High layer information */
};
typedef struct bhli	bhli_t;

/*---------------------------------------------------------------------------*/
/*     bhli_t.type             				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_ISO               0x00   /* ISO                                  */
#define  CM_USER_SPECIFIED    0x01   /* User specific                        */
#define  CM_HI_LAYER_PROFILE  0x02   /* High Layer Profile                   */
#define  CM_VENDOR_SPECIFIC   0x03   /* Vendor Specific Application ID       */


/*****************************************************************************/
/*   Broadband Low Layer Information 			     		     */
/*****************************************************************************/

#define CM_SNAP_OUI_SIZE	3	/* # of bytes in snap_oui */
#define CM_SNAP_PID_SIZE	2	/* # of bytes in snap_pid */

struct blli {
	short  length;		/* size of the blli_t or 0 */
	uchar  L2_prot;		/* Layer 2 protocol */
	uchar  L2_mode;		/* Layer 2 mode of operation */
	uchar  L2_win_size;	/* Layer 2 window size 1 - 127 */
	uchar  L2_info;		/* Layer 2 protocol information */
	uchar  L3_prot;		/* Layer 3 protocol */
	uchar  L3_mode;		/* Layer 3 mode of operation */
	uchar  L3_def_pkt_size;	/* Layer 3 default packet size */
	uchar  L3_pkt_win_size;	/* Layer 3 packet window size 1 - 127 */
	uchar  L3_info;		/* Layer 3 protocol information */
	uchar  ipi;		/* ISO/IEC TR9577 Initial Protocol ID */
	uchar  snap_oui[CM_SNAP_OUI_SIZE]; /* 24-bit Organization Unique ID */
	uchar  snap_pid[CM_SNAP_PID_SIZE]; /* 16-bit protocol ID */
};
typedef struct blli	blli_t;


/*---------------------------------------------------------------------------*/
/*     blli_t.L2_prot          				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_BASIC_MODE_ISO_1745  0x01   /* Basic Mode ISO 1745             */
#define  CM_CCITT_Q921           0x02   /* CCITT Q.921                     */
#define  CM_CCITT_X25_LINK       0x06   /* CCITT X.25 Link Layer           */
#define  CM_CCITT_X25_MULTI_LINK 0x07   /* CCITT X.25 Multi-Link           */
#define  CM_LAPB_EXT_HALF_DUP    0x08   /* Extended LAPB for half duplex   */
#define  CM_HDLC_ARM             0x09   /* HDLC ARM (ISO 4335)             */
#define  CM_HDLC_NRM             0x0A   /* HDLC NRM (ISO 4335)             */
#define  CM_HDLC_ABM             0x0B   /* HDLC ABM (ISO 4335)             */
#define  CM_LAN_LLC_ISO_8802     0x0C   /* LAN LLC (ISO 8802/2)            */
#define  CM_CCITT_X75            0x0D   /* CCITT X.75 (SLP)                */
#define  CM_CCITT_Q922           0x0E   /* CCITT Q.922                     */
#define  CM_L2_PROT_USER         0x10   /* User Specified.                 */
#define  CM_ISO_7776_DTE_DTE     0x11   /* ISO 7776 DTE-DTE oper.          */

/*---------------------------------------------------------------------------*/
/*     blli_t.L2_mode          				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_L2_MODE_NORMAL    0x01   /* Normal Mode                         */
#define  CM_L2_MODE_EXTENDED  0x02   /* Extended Mode                       */

/*---------------------------------------------------------------------------*/
/*     blli_t.L3_prot          				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_CCITT_X25_PACKET  0x06   /* CCITT X.25 Packet layer             */
#define  CM_ISO_8208          0x07   /* ISO/IEC 8208 (X.25 packet)          */
#define  CM_ISO_8878          0x08   /* X.223/ISO 8878                      */
#define  CM_ISO_8473          0x09   /* ISO/IEC 8473 (OSI connectionless.)  */
#define  CM_CCITT_T70         0x0A   /* CCITT T.70 minimum network layer.   */
#define  CM_ISO_9577          0x0B   /* ISO/IEC 9577                        */
#define  CM_L3_PROT_USER      0x10   /* User Specified.                     */

/*---------------------------------------------------------------------------*/
/*     blli_t.L3_mode          				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_L3_MODE_NORMAL    0x01   /* Normal packet sequence numbering    */
#define  CM_L3_MODE_EXTENDED  0x02   /* Extended packet sequence numbering  */

/*---------------------------------------------------------------------------*/
/*     blli_t.L3_def_pkt_size  				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_PKT_16            0x04   /* 16 octets                           */
#define  CM_PKT_32            0x05   /* 32 octets                           */
#define  CM_PKT_64            0x06   /* 64 octets                           */
#define  CM_PKT_128           0x07   /* 128 octets                          */
#define  CM_PKT_256           0x08   /* 256 octets                          */
#define  CM_PKT_512           0x09   /* 512 octets                          */
#define  CM_PKT_1024          0x0A   /* 1024 octets                         */
#define  CM_PKT_2048          0x0B   /* 2048 octets                         */
#define  CM_PKT_4096          0x0C   /* 4096 octets                         */


/*---------------------------------------------------------------------------*/
/*     blli_t.IPI              				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_IPI_SNAP        0x80       /* SNAP protocol                     */
#define  CM_IPI_IP          0xCC       /* IP protocol                       */



/*****************************************************************************/
/*   Calling and Called Party Number 			   		     */
/*****************************************************************************/

struct call_pnum {
	short length;		/* Length of the actual data in the number */
	uchar type;		/* Type of number */
	uchar plan_id;		/* Addressing/Numbering Plan ID */
	uchar pres_ind;		/* Presentation Indicator, only used 
				   for specifying Calling Party Number */
	uchar screening;	/* Screening Indicator, only used 
				   for specifying Calling Party Number */
	atm_addr_t number; 	/* ATM Endsystem Address/Number */
};
typedef struct call_pnum	call_pnum_t;

/*---------------------------------------------------------------------------*/
/*     call_pnum.type      				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_UNKNOWN_ADDR_TYPE	0x00	/* Unknown */
#define  CM_INTL_ADDR_TYPE	0x01	/* International number */

/*---------------------------------------------------------------------------*/
/*     call_pnum.plan_id      				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_E164		0x01   /* E.164 numbering plan */
#define  CM_NSAP	 	0x02   /* ATM Endsystem Address */

/*---------------------------------------------------------------------------*/
/*     call_pnum.pres_ind     				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_PRES_ALLOWED	0x00	/* Presentation allowed  */
#define  CM_PRES_RESTRICTED	0x01	/* Presentation restricted */
#define  CM_PRES_NOT_AVAIL	0x02	/* Number not available */

/*---------------------------------------------------------------------------*/
/*     call_pnum.screening    				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_NO_SCRN		0x00	/* User-provided, not screened */
#define  CM_SCRN_PASS		0x01	/* User-provided, verified and passed */
#define  CM_SCRN_FAIL		0x02	/* User-provided, verified and failed */
#define  CM_SCRN_NET		0x03	/* Network provided */


/*****************************************************************************/
/*   Calling and Called Party Subaddress 		             	     */
/*****************************************************************************/

struct call_psub {
	short length;		/* Length of the actual data in the subaddr */
	uchar type;		/* Type of subaddress */
	atm_addr_t subaddr;	/* Subaddress information */
};
typedef struct call_psub	call_psub_t;

/*---------------------------------------------------------------------------*/
/*     call_psub.type      				     		     */
/*---------------------------------------------------------------------------*/
#define  CM_PSUB_NSAP  		0x00   /* X.213/ISO 8348 AD2)   */
#define  CM_PSUB_ATM		0x01   /* ATM Endsystem address */


/*****************************************************************************/
/*   Connection Identifier           			             	     */
/*****************************************************************************/

struct atm_conn_id {
	ushort vpi;		/* Virtual Path Connection Identifier */
	ushort vci;		/* Virtual Channel Identifier */
};
typedef struct atm_conn_id	atm_conn_id_t;


/*****************************************************************************/
/*   QoS Parameter                   			             	     */
/*****************************************************************************/

struct qos_parm {
	uchar qos_fwd;		/* QoS Class Forward */
	uchar qos_bak;		/* QoS Class Backward */
};
typedef struct qos_parm	qos_parm_t;

/*---------------------------------------------------------------------------*/
/*     qos_parm_t.qos_fwd,  qos_parm_t.qos_bak				     */
/*---------------------------------------------------------------------------*/
#define  CM_QOS_0   0x00  /* QOS class 0 - Unspecified class                */
#define  CM_QOS_1   0x01  /* QOS class 1 - To be defined by switch vendor   */
#define  CM_QOS_2   0x02  /* QOS class 2 - To be defined by switch vendor   */
#define  CM_QOS_3   0x03  /* QOS class 3 - To be defined by switch vendor   */
#define  CM_QOS_4   0x04  /* QOS class 4 - To be defined by switch vendor   */


/*****************************************************************************/
/*   Broadband Sending Complete 					     */
/*****************************************************************************/

#define CM_COMP_IND_SIZE	2	/* # of bytes in comp_ind */

struct bb_sending_comp {
	short	length;		/* length of the comp_ind */
	uchar	comp_ind[CM_COMP_IND_SIZE]; /* Broadband sending complete 
						indication */
};
typedef struct bb_sending_comp	bb_sending_comp_t;


/*****************************************************************************/
/*   Transit Network Selection  					     */
/*****************************************************************************/

#define CM_NET_ID_SIZE	5	/* # of bytes in net_id */

struct transit_sel {
	short	length;		/* length of the net_id */
	uchar	type;		/* Type of network ID */
	uchar	plan;		/* Netowrk ID plan */
	uchar	net_id[CM_NET_ID_SIZE];	/* Network ID */
};
typedef struct transit_sel	transit_sel_t;
	
/*---------------------------------------------------------------------------*/
/*     transit_sel.type						     	     */
/*---------------------------------------------------------------------------*/
#define  CM_TS_NETID_TYPE	0x02	/* National network identification */

/*---------------------------------------------------------------------------*/
/*     transit_sel.plan						     	     */
/*---------------------------------------------------------------------------*/
#define  CM_TS_NETID_PLAN	0x01	/* Carrier Identification Code */


/*****************************************************************************/
/*   Endpoint Reference              			             	     */
/*****************************************************************************/

struct endpoint_ref {
	uchar	type;		/* Endpoint reference type */
	ushort	ref_num;	/* Endpoint reference ID value */
};
typedef struct endpoint_ref	endpoint_ref_t;

/*---------------------------------------------------------------------------*/
/*     endpoint_ref_t.type						     */
/*---------------------------------------------------------------------------*/
#define  CM_EP_TYPE_LOCAL		0x00	/* Locally defined integer */



/*****************************************************************************/
/*   Cause                        			             	     */
/*****************************************************************************/

#define CM_DIAG_SIZE	28	/* size of the diag */

struct cause {
	uchar  cause;		/* Cause value */
	short  length;		/* length of the actual data in diag */
	uchar  diag[CM_DIAG_SIZE];	/* Diagnostics */
};

typedef struct cause	cause_t;

/*---------------------------------------------------------------------------*/
/*     cause_parm.cause         			     		     */
/*---------------------------------------------------------------------------*/
#define  CM_ATM_ADDRESS_UNASSIGNED     1  /* Unassigned Number               */
#define  CM_NO_ROUTE_TO_TRANSIT_NET    2  /* No route to transit network     */
#define  CM_NO_ROUTE_TO_PARTY          3  /* No route to destination         */
#define  CM_VPI_VCI_UNACCEPTABLE      10  /* VPI/VCI Unacceptable UNI30      */
#define  CM_NORMAL_CALL_CLEARING      16  /* Normal call clearing UNI31      */
#define  CM_CALLED_PARTY_BUSY         17  /* User busy                       */
#define  CM_NO_RESPONSE_FROM_PARTY    18  /* No user responding              */
#define  CM_PARTY_REJECTED_CALL       21  /* Call rejected                   */
#define  CM_ATM_ADDRESS_CHANGED       22  /* Number changed                  */
#define  CM_CALLER_ADDR_MANDATORY     23  /* User rjt calls w/o callers addr */
#define  CM_DESTINATION_OUT_OF_ORDER  27  /* Destination out of order        */
#define  CM_INVALID_ATM_ADDRESS       28  /* Invalid/incomplete Number       */
#define  CM_RESPONSE_TO_STATUS_ENQ    30  /* Response to STATUS Enquiry      */
#define  CM_CAUSE_NORMAL              31  /* Normal/Unspecified              */
#define  CM_THIS_VPI_VCI_UNAVAILABLE  35  /* VPCI/VCI not available          */
#define  CM_VPI_VCI_ASSIGNMENT_FAIL   36  /* VPCI/VCI assignment fail UNI31  */
#define  CM_DATA_RATE_NOT_AVAIL_31    37  /* User cell rate not avail UNI31  */
#define  CM_TEMPORARY_FAILURE         41  /* Temporary failure               */
#define  CM_ACCESS_INFO_DISCARDED     43  /* Access information discarded    */
#define  CM_NO_VPI_VCI_AVAILABLE      45  /* No VPI/VCI Available            */
#define  CM_RESOURCE_UNAVAILABLE      47  /* Resource unavail, unspec.       */
#define  CM_QOS_NOT_AVAILABLE         49  /* QOS not Available               */
#define  CM_DATA_RATE_NOT_AVAILABLE   51  /* User cell rate not avail UNI30  */
#define  CM_BEARER_NOT_AUTHORIZED     57  /* Bearer capab. not authorized    */
#define  CM_BEARER_NOT_AVAILABLE      58  /* Bearer cap. not available now   */
#define  CM_SERVICE_NOT_AVAILABLE     63  /* Service or option not avail     */
#define  CM_BEARER_NOT_IMPLEMENTED    65  /* Bearer cap. not implemented     */
#define  CM_UNSUP_TRAFFIC_PARM_MIX    73  /* Unsupp mix of traffic parms     */
#define  CM_UNSUPPORTED_AAL_31        78  /* AAL parms not supported UNI31   */
#define  CM_INVALID_CALL_REFERENCE    81  /* Invalid call ref value          */
#define  CM_VPI_VCI_NONEXISTENT       82  /* channel does not exist          */
#define  CM_INCOMPATIBLE_DESTINATION  88  /* Incompatible destination        */
#define  CM_INVALID_ENDPOINT_REF      89  /* Invalid endpoint reference      */
#define  CM_TRANSIT_NET_NONEXISTENT   91  /* Transit network does not exist  */
#define  CM_ADDPARTY_QUEUE_OVERFLOW   92  /* Too many pending add party's    */
#define  CM_UNSUPPORTED_AAL_PARMS     93  /* AAL parms not supported UNI30   */
#define  CM_MANDATORY_IE_MISSING      96  /* Mandatory IE missing            */
#define  CM_MESSAGE_NOT_IMPLEMENTED   97  /* Message type not implemented    */
#define  CM_IE_NOT_IMPLEMENTED        99  /* IE nonexistent or not impl      */
#define  CM_INVALID_IE_DATA          100  /* Invalid IE contents             */
#define  CM_CALL_STATE_ERROR         101  /* Message/Call state mismatch     */
#define  CM_TIMER_RECOVERY           102  /* Recovery on timer expiry        */
#define  CM_BAD_MESSAGE_LENGTH       104  /* Incorrect Message Length        */
#define  CM_SVC_PROTOCOL_ERROR       111  /* Protocol error, unspecified     */



/*****************************************************************************/
/*									     */
/*  Structures defined for System users interfacing with the Call Manager    */
/*									     */
/*****************************************************************************/

struct call_ks {
	int (*call_reg)();		/* register to Call Manager */
	int (*call_dereg)();		/* de_register from Call Manager */
	int (*call_svc_reg)();		/* SVC registration */
	int (*call_svc_dereg)();	/* SVC de-registration */
	int (*call_connect)();		/* VC connection service */
	int (*call_disconnect)();	/* VC disconnection service */
	int (*call_addparty)();		/* SVC add party service */
	int (*call_dropparty)();	/* SVC drop party service */
	int (*call_ind_accept)();	/* accept SVC call indication */
	int (*get_lecs_list)(); 	/* fetch the LANE ILMI LECS list */
};

typedef struct call_ks	call_ks_t;


struct reg_ie {
	blli_t		reg_blli;	/* Broadband Low Layer Info */
	call_pnum_t	reg_pnum;	/* Called Party Number */
	call_psub_t	reg_psub;	/* Called Party Subaddress */
};

typedef struct reg_ie	reg_ie_t;

#define CM_MAX_BLLI	3	/* max. # of blli in the connect request */


struct connect_ie {
	aal_parm_t        conn_aal_parm;       /* AAL parameter */
	traffic_des_t     conn_traffic_des;    /* Traffic Descriptor */
	bearer_t          conn_bearer;         /* Broadband Bearer Capability */
	bhli_t            conn_bhli;           /* BHLI */
	blli_t            conn_blli[CM_MAX_BLLI]; /* up to 3 BLLI */
	call_pnum_t       conn_called_num;     /* Called Party Number */
	call_psub_t       conn_called_subaddr; /* Called Party Subaddress */
	call_pnum_t       conn_calling_num;    /* Calling Party Number */
	call_psub_t       conn_calling_subaddr;/* Calling Party Subaddress */
	qos_parm_t        conn_qos;            /* QOS parameter */
	bb_sending_comp_t conn_bb_sending_comp;/* Broadband Sending Complete */
	transit_sel_t     conn_transit_sel;    /* Transit Network Selection */
};

typedef struct connect_ie	connect_ie_t;
	
/*---------------------------------------------------------------------------*/
/*     flags used in the call_connect()	     		     		     */
/*---------------------------------------------------------------------------*/
#define CONN_PVC	0x00000001	/* PVC connection request 	     */
#define CONN_SVC	0x00000002	/* SVC point-to point connection 
						request 	     	     */
#define CONN_P2M	0x00000004	/* SVC point-to-multipoint connection
						request			     */


struct addparty_ie {
	aal_parm_t        ap_aal_parm;         /* AAL parameter */
	bhli_t            ap_bhli;             /* BHLI */
	blli_t            ap_blli;             /* BLLI */
	call_pnum_t       ap_called_num;       /* Called Party Number */
	call_psub_t       ap_called_subaddr;   /* Called Party Subaddress */
	call_pnum_t       ap_calling_num;      /* Calling Party Number */
	call_psub_t       ap_calling_subaddr;  /* Calling Party Subaddress */
	transit_sel_t     ap_transit_sel;      /* Transit Network Selection */
	endpoint_ref_t    ap_endpoint_ref;     /* Endpoint Reference */
};

typedef struct addparty_ie	addparty_ie_t;
	

struct dropparty_ie {
	endpoint_ref_t    dp_endpoint_ref;     /* Endpoint Reference */
	cause_t           dp_cause;            /* Cause */
};

typedef struct dropparty_ie	dropparty_ie_t;
	
struct indaccept_ie {
	aal_parm_t        ia_aal_parm;         /* AAL parameter */
	blli_t		  ia_blli;	       /* BLLI */
};

typedef struct indaccept_ie	indaccept_ie_t;


#define MAX_LECS_ADDRS 4
struct LECS_address_list {
  uchar count;
  uchar                 resvd;          /* Alignment */
  atm_addr_struct_t lecs_addr[MAX_LECS_ADDRS];
};
typedef struct LECS_address_list LECS_address_list_t;


/*---------------------------------------------------------------------------*/
/*     status used in the call_status()	     		     		     */
/*---------------------------------------------------------------------------*/
#define CALL_DISCON	0x00000001	/* disconnected by remote endpoint   */
#define CALL_ACK	0x00000002	/* connection confirmed		     */
#define CALL_ACCEPT	0x00000003	/* connection acceptance complete    */
#define CALL_ADDR_REG	0x00000004	/* SVC ATM address registered        */
#define CALL_ADDR_DEREG	0x00000005	/* SVC ATM address de-registered     */
#define CALL_LEAF_DISCON  0x00000006	/* leaf disconnected by network      */
#define CALL_LEAF_ACK	0x00000007	/* leaf connection confirmed	     */
#define ILMI_ADDR_LIST	0x00000008	/* LANE ILMI LECS list complete	     */


#endif /* _H_CALL_IE */
