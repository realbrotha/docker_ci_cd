/*
 * Copyright 1998-2003 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _SYS_NDI_IMPLDEFS_H
#define	_SYS_NDI_IMPLDEFS_H

#pragma ident	"@(#)ndi_impldefs.h	1.24	03/05/01 SMI"

#include <sys/types.h>
#include <sys/param.h>
#include <sys/t_lock.h>
#include <sys/ddipropdefs.h>
#include <sys/devops.h>
#include <sys/autoconf.h>
#include <sys/mutex.h>
#include <vm/page.h>
#include <sys/ddi_impldefs.h>

#ifdef	__cplusplus
extern "C" {
#endif

/* event handle for callback management */
struct ndi_event_hdl {
	dev_info_t		*ndi_evthdl_dip;

	/*
	 * mutex that protect the handle and event defs
	 */
	kmutex_t		ndi_evthdl_mutex;

	/*
	 * mutex that just protects the callback list
	 */
	kmutex_t		ndi_evthdl_cb_mutex;

	ddi_iblock_cookie_t	ndi_evthdl_iblock_cookie;

	uint_t			ndi_evthdl_high_plevels;
	uint_t			ndi_evthdl_other_plevels;

	uint_t			ndi_evthdl_n_events;
	ndi_event_cookie_t 	*ndi_evthdl_cookie_list;
	ndi_event_hdl_t 	ndi_next_hdl;
};

/* prototypes needed by sunndi.c */
int ddi_prop_fm_encode_bytes(prop_handle_t *, void *data, uint_t);

int ddi_prop_fm_encode_ints(prop_handle_t *, void *data, uint_t);

int ddi_prop_fm_encode_int64(prop_handle_t *, void *data, uint_t);

int ddi_prop_int64_op(prop_handle_t *, uint_t, int64_t *);

int ddi_prop_update_common(dev_t, dev_info_t *, int, char *, void *, uint_t,
    int (*)(prop_handle_t *, void *, uint_t));

int ddi_prop_lookup_common(dev_t, dev_info_t *, uint_t, char *, void *,
    uint_t *, int (*)(prop_handle_t *, void *, uint_t *));

int ddi_prop_remove_common(dev_t, dev_info_t *, char *, int);
void ddi_prop_remove_all_common(dev_info_t *, int);

int ddi_prop_fm_encode_string(prop_handle_t *, void *, uint_t);

int ddi_prop_fm_encode_strings(prop_handle_t *, void *, uint_t);
int ddi_prop_fm_decode_strings(prop_handle_t *, void *, uint_t *);

/*
 * Internal configuration routines
 */
int i_ndi_config_node(dev_info_t *, ddi_node_state_t, uint_t);
int i_ndi_unconfig_node(dev_info_t *, ddi_node_state_t, uint_t);

/*
 * Obsolete interface, no longer used, to be removed.
 * Retained only for driver compatibility.
 */
void i_ndi_block_device_tree_changes(uint_t *);		/* obsolete */
void i_ndi_allow_device_tree_changes(uint_t);		/* obsolete */

/*
 * ndi_dev_is_auto_assigned_node: Return non-zero if the nodeid in dev
 * has been auto-assigned by the framework and should be auto-freed.
 * (Intended for use by the framework only.)
 */
int i_ndi_dev_is_auto_assigned_node(dev_info_t *);

/*
 * Get and set nodeclass and node attributes.
 * (Intended for ddi framework use only.)
 */
ddi_node_class_t i_ndi_get_node_class(dev_info_t *);
void i_ndi_set_node_class(dev_info_t *, ddi_node_class_t);

int i_ndi_get_node_attributes(dev_info_t *);
void i_ndi_set_node_attributes(dev_info_t *, int);

/*
 * Set nodeid .. not generally advisable.
 * (Intended for the ddi framework use only.)
 */
void i_ndi_set_nodeid(dev_info_t *, int);

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_NDI_IMPLDEFS_H */
