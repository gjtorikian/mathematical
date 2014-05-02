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

#include <lsmsvgstyle.h>
#include <lsmsvgcolors.h>
#include <lsmsvgtraits.h>
#include <lsm.h>
#include <string.h>
#include <math.h>

static const LsmPropertyInfos lsm_svg_property_infos[] = {
	{
		.name = "alignment-baseline",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, alignment_baseline),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "auto" /* FIXME specification says "see property description" */
	},
	{
		.name = "baseline-shift",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, baseline_shift),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "baseline"
	},
	{
		.name = "clip",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, clip),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "auto"
	},
	{
		.name = "clip-path",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, clip_path),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "none"
	},
	{
		.name = "comp-op",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, comp_op),
		.trait_class = &lsm_svg_comp_op_trait_class,
		.trait_default = "src-over"
	},
	{
		.name = "dominant-baseline",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, dominant_baseline),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "auto"
	},
	{
		.name = "enable-background",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, enable_background),
		.trait_class = &lsm_svg_enable_background_trait_class,
		.trait_default = "accumulate"
	},
	{
		.name = "filter",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, filter),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "none"
	},
	{
		.name = "flood-color",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, flood_color),
		.trait_class = &lsm_svg_color_trait_class,
		.trait_default = "black"
	},
	{
		.name = "flood-opacity",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, flood_opacity),
		.trait_class = &lsm_double_trait_class,
		.trait_default = "1"
	},
	{
		.name = "lighting-color",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, lighting_color),
		.trait_class = &lsm_svg_color_trait_class,
		.trait_default = "white"
	},
	{
		.name = "mask",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, mask),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "none"
	},
	{
		.name = "opacity",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, opacity),
		.trait_class = &lsm_double_trait_class,
		.trait_default = "1"
	},
	{
		.name = "overflow",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, overflow),
		.trait_class = &lsm_svg_overflow_trait_class,
		.trait_default = "hidden"
	},
	{
		.name = "stop-color",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, stop_color),
		.trait_class = &lsm_svg_color_trait_class,
		.trait_default = "black"
	},
	{
		.name = "stop-opacity",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, stop_opacity),
		.trait_class = &lsm_double_trait_class,
		.trait_default = "1"
	},
	{
		.name = "text-decoration",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, text_decoration),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "none"
	},
	{
		.name = "unicode-bidi",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, unicode_bidi),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "normal"
	},
	{
		.name = "viewport-fill",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, viewport_fill),
		.trait_class = &lsm_svg_paint_trait_class,
		.trait_default = "none" 
	},
	{
		.name = "viewport-fill-opacity",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, viewport_fill_opacity),
		.trait_class = &lsm_double_trait_class,
		.trait_default = "1"
	},
	/* Inherited properties */
	{
		.name = "clip-rule",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, clip_rule),
		.trait_class = &lsm_svg_fill_rule_trait_class,
		.trait_default = "nonzero"
	},
	{
		.name = "color",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, color),
		.trait_class = &lsm_svg_color_trait_class,
		.trait_default = "black" /* Depends on user agent */
	},
	{
		.name = "color-interpolation",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, color_interpolation),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "sRGB"
	},
	{
		.name = "color-interpolation-filters",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, color_interpolation_filters),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "linearRGB"
	},
	{
		.name = "color-profile",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, color_profile),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "auto"
	},
	{
		.name = "color-rendering",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, color_rendering),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "auto"
	},
	{
		.name = "cursor",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, cursor),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "auto"
	},
	{
		.name = "direction",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, direction),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "ltr"
	},
	{
		.name = "display",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, display),
		.trait_class = &lsm_svg_display_trait_class,
		.trait_default = "inline"
	},
	{
		.name = "fill",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, fill),
		.trait_class = &lsm_svg_paint_trait_class,
		.trait_default = "black"
	},
	{
		.name = "fill-opacity",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, fill_opacity),
		.trait_class = &lsm_double_trait_class,
		.trait_default = "1"
	},
	{
		.name = "fill-rule",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, fill_rule),
		.trait_class = &lsm_svg_fill_rule_trait_class,
		.trait_default = "nonzero"
	},
	{
		.name = "font",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, font),
		.trait_class = &lsm_null_trait_class,
		.trait_default = NULL /* specification says "See individual properties" */
	},
	{
		.name = "font-family",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, font_family),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "Sans" /* Depends on user agent */
	},
	{
		.name = "font-size",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, font_size),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = "10pt" /* FIXME Specification says "medium" */
	},
	{
		.name = "font-size-adjust",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, font_size_adjust),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "none"
	},
	{
		.name = "font-stretch",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, font_stretch),
		.trait_class = &lsm_svg_font_stretch_trait_class,
		.trait_default = "normal"
	},
	{
		.name = "font-style",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, font_style),
		.trait_class = &lsm_svg_font_style_trait_class,
		.trait_default = "normal"
	},
	{
		.name = "font-variant",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, font_variant),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "normal"
	},
	{
		.name = "font-weight",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, font_weight),
		.trait_class = &lsm_svg_font_weight_trait_class,
		.trait_default = "normal"
	},
	{
		.name = "glyph-orientation-horizontal",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, glyph_orientation_horizontal),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "0deg"
	},
	{
		.name = "glyph-orientation-vertical",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, glyph_orientation_vertical),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "auto"
	},
	{
		.name = "image-rendering",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, image_rendering),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "auto"
	},
	{
		.name = "kerning",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, kerning),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "auto"
	},
	{
		.name = "letter-spacing",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, letter_spacing),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "normal"
	},
	{
		.name = "marker",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, marker),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "none"
	},
	{
		.name = "marker-end",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, marker_end),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "none"
	},
	{
		.name = "marker-mid",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, marker_mid),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "none"
	},
	{
		.name = "marker-start",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, marker_start),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "none"
	},
	{
		.name = "pointer-events",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, pointer_events),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "visiblePainted"
	},
	{
		.name = "shape-rendering",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, shape_rendering),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "auto"
	},
	{
		.name = "stroke",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, stroke),
		.trait_class = &lsm_svg_paint_trait_class,
		.trait_default = "none"
	},
	{
		.name = "stroke-dasharray",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, stroke_dash_array),
		.trait_class = &lsm_svg_dash_array_trait_class,
		.trait_default = "none"
	},
	{
		.name = "stroke-dashoffset",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, stroke_dash_offset),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = "0"
	},
	{
		.name = "stroke-linecap",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, stroke_line_cap),
		.trait_class = &lsm_svg_line_cap_trait_class,
		.trait_default = "butt"
	},
	{
		.name = "stroke-linejoin",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, stroke_line_join),
		.trait_class = &lsm_svg_line_join_trait_class,
		.trait_default = "miter"
	},
	{
		.name = "stroke-miterlimit",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, stroke_miter_limit),
		.trait_class = &lsm_double_trait_class,
		.trait_default = "4"
	},
	{
		.name = "stroke-opacity",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, stroke_opacity),
		.trait_class = &lsm_double_trait_class,
		.trait_default = "1"
	},
	{
		.name = "stroke-width",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, stroke_width),
		.trait_class = &lsm_svg_length_trait_class,
		.trait_default = "1"
	},
	{
		.name = "text-anchor",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, text_anchor),
		.trait_class = &lsm_svg_text_anchor_trait_class,
		.trait_default = "start"
	},
	{
		.name = "text-rendering",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, text_rendering),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "auto"
	},
	{
		.name = "visibility",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, visibility),
		.trait_class = &lsm_svg_visibility_trait_class,
		.trait_default = "visible"
	},
	{
		.name = "word-spacing",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, word_spacing),
		.trait_class = &lsm_null_trait_class,
		.trait_default = "normal"
	},
	{
		.name = "writing-mode",
		.id = LSM_PROPERTY_OFFSET_TO_ID (LsmSvgStyle, writing_mode),
		.trait_class = &lsm_svg_writing_mode_trait_class,
		.trait_default = "lr-tb"
	}
};

