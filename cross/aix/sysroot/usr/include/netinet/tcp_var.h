/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernext/inet/tcp_var.h 1.14.3.65                        */
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
/* @(#)55       1.14.3.65  src/bos/kernext/inet/tcp_var.h, sysxinet_tcp, bos53L, l2006_45A4 10/23/06 15:23:52 */
/*
 *   COMPONENT_NAME: SYSXINET
 *
 *   FUNCTIONS: REASS_MBUF
 *              TCPMISC_LOCK
 *              TCPMISC_LOCKINIT
 *              TCPMISC_UNLOCK
 *              TCP_REXMTVAL
 *              intotcpcb
 *              inp2tcpcb
 *              sototcpcb
 *
 *
 *   ORIGINS: 26,27,85,90,127,196
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1997
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * (c) Copyright 1990, 1991, 1992, 1993 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * OSF/1 1.2
 */
/*
 * Copyright (C) 1988,1989 Encore Computer Corporation.  All Rights Reserved
 *
 * Property of Encore Computer Corporation.
 * This software is made available solely pursuant to the terms of
 * a software license agreement which governs its use. Unauthorized
 * duplication, distribution or sale are strictly prohibited.
 *
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *      Base:   tcp_var.h       7.8 (Berkeley) 6/29/88
 *      Merged: tcp_var.h       7.10 (Berkeley) 6/28/90
 */

/*
 * Kernel variables for tcp.
 */

#include <netinet/tcpip.h>

#ifndef _TCP_VAR_H_
#define _TCP_VAR_H_

#ifdef __cplusplus
struct tcpiphdr;
struct inpcb;
#endif

/*
 * Structures to use in implementing SACK - RFC2018.
 */
struct sackblk {
	tcp_seq start;			/* starting sequence in a sack block */
	tcp_seq end;			/* ending sequence in a sack block */
};
typedef struct sackblk SackBlk;
struct sackhole {
	tcp_seq start;			/* starting sequence of a hole */
	tcp_seq rxmit;			/* retransmitted sequence number */
	tcp_seq end;			/* ending sequence of a hole */
					/* start <= rxmit < end */
	short	dups;			/* number of dup. acks for this hole */
	unsigned int :16;		/* Pad out to 64-bit boundary. */
};
typedef struct sackhole SackHole;

/* INI_SACK_* values for 32-bit kernel only! */
#define INI_SACK_BLOCKS	  10

#define SEGS_ACKED(len, tp) ((len)/(tp)->t_maxseg+(((len)%(tp)->t_maxseg)?1:0))

#define INI_SACK_HOLES	  9

struct sackinfo {
	int max_sack_blocks;		/* initialized to INI_SACK_BLOCKS */
	int used_sack_blocks;		/* initialized to INI_SACK_HOLES  */
	int last_sack_block_updated;	/* index of block that must be output
					   next */
	int next_sack_block2send;	/* index of next additional block(s) to
					   be output next */
	tcp_seq highest_sacked;		/* 1 + highest byte SACKed */
	int max_sack_holes;
	int used_sack_holes;
	unsigned int :32;		/* Make sack_blocks[] start on 64-bit
					   boundary */
	SackBlk	 sack_blocks[INI_SACK_BLOCKS];
	SackHole sack_holes[INI_SACK_HOLES];
};
typedef struct sackinfo SackInfo;


/*
 * Tcp control block, one per tcp; fields:
 */
