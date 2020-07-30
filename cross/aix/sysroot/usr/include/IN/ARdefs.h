/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53E src/bos/usr/include/IN/ARdefs.h 1.13                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)85       1.13  src/bos/usr/include/IN/ARdefs.h, libIN, bos53E, e2005_30C6 7/25/05 17:55:08 */
/*
 * COMPONENT_NAME: LIBIN
 *
 * FUNCTIONS:
 *
 * ORIGINS: 9,27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

/* Archive format identifying numbers */
#define NO_AR_ID	0x00
#define	S3_AR_ID	0x03
#define S5_AR_ID	0x05
#define BK_AR_ID	0x2a
#define	AIAF_AR_ID	0x2f
#define	ABIG_AR_ID	0x30

/* Definitions for using ARforeach */
typedef struct {
	FILE *file;			/* positioned FILE pointer */
	long date;
	unsigned int uid, gid;
	long mode;			/* facts from the ar header */
#ifdef __AR_BIG__
	long long size;
	long long oldpos;		/* file position of old header */
#else
	long size;
	long oldpos;			/* file position of old header */
#endif
	char *name;}			/* file name ("" is symbol table ) */
    ARparm;
