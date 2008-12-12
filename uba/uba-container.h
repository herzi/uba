/* This file is part of the universal business adapter
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
 *
 * Copyright (C) 2007  Sven Herzberg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#ifndef UBA_CONTAINER_H
#define UBA_CONTAINER_H

#include <gtk/gtksocket.h>

G_BEGIN_DECLS

typedef struct _UbaContainer        UbaContainer;
typedef struct _UbaContainerPrivate UbaContainerPrivate;
typedef struct _UbaContainerClass   UbaContainerClass;

#define UBA_TYPE_CONTAINER         (uba_container_get_type ())
#define UBA_CONTAINER(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), UBA_TYPE_CONTAINER, UbaContainer))
#define UBA_CONTAINER_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), UBA_TYPE_CONTAINER, UbaContainerClass))
#define UBA_IS_CONTAINER(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), UBA_TYPE_CONTAINER))
#define UBA_IS_CONTAINER_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), UBA_TYPE_CONTAINER))
#define UBA_CONTAINER_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), UBA_TYPE_CONTAINER, UbaContainerClass))

GType      uba_container_get_type (void);
GtkWidget* uba_container_new      (gchar const* service_name,
                                   gchar const* creator_path);

struct _UbaContainer {
        GtkSocket            base_instance;
        UbaContainerPrivate* _private;
};

struct _UbaContainerClass {
        GtkSocketClass       base_class;
};

G_END_DECLS

#endif /* !UBA_CONTAINER_H */
