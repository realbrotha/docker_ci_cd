/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_LIBNVP_H
#define	_LIBNVP_H

#pragma ident	"@(#)libnvpair.h	1.2	04/03/17 SMI"

#include <sys/nvpair.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif

void nvlist_print(FILE *, nvlist_t *);

#ifdef	__cplusplus
}
#endif

#endif	/* _LIBNVP_H */