struct tcpcb {
	union {                         /* sequencing queue */
	        struct  tcpiphdr *seg_next_4;
	        struct  tcp6hdrs *seg_next_6;
	} tcpcb_next;
#define seg_next        tcpcb_next.seg_next_4
#define seg_next6       tcpcb_next.seg_next_6
	union {
	        struct  tcpiphdr *seg_prev_4;
	        struct  tcp6hdrs *seg_prev_6;
	} tcpcb_prev;
#define seg_prev        tcpcb_prev.seg_prev_4
#define seg_prev6       tcpcb_prev.seg_prev_6
	short   t_state;                /* state of this connection */
	short   t_softerror;            /* possible error not yet reported */
	short   t_timer[TCPT_NTIMERS];  /* tcp timers */
	short   t_rxtshift;             /* log(2) of rexmt exp. backoff */
	short   t_rxtcur;               /* current retransmit value */
	short   t_dupacks;              /* consecutive dup acks recd */
	u_int32 t_maxseg;               /* maximum segment size */
	u_int32 t_flags;
#define TF_ACKNOW	0x0001		/* ack peer immediately */
#define TF_DELACK	0x0002		/* ack, but try to delay it */
#define TF_NODELAY	0x0004		/* don't delay packets to coalesce */
#define TF_NOOPT	0x0008		/* don't use tcp options */
#define TF_SENTFIN	0x0010		/* have sent FIN */
#define TF_RFC1323	0x0020		/* Use RFC1323 TCP options */
#define TF_SENT_WS	0x0040		/* TCP has sent a windowscale option */
#define TF_RCVD_WS	0x0080		/* TCP has rcvd a windowscale option */
#define TF_SENT_TS	0x0100		/* TCP has sent a timestamp option */
#define TF_RCVD_TS	0x0200		/* TCP has rcvd a timestamp option */
#define TF_STDURG	0x0400		/* RFC 1122-compliant urgent handling */
#define TF_DELAY_ACK	0x0800		/* Delay because of delayackport opt */
#define TF_FASTRXMT_PHASE	0x1000	/* used when tcp_newreno is on */
#define TF_NEWRENO_RXMT		0x2000	/* used when tcp_newreno is on. Set
					 * on receiving a partial ACK after a
					 * fast retransmit that doesn't ACK
					 * everything upto snd_recover.
					 */
#define TF_SACK_PROCESS	 0x4000		/* SACK enabled on sender size -- RFC2018 */
#define TF_SACK_GENERATE 0x8000		/* SACK enabled on receiver side -- RFC2018 */
#define	TF_ECN					0x10000	/* ECN - rfc2481 */
#define	TF_SEND_ECHO			0x20000	/* Set ECN ECHO bit in the tcp header */
#define	TF_SEND_CWR				0x40000	/* Set ECN CWR  bit in the tcp header */
#define	TF_LARGESEND			0x80000		/* largesend capable connection */
#define	TF_NODELAYACK			0x100000	/* don't delay the ACKs */
#define	TF_DF					0x200000	/* don't set IP_DF flag */
/*
 * When tcp_output is in progress without holding the socket lock,
 * the below flag is set.
*/
#define	TF_SEND_INPROGRESS		0x400000
#define TF_CON_INPROGRESS		0x800000 /* connection in progress */
#define TF_NAGLEOVRD                    0x1000000 /*override nagle for one send*/

/* flags for TCP dynamic cksum offload enable/disable changes - defect 530194 */
#define TF_CKSUM_OFFLOAD1       0x2000000 /* Checksum offload capable connection */
#define TF_CKSUM_OFFLOAD2       0x4000000 /* Whether to use cksum offload for this connection */

/* Flags for virtual ethernet adapter's largesend */
#define TF_VIRTUAL_LARGESEND	0x8000000 /* Outgoing virtual ethernet supports largesend */
#define TF_SENT_LS		0x10000000 /* sent largesend option */
#define TF_RCVD_LS		0x20000000 /* received largesend option */

/*
 * Flag for enabling/disabling lower retransmission timer granularity for a connection
 */
#define TF_LOW_RTO          0x40000000


/* flags inherited from listening socket */
#define TF_COPYFLAGS	(TF_NODELAY|TF_RFC1323|TF_STDURG|TF_NODELAYACK)

	char    t_force;                /* 1 if forcing out a byte */
/* out-of-band data */
	char    t_oobflags;             /* have some */
	char    t_iobc;                 /* input character */
#define TCPOOB_HAVEDATA 0x01
#define TCPOOB_HADDATA  0x02

#define SACKGenerateEnabled(tp) ((tp)->t_flags & TF_SACK_GENERATE)
#define SACKProcessEnabled(tp)	((tp)->t_flags & TF_SACK_PROCESS)

