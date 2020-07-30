/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernext/inet/icmp6_var.h 1.8                            */
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
/* @(#)22  1.8  src/bos/kernext/inet/icmp6_var.h, sockinc, bos530 10/20/03 06:43:11" */

/*
 * Copyright (c) 1982, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
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
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
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
 *	@(#)icmp_var.h	8.1 (Berkeley) 6/10/93
 */

#ifndef _NETINET_ICMP6_VAR_H_
#define _NETINET_ICMP6_VAR_H_

#define CACHE_LINE_SIZE 256
/*
 * Variables related to this implementation
 * of the IPv6 control message protocol.
 */
struct	icmp6stat {
/* statistics related to IPV6 icmp packets generated */
	u_long	icp6s_error;		/* # of calls to icmp6_error */
	u_long	icp6s_ratelim;		/* # beyond error rate limit */
	u_long	icp6s_oldicmp;		/* no error 'cuz old was icmp */
	u_long	icp6s_snd_unreach;	/* # of sent unreachables */
	u_long	icp6s_snd_pkttoobig;	/* # of sent packet too big */
	u_long	icp6s_snd_timxceed;	/* # of sent time exceeded */
	u_long	icp6s_snd_paramprob;	/* # of sent parameter problems */
	u_long	icp6s_snd_echoreq;	/* # of sent echo requests */
	u_long	icp6s_snd_echorep;	/* # of sent echo replies */
	u_long	icp6s_snd_mldqry;	/* # of sent group queries */
	u_long	icp6s_snd_mldrep;	/* # of sent group reports */
	u_long	icp6s_snd_mldterm;	/* # of sent group terminations */
	u_long	icp6s_snd_rtsol;	/* # of sent router solicitations */
	u_long	icp6s_snd_rtadv;	/* # of sent router advertisements */
	u_long	icp6s_snd_ndsol;	/* # of sent neighbor solicitations */
	u_long	icp6s_snd_ndadv;	/* # of sent neighbor advertisements */
	u_long  icp6s_snd_redirect;	/* # of sent redirects */
	u_long  icp6s_snd_rtrenum;	/* # of sent router renumberings */
/* statistics related to input messages processed */
	u_long	icp6s_badcode;		/* icmp6_code out of range */
	u_long	icp6s_tooshort;		/* packet < ICMP6_MINLEN */
	u_long	icp6s_checksum;		/* bad checksum */
	u_long	icp6s_badlen;		/* calculated bound mismatch */
	u_long	icp6s_reflect;		/* number of responses */
	u_long	icp6s_rcv_unreach;	/* # of rcvd unreachables */
	u_long	icp6s_rcv_pkttoobig;	/* # of rcvd packet too big */
	u_long	icp6s_rcv_timxceed;	/* # of rcvd time exceeded */
	u_long	icp6s_rcv_paramprob;	/* # of rcvd parameter problems */
	u_long	icp6s_rcv_echoreq;	/* # of rcvd echo requests */
	u_long	icp6s_rcv_echorep;	/* # of rcvd echo replies */
	u_long	icp6s_rcv_mldqry;	/* # of rcvd group queries */
	u_long	icp6s_rcv_mldrep;	/* # of rcvd group reports */
	u_long	icp6s_rcv_mldterm;	/* # of rcvd group terminations */
	u_long	icp6s_rcv_bad_mldqry;	/* # of rcvd bad group queries */
	u_long	icp6s_rcv_bad_mldrep;	/* # of rcvd bad group reports */
	u_long	icp6s_rcv_our_mldrep;	/* # of rcvd our groups' reports */
	u_long	icp6s_rcv_bad_mldterm;	/* # of rcvd bad group terminations */
	u_long	icp6s_rcv_rtsol;	/* # of rcvd router solicitations */
	u_long	icp6s_rcv_rtadv;	/* # of rcvd router advertisements */
	u_long	icp6s_rcv_ndsol;	/* # of rcvd neighbor solicitations */
	u_long	icp6s_rcv_ndadv;	/* # of rcvd neighbor advertisements */
	u_long	icp6s_rcv_redirect;	/* # of rcvd redirects */
	u_long	icp6s_rcv_badrtsol;	/* # of rcvd bad router sol. */
	u_long	icp6s_rcv_badrtadv;	/* # of rcvd bad router adv. */
	u_long	icp6s_rcv_badndsol;	/* # of rcvd bad neighbor sol. */
	u_long	icp6s_rcv_badndadv;	/* # of rcvd bad neighbor adv. */
	u_long	icp6s_rcv_badredirect;	/* # of rcvd bad redirects */
	u_long	icp6s_rcv_rtrenum;	/* # of rcvd router renumberings */
	u_long	icp6s_ndpqdrop;		/* # of held packets dropped waiting */
					/*    for ndp to finish */
	u_long	icp6s_nomobip6;		/* mobility not started */ 
	u_long	icp6s_rcv_haadreq;	/* # of rcvd HAAD requests */
	u_long	icp6s_rcv_haadreply;	/* # of rcvd HAAD replies */
	u_long	icp6s_rcv_prefsol;	/* # of rcvd prefix solicitations */
	u_long	icp6s_rcv_prefadv;	/* # of rcvd prefix advertisements */
	u_long	icp6s_rcv_badhaadreq;	/* # of rcvd bad HAAD requests */
	u_long	icp6s_rcv_badhaadreply;	/* # of rcvd bad HAAD replies */
	u_long	icp6s_rcv_badprefsol;	/* # of rcvd bad prefix sol. */
	u_long	icp6s_rcv_badprefadv;	/* # of rcvd bad prefix adv. */
};


