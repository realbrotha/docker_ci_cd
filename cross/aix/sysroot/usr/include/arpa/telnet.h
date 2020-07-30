/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/arpa/telnet.h 1.10                          */
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
/* @(#)72	1.10  src/bos/usr/include/arpa/telnet.h, sockinc, bos530 12/12/97 23:27:54 */
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

/*
 * Definitions for the TELNET protocol.
 */
#define	IAC	255		/* interpret as command: */
#define	DONT	254		/* you are not to use option */
#define	DO	253		/* please, you use option */
#define	WONT	252		/* I won't use option */
#define	WILL	251		/* I will use option */
#define	SB	250		/* interpret as subnegotiation */
#define	GA	249		/* you may reverse the line */
#define	EL	248		/* erase the current line */
#define	EC	247		/* erase the current character */
#define	AYT	246		/* are you there */
#define	AO	245		/* abort output--but let prog finish */
#define	IP	244		/* interrupt process--permanently */
#define	BREAK	243		/* break */
#define	DM	242		/* data mark--for connect. cleaning */
#define	NOP	241		/* nop */
#define	SE	240		/* end sub negotiation */
#define EOR     239             /* end of record (transparent mode) */
#define ABORT   238             /* Abort process */
#define SUSP    237             /* Suspend process */
#define xEOF    236             /* End of file: EOF is already used... */

#ifdef _CSECURITY
#define	SAK	200		/* send secure attention key to remote */
#endif  /* _CSECURITY */

#define SYNCH	242		/* for telfunc calls */

#ifdef TELCMDS
char *telcmds[] = {
	"SE", "NOP", "DMARK", "BRK", "IP", "AO", "AYT", "EC",
	"EL", "GA", "SB", "WILL", "WONT", "DO", "DONT", "IAC",0
};
#else
extern char *telcmds[];
#endif   /* TELCMDS  */

#define TELCMD_FIRST    xEOF
#define TELCMD_LAST     IAC
#define TELCMD_OK(x)    ((unsigned int)(x) <= TELCMD_LAST && \
                         (unsigned int)(x) >= TELCMD_FIRST)
#define TELCMD(x)       telcmds[(x)-TELCMD_FIRST]

/* telnet options */
#define TELOPT_BINARY	0	/* 8-bit data path */
#define TELOPT_ECHO	1	/* echo */
#define	TELOPT_RCP	2	/* prepare to reconnect */
#define	TELOPT_SGA	3	/* suppress go ahead */
#define	TELOPT_NAMS	4	/* approximate message size */
#define	TELOPT_STATUS	5	/* give status */
#define	TELOPT_TM	6	/* timing mark */
#define	TELOPT_RCTE	7	/* remote controlled transmission and echo */
#define TELOPT_NAOL 	8	/* negotiate about output line width */
#define TELOPT_NAOP 	9	/* negotiate about output page size */
#define TELOPT_NAOCRD	10	/* negotiate about CR disposition */
#define TELOPT_NAOHTS	11	/* negotiate about horizontal tabstops */
#define TELOPT_NAOHTD	12	/* negotiate about horizontal tab disposition */
#define TELOPT_NAOFFD	13	/* negotiate about formfeed disposition */
#define TELOPT_NAOVTS	14	/* negotiate about vertical tab stops */
#define TELOPT_NAOVTD	15	/* negotiate about vertical tab disposition */
#define TELOPT_NAOLFD	16	/* negotiate about output LF disposition */
#define TELOPT_XASCII	17	/* extended ascic character set */
#define	TELOPT_LOGOUT	18	/* force logout */
#define	TELOPT_BM	19	/* byte macro */
#define	TELOPT_DET	20	/* data entry terminal */
#define	TELOPT_SUPDUP	21	/* supdup protocol */
#define	TELOPT_SUPDUPOUTPUT 22	/* supdup output */
#define	TELOPT_SNDLOC	23	/* send location */
#define	TELOPT_TTYPE	24	/* terminal type */
#define	TELOPT_EOR	25	/* end or record */
#define TELOPT_TUID     26      /* TACACS user identification */
#define TELOPT_OUTMRK   27      /* output marking */
#define TELOPT_TTYLOC   28      /* terminal location number */
#define TELOPT_3270REGIME 29    /* 3270 regime */
#define TELOPT_X3PAD    30      /* X.3 PAD */
#define TELOPT_NAWS	31	/* Negotiate about Window Size */
#define TELOPT_TSPEED   32      /* terminal speed */
#define TELOPT_LFLOW    33      /* remote flow control */
#define TELOPT_LINEMODE 34      /* Linemode option */
#define TELOPT_XDISPLOC 35      /* X Display Location */
#define TELOPT_OLD_ENVIRON 36   /* Old - Environment variables */
#define TELOPT_AUTHENTICATION 37/* Authenticate */
#define TELOPT_ENCRYPT  38      /* Encryption option */
#define TELOPT_NEW_ENVIRON 39   /* New - Environment variables */

