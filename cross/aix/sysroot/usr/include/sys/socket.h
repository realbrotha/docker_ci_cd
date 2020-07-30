/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53L src/bos/kernel/sys/socket.h 1.10.2.67                           */
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
/* @(#)63	1.10.2.67  src/bos/kernel/sys/socket.h, sockinc, bos53L, l2006_41A1 10/2/06 17:04:28 */

/*
 *   COMPONENT_NAME: SOCKINC
 *
 *   FUNCTIONS: CMSG_DATA
 *              CMSG_FIRSTHDR
 *              CMSG_NXTHDR
 *   		CMSG_ALIGN
 *		CMSG_SPACE
 *		CMSG_LEN
 *
 *
 *   ORIGINS: 26,27,85,127
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
 * Copyright (c) 1982,1985,1986,1988 Regents of the University of California.
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
 *      Base:   socket.h        7.6 (Berkeley) 9/4/89
 *      Merged: socket.h        7.10 (Berkeley) 6/28/90
 */

#ifndef _SYS_SOCKET_H_
#define _SYS_SOCKET_H_

#include <standards.h>          /* define standards macros */
#include <sys/types.h>          /* for uchar_t, ushort_t, etc. */
#include <sys/uio.h>            /* for iovec */

/*
 * Definitions related to sockets: types, address families, options.
 */

/* 
 * socklen_t also has a similar definition in netinet/in.h 
 * If we need to change this typedef, it must be changed
 * in netinet/in.h also
 */
#ifndef __SOCKLEN_T
#define __SOCKLEN_T
typedef __ulong32_t socklen_t;
#endif

#ifdef _ALL_SOURCE
/*
 * In a non-SPEC 1170 environment, we'd rather just call the "n" versions of
 * these routines, because they're a little bit quicker.
 */
#ifndef _KERNEL
#ifdef __cplusplus
extern "C" int naccept(int, struct sockaddr *, socklen_t *);
extern "C" int ngetpeername(int, struct sockaddr *, socklen_t *);
extern "C" int ngetsockname(int, struct sockaddr *, socklen_t *);
extern "C" ssize_t nrecvfrom(int, void *, size_t, int, struct sockaddr *,
	                     socklen_t *);
inline int accept(int socketfd, struct sockaddr *address, socklen_t *address_len)
{
	return naccept(socketfd, address, address_len);
}
inline int getpeername(int socketfd, struct sockaddr *address,
	               socklen_t *address_len)
{
	return ngetpeername(socketfd, address, address_len);
}
inline int getsockname(int socketfd, struct sockaddr *address,
	               socklen_t *address_len)
{
	return ngetsockname(socketfd, address, address_len);
}
inline ssize_t recvfrom(int socketfd, void *buffer, size_t length, int flags,
	                struct sockaddr *address, socklen_t *address_len)
{
	return nrecvfrom(socketfd, buffer, length, flags, address,
	                 address_len);
}
int     getpeereid(int, uid_t *__restrict__, gid_t *__restrict__);
#ifndef COMPAT_43
extern "C" ssize_t nrecvmsg(int, struct msghdr *, int);
extern "C" ssize_t nsendmsg(int, const struct msghdr *, int);
inline ssize_t recvmsg(int socketfd, struct msghdr *message, int flags)
{
	return nrecvmsg(socketfd, message, flags);
}
inline ssize_t sendmsg(int socketfd, const struct msghdr *message, int flags)
{
	return nsendmsg(socketfd, message, flags);
}
#else /* COMPAT_43 */
extern "C" ssize_t recvmsg(int, struct msghdr *, int);
extern "C" ssize_t sendmsg(int, const struct msghdr *, int);
#endif /* COMPAT_43 */
#else  /* __cplusplus */
#define recvfrom        nrecvfrom
#define accept          naccept
#define getpeername     ngetpeername
#define getsockname     ngetsockname

