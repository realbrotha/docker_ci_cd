/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* tcpip530 src/tcpip/usr/include/authm.h 1.3                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)81       1.3  src/tcpip/usr/include/authm.h, tcpip, tcpip530  6/19/02  13:48:30 */ 
/*
 *   COMPONENT_NAME: tcpip
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *                    -- (                            when
 *   combined with the aggregated modules for this product)
 *   OBJECT CODE ONLY SOURCE MATERIALS
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1997
 *   All Rights Reserved
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/* Authentication types stored in high-order 16 bits */
#define	AUTHM_TYPE_AIX		(1<<16)
#define	AUTHM_TYPE_KERBEROS	(2<<16)

/* Authentication instances stored in low-order 16 bits */
#define	AUTH_INST_K4		1
#define	AUTH_INST_K5		2
#define AUTH_INST_K5DCE         4

/* Authentication methods */
#define AUTHM_STD_AIX		(AUTHM_TYPE_AIX)
#define AUTHM_KERB_4		(AUTHM_TYPE_KERBEROS|AUTH_INST_K4)
#define AUTHM_KERB_5		(AUTHM_TYPE_KERBEROS|AUTH_INST_K5)
#define AUTHM_KERB_5DCE         (AUTHM_TYPE_KERBEROS|AUTH_INST_K5DCE)

#define NUM_AUTH	4  /* number of supported authentication methods */

/* Prototypes */
int	get_auth_methods(uint **);
int	set_auth_methods(uint *);
