/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/* camel-data-wrapper.h : Abstract class for a data wrapper */

/*
 *
 * Author :
 *  Bertrand Guiheneuf <bertrand@helixcode.com>
 *
 * Copyright 1999, 2000 Ximian, Inc. (www.ximian.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */


#ifndef CAMEL_DATA_WRAPPER_H
#define CAMEL_DATA_WRAPPER_H 1

#ifdef __cplusplus
extern "C" {
#pragma }
#endif /* __cplusplus }*/

#include <glib.h>
#include <camel/camel-object.h>

#define CAMEL_DATA_WRAPPER_TYPE     (camel_data_wrapper_get_type ())
#define CAMEL_DATA_WRAPPER(obj)     (CAMEL_CHECK_CAST((obj), CAMEL_DATA_WRAPPER_TYPE, CamelDataWrapper))
#define CAMEL_DATA_WRAPPER_CLASS(k) (CAMEL_CHECK_CLASS_CAST ((k), CAMEL_DATA_WRAPPER_TYPE, CamelDataWrapperClass))
#define CAMEL_IS_DATA_WRAPPER(o)    (CAMEL_CHECK_TYPE((o), CAMEL_DATA_WRAPPER_TYPE))

struct _CamelDataWrapper
{
	CamelObject parent_object;
	struct _CamelDataWrapperPrivate *priv;
	
	CamelContentType *mime_type;
	CamelStream *stream;
	
	unsigned int offline:1;
	unsigned int rawtext:1;
};

typedef struct {
	CamelObjectClass parent_class;

	/* Virtual methods */
	void                (*set_mime_type)          (CamelDataWrapper *data_wrapper,
						       const gchar * mime_type);
	gchar *             (*get_mime_type)          (CamelDataWrapper *data_wrapper);
	CamelContentType *  (*get_mime_type_field)    (CamelDataWrapper *data_wrapper);
	void                (*set_mime_type_field)    (CamelDataWrapper *data_wrapper,
						       CamelContentType *mime_type_field);

	int                 (*write_to_stream)        (CamelDataWrapper *data_wrapper,
						       CamelStream *stream);

	int                 (*construct_from_stream)  (CamelDataWrapper *data_wrapper,
						       CamelStream *);

	gboolean            (*is_offline)             (CamelDataWrapper *data_wrapper);

} CamelDataWrapperClass;

/* Standard Camel function */
CamelType camel_data_wrapper_get_type (void);

/* public methods */
CamelDataWrapper *  camel_data_wrapper_new(void);
int                 camel_data_wrapper_write_to_stream          (CamelDataWrapper *data_wrapper,
								 CamelStream *stream);
void                camel_data_wrapper_set_mime_type            (CamelDataWrapper *data_wrapper,
								 const gchar *mime_type);
gchar *             camel_data_wrapper_get_mime_type            (CamelDataWrapper *data_wrapper);
CamelContentType *  camel_data_wrapper_get_mime_type_field      (CamelDataWrapper *data_wrapper);
void                camel_data_wrapper_set_mime_type_field      (CamelDataWrapper *data_wrapper,
								 CamelContentType *mime_type);

int                 camel_data_wrapper_construct_from_stream    (CamelDataWrapper *data_wrapper, CamelStream *stream);

gboolean            camel_data_wrapper_is_offline               (CamelDataWrapper *data_wrapper);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CAMEL_DATA_WRAPPER_H */