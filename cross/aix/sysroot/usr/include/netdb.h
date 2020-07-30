/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/netdb.h 1.41                                */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1995          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)43       1.41  src/bos/usr/include/netdb.h, sockinc, bos530 7/25/02 19:25:00 */

#ifndef _H_NETDB
#define _H_NETDB
#ifdef _POWER_PROLOG_
/*
 *   COMPONENT_NAME: SOCKINC
 *
 *   FUNCTIONS:
 *
 *   ORIGINS: 26,27,71
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1988,1995
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 */
#endif /* _POWER_PROLOG_ */

/*
 * (c) Copyright 1990, 1991, 1992 OPEN SOFTWARE FOUNDATION, INC.
 * ALL RIGHTS RESERVED
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 */

#include <standards.h>                  /* define standards macros */
#include <netinet/in.h>

#if _XOPEN_SOURCE_EXTENDED == 1

/*
 * h_errno is provided by h_errno_which() routine.
 * For non multi-threaded applications, it'll return the static h_errno
 * for the multi-threaded ones, it'll return the per-thread value.
 */
extern void *h_errno_which(void);
#define h_errno   (*(int *)h_errno_which())

/*
 * Structures returned by network
 * data base library.  All addresses
 * are supplied in host order, and
 * returned in network order (suitable
 * for use in system calls).
 */
struct  hostent {
        char    *h_name;                        /* official name of host */
        char    **h_aliases;                     /* alias list */
        int     h_addrtype;                     /* host address type */
        int     h_length;                       /* length of address */
        char    **h_addr_list;                  /* list of addresses from */
                                                /* name server */
#define h_addr  h_addr_list[0]  /* address, for backward compatiblity */
};

/*
 * IPv6 address entry
 */
#ifdef IPV6ADDR_ANY_INIT
struct  ipv6_hostent_addr {
        struct in6_addr iha_addr;
        u_int32_t       iha_lifetime;
};
#endif

/*
 * Trouble here... nlist.h and syms.h #define n_name.
 */
#ifdef n_name
#undef n_name
#endif

/*
 * Assumption here is that a network number
 * fits in 32 bits -- probably a poor one.
 */
struct  netent {
        char            *n_name;        /* official name of net */
        char            **n_aliases;    /* alias list */
        int             n_addrtype;     /* net address type */
        in_addr_t       n_net;          /* network # */
};

struct  servent {
        char    *s_name;        /* official service name */
        char    **s_aliases;    /* alias list */
        int     s_port;         /* port # */
        char    *s_proto;       /* protocol to use */
};


struct  protoent {
        char    *p_name;        /* official protocol name */
        char    **p_aliases;    /* alias list */
        int     p_proto;        /* protocol # */
};


#ifdef _NO_PROTO

void            endhostent();
void            endnetent();
void            endprotoent();
void            endservent();
struct hostent  *gethostbyaddr();
struct hostent  *gethostbyname();
struct hostent  *gethostent();
struct netent   *getnetbyaddr();
struct netent   *getnetbyname();
struct netent   *getnetent();
struct protoent *getprotobyname();
struct protoent *getprotobynumber();
struct protoent *getprotoent();
struct servent  *getservbyname();
struct servent  *getservbyport();
struct servent  *getservent();
void            sethostent();
void            setnetent();
void            setprotoent();
void            setservent();

#else   /* _NO_PROTO */

void            endhostent(void);
void            endnetent(void);
void            endprotoent(void);
void            endservent(void);
struct hostent  *gethostbyaddr(const void *, size_t, int);
struct hostent  *gethostbyname(const char *);
struct hostent  *gethostent(void);
struct netent   *getnetbyaddr(in_addr_t, int);
struct netent   *getnetbyname(const char *);
struct netent   *getnetent(void);
struct protoent *getprotobyname(const char *);
struct protoent *getprotobynumber(int);
struct protoent *getprotoent(void);
struct servent  *getservbyname(const char *, const char *);
struct servent  *getservbyport(int, const char *);
struct servent  *getservent(void);
void            sethostent(int);
void            setnetent(int);
void            setprotoent(int);
void            setservent(int);

#endif /* _NO_PROTO */

/*
 * Error return codes from gethostbyname() and gethostbyaddr()
 * (left in extern int h_errno).
 */

#define HOST_NOT_FOUND  1 /* Authoritative Answer Host not found */
#define TRY_AGAIN       2 /* Non-Authoritive Host not found, or SERVERFAIL */
#define NO_RECOVERY     3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */
#define NO_DATA         4 /* Valid name, no data record of requested type */

