/*
 * Copyright 2002 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * This header file defines the public interfaces for the alternative
 * audio mixer sample rate converter.
 *
 * CAUTION: This header file has not gone through a formal review process.
 *	Thus its commitment level is very low and may change or be removed
 *	at any time.
 */

#ifndef	_SYS_AM_SRC2_H
#define	_SYS_AM_SRC2_H

#pragma ident	"@(#)am_src2.h	1.1	02/06/12 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#define	AM_SRC2_MOD_NAME	"Audio Sample Rate Conv. #2"

#ifdef _KERNEL

extern am_ad_src_entry_t am_src2;	/* sample rate conversion routine #2 */

#endif	/* _KERNEL */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_AM_SRC2_H */
