/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/jfs/fsvar.h 1.3                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1992          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)42	1.3  src/bos/usr/include/jfs/fsvar.h, syspfs, bos530 12/9/92 08:13:26 */
/*
 * COMPONENT_NAME: (SYSPFS) Physical File System
 *
 * FUNCTIONS: fsvar.h
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

#ifndef _H_JFS_FSVAR
#define _H_JFS_FSVAR

#include <jfs/genalloc.h>

/*
 * Congregation of file system variables to ease debugging and 
 * post mordems.
 */
struct fsvar {
	int		v_ninode;	/* initial allocation of inodes */
	genalloc_t	*v_inode;	/* Inode allocation information */
	int		v_nmount;	/* initial allocation of mounts */
	genalloc_t	*v_mount;	/* Mount allocation information */
	int		v_nfile;	/* initial allocation of files */
	genalloc_t	*v_file;	/* File allocation information */
	int		v_nflock;	/* initial allocation for file locks */ 
	genalloc_t	*v_flock;	/* Lock table allocation information */
	int		v_ndevinode;	/* initial allocation of dev inodes */
	genalloc_t	*v_devinode;	/* Dev inode allocation information */
	int		v_ndquot;	/* initial allocation of dquots */
	genalloc_t	*v_dquot;	/* Dquot allocation information */
	int		v_nspare3;
	genalloc_t	*v_spare3;
};

#endif /* _H_JFS_FSVAR */
