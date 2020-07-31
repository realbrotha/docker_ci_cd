/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_ARCHSYSTM_H
#define	_SYS_ARCHSYSTM_H

#pragma ident	"@(#)archsystm.h	1.30	04/07/16 SMI"

/*
 * A selection of ISA-dependent interfaces
 */

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_KERNEL) && !defined(_ASM)

#include <sys/types.h>
#include <sys/regset.h>
#include <sys/model.h>

extern greg_t getfp(void);
extern greg_t getpsr(void);
extern uint_t getpil(void);
extern void setpil(uint_t);
extern greg_t gettbr(void);
extern void realsigprof(int, int);

extern uintptr_t shm_alignment;

struct proc;
struct _klwp;
extern void xregrestore(struct _klwp *, int);
extern int  copy_return_window(int);

extern void setgwins(struct _klwp *, gwindows_t *);
extern void getgwins(struct _klwp *, gwindows_t *);
extern void setgwins32(struct _klwp *, gwindows32_t *);
extern void getgwins32(struct _klwp *, gwindows32_t *);
extern void setasrs(struct _klwp *, asrset_t);
extern void getasrs(struct _klwp *, asrset_t);
extern void setfpasrs(struct _klwp *, asrset_t);
extern void getfpasrs(struct _klwp *, asrset_t);

extern void setgregs(struct _klwp *, gregset_t);
extern void getgregs(struct _klwp *, gregset_t);
extern void setfpregs(struct _klwp *, fpregset_t *);
extern void getfpregs(struct _klwp *, fpregset_t *);

#ifdef _SYSCALL32_IMPL
extern void getgregs32(struct _klwp *, gregset32_t);
extern void setfpregs32(struct _klwp *, fpregset32_t *);
extern void getfpregs32(struct _klwp *, fpregset32_t *);
#endif

extern void vac_flushall(void);

extern void bind_hwcap(void);

extern u_longlong_t gettick(void);
extern uint64_t	gettick_counter(void);
extern int xcopyin_little(const void *, void *, size_t);
extern int xcopyout_little(const void *, void *, size_t);
extern void xregs_getgfiller(klwp_id_t lwp, caddr_t xrp);
extern void xregs_setgfiller(klwp_id_t lwp, caddr_t xrp);
extern void xregs_getfpfiller(klwp_id_t lwp, caddr_t xrp);
extern void xregs_setfpfiller(klwp_id_t lwp, caddr_t xrp);

struct ucontext;
extern	void	xregs_clrptr(struct _klwp *, struct ucontext *);
extern	int	xregs_hasptr(struct _klwp *, struct ucontext *);
extern	caddr_t	xregs_getptr(struct _klwp *, struct ucontext *);
extern	void	xregs_setptr(struct _klwp *, struct ucontext *, caddr_t);

#ifdef _SYSCALL32_IMPL
struct	ucontext32;
extern	void	xregs_clrptr32(struct _klwp *, struct ucontext32 *);
extern	int	xregs_hasptr32(struct _klwp *, struct ucontext32 *);
extern	caddr32_t xregs_getptr32(struct _klwp *, struct ucontext32 *);
extern	void	xregs_setptr32(struct _klwp *, struct ucontext32 *, caddr32_t);
#endif /* _SYSCALL32_IMPL */

extern	void	xregs_getgregs(struct _klwp *, caddr_t);
extern	void	xregs_getfpregs(struct _klwp *, caddr_t);
extern	void	xregs_get(struct _klwp *, caddr_t);
extern	void	xregs_setgregs(struct _klwp *, caddr_t);
extern	void	xregs_setfpregs(struct _klwp *, caddr_t);
extern	void	xregs_set(struct _klwp *, caddr_t);
extern	int	xregs_getsize(struct proc *);

extern void doflush(void *);

extern uint_t cpu_hwcap_flags;

#endif /* _KERNEL && !_ASM */


#if defined(_KERNEL)

/*
 * For binary compatability with SPARC/Solaris 1.  Needed in the
 * sparc assembly files.
 */
#define	OSYS_mmap	71

#endif /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif	/* _SYS_ARCHSYSTM_H */