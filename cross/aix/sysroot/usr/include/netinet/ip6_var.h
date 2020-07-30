/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernext/inet/ip6_var.h 1.18                             */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2003          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)17  1.18  src/bos/kernext/inet/ip6_var.h, sockinc, bos530 9/23/03 17:02:29 */
/*      $NetBSD: ip_var.h,v 1.10 1994/06/29 06:38:29 cgd Exp $  */

/*
 * Copyright (c) 1982, 1986, 1993
 *      The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      @(#)ip_var.h    8.1 (Berkeley) 6/10/93
 */

#ifndef _NETINET_IP6_VAR_H_
#define _NETINET_IP6_VAR_H_

/*
 * Overlay for IPv6 header used for checksum by other protocols.
 */
struct ip6ovck {
        u_int32_t ih6_wrd0;                     /* first word */
        union {
                u_int32_t ihuw6_wrd1;           /* second word */
                struct {
                        u_int8_t  ihu6_x;       /* reserved (0) */
                        u_int8_t  ihu6_pr;      /* protocol */
                        u_int16_t ihu6_len;     /* payload length */
                } ihus6_wrd1;
        } ihu6_wrd1;
};
#define ih6_wrd1        ihu6_wrd1.ihuw6_wrd1
#define ih6_x           ihu6_wrd1.ihus6_wrd1.ihu6_x
#define ih6_pr          ihu6_wrd1.ihus6_wrd1.ihu6_pr
#define ih6_len         ihu6_wrd1.ihus6_wrd1.ihu6_len


/*
 * IPv6 reassembly queue structure.  Each fragment
 * being reassembled is attached to one of these structures.
 * They are timed out after ipq_ttl drops to 0, and may also
 * be reclaimed if memory becomes tight.
 */
struct ip6q {
        struct    ip6q *next, *prev;    /* to other reass headers */
        u_int8_t  ip6q_ttl;             /* time for reass q to live */
        u_int8_t  ip6q_nh;              /* next header type of this fragment */
        u_int16_t ip6q_spare;           /* for alignment */
        u_int32_t ip6q_id;              /* sequence id for reassembly */
        struct    ip6asfrag *ip6q_next, *ip6q_prev;
                                        /* to IPv6 headers of fragments */
        struct    in6_addr ip6q_src, ip6q_dst;
        struct    mbuf *ip6q_mbuf;      /* pointer to the mbuf of this block */
};

/*
 * IPv6 header, when holding a fragment.
 *
 * Note: ip6f_next must be at same offset as ip6q_next above
 */
struct  ip6asfrag {
        u_int32_t ip6f_head;            /* next */
        u_int16_t ip6f_len;             /* prev */
        u_int8_t  ip6f_nh;
        u_int8_t  ip6f_hlim;
	union {
	  struct {
       	    void		*pad;		/* to align next and prev */
	    struct mbuf		*u_ip6f_mbuf;	/* pointer of this fragment */
	    struct ip6asfrag	*u_ip6f_next;	/* ip6q_next */
	    struct ip6asfrag	*u_ip6f_prev;	/* ip6q_prev */
	  } fp;
	  u_int8_t	pad32[32];		/* to align fields below */
	} fu;
        u_int8_t  ip6f_fnh;			/* fragment header */
        u_int8_t  ip6f_mff;
        u_int16_t ip6f_off;
        u_int32_t ip6f_id;
};

#define	ip6f_mbuf	fu.fp.u_ip6f_mbuf
#define	ip6f_next	fu.fp.u_ip6f_next
#define	ip6f_prev	fu.fp.u_ip6f_prev

