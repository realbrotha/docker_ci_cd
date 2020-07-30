/* static char sccsid[] = "@(#)69  1.8  src/bos/usr/include/rpc/pmap_rmt.h, libcrpc, bos530 4/19/00 13:31:59"; */
/*
 *   COMPONENT_NAME: LIBCRPC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 24
 *
 *
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *	1.2 88/02/08 SMI	
 */

/*	@(#)pmap_rmt.h	1.2 90/07/17 4.1NFSSRC SMI	*/


/*
 * Structures and XDR routines for parameters to and replies from
 * the portmapper remote-call-service.
 */


#ifdef _AIX_TIRPC

#include <tirpc/rpc/pmap_rmt.h> 

#else 

#ifndef _RPC_PMAP_RMT_H
#define	_RPC_PMAP_RMT_H

struct rmtcallargs {
	rpcprog_t prog; 
        rpcvers_t vers;
        rpcproc_t proc; 
        rpcrmtcall_arglen_t arglen;
	caddr_t args_ptr;
	xdrproc_t xdr_args;
};

bool_t xdr_rmtcall_args(XDR *, struct rmtcallargs *);

struct rmtcallres {
	rpcport_t *port_ptr;
	rpcrmtcall_resultslen_t resultslen;
	caddr_t results_ptr;
	xdrproc_t xdr_results;
};

bool_t xdr_rmtcallres(XDR *, struct rmtcallres *);

#endif 

#endif /*!_RPC_PMAP_RMT_H*/
