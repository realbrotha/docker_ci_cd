/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernext/inet/proto_inet.h 1.99.2.3                      */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1988,1995              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)84       1.99.2.3  src/bos/kernext/inet/proto_inet.h, sysxinet, bos53Q, q2008_08C3 2/5/08 15:07:14 */
/*
 *   COMPONENT_NAME: SYSXINET
 *
 *   FUNCTIONS: P
 *
 *
 *   ORIGINS: 27,85,89,127,196
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1997
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#ifdef _KERNEL
#ifndef _PROTO_INET_H_
#define _PROTO_INET_H_
/*
 *
 * (c) Copyright 1991, OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 *
 */
/*
 * OSF/1 1.2
 */
#include <sys/mbuf.h>
#include <sys/domain.h>
#include <netinet/ip.h>
#include <netinet/in6_var.h>
#include <netinet/in_pcb.h>
#include <netinet/ip_mroute.h>
#include <netinet/ip_var.h>
#include <netinet/ip6_var.h>
#include <netinet/ip6_opts.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp.h>
#include <netinet/tcpip.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_debug.h>

# define        P(s) s

/* Avoid scoping problems */
struct arpcom; struct in_addr; struct arptab;
struct mbuf; struct ifnet;
struct sockaddr; struct sockaddr_in; struct socket;
struct in_ifaddr; struct inpcb; struct ipq;
struct ipasfrag; struct route; struct ip;
struct tcpcb; struct tcpiphdr;
struct pmtu_entry;
/* The tcp_seq typedef is a problem. Better to cast or rearrange? */
#define proto_tcp_seq   __ulong32_t

/* if_arp.c */
int     arpinit P((void));
void    arptimer P((void));
void    arpsched P((void));
void    arptimer_init P((void));
void    arptfree P((struct arptab *));
int     arpioctl P((int, caddr_t));
struct  arptab *arptnew P((struct in_addr *, struct ifnet *));
void    ie2_llc P((struct ie2_llc_snaphdr *, int));

/* if_llink6.c */
void llink_resolve P((struct mbuf *, struct sockaddr *, struct rtentry *));
void llink_resolve_nolock P((struct mbuf *, struct sockaddr *, struct rtentry *));

#ifdef IP_MULTICAST

/* if_mcast_aux.c */
int driver_addmulti P((struct ifreq *, struct arpcom *, void (*)(struct sockaddr_in *, u_char *, u_char *), int *, char *));
int driver_delmulti P((struct ifreq *, struct arpcom *, void (*)(struct sockaddr_in *, u_char *, u_char *), int *, char *));

#endif /* IP_MULTICAST */

/* if_ndp6.c */
void    ndp6_rtrequest P((int, struct rtentry *, struct sockaddr *));
int     ndp6_resolve P((struct ifnet *,
	   struct rtentry *, struct mbuf *, struct sockaddr *, u_char *));
void    ndsol6_output P((struct ifnet *,
	        struct mbuf *, struct in6_addr *, struct in6_addr *));
void    ndadv6_output P((struct ifnet *,
	        struct in6_addr *, struct in6_addr *, int));
void    redirect6_output P((struct mbuf *, struct rtentry *));
int     ndsol6_input P((struct mbuf *, caddr_t));
int     ndadv6_input P((struct mbuf *, caddr_t));
int     rtsol6_input P((struct mbuf *, caddr_t));
int     rtadv6_input P((struct mbuf *, caddr_t));
int     redirect6_input P((struct mbuf *, caddr_t));
void    ip6_reachhint P((struct inpcb *));
struct  llinfo_ndp6 *ndplookup P((struct in6_addr *, int));
void  	ip6_rtexpire_timeout_setup P((struct rtentry *));
void  	ip6_rtexpire_netisr P((void));

void    ndp6_ifinit P((struct ifnet *, struct ifaddr *));
void    ndp6_rtlost P((struct rtentry *, int));
void    ip6_ndsol_netisr P((void));     
char    *ether_sprintf P((u_char *));

#ifdef IP_MULTICAST

/* igmp.c */

void igmp_init P((void));
int fill_rti P((struct in_multi *));
struct router_info* find_rti P((struct ifnet *));
void igmp_input P((struct mbuf *, int));
void igmp_joingroup P((struct in_multi *));
void igmp_leavegroup P((struct in_multi *));
void igmp_fasttimo P((void));
void igmp_slowtimo P((void));
void igmp_sendpkt P((struct in_multi *, int));
void igmp_sendleave P((struct in_multi *));
u_long random_num_get P((void));

#endif /* IP_MULTICAST */

