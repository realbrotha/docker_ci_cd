/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_FPU_FPUSYSTM_H
#define	_SYS_FPU_FPUSYSTM_H

#pragma ident	"@(#)fpusystm.h	1.12	05/06/30 SMI"

/*
 * ISA-dependent FPU interfaces
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _KERNEL

struct fpu;
struct regs;

#if !defined(DEBUG) && !defined(NEED_FPU_EXISTS)
#define	fpu_exists 1
#else
extern int fpu_exists;
#endif

extern int fpu_version;
extern int fpdispr;

extern void fpu_probe(void);
extern void fp_disable(void);
extern void fp_disabled(struct regs *);
extern void fp_clearregs(kfpu_t *);
extern void fp_enable(void);
extern void fp_fksave(kfpu_t *);
extern void fp_runq(struct regs *);
extern void fp_load(kfpu_t *);
extern void fp_save(kfpu_t *);
extern void fp_restore(kfpu_t *);
extern void run_fpq(klwp_t *, fpregset_t *);
extern void syncfpu(void);
extern void _fp_read_pfsr(uint64_t *fsr);
extern void _fp_write_pfsr(uint64_t *);
extern void _fp_read_pfreg(uint32_t *, uint_t);
extern void _fp_write_pfreg(uint32_t *, uint_t);
extern void fp_free(kfpu_t *, int);
extern void fp_fork(klwp_t *, klwp_t *);
extern void fp_v8_load(kfpu_t *);
extern void fp_v8p_load(kfpu_t *);
extern void fp_v8_fksave(kfpu_t *);
extern void fp_v8p_fksave(kfpu_t *);
extern uint32_t _fp_read_fprs(void);
extern void _fp_write_fprs(uint32_t);
extern void save_gsr(kfpu_t *);
extern void restore_gsr(kfpu_t *);
extern uint64_t get_gsr(kfpu_t *);
extern void set_gsr(uint64_t, kfpu_t *);
extern uint64_t _fp_read_pgsr(kfpu_t *);
extern void _fp_write_pgsr(uint64_t, kfpu_t *);
extern void _fp_read_pdreg(uint64_t *, uint_t);
extern void _fp_write_pdreg(uint64_t *, uint_t);

#endif	/* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif	/* _SYS_FPU_FPUSYSTM_H */
