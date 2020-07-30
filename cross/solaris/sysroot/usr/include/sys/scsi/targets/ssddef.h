/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * Copyright (c) 1995 by Cray Research, Inc.
 */

#ifndef	_SYS_SCSI_TARGETS_SSDDEF_H
#define	_SYS_SCSI_TARGETS_SSDDEF_H

#pragma ident	"@(#)ssddef.h	1.49	04/03/01 SMI"


#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Force compilation of "ssd" semantics, for backward compatability
 */
#ifndef __fibre
#define	__fibre
#endif

/*
 * sddef.h is the real header file. (ssddef.h is expected to
 * become obsolete.)
 */
#include <sun/sys/scsi/targets/sddef.h>


#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_SCSI_TARGETS_SSDDEF_H */
