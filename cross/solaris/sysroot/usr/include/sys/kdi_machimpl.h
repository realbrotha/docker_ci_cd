/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_KDI_MACHIMPL_H
#define	_SYS_KDI_MACHIMPL_H

#pragma ident	"@(#)kdi_machimpl.h	1.3	05/06/30 SMI"

#include <sys/modctl.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Return codes from the kdi_xc_one op */
#define	KDI_XC_RES_ERR		-1
#define	KDI_XC_RES_OK		0
#define	KDI_XC_RES_BUSY		1
#define	KDI_XC_RES_NACK		2

struct regs;

typedef struct kdi_mach {
	/*
	 * Iterates through the CPUs in the ready set, invoking the
	 * caller-provided callback with the CPU ID of each one.
	 */
	int (*mkdi_cpu_ready_iter)(int (*)(int, void *), void *);

	/*
	 * Send a two-argument cross-call to a specific CPU.
	 */
	int (*mkdi_xc_one)(int, void (*)(uintptr_t, uintptr_t),
	    uintptr_t, uintptr_t);

	/*
	 * Used by the state-saving code, at TL=1, to determine the current
	 * CPU's ID.  This routine may only use registers %g1 and %g2, and
	 * must return the result in %g1.  %g7 will contain the return address.
	 */
	void (*mkdi_cpu_index)(void);

	/*
	 * Used by the trap handlers to retrieve TTEs for virtual addresses.
	 * This routine may use %g1-g6, and must return the result in %g1.  %g7
	 * will contain the return address.
	 */
	void (*mkdi_trap_vatotte)(void);

	void (*mkdi_tickwait)(clock_t);
	int (*mkdi_get_stick)(uint64_t *);

	void (*mkdi_kernpanic)(struct regs *, uint_t);

	void (*mkdi_cpu_init)(int, int, int, int);
} kdi_mach_t;

#define	mkdi_cpu_ready_iter	kdi_mach.mkdi_cpu_ready_iter
#define	mkdi_xc_one		kdi_mach.mkdi_xc_one
#define	mkdi_cpu_index		kdi_mach.mkdi_cpu_index
#define	mkdi_trap_vatotte	kdi_mach.mkdi_trap_vatotte
#define	mkdi_tickwait		kdi_mach.mkdi_tickwait
#define	mkdi_get_stick		kdi_mach.mkdi_get_stick
#define	mkdi_kernpanic		kdi_mach.mkdi_kernpanic
#define	mkdi_cpu_init		kdi_mach.mkdi_cpu_init

extern void kdi_cpu_index(void);
extern void kdi_trap_vatotte(void);

extern int kdi_watchdog_disable(void);
extern void kdi_watchdog_restore(void);

extern void kdi_tlb_page_lock(caddr_t, int);
extern void kdi_tlb_page_unlock(caddr_t, int);

#ifdef __cplusplus
}
#endif

#endif /* _SYS_KDI_MACHIMPL_H */
