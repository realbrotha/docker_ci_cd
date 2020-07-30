/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53V src/bos/kernel/net/proto_uipc.h 1.41.2.3                        */
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
/* @(#)19       1.41.2.3  src/bos/kernel/net/proto_uipc.h, sysnet, bos53V, v2009_14A4 3/24/09 17:25:52 */
/*
 *   COMPONENT_NAME: SYSNET
 *
 *   FUNCTIONS: P
 *
 *
 *   ORIGINS: 27,85
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1993
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
 * OSF/1 1.1 Snapshot 2
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

#ifdef _KERNEL
#ifndef _PROTO_UIPC
#define _PROTO_UIPC

#define        PROTO(s) s

#include <sys/file.h>
#include <sys/cdli.h>
#include <sys/ndd.h>
#include <sys/socketvar.h>

/* cdli.h can include net_globals.h, which can include proto_net.h,
 * which will #undef PROTO
 */
#ifndef PROTO
#define        PROTO(s) s
#endif


/* Avoid scoping problems */
struct file; struct uio; struct ucred; struct stat; struct proc;
struct socket; struct sockbuf; struct mbuf;
struct msghdr; struct unpcb;
struct domain; struct domain_funnel;
struct netopt;
struct qos_socket_funcs;
struct sndbufpool;

/* domain.c */
int             fasttimo_init PROTO((long *, struct netopt *));
void            domaininit PROTO((void));
int             domain_add PROTO((struct domain *));
int             domain_del PROTO((struct domain *));
struct protosw *pffindtype PROTO((int, int));
struct protosw *pffindproto PROTO((int, int, int));
void            pfctlinput PROTO((int, struct sockaddr *));
void            pfreclaim PROTO((void));
void            pfslowtimo PROTO((void));
void            pffasttimo PROTO((void));
int             pfslowsched PROTO((void));
int             pffastsched PROTO((void));
long            gethostid PROTO((void));
int             sethostid PROTO((int));
int             gethostname PROTO((char *, size_t));
int             kgethostname PROTO((char *, int *));
int             sethostname PROTO((char *, int));
int             add_domain_af PROTO((struct domain *));
int             del_domain_af PROTO((struct domain *));
int             protosw_enable PROTO((struct protosw *));
int             protosw_disable PROTO((struct protosw *));
int             protosw6_enable PROTO((struct protosw *));
int             protosw6_disable PROTO((struct protosw *));

/* log.c */
void            bsdlog PROTO((int, char *, ...));
void            bsdlog_reg PROTO((struct socket *));
void            bsdlog_unreg PROTO((struct socket *));

/* mbuf.c */
int             thewall_init PROTO((long *, struct netopt *));
int             sockthresh_init PROTO((long *, struct netopt *));
void            mbinit PROTO((void));
caddr_t         m_clalloc PROTO((struct mbuf *, int, int));
caddr_t		m_clalloc_srad PROTO((struct mbuf *, int, int, sradid_t));
void            mbufintr PROTO((void));
#undef m_retry
struct mbuf *   m_retry PROTO((int, int));
struct mbuf *   m_retry_srad PROTO((int, int, sradid_t));
struct mbuf *   m_retryhdr PROTO((int, int));
struct mbuf *   m_retryhdr_srad PROTO((int, int, sradid_t));
struct mbuf *   m_get PROTO((int, int));
struct mbuf *	m_get_srad PROTO((int, int, sradid_t));
struct mbuf *   m_gethdr PROTO((int, int));
struct mbuf *	m_gethdr_srad PROTO((int, int, sradid_t));
struct mbuf *   m_getclr PROTO((int, int));
struct mbuf *	m_getclr_srad PROTO((int, int, sradid_t));
struct mbuf *   m_free PROTO((struct mbuf *));
void            m_freem PROTO((struct mbuf *));
int             m_leadingspace PROTO((struct mbuf *));
int             m_trailingspace PROTO((struct mbuf *));
struct mbuf *   m_prepend PROTO((struct mbuf *, int, int));
struct mbuf *   m_prepend_srad PROTO((struct mbuf *, int, int, sradid_t));
struct mbuf *   m_copym PROTO((struct mbuf *, int, int, int));
struct mbuf *   m_copy2 PROTO((struct mbuf *, int, struct mbuf *));
struct mbuf *	m_copym_srad PROTO((struct mbuf *, int, int, int, sradid_t));
void            m_copydata PROTO((struct mbuf *, int, int, caddr_t));
void            m_cat PROTO((struct mbuf *, struct mbuf *));
void            m_adj PROTO((struct mbuf *, int));
struct mbuf *   m_pullup PROTO((struct mbuf *, int));
struct mbuf *	m_pullup_srad PROTO((struct mbuf *, int, sradid_t));
void            m_freea PROTO((char *, char *));
struct mbuf *   m_clattach PROTO((caddr_t, void (*)(), int32ulong64_t,
	                int32caddr64_t, int));
