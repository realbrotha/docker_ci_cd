/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/diag/atu.h 1.2                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1991               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)18	1.2  src/bos/usr/include/diag/atu.h, cmddiag, bos530 2/19/91 17:12:38 */
/*
 *   COMPONENT_NAME: CMDDIAG
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1991
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*****************************************************************************/
/* tu is the test unit number.                                               */
/* mfg is manufacturing mode.                                                */
/* loop is number of times to repeat the test unit. If an error occurs       */
/* the application test unit exits.                                          */
/* r1 and r2 is reserved.                                                    */
/*****************************************************************************/
typedef struct tucb_t {
        long tu,mfg,loop;
        long r1,r2;
};
