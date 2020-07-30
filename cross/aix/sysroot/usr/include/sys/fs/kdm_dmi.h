/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/kdm/kdm_dmi.h 1.5                                */
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
/* @(#)43  1.5  src/bos/kernel/kdm/kdm_dmi.h, syskdm, bos530 11/18/02 16:38:58 */

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

#ifndef _H_KDM_DMI
#define _H_KDM_DMI

#define	DM_ACTIVE	1
#define	DM_PENDING	2

/*
 * name descrepancies ..
 */

#define	vd_off	vd_offset
#define	vd_len	vd_length

/*
 * hsm file handle
 * we need it here to simplify allocations
 * in variable length structures
 */

struct kdm_handle {
	dm_fsid_t	fsid;
	dm_ino_t	ino;
/*	dm_u32_t	pad1; */	/* no need to pad 64-bit dm_ino_t */
	dm_igen_t	gen;
	short		flags;
	char		type;
	char		pad2[5];
};
typedef struct kdm_handle kdm_handle_t;

#define KDM_HANDLE_SIZE_OK(len)		\
	((len) == sizeof (kdm_handle_t))

struct kdm_data_event {
	dm_data_event_t	kde_base;
	kdm_handle_t	kde_vhandle;	/* private */
};
typedef struct kdm_data_event kdm_data_event_t;

#define	kde_handle	kde_base.de_handle
#define	kde_offset	kde_base.de_offset
#define	kde_length	kde_base.de_length

struct kdm_namesp_event {
	dm_namesp_event_t	kne_base;
	kdm_handle_t		kne_phandle1;		/* private */
	kdm_handle_t		kne_phandle2;
	char			kne_pathnames[4];
};
typedef	struct kdm_namesp_event kdm_namesp_event_t;

#define	kne_mode		kne_base.ne_mode
#define	kne_handle1		kne_base.ne_handle1
#define	kne_handle2		kne_base.ne_handle2
#define	kne_name1		kne_base.ne_name1
#define	kne_name2		kne_base.ne_name2
#define	kne_retcode		kne_base.ne_retcode

struct kdm_mount_event {
	dm_mount_event_t	kme_base;
	kdm_handle_t		kme_pfshandle;
	kdm_handle_t		kme_pmnthandle;
	kdm_handle_t		kme_proothandle;
	char			kme_pathnames[4];
};
typedef	struct kdm_mount_event kdm_mount_event_t;

#define	kme_mode		kme_base.me_mode
#define	kme_fshandle		kme_base.me_handle1
#define	kme_mnthandle		kme_base.me_handle2
#define	kme_roothandle		kme_base.me_roothandle
#define	kme_path		kme_base.me_name1
#define	kme_media		kme_base.me_name2
#define	kme_retcode		kme_base.me_retcode

struct kdm_destroy_event {
	dm_destroy_event_t	kds_base;
	kdm_handle_t		kds_phandle;
	char			kds_pattrdata[4];
};
typedef	struct kdm_destroy_event kdm_destroy_event_t;

#define	kds_handle		kds_base.ds_handle
#define	kds_attrname		kds_base.ds_attrname
#define	kds_attrdata		kds_base.ds_attrdata

struct kdm_dispinfo {
	dm_dispinfo_t	kdi_base;
	kdm_handle_t	kdi_handle;
};
typedef struct kdm_dispinfo kdm_dispinfo_t;

#define	kdi_handleoff	kdi_base.di_fshandle.vd_offset
#define	kdi_handlelen	kdi_base.di_fshandle.vd_length
#define	kdi_link	kdi_base._link
#define	kdi_eventset	kdi_base.di_eventset
#define	kdi_fsid	kdi_handle.fsid
#define	kdi_type	kdi_handle.type
#define	kdi_handlestart	kdi_handle.fsid

struct kdm_sessinfo {
	int		hsmsi_id;		/* session id */
	int		hsmsi_nexttoken;	/* next event token */
	int		hsmsi_numoutq;		/* # messages on hsms_outq */
	int		hsmsi_totmsg;		/* total outmsgs for session  */
	int		hsmsi_waitcnt;		/* waiters on outq */
	int		hsmsi_namlen;		/* name length */
	char		hsmsi_name[DM_MAXNAME];	/* session name string */
};

struct kdm_eventinfo {
	int		hsmei_status;
	int		hsmei_origactive;	/* active level at posting */
	int		hsmei_curactive;	/* current active level */
};

/*
 * hsmei_status values : flags
 */

#define KDM_NEEDCONTEXT		0x01
#define	KDM_NEEDDISP		0x02	/* return error if no disposition */
#define	KDM_FORCEASYNC_EV	0x04	/* force async for user event */

