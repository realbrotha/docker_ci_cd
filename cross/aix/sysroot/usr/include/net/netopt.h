/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/net/netopt.h 1.18.1.2                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1989              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)76	1.18.1.2  src/bos/kernel/net/netopt.h, sockinc, bos53V, v2009_12B5 2/24/09 06:51:04 */
/* 
 * COMPONENT_NAME: (SOCKET) Socket services
 * 
 * FUNCTIONS: ADD_NETOPT, NETOPTINT 
 *
 * ORIGINS: 26 27 
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989 
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */
#include <sys/limits.h>

#ifndef _NETOPT_H_
#define _NETOPT_H_

#define  MAXOPTLEN  128

struct netopt {
	char *name;		/* name of option/symbol */
	short size;		/* size of object in kernel */
	caddr_t obj;		/* address of object in kernel */
	caddr_t deflt;		/* address of default object in kernel */
	char *format;		/* printf format for this option (%s, %d) */
	struct netopt *next;	/* next in linked list */
	int (*init)();		/* option init routine (may be NULL) */
	int readonly;		/* option is read-only */
        int64_t max;                /* Max. value */
        int64_t min;                /* Min. value */
        int  unit;               /* Measured unit */
        int groups;             /* groups for displayed by -x */
        int types;              /* RUNTIME, LOADTIME or REDAONLY */
};

struct netopt_pre520_compat {
        char *name;             /* name of option/symbol */
        short size;             /* size of object in kernel */
        caddr_t obj;            /* address of object in kernel */
        caddr_t deflt;          /* address of default object in kernel */
        char *format;           /* printf format for this option (%s, %d) */
        struct netopt *next;    /* next in linked list */
        int (*init)();          /* option init routine (may be NULL) */
        int readonly;           /* option is read-only */
};

struct optreq {
	char name[MAXOPTLEN];	/* name of option/symbol */
	char data[MAXOPTLEN];	/* data area for option value */
	char getnext;		/* flag */
};

struct optreq1 {
        char name[MAXOPTLEN];   /* name of option/symbol */
        char data[MAXOPTLEN];   /* data area for option value */
        char deflt[MAXOPTLEN];  /* default value for option value */
        int64_t max;               /* Max. value */
        int64_t min;               /* Min. value */
        int  unit;              /* Measured unit */
        int groups;             /* groups for displayed by -x */
        int types;              /* RUNTIME, LOADTIME or REDAONLY */
        char getnext;           /* flag */
};

extern struct netopt *netopts;
extern void add_netoption(struct netopt_pre520_compat *);

#define   add_netopt  ADD_NETOPT_PRE520
#define	  ADD_NETOPT_PRE520(optname, fmt)				\
	  {								\
                  optname##_opt.name = #optname;                        \
                  optname##_opt.size = sizeof( optname );               \
                  optname##_opt.obj = (caddr_t)&optname;                \
                  optname##_opt.deflt = (caddr_t)&optname##_dflt;       \
                  optname##_opt.format = fmt;                   	\
                  optname##_opt.next = NULL;                    	\
                  optname##_opt.readonly = 0;                   	\
		  optname##_opt.max = LONG_MAX;				\
		  optname##_opt.min = 0;				\
		  optname##_opt.unit = UT_NUMERIC;			\
		  optname##_opt.groups = OTHER_OPT;			\
		  optname##_opt.types = RUNTIME_TP;			\
                  add_netoption_520(&optname##_opt);                        \
          }

#define   ADD_NETOPT(optname, fmt, group, type)  \
	  {							\
                optname##_opt.name = #optname;\
                optname##_opt.size = sizeof( optname );\
                optname##_opt.obj = (caddr_t)&optname;\
                optname##_opt.deflt = (caddr_t)&optname##_dflt;       \
                optname##_opt.format = fmt;\
                optname##_opt.next = NULL;\
                optname##_opt.readonly = 0;\
                optname##_opt.max = (int64_t)optname##_max;       \
                optname##_opt.min = (int64_t)optname##_min;     \
                optname##_opt.unit = optname##_unit;   \
                optname##_opt.groups = group;  \
                optname##_opt.types = type;    \
                add_netoption_520(&optname##_opt); \
	  }

#define   del_netopt   DEL_NETOPT
#define   DEL_NETOPT(optname)   delete_netopt_520(&optname##_opt)

/* declaration for the stuff that describes integer option */
#define  NETOPTINT(x)  struct netopt x##_opt; \
		extern long x, x##_dflt, x##_max, x##_min;\
                extern int x##_unit 

/* declaration for the stuff that describes integer option
 * same as NETOPTINT but max value is a pointer
 */
#define  NETOPTINTPTR(x)  struct netopt x##_opt; \
		extern long x, x##_dflt, x##_min;\
		extern long * x##_max;\
		extern int x##_unit

/* declaration for the stuff that describes unsigned integer option */
#define  NETOPTINTUINT(x)  struct netopt x##_opt; \
		extern unsigned int x, x##_dflt, x##_max, x##_min; \
		extern int x##_unit

/*
 * following MSG number was hard coded from obj/power/bos/usr/sbin/no/no_msg.h
*/
#define GEN_OPT         24
#define TCP_OPT         25
#define UDP_OPT         26
#define IP_OPT          27
#define ARP_OPT         28
#define STR_OPT         29
#define OTHER_OPT       30

#define UT_NUMERIC      31
#define UT_BOOLEAN      32
#define UT_MINUTE       33
#define UT_15SEC        34
#define UT_SECOND       35
#define UT__6SEC        36
#define UT_HSECOND      37
#define UT_MSECOND      38
#define UT_MSGRATE      39
#define UT_KBYTE        40
#define UT_BYTE         41
#define UT_SEGMENT      42
#define UT_RTT          43
#define UT_PERCENT      44
#define UT_BUCKETSZ     45
#define UT_BUCKET       46
#define UT_PORTLST      47
#define UT_MASK         48
#define UT_STRING       49

#define RUNTIME_TP      49
#define LOADTIME_TP     50
#define READONLY_TP     51
#define CONNECT_TP	61
#define INCREMENT_TP	62
#endif /* _NETOPT_H_ */
