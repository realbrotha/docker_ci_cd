/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/net/if_arp.h 1.8.1.35                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1993          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)61	1.8.1.35  src/bos/kernel/net/if_arp.h, sockinc, bos53D, d2005_16B6 4/8/05 16:51:08 */
/*
 *   COMPONENT_NAME: SYSNET
 *
 *   FUNCTIONS: ACMULTI_LOCK
 *		ACMULTI_LOCKINIT
 *		ACMULTI_UNLOCK
 *		ARPTAB_HASH
 *		ARPTAB_LOCK
 *		ARPTAB_LOCKINIT
 *		ARPTAB_LOOK
 *		ARPTAB_UNLOCK
 *		
 *
 *   ORIGINS: 26,27,127,196
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1997
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/* Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#ifndef	_H_IF_ARP
#define	_H_IF_ARP

#ifdef __cplusplus
struct mbuf;
struct ifnet;
struct sockaddr;
struct driver_multi;
#endif

#include <netinet/in.h>

/*
 * Address Resolution Protocol.
 *
 * See RFC 826 for protocol description.  ARP packets are variable
 * in size; the arphdr structure defines the fixed-length portion.
 * Protocol type values are the same as those for 10 Mb/s Ethernet.
 * It is followed by the variable-sized fields ar_sha, arp_spa,
 * arp_tha and arp_tpa in that order, according to the lengths
 * specified.  Field names used correspond to RFC 826.
 */
struct	arphdr {
	u_short	ar_hrd;		/* format of hardware address */
#define ARPHRD_ETHER 	1	/* ethernet hardware address	*/
#define	ARPHRD_802_5	6	/* 802.5 hardware address	*/
#define	ARPHRD_802_3	6	/* 802.3 hardware address	*/
#define ARPHRD_FDDI	1	/* FDDI  hardware address	*/
	u_short	ar_pro;		/* format of protocol address */
	u_char	ar_hln;		/* length of hardware address */
	u_char	ar_pln;		/* length of protocol address */
	u_short	ar_op;		/* one of: */
#define	ARPOP_REQUEST	1	/* request to resolve address */
#define	ARPOP_REPLY	2	/* response to previous request */
/*
 * The remaining fields are variable in size,
 * according to the sizes above.
 */
/*	u_char	ar_sha[];	   sender hardware address */
/*	u_char	ar_spa[];	   sender protocol address */
/*	u_char	ar_tha[];	   target hardware address */
/*	u_char	ar_tpa[];	   target protocol address */
};

/*  arp_flags and at_flags field values */
#define	ATF_INUSE	0x01	/* entry in use */
#define ATF_COM		0x02	/* completed entry (enaddr valid) */
#define	ATF_PERM	0x04	/* permanent entry */
#define	ATF_PUBL	0x08	/* publish entry (respond for other host) */
#define	ATF_USETRAILERS	0x10	/* has requested trailers */
#define	ATF_ASK		0x20	/* arp request outstanding. */

union if_dependent {
	struct   token  {
		u_short	u_rcf;		/* route control field */
		u_short	u_seg[8];	/* routing info */
	} token;
	struct  x25 {
		u_short	u_session_id;	/* x.25 session id */
		u_short	u_unit;		/* unit number     */
	} x25;
	struct fddi {
		u_short u_rcf;		/* route control field 	*/
		u_short u_seg[16];	/* routing info 	*/
	} fddi;
};

#define  MAX_HWADDR		20
/* The following defines specify the action to be 
 * performed by function arpupdate. This function is
 * called by the IF layer code when it receives arp request
 * or reply */
#define  LOOK                   1
#define  LKPUB                  2
#define  UPDT                   3
#define  REVARP                 4

/* The following defines specify the return code for the
 * function arpresolve_common and arpupdate
 * */
#define  ARP_OK                 0  /* arpupdate */
#define  ARP_FAIL               1  /* arpupdate */
#define  ARP_NEWF               -1 /* arpresolve_common & arpupdate */
#define  ARP_MBUF               0  /* arpresolve_common */
#define  ARP_HWADDR             1  /* arpresolve_common */
#define  ARP_FLG_NOARP  		2  /* arpresolve_common */
/* The following defines specify whether it is a OLD or NEW
 * arptab entry when if_dependent data has to added/updated in the 
 * arptab by the function in IF layer.
 * */
#define  IF_DEP_NEW				1
#define  IF_DEP_OLD				2
/* The returns code for the function handling if_dependent data
 * in the IF layer.
 * */
#define  IF_OK					0
#define  IF_FAIL				1

/* arpupdate_parm structure which is used by the IF layer to pass
 * the required parameters for the function arpupdate */

