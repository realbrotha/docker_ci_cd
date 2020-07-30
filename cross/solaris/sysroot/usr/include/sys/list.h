/*
 * Copyright 2006 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef	_SYS_LIST_H
#define	_SYS_LIST_H

#pragma ident	"@(#)list.h	1.4	06/03/10 SMI"

#include <sys/list_impl.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct list_node list_node_t;
typedef struct list list_t;

void list_create(list_t *, size_t, size_t);
void list_destroy(list_t *);

void list_insert_after(list_t *, void *, void *);
void list_insert_before(list_t *, void *, void *);
void list_insert_head(list_t *, void *);
void list_insert_tail(list_t *, void *);
void list_remove(list_t *, void *);
void list_move_tail(list_t *, list_t *);

void *list_head(list_t *);
void *list_tail(list_t *);
void *list_next(list_t *, void *);
void *list_prev(list_t *, void *);

int list_link_active(list_node_t *);
int list_is_empty(list_t *);

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_LIST_H */
