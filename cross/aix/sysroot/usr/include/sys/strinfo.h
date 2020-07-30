/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/strinfo.h 1.4                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1991,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)39     1.4  src/bos/kernel/sys/strinfo.h, sysxpse, bos530 10/12/95 11:52:23 */
/*
 *   COMPONENT_NAME: SYSXPSE strinfo.h
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

#ifndef	_STRINFO_H_
#define	_STRINFO_H_

typedef struct strmdi {
	int heapsize;
	int maxheap;
	int clonemaj;
	int sadmaj;
	int logmaj;
	char *strtune;
	int  stunelen;
} strmdi_t;

typedef struct strtunable {
	char	name[16];
	int	value;
} strtune_t;

#define	STR_INFO_HEAP	1
#define	STR_INFO_MODS	2
#define	STR_INFO_RUNQ	3

#endif	/* _STRINFO_H_ */
