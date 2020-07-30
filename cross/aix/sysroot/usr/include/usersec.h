/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/usr/include/usersec.h 1.20.9.2                          */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1985,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)65	1.20.9.2  src/bos/usr/include/usersec.h, cmdsauth, bos53Q, q2008_22B4 5/19/08 12:45:51 */
/*
 * COMPONENT_NAME: CMDSAUTH
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
 
#ifndef _H_USERSEC    
#define _H_USERSEC

#include <sys/limits.h>
#include <sys/types.h>
#include <userpw.h>	/* struct userpw */
#include <pwd.h>	/* struct passwd */
#include <grp.h>	/* struct group */
#include <stdio.h>
#include <stddef.h>	/* wchar_t */

/*****************************************************/
/* The (dbattr_t) type provides the ability to fully */
/* describe an attribute in terms of its name, type, */
/* and location to the attribute storage  and        */
/* retrieval functions.                              */
/*****************************************************/

typedef struct {
	char   *attr_name;
	char   *attr_domain;
	int    attr_idx;
	int    attr_type;
	int    attr_flag;
	union {
		char      *au_char;
		int32_t   au_int;
		long      au_long;
		int64_t   au_llong;
	} attr_un;
} dbattr_t;

#ifdef  _NO_PROTO
	/* set and get user credentials */
	extern  int	setpcred ();
	extern  char 	**getpcred ();

	/* set and get process environment */
	extern  int	setpenv ();
	extern  char	**getpenv ();

	/* user database */
	extern	int	setuserdb ();
	extern	int	enduserdb ();

	/* set and  get user attributes */
	extern  int	setuserattr ();
	extern	int	getuserattr ();
	extern	int	getuserattrs ();
	extern	int	putuserattr ();
	extern	int	putuserattrs ();
	extern	int	enduserattr ();
	extern	char	*IDtouser ();

	/* set and  get group attributes */
	extern  int	setgroupattr ();
	extern	int	getgroupattr ();
	extern	int	getgroupattrs ();
	extern	int	putgroupattr ();
	extern	int	putgroupattrs ();
	extern  int	endgroupattr ();
	extern	char	*IDtogroup ();

	extern	int	putportattr ();
	extern	int	getportattr ();
	extern	int	getconfattr ();
	extern	int	getconfattrs ();
	extern	int	putconfattr ();
	extern	int	putconfattrs ();

	extern 	char	*newpass();
	extern	int	chpass();
	extern	int	passwdexpired();

	/* user authentication */
	extern	int	ckuseracct();

	/* next user and group name */
	extern	char	*nextuser();
	extern	char	*nextgroup();

	/* authorizations */
	extern	char	*GetUserAuths ();
	extern	int	MatchAllAuths ();
	extern	int	MatchAllAuthsList ();
	extern	int	MatchAnyAuths ();
	extern	int	MatchAnyAuthsList ();

	/* screens */
	extern	char	*GetUserScreens ();
	extern	char	*SMITScreenAccess ();
	extern	int	getusraclattr ();
	extern	int	putusraclattr ();
	extern	int	getgrpaclattr ();
	extern	int	putgrpaclattr ();
	extern	int	setacldb ();
	extern	int	endacldb ();
	extern	char *nextusracl();
	extern	char *nextgrpacl();

	/* roles */
	extern	int	setroledb ();
	extern	int	endroledb ();
	extern	char	*nextrole ();
	extern	int	getroleattr ();
	extern	int	putroleattr ();
	extern	int	endroleattr ();

	/* generic security attributes */
	extern	int	setsecdb();
	extern	int	endsecdb();

	/* audithost */
	extern	char	*nexthost();
	extern	char	*IDtohost();
	extern	char	*hosttoID();
	extern	int	getaudithostattr();
	extern	int	putaudithostattr();

	extern	int	authenticate();
	extern	int	loginfailed();
	extern	int	loginsuccess();
	extern	int	loginrestrictions();

