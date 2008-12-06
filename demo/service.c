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

#include <syslog.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <gtk/gtk.h>

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

int
main (int   argc,
      char**argv)
{
        DBusConnection* bus;
        GMainLoop* loop;
        GtkWidget* plug;
        GtkWidget* label;
        DBusError  error;
        gchar* text;
        guint64 socket = 0L;

        GOptionContext* context;
        GOptionEntry    entries[] = {
                {"socket", 's', 0, G_OPTION_ARG_INT64, &socket,
                 "The socket id of the parent window", "SOCKET"},
                {NULL}
        };

        openlog (g_get_prgname (),
                 LOG_CONS, LOG_USER);

        g_log_set_default_handler (my_log_func,
                                   NULL);

        syslog (LOG_INFO, "started");

        context = g_option_context_new ("");
        g_option_context_add_main_entries (context,
                                           entries,
                                           NULL);
        g_option_context_parse (context, &argc, &argv, NULL); // FIXME: add error checking

        if (!socket) {
                gchar* help = g_option_context_get_help (context, TRUE, NULL);
                g_printerr ("%s", help);
                g_free (help);
                g_option_context_free (context);
                return 1;
        }

        g_option_context_free (context);

        dbus_error_init (&error);
        bus = dbus_bus_get (DBUS_BUS_SESSION, &error);
        if (!bus) {
                g_warning ("Failed to connect to dbus session bus: %s",
                           error.message);
                dbus_error_free (&error);
                return 1;
        }

        dbus_connection_setup_with_g_main (bus, NULL);

        gtk_init (&argc, &argv);

        loop = g_main_loop_new (NULL, FALSE);

        plug = gtk_plug_new (socket);
        g_object_set_data_full (G_OBJECT (plug),
                                "UbiMainLoop",
                                loop,
                                (GDestroyNotify)g_main_loop_quit);

        text = g_strdup_printf ("GtkPlug in GtkSocket (%d)",
                                socket);
        label = gtk_label_new (text);
        gtk_container_add (GTK_CONTAINER (plug),
                           label);
        g_free (text);

        gtk_widget_show_all (plug);

        g_main_loop_run (loop);
        g_main_loop_unref (loop);

        closelog ();

        return 0;
}

