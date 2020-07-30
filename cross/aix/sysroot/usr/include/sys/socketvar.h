/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53X src/bos/kernel/sys/socketvar.h 1.12.11.3                        */
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
/* @(#)74       1.12.11.3  src/bos/kernel/sys/socketvar.h, sockinc, bos53X, x2010_32A4 4/9/10 12:59:34 */
/*
 *   COMPONENT_NAME: SOCKINC
 *
 *   FUNCTIONS: 
 *              SOCKET_ISLOCKED
 *              SOCKET_LOCK
 *              SOCKET_LOCK2
 *              SOCKET_LOCKINIT
 *              SOCKET_UNLOCK
 *              SOCKET_UNLOCK2
 *              SOHASUAREA
 *              sballoc
 *              sbfree
 *              sbspace
 *              sodomain
 *              sonewconn
 *              soreadable
 *              sorwakeup
 *              sosendallatonce
 *              sowatomic
 *              sowriteable
 *              sowwakeup
 *              so2gidstruct
 *
 *
 *   ORIGINS: 26,27,85
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
 * OSF/1 1.2
 */
/* socketvar.h  2.1 16:08:08 4/20/90 SecureWare */
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
 * Copyright (c) 1982, 1986, 1990 Regents of the University of California.
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
 *      Base:   socketvar.h     7.6 (Berkeley) 9/4/89
 *      Merged: socketvar.h     7.11 (Berkeley) 6/30/90
 */

#ifndef _SYS_SOCKETVAR_H_
#define _SYS_SOCKETVAR_H_

