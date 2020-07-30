/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/mbuf.h 1.22.8.7                              */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1993              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)62       1.22.8.7  src/bos/kernel/sys/mbuf.h, sockinc, bos53X, x2010_06A4 2/3/10 15:35:52 */
/*
 *   COMPONENT_NAME: SOCKINC
 *
 *   FUNCTIONS: CLTOM
 *		DTOM
 *		MBSTAT
 *		MBUF_LOCK
 *		MBUF_LOCK_HASH
 *		MBUF_LOCKINIT
 *		MBUF_UNLOCK
 *		MCHTYPE
 *		MCLALLOC
 *		MCLFREE
 *		MCLGET
 *		MCLREFERENCE
 *		MCLREFERENCED
 *		MCLUNREFERENCE
 *		MFREE
 *		MGET
 *		MGETHDR
 *		MH_ALIGN
 *		MTOCL
 *		MTOD
 *		M_ALIGN
 *		M_COPY_PKTHDR
 *		M_HASCL
 *		M_LEADINGSPACE
 *		M_PREPEND
 *		M_TRAILINGSPACE
 *		M_XMEMD
 *		dtom
 *		m_broadcast
 *		m_clget
 *		m_copy
 *		m_getclust
 *		mtocl
 *		mtod
 *		
 *
 *   ORIGINS: 26,27,85
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1997
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

/*
 * 
 * (c) Copyright 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 * 
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
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
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
 *	Base:	mbuf.h	7.12 (Berkeley) 9/4/89
 *	Merged: mbuf.h	7.13 (Berkeley) 6/28/90
 */

#ifndef	_SYS_MBUF_H_
#define	_SYS_MBUF_H_

#ifdef __cplusplus
extern "C" {

struct mbuf;
#endif

#define	MSIZE		512

#define	MCLBYTES	CLBYTES			/* XXX */
#include "sys/xmem.h"
#include "sys/trchkid.h"
#if	defined(_KERNEL) && !defined(_NET_GLOBALS_H_)
#include "net/net_globals.h"
#endif
#ifndef	NET_MALLOC
#include "net/net_malloc.h"
#endif
#include <sys/adspace.h>
#include <sys/ras.h>

extern struct xmem mclxmemd[4];

/*
 * Mbufs are of a single size, MSIZE (machine/machparam.h), which
 * includes overhead.  An mbuf may add a single "mbuf cluster" of size
 * MCLBYTES (also in machine/machparam.h), which has no additional overhead
 * and is used instead of the internal data area; this is done when
 * at least MINCLSIZE of data must be stored.
 */

#ifdef __64BIT_KERNEL
#define	MLEN		(MSIZE - sizeof(struct m_hdr))	/* normal data len */
#else
#define MLEN		(MSIZE - sizeof (struct m_hdr) - sizeof(struct m_hdr2))
#endif /* __64BIT_KERNEL */

#define	MHLEN		(MLEN - sizeof(struct pkthdr))	/* data len w/pkthdr */
#define MQOSLEN		(MHLEN - sizeof(struct qoshdr) \
				- sizeof(struct __m_ext) \
				- sizeof(struct suminfo))
#define MSUMLEN		(MHLEN - sizeof(struct suminfo))

#define MINCLSIZE	(MHLEN + 3*MLEN) /* smallest amount to put in cluster */
#define	M_MAXCOMPRESS	(MHLEN / 2)	/* max amount to copy for compression */

/*
 * Macros for type conversion
 * mtod(m,t) -	convert mbuf pointer to data pointer of correct type
 * dtom(x) -	convert data pointer within mbuf to mbuf pointer (XXX)
 */
#define mtod(m,t)	((t)((m)->m_data))
#define	dtom(x)		((struct mbuf *)((u_long)(x) & ~(MSIZE-1)))
#define	mtocl(m)	((m)->m_ext.ext_buf)
#define MTOD(m,t)	mtod(m,t)
#define	DTOM(x)		dtom(x)
#define	MTOCL(x)	mtocl(x)
#define	CLTOM(x)	cltom(x)

#define EYEC_MBUFA      0x256D627566414C4Cull /* %mbufALL */
#define EYEC_MBUFF      0x256D627566465245ull /* %mbufFRE */

typedef ulong memreg_t;

/*
 * m_contig contains information about mbufs added to an mpool as a part of 
 *  a mpool_grow_block call.  The mbuf's clusters are all part of the same
 *  contiguous block of memory which is freed when all the mbufs have been 
 *  freed and the pool they are in.
 */

typedef struct m_contig
{
	caddr_t va;
	uint	elemsize;
	uint	elemcnt;
	ulong	freecnt;
	memreg_t memreg;
} m_contig_t;

