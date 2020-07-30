/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/net/proto_net.h 1.49.2.3                         */
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
/* @(#)18	1.49.2.3  src/bos/kernel/net/proto_net.h, sysnet, bos53X, x2010_50A9 1/28/10 05:47:46 */
/*
 *   COMPONENT_NAME: SYSNET
 *
 *   FUNCTIONS: 
 *		
 *
 *   ORIGINS: 27,85,127,196
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

#ifdef _KERNEL
#ifndef _PROTO_NET_H
#define _PROTO_NET_H

#ifdef INFULLPROTO

# define	PROTO(s) s

#include <sys/file.h>
#include <sys/socket.h>
#include <net/route.h>
#include <sys/call_ie.h>
#include <net/raw_cb.h>
#include <sys/ndd_var.h>
#include <sys/socketvar.h>
#include <net/netopt.h>
#include <sys/comio.h>
#include <aixif/net_if.h>

#else
# define	PROTO(s) ()
#endif

#include <sys/mbuf.h>
#include <sys/ndd.h>
#include <net/nd_lan.h>
#include <sys/cdli.h>
#include <sys/dr.h>

/* Avoid scoping problems */
typedef union {
	struct sockaddr		*p1;
	struct socket		*p2;
	struct sockproto	*p3;
	struct mbuf		*p4;
	struct ifnet		*p5;
	struct ifqueue		*p6;
	struct ifaddr		*p7;
	struct ether_header	*p8;
	struct tty		*p9;
	struct slcompress	*p10;
	struct ip		*p11;
	struct in_addr		*p12;
	struct arpcom		*p13;
	struct arpent		*p14;
	struct domain		*p15;
	struct netisr		*p16;
	struct radix_node	*p17;
	struct radix_node_head	*p18;
	struct rawcb		*p19;
	struct route		*p20;
	struct rtentry		*p21;
	struct rt_metrics	*p22;
	struct sl_softc		*p23;
	struct arptab		*p24;
} proto_net_union_t;

typedef int walktree_f_t PROTO((struct radix_node *, void *));

/* aix_misc.c */
void 		aix_netinit PROTO((void));
void 		net_tap PROTO((ndd_t *, struct mbuf *, caddr_t, u_char));
void 		netsleepinit PROTO((void));
int 		net_sleep PROTO((void *, int));
void 		net_wakeup PROTO((void *));
void 		add_netoption PROTO((struct netopt_pre520_compat *));
void 		add_netoption_520 PROTO((struct netopt *));
void 		delete_netopt PROTO((struct netopt_pre520_compat *));
void 		delete_netopt_520 PROTO((struct netopt *));
int 		splnet PROTO((void));
int 		splimp PROTO((void));
int 		splhi PROTO((void));
int 		splhigh PROTO((void));
int 		splx PROTO((int));
int 		find_input_type PROTO((u_short, struct mbuf *, struct arpcom *, 
			caddr_t));
int 		add_input_type PROTO((u_short, u_short, void (*)(), 
			struct ifqueue *, u_short));
int 		del_input_type PROTO((u_short));
int 		wild_type_dispatch PROTO((u_short, struct mbuf *, struct ifnet *, 
			caddr_t, u_char));
int 		add_netisr PROTO((u_short, u_short, void (*)(void)));
int 		del_netisr PROTO((u_short));
int 		in_cksum PROTO((struct mbuf *, register int));
u_short 	in_cksum_remove PROTO((struct mbuf *, int, u_short, int));
void 		make_ifname PROTO((char *, int, char *));

/* atmsock.c */
void 		atmsock_init PROTO((void));
int 		ndd_atm_usrreq PROTO((struct socket *, int, struct mbuf *, 
			struct mbuf *, struct mbuf *));
uint 		ndd_atm_call_ind PROTO((uint, struct connect_ie *, struct cause *));
void 		ndd_atm_call_status PROTO((uint, uint, uint, uint, ushort, uchar, int));
int 		ndd_atm_ctloutput PROTO((int, struct socket *, int, int, 
			struct mbuf **));
int 		ndd_atm_send PROTO((struct socket *, struct mbuf *, struct uio *, 
			struct mbuf *, struct mbuf *, int));
void 		ndd_atm_recv PROTO((ndd_t *, struct mbuf *, caddr_t, caddr_t));
int 		ndd_atm_receive PROTO((struct socket *, struct mbuf **, 
			struct uio *, struct mbuf **, struct mbuf **, int *));
