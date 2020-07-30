/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/timod.h 1.5                                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1991,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)44     1.5  src/bos/kernel/sys/timod.h, sysxpse, bos530 2/21/96 15:19:40 */
/*
 *   COMPONENT_NAME: SYSXPSE
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 18,27,63
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1991,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *   (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC.
 *   ALL RIGHTS RESERVED
 *
 *   Copyright (c) 1990  Mentat Inc.
 *
 */

#ifndef _TIMOD_H
#define	_TIMOD_H

/* Ioctl values for timod requests */
#define	TI_BIND			1
#define	TI_GETINFO		2
#define	TI_OPTMGMT		3
#define	TI_UNBIND		4
#define	TI_GETMYNAME		5
#define	TI_GETPEERNAME		6
#define	TI_ADDR			7

/* Extra values for XTI */
#define	TI_XTI_HELLO		8	/* We are XTI, not TLI */
#define	TI_XTI_GET_STATE	9	/* Retrieve state saved for XTI */
#define	TI_XTI_CLEAR_EVENT	10	/* Clear disc or ordrel indication */

#define	TI_XTI_MODE		11
#define	TI_TLI_MODE		12

#define	TI_XTI_GET_SEQUENCE	13	/* Retrieve sequence number for XTI */

/* Return structure for TI_XTI_GET_STATE request */
typedef struct xti_state_s {
	unsigned int	xtis_qlen;	/* Saved qlen parameter from t_bind */
} XTIS, * XTISP;

#endif	/* _TIMOD_H */