#else	/* _NO_PROTO */
	/* set and get user credentials */
	extern  int	setpcred (char *, char **);
	extern  char 	**getpcred (int);

	/* set and get process environment */
	extern  int	setpenv (char *, int, char **, char *);
	extern  char	**getpenv (int);

	/* user database */
	extern	int	setuserdb (int);
	extern	int	enduserdb (void);

	/* set and  get user attributes */
	extern	int	setuserattr (int);
	extern	int	getuserattr (char *, char *, void *, int);
	extern	int	getuserattrs (char *, dbattr_t *, int);
	extern	int	putuserattr (char *, char *, void *, int);
	extern	int	putuserattrs (char *, dbattr_t *, int);
	extern	int	enduserattr ();
	extern	char	*IDtouser (uid_t);

	/* set and  get group attributes */
	extern	int	setgroupattr (int);
	extern	int	getgroupattr (char *, char *, void *, int);
	extern	int	getgroupattrs (char *, dbattr_t *, int);
	extern	int	putgroupattr (char *, char *, void *, int);
	extern	int	putgroupattrs (char *, dbattr_t *, int);
	extern	int	endgroupattr ();
	extern	char	*IDtogroup (uid_t);

	extern	int	putportattr (char *,char *,void *,int);
	extern	int	getportattr (char *,char *,void *,int);
	extern	int	getconfattr (char *, char *, void *, int);
	extern	int	getconfattrs (char *, dbattr_t *, int);
	extern	int	putconfattr (char *, char *, void *, int);
	extern	int	putconfattrs (char *, dbattr_t *, int);

	extern 	char	*newpass    (struct userpw *);
	extern	int	chpass(char *, char *, int *, char **);
	extern	int	passwdexpired(char *, char **);

	/* user authentication */
	extern	int	ckuseracct (char *, int, char *);

	/* next user and group name */
	extern	char	*nextuser (int, int);
	extern	char	*nextgroup (int, int);

	/* authorizations */
	extern	char	*GetUserAuths (void);
	extern	int	MatchAllAuths (char *);
	extern	int	MatchAllAuthsList (char *, char *);
	extern	int	MatchAnyAuths (char *);
	extern	int	MatchAnyAuthsList (char *, char *);

	/* screens */
	extern	char	*GetUserScreens (void);
	extern	int	SMITScreenAccess (char *, char *);
	extern	int	getusraclattr (char *, char *, void *, int);
	extern	int	putusraclattr (char *, char *, void *, int);
	extern	int	getgrpaclattr (char *, char *, void *, int);
	extern	int	putgrpaclattr (char *, char *, void *, int);
	extern	int	setacldb (int);
	extern	int	endacldb (void);
	extern  char *nextusracl(void);
	extern  char *nextgrpacl(void);

	/* roles */
	extern	int	setroledb (int);
	extern	int	endroledb (void);
	extern	char	*nextrole (void);
	extern	int	getroleattr (char *, char *, void *, int);
	extern	int	putroleattr (char *, char *, void *, int);
	extern	int	endroleattr (void);

	/* generic security attributes */
	extern	int	setsecdb(int);
	extern	int	endsecdb(void);

	/* audithost */
	extern	char	*nexthost(void);
	extern	char	*IDtohost(char *);
	extern	char	*hosttoID(char *, int *);
	extern	int	getaudithostattr(char *, char *, void *, int);
	extern	int	putaudithostattr(char *, char *, void *, int);

	extern	int	authenticate(char *, char *, int *, char **);
	extern	int	loginfailed(char *, char *, char *, int);
	extern	int	loginsuccess(char *, char *, char *, char **);
	extern	int	loginrestrictions(char *, int, char *, char **);

#endif	/* _NO_PROTO */

/* modes for set attribute routines */
#define S_READ		0x1
#define S_WRITE		0x2

/* attribute types (these are indexes into xtab[].) */
#define	SEC_CHAR	1
#define SEC_INT		2
#define SEC_LIST	3
#define SEC_BOOL	4

/* delete the entry */
#define SEC_DELETE	5

/* Commit the changes to hard files */
#define SEC_COMMIT	6

/* create a new entry */
#define SEC_NEW		7

#define SEC_TCBLLONG	8	/* internal use only */
#define SEC_LONG        9       /* future use */
#define SEC_LLONG	10	/* future use */

/* Type value of attribute that is not implemented */
#define NOT_IMPLEM	-1	/* Not implemented */

/*
 * The user attributes names 
 */
#define	S_ID		"id"		/* SEC_INT - user, group id */
#define	S_PWD		"password"	/* SEC_CHAR - user password */
#define	S_PGRP		"pgrp"		/* SEC_CHAR - primary group name */
#define S_PGID		"pgid"		/* SEC_INT - primary group gid */
#define S_GROUPS	"groups"	/* SEC_LIST - concurrent group list */
#define S_GROUPSIDS	"groupsids"	/* SEC_LIST - concurrent group list by id */
#define S_ADMGROUPS	"admgroups"	/* SEC_LIST - groups for 
					which this user is an administrator */
#define S_PUSERS	"primary"	/* SEC_LIST - primary users of group */
#define	S_USERS		"users"		/* SEC_LIST - the members of a group */
#define S_ADMIN		"admin"		/* SEC_BOOL - administrative group */
#define S_ADMS		"adms"		/* SEC_LIST - group administrators */
#define S_PACCT		"pacct"		/* NOT_IMPLEM - primary account */
#define S_ACCTS		"accts"		/* NOT_IMPLEM - this users accounts */
#define S_ADMACCTS	"admacct"	/* NOT_IMPLEM - accounts for which 
					this user is an administrator */