void 		atm_delay_sbdroprecord PROTO((struct sockbuf *,struct mbuf **));
void 		set_data_call_parm PROTO((struct connect_ie *));
int 		ndd_atm_control PROTO((struct socket *, int, caddr_t, ndd_t *));
void 		check_blli PROTO((blli_t *));

/* cdli.c */
int 		ns_init PROTO((void));
struct ns_demuxer * ns_get_demuxer PROTO((u_short));
int 		ns_add_demux PROTO((u_long, struct ns_demuxer *));
int 		ns_del_demux PROTO((u_int));
int 		ns_add_filter PROTO((ndd_t *, caddr_t, int, struct ns_user *));
int 		ns_del_filter PROTO((ndd_t *, caddr_t, int));
int 		ns_add_status PROTO((ndd_t *, caddr_t, int, struct ns_statuser *));
int 		ns_del_status PROTO((ndd_t *, caddr_t, int));
int 		ns_attach PROTO((ndd_t *));
int 		ns_detach PROTO((ndd_t *));
ndd_t * 	ns_locate PROTO((char *));
void 		ns_wait PROTO((ndd_t *));
int 		ns_alloc PROTO((char *, ndd_t **));
void 		ns_free PROTO((ndd_t *));
int 		kinfo_ndd PROTO((int, caddr_t, int *, int32caddr64_t, int *, 
			struct xmem *));
int 		kinfo_ndd_copy PROTO((ndd_t *, caddr_t));
int		ndd_event_tracing_nofct PROTO ((long *, struct netopt *));
int		ndd_event_name_nofct PROTO ((char *, struct netopt *));

/* if.c */
void		ifinit PROTO((void));
void		ifubareset PROTO((int));
void		ifreset PROTO((int));
void		if_attach PROTO((struct ifnet *));
struct	ifaddr *ifa_ifwithaddr PROTO((struct sockaddr *));
struct	ifaddr *ifa_ifwithdstaddr PROTO((struct sockaddr *));
struct	ifaddr *ifa_ifwithnet PROTO((struct sockaddr *));
struct	ifaddr *ifa_ifpwithdst PROTO((struct ifnet *, struct sockaddr *));
struct	ifaddr *ifa_ifpwithaf PROTO((struct ifnet *, int));
struct	ifaddr *ifa_ifwithtype PROTO((u_long));
struct	ifaddr *ifa_ifwithaf PROTO((int));
struct	ifaddr *ifaof_ifpforaddr PROTO((struct sockaddr *, struct ifnet *, struct ifaddr *));
void		link_rtrequest PROTO((int, struct rtentry *, struct sockaddr *));
void		if_down PROTO((struct ifnet *));
void		if_qflush PROTO((struct ifqueue *));
void		if_slowtimo PROTO((void));
void		if_slowsched PROTO((void));
int 		if_nostat PROTO((struct ifnet *));
int 		if_ifp_rtflush PROTO((struct radix_node *, void *));
void		if_rt_delete PROTO((struct ifnet *));
int		if_detach PROTO((struct ifnet *));
struct ifnet *	ifunit PROTO((char *));
int		ifioctl PROTO((struct socket *, u_int, caddr_t));
int		ifconf PROTO((int, caddr_t));
int 		ifconfsize PROTO((caddr_t));
int		insert_mtu PROTO((int));
int		delete_mtu PROTO((int));
int		next_mtu PROTO((int));
struct ifaddr * ifaof_ifpforaddrexaddr PROTO((struct sockaddr *, 
			register struct ifnet *, struct ifaddr *));
int 		netif_handler PROTO((int, int, void *));
void		if_rt_ifaddr_reset PROTO( (
			const struct ifnet *,
			const sa_family_t addr_family
		) );

/* if_loop.c */
void 		loinit PROTO((void));
void 		loattach PROTO((void));
int		looutput PROTO((struct ifnet *, struct mbuf *, struct sockaddr *, 
			struct rtentry *));
int		loioctl PROTO((struct ifnet *, int, caddr_t));
struct ifnet *  loifp PROTO((void));

