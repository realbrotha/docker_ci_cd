/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/lvmrec.h 1.25                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1989          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)57     1.25  src/bos/usr/include/lvmrec.h, liblvm, bos530 11/14/03 10:31:31 */

#ifndef  _H_LVMREC
#define  _H_LVMREC

/*
 * COMPONENT_NAME: (LIBLVM) Logical Volume Manager - lvmrec.h
 *
 * ORIGINS: 27
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1998
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 *   This file contains the structures which describe the LVM
 *   information record.  This is physical block 7 of each hardfile.
 */
#include <sys/inttypes.h>

#define LVM_LVMID    0x5F4C564D     /* LVM id field of ASCII "_LVM" */

#define  LVM_VERSION_1		1   /* first version - AIX 3.0 */
#define  LVM_STRIPE_ENHANCE	2   /* version with striped lv's - AIX 4.1 */
#define  LVM_1024_PPSIZE	3   /* ppsizes of 512 and 1024 */
#define  LVM_GT_1016		4   /* version with support for > 1016 pps/pv */
#define  LVM_BIG_VGDA		5   /* version with support for > 32 pvs/vg */
#define  LVM_STRIPE_MIRROR	6   /* support for striped + mirrored lvs */
#define  LVM_MIRROR_SCHED_99	7   /* support parallel write sequential read */
#define  LVM_32_CHAR_VGID	8   /* 128-bit VGids are Created in AIX 5.1.0 */
				    /* and supported in AIX 4.3.3 and later */ 
#define  LVM_GS_CONC_SUPPORT	8   /* support for Enhanced concurrent mode */
#define  LVM_PASSIVE_MWCC	9   /* new passive mwcc algorithm introduced */
#define  LVM_VARIABLE_LTG     	9   /* support for variable ltg  */
#define  LVM_SNAPSHOT_VG      	10  /* support for snapshot ltg  */
#define  LVM_GROW_DISK_SIZE     10  /* support for grow disk */

				    /* The following (LVM_DEVLVZ*) are versions
                                     * to indicate support of an LV type that 
                                     * does not require skipping the LVCB.
                                     * This is the mklv -T O option */
#define  LVM_DEVLVZ43		11  /* Allows import back to 4.3 */
#define  LVM_DEVLVZ51		12  /* Allows import back to 5.1 */
#define  LVM_DEVLVZ52		13  /* 5.2 and later releases only */

                                    /* Skip some version numbers to allow for 
                                     * future backporting of function */

#define  LVM_VG_530		30  /* Support Large LTG and LV stripe sizes */
#define  LVM_SVG_VER		31  /* Version 5.3 VG */

#define  LVM_MAX_VERSION        LVM_SVG_VER /* max version # */


#define  FIRST_ALTERNATE_VM   32000 /* first version number for alternate 
                                     * volume managers */

#define  GPFS_PV              32001 /* PV reserved for GPFS */


/*************************************************************************
 * LVM record for Scalable Volume Groups (default for AIX 5.3 and later) 
 * The lvm_id, vg_id and version must be in the same location as the 
 * previous lvm record for pre 53 code.
 *************************************************************************
 */

struct lvm_rec {

        /* Validity field to determine if LVM record is valid (_LVM) */
        __long32_t lvm_id;

        /* VGID */
        struct unique_id vg_id;

        /* Length of the VG Status Area */
        __long32_t ppsa_len;

        /* Length of the PV Missing area */
        __long32_t pv_miss_len;

        /* Length of the MWC Dirty Bits area */
        __long32_t mwc_db_len;

        /* Length of the VG info area */
        __long32_t vg_info_len;

        /* Length of the PV info area */
        __long32_t pv_info_len;

        /* Length of the LVCB info area */
        __long32_t lvcb_info_len;

        /* Length of the LV Entries Area */
        __long32_t lvea_len;

        /* Length of the PP Entries Area */
        __long32_t ppea_len;

        /* The length of the LVM metadata reserved area */
        __long32_t res_area_len;

        /* The PV index number within the metadata areas */
        int pv_num;

        /* Version number of this VG */
        short int version;

        /* Partition size. (2 to the power pp_size) */
        short int pp_shift;

	/*** VGSA ***/

        /* PPSA Physical Sector Numbers (Primary/Secondary) */
        daddr64_t ppsa_psn[2];

        /* PV Missing Physical Sector Number (Primary/Secondary) */
        daddr64_t pv_miss_psn[2];

        /* Passive MWC Area Physical Sector Number (Primary/Secondary) */
        daddr64_t mwc_db_psn[2];

	/*** VGDA ***/

        /* VG Info Physical Sector Number (Primary/Secondary) */
        daddr64_t vg_info_psn[2];

        /* PV Info Physical Sector Number (Primary/Secondary) */
        daddr64_t pv_info_psn[2];

        /* LVCB Info Physical Sector Number (Primary/Secondary) */
        daddr64_t lvcb_info_psn[2];

        /* LV Entries Physical Sector Numbers (Primary/Secondary) */
        daddr64_t lvea_psn[2];