/* distributed stat structures for IPv6 control message protocol. */

struct  dist_icmp6stat {
/* statistics related to IPV6 icmp packets generated */
        u_long  icp6s_error;            /* # of calls to icmp6_error */
        u_long  icp6s_ratelim;          /* # beyond error rate limit */
        u_long  icp6s_oldicmp;          /* no error 'cuz old was icmp */
        u_long  icp6s_snd_unreach;      /* # of sent unreachables */
        u_long  icp6s_snd_pkttoobig;    /* # of sent packet too big */
        u_long  icp6s_snd_timxceed;     /* # of sent time exceeded */
        u_long  icp6s_snd_paramprob;    /* # of sent parameter problems */
        u_long  icp6s_snd_echoreq;      /* # of sent echo requests */
        u_long  icp6s_snd_echorep;      /* # of sent echo replies */
        u_long  icp6s_snd_mldqry;       /* # of sent group queries */
        u_long  icp6s_snd_mldrep;       /* # of sent group reports */
        u_long  icp6s_snd_mldterm;      /* # of sent group terminations */
        u_long  icp6s_snd_rtsol;        /* # of sent router solicitations */
        u_long  icp6s_snd_rtadv;        /* # of sent router advertisements */
        u_long  icp6s_snd_ndsol;        /* # of sent neighbor solicitations */
        u_long  icp6s_snd_ndadv;        /* # of sent neighbor advertisements */
        u_long  icp6s_snd_redirect;     /* # of sent redirects */
        u_long  icp6s_snd_rtrenum;      /* # of sent router renumberings */
/* statistics related to input messages processed */
        u_long  icp6s_badcode;          /* icmp6_code out of range */
        u_long  icp6s_tooshort;         /* packet < ICMP6_MINLEN */
        u_long  icp6s_checksum;         /* bad checksum */
        u_long  icp6s_badlen;           /* calculated bound mismatch */
        u_long  icp6s_reflect;          /* number of responses */
        u_long  icp6s_rcv_unreach;      /* # of rcvd unreachables */
        u_long  icp6s_rcv_pkttoobig;    /* # of rcvd packet too big */
        u_long  icp6s_rcv_timxceed;     /* # of rcvd time exceeded */
        u_long  icp6s_rcv_paramprob;    /* # of rcvd parameter problems */
        u_long  icp6s_rcv_echoreq;      /* # of rcvd echo requests */
        u_long  icp6s_rcv_echorep;      /* # of rcvd echo replies */
        u_long  icp6s_rcv_mldqry;       /* # of rcvd group queries */
        u_long  icp6s_rcv_mldrep;       /* # of rcvd group reports */
        u_long  icp6s_rcv_mldterm;      /* # of rcvd group terminations */
        u_long  icp6s_rcv_bad_mldqry;   /* # of rcvd bad group queries */
        u_long  icp6s_rcv_bad_mldrep;   /* # of rcvd bad group reports */
        u_long  icp6s_rcv_our_mldrep;   /* # of rcvd our groups' reports */
        u_long  icp6s_rcv_bad_mldterm;  /* # of rcvd bad group terminations */
        u_long  icp6s_rcv_rtsol;        /* # of rcvd router solicitations */
        u_long  icp6s_rcv_rtadv;        /* # of rcvd router advertisements */
        u_long  icp6s_rcv_ndsol;        /* # of rcvd neighbor solicitations */
        u_long  icp6s_rcv_ndadv;        /* # of rcvd neighbor advertisements */
        u_long  icp6s_rcv_redirect;     /* # of rcvd redirects */
        u_long  icp6s_rcv_badrtsol;     /* # of rcvd bad router sol. */
        u_long  icp6s_rcv_badrtadv;     /* # of rcvd bad router adv. */
        u_long  icp6s_rcv_badndsol;     /* # of rcvd bad neighbor sol. */
        u_long  icp6s_rcv_badndadv;     /* # of rcvd bad neighbor adv. */
        u_long  icp6s_rcv_badredirect;  /* # of rcvd bad redirects */
        u_long  icp6s_rcv_rtrenum;      /* # of rcvd router renumberings */
        u_long  icp6s_ndpqdrop;         /* # of held packets dropped waiting */
                                        /*    for ndp to finish */
        u_long  icp6s_nomobip6;         /* mobility not started */ 
        u_long  icp6s_rcv_haadreq;      /* # of rcvd HAAD requests */
        u_long  icp6s_rcv_haadreply;    /* # of rcvd HAAD replies */
        u_long  icp6s_rcv_prefsol;      /* # of rcvd prefix solicitations */
        u_long  icp6s_rcv_prefadv;      /* # of rcvd prefix advertisements */
        u_long  icp6s_rcv_badhaadreq;   /* # of rcvd bad HAAD requests */
        u_long  icp6s_rcv_badhaadreply; /* # of rcvd bad HAAD replies */
        u_long  icp6s_rcv_badprefsol;   /* # of rcvd bad prefix sol. */
        u_long  icp6s_rcv_badprefadv;   /* # of rcvd bad prefix adv. */
        char    dummy[IP_CACHE_LINE_SIZE - sizeof(struct icmp6stat) % IP_CACHE_LINE_SIZE]; /*pad for cache line*/

};



#ifdef _KERNEL
extern struct	icmp6stat icmp6stat;
extern struct   dist_icmp6stat *dist_icmp6stat[];
#endif

#endif