#ifdef __64BIT_KERNEL
typedef u_int __mh_flags_t;
#else
typedef short __mh_flags_t;
#endif
/* header at beginning of each mbuf: */
struct m_hdr {
	struct	mbuf *mh_next;		/* next buffer in chain */
	struct	mbuf *mh_nextpkt;	/* next chain in queue/record */
	long	mh_len;			/* amount of data in this mbuf */
	caddr_t	mh_data;		/* location of data */
	short	mh_type;		/* type of data in this mbuf */
	__mh_flags_t mh_flags;		/* flags; see below */
#ifdef __64BIT_KERNEL
	long	mh_flags2;		/* expansion to the flags field */
	void	*mh_event;		/* pointer to an event tied to pkt */
	eye_catch8b_t	mh_eyecat;	
	m_contig_t *mh_contig;
	long	mh_options[4];		/* options field for local use */
#endif
};

#define CHECK_MBUF(m)   \
        if (m->m_eyecat != EYEC_MBUFA)  \
                panic("mbuf eyecatcher not set");

/* expansion to the m_hdr structure for the 32 bit kernel */
#ifndef __64BIT_KERNEL
struct m_hdr2 {
	long	mh2_flags2;		/* expansion to the flags field */
	void	*mh2_event;		/* pointer to an event tied to pkt */
	eye_catch8b_t	mh2_eyecat;
	m_contig_t *mh2_contig;
	long	mh2_options[9];	/* reserved fields */
};
#endif /* __64BIT_KERNEL */

/* record/packet header in first mbuf of chain; valid if M_PKTHDR set */
/* XXX: We don't use the INRIA union here, since the define for */
/*      rcvif (to get through the union) was breaking other folks */
struct	pkthdr {
	long	len;			/* total packet length */
	struct ifnet *rcvif;		/* rcv interface */
};

typedef struct mpool_debug mpool_debug_t;

/* description of external storage mapped into mbuf, valid if M_EXT set */
struct __m_ext {
	caddr_t	ext_buf;		/* start of buffer */
#ifdef	_KERNEL
	void	(*ext_free)(caddr_t, u_long, caddr_t);
#else
	void	(*ext_free)();		/* free routine if not the usual */
#endif
	u_long	ext_size;		/* size of buffer, for ext_free */
	caddr_t	ext_arg;		/* additional ext_free argument */
					/*  ext_arg is unused by mpool code */
	struct	ext_refq {		/* reference list */
		struct ext_refq *forw, *back;
	} ext_ref;
	int	ext_hasxm;		/* cross memory descriptor present? */
	struct	xmem	ext_xmemd;	/* cross memory descriptor */
	mpool_debug_t  	*ext_debug;              /* debug pointer */
	struct mclust_pool *ext_mpool; 	/* valid for mbufs that are a part of */
					/*   a mpool only */
};

struct qoshdr {
	void	*qos_ifhandle;		/* IFNET reservation identifier */
	u_long	qos_priority;		/* R-SPEC service level */
	int	qos_reserved[2];	/* Room to grow... */
};



struct suminfo {
        u_short  type;      	/* RX - type of receive checksum */
        u_short  flags;     	/* flags */
        u_short *sump;      	/* TX - where to put protocol sum */
	caddr_t	 iphdr;		/* TX - ip header starts at this address */
	size_t	 iplen;   	/* TX - length of the ip header */
        size_t   protolen;	/* TX - length of the protocol header */
        u_short  headersum; 	/* RX - pseudo-header sum */
};

/* Definition for suminfo flags */
#define IP_SUM_GOOD    1 /* IP checksum was offloaded by the adapter and
                            was found to be good */
#define PROTO_SUM_GOOD 2 /* TCP or UDP checksum was offloaded by the adapter
                            and was found to be good */
#define PROTO_NO_SUM   4 /* Support for Virtual adapter offload when no TCP checksum is present. This flag can be used only with PROTO_BY_FLAG set*/

/* Definition for suminfo type */
#define PROTO_BY_VALUE 0 /* protocol checksum passed by value in headersum */
#define IP_BY_FLAG     1 /* IP checksum flagged as good/bad */
#define PROTO_BY_FLAG  2 /* TCP/UDP checksum flagged as good/bad */


