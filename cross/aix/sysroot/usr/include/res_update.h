/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/include/res_update.h 1.1                            */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000               */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)92	1.1  src/bos/usr/include/res_update.h, sockinc, bos530 1/23/00 22:13:24 */
/*
 * Copyright (c) 1999 by Internet Software Consortium, Inc.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL INTERNET SOFTWARE
 * CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#ifndef __RES_UPDATE_H
#define __RES_UPDATE_H

#include <sys/types.h>
#include <arpa/nameser.h>
#include <isc/list.h>
#include <resolv.h>

/*
 * This RR-like structure is particular to UPDATE.
 */
struct ns_updrec {
	LINK(struct ns_updrec) r_link, r_glink;
	ns_sect		r_section;	/* ZONE/PREREQUISITE/UPDATE */
	char *		r_dname;	/* owner of the RR */
	ns_class	r_class;	/* class number */
	ns_type		r_type;		/* type number */
	u_int32_t	r_ttl;		/* time to live */
	u_char *	r_data;		/* rdata fields as text string */
	u_int		r_size;		/* size of r_data field */
	int		r_opcode;	/* type of operation */
	/* following fields for private use by the resolver/server routines */
	struct databuf *r_dp;		/* databuf to process */
	struct databuf *r_deldp;	/* databuf's deleted/overwritten */
	u_int		r_zone;		/* zone number on server */
};
typedef struct ns_updrec ns_updrec;
typedef	LIST(ns_updrec)	ns_updque;

int		res_mkupdate(ns_updrec *, u_char *, int);
int		res_update(ns_updrec *);
ns_updrec *	res_mkupdrec(int, const char *, u_int, u_int, __ulong32_t);
void		res_freeupdrec(ns_updrec *);
int		res_nmkupdate(struct __res_state *, ns_updrec *, u_char *, int);
int		res_nupdate(struct __res_state *, ns_updrec *, ns_tsig_key *);

#endif /*__RES_UPDATE_H*/