/* in.c */
struct  in_addr in_makeaddr P((u_long, u_long));
u_long  in_netof P((struct in_addr));
void    in_sockmaskof P((struct in_addr, struct sockaddr_in *));
u_long  in_lnaof P((struct in_addr));
int     in_localaddr P((struct in_addr));
int     in_canforward P((struct in_addr));
int     in_control P((struct socket *, u_int, caddr_t, struct ifnet *));
void    in_delete_addrs P((struct ifnet *));
void    in_ifdetach P((struct ifnet *));
int     in_ifattach P((struct ifnet *));

void    in_ifscrub P((struct ifnet *, struct in_ifaddr *));
void    init_seq_key_addr P((struct sockaddr_in *));
int     in_ifinit P((struct ifnet *, struct in_ifaddr *, struct sockaddr_in *,
	                        int));
struct  in_ifaddr *in_iaonnetof P((u_long));
int     in_broadcast P((struct in_addr));
struct in_multi *in_addmulti P((struct in_addr, struct ifnet *));
int     in_delmulti P((struct in_multi *));

/* in6.c */
struct  in6_addr
	*in6_prefixof P(( struct in6_addr *));
int     in6_localaddr(struct in6_addr *addr);
int     in6_isanycast P(( struct in6_addr *));
int     in6_addanycast P((struct in6_addr *, u_int));
int     in6_delanycast P((struct in6_addr *));
char    *ip6_sprintf P((struct in6_addr *));
int     in6_control P((struct socket *, u_int, caddr_t, struct ifnet *));
void    in6_delete_addrs P((struct ifnet *));
int     in6_ifattach P((struct ifnet *));
void    in6_ifscrub P((struct ifnet *, struct in6_ifaddr *));
void    init_seq_key_addr P((struct sockaddr_in *));
int     in6_ifinit P((struct ifnet *,
	    struct in6_ifaddr *, struct sockaddr_in6 *, int));
struct  in6_multi *in6_addmulti P((struct in6_addr *, struct ifnet *));
void    in6_delmulti P((struct in6_multi *));
struct in6_ifaddr*      source_address_select P((struct in6_addr*, struct ifnet *));

/* in6_pcb.c */
int     in6_pcbbind P((struct inpcb *, struct mbuf *));
int     in6_pcbbind_dyn P((struct inpcb *, struct mbuf *, int));
int     in6_pcbrebind P((struct inpcb *, int));
int     in6_pcbconnect P((struct inpcb *, struct mbuf *));
int     in6_pcb_pseudoconnect P((struct inpcb *, struct mbuf *,
                 struct inhdr_info *, struct ip6ancillary* ancillary));
int     in6_pcb_pseudobind P((struct inpcb *, struct mbuf *,
                 struct inhdr_info *));
int     in6_pcb_pseudorebind P((struct inpcb *, int, struct inhdr_info *));
void    in6_pcbnotify P((struct inpcb *, struct sockaddr *, u_int,
	        struct in6_addr *, u_int, int, void (*)()));
void    in6_pcbnotifyall P((struct inpcb *, struct sockaddr *,
                struct sockaddr *, int, void (*)()));
struct rtentry *in6_rthost P((struct in6_addr *, struct gidstruct *, uint));
void    in6_rtalloc P((struct route *, struct gidstruct *, struct ifaddr *, uint));
int     in6_setifa P((struct inpcb *, struct ifaddr *));
struct inpcb *in6_pcbmatch P((struct inpcb_hash_table *, struct in6_addr *,
	        u_short, struct in6_addr *, u_short, int));
struct inpcb *in6_pcblookup P((struct inpcb *, struct in6_addr *, u_short,
	        struct in6_addr *, u_short, int));
void    in6_setmss P((struct inpcb *, int));
void    in6_pmtuclone P((struct inpcb *, int));
void    in6_pcbnotifymtu P((struct inpcb *, u_int32_t,
                            struct sockaddr *, void (*)()));
void    in6_recvpathmtu P((struct inpcb *, u_int32_t, struct sockaddr *));


/* in_init.c */
int     config_inet P((int, struct uio *));
void    in_arpintr P((struct ndd *, struct mbuf *, caddr_t));
int     in_arpresolve P((struct arpcom *, struct mbuf *, struct in_addr *,
	        u_char *));
struct cdt_head *netdmpf P((void));
void    init_common_mtus P((void));
void    in_rarpintr P((struct ndd *, struct mbuf *, caddr_t hp));
int	tcp_sendspace_change P((char *, struct netopt *));
int 	udp_sendspace_change P((char *, struct netopt *));

int     tcp_bad_port_limit_init P((long *, struct netopt *));
int     udp_bad_port_limit_init P((long *, struct netopt *));

