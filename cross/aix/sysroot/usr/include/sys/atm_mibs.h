/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/atm_mibs.h 1.2                               */
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
/* @(#)30  1.2 src/bos/kernel/sys/atm_mibs.h, sysxatm, bos530 4/24/97 16:29:29
  *
  * COMPONENT_NAME: sysxatm
  *
  * FUNCTIONS: none
  *
  * ORIGINS: 27
  *
  *                  -- (                            when
  * combined with the aggregated modules for this product)
  * OBJECT CODE ONLY SOURCE MATERIALS
  *
  * (C) COPYRIGHT International Business Machines Corp. 1995
  * All Rights Reserved
  *
  * US Government Users Restricted Rights - Use, duplication or
  * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
  */


#ifndef _H_ATM_MIBS
#define _H_ATM_MIBS
typedef struct atmInterfaceConfEntry {


#define atmInterfaceMaxVpcs             0x0
        __ulong32_t  max_vpcs;

#define atmInterfaceMaxVccs             0x1
        __ulong32_t  max_vccs;

#define atmInterfaceConfVpcs            0x2
        __ulong32_t  conf_vpcs;

#define atmInterfaceConfVccs            0x3
        __ulong32_t  conf_vccs;

#define atmInterfaceMaxActiveVpiBits    0x4
        __ulong32_t  active_vpi_bits;

#define atmInterfaceMaxActiveVciBits    0x5
        __ulong32_t  active_vci_bits;

#define atmInterfaceIlmiVpi             0x6
        __ulong32_t  ilmi_vpi;

#define atmInterfaceIlmiVci             0x7
        __ulong32_t  ilmi_vci;

#define atmInterfaceAddressType         0x8
        __ulong32_t  int_address;

#define atmInterfaceAdminAddress        0x9
        unsigned char  admin_address[20];

#define atmInterfaceMyNeighbourIpAddress        0xa
        unsigned char  neighbour_ip_addr[4];


#define atmInterfaceMyNeighbourIfName        0xb
        unsigned char  neighbour_if_name[20];

}atmInterfaceConfEntry_t;


typedef struct atmTrafficDescrParamEntry {

#define atmTrafficDescrType             0x10
        __ulong32_t  descr_type;

#define atmTrafficDescrParam1           0x11
        __ulong32_t  tparam1;

#define atmTrafficDescrParam2           0x12
        __ulong32_t  tparam2;

#define atmTrafficDescrParam3           0x13
        __ulong32_t  tparam3;

#define atmTrafficDescrParam4           0x14
        __ulong32_t  tparam4;

#define atmTrafficDescrParam5           0x15
        __ulong32_t  tparam5;

#define atmTrafficQoSClass              0x16
        __ulong32_t  qos;

#define atmTrafficDescrRowStatus        0x17
        __ulong32_t  rowstatus;

}atmTrafficDescrParamEntry_t;

typedef struct atmVclEntry {

#define atmVclAdminStatus                0x20
        __ulong32_t  adminstatus;

#define atmVclOperStatus                 0x21
        __ulong32_t  operstatus;

#define atmVclLastChange                 0x22
        __ulong32_t  lastchange;

#define atmVclReceiveTrafficDescrIndex   0x23
        __ulong32_t  rxtrafficindex;

#define atmVclTransmitTrafficDescrIndex  0x24
        __ulong32_t  txtrafficindex;

#define atmVccAalType                    0x25
        __ulong32_t  aaltype;

#define atmVccAal5CpcsTransmitSduSize    0x26
        __ulong32_t  xmitsdusize;

#define atmVccAal5CpcsReceiveSduSize     0x27
        __ulong32_t  rcevsdusize;

#define atmVccAal5EncapsType             0x28
        __ulong32_t  encaptype;

#define atmVclCrossConnectIdentifier     0x29
        __ulong32_t  connid;

#define atmVclRowStatus                  0x2a
        __ulong32_t  rowstatus;
}atmVclEntry_t;


typedef struct aal5VccEntry {
#define aal5VccVpi                      0x50
        __ulong32_t  vccvpi;

#define aal5VccVci                      0x51
        __ulong32_t  vccvci;

#define aal5VccCrcErrors                0x52
        __ulong32_t  vcccrc;

#define aal5VccSarTimeOuts              0x53
        __ulong32_t  sartimeout;

#define aal5VccOverSizedSDUs            0x54
        __ulong32_t  oversizedsdu;

}aal5VccEntry_t;


typedef struct atom_mib  {
        atmInterfaceConfEntry_t      atmInterfaceConfEntry;
        atmTrafficDescrParamEntry_t  atmTrafficDescParamEntry;
        atmVclEntry_t                atmVclEntry;
        aal5VccEntry_t               aal5VccEntry;
}  atom_mib_t;

