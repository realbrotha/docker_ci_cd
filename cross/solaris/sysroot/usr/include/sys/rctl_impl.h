/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_RCTL_IMPL_H
#define	_SYS_RCTL_IMPL_H

#pragma ident	"@(#)rctl_impl.h	1.3	04/09/28 SMI"

#include <sys/rctl.h>
#include <sys/time.h>
#include <sys/types.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define	RCTLCTL_GET	0
#define	RCTLCTL_SET	1

#ifndef _KERNEL

extern int rctlctl(const char *, rctlblk_t *, int);
extern size_t rctllist(char *, size_t);

#endif /* _KERNEL */

typedef struct rctl_opaque {
	rctl_qty_t	rcq_value;
	rctl_qty_t	rcq_enforced_value;
	rctl_priv_t	rcq_privilege;
	int		rcq_global_flagaction;
	int		rcq_global_syslog_level;
	int		rcq_local_flagaction;
	int		rcq_local_signal;
	id_t		rcq_local_recipient_pid;
	hrtime_t	rcq_firing_time;
} rctl_opaque_t;

extern uint_t rlim_fd_cur;
extern uint_t rlim_fd_max;

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_RCTL_IMPL_H */
