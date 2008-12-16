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

#include "uba-creator.h"

#include <gtk/gtk.h>

#include "uba-creator-glue.h"
#include "uba-marshallers.h"

#include <glib/gi18n.h>

enum {
        CONNECT,
        N_SIGNALS
};

struct _UbaServicePrivate {
        GMainLoop* loop;
};

#define PRIV(i) ((UbaService*)(i))->_private

static guint uba_service_signals[N_SIGNALS] = {0};

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

        /* UbaService::connect
         *
         * This signal gets emitted once the service should create a new
         * widget.
         *
         * Returns a #GtkWidget (with initial floating reference); %NULL
         * on error conditions.
         */
        uba_service_signals[CONNECT] = g_signal_new ("connect",
                                                     UBA_TYPE_SERVICE,
                                                     G_SIGNAL_ACTION,
                                                     0,
                                                     NULL, NULL, /* FIXME: add accumulator */
                                                     uba_marshal_OBJECT__UINT64,
                                                     GTK_TYPE_WIDGET,
                                                     1,
                                                     G_TYPE_UINT64);

        g_type_class_add_private (self_class, sizeof (UbaServicePrivate));
}

gboolean
uba_service_get_instance (UbaService* self,
                          gchar     **path,
                          GError    **error)
{
        static guint id = 0;
        static gchar* iter;

        /* FIXME: add a logging function that sets the error */
        g_return_val_if_fail (UBA_IS_SERVICE (self), FALSE);
        g_return_val_if_fail (path && !*path, FALSE);

        *path = g_strdup_printf ("/eu/adeal/uba/%s_%lu",
                                 g_get_prgname (),
                                 id++);
        for (iter = *path; iter && *iter; iter++) {
                if (*iter == '-') {
                        *iter = '_';
                }
        }

        return *path != NULL;
}

gboolean
uba_service_connect (UbaService* self,
                     guint64     socket_id,
                     gchar     * path,
                     GError    **error)
{
        GtkWidget* plug;
        GtkWidget* result = NULL;

        g_return_val_if_fail (UBA_IS_SERVICE (self), FALSE);

        /* FIXME: rename the signal */
        g_signal_emit (self,
                       uba_service_signals[CONNECT],
                       0,
                       socket_id,
                       &result);

        if (GTK_IS_WIDGET (result)) {
                plug = gtk_plug_new (socket_id);
                g_object_set_data_full (G_OBJECT (plug),
                                        "UbaMainLoop",
                                        PRIV (self)->loop,
                                        (GDestroyNotify)g_main_loop_quit);

                gtk_container_add (GTK_CONTAINER (plug),
                                   result);

                gtk_widget_show_all (plug);
        } else {
                g_set_error (error,
                             0, /* domain */
                             0, /* code */
                             _("The service didn't receive an object"));
        }

        return GTK_IS_WIDGET (result);
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