/* values for type field of kdm_handle */
#define KDM_INODE_HANDLE	1		/* inode */
#define KDM_GENERIC_HANDLE	2		/* generic handle for fs */
#define KDM_GLOBAL_HANDLE	4		/* global hsm handle */
#define KDM_INVALID_HANDLE	8		/* invalid hsm handle */

#define KDM_ROOTINO		2

/*
 * values for flags field of kdm_handle
 */

#define KDM_IGNORE_GEN	0x1			/* ignore gen part of handle */

#define KDM_MAXBUF		65536
#define KDM_MAXREG		(KDM_MAXBUF / sizeof (dm_region_t))

struct kdm_stat {
	dm_stat_t	kdt_base;
	kdm_handle_t	kdt_phandle;
	char		kdt_pname[4];
};
typedef	struct kdm_stat	kdm_stat_t;

#define	kdt_link	kdt_base._link
#define	kdt_handle	kdt_base.dt_handle
#define	kdt_compname	kdt_base.dt_compname
#define	kdt_emask	kdt_base.dt_emask
#define	kdt_nevents	kdt_base.dt_nevents
#define	kdt_dtime	kdt_base.dt_dtime
#define	kdt_change	kdt_base.dt_change
#define	kdt_dev		kdt_base.dt_dev
#define	kdt_ino		kdt_base.dt_ino
#define	kdt_mode	kdt_base.dt_mode
#define	kdt_nlink	kdt_base.dt_nlink
#define	kdt_uid		kdt_base.dt_uid
#define	kdt_gid		kdt_base.dt_gid
#define	kdt_rdev	kdt_base.dt_rdev
#define	kdt_size	kdt_base.dt_size
#define	kdt_atime	kdt_base.dt_atime
#define	kdt_ctime	kdt_base.dt_ctime
#define	kdt_mtime	kdt_base.dt_mtime
#define	kdt_blocksize	kdt_base.dt_blksize
#define	kdt_blocks	kdt_base.dt_blocks
#define kdt_pers	kdt_base.dt_pers
#define kdt_pmanreg	kdt_base.dt_pmanreg

struct kdm_xstat {
	dm_xstat_t	kdxt_base;
	kdm_handle_t	kdxt_phandle;
	char		kdxt_vardata[4];
};
typedef struct kdm_xstat	kdm_xstat_t;

#define	kdxt_link	kdxt_base._link
#define	kdxt_stat	kdxt_base.dx_statinfo
#define kdxt_sublink	kdxt_base.dx_statinfo._link
#define kdxt_handle	kdxt_base.dx_statinfo.dt_handle
#define kdxt_compname	kdxt_base.dx_statinfo.dt_compname
#define kdxt_emask	kdxt_base.dx_statinfo.dt_emask
#define kdxt_nevents	kdxt_base.dx_statinfo.dt_nevents
#define kdxt_dtime	kdxt_base.dx_statinfo.dt_dtime
#define kdxt_change	kdxt_base.dx_statinfo.dt_change
#define kdxt_dev	kdxt_base.dx_statinfo.dt_dev
#define kdxt_ino	kdxt_base.dx_statinfo.dt_ino
#define kdxt_mode	kdxt_base.dx_statinfo.dt_mode
#define kdxt_nlink	kdxt_base.dx_statinfo.dt_nlink
#define kdxt_uid	kdxt_base.dx_statinfo.dt_uid
#define kdxt_gid	kdxt_base.dx_statinfo.dt_gid
#define kdxt_rdev	kdxt_base.dx_statinfo.dt_rdev
#define kdxt_size	kdxt_base.dx_statinfo.dt_size
#define kdxt_atime	kdxt_base.dx_statinfo.dt_atime
#define kdxt_ctime	kdxt_base.dx_statinfo.dt_ctime
#define kdxt_mtime	kdxt_base.dx_statinfo.dt_mtime
#define kdxt_blocksize	kdxt_base.dx_statinfo.dt_blksize
#define kdxt_blocks	kdxt_base.dx_statinfo.dt_blocks
#define kdxt_pers	kdxt_base.dx_statinfo.dt_pers
#define kdxt_pmanreg	kdxt_base.dx_statinfo.dt_pmanreg
#define kdxt_attrdata	kdxt_base.dx_attrdata

#define _OS_PAGESIZE	    4096
#define DM_EXTENTSPERPAGE	(_OS_PAGESIZE / sizeof (dm_extent_t))
#define DM_EXTENTBUFLEN		(DM_EXTENTSPERPAGE * sizeof (dm_extent_t))

