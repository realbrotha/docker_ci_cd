/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/IbApi.h 1.35.1.23                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2005,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)05	1.35.1.23  src/bos/kernel/sys/IbApi.h, sysxicm, bos53X, x2009_38B1 9/10/09 16:00:56 */
/*****************************************************************************
 * COMPONENT_NAME: sysxicm
 *
 * ORIGINS: 27
 *
 * MODULE: Infiniband: API Control Blocks
 *
 *****************************************************************************/
#ifndef _H_IBAPI
#define _H_IBAPI

#include <sys/types.h>

/* Pack all IB interface structures */
#pragma options align=packed

/* Note: u_longlong_t is 64 bits for both 32 and 64 bit compiles */
typedef u_longlong_t Ib64bit;
typedef u_longlong_t IbHandle_t;
typedef u_longlong_t IbPd_t;

#define IB_MAX_HCA		256	/* Maximum HCA's per LPAR */
#define IB_MAX_PORTS		16	/* Maximum Ports per HCA */
#define IB_MAX_CQ_ENTRIES	65536	/* maximum CQ entries allowed per CQ */
#define IB_MAX_QP_ENTRIES	65536	/* maximum QP entries allowed per QP */
#define IB_MAX_EQ_ENTRIES	1024	/* maximum QP entries allowed per EQ */
#define IB_MAX_ARRAY_SIZE       65536   /* Maximum number of fixed array indexes */

/* Path Record Maximum Packet Payload */
typedef enum {                 /******* Maximum Packet Payload (PMTU) *******/
        IB_PR_PMTU_256          = 1,    /* note: 0 and 6-15 are reserved */
        IB_PR_PMTU_512          = 2,
        IB_PR_PMTU_1024         = 3,
        IB_PR_PMTU_2048         = 4,
        IB_PR_PMTU_4096         = 5
} IbPmtu_t;

/* Path Record MTU Selector */
typedef enum {
	IB_PR_MTU_SEL_GREATER	= 0,	/* Greater than MTU specified */
        IB_PR_MTU_SEL_LESS	= 1,	/* Less than MTU specified */
        IB_PR_MTU_SEL_EXACT	= 2,	/* Exactly the MTU specified */
        IB_PR_MTU_SEL_LARGEST	= 3	/* Largest MTU available */
} IbMTUSelector_t;

/* Multicast Record Syntax */
struct IbMcastRecord {
      uchar	McastGID[16];   	/* Multicast 128-bit Destination GID */
                                        /* being registered */
      uchar	LocalPortGID[16];	/* Local port GID to accept the */
                                        /*  multicast packets */
      uint	McastQkey;      	/* Q_KEY to be used by this */
                                        /* multicast group */
      uint	McastLID	: 16;	/* Multicast LID assigned by SA */
      uint	Reserved1	: 2;
      uint      Pmtu		: 6;	/* See Path Record Maximum Packet */
      uint	TrafficClass	: 8;	/* Ipv6 Traffic Class */
      uint	Pkey		: 16;	/* P_Key of the multicast partition */
      uint	Reserved2	: 2;
      uint	PacketRate	: 6;	/* See Path Record Rate */
      uint	Reserved3	: 2;
      uint	PktLifetime	: 6;	/* Packet lifetime
					   (4.096 * 2**PktLifetime usec) */
      uint	ServiceLevel	: 4;	/* Ipv6 Service Level */
      uint	FlowLabel	: 20;	/* Ipv6 Flow Label */
      uint	HopLimit	: 8;	/* Hop Limit */
      uint      Scope	        : 4;	/* See Multicast Address Scope syntax*/
      uint      JoinStatus      : 4;	/* See Join Multicast Status Syntax */
      uint	Reserved4	: 24;
};
typedef struct IbMcastRecord IbMcastRecord_t;

/* Path Record Syntax */
struct IbPathRecord {
	uint	Reserved1;
	uint	Reserved2;
	uchar	RemoteGID[16];		/* Remote port's GID */
	uchar	LocalGID[16];		/* Local port's GID */
        ushort	RemoteLID;		/* Remote LID */
        ushort	LocalLID;		/* Local LID */

	uint	Reserved3	: 4;
	uint	FlowLabel	: 20;	/* Ipv6 Flow label */
	uint	HopLimit	: 8;	/* Hop limit */

	uint	TrafficClass	: 8;	/* Ipv6 Traffic class */
	uint	Reversible	: 1;	/* 1=path is reversible */
	uint	NumbPath	: 7;	/* Number of paths being requested
					   on a IbPathFind query */
	uint	Pkey		: 16;	/* Partition key */
	uint	Reserved5	: 12;
	uint	ServiceLevel	: 4;	/* Ipv6 Service level */
        uint    MtuSelector     : 2;    /* See Path Record MTU Selector */
	uint    Mtu		: 6;	/* See Path Record Max Packet Payload */
	uint	RateSelector	: 2;	/* See Path Record Rate Selector */
	uint	PacketRate	: 6;	/* See Path Record Rate  */
	uint	PktLifetimeSel 	: 2;	/* See Path Record Packet Lifetime */
                                        /*    Selector */
	uint	PktLifetime	: 6;	/* Packet lifetime: 4.096 * 2 */
                                        /*    pkt_lifetime usec */
	uint	Reserved6	: 24;
};
typedef struct IbPathRecord IbPathRecord_t;

/* Note: The number inside a bracket in the following comment areas indicates
 *       the number of available least significant bits for that attribute.
 *       Any non-zero value of bits exceeding this range declares the attribute
 *       invalid.  Also, the adapter in use may or may not support the full
 *       number of bits available.
 */

/*------ Connection Mode Address Vector (RC and UC transports only) -----*/
struct AddressVector {
	uint 	ServiceLevel;	/* [4] Ipv6 Service level */
      	uint 	SendGRHFlag;	/* [1] Send Global Routing Header Flag */
      	uint 	RetryCount;	/* [3] retry count */
      	uint 	Timeout;	/* [5] ACK Timeout (4.096 * 2**Timeout) */
      	uint 	PathMTU;	/* [8] Path MTU */
      	uint 	MaxStaticRate;	/* [8] Maximum static rate (also IpDelay) */
      	uint 	DestLid;	/* [16] Destintion LID  */
      	uint 	RNRRetryCount;	/* [3] RNR retry count */
      	uint 	SourcePathBits;	/* [7] Source Path bits (value must fit within
				       the port's LID mask control (LMC) */
};
typedef struct AddressVector AddressVector_t;

/* Connection Mode Global Route Header */
struct GRHeader {
      uint 	TrafficClass;	/* [8] Ipv6 Traffic Class */
      uint 	HopLimit;	/* [8] Hop limit */
      uint 	SourceGIDIndex;	/* [8] Source GID Index */  	
      uint 	FlowLabel;	/* [20] Ipv6 Flow label */
      uint 	Reserve1;
      uint 	DestGID[4];	/* [128] Destination GID */
};
typedef struct GRHeader GRHeader_t;

typedef enum {                 /*------ RDMA Control Bit Mask ------*/
  IB_RDMA_CTL_READ    = 1,    /* Enable RDMA Read Operations */
  IB_RDMA_CTL_WRITE   = 2,    /* Enable RDMA Write Operations */
  IB_RDMA_CTL_ATOMIC  = 4     /* Enable Atomic Operations */
} IbRdmaCtl_t;


typedef enum {                 /*------------- QP State -------------*/
  IB_QP_STATE_RES0   = 0,     /* (reserved)                         */
  IB_QP_STATE_RESET  = 1,     /* Reset                              */
  IB_QP_STATE_INIT   = 2,     /* Initialized                        */
  IB_QP_STATE_RTR    = 3,     /* Ready To Receive                   */
  IB_QP_STATE_RES4   = 4,     /* (reserved)                         */
  IB_QP_STATE_RTS    = 5,     /* Ready To Send                      */
  IB_QP_STATE_SQDG   = 6,     /* Send Queue Draining                */
  IB_QP_STATE_SQD    = 7,     /* Send Queue Drained                 */
  IB_QP_STATE_SQE    = 8,     /* Send Queue Error                   */
  IB_QP_STATE_ERROR  = 0x80   /* Error - Tx and Rx disabled         */
} IbQpState_t;


typedef enum {                 /*------- Path Migration State -------*/
  IB_PM_STATE_NO_OP   = 0,    /* (reserved)                         */
  IB_PM_STATE_MIG     = 1,    /* Migrated                           */
  IB_PM_STATE_REARM   = 2,    /* Rearm                              */
  IB_PM_STATE_ARMED   = 3     /* Armed                              */
} IbPathMigState_t;


typedef enum {                 /*------ RNR NAK Timer Encodes -------*/
  IB_RNR_NAK_655360   = 0,    /* 655.36 msec                        */
  IB_RNR_NAK_10       = 1,    /* 0.01 msec                          */
  IB_RNR_NAK_20       = 2,    /* 0.02 msec                          */
  IB_RNR_NAK_30       = 3,    /* 0.03 msec                          */
  IB_RNR_NAK_40       = 4,    /* 0.04 msec                          */
  IB_RNR_NAK_60       = 5,    /* 0.06 msec                          */
  IB_RNR_NAK_80       = 6,    /* 0.08 msec                          */
  IB_RNR_NAK_120      = 7,    /* 0.12 msec                          */
  IB_RNR_NAK_160      = 8,    /* 0.16 msec                          */
  IB_RNR_NAK_240      = 9,    /* 0.24 msec                          */
  IB_RNR_NAK_320      = 10,   /* 0.32 msec                          */
  IB_RNR_NAK_480      = 11,   /* 0.48 msec                          */
  IB_RNR_NAK_640      = 12,   /* 0.64 msec                          */
  IB_RNR_NAK_960      = 13,   /* 0.96 msec                          */
  IB_RNR_NAK_1280     = 14,   /* 1.28 msec                          */
  IB_RNR_NAK_1920     = 15,   /* 1.92 msec                          */
  IB_RNR_NAK_2560     = 16,   /* 2.56 msec                          */
  IB_RNR_NAK_3840     = 17,   /* 3.84 msec                          */
  IB_RNR_NAK_5120     = 18,   /* 5.12 msec                          */
  IB_RNR_NAK_7680     = 19,   /* 7.68 msec                          */
  IB_RNR_NAK_10240    = 20,   /* 10.24 msec                         */
  IB_RNR_NAK_15360    = 21,   /* 15.36 msec                         */
  IB_RNR_NAK_20480    = 22,   /* 20.48 msec                         */
  IB_RNR_NAK_30720    = 23,   /* 30.72 msec                         */
  IB_RNR_NAK_40960    = 24,   /* 40.96 msec                         */
  IB_RNR_NAK_61440    = 25,   /* 61.44 msec                         */
  IB_RNR_NAK_81920    = 26,   /* 81.92 msec                         */
  IB_RNR_NAK_122880   = 27,   /* 122.88 msec                        */
  IB_RNR_NAK_163840   = 28,   /* 163.84 msec                        */
  IB_RNR_NAK_245760   = 29,   /* 245.76 msec                        */
  IB_RNR_NAK_327680   = 30,   /* 327.68 msec                        */
  IB_RNR_NAK_491520   = 31    /* 491.52 msec                        */
} IbMinRnrNakTimer_t;


struct IbQpCtlBlk {
      uint		Qkey;	
      uint		RDDomain;	    /* Reliable datagram domain */
      uint		SendPsn;       	    /* [24] send PSN */
      uint		RcvPsn;             /* [24] receive PSN */
      uint		PriPhyPort;         /* [8] primary physical port */
      uint		AltPhyPort;         /* [8] alternate physical port */
      uint		PriPkeyIndex; 	    /* [8] primary PKEY index */
      uint		AltPkeyIndex; 	    /* [8] Alternate PKEY index  */
      IbRdmaCtl_t	RdmaCtl;            /* [3] RDMA/Atomic control */
      IbQpState_t	QpState;     	    /* [8] QP state */
      uint		Res10;              /* Reserved */
      uint		RdmaRespResource;   /* # of responder resources for
					       incoming RDMA/Atomic operations.
					       (must fit within InOpsQpMax) */
      IbPathMigState_t	PathMigState;       /* [2] Path migration state */
      uint		RdmaOutstanding;    /* # of RDMA/Atomic outstanding at
					       Destination QP. (must fit within
					       OutOpsQpMax) */
      uint		DestQpNumber;       /* [24] Destination Qp Number */
      IbMinRnrNakTimer_t RnrNakTimer; 	    /* [5] Min. RNR Nak Timer Field
						value */
      AddressVector_t 	PriAV;              /* Primary Address Vector */
      GRHeader_t	PriGRHeader;        /* Primary Global routing header */
      AddressVector_t 	AltAV;              /* Alternate Address Vector */
      GRHeader_t	AltGRHeader;        /* Alternate Global routing header*/
      uint		MaxOutstandingSend; /* [16] MAX# outstanding Send
						work requests */
      uint		MaxOutstandingRecv; /* [16] MAX# outstanding Receive
						work requests */
      uint		Res54;              /* Reserved for Disable ETE Credit
						Checking */
      uint		QpNumber;	    /* [8] QP number */
      Ib64bit		SendQueCqHandle;    /* [64] Send queue CQ handle */
      Ib64bit		RecQueCqHandle;     /* [64] Receive queue CQ handle */
      uint		BufInSendWQE; 	    /* [8] Actual number of scatter
						gather elements in send queue
						WQE */
      uint		BufInRecWQE;        /* [8] Actual number of scatter
						gather elements in receive
						queue WQE   */
      uint		Res62;              /* Reserved for QP Enable */
      uint		Res63;              /* Reserved for Current SRQ Limit */
      Ib64bit		Res64_65;           /* Reserved for QPx_AAELOG */
      Ib64bit		Res66_67;           /* Reserved for Shared Receive QP
						Handle */
      Ib64bit		Res68_69;           /* Reserved for Triggered DB QP
						Handle */
      uint	        QpCtlSubMask;	    /* byte 70 - submask for QP special control */
#define  SubMaskDelayAck 0x00000001         /* bit 0 is to control delay ack bit in byte 71 */
      uint       	QpSpControl;        /* QP special control */
#define QpDelayAck       0x00000001         /* bit 0 is delay ack bit */
      uint		Res70_127[56];      /* byte 72 to 127 */
};
typedef struct IbQpCtlBlk IbQpCtlBlk_t;

/*  IB Node Information */
struct IbNodeInfo {
				/* --- Vendor Info --- */
	uint	VendorID;	/* Device vendor, IEEE Vendor ID */
	ushort	PartID;		/* Manufacturer device ID */
	uint	HwVersion;	/* Manufacturer device revision */
				/* --- Node info --- */
	uint	NumPorts;	/* Number of physical ports on this HCA */
	uint	PartitionsMax;	/* Maximum number of partitions (Pkeys) */
	uint	LocalAckDelay;  /* Local acknowlegement delay in nsec */
	char	NodeGUID[8];	/* Node's EUI-64 Global Unique Identifier */