struct  ip6stat {
        u_long  ip6s_total;             /* total packets received */
        u_long  ip6s_tooshort;          /* packet too short */
        u_long  ip6s_toosmall;          /* not enough data */
        u_long  ip6s_inomem;            /* no more memory on input */
        u_long  ip6s_fragments;         /* fragments received */
        u_long  ip6s_fragdropped;       /* fragments dropped */
        u_long  ip6s_fragtimeout;       /* fragments timed out */
        u_long  ip6s_forward;           /* packets forwarded */
        u_long  ip6s_cantforward;       /* packets rcvd for unreachable dest */
        u_long  ip6s_badsource;         /* packets rcvd from bad sources */
        u_long  ip6s_noproto;           /* unknown or unsupported protocol */
        u_long  ip6s_delivered;         /* datagrams delivered to upper level*/
        u_long  ip6s_inhist[256];       /* input histogram */
        u_long  ip6s_localout;          /* total ipv6 packets generated here */
        u_long  ip6s_onomem;            /* no more memory on output */
        u_long  ip6s_odropped;          /* lost packets due to nobufs, etc. */
        u_long  ip6s_reassembled;       /* total packets reassembled ok */
        u_long  ip6s_fragmented;        /* datagrams sucessfully fragmented */
        u_long  ip6s_ofragments;        /* output fragments created */
        u_long  ip6s_noroute;           /* packets discarded due to no route */
        u_long  ip6s_badvers;           /* ipv6 version != 6 */
        u_long  ip6s_rawout;            /* total raw ipv6 packets generated */
        u_long  ip6s_toobig;            /* not forwarded because size > MTU */
	u_long  ip6s_fullsock;		/* packet dropped by full raw socket */
	u_long  ip6s_rawcksum;		/* packets dropped for raw checksum failure */
};


/* distributed structure for IPv6 stats to fit in cache lines */

#define IP6_CACHE_LINE_SIZE 128

struct  dist_ip6stat {
        u_long  ip6s_total;             /* total packets received */
        u_long  ip6s_tooshort;          /* packet too short */
        u_long  ip6s_toosmall;          /* not enough data */
        u_long  ip6s_inomem;            /* no more memory on input */
        u_long  ip6s_fragments;         /* fragments received */
        u_long  ip6s_fragdropped;       /* fragments dropped */
        u_long  ip6s_fragtimeout;       /* fragments timed out */
        u_long  ip6s_forward;           /* packets forwarded */
        u_long  ip6s_cantforward;       /* packets rcvd for unreachable dest */
        u_long  ip6s_badsource;         /* packets rcvd from bad sources */
        u_long  ip6s_noproto;           /* unknown or unsupported protocol */
        u_long  ip6s_delivered;         /* datagrams delivered to upper level*/
        u_long  ip6s_inhist[256];       /* input histogram */
        u_long  ip6s_localout;          /* total ipv6 packets generated here */
        u_long  ip6s_onomem;            /* no more memory on output */
        u_long  ip6s_odropped;          /* lost packets due to nobufs, etc. */
        u_long  ip6s_reassembled;       /* total packets reassembled ok */
        u_long  ip6s_fragmented;        /* datagrams sucessfully fragmented */
        u_long  ip6s_ofragments;        /* output fragments created */
        u_long  ip6s_noroute;           /* packets discarded due to no route */
        u_long  ip6s_badvers;           /* ipv6 version != 6 */
        u_long  ip6s_rawout;            /* total raw ipv6 packets generated */
        u_long  ip6s_toobig;            /* not forwarded because size > MTU */
        u_long  ip6s_fullsock;          /* packet dropped by full raw socket */
	u_long  ip6s_rawcksum;          /* packets dropped for raw checksum failure */
	char    dummy[IP6_CACHE_LINE_SIZE -
	  sizeof(struct ip6stat) % IP6_CACHE_LINE_SIZE]; /* pad - cache  size */
};


#if defined(_KERNEL)