	struct	tcptemp t_template;	/* skeletal packet for transmit
					 * (used to be mbuf)
					 */
	struct	inpcb *t_inpcb;		/* back pointer to internet pcb */
	tcp_seq t_timestamp;		/* used by slowtimo */
/*
 * The following fields are used as in the protocol specification.
 * See RFC783, Dec. 1981, page 21.
 */
/* send sequence variables */
	tcp_seq snd_una;                /* send unacknowledged */
	tcp_seq snd_nxt;                /* send next */
	tcp_seq snd_up;                 /* send urgent pointer */
	tcp_seq snd_wl1;                /* window update seg seq number */
	tcp_seq snd_wl2;                /* window update seg ack number */
	tcp_seq iss;                    /* initial send sequence number */
	u_long  snd_wnd;                /* send window */
/* receive sequence variables */
	u_long  rcv_wnd;                /* receive window */
	tcp_seq rcv_nxt;                /* receive next */
	tcp_seq rcv_up;                 /* receive urgent pointer */
	tcp_seq irs;                    /* initial receive sequence number */
/* RFC 1323 - variables */
	short   snd_wnd_scale;          /* snd window scale */
	short   rcv_wnd_scale;          /* rcv window scale */
	short   req_scale_sent;
	short   req_scale_rcvd;
	tcp_seq last_ack_sent;          /* seqno of last ACK sent (RTTM) */
	u_int	timestamp_recent;       /* most recent timestamp rcved (RTTM) */
	int     timestamp_age;          /* age of timestamp_recent */
/*
 * Additional variables for this implementation.
 */
/* receive variables */
	tcp_seq rcv_adv;                /* advertised window */
/* retransmit variables */
	tcp_seq snd_max;                /* highest sequence number sent;
	                                 * used to recognize retransmits
	                                 */
/* congestion control (for slow start, source quench, retransmit after loss) */
	u_long  snd_cwnd;               /* congestion-controlled window */
	u_long snd_ssthresh;            /* snd_cwnd size threshhold for
	                                 * slow start exponential to
	                                 * linear switch
	                                 */
/*
 * transmit timing stuff.  See below for scale of srtt and rttvar.
 * "Variance" is actually smoothed difference.
 */
	short	t_idle;			/* inactivity time */
	short	t_rtt;			/* round trip time */
	tcp_seq t_rtseq;		/* sequence number being timed */
	short	t_srtt;			/* smoothed round-trip time */
	short	t_rttvar;		/* variance in round-trip time */
	u_short t_rttmin;		/* minimum rtt allowed */
	u_long	max_rcvd;		/* most peer has sent into window */
	u_long	max_sndwnd;		/* largest window peer has offered */
	u_int32 t_peermaxseg;		/* peer maximum segment size */

	int snd_in_pipe;		/* used in Fast Retransmit and Timeout
					 * phases only always incremented on
					 * output reset to 0 before timeout
					 * retransmit set accordingly upon
					 * entering Fast Retransmit
					 */

/* pointer to SACK data structures: */
	SackInfo *sack_data;		/* non-NULL only after a SACK-enabled
					 * connection starts sending or
					 * receiving SACK blocks
					 */
	tcp_seq	snd_recover;		/* Records the highest sequence
					 * number transmitted (snd_max) when
					 * doing fast retransmit
					*/
	tcp_seq	snd_high;		/* Records the highest sequence
					 * number transmitted (snd_max) when
					 * retransmitting after a RTO
					*/
	tcp_seq	snd_ecn_max;		/* Records the highest sequence
					 * number transmitted (snd_max) when
					 * reacting to any form of congestion
					 * notification (FastRetransmit, ECN,
					 * SACK, RTO, ICMP Source Quench).
					 * Used for ECN.
					*/
	tcp_seq	snd_ecn_clear;		/* Used to detect if a retransmitted
					 * segment itself is dropped. In which
					 * case it is treated as a new 
					 * instance of congestion. Used for
					 * ECN.
					*/
	struct	tcpcb	*t_splice_with; /* points to the other connection of
					 * the splice.
					*/
	u_int32	t_splice_flags;
#define	SPLICE_EOF	1
#define	SPLICED_SOCK1	2

        struct twheel_timer *t_rxtimer; /* retransmission timer - uses timerwheel */