#ifdef _CSECURITY
#define	TELOPT_SAK	200	/* remote side supports SAK */
#endif  /* _CSECURITY */
#define TELOPT_EXOPL	255	/* extended-options-list */

#ifdef TELOPTS
#define	NTELOPTS	(1+TELOPT_NEW_ENVIRON)
char *telopts[NTELOPTS+1] = {
	"BINARY", "ECHO", "RCP", "SUPPRESS GO AHEAD", "NAME",
	"STATUS", "TIMING MARK", "RCTE", "NAOL", "NAOP",
	"NAOCRD", "NAOHTS", "NAOHTD", "NAOFFD", "NAOVTS",
	"NAOVTD", "NAOLFD", "EXTEND ASCII", "LOGOUT", "BYTE MACRO",
	"DATA ENTRY TERMINAL", "SUPDUP", "SUPDUP OUTPUT",
	"SEND LOCATION", "TERMINAL TYPE", "END OF RECORD",
        "TACACS UID", "OUTPUT MARKING", "TTYLOC",
        "3270 REGIME", "X.3 PAD", "NAWS", "TSPEED", "LFLOW",
        "LINEMODE", "XDISPLOC", "OLD-ENVIRON", "AUTHENTICATION",
        "ENCRYPT", "NEW-ENVIRON",
        0,
};
#define TELOPT_FIRST    TELOPT_BINARY
#define TELOPT_LAST     TELOPT_NEW_ENVIRON
#define TELOPT_OK(x)    ((unsigned int)(x) <= TELOPT_LAST)
#define TELOPT(x)       telopts[(x)-TELOPT_FIRST]
#endif /* TELOPTS */


/* sub-option qualifiers */
#define	TELQUAL_IS	0	/* option is... */
#define	TELQUAL_SEND	1	/* send option */
#define TELQUAL_INFO    2       /* ENVIRON: informational version of IS */
#define TELQUAL_REPLY   2       /* AUTHENTICATION: client version of IS */
#define TELQUAL_NAME    3       /* AUTHENTICATION: client version of IS */

/* env definitions */
#define OLD_ENV_VAR     1
#define OLD_ENV_VALUE   0
#define NEW_ENV_VAR     0
#define NEW_ENV_VALUE   1
#define ENV_ESC         2
#define ENV_USERVAR     3

/* AUTHENTICATION suboptions */
/*
 * Who is authenticating who ...
 */
#define AUTH_WHO_CLIENT         0       /* Client authenticating server */
#define AUTH_WHO_SERVER         1       /* Server authenticating client */
#define AUTH_WHO_MASK           1

/*
 * amount of authentication done
 */
#define AUTH_HOW_ONE_WAY        0
#define AUTH_HOW_MUTUAL         2
#define AUTH_HOW_MASK           2

/*
 * should we be encrypting? (not yet formally standardized)
 */
#define AUTH_ENCRYPT_OFF        0
#define AUTH_ENCRYPT_ON         4
#define AUTH_ENCRYPT_MASK       4

#define AUTHTYPE_NULL           0
#define AUTHTYPE_KERBEROS_V4    1
#define AUTHTYPE_KERBEROS_V5    2
#define AUTHTYPE_SPX            3
#define AUTHTYPE_MINK           4
#define AUTHTYPE_CNT            5

#define AUTHTYPE_TEST           99

#ifdef  AUTH_NAMES
char *authtype_names[] = {
        "NULL", "KERBEROS_V4", "KERBEROS_V5", "SPX", "MINK", 0,
};
#else
extern char *authtype_names[];
#endif

#define AUTHTYPE_NAME_OK(x)     ((unsigned int)(x) < AUTHTYPE_CNT)
#define AUTHTYPE_NAME(x)        authtype_names[x]

