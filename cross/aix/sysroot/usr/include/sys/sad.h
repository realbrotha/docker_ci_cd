/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/sad.h 1.7                                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1991,1999          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)36       1.7  src/bos/kernel/sys/sad.h, sysxpse, bos530 2/26/99 13:51:46 */
/*
 *   COMPONENT_NAME: SYSXPSE sad.h
 *
 *   ORIGINS: 27 63 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1991
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 *   Copyright (c) 1990  Mentat Inc.
 *   
 *   LEVEL 1, 5 Years Bull Confidential Information
 *
 */

#include <sys/types.h>

#ifndef _SAD_
#define _SAD_

#define	MAXAPUSH	8

/* Ioctl commands for sad driver */
#define	SAD_BASE	('A' << 8)
#define	SAD_SAP		(SAD_BASE + 1)	/* Set autopush information */
#define	SAD_GAP		(SAD_BASE + 2)	/* Get autopush information */
#define	SAD_VML		(SAD_BASE + 3)	/* Validate a list of modules */

/* Ioctl structure used for SAD_SAP and SAD_GAP commands */
struct strapush {
	uint		sap_cmd;
	__long32_t	sap_major;
	__long32_t	sap_minor;
	__long32_t	sap_lastminor;
	__long32_t	sap_npush;
	char		sap_list[MAXAPUSH][FMNAMESZ+1];
};

/* Command values for sap_cmd */
#define	SAP_ONE		1	/* Configure a single minor device */
#define	SAP_RANGE	2	/* Configure a range of minor devices */
#define	SAP_ALL		3	/* Configure all minor devices */
#define	SAP_CLEAR	4	/* Clear autopush information */

#ifdef _KERNEL
extern int sad_get_autopush(int, int, struct strapush *);
#endif /* KERNEL */

#endif /* _SAD_ */
