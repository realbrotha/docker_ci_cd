/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* ssa530 src/ssa/kernel/sys/POWER/tmssa.h 1.3                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996,2000          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* static char sccsid [] = "@(#) 89 1.3 src/ssa/kernel/sys/POWER/tmssa.h, tmssadd, ssa530 5/23/00 06:36:46"; */
/*
 * COMPONENT NAME:      TMSSADD SSA Subsystem
 *
 * FUNCTION:            Header files for TMSSA subsystem
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 ****************************************************************************
 *
 */
#ifndef _TMSSA_H
#define _TMSSA_H
/*--------------------------------------------------------------------------*/
/*             SYSTEM INCLUDES                                              */
/*--------------------------------------------------------------------------*/
#include <sys/types.h>                                 /* For dev_t typedef */
/*--------------------------------------------------------------------------*/
/*             Includes from IPN                                            */
/*--------------------------------------------------------------------------*/
#include <ipn/ipndef.h>      /* For NN_AdapterA, NN_AdapterAEnd defns. etc. */

/*
 * General definitions
 */
#define MAX_ADAPTERS (NN_NewAdaptorEnd + 1 - NN_NewAdaptor)
#define MAX_CLUSTERS_SUPPORTED    127

/*
 * Identifier to verify the DDS with.
 */
/* If changing TMSSA_DDS_ID ******* UPDATE DDS_ID_SIZE */
#define TMSSA_DDS_ID "TMSSA DDS"
#define DDS_ID_SIZE  10

/*
 * The device specific data block
 */
typedef struct TMSSA_DDS {
    int         TargetCluster;
    int         LocalCluster;
    dev64_t     AdapterDevnos [MAX_ADAPTERS];  /* MUST be -1 if not found etc. */
    Inodenum    AdapterNodeNos [MAX_ADAPTERS]; /* Only valid if there is a devno */
    int         PreferredAdapter;
    int         NumOfReceiveBuffers;
    int         SizeofReceiveBuffers;
    int         NumOfTransmitBuffers;
    int         SizeofTransmitBuffers;
    char        ResourceName [8];             /* xxx.[it]m OR network OR keepopn */
    char        Identifier [DDS_ID_SIZE];     /* Leave at end, so that changes */
                                              /* are easier to detect (run time) */
} TMSSA_DDS_t;


/*
 * The special devnos used for the special devices are defined
 */
#define SPECIAL_TMSSA_DEVNO_BASE  65534
#define NETWORK_MINOR_DEVNO      (SPECIAL_TMSSA_DEVNO_BASE + 0)
#define KEEP_OPEN_MINOR_DEVNO    (SPECIAL_TMSSA_DEVNO_BASE + 1)

/*
 * When reading the network, we need to use the following structure for
 * each entry.
 */
typedef struct {
    Inodenum      AdapterNodeNum;    /* Adapter connected to cluster */
    unsigned int  NetworkedCluster;  /* Cluster number of connected node */
} TMSSA_Network_t;

#define TM_NETWORK_BUFFER_SIZE  (MAX_ADAPTERS * (MAX_CLUSTERS_SUPPORTED - 1) * \
                                 sizeof (TMSSA_Network_t))

/*
 * When the DEVINFO IOCTL is used, the following macro MUST be used
 * to access the node number.
 */
#define TM_GetDevinfoNodeNum(pInfo)   (Iu16)((Iu16)(((pInfo)->un.tmscsi.lun_id)<<8) + \
                                            ((Iu16)((pInfo)->un.tmscsi.scsi_id)))

#endif /* _TMSSA_H */