int	inet_dr_cpu_add P((cpu_t));
int	inet_dr_cpu_remove P((cpu_t));


/* in_pcb.c */
int     in_pcballoc P((struct socket *, struct inpcb *));
int     in_pcbbind P((struct inpcb *, struct mbuf *));
int     in_pcbconnect P((struct inpcb *, struct mbuf *));
int     in_pcb_pseudoconnect P((struct inpcb *, struct mbuf *,
                 struct inhdr_info *));
int     in_pcb_pseudobind P((struct inpcb *, struct mbuf *,
                 struct inhdr_info *));
void    in_pcbdisconnect P((struct inpcb *));
void    in_pcbdetach P((struct inpcb *));
void    in_pcbfree P((struct inpcb *));
/* XXX: Note the additional arg for in_setsockaddr and in_setpeeraddr */
void    in_setsockaddr P((struct inpcb *, struct mbuf *, int));
void    in_setpeeraddr P((struct inpcb *, struct mbuf *, int));
void    in_pcbnotify P((struct inpcb *, struct sockaddr *, u_short,
	        struct in_addr *, u_short, int, void (*)(struct inpcb *,
	        int)));
void    in_pcbnotifyall P((struct inpcb *, struct sockaddr *,
	    int, void (*)(struct inpcb *, int)));
void    in_pcblocalipnotify P((struct inpcb *, struct sockaddr *,
            int, void (*)(struct inpcb *, int)));
void    in_pcbnotifysrc P((struct inpcb *, struct sockaddr *, int));
void    in_losing P((struct inpcb *));

#if     NETSYNC_LOCK
void    in_losing_lock P((struct inpcb *));
#endif
void    in_rtchange P((struct inpcb *, int));
struct  inpcb *in_pcblookup P((struct inpcb *, struct in_addr,
	                        u_short, struct in_addr, u_short, int));
void    in_pcb_hash_ins P((struct inpcb *));
void    in_pcb_hash_del P((struct inpcb *));
void    in_pcb_tcp_lport_hash_ins P((struct inpcb *));
void    in_pcb_tcp_hash_del P((struct inpcb *));
struct  inpcb *in_pcbhashlookup P((struct inpcb_hash_table *, struct in_addr,
	        u_short, struct in_addr, u_short, int));
struct  inpcb *in_pcbhashlookup2 P((struct inpcb_hash_table *,
	                        void *, u_short, void *, u_short, int));
void    in_pcbmovetotimewaite P((struct inpcb *));
struct  inpcb *in_pcbmatch P((struct inpcb_hash_table *, struct in_addr,
	                        u_short, struct in_addr, u_short, int));
void    in_allpcbs P((struct inpcb *, void (*)()));
void    in_rawpcbs P((void));
void    in_rtinvalidate P((void));
struct  ifaddr  *in_ifa_ifwithaddr P((struct inpcb *, struct sockaddr *));

/* in_proto.c */
void    inet_sanity P((void));
void    inet_unfunnel P((struct domain_funnel *));
void    inet_funnel P((struct domain_funnel *));

/* ip6_icmp.c */
void    icmp6_init P((void));
void    icmp6_joingroup P((struct in6_multi *));
void    icmp6_leavegroup P((struct in6_multi *));
void    icmp6_fasttimo P((void));
void    icmp6_sendmld P((struct in6_multi *, int, struct in6_addr *));
void    icmp6_errparam P((struct mbuf *, struct mbuf *, int));
void    icmp6_error P((struct mbuf *, int, int, caddr_t));
int     icmp6_input P((struct mbuf **, struct mbuf **, caddr_t, caddr_t*));
void    icmp6_reflect P((struct mbuf *, struct mbuf *));
void    icmp6_send P((struct mbuf *, struct mbuf *, struct ip_moptions *,
	int));
void    icmp6_reinsert_error P((struct mbuf *, int, int, struct mbuf *, u_int32_t, int));

