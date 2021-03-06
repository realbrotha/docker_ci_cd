/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _NFSID_MAP_H
#define	_NFSID_MAP_H

#pragma ident	"@(#)nfsid_map.h	1.1	04/07/18 SMI"

#ifndef _KERNEL
#include <stddef.h>
#endif
#include <sys/sysmacros.h>
#include <sys/types.h>

/*
 * NFSv4 id mapping daemon
 *
 * This daemon is used by the kernel to map strings in the form
 * "user@dns_domain" from an integer form or vice-versa.  The daemon
 * uses the system configured name services for the mapping.
 *
 * The status results determines if a mapping was successful.
 *
 * The mapping is cached in the kernel, so that expensive upcalls are
 * reduced to a minimum.
 */

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * mapid commands
 */
#define	NFSMAPID_STR_UID	1
#define	NFSMAPID_UID_STR	2
#define	NFSMAPID_STR_GID	3
#define	NFSMAPID_GID_STR	4

/*
 * We are passing in arguments in a variable length struct
 * similar to a dirent_t. We break apart a utf8string into
 * its components and allocate a struct long enough to hold
 * the string and a NUL terminator.  The caller must ensure the
 * terminator is set.
 */
struct mapid_arg {
	uint_t	cmd;
	union {
		uid_t		uid;
		gid_t		gid;
		int		len;
	} u_arg;
	char str[1];
};
typedef struct mapid_arg mapid_arg_t;

/*
 * The actual required size of the args, rounded up to a 64 bit boundary
 */
#define	MAPID_ARG_LEN(str_length)	\
	((offsetof(mapid_arg_t, str[0]) + 1 + (str_length) + 7) & ~ 7)

/*
 * Return status codes
 */
#define	NFSMAPID_OK		0

/*
 * numeric string is mapped to its literal number
 */
#define	NFSMAPID_NUMSTR		1

/*
 * Value cannot be mapped, badly formed string
 */
#define	NFSMAPID_UNMAPPABLE	2

/*
 * Caller provided invalid arguments
 */
#define	NFSMAPID_INVALID	3

/*
 * Internal error in daemon e.g. out of memory, can't return result
 */
#define	NFSMAPID_INTERNAL	4

/*
 * Incorrect domain used
 */
#define	NFSMAPID_BADDOMAIN	5

/*
 * Out of range uid/gid
 */
#define	NFSMAPID_BADID		6

/*
 * User or group cannot be found in nameservice
 */
#define	NFSMAPID_NOTFOUND	7

/*
 * Similar to the arguments, the result is variable length.
 * The returner must ensure the string terminator is set.
 */
struct mapid_res {
	uint_t	status;
	union {
		uid_t		uid;
		gid_t		gid;
		int		len;
	} u_res;
	char str[1];
};
typedef struct mapid_res mapid_res_t;

/*
 * The actual required size of the result, rounded up to a 64 bit boundary
 */
#define	MAPID_RES_LEN(str_length)	\
	((offsetof(mapid_res_t, str[0]) + 1 + (str_length) + 7) & ~ 7)

#ifdef	__cplusplus
}
#endif

#endif /* _NFSID_MAP_H */
