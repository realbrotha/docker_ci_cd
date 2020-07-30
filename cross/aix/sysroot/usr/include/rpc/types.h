/* static char sccsid[] = "@(#)42  1.16  src/bos/usr/include/rpc/types.h, libcrpc, bos530 7/25/02 19:29:32"; */
/*
 *   COMPONENT_NAME: LIBCRPC
 *
 *   FUNCTIONS: mem_alloc
 *		mem_free
 *		
 *
 *   ORIGINS: 24
 *
 *
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *      @(#)types.h 1.20 88/02/08 SMI      
 */

/*	@(#)types.h	1.6 90/07/19 4.1NFSSRC SMI	*/


/*
 * Rpc additions to <sys/types.h>
 */


#ifdef _AIX_TIRPC

#include <tirpc/rpc/types.h>

#else 
#ifndef	__RPC_TYPES_H
#define	__RPC_TYPES_H

#define	bool_t	int
#define	enum_t	int
#define __dontcare__	-1

/*
 *  LDT changes
 *    to match Sun's 64 bit rpc definition
 *    for kernel or 32 bit apps,            
 *      rpc data types are long/ulong
 *    other cases                           
 *      rpc data types are int/uint
 *  
 *  existing code
 *      rpc data types are long/ulong
 *              
 * 
*/
#if defined(_KERNEL) || !defined(__64BIT__)
typedef unsigned long rpcprog_t;
typedef unsigned long rpcvers_t;
typedef unsigned long rpcproc_t;
typedef unsigned long rpcprot_t;
typedef unsigned long rpcport_t;
typedef long          rpc_inline_t;
typedef long          rpcs1_t;  
typedef long          rpcs2_t;  
typedef unsigned long rpcxid_t; 
typedef unsigned long rpcrmtcall_arglen_t;
typedef unsigned long rpcrmtcall_resultslen_t;
typedef long          rpclong_t;  
#else                   
typedef unsigned int rpcprog_t;
typedef unsigned int rpcvers_t;
typedef unsigned int rpcproc_t;
typedef unsigned int rpcprot_t;
typedef unsigned int rpcport_t;
typedef int          rpc_inline_t;
typedef int          rpcs1_t;  
typedef int          rpcs2_t;  
typedef unsigned int rpcxid_t; 
typedef unsigned int rpcrmtcall_arglen_t;
typedef unsigned int rpcrmtcall_resultslen_t;  
typedef int           rpclong_t;  
#endif

#ifndef FALSE
#	define	FALSE	(0)
#endif

#ifndef TRUE
#	define	TRUE	(1)
#endif

#ifndef NULL
#	define NULL 0
#endif

#ifndef	_KERNEL
	#define	mem_alloc(bsize)	malloc(bsize)
	#define	mem_free(ptr, bsize)	free(ptr)
#else /* _KERNEL */
	#ifndef __cplusplus
		#include <sys/malloc.h>
		#define kmem_alloc(bsize)	xmalloc(bsize, 2, kernel_heap)
		#define	kmem_free(ptr, bsize)	xmfree(ptr, kernel_heap)
		#define	mem_alloc(bsize)	xmalloc(bsize, 2, kernel_heap)
		#define	mem_free(ptr, bsize)	xmfree(ptr, kernel_heap)
	#else /* __cplusplus */
		extern "C" char *mem_getbytes();
		#define mem_alloc(bsize)        mem_getbytes((u_int)bsize)
		#define mem_free(ptr, bsize)    mem_freebytes((caddr_t)(ptr))
	#endif /* __cplusplus */
#endif /* _KERNEL */

#include <sys/types.h>

#include <sys/time.h>

#endif 

#endif	/* !__RPC_TYPES_H */
