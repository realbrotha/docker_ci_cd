/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/pag.h 1.2                                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2001,2003          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)02     1.2  src/bos/kernel/sys/pag.h, syssauth, bos530 12/8/03 12:06:51 */
/*
 *   COMPONENT_NAME: SYSSAUTH
 *
 *   FUNCTIONS: __pag_getid, __pag_getname, __pag_setname,
 *		__pag_getvalue, __pag_setvalue
 *
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 2001
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_PAG
#define _H_PAG

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * PAG parameters, limits, etc.
 */

#define	PAG_NAME_LENGTH_MAX	4
#define	PAG_NPAGS		9

/*
 * Flags to __pag_setname/kcred_setpagname
 */

#define	PAG_UNIQUEVALUE		0
#define	PAG_MULTIVALUED		1
#define	PAG_64BIT		2

/*
 * Flags to alloc/free function referenced by
 * kcred_setpagname
 */

#define	PAGVALUE_ALLOC		1
#define	PAGVALUE_FREE		2

/*
 * Internal flag to set PAG data produced by authenticate()
 * function.
 */

#define	PAG_USE_AUTH_DATA	((char*) 1)

/*
 * Flags to genpagvalue/__pag_genpagvalue/kcred_genpagvalue
 */

#define	PAG_SET_VALUE		1
#define	PAG_COPY_CRED		2

/*
 * Structure for *info() routines 
 */

struct paginfo {
	int pag_type;
	int pag_flags;
	int pag_pad[2];
};

/*
 * PAG name management kernel services
 */

#ifdef _KERNEL

/*
 * Kernel services
 */

int kcred_getpagname (int, char *, int);
int kcred_getpagid (char *);
int kcred_setpagname (char *, int, void (*) (int, int));
int kcred_getpaginfo (int, struct paginfo *, int);
#else

/*
 * Low level system calls
 */

int __pag_getname (int, char *, int);
int __pag_setname (char *, int);
int __pag_getid (char *);
int __pag_getvalue (int);
int __pag_getvalue64 (int, uint64_t *);
int __pag_setvalue (int, int);
int __pag_setvalue64 (int, uint64_t);
int __pag_genpagvalue (int, uint64_t *, int);
int __pag_getinfo (int, struct paginfo *, int);

/*
 * C library functions
 */

int getpagdata (char *, char **, int*);
int getpaglist (char **);
int getpagvalue (char *);
uint64_t getpagvalue64 (char *);
int resetpagvalue (char *);
int setpagdata (char *, char *, int);
int setpagname (char *, int);
int setpagvalue (char *, int);
int setpagvalue64 (char *, uint64_t);
int genpagvalue (char *, uint64_t *, int);
int getpaginfo (char *, struct paginfo *, int);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _H_PAG */
