/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/fp_io.h 1.20.2.3                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,2010              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)26     1.20.2.3  src/bos/kernel/sys/fp_io.h, syslfs, bos53X, x2010_31A9 4/27/10 16:00:52 */

/*
 * COMPONENT_NAME: (SYSLFS) Logical File System
 *
 * FUNCTIONS:
 *
 * ORIGINS: 27
 *
 * Copyright International Business Machines Corp. 1988
 * All Rights Reserved
 * Licensed Material - Property of IBM
 *
 * RESTRICTED RIGHTS LEGEND
 * Use, Duplication or Disclosure by the Government is subject to
 * restrictions as set forth in paragraph (b)(3)(B) of the Rights in
 * Technical Data and Computer Software clause in DAR 7-104.9(a).
 */

#ifndef	_H_FP_IO
#define	_H_FP_IO

#include <sys/file.h>
#include <sys/uio.h>
#include <sys/ras.h>

/* fpflag values for fp_open() */
#define FP_USR	 	0x00000000	/* file name in user space */
#define FP_SYS	 	0x00000001	/* file name in kernel space */

#ifdef _KERNEL

#ifndef _NO_PROTO
/* These functions are exported for use by kernel extensions and are	*/
/* available for use by the kernel also.  Eventually there should be	*/
/* "fp_" functions for all services provided by the logical file system	*/
/* to the kernel and kernel extensions.  Currently other functions are	*/
/* provided for individual components that need them.  The caller of	*/
/* these functions does not need to have the kernel lock.  All of these	*/
/* functions return a errno style error code.  The caller is		*/
/* responsible for setting u.u_error if the return code is non-zero.	*/

/* open file by name, create file if (oflags | O_CREATE), return a	*/
/* file pointer								*/
extern
int
fp_open (
	char *		path,		/* path to file to open		*/
	int32long64_t	oflags,		/* open() style flags		*/
	int		mode,		/* perms for file if O_CREATE	*/
	ext_t		ext,		/* device driver specific data	*/
	int		fpflag,		/* fp flags:  FP_USR or FP_SYS	*/
	struct file **	fpp);		/* file pointer return address	*/

/* open file by name for execution, return a file pointer and last	*/
/* component of file name; used by exec code				*/
extern
int
fp_xopen (
	char *		fname,		/* path to file to open		*/
	int		fpflag,		/* fp flags:  FP_USR or FP_SYS	*/
	int32long64_t	oflag,		/* open() style flags		*/
	caddr_t		basename,	/* last component of pathname	*/
	uint		basenamelen,	/* basename buffer length	*/
	struct file **	fpp);		/* file pointer return address	*/

/* open a device for kernel use only					*/
extern
int
fp_opendev (
	dev_t		devno,		/* device number of dev to open	*/
	int		flags,		/* device flags:  DREAD, DWRITE	*/
	caddr_t		cname,		/* channel name string		*/
	ext_t		ext,		/* device driver specific data	*/
	struct file **	fpp);		/* file pointer return address	*/


/* return the file pointer associated with a file descriptor		*/
extern
int
fp_getf (
	int		fd,		/* file descriptor of file ptr	*/
	struct file **	fp);		/* file pointer return address	*/


/* allocate a file descriptor associated with a file pointer		*/
extern
int
fp_ufdgetf (
	struct file    *fp);		/* file ptr of file descriptor	*/

/* return the file pointer associated with a file descriptor; this	*/
/* is intended for lfs use only						*/
extern
int
getf (
	int		fd,		/* file descriptor of file ptr	*/
	struct file **	fpp);		/* file pointer return address	*/

/* return the first available file descriptor greater than or equal to	*/
/* startfd								*/
extern
int
ufdalloc (
	int		startfd,	/* first file desc to check	*/
	int *		fdp);		/* file descriptor return addr	*/

/* free a file descriptor						*/
extern
void
ufdfree (
	int		fd);		/* file descriptor to free	*/

/* reserve the file descriptor  */
extern
int
ufdreserve (
        int             fd);

/* set the file descriptor  */
extern
void
ufdsetf (
        int             fd,
	struct file *	fp);

/* definitions of special kernel global variables that keep addresses
 * of aio functions desired to be run by other extensions
 * They are set to NULL when defined and set when AIO(LEGACY/POSIX) is loaded.
 */
extern 
int 
(*ptx_kaio_stats)(
	caddr_t *	buf,		/* receiving buf	*/
	int		len,		/* length of buffer 	*/
	int		flag);		/* indicates which stat */

extern 
int 
(*ptx_aio_cntl)(
	int		cmd, 		/* type of operation */
	int		opt,            /* which parameter to change */
	int		value);         /* new value of specified option */

