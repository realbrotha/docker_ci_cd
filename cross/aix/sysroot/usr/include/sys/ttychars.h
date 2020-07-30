/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/ttychars.h 1.13                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)37	1.13  src/bos/kernel/sys/ttychars.h, cmdtty, bos530 7/25/02 19:28:20 */

/*
 * COMPONENT_NAME: (sysxtty) System Extension for tty support
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 3, 9, 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *
 * <bsd/sys/ttychars.h - a la 4.xBSD for BSD to AIX porting tools
 *	derived from BSD <sys/ttychars.h>
 * COPYRIGHT 1987 IBM CORP.
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	(#)ttychars.h	7.1 (Berkeley) 6/4/86
 */

/*
 * User visible structures and constants
 * related to terminal handling.
 */
#ifndef _H_TTYCHARS_
#define	_H_TTYCHARS_


struct ttychars {
	char	tc_erase;	/* erase last character */
	char	tc_kill;	/* erase entire line */
	char	tc_intrc;	/* interrupt */
	char	tc_quitc;	/* quit */
	char	tc_startc;	/* start output */
	char	tc_stopc;	/* stop output */
	char	tc_eofc;	/* end-of-file */
	char	tc_brkc;	/* input delimiter (like nl) */
	char	tc_suspc;	/* stop process signal */
	char	tc_dsuspc;	/* delayed stop process signal */
	char	tc_rprntc;	/* reprint line */
	char	tc_flushc;	/* flush output (toggles) */
	char	tc_werasc;	/* word erase */
	char	tc_lnextc;	/* literal next character */
};

#define	CTRL(c)		('c'&037)
#define	CTRL2(c)	((c)&037)

/* default special characters */
#define	CBRK	0377
#define	CRPRNT	CTRL2('r')

#define CDSUSP  CTRL2('y')
#define CEOF    '\004'                  /* ^D */
#define CEOT    CEOF
#define CERASE  '\010'                  /* ^H */
#define CFLUSH  CTRL2('o')
#define CINTR   '\003'                  /* ^C */
#define CKILL   '\025'                  /* ^U */
#define CLNEXT  CTRL2('v')
#define CQUIT   '\034'                  /* ^\ */
#define CSTART  '\021'                  /* ^Q */
#define CSTOP   '\023'                  /* ^S */
#define CSUSP   CTRL2('z')
#define CWERASE CTRL2('w')

#endif /* _H_TTYCHARS_ */
