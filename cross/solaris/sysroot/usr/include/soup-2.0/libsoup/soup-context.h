/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * soup-context.h: Asyncronous Callback-based HTTP Request Queue.
 *
 * Authors:
 *      Alex Graveley (alex@ximian.com)
 *
 * Copyright (C) 2000-2002, Ximian, Inc.
 */

#ifndef SOUP_CONTEXT_H
#define SOUP_CONTEXT_H 1

#include <glib.h>
#include <libsoup/soup-uri.h>

typedef struct _SoupContext SoupContext;

typedef struct _SoupConnection SoupConnection;

typedef enum {
	SOUP_CONNECT_ERROR_NONE,
	SOUP_CONNECT_ERROR_ADDR_RESOLVE,
	SOUP_CONNECT_ERROR_NETWORK
} SoupConnectErrorCode;

typedef void (*SoupConnectCallbackFn) (SoupContext          *ctx,
				       SoupConnectErrorCode  err,
				       SoupConnection       *conn, 
				       gpointer              user_data);

typedef gpointer SoupConnectId;

SoupContext   *soup_context_get               (const gchar          *uri);

SoupContext   *soup_context_from_uri          (SoupUri              *suri);

void           soup_context_ref               (SoupContext          *ctx);

void           soup_context_unref             (SoupContext          *ctx);

SoupConnectId  soup_context_get_connection    (SoupContext          *ctx,
					       SoupConnectCallbackFn cb,
					       gpointer              user_data);

void           soup_context_cancel_connect    (SoupConnectId         tag);

const SoupUri *soup_context_get_uri           (SoupContext          *ctx);


GIOChannel    *soup_connection_get_iochannel  (SoupConnection       *conn);

SoupContext   *soup_connection_get_context    (SoupConnection       *conn);

void           soup_connection_set_keep_alive (SoupConnection       *conn, 
					       gboolean              keepalive);

gboolean       soup_connection_is_keep_alive  (SoupConnection       *conn);

void           soup_connection_set_used       (SoupConnection       *conn);
gboolean       soup_connection_is_new         (SoupConnection       *conn);

void           soup_connection_release        (SoupConnection       *conn);


void           soup_connection_purge_idle     (void);


void           soup_context_preauthenticate   (SoupContext          *ctx,
					       const char           *header);
					  
#endif /*SOUP_CONTEXT_H*/