#ifndef IPPORT_RESERVED
#define IPPORT_RESERVED 1024
#endif /* IPPORT_RESERVED */

#endif /* _XOPEN_SOURCE_EXTENDED == 1 */


#ifdef _ALL_SOURCE

#include <stdio.h>                      /* BUFSIZ */

#define _PATH_HEQUIV    "/etc/hosts.equiv"
#define _PATH_HOSTS     "/etc/hosts"
#define _PATH_NETWORKS  "/etc/networks"
#define _PATH_PROTOCOLS "/etc/protocols"
#define _PATH_SERVICES  "/etc/services"
#define _PATH_SERVCONF  "/etc/netsvc.conf"
#define _PATH_RPCDB     "/etc/rpc"
#define _PATH_IRS_CONF  "/etc/irs.conf"


#define _MAXSERVICES    255
#define _MAXALIASES     35
#define _MAXADDRS       35
#define _MAXLINELEN     1024
#define _HOSTBUFSIZE    (BUFSIZ + 1)

struct  netent_data {           /* should be considered opaque */
        FILE    *net_fp;
        char    line[_MAXLINELEN];
        char    *net_aliases[_MAXALIASES];
        int     _net_stayopen;
        char    *current;
        int     currentlen;
        void    *_net_reserv1;          /* reserved for future use */
        void    *_net_reserv2;          /* reserved for future use */
};

/*
 * After a successful call to gethostbyname_r()/gethostbyaddr_r(), the
 * structure hostent_data will contain the data to which pointers in
 * the hostent structure will point to.
 */
struct  hostent_data {
        struct  in_addr host_addr;       /* host address pointer */
        char    *h_addr_ptrs[_MAXADDRS + 1];    /* host address */
        char    hostaddr[_MAXADDRS];
        char    hostbuf[_HOSTBUFSIZE + 1];      /* host data */
        char    *host_aliases[_MAXALIASES];
        char    *host_addrs[2];
        FILE    *hostf;
        int     stayopen;               /* AIX addon */
        ulong   host_addresses[_MAXADDRS];      /* As per defect 48367. */
        int     this_service;
        char    domain[256];
        char    *current;
        int     currentlen;
        void    *_host_reserv1;         /* reserved for future use */
        void    *_host_reserv2;         /* reserved for future use */
};                                              /*    Actual Addresses. */

struct  servent_data {          /* should be considered opaque */
        FILE    *serv_fp;
        char    line[_MAXLINELEN];
        char    *serv_aliases[_MAXALIASES];
        int     _serv_stayopen;
        char     *current;
        int     currentlen;
        void    *_serv_reserv1;         /* reserved for future use */
        void    *_serv_reserv2;         /* reserved for future use */
};

struct  protoent_data {         /* should be considered opaque */
        FILE    *proto_fp;
        int     _proto_stayopen;
        char    line[_MAXLINELEN];
        char    *proto_aliases[_MAXALIASES];
        int     currentlen;
        char    *current;
        void    *_proto_reserv1;        /* reserved for future use */
        void    *_proto_reserv2;        /* reserved for future use */
};

struct rpcent {
        char    *r_name;        /* name of server for this rpc program */
        char    **r_aliases;    /* alias list */
        int     r_number;       /* rpc program number */
};

struct  rpcent_data {           /* should be considered opaque */
        FILE    *rpc_fp;
        int     _rpc_stayopen;
        char    line[_MAXLINELEN];
        char    *rpc_aliases[_MAXALIASES];
        int     currentlen;
        char    *current;
        void    *_rpc_reserv1;  /* reserved for future use */
        void    *_rpc_reserv2;  /* reserved for future use */
};

struct innetgr_data {           /* should be considered opaque */
        char *name;
        char *machine;
        char *domain;
        char *list[200];
        char **listp;
};

/* Structure for protocol-independent name/addr/service service.  RFC2133 */
struct addrinfo {
        int              ai_flags;      /* AI_PASSIVE, AI_CANONNAME, AI_NUMERICHOST */
        int              ai_family;     /* PF_xxx */
        int              ai_socktype;   /* SOCK_xxx */
        int              ai_protocol;   /* 0 or IPPROTO_xxx */
        size_t           ai_addrlen;    /* length of ai_addr */
        char            *ai_canonname;  /* canonical name for hostname */
        struct sockaddr *ai_addr;       /* binary address */
        struct addrinfo *ai_next;       /* next structure in list */
};