#define S_AUDITCLASSES	"auditclasses"	/* SEC_LIST - the users audit classes */
#define S_HOME		"home"		/* SEC_CHAR - home directory */
#define S_SHELL		"shell"		/* SEC_CHAR - the users login shell */
#define S_GECOS		"gecos"		/* SEC_CHAR - user information */
#define S_SYSENV	"sysenv"	/* SEC_LIST - protected environment */
#define S_USRENV	"usrenv"	/* SEC_LIST - public environment */
#define S_LOGINCHK	"login"		/* SEC_BOOL - login permitted or not */
#define S_SUCHK		"su"		/* SEC_BOOL - su permitted or not */
#define S_DAEMONCHK	"daemon"	/* SEC_BOOL - cron or src permitted */
#define S_RLOGINCHK	"rlogin"	/* SEC_BOOL - rlogin or telnet allowed*/
#define S_TELNETCHK	"telnet"	/* SEC_BOOL - rlogin or telnet allowed*/
#define S_ADMCHK	"admchk"	/* SEC_BOOL - force passwd renewal */
#define S_TPATH		"tpath"		/* SEC_CHAR - can be 
					: "nosak", "always", "notsh", or "on" */
#define S_TTYS		"ttys"		/* SEC_LIST - allowed login ttys */
#define S_SUGROUPS	"sugroups"	/* SEC_LIST - groups that can 
						su to this account */
#define S_EXPIRATION	"expires"	/* SEC_CHAR - account expiration */
#define S_AUTH1		"auth1"		/* SEC_LIST - primary authentication */
#define S_AUTH2		"auth2"		/* SEC_LIST - secondary authentication*/
#define S_ULIMIT	"limits"	/* SEC_INT  - ulimit */
#define	S_UFSIZE 	"fsize"		/* SEC_INT  - file size */
#define	S_UCPU   	"cpu"		/* SEC_INT  - cpu usage limit */
#define	S_UDATA 	"data"		/* SEC_INT  - data memory limit */
#define	S_USTACK 	"stack"		/* SEC_INT  - stack memory limit */
#define	S_UCORE 	"core"		/* SEC_INT  - core memory limit */
#define	S_URSS		"rss"		/* SEC_INT  - rss memory limit */
#define	S_UNOFILE	"nofiles"	/* SEC_INT  - file descriptor limit */
#define	S_UFSIZE_HARD 	"fsize_hard"	/* SEC_INT  - hard file size */
#define	S_UCPU_HARD   	"cpu_hard"	/* SEC_INT  - hard cpu usage limit */
#define	S_UDATA_HARD 	"data_hard"	/* SEC_INT  - hard data memory limit */
#define	S_USTACK_HARD 	"stack_hard"	/* SEC_INT  - hard stack memory limit */
#define	S_UCORE_HARD 	"core_hard"	/* SEC_INT  - hard core memory limit */
#define	S_URSS_HARD	"rss_hard"	/* SEC_INT  - hard rss memory limit */
#define	S_UNOFILE_HARD	"nofiles_hard"	/* SEC_INT  - hard file desc limit */
#define	S_UMASK		"umask"		/* SEC_INT  - file creation mask */
#define S_AUTHSYSTEM	"SYSTEM"	/* SEC_CHAR - authentication grammar */
#define S_REGISTRY	"registry"	/* SEC_CHAR - administration domain */
#define S_LOGTIMES	"logintimes"	/* SEC_LIST - valid login times */
#define S_LOCKED	"account_locked"/* SEC_BOOL - is the account locked */
#define S_LOGRETRIES	"loginretries"	/* SEC_INT  - invalid login attempts
					before the account is locked */
#define	S_MINALPHA	"minalpha"	/* SEC_INT - passwd minalpha   */
#define	S_MINOTHER	"minother"	/* SEC_INT - passwd minother   */
#define	S_MINDIFF	"mindiff"	/* SEC_INT - passwd mindiff    */
#define	S_MAXREPEAT	"maxrepeats"	/* SEC_INT - passwd maxrepeats */
#define	S_MINLEN	"minlen"	/* SEC_INT - passwd minlen     */
#define	S_MINAGE	"minage"	/* SEC_INT - passwd minage     */
#define	S_MAXAGE	"maxage"	/* SEC_INT - passwd maxage     */
#define	S_MAXEXPIRED	"maxexpired"	/* SEC_INT - passwd maxexpired */
#define S_HISTEXPIRE    "histexpire"    /* SEC_INT - passwd reuse interval  */
#define S_HISTSIZE      "histsize"      /* SEC_INT - passwd reuse list size */
#define	S_PWDCHECKS	"pwdchecks"	/* SEC_LIST - passwd pwdchecks   */
#define	S_DICTION	"dictionlist"	/* SEC_LIST - passwd dictionlist */
#define	S_PWDWARNTIME	"pwdwarntime"	/* SEC_INT - passwd pwdwarntime */

#define	S_USREXPORT	"dce_export"	/* SEC_BOOL - passwd export protection */
#define	S_GRPEXPORT	"dce_export"	/* SEC_BOOL - group export protection  */


/* attributes set by tsm */
#define	S_LASTTIME	"time_last_login"	
			/* SEC_INT  - time of last successful login */
#define	S_ULASTTIME	"time_last_unsuccessful_login"	
			/* SEC_INT  - time of last unsuccessful login */
