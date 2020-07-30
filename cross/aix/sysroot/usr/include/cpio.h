/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/cpio.h 1.5                                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1990,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)65	1.5  src/bos/usr/include/cpio.h, cmdarch, bos530 2/22/96 11:56:16 */
/*
 * COMPONENT_NAME: CMDARCH
 *                                                                    
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1990, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_CPIO
#define _H_CPIO

#ifndef _H_STANDARDS
#include <standards.h>
#endif

#define	C_IRUSR		0000400
#define	C_IWUSR		0000200
#define	C_IXUSR		0000100
#define	C_IRGRP		0000040
#define	C_IWGRP		0000020
#define	C_IXGRP		0000010
#define	C_IROTH		0000004
#define	C_IWOTH		0000002
#define	C_IXOTH		0000001
#define	C_ISUID		0004000
#define	C_ISGID		0002000
#define	C_ISVTX		0001000
#define	C_ISDIR		0040000
#define	C_ISFIFO	0010000
#define	C_ISREG		0100000
#define	C_ISBLK		0060000
#define	C_ISCHR		0020000
#define	C_ISCTG		0110000
#define	C_ISLNK		0120000
#define	C_ISSOCK	0140000

#define	MAGIC		"070707"

#endif  /* _H_CPIO */
