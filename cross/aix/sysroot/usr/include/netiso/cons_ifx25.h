/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/netiso/cons_ifx25.h 1.5                     */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 1988,1991          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)46	1.5  src/bos/usr/include/netiso/cons_ifx25.h, sockinc, bos530 6/26/02 14:32:08 */

/*
 * 
 * COMPONENT_NAME: (SOCKET) Socket services
 * 
 * FUNCTIONS: 
 *
 * ORIGINS: 26 27 
 *
 * (C) COPYRIGHT International Business Machines Corp. 1988, 1989, 1991
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *****************************************************************/

#define MAX_HWADDR 	MAX_SNPALEN

#ifdef __cplusplus
struct file;
#endif

struct  ifx25com {
	struct  ifnet	ac_if;			/* network visible interface */
	u_char		ac_hwaddr[MAX_HWADDR];	/* hardware address */
	u_short		ac_hwlen;		/* length of hw address	*/
	u_long		ifType;			/* interface type */
};

struct	ifx25_softc {
	struct ifx25com	ifx25_com;
	struct  file *netfp;		/* file pointer for driver	*/
	u_short	ifx25_flags;		/* private flags		*/
	x25_devinfo_t iocinfo;		/* ddi info			*/
};

#define ifx25_if	ifx25_com.ac_if
#define ifx25_addr	ifx25_com.ac_hwaddr

