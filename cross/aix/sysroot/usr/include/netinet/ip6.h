/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernext/inet/ip6.h 1.10                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2004          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)16        1.10  src/bos/kernext/inet/ip6.h, sockinc, bos530 3/24/04 14:25:37 */
#ifndef _NETINET_IP6_H_
#define _NETINET_IP6_H_

/*
 * Definitions for internet protocol version 6.
 * Per RFC 1883
 */

/*
 * Structure of an IPv6 (first) header.
 * RFC3542 uses the name ip6_hlim for another purpose later in this file.
 * Hence we have changed this name in struct ipv6 to be ip6_hlimit.
 * Any older applications that use this name in struct ipv6 will need to
 * define the IP6_PRERFC3542 flag in order to compile successfully.
 */

struct ipv6 {
	u_int32_t ip6_head;		/* version and flow label */
	u_int16_t ip6_len;		/* payload length */
	u_int8_t  ip6_nh;		/* next header */
#ifdef IP6_PRERFC3542
	u_int8_t  ip6_hlim;		/* hop limit */
#else
	u_int8_t  ip6_hlimit;  		/* hop limit */
#endif

	struct    in6_addr ip6_src;	/* source address */
	struct	  in6_addr ip6_dst;	/* destination address */
};

#define IP6_MMTU	1280		/* minimal MTU and reassembly */

/*
 * Definitions of next header field values.
 */

#define IP6_NHDR_HOP	0	/* hop-by-hop IPv6 header */
#define IP6_NHDR_RT	43	/* routing IPv6 header */
#define IP6_NHDR_FRAG	44	/* fragment IPv6 header */
#define IP6_NHDR_ESP	50	/* encryption IPv6 header */
#define IP6_NHDR_AUTH	51	/* authentication IPv6 header */
#define IP6_NHDR_NONH	59	/* no next header */
#define IP6_NHDR_DOPT	60	/* destination options IPv6 header */
#define IP6_NHDR_MH	135	/* mobility IPv6 header */


/* The foll is used for IPV6_RTHDRDSTOPTS. We will store this in the next
 * header field to indicate that this option is RTHDRDSTOPTS and not
 * just a normal DSTOPTS. The actual type is stored in the m_pkthdr.rcvif
 * field and it will be IP6_NHDR_DOPT for both of these.
 */
#define IP6_NHDR_DOPT1 	0x1


/* Macro to reverse an mbuf chain in place */
#define REVOPTSLIST(opts) {\
        if(*opts!=NULL) { \
                struct mbuf *prev, *curr, *next; \
                \
                prev=NULL; curr=*opts; next=(*opts)->m_next; \
                while(next != NULL) { \
                        curr->m_next = prev; \
                        prev = curr; \
                        curr = next; \
                        next = curr->m_next; \
                } \
                curr->m_next = prev; \
                *opts = curr; \
        }\
}


/*
 * Fragment Header.
 */

struct ipv6_fraghdr {
	u_int8_t  if6_nh;	/* next header */
	u_int8_t  if6_res;	/* reserved */
	u_int16_t if6_off;	/* offset */
#define IP6_MF 0x1		/* more flag */
#define IP6_OFFMASK 0xfff8	/* mask of real offset field */
	u_int32_t if6_id;	/* identifier */
};

/*
 * Hop-by-Hop Options Header.
 */

struct ipv6_h2hhdr {
	u_int8_t  ih6_nh;	/* next header */
	u_int8_t  ih6_hlen;	/* header extension length */
	u_int16_t ih6_pad1;	/* to 4 byte length */
	u_int32_t ih6_pad2;	/* to 8 byte length */
};

/*
 * Routing Header.
 */

struct ipv6_rthdr {
	u_int8_t  ir6_nh;	/* next header */
	u_int8_t  ir6_hlen;	/* header extension length */
	u_int8_t  ir6_type;	/* routing type */
#define IP6_LSRRT 0		/* type 0 */
#define IP6_MIPRT 2		/* type 2 for IPv6 mobility */
	u_int8_t  ir6_sglt;	/* index of next address */
	u_int32_t ir6_reserved;	/* not used for type 0 or 2 */
};

