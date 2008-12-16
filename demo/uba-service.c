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

#include "uba-service.h"

#include "uba-service-glue.h"

G_DEFINE_TYPE_WITH_CODE (UbaService, uba_service, G_TYPE_OBJECT,
                         dbus_g_object_type_install_info (g_define_type_id, &dbus_glib_uba_service_object_info););

static void
uba_service_init (UbaService* self)
{}

static void
uba_service_class_init (UbaServiceClass* self_class)
{}

gboolean
uba_service_connect (UbaService* self,
                     guint64     socket_id,
                     gchar     * path,
                     GError    **error)
{
        return TRUE;
}

UbaService*
uba_service_new (void)
{
        return g_object_new (UBA_TYPE_SERVICE,
                             NULL);
}

