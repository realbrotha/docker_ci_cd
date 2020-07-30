/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/cdli_entuser.bent.h 1.4                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2003,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)68	1.4  src/bos/kernel/sys/cdli_entuser.bent.h, pcibent, bos53D, d2005_22A4 5/24/05 17:32:28 */

#ifndef _H_CDLI_ENTUSER_BENT
#define _H_CDLI_ENTUSER_BENT

/*
 *  Miscellaneous definitions
 */
#define ENT_BT_JUMBO_MAX_MTU	(9014)		/* jumbo packet max data size */
#define ENT_BT_PCI		0x0000000A	/* flag for device_type */
						/* field in ent_genstats */
#define ENT_UTP_PCI		0x0000000C	/* flag for Gigabit UTP */
						/* device_type */
#define ENT_BT_PCI_OTHER	0x00000010	/* flag for device_type */
						/* field in ent_genstats */    
						/* OTHER */
#define ENT_UTP_PCI_OTHER	0x00000011	/* flag for Gigabit UTP */
						/* device_type OTHER */
/*
 *  Gigabit Ethernet adapter (e414a816) device specific ndd_flags bits
 */
#define	NDD_BENT_32BIT		(16*NDD_SPECFLAGS) /* running in a 32bit slot */
#define	NDD_BENT_LINK_DOWN	(32*NDD_SPECFLAGS) /* link is down */
#define	NDD_BENT_AUTO_NEG	(64*NDD_SPECFLAGS) /* establish(ed) link by */
						   /* on: autonegotiate link */
						   /* off: force gigabit and */
					           /* full duplex */
/*
 *  Gigabit Ethernet adapter (e414a816) device specific statistics
 */
struct bent_stats {
	uint	tx_timeout_rtn;		/* # of entries to timeout routine */
	uint	link_negotiated;	/* negotiated link status */
	int	coll_freq[16];		/* Frequency of no. of collisions */
	uint	speed_selected;		/* Selected speed and mode */
	uint	device_type;		/* Device type to display UTP */
					/* or Fiber adapter statistics */ 
#define	NDD_BENT_LNK_UP	    		0x80000000  /* link is operational    */
#define NDD_BENT_LNK_ENABLE	    	0x40000000  /* enable link */
#define NDD_BENT_LNK_NEGOTIATE	    	0x20000000  /* enable autonegotiation */
#define NDD_BENT_LNK_RX_FLOW_CTL_Y 	0x00800000  /* do RX flow control */
#define NDD_BENT_LNK_TX_FLOW_CTL_Y 	0x00200000  /* do TX flow control */
#define NDD_BENT_LNK_HALF_DUPLEX   	0x00100000  /* half duplex */
#define NDD_BENT_LNK_FULL_DUPLEX   	0x00080000  /* full duplex */
#define NDD_BENT_LNK_1000MB	    	0x00040000  /* 1000 megabit data rate */
#define NDD_BENT_LNK_100MB	    	0x00020000  /* 100 megabit data rate */
#define NDD_BENT_LNK_10MB	    	0x00010000  /* 10 megabit data rate */

#ifndef	MEDIA_10_HALF
#define MEDIA_10_HALF			(0) 	/* 10 Mbps Half Duplex 	*/
#define MEDIA_10_FULL			(1)	/* 10 Mbps Full Duplex 	*/
#define MEDIA_100_HALF  		(2)	/* 100 Mbps Half Duplex */
#define MEDIA_100_FULL			(3) 	/* 100 Mbps Full Duplex */
#define MEDIA_AUTO			(4)	/* Autonegotiation 	*/
#define MEDIA_1000_FULL			(5) 	/* 1000 Mbps Full Duplex*/
#endif
};
typedef struct bent_stats bent_stats_t;

struct bent_all_stats {
	struct	ndd_genstats ent_ndd_stats;	/* network generic stats  */
	struct	ent_genstats ent_gen_stats;	/* ethernet generic stats */
	struct	bent_stats  bent_stats;		/* device specific stats  */
};
typedef struct bent_all_stats bent_all_stats_t;

/*
 *  Gigabit ethernet adapter (e414a816) trace hook numbers
 */
#define HKWD_BENT_XMIT			0x5B2	/* transmit events */
#define HKWD_BENT_RECV			0x5B3	/* receive events  */
#define HKWD_BENT_OTHER	 		0x5B4	/* other events    */

#endif  /* _H_CDLI_ENTUSER_BENT */
