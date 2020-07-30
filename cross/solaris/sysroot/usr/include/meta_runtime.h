/*
 * Copyright (c) 1998 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#ifndef _META_RUNTIME_H
#define	_META_RUNTIME_H

#pragma ident	"@(#)meta_runtime.h	2.1	00/06/22 SMI"

/*
 * Declares functions that return the values of runtime
 * parameters set in /etc/lvm/runtime.cf.  All
 * the functions declared in this file are defined in
 * SUNWmd/lib/libmeta/meta_runtime.c unless otherwise
 * noted.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

extern
boolean_t
do_owner_ioctls(void);

#ifdef __cplusplus
}
#endif

#endif /* _META_RUNTIME_H */
