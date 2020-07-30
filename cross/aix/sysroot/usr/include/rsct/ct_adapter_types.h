/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/*                                                                        */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2006,2009          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
#ifndef _RSCT_ADAPTER_TYPES_H_
#define _RSCT_ADAPTER_TYPES_H_

static char *rsct_adapter_types_h_sccsid = "@(#)59   1.1   src/rsct/pgs/rsctnamlib/ct_adapter_types.h, gsglobalAM, rsct_rhay53, rhay531006a 1/5/06 09:40:44";    

#ifdef __cplusplus
extern "C" {
#endif


#ifndef DONT_DEFINE_RSCT_DEVTYPES

#define RSCT_DEVTYPE_UNSUPPORTED             0
#define RSCT_DEVTYPE_ETHER                   1
#define RSCT_DEVTYPE_IEEE802                 6
#define RSCT_DEVTYPE_INFINIBAND             32
#define RSCT_DEVTYPE_PPP                   256
#define RSCT_DEVTYPE_LOOPBACK              772
#define RSCT_DEVTYPE_FDDI                  774
#define RSCT_DEVTYPE_HIPPI                 780
#define RSCT_DEVTYPE_TOKEN_RING            800
#define RSCT_DEVTYPE_CANOPUS              9696
#define RSCT_DEVTYPE_CANOPUS_FIFO         9697
#define RSCT_DEVTYPE_CANOPUS_FIFO_RDMA    9698
#define RSCT_DEVTYPE_CANOPUS_PLUS         9699
#define RSCT_DEVTYPE_KMUX                 9314
#define RSCT_DEVTYPE_HPCE                 9315

#endif /* DONT_DEFINE_RSCT_DEVTYPES */

#ifdef __cplusplus
}                                       /* end extern "C" */
#endif

#endif                                  /* _RSCT_ADAPTER_TYPES_H_ */
