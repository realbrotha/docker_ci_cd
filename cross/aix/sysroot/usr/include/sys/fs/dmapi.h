/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/kdm/dmapi.h 1.5                                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)37  1.5  src/bos/kernel/kdm/dmapi.h, syskdm, bos530 12/18/02 17:55:58 */

/*
 * Copyright (c) 1998 VERITAS Software Corporation.  ALL RIGHTS RESERVED.
 * UNPUBLISHED -- RIGHTS RESERVED UNDER THE COPYRIGHT
 * LAWS OF THE UNITED STATES.  USE OF A COPYRIGHT NOTICE
 * IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 *
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND
 * TRADE SECRETS OF VERITAS SOFTWARE.  USE, DISCLOSURE,
 * OR REPRODUCTION IS PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF VERITAS SOFTWARE.
 *
 *		RESTRICTED RIGHTS LEGEND
 * USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT IS
 * SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH
 * (C) (1) (ii) OF THE RIGHTS IN TECHNICAL DATA AND
 * COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013.
 *		VERITAS SOFTWARE
 * 1600 PLYMOUTH STREET, MOUNTAIN VIEW, CA 94043
 */

#ifndef _H_KDM_DMAPI
#define _H_KDM_DMAPI

#include <sys/fs/dmapi_size.h>	/* REQUIRED */

/*
 * maximum hsm name string
 */

#define DM_MAXNAME		256

/*
 * Definitions from DMAPI specification v2.0 Ch.5
 */

typedef enum {
	DM_EVENT_INVALID,
	DM_EVENT_CLOSE,
	DM_EVENT_MOUNT,
	DM_EVENT_PREUNMOUNT,	DM_EVENT_UNMOUNT,
	DM_EVENT_NOSPACE,
	DM_EVENT_DEBUT,
	DM_EVENT_CREATE,	DM_EVENT_POSTCREATE,
	DM_EVENT_REMOVE,	DM_EVENT_POSTREMOVE,
	DM_EVENT_RENAME,	DM_EVENT_POSTRENAME,
	DM_EVENT_SYMLINK,	DM_EVENT_POSTSYMLINK,
	DM_EVENT_LINK,		DM_EVENT_POSTLINK,
	DM_EVENT_READ,
	DM_EVENT_WRITE,
	DM_EVENT_TRUNCATE,
	DM_EVENT_ATTRIBUTE,
	DM_EVENT_DESTROY,
	DM_EVENT_USER,
	DM_EVENT_MAX,
	DM_EVENT_CANCEL,	/* not supported -- returns EINVAL */
	
	/* NOTE: The standard defines DM_EVENT_MAX as "guaranteed to
	 * be larger than the number of the largest valid event type
	 * that can be represented in the dm_eventset_t type." The
	 * pseudo-events defined below are not valid events in terms
	 * of dm_eventset_t, thus are outside the DM_EVENT_MAX
	 * boundary. They are intended for implementation convenience
	 * only, which the KDM maps to standard-defined events.
	 */
	DM_EVENT_FCLEAR,
	DM_EVENT_MMAP
} dm_eventtype_t;

typedef enum {
	DM_EXTENT_INVALID,
	DM_EXTENT_RES,
	DM_EXTENT_HOLE
} dm_extenttype_t;

typedef enum {
	DM_MSGTYPE_INVALID,
	DM_MSGTYPE_SYNC,
	DM_MSGTYPE_ASYNC
} dm_msgtype_t;

typedef enum {
	DM_RETFLAG_INVALID,
	DM_RETFLAG_NOFLAG,
	DM_RETFLAG_FORCE
} dm_namesp_retflag_t;

typedef enum {
	DM_RESP_INVALID,
	DM_RESP_CONTINUE,
	DM_RESP_ABORT,
	DM_RESP_DONTCARE
} dm_response_t;

typedef enum {
	DM_RIGHT_NULL,
	DM_RIGHT_SHARED,
	DM_RIGHT_EXCL
} dm_right_t;

typedef enum {
	DM_CONFIG_INVALID,
	DM_CONFIG_BULKALL,
	DM_CONFIG_CREATE_BY_HANDLE,
	DM_CONFIG_DTIME_OVERLOAD,
	DM_CONFIG_LEGACY,
	DM_CONFIG_LOCK_UPGRADE,
	DM_CONFIG_MAX_ATTR_ON_DESTROY,
	DM_CONFIG_MAX_ATTRIBUTE_SIZE,
	DM_CONFIG_MAX_HANDLE_SIZE,
	DM_CONFIG_MAX_MANAGED_REGIONS,
	DM_CONFIG_MAX_MESSAGE_DATA,
	DM_CONFIG_OBJ_REF,
	DM_CONFIG_PENDING,
	DM_CONFIG_PERS_ATTRIBUTES,
	DM_CONFIG_PERS_EVENTS,
	DM_CONFIG_PERS_INHERIT_ATTRIBS,
	DM_CONFIG_PERS_MANAGED_REGIONS,
	DM_CONFIG_PUNCH_HOLE,
	DM_CONFIG_TOTAL_ATTRIBUTE_SPACE,
	DM_CONFIG_WILL_RETRY,
	DM_CONFIG_MAX
} dm_config_t;