extern 
int 
(*ptx_posix_kaio_stats)(
	caddr_t *	buf,		/* receiving buf	*/
	int		len,		/* lenght of buffer	*/
	int		flag);		/* indicates which stat */

extern 
int 
(*ptx_posix_aio_cntl)(
	int		cmd,		/* type of operation */
	int		opt,		/* which parameter to change */
	int		value);		/* new value of specified option */

/* aio fast path communication */
#define AIO_FAST_PATH_ID	0x41494F46	/* AIOF */
#define AIO_FAST_PATH_VERSION_1	1
struct aio_fsfp
{
	eye_catch4b_t	aioFastPath_id;
	int		aioFastPath_version;
	void		(*aioFPdone)(int64, int, int64);
	int64		aioTracker;
};

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)

/* get the device number of the device associated with fp		*/
extern
int
fp_getdevno (
	struct file *   fp,		/* file pointer			*/
	dev_t *         devp,		/* device number return address */
	chan_t *        chanp);		/* channel return address	*/

/* return the file pointer associated with a held file descriptor	*/
extern int
ufdgetf (
	int		fd,		/* file descriptor of file ptr	*/
	struct file **	fp);		/* file pointer return address	*/

/* create a file descriptor/file struct pair				*/
extern int
ufdcreate(
	int32long64_t	flags,		/* flags for file struct	*/
	struct fileops *ops,		/* list	of file	op routines	*/
	void *		datap,		/* address of dependent	structs */
	short		type,		/* type value for file struct	*/
	int *		fdp,		/* address of file descriptor	*/
	struct ucred *	crp);		/* cred to store in file struct */

/* put a hold count on a file descriptor				*/
extern int
ufdhold(int fd);                        /* file descriptor		*/

/* release a hold count on a file descriptor				*/
extern int
ufdrele(int fd);                        /* file descriptor              */

/* We can not include sys/user.h since that causes a build break.	*/
struct	user;

/* lock a file descriptor with a non-standard ublock address		*/
void
ufdlock_u(
	int		fd,		/* file descriptor		*/
	struct user *	up);		/* ublock->user pointer		*/

/* unlock a file descriptor with a non-standard ublock address		*/
void
ufdunlock_u(
	int		fd,		/* file descriptor		*/
	struct user *	up);		/* ublock->user pointer		*/

/* get the flags from a file descriptor					*/
extern int
getufdflags(int fd,                     /* file descriptor		*/
	    int * flagsp);              /* pointer to flags for fd	*/

/* set the flags for a file descriptor (only close on exec is valid)	*/
extern int
setufdflags(int fd,                     /* file descriptor		*/
	    int flags);                 /* FD_CLOEXEC or 0		*/

/* set the UF_POLLED flag for a file descriptor				*/
extern int
setufdflags_polled(int fd, struct file **fpp);	/* file descriptor	*/

/* get the file creation mask for the running process			*/
extern int
get_umask(void);

/* search the system file table, executing 'ftecheck' routine for each	*/
/* entry of specified type that is currently in use			*/
extern int
ftsearch(int (*ftecheck) (struct file *fp, void *checkarg),
         int   type,
         void *checkarg);
#endif /* __64BIT_KERNEL || __FULL_PROTO */

/************************************************************************/
/* These functions are for use by logical file system functions only.	*/

/* allocate and return a file pointer of the appropriate type for a	*/
/* given vnode								*/
extern
int
fpalloc (
	struct vnode *	vp,		/* vnode pointer to attach	*/
	int32long64_t	flag,		/* file flag value to use	*/
	int		type,		/* file pointer type to use	*/
	struct fileops *ops,		/* file operations to attach	*/
	struct file **	fpp);		/* file pointer return address	*/

extern
int
fp_ufalloc (	struct file *	fp);

extern
void
fp_hold (
		struct file *	fp);

extern
void
ffree (		struct file *	fp);
/************************************************************************/

#if defined(__64BIT_KERNEL) || defined(__FULL_PROTO)
extern int
fp_read (	struct file *	fp,
		char *		buf,
		ssize_t		nbytes,
		ext_t		ext,
		int		seg,
		ssize_t *	countp);
extern int
fp_readv (	struct file *	fp,
		struct iovec *	iov,
		ssize_t		iovcnt,
		ext_t		ext,
		int		seg,
		ssize_t *	countp);
extern int
fp_write (	struct file *	fp,
		char *		buf,
		ssize_t		nbytes,
		ext_t		ext,
		int		seg,
		ssize_t *	countp);
extern int
fp_writev (	struct file *	fp,
		struct iovec *	iov,
		ssize_t		iovcnt,
		ext_t		ext,
		int		seg,
		ssize_t *	countp);
extern int
fp_ioctl (	struct file *	fp,
		unsigned long	cmd,
		caddr_t		arg, 
		ext_t		ext);
