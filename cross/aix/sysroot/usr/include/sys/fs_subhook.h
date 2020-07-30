/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/sys/fs_subhook.h 1.8.1.1                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2005,2009              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)19       1.8.1.1  src/bos/kernel/sys/fs_subhook.h, syslfs, bos53V, v2009_08A6 2/11/09 16:42:29 */

/*
 * COMPONENT_NAME: syslfs, sysj2, syspfs, sysxaio, syskdm
 *
 * This file should not be included directly by anything but
 * trchkid.h. This file contains subhooks for filesystems related
 * tracehooks. The hookwords themselves are defined in trchkid.h.
 */ 

#ifndef _H_FS_SUBHOOK
#define _H_FS_SUBHOOK

/* HKWD_VNOP_*, HKWD_VNODE_REF: */
#define hkwd_VNOP_EXIT             0xff         /* vnop exit */
#define hkwd_VNOP_EXIT_2           0xfe         /* secondary exit */
#define hkwd_VNOP_EXIT_32_1        0xef		/* 32BK double trace, 1/2 */
#define hkwd_VNOP_EXIT_32_2        0xee         /* 32BK double trace, 2/2 */

/* HKWD_VFS_*: */
#define hkwd_VFS_EXIT              0xff         /* vfsop exit */

/* HKWD_VFS_VGET: */
#define hkwd_VNC_ENTER				13
#define hkwd_VNC_REMOVE				14
#define hkwd_VNC_PURGE				15
#define hkwd_VNC_LOOKUP				16 /* 16-23 */
#define hkwd_VNC_LOOKUP_HIT			16
#define hkwd_VNC_LOOKUP_MISS			17

/* HKWD_PILE: */
#define hkwd_PILE_INIT			1
#define hkwd_PILE_DESTROY		2
#define hkwd_PILE_ALLOC			3
#define hkwd_PILE_FREE			4
#define hkwd_PILE_CONFIG_MAX		5
#define hkwd_PILE_CONFIG_MIN		6
#define hkwd_PILE_SLAB_ALLOC		7
#define hkwd_PILE_SLAB_DESTROY		8
#define hkwd_PILE_SLAB_SQUEEZE		9
#define hkwd_PILE_SLAB_RECLAIM		10

/* HKWD_NLC: */
#define hkwd_NLC_PURGE			1
#define hkwd_NLC_RESUME			2
#define hkwd_NLC_ENTER			3
#define hkwd_NLC_DELETE			4
#define hkwd_NLC_LOOKUP_UNDEF		16
#define hkwd_NLC_LOOKUP_MISS		17
#define hkwd_NLC_LOOKUP_NEGATIVE_HIT	18
#define hkwd_NLC_LOOKUP_FALSE_HIT	19
#define hkwd_NLC_LOOKUP_GOOD_HIT	20

/* HKWD_J2_IO: */
#define hkwd_IO_READI			5
#define hkwd_IO_WRITEI			6
#define hkwd_IO_GATHER			7
#define hkwd_IO_PAGEOUT			8
#define hkwd_IO_PAGEIN			9
#define hkwd_IO_PAGEPROTECT		10
#define hkwd_IO_DEVSTRAT		11
#define hkwd_IO_DEVSERV			12
#define hkwd_IO_IODONE			13
#define hkwd_IO_EXCEPTION		14
#define hkwd_IO_DIOMOVE			15
#define hkwd_IO_DIODEMOTED		16
#define hkwd_IO_DIODEVSTRAT		17
#define hkwd_IO_DIODONE			18
#define hkwd_IO_DIOERR			19
#define hkwd_IO_PAGERBIND		20	
#define hkwd_IO_READAHEAD		21	
#define hkwd_IO_OCLEAR			22	
#define hkwd_IO_OSET			23
#define hkwd_IO_CCLEAR			24	
#define hkwd_IO_CSET			25
#define hkwd_IO_MCLEAR			26
#define hkwd_IO_MSET			27

/* HKWD_J2_BUFMGR: */
#define hkwd_BM_CHECKOUT		1
#define hkwd_BM_CHECKIN			2
#define hkwd_BM_DEVSTRAT		3
#define hkwd_BM_IODONE			4
#define hkwd_BM_BUFWAIT			5

