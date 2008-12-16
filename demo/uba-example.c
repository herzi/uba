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

#include <glib.h>
#include <dbus/dbus-glib.h>
#include <gtk/gtk.h>

#include "uba-creator.h"

static GtkWidget*
connect_cb (UbaService* service,
            guint64     socket_id)
{
        return gtk_button_new_with_label ("UbaExample");
}

int
main (int   argc,
      char**argv)
{
        DBusGConnection* bus;
        UbaService     * service;
        GMainLoop      * loop;
        GError         * error = NULL;

        g_type_init ();

        bus = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
        if (error) {
                g_warning ("Failed to connect to dbus session bus: %s",
                           error->message);
                g_clear_error (&error);
                return 1;
        }

        switch (dbus_bus_request_name (dbus_g_connection_get_connection (bus),
                                       "eu.adeal.uba.example",
                                       DBUS_NAME_FLAG_REPLACE_EXISTING,
                                       NULL))
        {
        case DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER:
                /* happy */
                break;
        default:
                /* unhappy */
                break;
        }

        gtk_init (&argc, &argv);

        loop = g_main_loop_new (NULL, FALSE);

        service = uba_service_new ();
        uba_service_set_main_loop (service, loop);

        g_signal_connect (service, "connect",
                          G_CALLBACK (connect_cb), NULL);

        dbus_g_connection_register_g_object (bus,
                                             "/eu/adeal/uba/example",
                                             G_OBJECT (service));

        g_main_loop_run (loop);
        g_main_loop_unref (loop);

        g_object_unref (service);

        return 0;
}

