/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/ccs/lib/libpam/security/pam_modules.h 1.2           */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000,2001          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* $XConsortium: pam_modules.h /main/5 1996/05/09 04:25:54 drk $ */
/*
 * Copyright (c) 1992-1995, by Sun Microsystems, Inc.
 * All rights reserved.
 */


#ifndef	_PAM_MODULES_H
#define	_PAM_MODULES_H

#ifndef _PAM_APPL_H
#include <security/pam_appl.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern int
pam_sm_authenticate(
	pam_handle_t	*pamh,
	int	flags,
	int	argc,
	const char	**argv);

extern int
pam_sm_setcred(
	pam_handle_t	*pamh,
	int	flags,
	int	argc,
	const char	**argv);

extern int
pam_sm_acct_mgmt(
	pam_handle_t	*pamh,
	int	flags,
	int	argc,
	const char	**argv);

extern int
pam_sm_open_session(
	pam_handle_t	*pamh,
	int	flags,
	int	argc,
	const char	**argv);

extern int
pam_sm_close_session(
	pam_handle_t	*pamh,
	int	flags,
	int	argc,
	const char	**argv);

/*
 * Be careful - there are flags defined for pam_chauthtok() in
 * pam_appl.h also.
 */
#define	PAM_PRELIM_CHECK	1
#define	PAM_UPDATE_AUTHTOK	2

#define	PAM_REP_DEFAULT	0x0
#define	PAM_REP_FILES	0x01
#define	PAM_REP_NIS	0x02
#define	PAM_REP_NISPLUS	0x04
#define	PAM_OPWCMD	0x08	/* for nispasswd, yppasswd */
#define	IS_FILES(x)	((x & PAM_REP_FILES) == PAM_REP_FILES)
#define	IS_NIS(x)	((x & PAM_REP_NIS) == PAM_REP_NIS)
#define	IS_NISPLUS(x)	((x & PAM_REP_NISPLUS) == PAM_REP_NISPLUS)
#define	IS_OPWCMD(x)	((x & PAM_OPWCMD) == PAM_OPWCMD)

extern int
pam_sm_chauthtok(
	pam_handle_t	*pamh,
	int		flags,
	int		argc,
	const char	**argv);

#ifdef __cplusplus
}
#endif

#endif	/* _PAM_MODULES_H */