#ifndef COMPAT_43
#define recvmsg         nrecvmsg
#define sendmsg         nsendmsg
#endif /* COMPAT_43 */
#endif /* __cplusplus */

#endif /* _KERNEL */

/*
 * Structure to get peer socket's process id, effective uid
 * and effective gid. euid and egid are applicable only for
 * unix domain sockets.
 */
struct peercred_struct {
	pid_t pid;                      /* peer's process id */
	tid_t tid;			/* peer's thread id */
	uid_t euid;                     /* peer's effective uid */
	gid_t egid;                     /* peer's effective gid */
};

/* peercred_struct structure for 32-bit and 64-bit */
struct peercred_struct_32_64 {
	pid32_t pid;
	tid_t tid;
	uid_t euid;
	gid_t egid;
};

/* peercred_struct structure for 32-bit */
struct peercred_struct32 {
	pid32_t pid;
	tid32_t tid;
	uid_t euid;
	gid_t egid;
};

/* peercred_struct structure for 64-bit */
struct peercred_struct64 {
	pid32_t pid;
	tid64_t tid;
	uid_t euid;
	gid_t egid;
};

#endif /* _ALL_SOURCE */


#if _XOPEN_SOURCE_EXTENDED == 1

/*
 * Types
 */
#define SOCK_STREAM     1               /* stream socket */
#define SOCK_DGRAM      2               /* datagram socket */
#define SOCK_RAW        3               /* raw-protocol interface */
#define SOCK_RDM        4               /* reliably-delivered message */
#define SOCK_SEQPACKET  5               /* sequenced packet stream */
#define SOCK_CONN_DGRAM 6               /* connection datagram */

/*
 * Option flags per-socket.
 */
#define SO_DEBUG        0x0001          /* turn on debugging info recording */
#define SO_ACCEPTCONN   0x0002          /* socket has had listen() */
#define SO_REUSEADDR    0x0004          /* allow local address reuse */
#define SO_KEEPALIVE    0x0008          /* keep connections alive */
#define SO_DONTROUTE    0x0010          /* just use interface addresses */
#define SO_BROADCAST    0x0020          /* permit sending of broadcast msgs */
#define SO_USELOOPBACK  0x0040          /* bypass hardware when possible */
#define SO_LINGER       0x0080          /* linger on close if data present */
#define SO_OOBINLINE    0x0100          /* leave received OOB data in line */
#define SO_REUSEPORT    0x0200          /* allow local address & port reuse */
#define SO_USE_IFBUFS   0x0400          /* Interface will supply buffers */
#define SO_CKSUMRECV    0x0800          /* defer checksum until receive */
#define SO_NOREUSEADDR  0x1000          /* prevent local address reuse */
#define SO_KERNACCEPT   0x2000          /* derive a in-kernel only socket */
#define SO_NOMULTIPATH	0x4000		/* always use first matching route */
#define SO_AUDIT        0x8000          /* turn on socket auditing */

/*
 * Additional options, not kept in so_options.
 */
#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */

#define SO_SNDLOWAT     0x1003          /* send low-water mark */
#define SO_RCVLOWAT     0x1004          /* receive low-water mark */

#define SO_SNDTIMEO     0x1005          /* send timeout */
#define SO_RCVTIMEO     0x1006          /* receive timeout */
#define SO_ERROR        0x1007          /* get error status and clear */
#define SO_TYPE         0x1008          /* get socket type */
#define SO_PEERID	0x1009		/* get peer socket's process id, thread id, 
							euid and egid */

/*
 * Structure used for manipulating linger option.
 */
struct  linger {
	int     l_onoff;                /* option on/off */
	int     l_linger;               /* linger time */
};

/*
 * Level number for (get/set)sockopt() to apply to socket itself.
 */
#define SOL_SOCKET      0xffff          /* options for socket level */

/*
 * Address families.
 */
