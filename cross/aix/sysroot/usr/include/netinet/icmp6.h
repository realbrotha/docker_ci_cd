/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernext/inet/icmp6.h 1.5                                */
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
/* @(#)69	1.5  src/bos/kernext/inet/icmp6.h, sysxinet_ipv6, bos530 9/23/03 17:02:39 */
#ifndef _NETINET_ICMP6_H_
#define _NETINET_ICMP6_H_

/*
 * Header for the BSD advanced API
 */

struct icmp6_hdr {
    u_int8_t		icmp6_type;	/* type field */
    u_int8_t		icmp6_code;	/* code field */
    u_int16_t		icmp6_cksum;	/* checksum field */
    union {
	u_int32_t	icmp6_un_data32[1];	/* type-specific field */
	u_int16_t	icmp6_un_data16[2];	/* type-specific field */
	u_int8_t	icmp6_un_data8[4];	/* type-specific field */
    } icmp6_dataun;
};

#define icmp6_data32	icmp6_dataun.icmp6_un_data32
#define icmp6_data16	icmp6_dataun.icmp6_un_data16
#define icmp6_data8	icmp6_dataun.icmp6_un_data8
#define icmp6_pptr	icmp6_data32[0]	/* parameter prob */
#define icmp6_mtu	icmp6_data32[0]	/* packet too big */
#define icmp6_id	icmp6_data16[0]	/* echo request/reply */
#define icmp6_seq	icmp6_data16[1]	/* echo request/reply */
#define icmp6_maxdelay	icmp6_data16[0]	/* mcast group membership */

/*
 * The following definitions are compatible with RFC 3542.
 * They point to older definitions that AIX already shipped.
 */
#define ICMP6_DST_UNREACH       1
#define ICMP6_PACKET_TOO_BIG    2
#define ICMP6_TIME_EXCEEDED     3
#define ICMP6_PARAM_PROB        4

#define ICMP6_INFOMSG_MASK      0x80 	/*all informational messages*/

#define ICMP6_ECHO_REQUEST      128
#define ICMP6_ECHO_REPLY        129

#define ICMP6_DST_UNREACH_NOROUTE       0   /* no route to destination */
#define ICMP6_DST_UNREACH_ADMIN         1   /* communication with dest */
					    /* admin. prohibited */
#define ICMP6_DST_UNREACH_BEYONDSCOPE   2   /* beyond scope of source address */
#define ICMP6_DST_UNREACH_ADDR          3   /* address unreachable */
#define ICMP6_DST_UNREACH_NOPORT        4   /* port unreachable */

#define ICMP6_TIME_EXCEED_TRANSIT       0   /* Hop Limit == 0 in transit */
#define ICMP6_TIME_EXCEED_REASSEMBLY    1   /* Reassembly time out */

#define ICMP6_PARAMPROB_HEADER          0   /* erroneous header field */
#define ICMP6_PARAMPROB_NEXTHEADER      1   /* unrecognized Next Header */
#define ICMP6_PARAMPROB_OPTION          2   /* unrecognized IPv6 option */


/* ICMPV6 type definitions */
#define ICMPV6_DEST_UNREACH	ICMP6_DST_UNREACH
#define ICMPV6_PACKET_TOOBIG	ICMP6_PACKET_TOO_BIG
#define ICMPV6_TIME_EXCEEDED	ICMP6_TIME_EXCEEDED
#define ICMPV6_PARAMPROB	ICMP6_PARAM_PROB

#define ICMPV6_INFOMSG_MASK	ICMP6_INFOMSG_MASK

#define ICMPV6_ECHOREQUEST	ICMP6_ECHO_REQUEST
#define ICMPV6_ECHOREPLY	ICMP6_ECHO_REPLY
#define ICMPV6_MGM_QUERY	130
#define ICMPV6_MGM_REPORT	131
#define ICMPV6_MGM_REDUCTION	132

#define ICMPV6_DEST_UNREACH_NOROUTE	ICMP6_DST_UNREACH_NOROUTE
#define ICMPV6_DEST_UNREACH_ADMIN	ICMP6_DST_UNREACH_ADMIN
#define ICMPV6_DEST_UNREACH_NOTNEIGHBOR	ICMP6_DST_UNREACH_BEYONDSCOPE
#define ICMPV6_DEST_UNREACH_ADDR	ICMP6_DST_UNREACH_ADDR
#define ICMPV6_DEST_UNREACH_NOPORT	ICMP6_DST_UNREACH_NOPORT

#define ICMPV6_TIME_EXCEEDED_HOPS	ICMP6_TIME_EXCEED_TRANSIT
#define ICMPV6_TIME_EXCEEDED_REASSEMBLY	ICMP6_TIME_EXCEED_REASSEMBLY