typedef u_int	 dm_boolean_t;
typedef int	 dm_sessid_t;
typedef int	 dm_token_t;
typedef dm_ino_t dm_attrloc_t;
typedef int	 dm_ftype_t;
typedef int	 dm_updtimes_t;
typedef char	 dm_event_type_t;
typedef int	 dm_event_disp_t;
typedef	int	 dm_eventset_t;
typedef dm_u64_t dm_sequence_t;
typedef dm_s64_t dm_igen_t;
typedef dm_s64_t dm_fsid_t;
typedef dm_u64_t dm_fset_index_t;

struct dm_fileattr {
	mode_t		fa_mode;
	uid_t		fa_uid;
	gid_t		fa_gid;
	time_t		fa_atime;
	time_t		fa_mtime;
	time_t		fa_ctime;
	time_t		fa_dtime;
	dm_off_t	fa_size;
};
typedef struct dm_fileattr dm_fileattr_t;

/*
 * variable data length structure
 */

struct dm_vardata {
	dm_off_t	vd_offset;
	dm_size_t	vd_length;
};
typedef	struct dm_vardata dm_vardata_t;

#define	DM_GET_VALUE(p, field, type)	\
	((type)((dm_off_t)(p) + (p)->field.vd_offset))

#define DM_GET_LEN(p, field)	\
	((p)->field.vd_length)

#define	DM_STEP_TO_NEXT(p, type)	\
	((type)((p)->_link ? (char *)(p) + (p)->_link : NULL))

typedef dm_vardata_t	dm_handle_t;
typedef dm_vardata_t	dm_path_t;
typedef dm_vardata_t	dm_index_t;

/*
 * DM global handle, invalid handle
 */

typedef struct kdm_handle	dm_dummy_handle_t;

extern	dm_dummy_handle_t	hsmfs_global_handle;
#define	DM_GLOBAL_HANP	(void *)&hsmfs_global_handle
#define	DM_GLOBAL_HLEN	sizeof (dm_dummy_handle_t)

extern	dm_dummy_handle_t	hsmfs_invalid_handle;
#define	DM_INVALID_HANP	(void *)&hsmfs_invalid_handle
#define	DM_INVALID_HLEN	sizeof (dm_dummy_handle_t)

#define	DM_ATTR_NAME_SIZE	8	/* for dm_attrname_t */

struct dm_attrname {
	u_char	an_chars[DM_ATTR_NAME_SIZE];
};
typedef struct dm_attrname dm_attrname_t;

struct dm_attrlist {
	dm_attrname_t	al_name;
	dm_vardata_t	al_data;
};
typedef	struct dm_attrlist dm_attrlist_t;

struct dm_data_event {
	dm_handle_t	de_handle;
	dm_off_t	de_offset;
	dm_size_t	de_length;
};
typedef struct dm_data_event dm_data_event_t;

struct dm_namesp_event {
	mode_t			ne_mode;
	dm_handle_t		ne_handle1;
	dm_handle_t		ne_handle2;
	dm_path_t		ne_name1;
	dm_path_t		ne_name2;
	int			ne_retcode;
};
typedef	struct dm_namesp_event dm_namesp_event_t;

struct dm_mount_event {
	mode_t			me_mode;
	dm_handle_t		me_handle1;
	dm_handle_t		me_handle2;
	dm_path_t		me_name1;
	dm_path_t		me_name2;
	dm_handle_t		me_roothandle;
	int			me_retcode;
};
typedef	struct dm_mount_event dm_mount_event_t;

struct dm_destroy_event {
	dm_handle_t		ds_handle;
	dm_attrname_t		ds_attrname;
	dm_vardata_t		ds_attrdata;
};
typedef	struct dm_destroy_event dm_destroy_event_t;

struct dm_inherit {
	dm_attrname_t	ih_name;
	mode_t		ih_filetype;
};
typedef struct dm_inherit dm_inherit_t;

struct dm_dispinfo {
	dm_ssize_t	_link;
	dm_vardata_t	di_fshandle;
	dm_eventset_t	di_eventset;
};
typedef struct dm_dispinfo dm_dispinfo_t;

struct dm_eventmsg {
	dm_ssize_t	_link;
	dm_eventtype_t	ev_type;
	dm_token_t	ev_token;
	dm_sequence_t	ev_sequence;
	dm_vardata_t	ev_data;
	char		ev_body[8];
};
typedef struct dm_eventmsg dm_eventmsg_t;

struct dm_cancel_event {
	dm_sequence_t	ce_sequence;
	dm_token_t	ce_token;
};
typedef struct dm_cancel_event dm_cancel_event_t;

struct dm_region {
	dm_off_t	rg_offset;	/* start offset in file */
	dm_size_t	rg_size;	/* region length */
	u_int		rg_flags;	/* flags - read/write/trunc */
};
typedef struct dm_region dm_region_t;

