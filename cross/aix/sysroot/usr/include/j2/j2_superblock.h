/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/j2/include/j2_superblock.h 1.15                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1999,2006          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)96	1.15  src/bos/kernel/j2/include/j2_superblock.h, sysj2, bos53H, h2006_04A1 1/17/06 14:22:49 */
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

#ifndef	_H_J2_SUPERBLOCK
#define _H_J2_SUPERBLOCK	
/*
 *	j2_superblock.h
 */

#include <j2/j2_dinode.h>
#include <j2/j2_snapshot.h>

/*
 * make the magic number something a human could read
 */
#define J2_MAGIC	"J2FS" 	/* Magic word: Version 1 */

#define J2_ORIG		1	/* Version number: Version 1 */
#define	J2_VERSION	2	/* Version number: Supports versioning
				 *	s_feature* fields will indicate what
				 *	features are implemented and backwards
				 *	compatibility of the features.
				 */

/* J2_FEATURE_EXTENDED:	High-order bit is reserved to extend the file system
 * 			version support.
 */
#define J2_FEATURE_EXTENDED	0x8000000000000000LL

/* J2_FEATURE_TEST:	Bit reserved to test supported version support. */
#define	J2_FEATURE_TEST		0x4000000000000000LL
/* J2_COMPAT_VIX:	Bit indicates small inode extents are allowed.
 *			This bit is turned on to allow the filesystem to create
 *			small inode extents if there is not 16K of contiguous
 *			free space.  The filesystem remains backwards compatible
 *			until a small inode extent is created.  Once a small
 *			inode extent is created the J2_INCOMPAT_VIX bit is
 *			turned on.
 */
#define J2_COMPAT_VIX		0x0000000000000001LL

/* J2_FEATURE_COMPAT:	Features implemented by this version of the file system
 *			which are fully backwards compatible
 */
#define	J2_FEATURE_COMPAT	(J2_FEATURE_TEST | J2_COMPAT_VIX)

/* J2_FEATURE_RDONLY:	Features implemented by this version of the file system
 *			which are read-only backwards compatible
 */
#define	J2_RDONLY_SNAPSHOT	0x0000000000000001LL
#define	J2_FEATURE_RDONLY	(J2_FEATURE_TEST|J2_RDONLY_SNAPSHOT)

/* J2_FEATURE_INCOMPAT:	Features implemented by this version of the file system
 *			which are not backwards compatible in any form
 */
#define	J2_INCOMPAT_DMAPI	0x0000000000000001LL
#define	J2_INCOMPAT_EAV2	0x0000000000000002LL
/* J2_INCOMPAT_VIX:	Bit indicates small inode extents are present */
#define J2_INCOMPAT_VIX		0x0000000000000004LL

/* J2_FEATURE_LOCK: Is never supported.  The bit is used to prevent
 *	other filesystem operations when a command requires exclusive access.
 *	(e.g. rollback).  The s_feature_lock field will be filled in with the
 *	name of the command holding the lock if known.
 */
#define	J2_FEATURE_LOCK	0x2000000000000000LL
#define	J2_FEATURE_INCOMPAT	(J2_FEATURE_TEST|J2_INCOMPAT_DMAPI|J2_INCOMPAT_EAV2|J2_INCOMPAT_VIX)

/* J2_FEATURE_SUPPORTED:	Returns True/False if the specified feature is
 *				supported in the file system
 * PARAMETERS:
 *	SB	- Pointer to superblock from file system
 *	FEATURE	- Feature to check
 *	TYPE	- J2COMPAT, J2RDONLY or J2INCOMPAT; J2COMPAT indicates the
 *		  feature is a s_feature_compat feature, J2RDONLY indicates the
 *		  feature is a s_feature_rdonly feature, J2INCOMPAT indicates
 *		  the feature is a s_feature_incompat feature.
 */
#define	J2RDONLY	1
#define	J2INCOMPAT	2
#define J2COMPAT	3
#define	J2_FEATURE_SUPPORTED(SB, FEATURE, TYPE) \
	((SB)->s_version == J2_VERSION && \
	((TYPE == J2RDONLY) ? (((SB)->s_feature_rdonly & FEATURE) == FEATURE)\
			  : ((TYPE == J2INCOMPAT)\
				? (((SB)->s_feature_incompat & FEATURE)\
					== FEATURE)\
				: (((SB)->s_feature_compat & FEATURE)\
					== FEATURE))))


#define J2_FEATURE_DISABLE(SB, FEATURE, TYPE) j2_feature_disable(SB,FEATURE,TYPE)
/* 
 *	aggregate superblock 
 */
