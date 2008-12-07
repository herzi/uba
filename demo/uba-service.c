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

#include "uba-service.h"

#include <gtk/gtk.h>

struct _UbaServicePrivate {
        GMainLoop* loop;
};

#define PRIV(i) ((UbaService*)(i))->_private

G_DEFINE_TYPE (UbaService, uba_service, G_TYPE_OBJECT);

static void
uba_service_init (UbaService* self)
{
        PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self,
                                                   UBA_TYPE_SERVICE,
                                                   UbaServicePrivate);
}

static void
service_dispose (GObject* object)
{
        /* FIXME: move into finalize */
        if (PRIV (object)->loop) {
                uba_service_set_main_loop (UBA_SERVICE (object),
                                           NULL);
        }

        G_OBJECT_CLASS (uba_service_parent_class)->dispose (object);
}

static void
uba_service_class_init (UbaServiceClass* self_class)
{
        GObjectClass* object_class = G_OBJECT_CLASS (self_class);

        object_class->dispose = service_dispose;

        g_type_class_add_private (self_class, sizeof (UbaServicePrivate));
}

gboolean
uba_service_connect (UbaService* self,
                     guint64     socket_id,
                     GError    **error)
{
        GtkWidget* plug;
        GtkWidget* label;
        gchar* text;

        g_return_val_if_fail (UBA_IS_SERVICE (self), FALSE);

        plug = gtk_plug_new (socket_id);
        g_object_set_data_full (G_OBJECT (plug),
                                "UbaMainLoop",
                                PRIV (self)->loop,
                                (GDestroyNotify)g_main_loop_quit);

        text = g_strdup_printf ("GtkPlug in GtkSocket (%d)",
                                socket_id);
        label = gtk_label_new (text);
        gtk_container_add (GTK_CONTAINER (plug),
                           label);
        g_free (text);

        gtk_widget_show_all (plug);

        return TRUE;
}

UbaService*
uba_service_new (void)
{
        return g_object_new (UBA_TYPE_SERVICE,
                             NULL);
}

void
uba_service_set_main_loop (UbaService* self,
                           GMainLoop * loop)
{
        g_return_if_fail (UBA_IS_SERVICE (self));

        if (PRIV (self)->loop) {
                g_main_loop_unref (PRIV (self)->loop);
                PRIV (self)->loop = NULL;
        }

        if (loop) {
                PRIV (self)->loop = g_main_loop_ref (loop);
        }
}