/*
 * Destination Options Header.
 */

struct ipv6_dopthdr {
	u_int8_t  io6_nh;	/* next header */
	u_int8_t  io6_hlen;	/* header extension length */
	u_int16_t io6_pad1;	/* to 4 byte length */
	u_int32_t io6_pad2;	/* to 8 byte length */
};

/*
 * Mobility Header.
 */

struct ipv6_mobhdr {
	u_int8_t  mh6_nh;	/* next header */
	u_int8_t  mh6_hlen;	/* header extension length */
	u_int8_t  mh6_type;	/* mobility header type */
	u_int8_t  mh6_reserved;	/* reserved field */
	u_int16_t mh6_sum;	/* mobility header checksum */
};

/*
 * Authentication Header.
 */

struct ipv6_authhdr {
	u_int8_t  ah6_nh;       /* next header */
	u_int8_t  ah6_hlen;     /* header extension length */
	u_int16_t ah6_pad;      /* to 4 byte length */
	u_int32_t ah6_spi;      /* security parameter index */
	u_int32_t ah6_seq;		/* sequence number (> 0: new) */
};

/*
 * Encryption Security Payload Header.
 */

struct ipv6_esphdr {
	u_int32_t esp6_spi;     /* security parameter index */
};

#define IP6_OPT_PAD1	0	/* one-byte pad option type */
#define IP6_OPT_PADN	1	/* N-byte pad option type */

/*
 * IPv6 implementation parameters.
 */
#define IP6FRAGTTL      120             /* time to live for frags, slowhz */

/*
 * Header structure of BSD advanced API
 */

#ifdef STEVENS_API

struct ip6hdr {
    union {
	struct ip6hdrctl {
	    u_int32_t	ctl6_flow;	/* 24 bits of flow-ID */
	    u_int16_t	ctl6_plen;	/* payload length */
	    u_int8_t	ctl6_nxt;	/* next header */
	    u_int8_t	ctl6_hlim;	/* hop limit */
	} un_ctl6;
	u_int8_t un_vfc;		/* 4 bits version, 4 bits priority */
    } ip6_ctlun;
    struct in6_addr ip6_src;		/* source address */
    struct in6_addr ip6_dst;		/* destination address */
};

#define	ip6_vfc		ip6_ctlun.un_vfc
#define ip6_flow	ip6_ctlun.un_ctl6.ctl6_flow
#define ip6_plen	ip6_ctlun.un_ctl6.ctl6_plen
#define ip6_nxt		ip6_ctlun.un_ctl6.ctl6_nxt
#ifndef IP6_PRERFC3542
#define ip6_hlim	ip6_ctlun.un_ctl6.ctl6_hlim
#endif
#define ip6_hops	ip6_ctlun.un_ctl6.ctl6_hlim

/* Hop-by-Hop options header */
struct ip6_hbh {
	u_int8_t	ip6h_nxt;   /* next header */
	u_int8_t	ip6h_len;   /* length in units of 8 octets */
	/* followed by options */
};

/* Destination options header */
struct ip6_dest {
	u_int8_t	ip6d_nxt;   /* next header */
	u_int8_t	ip6d_len;   /* length in units of 8 octets */
    /* followed by options */
};

/* Routing header */
struct ip6_rthdr {
	u_int8_t	ip6r_nxt;   /* next header */
	u_int8_t	ip6r_len;   /* length in units of 8 octets */
	u_int8_t	ip6r_type;  /* routing type */
	u_int8_t	ip6r_segleft;   /* segments left */
	/* followed by routing type specific data */
};

/* Type 0 Routing header */
struct ip6_rthdr0 {
	u_int8_t	ip6r0_nxt;  /* next header */
	u_int8_t	ip6r0_len;  /* length in units of 8 octets */
	u_int8_t	ip6r0_type; /* always zero */
	u_int8_t	ip6r0_segleft;  /* segments left */
	u_int8_t	ip6r0_reserved; /* reserved field */
	u_int8_t	ip6r0_slmap[3]; /* strict/loose bit map */
	struct in6_addr	ip6r0_addr[1];  /* up to 23 addresses */
};

