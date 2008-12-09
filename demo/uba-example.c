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

int
main (int   argc,
      char**argv)
{
        DBusGConnection* bus;
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

        loop = g_main_loop_new (NULL, FALSE);

        g_main_loop_run (loop);
        g_main_loop_unref (loop);
        return 0;
}

