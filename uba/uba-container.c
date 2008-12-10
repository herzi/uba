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

#include "uba-container.h"

struct _UbaContainerPrivate {
        gchar* bus_name;
};

#define PRIV(i) ((UbaContainer*)(i))->_private

G_DEFINE_TYPE (UbaContainer, uba_container, GTK_TYPE_SOCKET);

static void
uba_container_init (UbaContainer* self)
{
        PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self,
                                                   UBA_TYPE_CONTAINER,
                                                   UbaContainerPrivate);
}

static void
container_finalize (GObject* object)
{
        g_free (PRIV (object)->bus_name);

        G_OBJECT_CLASS (uba_container_parent_class)->finalize (object);
}

static void
container_get_property (GObject   * object,
                        guint       prop_id,
                        GValue    * value,
                        GParamSpec* pspec)
{
        switch (prop_id) {
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
                break;
        }
}

static void
container_set_property (GObject     * object,
                        guint         prop_id,
                        GValue const* value,
                        GParamSpec  * pspec)
{
        switch (prop_id) {
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
                break;
        }
}

static void
uba_container_class_init (UbaContainerClass* self_class)
{
        GObjectClass* object_class = G_OBJECT_CLASS (self_class);

        object_class->finalize     = container_finalize;
        object_class->get_property = container_get_property;
        object_class->set_property = container_set_property;

        g_type_class_add_private (self_class, sizeof (UbaContainerPrivate));
}

/* Public API Implementation */

GtkWidget*
uba_container_new (void)
{
        return g_object_new (UBA_TYPE_CONTAINER,
                             NULL);
}

