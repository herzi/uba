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
 * goods or creators; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 */

#include "uba-creator.h"

#include <gtk/gtk.h>

#include "uba-creator-glue.h"
#include "uba-marshallers.h"
#include "uba-service.h"

#include <glib/gi18n.h>

enum {
        CONNECT,
        N_SIGNALS
};

struct _UbaCreatorPrivate {
        DBusGConnection* bus;
        GMainLoop      * loop;
};

#define PRIV(i) ((UbaCreator*)(i))->_private

static guint uba_creator_signals[N_SIGNALS] = {0};

G_DEFINE_TYPE_WITH_CODE (UbaCreator, uba_creator, G_TYPE_OBJECT,
                         dbus_g_object_type_install_info (g_define_type_id, &dbus_glib_uba_creator_object_info););

static void
uba_creator_init (UbaCreator* self)
{
        PRIV (self) = G_TYPE_INSTANCE_GET_PRIVATE (self,
                                                   UBA_TYPE_CREATOR,
                                                   UbaCreatorPrivate);
}

static void
creator_dispose (GObject* object)
{
        /* FIXME: move into finalize */
        if (PRIV (object)->loop) {
                uba_creator_set_main_loop (UBA_CREATOR (object),
                                           NULL);
        }

        G_OBJECT_CLASS (uba_creator_parent_class)->dispose (object);
}

static void
uba_creator_class_init (UbaCreatorClass* self_class)
{
        GObjectClass* object_class = G_OBJECT_CLASS (self_class);

        object_class->dispose = creator_dispose;

        /* UbaCreator::connect
         *
         * This signal gets emitted once the creator should create a new
         * widget.
         *
         * Returns a #GtkWidget (with initial floating reference); %NULL
         * on error conditions.
         */
        uba_creator_signals[CONNECT] = g_signal_new ("connect",
                                                     UBA_TYPE_CREATOR,
                                                     G_SIGNAL_ACTION,
                                                     0,
                                                     NULL, NULL, /* FIXME: add accumulator */
                                                     uba_marshal_OBJECT__UINT64,
                                                     GTK_TYPE_WIDGET,
                                                     1,
                                                     G_TYPE_UINT64);

        g_type_class_add_private (self_class, sizeof (UbaCreatorPrivate));
}

gboolean
uba_creator_get_instance (UbaCreator* self,
                          gchar     **path,
                          GError    **error)
{
        static guint id = 0;
        static gchar* iter;

        /* FIXME: add a logging function that sets the error */
        g_return_val_if_fail (UBA_IS_CREATOR (self), FALSE);
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
uba_creator_connect (UbaCreator* self,
                     guint64     socket_id,
                     gchar     * path,
                     GError    **error)
{
        UbaService* service = NULL;
        GtkWidget* result = NULL;

        g_return_val_if_fail (UBA_IS_CREATOR (self), FALSE);

        /* FIXME: rename the signal */
        g_signal_emit (self,
                       uba_creator_signals[CONNECT],
                       0,
                       socket_id,
                       &result);

        if (GTK_IS_WIDGET (result)) {
                UbaService* service = uba_service_new (result);
                g_object_set_data_full (G_OBJECT (result),
                                        "UbaMainLoop",
                                        PRIV (self)->loop,
                                        (GDestroyNotify)g_main_loop_quit);

                dbus_g_connection_register_g_object (PRIV (self)->bus,
                                                     path,
                                                     G_OBJECT (service));
        } else {
                g_set_error (error,
                             0, /* domain */
                             0, /* code */
                             _("The creator didn't receive an object"));
        }

        service = UBA_SERVICE (dbus_g_connection_lookup_g_object (PRIV (self)->bus, path));

        if (service) {
                uba_service_connect (service,
                                     socket_id,
                                     path,
                                     error);
        } else {
                g_set_error (error, 0, 0, _("Didn't get a service, strange..."));
        }

        return service != NULL;
}

UbaCreator*
uba_creator_new (void)
{
        return g_object_new (UBA_TYPE_CREATOR,
                             NULL);
}

void
uba_creator_register (UbaCreator     * self,
                      DBusGConnection* bus,
                      gchar const    * path)
{
        gboolean registered = PRIV (self)->bus != NULL;

        g_return_if_fail (!registered);

        PRIV (self)->bus = bus;

        dbus_g_connection_register_g_object (bus,
                                             path,
                                             G_OBJECT (self));
}

void
uba_creator_set_main_loop (UbaCreator* self,
                           GMainLoop * loop)
{
        g_return_if_fail (UBA_IS_CREATOR (self));

        if (PRIV (self)->loop) {
                g_main_loop_unref (PRIV (self)->loop);
                PRIV (self)->loop = NULL;
        }

        if (loop) {
                PRIV (self)->loop = g_main_loop_ref (loop);
        }
}

