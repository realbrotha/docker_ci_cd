/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/utsname.h 1.23                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1992          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)15       1.23  src/bos/kernel/sys/utsname.h, syslfs, bos530 12/12/03 11:31:48 */

/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1985, 1992
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef	_H_UTSNAME
#define	_H_UTSNAME

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif



/*
 * POSIX requires that certain values be included in utsname.h.  It also
 * requires that when _POSIX_SOURCE is defined only those standard
 * specific values are present.  This header includes all the POSIX
 * required entries.
 */
#ifdef _POSIX_SOURCE

#define  _SYS_NMLN           32     /* Important: do not change this value ! */

/* struct for uname() */
struct utsname {
	char    sysname[_SYS_NMLN];
	char    nodename[_SYS_NMLN];
	char    release[_SYS_NMLN];
	char    version[_SYS_NMLN];
	char    machine[_SYS_NMLN];
#if defined(_IA64) || defined(__ia64)
	char    procserial[_SYS_NMLN];
#endif
};

#ifdef _NO_PROTO
extern int uname();
#else
#ifndef _KERNEL
extern int uname(struct utsname *);
#endif /* _KERNEL */
#endif /* _NO_PROTO */

#endif /* _POSIX_SOURCE */

#ifdef _ALL_SOURCE

#define  SYS_NMLN _SYS_NMLN

/* struct for unamex() */
struct xutsname {
	unsigned int nid;
	int reserved;
	unsigned long long longnid;
};


/* The only permissible value for
 * the target field in struct setuname */
#define  UUCPNODE     2

/* struct for unameu() */
struct setuname {
	int	target;
	int	len;
	char *newstr;
};

#define  LPAR_NAME_LEN		128

typedef struct {
	int	flags;	/* see sysconfig.H for definitions */
	unsigned int	part_number;
	char    part_name[LPAR_NAME_LEN];
} LPAR_ID_INFO;

#ifdef	_KERNEL
extern struct utsname  utsname;
extern struct xutsname xutsname;
#endif

#endif /* _ALL_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* _H_UTSNAME */
