/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_FM_ULTRASPARC_T1_H
#define	_SYS_FM_ULTRASPARC_T1_H

#pragma ident	"@(#)UltraSPARC-T1.h	1.3	06/05/31 SMI"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * header file for Niagara-specific ereports
 */

#define	FM_EREPORT_PAYLOAD_NAME_L2_AFSR		"l2-afsr"
#define	FM_EREPORT_PAYLOAD_NAME_L2_AFAR		"l2-afar"
#define	FM_EREPORT_PAYLOAD_NAME_L2_REAL_AFAR	"l2-real-afar"
#define	FM_EREPORT_PAYLOAD_NAME_L2_SYND		"l2-synd"

#define	FM_EREPORT_PAYLOAD_NAME_DRAM_AFSR	"dram-afsr"
#define	FM_EREPORT_PAYLOAD_NAME_DRAM_AFAR	"dram-afar"
#define	FM_EREPORT_PAYLOAD_NAME_DRAM_REAL_AFAR	"dram-real-afar"
#define	FM_EREPORT_PAYLOAD_NAME_DRAM_SYND	"dram-synd"

#define	FM_EREPORT_CPU_UST1_DAU			"dau"
#define	FM_EREPORT_CPU_UST1_DAC			"dac"
#define	FM_EREPORT_CPU_UST1_DSU			"dsu"
#define	FM_EREPORT_CPU_UST1_DSC			"dsc"

/*
 * The following constants are also defined in UltraSPARC-III.h and
 * could possibly be moved into a common header file
 */

#define	FM_EREPORT_PAYLOAD_NAME_RESOURCE	"resource"
#define	FM_EREPORT_PAYLOAD_NAME_ERR_TYPE	"error-type"
#define	FM_EREPORT_PAYLOAD_NAME_ERR_DISP	"error-disposition"

#ifdef __cplusplus
}
#endif

#endif /* _SYS_FM_ULTRASPARC_T1_H */
