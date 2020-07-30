/* static char sccsid[] = "@(#)37  1.9  src/bos/usr/include/rpc/pmap_clnt.h, libcrpc, bos530 4/19/00 13:31:16"; */
/*
 *   COMPONENT_NAME: LIBCRPC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 24
 *
 *
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *	@(#)pmap_clnt.h 1.11 88/02/08 SMI
 */

/*	@(#)pmap_clnt.h	1.2 90/07/17 4.1NFSSRC SMI	*/


/*
 * pmap_clnt.h
 * Supplies C routines to get to portmap services.
 */

/*
 * Usage:
 *	success = pmap_set(program, version, protocol, port);
 *	success = pmap_unset(program, version);
 *	port = pmap_getport(address, program, version, protocol);
 *	head = pmap_getmaps(address);
 *	clnt_stat = pmap_rmtcall(address, program, version, procedure,
 *		xdrargs, argsp, xdrres, resp, tout, port_ptr)
 *		(works for udp only.) 
 * 	clnt_stat = clnt_broadcast(program, version, procedure,
 *		xdrargs, argsp,	xdrres, resp, eachresult)
 *		(like pmap_rmtcall, except the call is broadcasted to all
 *		locally connected nets.  For each valid response received,
 *		the procedure eachresult is called.  Its form is:
 *	done = eachresult(resp, raddr)
 *		bool_t done;
 *		caddr_t resp;
 *		struct sockaddr_in raddr;
 *		where resp points to the results of the call and raddr is the
 *		address if the responder to the broadcast.
 */


#ifdef _AIX_TIRPC

#include <tirpc/rpc/pmap_clnt.h>

#else 

#ifndef _RPC_PMAP_CLNT_H
#define	_RPC_PMAP_CLNT_H

typedef bool_t (*resultproc_t)(caddr_t, struct sockaddr_in *);

extern bool_t		pmap_set(rpcprog_t, rpcvers_t, rpcprot_t, u_short);
extern bool_t		pmap_unset(rpcprog_t, rpcvers_t);
extern struct pmaplist	*pmap_getmaps(struct sockaddr_in *);
enum clnt_stat		pmap_rmtcall(struct sockaddr_in *, rpcprog_t, rpcvers_t,
				     rpcproc_t, xdrproc_t, caddr_t, xdrproc_t,
				     caddr_t, struct timeval, rpcport_t *);
enum clnt_stat		clnt_broadcast(rpcprog_t, rpcvers_t, rpcproc_t, xdrproc_t,
				       caddr_t, xdrproc_t, caddr_t,
				       resultproc_t);
extern u_short		pmap_getport(struct sockaddr_in *, rpcprog_t, rpcvers_t,
				     rpcprot_t);

#endif 

#endif /*!_RPC_PMAP_CLNT_H*/
