/* static char sccsid[] = "@(#)24  1.2  src/bos/usr/include/rpc/raw.h, libcrpc, bos530 11/8/96 15:10:35"; */
/*
 *   COMPONENT_NAME: LIBCRPC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 24
 *
 *
 * Copyright (C) 1989,1990 Sun Microsystems, Inc.
 */

/*	@(#)raw.h	1.1 90/07/19 4.1NFSSRC SMI	*/

/*
 * raw.h
 *
 * Raw interface
 * The common memory area over which they will communicate
 *
 */


#ifdef _AIX_TIRPC

#include <tirpc/rpc/raw.h>

#else

#ifndef _RPC_RAW_H
#define	_RPC_RAW_H
 char *_rpcrawcombuf;

#endif

#endif /* !_RPC_RAW_H */
