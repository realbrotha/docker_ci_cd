/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53D src/bos/kernel/sys/atmsock.h 1.10                               */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)82	1.10  src/bos/kernel/sys/atmsock.h, sysnet, bos53D, d2005_24A2 6/10/05 13:54:14 */
/*
 *   COMPONENT_NAME: SYSNET
 *
 *   ORIGINS: 27
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */

#ifndef H_ATMSOCK_H
#define H_ATMSOCK_H

#include <sys/call_ie.h>

#define SO_ATM_CALLING          1
#define SO_ATM_CALLED           2
#define SO_ATM_AAL_PARM         3
#define SO_ATM_TRAFFIC_DES      4
#define SO_ATM_BEARER           5
#define SO_ATM_BHLI             6
#define SO_ATM_BLLI             7
#define SO_ATM_QOS_PARM         8
#define SO_ATM_TRANSIT_SEL      9
#define SO_ATM_MAX_PEND         10
#define SO_ATM_PARAM            11
#define SO_ATM_CAUSE            12
#define SO_ATM_ACCEPT           13

#define SO_ATM_ADDPARTY         14      /* P2MP */
#define SO_ATM_DROPPARTY        15      /* P2MP */
#define SO_ATM_LEAF_IND         16      /* P2MP */

#define NDD_ATM_LEAF_NOCHANGE      0    /* P2MP */
#define NDD_ATM_LEAF_CONNECTED     1    /* P2MP */
#define NDD_ATM_LEAF_DISCONNECTED  2    /* P2MP */


int ndd_atm_usrreq( struct socket *so, int req, struct mbuf *m,
                struct mbuf *nam, struct mbuf *control );

int ndd_atm_ctloutput( int op, struct socket *so, int level, int optname,
               struct mbuf **mp );

int ndd_atm_send( struct socket *so, struct mbuf *addr, struct uio *uio,
          struct mbuf *top, struct mbuf *control, int flags );

int ndd_atm_receive( struct socket *so, struct mbuf **paddr, struct uio *uio,
                 struct mbuf **mp0, struct mbuf **controlp, int *flagsp );


typedef struct sockaddr_ndd_atm sockaddr_ndd_atm_t; /* ATM Socket Address */
typedef struct ndd_atm_alloc ndd_atm_alloc_t; /* Opened ATM device */
typedef struct atm_pcb  atm_pcb_t;            /* ATM Protocol Control Block */
typedef struct qelem    qelem_t;              /* For insque/remque */

/* ATM socket address */

struct sockaddr_ndd_atm {
   u_char sndd_atm_len;                     /* sizeof(sockaddr_ndd_atm_t) */
   u_char sndd_atm_family;                  /* AF_NDD */
   u_char sndd_atm_vc_type;                 /* CONN_PVC or CONN_SVC */
   char   sndd_atm_nddname[NDD_MAXNAMELEN]; /* ATM device name, i.e. atm0 */
  union {
    struct {
      call_pnum_t  sndd_atm_addr;
      call_pnum_t  sndd_atm_sub_addr;
    } atm_addr;
    atm_conn_id_t  conn_id;
  } atm_id;


};

/* Queue structure for insque/remque */

struct qelem {
   struct qelem *next;
   struct qelem *prev;
};

/* This is the ancor control block for an opened ATM device */
/* All PCBs using this device will be to it. */

struct ndd_atm_alloc {
   qelem_t              connect_chain; /* sockets that have just been bound
                                          or have been actively connected
                                          with the connect function */
   qelem_t              listen_chain;  /* listening sockets */
   qelem_t              accept_chain;  /* sockets created by accept */
   qelem_t              alloc_chain;   /* open ATM devices */
   struct ndd           *nddp;         /* ATM device ndd */
   uint                 reg_id;        /* ATM Call Manager reg_id for sockets
                                          on the connect chain */
   char                 name[NDD_MAXNAMELEN]; /* ATM device name, i.e. atm0 */
   call_pnum_t          atm_addr;      /* ATM address */
   call_pnum_t          atm_sub_addr;  /* ATM subaddress (optional) */
   uint                 flags;
#define NDD_ATM_ADDR_VALID      0x01   /* CALL_ADDR_REG has been received.
                                          This will be cleared when
                                          CALL_ADDR_REG is received */
   uint                 use;           /* Sockets using this ATM device */

   int                  reserved[20];  /* For future use */
};



