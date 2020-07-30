/*
 * Copyright 1986-1999,2002-2003 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_PRIVREGS_H
#define	_SYS_PRIVREGS_H

#pragma ident	"@(#)privregs.h	1.8	03/05/22 SMI" /* from SunOS psl.h 1.2 */

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * This file is kernel isa dependent.
 */

/*
 * This file describes the cpu's privileged register set, and
 * how the machine state is saved on the stack when a trap occurs.
 */

#include <v7/sys/psr.h>
#include <sys/fsr.h>

#ifndef	_ASM

/*
 * This structure is only here for compatibility.  It is not used by the kernel
 * and may be removed in a future release.  A better way to access this data
 * is to use gregset_t; see proc(4) and ucontext(3HEAD).
 */
struct regs {
	long	r_psr;		/* processor status register */
	long	r_pc;		/* program counter */
	long	r_npc;		/* next program counter */
	long	r_y;		/* the y register */
	long	r_g1;		/* user global regs */
	long	r_g2;
	long	r_g3;
	long	r_g4;
	long	r_g5;
	long	r_g6;
	long	r_g7;
	long	r_o0;
	long	r_o1;
	long	r_o2;
	long	r_o3;
	long	r_o4;
	long	r_o5;
	long	r_o6;
	long	r_o7;
};

#define	r_ps	r_psr		/* for portablility */
#define	r_r0	r_o0
#define	r_sp	r_o6

#endif	/* _ASM */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_PRIVREGS_H */
