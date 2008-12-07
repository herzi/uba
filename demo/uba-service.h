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

#ifndef UBA_SERVICE_H
#define UBA_SERVICE_H

#include <glib-object.h>

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

GType       uba_service_get_type      (void);
UbaService* uba_service_new           (void);
void        uba_service_set_main_loop (UbaService* self,
                                       GMainLoop * loop);

struct _UbaService {
        GObject            base_instance;
        UbaServicePrivate* _private;
};

struct _UbaServiceClass {
        GObjectClass       base_class;
};

G_END_DECLS

#endif /* !UBA_SERVICE_H */
