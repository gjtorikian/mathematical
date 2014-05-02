/* Lasem - SVG and Mathml library
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

#ifndef LSM_SVG_ATTRIBUTES_H
#define LSM_SVG_ATTRIBUTES_H

#include <lsmdom.h>
#include <lsmsvgtypes.h>
#include <lsmsvgenums.h>
#include <lsmsvgtraits.h>
#include <lsmsvglength.h>
#include <lsmsvgmatrix.h>

G_BEGIN_DECLS

typedef struct {
	LsmAttribute base;
	LsmSvgBlendingMode value;
} LsmSvgBlendingModeAttribute;

typedef struct {
	LsmAttribute base;
	double value;
} LsmSvgDoubleAttribute;

typedef struct {
	LsmAttribute base;
	LsmSvgOneOrTwoDouble value;
} LsmSvgOneOrTwoDoubleAttribute;

typedef struct {
	LsmAttribute base;
	LsmSvgDashArray *value;
} LsmSvgDashArrayAttribute;

typedef struct {
	LsmAttribute base;
	LsmSvgLength length;
} LsmSvgLengthAttribute;

typedef struct {
	LsmAttribute base;
	LsmSvgPaint paint;
} LsmSvgPaintAttribute;

typedef struct {
	LsmAttribute base;
	char *value;
} LsmSvgStringAttribute;

typedef struct {
	LsmAttribute base;
	LsmSvgColor value;
} LsmSvgColorAttribute;

typedef struct {
	LsmAttribute base;
	LsmBox value;
} LsmSvgViewboxAttribute;

typedef struct {
	LsmAttribute base;
	LsmSvgMatrix matrix;
} LsmSvgTransformAttribute;

typedef struct {
	LsmAttribute base;
	LsmSvgPreserveAspectRatio value;
} LsmSvgPreserveAspectRatioAttribute;

typedef struct {
	LsmAttribute base;
	LsmSvgSpreadMethod value;
} LsmSvgSpreadMethodAtttribute;

typedef struct {
	LsmAttribute base;
	LsmSvgPatternUnits value;
} LsmSvgPatternUnitsAttribute;

typedef struct {
	LsmAttribute base;
	LsmSvgMarkerUnits value;
} LsmSvgMarkerUnitsAttribute;

typedef struct {
	LsmAttribute base;
	LsmSvgAngle value;
} LsmSvgAngleAttribute;

G_END_DECLS

#endif
