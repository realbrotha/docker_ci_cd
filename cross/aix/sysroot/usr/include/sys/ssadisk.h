/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* ssa530 src/ssa/kernel/sys/POWER/ssadisk.h 1.8                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1994,2000          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#) 13 1.8 src/ssa/kernel/sys/POWER/ssadisk.h, ssadiskdd, ssa530 5/23/00 06:19:59 */
/*
 * COMPONENT NAME: ssadiskdd
 *
 * FILE NAME: ssadisk.h
 *
 * EXECUTABE NAME: ssadisk
 *
 * DESCRIPTION: ssa disk device driver shipped header file.
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 ****************************************************************************
 *
 * Change Log.
 */

#ifndef ssadisk_h
#define ssadisk_h
/*--------------------------------------------------------------------------*/
/*             SYSTEM INCLUDES                                              */
/*--------------------------------------------------------------------------*/

#include <sys/types.h>
#include <sys/scsi.h>

/*--------------------------------------------------------------------------*/
/*             IPN  INCLUDES                                               */
/*-------------------------------------------------------------------------*/

#include <ipn/ipndef.h>
#include <ipn/ipnsal.h>
#include <ipn/ipnreg.h>
#include <ipn/ipntra.h>
#include <ipn/ipnadp.h>

/*
 * Temporary definition until we get our hookword defined in
 * trcids.h
 */
#ifndef HKWD_DD_SSADISKDDDD

#define HKWD_DD_SSADISKDD       0x45B00000     /* SSA disk DD           */

#endif

/*
 * Constants for trace macros
 */
#define SK_ENTRY_FINISH              0x30
#define SK_EXIT_FINISH               0x31
/*
 * Constant Definitions
 */

#define SSADISK_SERIAL_NO_SIZE        16
#define SSADISK_RESOURCENAME_LENGTH    16
/*
 * Modes for openext
 */
#define SSADISK_ISALMGR           0x00010000 /* ISAL Manager Ioctls only mode */

#define SSADISK_PRIMARY           0x00008000 /* Use the primary adapter path  */

#define SSADISK_SECONDARY         0x00004000 /* Use the secondary adapter path*/
 
#define SSADISK_NOSWITCH          0x00002000 /* Do not switch adapter paths  */

#define SSADISK_SERVICEMODE       0x00001000 /* place device in service mode  */

#define SSADISK_NO_RESERVE      SC_NO_RESERVE
                                             /* Don't reserve device on open */

#define SSADISK_FORCED_OPEN     SC_FORCED_OPEN /* do not honor device reservation
                                                 conflict status */
#define SSADISK_RETAIN_RESERVATION SC_RETAIN_RESERVATION
                                             /* do not release SCSI device on
                                                close */
#define SSADISK_SCSIMODE          0x00000800 /* place device in SCSI Passthrough mode */
#define SSADISK_NORETRY           0x00000400 /* Reduced level of error recovery       */
#define SSADISK_FENCEMODE         0x00000200 /* Allows opeing of fenced off hdisks    */
#define SSADISK_DIAGMODE SSADISK_FENCEMODE   /* Used my ssa diagnostics               */



/*
 *  DEVICE DEPENDENT STRUCTURES
 */
typedef struct _SSADISK_HdiskDDS_t       /* Hdisk Device Dependent Structure */
{
    char       ResourceName[SSADISK_RESOURCENAME_LENGTH];
                                         /* The aix resource name           */ 
    dev64_t    PrimaryAdapDevno;         /* devno of the primary adapter    */
    dev64_t    SecondaryAdapDevno;       /* devno of the secondary adapter  */
    Inodenum   PrimaryAdapNodeNumber;    /* IPN node number of primary adap */
    Inodenum   SecondaryAdapNodeNumber;  /* IPN node number of secondary adap */  
    Iu8        OwningModuleType;         /* IPN Owning Module Type.         */
    char       SerialNumber[SSADISK_SERIAL_NO_SIZE];
                                         /* Device's IPN Serial Number      */  
    uint_t     MaxCoalesce;              /* Max number of bytes to colaesce */
    int        QueueDepth;               /* Max commands to queue to device */
    uint_t     SegmentSize;              /* segment size for transfer stats */
    uint_t     SegmentCount;             /* segment count for transfer stats*/
    uint_t     ByteCount;                /* byte count for transfer stats   */
    int        bSecondaryExists;         /* True if secondary adap valid    */
    Icluster   ClusterNumber;            /* IPN cluster number, used for fencing */
    int        bReserveOnOpen;           /* Whether to reserve on open      */
    int        WriteQModifier;           /* Write queue depth (if non-zero) */
    int        StrideWidth;              /* Stride width (if non-zero)      */
    
} SSADISK_HdiskDDS_t, * pSSADISK_HdiskDDS_t;