/*
 * This structure is returned for each event disposition as part of a
 * GETSESSIONINFO call
 */

struct kdm_u_dispinfo {
	int		eventnum;
	dm_sessid_t	id;		/* id of session */
	int		type;		/* KDM_GENERIC_HANDLE or GLOBAL */
	dev_t		fsid;		/* no value if KDM_GLOBAL_HANDLE */
};

/*
 * lock flags, must not overlap dmapi.h lock flag(s)
 * #define DM_RR_WAIT		0x01
 */

#define DM_KEEPLOCK		0x0200	/* retain lock after event complete */
#define DM_NORLSE		0x0400	/* lock acquired outside of event */
#define DM_LOCKHANDOFF		0x0800	/* hand off lock to user thread */

/* lock info */
struct kdm_lockinfo {
	kdm_handle_t		handle;
	short			flags;
	char			right;
};

#define KDM_U_IOCTL(f, c, a) kdm_u_ioctl(f, c, a)

/*
 * The DMAPI ioctl for VxFS is VX_DMAPI_IOCTL.
 * The KDM_IOC_XXX numbers are embedded in a structure
 * that gets passed in with a VX_DMAPI_GROUP ioctl, to identify
 * which DMAPI operation has been requested.
 */

#define KDM_IOC	(10000)
#define	KDM_IOC_OPENSESSION	(KDM_IOC + 0)	/* open a session */
#define	KDM_IOC_CLOSESESSION	(KDM_IOC + 1)	/* close a session */
#define	KDM_IOC_GETALLTOKENS	(KDM_IOC + 2)	/* get tokens for session */
#define	KDM_IOC_REQUESTRIGHT	(KDM_IOC + 3)	/* request a right */
#define	KDM_IOC_RELEASERIGHT	(KDM_IOC + 4)	/* release a right */
#define	KDM_IOC_GETALLOCINFO	(KDM_IOC + 5)	/* get allocation info */
#define	KDM_IOC_PROBEHOLE	(KDM_IOC + 6)	/* punch a hole */
#define	KDM_IOC_READINVIS	(KDM_IOC + 7)	/* invisible read */
#define	KDM_IOC_WRITEINVIS	(KDM_IOC + 8)	/* invisible write */
#define	KDM_IOC_GETREGION	(KDM_IOC + 9)	/* get managed regions*/
#define	KDM_IOC_SETREGION	(KDM_IOC + 10)	/* set managed regions*/
#define	KDM_IOC_GETBULKATTR	(KDM_IOC + 11)	/* bulk attribute get */
#define	KDM_IOC_GETFILEATTR	(KDM_IOC + 12)	/* single attribute get */
#define	KDM_IOC_GETDMATTR	(KDM_IOC + 13)	/* get hsm attribute */
#define	KDM_IOC_SETDMATTR	(KDM_IOC + 14)	/* set hsm attribute */
#define	KDM_IOC_REMOVEDMATTR	(KDM_IOC + 15)	/* remove hsm attribute */
#define	KDM_IOC_GETMOUNTINFO	(KDM_IOC + 16)	/* return mount info */
#define	KDM_IOC_LISTDMATTR	(KDM_IOC + 17)	/* list hsm attribute */
#define	KDM_IOC_LISTINHERIT	(KDM_IOC + 18)	/* list inheritable */
#define	KDM_IOC_SETINHERIT	(KDM_IOC + 19)	/* mark as inheritable*/
#define	KDM_IOC_CLEARINHERIT	(KDM_IOC + 20)	/* mark as not inheritable */
#define	KDM_IOC_SETFILEATTR	(KDM_IOC + 21)	/* invisible setattr */
#define	KDM_IOC_SETEVENTLIST	(KDM_IOC + 22)	/* event enable */
#define	KDM_IOC_GETEVENTLIST	(KDM_IOC + 23)	/* event list */
#define	KDM_IOC_GETDIRATTR	(KDM_IOC + 24)	/* invisible readdir */
#define	KDM_IOC_GETNEXTEVENT	(KDM_IOC + 25)	/* event get */
#define	KDM_IOC_RESPONDEVENT	(KDM_IOC + 26)	/* event respond */
#define	KDM_IOC_MOVEEVENT	(KDM_IOC + 27)	/* move event */
#define	KDM_IOC_QUERYSESSION	(KDM_IOC + 28)	/* return session name */
#define	KDM_IOC_QUERYRIGHT	(KDM_IOC + 29)	/* check for a right */
#define	KDM_IOC_PUNCHHOLE	(KDM_IOC + 30)	/* punch a hole */
#define	KDM_IOC_FINDEVENTMSG	(KDM_IOC + 31)	/* return message for event */
#define	KDM_IOC_SENDMSG		(KDM_IOC + 32)	/* add a user event */
#define	KDM_IOC_GETDISP		(KDM_IOC + 33)	/* get event disposition */
#define	KDM_IOC_SETDISP		(KDM_IOC + 34)	/* set event disposition */
#define	KDM_IOC_ATTACHEVENT	(KDM_IOC + 35)	/* attach to an event */
#define	KDM_IOC_GETSESSIONINFO	(KDM_IOC + 36)	/* get session info */
#define	KDM_IOC_GETEVENTINFO	(KDM_IOC + 37)	/* get event info */
#define	KDM_IOC_LISTSESSIONS	(KDM_IOC + 38)	/* list sessions */
#define	KDM_IOC_FDTOHANDLE	(KDM_IOC + 39)	/* fdtohandle */
#define	KDM_IOC_SETRESIDENT	(KDM_IOC + 40)	/* set_resident */
#define	KDM_IOC_CREATEUSER	(KDM_IOC + 41)	/* create msg with thread */
#define KDM_IOC_GETBULKALL	(KDM_IOC + 42)	/* bulkall attribute get */
#define KDM_IOC_SYNC		(KDM_IOC + 43)	/* sync by handle */
#define KDM_IOC_SETONDESTROY	(KDM_IOC + 44)	/* set dm attr on destroy */
#define KDM_IOC_PATHTOHANDLE	(KDM_IOC + 45)	/* pathtohandle : nofollow */
#define KDM_IOC_CREATBYHAN	(KDM_IOC + 46)	/* create object by handle */
#define KDM_IOC_VER_STR		(KDM_IOC + 47)	/* get version string */
#define KDM_IOC_EVENTQUERY	(KDM_IOC + 48)	/* query event thread state */
/* extensions */
#define KDM_IOC_GETCONFIG	(KDM_IOC + 49)	/* query implementation cfg */