					 /* --- Node's Ability Mask --- */
	uint	AutoPathMigration_f : 1; /* Supports auto path migration 1=yes*/
	uint	BadPkeyCtr_f	    : 1; /* To Count P-Key violations, 1=yes */
	uint	BadQkeyCtr_f        : 1; /* To count Q-Key violations, 1=yes */
	uint	CanModifyQpSize_f   : 1; /* To alter QP's max depth, 1=yes */
	uint	PortActiveEvent_f   : 1; /* Supports port active eventi */
                                         /*    notification, 1=yes */
	uint	QpStateRTS_f        : 1; /* Allows QP State change to RTS */
                                         /*    on Modify QP, 1=yes */
 	uint	RawMcastSupport_f   : 1; /* Supports raw packet mcast, set=0 */
 	uint	AddrHandlePortCk_f  : 1; /* Address handle port number  */
                                         /*    checking, set=0 */
 	uint	AtomicSupport_f	    : 1; /* Supports atomic operations, set=0 */
 	uint	InitType_f	    : 1; /* Supports setting InitType, set=0 */
 	uint	PortShutdown_f	    : 1; /* Shutdown port capability , set=0 */
 	uint	PriPortChange_f	    : 1; /* Primary port change on SQD to RTS */
                                         /*    , set=0 */
 	uint	SysImageGUID_f	    : 1; /* System image GUID support, set=0 */
        uint    LLQP_f              : 1; /* Low latency QP */
        uint    SRQ_f               : 1; /* shared Receive Queue */
        uint    LLUDQP_f            : 1; /* Low latency UD QP */
        uint    QpDelayAck_f        : 1; /* QP delay Ack option, yes = 1 */
        uint    Reserved01           : 15;
					/* --- Queue Pair Info --- */
	uint    QpMax;		   /* Max number of Queue Pairs */
	uint    WrkReqMax;	   /* Max number of outstanding work requests */
	uint    ScatterGatherMax;  /* Max scatter/gather entries per  */
                                   /*     WQE(non-RD) */
 	uint    RawIpQpMax;	   /* Max Raw IPv6 Datagram QP's */
 	uint    RawEthertypeQpMax; /* Max Raw Ethertype QP's */
					/* --- End-to-End Context Info --- */
 	uint	EecMax;		    /* Max number of End-to-End Contexts */
 	uint	ScatterGatherRdMax; /* Max scatter/gather entries per RD RQ */
 	uint	RddMax;		    /* Max number of Reliable Datagram Domains*/

					/* --- Completion Queue Info --- */
 	uint	CqMax;		    /* Max Completion Queues */
	uint	CqEntriesMax;	    /* Max entries per CQ */

					/* --- Multicast Info --- */
	uint	McastGroupsMax;	      /* Max multicast groups */
	uint	QpsTotalMcastGrpsMax; /* Max QP's in all the mcast groups */
	uint	QpsPerMcastGroupMax;  /* Max QP's per single mcast group */

 					/* --- Protection Domain Info --- */
	uint	PdMax;		      /* Max protection Domains */

					/* --- Address Handle Info --- */
	uint	AddrHandlesMax;	      /* Max Address Handles */

					/* --- Memory Region Info --- */
	uint	RegionsMax; 	      /* Max Memory Regions */
	uint	BlockBytesMax;	      /* Largest contiguous memory block */
	uint	PageSize;	      /* Memory page size */
	uint	MemWindowsMax;	      /* Max memory windows */
					/* --- Remote DMA Info --- */
	uint	InOpsHcaMax;	/* Max HCA depth for incoming RDMA reads */
	uint	InOpsQpMax;	/* Max depth per QP for incoming RDMA reads   */
	uint	OutOpsQpMax;	/* Max depth per QP to initiate RDMA reads */
 	uint	InOpsEecMax;	/* Max depth per EE for incoming RDMA reads   */
 	uint	OutOpsEecMax;	/* Max depth per EE to initiate RDMA reads */
};
typedef struct IbNodeInfo IbNodeInfo_t;

/* IB port Information  */
/* Design Note - this structure is a mix of what's provided by the RPA and
		 what's specified in 14.2.5.6 PortInfo */
struct IbPortInfo {
	Ib64bit	GidPrefix;		/* GID prefix for this port */
	uint	LID		:16;	/* Local ID (LID) */
	uint	MasterSMLID	:16;	/* Subnet Manager LID */
						/* --- Capability Mask --- */
	uint	Reserved0	: 1;
	uint	IsSM		: 1;	/* 1 = Is a subnet manager */
	uint    PhyPrtWidth     : 8;    /* Physical port width */
	uint	IsSMdisabled	: 1;    /* 1 = Subnet manager is disabled */
	uint	Reserved2	: 1;
	uint    PhyPrtPhyState  : 4;    /* Physical port physical state */
	uint	IsCMSupported	: 1;	/* 1 = Communication Mgr is supported */
	uint	IsSNMPTunneling	: 1;	/* 1 = SNMP Tunneling is supported */
	uint	Reserved3	: 1;
	uint	IsDMSupported	: 1;	/* 1 = Device management is supported */
	uint	IsVendorClass	: 1;	/* 1 = Vendor class is supported */
	uint    PhyPrtState     : 4;    /* Physical port state */
	uint    PhyPrtSpd       : 4;    /* Physical port speed */
	uint	Reserved4	: 3;
	uint	PortState	: 4;	/* Port state */
	uint	LMC		: 3;	/* LID Mask Control count (where
					   value = 2**LMC) */	
	uint	SubnetTimeOut	: 5;	/* Subnet timeout value based on
                                           4.096 usec times 2 SubnetTimeOut */
	uint	MasterSMSL	: 4;	/* Ipv6 Service level of master SM */
	uint	InitTypeReply	: 4;	/* Init Type Reply mask value */
	uint	MtuCap		: 4;	/* Maximum transmission unit capacity
					   (see MtuCap definition) */
	uint	VLCap		: 4;	/* Virtual Lanes Capacity
					   (see VLCap definition) */
	uint	Reserved5	: 4;
	uint	PkeyViolations	:16;	/* Current P_Key violations */
	uint	QkeyViolations	:16;	/* Current Q_Key violations */
						/* --- PKey List --- */
	uint    NumPkeys;		/* Current number of P_Keys */
	ushort  Pkey[32];		/* PKey Table (IB Arch 14.2.5.7) */
						/* --- GUID List --- */
	uint    NumGUIDs;		/* Current number of Global IDs */
	Ib64bit GUID[8];		/* GUIDInfo (IB Arch 14.2.5.5) */
};
typedef struct IbPortInfo IbPortInfo_t;

typedef enum {
	IB_ACCESS_LOCAL_WRITE	= 0x00800000,
	IB_ACCESS_REMOTE_WRITE	= 0x00400000,
	IB_ACCESS_REMOTE_READ	= 0x00200000,
	IB_ACCESS_REMOTE_ATOMIC	= 0x00100000,
	IB_ACCESS_BIND_MW	= 0x00080000
} IbAccessCtrl_t;

/*------ Unreliable Datagram Global Route Header ------*/
struct IbGRH
{
        uint    IpVersion       : 4;    /* version of the GRH */
        uint    TrafficClass    : 8;    /* Ipv6 Traffic Class */
        uint    FlowLabel       :20;    /* Ipv6 Flow Label */

        uint    PayloadLen      :16;    /* Payload length */
        uint    NextHdr         : 8;    /* Next header following the GRH */
        uint    HopLimit        : 8;    /* Hop limit */

        uint    SrcGIDIndex;		/* Source GID Index (identifies SGID) */
        uchar   Reserved[12];		/* Reserve for remainder of full SGID */
        uchar   DestGID[16];            /* 128-bit Destination GID */
};
typedef struct IbGRH IbGRH_t;

/*------ Unreliable Datagram Address Vector ------*/
struct IbAddrVector
{
        uint    Reserved1    : 4;
        uint    SvcLevel     : 4;   /* Ipv6 Service Level */
        uint    Reserved2    : 7;
        uint    GrhPresent   : 1;   /* Global Routing Header is present */
        uint    DLid         :16;   /* Destination Local ID */

        uint    Reserved3    :25;
        uint    SrcLidPath   :07;   /* Source LID path bits */

        uint    Reserved4    : 8;
        uint    IpDelay      : 8;   /* Inter packet delay (also Static Rate) */
        uint    Reserved5    : 8;
        uint    Reserved6    : 8;   /* REQUIREDR for PMTU  !!!!!*/

        uint    Reserved7;
        Ib64bit Reserved8;
        IbGRH_t Grh;                /* See UD global route header */
};
typedef struct IbAddrVector IbAddrVector_t;

union IbUdRemoteAddr
{
	IbHandle_t	AddrHandle;	/* User's address handle */
	IbAddrVector_t	IbAddrVector;	/* Subsystem address vector
					   (internal use only) */
};
typedef union IbUdRemoteAddr IbUdRemoteAddr_t;
	
/* SIDR_REP status field */
typedef enum {
  IB_SIDR_VALID		= 0,	/* QPN and Q_key are valid */
  IB_SIDR_SID_NOT_SUPP	= 1,	/* Service ID not supported */
  IB_SIDR_REJECTED	= 2,	/* Rejected by the service provider */
  IB_SIDR_NO_QP		= 3,	/* No queue pair is available */
  IB_SIDR_REDIRECT	= 4,	/* Request should be redirected to
					classPortinfo Structure in additional
					data area */
  IB_SIDR_BAD_VERSION	= 5	/* ClassVersion is not supported, see highest
					supported version in additional data
					area */
} IbSidrRepStatus_t;

/*------ Completion Queue Element (CQE) Structure ------*/
struct IbCqEvent
{
	struct IbCqEvent *pNext;	/* Pointer to next CQE in chain */
	Ib64bit	WrkReqId;		/* User defined work request id */
	uint	OpType		: 8;	/* See Send/receive  Operation Types */
	uint	WrkCmplFlgs	: 8;	/* See CQE Work Completion Flags  */
	uint	Reserved1	:16;
	uint	BytesXfered;		/* Number of bytes transfered */
	uint	ImmedData;		/* Immediate data field */

	uint	Reserved2	: 8;
	uint	LocalQpn	:24;	/* Local queue pair number */
	uint	Reserved3	:12;
	uint	SvcLevel	: 4;	/* Ipv6 Service level */
	uint	WqeCount	:16;	/* Count of WQE processed on this SQ */
				        /*   since last CQE generated */
	uint	QpToken;		/* QP token */
	uint	QKey;			/* Q_Key */

	uint	Reserved4	: 8;
	uint	RemoteQpn	:24;	/* Remote QP number (datagram only) */
	uint	DestLID		:16;	/* Destination local ID (UD only) */
	uint	RemoteLID	:16;	/* Remote local ID (datagram only) */
	uint	Reserved5	:16;
	uint	PkeyOrIndex	:16;	/* P_Key or P_Key index, based on */
				        /*   P_Key Mode */
	uint	Timestamp;		/* CQE timestamp of WQE's 1st packet */
	uint	WqeTimestamp;		/* WQE Timestamp */
	uint	TimestampValid_f: 1;	/* 1= WQE timestamp is valid */
	uint	Reserved6	:23;
	uint	CqeValid_f	: 1;	/* CQE valid toggle bit */
	uint	Reserved7	: 7;
	uint	ErrorStatus	: 1;	/* Status: completed with error */
	uint	Reserved8	:19;
	uint	NakCode		:05;	/* NAK code received */
		#define IB_CQE_NAK_PSN    0	/* PSN sequence error */
		#define IB_CQE_NAK_INV_RQ 1	/* Invalid request */
		#define IB_CQE_NAK_ACCESS 2	/* Remote access error */
		#define IB_CQE_NAK_OP 	  3	/* Remote operation error */
		#define IB_CQE_NAK_INV_RD 4	/* Invalid RD request */
	uint	PktSent		: 1;	/* 1= packet sent on link */
	uint	ErrorType	: 6;	/* error types */
		/*------ error types for send queues ------*/
		#define IB_SQ_ERR_LOCAL_LENGTH	0x01 /* local length */
		#define IB_SQ_ERR_LOCAL_QP_OP	0x02 /* local QP operation*/
		#define IB_SQ_ERR_LOCAL_PROT	0x04 /* local protection */
		#define IB_SQ_ERR_WQE_FLUSHED	0x05 /* WQE flushed */
		#define IB_SQ_ERR_MW_BIND	0x06 /* Mem window bind */
		#define IB_SQ_ERR_REMOTE	0x07 /* See NAK code */
		#define IB_SQ_ERR_RETRIES	0x08 /* Transport retries */
		#define IB_SQ_ERR_RNR_NAK	0x09 /* RNR NAK retries */
		#define IB_SQ_ERR_ABORTED	0x0A /* Remote aborted */
		#define IB_SQ_ERR_BAD_RSP	0x0D /* Bad response */
		#define IB_SQ_ERR_WQE_PURGED	0x10 /* WQE purged */
		/*------ error types for receive queues ------*/
		#define IB_RQ_ERR_LOCAL_LENGTH	0x21 /* local length */
		#define IB_RQ_ERR_LOCAL_QP_OP	0x22 /* local QP operation*/
		#define IB_RQ_ERR_LOCAL_PROT	0x24 /* local protection */
		#define IB_RQ_ERR_WQE_FLUSHED	0x25 /* WQE flushed */
		#define IB_RQ_ERR_ABORTED	0x2D /* Remote aborted */
};
typedef struct IbCqEvent IbCqEvent_t;

/* Other Structures ************************************************/

/* Failover Accept Flags */
typedef enum {
  IB_FAILOVER_ACK  = 0,	/* Failover accepted */
  IB_FAILOVER_REJ1 = 1,	/* Failover port rejected, alternate path was not
			   Checked */
  IB_FAILOVER_REJ2 = 2	/* Failover supported, alternate path was ok, but
			   Failover port rejected */
} IbFailover_t;

/* Reject Message Type Syntax */
typedef enum {			/*************** Message Type ****************/
	IB_REJ_TYPE_REQ		= 0,		/* Request */
	IB_REJ_TYPE_REP		= 1,		/* Reply */
	IB_REJ_TYPE_UNKNOWN	= 2		/* Unknown or No Message */
} IbRejMsgType_t;

