/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2008,2009          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

#ifndef _CT_MICROSENSOR_DOT_H
#define _CT_MICROSENSOR_DOT_H

#include <rsct/ct.h>          /* Cluster common types     */
#include <rsct/ct_cu.h>       /* Cluster common utilities */
#include <rsct/ct_rmc.h>      /* RMC common types         */
#include <rsct/ct_mcerr.h>    /* Error structures         */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/***************************************************/
/* the MicroSensor API version of this header file */
/***************************************************/
#define USF_API_VERSION              2

/*********************************************/
/* macros for standard dynamic attribute IDs */
/*********************************************/
#define USF_DATTR_STRING_ID            1
#define USF_DATTR_INT32_ID             2
#define USF_DATTR_UINT32_ID            3
#define USF_DATTR_INT64_ID             4
#define USF_DATTR_UINT64_ID            5
#define USF_DATTR_FLOAT32_ID           6
#define USF_DATTR_FLOAT64_ID           7
#define USF_DATTR_STRING_ARRAY_ID      8
#define USF_DATTR_INT32_ARRAY_ID       9
#define USF_DATTR_UINT32_ARRAY_ID     10
#define USF_DATTR_INT64_ARRAY_ID      11
#define USF_DATTR_UINT64_ARRAY_ID     12
#define USF_DATTR_FLOAT32_ARRAY_ID    13
#define USF_DATTR_FLOAT64_ARRAY_ID    14
#define USF_DATTR_QUANTUM_ID          15

/****************************************/
/* values suitable for use in bitfields */
/****************************************/
#define USF_DATTR_STRING           0x0001
#define USF_DATTR_INT32            0x0002
#define USF_DATTR_UINT32           0x0004
#define USF_DATTR_INT64            0x0008
#define USF_DATTR_UINT64           0x0010
#define USF_DATTR_FLOAT32          0x0020
#define USF_DATTR_FLOAT64          0x0040
#define USF_DATTR_STRING_ARRAY     0x0080
#define USF_DATTR_INT32_ARRAY      0x0100
#define USF_DATTR_UINT32_ARRAY     0x0200
#define USF_DATTR_INT64_ARRAY      0x0400
#define USF_DATTR_UINT64_ARRAY     0x0800
#define USF_DATTR_FLOAT32_ARRAY    0x1000
#define USF_DATTR_FLOAT64_ARRAY    0x2000
#define USF_DATTR_QUANTUM          0x4000

/***********************************************/
/* properties of the custom dynamic attributes */
/***********************************************/
#define USF_RSRC_DATTR_QRY_REQS_MONITORING  0x0001


/* basic information about a resource attribute */
typedef struct usf_attribute
{
    rmc_attribute_id_t  attribute_id;
    ct_data_type_t      data_type;
    ct_value_t          value;
} usf_attribute_t;

/* basic information about a MicroSensor */
typedef struct usf_control_data
{
    ct_uint32_t    usf_API_version;        /* API version implemented by MicroSensor */
    ct_uint32_t    usf_uSensor_version;    /* version of MicroSensor */
    ct_uint64_t    usf_standard_dattrs;    /* bit mask of standard dynamic attrs */
    void           *usf_anchor;            /* anchor for re-entrancy */
    ct_uint32_t    usf_num_custom_dattrs;  /* number of custom dattrs defined */
} usf_control_data_t;

/* Custom dynamic attributes info */
typedef struct usf_custom_dattr_info
{
    char          *usf_name;               /* cda name */
    ct_int32_t    usf_data_type;           /* cda type */
    ct_int32_t    usf_variable_type;       /* cda variable type */
    ct_int32_t    usf_reporting_interval;  /* cda reporting interval in seconds */
    ct_uint32_t   usf_properties;          /* cda properties */
} usf_custom_dattr_info_t;


/*--------------------------------------------------------------------------*/
/*  MicroSensor API callback function prototypes.                           */
/*--------------------------------------------------------------------------*/

cu_error_t*
usf_get_control_data (
    ct_int32_t            argc,            /* input: argument count */
    char                  **argv,          /* input: argument vector */
    usf_control_data_t    *control_data_p  /* output: control data */
);

cu_error_t*
usf_start_standard_dattr (
    void           *anchor_p,  /* input: anchor pointer */
    ct_int32_t     dattr_ID,   /* input: standard dattr ID */
    int            *fd_p       /* output: file descriptor */
);

cu_error_t*
usf_start_standard_dattrs (
    void           *anchor_p,  /* input: anchor pointer */
    ct_uint64_t    dattr_ID,   /* input: standard dattr ID */
    int            *fd_p       /* output: file descriptor */
);

cu_error_t*
usf_stop_standard_dattr (
    void        *anchor_p,      /* input: anchor pointer */
    ct_int32_t  dattr_ID        /* input: standard dattr ID */
);

cu_error_t*
usf_stop_standard_dattrs (
    void          *anchor_p,    /* input: anchor pointer */
    ct_uint64_t   dattr_ID      /* input: standard dattr ID */
);

cu_error_t*
usf_get_standard_dattr_values (
    void               *anchor_p,   /* input: anchor pointer */
    ct_uint32_t        num_values,  /* input: number of values requested */
    usf_attribute_t    values[]     /* input/output: array of values */
);

cu_error_t*
usf_get_custom_dattr_info (
    void                       *anchor_p,    /* input: anchor pointer */
    ct_uint32_t                num_attrs,    /* number of attrs */
    usf_custom_dattr_info_t    dattr_info[]  /* output: dattr info */
);

cu_error_t*
usf_start_custom_dattr (
    void            *anchor_p,  /* input: anchor pointer */
    ct_int32_t      dattr_ID,   /* input: custom dattr ID */
    int             *fd_p       /* output: file descriptor */
);

cu_error_t*
usf_stop_custom_dattr (
    void           *anchor_p,  /* input: anchor pointer */
    ct_int32_t     dattr_ID    /* input: custom dattr ID */
);

cu_error_t*
usf_get_custom_dattr_values (
    void               *anchor_p,   /* input: anchor pointer */
    ct_uint32_t        num_values,  /* input: number of values requested */
    usf_attribute_t    values[]     /* input/output: array of values */
);

cu_error_t* usf_fini (
    void           *anchor_p,   /* input: anchor pointer */
    ct_uint32_t    unload_flag  /* unload flag */
);

#ifdef __cplusplus
} // end extern "C"
#endif /* __cplusplus */

#endif /* _CT_MICROSENSOR_DOT_H */
