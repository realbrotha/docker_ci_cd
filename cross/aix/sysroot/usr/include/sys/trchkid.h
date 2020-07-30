/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/trchkid.h 1.96.15.18                         */
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
/* @(#)08     1.96.15.18  src/bos/kernel/sys/trchkid.h, systrace, bos53X, x2010_50B0 9/3/10 13:26:13 */
/*
 * COMPONENT_NAME:            include/sys/trchkid.h
 *
 * FUNCTIONS: header file for system trace hookwords
 *
 * ORIGINS: 27, 83
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 2002
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 * LEVEL 1, 5 Years Bull Confidential Information
 */

/* All major hook id's should begin with HKWD_, and all minor hook id's
   should begin with hkwd_.
*/

#ifndef _H_TRCHKID
#define _H_TRCHKID

#include "sys/trcmacros.h"

#define HKWD_TRACE                0x00000000
#define HKWD_TRACE_SYNC           0x00000000
#define HKWD_TRACE_TRCON          0x00100000
#define HKWD_TRACE_TRCOFF         0x00200000
#define HKWD_TRACE_HEADER         0x00300000
#define HKHDR_UTS		  0x1	/* uts data */
#define HKHDR_CMD		  0x2	/* trace command */
#define HKHDR_ALL		  0x3	/* tracing all hooks */
#define HKHDR_INCL		  0x4	/* tracing only these hooks */
#define HKHDR_EXCL		  0x5	/* Exclude these hooks */
#define HKHDR_HKBM		  0x6	/* traced hooks bit map */
#define HKHDR_MSG 		  0xff	/* message */

#define HKWD_TRACE_NULL           0x00400000
#define HKWD_TRACE_LWRAP          0x00500000
#define HKWD_TRACE_TWRAP          0x00600000
#define HKWD_TRACE_UNDEFINED      0x00700000
#define HKWD_TRACE_DEFAULT        0x00800000
#define HKWD_TRACE_ERR            0x00900000
#define HKWD_TRACE_UTIL           0x00A00000
/* Utility hook types */
#define HKUT_TSYNC 		  0x0	/* Timer sync, 32-bit only */
#define HKUT_PID		  0x1	/* process info */
#define HKUT_LDR		  0x2	/* loader info */
#define HKUT_CPID		  0x3	/* current pid info */
#define HKUT_DEV		  0x4	/* device info */
#define HKUT_IP			  0x5	/* IP addr */
#define HKUT_BUFF		  0x6	/* buffer allocation scheme */
#define HKUT_CPUMAP  		  0x7	/* cpu usage map */
#define HKUT_SYM		  0xc	/* symbol address */
#define HKUT_TIME		  0x25c	/* Time conversion data */
#define HKUT_CPUFILE		  0x10	/* id/name for cpu file */
#define HKUT_CPUF2  		  0x11	/* base logfile for this cpu file */
#define HKUT_CPUS		  0x12	/* total and traced # cpus */
#define HKUT_LDT 		  0x13	/* indicate large data types */
#define HKUT_REGS 		  0x14	/* programmable registers */
#define HKUT_IVALS 		  0x15	/* initial register values */
#define HKUT_LONGPID      	  0x16  /* process info with long process name */
#define HKUT_CTFILE               0x17  /* name for component trace file */
#define HKUT_CTF2                 0x18  /* base logfile for this CT file */
#define HKUT_MTRC_TSYNC           0x19  /* LMT Timestamp, 32-bit only */
#define HKUT_MTRC_SUSPEND         0x1a  /* LMT Suspend,   32-bit only */
#define HKUT_MTRC_RESTART         0x1b  /* LMT Restart,   32-bit only */
#define HKUT_PROC_SLIB            0x1c  /* proc info with named slib */
#define HKUT_VSID_NAME            0x1d  /* VSID to name mapping for slibs */
#define HKUT_DAEMON               0x1e  /* force trace daemon ident into buffer */
#define HKUT_LDR_PROC_LDINFO      0x1f  /* Process memory mapping */

#define HKWD_6432	          0x00B00000	/* 64-bit hook in 32-bit trc */

#define HKWD_USER1                0x01000000
#define HKWD_USER2                0x02000000
#define HKWD_USER3                0x03000000
#define HKWD_USER4                0x04000000
#define HKWD_USER5                0x05000000
#define HKWD_USER6                0x06000000
#define HKWD_USER7                0x07000000
#define HKWD_USER8                0x08000000
#define HKWD_USER9                0x09000000
#define HKWD_USERA                0x0a000000
#define HKWD_USERB                0x0b000000
#define HKWD_USERC                0x0c000000
#define HKWD_USERD                0x0d000000
#define HKWD_USERE                0x0e000000
#define HKWD_USERAIX              0x0f000000

#define HKWD_KERN_FLIH            0x10000000
#define HKWD_KERN_SVC             0x10100000    /* common SVC entry */
#define HKWD_KERN_SLIH            0x10200000
#define HKWD_KERN_SLIHRET         0x10300000
#define HKWD_KERN_SYSCRET         0x10400000    /* common SVC return */
#define HKWD_KERN_LVM             0x10500000    /* LVM bad blk/resync flow */
#define HKWD_KERN_DISPATCH        0x10600000
#define HKWD_KERN_UNDISP          0x4B000000
#define HKWD_KERN_LVMSIMP         0x10B00000    /* LVM simple request flow */
#define HKWD_KERN_IDLE            0x10C00000    /* Dispatching idle process */
#define HKWD_KERN_RELOCK          0x10e00000	/* ownership games wi RQ lock */
#define HKWD_KERN_EOF             0x10f00000
#define HKWD_KERN_STDERR          0x11000000
#define HKWD_KERN_LOCKF           0x11100000
#define HKWD_KERN_LOCK            0x11200000	
#define HKWD_KERN_UNLOCK          0x11300000	
#define HKWD_KERN_LOCKALLOC       0x11400000	
#define HKWD_KERN_SETRECURSIVE    0x11500000	

#define HKWD_KERN_XMALLOC         0x11600000
#define HKWD_KERN_XMFREE          0x11700000
#define HKWD_KERN_FORKCOPY        0x11800000
#define HKWD_KERN_PIDSIG          0x11900000
#define HKWD_KERN_RCVSIGNAL       0x11a00000
#define HKWD_KERN_P_SLIH          0x11c00000
#define HKWD_KERN_SIG_SLIH        0x11d00000
#define HKWD_KERN_ISSIG           0x11e00000
#define HKWD_KERN_SORQ            0x11f00000
#define HKWD_KERN_RESUME          0x20000000
#define HKWD_KERN_HFT             0x20100000
#define HKWD_KERN_KTSM            0x20200000
#define HKWD_KERN_CON             0x20300000
#define HKWD_KERN_SCHED_SWAPIN	  0X20400000
#define HKWD_KERN_SCHED_SWAPOUT   0X20500000
#define HKWD_KERN_SCHED_POST	  0x20600000
#define HKWD_KERN_SCHED		  0x20700000
#define HKWD_KERN_SCHED_STAT	  0x20800000
#define HKWD_KERN_SCHED_STAT1	  0x20900000
#define HKWD_KERN_SCRUB_DISABLE	  0x20A00000
#define HKWD_KERN_SCRUB_ENABLE	  0x20B00000
#define HKWD_KERN_SCRUB_SEG	  0x20C00000
#define HKWD_KERN_SCRUB_SOFT	  0x20D00000
#define HKWD_KERN_LOCKL           0x20E00000
#define HKWD_KERN_UNLOCKL         0x20F00000
#define HKWD_KERN_INITP		  0x21000000
#define HKWD_KERN_PHANTOM_EXTINT  0x47F00000
#define HKWD_KERN_IOPATH_DATA	  0x49100000

/*
 * "sub-hookids"
 */
#define hkwd_VMUIOMOVE_READ	0
#define hkwd_VMUIOMOVE_WRITE	1

#define LOCK_TAKEN          1
#define LOCK_MISS           2
#define LOCK_RECURSIVE      3
#define LOCK_BUSY      	    4

#define SETRECURSIVE        1
#define CLEARRECURSIVE      2


/* *** START FILESYSTEM HOOKS *** */

/* Note: All filesystem related subhooks for kernel filesystem
 * components are in fs_subhook.h
 *
 * AIO related subhooks are in sysxaio_trc.h
 */
#ifdef _KERNEL
#include <sys/fs_subhook.h>
#endif

/*
 * LFS hook and sub-hook ids (Component syslfs)
 */

/* All vnops should appear in the following list: */ 
#define HKWD_VNOP_ACCESS	0x12000000      /* vnop_access */
#define HKWD_VNOP_CLOSE         0x12e00000      /* vnop_close */
#define HKWD_VNOP_CREATE        0x13000000	/* vnop_create,
						   vnop_create_attr,
						   vnop_mknod */
#define HKWD_VNOP_FCLEAR        0x13600000      /* vnop_fclear */
#define HKWD_VNOP_FID           0x4cb00000      /* vnop_fid */
#define HKWD_VNOP_FINFO         0x4f100000      /* vnop_finfo */
#define HKWD_VNOP_FSYNC         0x13c00000      /* vnop_fsync,
						   vnop_fsync_range */
#define HKWD_VNOP_FTRUNC        0x13d00000      /* vnop_ftrunc */
#define HKWD_VNOP_GETACL        0x4cc00000      /* vnop_getacl,
						   vnop_getxacl */
#define HKWD_VNOP_GETATTR       0x13a00000      /* vnop_getattr */
#define HKWD_VNOP_GETEA         0x4ce00000      /* vnop_getea */
#define HKWD_VNOP_GETPCL        0x4d200000      /* vnop_getpcl */
#define HKWD_VNOP_IOCTL         0x14c00000      /* vnop_ioctl */
#define HKWD_VNOP_LINK          0x15000000      /* vnop_link */
#define HKWD_VNOP_LISTEA        0x4d000000      /* vnop_listea */
#define HKWD_VNOP_LOCKCTL       0x15200000      /* vnop_lockctl */
#define HKWD_VNOP_LOOKUP	0x10700000      /* vnop_lookup,
						   lookuppn */
#define HKWD_VNOP_MAP           0x4ef00000      /* vnop_map */
#define HKWD_VNOP_MEMCNTL       0x4d500000      /* vnop_memcntl */
#define HKWD_VNOP_MKDIR         0x15600000      /* vnop_mkdir */
#define HKWD_VNOP_OPEN          0x15b00000      /* vnop_open */
#define HKWD_VNOP_READDIR       0x1a000000      /* vnop_readdir */
#define HKWD_VNOP_READLINK      0x16400000      /* vnop_readlink */
#define HKWD_VNOP_REMOVEEA      0x4d100000      /* vnop_removeea */
#define HKWD_VNOP_RENAME        0x16700000      /* vnop_rename */
#define HKWD_VNOP_REVOKE        0x4d400000      /* vnop_revoke */
#define HKWD_VNOP_RDWR_READ     0x16300000      /* vnop_rdwr (read),
						   vnop_rdwr_attr (read) */
#define HKWD_VNOP_RDWR_WRITE    0x19c00000      /* vnop_rdwr (write),
						   vnop_rdwr_attr (write) */
#define HKWD_VNOP_RMDIR         0x16800000      /* vnop_rmdir */
#define HKWD_VNOP_SEEK          0x15400000      /* vnop_seek */
#define HKWD_VNOP_SETACL        0x4cd00000      /* vnop_setacl */
#define HKWD_VNOP_SETATTR	0x12900000      /* vnop_setattr */
#define HKWD_VNOP_SETEA         0x4cf00000      /* vnop_setea */
#define HKWD_VNOP_SETPCL        0x4d300000      /* vnop_setpcl */
#define HKWD_VNOP_STATEA        0x4f200000      /* vnop_statea */
#define HKWD_VNOP_SYMLINK       0x18b00000      /* vnop_symlink */
#define HKWD_VNOP_REMOVE        0x19400000      /* vnop_remove */
#define HKWD_VNOP_UNMAP         0x4f000000      /* vnop_unmap */
#define HKWD_VNOP_HOLD          0x4db00000      /* vnop_hold,
						   vnop_rele */

/* Ignored:                                        vnop_select,
 *                                                 vnop_strategy
 */
/* end vnops */

/* All vfsops should appear in the following list: */
#define HKWD_VFS_ACLXCNTL       0x4da00000      /* vfs_aclxcntl */
#define HKWD_VFS_CNTL           0x4d800000      /* vfs_cntl */
#define HKWD_VFS_MOUNT          0x15900000      /* vfs_mount */
#define HKWD_VFS_QUOTACTL       0x4d900000      /* vfs_quotactl */
#define HKWD_VFS_ROOT           0x4d600000      /* vfs_root */
#define HKWD_VFS_STATFS         0x13b00000      /* vfs_statfs, vfs_statfsvp */
#define HKWD_VFS_SYNC           0x4d700000      /* vfs_sync, vfs_syncvfs */
#define HKWD_VFS_UNMOUNT        0x19100000      /* vfs_unmount */
#define HKWD_VFS_VGET		0x3ec00000	/* vfs_vget, vnode_cache */
/* end vfsops */

#define HKWD_PILE               0x4dc00000      /* pile subsystem */
#define HKWD_NLC                0x4dd00000      /* nlc subsystem */

/*
 * J2 hook and sub-hook ids (Component sysj2)
 */    
#define HKWD_J2_BUFMGR          0x4de00000      /* metadata cache */
#define HKWD_J2_ICACHE          0x4df00000      /* inode cache */
#define HKWD_J2_SNAPSHOT        0x4e000000      /* snapshot ops */
#define HKWD_J2_DMAP            0x4e100000      /* block map */
#define HKWD_J2_GLOBAL          0x4e200000      /* global events */
#define HKWD_J2_LOGMGR          0x4e300000      /* log manager */
#define HKWD_J2_TXNMGR          0x4e400000      /* transaction manager */
#define HKWD_J2_IO              0x59b00000      /* userdata ops */

/*
 * KDM operations (Component syskdm)
 */
#define HKWD_KDM                0x4e500000      /* kdm operations */

/*
 * AIO operations (Component sysxaio)
 */
#define HKWD_AIO                0x38d00000      /* aio operations */

/*
 * JFS hook and sub-hook ids (Component syspfs)
 */
#define HKWD_KERN_PFS     0x10a00000
#define HKWD_KERN_VFSINO  0x10d00000

#define HKWD_DIO	  0x3b100000	/* JFS: General Direct IO events   */
#define HKWD_DIO_IO	  0x3b200000	/* JFS: Direct IO startio/iodone   */
#define HKWD_DIO_PSEG	  0x3b300000	/* JFS: Direct IO requests demoted */

/* GRAVEYARD: All FS hooks past here are deprecated or unused, or
 * these are old names for current hooks. Do NOT use these names or
 * these hookids without first consulting the syslfs owner.
 *
 * NOTE: Do not define any real FS hook after the graveyard. The first
 * #define for a given hookid must be the main one for kdb_trace.h to
 * be effective.
 */
#define HKWD_LFS_LOOKUP	        HKWD_VNOP_LOOKUP      /* deprecated old name */
#define HKWD_SYSC_ACCESS        HKWD_VNOP_ACCESS      /* deprecated old name */
#define HKWD_SYSC               HKWD_VNOP_ACCESS      /* deprecated old name */
#define HKWD_SYSC_CHMOD	        HKWD_VNOP_SETATTR     /* deprecated old name */
#define HKWD_SYSC_CHOWN         HKWD_VNOP_SETATTR     /* deprecated old name */
#define HKWD_SYSC_CHOWNX        HKWD_VNOP_SETATTR     /* deprecated old name */
#define HKWD_SYSC_FCHMOD        HKWD_VNOP_SETATTR     /* deprecated old name */
#define HKWD_SYSC_FCHOWN        HKWD_VNOP_SETATTR     /* deprecated old name */
#define HKWD_SYSC_CLOSE         HKWD_VNOP_CLOSE       /* deprecated old name */
#define HKWD_SYSC_CLOSEX        HKWD_VNOP_CLOSE       /* deprecated old name */
#define HKWD_SYSC_CREAT         HKWD_VNOP_CREATE      /* deprecated old name */
#define HKWD_SYSC_MKNOD         HKWD_VNOP_CREATE      /* deprecated old name */
#define HKWD_SYSC_FCLEAR        HKWD_VNOP_FCLEAR      /* deprecated old name */
#define HKWD_SYSC_FSTAT         HKWD_VNOP_GETATTR     /* deprecated old name */
#define HKWD_SYSC_FFULLSTAT     HKWD_VNOP_GETATTR     /* deprecated old name */
#define HKWD_SYSC_FULLSTAT      HKWD_VNOP_GETATTR     /* deprecated old name */
#define HKWD_SYSC_STAT          HKWD_VNOP_GETATTR     /* deprecated old name */
#define HKWD_SYSC_STATX         HKWD_VNOP_GETATTR     /* deprecated old name */
#define HKWD_SYSC_LSTAT         HKWD_VNOP_GETATTR     /* deprecated old name */
#define HKWD_SYSC_FSYNC         HKWD_VNOP_FSYNC       /* deprecated old name */
#define HKWD_SYSC_FTRUNCATE     HKWD_VNOP_FTRUNC      /* deprecated old name */
#define HKWD_SYSC_IOCTL         HKWD_VNOP_IOCTL       /* deprecated old name */
#define HKWD_SYSC_IOCTLX        HKWD_VNOP_IOCTL       /* deprecated old name */
#define HKWD_SYSC_LINK          HKWD_VNOP_LINK        /* deprecated old name */
#define HKWD_SYSC_LOCKF         HKWD_VNOP_LOCKCTL     /* deprecated old name */
#define HKWD_SYSC_LSEEK         HKWD_VNOP_SEEK        /* deprecated old name */
#define HKWD_SYSC_MKDIR         HKWD_VNOP_MKDIR       /* deprecated old name */
#define HKWD_SYSC_OPEN          HKWD_VNOP_OPEN        /* deprecated old name */
#define HKWD_SYSC_OPENX         HKWD_VNOP_OPEN        /* deprecated old name */
#define HKWD_SYSC_READ          HKWD_VNOP_RDWR_READ   /* deprecated old name */
#define HKWD_SYSC_READX         HKWD_VNOP_RDWR_READ   /* deprecated old name */
#define HKWD_SYSC_WRITE         HKWD_VNOP_RDWR_WRITE  /* deprecated old name */
#define HKWD_SYSC_WRITEX        HKWD_VNOP_RDWR_WRITE  /* deprecated old name */
#define HKWD_SYSC_READLINK      HKWD_VNOP_READLINK    /* deprecated old name */
#define HKWD_SYSC_RENAME        HKWD_VNOP_RENAME      /* deprecated old name */
#define HKWD_SYSC_RMDIR         HKWD_VNOP_RMDIR       /* deprecated old name */
#define HKWD_SYSC_SYMLINK       HKWD_VNOP_SYMLINK     /* deprecated old name */
#define HKWD_SYSC_UNLINK        HKWD_VNOP_REMOVE      /* deprecated old name */
#define HKWD_SYSC_GETDIRENTRIES HKWD_VNOP_READDIR     /* deprecated old name */

#define HKWD_SYSC_MOUNT         HKWD_VFS_MOUNT        /* deprecated old name */
#define HKWD_SYSC_VMOUNT        HKWD_VFS_MOUNT        /* deprecated old name */
#define HKWD_SYSC_FSTATFS       HKWD_VFS_STATFS       /* deprecated old name */
#define HKWD_SYSC_STATFS        HKWD_VFS_STATFS       /* deprecated old name */
#define HKWD_SYSC_USTAT         HKWD_VFS_STATFS       /* deprecated old name */
#define HKWD_SYSC_SYNC          HKWD_VFS_SYNC         /* deprecated old name */
#define HKWD_SYSC_UMOUNT        HKWD_VFS_UNMOUNT      /* deprecated old name */
#define HKWD_SYSC_UVMOUNT       HKWD_VFS_UNMOUNT      /* deprecated old name */
#define HKWD_JFS_VNC		HKWD_VFS_VGET         /* deprecated old name */

#define HKWD_KERN_LFS           0x10900000    /* XXX: UNUSED */
#define HKWD_SYSC_CHDIR         0x12700000    /* XXX: UNUSED */
#define HKWD_OLD_CHOWN          0x12a00000    /* XXX: UNUSED */
#define HKWD_OLD_CHOWNX         0x12b00000    /* XXX: UNUSED */
#define HKWD_SYSC_CHROOT        0x12d00000    /* XXX: UNUSED */
#define HKWD_OLD_CLOSEX         0x12f00000    /* XXX: UNUSED */
#define HKWD_SYSC_DUP           0x13300000    /* XXX: UNUSED */
#define HKWD_SYSC_FCNTL         0x13700000    /* XXX: UNUSED */
#define HKWD_OLD_FFULLSTAT      0x13800000    /* XXX: UNUSED */
#define HKWD_OLD_FULLSTAT       0x13e00000    /* XXX: UNUSED */
#define HKWD_OLD_IOCTLX         0x14d00000    /* XXX: UNUSED */
#define HKWD_OLD_MKNOD          0x15700000    /* XXX: UNUSED */
#define HKWD_SYSC_MNTCTL        0x15800000    /* XXX: UNUSED */
#define HKWD_OLD_STAT           0x18600000    /* XXX: UNUSED */
#define HKWD_OLD_STATX          0x18800000    /* XXX: UNUSED */
#define HKWD_OLD_OPENX          0x15c00000    /* XXX: UNUSED */
#define HKWD_OLD_READX          0x16500000    /* XXX: UNUSED */
#define HKWD_OLD_STATFS         0x18700000    /* XXX: UNUSED */
#define HKWD_OLD_SYNC           0x18c00000    /* XXX: UNUSED */
#define HKWD_SYSC_UNAME         0x19200000    /* XXX: UNUSED */
#define HKWD_SYSC_UNAMEX        0x19300000    /* XXX: UNUSED */
#define HKWD_OLD_USTAT          0x19600000    /* XXX: UNUSED */
#define HKWD_OLD_UVMOUNT        0x19900000    /* XXX: UNUSED */
#define HKWD_OLD_VMOUNT         0x19a00000    /* XXX: UNUSED */
#define HKWD_OLD_WRITEX         0x19d00000    /* XXX: UNUSED */
#define HKWD_OLD_FCHMOD         0x19e00000    /* XXX: UNUSED */
#define HKWD_OLD_FCHOWN         0x19f00000    /* XXX: UNUSED */
#define HKWD_OLD_LSTAT          0x1a100000    /* XXX: UNUSED */
#define HKWD_JFS_DNLC           0x3ed00000    /* XXX: UNUSED */

#define HKWD_SYSC_PIPE          0x15f00000    /* Deprecated */

/* NOTE: HKWD_SYSC_LFS is deprecated. Use specific hookids for each
 * vnop or use the "lfs" trace group.
 */
#define HKWD_SYSC_LFS     0x10800000    /* file system system call */

/* NOTE: HKWD_KERN_J2 is dead. The subhooks have been entirely
 * replaced by full vnode op hooks in the LFS layer.
 */
#define HKWD_KERN_J2      0x3f700000    /* JFS2: vnode operation events */

/* NOTE: HKWD_KERN_J2PAGER is dead. Use 59b (HKWD_IO_J2) to track
 * userdata I/O and other hookwords to track other I/O.
 */
#define HKWD_KERN_J2PAGER 0x3f800000 	/* JFS2: pager events */

/* NOTE: HKWD_DIO_J2 is dead. Use 59b (HKWD_IO_J2) to track userdata
 * I/O, including DIO.
 */
#define HKWD_DIO_J2       0x59c00000	/* JFS2: direct I/O */

#define HKWD_IO_J2        HKWD_J2_IO    /* deprecated old name */

/* *** STOP FILESYSTEM HOOKS *** */


/*--------------------------------------------------------------
 * LVM device driver hooks and sub-hookids
 */

/* LVM Hooks
 *     NOTE: 2 LVM Hooks are defined above (105 and 10B).
 *     NOTE: LVM sub-hooks are defined in lvdd_trchkid.h
 */

#define HKWD_KERN_LVM_NONIO     0x39300000      /* LVM non-I/O hook ID    */
#define HKWD_KERN_LVM_CFG       0x5D400000      /* LVM config operations  */
#define HKWD_KERN_LVM_CONC      0x5D500000      /* LVM concurrent ops     */
#define HKWD_KERN_LVM_D         0x5D600000      /* LVM general debug hook */
#define HKWD_KERN_LVM_ERR       0x5D700000      /* LVM error path         */

#include <sys/lvdd_trchkid.h>
/*
 * END LVM Hooks...
 *----------------------------------------------------------------------*/



#define HKWD_SYSC_ACCT            0x12100000
#define HKWD_SYSC_ALARM           0x12200000
#define HKWD_SYSC_AUDIT           0x12300000
#define HKWD_SYSC_AUDITLOG        0x12400000
#define HKWD_SYSC_AUDITPROC       0x12500000
#define HKWD_SYSC_AUDITSYS        0x12600000
#define HKWD_SYSC_CHMAC           0x12800000
#define HKWD_SYSC_CHPRIV          0x12c00000
#define HKWD_SYSC_DISCLAIM        0x13100000
#define HKWD_SYSC_DISCLAIM64	  0x13100010
#define HKWD_SYSC_EXECVE          0x13400000
#define HKWD_SYSC__EXIT           0x13500000
#define HKWD_SYSC_FORK            0x13900000
#define hkwd_SYSC_FORK_PREPARE      	0x02  /* Subhook for ld_fork_prepare 
					       * failure. 0x01 skipped for 
					       * compatibility with 6.1 
					       * versions */
#define HKWD_SYSC_GETEGID         0x13f00000
#define HKWD_SYSC_GETEPRIV        0x14000000
#define HKWD_SYSC_GETEUID         0x14100000
#define HKWD_SYSC_GETGID          0x14200000
#define HKWD_SYSC_GETGROUPS       0x14300000
#define HKWD_SYSC_GETMPRIV        0x14400000
#define HKWD_SYSC_GETPGRP         0x14500000
#define HKWD_SYSC_GETPID          0x14600000
#define HKWD_SYSC_GETPPID         0x14700000
#define HKWD_SYSC_GETPRIV         0x14800000
#define HKWD_SYSC_GETTSTATE       0x14900000
#define HKWD_SYSC_GETUID          0x14a00000
#define HKWD_SYSC_GTTY            0x14b00000
#define HKWD_SYSC_KILL            0x14e00000
#define HKWD_SYSC_KPRINTF         0x14f00000
#define HKWD_SYSC_LOADTBL         0x15100000
#define HKWD_SYSC_LOCKX           0x15300000
#define HKWD_SYSC_MACCTL          0x15500000
#define HKWD_SYSC_NICE            0x15a00000
#define HKWD_SYSC_OUNAME          0x15d00000
#define HKWD_SYSC_PAUSE           0x15e00000
#define HKWD_SYSC_PLOCK           0x16000000
#define HKWD_SYSC_PROFIL          0x16100000
#define HKWD_SYSC_PTRACE          0x16200000
#define HKWD_SYSC_REBOOT          0x16600000
#define HKWD_SYSC_SBREAK          0x16900000
#define HKWD_SYSC_SELECT          0x16a00000
#define HKWD_SYSC_SETGID          0x16b00000
#define HKWD_SYSC_SETGROUPS       0x16c00000
#define HKWD_SYSC_SETMAC          0x16d00000
#define HKWD_SYSC_SETPGRP         0x16e00000
#define HKWD_SYSC_SETPRIO         0x16f00000
#define HKWD_SYSC_SETPRIV         0x17000000
#define HKWD_SYSC_SETREUID        0x17100000
#define HKWD_SYSC_SETTSTATE       0x17200000
#define HKWD_SYSC_SETUID          0x17300000
#define HKWD_SYSC_SIGACTION       0x18000000
#define HKWD_SYSC_SIGCLEANUP      0x18100000
#define HKWD_SYSC_SIGPROCMASK     0x18200000
#define HKWD_SYSC_SIGRETURN       0x18300000
#define HKWD_SYSC_SIGSTACK        0x18400000
#define HKWD_SYSC_SIGSUSPEND      0x18500000
#define HKWD_SYSC_STIME           0x18900000
#define HKWD_SYSC_STTY            0x18a00000
#define HKWD_SYSC_TIME            0x18d00000
#define HKWD_SYSC_TIMES           0x18e00000
#define HKWD_SYSC_ULIMIT          0x18f00000
#define HKWD_SYSC_UMASK           0x19000000
#define HKWD_SYSC_USRINFO         0x19500000
#define HKWD_SYSC_UTIME           0x19700000
#define HKWD_SYSC_UTSSYS          0x19800000
#define HKWD_SYSC_WAIT            0x19b00000
#define HKWD_SYSC_UTIMES          0x1a200000
#define HKWD_SYSC_SLOOKUP         0x1a300000
#define HKWD_SYSC_GETRLIMIT       0x1a400000
#define HKWD_SYSC_SETRLIMIT       0x1a500000
#define HKWD_SYSC_GETRUSAGE       0x1a600000
#define HKWD_SYSC_GETPRIORITY     0x1a700000
#define HKWD_SYSC_SETPRIORITY     0x1a800000
#define HKWD_SYSC_ABSINTERVAL     0x1a900000
#define HKWD_SYSC_GETINTERVAL     0x1aa00000
#define HKWD_SYSC_GETTIMER        0x1ab00000
#define HKWD_SYSC_INCINTERVAL     0x1ac00000
#define HKWD_SYSC_RESTIMER        0x1ad00000
#define HKWD_SYSC_RESABS          0x1ae00000
#define HKWD_SYSC_RESINC          0x1af00000
#define HKWD_SYSC_SETTIMER        0x1f000000
#define HKWD_SYSC_GETARGS         0x1f100000
#define HKWD_SYSC_GETPROC         0x1f200000
#define HKWD_SYSC_GETUSER         0x1f300000
#define HKWD_SYSC_KNLIST          0x1f400000
#define HKWD_SYSC_SETSID          0x1f500000
#define HKWD_SYSC_SETPGID         0x1f600000
#define HKWD_SYSC_SETREGID        0x1f700000
#define HKWD_SYSC_SETPRI          0x1f800000

#define HKWD_VMM                  0x1b000000
#define HKWD_VMM_ASSIGN           0x1b000000
#define HKWD_VMM_DELETE           0x1b100000
#define HKWD_VMM_PGEXCT           0x1b200000
#define HKWD_VMM_PROTEXCT         0x1b300000
#define HKWD_VMM_LOCKEXCT         0x1b400000
#define HKWD_VMM_RECLAIM          0x1b500000
#define HKWD_VMM_GETPARENT        0x1b600000
#define HKWD_VMM_COPYPARENT       0x1b700000
#define HKWD_VMM_MAPPARENT        0x1b700001
#define HKWD_VMM_COWRELOAD        0x1b700002
#define HKWD_VMM_VMAP             0x1b800000
#define HKWD_VMM_ZFOD             0x1b900000
#define HKWD_VMM_SIO              0x1ba00000
#define HKWD_VMM_PAGEOUT          0x1ba00000
#define HKWD_VMM_PAGEIN           0x1ba00001
#define HKWD_VMM_SIO_PPIN         0x1ba00002
#define HKWD_VMM_SIO_PPOUT        0x1ba00003
#define HKWD_VMM_SEGCREATE        0x1bb00000
#define HKWD_VMM_SEGDELETE        0x1bc00000
#define HKWD_VMM_DALLOC           0x1bd00000
#define HKWD_VMM_DALLOC_PP        0x1bd00001
#define HKWD_VMM_DFREE            0x1bd00002
#define HKWD_VMM_DFREE_PPNFR      0x1bd00003
#define HKWD_VMM_DFREE_PPXPT      0x1bd00004
#define HKWD_VMM_PFENDOUT         0x1be00000
#define HKWD_VMM_PFENDIN          0x1be00001
#define HKWD_VMM_PFENDOUT_PP      0x1be00002
#define HKWD_VMM_PFENDIN_PP       0x1be00003
#define HKWD_VMM_EXCEPT           0x1bf00000
#define HKWD_VMM_ZERO_0		  0x1d900000
#define HKWD_VMM_ZERO_1		  0x1d900001
#define HKWD_VMM_MKP		  0x1da00000
#define HKWD_VMM_FPGIN		  0x1db00000
#define HKWD_VMM_SPACEOK_0        0x1dc00000
#define HKWD_VMM_SPACEOK_1        0x1dc00001

#define HKWD_VMM_RESERVATION      0x4F900000
#define hkwd_VMM_GET_RESV0              0
#define hkwd_VMM_GET_RESV1              1
#define hkwd_VMM_USE_RESV0              2
#define hkwd_VMM_USE_RESV1              3
#define hkwd_VMM_FREE_RESV0             4
#define hkwd_VMM_FREE_RESV1             5
#define hkwd_VMM_GETFREE                6

/* More frequent VMM LRU events */
#define HKWD_VMM_LRU		  0x1dd00000
#define hkwd_VMM_LRU_START		0x0
#define hkwd_VMM_LRU_END		0x1
#define hkwd_VMM_LRU_MAIN_LOOP		0x2
#define hkwd_VMM_LRU_PAGE_STEAL		0x3
#define hkwd_VMM_LRU_SKIP_CCB		0x4
#define hkwd_VMM_LRU_TIMER_START	0x5
#define hkwd_VMM_LRU_TIMER_STOP		0x6
#define hkwd_VMM_LRU_TIMER_POLL		0x7
#define hkwd_VMM_LRU_TIMER_TMOUT	0x8
#define hkwd_VMM_LRU_DLATIMER_START	0x9
#define hkwd_VMM_LRU_DLATIMER_STOP	0xA
#define hkwd_VMM_LRU_DLATIMER_TMOUT	0xB
#define hkwd_VMM_LRU_DLA_DONE		0xC

/* Less frequent VMM LRU events */
#define HKWD_VMM_LRU2		  0x4a500000
#define hkwd_VMM_LRU_CYCLE		0x0
#define hkwd_VMM_LRU_NO_XMEMOK		0x1
#define hkwd_VMM_LRU_NEXT_LRULIST	0x2
#define hkwd_VMM_LRU_COMP_LRULIST	0x3
#define hkwd_VMM_LRU_NEW_CCB		0x4
#define hkwd_VMM_LRU_UPD_CRITERIA	0x5
#define hkwd_VMM_LRU_NEW_PASS		0x6
#define hkwd_VMM_LRU_DLAMODE		0x7
#define hkwd_VMM_LRU_DLA_WAKEALL	0x8
#define hkwd_VMM_LRU_DLA_UPDATE		0x9

/* VMM page size management hooks */
#define HKWD_VMM_PSIZE_INC        0x4C100000
#define HKWD_VMM_PSIZE_DEC        0x4C100001
#define HKWD_VMM_PSM_PROM         0x4C200000
#define HKWD_VMM_PSM_PROM_SCAN    0x4C200001
#define HKWD_VMM_PSM_PCHANGE      0x4C200002
#define HKWD_VMM_PSM_LWPROM       0x4C200003
#define HKWD_VMM_PSM_LWMIG        0x4C200004
#define HKWD_VMM_PSM_HWPROM       0x4C200005
#define HKWD_VMM_PSM_DEM          0x4C200006
#define HKWD_VMM_PSM_DEM_SCAN     0x4C200007
#define HKWD_VMM_PSM_REQ          0x4C200008
#define HKWD_VMM_PSM_PIN_TH       0x4C200009
#define HKWD_VMM_PSM_FREE_TH0     0x4C20000A
#define HKWD_VMM_PSM_FREE_TH1     0x4C20000B
#define HKWD_VMM_PSM_TGT          0x4C20000C
#define HKWD_VMM_PSM_TMR_START    0x4C20000D
#define HKWD_VMM_PSM_TMR_TMOUT    0x4C20000E
#define HKWD_VMM_PSM_TMR_STOP     0x4C20000F
#define HKWD_VMM_PSM_START_LRU    0x4C200010
#define HKWD_VMM_PSM_NOPROG_TMOUT 0x4C200011
#define HKWD_VMM_PSM_HW_MIGABLE   0x4C200015
#define HKWD_VMM_PSM_LW_MIGABLE   0x4C200016
#define HKWD_VMM_PSM_PROM_SCAN2   0x4C200017

