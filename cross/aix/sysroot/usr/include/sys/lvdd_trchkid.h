/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53N src/bos/kernel/sys/lvdd_trchkid.h 1.2                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 2007                   */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)73        1.2  src/bos/kernel/sys/lvdd_trchkid.h, sysxlvm, bos53N, n2007_34A8 8/3/07 15:03:01 */

#ifndef _H_LVDD_TRCHKID_H
#define _H_LVDD_TRCHKID_H

/*
 *--------------------------------------------------------------------
 * LVM Trace sub-hook definitions.
 * LVM trace hooks are defined in trchkid.h. 
 */

/* General LVM sub-hooks ( hook 105)  */
#define hkwd_LVM_RELOCINGBLK     1      /* Encountered relocated blk      */
#define hkwd_LVM_OLDBADBLK       2      /* Old bad block                  */
#define hkwd_LVM_BADBLKDONE      3      /* Blk relocation complete        */
#define hkwd_LVM_NEWBADBLK       4      /* New bad block found            */
#define hkwd_LVM_SWRELOC         5      /* Software relocating bad blk    */
#define hkwd_LVM_RESYNCPP        6      /* Resyncing LP mirrors           */
#define hkwd_LVM_OPEN            7      /* LV open                        */
#define hkwd_LVM_CLOSE           8      /* LV close                       */
#define hkwd_LVM_READ            9      /* LV character device read       */
#define hkwd_LVM_WRITE          10      /* LV character device write      */
#define hkwd_LVM_IOCTL          11      /* LVM device driver ioctl        */
#define hkwd_LVM_UPD_BBDIR      12      /* Update BB directory. pb queued */
#define hkwd_LVM_BBDIREND       13      /* Iodone for BB directory I/O    */
#define hkwd_LVM_BBDIROP        14      /* Continue BB directory operation*/
#define hkwd_LVM_BBADD          15      /* Add BB directory entry on disk */
#define hkwd_LVM_BBDEL          16      /* Delete BB dir entry on disk    */
#define hkwd_LVM_BBUPD          17      /* Update BB dir entry on disk    */
#define hkwd_LVM_BBDIRDONE      18      /* Completion of BB dir updating  */
#define hkwd_LVM_CA_CHKCACH     19      /* check for a cache hit          */
#define hkwd_LVM_CA_CHKHIT      20      /* got a cache hit                */
#define hkwd_LVM_CA_WRT         21      /* start cache writes             */
#define hkwd_LVM_CA_WEND        22      /* cache write end                */
#define hkwd_LVM_MWCCWCOMP      23      /* MWCC write done. sched pending */
#define hkwd_LVM_CA_CLNUP       24      /* flush MWCC cache               */
#define hkwd_LVM_CA_TERM        25      /* logical cached request finished*/
#define hkwd_LVM_MVHLD          26      /* cache hold queue to pending    */


/* I/O sub-hooks  (hook 10B)  */
#define hkwd_LVM_PEND            1      /* End of physical request      X */
#define hkwd_LVM_PSTART          2      /* Start of physical request    X */
#define hkwd_LVM_LSTART          3      /* Start of logical request     X */
#define hkwd_LVM_RBLOCKED        4      /* request blocked - conflicts  X */
#define hkwd_LVM_LEND            5      /* End of logical request       X */
#define hkwd_LVM_IN_HDBEGIN	 6 
#define hkwd_LVM_IN_HDRESUME	 7 
#define hkwd_LVM_IN_HDSTART	 8 
#define hkwd_LVM_IN_STRATEGY	 9 


/* non-I/O sub-hooks (hook 393)  */
#define hkwd_LVM_CFG_CMD         1      /* LVM config cmd */
#define hkwd_LVM_SA_STRT         2      /* Put SA request on hold list */
#define hkwd_LVM_SA_CONT         3      /* continue writing VGSAs         */
#define hkwd_LVM_SA_WRT          4      /* split buf for next SA on wheel */
#define hkwd_LVM_SA_IODONE       5      /* iodone for VGSA write          */
#define hkwd_LVM_VGSA_DIO        6      /* vgsa parallel writes start     */
#define hkwd_LVM_VGSA_DIO_END    7      /* vgdsa parallel writes done     */
#define hkwd_LVM_SA_WHLADV       8      /* return vgsa done requestsr     */
#define hkwd_LVM_SA_RTN          9      /* return requests to callers     */
#define hkwd_LVM_SA_CONFIG      10      /* hd_config req for VGSA wheel   */
#define hkwd_LVM_SA_GS_READ     11      /* split buf for conc SA read     */
#define hkwd_LVM_SA_GS_IODONE   12      /* iodone for conc vgsa read      */
    

