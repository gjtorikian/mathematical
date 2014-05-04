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

#ifndef LSM_SVG_DOCUMENT_H
#define LSM_SVG_DOCUMENT_H

#include <lsmsvgtypes.h>
#include <lsmdomdocument.h>

G_BEGIN_DECLS

#define LSM_TYPE_SVG_DOCUMENT             (lsm_svg_document_get_type ())
#define LSM_SVG_DOCUMENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_SVG_DOCUMENT, LsmSvgDocument))
#define LSM_SVG_DOCUMENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_SVG_DOCUMENT, LsmSvgDocumentClass))
#define LSM_IS_SVG_DOCUMENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_SVG_DOCUMENT))
#define LSM_IS_SVG_DOCUMENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_SVG_DOCUMENT))
#define LSM_SVG_DOCUMENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_SVG_DOCUMENT, LsmSvgDocumentClass))

typedef struct _LsmSvgDocumentClass LsmSvgDocumentClass;

struct _LsmSvgDocument {
	LsmDomDocument	document;

	GHashTable *	ids;
};

struct _LsmSvgDocumentClass {
	LsmDomDocumentClass  parent_class;
};

GType lsm_svg_document_get_type (void);

LsmDomDocument *	lsm_svg_document_new 			(void);

LsmSvgSvgElement * 	lsm_svg_document_get_root_element 	(const LsmSvgDocument *document);
LsmSvgElement * 	lsm_svg_document_get_element_by_url 	(LsmSvgDocument *document, const char *url);
LsmSvgElement *		lsm_svg_document_get_element_by_id 	(LsmSvgDocument *self, const char *id);
void 			lsm_svg_document_register_element 	(LsmSvgDocument *self, LsmSvgElement *element,
								 const char *id, const char *old_id);

G_END_DECLS

#endif

