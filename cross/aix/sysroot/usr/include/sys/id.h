/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/id.h 1.4.1.1                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)21	1.4.1.1  src/bos/kernel/sys/id.h, syssauth, bos530 5/28/98 10:48:16 */
/*
 * COMPONENT_NAME: (id.h) 
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_ID
#define _H_ID

#include <sys/types.h>

#define	ID_EFFECTIVE	0x01
#define	ID_REAL		0x02
#define	ID_SAVED	0x04
#define	ID_LOGIN	0x08
#define ID_ACCT		0x10

/*
 * The following prototypes declare the functions which use the
 * constants defined above.
 */

#ifdef	_NO_PROTO
extern	uid_t	getuidx();
extern	gid_t	getgidx();
extern	int	setuidx();
extern	int	setgidx();
#else
extern	uid_t	getuidx (int which);
extern	gid_t	getgidx (int which);
extern	int	setuidx (int which, uid_t uid);
extern	int	setgidx (int which, gid_t gid);
#endif

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
extern void geteuidx (uid_t *, gid_t *);
extern int seteuid(uid_t);
#endif /* __64BIT_KERNEL || __FULL_PROTO */

#endif /* _H_ID */
