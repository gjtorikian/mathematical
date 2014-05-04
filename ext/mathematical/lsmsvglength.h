/* Lasem
 *
 * Copyright © 2009 Emmanuel Pacaud
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

#ifndef LSM_SVG_LENGTH
#define LSM_SVG_LENGTH

#include <lsmdom.h>
#include <lsmsvgtypes.h>
#include <lsmsvgenums.h>

G_BEGIN_DECLS

typedef struct {
	double resolution_ppi;
	LsmBox viewbox;
	double diagonal;
} LsmSvgViewbox;

LsmSvgViewbox *	lsm_svg_viewbox_new 		(double resolution_ppi, const LsmBox *viewbox);
void		lsm_svg_viewbox_free 		(LsmSvgViewbox *viewbox);

typedef struct {
	double value_unit;
	LsmSvgLengthType type;
} LsmSvgLength;

typedef struct {
	LsmSvgLength base;
	LsmSvgLength animated;
} LsmSvgAnimatedLength;

double 			lsm_svg_length_normalize	(const LsmSvgLength *length,
							 const LsmSvgViewbox *viewbox,
							 double font_size,
							 LsmSvgLengthDirection direction);
gboolean 		lsm_svg_parse_length 		(char **str, LsmSvgLength *length);

typedef struct {
	unsigned int n_lengths;
	LsmSvgLength *lengths;
} LsmSvgLengthList;

G_END_DECLS

#endif
