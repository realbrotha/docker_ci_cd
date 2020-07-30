/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/bin/que/accrec.h 1.2                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)22	1.2  src/bos/usr/bin/que/accrec.h, cmdque, bos530 6/17/93 15:17:17 */
/*
 *   COMPONENT_NAME: CMDQUE
 *
 *   FUNCTIONS: none
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1989,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/* This is the accounting record used for keeping track of
 * how many pages are charged to each user.
 */
struct acctrec
	{   char from[255];	/* User's name.... e.g. dean@jlkey */
	    char acctchar;	/* not used                        */
	    long acctdate;	/* date last job made...not used   */
	    int  pages;		/* number of pages charged.        */
	    int	numjobs;	/* number of jobs charged.         */
	} acctrec;