/* ip6_input.c */
int     ip6rttimeout P((struct radix_node *, void *));
void    ip6rttimer P((void));
void    ip6rttimer_sched P((void));
void    ip6_init P((void));
int     flow6_rand P((int));
void    ip6_input P((struct mbuf *, caddr_t));
int     frg6_input P((struct mbuf **, struct mbuf **, caddr_t, caddr_t *));
struct ipv6 *ip6_reass P((struct ip6asfrag *, struct ip6q *, struct ip6q *));
void    frg6_freef P((struct ip6q *));
void    frg6_enq P((struct ip6asfrag *, struct ip6asfrag *));
void    frg6_deq P((struct ip6asfrag *));
void    frg6_slowtimo P((void));
void    frg6_drain P((void));
struct mbuf * ip6_saveoption P((struct mbuf *, struct mbuf *, int, int));
void    ip6_deloption P((struct mbuf *, int));
struct mbuf * ip6_dropoption P((struct mbuf *, int));
struct mbuf * ip6_copyoptions P((struct ipv6 *, struct mbuf *, int, int));
int     hop6_input P((struct mbuf **, struct mbuf **, caddr_t, caddr_t *));
int     rt6_input P((struct mbuf **, struct mbuf **, caddr_t, caddr_t *));
struct mbuf * rt6_reverse P((struct ipv6 *, struct mbuf *));
struct mbuf * opt6_reverse P((struct ipv6 *, struct mbuf *));
int     dopt6_input P((struct mbuf **, struct mbuf **, caddr_t, caddr_t *));
int     mh6_input P((struct mbuf **, struct mbuf **, caddr_t, caddr_t *));
int     end6_input P((struct mbuf **, struct mbuf **, caddr_t, caddr_t *));
void    opt6_ctlinput P((int, struct sockaddr *, struct ipv6 *, struct mbuf *));
void    ip6_forward P((struct mbuf *, int));
int	ip6_insertdopt P((struct mbuf **, struct mbuf **));
int     tentative_ip6_input P((struct mbuf *));

/* ip6_mroute.c */
int     mroute6_init P((void));
int     ip6_mforward P((struct mbuf *, struct ifnet *));
void    multicast_send P((struct mbuf *, struct ifnet *));
int     mfc_addqueue P((struct mbuf *, struct mfcentry *));
void    mfc_requeue P((int, struct ifqueue *, struct mfcentry *));
void    mfctimer P((void));

/* ip6_opts.c */
void    opt6_init P((void));
int     hd6_inoptions P((struct mbuf *, struct mbuf *, int *));
int     opt6_pad0_input P((struct opt6_any *, struct mbuf *, struct mbuf *,
	        int *));
int     opt6_padn_input P((struct opt6_any *, struct mbuf *, struct mbuf *,
	        int *));
int     opt6_rtalert_input P((struct opt6_any *, struct mbuf *, struct mbuf *,
	        int *));
int     opt6_haddr_input P((struct opt6_any *, struct mbuf *, struct mbuf *,
	        int *));
int     opt6_skip_input P((struct opt6_any *, struct mbuf *, struct mbuf *,
	        int *));
int     opt6_disc_input P((struct opt6_any *, struct mbuf *, struct mbuf *,
	        int *));
int     opt6_ferr_input P((struct opt6_any *, struct mbuf *, struct mbuf *,
	        int *));
int     opt6_oerr_input P((struct opt6_any *, struct mbuf *, struct mbuf *,
	        int *));
int     hd6_outoptions P((struct mbuf *, struct mbuf *));
int     opt6_pad0_output P((struct opt6_any *, struct mbuf *, struct mbuf *));
int     opt6_padn_output P((struct opt6_any *, struct mbuf *, struct mbuf *));
int     opt6_gen_output P((struct opt6_any *, struct mbuf *, struct mbuf *));

/* ip6_output.c */

int     ip6_output P((struct mbuf *, struct mbuf *, struct route *, int,
	        struct ip_moptions *, struct inpcb *, struct gidstruct *,
		struct ip6ancillary *));
struct mbuf *ip6_insertoption P((struct mbuf *, struct mbuf *,
	        caddr_t *, int));
int     ip6_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int     ip6_setcontrol P((struct inpcb *, struct mbuf *));
int     ip6_setoptions P((struct mbuf **, struct mbuf *, struct inpcb *));
int     ip6_getoptions P((struct mbuf *, struct mbuf **, int));
int     ip6_setmoptions P((struct inpcb *, int, struct mbuf *));
int     ip6_getmoptions P((int, struct ip_moptions *, struct mbuf **));
void    ip6_freemoptions P((struct ip_moptions *));
void    ip6_mloopback P((struct ifnet *, struct mbuf *, struct mbuf *,
	        struct sockaddr_in6 *));
int     ip6_getctrlinfo P((struct inpcb *, struct mbuf *, 
		struct ip6ancillary **));
int     ip6_setexthdroption P((struct mbuf **, struct mbuf *,
                                struct inpcb *, int));
int     ip6_getexthdroption P((int, struct mbuf *, struct mbuf **));
int     ip6_setmoptions P((struct inpcb *, int, struct mbuf *));
int     ip6_getmoptions P((int, struct ip_moptions *, struct mbuf **));
void    ip6_freemoptions P((struct ip_moptions *));
void    ip6_mloopback P((struct ifnet *, struct mbuf *, struct mbuf *,
                struct sockaddr_in6 *));