#ifdef __cplusplus
extern "C" {

struct protosw;
struct mbuf;
struct proc;
#endif

#if     defined(_KERNEL) && !defined(_NET_GLOBALS_H_)
#include "net/net_globals.h"
#endif

#include <sys/time.h>

#if     MACH
#include <sys/secdefines.h>
#if     SEC_ARCH
#include <sys/security.h>
#endif
#endif
#include <sys/ras_trace.h>

/* Structure inside the socket structure to store the pid and tid
 * of the associated process and thread.
 */
struct prid {
	pid_t pid;
	tid_t tid;
};

/*
 * Kernel structure per socket.
 * Contains send and receive buffer queues,
 * handle on protocol and pointer to protocol
 * private data and error information.
 */
struct socket {
        short   so_type;                /* generic type, see socket.h */
        short   so_options;             /* from socket call, see socket.h */
        ushort  so_linger;              /* time to linger while closing */
        short   so_state;               /* internal state flags SS_*, below */
        caddr_t so_pcb;                 /* protocol control block */
        struct  protosw *so_proto;      /* protocol handle */
        struct  socklocks *so_lock;     /* socket structure lock(s) */
/*
 * Variables for connection queueing.
 * Socket where accepts occur is so_head in all subsidiary sockets.
 * If so_head is 0, socket is not related to an accept.
 * For head socket so_q0 queues partially completed connections,
 * while so_q is a queue of connections ready to be accepted.
 * If a connection is aborted and it has so_head set, then
 * it has to be pulled out of either so_q0 or so_q.
 * We allow connections to queue up based on current queue lengths
 * and limit on number of queued connections for this socket.
 */
        struct  socket *so_head;        /* back pointer to accept socket */
        struct  socket *so_q0;          /* queue of partial connections OR */
					/* array of sockets for socketgroup */
        struct  socket *so_q;           /* queue of incoming connections OR */
					/* pointer to main socketgroup socket */
/*        struct  socket *so_dq; */          /* unused */
/*      Replace so_dq with reference count */
        long    so_refcnt;              /* Socket and pcb can't be freed if refcnt != 0 */

        short   so_q0len;               /* partials on so_q0 OR */
					/* number of sockets in socketgroup */
        short   so_qlen;                /* number of connections on so_q */
        short   so_qlimit;              /* max number queued connections */
        short   so_dqlen;               /* unused */
        short   so_timeo;               /* connection timeout */
        u_short so_error;               /* error affecting connection */
        short   so_special;             /* special state flags SP_*, below */
        short   so_special2;            /* special state flags SP2_*, below */
        pid_t   so_pgid;                /* pgid for signals */
        u_long  so_oobmark;             /* chars to oob mark */
/*
 * Variables for socket buffering.
 */
        struct  sockbuf {
                u_long  sb_cc;          /* actual chars in buffer */
                u_long  sb_hiwat;       /* max actual char count */
                u_long  sb_mbcnt;       /* chars of mbufs used */
                u_long  sb_mbmax;       /* max chars of mbufs to use */
                long    sb_lowat;       /* low water mark */
                struct  mbuf *sb_mb;    /* the mbuf chain */
                union {                 /* process selecting read/write */
                        struct proc *sb_selproc;        /* UNIX */
                        struct sbselque {               /* MACH */
                                struct sbselque *next, *prev;
                        } sb_selque;
                } sb_select;
                ushort  sb_reqevents;   /* current pending events */
                int     (*sb_iodone)(); /* I/O done function */
                caddr_t sb_ioarg;       /* arg for sb_iodone */
                struct  mbuf *sb_lastpkt; /* last packet of mbuf chain */
                tid_t   sb_wakeone;     /* SB_WAKEONE sleep event */
                caddr_t sb_timer;       /* pre-allocated trb */
                short   sb_flags;       /* flags, see below */
                ushort  sb_timeo;       /* timeout for read/write */
#ifdef  _KERNEL
                void    (*sb_wakeup)(caddr_t, int);
#else
                void    (*sb_wakeup)(); /* upcall instead of sowakeup */
#endif
                caddr_t sb_wakearg;     /* (*sb_wakeup)(sb_wakearg, state) */
		tid_t	sb_lockwaiting;	/* list of threads waiting for SB_LOCK flag */
        } so_rcv, so_snd;
#define sb_sel          sb_select.sb_selproc
#define sb_selq         sb_select.sb_selque
#define SB_MAX          (1024*1024)       /* default for max chars in sockbuf */
#define SB_LOCK         0x01            /* lock on data queue */
#define SB_WANT         0x02            /* someone is waiting to lock */
#define SB_WAIT         0x04            /* someone is waiting for data/space */
#define SB_SEL          0x08            /* someone is selecting */
#define SB_ASYNC        0x10            /* ASYNC I/O, need signals */
#define SB_NOINTR       0x40            /* operations not interruptible */
#define SB_WAKEONE      0x80            /* wakeup only one on notify */
#define SB_WAITING      0x100           /* MSG_WAITALL receive in progress */
#define SB_INHERIT      (SB_NOINTR|SB_WAKEONE)
#define SB_PSEG		0x200           /* buffers may be in private segment */
#define SB_KIODONE      0x400           /* socket kernel iodone */
#define SB_NOTIFY       (SB_WAIT|SB_SEL|SB_ASYNC|SB_WAKEONE|SB_KIODONE)
#define SB_NOSELECT     0x800

        caddr_t so_tpcb;                /* Wisc. protocol control block XXX */
        void  *fdev_chain_f;            /* anchor of chain of fsel_cb's     */
        caddr_t so_sec_info;            /* BESTX security info */
        void    *so_qos;                /* Quality Of Service cookie        */
        struct  gidstruct *so_gidlist;  /* Group ID list for socket owner   */
        caddr_t so_private;             /* Used by NFS                      */
        uid_t   so_uid;                 /* UID of socket owner              */
        ushort  so_bufsize;             /* Size of interface-supplied buffer */
        ushort  so_threadcnt;           /* Semaphore used for freeing socket */
        struct  socket *so_nextfree;    /* Link for free_sockets list       */
        int     so_siguid;
        int     so_sigeuid;
        int     so_sigpriv;
/* These belong in the sockbufs, but we can't change those.  We use
 * these to set the sb_timeo field in the sockbufs.
 */
        struct timeval so_sndtimeval;
        struct timeval so_rcvtimeval;
	struct 	saioq	*so_saioq;
	struct saioq_head *so_saioq_head;
        tid_t   so_accept;              /* Chain of threads accepting       */
        int     so_frcatime;            /* FRCA Connection Time             */
	int	so_isnoflags;		/* Don't use isno options if set
					   by setsockopt		    */
	u_long	so_rcvlen;		/* used by MSG_WAITALL 		    */
	struct socket *so_frca_backup ;	/* used by frca to recall listen so */
	struct socket *so_frca_assoc ;	/* used by frca to find assoc so */
	long	so_frca_bucket;		/* used by frca to alloc more bytes..*/
	int     (*so_iodone)(); 	/* I/O done function 		    */
	short	so_iodoneflags; 	/* flags, see below 	  	    */
        short   so_trclev;              /* trace level for the socket */
        caddr_t so_ioarg;	        /* arg for so_iodone */
	tid_t	so_inprogwaiting;	/* list of threads waiting for SP_INPROGRESS flag */
	struct socklocks *so_lpfreelist;/* Chain of socklocks to be freed.   */	
	struct	prid prid;		/* proces id and thread id */
	u_long 	so_flag;		/* Flag to use for any socket options D746955 */
	long	so_reserved[3];		/* Room to grow...		    */
};

/* so_flag bits. D746955 */
#define SO_FLAG_TCPTR		0x01	/* TCPTR Flag to monitor socket connectoins */

#define SO_IODONE_KACCEPT	0x01
#define SO_IODONE_KREAD		0x02
#define SO_IODONE_KWRITE	0x04


#define SO_NOISNO_TCP_SENDSPACE 0x00000001
#define SO_NOISNO_TCP_RECVSPACE 0x00000002
#define SO_NOISNO_TCP_NODELAY   0x00000004
#define SO_NOISNO_RFC1323       0x00000008

/* Values for so_trclev */
#define SO_TRC_NONE             0
#define SO_TRC_MIN              CT_LVL_MINIMAL
#define SO_TRC_NORM             CT_LVL_NORMAL
#define SO_TRC_DTL              CT_LVL_DETAIL

#define soorfield SOORFIELD
#define SOORFIELD(so, field, value) \
        { \
                so->field## |= value; \
                if (so->so_special & SP_GROUP && so->so_q0) { \
                        int z2; \
                        struct socket *sg2; \
                        for (z2 = 1; z2 < so->so_q0len; z2++) { \
                                sg2 = ((struct socket **)so->so_q0)[z2]; \
                                sg2->field## |= value; \
                        } \
                } \
        }

#define soandfield SOANDFIELD
#define SOANDFIELD(so, field, value) \
        { \
                so->field## &= value; \
                if (so->so_special & SP_GROUP && so->so_q0) { \
                        int z2; \
                        struct socket *sg2; \
                        for (z2 = 1; z2 < so->so_q0len; z2++) { \
                                sg2 = ((struct socket **)so->so_q0)[z2]; \
                                sg2->field## &= value; \
                        } \
                } \
        }

#define sosetrcvwakearg SOSETRCVWAKEARG
#define SOSETRCVWAKEARG(so) \
        { \
                so->so_rcv.sb_wakearg = (caddr_t)so; \
                if (so->so_special & SP_GROUP && so->so_q0) { \
                        int z2; \
                        struct socket *sg2; \
                        for (z2 = 1; z2 < so->so_q0len; z2++) { \
                                sg2 = ((struct socket **)so->so_q0)[z2]; \
                                sg2->so_rcv.sb_wakearg = (caddr_t)sg2; \
                        } \
                } \
        }

#define SOMAXBUFSIZE    (65536)

#define EYEC_SOCKETA 0x25736F636B657441ull /* %socketA */
#define EYEC_SOCKETF 0x25736F636B657446ull /* %socketF */

struct socket_plus {
        eye_catch8b_t	sop_eyecat;
        struct socket	sop_so;
};

#define sotosop(so)     (struct socket_plus *)((void *)so - sizeof(eye_catch8b_t))

#define SOFREE(so) 	{	\
			soplus = sotosop(so);			\
			soplus->sop_eyecat = EYEC_SOCKETF;	\
			NET_FREE(soplus, M_SOCKET);		\
		}

