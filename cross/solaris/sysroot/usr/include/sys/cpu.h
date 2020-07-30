/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_CPU_H
#define	_SYS_CPU_H

#pragma ident	"@(#)cpu.h	1.21	06/06/08 SMI"

/*
 * Include generic bustype cookies.
 */
#include <sys/bustypes.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Global kernel variables of interest
 */

#if defined(_KERNEL) && !defined(_ASM)

extern int dvmasize;			/* usable dvma size in pages */

/*
 * Cache defines
 *
 * Each bit represents an attribute of the system's caches that
 * the OS must handle.  For example, VAC caches must have virtual
 * alias detection, VTAG caches must be flushed on every demap, etc.
 */
#define	CACHE_NONE		0	/* No caches of any type */
#define	CACHE_VAC		0x01	/* Virtual addressed cache */
#define	CACHE_VTAG		0x02	/* Virtual tagged cache */
#define	CACHE_PAC		0x04	/* Physical addressed cache */
#define	CACHE_PTAG		0x08	/* Physical tagged cache */
#define	CACHE_WRITEBACK		0x10	/* Writeback cache */
#define	CACHE_IOCOHERENT	0x20	/* I/O coherent cache */

extern int cache;

/* set this to zero if no vac */
extern int vac;

/*
 * Use to insert cpu-dependent instructions into spin loops
 */
#pragma weak	cpu_smt_pause
extern	void	cpu_smt_pause();
#define	SMT_PAUSE()	{ if (&cpu_smt_pause) cpu_smt_pause(); }

#endif /* defined(_KERNEL) && !defined(_ASM) */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_CPU_H */
