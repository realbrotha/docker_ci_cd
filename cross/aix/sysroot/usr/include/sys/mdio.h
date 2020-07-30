/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53H src/bos/kernel/sys/mdio.h 1.63                                  */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1989,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)82       1.63  src/bos/kernel/sys/mdio.h, machdd, bos53H, h2006_08B1 2/17/06 15:46:09 */

#ifndef _H_MDIO
#define _H_MDIO


/*
 * COMPONENT_NAME: (MACHDD) Machine Device Driver
 */
#define NV_VERSION 1

typedef struct mdio {
    ulong md_addr;	/* specified address */
    __ulong32_t md_size;	/* size of md_data */
    int md_incr;	/* increment type: MV_BYTE, MV_WORD, MV_SHORT */
    char *md_data;	/* pointer to space of size md_size */
    int md_sla;		/* entry buid value, exit error code */
    __ulong32_t *md_length;	/* length of data read in user buffer */
} MACH_DD_IO;

typedef struct md_ioctl_handler {
    struct md_ioctl_handler *next;	/* So the kernel can chain handlers */
    int	(*handler)();			/* handler function */
#ifdef __cplusplus
    int32long64_t private_data;		/* handler's private data field */
#else
    int32long64_t private;		/* handler's private data field */
#endif /* __cplusplus */
    int32long64_t rsvd1;		/* reserved field */
    int32long64_t rsvd2;		/* reserved field */
    int32long64_t rsvd3;		/* reserved field */
} MACH_DD_IOCTL_HANDLER;

#define md_seqnum md_size
#define md_type md_addr
#define md_buid md_sla
#define md_slaerr md_sla
#define md_eenum md_sla
#define md_cbnum md_addr
#define md_cmd md_sla
#define md_dknum md_sla
#define md_mode md_addr
#define md_delay md_sla
#define md_cpunum md_addr

#define MV_BYTE		0	/* 8 bit access */
#define MV_WORD		1	/* 32 bit access */
#define MV_SHORT	2	/* 16 bit access */

/*
 * ioctl codes
 *
 */

/* As of AIX 5.2, all ioctls labeled with RS6K, POWER and Pr*P have been
 * deprecated for those particular machines.  ioctls that are labeled with
 * All or CHRP will still work for that platform.
 */

#define MIOBUSGET		0x1	/* All */
#define MIOBUSPUT		0x2	/* All */
#define MIOCCGET		0x3	/* RS6K and POWER */
#define MIOCCPUT		0x4	/* RS6K and POWER */
#define MIONVGET		0x5	/* RS6K and POWER */
#define MIONVPUT		0x6	/* RS6K and POWER */
#define MIOGETPS		0x7	/* All */
#define MIOGETKEY		0x8	/* All */
#define MIOBUSMEM		0x9	/* POWER */
#define MIOBUSIO		0xa	/* POWER */
#define MIONVTEST		0xb	/* Not used */
#define MIONVLED		0xc	/* All */
#define MIOAIPLCB		0xd	/* All */
#define MIOIPLCB		0xe	/* All */
#define MIONVCHCK		0xf	/* All */
#define MSLAGET			0x10	/* POWER */
#define MSLAPUT			0x11	/* POWER */
#define MIOTODGET		0x12	/* ALL */
#define MIOTODPUT		0x13	/* ALL */
#define MIOVPDGET		0x14	/* RS6K UP */
#define MIOCFGGET		0x15	/* RS6K UP */
#define MIOCFGPUT		0x16	/* RS6K UP */
#define MIORESET		0x17	/* RS6K UP */
#define MIOSETKEY		0x18	/* RS6K SMP */
#define MIONVSTRLED		0x19	/* RS6K SMP */
#define MEEPROMGET		0x1a	/* RS6K SMP */
#define MEEVPDGET		0x1b	/* RS6K SMP */
#define MEEVPDPUT		0x1c	/* RS6K SMP */
#define MFEPROMPUT		0x1d	/* RS6K SMP */
#define MPOWERGET		0x1e	/* RS6K SMP */
#define MPOWERSET		0x1f	/* RS6K SMP */
#define MRDSGET			0x20	/* RS6K SMP */
#define MRDSSET			0x21	/* RS6K SMP */
#define MSURVSET		0x22	/* RS6K SMP */
#define MSURVRESET		0x23	/* RS6K SMP */
#define MCPUSET			0x24	/* RS6K SMP */
#define MCPUGET			0x25	/* RS6K SMP */
#define MDINFOSET		0x26	/* RS6K SMP */
#define MDINFOGET		0x27	/* RS6K SMP */
#define MIOKEYCONNECT		0x28	/* RS6K SMP */
#define MIOKEYDISCONNECT	0x29	/* RS6K SMP */
#define MIOPCFGET		0x2a	/* PReP and CHRP */
#define MIOPCFPUT		0x2b	/* PReP and CHRP */
#define MIOMEMGET		0x2c	/* PReP and CHRP */
#define MIOMEMPUT		0x2d	/* PReP and CHRP */
#define MIOGEARD		0x2e	/* PReP and CHRP */
#define MIOGEAUPD		0x2f	/* PReP and CHRP */
#define MIOGEAST		0x30	/* PReP and CHRP */
#define MIOGEARDA		0x31	/* PReP and CHRP */
#define MIONVERRGET		0x32	/* All */
#define MIOHA			0x33	/* CHRP: common high availability */
					/*	related event handler */
