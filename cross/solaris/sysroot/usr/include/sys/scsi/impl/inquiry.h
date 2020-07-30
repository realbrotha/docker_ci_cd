/*
 * Copyright (c) 1996, 2001 by Sun Microsystems, Inc.
 * All rights reserved.
 */

#ifndef	_SYS_SCSI_IMPL_INQUIRY_H
#define	_SYS_SCSI_IMPL_INQUIRY_H

#pragma ident	"@(#)inquiry.h	1.7	01/05/11 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Implementation inquiry data that is not within
 * the scope of any released SCSI standard.
 */

/*
 * Minimum inquiry data length (includes up through RDF field)
 */

#define	SUN_MIN_INQLEN	4

/*
 * Inquiry data size definition
 */
#define	SUN_INQSIZE	(sizeof (struct scsi_inquiry))

/*
 * SCSI inquiry properties
 */
#define	INQUIRY_PRODUCT_ID	"inquiry-product-id"
#define	INQUIRY_VENDOR_ID	"inquiry-vendor-id"
#define	INQUIRY_REVISION_ID	"inquiry-revision-id"
#define	INQUIRY_DEVICE_TYPE	"inquiry-device-type"

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_SCSI_IMPL_INQUIRY_H */