struct mbuf {
	struct	m_hdr m_hdr;
	union {
		struct {
			struct	pkthdr MH_pkthdr;	/* M_PKTHDR set */
			union {
                               struct  __m_ext MH_ext; /* M_EXT set */
				char	MH_databuf[MHLEN];
				/*
				 * MH_qos is used when M_QOS is set or when
				 * both M_EXT and (M_CHECKSUM_RX or
				 * M_CHECKSUM_TX) are set.
				 */
				struct {
                                       struct  __m_ext MH_ext;
					struct  suminfo MH_suminfo;
					struct  qoshdr MH_qoshdr;
					char    MH_qosdatabuf[MQOSLEN];
				} MH_qos;
				/*
				 * MH_sum is used when (M_CHECKSUM_TX or
				 * M_CHECKSUM_RX) is set but M_EXT is clear.
				 */
				struct {
					struct suminfo MH_suminfo;
					char MH_sumdat[MSUMLEN];
				} MH_sum;

			} MH_dat;
		} MH;
		char	M_databuf[MLEN];		/* !M_PKTHDR, !M_EXT */
	} M_dat;
#ifndef __64BIT_KERNEL
	struct m_hdr2	m_hdr2;
#endif
};
#define	m_next		m_hdr.mh_next
#define	m_len		m_hdr.mh_len
#define	m_data		m_hdr.mh_data
#define	m_type		m_hdr.mh_type
#define	m_flags		m_hdr.mh_flags
#define	m_nextpkt	m_hdr.mh_nextpkt
#ifdef __64BIT_KERNEL
#define m_eyecat	m_hdr.mh_eyecat
#define m_options	m_hdr.mh_options
#define	m_flags2	m_hdr.mh_flags2
#define	m_event		m_hdr.mh_event
#define	m_contig	m_hdr.mh_contig
#else
#define m_eyecat	m_hdr2.mh2_eyecat
#define	m_flags2	m_hdr2.mh2_flags2
#define	m_event		m_hdr2.mh2_event
#define	m_contig	m_hdr2.mh2_contig
#endif /* __64BIT_KERNEL */
#define	m_act		m_nextpkt
#define	m_pkthdr	M_dat.MH.MH_pkthdr
#define	m_ext		M_dat.MH.MH_dat.MH_ext
#define	m_pktdat	M_dat.MH.MH_dat.MH_databuf
#define m_qosdat	M_dat.MH.MH_dat.MH_qos.MH_qosdatabuf
#define m_qoshdr	M_dat.MH.MH_dat.MH_qos.MH_qoshdr
#define m_sumdat	M_dat.MH.MH_dat.MH_sum.MH_sumdat
#define m_suminfo	M_dat.MH.MH_dat.MH_sum.MH_suminfo
#define m_qossuminfo	M_dat.MH.MH_dat.MH_qos.MH_suminfo
#define	m_dat		M_dat.M_databuf

/* mbuf flags */
/* 16-bit field in 32-bit kernel, 32-bit field in 64-bit kernel. */
#define	M_EXT		0x0001	/* has associated external storage */
#define	M_PKTHDR	0x0002	/* start of record */
#define	M_EOR		0x0004	/* end of record */
#define	M_MPEG		0x0010	/* hold MPEG video data */
#define M_QOS		0x0020	/* mbuf contains a QoS header */
#define M_EXT2		0x0040	/* mbuf to be freed externally */
#define M_IPV6		0x0080	/* mbuf contains an IPv6 datagram */

/* mbuf pkthdr flags, also in m_flags */
#define	M_BCAST		0x0100	/* send/received as link-level broadcast */
#define	M_MCAST		0x0200	/* send/received as link-level multicast */
#define	M_WCARD		0x0400	/* received as network-level broadcast */
#define	M_MLOOP		0x0800	/* multicast sent/rcvd thru loopback intf */
#define	M_CHECKSUM_TX	0x1000	/* transmitted mbuf contains checksum
				   information */
#define	M_CHECKSUM_RX	0x2000	/* received mbuf contains checksum
				   information */
#define M_CHECKSUM	(M_CHECKSUM_TX|M_CHECKSUM_RX) /* XXX: REMOVE THIS */
#define	M_PSEG		0x0008	/* mbuf chain contains private segment */
#define	M_MAPPED	0x4000	/* private segment in buffer is mapped in */
#define	M_LARGESEND	0x8000	/* galaxy ethernet largesend */

/* does mbuf hold a broadcast packet? */
#define m_broadcast(m)	((m)->m_flags & (M_BCAST|M_MCAST|M_WCARD))

/* flags copied when copying m_pkthdr */
#define	M_COPYFLAGS	(~(M_EXT|M_EXT2|M_PSEG|M_MAPPED))

/* mbuf types */
#define	MT_FREE		0	/* should be on free list */
#define	MT_DATA		1	/* dynamic (data) allocation */
#define	MT_HEADER	2	/* packet header */
#define	MT_SOCKET	3	/* socket structure */
#define	MT_PCB		4	/* protocol control block */
#define	MT_RTABLE	5	/* routing tables */
#define	MT_HTABLE	6	/* IMP host tables */
#define	MT_ATABLE	7	/* address resolution tables */
#define	MT_SONAME	8	/* socket name */
#define	MT_SOOPTS	10	/* socket options */
#define	MT_FTABLE	11	/* fragment reassembly header */
#define	MT_RIGHTS	12	/* access rights */
#define	MT_IFADDR	13	/* interface address */
#define MT_CONTROL	14	/* extra-data protocol message */
#define MT_OOBDATA	15	/* expedited data  */

#define MT_MAX		32	/* e.g. */

#ifdef IP_MULTICAST
/* to support IP multicasting */
#define	MT_IPMOPTS	16	/* internet multicast options */
#define	MT_IPMADDR	17	/* internet multicast address */
#define	MT_IFMADDR	18	/* link-level multicast address */
#define	MT_MRTABLE	19	/* multicast routing tables */
#endif

#define MT_IEEE1284     20      /* ecp parallel port data  */

