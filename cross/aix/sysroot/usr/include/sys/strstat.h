/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/strstat.h 1.5                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1991,2000          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)42     1.5  src/bos/kernel/sys/strstat.h, sysxpse, bos530 3/9/00 17:36:51 */
/*
 *   COMPONENT_NAME: SYSXPSE strstat.h
 *
 *   ORIGINS: 27 63
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
 */

#ifndef _STRSTAT_
#define _STRSTAT_

#include <sys/inttypes.h>

/* module statistics structure */
struct	module_stat {
	long	ms_pcnt;	/* count of calls to put proc */
	long	ms_scnt;	/* count of calls to service proc */
	long	ms_ocnt;	/* count of calls to open proc */
	long	ms_ccnt;	/* count of calls to close proc */
	long	ms_acnt;	/* count of calls to admin proc */
	char	* ms_xptr;	/* pointer to private statistics */
	short	ms_xsize;	/* length of private statistics buffer */
};

/* allocb() statistic failures structures */
struct allocstat {
	__long32_t    as_lowpri;   /* fails count of allocb() calls with a
				      low priority */
	__long32_t    as_medpri;   /* fails count of allocb() calls with a
				      medium priority */
	__long32_t    as_hipri;    /* fails count of allocb() calls with a
				      high priority */
};

#endif
