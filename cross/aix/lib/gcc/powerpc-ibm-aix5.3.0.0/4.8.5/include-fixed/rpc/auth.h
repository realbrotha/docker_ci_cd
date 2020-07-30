/*  DO NOT EDIT THIS FILE.

    It has been auto-edited by fixincludes from:

	"/opt/cross/aix/sysroot/usr/include/rpc/auth.h"

    This had to be done to correct non-standard usages in the
    original, manufacturer supplied header file.  */

/* static char sccsid[] = "@(#)63  1.12  src/bos/usr/include/rpc/auth.h, libcrpc, bos530 11/24/03 16:49:11"; */
/*
 *   COMPONENT_NAME: LIBCRPC
 *
 *   FUNCTIONS: AUTH_DESTROY
 *		AUTH_MARSHALL
 *		AUTH_NEXTVERF
 *		AUTH_REFRESH
 *		AUTH_VALIDATE
 *		auth_destroy
 *		auth_marshall
 *		auth_nextverf
 *		auth_refresh
 *		auth_validate
 *
 *   ORIGINS: 24
 *
 * Copyright (C) 1984, Sun Microsystems, Inc.
 *
 *
 */

/*
 * auth.h, Authentication interface.
 *
 *
 * The data structures are completely opaque to the client.  The client
 * is required to pass a AUTH * to routines that create rpc
 * "sessions".
 */


#ifdef _AIX_TIRPC
#include <tirpc/rpc/auth.h>
#else

#ifndef _RPC_AUTH_H
#define	_RPC_AUTH_H

#define	MAX_AUTH_BYTES	400
#define	MAXNETNAMELEN	255	/* maximum length of network user's name */

#include <rpc/xdr.h>

/*
 * Status returned from authentication check
 */
enum auth_stat {
	AUTH_OK=0,
	/*
	 * failed at remote end
	 */
	AUTH_BADCRED=1,			/* bogus credentials (seal broken) */
	AUTH_REJECTEDCRED=2,		/* client should begin new session */
	AUTH_BADVERF=3,			/* bogus verifier (seal broken) */
	AUTH_REJECTEDVERF=4,		/* verifier expired or was replayed */
	AUTH_TOOWEAK=5,			/* rejected due to security reasons */
	/*
	 * failed locally
	*/
	AUTH_INVALIDRESP=6,		/* bogus response verifier */
	AUTH_FAILED=7			/* some unknown reason */
};

/* typedef u_long u_int32; */ /* 32-bit unsigned integers */

union des_block {
	struct {
		u_int32 high;
		u_int32 low;
	} key;
	char c[8];
};
typedef union des_block des_block;
extern bool_t xdr_des_block(XDR *, des_block *);

/*
 * Authentication info.  Opaque to client.
 */
struct opaque_auth {
	enum_t	oa_flavor;		/* flavor of auth */
	caddr_t	oa_base;		/* address of more auth stuff */
	u_int	oa_length;		/* not to exceed MAX_AUTH_BYTES */
};


/*
 * Auth handle, interface to client side authenticators.
 */
typedef struct __auth {
	struct	opaque_auth	ah_cred;
	struct	opaque_auth	ah_verf;
	union	des_block	ah_key;
	struct auth_ops {
#ifdef _NO_PROTO
#ifdef __cplusplus
		void	(*ah_nextverf)(...);
#else
		void	(*ah_nextverf)();
#endif
#ifdef __cplusplus
		int	(*ah_marshal)(...);	/* nextverf & serialize */
#else
		int	(*ah_marshal)();	/* nextverf & serialize */
#endif
#ifdef __cplusplus
		int	(*ah_validate)(...);	/* validate varifier */
#else
		int	(*ah_validate)();	/* validate varifier */
#endif
#ifdef __cplusplus
		int	(*ah_refresh)(...);	/* refresh credentials */
#else
		int	(*ah_refresh)();	/* refresh credentials */
#endif
#ifdef __cplusplus
		void	(*ah_destroy)(...);	/* destroy this structure */
#else
		void	(*ah_destroy)();	/* destroy this structure */
#endif
#else
		void	(*ah_nextverf)(struct __auth *);
		int	(*ah_marshal)(struct __auth *, XDR *);
		int	(*ah_validate)(struct __auth *, struct opaque_auth *);
		int	(*ah_refresh)(struct __auth *);
		void	(*ah_destroy)(struct __auth *);
#endif
	} *ah_ops;
	caddr_t ah_private;
} AUTH;