#define MIORESIDPUT		0x34	/* All */
#define MIOTRACEGET		0x35	/* All */
#define MIOTRACEPUT		0x36	/* All */
#define MIOIPLCBPUT		0x37	/* All */

/*
 * The ioctls from 0x200 to 0x3ff are reserved for CHRP specific
 * ioctls implemented as part of the CHRP PAL.
 */

/*
 * The ioctls from 0x400 to 0xfff are reserved for OEM defined
 * ioctls for both PReP and CHRP.
 */

/*
 * Return code for a register machine driver ioctl extension that has handled
 * and ioctl but needs to return EINVAL for the handled ioctl.
 */
#define EINVAL_MD_EXT	-1

/* values of status for MRDSGET/MRDSSET */
#define MRDS_ON		1
#define MRDS_OFF	0

/* values of md_mode for MSURVSET */
#define MSOFT_RESET	1
#define MHARD_RESET	2

/* values of cpu status for MCPUSET/MCPUGET */
#define MCPU_START	0x9
#define MCPU_DISABLED	0xa
#define MCPU_ENABLED	0xb

/* values returned by MIONVCHK */
#define NVRAM_OK    0
#define NVRAM_RESET 1
#define NVRAM_BAD   2

/*
 *  Segment Regs
 *
 */

#define MIOMEMSYS	0x0
#define MIOMEMBUS	0x00020
#define MIOMEMRT	0x00060
#define MIOMEMADDR	0x40000


struct dsc_disk {
    char disk0;
};

struct dsc_native {
    char nat0;
    char nat1;
};

struct dsc_exp {
    char exp0;
    char exp1;
};

struct dsc_pvid {
    struct unique_id pvid;
};

struct dsc_scsi {
    char buid;		/* Bus ID */
    char loc;		/* location 'I' = Internal, 'E' = External */
    char slot;		/* slot number */
    char adp_sid;	/* adapter scsi ID */
    char type;		/* type ?? */
    char target_sid;	/* target device scsi ID */
    char lun;		/* lun ID */
};

struct dsc_pvscsi {
    struct unique_id pvid;
    char   stype;
    struct dsc_scsi d_scsi;
};

struct dsc_sla {
    uchar sla[5];
};

struct dsc_general {
    uchar gen;
};

