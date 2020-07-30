/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/finfo.h 1.7                                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1996,2000          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)92	1.7  src/bos/kernel/sys/finfo.h, syslfs, bos530 7/18/00 17:04:32
 *
 * COMPONENT_NAME: SYSLFS - Logical File System
 *
 */
#ifndef _H_FINFO
#define _H_FINFO

/* command parameters for finfo and ffinfo */

#define	FI_PATHCONF	0
#define FI_DIOCAP	1
#define FI_KDM_FHANDLE	2	/* used by kdm only */
#define	FI_KDM_MOUNT	3	/* temporary */

struct pathconf
{
	uint		pc_link_max;
	uint		pc_max_canon;
	uint		pc_max_input;
	uint		pc_name_max;
	uint		pc_path_max;
	uint		pc_pipe_buf;
	uint		pc_vdisable;
	uint   		pc_mask;
	uint		pc_fsinfo;
	uint		__pad;
	offset_t	pc_maxfilesize;
	uint		pc_reserved[6];
};

struct diocapbuf
{
	offset_t	dio_offset;  /* Direct I/O seek alignment required */
	u_longlong_t	dio_max;     /* Maximum direct i/o transfer size */
	u_longlong_t	dio_min;     /* Minimum direct i/o transfer size */
	uint_t		dio_align;   /* Direct I/O memory alignment required */
	int		dio_rsvd[5];
};

/* defines for pc_mask */

#ifndef _H_UNISTD
#include <unistd.h>
#endif

#define PCS_NO_TRUNC		(1<<_PC_NO_TRUNC)
#define PCS_CHOWN_RESTRICTED	(1<<_PC_CHOWN_RESTRICTED)
#define PCS_SYNC_IO		(1<<_PC_SYNC_IO)

/* defines for pc_fsinfo */

#define FSI_CASE_INSENSITIVE	0x01
#define FSI_CASE_PRESERVING	0x02
#define FSI_LINK		0x04
#define FSI_SYMLINK		0x08
#define FSI_HOMOGENEOUS		0x10
#define FSI_CANSETTIME		0x20


#ifndef _NO_PROTO
int finfo(const char *, int, void *, int32long64_t);
int ffinfo(int, int, void *, int32long64_t);
#else
int finfo();
int ffinfo();
#endif

#endif /* _H_FINFO */
