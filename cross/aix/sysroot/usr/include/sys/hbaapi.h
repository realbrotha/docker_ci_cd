/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/usr/lib/hbaapi/hbaapi.h 1.7                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2002,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)12       1.7  src/bos/usr/lib/hbaapi/hbaapi.h, hbaapi, bos53V, v2009_14A8 3/17/09 09:39:31 */

#ifdef __cplusplus
extern "C" {
#endif


#ifndef HBA_API_H
#define HBA_API_H

#ifndef _H_TIME
#include <time.h>
#endif

/* Library version string */
#define HBA_LIBVERSION 2
#define HBA_VERSION_2  2

#ifndef HBA_API
#define HBA_API
#endif

/* OS specific definitions */

typedef unsigned char  	 HBA_UINT8;	   /* Unsigned  8 bits */
typedef          char    HBA_INT8;         /* Signed    8 bits */
typedef unsigned short   HBA_UINT16;	   /* Unsigned 16 bits */
typedef          short   HBA_INT16;	   /* Signed   16 bits */
typedef unsigned int     HBA_UINT32;       /* Unsigned 32 bits */
typedef          int     HBA_INT32;        /* Signed   32 bits */
typedef void*            HBA_PVOID;        /* Pointer  to void */
typedef HBA_UINT32   	 HBA_VOID32;       /* Opaque   32 bits */
typedef long long   	 HBA_INT64;
typedef long long   	 HBA_UINT64;
typedef HBA_UINT8        HBA_BOOLEAN;      /* A single true/false flag */


/* Handle to Device */
typedef HBA_UINT32  	 			HBA_HANDLE;

/* Status Return Values */
typedef HBA_UINT32 HBA_STATUS;

#define HBA_STATUS_OK        			0
#define HBA_STATUS_ERROR 			1   /* Error */
#define HBA_STATUS_ERROR_NOT_SUPPORTED    	2   /* Function not supported.*/
#define HBA_STATUS_ERROR_INVALID_HANDLE	  	3   /* invalid handle */
#define HBA_STATUS_ERROR_ARG       		4   /* Bad argument */
#define HBA_STATUS_ERROR_ILLEGAL_WWN   	  	5   /* WWN not recognized */
#define HBA_STATUS_ERROR_ILLEGAL_INDEX	  	6   /* Index not recognized */
#define HBA_STATUS_ERROR_MORE_DATA		7   /* Larger buffer required */
#define HBA_STATUS_ERROR_STALE_DATA    		8   /* "Refresh" required. */
#define HBA_STATUS_SCSI_CHECK_CONDITION		9   /* SCSI Check Condition reported */
#define HBA_STATUS_ERROR_BUSY                   10  /* Adapter Busy or Reserved  retry may be effective */
#define HBA_STATUS_ERROR_TRY_AGAIN              11  /* Adapter Busy or Reserved  retry may be effective */
#define HBA_STATUS_ERROR_UNAVAILABLE            12  /* Referenced HBA has been removed or deactivated */
#define HBA_STATUS_ERROR_ELS_REJECT             13  /* The requested ELS was rejected by the local HBA */
#define HBA_STATUS_ERROR_INVALID_LUN            14  /* The specified LUN is not provided by the specified HBA */
#define HBA_STATUS_ERROR_INCOMPATIBLE           15  /* An incompatibility has been detected among the library
and driver modules invoked that may cause one or more functions in the highest version they all support to
operate incorrectly.  The differing function sets of software modules implementing different versions of the
HBA API specification does not in itself constitute an incompatibility.  Known interoperability bugs among
supposedly compatible versions should be reported as incompatibilities, but not all such interoperability bugs
may be known.  This value may be returned by any function that calls an HBA specfic library and returns an
HBA_STATUS, and by HBA_LoadLibrary and HBA_GetAdapterName */
#define HBA_STATUS_ERROR_AMBIGUOUS_WWN          16  /* Multiple adapters have a matching Name_Identifier.
This may occur if the NodeWWN of multiple adapters is identical. */
#define HBA_STATUS_ERROR_LOCAL_BUS              17  /* A persistent binding request included a bad local SCSI
bus number */
#define HBA_STATUS_ERROR_LOCAL_TARGET           18  /* A persistent binding request included a bad local SCSI
logical unit number */
#define HBA_STATUS_ERROR_LOCAL_LUN              19  /* A persistent binding request included a bad local SCSI logical unit number */
#define HBA_STATUS_ERROR_LOCAL_SCSIID_BOUND     20  /* A persistent binding set request included a local SCSI ID that was already bound */
#define HBA_STATUS_ERROR_TARGET_FCID            21  /* A persistent binding request included a bad or unlocatable FCP-2 target FCID */
#define HBA_STATUS_ERROR_TARGET_NODE_WWN        22  /* A persistent binding request included a bad FCP-2 target Node_Name */
#define HBA_STATUS_ERROR_TARGET_PORT_WWN        23  /* A persistent binding request included a bad FCP-2 target N_Port_Name */
#define HBA_STATUS_ERROR_TARGET_LUN             24  /* A persistent binding request included an FCP logical unit number not defined by the identified target*/
#define HBA_STATUS_ERROR_TARGET_LUID            25  /* A persistent binding request included an undefined or otherwise inaccessible Logical Unit Unique Identifier */
#define HBA_STATUS_ERROR_NO_SUCH_BINDING        26  /* A persistent binding remove request included a binding that did not match a binding established by the specified local end port */
#define HBA_STATUS_ERROR_NOT_A_TARGET           27  /* A SCSI command was requested to an end port that was not a SCSI target Port */
#define HBA_STATUS_ERROR_UNSUPPORTED_FC4        28  /* A request was made concerning an unsupported FC-4 protocol */
#define HBA_STATUS_ERROR_INCAPABLE              29  /* A request was made to enable unimplemented capabilities for a local end port */
#define HBA_STATUS_ERROR_TARGET_BUSY            30  /* A SCSI function was rejected to prevent causing a SCSI overlapped command condition (see SAM-3) */
#define HBA_STATUS_ERROR_NOT_LOADED             31  /* A call was made to HBA_FreeLibrary when no library was loaded */
#define HBA_STATUS_ERROR_ALREADY_LOADED         32  /* A call was made to HBA_LoadLibrary when a library was already loaded */
#define HBA_STATUS_ERROR_ILLEGAL_FCID           33  /* The Address Identifier specified in a call to HBA_SendRNIDV2 violates access control rules for that call */

/* Port Operational Modes Values */

typedef HBA_UINT32 HBA_PORTTYPE; 		

#define HBA_PORTTYPE_UNKNOWN		   	1 /* Unknown */
#define HBA_PORTTYPE_OTHER             		2 /* Other */
#define HBA_PORTTYPE_NOTPRESENT        		3 /* Not present */
#define HBA_PORTTYPE_NPORT          		5 /* Fabric  */
#define HBA_PORTTYPE_NLPORT 			6 /* Public Loop */
#define HBA_PORTTYPE_FLPORT			7
#define HBA_PORTTYPE_FPORT	       		8 /* Fabric Port */
#define HBA_PORTTYPE_LPORT        	  	20 /* Private Loop */
#define HBA_PORTTYPE_PTP  			21 /* Point to Point */
/*
   The following 2 PORTTYPEs defines are included for compatability
   with earlier versions of the HBA API but are not used or returned on any
   API function calls with the current (Version 2) of libHBAAPI.a.
*/
#define HBA_PORTTYPE_EPORT                       9 /* Fabric expansion port */
#define HBA_PORTTYPE_GPORT                      10 /* Generic Fabric Port */


typedef HBA_UINT32 HBA_PORTSTATE; 		

#define HBA_PORTSTATE_UNKNOWN 			1 /* Unknown */
#define HBA_PORTSTATE_ONLINE			2 /* Operational */
#define HBA_PORTSTATE_OFFLINE 			3 /* User Offline */
#define HBA_PORTSTATE_BYPASSED         		4 /* Bypassed */
#define HBA_PORTSTATE_DIAGNOSTICS      		5 /* In diagnostics mode */
#define HBA_PORTSTATE_LINKDOWN 			6 /* Link Down */
#define HBA_PORTSTATE_ERROR 			7 /* Port Error */
#define HBA_PORTSTATE_LOOPBACK 			8 /* Loopback */


typedef HBA_UINT32 HBA_PORTSPEED;

#define HBA_PORTSPEED_UNKNOWN          		0 /* Unknown - transceiver incable of reporting */
#define HBA_PORTSPEED_1GBIT			1 /* 1 GBit/sec */
#define HBA_PORTSPEED_2GBIT			2 /* 2 GBit/sec */
#define HBA_PORTSPEED_10GBIT			4 /* 10 GBit/sec */
#define HBA_PORTSPEED_4GBIT			8 /* 10 GBit/sec */
#define HBA_PORTSPEED_NOT_NEGOTIATED   		(1<<15) /* Speed not established */


typedef HBA_UINT32 HBA_COS;    /* See Class of Service - Format in FC-GS-4*/


/* Fc4Types Values */

typedef struct HBA_fc4types {
	HBA_UINT8 			bits[32]; 		/* 32 bytes of FC-4 per GS-2 */
} HBA_FC4TYPES, *PHBA_FC4TYPES;

/* Basic Types */

typedef struct HBA_wwn {
	HBA_UINT8 			wwn[8];
} HBA_WWN, *PHBA_WWN;

typedef struct HBA_ipaddress {
	int				ipversion;		/* see enumerations in RNID */
	union
	{
		unsigned char		ipv4address[4];
		unsigned char 		ipv6address[16];
	} ipaddress;
} HBA_IPADDRESS, *PHBA_IPADDRESS;

#define EMULEX_VENDOR_ID   "df10"     /* Emulex Vendor ID */
#define QLOGIC_VENDOR_ID   "7710"     /* QLogic Vendor ID */

/* Adapter Attributes */
typedef struct HBA_AdapterAttributes {
	char 			Manufacturer[64];  		/*Emulex */
	char 			SerialNumber[64];  		/* A12345 */
	char 			Model[256];            		/* QLA2200 */
    	char 			ModelDescription[256];  	/* Agilent TachLite */
	HBA_WWN 		NodeWWN; 
	char 			NodeSymbolicName[256];		/* From GS-3 */
	char 			HardwareVersion[256];		/* Vendor use */
	char 			DriverVersion[256]; 		/* Vendor use */
    	char 			OptionROMVersion[256]; 		/* Vendor use  - i.e. hardware boot ROM*/
	char 			FirmwareVersion[256];		/* Vendor use */
	HBA_UINT32 		VendorSpecificID;		/* Vendor specific */
   	HBA_UINT32 		NumberOfPorts;
	char			DriverName[256];		/* Binary path and/or name of driver file. */
} HBA_ADAPTERATTRIBUTES, *PHBA_ADAPTERATTRIBUTES;

/* Port Attributes */
typedef struct HBA_PortAttributes {
    	HBA_WWN 		NodeWWN;
	HBA_WWN 		PortWWN;
	HBA_UINT32 		PortFcId;
	HBA_PORTTYPE 		PortType; 			/*PTP, Fabric, etc. */
	HBA_PORTSTATE	 	PortState;
	HBA_COS 		PortSupportedClassofService;
	HBA_FC4TYPES		PortSupportedFc4Types;
	HBA_FC4TYPES		PortActiveFc4Types;
	char			PortSymbolicName[256];
	char 			OSDeviceName[256]; 		/* \device\ScsiPort3  */
    	HBA_PORTSPEED		PortSupportedSpeed;
	HBA_PORTSPEED		PortSpeed; 
	HBA_UINT32		PortMaxFrameSize;
	HBA_WWN			FabricName;
	HBA_UINT32		NumberofDiscoveredPorts;
} HBA_PORTATTRIBUTES, *PHBA_PORTATTRIBUTES;


/* Port Statistics */
typedef struct HBA_PortStatistics {
	HBA_INT64		SecondsSinceLastReset;
	HBA_INT64		TxFrames;
	HBA_INT64		TxWords;
   	HBA_INT64		RxFrames;
   	HBA_INT64		RxWords;
	HBA_INT64		LIPCount;
	HBA_INT64		NOSCount;
	HBA_INT64		ErrorFrames;
	HBA_INT64		DumpedFrames;
	HBA_INT64		LinkFailureCount;
	HBA_INT64		LossOfSyncCount;
	HBA_INT64		LossOfSignalCount;
	HBA_INT64		PrimitiveSeqProtocolErrCount;
	HBA_INT64		InvalidTxWordCount;
	HBA_INT64		InvalidCRCCount;
} HBA_PORTSTATISTICS, *PHBA_PORTSTATISTICS;

/* Statistical counters for FC-4 protocols */ 
typedef struct HBA_FC4Statistics { 
        HBA_INT64               InputRequests; 
        HBA_INT64               OutputRequests; 
        HBA_INT64               ControlRequests; 
        HBA_INT64               InputMegabytes; 
        HBA_INT64               OutputMegabytes; 
} HBA_FC4STATISTICS, *PHBA_FC4STATISTICS;

/* FCP_Port Attributes */

/* A bit mask of Phase 1 persistent binding capabilities */
typedef enum HBA_fcpbindingtype {TO_D_ID, TO_WWN, TO_OTHER} HBA_FCPBINDINGTYPE;

/* HBA_BIND_CAPABILITY */
typedef HBA_UINT32 HBA_BIND_CAPABILITY; 

#define HBA_CAN_BIND_TO_D_ID 0x0001 
#define HBA_CAN_BIND_TO_WWPN 0x0002 
#define HBA_CAN_BIND_TO_WWNN 0x0004 
#define HBA_CAN_BIND_TO_LUID 0x0008 
#define HBA_CAN_BIND_ANY_LUNS 0x0400 
#define HBA_CAN_BIND_TARGETS 0x0800 
#define HBA_CAN_BIND_AUTOMAP 0x1000 
#define HBA_CAN_BIND_CONFIGURED 0x2000


/* HBA_BIND_TYPE */
typedef HBA_UINT32 HBA_BIND_TYPE;
#define HBA_BIND_TO_D_ID 0x0001
#define HBA_BIND_TO_WWPN 0x0002
#define HBA_BIND_TO_WWNN 0x0004
#define HBA_BIND_TO_LUID 0x0008
#define HBA_BIND_TARGETS 0x800

typedef struct HBA_LUID {
        char                    buffer[256];
} HBA_LUID, *PHBA_LUID;

typedef struct HBA_ScsiId {
	char 			OSDeviceName[256]; 	/* \device\ScsiPort3  */
	HBA_UINT32		ScsiBusNumber;		/* Bus on the HBA */
	HBA_UINT32		ScsiTargetNumber;	/* SCSI Target ID to OS */
	HBA_UINT32		ScsiOSLun;	
} HBA_SCSIID, *PHBA_SCSIID;

typedef struct HBA_FcpId {
	HBA_UINT32 		FcId;
	HBA_WWN			NodeWWN;
	HBA_WWN			PortWWN;
	HBA_UINT64		FcpLun;
} HBA_FCPID, *PHBA_FCPID;

typedef struct HBA_FcpScsiEntry {
	HBA_SCSIID 		ScsiId;
	HBA_FCPID		FcpId;
} HBA_FCPSCSIENTRY, *PHBA_FCPSCSIENTRY;

typedef struct HBA_FcpScsiEntryV2 { 
        HBA_SCSIID              ScsiId; 
        HBA_FCPID               FcpId; 
        HBA_LUID                LUID; 
} HBA_FCPSCSIENTRYV2, *PHBA_FCPSCSIENTRYV2;

typedef struct HBA_FCPTargetMapping {
	HBA_UINT32		NumberOfEntries;
	HBA_FCPSCSIENTRY 	entry[1];  	/* Variable length array containing mappings*/
} HBA_FCPTARGETMAPPING, *PHBA_FCPTARGETMAPPING;

typedef struct HBA_FCPTargetMappingV2 {
        HBA_UINT32              NumberOfEntries;
        HBA_FCPSCSIENTRYV2      entry[1];       /* Variable length array containing mappings*/
} HBA_FCPTARGETMAPPINGV2, *PHBA_FCPTARGETMAPPINGV2;

typedef struct HBA_FCPBindingEntry {
	HBA_FCPBINDINGTYPE	type;
	HBA_SCSIID		ScsiId;
	HBA_FCPID		FcpId;		/* WWN valid only if type is to WWN, FcpLun always valid */
	HBA_UINT32		FcId;	
} HBA_FCPBINDINGENTRY, *PHBA_FCPBINDINGENTRY;

typedef struct HBA_FCPBinding {
	HBA_UINT32		NumberOfEntries;
	HBA_FCPBINDINGENTRY	entry[1]; 	/* Variable length array */
} HBA_FCPBINDING, *PHBA_FCPBINDING;

typedef struct HBA_FCPBindingEntry2 {
        HBA_BIND_TYPE           type; 
        HBA_SCSIID              ScsiId; 
        HBA_FCPID               FcpId; 
        HBA_LUID                LUID; 
        HBA_STATUS              Status;
} HBA_FCPBINDINGENTRY2, *PHBA_FCPBINDINGENTRY2;

typedef struct HBA_FcpBinding2 {
        HBA_UINT32              NumberOfEntries; 
        HBA_FCPBINDINGENTRY2    entry[1]; /* Variable length array */
} HBA_FCPBINDING2, *PHBA_FCPBINDING2;

/* SB Attributes */
/* Note: Not supported by HBA API Version 2 on AIX, definitions are included in this header
   file to comply with standard */
typedef struct HBA_SBDevId { 
    char OSDeviceName[256]; 
} HBA_SBDEVID, *PHBA_SBDEVID; 

typedef struct HBA_SBId { 
    HBA_UINT32 FcId; 
    HBA_WWN NodeWWN;
    HBA_WWN PortWWN; 
    HBA_UINT32 SBDeviceIdentifier; 
} HBA_SBID, *PHBA_SBID; 

typedef struct HBA_Ned { 
    HBA_UINT32 NEDWord0; 
    HBA_UINT32 NelId[7]; /* Node Element Identifier*/ 
} HBA_NED, *PHBA_NED; /* Node Element Descriptor*/ 

typedef struct HBA_DeviceSelfDesc { 
    HBA_NED TokenNED; 
    HBA_NED DeviceNED; 
} HBA_DEVICESELFDESC, *PHBA_DEVICESELFDESC; 

typedef struct HBA_SBDevEntry { 
    HBA_SBDEVID SBDevId; 
    HBA_SBID SBId; 
    HBA_DEVICESELFDESC DeviceSelfDesc; /* Device Self Description Data*/ 
} HBA_SBDEVENTRY, *PHBA_SBDEVENTRY; 

typedef struct HBA_SBTargetMapping { 
    HBA_UINT32 NumberOfEntries; 
    HBA_SBDEVENTRY entry[1]; /* Variable length array containing mappings*/ 
} HBA_SBTARGETMAPPING, *PHBA_SBTARGETMAPPING;

typedef struct HBA_SBStatistics { 
    HBA_INT32 SSCHRSCHCount; 
    HBA_INT32 SampleCount; 
    HBA_INT32 DeviceConnectTime; 
    HBA_INT32 FunctionPendingTime; 
    HBA_INT32 DeviceDisconnectTime; 
    HBA_INT32 ControlUnitQueuingTime; 
    HBA_INT32 DeviceActiveOnlyTime; 
    HBA_INT32 Reserved; 
    HBA_INT32 Reserved2; 
} HBA_SBSTATISTICS, *PHBA_SBSTATISTICS; 

typedef struct HBA_SBDskCapacity { 
    HBA_INT32 SCSIFormatLBA; /* SCSI Read Capacity Format */ 
    HBA_INT32 SCSIFormatBlkLen; /* SCSI Read Capacity Format */ 
    HBA_INT32 SBDskNumberOfCylinders; /* cyls*/ 
    HBA_INT32 SBDskTracksPerCylinder; /* tracks per cyl */ 
    HBA_INT32 SBDskMaxUsableTrackLen; /* usable track capacity */ 
} HBA_SBDSKCAPACITY, *PHBA_SBDSKCAPACITY;

/* FC-3 Management Atrributes */

typedef enum HBA_wwntype { NODE_WWN, PORT_WWN } HBA_WWNTYPE;

typedef struct HBA_MgmtInfo {
	HBA_WWN 		wwn;
	HBA_UINT32 		unittype;
	HBA_UINT32 		PortId;
	HBA_UINT32 		NumberOfAttachedNodes;
	HBA_UINT16 		IPVersion;
	HBA_UINT16 		UDPPort;
	HBA_UINT8		IPAddress[16];
	HBA_UINT16		reserved;
	HBA_UINT16 		TopologyDiscoveryFlags;
} HBA_MGMTINFO, *PHBA_MGMTINFO;

#define HBA_EVENT_LIP_OCCURRED		1
#define HBA_EVENT_LINK_UP		2
#define HBA_EVENT_LINK_DOWN		3
#define HBA_EVENT_LIP_RESET_OCCURRED	4
#define HBA_EVENT_RSCN			5
#define HBA_EVENT_PROPRIETARY           0xFFFF

typedef struct HBA_Link_EventInfo {
	HBA_UINT32 			PortFcId; 	/* Port which this event occurred */
	HBA_UINT32 			Reserved[3];
} HBA_LINK_EVENTINFO, *PHBA_LINK_EVENTINFO;

typedef struct HBA_RSCN_EventInfo {
	HBA_UINT32 			PortFcId; 	/* Port which this event occurred */
	HBA_UINT32 			NPortPage;   	/* Reference FC-FS for  RSCN ELS "Affected N-Port Pages"*/
	HBA_UINT32 			Reserved[2];
} HBA_RSCN_EVENTINFO, *PHBA_RSCN_EVENTINFO;

typedef struct HBA_Pty_EventInfo {
	HBA_UINT32 			PtyData[4];  	/* Proprietary data */
} HBA_PTY_EVENTINFO, *PHBA_PTY_EVENTINFO;

typedef struct HBA_EventInfo {
	HBA_UINT32 			EventCode;
	union {
	HBA_LINK_EVENTINFO 		Link_EventInfo;
	HBA_RSCN_EVENTINFO 		RSCN_EventInfo;
	HBA_PTY_EVENTINFO 		Pty_EventInfo;
	} Event;
} HBA_EVENTINFO, *PHBA_EVENTINFO;

/* Asynchronous Event Data Declarations */
typedef void *HBA_CALLBACKHANDLE;
#define HBA_EVENT_ADAPTER_ADD 0x101
#define HBA_EVENT_ADAPTER_UNKNOWN 0x100
#define HBA_EVENT_ADAPTER_REMOVE 0x102
#define HBA_EVENT_ADAPTER_CHANGE 0x103
#define HBA_EVENT_PORT_UNKNOWN 0x200
#define HBA_EVENT_PORT_OFFLINE 0x201
#define HBA_EVENT_PORT_ONLINE 0x202
#define HBA_EVENT_PORT_NEW_TARGETS 0x203
#define HBA_EVENT_PORT_FABRIC 0x204
#define HBA_EVENT_PORT_STAT_THRESHOLD 0x301
#define HBA_EVENT_PORT_STAT_GROWTH 0x302
#define HBA_EVENT_TARGET_UNKNOWN 0x400
#define HBA_EVENT_TARGET_OFFLINE 0x401
#define HBA_EVENT_TARGET_ONLINE 0x402
#define HBA_EVENT_TARGET_REMOVED 0x403
#define HBA_EVENT_LINK_UNKNOWN 0x500 
#define HBA_EVENT_LINK_INCIDENT 0x501

typedef struct HBA_LibraryAttributes { 
    HBA_BOOLEAN final; 
    char LibPath[256]; 
    char VName[256]; 
    char VVersion[256]; 
    struct tm build_date; 
} HBA_LIBRARYATTRIBUTES, *PHBA_LIBRARYATTRIBUTES;

/* HBA Library Function Table */

typedef HBA_UINT32  ( * HBAGetVersionFunc)();
typedef HBA_STATUS  ( * HBALoadLibraryFunc)();
typedef HBA_STATUS  ( * HBAFreeLibraryFunc)();
typedef HBA_UINT32  ( * HBAGetNumberOfAdaptersFunc)();
typedef HBA_STATUS  ( * HBAGetAdapterNameFunc)(HBA_UINT32, char*);
typedef HBA_HANDLE  ( * HBAOpenAdapterFunc)(char*);
typedef void	    ( * HBACloseAdapterFunc)(HBA_HANDLE);
typedef HBA_STATUS  ( * HBAGetAdapterAttributesFunc)(HBA_HANDLE, PHBA_ADAPTERATTRIBUTES);
typedef HBA_STATUS  ( * HBAGetAdapterPortAttributesFunc)(HBA_HANDLE, HBA_UINT32, PHBA_PORTATTRIBUTES);
typedef HBA_STATUS  ( * HBAGetPortStatisticsFunc)(HBA_HANDLE, HBA_UINT32, PHBA_PORTSTATISTICS);
typedef HBA_STATUS  ( * HBAGetDiscoveredPortAttributesFunc)(HBA_HANDLE, HBA_UINT32, HBA_UINT32, PHBA_PORTATTRIBUTES);
typedef HBA_STATUS  ( * HBAGetPortAttributesByWWNFunc)(HBA_HANDLE, HBA_WWN, PHBA_PORTATTRIBUTES);
typedef HBA_STATUS  ( * HBASendCTPassThruFunc)(HBA_HANDLE, void *,  HBA_UINT32,  void *,  HBA_UINT32);
typedef void	    ( * HBARefreshInformationFunc)(HBA_HANDLE);
typedef void	    ( * HBAResetStatisticsFunc)(HBA_HANDLE, HBA_UINT32);
typedef HBA_STATUS  ( * HBAGetFcpTargetMappingFunc) (HBA_HANDLE, PHBA_FCPTARGETMAPPING );
typedef HBA_STATUS  ( * HBAGetFcpPersistentBindingFunc) (HBA_HANDLE, PHBA_FCPBINDING );
typedef HBA_STATUS  ( * HBAGetEventBufferFunc)(HBA_HANDLE, PHBA_EVENTINFO, HBA_UINT32 *);
typedef HBA_STATUS  ( * HBASetRNIDMgmtInfoFunc) (HBA_HANDLE, HBA_MGMTINFO);
typedef HBA_STATUS  ( * HBAGetRNIDMgmtInfoFunc)(HBA_HANDLE, PHBA_MGMTINFO);
typedef HBA_STATUS  ( * HBASendRNIDFunc) (HBA_HANDLE, HBA_WWN, HBA_WWNTYPE, void *, HBA_UINT32 *);
typedef HBA_STATUS  ( * HBASendScsiInquiryFunc) (HBA_HANDLE, HBA_WWN, HBA_UINT64, HBA_UINT8, HBA_UINT32, void *, HBA_UINT32, void *, HBA_UINT32 );
typedef HBA_STATUS  ( * HBASendReportLUNsFunc) (HBA_HANDLE, HBA_WWN,void *, HBA_UINT32,void *,HBA_UINT32 );
typedef HBA_STATUS  ( * HBASendReadCapacityFunc) (HBA_HANDLE, HBA_WWN,HBA_UINT64, void *, HBA_UINT32,void *,HBA_UINT32);

/* HBA API Phase 2 prototypes */
typedef HBA_STATUS (* HBAOpenAdapterByWWNFunc) (HBA_HANDLE *, HBA_WWN); 
typedef HBA_STATUS (* HBAGetFcpTargetMappingV2Func) (HBA_HANDLE, HBA_WWN, HBA_FCPTARGETMAPPINGV2 *); 
typedef HBA_STATUS (* HBASendCTPassThruV2Func) (HBA_HANDLE, HBA_WWN, void *, HBA_UINT32, void *, HBA_UINT32 *); 
typedef void (* HBARefreshAdapterConfigurationFunc) (); 
typedef HBA_STATUS (* HBAGetBindingCapabilityFunc) (HBA_HANDLE, HBA_WWN, HBA_BIND_CAPABILITY *); 
typedef HBA_STATUS (* HBAGetBindingSupportFunc) (HBA_HANDLE, HBA_WWN, HBA_BIND_CAPABILITY *); 
typedef HBA_STATUS (* HBASetBindingSupportFunc) (HBA_HANDLE, HBA_WWN, HBA_BIND_CAPABILITY);
typedef HBA_STATUS (* HBASetPersistentBindingV2Func) (HBA_HANDLE, HBA_WWN, const HBA_FCPBINDING2 *); 
typedef HBA_STATUS (* HBAGetPersistentBindingV2Func) (HBA_HANDLE, HBA_WWN, HBA_FCPBINDING2 *); 
typedef HBA_STATUS (* HBARemovePersistentBindingFunc) (HBA_HANDLE, HBA_WWN, const HBA_FCPBINDING2 *); 
typedef HBA_STATUS (* HBARemoveAllPersistentBindingsFunc) (HBA_HANDLE, HBA_WWN); 
typedef HBA_STATUS (* HBASendRNIDV2Func) (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT32, HBA_UINT32, void *, HBA_UINT32*); 
typedef HBA_STATUS (* HBAScsiInquiryV2Func) (HBA_HANDLE,HBA_WWN,HBA_WWN, HBA_UINT64, HBA_UINT8, HBA_UINT8, void *, HBA_UINT32 *, HBA_UINT8 *, void *, HBA_UINT32 *); 
typedef HBA_STATUS (* HBAScsiReportLUNsV2Func) (HBA_HANDLE, HBA_WWN, HBA_WWN, void *, HBA_UINT32 *, HBA_UINT8 *, void *, HBA_UINT32 *); 
typedef HBA_STATUS (* HBAScsiReadCapacityV2Func) (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT64, void *, HBA_UINT32 *, HBA_UINT8 *, void *, HBA_UINT32 *); 
typedef HBA_UINT32 (* HBAGetVendorLibraryAttributesFunc) (HBA_LIBRARYATTRIBUTES *); 
typedef HBA_STATUS (* HBARemoveCallbackFunc) (HBA_CALLBACKHANDLE); 
typedef HBA_STATUS (* HBARegisterForAdapterAddEventsFunc) (void (*)(void *, HBA_WWN, HBA_UINT32), void *,HBA_CALLBACKHANDLE *); 
typedef HBA_STATUS (* HBARegisterForAdapterEventsFunc) (void (*)(void *, HBA_WWN, HBA_UINT32), void *,HBA_HANDLE, HBA_CALLBACKHANDLE *); 
typedef HBA_STATUS (* HBARegisterForAdapterPortEventsFunc) (void (*)(void *, HBA_WWN, HBA_UINT32, HBA_UINT32), void *, HBA_HANDLE, HBA_WWN, HBA_CALLBACKHANDLE *); 
typedef HBA_STATUS (* HBARegisterForAdapterPortStatEventsFunc) (void (*)(void *, HBA_WWN, HBA_UINT32), void *,HBA_HANDLE, HBA_WWN, HBA_PORTSTATISTICS, HBA_UINT32, HBA_CALLBACKHANDLE *); 
typedef HBA_STATUS (* HBARegisterForTargetEventsFunc) (void (*)(void *, HBA_WWN, HBA_WWN, HBA_UINT32), void *, HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_CALLBACKHANDLE *, HBA_UINT32); 
typedef HBA_STATUS (* HBARegisterForLinkEventsFunc) (void (*)(void *, HBA_WWN, HBA_UINT32, void *,HBA_UINT32), void *, void *, HBA_UINT32, HBA_HANDLE, HBA_CALLBACKHANDLE *); 
typedef HBA_STATUS (* HBASendRPLFunc) (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT32, HBA_UINT32, void *, HBA_UINT32 *); 
typedef HBA_STATUS (* HBASendRPSFunc) (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT32, HBA_WWN, HBA_UINT32, void *, HBA_UINT32 *); 
typedef HBA_STATUS (* HBASendSRLFunc) (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT32, void *, HBA_UINT32 *); 
typedef HBA_STATUS (* HBASendLIRRFunc) (HBA_HANDLE, HBA_WWN, HBA_WWN, HBA_UINT8, HBA_UINT8, void *, HBA_UINT32 *);
typedef HBA_STATUS (* HBAGetFC4StatisticsFunc) (HBA_HANDLE, HBA_WWN, HBA_UINT8, HBA_FC4STATISTICS *); 
typedef HBA_STATUS (* HBAGetFCPStatisticsFunc) (HBA_HANDLE, const HBA_SCSIID *, HBA_FC4STATISTICS *); 
typedef HBA_STATUS (* HBASendRLSFunc) (HBA_HANDLE, HBA_WWN, HBA_WWN, void *, HBA_UINT32 *); 
typedef HBA_STATUS (* HBA_GetSBTargetMappingFunc) (HBA_HANDLE, HBA_WWN, HBA_SBTARGETMAPPING *); 
typedef HBA_STATUS (* HBA_GetSBStatisticsFunc) (HBA_HANDLE, const HBA_SBDEVID *, HBA_SBSTATISTICS *); 
typedef HBA_STATUS (* HBA_SBDskGetCapacityFunc) (HBA_DEVICESELFDESC, HBA_SBDSKCAPACITY *);

typedef struct HBA_EntryPoints {
	HBAGetVersionFunc			GetVersionHandler;
	HBALoadLibraryFunc                     	LoadLibraryHandler;
	HBAFreeLibraryFunc                     	FreeLibraryHandler;
	HBAGetNumberOfAdaptersFunc		GetNumberOfAdaptersHandler;
	HBAGetAdapterNameFunc			GetAdapterNameHandler;
	HBAOpenAdapterFunc			OpenAdapterHandler;
	HBACloseAdapterFunc			CloseAdapterHandler;
	HBAGetAdapterAttributesFunc		GetAdapterAttributesHandler;
	HBAGetAdapterPortAttributesFunc		GetAdapterPortAttributesHandler;
	HBAGetPortStatisticsFunc		GetPortStatisticsHandler;
	HBAGetDiscoveredPortAttributesFunc	GetDiscoveredPortAttributesHandler;
	HBAGetPortAttributesByWWNFunc		GetPortAttributesByWWNHandler;
	HBASendCTPassThruFunc			SendCTPassThruHandler;
	HBARefreshInformationFunc		RefreshInformationHandler;
	HBAResetStatisticsFunc			ResetStatisticsHandler;
	HBAGetFcpTargetMappingFunc		GetFcpTargetMappingHandler;
	HBAGetFcpPersistentBindingFunc		GetFcpPersistentBindingHandler;
	HBAGetEventBufferFunc			GetEventBufferHandler;
	HBASetRNIDMgmtInfoFunc			SetRNIDMgmtInfoHandler;
	HBAGetRNIDMgmtInfoFunc			GetRNIDMgmtInfoHandler;
	HBASendRNIDFunc				SendRNIDHandler;
	HBASendScsiInquiryFunc			ScsiInquiryHandler;
	HBASendReportLUNsFunc			ReportLUNsHandler;
	HBASendReadCapacityFunc			ReadCapacityHandler;
} HBA_ENTRYPOINTS, *PHBA_ENTRYPOINTS;

typedef struct HBA_EntryPointsV2 { 
    HBAGetVersionFunc GetVersionHandler; 
    HBALoadLibraryFunc LoadLibraryHandler; 
    HBAFreeLibraryFunc FreeLibraryHandler; 
    HBAGetNumberOfAdaptersFunc GetNumberOfAdaptersHandler; 
    HBAGetAdapterNameFunc GetAdapterNameHandler; 
    HBAOpenAdapterFunc OpenAdapterHandler; 
    HBACloseAdapterFunc CloseAdapterHandler; 
    HBAGetAdapterAttributesFunc GetAdapterAttributesHandler; 
    HBAGetAdapterPortAttributesFunc GetAdapterPortAttributesHandler; 
    HBAGetPortStatisticsFunc GetPortStatisticsHandler; 
    HBAGetDiscoveredPortAttributesFunc GetDiscoveredPortAttributesHandler; 
    HBAGetPortAttributesByWWNFunc GetPortAttributesByWWNHandler; 
    HBASendCTPassThruFunc SendCTPassThruHandler; 
    HBARefreshInformationFunc RefreshInformationHandler; 
    HBAResetStatisticsFunc ResetStatisticsHandler; 
    HBAGetFcpTargetMappingFunc GetFcpTargetMappingHandler; 
    HBAGetFcpPersistentBindingFunc GetFcpPersistentBindingHandler; 
    HBAGetEventBufferFunc GetEventBufferHandler; 
    HBASetRNIDMgmtInfoFunc SetRNIDMgmtInfoHandler; 
    HBAGetRNIDMgmtInfoFunc GetRNIDMgmtInfoHandler; 
    HBASendRNIDFunc SendRNIDHandler; 
    HBASendScsiInquiryFunc ScsiInquiryHandler; 
    HBASendReportLUNsFunc ReportLUNsHandler; 
    HBASendReadCapacityFunc ReadCapacityHandler; 
    HBAOpenAdapterByWWNFunc OpenAdapterByWWNHandler; 
    HBAGetFcpTargetMappingV2Func GetFcpTargetMappingV2Handler; 
    HBASendCTPassThruV2Func SendCTPassThruV2Handler; 
    HBARefreshAdapterConfigurationFunc RefreshAdapterConfigurationHandler; 
    HBAGetBindingCapabilityFunc GetBindingCapabilityHandler; 
    HBAGetBindingSupportFunc GetBindingSupportHandler; 
    HBASetBindingSupportFunc SetBindingSupportHandler; 
    HBASetPersistentBindingV2Func SetPersistentBindingV2Handler; 
    HBAGetPersistentBindingV2Func GetPersistentBindingV2Handler; 
    HBARemovePersistentBindingFunc RemovePersistentBindingHandler; 
    HBARemoveAllPersistentBindingsFunc RemoveAllPersistentBindingsHandler; 
    HBASendRNIDV2Func SendRNIDV2Handler; 
    HBAScsiInquiryV2Func ScsiInquiryV2Handler; 
    HBAScsiReportLUNsV2Func ScsiReportLUNsV2Handler; 
    HBAScsiReadCapacityV2Func ScsiReadCapacityV2Handler; 
    HBAGetVendorLibraryAttributesFunc GetVendorLibraryAttributesHandler; 
    HBARemoveCallbackFunc RemoveCallbackHandler; 
    HBARegisterForAdapterAddEventsFunc RegisterForAdapterAddEventsHandler; 
    HBARegisterForAdapterEventsFunc RegisterForAdapterEventsHandler; 
    HBARegisterForAdapterPortEventsFunc RegisterForAdapterPortEventsHandler; 
    HBARegisterForAdapterPortStatEventsFunc RegisterForAdapterPortStatEventsHandler; 
    HBARegisterForTargetEventsFunc RegisterForTargetEventsHandler; 
    HBARegisterForLinkEventsFunc RegisterForLinkEventsHandler; 
    HBASendRPLFunc SendRPLHandler; 
    HBASendRPSFunc SendRPSHandler; 
    HBASendSRLFunc SendSRLHandler; 
    HBASendLIRRFunc SendLIRRHandler; 
    HBAGetFC4StatisticsFunc GetFC4StatisticsHandler; 
    HBAGetFCPStatisticsFunc GetFCPStatisticsHandler;
    HBASendRLSFunc SendRLSHandler; 
    HBA_GetSBTargetMappingFunc GetSBTargetMappingHandler; 
    HBA_GetSBStatisticsFunc GetSBStatisticsHandler; 
    HBA_SBDskGetCapacityFunc SBDskGetCapacityHandler;
} HBA_ENTRYPOINTSV2, *PHBA_ENTRYPOINTSV2;

/* Phase 1 Function Prototypes */

HBA_API HBA_UINT32 HBA_GetVersion();

HBA_API HBA_STATUS HBA_LoadLibrary();

HBA_API HBA_STATUS HBA_FreeLibrary();

HBA_API HBA_STATUS HBA_RegisterLibrary(PHBA_ENTRYPOINTS entrypoints);

HBA_API HBA_UINT32 HBA_GetNumberOfAdapters();

HBA_API HBA_STATUS HBA_GetAdapterName(
	HBA_UINT32 			adapterindex,
	char 				* adaptername
	);

HBA_API HBA_HANDLE HBA_OpenAdapter(
	char				* adaptername
	);

HBA_API void HBA_CloseAdapter(
	HBA_HANDLE 			handle
	);

HBA_API HBA_STATUS HBA_GetAdapterAttributes(
	HBA_HANDLE 			handle, 
	HBA_ADAPTERATTRIBUTES 		* hbaattributes	
	);

HBA_API HBA_STATUS HBA_GetAdapterPortAttributes(
	HBA_HANDLE 			handle, 
	HBA_UINT32 			portindex,
	HBA_PORTATTRIBUTES 		* portattributes
	);

HBA_API HBA_STATUS HBA_GetPortStatistics(
	HBA_HANDLE			handle,
	HBA_UINT32			portindex,
	HBA_PORTSTATISTICS		* portstatistics
	);

HBA_API HBA_STATUS HBA_GetDiscoveredPortAttributes(
	HBA_HANDLE 			handle, 
	HBA_UINT32 			portindex,
	HBA_UINT32 			discoveredportindex,
	HBA_PORTATTRIBUTES		* portattributes
	);

HBA_API HBA_STATUS HBA_GetPortAttributesByWWN(
	HBA_HANDLE 			handle,
	HBA_WWN	 			PortWWN,
	HBA_PORTATTRIBUTES 		* portattributes
	);

HBA_API HBA_STATUS HBA_SendCTPassThru(
	HBA_HANDLE 			handle, 
	void 				* pReqBuffer,
	HBA_UINT32 			ReqBufferSize,
	void 				* pRspBuffer,  
	HBA_UINT32 			RspBufferSize
	);


HBA_API HBA_STATUS HBA_GetEventBuffer(
	HBA_HANDLE 			handle, 
	PHBA_EVENTINFO 			EventBuffer, 
	HBA_UINT32 			* EventBufferCount
	);

HBA_API HBA_STATUS HBA_SetRNIDMgmtInfo(
	HBA_HANDLE 			handle, 
	HBA_MGMTINFO 			info
	);

HBA_API HBA_STATUS HBA_GetRNIDMgmtInfo(
	HBA_HANDLE 			handle, 
	HBA_MGMTINFO 			* pInfo
	);
	
HBA_API HBA_STATUS HBA_SendRNID(
	HBA_HANDLE 			handle,
	HBA_WWN 			wwn,
	HBA_WWNTYPE 			wwntype,
	void 				* pRspBuffer,
	HBA_UINT32 			* RspBufferSize
	);

HBA_API void HBA_RefreshInformation(
	HBA_HANDLE 			handle
	);

HBA_API void HBA_ResetStatistics(
	HBA_HANDLE 			handle,
	HBA_UINT32 			portindex
	);

HBA_API HBA_STATUS HBA_GetFcpTargetMapping(
	HBA_HANDLE 			handle, 
	PHBA_FCPTARGETMAPPING 		mapping
	);

HBA_API HBA_STATUS HBA_GetFcpPersistentBinding(
	HBA_HANDLE 			handle, 
	PHBA_FCPBINDING 		binding
	);

HBA_API HBA_STATUS HBA_SendScsiInquiry (	
	HBA_HANDLE 			handle,	
	HBA_WWN 			PortWWN, 
	HBA_UINT64 			fcLUN, 
	HBA_UINT8 			EVPD, 
	HBA_UINT32 			PageCode, 
	void 				* pRspBuffer, 
	HBA_UINT32 			RspBufferSize, 
	void 				* pSenseBuffer, 
	HBA_UINT32 			SenseBufferSize
	);

HBA_API HBA_STATUS HBA_SendReportLUNs (
	HBA_HANDLE 			handle,
	HBA_WWN 			portWWN,
	void 				* pRspBuffer, 
	HBA_UINT32 			RspBufferSize,
	void 				* pSenseBuffer,
	HBA_UINT32 			SenseBufferSize
	);

HBA_API HBA_STATUS HBA_SendReadCapacity (
	HBA_HANDLE 			handle,
	HBA_WWN 			portWWN,
	HBA_UINT64 			fcLUN,
	void 				* pRspBuffer, 
	HBA_UINT32 			RspBufferSize,
	void 				* pSenseBuffer,
	HBA_UINT32 			SenseBufferSize
	);


/* Phase 2 Function Prototypes */
HBA_API HBA_STATUS HBA_RegisterLibraryV2(HBA_ENTRYPOINTSV2 *pHBAInfo);

HBA_API HBA_STATUS HBA_OpenAdapterByWWN( 
        HBA_HANDLE *pHandle, 
        HBA_WWN wwn 
    );

HBA_API HBA_STATUS HBA_GetFcpTargetMappingV2( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_FCPTARGETMAPPINGV2 *pMapping
    );

HBA_API HBA_STATUS HBA_SendCTPassThruV2( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        void *pReqBuffer, 
        HBA_UINT32 ReqBufferSize, 
        void *pRspBuffer, 
        HBA_UINT32 *pRspBufferSize 
    );

HBA_API void HBA_RefreshAdapterConfiguration();

HBA_API HBA_STATUS HBA_GetBindingCapability( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_BIND_CAPABILITY*pFlags 
    );

HBA_API HBA_STATUS HBA_GetBindingSupport( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_BIND_CAPABILITY*pFlags 
    );

HBA_API HBA_STATUS HBA_SetBindingSupport( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_BIND_CAPABILITY flags 
    );

HBA_API HBA_STATUS HBA_SetPersistentBindingV2( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        const HBA_FCPBINDING2 *binding 
    );

HBA_API HBA_STATUS HBA_GetPersistentBindingV2( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_FCPBINDING2 *binding 
    );

HBA_API HBA_STATUS HBA_RemovePersistentBinding( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        const HBA_FCPBINDING2 *binding 
    );

HBA_API HBA_STATUS HBA_RemoveAllPersistentBindings( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN 
    );

HBA_API HBA_STATUS HBA_SendRNIDV2( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_WWN destWWN, 
        HBA_UINT32 destFCID, 
        HBA_UINT32 NodeIdDataFormat, 
        void *pRspBuffer, 
        HBA_UINT32 *pRspBufferSize 
    );

HBA_API HBA_STATUS HBA_ScsiInquiryV2 ( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_WWN discoveredPortWWN, 
        HBA_UINT64 fcLUN, 
        HBA_UINT8 CDB_Byte1, 
        HBA_UINT8 CDB_Byte2, 
        void *pRspBuffer, 
        HBA_UINT32 *pRspBufferSize, 
        HBA_UINT8 *pScsiStatus, 
        void *pSenseBuffer, 
        HBA_UINT32 *pSenseBufferSize 
    );

HBA_API HBA_STATUS HBA_ScsiReportLUNsV2( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_WWN discoveredPortWWN, 
        void *pRspBuffer, 
        HBA_UINT32 *pRspBufferSize, 
        HBA_UINT8 *pScsiStatus, 
        void *pSenseBuffer, 
        HBA_UINT32 *pSenseBufferSize 
    );

HBA_API HBA_STATUS HBA_ScsiReadCapacityV2( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_WWN discoveredPortWWN, 
        HBA_UINT64 fcLUN, 
        void *pRspBuffer, 
        HBA_UINT32 *pRspBufferSize, 
        HBA_UINT8 *pScsiStatus, 
        void *pSenseBuffer, 
        HBA_UINT32 *pSenseBufferSize 
    );

HBA_API HBA_UINT32 HBA_GetWrapperLibraryAttributes(
        HBA_LIBRARYATTRIBUTES *attributes
    );

HBA_API HBA_UINT32 HBA_GetVendorLibraryAttributes( 
        HBA_UINT32 adapter_index, 
        HBA_LIBRARYATTRIBUTES *attributes 
    );

HBA_API HBA_STATUS HBA_RemoveCallback( 
        HBA_CALLBACKHANDLE callbackHandle 
    );

HBA_API HBA_STATUS HBA_RegisterForAdapterAddEvents( 
        void (*pCallback) ( 
              void *pData, 
              HBA_WWN PortWWN, 
              HBA_UINT32 eventType
            ), 
        void *pUserData, 
        HBA_CALLBACKHANDLE *pCallbackHandle 
    );

HBA_API HBA_STATUS HBA_RegisterForAdapterEvents( 
        void (*pCallback) ( 
              void *pData, 
              HBA_WWN PortWWN, 
              HBA_UINT32 eventType
            ), 
        void *pUserData, 
        HBA_HANDLE handle, 
        HBA_CALLBACKHANDLE *pCallbackHandle 
    );

HBA_API HBA_STATUS HBA_RegisterForAdapterPortEvents( 
        void (*pCallback) ( 
              void *pData, 
              HBA_WWN PortWWN, 
              HBA_UINT32 eventType, 
              HBA_UINT32 fabricPortID
            ), 
        void *pUserData, 
        HBA_HANDLE handle, 
        HBA_WWN PortWWN, 
        HBA_CALLBACKHANDLE *pCallbackHandle 
    );

HBA_API HBA_STATUS HBA_RegisterForAdapterPortStatEvents( 
        void (*pCallback) ( 
              void *pData, 
              HBA_WWN PortWWN, 
              HBA_UINT32 eventType 
              ), 
        void *pUserData, 
        HBA_HANDLE handle, 
        HBA_WWN PortWWN, 
        HBA_PORTSTATISTICS stats, 
        HBA_UINT32 statType, 
        HBA_CALLBACKHANDLE *pCallbackHandle 
    );

HBA_API HBA_STATUS HBA_RegisterForTargetEvents( 
        void (*pCallback) ( 
              void *pData, 
              HBA_WWN hbaPortWWN, 
              HBA_WWN discoveredPortWWN, 
              HBA_UINT32 eventType
              ), 
        void *pUserData, 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_WWN discoveredPortWWN, 
        HBA_CALLBACKHANDLE *pCallbackHandle, 
        HBA_UINT32 allTargets 
    );

HBA_API HBA_STATUS HBA_RegisterForLinkEvents( 
        void (*pCallback) ( 
              void *pData, 
              HBA_WWN adapterWWN, 
              HBA_UINT32 eventType, 
              void *pRLIRBuffer, 
              HBA_UINT32 RLIRBufferSize 
              ), 
        void *pUserData, 
        void *pRLIRBuffer, 
        HBA_UINT32 RLIRBufferSize, 
        HBA_HANDLE handle, 
        HBA_CALLBACKHANDLE *pCallbackHandle 
    );

HBA_API HBA_STATUS HBA_SendRPL ( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_WWN agent_wwn, 
        HBA_UINT32 agent_domain, 
        HBA_UINT32 portIndex, 
        void *pRspBuffer, 
        HBA_UINT32 *pRspBufferSize 
    );

HBA_API HBA_STATUS HBA_SendRPS ( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_WWN agent_wwn, 
        HBA_UINT32 agent_domain, 
        HBA_WWN object_wwn, 
        HBA_UINT32 object_port_number, 
        void *pRspBuffer, 
        HBA_UINT32 *pRspBufferSize
    );

HBA_API HBA_STATUS HBA_SendSRL ( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_WWN wwn, 
        HBA_UINT32 domain, 
        void *pRspBuffer, 
        HBA_UINT32 *pRspBufferSize 
    );

HBA_API HBA_STATUS HBA_SendLIRR ( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_WWN destWWN, 
        HBA_UINT8 function, 
        HBA_UINT8 type,
        void *pRspBuffer, 
        HBA_UINT32 *pRspBufferSize 
    );

HBA_API HBA_STATUS HBA_GetFC4Statistics( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_UINT8 FC4type, 
        HBA_FC4STATISTICS *statistics 
    );

HBA_API HBA_STATUS HBA_GetFCPStatistics( 
        HBA_HANDLE handle, 
        const HBA_SCSIID *lunit, 
        HBA_FC4STATISTICS *statistics 
    );

HBA_API HBA_STATUS HBA_SendRLS ( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_WWN destWWN, 
        void *pRspBuffer, 
        HBA_UINT32 *pRspBufferSize 
    );

HBA_API HBA_STATUS HBA_GetSBTargetMapping ( 
        HBA_HANDLE handle, 
        HBA_WWN hbaPortWWN, 
        HBA_SBTARGETMAPPING *pMapping 
    );

HBA_API HBA_STATUS HBA_GetSBStatistics ( 
        HBA_HANDLE handle, 
        const HBA_SBDEVID *device, 
        HBA_SBSTATISTICS *statistics 
    );

HBA_API HBA_STATUS HBA_SBDskGetCapacity ( 
        HBA_DEVICESELFDESC DeviceSelfDesc, 
        HBA_SBDSKCAPACITY *pSBDskCapacity 
    );
#endif

#ifdef __cplusplus
}
#endif