	short t_keepidle;		/* user-settable value of keepalive time
					 r */
	short t_keepintvl;		/*user-settable keepalive timer interval 					value */
	short t_keepcnt;		/* number of keepalive probes */	
	short t_badack;                 /* Number of invalid acks received */
	u_int timestamp_echo_recent;	/* most recent timestamp echo received */
};

#define HasSACKInfo(tp)	   ((tp)->sack_data != NULL)

#define SACKBlocksP(tp)	   (&((tp)->sack_data->sack_blocks[0]))
#define MaxSACKBlocks(tp)  ((tp)->sack_data->max_sack_blocks)
#define UsedSACKBlocks(tp) ((tp)->sack_data->used_sack_blocks)

#define FirstSACKBlock(tp) ((tp)->sack_data->last_sack_block_updated)
#define NextSACKBlock(tp)  ((tp)->sack_data->next_sack_block2send)
#define HighestUnSACKed(tp) ((tp)->sack_data->highest_sacked)

#define SACKHolesP(tp)	   ((SackHole *)&((tp)->sack_data->sack_blocks[MaxSACKBlocks(tp)]))
#define MaxSACKHoles(tp)   ((tp)->sack_data->max_sack_holes)
#define UsedSACKHoles(tp)  ((tp)->sack_data->used_sack_holes)

#define intotcpcb(ip)	((struct tcpcb *)(ip)->inp_ppcb)
#define sototcpcb(so)	(intotcpcb(sotoinpcb(so)))

#define inp2tcpcb(inp) (struct tcpcb *) ((struct inpcb *)(inp) + 1)


/*
 * The smoothed round-trip time and estimated variance
 * are stored as fixed point numbers scaled by the values below.
 * For convenience, these scales are also used in smoothing the average
 * (smoothed = (1/scale)sample + ((scale-1)/scale)smoothed).
 * With these scales, srtt has 3 bits to the right of the binary point,
 * and thus an "ALPHA" of 0.875.  rttvar has 2 bits to the right of the
 * binary point, and is smoothed with an ALPHA of 0.75.
 */
#define TCP_RTT_SCALE           8       /* multiplier for srtt; 3 bits frac. */
#define TCP_RTT_SHIFT           3       /* shift for srtt; 3 bits frac. */
#define TCP_RTTVAR_SCALE        4       /* multiplier for rttvar; 2 bits */
#define TCP_RTTVAR_SHIFT        2       /* multiplier for rttvar; 2 bits */

/*
 * The initial retransmission should happen at rtt + 4 * rttvar.
 * Because of the way we do the smoothing, srtt and rttvar
 * will each average +1/2 tick of bias.  When we compute
 * the retransmit timer, we want 1/2 tick of rounding and
 * 1 extra tick because of +-1/2 tick uncertainty in the
 * firing of the timer.  The bias will give us exactly the
 * 1.5 tick we need.  But, because the bias is
 * statistical, we have to test that we don't drop below
 * the minimum feasible timer (which is 2 ticks).
 * This macro assumes that the value of TCP_RTTVAR_SCALE
 * is the same as the multiplier for rttvar.
 */
#define TCP_REXMTVAL(tp) \
	(((tp)->t_srtt >> TCP_RTT_SHIFT) + (tp)->t_rttvar)

#define	TCP_INITIAL_WINDOW(init_window, mss)	\
	(((init_window) == 0) ? (MIN(4 * (mss), MAX(2 * (mss), 4380))) : \
	((mss) * (init_window)))

#ifndef __64BIT_KERNEL
/* XXX
 * We want to avoid doing m_pullup on incoming packets but that
 * means avoiding dtom on the tcp reassembly code.  That in turn means
 * keeping an mbuf pointer in the reassembly queue (since we might
 * have a cluster).  As a quick hack, the source & destination
 * port numbers (which are no longer needed once we've located the
 * tcpcb) are overlayed with an mbuf pointer.
 */
#define REASS_MBUF(ti) (*(struct mbuf **)&((ti)->ti_t))
#endif /* __64BIT_KERNEL */

/*
 * RFC 1323 - In the spirit of Header Prediction, we use this struct to
 *              check for the TS option.  If we match, then we avoid
 *              tcp_dooption() parsing...
 */
struct tcp_ts {
	u_int    ts_name;
	u_int    ts_val;
	u_int    ts_ecr;
};


