/* This file is part of universal business adapter
 *
 * AUTHORS
 *     Sven Herzberg  <sven@imendio.com>
 *
 * Copyright (C) 2008  Sven Herzberg
 *
 * This work is provided "as is"; redistribution and modification
 * in whole or in part, in any medium, physical or electronic is
 * permitted without restriction.
 *
 * This work is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * In no event shall the authors or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 */

/* UBA Demo: create a simple label containing information about the embedding */

#include <syslog.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <gtk/gtk.h>

#include "uba-service.h"

static void
my_log_func (gchar const*    domain,
             GLogLevelFlags  flags,
             gchar const*    message,
             gpointer        user_data G_GNUC_UNUSED)
{
        gchar const* severity = "debug";
        int          priority = LOG_DEBUG;

        if ((flags & G_LOG_LEVEL_DEBUG) != 0) {
                /* already set */
        }
        if ((flags & G_LOG_LEVEL_INFO) != 0) {
                priority = LOG_INFO;
                severity = "info";
        }
        if ((flags & G_LOG_LEVEL_MESSAGE) != 0) {
                priority = LOG_NOTICE;
                severity = "message";
        }
        if ((flags & G_LOG_LEVEL_WARNING) != 0) {
                priority = LOG_WARNING;
                severity = "warning";
        }
        if ((flags & G_LOG_LEVEL_CRITICAL) != 0) {
                priority = LOG_CRIT;
                severity = "critical";
        }
        if ((flags & G_LOG_LEVEL_CRITICAL) != 0) {
                priority = LOG_ERR;
                severity = "error";
        }

        syslog (priority,
                "%s (%s): %s",
                domain,
                severity,
                message);
}

static GtkWidget*
connect_cb (UbaService* service,
            guint64     socket_id)
{
        GtkWidget* label;
        gchar* text;

        g_message ("creating label for socket %d", socket_id);

        text = g_strdup_printf ("UBA Demo: GtkPlug in GtkSocket (%d)",
                                socket_id);
        label = gtk_label_new (text);
        g_free (text);

        return label;
}

int
main (int   argc,
      char**argv)
{
        DBusGConnection* bus;
        UbaService     * service;
        GMainLoop      * loop;
        GError         * error = NULL;

        openlog (g_get_prgname (),
                 LOG_CONS, LOG_USER);

        g_log_set_default_handler (my_log_func,
                                   NULL);

        syslog (LOG_INFO, "started");

        g_type_init ();

        bus = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
        if (!bus) {
                g_warning ("Failed to connect to dbus session bus: %s",
                           error->message);
                g_clear_error (&error);
                return 1;
        }

        switch (dbus_bus_request_name (dbus_g_connection_get_connection (bus),
                                       "eu.adeal.uba.demo",
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
                                             "/eu/adeal/uba/demo",
                                             G_OBJECT (service));

        g_main_loop_run (loop);
        g_main_loop_unref (loop);

        g_object_unref (service);

        closelog ();

        return 0;
}

