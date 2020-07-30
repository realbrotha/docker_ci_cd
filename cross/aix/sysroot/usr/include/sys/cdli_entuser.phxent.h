/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/cdli_entuser.phxent.h 1.11                   */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/*
 *   COMPONENT_NAME: pciphxent
 *
 *   FUNCTIONS: phxent_all_stats_t
 *		phxent_stats_t
 *
 *   ORIGINS: 27
 *
 *                    -- (                            when
 *   combined with the aggregated modules for this product)
 *   OBJECT CODE ONLY SOURCE MATERIALS
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1996
 *   All Rights Reserved
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifndef _H_CDLI_ENTUSER_PHXENT
#define _H_CDLI_ENTUSER_PHXENT

/* PHY type constants */
#define UNKNOWN_PHY	  0		/* PHY type unknown (default)	*/
#define ENT_PHX_PHY	  1		/* PHY type for IBM 10/100 Mbps */
					/* integrated and non-integrated*/
					/* PCI Ethernet Adapter 	*/
#define ENT_CLVR_PHY	  2		/* PHY type for IBM 4-Port and 	*/
					/* integrated 2-Port 10/100 Mbps*/
					/* PCI Ethernet card		*/

/* device_type field in phxent_stats_t holds one of the following value */
#define ENT_PHX_PCI       0x00000009	/* IBM 10/100 Mbps PCI Ethernet	*/
					/*			Adapter */
#define ENT_CLVR_PCI	  0x0000000D    /* IBM 4-port 10/100 Mbps PCI	*/
					/*           Ethernet Adapter	*/
#define ENT_PHX_INT_PCI	  0x0000000E    /* IBM 10/100 Mbps Integrated	*/
					/*       PCI Ethernet Adapter	*/
#define ENT_CLVR_INT_PCI  0x0000000F    /* IBM 2-port 10/100 Mbps PCI	*/
					/*           Ethernet Adapter	*/

#define TP_PORT           0             /* twisted pair connector */

/* IBM 100 Mbps PCI Ethernet adapter specific statistics */
struct phxent_stats {
  int coll_freq[16];	      	/* Frequency of no. of collisions */
  __ulong32_t excessive_deferral;  /* # of packets that experience */
				   /* 	excess deferral		   */
  int link_status;            /* Twisted pair Link status */
  int media_speed;              /* Used to hold the network speed */
  int speed_selected;		/* Network speed selected */
  int ip_gap;			/* Inter packet gap */
  int ctl_restart;              /* Number of times adapter was restarted due */
				/* 	to an ioctl command */
  char chip_rev;                /* Used to hold the version id of the */
                                /* 	AMD chip */
  int rxbuf_pool_size;          /* Total number of mbufs pre-allocated to */
				/* the receive buffer pool. */ 
  int mapped_rxbuf_err;		/* Number of times the receive handler had */
				/* to get an mbuf from the system due */
				/* to running out of pre-allocated mbufs */
  int device_type;		/* Device type to display stats */
};
typedef struct phxent_stats phxent_stats_t;

struct phxent_all_stats {
        struct  ndd_genstats ent_ndd_stats;     /* network neneric stats */
        struct  ent_genstats ent_gen_stats;     /* ethernet generic stats */
        struct  phxent_stats phxent_stats;      /* device specific stats */
};
typedef struct phxent_all_stats phxent_all_stats_t;

/* IBM 10/100 Mbps ethernet adapter (phxent) trace hook numbers */
#define HKWD_PHXENT_XMIT		0x2E6		/* transmit events */
#define HKWD_PHXENT_RECV		0x2E7		/* receive events */
#define HKWD_PHXENT_OTHER		0x2E8		/* other events */

#ifndef	MEDIA_10_HALF
#define MEDIA_10_HALF           0
#define MEDIA_10_FULL           1
#define MEDIA_100_HALF          2
#define MEDIA_100_FULL          3
#define MEDIA_AUTO              4

/* Link Status */
#define LINK_UP           0
#define LINK_DOWN         1
#define LINK_LIMBO        2
#endif

#endif  /* _H_CDLI_ENTUSER_PHXENT */
