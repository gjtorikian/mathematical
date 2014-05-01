/* Lasem
 * 
 * Copyright © 2012 Emmanuel Pacaud
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

#include <lsmsvgfiltermerge.h>
#include <lsmsvgfiltermergenode.h>
#include <lsmsvgview.h>

static GObjectClass *parent_class;

/* GdomNode implementation */

static const char *
lsm_svg_filter_merge_get_node_name (LsmDomNode *node)
{
	return "feMerge";
}

static gboolean
lsm_svg_filter_merge_can_append_child (LsmDomNode *self, LsmDomNode *child)
{
	return LSM_IS_SVG_FILTER_MERGE_NODE (child);
}

/* LsmSvgElement implementation */

static void
lsm_svg_filter_merge_apply  (LsmSvgFilterPrimitive *self, LsmSvgView *view,
			     const char *input, const char *output,
			     const LsmBox *subregion)
{
	LsmDomNode *iter;

	for (iter = LSM_DOM_NODE (self)->first_child; iter != NULL; iter = iter->next_sibling)
		lsm_svg_filter_primitive_apply (LSM_SVG_FILTER_PRIMITIVE (iter), view);
}

/* LsmSvgFilterMerge implementation */

LsmDomNode *
lsm_svg_filter_merge_new (void)
{
	return g_object_new (LSM_TYPE_SVG_FILTER_MERGE, NULL);
}

static void
lsm_svg_filter_merge_init (LsmSvgFilterMerge *self)
{
}

static void
lsm_svg_filter_merge_finalize (GObject *object)
{
	parent_class->finalize (object);
}

/* LsmSvgFilterMerge class */

static void
lsm_svg_filter_merge_class_init (LsmSvgFilterMergeClass *klass)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	LsmDomNodeClass *d_node_class = LSM_DOM_NODE_CLASS (klass);
	LsmSvgElementClass *s_element_class = LSM_SVG_ELEMENT_CLASS (klass);
	LsmSvgFilterPrimitiveClass *f_primitive_class = LSM_SVG_FILTER_PRIMITIVE_CLASS (klass);

	parent_class = g_type_class_peek_parent (klass);

	object_class->finalize = lsm_svg_filter_merge_finalize;

	d_node_class->get_node_name = lsm_svg_filter_merge_get_node_name;
	d_node_class->can_append_child = lsm_svg_filter_merge_can_append_child;

	s_element_class->attribute_manager = lsm_attribute_manager_duplicate (s_element_class->attribute_manager);

	f_primitive_class->apply = lsm_svg_filter_merge_apply;
}

G_DEFINE_TYPE (LsmSvgFilterMerge, lsm_svg_filter_merge, LSM_TYPE_SVG_FILTER_PRIMITIVE)
