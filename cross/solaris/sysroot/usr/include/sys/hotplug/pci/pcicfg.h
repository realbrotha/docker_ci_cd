/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_HOTPLUG_PCI_PCICFG_H
#define	_SYS_HOTPLUG_PCI_PCICFG_H

#pragma ident	"@(#)pcicfg.h	1.4	05/12/20 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#include <sys/hotplug/pci/pcihp_impl.h>

/*
 * Interfaces exported by PCI configurator module, kernel/misc/pcicfg.
 */
int pcicfg_configure(dev_info_t *, uint_t);
int pcicfg_unconfigure(dev_info_t *, uint_t);

#define	PCICFG_SUCCESS DDI_SUCCESS
#define	PCICFG_FAILURE DDI_FAILURE

/*
 * The following subclass definition for Non Transparent bridge should
 * be moved to pci.h.
 */
#define	PCI_BRIDGE_STBRIDGE	0x9

#define	PCICFG_CONF_INDIRECT_MAP	1
#define	PCICFG_CONF_DIRECT_MAP		0

#define	PCICFG_DEV_CONF_MAP_PROP	PCI_DEV_CONF_MAP_PROP
#define	PCICFG_BUS_CONF_MAP_PROP	PCI_BUS_CONF_MAP_PROP

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_HOTPLUG_PCI_PCICFG_H */
