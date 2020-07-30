/* static char sccsid[] = "@(#)68  1.9  src/bos/usr/include/rpc/pmap_prot.h, libcrpc, bos530 4/19/00 13:31:43"; */
/*
 *   COMPONENT_NAME: LIBCRPC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 24
 *
 *
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 * 1.14 88/02/08 SMI	
 */

/*	@(#)pmap_prot.h	1.2 90/07/17 4.1NFSSRC SMI	*/


/*
 * pmap_prot.h
 * Protocol for the local binder service, or pmap.
 *
 *
 * The following procedures are supported by the protocol:
 *
 * PMAPPROC_NULL() returns ()
 * 	takes nothing, returns nothing
 *
 * PMAPPROC_SET(struct pmap) returns (bool_t)
 * 	TRUE is success, FALSE is failure.  Registers the tuple
 *	[prog, vers, prot, port].
 *
 * PMAPPROC_UNSET(struct pmap) returns (bool_t)
 *	TRUE is success, FALSE is failure.  Un-registers pair
 *	[prog, vers].  prot and port are ignored.
 *
 * PMAPPROC_GETPORT(struct pmap) returns (long unsigned).
 *	0 is failure.  Otherwise returns the port number where the pair
 *	[prog, vers] is registered.  It may lie!
 *
 * PMAPPROC_DUMP() RETURNS (struct pmaplist *)
 *
 * PMAPPROC_CALLIT(unsigned, unsigned, unsigned, string<>)
 * 	RETURNS (port, string<>);
 * usage: encapsulatedresults = PMAPPROC_CALLIT(prog, vers, proc, encapsulatedargs);
 * 	Calls the procedure on the local machine.  If it is not registered,
 *	this procedure is quite; ie it does not return error information!!!
 *	This procedure only is supported on rpc/udp and calls via
 *	rpc/udp.  This routine only passes null authentication parameters.
 *	This file has no interface to xdr routines for PMAPPROC_CALLIT.
 *
 * The service supports remote procedure calls on udp/ip or tcp/ip socket 111.
 */


#ifdef _AIX_TIRPC

#include <tirpc/rpc/pmap_prot.h>

#else 

#ifndef _RPC_PMAP_PROT_H
#define	_RPC_PMAP_PROT_H

#include <rpc/xdr.h>


#define PMAPPORT		((u_short)111)
#define PMAPPROG		((rpcprog_t)100000)
#define PMAPVERS		((rpcvers_t)2)
#define PMAPVERS_PROTO		((rpcvers_t)2)
#define PMAPVERS_ORIG		((rpcvers_t)1)
#define PMAPPROC_NULL		((rpcproc_t)0)
#define PMAPPROC_SET		((rpcproc_t)1)
#define PMAPPROC_UNSET		((rpcproc_t)2)
#define PMAPPROC_GETPORT	((rpcproc_t)3)
#define PMAPPROC_DUMP		((rpcproc_t)4)
#define PMAPPROC_CALLIT		((rpcproc_t)5)

struct pmap {
	rpcprog_t     pm_prog;
	rpcvers_t     pm_vers;
	rpcprot_t     pm_prot;
	rpcport_t     pm_port;
};

extern bool_t xdr_pmap(XDR *, struct pmap *);

struct pmaplist {
	struct pmap	pml_map;
	struct pmaplist *pml_next;
};

#ifndef _KERNEL
extern bool_t xdr_pmaplist(XDR *, struct pmaplist **);
#endif /*!_KERNEL*/

#endif 

#endif /*!_RPC_PMAP_PROT_H*/
