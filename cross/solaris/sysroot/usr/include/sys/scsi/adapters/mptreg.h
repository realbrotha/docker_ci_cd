/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_SCSI_ADAPTERS_MPTREG_H
#define	_SYS_SCSI_ADAPTERS_MPTREG_H

#pragma ident	"@(#)mptreg.h	1.5	06/02/08 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

struct mptreg {
	uint32_t	m_doorbell;
	uint32_t	m_write_seq;
	uint32_t	m_diag;
	uint32_t	m_test_base_addr;
	uint32_t	m_diagrw_data;
	uint32_t	m_diagrw_addr;

	uint32_t	m_res1[6];

	uint32_t	m_intr_status;
	uint32_t	m_intr_mask;

	uint32_t	m_res2[2];

	uint32_t	m_req_q;
	uint32_t	m_reply_q;
};

/*
 * Device ids.
 */
#define	MPT_909		0x621
#define	MPT_929		0x622
#define	MPT_919		0x623
#define	MPT_1030	0x30
#define	MPT_1064	0x50
#define	MPT_1068	0x54
#define	MPT_1064E	0x56
#define	MPT_1068E	0x58

/*
 * Revisons.
 */
#define	MPT_REV(mpt)	(mpt->m_revid)

#define	FAST160_PERIOD	0x8
#define	FAST80_PERIOD	0x9
#define	FAST40_PERIOD	0xa
#define	FAST20_PERIOD	0xc
#define	FAST_PERIOD	0x19

#define	MPT_GET_PERIOD(ns) \
	(ns == 0x0) ? 5000 : \
	(ns == 0x8) ? 160000 : \
	(ns == 0x9) ? 80000 : \
	(ns == 0xa) ? 40000 : \
	(ns == 0xb) ? ((1000 * 1000)/30) : \
	(ns == 0xc) ? ((1000 * 1000)/((ns * 4) + 2)) : ((1000 * 1000)/(ns * 4))

#define	MPT_REDUCE_PERIOD(ns) \
	(ns == 0x8) ? 0x9 : \
	(ns == 0x9) ? 0xa : \
	(ns == 0xa) ? 0xc : \
	(ns == 0xc) ? 0x19 : (ns * 2)

#define	MPT_PERIOD_TO_OPTIONS(ns) 					\
	((ns == 0x8) ? (SCSI_OPTIONS_FAST160 | SCSI_OPTIONS_FAST80 |	\
	    SCSI_OPTIONS_FAST40 | 					\
	    SCSI_OPTIONS_FAST20 | SCSI_OPTIONS_FAST) : 			\
	(ns == 0x9) ? (SCSI_OPTIONS_FAST80 | SCSI_OPTIONS_FAST40 | 	\
	    SCSI_OPTIONS_FAST20 | SCSI_OPTIONS_FAST) : 			\
	(ns == 0xa || ns == 0xb) ? (SCSI_OPTIONS_FAST40 | SCSI_OPTIONS_FAST20 |\
	    SCSI_OPTIONS_FAST) : 					\
	(ns >= 0xc && ns <= 0x18) ? (SCSI_OPTIONS_FAST20 | SCSI_OPTIONS_FAST) :\
	(ns >= 0x19 && ns <= 0x31) ? SCSI_OPTIONS_FAST :  0)

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_SCSI_ADAPTERS_MPTREG_H */
