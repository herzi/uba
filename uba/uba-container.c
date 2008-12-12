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

#include <dbus/dbus-glib.h>

#include "uba-creator-introspection.h"

enum {
        PROP_0,
        PROP_BUS_NAME,
        PROP_CREATOR_PATH
};

struct _UbaContainerPrivate {
        gchar* bus_name;
        gchar* creator_path;

        gchar* plug_path;

        DBusGProxy* proxy;
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
container_constructed (GObject* object)
{
        DBusGConnection* bus;
        GError         * error = NULL;

        g_return_if_fail (PRIV (object)->bus_name);
        g_return_if_fail (PRIV (object)->creator_path);
        g_return_if_fail (!PRIV (object)->proxy);

        /* FIXME: add error check */
        bus = dbus_g_bus_get (DBUS_BUS_SESSION, NULL);

        PRIV (object)->proxy = dbus_g_proxy_new_for_name (bus,
                                                          PRIV (object)->bus_name,
                                                          PRIV (object)->creator_path,
                                                          "eu.adeal.uba.creator");
        eu_adeal_uba_creator_get_instance (PRIV (object)->proxy,
                                           &PRIV (object)->plug_path,
                                           &error);

        if (error) {
                g_warning ("error getting the service proxy for \"%s\" on \"%s\": %s",
                           PRIV (object)->creator_path,
                           PRIV (object)->bus_name,
                           error->message);
                g_clear_error (&error);
        }
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
        case PROP_BUS_NAME:
                g_value_set_string (value,
                                    PRIV (object)->bus_name);
                break;
        case PROP_CREATOR_PATH:
                g_value_set_string (value,
                                    PRIV (object)->creator_path);
                break;
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
        case PROP_BUS_NAME:
                g_return_if_fail (!PRIV (object)->bus_name);

                PRIV (object)->bus_name = g_value_dup_string (value);
                break;
        case PROP_CREATOR_PATH:
                g_return_if_fail (!PRIV (object)->creator_path);

                PRIV (object)->creator_path = g_value_dup_string (value);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
                break;
        }
}

static void
uba_container_class_init (UbaContainerClass* self_class)
{
        GObjectClass* object_class = G_OBJECT_CLASS (self_class);

        object_class->constructed  = container_constructed;
        object_class->finalize     = container_finalize;
        object_class->get_property = container_get_property;
        object_class->set_property = container_set_property;

        g_object_class_install_property (object_class,
                                         PROP_BUS_NAME,
                                         g_param_spec_string ("bus-name", NULL, NULL,
                                                              NULL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
        g_object_class_install_property (object_class,
                                         PROP_CREATOR_PATH,
                                         g_param_spec_string ("creator-path", NULL, NULL,
                                                              NULL, G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

        g_type_class_add_private (self_class, sizeof (UbaContainerPrivate));
}

/* Public API Implementation */

GtkWidget*
uba_container_new (gchar const* service_name,
                   gchar const* creator_path)
{
        return g_object_new (UBA_TYPE_CONTAINER,
                             "bus-name", service_name,
                             "creator-path", creator_path,
                             NULL);
}

