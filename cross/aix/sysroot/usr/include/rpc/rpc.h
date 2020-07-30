/* static char sccsid[] = "@(#)38  1.7  src/bos/usr/include/rpc/rpc.h, libcrpc, bos530 11/8/96 15:11:25"; */
/*
 *   COMPONENT_NAME: LIBCRPC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 24
 *
 *
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *	@(#)rpc.h 1.9 88/02/08 SMI	  
 */

/*	@(#)rpc.h	1.3 90/07/17 4.1NFSSRC SMI	*/


/*
 * rpc.h, Just includes the billions of rpc header files necessary to 
 * do remote procedure calling.
 */


#ifdef _AIX_TIRPC

#include <tirpc/rpc/rpc.h>

#else 

#ifndef _RPC_RPC_H
#define	_RPC_RPC_H

#include <rpc/types.h>		/* some typedefs */
#include <netinet/in.h>

/* external data representation interfaces */
#include <rpc/xdr.h>		/* generic (de)serializer */

/* Client side only authentication */
#include <rpc/auth.h>		/* generic authenticator (client side) */

/* Client side (mostly) remote procedure call */
#include <rpc/clnt.h>		/* generic rpc stuff */

/* semi-private protocol headers */
#include <rpc/rpc_msg.h>	/* protocol for rpc messages */
#include <rpc/auth_unix.h>	/* protocol for unix style cred */
#include <rpc/auth_des.h>	/* protocol for des style cred */

/* Server side only remote procedure callee */
#include <rpc/svc.h>		/* service manager and multiplexer */
#include <rpc/svc_auth.h>	/* service side authenticator */

#endif 

#endif /*!_RPC_RPC_H*/