#define	S_LASTTTY	"tty_last_login"	
			/* SEC_CHAR  - tty of last successful login */
#define	S_ULASTTTY	"tty_last_unsuccessful_login"	
			/* SEC_CHAR  - tty of last unsuccessful login */
#define	S_LASTHOST	"host_last_login"	
			/* SEC_CHAR  - host name of last successful login */
#define	S_ULASTHOST	"host_last_unsuccessful_login"	
			/* SEC_CHAR  - host name of last unsuccessful login */
#define	S_ULOGCNT	"unsuccessful_login_count"	
			/* SEC_INT  - number of unsuccessful logins */

/*
 * new user attributes name
 */
#define S_MAXULOGS      "maxulogs"      /* SEC_INT - max number of logs per u */
#define S_UACTIVITY     "uactivity"     /* SEC_INT - user timeout activity */
#define S_UTOCOUNT      "utocount"      /* SEC_INT - user timeout count */

/*
 * new mac_user attributes
 */
#define S_LLEVEL        "l_level"       /* SEC_CHAR - low level mac */
#define S_ULEVEL        "u_level"       /* SEC_CHAR - upper level mac */
#define S_DLEVEL        "d_level"       /* SEC_CHAR - default level mac */
#define S_PROMPTMAC     "prompt_mac"    /* SEC_BOOL - prompt mac or not */

/*
 * The port attribute names
 */
#define S_HERALD	"herald"	/* SEC_CHAR - login herald */
#define S_HERALD2	"herald2"	/* SEC_CHAR - login herald2 */
#define S_SAKENABLED	"sak_enabled"	/* SEC_BOOL - sak enabled or not */
#define S_SYNONYM	"synonym"	/* SEC_LIST - synonym ports */
#define S_LOGDISABLE	"logindisable"	/* SEC_INT - invalid login attempts
					before the port is disabled */
#define S_LOGINTERVAL	"logininterval"	/* SEC_INT - time period for port
					disabling */
#define S_LOGREENABLE	"loginreenable"	/* SEC_INT - time period after which
					the port is reenabled */
#define S_LOGDELAY	"logindelay"	/* SEC_INT - delay between invalid
					login attempts */
#define S_LOCKTIME	"locktime"	/* SEC_INT - time the port was locked */
#define S_ULOGTIMES	"unsuccessful_login_times"
					/* SEC_LIST - times when invalid login
					attempts occurred */
#define S_TACTIVITY     "tactivity"     /* SEC_INT - port timeout activity */
#define S_TLOGOUT       "tlogout"       /* SEC_INT - port is to logout */
#define S_PWDPROMPT	"pwdprompt"	/* SEC_CHAR - login password prompt */
#define S_USERNAMEECHO	"usernameecho"	/* SEC_BOOL - echo user name or not */

#define S_PROJECTS	"projects"	/* SEC_LIST - list of projects for users/groups */


/*
 * System attribute names
 */
#define S_LOGTIMEOUT	"logintimeout"	/* SEC_INT - time given to enter a
					password */

/*
 * Role attribute names
 */
#define	S_ROLES		"roles"		/* SEC_LIST - user roles */

/*
 * Audit host names
 */
#define S_CPUID "cpuid"	/* SEC_LIST - audit host id */

/*
 * Authorization attribute names
 */
#define	S_AUTHORIZATIONS "authorizations" /* SEC_LIST - role authorizations */
#define	S_ROLELIST	"rolelist"	/* SEC_LIST - rolelist */
#define	S_VISIBILITY	"visibility"	/* SEC_INT - visibility */
#define	S_SCREENS	"screens"	/* SEC_LIST - screens */
#define	S_MSGCAT	"msgcat"	/* SEC_CHAR - msgcat */
#define	S_MSGNUMBER	"msgnum"	/* SEC_INT - msgnum */
#define	S_FUNCMODE	"funcmode"	/* SEC_CHAR - funcmode */

#define kAuthALL	"ALL"
#define kAuthOFF	"OFF"
#define kScreensALL	"*"
#define S_HOSTSALLOWEDLOGIN  "hostsallowedlogin"  /* SEC_LIST */
#define S_HOSTSDENIEDLOGIN   "hostsdeniedlogin"   /* SEC_LIST */
#define S_RCMDS   "rcmds"   /* SEC_CHAR */


/*
 * for process ENVIRONMENT manipulation: setpenv() and getpenv()
 */
/* setpenv() */
#define	PENV_INIT	0x1		/* initialize (used by tsm) */
#define	PENV_DELTA	0x2		/* modify by adding to process env */
#define	PENV_RESET	0x4		/* reset process environment */
#define PENV_ARGV	0x8		/* command will be in argv format */
#define PENV_KLEEN	0x10		/* indicates running kleenup() */
#define PENV_NOPROF	0x20		/* execute command without profiles */
#define PENV_NOEXEC	0x40		/* initialize environment only */

/* getpenv() */
#define PENV_SYS	0x1		/* indicates environment wanted */
#define PENV_USR	0x2		/* indicates environment wanted */

