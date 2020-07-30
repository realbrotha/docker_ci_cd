/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/usr/include/userconf.h 1.11.5.4                         */
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
/* @(#)93	1.11.5.4  src/bos/usr/include/userconf.h, cmdsauth, bos53X, x2011_31B5 7/19/11 06:45:42 */
/*
 * COMPONENT_NAME: CMDSAUTH 
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1995
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
 
#ifndef _H_USERCONF    
#define _H_USERCONF

#ifdef _NO_PROTO
	extern	int	getconfattr ();
	extern  int	endconfattr ();
#else  /* _NO_PROTO */
	extern	int	getconfattr (char *, char *, void *, int);
	extern  int	endconfattr (void);
#endif /* _NO_PROTO */

/* system attribute values */
#define SC_SYS_LOGIN		"usw"
#define SC_SYS_USER		"user"
#define SC_SYS_ADMUSER		"admin"

#define SC_SYS_AUDIT		"classes"
#define SC_SYS_AUSERS		"users"
#define SC_SYS_ASYS		"system"
#define SC_SYS_ABIN		"bin"
#define SC_SYS_ASTREAM		"stream"
#define SC_SYS_ATTRLIST     	"attrlist"

/* attributes associated with logins */
#define SC_AUTHTYPE		"auth_type"
#define	SC_GECOS		"gecos"		
#define	SC_IDS			"ids"
#define	SC_MAXBAD		"maxbad"		
#define	SC_MAXLOGINS		"maxlogins"		
#define	SC_PASSWDGEN		"passwdgen"		
#define SC_SEARCHORDER_FLAG     "searchorderflag"
#define	SC_SHELLS		"shells"		
#define	SC_YPDOMAIN		"YPdomain"		
#define SC_PWD_ALGO		"pwd_algorithm"
#define SC_MKHOMEATLOGIN	"mkhomeatlogin"
#define SC_UNIXPASSWDCOMPAT     "unix_passwd_compat"

/* system attributes in /etc/security/passwd */
#define SC_FLAGS		"flags"
#define SC_LASTUPDATE		"lastupdate"