/* Config operation sub-hooks  (hook 5D4)  */
#define hkwd_LVM_CFG_VG          1 
#define hkwd_LVM_IN_KADDLV       2 
#define hkwd_LVM_OUT_KADDLV      3 
#define hkwd_LVM_IN_KCHGLV       4 
#define hkwd_LVM_OUT_KCHGLV      5 
#define hkwd_LVM_IN_KCHKLV       6 
#define hkwd_LVM_OUT_KCHKLV      7 
#define hkwd_LVM_IN_KEXTEND      8 
#define hkwd_LVM_OUT_KEXTEND     9 
#define hkwd_LVM_IN_GSEXTEND    10 
#define hkwd_LVM_OUT_GSEXTEND   11 
#define hkwd_LVM_IN_KREDUCE     12 
#define hkwd_LVM_OUT_KREDUCE    13 
#define hkwd_LVM_IN_GSREDUCE    14 
#define hkwd_LVM_OUT_GSREDUCE   15 
#define hkwd_LVM_IN_KMARKLV     16 
#define hkwd_LVM_OUT_KMARKLV    17 
#define hkwd_LVM_IN_KDELLV      18 
#define hkwd_LVM_OUT_KDELLV     19 
#define hkwd_LVM_IN_KADDMPV     20 
#define hkwd_LVM_OUT_KADDMPV    21 
#define hkwd_LVM_IN_KADDPV      22 
#define hkwd_LVM_OUT_KADDPV     23 
#define hkwd_LVM_IN_KCOPYBB     24 
#define hkwd_LVM_OUT_KCOPYBB    25 
#define hkwd_LVM_IN_KDELPV      26 
#define hkwd_LVM_OUT_KDELPV     27 
#define hkwd_LVM_IN_KCHGVGSA    28 
#define hkwd_LVM_OUT_KCHGVGSA   29 
#define hkwd_LVM_IN_CONFIG      30 
#define hkwd_LVM_OUT_CONFIG     31 
#define hkwd_LVM_IN_LVMCONFIG   32 
#define hkwd_LVM_OUT_LVMCONFIG  33 
#define hkwd_LVM_IN_VERIFYVGID  34 
#define hkwd_LVM_OUT_VERIFYVGID 35 
#define hkwd_LVM_IN_KDEFLVS     36 
#define hkwd_LVM_OUT_KDEFLVS    37 
#define hkwd_LVM_IN_KSETUPVG    38 
#define hkwd_LVM_OUT_KSETUPVG   39 
#define hkwd_LVM_IN_MWC_FPREC   40 
#define hkwd_LVM_OUT_MWC_FPREC  41 
#define hkwd_LVM_IN_KDEFVG      42 
#define hkwd_LVM_OUT_KDEFVG     43 
#define hkwd_LVM_IN_KDELVG      44 
#define hkwd_LVM_OUT_KDELVG     45 
#define hkwd_LVM_IN_FREE_LVOLS  46 
#define hkwd_LVM_OUT_FREE_LVOLS 47 
#define hkwd_LVM_IN_KCHGQRM     48 
#define hkwd_LVM_OUT_KCHGQRM    49 
#define hkwd_LVM_IN_KQRYVGS     50 
#define hkwd_LVM_OUT_KQRYVGS    51 
#define hkwd_LVM_IN_KREBUILD    52 
#define hkwd_LVM_OUT_KREBUILD   53 
#define hkwd_LVM_IN_KVGSTAT     54 
#define hkwd_LVM_OUT_KVGSTAT    55 
#define hkwd_LVM_IN_CFG         56 
#define hkwd_LVM_OUT_CFG        57 
#define hkwd_LVM_IN_CON1016     58 
#define hkwd_LVM_OUT_CON1016    59 
#define hkwd_LVM_IN_EXT_DALV    60 
#define hkwd_LVM_OUT_EXT_DALV   61 
#define hkwd_LVM_ALLOC_SA       62 


/* Concurrent operation sub-hooks  (hook 5D5)  */
#define hkwd_LVM_CONC_DIST_CMD   1   /* distributed cmd */
#define hkwd_LVM_CONC_DCFG_CH    2   /* dev, msg_type, result */
#define hkwd_LVM_CONC_EVENT      3   /* dev, event, line */
#define hkwd_LVM_CONC_TS         4   /* dev, tv_sec, tv_nsec, line */
#define hkwd_LVM_CONC_VGSA_CH    5   /* dev, msg_type, result */


/* General debug sub-hooks  (hook 5D6)  */
#define hkwd_LVM_D_TOP           1  /* dev, event, line */


/*
 * Error event sub-hooks  (hook 5D7)
 *
 * These sub-hooks are currently file based -- one for each file in LVM DD.
 * The 1st parm is typically the devno of the device on which
 * the operation is being performed. The next 2 parms are
 * data items. These are often flags for the LV device and errno
 * respectively; however, this condition is not a hard fast rule.
 * The last parm must always be the line number in order to locate
 * the trace point in the file.
 */
#define hkwd_LVM_ERR_BBDIR       1  /* dev(data1), d2(flags), d3(errno), line */
#define hkwd_LVM_ERR_BBREL	 2  /* dev(data1), d2(flags), d3(errno), line */
#define hkwd_LVM_ERR_CFGLV       3  /* dev(data1), d2(flags), d3(errno), line */
#define hkwd_LVM_ERR_CFGPV       4  /* dev(data1), d2(flags), d3(errno), line */
#define hkwd_LVM_ERR_CFGVG       5  /* dev(data1), d2(flags), d3(errno), line */
#define hkwd_LVM_ERR_GS_CONC     6  /* dev(data1), d2(flags), d3(errno), line */
#define hkwd_LVM_ERR_MIRCACH	 7  /* dev(data1), d2(flags), d3(errno), line */
#define hkwd_LVM_ERR_PHYS	 8  /* dev(data1), d2(flags), d3(errno), line */
#define hkwd_LVM_ERR_SCHED       9  /* dev(data1), d2(flags), d3(errno), line */
#define hkwd_LVM_ERR_STRAT      10  /* dev(data1), d2(flags), d3(errno), line */
#define hkwd_LVM_ERR_TOP        11  /* dev(data1), d2(flags), d3(errno), line */
#define hkwd_LVM_ERR_VGSA       12  /* dev(data1), d2(flags), d3(errno), line */

#endif /* _H_LVDD_TRCHKID_H */
