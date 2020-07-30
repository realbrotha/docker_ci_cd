/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/syslog.h 1.6.2.4                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)39       1.6.2.4  src/bos/kernel/sys/syslog.h, sockinc, bos53D, d2004_51B9 12/8/04 15:24:26 */
#ifdef _POWER_PROLOG_
/*
 *   COMPONENT_NAME: SOCKINC
 *
 *   FUNCTIONS: LOG_MASK, LOG_UPTO
 *
 *   ORIGINS: 26,27,71
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#endif /* _POWER_PROLOG_ */

/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef	_H_SYS_SYSLOG
#define _H_SYS_SYSLOG

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if _XOPEN_SOURCE_EXTENDED==1
/*
 *  Option flags for openlog.
 *
 *	LOG_ODELAY no longer does anything; LOG_NDELAY is the
 *	inverse of what it used to be.
 */

#define	LOG_PID		0x01	/* log the pid with each message */
#define	LOG_CONS	0x02	/* log on the console if errors in sending */
#define	LOG_ODELAY	0x04	/* delay open until syslog() is called */
#define LOG_NDELAY	0x08	/* don't delay open */
#define LOG_NOWAIT	0x10	/* if forking to log on console, don't wait() */

/*
 *  Facility codes
 */

#define LOG_KERN	(0<<3)	/* kernel messages */
#define LOG_USER	(1<<3)	/* random user-level messages */
#define LOG_MAIL	(2<<3)	/* mail system */
#define LOG_DAEMON	(3<<3)	/* system daemons */
#define LOG_AUTH	(4<<3)	/* security/authorization messages */
#define LOG_SYSLOG	(5<<3)	/* messages generated internally by syslogd */
#define LOG_LPR		(6<<3)	/* line printer subsystem */
#define LOG_NEWS	(7<<3)	/* news subsystem */
#define LOG_UUCP	(8<<3)	/* uucp subsystem */
#define LOG_CRON	(9<<3)	/* clock daemon */
	/* other codes through 15 reserved for system use */
#define LOG_LOCAL0	(16<<3)	/* reserved for local use */
#define LOG_LOCAL1	(17<<3)	/* reserved for local use */
#define LOG_LOCAL2	(18<<3)	/* reserved for local use */
#define LOG_LOCAL3	(19<<3)	/* reserved for local use */
#define LOG_LOCAL4	(20<<3)	/* reserved for local use */
#define LOG_LOCAL5	(21<<3)	/* reserved for local use */
#define LOG_LOCAL6	(22<<3)	/* reserved for local use */
#define LOG_LOCAL7	(23<<3)	/* reserved for local use */

/*
 * arguments to setlogmask.
 */
#define	LOG_MASK(pri)	(1 << (pri))		/* mask for one priority */
#if defined(_ALL_SOURCE) || (_XOPEN_SOURCE != 500)
#define	LOG_UPTO(pri)	((1 << ((pri)+1)) - 1)	/* all priorities through pri */
#endif

/*
 *  Priorities (these are ordered)
 */

#define LOG_EMERG	0	/* system is unusable */
#define LOG_ALERT	1	/* action must be taken immediately */
#define LOG_CRIT	2	/* critical conditions */
#define LOG_ERR		3	/* error conditions */
#define LOG_WARNING	4	/* warning conditions */
#define LOG_NOTICE	5	/* normal but signification condition */
#define LOG_INFO	6	/* informational */
#define LOG_DEBUG	7	/* debug-level messages */

#ifdef _NO_PROTO
void	closelog();
void	openlog();
int	setlogmask();
void	syslog();
#else /* _NO_PROTO */
void	closelog(void);
void	openlog(const char *, int, int);
int	setlogmask(int);
void	syslog(int, const char *, ...);
#endif /* _NO_PROTO */

#endif /* _XOPEN_SOURCE_EXTENDED */

#ifdef _ALL_SOURCE
#define LOG_NFACILITIES	24	/* maximum number of facilities */
#define LOG_FACMASK	0x03f8	/* mask to extract facility part */

#define LOG_PRIMASK	0x0007	/* mask to extract priority part (internal) */

/*
 * Additional openlog flag.
 * Log to stderr as well.
 */
#define LOG_PERROR	0x20

/*
 * Additional facilities.
 */
#define LOG_AUTHPRIV	(10<<3) /* security/authorization messages (private) */

/* for thread safe _r functions */

#ifdef _THREAD_SAFE
#include <sys/types.h>
#include <sys/socket.h>
struct syslog_data {
	int log_file;
	int log_stat;
	char *log_tag;
	int log_mask;
	int log_facility;
	struct sockaddr syslog_addr;
};
#define SYSLOG_DATA_INIT {-1, 0, "syslog", 0xff, LOG_USER}
#endif /* _THREAD_SAFE */

#ifdef _NO_PROTO

#ifdef _THREAD_SAFE
extern int openlog_r();
extern int syslog_r();
extern void closelog_r();
extern int setlogmask_r();
#endif /* _THREAD_SAFE */

#else /* _NO_PROTO */

#ifdef _THREAD_SAFE
extern int openlog_r(const char *ident, int logstat, int logfac, struct syslog_data *SysLogData);
extern int syslog_r(int pri, struct syslog_data *SysLogData, const char *fmt, ...);
extern void closelog_r(struct syslog_data *SysLogData);
extern int setlogmask_r(int pmask, struct syslog_data *SysLogData);
#endif /* _THREAD_SAFE */

#endif	/* _NO_PROTO */
#endif  /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif
#endif	/* _H_SYS_SYSLOG */