/* for setpenv() */
#define PENV_USRSTR	"USRENVIRON:"	/* start of environ from environ area */
#define PENV_SYSSTR	"SYSENVIRON:"	/* start of environ from usrinfo area */

/* defines for nextuser() and nextgroup()	*/
#define S_LOCAL		0x01		/* bit mask for 'local' database  */
#define	S_SYSTEM	0x02		/* bit mask for 'system' database */

/* bits for getpcred argument */
#define CRED_RUID	0x2    	/* user's real id */
#define CRED_LUID	0x4 	/* user's login id */
#define CRED_RGID	0x8	/* group id */
#define CRED_ACCT	0x10	/* account id */
#define CRED_AUDIT	0x20	/* audit classes */
#define CRED_RLIMITS	0x40	/* ulimit credentials */
#define CRED_UMASK    	0x80	/* umask credentials */
#define CRED_GROUPS	0x100	/* ids of all groups */
#define CRED_PAG_DATA	0x200	/* pag data */

/* misc */
#define S_NAMELEN 	L_cuserid	/* for compatablity */
#define S_NGROUPS	NGROUPS_MAX	/* max # of concurrent groups set */

/* attribute names */
#define SEC_PASSWD	"spassword"	/* passwd in shadow pwd file */
#define SEC_LASTUP	"lastupdate"
#define SEC_FLAGS	"flags"

/* capability strings */                                                      
#define	S_CAPABILITIES  "capabilities"  /* capability list */           
#define	SCAP_PROPAGATE  "CAP_PROPAGATE" /* propagate capabilities */    
#define	SCAP_PROPOGATE  "CAP_PROPOGATE" /* deprecated spelling -- do not use */
#define	SCAP_NUMA_ATTACH "CAP_NUMA_ATTACH" /* NUMA attachment capability */
#define	SCAP_BYPASS_RAC_VMM "CAP_BYPASS_RAC_VMM" /* bypass VMM limits */
#define	SCAP_EWLM_AGENT	"CAP_EWLM_AGENT" /* eWLM agent capability */
#define	SCAP_ARM_APPLICATION "CAP_ARM_APPLICATION" /* ARM capability */
#define	SCAP_AACCT	"CAP_AACCT"	/* Advanced accounting capability */
#define SCAP_CREDENTIALS "CAP_CREDENTIALS" /* per-thread Credentials */

/* domain building attibutes */
#define  S_AUTHNAME "auth_name"  /* SEC_CHAR - auth name for auth module */
#define  S_AUTHDOMAIN "auth_domain" /* SEC_CHAR - auth domain for auth module */

/* corefile attributes */
#define  S_CORECOMP "core_compress"	/* SEC_CHAR */
#define  S_COREPATH "core_path"		/* SEC_CHAR */
#define  S_COREPNAME "core_pathname"	/* SEC_CHAR */
#define  S_CORENAMING "core_naming"	/* SEC_CHAR */
#define  S_CORENAME "core_name"		/* SEC_CHAR */

/* load module only attributes */
#define	S_HISTLIST	"histlist"	/* SEC_LIST -- password history list */
#define S_PAG_DATA	"pag_data"	/* SEC_CHAR -- PAG data */



/********************************/
/* table types for data base	*/
/********************************/

#define USER_TABLE	0
#define GROUP_TABLE	1
#define PASSWD_TABLE	2
#define	SYSCK_TABLE	3
#define PORT_TABLE	4
#define GENERIC_TABLE	5
#define ROLES_TABLE	6
#define SMITUSR_TABLE	7
#define SMITGRP_TABLE	8

/**************************************/
/* Defines for authentication grammar */
/**************************************/
#define AUTH_ENV	"AUTHSTATE"	/* Environment variable name         */
#define AUTHPATH_ENV	"AUTHPATH"	/* Environment variable name         */
#define AUTH_COMPAT	"compat"	/* local files plus NIS              */
#define AUTH_DCE	"DCE"		/* Distributed Computing Environment */
#define AUTH_FILES	"files"		/* local files only		     */
#define AUTH_NONE_SEC	"NONE"		/* No authentication required	     */
#define AUTH_AND	"AND"		/* Boolean "and" within grammar	     */
#define AUTH_OR		"OR"		/* Boolean "or" within grammar       */
#define AUTH_DEFPATH	"/usr/lib/security/"	/* Default method path	     */
#define AUTH_NIS	"NIS"		/* Not used in grammar		     */

#define AUTH_SUCCESS	0		/* Success or reenter is non-zero    */
#define AUTH_FAILURE	1		/* Failure                           */
#define AUTH_UNAVAIL	2		/* Method not available              */
#define AUTH_NOTFOUND	3		/* User unknown to method            */
#define AUTH_WILDCARD   4		/* Grammar matches any result code   */
#define	AUTH_UNKNOWN	5		/* Method has not completed auth     */
#define AUTH_NOLOGIN    6               /* Failed due to login permissibility*/
#define AUTH_PWDMUSTCHANGE	7	/* Success and must reset password   */

