/* static char sccsid[] = "@(#)41  1.7  src/bos/usr/include/rpc/svc_auth.h, libcrpc, bos530 6/3/97 15:42:16"; */
/*
 *   COMPONENT_NAME: LIBCRPC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 24
 *
 *
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 */

/*	@(#)svc_auth.h	1.2 90/07/17 4.1NFSSRC SMI	*/


/*
 * Service side of rpc authentication.
 */


#ifdef _AIX_TIRPC

#include <tirpc/rpc/svc_auth.h> 

#else

#ifndef _RPC_SVC_AUTH_H
#define	_RPC_SVC_AUTH_H

extern enum auth_stat _authenticate(struct svc_req *, struct rpc_msg *);

#endif 

#endif /*!_RPC_SVC_AUTH_H*/
