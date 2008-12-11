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

#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <gtk/gtk.h>
#include "uba-container.h"

#include "uba-service-binding.h"

int
main (int   argc,
      char**argv)
{
        DBusGConnection* bus;
        DBusGProxy     * proxy;
        GtkWidget* window;
        GtkWidget* vbox;
        GtkWidget* button;
        GtkWidget* socket;
        GError         * error = NULL;

        g_type_init ();

        bus = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
        if (!bus) {
                g_warning ("eeek!");
                return 1;
        }

        gtk_init (&argc, &argv);

        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        g_signal_connect (window, "destroy",
                          G_CALLBACK (gtk_main_quit), NULL);

        vbox = gtk_vbox_new (FALSE, 6);
        gtk_container_add (GTK_CONTAINER (window),
                           vbox);

        button = gtk_button_new_from_stock (GTK_STOCK_QUIT);
        g_signal_connect (button, "clicked",
                          G_CALLBACK (gtk_main_quit), NULL);
        gtk_box_pack_start (GTK_BOX (vbox),
                            button,
                            FALSE, TRUE, 0);

        socket = uba_container_new ();
        gtk_container_add (GTK_CONTAINER (vbox),
                           socket);

        proxy = dbus_g_proxy_new_for_name (bus,
                                           "eu.adeal.uba.demo",
                                           "/eu/adeal/uba/demo",
                                           "eu.adeal.uba.creator");
        eu_adeal_uba_creator_get_instance (proxy,
                                           gtk_socket_get_id (GTK_SOCKET (socket)),
                                           &error);

        if (error) {
                g_warning ("error getting the demo: %s", error->message);
                g_clear_error (&error);

                return 1;
        }

        socket = uba_container_new ();
        gtk_container_add (GTK_CONTAINER (vbox),
                           socket);

        proxy = dbus_g_proxy_new_for_name (bus,
                                           "eu.adeal.uba.example",
                                           "/eu/adeal/uba/example",
                                           "eu.adeal.uba.creator");
        eu_adeal_uba_creator_get_instance (proxy,
                                           gtk_socket_get_id (GTK_SOCKET (socket)),
                                           &error);

        if (error) {
                g_warning ("error getting the example: %s", error->message);
                g_clear_error (&error);

                return 1;
        }

        gtk_widget_show_all (window);
        gtk_main ();

        return 0;
}