#define ISLOCAL(str)    !strcmp(str, AUTH_FILES)
#define ISCOMPAT(str)   !strcmp(str, AUTH_COMPAT)
#define ISNIS(str)	!strcmp(str, AUTH_NIS)
#define ISNONE(str)	!strcmp(str, AUTH_NONE_SEC)
#define ISDCE(str)	!strcmp(str, AUTH_DCE)

/********************************/
/*    Method function pointers  */
/********************************/

typedef struct {
	int attr_flag;
	union {
		int au_int;
		long au_long;
		long long au_llong;
		char *au_char;
	} attr_un;
} attrval_t;

#define AL_USERATTR	01
#define AL_GROUPATTR	02
#define AL_SYSTEMATTR	03

typedef struct {
	char *al_name;
	int  al_flags;
	int	 al_type;
} attrlist_t;


#define attr_int attr_un.au_int
#define attr_long attr_un.au_long
#define attr_llong attr_un.au_llong
#define attr_char attr_un.au_char

/*
 * Prototypes and typedefs for functions which manipulate
 * authentication domains.
 */

typedef char authdb_t[16];

#ifdef _NO_PROTO
extern int setauthdb ();
extern int setauthdb_r ();
extern int getauthdb ();
extern int getauthdb_r ();
#else
extern int setauthdb (authdb_t, authdb_t);
extern int setauthdb_r (authdb_t, authdb_t);
extern int getauthdb (authdb_t);
extern int getauthdb_r (authdb_t);
#endif


#define	SECMETHOD_VERSION_PRE520	0
#define	SECMETHOD_VERSION_520		1
#define	SECMETHOD_VERSION_530		2
#define	SECMETHOD_VERSION_IAM		0x8000
#define	SECMETHOD_WHICH_VERSION(t) \
	(((t)->method_version & SECMETHOD_VERSION_IAM) ? \
		((t)->method_version & ~SECMETHOD_VERSION_IAM) : \
		SECMETHOD_VERSION_PRE520)

struct secmethod_table {
	int (*method_authenticate)(char*,char*,int*,char**);
	int (*method_chpass)(char*,char*,char*,char**);
	struct passwd * (*method_getpwnam)(const char*);
	struct passwd * (*method_getpwuid)(uid_t);
	struct group  * (*method_getgrgid)(gid_t);
	struct group  * (*method_getgrnam)(const char*);
	char * (*method_getgrset)(char*);
	int (*method_passwdexpired)(char*,char**);
	int (*method_passwdrestrictions)(char*,char*,char*,char**);
	int (*method_normalize)(char *, char *);
	int (*method_getentry)(char *, char *, char *[], attrval_t [], int);
	struct group * (*method_getgracct)(void *, int);
	int (*method_getgrusers)(char *, void *, int, int *);
	char * (*method_getpasswd)(char *);
	int (*method_commit)(char *, char *);
	int (*method_delgroup)(char *,char *);
	int (*method_deluser)(char *,char *);
	int (*method_newgroup)(char *);
	int (*method_newuser)(char *);
	int (*method_putentry)(char *, char *, char *[], attrval_t [], int);
	int (*method_putgrent)(struct group *);
	int (*method_putgrusers)(char *, char *);
	int (*method_putpwent)(struct passwd *);
	void * (*method_open)(const char *, const char *, int,char *);
	void (*method_close)(void *);
	void * (*method_lock)(char *, char *, int);
	void * (*method_unlock)(void *);
	attrlist_t ** (*method_attrlist)(void);
#ifdef	__64BIT__
	long	method_version;
#else
	int	method_version;
#endif
	int (*method_getcred) (char *, char *, char **, int *);
	int (*method_setcred) (char *, char *, char *, int);
	int (*method_deletecred) (char *, char *);
};

struct secmethod_table_v2 {
	int (*method_authenticate)(void*,char*,char*,int*,char**);
	int (*method_chpass)(void*,char*,char*,char*,char**);
	struct passwd * (*method_getpwnam)(void*,const char*);
	struct passwd * (*method_getpwuid)(void*,uid_t);
	struct group  * (*method_getgrgid)(void*,gid_t);
	struct group  * (*method_getgrnam)(void*,const char*);
	char * (*method_getgrset)(void*,char*);
	int (*method_passwdexpired)(void*,char*,char**);
	int (*method_passwdrestrictions)(void*,char*,char*,char*,char**);
	int (*method_normalize)(void *,char *, char *);
	int (*method_getentry)(void *,char *, char *, dbattr_t [], int);
	struct group * (*method_getgracct)(void *,void *, int);
	int (*method_getgrusers)(void *, char *, void *, int, int *);
	char * (*method_getpasswd)(void *, char *);
	int (*method_commit)(void *, char *, char *);
	int (*method_delgroup)(void *, char *,char *);
	int (*method_deluser)(void *, char *,char *);
	int (*method_newgroup)(void *, char *);
	int (*method_newuser)(void *, char *);
	int (*method_putentry)(void *, char *, char *, dbattr_t [], int);
	int (*method_putgrent)(void *, struct group *);
	int (*method_putgrusers)(void *, char *, char *);
	int (*method_putpwent)(void *, struct passwd *);
	void * (*method_open)(const char *, const char *, int,char *);
	void (*method_close)(void *);
	void * (*method_lock)(void *, char *, char *, int);
	void * (*method_unlock)(void *, void *);
	attrlist_t ** (*method_attrlist)(void *);
#ifdef	__64BIT__
	long	method_version;
#else
	int	method_version;
#endif
	int (*method_getcred) (void *, char *, char *, char **, int *);
	int (*method_setcred) (void *, char *, char *, char *, int);
	int (*method_deletecred) (void *, char *, char *);
	int (*method_delentry) (void *, char *, char *, char *);
	int (*method_newentry) (void *, char *, char *, char *);
	char *(*method_nextentry) (void *, char *, char *, char *);
};