#define MT_IPSEC	21	/* buffer holding ipsec data */

/* flags to m_get/MGET */
#define	M_DONTWAIT	0
#define	M_WAIT		1

/*
 * mbuf allocation/deallocation macros:
 *
 *	MGET(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain internal data.
 *
 *	MGETHDR(struct mbuf *m, int how, int type)
 * allocates an mbuf and initializes it to contain a packet header
 * and internal data.
 */

#define	MGET(m, how, type) { \
	MTRCHKL2T(HKWD_MBUF | hkwd_m_get_in, how, type); \
	TRCHKL5T_NOMTRC(HKWD_MBUF | hkwd_m_get_in, how, type, getcaller(), \
		0, getpid()); \
	MALLOC((m), struct mbuf *, MSIZE, M_MBUF, (!how)); \
	if (m) { \
		MBSTAT2(mbstat.m_mtypes[type], 1); \
		MBSTAT2(mbstat.m_mbufs, 1); \
		(m)->m_next = (m)->m_nextpkt = 0; \
		(m)->m_type = (type); \
		(m)->m_data = (m)->m_dat; \
		(m)->m_flags = 0; \
		(m)->m_contig = NULL; \
		(m)->m_eyecat = EYEC_MBUFA; \
		(m)->m_ext.ext_mpool = NULL; \
		(m)->m_ext.ext_debug = NULL; \
		TRCHKL2T_NOMTRC(HKWD_MBUF | hkwd_m_get_out, m, mtod(m, caddr_t)); \
	} else { \
		MBSTAT(mbstat.m_drops, 1); \
	} \
}

#define	MGET_SRAD(m, how, type, srad) { \
	MTRCHKL2T(HKWD_MBUF | hkwd_m_get_in, how, type); \
	TRCHKL5T_NOMTRC(HKWD_MBUF | hkwd_m_get_in, how, type, getcaller(), \
		0, getpid()); \
	MALLOC((m), struct mbuf *, MSIZE, M_MBUF, (!how)); \
	if (m) { \
		MBSTAT2(mbstat.m_mtypes[type], 1); \
		MBSTAT2(mbstat.m_mbufs, 1); \
		(m)->m_next = (m)->m_nextpkt = 0; \
		(m)->m_type = (type); \
		(m)->m_data = (m)->m_dat; \
		(m)->m_flags = 0; \
		(m)->m_contig = NULL; \
		(m)->m_eyecat = EYEC_MBUFA; \
		(m)->m_ext.ext_mpool = NULL; \
		(m)->m_ext.ext_debug = NULL; \
		TRCHKL2T_NOMTRC(HKWD_MBUF | hkwd_m_get_out, m, mtod(m, caddr_t)); \
	} else { \
		MBSTAT(mbstat.m_drops, 1); \
	} \
}

#define	MGETHDR(m, how, type) { \
	MTRCHKL2T(HKWD_MBUF | hkwd_m_get_in, how, type); \
	TRCHKL5T_NOMTRC(HKWD_MBUF | hkwd_m_get_in, how, type, getcaller(), \
		0, getpid()); \
	MALLOC((m), struct mbuf *, MSIZE, M_MBUF, (!how)); \
	if (m) { \
		MBSTAT2(mbstat.m_mtypes[type], 1); \
		MBSTAT2(mbstat.m_mbufs, 1); \
		(m)->m_next = (m)->m_nextpkt = 0; \
		(m)->m_type = (type); \
		(m)->m_data = (m)->m_pktdat; \
		(m)->m_flags = M_PKTHDR; \
		(m)->m_contig = NULL; \
		(m)->m_eyecat = EYEC_MBUFA; \
		(m)->m_ext.ext_mpool = NULL; \
		(m)->m_ext.ext_debug = NULL; \
		TRCHKL2T_NOMTRC(HKWD_MBUF | hkwd_m_get_out, m, mtod(m, caddr_t)); \
	} else { \
		MBSTAT(mbstat.m_drops, 1); \
	} \
}

#define	MGETHDR_SRAD(m, how, type, srad) { \
	MTRCHKL2T(HKWD_MBUF | hkwd_m_get_in, how, type); \
	TRCHKL5T_NOMTRC(HKWD_MBUF | hkwd_m_get_in, how, type, getcaller(), \
		0, getpid()); \
	MALLOC((m), struct mbuf *, MSIZE, M_MBUF, (!how)); \
	if (m) { \
		MBSTAT2(mbstat.m_mtypes[type], 1); \
		MBSTAT2(mbstat.m_mbufs, 1); \
		(m)->m_next = (m)->m_nextpkt = 0; \
		(m)->m_type = (type); \
		(m)->m_data = (m)->m_pktdat; \
		(m)->m_flags = M_PKTHDR; \
		(m)->m_contig = NULL; \
		(m)->m_eyecat = EYEC_MBUFA; \
		(m)->m_ext.ext_mpool = NULL; \
		(m)->m_ext.ext_debug = NULL; \
		TRCHKL2T_NOMTRC(HKWD_MBUF | hkwd_m_get_out, m, mtod(m, caddr_t)); \
	} else { \
		MBSTAT(mbstat.m_drops, 1); \
	} \
}