/* kern_malloc.c */
struct netkmem_srad *mynetkmem PROTO((void));
int 		mysockthresh PROTO((void));
long		mykmeminuse PROTO((void));
void 		log_police_event PROTO((char, char, u_long, void *, int));
int		net_malloc_police_station PROTO((long *, struct netopt *));
int		net_buf_type_nofct PROTO ((char *, struct netopt *));
int		net_buf_size_nofct PROTO ((char *, struct netopt *));
void 		police_net_malloc PROTO((void *, ulong, int));
void		police_net_free PROTO((void *, ulong, int));
int		net_malloc_frag_init PROTO((long *, struct netopt *));
void *		net_malloc PROTO((u_long, int, int));
void *		net_malloc_srad PROTO((u_long, int, int, sradid_t));
void *		net_malloc_cpu PROTO((u_long, int, int, cpu_t));
void *		empty_bucket PROTO((u_long, long, int, struct kmemstats *, int, struct netkmem_srad*));
void		net_free PROTO((void *, int));
int		large_free PROTO((void *));
void		coalesce PROTO((struct kmemusage *, struct kmembuckets *, long, 
			void*));
void *		malloc_loan PROTO((size_t, long, int, int, struct netkmem_srad *));
void *		malloc_load PROTO((u_long, int, int));
void		malloc_thread PROTO((void));
int		kmemsetlimit PROTO((int, long));
void		kmeminit PROTO((void));
void		kmeminit_phase2 PROTO((void));
void		kmeminit_cpu PROTO((struct netkmem_srad *,cpu_t));
void		prime_the_buckets PROTO((struct netkmem_srad *));
void		prime_the_buckets_cpu PROTO((struct netkmem_srad *,cpu_t));
void		kmeminit_thread PROTO((int));
int		log_inuse PROTO((struct netkmem_srad *));
void *		aix_kmem_alloc PROTO((struct netkmem_srad*,ulong, int));
void 		aix_kmem_free PROTO((struct netkmem_srad*,caddr_t, size_t));
void		kmem_unhide_all PROTO((void));
void 		threadtimer PROTO((void));
void 		malloc_thread_set_timeout PROTO((int,struct netkmem_srad *));
int		extendednetstats_set PROTO((char *, struct netopt *));

void * 		aix_kmem_alloc2 PROTO((struct netkmem_srad *, long, int, size_t, int));
int		init_police_usage PROTO((struct netkmem_srad *, ulong, int)); 
int		free_police_usage_all PROTO((struct netkmem_srad *));
int		kmem_init_seg PROTO((struct netkmem_srad *, long));  
void		kmem_set_highwat PROTO((struct netkmem_srad *, cpu_t));
int 		netkmem_dr_handler PROTO((void *, void *, int, void *));
int		netkmem_dr_cpu_add PROTO((cpu_t));
int		netkmem_dr_cpu_remove PROTO((cpu_t));

void		coalesce_pages PROTO((void *, struct kmembuckets *,
						void **, long));
void *		large_alloc PROTO((size_t, long, int, struct kmemstats *,
						int, struct kmembuckets *));
int		addr2heap PROTO((caddr_t)); 
void		kmem_init_heap PROTO((int)); 


int 		dmx_8022_receive PROTO((ndd_t *, struct mbuf *, int, 
			struct isr_data_ext *));
void 		dmx_non_ui PROTO((ndd_t *, struct mbuf *, int));
int		dmx_8022_add_filter PROTO((ndd_t *, ns_8022_t *, ns_user_t *));
int		dmx_8022_del_filter PROTO((ndd_t *, ns_8022_t *));
int		dmx_add_status PROTO((ndd_t *, ns_com_status_t *, ns_statuser_t *));
int		dmx_del_status PROTO((ndd_t *, ns_com_status_t *));
void		dmx_status PROTO((ndd_t *, ndd_statblk_t *));
struct ns_8022_user * dmx_8022_get_user PROTO((ns_8022_t *, ndd_t *));
int		dmx_init PROTO((ndd_t *));
void		dmx_term PROTO((ndd_t *));
int		nd_config_proto PROTO((u_short, struct config_proto *));
int		nd_config_sap PROTO((u_short, u_short, struct config_proto *, 
			u_short *));
int		nd_find_af PROTO((u_short, u_short));
int 		kinfo_zstats PROTO((int, caddr_t, int *, int32caddr64_t, int *, 
			struct xmem *));
int		net_malloc_cpudata PROTO((int, void *[] ));
void            ostd_mem_expand PROTO((void));
void		ostd_mem_del PROTO((void *, size_t, int, u_int));
void		ostd_mem_add PROTO((struct ostd_mem_rec *, void *, char,
			size_t, int, u_int, u_int));