struct  arpupdate_parm 
{
	struct in_addr	*isaddr; /* ptr for address for lookup/update/reverse arp */
	struct in_addr  *itaddr; /* ptr for target IP address */
	struct in_addr  *myaddr; /* ptr to IP address of receving interface */
	struct mbuf		**tmpmbuf; /* ptr to mbuf to be returned by arpupdate */
	union  if_dependent *if_dependent; /* ptr to if_dependent structure */
	u_char			*hwaddr; /* ptr to buffer for hardware address */
	int				szhwaddr; /* size of the hwaddr buffer */
	u_char 			*flags; /* ptr to flags to be returned by arpupdate */
	struct arptab	*at_addr; /* ptr to arptab entry. This should not be used for
								 accessing the arp entry. */
	int (*if_ifdependent) (caddr_t  hp, 
			union if_dependent *if_dependent, 
			int action); /* function ptr which handles if_dependent 
							data before update */
};



/*
 * Internet to link layer address resolution table.
 */
struct  arptab {
	struct	in_addr	at_iaddr;	/* internet address */
	u_char 		hwaddr[MAX_HWADDR];	/* hardware address */
	u_char		at_timer;	/* minutes since last reference */
	u_char		at_flags;	/* flags */
	u_short		at_count;	/* count of mbufs on at_hold */
	struct  mbuf    *at_hold;       /*first pkt in the list until resolved/timeout */
    struct  mbuf    *at_last;   /*last pkt in the list until resolved/timeout */
	struct 	ifnet	*at_ifp;	/* ifnet associated with entry */
	struct timestruc_t at_time;	/* time last request sent */
	u_int		at_requests;	/* requests sent since last timer pop */
	union if_dependent if_dependent;/* hdwr dependent info */
};

#define	at_enaddr	hwaddr
#define	at_traddr	hwaddr
#define	at_ie3addr	hwaddr
#define	at_x25addr	hwaddr
#define	at_fdaddr	hwaddr
#define	at_fcaddr	hwaddr

#define	at_rcf		if_dependent.token.u_rcf
#define	at_seg		if_dependent.token.u_seg
#define	at_session_id	if_dependent.x25.u_session_id
#define	at_x25unit	if_dependent.x25.u_unit
#define at_fddi_rcf	if_dependent.fddi.u_rcf
#define at_fddi_seg 	if_dependent.fddi.u_seg


#define MAX_ARP_RETRIES_PER_MINUTE 60

/*
 * ARP ioctl request
 */
struct	arpreq {
	struct	sockaddr	arp_pa;		/* protocol address */
	struct  sockaddr	arp_ha;		/* hardware address */
	int			arp_flags;	/* flags */
	u_short		at_length;		/* length of hardware address */
	union if_dependent ifd;			/* hdwr dependent info */
	__ulong32_t	ifType;				/* interface type */
};

#define	arp_rcf		ifd.token.u_rcf
#define	arp_seg		ifd.token.u_seg
#define	arp_session_id	ifd.x25.u_session_id
#define	arp_x25unit	ifd.x25.u_unit
#define arp_fddi_rcf	ifd.fddi.u_rcf
#define arp_fddi_seg 	ifd.fddi.u_seg

#define IN_USE  0x0001          /* interface entry in use when bit = = 1 */

/*
 * Structure shared between the ethernet driver modules and
 * the address resolution code.  For example, each ec_softc or il_softc
 * begins with this structure.
 */
struct  arpcom {
	struct  ifnet	ac_if;			/* network visible interface */
	u_char		ac_hwaddr[MAX_HWADDR];	/* hardware address */
	struct	in_addr ac_ipaddr;		/* copy of IP address */
	struct driver_multi *ac_multiaddrs;      /* list of multicast addrs */
	simple_lock_data_t	ac_multi_lock;   /* lock for walking list of 
							multicast addrs */
	struct	in6_addr ac_llip6;	/* link-local address */
};

#define ac_enaddr	ac_hwaddr
#define ac_traddr	ac_hwaddr
#define ac_fdaddr 	ac_hwaddr
#define ac_fcaddr 	ac_hwaddr

#define	ARPTAB_BSIZ	7		/* bucket size */
#define	ARPTAB_NB	149		/* number of buckets */

extern long	nlocks_per_arptabbuckets;

#ifdef _KERNEL
extern simple_lock_data_t *arptab_lock;

#define NET_CACHELINESIZE       128
/*
 * Including net_globals.h (where NET_CACHELINESIZE is defined) breaks nfs.
 * Hence we redefine NET_CACHELINESIZE here. These should be kept consistent.
 * This is also defined in in_var.h & in_pbc.h (because of build breaks
 * encountered when included through net_globals.h).
 */
