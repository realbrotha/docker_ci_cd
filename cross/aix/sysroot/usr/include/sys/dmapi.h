/* IBM_PROLOG_BEGIN_TAG                                                   */
/* This is an automatically generated prolog.                             */
/*                                                                        */
/* bos530 src/bos/usr/ccs/lib/libxdsm/dmapi.h 1.3                         */
/*                                                                        */
/* Licensed Materials - Property of IBM                                   */
/*                                                                        */
/* Restricted Materials of IBM                                            */
/*                                                                        */
/* (C) COPYRIGHT International Business Machines Corp. 2000,2002          */
/* All Rights Reserved                                                    */
/*                                                                        */
/* US Government Users Restricted Rights - Use, duplication or            */
/* disclosure restricted by GSA ADP Schedule Contract with IBM Corp.      */
/*                                                                        */
/* IBM_PROLOG_END_TAG                                                     */
/* @(#)63  1.3  src/bos/usr/ccs/lib/libxdsm/dmapi.h, syskdm, bos530 10/4/02 13:30:15 */

/*
 * Copyright (c) 1998 VERITAS Software Corporation.  ALL RIGHTS RESERVED.
 * UNPUBLISHED -- RIGHTS RESERVED UNDER THE COPYRIGHT
 * LAWS OF THE UNITED STATES.  USE OF A COPYRIGHT NOTICE
 * IS PRECAUTIONARY ONLY AND DOES NOT IMPLY PUBLICATION
 * OR DISCLOSURE.
 *
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND
 * TRADE SECRETS OF VERITAS SOFTWARE.  USE, DISCLOSURE,
 * OR REPRODUCTION IS PROHIBITED WITHOUT THE PRIOR
 * EXPRESS WRITTEN PERMISSION OF VERITAS SOFTWARE.
 *
 *	       RESTRICTED RIGHTS LEGEND
 * USE, DUPLICATION, OR DISCLOSURE BY THE GOVERNMENT IS
 * SUBJECT TO RESTRICTIONS AS SET FORTH IN SUBPARAGRAPH
 * (C) (1) (ii) OF THE RIGHTS IN TECHNICAL DATA AND
 * COMPUTER SOFTWARE CLAUSE AT DFARS 252.227-7013.
 *	       VERITAS SOFTWARE
 * 1600 PLYMOUTH STREET, MOUNTAIN VIEW, CA 94043
 */

#ifndef _DMAPI_H
#define _DMAPI_H

#include <sys/fs/dmapi.h>
#include <sys/fs/kdm_dmi.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int	dm_clear_inherit(dm_sessid_t, void *, size_t,
				 dm_token_t, dm_attrname_t *);
extern int	dm_create_by_handle(dm_sessid_t, void *, size_t, dm_token_t,
				    void *, size_t, char *);
extern int	dm_create_session(dm_sessid_t, char *, dm_sessid_t *);
extern int	dm_create_userevent(dm_sessid_t, size_t, void *, dm_token_t *);
extern int	dm_destroy_session(dm_sessid_t);
extern int	dm_event_query(dm_sessid_t, dm_token_t, dm_eventquery_t,
			       dm_size_t *);
extern int	dm_find_eventmsg(dm_sessid_t, dm_token_t, size_t,
				 void *, size_t *);
extern int	dm_get_allocinfo(dm_sessid_t, void *, size_t, dm_token_t,
				 dm_off_t *, u_int, dm_extent_t *, u_int *);
extern int	dm_get_bulkall(dm_sessid_t, void *, size_t, dm_token_t,
			       u_int, dm_attrname_t *, dm_attrloc_t *, size_t,
			       void *, size_t *);
extern int	dm_get_bulkattr(dm_sessid_t, void *, size_t, dm_token_t,
				u_int, dm_attrloc_t *, size_t,
				void *, size_t *);
extern int	dm_get_dirattrs(dm_sessid_t, void *, size_t, dm_token_t,
				u_int, dm_attrloc_t *, size_t, void *,
				size_t *);
extern int	dm_init_attrloc(dm_sessid_t, void *, size_t, dm_token_t,
				dm_attrloc_t *);
extern int	dm_get_config(void *, size_t, dm_config_t, dm_size_t *);
extern int	dm_get_config_events(void *, size_t, u_int, dm_eventset_t *,
				     u_int *);
extern int	dm_get_dmattr(dm_sessid_t, void *, size_t, dm_token_t,
			      dm_attrname_t *, size_t, void *, size_t *);
extern int	dm_get_eventlist(dm_sessid_t, void *, size_t, dm_token_t,
				 u_int, dm_eventset_t *, u_int	*);
extern int	dm_get_events(dm_sessid_t, u_int, u_int, size_t, void *,
			      size_t *);
extern int	dm_get_fileattr(dm_sessid_t, void *, size_t, dm_token_t,
				u_int, dm_stat_t *);
extern int	dm_get_mountinfo(dm_sessid_t, void *, size_t, dm_token_t,
				 size_t, void *, size_t *);
extern int	dm_get_region(dm_sessid_t, void *, size_t, dm_token_t,
			      u_int, dm_region_t *, u_int *);