int     ip6_reroute P((struct route *, struct ipv6 *, struct ifnet **,
                int *, struct inpcb *, struct sockaddr_in6 **));

/* ip_icmp.c */
void    icmp_error P((struct mbuf *, int, int, struct in_addr, struct ifnet *));
void    queue_pfctlinput P((int, struct sockaddr_in *));
void    dequeue_pfctlinput P((void));
void    icmp_input P((struct mbuf *, int));
void    icmp_reflect P((struct mbuf *));
struct  in_ifaddr *ifptoia P((struct ifnet *));
void    icmp_send P((struct mbuf *, struct mbuf *));
n_time  iptime P((void));

/* ip_input.c */
void    setiproutemask P((struct sockaddr_in *, struct sockaddr_in *));
void    ip_init P((void));
void    ipintr P((void));
void    ipintr_noqueue P((struct ndd *, struct mbuf *, caddr_t));
void    ipintr_noqueue_post_fw P((struct ifnet *, struct mbuf *,
				  inbound_fw_args_t *));
inbound_fw_args_t *inbound_fw_save_args P((inbound_fw_args_t *));
void	inbound_fw_free_args P((inbound_fw_args_t *));
struct  mbuf *ip_reass P((struct mbuf *));
void    ip_freef P((struct ipq *, uint));
void    ip_slowtimo P((void));
void    ip_drain P((void));
int     ip_dooptions P((struct mbuf *));
struct  in_ifaddr *ip_rtaddr P((struct in_addr, struct gidstruct *));
int     gids_ok_needlock P((struct gidstruct *, struct rtentry *));
int     gids_ok P((struct gidstruct *, struct gidstruct *));
void    save_rte P((u_char *, struct in_addr));
struct  mbuf *ip_srcroute P((void));
void    ip_stripoptions P((struct mbuf *, unsigned long));
void    ip_forward P((struct mbuf *, int));
void    in_flip_and_run P((struct ndd *, struct mbuf *, caddr_t));
void 	calc_cksum(struct mbuf *m,int);

#ifdef IP_MULTICAST

/* ip_mroute.c */
int     ip_mrouter_set P((int, struct socket *, struct mbuf *));
int     ip_mrouter_get P((int, struct socket *, struct mbuf **));
int     mrt_ioctl P((int, caddr_t));
int     get_sg_cnt P((struct sioc_sg_req *));
int     get_vif_cnt P((struct sioc_vif_req *));
int     mroute_init P((void));
int     ip_mrouter_init P((struct socket *, struct mbuf *));
int     ip_mrouter_doner P((void));
int     get_version P((struct mbuf *));
int     set_assert P((int *));
int     get_assert P((struct mbuf *));
int     add_vif P((struct vifctl *));
int     del_vif P((vifi_t *));
int     add_mfc P((struct mfcctl *));
void    collate P((struct timeval *));
int     del_mfc P((struct mfcctl *));
int     socket_send P((struct socket *, struct mbuf *, struct sockaddr_in *));
#ifdef RSVP_ISI
int     ip_mforward P((struct ip *, struct ifnet *, struct mbuf *,
	        struct ip_moptions *));
#else
int     ip_mforward P((struct ip *, struct ifnet *, struct mbuf *));
#endif
void    expire_upcalls P((void));
#ifdef RSVP_ISI
int     ip_mdq P((struct mbuf *, struct ifnet *, struct mfc *, vifi_t));
#else
int     ip_mdq P((struct mbuf *, struct ifnet *, struct mfc *));
#endif
int     legal_vif_num P((int));
u_long  ip_mcast_src P((int));
void    phyint_send P((struct ip *, struct vif *, struct mbuf *));
void    encap_send P((struct ip *, struct vif *, struct mbuf *));
int     ipip_input P((struct mbuf *, int));
void    tbf_control P((struct vif *, struct mbuf *, struct ip *, u_long));
void    tbf_queue P((struct vif *, struct mbuf *, struct ip *));
void    tbf_process_q P((struct vif *));
void    tbf_dequeue P((struct vif *, int));
void    tbf_reprocess_q P((struct vif *));
int     tbf_dq_sel P((struct vif *, struct ip *));
void    tbf_send_packet P((struct vif *, struct mbuf *));
void    tbf_update_tokens P((struct vif *));
int     priority P((struct vif *, struct ip *));
#ifdef RSVP_ISI
int     ip_rsvp_vif P((struct socket *, struct mbuf *));
int     ip_rsvp_vif_done P((struct socket *, struct mbuf *));
int     ip_rsvp_force_done P((struct socket *));
int     rsvp_input P((struct mbuf *, struct ifnet *));
#endif /* RSVP_ISI */
#endif  /* IP_MULTICAST */

