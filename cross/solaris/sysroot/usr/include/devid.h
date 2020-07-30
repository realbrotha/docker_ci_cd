/*
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_DEVID_H
#define	_DEVID_H

#pragma ident	"@(#)devid.h	1.13	04/07/16 SMI"

#ifndef	_KERNEL
#include <sys/types.h>
#endif	/* _KERNEL */

#include <sys/sunddi.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct devid_nmlist {
	char 	*devname;
	dev_t	dev;
} devid_nmlist_t;

extern int	devid_get(int fd, ddi_devid_t *retdevid);
extern void	devid_free(ddi_devid_t devid);
extern int	devid_get_minor_name(int fd, char **retminor_name);
extern size_t	devid_sizeof(ddi_devid_t devid);
extern int	devid_compare(ddi_devid_t devid1, ddi_devid_t devid2);
extern int	devid_deviceid_to_nmlist(char *search_path, ddi_devid_t devid,
		    char *minor_name, devid_nmlist_t **retlist);
extern void	devid_free_nmlist(devid_nmlist_t *list);
extern int	devid_valid(ddi_devid_t devid);
extern char	*devid_str_encode(ddi_devid_t devid, char *minor_name);
extern int	devid_str_decode(char *devidstr,
		    ddi_devid_t *retdevid, char **retminor_name);
extern void	devid_str_free(char *devidstr);
extern int	devid_scsi_encode(int version, char *driver_name,
		    uchar_t *inq, size_t inq_len, uchar_t *inq80,
		    size_t inq80_len, uchar_t *inq83, size_t inq83_len,
		    ddi_devid_t *ret_devid);
extern char	*devid_to_guid(ddi_devid_t devid);
extern void	devid_free_guid(char *guid);

#ifdef	__cplusplus
}
#endif

#endif	/* _DEVID_H */