/* nddsock.c */
void		nddpcb_free PROTO((struct raw_nddpcb *));
void		nddsock_init PROTO((void));
void		ndd_clean_isrq PROTO((struct socket *));
int		ndd_usrreq PROTO((struct socket *, int, struct mbuf *, 
			struct mbuf *, struct mbuf *));
int		ndd_control PROTO((struct socket *, int, caddr_t, ndd_t *));
void		nddintr PROTO((ndd_t *, struct mbuf *, caddr_t, struct socket *));
void		nddisr PROTO((void));
int		ndd_output PROTO((struct mbuf *, struct socket *));

/* net_if.c */
void		net_start_timeout PROTO((struct trb *));
int		net_start PROTO((struct file **, struct netid_list *));
int		net_attach PROTO((struct kopen_ext *, struct device_req *, 
			struct netid_list *, struct file **));
int		net_start_done PROTO((struct netid_list *, struct status_block *));
int		net_xmit PROTO((struct ifnet *, struct mbuf *, struct file *, int, 
			struct mbuf *));
int		net_detach PROTO((struct file *));
void		net_queued_write PROTO((void));
void		net_xmit_trace PROTO((struct ifnet *, struct mbuf *));
void 		net_xmit_trace_cdli PROTO((ndd_t *, struct mbuf *, caddr_t, 
			caddr_t));
void		net_recv_trace_cdli PROTO((ndd_t *, struct mbuf *, caddr_t, 
			caddr_t));
void		net_error PROTO((struct ifnet *, int, struct file *));

/* netisr.c */
void		netinit PROTO((int));
void		netisrinit PROTO((void));
struct	netisr *netisr_lookup PROTO((int));
int		netisr_add PROTO((int, void (*)(void), struct ifqueue *, 
			struct domain *));
int		netisr_del PROTO((int));
int		netisr_input PROTO((int, struct mbuf *, caddr_t, int));
int		netisr_af PROTO((int));
void		netisr_timeout PROTO((caddr_t));
void		Netintr PROTO((void));
void		netisr_thread PROTO((void));
void 		netthread_init PROTO((void));
void		netthread_start PROTO((void));

/* radix.c */
struct radix_node *rn_addmask PROTO((void *, int, int));
struct radix_node *rn_addroute PROTO((void *, void *, struct radix_node_head *,
		struct radix_node [2], void *, struct rtreq_parm *));
struct radix_node *rn_delete PROTO((void *, void *, struct radix_node_head *, 
		struct gidstruct *, void *, struct ifnet *, __ulong32_t *));
struct radix_node *rn_insert PROTO((void *, struct radix_node_head *, int *,
		struct radix_node [2]));
struct radix_node *rn_match PROTO((void *, struct radix_node_head *, 
		struct gidstruct *));
struct radix_node *rn_newpair PROTO((void *, int, struct radix_node[2]));
struct radix_node *rn_search PROTO((void *, struct radix_node *));
struct radix_node *rn_search_m PROTO((void *, struct radix_node *, void *));
struct radix_node *rn_lookup PROTO((void *, void *, struct radix_node_head *, 
		struct gidstruct *));
struct radix_node *rn_genmatch PROTO((void *, struct radix_node_head *, 
		struct gidstruct *, struct ifaddr *, uint));
struct radix_mask *rn_new_radix_mask PROTO((struct radix_node *, 
		struct radix_mask *));
struct radix_node *rn_change PROTO((void *, void *, struct radix_node_head *,
		void *, struct gidstruct *, struct ifnet *, __ulong32_t *));
struct radix_node *rn_change_policy PROTO((void *, void *, struct radix_node_head *,
		void *, struct rtreq_parm *));

int	 	rn_inithead PROTO((void **, int));
int		rn_walktree PROTO((struct radix_node_head *, walktree_f_t *, 
			void *));
int		rn_refines PROTO((void *, void *));
int		rn_satisfies_leaf PROTO((char *, struct radix_node *, int));
int		rn_lexobetter PROTO((void *, void *));
int		gidsmatch PROTO((struct gidstruct *, struct gidstruct *));
void		rn_init PROTO((void));
void            rn_change_cost PROTO((struct rtentry *, __ulong32_t));

/* raw_cb.c */
int		raw_attach PROTO((struct socket *, int));
void		raw_detach PROTO((struct rawcb *));
void		raw_disconnect PROTO((struct rawcb *));
int		raw_bind PROTO((struct socket *, struct mbuf *));