/* VMM error trace hooks */
#define HKWD_VMM_ERR_REL_ALIGN    0x4CA00000
#define HKWD_VMM_ERR_PROT_ALIGN   0x4CA00001

#define HKWD_VMM_VWAIT            0x2FC00000
#define HKWD_VMM_WRITE_0          0x4C300000
#define HKWD_VMM_WRITE_1          0x4C300001

/* VMM Service trace hooks */
#define HKWD_VMSVC_PIN            0x62400000
#define HKWD_VMSVC_UNPIN          0x62400002
#define HKWD_VMSVC_XLATE_PIN      0x62400004
#define HKWD_VMSVC_XLATE_UNPIN    0x62400006
#define HKWD_VMSVC_RMLMB_KERNEL   0x62500000
#define HKWD_VMSVC_ADDLMB_KERNEL  0x62500002
#define HKWD_VMSVC_VM_ADDMEM      0x62500004
#define HKWD_VMSVC_VM_FREEMEM     0x62500006
#define HKWD_VMSVC_VM_GFREE       0x62600000
#define HKWD_VMSVC_VM_GALLOC_ATT  0x62600002
#define HKWD_VMSVC_VMS_DELETE     0x62700000
#define HKWD_VMSVC_VM_RELEASE     0x62700002
#define HKWD_VMSVC_VM_RELEASEP    0x62700004
#define HKWD_VMSVC_VM_DISCLAIM    0x62700006
#define HKWD_VMSVC_VMS_IOWAITF    0x62800000
#define HKWD_VMSVC_VM_PROTECT     0x62900000
#define HKWD_VMSVC_VM_WRITE       0x62A00000
#define HKWD_VMSVC_VM_XWRITEP     0x62A00002 
#define HKWD_VMSVC_AS_ATT64       0x62B00000
#define HKWD_VMSVC_AS_DET64       0x62B00002 
#define HKWD_VMSVC_AS_SETH64      0x62B00004 

/* DR page migration trace hooks */
#define HKWD_VMM_MIG_DR           0x62C00000
#define HKWD_VMM_MIG_DR_ERR       0x62C00001
#define HKWD_VMM_MIG_PG_DR        0x62C00002
#define HKWD_VMM_MIG_PG_DR_ERR    0x62C00003
#define HKWD_VMM_MIG_SERV_DR      0x62C00004
#define HKWD_VMM_MIG_SERV_DR_ERR  0x62C00005

/* System V IPC Trace Hooks */
#define HKWD_SYSC_IPCACCESS       0x3c500000
#define HKWD_SYSC_IPCGET          0x3c600000

/* System V Message Queue Trace Hooks */
#define HKWD_SYSC_MSGCONV         0x3c700000
#define HKWD_SYSC_MSGCTL          0x3c800000
#define HKWD_SYSC_MSGGET          0x3c900000
#define HKWD_SYSC_MSGRCV          0x3ca00000
#define HKWD_SYSC_MSGSELECT       0x3cb00000
#define HKWD_SYSC_MSGSND          0x3cc00000
#define HKWD_SYSC_MSGXRCV         0x3cd00000

/* System V Semaphore Sets Trace Hooks */
#define HKWD_SYSC_SEMCONV         0x3ce00000
#define HKWD_SYSC_SEMCTL          0x3cf00000
#define HKWD_SYSC_SEMGET          0x3d000000
#define HKWD_SYSC_SEMOP           0x3d100000
#define HKWD_SYSC_SEM_OP          0x3d200000

/* System V Shared Memory Region Trace Hooks */
#define HKWD_SYSC_SHMAT           0x3d300000
#define HKWD_SYSC_SHMCONV         0x3d400000
#define HKWD_SYSC_SHMCTL          0x3d500000
#define HKWD_SYSC_SHMDT           0x3d600000
#define HKWD_SYSC_SHMGET          0x3d700000

/* mmap Services Trace Hooks */
#define HKWD_SYSC_MADVISE         0x3d800000
#define HKWD_SYSC_MINCORE         0x3d900000
#define HKWD_SYSC_MMAP            0x3da00000
#define HKWD_SYSC_MPROTECT        0x3db00000
#define HKWD_SYSC_MSYNC           0x3dc00000
#define HKWD_SYSC_MUNMAP          0x3dd00000
#define HKWD_SYSC_MVALID          0x3de00000
#define HKWD_SYSC_UKEY_PROTECT    0x60c00000
#define HKWD_SYSC_UKEY_GETKEY     0x60d00000

/* msemaphore Services Trace Hooks */
#define HKWD_SYSC_MSEM_INIT       0x3df00000
#define HKWD_SYSC_MSEM_LOCK       0x3e000000
#define HKWD_SYSC_MSEM_REMOVE     0x3e100000
#define HKWD_SYSC_MSEM_UNLOCK     0x3e200000

#define HKWD_DD                   0x1c000000
#define HKWD_DD_STRATEGY          0x1c000000
#define HKWD_DD_START             0x1c100000
#define HKWD_DD_INTR              0x1c200000
#define HKWD_DD_GETBLK            0x1c300000
#define HKWD_DD_IOWAIT            0x1c400000
#define HKWD_DD_IODONE            0x1c500000
#define HKWD_DD_PHYSIO            0x1c600000
#define HKWD_DD_ATTACH            0x1c700000
#define HKWD_DD_PPDD              0x1c800000    /* parallel printer DD */
#define HKWD_DD_CDDD              0x1c900000    /* cdrom DD */
#define HKWD_DD_TAPEDD            0x1ca00000    /* tape DD */
#define HKWD_DD_CIODD             0x1cb00000    /* cio DD */
#define HKWD_DD_ETHDD             0x1cc00000    /* cio PC  ethernet DD */
#define HKWD_DD_ENTDD             0x1cd00000    /* cio MCA ethernet DD */
#define HKWD_DD_TOKDD             0x1ce00000    /* cio MCA tokenring DD */
#define HKWD_DD_C327DD            0x1cf00000    /* 3270 DD */

#define HKWD_DD_FDDD              0x22000000    /* diskette DD */
#define HKWD_DD_SCDISKDD          0x22100000    /* SCSI Disk DD */
#define HKWD_DD_BADISKDD          0x22200000    /* Bus Attached Disk DD */
#define HKWD_DD_SCSIDD            0x22300000    /* SCSI Adapter DD    */
#define HKWD_DD_MPQPDD            0x22400000    /* multi-protocol     */
#define HKWD_DD_X25DD             0x22500000    /* X.25 Device Driver */
#define HKWD_DD_GIO               0x22600000    /* G.I. Joe */
#define HKWD_DD_X25PRF            0x22700000    /* X.25 performance  */
#define HKWD_DD_SERDASDD          0x22800000    /* Serial DASD Subsystem */
#define HKWD_DD_TMSCSIDD          0x22900000    /* SCSI Target Mode DD */
#define	HKWD_DD_SOL		  0x24800000	/* optic 2-port */
#define HKWD_DD_CATDD             0x35000000    /* S/370 Channel */
#define HKWD_DD_SISADD            0x38E00000    /* SIS based SCSI DD */
#define HKWD_DD_SISRAID           0x39000000    /* SIS based SCSI (RAID) DD */
#define HKWD_USBCDROM		  0x47c00000	/* USB CD-ROM client driver */
#define HKWD_DD_SISSAS            0x5BD00000    /* SIS based SAS (RAID) DD */

#define HKWD_DDSPEC               0x1d000000
#define HKWD_DDSPEC_GRAPHIO       0x1d000000
#define HKWD_RAS_ERRLG            0x1d100000
#define HKWD_RAS_DUMP             0x1d200000

#define HKWD_LPP_PCSIM            0x1d300000
#define hkwd_PCSIM_FILE   1
#define hkwd_PCSIM_DISP   2
#define hkwd_PCSIM_CNTL   3
#define hkwd_PCSIM_PCAT   4
#define hkwd_PCSIM_DSKT   5

#define HKWD_WHIP_API             0x1d400000
#define HKWD_WHIP_DAEMON          0x1d500000
#define HKWD_WHIP_DRIVER          0x1d600000
#define HKWD_WHIP_EMUL            0x1d700000
#define HKWD_WHIP_FILE            0x1d800000

#define HKWD_COMM                 0x1e000000
#define HKWD_COMM_EM78            0x1e000000

/*
 * Socket, Network, and Network Interface hook id and sub-hook id's
 */

#define HKWD_NETPERF		0x25000000

#define HKWD_NETERR		0x25100000 

#define HKWD_SOCKET		0x25200000
#define hkwd_accept_in			1
#define hkwd_accept_out			2
#define hkwd_bind_in			3
#define hkwd_bind_out			4
#define hkwd_connect_in			5
#define hkwd_connect_out		6
#define hkwd_getkerninfo_in		7
#define hkwd_getkerninfo_out		8
#define hkwd_getpeername_in		9
#define hkwd_getpeername_out		10
#define hkwd_getsockname_in		11
#define hkwd_getsockname_out		12
#define hkwd_getsockopt_in		13
#define hkwd_getsockopt_out		14
#define hkwd_listen_in			15
#define hkwd_listen_out			16
#define hkwd_recv_in			17
#define hkwd_recv_out			18
#define hkwd_recvfrom_in		19
#define hkwd_recvfrom_out		20
#define hkwd_recvit_in			21
#define hkwd_recvit_out			22
#define hkwd_recvmsg_err		23
#define hkwd_recvmsg_in			24
#define hkwd_recvmsg_out		25
#define hkwd_rmsock_in			26
#define hkwd_rmsock_out			27
#define hkwd_sbwakeup_in		28
#define hkwd_sbwakeup_out		29
#define hkwd_send_in			30
#define hkwd_send_out			31
#define hkwd_sendfile_in		32
#define hkwd_sendfile_out		33
#define hkwd_sendit_in			34
#define hkwd_sendit_out			35
#define hkwd_sendmsg_in			36
#define hkwd_sendmsg_out		37
#define hkwd_sendto_in			38
#define hkwd_setsockopt_in		39
#define hkwd_setsockopt_out		40
#define hkwd_shutdown_in		41
#define hkwd_shutdown_out		42
#define hkwd_soabort_in			43
#define hkwd_soabort_out		44
#define hkwd_soaccept_in		45
#define hkwd_soaccept_out		46
#define hkwd_soaccessfailure_in		47
#define hkwd_soaccessfailure_out	48
#define hkwd_sobind_in			49
#define hkwd_sobind_out			50
#define hkwd_sockargs_in		51
#define hkwd_sockargs_out		52
#define hkwd_socket_aio_dequeue_in	53
#define hkwd_socket_aio_dequeue_out	54
#define hkwd_socket_in			55
#define hkwd_socket_out			56
#define hkwd_socketpair_err		57
#define hkwd_socketpair_in		58
#define hkwd_socketpair_out		59
#define hkwd_socksetup_in		60
#define hkwd_socksetup_out		61
#define hkwd_soclose_in			62
#define hkwd_soclose_out		63
#define hkwd_soconnect2_in		64
#define hkwd_soconnect2_out		65
#define hkwd_soconnect_in		66
#define hkwd_soconnect_out		67
#define hkwd_socreate_err		68
#define hkwd_socreate_in		69
#define hkwd_socreate_out		70
#define hkwd_socreategroup_err		71
#define hkwd_socreategroup_in		72
#define hkwd_socreategroup_out		73
#define hkwd_sodisconn_in		74
#define hkwd_sodisconn_out		75
#define hkwd_sodisconnect_in		76
#define hkwd_sodisconnect_out		77
#define hkwd_sofree_err			78
#define hkwd_sofree_in			79
#define hkwd_sofree_out			80
#define hkwd_sogetopt_in		81
#define hkwd_sogetopt_out		82
#define hkwd_sohasoutofband_in		83
#define hkwd_sohasoutofband_out		84
#define hkwd_soisconnected_in		85
#define hkwd_soisconnected_out		86
#define hkwd_soisdisconnected_in	87
#define hkwd_soisdisconnected_out	88
#define hkwd_solisten_in		89
#define hkwd_solisten_out		90
#define hkwd_sonewsock_in		91
#define hkwd_sonewsock_out		92
#define hkwd_soo_close_in		93
#define hkwd_soo_close_out		94
#define hkwd_soo_ioctl_in		95
#define hkwd_soo_ioctl_out		96
#define hkwd_soo_read_in		97
#define hkwd_soo_read_out		98
#define hkwd_soo_select_in		99
#define hkwd_soo_select_out		100
#define hkwd_soo_stat_in		101
#define hkwd_soo_stat_out		102
#define hkwd_soo_write_in		103
#define hkwd_soo_write_out		104
#define hkwd_soreceive_in		105
#define hkwd_soreceive_out		106
#define hkwd_soreserve_in		107
#define hkwd_soreserve_out		108
#define hkwd_sorflush_in		109
#define hkwd_sorflush_out		110
#define hkwd_sosbwait_in		111
#define hkwd_sosbwait_out		112
#define hkwd_sosend_in			113
#define hkwd_sosend_out			114
#define hkwd_sosetopt_in		115
#define hkwd_sosetopt_out		116
#define hkwd_soshutdown_in		117
#define hkwd_soshutdown_out		118
#define hkwd_sosleep_in			119
#define hkwd_sosleep_out		120
#define hkwd_sosplice_in		121
#define hkwd_sosplice_out		122
#define hkwd_sowakeup_in		123
#define hkwd_sowakeup_out		124
#define hkwd_splice_in			125
#define hkwd_splice_out			126
#define hkwd_gethostid_in		127
#define hkwd_sethostid_in		128
#define hkwd_gethostname_in		129
#define hkwd_sethostname_in		130
#define hkwd_getdomainname_in		131
#define hkwd_setdomainname_in		132
#define hkwd_getdomainname_out		133
#define hkwd_getpeereid_in              134
#define hkwd_getpeereid_out             135
#define hkwd_ksodebug_in                136
#define hkwd_ksodebug_err               137
#define hkwd_sbwakeup_out_lmt		138
#define hkwd_socreate_err1              140
#define hkwd_socreate_err2              141
#define hkwd_socreate_err3              142
#define hkwd_socreate_err4              143
#define hkwd_socreate_err5              144
#define hkwd_socreate_err6              145
#define hkwd_socreate_err7              146
#define hkwd_socreate_err8              147
#define hkwd_socreate_err9              148
#define hkwd_socreate_err10             149
#define hkwd_socreate_err11             150
#define hkwd_soclose2_err1              151
#define hkwd_soclose2_err2              152
#define hkwd_soconnect_err1             153
#define hkwd_sosend_err1                154
#define hkwd_sosend_err2                155
#define hkwd_sosend_err3                156
#define hkwd_sosend_err4                157
#define hkwd_sosend_err5                158
#define hkwd_sosend_err6                159
#define hkwd_sosend_err7                160
#define hkwd_sosend_err8                161
#define hkwd_sosend_err9                162
#define hkwd_sosend_err10               163
#define hkwd_sosend_err11               164
#define hkwd_sosend_err12               165
#define hkwd_sokernrecv_err1            166
#define hkwd_sokernrecv_err2            167
#define hkwd_sokernrecv_msgwaitall1     168
#define hkwd_sokernrecv_msgwaitall2	169
#define hkwd_sosetopt_err1              170
#define hkwd_sosetopt_err2              171
#define hkwd_sosetopt_err3              172
#define hkwd_sosetopt_err4              173
#define hkwd_sosetopt_err5              174
#define hkwd_sosetopt_err6              175
#define hkwd_sosetopt_err7              176
#define hkwd_sosetopt_err8              177
#define hkwd_sosetopt_err9              178
#define hkwd_sosetopt_err10             179
#define hkwd_sosetopt_err11             180
#define hkwd_sosetopt_err12             181
#define hkwd_sogetopt_err1              182
#define hkwd_sogetopt_err2              183
#define hkwd_sodequeue_err1             184
#define hkwd_sodequeue_err2             185
#define hkwd_sodequeue_err3             186
#define hkwd_sodequeue_err4             187
#define hkwd_sodequeue_err5             188
#define hkwd_sogetaddr_err1             189
#define hkwd_sogetaddr_err2             190
#define hkwd_socreategroup_err1         191
#define hkwd_socreategroup_err2         192
#define hkwd_socreategroup_err3         193
#define hkwd_socreategroup_err4         194
#define hkwd_sosplice_err1              195
#define hkwd_sosplice_err2              196
#define hkwd_sodisconnectreuse_in       197
#define hkwd_sodisconnectreuse_out      198
#define hkwd_sonewsock_err1             199
#define hkwd_sonewsock_err2             200
#define hkwd_sonewsock_err3             201
#define hkwd_sonewsock_err4             202
#define hkwd_sonewsock_err5             203
#define hkwd_sonewsock_err6             204
#define hkwd_sonewsock_err7             205
#define hkwd_sosbwait_err1              206
#define hkwd_soqaio_err1                207
#define hkwd_soqaio_err2                208
#define hkwd_soreserve_err1             209
#define hkwd_soreserve_err2             210
#define hkwd_sbinsertoob_err1           211
#define hkwd_sbappendaddr_err1          212
#define hkwd_sbdrop_in                  213
#define hkwd_sbdrop_out                 214
#define hkwd_sbdroprecord_in            215
#define hkwd_sbdroprecord_out           216
#define hkwd_so_exit_in                 217
#define hkwd_so_exit_out                218
#define hkwd_soiskernconnected_in       219
#define hkwd_soiskernconnected_out      220
#define hkwd_soiskerndisconnected_in    221
#define hkwd_soiskerndisconnected_out   222
#define hkwd_sndbufpool_dr_cpu_add_in   223
#define hkwd_sndbufpool_dr_cpu_add_out  224
#define hkwd_sndbufpool_dr_cpu_remove_in        225
#define hkwd_sndbufpool_dr_cpu_remove_out       226
#define hkwd_soo_read_err1              227
#define hkwd_soo_read_err2              229
#define hkwd_soo_ioctl_err1             230
#define hkwd_soo_ioctl_err2             231
#define hkwd_soo_ioctl_err3             232
#define hkwd_soo_ioctl_err4             233
#define hkwd_soo_ioctl_err5             234
#define hkwd_soo_ioctl_err6             235
#define hkwd_soo_ioctl_err7             236
#define hkwd_soo_ioctl_err8             237
#define hkwd_soo_ioctl_err9             238
#define hkwd_soo_ioctl_err10            239
#define hkwd_soo_ioctl_err11            240
#define hkwd_soo_ioctl_err12            241
#define hkwd_soo_ioctl_err13            242
#define hkwd_soo_ioctl_err14            243
#define hkwd_soo_ioctl_err15            244
#define hkwd_soo_ioctl_err16            245
#define hkwd_soo_ioctl_err17            246
#define hkwd_soo_ioctl_err18            247
#define hkwd_soo_ioctl_err19            248
#define hkwd_soo_ioctl_err20            249
#define hkwd_rmsock_err1                250
#define hkwd_rmsock_err2                251
#define hkwd_connect_err1               252
#define hkwd_connext_err1               253
#define hkwd_socket_err1                254
#define hkwd_bind_err1                  255
#define hkwd_bind_err2                  256
#define hkwd_bind_err3                  257
#define hkwd_accept1_err1               258
#define hkwd_accept1_err2               259
#define hkwd_accept1_err3               260
#define hkwd_accept1_err4               261
#define hkwd_accept1_err5               262
#define hkwd_accept1_err6               263
#define hkwd_accept1_err7               264
#define hkwd_accept1_err8               265
#define hkwd_accept1_err9               266
#define hkwd_accept1_err10              267
#define hkwd_accept1_err11              268
#define hkwd_accept1_err12              269
#define hkwd_accept1_err13              270
#define hkwd__connect_err1              271
#define hkwd__connect_err2              272
#define hkwd__connect_err3              273
#define hkwd_socketpair_err1            274
#define hkwd_socketpair_err2            275
#define hkwd_socketpair_err3            276
#define hkwd_socketpair_err4            277
#define hkwd_socketpair_err5            278
#define hkwd_socketpair_err6            279
#define hkwd_socketpair_err7            280
#define hkwd_socketpair_err8            281
#define hkwd_socketpair_err9            282
#define hkwd_socketpair_err10           283
#define hkwd_socketpair_err11           284
#define hkwd_sendto_err1                285
#define hkwd_sendto_err2                286
#define hkwd_send_err1                  287
#define hkwd_send_err2                  288
#define hkwd_sendmsg_err1               289
#define hkwd_sendmsg_err2               290
#define hkwd_sendmsg_err3               291
#define hkwd_sendmsg_err4               292
#define hkwd_sendmsg_err5               293
#define hkwd_sendmsg_err6               294
#define hkwd_sendmsg_err7               295
#define hkwd_sendmsg_err8               296
#define hkwd_sendmsg_err9               297
#define hkwd_sendmsg_err10              298
#define hkwd_sendmsg_err11              299
#define hkwd_sendmsg_err12              300
#define hkwd_sendmsg_err13              301
#define hkwd_sendmsg_err14              302
#define hkwd_sendmsg_err15              303
#define hkwd_sendmsg_err16              304
#define hkwd_sendmsg_err17              305
#define hkwd_sendmsg_err18              306
#define hkwd_nsendmsg_err1              307
#define hkwd_nsendmsg_err2              308
#define hkwd_nsendmsg_err3              309
#define hkwd_nsendmsg_err4              310
#define hkwd_nsendmsg_err5              311
#define hkwd_nsendmsg_err6              312
#define hkwd_nsendmsg_err7              313
#define hkwd_nsendmsg_err8              314
#define hkwd_nsendmsg_err9              315
#define hkwd_nsendmsg_err10             316
#define hkwd_nsendmsg_err11             317
#define hkwd_nsendmsg_err12             318
#define hkwd_nsendmsg_err13             319
#define hkwd_nsendmsg_err14             320
#define hkwd_nsendmsg_err15             321
#define hkwd_nsendmsg_err16             322
#define hkwd_nsendmsg_err17             323
#define hkwd_nsendmsg_err18             324
#define hkwd_sendit_err1                325
#define hkwd_sendit_err2                326
#define hkwd_sendit_err3                327
#define hkwd_sendit_err4                328
#define hkwd_sendit_err5                329
#define hkwd_sendit_err6                330
#define hkwd_sendit_err7                331
#define hkwd_sendit_err8                332
#define hkwd_sendit_err9                333
#define hkwd_sendit_out1                334
#define hkwd_nrecvfrom_err1             335
#define hkwd_nrecvfrom_err2             336
#define hkwd_nrecvfrom_err3             337
#define hkwd_nrecvfrom_err4             338
#define hkwd_recv_err1                  339
#define hkwd_recv_err2                  340
#define hkwd_recv_err3                  341
#define hkwd_soclose2_abort_call1      	342
#define hkwd_soclose2_abort_call2      	343
#define hkwd_sodisconn_err1   		346
#define hkwd_sodisconn_err2            	347
#define hkwd_soreceive_err1            	348
#define hkwd_soreceive_err2            	349
#define hkwd_soshutdown_err1          	350 
#define hkwd_sonewsock_out1          	351
#define hkwd_sonewsock_out2            	352
#define hkwd_sosbwait_out1            	353
#define hkwd_sosbwait_out2             	354
#define hkwd_soo_select_out1           	355
#define hkwd_soo_select_out2           	356
#define hkwd_sendmsg_out1              	357
#define hkwd_sendmsg_out2              	358
#define hkwd_sendmsg_out3              	359
#define hkwd_sendmsg_out4              	360
#define hkwd_nsendmsg_in               	361
#define hkwd_nsendmsg_out1             	362
#define hkwd_nsendmsg_out2             	363
#define hkwd_nsendmsg_out3            	364
#define hkwd_nsendmsg_out4             	365
#define hkwd_recvmsg_err1               366
#define hkwd_recvmsg_err2               367
#define hkwd_recvmsg_err3               368
#define hkwd_recvmsg_err4               369
#define hkwd_recvmsg_err5               370
#define hkwd_recvmsg_err6               371
#define hkwd_recvmsg_err7               372
#define hkwd_recvmsg_err8               373
#define hkwd_recvmsg_err9               374
#define hkwd_recvmsg_err10              375
#define hkwd_recvmsg_err11              376
#define hkwd_recvmsg_err12              377
#define hkwd_recvmsg_err13              378
#define hkwd_recvmsg_err14              379
#define hkwd_recvmsg_err15              380
#define hkwd_recvmsg_err16              381
#define hkwd_recvmsg_err17              382
#define hkwd_recvmsg_err18              383
#define hkwd_recvmsg_err19              384
#define hkwd_recvmsg_err20              385
#define hkwd_recvmsg_err21              386
#define hkwd_recvmsg_err22              387
#define hkwd_recvmsg_err23              388
#define hkwd_recvmsg_out1               389
#define hkwd_recvmsg_out2               390
#define hkwd_recvmsg_out3               391
#define hkwd_recvmsg_out4               392
#define hkwd_nrecvmsg_in                393
#define hkwd_nrecvmsg_err1              394
#define hkwd_nrecvmsg_err2                    	395
#define hkwd_nrecvmsg_err3                    	396
#define hkwd_nrecvmsg_err4                      397
#define hkwd_nrecvmsg_err5                      398
#define hkwd_nrecvmsg_err6                      399
#define hkwd_nrecvmsg_err7                      400
#define hkwd_nrecvmsg_err8                      401
#define hkwd_nrecvmsg_err9                      402
#define hkwd_nrecvmsg_err10                     403
#define hkwd_nrecvmsg_err11                     404
#define hkwd_nrecvmsg_err12                     405
#define hkwd_nrecvmsg_err13                     406
#define hkwd_nrecvmsg_err14                     407
#define hkwd_nrecvmsg_err15                     408
#define hkwd_nrecvmsg_err16                     409
#define hkwd_nrecvmsg_err17                     410
#define hkwd_nrecvmsg_err18                     411
#define hkwd_nrecvmsg_err19                     412
#define hkwd_nrecvmsg_err20                     413
#define hkwd_nrecvmsg_err21                     414
#define hkwd_nrecvmsg_err22                     415
#define hkwd_nrecvmsg_err23                     416
#define hkwd_nrecvmsg_err24                     417
#define hkwd_nrecvmsg_err25                     418
#define hkwd_nrecvmsg_err26                     419
#define hkwd_nrecvmsg_err27                     420
#define hkwd_nrecvmsg_err28                     421
#define hkwd_nrecvmsg_out1                      422
#define hkwd_nrecvmsg_out2                      423
#define hkwd_nrecvmsg_out3                      424
#define hkwd_recvit_err1                        425
#define hkwd_recvit_err2                        426
#define hkwd_recvit_err3                        427
#define hkwd_recvit_err4                        428
#define hkwd_recvit_err5                        429
#define hkwd_recvit_err6                        430
#define hkwd_recvit_err7                        431
#define hkwd_shutdown_err1                      432
#define hkwd_setsockopt_err1                    433
#define hkwd_setsockopt_err2                    434
#define hkwd_setsockopt_err3                    435
#define hkwd_setsockopt_err4                    436
#define hkwd_setsockopt_err5                    437
#define hkwd_getsockopt_err1                    438
#define hkwd_getsockopt_err2                    439
#define hkwd_getsockopt_err3                    440
#define hkwd_getsockopt_err4                    441
#define hkwd_getsockopt_err5                    442
#define hkwd_getsockopt_err6                    443
#define hkwd_getsockopt_err7                    444
#define hkwd_getsockname_err1                   445
#define hkwd_getsockname_err2                   446
#define hkwd_getsockname_err3                   447
#define hkwd_getsockname_err4                   448
#define hkwd_getsockname_err5                   449
#define hkwd_getsockname_err6                   450
#define hkwd_getsockname_err7                   451
#define hkwd_getsockname_err8                   452
#define hkwd_getpeername_err1                   453
#define hkwd_getpeername_err2                   454
#define hkwd_getpeername_err3                   455
#define hkwd_getpeername_err4                   456
#define hkwd_getpeername_err5                   457
#define hkwd_getpeername_err6                   458
#define hkwd_getpeername_err7                   459
#define hkwd_getpeername_err8                   460
#define hkwd_getpeername_err9                   461
#define hkwd_getpeereid_err1                    462
#define hkwd_getpeereid_err2                    463
#define hkwd_getpeereid_err3                    464
#define hkwd_getpeereid_err4                    465
#define hkwd_getpeereid_err5                    466
#define hkwd_getpeereid_err6                    467
#define hkwd_getpeereid_err7                    468
#define hkwd_sockargs_err1                      469
#define hkwd_sockargs_err2                      470
#define hkwd_sockargs_err3                      471
#define hkwd_sockargs_err4                      472
#define hkwd_socksetup_err1                     473
#define hkwd_socksetup_err2                     474
#define hkwd_getkerninfo_err1                   476
#define hkwd_getkerninfo_err2                   477
#define hkwd_getkerninfo_err3                   478
#define hkwd_getkerninfo_err4                   479
#define hkwd_getkerninfo_err5                   480
#define hkwd_getkerninfo_err6                   481
#define hkwd_getkerninfo_err7                   482
#define hkwd_getkerninfo_err8                   483
#define hkwd_getkerninfo_err9                   484
#define hkwd_getkerninfo_err10                  485
#define hkwd_getkerninfo_err11                  486
#define hkwd_getkerninfo_err12                  487
#define hkwd_getkerninfo_err13                  488
#define hkwd_getkerninfo_err14                  489
#define hkwd_getkerninfo_err15                  490
#define hkwd_getkerninfo_err16                  491
#define hkwd_getkerninfo_err17                  492
#define hkwd_getkerninfo_err18                  493
#define hkwd_getkerninfo_err19                  494
#define hkwd_getkerninfo_err20                  495
#define hkwd_socket_aio_dequeue_err1            496
#define hkwd_socket_aio_dequeue_err2            497
#define hkwd_kinfo_read_err1                    498
#define hkwd_kinfo_read_err2                    499
#define hkwd_kinfo_write_err1                   500
#define hkwd_kinfo_write_err2                   501
#define hkwd_splice_err1                        502
#define hkwd_splice_err2                        503
#define hkwd_sctp_opt_info_err1                 504
#define hkwd_sctp_opt_info_err2                 505
#define hkwd_sctp_opt_info_err3                 506
#define hkwd_sctp_opt_info_err4                 507
#define hkwd_sctp_opt_info_err5                 508
#define hkwd_sctp_opt_info_err6                 509
#define hkwd_sctp_peeloff_err1                  510
#define hkwd_sctp_peeloff_err2                  511
#define hkwd_sctp_peeloff_err3                  512
#define hkwd_sctp_peeloff_err4                  513
#define hkwd_sctp_peeloff_err5                  514
#define hkwd_sctp_peeloff_err6                  515
#define hkwd_sctp_peeloff_err7                  516
#define hkwd_sctp_peeloff_err8                  517
#define hkwd_k_getgroups_err1           	518
#define hkwd_k_getgroups_err2           	519
#define hkwd_sosplice_err3              	520	
#define hkwd_sodisconnectreuse_err1		521	
#define hkwd_sosbwait_err2              	522	
#define hkwd_soo_ioctl_err21            	523	
#define hkwd_soo_ioctl_err22            	524	
#define hkwd_soo_ioctl_err23            	525	
#define hkwd_soo_ioctl_err24           		526 
#define hkwd_soo_ioctl_err25           		527 
#define hkwd_socket_err2                	528	
#define hkwd_bind_err4                 	 	529
#define hkwd_listen_err1               		530 
#define hkwd__connect_err4              	531	
#define hkwd__connect_err5              	532	
#define hkwd__connect_err6              	533	
#define hkwd_send_err3                 		534	

