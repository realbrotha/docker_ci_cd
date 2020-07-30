/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#pragma ident	"@(#)io.d.in	1.5	06/04/05 SMI"

#pragma D depends_on module unix
#pragma D depends_on provider io

inline int B_BUSY = 0x0001;
#pragma D binding "1.0" B_BUSY
inline int B_DONE = 0x0002;
#pragma D binding "1.0" B_DONE
inline int B_ERROR = 0x0004;
#pragma D binding "1.0" B_ERROR
inline int B_PAGEIO = 0x0010;
#pragma D binding "1.0" B_PAGEIO
inline int B_PHYS = 0x0020;
#pragma D binding "1.0" B_PHYS
inline int B_READ = 0x0040;
#pragma D binding "1.0" B_READ
inline int B_WRITE = 0x0100;
#pragma D binding "1.0" B_WRITE
inline int B_ASYNC = 0x000400;
#pragma D binding "1.0" B_ASYNC

typedef struct bufinfo {
	int b_flags;			/* buffer status */
	size_t b_bcount;		/* number of bytes */
	caddr_t b_addr;			/* buffer address */
	uint64_t b_lblkno;		/* block # on device */
	uint64_t b_blkno;		/* expanded block # on device */
	size_t b_resid;			/* # of bytes not transferred */
	size_t b_bufsize;		/* size of allocated buffer */
	caddr_t b_iodone;		/* I/O completion routine */
	int b_error;			/* expanded error field */
	dev_t b_edev;			/* extended device */
} bufinfo_t;

#pragma D binding "1.0" translator
translator bufinfo_t < struct buf *B > {
	b_flags = B->b_flags;
	b_addr = B->b_un.b_addr;
	b_bcount = B->b_bcount;
	b_lblkno = B->_b_blkno._f;
	b_blkno = sizeof (long) == 8 ? B->_b_blkno._f : B->_b_blkno._p._l;
	b_resid = B->b_resid;
	b_bufsize = B->b_bufsize;
	b_iodone = (caddr_t)B->b_iodone;
	b_error = B->b_error;
	b_edev = B->b_edev;
}; 

typedef struct devinfo {
	int dev_major;			/* major number */
	int dev_minor;			/* minor number */
	int dev_instance;		/* instance number */
	string dev_name;		/* name of device */
	string dev_statname;		/* name of device + instance/minor */
	string dev_pathname;		/* pathname of device */
} devinfo_t;

#pragma D binding "1.0" translator
translator devinfo_t < struct buf *B > {
	dev_major = B->b_dip != NULL ? getmajor(B->b_edev) :
	    getmajor(B->b_file->v_vfsp->vfs_dev);
	dev_minor = B->b_dip != NULL ? getminor(B->b_edev) :
	    getminor(B->b_file->v_vfsp->vfs_dev);
	dev_instance = B->b_dip == NULL ? 
	    getminor(B->b_file->v_vfsp->vfs_dev) :
	    ((struct dev_info *)B->b_dip)->devi_instance;
	dev_name = B->b_dip == NULL ? "nfs" :
	    stringof(`devnamesp[getmajor(B->b_edev)].dn_name);
	dev_statname = strjoin(B->b_dip == NULL ? "nfs" :
	    stringof(`devnamesp[getmajor(B->b_edev)].dn_name),
	    lltostr(B->b_dip == NULL ? getminor(B->b_file->v_vfsp->vfs_dev) :
	    ((struct dev_info *)B->b_dip)->devi_instance == 0 &&
	    ((struct dev_info *)B->b_dip)->devi_parent != NULL &&
	    ((struct dev_info *)B->b_dip)->devi_parent->devi_node_name ==
	    "pseudo" ? getminor(B->b_edev) :
	    ((struct dev_info *)B->b_dip)->devi_instance));
	dev_pathname = B->b_dip == NULL ? "<nfs>" :
	    ddi_pathname(B->b_dip, getminor(B->b_edev));
};

typedef struct fileinfo {
	string fi_name;			/* name (basename of fi_pathname) */
	string fi_dirname;		/* directory (dirname of fi_pathname) */
	string fi_pathname;		/* full pathname */
	offset_t fi_offset;		/* offset within file */
	string fi_fs;			/* filesystem */
	string fi_mount;		/* mount point of file system */
	int fi_oflags;			/* open(2) flags for file descriptor */
} fileinfo_t;