#define CHECK_SOCKET(so)        					\
        if ((eye_catch8b_t) (((struct socket_plus *)((void *)so - 	\
                sizeof(eye_catch8b_t)))->sop_eyecat) != EYEC_SOCKETA) 	\
                        panic("socket eyec not set");

struct saioq_head {
	struct saioq 	*anchor;
	struct saioq 	*last;
};

struct saioq {
	struct saioq 	*next;
	int		count;
	int		freeflag;
	int		sigval;
};

#define SAIOQ_LOCK 	disable_lock(PL_IMP, &saioq_lock)
#define SAIOQ_UNLOCK(x)	unlock_enable(x, &saioq_lock)

/*
 * Socket state bits.
 */
#define SS_NOFDREF              0x001   /* no file table ref any more */
#define SS_ISCONNECTED          0x002   /* socket connected to a peer */
#define SS_ISCONNECTING         0x004   /* in process of connecting to peer */
#define SS_ISDISCONNECTING      0x008   /* in process of disconnecting */
#define SS_CANTSENDMORE         0x010   /* can't send more data to peer */
#define SS_CANTRCVMORE          0x020   /* can't receive more data from peer */
#define SS_RCVATMARK            0x040   /* at mark on input */

#define SS_PRIV                 0x080   /* privileged for broadcast, raw... */
#define SS_NBIO                 0x100   /* non-blocking ops */
#define SS_ASYNC                0x200   /* async i/o notify */
#define SS_QUEUE		0x800   /* async queueing */
#define SS_SPLICED		0x1000  /* spliced socket */
#define SS_NOCONN               0x2000  /* connection is closed (or never existed) */


