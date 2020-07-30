/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_FM_IO_DDI_H
#define	_SYS_FM_IO_DDI_H

#pragma ident	"@(#)ddi.h	1.2	04/08/06 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#define	DDI_DVR_MAX_CLASS		32

/* IO-specific FMA ereport class defintions */
#define	DDI_IO_CLASS			"io"

/* Driver defect ereport specifications */
#define	DVR_ERPT		"ddi."
#define	DVR_ECONTEXT		"context"	/* Invalid calling context */
#define	DVR_EINVAL		"einval"	/* Invalid calling semantic */
#define	DVR_EFMCAP		"fm-capability"	/* Improper FM capability */
#define	DVR_EVER		"version"	/* Invalid structure version */

/* Required payload member names */
#define	DVR_NAME		"dvr-name"
#define	DVR_STACK		"dvr-stack"
#define	DVR_STACK_DEPTH		"dvr-stack-depth"
#define	DVR_ERR_SPECIFIC	"dvr-error-specific"

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_FM_IO_DDI_H */
