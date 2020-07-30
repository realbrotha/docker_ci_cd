/*
 * Copyright 2002 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_BOOTSTAT_H
#define	_SYS_BOOTSTAT_H

#pragma ident	"@(#)bootstat.h	1.1	02/01/24 SMI"

#include <sys/stat.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * 32/64-bit neutral stat and time structure to allow booters to be shared
 *	among ILP32 and LP64 kernels.
 */
typedef struct boottime {
	int64_t	tv_sec;
	int64_t	tv_nsec;
} boottime_t;

/*
 * Current booters only support mode and size, with the exception of
 *	nfs booter also uses ino.
 */
struct bootstat {
	uint64_t	st_dev;
	uint64_t	st_ino;
	uint32_t	st_mode;
	uint32_t	st_nlink;
	int32_t		st_uid;
	int32_t		st_gid;
	uint64_t	st_rdev;
	uint64_t	st_size;
	boottime_t	st_atim;
	boottime_t	st_mtim;
	boottime_t	st_ctim;
	int32_t		st_blksize;
	int64_t		st_blocks;
	char		st_fstype[_ST_FSTYPSZ];
};

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_BOOTSTAT_H */