/*
 * Special socket state bits.
 */
#define SP_NOUAREA              0x0004  /* no u-area available (XTI - XXX) */
#define SP_LOCKABLE             0x0008  /* socket of parallel domain */
#define SP_CLOSING              0x0010  /* closing a listening socket */
#define SP_RWAKEUP		0x0020  /* sorwakeup pending release of lock */
#define SP_WWAKEUP		0x0040  /* sowwakeup pending release of lock */
#define SP_EXTPRIV              0x0080  /* SS_PRIV managed externally */
#define SP_XPG1170              0x0100  /* Follow SPEC1170 semantics */
#define SP_MEMCOMPRESS          0x0200  /* socket+gidlist+inpcb+tcpcb grouped */
#define SP_ACCEPT               0x0400  /* accepting threads are on so_accept */
#define SP_DISABLE              0x0800  /* use disable_lock for serialization */
#define SP_GROUP		0x1000	/* part of a socket group */
#define SP_INPROGRESS           0x2000  /* serialized operation is in progress */
#define	SP_ONFREELIST			0x4000	/* the socket is already in freelist */
#define	SP_QCONN_RESET			0x8000	/* completed connection in listener's queue got reset */
#define SP_INHERIT              (SP_NOUAREA|SP_LOCKABLE|SP_DISABLE|SP_XPG1170)
/* so_special2 bits
 */
#define SP2_PROC		0x0001  /* socket created by a process */
#define SP2_INHERIT		(SP2_PROC)
#define	SP2_MSGWAITALL		0x0002	/* TCP checks this flag to know if
					 * the recv() used MSG_WAITALL flag
					*/
#define SP2_LOCAL		0x0004  /* The socket is a local connection */
#define	SP2_FRCA_BACKDOOR_BUSY	0x1000	/*   */
#define	SP2_FRCA_BACKDOOR	0x2000	/*   */
#define	SP2_FRCA_BUCKET		0x4000	/*   */
#define	SP2_FRCA_BACKDOOR_DONE	0x8000	/*   */

#ifdef  _KERNEL

/*
 * Hash table of sockets waiting to be freed.
 */

extern struct free_sock_hash_bucket free_sock_hash_table[];

#define FREE_SOCK_HASH_SZ 103
struct free_sock_hash_bucket {
        int                     fsh_freecnt;
        simple_lock_data_t      fsh_lock;
        int                     fsh_intrlvl;
        struct socket           *fsh_freelist;
};

#define FREE_SOCK_HASH(so)      (((ulong)(so)) % FREE_SOCK_HASH_SZ)
#define FREE_SOCK_LOCK_INIT() {                                                                 \
        int _free_sock_index;                                                                   \
                                                                                                \
        for (_free_sock_index = 0; _free_sock_index < FREE_SOCK_HASH_SZ; _free_sock_index++) {  \
                lock_alloc(&free_sock_hash_table[_free_sock_index].fsh_lock, LOCK_ALLOC_PIN,    \
                        UNPMISC_LOCK_FAMILY, (uint)_free_sock_index);                           \
                simple_lock_init(&free_sock_hash_table[_free_sock_index].fsh_lock);             \
        }                                                                                       \
}

#define FREE_SOCK_LOCK(index)   free_sock_hash_table[(index)].fsh_intrlvl =             \
        disable_lock(PL_IMP, &free_sock_hash_table[(index)].fsh_lock);
#define FREE_SOCK_UNLOCK(index) unlock_enable(free_sock_hash_table[(index)].fsh_intrlvl,        \
        &free_sock_hash_table[(index)].fsh_lock);

#if DEBUG && POWER_MP
#define FREE_SOCK_ISLOCKED(lp)  lock_mine(lp)
#else
#define FREE_SOCK_ISLOCKED(lp)  1
#endif

/*
 * Macros for sockets, socket locking and socket buffering.
 */

