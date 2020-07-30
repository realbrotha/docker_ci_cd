/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* gos53D src/gos/2d/XTOP/lib/Xdmcp/Xdmcp.h 1.3                           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1997,2005          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)71	1.3  src/gos/2d/XTOP/lib/Xdmcp/Xdmcp.h, xdmcp, gos53D, d2005_16C4 4/19/05 13:47:53 */
/* $XConsortium: Xdmcp.h,v 1.9 95/06/07 18:30:59 gildea Exp $ */
/*
 * Copyright 1989 Network Computing Devices, Inc., Mountain View, California.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of N.C.D. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  N.C.D. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 */

#ifndef _XDMCP_H_
#define _XDMCP_H_

#include <X11/Xfuncproto.h>

#define XDM_PROTOCOL_VERSION	1
#define XDM_UDP_PORT		177

/* IANA has assigned FF0X:0:0:0:0:0:0:12B as the permanently assigned
 * multicast addresses for XDMCP, where X in the prefix may be replaced
 * by any valid scope identifier, such as 1 for Node-Local, 2 for Link-Local,
 * 5 for Site-Local, and so on.  We set the default here to the Link-Local
 * version to most closely match the old IPv4 subnet broadcast behavior.
 * Both xdm and X -query allow specifying a different address if a different
 * scope is defined.
 */
#define XDM_DEFAULT_MCAST_ADDR6 "ff02:0:0:0:0:0:0:12b"

#define XDM_MAX_MSGLEN		8192
#define XDM_MIN_RTX		2
#define XDM_MAX_RTX		32
#define XDM_RTX_LIMIT		7
#define XDM_KA_RTX_LIMIT	4
#define XDM_DEF_DORMANCY	(3 * 60)	/* 3 minutes */
#define XDM_MAX_DORMANCY	(24 * 60 * 60)	/* 24 hours */

typedef enum {
    BROADCAST_QUERY = 1, QUERY, INDIRECT_QUERY, FORWARD_QUERY,
    WILLING, UNWILLING, REQUEST, ACCEPT, DECLINE, MANAGE, REFUSE, 
    FAILED, KEEPALIVE, ALIVE 
} xdmOpCode;

typedef enum {
    XDM_QUERY, XDM_BROADCAST, XDM_INDIRECT, XDM_COLLECT_QUERY,
    XDM_COLLECT_BROADCAST_QUERY, XDM_COLLECT_INDIRECT_QUERY,
    XDM_START_CONNECTION, XDM_AWAIT_REQUEST_RESPONSE,
    XDM_AWAIT_MANAGE_RESPONSE, XDM_MANAGE, XDM_RUN_SESSION, XDM_OFF,
    XDM_AWAIT_USER_INPUT, XDM_KEEPALIVE, XDM_AWAIT_ALIVE_RESPONSE,
#if defined(IPv6) && defined(AF_INET6)
    XDM_MULTICAST, XDM_COLLECT_MULTICAST_QUERY,
#endif
    XDM_KEEP_ME_LAST
} xdmcp_states;

#ifdef NOTDEF
/* table of hosts */

#define XDM_MAX_STR_LEN 21
#define XDM_MAX_HOSTS 20
struct xdm_host_table {
  struct sockaddr_in sockaddr;
  char name[XDM_MAX_STR_LEN];
  char status[XDM_MAX_STR_LEN];
};
#endif /* NOTDEF */

typedef CARD8	*CARD8Ptr;
typedef CARD16	*CARD16Ptr;
typedef CARD32	*CARD32Ptr;

typedef struct _ARRAY8 {
    CARD16	length;
    CARD8Ptr	data;
} ARRAY8, *ARRAY8Ptr;

typedef struct _ARRAY16 {
    CARD8	length;
    CARD16Ptr	data;
} ARRAY16, *ARRAY16Ptr;

typedef struct _ARRAY32 {
    CARD8	length;
    CARD32Ptr	data;
} ARRAY32, *ARRAY32Ptr;

typedef struct _ARRAYofARRAY8 {
    CARD8	length;
    ARRAY8Ptr	data;
} ARRAYofARRAY8, *ARRAYofARRAY8Ptr;

typedef struct _XdmcpHeader {
    CARD16  version, opcode, length;
} XdmcpHeader, *XdmcpHeaderPtr;

typedef struct _XdmcpBuffer {
    BYTE    *data;
    int	    size;		/* size of buffer pointed by to data */
    int	    pointer;		/* current index into data */
    int	    count;		/* bytes read from network into data */
} XdmcpBuffer, *XdmcpBufferPtr;

typedef struct _XdmAuthKey {
    BYTE    data[8];
} XdmAuthKeyRec, *XdmAuthKeyPtr;


