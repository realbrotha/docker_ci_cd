/*
 * Copyright 2005 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_NEXUSDEFS_H
#define	_SYS_NEXUSDEFS_H

#pragma ident	"@(#)nexusdefs.h	1.19	05/06/30 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Bus Nexus Control Operations
 */

typedef enum {
	DDI_CTLOPS_DMAPMAPC,
	DDI_CTLOPS_INITCHILD,
	DDI_CTLOPS_UNINITCHILD,
	DDI_CTLOPS_REPORTDEV,
	DDI_CTLOPS_REPORTINT,
	DDI_CTLOPS_REGSIZE,
	DDI_CTLOPS_NREGS,
	DDI_CTLOPS_NINTRS,
	DDI_CTLOPS_SIDDEV,
	DDI_CTLOPS_SLAVEONLY,
	DDI_CTLOPS_AFFINITY,
	DDI_CTLOPS_IOMIN,
	DDI_CTLOPS_PTOB,
	DDI_CTLOPS_BTOP,
	DDI_CTLOPS_BTOPR,
	DDI_CTLOPS_RESERVED1,	/* Originally DDI_CTLOPS_POKE_INIT, obsolete */
	DDI_CTLOPS_RESERVED2,	/* Originally DDI_CTLOPS_POKE_FLUSH, obsolete */
	DDI_CTLOPS_RESERVED3,	/* Originally DDI_CTLOPS_POKE_FINI, obsolete */
	DDI_CTLOPS_INTR_HILEVEL,
	DDI_CTLOPS_XLATE_INTRS,
	DDI_CTLOPS_DVMAPAGESIZE,
	DDI_CTLOPS_POWER,
	DDI_CTLOPS_ATTACH,
	DDI_CTLOPS_DETACH,
	DDI_CTLOPS_QUIESCE,
	DDI_CTLOPS_UNQUIESCE,
	DDI_CTLOPS_PEEK,
	DDI_CTLOPS_POKE
} ddi_ctl_enum_t;

/*
 * For source compatibility, we define the following obsolete code:
 * Do NOT use this, use the real constant name.
 */
#define	DDI_CTLOPS_REMOVECHILD	DDI_CTLOPS_UNINITCHILD

/*
 * Bus config ops
 */
typedef enum {
	BUS_ENUMERATE = 0,
	BUS_CONFIG_ONE,
	BUS_CONFIG_ALL,
	BUS_CONFIG_AP,
	BUS_CONFIG_DRIVER,
	BUS_UNCONFIG_ONE,
	BUS_UNCONFIG_DRIVER,
	BUS_UNCONFIG_ALL,
	BUS_UNCONFIG_AP,
	BUS_CONFIG_OBP_ARGS
} ddi_bus_config_op_t;

/*
 * Bus Power Operations
 */
typedef enum {
	BUS_POWER_CHILD_PWRCHG = 0,
	BUS_POWER_NEXUS_PWRUP,
	BUS_POWER_PRE_NOTIFICATION,
	BUS_POWER_POST_NOTIFICATION,
	BUS_POWER_HAS_CHANGED,
	BUS_POWER_NOINVOL
} pm_bus_power_op_t;

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_NEXUSDEFS_H */
