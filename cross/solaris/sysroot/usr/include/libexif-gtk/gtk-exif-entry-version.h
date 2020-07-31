/* gtk-exif-entry-version.h
 *
 * Copyright � 2001 Lutz M�ller <lutz@users.sourceforge.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details. 
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef __GTK_EXIF_ENTRY_VERSION_H__
#define __GTK_EXIF_ENTRY_VERSION_H__

#include <libexif-gtk/gtk-exif-entry.h>

#define GTK_EXIF_TYPE_ENTRY_VERSION     (gtk_exif_entry_version_get_type())
#define GTK_EXIF_ENTRY_VERSION(o)       (GTK_CHECK_CAST((o),GTK_EXIF_TYPE_ENTRY_VERSION,GtkExifEntryVersion))
#define GTK_EXIF_ENTRY_VERSION_CLASS(k) (GTK_CHECK_CLASS_CAST((k),GTK_EXIF_TYPE_ENTRY_VERSION,GtkExifEntryVersionClass))
#define GTK_EXIF_IS_ENTRY_VERSION(o)    (GTK_CHECK_TYPE((o),GTK_EXIF_TYPE_ENTRY_VERSION))

typedef struct _GtkExifEntryVersion        GtkExifEntryVersion;
typedef struct _GtkExifEntryVersionPrivate GtkExifEntryVersionPrivate;
typedef struct _GtkExifEntryVersionClass   GtkExifEntryVersionClass;

struct _GtkExifEntryVersion
{
	GtkExifEntry parent;

	GtkExifEntryVersionPrivate *priv;
};

struct _GtkExifEntryVersionClass
{
	GtkExifEntryClass parent_class;
};

GtkType    gtk_exif_entry_version_get_type (void);
GtkWidget *gtk_exif_entry_version_new      (ExifEntry *entry);

#endif /* __GTK_EXIF_ENTRY_VERSION_H__ */