/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */

/* eel-gtk-extensions.h - interface for new functions that operate on
  			       gtk classes. Perhaps some of these should be
  			       rolled into gtk someday.

   Copyright (C) 1999, 2000, 2001 Eazel, Inc.

   The Gnome Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The Gnome Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the Gnome Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.

   Authors: John Sullivan <sullivan@eazel.com>
            Ramiro Estrugo <ramiro@eazel.com>
*/

#ifndef EEL_GTK_EXTENSIONS_H
#define EEL_GTK_EXTENSIONS_H

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gtk/gtkbutton.h>
#include <gtk/gtklabel.h>
#include <gtk/gtkmenu.h>
#include <gtk/gtkmenuitem.h>
#include <gtk/gtktreeview.h>
#include <gtk/gtkwindow.h>
#include <gtk/gtkviewport.h>
#include <eel/eel-gdk-extensions.h>

#define EEL_DEFAULT_POPUP_MENU_DISPLACEMENT 	2
#define EEL_STANDARD_CLOSE_WINDOW_CONTROL_KEY 	'w'

/* GtkButton */
GtkWidget*            eel_gtk_button_new_with_stock_icon              (const gchar	    *label,
								       const gchar	    *stock_id);
void                  eel_gtk_button_set_padding                      (GtkButton            *button,
								       int                   pad_amount);

/* signals */
guint                 eel_gtk_signal_connect_free_data                (GtkObject            *object,
								       const gchar          *name,
								       GtkSignalFunc         func,
								       gpointer              data);
guint                 eel_gtk_signal_connect_free_data_custom         (GtkObject            *object,
								       const gchar          *name,
								       GtkSignalFunc         func,
								       gpointer              data,
								       GtkDestroyNotify      destroy_func);
void                  eel_gtk_signal_connect_full_while_alive         (GtkObject            *object,
								       const gchar          *name,
								       GtkSignalFunc         func,
								       GtkCallbackMarshal    marshal,
								       gpointer              data,
								       GtkDestroyNotify      destroy_func,
								       gboolean              object_signal,
								       gboolean              after,
								       GtkObject            *alive_object);
void                  eel_gtk_signal_connect_while_realized           (GtkObject            *object,
								       const char           *name,
								       GtkSignalFunc         callback,
								       gpointer              callback_data,
								       GtkWidget            *realized_widget);

/* GtkWidget */
void                  eel_gtk_widget_set_shown                        (GtkWidget            *widget,
								       gboolean              shown);
gboolean              eel_point_in_allocation                         (const GtkAllocation  *allocation,
								       int                   x,
								       int                   y);
void                  eel_gtk_widget_set_font_by_name                 (GtkWidget            *widget,
								       const char           *font_name);
gboolean              eel_point_in_widget                             (GtkWidget            *widget,
								       int                   x,
								       int                   y);
void                  eel_gtk_widget_set_background_color             (GtkWidget            *widget,
								       const char           *color_spec);
void                  eel_gtk_widget_set_foreground_color             (GtkWidget            *widget,
								       const char           *color_spec);
GtkWidget *           eel_gtk_widget_find_windowed_ancestor           (GtkWidget            *widget);
PangoFontDescription *eel_gtk_get_system_font                         (void);
void                  eel_gtk_widget_get_button_event_location        (GtkWidget            *widget,
								       const GdkEventButton *event,
								       int                  *x,
								       int                  *y);
void                  eel_gtk_widget_get_motion_event_location        (GtkWidget            *widget,
								       const GdkEventMotion *event,
								       int                  *x,
								       int                  *y);

/* GtkContainer */
GtkWidget *           eel_gtk_container_get_first_child               (GtkContainer         *container);
void                  eel_gtk_container_foreach_deep                  (GtkContainer         *container,
								       GtkCallback           callback,
								       gpointer              callback_data);

/* GtkWindow */
void                  eel_gtk_window_set_initial_geometry             (GtkWindow            *window,
								       EelGdkGeometryFlags   geometry_flags,
								       int                   left,
								       int                   top,
								       guint                 width,
								       guint                 height);
void                  eel_gtk_window_set_initial_geometry_from_string (GtkWindow            *window,
								       const char           *geometry_string,
								       guint                 minimum_width,
								       guint                 minimum_height,
								       gboolean		     ignore_position);
void                  eel_gtk_window_set_up_close_accelerator         (GtkWindow            *window);
gboolean              eel_gtk_window_event_is_close_accelerator       (GtkWindow            *window,
								       GdkEventKey          *event);
char *                eel_gtk_window_get_geometry_string              (GtkWindow            *window);


/* GtkMenu and GtkMenuItem */
char *                eel_truncate_text_for_menu_item                 (const char           *text);
void                  eel_pop_up_context_menu                         (GtkMenu              *menu,
								       gint16                offset_x,
								       gint16                offset_y,
								       GdkEventButton       *event);
GtkMenuItem *         eel_gtk_menu_append_separator                   (GtkMenu              *menu);
GtkMenuItem *         eel_gtk_menu_insert_separator                   (GtkMenu              *menu,
								       int                   index);
void                  eel_gtk_menu_set_item_visibility                (GtkMenu              *menu,
								       int                   index,
								       gboolean              visible);

/* GtkLabel */
void                  eel_gtk_label_make_bold                         (GtkLabel             *label);
void                  eel_gtk_label_set_scale                         (GtkLabel             *label,
								       double                scale_factor);
void                  eel_gtk_label_set_drop_shadow_color             (GtkLabel             *label,
								       guint32               color);
void                  eel_gtk_label_set_drop_shadow_offset            (GtkLabel             *label,
								       gint                  offset); 
/* GtkAdjustment */
void                  eel_gtk_adjustment_set_value                    (GtkAdjustment        *adjustment,
								       float                 value);
void                  eel_gtk_adjustment_clamp_value                  (GtkAdjustment        *adjustment);

/* Client-side drawing with Pango */
PangoContext *        eel_gtk_widget_get_pango_ft2_context            (GtkWidget            *widget);

/* GtkTreeView */
gboolean              eel_gtk_tree_view_cell_is_completely_visible    (GtkTreeView          *tree_view,
								       GtkTreePath          *path,
								       GtkTreeViewColumn    *column);
void                  eel_gtk_tree_view_set_activate_on_single_click  (GtkTreeView               *tree_view,
								       gboolean                   should_activate);

/* GtkViewport */
gboolean              eel_gtk_viewport_get_visible_rect               (GtkViewport          *viewport, 
								       GdkRectangle         *rect);

void                  eel_gtk_viewport_scroll_to_rect                 (GtkViewport          *viewport,
								       GdkRectangle         *rect);

#endif /* EEL_GTK_EXTENSIONS_H */