/* Reject Reason code */
typedef enum {
				/******* Additional Reject Information *******/
  IB_RC_NO_QP_AVAIL		= 1,
  IB_RC_NO_EEC_AVAIL		= 2,
  IB_RC_NO_RESOURCES		= 3,
  IB_RC_TIMEOUT			= 4,	/* REJ sender's port GUID */
  IB_RC_UNSUPPORTED_REQ		= 5,
  IB_RC_INV_COMM_ID		= 6,
  IB_RC_INV_COMM_INSTANCE	= 7,
  IB_RC_INV_SERVICE_ID		= 8,
  IB_RC_INV_SERVICE_TYPE  	= 9,
  IB_RC_STALE_CONNECTION	= 10,
  IB_RC_NO_RD_CHANNEL		= 11,
  IB_RC_PRI_REMOTE_GID_REJ	= 12,	/* GID of acceptable primary port */
  IB_RC_PRI_PORT_LID_REJ	= 13,	/* LID of acceptable primary port */
  IB_RC_INV_PRI_SL		= 14,	/* Service level of acceptable
      						   primary port */
  IB_RC_INV_PRI_TRAFFIC_CLASS	= 15,	/* Traffic class of acceptable
      							   primary port */
  IB_RC_INV_PRI_HOP_LIMIT	= 16,	/* Hop limit of acceptable primary
      							   port */
  IB_RC_INV_PRI_PACKET_RATE	= 17,	/* Minimum acceptable primary packet
      							   rate */
  IB_RC_SEC_REMOTE_GID_REJ	= 18,	/* GID of acceptable secondary port */
  IB_RC_SEC_PORT_LID_REJ	= 19,	/* LID of acceptable secondary port */
  IB_RC_INV_SEC_SL		= 20,	/* Service level of acceptable
      							   secondary port */
  IB_RC_INV_SEC_TRAFFIC_CLASS	= 21,	/* Traffic class of acceptable
      							   secondary port */
  IB_RC_INV_SEC_HOP_LIMIT	= 22,	/* Hop limit of acceptable secondary
      							   port */
  IB_RC_INV_SEC_PACKET_RATE	= 23,	/* Minimum acceptable secodary
      							   packet rate */
  IB_RC_PORT_CM_REDIRECTION	= 24,	/* ClassPortInfo (IB Spec 13.4.8.1) */
  IB_RC_PORT_REDIRECTION	= 25,	/* Proposed GID for new REQ */
  IB_RC_INV_PATH_MTU		= 26,	/* Maximum acceptable MTU */
  IB_RC_INSUF_RESOURCES		= 27,
  IB_RC_CONSUMER_REJ		= 28,	/* User defined data */
  IB_RC_RNR_RETRY_COUNT_REJ	= 29,
  IB_RC_DUP_COMM_ID		= 30,
  IB_RC_INV_CLASS_VERSION	= 31,	/* Highest class version supported */
  IB_RC_INV_PRI_FLOW_LABEL	= 32,	/* Acceptable primary flow label */
  IB_RC_INV_ALT_FLOW_LABEL	= 33,	/* Acceptable alternate flow label */
  IB_RC_NO_PATH                 = 34    /* can not find a Path */
} IbRejReason_t;


/* Subnet Administration Common Status code (IB ARCH 13.4.7) */
#define IB_SA_COM_STAT_BUSY	   0x01 /* Temporarily Busy (non-error) */
#define IB_SA_COM_STAT_REDIRECT	   0x02 /* Redirection Required (non-error) */
#define IB_SA_COM_STAT_VERSION     0x04 /* Bad Version */
#define IB_SA_COM_STAT_METHOD      0x08 /* Method specified is not supported */
#define IB_SA_COM_STAT_METHOD_ATTR 0x0C /* Method/Attribute combination is
					   not supported */
#define IB_SA_COM_STAT_ATTR_MOD    0x1C /* Attribute or modifier invalid */


/* Subnet Administration Class-Specific Status code (IB ARCH 15.2.3) */
typedef enum {
  IB_SA_CS_STAT_NO_ERROR	= 0,	/* No class specific error occurred */
  IB_SA_CS_STAT_NO_RESOURCES	= 1,	/* Insufficient resources */
  IB_SA_CS_STAT_REQ_INV		= 2,	/* Supplied request is invalid */
  IB_SA_CS_STAT_NO_RECORDS	= 3,	/* No records match the query */
  IB_SA_CS_STAT_TOO_MANY	= 4,	/* Too many records match the query */
  IB_SA_CS_STAT_INV_GID		= 5,	/* Invalid GID is SA request */
  IB_SA_CS_STAT_INSUF_COMP	= 6	/* Insufficient required components */
} IbSaSpecStatus_t;


/*****************************************************************************
 * Communication Management Completion Buffers
 *****************************************************************************/
/* Find UD Service Completion Buffer  */
struct IbSvcsFindCmplBuf {
	IbSidrRepStatus_t status;  /* out - See SIDR_REP status field */
	uint	RemoteQkey;	   /* out - Remote service queue key */
	uint	RemoteQPN;	   /* out - Remote service queue pair number */
	uint	AdditionalDataLen; /* out - Length of any additional data */
	uchar	AdditionalData[72];/* out - Additional information area */
	uint	PrivateDataLen;    /* out - Byte length of optional privatei */
                                   /*       data */
	uchar	PrivateData[136];  /* out - Optional private data area */
};

/* Connect Completion Buffer */
struct IbConnectCmplBuf {
	uint	LocalCommID;	/* out - Final local communications ID (May
					 have changed from the initial connect
					 due to a redirect */
	uint	RemoteCommID;	/* out - Remote communications ID */
	uint	RemoteQkey;	/* out - Remote queue key */
	uint	RemoteQPN;	/* out - Remote queue pair number */
	uint	StartingPSN;	/* out - Starting packet sequence number */
	uint	ResponderResources : 8;	/* out - Responder RDMA resources */
	uint	InitiatorDepth	   : 8;	/* out - Initiator RDMA depth */
	uint	TargetAckDelay	   : 5;	/* out - Target ACK delay (value =
					         4.096 * 2**TargetAckDelay) */
	uint    Failover           : 2;	/* out - See Failover Accept Flags */
	uint	EEFlowControl_f	   : 1;	/* out - End to end flow control */
	uint	RNRReadyCount	   : 3;	/* out - RNR ready count */
	uint	Reserved1	   : 4;	
	uint	Reject_f	   : 1;	/* out - Connection rejected flag */
	uint    MsgType	           : 2;	/* out - Message type being rejected */
	uint	Reserved2	   : 6;
	uint	AdditionalDataLen  : 7;	/* out - Reject additional information*/                                               /*       length */
	uint	Reserved3	   : 1;
	uint    ReasonCode	   :16;	/* out - See Reject Reason Syntax */

	uint	RoleType;		/* out - active=1/passive=0 side */
  	uchar	AdditionalData[16];	/* out - Additional Reject Informatio */
  	uchar	PrivateData[196];	/* out - Optional private data area */
	uint	PrivateDataLen;	        /* out - Length of any private data */
};

/* Disconnect Completion Buffer */
struct IbDisconnectCmplBuf {
	uint	RemoteCommID;	        /* out - Remote communications ID */
	uint	RoleType;		/* out - active=1/passive=0 side */
	uint	PrivateDataLen;	        /* out - Length of any private data */
                                        /*  (may be zero) */
	uchar	PrivateData[224];	/* out - Optional private data area */
        uint    LocalCommID;            /* out - Local communications ID */
};

/* Listen Completion Buffer */
struct IbListenCmplBuf {
        IbHandle_t ConnHandle;  /* out - New connection handle */
	uint	RemoteCommID;	/* out - Remote Communications ID */
	Ib64bit	ServiceID;	/* out - Service ID (/etc/services, IANA) */
	uchar	RemoteGID[16];	/* out - Remote port's GID */
	ushort	RemoteLID;	/* out - Remote LID */
	uint	RemoteQPN;	/* out - Remote queue pair number */
	uint	ResponderResources : 8;	/* out-Actual responder RDMA resources*/
	uint	InitiatorDepth	   : 8;	/* out - Actual Initiator RDMA depth */
	uint	TargetAckDelay	   : 8;	/* out - Target ACK delay (value =
					         4.096 * 2**TargetAckDelay) */
	uint	Reserve1	   : 5;
	uint    Failover	   : 2;	/* out -See Failover Accept Flags */
	uint	EEFlowCntl_f	   : 1;	/* out -End-to-end flow control 1=yes */
	uint	RoleType;		/* out - active=1/passive=0 side */
	uint	PrivateDataLen;  /* out-Length of any private data (may be 0) */
  	uchar	PrivateData[92]; /* out-Optional private data area */
};

/* Multicast Join Completion Buffer */
struct IbMcastJoinCmplBuf {
	IbHandle_t McastHandle;	   /* out - ICM's multicast correlator for
					this result */
	char	SaComStatus;       /* out - SA Common Status returned */
	char	SaSpecStatus;      /* out - SA Class-Specific Status returned
						see IbSaSpecStatus_t */
	IbMcastRecord_t McastRecord;
};

/* Multicast Leave Completion Buffer */
struct IbMcastLeaveCmplBuf {
	IbHandle_t McastHandle;	   /* out - ICM's multicast correlator for
					this result */
	char	SaComStatus;       /* out - SA Common Status returned */
	char	SaSpecStatus;      /* out - SA Class-Specific Status returned
						see IbSaSpecStatus_t */
};

/* Multicast Query Completion Buffer */
struct IbMcastQueryCmplBuf {
	IbHandle_t McastHandle;	   /* out - ICM's multicast correlator for
					this result */
	uint	TotalMcastRecords; /* out - Total number of multicast records
					received */
	char	SaComStatus;       /* out - SA Common Status returned */
	char	SaSpecStatus;      /* out - SA Class-Specific Status returned
						see IbSaSpecStatus_t */
	IbMcastRecord_t McastRecord; /* 1st of n Multicast Records.
					Any additional records are obtained via
					IbMcastFetchRecords */
};

/* Multicast Subscription Completion Buffer */
struct IbMcastSubscrCmplBuf {
	uint	McastCreated_f	: 1; /* out - 1=created, 0=deleted  */
	uint	Reserved1	:31;
	uchar	McastGID[16];        /* out - Multicast GID created or
						deleted */
	char	SaComStatus;         /* out - SA Common Status returned */
	char	SaSpecStatus;        /* out - SA Class-Specific Status returned
						see IbSaSpecStatus_t */
};

/* Find Path Completion Buffer */
struct IbPathFindCmplBuf {
	IbHandle_t PathHandle;    /* out - ICM's path correlator for this
						result*/
	uint	TotalPathRecords; /* out - Total number of path records
						received*/
	char	SaComStatus;       /* out - SA Common Status returned */
	char	SaSpecStatus;      /* out - SA Class-Specific Status returned
						see IbSaSpecStatus_t */
	IbPathRecord_t PathRecord; /* 1st of n Path Records.
				      Any additional records are obtained via
				      IbPathFetchRecords */
};

/* MAD Packet Data (APR) */
typedef struct IbMadAprData
{
	uint	LocalCommID;		/* Local Communications ID */
	uint	RemoteCommID;		/* Remote Communications ID */

	uint	InfoLength	: 8;	/* Additional information length */
	uint	ApStatus	: 8;	/* Alternate Path Status: IbAltPath_t */
	uint	Reserved2	:16;

	uchar	AdditionalInfo[72];	/* Additional Information */

	uchar	PrivateData[148];	/* Private Data Area */
} IbMadAprData_t;

/* Load Alternate Path Completion Buffer (APR received) */
struct IbPathAltCmplBuf {
	IbMadAprData_t MadAprData; /* out - See MAD Packet Data (APR)  */
};

/* Connection Ready Buffer  */
struct IbConnReadyBuf {
	IbHandle_t ConnHandle;	  /* out-Connection Handle */
	uint	RoleType;	/* out - active=1/passive=0 side */
	uint	PrivateDataLen;	  /* out-Length of any private data (may be 0)*/
	uchar	PrivateData[224]; /* out-Optional private data area */
};

/* Connection Rejected Buffer */
struct IbConnRejBuf {
	IbHandle_t ConnHandle;		/* out - Connection Handle */
	uint    MsgType	         : 2;	/* out - See Reject Message Type */
	uint	Reserved1	 : 6;
	uint    AdditionalDataLen: 7;	/* out - Reject additional info
						 length */
	uint	Reserved2	 : 1;
	uint    ReasonCode       :16;	/* out - See Reject Reason*/
	uint	RoleType;		/* out - active=1/passive=0 side */
	uchar	AdditionalData[16];	/* out - Additional Reject Info */
	uint	PrivateDataLen;		/* out - Length of any private data
						 (may be zero) */
	uchar	PrivateData[204];	/* out - Optional private data area */
};

/* Disconnect Received Buffer */
struct IbDiscReqRcvdBuf {
	IbHandle_t ConnHandle;		/* out - Connection Handle */
	uint    RemoteQPN;		/* out - Remote Queue Pair Number */
	uint	RoleType;		/* out - active=1/passive=0 side */
	uint	PrivateDataLen;		/* out - Length of any private data
						 (may be zero) */
	uchar	PrivateData[220];	/* out - Optional private data area */
};

/* Connection Terminated Buffer */
struct IbConnTermBuf {
	IbHandle_t ConnHandle;		/* out - Connection Handle */
	uint	RoleType;		/* out - active=1/passive=0 side */
	uint	PrivateDataLen;		/* out - Length of any private data
						 (may be 0) */
	uchar	PrivateData[220];	/* out - Optional private data area */
};

/* Path Migrated Buffer */
struct IbPathMigratedBuf {
	IbHandle_t ConnHandle;		/* out - Connection Handle */
};

/* MAD Packet Data (LAP) */
typedef struct IbMadLapData
{
       uint	LocalCommID;		/* Local Communications ID */
       uint	RemoteCommID;		/* Remote Communications ID */
       uint	Reserved1; 	
       uint	RemoteQpn	: 24;	/* Remote QPN/EECN relative to sender */
       uint	RemoteCmRto	: 5;	/* Remote CM Response Timeout */
       uint	Reserved2	: 3;
       uint	Reserved3;
       uint	AltLocalPortLid	: 16;	/* Alternate local port LID */
       uint	AltRemotePortLid: 16;	/* Alternate remote port LID */
       uchar	AltLocalPortGid[16];	/* Alternate local port GID */
       uchar	AltRemotePortGid[16];	/* Alternate remote port GID */
       
       uint	AltFlowLabel	: 20;	/* Alternate Ipv6 flow label */
       uint	Reserved4	: 4;
       uint	AltTrafficClass	: 8;	/* Alternate Ipv6 traffic class */
       uint	AltHopLimit	: 8;	/* Alternate hop limit */
       uint	Reserved5	: 2;
       uint	AltPacketRate	: 6;	/* Alternate packet rate */
       uint	AltSvcLevel	: 4;	/* Alternate Ipv6 service level */
       uint	AltSameSubnet_f	: 1;	/* 1=Local and Remote on same subnet */
       uint	Reserved6	: 3;
       uint	AltLocalAckTo	: 5;	/* Alternate local ACK timeout
					   (value = 4.096 * 2**AltLocalAckTo) */
       uint	Reserved7	: 3;
       uchar	PrivateData[168];	/* Private Data Area */
} IbMadLapData_t;

/* Load Alternate Path Received Buffer */
struct IbPathAltRcvdBuf {
	IbHandle_t ConnHandle;		/* out - Connection Handle */
	IbMadLapData_t MadLapData;	/* out - See MAD Packet Data (LAP) */
};

/* Completion Timed out Buffer */
struct IbCmplTimeoutBuf {
	uint	LocalCommID;
	uint	RemoteCommID;
	uint	ReasonCode;
	uint	RoleType;		/* out - active=1/passive=0 side */
};