#define MGETBUF(len, flag)	((len) <= MHLEN) ? m_gethdr((flag), MT_DATA) : m_getclustm((flag), MT_DATA, (len))

/*
 * Mbuf cluster macros.
 * MCLALLOC(caddr_t p, int how) allocates an mbuf cluster.
 * MCLGET adds such clusters to a normal mbuf;
 * the flag M_EXT is set upon success.
 * MCLFREE unconditionally frees a cluster allocated by MCLALLOC,
 */

#define	MCLALLOC(p, how) \
	(p = m_clalloc((struct mbuf *)0, MCLBYTES, (how)))

#define	MCLALLOC_SRAD(p, how, srad) \
	(p = m_clalloc((struct mbuf *)0, MCLBYTES, (how)))

#define	MCLFREE(p) { \
	MBSTAT2(mbstat.m_clusters, -1); \
	FREE((p), M_CLUSTER); \
}

#define	MCLGET(m, how) \
	(void) m_clalloc((m), MCLBYTES, (how))

#define	MCLGET_SRAD(m, how, srad) \
	(void) m_clalloc((m), MCLBYTES, (how))

#define MCLREFERENCED(m) \
	((m)->m_ext.ext_ref.forw != &((m)->m_ext.ext_ref))

/*
 * MFREE(struct mbuf *m, struct mbuf *n)
 * Free a single mbuf and associated external storage.
 * Place the successor, if any, in n.
 */
#define	MFREE(m, n) {							\
	MBUF_LOCK_DECL()						\
	struct mbuf *mnext = (m)->m_next;				\
	void (*extfree)() = m->m_ext.ext_free;				\
	__mh_flags_t mflags = m->m_flags;				\
	MTRCHKL2T(HKWD_MBUF | hkwd_m_free_in, m, mtod(m, caddr_t));     \
	TRCHKL5T_NOMTRC(HKWD_MBUF | hkwd_m_free_in, m, mtod(m, caddr_t),\
                        getcaller(), 0, getpid());\
	if (m->m_flags & M_EXT) {					\
		if ((m)->m_hasxm && !((m)->m_flags & M_MAPPED)) \
				MBUF_LOCK((m)->m_ext.ext_size);				\
		else											\
				MBUF_LOCK((m)->m_ext.ext_buf);				\
		if (MCLREFERENCED(m)) {	/* Unlink with lock held */	\
			remque(&m->m_ext.ext_ref);			\
			mflags &= ~M_EXT2;				\
			if ((m)->m_hasxm && !((m)->m_flags & M_MAPPED)) \
				MBUF_UNLOCK((m)->m_ext.ext_size);		\
			else										\
				MBUF_UNLOCK((m)->m_ext.ext_buf);		\
		} else if (m->m_ext.ext_free == NULL) {			\
			if ((m)->m_hasxm && !((m)->m_flags & M_MAPPED)) \
					MBUF_UNLOCK((m)->m_ext.ext_size);		\
			else											\
					MBUF_UNLOCK((m)->m_ext.ext_buf);		\
			MBSTAT2(mbstat.m_clusters, -1);			\
			FREE(m->m_ext.ext_buf, M_CLUSTER);		\
		} else if (m->m_flags & M_EXT2) {			\
			if ((m)->m_hasxm && !((m)->m_flags & M_MAPPED)) \
					MBUF_UNLOCK((m)->m_ext.ext_size);		\
			else											\
					MBUF_UNLOCK((m)->m_ext.ext_buf);		\
			(*(m->m_ext.ext_free))((caddr_t)m,		\
			    m->m_ext.ext_size, m->m_ext.ext_arg);	\
		} else {						\
			if ((m)->m_hasxm && !((m)->m_flags & M_MAPPED)) \
					MBUF_UNLOCK((m)->m_ext.ext_size);		\
			else											\
					MBUF_UNLOCK((m)->m_ext.ext_buf);		\
			(*(m->m_ext.ext_free))(m->m_ext.ext_buf,	\
			    m->m_ext.ext_size, m->m_ext.ext_arg);	\
			m->m_flags &= ~M_EXT;				\
		}							\
	}								\
									\
	(n) = mnext;							\
	if (!((mflags & M_EXT2) && extfree)) {				\
		MBSTAT2(mbstat.m_mbufs, -1);				\
		MBSTAT2(mbstat.m_mtypes[m->m_type], -1);		\
		m->m_eyecat = EYEC_MBUFF;				\
		FREE(m, M_MBUF);					\
	}								\
	TRCHKL1T_NOMTRC(HKWD_MBUF | hkwd_m_free_out, m);		\
}

