/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */
/*
   Copyright (C) 2000 CodeFactory AB
   Copyright (C) 2000 Jonas Borgstr�m <jonas@codefactory.se>
   Copyright (C) 2000 Anders Carlsson <andersca@codefactory.se>
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.
*/

#ifndef __HTMLEVENT_H__
#define __HTMLEVENT_H__

#include <libgtkhtml/view/htmlview.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

void     html_event_mouse_move     (HtmlView *view, GdkEventMotion *event);
void     html_event_button_press   (HtmlView *view, GdkEventButton *button);
void     html_event_button_release (HtmlView *view, GdkEventButton *event);
void     html_event_activate       (HtmlView *view);
gboolean html_event_key_press      (HtmlView *view, GdkEventKey *event);

HtmlBox *html_event_find_root_box (HtmlBox *self, gint x, gint y);

G_END_DECLS

#endif /* __HTMLEVENT_H__ */