typedef struct superblock
{
	char	s_magic[4];	/* 4: magic number */
	uint32	s_version;	/* 4: version number */
	union {
		uint8		_tmspace[16];	/* 16: reserved time space for 
					             future expansion       */
		j2time_t	_s_time;	/* time last updated */
	} _sb_time;
#define s_time		_sb_time._s_time
	union {
		uint8		_nmspace[32];	/* 32: reserved name space for
					             future expansion       */
		struct {
			char	_s_fname[6];	/* name of this file system */
			char	_s_fpack[6];	/* name of this volume */
		} _nams;
	} _sb_names;

#define s_fname	 	_sb_names._nams._s_fname	
#define s_fpack	 	_sb_names._nams._s_fpack	

	int64	s_size;		/* 8: aggregate size in volume mgr blocks; */
	int32	s_bsize;	/* 4: aggregate block size in bytes; */
	int32	s_l2bsize;	/* 4: log2 of s_bsize */
	int32	s_pbsize;	/* 4: LVM block size in bytes */
	int32	s_l2pbsize;	/* 4: log2 of s_pbsize */
	int32	s_l2bfactor;	/* 4: log2(s_bsize/s_pbsize block size) */

	uint32	s_agsize;	/* 4: allocation group size in aggr. blocks */

	uint32	s_flag;		/* 4: aggregate attributes:
				 *    see j2_filsys.h
				 */ 
	uint32	s_state;	/* 4: mount/unmount/recovery state: 
				 *    see j2_filsys.h
				 */

	pxd_t	s_ait;		/* 8: first extent of 
				 *    aggregate inode table
				 */
	pxd_t	s_ait2;		/* 8: second extent of 
				 *    aggregate inode table
				 */
	char	s_rsv[16];	/* 16: */

				/* - 128 byte boundary - */

	dev64_t	s_logdev;	/* 8: device address of log */
	pxd_t	s_logpxd;	/* 8: inline log extent */
	pxd_t	s_fsckpxd;	/* 8: inline fsck work space extent */
	int32	s_logserial;	/* 4: log serial number at aggregate mount */
	int32	s_fsckloglen;	/* 4: Number of	filesystem blocks reserved for
				 *    the fsck service log.  
				 *    N.B. These blocks	are divided among the
				 *	   versions kept.  This	is not a per
				 *	   version size.
				 *    N.B. These blocks	are included in	the 
				 *	   length field	of s_fsckpxd.
				 */
	int32	s_fscklog;	/* 4: which fsck service log is	most recent
				 *    0	=> no service log data yet
				 *    1	=> the first one
				 *    2	=> the 2nd one
				 */
	int32	s_rsv1;		/* 4: */

	/* extendfs()/shrinkfs() parameter under 
	 * s_state & (FM_EXTENDFS | FM_SHRINKFS)
	 */
	int64	s_xsize;	/* 8: extendfs/shrinkfs s_size */
	pxd_t	s_xfsckpxd;	/* 8: extendfs/shrinkfs fsckpxd */
	pxd_t	s_xlogpxd;	/* 8: extendfs/shrinkfs logpxd */

	/* Version information */
	uint64	s_feature_compat;	/* 8: Bitmask of fully backward
					 *    compatible features implemented in
					 *    this file system
					 */
	uint64	s_feature_rdonly;	/* 8: Bitmask of read-only backward
					 *    compatible features implemented in
					 *    this file system
					 */
	uint64	s_feature_incompat;	/* 8: Bitmask of features implemented in
					 *    this file system that are not
					 *    backward compatible
					 */

	/* DMAPI Data */
	uint32	s_pevlist;	/* 4: file-system persistent event list */

	/* 36:	Name of command holding lock on filesystem */
#define	LOCKCMDLEN	36
	char	s_feature_lock[LOCKCMDLEN];

				/* - 256 byte boundary - */

	char	s_rsv3[256];
				/* - 512 byte boundary - */

	char	s_rsv4[512];
				/* - 1024 byte boundary - */

	/*
	 * snapshotSeries control (1024)
	 */
	char	s_snapshotMagic[4];	/* 4 */
	int32	s_snapshotVersion;	/* 4 */
	int32	s_snapshotState;	/* 4: Indicates aborted snapshots */
	int32	s_rsv5[5];	/* 20 */
	sSeries_t	s_snapshotSeries; /* 992 */
} superblock_t;

/* NAME: j2_feature_disable
 *
 * FUNCTION: Turns off version information for the specified feature
 *	in the superblock
 * PARAMETERS:
 *	sb	- Pointer to superblock from file system
 *	thisFeature	- Feature to disable
 *	featureType	- J2COMPAT, J2RDONLY or J2INCOMPAT; J2COMPAT indicates
 *			  the feature is a s_feature_compat feature, J2RDONLY
 *			  indicates the feature is a s_feature_rdonly feature,
 *			  J2INCOMPAT indicates the feature is a
 *			  s_feature_incompat feature.
 * RETURNS: None
 */
#ifdef __cplusplus
inline
#else
__inline
#endif
void
j2_feature_disable(
	struct superblock *sb,
	uint64 thisFeature,
	uint64 featureType)
{ 
	switch(featureType)
	{
	case J2RDONLY:
		sb->s_feature_rdonly &= ~thisFeature;
		break;
	case J2INCOMPAT:
		sb->s_feature_incompat &= ~thisFeature;
		break;
	case J2COMPAT:
		sb->s_feature_compat &= ~thisFeature;
		break;
	default:
		/* Unlikely, do nothing */ 
		break;
	}

	if (!sb->s_feature_compat 
		&& !sb->s_feature_rdonly 
		&& !sb->s_feature_incompat ) 
	{ 
		/* thisFeature was only feature implemented, go ahead and mark 
		 * the version back to the original 
		 */ 
		sb->s_version = J2_ORIG; 
	} 
}

#endif /*_H_J2_SUPERBLOCK */	
