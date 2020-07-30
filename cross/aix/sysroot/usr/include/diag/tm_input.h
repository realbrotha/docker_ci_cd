/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/diag/tm_input.h 1.4                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1994          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)29	1.4  src/bos/usr/include/diag/tm_input.h, cmddiag, bos530 3/25/94 06:12:38 */
/*
 *   COMPONENT_NAME: CMDDIAG
 *
 *   FUNCTIONS: Diagnostic header file.
 *
 *   ORIGINS: 27, 83
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1989, 1994
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 *
 *   LEVEL 1, 5 Years Bull Confidential Information
 *
 */


#ifndef _H_TM_INPUT
#define _H_TM_INPUT

#ifndef NAMESIZE
#define	NAMESIZE	16
#endif
#ifndef LOCSIZE
#define LOCSIZE		16
#endif

struct tm_input {
	short exenv;
	short advanced;
	short system;
	short dmode;
	char date[80];
	short loopmode;
	short lcount;
	short lerrors;
	short console;
	char parent[NAMESIZE];
	char parentloc[LOCSIZE];
	char dname[NAMESIZE];
	char dnameloc[LOCSIZE];
	char child1[NAMESIZE];
	short state1;
	char childloc1[LOCSIZE];
	char child2[NAMESIZE];
	short state2;
	char childloc2[LOCSIZE];
	long pid;
	short cpuid;
};

#endif