/*
 * Authentication ops.
 * The ops and the auth handle provide the interface to the authenticators.
 *
 * AUTH	*auth;
 * XDR	*xdrs;
 * struct opaque_auth verf;
 */
#define AUTH_NEXTVERF(auth)		\
		((*((auth)->ah_ops->ah_nextverf))(auth))
#define auth_nextverf(auth)		\
		((*((auth)->ah_ops->ah_nextverf))(auth))

#define AUTH_MARSHALL(auth, xdrs)	\
		((*((auth)->ah_ops->ah_marshal))(auth, xdrs))
#define auth_marshall(auth, xdrs)	\
		((*((auth)->ah_ops->ah_marshal))(auth, xdrs))

#define AUTH_VALIDATE(auth, verfp)	\
		((*((auth)->ah_ops->ah_validate))((auth), verfp))
#define auth_validate(auth, verfp)	\
		((*((auth)->ah_ops->ah_validate))((auth), verfp))

#define AUTH_REFRESH(auth)		\
		((*((auth)->ah_ops->ah_refresh))(auth))
#define auth_refresh(auth)		\
		((*((auth)->ah_ops->ah_refresh))(auth))

#define AUTH_DESTROY(auth)		\
		((*((auth)->ah_ops->ah_destroy))(auth))
#define auth_destroy(auth)		\
		((*((auth)->ah_ops->ah_destroy))(auth))


extern struct opaque_auth _null_auth;


/*
 * These are the various implementations of client side authenticators.
 */

/*
 * Unix style authentication
 * AUTH *authunix_create(machname, uid, gid, len, aup_gids)
 *	char *machname;
 *	int uid;
 *	int gid;
 *	int len;
 *	int *aup_gids;
 */
#ifdef _KERNEL
extern AUTH *authkern_create(void);		/* takes no parameters */
extern AUTH *authdes_create(char *, u_int, struct sockaddr_in *, des_block *,
			    struct ucred *);
#else
#ifdef _NO_PROTO
extern bool_t   xdr_opaque_auth();
extern int key_encryptsession();
extern int key_decryptsession();
extern int netname2user();
extern int netname2host();
extern int getnetname();
extern int user2netname();
extern int host2netname();
extern int key_gendes();
#else
extern AUTH *authunix_create(char *, int, int, int, u_int *);
extern AUTH *authunix_create_default(void);	/* takes no parameters */
extern AUTH *authnone_create(void);		/* takes no parameters */
extern AUTH *authdes_create(char *, u_int, struct sockaddr_in *, des_block *);

extern bool_t   xdr_opaque_auth(XDR *, struct opaque_auth *);
extern int key_encryptsession(char *, des_block *);
extern int key_decryptsession(char *, des_block *);
extern int netname2user(char *, int *, int *, int *, int *);
extern int netname2host(char *, char *, int);
extern int getnetname(char *);
extern int user2netname(char *, int, char *);
extern int host2netname(char *, char *, char *);
extern int key_gendes(des_block *);
#endif
#endif /* _KERNEL */

#define AUTH_NONE	0		/* no authentication */
#define	AUTH_NULL	0		/* backward compatibility */
#define	AUTH_UNIX	1		/* unix style (uid, gids) */
#define	AUTH_SHORT	2		/* short hand unix style */
#define AUTH_DES	3		/* des style (encrypted timestamps) */

#define AUTH_KERB5 	390003		/* Kerberos 5, service == none */
#define AUTH_KERB5I	390004		/* Kerberos 5, service == integrity */
#define AUTH_KERB5P	390005		/* Kerberos 5, service == privacy */

#endif

#endif /*!_RPC_AUTH_H*/
