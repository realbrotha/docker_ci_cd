/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/utmpx.h 1.16                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1995,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)49  1.16  src/bos/usr/include/utmpx.h, libcadm, bos530 2/27/04 15:37:48 */
/*
 *   COMPONENT_NAME: CMDOPER
 *
 *   FUNCTIONS: UTMP_DATA_INIT
 *
 *   ORIGINS: 27,71
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1989,1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */


#ifndef _H_UTMPX
#define _H_UTMPX

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#if _XOPEN_SOURCE_EXTENDED==1

#include <sys/time.h>

#ifdef _ALL_SOURCE
#ifndef _H_UTMP
#define	UTMP_FILE	"/etc/utmp"
#define WTMP_FILE       "/var/adm/wtmp"
#define ILOG_FILE       "/etc/security/failedlogin"
#define	ut_name	ut_user
#endif /* _H_UTMP */
#endif /* _ALL_SOURCE */

struct utmpx
  {
	char ut_user[256] ;		/* User login name */
	char ut_id[14] ;		/* /etc/inittab id */
	char ut_line[64] ;		/* device name (console, lnxx) */
	pid_t ut_pid ;			/* process id */
	short ut_type ; 		/* type of entry */
#ifndef __64BIT__
	int __timeval_space;		/* for 32vs64-bit timeval struct */
#endif
        struct timeval ut_tv;           /* time entry was made */
	char ut_host[256];		/* host id */
	int __dbl_word_pad;		/* for double word alignment */
	int __reservedA[2];
	int __reservedV[6];
  } ;

/*	Definitions for ut_type						*/

#define	EMPTY		0
#ifdef _ALL_SOURCE 
#define	RUN_LVL		1
#endif
#define	BOOT_TIME	2
#define	OLD_TIME	3
#define	NEW_TIME	4
#define	INIT_PROCESS	5	/* Process spawned by "init" */
#define	LOGIN_PROCESS	6	/* A "getty" process waiting for login */
#define	USER_PROCESS	7	/* A user process */
#define	DEAD_PROCESS	8

#ifdef _ALL_SOURCE 
#define	ACCOUNTING	9

#define	UTMAXTYPE	ACCOUNTING	/* Largest legal value of ut_type */

/*	Special strings or formats used in the "ut_line" field when	*/
/*	accounting for something other than a process.			*/
/*	No string for the ut_line field can be more than 11 chars +	*/
/*	a NULL in length.						*/

#define RUNLVL_MSG      "run-level %c"
#define	BOOT_MSG	"system boot"
#define	OTIME_MSG	"old time"
#define	NTIME_MSG	"new time"

#ifdef _THREAD_SAFE
#ifdef _H_UTMP
#undef utmp_data
#endif /*_H_UTMP*/
#define utmp_data utmpx_data

struct utmpx_data {
	int		ut_fd;
	long		loc_utmp;
	struct utmpx 	ubuf;
	char 		*name;
};
#define UTMP_DATA_INIT(__s) (__s.ut_fd=-1, __s.name=UTMP_FILE)
#endif /* _THREAD_SAFE */
#endif /* _ALL_SOURCE */

#ifdef	_NO_PROTO
extern void endutxent();
extern struct utmpx *getutxent();
extern struct utmpx *getutxid();
extern struct utmpx *getutxline();
extern struct utmpx *pututxline();
extern void setutxent();

#if defined(_THREAD_SAFE) && defined(_ALL_SOURCE)
extern  void    endutxent_r();
extern	int	getutxent_r();
extern	int	getutxid_r();
extern	int	getutxline_r();
extern	int	pututxline_r();
extern  void    setutxent_r();
/* See comments in stdlib.h on _AIX32_THREADS */
#endif /* _THREAD_SAFE */

#else	/* _NO_PROTO */
extern void endutxent(void);
extern struct utmpx *getutxent(void);
extern struct utmpx *getutxid(const struct utmpx *);
extern struct utmpx *getutxline(const struct utmpx *);
extern struct utmpx *pututxline(const struct utmpx *);
extern void setutxent(void);

#if defined(_THREAD_SAFE) && defined(_ALL_SOURCE)
extern	int	getutxent_r(struct utmpx **utmpx, struct utmpx_data *utmp_data);
extern	int	getutxid_r(const struct utmpx *utent, struct utmpx  **utmpx, 
			  struct utmpx_data *utmp_data);
extern	int	getutxline_r(const struct utmpx *utent, struct utmpx **utmpx, 
			    struct utmpx_data *utmp_data);
extern	int	pututxline_r(const struct utmpx *utent, 
			     struct utmpx_data *utmp_data);
extern  void    setutxent_r(struct utmpx_data *utmp_data);
extern  void    endutxent_r(struct utmpx_data *utmp_data);
/* See comments in stdlib.h on _AIX32_THREADS */
#endif /* _THREAD_SAFE */

#endif	/* _NO_PROTO */

#endif  /* _XOPEN_SOURCE_EXTENDED */

#endif /* _H_UTMPX */
