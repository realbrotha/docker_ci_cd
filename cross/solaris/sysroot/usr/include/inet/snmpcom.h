/*
 * Copyright 1992,1997,2001-2003 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_INET_SNMPCOM_H
#define	_INET_SNMPCOM_H

#pragma ident	"@(#)snmpcom.h	1.11	03/02/27 SMI"

#ifdef	__cplusplus
extern "C" {
#endif

#if defined(_KERNEL) && defined(__STDC__)

extern int	snmp_append_data(mblk_t *mpdata, char *blob, int len);
extern int	snmp_append_data2(mblk_t *mpdata, mblk_t **last_mpp,
		    char *blob, int len);

extern boolean_t	snmpcom_req(queue_t *q, mblk_t *mp, pfi_t setfn,
			    pfi_t getfn, cred_t *cr);

#endif	/* defined(_KERNEL) && defined(__STDC__) */

#ifdef	__cplusplus
}
#endif

#endif	/* _INET_SNMPCOM_H */