/*
 * TCP statistics.
 * Many of these should be kept per connection,
 * but that's inconvenient at the moment.
 */
struct  tcpstat {
	u_long  tcps_connattempt;       /* connections initiated */
	u_long  tcps_accepts;           /* connections accepted */
	u_long  tcps_connects;          /* connections established */
	u_long  tcps_drops;             /* connections dropped */
	u_long  tcps_conndrops;         /* embryonic connections dropped */
	u_long  tcps_closed;            /* conn. closed (includes drops) */
	u_long  tcps_segstimed;         /* segs where we tried to get rtt */
	u_long  tcps_rttupdated;        /* times we succeeded */
	u_long  tcps_delack;            /* delayed acks sent */
	u_long  tcps_timeoutdrop;       /* conn. dropped in rxmt timeout */
	u_long  tcps_rexmttimeo;        /* retransmit timeouts */
	u_long  tcps_persisttimeo;      /* persist timeouts */
	u_long  tcps_keeptimeo;         /* keepalive timeouts */
	u_long  tcps_keepprobe;         /* keepalive probes sent */
	u_long  tcps_keepdrops;         /* connections dropped in keepalive */

	u_long  tcps_sndtotal;          /* total packets sent */
	u_long  tcps_sndpack;           /* data packets sent */
	u_long  tcps_sndbyte;           /* data bytes sent */
	u_long  tcps_sndrexmitpack;     /* data packets retransmitted */
	u_long  tcps_sndrexmitbyte;     /* data bytes retransmitted */
	u_long  tcps_sndacks;           /* ack-only packets sent */
	u_long  tcps_sndprobe;          /* window probes sent */
	u_long  tcps_sndurg;            /* packets sent with URG only */
	u_long  tcps_sndwinup;          /* window update-only packets sent */
	u_long  tcps_sndctrl;           /* control (SYN|FIN|RST) packets sent */