#define AF_UNSPEC       0               /* unspecified */
#define AF_UNIX         1               /* local to host (pipes, portals) */
#define AF_INET         2               /* internetwork: UDP, TCP, etc. */
#define AF_IMPLINK      3               /* arpanet imp addresses */
#define AF_PUP          4               /* pup protocols: e.g. BSP */
#define AF_CHAOS        5               /* mit CHAOS protocols */
#define AF_NS           6               /* XEROX NS protocols */
#define AF_ISO          7               /* ISO protocols */
#define AF_OSI          AF_ISO
#define AF_ECMA         8               /* european computer manufacturers */
#define AF_DATAKIT      9               /* datakit protocols */
#define AF_CCITT        10              /* CCITT protocols, X.25 etc */
#define AF_SNA          11              /* IBM SNA */
#define AF_DECnet       12              /* DECnet */
#define AF_DLI          13              /* DEC Direct data link interface */
#define AF_LAT          14              /* LAT */
#define AF_HYLINK       15              /* NSC Hyperchannel */
#define AF_APPLETALK    16              /* Apple Talk */
#define AF_ROUTE        17              /* Internal Routing Protocol */
#define AF_LINK         18              /* Link layer interface */
/* Moved to _ALL_SOURCE section since it doesn't begin with AF_ */
/*efine pseudo_AF_XTP   19              / * eXpress Transfer Protocol (no AF) */
#ifdef  _AIX
#define AF_INTF         20              /* Debugging use only */
#define AF_RIF          21              /* raw interface */
#define AF_NETWARE      22
#define AF_NDD          23
#define AF_INET6        24              /* IPv6 */
#define AF_BYPASS       25              /* TCP/IP Stack Bypass Domain */
#define AF_MAX          30
#else
#define AF_MAX          20
#endif

/*
 * Family typedef
 */
#ifndef _SA_FAMILY_T
#define _SA_FAMILY_T
typedef uchar_t sa_family_t;
#endif

/*
 * Structure used by kernel to store most
 * addresses.
 */
#if defined(COMPAT_43) && !defined(_KERNEL)
struct sockaddr {
	ushort_t        sa_family;      /* address family */
	char            sa_data[14];    /* up to 14 bytes of direct address */
};


#else
struct sockaddr {
	uchar_t         sa_len;         /* total length */
	sa_family_t     sa_family;      /* address family */
	char            sa_data[14];    /* actually longer; address value */
};

#endif /* COMPAT_43 */


/*
 * Define sockaddr_storage in XOPEN namespace - UNIX03 Compliance
 */

#if !(defined(_ALL_SOURCE))
/* According to RFC3493 sockaddr_storage structure should be greater than or
equal to the largest sockaddr struct. The size of sockaddr_un structure changed to 1025 in order to support long user names. Change _SS_MAXSIZE accordingly
inorder to main compliance to the RFC */
#define _SS_MAXSIZE     1280 /* Implementation specific max size */

#if defined(__64BIT__) || (defined(_ALL_SOURCE) && defined(_LONG_LONG))
#define _SS_ALIGNSIZE   (sizeof (int64_t))      /* Desired alignment */
#else
#define _SS_ALIGNSIZE   (2 * sizeof(int))       /* Desired alignment */
#endif

#if defined(COMPAT_43) && !defined(_KERNEL)

#define _SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof(ushort_t))
#define _SS_PAD2SIZE (_SS_MAXSIZE - (sizeof(ushort_t) + \
                                        _SS_PAD1SIZE + _SS_ALIGNSIZE))

struct sockaddr_storage {
        ushort_t        __ss_family;    /* address family */
        char            __ss_pad1[_SS_PAD1SIZE]; /* pad up to alignment field */
#if defined(__64BIT__) || (defined(_ALL_SOURCE) && defined(_LONG_LONG))
        int64_t         __ss_align;     /* field to force desired structure */
                                        /* storage alignment */
#else
        int             __ss_align[2];
#endif
        char            __ss_pad2[_SS_PAD2SIZE];
                                /* pad to achieve desired size */
};
#else

