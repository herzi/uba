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

#ifndef UBA_SERVICE_H
#define UBA_SERVICE_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _UbaService        UbaService;
typedef struct _UbaServicePrivate UbaServicePrivate;
typedef struct _UbaServiceClass   UbaServiceClass;

#define UBA_TYPE_SERVICE         (uba_service_get_type ())
#define UBA_SERVICE(i)           (G_TYPE_CHECK_INSTANCE_CAST ((i), UBA_TYPE_SERVICE, UbaService))
#define UBA_SERVICE_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), UBA_TYPE_SERVICE, UbaServiceClass))
#define UBA_IS_SERVICE(i)        (G_TYPE_CHECK_INSTANCE_TYPE ((i), UBA_TYPE_SERVICE))
#define UBA_IS_SERVICE_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), UBA_TYPE_SERVICE))
#define UBA_SERVICE_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS ((i), UBA_TYPE_SERVICE, UbaServiceClass))

GType       uba_service_get_type (void);
UbaService* uba_service_new      (GtkWidget * widget);
gboolean    uba_service_connect  (UbaService* self,
                                  guint64     socket_id,
                                  GError    **error);

struct _UbaService {
        GObject            base_instance;
        UbaServicePrivate* _private;
};

struct _UbaServiceClass {
        GObjectClass       base_class;
};

G_END_DECLS

#endif /* !UBA_SERVICE_H */
