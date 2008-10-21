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

#include <gtk/gtk.h>
#include "uba-container.h"

int
main (int   argc,
      char**argv)
{
        GtkWidget* window;
        GtkWidget* vbox;
        GtkWidget* button;
        GtkWidget* socket;
        gchar    * command;

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

        command = g_strdup_printf ("./service --socket %d",
                                   gtk_socket_get_id (GTK_SOCKET (socket)));
        gdk_spawn_command_line_on_screen (gtk_widget_get_screen (socket),
                                          command,
                                          NULL); // FIXME: add error checking
        g_free (command);

        gtk_widget_show_all (window);
        gtk_main ();

        return 0;
}

