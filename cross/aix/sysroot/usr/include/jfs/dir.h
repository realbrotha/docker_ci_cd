/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/jfs/dir.h 1.4                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1998          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)39	1.4  src/bos/usr/include/jfs/dir.h, syspfs, bos530 5/22/98 10:08:32 */
/*
 * SYSPFS: journalled filesystem
 *
 * FUNCTIONS: dir.h
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

#ifndef _H_JFS_DIR
#define _H_JFS_DIR

/*
 * Internal directory routine argument type
 */
typedef	struct {
	caddr_t nm;
	int	nmlen;
} dname_t;

struct direct {
	ino32_t		d_ino;
	ushort		d_reclen;
	ushort		d_namlen;
	char		d_name[MAXNAMLEN+1];	/* NULL terminated	*/
};

typedef struct direct direct_t;

#	define	DIROUND	4
#	define	LDIRECLEN(dirp)	((struct direct *)dirp->d_reclen)
#	define	LDIRSIZE(len)	((sizeof(struct direct) - (MAXNAMLEN+1) + \
		((len)+1) + (DIROUND-1)) & ~(DIROUND-1))
#	define	LDIRNMLEN(dirp)	(dirp->d_namlen)

#define	DOT_EXIST	0x1
#define DOT_VALID	0x2
#define DDOT_EXIST	0x4
#define DDOT_VALID	0x8
#define DDOT_MASK	0xc
#define DDOT_STAT(d)	((d) & DDOT_MASK)

#endif /* _H_JFS_DIR */