#define _SS_PAD1SIZE (_SS_ALIGNSIZE - (sizeof(uchar_t) + sizeof(sa_family_t)))
#define _SS_PAD2SIZE (_SS_MAXSIZE - (sizeof(sa_family_t) + \
                                        _SS_PAD1SIZE + _SS_ALIGNSIZE))

struct sockaddr_storage {
        uchar_t         __ss_len;       /* address length */
        sa_family_t     ss_family;    /* address family */
        char            __ss_pad1[_SS_PAD1SIZE]; /* pad up to alignment field */
#if defined(__64BIT__) || (defined(_ALL_SOURCE) && defined(_LONG_LONG))
        int64_t         __ss_align;     /* field to force desired structure */
                                        /* storage alignment */
#else
        int             __ss_align[2];
#endif
        char            __ss_pad2[_SS_PAD2SIZE];
                                /* pad to achieve desired size */
};
#endif /* COMPAT_43 */
#endif /* _ALL_SOURCE */



/*
 * Protocol families, same as address families for now.
 */
#define PF_UNSPEC       AF_UNSPEC
#define PF_UNIX         AF_UNIX
#define PF_INET         AF_INET
#define PF_IMPLINK      AF_IMPLINK
#define PF_PUP          AF_PUP
#define PF_CHAOS        AF_CHAOS
#define PF_NS           AF_NS
#define PF_ISO          AF_ISO
#define PF_OSI          AF_ISO
#define PF_ECMA         AF_ECMA
#define PF_DATAKIT      AF_DATAKIT
#define PF_CCITT        AF_CCITT
#define PF_SNA          AF_SNA
#define PF_DECnet       AF_DECnet
#define PF_DLI          AF_DLI
#define PF_LAT          AF_LAT
#define PF_HYLINK       AF_HYLINK
#define PF_APPLETALK    AF_APPLETALK
#define PF_ROUTE        AF_ROUTE
#define PF_LINK         AF_LINK
#define PF_XTP          pseudo_AF_XTP   /* really just proto family, no AF */
#ifdef  _AIX
#define PF_RIF          AF_RIF
#define PF_INTF         AF_INTF         /* Used by sysx/intf */
#define PF_NDD          AF_NDD
#define PF_INET6        AF_INET6
#endif

#define PF_MAX          AF_MAX

/*
 * Maximum queue length specifiable by listen.
 */
#ifdef  _AIX
#define SOMAXCONN       1024
#else
#define SOMAXCONN       5
#endif

/*
 * Message header for recvmsg and sendmsg calls.
 * Used value-result for recvmsg, value only for sendmsg.
 */
#if defined(COMPAT_43) && !defined(_KERNEL)
struct msghdr {
	caddr_t msg_name;               /* optional address */
	int     msg_namelen;            /* size of address */
	struct  iovec *msg_iov;         /* scatter/gather array */
	int     msg_iovlen;             /* # elements in msg_iov */
	caddr_t msg_accrights;          /* access rights sent/received */
	int     msg_accrightslen;
};
#else
struct msghdr {
	void    *msg_name;              /* optional address */
	socklen_t  msg_namelen;         /* size of address */
	struct  iovec   *msg_iov;       /* scatter/gather array */
	int     msg_iovlen;             /* # elements in msg_iov */
	void    *msg_control;           /* ancillary data, see below */
	socklen_t  msg_controllen;      /* ancillary data buffer len */
	int     msg_flags;              /* flags on received message */
};

#endif

