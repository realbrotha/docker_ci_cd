/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/kernel/sys/ndd_var.h 1.6                                */
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
/* @(#)83	1.6  src/bos/kernel/sys/ndd_var.h, sysnet, bos530 2/4/03 17:57:38 */
/*
 *   COMPONENT_NAME: SOCKINC
 *
 *   FUNCTIONS: sotorawnddpcb
 *
 *
 *   ORIGINS: 27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1993
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef _H_NDD_VAR
#define _H_NDD_VAR
#include <sys/ndd.h>
#include <sys/cdli.h>

#define SNDD_MAXFILTER  64

/*
 * generic ndd sockaddr
 */
struct sockaddr_ndd {
        u_char  sndd_len;
        u_char  sndd_family;
        char    sndd_nddname[NDD_MAXNAMELEN];
        u_int   sndd_filterlen;
        u_char  sndd_data[SNDD_MAXFILTER];
};

struct sockaddr_ndd_8022 {
        u_char                  sndd_8022_len;
        u_char                  sndd_8022_family;
        u_char                  sndd_8022_nddname[NDD_MAXNAMELEN];
        u_int                   sndd_8022_filterlen;
        struct ns_8022          sndd_8022_ns;
};

#define sndd_8022_filtertype    sndd_8022_ns.filtertype
#define sndd_8022_dsap          sndd_8022_ns.dsap
#define sndd_8022_orgcode       sndd_8022_ns.orgcode
#define sndd_8022_ethertype     sndd_8022_ns.ethertype

struct nddctl {
        u_int           nddctl_buflen;
        caddr_t         nddctl_buf;
};

#define NDD_CTL_MAXBUFLEN       4096

/*
 * NDD Protocols
 */

#define NDD_PROT_ETHER   1
#define NDD_PROT_TOK     2
#define NDD_PROT_FDDI    3
#define NDD_PROT_FCS     4
#define NDD_PROT_ATM     5

#ifdef sotorawcb
/*
 * Common structure pcb for raw ndd protocol access.
 * Here are ndd specific extensions to the raw control block,
 * and space is allocated to the necessary sockaddrs.
 */
struct raw_nddpcb {
        struct rawcb            rndd_rcb; /* common control block prefix */
        struct ndd              *rndd_sendnddp;
        struct ndd              *rndd_recvnddp;
        struct sockaddr_ndd     rndd_faddr;
        struct sockaddr_ndd     rndd_laddr;
	int			rndd_refcnt;
};

#define NDDPCB_REF(rp) { \
	fetch_and_add(&((rp)->rndd_refcnt), 1); \
}

#define NDDPCB_UNREF(rp) { \
	fetch_and_add(&((rp)->rndd_refcnt), -1); { \
}

#endif

#define sotorawnddpcb(so)       ((struct raw_nddpcb *)(so)->so_pcb)

#endif  /* _H_NDD_VAR */