typedef struct AtmAdapterEntry {

#define atmAdapterIndex                0x0
        __ulong32_t  adapt_index;

#define atmAdapterSerialNumber         0x1
        __ulong32_t  serial_no;

#define atmAdapterDiagVersion          0x2
        __ulong32_t  diag_ver;

#define atmAdapterSoftwareVersion      0x3
        __ulong32_t  soft_ver;

#define atmAdapterFlowControlMechanism 0x4
        __ulong32_t  flow_cnt;

}AtmAdapterEntry_t;

typedef struct atmfPortEntry {

#define atmfPortIndex                0x0
        __ulong32_t  port_index;

#define atmfPortAddress              0x1
        unsigned char port_address[20];

#define atmfPortTransmissionType     0x2
        __ulong32_t  tx_type;

#define atmfPortMediaType            0x3
        __ulong32_t  media_type;

#define atmfPortOperStatus           0x4
        __ulong32_t  oper_status;

#define atmfPortSpecific             0x5
        __ulong32_t  port_specific;
}atmfPortEntry_t;

/* The atm layer group */
typedef struct  atmfAtmLayerEntry  {

#define atmfAtmLayerIndex            0x10
        __ulong32_t  layer_index;

#define atmfAtmLayerMaxVPCs          0x11
        __ulong32_t  maxvpcs;

#define atmfAtmLayerMaxVCCs          0x12
        __ulong32_t  maxvccs;

#define atmfAtmLayerConfiguredVPCs   0x13
        __ulong32_t  configvpcs;

#define atmfAtmLayerConfiguredVCCs   0x14
        __ulong32_t  configvccs;

#define atmfAtmLayerMaxvpiBits       0x15
        __ulong32_t  configvpi;

#define atmfAtmLayerMaxvciBits       0x16
        __ulong32_t  configvci;

#define atmfAtmLayerUniType          0x17
        __ulong32_t  unitype;
}atmfAtmLayerEntry_t;

typedef struct atmfAtmStatsEntry {

#define atmfAtmStatsIndex                  0x20
        __ulong32_t  stats_index;

#define atmfAtmStatsReceivedCells          0x21
        __ulong32_t  recvd_cells;

#define atmfAtmStatsDroppedReceivedCells   0x22
        __ulong32_t  dropped_cells;

#define atmfAtmStatsTransmittedCells       0x23
        __ulong32_t  trans_cells;

}atmfAtmStatsEntry_t;


typedef struct atmfVccEntry {
#define atmfVccPortIndex                        0x30
        __ulong32_t  port_index;

#define atmfVccVpi                              0x31
        __ulong32_t  vcc_vpi;

#define atmfVccVci                              0x32
        __ulong32_t  vcc_vci;

#define atmfVccOperStatus                       0x33
        __ulong32_t  vcc_oper;

#define atmfVccTransmitTrafficDescriptorType    0x34
        __ulong32_t  txtraffic_desc_type;

#define atmfVccTransmitTrafficDescriptorParam1  0x35
        __ulong32_t  txtraffic_desc_parm1;

#define atmfVccTransmitTrafficDescriptorParam2  0x36
        __ulong32_t  txtraffic_desc_parm2;

#define atmfVccTransmitTrafficDescriptorParam3  0x37
        __ulong32_t  txtraffic_desc_parm3;

#define atmfVccTransmitTrafficDescriptorParam4  0x38
        __ulong32_t  txtraffic_desc_parm4;

#define atmfVccTransmitTrafficDescriptorParam5  0x39
        __ulong32_t  txtraffic_desc_parm5;

#define atmfVccReceiveTrafficDescriptorType     0x3a
        __ulong32_t  rxtraffic_desc_type;

#define atmfVccReceiveTrafficDescriptorParam1   0x3b
        __ulong32_t  rxtraffic_desc_parm1;

#define atmfVccReceiveTrafficDescriptorParam2   0x3c
        __ulong32_t  rxtraffic_desc_parm2;

#define atmfVccReceiveTrafficDescriptorParam3   0x3d
        __ulong32_t  rxtraffic_desc_parm3;

#define atmfVccReceiveTrafficDescriptorParam4   0x3e
        __ulong32_t  rxtraffic_desc_parm4;

#define atmfVccReceiveTrafficDescriptorParam5   0x3f
        __ulong32_t  rxtraffic_desc_parm5;

#define atmfVccQoSCategory                      0x40
        __ulong32_t  vccqoscat;

#define atmfVccTransmitQoSClass                 0x41
        __ulong32_t  txqoscat;


#define atmfVccReceiveQoSClass                  0x42
        __ulong32_t  rxqoscat;

}atmfVccEntry_t;