/*
 * ATM Socket Protocol Control Block
 * One of these will be allocate when an ATM socket is created and
 * attached to the socket via the so_pcb field
 */

struct atm_pcb {
   struct socket   *so;         /* Owning socket */
   ndd_atm_alloc_t *allocp;     /* ATM device */
   uint            reg_id;      /* Call Manager reg_id */

   int             vc_handle;   /* connection handle */
   int             leaf_handle; /* leaf handle: pt to multi-pt only, or zero  */
   u_char          vc_type;     /* CONN_PVC or CONN_SVC */
   connect_ie_t    conn_ie;     /* connection signalling info */
   cause_t         cause;       /* last disconnect cause */
   u_char          max_pend;    /* max outstanding writes for video streams */

   int             flags;
#define NDD_ATM_HANDLE_VALID    0x01 /* CALL_ACK or CALL_ACCEPT received.
                                        Cleared when socket is disconnected. */
#define NDD_ATM_VIDEO           0x02 /* This is a video stream */
#define NDD_ATM_KILL_CALL       0x04 /* Disconnect this connection when
                                        CALL_ACK or CALL_ACCEPT is received
                                        and remove the demux filter if it
                                        one exists */
#define NDD_ATM_DISC            0x08 /* This connection has been disconnected
                                        by a CALL_DISCON */
#define NDD_ATM_CONNECT         0x10 /* This sockets is on the connect chain */
#define NDD_ATM_LISTEN          0x20 /* This sockets is on the listen  chain */
#define NDD_ATM_ACCEPT          0x40 /* This sockets is on the accept  chain */
#define NDD_ATM_REG             0x80 /* Only for tracing.  This is on the
                                        reg chain */
#define NDD_ATM_WAKEUP        0x0100 /* This is on the wakeup chain */
#define NDD_ATM_PARMS_CHANGED 0x0200 /* To support variable PVC rate */

   int          refcnt;         /* reference count */

   qelem_t      reg_chain;      /* Sockets sharing this Call Manager reg_id.
                                   Note that there is no ancor in the alloc
                                   structure.  This chain will either be
                                   the PCBs on the connect chain, or a
                                   combination of PCBs on the listen
                                   chain and the accept chain. */

   qelem_t      connect_chain;  /* Chaining fields for the chains that are */
   qelem_t      listen_chain;   /* ancored in the alloc structure */
   qelem_t      accept_chain;
   qelem_t      wakeup_chain;   /* Temp chain of listening sockets that
                                   need to be woken up because of a
                                   CALL_ADDR_DEREG.  This is necessary
                                   because NDD_ATM_LOCK must be held to
                                   walk the listen_chain and SOCKET_LOCK
                                   must be held to wakeup the socket, which
                                   is a heirarchy violation.  Thus, a temp
                                   chain of the sockets is created and
                                   those are woken up after NDD_ATM_LOCK
                                   is released.  The sockets are referenced
                                   with NDD_ATMRC_REF so they cannot be
                                   nuked before the wakeup has been called. */

   qelem_t              leaf_chain;    /* P2MP leaf indications */

   int                  reserved[20];  /* For future use */
};

/* P2MP */

struct ndd_atm_leaf_ind {
   u_int32         status;
   u_int32         leaf_ID;
   u_int32         reason;
};

#define sotoatmpcb(so)          ((atm_pcb_t *)(so)->so_pcb)

#define OFFSETOF(a1,a2)         (int)(size_t)&(((a1 *)0)->a2)

#define NDD_ATM_LOCK()   \
   intpri = disable_lock( PL_IMP, &ndd_atmsock_lock )
#define NDD_ATM_UNLOCK() \
   unlock_enable( intpri, &ndd_atmsock_lock )

#define NDD_ATM_USRREQ_LOCK()   \
   intprij = disable_lock( PL_IMP, &ndd_atmsock_usrreq_lock )
#define NDD_ATM_USRREQ_UNLOCK() \
   unlock_enable( intprij, &ndd_atmsock_usrreq_lock )


#define NDD_ATM_ENQUEUE_ALLOC(allocp) {                   \
                                                          \
   insque( &allocp->alloc_chain, &atm_alloc_ancor );      \
                                                          \
}

#define NDD_ATM_DEQUEUE_ALLOC(allocp) {                     \
                                                            \
   remque( &allocp->alloc_chain );                          \
}

