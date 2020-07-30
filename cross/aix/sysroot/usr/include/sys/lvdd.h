/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernel/sys/lvdd.h 1.32.1.5                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1990              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)18	1.32.1.5  src/bos/kernel/sys/lvdd.h, sysxlvm, bos53Q, q2008_18B9 4/24/08 14:19:08 */

#ifndef _H_LVDD
#define _H_LVDD

#include <sys/types.h>

/*
 * COMPONENT_NAME: (SYSXLVM) Logical Volume Manager - 18
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 2007
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * defines for Logical Volume Device Driver ext parameter for readx and
 * writex system calls and structure definition for XLATE ioctl.
 *
 * WRITEV, is passed through to the underlying disk driver.  HWRELOC and
 * UNSAFEREL are here to allow a consistent interface with the entire
 * class of disk device drivers.  Their use is invalid with the logical
 * volume manager.
 */

#define	LVDD_RSVD  0xf0000000	/* The upper 4 bits are used internally	*/

#define WRITEV	   0x0001	/* for this request perform physical	*/
				/* write verification			*/

#define HWRELOC	   0x0002	/* for this request perform hardware	*/
				/* bad block relocation			*/

#define UNSAFEREL  0x0004	/* for this request perform bad block	*/
				/* relocation even if unsafe		*/

#define RORELOC	   0x0008	/* for this request perform READ ONLY	*/
				/* bad block relocation			*/
				/* ie. relocate only existing defects	*/ 

#define	NO_MWC	   0x0010	/* only valid on writex call to inhibit	*/
				/* normal mirror write consistency	*/
				/* rules.				*/

#define	MWC_RCV_OP 0x0020	/* Set on readx call to indicate this	*/
				/* request is doing a mirror write	*/
				/* recovery operation. i.e. a resync	*/
				/* of one LTG				*/

#define RESYNC_OP  0x0080	/* for this request resync partition 	*/
				/* logical track group(LTG)		*/
 
#define AVOID_C1   0x0100	/* this request avoid the copy 1 (primary)  */
#define AVOID_C2   0x0200	/* this request avoid the copy 2 (secondary)*/
#define AVOID_C3   0x0400	/* this request avoid the copy 3 (tertiary) */

#define NO_OVERLAP_OP 0x800

#define	AVOID_SHFT	8	/* number of places to shift to align AVOID */
				/* mask if built dynamically		    */

#define AVOID_MSK  (AVOID_C1 | AVOID_C2 | AVOID_C3)  /* Mask for avoid bits */

#define NUMCOPIES 3		/* max number of copies per logical part. */

#define LV_READ_BACKUP 0x100000
#define LV_WRITE_BACKUP LV_READ_BACKUP
#define LV_READ_STALE  0x200000
#define LV_READONLY_MIRROR 0x400000

#define LV_READ_ONLY_C1  (AVOID_MSK & ~AVOID_C1)
#define LV_READ_ONLY_C2  (AVOID_MSK & ~AVOID_C2)
#define LV_READ_ONLY_C3  (AVOID_MSK & ~AVOID_C3)

#define LV_READ_STALE_C1  (LV_READ_STALE | LV_READ_ONLY_C1)
#define LV_READ_STALE_C2  (LV_READ_STALE | LV_READ_ONLY_C2)
#define LV_READ_STALE_C3  (LV_READ_STALE | LV_READ_ONLY_C3)

/* arg structure passed in for Logical Volume Device Driver XLATE ioctl - 
 * returns the physical dev_t & physical block number for the logical block 
 * number & mirror copy specified.
 */

struct lpview {
	
	int 	lpnum;			/* logical partition number */
	struct  lview {
	   short pvnum;			/* physical volume number */
	   unsigned int ppnum;		/* physical partition number */
	   char  ppstate;		/* state of the physical partition */
           char  res[3];		/* reserved/padded space */
	} copies[NUMCOPIES];
};

/* 32 bit structures */

#if  (!defined(__64BIT__) && !defined(LVMBIGTYPES)) || defined(__KERNEL_LVM)

struct xlate_arg {

	int lbn;		/* logical block number to translate	*/
	int mirror; 		/* which copy to return pbn for:	*/
				/*		1=copy 1 (primary)	*/
				/*		2=copy 2 (secondary)	*/
				/*		3=copy 3 (tertiary)	*/
	dev32_t p_devt;		/* physical dev_t (major/minor of disk)	*/
	int pbn;		/* physical block number on disk	*/
};

struct lv_info{
	struct unique_id	vg_id;		/* volume group id */
	short			major_num;	/* major number of lv */
	short			minor_num;	/* minor number of lv */
	int			max_lps;	/* max # of lps allowed on lv */
	int			current_lps;	/* current num lps for lv */
	char			mirror_policy;	/* parallel,sequential,striped*/
	char			permissions;	/* read-write or read-only */
	char			bb_relocation;	/* bad block relocation */
	char			write_verify;	/* write verification */
	unsigned int		num_blocks;	/* num of 512 byte blocks */
	char			mwcc;		/* 
						 * 0 = non-active
						 * 1 = active, original mwcc
						 * 2 = passive mwcc
						 * 4 = undergoing passive recov
						 */
	char			mirr_able;	/* able to be mirrored */
	char			num_mirrors;	/* number of current mirrors*/
	char			striping_width;	/* stripe width */
	unsigned int		stripe_exp;	/* stripe block exponent val */
	unsigned int		backup_mirror;  /* online backup mirror msk */
						/* AVOID_C1 first copy */
						/* AVOID_C2 second copy */
						/* AVOID_C3 third copy */
	int			rsvd1;
	int			rsvd2;
	int			rsvd3;
	int			rsvd4;
};

