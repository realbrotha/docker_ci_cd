/*
 * Copyright 2003 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_VM_SEG_KPM_H
#define	_VM_SEG_KPM_H

#pragma ident	"@(#)seg_kpm.h	1.2	03/12/21 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Kernel Physical Mapping (segkpm) segment driver.
 */

#include <vm/kpm.h>

struct segkpm_data {
	ushort_t *skd_va_select; /* page_create_va kpm vaddr bin count */
	short    skd_nvcolors;   /* VAC colors to deal with */
	uchar_t  skd_prot;
};

/*
 * segkpm create needs some platform knowledge
 */
struct segkpm_crargs {
	uint_t	prot;
	short	nvcolors;	/* VAC # virtual colors, 0 for PAC. */
};

extern struct seg *segkpm;
extern u_offset_t kpm_pgoff;
extern size_t	kpm_pgsz;
extern uint_t	kpm_pgshft;
extern uint_t	kpmp2pshft;
extern pgcnt_t	kpmpnpgs;

/* kpm controls */
extern int	kpm_enable;
extern int	kpm_smallpages;
extern int	segmap_kpm;

/*
 * kpm_page_t macros:
 * . bytes (b) to kpm pages (kpmp)
 * . pages (p) to kpm pages (kpmp), and back (with and without roundup)
 * . kpm page offset in bytes
 * . pages (p) modulo kpm pages (kpmp)
 */
#define	btokpmp(x)	((x) >> kpm_pgshft)
#define	btokpmpr(x)	(((x) + kpm_pgoff) >> kpm_pgshft)
#define	ptokpmp(x)	((x) >> kpmp2pshft)
#define	ptokpmpr(x)	(((x) + (kpmpnpgs - 1)) >> kpmp2pshft)
#define	kpmptop(x)	((x) << kpmp2pshft)
#define	kpmpageoff(x)	((x) & kpm_pgoff)
#define	pmodkpmp(x)	((x) & (kpmpnpgs - 1))

#ifdef	SEGKPM_SUPPORT

#define	IS_KPM_ADDR(addr) \
	((addr) >= segkpm->s_base && (addr) < (segkpm->s_base + segkpm->s_size))

#define	KPMPAGE_T_SZ \
	((kpm_smallpages == 0) ? sizeof (kpm_page_t) : sizeof (kpm_spage_t))

#else	/* SEGKPM_SUPPORT */

#define	IS_KPM_ADDR(addr) (segkpm != NULL)
#define	KPMPAGE_T_SZ	(0)

#endif	/* SEGKPM_SUPPORT */

#ifdef _KERNEL
/*
 * Public seg_kpm segment operations.
 */
extern int		segkpm_create(struct seg *, void *);
extern faultcode_t	segkpm_fault(struct hat *, struct seg *, caddr_t,
				size_t, enum fault_type, enum seg_rw);

/*
 * Public seg_kpm interfaces.
 */
extern caddr_t	segkpm_create_va(u_offset_t);
extern void	segkpm_mapout_validkpme(struct kpme *);

#endif	/* _KERNEL */

#ifdef	__cplusplus
}
#endif

#endif	/* _VM_SEG_KPM_H */