#define HKWD_TCP			0x53500000
#define hkwd_isprivport_in			1
#define hkwd_reroute_in				2
#define hkwd_splice_forward_in			3
#define hkwd_splice_forward_out			4
#define hkwd_tcp_SACKFastRecovery_in		5
#define hkwd_tcp_UpSACKInfo_in			6
#define hkwd_tcp_UpSACKInfo_out			7
#define hkwd_tcp_achalloc_in			8
#define hkwd_tcp_achfree_in			9
#define hkwd_tcp_achref_out			10
#define hkwd_tcp_achset_out			11
#define hkwd_tcp_acladd_in			12
#define hkwd_tcp_acladd_out			13
#define hkwd_tcp_aclbind_in			14
#define hkwd_tcp_aclclear_nolock_in		15
#define hkwd_tcp_acldel_in			16
#define hkwd_tcp_acldel_out			17
#define hkwd_tcp_aclflush_in			18
#define hkwd_tcp_aclls_in			19
#define hkwd_tcp_aclls_out			20
#define hkwd_tcp_adjust_buffers_in		21
#define hkwd_tcp_adjust_buffers_out		22
#define hkwd_tcp_attach_in			23
#define hkwd_tcp_attach_out			24
#define hkwd_tcp_auth0_in			25
#define hkwd_tcp_auth0_out1			26
#define hkwd_tcp_auth0_out2			27
#define hkwd_tcp_auth_in			28
#define hkwd_tcp_auth_out1			29
#define hkwd_tcp_auth_out2			30
#define hkwd_tcp_build_sacks_err		31
#define hkwd_tcp_build_sacks_in			32
#define hkwd_tcp_build_sacks_out		33
#define hkwd_tcp_canceltimers			34
#define hkwd_tcp_close_in			35
#define hkwd_tcp_close_out			36
#define hkwd_tcp_ctlinput_in			37
#define hkwd_tcp_ctlinput_out			38
#define hkwd_tcp_ctloutput_in			39
#define hkwd_tcp_ctloutput_out			40
#define hkwd_tcp_delayack_set_in		41
#define hkwd_tcp_delayack_set_out		42
#define hkwd_tcp_disconnect_in			43
#define hkwd_tcp_disconnect_out			44
#define hkwd_tcp_dooptions_in			45
#define hkwd_tcp_dooptions_out			46
#define hkwd_tcp_drop_in			47
#define hkwd_tcp_ephemeral_high_change_in	48
#define hkwd_tcp_ephemeral_high_change_out	49
#define hkwd_tcp_ephemeral_low_change_in	50
#define hkwd_tcp_ephemeral_low_change_out	51
#define hkwd_tcp_fasttimo_in			52
#define hkwd_tcp_fasttimo_out			53
#define hkwd_tcp_init_in			54
#define hkwd_tcp_init_out			55
#define hkwd_tcp_input0_in			56
#define hkwd_tcp_input0_out1			57
#define hkwd_tcp_input0_out2			58
#define hkwd_tcp_input0_out3			59
#define hkwd_tcp_input0_out4			60
#define hkwd_tcp_input0_out5			61
#define hkwd_tcp_input0_out6			62
#define hkwd_tcp_input0_out7			63
#define hkwd_tcp_input0_out8			64
#define hkwd_tcp_input0_out9			65
#define hkwd_tcp_input_in			66
#define hkwd_tcp_input_out			67
#define hkwd_tcp_lspriv_in			68
#define hkwd_tcp_lspriv_out			69
#define hkwd_tcp_map_pseg_in			70
#define hkwd_tcp_map_pseg_out			71
#define hkwd_tcp_mss_in				72
#define hkwd_tcp_mss_out			73
#define hkwd_tcp_newtcpcb_in			74
#define hkwd_tcp_newtcpcb_out			75
#define hkwd_tcp_notify_in			76
#define hkwd_tcp_notify_out			77
#define hkwd_tcp_output_in			78
#define hkwd_tcp_output_out			79
#define hkwd_tcp_pmtuchange_in			80
#define hkwd_tcp_process_sackopt_in		81
#define hkwd_tcp_process_sackopt_out1		82
#define hkwd_tcp_process_sackopt_out2		83
#define hkwd_tcp_pulloutofband_in		84
#define hkwd_tcp_pulloutofband_out		85
#define hkwd_tcp_quench_in			86
#define hkwd_tcp_reass_in			87
#define hkwd_tcp_reass_out1			88
#define hkwd_tcp_reass_out2			89
#define hkwd_tcp_reass_out3			90
#define hkwd_tcp_reass_out4			91
#define hkwd_tcp_reass_out5			92
#define hkwd_tcp_resend_in			93
#define hkwd_tcp_resend_out			94
#define hkwd_tcp_resprst_err			95
#define hkwd_tcp_resprst_in			96
#define hkwd_tcp_resprst_out			97
#define hkwd_tcp_send_and_disconnect_err	98
#define hkwd_tcp_send_and_disconnect_in		99
#define hkwd_tcp_send_and_disconnect_out	100
#define hkwd_tcp_send_and_kern_disconnect_err	101
#define hkwd_tcp_send_and_kern_disconnect_in	102
#define hkwd_tcp_send_and_kern_disconnect_out	103
#define hkwd_tcp_sendkeep_err			104
#define hkwd_tcp_sendkeep_in			105
#define hkwd_tcp_sendkeep_out			106
#define hkwd_tcp_setmss_in			107
#define hkwd_tcp_setmss_out			108
#define hkwd_tcp_setpersist_in			109
#define hkwd_tcp_setpersist_out			110
#define hkwd_tcp_setpriv_in			111
#define hkwd_tcp_setpriv_out			112
#define hkwd_tcp_slowtimo_in			113
#define hkwd_tcp_slowtimo_out			114
#define hkwd_tcp_splice_in			115
#define hkwd_tcp_splice_out			116
#define hkwd_tcp_template_in			117
#define hkwd_tcp_time_wait_timer_in		118
#define hkwd_tcp_time_wait_timer_out		119
#define hkwd_tcp_timer_init_in			120
#define hkwd_tcp_timers_in			121
#define hkwd_tcp_timers_out			122
#define hkwd_tcp_unsetpriv_in			123
#define hkwd_tcp_unsetpriv_out			124
#define hkwd_tcp_update_sacks_in		125
#define hkwd_tcp_update_sacks_out		126
#define hkwd_tcp_usrclosed_in			127
#define hkwd_tcp_usrclosed_out			128
#define hkwd_tcp_usrreq_err			129
#define hkwd_tcp_usrreq_in			130
#define hkwd_tcp_usrreq_out			131
#define hkwd_tcp_xmit_timer_in			132
#define hkwd_tcp_xmit_timer_out			133
#define hkwd_tcp_UpSACKInfo_out1                134
#define hkwd_tcp_build_sacks_out1               136
#define hkwd_tcp_build_sacks_out2               137
#define hkwd_tcp_build_sacks_out3               138
#define hkwd_tcp_build_sacks_out4               139
#define hkwd_tcp_input0_out10                   140
#define hkwd_tcp_input0_out11                   141
#define hkwd_tcp_input0_out12                   142
#define hkwd_tcp_input0_out13                   143
#define hkwd_tcp_input0_out14                   144
#define hkwd_tcp_input0_out15                   145
#define hkwd_tcp_input0_out16                   146
#define hkwd_tcp_input0_out17                   147
#define hkwd_tcp_input0_out18                   148
#define hkwd_tcp_input0_out19                   149
#define hkwd_tcp_input0_out20                   150
#define hkwd_tcp_input0_out21                   151
#define hkwd_tcp_input0_out22                   152
#define hkwd_tcp_input0_out23                   153
#define hkwd_tcp_input0_out24                   154
#define hkwd_tcp_input0_out25                   155
#define hkwd_tcp_input0_out26                   156
#define hkwd_tcp_input0_out27                   157
#define hkwd_tcp_input0_out28                   158
#define hkwd_tcp_input0_out29                   159
#define hkwd_tcp_input0_out30                   160
#define hkwd_tcp_input0_out31                   161
#define hkwd_tcp_input0_out32                   162
#define hkwd_tcp_input0_out33                   163
#define hkwd_tcp_input0_out34                   164
#define hkwd_tcp_input0_out35                   165
#define hkwd_tcp_input0_out36                   166
#define hkwd_tcp_input0_out37                   167
#define hkwd_tcp_input0_out38                   168
#define hkwd_tcp_input0_out39                   169
#define hkwd_tcp_input0_out40                   170
#define hkwd_tcp_input0_out41                   171
#define hkwd_tcp_input0_out42                   172
#define hkwd_tcp_input0_out43                   173
#define hkwd_tcp_input0_out44                   174
#define hkwd_tcp_input0_out45                   175
#define hkwd_tcp_input0_out46                   176
#define hkwd_tcp_input0_out47                   177
#define hkwd_tcp_input0_out48                   178
#define hkwd_tcp_input0_out49                   179
#define hkwd_tcp_input0_out50                   180
#define hkwd_tcp_input0_out51                   181
#define hkwd_tcp_input0_out52                   182
#define hkwd_tcp_input0_out53                   183
#define hkwd_tcp_input0_out54                   184
#define hkwd_tcp_input0_out55                   185
#define hkwd_tcp_input0_out56                   186
#define hkwd_tcp_input0_out57                   187
#define hkwd_tcp_input0_win1                    188
#define hkwd_tcp_process_sackopt_out3           191
#define hkwd_tcp_process_sackopt_out4           192
#define hkwd_tcp_auth_out3                      193
#define hkwd_tcp_mss_out1                       194
#define hkwd_tcp_setmss_out1                    195
#define hkwd_tcp_map_pseg_out1                  197
#define hkwd_tcp_output_sack_enabled1           198
#define hkwd_tcp_output_sack_enabled2           199
#define hkwd_tcp_output_update_snd_lowat	203
#define hkwd_tcp_output_out1                    204
#define hkwd_tcp_output_out2                    205
#define hkwd_tcp_output_out3                    206
#define hkwd_tcp_output_out4                    207
#define hkwd_tcp_output_out5                    208
#define hkwd_tcp_output_out6                    209
#define hkwd_tcp_output_out7                    210
#define hkwd_tcp_output_out8                    211
#define hkwd_tcp_output_out9                    212
#define hkwd_tcp_output_out10                   213
#define hkwd_tcp_output_out11                   214
#define hkwd_tcp_output_out12                   215
#define hkwd_tcp_newtcpcb_out1                  217
#define hkwd_tcp_notify_out1                    218
#define hkwd_tcp_ctlinput_out1                  220
#define hkwd_tcp_ctlinput_out2                  221
#define hkwd_tcp_ctlinput_out3                  222
#define hkwd_tcp_delayack_set_out1              223
#define hkwd_tcp_delayack_set_out2              224
#define hkwd_tcp_delayack_set_out3              225
#define hkwd_tcp_delayack_set_out4              226
#define hkwd_tcp_timers_out1                    227
#define hkwd_tcp_usrreq_err1                    228
#define hkwd_tcp_usrreq_err2                    229
#define hkwd_tcp_usrreq_err3                    230
#define hkwd_tcp_usrreq_err4                    231
#define hkwd_tcp_usrreq_err5                    232
#define hkwd_tcp_usrreq_out1                    233
#define hkwd_tcp_usrreq_out2                    234
#define hkwd_tcp_usrreq_out3                    235
#define hkwd_tcp_usrreq_out4                    236
#define hkwd_tcp_usrreq_out5                    237
#define hkwd_tcp_usrreq_out6                    238
#define hkwd_tcp_usrreq_out7                    239
#define hkwd_tcp_usrreq_out8                    240
#define hkwd_tcp_usrreq_out9                    241
#define hkwd_tcp_usrreq_out10                   242
#define hkwd_tcp_usrreq_err6                    243
#define hkwd_tcp_acladd_out1                    244
#define hkwd_tcp_acladd_out2                    245
#define hkwd_tcp_acladd_out3                    246
#define hkwd_tcp_acladd_out4                    247
#define hkwd_tcp_acldel_out1                    248
#define hkwd_tcp_acldel_out2                    249
#define hkwd_tcp_acldel_out3                    250
#define hkwd_tcp_aclls_out1                     251
#define hkwd_tcp_aclls_out2                     252
#define hkwd_tcp_aclls_out3                     253
#define hkwd_tcp_lspriv_out1                    254
#define hkwd_tcp_ctloutput_err			255
#define hkwd_tcp_attach_out1                    256
#define hkwd_tcp_attach_out2                    257
#define hkwd_tcp_attach_out3                    258
#define hkwd_tcp_splice_out1                    259
#define hkwd_tcp_splice_out2                    260
#define hkwd_tcp_reroute_out			261
#define hkwd_tcp_UpSACKInfo_out2		262
#define hkwd_tcp_reass_out			263
#define hkwd_tcp_input0_out58			264
#define hkwd_tcp_output_out13			265
#define hkwd_tcp_output_out14			266
#define hkwd_tcp_output_out15			267
#define hkwd_tcp_output_pmtu_alloc_fail		268
#define hkwd_tcp_usrreq_err7			269
#define hkwd_tcp_usrreq_err8			270
#define hkwd_tcp_usrreq_err9			271
#define hkwd_tcp_usrreq_err10			272
#define hkwd_tcp_usrreq_err11			273
#define hkwd_tcp_usrreq_err12			274
#define hkwd_tcp_usrreq_err13			275
#define hkwd_tcp_usrreq_err14			276
#define hkwd_tcp_usrreq_err15			277
#define hkwd_tcp_usrreq_err16			278
#define hkwd_tcp_usrreq_err17			279
#define hkwd_tcp_usrreq_pru_abort		280
#define hkwd_timer_wheel_init_in                281
#define hkwd_timer_wheel_init_out               282
#define hkwd_timer_wheel_slot_ins_in            283
#define hkwd_timer_wheel_slot_ins_out           284
#define hkwd_timer_wheel_slot_del_in            285
#define hkwd_timer_wheel_slot_del_out           286
#define hkwd_timer_wheel_sched_timer_in         287
#define hkwd_timer_wheel_sched_timer_out        288
#define hkwd_timer_wheel_resched_timer_in       289
#define hkwd_timer_wheel_resched_timer_out      290
#define hkwd_timer_wheel_cancel_timer_in        291
#define hkwd_timer_wheel_cancel_timer_out       292
#define hkwd_timer_wheel_tick_timeout_in        293
#define hkwd_timer_wheel_tick_timeout_out       294
#define hkwd_twheelsched_in                     295
#define hkwd_twheelsched_out                    296
#define hkwd_tcp_disconnect_out_error		297


#define HKWD_UDP			0x53600000
#define hkwd_delay_sbdroprecord   		1
#define hkwd_udp_cksum_and_move_in   		2
#define hkwd_udp_cksum_and_move_out   		3
#define hkwd_udp_ctlinput_in   			4
#define hkwd_udp_ctlinput_out   		5
#define hkwd_udp_ephemeral_high_change_in   	6
#define hkwd_udp_ephemeral_low_change_in   	7
#define hkwd_udp_findmac_in   			8
#define hkwd_udp_findmac_out1   		9
#define hkwd_udp_findmac_out2   		10
#define hkwd_udp_init_in   			11
#define hkwd_udp_init_out   			12
#define hkwd_udp_input0_in   			13
#define hkwd_udp_input0_out1   			14
#define hkwd_udp_input0_out2   			15
#define hkwd_udp_input0_out3   			16
#define hkwd_udp_input0_out4   			17
#define hkwd_udp_input0_out5   			18
#define hkwd_udp_input1_in   			19
#define hkwd_udp_input1_out   			20
#define hkwd_udp_input_in   			21
#define hkwd_udp_input_out   			22
#define hkwd_udp_output_in   			23
#define hkwd_udp_output_out   			24
#define hkwd_udp_receive_in   			25
#define hkwd_udp_receive_out   			26
#define hkwd_udp_saveopt_in   			27
#define hkwd_udp_saveopt_out1   		28
#define hkwd_udp_saveopt_out2   		29
#define hkwd_udp_saveopt_out3   		30
#define hkwd_udp_saveopt_out4   		31
#define hkwd_udp_usrreq_in   			32
#define hkwd_udp_usrreq_out   			33
#define hkwd_udpsend_in   			34
#define hkwd_udpsend_out   			35
#define hkwd_udp_ephemeral_low_change_err1      36
#define hkwd_udp_ephemeral_high_change_err1     37
#define hkwd_udp_input0_err1                    38
#define hkwd_udp_input0_err2                    39
#define hkwd_udp_input0_err3                    40
#define hkwd_udp_input0_err4                    41
#define hkwd_udp_input0_err5                    42
#define hkwd_udp_input0_err6                    43
#define hkwd_udp_input0_err7                    44
#define hkwd_udp_input0_err8                    45
#define hkwd_udp_input0_err9                    46
#define hkwd_udp_input0_err10                   47
#define hkwd_udp_ctlinput_err1                  48
#define hkwd_udp_output_err1                    49
#define hkwd_udp_output_err2                    50
#define hkwd_udp_output_err3                    51
#define hkwd_udp_output_err4                    52
#define hkwd_udp_output_err5                    53
#define hkwd_udp_output_err6                    54
#define hkwd_udp_output_err7                    55
#define hkwd_udp_output_err8                    56
#define hkwd_udp_output_err9                    57
#define hkwd_udp_output_err10                   58
#define hkwd_udp_usrreq_err1                    59
#define hkwd_udp_usrreq_err2                    60
#define hkwd_udp_usrreq_err3                    61
#define hkwd_udp_usrreq_err4                    62
#define hkwd_udp_usrreq_err5                    63
#define hkwd_udpsend_err1                       64
#define hkwd_udpsend_err2                       65
#define hkwd_udpsend_err3                       66
#define hkwd_udpsend_err4                       67
#define hkwd_udpsend_err5                       68
#define hkwd_udpsend_err6                       69
#define hkwd_udpsend_err7                       70
#define hkwd_udpsend_err8                       71
#define hkwd_udpsend_err9                       72
#define hkwd_udpsend_err10                      73
#define hkwd_udpsend_err11                      74
#define hkwd_udpsend_err12                      75
#define hkwd_udpsend_err13                      76
#define hkwd_udpsend_err14                      77
#define hkwd_udpsend_err15                      78
#define hkwd_udpsend_err16                      79
#define hkwd_udpsend_err17                      80
#define hkwd_udpsend_err18                      81
#define hkwd_udpsend_err19                      82
#define hkwd_udp_receive_err1                   83
#define hkwd_udp_receive_err2                   84
#define hkwd_udp_receive_err3                   85
#define hkwd_udp_receive_err4                   86
#define hkwd_udp_receive_err5                   87
#define hkwd_udp_receive_err6                   88
#define hkwd_udp_receive_err7                   89
#define hkwd_udp_receive_err8                   90
#define hkwd_udp_receive_err9                   91
#define hkwd_udp_receive_err10                  92
#define hkwd_udp_receive_err11                  93
#define hkwd_udp_usrreq_abort                   94
#define hkwd_udp_notify_in                      95
#define hkwd_udp_output_ip_output               96
#define hkwd_udp_send_ip_output                 97
#define hkwd_udp_usrreq_err6			98


#define HKWD_IP			0x53700000
#define hkwd_add_mfc_in			1
#define hkwd_add_mfc_out		2
#define hkwd_add_vif_in			3
#define hkwd_add_vif_out		4
#define hkwd_del_mfc_in			5
#define hkwd_del_mfc_out		6
#define hkwd_del_vif_in			7
#define hkwd_del_vif_out		8
#define hkwd_dequeue_pfctlinput_in	9
#define hkwd_dequeue_pfctlinput_out	10
#define hkwd_doghash_in			11
#define hkwd_doghash_out1		12
#define hkwd_doghash_out2		13
#define hkwd_doginit_in			14
#define hkwd_doginit_out1		15
#define hkwd_doginit_out2		16
#define hkwd_doginit_out3		17
#define hkwd_doginit_out4		18
#define hkwd_dogisr_in			19
#define hkwd_dogisr_out			20
#define hkwd_dogproc_in			21
#define hkwd_dogproc_out		22
#define hkwd_dogthread_in		23
#define hkwd_dogthread_out		24
#define hkwd_encap_send_in		25
#define hkwd_encap_send_out		26
#define hkwd_expire_upcalls_in		27
#define hkwd_expire_upcalls_out		28
#define hkwd_get_sg_cnt_in		29
#define hkwd_get_sg_cnt_out		30
#define hkwd_get_vif_cnt_in		31
#define hkwd_get_vif_cnt_out		32
#define hkwd_gids_ok_in			33
#define hkwd_gids_ok_out		34
#define hkwd_icmp_error_in		35
#define hkwd_icmp_error_out		36
#define hkwd_icmp_input_in		37
#define hkwd_icmp_input_out		38
#define hkwd_icmp_reflect_in		39
#define hkwd_icmp_reflect_out		40
#define hkwd_icmp_send_in		41
#define hkwd_icmp_send_out		42
#define hkwd_in_flip_and_run_in		43
#define hkwd_in_flip_and_run_out	44
#define hkwd_inbound_fw_free_args_in	45
#define hkwd_inbound_fw_save_args_in	46
#define hkwd_inbound_fw_save_args_out	47
#define hkwd_ip_changeversion_in	48
#define hkwd_ip_changeversion_out	49
#define hkwd_ip_ctloutput_in		50
#define hkwd_ip_ctloutput_out		51
#define hkwd_ip_dootions_in		52
#define hkwd_ip_drain_in		53
#define hkwd_ip_flush_packet_in		54
#define hkwd_ip_flush_packet_out	55
#define hkwd_ip_forward_in		56
#define hkwd_ip_forward_out1		57
#define hkwd_ip_forward_out2		58
#define hkwd_ip_forward_out3		59
#define hkwd_ip_forward_out4		60
#define hkwd_ip_forward_out5		61
#define hkwd_ip_freef_in		62
#define hkwd_ip_freemoptions_in		63
#define hkwd_ip_freemoptions_out	64
#define hkwd_ip_getmoptions_in		65
#define hkwd_ip_getmoptions_out		66
#define hkwd_ip_init_in			67
#define hkwd_ip_init_out		68
#define hkwd_ip_intr_in			69
#define hkwd_ip_intr_out		70
#define hkwd_ip_insertoptions_in	71
#define hkwd_ip_insertoptions_out	72
#define hkwd_ip_mdq_in			73
#define hkwd_ip_mdq_out			74
#define hkwd_ip_mforward_in		75
#define hkwd_ip_mforward_out		76
#define hkwd_ip_mloopback_in		77
#define hkwd_ip_mloopback_out		78
#define hkwd_ip_mrouter_done_in		79
#define hkwd_ip_mrouter_done_out	80
#define hkwd_ip_mrouter_get_in		81
#define hkwd_ip_mrouter_init_in		82
#define hkwd_ip_mrouter_init_out	83
#define hkwd_ip_mrouter_set_in		84
#define hkwd_ip_output_in		85
#define hkwd_ip_output_post_fw_in	86
#define hkwd_ip_output_post_fw_out	87
#define hkwd_ip_pcbopts_in		88
#define hkwd_ip_pcbopts_out1		89
#define hkwd_ip_pcbopts_out2		90
#define hkwd_ip_pmtu_start_in		91
#define hkwd_ip_pmtu_start_out		92
#define hkwd_ip_pmtu_stopt_in		93
#define hkwd_ip_pmtu_stopt_out		94
#define hkwd_ip_pmtu_timeout_in		95
#define hkwd_ip_pmtu_timeout_out	96
#define hkwd_ip_reass_in		97
#define hkwd_ip_reass_out1		98
#define hkwd_ip_reass_out2		99
#define hkwd_ip_rsvp_force_done_in	100
#define hkwd_ip_rsvp_force_done_out	101
#define hkwd_ip_rsvp_vif_done_in	102
#define hkwd_ip_rsvp_vif_done_out	103
#define hkwd_ip_rsvp_vif_init_in	104
#define hkwd_ip_rsvp_vif_init_out	105
#define hkwd_ip_rtaddr_in		106
#define hkwd_ip_rtaddr_out		107
#define hkwd_ip_setdupmtu_in		108
#define hkwd_ip_setdupmtu_out		109
#define hkwd_ip_setmoptions_in		110
#define hkwd_ip_setmoptions_out		111
#define hkwd_ip_slowtimo_in		112
#define hkwd_ip_srcroute_in		113
#define hkwd_ip_srcroute_out		114
#define hkwd_ip_stripoptions_in		115
#define hkwd_ip_stripoptions_out	116
#define hkwd_ipintr_noqueue_in		117
#define hkwd_ipintr_noqueue_out		118
#define hkwd_ipintr_noqueue_post_fw_in	119
#define hkwd_ipintr_noqueue_post_fw_out	120
#define hkwd_ipip_input_in		121
#define hkwd_ipip_input_out		122
#define hkwd_localaddr_notcast_in	123
#define hkwd_localaddr_notcast_out	124
#define hkwd_mroute_init_in		125
#define hkwd_mrt_ioctl_in		126
#define hkwd_outbound_fw_free_args_in	127
#define hkwd_outbound_fw_free_args_out	128
#define hkwd_outbound_fw_save_args_in	129
#define hkwd_outbound_fw_save_args_out	130
#define hkwd_phyint_send_in		131
#define hkwd_phyint_send_out		132
#define hkwd_pmtu_default_age_init_in	133
#define hkwd_pmtu_default_age_upd_in	134
#define hkwd_pmtu_default_age_upd_out	135
#define hkwd_pmtu_redis_intrvl_init_in	136
#define hkwd_pmtu_rtrequest_in		137
#define hkwd_pmtu_rtrequest_out		138
#define hkwd_priority_in		139
#define hkwd_priority_out		140
#define hkwd_queue_pfctlinput_in	141
#define hkwd_queue_pfctlinput_out	142
#define hkwd_raw_saveif_in		143
#define hkwd_raw_saveif_out		144
#define hkwd_rip_ctloutput_in		145
#define hkwd_rip_ctloutput_out		146
#define hkwd_rip_init_in		147
#define hkwd_rip_init_out		148
#define hkwd_rip_input_in		149
#define hkwd_rip_output_in		150
#define hkwd_rip_output_out		151
#define hkwd_rip_usrreq_in		152
#define hkwd_rip_usrreq_out		153
#define hkwd_rsvp_input_in		154
#define hkwd_rsvp_input_out		155
#define hkwd_save_rte_in		156
#define hkwd_save_rte_out		157
#define hkwd_socket_send_in		158
#define hkwd_socket_send_out		159
#define hkwd_tbf_control_in		160
#define hkwd_tbf_control_out		161
#define hkwd_tbf_dq_sel_in		162
#define hkwd_tbf_dq_sel_out		163
#define hkwd_tbf_process_q_in		164
#define hkwd_tbf_process_q_out		165
#define hkwd_tbf_reprocess_q_in		166
#define hkwd_tbf_reprocess_q_out	167
#define hkwd_tbf_send_packet_in		168
#define hkwd_tbf_send_packet_out	169
#define hkwd_tcp_pmtu_discover_init_in	170
#define hkwd_tcp_pmtu_discover_init_out	171
#define hkwd_tcp_pmtu_discover_upd_in	172
#define hkwd_tcp_pmtu_discover_upd_out	173
#define hkwd_udp_pmtu_discover_init_in	174
#define hkwd_udp_pmtu_discover_init_out	175
#define hkwd_udp_pmtu_discover_upd_in	176
#define hkwd_udp_pmtu_discover_upd_out	177
#define hkwd_outbound_fw_save_args_out1		178
#define hkwd_outbound_fw_save_args_out2		179
#define hkwd_outbound_fw_save_args_out3		180
#define hkwd_ip_output_post_fw_err1		181
#define hkwd_ip_output_post_fw_err2		182
#define hkwd_ip_output_post_fw_err3		183
#define hkwd_ip_output_post_fw_err4		184
#define hkwd_ip_output_post_fw_err5		185
#define hkwd_ip_output_post_fw_err6		186
#define hkwd_ip_output_post_fw_err7		187
#define hkwd_ip_output_post_fw_err8		188
#define hkwd_ip_output_post_fw_err9		189
#define hkwd_ip_output_post_fw_err10		190
#define hkwd_ip_output_post_fw_err11		191
#define hkwd_ip_output_post_fw_err12		192
#define hkwd_ip_output_post_fw_err13		193
#define hkwd_ip_output_post_fw_err14		194
#define hkwd_ip_output_post_fw_err15		195
#define hkwd_ip_output_post_fw_err16		196
#define hkwd_ip_output_post_fw_err17		197
#define hkwd_ip_output_post_fw_err18		198
#define hkwd_ip_output_post_fw_err19		199
#define hkwd_ip_insertoptions_out1		200
#define hkwd_ip_ctloutput_err1			201
#define hkwd_ip_ctloutput_err2			202	
#define hkwd_ip_ctloutput_err3			203
#define hkwd_ip_changeversion_err1		204
#define hkwd_ip_changeversion_err2		205
#define hkwd_ip_changeversion_err3		206
#define hkwd_ip_changeversion_err4		207
#define hkwd_localaddr_notcast_out1		208
#define hkwd_localaddr_notcast_out2		209
#define hkwd_localaddr_notcast_out3		210
#define hkwd_localaddr_notcast_out4		211
#define hkwd_ip_setmoptions_err1		212
#define hkwd_ip_setmoptions_err2		213
#define hkwd_ip_setmoptions_err3		214
#define hkwd_ip_setmoptions_err4		215
#define hkwd_ip_setmoptions_err5		216
#define hkwd_ip_getmoptions_err1		217
#define hkwd_ip_getmoptions_err2		218
#define hkwd_ip_getmoptions_out1		219
#define hkwd_ip_getmoptions_out2		220
#define hkwd_ip_getmoptions_out3		221
#define hkwd_ip_pcbopts_err1			222
#define hkwd_ip_pcbopts_err2			223
#define hkwd_ip_pcbopts_err3			224
#define hkwd_ip_pcbopts_err4			225
#define hkwd_ip_pcbopts_err5			226
#define hkwd_ip_intr_out1		227	
#define hkwd_ip_intr_out2		228
#define hkwd_inbound_fw_save_args_out1	229
#define hkwd_ip_dooptions_out		230
#define hkwd_ip_dooptions_out1		231
#define hkwd_ip_dooptions_out2		232
#define hkwd_ip_rtaddr_out1		233
#define hkwd_ip_rtaddr_out2		234
#define hkwd_gids_ok_out1		235
#define hkwd_gids_ok_out2		236
#define hkwd_gids_ok_out3		237
#define hkwd_save_rte_out1		238
#define hkwd_ip_srcroute_out1		239
#define hkwd_ip_srcroute_out2		240
#define hkwd_ip_forward_out6		241
#define hkwd_dogisr_out1		242
#define hkwd_dogisr_out2		243
#define hkwd_doghash_out3		244
#define hkwd_doghash_out4		245
#define hkwd_doghash_out5		246
#define hkwd_doghash_out6		247
#define hkwd_doghash_out7		248
#define hkwd_doghash_out8		249
#define hkwd_doghash_out9		250
#define hkwd_doghash_out10		251
#define hkwd_doghash_out11		252
#define hkwd_doghash_out12		253
#define hkwd_doghash_out13		254
#define hkwd_doghash_out14		255
#define hkwd_doghash_out15		256
#define hkwd_doghash_out16		257
#define hkwd_ip_reass_err1		258
#define hkwd_ip_reass_out3		259
#define hkwd_ip_reass_out4		260
#define hkwd_ip_insertoptions_out2		261
#define hkwd_udp_pmtu_discover_init_out1	262	
#define hkwd_tcp_pmtu_discover_init_out1	263
#define hkwd_pmtu_delete_not_found		264
#define hkwd_pmtu_delete_in			265
#define hkwd_pmtu_delete_out			266
#define hkwd_pmtu_expire_init_in		267
#define hkwd_pmtu_expire_init_out		268
#define hkwd_ip_pmtu_timeout_out1		269
#define hkwd_ip_pmtu_timeout_out2		270
#define hkwd_ip_pmtu_timeout_out3		271
#define hkwd_ip_pmtu_timeout_out4		272
#define hkwd_pmtu_equalifmtu_in         	273
#define hkwd_pmtu_setmtu_in             	274
#define hkwd_pmtu_del_request_usr            	275
#define hkwd_pmtu_del_request_route            	276
#define hkwd_pmtu_rediscover_v4         	277
#define hkwd_pmtu_rediscover_v6         	278
#define hkwd_pmtu_expire_upd_in			279
#define hkwd_pmtu_expire_upd_out		280
#define hkwd_pmtu_alloc_in			281
#define hkwd_pmtu_alloc_out			282
#define hkwd_pmtu_alloc_out1			283
#define hkwd_pmtu_alloc_out2			284
#define hkwd_pmtu_alloc_out3			285
#define hkwd_pmtu_alloc_out4			286
#define hkwd_ipintr_noqueue_post_fw_err1	287
#define hkwd_ipintr_noqueue_post_fw_err2	288
#define hkwd_ipintr_noqueue_post_fw_err3	289
#define hkwd_ipintr_noqueue_post_fw_err4	290
#define hkwd_ipintr_noqueue_post_fw_err5	291
#define hkwd_ipintr_noqueue_post_fw_err6	292
#define hkwd_ipintr_noqueue_post_fw_err7	293
#define hkwd_ipintr_noqueue_post_fw_err8	294
#define hkwd_ipintr_noqueue_post_fw_err9	295
#define hkwd_ipintr_noqueue_post_fw_err10	296
#define hkwd_ipintr_noqueue_post_fw_err11	297
#define hkwd_ip_dooptions_err1			298	
#define hkwd_ip_dooptions_err2			299	
#define hkwd_ip_dooptions_err3			300	
#define hkwd_ip_dooptions_err4			301	
#define hkwd_ip_dooptions_err5			302	
#define hkwd_ip_dooptions_err6			303	
#define hkwd_ip_dooptions_err7			304	
#define hkwd_ip_dooptions_err8			305	
#define hkwd_ip_dooptions_err9			306	
#define hkwd_ip_dooptions_err10			307	
#define hkwd_ip_dooptions_err11			308	
#define hkwd_ip_dooptions_err12			309	
#define hkwd_ip_dooptions_err13			310


#define HKWD_IP6			0x53800000
#define hkwd_dopt6_input_in			1
#define hkwd_dopt6_input_out			2
#define hkwd_end6_input_in			3
#define hkwd_frg6_drain				4
#define hkwd_frg6_freef_in			5
#define hkwd_frg6_input_in			6
#define hkwd_frg6_input_out			7
#define hkwd_frg6_slowtimo_in			8
#define hkwd_hd6_inoptions_in			9
#define hkwd_hd6_inoptions_out			10
#define hkwd_hd6_outoptions			11
#define hkwd_hop6_input_in			12
#define hkwd_hop6_input_out			13
#define hkwd_icmp6_error_in			14
#define hkwd_icmp6_error_out1			15
#define hkwd_icmp6_error_out2			16
#define hkwd_icmp6_errparam_in			17
#define hkwd_icmp6_fasttimo_in			18
#define hkwd_icmp6_init_in			19
#define hkwd_icmp6_input_in			20
#define hkwd_icmp6_input_out			21
#define hkwd_icmp6_joingroup			22
#define hkwd_icmp6_leavegroup			23
#define hkwd_icmp6_reflect_in			24
#define hkwd_icmp6_reflect_out			25
#define hkwd_icmp6_send_in			26
#define hkwd_icmp6_send_out			27
#define hkwd_icmp6_sendmld_in			28
#define hkwd_icmp6_sendmld_out1			29
#define hkwd_icmp6_sendmld_out2			30
#define hkwd_icmp6_sendmld_out3			31
#define hkwd_icmp6_sendmld_out4			32
#define hkwd_ip6_copyoptions_in			33
#define hkwd_ip6_copyoptions_out		34
#define hkwd_ip6_ctloutput_in			35
#define hkwd_ip6_ctloutput_out			36
#define hkwd_ip6_deloption			37
#define hkwd_ip6_dropoption_in			38
#define hkwd_ip6_forward_in			39
#define hkwd_ip6_forward_out			40
#define hkwd_ip6_freemoptions_in		41
#define hkwd_ip6_getmoptions_in			42
#define hkwd_ip6_getmoptions_out		43
#define hkwd_ip6_getoptions_in			44
#define hkwd_ip6_getoptions_out			45
#define hkwd_ip6_init_in			46
#define hkwd_ip6_init_out			47
#define hkwd_ip6_input_in			48
#define hkwd_ip6_input_out			49
#define hkwd_ip6_insertoption_in		50
#define hkwd_ip6_insertoption_out		51
#define hkwd_ip6_mforward_in			52
#define hkwd_ip6_mforward_out			53
#define hkwd_ip6_mloopback_in			54
#define hkwd_ip6_mloopback_out			55
#define hkwd_ip6_output_in			56
#define hkwd_ip6_output_out			57
#define hkwd_ip6_reass_in			58
#define hkwd_ip6_reass_out			59
#define hkwd_ip6_saveoption_in			60
#define hkwd_ip6_saveoption_out			61
#define hkwd_ip6_setcontrol_in			62
#define hkwd_ip6_setcontrol_out			63
#define hkwd_ip6_setmoptions_in			64
#define hkwd_ip6_setmoptions_out		65
#define hkwd_ip6_setoptions_in			66
#define hkwd_ip6_setoptions_out			67
#define hkwd_ip6rttimeout_in			68
#define hkwd_ip6rttimeout_out			69
#define hkwd_ip6rttimer_in			70
#define hkwd_ip6rttimer_sched_in		71
#define hkwd_mfc_addqueue_in			72
#define hkwd_mfc_addqueue_out			73
#define hkwd_mfc_requeue_in			74
#define hkwd_mfc_requeue_out			75
#define hkwd_mfctimer_in			76
#define hkwd_mfctimer_out			77
#define hkwd_mroute6_init			78
#define hkwd_multicast_send_in			79
#define hkwd_multicast_send_out			80
#define hkwd_opt6_ctlinput_in			81
#define hkwd_opt6_ctlinput_out			82
#define hkwd_opt6_ferr_input			83
#define hkwd_opt6_haddr_input			84
#define hkwd_opt6_haddr_output			85
#define hkwd_opt6_init_in			86
#define hkwd_opt6_oerr_input			87
#define hkwd_opt6_reverse_in			88
#define hkwd_opt6_rtalert_input			89
#define hkwd_real_ip6_output_in			90	/* Unused */
#define hkwd_real_ip6_output_out		91	/* Unused */
#define hkwd_rt6_input_in			92
#define hkwd_rt6_input_out			93
#define hkwd_rt6_reverse_in			94
#define hkwd_rt6_reverse_out			95
#define hkwd_ip6_output_cachedroute        	96
#define hkwd_ip6_output_cachedroute_free   	97
#define hkwd_ip6_output_routetoif          	98
#define hkwd_ip6_output_netunreach         	99
#define hkwd_ip6_output_hostunreach        	100
#define hkwd_ip6_output_route_gwroute      	101
#define hkwd_ip6_output_mcast              	102
#define hkwd_ip6_output_mcast_noxface      	103
#define hkwd_ip6_output_mcast_hoplimit     	104
#define hkwd_ip6_output_sendit             	105
#define hkwd_ip6_output_nofrag_sent        	106
#define hkwd_ip6_output_frag_sent          	107
#define hkwd_ip6_output_bad                 	108
#define hkwd_llink_resolve_in                   109
#define hkwd_llink_resolve_out                  110
#define hkwd_ndp6_rtrequest_in                  111
#define hkwd_ndp6_rtrequest_out                 112
#define hkwd_ndp6_resolve_in                    113
#define hkwd_ndp6_resolve_out                   114
#define hkwd_ndsol6_output_in                   115
#define hkwd_ndsol6_output_out                  116
#define hkwd_ndadv6_output_in                   117
#define hkwd_ndadv6_output_out                  118
#define hkwd_redirect6_output_in                119
#define hkwd_redirect6_output_out               120
#define hkwd_ndsol6_input_in                    121
#define hkwd_ndsol6_input_out                   122
#define hkwd_ndadv6_input_in                    123
#define hkwd_ndadv6_input_out                   124
#define hkwd_rtsol6_input_in                    125
#define hkwd_rtsol6_input_out                   126
#define hkwd_rtadv6_input_in                    127
#define hkwd_rtadv6_input_out                   128
#define hkwd_redirect6_input_in                 129
#define hkwd_redirect6_input_out                130
#define hkwd_ip6_reachhint_in                   131
#define hkwd_ip6_reachhint_out                  132
#define hkwd_ndplookup_in                       133
#define hkwd_ndplookup_out                      134
#define hkwd_ndp6_ifinit_in                     135
#define hkwd_ndp6_ifinit_out                    136
#define hkwd_ndp6_rtlost_in                     137
#define hkwd_ndp6_rtlost_out                    138
#define hkwd_rip6_input_in                      139
#define hkwd_rip6_input_out                     140
#define hkwd_raw6_saverecv_in                   141
#define hkwd_raw6_saverecv_out                  142
#define hkwd_rip6_output_in                     143
#define hkwd_rip6_output_out                    144
#define hkwd_rip6_ctloutput_in                  145
#define hkwd_rip6_ctloutput_out                 146
#define hkwd_rip6_usrreq_in                     147
#define hkwd_rip6_usrreq_out                    148
#define hkwd_rip6_ctlinput_in                   149
#define hkwd_rip6_ctlinput_out1                 150
#define hkwd_rip6_ctlinput_out2                 151
#define hkwd_rip6_ctlinput_out3                 152
#define hkwd_rip6_ctlinput_out4                 153
#define hkwd_ip6_getctrlinfo_in			154
#define hkwd_ip6_getctrlinfo_out		155
#define hkwd_source_address_select_in		156
#define hkwd_source_address_select_out		157
#define hkwd_rip6_output_ancillary_in		158
#define hkwd_rip6_output_ancillary_out		159
#define hkwd_llink_resolve_nolock_in		160
#define hkwd_llink_resolve_nolock_out		161
#define hkwd_ip6_rtexpire_timeout_setup_in	162
#define hkwd_ip6_rtexpire_timeout_setup_out 	163
#define hkwd_ip6_rtexpire_netisr_in		164
#define hkwd_ip6_rtexpire_netisr_out		165
#define hkwd_ip6_ndsol_netisr_in                166
#define hkwd_ip6_ndsol_netisr_out1              167
#define hkwd_ip6_ndsol_netisr_out2              168
#define hkwd_in6_recvpathmtu_in                 169
#define hkwd_in6_recvpathmtu_bad                170
#define hkwd_in6_recvpathmtu_out                171
#define hkwd_in6_pcbnotifymtu_in                172
#define hkwd_in6_pcbnotifymtu_out               173
#define hkwd_ip6_setexthdroption_in             174
#define hkwd_ip6_setexthdroption_out            175
#define hkwd_ip6_getexthdroption_in             176
#define hkwd_ip6_getexthdroption_out            177
#define hkwd_raw6_saveopt_in                    178
#define hkwd_raw6_saveopt_bad                   179
#define hkwd_raw6_saveopt_out                   180
#define hkwd_mh6_input_in			181
#define hkwd_mh6_input_out			182
#define hkwd_ip6_reroute_in			183
#define hkwd_ip6_reroute_out			184