/* Communication Management Event Buffer Types */
union IbCmEventBuf {
					/**** Completion Buffers ****/
	struct IbSvcsFindCmplBuf	SvcsFindCmplBuf;
	struct IbConnectCmplBuf		ConnectCmplBuf;
	struct IbDisconnectCmplBuf	DisconnectCmplBuf;
	struct IbListenCmplBuf		ListenCmplBuf;
	struct IbMcastJoinCmplBuf	McastJoinCmplBuf;
	struct IbMcastLeaveCmplBuf	McastLeaveCmplBuf;
	struct IbMcastQueryCmplBuf	McastQueryCmplBuf;
	struct IbMcastSubscrCmplBuf	McastSubscrCmplBuf;
	struct IbPathFindCmplBuf	PathFindCmplBuf;
	struct IbPathAltCmplBuf		PathAltCmplBuf;
					/**** Non-Completion Buffers ****/
	struct IbConnReadyBuf		ConnReadyBuf;
	struct IbConnRejBuf		ConnRejBuf;
	struct IbDiscReqRcvdBuf		DiscReqRcvdBuf;
	struct IbConnTermBuf		ConnTermBuf;
	struct IbPathMigratedBuf	PathMigratedBuf;
	struct IbPathAltRcvdBuf		PathAltRcvdBuf;
	struct IbCmplTimeoutBuf		CmplTimeoutBuf;
};

/* Communication Management Event Codes */
typedef enum {
					  /**** Completion Codes ****/
        IB_CONNECT_CMPL		= 1,	/* Outgoing connection completion */
        IB_DISCONNECT_CMPL	= 2,	/* Outgoing disconnect completion */
        IB_LISTEN_CMPL		= 3,	/* Listen completion */
	IB_MCAST_JOIN_CMPL	= 4,	/* Join multicast group completion */
	IB_MCAST_LEAVE_CMPL	= 5,	/* Leave multicast group completion */
	IB_MCAST_QUERY_CMPL	= 6,	/* Query multicast group completion */ 
	IB_MCAST_SUBSCR_CMPL	= 7,    /* Subscribe multicast group
                                                completion */ 
	IB_PATH_ALT_CMPL	= 8,	/* Load alternate path completion */
	IB_PATH_FIND_CMPL	= 9,	/* Find path completion */
	IB_SVC_FIND_CMPL	= 10,	/* Find service completion */
						/* (12-50 Reserved) */
	IB_CM_TIMEWAIT_CMPL	= 11,	/* Connctn Mgr:Timewait Time completed*/
					  /**** Non-Completion Codes ****/
	IB_CONN_READY		= 51,	/* Connection is ready for data */
	IB_CONN_REJECTED	= 52,	/* Connection Rejected */
	IB_CONN_TERMINATED	= 53,	/* Connection Terminated */
	IB_PATH_ALT_RCVD	= 54	/* Connection migrated to the 
                                                alternate path */
} IbCmEventCode_t;


/* Communication Management Event Queue Element (EQE) Structure
   for CM and SA events */
struct IbCmEvent {
        Ib64bit UserCmplCorr;		/* out - Users specific request
						completion correlator. Not used
						for non-completion events */
        IbCmEventCode_t EventCode;	/* out - Specific event being
						 notified */
        uint    ResultStatus;		/* out - Completion result status.
						 Not used for non-completion
						 events */
        union IbCmEventBuf EventBuf;	/* out - Buffer area */
};
typedef struct IbCmEvent IbCmEvent_t;


/* structures for API (kernel and user)  */

/******************************************************************************
 * Verb Results (Somewhat alphbetical order)
 *****************************************************************************/
typedef enum{
    IB_RSLT_SUCCESS         =      0, /* Successful */
    IB_RSLT_ACC_CTL_INV     = 0x8001, /* Access control is invalid */
    IB_RSLT_ADDR_INV        = 0x8002, /* Address handle is invalid */
    IB_RSLT_CMPL_TYPE_INV   = 0x8003, /* Completion notification type is
                                                 invalid */
    IB_RSLT_CONN_INV        = 0x8004, /* Connection handle is invalid */
    IB_RSLT_CQ_EMPTY        = 0x8005, /* Completion queue is empty */
    IB_RSLT_CQ_EXCEEDS      = 0x8006, /* Completion queue request exceeds HCA
                                                 capability */
    IB_RSLT_CQ_HAS_QP       = 0x8007, /* One or more queue pairs is still
                                                 associated with the CQ */
    IB_RSLT_CQ_INV          = 0x8008, /* Completion queue handle is invalid */
    IB_RSLT_EQ_EMPTY        = 0x8009, /* Exception queue is empty */
    IB_RSLT_EQ_EXCEEDS      = 0x800A, /* Exception queue request exceeds ICM
                                                 capability */
    IB_RSLT_HCA_INV         = 0x800B, /* HCA handle is invalid */
    IB_RSLT_INSUF_RESOURCE  = 0x800C, /* Insufficient Resources */
    IB_RSLT_LENGTH_INV      = 0x800D, /* Length is invalid */
    IB_RSLT_LKEY_INV        = 0x800E, /* L_Key is invalid */
    IB_RSLT_MCAST_EXCEEDS   = 0x800F, /* Number of QPs attached to multicast
                                                groups exceeded */
    IB_RSLT_MCAST_INV       = 0x8010, /* Multicast handle is invalid */
    IB_RSLT_MGID_INV        = 0x8011, /* Multicast GID is invalid */
    IB_RSLT_MLID_INV        = 0x8012, /* Multicast LID is invalid */
    IB_RSLT_MR_INV          = 0x8013, /* Memory region handle is invalid */
    IB_RSLT_MR_WINDOWS      = 0x8014, /* Memory region has bound windows */
    IB_RSLT_MTU_EXCEEDS     = 0x8015, /* MTU capacity of HCA port exceeded */
    IB_RSLT_MW_INV          = 0x8016, /* Memory window handle is invalid */
    IB_RSLT_NO_ATOMIC       = 0x8017, /* Atomic operations not supported */
    IB_RSLT_NO_EEC          = 0x8018, /* End to end context not supported */
    IB_RSLT_NO_RAW_DGRM     = 0x8019, /* Raw datagrams are not supported */
    IB_RSLT_NO_REL_DGRM     = 0x801A, /* Reliable datagrams not supported */
    IB_RSLT_OFFSET_INV      = 0x801B, /* Offset is invalid */
    IB_RSLT_PD_INV          = 0x801C, /* Protection domain is invalid */
    IB_RSLT_PD_IN_USE       = 0x801D, /* Protection domain is in use */
    IB_RSLT_PHYS_LIST       = 0x801E, /* Physical buffer list is invalid */
    IB_RSLT_PKEY_INV        = 0x801F, /* P_Key index specifies invalid entry
                                                in the P_Key table */
    IB_RSLT_PKEY_RANGE      = 0x8020, /* P_Key index is out of range */
    IB_RSLT_PM_STATE_INV    = 0x8021, /* Path migration state is invalid */
    IB_RSLT_PORT_INV        = 0x8022, /* Port number is invalid */
    IB_RSLT_QP_ATTR         = 0x8023, /* Cannot change QP attribute */
    IB_RSLT_QP_INV          = 0x8024, /* Queue pair handle is invalid */
    IB_RSLT_QP_STATE_INV    = 0x8025, /* Queue pair state is invalid */
    IB_RSLT_RKEY_INV        = 0x8026, /* R_Key is invalid */
    IB_RSLT_RNR_NAK_INV     = 0x8027, /* RNR NAK timer field is invalid */
    IB_RSLT_SG_EXCEEDS      = 0x8028, /* Maximum scatter/gather exceeds HCA
                                                capability */
    IB_RSLT_SG_FORMAT_INV   = 0x8029, /* Invalid scatter/gather list format */
    IB_RSLT_SG_LENGTH_INV   = 0x802A, /* Invalid scatter/gather list length */
    IB_RSLT_SID_INV         = 0x802B, /* Service ID handle is invalid */
    IB_RSLT_SQP_IN_USE      = 0x802C, /* Special queue pair type is already
                                                in use */
    IB_RSLT_SQP_TYPE_INV    = 0x802D, /* Special queue pair type is invalid */
    IB_RSLT_SVC_TYPE_INV    = 0x802E, /* Service type is invalid */
    IB_RSLT_UNKNOWN_FAIL    = 0x802F, /* Unknown failure */
    IB_RSLT_USER_INV        = 0x8030, /* User parameter is invalid */
    IB_RSLT_VADDR_INV       = 0x8031, /* Virtual address is invalid */
    IB_RSLT_WKRQ_EXCEEDS    = 0x8032, /* Maximum work requests exceeds HCA
                                                capability */
    IB_RSLT_WKRQ_INV        = 0x8033, /* Work Request handle is invalid */
    IB_RSLT_WQ_EXCEEDS      = 0x8034, /* More outstanding entries on work
                                                queue than size specified */
    IB_RSLT_TIMEOUT         = 0x8035, /* Failsafe timeout occurred */
    IB_RSLT_TERMINATION     = 0x8036, /* Resource Termination */
    IB_RSLT_WKRQ_INLINE     = 0x8037, /* Inline data size is incorrect */
    IB_RSLT_HCACB_CORRUPTED = 0x8038, /* Hca Control Block corrupted */
    IB_RSLT_CONNCB_CORRUPTD = 0x8039, /* Connection Control Block corrupted */
    IB_RSLT_WKRQ_CORRUPTD   = 0x803A, /* Work Request Control Block corrupted */
    IB_RSLT_USRCB_CORRUPTD  = 0x803B, /* User Control Block corrupted */
    IB_RSLT_CQE_ERR         = 0x803C, /* CQE event has an error */
    IB_RSLT_PKEY_MISMATCH   = 0x803D, /* Partition Key mismatch */
    IB_RSLT_SRVCLVL_MISMATCH= 0x803E, /* Service Level mismatch */
    IB_RSLT_PKTRATE_EXCESSIV= 0x803F, /* Packet rate excessive */
    IB_RSLT_QPCB_CORRUPTED  = 0x8040, /* Packet rate excessive */
    IB_RSLT_UPROC_CORRUPTED = 0x8041, /* Packet rate excessive */
    IB_RSLT_HCA_REG_CMPLT   = 0x8100, /* HCAD registration complete */
    IB_RSLT_HCA_DEREG_CMPLT = 0x8101,  /* HCAD de-registration complete */
    IB_RSLT_AH_INV          = 0x8102  /* Query the AH failed */
} IbVerbResults;


/******************************************************************************
 * Address Handle Control Blocks
 *****************************************************************************/
struct IbAhSizeCb {
        IbHandle_t         HcaHandle;           /* HCA Handle */
        uint               Size;                /* Target Port Number */
};
typedef struct IbAhSizeCb IbAhSizeCb_t;

struct IbAhCreateCb {
	IbHandle_t	   HcaHandle;		/* HCA Handle */
	IbPd_t	       	   PdIn;		/* Protection Domain */
	IbAddrVector_t	   AddrVectorIn;	/* Address Vector */
	uint               PortNumIn;		/* Target Port Number */
	IbHandle_t     	   AddrHandleOut;       /* Returned Address Handle */
};
typedef struct IbAhCreateCb IbAhCreateCb_t;


struct IbAhDestroyCb {
	IbHandle_t         HcaHandle;           /* HCA Handle */
	IbHandle_t         AddrHandleIn;        /* Address Handle */
};
typedef struct IbAhDestroyCb IbAhDestroyCb_t;

struct IbAhModifyCb {
	IbHandle_t         HcaHandle;           /* HCA Handle */
	IbHandle_t         AddrHandleIn;        /* Address Handle */
	IbAddrVector_t     AddrVectorIn;        /* New Address Vector */
	uint               PortNumIn;		/* New Port Number */
};
typedef struct IbAhModifyCb IbAhModifyCb_t;

struct IbAhQueryCb {
	IbHandle_t	   HcaHandle;		/* HCA Handle */
	IbHandle_t	   AddrHandleIn;	/* Address Handle */
	IbPd_t		   PdOut;		/* Returned Protection Domain*/
	IbAddrVector_t	   AddrVectorOut;       /* Returned Address Vector */
	uint               PortNumOut;		/* Returned Port Number */
};
typedef struct IbAhQueryCb IbAhQueryCb_t;

#define IB_MIN_EQ_ENTRIES 64	/* minimum EQE's allowed per EQ */
#define IB_MAX_EQ_ENTRIES 1024	/* maximum EQE's allowed per EQ */

/******************************************************************************
 * Event Handler Control Blocks
 *****************************************************************************/
/* Generic "Set Event Handler" structure for registering Asyncronous and
   Communications Management event handlers. */
struct IbSetHandlerCb {
    IbHandle_t	HcaHandle;	/* HCA Handle */
    uint	NumEntriesIn;	/* Max number of events allowed to be queued
				   for processing. (less than 64: default=64) */
    uint	FailSafeTimeIn; /* Failsafe timeout value in seconds, where
				   a value of zero indicates infinite */
#ifndef __64BIT__
    uint	Res1;
#endif
    void	*pEventFuncIn;  /* Pointer to the user's event handler */
    Ib64bit	UserCorrIn;     /* Opaque user correlator to be returned to
				   the user on each event */
};
typedef struct IbSetHandlerCb IbSetHandlerCb_t;

#define QP_STATE_ERR_USER 0xA0000000  /* QP error due to user Modify */
                                      /*    QP into error state      */

/* Event Queue Element (EQE) structure for asynchronous events:
 * See "Asynchronous Events" for further definition of each EventID */
struct IbEqEvent {
        uint  Reserved1 : 2;            /* Reserved */
        uint  EventID   : 6;            /* Event or error identifier */
        uint  QpCqNum   :24;            /* QP or CQ number */
        uint  ResourceID;               /* Resource identifier */
	uint  SpecificData1;		/* Adapter specific data #1 */
        uint  SpecificData2;            /* use by Galaxy driver to inform */
                                        /* user about EQE QP error        */
                                        /* 0x20000000 = user error        */

};
typedef struct IbEqEvent IbEqEvent_t;

/* User event handler entry point - Event Types */
/* Note: these event types are used for Async EQ, CM EQ, and CQ callback
         notifications */
typedef enum {
    IB_EVENT_CQ_ELEMENT	= 0,	/* This is a CQE notification */
    IB_EVENT_ATTACHED	= 1,	/* This notification has event data attached
				   (not used for CQ notifications) */
    IB_EVENT_TIMEOUT	= 2,	/* A failsafe timeout occurred */
    IB_EVENT_TERM	= 3,	/* The Eq/Cq handler thread will be terminated
				   following the return from this callback */
    IB_EVENT_SA_TIMEOUT = 4,    /* A Subnet Administration timeout occurred */
    IB_EVENT_CM_TIMEOUT = 5,    /* A Connection Management timeout occurred */
    IB_EVENT_CM_QP_RESET= 6     /* Connection Mgmt to set QP to RESET state */

} IbEventTypes_t;

/******************************************************************************
 * Completion Queue Control Blocks
 *****************************************************************************/
struct IbCqCreateCb {
	IbHandle_t    HcaHandle;    /* HCA handle */
	uint          NumEntriesIn; /* Number of CQ entries being requested */
	uint	      NumEntriesOut;/* Returned actual number of CQ entries */
	IbHandle_t    CqHandleOut;  /* Returned CQ Handle */
};
typedef struct IbCqCreateCb IbCqCreateCb_t;

struct IbCqDestroyCb {
	IbHandle_t	HcaHandle;		/* HCA Handle */
	IbHandle_t	CqHandleIn;		/* Completion Queue Handle */
};
typedef struct IbCqDestroyCb IbCqDestroyCb_t;