struct kdm_ioctl_param {
	int	oplen;
	int	aplen;
	int	(*func)();
};

struct	kdm_pathtohandleargs {
	kdm_handle_t	*handlep;
	char		*path;
};

struct	kdm_fdtohandleargs {
	kdm_handle_t	*handlep;
	int		fdes;
};

struct kdm_open_session_args {
	dm_sessid_t	old_session;
	dm_sessid_t	*new_session;
	int		newnamlen;
	char		newname[DM_MAXNAME];
};

struct kdm_ver_str_args {
	dm_size_t	buflen;
	caddr_t		bufp;
};

struct kdm_query_session_args {
	dm_sessid_t	id;
	dm_size_t	buflen;
	char		*buf;
	dm_size_t	*rlenp;
};

struct kdm_list_sessions_args {
	int		numentries;
	dm_sessid_t	*sidp;
	int		*rnump;
};

struct kdm_getall_tokens_args {
	dm_sessid_t	id;
	dm_token_t	*tokenbuf;
	int		numentries;
	int		*rnump;
};

struct kdm_request_right_args {
	dm_sessid_t	id;
	dm_token_t	token;
	kdm_handle_t	handle;
	short		flags;
	char		right;
	char		noblock;
};

struct kdm_query_right_args {
	dm_sessid_t		id;
	kdm_handle_t		handle;
	dm_token_t		token;
	struct kdm_lockinfo	*infop;
};

struct kdm_get_allocinfo_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	dm_off_t	off;
	int		nextents;
	dm_off_t	*offsp;
	dm_extent_t	*extentp;
	int		*rextentp;
	int		*retvalp;
};

struct kdm_punch_hole_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	int		op;
	dm_off_t	off;
	dm_size_t	len;
	dm_off_t	*roffp;
	dm_size_t	*rlenp;
};

struct kdm_invisread_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	dm_off_t	off;
	dm_size_t	len;
	char		*buf;
	int		flag;	/* buffered write */
};

struct kdm_sync_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	int		flags;
};

struct kdm_get_region_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	int		nregions;
	dm_region_t	*regbufp;
	int		*ret_regions;
};

struct kdm_set_region_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	int		nregions;
	dm_region_t	*regbufp;
	int		*exactflagp;
};

struct kdm_get_dirattr_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	dm_u32_t	mask;
	dm_attrloc_t	*rlocp;
	dm_attrloc_t	loc;
	dm_stat_t	*bufp;
	dm_size_t	buflen;
	int		*nretlen;
	int		*retvalp;
};