/* HKWD_J2_ICACHE: */
#define hkwd_IGET			1
#define hkwd_IPUT			2

/* HKWD_J2_SNAPSHOT: */
#define hkwd_SM_COW_FSEXT		1
#define hkwd_SM_COW_SNAPEXT		2
#define hkwd_SM_COW_BFSEXT		3
#define hkwd_SM_READ_FSEXT		4
#define hkwd_SM_READ_SNAPEXT		5
/* Following are for external snapshots only */
#define hkwd_SM_COW_QUEUE               6
#define hkwd_SM_COW_IOWAIT              7
#define hkwd_SM_COW_PIIOD               8
#define hkwd_SM_COW_WAKEUP              9
#define hkwd_SM_COWPOIOD                10
#define hkwd_SM_COWEOS                  11
#define hkwd_SM_COWPOR                  12
#define hkwd_SM_PIIOD                   13
#define hkwd_SM_POIOD                   14
#define hkwd_SM_COD                     15
#define hkwd_SM_COW_AWAKE               16


/* HKWD_J2_DMAP: */
#define hkwd_DB_ALLOC			1
#define hkwd_DB_FREE			2

/* HKWD_J2_GLOBAL: */
#define hkwd_GL_MOUNT			1
#define hkwd_GL_UMOUNT			2
#define hkwd_GL_LOGOPEN			3
#define hkwd_GL_LOGSHUTDOWN		4
#define hkwd_GL_RECONFIG		5
#define hkwd_GL_QENABLE			6
#define hkwd_GL_QDISABLE		7
#define hkwd_GL_FREEZE			8
#define hkwd_GL_THAW			9
#define hkwd_GL_REFREEZE		10	
#define hkwd_GL_SNAPCREATE		11
#define hkwd_GL_SNAPDELETE		12
#define hkwd_GL_SHRINK			13
#define hkwd_GL_EXTEND			14
#define hkwd_GL_DEFRAGFS		15
#define hkwd_GL_GENERIC			16

/* HKWD_J2_LOGMGR: */
#define hkwd_LM_WRAP_START		1
#define hkwd_LM_WRAP_STOP		2
#define hkwd_LM_OPEN			3
#define hkwd_LM_CLOSE			4
#define hkwd_LM_SYNC			5
#define hkwd_LM_EXCEPTION		6
#define hkwd_LM_DEVSTRAT		7
#define hkwd_LM_IODONE			8

/* HKWD_J2_TXNMGR: */
#define hkwd_TM_BEGIN			1
#define hkwd_TM_END			2
#define hkwd_TM_LOCK			3
#define hkwd_TM_COMMIT			4
#define hkwd_TM_ABORT			5
#define hkwd_TM_NOHOMEOK		6

/* HKWD_KERN_PFS: */
#define hkwd_PFS_RDWR                 1
#define hkwd_PFS_READI                2
#define hkwd_PFS_WRITEI               3

/* HKWD_DIO, HKWD_DIO_IO, HKWD_DIO_PSEG: */
#define hkwd_DIO_JMOVE	              1  /* HKWD_DIO */	
#define hkwd_DIO_PSEG                 2  /* HKWD_DIO_PSEG */
#define hkwd_DIO_PSEG_WRITE	      3  /* HKWD_DIO_PSEG */
#define hkwd_DIO_PSEG_IOWAIT	      4  /* HKWD_DIO_PSEG */
#define hkwd_DIO_XON		      5  /* HKWD_DIO */
#define hkwd_DIO_XOFF		      6  /* HKWD_DIO */
#define hkwd_DIO_STARTIO	      7  /* HKWD_DIO_IO */
#define hkwd_DIO_STARTIO_ADSPC	      8  /* HKWD_DIO_IO */
#define hkwd_DIO_STARTIO_ADSPC2	      9  /* HKWD_DIO_IO */
#define hkwd_DIO_IODONE		      10 /* HKWD_DIO_IO */
#define hkwd_DIO_IODONE_ERROR	      11 /* HKWD_DIO */
#define hkwd_DIO_STARTIO_MULTI        12 /* HKWD_DIO_IO */
#define hkwd_DIO_STARTIO_SIDS         13 /* HKWD_DIO_IO */