extern int	dm_getall_disp(dm_sessid_t, size_t, void *, size_t *);
extern int	dm_getall_dmattr(dm_sessid_t, void *, size_t, dm_token_t,
				 size_t, void *, size_t *);
extern int	dm_getall_inherit(dm_sessid_t, void *, size_t, dm_token_t,
				  u_int, dm_inherit_t *, u_int *);
extern int	dm_getall_sessions(u_int, dm_sessid_t *, u_int *);
extern int	dm_getall_tokens(dm_sessid_t, u_int, dm_token_t *, u_int *);
extern int	dm_handle_cmp(void *, size_t, void *, size_t);
extern dm_boolean_t dm_handle_is_valid(void *, size_t);
extern u_int	dm_handle_hash(void *, size_t);
extern int	dm_handle_to_fshandle(void *, size_t, void **, size_t *);
extern int	dm_handle_to_path(void *, size_t, void *, size_t,
				  size_t, char *, size_t *);
extern int	dm_init_service(char **);
extern int	dm_mkdir_by_handle(dm_sessid_t, void *, size_t, dm_token_t,
				   void *, size_t, char *);
extern int	dm_move_event(dm_sessid_t, dm_token_t, dm_sessid_t,
			      dm_token_t *);
extern int	dm_fd_to_handle(int, void **, size_t *);
extern int	dm_path_to_fshandle(char *, void **, size_t *);
extern int	dm_path_to_handle(char *, void **, size_t *);
extern void	dm_handle_free(void *, size_t);
extern int	dm_punch_hole(dm_sessid_t, void *, size_t, dm_token_t,
			      dm_off_t, dm_size_t);
extern int	dm_probe_hole(dm_sessid_t, void *, size_t, dm_token_t,
			      dm_off_t, dm_size_t, dm_off_t *, dm_size_t *);
extern int	dm_query_right(dm_sessid_t, void *, size_t, dm_token_t,
			       dm_right_t *);
extern int	dm_query_session(dm_sessid_t, size_t, void *, size_t *);
extern dm_ssize_t dm_read_invis(dm_sessid_t, void *, size_t, dm_token_t,
				dm_off_t, dm_size_t, void *);
extern dm_ssize_t dm_write_invis(dm_sessid_t, void *, size_t, dm_token_t,
				 int, dm_off_t, dm_size_t, void *);
extern int	dm_release_right(dm_sessid_t, void *, size_t, dm_token_t);
extern int	dm_remove_dmattr(dm_sessid_t, void *, size_t, dm_token_t,
				 int, dm_attrname_t *);
extern int	dm_request_right(dm_sessid_t, void *, size_t, dm_token_t,
				 u_int, dm_right_t);
extern int	dm_respond_event(dm_sessid_t, dm_token_t, dm_response_t,
				 int, size_t, void *);
extern int	dm_send_msg(dm_sessid_t, dm_msgtype_t, size_t, void *);
extern int	dm_set_disp(dm_sessid_t, void *, size_t, dm_token_t,
			    dm_eventset_t *, u_int);
extern int	dm_set_dmattr(dm_sessid_t, void *, size_t, dm_token_t,
			      dm_attrname_t *, int, size_t, void *);
extern int	dm_set_eventlist(dm_sessid_t, void *, size_t, dm_token_t,
				 dm_eventset_t *, u_int);
extern int	dm_set_fileattr(dm_sessid_t, void *, size_t, dm_token_t,
				u_int, dm_fileattr_t *);
extern int	dm_set_inherit(dm_sessid_t, void *, size_t, dm_token_t,
			       dm_attrname_t *, u_int);
extern int	dm_set_region(dm_sessid_t, void *, size_t, dm_token_t,
			      u_int, dm_region_t *, dm_boolean_t *);
extern int	dm_set_return_on_destroy(dm_sessid_t, void *, size_t,
					 dm_token_t,  dm_attrname_t *,
					 dm_boolean_t);
extern int	dm_symlink_by_handle(dm_sessid_t, void *, size_t, dm_token_t,
				     void *, size_t, char *, char *);
extern int	dm_sync_by_handle(dm_sessid_t, void *, size_t, dm_token_t);
extern int	dm_handle_to_fsid(void *, size_t, dm_fsid_t *);
extern int	dm_handle_to_igen(void *, size_t, dm_igen_t *);
extern int	dm_handle_to_ino(void *, size_t, dm_ino_t *);
extern int	dm_make_handle(dm_fsid_t, dm_ino_t, dm_igen_t, void **,
			       size_t *);
extern int	dm_make_fshandle(dm_fsid_t, void **, size_t *);

/*
 * Stubs for non-supported optional interfaces
 */

extern int	dm_upgrade_right(dm_sessid_t, void *, size_t, dm_token_t);
extern int	dm_downgrade_right(dm_sessid_t, void *, size_t, dm_token_t);
extern int	dm_pending(dm_sessid_t, dm_token_t, dm_timestruct_t *);
extern int	dm_obj_ref_hold(dm_sessid_t, dm_token_t, void *, size_t);
extern int	dm_obj_ref_rele(dm_sessid_t, dm_token_t, void *, size_t);
extern int	dm_obj_ref_query(dm_sessid_t, dm_token_t, void *, size_t);

#ifdef __cplusplus
}
#endif

#endif	/* _DMAPI_H */
