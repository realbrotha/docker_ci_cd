/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/ioctl.h 1.33.7.4                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1989,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)09	1.33.7.4  src/bos/kernel/sys/ioctl.h, sysio, bos53V, v2009_12B5 2/18/09 15:47:27 */
/*
 * COMPONENT_NAME: (SYSIO) System I/O
 *
 * FUNCTIONS: ioctl definitions
 *
 * ORIGINS: 27, 26, 83
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	(#)ioctl.h	7.1 (Berkeley) 6/4/86
 */

#ifndef _H_IOCTL
#define _H_IOCTL


#ifdef __cplusplus
extern "C" {
#endif



#define	IOCTYPE	0xff00
#define IOCINFO 0xff01
#define IOCCONFIG 0xff02

/* 
 *
 * ioctl.h - ioctl definitions a la 4.xBSD for BSD to AIX porting tools
 *	derived from BSD <sys/ioctl.h>
 */

/*
 * Ioctl definitions
 */
#ifndef	_IOCTL_
#define	_IOCTL_

#include <standards.h>

#include <sys/ttychars.h>
#include <sys/ttydev.h>

#ifdef _ALL_SOURCE

/* Common ioctl's for all disciplines which are handled in ttiocom */
enum tty_ioctl {
    TXISATTY = ('X'<<8),		/* quick path for isatty */
    TXTTYNAME,				/* quick path for ttyname */
    TXGETLD,				/* get line discipline */
    TXSETLD,				/* set line discipline */
    TXGETCD,				/* get control disciplines */
    TXADDCD,				/* add control discipline */
    TXDELCD,				/* delete control discipline */
    TXSBAUD,				/* set integer baud rate */
    TXGBAUD,				/* get integer baud rate */
    TXSETIHOG,				/* set the input buffer limit */
    TXSETOHOG,				/* set the output buffer limit */
    TXGPGRP,				/* get p grp with posix security */
    TXSPGRP,				/* set p grp with posix security */
    TXSETMASK				/* per tty trace ioctl */
};

#define TTNAMEMAX 32			/* used with TXGETLD, et al */

union txname {				/* used with TXGETCD */
    int tx_which;			/* which name to get -- inbound */
    char tx_name[TTNAMEMAX];		/* the name -- outbound */
};

/* 
 * window size structure used with TXSETWIN and TXGETWIN.  This is 
 * exactly the same as the Berkeley structure and can be used with 
 * TIOCSWINSZ and TIOCGWINSZ -- in fact they are defined to be the 
 * same.
 */
struct winsize {
	unsigned short	ws_row;			/* rows, in characters */
	unsigned short	ws_col;			/* columns, in characters */
	unsigned short	ws_xpixel;		/* horizontal size, pixels */
	unsigned short	ws_ypixel;		/* vertical size, pixels */
};

#endif /* _ALL_SOURCE */

struct tchars {
	char	t_intrc;	/* interrupt */
	char	t_quitc;	/* quit */
	char	t_startc;	/* start output */
	char	t_stopc;	/* stop output */
	char	t_eofc;		/* end-of-file */
	char	t_brkc;		/* input delimiter (like nl) */
};
struct ltchars {
	char	t_suspc;	/* stop process signal */
	char	t_dsuspc;	/* delayed stop process signal */
	char	t_rprntc;	/* reprint line */
	char	t_flushc;	/* flush output (toggles) */
	char	t_werasc;	/* word erase */
	char	t_lnextc;	/* literal next character */
};

/*
 * Structure for TIOCGETP and TIOCSETP ioctls.
 */

struct sgttyb {
	char	sg_ispeed;		/* input speed */
	char	sg_ospeed;		/* output speed */
	char	sg_erase;		/* erase character */
	char	sg_kill;		/* kill character */
	short	sg_flags;		/* mode flags */
};

/*
 * Pun for SUN.
 */
struct ttysize {
	unsigned short	ts_lines;
	unsigned short	ts_cols;
	unsigned short	ts_xxx;
	unsigned short	ts_yyy;
};
#define	TIOCGSIZE	TIOCGWINSZ
#define	TIOCSSIZE	TIOCSWINSZ


#ifndef _IO
/*
 * Ioctl's have the command encoded in the lower word,
 * and the size of any in or out parameters in the upper
 * word.  The high 2 bits of the upper word are used
 * to encode the in/out status of the parameter; for now
 * we restrict parameters to at most 128 bytes.
 */
 /*
  * Important note:
  *	All of these macros are also defined in stropts.h same as here,
  * 	so any changes to these should reflect in the stropts.h also.
  */
#define	IOCPARM_MASK	0x7f		/* parameters must be < 128 bytes */
#define	IOC_VOID	0x20000000	/* no parameters */
#define	IOC_OUT		0x40000000	/* copy out parameters */
/* THIS FILE IS IN BOS_PRE43 SIMPLY TO PROVIDE A TEMPORARY WORKAROUND FOR
 * A COMPILER BUG IN THE 64BIT COMPILER.  WHEN THE COMPILER IS FIXED, THIS
 * VERSION OF ioctl.h WILL BE REMOVED.
 */
#define	IOC_IN		(0x40000000<<1)	/* copy in parameters */
#define	IOC_INOUT	(IOC_IN|IOC_OUT)
/* the 0x20000000 is so we can distinguish new ioctl's from old */
#define	_IO(x,y)	(IOC_VOID|(x<<8)|y)
#define	_IOR(x,y,t)	(IOC_OUT|((sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
#define	_IOW(x,y,t)	(IOC_IN|((sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
/* this should be _IORW, but stdio got there first */
#define	_IOWR(x,y,t)	(IOC_INOUT|((sizeof(t)&IOCPARM_MASK)<<16)|(x<<8)|y)
#endif /* _IO */

/*
 * tty ioctl commands
 */
#define	TIOCGETD	_IOR('t', 0, int)	/* get line discipline */
#define	TIOCSETD	_IOW('t', 1, int)	/* set line discipline */
#define	TIOCHPCL	_IO('t', 2)		/* hang up on last close */
#define	TIOCMODG	_IOR('t', 3, int)	/* get modem control state */
#define	TIOCMODS	_IOW('t', 4, int)	/* set modem control state */
#define		TIOCM_LE	0001		/* line enable */
#define		TIOCM_DTR	0002		/* data terminal ready */
#define		TIOCM_RTS	0004		/* request to send */
#define		TIOCM_ST	0010		/* secondary transmit */
#define		TIOCM_SR	0020		/* secondary receive */
#define		TIOCM_CTS	0040		/* clear to send */
#define		TIOCM_CAR	0100		/* carrier detect */
#define		TIOCM_CD	TIOCM_CAR
#define		TIOCM_RNG	0200		/* ring */
#define		TIOCM_RI	TIOCM_RNG
#define		TIOCM_DSR	0400		/* data set ready */
#define	TIOCGETP	_IOR('t', 8,struct sgttyb)/* get parameters -- gtty */
#define	TIOCSETP	_IOW('t', 9,struct sgttyb)/* set parameters -- stty */
#define	TIOCSETN	_IOW('t',10,struct sgttyb)/* as above, but no flushtty */
#define	TIOCEXCL	_IO('t', 13)		/* set exclusive use of tty */
#define	TIOCNXCL	_IO('t', 14)		/* reset exclusive use of tty */
#define	TIOCFLUSH	_IOW('t', 16, int)	/* flush buffers */
#define	TIOCSETC	_IOW('t',17,struct tchars)/* set special characters */
#define	TIOCGETC	_IOR('t',18,struct tchars)/* get special characters */
#define		TANDEM		0x00000001	/* send stopc on out q full */
#define		CBREAK		0x00000002	/* half-cooked mode */
#define		LCASE		0x00000004	/* simulate lower case */

#define		ECHO		0x00000008	/* echo input */

#define		CRMOD		0x00000010	/* map \r to \r\n on output */
#define		RAW		0x00000020	/* no i/o processing */
#define		ODDP		0x00000040	/* get/send odd parity */
#define		EVENP		0x00000080	/* get/send even parity */
#define		ANYP		0x000000c0	/* get any parity/send none */
#define		CRDELAY		0x00000300	/* \r delay */
#define			CR0	0x00000000
#define			CR1	0x00000100	/* tn 300 */
#define			CR2	0x00000200	/* tty 37 */
#define			CR3	0x00000300	/* concept 100 */
#define		TBDELAY		0x00000c00	/* horizontal tab delay */
#define			TAB0	0x00000000

#define			TAB1	0x00000400	/* tty 37 */
#define			TAB2	0x00000800

#define		XTABS		0x00000c00	/* expand tabs on output */
#define		BSDELAY		0x00001000	/* \b delay */
#define			BS0	0x00000000

#define			BS1	0x00001000

#define		VTDELAY		0x00002000	/* vertical tab delay */
#define			FF0	0x00000000

#define			FF1	0x00002000	/* tty 37 */

#define		NLDELAY		0x0000c000	/* \n delay */

#define			NL0	0x00000000
#define			NL1	0x00004000	/* tty 37 */
#define			NL2	0x00008000	/* vt05 */
#define			NL3	0x0000c000

#define		ALLDELAY	(NLDELAY|TBDELAY|CRDELAY|VTDELAY|BSDELAY)

#define		TOSTOP		0x00010000	/* SIGSTOP on bckgnd output */

#define		PRTERA		0x00020000	/* \ ... / erase */
#define		CRTERA		0x00040000	/* " \b " to wipe out char */
#define		TILDE		0x00080000	/* hazeltine tilde kludge */

#define		FLUSHO		0x00100000	/* flush output to terminal */

#define		LITOUT		0x00200000	/* literal output */
#define		CRTBS		0x00400000	/* do backspacing for crt */
#define		MDMBUF		0x00800000	/* dtr pacing */
#define		NOHANG		0x01000000	/* no SIGHUP on carrier drop */
#define		L001000		0x02000000
#define		CRTKIL		0x04000000	/* kill line with " \b " */
#define		PASS8		0x08000000
#define		CTLECH		0x10000000	/* echo control chars as ^X */

#define		PENDIN		0x20000000	/* tp->t_rawq needs reread */

#define		DECCTQ		0x40000000	/* only ^Q starts after ^S */
#define		NOFLUSH		0x80000000	/* no output flush on signal */


/* SYS V REL. 4 PTY IOCTLs    */
#define UNLKPT          _IO('t',70)             /* unlock slave pty */
#define ISPTM           _IO('t',71)             /* ret. maj+min of pty master */
#define ISPTS           _IO('t',73)             /* return maj+min of slave */
#define GRTPT           _IO('t',74)             /* grantpt slave pty*/
#define RLOGIND         _IO('t',75)             /* for rlogind protocol in ptydd */
#define TELNETDP        _IO('t',76)             /* for telnetd protocol in ptydd */

#define	TIOCCONS	_IOW('t', 98, int)	/* become virtual console */
#define	TIOCGSID	_IOR('t', 72, int)	/* get the tty session id */

#ifdef	_BSD_INCLUDES
/*
 * Added for 4.3 BSD.
 */
#define		NOFLSH		NOFLUSH		/* no output flush on signal */


#endif	/* _BSD_INCLUDES */

						/* locals, from 127 down */
#define	TIOCLBIS	_IOW('t', 127, int)	/* bis local mode bits */
#define	TIOCLBIC	_IOW('t', 126, int)	/* bic local mode bits */
#define	TIOCLSET	_IOW('t', 125, int)	/* set entire mode word */
#define	TIOCLGET	_IOR('t', 124, int)	/* get local modes */
#define		LCRTBS		(CRTBS>>16)
#define		LPRTERA		(PRTERA>>16)
#define		LCRTERA		(CRTERA>>16)
#define		LTILDE		(TILDE>>16)
#define		LMDMBUF		(MDMBUF>>16)
#define		LLITOUT		(LITOUT>>16)
#define		LTOSTOP		(TOSTOP>>16)
#define		LFLUSHO		(FLUSHO>>16)
#define		LNOHANG		(NOHANG>>16)
#define		LCRTKIL		(CRTKIL>>16)
#define		LPASS8		(PASS8>>16)
#define		LCTLECH		(CTLECH>>16)
#define		LPENDIN		(PENDIN>>16)
#define		LDECCTQ		(DECCTQ>>16)
#define		LNOFLSH		(NOFLUSH>>16)
#define	TIOCSBRK	_IO('t', 123)		/* set break bit */
#define	TIOCCBRK	_IO('t', 122)		/* clear break bit */
#define	TIOCSDTR	_IO('t', 121)		/* set data terminal ready */
#define	TIOCCDTR	_IO('t', 120)		/* clear data terminal ready */
#define	TIOCGPGRP	_IOR('t', 119, int)	/* get process group */
#define	TIOCSPGRP	_IOW('t', 118, int)	 /* set process gorup */
#define	TIOCSLTC	_IOW('t',117,struct ltchars)/* set local special chars */
#define	TIOCGLTC	_IOR('t',116,struct ltchars)/* get local special chars */
#define	TIOCOUTQ	_IOR('t', 115, int)	/* output queue size */
#define	TIOCSTI		_IOW('t', 114, char)	/* simulate terminal input */
#define	TIOCNOTTY	_IO('t', 113)		/* void tty association */
#define	TIOCPKT		_IOW('t', 112, int)	/* pty: set/clear packet mode */
#define		TIOCPKT_DATA		0x00	/* data packet */
#define		TIOCPKT_FLUSHREAD	0x01	/* flush packet */
#define		TIOCPKT_FLUSHWRITE	0x02	/* flush packet */
#define		TIOCPKT_STOP		0x04	/* stop output */
#define		TIOCPKT_START		0x08	/* start output */
#define		TIOCPKT_NOSTOP		0x10	/* no more ^S, ^Q */
#define		TIOCPKT_DOSTOP		0x20	/* now do ^S ^Q */
#define	TIOCSTOP	_IO('t', 111)		/* stop output, like ^S */
#define	TIOCSTART	_IO('t', 110)		/* start output, like ^Q */
#define	TIOCMSET	_IOW('t', 109, int)	/* set all modem bits */
#define	TIOCMBIS	_IOW('t', 108, int)	/* bis modem bits */
#define	TIOCMBIC	_IOW('t', 107, int)	/* bic modem bits */
#define	TIOCMGET	_IOR('t', 106, int)	/* get all modem bits */
#define	TIOCREMOTE	_IOW('t', 105, int)	/* remote input editing */
#define	TIOCGWINSZ	_IOR('t', 104, struct winsize) 	/* get window size */
#define	TIOCSWINSZ	_IOW('t', 103, struct winsize) 	/* set window size */
#define	TIOCUCNTL	_IOW('t', 102, int)	/* pty: set/clr usr cntl mode */
#define TIOCMIWAIT	_IOW('t', 100, int)	/* wait for modem stat change */
/* SLIP (Serial Line IP) ioctl's */
#define	SLIOCGUNIT	_IOR('t', 101, int)	/* get slip unit number */
#define SLIOCSFLAGS     _IOW('t', 89, int)      /* set configuration flags */
#define SLIOCGFLAGS     _IOR('t', 90, int)      /* get configuration flags */
#define SLIOCSATTACH    _IOWR('t', 91, int)	/* Attach slip i.f. to tty  */
#define		UIOCCMD(n)	_IO('u', n)		/* usr cntl op "n" */

#define	OTTYDISC	0		/* old, v7 std tty driver */
#define	NETLDISC	1		/* line discip for berk net */
#define	NTTYDISC	2		/* new tty discipline */
#define	TABLDISC	3		/* tablet discipline */
#define	SLIPDISC	4		/* serial IP discipline */

#define	FIOCLEX		_IO('f', 1)		/* set close on exec    */
#define	FIONCLEX	_IO('f', 2)		/* clear close on exec  */
/* another local */

#define	FIONREAD	_IOR('f', 127, int)	/* get # bytes to read */
#define	FIONBIO		_IOW('f', 126, int)	/* set/clear non-blocking i/o */
#define	FIOASYNC	_IOW('f', 125, int)	/* set/clear async i/o */

#define	FIOSETOWN	_IOW('f', 124, int)	/* set owner */
#define	FIOGETOWN	_IOR('f', 123, int)	/* get owner */
#define	FIOASYNCQX	_IOW('f', 122, int)	/* set/clear async queueing */

/* socket i/o controls */
#define	SIOCSHIWAT	_IOW('s',  0, int)		/* set high watermark */
#define	SIOCGHIWAT	_IOR('s',  1, int)		/* get high watermark */
#define	SIOCSLOWAT	_IOW('s',  2, int)		/* set low watermark */
#define	SIOCGLOWAT	_IOR('s',  3, int)		/* get low watermark */
#define	SIOCATMARK	_IOR('s',  7, int)		/* at oob mark? */
#define	SIOCSPGRP	_IOW('s',  8, int)		/* set process group */
#define	SIOCGPGRP	_IOR('s',  9, int)		/* get process group */

#define	SIOCADDRT	(int)_IOW('r', 10, struct ortentry)	/* add route */
#define	SIOCDELRT	(int)_IOW('r', 11, struct ortentry)	/* delete route */

#define	SIOCSIFADDR	(int)_IOW('i', 12, struct oifreq)	/* set ifnet address */
#define	OSIOCGIFADDR	(int)_IOWR('i',13, struct oifreq)	/* get ifnet address */
#define	SIOCGIFADDR	(int)_IOWR('i',33, struct oifreq)	/* get ifnet address */
#define	SIOCGIFADDRS	(int)_IO('i',140)	/* get ifnet addresses for an if*/
#define	SIOCSIFDSTADDR	(int)_IOW('i', 14, struct oifreq)	/* set p-p address */
#define	OSIOCGIFDSTADDR	(int)_IOWR('i',15, struct oifreq)	/* get p-p address */
#define	SIOCGIFDSTADDR	(int)_IOWR('i',34, struct oifreq)	/* get p-p address */
#define	SIOCSIFFLAGS	(int)_IOW('i', 16, struct oifreq)	/* set ifnet flags */
#define	SIOCGIFFLAGS	(int)_IOWR('i',17, struct oifreq)	/* get ifnet flags */
#define	OSIOCGIFBRDADDR	(int)_IOWR('i',18, struct oifreq)	/* get broadcast addr */
#define	SIOCGIFBRDADDR	(int)_IOWR('i',35, struct oifreq)	/* get broadcast addr */
#define	SIOCSIFBRDADDR	(int)_IOW('i',19, struct oifreq)	/* set broadcast addr */
#define	OSIOCGIFCONF	(int)_IOWR('i',20, struct ifconf)	/* get ifnet list */
#define	CSIOCGIFCONF	(int)_IOWR('i',36, struct ifconf)	/* get ifnet list */
#define	SIOCGIFCONF	(int)_IOWR('i',69, struct ifconf)	/* get ifnet list */
#define	OSIOCGIFNETMASK	(int)_IOWR('i',21, struct oifreq)	/* get net addr mask */
#define	SIOCGIFNETMASK	(int)_IOWR('i',37, struct oifreq)	/* get net addr mask */
#define	SIOCSIFNETMASK	(int)_IOW('i',22, struct oifreq)	/* set net addr mask */
#define	SIOCGIFMETRIC	(int)_IOWR('i',23, struct oifreq)	/* get IF metric */
#define	SIOCSIFMETRIC	(int)_IOW('i',24, struct oifreq)	/* set IF metric */
#define	SIOCDIFADDR	(int)_IOW('i',25, struct oifreq)	/* delete IF addr */
#define	SIOCAIFADDR	(int)_IOW('i',26, struct ifaliasreq)	/* add/chg IF alias */
#define	SIOCSIFSUBCHAN	(int)_IOW('i',27, struct oifreq)	/* set subchannel adr.*/
#define SIOCSIFNETDUMP  (int)_IOW('i',28, struct oifreq)        /* set netdump fastwrt*/

#define SIOUPDROUTE     (int)_IOW('i',29, struct ifaliasreq)    /* Update Routing table */
#define	SIOCSARP	(int)_IOW('i', 30, struct arpreq)	/* set arp entry */
#define	OSIOCGARP	(int)_IOWR('i',31, struct arpreq)	/* get arp entry */
#define	SIOCGARP	(int)_IOWR('i',38, struct arpreq)	/* get arp entry */
#define	SIOCDARP	(int)_IOW('i', 32, struct arpreq)	/* delete arp entry */

#define	SIOCSIFOPTIONS	(int)_IOW('i', 41, struct oifreq)	/* set ifnet options */
#define	SIOCGIFOPTIONS	(int)_IOWR('i',42, struct oifreq)	/* get ifnet options */
#define	SIOCADDMULTI	(int)_IOW('i', 49, struct ifreq)	/* add multicast addr */
#define	SIOCDELMULTI	(int)_IOW('i', 50, struct ifreq)	/* del multicast addr */
#define	SIOCGETVIFCNT	(int)_IOWR('u', 51, struct sioc_vif_req)/* vif pkt cnt */
#define	SIOCGETSGCNT	(int)_IOWR('u', 52, struct sioc_sg_req) /* s,g pkt cnt */

#define	SIOCADDNETID	(int)_IOW('i',87, struct oifreq)	/* set netids */
#define	SIOCSIFMTU	(int)_IOW('i',88, struct oifreq)	/* set mtu */
#define	SIOCGIFMTU	(int)_IOWR('i',86, struct oifreq)	/* get mtu */

#define SIOCSNETOPT     (int)_IOW('i', 90, struct optreq) /* set network option */
#define SIOCGNETOPT     (int)_IOWR('i', 91, struct optreq) /* get network option */
#define SIOCDNETOPT     (int)_IOWR('i', 128, struct optreq) /* set default */
#define SIOCGNETOPT1	(int)_IOWR('i', 129, struct optreq1) /* get network option */
#define SIOCGLOADF      (int)_IOWR('i', 130, int) /* get flag: if loadtime passed */
#define SIOCSLOADF      (int)_IOWR('i', 131, int) /* set flag: if loadtime passed */
#define SIOCGTUNEPHASE	(int)_IOWR('i', 138, int) /* get tuning_phase */

#define	SIOCSX25XLATE	(int)_IOW('i', 99, struct oifreq)	/* set xlate tab */
#define	SIOCGX25XLATE	(int)_IOWR('i',100, struct oifreq)	/* get xlate tab */
#define	SIOCDX25XLATE	(int)_IOW('i', 101, struct oifreq)	/* delete xlate tab */

#define SIOCIFDETACH	(int)_IOW('i', 102, struct ifreq)	/* detach an ifnet */
#define SIOCIFATTACH	(int)_IOW('i', 103, struct ifreq)	/* attach an ifnet */

#define	SIOCGNMTUS	(int)_IO('i',110) /* get NMTUs */
#define	SIOCGETMTUS	(int)_IO('i',111) /* get common_mtus */
#define	SIOCADDMTU	(int)_IOW('i',112, int) /* add mtu  */
#define	SIOCDELMTU	(int)_IOW('i',113, int) /* delete mtu */

#define SIOCGIFGIDLIST  (int)_IO('i', 104)                   /* get gidlist */
#define SIOCSIFGIDLIST  (int)_IO('i', 105)                   /* set gidlist */

#define SIOCGSIZIFCONF  (int)_IOR('i', 106, int) /* get size for SIOCGIFCONF */

#define SIOCIF_ATM_UBR      	(int)_IOW('i',120,struct ifreq)  /* set ubr rate */
#define SIOCIF_ATM_SNMPARP      (int)_IOW('i',121,struct ifreq)  /* atm snmp arp */
#define SIOCIF_ATM_IDLE         (int)_IOW('i',122,struct ifreq)  /* set idle time */
#define SIOCIF_ATM_DUMPARP      (int)_IOW('i',123,struct ifreq)  /* atm dump arp */
#define SIOCIF_ATM_SVC		(int)_IOW('i',124,struct ifreq)  /* atmif init */
#define SIOCIF_ATM_DARP		(int)_IOW('i',125,struct ifreq)  /* del atmarp */
#define SIOCIF_ATM_GARP		(int)_IOW('i',126,struct ifreq)  /* get atmarp */
#define SIOCIF_ATM_SARP		(int)_IOW('i',127,struct ifreq)  /* set atmarp */

/* For IP over Infiniband */

#define SIOCIF_IB_DUMP_ARP      (int)_IOW('i',128,struct ifreq) /* ib dump arp */
#define SIOCIF_IB_DEL_ARP       (int)_IOW('i',129,struct ifreq) /* if_ib del  ibarp */
#define SIOCIF_IB_GET_ARP       (int)_IOW('i',130,struct ifreq) /* get ibarp */
#define SIOCIF_IB_SET_ARP       (int)_IOW('i',131,struct ifreq) /* set ibarp */
#define SIOCIF_IB_SET_PKEY      (int)_IOW('i',132,struct ifreq) /* set ib port  pkey value */
#define SIOCIFGETPKEY           (int)_IOW('i',101,struct ifreq) /* retrieve PKEY */
#define SIOCIF_IB_SET_PORT      (int)_IOW('i',133,struct ifreq) /* set ib_port  */
#define SIOCIF_IB_SET_QSIZE     (int)_IOW('i',134,struct ifreq) /* set ib qsize  */
#define SIOCIF_IB_RESIZE_CQ     (int)_IOW('i',135,struct ifreq) /* set resize IB CQ  */
#define SIOCIF_IB_ARP_TIMER     (int)_IOW('i',136,struct ifreq) /* set complete ARP expiration in minutes */
#define SIOCIF_IB_ARP_INCOMP    (int)_IOW('i',137,struct ifreq) /* set incomplete ARP expiration in minutes */
#define SIOCIF_IB_SET_QKEY      (int)_IOW('i',138,struct ifreq) /* set QKEY  value */
#define SIOCIF_IB_GET_INFO      (int)_IOWR('i',139,struct ifibreq) /* get IPoIB interface info  */
#define SIOCIF_IB_GET_STATS     (int)_IOWR('i',142,struct ifreq) /* get IPoIB interface stats  */
#define SIOCIF_IB_RESET_STATS   (int)_IOWR('i',143,struct ifreq) /* clear IPoIB interface stats  */
#define SIOCIF_IB_DEL_PINFO     (int)_IOWR('i',144,struct ifreq) /* clears the  IPoIB path information for IPv6  */
#define SIOCIF_IB_CLEAR_PINFO   (int)_IOWR('i',145,struct ifreq) /* deletes IPoIB path information for IPv6 */

#define	SIOCGISNO	(int)_IOWR('i',107, struct oifreq)	/* get IF network options */
#define	SIOCSISNO 	(int)_IOW('i', 108, struct oifreq)	/* set IF network options */
#define SIOCGIFBAUDRATE (int)_IOWR('i', 109, struct oifreq)     /* get ifnet's if_baudrate */

#define SIOCADDIFVIPA   (int)_IO('i',66)       /* specify interfaces that should use this vipa */
#define SIOCDELIFVIPA   (int)_IO('i',67)       /* unconfigure interfaces using this vipa       */
#define SIOCLISTIFVIPA  (int)_IO('i',68)       /* list interfaces using this vipa              */

#ifdef _NO_PROTO

int stty();
int gtty();

#else /* _NO_PROTO */

int stty(int fd, struct sgttyb *sg);
int gtty(int fd, struct sgttyb *sg);

#endif /* _NO_PROTO */

#endif  /* _IOCTL_ */

#ifdef __cplusplus
}
#endif

#ifdef _IA64
/* add support for UDI GIO mapper ioctl as required by UDI spec */
/* not that UDI is only supported on IA64 at this time */
#define GIOMAP_IOCTL(x) (int)(((int)'G'<<24) | (x))

#define UDI_GIO_DATA_XFER       GIOMAP_IOCTL(1)
#endif /* _IA64 */

#endif	/* _H_IOCTL */