struct devdesc {
    char   dsc_length;
    char   dsc_type;
    union {
	struct dsc_disk    d_disk;	/* type = 'N' */
	struct dsc_native  d_native;	/* type = 'K' */
	struct dsc_exp     d_exp;	/* type = 'R' */
	struct dsc_pvid    d_pvid;	/* type = 'V' */
	struct dsc_scsi    d_scsi;	/* type = 'S' */
	struct dsc_pvscsi  d_pvscsi;	/* type = 'V', length = 25 */
	struct dsc_sla     d_sla;	/* type = 'L' */
	struct dsc_general d_general;	/* type = 'G' */
    } dsc;
    char  dsc_unused[8];
};

struct drv_desc {
    ushort drv_magic;		/* ( 2) A5A5 */
    short  drv_length;		/* ( 2)  */
    __ulong32_t  drv_start;		/* ( 4)  */
    __ulong32_t  drv_crc;		/* ( 4)  */
    uchar  drv_unused0[12];	/* (12)  */
				/* (24) TOTAL */
};

struct ros_cb {
    __long32_t   rcb_unused0;		/* (   4)   0 */
    __long32_t   nv_size;		/* (   4)   4 */
    __long32_t   nv_version;		/* (   4)   8 */
    __long32_t   rcb_unused1;		/* (   4)   C */
    uchar  scsi_adap_id[16];	/* (  16)  10, 14, 18, 1C */
    __long32_t   mem_config[56];	/* ( 224)  20 - FC */
    uchar  mem_data[256];	/* ( 256) 100 - 1FC */
    struct devdesc prevdev;	/* (  36) 200 - 220 */
    uchar  norm_dev_list[84];	/* (  84) 224 - 274 */
    uchar  serv_dev_list[84];	/* (  84) 278 - 2C8 */
    struct drv_desc drv0;	/* (  24) 2CC - 2E0 */
    struct drv_desc drv1;	/* (  24) 2E4 - 2F8 */
    __ulong32_t  ros_crc;		/* (   4) 2FC */
				/* () */
};

struct gea_attrib {
    __long32_t   gea_length;		/* 4/0	num bytes in the GEArea	*/
    __long32_t   gea_used;		/* 4/4  num bytes used in the GEArea */
    __long32_t   gea_thresh;		/* 4/8  GEArea threshhold value */
};

/*
 * Macros
 *
 *      POSREG(p, slot) : returns addr appropriate for MACH_DD_IO md_addr
 *		p = POS Register number
 *           slot = card slot in microchannel
 */

/* things under ifdef OBSOLETE_MCA_PREP will be removed without notice in a
 * future release of AIX
 */
#ifdef OBSOLETE_MCA_PREP
#define POSREG(p, slot) (((slot) << 16) | (p))
#endif /* OBSOLETE_MCA_PREP */

#ifdef _KERNEL
#define NVQUERY 2
#define NVREAD  1
#define NVWRITE 0

/* Set offset into NVRAM block to zero for PAL enabled machines */
#define nvread(t,p,s,l)  nvrw(NVREAD,  t, p, s, l)
#define nvwrite(t,p,s,l) nvrw(NVWRITE, t, p, s, l)
#define nvquery(t)	 nvrw(NVQUERY, t, 0, 0, 0)

/* PReP and CHRP emulation of RS6K error log and dump info handling defines */
#define PREV_ERRLOG_SIZE 2100
#define ERRLOG_SIZE	2100   /* this needs to be deprecated */

extern int nvrw(int rbarw, int type, uchar *dptr, int dstart, int dlen);

/*
 * led display values are 0-9 for hex digits 0-9, and A-E are displayed below:
 * hex digit   '8'   '9'   'A'   'B'   'C'   'D'   'E'
 *             +--+  +--+              +  +  +--+  +
 *             |  |  |  |              |  |  |     |
 *             +--+  +--+  +--+  +--+  +--+  +--+  +--+
 *             |  |     |  |        |              |
 *             +--+     +  +--+  +--+        +--+  +--+
 * hex digit   '8'   '9'   'A'   'B'   'C'   'D'   'E'
 *
 * hex digit 'F' is blank, eg. '8F8' would display '8 8'
 */

/* 0<=ledvalue<=0xFFFF (only lower 3 nybbles significant) */
#endif /* _KERNEL */

#endif /* _H_MDIO */