	u_long  tcps_rcvtotal;          /* total packets received */
	u_long  tcps_rcvpack;           /* packets received in sequence */
	u_long  tcps_rcvbyte;           /* bytes received in sequence */
	u_long  tcps_rcvbadsum;         /* packets received with ccksum errs */
	u_long  tcps_rcvbadoff;         /* packets received with bad offset */
	u_long  tcps_rcvshort;          /* packets received too short */
	u_long  tcps_rcvduppack;        /* duplicate-only packets received */
	u_long  tcps_rcvdupbyte;        /* duplicate-only bytes received */
	u_long  tcps_rcvpartduppack;    /* packets with some duplicate data */
	u_long  tcps_rcvpartdupbyte;    /* dup. bytes in part-dup. packets */
	u_long  tcps_rcvoopack;         /* out-of-order packets received */
	u_long  tcps_rcvoobyte;         /* out-of-order bytes received */
	u_long  tcps_rcvpackafterwin;   /* packets with data after window */
	u_long  tcps_rcvbyteafterwin;   /* bytes rcvd after window */
	u_long  tcps_rcvafterclose;     /* packets rcvd after "close" */
	u_long  tcps_rcvwinprobe;       /* rcvd window probe packets */
	u_long  tcps_rcvdupack;         /* rcvd duplicate acks */
	u_long  tcps_rcvacktoomuch;     /* rcvd acks for unsent data */
	u_long  tcps_rcvackpack;        /* rcvd ack packets */
	u_long  tcps_rcvackbyte;        /* bytes acked by rcvd acks */
	u_long  tcps_rcvwinupd;         /* rcvd window update packets */
	u_long  tcps_pawsdrop;          /* (RFC 1323) pkts dropped because
	                                        of PAWS */
#if     defined(_KERNEL) && LOCK_NETSTATS
	simple_lock_data_t tcps_lock;   /* statistics lock */
#endif
	u_long	tcps_pmturesends;	/* resends due to PMTU discovery */
	u_long	tcps_pmtuhalts;		/* PMTU discovery halts due to rexmit */
	u_long	tcps_timewaitreuse;	/* time waits reused */
	u_long	tcps_rcvbadhwsum;	/* packets received with bad HW
					   checksum */
	u_long	tcps_delayacksyn;	/* delayed ACKs for SYNs  */
	u_long	tcps_delayackfin;	/* delayed ACKs for FINs  */
	u_long	tcps_sendanddisc;	/* send_and_disconnect()s */
	u_long	tcps_upsackblocks;	/* times SACK blocks array is extended */
	u_long	tcps_upsackholes;	/* times SACK holes array is extended */
	u_long	tcps_predack;		/* times header prediction okay for acks */
	u_long	tcps_preddat;		/* times header prediction okay for data packets */
	u_long  tcps_persistdrop;	/* connection drops in persist state */
	u_long	tcps_badsyn;		/* invalid packet for LISTEN state */
	u_long	tcps_fastrxmt;		/* Van Jacobson's fast retransmits */
	u_long	tcps_newrenorxmt;	/* rfc2582(NewReno) fast retransmits */
	u_long	tcps_falsefastrxmt;	/* avoided false fast rxmts (NewReno) */
	u_long	tcps_odropped;		/* output pkts dropped due to memory 
					 * allocation failures
					*/
	u_long	tcps_splicedconns;	/* spliced connections */
	u_long	tcps_spliceclosed;	/* spliced connections closed */
	u_long	tcps_spliceresets;	/* spliced connections reset */
	u_long	tcps_splicetimeouts;	/* spliced connection timeouts */
	u_long	tcps_splicepersistdrops;/* spliced conns persist timeouts */
	u_long	tcps_splicekeepdrops;   /* spliced conns keepalive timeouts */
	u_long	tcps_ecnconns;		/* ECN capable connections */
	u_long	tcps_ecncwr;		/* Congestion Window Reduced bit set */ 
	u_long	tcps_ecnce;		/* CE bit set */
	u_long	tcps_ecncongestion;	/* responded to ECN */
	u_long	tcps_limitedtransmit;	/* fast retransmit assisted by 'limited
					   transmit' algorithm */
	u_long	tcps_largesend;		/* number of largesends */
	u_long	tcps_lsbytes;		/* total bytes sent through largesend*/
	u_long	tcps_lsmax;		/* biggest largesend done (in bytes)*/
	u_long	tcps_listendrop; 	/* SYNs dropped due to listener's queue full */
        u_long  tcps_autocksumoffload;  /* connections where cksum offload was 
					   dynamically disabled */
	u_long  tcps_badackconndrops;   /* Connections dropped due to bad ACKs */
	u_long  tcps_dupsynconndrops;   /* Connections dropped due to duplicate SYN packets */
};


struct dist_tcpstat  {
        u_long  tcps_connattempt;       /* connections initiated */
        u_long  tcps_accepts;           /* connections accepted */
        u_long  tcps_connects;          /* connections established */
        u_long  tcps_drops;             /* connections dropped */
        u_long  tcps_conndrops;         /* embryonic connections dropped */
        u_long  tcps_closed;            /* conn. closed (includes drops) */
        u_long  tcps_segstimed;         /* segs where we tried to get rtt */
        u_long  tcps_rttupdated;        /* times we succeeded */
        u_long  tcps_delack;            /* delayed acks sent */
        u_long  tcps_timeoutdrop;       /* conn. dropped in rxmt timeout */
        u_long  tcps_rexmttimeo;        /* retransmit timeouts */
        u_long  tcps_persisttimeo;      /* persist timeouts */
        u_long  tcps_keeptimeo;         /* keepalive timeouts */
        u_long  tcps_keepprobe;         /* keepalive probes sent */
        u_long  tcps_keepdrops;         /* connections dropped in keepalive */

        u_long  tcps_sndtotal;          /* total packets sent */
        u_long  tcps_sndpack;           /* data packets sent */
        u_long  tcps_sndbyte;           /* data bytes sent */
        u_long  tcps_sndrexmitpack;     /* data packets retransmitted */
        u_long  tcps_sndrexmitbyte;     /* data bytes retransmitted */
        u_long  tcps_sndacks;           /* ack-only packets sent */
        u_long  tcps_sndprobe;          /* window probes sent */
        u_long  tcps_sndurg;            /* packets sent with URG only */
        u_long  tcps_sndwinup;          /* window update-only packets sent */
        u_long  tcps_sndctrl;           /* control (SYN|FIN|RST) packets sent */