/* implementation-independent network address structure.
   Equiv to sockaddr* for sockets and netbuf* for STREAMS. */

typedef char *XdmcpNetaddr;

_XFUNCPROTOBEGIN

extern int XdmcpWriteCARD8(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    CARD8		/* value */
#endif
);

extern int XdmcpWriteCARD16(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    CARD16		/* value */
#endif
);

extern int XdmcpWriteCARD32(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    CARD32		/* value */
#endif
);

extern int XdmcpWriteARRAY8(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    ARRAY8Ptr		/* array */
#endif
);

extern int XdmcpWriteARRAY16(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    ARRAY16Ptr		/* array */
#endif
);

extern int XdmcpWriteARRAY32(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    ARRAY32Ptr		/* array */
#endif
);

extern int XdmcpWriteARRAYofARRAY8(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    ARRAYofARRAY8Ptr	/* array */
#endif
);

extern int XdmcpWriteHeader(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    XdmcpHeaderPtr	/* header */
#endif
);

extern int XdmcpFlush(
#if NeedFunctionPrototypes
    int 		/* fd */,
    XdmcpBufferPtr	/* buffer */,
    XdmcpNetaddr	/* to */,
    int			/* tolen */
#endif
);

extern int XdmcpReadCARD8(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    CARD8Ptr		/* valuep */
#endif
);

extern int XdmcpReadCARD16(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    CARD16Ptr		/* valuep */
#endif
);

extern int XdmcpReadCARD32(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    CARD32Ptr		/* valuep */
#endif
);

extern int XdmcpReadARRAY8(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    ARRAY8Ptr		/* array */
#endif
);

extern int XdmcpReadARRAY16(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    ARRAY16Ptr		/* array */
#endif
);

extern int XdmcpReadARRAY32(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    ARRAY32Ptr		/* array */
#endif
);

extern int XdmcpReadARRAYofARRAY8(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    ARRAYofARRAY8Ptr	/* array */
#endif
);

extern int XdmcpReadHeader(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */,
    XdmcpHeaderPtr	/* header */
#endif
);

extern int XdmcpFill(
#if NeedFunctionPrototypes
    int 		/* fd */,
    XdmcpBufferPtr	/* buffer */,
    XdmcpNetaddr	/* from */,
    int*		/* fromlen */
#endif
);

extern int XdmcpReadRemaining(
#if NeedFunctionPrototypes
    XdmcpBufferPtr	/* buffer */
#endif
);

extern void XdmcpDisposeARRAY8(
#if NeedFunctionPrototypes
    ARRAY8Ptr		/* array */
#endif
);

extern void XdmcpDisposeARRAY16(
#if NeedFunctionPrototypes
    ARRAY16Ptr		/* array */
#endif
);

extern void XdmcpDisposeARRAY32(
#if NeedFunctionPrototypes
    ARRAY32Ptr		/* array */
#endif
);

extern void XdmcpDisposeARRAYofARRAY8(
#if NeedFunctionPrototypes
    ARRAYofARRAY8Ptr	/* array */
#endif
);

extern int XdmcpCopyARRAY8(
#if NeedFunctionPrototypes
    ARRAY8Ptr		/* src */,
    ARRAY8Ptr		/* dst */
#endif
);

extern int XdmcpARRAY8Equal(
#if NeedFunctionPrototypes
    ARRAY8Ptr		/* array1 */,
    ARRAY8Ptr		/* array2 */
#endif
);

#ifdef HASXDMAUTH
extern void XdmcpGenerateKey(
#if NeedFunctionPrototypes
    XdmAuthKeyPtr	/* key */
#endif
);

extern void XdmcpIncrementKey(
#if NeedFunctionPrototypes
    XdmAuthKeyPtr	/* key */
#endif
);

extern void XdmcpDecrementKey(
#if NeedFunctionPrototypes
    XdmAuthKeyPtr	/* key */
#endif
);

extern void XdmcpWrap(
#if NeedFunctionPrototypes
    unsigned char*	/* input */,
    unsigned char*	/* output */,
    unsigned char*	/* wrapper */,
    int			/* bytes */
#endif
);

extern void XdmcpUnwrap(
#if NeedFunctionPrototypes
    unsigned char*	/* input */,
    unsigned char*	/* output */,
    unsigned char*	/* wrapper */,
    int			/* bytes */
#endif
);

#endif

_XFUNCPROTOEND

#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif

#if !defined(Xalloc) && !defined(xalloc) && !defined(Xrealloc)
extern long *Xalloc (), *Xrealloc ();
extern void Xfree();
#endif

#endif /* _XDMCP_H_ */
