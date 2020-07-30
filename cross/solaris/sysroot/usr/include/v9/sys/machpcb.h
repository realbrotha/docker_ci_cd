/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_MACHPCB_H
#define	_SYS_MACHPCB_H

#pragma ident	"@(#)machpcb.h	1.20	05/06/30 SMI"

#include <sys/stack.h>
#include <sys/regset.h>
#include <v9/sys/privregs.h>
#if defined(__lint)
#include <sys/thread.h>
#endif /* __lint */

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * This file is machine dependent.
 */

/*
 * Machine dependent per-thread data.
 */
#define	MAXWIN	8	/* max # of windows currently supported */

/*
 * The system actually supports one more than the above number.
 * There is always one window reserved for trap handlers that
 * never has to be saved into the pcb struct.
 */

/*
 * Distance from beginning of thread stack (t_stk) to saved regs struct.
 */
#define	REGOFF	SA(MINFRAME)

#ifndef _ASM

/*
 * The struct machpcb is always allocated stack aligned.
 */
typedef struct machpcb {
	char	mpcb_frame[REGOFF];
	struct	regs mpcb_regs;	/* user's saved registers */
	caddr_t	mpcb_wbuf;	/* pointer to wbuf */
	caddr_t	mpcb_spbuf[MAXWIN]; /* sp's for each wbuf */
	struct	rwindow mpcb_rwin[2]; /* windows used while doing watchpoints */
	caddr_t	mpcb_rsp[2];	/* sp's for pcb_rwin[]  */
	int	mpcb_wbcnt;	/* number of saved windows in pcb_wbuf */
	uint_t	mpcb_wstate;	/* per-lwp %wstate */
	kfpu_t	*mpcb_fpu; /* fpu state */
	struct	fq mpcb_fpu_q[MAXFPQ]; /* fpu exception queue */
	caddr_t	mpcb_illexcaddr; /* address of last illegal instruction */
	uint_t	mpcb_illexcinsn; /* last illegal instruction */
	int	mpcb_flags;	/* various state flags */
	int	mpcb_wocnt;	/* window overflow count */
	int	mpcb_wucnt;	/* window underflow count */
	kthread_t *mpcb_thread;	/* associated thread */
	uint64_t mpcb_pa;	/* pcb physical */
	uint64_t mpcb_wbuf_pa;	/* pointer to wbuf - physical */
} machpcb_t;
#endif /* ! _ASM */

/* mpcb_flags */
#define	FP_TRAPPED	0x04	/* fp_traps call caused by fp queue */

/*
 * We can use lwp_regs to find the mpcb base.
 */
#ifndef _ASM
#define	lwptompcb(lwp)	((struct machpcb *) \
	    ((caddr_t)(lwp)->lwp_regs - REGOFF))
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_MACHPCB_H */