/* Fragment header */
struct ip6_frag {
	u_int8_t	ip6f_nxt;   /* next header */
	u_int8_t	ip6f_reserved;  /* reserved field */
	u_int16_t	ip6f_offlg; /* offset, reserved, and flag */
	u_int32_t	ip6f_ident; /* identification */
};

#if BYTE_ORDER == BIG_ENDIAN
#define IP6F_OFF_MASK       0xfff8  /* mask out offset from _offlg */
#define IP6F_RESERVED_MASK  0x0006  /* reserved bits in ip6f_offlg */
#define IP6F_MORE_FLAG      0x0001  /* more-fragments flag */
#else /* BYTE_ORDER == LITTLE_ENDIAN */
#define IP6F_OFF_MASK       0xf8ff  /* mask out offset from _offlg */
#define IP6F_RESERVED_MASK  0x0600  /* reserved bits in ip6f_offlg */
#define IP6F_MORE_FLAG      0x0100  /* more-fragments flag */
#endif

#else 	/* STEVENS_API */
/* 
 * The following definitions are from RFC3542. 
 * These are the defaults, unless STEVENS_API is defined.
 */

struct ip6_hdr {
	union {
	   struct ip6_hdrctl {
		uint32_t ip6_un1_flow; /*4 bits version, 8 bits TC, 20 bits flow-ID*/
		uint16_t ip6_un1_plen; /* payload length */
		uint8_t  ip6_un1_nxt;  /* next header */
		uint8_t  ip6_un1_hlim; /* hop limit */
	   } ip6_un1;
	   uint8_t ip6_un2_vfc;     /* 4 bits version, top 4 bits tclass */
	} ip6_ctlun;
	struct in6_addr ip6_src;   /* source address */
	struct in6_addr ip6_dst;   /* destination address */
};

#define ip6_vfc   ip6_ctlun.ip6_un2_vfc
#define ip6_flow  ip6_ctlun.ip6_un1.ip6_un1_flow
#define ip6_plen  ip6_ctlun.ip6_un1.ip6_un1_plen
#define ip6_nxt   ip6_ctlun.ip6_un1.ip6_un1_nxt
#ifndef IP6_PRERFC3542
#define ip6_hlim  ip6_ctlun.ip6_un1.ip6_un1_hlim 
#endif

/* Hop-by-Hop options header */
struct ip6_hbh {
	uint8_t  ip6h_nxt;        /* next header */
	uint8_t  ip6h_len;        /* length in units of 8 octets */
	/* followed by options */
};

/* Destination options header */
struct ip6_dest {
	uint8_t  ip6d_nxt;        /* next header */
	uint8_t  ip6d_len;        /* length in units of 8 octets */
	/* followed by options */
};


/* Routing header */
struct ip6_rthdr {
	uint8_t  ip6r_nxt;        /* next header */
	uint8_t  ip6r_len;        /* length in units of 8 octets */
	uint8_t  ip6r_type;       /* routing type */
	uint8_t  ip6r_segleft;    /* segments left */
	/* followed by routing type specific data */
};


/* Type 0 Routing header */
struct ip6_rthdr0 {
	uint8_t  ip6r0_nxt;       /* next header */
	uint8_t  ip6r0_len;       /* length in units of 8 octets */
	uint8_t  ip6r0_type;      /* always zero */
	uint8_t  ip6r0_segleft;   /* segments left */
	uint32_t ip6r0_reserved;  /* reserved field */
	/* followed by up to 127 struct in6_addr */
};

/* Fragment header */
struct ip6_frag {
	uint8_t   ip6f_nxt;       /* next header */
	uint8_t   ip6f_reserved;  /* reserved field */
	uint16_t  ip6f_offlg;     /* offset, reserved, and flag */
	uint32_t  ip6f_ident;     /* identification */
};


