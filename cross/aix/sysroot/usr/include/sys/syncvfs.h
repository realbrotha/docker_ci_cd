/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/syncvfs.h 1.2                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2003,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)25       1.2  src/bos/kernel/sys/syncvfs.h, syslfs, bos530 2/17/04 18:16:00 */

#ifndef _H_SYNCVFS
#define _H_SYNCVFS

/* exported syncvfs interface */

/* Command granularity */
#define FS_SYNCVFS_ALL      0x00  /* All FS */
#define FS_SYNCVFS_FSTYPE   0x10  /* specific FS type */
#define FS_SYNCVFS_FS       0x20  /* specific FS */

/* Command level */
#define FS_SYNCVFS_TRY      0x00 /* Try each */
#define FS_SYNCVFS_FORCE    0x01 /* Force each (don't defer) */ 
#define FS_SYNCVFS_QUIESCE  0x02 /* Force, and get hidden metadata */

#ifdef __cplusplus
extern "C" {
#endif

int syncvfs(char *, int);

#ifdef __cplusplus
}
#endif	

#endif /* _H_SYNCVFS */
