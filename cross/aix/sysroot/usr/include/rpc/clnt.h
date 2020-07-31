/* @(#)66       1.5.1.13  src/bos/usr/include/rpc/clnt.h, libcrpc, bos530 2/8/01 10:32:04 */
/*
 *   COMPONENT_NAME: LIBCRPC
 *
 *   FUNCTIONS: CLNT_ABORT
 *		CLNT_CALL
 *		CLNT_CONTROL
 *		CLNT_DESTROY
 *		CLNT_FREERES
 *		CLNT_GETERR
 *		alloc_xid
 *		clnt_abort
 *		clnt_call
 *		clnt_control
 *		clnt_destroy
 *		clnt_freeres
 *		clnt_geterr
 *		
 *
 *   ORIGINS: 24
 *
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *
 */

/*	@(#)clnt.h	1.3 90/07/19 4.1NFSSRC SMI	*/

/*
 * clnt.h - Client side remote procedure call interface.
 */


#ifdef _AIX_TIRPC

#include <tirpc/rpc/clnt.h>

#else

#ifndef _RPC_CLNT_H
#define	_RPC_CLNT_H

#ifdef __cplusplus
extern "C" {
#include <rpc/types.h>
#endif

/*
 * Rpc calls return an enum clnt_stat.  This should be looked at more,
 * since each implementation is required to live with this (implementation
 * independent) list of errors.
 */
enum clnt_stat {
	RPC_SUCCESS=0,			/* call succeeded */
	/*
	 * local errors
	 */
	RPC_CANTENCODEARGS=1,		/* can't encode arguments */
	RPC_CANTDECODERES=2,		/* can't decode results */
	RPC_CANTSEND=3,			/* failure in sending call */
	RPC_CANTRECV=4,			/* failure in receiving result */
	RPC_TIMEDOUT=5,			/* call timed out */
	RPC_INTR=18,                    /* call interrupted */
	/*
	 * remote errors
	 */
	RPC_VERSMISMATCH=6,		/* rpc versions not compatible */
	RPC_AUTHERROR=7,		/* authentication error */
	RPC_PROGUNAVAIL=8,		/* program not available */
	RPC_PROGVERSMISMATCH=9,		/* program version mismatched */
	RPC_PROCUNAVAIL=10,		/* procedure unavailable */
	RPC_CANTDECODEARGS=11,		/* decode arguments error */
	RPC_SYSTEMERROR=12,		/* generic "other problem" */

	/*
	 * callrpc & clnt_create errors
	 */
	RPC_UNKNOWNHOST=13,		/* unknown host name */
	RPC_UNKNOWNPROTO=17,		/* unkown protocol */

	/*
	 * _ create errors
	 */
	RPC_PMAPFAILURE=14,		/* the pmapper failed in its call */
	RPC_PROGNOTREGISTERED=15,	/* remote program is not registered */
	/*
	 * unspecified error
	 */
	RPC_FAILED=16
};


/*
 * Error info.
 */
struct rpc_err {
	enum clnt_stat re_status;
	union {
		int RE_errno;		/* realated system error */
		enum auth_stat RE_why;	/* why the auth error occurred */
		struct {
			rpcvers_t low;  /* lowest verion supported */
			rpcvers_t high; /* highest verion supported */
		} RE_vers;
		struct {		/* maybe meaningful if RPC_FAILED */
			rpcs1_t s1;
			rpcs2_t s2;
		} RE_lb;		/* life boot & debugging only */
	} ru;
#define	re_errno	ru.RE_errno
#define	re_why		ru.RE_why
#define	re_vers		ru.RE_vers
#define	re_lb		ru.RE_lb
};


/*
 * Client rpc handle.
 * Created by individual implementations, see e.g. rpc_udp.c.
 * Client is responsible for initializing auth, see e.g. auth_none.c.
 */
typedef struct __client {
	AUTH	*cl_auth;			/* authenticator */
	struct clnt_ops {
#ifdef _NO_PROTO
		enum clnt_stat	(*cl_call)();	/* call remote procedure */
		void		(*cl_abort)();	/* abort a call */
                void            (*cl_geterr)(); /* get specific error code */
		bool_t		(*cl_freeres)(); /* frees results */
		void		(*cl_destroy)();/* destroy this structure */
		bool_t          (*cl_control)();/* the ioctl() of rpc */
#else
		enum clnt_stat	(*cl_call)(struct __client *, rpcproc_t,
                                           xdrproc_t, caddr_t, 
					   xdrproc_t, caddr_t, struct timeval);
		void		(*cl_abort)(void);
                void            (*cl_geterr)(struct __client *, struct rpc_err *);
		bool_t		(*cl_freeres)(struct __client *, xdrproc_t, caddr_t);
		void		(*cl_destroy)(struct __client *);
		bool_t          (*cl_control)(struct __client *, int, char *);
#endif
	} *cl_ops;
	caddr_t			cl_private;	/* private stuff */
} CLIENT;


/*
 * client side rpc interface ops
 *
 * Parameter types are:
 *
 */

/*
 * enum clnt_stat
 * CLNT_CALL(rh, proc, xargs, argsp, xres, resp, timeout)
 * 	CLIENT *rh;
 *	rpcproc_t proc;
 *	xdrproc_t xargs;
 *	caddr_t argsp;
 *	xdrproc_t xres;
 *	caddr_t resp;
 *	struct timeval timeout;
 */
#define	CLNT_CALL(rh, proc, xargs, argsp, xres, resp, secs)	\
	((*(rh)->cl_ops->cl_call)(rh, proc, xargs, argsp, xres, resp, secs))
#define	clnt_call(rh, proc, xargs, argsp, xres, resp, secs)	\
	((*(rh)->cl_ops->cl_call)(rh, proc, xargs, argsp, xres, resp, secs))

/*
 * void
 * CLNT_ABORT(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_ABORT(rh)	((*(rh)->cl_ops->cl_abort)(rh))
#define	clnt_abort(rh)	((*(rh)->cl_ops->cl_abort)(rh))

/*
 * struct rpc_err
 * CLNT_GETERR(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_GETERR(rh,errp)	((*(rh)->cl_ops->cl_geterr)(rh, errp))
#define	clnt_geterr(rh,errp)	((*(rh)->cl_ops->cl_geterr)(rh, errp))


/*
 * bool_t
 * CLNT_FREERES(rh, xres, resp);
 * 	CLIENT *rh;
 *	xdrproc_t xres;
 *	caddr_t resp;
 */
#define	CLNT_FREERES(rh,xres,resp) ((*(rh)->cl_ops->cl_freeres)(rh,xres,resp))
#define	clnt_freeres(rh,xres,resp) ((*(rh)->cl_ops->cl_freeres)(rh,xres,resp))

/*
 * bool_t
 * CLNT_CONTROL(cl, request, info)
 *      CLIENT *cl;
 *      u_int request;
 *      char *info;
 */
#define	CLNT_CONTROL(cl,rq,in) ((*(cl)->cl_ops->cl_control)(cl,rq,in))
#define	clnt_control(cl,rq,in) ((*(cl)->cl_ops->cl_control)(cl,rq,in))

/*
 * control operations that apply to both udp and tcp transports
 */
#define CLSET_TIMEOUT       1   /* set timeout (timeval) */
#define CLGET_TIMEOUT       2   /* get timeout (timeval) */
#define CLGET_SERVER_ADDR   3   /* get server's address (sockaddr) */
#define	CLGET_FD		6   /* get connections file descriptor */
#define	CLSET_FD_CLOSE		8   /* close fd while clnt_destroy */
#define	CLSET_FD_NCLOSE		9   /* Do not close fd while clnt_destroy */
/*
 * udp only control operations
 */
#define CLSET_RETRY_TIMEOUT 4   /* set retry timeout (timeval) */
#define CLGET_RETRY_TIMEOUT 5   /* get retry timeout (timeval) */

/*
 * void
 * CLNT_DESTROY(rh);
 * 	CLIENT *rh;
 */
#define	CLNT_DESTROY(rh)	((*(rh)->cl_ops->cl_destroy)(rh))
#define	clnt_destroy(rh)	((*(rh)->cl_ops->cl_destroy)(rh))


/*
 * RPCTEST is a test program which is accessable on every rpc
 * transport/port.  It is used for testing, performance evaluation,
 * and network administration.
 */

#define RPCTEST_PROGRAM		((rpcprog_t)1)
#define RPCTEST_VERSION		((rpcvers_t)1)
#define RPCTEST_NULL_PROC	((rpcproc_t)2)
#define RPCTEST_NULL_BATCH_PROC	((rpcproc_t)3)

/*
 * By convention, procedure 0 takes null arguments and returns them
 */

#define NULLPROC ((rpcproc_t)0)

/*
 * Below are the client handle creation routines for the various
 * implementations of client side rpc.  They can return NULL if a 
 * creation failure occurs.
 */

#ifndef _KERNEL
/*
 * Memory based rpc (for speed check and testing)
 * CLIENT *
 * clntraw_create(prog, vers)
 *	rpcprog_t prog;
 *	rpcvers_t vers;
 */
extern CLIENT *clntraw_create(rpcprog_t, rpcvers_t);


/*
 * Generic client creation routine. Supported protocols are "udp" and "tcp"
 */
extern CLIENT *
clnt_create(char *, rpcprog_t, rpcvers_t, char *);

/*
 * Generic client creation routine. Supported protocols are "udp" and "tcp"
 */
extern CLIENT *
clnt_create_vers(char *, rpcprog_t, rpcvers_t *, rpcvers_t, rpcvers_t, char *);



/*
 * TCP based rpc
 * CLIENT *
 * clnttcp_create(raddr, prog, vers, sockp, sendsz, recvsz)
 *	struct sockaddr_in *raddr;
 *	rpcprog_t prog;
 *	rpcvers_t version;
 *	register int *sockp;
 *	u_int sendsz;
 *	u_int recvsz;
 */
extern CLIENT *clnttcp_create(struct sockaddr_in *, rpcprog_t, rpcvers_t,
			      int *, u_int, u_int);

/*
 * UDP based rpc.
 * CLIENT *
 * clntudp_create(raddr, program, version, wait, sockp)
 *	struct sockaddr_in *raddr;
 *	rpcprog_t program;
 *	rpcvers_t version;
 *	struct timeval wait;
 *	int *sockp;
 *
 * Same as above, but you specify max packet sizes.
 * CLIENT *
 * clntudp_bufcreate(raddr, program, version, wait, sockp, sendsz, recvsz)
 *	struct sockaddr_in *raddr;
 *	rpcprog_t program;
 *	rpcvers_t version;
 *	struct timeval wait;
 *	int *sockp;
 *	u_int sendsz;
 *	u_int recvsz;
 */
extern CLIENT *clntudp_create(struct sockaddr_in *, rpcprog_t, rpcvers_t,
			      struct timeval, int *);
extern CLIENT *clntudp_bufcreate(struct sockaddr_in *, rpcprog_t, rpcvers_t,
				 struct timeval, int *, u_int, u_int);

/*
 * Print why creation failed
 */
void clnt_pcreateerror(char *);	/* stderr */
char *clnt_spcreateerror(char *);	/* string */

/*
 * Like clnt_perror(), but is more verbose in its output
 */ 
void clnt_perrno(enum clnt_stat);	/* stderr */

/*
 * Print an English error message, given the client error code
 */
void clnt_perror(CLIENT *, char *); 	/* stderr */
char *clnt_sperror(CLIENT *, char *);	/* string */

/* 
 * If a creation fails, the following allows the user to figure out why.
 */
struct rpc_createerr {
	enum clnt_stat cf_stat;
	struct rpc_err cf_error; /* useful when cf_stat == RPC_PMAPFAILURE */
};

extern struct rpc_createerr rpc_createerr;
struct rpc_createerr *_rpc_createerr(void);

extern int getrpcport(const char *, u_long, u_long, u_int);

#endif /* !_KERNEL */

/*
 * Copy error message to buffer.
 */
char *clnt_sperrno(enum clnt_stat);	/* string */


#ifdef _KERNEL
/*
 * Kernel udp based rpc
 * CLIENT *
 * clntkudp_create(addr, pgm, vers)
 *	struct sockaddr_in *addr;
 *	rpcproc_t pgm;
 *	rpcvers_t vers;
 */
extern CLIENT *clntkudp_create(struct sockaddr_in *, rpcproc_t, rpcvers_t,
			       int, struct ucred *);
#endif

/*
 * Timers used for the pseudo-transport protocol when using datagrams
 */
struct rpc_timers {
	u_short		rt_srtt;	/* smoothed round-trip time */
	u_short		rt_deviate;	/* estimated deviation */
	u_long		rt_rtxcur;	/* current (backed-off) rto */
};

/*
 * Feedback values used for possible congestion and rate control
 */
#define	FEEDBACK_REXMIT1	1	/* first retransmit */
#define	FEEDBACK_OK		2	/* no retransmits */

#define	UDPMSGSIZE	8800	/* rpc imposed limit on udp msg size */
#define	RPCSMALLMSGSIZE	400	/* a more reasonable packet size */

#ifdef	_KERNEL
/*
 *	Alloc_xid presents an interface which kernel RPC clients
 *	should use to allocate their XIDs.  Its implementation
 *	may change over time (for example, to allow sharing of
 *	XIDs between the kernel and user-level applications, so
 *	all XID allocation should be done by calling alloc_xid().
 */
extern u_int	alloc_xid(void);
#endif

/*
 * Used in KERNEL and user space.  These statistics are recorded in the
 * nfs_krpc.ext kernel extension and reported via the cmd nfsstat or the
 * programming interface nfs_cntl() (see below).
 *
 * client side rpc statistics
 * struct is to be used with
 * NFS_CNTL_GET_CLKRPC_STAT in which the return stats are placed
 * in var of this type, i.e.
 * t_rcstat rcstat;
 * nfs_cntl(NFS_CNTL_GET_CLKRPC_STAT,&rcstat,NFS_CNTL_CLKRPC_SIZE);
 */
typedef struct {
	int     rccalls;
	int     rcbadcalls;
	int     rcretrans;
	int     rcbadxids;
	int     rctimeouts;
	int     rcwaits;
	int     rcnewcreds;
	int     rcbadverfs;
	int     rctimers;
} t_rcstat;


#endif

#ifdef __cplusplus
}
#endif

#endif /*!_RPC_CLNT_H*/