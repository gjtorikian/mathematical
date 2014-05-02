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

#ifndef LSM_MATHML_DOCUMENT_H
#define LSM_MATHML_DOCUMENT_H

#include <lsmmathmltypes.h>
#include <lsmdomdocument.h>

G_BEGIN_DECLS

#define LSM_TYPE_MATHML_DOCUMENT             (lsm_mathml_document_get_type ())
#define LSM_MATHML_DOCUMENT(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), LSM_TYPE_MATHML_DOCUMENT, LsmMathmlDocument))
#define LSM_MATHML_DOCUMENT_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), LSM_TYPE_MATHML_DOCUMENT, LsmMathmlDocumentClass))
#define LSM_IS_MATHML_DOCUMENT(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), LSM_TYPE_MATHML_DOCUMENT))
#define LSM_IS_MATHML_DOCUMENT_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), LSM_TYPE_MATHML_DOCUMENT))
#define LSM_MATHML_DOCUMENT_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS((obj), LSM_TYPE_MATHML_DOCUMENT, LsmMathmlDocumentClass))

typedef struct _LsmMathmlDocumentClass LsmMathmlDocumentClass;

struct _LsmMathmlDocument {
	LsmDomDocument	document;
};

struct _LsmMathmlDocumentClass {
	LsmDomDocumentClass  parent_class;
};

GType lsm_mathml_document_get_type (void);

LsmDomDocument *	lsm_mathml_document_new 		(void);
LsmMathmlMathElement * 	lsm_mathml_document_get_root_element 	(const LsmMathmlDocument *document);

LsmMathmlDocument * 	lsm_mathml_document_new_from_itex	(const char *itex, int size, GError **error);
LsmMathmlDocument * 	lsm_mathml_document_new_from_itex_path 	(const char *url, GError **error);
LsmMathmlDocument * 	lsm_mathml_document_new_from_itex_url 	(const char *url, GError **error);

G_END_DECLS

#endif