/* AIX is big-endian */
#define IP6F_OFF_MASK       0xfff8  /* mask out offset from _offlg */
#define IP6F_RESERVED_MASK  0x0006  /* reserved bits in ip6f_offlg */
#define IP6F_MORE_FRAG      0x0001  /* more-fragments flag */

/* IPv6 options */
struct ip6_opt {
	uint8_t  ip6o_type;
	uint8_t  ip6o_len;
};

/*
 * The high-order 3 bits of the option type define the behavior
 * when processing an unknown option and whether or not the option
 * content changes in flight.
 */
#define IP6OPT_TYPE(o)        ((o) & 0xc0)
#define IP6OPT_TYPE_SKIP      0x00
#define IP6OPT_TYPE_DISCARD   0x40
#define IP6OPT_TYPE_FORCEICMP 0x80
#define IP6OPT_TYPE_ICMP      0xc0
#define IP6OPT_MUTABLE        0x20

#define IP6OPT_PAD1           0x00  /* 00 0 00000 */
#define IP6OPT_PADN           0x01  /* 00 0 00001 */
#define IP6OPT_JUMBO          0xc2  /* 11 0 00010 */
#define IP6OPT_NSAP_ADDR      0xc3  /* 11 0 00011 */
#define IP6OPT_TUNNEL_LIMIT   0x04  /* 00 0 00100 */
#define IP6OPT_ROUTER_ALERT   0x05  /* 00 0 00101 */


/* Jumbo Payload Option */
struct ip6_opt_jumbo {
	uint8_t  ip6oj_type;
	uint8_t  ip6oj_len;
	uint8_t  ip6oj_jumbo_len[4];
};
#define IP6OPT_JUMBO_LEN   6

/* NSAP Address Option */
struct ip6_opt_nsap {
	uint8_t  ip6on_type;
	uint8_t  ip6on_len;
	uint8_t  ip6on_src_nsap_len;
	uint8_t  ip6on_dst_nsap_len;
	/* followed by source NSAP */
	/* followed by destination NSAP */
};

/* Tunnel Limit Option */
struct ip6_opt_tunnel {
	uint8_t  ip6ot_type;
	uint8_t  ip6ot_len;
	uint8_t  ip6ot_encap_limit;
};

/* Router Alert Option */
struct ip6_opt_router {
	uint8_t  ip6or_type;
	uint8_t  ip6or_len;
	uint8_t  ip6or_value[2];
};

/* Router alert values (in network byte order) */

/* AIX is big-endian */
#define IP6_ALERT_MLD      0x0000
#define IP6_ALERT_RSVP     0x0001
#define  IP6_ALERT_AN      0x0002


#endif 	/* STEVENS_API */

#define IPPMTU6_HEADLOCK_DECL()	int _pmtu6sl;

#define PMTU6_HASH(sin6_addr) ((sin6_addr.s6_addr32[0] + \
                                sin6_addr.s6_addr32[1] + \
                                sin6_addr.s6_addr32[2] + \
                                sin6_addr.s6_addr32[3] ) % PMTU_HASHSZ)
extern struct pmtu_hashchn_head        pmtu6_hash_table[];

#define IPPMTU6_HEAD_LOCK_INIT()  { \
        int i ; \
        for ( i = 0 ; i < PMTU_HASHSZ ; i++ ) { \
                lock_alloc ( &(pmtu6_hash_table[i].pmtu_lock),LOCK_ALLOC_PIN,IPPMTU_LOCK_FAMILY, i ) ; \
                simple_lock_init ( &(pmtu6_hash_table[i].pmtu_lock)) ; \
        } \
}

#define IPPMTU6_HEAD_LOCK(index) _pmtu6sl = \
                                disable_lock(PL_IMP,\
                        &(pmtu6_hash_table[index].pmtu_lock))

#define IPPMTU6_HEAD_UNLOCK(index) unlock_enable(_pmtu6sl,\
                        &(pmtu6_hash_table[index].pmtu_lock))
#endif