#define HKWD_PCB			0x53900000
#define hkwd_add_gateway_in			1
#define hkwd_add_gateway_out			2
#define hkwd_clear_ping_flags_in		3
#define hkwd_clear_ping_flags_out		4
#define hkwd_config_inet_in			5
#define hkwd_config_inet_out			6
#define hkwd_del_gateway_in			7
#define hkwd_del_gateway_nolock_in		8
#define hkwd_del_gateway_nolock_out		9
#define hkwd_del_gateway_out			10
#define hkwd_dgd_init_in			11
#define hkwd_dgd_init_out			12
#define hkwd_dgd_input6_in			13
#define hkwd_dgd_input6_out			14
#define hkwd_dgd_input_in			15
#define hkwd_dgd_input_out			16
#define hkwd_dgdretry_in			17
#define hkwd_dgdretry_out			18
#define hkwd_dgdretrysched_in			19
#define hkwd_dgdretrysched_out			20
#define hkwd_dgdsched_in			21
#define hkwd_dgdsched_out			22
#define hkwd_in6_addmulti_in			23
#define hkwd_in6_addmulti_out			24
#define hkwd_in6_control_in			25
#define hkwd_in6_control_out			26
#define hkwd_in6_delete_addrs_in		27
#define hkwd_in6_delete_addrs_out		28
#define hkwd_in6_delmulti_in			29
#define hkwd_in6_delmulti_out			30
#define hkwd_in6_ifattach_in			31
#define hkwd_in6_ifattach_out			32
#define hkwd_in6_ifinit_in			33
#define hkwd_in6_ifinit_out			34
#define hkwd_in6_ifscrub_in			35
#define hkwd_in6_ifscrub_out			36
#define hkwd_in6_pcbbind_dyn_in			37
#define hkwd_in6_pcbbind_dyn_out		38
#define hkwd_in6_pcbbind_in			39
#define hkwd_in6_pcbbind_out			43
#define hkwd_in6_pcbconnect_in			44
#define hkwd_in6_pcbconnect_out			47
#define hkwd_in6_pcblookup_in			48
#define hkwd_in6_pcblookup_out			51
#define hkwd_in6_pcbmatch_in			52
#define hkwd_in6_pcbmatch_out			53
#define hkwd_in6_pcbnotify_in			54
#define hkwd_in6_pcbnotify_out			55
#define hkwd_in6_pcbrebind_in			56
#define hkwd_in6_pcbrebind_out			57
#define hkwd_in6_rtalloc_in			58
#define hkwd_in6_rtalloc_out			59
#define hkwd_in6_rthost_in			60
#define hkwd_in6_rthost_out			61
#define hkwd_in6_setifa_in			62
#define hkwd_in6_setifa_out			63
#define hkwd_in_addmulti_in			64
#define hkwd_in_addmulti_out			65
#define hkwd_in_allpcbs_in			66
#define hkwd_in_allpcbs_out			67
#define hkwd_in_arpintr_in			68
#define hkwd_in_arpintr_out			69
#define hkwd_in_arpresolve_in			70
#define hkwd_in_control_in			71
#define hkwd_in_control_out			72
#define hkwd_in_delete_addrs_in			73
#define hkwd_in_delete_addrs_out		74
#define hkwd_in_delmulti_in			75
#define hkwd_in_delmulti_out			76
#define hkwd_in_hash_add_in			77
#define hkwd_in_hash_add_out			78
#define hkwd_in_hash_remove_in			79
#define hkwd_in_ifattach_in			80
#define hkwd_in_ifattach_out			81
#define hkwd_in_ifdetach_in			82
#define hkwd_in_ifdetach_out			83
#define hkwd_in_ifinit_in			84
#define hkwd_in_ifinit_out			85
#define hkwd_in_ifscrub_in			86
#define hkwd_in_losing_in			87
#define hkwd_in_losing_lock_in			88
#define hkwd_in_losing_lock_out			89
#define hkwd_in_losing_out			90
#define hkwd_in_pcb_hash_del_in			91
#define hkwd_in_pcb_hash_del_out		92
#define hkwd_in_pcb_hash_ins_in			93
#define hkwd_in_pcb_hash_ins_out		94
#define hkwd_in_pcb_tcp_hash_del_in		95
#define hkwd_in_pcb_tcp_hash_del_out		96
#define hkwd_in_pcb_tcp_lport_hash_ins_in	97
#define hkwd_in_pcb_tcp_lport_hash_ins_out	98
#define hkwd_in_pcballoc_in			99
#define hkwd_in_pcballoc_out			100
#define hkwd_in_pcbbind_in			101
#define hkwd_in_pcbbind_out			104
#define hkwd_in_pcbconnect_in			105
#define hkwd_in_pcbconnect_out			108
#define hkwd_in_pcbdetach_in			109
#define hkwd_in_pcbdetach_out			112
#define hkwd_in_pcbdisconnect_in		113
#define hkwd_in_pcbdisconnect_out		116
#define hkwd_in_pcbhashlookup2_in		121
#define hkwd_in_pcbhashlookup2_out		122
#define hkwd_in_pcbhashlookup_in		123
#define hkwd_in_pcbinit_in			124
#define hkwd_in_pcbinit_out			125
#define hkwd_in_pcblookup_in			126
#define hkwd_in_pcblookup_out			129
#define hkwd_in_pcbmatch_in			130
#define hkwd_in_pcbmatch_out			131
#define hkwd_in_pcbmovetotimewait_in		132
#define hkwd_in_pcbmovetotimewait_out		133
#define hkwd_in_pcbnotify_in			134
#define hkwd_in_pcbnotify_out			135
#define hkwd_in_pcbnotifyall_in			136
#define hkwd_in_pcbnotifyall_out		137
#define hkwd_in_rawpcbs_in			138
#define hkwd_in_rawpcbs_out			139
#define hkwd_in_rtchange_in			140
#define hkwd_in_rtchange_out			141
#define hkwd_in_rtinvalidate_in			142
#define hkwd_in_rtinvalidate_out		143
#define hkwd_in_setpeeraddr			144
#define hkwd_in_setsockaddr_in			145
#define hkwd_init_common_mtus_in		146
#define hkwd_mark_gateway_down_in		147
#define hkwd_mark_gateway_down_out		148
#define hkwd_ping_gateways_in			149
#define hkwd_ping_gateways_out			150
#define hkwd_ping_one_gateway_in		151
#define hkwd_ping_one_gateway_out		152
#define hkwd_set_ping_flag_in			153
#define hkwd_set_ping_flag_out			154
#define hkwd_tcp_bad_port_limit_init_in		155
#define hkwd_tcp_sendspace_change		156
#define hkwd_udp_bad_port_limit_init_in		157
#define hkwd_udp_sendspace_change		158
#define hkwd_in_pcbbind_sin			159
#define hkwd_in6_pcbbind_dyn_sin6		160
#define hkwd_in6_pcbbind_dyn_addr6		161
#define hkwd_in_pcb_pseudoconnect_in		162
#define hkwd_in_pcb_pseudoconnect_out		163
#define hkwd_in_pcb_pseudobind_in		164
#define hkwd_in_pcb_pseudobind_out		165
#define hkwd_in_pcb_pseudobind_sin		166
#define hkwd_in6_pcb_pseudoconnect_in		167
#define hkwd_in6_pcb_pseudoconnect_out		168
#define hkwd_in6_pcb_pseudobind_in		169
#define hkwd_in6_pcb_pseudobind_out		170
#define hkwd_in6_pcb_pseudobind_sin6		171
#define hkwd_in6_pcb_pseudobind_addr6		172
#define hkwd_in6_pcb_pseudorebind_in		173
#define hkwd_in6_pcb_pseudorebind_out		174
#define hkwd_in6_pcbnotifyall_in		176
#define hkwd_in6_pcbnotifyall_out               177
#define hkwd_in6_pcbnotifyall_err_out           178
#define hkwd_in6_setmss_in                      179
#define hkwd_in6_setmss_out                     180
#define hkwd_in6_pmtuclone_in                   181
#define hkwd_in6_pmtuclone_out                  182
#define hkwd_in_pcblocalipnotify_in             183
#define hkwd_in_pcblocalipnotify_out            184
#define hkwd_inet_dr_cpu_add_in			185
#define hkwd_inet_dr_cpu_add_out		186
#define hkwd_inet_dr_cpu_add_err1		187
#define hkwd_in_arpresolve_out1			188
#define hkwd_in_arpresolve_out2			189
#define hkwd_config_inet_err1			190
#define hkwd_in_pcbdetach_soputonfreelist      	191 
#define hkwd_pmignet_hd_in32			192
#define hkwd_pmignet_hd_in64			193
#define hkwd_pmignet_hd_out32			194
#define hkwd_pmignet_hd_out64			195
#define hkwd_pmignet_tx_in			196
#define hkwd_pmignet_tx_sa_family		197
#define hkwd_pmignet_tx_out			198
#define hkwd_pmignet_hd_enomen			199
#define hkwd_pmignet_register_ext		200


#define HKWD_MBUF		0x25400000
#define hkwd_m_get_in				1
#define hkwd_m_get_out				2
#define hkwd_m_getclr_in			3
#define hkwd_m_getclr_out			4
#define hkwd_m_free_in				5
#define hkwd_m_free_out				6
#define hkwd_m_copy_in				7
#define hkwd_m_copy_out				8
#define hkwd_m_copydata_in			9
#define hkwd_m_copydata_out			10
#define hkwd_m_pullup_1				11
#define hkwd_m_pullup_2				12
#define hkwd_mlowintr_in			13
#define hkwd_mlowintr_out			14
#define hkwd_m_low_test				15
#define hkwd_m_clgetm_in			16
#define hkwd_m_clgetm_out			17
#define hkwd_m_getclustm_in			18
#define hkwd_m_getclustm_out			19
#define hkwd_m_clattach_in			20
#define hkwd_m_clattach_out			21
#define hkwd_m_prepend_get_in			22
#define hkwd_m_prepend_get_out			23
#define hkwd_m_pullup_get_in			24
#define hkwd_m_pullup_get_out			25
#define hkwd_m_copy_get_in			26
#define hkwd_m_copy_get_out			27
#define hkwd_m_adj_in           		28
#define hkwd_m_pullup_in        		29
#define hkwd_m_retry_err1       		30
#define hkwd_m_pullup_err1      		31
#define hkwd_m_clattach_err1    		32
#define hkwd_m_getclustm_err1   		33
#define hkwd_m_getclustm_err2   		34
#define hkwd_m_collapse_err1    		35
#define hkwd_m_copymext_err1    		36
#define hkwd_m_copymext_err2    		37
#define hkwd_m_create_clustpool_err1            38
#define hkwd_m_create_clustpool_err2            39
#define hkwd_m_get_from_clustpool_nolock_err1   40
#define hkwd_mpool_grow_err1                    41
#define hkwd_mpool_grow_err2                    42
#define hkwd_mpool_clattach_err1                43
#define hkwd_mpool_clattach_err2                44
#define hkwd_mpool_clattach_err3                45
#define hkwd_m_copymext_in			46
#define hkwd_m_copymext_out			47
#define hkwd_m_create_clustpool_in		48
#define hkwd_m_create_clustpool_out		49
#define hkwd_mpool_grow_in			50	
#define hkwd_mpool_grow_out			51
#define hkwd_mpool_shrink_in			52
#define hkwd_mpool_shrink_out			53
#define hkwd_m_free_clustpool_in		54
#define hkwd_m_free_clustpool_out		55


/* These hook id's and sub hook id's are for Network Interface's */
#define HKWD_IFEN		0x25500000
#define HKWD_IFTR		0x25600000
#define HKWD_IFET		0x25700000
#define HKWD_IFXT		0x25800000
#define HKWD_IFSL		0x25900000
#define hkwd_statintr_in	1
#define hkwd_statintr_out	2	
#define hkwd_netintr_in		3
#define hkwd_netintr_out	4	
#define hkwd_attach_in		5
#define hkwd_attach_out		6
#define hkwd_detach_in		7
#define hkwd_detach_out		8
#define hkwd_init_in		9
#define hkwd_init_out		10
#define hkwd_ioctl_in		11
#define hkwd_ioctl_out		12
#define hkwd_output_in		13
#define hkwd_output_out		14
#define hkwd_reset_in		15
#define hkwd_reset_out		16
#define hkwd_rcv_in		17
#define hkwd_rcv_out		18
#define hkwd_incall_in		19
#define hkwd_incall_out		20	
#define hkwd_callcomp_in	21	
#define hkwd_callcomp_out	22
#define hkwd_clrind_in		23
#define hkwd_clrind_out		24
#define hkwd_slhiwat		25
#define hkwd_expand_table_or_add_row_out1       26
#define hkwd_expand_table_or_add_row_out2       27
#define hkwd_expand_table_or_add_row_out3       28
#define hkwd_config_en_in                       29
#define hkwd_config_en_out1                     30
#define hkwd_config_en_out2                     31
#define hkwd_config_en_out3                     32
#define hkwd_config_en_out4                     33
#define hkwd_config_en_out5                     34
#define hkwd_config_en_out6                     35
#define hkwd_config_en_out7                     36
#define hkwd_config_en_out8                     37
#define hkwd_config_en_out9                     38
#define hkwd_en_attach_in                       39
#define hkwd_en_ioctl_in                        40
#define hkwd_en_ioctl_out1                      41
#define hkwd_en_ioctl_err1                      42
#define hkwd_en_ioctl_err2                      43
#define hkwd_en_ioctl_err3                      44
#define hkwd_en_ioctl_err4                      45
#define hkwd_en_ioctl_err5                      46
#define hkwd_en_ioctl_err6                      47
#define hkwd_en_ioctl_err7                      48
#define hkwd_en_ioctl_debug1                    49
#define hkwd_en_ioctl_debug2                    50
#define hkwd_en_ioctl_debug3                    51
#define hkwd_en_ioctl_debug4                    52
#define hkwd_en_ioctl_out                       53
#define hkwd_en_output_in                       54
#define hkwd_en_output_out1                     55
#define hkwd_en_output_out2                     56
#define hkwd_en_output_out3                     57
#define hkwd_en_output_out4                     58
#define hkwd_en_output_out5                     59
#define hkwd_en_output_out6                     60
#define hkwd_en_output_out7                     61
#define hkwd_en_output_out8                     62
#define hkwd_en_output_out9                     63
#define hkwd_en_output_out10                    64
#define hkwd_en_output_out11                    65
#define hkwd_en_output_out12                    66
#define hkwd_en_output_out13                    67
#define hkwd_en_output_out14                    68
#define hkwd_en_output_out15                    69
#define hkwd_en_output_out16                    70
#define hkwd_en_output_out17                    71
#define hkwd_en_output_out18                    72
#define hkwd_en_output_out19                    73
#define hkwd_arpresolve_out1                    74
#define hkwd_arpresolve_out2                    75
#define hkwd_arpresolve_out3                    76
#define hkwd_arpresolve_out4                    77
#define hkwd_arpresolve_out5                    78
#define hkwd_arpresolve_out6                    79
#define hkwd_arpresolve_out7                    80
#define hkwd_arpresolve_out                     81
#define hkwd_arpinput_in                        82
#define hkwd_arpinput_out1                      83
#define hkwd_arpinput_out2                      84
#define hkwd_arpinput_out3                      85
#define hkwd_arpinput_out4                      86
#define hkwd_arpinput_out5                      87
#define hkwd_arpinput_out                       88
#define hkwd_in_arpinput_in                     89
#define hkwd_in_arpinput_out1                   90
#define hkwd_in_arpinput_out2                   91
#define hkwd_in_arpinput_out3                   92
#define hkwd_in_arpinput_out4                   93
#define hkwd_in_arpinput_out5                   94
#define hkwd_in_arpinput_out6                   95
#define hkwd_in_arpinput_out                    96

/* This hook id is for TCP debug */
#define HKWD_TCPDBG		0x25a00000

#define HKWD_NET_MALLOC		0x34000000

#define hkwd_net_malloc		1
#define hkwd_net_free		2

/* This hook id is for ATM Socket Extensions */

#define HKWD_ATMSOCK		0x3A500000

/* These are TCPIP/FDDI related */
#define HKWD_IFCA		0x26000000
#define HKWD_IFSO		0x26100000
#define HKWD_IFFD		0x26200000
#define HKWD_DD_FDDIDD		0x26300000

#define HKWD_RDS 		0x5EC00000  /* Reliable Datagram Sockets */
#define HKWD_RDS_ERROR		0x5F500000  /* Reliable Datagram Sockets */

#define HKWD_GRE_GENERAL	0x5F400000  /* Generic Routing Encapsulation */


/*
 * Data Link Control
 */
#define HKWD_SYSX_DLC_START       0x24000000 /* start link station    */
#define HKWD_SYSX_DLC_HALT        0x24100000 /* halt  link station    */
#define HKWD_SYSX_DLC_TIMER       0x24200000 /* timer                 */
#define HKWD_SYSX_DLC_XMIT        0x24300000 /* transmit packet       */
#define HKWD_SYSX_DLC_RECV        0x24400000 /* receive  packet       */
#define HKWD_SYSX_DLC_PERF        0x24500000 /* performance           */
#define HKWD_SYSX_DLC_MONITOR     0x24600000 /* monitor               */

#define HKWD_ODM_LIB              0x30000000 /* ODM code              */

/* hooks for STTY */
#define HKWD_STTY 		  0x40000000 
#define HKWD_STTY_STRTTY	  0x40100000 /* stream head tty */
#define HKWD_STTY_LDTERM 	  0x40200000 /* line discipline module */
#define HKWD_STTY_SPTR 		  0x40300000 /* serial printer discipline module */
#define HKWD_STTY_NLS 		  0x40400000 /* NLS mapping discipline module */
#define HKWD_STTY_PTY 		  0x40500000 /* pseudo tty driver */
#define HKWD_STTY_RS 		  0x40600000 /* RS driver */
#define HKWD_STTY_LION 		  0x40700000 /* LION driver */
#define HKWD_STTY_CXMA 		  0x40800000 /*  */
#define HKWD_STTY_ISA		  0x40900000 /* PCI/ISA native ports */
#define HKWD_STTY_JAS		  0x40a00000 /* Jasmine 2-port driver */

/* hooks till 0x40f00000 are reserved to stty for further use */

#define HKWD_VIRT_CONS            0x41700000 /* virtual console driver */

/* subhooks  for stty */
#define hkwd_TTY_CONFIG      0x01
#define hkwd_TTY_OPEN        0x02
#define hkwd_TTY_CLOSE       0x03
#define hkwd_TTY_WPUT        0x04
#define hkwd_TTY_RPUT        0x05
#define hkwd_TTY_WSRV        0x06
#define hkwd_TTY_RSRV        0x07
#define hkwd_TTY_REVOKE      0x08    /* for streamhead tty                   */
#define hkwd_TTY_IOCTL       0x09    /* for ioctls                           */
#define hkwd_TTY_PROC        0x0a    /* for drivers                          */
#define hkwd_TTY_SERVICE     0x0b    /* for drivers                          */
#define hkwd_TTY_SLIH        0x0c    /* for drivers                          */
#define hkwd_TTY_OFFL        0x0d    /* for drivers                          */
#define hkwd_TTY_LAST        0x0e    /* can be used for any specific entry   */

#define HKWD_CPU_PREEMPT 0x41900000	/* PHYP CPU preemption hook. */
/* Macros for the subhook */
#define _PRMT_REALLOC_M 0x8000		/* memory re-allocated */
#define _PRMT_WRAP_M 0x4000		/* preemption buffer wrapped */
#define _PRMT_CPUID_M 0xfff		/* cpu id */

/***********************************************************************/
/*************** DISPLAY SUBSYSTEM TRACE HOOK DEFINITIONS ************-*/
/***********************************************************************/
/*
 *  DISPLAY SUBSYSTEM MAJOR TRACE HOOKS
 *
 *  The display subsystem is divided into functional components.
 *  Each functional component is given two trace hooks.  The first
 *  trace hook is designated HKWD_xxx_P and is for performance trace.
 *  The second hook is designated HKWD_xxx_D and is for debug trace.
 *  The components of the display subsystem, for tracing purposes,
 *  are: Virtual Terminal Subsystem (VTSS); Rendering Context
 *  Manager (RCM); Device Dependent Functions of VTSS and RCM (DDF);
 *  Graphics Adapter Interface (GAI), which is divided into its
 *  subcomponents, 2D (GAI2DM1), Resource Management (GAIRMS),
 *  3D Model 1 (GAI3DM1), and 3D Model 2 (GAI3DM2); Enhanced X-Windows
 *  (X11); IBM's extensions to X (X11EXT); the SGI-like GL API (GL);
 *  and IBM graPHIGS (GRAPHIGS).
 *
 *  The trace hooks for display occupy the range 500 to 51F.  Further,
 *  the range 520-52F has been set aside in case the display subsystem
 *  requires additional growth.
 *
 *
 */

#define  HKWD_DISPLAY_VTSS_P           0x50000000  /*  display group  */
#define  HKWD_DISPLAY_VTSS_D           0x50100000
#define  HKWD_DISPLAY_RCM_P            0x50200000
#define  HKWD_DISPLAY_RCM_D            0x50300000
#define  HKWD_DISPLAY_DDF_P            0x50400000
#define  HKWD_DISPLAY_DDF_D            0x50500000
#define  HKWD_DISPLAY_GAIRMS_P         0x50600000
#define  HKWD_DISPLAY_GAIRMS_D         0x50700000
#define  HKWD_DISPLAY_GAI2DM1_P        0x50800000
#define  HKWD_DISPLAY_GAI2DM1_D        0x50900000
#define  HKWD_DISPLAY_GAI3DM1_P        0x50a00000
#define  HKWD_DISPLAY_GAI3DM1_D        0x50b00000
#define  HKWD_DISPLAY_GAI3DM2_P        0x50c00000
#define  HKWD_DISPLAY_GAI3DM2_D        0x50d00000
#define  HKWD_DISPLAY_X11_P            0x50e00000
#define  HKWD_DISPLAY_X11_D            0x50f00000
#define  HKWD_DISPLAY_X11EXT_P         0x51000000
#define  HKWD_DISPLAY_X11EXT_D         0x51100000
#define  HKWD_DISPLAY_GL_P             0x51200000
#define  HKWD_DISPLAY_GL_D             0x51300000
#define  HKWD_DISPLAY_GRAPHIGS_P       0x51400000
#define  HKWD_DISPLAY_GRAPHIGS_D       0x51500000
#define  HKWD_ACPA_P                   0x51600000
#define  HKWD_ACPA_D                   0x51700000
#define  HKWD_DISPLAY_RESERVED_518     0x51800000
#define  HKWD_DISPLAY_RESERVED_519     0x51900000
#define  HKWD_DISPLAY_RESERVED_51A     0x51a00000
#define  HKWD_DISPLAY_RESERVED_51B     0x51b00000
#define  HKWD_DISPLAY_RESERVED_51C     0x51c00000
#define  HKWD_DISPLAY_RESERVED_51D     0x51d00000
#define  HKWD_DISPLAY_RESERVED_51E     0x51e00000
#define  HKWD_DISPLAY_RESERVED_51F     0x51f00000

/*----------------------------------------------------------------
 *  DISPLAY SUBSYSTEM MINOR TRACE HOOKS
 *
 *  Each hookword occupies 32 bits.  The most significant 12 bits are
 *  the major hook ID.  The next four bits are reserved.  The least
 *  significant 16 bits are for component use.  The Display Subsystem
 *  uses the 16 bits to encode certain flags and to encode a minor
 *  hook ID.
 *
 *  The general format for the 16 bits of the minor hook ID is:
 *
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *  |           routine ID              | func ID|ex|
 *  +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
 *
 *
 *  The first twelve bits are a routine ID, giving a maximum of
 *  4096 routines per component.  The next three bits are the
 *  function ID within the component.  Function 000 is always
 *  reserved for the main entry/exit to the routine.  Functions
 *  001 to 110 are for internal functions within the routine.
 *  In this sense, function can be used to encode data as well.
 *  Function 111 is a special code that permits the first word
 *  of trace data to hold an expanded internal function code.
 *
 *  Bit 15, "ex", is set to 0 upon entry to the routine/function.
 *  The bit is set to 1 upon exit of the function.  This permits
 *  entry/exit tracing without reuse of the routine ID.
 *
 */

/*------------------------------------------------------------------
 *  VTSS MINOR TRACE HOOK DEFINITION
 *
 *  The VTSS component is has several major functional pieces, including
 *  the HFT (an AIX character device driver), the Screen Manager, the
 *  Mode Processor, the Virtual Display Driver, the Keyboard Device
 *  Driver, and other input device drivers.
 *
 *-----------------------------------------------------------------*/

#define  hkwd_DISPLAY_VTSS_HFT_OPEN          ( 0x001 << 4 )
#define  hkwd_DISPLAY_VTSS_HFT_CLOSE         ( 0x002 << 4 )
#define  hkwd_DISPLAY_VTSS_HFT_IOCTL         ( 0x003 << 4 )
#define  hkwd_DISPLAY_VTSS_HFT_CONFIG        ( 0x004 << 4 )
#define  hkwd_DISPLAY_VTSS_HFT_MULTIPLEX     ( 0x005 << 4 )
#define  hkwd_DISPLAY_VTSS_HFT_SELECT        ( 0x006 << 4 )
#define  hkwd_DISPLAY_VTSS_HFT_READ          ( 0x007 << 4 )
#define  hkwd_DISPLAY_VTSS_HFT_WRITE         ( 0x008 << 4 )
#define  hkwd_DISPLAY_VTSS_HFT_REVOKE        ( 0x009 << 4 )
#define  hkwd_DISPLAY_VTSS_HFT_INPUT         ( 0x00a << 4 )
#define  hkwd_DISPLAY_VTSS_HFT_OUTPUT        ( 0x00b << 4 )

#define  hkwd_DISPLAY_VTSS_VDD_ACT           ( 0x101 << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_CFL           ( 0x102 << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_CLR           ( 0x103 << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_CPL           ( 0x104 << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_DACT          ( 0x105 << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_DEFC          ( 0x106 << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_TERM          ( 0x107 << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_INIT          ( 0x108 << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_MOVC          ( 0x109 << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_RDS           ( 0x10a << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_TEXT          ( 0x10b << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_SCR           ( 0x10c << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_SETM          ( 0x10d << 4 )
#define  hkwd_DISPLAY_VTSS_VDD_STCT          ( 0x10e << 4 )

/*------------------------------------------------------------------
 *  GAI 2D Model 1 (GAI2DM1) MINOR TRACE HOOK DEFINITION
 *
 *  The minor IDs listed below are performance trace hooks
 *  for GAI 2D Model 1.
 *
 *  These functions are listed in the order specified in the             /
 *  2D Graphics Context Procedures structure.
 *
 *-----------------------------------------------------------------*/

#define  hkwd_DISPLAY_GAI2DM1_DESTROYGC             ( 1 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_ANALYZEGC             ( 2 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_COPYPIXTOWIN          ( 3 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_COPYWINTOPIX          ( 4 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_COPYWINTOWIN          ( 5 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_COPYPIXBPTOWIN        ( 6 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_COPYWINBPTOPIX        ( 7 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_COPYWINBPTOWIN        ( 8 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_POLYPOINT             ( 9 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_POLYLINES             ( 10 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_POLYSEGMENT           ( 11 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_POLYRECTANGLE         ( 12 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_POLYARC               ( 13 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_FILLPOLYGON           ( 14 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_POLYFILLRECT          ( 15 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_POLYFILLARC           ( 16 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_PUTIMAGE              ( 17 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_IMAGETEXT8            ( 18 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_POLYTEXT8             ( 19 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_IMAGETEXT16           ( 20 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_POLYTEXT16            ( 21 << 4 )
#define  hkwd_DISPLAY_GAI2DM1_PUSHPIXELS            ( 22 << 4 )

/*------------------------------------------------------------------
 *  M-ACPA/A MINOR TRACK HOOK DEFINITION
 *
 *  The minor IDs listed below are performance trace hooks
 *  for the Mulitmedia Audio Capture and Playback Adapter.
 *
 *-----------------------------------------------------------------*/

#define  hkwd_ACPA_CFGINIT                      ( 1 << 4 )
#define  hkwd_ACPA_CFGTERM                      ( 2 << 4 )
#define  hkwd_ACPA_OPEN                         ( 3 << 4 )
#define  hkwd_ACPA_CLOSE                        ( 4 << 4 )
#define  hkwd_ACPA_INTERRUPT                    ( 5 << 4 )
#define  hkwd_ACPA_READ                         ( 6 << 4 )
#define  hkwd_ACPA_WRITE                        ( 7 << 4 )
#define  hkwd_ACPA_IOCTL                        ( 8 << 4 )
#define  hkwd_ACPA_MPX                          ( 9 << 4 )
#define  hkwd_ACPA_SELECT                       ( 10 << 4 )
#define  hkwd_ACPA_INIT                         ( 11 << 4 )
#define  hkwd_ACPA_CHANGE                       ( 12 << 4 )
#define  hkwd_ACPA_START                        ( 13 << 4 )
#define  hkwd_ACPA_STOP                         ( 14 << 4 )
#define  hkwd_ACPA_PAUSE                        ( 15 << 4 )
#define  hkwd_ACPA_RESUME                       ( 16 << 4 )
#define  hkwd_ACPA_STATUS                       ( 17 << 4 )
#define  hkwd_ACPA_WAIT                         ( 18 << 4 )
#define  hkwd_ACPA_BUFFER                       ( 19 << 4 )
#define  hkwd_ACPA_LOAD                         ( 20 << 4 )
#define  hkwd_ACPA_DEVSTART                     ( 21 << 4 )
#define  hkwd_ACPA_DEVSTOP                      ( 22 << 4 )
#define  hkwd_ACPA_INITZ                        ( 23 << 4 )
#define  hkwd_ACPA_TIMEDOUT                     ( 24 << 4 )

/***********************************************************************/
/************ END OF DISPLAY SUBSYSTEM TRACE HOOK DEFINITIONS ********-*/
/***********************************************************************/

/* Netbios */

#define HKWD_NB_TRACE_NCB 		0x28300000
#define HKWD_NB_TRACE_IOB		0x28400000
#define HKWD_NB_TRACE_OPEN 	 	0x28500000
#define HKWD_NB_TRACE_COMM	 	0x28600000
#define HKWD_NB_TRACE_WRITE 		0x28700000
#define HKWD_NB_TRACE_READ 		0x28800000
#define HKWD_NB_TRACE_DATA	 	0x28900000
#define HKWD_NB_TRACE_MIF	 	0x28a00000
#define HKWD_NB_TRACE_VALUE		0x28b00000

/* Hook for detection of excessive interrupt disablement */
#define HKWD_KERN_DISABLEMENT	0x4AF00000

/* Hook for kernel profiling */
#define HKWD_KERN_PROF		0x23400000  /* capture iar at clock intr */
/* MSR bit tprof hooks modifier */
#define hkwd_PROF_HV	0x00008000
/* PR bit tprof hook modifier */
#define hkwd_PROF_PR	0x00004000

/* Hook for tprof events profiling */
#define HKWD_KERN_TPROF         0x2FF00000
/* Subhooks for HKWD_KERN_TPROF hook */
#define hkwd_tprof_cmd          1
#define hkwd_tprof_util         2
#define hkwd_tprof_hwevts       3
#define hkwd_tprof_swalign      4
#define hkwd_tprof_swemu        5
#define hkwd_tprof_swislbmiss   6
#define hkwd_tprof_swdslbmiss   7
#define hkwd_tprof_dataprof     8
#define hkwd_tprof_too_rapid    9
#define hkwd_tprof_usercmd      0xa
#define hkwd_tprof_lparmig      0xb

/* Hooks for COBOL */
#define HKWD_COB                        0x23500000
#define HKWD_COB_RTE                    0x23600000
#define HKWD_COB_APPL                   0x23700000

/* Hooks for PSLA */
#define HKWD_PSLA_OPEN                  0x27200000
#define HKWD_PSLA_CLOSE                 0x27300000
#define HKWD_PSLA_READ                  0x27400000
#define HKWD_PSLA_WRITE                 0x27500000
#define HKWD_PSLA_IOCTL                 0x27600000
#define HKWD_PSLA_INTR                  0x27700000
#define HKWD_PSLA_CONF			0x27800000

/* Hook for NCS */
#define HKWD_NCS_NCK                    0x27900000

/* Hooks for SNA */
#define HKWD_SNA_COMM                   0x27000000
#define HKWD_SNA_API                    0x27100000
#define HKWD_GSNA_API                   0x28100000
#define HKWD_SNALIB_API                 0x28200000

/* Hooks for SYSXMSLA */
#define HKWD_HIA			0x28000000

/* Hook for Netview */
#define HKWD_NETVIEW_6000               0x29000000

/* Hook for Hursley */
#define HKWD_HSTC_PRD                   0x29100000

/* Hook for SYSXVCA */
#define HKWD_VCA_DD			0x29200000