        /* PP Entries Physical Sector Numbers (Primary/Secondary) */
        daddr64_t ppea_psn[2];

        /* VGSA Physical Sector Number (Primary/Secondary) */
        daddr64_t vgsa_psn[2];
	
        /* VGDA Physical Sector Number (Primary/Secondary) */
        daddr64_t vgda_psn[2];
	
        /* Length of the VG Status Area 
	 * stalepp_len + pv_miss_len + mwc_db_len 
	 */
	__long32_t vgsa_len;

        /* Length of the VG Desciptor Area 
	 * vg_info_len + pv_info_len + lvcb_info_len + lvea_len + ppea_len
	 */
	__long32_t vgda_len;

        /* Logical Track Group size (2 to the power ltg_shift) */
        int ltg_shift;

        /* Length of the BB Relocation area */
        __long32_t bb_reloc_len;

        /* Bad Block Relocation Physical Sector Number */
        daddr64_t bb_reloc_psn;

	/* pad to DBSIZE (512 bytes) */
	char reserved[264];
};

/* LVM record layout 
00000E00   LVM___ID VGID__W1 VGID__W2 VGID__W3
00000E10   VGID__W4 PPSA_LEN PVM__LEN MWCDBLEN
00000E20   VGI__LEN PVI__LEN LVCBILEN LVEA_LEN
00000E30   PPEA_LEN RESA_LEN PV___NUM VERnPPSZ
00000E40   PPSAPSN0 PPSAPSN0 PPSAPSN1 PPSAPSN1
00000E50   PVM_PSN0 PVM_PSN0 PVM_PSN1 PVM_PSN1 
00000E60   MWC_PSN0 MWC_PSN0 MWC_PSN1 MWC_PSN1
00000E70   VGI_PSN0 VGI_PSN0 VGI_PSN1 VGI_PSN1 
00000E80   PVI_PSN0 PVI_PSN0 PVI_PSN1 PVI_PSN1 
00000E90   LVCBPSN0 LVCBPSN0 LVCBPSN1 LVCBPSN1
00000EA0   LVEAPSN0 LVEAPSN0 LVEAPSN1 LVEAPSN1 
00000EB0   PPEAPSN0 PPEAPSN0 PPEAPSN1 PPEAPSN1 
00000EC0   VGSAPSN0 VGSAPSN0 VGSAPSN1 VGSAPSN1 
00000ED0   VGDAPSN0 VGDAPSN0 VGDAPSN1 VGDAPSN1 
00000EE0   VGSA_LEN VGDA_LEN LTG_SIZE BBR__LEN 
00000EF0   BBR_PSN0 BBR_PSN0 RESERVED RESERVED
...
00000FF0   RESERVED RESERVED RESERVED RESERVED
*/



/*************************************************************************
 * Old LVM Record (32/128 PV)
 *************************************************************************
 */

struct lvm_rec_old {

        /* Validity field to determine if LVM record is valid (_LVM) */
        __long32_t lvm_id;

        /* VGID */
        struct unique_id vg_id;

        /* The length of the LVM reserved area */
        __long32_t lvmarea_len;

        /* Length of the volume group descriptor area */
        __long32_t vgda_len;

        /* The physical sector numbers of the beginning of the volume
         * group descriptor area copies on this disk */
        daddr32_t vgda_psn[2];

        /* The physical sector number of the beginning of a pool of
         * blocks (located at the end of the PV) which are reserved for
         * the relocation of bad blocks */
        daddr32_t reloc_psn;

        /* The length in number of sectors of the pool of bad block
         * relocation blocks */
        __long32_t reloc_len;

        /* The physical volume number within the volume group of this
         * physical volume */
        short int pv_num;

        /* The size in bytes for the partition, expressed as a power of
         * 2 (i.e., the partition size is 2 to the power pp_size) */
        short int pp_size;

        /* Length of the volume group status area */
        __long32_t vgsa_len;

        /* The physical sector numbers of the beginning of the volume
         * group status area copies on this disk */
        daddr32_t vgsa_psn[2];

        /* The version number of this volume group descriptor and status
         * area */
        short int version;

        /* Not used. */
        short int vg_type;

        /* The size in bytes for the LTG, expressed as a power of
         * 2 (i.e., the LTG size is 2 to the power ltg_shift) */
        int ltg_shift;

        char res1 [444];        /* reserved area */
};

/* Old LVM record layout
00000E00   LVM___ID VGID__W1 VGID__W2 VGID__W3
00000E10   VGID__W4 AREA_LEN VGDA_LEN VGDAPSN0
00000E20   VGDAPSN1 RELOCPSN RELOCLEN PVnmPPsh
00000E30   VGSA_LEN VGSAPSN0 VGSAPSN1 VERnTYPE
00000E40   LTG_SIZE RESERVED RESERVED RESERVED
00000E50   RESERVED RESERVED RESERVED RESERVED
...
00000FF0   RESERVED RESERVED RESERVED RESERVED
*/

#endif  /* _H_LVMREC */
