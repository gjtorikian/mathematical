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


#include <math.h>
#include <lsmsvglength.h>

LsmSvgViewbox *
lsm_svg_viewbox_new (double resolution_ppi,
		     const LsmBox *viewbox)
{
	LsmSvgViewbox *svg_viewbox;

	svg_viewbox = g_new (LsmSvgViewbox, 1);
	svg_viewbox->resolution_ppi = resolution_ppi;
	svg_viewbox->viewbox = *viewbox;
	svg_viewbox->diagonal = sqrt (viewbox->width * viewbox->width +
				      viewbox->height * viewbox->height) / sqrt (2.0);

	return svg_viewbox;
}

void
lsm_svg_viewbox_free (LsmSvgViewbox *viewbox)
{
	g_free (viewbox);
}

double
lsm_svg_length_normalize (const LsmSvgLength *length,
			  const LsmSvgViewbox *viewbox,
			  double font_size,
			  LsmSvgLengthDirection direction)
{
	g_return_val_if_fail (length != NULL, 0.0);
	g_return_val_if_fail (viewbox != NULL, 0.0);

	switch (length->type) {
		case LSM_SVG_LENGTH_TYPE_NUMBER:
		case LSM_SVG_LENGTH_TYPE_ERROR:
		case LSM_SVG_LENGTH_TYPE_PX:
			return length->value_unit;
		case LSM_SVG_LENGTH_TYPE_PERCENTAGE:
			switch (direction) {
				case LSM_SVG_LENGTH_DIRECTION_HORIZONTAL:
					return length->value_unit * viewbox->viewbox.width / 100.0;
				case LSM_SVG_LENGTH_DIRECTION_VERTICAL:
					return length->value_unit * viewbox->viewbox.height / 100.0;
				case LSM_SVG_LENGTH_DIRECTION_DIAGONAL:
				case LSM_SVG_LENGTH_DIRECTION_ERROR:
					return length->value_unit * viewbox->diagonal / 100.0;
			}
			break;
		case LSM_SVG_LENGTH_TYPE_PT:
			return length->value_unit * viewbox->resolution_ppi / 72.0;
		case LSM_SVG_LENGTH_TYPE_PC:
			return length->value_unit * viewbox->resolution_ppi / 6.00;
		case LSM_SVG_LENGTH_TYPE_CM:
			return length->value_unit * viewbox->resolution_ppi / 2.54;
		case LSM_SVG_LENGTH_TYPE_MM:
			return length->value_unit * viewbox->resolution_ppi / 25.4;
		case LSM_SVG_LENGTH_TYPE_IN:
			return length->value_unit * viewbox->resolution_ppi;
		case LSM_SVG_LENGTH_TYPE_EMS:
			return length->value_unit * font_size;
		case LSM_SVG_LENGTH_TYPE_EXS:
			return length->value_unit * font_size * 0.5;
	}

	g_warning ("[LsmSvg::normalize_length] Invalid length property");

	return 0.0;
}