/* raw_usrreq.c */
void		raw_init PROTO((void));
int		raw_input PROTO((struct mbuf *, struct sockproto *,
			struct sockaddr *, struct sockaddr *));
void		raw_ctlinput PROTO((int, struct sockaddr *, caddr_t));
int		raw_usrreq PROTO((struct socket *, int, struct mbuf *, 
			struct mbuf *, struct mbuf *));

/* route.c */
/*
void		rtinithead PROTO((int, int, void (*)(struct sockaddr *,
			struct sockaddr *)));
*/
void		rtable_init PROTO((void **));
void		rtalloc PROTO((struct route *));
void    	rtalloc_gr PROTO((struct route *, struct gidstruct *,
			struct ifaddr *, uint));
void		rtalloc_nolock PROTO((struct route *));
void		rtalloc_nolock_gr PROTO((struct route *, struct gidstruct *,
			struct ifaddr *, uint));
struct	rtentry *rtalloc1 PROTO((struct sockaddr *, int));
struct  rtentry *rtalloc1_gr PROTO((struct sockaddr *, int, struct gidstruct *,
			struct ifaddr *, uint));
struct	rtentry *rtalloc1_nolock PROTO((struct sockaddr *, int));
struct	rtentry *rtalloc1_nolock_gr PROTO((struct sockaddr *, int,
			struct gidstruct *, struct ifaddr *, uint));
void		rtfree PROTO((struct rtentry *));
void		rtfree_nolock PROTO((struct rtentry *));
void		rtredirect PROTO((struct sockaddr *, struct sockaddr *, 
			struct sockaddr *, int, struct sockaddr *, 
			struct rtentry **));
int		rtioctl PROTO((struct socket *, int, caddr_t));
struct	ifaddr *ifa_ifwithroute PROTO((int, struct sockaddr *, struct sockaddr *));
int		rtrequest PROTO((int, struct sockaddr *, struct sockaddr *,
			struct sockaddr *, int, struct rtentry **));
int     	rtrequest_gr PROTO((int, struct sockaddr *, struct sockaddr *,
                        struct sockaddr *, int, struct rtentry **, struct rtreq_parm *));
int		rtrequest_nolock PROTO((int, struct sockaddr *, struct sockaddr *,
			struct sockaddr *, int, struct rtentry **, struct rtreq_parm *));
void		rt_maskedcopy PROTO((struct sockaddr *, struct sockaddr *,
			struct sockaddr *));
int		rtinit PROTO((struct ifaddr *, int, int));
int		rtexpire PROTO((struct radix_node *, void *));
int		route_expire_upd PROTO((struct radix_node *, void *));
int		route_expire_init PROTO((long *, struct netopt *));
void		route_init PROTO((void));
void		ifafree PROTO((struct ifaddr *));
int 		rt_setgate PROTO((struct rtentry *, struct sockaddr *, 
			struct sockaddr *));
void		unresolved_enq PROTO((struct mfcentry *, struct mfcentry *));
void		unresolved_deq PROTO((struct mfcentry *));
int		mfcrequest PROTO((int, struct sockaddr *, struct sockaddr *, 
			struct sockaddr *, struct sockaddr *, int));
struct mfcentry *mfcalloc PROTO((struct sockaddr *, struct sockaddr *));
int		mfcfree PROTO((struct mfcentry *));
struct sockaddr *sockmerge PROTO((struct sockaddr *, struct sockaddr *));
void		sockdata1 PROTO((struct sockaddr *, struct sockaddr *));
void		sockaddr2 PROTO((struct sockaddr *, struct sockaddr *));
int		ifa_locate_down PROTO((struct sockaddr *, struct mfcentry *));
void		debug_dump_buf PROTO((void *, int));
int		rt_cleanclones PROTO((struct radix_node *,
			struct dst_and_mask *));
void            dead_gateway PROTO((struct sockaddr *, int));
void            mark_gateway PROTO((struct rtentry *, int));
void            gateway_up PROTO((struct sockaddr *));
int             raise_cost PROTO((struct radix_node *, void *));
int             compare_cost PROTO((struct radix_node *, void *));
int             restore_cost PROTO((struct radix_node *, void *));
int             dgd_timer PROTO((struct radix_node *, void *));
void            adjust_gateways PROTO((void));
struct rtentry *nextroute PROTO((struct route *, struct gidstruct *));