struct mbuf *	m_clattach_srad PROTO((caddr_t, void (*)(), int32ulong64_t,
			int32caddr64_t, int, sradid_t));
struct mbuf *   m_getclustm PROTO((int, int, int));
struct mbuf *	m_getclustm_srad PROTO((int, int, int, sradid_t));
void            m_reg PROTO((void *));
void            m_dereg PROTO((void *));
int             m_clgetm PROTO((struct mbuf *, int, int));
int		m_clgetm_srad PROTO((struct mbuf *, int, int, sradid_t));
struct mbuf *   m_collapse PROTO((struct mbuf *, u_int));
struct mbuf *	m_collapse_srad PROTO((struct mbuf *, u_int, sradid_t));
void            m_clrefrence PROTO((struct mbuf *, struct mbuf *));
void            m_clunreference PROTO((struct mbuf *));
struct mbuf *   m_copymext PROTO((struct mbuf *, int, int, int));
struct mbuf *	m_copymext_srad PROTO((struct mbuf *, int, int, int, sradid_t));
ptrdiff_t       m_ptr_to_offset PROTO((struct mbuf *, caddr_t));
caddr_t         m_offset_to_ptr PROTO((struct mbuf *, ptrdiff_t));
int		check_sock_thresh PROTO((void));

struct mclust_pool * m_create_clustpool PROTO((int, int, int, int));
int 		m_create_mpool PROTO((struct mclust_pool **, int, int, int, int, int));
struct mbuf *	m_get_from_clustpool PROTO((struct mclust_pool *));
struct mbuf * 	mpool_get PROTO((struct mclust_pool *, uint, ulong));
struct mbuf * 	mpool_get_nolock PROTO((struct mclust_pool *, uint));
void 		mpool_set_user_free PROTO((struct mclust_pool *, 
			int(fp(struct mbuf *))));
void		m_free_to_clustpool PROTO((struct mbuf *, ulong, caddr_t));
void		m_free_clustpool PROTO((struct mclust_pool *));
struct xmem *	m_getxmemd PROTO((struct mbuf *));
int		mpool_grow PROTO((struct mclust_pool *, int, int));
int		mpool_grow_block PROTO((struct mclust_pool *, ulong, int (), int, ulong));
void		mpool_setid PROTO((struct mclust_pool *, ulong));
int		mpool_shrink PROTO((struct mclust_pool *, int, struct mbuf **));
void		kmem_hide_cluster PROTO((struct mbuf *));
void		kmem_unhide_cluster PROTO((struct mbuf *, int));
void		kmem_hide_clustpool PROTO((struct mclust_pool *));
void		kmem_unhide_clustpool PROTO((struct mclust_pool *, int));
void		kmem_unhide_clustpool_all PROTO((void));
void		kmem_hide PROTO((caddr_t, int));
void		kmem_unhide PROTO((caddr_t, int, int));
void		log_clust_traceback PROTO((struct mpool_debug *));
int		mpool_shrink_nolock PROTO((struct mclust_pool *, int,
							struct mbuf **));
int             mpool_clattach PROTO((struct mclust_pool *, struct mbuf *,
									int));


/* pinmore.c */
void            so_pin_more_stack PROTO((struct socket *));

/* proto.c */
int             uipc_configure PROTO((void));
void            uipc_sanity PROTO((void));
void            uipc_unfunnel PROTO((struct domain_funnel *));
void            uipc_funnel PROTO((struct domain_funnel *));
void            uipc_funfrc PROTO((struct domain_funnel *));

/* rand.c */
uint            tcprandom PROTO((void));

/* sf.c */
ssize_t         send_file PROTO((int *, struct sf_parms *, uint_t));
void            sf_trace PROTO((char *, ulong, ulong, ulong));