/* VCA sub hook ids */
#define hkwd_VCA_ENTRY_OPEN			0x1
#define hkwd_VCA_EXIT_OPEN			0x2
#define hkwd_VCA_ENTRY_CLOSE			0x3
#define hkwd_VCA_EXIT_CLOSE			0x4
#define hkwd_VCA_ENTRY_READ			0x5
#define hkwd_VCA_EXIT_READ			0x6
#define hkwd_VCA_ENTRY_WRITE			0x7
#define hkwd_VCA_EXIT_WRITE			0x8
#define hkwd_VCA_ENTRY_CONFIG			0x9
#define hkwd_VCA_EXIT_CONFIG			0xA
#define hkwd_VCA_ENTRY_IOCTL			0xB
#define hkwd_VCA_EXIT_IOCTL			0xC
#define hkwd_VCA_ENTRY_VCA_SETUP		0xD
#define hkwd_VCA_EXIT_VCA_SETUP			0xE
#define hkwd_VCA_ENTRY_VCA_MEMCOPY		0xF
#define hkwd_VCA_EXIT_VCA_MEMCOPY		0x10
#define hkwd_VCA_ENTRY_MEM_SETUP		0x11
#define hkwd_VCA_EXIT_MEM_SETUP			0x12
#define hkwd_VCA_ENTRY_MEM_UNSET		0x13
#define hkwd_VCA_EXIT_MEM_UNSET			0x14
#define hkwd_VCA_ENTRY_GETSTATUS		0x15
#define hkwd_VCA_EXIT_GETSTATUS			0x16
#define hkwd_VCA_ENTRY_SETMASK			0x17
#define hkwd_VCA_EXIT_SETMASK			0x18
#define hkwd_VCA_ENTRY_CAPTURE_WAIT		0x19
#define hkwd_VCA_EXIT_CAPTURE_WAIT		0x1A
#define hkwd_VCA_ENTRY_INTR_ENABLE		0x1B
#define hkwd_VCA_EXIT_INTR_ENABLE		0x1C
#define hkwd_VCA_ENTRY_INTR_DISABLE		0x1D
#define hkwd_VCA_EXIT_INTR_DISABLE		0x1E
#define hkwd_VCA_ENTRY_VCA_SET_MODE		0x1F
#define hkwd_VCA_EXIT_VCA_SET_MODE		0x20
#define hkwd_VCA_ENTRY_VCA_SET_CONTROLS		0x21
#define hkwd_VCA_EXIT_VCA_SET_CONTROLS		0x22
#define hkwd_VCA_ENTRY_VCA_SET_CURSOR		0x23
#define hkwd_VCA_EXIT_VCA_SET_CURSOR		0x24
#define hkwd_VCA_ENTRY_VCA_SET_WINDOW		0x25
#define hkwd_VCA_EXIT_VCA_SET_WINDOW		0x26
#define hkwd_VCA_ENTRY_VCA_SET_DACS		0x27
#define hkwd_VCA_EXIT_VCA_SET_DACS		0x28
#define hkwd_VCA_ENTRY_ALTDAC			0x29
#define hkwd_VCA_EXIT_ALTDAC			0x2A
#define hkwd_VCA_ENTRY_VCA_GET_MODE		0x2B
#define hkwd_VCA_EXIT_VCA_GET_MODE		0x2C
#define hkwd_VCA_ENTRY_VCA_GET_CONTROLS		0x2D
#define hkwd_VCA_EXIT_VCA_GET_CONTROLS		0x2E
#define hkwd_VCA_ENTRY_VCA_GET_CURSOR		0x2F
#define hkwd_VCA_EXIT_VCA_GET_CURSOR		0x30
#define hkwd_VCA_ENTRY_VCA_GET_WINDOW		0x31
#define hkwd_VCA_EXIT_VCA_GET_WINDOW		0x32
#define hkwd_VCA_ENTRY_VCA_GET_DACS		0x33
#define hkwd_VCA_EXIT_VCA_GET_DACS		0x34
#define hkwd_VCA_ENTRY_READDAC			0x35
#define hkwd_VCA_EXIT_READDAC			0x36
#define hkwd_VCA_ENTRY_VCA_SET_DAC_DEFAULTS	0x37
#define hkwd_VCA_EXIT_VCA_SET_DAC_DEFAULTS	0x38
#define hkwd_VCA_ENTRY_VCA_INTR			0x39
#define hkwd_VCA_EXIT_VCA_INTR			0x3A
#define hkwd_VCA_ENTRY_VCA_OUTB			0x3B
#define hkwd_VCA_EXIT_VCA_OUTB			0x3C
#define hkwd_VCA_ENTRY_VCA_INB			0x3D
#define hkwd_VCA_EXIT_VCA_INB			0x3E
#define hkwd_VCA_ENTRY_VCA_TIMED_OUT		0x3F
#define hkwd_VCA_EXIT_VCA_TIMED_OUT		0x40
#define hkwd_VCA_ENTRY_VCA_ALTREG		0x41
#define hkwd_VCA_EXIT_VCA_ALTREG		0x42
#define hkwd_VCA_ENTRY_VCA_READREG		0x43
#define hkwd_VCA_EXIT_VCA_READREG		0x44
#define hkwd_VCA_ENTRY_VCA_KSET_CURSOR		0x45
#define hkwd_VCA_EXIT_VCA_KSET_CURSOR		0x46
#define hkwd_VCA_ENTRY_VCA_KGET_CURSOR		0x47
#define hkwd_VCA_EXIT_VCA_KGET_CURSOR		0x48
#define hkwd_VCA_ENTRY_VCA_DELAY		0x49
#define hkwd_VCA_EXIT_VCA_DELAY			0x4A
#define hkwd_VCA_ENTRY_VCA_INITIALIZE		0x4B
#define hkwd_VCA_EXIT_VCA_INITIALIZE		0x4C
#define hkwd_VCA_ENTRY_VCAERR			0x4D
#define hkwd_VCA_EXIT_VCAERR			0x4E

/*
 * STREAMS (PSE) Hookwords
 */

#define	HKWD_PSE		0x7FF00000

/* system calls */
#define	hkwd_pse_getmsg_in	0x01
#define	hkwd_pse_getmsg_out	0x02
#define	hkwd_pse_getpmsg_in	0x03
#define	hkwd_pse_getpmsg_out	0x04
#define	hkwd_pse_putmsg_in	0x05
#define	hkwd_pse_putmsg_out	0x06
#define	hkwd_pse_putpmsg_in	0x07
#define	hkwd_pse_putpmsg_out	0x08

/* driver entry points */
#define	hkwd_pse_open_in	0x09
#define	hkwd_pse_open_out	0x0a
#define	hkwd_pse_clone_in	0x0b
#define	hkwd_pse_clone_out	0x0c
#define	hkwd_pse_close_in	0x0d
#define	hkwd_pse_close_out	0x0e
#define	hkwd_pse_read_in	0x0f
#define	hkwd_pse_read_out	0x10
#define	hkwd_pse_write_in	0x11
#define	hkwd_pse_write_out	0x12
#define	hkwd_pse_ioctl_in	0x13
#define	hkwd_pse_ioctl_out	0x14
#define	hkwd_pse_poll_in	0x15
#define	hkwd_pse_poll_out	0x16
#define hkwd_pse_revoke_in      0x17
#define hkwd_pse_revoke_out     0x18

/* pse : mblks sub_hooks */
#define hkwd_pse_allocb_in                 0x19
#define hkwd_pse_allocb_out_bad            0x1a
#define hkwd_pse_allocb_out_ok             0x1b
#define hkwd_pse_freeb_in                  0x1c
#define hkwd_pse_flushband_in              0x1d
#define hkwd_pse_flushq_in                 0x1e
#define hkwd_pse_freemsg_in                0x1f

#define hkwd_pse_getq_in                   0x20
#define hkwd_pse_getq_out                  0x21
#define hkwd_pse_insq_in                   0x22
#define hkwd_pse_insq_out                  0x23
#define hkwd_pse_putq_in                   0x24
#define hkwd_pse_putq_out                  0x25
#define hkwd_pse_putbq_in                  0x26
#define hkwd_pse_putbq_out                 0x27
#define hkwd_pse_putctl_comm_in            0x28
#define hkwd_pse_putctl_comm_out           0x29
#define hkwd_pse_str_putnext_in            0x2a
#define hkwd_pse_qreply_in                 0x2b
#define hkwd_pse_rmvq_in                   0x2c
#define hkwd_pse_putnext_in                0x2d
#define hkwd_pse_strqget_in                0x2e
#define hkwd_pse_strqget_out               0x2f

#define hkwd_pse_strqset_in                0x30
#define hkwd_pse_strqset_out               0x31
#define hkwd_pse_insqband_in               0x32
#define hkwd_pse_insqband_out              0x33
#define hkwd_pse_putbqband_in              0x34
#define hkwd_pse_putbqband_out             0x35
#define hkwd_pse_puthere_in                0x36
#define hkwd_pse_putqband_in               0x37
#define hkwd_pse_putqband_out              0x38
#define hkwd_pse_str_strtune_module_info   0x39
#define hkwd_pse_str_strtune_modsw         0x3a
#define hkwd_pse_str_strtune_queue         0x3b

/* pse : minimum trace level sub hooks */ 
#define hkwd_pse_add_device_1              0x3c
#define hkwd_pse_add_device_2              0x3d
#define hkwd_pse_add_device_3              0x3e
#define hkwd_pse_add_device_4              0x3f

#define hkwd_pse_bufcall_configure         0x40
#define hkwd_pse_clone_configure           0x41
#define hkwd_pse_close_wrapper             0x42
#define hkwd_pse_del_device_1              0x43
#define hkwd_pse_del_device_2              0x44
#define hkwd_pse_dmodsw_install_1          0x45
#define hkwd_pse_dmodsw_install_2          0x46
#define hkwd_pse_dmodsw_install_3          0x47
#define hkwd_pse_dmodsw_remove             0x48
#define hkwd_pse_dmodsw_search             0x49
#define hkwd_pse_do_ioctl_job_control_1    0x4a
#define hkwd_pse_do_ioctl_job_control_2    0x4b
#define hkwd_pse_do_ioctl_job_control_3    0x4c
#define hkwd_pse_do_read_job_control_1     0x4d
#define hkwd_pse_do_read_job_control_2     0x4e
#define hkwd_pse_do_write_job_control_1    0x4f

#define hkwd_pse_do_write_job_control_2    0x50
#define hkwd_pse_do_write_job_control_3    0x51
#define hkwd_pse_drv_priv                  0x52
#define hkwd_pse_fd_alloc                  0x53
#define hkwd_pse_fmodsw_install_1          0x54
#define hkwd_pse_fmodsw_install_2          0x55
#define hkwd_pse_fmodsw_install_3          0x56
#define hkwd_pse_fmodsw_remove             0x57
#define hkwd_pse_funnel_init               0x58
#define hkwd_pse_get_sth_from_fd_1         0x59
#define hkwd_pse_get_sth_from_fd_2         0x5a
#define hkwd_pse_get_sth_from_fd_3         0x5b
#define hkwd_pse_get_sth_from_fd_4         0x5c
#define hkwd_pse_get_sth_from_fd_5         0x5d
#define hkwd_pse_get_sth_from_fd_6         0x5e
#define hkwd_pse_getmsg                    0x5f

#define hkwd_pse_getpmsg                   0x60
#define hkwd_pse_init_funnel               0x61
#define hkwd_pse_log_configure_1           0x62
#define hkwd_pse_log_configure_2           0x63
#define hkwd_pse_log_open_1                0x64
#define hkwd_pse_log_open_2                0x65
#define hkwd_pse_mi_offset_param_mblk_1    0x66
#define hkwd_pse_mi_offset_param_mblk_2    0x67
#define hkwd_pse_mi_offset_param_mblk_3    0x68
#define hkwd_pse_mi_open_comm_1            0x69
#define hkwd_pse_mi_open_comm_2            0x6a
#define hkwd_pse_mi_open_comm_3            0x6b
#define hkwd_pse_nd_get_default            0x6c
#define hkwd_pse_nd_get_names              0x6d
#define hkwd_pse_nd_set_long               0x6e
#define hkwd_pse_open_wrapper              0x6f

#define hkwd_pse_osr_atmark                0x70
#define hkwd_pse_osr_bufcall               0x71
#define hkwd_pse_osr_canput                0x72
#define hkwd_pse_osr_ckband                0x73
#define hkwd_pse_osr_close_subr_2          0x74
#define hkwd_pse_osr_fdinsert              0x75
#define hkwd_pse_osr_fifo                  0x76
#define hkwd_pse_osr_find                  0x77
#define hkwd_pse_osr_flush                 0x78
#define hkwd_pse_osr_flushband             0x79
#define hkwd_pse_osr_flushdata_1           0x7a
#define hkwd_pse_osr_flushdata_2           0x7b
#define hkwd_pse_osr_flushdata_3           0x7c
#define hkwd_pse_osr_getband               0x7d
#define hkwd_pse_osr_getmsg                0x7e
#define hkwd_pse_osr_getmsg_subr           0x7f

#define hkwd_pse_osr_getpmsg               0x80
#define hkwd_pse_osr_getsig                0x81
#define hkwd_pse_osr_link                  0x82
#define hkwd_pse_osr_list                  0x83
#define hkwd_pse_osr_look                  0x84
#define hkwd_pse_osr_peek                  0x85
#define hkwd_pse_osr_pipe                  0x86
#define hkwd_pse_osr_pipestat              0x87
#define hkwd_pse_osr_pop                   0x88
#define hkwd_pse_osr_putmsg                0x89
#define hkwd_pse_osr_putmsg_subr           0x8a
#define hkwd_pse_osr_putpmsg               0x8b
#define hkwd_pse_osr_read                  0x8c
#define hkwd_pse_osr_recvfd                0x8d
#define hkwd_pse_osr_revoke_1              0x8e
#define hkwd_pse_osr_revoke_2              0x8f

#define hkwd_pse_osr_run                   0x90
#define hkwd_pse_osr_sendfd                0x91
#define hkwd_pse_osr_setcltime             0x92
#define hkwd_pse_osr_setsig                0x93
#define hkwd_pse_osr_sleep                 0x94
#define hkwd_pse_osr_srdopt_1              0x95
#define hkwd_pse_osr_srdopt_2              0x96
#define hkwd_pse_osr_srdopt_3              0x97
#define hkwd_pse_osr_srdopt_4              0x98
#define hkwd_pse_osr_str                   0x99
#define hkwd_pse_osr_swropt                0x9a
#define hkwd_pse_osr_tcsak_1               0x9b
#define hkwd_pse_osr_tcsak_2               0x9c
#define hkwd_pse_osr_tcskep                0x9d
#define hkwd_pse_osr_tctrust_1             0x9e
#define hkwd_pse_osr_tctrust_2             0x9f

#define hkwd_pse_osr_tctrust_3             0xa0
#define hkwd_pse_osr_tctrust_4             0xa1
#define hkwd_pse_osr_tcxonc                0xa2
#define hkwd_pse_osr_tioccons_1            0xa3
#define hkwd_pse_osr_tioccons_2            0xa4
#define hkwd_pse_osr_tiocgpgrp             0xa5
#define hkwd_pse_osr_tiocgsid              0xa6
#define hkwd_pse_osr_tiocknopgrp           0xa7
#define hkwd_pse_osr_tiocknosess           0xa8
#define hkwd_pse_osr_tiocsctty_1           0xa9
#define hkwd_pse_osr_tiocsctty_2           0xaa
#define hkwd_pse_osr_unlink_subr           0xab
#define hkwd_pse_osr_write                 0xac
#define hkwd_pse_pse_clone_open_2          0xad
#define hkwd_pse_pse_close_2               0xae
#define hkwd_pse_pse_ctb_callback          0xaf

#define hkwd_pse_pse_init_1                0xb0
#define hkwd_pse_pse_init_2                0xb1
#define hkwd_pse_pse_ioctl_1               0xb2
#define hkwd_pse_pse_open_4                0xb3
#define hkwd_pse_pse_read_2                0xb4
#define hkwd_pse_pse_revoke_2              0xb5
#define hkwd_pse_pse_select                0xb6
#define hkwd_pse_pse_write_2               0xb7
#define hkwd_pse_psebufcalls_init          0xb8
#define hkwd_pse_psetimers_init            0xb9
#define hkwd_pse_putmsg                    0xba
#define hkwd_pse_putpmsg                   0xbb
#define hkwd_pse_sad_configure             0xbc
#define hkwd_pse_sth_fattach_1             0xbd
#define hkwd_pse_sth_fattach_2             0xbe
#define hkwd_pse_sth_fattach_3             0xbf

#define hkwd_pse_sth_fd_to_sth_1           0xc0
#define hkwd_pse_sth_fd_to_sth_2           0xc1
#define hkwd_pse_sth_read_seek_1           0xc2
#define hkwd_pse_sth_read_seek_2           0xc3
#define hkwd_pse_sth_test_and_set_sth      0xc4
#define hkwd_pse_sth_tiocspgrp_1           0xc5
#define hkwd_pse_sth_tiocspgrp_2           0xc6
#define hkwd_pse_sth_tiocspgrp_3           0xc7
#define hkwd_pse_sth_tiocspgrp_4           0xc8
#define hkwd_pse_sth_tiocspgrp_5           0xc9
#define hkwd_pse_str_config                0xca
#define hkwd_pse_str_init                  0xcb
#define hkwd_pse_str_install               0xcc
#define hkwd_pse_str_term                  0xcd
#define hkwd_pse_strinfo_1                 0xce
#define hkwd_pse_strinfo_2                 0xcf

#define hkwd_pse_strinfo_3                 0xd0
#define hkwd_pse_strinfo_4                 0xd1
#define hkwd_pse_strlog_1                  0xd2
#define hkwd_pse_strlog_2                  0xd3
#define hkwd_pse_strlog_3                  0xd4
#define hkwd_pse_strlog_4                  0xd5
#define hkwd_pse_strmod_add_1              0xd6
#define hkwd_pse_strmod_add_2              0xd7
#define hkwd_pse_strmod_add_3              0xd8
#define hkwd_pse_strmod_del_1              0xd9
#define hkwd_pse_strmod_del_2              0xda
#define hkwd_pse_strmod_del_3              0xdb
#define hkwd_pse_strqget_1                 0xdc
#define hkwd_pse_strqget_2                 0xdd
#define hkwd_pse_strqset_1                 0xde
#define hkwd_pse_strqset_2                 0xdf

#define hkwd_pse_strreset                  0xe0
#define hkwd_pse_unweldq_1                 0xe1
#define hkwd_pse_unweldq_2                 0xe2
#define hkwd_pse_unweldq_3                 0xe3
#define hkwd_pse_weldq_1                   0xe4
#define hkwd_pse_weldq_2                   0xe5
#define hkwd_pse_weldq_3                   0xe6
#define hkwd_pse_weldq_comm                0xe7

/* pse : flag change sub hooks */
#define hkwd_pse_alloc_qband               0xe8
#define hkwd_pse_bcanput                   0xe9
#define hkwd_pse_bufcall_init_1            0xea
#define hkwd_pse_bufcall_init_2            0xeb
#define hkwd_pse_canput                    0xec
#define hkwd_pse_csq_lateral               0xed
#define hkwd_pse_csq_run_1                 0xee
#define hkwd_pse_csq_run_2                 0xef

#define hkwd_pse_csq_run_3                 0xf0
#define hkwd_pse_csq_run_4                 0xf1
#define hkwd_pse_enableok                  0xf2
#define hkwd_pse_flushband_1               0xf3
#define hkwd_pse_flushband_2               0xf4
#define hkwd_pse_flushq_1                  0xf5
#define hkwd_pse_flushq_2                  0xf6
#define hkwd_pse_funnel_putp               0xf7
#define hkwd_pse_funnelq_run_1             0xf8
#define hkwd_pse_funnelq_run_2             0xf9
#define hkwd_pse_funnelq_run_3             0xfa
#define hkwd_pse_funnelq_run_4             0xfb
#define hkwd_pse_getq_1                    0xfc
#define hkwd_pse_getq_2                    0xfd
#define hkwd_pse_getq_3                    0xfe
#define hkwd_pse_getq_4                    0xff

#define hkwd_pse_getq_5                    0x100
#define hkwd_pse_insq                      0x101
#define hkwd_pse_insqband                  0x102
#define hkwd_pse_mult_sqh_acquire          0x103
#define hkwd_pse_mult_sqh_release          0x104
#define hkwd_pse_noenable                  0x105
#define hkwd_pse_osr_add_modules           0x106
#define hkwd_pse_osr_alloc                 0x107
#define hkwd_pse_osr_close_subr_1          0x108
#define hkwd_pse_osr_open_1                0x109
#define hkwd_pse_osr_open_2                0x10a
#define hkwd_pse_osr_open_3                0x10b
#define hkwd_pse_osr_open_4                0x10c
#define hkwd_pse_osr_pipe_1                0x10d
#define hkwd_pse_osr_pipe_2                0x10e
#define hkwd_pse_osr_pop_subr_1            0x10f

#define hkwd_pse_osr_pop_subr_2            0x110
#define hkwd_pse_osr_pop_subr_3            0x111
#define hkwd_pse_osr_push_1                0x112
#define hkwd_pse_osr_push_2                0x113
#define hkwd_pse_osr_push_3                0x114
#define hkwd_pse_osr_str_1                 0x115
#define hkwd_pse_osr_str_2                 0x116
#define hkwd_pse_osr_str_3                 0x117
#define hkwd_pse_osr_str_4                 0x118
#define hkwd_pse_pse_clone_open_1          0x119
#define hkwd_pse_pse_close_1               0x11a
#define hkwd_pse_pse_ioctl_2               0x11b
#define hkwd_pse_pse_open_1                0x11c
#define hkwd_pse_pse_open_2                0x11d
#define hkwd_pse_pse_open_3                0x11e
#define hkwd_pse_pse_read_1                0x11f

#define hkwd_pse_pse_revoke_1              0x120
#define hkwd_pse_pse_write_1               0x121
#define hkwd_pse_putbq                     0x122
#define hkwd_pse_putbqband                 0x123
#define hkwd_pse_putq                      0x124
#define hkwd_pse_putqband                  0x125
#define hkwd_pse_q_alloc_1                 0x126
#define hkwd_pse_q_alloc_2                 0x127
#define hkwd_pse_rmvq_1                    0x128
#define hkwd_pse_rmvq_2                    0x129
#define hkwd_pse_rmvq_3                    0x12a
#define hkwd_pse_rmvq_4                    0x12b
#define hkwd_pse_sqh_set_parent_1          0x12c
#define hkwd_pse_sqh_set_parent_3          0x12d
#define hkwd_pse_sqh_set_parent_4          0x12e
#define hkwd_pse_sqh_set_parent_5          0x12f

#define hkwd_pse_sqh_set_parent_6           0x130
#define hkwd_pse_sqh_set_parent_7          0x131
#define hkwd_pse_sq_wrapper                0x132
#define hkwd_pse_sqh_set_parent_2          0x133
#define hkwd_pse_unweldq_cnx               0x134
#define hkwd_pse_unweldq_exec              0x135
#define hkwd_pse_weldq_cnx                 0x136
#define hkwd_pse_weldq_exec                0x137

#define HKWD_DLPI		0x4A700000
/* DLPI subhook */
#define hkwd_dlpi_open_in            1
#define hkwd_dlpi_open_error_1       2
#define hkwd_dlpi_open_out           3

#define hkwd_dlpi_close_in           4
#define hkwd_dlpi_close_1            5
#define hkwd_dlpi_close_err1         6
#define hkwd_dlpi_close_err2         7

#define hkwd_dlpi_wput_in            8
#define hkwd_dlpi_wput_type          9

#define hkwd_dlpi_rsrv_in            10
#define hkwd_dlpi_wsrv_in            11
#define hkwd_dlpi_wsrv_type          12
#define hkwd_dlpi_wsrv_data          13
#define hkwd_dlpi_wsrv_prim          14

#define hkwd_dlpi_dlattach_err1      15
#define hkwd_dlpi_dlattach_err2      16
#define hkwd_dlpi_dlattach_err3      17

#define hkwd_dlpi_dlunbindsap_err    18
#define hkwd_dlpi_dladdfilter_err    19
#define hkwd_dlpi_dldelfilter_err    20

#define hkwd_dlpi_dl_bind            21
#define hkwd_dlpi_dl_subs_bind       22
#define hkwd_dlpi_dl_add_filter      23
#define hkwd_dlpi_dl_add_filter_def  24

#define hkwd_dlpi_dl_connind         25 /* rx_sabme: discard dup dlb */
#define hkwd_dlpi_dl_connind_1       26 /* rx_sabme: discard pend table full dlb */ 
#define hkwd_dlpi_dl_connind_2       27 /* not use */
#define hkwd_dlpi_dl_connreq         28 /* not use */
#define hkwd_dlpi_dl_datareq         29 /* dl_datareq: state %d drop */
#define hkwd_dlpi_dl_rexmit          30 /* dl_rexmit: retransmitting I-frames */
#define hkwd_dlpi_dl_rexmit_1        31 /* dl_rexmit: cannot dup */
#define hkwd_dlpi_dl_rexmit_2        32 /* dl_rexmit: no outstanding I-frames */
#define hkwd_dlpi_tx_i_err1          33 /* tx_i: mkframe failed */
#define hkwd_dlpi_tx_i_err2          34 /* tx_i: tx_frame failed %d */
#define hkwd_dlpi_tx_super_err       35 /* tx_super: tx_frame failed %d */
#define hkwd_dlpi_rx_i               36 /* rx_i: reject drop (t = %d) */
#define hkwd_dlpi_rx_i_1             37 /* rx_i: sent reject ended */
#define hkwd_dlpi_rx_i_2             38 /* rx_i: mbuf convert drop */
#define hkwd_dlpi_chktimers_T1       39 /* chktimers: why is T1 still running */
#define hkwd_dlpi_chktimers_T2       40 /* chktimers: why is T2 still running */
#define hkwd_dlpi_expired_t1         41 /* expired_t1: retry %d */
#define hkwd_dlpi_expired_t1_1       42 /* expired_t1: retry exhausted */
#define hkwd_dlpi_expired_t2         43 /* expired_t2: retry %d */
#define hkwd_dlpi_expired_t2_1       44 /* expired_t2: retry exhausted */
#define hkwd_dlpi_expired_ti         45 /* expired_ti: retry %d */
#define hkwd_dlpi_expired_ti_1       46 /* expired_ti: busy retry exhausted */

#define hkwd_dlpi_rsrv_type          47

#define hkwd_dlpi_rx_xtauto          50 /* rx_xtauto: unsolicited response drop */
#define hkwd_dlpi_tx_frame2          51 /* dans tx.c */
#define hkwd_dlpi_tq_start           52 /* tq_start: %s tenths %d */

#define hkwd_dlpi_rx_ua              57 /* rx_ua: p%d f%d, dropped UA */
#define hkwd_dlpi_rx_ua_err          58 /* rx_ua: state %d dropped UA */
#define hkwd_dlpi_rx_dm_err          59 /* rx_dm: state %d dropped DM */
#define hkwd_dlpi_rx_disc_err        60 /* rx_disc: state %d dropped DISC */
#define hkwd_dlpi_rx_ui              61 /* rx_ui: flow control drop */
#define hkwd_dlpi_local_busy         62 /* local_busy */
#define hkwd_dlpi_local_okay         63 /* local_okay */
#define hkwd_dlpi_dlpillc            64 /* dlpillc: sap 0x%x: no stream drop */
#define hkwd_dlpi_dlpillc_1          65 /* dlpillc: multi drop"*/
#define hkwd_dlpi_dlpillc_2          66 /* 1: dlpillc: ctl 0x%x: bad LLC drop"
					   2 dlpillc: ctl 0x%x: codls mode drop
					   3 dlpillc: ctl 0x%x: listen DM
					   4 dlpillc: ctl 0x%x: listen drop
 				        */
#define hkwd_dlpi_dlpillc_3          67
#define hkwd_dlpi_drd_bind           68 /* drd_bind: ndd 0x%x ppa %d sap 0x%x */
#define hkwd_dlpi_drd_bind_err       69 /* drd_bind: cannot bind; ppa %d, err %d */
#define hkwd_dlpi_drd_unbind         70 /* drd_unbind: ndd 0x%x ppa %d sap 0x%x */
#define hkwd_dlpi_drd_unbind_err     71 /* drd_unbind: cannot bind; ppa %d, err %d */

#define hkwd_dlpi_drd_update         72

#define hkwd_dlpi_drd_timer          73
#define hkwd_dlpi_drd_timeout1       74
#define hkwd_dlpi_drd_timeout2       75
#define hkwd_dlpi_drd_intr1          76 
#define hkwd_dlpi_drd_intr2          77
#define hkwd_dlpi_drd_intr3          78
#define hkwd_dlpi_drd_intr4          79

#define hkwd_dlpi_config_init        80
#define hkwd_dlpi_config_stop        81

#define hkwd_dlpi_nddrele            82



#define HKWD_XTISO		0x4A800000
/* XTI subhookid */
#define hkwd_xti_config_in		1
#define hkwd_xti_config_out		2
#define hkwd_xti_open_in		3
#define hkwd_xti_open_clone             4
#define hkwd_xti_open_noclone           5
#define hkwd_xti_open_noclone1          6
#define hkwd_xti_open_1                 7
#define hkwd_xti_open_2                 8
#define hkwd_xti_open_3                 9
#define hkwd_xti_wput_in		10
#define hkwd_xti_wput_prim              11
#define hkwd_xti_wput_in_type           12
#define hkwd_xti_wput_error             13
#define hkwd_xti_wput_error5            14
#define hkwd_xti_wput_error6            15
#define hkwd_xti_wput_error7            16
#define hkwd_xti_close_in		17
#define hkwd_xti_rsrv_in		18
#define hkwd_xti_wsrv_in		20
#define hkwd_xti_wsrv_in1               21
#define hkwd_xti_wsrv_in2               22
#define hkwd_xti_wsrv_in3               23
#define hkwd_xti_wsrv_in4               24
#define hkwd_xti_event_state		25
#define hkwd_xti_event_state1		26
#define hkwd_xti_addr_req               30
#define hkwd_xti_addrreq_error		31
#define hkwd_xti_bind_req		35
#define hkwd_xti_bindreq_error		36
#define hkwd_xti_bind_req1		37
#define hkwd_xti_bindreq_error1		38
#define hkwd_xti_bind_req2              39
#define hkwd_xti_bindreq_err            40
#define hkwd_xti_bind_req3		41
#define hkwd_xti_unbind_req             46
#define hkwd_xti_unbind_req1            47
#define hkwd_xti_unbindreq_error	48
#define hkwd_xti_optmgmt_req     	49
#define hkwd_xti_optmgmtreq_error	50
#define hkwd_xti_optmgmtreq_error1	51
#define hkwd_xti_listen_req             52
#define hkwd_xti_listenreq_error1	57
#define hkwd_xti_listenreq_error2	58
#define hkwd_xti_listenreq_error3	59
#define hkwd_xti_connreq_error	        60
#define hkwd_xti_conn_req               61
#define hkwd_xti_conn_res               62
#define hkwd_xti_discon_req             63
#define hkwd_xti_data_req               64
#define hkwd_xti_exdata_req             65
#define hkwd_xti_unitdata_req           66
#define hkwd_xti_ordrel_req             67
#define hkwd_xti_info_req               68
#define hkwd_xti_unitdata_req_1         69
#define hkwd_xti_connreq_connect        71
#define hkwd_xti_connres_error          72
#define hkwd_xti_disconreq_error        73
#define hkwd_xti_datareq_error          74
#define hkwd_xti_exdatareq_error        75
#define hkwd_xti_unitdatareq_error      76
#define hkwd_xti_ordrelreq_error        77
#define hkwd_xti_startup_bind           82
#define hkwd_xti_startup_binderr        83
#define hkwd_xti_startup_error          84
#define hkwd_xti_startup_error1         85
#define hkwd_xti_disconind_error        86
#define hkwd_xti_dataind_error          87
#define hkwd_xti_unitdataind_error      88
#define hkwd_xti_ordrelind_error        89
#define hkwd_xti_solisten1              90
#define hkwd_xti_solisten2              91
#define hkwd_xti_ordrelind_error1       92
#define hkwd_xti_send                   93
#define hkwd_xti_send1                  95
#define hkwd_xti_send_err               96
#define hkwd_xti_send_error             98
#define hkwd_xti_rcv                    97
#define hkwd_xti_finished_error         99
#define hkwd_xti_dumpso                 100
#define hkwd_xti_dumpproto              101
#define hkwd_xti_dumpiocblk             102
#define hkwd_xti_dumpproto_2            103
#define hkwd_xti_setopt_error           104
#define hkwd_xti_rcv_1                  105
#define hkwd_xti_rcv_2                  106
#define hkwd_xti_rcv_3                  107
#define hkwd_xti_prec_insq              110
#define hkwd_xti_prec_insq1             111
#define hkwd_xti_output                 112
#define hkwd_xti_input                  113
#define hkwd_xti_input1                 114
#define hkwd_xti_new_tp_ind             115
#define hkwd_xti_conn_ind               116
#define hkwd_xti_conn_con               117
#define hkwd_xti_discon_ind             118
#define hkwd_xti_data_ind               119 
#define hkwd_xti_ordrel_ind             120 
#define hkwd_xti_unitdata_ind           121  
#define hkwd_xti_uderror_ind            122
#define hkwd_xti_cleanup                123
#define hkwd_xti_finished               124
#define hkwd_xti_snd_error_ack          125
#define hkwd_xti_snd_flushrw            126
#define hkwd_xti_snd_ok_ack             127
#define hkwd_xti_entryinit_err          128
#define hkwd_xti_entryinit              129
#define hkwd_xti_wqenable               130
#define hkwd_xti_rqenable               131
#define hkwd_xti_canput                 132
#define hkwd_xti_init_socket            133 
#define hkwd_xti_putnext                134
#define hkwd_xti_discon_ind_1           135

#define hkwd_xti_canput_1               137
#define hkwd_xti_canput_2               138
#define hkwd_xti_new_tp_ind1            140
#define hkwd_xti_new_tp_ind2            141
#define hkwd_xti_new_tp_ind3            142
#define hkwd_xti_new_tp_ind4            143
#define hkwd_xti_new_tp_ind5            146
#define hkwd_xti_new_tp_ind6            147
#define hkwd_xti_copytombuf             150
#define hkwd_xti_copytombuf1            151
#define hkwd_xti_copytombuf2            152

#define HKWD_TIMOD		0x4A900000
/* TIMOD subhook */
#define hkwd_timod_open_in            1
#define hkwd_timod_open_1             2
#define hkwd_timod_close_in           3
#define hkwd_timod_close_1            4
#define hkwd_timod_rput_in            5
#define hkwd_timod_rput_type          6
#define hkwd_timod_rput_prim          7
#define hkwd_timod_wput_in            8
#define hkwd_timod_wput_type          9
#define hkwd_timod_wput_prim1         10
#define hkwd_timod_wput_prim2         11

#define HKWD_TIRDWR		0x4AA00000
/* TIRDWR subhook */
#define hkwd_tirdwr_open_in            1
#define hkwd_tirdwr_open_error         2
#define hkwd_tirdwr_close_in           3  
#define hkwd_tirdwr_close_in_1         4
#define hkwd_tirdwr_rput_in            5
#define hkwd_tirdwr_rput_type          6
#define hkwd_tirdwr_rput_prim          7
#define hkwd_tirdwr_wput_in            8
#define hkwd_tirdwr_wput_type          9

