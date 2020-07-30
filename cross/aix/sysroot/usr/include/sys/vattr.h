/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/vattr.h 1.12.1.11                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1985,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)35	1.12.1.11  src/bos/kernel/sys/vattr.h, syslfs, bos530 9/29/99 11:09:31 */
#ifndef _H_VATTR
#define _H_VATTR

/*
 * COMPONENT_NAME: SYSLFS - Logical File System
 */

#include <sys/types.h>
#include <sys/vnode.h>
#include <sys/time.h>
#include <sys/priv.h>

/*
 * Structure describing the attributes of files across all
 * the types of file systems which are supported.  This is
 * a superset of the AIX stat structure's fields.
 */
struct vattr
{
	enum vtype	va_type;	/* vnode type			*/
	mode_t	va_mode;		/* access mode			*/
	uid_t	va_uid;			/* owner uid			*/
	gid_t	va_gid;			/* owner gid			*/
	union {
		dev_t	_va_dev;	/* id of device containing file	*/
		long	_va_fsid;	/* fs id (dev for now)		*/
	} _vattr_union;
	ino_t	va_serialno;		/* file serial (inode) number	*/
	short	va_nlink;		/* number of links		*/
	short	va_flags;		/* Flags, see below for define  */
	long	va_mask;		/* Initial attribute mask	*/
	offset_t	va_size;	/* file size in bytes		*/
	blksize_t	va_blocksize;	/* preferred blocksize for io	*/
	blkcnt_t	va_blocks;	/* kbytes of disk held by file	*/
	struct	timestruc_t  va_atime; 	/* time of last access */
	struct	timestruc_t  va_mtime;	/* time of last data modification */
	struct	timestruc_t  va_ctime;	/* time of last status change */
	dev_t	va_rdev;		/* id of device			*/

	/* Fields added for compatability with the fullstat structure */
	long	va_nid;			/* node id			*/
	chan_t	va_chan;		/* channel of MPX device */
	char	*va_acl;		/* Access Control List */
	size_t	va_aclsiz;		/* size of ACL */
	int	va_gen;			/* inode generation number */
};
typedef struct vattr vattr_t;

#define	va_dev	_vattr_union._va_dev
#define	va_fsid	_vattr_union._va_fsid

/*
 * Flag definitions
 */
#define	VA_NOTAVAIL	0x0001	/* response to attribute request on lookup or
				 * rdwr when attributes cannot be returned
				 */

/*
 * time in vattr in now two longs, but some measure of back compatibility
 * is maintained, the short times are "tim" vs "time"
 */
#define	va_atim	va_atime.tv_sec
#define	va_mtim	va_mtime.tv_sec
#define	va_ctim	va_ctime.tv_sec

/*
 * Values known to the vn_setattr
 * Must be mutually exclusive
 */
#define	V_MODE	0x01
#define	V_OWN	0x02
#define	V_UTIME	0x04
#define V_STIME	0x08


/* 
 * The following are flags for use in the timeflg (arg1) field of
 * VNOP_SETATTR call. (comment them well, this is the only place
 * they are documented.
 */

	/* 
	 * NOTE:
	 * Only flags in the range of 00100-04000 may be used,
	 * those lower than this are used in chownx.h.
	 */
#define T_SETTIME	0200	/* Used in V_UTIME to tell the vnode
				 * op that the user requested the
				 * times be set to system time.
				 */

/*
 * va_mask values, passed to vnop_create_attr to specify which attributes
 * should be used.  Each bit corresponds to a field in the vattr structure
 * although only some are significant for create.
 */

#define AT_TYPE         (1<<0)
#define AT_MODE         (1<<1)
#define AT_UID          (1<<2)
#define AT_GID          (1<<3)
#define AT_FSID         (1<<4)
#define AT_SERIAL       (1<<5)
#define AT_NLINK        (1<<6)
#define AT_FLAGS        (1<<7)
#define AT_SIZE         (1<<8)
#define AT_BLKSIZ       (1<<9)
#define AT_BLOCKS       (1<<10)
#define AT_ATIME        (1<<11)
#define AT_MTIME        (1<<12)
#define AT_CTIME        (1<<13)
#define AT_RDEV         (1<<14)
#define AT_NID          (1<<15)
#define AT_CHAN         (1<<16)
#define AT_ACL          (1<<17)
#define AT_ACLSIZ       (1<<18)
#define AT_GEN          (1<<19)
#define AT_LAST         AT_GEN

#define AT_NOSET        0
#define AT_ALL          ((AT_LAST<<1)-1)


#ifdef	_KERNSYS
#ifndef _H_INLINE
#include <sys/inline.h>
#endif

/* Handy macro for fetching tod guarding against
 * rollover from the nsec to sec fields.
 */
#define	FETCH_TOD(t)	get_tod(&tod, &t);

#endif	/* _KERNSYS */

#endif	/* _H_VATTR */