#define ICMPV6_PARAMPROB_HEADER		ICMP6_PARAMPROB_HEADER
#define ICMPV6_PARAMPROB_NEXTHEADER	ICMP6_PARAMPROB_NEXTHEADER
#define ICMPV6_PARAMPROB_OPTION		ICMP6_PARAMPROB_OPTION

/* Neighbor Discovery Definitions */
#define ND6_ROUTER_SOLICITATION		133
#define ND6_ROUTER_ADVERTISEMENT	134
#define ND6_NEIGHBOR_SOLICITATION	135
#define ND6_NEIGHBOR_ADVERTISEMENT	136
#define ND6_REDIRECT			137



#define ND_ROUTER_SOLICIT               ND6_ROUTER_SOLICITATION
#define ND_ROUTER_ADVERT                ND6_ROUTER_ADVERTISEMENT
#define ND_NEIGHBOR_SOLICIT             ND6_NEIGHBOR_SOLICITATION
#define ND_NEIGHBOR_ADVERT              ND6_NEIGHBOR_ADVERTISEMENT
#define ND_REDIRECT                     ND6_REDIRECT


enum nd6_option {
	ND6_OPT_SOURCE_LINKADDR=1,
	ND6_OPT_TARGET_LINKADDR=2,
	ND6_OPT_PREFIX_INFORMATION=3,
	ND6_OPT_REDIRECTED_HEADER=4,
	ND6_OPT_MTU=5,
	ND6_OPT_ENDOFLIST=256
};

struct nd_router_solicit {	/* router solicitation */
    struct icmp6_hdr rsol_hdr;
};

#define rsol_type	rsol_hdr.icmp6_type
#define rsol_code	rsol_hdr.icmp6_code
#define rsol_cksum	rsol_hdr.icmp6_cksum
#define rsol_reserved	rsol_hdr.icmp6_data32[0]

#define nd_rs_hdr       rsol_hdr
#define nd_rs_type      nd_rs_hdr.icmp6_type
#define nd_rs_code      nd_rs_hdr.icmp6_code
#define nd_rs_cksum     nd_rs_hdr.icmp6_cksum
#define nd_rs_reserved  nd_rs_hdr.icmp6_data32[0]

struct nd_router_advert {	/* router advertisement */
    struct icmp6_hdr radv_hdr;
    u_int32_t	radv_reachable;		/* reachable time */
    u_int32_t	radv_retransmit;	/* reachable retransmit time */
};

#define radv_type		radv_hdr.icmp6_type
#define radv_code		radv_hdr.icmp6_code
#define radv_cksum		radv_hdr.icmp6_cksum
#define radv_maxhoplimit	radv_hdr.icmp6_data8[0]
#define radv_m_o_res		radv_hdr.icmp6_data8[1]
#define ND6_RADV_M_BIT	0x80
#define ND6_RADV_O_BIT	0x40
#define radv_router_lifetime	radv_hdr.icmp6_data16[1]

#define nd_ra_hdr               radv_hdr
#define nd_ra_reachable         radv_reachable
#define nd_ra_retransmit        radv_retransmit
#define nd_ra_type              nd_ra_hdr.icmp6_type
#define nd_ra_code              nd_ra_hdr.icmp6_code
#define nd_ra_cksum             nd_ra_hdr.icmp6_cksum
#define nd_ra_curhoplimit       nd_ra_hdr.icmp6_data8[0]
#define nd_ra_flags_reserved    nd_ra_hdr.icmp6_data8[1]
#define ND_RA_FLAG_MANAGED      0x80
#define ND_RA_FLAG_OTHER        0x40
#define nd_ra_router_lifetime   nd_ra_hdr.icmp6_data16[1]

struct nd6_nsolicitation {	/* neighbor solicitation */
    struct icmp6_hdr nsol6_hdr;
    struct in6_addr nsol6_target;
};


struct nd_neighbor_solicit {            /* neighbor solicitation */
	struct icmp6_hdr  nd_ns_hdr;
	struct in6_addr   nd_ns_target; /* target address */
	/* could be followed by options */
};

#define nd_ns_type               nd_ns_hdr.icmp6_type
#define nd_ns_code               nd_ns_hdr.icmp6_code
#define nd_ns_cksum              nd_ns_hdr.icmp6_cksum
#define nd_ns_reserved           nd_ns_hdr.icmp6_data32[0]


struct nd6_nadvertisement {	/* neighbor advertisement */
    struct icmp6_hdr nadv6_hdr;
    struct in6_addr nadv6_target;
};

#define nadv6_flags	nadv6_hdr.icmp6_data32[0]
#define ND6_NADVERFLAG_ISROUTER		0x80000000
#define ND6_NADVERFLAG_SOLICITED	0x40000000
#define ND6_NADVERFLAG_OVERRIDE		0x20000000