/* hooks for thread-based services */
#define HKWD_KERN_ASSERTWAIT		0x46000000
#define HKWD_KERN_CLEARWAIT		0x46100000
#define HKWD_KERN_THREADBLOCK		0x46200000
#define HKWD_KERN_EMPSLEEP		0x46300000
#define HKWD_KERN_EWAKEUPONE		0x46400000
#define HKWD_SYSC_CRTHREAD		0x46500000
#define HKWD_KERN_KTHREADSTART		0x46600000
#define HKWD_SYSC_TERMTHREAD  		0x46700000
#define HKWD_KERN_KSUSPEND    		0x46800000
#define HKWD_SYSC_THREADSETSTATE    	0x46900000
#define HKWD_SYSC_THREADTERM_ACK    	0x46A00000
#define HKWD_SYSC_THREADSETSCHED    	0x46B00000
#define HKWD_KERN_TIDSIG    		0x46C00000
#define HKWD_KERN_WAITLOCK  		0x46D00000
#define HKWD_KERN_WAKEUPLOCK		0x46E00000
#define HKWD_SYSC_THREADLOCKBOOST    	0x47600000
#define HKWD_KERN_WAITLOCKLOCAL         0x47700000

/* Hook for PCMCIA Socket Services */
#define	HKWD_PCMCIA_SS			0x23000000
/* Hook for PCMCIA Card Services */
#define	HKWD_PCMCIA_CS			0x34300000

/* Hooks for SECURITY */
#define HKWD_SEC			0x3B700000  /* Security major events */
#define HKWD_SEC_DATA			0x3B800000  /* Security data events  */
#define HKWD_SEC_CRED			0x52F00000  /* Security credential alloc/dealloc  */

/* Hook for Network Buffer Cache */
#define HKWD_NBC			0x2ED00000  /* Network Buffer Cache */

/* Hook Word for WLM */
#define HKWD_WLM_STAGE1			0x2F900000  /* Workload Management */

/*
 * RAS: high availability services
 */

#define HKWD_RPDP		0x2FD00000	    /* RPDP */
/* RPDP with sub-hook-ID-s */
#define HKWD_RPDP_START		(HKWD_RPDP | 0)	    /* RPDP start */
#define HKWD_RPDP_ABORT		(HKWD_RPDP | 1)	    /* RPDP aborted */
#define HKWD_RPDP_SUCCESS	(HKWD_RPDP | 2)	    /* RPDP successfully done */
#define HKWD_RPDP_HAEH		(HKWD_RPDP | 0x10)  /* HA handler: ACCEPTED */
#define HKWD_RPDP_HAEH_BAD	(HKWD_RPDP | 0x11)  /* HA handler: REFUSED */
#define HKWD_RPDP_IT_REROUTE	(HKWD_RPDP | 0x20)  /* Interrupt re-route */
#define HKWD_RPDP_CPUSWAP	(HKWD_RPDP | 0x30)  /* CPU swap takes place */
#define HKWD_RPDP_TRB_MIGR	(HKWD_RPDP | 0x40)  /* Timer migrated */
#define HKWD_RPDP_STOP_SELF	(HKWD_RPDP | 0x50)  /* pal_stop_myself() */

#define	HKWD_SYSFR		0x2FE00000	    /* System freeze */
/* System freeze with sub-hook-ID-s */
#define HKWD_SYSFR_START	(HKWD_SYSFR | 0)    /* System freeze start */
#define HKWD_SYSFR_END		(HKWD_SYSFR | 1)    /* System freeze end */
#define HKWD_SYSFR_MASTER_START	(HKWD_SYSFR | 0x20) /* Freeze master start */
#define HKWD_SYSFR_MASTER_END	(HKWD_SYSFR | 0x21) /* Freeze master end */
#define HKWD_SYSFR_SLAVE_START	(HKWD_SYSFR | 0x30) /* Fr. slave command start*/
#define HKWD_SYSFR_SLAVE_END	(HKWD_SYSFR | 0x31) /* Fr. slave command end */
#define HKWD_SYSFR_BLOCK_IT	(HKWD_SYSFR | 0x40) /* Block ext. interrupts */
#define HKWD_SYSFR_ENABLE_IT	(HKWD_SYSFR | 0x41) /* Enable ext. interrupts */
#define HKWD_SYSFR_DIS_PLVL	(HKWD_SYSFR | 0x50) /*Before pal_i_disableplvl*/
#define HKWD_SYSFR_DIS_PLVL_END	(HKWD_SYSFR | 0x51) /* After pal_i_disableplvl*/
#define HKWD_SYSFR_EN_PLVL	(HKWD_SYSFR | 0x60) /* Before pal_i_enableplvl*/
#define HKWD_SYSFR_EN_PLVL_END	(HKWD_SYSFR | 0x61) /* After pal_i_enableplvl */

/*
 * Dynamic Reconfiguration
 */
#define HKWD_DR			0x38F00000	    /* DR */

/* subhook ids */

#define hkwd_DR_REGISTER		0x01
#define hkwd_REGISTER_DR_EVENT		0x02
#define hkwd_DR_NOTIFY			0x03
#define hkwd_DR_UNREGISTER		0x04
#define hkwd_UNREGISTER_DR_EVENT	0x05
#define hkwd_DR_RECONFIG		0x06

#define hkwd_RECONFIG_REGISTER_ENTRY	0x14
#define hkwd_RECONFIG_REGISTER_EXIT	0x15
#define hkwd_RECONFIG_UNREGISTER_ENTRY	0x16
#define hkwd_RECONFIG_UNREGISTER_EXIT	0x17
#define hkwd_RECONFIG_COMPLETE_ENTRY	0x18
#define hkwd_RECONFIG_COMPLETE_HNAME	0x19
#define hkwd_RECONFIG_COMPLETE_EXIT	0x1A

#define hkwd_INVOKE_HANDLERS_ENTRY	0x28
#define hkwd_INVOKE_HANDLERS_SLEEP	0x29
#define hkwd_INVOKE_HANDLERS_AWAKE	0x2A

#define hkwd_MPC_REMOVE_HANDLER		0x32
#define hkwd_MPC_FREEZE_HANDLER		0x33

#define hkwd_SEND_SIGNAL		0x3C
#define hkwd_NPROC_POSTED		0x3D

#define hkwd_GET_USER_DATA		0x46
#define hkwd_DR_CALLOUT			0x47
#define hkwd_VALIDATE_PHASE		0x48
#define hkwd_VALIDATE_NOTIFY		0x49
#define hkwd_RUN_NOTIFY			0x4A
#define hkwd_KERNEL_NOTIFY		0x4B
#define hkwd_CLEAR_DRPARMS		0x4C

#define hkwd_HA_PROC			0x5A
#define hkwd_HA_PROC_FAIL_LCPU		0x5B
#define hkwd_DR_FAIL_LCPU_STATUS	0x5C
#define hkwd_DR_MIGRATE_WDOGS		0x5D
#define hkwd_DR_SEND_SIGCPUFAIL		0x5E

#define hkwd_ADDCPU_VALIDATE		0x64
#define hkwd_ADDCPU_PRE			0x65
#define hkwd_ADDCPU_CLEANUP		0x66
#define hkwd_ADDCPU_DOIT		0x67
#define hkwd_DR_START_CPU		0x68
#define hkwd_DR_MAIN_BS_PROC		0x69
#define hkwd_DR_VMM_INIT		0x6A
#define hkwd_DR_UPDATE_PNDA		0x6B
#define hkwd_DR_REROUTE_IT		0x6C

#define hkwd_DR_RM_ATTACH		0x78
#define hkwd_DR_MIGR_CLASS_ANY		0x79
#define hkwd_DR_STOP_LCPU		0x7A
#define hkwd_DR_MOVE_THREADS		0x7B
#define hkwd_RMCPU_VALIDATE		0x7C
#define hkwd_RMCPU_PRE			0x7D
#define hkwd_RMCPU_DOIT			0x7E
#define hkwd_RMCPU_CLEANUP		0x7F
#define hkwd_DR_CONTROLING_LCPU		0x80
#define hkwd_CALL_HA_HANDLERS		0x81
#define hkwd_DISABLE_DECR		0x82
#define hkwd_ENABLE_DECR		0x83
#define hkwd_DR_NEW_MASTER_LCPU		0x84
#define hkwd_RMCPU_STATUS		0x85

#define hkwd_FIND_DUMMY_PPDA		0x8C
#define hkwd_SCPU_VALIDATE		0x8D
#define hkwd_SCPU_DOIT			0x8E
#define hkwd_SCPU_START			0x8F
#define hkwd_SCPU_SUCCESS		0x90
#define hkwd_FAIL_CPU_STOPPED		0x91


/*
 * Checkpoint/Restart
 */
#define HKWD_CR			0x49E00000

/* subhook ids */

#define hkwd_CHK_START			1
#define hkwd_ISSUE_CHKPT		2
#define hkwd_INVOKE_HANDLER		3
#define hkwd_CALL_COMMIT		4
#define hkwd_PROCESS_SUSP		5
#define hkwd_START_WRITE		6
#define hkwd_FINISH_WRITE		7
#define hkwd_EXIT_CHKPT			8
#define hkwd_CHK_FINISH			9


/* hooks for security development */

#define hkwd_SEC_GETCONFATTR_ENTRY	10
#define hkwd_SEC_GETCONFATTR_FAILURE	11
#define hkwd_SEC_GETCONFATTR_SUCCESS	12
#define hkwd_SEC_GETGROUPATTR_ENTRY	20
#define hkwd_SEC_GETGROUPATTR_FAILURE	21
#define hkwd_SEC_GETGROUPATTR_SUCCESS	22
#define hkwd_SEC_PUTGROUPATTR_ENTRY	30
#define hkwd_SEC_PUTGROUPATTR_FAILURE	31
#define hkwd_SEC_PUTGROUPATTR_SUCCESS	32
#define hkwd_SEC_IDTOGROUP_ENTRY	40
#define hkwd_SEC_IDTOGROUP_SUCCESS	41
#define hkwd_SEC_IDTOGROUP_FAILURE	42
#define hkwd_SEC_GROUPTOID_ENTRY	50
#define hkwd_SEC_GROUPTOID_SUCCESS	51
#define hkwd_SEC_GROUPTOID_FAILURE	52
#define hkwd_SEC_IDTOUSER_ENTRY		60
#define hkwd_SEC_IDTOUSER_FAILURE	61
#define hkwd_SEC_IDTOUSER_SUCCESS	62
#define hkwd_SEC_GETUSERATTR_ENTRY	70
#define hkwd_SEC_GETUSERATTR_FAILURE	71
#define hkwd_SEC_GETUSERATTR_SUCCESS	72
#define hkwd_SEC_PUTUSERATTR_ENTRY	80
#define hkwd_SEC_PUTUSERATTR_FAILURE	81
#define hkwd_SEC_PUTUSERATTR_SUCCESS	82
#define hkwd_SEC_GETUSERPW_ENTRY	90
#define hkwd_SEC_GETUSERPW_SUCCESS	91
#define hkwd_SEC_GETUSERPW_FAILURE	92
#define hkwd_SEC_PUTUSERPW_ENTRY	100
#define hkwd_SEC_PUTUSERPW_FAILURE	101
#define hkwd_SEC_PUTUSERPW_SUCCESS	102
#define hkwd_SEC_GETGENERICATTR_ENTRY	110
#define hkwd_SEC_GETGENERICATTR_RETURN	112
#define hkwd_SEC_PUTGENERICATTR_ENTRY	120
#define hkwd_SEC_PUTGENERICATTR_RETURN	122
#define hkwd_SEC_GETPENV_ENTRY		130
#define hkwd_SEC_GETPENV_FAILURE	131
#define hkwd_SEC_GETPENV_SUCCESS	132
#define hkwd_SEC_SETPENV_ENTRY		140
#define hkwd_SEC_SETPENV_FAILURE	141
#define hkwd_SEC_SETPENV_SUCCESS	142
#define hkwd_SEC_SETPCRED_ENTRY		150
#define hkwd_SEC_SETPCRED_FAILURE	151
#define hkwd_SEC_SETPCRED_SUCCESS	152
#define hkwd_SEC_GETPCRED_ENTRY		160
#define hkwd_SEC_GETPCRED_FAILURE	161
#define hkwd_SEC_GETPCRED_SUCCESS	162
#define hkwd_SEC_AUTHENTICATE_ENTRY	170
#define hkwd_SEC_AUTHENTICATE_MACRO	171
#define hkwd_SEC_AUTHENTICATE_GRAMMAR	173
#define hkwd_SEC_GETPWNAM_R_ENTRY	180
#define hkwd_SEC_GETPWNAM_R_RETURN	181
#define hkwd_SEC_GETPWUID_R_ENTRY	190
#define hkwd_SEC_GETPWUID_R_RETURN	191
#define hkwd_SEC_GETPWENT_R_ENTRY	200
#define hkwd_SEC_GETPWENT_R_RETURN	201
#define hkwd_SEC_GETGRNAM_R_ENTRY	210
#define hkwd_SEC_GETGRGID_R_ENTRY	220
#define hkwd_SEC_GETGRGID_R_RETURN	221
#define hkwd_SEC_GETGRENT_R_ENTRY	230
#define hkwd_SEC_BAD_STANZA		231

/* PKI Service Module Sub-hook IDs */
#define hkwd_SEC_PKIMQUERYVERSIONS_ENTRY	244
#define hkwd_SEC_PKIMQUERYVERSIONS_FAILURE	245
#define hkwd_SEC_PKIMQUERYVERSIONS_SUCCESS	246
#define hkwd_SEC_PKIMERRORMODTEXT_ENTRY		247
#define hkwd_SEC_PKIMERRORMODTEXT_FAILURE	248
#define hkwd_SEC_PKIMERRORMODTEXT_SUCCESS	249
#define hkwd_SEC_PKIMLISTBUILD_ENTRY		250
#define hkwd_SEC_PKIMLISTBUILD_FAILURE		251
#define hkwd_SEC_PKIMLISTBUILD_SUCCESS		252
#define hkwd_SEC_PKIMLISTFREE_ENTRY		253
#define hkwd_SEC_PKIMLISTFREE_SUCCESS		255
#define hkwd_SEC_PKIMLISTLOADSRV_ENTRY		256
#define hkwd_SEC_PKIMLISTLOADSRV_FAILURE	257
#define hkwd_SEC_PKIMLISTLOADSRV_SUCCESS	258
#define hkwd_SEC_PKIMCERTCREATE_ENTRY		260
#define hkwd_SEC_PKIMCERTCREATE_FAILURE		261
#define hkwd_SEC_PKIMCERTCREATE_SUCCESS		262
#define hkwd_SEC_PKIMCERTREVOKE_ENTRY		263
#define hkwd_SEC_PKIMCERTREVOKE_FAILURE		264
#define hkwd_SEC_PKIMCERTREVOKE_SUCCESS		265
#define hkwd_SEC_PKIMCERTVERIFY_ENTRY		266
#define hkwd_SEC_PKIMCERTVERIFY_FAILURE		267
#define hkwd_SEC_PKIMCERTVERIFY_SUCCESS		268
#define hkwd_SEC_PKIMKSCHPASSWD_ENTRY		269
#define hkwd_SEC_PKIMKSCHPASSWD_FAILURE		270
#define hkwd_SEC_PKIMKSCHPASSWD_SUCCESS		271
#define hkwd_SEC_PKIMKSPASSWDRULES_ENTRY	272
#define hkwd_SEC_PKIMKSPASSWDRULES_FAILURE	273
#define hkwd_SEC_PKIMKSPASSWDRULES_SUCCESS	274
#define hkwd_SEC_PKIMKSVRFYPASSWD_ENTRY		275
#define hkwd_SEC_PKIMKSVRFYPASSWD_FAILURE	276
#define hkwd_SEC_PKIMKSVRFYPASSWD_SUCCESS	277
#define hkwd_SEC_PKIMKSCPOBJECTS_ENTRY		278
#define hkwd_SEC_PKIMKSCPOBJECTS_FAILURE	279
#define hkwd_SEC_PKIMKSCPOBJECTS_SUCCESS	280
#define hkwd_SEC_PKIMKSLSOBJECTS_ENTRY		281
#define hkwd_SEC_PKIMKSLSOBJECTS_FAILURE	282
#define hkwd_SEC_PKIMKSLSOBJECTS_SUCCESS	283
#define hkwd_SEC_PKIMKSRMOBJECTS_ENTRY		284
#define hkwd_SEC_PKIMKSRMOBJECTS_FAILURE	285
#define hkwd_SEC_PKIMKSRMOBJECTS_SUCCESS	286
#define hkwd_SEC_PKIMUSERCREATE_ENTRY		287
#define hkwd_SEC_PKIMUSERCREATE_FAILURE		288
#define hkwd_SEC_PKIMUSERCREATE_SUCCESS		289
#define hkwd_SEC_PKIMUSERDISABLE_ENTRY		290
#define hkwd_SEC_PKIMUSERDISABLE_FAILURE	291
#define hkwd_SEC_PKIMUSERDISABLE_SUCCESS	292
#define hkwd_SEC_PKIMQUERYMETHODS_ENTRY		293
#define hkwd_SEC_PKIMQUERYMETHODS_FAILURE	294
#define hkwd_SEC_PKIMQUERYMETHODS_SUCCESS	295
#define hkwd_SEC_PKIMCTRLCLEANUP_ENTRY		296
#define hkwd_SEC_PKIMCTRLCLEANUP_FAILURE	297
#define hkwd_SEC_PKIMCTRLCLEANUP_SUCCESS	298


/* PKI Toolkit Library Sub-hook IDs */

#define hkwd_SEC_PKIT_FUNC_ENTRY	300
#define hkwd_SEC_PKIT_FUNC_INFO		301
#define hkwd_SEC_PKIT_FUNC_FAILURE	302
#define hkwd_SEC_PKIT_FUNC_SUCCESS	303

/* PKI Load Module Sub-hook IDs */

#define hkwd_SEC_PKIL_FUNC_ENTRY	304
#define hkwd_SEC_PKIL_FUNC_INFO		305
#define hkwd_SEC_PKIL_FUNC_FAILURE	306
#define hkwd_SEC_PKIL_FUNC_SUCCESS	307

/* PKI Certificate and Key Management Commands Sub-hook IDs */

#define hkwd_SEC_CERT_COMMANDS_FUNC_ENTRY	320
#define hkwd_SEC_CERT_COMMANDS_FUNC_SUCCESS	321
#define hkwd_SEC_CERT_COMMANDS_FUNC_FAIL	322
#define hkwd_SEC_CERT_COMMANDS_FUNC_INFO	323


#define hkwd_SEC_ACCESSX_ENTRY		10000
#define hkwd_SEC_ACCESSX_EXIT		10001
#define hkwd_SEC_FACCESSX_ENTRY		10010
#define hkwd_SEC_FACCESSX_EXIT		10011
#define hkwd_SEC_AUDIT_ENTRY		10020
#define hkwd_SEC_AUDIT_EXIT		10021
#define hkwd_SEC_AUDITBIN_ENTRY		10030
#define hkwd_SEC_AUDITBIN_EXIT		10031
#define hkwd_SEC_AUDITLOG_ENTRY		10040
#define hkwd_SEC_AUDITLOG_EXIT		10041
#define hkwd_SEC_AUDITEVENTS_ENTRY	10050
#define hkwd_SEC_AUDITEVENTS_EXIT	10051
#define hkwd_SEC_AUDITPROC_ENTRY	10060
#define hkwd_SEC_AUDITPROC_EXIT		10061
#define hkwd_SEC_AUDITPROC_ERROR	10062
#define hkwd_SEC_CHACL_ENTRY		10070
#define hkwd_SEC_CHACL_EXIT		10071
#define hkwd_SEC_FCHACL_ENTRY		10080
#define hkwd_SEC_FCHACL_EXIT		10081
#define hkwd_SEC_CHPRIV_ENTRY		10090
#define hkwd_SEC_CHPRIV_EXIT		10091
#define hkwd_SEC_FCHPRIV_ENTRY		10100
#define hkwd_SEC_FCHPRIV_EXIT		10101
#define hkwd_SEC_PRIVCHECK_ENTRY	10110
#define hkwd_SEC_PRIVCHECK_EXIT		10111
#define hkwd_SEC_REVOKE_ENTRY		10120
#define hkwd_SEC_REVOKE_EXIT		10121
#define hkwd_SEC_FREVOKE_ENTRY		10130
#define hkwd_SEC_FREVOKE_EXIT		10131
#define hkwd_SEC_STATACL_ENTRY		10140
#define hkwd_SEC_STATACL_EXIT		10141
#define hkwd_SEC_FSTATACL_ENTRY		10150
#define hkwd_SEC_FSTATACL_EXIT		10151
#define hkwd_SEC_STATPRIV_ENTRY		10160
#define hkwd_SEC_STATPRIV_EXIT		10161
#define hkwd_SEC_FSTATPRIV_ENTRY	10170
#define hkwd_SEC_FSTATPRIV_EXIT		10171
#define	hkwd_SEC_FSTATACLX_ENTRY	10172
#define	hkwd_SEC_FSTATACLX_EXIT		10173
#define	hkwd_SEC_FCHACLX_ENTRY		10174
#define	hkwd_SEC_FCHACLX_EXIT		10175
#define	hkwd_SEC_CHACLX_ENTRY		10176
#define	hkwd_SEC_CHACLX_EXIT		10177
#define hkwd_SEC_STATACLX_ENTRY		10178
#define	hkwd_SEC_STATACLX_EXIT		10179
#define	hkwd_SEC_FCHXACL_ENTRY		10180
#define	hkwd_SEC_FCHXACL_EXIT		10181
#define	hkwd_SEC_CHXACL_ENTRY		10182
#define	hkwd_SEC_CHXACL_EXIT		10183
#define	hkwd_SEC_FSTATXACL_ENTRY	10184
#define	hkwd_SEC_FSTATXACL_EXIT		10185
#define	hkwd_SEC_STATXACL_ENTRY		10186
#define	hkwd_SEC_STATXACL_EXIT		10187
#define	hkwd_SEC_ACLXCNTL_ENTRY		10188
#define	hkwd_SEC_ACLXCNTL_EXIT		10189

#define	hkwd_SEC_CRED_CRGET		10300
#define	hkwd_SEC_CRED_CRFREE		10301
#define	hkwd_SEC_CRED_CRDUP		10302
#define	hkwd_SEC_CRED_CRHOLD		10303
#define	hkwd_SEC_CRED_CRREF		10304
#define	hkwd_SEC_CRED_CRCOPY		10305

#define hkwd_SEC_DATA1			1
#define hkwd_SEC_DATA2			2
#define hkwd_SEC_DATA3			3
#define hkwd_SEC_DATA4			4




/*
 *	HOOK ID's used by the PThreads instrumentation in
 *	"libpthreads.a".
 *
 */

#define HKWD_PTHREAD_SCHEDULER                                          0x60000000
#define HKWD_PTHREAD_TIMER                                              0x60300000
#define HKWD_PTHREAD_VPSLEEP                                            0x60500000
#define HKWD_PTHREAD_COND                                               0x60600000
#define HKWD_PTHREAD_MUTEX                                              0x60700000
#define HKWD_PTHREAD_SPINLOCK                                           0x48E00000
#define HKWD_PTHREAD_BARRIER                                            0x49600000
#define HKWD_PTHREAD_RWLOCK                                             0x60800000
#define HKWD_PTHREAD_GENERAL                                            0x60900000



/*
 *	Corresponding PThreads subhook declarations.
 *
 */

/* HKWD_PTHREAD_SCHEDULER subhooks.		*/
#define hkwd_PTHREAD_SCHED_KERN_SLEEP                              0x01
#define hkwd_PTHREAD_SCHED_KERN_AWAKE				   0x02
#define hkwd_PTHREAD_SCHED_YIELD                                   0x03
#define hkwd_PTHREAD_SCHED_SLEEP                                   0x04
#define hkwd_PTHREAD_SCHED_RUNQ_ADD                                0x05
#define hkwd_PTHREAD_SCHED_TIMESLICE_ENTRY                         0x06
#define hkwd_PTHREAD_SCHED_TIMESLICE_EXIT                          0x07
#define hkwd_PTHREAD_SCHED_TIMESLICE_EXIT_DISABLED                 0x08

/* HKWD_PTHREAD_TIMER subhooks.			*/
#define hkwd_PTHREAD_TIMER_SLEEP_NONEMPTY			   0x01
#define hkwd_PTHREAD_TIMER_SLEEP_EMPTY				   0x02
#define hkwd_PTHREAD_TIMER_AWAKE_NONEMPTY			   0x03
#define hkwd_PTHREAD_TIMER_AWAKE_EMPTY				   0x04

/* HKWD_PTHREAD_VPSLEEP subhooks.		*/
#define hkwd_PTHREAD_VPSLEEP_KERN_SLEEP	                           0x01
#define hkwd_PTHREAD_VPSLEEP_KERN_AWAKE	                           0x02
#define hkwd_PTHREAD_VPSLEEP_ENTRY                                 0x03
#define hkwd_PTHREAD_VPSLEEP_EXIT                                  0x04

/* HKWD_PTHREAD_COND subhooks.		*/
#define hkwd_PTHREAD_COND_INIT	                                   0x01
#define hkwd_PTHREAD_COND_DESTROY                                  0x02
#define hkwd_PTHREAD_COND_WAIT_ENTRY				   0x03
#define hkwd_PTHREAD_COND_WAIT_EXIT                                0x04
#define hkwd_PTHREAD_COND_TIMEDWAIT_ENTRY                          0x05
#define hkwd_PTHREAD_COND_TIMEDWAIT_EXIT                           0x06
#define hkwd_PTHREAD_COND_SIGNAL                                   0x07
#define hkwd_PTHREAD_COND_BROADCAST                                0x08

/* HKWD_PTHREAD_MUTEX subhooks.		*/
#define hkwd_PTHREAD_MUTEX_INIT						   0x01
#define hkwd_PTHREAD_MUTEX_DESTROY					   0x02
#define hkwd_PTHREAD_MUTEX_TAKEN_LOCAL				   0x03
#define hkwd_PTHREAD_MUTEX_TAKEN_GLOBAL				   0x04
#define hkwd_PTHREAD_MUTEX_MISS_LOCAL				   0x05
#define hkwd_PTHREAD_MUTEX_MISS_GLOBAL				   0x06
#define hkwd_PTHREAD_MUTEX_TRY_TAKEN_LOCAL			   0x07
#define hkwd_PTHREAD_MUTEX_TRY_TAKEN_GLOBAL			   0x08
#define hkwd_PTHREAD_MUTEX_TRY_MISS_LOCAL			   0x09
#define hkwd_PTHREAD_MUTEX_TRY_MISS_GLOBAL			   0x0A
#define hkwd_PTHREAD_MUTEX_RECURSIVE_TAKEN			   0x0B
#define hkwd_PTHREAD_MUTEX_RELEASE_LOCAL			   0x0C
#define hkwd_PTHREAD_MUTEX_RELEASE_GLOBAL			   0x0D
#define hkwd_PTHREAD_MUTEX_RECURSIVE_RELEASE		           0x0E
#define hkwd_PTHREAD_MUTEX_WAIT_LOCAL				   0x0F
#define hkwd_PTHREAD_MUTEX_WAIT_GLOBAL				   0x10
#define hkwd_PTHREAD_MUTEX_RUNQ_LOCK				   0x11
#define hkwd_PTHREAD_MUTEX_RUNQ_RELEASE				   0x12
#define hkwd_PTHREAD_MUTEX_BOOST				   0x13
#define hkwd_PTHREAD_MUTEX_UNBOOST				   0x14
#define hkwd_PTHREAD_MUTEX_CEILING_FAIL				   0x15
#define hkwd_PTHREAD_MUTEX_CAN_BOOST				   0x16
#define hkwd_PTHREAD_MUTEX_CAN_BOOST_LOCAL			   0x17
#define hkwd_PTHREAD_MUTEX_LOCAL_TIMEDOUT			   0x18
#define hkwd_PTHREAD_MUTEX_GLOBAL_TIMEDOUT			   0x19

/* HKWD_PTHREAD_RWLOCK subhooks.	*/
#define hkwd_PTHREAD_RWLOCK_INIT					   0x01
#define hkwd_PTHREAD_RWLOCK_DESTROY					   0x02
#define hkwd_PTHREAD_RWLOCK_UNLOCK					   0x03
#define hkwd_PTHREAD_RWLOCK_WRITE_TAKEN				   0x08
#define hkwd_PTHREAD_RWLOCK_WRITE_MISS				   0x09
#define hkwd_PTHREAD_RWLOCK_TRY_WRITE_TAKEN			   0x0A
#define hkwd_PTHREAD_RWLOCK_TRY_WRITE_MISS			   0x0B
#define hkwd_PTHREAD_RWLOCK_READ_TAKEN				   0x0C
#define hkwd_PTHREAD_RWLOCK_READ_MISS				   0x0D
#define hkwd_PTHREAD_RWLOCK_TRY_READ_TAKEN			   0x0E
#define hkwd_PTHREAD_RWLOCK_TRY_READ_MISS			   0x0F

/*
 * Posix Real Time Spinlocks
 * HKWD_PTHREAD_SPINLOCK subhooks
 */
#define hkwd_PTHREAD_SPINLOCK_INIT                                 0x01
#define hkwd_PTHREAD_SPINLOCK_DESTROY                              0x02
#define hkwd_PTHREAD_SPINLOCK_LOCK                                 0x03
#define hkwd_PTHREAD_SPINLOCK_TRYLOCK                              0x04
#define hkwd_PTHREAD_SPINLOCK_UNLOCK                               0x05

/*
 * Posix Real Time barriers
 * HKWD_PTHREAD_BARRIER subhooks
 */

#define hkwd_PTHREAD_BARRIER_INIT                                  0x01
#define hkwd_PTHREAD_BARRIER_DESTROY                               0x02
#define hkwd_PTHREAD_BARRIER_WAIT                                  0x03

/*	HKWD_PTHREAD_GENERAL subhooks.	*/
#define hkwd_PTHREAD_GEN_CREATE_ENTRY				   0x01
#define hkwd_PTHREAD_GEN_CREATE_EXIT_LOCAL			   0x02
#define hkwd_PTHREAD_GEN_CREATE_EXIT_GLOBAL			   0x03
#define hkwd_PTHREAD_GEN_EXIT						   0x04
#define hkwd_PTHREAD_GEN_KILL_ENTRY					   0x05
#define hkwd_PTHREAD_GEN_KILL_EXIT					   0x06
#define hkwd_PTHREAD_GEN_JOIN_ENTRY					   0x07
#define hkwd_PTHREAD_GEN_JOIN_EXIT					   0x08
#define hkwd_PTHREAD_GEN_DETACH_ENTRY				   0x09
#define hkwd_PTHREAD_GEN_DETACH_EXIT				   0x0A
#define hkwd_PTHREAD_GEN_CANCEL_ENTRY				   0x0B
#define hkwd_PTHREAD_GEN_CANCEL_EXIT				   0x0C
#define hkwd_PTHREAD_GEN_DISPATCH_ENTRY				   0x0D
#define hkwd_PTHREAD_GEN_DISPATCH_EXIT				   0x0E
#define hkwd_PTHREAD_GEN_ALLOCINITPTHREAD_ENTRY				0x0F
#define hkwd_PTHREAD_GEN_ALLOCINITPTHREAD_EXIT_GLOBAL			0x10
#define hkwd_PTHREAD_GEN_ALLOCINITPTHREAD_EXIT_LOCAL			0x11
#define hkwd_PTHREAD_GEN_SETSCHEDPRIO			                0x12

/* libc malloc trace hooks */
#define HKWD_LIBC_MALL_SUBSYSTEM                            0x60A00000

/* STAGE 0 */
#define hkwd_LIBC_MALL_MALLOC_COMMON_SIZE_ZERO              0x00
#define hkwd_LIBC_MALL_FREE_COMMON_NULL_PTR                 0x01
#define hkwd_LIBC_MALL_FREE_COMMON_OUT_OF_RANGE_PTR         0x02
#define hkwd_LIBC_MALL_FREE_COMMON_MEMALIGN_SUCCESS         0x03
#define hkwd_LIBC_MALL_FREE_COMMON_MEMALIGN_FAILURE         0x04
#define hkwd_LIBC_MALL_REALLOC_COMMON_NULL_PTR              0x05
#define hkwd_LIBC_MALL_REALLOC_COMMON_SIZE_ZERO             0x06
#define hkwd_LIBC_MALL_REALLOC_COMMON_OUT_OF_RANGE_PTR      0x07
#define hkwd_LIBC_MALL_REALLOC_COMMON_MEMALIGN_FAILED       0x08
#define hkwd_LIBC_MALL_REALLOC_COMMON_MEMALIGN_SUCCESS      0x09
#define hkwd_LIBC_MALL_MEMALIGN_COMMON_SIZE_ZERO            0x0A
#define hkwd_LIBC_MALL_MEMALIGN_COMMON_ALIGN_ERROR          0x0B
#define hkwd_LIBC_MALL_MEMALIGN_COMMON_ENOMEM               0x0C
#define hkwd_LIBC_MALL_MEMALIGN_COMMON_SUCCESS              0x0D

/* STAGE 1 */
#define hkwd_LIBC_MALL_MALLOC_CATCH_OVERFLOW_ENOMEM         0x10
#define hkwd_LIBC_MALL_MALLOC_CATCH_OVERFLOW_SUCCESS        0x11
#define hkwd_LIBC_MALL_FREE_CATCH_OVERFLOW_SUCCESS          0x12
#define hkwd_LIBC_MALL_REALLOC_CATCH_OVERFLOW_SUCCESS       0x13
#define hkwd_LIBC_MALL_REALLOC_CATCH_OVERFLOW_ENOMEM        0x14

/* STAGE 2 */
#define hkwd_LIBC_MALL_MALLOC_THREADCACHE_SUCCESS           0x20
#define hkwd_LIBC_MALL_FREE_THREADCACHE_SUCCESS             0x21

/* STAGE 3 */
#define hkwd_LIBC_MALL_MALLOC_HEAPCACHE_SUCCESS             0x20
#define hkwd_LIBC_MALL_FREE_HEAPCACHE_SUCCESS               0x21

/* STAGE 4 */
#define hkwd_LIBC_MALL_MALLOC_BUCKETS_SUCCESS_FREELIST      0x40
#define hkwd_LIBC_MALL_MALLOC_BUCKETS_SUCCESS_BUCKET        0x41
#define hkwd_LIBC_MALL_FREE_BUCKETS_SUCCESS                 0x43
#define hkwd_LIBC_MALL_FREE_BUCKETS_PREFIX_CORRUPTED        0x44
#define hkwd_LIBC_MALL_REALLOC_BUCKETS_SUCCESS              0x46
#define hkwd_LIBC_MALL_REALLOC_BUCKETS_PREFIX_CORRUPTED     0x47
#define hkwd_LIBC_MALL_MALLOC_NEWBUCKETS                    0x48
#define hkwd_LIBC_MALL_FREE_NEWBUCKETS                      0x49
#define hkwd_LIBC_MALL_REALLOC_NEWBUCKETS                   0x4A

/* STAGE 5 */
#define hkwd_LIBC_MALL_MALLOC_Y_SUCCESS                     0x50
#define hkwd_LIBC_MALL_MALLOC_Y_ENOMEM                      0x51
#define hkwd_LIBC_MALL_FREE_Y_SUCCESS                       0x52
#define hkwd_LIBC_MALL_FREE_Y_UNALIGNED                     0x54
#define hkwd_LIBC_MALL_FREE_Y_PREFIX_CORRUPTED              0x55
#define hkwd_LIBC_MALL_FREE_Y_INVALID_OVERLAP               0x56
#define hkwd_LIBC_MALL_REALLOC_Y_SUCCESS                    0x57
#define hkwd_LIBC_MALL_REALLOC_Y_ENOMEM                     0x58
#define hkwd_LIBC_MALL_REALLOC_Y_UNALIGNED                  0x5A
#define hkwd_LIBC_MALL_REALLOC_Y_PREFIX_CORRUPTED           0x5B