#define NDD_ATM_FIND_ALLOC(addr, allocpp) {                \
   ndd_atm_alloc_t      *alloc_work;                       \
   qelem_t              *qwork=&atm_alloc_ancor;           \
   *allocpp = NULL;                                         \
                                                           \
   qwork = atm_alloc_ancor.next;                          \
   while (qwork != &atm_alloc_ancor ) {                            \
      alloc_work = (ndd_atm_alloc_t *)((char *)qwork -                  \
                   OFFSETOF(ndd_atm_alloc_t, alloc_chain));              \
      if ( strcmp(alloc_work->name, addr->sndd_atm_nddname) == 0 ) {     \
         *allocpp = alloc_work;                                           \
         break;                                                          \
      } else {                                                           \
         qwork= qwork->next;                                             \
      } /* endif */                                                      \
   } /* endwhile */                                                      \
}


#define NDD_ATM_ENQ_PCB(pcbq, ancor, chain, offset) {   \
   TRCHKL2T_NOMTRC(HKWD_ATMSOCK | hkwd_atmsock_pcbenq, (char *)pcbq - offset, chain ); \
   insque( pcbq, ancor );                \
}

#define NDD_ATM_DEQ_PCB(pcbq, chain, offset) {          \
   TRCHKL2T_NOMTRC(HKWD_ATMSOCK | hkwd_atmsock_pcbdeq, (char *)pcbq - offset, chain ); \
   remque( pcbq );                       \
}

/* P2MP add the other chain, offset and trace later */

#define NDD_ATM_ENQ_LEAF(leafq, ancor) {   \
   insque( leafq, ancor );                 \
}

#define NDD_ATM_DEQ_LEAF(leafq) {          \
   remque( leafq );                        \
}

#define NDD_ATMRC_REF(atm_pcb) { \
   fetch_and_add(&((atm_pcb)->refcnt), 1); \
}

#define NDD_ATMRC_UNREF(atm_pcb) { \
   if (fetch_and_add(&((atm_pcb)->refcnt), -1) == 1) { \
      if (atm_pcb->refcnt <= 1) {                      \
         atm_pcb->so->so_state |= SS_NOCONN;                   \
         soputonfreelist(atm_pcb->so);                          \
         TRCHKL1T_NOMTRC(HKWD_ATMSOCK | hkwd_atmsock_netfree, atm_pcb ); \
      } \
   } \
}

/* Trace entries */

/* #define HKWD_ATMSOCK    0x3A500000 */

#define hkwd_atmsock_attach             1
#define hkwd_atmsock_bind               2
#define hkwd_atmsock_addr               3
#define hkwd_atmsock_listen             4
#define hkwd_atmsock_connpvc            5
#define hkwd_atmsock_connsvc            6
#define hkwd_atmsock_accept             7
#define hkwd_atmsock_disc               8
#define hkwd_atmsock_detach             9
#define hkwd_atmsock_abort              10
#define hkwd_atmsock_connerr            11
#define hkwd_atmsock_calldisc           12
#define hkwd_atmsock_shut               13
#define hkwd_atmsock_indentry           14
#define hkwd_atmsock_indexit            15
#define hkwd_atmsock_callack            16
#define hkwd_atmsock_addfill            17
#define hkwd_atmsock_adderr             18
#define hkwd_atmsock_delfill            19
#define hkwd_atmsock_svcreg             20
#define hkwd_atmsock_svcdereg           21
#define hkwd_atmsock_svcerr             22
#define hkwd_atmsock_netfree            23
#define hkwd_atmsock_callacc            24
#define hkwd_atmsock_work               25
#define hkwd_atmsock_allocp             26
#define hkwd_atmsock_allocfree          27
#define hkwd_atmsock_pcbenq             28
#define hkwd_atmsock_pcbdeq             29
#define hkwd_atmsock_lisq               30
#define hkwd_atmsock_regreg             31
#define hkwd_atmsock_regdereg           32
#define hkwd_atmsock_regerr             33
#define hkwd_atmsock_reglis             34
#define hkwd_atmsock_kill               35
#define hkwd_atmsock_fvtstart           36
#define hkwd_atmsock_fvtfinish          37
#define hkwd_atmsock_rcventry           38
#define hkwd_atmsock_rcvexit            39
#define hkwd_atmsock_sndentry           40
#define hkwd_atmsock_sndexit            41
#define hkwd_atmsock_leafack            42
#define hkwd_atmsock_leafdisc           43
#define hkwd_atmsock_addp               44
#define hkwd_atmsock_drop               45
#define hkwd_atmsock_leafind            46

#endif