struct nd_neighbor_advert {             /* neighbor advertisement */
	struct icmp6_hdr  nd_na_hdr;
	struct in6_addr   nd_na_target; /* target address */
	/* could be followed by options */
};

#define nd_na_type               nd_na_hdr.icmp6_type
#define nd_na_code               nd_na_hdr.icmp6_code
#define nd_na_cksum              nd_na_hdr.icmp6_cksum
#define nd_na_flags_reserved     nd_na_hdr.icmp6_data32[0]
/* AIX is big endian */
#define ND_NA_FLAG_ROUTER        0x80000000
#define ND_NA_FLAG_SOLICITED     0x40000000
#define ND_NA_FLAG_OVERRIDE      0x20000000


struct nd6_redirect {		/* redirect */
    struct icmp6_hdr redirect_hdr;
    struct in6_addr redirect_target;
    struct in6_addr redirect_destination;
};

struct nd_redirect {           /* redirect */
	struct icmp6_hdr  nd_rd_hdr;
	struct in6_addr   nd_rd_target; /* target address */
	struct in6_addr   nd_rd_dst;    /* destination address */
	/* could be followed by options */
};

#define nd_rd_type               nd_rd_hdr.icmp6_type
#define nd_rd_code               nd_rd_hdr.icmp6_code
#define nd_rd_cksum              nd_rd_hdr.icmp6_cksum
#define nd_rd_reserved           nd_rd_hdr.icmp6_data32[0]


struct nd6_opt_hdr {     /* Neighbor discovery option header */
    u_int8_t    nd6_opt_type;
    u_int8_t    nd6_opt_len;     /* in units of 8 octets */
};


struct nd_opt_hdr {            /* Neighbor discovery option header */
	uint8_t  nd_opt_type;
	uint8_t  nd_opt_len;        /* in units of 8 octets */
	/* followed by option specific data */
};

#define ND_OPT_SOURCE_LINKADDR          1
#define ND_OPT_TARGET_LINKADDR          2
#define ND_OPT_PREFIX_INFORMATION       3
#define ND_OPT_REDIRECTED_HEADER        4
#define ND_OPT_MTU                      5

struct nd6_opt_prefix_info {	/* prefix information */
    u_int8_t	opt_type;
    u_int8_t	opt_length;
    u_int8_t	opt_prefix_length;
    u_int8_t	opt_l_a_res;
    u_int32_t	opt_valid_life;
    u_int32_t	opt_preferred_life;
    u_int32_t	opt_reserved2;
    struct in6_addr opt_prefix;
};

#define ND6_OPT_PI_L_BIT	0x80
#define ND6_OPT_PI_A_BIT	0x40

struct nd_opt_prefix_info {    /* prefix information */
	uint8_t   nd_opt_pi_type;
	uint8_t   nd_opt_pi_len;
	uint8_t   nd_opt_pi_prefix_len;
	uint8_t   nd_opt_pi_flags_reserved;
	uint32_t  nd_opt_pi_valid_time;
	uint32_t  nd_opt_pi_preferred_time;
	uint32_t  nd_opt_pi_reserved2;
	struct in6_addr  nd_opt_pi_prefix;
};

#define ND_OPT_PI_FLAG_ONLINK        0x80
#define ND_OPT_PI_FLAG_AUTO          0x40


struct nd6_opt_rd_hdr {  /* redirected header */
    u_int8_t    opt_rh_type;
    u_int8_t    opt_rh_len;
    u_int16_t   opt_rh_reserved1;
    u_int32_t   opt_rh_reserved2;
};

struct nd_opt_rd_hdr {         /* redirected header */
	uint8_t   nd_opt_rh_type;
	uint8_t   nd_opt_rh_len;
	uint16_t  nd_opt_rh_reserved1;
	uint32_t  nd_opt_rh_reserved2;
	/* followed by IP header and data */
};


struct nd6_opt_mtu {		/* MTU option */
    u_int8_t	opt_type;
    u_int8_t	opt_length;
    u_int16_t	opt_reserved;
    u_int32_t	opt_mtu;
};

struct nd_opt_mtu {            /* MTU option */
	uint8_t   nd_opt_mtu_type;
	uint8_t   nd_opt_mtu_len;
	uint16_t  nd_opt_mtu_reserved;
	uint32_t  nd_opt_mtu_mtu;
};


/* Multicast Listener Discovery Definitions */
#define MLD_LISTENER_QUERY          130
#define MLD_LISTENER_REPORT         131
#define MLD_LISTENER_REDUCTION      132