/* Notification types for IbCqReqNotifyCb and IbCqPollCb */
#define IB_NOTIFY_NONE		0	/* Do not request notification */
#define IB_NOTIFY_ANY		1	/* Notify on any completion event */
#define IB_NOTIFY_SOLICITED	2	/* Notify on solicited events only */

struct IbCqPollCb {
	IbHandle_t	HcaHandle;	/* HCA Handle */
	IbHandle_t	CqHandleIn;	/* Completion Queue Handle */
	uint		NotifyTypeIn;	/* Type of notification to specify
					   when CQ is empty.  Non-zero value
					   indicates that poll-notify-poll is
					   being requested */
	uint		PollType;	/* blocking or non-blocking */
		#define IB_CQ_POLL_NONBLOCK   0
		#define IB_CQ_POLL_BLOCKED    1

	uint		Failsafe;	/* Maximum number of usec to block
					   (Zero indicates infinite) */
	uint		MaxNumCqe;	/* Total number of CQE structs
					   (Must be at least one) */
	uint		RtnNumCqe;	/* Number of CQE's returned */
	IbCqEvent_t	CqEventOut;	/* 1st CQ Event struct in chain */
};
typedef struct IbCqPollCb IbCqPollCb_t;

struct IbCqQueryCb {
	IbHandle_t	HcaHandle;	/* HCA Handle */
	IbHandle_t	CqHandleIn;	/* Completion Queue Handle */
	uint		NumEntriesOut;	/* Returned number of CQ entries */
};
typedef struct IbCqQueryCb IbCqQueryCb_t;

struct IbCqRegHandlerCb {
	IbHandle_t	HcaHandle;	/* HCA Handle */
	IbHandle_t	CqHandleIn;	/* Completion Queue Handle */
	uint		FailSafeTimeIn;	/* Failsafe timeout value in seconds */
					/* a value of zero indicates infinite */
#ifndef __64BIT__
	uint		Res1;
#endif
	void		*pEventFuncIn;	/* Pointer to the user's event handler.
					   (Null indicates registration for
					    blocked CQ polling) */
	Ib64bit		UserCorrIn;	/* Opaque user correlator to be
					   returned to the user on each event */
#ifndef __64BIT__
        uint            Res2;
#endif
	tid_t		TidIn;		/* Thread ID to wake up blocked CQ
					   polls.
					   (Null defaults to pthread_self)
					   (Required for null pEventFuncIn) */
	uint		SignalIn;	/* Signal value to use when waking up
					   blocked CQ polls.
					   (Null defaults to SIGIO)
					   (Required when pEventFuncIn = NULL)*/
};
typedef struct IbCqRegHandlerCb IbCqRegHandlerCb_t;

struct IbCqReqNotifyCb {
	IbHandle_t	HcaHandle;    /* HCA Handle */
	IbHandle_t	CqHandleIn;   /* Completion Queue Handle */
	uint		NotifyTypeIn; /* Type of events to cause notification */
};
typedef struct IbCqReqNotifyCb IbCqReqNotifyCb_t;

struct IbCqResizeCb {
  IbHandle_t	HcaHandle;	/* HCA Handle */
  IbHandle_t	CqHandleIn;	/* Queue Pair Handle */
  uint		NumEntriesIn;	/* Number of entries being requested */
  uint		NumEntriesOut;	/* Pointer to return number of CQ entries */
};
typedef struct IbCqResizeCb IbCqResizeCb_t;

/******************************************************************************
 * Communication Management Control Blocks
 *****************************************************************************/
struct IbConnectCb {
      IbHandle_t HcaHandle;         /* in - Handle of the local HCA */
      Ib64bit	UserCorrelator;	    /* in -Opaque user correlator to be
					returned */
				    /* ICM on asynchronous completion */
      IbHandle_t LocalQpHandle;     /* in - Handle of the local endpoint QP */
      Ib64bit	 TargetServiceID;   /* in (see /etc/services, IANA) */
      IbHandle_t ConnHandle;        /* in/out - Pointer for ICM to synchronously
					return the connection handle */
      uint   PhyPort;               /* Physical port number to use on HCA */

#ifndef __64BIT__
      uint       Res1;
#endif
      IbPathRecord_t *pPathRecord;  /* in - Pointer to optional path record */
#ifndef __64BIT__
      uint       Res2;
#endif
      void   *pPrivateData; 	    /* in - Pointer to optional private data
					area*/
      uint   LenPrivateData;	    /* in - Byte length of optional private
					data (0-92 bytes) */
      uchar  TargetGID[16];         /* in - 128-bit Destination GID (globally
					addressed) */

      uint   TargetLID         :16; /* in - Target LID */
      uint   ManualRTU_f       : 1; /* in - User will manually send the RTU
                                       once connected.  The default is for
                                       ICM to do this automatically */
      uint   ManualMRA_f       : 1; /* in - User will manually send the MRA
                                       A if acknowledgement will be delayed.
                                       Default is automatic ICM MRA */
      uint   DisablePeer_f     : 1; /* in - Connection cannot be peer to peer.
                                       The default is to accept incoming peer
                                       peer to peer REQ's that have the
      			               same Service ID, etc. */
      uint   DisableRedirect_f : 1; /* in -Connection cannot be redirected.
			               The default is to allow up to one
                                       (non-peer) redirection */
      uint   SubnetLocal_f     : 1; /* in - The target node is on the sama
                                       subnet (ie. Only using a LID to
      			               identify the remote. If this flag=0
      				       a target GID must be provided  */
      uint   PathInfo_f        : 1; /* in - The user is providing path
                                       information for this connection.
                                       Default is for ICM to locate a path */
      uint   Reserved1         :10;
      uchar  LocalRnrRetry;         /* Local RNR Retry Count
                                       0 means user didn't pass in a retry
                                       count. 7 means retry forever. 1 - 6
                                       means the number of retires */

};
typedef struct IbConnectCb IbConnectCb_t;

struct IbReadyCb {
        IbHandle_t      HcaHandle;      /* in - Handle of the local HCA */
	IbHandle_t	ConnHandle;     /* in - Handle of the outgoing
                                           connection request */
	uint		LenPrivateData;	/* in - Byte length of optional*/
                                        /* private data */
#ifndef __64BIT__
	uint		Res1;
#endif
	void		*pPrivateData;	/* in - Pointer to optional private */
                                        /* data area */
};
typedef struct IbReadyCb IbReadyCb_t;

struct IbDisconnectCb {
    IbHandle_t  HcaHandle;      /* in - Handle of the local HCA */
    Ib64bit	UserCorrelator;	/* in - Opaque user correlator to be returned
                                        by ICM on asynchronous completion */
    IbHandle_t	ConnHandle;	/* in - Handle of the target connection */
    uint  	LenPrivateData;	/* in - Byte length of optional private data */
#ifndef __64BIT__
    uint	Res1;
#endif
    void  	*pPrivateData;	/* in - Pointer to optional private data area */
};
typedef struct IbDisconnectCb IbDisconnectCb_t;

struct IbListenCb {
    IbHandle_t	HcaHandle;      /* in - Handle of the local HCA */
    Ib64bit	UserCorrelator; /* in - Opaque user correlator to be returned
                                        by ICM on asynchronous  completion */
    Ib64bit	TargetServiceID;/* in - Target Service ID
                                        (see /etc/services, IANA) */
    IbHandle_t	ListenHandle;   /* in/out - Pointer for ICM to synchronously
                                            return the listen handle */
    uint        PhyPort;        /* Physical port number to use on HCA */
    ushort	TargetPkey;     /* in - Target partition key */
    ushort	TargetLID;      /* in - Target LID (any LID = 0xFFFF) */
    uint	ManualMRA_f :1; /* in - User will manually send the MRA
                                        if acknowledgement will be delayed.
                                        Default is automatic ICM MRA */
    uint	Reserved1   :31; 
};
typedef struct IbListenCb IbListenCb_t;

struct IbUnlistenCb {
    IbHandle_t	HcaHandle;	/* in - Handle of the local HCA */
    IbHandle_t	ListenHandle;	/* in - Listen handle of the pending listen */
};
typedef struct IbUnlistenCb IbUnlistenCb_t;

struct IbAcceptCb {
      IbHandle_t HcaHandle;	/* in - Handle of the local HCA */
      IbHandle_t ConnHandle;    /* in - IbListenCb ListenHandle */
                                /* out - incoming connection request handle*/
      IbHandle_t LocalQpHandle; /* in - Handle of the local endpoint QP */
      Ib64bit UserCorrelator;   /* in - Opaque user correlator to be returned
                                        by ICM on subsequent asynchronous
                                        completions on this connection */
      uint	 LenPrivateData;/* in - Byte length of optional private data */
#ifndef __64BIT__
      uint       Res1;
#endif
      void	 *pPrivateData;	/* in - Pointer to optional private data area */
};
typedef struct IbAcceptCb IbAcceptCb_t;

struct IbRejectCb {
   IbHandle_t HcaHandle;        /* in - Handle of the local HCA */
   IbHandle_t ConnHandle;	/* in - Handle of the incoming connection
					request */
   uint	AdditionalInfoLength;	/* in - Byte length of any additional reject
					information  */
#ifndef __64BIT__
   uint Res1;
#endif
   void	*pAdditionalInfo;	/* in - Pointer to additional reject info */
   uint	LenPrivateData;		/* in - Byte length of optional private data */
#ifndef __64BIT__
   uint Res2;
#endif
   void	*pPrivateData;		/* in - Pointer to optional private data area */
   ushort	ReasonCode;	/* in - Reject reason code (See Reject Reason
					Syntax) */
};
typedef struct IbRejectCb IbRejectCb_t;

struct IbBusyCb {
   IbHandle_t   HcaHandle;      /* in - Handle of the local HCA */
   IbHandle_t	ConnHandle;	/* in -Handle of the incoming connection
					request */
   uint		LenPrivateData;	/* in - Byte length of optional private data */
#ifndef __64BIT__
   uint		Res1;
#endif
   void		*pPrivateData;	/* in - Pointer to optional private data area */
};
typedef struct IbBusyCb IbBusyCb_t;

/******************************************************************************
 * HCA Control Blocks
 *****************************************************************************/
#define IB_MAX_DEV_NAME 32
struct IbHcaOpenCb {
   char		DevNameIn[IB_MAX_DEV_NAME];	/* HCAD device name to open */
   IbHandle_t	HcaHandleOut;			/* Returned HCA Handle */
   uint         TrustedUser;                    /* TRUE/FALSE if Trusted User */
#ifdef IB_ERAS
   uint         StorageKeySafe;                 /* TRUE/FALSE if storage keys safe */
#endif /* IB_ERAS */
};
typedef struct IbHcaOpenCb IbHcaOpenCb_t;

struct IbHcaQueryCb {
   IbHandle_t	HcaHandle;	/* Handle of target HCA */
#ifndef __64BIT__
   uint		Res1;
#endif
   IbNodeInfo_t	*pNodeInfoOut;	/* Pointer to return node information */
#ifndef __64BIT__
   uint		Res2;
#endif
   IbPortInfo_t	*pPort1InfoOut;	/* Pointer to return Port-1 information */
#ifndef __64BIT__
   uint		Res3;
#endif
   IbPortInfo_t	*pPort2InfoOut;	/* Pointer to return Port-2 information */
};
typedef struct IbHcaQueryCb IbHcaQueryCb_t;

struct IbHcaQueryPortCb {
   IbHandle_t	HcaHandle;	/* Handle of target HCA */
   uint		PortNumIn;	/* Target port number */
#ifndef __64BIT__
   uint		Res1;
#endif
   IbPortInfo_t	*pPortInfoOut;	/* Pointer to return port information */
};
typedef struct IbHcaQueryPortCb IbHcaQueryPortCb_t;

/******************************************************************************
 * Memory Region Control Blocks
 *****************************************************************************/
struct IbMrDeregCb {
	IbHandle_t HcaHandle;		/* HCA handle */
	Ib64bit    MrHandleIn;		/* Memory region handle */
};
typedef struct IbMrDeregCb IbMrDeregCb_t;

struct IbMrQueryCb {
	IbHandle_t  HcaHandle;		/* HCA handle */
	Ib64bit     MrHandleIn;		/* Memory Region Handle */
	uint	    LKeyOut;		/* Returned L_Key */
	uint   	    RKeyOut;		/* Returned R_Key */
	Ib64bit	    LocalVaddrOut;	/* Local virtual address of MR */
	Ib64bit	    LocalByteNumOut;    /* Local length of memory region */
	Ib64bit	    RemoteVaddrOut;	/* Remote virtual address of MR */
	Ib64bit	    RemoteByteNumOut;	/* Remote length of memory region */
	IbPd_t	    PdOut;		/* Protection Domain Handle */
	IbAccessCtrl_t AccessCtrlOut;	/* Access Control */
};
typedef struct IbMrQueryCb IbMrQueryCb_t;

struct IbMrRegisterCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	Ib64bit		VaddrIn;	/* Virtual Address of MR */
	Ib64bit		ByteNumIn;	/* Length of Memory Region */
	IbPd_t		PdIn;		/* Protection Domain Handle */
	IbAccessCtrl_t AccessCtrlIn;	/* Access Control */
	Ib64bit	        MrHandleOut;	/* Returned Memory Region Handle */
	uint		LKeyOut;	/* Returned L_Key */
	uint		RKeyOut;	/* Returned R_Key */
};
typedef struct IbMrRegisterCb IbMrRegisterCb_t;

struct IbMrRegPhysCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
#ifndef __64BIT__
	uint		Res1;
#endif
	void		*pPhysBufListIn;/* Pointer to a list of physical */
				        /* buffer addresses */
	uint		NumBuffersIn;	/* Number of buffers in list  */
	Ib64bit		IoVaddrIn;	/* Requested I/O Virtual Address of */
				        /* the 1st byte of the region */
	uint		RegionLenIn;	/* Region byte length */
	uint		OffsetIn;	/* Offset of starting IOVA in the */
                                        /* 1st buffer */
	IbPd_t		PdIn;		/* Protection Domain */
	IbAccessCtrl_t AccessCtrlIn;	/* Access Control */
	Ib64bit	        MrHandleOut;	/* Returned Memory Region Handle */
	Ib64bit		IoVaddrOut;	/* Returned actual I/O Virtual Address*/
            			        /* of the 1st byte of the region */
	uint		LKeyOut;	/* Returned L_Key */
	uint		RKeyOut;	/* Returned R_Key */
};
typedef struct IbMrRegPhysCb IbMrRegPhysCb_t;

struct IbMrRegSharedCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	Ib64bit	        MrHandleIn;	/* Existing Memory Region Handle */
	Ib64bit		VaddrIn;	/* Virtual Address of MR */
	IbPd_t		PdIn;		/* Protection Domain Handle */
	IbAccessCtrl_t AccessCtrlIn;	/* Access Control */
	Ib64bit	        MrHandleOut;	/* Returned Memory Region Handle */
	Ib64bit		VaddrOut;	/* Returned Virtual Address of MR */
	uint		LKeyOut;	/* Returned L_Key */
	uint		RKeyOut;	/* Returned R_Key */
};
typedef struct IbMrRegSharedCb IbMrRegSharedCb_t;