#define	m_extfree	m_ext.ext_free
#define	m_extarg	m_ext.ext_arg
#define	m_extpool	m_ext.ext_mpool
#define	m_extdebug	m_ext.ext_debug
#define	m_forw		m_ext.ext_ref.forw
#define	m_back		m_ext.ext_ref.back
#define	m_hasxm		m_ext.ext_hasxm
#define	m_xmemd		m_ext.ext_xmemd

#define  m_getclust(h, t)	m_getclustm(h, t, MCLBYTES)

#define M_HASCL(m)	((m)->m_flags & M_EXT)

#define M_XMEMD(m)	(m_getxmemd((m)))

struct mbreq {
	int low_mbuf;		/* mbuf low water mark                  */
	int low_clust;		/* mbuf page size low water mark        */
	int initial_mbuf;	/* allocation of mbufs needed           */
	int initial_clust;	/* allocation of page size mbufs needed */
};

#define	MCLREFERENCE(m, n) 	m_clreference((m), (n))

#define	MCLUNREFERENCE(m) 	m_clunreference((m))

#define M_SUMINFOP(m)	((m)->m_flags & (M_CHECKSUM_RX|M_CHECKSUM_TX) ? \
			 ((m)->m_flags & (M_QOS|M_EXT) ? \
			  &(m)->m_qossuminfo : \
			  &(m)->m_suminfo) : \
			 0)

/*
 * Copy mbuf pkthdr from from to to.
 * from must have M_PKTHDR set, and to must be empty.
 */

/* NOTE: The new V8 compiler has a bug, that it cannot resolve 
 * if ((from)->m_flags & (M_CHECKSUM_TX|M_CHECKSUM_RX))  correctly.
 * Until the compiler is fixed we will modify the below macro to 
 * (((from)->m_flags & M_CHECKSUM_TX) || ((from)->m_flags & M_CHECKSUM_RX))
 * It will be changed back to the orignal macro as soon as we get a fix for
 * the compiler.
 */
#define	M_COPY_PKTHDR(to, from) { \
	(to)->m_pkthdr = (from)->m_pkthdr; \
	if ((from)->m_flags & M_QOS) {\
		(to)->m_qoshdr = (from)->m_qoshdr; \
		(to)->m_data = (to)->m_qosdat; \
	} else if (((from)->m_flags & M_CHECKSUM_TX) || ((from)->m_flags & M_CHECKSUM_RX)) \
		(to)->m_data = (to)->m_sumdat; \
	else \
		(to)->m_data = (to)->m_pktdat; \
	if (M_SUMINFOP(from)) \
		if ((from)->m_flags & M_QOS) \
			(to)->m_qossuminfo = *M_SUMINFOP(from); \
		else \
			(to)->m_suminfo = *M_SUMINFOP(from); \
	(to)->m_flags = (from)->m_flags & M_COPYFLAGS; \
}

/*
 * Set the m_data pointer of a newly-allocated mbuf (m_get/MGET) to place
 * an object of the specified size at the end of the mbuf, longword aligned.
 */
#define	M_ALIGN(m, len) \
	{ (m)->m_data += (MLEN - (len)) &~ (sizeof(long) - 1); }
/*
 * As above, for mbufs allocated with m_gethdr/MGETHDR
 * or initialized by M_COPY_PKTHDR.
 */
#define	MH_ALIGN(m, len) {						\
	int bufferlength;						\
	if ((m)->m_flags & M_QOS) {					\
		bufferlength = MQOSLEN;					\
	} else if ((m)->m_flags & (M_CHECKSUM_TX|M_CHECKSUM_RX)) {	\
		bufferlength = MSUMLEN;					\
	} else {							\
		bufferlength = MHLEN;				\
	}								\
	(m)->m_data += (bufferlength - (len)) & ~(sizeof(long) - 1);	\
}

/*
 * Similar to MH_ALIGN, but for mbufs with a struct qoshdr.
 */
#define MQOS_ALIGN(m, len) \
	{ (m)->m_data += (MQOSLEN - (len)) &~ (sizeof(long) - 1); }

/*
 * Compute the amount of space available
 * before the current start of data in an mbuf.
 */
#define M_LEADINGSPACE(m) \
        ((m)->m_flags & M_EXT ? ( MCLREFERENCED((m)) ? 0 :  \
            (m)->m_data - (m)->m_ext.ext_buf ) : \
            (m)->m_flags & M_PKTHDR ? \
	    ((m)->m_flags & M_QOS ? (m)->m_data - (m)->m_qosdat : \
	    ((m)->m_flags & (M_CHECKSUM_TX|M_CHECKSUM_RX) ? \
	     (m)->m_data - (m)->m_sumdat : (m)->m_data - (m)->m_pktdat)) : \
            (m)->m_data - (m)->m_dat)

/*
 * Compute the amount of space available
 * after the end of data in an mbuf.
 */
#define M_TRAILINGSPACE(m) \
        ((m)->m_flags & M_EXT ? ( MCLREFERENCED((m)) ? 0 :  \
	    (m)->m_ext.ext_buf + (m)->m_ext.ext_size - \
            ((m)->m_data + (m)->m_len) ) : \
            &(m)->m_dat[MLEN] - ((m)->m_data + (m)->m_len))