/* ip_output.c */
u_short get_ip_id P((void));
#ifdef IP_MULTICAST
int     ip_output P((struct mbuf *, struct mbuf *, struct route *, int,
	             struct ip_moptions *, struct gidstruct *));
#else
int     ip_output P((struct mbuf *, struct mbuf *, struct route *, int));
#endif /* IP_MULTICAST */
int     ip_output_post_fw P((struct ifnet *, struct mbuf *,
			     outbound_fw_args_t *));
outbound_fw_args_t *outbound_fw_save_args P((outbound_fw_args_t *));
void	outbound_fw_free_args P((outbound_fw_args_t *));
struct  mbuf *ip_insertoptions P((struct mbuf *, struct mbuf *, int *));
int     ip_optcopy P((struct ip *, struct ip *));
int     ip_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int     ip_changeversion P((int, struct socket *, struct inpcb *));
int     ip_pcbopts P((struct mbuf **, struct mbuf *));
int     localaddr_notcast P((struct in_addr));
#ifdef IP_MULTICAST
int ip_setmoptions P((struct socket *, int, struct ip_moptions **,
	              struct mbuf *));
int ip_getmoptions P((int, struct ip_moptions *, struct mbuf **m));
void ip_freemoptions P((struct ip_moptions *));
void ip_mloopback P((struct ifnet *, struct mbuf *, struct sockaddr_in *));
#endif /* IP_MULTICAST */

/* ip_pmtu.c */
int ip_pmtu_timeout P((struct pmtu_entry *, void *));
struct pmtu_entry *pmtu_alloc P((struct sockaddr *, struct rtentry *,int));
void pmtu_setmtu P((struct sockaddr *, struct rtentry *,__ulong32_t));
void pmtu_del_request P((short,void *));
int udp_pmtu_discover_init P((long *, struct netopt *));
int tcp_pmtu_discover_init P((long *, struct netopt *));
int pmtu_default_age_init P((long *, struct netopt *));
int pmtu_redis_intrvl_init P((long *, struct netopt *));
int pmtu_default_age_upd P((struct pmtu_entry *, void *));
int ip_setdupmtu P((struct radix_node *, void *));
int pmtu_expire_init P((long *, struct netopt *));
int pmtu_expire_upd P((struct pmtu_entry *, void *));
void pmtu_equalifmtu P((struct ifnet *));

/* md5.c */
void    MD5Update();
void    MD5Final();
void    Transform ();

/* rand.c */
uint    inetrandom P((void));

/* raw_ip.c */
void    rip_init P((void));
void    rip_input P((struct mbuf *, int));
struct mbuf *raw_saveif P((u_short ));
int     rip_output P((struct mbuf *, struct socket *, u_long));
int     rip_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int     rip_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
	                        struct mbuf *));

/* raw_ip6.c */
int     rip6_input P((struct mbuf **, struct mbuf **, caddr_t, caddr_t *));
struct mbuf *raw6_saverecv P((struct mbuf *, int, struct mbuf *));
struct mbuf *raw6_saveopt P((caddr_t, struct mbuf *, int, int, int));
int     rip6_output P((struct mbuf *, struct socket *, struct in6_addr *));
int     rip6_output_ancillary P((struct mbuf *, struct socket *,
                struct in6_addr *, int, struct ip6ancillary *));
int     rip6_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int     rip6_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
	        struct mbuf *));
void    rip6_ctlinput P((int, struct sockaddr *, struct ipv6 *,
	        struct mbuf *));

/* tcp_debug.c */
void    tcp_trace P((int, int, struct tcpcb *, struct tcpiphdr *, int, struct tcp_opt*));
void    tcp_systrace P((struct tcp_debug *, struct tcpcb *));
/* for tcp_debug table size option settable by no cmd */
int     tcp_ndbg_change P((long* , struct netopt *));

/* tcp_input.c */
#ifdef __64BIT_KERNEL
int     tcp_reass P((struct tcpcb *, struct tcpipreasshdr *, struct mbuf *, int));
#else
int     tcp_reass P((struct tcpcb *, struct tcpiphdr *, struct mbuf *, int));
#endif /* __64BIT_KERNEL */
int     get_seqnum P((in_addr_t, ushort, in_addr_t, ushort));
void    tcp_input P((struct mbuf *, int));
int     tcp_input0 P((struct mbuf **, struct mbuf **, caddr_t, caddr_t *));
void    tcp_adjust_buffers P((struct tcpcb *));
void    tcp_dooptions P((struct tcpcb *, struct mbuf *, struct tcpiphdr *,
	        u_int *, u_int *, struct tcp_options_received *));