/* Struct to contain ancillary data for packet output */
struct ip6ancillary {
        struct in6_addr srcaddr;              	/* source address */
        struct ifaddr *ifa;                    	/* outgoing interface */
        u_char ttl;                           	/* ttl */
        u_char imo_multicast_ttl;             	/* multicast ttl */
	int flags;			     	/* flags indicating which data is set */
	int tclass;                             /* traffic class */
        int useminmtu;                          /* IPV6_USE_MIN_MTU */
        int dontfrag;                           /* IPV6_DONTFRAG */
        struct in6_addr nexthop;                /* IPV6_NEXTHOP */
        struct mbuf *exthdrs;                   /* IPV6_HOPOPTS,IPV6_RTHDR,
						 * IPV6_DSTOPTS,
						 * IPV6_RTHDRDSTOPTS */
};

#define CTRL_SRCADDR		0x01		/* source address was set */
#define CTRL_IFA		0x02		/* outgoing interface was set */
#define CTRL_UNICAST_HOPS	0x04		/* unicast ttl was set */
#define CTRL_MULTICAST_HOPS	0x08		/* multicast ttl was set */
#define CTRL_TCLASS             0x10            /* traffic class was set */
#define CTRL_USE_MIN_MTU        0x20            /* IPV6_USE_MIN_MTU was set */
#define CTRL_DONTFRAG           0x40            /* IPV6_DONTFRAG was set */
#define CTRL_NEXTHOP            0x80            /* IPV6_NEXTHOP was set */
#define CTRL_HDRS               0x100           /* Extension hdrs are set */

/* Internal flags for merging ancillary and sticky options */
#define FLG_HOPOPTS             0x01
#define FLG_RTHDRDSTOPTS        0x02
#define FLG_RTHDR               0x04
#define FLG_DSTOPTS             0x08

/* List of receivable extension header options */
#define HDR_CONTROLOPTS ((INP_RECVRTHDR|INP_RECVHOPOPTS|INP_RECVDSTOPTS))

/* Macro to allocate and initialize an ipv6_opts structure (if needed) */
#define ALLOC_V6OPTS_IF_NEEDED(p) { \
	if(!p) { \
        	p = (struct ipv6_opts *) net_malloc(sizeof(struct ipv6_opts), \
                                        M_TEMP, M_NOWAIT); \
        	if (p != NULL) { \
                	bzero(p, sizeof(struct ipv6_opts)); \
                	p->v6o_cksumoffset = -1; \
                	p->v6o_use_min_mtu = IPV6_USE_MIN_MTU_DEFAULT; \
        	} \
	} \
}

/*
 * MULTI_HOMED:
 *  0: no multi-homed support
 *  1: old (ie loose & buggy) multi-homed support
 *  2: strict (and correct) multi-homed support
 *  3: strict multi-homed and multi-sited support
 */


/* Lock for the ip6_rtexpire_isr_* queue */
extern simple_lock_data_t	ip6_rtexpire_isr_lock;
#define IP6RTEXPIRE_ISR_LOCKINIT()	{\
	lock_alloc(&ip6_rtexpire_isr_lock, LOCK_ALLOC_PIN, IP6RTEXPIRE_LOCK_FAMILY, -1);\
	simple_lock_init(&ip6_rtexpire_isr_lock);\
}
#define IP6RTEXPIRE_ISR_LOCK_DECL()	int	_ip6rtexpl;
#define IP6RTEXPIRE_ISR_LOCK()	_ip6rtexpl = disable_lock(PL_IMP, &ip6_rtexpire_isr_lock)
#define IP6RTEXPIRE_ISR_UNLOCK()	unlock_enable(_ip6rtexpl, &ip6_rtexpire_isr_lock)



/* The following definitions are used to manage the netisr that sends
 * Neighbor Solicitation packets. We need to do this in a netisr because
 * the IPv6 stack becomes too long otherwise.
 */
 
