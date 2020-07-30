/*
 * Copyright 1992,1997-1998,2002 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_AFLT_H
#define	_SYS_AFLT_H

#pragma ident	"@(#)aflt.h	1.6	02/03/01 SMI"

#include <sys/dditypes.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Possible values of fault type
 */
#define	AFLT_ECC	1
#define	AFLT_SX		2
#define	AFLT_SX_VRFY	3

/*
 * Arg which is passed to an ECC async handler to specify the error
 * (For fault type AFLT_ECC)
 */
struct ecc_handler_args {
	uint_t e_uncorrectable;	/* true if uncorrectable error */
	uint_t e_addrhi;	/* most significant bits of address */
	uint_t e_addrlo;	/* least significant bits of address */
};


/*
 * Structure to hold state about each registered handler.
 */
struct aflt_cookie {
	int handler_type;
	void *cookie;
};

/*
 * Return values for asynchronous fault support routines
 */

#define	AFLT_SUCCESS		0
#define	AFLT_NOTSUPPORTED	1
#define	AFLT_FAILURE		2

/*
 * Return values for async fault handler
 */

#define	AFLT_HANDLED	0
#define	AFLT_NOTHANDLED	1

#ifdef	__STDC__

extern int aflt_get_iblock_cookie(dev_info_t *, int, ddi_iblock_cookie_t *);
extern int aflt_add_handler(dev_info_t *, int, void **,
    int (*)(void *, void *), void *);
extern int aflt_remove_handler(void *);

#else	/* __STDC__ */

extern int aflt_get_iblock_cookie();
extern int aflt_add_handler();
extern int aflt_remove_handler();

#endif	/* __STDC__ */

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_AFLT_H */
