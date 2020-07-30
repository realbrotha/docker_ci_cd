/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/sys/gfs.h 1.30                                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)00     1.30  src/bos/kernel/sys/gfs.h, syslfs, bos53H, h2006_07C4 2/9/06 10:52:05 */


/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 */

#ifndef _H_GFS
#define _H_GFS

#include <sys/types.h>
#include <sys/lock_def.h>

struct vfsops;
struct vnodeops;

extern Simple_lock gfs_lock;		/* GFS Table lock */

struct gfs {
	struct vfsops	*gfs_ops;
	struct vnodeops	*gn_ops;
	int		gfs_type;	/* type of gfs (from <sys/vmount.h>) */
	char		gfs_name[16];	/* name of vfs (eg. "jfs","nfs", ...)*/
	int		(*gfs_init)(struct gfs *);  /* ( gfsp ) - if ! NULL, */
					/*   called once to init gfs */
	int		gfs_flags;	/* flags for gfs capabilities */
	caddr_t		gfs_data;	/* ptr to gfs's private config data */
	int		(*gfs_rinit)(void);
	int             gfs_hold;       /* count of mounts of this gfs type  */
};

/* The new_root structure is passed through the sysconfig system
 * call to announce a new root file system device and type.  This
 * does not take effect until process 1 (ie. init) exits.
 */
struct new_root {
	dev_t		nr_dev;		/* device number of root gfs	*/
	int		nr_gfs_type;	/* new root's gfs type		*/
	char		nr_misc[32];	/* misc parameters, interpeted
					   by the new gfs's initialization
					   routine			*/
};

/* defines for gfs_flags */
#define GFS_SYS5DIR	0x00000001	/* directory entries are 16 bytes */
#define GFS_REMOTE	0x00000002	/* this is a remote file system */
#define	GFS_INIT	0x00000004	/* gfs has been initialized	*/
#define	GFS_FUMNT	0x00000008	/* gfs supports forced umount	*/
#define	GFS_VERSION4	0x00000010	/* gfs modified for AIX version 4 */ 
#define GFS_VERSION42	0x00000020	/* gfs modified for AIX version 4.2 */ 
#define GFS_NOUMASK	0x00000040	/* should umask be applied	*/
#define GFS_VERSION421	0x00000080	/* gfs modified for AIX 421	*/
#define GFS_VERSION43	0x00000100	/* gfs modified for AIX 4.3	*/
#define GFS_MEMCNTL	0x00000200	/* new memcntl vnode operation	*/
#define GFS_SYNCVFS     0x00000400      /* syncvfs vnode op */
#define GFS_VREGSEL	0x00000800	/* gfs wants select vnode op    */
                   	          	/* called for VREG files        */ 
#define GFS_NO_ACCT	0x00001000	/* don't do fs acct on this file system */
#define GFS_NAMED_OPEN  0x00002000	/* gfs uses named opens */
#define GFS_VERSION53	0x00004000	/* gfs modified for AIX 5.3     */ 
					/* expend vfs ops to 16		*/
#define GFS_STATFSVP	0x00008000	/* statfs call will be base on	*/
					/* a vnode instead of vfs	*/
#define GFS_DIROP	0x00010000	/* call parent vnop instead of object */
#define GFS_FASTPATH	0x00020000	/* gfs supports AIO fast path 	*/


#if defined(__64BIT_KERNEL) || defined( __FULL_PROTO)
int gfsadd(int, struct gfs *);
int gfsdel(int);
#endif /* 64BIT_KERNEL || __FULL_PROTO */

#endif /* _H_GFS */

