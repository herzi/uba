/* This file is part of the universal business controller
 *
 * AUTHORS
 *     Sven Herzberg  <herzi@gnome-de.org>
 *
 * Copyright (C) 2007  Sven Herzberg
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

#include "s-uba-container.h"

#include <uba/uba-container.h>

START_TEST (demo_testcase)
{
	//g_print ("%s\n", g_type_name (UBA_TYPE_CONTAINER));
}
END_TEST

TCase*
uba_container_scrollable_test (void)
{
	TCase* self = tcase_create ("Adding scrollable widgets to containers");
	//tcase_add_checked_fixture (self, g_type_init, NULL);
	tcase_add_test (self, demo_testcase);
	return self;
}

