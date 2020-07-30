/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/cdli_entuser.gxent.h 1.12                    */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1998,2003          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)27	1.12  src/bos/kernel/sys/cdli_entuser.gxent.h, pcigxent, bos530 4/2/03 12:58:08 */

#ifndef _H_CDLI_ENTUSER_GXENT
#define _H_CDLI_ENTUSER_GXENT

/*
 *  Miscellaneous definitions
 */
#define ENT_GX_JUMBO_MAX_MTU	(9014)		/* jumbo packet max data size */
#define ENT_GX_PCI		0x0000000A	/* flag for device_type
						   field in ent_genstats     */
#define ENT_UTP_PCI		0x0000000C	/* flag for Gigabit UTP
						   device_type */
#define ENT_GX_PCI_OTHER	0x00000010	/* flag for device_type
						   field in ent_genstats     
						   OTHER */
#define ENT_UTP_PCI_OTHER	0x00000011	/* flag for Gigabit UTP
						   device_type OTHER */
/*
 *  Gigabit Ethernet adapter (14100401) device specific ndd_flags bits
 */
#define	NDD_GXENT_32BIT		(16*NDD_SPECFLAGS) /* running in a 32bit slot */
#define	NDD_GXENT_LINK_DOWN	(32*NDD_SPECFLAGS) /* link is down */
#define	NDD_GXENT_AUTO_NEG	(64*NDD_SPECFLAGS) /* establish(ed) link by
						     on: autonegotiate link
						     off: force gigabit and
						          full duplex	     */
#define	NDD_GXENT_FW_TRACE	(128*NDD_SPECFLAGS) /* running with firmware
						      trace enabled */
#define	NDD_GXENT_FW_TRACED	(256*NDD_SPECFLAGS) /* firmware trace taken */

/*
 *  Gigabit Ethernet adapter (14100401) device specific statistics
 */
struct gxent_stats {
	uint	tx_timeout_rtn;		/* # of entries to timeout routine */
	uint	link_negotiated;	/* negotiated link status */
#define	NDD_GXENT_LNK_UP	    0x80000000  /* link is operational */
#define NDD_GXENT_LNK_ENABLE	    0x40000000  /* enable link */
#define NDD_GXENT_LNK_NEGOTIATE	    0x20000000  /* enable autonegotiation */
#define NDD_GXENT_LNK_RX_FLOW_CTL_Y 0x00800000  /* do RX flow control */
#define NDD_GXENT_LNK_TX_FLOW_CTL_Y 0x00200000  /* do TX flow control */
#define NDD_GXENT_LNK_HALF_DUPLEX   0x00100000  /* half duplex */
#define NDD_GXENT_LNK_FULL_DUPLEX   0x00080000  /* full duplex */
#define NDD_GXENT_LNK_1000MB	    0x00040000  /* 1000 megabit data rate */
#define NDD_GXENT_LNK_100MB	    0x00020000	/* 100 megabit data rate */
#define NDD_GXENT_LNK_10MB	    0x00010000	/* 10 megabit data rate */
	int	coll_freq[16];		/* Frequency of no. of collisions */
	uint    fw_major;		/* Firmware Release Major No. */
	uint	fw_minor;		/* Firmware Release Minor No. */
	uint	fw_fix;			/* Firmware Fix Level */
	uint	speed_selected;		/* Selected speed and mode */
#ifndef	MEDIA_10_HALF
#define MEDIA_10_HALF			(0) 	/* 10 Mbps Half Duplex */
#define MEDIA_10_FULL			(1)	/* 10 Mbps Full Duplex */
#define MEDIA_100_HALF  		(2)	/* 100 Mbps Half Duplex */
#define MEDIA_100_FULL			(3) 	/* 100 Mbps Full Duplex */
#define MEDIA_AUTO			(4)	/* Autonegotiation */
#endif
	uint	device_type;		/* Device type to display UTP */
					/* or Fiber adapter statistics */ 
};
typedef struct gxent_stats gxent_stats_t;

struct gxent_all_stats {
	struct	ndd_genstats ent_ndd_stats;	/* network generic stats */
	struct	ent_genstats ent_gen_stats;	/* ethernet generic stats */
	struct	gxent_stats  gxent_stats;	/* device specific stats */
};
typedef struct gxent_all_stats gxent_all_stats_t;

/*
 *  Gigabit ethernet adapter (14100401) trace hook numbers
 */
#define HKWD_GXENT_XMIT		0x2EA		/* transmit events */
#define HKWD_GXENT_RECV		0x2EB		/* receive events */
#define HKWD_GXENT_OTHER	0x2EC		/* other events */

#endif  /* _H_CDLI_ENTUSER_GXENT */
