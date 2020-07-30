/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/cdli_entuser.ment.h 1.5                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2005,2007          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)55	1.5  src/bos/kernel/sys/cdli_entuser.ment.h, pciment, bos53L, l2007_08C0 2/19/07 17:00:33 */

#ifndef _H_CDLI_ENTUSER_MENT
#define _H_CDLI_ENTUSER_MENT

/*
 *  Miscellaneous definitions
 */
#define ENT_MT_JUMBO_MAX_MTU	(9014)		/* jumbo packet max data size */
#define ENT_MT_SX_PCI		0x0000000A	/* Gigabit Ethernet-SX PCI-X */
						/* (14101403) */
#define ENT_SM_SX_PCI		0x0000000B	/* Gigabit Ethernet-SX PCI-X */
						/* (14106703) */
#define ENT_MT_TX_PCI		0x0000000C	/* reserved for future use */

/*
 *  Gigabit Ethernet adapter (14101403) device specific ndd_flags bits
 */
#define	NDD_MENT_32BIT		(16*NDD_SPECFLAGS) /* running in a 32bit slot */
#define	NDD_MENT_LINK_DOWN	(32*NDD_SPECFLAGS) /* link is down */
#define	NDD_MENT_AUTO_NEG	(64*NDD_SPECFLAGS) /* establish(ed) link by */
						   /* on: autonegotiate link */
						   /* off: force gigabit and */
					           /* full duplex */
/*
 *  Gigabit Ethernet adapter (14101403) device specific statistics
 */
struct ment_stats {
	uint	tx_timeout_rtn;		/* # of entries to timeout routine */
	uint	link_negotiated;	/* negotiated link status */
	int	coll_freq[16];		/* Frequency of no. of collisions */
	uint	speed_selected;		/* Selected speed and mode */
	uint	device_type;		/* Device type to display UTP */
					/* or Fiber adapter statistics */ 
#define	NDD_MENT_LNK_UP	    		0x80000000  /* link is operational    */
#define NDD_MENT_LNK_ENABLE	    	0x40000000  /* enable link */
#define NDD_MENT_LNK_NEGOTIATE	    	0x20000000  /* enable autonegotiation */
#define NDD_MENT_LNK_RX_FLOW_CTL_Y 	0x00800000  /* do RX flow control */
#define NDD_MENT_LNK_TX_FLOW_CTL_Y 	0x00200000  /* do TX flow control */
#define NDD_MENT_LNK_HALF_DUPLEX   	0x00100000  /* half duplex */
#define NDD_MENT_LNK_FULL_DUPLEX   	0x00080000  /* full duplex */
#define NDD_MENT_LNK_1000MB	    	0x00040000  /* 1000 megabit data rate */
#define NDD_MENT_LNK_100MB	    	0x00020000  /* 100 megabit data rate */
#define NDD_MENT_LNK_10MB	    	0x00010000  /* 10 megabit data rate */

#ifndef	MEDIA_10_HALF
#define MEDIA_10_HALF			(0) 	/* 10 Mbps Half Duplex 	*/
#define MEDIA_10_FULL			(1)	/* 10 Mbps Full Duplex 	*/
#define MEDIA_100_HALF  		(2)	/* 100 Mbps Half Duplex */
#define MEDIA_100_FULL			(3) 	/* 100 Mbps Full Duplex */
#define MEDIA_AUTO			(4)	/* Autonegotiation 	*/
#define MEDIA_1000_FULL			(5) 	/* 1000 Mbps Full Duplex*/
#endif
        uint    xonrxc;                 /* # of XON packets received      */
        uint    xontxc;                 /* # of XON packets transmitted   */
        uint    xoffrxc;                /* # of XOFF packets received     */
        uint    xofftxc;                /* # of XOFF packets transmitted  */
        uint    tx_tcpseg;              /* # of TX TCP seg. offld packets */
};
typedef struct ment_stats ment_stats_t;

struct ment_all_stats {
	struct	ndd_genstats ent_ndd_stats;	/* network generic stats  */
	struct	ent_genstats ent_gen_stats;	/* ethernet generic stats */
	struct	ment_stats  ment_stats;		/* device specific stats  */
};
typedef struct ment_all_stats ment_all_stats_t;

/*
 *  Gigabit ethernet adapter (14101403) trace hook numbers
 */
#define HKWD_MENT_XMIT			0x4C5	/* transmit events */
#define HKWD_MENT_RECV			0x4C6	/* receive events  */
#define HKWD_MENT_OTHER	 		0x4C7	/* other events    */

#endif  /* _H_CDLI_ENTUSER_MENT */