int     tcp_auth0 P((int, int, int, struct inpcb *, uint16_t));
int     tcp_auth P((struct tcp_options_received*, struct inpcb *, int));
void    tcp_pulloutofband P((struct socket *, struct tcpiphdr *,
	                        struct mbuf *));
void    tcp_xmit_timer P((struct tcpcb *, short));
int     tcp_mss P((register struct tcpcb *, u_short));
void    tcp_setmss P((register struct tcpcb *));

/* tcp_output.c */
int     tcp_output P((struct tcpcb *));
void    tcp_setpersist P((struct tcpcb *));

/* tcp_subr.c */
int     tcp_ephemeral_low_change P((char *, struct netopt *));
int     tcp_ephemeral_high_change P((char *, struct netopt *));
int     tcp_init P((void));
void    tcp_template P((struct tcpcb *));
void    tcp_resprst P((struct tcpcb *, struct tcpiphdr *, struct mbuf *,
	        tcp_seq, tcp_seq, int));
void    tcp_sendkeep P((struct tcpcb *, proto_tcp_seq, proto_tcp_seq));
struct  tcpcb *tcp_newtcpcb P((struct inpcb *));
struct  tcpcb *tcp_drop P((struct tcpcb *, int));
struct  tcpcb *tcp_close P((struct tcpcb *));
void    tcp_drain P((void));
void    tcp_notify P((struct inpcb *, int));
void    tcp_ctlinput P((int, struct sockaddr *, caddr_t));
void    tcp_quench P((struct inpcb *, int));
void    tcp_pmtuchange P((struct inpcb *, int));
void    tcp_resend P((struct inpcb *, int));
int     tcp_delayack_set P((char *, struct netopt *));
int     tcp_delayackports_set P((char *, struct netopt *));

/* tcp_timer.c */
void    tcp_fasttimo P((void));
void    tcp_slowtimo P((void));
void    tcp_canceltimers P((struct tcpcb *));
struct  tcpcb *tcp_timers P((struct tcpcb *, int));
void    tcp_time_wait_timer P((int, int));
void    tcp_timer_init P((void));
void    reroute P((struct inpcb *));
void    tcp_low_rto_init P((struct tcpcb *, int));
void    tcp_twheel_rexmt_timo P((struct tcpcb *));


/* tcp_usrreq.c */
int     tcp_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
	                        struct mbuf *));
struct tcpach *tcp_achalloc P((void));
void    tcp_achfree P((struct tcpach *));
struct tcpach *tcp_achref P((uint16_t));
void    tcp_achset P((uint16_t, struct tcpach *));
void    tcp_aclclear_nolock P((uint16_t));
void    tcp_aclclear P((uint16_t));
void    tcp_aclflush P((void));
int     tcp_acladd P((struct tcpdac *));
int     tcp_acldel P((struct tcpdac *));
int     tcp_aclls P((uint16_t, struct mbuf *));
void    tcp_aclbind P((uint16_t, struct inpcb *));
int     tcp_lspriv P((struct mbuf *));
int     isprivport P((uint16_t));
int     tcp_setpriv P((uint16_t));
int     tcp_unsetpriv P((uint16_t));
int     tcp_ctloutput P((int, struct socket *, int, int, struct mbuf **));
int     tcp_attach P((struct socket *));
struct  tcpcb *tcp_disconnect P((struct tcpcb *));
struct  tcpcb *tcp_usrclosed P((struct tcpcb *));
struct  tcpcb *tcp_send_and_disconnect P((struct tcpcb *, struct mbuf *,
	        int *));
struct  tcpcb *tcp_send_and_kern_disconnect P((struct tcpcb *, struct mbuf *,
	        int *));
struct	tcpcb *tcp_disconnectreuse P((struct tcpcb *));
struct	tcpcb *tcp_closereuse P((struct tcpcb *, int));

/* udp_usrreq.c */
int     udp_ephemeral_low_change P((char *, struct netopt *));
int     udp_ephemeral_high_change P((char *, struct netopt *));
void    udp_init P((void));
caddr_t udp_findmac P((struct mbuf *, struct ip *, caddr_t));
void    udp_input P((struct mbuf *, int));
void    udp_input1 P((struct mbuf *, int, caddr_t));
int     udp_input0 P((struct mbuf **, struct mbuf **, caddr_t, caddr_t *));
struct mbuf *udp_saveopt P((caddr_t, struct mbuf *, int, int, int));
void    udp_notify P((struct inpcb *, int));
void    udp_ctlinput P((int, struct sockaddr *, caddr_t));
int     udp_output P((struct inpcb *, struct mbuf *, struct mbuf *,
	                        struct mbuf *));
