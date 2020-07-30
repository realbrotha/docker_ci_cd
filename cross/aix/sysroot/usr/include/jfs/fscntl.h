/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/jfs/fscntl.h 1.3                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1998          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)50	1.3  src/bos/usr/include/jfs/fscntl.h, syspfs, bos530 5/22/98 10:08:48 */
/*
 * COMPONENT_NAME: (SYSPFS) Physical File System
 *
 * FUNCTIONS: fscntl.h
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1989, 1996
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _H_JFS_FSCNTL
#define _H_JFS_FSCNTL

#include <sys/types.h>
#include <jfs/fsdefs.h>

/* 'cmd' args for fscntl system call
 */
#define JFS_EXTENDFS		1	/* extend file system    */
#define JFS_MOVEBLKS            2       /* move blocks (defrag)  */
#define JFS_EXTENDFS_EXTRA      3	/* ext and overalloc map */
#define JFS_GET_FSINFO          4	/* get jfs specific info  */

/* compatibility defines
 */
#define	FS_EXTENDFS	  JFS_EXTENDFS		
#define	FS_MOVEBLKS	  JFS_MOVEBLKS		
#define FS_EXTENDFS_EXTRA JFS_EXTENDFS_EXTRA	

/* struct for JFS_MOVEBLKS 
 */
struct plist
{
	ino32_t	ino;		/* inode number of file */
	uint	gen;		/* inode generation number */
	uint	pno;		/* page number in file */
	frag_t  oldfrag;	/* current frag_t for bno */
	frag_t  newfrag;	/* new proposed frag_t for bno */
	int	commit;		/* 0 no commit, otherwise commit */
};

 
/* struct for JFS_GET_FSINFO
 */
struct jfs_info
{
        int	j_fragsize;     /* file system fragment size            */  
        int     j_blksize;      /* file system block size               */
        int     j_agsize;       /* allocation group size                */
        int     j_iagsize;      /* inode allocation group size          */
	int	j_reserved1;
        int     j_freefrags;    /* number of free fragments             */
	int	j_reserved2;
        int     j_totalfrags;   /* total size of JFS in fragments	*/
	dev32_t	j_jfsdev;	/* device number for file system	*/
        dev32_t j_logdev;       /* device number for log                */
        int	j_logserial;    /* log serial number			*/
	int	j_compress;	/* comp algorithm type       		*/
	int	j_bigexp;	/* log2 big alloc multiplier 		*/
	int	j_supvers;	/* superblock version number 		*/
	char	j_jfstype;	/* see defines below         		*/
	char	j_supfmod;	/* superblock mode (s_fmod)  		*/
	short	j_reserved3;
	int	j_reserved4;
	offset_t j_maxfilesize;	/* max file size (bytes)		*/
	int	j_reserved5[14];
};

/* defines for j_jfstype
 */
#define JFS_VER3COMPAT	0	/* can be exported backwards to v3 machine */
#define JFS_STANDARD	1	/* 4k fragment size, but not v3 compatible */
#define JFS_FRAGMENTS	2	/* fragment size < 4k, but not compressed  */
#define JFS_COMPRESSED	3	/* compressed file system		   */
#define JFS_LARGEFILE	4	/* large file enabled file system	   */

#endif /* _H_JFS_FSCNTL */