/* mkuser.default attribute values */
#define	SC_ACCT			"acct"			
#define	SC_ACCTS		"accounts"		
#define SC_ADMGROUPS		"admgroups"
#define SC_ADMIN		"admin"
#define	SC_AUDIT       		"auditclasses"		
#define	SC_AUTH1 		"auth1"		
#define	SC_AUTH2 		"auth2"		
#define	SC_AUTHDOMAIN		"auth_domain"
#define	SC_AUTHNAME		"auth_name"
#define SC_AUTHMESSAGES		"messages"
#define SC_AUTHPROGRAM		"program"
#define SC_AUTHRETRY		"retry"
#define SC_AUTHRETRYDELAY	"retry_delay"
#define SC_AUTHSYSTEM		"SYSTEM"
#define SC_AUTHTIMEOUT		"timeout"
#define	SC_CORE			"core"			
#define	SC_CORE_HARD		"core_hard"
#define SC_CORECOMP		"core_compress"
#define SC_COREPATH		"core_path"
#define SC_COREPNAME		"core_pathname"
#define SC_CORENAMING		"core_naming"
#define SC_CORENAME		"core_name"
#define	SC_CPU			"cpu"			
#define	SC_CPU_HARD		"cpu_hard"
#define SC_DAEMONCHK		"daemon"
#define	SC_DATA			"data"			
#define	SC_DATA_HARD		"data_hard"
#define	SC_DICTION		"dictionlist"
#define SC_DLEVEL               "d_level"
#define SC_EXPIRATION		"expires"
#define	SC_FSIZE		"fsize"		
#define	SC_FSIZE_HARD		"fsize_hard"		
#define	SC_FUNCMODE		"funcmode"
#define	SC_GROUP		"pgrp"		
#define	SC_GROUPS		"groups"		
#define SC_HISTEXPIRE           "histexpire"
#define SC_HISTSIZE             "histsize"
#define	SC_HOME			"home"			
#define	SC_HOSTSALLOWEDLOGIN	"hostsallowedlogin"
#define	SC_HOSTSDENIEDLOGIN	"hostsdeniedlogin"
#define	SC_LLEVEL		"l_level"
#define	SC_LOCKED		"account_locked"
#define SC_LOGINCHK		"login"
#define	SC_LOGRETRIES		"loginretries"
#define	SC_LOGTIMES		"logintimes"
#define	SC_MAXAGE		"maxage"		
#define	SC_MAXEXPIRED		"maxexpired"
#define	SC_MAXREPEAT		"maxrepeats"		
#define SC_MAXULOGS             "maxulogs"
#define	SC_MINAGE		"minage"		
#define	SC_MINALPHA		"minalpha"
#define	SC_MINDIFF		"mindiff"
#define	SC_MINLEN		"minlen"
#define	SC_MINOTHER		"minother"
#define	SC_NOFILE		"nofiles"			
#define	SC_NOFILE_HARD		"nofiles_hard"			
#define	SC_PGRP			"pgrp"
#define	SC_PROG			"shell"			
#define	SC_PROJECTS		"projects"
#define SC_PROMPTMAC            "prompt_mac"
#define	SC_PWDCHECKS		"pwdchecks"
#define	SC_PWDWARNTIME		"pwdwarntime"
#define	SC_RCMDS		"rcmds"
#define	SC_REGISTRY		"registry"
#define SC_RLOGINCHK		"rlogin"
#define	SC_ROLES		"roles"
#define	SC_RSS			"rss"			
#define	SC_RSS_HARD		"rss_hard"
#define	SC_SCREENS		"screens"
#define	SC_SHELL		"shell"
#define	SC_STACK		"stack"		
#define	SC_STACK_HARD		"stack_hard"
#define SC_SUCHK		"su"
#define SC_SUGROUPS		"sugroups"
#define SC_SYSENV		"sysenv"
#define SC_TELNETCHK		"telnet"
#define SC_TPATH		"tpath"
#define SC_TTYS			"ttys"
#define SC_UACTIVITY            "uactivity"
#define	SC_UCORE		"core"
#define	SC_UCORE_HARD		"core_hard"
#define	SC_UCPU			"cpu"
#define	SC_UCPU_HARD		"cpu_hard"
#define	SC_UDATA		"data"
#define	SC_UDATA_HARD		"data_hard"
#define	SC_UFSIZE		"fsize"		
#define	SC_UFSIZE_HARD		"fsize_hard"		
#define	SC_UID			"uid"			
#define SC_ULEVEL               "u_level"
#define SC_UMASK		"umask"
#define	SC_UNOFILE		"nofiles"		
#define	SC_UNOFILE_HARD		"nofiles_hard"		
#define	SC_URSS			"rss"
#define	SC_URSS_HARD		"rss_hard"
#define SC_USRENV		"usrenv"
#define	SC_USREXPORT		"dce_export"
#define	SC_USTACK		"stack"
#define	SC_USTACK_HARD		"stack_hard"
#define	SC_USW_OPTIONS		"options"
#define SC_UTOCOUNT             "utocount"
#define SC_BASEIDS              "baseids"
#define SC_DIST_UNIQID          "dist_uniqid"

/* /etc/security/audit/config attribute values */
/* start stanza */
#define	SC_AUD_BINMODE		"binmode"
#define	SC_AUD_STRMODE		"streammode"

/* bin stanza */
#define	SC_AUD_BIN1		"bin1"
#define	SC_AUD_BIN2		"bin2"
#define	SC_AUD_BINCMDS		"bincmds"
#define	SC_AUD_BINSIZE		"binsize"
#define	SC_AUD_FREESPACE	"freespace"
#define	SC_AUD_TRAIL		"trail"

/* stream stanza */
#define	SC_AUD_STRCMDS		"streamcmds"

/* /etc/security/audit/events attribute values */
#define	SC_AUD_EVENT		"auditpr"

/* /etc/security/audit/objects attribute values */
#define	SC_AUDOBJ_READ		"r"
#define	SC_AUDOBJ_WRITE		"w"
#define	SC_AUDOBJ_EXEC		"x"

/* /usr/lib/security/methods.cfg attribute values */
#define SC_METH_PROGRAM		"mprogram"
#define	SC_METH_PROGRAM64	"mprogram_64"
#define	SC_METH_OPTIONS		"moptions"
#define	SC_METH_DOMAIN		"mdomain"

/* /etc/security/pwdalg.cfg attributes */
#define SC_PWD_MODULE		"lpa_module"
#define SC_PWD_OPTIONS		"lpa_options"

#endif /* _H_USERCONF */