extern int
fp_ioctlx (	struct file *	fp,
		unsigned long	cmd,
		caddr_t		arg, 
		ext_t		ext,
		unsigned long	flags,
		long *		retval);

#else  /* __64BIT_KERNEL || __FULL_PROTO */

extern
int
fp_read (	struct file *	fp,
		char *		buf,
		int		nbytes,
		ext_t		ext,
		int		seg,
		int *		countp);
extern
int
fp_readv (	struct file *	fp,
		struct iovec *	iov,
		int		iovcnt,
		ext_t		ext,
		int		seg,
		int *		countp);
extern
int
fp_write (	struct file *	fp,
		char *		buf,
		int		nbytes,
		ext_t		ext,
		int		seg,
		int *		countp);
extern
int
fp_writev (	struct file *	fp,
		struct iovec *	iov,
		int		iovcnt,
		ext_t		ext,
		int		seg,
		int *		countp);
extern
int
fp_ioctl (	struct file *	fp,
		unsigned int	cmd,
		caddr_t		arg,
		... );
extern 
int
fp_ioctlx (	struct file *	fp,
		unsigned int	cmd,
		caddr_t		arg, 
		ext_t		ext,
		unsigned long	flags,
		long *		retval);

#endif /* __64BIT_KERNEL || __FULL_PROTO */

extern
int
fp_rwuio (	struct file *	fp,
		enum uio_rw	rw,
		struct uio *	uiop,
		ext_t		ext);
extern
int
fp_lseek (	struct file *	fp,
		off_t		offset,
		int		whence);

#ifdef _LONG_LONG
extern
int
fp_llseek (	struct file *	fp,
		offset_t	offset,
		int		whence);
#endif

extern
int
fp_close (	struct file *	fp);

extern
int
fp_fstat(	struct file	*fp,
		struct stat	*statp,
		int		 len,
		int		 seg);

extern
int
fp_access(	struct file	*fp,
		int		 perm);

#if defined(__64BIT_KERNEL) || defined( __FULL_PROTO)
extern int
fp_revoke(	struct file	*fp,
		int		flag);

extern int
fp_select(	struct file	*fp,
		ushort		reqevents,
		ushort		*rtneventsp,
		void		(*notify)());
#endif /* __64BIT_KERNEL || __FULL_PROTO */

extern int
fp_fsync(	struct file	*fp,
		int		how,
		offset_t	off,
		offset_t	len);
extern int
fp_ftruncate(	struct file	*fp,
		int		flag,
		offset_t	len);


/* These functions are only for use within the kernel.  Their use	*/
/* should be minimized.  They will probably be replaced at a future	*/
/* date.								*/

/* return the file pointer associated with a file descriptor;  avoids	*/
/* security checking;  THIS MUST ONLY BE CALLED BY close() AND exit()	*/
extern
int
getfx (		int		fd,	/* file descriptor of file ptr	*/
		struct file **	fpp);	/* file pointer return address	*/

/* return the file pointer associated with a file descriptor after	*/
/* validating the type							*/
extern
int
getft (		int		fd,	/* file descriptor of file ptr	*/
		struct file **	fpp,	/* file pointer return address	*/
		int		want);	/* file ptr type to validate	*/

#else /* _NO_PROTO */

extern int	fp_open();
extern int	fp_xopen();
extern int	fp_opendev();
extern int	fp_getdevno();
extern int	fp_getf();
extern int	fp_ufdgetf();
extern int	getf();
extern int	ufdalloc();
extern void	ufdfree();
extern int	ufdreserve();
extern int 	(*ptx_kaio_stats)();
extern int 	(*ptx_aio_cntl)();
extern int 	(*ptx_posix_kaio_stats)();
extern int 	(*ptx_posix_aio_cntl)();
extern int	ufdcreate();
extern int	ufdgetf();
extern int	ufdhold();
extern int	ufdrele();
extern void	ufdlock_u();
extern void	ufdunlock_u();
extern int	getufdflags();
extern int	setufdflags();
extern int	get_umask();
extern int	ftsearch();
extern int	fpalloc();
extern int	fp_ufalloc();
extern void	fp_hold();
extern void	ffree();
extern int	fp_read();
extern int	fp_readv();
extern int	fp_write();
extern int	fp_writev();
extern int	fp_rwuio();
extern int	fp_lseek();
extern int	fp_llseek();
extern int	fp_ioctl();
extern int	fp_ioctlx();
extern int	fp_close();
extern int	fp_fstat();
extern int	fp_access();
extern int	fp_revoke();
extern int	fp_select();
extern int	getfx();
extern int	getft();
extern int	fp_fsync();
extern int	fp_ftruncate();

#endif /* _NO_PROTO */
#endif /* _KERNEL */

#endif	/* _H_FP_IO */