#define MSG_MAXIOVLEN   16              /* compat only, no longer enforced */
#define MSG_OOB         0x1             /* process out-of-band data */
#define MSG_PEEK        0x2             /* peek at incoming message */
#define MSG_DONTROUTE   0x4             /* send without using routing tables */
#define MSG_EOR         0x8             /* data completes record */
#define MSG_TRUNC       0x10            /* data discarded before delivery */
#define MSG_CTRUNC      0x20            /* control data lost before delivery */
#define MSG_WAITALL     0x40            /* wait for full request or error */
#define MSG_MPEG2       0x80            /* Message contain MPEG2 data */
/* Following used within kernel */
#define MSG_NONBLOCK    0x4000          /* nonblocking request */
#define MSG_COMPAT      0x8000          /* 4.3-format sockaddr */

/*
 * Header for ancillary data objects in msg_control buffer.
 * Used for additional information with/about a datagram
 * not expressible by flags.  The format is a sequence
 * of message elements headed by cmsghdr structures.
 */
struct cmsghdr {
	socklen_t  cmsg_len;
	int     cmsg_level;             /* originating protocol */
	int     cmsg_type;              /* protocol-specific type */
/* followed by  u_char  cmsg_data[]; */
};

/* given pointer to struct adatahdr, return pointer to data */
#define CMSG_DATA(cmsg)     (((uchar_t *)(cmsg)) + \
			     _CMSG_ALIGN(sizeof(struct cmsghdr)))

/* AIX does not have any alignment/padding for ancillary data */
#define _CMSG_ALIGN(p)      (p)

/* given pointer to struct adatahdr, return pointer to next adatahdr */
#define CMSG_NXTHDR(mhdr, cmsg) \
        (((cmsg) == 0) ? CMSG_FIRSTHDR(mhdr) : \
         (((caddr_t)(cmsg) + (cmsg)->cmsg_len + sizeof(struct cmsghdr) > \
          (caddr_t)((mhdr)->msg_control) + (mhdr)->msg_controllen) ? \
          (struct cmsghdr *)0 : \
          (struct cmsghdr *)((caddr_t)(cmsg) + _CMSG_ALIGN((cmsg)->cmsg_len))))

#define CMSG_FIRSTHDR(mhdr) \
           ((mhdr)->msg_controllen >= sizeof(struct cmsghdr) ? \
            (struct cmsghdr *)(mhdr)->msg_control : \
            (struct cmsghdr *)0 )

/*
 * CMSG_ALIGN, CMSG_SPACE, CMSG_LEN
 */
#define	CMSG_ALIGN _CMSG_ALIGN
#define CMSG_SPACE(len) (_CMSG_ALIGN(sizeof(struct cmsghdr)) + _CMSG_ALIGN(len))
#define CMSG_LEN(len) (_CMSG_ALIGN(sizeof(struct cmsghdr)) + (len))

/* "Socket"-level control message types: */
#define SCM_RIGHTS      0x01            /* access rights (array of int) */

/*
 * Arguments for shutdown().
 */
#define SHUT_RD         0       /* shut down for reading */
#define SHUT_WR         1       /* shut down for writing */
#define SHUT_RDWR       2       /* shut down for read & write */

/*
 * Function declarations and prototypes.
 */
#ifndef _KERNEL

#ifdef  _NO_PROTO

int     accept();
int     bind();
int     connect();
int     getpeername();
int     getsockname();
int     getsockopt();
int     listen();
ssize_t recv();
ssize_t recvfrom();
ssize_t recvmsg();
ssize_t send();
ssize_t sendto();
ssize_t sendmsg();
int     setsockopt();
int     shutdown();
int     socket();
int     socketpair();

#else

