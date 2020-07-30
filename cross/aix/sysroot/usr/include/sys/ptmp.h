/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/sbin/acct/ptmp.h 1.5                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)33 1.5  src/bos/usr/sbin/acct/ptmp.h, cmdacct, bos530 11/12/03 18:33:14 */
/*
 * COMPONENT_NAME: (CMDACCT) Command Accounting
 *
 * FUNCTIONS: none
 *
 * ORIGINS: 3,9,27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1993
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *	per process temporary data
 */
#include "userpw.h"

struct ptmp {
	uid_t	pt_uid;			/* userid */
	char	pt_name[MAXIMPL_LOGIN_NAME_MAX];		/* login name */
	float   pt_cpu[2];		/* CPU (sys+usr) P/NP time tics */
	long    pt_io;                  /* chars transferred P/NP */
	long    pt_rw;                  /* blocks read/written P/NP */
	unsigned pt_mem;		/* avg. memory size (64byte clicks) */
};	
