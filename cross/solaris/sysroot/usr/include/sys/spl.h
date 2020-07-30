/*
 * Copyright 1986,2003 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_SPL_H
#define	_SYS_SPL_H

#pragma ident	"@(#)spl.h	1.4	03/04/21 SMI" /* from SunOS psl.h 1.2 */

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * v9 spl and ipl are identical since pil is a separate register.
 */
#define	ipltospl(n)	(n)
#define	spltoipl(n)	(n)

/*
 * Hardware spl levels
 * XXX - This is a hack for softcall to block all i/o interrupts.
 * XXX - SPL5 and SPL3 are hacks for the latest zs code.
 * it should be replace by the appropriate interrupt class info.
 */
#define	SPL8    15
#define	SPL7    13
#define	SPL5    12
#define	SPLTTY  SPL5
#define	SPL3    6

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_SPL_H */