#endif

/* mwcc states */
#define MWCC_NON_ACTIVE		0
#define MWCC_ACTIVE_MODE	1
#define	MWCC_PASSIVE_MODE	2
#define MWCC_PASSIVE_RECOVERY	4

#if  (defined(__64BIT__) || defined(LVMBIGTYPES)) && !defined(__KERNEL_LVM)
struct xlate_arg {
#else
struct xlate_arg64 {
#endif

	daddr64_t lbn;		/* logical block number to translate	*/
	int mirror; 		/* which copy to return pbn for:	*/
				/*		1=copy 1 (primary)	*/
				/*		2=copy 2 (secondary)	*/
				/*		3=copy 3 (tertiary)	*/
	dev64_t p_devt;		/* physical dev_t (major/minor of disk)	*/
	daddr64_t pbn;		/* physical block number on disk	*/
};

#if  (defined(__64BIT__) || defined(LVMBIGTYPES)) && !defined(__KERNEL_LVM)
struct lv_info{
#else
struct lv_info64{
#endif
	struct unique_id	vg_id;		/* volume group id */
	int			major_num;	/* major number of lv */
	int			minor_num;	/* minor number of lv */
	int			max_lps;	/* max # of lps allowed on lv */
	int			current_lps;	/* current num lps for lv */
	daddr64_t		num_blocks;	/* num of 512 byte blocks */
	char			mirror_policy;	/* parallel,sequential,striped*/
	char			permissions;	/* read-write or read-only */
	char			bb_relocation;	/* bad block relocation */
	char			write_verify;	/* write verification */
	char			mwcc;		/* mirror write consist check*/
	char			mirr_able;	/* able to be mirrored */
	char			num_mirrors;	/* number of current mirrors*/
	char			striping_width;	/* stripe width */
	unsigned int		stripe_exp;	/* stripe block exponent val */
	unsigned int		backup_mirror;  /* online backup mirror msk */
						/* AVOID_C1 first copy */
						/* AVOID_C2 second copy */
						/* AVOID_C3 third copy */
	int			rsvd1;
	int			rsvd2;
	int			rsvd3;
	int			rsvd4;
	int			rsvd5;
	int			rsvd6;
	int			rsvd7;
	int			rsvd8;
};

/* mirror/stripe policies */
#define SEQUENTIAL  1       /* mirrors are written and read sequentially */
#define PARALLEL    2       /* mirrors are written in and read parallel */
#define STRIPED     5       /* lvs are striped, no mirrors allowed */

/* permissions */
#define READ_ONLY	0
#define	READ_WRITE	1

/* Value required for the FORCEOFF_VG ioctl */
#define FORCE_VG_OFF    0x888

/* logical volume driver io control commands */
#define LVIOC		('v'<<8)
#if  (defined(__64BIT__) || defined(LVMBIGTYPES)) && !defined(__KERNEL_LVM)
#define	XLATE		(LVIOC|14)	/* translate lbn->pbn		    */
#else
#define	XLATE		(LVIOC|1)	/* translate lbn->pbn		    */
#endif
#define	GETVGSA		(LVIOC|2)	/* get a copy if the memory version */
					/* of the VGSA			    */
#define CACLNUP		(LVIOC|3)	/* Clean up the MWC cache and write */
					/* it to all PVs in the VG	    */
#define LP_LVIEW	(LVIOC|4)	/* send a logical view of a lp back */
#define PBUFCNT		(LVIOC|5)	/* increase pbuf pool size */

#ifdef GSCLVMD
#define CONC_STATE	(LVIOC|6)	/* see if vg is in concurrent mode */
#endif /* GSCLVMD */

#if  (defined(__64BIT__) || defined(LVMBIGTYPES)) && !defined(__KERNEL_LVM)
#define LV_INFO		(LVIOC|15)	/* get lv info */
#else
#define LV_INFO		(LVIOC|7)	/* get lv info */
#endif

#define LV_QRYBKPCOPY	(LVIOC|8)	/* get backup mirror copy mask */
#define LV_SETBKPCOPY	(LVIOC|9)	/* set backup copy mask */
#define LV_FSETBKPCOPY	(LVIOC|10)	/* force set backup mirror copy mask */
#define GETBIGVGSA	(LVIOC|11)	/* Get bigvg incore VGSA */
#define SET_SYNC_ON_RD	(LVIOC|12)	/* any read of any mirror causes sync */
#define CLR_SYNC_ON_RD	(LVIOC|13)	/* stop mirror sync on every read */
#define	XLATE64		(LVIOC|14)	/* translate lbn->pbn		    */
#define LV_INFO64	(LVIOC|15)	/* get lv info */
					/* 16: see lvdd_internal.h */
#define LV_HOLD_IOS	(LVIOC|17)	
					/* 18: see lvdd_internal.h */
					/* 19: see lvdd_internal.h */
					/* 20: see lvdd_internal.h */
					/* 21: see lvdd_internal.h */
#define GET_SVG_VGSA    (LVIOC|22)	/* Get SVG incore VGSA */
/*                      (LVIOC|23)         Used in 540 */
#define FORCEOFF_VG     (LVIOC|24)      /* Force a VG off-line */
					/* 25: see lvdd_internal.h */
					/* 26: see lvdd_internal.h */
#endif /* _H_LVDD */
