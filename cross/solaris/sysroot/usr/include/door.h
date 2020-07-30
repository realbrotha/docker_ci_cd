/*
 * Copyright 1995-1998,2002-2003 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SMI	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#ifndef	_DOOR_H
#define	_DOOR_H

#pragma ident	"@(#)door.h	1.9	03/02/27 SMI"

#include <sys/types.h>
#include <sys/door.h>
#include <ucred.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASM

/*
 * Doors API
 */
int	door_create(void (*)(void *, char *, size_t, door_desc_t *, uint_t),
    void *, uint_t);
int	door_revoke(int);
int	door_info(int, door_info_t *);
int	door_call(int, door_arg_t *);
int	door_return(char *, size_t, door_desc_t *, uint_t);
int	door_cred(door_cred_t *);
int	door_ucred(ucred_t **);
int	door_bind(int);
int	door_unbind(void);
typedef void door_server_func_t(door_info_t *);
door_server_func_t *door_server_create(door_server_func_t *);

#endif /* _ASM */

#ifdef __cplusplus
}
#endif

#endif	/* _DOOR_H */