#define hkwd_LIBC_MALL_MALLOC_W_SUCCESS                     0x60
#define hkwd_LIBC_MALL_MALLOC_W_ENOMEM                      0x61
#define hkwd_LIBC_MALL_FREE_W_SUCCESS                       0x63
#define hkwd_LIBC_MALL_FREE_W_UNALIGNED                     0x64
#define hkwd_LIBC_MALL_FREE_W_PREFIX_CORRUPTED              0x65
#define hkwd_LIBC_MALL_FREE_W_INVALID_OVERLAP               0x66
#define hkwd_LIBC_MALL_REALLOC_W_SUCCESS                    0x68
#define hkwd_LIBC_MALL_REALLOC_W_ENOMEM                     0x69
#define hkwd_LIBC_MALL_REALLOC_W_UNALIGNED                  0x6A
#define hkwd_LIBC_MALL_REALLOC_W_PREFIX_CORRUPTED           0x6B

#define hkwd_LIBC_MALL_MALLOC_31                            0x70
#define hkwd_LIBC_MALL_MALLOC_31_ENOMEM                     0x71 
#define hkwd_LIBC_MALL_FREE_31                              0x72
#define hkwd_LIBC_MALL_FREE_31_PREFIX_CORRUPTED             0x73
#define hkwd_LIBC_MALL_REALLOC_31                           0x74
#define hkwd_LIBC_MALL_REALLOC_31_ENOMEM                    0x75

#define hkwd_LIBC_MALL_MALLOC_USER                          0x80
#define hkwd_LIBC_MALL_FREE_USER                            0x81
#define hkwd_LIBC_MALL_REALLOC_USER                         0x82

#define HKWD_LIBC_MALL_INTERNAL                             0x60B00000

/* STAGE 2 */
#define hkwd_LIBC_MALL_MALLOC_THREADCACHE_CREATE_FAILED     0x20
#define hkwd_LIBC_MALL_MALLOC_THREADCACHE_FILL_FAILED       0x21
#define hkwd_LIBC_MALL_MALLOC_THREADCACHE_FILL_SUCCESS      0x22
#define hkwd_LIBC_MALL_FREE_THREADCACHE_HALVE_BUCKET        0x24
#define hkwd_LIBC_MALL_FREE_THREADCACHE_NOCACHE             0x25

/* libc spawn hooks */
#define HKWD_LIBC_SPAWN_FATHER                              0x60E00000
#define HKWD_LIBC_SPAWN_CHILD                               0x60F00000


#define HKWD_POLLCACHE		0x52600000	   /* poll cache */

/* subhook ids */
#define hkwd_PC_PENDING			1
#define hkwd_PC_REMOVE_PEND		2
#define hkwd_PC_PUSH_PEND		3
#define hkwd_PC_TIME_OUT		4
#define hkwd_PC_WAIT_START		5
#define hkwd_PC_WAIT_STOP		6
#define hkwd_PC_CLEANUP_FD		7
#define hkwd_PC_POLL			8
#define hkwd_PC_CLOSE			9
#define hkwd_PC_REGISTER		10
#define hkwd_PC_UNREGISTER		11
#define hkwd_PC_INIT			12
#define hkwd_PC_RELEASE			13
#define hkwd_PC_CACHE_ADD		14
#define hkwd_PC_CLEANUP			15
#define hkwd_PC_DEQUEUE_PEND		16
#define hkwd_PC_ENQUEUE_PEND		17
#define hkwd_PC_WAIT2_START		18
#define hkwd_PC_WAIT2_STOP		19


/* loader trace hooks */
#define HKWD_LDR                	0x5A000000
#define hkwd_LDR_LOAD_FILE		0x01
#define hkwd_LDR_LOAD_LIBPATH		0x02
#define hkwd_LDR_LOADMODULE_COUNT	0x03
#define hkwd_LDR_PURGE			0x20
#define hkwd_LDR_UNLOADMODULE_COUNT	0x30
#define hkwd_LDR_LIB_LIBPATH_PRE	0x50
#define hkwd_LDR_LIB_LIBPATH		0x51
#define hkwd_LDR_LIB_LIB		0x52	
#define hkwd_LDR_GET_DOMAIN             0x70
#define hkwd_LDR_CLEAN_DOMAIN_ENTRY     0x71
#define hkwd_LDR_UNLOAD_DOMAIN          0x72
#define hkwd_LDR_LD_UNLOAD_LE_FILE	0x80
#define hkwd_LDR_LD_UNLOAD_LE_ADDR      0x81
#define hkwd_LDR_LIBGETTEXT_LOADLIST	0x152
#define hkwd_LDR_LIBGETTEXT_LOADLIST_LE	0x153
#define hkwd_LDR_LIBLD_LOADLIST		0x154
#define hkwd_LDR_LIBLD_LOADLIST_LE	0x155
#define hkwd_LDR_SROINST_LOADLIST	0x156
#define hkwd_LDR_SROINST_LOADLIST_LE	0x157
#define hkwd_LDR_INSTANCE_LOADLIST	0x158
#define hkwd_LDR_INSTANCE_LOADLIST_LE	0x159

#define HKWD_LDR_KMOD           	0x5A100000
#define hkwd_LDR_KMOD_LOAD_FILE		0x01
#define hkwd_LDR_KMOD_LOAD_LIBPATH	0x02
#define hkwd_LDR_KMOD_UNLOAD_FILE	0x03
#define hkwd_LDR_KMOD_LOAD_COUNT	0x04
#define hkwd_LDR_KMOD_UNLOAD_COUNT	0x05

#define HKWD_LDR_PROC           	0x5A200000
#define hkwd_LDR_PROC_FILE		0x01
#define hkwd_LDR_PROC_PID		0x02
#define hkwd_LDR_PROC_SID		0x03
#define hkwd_LDR_PROC_LOAD		0x04
#define hkwd_LDR_PROC_UNLOAD		0x05

#define HKWD_LDR_ERR            	0x5A300000
#define hkwd_LDR_ERR_LD_MOD		0x01
#define hkwd_LDR_ERR_KMOD_LOAD		0x02
#define hkwd_LDR_ERR_KMOD_UNLOAD	0x03
#define hkwd_LDR_ERR_EXECLOAD		0x04
#define hkwd_LDR_ERR_GET_DOMAIN		0x05
#define hkwd_LDR_ERR_RESOLVE_EBUF	0x06
#define hkwd_LDR_ERR_RESOLVE_REASON	0x07
#define hkwd_LDR_ERR_RELOCATE		0x08

#define HKWD_LDR_CHKPT			0x5A400000
#define hkwd_LDR_CHKPT_SID_32		0x01
#define hkwd_LDR_CHKPT_SID_64_TEXT	0x02
#define hkwd_LDR_CHKPT_SID_64_DATA	0x03
#define hkwd_LDR_CHKPT_LE_ADDR		0x04

#define HKWD_LDR_NAMEDSHLIB		0x5A500000
#define hkwd_LDR_NAMEDSHLIB_CREATE	0x01
#define hkwd_LDR_NAMEDSHLIB_DESTROY	0x02

/* trace hooks for MPIO path control modules */
#define HKWD_DD_PCMKE                   0x17B00000

/* POSIX Realtime clock */
#define HKWD_SYSC_RTCLOCK               0x5AA00000	
#define hkwd_SYSC_RTCLOCK_GETRES        0x01
#define hkwd_SYSC_RTCLOCK_GETTIME       0x02    
#define hkwd_SYSC_RTCLOCK_SETTIME       0x03
#define hkwd_SYSC_RTCLOCK_CPUCLOCKID    0x04
#define hkwd_SYSC_RTCLOCK_NANOSLEEP     0x05
#define hkwd_RTCLOCK_NANOSLEEP_END      0x06

/* POSIX Realtime timer */	
#define HKWD_SYSC_RTTIMER               0x5AB00000	
#define hkwd_SYSC_RTTIMER_CREATE        0x01
#define hkwd_SYSC_RTTIMER_DELETE        0x02
#define hkwd_SYSC_RTTIMER_GETOVERRUN    0x03
#define hkwd_SYSC_RTTIMER_GETTIME       0x04
#define hkwd_SYSC_RTTIMER_SETTIME       0x05
#define hkwd_RTTIMER_TRB_INTRVL_END     0x06
#define hkwd_RTTIMER_CPUTMR_INTRVL_END  0x07

/* Posix Realtime semaphores */
#define HKWD_SYSC_RTSEM                0x5B500000
#define hkwd_SYSC_RTSEM_OPEN           0x01
#define hkwd_SYSC_RTSEM_CLOSE          0x02
#define hkwd_SYSC_RTSEM_UNLINK         0x03
#define hkwd_SYSC_RTSEM_INIT           0x04
#define hkwd_SYSC_RTSEM_DESTROY        0x05
#define hkwd_SYSC_RTSEM_GETVALUE       0x06
#define hkwd_SYSC_RTSEM_POST           0x07
#define hkwd_SYSC_RTSEM_WAIT           0x08
#define hkwd_RTSEM_CREATE              0x09
#define hkwd_RTSEM_GET                 0x0A
#define hkwd_RTSEM_REMOVE              0x0B
#define hkwd_RTSEM_CLOSEDES            0x0C
/* Posix Real time message queues */ 
#define HKWD_SYSC_RTMQ                 0x5B600000 
#define hkwd_SYSC_RTMQ_OPEN            0x01 
#define hkwd_SYSC_RTMQ_CLOSE           0x02 
#define hkwd_SYSC_RTMQ_UNLINK          0x03 
#define hkwd_SYSC_RTMQ_GETATTR         0x04 
#define hkwd_SYSC_RTMQ_SETATTR         0x05 
#define hkwd_SYSC_RTMQ_NOTIFY          0x06 
#define hkwd_SYSC_RTMQ_SEND            0x07
#define hkwd_SYSC_RTMQ_RECEIVE         0x08 
#define hkwd_RTMQ_CREATE               0x09
#define hkwd_RTMQ_GET                  0x0A
#define hkwd_RTMQ_REMOVE               0x0B
#define hkwd_RTMQ_CLOSEDES             0x0C
/* Posix Real time shared memory */ 
#define HKWD_SYSC_RTSHM                0x5B700000 
#define hkwd_SYSC_RTSHM_OPEN           0x01 
#define hkwd_SYSC_RTSHM_UNLINK         0x02
#define hkwd_RTSHM_CREATE              0x03
#define hkwd_RTSHM_GET                 0x04
#define hkwd_RTSHM_REMOVE              0x05
#define hkwd_RTSHM_CLOSEDES            0x06
/* Posix Real time ipc name */
#define HKWD_RTIPC_NAME                0x5B800000
/* Posix Real time thread priority scheduling */
#define HKWD_SYSC_PRIO_REQUEUE         0x5AC00000
/* Posix Real time priority scheduling */
#define HKWD_SYSC_PRIO_SCHED             0x5AD00000
#define hkwd_PRIO_SCHED_GET_PRIORITY_MIN 0x01
#define hkwd_PRIO_SCHED_GET_PRIORITY_MAX 0x02
#define hkwd_PRIO_SCHED_RR_GET_INTERVAL  0x03
#define hkwd_PRIO_SCHED_SETPARAM         0x04
#define hkwd_PRIO_SCHED_SETSCHEDULER     0x05
#define hkwd_PRIO_SCHED_GETPARAM         0x06
#define hkwd_PRIO_SCHED_GETSCHEDULER     0x07


#define HKWD_NETWLM                             0x5B900000
#define hkwd_netwlm_connect_in                  1
#define hkwd_netwlm_connect_out                 2
#define hkwd_netwlm_connect_out_not_auth        3
#define hkwd_netwlm_connect_out_limit1_conn     4
#define hkwd_netwlm_connect_out_bad_version     5
#define hkwd_netwlm_disconnect_in               6
#define hkwd_netwlm_disconnect_out              7
#define hkwd_netwlm_disconnect_out_bad_version  8
#define hkwd_netwlm_disconnect_out_buffer_small 9
#define hkwd_netwlm_query_in                    10
#define hkwd_netwlm_query_out                   11
#define hkwd_netwlm_query_out_bad_request       12
#define hkwd_netwlm_set_ipaddrports_in          13
#define hkwd_netwlm_set_ipaddrports_out         14
#define hkwd_netwlm_set_ipaddrports_out_bad_version        15
#define hkwd_netwlm_get_ipaddrportsPID_in       16
#define hkwd_netwlm_get_ipaddrportsPID_out      17
#define hkwd_netwlm_proc_table_lookup_in        18
#define hkwd_netwlm_proc_table_lookup_out       19
#define hkwd_netwlm_fd_lookup_in                20
#define hkwd_netwlm_fd_lookup_out               21
#define hkwd_netwlm_get_proctable_lookup_in     22
#define hkwd_netwlm_get_proctable_lookup_out    23
#define hkwd_netwlm_get_verify_pid_in           24
#define hkwd_netwlm_get_verify_pid_out          25
#define hkwd_netwlm_get_fdlookup_in             26
#define hkwd_netwlm_get_fdlookup_out1           27
#define hkwd_netwlm_get_fdlookup_out2           28
#define hkwd_netwlm_get_fdlookup_out3           29
#define hkwd_netwlm_postbind_save_pid_in        30
#define hkwd_netwlm_postbind_save_pid_out       31
#define hkwd_netwlm_add_pid_in                  32
#define hkwd_netwlm_add_pid_out                 33
#define hkwd_netwlm_del_pid_in                  34
#define hkwd_netwlm_del_pid_out                 35
#define hkwd_netwlm_get_fdlookup_data1		36

/* trace hooks for memory locking routine */
#define HKWD_SYSC_MLOCK                 0x47B00000
#define hkwd_SYSC_MLOCK_LOCKALL         0x01
#define hkwd_SYSC_MLOCK_UNLOCKALL       0x02
#define hkwd_SYSC_MLOCK_LOCK            0x03
#define hkwd_SYSC_MLOCK_UNLOCK          0x04
#define hkwd_SYSC_MLOCK_FPGIN           0x05

/*
 * ACL Engine  hook and sub-hook ids
 */    
#define HKWD_ACLE                       0x47800000  
#define hkwd_ACLE_SET_ACL_ENTRY         0x01
#define hkwd_ACLE_SET_ACL_EXIT          0x02
#define hkwd_ACLE_VALIDATE_ACL          0x03
#define hkwd_ACLE_CHK_ACCESS_ENTRY      0x04
#define hkwd_ACLE_CHK_RWX               0x05
#define hkwd_ACLE_CHK_RWX_PRIVCHECK     0x06
#define hkwd_ACLE_CHK_MASKS             0x07
#define hkwd_ACLE_CHK_MASKS_PRIVCHECK   0x08
#define hkwd_ACLE_CHK_ONLY_PRIVCHECK    0x09
#define hkwd_ACLE_CHK_ACCESS_EXIT       0x0A
#define hkwd_ACLE_GET_ACL_ENTRY         0x0B
#define hkwd_ACLE_GET_ACL_EXIT          0x0C
#define hkwd_ACLE_GET_CHILD_ACL_ENTRY   0x0D
#define hkwd_ACLE_GET_CHILD_ACL_EXIT    0x0E

/*
 * Hypervisor Call hook and sub-hook ids
 */
#define HKWD_KERN_HCALL			0x49200000
#define hkwd_KERN_HCALL_START		1
#define hkwd_KERN_HCALL_END		2

/* Special defines for H_CEDE */
#define hkwd_KERN_HCEDE_START		1
#define hkwd_KERN_HCEDE_END_DC		2	/* Dispatch count changed */
#define hkwd_KERN_HCEDE_END_JOB		3	/* New job available	  */

/*
 * Advanced Accounting Trace Hooks.
 */
#define HKWD_AACCT			0x49A00000 /* AACCT - no _aacct_put */
#define HKWD_AACCT_DBG			0x49B00000 /* AACCT - _acct_put() */

/* subhook ids */

#define hkwd_AACCT_DR_HANDLER		1
#define hkwd_AACCT_INT_REGISTER		2
#define hkwd_AACCT_INT_REGISTER_EXIT	3
#define hkwd_AACCT_INT_UNREGISTER	4
#define hkwd_AACCT_INT_WALK		5
#define hkwd_AACCT_CMD_INT		6
#define hkwd_AACCT_CMD_ENABLE		7
#define hkwd_AACCT_CMD_DISABLE		8	

#define	hkwd_AACCT_REQ			9

#define hkwd_AACCT_STARTED		10
#define hkwd_AACCT_STOPPED		11
#define hkwd_AACCT_ADD_FILE		12
#define hkwd_AACCT_RM_FILE		13
#define hkwd_AACCT_SWITCH_FILE		14
#define hkwd_AACCT_ACK_FILE		15

#define hkwd_AACCT_TRID_DEFINED		16
#define hkwd_AACCT_TRID_ENABLED		17
#define hkwd_AACCT_TRID_DISABLED	18

#define hkwd_AACCT_ACF_FULL		19
#define hkwd_AACCT_ACF_TERMINATE	20
#define hkwd_AACCT_ACF_NOBUFS		21
#define hkwd_AACCT_ACF_NOFILES		22
#define hkwd_AACCT_ACF_WARN		23

#define hkwd_AACCT_SYSINT_SET		24
#define hkwd_AACCT_SYSINT_RESET		25
#define hkwd_AACCT_PROCINT_SET		26
#define hkwd_AACCT_PROCINT_RESET	27

#define hkwd_AACCT_AGGR_SET		28
#define hkwd_AACCT_AGGR_RESET		29


/* subhookid for HK_AACCT_DBG	*/

#define hkwd_AACCT_ACCTPUT		1
#define hkwd_AACCT_AGGR_PROC		2
#define hkwd_AACCT_AGGR_APP		3
#define hkwd_AACCT_AGGR_KE		4

/*
 * HOOK for RAS Error Checking service.
 */
#define HKWD_ERRHK			0x4AE00000 /* raschk_errhook() */

/*
 * PCI Bus Driver's Hookwords.
 */
#define HKWD_KERN_EEH			0x49C00000  /* EEH Kernel Services */
#define HKWD_KERN_DMA			0x49D00000  /* DMA Kernel Services */

/* PAL Driver's Hookwords. */
#define HKWD_RTAS_CALLS			0x5BC00000  /* RTAS call services  */

/* subhookids for HKWD_KERN_EEH */
#define EEH_INIT_ENTER			0x01
#define EEH_INIT_EXIT			0x0F
#define EEH_INIT_MULTIFUNC_ENTER	0x11
#define EEH_INIT_MULTIFUNC_EXIT		0x1F
#define EEH_CLEAR_ENTER			0x21
#define EEH_CLEAR_EXIT			0x2F
#define EEH_READ_SLOT_STATE1		0x34
#define EEH_READ_SLOT_STATE2		0x37
#define EEH_READ_SLOT_STATE_EXIT	0x3F
#define EEH_RESET_SLOT_ENTER		0x41
#define EEH_RESET_SLOT_RTAS		0x45
#define EEH_RESET_SLOT_EXIT		0x4F
#define EEH_ENABLE_SLOT_ENTER		0x51
#define EEH_ENABLE_SLOT_RTAS		0x55
#define EEH_ENABLE_SLOT_EXIT		0x5F
#define EEH_DISABLE_SLOT_ENTER		0x61
#define EEH_DISABLE_SLOT_RTAS		0x65
#define EEH_DISABLE_SLOT_EXIT		0x6F
#define EEH_ENABLE_DMA_ENTER		0x71
#define EEH_ENABLE_DMA_RTAS		0x75
#define EEH_ENABLE_DMA_EXIT		0x7F
#define EEH_ENABLE_PIO_ENTER		0x81
#define EEH_ENABLE_PIO_RTAS		0x85
#define EEH_ENABLE_PIO_EXIT		0x8F
#define EEH_SLOT_ERROR_ENTER		0x91
#define EEH_SLOT_ERROR_RTAS		0x95
#define EEH_SLOT_ERROR_RTAS2		0x97
#define EEH_SLOT_ERROR_EXIT		0x9F
#define EEH_CONFIGURE_BRIDGE_ENTER	0xA1
#define EEH_CONFIGURE_BRIDGE_RTAS	0xA5
#define EEH_CONFIGURE_BRIDGE_EXIT	0xAF
#define EEH_ISSUE_CALLBACKS_ENTER	0xB1
#define EEH_ISSUE_CALLBACKS_ENTER2	0xB2
#define EEH_ISSUE_CALLBACKS_MASTER	0xB5
#define EEH_ISSUE_CALLBACKS_RESTR	0xB6
#define EEH_ISSUE_CALLBACKS_KCALL	0xB8
#define EEH_ISSUE_CALLBACKS_UCALL	0xB9
#define EEH_ISSUE_CALLBACKS_RET		0xBA
#define EEH_ISSUE_CALLBACKS_EXIT	0xBF
#define EEH_CALL_FIRMWARE		0xC1
#define EEH_CONFIGURE_PE_ENTER		0xD1
#define EEH_CONFIGURE_PE_RTAS		0xD5
#define EEH_CONFIGURE_PE_EXIT		0xDF


/*
 * VCM TRACE HOOKS 
 */
#define HKWD_VCM_MAIN  				0x48000000
#define hkwd_vcm_clientRegister_ENTER		0x001
#define hkwd_vcm_clientRegister_ERROR		0x002
#define hkwd_vcm_clientRegister_EXIT		0x003
#define hkwd_vcm_clientUnregister_ENTER		0x004
#define hkwd_vcm_clientUnregister_EXIT		0x005
#define hkwd_vcm_openVFS_ENTER			0x006
#define hkwd_vcm_openVFS_ERROR			0x007
#define hkwd_vcm_openVFS_EXIT			0x008
#define hkwd_vcm_closeVFS_ENTER			0x009
#define hkwd_vcm_closeVFS_EXIT			0x00a
#define hkwd_vcm_getOpRights_ENTER		0x00b
#define hkwd_vcm_getOpRights_ERROR1		0x00c
#define hkwd_vcm_getOpRights_ENTER2		0x00d
#define hkwd_vcm_getOpRights_ERROR2		0x00e
#define hkwd_vcm_getOpRights_EXIT1		0x00f
#define hkwd_vcm_returnOpRights_ENTER		0x010
#define hkwd_vcm_returnOpRights_EXIT		0x011
#define hkwd_vcm_beginCreate_ERROR		0x012
#define hkwd_vcm_beginCreate_ENTER		0x013
#define hkwd_vcm_beginCreate_EXIT2		0x014
#define hkwd_vcm_endCreate_ENTER		0x015
#define hkwd_vcm_endCreate_ERROR		0x016
#define hkwd_vcm_endCreate_EXIT1		0x017
#define hkwd_vcm_endCreate_EXIT2		0x018
#define hkwd_allocLocalObj_EXIT1    		0x019
#define hkwd_getLocalObj_ENTER    		0x01a
#define hkwd_getLocalObj_ERROR1    		0x01b
#define hkwd_getLocalObj_ERROR2    		0x01c
#define hkwd_getLocalObj_FINDLOCAL  		0x01d
#define hkwd_getLocalObj_EXIT  			0x01e
#define hkwd_localObjectRevoke_ENTER		0x01f
#define hkwd_localObjectRevoke_ERROR		0x020
#define hkwd_localObjectRevoke_CONFLICT_OPEN	0x021
#define hkwd_localObjectRevoke_CONFLICT_ACTIVE	0x022
#define hkwd_localObjectRevode_EXIT		0x023
#define hkwd_vcmi_localOpsInit_SIZES		0x024
#define hkwd_vcmi_localOpsInit_CLIENTADD	0x025
#define hkwd_vcm_localOpsGet_ENTER		0x026
#define hkwd_vcm_localOpsGet_ERROR		0x027
#define hkwd_vcm_localOpsGet_EXIT1		0x028
#define hkwd_vcm_localOpsGet_EXIT2		0x029
#define hkwd_vcm_localOpsPut_ENTER		0x02a
#define hkwd_vcm_localOpsPut_EXIT		0x02b
#define hkwd_vcm_localOpsOpen_ENTER		0x02c
#define hkwd_vcm_localOpsOpen_ERROR1		0x02d
#define hkwd_vcm_localOpsOpen_ERROR2		0x02e
#define hkwd_vcm_localOpsOpen_EXIT1		0x02f
#define hkwd_vcm_localOpsOpen_EXIT2		0x030
#define hkwd_vcm_localOpsClose_ENTER		0x031
#define hkwd_vcm_localOpsClose_ERROR1		0x032
#define hkwd_vcm_localOpsClose_ERROR2		0x033
#define hkwd_vcm_localOpsClose_ERROR4		0x035
#define hkwd_vcm_localOpsClose_ERROR5		0x036
#define hkwd_vcm_localOpsClose_ERROR6		0x037
#define hkwd_vcm_localOpsClose_EXIT		0x038
#define hkwd_vcm_localOpsBeginCreate_ENTER	0x039
#define hkwd_vcm_localOpsBeginCreate_NAME	0x03a
#define hkwd_vcm_localOpsBeginCreate_EXIT1	0x03b
#define hkwd_vcm_localOpsBeginCreate_EXIT2	0x03c
#define hkwd_vcm_localOpsEndCreate_ENTER	0x03d
#define hkwd_vcm_localOpsEndCreate_ERROR1	0x03e
#define hkwd_vcm_localOpsEndCreate_ERROR2	0x03f
#define hkwd_vcm_localOpsEndCreate_ERROR3	0x040
#define hkwd_vcm_localOpsEndCreate_ERROR4	0x041
#define hkwd_vcm_localOpsEndCreate_ERROR5	0x042
#define hkwd_vcm_localOpsEndCreate_EXIT1	0x043
#define hkwd_vcm_localOpsEndCreate_EXIT2	0x044
#define hkwd_vcm_init_EXIT_ERROR		0x045
#define hkwd_vcm_vnop_create_ENTER		0x046
#define hkwd_vcm_vnop_create_ERROR1		0x047
#define hkwd_vcm_vnop_create_ERROR2		0x048
#define hkwd_vcm_vnop_create_ERROR3		0x049
#define hkwd_vcm_vnop_create_EXIT		0x04a
#define hkwd_vcm_vnop_open_ERROR		0x04b
#define hkwd_vcm_vnop_create_attr_ENTER		0x04c
#define hkwd_vcm_vnop_create_attr_ERROR1	0x04d
#define hkwd_vcm_vnop_create_attr_ERROR2	0x04e
#define hkwd_vcm_vnop_create_attr_EXIT		0x04f
#define hkwd_chandleToClientRec_ERROR1		0x050
#define hkwd_chandleToClientRec_ERROR2		0x051
#define hkwd_vcmi_clientDelete_ERROR1		0x052
#define hkwd_vcmi_clientRevokeRights_ENTER1	0x053
#define hkwd_vcmi_clientRevokeRights_ENTER2	0x054
#define hkwd_vcmi_clientRevokeRights_EXIT	0x055
#define hkwd_vcmi_clientAddVFSOpen_ERROR1	0x056
#define hkwd_vcmi_clientAddVFSOpen_ERROR2	0x057
#define hkwd_vcmi_clientRemVFSOpen_ERROR1	0x058
#define hkwd_addVFS_ENTER			0x059
#define hkwd_closeVFS_ENTER			0x05a
#define hkwd_vcmi_vfsEndCreate_ERROR1		0x05b
#define hkwd_vcmi_vfsEndCreate_ERROR2		0x05c
#define hkwd_vcmi_vfsAddObjRef_ERROR1		0x05d
#define hkwd_vcmi_vfsAddObjRef_ERROR2		0x05e
#define hkwd_vcmi_vfsDelObjRef_ERROR1		0x05f
#define hkwd_vcmi_vfsDelObjRef_ERROR2		0x060
#define hkwd_vcmi_peerReturnObjHandle_ENTER	0x061
#define hkwd_vcmi_peerReturnObjHandle_EXIT	0x062
#define hkwd_vcmi_peerGetRights_ENTER		0x063
#define hkwd_vcmi_peerGetRights_EXIT1		0x064
#define hkwd_vcmi_peerGetRights_EXIT2		0x065
#define hkwd_vcmi_peerReturnRights_ENTER	0x066
#define hkwd_vcmi_peerReturnRights_EXIT		0x067
#define hkwd_vcmi_peerCreateObject_NAME		0x068
#define hkwd_vcmi_peerCreateObject_ENTER	0x069
#define hkwd_vcmi_peerCreateObject_EXIT		0x06a
#define hkwd_vcmi_peerOpenObject_ENTER		0x06b
#define hkwd_vcmi_peerOpenObject_EXIT		0x06c
#define hkwd_vcm_peerRegister_ENTER		0x06d
#define hkwd_vcm_peerRegister_ERROR1		0x06e
#define hkwd_vcm_peerRegister_EXIT		0x06f
#define hkwd_vcm_peerUnregister_ENTER		0x070
#define hkwd_vcm_peerUnregister_EXIT		0x071
#define hkwd_vcm_peerRevoke_ENTER		0x072
#define hkwd_vcm_peerRevoke_EXIT1		0x073
#define hkwd_removeRights_SUCCESS		0x074
#define hkwd_removeRights_TOPEER		0x075
#define hkwd_checkRevokeResponse_ERROR1		0x076
#define hkwd_checkRevokeResponse_ERROR2		0x077
#define hkwd_checkRevokeResponse_ERROR3		0x078
#define hkwd_checkRevokeResponse_ERROR4		0x079
#define hkwd_checkRevokeResponse_SETSTALE	0x07a
#define hkwd_objectRecGC_RESULTS		0x07b
#define hkwd_getHolder_NEW_HOLDER		0x07d
#define hkwd_getHolder_IS_LOCAL			0x07e
#define hkwd_getObjRec_NEWOBJ			0x07f
#define hkwd_objRecFromOpHandle_ERROR1		0x080
#define hkwd_getPeerRights_ERROR1		0x081
#define hkwd_resolveConflicts_INCREATE		0x082
#define hkwd_vcmi_rightsPeerRevoke_ERROR1	0x083
#define hkwd_vcmi_rightsPeerRevoke_ERROR2	0x084
#define hkwd_vcmi_rightsPeerRevoke_INCREATE	0x085
#define hkwd_vcmi_rightsFlushPeerState_ENTER	0x086
#define hkwd_vcmi_rightsFlushPeerState_EXIT	0x087
#define hkwd_vcmi_rightsGet_ESTALE		0x088
#define hkwd_vcmi_rightsPostCreate_ERROR	0x089
#define hkwd_vcmi_rightsFinishCreate_ERROR1	0x08a
#define hkwd_vcmi_rightsReturn_ERROR1		0x08b
#define hkwd_vcmi_rightsReturn_ERROR2		0x08c
#define hkwd_vcm_getOpRights_EXIT2		0x08d
#define hkwd_vcm_peerRevoke_EXIT2		0x08e
#define hkwd_vcm_beginCreate_EXIT1		0x08f
#define hkwd_localObjectRevoke_ERROR2		0x090
#define hkwd_vcm_localOpsClose_ERROR7		0x091
#define hkwd_objectRecGC_ENTER			0x092
#define hkwd_getHolder_OLD_RTAG			0x093
#define hkwd_vcmi_rightsGet_ENTER		0x094
#define hkwd_vcmi_rightsGet_BAD_RTAG		0x095
#define hkwd_vcmi_rightsGet_EXIT		0x096
#define hkwd_allocObj_ERROR_GCD			0x097
#define hkwd_vcmi_rightsPostCreate_XFER		0x098
#define hkwd_vcmi_rightsPostCreate_XFER_ERROR1	0x099
#define hkwd_vcmi_rightsGet_RESTART 		0x09a
#define hkwd_vcm_localOpsEnableObjRights_EXIT1	0x09b
#define hkwd_vcmi_disableObjectRights_ENTER	0x09c
#define hkwd_vcmi_disableObjectRights_EXIT	0x09d
#define hkwd_vcmi_enableObjectRights_ENTER	0x09e
#define hkwd_vcmi_enableObjectRights_EXIT	0x09f

#define hkwd_vcm_monitorRegister_ENTER		0x0a0
#define hkwd_vcm_monitorRegister_ERROR1		0x0a1
#define hkwd_vcm_monitorRegister_ERROR2		0x0a2
#define hkwd_vcm_monitorRegister_ERROR3		0x0a3
#define hkwd_vcm_monitorRegister_ERROR4		0x0a4
#define hkwd_vcm_monitorRegister_ERROR5		0x0a5
#define hkwd_vcm_monitorRegister_EXIT		0x0a6

#define hkwd_vcm_monitorUnregister_ENTER	0x0a7
#define hkwd_vcm_monitorUnregister_ERROR1	0x0a8
#define hkwd_vcm_monitorUnregister_ERROR2	0x0a9
#define hkwd_vcm_monitorUnregister_EXIT		0x0aa

#define hkwd_vcm_start_vfs_monitor_ENTER	0x0ab
#define hkwd_vcm_start_vfs_monitor_ERROR1	0x0ac
#define hkwd_vcm_start_vfs_monitor_ERROR2	0x0ad
#define hkwd_vcm_start_vfs_monitor_EXIT		0x0ae

#define hkwd_vcm_stop_vfs_monitor_ENTER		0x0af
#define hkwd_vcm_stop_vfs_monitor_ERROR1	0x0b0
#define hkwd_vcm_stop_vfs_monitor_ERROR2	0x0b1
#define hkwd_vcm_stop_vfs_monitor_EXIT		0x0b2

#define hkwd_vcm_monitor_CALLOUT		0x0b3
#define hkwd_vcm_monitor_RETURN			0x0b4


#define HKWD_VCM_DEBUG    			0x48100000
#define hkwd_releaseLocalObj_RETURN1		0x001
#define hkwd_releaseLocalObj_RETURN2		0x002
#define hkwd_releaseLocalObj_EXIT1		0x003
#define hkwd_releaseLocalObj_EXIT2		0x004
#define hkwd_getLocalRights_EXIT		0x005
#define hkwd_vcm_localOpsPut_ERROR		0x006
#define hkwd_findVFS_EXIT			0x007
#define hkwd_remVFS_ENTER			0x008
#define hkwd_vcmi_peerFind_RESULTS		0x009
#define hkwd_vcmi_peerGetObjHandle_ENTER	0x00a
#define hkwd_vcmi_peerGetObjHandle_EXIT1	0x00b
#define hkwd_vcmi_peerGetObjHandle_EXIT2	0x00c
#define hkwd_allocObj_STATS			0x00d
#define hkwd_getLocalRights_ENTER		0x00e
#define hkwd_getLocalRights_EXIT_ERROR		0x00f
#define hkwd_localObjectRevoke_INVALID_ERROR	0x010
#define hkwd_objectRecGC_STATS			0x011
#define hkwd_vcmi_enableObjectRights_freeobj	0x012

/*
 * TopSpin 1X/4X Infiniband Device Driver's Hookwords.
 */
#define HKWD_TSIB			0x4BD00000  /* TSIB DD Specific Library Services */
#define HKWD_TSIB_GENERAL		0x4BE00000  /* TSIB DD General Services */
#define HKWD_TSIB_ERROR			0x4BF00000  /* TSIB DD Error Services */
#define HKWD_TSIB_DEBUG			0x4C000000  /* TSIB DD Debugging Services */

