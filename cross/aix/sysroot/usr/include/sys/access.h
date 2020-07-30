/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/access.h 1.13                                */
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
/* @(#)33	1.13  src/bos/kernel/sys/access.h, syslfs, bos530 5/28/98 10:48:08 */

#ifndef _H_ACCESS
#define _H_ACCESS

/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27, 3
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#include <standards.h>

/* POSIX does not define access.h, however, certain values in access.h
 * are required to be included by unistd.h when _POSIX_SOURCE is defined.
 * Therefore, these values are confined within POSIX ifdefs.
 */

#ifdef _POSIX_SOURCE
/*
 *  BSD defines
 */
#define	F_OK	00		/* E_ACC does file exist */
#define	X_OK	01		/* X_ACC is it executable by caller */
#define	W_OK	02		/* W_ACC writable by caller */
#define	R_OK	04		/* R_ACC readable by caller */

#endif /* _POSIX_SOURCE */

#ifdef _ALL_SOURCE

#define R_ACC	04	/* read */
#define W_ACC	02	/* write */
#define X_ACC	01	/* execute (search) */
#define E_ACC	00	/* check existence of file */
#define NO_ACC	00	/* no access rights */

/* accessx() and acl_chg() "who" arguments */
#define ACC_SELF	0x00
#define ACC_INVOKER	0x01
#define ACC_OBJ_OWNER	0x02 
#define ACC_OBJ_GROUP	0x04
#define ACC_OTHERS	0x08
#define ACC_ANY		0x10
#define ACC_ALL		0x20

/* acl_chg() "how" paramaters */
#define ACC_PERMIT	0x01
#define ACC_DENY	0x02
#define ACC_SPECIFY	0x03

#ifdef  _NO_PROTO
	extern char *acl_get();
	extern char *acl_fget();
	extern int   acl_chg();
	extern int   acl_fchg();
	extern int   acl_put();
	extern int   acl_fput();
	extern int   acl_set();
	extern int   acl_fset();
	extern int   accessx();
#else	/* _NO_PROTO */
	extern char *acl_get(char *);
	extern char *acl_fget(int);
	extern int   acl_chg(char *, int, int, int);
	extern int   acl_fchg(int, int, int, int);
	extern int   acl_put(char *, char *, int);
	extern int   acl_fput(int, char *, int);
	extern int   acl_set(char *, int, int, int);
	extern int   acl_fset(int, int, int, int);
	extern int   accessx(char *, int, int);
#endif	/* _NO_PROTO */

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
	extern int 	faccessx(int, int, int);
#endif /* defined(__64BIT_KERNEL) || defined(__FULL_PROTO) */

#endif /* _ALL_SOURCE */
#endif /* _H_ACCESS */