/* Error codes for protocol-independent name/addr/service service. RFC2133 */
#define EAI_ADDRFAMILY  1       /* addr family not supported for hostname */
#define EAI_AGAIN       2       /* temp failure in resolution */
#define EAI_BADFLAGS    3       /* invalid value for ai_flags */
#define EAI_FAIL        4       /* non-recoverable failure in resolution */
#define EAI_FAMILY      5       /* addr family not supported */
#define EAI_MEMORY      6       /* memory allocation failure */
#define EAI_NODATA      7       /* no address associated with hostname */
#define EAI_NONAME      8       /* hostname nor servname not provided, or not known */
#define EAI_SERVICE     9       /* servname not supported for ai_socktype */
#define EAI_SOCKTYPE    10      /* ai_socktype not supported */
#define EAI_SYSTEM      11      /* system error returned in errno */
#define EAI_MAX         11      /* maximum defined addrinfo error code */

/* Flag definitions for addrinfo hints in protocol-independent name/addr/service service. RFC2133 */
/* Also flag definitions for getipnodebyname  RFC 2553  */
#define AI_CANONNAME    0x01    /* canonical name to be included in return */
#define AI_PASSIVE      0x02    /* prepare return for call to bind() */
#define AI_NUMERICHOST  0x04    /* RFC 2553, nodename is a numeric host address string */
#define AI_ADDRCONFIG   0x08    /* RFC 2553, source address family configured */
#define AI_V4MAPPED     0x10    /* RFC 2553, accept v4 mapped addresses */
#define AI_ALL          0x20    /* RFC 2553, accept all addresses */
#define AI_NUMERICSERV  0x40	/* RFC 2553, service name is a numeric string */
#define AI_DEFAULT      (AI_V4MAPPED | AI_ADDRCONFIG)     /* RFC 2553 */

/* Flag definitions for nameinfo hints in protocol-independent name/addr/service service. RFC2133 */
#define NI_NOFQDN       0x1     /* only return hostname (no domain) for local hosts */
#define NI_NUMERICHOST  0x2     /* return only address string for name (i.e. suppress gethostbyaddr) */
#define NI_NAMEREQD     0x4     /* error on lookup failure, instead of generating a numeric entry */
#define NI_NUMERICSERV  0x8     /* return only service port number string (i.e. suppress getservbyport) */
#define NI_DGRAM        0x10    /* use "udp" for lookup instead of "tcp" */

/* Size definitions for nameinfo hints in protocol-independent name/addr/service service. RFC2133 */
#define NI_MAXHOST      1025    /* XXX: This is intended to be the same value as MAXDNAME...maximum length (in chars) of fully qualified name */
#define NI_MAXSERV      32      /* maximum length (in chars) of service name */

#ifdef _NO_PROTO

void            endrpcent();
void            freeaddrinfo();   /* RFC2133 */
char            *gai_strerror();  /* RFC2133 */
int             getaddrinfo();    /* RFC2133 */
int             getnameinfo();    /* RFC2133 */
struct rpcent   *getrpcbyname();
struct rpcent   *getrpcbynumber();
struct rpcent   *getrpcent();
struct hostent  *getipnodebyname();  /* RFC 2553 */
struct hostent  *getipnodebyaddr();  /* RFC 2553 */
void            freehostent();       /* RFC 2553 */
#ifdef _USE_IRS
void            herror();
const char      *hstrerror();
#endif /* _USE_IRS */
struct hostent  *gethostbyname2();
extern void     setnetgrent();
extern void     endnetgrent();
extern int      innetgr();
extern int      getnetgrent();

extern void endhostent_r();
extern void sethostent_r();
extern int gethostbyname_r();
extern int gethostbyaddr_r();
extern int gethostent_r();
extern int setservent_r();
extern void endservent_r();
extern int getservent_r();
extern int getservbyname_r();
extern int getservbyport_r();
extern int setnetent_r();
extern void endnetent_r();
extern int getnetbyaddr_r();
extern int getnetbyname_r();
extern int getnetent_r();
extern int setprotoent_r();
extern void endprotoent_r();
extern int getprotoent_r();
extern int getprotobyname_r();
extern int getprotobynumber_r();
extern int setrpcent_r();
extern void endrpcent_r();
extern int getrpcbyname_r();
extern int getrpcbynumber_r();
extern int getrpcent_r();
extern int setnetgrent_r();
extern int getnetgrent_r();
extern void endnetgrent_r();
extern int innetgr_r();

extern int getdomainname();
extern int setdomainname();