typedef struct _SSADISK_PdiskDDS_t       /* Pdisk Device Dependent Structure */
{
    char       ResourceName[SSADISK_RESOURCENAME_LENGTH];
                                         /* The aix resource name           */ 
    dev64_t    PrimaryAdapDevno;         /* devno of the primary adapter    */
    dev64_t    SecondaryAdapDevno;       /* devno of the secondary adapter  */
    Inodenum   PrimaryAdapNodeNumber;    /* IPN node number of primary adap */
    Inodenum   SecondaryAdapNodeNumber;  /* IPN node number of secondary adap */  
    Iu8        OwningModuleType;         /* IPN Owning Module Type.         */
    char       SerialNumber[SSADISK_SERIAL_NO_SIZE];
                                         /* Device's IPN Serial Number      */  
    int        bSecondaryExists;         /* True if secondary adap valid    */

} SSADISK_PdiskDDS_t, * pSSADISK_PdiskDDS_t;

/*
 * Ioctls
 */
/************************************************************************/
/* This is the Change Cluster number ioctl for SSADS      		*/
/************************************************************************/
#define SSADISK_ISAL_CMD     0x71
#define SSADISK_ISALMgr_CMD  0x72
#define SSADISK_SCSI_CMD     0x73
#define SSADISK_LIST_PDISKS  0x74
#define SSADISK_FLUSH        0x75
#define SSADS_CHGCLUSTER     0x76
#define SSADISK_GET_ADAPTER  0x77

typedef struct _ssadisk_mem_desc_t
{
    caddr_t  buffer;
    uint_t     length;
} ssadisk_mem_desc_t;


typedef struct _ssadisk_name_desc_t
{
    char name[SSADISK_RESOURCENAME_LENGTH];
} ssadisk_name_desc_t;

/*
 * Argument structure for ioctls: SSADISK_ISAL_CMD, SSADISK_ISALMgr_CMD
 * SSADISK_SCSI_CMD, and SSADISK_LIST_PDISKS.
 */

typedef struct _ssadisk_ioctl_parms_t                
{
    signed char dsb;                     /* Filled in by the driver on return */
                                         /* with the IPN dsb                  */
    __long32_t  result;                  /* Filled in by the driver on return */
                                         /* with the IPN Result word          */
    union
    {
        struct 
        {
            /*
             *These next five feilds must be filled in by the caller
             */
            
            ssadisk_mem_desc_t parameter_descriptor; /* parameter buffer    */
            ssadisk_mem_desc_t transmit_descriptor;  /* transmit  buffer    */
            ssadisk_mem_desc_t receive_descriptor;   /* receive   buffer    */
            ssadisk_mem_desc_t status_descriptor;    /* status    buffer    */
            ushort minor_function;                   /* minor function      */
            
        } isal;        /* for  SSADISK_ISAL_CMD and */
                       /* SSADISK_ISALMgr_CMD */
        struct 
        {
            ssadisk_mem_desc_t data_descriptor;
            int direction;
            uchar_t identifier;
            char  cdb [12];
            int cdb_length;
            uchar_t scsi_status;                 
        } scsi;        /* for SSADISK_SCSI_CMD */
        struct
        {
            uint_t name_array_elements;         /* caller fills in with number of */
                                              /* elements in name_array         */ 
            ssadisk_name_desc_t * name_array; /* array of ssadisk_name_desc_t   */
            uint_t name_count;                  /* number of pdisks names available*/
            uint_t resource_count;              /* number of resources in the hdisk*/
        } list_pdisks; /* for SSADISK_LIST_PDISKS. */

    } u0;
} ssadisk_ioctl_parms_t;

#define SSADISK_SCSI_DIRECTION_NONE           0
#define SSADISK_SCSI_DIRECTION_READ           1
#define SSADISK_SCSI_DIRECTION_WRITE 	      2
#define SSADISK_SCSI_DIRECTION_READ_OVERRIDE  3
#define SSADISK_SCSI_DIRECTION_WRITE_OVERRIDE 4

/*
 * Useful defines for accessing the union
 */

#define ssadisk_minor_function    u0.isal.minor_function
#define ssadisk_parameter_buffer  u0.isal.parameter_descriptor.buffer
#define ssadisk_parameter_length  u0.isal.parameter_descriptor.length
#define ssadisk_transmit_buffer   u0.isal.transmit_descriptor.buffer
#define ssadisk_transmit_length   u0.isal.transmit_descriptor.length
#define ssadisk_receive_buffer    u0.isal.receive_descriptor.buffer
#define ssadisk_receive_length    u0.isal.receive_descriptor.length
#define ssadisk_status_buffer     u0.isal.status_descriptor.buffer
#define ssadisk_status_length     u0.isal.status_descriptor.length
#define ssadisk_scsi_buffer       u0.scsi.data_descriptor.buffer
#define ssadisk_scsi_length       u0.scsi.data_descriptor.length
#define ssadisk_scsi_direction    u0.scsi.direction
#define ssadisk_scsi_identifier   u0.scsi.identifier
#define ssadisk_scsi_cdb          u0.scsi.cdb
#define ssadisk_scsi_cdb_length   u0.scsi.cdb_length
#define ssadisk_scsi_status       u0.scsi.scsi_status