/* socket.c */
int             k_getgroups PROTO((int, struct gidnode *));
int             socreate PROTO((int, struct socket **, int, int));
int             sobind PROTO((struct socket *, struct mbuf *));
int             solisten PROTO((struct socket *, int));
void            sodqfree PROTO((struct socket *));
void            sofree PROTO((struct socket *));
void            sofree2 PROTO((struct socket *));
int             solockpair PROTO((struct socket *, struct socket *));
int             sounlock PROTO((struct socket *));
int             sodisconn PROTO((struct socket *));
int             soclose PROTO((struct socket *));
int             soabort PROTO((struct socket *));
int             soaccept PROTO((struct socket *, struct mbuf *));
int             soconnect PROTO((struct socket *, struct mbuf *));
int             soconnect2 PROTO((struct socket *, struct socket *));
int             sodisconnect PROTO((struct socket *));
int             sodisconnectreuse PROTO((struct socket *));
int             sosend PROTO((struct socket *, struct mbuf *, struct uio *,
	                struct mbuf *, struct mbuf *, int));
int             soreceive PROTO((struct socket *, struct mbuf **, struct uio *,
	                struct mbuf **, struct mbuf **, int *));
int             soshutdown PROTO((struct socket *, int));
void            sorflush PROTO((struct socket *));
void            sopriv PROTO((struct socket *));
int             sosetopt PROTO((struct socket *, int, int, struct mbuf *));
int             sogetopt PROTO((struct socket *, int, int, struct mbuf **));
void            _csignal PROTO((pid_t, int, uid_t, uid_t, int));
void            queued_csignal PROTO((void));
void            csignal PROTO((pid_t, int, uid_t, uid_t, int));
void            sohasoutofband PROTO((struct socket *));
int             sodequeue PROTO((struct socket *, struct socket **, struct mbuf **,                     int));
int             sogetaddr PROTO((struct socket *, struct mbuf **, int, int));
int             sosblock PROTO((struct sockbuf *, struct socket *));
void            sbunlock PROTO((struct sockbuf *));
int             socreategroup PROTO((int, struct socket **, int, int, int));

/* socket2.c */
void            soisconnecting PROTO((struct socket *));
void            soisconnected PROTO((struct socket *));
void            soisdisconnecting PROTO((struct socket *));
void            soisdisconnected PROTO((struct socket *));
void            soiskerndisconnected PROTO((struct socket *));
struct socket * sonewsock PROTO((struct socket *, int));
void            soqinsque PROTO((struct socket *, struct socket *, int));
int             soqremque PROTO((struct socket *, int));
void            socantsendmore PROTO((struct socket *));
void            socantrcvmore PROTO((struct socket *));
void            sosleep_timeout PROTO((struct trb *));
int             sosbwait PROTO((struct sockbuf *, struct socket *));
int             sosleep PROTO((struct socket *, caddr_t, int, int));
void            sowakeup PROTO((struct socket *, struct sockbuf *));
int             soqaio PROTO((struct socket *));
int             sbwakeup PROTO((struct socket *, struct sockbuf *, int));
int             sbpoll PROTO((struct socket *, struct sockbuf *));
int             soreserve PROTO((struct socket *, u_long, u_long));
int             sbreserve PROTO((struct sockbuf *, u_long));
void            sbrelease PROTO((struct sockbuf *));
void            sbappend PROTO((struct sockbuf *, struct mbuf *));
void            sbappendrecord PROTO((struct sockbuf *, struct mbuf *));
void            sbinsertoob PROTO((struct sockbuf *, struct mbuf *));
int             sbappendaddr PROTO((struct sockbuf *, struct sockaddr *,
	                struct mbuf *, struct mbuf *));
int             sbappendcontrol PROTO((struct sockbuf *, struct mbuf *,
	                struct mbuf *));
void            sbcompress PROTO((struct sockbuf *, struct mbuf *, struct mbuf *));
void            sbflush PROTO((struct sockbuf *));
void            sbdrop PROTO((struct sockbuf *, int));
void            sbdroprecord PROTO((struct sockbuf *));
int             lock_socheck PROTO((struct socket *));
int             unlock_socheck PROTO((struct socket *));
int             lock_sbcheck PROTO((struct sockbuf *));
int             unlock_sbcheck PROTO((struct sockbuf *));
int             sbwait PROTO((struct sockbuf *));
struct socket * sonewconn1 PROTO((struct socket *, int));
int             sb_max_init PROTO((long *, struct netopt *));
int             somaxconn_init PROTO((long *, struct netopt *));
int             tcptr_enable_init PROTO((long *, struct netopt *));
void            soqosregister PROTO((struct qos_socket_funcs *));
void            soaccessfailure PROTO((struct socket *));
void            so_exit PROTO((void));
int		sndbufpool_init PROTO((long *, struct netopt *));
void		sndbufpool_init_cpu PROTO((cpu_t));
void		sndbufpool_grow PROTO((void));
void		sndbufpool_dr_cpu_add PROTO((cpu_t));
void		sndbufpool_dr_cpu_remove PROTO((cpu_t));
void		sndbufpool_timo_sched PROTO((void));
void		sndbufpool_timo PROTO((void));
void		sndbufpool_timer_init PROTO((void));
struct mbuf *   m_get_from_sndpool PROTO((struct sndbufpool *, int));