/*
 * Arrange to prepend space of size plen to mbuf m.
 * If a new mbuf must be allocated, how specifies whether to wait.
 * If how is M_DONTWAIT and allocation fails, the original mbuf chain
 * is freed and m is set to NULL.
 */
#define	M_PREPEND(m, plen, how) { \
	if (M_LEADINGSPACE(m) >= (plen)) { \
		(m)->m_data -= (plen); \
		(m)->m_len += (plen); \
	} else \
		(m) = m_prepend((m), (plen), (how)); \
	if ((m) && (m)->m_flags & M_PKTHDR) \
		(m)->m_pkthdr.len += (plen); \
}

/* change mbuf to new type */
#define MCHTYPE(m, t) { \
	MBSTAT2(mbstat.m_mtypes[(m)->m_type], -1); \
	MBSTAT2(mbstat.m_mtypes[t], 1); \
	(m)->m_type = t;\
}

/* length to m_copy to copy all */
/* XXX:  Is this still okay in a 64-bit world? */
#define	M_COPYALL	1000000000

/* compatiblity with 4.3 */
#define  m_copy(m, o, l)	m_copym((m), (o), (l), M_DONTWAIT)
#define  m_clget(m)		m_clgetm((m), M_DONTWAIT, MCLBYTES)

#define  m_getclust(h, t)	m_getclustm(h, t, MCLBYTES)


/*
 * Mbuf statistics.
 */
struct mbstat {
	u_long	m_mbufs;	/* mbufs obtained from page pool - UNUSED */
	u_long	m_clusters;	/* clusters obtained from page pool - UNUSED */
	u_long	m_mfree;	/* free mbufs - UNUSED */
	u_long	m_clfree;	/* free clusters - UNUSED */
	u_long	m_drops;	/* times failed to find space */
	u_long	m_wait;		/* times socket not created due to sockthresh */
	u_long	m_drain;	/* times drained protocols for space */
	u_long	m_mtypes[MT_MAX]; /* type specific mbuf allocations - UNUSED */
};

/* flags for mbuf pools */
#define MPOOL_CONTIGUOUS	1	/* Contiguous memory for the buffers */

/* options for the mpool_get function */
#define MPOOLGET_ALL		1	/* routine must return the count of 
					 * buffers or fail */
#define MPOOLGET_WAIT		2	/* routine will sleep until the count
					 * can be filled.  */

#define MPOOL_FREECNT(mpool)	((mpool)->p_size-(mpool)->m_outcnt)
#define MPOOL_CBUF(mpool)	((mpool)->cbufaddr)

struct mclust_pool
{
	struct mclust_pool *p_next; /* next pool in cluster pool list */
#ifdef _KERNEL
	Simple_lock p_lock;	/* serialize pool usage */
	char cache_line[128 - sizeof(struct mclust_pool *) - sizeof(Simple_lock)];
#else
	long p_lock;
	char cache_line[128 - sizeof(struct mclust_pool *) - sizeof(long)];
#endif

	int p_size;		/* total # of clusters in this pool */
	int p_inuse;		/* pool in use by the caller */
	int flags;		/* flags for the pool */
	int m_outcnt;		/* # of clusters given out from this pool */
	int m_maxoutcnt;        /* Max # of clusters given out at any point */
	int buftype;		/* type of data in this mbuf */
	int bufsize;		/* type of data in this mbuf */
	caddr_t cbufaddr;	/* continguous cluster buffer user for */
				/*	clusters in contiguous pools */
	struct mbuf *next;	/* pointer to next available cluster */
	struct mbuf *tail;	/* pointer to last cluster in the pool */
	long failed;            /* # of times cluster allocation failed */
	long calls;             /* total # of calls to allocate cluster from */
				/* this pool */
	ulong id;		/* user set identifier to id pools */
	uint waitcnt;		/* number of processes waiting on the mpool */
	tid_t waiting;		/* user waiting for buffers from the pool */
	int (*mpool_user_free)(struct mbuf *);
};

#define CLUST_FREE	0
#define CLUST_ALLOCATED	1

struct mpool_debug {
	caddr_t addr;
	long allocated;
	void *traceback[10];
};

struct mclustpool_info {
	ulong npools;
#ifdef _KERNEL
	simple_lock_data_t p_lock; /* to serialize cluster pool list access */
#else
	long p_lock;
#endif
	struct mclust_pool *m_pool; /* Cluster pool list */
};