/******************************************************************************
 * Memory Window Control Blocks
 *****************************************************************************/
struct IbMwAllocCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	IbPd_t		PdIn;		/* Protection Domain */
	IbHandle_t	MwHandleOut;	/* Returned Memory Window Handle */
	uint		RKeyOut;	/* Returned R_Key */
};
typedef struct IbMwAllocCb IbMwAllocCb_t;

struct IbMwBindCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	IbHandle_t	QpHandleIn;	/* QP handle */
	Ib64bit		WrkReqIDIn;	/* User defined work request ID */
	IbHandle_t	MwHandleIn;	/* Memory Window handle */
	uint		RKeyIn;		/* R_Key */
	IbHandle_t	MrHandleIn;	/* Memory Region handle */
	uint		LKeyIn;		/* L_Key */
	Ib64bit		VaddrIn;	/* Virtual Address of bound range */
	Ib64bit		ByteNumIn;	/* Byte length of range to be bound */
	IbAccessCtrl_t	AccessCtrlIn;	/* Access Control */
	uint		NotifyIn_f : 1;	/* 1 = notify on completion */
	uint		FenceIn_f  : 1;	/* 1= RDMA reads must complete*/
	uint		Reserved1  :30;
	uint		RKeyOut;	/* Returned R_Key */
};
typedef struct IbMwBindCb IbMwBindCb_t;

struct IbMwDeallocCb {
	IbHandle_t	HcaHandle;		/* HCA handle */
	IbHandle_t	MwHandleIn;		/* Memory Window handle */
};
typedef struct IbMwDeallocCb IbMwDeallocCb_t;

struct IbMwQueryCb {
	IbHandle_t	HcaHandle;		/* HCA handle */
	IbHandle_t	MwHandleIn;		/* Memory Window handle */
	uint		RKeyOut;		/* Returned R_Key */
	IbPd_t		PdOut;			/* Returned protection domain */
};
typedef struct IbMwQueryCb IbMwQueryCb_t;

/******************************************************************************
 * Multicast Control Blocks
 *****************************************************************************/
/* Multicast Address Scope Syntax  */
typedef enum {
	IB_ASCOPE_LINK_LOCAL	= 2,	/* Link-local (single subnet only) */
	IB_ASCOPE_SITE_LOCAL	= 5,	/* Site-local (site collection of
						   subnets) */
	IB_ASCOPE_ORG_LOCAL	= 8,	/* Organization-local (broader
                                              collection of subnets */
	IB_ASCOPE_GLOBAL	= 14	/* Global (fully routable) */
} IbMcastScope_t;

typedef enum {
	IB_MC_FULL_MEMBER	= 0x1,	/* Include/delete this endpoint as a
					   member sender and receiver */
        IB_MC_NON_MEMBER	= 0x2,	/* Include/delete this endpoint as a
      					   non-member sender and receiver
      					   (e.g., router) */
        IB_MC_SEND_NON_MEMBER	= 0x4	/* Include/delete this endpoint as a
      					   non-member sender only (e.g.,
      					   heartbeat generator) */
} IbJoinStatus_t;

typedef enum {
  IB_ST_RELIABLE_CONNECTION	= 0,
  IB_ST_UNRELIABLE_CONNECTION	= 1,
  IB_ST_RELIABLE_DATAGRAM	= 2,
  IB_ST_UNRELIABLE_DATAGRAM	= 3	/* note: reserved in IA Arch 12.7.6 */
} IbServiceType_t;

typedef enum {
   NO_GEN_CQE           = 0,       /* Do not generate a CQE */
   CONDITIONAL_GEN_CQE  = 1,       /* Conditionally generate CQEs  */
   ALWAYS_GEN_CQE       = 2        /* Generate CQE for every WQE */
} IbSignalType_t;

			/*** Mutually Exclusive Enhanced QP Operations ***/
			/***  (currently only QP_NORMAL is supported)  ***/
typedef enum {
   QP_NORMAL		= 0,	/* Normal QP operations */
   QP_LOW_LATENCY	= 1,	/* Low-latency QP enabled (RC only) */
   QP_HAS_SHARED_RCVQ	= 2,	/* Base QP has a shared RQ (RC or RD only) */
   QP_IS_SHARED_RCVQ	= 3,	/* QP configured as shared RQ (RC or RD only) */
   QP_TRIG_DOORBELL	= 4,	/* Triggered doorbell operation (RC only) */
   QP_METADATA_TRIG	= 5	/* Metadata and triggered doorbell operation
					(RC only) */
} IbQpEnhOpts_t;

/* For Scatter/Gather field in QP create, the field is used to specify  */
/* the WQE size in Low Latency Enhanced options.   Only the right most  */
/* 3 bits are used and only the value of 1-5 are valid.  The size       */
/* include a 128 bytes overhead.                                        */
typedef enum {
   QP_LL_WQE_SZ_256	= 1,	/* 256 bytes */
   QP_LL_WQE_SZ_512	= 2,	/* 512 bytes */
   QP_LL_WQE_SZ_1K 	= 3,	/* 1024 bytes */
   QP_LL_WQE_SZ_2K 	= 4,	/* 2048 bytes */
   QP_LL_WQE_SZ_4K 	= 5,	/* 4096 bytes */
} IbQpLL_WQESz_t;

typedef enum {
  IB_MGMT_TYPE_SMI      = 1,  /* QP0 Subnet Manager Interface             */
  IB_MGMT_TYPE_PERF     = 4,  /* QP1 Performance Management               */
  IB_MGMT_TYPE_BM       = 5,  /* QP1 Baseboard Management                 */
  IB_MGMT_TYPE_DEV_MGT  = 6,  /* QP1 Device Management                    */
  IB_MGMT_TYPE_COM_MGT  = 7,  /* QP1 Communication Management (not avail) */
  IB_MGMT_TYPE_SNMP     = 8,  /* QP1 SNMP Tunneling                       */
  IB_MGMT_TYPE_VENDOR_L = 9,  /* QP1 Vendor specific 0x09 - 0x0F          */
  IB_MGMT_TYPE_APP      = 16, /* QP1 Application specific 0x10 - 0x2F     */
  IB_MGMT_TYPE_VENDOR_H = 48  /* QP1 Vendor specific 0x30 - 0x4F          */
} IbMgmtType_t;

struct IbMcastCtl {
      IbHandle_t HcaHandle;	 /* in - Handle of the local HCA */
      Ib64bit	 UserCorrelator; /* in - Opaque user correlator to be returned
					 by ICM on asynchronous completion */
      uint	 LocalPortNum;	 /* in - Local port to issue multicast request*/
#ifndef __64BIT__
      uint	 Res1;
#endif
      IbHandle_t *pMcastHandle;	 /* in - Pointer to location for a multicast
      			                 handle:
					 (a) returned to user on Create or Join
					 (b) provided by the user on Leave
					 (c) ignored on Query */
      uint  ManualSubscribe_f : 1; /* in - Non-full member will manually
      			                   subscribe to the mcast group if not
      			                   already created.  Default is for ICM
      				           to automatically subscribe to the
      				           target group */
      uint  Reserved1         :31;
      uint  MaxMcastRecords;       /* in - Maximum number of mcast records
      				           being requested (cannot be zero or
      				           greater than the configured
					   max_records) */
      Ib64bit	ComponentMask;	   /* in - Bit mapped mask to identify which
      				           attributes are to be used in the
                                           request See Multicast Record
					   Component Mask */
      IbMcastRecord_t McastRecord; /* in - See Multicast Record Syntax */
};
typedef struct IbMcastCtl IbMcastCtl_t;

struct IbMcastAttachCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	IbHandle_t	QpHandle;	/* QP handle to be attached */
	uchar		McastGID[16];	/* Multicast 128-bit GID */
	ushort		McastLID;	/* Multicast LID */
};
typedef struct IbMcastAttachCb IbMcastAttachCb_t;

struct IbMcastDetachCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	IbHandle_t	QpHandle;	/* QP handle to be detached */
	uchar		McastGID[16];	/* Multicast 128-bit GID */
	ushort		McastLID;	/* Multicast LID */
};
typedef struct IbMcastDetachCb IbMcastDetachCb_t;

struct IbMcastFetchCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	IbHandle_t	McastHandle;	/* Multicast handle from find request */
	uint		RecordDataLen;	/* Byte length of Record Date area */
#ifndef __64BIT__
        uint            Res1;
#endif
        void		*pRecordData;	/* Pointer of the multicast record data
					   area to be synchronously filled in
					   by ICM (series of IbMcastRecord_t) */
};
typedef struct IbMcastFetchCb IbMcastFetchCb_t;

struct IbMcastSubscrCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	Ib64bit		UserCorrelator;	/* Opaque user correlator to be returned
					   by ICM on asynchronous completion */

					/********* Subscription Flags *********/
        uint	McastSubscrAdd_f : 1;	/* Flag=1: subscribing to notification
					   of a multicast group being created */
        uint	McastSubscrDel_f : 1;	/* Flag=1: subscribing to notification
					   of a multicast group being deleted */
        uint	Reserved1        :30;
	uint	LocalPortNum;		/* Local port to issue mcast request*/
	uchar		McastGID[16];	/* Target multicast 128-bit GID.
					   Note - all zeros is the wildcard */
	IbHandle_t	McastHandle;	/* Returned multicast handle */
};
typedef struct IbMcastSubscrCb IbMcastSubscrCb_t;

struct IbMcastUnSubscrCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	IbHandle_t	McastHandle;	/* Multicast handle from subscription */
	Ib64bit		UserCorrelator;	/* Opaque user correlator to be returned
					   by ICM on asynchronous completion */


					/******** Unsubscription Flags ********/
        uint	McastUnsubscrAdd_f : 1;	/* Flag=1: unsubscribing notification
					   of a multicast group being created */
        uint	McastUnsubscrDel_f : 1;	/* Flag=1: unsubscribing notification
					   of a multicast group being deleted */
        uint	Reserved1          :30;
	uint	LocalPortNum;		/* Local port to issue mcast request*/
};
typedef struct IbMcastUnSubscrCb IbMcastUnSubscrCb_t;


/******************************************************************************
 * Path Control Blocks
 *****************************************************************************/
struct IbPathAltRspCb {
	IbHandle_t HcaHandle;		/* in - Handle of the local HCA */
	IbHandle_t ConnHandle;		/* in - Handle of the connection */
	uint	LocalPortNum;		/* in - Local port number */
	uint	ApStatus	: 8;	/* in - Alternate Path Status
						(see IbAltPath_t) */
	uint	Reserved	:16;
	uint	InfoLength	: 8;	/* in - Additional information length */
	uchar	AdditionalInfo[72];	/* in - Additional Information */
	uchar	PrivateData[148];	/* in - Private Data */
};
typedef struct IbPathAltRspCb IbPathAltRspCb_t;

struct IbPathFetchCb {
      IbHandle_t	HcaHandle;	/* in - Handle of the local HCA */
      IbHandle_t	PathHandle;	/* in - Path correlator from
      						IB_FIND_PATH_CMPL event */
      uint		LenRecordData;	/* in - Byte length of the following
						path record data area */
#ifndef __64BIT__
      uint		Res1;
#endif
      void		*pRecordData;	/* Pointer of the path record data
					   area to be synchronously filled in
					   by ICM (series of IbPathRecord_t) */
};
typedef struct IbPathFetchCb IbPathFetchCb_t;

struct IbPathFindCb {
      IbHandle_t HcaHandle;		/* in - Handle of the local HCA */
      Ib64bit	UserCorrelator;		/* in - Opaque user correlator to be
      						returned by ICM on asyn
						completion */
      uint	 LocalPortNum;		/* in - Local port to issue the
						request */
      Ib64bit	 ComponentMask;		/* in - Bit mapped mask to identify
                                                which attributes are to be used
                                                in the query.  See Path Record
                                                Component Mask */
      IbPathRecord_t PathRecord;	/* in - Path record with values
                                                filled in with the desired
                                                components masked above. */
};
typedef struct IbPathFindCb IbPathFindCb_t;

struct IbLoadAltPathCb {
	IbHandle_t	HcaHandle;	/* in - Handle of the local HCA */
	IbHandle_t	ConnHandle;	/* in - Handle of the connection */
	uint		LocalPortNum;	/* in - Local port number */
	IbPathRecord_t  PathRecord;	/* in - New path record for the
						alternate path. */
};	
typedef struct IbLoadAltPathCb IbLoadAltPathCb_t;

/******************************************************************************
 * Protection Domain Control Blocks
 *****************************************************************************/
struct IbPdAllocCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	IbPd_t		PdOut;		/* Returned Protection Domain */
};
typedef struct IbPdAllocCb IbPdAllocCb_t;

struct IbPdDeallocCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	IbPd_t		PdIn;		/* Protection Domain */
};
typedef struct IbPdDeallocCb IbPdDeallocCb_t;

/******************************************************************************
 * Queue Pair Control Blocks
 *****************************************************************************/
struct IbQpCreateCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	IbServiceType_t ServiceTypeIn;	/* Service type */
	IbSignalType_t  SendSigTypeIn;	/* Send queue signal type */
	IbQpEnhOpts_t	EnhOptions;	/* Enhanced QP Options (see individual
					   adapters for supported values) */
	IbPd_t		PdIn;		/* Protection domain */
	IbHandle_t	TxCqHandleIn;	/* CQ handle for transmit queue */
	IbHandle_t	RxCqHandleIn;	/* CQ handle for receive queue */
	int		MaxTxRegIn;	/* Maximum transmit requests */
	int		MaxTxDataSegIn;	/* Max scatter/gather per Tx request */
                                        /* For LL QP, this's the send Msg siz */
	int		MaxRxRegIn;	/* Maximum receive requests */
	int		MaxRxDataSegIn;	/* Max scatter/gather per Rx request */	
                                        /* For LL QP, this's the Recv Msg siz */
					/* only value of 1-5 are valid, see */
					/* enum for QP_LL_WQE_SZ for detail */
	IbHandle_t	QpHandleOut;	/* QP handle */
	uint		QpNumberOut;	/* QP number */
	int		MaxTxRegOut;	/* Actual transmit requests */
	int		MaxTxDataSegOut;/* Actual scatter/gather per Tx req */
	int		MaxRxRegOut;	/* Actual receive requests */
	int		MaxRxDataSegOut;/* Actual scatter/gather per Rx req */
        int             InlineDataIn;   /* User specify intended inline data size  */
                                        /* set to zero if no inline data needed */
        int             InlineDataOut;  /* the exact size of inline data that this */
                                        /* adapter support, zero indicate no inline */
                                        /* data support */
#ifndef __64BIT__
	uint            Res1;
#endif
        char            *RcvQueueHeadOut;  /* Receive Queue head address for LL QP  */
#ifndef __64BIT__
	uint            Res2;
#endif
        char            *SendQueueHeadOut; /* Send Queue head address for LL QP  */
        int             CQEenableBit :1 ;  /* For LL QP receive only */ 
                                           /* 0=no CQE generated on receive */
                                           /* 1=   CQE generated on receive */
        int             Reserve      :31; 

};
typedef struct IbQpCreateCb IbQpCreateCb_t;

