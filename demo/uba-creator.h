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

#ifndef UBA_CREATOR_H
#define UBA_CREATOR_H

#include <dbus/dbus-glib.h>

G_BEGIN_DECLS

typedef struct _UbaCreator        UbaCreator;
typedef struct _UbaCreatorPrivate UbaCreatorPrivate;
typedef struct _UbaCreatorClass   UbaCreatorClass;

#define UBA_TYPE_CREATOR         (uba_creator_get_type ())
#define UBA_CREATOR(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), UBA_TYPE_CREATOR, UbaCreator))
#define UBA_CREATOR_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), UBA_TYPE_CREATOR, UbaCreatorClass))
#define UBA_IS_CREATOR(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), UBA_TYPE_CREATOR))
#define UBA_IS_CREATOR_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), UBA_TYPE_CREATOR))
#define UBA_CREATOR_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), UBA_TYPE_CREATOR, UbaCreatorClass))

GType       uba_creator_get_type      (void);
UbaCreator* uba_creator_new           (void);
gboolean    uba_creator_connect       (UbaCreator* self,
                                       guint64     socket_id,
                                       gchar     * path,
                                       GError    **error);
gboolean    uba_creator_get_instance  (UbaCreator* self,
                                       gchar     **path,
                                       GError    **error);
void        uba_creator_register      (UbaCreator     * self,
                                       DBusGConnection* bus,
                                       gchar const    * path);
void        uba_creator_set_main_loop (UbaCreator* self,
                                       GMainLoop * loop);

struct _UbaCreator {
        GObject            base_instance;
        UbaCreatorPrivate* _private;
};

struct _UbaCreatorClass {
        GObjectClass       base_class;
};

G_END_DECLS

#endif /* !UBA_CREATOR_H */
