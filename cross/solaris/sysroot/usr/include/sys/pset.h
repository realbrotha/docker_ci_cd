/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_PSET_H
#define	_SYS_PSET_H

#pragma ident	"@(#)pset.h	1.5	04/08/13 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#if !defined(_ASM)

#include <sys/types.h>
#include <sys/processor.h>
#include <sys/procset.h>

typedef int psetid_t;

/* special processor set id's */
#define	PS_NONE		-1
#define	PS_QUERY	-2
#define	PS_MYID		-3

/* types of processor sets */
#define	PS_SYSTEM	1
#define	PS_PRIVATE	2

#ifndef	_KERNEL
#ifdef	__STDC__

extern int	pset_create(psetid_t *);
extern int	pset_destroy(psetid_t);
extern int	pset_assign(psetid_t, processorid_t, psetid_t *);
extern int	pset_info(psetid_t, int *, uint_t *, processorid_t *);
extern int	pset_bind(psetid_t, idtype_t, id_t, psetid_t *);
extern int	pset_getloadavg(psetid_t, double [], int);
extern int	pset_list(psetid_t *, uint_t *);
extern int	pset_setattr(psetid_t, uint_t);
extern int	pset_getattr(psetid_t, uint_t *);

#else

extern int	pset_create();
extern int	pset_destroy();
extern int	pset_assign();
extern int	pset_info();
extern int	pset_bind();
extern int	pset_getloadavg();
extern int	pset_list();
extern int	pset_setattr();
extern int	pset_getattr();

#endif	/* __STDC__ */
#endif	/* ! _KERNEL */

#endif	/* !defined(_ASM) */

/* system call subcodes */
#define	PSET_CREATE		0
#define	PSET_DESTROY		1
#define	PSET_ASSIGN		2
#define	PSET_INFO		3
#define	PSET_BIND		4
#define	PSET_GETLOADAVG		5
#define	PSET_LIST		6
#define	PSET_SETATTR		7
#define	PSET_GETATTR		8
#define	PSET_ASSIGN_FORCED	9

/* attribute bits */
#define	PSET_NOESCAPE	0x0001

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_PSET_H */
