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

#ifndef LSM_MATHML_TRAITS_H
#define LSM_MATHML_TRAITS_H

#include <lsmmathmlenums.h>
#include <lsmtraits.h>

G_BEGIN_DECLS

#define LSM_MATHML_SPACE_EM_VERY_VERY_THIN	0.055556
#define LSM_MATHML_SPACE_EM_VERY_THIN		0.111111
#define LSM_MATHML_SPACE_EM_THIN		0.166667
#define LSM_MATHML_SPACE_EM_MEDIUM	 	0.222222
#define LSM_MATHML_SPACE_EM_THICK		0.277778
#define LSM_MATHML_SPACE_EM_VERY_THICK		0.333333
#define LSM_MATHML_SPACE_EM_VERY_VERY_THICK	0.388889

#define LSM_TYPE_MATHML_COLOR (lsm_mathml_color_get_type())

typedef struct {
	double red;
	double green;
	double blue;
	double alpha;
} LsmMathmlColor;

GType lsm_mathml_color_get_type (void);

#define LSM_TYPE_MATHML_LENGTH (lsm_mathml_length_get_type())

typedef struct {
	double value;
	LsmMathmlUnit unit;
} LsmMathmlLength;

GType 	lsm_mathml_length_get_type 	(void);
double 	lsm_mathml_length_normalize 	(const LsmMathmlLength *length,
					 double base,
					 double font_size);

typedef struct {
	LsmMathmlScriptLevelSign sign;
	int level;
} LsmMathmlScriptLevel;

typedef struct {
	unsigned int n_values;
	int *values;
} LsmMathmlEnumList;

#define LSM_TYPE_MATHML_SPACE (lsm_mathml_space_get_type())

typedef struct {
	LsmMathmlSpaceName name;
	LsmMathmlLength length;
} LsmMathmlSpace;

GType 	lsm_mathml_space_get_type 	(void);

typedef struct {
	unsigned int n_spaces;
	LsmMathmlSpace *spaces;
} LsmMathmlSpaceList;

void lsm_mathml_enum_list_init  (LsmMathmlEnumList *enum_list, const LsmMathmlEnumList *enum_list_default);
void lsm_mathml_space_list_init (LsmMathmlSpaceList *space_list, const LsmMathmlSpaceList *space_list_default);

extern const LsmTraitClass lsm_mathml_boolean_trait_class;

extern const LsmTraitClass lsm_mathml_unsigned_trait_class;

extern const LsmTraitClass lsm_mathml_display_trait_class;
extern const LsmTraitClass lsm_mathml_mode_trait_class;
extern const LsmTraitClass lsm_mathml_line_trait_class;
extern const LsmTraitClass lsm_mathml_font_style_trait_class;
extern const LsmTraitClass lsm_mathml_font_weight_trait_class;
extern const LsmTraitClass lsm_mathml_variant_trait_class;
extern const LsmTraitClass lsm_mathml_form_trait_class;

extern const LsmTraitClass lsm_mathml_row_align_list_trait_class;
extern const LsmTraitClass lsm_mathml_column_align_list_trait_class;
extern const LsmTraitClass lsm_mathml_line_list_trait_class;

extern const LsmTraitClass lsm_mathml_script_level_trait_class;

extern const LsmTraitClass lsm_mathml_double_trait_class;
extern const LsmTraitClass lsm_mathml_string_trait_class;
extern const LsmTraitClass lsm_mathml_length_trait_class;

extern const LsmTraitClass lsm_mathml_space_trait_class;
extern const LsmTraitClass lsm_mathml_space_list_trait_class;

extern const LsmTraitClass lsm_mathml_color_trait_class;

G_END_DECLS

#endif
