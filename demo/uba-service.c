/* This file is part of universal business adapter
 *
 * AUTHORS
 *     Sven Herzberg  <sven@imendio.com>
 *
 * Copyright (C) 2008  Sven Herzberg
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

#include "uba-service.h"

#include "uba-service-glue.h"

struct _UbaServicePrivate {
        GtkWidget* widget;
};

#define PRIV(i) (((UbaService*)(i))->_private)

enum {
        PROP_0,
        PROP_WIDGET
};

G_DEFINE_TYPE_WITH_CODE (UbaService, uba_service, G_TYPE_OBJECT,
                         dbus_g_object_type_install_info (g_define_type_id, &dbus_glib_uba_service_object_info););

static void
uba_service_init (UbaService* self)
{
        PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self,
                                                   UBA_TYPE_SERVICE,
                                                   UbaServicePrivate);
}

static void
service_set_property (GObject     * object,
                      guint         prop_id,
                      GValue const* value,
                      GParamSpec  * pspec)
{
        switch (prop_id) {
        case PROP_WIDGET:
                g_return_if_fail (!PRIV(object)->widget);

                PRIV (object)->widget = g_value_get_object (value);

                g_object_notify (object, "widget");
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
                break;
        }
}

static void
uba_service_class_init (UbaServiceClass* self_class)
{
        GObjectClass* object_class = G_OBJECT_CLASS (self_class);

        object_class->set_property = service_set_property;

        g_object_class_install_property (object_class,
                                         PROP_WIDGET,
                                         g_param_spec_object ("widget", NULL, NULL,
                                                              GTK_TYPE_WIDGET,
                                                              G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY));

        g_type_class_add_private (self_class, sizeof (UbaServicePrivate));
}

gboolean
uba_service_connect (UbaService* self,
                     guint64     socket_id,
                     GError    **error)
{
        GtkWidget* plug = gtk_plug_new (socket_id);

        gtk_container_add (GTK_CONTAINER (plug),
                           PRIV (self)->widget);

        gtk_widget_show_all (plug);

        return TRUE;
}

UbaService*
uba_service_new (GtkWidget* widget)
{
        g_return_val_if_fail (GTK_IS_WIDGET (widget), NULL);

        return g_object_new (UBA_TYPE_SERVICE,
                             "widget", widget,
                             NULL);
}