#define	METHOD_ATTRLIST(l) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_attrlist) \
		(l->lm_open_handle)) : \
	((l->lm_table->method_attrlist) ()))

#define	METHOD_AUTHENTICATE(l,a,b,c,d) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_authenticate) \
		(l->lm_open_handle, a, b, c, d)) : \
	((l->lm_table->method_authenticate) (a, b, c, d)))

#define	METHOD_CHPASS(l,a,b,c,d) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_chpass) \
		(l->lm_open_handle, a, b, c, d)) : \
	((l->lm_table->method_chpass) (a, b, c, d)))

#define	METHOD_CLOSE(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_close) (a)) : \
	((l->lm_table->method_close) (a)))

#define	METHOD_COMMIT(l,a,b) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_commit) \
		(l->lm_open_handle, a, b)) : \
	((l->lm_table->method_commit) (a, b)))

#define	METHOD_DELETECRED(l,a,b) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_deletecred) \
		(l->lm_open_handle, a, b)) : \
	((l->lm_table->method_deletecred) (a, b)))

#define	METHOD_DELGROUP(l,a,b) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_delgroup) \
		(l->lm_open_handle, a, b)) : \
	((l->lm_table->method_delgroup) (a, b)))

#define	METHOD_DELUSER(l,a,b) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_deluser) \
		(l->lm_open_handle, a, b)) : \
	((l->lm_table->method_deluser) (a, b)))

#define METHOD_DELENTRY(l,a,b,c) \
	(((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) && \
	    ((struct secmethod_table_v2 *) (l->lm_table))->method_delentry) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_delentry) \
		(l->lm_open_handle, a, b, c)) : \
	((errno = ENOSYS, -1)))

#define	METHOD_GETCRED(l,a,b,c,d) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_getcred) \
		(l->lm_open_handle, a, b, c, d)) : \
	((l->lm_table->method_getcred) (a, b, c, d)))

#define	METHOD_GETGRACCT(l,a,b) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_getgracct) \
		(l->lm_open_handle, a, b)) : \
	((l->lm_table->method_getgracct) (a, b)))

#define	METHOD_GETGRUSERS(l,a,b,c,d) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_getgrusers) \
		(l->lm_open_handle, a, b, c, d)) : \
	((l->lm_table->method_getgrusers) (a, b, c, d)))

#define	METHOD_GETPASSWD(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_getpasswd) \
		(l->lm_open_handle, a)) : \
	((l->lm_table->method_getpasswd) (a)))

#define	METHOD_GETPWNAM(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_getpwnam) \
		(l->lm_open_handle, a)) : \
	((l->lm_table->method_getpwnam) (a)))

#define	METHOD_GETPWUID(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_getpwuid) \
		(l->lm_open_handle, a)) : \
	((l->lm_table->method_getpwuid) (a)))

#define	METHOD_GETGRGID(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_getgrgid) \
		(l->lm_open_handle, a)) : \
	((l->lm_table->method_getgrgid) (a)))

#define	METHOD_GETGRNAM(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_getgrnam) \
		(l->lm_open_handle, a)) : \
	((l->lm_table->method_getgrnam) (a)))

#define	METHOD_GETGRSET(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_getgrset) \
		(l->lm_open_handle, a)) : \
	((l->lm_table->method_getgrset) (a)))

#define	METHOD_LOCK(l,a,b,c) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_lock) \
		(l->lm_open_handle, a, b, c)) : \
	((l->lm_table->method_lock) (a, b, c)))

#define METHOD_NEWENTRY(l,a,b,c) \
	(((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) && \
	    ((struct secmethod_table_v2 *) (l->lm_table))->method_newentry) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_newentry) \
		(l->lm_open_handle, a, b, c)) : \
	((errno = ENOSYS, -1)))

#define	METHOD_NEWGROUP(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_newgroup) \
		(l->lm_open_handle, a)) : \
	((l->lm_table->method_newgroup) (a)))

#define	METHOD_NEWUSER(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_newuser) \
		(l->lm_open_handle, a)) : \
	((l->lm_table->method_newuser) (a)))