struct  socklocks {
        simple_lock_data_t      sock_lock;
        simple_lock_data_t      snd_lock;	/* not used */
        simple_lock_data_t      rcv_lock;	/* not used */
        int                     refcnt;
        struct socket           *sp_wake;
        struct socket           *so;            /* back pointer */
        int                     spl;
        struct socklocks        *freelist;
};

/* socket send buffer pool */

struct sndbufpool {
	struct mclust_pool *sb_pool;
	int sb_freecnt;			/* Timer free count */
};

#if DEBUG && POWER_MP
#define SOCKET_ISLOCKED(so)     lock_mine(&((so)->so_lock->sock_lock))
#else
#define SOCKET_ISLOCKED(so)     1
#endif

#define SOCKET_LOCKINIT(so, lp)  { \
        (so)->so_lock = (lp); \
        (lp)->refcnt = 0; \
        (lp)->sp_wake = 0; \
        (lp)->so = so; \
        (lp)->freelist = 0; \
        lock_alloc(&((lp)->sock_lock), LOCK_ALLOC_PIN, SOCKET_LOCK_FAMILY, \
		(uint)so);\
        simple_lock_init(&((lp)->sock_lock));  \
}

/* Lock order of unpaired sockets is critical to avoid deadlock. */
#define SOCKET_LOCK2(so1, so2) { \
        if ((so1) < (so2)) { \
                SOCKET_LOCK(so1); \
                if ((so1)->so_lock != (so2)->so_lock) \
                        SOCKET_LOCK(so2); \
        } else { \
                SOCKET_LOCK(so2); \
                if ((so1)->so_lock != (so2)->so_lock) \
                        SOCKET_LOCK(so1); \
        } \
}
#define SOCKET_UNLOCK2(so1, so2) { \
        if ((so1) < (so2)) { \
                if ((so1)->so_lock != (so2)->so_lock) \
                        SOCKET_UNLOCK(so2); \
                SOCKET_UNLOCK(so1); \
        } else { \
                if ((so1)->so_lock != (so2)->so_lock) \
                        SOCKET_UNLOCK(so1); \
                SOCKET_UNLOCK(so2); \
        } \
}

#ifdef __64BIT__
#define SOCKET_LOCK(so)         {       \
if ((so)->so_special & SP_DISABLE)      \
        (so)->so_lock->spl = disable_lock(PL_IMP,&((so)->so_lock->sock_lock)); \
else {  \
        simple_lock_data_t *lw = &((so)->so_lock->sock_lock); \
\
        simple_lock(lw); \
        while (lw != &((so)->so_lock->sock_lock)) { \
                simple_unlock(lw); \
                lw = &((so)->so_lock->sock_lock); \
                simple_lock(lw); \
        }  \
} \
}
#else
#define SOCKET_LOCK(so)         {       \
if ((so)->so_special & SP_DISABLE)      \
        so_pin_more_stack(so); \
else {  \
        simple_lock_data_t *lw = &((so)->so_lock->sock_lock); \
\
        simple_lock(lw); \
        while (lw != &((so)->so_lock->sock_lock)) { \
                simple_unlock(lw); \
                lw = &((so)->so_lock->sock_lock); \
                simple_lock(lw); \
        }  \
} \
}
#endif

#define SOCKET_UNLOCK(so)	sounlock(so);

#define SOCKET_REF(so)          fetch_and_addlp(&(so->so_refcnt), 1);
#define SOCKET_UNREF(so)        fetch_and_addlp(&(so->so_refcnt), -1);

#define sosetfield SOSETFIELD
#define SOSETFIELD(so, field, value) \
        { \
                so->field## = value; \
                if (so->so_special & SP_GROUP && so->so_q0) { \
                        int z2; \
                        struct socket *sg2; \
                        for (z2 = 1; z2 < so->so_q0len; z2++) { \
                                sg2 = ((struct socket **)so->so_q0)[z2]; \
                                SOCKET_LOCK(sg2);\
                                sg2->field## = value; \
                                SOCKET_UNLOCK(sg2);\
                        } \
                } \
        }

#define SOCKBUF_LOCK(sb)        /* unused, symbol kept for compat */
#define SOCKBUF_UNLOCK(sb)      /* unused, symbol kept for compat */

