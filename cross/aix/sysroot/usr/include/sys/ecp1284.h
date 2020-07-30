/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* rspc530 src/rspc/usr/include/sys/ecp1284.h 1.4                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)86	1.2  src/rspc/usr/include/sys/ecp1284.h, sysxprnt, rspc43D 11/16/97 22:46:32  */
/*
 *   COMPONENT_NAME: sysxprnt
 *
 * FUNCTIONS:
 *
 *   ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _H_IEEE1284
#define _H_IEEE1284

#include <sys/types.h>

/*
 * IEEE 1284 "dot" protocol definitions.
 */
/*
 * Note that all bit encodings reflect the document as to bit order, and not
 * the transmitted (big endian) order.
 */

#ifdef __cplusplus
extern "C" {
#endif

#pragma options enum=small
enum ieee1284Interpreter             /* Interpreter types. */
{
    InterpCMD
    , InterpPCL
    , InterpPostscript
    , InterpOther
};
#pragma options enum=reset
typedef enum ieee1284Interpreter ieee1284Interpreter;


#pragma options enum=small
enum ByteLU                     /* maximum logical units */
{
    DefaultInterpreter
    , InterpreterUnknown = 0xFF
};
#pragma options enum=reset
typedef enum  ByteLU ByteLU;

struct ieee1284_lu              /* Used to pass in ioctl */
{
    ieee1284Interpreter type;
    uint :16;
    ByteLU              channel;
};
typedef struct ieee1284_lu ieee1284_lu;

#pragma options align=packed
struct clen_str                 /* char length string */
{
    uchar clen;
    uchar cval[1];
};
#pragma options align=reset
typedef struct clen_str clen_str;

#pragma options align=packed
struct slen_str                 /* short length string */
{
    ushort slen;
    uchar  sval[1];
};
#pragma options align=reset
typedef struct slen_str slen_str;


/* ======================================== Request Device Characteristics */
#pragma options enum=small
enum RDCSubCommand
{
    RDCSummaryInfo
    , RDCReserved
    , RDCInputCharacteristics
    , RDCOutputCharacteristics
    , RDCOptionCharacteristics
};
#pragma options enum=reset
typedef enum RDCSubCommand RDCSubCommand;

                                /* Request Summary RDC-RS */
#pragma options enum=small
enum MarkingTechnologyCodes
{
    ElectroPhotoGrahic
    , ImpactDotMatrix, ImpactFormed, ImpactBand
    , InkJetAqueous, InkJetSolid
    , Pen
    , ThermalTransfer, ThermalSensitive, ThermalDiffusion
    , ElectroStatic, Photographic, IonDeposition
    , EBeam, Typesetter, ElectroErosion, InkJetOther, ThermalOther
    , MTCOther = 0xFE, MTCUnknown = 0xFF
};
#pragma options enum=reset
typedef enum MarkingTechnologyCodes MarkingTechnologyCodes;


#pragma options enum=small
enum ColorCapabilityCodes
{
    Monochrome, SpotColor, CMYColor, CMYKColor
    , CCCOther = 0xFE, CCCUnknown
};
#pragma options enum=reset
typedef enum ColorCapabilityCodes ColorCapabilityCodes;


#pragma options align=packed
struct duplex_capability
{
    uint :6;                    /* bits 7-2 */
    uint long_edge_capable:1;   /* bit 1 */
    uint short_edge_capable:1;  /* bit 0 */
};
#pragma options align=reset
typedef struct duplex_capability duplex_capability;

#pragma options enum=small
enum SpeedUnitsCodes
{
    SheetsPerMinute
    , InchesPerSec, FeetPerSec, YardsPerSec
    , MillimetersPerSec, CentimetersPerSec, DecimetersPerSec, MetersPerSec
    , CharactersPerSec, TensCharactersPerSec
    , HundredsCharactersPerSec, ThousandsCharactersSec
    , LinesPerMinute, TensLinesPerMinute
    , HundredsLinesPerMinute, ThousandsLinesPerMinute
    , SUCOther = 0xFE, SUCUnknown = 0xFF
};
#pragma options enum=reset
typedef enum SpeedUnitsCodes SpeedUnitsCodes;

#pragma options enum=small
enum LengthUnitsCodes
{
    Pages, Inches, Feet, Yards
    , Millimeters, Centimeters, Decimeters, Meters
    , Characters, TensCharacters, HundredsCharacters, ThousandsCharacters
    , Lines, TensLines, HundredsLines, ThousandsLines
    , LUCOther = 0xFE, LUCUnknown = 0xFF
};
#pragma options enum=reset
typedef enum LengthUnitsCodes LengthUnitsCodes;

#pragma options enum=small
enum LanguageCodes
{
    English, German, French, CanadianFrench, Spanish, Italian, Danish
    , Norwegian, Dutch, Japanese, Korean, TraditionalChinese, SimplfiedChinese
    , Swedish, LCOther = 0xFE, LCUnknown = 0xFF
};
#pragma options enum=reset
typedef enum LanguageCodes LanguageCodes;


#pragma options align=packed
struct rdc_rs
{
    RDCSubCommand sub_command;
};
#pragma options align=reset
typedef struct rdc_rs rdc_rs;

#pragma options align=packed
struct rdc_rs_reply
{
    RDCSubCommand          sub_command;
    uchar                  std_major;
    uchar                  std_minor;
    uchar                  prt_exten_rev;
    MarkingTechnologyCodes marking_technology;
    ColorCapabilityCodes   color_cap;
    ushort                 color_levels;
    duplex_capability      duplex_cap;
    ushort                 max_entries_query_queue;
    SpeedUnitsCodes        speed_units_def;
    uchar                  speed_units;
    LengthUnitsCodes       len_units_def;
    ushort                 hor_logical_units;
    ushort                 ver_logical_units;
    uchar                  counter_units;
    uchar                  resvd0;
    uint                   total_installed_memory;
    ushort                 max_receive_packet_size;
    ushort                 max_outstanding_commands;
    uchar                  resvd1;
    uchar                  num_interpreters_supported;
    uchar                  num_inputs_supported;
    uchar                  num_outputs_supported;
    uchar                  num_options_supported;
    LanguageCodes          printer_language;
    clen_str               product_name;
        /* This followed by: */
        /* clen_str product_revision; */
        /* clen_str serial_number; */
        /* ushort max_receive_cmd_buffer_size; */
};
#pragma options align=reset
typedef struct rdc_rs_reply rdc_rs_reply;


/* ===================================== Request Input Characteristics RIC- */
/* Details of all print media input sources of the printer. */

#pragma options enum=small
enum InputFeedCodes
{
    IFCReserved
    , IFCSheetFeedAuto
    , IFCSheetFeedManual
    , IFCContinuousRoll
    , IFCContinuousFanFold
    , IFCOther              = 0xFE
    , IFCUnknown            = 0xFF
};
#pragma options enum=reset
typedef enum InputFeedCodes InputFeedCodes;

#pragma options enum=small
enum InputMediumCharacteristicCodes
{
    IMCReserved
    , IMCPaper
    , IMCEnvelope
    , IMCTransparency
    , IMCReservedRangeStart = 0x05
    , IMCReservedRangeEnd   = 0xFD
    , IMCOther              = 0xFE
    , IMCUnknown            = 0xFF
};
#pragma options enum=reset
typedef enum InputMediumCharacteristicCodes InputMediumCharacteristicCodes;

#pragma options enum=small
enum InputMediumSizeCodes
{
    IMSISOA           = 0x01
    , IMSISOB
    , IMSISOC
    , IMSISOD
    , IMSISOE
    , IMSISOF
    , IMSLegal
    , IMSHalfLetter
    , IMSExecutive    = 0x09

    , IMS_4A0         = 0x10
    , IMS_2A0
    , IMSISOA0
    , IMSISOA1
    , IMSISOA2
    , IMSISOA3
    , IMSISOA4
    , IMSISOA5
    , IMSISOA6
    , IMSISOA7
    , IMSISOA8
    , IMSISOA9
    , IMSISOA10       = 0x1C

    , IMSRA0          = 0x20
    , IMSRA1
    , IMSRA2
    , IMSSRA0
    , IMSSRA1

    , IMSISOB0        = 0x30
    , IMSISOB1
    , IMSISOB2
    , IMSISOB3
    , IMSISOB4
    , IMSISOB5
    , IMSISOB6
    , IMSISOB7
    , IMSISOB8
    , IMSISOB9
    , IMSISOB10       = 0x3A

    , IMSISOC0        = 0x40
    , IMSISOC1
    , IMSISOC2
    , IMSISOC3
    , IMSISOC4
    , IMSISOC5
    , IMSISOC6
    , IMSISOC7
    , IMSISOC8        = 0x48

    , IMSEnvelopeC3   = 0x50
    , IMSEnvelopeB4
    , IMSEnvelopeC4
    , IMSEnvelopeB5
    , IMSEnvelopeC5
    , IMSEnvelopeB6_C4
    , IMSEnvelopeB6
    , IMSEnvelopeC6
    , IMSEnvelopeDL
    , IMSEnvelopeC7_C6
    , IMSEnvelopeC7

    , IMSPostCard     = 0x60

    , IMSJISB0        = 0x70
    , IMSJISB1
    , IMSJISB2
    , IMSJISB3
    , IMSJISB4
    , IMSJISB5
    , IMSJISB6
    , IMSJISB7
    , IMSJISB8
    , IMSJISB9
    , IMSJISB10       = 0x7A

    , IMSEnvelope7_34 = 0x80
    , IMSEnvelope9
    , IMSEnvelope10   = 0x82

    , IMSOther        = 0xFE
    , IMSUnknown      = 0xFF
};
#pragma options enum=reset
typedef enum InputMediumSizeCodes InputMediumSizeCodes;

#pragma options align=packed
struct rdc_ric_reply_hdr
{
    RDCSubCommand sub_command;
    uchar         input_id;
};
#pragma options align=reset
typedef struct rdc_ric_reply_hdr rdc_ric_reply_hdr;

    /* =============== Request Interpreter Characteristics ================= */
                                /* RIC-RS Summary Information */
#pragma options enum=small
enum RICSubCommand
{
    RICSummaryInfo
    , RICFontDetails
    , RICInputCharacteristics
    , RICOutputCharacteristics
    , RICReservedRangeEnd   = 0xFF
};
#pragma options enum=reset
typedef enum RICSubCommand RICSubCommand;

#pragma options align=packed
struct ric_si
{
    RICSubCommand sub_command;
    ByteLU        lun;
};
#pragma options align=reset
typedef struct ric_si ric_si;

#pragma options enum=small
enum RICLUFreeMem
{
    RS_LUN_FREE_MEM_NOTAVAIL = 0xFFFFFFFF
};
typedef enum RICLUFreeMem RICLUFreeMem;

enum RICLUNumFonts
{
    RICLUNumFontsNotAvail = 0xFFFF
};
typedef enum RICLUNumFonts RICLUNumFonts;

enum RICLUNumInputs
{
    RICLUNumInputsNotAvail = 0xFF
};
typedef enum RICLUNumInputs RICLUNumInputs;

enum RICLUNumOutputs
{
    RICLUNumOutputsNotAvail = 0xFF
};
#pragma options enum=reset
typedef enum RICLUNumOutputs RICLUNumOutputs;

#pragma options align=packed
struct ric_lu_features
{
    ByteLU       lun;
    struct
    {
        uint :2;                         /* bits 7-6 reserved */
        uint can_report_download_font:1; /* bit 5 */
        uint can_report_fontcard:1;      /* bit 4 */
        uint can_report_resident_font:1; /* bit 3 */
        uint interpreter_concurrent:1;   /* bit 2 */
        uint state_save_on_switch:1;     /* bit 1 */
        uint features_valid:1;           /* bit 0 */
    } summary;
    uint :8;
    RICLUFreeMem    max_lun_free_memory;
    RICLUNumFonts   num_fonts;
    RICLUNumInputs  num_input_sources;
    RICLUNumOutputs num_output_bins;
    ushort          horiz_print_resolution;
    ushort          vert_print_resolution;
    clen_str        interpreter_name;
};
#pragma options align=reset
typedef struct ric_lu_features ric_lu_features;

#pragma options align=packed
struct ric_si_reply
{
    RICSubCommand    sub_command;
    uchar            num_luns;
    ric_lu_features  lu_features[1];
};
#pragma options align=reset
typedef struct ric_si_reply ric_si_reply;

                              /* RIC-FD Font Details */
#pragma options enum=small
enum RICFDStorageTypeCodes
{
    RICFDSInROM
    , RICFDSOnFontCard
    , RICFDSOnHardDisk
    , RICFDSInRAM
    , RICFDSInFlash
    , RICFDSInRAMSIMM
    , RICFDSOther = 0xFD
    , RICFDSException
    , RICFDSAllTypes = 0xFF     /* Request all types from host. If from
                                 * printer, printer cannot provide font
                                 * storage type. */
};
#pragma options enum=reset
typedef enum  RICFDStorageTypeCodes RICFDStorageTypeCodes;

#pragma options enum=small
enum RICFDStorageTypeID
{
    RICFDSIDAll = 0xFF          /* From host. If from printer, printer */
                                /* cannot provide font storage type. */
};
#pragma options enum=reset
typedef enum RICFDStorageTypeID RICFDStorageTypeID;

#pragma options align=packed
struct ric_fd
{
    RICSubCommand         sub_command;
    ByteLU                lun;
    RICFDStorageTypeCodes storage;
    RICFDStorageTypeID    id;
};
#pragma options align=reset
typedef struct ric_fd ric_fd;


#pragma options align=packed
struct ric_fd_reply
{
    RICSubCommand sub_command;
    ByteLU        lun;
    ushort        num_fonts;
        /* Followed by num_fonts times:
         * clen_str              font_description_type;
         * RICFDStorageTypeCodes font_storage_type;
         * RICFDStorageTypeID    font_storage_type_id;
         * slen_str              font_descriptor;
         */
};
#pragma options align=reset
typedef struct ric_fd_reply ric_fd_reply;

    /* RIC-IC Input Characteristics */
    /* RIC-OC Output Characteristics */

    /* ========================== Job Control ============================== */
#pragma options enum=small
enum JCSubCommand
{
    JCStartJob                  /* JC-SJ   Start Job */
    , JCEndJob                  /* JC-EJ   End Job */
    , JCQueryJobsCompleted      /* JC-QJC  Query Jobs Completed */
    , JCQueryJobsQueuedOrActive /* JC-QQA  Query Jobs Queued or Active */
    , JCStartSession = 0x08     /* JC-SS   Start Session */
    , JCEndSession              /* JC-ES   End Session */
    , JCQuerySessionQueuedOrActive /* JC-QSQA Query Session Queued or Active */
    , JCChangeSessionPriority   /* JC-CSP  Change Session Priority */
    , JCDeleteSession           /* JC-DS   Delete Session */
    , JCResumeSuspendedJob = 0x10 /* JC-RSJ  Resume Suspended Job */
};
#pragma options enum=reset
typedef enum JCSubCommand JCSubCommand;

#pragma options enum=small
enum JCSessionPriority
{
    JCSPInvalid
    , JCSPLowest
    , JCSPHighest = 0xFF
};
#pragma options enum=reset
typedef enum JCSessionPriority JCSessionPriority;

                                /* JC-SS   Start Session */
#pragma options align=packed
struct jc_ss
{
    JCSubCommand      sub_command;
    JCSessionPriority priority;
};
#pragma options align=reset
typedef struct jc_ss jc_ss;

#pragma options align=packed
struct jc_ss_reply
{
    JCSubCommand      sub_command;
    ushort            session_id;
    JCSessionPriority assigned_priority;
};
#pragma options align=reset
typedef struct jc_ss_reply jc_ss_reply;

                                /* JC-SJ   Start Job */
#pragma options enum=small
enum JCSJAlerts
{
    JCSJANone
    , JCSJALUStart       = 0x40
    , JCSJASheetComplete = 0x02
    , JCSJAJobComplete   = 0x01
};
#pragma options enum=reset
typedef enum JCSJAlerts JCSJAlerts;

#pragma options enum=small
enum JCSJProcessing
{
    JCSJPNone
    , JCSJPSuspendAtLUStart          = 0x40
    , JCSJPSuspendAtStartOfPrinting  = 0x10
    , JCSJPSuspendAtStartOfFinishing = 0x04
    , JCSJPSeparateDataChannel       = 0x02
    , JCSJPRetainIncompleteSheet     = 0x01
};
#pragma options enum=reset
typedef enum JCSJProcessing JCSJProcessing;

#pragma options align=packed
struct jc_sj
{
    JCSubCommand sub_command;
    ByteLU       lun;
    struct
    {
        uint job_complete:1;    /* bit 7 */
        uint sheet_complete:1;  /* bit 6 */
        uint :4;                /* bits 5-2 */
        uint lu_start:1;        /* bit 1 */
        uint :1;                /* bit 0 */
    } alert_points;
    struct
    {
        uint retain_incomplete_sheet:1; /* bit 7 */
        uint separate_data_channel:1; /* bit 6 */
        uint suspend_start_finishing:1; /* bit 5 */
        uint :1;                /* bit 4 */
        uint suspend_start_printing:1; /* bit 3 */
        uint :1;                /* bit 2 */
        uint suspend_lu_start:1; /* bit 1 */
        uint :1;                /* bit 0 */
    } processing_flags;
};
#pragma options align=reset
typedef struct jc_sj jc_sj;

#pragma options align=packed
struct jc_sj_reply
{
    JCSubCommand sub_command;
    ByteLU       lun;
    ushort       job_id;
    ushort       channel;       /* 1284-1994 specifies as <= 127 */
};
#pragma options align=reset
typedef struct jc_sj_reply jc_sj_reply;

                                /* JC-EJ   End Job */
#pragma options align=packed
struct jc_ej
{
    JCSubCommand sub_command;
    ByteLU       lun;
    ushort       job_id;
};
#pragma options align=reset
typedef struct jc_ej jc_ej;
typedef struct jc_ej jc_ej_reply; /* Identical on query and reply */

                                /* JC-ES   End Session */
#pragma options align=packed
struct jc_es
{
    JCSubCommand sub_command;
    ushort       session_id;
};
#pragma options align=reset
typedef struct jc_es jc_es;

#pragma options align=packed
struct jc_es_job
{
    ByteLU lun;
    ushort session_id;
};
#pragma options align=reset
typedef struct jc_es_job jc_es_job;


#pragma options align=packed
struct jc_es_reply
{
    JCSubCommand sub_command;
    ushort       session_id;
    uchar        num_jobs;
    jc_es_job    job[1];
};
#pragma options align=reset
typedef struct jc_es_reply jc_es_reply;

    /* ====================== Request Device Status ======================== */
#pragma options enum=small
enum RDSSubCommand
{
    RDSStatusSummary             /* RDS-RS    Request Status Summary */
    , RDSStatusInput             /* RDS-RIS   Request Input Status */
    , RDSStatusOutput            /* RDS-ROS   Request Output Status */
    , RDSAlertInput              /* RDS-RIA   Request Input Alert */
    , RDSAlertOutput             /* RDS-ROA   Request Output Alert */
    , RDSAlertJam                /* RDS-RJA   Request Jam Alert*/
    , RDSAlertOpInterventionReqd /* RDS-ROIRA Request Operator Intervention Required Alert */
    , RDSWarnings                /* RDS-RW    Request Warnings */
    , RDSAlertDeviceServiceReqd  /* RDS-RDSRA Request Device Service Required Alert */
    , RDSAlertConfigChange       /* RDS-RCCA  Request Configuration Change Alert */
    , RDSSuppliesAlert           /* RDS-RSA   Request Supplies Alert */
    , RDSPrinterStatistics       /* RDS-RPS   Request Printer Statistics */
    , RDSSuppliesStatus          /* RDS-RSS   Request Supplies Status */
};
#pragma options enum=reset
typedef enum RDSSubCommand RDSSubCommand;

                                /* RDS-RS    Request Status Summary */
#pragma options align=packed
struct rds_rs
{
    RDSSubCommand sub_command;
};
#pragma options align=reset
typedef struct rds_rs rds_rs;

#pragma options align=packed
struct rds_rs_reply
{
    RDSSubCommand sub_command;
    struct
    {
        uint data_link_buffer_full:1; /* bit 7 */
        uint offline:1;         /* bit 6 */
        uint printer_idle:1;    /* bit 5 */
        uint :4;                /* bits 4-1 */
        uint power_on_init:1;   /* bit 0 */
    } overall;

    struct
    {
        uint :4;                /* bits 7-4 */
        uint input:1;           /* bit 3 */
        uint output:1;          /* bit 2 */
        uint paper_jam:1;       /* bit 1 */
        uint supply_alert:1;    /* bit 0 */
    } alerts1;

    struct
    {
        uint :4;                /* bits 7-4 */
        uint intervention_reqd:1; /* bit 3 */
        uint service_reqd:1;    /* bit 2 */
        uint warnings:1;        /* bit 1 */
        uint config_change:1;   /* bit 0 */
    } alerts2;

};
#pragma options align=reset
typedef struct rds_rs_reply rds_rs_reply;

    /* =================== Printer Configuration Control =================== */
#pragma options enum=small
enum PCCSubCommand
{
    PCCReadConfiguration                  /* PCC-RCPC Read Current Printer Configuration */
    , PCCResetPrinter                     /* PCC-RP   Reset Printer */
    , PCCDSelectDeviceStatusAlerts = 0x03 /* PCC-DLB  Select Device Status Alerts */
    , PCCDataLoopBack                     /* PCC-DLB  Data Loop Back (ping) */
    , PCCSelectHostPacketSize             /* PCC-SHPS Select Host Packet Size */
    , PCCResetHostControlledCounter       /* PCC-RHCC Reset Host Controlled Counter */
    , PCCSelectInterpreterMessages        /* PCC-SUIM Select Unsolicited Interpreter Messages */
    , PCCReadInterpreterMessagesSelected  /* PCC-RIM  Read Interpreter Messages Selected */
    , PCCSelectJobAlerts                  /* PCC-SJA  Select Job Alerts */
    , PCCReadJobAlerts                    /* PCC-RJAS Read Job Alerts Selected */
    , PCCSetPrinterID                     /* PCC-SPI  Set Printer ID */
    , PCCEnableCommonPrinterMIBAlert      /* PCC-EMA  Enable Common Printer MIB Alert */
    , PCCDisableCommonPrinterMIBAlert     /* PCC-DMA  Disable Common Printer MIB Alert */
    , PCCReadPrinterID                    /* PCC-RPI  Read Printer ID */
};
#pragma options enum=reset
typedef enum PCCSubCommand PCCSubCommand;

#pragma options align=packed
struct pcc_overall_status
{
    uint printer_busy:1;        /* Bit 7 */
    uint printer_offline:1;     /* Bit 6 */
    uint :5;                    /* Bits 5-1 */
    uint power_on_init:1;       /* Bit 0 */
};
#pragma options align=reset
typedef struct pcc_overall_status pcc_overall_status;

#pragma options align=packed
struct pcc_device_alerts
{
    struct
    {
        uint :4;                /* Bits 7-4 */
        uint input:1;           /* Bit 3 */
        uint output:1;          /* Bit 2 */
        uint paper_jam:1;       /* Bit 1 */
        uint printing_supply:1; /* Bit 0 */
    } alerts1;
    struct
    {
        uint :4;                /* Bits 7-4 */
        uint intervention_reqd:1; /* Bit 3 */
        uint service_reqd:1;    /* Bit 2 */
        uint warnings:1;        /* Bit 1 */
        uint config_change:1;   /* Bit 0 */
    } alerts2;
};
#pragma options align=reset
typedef struct pcc_device_alerts pcc_device_alerts;

                                /* Read Current Printer Configuration */
#pragma options align=packed
struct pcc_rcpc
{
    PCCSubCommand      sub_command;
};
#pragma options align=reset
typedef struct pcc_rcpc pcc_rcpc;

#pragma options align=packed
struct pcc_rcpc_reply
{
    PCCSubCommand      sub_command;
    ushort             max_host_packet_sz;
    pcc_overall_status overall;
    pcc_device_alerts  device;
};
#pragma options align=reset
typedef struct pcc_rcpc_reply pcc_rcpc_reply;

                                /* PCC-RP   Reset Printer */
#pragma options enum=small
enum PCCReset
{
        /* encoded as 1284.1 State, comm state, interpreter state. */
    PCC_RP_None
    , PCC_RP_D1_Default_Default
    , PCC_RP_D1_Default_Unchanged
    , PCC_RP_NON_NON_Default
    , PCC_RP_NON_NON_Unchanged
};
#pragma options enum=reset
typedef enum PCCReset PCCReset;

#pragma options align=packed
struct pcc_rp
{
    PCCSubCommand sub_command;
    PCCReset      reset;
};
#pragma options align=reset
typedef struct pcc_rp pcc_rp;

                                /*  PCC-DLB Data Loop Back */
#pragma options align=packed
struct pcc_dlb
{
    PCCSubCommand sub_command;
    uchar         data[1];
};
#pragma options align=reset
typedef struct pcc_dlb pcc_dlb;
typedef pcc_dlb pcc_dlb_reply;

                                /* PCC-SHPS Select Host Packet Size */
#pragma options align=packed
struct pcc_shps
{
    PCCSubCommand      sub_command;
    ushort             max_host_packet_sz;
};
#pragma options align=reset
typedef struct pcc_shps pcc_shps;

                                /*  PCC-SJA Select Job Alerts */
#pragma options align=packed
struct pcc_sja
{
    PCCSubCommand sub_command;
    struct {
        uint job_accounting:1;  /* bit 7 */
        uint end_of_job:1;      /* bit 6 */
        uint :1;                /* bit 5 */
        uint page_alert:1;      /* bit 4 */
        uint :2;                /* bits 3-2 */
        uint lu_start:1;        /* bit 1 */
        uint :1;                /* bit 0 */
    } alert_points;
};
#pragma options align=reset
typedef struct pcc_sja pcc_sja;


                                /*  PCC-RJA Read Job Alerts Selected */
#pragma options align=packed
struct pcc_rja
{
    PCCSubCommand sub_command;
};
#pragma options align=reset
typedef struct pcc_rja pcc_rja;

#pragma options align=packed
struct pcc_rja_reply
{
    PCCSubCommand sub_command;
    struct {
        uint job_accounting:1;  /* bit 7 */
        uint extended_job_complete:1; /* bit 6 */
        uint :4;                /* bits 5-2 */
        uint lu_start:1;        /* bit 1 */
        uint :1;                /* bit 0 */
    } alert_points;
};
#pragma options align=reset
typedef struct pcc_rja_reply pcc_rja_reply;

                                /*  PCC-SPI Set Printer ID */
#pragma options align=packed
struct pcc_spi
{
    PCCSubCommand sub_command;
    clen_str      printer_id;
};
#pragma options align=reset
typedef struct pcc_spi pcc_spi;

                                /*  PCC-RPI Read Printer ID */
#pragma options align=packed
struct pcc_rpi
{
    PCCSubCommand sub_command;
};
#pragma options align=reset
typedef struct pcc_rpi pcc_rpi;
typedef struct pcc_spi pcc_rpi_reply;


    /* ================= Request Logical Unit Characteristics ============== */
#pragma options enum=small
enum RLUCSISubCommand
{
    RLUCSISummary    /* RLUC-SI Summary Information*/
};
#pragma options enum=reset
typedef enum RLUCSISubCommand RLUCSISubCommand;

#pragma options enum=small
enum RLUCIdentifier
{
    RLUCPageControlInterpreter
    , RLUCScanner
    , RLUCModem
    , RLUCFax
    , RLUCManSpecificStart = 0x8000
    , RLUCManSpecificEnd   = 0xFFFF
};
#pragma options enum=reset
typedef enum RLUCIdentifier RLUCIdentifier;

#pragma options align=packed
struct rluc_si
{
    RLUCSISubCommand sub_command;
    ByteLU           lun;
};
#pragma options align=reset
typedef struct rluc_si rluc_si;

#pragma options align=packed
struct rluc_lu_info
{
    ByteLU           lun;
    RLUCIdentifier   identifier;
};
#pragma options align=reset
typedef struct rluc_lu_info rluc_lu_info;

#pragma options align=packed
struct rluc_si_reply
{
    RLUCSISubCommand sub_command;
    uchar            num_lu;
    rluc_lu_info     info[1];
};
#pragma options align=reset
typedef struct rluc_si_reply rluc_si_reply;

    /* ===================== Printer Variable Commands ===================== */
#pragma options enum=small
enum PVCSubCommand
{
    PVCGetPrinterVariable       /* PVC-GPV Get Printer Variable */
    , PVCSetPrinterVariable     /* PVC-SPV Set Printer Variable */
    , PVCGetNextPrinterVariable /* PVC-GNV Get Next Printer Variable */
};
#pragma options enum=reset
typedef enum PVCSubCommand PVCSubCommand;

    /* ====================== Remote Operator Panel ======================== */
#pragma options enum=small
enum ROPSubCommand
{
    ROPRequestSummary           /* ROP-RS  Request Summary */
    , ROPRequestObjectCharacteristics /* ROP-ROC Request Object
                                       * Characteristics */
    , ROPReadObjectStatus       /* ROP-RO  Read Object Status/Contents */
    , ROPSelectAlerts           /* ROP-SA  Select Alerts */
    , ROPOperatorPanelAlerts    /* ROP-OPA Operator Panel Alerts @@@ */
    , ROPReadAlertsSelected     /* ROP-RAS Read Alerts Selected */
    , ROPAcquirePanelControl    /* ROP-APC Acquire Panel Control */
    , ROPRelenquishPanelControl /* ROP-RPC Relenquish Panel Control */
    , ROPControlPanelObject     /* ROP-CPO Control Panel Object */
    , ROPReadOperatorPanelVariables /* ROP-RPV Read Operator Panel Variables */
    , ROPSetOperatorPanelVariables /* ROP-SPV Set Operator Panel Variables */
    , ROPSetOperatorPanelPassword /* ROP-SPP Set Operator Panel Password */
    , ROPGetOperatorPanelColorPalette /* ROP-GCP Get Operator Panel Color
                                       * Palette */
};
#pragma options enum=reset
typedef enum ROPSubCommand ROPSubCommand;

    /* ======================= Device Status Alert ========================= */
    /* DSA- */

#pragma options align=packed
struct dsa_device_alerts
{
    struct
    {
        uint :4;                /* Bits 7-4 */
        uint input:1;           /* Bit 3 */
        uint output:1;          /* Bit 2 */
        uint paper_jam:1;       /* Bit 1 */
        uint printing_supply:1; /* Bit 0 */
    } alert1;
    struct
    {
        uint :4;                /* Bits 7-4 */
        uint intervention_reqd:1; /* Bit 3 */
        uint service_reqd:1;    /* Bit 2 */
        uint warnings:1;        /* Bit 1 */
        uint config_change:1;   /* Bit 0 */
    } alert2;
};
#pragma options align=reset
typedef struct dsa_device_alerts dsa_device_alerts;

#pragma options align=packed
struct dsa_msg_hdr
{
    struct
    {
        uint          printer_busy:1;    /* Bit 7 */
        uint          printer_offline:1; /* Bit 6 */
        uint :5;                         /* Bits 5-1 */
        uint          power_on_init:1;   /* Bit 0 */
    } summary;
    dsa_device_alerts device;
    uchar             alert_detail[1];
};
#pragma options align=reset
typedef struct dsa_msg_hdr dsa_msg_hdr;

    /* ==================== Interpreter Message Alerts ===================== */
    /* IMA- */

#pragma options enum=small
enum IMAprinter_assigned_job_id
{
    IMAPAJIDUnknown = 0xFFFF
};
#pragma options enum=reset
typedef enum IMAprinter_assigned_job_id IMAprinter_assigned_job_id;

#pragma options enum=small
enum IMApage_num_printer_assigned_job_id
{
    IMANumPageNumUnknown = 0xFFFF
};
#pragma options enum=reset
typedef enum IMApage_num_printer_assigned_job_id IMApage_num_printer_assigned_job_id;

#pragma options enum=small
enum IMAinterpreter_flag
{
    IMAIFInformational
    , IMAIFWarning          /* Job may not appear as completely as
                             * specified by data stream. */
    , IMAIFError            /* Job shall not print. */
    , IMAIFUnknown = 0xFF
};
#pragma options enum=reset
typedef enum IMAinterpreter_flag IMAinterpreter_flag;

#pragma options align=packed
struct ima_msg
{
    ByteLU                              lu;
    IMAprinter_assigned_job_id          printer_assigned_job_id;
    IMApage_num_printer_assigned_job_id page_num_printer_assigned_job_id;
    IMAinterpreter_flag                 interpreter_flag;

    struct
    {
        uint :7;                /* Bits 7-1 */
        uint response:1;        /* Bit 0 */
    } interpreter_status_alerts1;
    struct
    {
        uint :8;                /* Bits 7-0 */
    } interpreter_status_alerts2;
};
#pragma options align=reset
typedef struct ima_msg ima_msg;

    /* ======================== Job Control Alerts ========================= */
#pragma options enum=small
enum JCASubCommand
{
    JCALogicalUnitStart            = 0x0200 /* JCA-LUS    Logical Unit Start */
    , JCASheetComplete             = 0x1000 /* JCA-SC     Sheet Complete */
    , JCAEndofJob                  = 0x4000 /* JCA-EOJ    End of Job */
    , JCASuspendAtLogicalUnitStart = 0x0002 /* JCA-SP-LUS Suspend Processing
                                             * at Logical Unit Start */
    , JCASuspendAtStartofPrinting  = 0x0003 /* JCA-SP-SOP Suspend Processing at
                                            * Start of Printing */
    , JCASuspendAtStartofFinishing = 0x0004 /* JCA-SP-SOF Suspend Processing
                                             * at Start of Finishing */
    , JCAEndofJobAccountingMessage = 0x8000 /* JCA-EOJ End of Job Accounting
                                             * Message */
};
#pragma options enum=reset
typedef enum JCASubCommand JCASubCommand;

#pragma options align=packed
struct eoj_alert
{
    uchar  num_input_sources;
    ByteLU lu;
    ushort job_id;
    ushort processing_time;
    uint   sheets_used;
    uint   impressions;
    uint   counter_units;
};
#pragma options align=reset
typedef struct eoj_alert eoj_alert;

    /* JCA-LUS */
#pragma options enum=small
enum LUCurrentStatus
{
    LUCSJobRunning
    , LUCSWaitingForData
};
#pragma options enum=reset
typedef enum LUCurrentStatus LUCurrentStatus;

#pragma options align=packed
struct lu_start
{
    ByteLU          lu;
    ushort          printer_assigned_job_id;
    LUCurrentStatus current_status;
};
#pragma options align=reset
typedef struct lu_start lu_start;

#pragma options align=packed
struct jca_lus
{
    JCASubCommand sub_command;
    ushort        num_lu_start_alerts;
    lu_start      start_alert[1];
};
#pragma options align=reset
typedef struct jca_lus jca_lus;

    /* JCA-SC */
#pragma options align=packed
struct sheet_alert
{
    ByteLU lu;
    ushort printer_assigned_job_id;
    uint   sheet_num;
};
#pragma options align=reset
typedef struct sheet_alert sheet_alert;

#pragma options align=packed
struct jca_sc
{
    JCASubCommand sub_command;
    ushort num_sheet_complete_alerts;
    sheet_alert sheet_alert[1];
};
#pragma options align=reset
typedef struct jca_sc jca_sc;

    /* JCA-SP_LUS */
#pragma options align=packed
struct jca_sp_lus
{
    ByteLU lu;
    ushort printer_assigned_job_id;
};
#pragma options align=reset
typedef struct jca_sp_lus jca_sp_lus;

    /* JCA-SP_SOP */
#pragma options align=packed
struct jca_sp_sop
{
    ByteLU lu;
    ushort printer_assigned_job_id;
};
#pragma options align=reset
typedef struct jca_sp_sop jca_sp_sop;

    /* JCA-SP_SOF */
#pragma options align=packed
struct jca_sp_sof
{
    ByteLU lu;
    ushort printer_assigned_job_id;
};
#pragma options align=reset
typedef struct jca_sp_sof jca_sp_sof;

    /* JCA-EOJ Accounting Message*/
#pragma options enum=small
enum JCAProcessingTime
{
    JCAPTNotSupported = 0xFFFF
};
#pragma options enum=reset
typedef enum JCAProcessingTime JCAProcessingTime;

#pragma options enum=small
enum JCAElapsedTime
{
    JCAETUnknown = 0xFFFFFFFF
};
#pragma options enum=reset
typedef enum JCAElapsedTime JCAElapsedTime;

#pragma options enum=small
enum JCADataStreamLen
{
    JCADSUnknown = 0xFFFFFFFF
};
#pragma options enum=reset
typedef enum JCADataStreamLen JCADataStreamLen;

#pragma options enum=small
enum JobCompletionCodes
{
    JCCSuccess
    , JCCTimeout
    , JCCTerminateAbnormal = 0xFFFE
    , JCCCanceled          = 0xFFFF
};
#pragma options enum=reset
typedef enum JobCompletionCodes JobCompletionCodes;

#pragma options align=packed
struct jca_eoj_accounting_msg
{
    ByteLU            lu;
    ushort            printer_assigned_job_id;
    JCAProcessingTime processing_time;
    JCAElapsedTime    elapsed_time;
    JCADataStreamLen  num_bytes_in_job_data_stream;
    uint              date_job_started;
};
#pragma options align=reset
typedef struct jca_eoj_accounting_msg jca_eoj_accounting_msg;

#pragma options align=packed
struct eoj_input_data
{
    uchar                          num_input_sources;
    ushort                         input_id;
    InputMediumCharacteristicCodes medium_characteristic;
    InputMediumSizeCodes           medium_size;
    clen_str                       medium_description;
};
#pragma options align=reset
typedef struct eoj_input_data eoj_input_data;

#pragma options align=packed
struct eoj_output_data
{
    uchar  num_output_sources;
    ushort output_id;
};
#pragma options align=reset
typedef struct eoj_output_data eoj_output_data;

    /* JCA-EOJ */
#pragma options align=packed
struct jca_eoj
{
    JCASubCommand sub_command;
    ushort num_eoj_alerts;
    union
    {
        jca_sp_lus jca_sp_lus;
        jca_sp_sop jca_sp_sop;
        jca_sp_sof jca_sp_sof;
        jca_eoj_accounting_msg jca_eoj_accounting_msg;
    } alerts[1];
};
#pragma options align=reset
typedef struct jca_eoj jca_eoj;


    /* ===================== Common Printer MIB Alerts ===================== */
    /* CPMA- */
#pragma options align=packed
struct cpma_msg
{
    uint     alert_index;
    clen_str iod[1];
};
#pragma options align=reset
typedef struct cpma_msg cpma_msg;

    /* ====================== Operator Panel Alert ========================= */
    /* OPA- */
#pragma options align=packed
struct opa_object_alert
{
    ushort type;
    ushort id;
};
#pragma options align=reset
typedef struct opa_object_alert opa_object_alert;

#pragma options align=packed
struct operator_panel_alert
{
    ushort num_object_alerts;
    opa_object_alert object[1];
};
#pragma options align=reset
typedef struct operator_panel_alert operator_panel_alert;

    /* ====================== Command Packet ========================= */

#pragma options enum=small
enum CommandByte            /* command or LU, depending on Destination value */
{
    CommandByteNone
    , RequestDeviceCharacteristics
    , RequestInterpreterCharacteristics
    , PrinterConfigurationControl
    , RequestDeviceStatus
    , JobControl
    , RequestLUCharacteristics
    , ControlPacketRejection    /* deprecated */
    , CommonPrinterVariable
    , RemoteOpPanel
                                /* The following are set when the packet is an
                                 * unsolicited message from the command
                                 * processor */
    , AlertMfrSpecificDeviceStatus = 0xF0
    , AlertOperatorPanel           = 0xFB
    , AlertCommonPrinterMIB        = 0xFC
    , AlertJobControl              = 0xFD
    , AlertInterpreterMessage      = 0xFE
    , AlertDeviceStatus            = 0xFF
};
#pragma options enum=reset
typedef enum CommandByte CommandByte;


enum DestinationFlag
{
    DestLU                      /* data destined for logical unit */
    , DestCmdInterpreter        /* data destined for default command interp */
};

enum CheckTypeValue
{
                                /* These values are valid only if flag.Error
                                 * is set. */
    CTCmdRejected               /* Peripheral rejected the command. */
    , CTDataError               /* Data error */
    , CTCommandError            /* Command Error */
    , CTReserved                /* Reserved */
};

enum PrinterStatusValue
{
    PrtOK                       /* printer is ok. */
    , PrtCheck                  /* Printer is ok, but operator may want to
                                 * know about condition. */
    , PrtIntervention           /* Out of paper, output bin full, toner low... */
    , PrtService                /* Condition exists that will prevent further
                                 * printing, e.g., hardware failures. */
};

#pragma options align=packed
struct ieee1284_d1
{
    ushort length;              /* length of data */
    union
    {
        struct
        {
            uint  NOP:1;        /* bit 7 */
            uint  Destination:1; /* bit 6. If set, data contains message and
                                  * CommandByte contains the command. If
                                  * clear, data contains data for the LU with
                                  * command byte being the LU number. */
            uint  Continue:1;   /* bit 5 */
            uint  ReplyRequired:1; /* bit 4 */
            uint :4;            /* bits 3-0 */
        } query;

        struct
        {
            uint Error:1;       /* bit 7 */
            uint Source:1;      /* bit 6 */
            uint Continue:1;    /* bit 5 */
            uint ReplyType:1;   /* bit 4 */
            uint CheckType:2;   /* bits 3-2 */
            uint PrinterStatus:2; /* bits 1-0 */
        } reply;

        uchar byte;
    } flag;

    union
    {
        CommandByte command;
        ByteLU      lun;
        uchar       byte;
    } value;

    union
    {
        union
        {
            jc_ej          jc_ej;
            jc_ej_reply    jc_ej_reply;
            jc_es          jc_es;
            jc_es_reply    jc_es_reply;
            jc_sj          jc_sj;
            jc_sj_reply    jc_sj_reply;
            jc_ss          jc_ss;
            jc_ss_reply    jc_ss_reply;

            pcc_dlb        pcc_dlb;
            pcc_dlb_reply  pcc_dlb_reply;
            pcc_rcpc       pcc_rcpc;
            pcc_rcpc_reply pcc_rcpc_reply;
            pcc_rja        pcc_rja;
            pcc_rja_reply  pcc_rja_reply;
            pcc_rp         pcc_rp;
            pcc_rpi        pcc_rpi;
            pcc_rpi_reply  pcc_rpi_reply;
            pcc_shps       pcc_shps;
            pcc_sja        pcc_sja;    /* no reply */
            pcc_spi        pcc_spi;    /* no reply */

            rdc_rs         rdc_rs;
            rdc_rs_reply   rdc_rs_reply;

            rds_rs         rds_rs;
            rds_rs_reply   rds_rs_reply;

            ric_fd         ric_fd;
            ric_fd_reply   ric_fd_reply;
            ric_si         ric_si;
            ric_si_reply   ric_si_reply;

            rluc_si        rluc_si;
            rluc_si_reply  rluc_si_reply;

        } subcmd;
#define IEEE1284_D1_DATASZ      4
        uchar            byte [IEEE1284_D1_DATASZ];
    } data;
};
#pragma options align=reset
typedef struct ieee1284_d1 ieee1284_d1;

#ifdef __cplusplus
}
#endif
#endif /* _H_IEEE1284 */
