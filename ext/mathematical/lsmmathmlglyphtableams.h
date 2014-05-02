/* Lasem
 *
 * Copyright © 2007-2008 Emmanuel Pacaud
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * Author:
 * 	Emmanuel Pacaud <emmanuel@gnome.org>
 */

#ifndef LSM_MATHML_GLYPH_TABLE_AMS_H
#define LSM_MATHML_GLYPH_TABLE_AMS_H

#include <lsmmathmltypes.h>
#include <lsmmathmlview.h>

G_BEGIN_DECLS

#define LSM_MATHML_RADICAL_UTF8 "\xe2\x88\x9a"

#define LSM_MATHML_RADICAL_ORDER_X_OFFSET	0.5
#define LSM_MATHML_RADICAL_ORDER_Y_OFFSET  0.5
#define LSM_MATHML_RADICAL_TOP_LINE_WIDTH	0.05

extern const LsmMathmlOperatorGlyph AMS_table[];

const LsmMathmlOperatorGlyph *	lsm_mathml_glyph_table_find_operator_glyph (const char *text);
double 				lsm_mathml_glyph_table_get_operator_slant 	(const char *text);

G_END_DECLS

#endif