/* Bits for network events to sb_wakeup */
#define SE_ERROR        0x0001  /* so_error non-0 */
#define SE_HAVEDATA     0x0002  /* data in send or recv q */
#define SE_HAVEOOB      0x0004  /* oob data in recv q */
#define SE_DATAFULL     0x0008  /* send or recv q is full */
#define SE_CONNOUT      0x0010  /* outgoing connect complete (connect) */
#define SE_CONNIN       0x0020  /* incoming connect complete (listen)  */
#define SE_SENDCONN     0x0040  /* connected for send */
#define SE_RECVCONN     0x0080  /* connected for recv */
#define SE_POLL         0x4000  /* wakeup is synchronous poll */
#define SE_STATUS       0x8000  /* above status bits valid */

/* does socket have a valid u-area associated? (for stats, security, etc) */
#define SOHASUAREA(so)  (!((so)->so_special & SP_NOUAREA))

/* what is the domain associated with this socket? */
#define sodomain(so)    ((so)->so_proto->pr_domain)

/*
 * How much space is there in a socket buffer (so->so_snd or so->so_rcv)?
 * This is problematical if the fields are unsigned, as the space might
 * still be negative (cc > hiwat or mbcnt > mbmax).  Should detect
 * overflow and return 0.  Should use "lmin" but it doesn't exist now.
 */
#define sbspace(sb) \
    (MIN((int)((sb)->sb_hiwat - (sb)->sb_cc), \
         (int)((sb)->sb_mbmax - (sb)->sb_mbcnt)))

/* do we have to send all at once on a socket? */
#define sosendallatonce(so) \
    ((so)->so_proto->pr_flags & PR_ATOMIC)

/* can we read something from so? */
#define soreadable(so) \
    ((so)->so_rcv.sb_cc >= (so)->so_rcv.sb_lowat || \
        ((so)->so_state & SS_CANTRCVMORE) || \
        (so)->so_qlen || (so)->so_error)

/* can we write something to so? */
#define sowriteable(so) \
    (sbspace(&(so)->so_snd) >= (so)->so_snd.sb_lowat && \
        (((so)->so_state&SS_ISCONNECTED) || \
          ((so)->so_proto->pr_flags&PR_CONNREQUIRED)==0) || \
     ((so)->so_state & SS_CANTSENDMORE) || \
     (so)->so_error)

/* adjust counters in sb reflecting allocation of m */
#define sballoc(sb, m) { \
        (sb)->sb_cc += (m)->m_len; \
        (sb)->sb_mbcnt += MSIZE; \
        if ((m)->m_flags & M_EXT) \
                (sb)->sb_mbcnt += (m)->m_ext.ext_size; \
}

/* adjust counters in sb reflecting freeing of m */
#define sbfree(sb, m) { \
        (sb)->sb_cc -= (m)->m_len; \
        (sb)->sb_mbcnt -= MSIZE; \
        if ((m)->m_flags & M_EXT) \
                (sb)->sb_mbcnt -= (m)->m_ext.ext_size; \
}

#define sorwakeup(so)   sowakeup((so), &(so)->so_rcv)
#define sowwakeup(so)   sowakeup((so), &(so)->so_snd)

/* to catch callers missing new second argument to sonewconn: */
#define sonewconn(head, connstatus)     sonewsock((head), (connstatus))
extern u_long   sb_max;

/*
 *    QOS extensions register these functions with the socket layer.
 */
struct  qos_socket_funcs {
    int  (*qos_alloc)();        /* QOS buffer allocation, policing, shaping */
    int  (*qos_buf_alloc)();    /* QOS buffer allocation */
    int  (*qos_ctrl_flow)();    /* QOS tcp policing, shaping by tcp_timer */
    void (*qos_isconnected)();          /* QOS connect notification */
    void (*qos_isdisconnected)();       /* QOS disconnect notification */
    int  (*qos_input)(struct mbuf *, int);
    int  (*qos_usrreq)(struct socket *, int, struct mbuf *, 
                       struct mbuf *, struct mbuf *);
    void (*qos_ctlinput)(int, struct ifnet *, caddr_t);
    void (*qos_classify)(struct socket *);
    int (*qos_applied)(struct socket *, ushort, uchar, struct mbuf **);
};
extern struct qos_socket_funcs qos_fns;
#define QOS_IS_LOADED (qos_fns.qos_alloc != NULL)

#define so2gidstruct(so) (struct gidstruct *) ((struct socket *)(so) + 1)

#endif  /* _KERNEL */

#ifdef __cplusplus
}
#endif

#endif