/* sys_sock.c */
int             soo_rw PROTO((struct file *, enum uio_rw, struct uio *, ext_t));
int             soo_read PROTO((struct file *, struct uio *, struct ucred *));
int             soo_write PROTO((struct file *, struct uio *, struct ucred *));
int             soo_ioctl PROTO((struct file *, int, caddr_t ));
int             soo_select PROTO((struct file *, int, ushort, ushort *,
	                void (*)()));
int             soo_stat PROTO((struct file *, struct stat *));
int             soo_close PROTO((struct file *));
struct netopt * find_netopt PROTO((char *));
int             set_netopt PROTO((char *, long));

/* syscalls.c */
int             connect PROTO((int, caddr_t, int));
int             connext PROTO((int, caddr_t, int));
int             socket PROTO((int, int, int));
int             bind PROTO((int, caddr_t, int));
int             listen PROTO((int, int));
int             naccept PROTO((int, caddr_t, int *));
int             accept PROTO((int, caddr_t, int *));
int             socketpair PROTO((int, int, int, int*));
int             sendto PROTO((int, caddr_t, int, int, caddr_t, int));
int             send PROTO((int, caddr_t, int, int));
int             sendmsg PROTO((int, caddr_t, int));
int             nsendmsg PROTO((int, caddr_t, int));
int             recvfrom PROTO((int, caddr_t, int, int, caddr_t, int *));
int             nrecvfrom PROTO((int, caddr_t, int, int, caddr_t, int *));
int             recv PROTO((int, caddr_t, int, int));
int             recvmsg PROTO((int, struct omsghdr *, int));
int             shutdown PROTO((int, int));
int             setsockopt PROTO((int, int, int, caddr_t, int));
int             getsockopt PROTO((int, int, int, caddr_t, int*));
int             ngetsockname PROTO((int, caddr_t, int*));
int             getsockname PROTO((int, caddr_t, int *));
int             ngetpeername PROTO((int, caddr_t, int *));
int             getpeername PROTO((int, caddr_t, int *));
int             getpeereid PROTO((int, uid_t *, gid_t  *));
int             getkerninfo PROTO((int, char *, int *, int32long64_t));
int             accept1 PROTO((int, caddr_t, int *, int));
int             sendit PROTO((int, struct msghdr *, int));
int             recvit PROTO((int, struct msghdr *, caddr_t));
int             getsockname1 PROTO((int, caddr_t, int*, int));
int             getpeername1 PROTO((int, caddr_t, int *, int));
void            sockaddr_new PROTO((struct mbuf *));
void            sockaddr_old PROTO((struct mbuf *));
int             sockargs PROTO((struct mbuf **, caddr_t, int, int));
int             socksetup PROTO((int *, struct file **));
int             socket_aio_dequeue PROTO((void));
int 		kinfo_read PROTO((int, caddr_t, int *, int32caddr64_t, int *, 
			struct xmem *));
int 		kinfo_write PROTO((int, caddr_t, int *, int32caddr64_t, int *, 
			struct xmem *));

/* usrreq.c */
void            uipc_init PROTO((void));
int             uipc_usrreq PROTO((struct socket *, int, struct mbuf *,
	                struct mbuf *, struct mbuf *));
int             unp_attach PROTO((struct socket *));
void            unp_detach PROTO((struct unpcb *));
int             unp_bind PROTO((struct unpcb *, struct mbuf *));
int             unp_connect PROTO((struct socket *, struct mbuf *));
int             unp_connect2 PROTO((struct socket *, struct socket *));
void            unp_disconnect PROTO((struct unpcb *));
void            unp_abort PROTO((struct unpcb *));
void            unp_shutdown PROTO((struct unpcb *));
void            unp_drop PROTO((struct unpcb *, int));
void            unp_drain PROTO((void));
int             unp_externalize PROTO((struct mbuf *, struct socket *));
int             unp_internalize PROTO((struct mbuf *));
void            unp_dispose PROTO((struct mbuf *));
void            unp_scan PROTO((struct mbuf *, void (*)(struct file *)));
void            unp_mark PROTO((struct file *));
void            unp_discard PROTO((struct file *));
void            uipc_slowtimo PROTO((void));


#undef PROTO
#endif /* _PROTO_UIPC */
#endif /* _KERNEL */
