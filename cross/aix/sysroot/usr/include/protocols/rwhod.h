/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/usr/include/protocols/rwhod.h 1.11                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)67	1.11  src/bos/usr/include/protocols/rwhod.h, sockinc, bos53L, l2007_25A6 1/3/07 05:06:02 */
/*
 * COMPONENT_NAME: INCPROTO
 *
 * FUNCTIONS:
 *
 * ORIGINS: 26,27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#include <userpw.h>

/*
 * rwho protocol packet format.
 */
struct	outmp {
	char	out_line[8];		/* tty name */
	char	out_name[MAXIMPL_LOGIN_NAME_MAX];		/* user id */
	long	out_time;			/* time on */
};

struct	whod {
	char	wd_vers;		/* protocol version # */
	char	wd_type;		/* packet type, see below */
	char	wd_pad[2];
	int	wd_sendtime;		/* time stamp by sender */
	int	wd_recvtime;		/* time stamp applied by receiver */
	char	wd_hostname[32];	/* hosts's name */
	int	wd_loadav[3];		/* load average as in uptime */
	int	wd_boottime;		/* time system booted */
	struct	whoent {
		struct	outmp we_utmp;	/* active tty info */
		int	we_idle;	/* tty idle time */
	} wd_we[1024 * 6 / sizeof (struct whoent)];
/* Apar IY13674 : Increasing the size of wd_we 6 times */
};

#define	WHODVERSION	1
#define	WHODTYPE_STATUS	1		/* host status */
