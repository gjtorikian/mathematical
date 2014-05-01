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

#include <lsmdebug.h>
#include <lsmmathmlglyphtableams.h>
#include <string.h>
#include <math.h>

const LsmMathmlOperatorGlyph AMS_table[] = {
	{
		LSM_MATHML_RADICAL_UTF8, /* radical */
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL |
		LSM_MATHML_GLYPH_FLAG_TYPE_SIZED,
		{LSM_MATHML_FONT_CMEX10,		"t"},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_CMEX10,		"v"},
		{LSM_MATHML_FONT_CMEX10,		"u"},
		4,
		{
			{LSM_MATHML_FONT_CMEX10,		"p"},
			{LSM_MATHML_FONT_CMEX10,		"q"},
			{LSM_MATHML_FONT_CMEX10,		"r"},
			{LSM_MATHML_FONT_CMEX10,		"s"}
		}
	},
	{
		"(",
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL |
		LSM_MATHML_GLYPH_FLAG_TYPE_SIZED |
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS,
		{LSM_MATHML_FONT_CMEX10,		"0"},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_CMEX10,		"@"},
		{LSM_MATHML_FONT_CMEX10,		"B"},
		5,
		{
			{LSM_MATHML_FONT_CMR10,		"("},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xa1"},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xb3"},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xb5"},
			{LSM_MATHML_FONT_CMEX10,		"\xc3\x83"}
		}
	},
	{
		")",
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL |
		LSM_MATHML_GLYPH_FLAG_TYPE_SIZED |
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS,
		{LSM_MATHML_FONT_CMEX10, 		"1"},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_CMEX10,		"A"},
		{LSM_MATHML_FONT_CMEX10,		"C"},
		5,
		{
			{LSM_MATHML_FONT_CMR10, 		")"},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xa2"},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xb4"},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xb6"},
			{LSM_MATHML_FONT_CMEX10,		"!"}
		}
	},
	{
		"{",
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL |
		LSM_MATHML_GLYPH_FLAG_TYPE_SIZED |
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS,
		{LSM_MATHML_FONT_CMEX10, 		"8"},
		{LSM_MATHML_FONT_CMEX10, 		"<"},
		{LSM_MATHML_FONT_CMEX10, 		":"},
		{LSM_MATHML_FONT_CMEX10, 		">"},
		5,
		{
			{LSM_MATHML_FONT_CMSY10, 		"f"},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xa9"},
			{LSM_MATHML_FONT_CMEX10,		"n"},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xbd"},
			{LSM_MATHML_FONT_CMEX10,		"("}
		}
	},
	{
		"}",
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL |
		LSM_MATHML_GLYPH_FLAG_TYPE_SIZED |
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS,
		{LSM_MATHML_FONT_CMEX10, 		"9"},
		{LSM_MATHML_FONT_CMEX10, 		"="},
		{LSM_MATHML_FONT_CMEX10, 		";"},
		{LSM_MATHML_FONT_CMEX10, 		">"},
		5,
		{
			{LSM_MATHML_FONT_CMSY10,		"g"},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xaa"},
			{LSM_MATHML_FONT_CMEX10,		"o"},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xbe"},
			{LSM_MATHML_FONT_CMEX10,		")"}
		}
	},
	{
		"[",
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL |
		LSM_MATHML_GLYPH_FLAG_TYPE_SIZED |
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS,
		{LSM_MATHML_FONT_CMEX10, 		"2"},
		{LSM_MATHML_FONT_ERROR, 		""},
		{LSM_MATHML_FONT_CMEX10, 		"4"},
		{LSM_MATHML_FONT_CMEX10, 		"6"},
		3,
		{
			{LSM_MATHML_FONT_CMR10, 		"["},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xa3"},
			{LSM_MATHML_FONT_CMEX10,		"h"},
			{LSM_MATHML_FONT_ERROR,		""},
			{LSM_MATHML_FONT_ERROR,		""}
		}
	},
	{
		"]",
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL |
		LSM_MATHML_GLYPH_FLAG_TYPE_SIZED |
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS,
		{LSM_MATHML_FONT_CMEX10, 		"3"},
		{LSM_MATHML_FONT_ERROR, 		""},
		{LSM_MATHML_FONT_CMEX10, 		"5"},
		{LSM_MATHML_FONT_CMEX10, 		"7"},
		3,
		{
			{LSM_MATHML_FONT_CMR10,		"]"},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xa4"},
			{LSM_MATHML_FONT_CMEX10,		"i"},
			{LSM_MATHML_FONT_ERROR,		""},
			{LSM_MATHML_FONT_ERROR,		""}
		}
	},
	{
		"\xe2\x8c\xa9", /* 〈 */
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL |
		LSM_MATHML_GLYPH_FLAG_TYPE_SIZED |
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		3,
		{
			{LSM_MATHML_FONT_CMEX10,		"D"},
			{LSM_MATHML_FONT_CMEX10,		"\xc2\xbf"},
			{LSM_MATHML_FONT_CMEX10,		"*"},
			{LSM_MATHML_FONT_ERROR,		""},
			{LSM_MATHML_FONT_ERROR,		""}
		}
	},
	{
		"\xe2\x8c\xaa", /* 〉 */
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL |
		LSM_MATHML_GLYPH_FLAG_TYPE_SIZED |
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		3,
		{
			{LSM_MATHML_FONT_CMEX10,		"E"},
			{LSM_MATHML_FONT_CMEX10,		"\xc3\x80"},
			{LSM_MATHML_FONT_CMEX10,		"+"},
			{LSM_MATHML_FONT_ERROR,		""},
			{LSM_MATHML_FONT_ERROR,		""}
		}
	},
	{
		"\xe2\x88\x91" /* ∑ */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMEX10,	"P"},
			{LSM_MATHML_FONT_CMEX10,	"X"}
		}
	},
	{
		"\xe2\x88\x8f" /* ∏ */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMEX10,	"Q"},
			{LSM_MATHML_FONT_CMEX10,	"Y"}
		}
	},
	{
		"\xe2\x88\x90" /* ∐ */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMEX10,	"`"},
			{LSM_MATHML_FONT_CMEX10,	"a"}
		}
	},
	{
		"\xe2\x8b\x81" /* ∨ - bigvee */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMSY10,	"_"},
			{LSM_MATHML_FONT_CMEX10,	"W"}
		}
	},
	{
		"\xe2\x8b\x80" /* ∧  - bigwedge */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMSY10,	"^"},
			{LSM_MATHML_FONT_CMEX10,	"V"}
		}
	},
	{
		"\xe2\x88\xa8" /* ∨ */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMSY10,	"_"},
			{LSM_MATHML_FONT_CMEX10,	"W"}
		}
	},
	{
		"\xe2\x88\xa7" /* ∧ */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMSY10,	"^"},
			{LSM_MATHML_FONT_CMEX10,	"V"}
		}
	},
	{
		"\xe2\x88\xa9" /* ⋂ - cap*/,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMSY10,	"\\"},
			{LSM_MATHML_FONT_CMEX10,	"\\"}
		}
	},
	{
		"\xe2\x88\xaa" /* ⋃ - cup */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMSY10,	"["},
			{LSM_MATHML_FONT_CMEX10,	"["}
		}
	},
	{
		"\xe2\x8b\x82" /* ⋂ - bigcap */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMSY10,	"\\"},
			{LSM_MATHML_FONT_CMEX10,	"\\"}
		}
	},
	{
		"\xe2\x8b\x83" /* ⋃ - bigcup */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMSY10,	"["},
			{LSM_MATHML_FONT_CMEX10,	"["}
		}
	},
	{
		"\xe2\x88\xab" /* ∫ */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION |
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL |
		LSM_MATHML_GLYPH_FLAG_INTEGRAL_SLANT,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMEX10,	"R"},
			{LSM_MATHML_FONT_CMEX10,	"Z"}
		}
	},
	{
		"\xe2\x88\xac" /* ∬ */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION |
		LSM_MATHML_GLYPH_FLAG_INTEGRAL_SLANT,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMEX10,	"RR"},
			{LSM_MATHML_FONT_CMEX10,	"ZZ"}
		}
	},
	{
		"\xe2\x88\xad" /* ∭ */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION |
		LSM_MATHML_GLYPH_FLAG_INTEGRAL_SLANT,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMEX10,	"RRR"},
			{LSM_MATHML_FONT_CMEX10,	"ZZZ"}
		}
	},
	{
		"\xe2\x88\xae" /* ∮ */,
		LSM_MATHML_GLYPH_FLAG_ALIGN_AXIS | LSM_MATHML_GLYPH_FLAG_HAS_LARGE_VERSION |
		LSM_MATHML_GLYPH_FLAG_INTEGRAL_SLANT,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		2,
		{
			{LSM_MATHML_FONT_CMEX10,	"H"},
			{LSM_MATHML_FONT_CMEX10,	"I"}
		}
	},
	{
		"\xe2\x85\x86" /* d */,
		0,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_CMMI10,	"d"}
		}
	},
	{
		"\xe2\x85\x88" /* i */,
		0,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_CMMI10,	"i"}
		}
	},
	{
		"\xf0\x9d\x95\x9b" /* j */,
		0,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_CMMI10,	"j"}
		}
	},
	{
		"\xcc\xb2" /* _ */,
		LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_DEFAULT,	"\xcc\xb2"}
		}
	},
	{
		"\xc2\xaf" /* hor */,
		LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_DEFAULT,	"\xc2\xaf"}
		}
	},
	{
		"\xef\xb8\xb8" /* ︸ */,
		LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_DEFAULT,	"\xef\xb8\xb8"}
		}
	},
	{
		"\xef\xb8\xb7" /* ︷ */,
		LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_DEFAULT,	"\xef\xb8\xb7"}
		}
	},
	{
		"\xcd\x9c" /* ˜ */,
		LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		3,
		{
			{LSM_MATHML_FONT_CMEX10,	"e"},
			{LSM_MATHML_FONT_CMEX10,	"f"},
			{LSM_MATHML_FONT_CMEX10,	"g"}
		}
	},
	{
		"\xe2\x86\x92", /* → */
		LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_DEFAULT,	"\xe2\x86\x92"}
		}
	},
	{
		"\xe2\x86\x90", /* ← */
		LSM_MATHML_GLYPH_FLAG_STRETCH_HORIZONTAL,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_DEFAULT,	"\xe2\x86\x90"}
		}
	},
	{
		"\xe2\x86\x91", /* ↑ */
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_DEFAULT,	"\xe2\x86\x91"}
		}
	},
	{
		"\xe2\x86\x93", /* ↓ */
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_DEFAULT,	"\xe2\x86\x93"}
		}
	},
	{
		"-",
		0,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_DEFAULT,	"\xe2\x88\x92"}
		}
	},
	{
		"|",
		LSM_MATHML_GLYPH_FLAG_STRETCH_VERTICAL,
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		{LSM_MATHML_FONT_ERROR,		""},
		1,
		{
			{LSM_MATHML_FONT_DEFAULT,	"|"}
		}
	}
};

static GHashTable *
_get_glyph_table (void)
{
	static GHashTable *glyph_table = NULL;
	unsigned int i;

	if (glyph_table != NULL)
		return glyph_table;

	glyph_table = g_hash_table_new_full (g_str_hash, g_str_equal, NULL, NULL);

	for (i = 0; i < G_N_ELEMENTS (AMS_table); i++)
		g_hash_table_insert (glyph_table, (void *) AMS_table[i].utf8, (void *) &AMS_table[i]);

	return glyph_table;
}

const LsmMathmlOperatorGlyph *
lsm_mathml_glyph_table_find_operator_glyph (const char *text)
{
	return g_hash_table_lookup (_get_glyph_table (), text);
}

double
lsm_mathml_glyph_table_get_operator_slant (const char *text)
{
	const LsmMathmlOperatorGlyph *glyph;

	glyph = g_hash_table_lookup (_get_glyph_table (), text);

	if (glyph != NULL)
		if (glyph->flags & LSM_MATHML_GLYPH_FLAG_INTEGRAL_SLANT)
			return -12.0 / 180.0 * M_PI;

	return 0.0;
}
