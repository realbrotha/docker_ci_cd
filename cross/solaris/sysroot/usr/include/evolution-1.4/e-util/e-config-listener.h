/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
 * Configuration component listener
 *
 * Author:
 *   Rodrigo Moya <rodrigo@ximian.com>
 *
 * Copyright 2002, Ximian, Inc.
 */

#ifndef __E_CONFIG_LISTENER_H__
#define __E_CONFIG_LISTENER_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define E_CONFIG_LISTENER_TYPE        (e_config_listener_get_type ())
#define E_CONFIG_LISTENER(o)          (G_TYPE_CHECK_INSTANCECAST ((o), E_CONFIG_LISTENER_TYPE, EConfigListener))
#define E_CONFIG_LISTENER_CLASS(k)    (G_TYPE_CHECK_CLASS_CAST((k), E_CONFIG_LISTENER_TYPE, EConfigListenerClass))
#define E_IS_CONFIG_LISTENER(o)       (G_TYPE_CHECK_INSTANCE_TYPE ((o), E_CONFIG_LISTENER_TYPE))
#define E_IS_CONFIG_LISTENER_CLASS(k) (GT_TYPE_CHECK_CLASS_TYPE ((k), E_CONFIG_LISTENER_TYPE))

typedef struct _EConfigListenerPrivate EConfigListenerPrivate;

typedef struct {
	GObject object;
	EConfigListenerPrivate *priv;
} EConfigListener;

typedef struct {
	GObjectClass parent_class;

	void (* key_changed) (EConfigListener *cl, const char *key);
} EConfigListenerClass;

GType                 e_config_listener_get_type (void);
EConfigListener      *e_config_listener_new (void);

gboolean              e_config_listener_get_boolean (EConfigListener *cl, const char *key);
gboolean              e_config_listener_get_boolean_with_default (EConfigListener *cl,
								  const char *key,
								  gboolean def,
								  gboolean *used_default);
float                 e_config_listener_get_float (EConfigListener *cl, const char *key);
float                 e_config_listener_get_float_with_default (EConfigListener *cl,
								const char *key,
								float def,
								gboolean *used_default);
long                  e_config_listener_get_long (EConfigListener *cl, const char *key);
long                  e_config_listener_get_long_with_default (EConfigListener *cl,
							       const char *key,
							       long def,
							       gboolean *used_default);
char                 *e_config_listener_get_string (EConfigListener *cl, const char *key);
char                 *e_config_listener_get_string_with_default (EConfigListener *cl,
								 const char *key,
								 const char *def,
								 gboolean *used_default);
void                  e_config_listener_set_boolean (EConfigListener *cl,
						     const char *key,
						     gboolean value);
void                  e_config_listener_set_float (EConfigListener *cl,
						   const char *key,
						   float value);
void                  e_config_listener_set_long (EConfigListener *cl,
						  const char *key,
						  long value);
void                  e_config_listener_set_string (EConfigListener *cl,
						    const char *key,
						    const char *value);

void                  e_config_listener_remove_value (EConfigListener *cl,
						      const char *key);
void                  e_config_listener_remove_dir (EConfigListener *cl,
						    const char *dir);

G_END_DECLS

#endif