/* HKWD_KDM: */
#define hkwd_FSET_MOUNT		1
#define hkwd_FSET_UNMOUNT	2
#define hkwd_FSET_ACTIVE	3
#define hkwd_FSET_INACTIVE	4
#define hkwd_FSET_HANDLETOIP	5
#define hkwd_FSET_GETBULKATTR	6
#define hkwd_FSET_GETBULKALL	7
#define hkwd_FSET_DO_SOD	8
#define hkwd_FSET_DO_SEL	9
#define hkwd_FSET_GETCONFIG	10
#define hkwd_VN_IPTOHANDLE	11
#define hkwd_VN_KVPTOVP		12
#define hkwd_VN_VRELE		13
#define hkwd_VN_RWLOCK		14
#define hkwd_VN_RWUNLOCK	15
#define hkwd_VN_RWLOCK_TRY	16
#define hkwd_VN_PROBE_HOLE	17
#define hkwd_VN_GET_ALLOCINFO	18
#define hkwd_VN_GET_FILEATTR	19
#define hkwd_VN_GET_DIRATTR	20
#define hkwd_VN_GET_DMATTR	21
#define hkwd_VN_ATTRTOMR	22
#define hkwd_VN_DO_READINVIS	23
#define hkwd_VN_DO_WRITEINVIS	24
#define hkwd_VN_DO_PUNCH_HOLE	25
#define hkwd_VN_DO_SETFILEATTR	26
#define hkwd_VN_DO_SET_DMATTR	27
#define hkwd_VN_DO_SET_RESIDENT	28
#define hkwd_VN_DO_SYNC		29
#define hkwd_VN_DO_CREATBYHAN	30
#define hkwd_VN_DO_SET_REGION	31
#define hkwd_VN_SET_EVENTLIST	32


/* GRAVEYARD: The following subhook ids are still in code, but the
 * hookids have been deprecated or will be deleted in the future.
 */

/* HKWD_SYSC_LFS: */
#define hkwd_SYSC_FULLSTAT      1
#define hkwd_SYSC_LOCKFX        2
#define hkwd_SYSC_STAT          3
#define hkwd_SYSC_MKNOD         4
#define hkwd_SYSC_ACCESS        5
#define hkwd_SYSC_CHOWN         6
#define hkwd_SYSC_CHOWNX        7
#define hkwd_SYSC_CLOSEX        8
#define hkwd_SYSC_OPENX         9
#define hkwd_SYSC_FCHMOD        10
#define hkwd_SYSC_FCHOWN        11
#define hkwd_SYSC_FCHOWNX       12
#define hkwd_SYSC_FCLEAR        14
#define hkwd_SYSC_FSYNC         15
#define hkwd_SYSC_FTRUNCATE     16
#define hkwd_SYSC_TRUNCATE      17
#define hkwd_SYSC_IOCTLX        18
#define hkwd_SYSC_READX         19
#define hkwd_SYSC_WRITEX        20
#define hkwd_SYSC_LSEEK         21

/* HKWD_KERN_J2: */
#define hkwd_J2_RDWR            1
#define hkwd_J2_READI           2
#define hkwd_J2_WRITEI          3
#define hkwd_J2_CLOSE           4
#define hkwd_J2_IOPEN           5
#define hkwd_VFS_INO		6

/* HKWD_KERN_J2PAGER: */
#define hkwd_J2_PAGEIN          1
#define hkwd_J2_PAGEOUT         2
#define hkwd_J2_READAHEAD       3

/* HKWD_J2_IO: */
#define hkwd_IO_READ			1
#define hkwd_IO_WRITE			2
#define hkwd_DIO_DEMOTED		3
#define hkwd_DEVSTRAT			4

/* HKWD_DIO_J2: */
#define hkwd_DIO_CLEAR                1
#define hkwd_DIO_SET                  2
#define	hkwd_DIO_READ                 3
#define	hkwd_DIO_WRITE                4
#define hkwd_DIO_MOVE                 5
#define hkwd_J2DIO_IODONE             6
#define hkwd_DIODONE_ERR              7

#endif /* _H_FS_SUBHOOK */