#else
void            endrpcent(void);
void            freeaddrinfo(struct addrinfo *);    /* RFC2133 */
char            *gai_strerror(int);    /* RFC2133 */
int             getaddrinfo(const char *__restrict__, const char *__restrict__, const struct addrinfo *__restrict__, struct addrinfo **__restrict__);    /* RFC2133 */
int             getnameinfo(const struct sockaddr *__restrict__, size_t, char *__restrict__, size_t, char *__restrict__, size_t, int);    /* RFC2133 */
struct rpcent   *getrpcbyname(const char *);
struct rpcent   *getrpcbynumber(int);
struct rpcent   *getrpcent(void);
void            setrpcent(int);
struct hostent  *getipnodebyname(const char *, int, int, int *);  /* RFC 2553 */
struct hostent  *getipnodebyaddr(const void *, size_t, int, int *);  /* RFC 2553 */
void            freehostent(struct hostent *);  /* RFC 2553 */
#ifdef _USE_IRS
void            herror(const char *);
const char *    hstrerror(int);
#endif /* _USE_IRS */
struct hostent  *gethostbyname2(const char *, int);
extern void     setnetgrent(const char *);
extern void     endnetgrent(void);
extern int      innetgr(const char *, const char *, const char *, const char *);
extern int      getnetgrent(char **, char **, char **);


extern int getnetbyaddr_r(in_addr_t net, int type, struct netent *netptr,
        struct netent_data *net_data);
extern int getnetbyname_r(const char *name, struct netent *netptr,
        struct netent_data *net_data);
extern int setnetent_r(int f, struct netent_data *net_data);
extern void endnetent_r(struct netent_data *net_data);
extern int getnetent_r(struct netent *net, struct netent_data *net_data);
extern int gethostbyname_r(const char *name, struct hostent *htent,
        struct hostent_data *ht_data);
extern int gethostbyaddr_r(const char *addr, size_t len, int type,
        struct hostent *htent, struct hostent_data *ht_data);
extern int gethostent_r(struct hostent *htent, struct hostent_data *ht_data);
extern void endhostent_r(struct hostent_data *ht_data);
extern void sethostent_r(int flag, struct hostent_data *ht_data);
extern int setservent_r(int f, struct servent_data *serv_data);
extern void endservent_r(struct servent_data *serv_data);
extern int getservent_r(struct servent *serv, struct servent_data *serv_data);
extern int getservbyname_r(const char *name, const char *proto,
        struct servent *servptr, struct servent_data *serv_data);
extern int getservbyport_r(int port, const char *proto, struct servent *servptr,
        struct servent_data *serv_data);
extern int setprotoent_r(int f, struct protoent_data *proto_data);
extern void endprotoent_r(struct protoent_data *proto_data);
extern int getprotoent_r(struct protoent *proto,
        struct protoent_data *prot_data);
extern int getprotobyname_r(const char *name, struct protoent *protoptr,
        struct protoent_data *proto_data);
extern int getprotobynumber_r(int proto, struct protoent *protoptr,
         struct protoent_data *proto_data);
extern int setrpcent_r(int f, struct rpcent_data *rpc_data);
extern void endrpcent_r(struct rpcent_data *rpc_data);
extern int getrpcent_r(struct rpcent *rpcent, struct rpcent_data *rpc_data);
extern int getrpcbyname_r(const char *name, struct rpcent *rpcent,
                          struct rpcent_data *rpc_data);
extern int getrpcbynumber_r(int number, struct rpcent *rpcent,
                            struct rpcent_data *rpc_data);
extern int setnetgrent_r(char *, void **);
extern void endnetgrent_r(void **ptr);
extern int getnetgrent_r( char **, char **, char **, void **);
extern int innetgr_r(char *, char *, char *, char *, struct innetgr_data *);

extern int getdomainname(char *, int);
extern int setdomainname(char *, int);

#ifdef	_LINUX_SOURCE_COMPAT
extern int __linux_gethostbyname_r(const char *, struct hostent *, char *,
		size_t, struct hostent **, int*);
#define gethostbyname_r(a, b, c, d, e, f) \
	__linux_gethostbyname_r((a), (b), (c), (d), (e), (f))
extern int __linux_gethostbyaddr_r(const char *, size_t, int, struct hostent *,
		char *, size_t, struct hostent **, int *);
#define gethostbyaddr_r(a, b, c, d, e, f, g, h) \
	__linux_gethostbyaddr_r((a), (b), (c), (d), (e), (f), (g), (h))
#endif	/* _LINUX_SOURCE_COMPAT */

#endif /* _NO_PROTO */

#define NETDB_INTERNAL  -1 /* see errno */
#define NETDB_SUCCESS   0 /* no problem */
#define NO_ADDRESS      NO_DATA         /* no address, look for MX record */
#define SERVICE_UNAVAILABLE 5

#endif /* _ALL_SOURCE */

#endif /* _H_NETDB */
