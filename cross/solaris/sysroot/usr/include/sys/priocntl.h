/*	Copyright (c) 1984, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_PRIOCNTL_H
#define	_SYS_PRIOCNTL_H

#pragma ident	"@(#)priocntl.h	1.19	04/09/28 SMI"	/* from SVR4 1.6 */

#include <sys/types.h>
#include <sys/procset.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	PC_VERSION	1	/* First version of priocntl */

#ifdef __STDC__
extern long	priocntl(idtype_t, id_t, int, ...);
extern long	priocntlset(procset_t *, int, ...);
#else
extern long	priocntl(), priocntlset();
#endif	/* __STDC__ */

/*
 * The following are the possible values of the command
 * argument for the priocntl system call.
 */

#define	PC_GETCID	0	/* Get class ID */
#define	PC_GETCLINFO	1	/* Get info about a configured class */
#define	PC_SETPARMS	2	/* Set scheduling parameters */
#define	PC_GETPARMS	3	/* Get scheduling parameters */
#define	PC_ADMIN	4	/* Scheduler administration (used by */
				/*   dispadmin(1M), not for general use) */
#define	PC_GETPRIRANGE	5	/* Get global priority range for a class */
				/* posix.4 scheduling, not for general use */
#define	PC_DONICE	6	/* Set or get nice value */
#define	PC_SETXPARMS	7	/* Set extended scheduling parameters */
#define	PC_GETXPARMS	8	/* Get extended scheduling parameters */
#define	PC_SETDFLCL	9	/* Set default class, not for general use */

#define	PC_CLNULL	-1

#define	PC_CLNMSZ	16
#define	PC_CLINFOSZ	(32 / sizeof (int))
#define	PC_CLPARMSZ	(32 / sizeof (int))

#define	PC_GETNICE	0
#define	PC_SETNICE	1

typedef struct pcinfo {
	id_t	pc_cid;			/* class id */
	char	pc_clname[PC_CLNMSZ];	/* class name */
	int	pc_clinfo[PC_CLINFOSZ];	/* class information */
} pcinfo_t;

typedef struct pcparms {
	id_t	pc_cid;			    /* process class */
	int	pc_clparms[PC_CLPARMSZ];    /* class specific parameters */
} pcparms_t;

typedef struct pcnice {
	int	pc_val;			/* nice value */
	int	pc_op;			/* type of operation, set or get */
} pcnice_t;

/*
 * The following is used by the priocntl(2) varargs interface (command
 * codes: PC_SETXPARMS and PC_GETXPARMS).
 */

#define	PC_VAPARMCNT	8	/* maximal number of (key, value) pairs */
#define	PC_KY_NULL	0	/* terminates the (key, value) pair chain */
#define	PC_KY_CLNAME	1	/* get the class name of a process or LWP. */

typedef	struct pc_vaparm {
	int		pc_key;		/* describing key */
	u_longlong_t	pc_parm;	/* associated parameter */
} pc_vaparm_t;

typedef	struct pc_vaparms {
	uint_t		pc_vaparmscnt;		/* # of (key, value) pairs */
	pc_vaparm_t	pc_parms[PC_VAPARMCNT];	/* parameter buffer */
} pc_vaparms_t;

#if defined(_SYSCALL32) && \
	_LONG_LONG_ALIGNMENT == 8 && _LONG_LONG_ALIGNMENT_32 == 4

/*
 * These structures are needed by the 64-bit kernel on certain architectures
 * to translate pc_vaparms_t/pc_vaparm_t data structures from 32-bit userland.
 */
#pragma pack(4)

typedef struct {
	int32_t		pc_key;		/* describing key */
	uint64_t	pc_parm;	/* associated parameter */
} pc_vaparm32_t;

#pragma pack()

typedef struct {
	uint32_t	pc_vaparmscnt;		/* # of (key, value) pairs */
	pc_vaparm32_t	pc_parms[PC_VAPARMCNT];	/* parameter buffer */
} pc_vaparms32_t;

#endif	/* _SYSCALL32 && ... */

/*
 * The following is used by the library librt for
 * posix.4 scheduler interfaces and is not for general use.
 */

typedef struct pcpri {
	id_t	pc_cid;			/* process class */
	pri_t	pc_clpmax;		/* class global priority max */
	pri_t	pc_clpmin;		/* class global priority min */
} pcpri_t;

/*
 * The following is used by the dispadmin(1M) command for
 * scheduler administration and is not for general use.
 */

#ifdef _SYSCALL32
/* Data structure for ILP32 clients */
typedef struct pcadmin32 {
	id32_t		pc_cid;
	caddr32_t	pc_cladmin;
} pcadmin32_t;
#endif	/* _SYSCALL32 */

typedef struct pcadmin {
	id_t	pc_cid;
	caddr_t	pc_cladmin;
} pcadmin_t;

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_PRIOCNTL_H */