        u_long  tcps_rcvtotal;          /* total packets received */
        u_long  tcps_rcvpack;           /* packets received in sequence */
        u_long  tcps_rcvbyte;           /* bytes received in sequence */
        u_long  tcps_rcvbadsum;         /* packets received with ccksum errs */
        u_long  tcps_rcvbadoff;         /* packets received with bad offset */
        u_long  tcps_rcvshort;          /* packets received too short */
        u_long  tcps_rcvduppack;        /* duplicate-only packets received */
        u_long  tcps_rcvdupbyte;        /* duplicate-only bytes received */
        u_long  tcps_rcvpartduppack;    /* packets with some duplicate data */
        u_long  tcps_rcvpartdupbyte;    /* dup. bytes in part-dup. packets */
        u_long  tcps_rcvoopack;         /* out-of-order packets received */
        u_long  tcps_rcvoobyte;         /* out-of-order bytes received */
        u_long  tcps_rcvpackafterwin;   /* packets with data after window */
        u_long  tcps_rcvbyteafterwin;   /* bytes rcvd after window */
        u_long  tcps_rcvafterclose;     /* packets rcvd after "close" */
        u_long  tcps_rcvwinprobe;       /* rcvd window probe packets */
        u_long  tcps_rcvdupack;         /* rcvd duplicate acks */
        u_long  tcps_rcvacktoomuch;     /* rcvd acks for unsent data */
        u_long  tcps_rcvackpack;        /* rcvd ack packets */
        u_long  tcps_rcvackbyte;        /* bytes acked by rcvd acks */
        u_long  tcps_rcvwinupd;         /* rcvd window update packets */
        u_long  tcps_pawsdrop;          /* (RFC 1323) pkts dropped because
                                                of PAWS */
#if     defined(_KERNEL) && LOCK_NETSTATS
        simple_lock_data_t tcps_lock;   /* statistics lock */
#endif
        u_long  tcps_pmturesends;       /* resends due to PMTU discovery */
        u_long  tcps_pmtuhalts;         /* PMTU discovery halts due to rexmit */
        u_long  tcps_timewaitreuse;     /* time waits reused */
        u_long  tcps_rcvbadhwsum;       /* packets received with bad HW
                                           checksum */
        u_long  tcps_delayacksyn;       /* delayed ACKs for SYNs  */
        u_long  tcps_delayackfin;       /* delayed ACKs for FINs  */
        u_long  tcps_sendanddisc;       /* send_and_disconnect()s */
        u_long  tcps_upsackblocks;      /* times SACK blocks array is extended */
        u_long  tcps_upsackholes;       /* times SACK holes array is extended */
        u_long  tcps_predack;           /* times header prediction okay for acks
*/
        u_long  tcps_preddat;           /* times header prediction okay for data
packets */
        u_long  tcps_persistdrop;       /* connection drops in persist state */
        u_long  tcps_badsyn;            /* invalid packet for LISTEN state */
	u_long	tcps_fastrxmt;		/* Van Jacobson's fast retransmits */
	u_long	tcps_newrenorxmt;	/* rfc2582(NewReno) fast retransmits */
	u_long	tcps_falsefastrxmt;	/* avoided false fast rxmts (NewReno) */
	u_long	tcps_odropped;		/* output pkts dropped due to memory 
					 * allocation failures
					*/
	u_long	tcps_splicedconns;	/* spliced connections */
	u_long	tcps_spliceclosed;	/* spliced connections closed */
	u_long	tcps_spliceresets;	/* spliced connections reset */
	u_long	tcps_splicetimeouts;	/* spliced connection timeouts */
	u_long	tcps_splicepersistdrops;/* spliced conns persist timeouts */
	u_long	tcps_splicekeepdrops;   /* spliced conns keepalive timeouts */
	u_long	tcps_ecnconns;		/* ECN capable connections */
	u_long	tcps_ecncwr;		/* Congestion Window Reduced bit set */ 
	u_long	tcps_ecnce;		/* CE bit set */
	u_long	tcps_ecncongestion;	/* responded to ECN */
	u_long	tcps_limitedtransmit;	/* fast retransmit assisted by 'limited
					   transmit' algorithm */
	u_long	tcps_largesend;		/* number of largesends */
	u_long	tcps_lsbytes;		/* total bytes sent through largesend*/
	u_long	tcps_lsmax;		/* biggest largesend done (in bytes)*/
	u_long	tcps_listendrop; 	/* SYNs dropped due to listener's queue full */
        u_long  tcps_autocksumoffload;  /* connections where cksum offload was 
					   dynamically disabled */
	u_long  tcps_badackconndrops;   /* Connections dropped due to bad ACKs */
	u_long  tcps_dupsynconndrops;   /* Connections dropped due to duplicate SYN packets */
	char    dummy[IP_CACHE_LINE_SIZE -
	   (sizeof(struct tcpstat) % IP_CACHE_LINE_SIZE)]; /* pad cache size */
};


