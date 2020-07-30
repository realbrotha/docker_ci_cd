/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* rspc530 src/rspc/usr/include/sys/ecpio.h 1.9                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,1998          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)89	1.9  src/rspc/usr/include/sys/ecpio.h, sysxprnt, rspc530 10/15/98 11:59:38  */
/*
 *   COMPONENT_NAME: sysxprnt
 *
 *   ORIGINS: 27
 *
 */

#ifndef _H_ECPIO
#define _H_ECPIO

#include <sys/types.h>
#include <sys/trchkid.h>
#include <sys/limits.h>
#include <sys/lpio.h>

#define LPAD_ECP        (0x401) /* type of parallel adapter in struct lpquery */

#define ECP_DEVSTR_LEN  (USHRT_MAX - 2) /* maximum 1284 device identification
                                         * string length */

#define ECP_DFIFO_DEPTH (16)

#ifdef __cplusplus
extern "C" {
#endif

struct ecp_device_ident         /* ieee 1284 device identification */
{
    ushort len;                 /* length in bytes */
    uchar  str[2];              /* first 2 bytes of device identification
                                 * string */
};
typedef struct ecp_device_ident  ecp_device_ident;

/* device identification string field names */
#define ECP_MFGL        "MANUFACTURER"
#define ECP_MFG         "MFG"
#define ECP_MDLL        "MODEL"
#define ECP_MDL         "MDL"

/* first 20 bytes of the MFG + MDL fields of device id concated with the 16
 * bit uppercase hex CRC of the MFG + MDL.  See ECP design spec for full
 * description of the conversion algorithm. */
typedef struct ecp_devid ecp_devid;
#define ECP_DEVID_LEN   (24)
struct ecp_devid
{
    unsigned char val[ECP_DEVID_LEN+1];
};

/*
 * bit masks for modes the *peripheral* supports.
 */
enum ecpCapable
{
    CapNone
    , CapSPP    = 0x01
    , CapNibble = 0x02
    , CapByte   = 0x04
    , CapEPP    = 0x08          /* NOT SUPPORTED IN AIX */
    , CapECP    = 0x10

    , CapMax    = 0x80
};
typedef enum ecpCapable ecpCapable;

/* ioctls specific to IEEE1284 */
enum ecpIoctl
{
    ECP = (LPR+40)
    , ECPDEVSTR                 /* return the device identification string */
    , ECPTERMINATE              /* force back to Compatibility */
    , ECPMODECAP                /* bit map of all modes peripheral supports */
    , ECPMODE                   /* current negotiated mode */
    , ECPWFLUSH                 /* output the contents of the send buffer */
    , ECPWATOMIC                /* write each output buffer without caching */

        /*  See sys/ieee1284.h for the args used with the following. */
    , ECPS1284_D1               /* send the passed in ieee1284_d1 struct to the
                                 * peripheral.*/
    , ECPSLU                    /* Pass a logical unit channel to the
                                 * interface */

    , ECPCTLEND                 /* marker for end, 1 greater than valid ioctls */

    , ECPGET   = LPRGET
    , ECPSET   = LPRSET
    , ECPGETA  = LPRGETA
    , ECPSETA  = LPRSETA
    , ECPGTOV  = LPRGTOV
    , ECPSTOV  = LPRSTOV
    , ECPQUERY = LPQUERY
    , ECPDIAG  = LPDIAG
    , ECPMODG  = LPRMODG
    , ECPMODS  = LPRMODS
};
typedef enum ecpIoctl ecpIoctl;

enum ecpDiagCmd                 /* diagnostic commands specific to the CHRP ECP
                                 * driver */
{
    ECP_R_TFIFO = 0x10          /* read the tfifo */
    , ECP_W_TFIFO               /* write the tfifo */
    , ECP_R_ECR                 /* read the ecr */
    , ECP_W_ECR                 /* write the ecr */
    , ECP_WR_DMA                /* Write and read back a buffer from the tfifo
                                 * using dma */
};
typedef enum ecpDiagCmd ecpDiagCmd;

struct ecp_diag                 /* struct to pass for the ecp dma diagnostic
                                 * testing. */
{
    ecpDiagCmd cmd;
    int        value;
#define ECP_SUCC        (0)
#define ECP_DIAG_ERR    (-1)    /* return value when failure occurred */
    uchar      buf[ECP_DFIFO_DEPTH];
    int        err_map;         /* error reported by d_(un)map_slave. */
    int        bytes_done;      /* bytes reported as moved by d_(un)map_slave */
};
typedef struct ecp_diag ecp_diag;

enum ecpIFType
{
    IF_Standard                 /* plain old Centronics parallel printer. */
    , IF_Converged              /* Reversed nInit, nSelectIn, nAutoFd
                                 * settings.                              */
    , IF_IEEE1284               /* The real reason we came this way.      */
    , IF_None         = 0xff    /* Before any interface is configured.    */
};
typedef enum ecpIFType ecpIFType;

#ifdef __cplusplus
}
#endif
#endif /* _H_ECPIO */