/* Lock for the ip6_ndsol6_isr* queue */
extern simple_lock_data_t       ip6_ndsol6_isr_lock;
#define IP6NDSOL6_ISR_LOCKINIT() {\
        lock_alloc(&ip6_ndsol6_isr_lock, LOCK_ALLOC_PIN, IP6NDSOL6_LOCK_FAMILY, -1);\
        simple_lock_init(&ip6_ndsol6_isr_lock);\
}
#define IP6NDSOL6_ISR_LOCK_DECL()     int     _ip6ndsol6expl;
#define IP6NDSOL6_ISR_LOCK() _ip6ndsol6expl=disable_lock(PL_IMP, &ip6_ndsol6_isr_lock)
#define IP6NDSOL6_ISR_UNLOCK()  unlock_enable(_ip6ndsol6expl, &ip6_ndsol6_isr_lock)


/* List element for list of NS packets to be sent */
struct ip6_nsentry {
        struct ip6_nsentry* next;       /* Linked list glue */
        struct mbuf *nspacket;          /* NS packet to be sent */
        struct ip_moptions *imo;        /* Mcast opts to pass to ip6_output*/
};

extern  simple_lock_data_t      ip6_frag_lock;
#define IP6FRAG_LOCKINIT()      {                                       \
        lock_alloc(&ip6_frag_lock, LOCK_ALLOC_PIN, IP6FRAG_LOCK_FAMILY, -1);\
        simple_lock_init(&ip6_frag_lock);               \
}
#define IP6FRAG_LOCK_DECL()     int     _ip6fl;
#define IP6FRAG_LOCK()          _ip6fl = disable_lock(PL_IMP, &ip6_frag_lock)
#define IP6FRAG_UNLOCK()                unlock_enable(_ip6fl, &ip6_frag_lock)

/* This flag is unused - it is never set */
#define IP6_DONTFRAG    0x4             /* ip6_outpt must not fragment */

#define IP6_INSOPT_NOALLOC      1
#define IP6_INSOPT_RAW          2

/* Kernel default values for Traffic Class */
#define IP6_TCLASS      0
#define MAXTCLASS       255
#define IP6_TCLASSMASK 0x0ff00000

/* Number of bits in the IPv6 Flow Label */
#define IP6_FLOWLABELBITS 20

/* Default value for IPV6_USE_MIN_MTU */
#define IPV6_USE_MIN_MTU_DEFAULT -1


/* Constants for IP6 input handlers. */
#define IP6_HANDLER_DONE  0
#define IP6_HANDLER_MORE  1
#define IP6_HANDLER_IPSEC 2

extern struct     ip6stat ip6stat;
extern struct     dist_ip6stat *dist_ip6stat[];
extern struct     ip6q ip6q[];            /* IPv6 reass. queue */
extern u_int32_t  ip6_id;               /* IPv6 packet ctr, for ids */
extern struct socket *ip6_mrouter;      /* multicast routing daemon */

extern long ip6printfs;
#define D6_INPUT        0x00000001
#define D6_CTLIN        0x00000002
#define D6_MCASTIN      0x00000004
#define D6_REASS        0x00000008
#define D6_OPTIN        0x00000010
#define D6_ETHERIN      0x00000020
#define D6_SITIN        0x00000040
#define D6_FORWARD      0x00000080
#define D6_OUTPUT       0x00000100
#define D6_CTLOUT       0x00000200
#define D6_MCASTOUT     0x00000400
#define D6_FRAG         0x00000800
#define D6_OPTOUT       0x00001000
#define D6_ETHEROUT     0x00002000
#define D6_SITOUT       0x00004000
#define D6_SITCTL       0x00008000
#define D6_INIT         0x00010000
#define D6_RAW          0x00020000
#define D6_NDP0         0x00040000
#define D6_NDP1         0x00080000
#define D6_UDP          0x00100000
#define D6_PMTU         0x00200000
#define D6_TCP0         0x00400000
#define D6_TCP1         0x00800000
#define D6_AH           0x01000000
#define D6_ESP          0x02000000
#define D6_KEY          0x04000000
#define D6_TUGCTL       0x10000000
#define D6_TUGIN        0x20000000
#define D6_TUGOUT       0x40000000


#endif

#endif