#if !defined(_ALL_SOURCE) || defined(_KERNEL) || !defined(__cplusplus)
int     accept(int, struct sockaddr *__restrict__, socklen_t *__restrict__);
int     getpeername(int, struct sockaddr *__restrict__, socklen_t *__restrict__);
int     getsockname(int, struct sockaddr *__restrict__, socklen_t *__restrict__);
ssize_t recvfrom(int, void *__restrict__, size_t, int, struct sockaddr *__restrict__, socklen_t *__restrict__);
#ifndef COMPAT_43
ssize_t recvmsg(int, struct msghdr *, int);
ssize_t sendmsg(int, const struct msghdr *, int);
#endif
#endif
int     bind(int, const struct sockaddr *, socklen_t);
int     connect(int, const struct sockaddr *, socklen_t);
int     getsockopt(int, int, int, void *__restrict__, socklen_t *__restrict__);
int     listen(int, int);
ssize_t recv(int, void *, size_t, int);
ssize_t send(int, const void *, size_t, int);
ssize_t sendto(int, const void *, size_t, int, const struct sockaddr *, socklen_t);
int     setsockopt(int, int, int, const void *, socklen_t);
int     shutdown(int, int);
int     socket(int, int, int);
int     socketpair(int, int, int, int[2]);
#if _POSIX_C_SOURCE >= 200112L
int sockatmark(int);
#endif /* _POSIX_C_SOURCE */
#endif /* _NO_PROTO */

#endif /* _KERNEL */

#endif /* _XOPEN_SOURCE_EXTENDED == 1 */


#ifdef _ALL_SOURCE
/*
 * Address families.
 */
#define pseudo_AF_XTP   19              /* eXpress Transfer Protocol (no AF) */

/*
 * Family typedef
 */
#ifndef _SA_FAMILY_T
#define _SA_FAMILY_T
typedef uchar_t sa_family_t;
#endif

/* According to RFC3493 sockaddr_storage structure should be greater than or 
equal to the largest sockaddr struct. The size of sockaddr_un structure changed to 1025 in order to support long user names. Change _SS_MAXSIZE accordingly 
inorder to main compliance to the RFC */
#define	_SS_MAXSIZE	1280 /* Implementation specific max size */

#if defined(__64BIT__) || (defined(_ALL_SOURCE) && defined(_LONG_LONG))
#define	_SS_ALIGNSIZE	(sizeof (int64_t))	/* Desired alignment */
#else
#define	_SS_ALIGNSIZE	(2 * sizeof(int))	/* Desired alignment */
#endif

#if defined(COMPAT_43) && !defined(_KERNEL)

#define	_SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof(ushort_t))
#define	_SS_PAD2SIZE (_SS_MAXSIZE - (sizeof(ushort_t) + \
					_SS_PAD1SIZE + _SS_ALIGNSIZE))

struct sockaddr_storage {
	ushort_t	__ss_family;	/* address family */
	char		__ss_pad1[_SS_PAD1SIZE]; /* pad up to alignment field */
#if defined(__64BIT__) || (defined(_ALL_SOURCE) && defined(_LONG_LONG))
	int64_t		__ss_align;	/* field to force desired structure */
					/* storage alignment */
#else
	int		__ss_align[2];
#endif
	char		__ss_pad2[_SS_PAD2SIZE];
				/* pad to achieve desired size */
};
#else

#define	_SS_PAD1SIZE (_SS_ALIGNSIZE - (sizeof(uchar_t) + sizeof(sa_family_t)))
#define	_SS_PAD2SIZE (_SS_MAXSIZE - (sizeof(sa_family_t) + \
					_SS_PAD1SIZE + _SS_ALIGNSIZE))

struct sockaddr_storage {
	uchar_t		__ss_len;	/* address length */
	sa_family_t	ss_family;	/* address family */
	char		__ss_pad1[_SS_PAD1SIZE]; /* pad up to alignment field */
#if defined(__64BIT__) || (defined(_ALL_SOURCE) && defined(_LONG_LONG))
	int64_t		__ss_align;	/* field to force desired structure */
					/* storage alignment */
#else
	int		__ss_align[2];
#endif
	char		__ss_pad2[_SS_PAD2SIZE];
				/* pad to achieve desired size */
};
#endif /* COMPAT_43 */

/*
 * 4.3 compat sockaddr, move to compat file later
 */
struct osockaddr {
	u_short sa_family;              /* address family */
	char    sa_data[14];            /* up to 14 bytes of direct address */
};

