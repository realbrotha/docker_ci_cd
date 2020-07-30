/*
 * Copyright (c) 2001 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#ifndef	_VM_RM_H
#define	_VM_RM_H

#pragma ident	"@(#)rm.h	1.25	01/04/02 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	_KERNEL

extern size_t rm_asrss(struct as *);
extern size_t rm_assize(struct as *);
extern ushort_t rm_pctmemory(struct as *);

#endif	/* _KERNEL */

#ifdef	__cplusplus
}
#endif

#endif	/* _VM_RM_H */
