/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/j2/include/j2_dinode.h 1.10                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2003          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */

/* @(#)84       1.10  src/bos/kernel/j2/include/j2_dinode.h, sysj2, bos530 9/25/03 21:06:44 */
/*
 * COMPONENT_NAME: (SYSJ2) JFS2 Physical File System
 *
 * FUNCTIONS: 
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1999
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef	_H_J2_DINODE
#define _H_J2_DINODE	

#include <j2/j2_types.h>
#include <sys/types.h>
#include <sys/mode.h>
#include <sys/time.h>
#include <sys/lock_def.h>

/* on-disk inode segment */
#define	INODESLOTSIZE		16
#define	L2INODESLOTSIZE	4
#if 0
#define	INODESLOTSIZE		128
#define	L2INODESLOTSIZE		7
#endif
#define	log2INODESIZE		9
#define	BASEINODESIZE		160

/*
 * extended mode bits (on-disk inode i_mode): ref. sys/mode.h
 */
#define IFJOURNAL 	0x00010000	/* journalled file */
#define J2OBSOLETE	0x00020000	/* Was ISPARSE, not used anymore */

/*
 * 64 bit size invariant time structure (ref. sys/time.h)
 */
typedef struct {
	int64	tj_sec;		/* (time64_t) seconds since the epoch */
	int32	tj_nsec;	/* (suseconds_t) nanoseconds */
	int32	tj_rsrv;	/* alignment */
} j2time_t;

#define CP_TIME2I(__tsrc, __tdest) \
{ \
	(__tdest).tj_sec  = (__tsrc).tv_sec;  \
	(__tdest).tj_nsec = (__tsrc).tv_nsec; \
}
#define CP_ITIME(__tsrc, __tdest) \
{ \
	(__tdest).tv_sec  = (__tsrc).tj_sec;  \
	(__tdest).tv_nsec = (__tsrc).tj_nsec; \
}



/*
 *	on-disk inode (dinode_t): 512 bytes
 *
 * N.B. field definition should be independent of 32/64-bit
 * environment based on primitive types only;
 */
struct dinode
{
	/*
	 *	I. base area (128 bytes)
	 *	------------------------
	 *
	 * define generic/POSIX attributes
	 */
	ino64_t	di_number;	/* 8: inode number, aka file serial number */
	uint32	di_gen;		/* 4: inode generation number */
	uint32	di_fileset;	/* 4: fileset #, inode # of inode map file */
	uint32	di_inostamp;	/* 4: stamp to show inode belongs to fileset */
	uint32	di_rsv1;	/* 4: */

	pxd_t	di_ixpxd;	/* 8: inode extent descriptor */

	int64	di_size;	/* 8: size */
	int64	di_nblocks;	/* 8: number of blocks allocated */

	uint32	di_uid;		/* 4: uid_t user id of owner */
	uint32	di_gid;		/* 4: gid_t group id of owner */

	int32	di_nlink;	/* 4: number of links to the object */
	uint32	di_mode;	/* 4: mode_t attribute, format & permission */

	j2time_t  di_atime;	/* 16: time last data accessed */
	j2time_t  di_ctime;	/* 16: time last status changed */
	j2time_t  di_mtime;	/* 16: time last data modified */
	j2time_t  di_otime;	/* 16: time created */

	/*
	 *	II. extension area (128 bytes)
	 *	------------------------------
	 */
	/*
	 *	extended attributes root (96);
	 */
	union {
		ead_t	di_ea;		/* 16: EAv1 ea descriptor */
		eaRoot_t	di_eaRoot;	/* 96: Eav2 ea descriptor */
#define di_eaFlag	di_eaRoot.eaFlag
#define di_eaDirectory	di_eaRoot.eaDirectory
#define di_eaMode	di_eaRoot.eaMode
#define di_eaACL	di_eaRoot.eaACL
#define di_aclType	di_eaRoot.eaRootData.aclObject.aclType
#define di_aclOwner	di_eaRoot.eaRootData.aclObject.aclOwner

#ifdef _KERNEL
		/* overlay for system files */
		struct {
			uint64	rsrvd[4]; /* skip eaRoot prefix */

			/* block allocation map */
			struct bmap *di_bmap;	/* incore bmap descriptor */

			/* inode allocation map */
			struct {
				uint32	di_gengen;		/* di_gen generator */
				struct inode	*di_ipimap2;	/* replica */
				struct inomap	*di_imap;	/* incore imap control */
			};
		};
#endif /* _KERNEL */
	};

	/*
	 *	B+-tree root header (32)
	 *
	 * B+-tree root node header, or dtroot_t for directory, 
	 * or data extent descriptor for inline data;
	 * N.B. must be on 8-byte boundary.
	 */
	union {
		struct {
			int32	_di_rsrvd[4];	/* 16: */
			dxd_t	_di_dxd;	/* 16: data extent descriptor */
		} _xd;
		int32		_di_btroot[8];	/* 32: xtpage_t or dtroot_t */
		ino64_t		_di_parent;	/* 8: idotdot in dtroot_t */
	} _data2r;
#define di_dxd		_data2r._xd._di_dxd
#define di_btroot	_data2r._di_btroot
#define di_dtroot	_data2r._di_btroot
#define di_xtroot	_data2r._di_btroot
#define di_parent	_data2r._di_parent

	/*
	 *	III. type-dependent area (128 bytes)
	 *	------------------------------------
	 *
	 * B+-tree root node xad array or inline data
	 */
	union {
		uint8	_data[128];
#define di_inlinedata	_data3._data

		/*
		 *	regular file or directory
		 *
		 * B+-tree root node/inline data area
		 */
		struct {
			uint8	_xad[128];
		} _file;

		/*
		 *	device special file
		 */
		struct {
			dev64_t	_rdev;	   /* 8: dev_t device major and minor */
		} _specfile;
#define di_rdev		_data3._specfile._rdev

		/*
		 *	symbolic link.
		 *
		 * link is stored in inode if its length is less than 
		 * IDATASIZE.  Otherwise stored like a regular file.
		 */
		struct {
			uint8	_fastsymlink[128];
		} _symlink;
#define di_fastsymlink	_data3._symlink._fastsymlink
	} _data3;

	/*
	 *	IV. type-dependent extension area (128 bytes)
	 *	-----------------------------------------
	 *
	 *	user-defined attribute, or 
	 *	inline data continuation, or
	 *	B+-tree root node continuation
	 * 
	 */
	union {
		uint8	_data[128];
#define di_inlineea	_data4._data
	} _data4;
};

typedef struct dinode	dinode_t;


#endif /*_H_J2_DINODE */	