/*
 * Structure used by kernel to pass protocol
 * information in raw sockets.
 */
struct sockproto {
	u_short sp_family;              /* address family */
	u_short sp_protocol;            /* protocol */
};

/*
 * 4.3-compat message header (move to compat file later).
 */
struct omsghdr {
	caddr_t msg_name;               /* optional address */
	int     msg_namelen;            /* size of address */
	struct  iovec *msg_iov;         /* scatter/gather array */
	int     msg_iovlen;             /* # elements in msg_iov */
	caddr_t msg_accrights;          /* access rights sent/received */
	int     msg_accrightslen;
};

#ifndef UIO_MAXIOV
#define UIO_MAXIOV      1024            /* max 1K of iov's */
#endif

#ifndef UIO_SMALLIOV
#define UIO_SMALLIOV    8               /* 8 on stack, else malloc */
#endif

/*
 * param.h
 */
#ifndef MACHINE_ALIGNMENT               /* optional machine/machparam.h */
#define MACHINE_ALIGNMENT       sizeof (void *)
#endif

#ifndef ALIGN
#define ALIGNMENT(p)    ((ulong)(p) % MACHINE_ALIGNMENT)
#define ALIGN(p)        (ulong)((caddr_t)(p) + MACHINE_ALIGNMENT - 1 - \
	                 ALIGNMENT((caddr_t)(p) + MACHINE_ALIGNMENT - 1))
#endif

/*
 * Structure for the send_file() system call
 */
#ifdef __64BIT__
#define SF_INT64(x)     int64_t x;
#define SF_UINT64(x)    uint64_t x;
#else
#ifdef _LONG_LONG
#define SF_INT64(x)     int64_t x;
#define SF_UINT64(x)    uint64_t x;
#else
#define SF_INT64(x)     int filler_##x; int x;
#define SF_UINT64(x)    int filler_##x; uint_t x;
#endif
#endif

struct sf_parms {
    /* --------- header parms ---------- */
    void      *header_data;         /* Input/Output. Points to header buf */
    uint_t    header_length;        /* Input/Output. Length of the header */
    /* --------- file parms ------------ */
    int       file_descriptor;      /* Input. File descriptor of the file */
#if !defined(__64BIT__) && defined(__ia64)
    /*
     * In IA64, the 32bit application aligns 64 bit items on 32 bit 
     * boundaries.  This is different than POWER.  So, we pad.  This allows
     * for the 64 bit items to map into 64 bit aligned units in the kernel
     */
    int       padto64bit;           /* See explaination above */
#endif
    SF_UINT64(file_size)            /* Output. Size of the file */
    SF_UINT64(file_offset)          /* Input/Output. Starting offset */
    SF_INT64(file_bytes)            /* Input/Output. no. of bytes to send */
    /* --------- trailer parms --------- */
    void      *trailer_data;        /* Input/Output. Points to trailer buf */
    uint_t    trailer_length;       /* Input/Output. Length of the trailer */
    /* --------- return info ----------- */
    SF_UINT64(bytes_sent)           /* Output. no. of bytes sent */
};


/*
 * Flags for the send_file() system call
 */
#define SF_CLOSE        0x00000001      /* close the socket after completion */
#define SF_REUSE        0x00000002      /* reuse socket. not supported */
#define SF_DONT_CACHE   0x00000004      /* don't apply network buffer cache */
#define SF_SYNC_CACHE   0x00000008      /* sync/update network buffer cache */

/*
 * send_file prototypes.
 */
#ifndef _KERNEL

#ifdef  _NO_PROTO
ssize_t send_file();
#else
ssize_t send_file(int *, struct sf_parms *, uint_t);
#endif  /* _NO_PROTO */

#else

ssize_t send_file(int *, struct sf_parms *, uint_t);

#endif  /* _KERNEL */


#endif /* _ALL_SOURCE */

#endif /* _SYS_SOCKET_H */