/* rtsock.c */
int		route_usrreq PROTO((struct socket *, int, struct mbuf *, 
			struct mbuf *, struct mbuf *));
int		rt_changegids PROTO((struct gidstruct **, struct gidstruct));
void		route_init PROTO((void));
int		route_output PROTO((struct mbuf *, struct socket *));
void		rt_setmetrics PROTO((u_long, struct rt_metrics_compat *, 
			struct rt_metrics_compat *));
void		rt_xaddrs PROTO((caddr_t, caddr_t, struct rt_addrinfo *));
struct mbuf *	rt_msg1 PROTO((int, struct rt_addrinfo *));
int		rt_msg2 PROTO((int, struct rt_addrinfo *, caddr_t, struct walkarg *,
			int));
void		m_copyback PROTO((struct mbuf *, int, int, caddr_t));
void		rt_missmsg PROTO((int, struct rt_addrinfo *, int, int));
void		rt_ifmsg PROTO((struct ifnet *));
int		sysctl_dumpentry PROTO((struct radix_node *, void *));
int		sysctl_iflist PROTO((int, struct walkarg *));
int		sysctl_rtable PROTO((int *, int, caddr_t, size_t, caddr_t, size_t));
int		rt_dumpentry PROTO((struct radix_node *, struct walkarg *));
void		rt_newaddrmsg PROTO((int, struct ifaddr *, int, struct rtentry *));
int		rt_setgate PROTO((struct rtentry *, struct sockaddr *, 
			struct sockaddr *));
int		route_configure PROTO((void));
void		route_sanity PROTO((void));
void 		route_unfunnel PROTO((struct domain_funnel *));
void		route_funnel PROTO((struct domain_funnel *));
int		kinfo_iflist PROTO((int, struct walkarg *, int));
int		kinfo_rtable PROTO((int, caddr_t, int *, int, int*, struct xmem *));






#ifdef _AIX_FULLOSF
/* if_arp.c */
void	arpinit PROTOROTO((void));
void	arpattach PROTO((struct arpent *));
void	arptimer PROTO((void));
void	arpintr PROTO((void));
void	arpwhohas PROTO((struct arpcom *, struct in_addr *));
int	arpresolve PROTO((struct arpcom *, struct mbuf *, struct sockaddr *,
				u_char *, int *));
int	arpoutput PROTO((struct arpcom *, struct mbuf *, u_char *));
int	arpioctl PROTO((int, caddr_t));
void	arptfree(struct arptab *);
struct	arptab *arptlookup(struct arptab *, struct sockaddr *, struct ifnet *);
struct	arptab *arptnew(struct arptab *, struct sockaddr *, struct ifnet *);
void	arpttimer(struct arptab *);
char	*arp_sprintf PROTO((char *, u_char *, int));
int     arpresolve_common (register struct arpcom *, struct mbuf *,
        int (*arpwhohas)(register struct arpcom *, struct in_addr *,
        int, void *), struct in_addr *, u_char *, int, void *,
                union if_dependent *);
int     arpupdate (register struct arpcom *, struct mbuf *,
                caddr_t, int, struct arpupdate_parm *);


/* if_ethersubr.c */
void	etherinit PROTO((void));
int	ether_arpoutput PROTO((struct arpcom *, struct mbuf *, u_char *));
int	ether_output PROTO((struct ifnet *, struct mbuf *, struct sockaddr *,
			struct rtentry *));
void	ether_input PROTO((struct ifnet *, struct ether_header *, struct mbuf *));
char	*ether_sprintf PROTO((u_char *));

/* if_sl.c */
void	slattach PROTO((void));
int	slinit PROTO((struct sl_softc *));
void	sldinit PROTO((struct sl_softc *));
struct	mbuf *sl_btom PROTO((struct sl_softc *, int));
int	sl_output PROTO((struct ifnet *, struct mbuf *, struct sockaddr *,
                        struct rtentry *));
int	sl_ioctl PROTO((struct ifnet *, int, caddr_t));

/* slcompress.c */
void	sl_compress_init PROTO((struct slcompress *));
int	sl_compress_tcp PROTO((struct mbuf *, struct ip *,struct slcompress *,int));
int	sl_uncompress_tcp PROTO((u_char **, int, int, struct slcompress *));
#endif /* _AIX_FULLOSF */

#undef PROTO
#endif /* _PROTO_NET_H */
#endif /* _KERNEL */
