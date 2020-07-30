/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/hd_psn.h 1.15                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1990          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)44     1.15  src/bos/kernel/sys/hd_psn.h, sysxlvm, bos53D, d2005_07B0 2/11/05 12:04:47 */
#ifndef  _H_HD_PSN
#define  _H_HD_PSN

/*
 * COMPONENT_NAME: (SYSXLVM) Logical Volume Manager - 44
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1990
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *   This file contains the physical sector number (PSN) layout of
 *   reserved space on the hardfile.
 */


#define  PSN_IPL_REC     0     /* PSN of the IPL record			*/
#define  PSN_CFG_REC     1     /* PSN of the configuration record	*/
/*
 * The Mirror Write Consistency(MWC) records must stay contiguous.  The
 * MWC cache is written to each alternately by the LVDD.
 */
#define  PSN_MWC_REC0    2     /* PSN of the first MWC cache record	*/
#define  PSN_MWC_REC1    3     /* PSN of the second MWC cache record	*/
#define  PSN_LVM_REC     7     /* PSN of LVM information record		*/
#define  PSN_BB_DIR      8     /* beginning PSN of bad block directory	*/
#define  LEN_BB_DIR      22    /* length in sectors of bad block dir	*/
#define  PSN_CFG_BAK     64    /* PSN of the backup config record	*/
#define  PSN_GEO_LVM     69    /* PSN of block reseverd for GEO LVM use */
#define  PSN_LVM_BAK     70    /* PSN of backup LVM information record	*/
#define  PSN_BB_BAK      71    /* PSN of backup bad block directory	*/
#define  PSN_SVG_MWC_REC 100   /* (100-119) PSN of the first MWC cache 
				   record for SVG  */
#define  PSN_CFG_TMP	 120   /* Area the HA heart beat info is kept	*/
#define  PSN_NONRSRVD    128   /* PSN of first non-reserved sector	*/

/*
 * The concurrent config scratch sectors (120-128)
 * are accessible thru LV0 as a negative offset from
 * the VGSA area, which starts at PSN_NONRSRVD.
 * Note that there is one config scratch area
 * per pvol.  When a config operation is sent across,
 * We need to write each of them in turn.
 * When reading them, we stop once we hit a match--
 * (one which contains the same OP/NODEID/HINT as the config message)
 */
#define  GETCFG_LSN(Vg, copy)	\
		(GETSA_LSN(Vg, copy<<1) - (PSN_NONRSRVD - PSN_CFG_TMP))
#endif /* _H_HD_PSN */