static LsmPropertyManager *
lsm_svg_get_property_manager (void)
{
	static LsmPropertyManager *manager = NULL;

	if (G_LIKELY (manager != NULL))
		return manager;

	manager = lsm_property_manager_new (G_N_ELEMENTS (lsm_svg_property_infos), lsm_svg_property_infos);

	return manager;
}

void
lsm_svg_property_bag_set_property (LsmPropertyBag *property_bag, const char *name, const char *value)
{
	LsmPropertyManager *property_manager = lsm_svg_get_property_manager ();

	lsm_property_manager_set_property (property_manager, property_bag, name, value);
}

const char *
lsm_svg_property_bag_get_property (LsmPropertyBag *property_bag, const char *name)
{
	LsmPropertyManager *property_manager = lsm_svg_get_property_manager ();

	return lsm_property_manager_get_property (property_manager, property_bag, name);
}

void
lsm_svg_property_bag_clean (LsmPropertyBag *property_bag)
{
	LsmPropertyManager *property_manager = lsm_svg_get_property_manager ();

	lsm_property_manager_clean_properties (property_manager, property_bag);
}

char *
lsm_svg_property_bag_serialize (LsmPropertyBag *property_bag)
{
	LsmPropertyManager *property_manager = lsm_svg_get_property_manager ();

	return lsm_property_manager_serialize (property_manager, property_bag);
}