#define HKWD_NET                                0x61500000 
#define hkwd_ras_netinet_callback_err1          1
#define hkwd_ras_netinet_tcp_callback_err1      2
#define hkwd_ras_netinet_udp_callback_err1      3
#define hkwd_ras_netinet_ipv4_callback_err1     4
#define hkwd_ras_netinet_misc_callback_err1     5
#define hkwd_ras_if_en_callback_err1            6
#define hkwd_ras_ethchan_callback_err1          7
#define hkwd_ras_netmalloc_callback_err1        8
#define hkwd_ras_net_callback_err1              9
#define hkwd_ras_net_route_callback_err1        10
#define hkwd_ras_net_cdli_callback_err1         11
#define hkwd_ras_net_loop_callback_err1         12
#define hkwd_ras_mbuf_callback_err1             13
#define hkwd_ras_socket_callback_err1           14
#define hkwd_ras_socket_so_unix_callback_err1   15
#define hkwd_network_ras_unregister_err1        16
#define hkwd_network_ras_register_in		17
#define hkwd_network_ras_register_out		18
#define hkwd_network_ras_register_error1	19
#define hkwd_network_ras_register_error2	20
#define hkwd_network_ras_register_error3	21
#define hkwd_network_ras_register_error4	22
#define hkwd_network_ras_register_error5	23
#define hkwd_network_ras_register_error6	24
#define hkwd_network_ras_register_error7	25
#define hkwd_network_ras_register_error8	26
#define hkwd_network_ras_register_error9	27
#define hkwd_network_ras_unregister_in		28
#define hkwd_network_ras_unregister_out		29
#define hkwd_ras_callback_common_in		30	
#define hkwd_ras_callback_common_out		31	
#define hkwd_ras_callback_common_error1		32	
#define hkwd_ras_callback_common_error2		33	
#define hkwd_ras_callback_common_error3		34	
#define hkwd_ras_callback_common_error4		35	
#define hkwd_ras_callback_common_error5		36	
#define hkwd_ras_callback_common_error6		37	
#define hkwd_ras_callback_common_error7		38	
#define hkwd_ras_callback_common_error8		39	
#define hkwd_ras_callback_common_error9		40	
#define hkwd_ras_callback_common_error10	41	
#define hkwd_ras_callback_common_error11	42	
#define hkwd_ras_callback_common_error12	43	
#define hkwd_ras_callback_common_error13	44	
#define hkwd_ras_callback_common_error14	45	
#define hkwd_ras_netinet_callback_in		46
#define hkwd_ras_netinet_callback_out		47
#define hkwd_ras_netinet_tcp_callback_in	48
#define hkwd_ras_netinet_tcp_callback_out	49
#define hkwd_ras_netinet_udp_callback_in	50
#define hkwd_ras_netinet_udp_callback_out	51
#define hkwd_ras_netinet_ipv4_callback_in	52
#define hkwd_ras_netinet_ipv4_callback_out	53
#define hkwd_ras_netinet_misc_callback_in	54
#define hkwd_ras_netinet_misc_callback_out	55
#define hkwd_ras_if_en_callback_in		56
#define hkwd_ras_if_en_callback_out		57
#define hkwd_ras_ethchan_callback_in		58
#define hkwd_ras_ethchan_callback_out		59
#define hkwd_ras_netmalloc_callback_in		60
#define hkwd_ras_netmalloc_callback_out		61
#define hkwd_ras_net_callback_in		62
#define hkwd_ras_net_callback_out		63
#define hkwd_ras_net_route_callback_in		64
#define hkwd_ras_net_route_callback_out		65
#define hkwd_ras_net_cdli_callback_in		66
#define hkwd_ras_net_cdli_callback_out		67
#define hkwd_ras_net_loop_callback_in		68
#define hkwd_ras_net_loop_callback_out		69
#define hkwd_ras_mbuf_callback_in		70
#define hkwd_ras_mbuf_callback_out		71
#define hkwd_ras_socket_callback_in		72
#define hkwd_ras_socket_callback_out		73
#define hkwd_ras_socket_so_unix_callback_in	74
#define hkwd_ras_socket_so_unix_callback_out	75
#define hkwd_ras_callback_common_error15	76	
#define hkwd_ras_callback_common_error16	77	
#define hkwd_ras_callback_common_error17	78	
#define hkwd_ras_vasi_callback_in		79
#define hkwd_ras_vasi_callback_err1		80
#define hkwd_ras_vasi_callback_out		81
#define hkwd_ras_mover_callback_err1     	82
#define hkwd_ras_mover_callback_in       	83
#define hkwd_ras_mover_callback_out      	84
#define hkwd_ras_sea_callback_in    		85 
#define hkwd_ras_sea_callback_err1    		86
#define hkwd_ras_sea_callback_out    		87
#define hkwd_ras_seaha_callback_in    		88
#define hkwd_ras_seaha_callback_err1   		89
#define hkwd_ras_seaha_callback_out    		90
#define hkwd_ras_sea_gvrp_callback_in    	91
#define hkwd_ras_sea_gvrp_callback_err1   	92
#define hkwd_ras_sea_gvrp_callback_out   	93


#define HKWD_ROUTE                      0x61700000
#define hkwd_rtinithead_in              1
#define hkwd_route_configure_in         2
#define hkwd_route_init_in              3
#define hkwd_rn_inithead_in             4
#define hkwd_rn_inithead_err1           5
#define hkwd_rn_init_in                 6
#define hkwd_rtredirect_in              7
#define hkwd_rtexpire_in                8
#define hkwd_rtexpire_out               9
#define hkwd_rtioctl_in                 10
#define hkwd_rtioctl_out                11
#define hkwd_dead_gateway               12
#define hkwd_gateway_up                 13
#define hkwd_raise_cost_1               14
#define hkwd_raise_cost_2               15
#define hkwd_restore_cost_1             16
#define hkwd_restore_cost_2             17
#define hkwd_rn_change_cost_in          18
#define hkwd_rn_change_cost_out         19
#define hkwd_rn_change_cost_out1        20
#define hkwd_rn_change_cost_out2        21
#define hkwd_rn_change_cost_out3        22
#define hkwd_rt_changegids_in           23
#define hkwd_rt_changegids_out          24
#define hkwd_rt_changegids_out1         25
#define hkwd_rt_changegids_err1         26
#define hkwd_rt_changegids_err2         27
#define hkwd_rt_changegids_err3         28
#define hkwd_route_output_in            29
#define hkwd_route_output_out           30
#define hkwd_route_output_err1          31
#define hkwd_route_output_err2          32
#define hkwd_route_output_err3          33
#define hkwd_route_output_err4          34
#define hkwd_route_output_err5          35
#define hkwd_route_output_err6          36
#define hkwd_route_output_err7          37
#define hkwd_route_output_err8          38
#define hkwd_route_output_err9          39
#define hkwd_route_output_err10         40
#define hkwd_route_output_err11         41
#define hkwd_route_output_err12         42
#define hkwd_route_output_err13         43
#define hkwd_route_output_err14         44
#define hkwd_route_output_err15         45
#define hkwd_route_output_err16         46
#define hkwd_route_output_err17         47
#define hkwd_route_output_err18         48
#define hkwd_route_output_err19         49
#define hkwd_route_output_err20         50
#define hkwd_route_output_err21         51
#define hkwd_route_output_err22         52
#define hkwd_route_output_err23         53
#define hkwd_route_output_err24         54
#define hkwd_route_output_err25         55
#define hkwd_route_output_err26         56
#define hkwd_route_output_err27         57
#define hkwd_route_output_err28         58
#define hkwd_route_output_err29         59
#define hkwd_route_output_err30         60
#define hkwd_rt_missmsg_in              61
#define hkwd_rt_missmsg_out1            62
#define hkwd_rt_missmsg_out2            63
#define hkwd_rn_select_in               64
#define hkwd_rn_select_out              65
#define hkwd_rn_select_out1             66
#define hkwd_rn_select_out2             67
#define hkwd_rn_lookup_in               68
#define hkwd_rn_lookup_out              69
#define hkwd_rn_lookup_out1             70
#define hkwd_rn_lookup_out2             71
#define hkwd_rn_lookup_out3             72
#define hkwd_rn_lookup_out4             73
#define hkwd_rn_genmatch_in             74
#define hkwd_rn_genmatch_out            75
#define hkwd_rn_genmatch_out1           76
#define hkwd_rn_genmatch_out2           77
#define hkwd_rn_genmatch_out3           78
#define hkwd_rn_genmatch_out4           79
#define hkwd_rn_genmatch_out5           80
#define hkwd_rn_genmatch_out6           81
#define hkwd_rn_addmask_err1            82
#define hkwd_rn_new_radix_mask_err1     83
#define hkwd_rn_addroute_in             84
#define hkwd_rn_addroute_out            85
#define hkwd_rn_addroute_out1           86
#define hkwd_rn_addroute_out2           87
#define hkwd_rn_addroute_out3           88
#define hkwd_rn_addroute_out4           89
#define hkwd_rn_addroute_out5           90
#define hkwd_rn_delete_in               91
#define hkwd_rn_delete_out              92
#define hkwd_rn_delete_out1             93
#define hkwd_rn_delete_out2             94
#define hkwd_rn_delete_out3             95
#define hkwd_rn_delete_out4             96
#define hkwd_rn_delete_out5             97
#define hkwd_rn_delete_out6             98
#define hkwd_rn_delete_out7             99
#define hkwd_rn_change_in               100
#define hkwd_rn_change_out              101
#define hkwd_rn_change_out1             102
#define hkwd_rn_change_out2             103
#define hkwd_rn_change_out3             104
#define hkwd_rn_change_out4             105
#define hkwd_rn_change_out5             106
#define hkwd_rn_walktree_in             107
#define hkwd_rn_walktree_out            108
#define hkwd_rn_walktree_out1           109
#define hkwd_rn_walktree_err1           110
#define hkwd_rn_walktree_err2           111
#define hkwd_rn_change_policy_in        112
#define hkwd_rn_change_policy_out       113
#define hkwd_rn_change_policy_out1      114
#define hkwd_rn_change_policy_out2      115
#define hkwd_rn_change_policy_out3      116
#define hkwd_rn_change_policy_out4      117
#define hkwd_rn_change_policy_out5      118
#define hkwd_rn_change_policy_out6      119
#define hkwd_rn_change_policy_out7      120
#define hkwd_nextroute_in               121
#define hkwd_nextroute_out              122
#define hkwd_nextroute_out1             123
#define hkwd_nextroute_out2             124
#define hkwd_rtalloc1_nolock_gr_in      125
#define hkwd_rtalloc1_nolock_gr_out     126
#define hkwd_rtalloc1_nolock_gr_err1    129
#define hkwd_rtalloc1_nolock_gr_err2    130
#define hkwd_rtalloc1_nolock_gr_err3    131
#define hkwd_rtfree_nolock_out1         132
#define hkwd_rtfree_nolock_out2         133
#define hkwd_rtredirect_err1            134
#define hkwd_rtredirect_err2            135
#define hkwd_rtredirect_err3            136
#define hkwd_rtredirect_err4            137
#define hkwd_rtioctl_err1               138
#define hkwd_rtioctl_err2               139
#define hkwd_rtioctl_err3               140
#define hkwd_ifa_ifwithroute_err1       141
#define hkwd_ifa_ifwithroute_err2       142
#define hkwd_ifa_ifwithroute_err3       143
#define hkwd_rtrequest_nolock_in        144
#define hkwd_rtrequest_nolock_out       145
#define hkwd_rtrequest_nolock_err1      146
#define hkwd_rtrequest_nolock_err2      147
#define hkwd_rtrequest_nolock_err3      148
#define hkwd_rtrequest_nolock_err4      149
#define hkwd_rtrequest_nolock_err5      150
#define hkwd_rtrequest_nolock_err6      151
#define hkwd_rtrequest_nolock_err7      152
#define hkwd_rtrequest_nolock_err8      153
#define hkwd_rtrequest_nolock_err9      154
#define hkwd_rtrequest_nolock_err10     155
#define hkwd_rtrequest_nolock_err11     156
#define hkwd_rtrequest_nolock_err12     157
#define hkwd_rtrequest_nolock_err13     158
#define hkwd_rt_setgate_in              159
#define hkwd_rt_setgate_err1            160
#define hkwd_rt_setgate_err2            161
#define hkwd_rtinit_in                  162
#define hkwd_rtinit_out                 163
#define hkwd_rtinit_err1                164
#define hkwd_rtinit_err2                165
#define hkwd_rtinit_err3                166
#define hkwd_rt_cleanclones_in          167
#define hkwd_rt_cleanclones_out         168
#define hkwd_adjust_gateways_in         169
#define hkwd_adjust_gateways_out        170
#define hkwd_route_usrreq_in            171
#define hkwd_route_usrreq_out           172
#define hkwd_route_usrreq_err1          173
#define hkwd_route_usrreq_err2          174
#define hkwd_route_usrreq_err3          175
#define hkwd_rt_setmetrics_in           176
#define hkwd_m_copyback_in              177
#define hkwd_m_copyback_out             178
#define hkwd_m_copyback_err1            179
#define hkwd_m_copyback_err2            180
#define hkwd_rt_msg1_in                 181
#define hkwd_rt_msg1_out                182
#define hkwd_rt_msg2_in                 183
#define hkwd_rt_msg2_out                184
#define hkwd_rt_ifmsg_err1              185
#define hkwd_raw_init_in                186
#define hkwd_raw_input_in               187
#define hkwd_raw_input_out              188
#define hkwd_raw_usrreq_in              189
#define hkwd_raw_usrreq_out             190
#define hkwd_raw_usrreq_err1            191
#define hkwd_raw_usrreq_err2            192
#define hkwd_raw_usrreq_err3            193
#define hkwd_raw_usrreq_err4            194
#define hkwd_raw_usrreq_err5            195
#define hkwd_raw_usrreq_err6            196
#define hkwd_raw_usrreq_err7            197
#define hkwd_raw_usrreq_err8            198
#define hkwd_raw_usrreq_err9            199
#define hkwd_raw_usrreq_err10           200
#define hkwd_raw_usrreq_err11           201
#define hkwd_raw_usrreq_err12           202
#define hkwd_raw_usrreq_err13           203
#define hkwd_raw_usrreq_err14           204
#define hkwd_raw_usrreq_err15           205
#define hkwd_raw_usrreq_err16           206
#define hkwd_raw_usrreq_err17           207
#define hkwd_raw_usrreq_err18           208
#define hkwd_rn_genmatch_out7		209
#define hkwd_rtexpire_delete		210
#define hkwd_route_output_err31         211


#define HKWD_LOOP                       0x61800000
#define hkwd_loinit_in                  1
#define hkwd_loattach_in                2
#define hkwd_looutput_in                3
#define hkwd_looutput_out               4
#define hkwd_loioctl_in                 5
#define hkwd_loioctl_out                6
#define hkwd_looutput_out1              7
#define hkwd_looutput_out2              8
#define hkwd_looutput_out3              9
#define hkwd_looutput_err1              10
#define hkwd_looutput_err2              11
#define hkwd_looutput_err3              12
#define hkwd_loioctl_err1               13
#define hkwd_loioctl_err2               14

#define HKWD_CDLI			0x61900000
#define hkwd_ifinit_in			1
#define hkwd_ifinit_out			2
#define hkwd_ifreset_in			3
#define hkwd_ifreset_out		4
#define hkwd_netif_handler_in		5
#define hkwd_netif_handler_out		6
#define hkwd_if_attach_in		7
#define hkwd_if_attach_out		8
#define hkwd_link_rtrequest_in		9
#define hkwd_link_rtrequest_out		10
#define hkwd_link_rtrequest_out1	11
#define hkwd_if_down_in			12
#define hkwd_if_down_out		13
#define hkwd_if_detach_in		14
#define hkwd_if_detach_out		15
#define hkwd_if_rt_delete_in		16
#define hkwd_if_rt_delete_out		17
#define hkwd_if_rt_updroute_in		19
#define hkwd_ifioctl_in			20
#define hkwd_ifioctl_err1		21
#define hkwd_ifioctl_err2		22
#define hkwd_ifioctl_err3		23
#define hkwd_ifioctl_err4		24
#define hkwd_ifioctl_err5		25
#define hkwd_ifioctl_err6		26
#define hkwd_ifioctl_err7		27
#define hkwd_ifioctl_err8		28
#define hkwd_ifioctl_err9		29
#define hkwd_ifioctl_err10		30
#define hkwd_ifioctl_err11		31
#define hkwd_ifioctl_err12		32
#define hkwd_ifioctl_err13		33
#define hkwd_ifioctl_err14		34
#define hkwd_ifioctl_err15		35
#define hkwd_ifioctl_err16		36
#define hkwd_ifioctl_err17		37
#define hkwd_ifioctl_err18		38
#define hkwd_ifioctl_err19		39
#define hkwd_ifioctl_err20		40
#define hkwd_ifioctl_err21		41
#define hkwd_ifioctl_err22		42
#define hkwd_ifioctl_err23		43
#define hkwd_ifioctl_err24		44
#define hkwd_ifioctl_err25		45
#define hkwd_ifioctl_err26		46
#define hkwd_ifioctl_err27		47
#define hkwd_ifioctl_err28		48
#define hkwd_ifioctl_err29		49
#define hkwd_ifioctl_err30		50
#define hkwd_ifioctl_err31		51
#define hkwd_ifioctl_err32		52
#define hkwd_ifioctl_err33		53
#define hkwd_ifioctl_err34		54
#define hkwd_ifioctl_err35		55
#define hkwd_ifioctl_err36		56
#define hkwd_ifioctl_err37		57
#define hkwd_ifioctl_err38		58
#define hkwd_ifioctl_err39		59
#define hkwd_ifioctl_err40		60
#define hkwd_ifioctl_err41		61
#define hkwd_ifioctl_err42		62
#define hkwd_ifioctl_err43		63	
#define hkwd_ifioctl_err44		64
#define hkwd_ifioctl_err45		65
#define hkwd_ifioctl_err46		66
#define hkwd_ifioctl_err47		67
#define hkwd_ifioctl_err48		68
#define hkwd_ifioctl_err49		69
#define hkwd_ifioctl_err50		70
#define hkwd_ifioctl_err51		71
#define hkwd_ifioctl_err52		72
#define hkwd_ifioctl_err53		73
#define hkwd_ifioctl_err54		74
#define hkwd_ifioctl_err55		75
#define hkwd_ifioctl_err56		76
#define hkwd_ifioctl_err57		77
#define hkwd_ifioctl_err58		78
#define hkwd_ifioctl_err59		79
#define hkwd_ifioctl_err60		80
#define hkwd_ifioctl_err61		81
#define hkwd_ifioctl_err62		82
#define hkwd_ifioctl_err63		83
#define hkwd_ifioctl_err64		84
#define hkwd_ifioctl_err65		85
#define hkwd_ifioctl_err66		86
#define hkwd_ifioctl_err67		87
#define hkwd_ifconf_err1		88
#define hkwd_ifconf_err2		89
#define hkwd_ifconf_err3		90
#define hkwd_insert_mtu_in		91
#define hkwd_insert_mtu_err1		92
#define hkwd_insert_mtu_err2		93
#define hkwd_insert_mtu_out		94
#define hkwd_delete_mtu_in		95
#define hkwd_delete_mtu_err1		96
#define hkwd_delete_mtu_err2		97
#define hkwd_delete_mtu_out		98
#define hkwd_next_mtu_in		99
#define hkwd_next_mtu_out		100
#define hkwd_listifvipa_in		101
#define hkwd_listifvipa_out		102
#define hkwd_setifvipa_in		103
#define hkwd_setifvipa_err1		104
#define hkwd_setifvipa_err2		105
#define hkwd_setifvipa_err3		106
#define hkwd_setifvipa_err4		107
#define hkwd_delifvipa_in		108
#define hkwd_delifvipa_err1		109
#define hkwd_delifvipa_err2		110
#define hkwd_delifvipa_err3		111
#define hkwd_delifvipa_err4		112
#define hkwd_delvipaxface		113
#define hkwd_if_reset_route_addr	117
#define hkwd_if_rt_ifaddr_reset_in	118
#define hkwd_if_rt_ifaddr_reset_out	119

#define HKWD_NETINET_MISC               0x61A00000
#define hkwd_arpinit_in                 1
#define hkwd_arpinit_err1               2
#define hkwd_arptimer_init_in           3
#define hkwd_arpresolve_common_in       4
#define hkwd_arpresolve_common_out      5
#define hkwd_arpresolve_common_out1     6
#define hkwd_arpresolve_common_out2     7
#define hkwd_arpresolve_common_out3     8
#define hkwd_arpresolve_common_out4     9
#define hkwd_arpupdate_in               10
#define hkwd_arpupdate_out              11
#define hkwd_arpioctl_in                12
#define hkwd_arpioctl_out               13
#define hkwd_arptnew_in                 14
#define hkwd_arptnew_call_arptfree      15
#define hkwd_arpupdate_out1             16
#define hkwd_arpupdate_out2             17
#define hkwd_arpupdate_out3             18
#define hkwd_arpupdate_out4             19
#define hkwd_arpupdate_out5             20
#define hkwd_arpupdate_out6             21
#define hkwd_arpupdate_err1             22
#define hkwd_arpupdate_err2             23
#define hkwd_arpupdate_err3             24
#define hkwd_arpupdate_err4             25
#define hkwd_arpupdate_err5             26
#define hkwd_arpupdate_err6             27
#define hkwd_arpupdate_err7             28
#define hkwd_arpupdate_err8             29
#define hkwd_add_gateway_out1           30
#define hkwd_mark_gateway_down_out1     31
#define hkwd_in_control_err1		32	
#define hkwd_in_control_err2		33
#define hkwd_in_control_err3		34
#define hkwd_in_control_err4		35
#define hkwd_in_control_err5		36
#define hkwd_in_control_err6		37
#define hkwd_in_control_err7		38
#define hkwd_in_control_err8		39
#define hkwd_in_control_err9		40
#define hkwd_in_control_err10		41
#define hkwd_in_control_err11		42
#define hkwd_in_control_err12		43
#define hkwd_in_control_err13		44
#define hkwd_in_control_err14		45
#define hkwd_in_control_err15		46
#define hkwd_in_control_err16		47
#define hkwd_in_control_err17		48
#define hkwd_in_control_err18		49
#define hkwd_in_ifattach_err1		50
#define hkwd_in_ifattach_err2		51
#define hkwd_in_ifattach_err3		52
#define hkwd_in_ifattach_err4		53
#define hkwd_in_ifattach_err5		54
#define hkwd_in_ifinit_err1		55
#define hkwd_in_ifinit_out1		56
#define hkwd_in_ifinit_out2		57
#define hkwd_in_ifinit_out3		58
#define hkwd_in_addmulti_out1		59
#define hkwd_in_addmulti_out2		60
#define hkwd_in_hash_add_out1		61
#define hkwd_in_ifscrub_vipa            62
#define hkwd_in_ifscrub_out1            63
#define hkwd_in_pcballoc_err1			65
#define hkwd_in_pcbbind_err1			66
#define hkwd_in_pcbbind_err2			67
#define hkwd_in_pcbbind_err3			68
#define hkwd_in_pcbbind_err4			69
#define hkwd_in_pcbbind_err5			70
#define hkwd_in_pcbbind_err6			71
#define hkwd_in_pcbbind_err7			72
#define hkwd_in_pcbbind_err8			73
#define hkwd_in_pcbconnect_err1			74
#define hkwd_in_pcbconnect_err2			75
#define hkwd_in_pcbconnect_err3			76
#define hkwd_in_pcbconnect_err4			77
#define hkwd_in_pcbconnect_err5			78
#define hkwd_in_pcbconnect_err6			79
#define hkwd_in_pcbconnect_err7			80
#define hkwd_in_pcbconnect_err8			81
#define hkwd_in_pcbconnect_err9			82
#define hkwd_in_pcb_pseudoconnect_err1		83
#define hkwd_in_pcb_pseudoconnect_err2		84
#define hkwd_in_pcb_pseudoconnect_err3		85
#define hkwd_in_pcb_pseudoconnect_err4		86
#define hkwd_in_pcb_pseudoconnect_err5		87
#define hkwd_in_pcb_pseudoconnect_err6		88
#define hkwd_in_pcb_pseudoconnect_err7		89
#define hkwd_in_pcb_pseudoconnect_err8		90
#define hkwd_in_pcb_pseudoconnect_err9		91
#define hkwd_in_pcb_pseudobind_err1		92
#define hkwd_in_pcb_pseudobind_err2		93
#define hkwd_in_pcb_pseudobind_err3		94
#define hkwd_in_pcb_pseudobind_err4		95
#define hkwd_in_pcb_pseudobind_err5		96
#define hkwd_in_pcb_pseudobind_err6		97
#define hkwd_in_pcb_pseudobind_err7		98
#define hkwd_in_pcb_pseudobind_err8		99
#define hkwd_in_pcbnotify_out1			100
#define hkwd_in_pcbnotify_out2			101	
#define hkwd_in_pcbnotify_out3			102
#define hkwd_in_pcbnotifyall_out1		103
#define hkwd_in_pcbnotifyall_out2		104
#define hkwd_in_pcbnotifyall_out3		105
#define hkwd_in_pcblocalipnotify_out1		106
#define hkwd_in_pcblocalipnotify_out2		107
#define hkwd_in_pcblocalipnotify_out3		108
#define hkwd_icmp_unreachable			109


#define HKWD_SOCKET_UNIX			0x61B00000
#define hkwd_uipc_init_in			1
#define hkwd_unp_dispose			2
#define hkwd_unp_drop				3
#define hkwd_unp_externalize			4
#define hkwd_unp_internalize			5
#define hkwd_uipc_usrreq_err1			6
#define hkwd_uipc_usrreq_err2			7
#define hkwd_uipc_usrreq_err3			8
#define hkwd_uipc_usrreq_err4			9
#define hkwd_uipc_usrreq_err5			10	
#define hkwd_uipc_usrreq_err6			11
#define hkwd_uipc_usrreq_err7			12
#define hkwd_uipc_usrreq_err8			13
#define hkwd_uipc_usrreq_err9			14
#define hkwd_uipc_usrreq_err10			15
#define hkwd_uipc_usrreq_err11			16
#define hkwd_uipc_usrreq_err12			17
#define hkwd_uipc_usrreq_err13			18
#define hkwd_uipc_usrreq_err14			19
#define hkwd_uipc_usrreq_err15			20
#define hkwd_uipc_usrreq_err16			21
#define hkwd_uipc_usrreq_err17			22
#define hkwd_uipc_usrreq_err18			23
#define hkwd_uipc_usrreq_err19			24
#define hkwd_uipc_usrreq_err20			25
#define hkwd_uipc_usrreq_err21			26
#define hkwd_uipc_usrreq_err22			27
#define hkwd_uipc_usrreq_err23			28
#define hkwd_unp_attach_err1			29
#define hkwd_unp_attach_err2			30
#define hkwd_unp_bind_err1			31
#define hkwd_unp_bind_err2			32
#define hkwd_unp_bind_err3			33
#define hkwd_unp_bind_err4			34
#define hkwd_unp_bind_err5			35
#define hkwd_unp_bind_err6			36
#define hkwd_unp_bind_err7			37
#define hkwd_unp_bind_err8			38
#define hkwd_unp_bind_err9			39
#define hkwd_unp_bind_err10			40
#define hkwd_unp_connect_err1			41
#define hkwd_unp_connect_err2			42
#define hkwd_unp_connect_err3			43
#define hkwd_unp_connect_err4			44
#define hkwd_unp_connect_err5			45
#define hkwd_unp_connect_err6			46
#define hkwd_unp_connect_err7			47
#define hkwd_unp_connect_err8			48
#define hkwd_unp_connect_err9			49
#define hkwd_unp_connect2_err1			50
#define hkwd_unp_connect2_err2			51
#define hkwd_unp_internalize_err1		52
#define hkwd_unp_internalize_err2		53
#define hkwd_unp_internalize_err3		54
#define hkwd_unp_internalize_err4		55
#define hkwd_unp_connect_in			56
#define hkwd_unp_connect_out			57
#define hkwd_unp_bind_in			58
#define hkwd_unp_bind_out			59
#define hkwd_uipc_usrreq_in			60
#define hkwd_uipc_usrreq_out			61
#define hkwd_unp_detach_in			62
#define hkwd_unp_detach_out			63
#define hkwd_unp_attach_in			64
#define hkwd_unp_attach_out			65
#define hkwd_unp_shutdown_in			66
#define hkwd_unp_shutdown_out			67

#define HKWD_DSM_MAIN 0x5BA00000
#define hkwd_DSM_RELEASEPROVIDER_ENTER 1
#define hkwd_DSM_RELEASEPROVIDER_EXIT 2
#define hkwd_DSM_FINDPROVIDER_ENTER 3
#define hkwd_DSM_FINDPROVIDER_EXIT 4
#define hkwd_DSM_GETLOCATIONS_ENTER 5
#define hkwd_DSM_GETLOCATIONS_EXIT 6
#define hkwd_LMTDSM_GETLOCATIONS 7
#define hkwd_DSM_DBG_TRACE_UUID 8
#define hkwd_DSM_FREELOCATIONS_ENTER 9
#define hkwd_DSM_FREELOCATIONS_EXIT 10
#define hkwd_DSM_DSETINIT_ENTER 11
#define hkwd_DSM_DSETINIT_EXIT 12
#define hkwd_DSM_DSETSHUTDOWN_ENTER 13
#define hkwd_DSM_DSETSHUTDOWN_BUSY 14
#define hkwd_DSM_DSETSHUTDOWN_EXIT 15
#define hkwd_DSM_DSETGSVCSREGISTER_ENTER 16
#define hkwd_DSM_DSETGSVCSREGISTER_EXIT 17
#define hkwd_LMTDSM_DSETGSVCSREGISTER_EXIT 18
#define hkwd_DSM_DSETGSVCSUNREGISTER_ENTER 19
#define hkwd_DSM_DSETGSVCSUNREGISTER_EXIT 20
#define hkwd_LMTDSM_DSETGSVCSUNREGISTER_EXIT 21
#define hkwd_DSM_DSETPIREGISTER_ENTER 22
#define hkwd_DSM_DSETPIREGISTER_EXIT 23
#define hkwd_LMTDSM_DSETPIREGISTER_EXIT 24
#define hkwd_DSM_DSETPIUNREGISTER_ENTER 25
#define hkwd_DSM_DSETPIUNREGISTER_EXIT 26
#define hkwd_LMTDSM_DSETPIUNREGISTER_EXIT 27
#define hkwd_DSM_DSETALLOCMEM_ENTER 28
#define hkwd_LMTDSM_DSETALLOCMEM_EXIT 29
#define hkwd_DSM_DSETALLOCMEM_EXIT 30
#define hkwd_DSM_DSETFREEMEM_ENTER 31
#define hkwd_DSM_DSETFREEMEM_EXIT 32
#define hkwd_DSM_EVENTNOTIFY_ENTER 33
#define hkwd_DSM_EVENTNOTIFY_EXIT 34
#define hkwd_LMTDSM_EVENTNOTIFY_EXIT 35
#define hkwd_DSM_CALLNOTIFYFUNC 36
#define hkwd_DSM_NOTIFYFUNCDONE 37
#define hkwd_DSM_CIFINDPROVIDER_ENTER 38
#define hkwd_LMTDSM_CIFINDPROVIDER_EXIT 39
#define hkwd_DSM_CIFINDPROVIDER_EXIT 40
#define hkwd_DSM_CIRELEPROVIDER_ENTER 41
#define hkwd_LMTDSM_CIRELEPROVIDER_EXIT 42
#define hkwd_DSM_CIRELEPROVIDER_EXIT 43
#define hkwd_DSM_CIISDSETREF_ENTER 44
#define hkwd_DSM_CIISDSETREF_EXIT 45
#define hkwd_LMTDSM_CIISDSETREF_EXIT 46
#define hkwd_DSM_CIGETREFLOCS_ENTER 47
#define hkwd_LMTDSM_CIGETREFLOCS_EXIT 48
#define hkwd_DSM_CIGETREFLOCS_EXIT 49
#define hkwd_DSM_CIGETLOCS_ENTER 50
#define hkwd_LMTDSM_CIGETLOCS_EXIT 51
#define hkwd_DSM_CIGETLOCS_EXIT 52
#define hkwd_DSM_CIGETLOCSUUID_ENTER 53
#define hkwd_DSM_CIGETLOCSUUID_EXIT 54
#define hkwd_DSM_CIRGYNOTIFYHK_ENTER 55
#define hkwd_DSM_CIRGYNOTIFYHK_EXIT 56
#define hkwd_LMTDSM_CIRGYNOTIFYHK_EXIT 57
#define hkwd_DSM_CIRGYNOTIFY_EXIT 58
#define hkwd_DSM_CIRMNOTIFYHK_ENTER 59
#define hkwd_DSM_CIRMNOTIFYHK_EXIT 60
#define hkwd_DSM_CIFREELOCS_ENTER 61
#define hkwd_DSM_CIFREELOCS_EXIT 62
#define hkwd_DSM_PROPFINDDSET_ENTRY 63
#define hkwd_DSM_PROPFINDDSET_EXIT 64
#define hkwd_LMTDSM_PROPFINDDSET_EXIT 65
#define hkwd_DSM_PROPFINDDSETBYINTID_ENTER 66
#define hkwd_LMTDSM_PROPFINDDSETBYINTID_EXIT 67
#define hkwd_DSM_PROPFINDDSETBYINTID_EXIT 68
#define hkwd_DSM_FINDDSETBYUUID_ENTER 69
#define hkwd_LMTDSM_FINDDSETBYUUID_EXIT 70
#define hkwd_DSM_FINDDSETBYUUID_EXIT 71
#define hkwd_DSM_PROPFINDDSETBYUUID_ENTER 72
#define hkwd_DSM_PROPFINDDSETBYUUID_EXIT 73
#define hkwd_LMTDSM_PROPFINDDSETBYUUID_EXIT 74
#define hkwd_LMTDSM_DBG_TRACE_UUID 75
#define hkwd_DSM_PROPCREATEDSET_ENTER 76
#define hkwd_LMTDSM_PROPCREATEDSET_EXIT 77
#define hkwd_DSM_PROPCREATEDSET_EXIT 78
#define hkwd_DSM_PROPDIRTODSET_ENTER 79
#define hkwd_LMTDSM_PROPDIRTODSET_EXIT 80
#define hkwd_DSM_PROPDIRTODSET_EXIT 81
#define hkwd_DSM_PROPLISTDSETS_ENTER 82
#define hkwd_LMTDSM_PROPLISTDSETS_EXIT 83
#define hkwd_DSM_PROPLISTDSETS_EXIT 84
#define hkwd_DSM_PROPISDSETREF_ENTER 85
#define hkwd_LMTDSM_PROPISDSETREF_EXIT 86
#define hkwd_DSM_PROPISDSETREF_EXIT 87
#define hkwd_DSM_PROPGETDSETGENBYID_ENTER 88
#define hkwd_LMTDSM_PROPGETDSETGENBYID_EXIT 89
#define hkwd_DSM_PROPGETDSETGENBYID_EXIT 90
#define hkwd_DSM_DSOPHOLD_ENTER 91
#define hkwd_LMTDSM_DSOPHOLD_EXIT 92
#define hkwd_DSM_DSOPHOLD_EXIT 93
#define hkwd_DSM_DSOPRELE_ENTER 94
#define hkwd_LMTDSM_DSOPRELE_EXIT 95
#define hkwd_DSM_DSOPRELE_EXIT 96
#define hkwd_DSM_DSOPDSETROOT_ENTER 97
#define hkwd_LMTDSM_DSOPDSETROOT_EXIT 98
#define hkwd_DSM_DSOPDSETROOT_EXIT 99
#define hkwd_DSM_DSOPCREATEDSETREF_ENTER 100
#define hkwd_LMTDSM_DSOPCREATEDSETREF_EXIT 101
#define hkwd_DSM_DO_CREATEDSETREF_EXIT 102
#define hkwd_DSM_DSOPDELETEDSET_ENTER 103
#define hkwd_LMTDSM_DSOPDELETEDSET_EXIT 104
#define hkwd_DSM_DSOPDELETEDSET_EXIT 105
#define hkwd_DSM_DSOPDELETEDSETREF_ENTER 106
#define hkwd_LMTDSM_DSOPDELETEDSETREF_EXIT 107
#define hkwd_DSM_DSOPDELETEDSETREF_EXIT 108
#define hkwd_DSM_DSOPGETDSETGEN_ENTER 109
#define hkwd_LMTDSM_DSOPGETDSETGEN_EXIT 110
#define hkwd_DSM_DSOPGETDSETGEN_EXIT 111
#define hkwd_DSM_DSOPDSETTODIR_ENTER 112
#define hkwd_LMTDSM_DSOPDSETTODIR_EXIT 113
#define hkwd_DSM_DSOPDSETTODIR_EXIT 114
#define hkwd_DSM_DSOPGETDSETATTR_ENTER 115
#define hkwd_LMTDSM_DSOPGETDSETATTR_EXIT 116
#define hkwd_DSM_DSOPGETDSETATTR_EXIT 117

#endif /* _H_TRCHKID */