struct IbQpDestroyCb {
	IbHandle_t	HcaHandle;	/* HCA Handle */
	IbHandle_t	QpHandleIn;	/* QP Handle */		
};
typedef struct IbQpDestroyCb IbQpDestroyCb_t;


/*****************************************************************************
 * Queue Pair Control Block Mask (used by modify queue pair).
 *
 * Note: Any bit turned on (=1) in this mask indicates that the corresponding
 *       field in the IbQpCtlBlk_t structure contains a new value to apply to
 *       the target queue pair.
 ****************************************************************************/
struct IbQpMask {
  /********* BYTE 0 *********/
  uint mQKey                       : 1; /* Queue Key */
  uint mRes01                      : 1; /* Reserved (Reliable Dgrm Domain) */
  uint mSendPsn                    : 1; /* Send packet sequence number */
  uint mRecvPsn                    : 1; /* Receive packet sequence number */
  uint mPriPort                    : 1; /* Primary physical port */
  uint mAltPort                    : 1; /* Alternate physical port */
  uint mPriPkeyIndex               : 1; /* Primary PKey index */
  uint mAltPkeyIndex               : 1; /* Alternate PKey index */

  /********* BYTE 1 *********/
  uint mAtomicRdmaCtl              : 1; /* Incoming atomic-RDMA control flags */
  uint mQpState                    : 1; /* QP state */
  uint mRes10                      : 1; /* Reserved                         */
  uint mMaxRespResources           : 1; /* Maximum RDMA reads and atomics
                                           allowed as a responder */
  uint mPathMigState               : 1; /* Path migration state */
  uint mMaxDestResources           : 1; /* Maximum RDMA reads and atomics
                                           allowed at the destination QP */
  uint mDestQpNum                  : 1; /* Destination QP number */
  uint mMinRnrNakTimer             : 1; /* minimum RNR NAK timer value */

  /********* BYTE 2 *********/
                                        /* ---- Primary Address Vector ---- */
  uint mPriServiceLevel            : 1; /* Service level                    */
  uint mPriGlobalRoute             : 1; /* 1=Global route header present    */
  uint mPriRetryCount              : 1; /* Retry count                      */
  uint mPriAckTimeout              : 1; /* ACK timeout                      */
  uint mPathMtu                    : 1; /* Path MTU                         */
  uint mPriMaxStaticRate           : 1; /* Maximum static rate              */
  uint mPriDestLid                 : 1; /* Destination LID                  */
  uint mPriRnrRetryCount           : 1; /* RNR retry count                  */
  /********* BYTE 3 *********/
  uint mPriSourcePathBits          : 1; /* Source path bits                 */

                                        /* ---------- Primary GRH --------- */
  uint mPriTrafficClass            : 1; /* Ipv6 Traffic class               */
  uint mPriHopLimit                : 1; /* Hop limit                        */
  uint mPriSourceGidIndex          : 1; /* Source GID index                 */
  uint mPriFlowLabel               : 1; /* Ipv6 Flow label                  */
  uint mRes29                      : 1; /* Reserved                         */
  uint mPriDestGid                 : 1; /* Destination GID                  */

                                        /* --- Alternate Address Vector --- */
  uint mAltServiceLevel            : 1; /* Service level                    */
  /********* BYTE 4 *********/
  uint mAltGlobalRoute             : 1; /* 1=Global route header present    */
  uint mAltRetryCount              : 1; /* Retry count                      */
  uint mAltAckTimeout              : 1; /* ACK timeout                      */
  uint mAltMaxStaticRate           : 1; /* Maximum static rate              */
  uint mAltDestLid                 : 1; /* Destination LID                  */
  uint mAltRnrRetryCount           : 1; /* RNR retry count                  */
  uint mAltSourcePathBits          : 1; /* Source path bits                 */

                                        /* --------- Alternate GRH -------- */
  uint mAltTrafficClass            : 1; /* Ipv6 Traffic class               */
  /********* BYTE 5 *********/
  uint mAltHopLimit                : 1; /* Hop limit                        */
  uint mAltSourceGidIndex          : 1; /* Source GID index                 */
  uint mAltFlowLabel               : 1; /* Ipv6 Flow label                  */
  uint mres43                      : 1; /* Reserved                         */
  uint mAltDestGid                 : 1; /* Destination GID                  */

  uint mMaxSendWrkReq              : 1; /* Maximum outstanding send work
                                           requests                         */
  uint mMaxRecvWrkReq              : 1; /* Maximum outstanding receive work
                                           requests                         */
  uint mRes54			   : 1; /* Reserved for ETE Credit Checking */
  /********* BYTE 6 *********/
  uint mRes62		           : 1; /* Reserved for Enable QP           */
  uint mRes63		           : 1; /* Reserved for Current SRQ Limit   */
  uint mRes64_65	           : 1; /* Reserved for QPx_AAELOG          */
  uint mRes66_67	           : 1; /* Reserved for Shared Rcv Handle   */
  uint mRes68_69	           : 1; /* Reserved for Trig'd DB QP Handle */
  uint mQpControl	           : 1; /* mask 53: QP special control for byte 70-71 */
};
typedef struct IbQpMask IbQpMask_t;


struct IbQpModifyCb {
 /* Note: any pointer set to zero indicates that no output is desired for
			that particular field */
	IbHandle_t	HcaHandle;	/* HCA handle */
	IbHandle_t	QpHandleIn;	/* QP handle */	
	IbQpMask_t	QpMaskIn;	/* QP update mask (see IbQpMask_t) */
	IbQpCtlBlk_t	QpCtlBlkIn;	/* QP control block */

	Ib64bit		InvalAttrIdOut;	/* Returned first invalid attribute
                                           mask bit number whenever the modify
					   command fails with EINVAL */
        #define IB_QP_MOD_UNSPEC_ERR 0xFF /* Unspecified attribute error */

	uint_t		MaxTxReqOut;	/* Returned actual maximum transmit
				           requests */
	uint_t		MaxRxReqOut;	/* Returned actual maximum receive
				           requests */
};
typedef struct IbQpModifyCb IbQpModifyCb_t;

/*------ Data Segment Descriptor -----*/
struct IbDataSeg
{
	Ib64bit	Va;		/* Virtual Address of segment */
	uint	LKey;		/* L_Key */
	uint	Length;		/* Length of segment */
};
typedef struct IbDataSeg IbDataSeg_t;

/*------ Work Request Structure for all receive service types ------*/
struct IbWrkReqRecv
{
                                        /*** All Inputs ***/
        Ib64bit WrkReqIdIn;     /* User defined work request id */
        uchar   Reserved1[5];   /* 5 bytes of reserved area */
        uchar   NumDataSegIn;   /* Number of data segments */
        uchar   Reserved2[50];  /* 50 bytes of reserved area */
        IbDataSeg_t DataSeg;    /* 1st of n data segment descriptors in
                                    the scatter/gather list.  Additional
                                    descriptors may follow */
};
typedef struct IbWrkReqRecv IbWrkReqRecv_t;



/*------ Work Request Structure with pNext pointer ---------*/
struct IbWrkReqRChain
{
        struct IbWrkReqRChain  *pNext;     /* point to the next chained packet, end with NULL */
        IbWrkReqRecv_t         IbWrkReqR; 
					/*** All Inputs ***/
};
typedef struct IbWrkReqRChain IbWrkReqRChain_t;

struct IbQpPostRecvCb {
	IbHandle_t	HcaHandle;	/* HCA Handle */
	IbHandle_t	QpHandleIn;	/* Queue Pair Handle */
#ifndef __64BIT__
	uint		Res1;
#endif
	IbWrkReqRChain_t *pWrkReqInC;	/* Pointer to the work request */
        uint            Num ;           /* Number of Chained packets */
};
typedef struct IbQpPostRecvCb IbQpPostRecvCb_t;

/*------ Work Request Structure for send connected service ------*/
struct IbWrkReqSendConn
{
						/*** All Inputs ***/
	Ib64bit	WrkReqId;	/* User defined work request id */
	uchar	OpType;		/* See Send Operation types */
	uchar	WrtFlag;	/* See Write Flags */
	ushort	Reserved1;	/* 2 bytes of reserved area */
	uchar	WqeFlags;	/* See Send Connected WQE Flags */
	uchar	NumDataSeg;	/* Number of data segments (252 max) */
	uchar	Reserved2[14];	/* 14 bytes of reserved area */
	uint	ImmedData;	/* Immediate data field */
	Ib64bit	RemoteVa;	/* Remote virtual address (only for
					   RDMA or cache hint */
	uint	RKey;		/* R_Key (only for RDMA with cache
					   hint) */
	uchar	Reserved3[8];	/* 8 bytes of reserved area */
	uint	RdmaLength;	/* RDMA byte length (RDMA only) */
	uchar	Reserved4[8];	/* 8 bytes of reserved area */
	IbDataSeg_t DataSeg;	/* 1st of n data segment descriptors in
				   the scatter/gather list.  Additional
				   descriptors may follow */
};
typedef struct IbWrkReqSendConn IbWrkReqSendConn_t;

/*------ Work Request Structure for send unreliable datagram service ------*/
struct IbWrkReqSendUD
{
					/*** All Inputs ***/
	Ib64bit	WrkReqId;		/* User defined work request id */
	uint	OpType	        : 8;	/* See Send Operation types */
	uint	WrtFlag 	: 8;	/* See Write Flags */
	uint	PKeyIndex 	:16;	/* Selects 1 of 16 P_Keys */

	uint	WqeFlags	: 8;	/* See Unreliable Datagram WQE Flags */
	uint	NumDataSeg	: 8;	/* Number of data segments (252 max) */
	uint	ProvSlid	:16;	/* WQE provided SLID value */

	uint	ProvDestQpn	:24;	/* WQE provided destination QP number */
	uint	Reserved1	: 8;

	uint	Reserved2	: 8;
	uint	ProvSrcQpn	:24;	/* WQE provided source QP number */

	uint	QKey;			/* Authorization Q_Key */
	uint	ImmedData;		/* Immediate data field */
	IbUdRemoteAddr_t UdRemoteAddr;	/* Must be an address handle for UD */
	IbDataSeg_t DataSeg;            /* 1st of n data segment descriptors in
				           the scatter/gather list.  Additional
				           descriptors may follow */
};
typedef struct IbWrkReqSendUD IbWrkReqSendUD_t;

union IbWrkReqSend {
	IbWrkReqSendConn_t	Conn;
	IbWrkReqSendUD_t	UD;
};
typedef union IbWrkReqSend IbWrkReqSend_t;

struct IbWrkReqSC {
	struct IbWrkReqSC	*pNext;
        Ib64bit                 AhDllCorr;   /* reserved for IB stack used */
        uint                    InlineFlag;  /* indicate if this WKE is for inline data */
	IbWrkReqSend_t	        IbWRSend;
};
typedef struct  IbWrkReqSC IbWrkReqSC_t;

struct IbQpPostSendCb {
	IbHandle_t	HcaHandle;	/* HCA Handle */
	IbHandle_t	QpHandleIn;	/* Queue Pair Handle */
#ifndef __64BIT__
	uint		Res2;
#endif
	IbWrkReqSC_t    *pWrkReqInC;	/* Pointer to the work request */
        int             Num;            /* number of chained WQE       */
};
typedef struct IbQpPostSendCb IbQpPostSendCb_t;

struct IbQpQueryCb {
	IbHandle_t	HcaHandle;	/* HCA handle */
	IbHandle_t	QpHandleIn;	/* QP handle */	
#ifndef __64BIT__
	uint		Res1;
#endif
	IbQpCtlBlk_t	*pQpCtlBlkOut;	/* Pointer to a QP control block area */
};
typedef struct IbQpQueryCb IbQpQueryCb_t;

/*****************************************************************************
 * Special QP Control Blocks
 ****************************************************************************/
struct IbSpecialQpGetCb {
	IbQpCreateCb_t	QpCreateCb;	/* Note: only the primary port entries
					         are used for special QP's */
	IbMgmtType_t  	SpecialTypeIn;	/* Management type being requested */
	uint		PortNumIn;	/* Port number */
};
typedef struct IbSpecialQpGetCb IbSpecialQpGetCb_t;

/*****************************************************************************
 * UD Services Control Blocks
 ****************************************************************************/
struct IbServiceFindCb {
      IbHandle_t   HcaHandle;        /* in - Handle of the local HCA */
      Ib64bit	   UserCorrelator;   /* in - Opaque user correlator to be
      			               	     returned by ICM on asynchronous 
      			                     completion */
      Ib64bit	   TargetServiceID;  /* in - Target Service ID  */
      ushort	   TargetPkey;	     /* in - Target partition key */
      uint	   LenPrivateData;   /* in - Byte length of optional private
					     data */
#ifndef __64BIT__
      uint	   Res1;
#endif
      void	   *pPrivateData;    /* in - Pointer to optional private
                                             data area (up to 216 bytes) */
};
typedef struct IbServiceFindCb IbServiceFindCb_t;

struct IbServiceRegCb {
	IbHandle_t	HcaHandle;	/* in - Handle of the local HCA */
	uint		LocalPortNum;	/* in - Local port number */
	IbHandle_t	LocalQpHandle;	/* in - Handle of the local service QP*/
	
	Ib64bit		ServiceID;	/* in - UD Service ID being registered*/
	uint	ManualSIDR_f	: 1;	/* in - User will manually respond to
						SIDR_REQ's.  The default is for
						ICM to do this automatically */
	uint	ReservedFlags	: 31;

        uint		LenPrivateData;	/* in - Byte length of optional private
						data */
#ifndef __64BIT__
	uint		Res1;
#endif
	void		*pPrivateData;	/* in - Pointer to optional private
						data to be sent on automated
						SIDR_REP's (up to 136 bytes) */
#ifndef __64BIT__
	uint		Res2;
#endif
	IbHandle_t	*pServiceHandle;/* in - Pointer for ICM to
                                                synchronously return a UD
						service registration handle */
 };
typedef struct IbServiceRegCb IbServiceRegCb_t;

struct IbServiceReplyCb {
	IbHandle_t	HcaHandle;	   /* in - Handle of the local HCA */
	IbHandle_t	ServiceHandle;	   /* in - UD Service Handle */
        IbSidrRepStatus_t Status;	   /* in - SIDR Reply Status */
	uint		LenAdditionalData; /* in - Length of any required 
						additional data when status
						field is redirect or version */
#ifndef __64BIT__
	uint		Res1;
#endif
	void		*pAdditionalData;  /* in - Pointer to up to 72 bytes
						of additional data */

        uint		LenPrivateData;	   /* in - Byte length of optional
						private data */
#ifndef __64BIT__
	uint		Res2;
#endif
	void		*pPrivateData;	   /* in - Pointer to optional private
						data to be sent on the
						SIDR_REP (up to 136 bytes) */
 };
typedef struct IbServiceReplyCb IbServiceReplyCb_t;

struct IbServiceUnregCb {
	IbHandle_t	HcaHandle;	/* HCA Handle */
	IbHandle_t	ServiceHandle;	/* UD Service Handle */
};
typedef struct IbServiceUnregCb IbServiceUnregCb_t;


