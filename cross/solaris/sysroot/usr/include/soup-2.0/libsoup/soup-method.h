/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * soup-method.h: HTTP Method defines and related processing.
 *
 * Authors:
 *      Alex Graveley (alex@ximian.com)
 *
 * Copyright (C) 2001-2002, Ximian, Inc.
 */

#ifndef SOUP_METHOD_H
#define SOUP_METHOD_H 1

#define SOUP_METHOD_POST      "POST"
#define SOUP_METHOD_GET       "GET"
#define SOUP_METHOD_HEAD      "HEAD"
#define SOUP_METHOD_OPTIONS   "OPTIONS"
#define SOUP_METHOD_PUT       "PUT"
#define SOUP_METHOD_MOVE      "MOVE"
#define SOUP_METHOD_COPY      "COPY"
#define SOUP_METHOD_DELETE    "DELETE"
#define SOUP_METHOD_TRACE     "TRACE"
#define SOUP_METHOD_CONNECT   "CONNECT"
#define SOUP_METHOD_MKCOL     "MKCOL"
#define SOUP_METHOD_PROPPATCH "PROPPATCH"
#define SOUP_METHOD_PROPFIND  "PROPFIND"
#define SOUP_METHOD_PATCH     "PATCH"
#define SOUP_METHOD_LOCK      "LOCK"
#define SOUP_METHOD_UNLOCK    "UNLOCK"

typedef enum {
	SOUP_METHOD_ID_UNKNOWN = 0,
	SOUP_METHOD_ID_POST,
	SOUP_METHOD_ID_GET,
	SOUP_METHOD_ID_HEAD,
	SOUP_METHOD_ID_OPTIONS,
	SOUP_METHOD_ID_PUT,
	SOUP_METHOD_ID_MOVE,
	SOUP_METHOD_ID_COPY,
	SOUP_METHOD_ID_DELETE,
	SOUP_METHOD_ID_TRACE,
	SOUP_METHOD_ID_CONNECT,
	SOUP_METHOD_ID_MKCOL,
	SOUP_METHOD_ID_PROPPATCH,
	SOUP_METHOD_ID_PROPFIND,
	SOUP_METHOD_ID_PATCH,
	SOUP_METHOD_ID_LOCK,
	SOUP_METHOD_ID_UNLOCK
} SoupMethodId;

SoupMethodId soup_method_get_id (const char *method);

#endif /* SOUP_METHOD_H */