typedef struct {
	LsmSvgStyle base;

	volatile gint ref_count;
} LsmSvgRealStyle;

static const LsmSvgStyle *
lsm_svg_get_default_style (void)
{
	static LsmSvgStyle *style = NULL;
	LsmPropertyManager *property_manager = lsm_svg_get_property_manager ();

	if (style != NULL)
		return style;

	style = lsm_svg_style_new ();
	style->font_size_px = 0.0;

	lsm_property_manager_init_default_style (property_manager, style);

	return style;
}

LsmSvgStyle *
lsm_svg_style_new (void)
{
	LsmSvgRealStyle *style;

	style = g_slice_new0 (LsmSvgRealStyle);
	style->ref_count = 1;

	return (LsmSvgStyle *) style;
}

LsmSvgStyle *
lsm_svg_style_ref (LsmSvgStyle *style)
{
	LsmSvgRealStyle *real_style = (LsmSvgRealStyle *) style;

	g_return_val_if_fail (real_style != NULL, style);
	g_return_val_if_fail (g_atomic_int_get (&real_style->ref_count) > 0, style);
	g_atomic_int_inc (&real_style->ref_count);

	return style;
}

void
lsm_svg_style_unref (LsmSvgStyle *style)
{
	LsmSvgRealStyle *real_style = (LsmSvgRealStyle *) style;

	 g_return_if_fail (g_atomic_int_get (&real_style->ref_count) > 0);
	 if (g_atomic_int_dec_and_test (&real_style->ref_count))
		 g_slice_free (LsmSvgRealStyle, real_style);
}

LsmSvgStyle *
lsm_svg_style_new_inherited (const LsmSvgStyle *parent_style, LsmPropertyBag *property_bag)
{
	LsmPropertyManager *property_manager = lsm_svg_get_property_manager ();
	LsmSvgRealStyle *real_style;
	LsmSvgStyle *style;
	const LsmSvgStyle *default_style;

	default_style = lsm_svg_get_default_style ();

	real_style = g_slice_new (LsmSvgRealStyle);
	real_style->ref_count = 1;

	style = &real_style->base;

	if (parent_style != NULL) {
		memcpy (style, default_style, offsetof (LsmSvgStyle, clip_rule));
		memcpy (&style->clip_rule, &parent_style->clip_rule,
			sizeof (LsmSvgStyle) - offsetof (LsmSvgStyle, clip_rule));
	} else {
		memcpy (style, default_style, sizeof (LsmSvgStyle));
	}

	lsm_property_manager_apply_property_bag (property_manager, property_bag, style, parent_style);

	return style;
}

LsmSvgStyle *
lsm_svg_style_duplicate (const LsmSvgStyle *origin)
{
	LsmSvgStyle *style;

	style = g_new (LsmSvgStyle, 1);

	memcpy (style, origin, sizeof (LsmSvgStyle));

	return style;
}