#include <sys/lock_alloc.h>
#define DISTARPTAB_LOCKINIT()  { \
        int i ; \
        int cache_line_sz ; \
        int hlmem_sz ; \
        cache_line_sz = NET_CACHELINESIZE; \
        hlmem_sz = arptabnb * cache_line_sz ; \
        nlocks_per_arptabbuckets = cache_line_sz / sizeof ( simple_lock_data_t ) ; \
        arptab_lock = (simple_lock_data_t *) xmalloc ( hlmem_sz, 8, pinned_heap ) ; \
        for ( i = 0 ; i < arptabnb * nlocks_per_arptabbuckets ; i++ ) { \
                lock_alloc ( &(arptab_lock[i]), LOCK_ALLOC_PIN, ARPTAB_LOCK_FAMILY, i ) ; \
                simple_lock_init ( &(arptab_lock[i]) ) ; \
        } \
}
#define DISTARPTAB_LOCK(lockp)      s = disable_lock(PL_IMP,(&(lockp)));
#define DISTARPTAB_UNLOCK(lockp)    unlock_enable(s, (&(lockp)));

#define ARPTAB_LOCKINIT(lockp)  { \
        lock_alloc((lockp), LOCK_ALLOC_PIN, ARPTAB_LOCK_FAMILY, -1); \
        simple_lock_init((lockp)); \
}
#define ARPTAB_LOCK(lockp)      s = disable_lock(PL_IMP, (lockp));
#define ARPTAB_UNLOCK(lockp)    unlock_enable(s, (lockp));

extern struct arptab	*arptabp;
extern long		arptabbsiz;
extern long		arptabnb;
extern long		arptabsize;

extern long	arptab_bsiz;
extern long	arptab_bsiz_dflt;
extern long	arptab_nb;
extern long	arptab_nb_dflt;

extern long	arpqsize;
extern long	arpqsize_dflt;


#define	ARPTAB_HASH(a)		\
		((u_long)(a) % arptabnb)

#define	ARPTAB_LOOK(at, addr) {	\
		register int n;	\
		at = &arptabp[ARPTAB_HASH(addr) * arptabbsiz];	\
		for (n = 0 ; n < arptabbsiz ; n++, at++)	\
			if (at->at_iaddr.s_addr == addr)	\
				break;		\
		if  (n >= arptabbsiz)		\
			at = 0; \
}
#endif /* _KERNEL */

/* timer values */
#define	ARPT_AGE	(60 * 1)	/* aging timer, 1 min. */
#define	ARPT_KILLC	20		/* kill completed entry in 20 minutes */
#define	ARPT_KILLI	3		/* kill incomplete entry in 3 minutes */

#define  MAX_NASTIES  69	/* of course */

/*
 * Device driver multicast address structure.  There is one of these for each
 * multicast address or range of multicast addresses that we are supposed
 * to listen to on a particular interface.  They are kept in a linked list,
 * rooted in the interface's arpcom structure.  (This really has nothing to
 * do with ARP, or with the Internet address family, but this appears to be
 * the minimally-disrupting place to put it.)
 */
struct driver_multi {
	u_char              enm_addrlo[6];/* low  or only address of range */
	u_char              enm_addrhi[6];/* high or only address of range */
	struct arpcom      *enm_ac;	  /* back pointer to arpcom        */
	u_int               enm_refcount; /* no. claims to this addr/range */
	struct driver_multi *enm_next;	  /* ptr to next driver_multi       */
};

#define ACMULTI_LOCK_DECL()    int _acml;
#define ACMULTI_LOCK(acp)      _acml = disable_lock(PL_IMP, &((acp)->ac_multi_lock))
#define ACMULTI_UNLOCK(acp)    unlock_enable(_acml, &((acp)->ac_multi_lock))
#define ACMULTI_LOCKINIT(acp)  {					\
	lock_alloc(&((acp)->ac_multi_lock), LOCK_ALLOC_PIN, \
		ACMULTI_LOCK_FAMILY, (short32uint64_t)acp);	\
	simple_lock_init(&((acp)->ac_multi_lock));			\
}


struct en_softc
{
        struct arpcom   en_ac;
        struct ndd      *nddp;
};

#define en_if           en_ac.ac_if             /* network-visible interface */
#define en_addr         en_ac.ac_enaddr         /* hardware Ethernet address */

/*****************************************************************************
 *
 * FCS software status per interface.
 *
 * Each interface is referenced by a network interface structure,
 * fc_if, which the routing code uses to locate the interface.
 * This structure contains the hardware address, device handler file ptr
 *
 */
struct  fc_softc {
	struct arpcom   fc_ac;              /* FCS common part		   */
	struct ndd    *nddp;                /* returned from NS		   */
	int(*efcnet_arp_fct)
	     (struct ndd *, struct mbuf *); /* efcnet_arp function address */
} *fc_softc ;

#define fc_if           fc_ac.ac_if         /* visible for fcs interface   */
#define fc_addr         fc_ac.ac_fcaddr     /* hardware FCS address        */

#endif	/* _H_IF_ARP */