struct mld_hdr {
	struct icmp6_hdr  mld_icmp6_hdr;
	struct in6_addr   mld_addr; /* multicast address */
};
#define mld_type                 mld_icmp6_hdr.icmp6_type
#define mld_code                 mld_icmp6_hdr.icmp6_code
#define mld_cksum                mld_icmp6_hdr.icmp6_cksum
#define mld_maxdelay             mld_icmp6_hdr.icmp6_data16[0]
#define mld_reserved             mld_icmp6_hdr.icmp6_data16[1]


/* Router Renumbering Definitions */
#define ICMP6_ROUTER_RENUMBERING    138    /* router renumbering */

struct icmp6_router_renum {  /* router renumbering header */
	struct icmp6_hdr  rr_hdr;
	uint8_t           rr_segnum;
	uint8_t           rr_flags;
	uint16_t          rr_maxdelay;
	uint32_t          rr_reserved;
};
#define rr_type                  rr_hdr.icmp6_type
#define rr_code                  rr_hdr.icmp6_code
#define rr_cksum                 rr_hdr.icmp6_cksum
#define rr_seqnum                rr_hdr.icmp6_data32[0]

/* Router renumbering flags */
#define ICMP6_RR_FLAGS_TEST        0x80
#define ICMP6_RR_FLAGS_REQRESULT   0x40
#define ICMP6_RR_FLAGS_FORCEAPPLY  0x20
#define ICMP6_RR_FLAGS_SPECSITE    0x10
#define ICMP6_RR_FLAGS_PREVDONE    0x08

struct rr_pco_match {    /* match prefix part */
	uint8_t          rpm_code;
	uint8_t          rpm_len;
	uint8_t          rpm_ordinal;
	uint8_t          rpm_matchlen;
	uint8_t          rpm_minlen;
	uint8_t          rpm_maxlen;
	uint16_t         rpm_reserved;
	struct in6_addr  rpm_prefix;
};

/* PCO code values */
#define RPM_PCO_ADD              1
#define RPM_PCO_CHANGE           2
#define RPM_PCO_SETGLOBAL        3

struct rr_pco_use {    /* use prefix part */
	uint8_t          rpu_uselen;
	uint8_t          rpu_keeplen;
	uint8_t          rpu_ramask;
	uint8_t          rpu_raflags;
	uint32_t         rpu_vltime;
	uint32_t         rpu_pltime;
	uint32_t         rpu_flags;
	struct in6_addr  rpu_prefix;
};
#define ICMP6_RR_PCOUSE_RAFLAGS_ONLINK   0x20
#define ICMP6_RR_PCOUSE_RAFLAGS_AUTO     0x10

/* AIX is big-endian */
#define ICMP6_RR_PCOUSE_FLAGS_DECRVLTIME 0x80000000
#define ICMP6_RR_PCOUSE_FLAGS_DECRPLTIME 0x40000000

struct rr_result {    /* router renumbering result message */
	uint16_t         rrr_flags;
	uint8_t          rrr_ordinal;
	uint8_t          rrr_matchedlen;
	uint32_t         rrr_ifid;
	struct in6_addr  rrr_prefix;
};

/* AIX is big-endian */
#define ICMP6_RR_RESULT_FLAGS_OOB        0x0002
#define ICMP6_RR_RESULT_FLAGS_FORBIDDEN  0x0001


/* The following filter definitions are included in both ip6_icmp.h and icmp6.h
 * This is because one file is for kernel includes and the other for apps
 * Be sure to make any changes in both files
 */
#ifndef FILTERDEF
#define FILTERDEF
struct icmp6_filter {           /* ICMPv6 type filtering */
        uint32_t        icmp6_filt[8];          /* 8*32 = 256 bits */
};
 
#define ICMP6_FILTER_SETPASS(type, filterp) \
        (((filterp)->icmp6_filt[(type) >> 5]) |= (1 << ((type) & 31)))
#define ICMP6_FILTER_SETBLOCK(type, filterp) \
        (((filterp)->icmp6_filt[(type) >> 5]) &= ~(1 << ((type) & 31)))
#define ICMP6_FILTER_WILLPASS(type, filterp) \
        ((((filterp)->icmp6_filt[(type) >> 5]) & (1 << ((type) & 31))) != 0)
#define ICMP6_FILTER_WILLBLOCK(type, filterp) \
        ((((filterp)->icmp6_filt[(type) >> 5]) & (1 << ((type) & 31))) == 0)
#define ICMP6_FILTER_SETPASSALL(filterp) \
        memset(filterp, 0xff, sizeof(struct icmp6_filter))
#define ICMP6_FILTER_SETBLOCKALL(filterp) \
        memset(filterp, 0x00, sizeof(struct icmp6_filter))
 
#endif /* FILTERDEF */

#endif