#ifdef _KERNEL

struct tcp_options_received {
	int     flags;
	uid_t   peer_uid;
	gid_t   peer_gid;
};

/* values for flags */
#define TIMESTAMP_RECEIVED 1
#define TCPAH_RECEIVED 2
#define SACK_RECEIVED 4

#define TCPACL_LOCKINIT()       {                                       \
	lock_alloc(&tcpacl.tcpa_lock, LOCK_ALLOC_PIN, TCPMISC_LOCK_FAMILY,-1); \
	simple_lock_init(&tcpacl.tcpa_lock);                            \
}
#define TCPACL_LOCK_DECL()      int     _tcpal;
#define TCPACL_LOCK()           simple_lock(&tcpacl.tcpa_lock)
#define TCPACL_UNLOCK()         simple_unlock(&tcpacl.tcpa_lock)

struct tcpacl {
	struct tcpaclpage *page[64];
	int     tcpa_priv[2048];        /* privileged ports */
	simple_lock_data_t tcpa_lock;   /* serialize sockopts */
};

extern struct tcpacl tcpacl;            /* DAC-on-ports ACL */

struct tcpaclpage {
	struct tcpach *port[1024];      /* ACL heads for 1024 adjacent ports */
};

struct tcpach {
	struct tcpac *head;             /* head of ACL */
	int     refs;                   /* # of ptrs to this currently in use */
	int     count;                  /* number of items on list */
};

struct tcpac {
	uint16_t        pad;            /* for word alignment */
	uint16_t        flags;
	uid_t           id;             /* user/group id */
	struct in6_addr host;           /* host or subnet */
	struct in6_addr netmask;        /* netmask if "host" is a subnet */
	struct tcpac    *next;          /* next tcpac on list */
};

struct tcpah {
	unsigned char   kind;           /* TCP option number = C2 */
	unsigned char   len;            /* length of AH */
	unsigned char   opt[2];         /* suboptions for future use */
	uid_t           uid;            /* effective user id of peer */
	uid_t           luid;           /* login user id of peer */
	gid_t           gid;            /* effective group id of peer */
};

struct tcpach* tcp_achref(uint16_t port);
void tcp_achfree(struct tcpach *ach);

extern  simple_lock_data_t      misc_tcp_lock;
#define TCPMISC_LOCKINIT()      {                                       \
	lock_alloc(&misc_tcp_lock, LOCK_ALLOC_PIN, TCPMISC_LOCK_FAMILY, -1);\
	simple_lock_init(&misc_tcp_lock);                               \
}
#define TCPMISC_LOCK_DECL()     int     _tcpml;
#define TCPMISC_LOCK()          _tcpml = disable_lock(PL_IMP, &misc_tcp_lock)
#define TCPMISC_UNLOCK()        unlock_enable(_tcpml, &misc_tcp_lock)

extern  int tcp_compat_42;
extern  struct  inpcb tcb;              /* head of queue of active tcpcb's */
extern  struct  tcpstat tcpstat;        /* tcp statistics */
extern  struct  dist_tcpstat *dist_tcpstat[]; /* distributed tcp stats */

#define TCP_EPHEMERAL_LOW_DFLT  32768
#define TCP_EPHEMERAL_HIGH_DFLT 65535

#define TCP_NAGLE_LIMIT 65535
#endif

#endif /* _TCP_VAR_H_ */