int     udp_usrreq P((struct socket *, int, struct mbuf *, struct mbuf *,
	                        struct mbuf *));
int     udp_send P((struct socket *, struct mbuf *, struct uio *, struct mbuf *,
	                struct mbuf *, int));
void    delay_sbdroprecord P((struct sockbuf *, struct mbuf **));
int     udp_receive P((struct socket *, struct mbuf **, struct uio *,
	        struct mbuf **, struct mbuf **, int *));
int     udp_cksum_and_move P((struct mbuf *, struct uio *, u_int hdrsum,
	        struct socket *));

/* qos_stubs.c */
int    qos_input_stub P((struct mbuf *, int));
int    qos_usrreq_stub P((struct socket *, int, struct mbuf *, struct mbuf *,
	                struct mbuf *));
void   qos_ctlinput_stub P((int, struct sockaddr *, caddr_t));
void   qos_init P((void));

/* in_dgd.c */
void    dgd_init P((void));
void    dgdsched P((void));
void    dgdretrysched P((void));
void    add_gateway P((struct rtentry *));
void    del_gateway P((struct rtentry *));
void    del_gateway_nolock P((struct rtentry *, int));
int     ping_one_gateway P((struct active_dgd_gateway *));
void    dgdretry P((void));
void    ping_gateways P((void));
void    dgd_input P((struct mbuf *));
void    dgd_input6 P((struct mbuf *));
void    clear_ping_flags P((void));
void    set_ping_flag P((struct rtentry *));

#ifndef CONST
#define CONST
#endif

/* externs */

/* Any 'no' options used in multiple modules are externed here. */
extern long rfc1122addrchk;
extern long maxttl;
extern long rfc1323;
extern long rfc1323_dflt;
extern long pmtu_default_age;
extern long pmtu_default_age_dflt;
extern long udp_pmtu_discover;
extern long tcp_pmtu_discover;
extern long tcp_sendspace;
extern long tcp_recvspace;
extern long tcp_mssdflt;
extern long tcp_keepinit;
extern long tcp_keepidle;
extern long tcp_keepintvl;
extern long tcp_keepcnt;
extern long tcp_maxidle;
extern long tcp_ttl;
extern long udp_ttl;

extern long tcp_rtolow;
extern long tcp_rtohigh;
extern long tcp_rtolimit;
extern long tcp_rtolength;
extern long tcp_rtoshift;
extern long tcpcksum;
extern long tcprexmtthresh;
extern long tcppredack;  /* XXX debugging: times hdr predict ok for acks */
extern long tcppreddat;  /* XXX # times header prediction ok for data packets */
extern long tcp_timewait;
extern long tcp_newreno;
extern long tcp_newreno_dflt;
extern long tcp_nagle_limit;
extern long tcp_init_window;
extern long tcp_init_window_dflt;
extern long rfc2414;
extern long rfc2414_dflt;
extern long tcp_ecn;
extern long tcp_ecn_dflt;
extern long tcp_limited_transmit;
extern long tcp_limited_transmit_dflt;
extern long icmp6_errmsg_rate;
extern long icmp6_errmsg_rate_dflt;
extern long tcp_maxburst;
extern long tcp_maxburst_dflt;
extern long	tcp_finwait2;
extern long	tcp_finwait2_dflt;

/*
 * RFC 1323 - timestamp clock.  It will be initialized to the kernel
 * time var (time in seconds since Epoch) and then incremented by
 * tcp_slowtimo.  Thus it's granularity is 500ms ticks...
 */
extern u_long timestamp_clock;



/*
 * RFC 1323 timestamp clock.
 */
extern u_long timestamp_clock;

/*
 * DHCP uses this to enable passing up packets received on an interface
 * with no address bound yet...the chicken before the egg deal...
 */
extern int dhcp_mode;

extern struct ifqueue pfctlinputq;
extern CONST u_char inetctlerrmap[];
#ifdef IP_MULTICAST
extern struct igmpstat igmpstat;
extern struct dist_igmpstat *dist_igmpstat[];
#endif
extern int in_interfaces;
extern CONST struct   in_addr zeroin_addr;
#ifdef INETPRINTFS
extern long inetprintfs;
extern long inetprintfs_dflt;
extern long ip6printfs;
extern long ip6printfs_dflt;
#endif
#undef P
#endif /* _PROTO_INET_H_ */
#endif /* _KERNEL */