typedef struct ilmi_mib  {
        atmfPortEntry_t      atmfPortEntry;
        atmfAtmLayerEntry_t  atmfLayerEntry;
        atmfAtmStatsEntry_t  atmfStatsEntry;
        atmfVccEntry_t       atmfVccEntry;
}  ilmi_mib_t;


/* The SONET MIB has the following groups */

typedef struct sonetMediumEntry {

#define sonetMediumType                0x0
        __ulong32_t  medium_type;

#define sonetMediumTimeElapsed         0x1
        __ulong32_t  time_elapsed;

#define sonetMediumValidIntervals      0x2
        __ulong32_t  valid_intervals;

#define sonetMediumLineCoding          0x3
        __ulong32_t  line_coding;

#define sonetMediumLineType            0x4
        __ulong32_t  line_type;

#define sonetMediumCircuitIdentifier   0x5
        unsigned char  circuit_id[50];

}sonetMediumEntry_t;

typedef struct sonetSectionCurrentEntry {

#define sonetSectionCurrentStatus      0x10
        __ulong32_t  sect_status;

#define sonetSectionCurrentESs         0x11
        __ulong32_t  sect_errsec;

#define sonetSectionCurrentSESs        0x12
        __ulong32_t  sect_severr;


#define sonetSectionCurrentCVs         0x13
        __ulong32_t  sect_violations;

}sonetSectionCurrentEntry_t;


typedef struct sonetLineCurrentEntry {
#define sonetLineCurrentStatus         0x30
        __ulong32_t  line_status;

#define sonetLineCurrentESs            0x31
        __ulong32_t  line_errsec;

#define sonetLineCurrentSESs           0x32
        __ulong32_t  line_severr;

#define sonetLineCurrentCVs            0x33
        __ulong32_t  line_violations;

#define sonetLineCurrentUASs           0x34
        __ulong32_t  line_uas;

}sonetLineCurrentEntry_t;



typedef struct sonetPathCurrentEntry {

#define sonetPathCurrentWidth         0x60
        __ulong32_t  path_width;

#define sonetPathCurrentStatus         0x61
        __ulong32_t  path_status;

#define sonetPathCurrentESs            0x62
        __ulong32_t  path_errsec;

#define sonetPathCurrentSESs           0x63
        __ulong32_t  path_severr;

#define sonetPathCurrentCVs            0x64
        __ulong32_t  path_violations;

#define sonetPathCurrentUASs           0x65
        __ulong32_t  path_uas;

}sonetPathCurrentEntry_t;


typedef struct sonet_mib  {
        sonetMediumEntry_t            sonetMediumEntry;
        sonetSectionCurrentEntry_t    sonetSectionCurrentEntry;
        sonetLineCurrentEntry_t       sonetLineCurrentEntry;
        sonetPathCurrentEntry_t       sonetPathCurrentEntry;
}  sonet_mib_t;

typedef struct atm_all_mib  {
        ilmi_mib_t         Ilmi_mib;
        sonet_mib_t        Sonet_mib;
        atom_mib_t         Atom_mib;
        AtmAdapterEntry_t  Adapter_mib;
        int                static_flag;
}  Atm_all_mib_t;

typedef struct snmp_static_mib {
        __ulong32_t max_vpcs;
        __ulong32_t max_vccs;
        __ulong32_t conf_vpcs;
        __ulong32_t conf_vccs;
        __ulong32_t active_vpi_bits;
        __ulong32_t active_vci_bits;
        __ulong32_t xmitsdusize;
        __ulong32_t serial_no;
        __ulong32_t diag_ver;
        __ulong32_t soft_ver;
        __ulong32_t flow_cnt;
        __ulong32_t tx_type;
        __ulong32_t media_type;
        } Snmp_static_mib_t;


typedef struct snmp_dynamic_mib {
        __ulong32_t tparam1;
        __ulong32_t vcccrc;
        __ulong32_t oversizedsdu;
        __ulong32_t recvd_cells;
        __ulong32_t dropped_cells;
        __ulong32_t trans_cells;
        __ulong32_t sect_status;
        __ulong32_t sect_errsec;
        __ulong32_t sect_severr;
        __ulong32_t sect_violations;
        __ulong32_t line_status;
        __ulong32_t line_errsec;
        __ulong32_t line_severr;
        __ulong32_t line_violations;
        __ulong32_t line_uas;
        __ulong32_t path_status;
        __ulong32_t path_errsec;
        __ulong32_t path_severr;
        __ulong32_t path_violations;
        __ulong32_t path_uas;
        } Snmp_dynamic_mib_t;

#endif  /* _H_atm_mibs */
