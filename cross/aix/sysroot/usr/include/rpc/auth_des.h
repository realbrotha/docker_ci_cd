/* static char sccsid[] = "@(#)64  1.7  src/bos/usr/include/rpc/auth_des.h, libcrpc, bos530 5/12/99 10:57:10"; */
/*
 *   COMPONENT_NAME: LIBCRPC
 *
 *   FUNCTIONS: 
 *
 *   ORIGINS: 24
 *
 * Copyright (c) 1990 by Sun Microsystems, Inc.
 *
 */

/*	@(#)auth_des.h	1.3 90/07/17 4.1NFSSRC SMI	*/

/*
 * auth_des.h, Protocol for DES style authentication for RPC
 */

#ifdef _AIX_TIRPC
#include <tirpc/rpc/auth_des.h>
#else

#ifndef _RPC_AUTH_DES_H
#define	_RPC_AUTH_DES_H

/*
 * There are two kinds of "names": fullnames and nicknames
 */
enum authdes_namekind {
	ADN_FULLNAME, 
	ADN_NICKNAME
};

/*
 * A fullname contains the network name of the client, 
 * a conversation key and the window
 */
struct authdes_fullname {
	char *name;		/* network name of client, up to MAXNETNAMELEN */
	des_block key;		/* conversation key */
#ifndef __64BIT__
	u_long window;		/* assiciated window */
#else
	u_int window;
#endif
};


/*
 * A credential 
 */
struct authdes_cred {
	enum authdes_namekind adc_namekind;
	struct authdes_fullname adc_fullname;
#ifndef __64BIT__
	u_long adc_nickname;
#else
	u_int adc_nickname;
#endif
};



/*
 * A des authentication verifier 
 */
struct authdes_verf {
	union {
		struct timeval adv_ctime;	/* clear time */
		des_block adv_xtime;		/* crypt time */
	} adv_time_u;
#ifndef __64BIT__
	u_long adv_int_u;
#else
	u_int adv_int_u;
#endif
};

/*
 * des authentication verifier: client variety
 *
 * adv_timestamp is the current time.
 * adv_winverf is the credential window + 1.
 * Both are encrypted using the conversation key.
 */
#define adv_timestamp	adv_time_u.adv_ctime
#define adv_xtimestamp	adv_time_u.adv_xtime
#define adv_winverf	adv_int_u

/*
 * des authentication verifier: server variety
 *
 * adv_timeverf is the client's timestamp + client's window
 * adv_nickname is the server's nickname for the client.
 * adv_timeverf is encrypted using the conversation key.
 */
#define adv_timeverf	adv_time_u.adv_ctime
#define adv_xtimeverf	adv_time_u.adv_xtime
#define adv_nickname	adv_int_u

#endif /*!_RPC_AUTH_DES_H*/

#endif /*!_AIX_TIRPC*/

