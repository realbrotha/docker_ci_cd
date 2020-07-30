/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/utmp.h 1.11.1.19                            */
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
/* @(#)87  1.11.1.19  src/bos/usr/include/utmp.h, libcadm, bos530 2/27/04 15:37:47 */
/*
 *   COMPONENT_NAME: CMDOPER
 *
 *   FUNCTIONS: UTMP_DATA_INIT
 *
 *   ORIGINS: 27,71
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1989,1994
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC. 
 * ALL RIGHTS RESERVED 
 */


#ifndef _H_UTMP
#define _H_UTMP

/*	<sys/types.h> must be included.					*/

#ifndef _H_UTMPX
#define	UTMP_FILE	"/etc/utmp"
#define WTMP_FILE       "/var/adm/wtmp"
#define ILOG_FILE       "/etc/security/failedlogin"
#define	ut_name	ut_user
#endif /* _H_UTMPX */

struct utmp
  {
	char ut_user[256] ;		/* User login name */
	char ut_id[14] ;		/* /etc/inittab id */
	char ut_line[64] ;		/* device name (console, lnxx) */
	pid_t ut_pid ;			/* process id */
	short ut_type ; 		/* type of entry */
#if !defined(__64BIT__) && !defined(__ia64)
        int __time_t_space;             /* for 32vs64-bit time_t PPC */
#endif
	time_t ut_time ;		/* time entry was made */
#if !defined(__64BIT__) && defined(__ia64)
        int __time_t_space;             /* for 32vs64-bit time_t IA64 */
#endif
	struct exit_status
	  {
	    short e_termination ;	/* Process termination status */
	    short e_exit ;		/* Process exit status */
	  }
	ut_exit ;			/* The exit status of a process
					 * marked as DEAD_PROCESS.
					 */
	char ut_host[256] ;		/* host name */
	int __dbl_word_pad;		/* for double word alignment */
	int __reservedA[2];
	int __reservedV[6];
  } ;

/*	Definitions for ut_type						*/

#define	EMPTY		0
#define	RUN_LVL		1
#define	BOOT_TIME	2
#define	OLD_TIME	3
#define	NEW_TIME	4
#define	INIT_PROCESS	5	/* Process spawned by "init" */
#define	LOGIN_PROCESS	6	/* A "getty" process waiting for login */
#define	USER_PROCESS	7	/* A user process */
#define	DEAD_PROCESS	8
#define	ACCOUNTING	9

#define	UTMAXTYPE	ACCOUNTING	/* Largest legal value of ut_type */

/*	Special strings or formats used in the "ut_line" field when	*/
/*	accounting for something other than a process.			*/
/*	No string for the ut_line field can be more than 63 chars +	*/
/*	a NULL in length.						*/

#define RUNLVL_MSG      "run-level %c"
#define	BOOT_MSG	"system boot"
#define	OTIME_MSG	"old time"
#define	NTIME_MSG	"new time"

#ifdef _THREAD_SAFE
#ifndef _UTMPX_H
#define utmp_data _utmp_data
#endif /*_UTMPX_H*/

struct _utmp_data {
	int		ut_fd;
	long		loc_utmp;
	struct utmp 	ubuf;
	char 		*name;
};
#define UTMP_DATA_INIT(__s) (__s.ut_fd=-1, __s.name=UTMP_FILE)
#endif /* _THREAD_SAFE */

#ifdef	_NO_PROTO
extern void endutent();
extern struct utmp *getutent();
extern struct utmp *getutid();
extern struct utmp *getutline();
extern struct utmp *pututline();
extern void setutent();
extern int utmpname();
extern void updwtmp();

#ifdef _THREAD_SAFE
extern  void    endutent_r();
extern	int	getutent_r();
extern	int	getutid_r();
extern	int	getutline_r();
extern	int	pututline_r();
extern  void    setutent_r();
/* See comments in stdlib.h on _AIX32_THREADS */
#if _AIX32_THREADS
extern  void    utmpname_r();
#else	/* POSIX 1003.4a Draft 7 prototype */
extern  int     utmpname_r();
#endif /* _AIX32_THREADS */
#endif /* _THREAD_SAFE */

#else	/* _NO_PROTO */
extern void endutent(void);
extern struct utmp *getutent(void);
extern struct utmp *getutid(const struct utmp *);
extern struct utmp *getutline(const struct utmp *);
extern struct utmp *pututline(const struct utmp *);
extern void setutent(void);
extern int  utmpname(char *);
extern void updwtmp(const char *, const struct utmp *);

#ifdef _THREAD_SAFE
extern	int	getutent_r(struct utmp **utmp, struct _utmp_data *utmp_data);
extern	int	getutid_r(const struct utmp *utent, struct utmp  **utmp, 
			  struct _utmp_data *utmp_data);
extern	int	getutline_r(const struct utmp *utent, struct utmp **utmp, 
			    struct _utmp_data *utmp_data);
extern	int	pututline_r(const struct utmp *utent, 
			     struct _utmp_data *utmp_data);
extern  void    setutent_r(struct _utmp_data *utmp_data);
extern  void    endutent_r(struct _utmp_data *utmp_data);
/* See comments in stdlib.h on _AIX32_THREADS */
#if _AIX32_THREADS
extern  void    utmpname_r(char *newfile, struct _utmp_data *utmp_data);
#else	/* POSIX 1003.4a Draft 7 prototype */
extern  int     utmpname_r(char *newfile, struct _utmp_data *utmp_data);
#endif /* _AIX32_THREADS */
#endif /* _THREAD_SAFE */

#endif	/* _NO_PROTO */

#endif /* _H_UTMP */