#pragma D binding "1.0" translator
translator fileinfo_t < struct buf *B > {
	fi_name = B->b_file == NULL ? "<none>" :
	    B->b_file->v_path == NULL ? "<unknown>" :
	    basename(cleanpath(B->b_file->v_path));
	fi_dirname = B->b_file == NULL ? "<none>" :
	    B->b_file->v_path == NULL ? "<unknown>" :
	    dirname(cleanpath(B->b_file->v_path));
	fi_pathname = B->b_file == NULL ? "<none>" :
	    B->b_file->v_path == NULL ? "<unknown>" :
	    cleanpath(B->b_file->v_path);
	fi_offset = B->b_offset;
	fi_fs = B->b_file == NULL ? "<none>" :
	    stringof(B->b_file->v_op->vnop_name);
	fi_mount = B->b_file == NULL ? "<none>" :
	    B->b_file->v_vfsp->vfs_vnodecovered == NULL ? "/" :
	    B->b_file->v_vfsp->vfs_vnodecovered->v_path == NULL ? "<unknown>" :
	    cleanpath(B->b_file->v_vfsp->vfs_vnodecovered->v_path);
	fi_oflags = 0;
};

/*
 * The following inline constants can be used to examine fi_oflags when using
 * the fds[] array or a translated fileinfo_t.  Note that the various open
 * flags behave as a bit-field *except* for O_RDONLY, O_WRONLY, and O_RDWR.
 * To test the open mode, you write code similar to that used with the fcntl(2)
 * F_GET[X]FL command, such as: if ((fi_oflags & O_ACCMODE) == O_WRONLY).
 */
inline int O_ACCMODE = 3;
#pragma D binding "1.1" O_ACCMODE

inline int O_RDONLY = 0;
#pragma D binding "1.1" O_RDONLY
inline int O_WRONLY = 1;
#pragma D binding "1.1" O_WRONLY
inline int O_RDWR = 2;
#pragma D binding "1.1" O_RDWR

inline int O_APPEND = 0x08;
#pragma D binding "1.1" O_APPEND
inline int O_CREAT = 0x100;
#pragma D binding "1.1" O_CREAT
inline int O_DSYNC = 0x40;
#pragma D binding "1.1" O_DSYNC
inline int O_EXCL = 0x400;
#pragma D binding "1.1" O_EXCL
inline int O_LARGEFILE = 0x2000;
#pragma D binding "1.1" O_LARGEFILE
inline int O_NOCTTY = 0x800;
#pragma D binding "1.1" O_NOCTTY
inline int O_NONBLOCK = 0x80;
#pragma D binding "1.1" O_NONBLOCK
inline int O_NDELAY = 0x04;
#pragma D binding "1.1" O_NDELAY
inline int O_RSYNC = 0x8000;
#pragma D binding "1.1" O_RSYNC
inline int O_SYNC = 0x10;
#pragma D binding "1.1" O_SYNC
inline int O_TRUNC = 0x200;
#pragma D binding "1.1" O_TRUNC
inline int O_XATTR = 0x4000;
#pragma D binding "1.1" O_XATTR

#pragma D binding "1.1" translator
translator fileinfo_t < struct file *F > {
	fi_name = F == NULL ? "<none>" :
	    F->f_vnode->v_path == NULL ? "<unknown>" :
	    basename(cleanpath(F->f_vnode->v_path));
	fi_dirname = F == NULL ? "<none>" :
	    F->f_vnode->v_path == NULL ? "<unknown>" :
	    dirname(cleanpath(F->f_vnode->v_path));
	fi_pathname = F == NULL ? "<none>" :
	    F->f_vnode->v_path == NULL ? "<unknown>" :
	    cleanpath(F->f_vnode->v_path);
	fi_offset = F == NULL ? 0 : F->f_offset;
	fi_fs = F == NULL ? "<none>" : stringof(F->f_vnode->v_op->vnop_name);
	fi_mount = F == NULL ? "<none>" :
	    F->f_vnode->v_vfsp->vfs_vnodecovered == NULL ? "/" :
	    F->f_vnode->v_vfsp->vfs_vnodecovered->v_path == NULL ? "<unknown>" :
	    cleanpath(F->f_vnode->v_vfsp->vfs_vnodecovered->v_path);
	fi_oflags = F == NULL ? 0 : F->f_flag + (int)0xffffffff;
};

inline fileinfo_t fds[int fd] = xlate <fileinfo_t> (
    fd >= 0 && fd < curthread->t_procp->p_user.u_finfo.fi_nfiles ?
    curthread->t_procp->p_user.u_finfo.fi_list[fd].uf_file : NULL);

#pragma D attributes Stable/Stable/Common fds
#pragma D binding "1.1" fds

#pragma D binding "1.2" translator
translator fileinfo_t < struct vnode *V > {
	fi_name = V->v_path == NULL ? "<unknown>" :
	    basename(cleanpath(V->v_path));
	fi_dirname = V->v_path == NULL ? "<unknown>" :
	    dirname(cleanpath(V->v_path));
	fi_pathname = V->v_path == NULL ? "<unknown>" : cleanpath(V->v_path);
	fi_fs = stringof(V->v_op->vnop_name);
	fi_mount = V->v_vfsp->vfs_vnodecovered == NULL ? "/" :
	    V->v_vfsp->vfs_vnodecovered->v_path == NULL ? "<unknown>" :
	    cleanpath(V->v_vfsp->vfs_vnodecovered->v_path);
};
