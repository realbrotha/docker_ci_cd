/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos53Q src/bos/kernext/iocp/iocp.h 1.7                                 */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* COPYRIGHT International Business Machines Corp. 1999,2008              */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
#define IOCP_H_SCCSID "@(#)86  1.7  src/bos/kernext/iocp/iocp.h, sysxiocp, bos53Q, q2008_21C1 5/16/08 18:56:41"
#include <sys/errno.h>

#ifndef	_iocp_types
#define	_iocp_types
typedef	int 			DWORD;
typedef	int 			SOCKET;
typedef	DWORD *			LPDWORD;
typedef int			HANDLE;
typedef	void *			PVOID;
typedef	void *			LPVOID;
typedef	const void *		LPCVOID;
typedef boolean_t		BOOL;
#endif

#define	INVALID_HANDLE_VALUE	((HANDLE)(-1))
#define	INFINITE		(-1)

typedef struct __ovl {
	DWORD		Internal; 
	DWORD		InternalHigh; 
	DWORD		Offset; 
	DWORD		OffsetHigh; 
	HANDLE		hEvent; 
} OVERLAPPED; 

typedef OVERLAPPED *	LPOVERLAPPED;

struct gmcs {
	DWORD   	transfer_count;
	DWORD   	completion_key;
	LPOVERLAPPED	overlapped;
	DWORD		errorno;
};

#ifdef _KERNEL
struct gmcs32 {
	DWORD   	transfer_count;
	DWORD   	completion_key;
	DWORD		overlapped;
	DWORD		errorno;
};

struct gmcs64 {
	DWORD   	transfer_count;
	DWORD   	completion_key;
	ptr64		overlapped;
	DWORD		errorno;
};
#endif

#define GMCS_NMAX 4096		/* max for nmax below */
				/* beware: stack space allocation */

int
GetMultipleCompletionStatus (
	HANDLE		completion_port,
	DWORD		nmin,
	DWORD		nmax,
	DWORD		timeout,
	struct gmcs	results[]
);

#ifdef	__FULL_PROTO

HANDLE 
CreateIoCompletionPort (
	HANDLE		fd,
	HANDLE		completion_port,
	DWORD		completion_key,
	DWORD		thread_count
);
	
BOOL
GetQueuedCompletionStatus (
	HANDLE		completion_port,
	LPDWORD   	transfer_count,
	LPDWORD   	completion_key,
	LPOVERLAPPED  *	overlapped,
	DWORD		timeout
);

BOOL
PostQueuedCompletionStatus (
	HANDLE		completion_port,
	DWORD		transfer_count,
	DWORD		completion_key,
	LPOVERLAPPED    overlapped
);

BOOL
ReadFile (
	HANDLE		fd,
	LPVOID 	       	buf,
	DWORD		read_count,
	LPDWORD        	amount_read,
	LPOVERLAPPED    overlapped
);	

BOOL
WriteFile (
	HANDLE		fd,
	LPCVOID        	buf,
	DWORD		write_count,
	LPDWORD        	amount_written,
	LPOVERLAPPED    overlapped
);	

HANDLE  AcceptIOCP(
        SOCKET  lis_fd,
        SOCKET  acc_fd,
        PVOID   buf,
        DWORD   read_count,
        HANDLE  completion_port,
        DWORD   completion_key,
        LPDWORD amount_read,
        LPOVERLAPPED    overlapped
);

#endif	/* __FULL_PROTO */