struct kdm_get_bulkattr_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	int		mask;
	dm_attrloc_t	*rlocp;
	dm_attrloc_t	loc;
	dm_stat_t	*bufp;
	int		nelem;
	int		*nretp;
	int		*retvalp;
};
typedef struct kdm_get_bulkattr_args	kdm_get_bulkattr_args_t;

struct kdm_get_bulkall_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	int		mask;
	dm_attrloc_t	*rlocp;
	dm_attrloc_t	loc;
	dm_attrname_t	attrname;
	dm_stat_t	*bufp;
	dm_size_t	len;
	dm_size_t	*rlenp;
	int		*retvalp;
};
typedef struct kdm_get_bulkall_args	kdm_get_bulkall_args_t;

struct kdm_get_dmattr_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	char		attrname[9];
	dm_updtimes_t	dmtime;
	void		*buf;
	dm_size_t	len;
	dm_size_t	*rlenp;
};

struct kdm_set_resident_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	int		res;
};

struct kdm_getattrtimes_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	time_t		*tp;
};

struct kdm_list_dmattr_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	dm_inherit_t	*bufp;
	u_int		nelem;
	u_int		*nelemp;
};

struct kdm_set_inherit_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	char		attrname[9];
	mode_t		mode;
};

struct kdm_setondestroy_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	char		attrname[9];
	int		length;
	int		flag;
};
typedef struct kdm_setondestroy_args	kdm_setondestroy_args_t;

struct kdm_fileattr_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	dm_fileattr_t	attrstruct;
};

struct kdm_set_eventlist_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	int		eventmask;
	int		maxevent;
	int		*retmaskp;
};

struct kdm_getall_disp_args {
	dm_sessid_t	id;
	dm_size_t	buflen;
	dm_dispinfo_t	*dispbuf;
	dm_size_t	*rlenp;
};

struct kdm_getmountinfo_args {
	dm_sessid_t	id;
	dm_token_t	token;
	kdm_handle_t	handle;
	dm_size_t	len;
	char		*buf;
	dm_size_t	*rlenp;
};

struct kdm_get_eventlist_args {
	dm_sessid_t	id;
	kdm_handle_t	handle;
	dm_token_t	token;
	int		*eventmaskp;
};

struct kdm_get_nextevent_args {
	dm_sessid_t	id;
	char		*msgbuf;
	dm_size_t	buflen;
	dm_size_t	*rlenp;
	int		maxmsgs;
	int		nowait;
};

struct kdm_find_eventmsg_args {
	dm_sessid_t	id;
	dm_token_t	token;
	dm_size_t	buflen;
	dm_eventmsg_t	*msgbuf;
	dm_size_t	*rlenp;
};

struct kdm_respond_event_args {
	dm_sessid_t	id;
	dm_token_t	token;
	void		*buf;
	dm_size_t	buflen;
	int		action;
	int		err;
};

struct kdm_create_msg_args {
	dm_sessid_t	id;
	int		type;
	dm_size_t	buflen;
	char		*msgbuf;
	dm_token_t	*tokenp;
};

struct kdm_attach_event_args {
	dm_sessid_t	id;
	dm_token_t	token;
};

struct kdm_move_event_args {
	dm_token_t	token;
	dm_sessid_t	fromid;
	dm_sessid_t	toid;
	dm_token_t	*rtokenp;
};

struct kdm_get_sessioninfo_args {
	dm_sessid_t		id;
	struct kdm_sessinfo	*sesinfop;
	struct kdm_dispinfo	*infop;
	int			nentries;
	int			*rnump;
};

struct kdm_get_eventinfo_args {
	dm_sessid_t		id;
	dm_token_t		token;
	struct kdm_eventinfo	*eventinfop;
	struct kdm_lockinfo	*lockbuf;
	int			numentries;
	int			*rnump;
};

struct kdm_posix_byhandle_args {
	dm_sessid_t	id;
	dm_token_t	token;
	kdm_handle_t	dhandle;
	kdm_handle_t	handle;
	int		opcode;
	char		*name;
	int		namelen;
	char		*symlink;
	int		linklen;
};

struct kdm_eventquery_args {
	dm_sessid_t	sid;
	dm_token_t	token;
	dm_eventquery_t	queryname;
	dm_size_t	*value;
};

struct	kdm_get_config_args {
	kdm_handle_t	handle;
	dm_config_t	flag;
	dm_size_t	*retvalp;
};

/*
 * opcode values for the above
 */

#define	DM_CREATE_FILE	1
#define	DM_CREATE_DIR	2
#define	DM_CREATE_SYML	3

#endif	/* _H_KDM_DMI */