struct dm_extent {
	dm_extenttype_t	ex_type;
	dm_off_t	ex_offset;
	dm_size_t	ex_length;
};
typedef struct dm_extent dm_extent_t;

#define	DM_REGION_NOEVENT	0x00
#define	DM_REGION_READ		0x01
#define DM_REGION_WRITE		0x02
#define	DM_REGION_TRUNCATE	0x04
#define	DM_REGION_VALIDFLAG	0x07

/*
 * Misc defines
 */

#define	DM_SESSION_INFO_LEN	256
#define	DM_NO_SESSION		-1

#define DM_TRUE			1
#define DM_FALSE		0

#define	DM_INVALID_TOKEN	-1
#define	DM_NO_TOKEN		0

/*
 * Wait flags
 */

#define	DM_EV_WAIT		0x01
#define	DM_RR_WAIT		0x01

/*
 * mount option flags -- delivered with mount event in the
 * me_mode field
 */

#define	DM_MOUNT_RDONLY		0x01
#define	DM_MOUNT_SNAPSHOT	0x02
#define	DM_MOUNT_REMOUNT	0x04

/*
 * unmount flag
 */

#define DM_UNMOUNT_FORCE	0x001

/*
 * dm_invis_write() option
 */

#define DM_WRITE_SYNC		0x01

/*
 * Attribute mask flags for dm_stat structure
 */

#define	DM_AT_ATIME	0x0001
#define	DM_AT_CFLAG	0x0002
#define	DM_AT_CTIME	0x0004
#define	DM_AT_DTIME	0x0008
#define	DM_AT_EMASK	0x0010
#define	DM_AT_GID	0x0020
#define	DM_AT_HANDLE	0x0040
#define	DM_AT_MODE	0x0080
#define	DM_AT_MTIME	0x0100
#define	DM_AT_PATTR	0x0200
#define	DM_AT_PMANR	0x0400
#define	DM_AT_SIZE	0x0800
#define	DM_AT_STAT	0x1000
#define	DM_AT_UID	0x2000

#ifdef __64BIT__
#define TIME_T time_t
#else
#define TIME_T uint :32; time_t
#endif

#ifdef __64BIT__
#define DEV_T dev_t
#else
#define DEV_T uint :32; dev_t
#endif

/* Don't even think about changing this structure. It is carefully
 * constructed so that all the members come out in the right spots
 * when accounting for 32/64-bit process/kernel combinations without
 * having to go through all the mind-bending craziness in kdm_copy.c.
 * If you feel you must change it (or even any of the dm* typedefs
 * defined elsewhere) all 32/64-bit combinations must be throughly
 * tested. Twice. Then change your mind and leave it alone.
 */
struct dm_stat {
	dm_ssize_t	_link;
	dm_vardata_t	dt_handle;
	dm_vardata_t	dt_compname;
	dm_eventset_t	dt_emask;
	int		dt_nevents;
	int		dt_pers;
	int		dt_pmanreg;
	TIME_T		dt_dtime;
	u_int		dt_change;
#ifndef __64BIT__
	uint		:32;
#endif
	/*  1170 fields */
	DEV_T		dt_dev;
	dm_ino_t	dt_ino;
	mode_t		dt_mode;
	nlink_t		dt_nlink;
	uid_t		dt_uid;
	gid_t		dt_gid;
	DEV_T		dt_rdev;
	dm_off_t	dt_size;
	TIME_T		dt_atime;
	TIME_T		dt_mtime;
	TIME_T		dt_ctime;
	u_int		dt_blksize;
	dm_size_t	dt_blocks;
};
typedef struct dm_stat dm_stat_t;

/*
 * dm_xstat -- same as dm_stat but includes data for one named
 * 	       DM attribute
 */
struct dm_xstat {
	dm_ssize_t	_link;
	dm_stat_t	dx_statinfo;
	dm_vardata_t	dx_attrdata;
};
typedef struct dm_xstat dm_xstat_t;

/*
 * Macros for setting/resetting event set list.
 */
#define	DMEV_SET(ev, evlist)	((evlist) |= (1 << (ev)))
#define	DMEV_CLR(ev, evlist)	((evlist) &= ~(1 << (ev)))
#define	DMEV_ISSET(ev, evlist)	((evlist) & (1 << (ev)))
#define	DMEV_ZERO(evlist)	(evlist) = 0

/*
 * NFS server thread starvation avoidance.
 */
#ifdef NFS3ERR_JUKEBOX
#define DM_EJUKEBOX	NFS3ERR_JUKEBOX
#else
#define DM_EJUKEBOX	10008
#endif

typedef unsigned int	dm_eventquery_t;
#define DM_OK_TO_PEND	1

struct dm_timestruct {
	time_t	dm_tv_sec;
	int32	dm_tv_nsec;
};
typedef struct dm_timestruct dm_timestruct_t;

#endif	/* _H_KDM_DMAPI */
