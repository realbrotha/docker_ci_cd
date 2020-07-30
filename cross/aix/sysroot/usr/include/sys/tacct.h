/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/sbin/acct/tacct.h 1.4                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,2003          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)40	1.4  src/bos/usr/sbin/acct/tacct.h, cmdacct, bos530 11/12/03 18:36:56 */
/*
 * COMPONENT_NAME:  (CMDACCT) Command Accounting
 *
 * FUNCTIONS: none
 *
 * ORIGIN: 3,9,27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *	total accounting (for acct period), also for day
 */

/* Float arrays below contain prime and non-prime components */
#include "userpw.h"

#define TACCTXVER "#=V2.0=#"

struct	tacct	{
	uid_t		ta_uid;		/* userid */
	char		ta_name[8];	/* login name */
	float       ta_cpu[2];      /* cum. cpu time (mins) */
	float       ta_kcore[2];    /* cum kcore-mins */
	float       ta_io[2];       /* cum. chars xferred (512s) */
	float       ta_rw[2];       /* cum. blocks read/written */
	float       ta_con[2];      /* cum. connect time (mins) */
	float		ta_du;		/* cum. disk usage */
	long        ta_qsys;        /* queueing sys charges (pgs) */
	float		ta_fee; 	/* fee for special services */
	long		ta_pc;		/* count of processes */
	unsigned short	ta_sc;		/* count of login sessions */
	unsigned short	ta_dc;		/* count of disk samples */
};

struct	tacctx	{
	uid_t		ta_uid;		/* userid */
	char		ta_name[256];	/* login name */
	float       ta_cpu[2];      /* cum. cpu time (mins) */
	float       ta_kcore[2];    /* cum kcore-mins */
	float       ta_io[2];       /* cum. chars xferred (512s) */
	float       ta_rw[2];       /* cum. blocks read/written */
	float       ta_con[2];      /* cum. connect time (mins) */
	float		ta_du;		/* cum. disk usage */
	long        ta_qsys;        /* queueing sys charges (pgs) */
	float		ta_fee; 	/* fee for special services */
	long		ta_pc;		/* count of processes */
	unsigned short	ta_sc;		/* count of login sessions */
	unsigned short	ta_dc;		/* count of disk samples */
};