/* Definition for PortState */ 
   #define IB_PORT_STATE_NONE              0x0
   #define IB_PORT_STATE_DOWN              0x1
   #define IB_PORT_STATE_INITIALIZED       0x2
   #define IB_PORT_STATE_ARMED             0x3
   #define IB_PORT_STATE_ACTIVE            0x4

/* Definition for Physical Port Physical State */ 
   #define IB_PORT_PHYSICAL_STATE_NO_CHANGE  0x0
   #define IB_PORT_PHYSICAL_STATE_SLEEP      0x1
   #define IB_PORT_PHYSICAL_STATE_DISABLED   0x2
   #define IB_PORT_PHYSICAL_STATE_PORT_CONFIG_TRAINING  0x4
   #define IB_PORT_PHYSICAL_STATE_LINK_UP    0x5
   #define IB_PORT_PHYSICAL_STATE_LINK_ERROR_RECOVERY  0x6

/* Definition for Physical Port Speed */ 
   #define IB_PORT_SPEED_2_5G		     0x1
   #define IB_PORT_SPEED_5_0G                0x2
   #define IB_PORT_SPEED_10G                 0x4

/* Definition for Physical Port Speed */ 
   #define IB_PORT_WIDTH_1X		     0x1
   #define IB_PORT_WIDTH_4X		     0x2
   #define IB_PORT_WIDTH_8X		     0x4
   #define IB_PORT_WIDTH_12X		     0x8

/* Definition for InitTypeReply */
 #define IB_NO_LOAD_REPLY           1  /* No port attributes were loaded */
 #define IB_PRESERVE_CONTENT_REPLY  2  /* Attributes from most recent SM load */
 #define IB_PRESERVE_PRESENCE_REPLY 4  /* All settable SA attributes were
                                          preserved */


/* Definition for Maximum Transmission Unit Capacity (MtuCap) */
   #define IB_MTU_256      1
   #define IB_MTU_512      2
   #define IB_MTU_1024     3
   #define IB_MTU_2048     4
   #define IB_MTU_4096     5


/* Definition of Virtual Lanes Capacity (VLCap) */ 
   #define IB_VL0          1        /* VL0 only */
   #define IB_VL0_TO_VL1   2        /* VL0 and VL1 */
   #define IB_VL0_TO_VL3   3        /* VL0 through VL3 */
   #define IB_VL0_TO_VL7   4        /* VL0 through VL7 */
   #define IB_VL0_TO_VL14  5        /* Vl0 through VL14 */


/* Definition of Static Rate or Inter Packet Delay (IpDelay) */ 
   #define IB_IP_NO_DELAY  0x00     /* No delay, 100% usage */
   #define IB_IP_DELAY_67  0x02     /* 33% usage permitted */
   #define IB_IP_DELAY_75  0x03     /* 25% usage permitted */
   #define IB_IP_DELAY_92  0x0B     /* 8% usage permitted */


/*****************************************************************************
 * Asynchronous Events (for IbEqEvent_t)
 *****************************************************************************/
/* Definitions */
/*------- Event/Error Identifiers (EventID) --------------------*/
                                        /* Each error (EventID) has additional
                                         * information available within the
                                         * IbEqEvent structure fields:
                                         * EVENT, QP/CQ NUM, RESOURCE ID
                                         *************************************/
#define IB_EQE_PATH_MIGRATED	0x02	/* Path Migrated, QPN, QP correlator */
#define IB_EQE_COMM_ESTABLISHED	0x03	/* Communications established (used
					   only by ICM), QPN, QP correlator */
#define IB_EQE_SQ_DRAINED	0x04	/* Send queue drained, QPN,
                                       		  QP correlator */
#define IB_EQE_QP_ERR		0x05	/* QP error, QPN, QP correlator */
#define IB_EQE_QP0_ERR		0x06	/* QP error, QPN, QP correlator (EQ0) */
#define IB_EQE_CQ_ERR		0x07	/* CQ error, CQN, CQ correlator */
#define IB_EQE_CQ0_ERR		0x08	/* CQ error, CQN, CQ correlator (EQ0) */
#define IB_EQE_MRWPTE_ERR	0x09	/* MRWPTE error, n/a, MRWPTE number */
#define IB_EQE_PORT_EVENT	0x0A	/* Port event, n/a, port number */
#define IB_EQE_MR_ACCESS	0x0B	/* MR access error, n/a, LKey/RKey */
#define IB_EQE_EQ_ERR		0x0C	/* Event queue error, n/a,
						EQ number */
#define IB_EQE_PKEY_QKEY	0x0D	/* PKey QKey mismatch, n/a, port num */
#define IB_EQE_SAMPLE_CMPL	0x10	/* Sampling complete, n/a,
						Sampling Mechanism ID */
#define IB_EQE_UNAFF_ACCESS	0x11	/* Unaffiliated access error, n/a,
						n/a*/
#define IB_EQE_PATH_MIGRATING	0x12	/* Path migrating, QPN, QP correlator */
#define IB_EQE_TRACE_STOPPED	0x13	/* Interface trace stopped, n/a, n/a */
#define IB_EQE_1ST_ERR_CAPTURE	0x14	/* 1st error capture info available,
						n/a, n/a */
#define IB_PORT_AVAIL_CHANGE	0x30	/* Port availability changed, port#,
						1=port available */
#define IB_PORT_CONFIG_CHANGE	0x31	/* Port configuration changed, port#,
						1=disruptive change */
#define IB_ADAPTER_MALFUNCTION	0x32	/* Adapter malfunction, n/a, n/a */
#define IB_TRACE_STOPPED	0x33	/* Adapter tracing stopped, n/a,
						n/a */
#define IB_REJOIN_MCAST_GRP	0x34	/* Rejoin mutlicast group */
#define IB_EQE_SHUTDOWN		0x3E	/* Device Shutdown, n/a, n/a */
#define IB_EQE_PATH_MIG_FAILED	0x3F	/* Path Migration Failed, QPN,
                                       		  QP correlator */

#define IB_EQE_GET_QP_COUNT     0x35    /* Get QP Count Event */
#define IB_EQE_GET_CQ_COUNT     0x36    /* Get CQ Count Event */

/* Command Completion Result Status */
typedef enum {
  IB_CMPL_SUCCESSFUL	  = 0, /* completion was successful */
  IB_CMPL_REQ_INVALID     = 1, /* request was invalid */
  IB_CMPL_NO_RESOURCES    = 2, /* not enough resources to satisfy the request */
  IB_CMPL_SEE_ADDITIONAL  = 3, /* see additional status in completion buffer */
  IB_CMPL_SUBSCR_PENDING  = 4, /* multicast subscription is still pending */
  IB_CMPL_TIMEOUT         = 5  /* request timed out */
} IbResultStatus_t;

/*------ CQE Receive Operation Types ------*/
#define IB_DATA_RECEIVED	0x01	/* Data received */
#define IB_RDMA_WITH_DATA	0x02	/* RDMA with immediate data received */

/*------ CQE Work Completion Flags ------*/
#define IB_WQ_RCV		0x80  /* 0=Send Queue CQE, 1=Receive Queue CQ */
#define IB_IMMED_DATA_PRES	0x40  /* Immediate data present (receive only)*/
#define IB_GRH_PRES		0x20  /* GRH present in 1st data segment
                                              (UD receive only) */
#define IB_SOLICITED		0x10  /* Solicited Event bit set in received
						   packet (receive only) */

/*
 * ComponentMask for MCMemberRecord requests.
 * See IbMcastRecord_t and Infiniband Architecture 15.2.5.17).
 */
typedef enum {
      IB_MC_MASK_MCAST_GID		= 0x00000001,
      IB_MC_MASK_LOCAL_GID		= 0x00000002,
      IB_MC_MASK_MCAST_QKEY    	       	= 0x00000004,
      IB_MC_MASK_MCAST_LID		= 0x00000008,
      IB_MC_MASK_MTU_SELECTOR		= 0x00000010,
      IB_MC_MASK_MTU			= 0x00000020,
      IB_MC_MASK_TRAFFIC_CLASS		= 0x00000040,
      IB_MC_MASK_PKEY			= 0x00000080,
      IB_MC_MASK_RATE_SELECTOR		= 0x00000100,
      IB_MC_MASK_PACKET_RATE		= 0x00000200,
      IB_MC_MASK_PKT_LIFETIME_SELECTOR	= 0x00000400,
      IB_MC_MASK_PKT_LIFETIME		= 0x00000800,
      IB_MC_MASK_SERVICE_LEVEL		= 0x00001000,
      IB_MC_MASK_FLOW_LABEL		= 0x00002000,
      IB_MC_MASK_HOP_LIMIT		= 0x00004000,
      IB_MC_MASK_SCOPE			= 0x00008000,
      IB_MC_MASK_JOIN_STATUS		= 0x00010000
} IbMcMask_t;

/* Packet Rate Syntax */
typedef enum {
	IB_PKT_RATE_1X		= 2,		/* 1X = 2.5Gbps */
	IB_PKT_RATE_4X		= 3,		/* 4X = 10 Gbps */
	IB_PKT_RATE_10X		= 4		/* 10X = 30 Gbps */
} IbPktRate_t;

/*  Path Record Component Mask */
typedef enum {
      IB_PR_MASK_DEST_GID		= 0x00000004,
      IB_PR_MASK_SRC_GID		= 0x00000008,
      IB_PR_MASK_DEST_LID		= 0x00000010,
      IB_PR_MASK_SRC_LID		= 0x00000020,
      IB_PR_MASK_RAW_TRAFFIC		= 0x00000040,
      IB_PR_MASK_FLOW_LABEL		= 0x00000100,
      IB_PR_MASK_HOP_LIMIT		= 0x00000200,
      IB_PR_MASK_TRAFFIC_CLASS		= 0x00000400,
      IB_PR_MASK_REVERSABLE		= 0x00000800,
      IB_PR_MASK_NUM_PATHS		= 0x00001000,
      IB_PR_MASK_PKEY			= 0x00002000,
      IB_PR_MASK_SERVICE_LEVEL		= 0x00008000,
      IB_PR_MASK_MTU_SELECTOR		= 0x00010000,
      IB_PR_MASK_MTU			= 0x00020000,
      IB_PR_MASK_RATE_SELECTOR		= 0x00040000,
      IB_PR_MASK_RATE			= 0x00080000,
      IB_PR_MASK_PKT_LIFETIME_SELECTOR	= 0x00100000,
      IB_PR_MASK_PKT_LIFETIME		= 0x00200000
};

/* Path Record Rate Selector */
typedef enum {
      IB_PR_RATE_SEL_GREATER	= 0,	/* Greater than rate specified */
      IB_PR_RATE_SEL_LESS	= 1,	/* Less than rate specified */
      IB_PR_RATE_SEL_EXACT	= 2,	/* Exactly the rate specified */
      IB_PR_RATE_SEL_LARGEST	= 3	/* Largest rate available */
} IbPrRateSel_t;

/* Path Record Rate */
typedef enum {
      IB_PR_RATE_1X		= 2,	/* 2.5 Gb/sec */
      IB_PR_RATE_4X		= 3,	/* 10 Gb/sec */
      IB_PR_RATE_10X		= 4	/* 30 Gb/sec */
} IbPrRate_t;

/* Path Record Packet Lifetime Selector */
typedef enum {
      IB_PR_LIFETIME_SEL_GREATER	= 0,	/* Greater than packet lifetime
							specified */
      IB_PR_LIFETIME_SEL_LESS		= 1,	/* Less than packet lifetime
      							specified */
      IB_PR_LIFETIME_SEL_EXACT		= 2,	/* Exactly the packet lifetime
      							specified */
      IB_PR_LIFETIME_SEL_SMALLEST	= 3	/* Smallest packet lifetime
      							available */
} IbPrLifetimeSel_t;

/* Alternate Path Status Syntax */
typedef enum {				/**** Additional Information Field ****/
	IB_AP_LOADED_SUCCESFULLY	= 0,
	IB_AP_INVALID_COMM_ID		= 1,
	IB_AP_NOT_SUPPORTED		= 2,
	IB_AP_FAILOVER_PORT_REJECTED	= 3,
	IB_AP_REJ_REDIRECT		= 4,	/* Redirect ClassPortInfo
                                                    data struct */
	IB_AP_SAME_AS_PRIMARY		= 5,
	IB_AP_INVALID_QPN		= 6,
	IB_AP_PORT_LID_REJECTED		= 7,	/* LID of acceptable port */
	IB_AP_PORT_GID_REJECTED		= 8,	/* GID of acceptable port */
	IB_AP_FLOW_LABEL_REJECTED	= 9,	/* Acceptable flow label */
	IB_AP_TRAFFIC_CLASS_REJECTED	= 10,	/* Acceptable traffic class */
	IB_AP_HOP_LIMIT_REJECTED	= 11,	/* Acceptable hop limit */
	IB_AP_PACKET_RATE_REJECTED	= 12,	/* Minimum acceptable packet
                                                      rate */
	IB_AP_SVC_LEVEL_REJECTED	= 13	/* Acceptable service level */
} IbAltPath_t;

/* Send Operation Types */
/*------ Send Operation Types (bit flags) ------*/
/* NOTE: only one bit may be set for a valid operation */
#define IB_OP_SEND		0x80		/* Send */
#define IB_OP_RDMA_READ		0x40		/* RDMA Read */
#define IB_OP_RDMA_WRITE	0x20		/* RDMA Write */
#define IB_OP_COMP_AND_SWAP	0x10		/* Compare and Swap */
#define IB_OP_FETCH_AND_ADD	0x08		/* Fetch and Add */
#define IB_OP_BIND_MW		0x04		/* Memory Window Bind */


/*------ Write Flags ------*/
#define IB_WRF_SIGNAL		0x80		/* Signal on completion */
#define IB_WRF_FENCE		0x40		/* RDMA reads must complete */
#define IB_WRF_IMMED_DATA	0x20		/* Immediate data present */
#define IB_WRF_SOLICITED	0x10		/* Solicited event */


/*------ Send Connected WQE Flags ------*/
#define IB_WQEF_SC_CACHE_HINT	0x80		/* This WQE contains a Cache
						   Hint */
#define IB_WQEF_SC_RDMA_WRT	0x40		/* 0=hint is for RDMA read,
						   1=hint is for RDMA write */
#define IB_WQEF_SC_TIMED	0x20		/* WQE to be timed from the
						   start */
#define IB_WQEF_SC_PURGE	0x08		/* WQE is to be purged */


/*------ Send Unreliable Datagram WQE Flags ------*/
#define IB_WQEF_UD_TIMED	0x20	/* WQE to be timed from the start */
#define IB_WQEF_UD_FORCE_OUT	0x10	/* This WQE contains a Cache Hint */
#define IB_WQEF_UD_PURGE	0x08	/* This WQE is to be purged */
#define IB_WQEF_UD_USE_SLID	0x04	/* Use WQE provided SLID */
#define IB_WQEF_UD_USE_QPN	0x02	/* Use WQE provided QP number */

/*  IbGetDeviceList Structure  */

typedef struct {
   char DevName[IB_MAX_DEV_NAME];
   char DevId[IB_MAX_DEV_NAME];
} IbDevice_t;

/* Complete packed alignment */
#pragma options align=reset

#endif /* _H_IBAPI */