#ifdef	_KERNEL
/* The following should probably be under NETSYNC_LOCK, I guess. */
typedef struct {
	simple_lock_data_t	lock;
#ifdef _POWER_MP
	char			pad[128 - sizeof(simple_lock_data_t)];
#endif	
} aligned_lock_t;
#ifdef	_POWER_MP
#define MBLOCK_HASHSZ 29
extern	aligned_lock_t mbuf_slock[MBLOCK_HASHSZ];
#define MBUF_LOCK_HASH(claddr)	((unsigned long)(SEGOFFSET(claddr)) % MBLOCK_HASHSZ)
#define MBUF_LOCK_DECL()	int _mbufs, _mbcell;
#define MBUF_LOCK(claddr)	_mbufs = disable_lock(PL_IMP, &mbuf_slock[(_mbcell = MBUF_LOCK_HASH(claddr))].lock)
#define MBUF_UNLOCK(claddr)	unlock_enable(_mbufs, &mbuf_slock[_mbcell].lock)
#define MBUF_LOCKINIT() {                                               \
        int i;                                                          \
	for (i = MBLOCK_HASHSZ - 1; i >= 0; i--) {                      \
		lock_alloc(&mbuf_slock[i].lock, LOCK_ALLOC_PIN, MBUF_LOCK_FAMILY, i);\
		simple_lock_init(&mbuf_slock[i].lock);                 	\
	}								\
}
#else
#define MBLOCK_HASHSZ 1
#define MBUF_LOCK_DECL() int    _mbufs;
#define MBUF_LOCK(claddr)	_mbufs = disable_ints()
#define MBUF_UNLOCK(claddr)	enable_ints(_mbufs)
#define MBUF_LOCKINIT()
#endif
#define MBSTAT(x, i)	(x) += (i)
#define MBSTAT2(x, i)

#define M_MEMREG(m) (((m)->m_contig) ? (m)->m_contig->memreg : 0)

#define M_MPOOLID(m) ((M_HASCL(m) && (m)->m_extpool) ? (m)->m_extpool->id : 0)

extern struct	mbstat mbstat;		/* statistics */
extern int	max_linkhdr;		/* largest link-level header */
extern int	max_protohdr;		/* largest protocol header */
extern int	max_hdr;		/* largest link+protocol header */
extern int	max_datalen;		/* MHLEN - max_hdr */
extern int	mclbytes;		/* variable version of MCLBYTES */
#endif

#ifdef __cplusplus
}
#endif

/*
 * Macros for dealing with buffers in private segments
 */

/* Does this buffer contain private segment buffer and need to be mapped in? */
#define M_NEED_PSEG_MAP(a) (M_HASCL(a) && (a)->m_hasxm && \
	(a)->m_xmemd.aspace_id != XMEM_GLOBAL && \
	!((a)->m_flags & M_MAPPED))

/* Does this buffer contain private segment buffer and need to be unmapped? */
#define M_NEED_PSEG_UNMAP(a) (M_HASCL(a) && (a)->m_hasxm && \
	(a)->m_xmemd.aspace_id != XMEM_GLOBAL && \
	((a)->m_flags & M_MAPPED))

/* Map in a private segment */
#define M_PSEG_MAP(a) { \
	long off; \
	int __rv; \
	\
	off = a->m_data - a->m_ext.ext_buf; \
	__rv = xm_mapin(&(a->m_xmemd), a->m_ext.ext_buf, \
		a->m_ext.ext_size, &(a->m_ext.ext_buf)); \
	a->m_flags |= M_MAPPED; \
	a->m_data = a->m_ext.ext_buf + off; \
}

/* Unmap a private segment */
#define M_PSEG_UNMAP(a) { \
	xm_det(a->m_ext.ext_buf, &(a->m_xmemd)); \
        a->m_flags &= ~M_MAPPED; \
}

/* Map in any private segments in the chain */
#define M_DO_PSEG_MAP(a) { \
	if ((a)->m_flags & M_PSEG) { \
	  struct mbuf *nextp; \
	  \
	  nextp = a; \
	  do { \
		if (M_NEED_PSEG_MAP(nextp)) { \
		  M_PSEG_MAP(nextp); \
		} \
		nextp = nextp->m_next; \
	  } while (nextp); \
	} \
}

/* Unmap any private segments in the chain */
#define M_DO_PSEG_UNMAP(a) { \
	if ((a)->m_flags & M_PSEG) { \
	  struct mbuf *nextp; \
	  \
	  nextp = a; \
	  do { \
		if (M_NEED_PSEG_UNMAP(nextp)) { \
			M_PSEG_UNMAP(nextp); \
		} \
		nextp = nextp->m_next; \
	  } while (nextp); \
	} \
}

/* This function checks if the len we are copying into nam is greater than MLEN.
 * If so we attach a cluster to the mbuf and then do the copy.
 * This function was added due to changes made in sockargs for long user names.
 * The sun_path in sockaddr_un was changed to PATH_MAX. Hence we allocate a
 * mbuf cluster to hold MT_SONAME. However some functions like sogetaddr etc 
 * allocate mbuf's using m_get and we try to copy the address  from a cluster
 * to mbuf of size MLEN. This caused thes system to crash. 
 */
#define CHECKBUFF(error, nam, len) { \
        if(!(nam->m_flags & M_EXT) && (len > MLEN)) { \
                if(m_clgetm(nam,M_DONTWAIT,len) == 0) \
                { \
                        error = ENOBUFS; \
                } \
        } \
}


#endif