#define METHOD_NEXTENTRY(l,a,b,c) \
	(((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) && \
	    ((struct secmethod_table_v2 *) (l->lm_table))->method_nextentry) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_nextentry) \
		(l->lm_open_handle, a, b, c)) : \
	((errno = ENOSYS, (char *) 0)))

#define	METHOD_NORMALIZE(l,a,b) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_normalize) \
		(l->lm_open_handle, a, b)) : \
	((l->lm_table->method_normalize) (a, b)))

#define	METHOD_OPEN(l,a,b,c,d) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_open) \
			(a,b,c,d)) : \
	((l->lm_table->method_open) (a,b,c,d)))

#define	METHOD_PASSWDEXPIRED(l,a,b) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_passwdexpired) \
		(l->lm_open_handle, a, b)) : \
	((l->lm_table->method_passwdexpired) (a, b)))

#define	METHOD_PASSWDRESTRICTIONS(l,a,b,c,d) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_passwdrestrictions) \
		(l->lm_open_handle, a, b, c, d)) : \
	((l->lm_table->method_passwdrestrictions) (a, b, c, d)))

#define	METHOD_PUTGRENT(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_putgrent) \
		(l->lm_open_handle, a)) : \
	((l->lm_table->method_putgrent) (a)))

#define	METHOD_PUTGRUSERS(l,a,b) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_putgrusers) \
		(l->lm_open_handle, a, b)) : \
	((l->lm_table->method_putgrusers) (a, b)))

#define	METHOD_PUTPWENT(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_putpwent) \
		(l->lm_open_handle, a)) : \
	((l->lm_table->method_putpwent) (a)))

#define	METHOD_SETCRED(l,a,b,c,d) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_setcred) \
		(l->lm_open_handle, a, b, c, d)) : \
	((l->lm_table->method_setcred) (a, b, c, d)))

#define	METHOD_UNLOCK(l,a) \
	((SECMETHOD_WHICH_VERSION(l->lm_table) >= SECMETHOD_VERSION_530) ? \
	((((struct secmethod_table_v2 *) (l->lm_table))->method_unlock) \
		(l->lm_open_handle, a)) : \
	((l->lm_table->method_unlock) (a)))


/* Parse tree for authentication grammar */
struct secgrammar_tree
{
	enum {NODE, LEAF} type;         /* Interior branch or leaf      */
	char *name;                     /* Method name                  */
	int  result;                    /* Expected result from method  */
#ifndef __cplusplus
	char *operator;                 /* Binary operator "AND"/"OR"   */
#else
	char *binary_operator;		/* different name if C++ 	*/
#endif
	struct secgrammar_tree *left;   /* Left branch of tree          */
	struct secgrammar_tree *right;  /* Right branch of tree         */
	int  rc;			/* Actual result		*/
	int  visited;			/* Node/Leaf already evaluated	*/
};

/* defines for pwdbm_update() */
#define PWDBM_PASSWD 1
#define PWDBM_SHELL  4
#define PWDBM_GECOS  6

/********************************/
/*	AF routines defines	*/
/********************************/

/* structures for lowest level routine for attribute file manipulation */
struct ATTR
{       char *  AT_name;
	char *  AT_value;
};

typedef struct ATTR * ATTR_t;

struct AFILE
{       FILE *  AF_iop;
	int     AF_rsiz;
	int     AF_natr;
	char *  AF_cbuf;
	char *  AF_dbuf;
	ATTR_t  AF_catr;
	ATTR_t  AF_datr;
};

typedef struct AFILE * AFILE_t;

/* security library routines */
#ifdef  _NO_PROTO

extern AFILE_t 	afopen();
extern int	afclose();
extern int	afrewind();
extern ATTR_t 	afnxtrec();
extern ATTR_t 	afgetrec();
extern ATTR_t 	affndrec();
extern char * 	afgetatr();

extern char *auditread();
extern char *auditread_r();

#else /* _NO_PROTO */

extern AFILE_t 	afopen(char *);
extern int	afclose(AFILE_t);
extern int	afrewind(AFILE_t);
extern ATTR_t 	afnxtrec(AFILE_t);
extern ATTR_t 	afgetrec(AFILE_t, char *);
extern ATTR_t 	affndrec();
extern char * 	afgetatr(ATTR_t, char *);

struct aud_rec;
extern char *auditread(FILE *, struct aud_rec *);
extern char *auditread_r(FILE *, struct aud_rec *, size_t, void **);

#endif /* _NO_PROTO */

/*-----------------------------------------------------------------------*
 * index names for the security related  database files
 *-----------------------------------------------------------------------*/
#define PASSWDNM_IDX "/etc/passwd.nm.idx"
#define PASSWDID_IDX "/etc/passwd.id.idx"
#define SPASSWD_IDX  "/etc/security/passwd.idx"
#define LASTLOG_IDX  "/etc/security/lastlog.idx"

#endif /* _H_USERSEC */
