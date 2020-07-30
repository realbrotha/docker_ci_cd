/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_HOTPLUG_PCI_PCIHP_H
#define	_SYS_HOTPLUG_PCI_PCIHP_H

#pragma ident	"@(#)pcihp.h	1.9	06/09/22 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#include <sys/hotplug/pci/pcihp_impl.h>

#ifdef	_KERNEL
/*
 * Interfaces exported by PCI Nexus extension module, kernel/misc/pcihp.
 */
int pcihp_init(dev_info_t *);
int pcihp_uninit(dev_info_t *);
int pcihp_info(dev_info_t *, ddi_info_cmd_t, void *, void **);
struct cb_ops *pcihp_get_cb_ops(void);
#endif

/* definitions for minor numbers */
#define	PCIHP_AP_MINOR_NUM(x, y)		(((uint_t)(x) << 8) | \
						((y) & 0xFF))
#define	PCIHP_AP_MINOR_NUM_TO_PCI_DEVNUM(x)	((x) & 0xFF)
#define	PCIHP_AP_MINOR_NUM_TO_INSTANCE(x)	((x) >> 8)
#define	PCIHP_DEVCTL_MINOR	0xFF
#define	PCIHP_DEBUG_MINOR	0xFE

/* definitons for cPCI platforms */
#define	PCI_CONF_EXTCAP		0x34	/* Extended Capabilities Pointer */
#define	PCI_ECP_CAPID		0x00	/* Capability ID */
#define	PCI_ECP_NEXT		0x01	/* Pointer to Next Capability */
#define	PCI_ECP_HS_CSR		0x02	/* Hot Swap Control and Status Reg */
#define	CPCI_HOTSWAP_CAPID	0x06	/* Hot Swap Capability ID */

#define	HS_CSR_INS		0x80	/* ENUM Status - Insertion */
#define	HS_CSR_EXT		0x40	/* ENUM Status - Extraction */
#define	HS_CSR_LOO		0x08	/* LED ON/OFF 1=ON 0=OFF */
#define	HS_CSR_EIM		0x02	/* ENUM# Signal Mask */

#define	PCIHP_MAKE_REG_HIGH(busnum, devnum, funcnum, register)\
	(\
	((ulong_t)(busnum & 0xff) << 16)	|\
	((ulong_t)(devnum & 0x1f) << 11)	|\
	((ulong_t)(funcnum & 0x7) <<  8)	|\
	((ulong_t)(register & 0x3f)))

#define	PCIHP_SUCCESS DDI_SUCCESS
#define	PCIHP_FAILURE DDI_FAILURE

/* cPCI hotswap definitions */
#define	PCIHP_HANDLE_ENUM	1	/* clear interrupt and take action */
#define	PCIHP_CLEAR_ENUM	2	/* clear interrupt only. */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_HOTPLUG_PCI_PCIHP_H */