#if defined( _KERNEL )

/************************************************************************/
/* Device driver only type definitions required to support 64-bit apps  */
/* These are a 32-bit view of the 64-bit versions of the above		*/
/* 64-bit memory descriptor						*/
/************************************************************************/

typedef struct _ssadisk_mem_desc64_t
{
    ptr64  buffer;
    uint_t length;
} ssadisk_mem_desc64_t;

/************************************************************************/
/* 64-bit IOCtl parameters						*/
/************************************************************************/

typedef struct _ssadisk_ioctl_parms64_t
{
    signed char dsb;                     /* Filled in by the driver on return */
                                         /* with the IPN dsb                  */
    __long32_t  result;                  /* Filled in by the driver on return */
                                         /* with the IPN Result word          */
    union
    {
        struct 
        {
            /*
             *These next five feilds must be filled in by the caller
             */
            
            ssadisk_mem_desc64_t parameter_descriptor; /* parameter buffer    */
            ssadisk_mem_desc64_t transmit_descriptor;  /* transmit  buffer    */
            ssadisk_mem_desc64_t receive_descriptor;   /* receive   buffer    */
            ssadisk_mem_desc64_t status_descriptor;    /* status    buffer    */
            ushort minor_function;                   /* minor function      */
            
        } isal;        /* for  SSADISK_ISAL_CMD and */
                       /* SSADISK_ISALMgr_CMD */
        struct 
        {
            ssadisk_mem_desc64_t data_descriptor;
            int direction;
            uchar_t identifier;
            char  cdb [12];
            int cdb_length;
            uchar_t scsi_status;                 
        } scsi;        /* for SSADISK_SCSI_CMD */
        struct
        {
            uint_t name_array_elements;         /* caller fills in with number of */
                                                /* elements in name_array         */ 
            ptr64  name_array;                  /* array of ssadisk_name_desc_t   */
            uint_t name_count;                  /* number of pdisks names available*/
            uint_t resource_count;              /* number of resources in the hdisk*/
        } list_pdisks; /* for SSADISK_LIST_PDISKS. */

    } u0;
} ssadisk_ioctl_parms64_t;

/************************************************************************/
/* Device driver only type definitions required to support 32-bit apps  */
/* These are a 64-bit view of the 32-bit versions of the above		*/
/* 32-bit memory descriptor						*/
/************************************************************************/

typedef struct _ssadisk_mem_desc32_t
{
    ptr32  buffer;
    uint_t length;
} ssadisk_mem_desc32_t;

/************************************************************************/
/* 32-bit IOCtl parameters						*/
/************************************************************************/

typedef struct _ssadisk_ioctl_parms32_t
{
    signed char dsb;                     /* Filled in by the driver on return */
                                         /* with the IPN dsb                  */
    __long32_t  result;                  /* Filled in by the driver on return */
                                         /* with the IPN Result word          */
    union
    {
        struct 
        {
            /*
             *These next five fields must be filled in by the caller
             */
            
            ssadisk_mem_desc32_t parameter_descriptor; /* parameter buffer    */
            ssadisk_mem_desc32_t transmit_descriptor;  /* transmit  buffer    */
            ssadisk_mem_desc32_t receive_descriptor;   /* receive   buffer    */
            ssadisk_mem_desc32_t status_descriptor;    /* status    buffer    */
            ushort minor_function;                   /* minor function      */
            
        } isal;        /* for  SSADISK_ISAL_CMD and */
                       /* SSADISK_ISALMgr_CMD */
        struct 
        {
            ssadisk_mem_desc32_t data_descriptor;
            int direction;
            uchar_t identifier;
            char  cdb [12];
            int cdb_length;
            uchar_t scsi_status;                 
        } scsi;        /* for SSADISK_SCSI_CMD */
        struct
        {
            uint_t name_array_elements;         /* caller fills in with number of */
                                                /* elements in name_array         */ 
            ptr32  name_array;                  /* array of ssadisk_name_desc_t   */
            uint_t name_count;                  /* number of pdisks names available*/
            uint_t resource_count;              /* number of resources in the hdisk*/
        } list_pdisks; /* for SSADISK_LIST_PDISKS. */

    } u0;
} ssadisk_ioctl_parms32_t;

#endif

#endif /* ssadisk_h*/ 

    
        
    
