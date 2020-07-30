/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/chownx.h 1.10                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)26	1.10  src/bos/kernel/sys/chownx.h, syslfs, bos530 11/8/02 16:57:30 */
/*
 * COMPONENT_NAME: (SYSLFS) Logical File System
 *
 * FUNCTIONS: chownx header
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_CHOWNX
#define _H_CHOWNX

/*
 * Values for the sva_tflag.
 * Specifies how the uid and gid values are to be set.
 */
#define	T_OWNER_AS_IS	004	/* the owner id in the inode is		*/
				/*   unaltered				*/
#define	T_GROUP_AS_IS	040	/* the group id in the inode is		*/
				/*   unaltered				*/

/* flags 00100-04000 are reserved for the other parts of setattr */

#ifndef __cplusplus
extern int chownx(char *, uid_t, gid_t, int);
extern int fchownx(int, uid_t, gid_t, int);
#endif  /* __cplusplus */

#endif	/* _H_CHOWNX */
