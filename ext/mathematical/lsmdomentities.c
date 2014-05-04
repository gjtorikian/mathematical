/* Lasem
 *
 * Copyright © 2007-2012 Emmanuel Pacaud
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

#include <lsmdomentities.h>
#include <glib.h>
#include <stdio.h>

static const struct {
	const char *name;
	const char *utf8;
} lsm_dom_entities[] = {
	{"AElig",                 "\xc3\x86"                }, /* Æ [LATIN CAPITAL LETTER AE]*/
	{"Aacute",                "\xc3\x81"                }, /* Á [LATIN CAPITAL LETTER A WITH ACUTE]*/
	{"Abreve",                "\xc4\x82"                }, /* Ă [LATIN CAPITAL LETTER A WITH BREVE]*/
	{"Acirc",                 "\xc3\x82"                }, /* Â [LATIN CAPITAL LETTER A WITH CIRCUMFLEX]*/
	{"Acy",                   "\xd0\x90"                }, /* А [CYRILLIC CAPITAL LETTER A]*/
	{"Afr",                   "\xf0\x9d\x94\x84"        }, /* 𝔄 [MATHEMATICAL FRAKTUR CAPITAL A]*/
	{"Agrave",                "\xc3\x80"                }, /* À [LATIN CAPITAL LETTER A WITH GRAVE]*/
	{"Alpha",		  "\xce\x91"		    }, /* Α [GREEK CAPITAL LETTER ALPHA] */
	{"Amacr",                 "\xc4\x80"                }, /* Ā [LATIN CAPITAL LETTER A WITH MACRON]*/
	{"And",                   "\xe2\xa9\x93"            }, /* ⩓ [DOUBLE LOGICAL AND]*/
	{"Aogon",                 "\xc4\x84"                }, /* Ą [LATIN CAPITAL LETTER A WITH OGONEK]*/
	{"Aopf",                  "\xf0\x9d\x94\xb8"        }, /* 𝔸 [MATHEMATICAL DOUBLE-STRUCK CAPITAL A]*/
	{"ApplyFunction",         "\xe2\x81\xa1"            }, /* ⁡ [FUNCTION APPLICATION]*/
	{"Aring",                 "\xc3\x85"                }, /* Å [LATIN CAPITAL LETTER A WITH RING ABOVE]*/
	{"Ascr",                  "\xf0\x9d\x92\x9c"        }, /* 𝒜 [MATHEMATICAL SCRIPT CAPITAL A]*/
	{"Assign",                "\xe2\x89\x94"            }, /* ≔ [COLON EQUALS]*/
	{"Atilde",                "\xc3\x83"                }, /* Ã [LATIN CAPITAL LETTER A WITH TILDE]*/
	{"Auml",                  "\xc3\x84"                }, /* Ä [LATIN CAPITAL LETTER A WITH DIAERESIS]*/
	{"Backslash",             "\xe2\x88\x96"            }, /* ∖ [SET MINUS]*/
	{"Barv",                  "\xe2\xab\xa7"            }, /* ⫧ [SHORT DOWN TACK WITH OVERBAR]*/
	{"Barwed",                "\xe2\x8c\x86"            }, /* ⌆ [PERSPECTIVE]*/
	{"Bcy",                   "\xd0\x91"                }, /* Б [CYRILLIC CAPITAL LETTER BE]*/
	{"Because",               "\xe2\x88\xb5"            }, /* ∵ [BECAUSE]*/
	{"Bernoullis",            "\xe2\x84\xac"            }, /* ℬ [SCRIPT CAPITAL B]*/
	{"Beta",		  "\xce\x92"                }, /* Β [GREEK CAPITAL LETTER BETA] */
	{"Bfr",                   "\xf0\x9d\x94\x85"        }, /* 𝔅 [MATHEMATICAL FRAKTUR CAPITAL B]*/
	{"Bopf",                  "\xf0\x9d\x94\xb9"        }, /* 𝔹 [MATHEMATICAL DOUBLE-STRUCK CAPITAL B]*/
	{"Breve",                 "\xcb\x98"                }, /* ˘ [BREVE]*/
	{"Bscr",                  "\xe2\x84\xac"            }, /* ℬ [SCRIPT CAPITAL B]*/
	{"Bumpeq",                "\xe2\x89\x8e"            }, /* ≎ [GEOMETRICALLY EQUIVALENT TO]*/
	{"CHcy",                  "\xd0\xa7"                }, /* Ч [CYRILLIC CAPITAL LETTER CHE]*/
	{"Cacute",                "\xc4\x86"                }, /* Ć [LATIN CAPITAL LETTER C WITH ACUTE]*/
	{"Cap",                   "\xe2\x8b\x92"            }, /* ⋒ [DOUBLE INTERSECTION]*/
	{"CapitalDifferentialD",  "\xe2\x85\x85"            }, /* ⅅ [DOUBLE-STRUCK ITALIC CAPITAL D]*/
	{"Cayleys",               "\xe2\x84\xad"            }, /* ℭ [BLACK-LETTER CAPITAL C]*/
	{"Ccaron",                "\xc4\x8c"                }, /* Č [LATIN CAPITAL LETTER C WITH CARON]*/
	{"Ccedil",                "\xc3\x87"                }, /* Ç [LATIN CAPITAL LETTER C WITH CEDILLA]*/
	{"Ccirc",                 "\xc4\x88"                }, /* Ĉ [LATIN CAPITAL LETTER C WITH CIRCUMFLEX]*/
	{"Cconint",               "\xe2\x88\xb0"            }, /* ∰ [VOLUME INTEGRAL]*/
	{"Cdot",                  "\xc4\x8a"                }, /* Ċ [LATIN CAPITAL LETTER C WITH DOT ABOVE]*/
	{"Cedilla",               "\xc2\xb8"                }, /* ¸ [CEDILLA]*/
	{"CenterDot",             "\xc2\xb7"                }, /* · [MIDDLE DOT]*/
	{"Cfr",                   "\xe2\x84\xad"            }, /* ℭ [BLACK-LETTER CAPITAL C]*/
	{"CircleDot",             "\xe2\x8a\x99"            }, /* ⊙ [CIRCLED DOT OPERATOR]*/
	{"CircleMinus",           "\xe2\x8a\x96"            }, /* ⊖ [CIRCLED MINUS]*/
	{"CirclePlus",            "\xe2\x8a\x95"            }, /* ⊕ [CIRCLED PLUS]*/
	{"CircleTimes",           "\xe2\x8a\x97"            }, /* ⊗ [CIRCLED TIMES]*/
	{"ClockwiseContourIntegral","\xe2\x88\xb2"            }, /* ∲ [CLOCKWISE CONTOUR INTEGRAL]*/
	{"CloseCurlyDoubleQuote", "\xe2\x80\x9d"            }, /* ” [RIGHT DOUBLE QUOTATION MARK]*/
	{"CloseCurlyQuote",       "\xe2\x80\x99"            }, /* ’ [RIGHT SINGLE QUOTATION MARK]*/
	{"Colon",                 "\xe2\x88\xb7"            }, /* ∷ [PROPORTION]*/
	{"Colone",                "\xe2\xa9\xb4"            }, /* ⩴ [DOUBLE COLON EQUAL]*/
	{"Congruent",             "\xe2\x89\xa1"            }, /* ≡ [IDENTICAL TO]*/
	{"Conint",                "\xe2\x88\xaf"            }, /* ∯ [SURFACE INTEGRAL]*/
	{"ContourIntegral",       "\xe2\x88\xae"            }, /* ∮ [CONTOUR INTEGRAL]*/
	{"Copf",                  "\xe2\x84\x82"            }, /* ℂ [DOUBLE-STRUCK CAPITAL C]*/
	{"Coproduct",             "\xe2\x88\x90"            }, /* ∐ [N-ARY COPRODUCT]*/
	{"CounterClockwiseContourIntegral","\xe2\x88\xb3"            }, /* ∳ [ANTICLOCKWISE CONTOUR INTEGRAL]*/
	{"Cross",                 "\xe2\xa8\xaf"            }, /* ⨯ [VECTOR OR CROSS PRODUCT]*/
	{"Cscr",                  "\xf0\x9d\x92\x9e"        }, /* 𝒞 [MATHEMATICAL SCRIPT CAPITAL C]*/
	{"Cup",                   "\xe2\x8b\x93"            }, /* ⋓ [DOUBLE UNION]*/
	{"CupCap",                "\xe2\x89\x8d"            }, /* ≍ [EQUIVALENT TO]*/
	{"DD",                    "\xe2\x85\x85"            }, /* ⅅ [DOUBLE-STRUCK ITALIC CAPITAL D]*/
	{"DDotrahd",              "\xe2\xa4\x91"            }, /* ⤑ [RIGHTWARDS ARROW WITH DOTTED STEM]*/
	{"DJcy",                  "\xd0\x82"                }, /* Ђ [CYRILLIC CAPITAL LETTER DJE]*/
	{"DScy",                  "\xd0\x85"                }, /* Ѕ [CYRILLIC CAPITAL LETTER DZE]*/
	{"DZcy",                  "\xd0\x8f"                }, /* Џ [CYRILLIC CAPITAL LETTER DZHE]*/
	{"Dagger",                "\xe2\x80\xa1"            }, /* ‡ [DOUBLE DAGGER]*/
	{"Dagger",                "\xe2\x80\xa1"            }, /* ‡ [DOUBLE DAGGER]*/
	{"Darr",                  "\xe2\x86\xa1"            }, /* ↡ [DOWNWARDS TWO HEADED ARROW]*/
	{"Dashv",                 "\xe2\xab\xa4"            }, /* ⫤ [VERTICAL BAR DOUBLE LEFT TURNSTILE]*/
	{"Dcaron",                "\xc4\x8e"                }, /* Ď [LATIN CAPITAL LETTER D WITH CARON]*/
	{"Dcy",                   "\xd0\x94"                }, /* Д [CYRILLIC CAPITAL LETTER DE]*/
	{"Del",                   "\xe2\x88\x87"            }, /* ∇ [NABLA]*/
	{"Delta",                 "\xce\x94"                }, /* Δ [GREEK CAPITAL LETTER DELTA]*/
	{"Dfr",                   "\xf0\x9d\x94\x87"        }, /* 𝔇 [MATHEMATICAL FRAKTUR CAPITAL D]*/
	{"DiacriticalAcute",      "\xc2\xb4"                }, /* ´ [ACUTE ACCENT]*/
	{"DiacriticalDot",        "\xcb\x99"                }, /* ˙ [DOT ABOVE]*/
	{"DiacriticalDoubleAcute","\xcb\x9d"                }, /* ˝ [DOUBLE ACUTE ACCENT]*/
	{"DiacriticalGrave",      "\x60"                    }, /* ` [GRAVE ACCENT]*/
	{"DiacriticalTilde",      "\xcb\x9c"                }, /* ˜ [SMALL TILDE]*/
	{"Diamond",               "\xe2\x8b\x84"            }, /* ⋄ [DIAMOND OPERATOR]*/
	{"DifferentialD",         "\xe2\x85\x86"            }, /* ⅆ [DOUBLE-STRUCK ITALIC SMALL D]*/
	{"Dopf",                  "\xf0\x9d\x94\xbb"        }, /* 𝔻 [MATHEMATICAL DOUBLE-STRUCK CAPITAL D]*/
	{"Dot",                   "\xc2\xa8"                }, /* ¨ [DIAERESIS]*/
	{"DotDot",                "\xe2\x83\x9c"            }, /* ⃜ [COMBINING FOUR DOTS ABOVE]*/
	{"DotEqual",              "\xe2\x89\x90"            }, /* ≐ [APPROACHES THE LIMIT]*/
	{"DoubleContourIntegral", "\xe2\x88\xaf"            }, /* ∯ [SURFACE INTEGRAL]*/
	{"DoubleDot",             "\xc2\xa8"                }, /* ¨ [DIAERESIS]*/
	{"DoubleDownArrow",       "\xe2\x87\x93"            }, /* ⇓ [DOWNWARDS DOUBLE ARROW]*/
	{"DoubleLeftArrow",       "\xe2\x87\x90"            }, /* ⇐ [LEFTWARDS DOUBLE ARROW]*/
	{"DoubleLeftRightArrow",  "\xe2\x87\x94"            }, /* ⇔ [LEFT RIGHT DOUBLE ARROW]*/
	{"DoubleLeftTee",         "\xe2\xab\xa4"            }, /* ⫤ [VERTICAL BAR DOUBLE LEFT TURNSTILE]*/
	{"DoubleLongLeftArrow",   "\xe2\x9f\xb8"            }, /* ⟸ [LONG LEFTWARDS DOUBLE ARROW]*/
	{"DoubleLongLeftRightArrow","\xe2\x9f\xba"            }, /* ⟺ [LONG LEFT RIGHT DOUBLE ARROW]*/
	{"DoubleLongRightArrow",  "\xe2\x9f\xb9"            }, /* ⟹ [LONG RIGHTWARDS DOUBLE ARROW]*/
	{"DoubleRightArrow",      "\xe2\x87\x92"            }, /* ⇒ [RIGHTWARDS DOUBLE ARROW]*/
	{"DoubleRightTee",        "\xe2\x8a\xa8"            }, /* ⊨ [TRUE]*/
	{"DoubleUpArrow",         "\xe2\x87\x91"            }, /* ⇑ [UPWARDS DOUBLE ARROW]*/
	{"DoubleUpDownArrow",     "\xe2\x87\x95"            }, /* ⇕ [UP DOWN DOUBLE ARROW]*/
	{"DoubleVerticalBar",     "\xe2\x88\xa5"            }, /* ∥ [PARALLEL TO]*/
	{"DownArrow",             "\xe2\x86\x93"            }, /* ↓ [DOWNWARDS ARROW]*/
	{"DownArrowBar",          "\xe2\xa4\x93"            }, /* ⤓ [DOWNWARDS ARROW TO BAR]*/
	{"DownArrowUpArrow",      "\xe2\x87\xb5"            }, /* ⇵ [DOWNWARDS ARROW LEFTWARDS OF UPWARDS ARROW]*/
	{"DownBreve",             "\xcc\x91"                }, /* ̑ [COMBINING INVERTED BREVE]*/
	{"DownLeftRightVector",   "\xe2\xa5\x90"            }, /* ⥐ [LEFT BARB DOWN RIGHT BARB DOWN HARPOON]*/
	{"DownLeftTeeVector",     "\xe2\xa5\x9e"            }, /* ⥞ [LEFTWARDS HARPOON WITH BARB DOWN FROM BAR]*/
	{"DownLeftVector",        "\xe2\x86\xbd"            }, /* ↽ [LEFTWARDS HARPOON WITH BARB DOWNWARDS]*/
	{"DownLeftVectorBar",     "\xe2\xa5\x96"            }, /* ⥖ [LEFTWARDS HARPOON WITH BARB DOWN TO BAR]*/
	{"DownRightTeeVector",    "\xe2\xa5\x9f"            }, /* ⥟ [RIGHTWARDS HARPOON WITH BARB DOWN FROM BAR]*/
	{"DownRightVector",       "\xe2\x87\x81"            }, /* ⇁ [RIGHTWARDS HARPOON WITH BARB DOWNWARDS]*/
	{"DownRightVectorBar",    "\xe2\xa5\x97"            }, /* ⥗ [RIGHTWARDS HARPOON WITH BARB DOWN TO BAR]*/
	{"DownTee",               "\xe2\x8a\xa4"            }, /* ⊤ [DOWN TACK]*/
	{"DownTeeArrow",          "\xe2\x86\xa7"            }, /* ↧ [DOWNWARDS ARROW FROM BAR]*/
	{"Downarrow",             "\xe2\x87\x93"            }, /* ⇓ [DOWNWARDS DOUBLE ARROW]*/
	{"Dscr",                  "\xf0\x9d\x92\x9f"        }, /* 𝒟 [MATHEMATICAL SCRIPT CAPITAL D]*/
	{"Dstrok",                "\xc4\x90"                }, /* Đ [LATIN CAPITAL LETTER D WITH STROKE]*/
	{"ENG",                   "\xc5\x8a"                }, /* Ŋ [LATIN CAPITAL LETTER ENG]*/
	{"ETH",                   "\xc3\x90"                }, /* Ð [LATIN CAPITAL LETTER ETH]*/
	{"Eacute",                "\xc3\x89"                }, /* É [LATIN CAPITAL LETTER E WITH ACUTE]*/
	{"Ecaron",                "\xc4\x9a"                }, /* Ě [LATIN CAPITAL LETTER E WITH CARON]*/
	{"Ecirc",                 "\xc3\x8a"                }, /* Ê [LATIN CAPITAL LETTER E WITH CIRCUMFLEX]*/
	{"Ecy",                   "\xd0\xad"                }, /* Э [CYRILLIC CAPITAL LETTER E]*/
	{"Edot",                  "\xc4\x96"                }, /* Ė [LATIN CAPITAL LETTER E WITH DOT ABOVE]*/
	{"Efr",                   "\xf0\x9d\x94\x88"        }, /* 𝔈 [MATHEMATICAL FRAKTUR CAPITAL E]*/
	{"Egrave",                "\xc3\x88"                }, /* È [LATIN CAPITAL LETTER E WITH GRAVE]*/
	{"Element",               "\xe2\x88\x88"            }, /* ∈ [ELEMENT OF]*/
	{"Emacr",                 "\xc4\x92"                }, /* Ē [LATIN CAPITAL LETTER E WITH MACRON]*/
	{"EmptySmallSquare",      "\xe2\x97\xbb"            }, /* ◻ [WHITE MEDIUM SQUARE]*/
	{"EmptyVerySmallSquare",  "\xe2\x96\xab"            }, /* ▫ [WHITE SMALL SQUARE]*/
	{"Eogon",                 "\xc4\x98"                }, /* Ę [LATIN CAPITAL LETTER E WITH OGONEK]*/
	{"Eopf",                  "\xf0\x9d\x94\xbc"        }, /* 𝔼 [MATHEMATICAL DOUBLE-STRUCK CAPITAL E]*/
	{"Epsilon",               "\xce\x95"                }, /* Ε [GREEK CAPITAL LETTER EPSILON] */
	{"Equal",                 "\xe2\xa9\xb5"            }, /* ⩵ [TWO CONSECUTIVE EQUALS SIGNS]*/
	{"EqualTilde",            "\xe2\x89\x82"            }, /* ≂ [MINUS TILDE]*/
	{"Equilibrium",           "\xe2\x87\x8c"            }, /* ⇌ [RIGHTWARDS HARPOON OVER LEFTWARDS HARPOON]*/
	{"Escr",                  "\xe2\x84\xb0"            }, /* ℰ [SCRIPT CAPITAL E]*/
	{"Esim",                  "\xe2\xa9\xb3"            }, /* ⩳ [EQUALS SIGN ABOVE TILDE OPERATOR]*/
	{"Eta",                   "\xce\x97"                }, /* Η [GREEK CAPITAL LETTER ETA] */
	{"Euml",                  "\xc3\x8b"                }, /* Ë [LATIN CAPITAL LETTER E WITH DIAERESIS]*/
	{"Exists",                "\xe2\x88\x83"            }, /* ∃ [THERE EXISTS]*/
	{"ExponentialE",          "\xe2\x85\x87"            }, /* ⅇ [DOUBLE-STRUCK ITALIC SMALL E]*/
	{"Fcy",                   "\xd0\xa4"                }, /* Ф [CYRILLIC CAPITAL LETTER EF]*/
	{"Ffr",                   "\xf0\x9d\x94\x89"        }, /* 𝔉 [MATHEMATICAL FRAKTUR CAPITAL F]*/
	{"FilledSmallSquare",     "\xe2\x97\xbc"            }, /* ◼ [BLACK MEDIUM SQUARE]*/
	{"FilledVerySmallSquare", "\xe2\x96\xaa"            }, /* ▪ [BLACK SMALL SQUARE]*/
	{"Fopf",                  "\xf0\x9d\x94\xbd"        }, /* 𝔽 [MATHEMATICAL DOUBLE-STRUCK CAPITAL F]*/
	{"ForAll",                "\xe2\x88\x80"            }, /* ∀ [FOR ALL]*/
	{"Fouriertrf",            "\xe2\x84\xb1"            }, /* ℱ [SCRIPT CAPITAL F]*/
	{"Fscr",                  "\xe2\x84\xb1"            }, /* ℱ [SCRIPT CAPITAL F]*/
	{"GJcy",                  "\xd0\x83"                }, /* Ѓ [CYRILLIC CAPITAL LETTER GJE]*/
	{"Gamma",                 "\xce\x93"                }, /* Γ [GREEK CAPITAL LETTER GAMMA]*/
	{"Gammad",                "\xcf\x9c"                }, /* Ϝ [GREEK LETTER DIGAMMA]*/
	{"Gbreve",                "\xc4\x9e"                }, /* Ğ [LATIN CAPITAL LETTER G WITH BREVE]*/
	{"Gcedil",                "\xc4\xa2"                }, /* Ģ [LATIN CAPITAL LETTER G WITH CEDILLA]*/
	{"Gcirc",                 "\xc4\x9c"                }, /* Ĝ [LATIN CAPITAL LETTER G WITH CIRCUMFLEX]*/
	{"Gcy",                   "\xd0\x93"                }, /* Г [CYRILLIC CAPITAL LETTER GHE]*/
	{"Gdot",                  "\xc4\xa0"                }, /* Ġ [LATIN CAPITAL LETTER G WITH DOT ABOVE]*/
	{"Gfr",                   "\xf0\x9d\x94\x8a"        }, /* 𝔊 [MATHEMATICAL FRAKTUR CAPITAL G]*/
	{"Gg",                    "\xe2\x8b\x99"            }, /* ⋙ [VERY MUCH GREATER-THAN]*/
	{"Gopf",                  "\xf0\x9d\x94\xbe"        }, /* 𝔾 [MATHEMATICAL DOUBLE-STRUCK CAPITAL G]*/
	{"GreaterEqual",          "\xe2\x89\xa5"            }, /* ≥ [GREATER-THAN OR EQUAL TO]*/
	{"GreaterEqualLess",      "\xe2\x8b\x9b"            }, /* ⋛ [GREATER-THAN EQUAL TO OR LESS-THAN]*/
	{"GreaterFullEqual",      "\xe2\x89\xa7"            }, /* ≧ [GREATER-THAN OVER EQUAL TO]*/
	{"GreaterGreater",        "\xe2\xaa\xa2"            }, /* ⪢ [DOUBLE NESTED GREATER-THAN]*/
	{"GreaterLess",           "\xe2\x89\xb7"            }, /* ≷ [GREATER-THAN OR LESS-THAN]*/
	{"GreaterSlantEqual",     "\xe2\xa9\xbe"            }, /* ⩾ [GREATER-THAN OR SLANTED EQUAL TO]*/
	{"GreaterTilde",          "\xe2\x89\xb3"            }, /* ≳ [GREATER-THAN OR EQUIVALENT TO]*/
	{"Gscr",                  "\xf0\x9d\x92\xa2"        }, /* 𝒢 [MATHEMATICAL SCRIPT CAPITAL G]*/
	{"Gt",                    "\xe2\x89\xab"            }, /* ≫ [MUCH GREATER-THAN]*/
	{"HARDcy",                "\xd0\xaa"                }, /* Ъ [CYRILLIC CAPITAL LETTER HARD SIGN]*/
	{"Hacek",                 "\xcb\x87"                }, /* ˇ [CARON]*/
	{"Hat",                   "\x5e"                    }, /* ^ [CIRCUMFLEX ACCENT]*/
	{"Hcirc",                 "\xc4\xa4"                }, /* Ĥ [LATIN CAPITAL LETTER H WITH CIRCUMFLEX]*/
	{"Hfr",                   "\xe2\x84\x8c"            }, /* ℌ [BLACK-LETTER CAPITAL H]*/
	{"HilbertSpace",          "\xe2\x84\x8b"            }, /* ℋ [SCRIPT CAPITAL H]*/
	{"Hopf",                  "\xe2\x84\x8d"            }, /* ℍ [DOUBLE-STRUCK CAPITAL H]*/
	{"HorizontalLine",        "\xe2\x94\x80"            }, /* ─ [BOX DRAWINGS LIGHT HORIZONTAL]*/
	{"Hscr",                  "\xe2\x84\x8b"            }, /* ℋ [SCRIPT CAPITAL H]*/
	{"Hstrok",                "\xc4\xa6"                }, /* Ħ [LATIN CAPITAL LETTER H WITH STROKE]*/
	{"HumpDownHump",          "\xe2\x89\x8e"            }, /* ≎ [GEOMETRICALLY EQUIVALENT TO]*/
	{"HumpEqual",             "\xe2\x89\x8f"            }, /* ≏ [DIFFERENCE BETWEEN]*/
	{"IEcy",                  "\xd0\x95"                }, /* Е [CYRILLIC CAPITAL LETTER IE]*/
	{"IJlig",                 "\xc4\xb2"                }, /* Ĳ [LATIN CAPITAL LIGATURE IJ]*/
	{"IOcy",                  "\xd0\x81"                }, /* Ё [CYRILLIC CAPITAL LETTER IO]*/
	{"Iacute",                "\xc3\x8d"                }, /* Í [LATIN CAPITAL LETTER I WITH ACUTE]*/
	{"Icirc",                 "\xc3\x8e"                }, /* Î [LATIN CAPITAL LETTER I WITH CIRCUMFLEX]*/
	{"Icy",                   "\xd0\x98"                }, /* И [CYRILLIC CAPITAL LETTER I]*/
	{"Idot",                  "\xc4\xb0"                }, /* İ [LATIN CAPITAL LETTER I WITH DOT ABOVE]*/
	{"Ifr",                   "\xe2\x84\x91"            }, /* ℑ [BLACK-LETTER CAPITAL I]*/
	{"Igrave",                "\xc3\x8c"                }, /* Ì [LATIN CAPITAL LETTER I WITH GRAVE]*/
	{"Im",                    "\xe2\x84\x91"            }, /* ℑ [BLACK-LETTER CAPITAL I]*/
	{"Imacr",                 "\xc4\xaa"                }, /* Ī [LATIN CAPITAL LETTER I WITH MACRON]*/
	{"ImaginaryI",            "\xe2\x85\x88"            }, /* ⅈ [DOUBLE-STRUCK ITALIC SMALL I]*/
	{"Implies",               "\xe2\x87\x92"            }, /* ⇒ [RIGHTWARDS DOUBLE ARROW]*/
	{"Int",                   "\xe2\x88\xac"            }, /* ∬ [DOUBLE INTEGRAL]*/
	{"Integral",              "\xe2\x88\xab"            }, /* ∫ [INTEGRAL]*/
	{"Intersection",          "\xe2\x8b\x82"            }, /* ⋂ [N-ARY INTERSECTION]*/
	{"InvisibleComma",        "\xe2\x81\xa3"            }, /* ⁣ [INVISIBLE SEPARATOR]*/
	{"InvisibleTimes",        "\xe2\x81\xa2"            }, /* ⁢ [INVISIBLE TIMES]*/
	{"Iogon",                 "\xc4\xae"                }, /* Į [LATIN CAPITAL LETTER I WITH OGONEK]*/
	{"Iopf",                  "\xf0\x9d\x95\x80"        }, /* 𝕀 [MATHEMATICAL DOUBLE-STRUCK CAPITAL I]*/
	{"Iota",                  "\xce\x99"                }, /* Ι [GREEK CAPITAL LETTER IOTA] */
	{"Iscr",                  "\xe2\x84\x90"            }, /* ℐ [SCRIPT CAPITAL I]*/
	{"Itilde",                "\xc4\xa8"                }, /* Ĩ [LATIN CAPITAL LETTER I WITH TILDE]*/
	{"Iukcy",                 "\xd0\x86"                }, /* І [CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I]*/
	{"Iuml",                  "\xc3\x8f"                }, /* Ï [LATIN CAPITAL LETTER I WITH DIAERESIS]*/
	{"Jcirc",                 "\xc4\xb4"                }, /* Ĵ [LATIN CAPITAL LETTER J WITH CIRCUMFLEX]*/
	{"Jcy",                   "\xd0\x99"                }, /* Й [CYRILLIC CAPITAL LETTER SHORT I]*/
	{"Jfr",                   "\xf0\x9d\x94\x8d"        }, /* 𝔍 [MATHEMATICAL FRAKTUR CAPITAL J]*/
	{"Jopf",                  "\xf0\x9d\x95\x81"        }, /* 𝕁 [MATHEMATICAL DOUBLE-STRUCK CAPITAL J]*/
	{"Jscr",                  "\xf0\x9d\x92\xa5"        }, /* 𝒥 [MATHEMATICAL SCRIPT CAPITAL J]*/
	{"Jsercy",                "\xd0\x88"                }, /* Ј [CYRILLIC CAPITAL LETTER JE]*/
	{"Jukcy",                 "\xd0\x84"                }, /* Є [CYRILLIC CAPITAL LETTER UKRAINIAN IE]*/
	{"Kappa",                 "\xce\x9a"                }, /* Κ [GREEK CAPITAL LETTER KAPPA] */
	{"KHcy",                  "\xd0\xa5"                }, /* Х [CYRILLIC CAPITAL LETTER HA]*/
	{"KJcy",                  "\xd0\x8c"                }, /* Ќ [CYRILLIC CAPITAL LETTER KJE]*/
	{"Kcedil",                "\xc4\xb6"                }, /* Ķ [LATIN CAPITAL LETTER K WITH CEDILLA]*/
	{"Kcy",                   "\xd0\x9a"                }, /* К [CYRILLIC CAPITAL LETTER KA]*/
	{"Kfr",                   "\xf0\x9d\x94\x8e"        }, /* 𝔎 [MATHEMATICAL FRAKTUR CAPITAL K]*/
	{"Kopf",                  "\xf0\x9d\x95\x82"        }, /* 𝕂 [MATHEMATICAL DOUBLE-STRUCK CAPITAL K]*/
	{"Kscr",                  "\xf0\x9d\x92\xa6"        }, /* 𝒦 [MATHEMATICAL SCRIPT CAPITAL K]*/
	{"LJcy",                  "\xd0\x89"                }, /* Љ [CYRILLIC CAPITAL LETTER LJE]*/
	{"Lacute",                "\xc4\xb9"                }, /* Ĺ [LATIN CAPITAL LETTER L WITH ACUTE]*/
	{"Lambda",                "\xce\x9b"                }, /* Λ [GREEK CAPITAL LETTER LAMDA]*/
	{"Lang",                  "\xe3\x80\x8a"            }, /* 《 [LEFT DOUBLE ANGLE BRACKET]*/
	{"Laplacetrf",            "\xe2\x84\x92"            }, /* ℒ [SCRIPT CAPITAL L]*/
	{"Larr",                  "\xe2\x86\x9e"            }, /* ↞ [LEFTWARDS TWO HEADED ARROW]*/
	{"Lcaron",                "\xc4\xbd"                }, /* Ľ [LATIN CAPITAL LETTER L WITH CARON]*/
	{"Lcedil",                "\xc4\xbb"                }, /* Ļ [LATIN CAPITAL LETTER L WITH CEDILLA]*/
	{"Lcy",                   "\xd0\x9b"                }, /* Л [CYRILLIC CAPITAL LETTER EL]*/
	{"LeftAngleBracket",      "\xe2\x8c\xa9"            }, /* 〈 [LEFT-POINTING ANGLE BRACKET]*/
	{"LeftArrow",             "\xe2\x86\x90"            }, /* ← [LEFTWARDS ARROW]*/
	{"LeftArrowBar",          "\xe2\x87\xa4"            }, /* ⇤ [LEFTWARDS ARROW TO BAR]*/
	{"LeftArrowRightArrow",   "\xe2\x87\x86"            }, /* ⇆ [LEFTWARDS ARROW OVER RIGHTWARDS ARROW]*/
	{"LeftCeiling",           "\xe2\x8c\x88"            }, /* ⌈ [LEFT CEILING]*/
	{"LeftDoubleBracket",     "\xe3\x80\x9a"            }, /* 〚 [LEFT WHITE SQUARE BRACKET]*/
	{"LeftDownTeeVector",     "\xe2\xa5\xa1"            }, /* ⥡ [DOWNWARDS HARPOON WITH BARB LEFT FROM BAR]*/
	{"LeftDownVector",        "\xe2\x87\x83"            }, /* ⇃ [DOWNWARDS HARPOON WITH BARB LEFTWARDS]*/
	{"LeftDownVectorBar",     "\xe2\xa5\x99"            }, /* ⥙ [DOWNWARDS HARPOON WITH BARB LEFT TO BAR]*/
	{"LeftFloor",             "\xe2\x8c\x8a"            }, /* ⌊ [LEFT FLOOR]*/
	{"LeftRightArrow",        "\xe2\x86\x94"            }, /* ↔ [LEFT RIGHT ARROW]*/
	{"LeftRightVector",       "\xe2\xa5\x8e"            }, /* ⥎ [LEFT BARB UP RIGHT BARB UP HARPOON]*/
	{"LeftTee",               "\xe2\x8a\xa3"            }, /* ⊣ [LEFT TACK]*/
	{"LeftTeeArrow",          "\xe2\x86\xa4"            }, /* ↤ [LEFTWARDS ARROW FROM BAR]*/
	{"LeftTeeVector",         "\xe2\xa5\x9a"            }, /* ⥚ [LEFTWARDS HARPOON WITH BARB UP FROM BAR]*/
	{"LeftTriangle",          "\xe2\x8a\xb2"            }, /* ⊲ [NORMAL SUBGROUP OF]*/
	{"LeftTriangleBar",       "\xe2\xa7\x8f"            }, /* ⧏ [LEFT TRIANGLE BESIDE VERTICAL BAR]*/
	{"LeftTriangleEqual",     "\xe2\x8a\xb4"            }, /* ⊴ [NORMAL SUBGROUP OF OR EQUAL TO]*/
	{"LeftUpDownVector",      "\xe2\xa5\x91"            }, /* ⥑ [UP BARB LEFT DOWN BARB LEFT HARPOON]*/
	{"LeftUpTeeVector",       "\xe2\xa5\xa0"            }, /* ⥠ [UPWARDS HARPOON WITH BARB LEFT FROM BAR]*/
	{"LeftUpVector",          "\xe2\x86\xbf"            }, /* ↿ [UPWARDS HARPOON WITH BARB LEFTWARDS]*/
	{"LeftUpVectorBar",       "\xe2\xa5\x98"            }, /* ⥘ [UPWARDS HARPOON WITH BARB LEFT TO BAR]*/
	{"LeftVector",            "\xe2\x86\xbc"            }, /* ↼ [LEFTWARDS HARPOON WITH BARB UPWARDS]*/
	{"LeftVectorBar",         "\xe2\xa5\x92"            }, /* ⥒ [LEFTWARDS HARPOON WITH BARB UP TO BAR]*/
	{"Leftarrow",             "\xe2\x87\x90"            }, /* ⇐ [LEFTWARDS DOUBLE ARROW]*/
	{"Leftrightarrow",        "\xe2\x87\x94"            }, /* ⇔ [LEFT RIGHT DOUBLE ARROW]*/
	{"LessEqualGreater",      "\xe2\x8b\x9a"            }, /* ⋚ [LESS-THAN EQUAL TO OR GREATER-THAN]*/
	{"LessFullEqual",         "\xe2\x89\xa6"            }, /* ≦ [LESS-THAN OVER EQUAL TO]*/
	{"LessGreater",           "\xe2\x89\xb6"            }, /* ≶ [LESS-THAN OR GREATER-THAN]*/
	{"LessLess",              "\xe2\xaa\xa1"            }, /* ⪡ [DOUBLE NESTED LESS-THAN]*/
	{"LessSlantEqual",        "\xe2\xa9\xbd"            }, /* ⩽ [LESS-THAN OR SLANTED EQUAL TO]*/
	{"LessTilde",             "\xe2\x89\xb2"            }, /* ≲ [LESS-THAN OR EQUIVALENT TO]*/
	{"Lfr",                   "\xf0\x9d\x94\x8f"        }, /* 𝔏 [MATHEMATICAL FRAKTUR CAPITAL L]*/
	{"Ll",                    "\xe2\x8b\x98"            }, /* ⋘ [VERY MUCH LESS-THAN]*/
	{"Lleftarrow",            "\xe2\x87\x9a"            }, /* ⇚ [LEFTWARDS TRIPLE ARROW]*/
	{"Lmidot",                "\xc4\xbf"                }, /* Ŀ [LATIN CAPITAL LETTER L WITH MIDDLE DOT]*/
	{"LongLeftArrow",         "\xe2\x9f\xb5"            }, /* ⟵ [LONG LEFTWARDS ARROW]*/
	{"LongLeftRightArrow",    "\xe2\x9f\xb7"            }, /* ⟷ [LONG LEFT RIGHT ARROW]*/
	{"LongRightArrow",        "\xe2\x9f\xb6"            }, /* ⟶ [LONG RIGHTWARDS ARROW]*/
	{"Longleftarrow",         "\xe2\x9f\xb8"            }, /* ⟸ [LONG LEFTWARDS DOUBLE ARROW]*/
	{"Longleftrightarrow",    "\xe2\x9f\xba"            }, /* ⟺ [LONG LEFT RIGHT DOUBLE ARROW]*/
	{"Longrightarrow",        "\xe2\x9f\xb9"            }, /* ⟹ [LONG RIGHTWARDS DOUBLE ARROW]*/
	{"Lopf",                  "\xf0\x9d\x95\x83"        }, /* 𝕃 [MATHEMATICAL DOUBLE-STRUCK CAPITAL L]*/
	{"LowerLeftArrow",        "\xe2\x86\x99"            }, /* ↙ [SOUTH WEST ARROW]*/
	{"LowerRightArrow",       "\xe2\x86\x98"            }, /* ↘ [SOUTH EAST ARROW]*/
	{"Lscr",                  "\xe2\x84\x92"            }, /* ℒ [SCRIPT CAPITAL L]*/
	{"Lsh",                   "\xe2\x86\xb0"            }, /* ↰ [UPWARDS ARROW WITH TIP LEFTWARDS]*/
	{"Lstrok",                "\xc5\x81"                }, /* Ł [LATIN CAPITAL LETTER L WITH STROKE]*/
	{"Lt",                    "\xe2\x89\xaa"            }, /* ≪ [MUCH LESS-THAN]*/
	{"Map",                   "\xe2\xa4\x85"            }, /* ⤅ [RIGHTWARDS TWO-HEADED ARROW FROM BAR]*/
	{"Mcy",                   "\xd0\x9c"                }, /* М [CYRILLIC CAPITAL LETTER EM]*/
	{"MediumSpace",           "\xe2\x81\x9f"            }, /*   [MEDIUM MATHEMATICAL SPACE]*/
	{"Mellintrf",             "\xe2\x84\xb3"            }, /* ℳ [SCRIPT CAPITAL M]*/
	{"Mfr",                   "\xf0\x9d\x94\x90"        }, /* 𝔐 [MATHEMATICAL FRAKTUR CAPITAL M]*/
	{"MinusPlus",             "\xe2\x88\x93"            }, /* ∓ [MINUS-OR-PLUS SIGN]*/
	{"Mopf",                  "\xf0\x9d\x95\x84"        }, /* 𝕄 [MATHEMATICAL DOUBLE-STRUCK CAPITAL M]*/
	{"Mu",                    "\xce\x9c"                }, /* Μ [GREEK CAPITAL LETTER MU] */
	{"Mscr",                  "\xe2\x84\xb3"            }, /* ℳ [SCRIPT CAPITAL M]*/
	{"NJcy",                  "\xd0\x8a"                }, /* Њ [CYRILLIC CAPITAL LETTER NJE]*/
	{"Nacute",                "\xc5\x83"                }, /* Ń [LATIN CAPITAL LETTER N WITH ACUTE]*/
	{"Ncaron",                "\xc5\x87"                }, /* Ň [LATIN CAPITAL LETTER N WITH CARON]*/
	{"Ncedil",                "\xc5\x85"                }, /* Ņ [LATIN CAPITAL LETTER N WITH CEDILLA]*/
	{"Ncy",                   "\xd0\x9d"                }, /* Н [CYRILLIC CAPITAL LETTER EN]*/
	{"NegativeMediumSpace",   "\xe2\x80\x8b"            }, /* ​ [ZERO WIDTH SPACE]*/
	{"NegativeThickSpace",    "\xe2\x80\x8b"            }, /* ​ [ZERO WIDTH SPACE]*/
	{"NegativeThinSpace",     "\xe2\x80\x8b"            }, /* ​ [ZERO WIDTH SPACE]*/
	{"NegativeVeryThinSpace", "\xe2\x80\x8b"            }, /* ​ [ZERO WIDTH SPACE]*/
	{"NestedGreaterGreater",  "\xe2\x89\xab"            }, /* ≫ [MUCH GREATER-THAN]*/
	{"NestedLessLess",        "\xe2\x89\xaa"            }, /* ≪ [MUCH LESS-THAN]*/
	{"NewLine",               "\xa"                     }, /* 
 [LINE FEED (LF)]*/
	{"Nfr",                   "\xf0\x9d\x94\x91"        }, /* 𝔑 [MATHEMATICAL FRAKTUR CAPITAL N]*/
	{"NoBreak",               "\xe2\x81\xa0"            }, /* ⁠ [WORD JOINER]*/
	{"NonBreakingSpace",      "\xc2\xa0"                }, /*   [NO-BREAK SPACE]*/
	{"Nopf",                  "\xe2\x84\x95"            }, /* ℕ [DOUBLE-STRUCK CAPITAL N]*/
	{"Not",                   "\xe2\xab\xac"            }, /* ⫬ [DOUBLE STROKE NOT SIGN]*/
	{"NotCongruent",          "\xe2\x89\xa2"            }, /* ≢ [NOT IDENTICAL TO]*/
	{"NotCupCap",             "\xe2\x89\xad"            }, /* ≭ [NOT EQUIVALENT TO]*/
	{"NotDoubleVerticalBar",  "\xe2\x88\xa6"            }, /* ∦ [NOT PARALLEL TO]*/
	{"NotElement",            "\xe2\x88\x89"            }, /* ∉ [NOT AN ELEMENT OF]*/
	{"NotEqual",              "\xe2\x89\xa0"            }, /* ≠ [NOT EQUAL TO]*/
	{"NotEqualTilde",         "\xe2\x89\x82\xcc\xb8"    }, /* ≂̸ [MINUS TILDE with slash]*/
	{"NotExists",             "\xe2\x88\x84"            }, /* ∄ [THERE DOES NOT EXIST]*/
	{"NotGreater",            "\xe2\x89\xaf"            }, /* ≯ [NOT GREATER-THAN]*/
	{"NotGreaterEqual",       "\xe2\x89\xb1"            }, /* ≱ [NEITHER GREATER-THAN NOR EQUAL TO]*/
	{"NotGreaterFullEqual",   "\xe2\x89\xa6\xcc\xb8"    }, /* ≦̸ [LESS-THAN OVER EQUAL TO with slash]*/
	{"NotGreaterGreater",     "\xe2\x89\xab\xcc\xb8"    }, /* ≫̸ [MUCH GREATER THAN with slash]*/
	{"NotGreaterLess",        "\xe2\x89\xb9"            }, /* ≹ [NEITHER GREATER-THAN NOR LESS-THAN]*/
	{"NotGreaterSlantEqual",  "\xe2\xa9\xbe\xcc\xb8"    }, /* ⩾̸ [GREATER-THAN OR SLANTED EQUAL TO with slash]*/
	{"NotGreaterTilde",       "\xe2\x89\xb5"            }, /* ≵ [NEITHER GREATER-THAN NOR EQUIVALENT TO]*/
	{"NotHumpDownHump",       "\xe2\x89\x8e\xcc\xb8"    }, /* ≎̸ [GEOMETRICALLY EQUIVALENT TO with slash]*/
	{"NotHumpEqual",          "\xe2\x89\x8f\xcc\xb8"    }, /* ≏̸ [DIFFERENCE BETWEEN with slash]*/
	{"NotLeftTriangle",       "\xe2\x8b\xaa"            }, /* ⋪ [NOT NORMAL SUBGROUP OF]*/
	{"NotLeftTriangleBar",    "\xe2\xa7\x8f\xcc\xb8"    }, /* ⧏̸ [LEFT TRIANGLE BESIDE VERTICAL BAR with slash]*/
	{"NotLeftTriangleEqual",  "\xe2\x8b\xac"            }, /* ⋬ [NOT NORMAL SUBGROUP OF OR EQUAL TO]*/
	{"NotLess",               "\xe2\x89\xae"            }, /* ≮ [NOT LESS-THAN]*/
	{"NotLessEqual",          "\xe2\x89\xb0"            }, /* ≰ [NEITHER LESS-THAN NOR EQUAL TO]*/
	{"NotLessGreater",        "\xe2\x89\xb8"            }, /* ≸ [NEITHER LESS-THAN NOR GREATER-THAN]*/
	{"NotLessLess",           "\xe2\x89\xaa\xcc\xb8"    }, /* ≪̸ [MUCH LESS THAN with slash]*/
	{"NotLessSlantEqual",     "\xe2\xa9\xbd\xcc\xb8"    }, /* ⩽̸ [LESS-THAN OR SLANTED EQUAL TO with slash]*/
	{"NotLessTilde",          "\xe2\x89\xb4"            }, /* ≴ [NEITHER LESS-THAN NOR EQUIVALENT TO]*/
	{"NotNestedGreaterGreater","\xe2\xaa\xa2\xcc\xb8"    }, /* ⪢̸ [DOUBLE NESTED GREATER-THAN with slash]*/
	{"NotNestedLessLess",     "\xe2\xaa\xa1\xcc\xb8"    }, /* ⪡̸ [DOUBLE NESTED LESS-THAN with slash]*/
	{"NotPrecedes",           "\xe2\x8a\x80"            }, /* ⊀ [DOES NOT PRECEDE]*/
	{"NotPrecedesEqual",      "\xe2\xaa\xaf\xcc\xb8"    }, /* ⪯̸ [PRECEDES ABOVE SINGLE-LINE EQUALS SIGN with slash]*/
	{"NotPrecedesSlantEqual", "\xe2\x8b\xa0"            }, /* ⋠ [DOES NOT PRECEDE OR EQUAL]*/
	{"NotReverseElement",     "\xe2\x88\x8c"            }, /* ∌ [DOES NOT CONTAIN AS MEMBER]*/
	{"NotRightTriangle",      "\xe2\x8b\xab"            }, /* ⋫ [DOES NOT CONTAIN AS NORMAL SUBGROUP]*/
	{"NotRightTriangleBar",   "\xe2\xa7\x90\xcc\xb8"    }, /* ⧐̸ [VERTICAL BAR BESIDE RIGHT TRIANGLE with slash]*/
	{"NotRightTriangleEqual", "\xe2\x8b\xad"            }, /* ⋭ [DOES NOT CONTAIN AS NORMAL SUBGROUP OR EQUAL]*/
	{"NotSquareSubset",       "\xe2\x8a\x8f\xcc\xb8"    }, /* ⊏̸ [SQUARE IMAGE OF with slash]*/
	{"NotSquareSubsetEqual",  "\xe2\x8b\xa2"            }, /* ⋢ [NOT SQUARE IMAGE OF OR EQUAL TO]*/
	{"NotSquareSuperset",     "\xe2\x8a\x90\xcc\xb8"    }, /* ⊐̸ [SQUARE ORIGINAL OF with slash]*/
	{"NotSquareSupersetEqual","\xe2\x8b\xa3"            }, /* ⋣ [NOT SQUARE ORIGINAL OF OR EQUAL TO]*/
	{"NotSubset",             "\xe2\x8a\x82\xe2\x83\x92"}, /* ⊂⃒ [SUBSET OF with vertical line]*/
	{"NotSubsetEqual",        "\xe2\x8a\x88"            }, /* ⊈ [NEITHER A SUBSET OF NOR EQUAL TO]*/
	{"NotSucceeds",           "\xe2\x8a\x81"            }, /* ⊁ [DOES NOT SUCCEED]*/
	{"NotSucceedsEqual",      "\xe2\xaa\xb0\xcc\xb8"    }, /* ⪰̸ [SUCCEEDS ABOVE SINGLE-LINE EQUALS SIGN with slash]*/
	{"NotSucceedsSlantEqual", "\xe2\x8b\xa1"            }, /* ⋡ [DOES NOT SUCCEED OR EQUAL]*/
	{"NotSucceedsTilde",      "\xe2\x89\xbf\xcc\xb8"    }, /* ≿̸ [SUCCEEDS OR EQUIVALENT TO with slash]*/
	{"NotSuperset",           "\xe2\x8a\x83\xe2\x83\x92"}, /* ⊃⃒ [SUPERSET OF with vertical line]*/
	{"NotSupersetEqual",      "\xe2\x8a\x89"            }, /* ⊉ [NEITHER A SUPERSET OF NOR EQUAL TO]*/
	{"NotTilde",              "\xe2\x89\x81"            }, /* ≁ [NOT TILDE]*/
	{"NotTildeEqual",         "\xe2\x89\x84"            }, /* ≄ [NOT ASYMPTOTICALLY EQUAL TO]*/
	{"NotTildeFullEqual",     "\xe2\x89\x87"            }, /* ≇ [NEITHER APPROXIMATELY NOR ACTUALLY EQUAL TO]*/
	{"NotTildeTilde",         "\xe2\x89\x89"            }, /* ≉ [NOT ALMOST EQUAL TO]*/
	{"NotVerticalBar",        "\xe2\x88\xa4"            }, /* ∤ [DOES NOT DIVIDE]*/
	{"Nscr",                  "\xf0\x9d\x92\xa9"        }, /* 𝒩 [MATHEMATICAL SCRIPT CAPITAL N]*/
	{"Ntilde",                "\xc3\x91"                }, /* Ñ [LATIN CAPITAL LETTER N WITH TILDE]*/
	{"Nu",                    "\xce\x9d"                }, /* Ν [GREEK CAPITAL LETTER NU] */
	{"OElig",                 "\xc5\x92"                }, /* Œ [LATIN CAPITAL LIGATURE OE]*/
	{"Oacute",                "\xc3\x93"                }, /* Ó [LATIN CAPITAL LETTER O WITH ACUTE]*/
	{"Ocirc",                 "\xc3\x94"                }, /* Ô [LATIN CAPITAL LETTER O WITH CIRCUMFLEX]*/
	{"Ocy",                   "\xd0\x9e"                }, /* О [CYRILLIC CAPITAL LETTER O]*/
	{"Odblac",                "\xc5\x90"                }, /* Ő [LATIN CAPITAL LETTER O WITH DOUBLE ACUTE]*/
	{"Ofr",                   "\xf0\x9d\x94\x92"        }, /* 𝔒 [MATHEMATICAL FRAKTUR CAPITAL O]*/
	{"Ograve",                "\xc3\x92"                }, /* Ò [LATIN CAPITAL LETTER O WITH GRAVE]*/
	{"Omacr",                 "\xc5\x8c"                }, /* Ō [LATIN CAPITAL LETTER O WITH MACRON]*/
	{"Omega",                 "\xce\xa9"                }, /* Ω [GREEK CAPITAL LETTER OMEGA]*/
	{"Oopf",                  "\xf0\x9d\x95\x86"        }, /* 𝕆 [MATHEMATICAL DOUBLE-STRUCK CAPITAL O]*/
	{"OpenCurlyDoubleQuote",  "\xe2\x80\x9c"            }, /* “ [LEFT DOUBLE QUOTATION MARK]*/
	{"OpenCurlyQuote",        "\xe2\x80\x98"            }, /* ‘ [LEFT SINGLE QUOTATION MARK]*/
	{"Or",                    "\xe2\xa9\x94"            }, /* ⩔ [DOUBLE LOGICAL OR]*/
	{"Oscr",                  "\xf0\x9d\x92\xaa"        }, /* 𝒪 [MATHEMATICAL SCRIPT CAPITAL O]*/
	{"Oslash",                "\xc3\x98"                }, /* Ø [LATIN CAPITAL LETTER O WITH STROKE]*/
	{"Otilde",                "\xc3\x95"                }, /* Õ [LATIN CAPITAL LETTER O WITH TILDE]*/
	{"Otimes",                "\xe2\xa8\xb7"            }, /* ⨷ [MULTIPLICATION SIGN IN DOUBLE CIRCLE]*/
	{"Ouml",                  "\xc3\x96"                }, /* Ö [LATIN CAPITAL LETTER O WITH DIAERESIS]*/
	{"OverBar",               "\xc2\xaf"                }, /* ¯ [MACRON]*/
	{"OverBrace",             "\xef\xb8\xb7"            }, /* ︷ [PRESENTATION FORM FOR VERTICAL LEFT CURLY BRACKET]*/
	{"OverBracket",           "\xe2\x8e\xb4"            }, /* ⎴ [TOP SQUARE BRACKET]*/
	{"OverParenthesis",       "\xef\xb8\xb5"            }, /* ︵ [PRESENTATION FORM FOR VERTICAL LEFT PARENTHESIS]*/
	{"PartialD",              "\xe2\x88\x82"            }, /* ∂ [PARTIAL DIFFERENTIAL]*/
	{"Pcy",                   "\xd0\x9f"                }, /* П [CYRILLIC CAPITAL LETTER PE]*/
	{"Pfr",                   "\xf0\x9d\x94\x93"        }, /* 𝔓 [MATHEMATICAL FRAKTUR CAPITAL P]*/
	{"Phi",                   "\xce\xa6"                }, /* Φ [GREEK CAPITAL LETTER PHI]*/
	{"Pi",                    "\xce\xa0"                }, /* Π [GREEK CAPITAL LETTER PI]*/
	{"PlusMinus",             "\xc2\xb1"                }, /* ± [PLUS-MINUS SIGN]*/
	{"Poincareplane",         "\xe2\x84\x8c"            }, /* ℌ [BLACK-LETTER CAPITAL H]*/
	{"Popf",                  "\xe2\x84\x99"            }, /* ℙ [DOUBLE-STRUCK CAPITAL P]*/
	{"Pr",                    "\xe2\xaa\xbb"            }, /* ⪻ [DOUBLE PRECEDES]*/
	{"Precedes",              "\xe2\x89\xba"            }, /* ≺ [PRECEDES]*/
	{"PrecedesEqual",         "\xe2\xaa\xaf"            }, /* ⪯ [PRECEDES ABOVE SINGLE-LINE EQUALS SIGN]*/
	{"PrecedesSlantEqual",    "\xe2\x89\xbc"            }, /* ≼ [PRECEDES OR EQUAL TO]*/
	{"PrecedesTilde",         "\xe2\x89\xbe"            }, /* ≾ [PRECEDES OR EQUIVALENT TO]*/
	{"Prime",                 "\xe2\x80\xb3"            }, /* ″ [DOUBLE PRIME]*/
	{"Product",               "\xe2\x88\x8f"            }, /* ∏ [N-ARY PRODUCT]*/
	{"Proportion",            "\xe2\x88\xb7"            }, /* ∷ [PROPORTION]*/
	{"Proportional",          "\xe2\x88\x9d"            }, /* ∝ [PROPORTIONAL TO]*/
	{"Pscr",                  "\xf0\x9d\x92\xab"        }, /* 𝒫 [MATHEMATICAL SCRIPT CAPITAL P]*/
	{"Psi",                   "\xce\xa8"                }, /* Ψ [GREEK CAPITAL LETTER PSI]*/
	{"Qfr",                   "\xf0\x9d\x94\x94"        }, /* 𝔔 [MATHEMATICAL FRAKTUR CAPITAL Q]*/
	{"Qopf",                  "\xe2\x84\x9a"            }, /* ℚ [DOUBLE-STRUCK CAPITAL Q]*/
	{"Qscr",                  "\xf0\x9d\x92\xac"        }, /* 𝒬 [MATHEMATICAL SCRIPT CAPITAL Q]*/
	{"RBarr",                 "\xe2\xa4\x90"            }, /* ⤐ [RIGHTWARDS TWO-HEADED TRIPLE DASH ARROW]*/
	{"Racute",                "\xc5\x94"                }, /* Ŕ [LATIN CAPITAL LETTER R WITH ACUTE]*/
	{"Rang",                  "\xe3\x80\x8b"            }, /* 》 [RIGHT DOUBLE ANGLE BRACKET]*/
	{"Rarr",                  "\xe2\x86\xa0"            }, /* ↠ [RIGHTWARDS TWO HEADED ARROW]*/
	{"Rarrtl",                "\xe2\xa4\x96"            }, /* ⤖ [RIGHTWARDS TWO-HEADED ARROW WITH TAIL]*/
	{"Rcaron",                "\xc5\x98"                }, /* Ř [LATIN CAPITAL LETTER R WITH CARON]*/
	{"Rcedil",                "\xc5\x96"                }, /* Ŗ [LATIN CAPITAL LETTER R WITH CEDILLA]*/
	{"Rcy",                   "\xd0\xa0"                }, /* Р [CYRILLIC CAPITAL LETTER ER]*/
	{"Re",                    "\xe2\x84\x9c"            }, /* ℜ [BLACK-LETTER CAPITAL R]*/
	{"ReverseElement",        "\xe2\x88\x8b"            }, /* ∋ [CONTAINS AS MEMBER]*/
	{"ReverseEquilibrium",    "\xe2\x87\x8b"            }, /* ⇋ [LEFTWARDS HARPOON OVER RIGHTWARDS HARPOON]*/
	{"ReverseUpEquilibrium",  "\xe2\xa5\xaf"            }, /* ⥯ [DOWNWARDS HARPOON WITH BARB LEFT BESIDE UPWARDS HARPOON WITH BARB RIGHT]*/
	{"Rfr",                   "\xe2\x84\x9c"            }, /* ℜ [BLACK-LETTER CAPITAL R]*/
	{"Rho",	                  "\xce\xa1"                }, /* Ρ [GREEK CAPITAL LETTER RHO] */
	{"RightAngleBracket",     "\xe2\x8c\xaa"            }, /* 〉 [RIGHT-POINTING ANGLE BRACKET]*/
	{"RightArrow",            "\xe2\x86\x92"            }, /* → [RIGHTWARDS ARROW]*/
	{"RightArrowBar",         "\xe2\x87\xa5"            }, /* ⇥ [RIGHTWARDS ARROW TO BAR]*/
	{"RightArrowLeftArrow",   "\xe2\x87\x84"            }, /* ⇄ [RIGHTWARDS ARROW OVER LEFTWARDS ARROW]*/
	{"RightCeiling",          "\xe2\x8c\x89"            }, /* ⌉ [RIGHT CEILING]*/
	{"RightDoubleBracket",    "\xe3\x80\x9b"            }, /* 〛 [RIGHT WHITE SQUARE BRACKET]*/
	{"RightDownTeeVector",    "\xe2\xa5\x9d"            }, /* ⥝ [DOWNWARDS HARPOON WITH BARB RIGHT FROM BAR]*/
	{"RightDownVector",       "\xe2\x87\x82"            }, /* ⇂ [DOWNWARDS HARPOON WITH BARB RIGHTWARDS]*/
	{"RightDownVectorBar",    "\xe2\xa5\x95"            }, /* ⥕ [DOWNWARDS HARPOON WITH BARB RIGHT TO BAR]*/
	{"RightFloor",            "\xe2\x8c\x8b"            }, /* ⌋ [RIGHT FLOOR]*/
	{"RightTee",              "\xe2\x8a\xa2"            }, /* ⊢ [RIGHT TACK]*/
	{"RightTeeArrow",         "\xe2\x86\xa6"            }, /* ↦ [RIGHTWARDS ARROW FROM BAR]*/
	{"RightTeeVector",        "\xe2\xa5\x9b"            }, /* ⥛ [RIGHTWARDS HARPOON WITH BARB UP FROM BAR]*/
	{"RightTriangle",         "\xe2\x8a\xb3"            }, /* ⊳ [CONTAINS AS NORMAL SUBGROUP]*/
	{"RightTriangleBar",      "\xe2\xa7\x90"            }, /* ⧐ [VERTICAL BAR BESIDE RIGHT TRIANGLE]*/
	{"RightTriangleEqual",    "\xe2\x8a\xb5"            }, /* ⊵ [CONTAINS AS NORMAL SUBGROUP OR EQUAL TO]*/
	{"RightUpDownVector",     "\xe2\xa5\x8f"            }, /* ⥏ [UP BARB RIGHT DOWN BARB RIGHT HARPOON]*/
	{"RightUpTeeVector",      "\xe2\xa5\x9c"            }, /* ⥜ [UPWARDS HARPOON WITH BARB RIGHT FROM BAR]*/
	{"RightUpVector",         "\xe2\x86\xbe"            }, /* ↾ [UPWARDS HARPOON WITH BARB RIGHTWARDS]*/
	{"RightUpVectorBar",      "\xe2\xa5\x94"            }, /* ⥔ [UPWARDS HARPOON WITH BARB RIGHT TO BAR]*/
	{"RightVector",           "\xe2\x87\x80"            }, /* ⇀ [RIGHTWARDS HARPOON WITH BARB UPWARDS]*/
	{"RightVectorBar",        "\xe2\xa5\x93"            }, /* ⥓ [RIGHTWARDS HARPOON WITH BARB UP TO BAR]*/
	{"Rightarrow",            "\xe2\x87\x92"            }, /* ⇒ [RIGHTWARDS DOUBLE ARROW]*/
	{"Ropf",                  "\xe2\x84\x9d"            }, /* ℝ [DOUBLE-STRUCK CAPITAL R]*/
	{"RoundImplies",          "\xe2\xa5\xb0"            }, /* ⥰ [RIGHT DOUBLE ARROW WITH ROUNDED HEAD]*/
	{"Rrightarrow",           "\xe2\x87\x9b"            }, /* ⇛ [RIGHTWARDS TRIPLE ARROW]*/
	{"Rscr",                  "\xe2\x84\x9b"            }, /* ℛ [SCRIPT CAPITAL R]*/
	{"Rsh",                   "\xe2\x86\xb1"            }, /* ↱ [UPWARDS ARROW WITH TIP RIGHTWARDS]*/
	{"RuleDelayed",           "\xe2\xa7\xb4"            }, /* ⧴ [RULE-DELAYED]*/
	{"SHCHcy",                "\xd0\xa9"                }, /* Щ [CYRILLIC CAPITAL LETTER SHCHA]*/
	{"SHcy",                  "\xd0\xa8"                }, /* Ш [CYRILLIC CAPITAL LETTER SHA]*/
	{"SOFTcy",                "\xd0\xac"                }, /* Ь [CYRILLIC CAPITAL LETTER SOFT SIGN]*/
	{"Sacute",                "\xc5\x9a"                }, /* Ś [LATIN CAPITAL LETTER S WITH ACUTE]*/
	{"Sc",                    "\xe2\xaa\xbc"            }, /* ⪼ [DOUBLE SUCCEEDS]*/
	{"Scaron",                "\xc5\xa0"                }, /* Š [LATIN CAPITAL LETTER S WITH CARON]*/
	{"Scedil",                "\xc5\x9e"                }, /* Ş [LATIN CAPITAL LETTER S WITH CEDILLA]*/
	{"Scirc",                 "\xc5\x9c"                }, /* Ŝ [LATIN CAPITAL LETTER S WITH CIRCUMFLEX]*/
	{"Scy",                   "\xd0\xa1"                }, /* С [CYRILLIC CAPITAL LETTER ES]*/
	{"Sfr",                   "\xf0\x9d\x94\x96"        }, /* 𝔖 [MATHEMATICAL FRAKTUR CAPITAL S]*/
#if 0	
	{"ShortDownArrow",        "\xe2\x86\x93"            }, /* ↓ [DOWNWARDS ARROW]*/
	{"ShortLeftArrow",        "\xe2\x86\x90"            }, /* ← [LEFTWARDS ARROW]*/
	{"ShortRightArrow",       "\xe2\x86\x92"            }, /* → [RIGHTWARDS ARROW]*/
	{"ShortUpArrow",          "\xe2\x86\x91"            }, /* ↑ [UPWARDS ARROW]*/
#endif
	{"Sigma",                 "\xce\xa3"                }, /* Σ [GREEK CAPITAL LETTER SIGMA]*/
	{"SmallCircle",           "\xe2\x88\x98"            }, /* ∘ [RING OPERATOR]*/
	{"Sopf",                  "\xf0\x9d\x95\x8a"        }, /* 𝕊 [MATHEMATICAL DOUBLE-STRUCK CAPITAL S]*/
	{"Sqrt",                  "\xe2\x88\x9a"            }, /* √ [SQUARE ROOT]*/
	{"Square",                "\xe2\x96\xa1"            }, /* □ [WHITE SQUARE]*/
	{"SquareIntersection",    "\xe2\x8a\x93"            }, /* ⊓ [SQUARE CAP]*/
	{"SquareSubset",          "\xe2\x8a\x8f"            }, /* ⊏ [SQUARE IMAGE OF]*/
	{"SquareSubsetEqual",     "\xe2\x8a\x91"            }, /* ⊑ [SQUARE IMAGE OF OR EQUAL TO]*/
	{"SquareSuperset",        "\xe2\x8a\x90"            }, /* ⊐ [SQUARE ORIGINAL OF]*/
	{"SquareSupersetEqual",   "\xe2\x8a\x92"            }, /* ⊒ [SQUARE ORIGINAL OF OR EQUAL TO]*/
	{"SquareUnion",           "\xe2\x8a\x94"            }, /* ⊔ [SQUARE CUP]*/
	{"Sscr",                  "\xf0\x9d\x92\xae"        }, /* 𝒮 [MATHEMATICAL SCRIPT CAPITAL S]*/
	{"Star",                  "\xe2\x8b\x86"            }, /* ⋆ [STAR OPERATOR]*/
	{"Sub",                   "\xe2\x8b\x90"            }, /* ⋐ [DOUBLE SUBSET]*/
	{"Subset",                "\xe2\x8b\x90"            }, /* ⋐ [DOUBLE SUBSET]*/
	{"SubsetEqual",           "\xe2\x8a\x86"            }, /* ⊆ [SUBSET OF OR EQUAL TO]*/
	{"Succeeds",              "\xe2\x89\xbb"            }, /* ≻ [SUCCEEDS]*/
	{"SucceedsEqual",         "\xe2\xaa\xb0"            }, /* ⪰ [SUCCEEDS ABOVE SINGLE-LINE EQUALS SIGN]*/
	{"SucceedsSlantEqual",    "\xe2\x89\xbd"            }, /* ≽ [SUCCEEDS OR EQUAL TO]*/
	{"SucceedsTilde",         "\xe2\x89\xbf"            }, /* ≿ [SUCCEEDS OR EQUIVALENT TO]*/
	{"SuchThat",              "\xe2\x88\x8b"            }, /* ∋ [CONTAINS AS MEMBER]*/
	{"Sum",                   "\xe2\x88\x91"            }, /* ∑ [N-ARY SUMMATION]*/
	{"Sup",                   "\xe2\x8b\x91"            }, /* ⋑ [DOUBLE SUPERSET]*/
	{"Superset",              "\xe2\x8a\x83"            }, /* ⊃ [SUPERSET OF]*/
	{"SupersetEqual",         "\xe2\x8a\x87"            }, /* ⊇ [SUPERSET OF OR EQUAL TO]*/
	{"Supset",                "\xe2\x8b\x91"            }, /* ⋑ [DOUBLE SUPERSET]*/
	{"THORN",                 "\xc3\x9e"                }, /* Þ [LATIN CAPITAL LETTER THORN]*/
	{"TSHcy",                 "\xd0\x8b"                }, /* Ћ [CYRILLIC CAPITAL LETTER TSHE]*/
	{"TScy",                  "\xd0\xa6"                }, /* Ц [CYRILLIC CAPITAL LETTER TSE]*/
	{"Tab",                   "\x9"                     }, /* 	 [CHARACTER TABULATION]*/
	{"Tau",                   "\xce\xa4"                }, /* Τ [GREEK CAPITAL LETTER TAU] */
	{"Tcaron",                "\xc5\xa4"                }, /* Ť [LATIN CAPITAL LETTER T WITH CARON]*/
	{"Tcedil",                "\xc5\xa2"                }, /* Ţ [LATIN CAPITAL LETTER T WITH CEDILLA]*/
	{"Tcy",                   "\xd0\xa2"                }, /* Т [CYRILLIC CAPITAL LETTER TE]*/
	{"Tfr",                   "\xf0\x9d\x94\x97"        }, /* 𝔗 [MATHEMATICAL FRAKTUR CAPITAL T]*/
	{"Therefore",             "\xe2\x88\xb4"            }, /* ∴ [THEREFORE]*/
	{"Theta",                 "\xce\x98"                }, /* Θ [GREEK CAPITAL LETTER THETA]*/
	{"ThickSpace",            "\xe2\x80\x89\xe2\x80\x8a\xe2\x80\x8a"}, /*     [space of width 5/18 em]*/
	{"ThinSpace",             "\xe2\x80\x89"            }, /*   [THIN SPACE]*/
	{"Tilde",                 "\xe2\x88\xbc"            }, /* ∼ [TILDE OPERATOR]*/
	{"TildeEqual",            "\xe2\x89\x83"            }, /* ≃ [ASYMPTOTICALLY EQUAL TO]*/
	{"TildeFullEqual",        "\xe2\x89\x85"            }, /* ≅ [APPROXIMATELY EQUAL TO]*/
	{"TildeTilde",            "\xe2\x89\x88"            }, /* ≈ [ALMOST EQUAL TO]*/
	{"Topf",                  "\xf0\x9d\x95\x8b"        }, /* 𝕋 [MATHEMATICAL DOUBLE-STRUCK CAPITAL T]*/
	{"TripleDot",             "\xe2\x83\x9b"            }, /* ⃛ [COMBINING THREE DOTS ABOVE]*/
	{"Tscr",                  "\xf0\x9d\x92\xaf"        }, /* 𝒯 [MATHEMATICAL SCRIPT CAPITAL T]*/
	{"Tstrok",                "\xc5\xa6"                }, /* Ŧ [LATIN CAPITAL LETTER T WITH STROKE]*/
	{"Uacute",                "\xc3\x9a"                }, /* Ú [LATIN CAPITAL LETTER U WITH ACUTE]*/
	{"Uarr",                  "\xe2\x86\x9f"            }, /* ↟ [UPWARDS TWO HEADED ARROW]*/
	{"Uarrocir",              "\xe2\xa5\x89"            }, /* ⥉ [UPWARDS TWO-HEADED ARROW FROM SMALL CIRCLE]*/
	{"Ubrcy",                 "\xd0\x8e"                }, /* Ў [CYRILLIC CAPITAL LETTER SHORT U]*/
	{"Ubreve",                "\xc5\xac"                }, /* Ŭ [LATIN CAPITAL LETTER U WITH BREVE]*/
	{"Ucirc",                 "\xc3\x9b"                }, /* Û [LATIN CAPITAL LETTER U WITH CIRCUMFLEX]*/
	{"Ucy",                   "\xd0\xa3"                }, /* У [CYRILLIC CAPITAL LETTER U]*/
	{"Udblac",                "\xc5\xb0"                }, /* Ű [LATIN CAPITAL LETTER U WITH DOUBLE ACUTE]*/
	{"Ufr",                   "\xf0\x9d\x94\x98"        }, /* 𝔘 [MATHEMATICAL FRAKTUR CAPITAL U]*/
	{"Ugrave",                "\xc3\x99"                }, /* Ù [LATIN CAPITAL LETTER U WITH GRAVE]*/
	{"Umacr",                 "\xc5\xaa"                }, /* Ū [LATIN CAPITAL LETTER U WITH MACRON]*/
	{"UnderBar",              "\xcc\xb2"                }, /* ̲ [COMBINING LOW LINE]*/
	{"UnderBrace",            "\xef\xb8\xb8"            }, /* ︸ [PRESENTATION FORM FOR VERTICAL RIGHT CURLY BRACKET]*/
	{"UnderBracket",          "\xe2\x8e\xb5"            }, /* ⎵ [BOTTOM SQUARE BRACKET]*/
	{"UnderParenthesis",      "\xef\xb8\xb6"            }, /* ︶ [PRESENTATION FORM FOR VERTICAL RIGHT PARENTHESIS]*/
	{"Union",                 "\xe2\x8b\x83"            }, /* ⋃ [N-ARY UNION]*/
	{"UnionPlus",             "\xe2\x8a\x8e"            }, /* ⊎ [MULTISET UNION]*/
	{"Uogon",                 "\xc5\xb2"                }, /* Ų [LATIN CAPITAL LETTER U WITH OGONEK]*/
	{"Uopf",                  "\xf0\x9d\x95\x8c"        }, /* 𝕌 [MATHEMATICAL DOUBLE-STRUCK CAPITAL U]*/
	{"UpArrow",               "\xe2\x86\x91"            }, /* ↑ [UPWARDS ARROW]*/
	{"UpArrowBar",            "\xe2\xa4\x92"            }, /* ⤒ [UPWARDS ARROW TO BAR]*/
	{"UpArrowDownArrow",      "\xe2\x87\x85"            }, /* ⇅ [UPWARDS ARROW LEFTWARDS OF DOWNWARDS ARROW]*/
	{"UpDownArrow",           "\xe2\x86\x95"            }, /* ↕ [UP DOWN ARROW]*/
	{"UpEquilibrium",         "\xe2\xa5\xae"            }, /* ⥮ [UPWARDS HARPOON WITH BARB LEFT BESIDE DOWNWARDS HARPOON WITH BARB RIGHT]*/
	{"UpTee",                 "\xe2\x8a\xa5"            }, /* ⊥ [UP TACK]*/
	{"UpTeeArrow",            "\xe2\x86\xa5"            }, /* ↥ [UPWARDS ARROW FROM BAR]*/
	{"Uparrow",               "\xe2\x87\x91"            }, /* ⇑ [UPWARDS DOUBLE ARROW]*/
	{"Updownarrow",           "\xe2\x87\x95"            }, /* ⇕ [UP DOWN DOUBLE ARROW]*/
	{"UpperLeftArrow",        "\xe2\x86\x96"            }, /* ↖ [NORTH WEST ARROW]*/
	{"UpperRightArrow",       "\xe2\x86\x97"            }, /* ↗ [NORTH EAST ARROW]*/
	{"Upsi",                  "\xcf\x92"                }, /* ϒ [GREEK UPSILON WITH HOOK SYMBOL]*/
	{"Upsilon",               "\xce\xa5"                }, /* Υ [GREEK CAPITAL LETTER UPSILON]*/
	{"Uring",                 "\xc5\xae"                }, /* Ů [LATIN CAPITAL LETTER U WITH RING ABOVE]*/
	{"Uscr",                  "\xf0\x9d\x92\xb0"        }, /* 𝒰 [MATHEMATICAL SCRIPT CAPITAL U]*/
	{"Utilde",                "\xc5\xa8"                }, /* Ũ [LATIN CAPITAL LETTER U WITH TILDE]*/
	{"Uuml",                  "\xc3\x9c"                }, /* Ü [LATIN CAPITAL LETTER U WITH DIAERESIS]*/
	{"VDash",                 "\xe2\x8a\xab"            }, /* ⊫ [DOUBLE VERTICAL BAR DOUBLE RIGHT TURNSTILE]*/
	{"Vbar",                  "\xe2\xab\xab"            }, /* ⫫ [DOUBLE UP TACK]*/
	{"Vcy",                   "\xd0\x92"                }, /* В [CYRILLIC CAPITAL LETTER VE]*/
	{"Vdash",                 "\xe2\x8a\xa9"            }, /* ⊩ [FORCES]*/
	{"Vdashl",                "\xe2\xab\xa6"            }, /* ⫦ [LONG DASH FROM LEFT MEMBER OF DOUBLE VERTICAL]*/
	{"Vee",                   "\xe2\x8b\x81"            }, /* ⋁ [N-ARY LOGICAL OR]*/
	{"Verbar",                "\xe2\x80\x96"            }, /* ‖ [DOUBLE VERTICAL LINE]*/
	{"Vert",                  "\xe2\x80\x96"            }, /* ‖ [DOUBLE VERTICAL LINE]*/
	{"VerticalBar",           "\xe2\x88\xa3"            }, /* ∣ [DIVIDES]*/
	{"VerticalLine",          "\x7c"                    }, /* | [VERTICAL LINE]*/
	{"VerticalSeparator",     "\xe2\x9d\x98"            }, /* ❘ [LIGHT VERTICAL BAR]*/
	{"VerticalTilde",         "\xe2\x89\x80"            }, /* ≀ [WREATH PRODUCT]*/
	{"VeryThinSpace",         "\xe2\x80\x8a"            }, /*   [HAIR SPACE]*/
	{"Vfr",                   "\xf0\x9d\x94\x99"        }, /* 𝔙 [MATHEMATICAL FRAKTUR CAPITAL V]*/
	{"Vopf",                  "\xf0\x9d\x95\x8d"        }, /* 𝕍 [MATHEMATICAL DOUBLE-STRUCK CAPITAL V]*/
	{"Vscr",                  "\xf0\x9d\x92\xb1"        }, /* 𝒱 [MATHEMATICAL SCRIPT CAPITAL V]*/
	{"Vvdash",                "\xe2\x8a\xaa"            }, /* ⊪ [TRIPLE VERTICAL BAR RIGHT TURNSTILE]*/
	{"Wcirc",                 "\xc5\xb4"                }, /* Ŵ [LATIN CAPITAL LETTER W WITH CIRCUMFLEX]*/
	{"Wedge",                 "\xe2\x8b\x80"            }, /* ⋀ [N-ARY LOGICAL AND]*/
	{"Wfr",                   "\xf0\x9d\x94\x9a"        }, /* 𝔚 [MATHEMATICAL FRAKTUR CAPITAL W]*/
	{"Wopf",                  "\xf0\x9d\x95\x8e"        }, /* 𝕎 [MATHEMATICAL DOUBLE-STRUCK CAPITAL W]*/
	{"Wscr",                  "\xf0\x9d\x92\xb2"        }, /* 𝒲 [MATHEMATICAL SCRIPT CAPITAL W]*/
	{"Xfr",                   "\xf0\x9d\x94\x9b"        }, /* 𝔛 [MATHEMATICAL FRAKTUR CAPITAL X]*/
	{"Xi",                    "\xce\x9e"                }, /* Ξ [GREEK CAPITAL LETTER XI]*/
	{"Xopf",                  "\xf0\x9d\x95\x8f"        }, /* 𝕏 [MATHEMATICAL DOUBLE-STRUCK CAPITAL X]*/
	{"Xscr",                  "\xf0\x9d\x92\xb3"        }, /* 𝒳 [MATHEMATICAL SCRIPT CAPITAL X]*/
	{"YAcy",                  "\xd0\xaf"                }, /* Я [CYRILLIC CAPITAL LETTER YA]*/
	{"YIcy",                  "\xd0\x87"                }, /* Ї [CYRILLIC CAPITAL LETTER YI]*/
	{"YUcy",                  "\xd0\xae"                }, /* Ю [CYRILLIC CAPITAL LETTER YU]*/
	{"Yacute",                "\xc3\x9d"                }, /* Ý [LATIN CAPITAL LETTER Y WITH ACUTE]*/
	{"Ycirc",                 "\xc5\xb6"                }, /* Ŷ [LATIN CAPITAL LETTER Y WITH CIRCUMFLEX]*/
	{"Ycy",                   "\xd0\xab"                }, /* Ы [CYRILLIC CAPITAL LETTER YERU]*/
	{"Yfr",                   "\xf0\x9d\x94\x9c"        }, /* 𝔜 [MATHEMATICAL FRAKTUR CAPITAL Y]*/
	{"Yopf",                  "\xf0\x9d\x95\x90"        }, /* 𝕐 [MATHEMATICAL DOUBLE-STRUCK CAPITAL Y]*/
	{"Yscr",                  "\xf0\x9d\x92\xb4"        }, /* 𝒴 [MATHEMATICAL SCRIPT CAPITAL Y]*/
	{"Yuml",                  "\xc5\xb8"                }, /* Ÿ [LATIN CAPITAL LETTER Y WITH DIAERESIS]*/
	{"ZHcy",                  "\xd0\x96"                }, /* Ж [CYRILLIC CAPITAL LETTER ZHE]*/
	{"Zacute",                "\xc5\xb9"                }, /* Ź [LATIN CAPITAL LETTER Z WITH ACUTE]*/
	{"Zcaron",                "\xc5\xbd"                }, /* Ž [LATIN CAPITAL LETTER Z WITH CARON]*/
	{"Zcy",                   "\xd0\x97"                }, /* З [CYRILLIC CAPITAL LETTER ZE]*/
	{"Zdot",                  "\xc5\xbb"                }, /* Ż [LATIN CAPITAL LETTER Z WITH DOT ABOVE]*/
	{"ZeroWidthSpace",        "\xe2\x80\x8b"            }, /* ​ [ZERO WIDTH SPACE]*/
	{"Zeta",                  "\xce\x96"                }, /* Ζ [GREEK CAPITAL LETTER ZETA] */
	{"Zfr",                   "\xe2\x84\xa8"            }, /* ℨ [BLACK-LETTER CAPITAL Z]*/
	{"Zopf",                  "\xe2\x84\xa4"            }, /* ℤ [DOUBLE-STRUCK CAPITAL Z]*/
	{"Zscr",                  "\xf0\x9d\x92\xb5"        }, /* 𝒵 [MATHEMATICAL SCRIPT CAPITAL Z]*/
	{"aacute",                "\xc3\xa1"                }, /* á [LATIN SMALL LETTER A WITH ACUTE]*/
	{"abreve",                "\xc4\x83"                }, /* ă [LATIN SMALL LETTER A WITH BREVE]*/
	{"ac",                    "\xe2\x88\xbe"            }, /* ∾ [INVERTED LAZY S]*/
	{"acE",                   "\xe2\x88\xbe\xcc\xb3"    }, /* ∾̳ [INVERTED LAZY S with double underline]*/
	{"acd",                   "\xe2\x88\xbf"            }, /* ∿ [SINE WAVE]*/
	{"acirc",                 "\xc3\xa2"                }, /* â [LATIN SMALL LETTER A WITH CIRCUMFLEX]*/
	{"acute",                 "\xc2\xb4"                }, /* ´ [ACUTE ACCENT]*/
	{"acy",                   "\xd0\xb0"                }, /* а [CYRILLIC SMALL LETTER A]*/
	{"aelig",                 "\xc3\xa6"                }, /* æ [LATIN SMALL LETTER AE]*/
	{"af",                    "\xe2\x81\xa1"            }, /* ⁡ [FUNCTION APPLICATION]*/
	{"afr",                   "\xf0\x9d\x94\x9e"        }, /* 𝔞 [MATHEMATICAL FRAKTUR SMALL A]*/
	{"agrave",                "\xc3\xa0"                }, /* à [LATIN SMALL LETTER A WITH GRAVE]*/
	{"aleph",                 "\xe2\x84\xb5"            }, /* ℵ [ALEF SYMBOL]*/
	{"alpha",                 "\xce\xb1"                }, /* α [GREEK SMALL LETTER ALPHA]*/
	{"amacr",                 "\xc4\x81"                }, /* ā [LATIN SMALL LETTER A WITH MACRON]*/
	{"amalg",                 "\xe2\xa8\xbf"            }, /* ⨿ [AMALGAMATION OR COPRODUCT]*/
	{"amp",                   "\x26"                    }, /* & [AMPERSAND]*/
	{"and",                   "\xe2\x88\xa7"            }, /* ∧ [LOGICAL AND]*/
	{"andand",                "\xe2\xa9\x95"            }, /* ⩕ [TWO INTERSECTING LOGICAL AND]*/
	{"andd",                  "\xe2\xa9\x9c"            }, /* ⩜ [LOGICAL AND WITH HORIZONTAL DASH]*/
	{"andslope",              "\xe2\xa9\x98"            }, /* ⩘ [SLOPING LARGE AND]*/
	{"andv",                  "\xe2\xa9\x9a"            }, /* ⩚ [LOGICAL AND WITH MIDDLE STEM]*/
	{"ang",                   "\xe2\x88\xa0"            }, /* ∠ [ANGLE]*/
	{"ange",                  "\xe2\xa6\xa4"            }, /* ⦤ [ANGLE WITH UNDERBAR]*/
	{"angle",                 "\xe2\x88\xa0"            }, /* ∠ [ANGLE]*/
	{"angmsd",                "\xe2\x88\xa1"            }, /* ∡ [MEASURED ANGLE]*/
	{"angmsdaa",              "\xe2\xa6\xa8"            }, /* ⦨ [MEASURED ANGLE WITH OPEN ARM ENDING IN ARROW POINTING UP AND RIGHT]*/
	{"angmsdab",              "\xe2\xa6\xa9"            }, /* ⦩ [MEASURED ANGLE WITH OPEN ARM ENDING IN ARROW POINTING UP AND LEFT]*/
	{"angmsdac",              "\xe2\xa6\xaa"            }, /* ⦪ [MEASURED ANGLE WITH OPEN ARM ENDING IN ARROW POINTING DOWN AND RIGHT]*/
	{"angmsdad",              "\xe2\xa6\xab"            }, /* ⦫ [MEASURED ANGLE WITH OPEN ARM ENDING IN ARROW POINTING DOWN AND LEFT]*/
	{"angmsdae",              "\xe2\xa6\xac"            }, /* ⦬ [MEASURED ANGLE WITH OPEN ARM ENDING IN ARROW POINTING RIGHT AND UP]*/
	{"angmsdaf",              "\xe2\xa6\xad"            }, /* ⦭ [MEASURED ANGLE WITH OPEN ARM ENDING IN ARROW POINTING LEFT AND UP]*/
	{"angmsdag",              "\xe2\xa6\xae"            }, /* ⦮ [MEASURED ANGLE WITH OPEN ARM ENDING IN ARROW POINTING RIGHT AND DOWN]*/
	{"angmsdah",              "\xe2\xa6\xaf"            }, /* ⦯ [MEASURED ANGLE WITH OPEN ARM ENDING IN ARROW POINTING LEFT AND DOWN]*/
	{"angrt",                 "\xe2\x88\x9f"            }, /* ∟ [RIGHT ANGLE]*/
	{"angrtvb",               "\xe2\x8a\xbe"            }, /* ⊾ [RIGHT ANGLE WITH ARC]*/
	{"angrtvbd",              "\xe2\xa6\x9d"            }, /* ⦝ [MEASURED RIGHT ANGLE WITH DOT]*/
	{"angsph",                "\xe2\x88\xa2"            }, /* ∢ [SPHERICAL ANGLE]*/
	{"angst",                 "\xe2\x84\xab"            }, /* Å [ANGSTROM SIGN]*/
	{"angzarr",               "\xe2\x8d\xbc"            }, /* ⍼ [RIGHT ANGLE WITH DOWNWARDS ZIGZAG ARROW]*/
	{"aogon",                 "\xc4\x85"                }, /* ą [LATIN SMALL LETTER A WITH OGONEK]*/
	{"aopf",                  "\xf0\x9d\x95\x92"        }, /* 𝕒 [MATHEMATICAL DOUBLE-STRUCK SMALL A]*/
	{"ap",                    "\xe2\x89\x88"            }, /* ≈ [ALMOST EQUAL TO]*/
	{"apE",                   "\xe2\xa9\xb0"            }, /* ⩰ [APPROXIMATELY EQUAL OR EQUAL TO]*/
	{"apacir",                "\xe2\xa9\xaf"            }, /* ⩯ [ALMOST EQUAL TO WITH CIRCUMFLEX ACCENT]*/
	{"ape",                   "\xe2\x89\x8a"            }, /* ≊ [ALMOST EQUAL OR EQUAL TO]*/
	{"apid",                  "\xe2\x89\x8b"            }, /* ≋ [TRIPLE TILDE]*/
	{"apos",                  "\x27"                    }, /* ' [APOSTROPHE]*/
	{"approx",                "\xe2\x89\x88"            }, /* ≈ [ALMOST EQUAL TO]*/
	{"approxeq",              "\xe2\x89\x8a"            }, /* ≊ [ALMOST EQUAL OR EQUAL TO]*/
	{"aring",                 "\xc3\xa5"                }, /* å [LATIN SMALL LETTER A WITH RING ABOVE]*/
	{"ascr",                  "\xf0\x9d\x92\xb6"        }, /* 𝒶 [MATHEMATICAL SCRIPT SMALL A]*/
	{"ast",                   "\x2a"                    }, /* * [ASTERISK]*/
	{"asymp",                 "\xe2\x89\x88"            }, /* ≈ [ALMOST EQUAL TO]*/
	{"asympeq",               "\xe2\x89\x8d"            }, /* ≍ [EQUIVALENT TO]*/
	{"atilde",                "\xc3\xa3"                }, /* ã [LATIN SMALL LETTER A WITH TILDE]*/
	{"auml",                  "\xc3\xa4"                }, /* ä [LATIN SMALL LETTER A WITH DIAERESIS]*/
	{"awconint",              "\xe2\x88\xb3"            }, /* ∳ [ANTICLOCKWISE CONTOUR INTEGRAL]*/
	{"awint",                 "\xe2\xa8\x91"            }, /* ⨑ [ANTICLOCKWISE INTEGRATION]*/
	{"bNot",                  "\xe2\xab\xad"            }, /* ⫭ [REVERSED DOUBLE STROKE NOT SIGN]*/
	{"backcong",              "\xe2\x89\x8c"            }, /* ≌ [ALL EQUAL TO]*/
	{"backepsilon",           "\xcf\xb6"                }, /* ϶ [GREEK REVERSED LUNATE EPSILON SYMBOL]*/
	{"backprime",             "\xe2\x80\xb5"            }, /* ‵ [REVERSED PRIME]*/
	{"backsim",               "\xe2\x88\xbd"            }, /* ∽ [REVERSED TILDE]*/
	{"backsimeq",             "\xe2\x8b\x8d"            }, /* ⋍ [REVERSED TILDE EQUALS]*/
	{"barvee",                "\xe2\x8a\xbd"            }, /* ⊽ [NOR]*/
	{"barwed",                "\xe2\x8c\x85"            }, /* ⌅ [PROJECTIVE]*/
	{"barwedge",              "\xe2\x8c\x85"            }, /* ⌅ [PROJECTIVE]*/
	{"bbrk",                  "\xe2\x8e\xb5"            }, /* ⎵ [BOTTOM SQUARE BRACKET]*/
	{"bbrktbrk",              "\xe2\x8e\xb6"            }, /* ⎶ [BOTTOM SQUARE BRACKET OVER TOP SQUARE BRACKET]*/
	{"bcong",                 "\xe2\x89\x8c"            }, /* ≌ [ALL EQUAL TO]*/
	{"bcy",                   "\xd0\xb1"                }, /* б [CYRILLIC SMALL LETTER BE]*/
	{"becaus",                "\xe2\x88\xb5"            }, /* ∵ [BECAUSE]*/
	{"because",               "\xe2\x88\xb5"            }, /* ∵ [BECAUSE]*/
	{"bemptyv",               "\xe2\xa6\xb0"            }, /* ⦰ [REVERSED EMPTY SET]*/
	{"bepsi",                 "\xcf\xb6"                }, /* ϶ [GREEK REVERSED LUNATE EPSILON SYMBOL]*/
	{"bernou",                "\xe2\x84\xac"            }, /* ℬ [SCRIPT CAPITAL B]*/
	{"beta",                  "\xce\xb2"                }, /* β [GREEK SMALL LETTER BETA]*/
	{"beth",                  "\xe2\x84\xb6"            }, /* ℶ [BET SYMBOL]*/
	{"between",               "\xe2\x89\xac"            }, /* ≬ [BETWEEN]*/
	{"bfr",                   "\xf0\x9d\x94\x9f"        }, /* 𝔟 [MATHEMATICAL FRAKTUR SMALL B]*/
	{"bigcap",                "\xe2\x8b\x82"            }, /* ⋂ [N-ARY INTERSECTION]*/
	{"bigcirc",               "\xe2\x97\xaf"            }, /* ◯ [LARGE CIRCLE]*/
	{"bigcup",                "\xe2\x8b\x83"            }, /* ⋃ [N-ARY UNION]*/
	{"bigodot",               "\xe2\xa8\x80"            }, /* ⨀ [N-ARY CIRCLED DOT OPERATOR]*/
	{"bigoplus",              "\xe2\xa8\x81"            }, /* ⨁ [N-ARY CIRCLED PLUS OPERATOR]*/
	{"bigotimes",             "\xe2\xa8\x82"            }, /* ⨂ [N-ARY CIRCLED TIMES OPERATOR]*/
	{"bigsqcup",              "\xe2\xa8\x86"            }, /* ⨆ [N-ARY SQUARE UNION OPERATOR]*/
	{"bigstar",               "\xe2\x98\x85"            }, /* ★ [BLACK STAR]*/
	{"bigtriangledown",       "\xe2\x96\xbd"            }, /* ▽ [WHITE DOWN-POINTING TRIANGLE]*/
	{"bigtriangleup",         "\xe2\x96\xb3"            }, /* △ [WHITE UP-POINTING TRIANGLE]*/
	{"biguplus",              "\xe2\xa8\x84"            }, /* ⨄ [N-ARY UNION OPERATOR WITH PLUS]*/
	{"bigvee",                "\xe2\x8b\x81"            }, /* ⋁ [N-ARY LOGICAL OR]*/
	{"bigwedge",              "\xe2\x8b\x80"            }, /* ⋀ [N-ARY LOGICAL AND]*/
	{"bkarow",                "\xe2\xa4\x8d"            }, /* ⤍ [RIGHTWARDS DOUBLE DASH ARROW]*/
	{"blacklozenge",          "\xe2\xa7\xab"            }, /* ⧫ [BLACK LOZENGE]*/
	{"blacksquare",           "\xe2\x96\xaa"            }, /* ▪ [BLACK SMALL SQUARE]*/
	{"blacktriangle",         "\xe2\x96\xb4"            }, /* ▴ [BLACK UP-POINTING SMALL TRIANGLE]*/
	{"blacktriangledown",     "\xe2\x96\xbe"            }, /* ▾ [BLACK DOWN-POINTING SMALL TRIANGLE]*/
	{"blacktriangleleft",     "\xe2\x97\x82"            }, /* ◂ [BLACK LEFT-POINTING SMALL TRIANGLE]*/
	{"blacktriangleright",    "\xe2\x96\xb8"            }, /* ▸ [BLACK RIGHT-POINTING SMALL TRIANGLE]*/
	{"blank",                 "\xe2\x90\xa3"            }, /* ␣ [OPEN BOX]*/
	{"blk12",                 "\xe2\x96\x92"            }, /* ▒ [MEDIUM SHADE]*/
	{"blk14",                 "\xe2\x96\x91"            }, /* ░ [LIGHT SHADE]*/
	{"blk34",                 "\xe2\x96\x93"            }, /* ▓ [DARK SHADE]*/
	{"block",                 "\xe2\x96\x88"            }, /* █ [FULL BLOCK]*/
	{"bne",                   "\x3d\xe2\x83\xa5"        }, /* =⃥ [EQUALS SIGN with reverse slash]*/
	{"bnequiv",               "\xe2\x89\xa1\xe2\x83\xa5"}, /* ≡⃥ [IDENTICAL TO with reverse slash]*/
	{"bnot",                  "\xe2\x8c\x90"            }, /* ⌐ [REVERSED NOT SIGN]*/
	{"bopf",                  "\xf0\x9d\x95\x93"        }, /* 𝕓 [MATHEMATICAL DOUBLE-STRUCK SMALL B]*/
	{"bot",                   "\xe2\x8a\xa5"            }, /* ⊥ [UP TACK]*/
	{"bottom",                "\xe2\x8a\xa5"            }, /* ⊥ [UP TACK]*/
	{"bowtie",                "\xe2\x8b\x88"            }, /* ⋈ [BOWTIE]*/
	{"boxDL",                 "\xe2\x95\x97"            }, /* ╗ [BOX DRAWINGS DOUBLE DOWN AND LEFT]*/
	{"boxDR",                 "\xe2\x95\x94"            }, /* ╔ [BOX DRAWINGS DOUBLE DOWN AND RIGHT]*/
	{"boxDl",                 "\xe2\x95\x96"            }, /* ╖ [BOX DRAWINGS DOWN DOUBLE AND LEFT SINGLE]*/
	{"boxDr",                 "\xe2\x95\x93"            }, /* ╓ [BOX DRAWINGS DOWN DOUBLE AND RIGHT SINGLE]*/
	{"boxH",                  "\xe2\x95\x90"            }, /* ═ [BOX DRAWINGS DOUBLE HORIZONTAL]*/
	{"boxHD",                 "\xe2\x95\xa6"            }, /* ╦ [BOX DRAWINGS DOUBLE DOWN AND HORIZONTAL]*/
	{"boxHU",                 "\xe2\x95\xa9"            }, /* ╩ [BOX DRAWINGS DOUBLE UP AND HORIZONTAL]*/
	{"boxHd",                 "\xe2\x95\xa4"            }, /* ╤ [BOX DRAWINGS DOWN SINGLE AND HORIZONTAL DOUBLE]*/
	{"boxHu",                 "\xe2\x95\xa7"            }, /* ╧ [BOX DRAWINGS UP SINGLE AND HORIZONTAL DOUBLE]*/
	{"boxUL",                 "\xe2\x95\x9d"            }, /* ╝ [BOX DRAWINGS DOUBLE UP AND LEFT]*/
	{"boxUR",                 "\xe2\x95\x9a"            }, /* ╚ [BOX DRAWINGS DOUBLE UP AND RIGHT]*/
	{"boxUl",                 "\xe2\x95\x9c"            }, /* ╜ [BOX DRAWINGS UP DOUBLE AND LEFT SINGLE]*/
	{"boxUr",                 "\xe2\x95\x99"            }, /* ╙ [BOX DRAWINGS UP DOUBLE AND RIGHT SINGLE]*/
	{"boxV",                  "\xe2\x95\x91"            }, /* ║ [BOX DRAWINGS DOUBLE VERTICAL]*/
	{"boxVH",                 "\xe2\x95\xac"            }, /* ╬ [BOX DRAWINGS DOUBLE VERTICAL AND HORIZONTAL]*/
	{"boxVL",                 "\xe2\x95\xa3"            }, /* ╣ [BOX DRAWINGS DOUBLE VERTICAL AND LEFT]*/
	{"boxVR",                 "\xe2\x95\xa0"            }, /* ╠ [BOX DRAWINGS DOUBLE VERTICAL AND RIGHT]*/
	{"boxVh",                 "\xe2\x95\xab"            }, /* ╫ [BOX DRAWINGS VERTICAL DOUBLE AND HORIZONTAL SINGLE]*/
	{"boxVl",                 "\xe2\x95\xa2"            }, /* ╢ [BOX DRAWINGS VERTICAL DOUBLE AND LEFT SINGLE]*/
	{"boxVr",                 "\xe2\x95\x9f"            }, /* ╟ [BOX DRAWINGS VERTICAL DOUBLE AND RIGHT SINGLE]*/
	{"boxbox",                "\xe2\xa7\x89"            }, /* ⧉ [TWO JOINED SQUARES]*/
	{"boxdL",                 "\xe2\x95\x95"            }, /* ╕ [BOX DRAWINGS DOWN SINGLE AND LEFT DOUBLE]*/
	{"boxdR",                 "\xe2\x95\x92"            }, /* ╒ [BOX DRAWINGS DOWN SINGLE AND RIGHT DOUBLE]*/
	{"boxdl",                 "\xe2\x94\x90"            }, /* ┐ [BOX DRAWINGS LIGHT DOWN AND LEFT]*/
	{"boxdr",                 "\xe2\x94\x8c"            }, /* ┌ [BOX DRAWINGS LIGHT DOWN AND RIGHT]*/
	{"boxh",                  "\xe2\x94\x80"            }, /* ─ [BOX DRAWINGS LIGHT HORIZONTAL]*/
	{"boxhD",                 "\xe2\x95\xa5"            }, /* ╥ [BOX DRAWINGS DOWN DOUBLE AND HORIZONTAL SINGLE]*/
	{"boxhU",                 "\xe2\x95\xa8"            }, /* ╨ [BOX DRAWINGS UP DOUBLE AND HORIZONTAL SINGLE]*/
	{"boxhd",                 "\xe2\x94\xac"            }, /* ┬ [BOX DRAWINGS LIGHT DOWN AND HORIZONTAL]*/
	{"boxhu",                 "\xe2\x94\xb4"            }, /* ┴ [BOX DRAWINGS LIGHT UP AND HORIZONTAL]*/
	{"boxminus",              "\xe2\x8a\x9f"            }, /* ⊟ [SQUARED MINUS]*/
	{"boxplus",               "\xe2\x8a\x9e"            }, /* ⊞ [SQUARED PLUS]*/
	{"boxtimes",              "\xe2\x8a\xa0"            }, /* ⊠ [SQUARED TIMES]*/
	{"boxuL",                 "\xe2\x95\x9b"            }, /* ╛ [BOX DRAWINGS UP SINGLE AND LEFT DOUBLE]*/
	{"boxuR",                 "\xe2\x95\x98"            }, /* ╘ [BOX DRAWINGS UP SINGLE AND RIGHT DOUBLE]*/
	{"boxul",                 "\xe2\x94\x98"            }, /* ┘ [BOX DRAWINGS LIGHT UP AND LEFT]*/
	{"boxur",                 "\xe2\x94\x94"            }, /* └ [BOX DRAWINGS LIGHT UP AND RIGHT]*/
	{"boxv",                  "\xe2\x94\x82"            }, /* │ [BOX DRAWINGS LIGHT VERTICAL]*/
	{"boxvH",                 "\xe2\x95\xaa"            }, /* ╪ [BOX DRAWINGS VERTICAL SINGLE AND HORIZONTAL DOUBLE]*/
	{"boxvL",                 "\xe2\x95\xa1"            }, /* ╡ [BOX DRAWINGS VERTICAL SINGLE AND LEFT DOUBLE]*/
	{"boxvR",                 "\xe2\x95\x9e"            }, /* ╞ [BOX DRAWINGS VERTICAL SINGLE AND RIGHT DOUBLE]*/
	{"boxvh",                 "\xe2\x94\xbc"            }, /* ┼ [BOX DRAWINGS LIGHT VERTICAL AND HORIZONTAL]*/
	{"boxvl",                 "\xe2\x94\xa4"            }, /* ┤ [BOX DRAWINGS LIGHT VERTICAL AND LEFT]*/
	{"boxvr",                 "\xe2\x94\x9c"            }, /* ├ [BOX DRAWINGS LIGHT VERTICAL AND RIGHT]*/
	{"bprime",                "\xe2\x80\xb5"            }, /* ‵ [REVERSED PRIME]*/
	{"breve",                 "\xcb\x98"                }, /* ˘ [BREVE]*/
	{"brvbar",                "\xc2\xa6"                }, /* ¦ [BROKEN BAR]*/
	{"bscr",                  "\xf0\x9d\x92\xb7"        }, /* 𝒷 [MATHEMATICAL SCRIPT SMALL B]*/
	{"bsemi",                 "\xe2\x81\x8f"            }, /* ⁏ [REVERSED SEMICOLON]*/
	{"bsim",                  "\xe2\x88\xbd"            }, /* ∽ [REVERSED TILDE]*/
	{"bsime",                 "\xe2\x8b\x8d"            }, /* ⋍ [REVERSED TILDE EQUALS]*/
	{"bsol",                  "\x5c"                    }, /* \ [REVERSE SOLIDUS]*/
	{"bsolb",                 "\xe2\xa7\x85"            }, /* ⧅ [SQUARED FALLING DIAGONAL SLASH]*/
	{"bsolhsub",              "\x5c\xe2\x8a\x82"        }, /* \⊂ [REVERSE SOLIDUS, SUBSET OF]*/
	{"bull",                  "\xe2\x80\xa2"            }, /* • [BULLET]*/
	{"bullet",                "\xe2\x80\xa2"            }, /* • [BULLET]*/
	{"bump",                  "\xe2\x89\x8e"            }, /* ≎ [GEOMETRICALLY EQUIVALENT TO]*/
	{"bumpE",                 "\xe2\xaa\xae"            }, /* ⪮ [EQUALS SIGN WITH BUMPY ABOVE]*/
	{"bumpe",                 "\xe2\x89\x8f"            }, /* ≏ [DIFFERENCE BETWEEN]*/
	{"bumpeq",                "\xe2\x89\x8f"            }, /* ≏ [DIFFERENCE BETWEEN]*/
	{"cacute",                "\xc4\x87"                }, /* ć [LATIN SMALL LETTER C WITH ACUTE]*/
	{"cap",                   "\xe2\x88\xa9"            }, /* ∩ [INTERSECTION]*/
	{"capand",                "\xe2\xa9\x84"            }, /* ⩄ [INTERSECTION WITH LOGICAL AND]*/
	{"capbrcup",              "\xe2\xa9\x89"            }, /* ⩉ [INTERSECTION ABOVE BAR ABOVE UNION]*/
	{"capcap",                "\xe2\xa9\x8b"            }, /* ⩋ [INTERSECTION BESIDE AND JOINED WITH INTERSECTION]*/
	{"capcup",                "\xe2\xa9\x87"            }, /* ⩇ [INTERSECTION ABOVE UNION]*/
	{"capdot",                "\xe2\xa9\x80"            }, /* ⩀ [INTERSECTION WITH DOT]*/
	{"caps",                  "\xe2\x88\xa9\xef\xb8\x80"}, /* ∩︀ [INTERSECTION with serifs]*/
	{"caret",                 "\xe2\x81\x81"            }, /* ⁁ [CARET INSERTION POINT]*/
	{"caron",                 "\xcb\x87"                }, /* ˇ [CARON]*/
	{"ccaps",                 "\xe2\xa9\x8d"            }, /* ⩍ [CLOSED INTERSECTION WITH SERIFS]*/
	{"ccaron",                "\xc4\x8d"                }, /* č [LATIN SMALL LETTER C WITH CARON]*/
	{"ccedil",                "\xc3\xa7"                }, /* ç [LATIN SMALL LETTER C WITH CEDILLA]*/
	{"ccirc",                 "\xc4\x89"                }, /* ĉ [LATIN SMALL LETTER C WITH CIRCUMFLEX]*/
	{"ccups",                 "\xe2\xa9\x8c"            }, /* ⩌ [CLOSED UNION WITH SERIFS]*/
	{"ccupssm",               "\xe2\xa9\x90"            }, /* ⩐ [CLOSED UNION WITH SERIFS AND SMASH PRODUCT]*/
	{"cdot",                  "\xc4\x8b"                }, /* ċ [LATIN SMALL LETTER C WITH DOT ABOVE]*/
	{"cedil",                 "\xc2\xb8"                }, /* ¸ [CEDILLA]*/
	{"cemptyv",               "\xe2\xa6\xb2"            }, /* ⦲ [EMPTY SET WITH SMALL CIRCLE ABOVE]*/
	{"cent",                  "\xc2\xa2"                }, /* ¢ [CENT SIGN]*/
	{"centerdot",             "\xc2\xb7"                }, /* · [MIDDLE DOT]*/
	{"cfr",                   "\xf0\x9d\x94\xa0"        }, /* 𝔠 [MATHEMATICAL FRAKTUR SMALL C]*/
	{"chcy",                  "\xd1\x87"                }, /* ч [CYRILLIC SMALL LETTER CHE]*/
	{"check",                 "\xe2\x9c\x93"            }, /* ✓ [CHECK MARK]*/
	{"checkmark",             "\xe2\x9c\x93"            }, /* ✓ [CHECK MARK]*/
	{"chi",                   "\xcf\x87"                }, /* χ [GREEK SMALL LETTER CHI]*/
	{"cir",                   "\xe2\x97\x8b"            }, /* ○ [WHITE CIRCLE]*/
	{"cirE",                  "\xe2\xa7\x83"            }, /* ⧃ [CIRCLE WITH TWO HORIZONTAL STROKES TO THE RIGHT]*/
	{"circ",                  "\xcb\x86"                }, /* ˆ [MODIFIER LETTER CIRCUMFLEX ACCENT]*/
	{"circeq",                "\xe2\x89\x97"            }, /* ≗ [RING EQUAL TO]*/
	{"circlearrowleft",       "\xe2\x86\xba"            }, /* ↺ [ANTICLOCKWISE OPEN CIRCLE ARROW]*/
	{"circlearrowright",      "\xe2\x86\xbb"            }, /* ↻ [CLOCKWISE OPEN CIRCLE ARROW]*/
	{"circledR",              "\xc2\xae"                }, /* ® [REGISTERED SIGN]*/
	{"circledS",              "\xe2\x93\x88"            }, /* Ⓢ [CIRCLED LATIN CAPITAL LETTER S]*/
	{"circledast",            "\xe2\x8a\x9b"            }, /* ⊛ [CIRCLED ASTERISK OPERATOR]*/
	{"circledcirc",           "\xe2\x8a\x9a"            }, /* ⊚ [CIRCLED RING OPERATOR]*/
	{"circleddash",           "\xe2\x8a\x9d"            }, /* ⊝ [CIRCLED DASH]*/
	{"cire",                  "\xe2\x89\x97"            }, /* ≗ [RING EQUAL TO]*/
	{"cirfnint",              "\xe2\xa8\x90"            }, /* ⨐ [CIRCULATION FUNCTION]*/
	{"cirmid",                "\xe2\xab\xaf"            }, /* ⫯ [VERTICAL LINE WITH CIRCLE ABOVE]*/
	{"cirscir",               "\xe2\xa7\x82"            }, /* ⧂ [CIRCLE WITH SMALL CIRCLE TO THE RIGHT]*/
	{"clubs",                 "\xe2\x99\xa3"            }, /* ♣ [BLACK CLUB SUIT]*/
	{"clubsuit",              "\xe2\x99\xa3"            }, /* ♣ [BLACK CLUB SUIT]*/
	{"colon",                 "\x3a"                    }, /* : [COLON]*/
	{"colone",                "\xe2\x89\x94"            }, /* ≔ [COLON EQUALS]*/
	{"coloneq",               "\xe2\x89\x94"            }, /* ≔ [COLON EQUALS]*/
	{"comma",                 "\x2c"                    }, /* , [COMMA]*/
	{"commat",                "\x40"                    }, /* @ [COMMERCIAL AT]*/
	{"comp",                  "\xe2\x88\x81"            }, /* ∁ [COMPLEMENT]*/
	{"compfn",                "\xe2\x88\x98"            }, /* ∘ [RING OPERATOR]*/
	{"complement",            "\xe2\x88\x81"            }, /* ∁ [COMPLEMENT]*/
	{"complexes",             "\xe2\x84\x82"            }, /* ℂ [DOUBLE-STRUCK CAPITAL C]*/
	{"cong",                  "\xe2\x89\x85"            }, /* ≅ [APPROXIMATELY EQUAL TO]*/
	{"congdot",               "\xe2\xa9\xad"            }, /* ⩭ [CONGRUENT WITH DOT ABOVE]*/
	{"conint",                "\xe2\x88\xae"            }, /* ∮ [CONTOUR INTEGRAL]*/
	{"copf",                  "\xf0\x9d\x95\x94"        }, /* 𝕔 [MATHEMATICAL DOUBLE-STRUCK SMALL C]*/
	{"coprod",                "\xe2\x88\x90"            }, /* ∐ [N-ARY COPRODUCT]*/
	{"copy",                  "\xc2\xa9"                }, /* © [COPYRIGHT SIGN]*/
	{"copysr",                "\xe2\x84\x97"            }, /* ℗ [SOUND RECORDING COPYRIGHT]*/
	{"cross",                 "\xe2\x9c\x97"            }, /* ✗ [BALLOT X]*/
	{"cscr",                  "\xf0\x9d\x92\xb8"        }, /* 𝒸 [MATHEMATICAL SCRIPT SMALL C]*/
	{"csub",                  "\xe2\xab\x8f"            }, /* ⫏ [CLOSED SUBSET]*/
	{"csube",                 "\xe2\xab\x91"            }, /* ⫑ [CLOSED SUBSET OR EQUAL TO]*/
	{"csup",                  "\xe2\xab\x90"            }, /* ⫐ [CLOSED SUPERSET]*/
	{"csupe",                 "\xe2\xab\x92"            }, /* ⫒ [CLOSED SUPERSET OR EQUAL TO]*/
	{"ctdot",                 "\xe2\x8b\xaf"            }, /* ⋯ [MIDLINE HORIZONTAL ELLIPSIS]*/
	{"cudarrl",               "\xe2\xa4\xb8"            }, /* ⤸ [RIGHT-SIDE ARC CLOCKWISE ARROW]*/
	{"cudarrr",               "\xe2\xa4\xb5"            }, /* ⤵ [ARROW POINTING RIGHTWARDS THEN CURVING DOWNWARDS]*/
	{"cuepr",                 "\xe2\x8b\x9e"            }, /* ⋞ [EQUAL TO OR PRECEDES]*/
	{"cuesc",                 "\xe2\x8b\x9f"            }, /* ⋟ [EQUAL TO OR SUCCEEDS]*/
	{"cularr",                "\xe2\x86\xb6"            }, /* ↶ [ANTICLOCKWISE TOP SEMICIRCLE ARROW]*/
	{"cularrp",               "\xe2\xa4\xbd"            }, /* ⤽ [TOP ARC ANTICLOCKWISE ARROW WITH PLUS]*/
	{"cup",                   "\xe2\x88\xaa"            }, /* ∪ [UNION]*/
	{"cupbrcap",              "\xe2\xa9\x88"            }, /* ⩈ [UNION ABOVE BAR ABOVE INTERSECTION]*/
	{"cupcap",                "\xe2\xa9\x86"            }, /* ⩆ [UNION ABOVE INTERSECTION]*/
	{"cupcup",                "\xe2\xa9\x8a"            }, /* ⩊ [UNION BESIDE AND JOINED WITH UNION]*/
	{"cupdot",                "\xe2\x8a\x8d"            }, /* ⊍ [MULTISET MULTIPLICATION]*/
	{"cupor",                 "\xe2\xa9\x85"            }, /* ⩅ [UNION WITH LOGICAL OR]*/
	{"cups",                  "\xe2\x88\xaa\xef\xb8\x80"}, /* ∪︀ [UNION with serifs]*/
	{"curarr",                "\xe2\x86\xb7"            }, /* ↷ [CLOCKWISE TOP SEMICIRCLE ARROW]*/
	{"curarrm",               "\xe2\xa4\xbc"            }, /* ⤼ [TOP ARC CLOCKWISE ARROW WITH MINUS]*/
	{"curlyeqprec",           "\xe2\x8b\x9e"            }, /* ⋞ [EQUAL TO OR PRECEDES]*/
	{"curlyeqsucc",           "\xe2\x8b\x9f"            }, /* ⋟ [EQUAL TO OR SUCCEEDS]*/
	{"curlyvee",              "\xe2\x8b\x8e"            }, /* ⋎ [CURLY LOGICAL OR]*/
	{"curlywedge",            "\xe2\x8b\x8f"            }, /* ⋏ [CURLY LOGICAL AND]*/
	{"curren",                "\xc2\xa4"                }, /* ¤ [CURRENCY SIGN]*/
	{"curvearrowleft",        "\xe2\x86\xb6"            }, /* ↶ [ANTICLOCKWISE TOP SEMICIRCLE ARROW]*/
	{"curvearrowright",       "\xe2\x86\xb7"            }, /* ↷ [CLOCKWISE TOP SEMICIRCLE ARROW]*/
	{"cuvee",                 "\xe2\x8b\x8e"            }, /* ⋎ [CURLY LOGICAL OR]*/
	{"cuwed",                 "\xe2\x8b\x8f"            }, /* ⋏ [CURLY LOGICAL AND]*/
	{"cwconint",              "\xe2\x88\xb2"            }, /* ∲ [CLOCKWISE CONTOUR INTEGRAL]*/
	{"cwint",                 "\xe2\x88\xb1"            }, /* ∱ [CLOCKWISE INTEGRAL]*/
	{"cylcty",                "\xe2\x8c\xad"            }, /* ⌭ [CYLINDRICITY]*/
	{"dArr",                  "\xe2\x87\x93"            }, /* ⇓ [DOWNWARDS DOUBLE ARROW]*/
	{"dHar",                  "\xe2\xa5\xa5"            }, /* ⥥ [DOWNWARDS HARPOON WITH BARB LEFT BESIDE DOWNWARDS HARPOON WITH BARB RIGHT]*/
	{"dagger",                "\xe2\x80\xa0"            }, /* † [DAGGER]*/
	{"dagger",                "\xe2\x80\xa0"            }, /* † [DAGGER]*/
	{"daleth",                "\xe2\x84\xb8"            }, /* ℸ [DALET SYMBOL]*/
	{"darr",                  "\xe2\x86\x93"            }, /* ↓ [DOWNWARDS ARROW]*/
	{"dash",                  "\xe2\x80\x90"            }, /* ‐ [HYPHEN]*/
	{"dashv",                 "\xe2\x8a\xa3"            }, /* ⊣ [LEFT TACK]*/
	{"dbkarow",               "\xe2\xa4\x8f"            }, /* ⤏ [RIGHTWARDS TRIPLE DASH ARROW]*/
	{"dblac",                 "\xcb\x9d"                }, /* ˝ [DOUBLE ACUTE ACCENT]*/
	{"dcaron",                "\xc4\x8f"                }, /* ď [LATIN SMALL LETTER D WITH CARON]*/
	{"dcy",                   "\xd0\xb4"                }, /* д [CYRILLIC SMALL LETTER DE]*/
	{"dd",                    "\xe2\x85\x86"            }, /* ⅆ [DOUBLE-STRUCK ITALIC SMALL D]*/
	{"ddagger",               "\xe2\x80\xa1"            }, /* ‡ [DOUBLE DAGGER]*/
	{"ddarr",                 "\xe2\x87\x8a"            }, /* ⇊ [DOWNWARDS PAIRED ARROWS]*/
	{"ddotseq",               "\xe2\xa9\xb7"            }, /* ⩷ [EQUALS SIGN WITH TWO DOTS ABOVE AND TWO DOTS BELOW]*/
	{"deg",                   "\xc2\xb0"                }, /* ° [DEGREE SIGN]*/
	{"delta",                 "\xce\xb4"                }, /* δ [GREEK SMALL LETTER DELTA]*/
	{"demptyv",               "\xe2\xa6\xb1"            }, /* ⦱ [EMPTY SET WITH OVERBAR]*/
	{"dfisht",                "\xe2\xa5\xbf"            }, /* ⥿ [DOWN FISH TAIL]*/
	{"dfr",                   "\xf0\x9d\x94\xa1"        }, /* 𝔡 [MATHEMATICAL FRAKTUR SMALL D]*/
	{"dharl",                 "\xe2\x87\x83"            }, /* ⇃ [DOWNWARDS HARPOON WITH BARB LEFTWARDS]*/
	{"dharr",                 "\xe2\x87\x82"            }, /* ⇂ [DOWNWARDS HARPOON WITH BARB RIGHTWARDS]*/
	{"diam",                  "\xe2\x8b\x84"            }, /* ⋄ [DIAMOND OPERATOR]*/
	{"diamond",               "\xe2\x8b\x84"            }, /* ⋄ [DIAMOND OPERATOR]*/
	{"diamondsuit",           "\xe2\x99\xa6"            }, /* ♦ [BLACK DIAMOND SUIT]*/
	{"diams",                 "\xe2\x99\xa6"            }, /* ♦ [BLACK DIAMOND SUIT]*/
	{"die",                   "\xc2\xa8"                }, /* ¨ [DIAERESIS]*/
	{"digamma",               "\xcf\x9d"                }, /* ϝ [GREEK SMALL LETTER DIGAMMA]*/
	{"disin",                 "\xe2\x8b\xb2"            }, /* ⋲ [ELEMENT OF WITH LONG HORIZONTAL STROKE]*/
	{"div",                   "\xc3\xb7"                }, /* ÷ [DIVISION SIGN]*/
	{"divide",                "\xc3\xb7"                }, /* ÷ [DIVISION SIGN]*/
	{"divideontimes",         "\xe2\x8b\x87"            }, /* ⋇ [DIVISION TIMES]*/
	{"divonx",                "\xe2\x8b\x87"            }, /* ⋇ [DIVISION TIMES]*/
	{"djcy",                  "\xd1\x92"                }, /* ђ [CYRILLIC SMALL LETTER DJE]*/
	{"dlcorn",                "\xe2\x8c\x9e"            }, /* ⌞ [BOTTOM LEFT CORNER]*/
	{"dlcrop",                "\xe2\x8c\x8d"            }, /* ⌍ [BOTTOM LEFT CROP]*/
	{"dollar",                "\x24"                    }, /* $ [DOLLAR SIGN]*/
	{"dopf",                  "\xf0\x9d\x95\x95"        }, /* 𝕕 [MATHEMATICAL DOUBLE-STRUCK SMALL D]*/
	{"dot",                   "\xcb\x99"                }, /* ˙ [DOT ABOVE]*/
	{"doteq",                 "\xe2\x89\x90"            }, /* ≐ [APPROACHES THE LIMIT]*/
	{"doteqdot",              "\xe2\x89\x91"            }, /* ≑ [GEOMETRICALLY EQUAL TO]*/
	{"dotminus",              "\xe2\x88\xb8"            }, /* ∸ [DOT MINUS]*/
	{"dotplus",               "\xe2\x88\x94"            }, /* ∔ [DOT PLUS]*/
	{"dotsquare",             "\xe2\x8a\xa1"            }, /* ⊡ [SQUARED DOT OPERATOR]*/
	{"doublebarwedge",        "\xe2\x8c\x86"            }, /* ⌆ [PERSPECTIVE]*/
	{"downarrow",             "\xe2\x86\x93"            }, /* ↓ [DOWNWARDS ARROW]*/
	{"downdownarrows",        "\xe2\x87\x8a"            }, /* ⇊ [DOWNWARDS PAIRED ARROWS]*/
	{"downharpoonleft",       "\xe2\x87\x83"            }, /* ⇃ [DOWNWARDS HARPOON WITH BARB LEFTWARDS]*/
	{"downharpoonright",      "\xe2\x87\x82"            }, /* ⇂ [DOWNWARDS HARPOON WITH BARB RIGHTWARDS]*/
	{"drbkarow",              "\xe2\xa4\x90"            }, /* ⤐ [RIGHTWARDS TWO-HEADED TRIPLE DASH ARROW]*/
	{"drcorn",                "\xe2\x8c\x9f"            }, /* ⌟ [BOTTOM RIGHT CORNER]*/
	{"drcrop",                "\xe2\x8c\x8c"            }, /* ⌌ [BOTTOM RIGHT CROP]*/
	{"dscr",                  "\xf0\x9d\x92\xb9"        }, /* 𝒹 [MATHEMATICAL SCRIPT SMALL D]*/
	{"dscy",                  "\xd1\x95"                }, /* ѕ [CYRILLIC SMALL LETTER DZE]*/
	{"dsol",                  "\xe2\xa7\xb6"            }, /* ⧶ [SOLIDUS WITH OVERBAR]*/
	{"dstrok",                "\xc4\x91"                }, /* đ [LATIN SMALL LETTER D WITH STROKE]*/
	{"dtdot",                 "\xe2\x8b\xb1"            }, /* ⋱ [DOWN RIGHT DIAGONAL ELLIPSIS]*/
	{"dtri",                  "\xe2\x96\xbf"            }, /* ▿ [WHITE DOWN-POINTING SMALL TRIANGLE]*/
	{"dtrif",                 "\xe2\x96\xbe"            }, /* ▾ [BLACK DOWN-POINTING SMALL TRIANGLE]*/
	{"duarr",                 "\xe2\x87\xb5"            }, /* ⇵ [DOWNWARDS ARROW LEFTWARDS OF UPWARDS ARROW]*/
	{"duhar",                 "\xe2\xa5\xaf"            }, /* ⥯ [DOWNWARDS HARPOON WITH BARB LEFT BESIDE UPWARDS HARPOON WITH BARB RIGHT]*/
	{"dwangle",               "\xe2\xa6\xa6"            }, /* ⦦ [OBLIQUE ANGLE OPENING UP]*/
	{"dzcy",                  "\xd1\x9f"                }, /* џ [CYRILLIC SMALL LETTER DZHE]*/
	{"dzigrarr",              "\xe2\x9f\xbf"            }, /* ⟿ [LONG RIGHTWARDS SQUIGGLE ARROW]*/
	{"eDDot",                 "\xe2\xa9\xb7"            }, /* ⩷ [EQUALS SIGN WITH TWO DOTS ABOVE AND TWO DOTS BELOW]*/
	{"eDot",                  "\xe2\x89\x91"            }, /* ≑ [GEOMETRICALLY EQUAL TO]*/
	{"eacute",                "\xc3\xa9"                }, /* é [LATIN SMALL LETTER E WITH ACUTE]*/
	{"easter",                "\xe2\xa9\xae"            }, /* ⩮ [EQUALS WITH ASTERISK]*/
	{"ecaron",                "\xc4\x9b"                }, /* ě [LATIN SMALL LETTER E WITH CARON]*/
	{"ecir",                  "\xe2\x89\x96"            }, /* ≖ [RING IN EQUAL TO]*/
	{"ecirc",                 "\xc3\xaa"                }, /* ê [LATIN SMALL LETTER E WITH CIRCUMFLEX]*/
	{"ecolon",                "\xe2\x89\x95"            }, /* ≕ [EQUALS COLON]*/
	{"ecy",                   "\xd1\x8d"                }, /* э [CYRILLIC SMALL LETTER E]*/
	{"edot",                  "\xc4\x97"                }, /* ė [LATIN SMALL LETTER E WITH DOT ABOVE]*/
	{"ee",                    "\xe2\x85\x87"            }, /* ⅇ [DOUBLE-STRUCK ITALIC SMALL E]*/
	{"efDot",                 "\xe2\x89\x92"            }, /* ≒ [APPROXIMATELY EQUAL TO OR THE IMAGE OF]*/
	{"efr",                   "\xf0\x9d\x94\xa2"        }, /* 𝔢 [MATHEMATICAL FRAKTUR SMALL E]*/
	{"eg",                    "\xe2\xaa\x9a"            }, /* ⪚ [DOUBLE-LINE EQUAL TO OR GREATER-THAN]*/
	{"egrave",                "\xc3\xa8"                }, /* è [LATIN SMALL LETTER E WITH GRAVE]*/
	{"egs",                   "\xe2\xaa\x96"            }, /* ⪖ [SLANTED EQUAL TO OR GREATER-THAN]*/
	{"egsdot",                "\xe2\xaa\x98"            }, /* ⪘ [SLANTED EQUAL TO OR GREATER-THAN WITH DOT INSIDE]*/
	{"el",                    "\xe2\xaa\x99"            }, /* ⪙ [DOUBLE-LINE EQUAL TO OR LESS-THAN]*/
	{"elinters",              "\xef\xbf\xbd"            }, /* � [REPLACEMENT CHARACTER]*/
	{"ell",                   "\xe2\x84\x93"            }, /* ℓ [SCRIPT SMALL L]*/
	{"els",                   "\xe2\xaa\x95"            }, /* ⪕ [SLANTED EQUAL TO OR LESS-THAN]*/
	{"elsdot",                "\xe2\xaa\x97"            }, /* ⪗ [SLANTED EQUAL TO OR LESS-THAN WITH DOT INSIDE]*/
	{"emacr",                 "\xc4\x93"                }, /* ē [LATIN SMALL LETTER E WITH MACRON]*/
	{"empty",                 "\xe2\x88\x85"            }, /* ∅ [EMPTY SET]*/
	{"emptyset",              "\xe2\x88\x85"            }, /* ∅ [EMPTY SET]*/
	{"emptyv",                "\xe2\x88\x85"            }, /* ∅ [EMPTY SET]*/
	{"emsp",                  "\xe2\x80\x83"            }, /*   [EM SPACE]*/
	{"emsp13",                "\xe2\x80\x84"            }, /*   [THREE-PER-EM SPACE]*/
	{"emsp14",                "\xe2\x80\x85"            }, /*   [FOUR-PER-EM SPACE]*/
	{"eng",                   "\xc5\x8b"                }, /* ŋ [LATIN SMALL LETTER ENG]*/
	{"ensp",                  "\xe2\x80\x82"            }, /*   [EN SPACE]*/
	{"eogon",                 "\xc4\x99"                }, /* ę [LATIN SMALL LETTER E WITH OGONEK]*/
	{"eopf",                  "\xf0\x9d\x95\x96"        }, /* 𝕖 [MATHEMATICAL DOUBLE-STRUCK SMALL E]*/
	{"epar",                  "\xe2\x8b\x95"            }, /* ⋕ [EQUAL AND PARALLEL TO]*/
	{"eparsl",                "\xe2\xa7\xa3"            }, /* ⧣ [EQUALS SIGN AND SLANTED PARALLEL]*/
	{"eplus",                 "\xe2\xa9\xb1"            }, /* ⩱ [EQUALS SIGN ABOVE PLUS SIGN]*/
	{"epsi",                  "\xcf\xb5"                }, /* ϵ [GREEK LUNATE EPSILON SYMBOL]*/
	{"epsiv",                 "\xce\xb5"                }, /* ε [GREEK SMALL LETTER EPSILON]*/
	{"eqcirc",                "\xe2\x89\x96"            }, /* ≖ [RING IN EQUAL TO]*/
	{"eqcolon",               "\xe2\x89\x95"            }, /* ≕ [EQUALS COLON]*/
	{"eqsim",                 "\xe2\x89\x82"            }, /* ≂ [MINUS TILDE]*/
	{"eqslantgtr",            "\xe2\xaa\x96"            }, /* ⪖ [SLANTED EQUAL TO OR GREATER-THAN]*/
	{"eqslantless",           "\xe2\xaa\x95"            }, /* ⪕ [SLANTED EQUAL TO OR LESS-THAN]*/
	{"equals",                "\x3d"                    }, /* = [EQUALS SIGN]*/
	{"equest",                "\xe2\x89\x9f"            }, /* ≟ [QUESTIONED EQUAL TO]*/
	{"equiv",                 "\xe2\x89\xa1"            }, /* ≡ [IDENTICAL TO]*/
	{"equivDD",               "\xe2\xa9\xb8"            }, /* ⩸ [EQUIVALENT WITH FOUR DOTS ABOVE]*/
	{"eqvparsl",              "\xe2\xa7\xa5"            }, /* ⧥ [IDENTICAL TO AND SLANTED PARALLEL]*/
	{"erDot",                 "\xe2\x89\x93"            }, /* ≓ [IMAGE OF OR APPROXIMATELY EQUAL TO]*/
	{"erarr",                 "\xe2\xa5\xb1"            }, /* ⥱ [EQUALS SIGN ABOVE RIGHTWARDS ARROW]*/
	{"escr",                  "\xe2\x84\xaf"            }, /* ℯ [SCRIPT SMALL E]*/
	{"esdot",                 "\xe2\x89\x90"            }, /* ≐ [APPROACHES THE LIMIT]*/
	{"esim",                  "\xe2\x89\x82"            }, /* ≂ [MINUS TILDE]*/
	{"eta",                   "\xce\xb7"                }, /* η [GREEK SMALL LETTER ETA]*/
	{"eth",                   "\xc3\xb0"                }, /* ð [LATIN SMALL LETTER ETH]*/
	{"euml",                  "\xc3\xab"                }, /* ë [LATIN SMALL LETTER E WITH DIAERESIS]*/
	{"excl",                  "\x21"                    }, /* ! [EXCLAMATION MARK]*/
	{"exist",                 "\xe2\x88\x83"            }, /* ∃ [THERE EXISTS]*/
	{"expectation",           "\xe2\x84\xb0"            }, /* ℰ [SCRIPT CAPITAL E]*/
	{"exponentiale",          "\xe2\x85\x87"            }, /* ⅇ [DOUBLE-STRUCK ITALIC SMALL E]*/
	{"fallingdotseq",         "\xe2\x89\x92"            }, /* ≒ [APPROXIMATELY EQUAL TO OR THE IMAGE OF]*/
	{"fcy",                   "\xd1\x84"                }, /* ф [CYRILLIC SMALL LETTER EF]*/
	{"female",                "\xe2\x99\x80"            }, /* ♀ [FEMALE SIGN]*/
	{"ffilig",                "\xef\xac\x83"            }, /* ﬃ [LATIN SMALL LIGATURE FFI]*/
	{"fflig",                 "\xef\xac\x80"            }, /* ﬀ [LATIN SMALL LIGATURE FF]*/
	{"ffllig",                "\xef\xac\x84"            }, /* ﬄ [LATIN SMALL LIGATURE FFL]*/
	{"ffr",                   "\xf0\x9d\x94\xa3"        }, /* 𝔣 [MATHEMATICAL FRAKTUR SMALL F]*/
	{"filig",                 "\xef\xac\x81"            }, /* ﬁ [LATIN SMALL LIGATURE FI]*/
	{"flat",                  "\xe2\x99\xad"            }, /* ♭ [MUSIC FLAT SIGN]*/
	{"fllig",                 "\xef\xac\x82"            }, /* ﬂ [LATIN SMALL LIGATURE FL]*/
	{"fltns",                 "\xe2\x96\xb1"            }, /* ▱ [WHITE PARALLELOGRAM]*/
	{"fnof",                  "\xc6\x92"                }, /* ƒ [LATIN SMALL LETTER F WITH HOOK]*/
	{"fopf",                  "\xf0\x9d\x95\x97"        }, /* 𝕗 [MATHEMATICAL DOUBLE-STRUCK SMALL F]*/
	{"forall",                "\xe2\x88\x80"            }, /* ∀ [FOR ALL]*/
	{"fork",                  "\xe2\x8b\x94"            }, /* ⋔ [PITCHFORK]*/
	{"forkv",                 "\xe2\xab\x99"            }, /* ⫙ [ELEMENT OF OPENING DOWNWARDS]*/
	{"fpartint",              "\xe2\xa8\x8d"            }, /* ⨍ [FINITE PART INTEGRAL]*/
	{"frac12",                "\xc2\xbd"                }, /* ½ [VULGAR FRACTION ONE HALF]*/
	{"frac13",                "\xe2\x85\x93"            }, /* ⅓ [VULGAR FRACTION ONE THIRD]*/
	{"frac14",                "\xc2\xbc"                }, /* ¼ [VULGAR FRACTION ONE QUARTER]*/
	{"frac15",                "\xe2\x85\x95"            }, /* ⅕ [VULGAR FRACTION ONE FIFTH]*/
	{"frac16",                "\xe2\x85\x99"            }, /* ⅙ [VULGAR FRACTION ONE SIXTH]*/
	{"frac18",                "\xe2\x85\x9b"            }, /* ⅛ [VULGAR FRACTION ONE EIGHTH]*/
	{"frac23",                "\xe2\x85\x94"            }, /* ⅔ [VULGAR FRACTION TWO THIRDS]*/
	{"frac25",                "\xe2\x85\x96"            }, /* ⅖ [VULGAR FRACTION TWO FIFTHS]*/
	{"frac34",                "\xc2\xbe"                }, /* ¾ [VULGAR FRACTION THREE QUARTERS]*/
	{"frac35",                "\xe2\x85\x97"            }, /* ⅗ [VULGAR FRACTION THREE FIFTHS]*/
	{"frac38",                "\xe2\x85\x9c"            }, /* ⅜ [VULGAR FRACTION THREE EIGHTHS]*/
	{"frac45",                "\xe2\x85\x98"            }, /* ⅘ [VULGAR FRACTION FOUR FIFTHS]*/
	{"frac56",                "\xe2\x85\x9a"            }, /* ⅚ [VULGAR FRACTION FIVE SIXTHS]*/
	{"frac58",                "\xe2\x85\x9d"            }, /* ⅝ [VULGAR FRACTION FIVE EIGHTHS]*/
	{"frac78",                "\xe2\x85\x9e"            }, /* ⅞ [VULGAR FRACTION SEVEN EIGHTHS]*/
	{"frown",                 "\xe2\x8c\xa2"            }, /* ⌢ [FROWN]*/
	{"fscr",                  "\xf0\x9d\x92\xbb"        }, /* 𝒻 [MATHEMATICAL SCRIPT SMALL F]*/
	{"gE",                    "\xe2\x89\xa7"            }, /* ≧ [GREATER-THAN OVER EQUAL TO]*/
	{"gEl",                   "\xe2\xaa\x8c"            }, /* ⪌ [GREATER-THAN ABOVE DOUBLE-LINE EQUAL ABOVE LESS-THAN]*/
	{"gacute",                "\xc7\xb5"                }, /* ǵ [LATIN SMALL LETTER G WITH ACUTE]*/
	{"gamma",                 "\xce\xb3"                }, /* γ [GREEK SMALL LETTER GAMMA]*/
	{"gammad",                "\xcf\x9d"                }, /* ϝ [GREEK SMALL LETTER DIGAMMA]*/
	{"gap",                   "\xe2\xaa\x86"            }, /* ⪆ [GREATER-THAN OR APPROXIMATE]*/
	{"gbreve",                "\xc4\x9f"                }, /* ğ [LATIN SMALL LETTER G WITH BREVE]*/
	{"gcirc",                 "\xc4\x9d"                }, /* ĝ [LATIN SMALL LETTER G WITH CIRCUMFLEX]*/
	{"gcy",                   "\xd0\xb3"                }, /* г [CYRILLIC SMALL LETTER GHE]*/
	{"gdot",                  "\xc4\xa1"                }, /* ġ [LATIN SMALL LETTER G WITH DOT ABOVE]*/
	{"ge",                    "\xe2\x89\xa5"            }, /* ≥ [GREATER-THAN OR EQUAL TO]*/
	{"gel",                   "\xe2\x8b\x9b"            }, /* ⋛ [GREATER-THAN EQUAL TO OR LESS-THAN]*/
	{"geq",                   "\xe2\x89\xa5"            }, /* ≥ [GREATER-THAN OR EQUAL TO]*/
	{"geqq",                  "\xe2\x89\xa7"            }, /* ≧ [GREATER-THAN OVER EQUAL TO]*/
	{"geqslant",              "\xe2\xa9\xbe"            }, /* ⩾ [GREATER-THAN OR SLANTED EQUAL TO]*/
	{"ges",                   "\xe2\xa9\xbe"            }, /* ⩾ [GREATER-THAN OR SLANTED EQUAL TO]*/
	{"gescc",                 "\xe2\xaa\xa9"            }, /* ⪩ [GREATER-THAN CLOSED BY CURVE ABOVE SLANTED EQUAL]*/
	{"gesdot",                "\xe2\xaa\x80"            }, /* ⪀ [GREATER-THAN OR SLANTED EQUAL TO WITH DOT INSIDE]*/
	{"gesdoto",               "\xe2\xaa\x82"            }, /* ⪂ [GREATER-THAN OR SLANTED EQUAL TO WITH DOT ABOVE]*/
	{"gesdotol",              "\xe2\xaa\x84"            }, /* ⪄ [GREATER-THAN OR SLANTED EQUAL TO WITH DOT ABOVE LEFT]*/
	{"gesl",                  "\xe2\x8b\x9b\xef\xb8\x80"}, /* ⋛︀ [GREATER-THAN slanted EQUAL TO OR LESS-THAN]*/
	{"gesles",                "\xe2\xaa\x94"            }, /* ⪔ [GREATER-THAN ABOVE SLANTED EQUAL ABOVE LESS-THAN ABOVE SLANTED EQUAL]*/
	{"gfr",                   "\xf0\x9d\x94\xa4"        }, /* 𝔤 [MATHEMATICAL FRAKTUR SMALL G]*/
	{"gg",                    "\xe2\x89\xab"            }, /* ≫ [MUCH GREATER-THAN]*/
	{"ggg",                   "\xe2\x8b\x99"            }, /* ⋙ [VERY MUCH GREATER-THAN]*/
	{"gimel",                 "\xe2\x84\xb7"            }, /* ℷ [GIMEL SYMBOL]*/
	{"gjcy",                  "\xd1\x93"                }, /* ѓ [CYRILLIC SMALL LETTER GJE]*/
	{"gl",                    "\xe2\x89\xb7"            }, /* ≷ [GREATER-THAN OR LESS-THAN]*/
	{"glE",                   "\xe2\xaa\x92"            }, /* ⪒ [GREATER-THAN ABOVE LESS-THAN ABOVE DOUBLE-LINE EQUAL]*/
	{"gla",                   "\xe2\xaa\xa5"            }, /* ⪥ [GREATER-THAN BESIDE LESS-THAN]*/
	{"glj",                   "\xe2\xaa\xa4"            }, /* ⪤ [GREATER-THAN OVERLAPPING LESS-THAN]*/
	{"gnE",                   "\xe2\x89\xa9"            }, /* ≩ [GREATER-THAN BUT NOT EQUAL TO]*/
	{"gnap",                  "\xe2\xaa\x8a"            }, /* ⪊ [GREATER-THAN AND NOT APPROXIMATE]*/
	{"gnapprox",              "\xe2\xaa\x8a"            }, /* ⪊ [GREATER-THAN AND NOT APPROXIMATE]*/
	{"gne",                   "\xe2\xaa\x88"            }, /* ⪈ [GREATER-THAN AND SINGLE-LINE NOT EQUAL TO]*/
	{"gneq",                  "\xe2\xaa\x88"            }, /* ⪈ [GREATER-THAN AND SINGLE-LINE NOT EQUAL TO]*/
	{"gneqq",                 "\xe2\x89\xa9"            }, /* ≩ [GREATER-THAN BUT NOT EQUAL TO]*/
	{"gnsim",                 "\xe2\x8b\xa7"            }, /* ⋧ [GREATER-THAN BUT NOT EQUIVALENT TO]*/
	{"gopf",                  "\xf0\x9d\x95\x98"        }, /* 𝕘 [MATHEMATICAL DOUBLE-STRUCK SMALL G]*/
	{"grave",                 "\x60"                    }, /* ` [GRAVE ACCENT]*/
	{"gscr",                  "\xe2\x84\x8a"            }, /* ℊ [SCRIPT SMALL G]*/
	{"gsim",                  "\xe2\x89\xb3"            }, /* ≳ [GREATER-THAN OR EQUIVALENT TO]*/
	{"gsime",                 "\xe2\xaa\x8e"            }, /* ⪎ [GREATER-THAN ABOVE SIMILAR OR EQUAL]*/
	{"gsiml",                 "\xe2\xaa\x90"            }, /* ⪐ [GREATER-THAN ABOVE SIMILAR ABOVE LESS-THAN]*/
	{"gt",                    "\x3e"                    }, /* > [GREATER-THAN SIGN]*/
	{"gtcc",                  "\xe2\xaa\xa7"            }, /* ⪧ [GREATER-THAN CLOSED BY CURVE]*/
	{"gtcir",                 "\xe2\xa9\xba"            }, /* ⩺ [GREATER-THAN WITH CIRCLE INSIDE]*/
	{"gtdot",                 "\xe2\x8b\x97"            }, /* ⋗ [GREATER-THAN WITH DOT]*/
	{"gtlPar",                "\xe2\xa6\x95"            }, /* ⦕ [DOUBLE LEFT ARC GREATER-THAN BRACKET]*/
	{"gtquest",               "\xe2\xa9\xbc"            }, /* ⩼ [GREATER-THAN WITH QUESTION MARK ABOVE]*/
	{"gtrapprox",             "\xe2\xaa\x86"            }, /* ⪆ [GREATER-THAN OR APPROXIMATE]*/
	{"gtrarr",                "\xe2\xa5\xb8"            }, /* ⥸ [GREATER-THAN ABOVE RIGHTWARDS ARROW]*/
	{"gtrdot",                "\xe2\x8b\x97"            }, /* ⋗ [GREATER-THAN WITH DOT]*/
	{"gtreqless",             "\xe2\x8b\x9b"            }, /* ⋛ [GREATER-THAN EQUAL TO OR LESS-THAN]*/
	{"gtreqqless",            "\xe2\xaa\x8c"            }, /* ⪌ [GREATER-THAN ABOVE DOUBLE-LINE EQUAL ABOVE LESS-THAN]*/
	{"gtrless",               "\xe2\x89\xb7"            }, /* ≷ [GREATER-THAN OR LESS-THAN]*/
	{"gtrsim",                "\xe2\x89\xb3"            }, /* ≳ [GREATER-THAN OR EQUIVALENT TO]*/
	{"gvertneqq",             "\xe2\x89\xa9\xef\xb8\x80"}, /* ≩︀ [GREATER-THAN BUT NOT EQUAL TO - with vertical stroke]*/
	{"gvnE",                  "\xe2\x89\xa9\xef\xb8\x80"}, /* ≩︀ [GREATER-THAN BUT NOT EQUAL TO - with vertical stroke]*/
	{"hArr",                  "\xe2\x87\x94"            }, /* ⇔ [LEFT RIGHT DOUBLE ARROW]*/
	{"hairsp",                "\xe2\x80\x8a"            }, /*   [HAIR SPACE]*/
	{"half",                  "\xc2\xbd"                }, /* ½ [VULGAR FRACTION ONE HALF]*/
	{"hamilt",                "\xe2\x84\x8b"            }, /* ℋ [SCRIPT CAPITAL H]*/
	{"hardcy",                "\xd1\x8a"                }, /* ъ [CYRILLIC SMALL LETTER HARD SIGN]*/
	{"harr",                  "\xe2\x86\x94"            }, /* ↔ [LEFT RIGHT ARROW]*/
	{"harrcir",               "\xe2\xa5\x88"            }, /* ⥈ [LEFT RIGHT ARROW THROUGH SMALL CIRCLE]*/
	{"harrw",                 "\xe2\x86\xad"            }, /* ↭ [LEFT RIGHT WAVE ARROW]*/
	{"hbar",                  "\xe2\x84\x8f"            }, /* ℏ [PLANCK CONSTANT OVER TWO PI]*/
	{"hcirc",                 "\xc4\xa5"                }, /* ĥ [LATIN SMALL LETTER H WITH CIRCUMFLEX]*/
	{"hearts",                "\xe2\x99\xa5"            }, /* ♥ [BLACK HEART SUIT]*/
	{"heartsuit",             "\xe2\x99\xa5"            }, /* ♥ [BLACK HEART SUIT]*/
	{"hellip",                "\xe2\x80\xa6"            }, /* … [HORIZONTAL ELLIPSIS]*/
	{"hercon",                "\xe2\x8a\xb9"            }, /* ⊹ [HERMITIAN CONJUGATE MATRIX]*/
	{"hfr",                   "\xf0\x9d\x94\xa5"        }, /* 𝔥 [MATHEMATICAL FRAKTUR SMALL H]*/
	{"hksearow",              "\xe2\xa4\xa5"            }, /* ⤥ [SOUTH EAST ARROW WITH HOOK]*/
	{"hkswarow",              "\xe2\xa4\xa6"            }, /* ⤦ [SOUTH WEST ARROW WITH HOOK]*/
	{"hoarr",                 "\xe2\x87\xbf"            }, /* ⇿ [LEFT RIGHT OPEN-HEADED ARROW]*/
	{"homtht",                "\xe2\x88\xbb"            }, /* ∻ [HOMOTHETIC]*/
	{"hookleftarrow",         "\xe2\x86\xa9"            }, /* ↩ [LEFTWARDS ARROW WITH HOOK]*/
	{"hookrightarrow",        "\xe2\x86\xaa"            }, /* ↪ [RIGHTWARDS ARROW WITH HOOK]*/
	{"hopf",                  "\xf0\x9d\x95\x99"        }, /* 𝕙 [MATHEMATICAL DOUBLE-STRUCK SMALL H]*/
	{"horbar",                "\xe2\x80\x95"            }, /* ― [HORIZONTAL BAR]*/
	{"hscr",                  "\xf0\x9d\x92\xbd"        }, /* 𝒽 [MATHEMATICAL SCRIPT SMALL H]*/
	{"hslash",                "\xe2\x84\x8f"            }, /* ℏ [PLANCK CONSTANT OVER TWO PI]*/
	{"hstrok",                "\xc4\xa7"                }, /* ħ [LATIN SMALL LETTER H WITH STROKE]*/
	{"hybull",                "\xe2\x81\x83"            }, /* ⁃ [HYPHEN BULLET]*/
	{"hyphen",                "\xe2\x80\x90"            }, /* ‐ [HYPHEN]*/
	{"iacute",                "\xc3\xad"                }, /* í [LATIN SMALL LETTER I WITH ACUTE]*/
	{"ic",                    "\xe2\x81\xa3"            }, /* ⁣ [INVISIBLE SEPARATOR]*/
	{"icirc",                 "\xc3\xae"                }, /* î [LATIN SMALL LETTER I WITH CIRCUMFLEX]*/
	{"icy",                   "\xd0\xb8"                }, /* и [CYRILLIC SMALL LETTER I]*/
	{"iecy",                  "\xd0\xb5"                }, /* е [CYRILLIC SMALL LETTER IE]*/
	{"iexcl",                 "\xc2\xa1"                }, /* ¡ [INVERTED EXCLAMATION MARK]*/
	{"iff",                   "\xe2\x87\x94"            }, /* ⇔ [LEFT RIGHT DOUBLE ARROW]*/
	{"ifr",                   "\xf0\x9d\x94\xa6"        }, /* 𝔦 [MATHEMATICAL FRAKTUR SMALL I]*/
	{"igrave",                "\xc3\xac"                }, /* ì [LATIN SMALL LETTER I WITH GRAVE]*/
	{"ii",                    "\xe2\x85\x88"            }, /* ⅈ [DOUBLE-STRUCK ITALIC SMALL I]*/
	{"iiiint",                "\xe2\xa8\x8c"            }, /* ⨌ [QUADRUPLE INTEGRAL OPERATOR]*/
	{"iiint",                 "\xe2\x88\xad"            }, /* ∭ [TRIPLE INTEGRAL]*/
	{"iinfin",                "\xe2\xa7\x9c"            }, /* ⧜ [INCOMPLETE INFINITY]*/
	{"iiota",                 "\xe2\x84\xa9"            }, /* ℩ [TURNED GREEK SMALL LETTER IOTA]*/
	{"ijlig",                 "\xc4\xb3"                }, /* ĳ [LATIN SMALL LIGATURE IJ]*/
	{"imacr",                 "\xc4\xab"                }, /* ī [LATIN SMALL LETTER I WITH MACRON]*/
	{"image",                 "\xe2\x84\x91"            }, /* ℑ [BLACK-LETTER CAPITAL I]*/
	{"imagline",              "\xe2\x84\x90"            }, /* ℐ [SCRIPT CAPITAL I]*/
	{"imagpart",              "\xe2\x84\x91"            }, /* ℑ [BLACK-LETTER CAPITAL I]*/
	{"imath",                 "\xc4\xb1"                }, /* ı [LATIN SMALL LETTER DOTLESS I]*/
	{"imof",                  "\xe2\x8a\xb7"            }, /* ⊷ [IMAGE OF]*/
	{"imped",                 "\xc6\xb5"                }, /* Ƶ [LATIN CAPITAL LETTER Z WITH STROKE]*/
	{"in",                    "\xe2\x88\x88"            }, /* ∈ [ELEMENT OF]*/
	{"incare",                "\xe2\x84\x85"            }, /* ℅ [CARE OF]*/
	{"infin",                 "\xe2\x88\x9e"            }, /* ∞ [INFINITY]*/
	{"infintie",              "\xe2\xa7\x9d"            }, /* ⧝ [TIE OVER INFINITY]*/
	{"inodot",                "\xc4\xb1"                }, /* ı [LATIN SMALL LETTER DOTLESS I]*/
	{"int",                   "\xe2\x88\xab"            }, /* ∫ [INTEGRAL]*/
	{"intcal",                "\xe2\x8a\xba"            }, /* ⊺ [INTERCALATE]*/
	{"integers",              "\xe2\x84\xa4"            }, /* ℤ [DOUBLE-STRUCK CAPITAL Z]*/
	{"intercal",              "\xe2\x8a\xba"            }, /* ⊺ [INTERCALATE]*/
	{"intlarhk",              "\xe2\xa8\x97"            }, /* ⨗ [INTEGRAL WITH LEFTWARDS ARROW WITH HOOK]*/
	{"intprod",               "\xe2\xa8\xbc"            }, /* ⨼ [INTERIOR PRODUCT]*/
	{"iocy",                  "\xd1\x91"                }, /* ё [CYRILLIC SMALL LETTER IO]*/
	{"iogon",                 "\xc4\xaf"                }, /* į [LATIN SMALL LETTER I WITH OGONEK]*/
	{"iopf",                  "\xf0\x9d\x95\x9a"        }, /* 𝕚 [MATHEMATICAL DOUBLE-STRUCK SMALL I]*/
	{"iota",                  "\xce\xb9"                }, /* ι [GREEK SMALL LETTER IOTA]*/
	{"iprod",                 "\xe2\xa8\xbc"            }, /* ⨼ [INTERIOR PRODUCT]*/
	{"iquest",                "\xc2\xbf"                }, /* ¿ [INVERTED QUESTION MARK]*/
	{"iscr",                  "\xf0\x9d\x92\xbe"        }, /* 𝒾 [MATHEMATICAL SCRIPT SMALL I]*/
	{"isin",                  "\xe2\x88\x88"            }, /* ∈ [ELEMENT OF]*/
	{"isinE",                 "\xe2\x8b\xb9"            }, /* ⋹ [ELEMENT OF WITH TWO HORIZONTAL STROKES]*/
	{"isindot",               "\xe2\x8b\xb5"            }, /* ⋵ [ELEMENT OF WITH DOT ABOVE]*/
	{"isins",                 "\xe2\x8b\xb4"            }, /* ⋴ [SMALL ELEMENT OF WITH VERTICAL BAR AT END OF HORIZONTAL STROKE]*/
	{"isinsv",                "\xe2\x8b\xb3"            }, /* ⋳ [ELEMENT OF WITH VERTICAL BAR AT END OF HORIZONTAL STROKE]*/
	{"isinv",                 "\xe2\x88\x88"            }, /* ∈ [ELEMENT OF]*/
	{"it",                    "\xe2\x81\xa2"            }, /* ⁢ [INVISIBLE TIMES]*/
	{"itilde",                "\xc4\xa9"                }, /* ĩ [LATIN SMALL LETTER I WITH TILDE]*/
	{"iukcy",                 "\xd1\x96"                }, /* і [CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I]*/
	{"iuml",                  "\xc3\xaf"                }, /* ï [LATIN SMALL LETTER I WITH DIAERESIS]*/
	{"jcirc",                 "\xc4\xb5"                }, /* ĵ [LATIN SMALL LETTER J WITH CIRCUMFLEX]*/
	{"jcy",                   "\xd0\xb9"                }, /* й [CYRILLIC SMALL LETTER SHORT I]*/
	{"jfr",                   "\xf0\x9d\x94\xa7"        }, /* 𝔧 [MATHEMATICAL FRAKTUR SMALL J]*/
	{"jmath",                 "\x6a"                    }, /* j [LATIN SMALL LETTER J]*/
	{"jopf",                  "\xf0\x9d\x95\x9b"        }, /* 𝕛 [MATHEMATICAL DOUBLE-STRUCK SMALL J]*/
	{"jscr",                  "\xf0\x9d\x92\xbf"        }, /* 𝒿 [MATHEMATICAL SCRIPT SMALL J]*/
	{"jsercy",                "\xd1\x98"                }, /* ј [CYRILLIC SMALL LETTER JE]*/
	{"jukcy",                 "\xd1\x94"                }, /* є [CYRILLIC SMALL LETTER UKRAINIAN IE]*/
	{"kappa",                 "\xce\xba"                }, /* κ [GREEK SMALL LETTER KAPPA]*/
	{"kappav",                "\xcf\xb0"                }, /* ϰ [GREEK KAPPA SYMBOL]*/
	{"kcedil",                "\xc4\xb7"                }, /* ķ [LATIN SMALL LETTER K WITH CEDILLA]*/
	{"kcy",                   "\xd0\xba"                }, /* к [CYRILLIC SMALL LETTER KA]*/
	{"kfr",                   "\xf0\x9d\x94\xa8"        }, /* 𝔨 [MATHEMATICAL FRAKTUR SMALL K]*/
	{"kgreen",                "\xc4\xb8"                }, /* ĸ [LATIN SMALL LETTER KRA]*/
	{"khcy",                  "\xd1\x85"                }, /* х [CYRILLIC SMALL LETTER HA]*/
	{"kjcy",                  "\xd1\x9c"                }, /* ќ [CYRILLIC SMALL LETTER KJE]*/
	{"kopf",                  "\xf0\x9d\x95\x9c"        }, /* 𝕜 [MATHEMATICAL DOUBLE-STRUCK SMALL K]*/
	{"kscr",                  "\xf0\x9d\x93\x80"        }, /* 𝓀 [MATHEMATICAL SCRIPT SMALL K]*/
	{"lAarr",                 "\xe2\x87\x9a"            }, /* ⇚ [LEFTWARDS TRIPLE ARROW]*/
	{"lArr",                  "\xe2\x87\x90"            }, /* ⇐ [LEFTWARDS DOUBLE ARROW]*/
	{"lAtail",                "\xe2\xa4\x9b"            }, /* ⤛ [LEFTWARDS DOUBLE ARROW-TAIL]*/
	{"lBarr",                 "\xe2\xa4\x8e"            }, /* ⤎ [LEFTWARDS TRIPLE DASH ARROW]*/
	{"lE",                    "\xe2\x89\xa6"            }, /* ≦ [LESS-THAN OVER EQUAL TO]*/
	{"lEg",                   "\xe2\xaa\x8b"            }, /* ⪋ [LESS-THAN ABOVE DOUBLE-LINE EQUAL ABOVE GREATER-THAN]*/
	{"lHar",                  "\xe2\xa5\xa2"            }, /* ⥢ [LEFTWARDS HARPOON WITH BARB UP ABOVE LEFTWARDS HARPOON WITH BARB DOWN]*/
	{"lacute",                "\xc4\xba"                }, /* ĺ [LATIN SMALL LETTER L WITH ACUTE]*/
	{"laemptyv",              "\xe2\xa6\xb4"            }, /* ⦴ [EMPTY SET WITH LEFT ARROW ABOVE]*/
	{"lagran",                "\xe2\x84\x92"            }, /* ℒ [SCRIPT CAPITAL L]*/
	{"lambda",                "\xce\xbb"                }, /* λ [GREEK SMALL LETTER LAMDA]*/
	{"lang",                  "\xe2\x8c\xa9"            }, /* 〈 [LEFT-POINTING ANGLE BRACKET]*/
	{"langd",                 "\xe2\xa6\x91"            }, /* ⦑ [LEFT ANGLE BRACKET WITH DOT]*/
	{"langle",                "\xe2\x8c\xa9"            }, /* 〈 [LEFT-POINTING ANGLE BRACKET]*/
	{"lap",                   "\xe2\xaa\x85"            }, /* ⪅ [LESS-THAN OR APPROXIMATE]*/
	{"laquo",                 "\xc2\xab"                }, /* « [LEFT-POINTING DOUBLE ANGLE QUOTATION MARK]*/
	{"larr",                  "\xe2\x86\x90"            }, /* ← [LEFTWARDS ARROW]*/
	{"larrb",                 "\xe2\x87\xa4"            }, /* ⇤ [LEFTWARDS ARROW TO BAR]*/
	{"larrbfs",               "\xe2\xa4\x9f"            }, /* ⤟ [LEFTWARDS ARROW FROM BAR TO BLACK DIAMOND]*/
	{"larrfs",                "\xe2\xa4\x9d"            }, /* ⤝ [LEFTWARDS ARROW TO BLACK DIAMOND]*/
	{"larrhk",                "\xe2\x86\xa9"            }, /* ↩ [LEFTWARDS ARROW WITH HOOK]*/
	{"larrlp",                "\xe2\x86\xab"            }, /* ↫ [LEFTWARDS ARROW WITH LOOP]*/
	{"larrpl",                "\xe2\xa4\xb9"            }, /* ⤹ [LEFT-SIDE ARC ANTICLOCKWISE ARROW]*/
	{"larrsim",               "\xe2\xa5\xb3"            }, /* ⥳ [LEFTWARDS ARROW ABOVE TILDE OPERATOR]*/
	{"larrtl",                "\xe2\x86\xa2"            }, /* ↢ [LEFTWARDS ARROW WITH TAIL]*/
	{"lat",                   "\xe2\xaa\xab"            }, /* ⪫ [LARGER THAN]*/
	{"latail",                "\xe2\xa4\x99"            }, /* ⤙ [LEFTWARDS ARROW-TAIL]*/
	{"late",                  "\xe2\xaa\xad"            }, /* ⪭ [LARGER THAN OR EQUAL TO]*/
	{"lates",                 "\xe2\xaa\xad\xef\xb8\x80"}, /* ⪭︀ [LARGER THAN OR slanted EQUAL]*/
	{"lbarr",                 "\xe2\xa4\x8c"            }, /* ⤌ [LEFTWARDS DOUBLE DASH ARROW]*/
	{"lbbrk",                 "\xe3\x80\x94"            }, /* 〔 [LEFT TORTOISE SHELL BRACKET]*/
	{"lbrace",                "\x7b"                    }, /* { [LEFT CURLY BRACKET]*/
	{"lbrack",                "\x5b"                    }, /* [ [LEFT SQUARE BRACKET]*/
	{"lbrke",                 "\xe2\xa6\x8b"            }, /* ⦋ [LEFT SQUARE BRACKET WITH UNDERBAR]*/
	{"lbrksld",               "\xe2\xa6\x8f"            }, /* ⦏ [LEFT SQUARE BRACKET WITH TICK IN BOTTOM CORNER]*/
	{"lbrkslu",               "\xe2\xa6\x8d"            }, /* ⦍ [LEFT SQUARE BRACKET WITH TICK IN TOP CORNER]*/
	{"lcaron",                "\xc4\xbe"                }, /* ľ [LATIN SMALL LETTER L WITH CARON]*/
	{"lcedil",                "\xc4\xbc"                }, /* ļ [LATIN SMALL LETTER L WITH CEDILLA]*/
	{"lceil",                 "\xe2\x8c\x88"            }, /* ⌈ [LEFT CEILING]*/
	{"lcub",                  "\x7b"                    }, /* { [LEFT CURLY BRACKET]*/
	{"lcy",                   "\xd0\xbb"                }, /* л [CYRILLIC SMALL LETTER EL]*/
	{"ldca",                  "\xe2\xa4\xb6"            }, /* ⤶ [ARROW POINTING DOWNWARDS THEN CURVING LEFTWARDS]*/
	{"ldquo",                 "\xe2\x80\x9c"            }, /* “ [LEFT DOUBLE QUOTATION MARK]*/
	{"ldquor",                "\xe2\x80\x9e"            }, /* „ [DOUBLE LOW-9 QUOTATION MARK]*/
	{"ldrdhar",               "\xe2\xa5\xa7"            }, /* ⥧ [LEFTWARDS HARPOON WITH BARB DOWN ABOVE RIGHTWARDS HARPOON WITH BARB DOWN]*/
	{"ldrushar",              "\xe2\xa5\x8b"            }, /* ⥋ [LEFT BARB DOWN RIGHT BARB UP HARPOON]*/
	{"ldsh",                  "\xe2\x86\xb2"            }, /* ↲ [DOWNWARDS ARROW WITH TIP LEFTWARDS]*/
	{"le",                    "\xe2\x89\xa4"            }, /* ≤ [LESS-THAN OR EQUAL TO]*/
	{"leftarrow",             "\xe2\x86\x90"            }, /* ← [LEFTWARDS ARROW]*/
	{"leftarrowtail",         "\xe2\x86\xa2"            }, /* ↢ [LEFTWARDS ARROW WITH TAIL]*/
	{"leftharpoondown",       "\xe2\x86\xbd"            }, /* ↽ [LEFTWARDS HARPOON WITH BARB DOWNWARDS]*/
	{"leftharpoonup",         "\xe2\x86\xbc"            }, /* ↼ [LEFTWARDS HARPOON WITH BARB UPWARDS]*/
	{"leftleftarrows",        "\xe2\x87\x87"            }, /* ⇇ [LEFTWARDS PAIRED ARROWS]*/
	{"leftrightarrow",        "\xe2\x86\x94"            }, /* ↔ [LEFT RIGHT ARROW]*/
	{"leftrightarrows",       "\xe2\x87\x86"            }, /* ⇆ [LEFTWARDS ARROW OVER RIGHTWARDS ARROW]*/
	{"leftrightharpoons",     "\xe2\x87\x8b"            }, /* ⇋ [LEFTWARDS HARPOON OVER RIGHTWARDS HARPOON]*/
	{"leftrightsquigarrow",   "\xe2\x86\xad"            }, /* ↭ [LEFT RIGHT WAVE ARROW]*/
	{"leftthreetimes",        "\xe2\x8b\x8b"            }, /* ⋋ [LEFT SEMIDIRECT PRODUCT]*/
	{"leg",                   "\xe2\x8b\x9a"            }, /* ⋚ [LESS-THAN EQUAL TO OR GREATER-THAN]*/
	{"leq",                   "\xe2\x89\xa4"            }, /* ≤ [LESS-THAN OR EQUAL TO]*/
	{"leqq",                  "\xe2\x89\xa6"            }, /* ≦ [LESS-THAN OVER EQUAL TO]*/
	{"leqslant",              "\xe2\xa9\xbd"            }, /* ⩽ [LESS-THAN OR SLANTED EQUAL TO]*/
	{"les",                   "\xe2\xa9\xbd"            }, /* ⩽ [LESS-THAN OR SLANTED EQUAL TO]*/
	{"lescc",                 "\xe2\xaa\xa8"            }, /* ⪨ [LESS-THAN CLOSED BY CURVE ABOVE SLANTED EQUAL]*/
	{"lesdot",                "\xe2\xa9\xbf"            }, /* ⩿ [LESS-THAN OR SLANTED EQUAL TO WITH DOT INSIDE]*/
	{"lesdoto",               "\xe2\xaa\x81"            }, /* ⪁ [LESS-THAN OR SLANTED EQUAL TO WITH DOT ABOVE]*/
	{"lesdotor",              "\xe2\xaa\x83"            }, /* ⪃ [LESS-THAN OR SLANTED EQUAL TO WITH DOT ABOVE RIGHT]*/
	{"lesg",                  "\xe2\x8b\x9a\xef\xb8\x80"}, /* ⋚︀ [LESS-THAN slanted EQUAL TO OR GREATER-THAN]*/
	{"lesges",                "\xe2\xaa\x93"            }, /* ⪓ [LESS-THAN ABOVE SLANTED EQUAL ABOVE GREATER-THAN ABOVE SLANTED EQUAL]*/
	{"lessapprox",            "\xe2\xaa\x85"            }, /* ⪅ [LESS-THAN OR APPROXIMATE]*/
	{"lessdot",               "\xe2\x8b\x96"            }, /* ⋖ [LESS-THAN WITH DOT]*/
	{"lesseqgtr",             "\xe2\x8b\x9a"            }, /* ⋚ [LESS-THAN EQUAL TO OR GREATER-THAN]*/
	{"lesseqqgtr",            "\xe2\xaa\x8b"            }, /* ⪋ [LESS-THAN ABOVE DOUBLE-LINE EQUAL ABOVE GREATER-THAN]*/
	{"lessgtr",               "\xe2\x89\xb6"            }, /* ≶ [LESS-THAN OR GREATER-THAN]*/
	{"lesssim",               "\xe2\x89\xb2"            }, /* ≲ [LESS-THAN OR EQUIVALENT TO]*/
	{"lfisht",                "\xe2\xa5\xbc"            }, /* ⥼ [LEFT FISH TAIL]*/
	{"lfloor",                "\xe2\x8c\x8a"            }, /* ⌊ [LEFT FLOOR]*/
	{"lfr",                   "\xf0\x9d\x94\xa9"        }, /* 𝔩 [MATHEMATICAL FRAKTUR SMALL L]*/
	{"lg",                    "\xe2\x89\xb6"            }, /* ≶ [LESS-THAN OR GREATER-THAN]*/
	{"lgE",                   "\xe2\xaa\x91"            }, /* ⪑ [LESS-THAN ABOVE GREATER-THAN ABOVE DOUBLE-LINE EQUAL]*/
	{"lhard",                 "\xe2\x86\xbd"            }, /* ↽ [LEFTWARDS HARPOON WITH BARB DOWNWARDS]*/
	{"lharu",                 "\xe2\x86\xbc"            }, /* ↼ [LEFTWARDS HARPOON WITH BARB UPWARDS]*/
	{"lharul",                "\xe2\xa5\xaa"            }, /* ⥪ [LEFTWARDS HARPOON WITH BARB UP ABOVE LONG DASH]*/
	{"lhblk",                 "\xe2\x96\x84"            }, /* ▄ [LOWER HALF BLOCK]*/
	{"ljcy",                  "\xd1\x99"                }, /* љ [CYRILLIC SMALL LETTER LJE]*/
	{"ll",                    "\xe2\x89\xaa"            }, /* ≪ [MUCH LESS-THAN]*/
	{"llarr",                 "\xe2\x87\x87"            }, /* ⇇ [LEFTWARDS PAIRED ARROWS]*/
	{"llcorner",              "\xe2\x8c\x9e"            }, /* ⌞ [BOTTOM LEFT CORNER]*/
	{"llhard",                "\xe2\xa5\xab"            }, /* ⥫ [LEFTWARDS HARPOON WITH BARB DOWN BELOW LONG DASH]*/
	{"lltri",                 "\xe2\x97\xba"            }, /* ◺ [LOWER LEFT TRIANGLE]*/
	{"lmidot",                "\xc5\x80"                }, /* ŀ [LATIN SMALL LETTER L WITH MIDDLE DOT]*/
	{"lmoust",                "\xe2\x8e\xb0"            }, /* ⎰ [UPPER LEFT OR LOWER RIGHT CURLY BRACKET SECTION]*/
	{"lmoustache",            "\xe2\x8e\xb0"            }, /* ⎰ [UPPER LEFT OR LOWER RIGHT CURLY BRACKET SECTION]*/
	{"lnE",                   "\xe2\x89\xa8"            }, /* ≨ [LESS-THAN BUT NOT EQUAL TO]*/
	{"lnap",                  "\xe2\xaa\x89"            }, /* ⪉ [LESS-THAN AND NOT APPROXIMATE]*/
	{"lnapprox",              "\xe2\xaa\x89"            }, /* ⪉ [LESS-THAN AND NOT APPROXIMATE]*/
	{"lne",                   "\xe2\xaa\x87"            }, /* ⪇ [LESS-THAN AND SINGLE-LINE NOT EQUAL TO]*/
	{"lneq",                  "\xe2\xaa\x87"            }, /* ⪇ [LESS-THAN AND SINGLE-LINE NOT EQUAL TO]*/
	{"lneqq",                 "\xe2\x89\xa8"            }, /* ≨ [LESS-THAN BUT NOT EQUAL TO]*/
	{"lnsim",                 "\xe2\x8b\xa6"            }, /* ⋦ [LESS-THAN BUT NOT EQUIVALENT TO]*/
	{"loang",                 "\xe3\x80\x98"            }, /* 〘 [LEFT WHITE TORTOISE SHELL BRACKET]*/
	{"loarr",                 "\xe2\x87\xbd"            }, /* ⇽ [LEFTWARDS OPEN-HEADED ARROW]*/
	{"lobrk",                 "\xe3\x80\x9a"            }, /* 〚 [LEFT WHITE SQUARE BRACKET]*/
	{"longleftarrow",         "\xe2\x9f\xb5"            }, /* ⟵ [LONG LEFTWARDS ARROW]*/
	{"longleftrightarrow",    "\xe2\x9f\xb7"            }, /* ⟷ [LONG LEFT RIGHT ARROW]*/
	{"longmapsto",            "\xe2\x9f\xbc"            }, /* ⟼ [LONG RIGHTWARDS ARROW FROM BAR]*/
	{"longrightarrow",        "\xe2\x9f\xb6"            }, /* ⟶ [LONG RIGHTWARDS ARROW]*/
	{"looparrowleft",         "\xe2\x86\xab"            }, /* ↫ [LEFTWARDS ARROW WITH LOOP]*/
	{"looparrowright",        "\xe2\x86\xac"            }, /* ↬ [RIGHTWARDS ARROW WITH LOOP]*/
	{"lopar",                 "\xe2\xa6\x85"            }, /* ⦅ [LEFT WHITE PARENTHESIS]*/
	{"lopf",                  "\xf0\x9d\x95\x9d"        }, /* 𝕝 [MATHEMATICAL DOUBLE-STRUCK SMALL L]*/
	{"loplus",                "\xe2\xa8\xad"            }, /* ⨭ [PLUS SIGN IN LEFT HALF CIRCLE]*/
	{"lotimes",               "\xe2\xa8\xb4"            }, /* ⨴ [MULTIPLICATION SIGN IN LEFT HALF CIRCLE]*/
	{"lowast",                "\xe2\x88\x97"            }, /* ∗ [ASTERISK OPERATOR]*/
	{"lowbar",                "\x5f"                    }, /* _ [LOW LINE]*/
	{"loz",                   "\xe2\x97\x8a"            }, /* ◊ [LOZENGE]*/
	{"lozenge",               "\xe2\x97\x8a"            }, /* ◊ [LOZENGE]*/
	{"lozf",                  "\xe2\xa7\xab"            }, /* ⧫ [BLACK LOZENGE]*/
	{"lpar",                  "\x28"                    }, /* ( [LEFT PARENTHESIS]*/
	{"lparlt",                "\xe2\xa6\x93"            }, /* ⦓ [LEFT ARC LESS-THAN BRACKET]*/
	{"lrarr",                 "\xe2\x87\x86"            }, /* ⇆ [LEFTWARDS ARROW OVER RIGHTWARDS ARROW]*/
	{"lrcorner",              "\xe2\x8c\x9f"            }, /* ⌟ [BOTTOM RIGHT CORNER]*/
	{"lrhar",                 "\xe2\x87\x8b"            }, /* ⇋ [LEFTWARDS HARPOON OVER RIGHTWARDS HARPOON]*/
	{"lrhard",                "\xe2\xa5\xad"            }, /* ⥭ [RIGHTWARDS HARPOON WITH BARB DOWN BELOW LONG DASH]*/
	{"lrtri",                 "\xe2\x8a\xbf"            }, /* ⊿ [RIGHT TRIANGLE]*/
	{"lscr",                  "\xf0\x9d\x93\x81"        }, /* 𝓁 [MATHEMATICAL SCRIPT SMALL L]*/
	{"lsh",                   "\xe2\x86\xb0"            }, /* ↰ [UPWARDS ARROW WITH TIP LEFTWARDS]*/
	{"lsim",                  "\xe2\x89\xb2"            }, /* ≲ [LESS-THAN OR EQUIVALENT TO]*/
	{"lsime",                 "\xe2\xaa\x8d"            }, /* ⪍ [LESS-THAN ABOVE SIMILAR OR EQUAL]*/
	{"lsimg",                 "\xe2\xaa\x8f"            }, /* ⪏ [LESS-THAN ABOVE SIMILAR ABOVE GREATER-THAN]*/
	{"lsqb",                  "\x5b"                    }, /* [ [LEFT SQUARE BRACKET]*/
	{"lsquo",                 "\xe2\x80\x98"            }, /* ‘ [LEFT SINGLE QUOTATION MARK]*/
	{"lsquor",                "\xe2\x80\x9a"            }, /* ‚ [SINGLE LOW-9 QUOTATION MARK]*/
	{"lstrok",                "\xc5\x82"                }, /* ł [LATIN SMALL LETTER L WITH STROKE]*/
	{"lt",                    "\x3c"                    }, /* < [LESS-THAN SIGN]*/
	{"ltcc",                  "\xe2\xaa\xa6"            }, /* ⪦ [LESS-THAN CLOSED BY CURVE]*/
	{"ltcir",                 "\xe2\xa9\xb9"            }, /* ⩹ [LESS-THAN WITH CIRCLE INSIDE]*/
	{"ltdot",                 "\xe2\x8b\x96"            }, /* ⋖ [LESS-THAN WITH DOT]*/
	{"lthree",                "\xe2\x8b\x8b"            }, /* ⋋ [LEFT SEMIDIRECT PRODUCT]*/
	{"ltimes",                "\xe2\x8b\x89"            }, /* ⋉ [LEFT NORMAL FACTOR SEMIDIRECT PRODUCT]*/
	{"ltlarr",                "\xe2\xa5\xb6"            }, /* ⥶ [LESS-THAN ABOVE LEFTWARDS ARROW]*/
	{"ltquest",               "\xe2\xa9\xbb"            }, /* ⩻ [LESS-THAN WITH QUESTION MARK ABOVE]*/
	{"ltrPar",                "\xe2\xa6\x96"            }, /* ⦖ [DOUBLE RIGHT ARC LESS-THAN BRACKET]*/
	{"ltri",                  "\xe2\x97\x83"            }, /* ◃ [WHITE LEFT-POINTING SMALL TRIANGLE]*/
	{"ltrie",                 "\xe2\x8a\xb4"            }, /* ⊴ [NORMAL SUBGROUP OF OR EQUAL TO]*/
	{"ltrif",                 "\xe2\x97\x82"            }, /* ◂ [BLACK LEFT-POINTING SMALL TRIANGLE]*/
	{"lurdshar",              "\xe2\xa5\x8a"            }, /* ⥊ [LEFT BARB UP RIGHT BARB DOWN HARPOON]*/
	{"luruhar",               "\xe2\xa5\xa6"            }, /* ⥦ [LEFTWARDS HARPOON WITH BARB UP ABOVE RIGHTWARDS HARPOON WITH BARB UP]*/
	{"lvertneqq",             "\xe2\x89\xa8\xef\xb8\x80"}, /* ≨︀ [LESS-THAN BUT NOT EQUAL TO - with vertical stroke]*/
	{"lvnE",                  "\xe2\x89\xa8\xef\xb8\x80"}, /* ≨︀ [LESS-THAN BUT NOT EQUAL TO - with vertical stroke]*/
	{"mDDot",                 "\xe2\x88\xba"            }, /* ∺ [GEOMETRIC PROPORTION]*/
	{"macr",                  "\xc2\xaf"                }, /* ¯ [MACRON]*/
	{"male",                  "\xe2\x99\x82"            }, /* ♂ [MALE SIGN]*/
	{"malt",                  "\xe2\x9c\xa0"            }, /* ✠ [MALTESE CROSS]*/
	{"maltese",               "\xe2\x9c\xa0"            }, /* ✠ [MALTESE CROSS]*/
	{"map",                   "\xe2\x86\xa6"            }, /* ↦ [RIGHTWARDS ARROW FROM BAR]*/
	{"mapsto",                "\xe2\x86\xa6"            }, /* ↦ [RIGHTWARDS ARROW FROM BAR]*/
	{"mapstodown",            "\xe2\x86\xa7"            }, /* ↧ [DOWNWARDS ARROW FROM BAR]*/
	{"mapstoleft",            "\xe2\x86\xa4"            }, /* ↤ [LEFTWARDS ARROW FROM BAR]*/
	{"mapstoup",              "\xe2\x86\xa5"            }, /* ↥ [UPWARDS ARROW FROM BAR]*/
	{"marker",                "\xe2\x96\xae"            }, /* ▮ [BLACK VERTICAL RECTANGLE]*/
	{"mcomma",                "\xe2\xa8\xa9"            }, /* ⨩ [MINUS SIGN WITH COMMA ABOVE]*/
	{"mcy",                   "\xd0\xbc"                }, /* м [CYRILLIC SMALL LETTER EM]*/
	{"mdash",                 "\xe2\x80\x94"            }, /* — [EM DASH]*/
	{"measuredangle",         "\xe2\x88\xa1"            }, /* ∡ [MEASURED ANGLE]*/
	{"mfr",                   "\xf0\x9d\x94\xaa"        }, /* 𝔪 [MATHEMATICAL FRAKTUR SMALL M]*/
	{"mho",                   "\xe2\x84\xa7"            }, /* ℧ [INVERTED OHM SIGN]*/
	{"micro",                 "\xc2\xb5"                }, /* µ [MICRO SIGN]*/
	{"mid",                   "\xe2\x88\xa3"            }, /* ∣ [DIVIDES]*/
	{"midast",                "\x2a"                    }, /* * [ASTERISK]*/
	{"midcir",                "\xe2\xab\xb0"            }, /* ⫰ [VERTICAL LINE WITH CIRCLE BELOW]*/
	{"middot",                "\xc2\xb7"                }, /* · [MIDDLE DOT]*/
	{"minus",                 "\xe2\x88\x92"            }, /* − [MINUS SIGN]*/
	{"minusb",                "\xe2\x8a\x9f"            }, /* ⊟ [SQUARED MINUS]*/
	{"minusd",                "\xe2\x88\xb8"            }, /* ∸ [DOT MINUS]*/
	{"minusdu",               "\xe2\xa8\xaa"            }, /* ⨪ [MINUS SIGN WITH DOT BELOW]*/
	{"mlcp",                  "\xe2\xab\x9b"            }, /* ⫛ [TRANSVERSAL INTERSECTION]*/
	{"mldr",                  "\xe2\x80\xa6"            }, /* … [HORIZONTAL ELLIPSIS]*/
	{"mnplus",                "\xe2\x88\x93"            }, /* ∓ [MINUS-OR-PLUS SIGN]*/
	{"models",                "\xe2\x8a\xa7"            }, /* ⊧ [MODELS]*/
	{"mopf",                  "\xf0\x9d\x95\x9e"        }, /* 𝕞 [MATHEMATICAL DOUBLE-STRUCK SMALL M]*/
	{"mp",                    "\xe2\x88\x93"            }, /* ∓ [MINUS-OR-PLUS SIGN]*/
	{"mscr",                  "\xf0\x9d\x93\x82"        }, /* 𝓂 [MATHEMATICAL SCRIPT SMALL M]*/
	{"mstpos",                "\xe2\x88\xbe"            }, /* ∾ [INVERTED LAZY S]*/
	{"mu",                    "\xce\xbc"                }, /* μ [GREEK SMALL LETTER MU]*/
	{"multimap",              "\xe2\x8a\xb8"            }, /* ⊸ [MULTIMAP]*/
	{"mumap",                 "\xe2\x8a\xb8"            }, /* ⊸ [MULTIMAP]*/
	{"nGg",                   "\xe2\x8b\x99\xcc\xb8"    }, /* ⋙̸ [VERY MUCH GREATER-THAN with slash]*/
	{"nGt",                   "\xe2\x89\xab\xe2\x83\x92"}, /* ≫⃒ [MUCH GREATER THAN with vertical line]*/
	{"nGtv",                  "\xe2\x89\xab\xcc\xb8"    }, /* ≫̸ [MUCH GREATER THAN with slash]*/
	{"nLeftarrow",            "\xe2\x87\x8d"            }, /* ⇍ [LEFTWARDS DOUBLE ARROW WITH STROKE]*/
	{"nLeftrightarrow",       "\xe2\x87\x8e"            }, /* ⇎ [LEFT RIGHT DOUBLE ARROW WITH STROKE]*/
	{"nLl",                   "\xe2\x8b\x98\xcc\xb8"    }, /* ⋘̸ [VERY MUCH LESS-THAN with slash]*/
	{"nLt",                   "\xe2\x89\xaa\xe2\x83\x92"}, /* ≪⃒ [MUCH LESS THAN with vertical line]*/
	{"nLtv",                  "\xe2\x89\xaa\xcc\xb8"    }, /* ≪̸ [MUCH LESS THAN with slash]*/
	{"nRightarrow",           "\xe2\x87\x8f"            }, /* ⇏ [RIGHTWARDS DOUBLE ARROW WITH STROKE]*/
	{"nVDash",                "\xe2\x8a\xaf"            }, /* ⊯ [NEGATED DOUBLE VERTICAL BAR DOUBLE RIGHT TURNSTILE]*/
	{"nVdash",                "\xe2\x8a\xae"            }, /* ⊮ [DOES NOT FORCE]*/
	{"nabla",                 "\xe2\x88\x87"            }, /* ∇ [NABLA]*/
	{"nacute",                "\xc5\x84"                }, /* ń [LATIN SMALL LETTER N WITH ACUTE]*/
	{"nang",                  "\xe2\x88\xa0\xe2\x83\x92"}, /* ∠⃒ [ANGLE with vertical line]*/
	{"nap",                   "\xe2\x89\x89"            }, /* ≉ [NOT ALMOST EQUAL TO]*/
	{"napE",                  "\xe2\xa9\xb0\xcc\xb8"    }, /* ⩰̸ [APPROXIMATELY EQUAL OR EQUAL TO with slash]*/
	{"napid",                 "\xe2\x89\x8b\xcc\xb8"    }, /* ≋̸ [TRIPLE TILDE with slash]*/
	{"napos",                 "\xc5\x89"                }, /* ŉ [LATIN SMALL LETTER N PRECEDED BY APOSTROPHE]*/
	{"napprox",               "\xe2\x89\x89"            }, /* ≉ [NOT ALMOST EQUAL TO]*/
	{"natur",                 "\xe2\x99\xae"            }, /* ♮ [MUSIC NATURAL SIGN]*/
	{"natural",               "\xe2\x99\xae"            }, /* ♮ [MUSIC NATURAL SIGN]*/
	{"naturals",              "\xe2\x84\x95"            }, /* ℕ [DOUBLE-STRUCK CAPITAL N]*/
	{"nbsp",                  "\xc2\xa0"                }, /*   [NO-BREAK SPACE]*/
	{"nbump",                 "\xe2\x89\x8e\xcc\xb8"    }, /* ≎̸ [GEOMETRICALLY EQUIVALENT TO with slash]*/
	{"nbumpe",                "\xe2\x89\x8f\xcc\xb8"    }, /* ≏̸ [DIFFERENCE BETWEEN with slash]*/
	{"ncap",                  "\xe2\xa9\x83"            }, /* ⩃ [INTERSECTION WITH OVERBAR]*/
	{"ncaron",                "\xc5\x88"                }, /* ň [LATIN SMALL LETTER N WITH CARON]*/
	{"ncedil",                "\xc5\x86"                }, /* ņ [LATIN SMALL LETTER N WITH CEDILLA]*/
	{"ncong",                 "\xe2\x89\x87"            }, /* ≇ [NEITHER APPROXIMATELY NOR ACTUALLY EQUAL TO]*/
	{"ncongdot",              "\xe2\xa9\xad\xcc\xb8"    }, /* ⩭̸ [CONGRUENT WITH DOT ABOVE with slash]*/
	{"ncup",                  "\xe2\xa9\x82"            }, /* ⩂ [UNION WITH OVERBAR]*/
	{"ncy",                   "\xd0\xbd"                }, /* н [CYRILLIC SMALL LETTER EN]*/
	{"ndash",                 "\xe2\x80\x93"            }, /* – [EN DASH]*/
	{"ne",                    "\xe2\x89\xa0"            }, /* ≠ [NOT EQUAL TO]*/
	{"neArr",                 "\xe2\x87\x97"            }, /* ⇗ [NORTH EAST DOUBLE ARROW]*/
	{"nearhk",                "\xe2\xa4\xa4"            }, /* ⤤ [NORTH EAST ARROW WITH HOOK]*/
	{"nearr",                 "\xe2\x86\x97"            }, /* ↗ [NORTH EAST ARROW]*/
	{"nearrow",               "\xe2\x86\x97"            }, /* ↗ [NORTH EAST ARROW]*/
	{"nedot",                 "\xe2\x89\x90\xcc\xb8"    }, /* ≐̸ [APPROACHES THE LIMIT with slash]*/
	{"nequiv",                "\xe2\x89\xa2"            }, /* ≢ [NOT IDENTICAL TO]*/
	{"nesear",                "\xe2\xa4\xa8"            }, /* ⤨ [NORTH EAST ARROW AND SOUTH EAST ARROW]*/
	{"nesim",                 "\xe2\x89\x82\xcc\xb8"    }, /* ≂̸ [MINUS TILDE with slash]*/
	{"nexist",                "\xe2\x88\x84"            }, /* ∄ [THERE DOES NOT EXIST]*/
	{"nexists",               "\xe2\x88\x84"            }, /* ∄ [THERE DOES NOT EXIST]*/
	{"nfr",                   "\xf0\x9d\x94\xab"        }, /* 𝔫 [MATHEMATICAL FRAKTUR SMALL N]*/
	{"ngE",                   "\xe2\x89\xa7\xcc\xb8"    }, /* ≧̸ [GREATER-THAN OVER EQUAL TO with slash]*/
	{"nge",                   "\xe2\x89\xb1"            }, /* ≱ [NEITHER GREATER-THAN NOR EQUAL TO]*/
	{"ngeq",                  "\xe2\x89\xb1"            }, /* ≱ [NEITHER GREATER-THAN NOR EQUAL TO]*/
	{"ngeqq",                 "\xe2\x89\xa7\xcc\xb8"    }, /* ≧̸ [GREATER-THAN OVER EQUAL TO with slash]*/
	{"ngeqslant",             "\xe2\xa9\xbe\xcc\xb8"    }, /* ⩾̸ [GREATER-THAN OR SLANTED EQUAL TO with slash]*/
	{"nges",                  "\xe2\xa9\xbe\xcc\xb8"    }, /* ⩾̸ [GREATER-THAN OR SLANTED EQUAL TO with slash]*/
	{"ngsim",                 "\xe2\x89\xb5"            }, /* ≵ [NEITHER GREATER-THAN NOR EQUIVALENT TO]*/
	{"ngt",                   "\xe2\x89\xaf"            }, /* ≯ [NOT GREATER-THAN]*/
	{"ngtr",                  "\xe2\x89\xaf"            }, /* ≯ [NOT GREATER-THAN]*/
	{"nhArr",                 "\xe2\x87\x8e"            }, /* ⇎ [LEFT RIGHT DOUBLE ARROW WITH STROKE]*/
	{"nharr",                 "\xe2\x86\xae"            }, /* ↮ [LEFT RIGHT ARROW WITH STROKE]*/
	{"nhpar",                 "\xe2\xab\xb2"            }, /* ⫲ [PARALLEL WITH HORIZONTAL STROKE]*/
	{"ni",                    "\xe2\x88\x8b"            }, /* ∋ [CONTAINS AS MEMBER]*/
	{"nis",                   "\xe2\x8b\xbc"            }, /* ⋼ [SMALL CONTAINS WITH VERTICAL BAR AT END OF HORIZONTAL STROKE]*/
	{"nisd",                  "\xe2\x8b\xba"            }, /* ⋺ [CONTAINS WITH LONG HORIZONTAL STROKE]*/
	{"niv",                   "\xe2\x88\x8b"            }, /* ∋ [CONTAINS AS MEMBER]*/
	{"njcy",                  "\xd1\x9a"                }, /* њ [CYRILLIC SMALL LETTER NJE]*/
	{"nlArr",                 "\xe2\x87\x8d"            }, /* ⇍ [LEFTWARDS DOUBLE ARROW WITH STROKE]*/
	{"nlE",                   "\xe2\x89\xa6\xcc\xb8"    }, /* ≦̸ [LESS-THAN OVER EQUAL TO with slash]*/
	{"nlarr",                 "\xe2\x86\x9a"            }, /* ↚ [LEFTWARDS ARROW WITH STROKE]*/
	{"nldr",                  "\xe2\x80\xa5"            }, /* ‥ [TWO DOT LEADER]*/
	{"nle",                   "\xe2\x89\xb0"            }, /* ≰ [NEITHER LESS-THAN NOR EQUAL TO]*/
	{"nleftarrow",            "\xe2\x86\x9a"            }, /* ↚ [LEFTWARDS ARROW WITH STROKE]*/
	{"nleftrightarrow",       "\xe2\x86\xae"            }, /* ↮ [LEFT RIGHT ARROW WITH STROKE]*/
	{"nleq",                  "\xe2\x89\xb0"            }, /* ≰ [NEITHER LESS-THAN NOR EQUAL TO]*/
	{"nleqq",                 "\xe2\x89\xa6\xcc\xb8"    }, /* ≦̸ [LESS-THAN OVER EQUAL TO with slash]*/
	{"nleqslant",             "\xe2\xa9\xbd\xcc\xb8"    }, /* ⩽̸ [LESS-THAN OR SLANTED EQUAL TO with slash]*/
	{"nles",                  "\xe2\xa9\xbd\xcc\xb8"    }, /* ⩽̸ [LESS-THAN OR SLANTED EQUAL TO with slash]*/
	{"nless",                 "\xe2\x89\xae"            }, /* ≮ [NOT LESS-THAN]*/
	{"nlsim",                 "\xe2\x89\xb4"            }, /* ≴ [NEITHER LESS-THAN NOR EQUIVALENT TO]*/
	{"nlt",                   "\xe2\x89\xae"            }, /* ≮ [NOT LESS-THAN]*/
	{"nltri",                 "\xe2\x8b\xaa"            }, /* ⋪ [NOT NORMAL SUBGROUP OF]*/
	{"nltrie",                "\xe2\x8b\xac"            }, /* ⋬ [NOT NORMAL SUBGROUP OF OR EQUAL TO]*/
	{"nmid",                  "\xe2\x88\xa4"            }, /* ∤ [DOES NOT DIVIDE]*/
	{"nopf",                  "\xf0\x9d\x95\x9f"        }, /* 𝕟 [MATHEMATICAL DOUBLE-STRUCK SMALL N]*/
	{"not",                   "\xc2\xac"                }, /* ¬ [NOT SIGN]*/
	{"notin",                 "\xe2\x88\x89"            }, /* ∉ [NOT AN ELEMENT OF]*/
	{"notinE",                "\xe2\x8b\xb9\xcc\xb8"    }, /* ⋹̸ [ELEMENT OF WITH TWO HORIZONTAL STROKES with slash]*/
	{"notindot",              "\xe2\x8b\xb5\xcc\xb8"    }, /* ⋵̸ [ELEMENT OF WITH DOT ABOVE with slash]*/
	{"notinva",               "\xe2\x88\x89"            }, /* ∉ [NOT AN ELEMENT OF]*/
	{"notinvb",               "\xe2\x8b\xb7"            }, /* ⋷ [SMALL ELEMENT OF WITH OVERBAR]*/
	{"notinvc",               "\xe2\x8b\xb6"            }, /* ⋶ [ELEMENT OF WITH OVERBAR]*/
	{"notni",                 "\xe2\x88\x8c"            }, /* ∌ [DOES NOT CONTAIN AS MEMBER]*/
	{"notniva",               "\xe2\x88\x8c"            }, /* ∌ [DOES NOT CONTAIN AS MEMBER]*/
	{"notnivb",               "\xe2\x8b\xbe"            }, /* ⋾ [SMALL CONTAINS WITH OVERBAR]*/
	{"notnivc",               "\xe2\x8b\xbd"            }, /* ⋽ [CONTAINS WITH OVERBAR]*/
	{"npar",                  "\xe2\x88\xa6"            }, /* ∦ [NOT PARALLEL TO]*/
	{"nparallel",             "\xe2\x88\xa6"            }, /* ∦ [NOT PARALLEL TO]*/
	{"nparsl",                "\xe2\xab\xbd\xe2\x83\xa5"}, /* ⫽⃥ [DOUBLE SOLIDUS OPERATOR with reverse slash]*/
	{"npart",                 "\xe2\x88\x82\xcc\xb8"    }, /* ∂̸ [PARTIAL DIFFERENTIAL with slash]*/
	{"npolint",               "\xe2\xa8\x94"            }, /* ⨔ [LINE INTEGRATION NOT INCLUDING THE POLE]*/
	{"npr",                   "\xe2\x8a\x80"            }, /* ⊀ [DOES NOT PRECEDE]*/
	{"nprcue",                "\xe2\x8b\xa0"            }, /* ⋠ [DOES NOT PRECEDE OR EQUAL]*/
	{"npre",                  "\xe2\xaa\xaf\xcc\xb8"    }, /* ⪯̸ [PRECEDES ABOVE SINGLE-LINE EQUALS SIGN with slash]*/
	{"nprec",                 "\xe2\x8a\x80"            }, /* ⊀ [DOES NOT PRECEDE]*/
	{"npreceq",               "\xe2\xaa\xaf\xcc\xb8"    }, /* ⪯̸ [PRECEDES ABOVE SINGLE-LINE EQUALS SIGN with slash]*/
	{"nrArr",                 "\xe2\x87\x8f"            }, /* ⇏ [RIGHTWARDS DOUBLE ARROW WITH STROKE]*/
	{"nrarr",                 "\xe2\x86\x9b"            }, /* ↛ [RIGHTWARDS ARROW WITH STROKE]*/
	{"nrarrc",                "\xe2\xa4\xb3\xcc\xb8"    }, /* ⤳̸ [WAVE ARROW POINTING DIRECTLY RIGHT with slash]*/
	{"nrarrw",                "\xe2\x86\x9d\xcc\xb8"    }, /* ↝̸ [RIGHTWARDS WAVE ARROW with slash]*/
	{"nrightarrow",           "\xe2\x86\x9b"            }, /* ↛ [RIGHTWARDS ARROW WITH STROKE]*/
	{"nrtri",                 "\xe2\x8b\xab"            }, /* ⋫ [DOES NOT CONTAIN AS NORMAL SUBGROUP]*/
	{"nrtrie",                "\xe2\x8b\xad"            }, /* ⋭ [DOES NOT CONTAIN AS NORMAL SUBGROUP OR EQUAL]*/
	{"nsc",                   "\xe2\x8a\x81"            }, /* ⊁ [DOES NOT SUCCEED]*/
	{"nsccue",                "\xe2\x8b\xa1"            }, /* ⋡ [DOES NOT SUCCEED OR EQUAL]*/
	{"nsce",                  "\xe2\xaa\xb0\xcc\xb8"    }, /* ⪰̸ [SUCCEEDS ABOVE SINGLE-LINE EQUALS SIGN with slash]*/
	{"nscr",                  "\xf0\x9d\x93\x83"        }, /* 𝓃 [MATHEMATICAL SCRIPT SMALL N]*/
	{"nshortmid",             "\xe2\x88\xa4"            }, /* ∤ [DOES NOT DIVIDE]*/
	{"nshortparallel",        "\xe2\x88\xa6"            }, /* ∦ [NOT PARALLEL TO]*/
	{"nsim",                  "\xe2\x89\x81"            }, /* ≁ [NOT TILDE]*/
	{"nsime",                 "\xe2\x89\x84"            }, /* ≄ [NOT ASYMPTOTICALLY EQUAL TO]*/
	{"nsimeq",                "\xe2\x89\x84"            }, /* ≄ [NOT ASYMPTOTICALLY EQUAL TO]*/
	{"nsmid",                 "\xe2\x88\xa4"            }, /* ∤ [DOES NOT DIVIDE]*/
	{"nspar",                 "\xe2\x88\xa6"            }, /* ∦ [NOT PARALLEL TO]*/
	{"nsqsube",               "\xe2\x8b\xa2"            }, /* ⋢ [NOT SQUARE IMAGE OF OR EQUAL TO]*/
	{"nsqsupe",               "\xe2\x8b\xa3"            }, /* ⋣ [NOT SQUARE ORIGINAL OF OR EQUAL TO]*/
	{"nsub",                  "\xe2\x8a\x84"            }, /* ⊄ [NOT A SUBSET OF]*/
	{"nsubE",                 "\xe2\xab\x85\xcc\xb8"    }, /* ⫅̸ [SUBSET OF ABOVE EQUALS SIGN with slash]*/
	{"nsube",                 "\xe2\x8a\x88"            }, /* ⊈ [NEITHER A SUBSET OF NOR EQUAL TO]*/
	{"nsubset",               "\xe2\x8a\x82\xe2\x83\x92"}, /* ⊂⃒ [SUBSET OF with vertical line]*/
	{"nsubseteq",             "\xe2\x8a\x88"            }, /* ⊈ [NEITHER A SUBSET OF NOR EQUAL TO]*/
	{"nsubseteqq",            "\xe2\xab\x85\xcc\xb8"    }, /* ⫅̸ [SUBSET OF ABOVE EQUALS SIGN with slash]*/
	{"nsucc",                 "\xe2\x8a\x81"            }, /* ⊁ [DOES NOT SUCCEED]*/
	{"nsucceq",               "\xe2\xaa\xb0\xcc\xb8"    }, /* ⪰̸ [SUCCEEDS ABOVE SINGLE-LINE EQUALS SIGN with slash]*/
	{"nsup",                  "\xe2\x8a\x85"            }, /* ⊅ [NOT A SUPERSET OF]*/
	{"nsupE",                 "\xe2\xab\x86\xcc\xb8"    }, /* ⫆̸ [SUPERSET OF ABOVE EQUALS SIGN with slash]*/
	{"nsupe",                 "\xe2\x8a\x89"            }, /* ⊉ [NEITHER A SUPERSET OF NOR EQUAL TO]*/
	{"nsupset",               "\xe2\x8a\x83\xe2\x83\x92"}, /* ⊃⃒ [SUPERSET OF with vertical line]*/
	{"nsupseteq",             "\xe2\x8a\x89"            }, /* ⊉ [NEITHER A SUPERSET OF NOR EQUAL TO]*/
	{"nsupseteqq",            "\xe2\xab\x86\xcc\xb8"    }, /* ⫆̸ [SUPERSET OF ABOVE EQUALS SIGN with slash]*/
	{"ntgl",                  "\xe2\x89\xb9"            }, /* ≹ [NEITHER GREATER-THAN NOR LESS-THAN]*/
	{"ntilde",                "\xc3\xb1"                }, /* ñ [LATIN SMALL LETTER N WITH TILDE]*/
	{"ntlg",                  "\xe2\x89\xb8"            }, /* ≸ [NEITHER LESS-THAN NOR GREATER-THAN]*/
	{"ntriangleleft",         "\xe2\x8b\xaa"            }, /* ⋪ [NOT NORMAL SUBGROUP OF]*/
	{"ntrianglelefteq",       "\xe2\x8b\xac"            }, /* ⋬ [NOT NORMAL SUBGROUP OF OR EQUAL TO]*/
	{"ntriangleright",        "\xe2\x8b\xab"            }, /* ⋫ [DOES NOT CONTAIN AS NORMAL SUBGROUP]*/
	{"ntrianglerighteq",      "\xe2\x8b\xad"            }, /* ⋭ [DOES NOT CONTAIN AS NORMAL SUBGROUP OR EQUAL]*/
	{"nu",                    "\xce\xbd"                }, /* ν [GREEK SMALL LETTER NU]*/
	{"num",                   "\x23"                    }, /* # [NUMBER SIGN]*/
	{"numero",                "\xe2\x84\x96"            }, /* № [NUMERO SIGN]*/
	{"numsp",                 "\xe2\x80\x87"            }, /*   [FIGURE SPACE]*/
	{"nvDash",                "\xe2\x8a\xad"            }, /* ⊭ [NOT TRUE]*/
	{"nvHarr",                "\xe2\xa4\x84"            }, /* ⤄ [LEFT RIGHT DOUBLE ARROW WITH VERTICAL STROKE]*/
	{"nvap",                  "\xe2\x89\x8d\xe2\x83\x92"}, /* ≍⃒ [EQUIVALENT TO with vertical line]*/
	{"nvdash",                "\xe2\x8a\xac"            }, /* ⊬ [DOES NOT PROVE]*/
	{"nvge",                  "\xe2\x89\xa5\xe2\x83\x92"}, /* ≥⃒ [GREATER-THAN OR EQUAL TO with vertical line]*/
	{"nvgt",                  "\x3e\xe2\x83\x92"        }, /* >⃒ [GREATER-THAN SIGN with vertical line]*/
	{"nvinfin",               "\xe2\xa7\x9e"            }, /* ⧞ [INFINITY NEGATED WITH VERTICAL BAR]*/
	{"nvlArr",                "\xe2\xa4\x82"            }, /* ⤂ [LEFTWARDS DOUBLE ARROW WITH VERTICAL STROKE]*/
	{"nvle",                  "\xe2\x89\xa4\xe2\x83\x92"}, /* ≤⃒ [LESS-THAN OR EQUAL TO with vertical line]*/
	{"nvlt",                  "\x3c\xe2\x83\x92"        }, /* <⃒ [LESS-THAN SIGN with vertical line]*/
	{"nvltrie",               "\xe2\x8a\xb4\xe2\x83\x92"}, /* ⊴⃒ [NORMAL SUBGROUP OF OR EQUAL TO with vertical line]*/
	{"nvrArr",                "\xe2\xa4\x83"            }, /* ⤃ [RIGHTWARDS DOUBLE ARROW WITH VERTICAL STROKE]*/
	{"nvrtrie",               "\xe2\x8a\xb5\xe2\x83\x92"}, /* ⊵⃒ [CONTAINS AS NORMAL SUBGROUP OR EQUAL TO with vertical line]*/
	{"nvsim",                 "\xe2\x88\xbc\xe2\x83\x92"}, /* ∼⃒ [TILDE OPERATOR with vertical line]*/
	{"nwArr",                 "\xe2\x87\x96"            }, /* ⇖ [NORTH WEST DOUBLE ARROW]*/
	{"nwarhk",                "\xe2\xa4\xa3"            }, /* ⤣ [NORTH WEST ARROW WITH HOOK]*/
	{"nwarr",                 "\xe2\x86\x96"            }, /* ↖ [NORTH WEST ARROW]*/
	{"nwarrow",               "\xe2\x86\x96"            }, /* ↖ [NORTH WEST ARROW]*/
	{"nwnear",                "\xe2\xa4\xa7"            }, /* ⤧ [NORTH WEST ARROW AND NORTH EAST ARROW]*/
	{"oS",                    "\xe2\x93\x88"            }, /* Ⓢ [CIRCLED LATIN CAPITAL LETTER S]*/
	{"oacute",                "\xc3\xb3"                }, /* ó [LATIN SMALL LETTER O WITH ACUTE]*/
	{"oast",                  "\xe2\x8a\x9b"            }, /* ⊛ [CIRCLED ASTERISK OPERATOR]*/
	{"ocir",                  "\xe2\x8a\x9a"            }, /* ⊚ [CIRCLED RING OPERATOR]*/
	{"ocirc",                 "\xc3\xb4"                }, /* ô [LATIN SMALL LETTER O WITH CIRCUMFLEX]*/
	{"ocy",                   "\xd0\xbe"                }, /* о [CYRILLIC SMALL LETTER O]*/
	{"odash",                 "\xe2\x8a\x9d"            }, /* ⊝ [CIRCLED DASH]*/
	{"odblac",                "\xc5\x91"                }, /* ő [LATIN SMALL LETTER O WITH DOUBLE ACUTE]*/
	{"odiv",                  "\xe2\xa8\xb8"            }, /* ⨸ [CIRCLED DIVISION SIGN]*/
	{"odot",                  "\xe2\x8a\x99"            }, /* ⊙ [CIRCLED DOT OPERATOR]*/
	{"odsold",                "\xe2\xa6\xbc"            }, /* ⦼ [CIRCLED ANTICLOCKWISE-ROTATED DIVISION SIGN]*/
	{"oelig",                 "\xc5\x93"                }, /* œ [LATIN SMALL LIGATURE OE]*/
	{"ofcir",                 "\xe2\xa6\xbf"            }, /* ⦿ [CIRCLED BULLET]*/
	{"ofr",                   "\xf0\x9d\x94\xac"        }, /* 𝔬 [MATHEMATICAL FRAKTUR SMALL O]*/
	{"ogon",                  "\xcb\x9b"                }, /* ˛ [OGONEK]*/
	{"ograve",                "\xc3\xb2"                }, /* ò [LATIN SMALL LETTER O WITH GRAVE]*/
	{"ogt",                   "\xe2\xa7\x81"            }, /* ⧁ [CIRCLED GREATER-THAN]*/
	{"ohbar",                 "\xe2\xa6\xb5"            }, /* ⦵ [CIRCLE WITH HORIZONTAL BAR]*/
	{"ohm",                   "\xe2\x84\xa6"            }, /* Ω [OHM SIGN]*/
	{"oint",                  "\xe2\x88\xae"            }, /* ∮ [CONTOUR INTEGRAL]*/
	{"olarr",                 "\xe2\x86\xba"            }, /* ↺ [ANTICLOCKWISE OPEN CIRCLE ARROW]*/
	{"olcir",                 "\xe2\xa6\xbe"            }, /* ⦾ [CIRCLED WHITE BULLET]*/
	{"olcross",               "\xe2\xa6\xbb"            }, /* ⦻ [CIRCLE WITH SUPERIMPOSED X]*/
	{"olt",                   "\xe2\xa7\x80"            }, /* ⧀ [CIRCLED LESS-THAN]*/
	{"omacr",                 "\xc5\x8d"                }, /* ō [LATIN SMALL LETTER O WITH MACRON]*/
	{"omega",                 "\xcf\x89"                }, /* ω [GREEK SMALL LETTER OMEGA]*/
	{"omid",                  "\xe2\xa6\xb6"            }, /* ⦶ [CIRCLED VERTICAL BAR]*/
	{"ominus",                "\xe2\x8a\x96"            }, /* ⊖ [CIRCLED MINUS]*/
	{"oopf",                  "\xf0\x9d\x95\xa0"        }, /* 𝕠 [MATHEMATICAL DOUBLE-STRUCK SMALL O]*/
	{"opar",                  "\xe2\xa6\xb7"            }, /* ⦷ [CIRCLED PARALLEL]*/
	{"operp",                 "\xe2\xa6\xb9"            }, /* ⦹ [CIRCLED PERPENDICULAR]*/
	{"oplus",                 "\xe2\x8a\x95"            }, /* ⊕ [CIRCLED PLUS]*/
	{"or",                    "\xe2\x88\xa8"            }, /* ∨ [LOGICAL OR]*/
	{"orarr",                 "\xe2\x86\xbb"            }, /* ↻ [CLOCKWISE OPEN CIRCLE ARROW]*/
	{"ord",                   "\xe2\xa9\x9d"            }, /* ⩝ [LOGICAL OR WITH HORIZONTAL DASH]*/
	{"order",                 "\xe2\x84\xb4"            }, /* ℴ [SCRIPT SMALL O]*/
	{"orderof",               "\xe2\x84\xb4"            }, /* ℴ [SCRIPT SMALL O]*/
	{"ordf",                  "\xc2\xaa"                }, /* ª [FEMININE ORDINAL INDICATOR]*/
	{"ordm",                  "\xc2\xba"                }, /* º [MASCULINE ORDINAL INDICATOR]*/
	{"origof",                "\xe2\x8a\xb6"            }, /* ⊶ [ORIGINAL OF]*/
	{"oror",                  "\xe2\xa9\x96"            }, /* ⩖ [TWO INTERSECTING LOGICAL OR]*/
	{"orslope",               "\xe2\xa9\x97"            }, /* ⩗ [SLOPING LARGE OR]*/
	{"orv",                   "\xe2\xa9\x9b"            }, /* ⩛ [LOGICAL OR WITH MIDDLE STEM]*/
	{"oscr",                  "\xe2\x84\xb4"            }, /* ℴ [SCRIPT SMALL O]*/
	{"oslash",                "\xc3\xb8"                }, /* ø [LATIN SMALL LETTER O WITH STROKE]*/
	{"osol",                  "\xe2\x8a\x98"            }, /* ⊘ [CIRCLED DIVISION SLASH]*/
	{"otilde",                "\xc3\xb5"                }, /* õ [LATIN SMALL LETTER O WITH TILDE]*/
	{"otimes",                "\xe2\x8a\x97"            }, /* ⊗ [CIRCLED TIMES]*/
	{"otimesas",              "\xe2\xa8\xb6"            }, /* ⨶ [CIRCLED MULTIPLICATION SIGN WITH CIRCUMFLEX ACCENT]*/
	{"ouml",                  "\xc3\xb6"                }, /* ö [LATIN SMALL LETTER O WITH DIAERESIS]*/
	{"ovbar",                 "\xe2\x8c\xbd"            }, /* ⌽ [APL FUNCTIONAL SYMBOL CIRCLE STILE]*/
	{"par",                   "\xe2\x88\xa5"            }, /* ∥ [PARALLEL TO]*/
	{"para",                  "\xc2\xb6"                }, /* ¶ [PILCROW SIGN]*/
	{"parallel",              "\xe2\x88\xa5"            }, /* ∥ [PARALLEL TO]*/
	{"parsim",                "\xe2\xab\xb3"            }, /* ⫳ [PARALLEL WITH TILDE OPERATOR]*/
	{"parsl",                 "\xe2\xab\xbd"            }, /* ⫽ [DOUBLE SOLIDUS OPERATOR]*/
	{"part",                  "\xe2\x88\x82"            }, /* ∂ [PARTIAL DIFFERENTIAL]*/
	{"pcy",                   "\xd0\xbf"                }, /* п [CYRILLIC SMALL LETTER PE]*/
	{"percnt",                "\x25"                    }, /* % [PERCENT SIGN]*/
	{"period",                "\x2e"                    }, /* . [FULL STOP]*/
	{"permil",                "\xe2\x80\xb0"            }, /* ‰ [PER MILLE SIGN]*/
	{"perp",                  "\xe2\x8a\xa5"            }, /* ⊥ [UP TACK]*/
	{"pertenk",               "\xe2\x80\xb1"            }, /* ‱ [PER TEN THOUSAND SIGN]*/
	{"pfr",                   "\xf0\x9d\x94\xad"        }, /* 𝔭 [MATHEMATICAL FRAKTUR SMALL P]*/
	{"phi",                   "\xcf\x95"                }, /* ϕ [GREEK PHI SYMBOL]*/
	{"phiv",                  "\xcf\x86"                }, /* φ [GREEK SMALL LETTER PHI]*/
	{"phmmat",                "\xe2\x84\xb3"            }, /* ℳ [SCRIPT CAPITAL M]*/
	{"phone",                 "\xe2\x98\x8e"            }, /* ☎ [BLACK TELEPHONE]*/
	{"pi",                    "\xcf\x80"                }, /* π [GREEK SMALL LETTER PI]*/
	{"pitchfork",             "\xe2\x8b\x94"            }, /* ⋔ [PITCHFORK]*/
	{"piv",                   "\xcf\x96"                }, /* ϖ [GREEK PI SYMBOL]*/
	{"planck",                "\xe2\x84\x8f"            }, /* ℏ [PLANCK CONSTANT OVER TWO PI]*/
	{"planckh",               "\xe2\x84\x8e"            }, /* ℎ [PLANCK CONSTANT]*/
	{"plankv",                "\xe2\x84\x8f"            }, /* ℏ [PLANCK CONSTANT OVER TWO PI]*/
	{"plus",                  "\x2b"                    }, /* + [PLUS SIGN]*/
	{"plusacir",              "\xe2\xa8\xa3"            }, /* ⨣ [PLUS SIGN WITH CIRCUMFLEX ACCENT ABOVE]*/
	{"plusb",                 "\xe2\x8a\x9e"            }, /* ⊞ [SQUARED PLUS]*/
	{"pluscir",               "\xe2\xa8\xa2"            }, /* ⨢ [PLUS SIGN WITH SMALL CIRCLE ABOVE]*/
	{"plusdo",                "\xe2\x88\x94"            }, /* ∔ [DOT PLUS]*/
	{"plusdu",                "\xe2\xa8\xa5"            }, /* ⨥ [PLUS SIGN WITH DOT BELOW]*/
	{"pluse",                 "\xe2\xa9\xb2"            }, /* ⩲ [PLUS SIGN ABOVE EQUALS SIGN]*/
	{"plusmn",                "\xc2\xb1"                }, /* ± [PLUS-MINUS SIGN]*/
	{"plussim",               "\xe2\xa8\xa6"            }, /* ⨦ [PLUS SIGN WITH TILDE BELOW]*/
	{"plustwo",               "\xe2\xa8\xa7"            }, /* ⨧ [PLUS SIGN WITH SUBSCRIPT TWO]*/
	{"pm",                    "\xc2\xb1"                }, /* ± [PLUS-MINUS SIGN]*/
	{"pointint",              "\xe2\xa8\x95"            }, /* ⨕ [INTEGRAL AROUND A POINT OPERATOR]*/
	{"popf",                  "\xf0\x9d\x95\xa1"        }, /* 𝕡 [MATHEMATICAL DOUBLE-STRUCK SMALL P]*/
	{"pound",                 "\xc2\xa3"                }, /* £ [POUND SIGN]*/
	{"pr",                    "\xe2\x89\xba"            }, /* ≺ [PRECEDES]*/
	{"prE",                   "\xe2\xaa\xb3"            }, /* ⪳ [PRECEDES ABOVE EQUALS SIGN]*/
	{"prap",                  "\xe2\xaa\xb7"            }, /* ⪷ [PRECEDES ABOVE ALMOST EQUAL TO]*/
	{"prcue",                 "\xe2\x89\xbc"            }, /* ≼ [PRECEDES OR EQUAL TO]*/
	{"pre",                   "\xe2\xaa\xaf"            }, /* ⪯ [PRECEDES ABOVE SINGLE-LINE EQUALS SIGN]*/
	{"prec",                  "\xe2\x89\xba"            }, /* ≺ [PRECEDES]*/
	{"precapprox",            "\xe2\xaa\xb7"            }, /* ⪷ [PRECEDES ABOVE ALMOST EQUAL TO]*/
	{"preccurlyeq",           "\xe2\x89\xbc"            }, /* ≼ [PRECEDES OR EQUAL TO]*/
	{"preceq",                "\xe2\xaa\xaf"            }, /* ⪯ [PRECEDES ABOVE SINGLE-LINE EQUALS SIGN]*/
	{"precnapprox",           "\xe2\xaa\xb9"            }, /* ⪹ [PRECEDES ABOVE NOT ALMOST EQUAL TO]*/
	{"precneqq",              "\xe2\xaa\xb5"            }, /* ⪵ [PRECEDES ABOVE NOT EQUAL TO]*/
	{"precnsim",              "\xe2\x8b\xa8"            }, /* ⋨ [PRECEDES BUT NOT EQUIVALENT TO]*/
	{"precsim",               "\xe2\x89\xbe"            }, /* ≾ [PRECEDES OR EQUIVALENT TO]*/
	{"prime",                 "\xe2\x80\xb2"            }, /* ′ [PRIME]*/
	{"primes",                "\xe2\x84\x99"            }, /* ℙ [DOUBLE-STRUCK CAPITAL P]*/
	{"prnE",                  "\xe2\xaa\xb5"            }, /* ⪵ [PRECEDES ABOVE NOT EQUAL TO]*/
	{"prnap",                 "\xe2\xaa\xb9"            }, /* ⪹ [PRECEDES ABOVE NOT ALMOST EQUAL TO]*/
	{"prnsim",                "\xe2\x8b\xa8"            }, /* ⋨ [PRECEDES BUT NOT EQUIVALENT TO]*/
	{"prod",                  "\xe2\x88\x8f"            }, /* ∏ [N-ARY PRODUCT]*/
	{"profalar",              "\xe2\x8c\xae"            }, /* ⌮ [ALL AROUND-PROFILE]*/
	{"profline",              "\xe2\x8c\x92"            }, /* ⌒ [ARC]*/
	{"profsurf",              "\xe2\x8c\x93"            }, /* ⌓ [SEGMENT]*/
	{"prop",                  "\xe2\x88\x9d"            }, /* ∝ [PROPORTIONAL TO]*/
	{"propto",                "\xe2\x88\x9d"            }, /* ∝ [PROPORTIONAL TO]*/
	{"prsim",                 "\xe2\x89\xbe"            }, /* ≾ [PRECEDES OR EQUIVALENT TO]*/
	{"prurel",                "\xe2\x8a\xb0"            }, /* ⊰ [PRECEDES UNDER RELATION]*/
	{"pscr",                  "\xf0\x9d\x93\x85"        }, /* 𝓅 [MATHEMATICAL SCRIPT SMALL P]*/
	{"psi",                   "\xcf\x88"                }, /* ψ [GREEK SMALL LETTER PSI]*/
	{"puncsp",                "\xe2\x80\x88"            }, /*   [PUNCTUATION SPACE]*/
	{"qfr",                   "\xf0\x9d\x94\xae"        }, /* 𝔮 [MATHEMATICAL FRAKTUR SMALL Q]*/
	{"qint",                  "\xe2\xa8\x8c"            }, /* ⨌ [QUADRUPLE INTEGRAL OPERATOR]*/
	{"qopf",                  "\xf0\x9d\x95\xa2"        }, /* 𝕢 [MATHEMATICAL DOUBLE-STRUCK SMALL Q]*/
	{"qprime",                "\xe2\x81\x97"            }, /* ⁗ [QUADRUPLE PRIME]*/
	{"qscr",                  "\xf0\x9d\x93\x86"        }, /* 𝓆 [MATHEMATICAL SCRIPT SMALL Q]*/
	{"quaternions",           "\xe2\x84\x8d"            }, /* ℍ [DOUBLE-STRUCK CAPITAL H]*/
	{"quatint",               "\xe2\xa8\x96"            }, /* ⨖ [QUATERNION INTEGRAL OPERATOR]*/
	{"quest",                 "\x3f"                    }, /* ? [QUESTION MARK]*/
	{"questeq",               "\xe2\x89\x9f"            }, /* ≟ [QUESTIONED EQUAL TO]*/
	{"quot",                  "\x22"                    }, /* " [QUOTATION MARK]*/
	{"rAarr",                 "\xe2\x87\x9b"            }, /* ⇛ [RIGHTWARDS TRIPLE ARROW]*/
	{"rArr",                  "\xe2\x87\x92"            }, /* ⇒ [RIGHTWARDS DOUBLE ARROW]*/
	{"rAtail",                "\xe2\xa4\x9c"            }, /* ⤜ [RIGHTWARDS DOUBLE ARROW-TAIL]*/
	{"rBarr",                 "\xe2\xa4\x8f"            }, /* ⤏ [RIGHTWARDS TRIPLE DASH ARROW]*/
	{"rHar",                  "\xe2\xa5\xa4"            }, /* ⥤ [RIGHTWARDS HARPOON WITH BARB UP ABOVE RIGHTWARDS HARPOON WITH BARB DOWN]*/
	{"race",                  "\xe2\xa7\x9a"            }, /* ⧚ [LEFT DOUBLE WIGGLY FENCE]*/
	{"racute",                "\xc5\x95"                }, /* ŕ [LATIN SMALL LETTER R WITH ACUTE]*/
	{"radic",                 "\xe2\x88\x9a"            }, /* √ [SQUARE ROOT]*/
	{"raemptyv",              "\xe2\xa6\xb3"            }, /* ⦳ [EMPTY SET WITH RIGHT ARROW ABOVE]*/
	{"rang",                  "\xe2\x8c\xaa"            }, /* 〉 [RIGHT-POINTING ANGLE BRACKET]*/
	{"rangd",                 "\xe2\xa6\x92"            }, /* ⦒ [RIGHT ANGLE BRACKET WITH DOT]*/
	{"range",                 "\xe2\xa6\xa5"            }, /* ⦥ [REVERSED ANGLE WITH UNDERBAR]*/
	{"rangle",                "\xe2\x8c\xaa"            }, /* 〉 [RIGHT-POINTING ANGLE BRACKET]*/
	{"raquo",                 "\xc2\xbb"                }, /* » [RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK]*/
	{"rarr",                  "\xe2\x86\x92"            }, /* → [RIGHTWARDS ARROW]*/
	{"rarrap",                "\xe2\xa5\xb5"            }, /* ⥵ [RIGHTWARDS ARROW ABOVE ALMOST EQUAL TO]*/
	{"rarrb",                 "\xe2\x87\xa5"            }, /* ⇥ [RIGHTWARDS ARROW TO BAR]*/
	{"rarrbfs",               "\xe2\xa4\xa0"            }, /* ⤠ [RIGHTWARDS ARROW FROM BAR TO BLACK DIAMOND]*/
	{"rarrc",                 "\xe2\xa4\xb3"            }, /* ⤳ [WAVE ARROW POINTING DIRECTLY RIGHT]*/
	{"rarrfs",                "\xe2\xa4\x9e"            }, /* ⤞ [RIGHTWARDS ARROW TO BLACK DIAMOND]*/
	{"rarrhk",                "\xe2\x86\xaa"            }, /* ↪ [RIGHTWARDS ARROW WITH HOOK]*/
	{"rarrlp",                "\xe2\x86\xac"            }, /* ↬ [RIGHTWARDS ARROW WITH LOOP]*/
	{"rarrpl",                "\xe2\xa5\x85"            }, /* ⥅ [RIGHTWARDS ARROW WITH PLUS BELOW]*/
	{"rarrsim",               "\xe2\xa5\xb4"            }, /* ⥴ [RIGHTWARDS ARROW ABOVE TILDE OPERATOR]*/
	{"rarrtl",                "\xe2\x86\xa3"            }, /* ↣ [RIGHTWARDS ARROW WITH TAIL]*/
	{"rarrw",                 "\xe2\x86\x9d"            }, /* ↝ [RIGHTWARDS WAVE ARROW]*/
	{"ratail",                "\xe2\xa4\x9a"            }, /* ⤚ [RIGHTWARDS ARROW-TAIL]*/
	{"ratio",                 "\xe2\x88\xb6"            }, /* ∶ [RATIO]*/
	{"rationals",             "\xe2\x84\x9a"            }, /* ℚ [DOUBLE-STRUCK CAPITAL Q]*/
	{"rbarr",                 "\xe2\xa4\x8d"            }, /* ⤍ [RIGHTWARDS DOUBLE DASH ARROW]*/
	{"rbbrk",                 "\xe3\x80\x95"            }, /* 〕 [RIGHT TORTOISE SHELL BRACKET]*/
	{"rbrace",                "\x7d"                    }, /* } [RIGHT CURLY BRACKET]*/
	{"rbrack",                "\x5d"                    }, /* ] [RIGHT SQUARE BRACKET]*/
	{"rbrke",                 "\xe2\xa6\x8c"            }, /* ⦌ [RIGHT SQUARE BRACKET WITH UNDERBAR]*/
	{"rbrksld",               "\xe2\xa6\x8e"            }, /* ⦎ [RIGHT SQUARE BRACKET WITH TICK IN BOTTOM CORNER]*/
	{"rbrkslu",               "\xe2\xa6\x90"            }, /* ⦐ [RIGHT SQUARE BRACKET WITH TICK IN TOP CORNER]*/
	{"rcaron",                "\xc5\x99"                }, /* ř [LATIN SMALL LETTER R WITH CARON]*/
	{"rcedil",                "\xc5\x97"                }, /* ŗ [LATIN SMALL LETTER R WITH CEDILLA]*/
	{"rceil",                 "\xe2\x8c\x89"            }, /* ⌉ [RIGHT CEILING]*/
	{"rcub",                  "\x7d"                    }, /* } [RIGHT CURLY BRACKET]*/
	{"rcy",                   "\xd1\x80"                }, /* р [CYRILLIC SMALL LETTER ER]*/
	{"rdca",                  "\xe2\xa4\xb7"            }, /* ⤷ [ARROW POINTING DOWNWARDS THEN CURVING RIGHTWARDS]*/
	{"rdldhar",               "\xe2\xa5\xa9"            }, /* ⥩ [RIGHTWARDS HARPOON WITH BARB DOWN ABOVE LEFTWARDS HARPOON WITH BARB DOWN]*/
	{"rdquo",                 "\xe2\x80\x9d"            }, /* ” [RIGHT DOUBLE QUOTATION MARK]*/
	{"rdquor",                "\xe2\x80\x9d"            }, /* ” [RIGHT DOUBLE QUOTATION MARK]*/
	{"rdsh",                  "\xe2\x86\xb3"            }, /* ↳ [DOWNWARDS ARROW WITH TIP RIGHTWARDS]*/
	{"real",                  "\xe2\x84\x9c"            }, /* ℜ [BLACK-LETTER CAPITAL R]*/
	{"realine",               "\xe2\x84\x9b"            }, /* ℛ [SCRIPT CAPITAL R]*/
	{"realpart",              "\xe2\x84\x9c"            }, /* ℜ [BLACK-LETTER CAPITAL R]*/
	{"reals",                 "\xe2\x84\x9d"            }, /* ℝ [DOUBLE-STRUCK CAPITAL R]*/
	{"rect",                  "\xe2\x96\xad"            }, /* ▭ [WHITE RECTANGLE]*/
	{"reg",                   "\xc2\xae"                }, /* ® [REGISTERED SIGN]*/
	{"rfisht",                "\xe2\xa5\xbd"            }, /* ⥽ [RIGHT FISH TAIL]*/
	{"rfloor",                "\xe2\x8c\x8b"            }, /* ⌋ [RIGHT FLOOR]*/
	{"rfr",                   "\xf0\x9d\x94\xaf"        }, /* 𝔯 [MATHEMATICAL FRAKTUR SMALL R]*/
	{"rhard",                 "\xe2\x87\x81"            }, /* ⇁ [RIGHTWARDS HARPOON WITH BARB DOWNWARDS]*/
	{"rharu",                 "\xe2\x87\x80"            }, /* ⇀ [RIGHTWARDS HARPOON WITH BARB UPWARDS]*/
	{"rharul",                "\xe2\xa5\xac"            }, /* ⥬ [RIGHTWARDS HARPOON WITH BARB UP ABOVE LONG DASH]*/
	{"rho",                   "\xcf\x81"                }, /* ρ [GREEK SMALL LETTER RHO]*/
	{"rhov",                  "\xcf\xb1"                }, /* ϱ [GREEK RHO SYMBOL]*/
	{"rightarrow",            "\xe2\x86\x92"            }, /* → [RIGHTWARDS ARROW]*/
	{"rightarrowtail",        "\xe2\x86\xa3"            }, /* ↣ [RIGHTWARDS ARROW WITH TAIL]*/
	{"rightharpoondown",      "\xe2\x87\x81"            }, /* ⇁ [RIGHTWARDS HARPOON WITH BARB DOWNWARDS]*/
	{"rightharpoonup",        "\xe2\x87\x80"            }, /* ⇀ [RIGHTWARDS HARPOON WITH BARB UPWARDS]*/
	{"rightleftarrows",       "\xe2\x87\x84"            }, /* ⇄ [RIGHTWARDS ARROW OVER LEFTWARDS ARROW]*/
	{"rightleftharpoons",     "\xe2\x87\x8c"            }, /* ⇌ [RIGHTWARDS HARPOON OVER LEFTWARDS HARPOON]*/
	{"rightrightarrows",      "\xe2\x87\x89"            }, /* ⇉ [RIGHTWARDS PAIRED ARROWS]*/
	{"rightsquigarrow",       "\xe2\x86\x9d"            }, /* ↝ [RIGHTWARDS WAVE ARROW]*/
	{"rightthreetimes",       "\xe2\x8b\x8c"            }, /* ⋌ [RIGHT SEMIDIRECT PRODUCT]*/
	{"ring",                  "\xcb\x9a"                }, /* ˚ [RING ABOVE]*/
	{"risingdotseq",          "\xe2\x89\x93"            }, /* ≓ [IMAGE OF OR APPROXIMATELY EQUAL TO]*/
	{"rlarr",                 "\xe2\x87\x84"            }, /* ⇄ [RIGHTWARDS ARROW OVER LEFTWARDS ARROW]*/
	{"rlhar",                 "\xe2\x87\x8c"            }, /* ⇌ [RIGHTWARDS HARPOON OVER LEFTWARDS HARPOON]*/
	{"rmoust",                "\xe2\x8e\xb1"            }, /* ⎱ [UPPER RIGHT OR LOWER LEFT CURLY BRACKET SECTION]*/
	{"rmoustache",            "\xe2\x8e\xb1"            }, /* ⎱ [UPPER RIGHT OR LOWER LEFT CURLY BRACKET SECTION]*/
	{"rnmid",                 "\xe2\xab\xae"            }, /* ⫮ [DOES NOT DIVIDE WITH REVERSED NEGATION SLASH]*/
	{"roang",                 "\xe3\x80\x99"            }, /* 〙 [RIGHT WHITE TORTOISE SHELL BRACKET]*/
	{"roarr",                 "\xe2\x87\xbe"            }, /* ⇾ [RIGHTWARDS OPEN-HEADED ARROW]*/
	{"robrk",                 "\xe3\x80\x9b"            }, /* 〛 [RIGHT WHITE SQUARE BRACKET]*/
	{"ropar",                 "\xe2\xa6\x86"            }, /* ⦆ [RIGHT WHITE PARENTHESIS]*/
	{"ropf",                  "\xf0\x9d\x95\xa3"        }, /* 𝕣 [MATHEMATICAL DOUBLE-STRUCK SMALL R]*/
	{"roplus",                "\xe2\xa8\xae"            }, /* ⨮ [PLUS SIGN IN RIGHT HALF CIRCLE]*/
	{"rotimes",               "\xe2\xa8\xb5"            }, /* ⨵ [MULTIPLICATION SIGN IN RIGHT HALF CIRCLE]*/
	{"rpar",                  "\x29"                    }, /* ) [RIGHT PARENTHESIS]*/
	{"rpargt",                "\xe2\xa6\x94"            }, /* ⦔ [RIGHT ARC GREATER-THAN BRACKET]*/
	{"rppolint",              "\xe2\xa8\x92"            }, /* ⨒ [LINE INTEGRATION WITH RECTANGULAR PATH AROUND POLE]*/
	{"rrarr",                 "\xe2\x87\x89"            }, /* ⇉ [RIGHTWARDS PAIRED ARROWS]*/
	{"rscr",                  "\xf0\x9d\x93\x87"        }, /* 𝓇 [MATHEMATICAL SCRIPT SMALL R]*/
	{"rsh",                   "\xe2\x86\xb1"            }, /* ↱ [UPWARDS ARROW WITH TIP RIGHTWARDS]*/
	{"rsqb",                  "\x5d"                    }, /* ] [RIGHT SQUARE BRACKET]*/
	{"rsquo",                 "\xe2\x80\x99"            }, /* ’ [RIGHT SINGLE QUOTATION MARK]*/
	{"rsquor",                "\xe2\x80\x99"            }, /* ’ [RIGHT SINGLE QUOTATION MARK]*/
	{"rthree",                "\xe2\x8b\x8c"            }, /* ⋌ [RIGHT SEMIDIRECT PRODUCT]*/
	{"rtimes",                "\xe2\x8b\x8a"            }, /* ⋊ [RIGHT NORMAL FACTOR SEMIDIRECT PRODUCT]*/
	{"rtri",                  "\xe2\x96\xb9"            }, /* ▹ [WHITE RIGHT-POINTING SMALL TRIANGLE]*/
	{"rtrie",                 "\xe2\x8a\xb5"            }, /* ⊵ [CONTAINS AS NORMAL SUBGROUP OR EQUAL TO]*/
	{"rtrif",                 "\xe2\x96\xb8"            }, /* ▸ [BLACK RIGHT-POINTING SMALL TRIANGLE]*/
	{"rtriltri",              "\xe2\xa7\x8e"            }, /* ⧎ [RIGHT TRIANGLE ABOVE LEFT TRIANGLE]*/
	{"ruluhar",               "\xe2\xa5\xa8"            }, /* ⥨ [RIGHTWARDS HARPOON WITH BARB UP ABOVE LEFTWARDS HARPOON WITH BARB UP]*/
	{"rx",                    "\xe2\x84\x9e"            }, /* ℞ [PRESCRIPTION TAKE]*/
	{"sacute",                "\xc5\x9b"                }, /* ś [LATIN SMALL LETTER S WITH ACUTE]*/
	{"sc",                    "\xe2\x89\xbb"            }, /* ≻ [SUCCEEDS]*/
	{"scE",                   "\xe2\xaa\xb4"            }, /* ⪴ [SUCCEEDS ABOVE EQUALS SIGN]*/
	{"scap",                  "\xe2\xaa\xb8"            }, /* ⪸ [SUCCEEDS ABOVE ALMOST EQUAL TO]*/
	{"scaron",                "\xc5\xa1"                }, /* š [LATIN SMALL LETTER S WITH CARON]*/
	{"sccue",                 "\xe2\x89\xbd"            }, /* ≽ [SUCCEEDS OR EQUAL TO]*/
	{"sce",                   "\xe2\xaa\xb0"            }, /* ⪰ [SUCCEEDS ABOVE SINGLE-LINE EQUALS SIGN]*/
	{"scedil",                "\xc5\x9f"                }, /* ş [LATIN SMALL LETTER S WITH CEDILLA]*/
	{"scirc",                 "\xc5\x9d"                }, /* ŝ [LATIN SMALL LETTER S WITH CIRCUMFLEX]*/
	{"scnE",                  "\xe2\xaa\xb6"            }, /* ⪶ [SUCCEEDS ABOVE NOT EQUAL TO]*/
	{"scnap",                 "\xe2\xaa\xba"            }, /* ⪺ [SUCCEEDS ABOVE NOT ALMOST EQUAL TO]*/
	{"scnsim",                "\xe2\x8b\xa9"            }, /* ⋩ [SUCCEEDS BUT NOT EQUIVALENT TO]*/
	{"scpolint",              "\xe2\xa8\x93"            }, /* ⨓ [LINE INTEGRATION WITH SEMICIRCULAR PATH AROUND POLE]*/
	{"scsim",                 "\xe2\x89\xbf"            }, /* ≿ [SUCCEEDS OR EQUIVALENT TO]*/
	{"scy",                   "\xd1\x81"                }, /* с [CYRILLIC SMALL LETTER ES]*/
	{"sdot",                  "\xe2\x8b\x85"            }, /* ⋅ [DOT OPERATOR]*/
	{"sdotb",                 "\xe2\x8a\xa1"            }, /* ⊡ [SQUARED DOT OPERATOR]*/
	{"sdote",                 "\xe2\xa9\xa6"            }, /* ⩦ [EQUALS SIGN WITH DOT BELOW]*/
	{"seArr",                 "\xe2\x87\x98"            }, /* ⇘ [SOUTH EAST DOUBLE ARROW]*/
	{"searhk",                "\xe2\xa4\xa5"            }, /* ⤥ [SOUTH EAST ARROW WITH HOOK]*/
	{"searr",                 "\xe2\x86\x98"            }, /* ↘ [SOUTH EAST ARROW]*/
	{"searrow",               "\xe2\x86\x98"            }, /* ↘ [SOUTH EAST ARROW]*/
	{"sect",                  "\xc2\xa7"                }, /* § [SECTION SIGN]*/
	{"semi",                  "\x3b"                    }, /* ; [SEMICOLON]*/
	{"seswar",                "\xe2\xa4\xa9"            }, /* ⤩ [SOUTH EAST ARROW AND SOUTH WEST ARROW]*/
	{"setminus",              "\xe2\x88\x96"            }, /* ∖ [SET MINUS]*/
	{"setmn",                 "\xe2\x88\x96"            }, /* ∖ [SET MINUS]*/
	{"sext",                  "\xe2\x9c\xb6"            }, /* ✶ [SIX POINTED BLACK STAR]*/
	{"sfr",                   "\xf0\x9d\x94\xb0"        }, /* 𝔰 [MATHEMATICAL FRAKTUR SMALL S]*/
	{"sfrown",                "\xe2\x8c\xa2"            }, /* ⌢ [FROWN]*/
	{"sharp",                 "\xe2\x99\xaf"            }, /* ♯ [MUSIC SHARP SIGN]*/
	{"shchcy",                "\xd1\x89"                }, /* щ [CYRILLIC SMALL LETTER SHCHA]*/
	{"shcy",                  "\xd1\x88"                }, /* ш [CYRILLIC SMALL LETTER SHA]*/
	{"shortmid",              "\xe2\x88\xa3"            }, /* ∣ [DIVIDES]*/
	{"shortparallel",         "\xe2\x88\xa5"            }, /* ∥ [PARALLEL TO]*/
	{"shy",                   "\xc2\xad"                }, /* ­ [SOFT HYPHEN]*/
	{"sigma",                 "\xcf\x83"                }, /* σ [GREEK SMALL LETTER SIGMA]*/
	{"sigmav",                "\xcf\x82"                }, /* ς [GREEK SMALL LETTER FINAL SIGMA]*/
	{"sim",                   "\xe2\x88\xbc"            }, /* ∼ [TILDE OPERATOR]*/
	{"simdot",                "\xe2\xa9\xaa"            }, /* ⩪ [TILDE OPERATOR WITH DOT ABOVE]*/
	{"sime",                  "\xe2\x89\x83"            }, /* ≃ [ASYMPTOTICALLY EQUAL TO]*/
	{"simeq",                 "\xe2\x89\x83"            }, /* ≃ [ASYMPTOTICALLY EQUAL TO]*/
	{"simg",                  "\xe2\xaa\x9e"            }, /* ⪞ [SIMILAR OR GREATER-THAN]*/
	{"simgE",                 "\xe2\xaa\xa0"            }, /* ⪠ [SIMILAR ABOVE GREATER-THAN ABOVE EQUALS SIGN]*/
	{"siml",                  "\xe2\xaa\x9d"            }, /* ⪝ [SIMILAR OR LESS-THAN]*/
	{"simlE",                 "\xe2\xaa\x9f"            }, /* ⪟ [SIMILAR ABOVE LESS-THAN ABOVE EQUALS SIGN]*/
	{"simne",                 "\xe2\x89\x86"            }, /* ≆ [APPROXIMATELY BUT NOT ACTUALLY EQUAL TO]*/
	{"simplus",               "\xe2\xa8\xa4"            }, /* ⨤ [PLUS SIGN WITH TILDE ABOVE]*/
	{"simrarr",               "\xe2\xa5\xb2"            }, /* ⥲ [TILDE OPERATOR ABOVE RIGHTWARDS ARROW]*/
	{"slarr",                 "\xe2\x86\x90"            }, /* ← [LEFTWARDS ARROW]*/
	{"smallsetminus",         "\xe2\x88\x96"            }, /* ∖ [SET MINUS]*/
	{"smashp",                "\xe2\xa8\xb3"            }, /* ⨳ [SMASH PRODUCT]*/
	{"smeparsl",              "\xe2\xa7\xa4"            }, /* ⧤ [EQUALS SIGN AND SLANTED PARALLEL WITH TILDE ABOVE]*/
	{"smid",                  "\xe2\x88\xa3"            }, /* ∣ [DIVIDES]*/
	{"smile",                 "\xe2\x8c\xa3"            }, /* ⌣ [SMILE]*/
	{"smt",                   "\xe2\xaa\xaa"            }, /* ⪪ [SMALLER THAN]*/
	{"smte",                  "\xe2\xaa\xac"            }, /* ⪬ [SMALLER THAN OR EQUAL TO]*/
	{"smtes",                 "\xe2\xaa\xac\xef\xb8\x80"}, /* ⪬︀ [SMALLER THAN OR slanted EQUAL]*/
	{"softcy",                "\xd1\x8c"                }, /* ь [CYRILLIC SMALL LETTER SOFT SIGN]*/
	{"sol",                   "\x2f"                    }, /* / [SOLIDUS]*/
	{"solb",                  "\xe2\xa7\x84"            }, /* ⧄ [SQUARED RISING DIAGONAL SLASH]*/
	{"solbar",                "\xe2\x8c\xbf"            }, /* ⌿ [APL FUNCTIONAL SYMBOL SLASH BAR]*/
	{"sopf",                  "\xf0\x9d\x95\xa4"        }, /* 𝕤 [MATHEMATICAL DOUBLE-STRUCK SMALL S]*/
	{"spades",                "\xe2\x99\xa0"            }, /* ♠ [BLACK SPADE SUIT]*/
	{"spadesuit",             "\xe2\x99\xa0"            }, /* ♠ [BLACK SPADE SUIT]*/
	{"spar",                  "\xe2\x88\xa5"            }, /* ∥ [PARALLEL TO]*/
	{"sqcap",                 "\xe2\x8a\x93"            }, /* ⊓ [SQUARE CAP]*/
	{"sqcaps",                "\xe2\x8a\x93\xef\xb8\x80"}, /* ⊓︀ [SQUARE CAP with serifs]*/
	{"sqcup",                 "\xe2\x8a\x94"            }, /* ⊔ [SQUARE CUP]*/
	{"sqcups",                "\xe2\x8a\x94\xef\xb8\x80"}, /* ⊔︀ [SQUARE CUP with serifs]*/
	{"sqsub",                 "\xe2\x8a\x8f"            }, /* ⊏ [SQUARE IMAGE OF]*/
	{"sqsube",                "\xe2\x8a\x91"            }, /* ⊑ [SQUARE IMAGE OF OR EQUAL TO]*/
	{"sqsubset",              "\xe2\x8a\x8f"            }, /* ⊏ [SQUARE IMAGE OF]*/
	{"sqsubseteq",            "\xe2\x8a\x91"            }, /* ⊑ [SQUARE IMAGE OF OR EQUAL TO]*/
	{"sqsup",                 "\xe2\x8a\x90"            }, /* ⊐ [SQUARE ORIGINAL OF]*/
	{"sqsupe",                "\xe2\x8a\x92"            }, /* ⊒ [SQUARE ORIGINAL OF OR EQUAL TO]*/
	{"sqsupset",              "\xe2\x8a\x90"            }, /* ⊐ [SQUARE ORIGINAL OF]*/
	{"sqsupseteq",            "\xe2\x8a\x92"            }, /* ⊒ [SQUARE ORIGINAL OF OR EQUAL TO]*/
	{"squ",                   "\xe2\x96\xa1"            }, /* □ [WHITE SQUARE]*/
	{"square",                "\xe2\x96\xa1"            }, /* □ [WHITE SQUARE]*/
	{"squarf",                "\xe2\x96\xaa"            }, /* ▪ [BLACK SMALL SQUARE]*/
	{"squf",                  "\xe2\x96\xaa"            }, /* ▪ [BLACK SMALL SQUARE]*/
	{"srarr",                 "\xe2\x86\x92"            }, /* → [RIGHTWARDS ARROW]*/
	{"sscr",                  "\xf0\x9d\x93\x88"        }, /* 𝓈 [MATHEMATICAL SCRIPT SMALL S]*/
	{"ssetmn",                "\xe2\x88\x96"            }, /* ∖ [SET MINUS]*/
	{"ssmile",                "\xe2\x8c\xa3"            }, /* ⌣ [SMILE]*/
	{"sstarf",                "\xe2\x8b\x86"            }, /* ⋆ [STAR OPERATOR]*/
	{"star",                  "\xe2\x98\x86"            }, /* ☆ [WHITE STAR]*/
	{"starf",                 "\xe2\x98\x85"            }, /* ★ [BLACK STAR]*/
	{"straightepsilon",       "\xcf\xb5"                }, /* ϵ [GREEK LUNATE EPSILON SYMBOL]*/
	{"straightphi",           "\xcf\x95"                }, /* ϕ [GREEK PHI SYMBOL]*/
	{"strns",                 "\xc2\xaf"                }, /* ¯ [MACRON]*/
	{"sub",                   "\xe2\x8a\x82"            }, /* ⊂ [SUBSET OF]*/
	{"subE",                  "\xe2\xab\x85"            }, /* ⫅ [SUBSET OF ABOVE EQUALS SIGN]*/
	{"subdot",                "\xe2\xaa\xbd"            }, /* ⪽ [SUBSET WITH DOT]*/
	{"sube",                  "\xe2\x8a\x86"            }, /* ⊆ [SUBSET OF OR EQUAL TO]*/
	{"subedot",               "\xe2\xab\x83"            }, /* ⫃ [SUBSET OF OR EQUAL TO WITH DOT ABOVE]*/
	{"submult",               "\xe2\xab\x81"            }, /* ⫁ [SUBSET WITH MULTIPLICATION SIGN BELOW]*/
	{"subnE",                 "\xe2\xab\x8b"            }, /* ⫋ [SUBSET OF ABOVE NOT EQUAL TO]*/
	{"subne",                 "\xe2\x8a\x8a"            }, /* ⊊ [SUBSET OF WITH NOT EQUAL TO]*/
	{"subplus",               "\xe2\xaa\xbf"            }, /* ⪿ [SUBSET WITH PLUS SIGN BELOW]*/
	{"subrarr",               "\xe2\xa5\xb9"            }, /* ⥹ [SUBSET ABOVE RIGHTWARDS ARROW]*/
	{"subset",                "\xe2\x8a\x82"            }, /* ⊂ [SUBSET OF]*/
	{"subseteq",              "\xe2\x8a\x86"            }, /* ⊆ [SUBSET OF OR EQUAL TO]*/
	{"subseteqq",             "\xe2\xab\x85"            }, /* ⫅ [SUBSET OF ABOVE EQUALS SIGN]*/
	{"subsetneq",             "\xe2\x8a\x8a"            }, /* ⊊ [SUBSET OF WITH NOT EQUAL TO]*/
	{"subsetneqq",            "\xe2\xab\x8b"            }, /* ⫋ [SUBSET OF ABOVE NOT EQUAL TO]*/
	{"subsim",                "\xe2\xab\x87"            }, /* ⫇ [SUBSET OF ABOVE TILDE OPERATOR]*/
	{"subsub",                "\xe2\xab\x95"            }, /* ⫕ [SUBSET ABOVE SUBSET]*/
	{"subsup",                "\xe2\xab\x93"            }, /* ⫓ [SUBSET ABOVE SUPERSET]*/
	{"succ",                  "\xe2\x89\xbb"            }, /* ≻ [SUCCEEDS]*/
	{"succapprox",            "\xe2\xaa\xb8"            }, /* ⪸ [SUCCEEDS ABOVE ALMOST EQUAL TO]*/
	{"succcurlyeq",           "\xe2\x89\xbd"            }, /* ≽ [SUCCEEDS OR EQUAL TO]*/
	{"succeq",                "\xe2\xaa\xb0"            }, /* ⪰ [SUCCEEDS ABOVE SINGLE-LINE EQUALS SIGN]*/
	{"succnapprox",           "\xe2\xaa\xba"            }, /* ⪺ [SUCCEEDS ABOVE NOT ALMOST EQUAL TO]*/
	{"succneqq",              "\xe2\xaa\xb6"            }, /* ⪶ [SUCCEEDS ABOVE NOT EQUAL TO]*/
	{"succnsim",              "\xe2\x8b\xa9"            }, /* ⋩ [SUCCEEDS BUT NOT EQUIVALENT TO]*/
	{"succsim",               "\xe2\x89\xbf"            }, /* ≿ [SUCCEEDS OR EQUIVALENT TO]*/
	{"sum",                   "\xe2\x88\x91"            }, /* ∑ [N-ARY SUMMATION]*/
	{"sung",                  "\xe2\x99\xaa"            }, /* ♪ [EIGHTH NOTE]*/
	{"sup",                   "\xe2\x8a\x83"            }, /* ⊃ [SUPERSET OF]*/
	{"sup1",                  "\xc2\xb9"                }, /* ¹ [SUPERSCRIPT ONE]*/
	{"sup2",                  "\xc2\xb2"                }, /* ² [SUPERSCRIPT TWO]*/
	{"sup3",                  "\xc2\xb3"                }, /* ³ [SUPERSCRIPT THREE]*/
	{"supE",                  "\xe2\xab\x86"            }, /* ⫆ [SUPERSET OF ABOVE EQUALS SIGN]*/
	{"supdot",                "\xe2\xaa\xbe"            }, /* ⪾ [SUPERSET WITH DOT]*/
	{"supdsub",               "\xe2\xab\x98"            }, /* ⫘ [SUPERSET BESIDE AND JOINED BY DASH WITH SUBSET]*/
	{"supe",                  "\xe2\x8a\x87"            }, /* ⊇ [SUPERSET OF OR EQUAL TO]*/
	{"supedot",               "\xe2\xab\x84"            }, /* ⫄ [SUPERSET OF OR EQUAL TO WITH DOT ABOVE]*/
	{"suphsol",               "\xe2\x8a\x83\x2f"        }, /* ⊃/ [SUPERSET OF, SOLIDUS]*/
	{"suphsub",               "\xe2\xab\x97"            }, /* ⫗ [SUPERSET BESIDE SUBSET]*/
	{"suplarr",               "\xe2\xa5\xbb"            }, /* ⥻ [SUPERSET ABOVE LEFTWARDS ARROW]*/
	{"supmult",               "\xe2\xab\x82"            }, /* ⫂ [SUPERSET WITH MULTIPLICATION SIGN BELOW]*/
	{"supnE",                 "\xe2\xab\x8c"            }, /* ⫌ [SUPERSET OF ABOVE NOT EQUAL TO]*/
	{"supne",                 "\xe2\x8a\x8b"            }, /* ⊋ [SUPERSET OF WITH NOT EQUAL TO]*/
	{"supplus",               "\xe2\xab\x80"            }, /* ⫀ [SUPERSET WITH PLUS SIGN BELOW]*/
	{"supset",                "\xe2\x8a\x83"            }, /* ⊃ [SUPERSET OF]*/
	{"supseteq",              "\xe2\x8a\x87"            }, /* ⊇ [SUPERSET OF OR EQUAL TO]*/
	{"supseteqq",             "\xe2\xab\x86"            }, /* ⫆ [SUPERSET OF ABOVE EQUALS SIGN]*/
	{"supsetneq",             "\xe2\x8a\x8b"            }, /* ⊋ [SUPERSET OF WITH NOT EQUAL TO]*/
	{"supsetneqq",            "\xe2\xab\x8c"            }, /* ⫌ [SUPERSET OF ABOVE NOT EQUAL TO]*/
	{"supsim",                "\xe2\xab\x88"            }, /* ⫈ [SUPERSET OF ABOVE TILDE OPERATOR]*/
	{"supsub",                "\xe2\xab\x94"            }, /* ⫔ [SUPERSET ABOVE SUBSET]*/
	{"supsup",                "\xe2\xab\x96"            }, /* ⫖ [SUPERSET ABOVE SUPERSET]*/
	{"swArr",                 "\xe2\x87\x99"            }, /* ⇙ [SOUTH WEST DOUBLE ARROW]*/
	{"swarhk",                "\xe2\xa4\xa6"            }, /* ⤦ [SOUTH WEST ARROW WITH HOOK]*/
	{"swarr",                 "\xe2\x86\x99"            }, /* ↙ [SOUTH WEST ARROW]*/
	{"swarrow",               "\xe2\x86\x99"            }, /* ↙ [SOUTH WEST ARROW]*/
	{"swnwar",                "\xe2\xa4\xaa"            }, /* ⤪ [SOUTH WEST ARROW AND NORTH WEST ARROW]*/
	{"szlig",                 "\xc3\x9f"                }, /* ß [LATIN SMALL LETTER SHARP S]*/
	{"target",                "\xe2\x8c\x96"            }, /* ⌖ [POSITION INDICATOR]*/
	{"tau",                   "\xcf\x84"                }, /* τ [GREEK SMALL LETTER TAU]*/
	{"tbrk",                  "\xe2\x8e\xb4"            }, /* ⎴ [TOP SQUARE BRACKET]*/
	{"tcaron",                "\xc5\xa5"                }, /* ť [LATIN SMALL LETTER T WITH CARON]*/
	{"tcedil",                "\xc5\xa3"                }, /* ţ [LATIN SMALL LETTER T WITH CEDILLA]*/
	{"tcy",                   "\xd1\x82"                }, /* т [CYRILLIC SMALL LETTER TE]*/
	{"tdot",                  "\xe2\x83\x9b"            }, /* ⃛ [COMBINING THREE DOTS ABOVE]*/
	{"telrec",                "\xe2\x8c\x95"            }, /* ⌕ [TELEPHONE RECORDER]*/
	{"tfr",                   "\xf0\x9d\x94\xb1"        }, /* 𝔱 [MATHEMATICAL FRAKTUR SMALL T]*/
	{"there4",                "\xe2\x88\xb4"            }, /* ∴ [THEREFORE]*/
	{"therefore",             "\xe2\x88\xb4"            }, /* ∴ [THEREFORE]*/
	{"theta",                 "\xce\xb8"                }, /* θ [GREEK SMALL LETTER THETA]*/
	{"thetav",                "\xcf\x91"                }, /* ϑ [GREEK THETA SYMBOL]*/
	{"thickapprox",           "\xe2\x89\x88"            }, /* ≈ [ALMOST EQUAL TO]*/
	{"thicksim",              "\xe2\x88\xbc"            }, /* ∼ [TILDE OPERATOR]*/
	{"thinsp",                "\xe2\x80\x89"            }, /*   [THIN SPACE]*/
	{"thkap",                 "\xe2\x89\x88"            }, /* ≈ [ALMOST EQUAL TO]*/
	{"thksim",                "\xe2\x88\xbc"            }, /* ∼ [TILDE OPERATOR]*/
	{"thorn",                 "\xc3\xbe"                }, /* þ [LATIN SMALL LETTER THORN]*/
	{"tilde",                 "\xcb\x9c"                }, /* ˜ [SMALL TILDE]*/
	{"times",                 "\xc3\x97"                }, /* × [MULTIPLICATION SIGN]*/
	{"timesb",                "\xe2\x8a\xa0"            }, /* ⊠ [SQUARED TIMES]*/
	{"timesbar",              "\xe2\xa8\xb1"            }, /* ⨱ [MULTIPLICATION SIGN WITH UNDERBAR]*/
	{"timesd",                "\xe2\xa8\xb0"            }, /* ⨰ [MULTIPLICATION SIGN WITH DOT ABOVE]*/
	{"tint",                  "\xe2\x88\xad"            }, /* ∭ [TRIPLE INTEGRAL]*/
	{"toea",                  "\xe2\xa4\xa8"            }, /* ⤨ [NORTH EAST ARROW AND SOUTH EAST ARROW]*/
	{"top",                   "\xe2\x8a\xa4"            }, /* ⊤ [DOWN TACK]*/
	{"topbot",                "\xe2\x8c\xb6"            }, /* ⌶ [APL FUNCTIONAL SYMBOL I-BEAM]*/
	{"topcir",                "\xe2\xab\xb1"            }, /* ⫱ [DOWN TACK WITH CIRCLE BELOW]*/
	{"topf",                  "\xf0\x9d\x95\xa5"        }, /* 𝕥 [MATHEMATICAL DOUBLE-STRUCK SMALL T]*/
	{"topfork",               "\xe2\xab\x9a"            }, /* ⫚ [PITCHFORK WITH TEE TOP]*/
	{"tosa",                  "\xe2\xa4\xa9"            }, /* ⤩ [SOUTH EAST ARROW AND SOUTH WEST ARROW]*/
	{"tprime",                "\xe2\x80\xb4"            }, /* ‴ [TRIPLE PRIME]*/
	{"trade",                 "\xe2\x84\xa2"            }, /* ™ [TRADE MARK SIGN]*/
	{"triangle",              "\xe2\x96\xb5"            }, /* ▵ [WHITE UP-POINTING SMALL TRIANGLE]*/
	{"triangledown",          "\xe2\x96\xbf"            }, /* ▿ [WHITE DOWN-POINTING SMALL TRIANGLE]*/
	{"triangleleft",          "\xe2\x97\x83"            }, /* ◃ [WHITE LEFT-POINTING SMALL TRIANGLE]*/
	{"trianglelefteq",        "\xe2\x8a\xb4"            }, /* ⊴ [NORMAL SUBGROUP OF OR EQUAL TO]*/
	{"triangleq",             "\xe2\x89\x9c"            }, /* ≜ [DELTA EQUAL TO]*/
	{"triangleright",         "\xe2\x96\xb9"            }, /* ▹ [WHITE RIGHT-POINTING SMALL TRIANGLE]*/
	{"trianglerighteq",       "\xe2\x8a\xb5"            }, /* ⊵ [CONTAINS AS NORMAL SUBGROUP OR EQUAL TO]*/
	{"tridot",                "\xe2\x97\xac"            }, /* ◬ [WHITE UP-POINTING TRIANGLE WITH DOT]*/
	{"trie",                  "\xe2\x89\x9c"            }, /* ≜ [DELTA EQUAL TO]*/
	{"triminus",              "\xe2\xa8\xba"            }, /* ⨺ [MINUS SIGN IN TRIANGLE]*/
	{"triplus",               "\xe2\xa8\xb9"            }, /* ⨹ [PLUS SIGN IN TRIANGLE]*/
	{"trisb",                 "\xe2\xa7\x8d"            }, /* ⧍ [TRIANGLE WITH SERIFS AT BOTTOM]*/
	{"tritime",               "\xe2\xa8\xbb"            }, /* ⨻ [MULTIPLICATION SIGN IN TRIANGLE]*/
	{"trpezium",              "\xef\xbf\xbd"            }, /* � [REPLACEMENT CHARACTER]*/
	{"tscr",                  "\xf0\x9d\x93\x89"        }, /* 𝓉 [MATHEMATICAL SCRIPT SMALL T]*/
	{"tscy",                  "\xd1\x86"                }, /* ц [CYRILLIC SMALL LETTER TSE]*/
	{"tshcy",                 "\xd1\x9b"                }, /* ћ [CYRILLIC SMALL LETTER TSHE]*/
	{"tstrok",                "\xc5\xa7"                }, /* ŧ [LATIN SMALL LETTER T WITH STROKE]*/
	{"twixt",                 "\xe2\x89\xac"            }, /* ≬ [BETWEEN]*/
	{"twoheadleftarrow",      "\xe2\x86\x9e"            }, /* ↞ [LEFTWARDS TWO HEADED ARROW]*/
	{"twoheadrightarrow",     "\xe2\x86\xa0"            }, /* ↠ [RIGHTWARDS TWO HEADED ARROW]*/
	{"uArr",                  "\xe2\x87\x91"            }, /* ⇑ [UPWARDS DOUBLE ARROW]*/
	{"uHar",                  "\xe2\xa5\xa3"            }, /* ⥣ [UPWARDS HARPOON WITH BARB LEFT BESIDE UPWARDS HARPOON WITH BARB RIGHT]*/
	{"uacute",                "\xc3\xba"                }, /* ú [LATIN SMALL LETTER U WITH ACUTE]*/
	{"uarr",                  "\xe2\x86\x91"            }, /* ↑ [UPWARDS ARROW]*/
	{"ubrcy",                 "\xd1\x9e"                }, /* ў [CYRILLIC SMALL LETTER SHORT U]*/
	{"ubreve",                "\xc5\xad"                }, /* ŭ [LATIN SMALL LETTER U WITH BREVE]*/
	{"ucirc",                 "\xc3\xbb"                }, /* û [LATIN SMALL LETTER U WITH CIRCUMFLEX]*/
	{"ucy",                   "\xd1\x83"                }, /* у [CYRILLIC SMALL LETTER U]*/
	{"udarr",                 "\xe2\x87\x85"            }, /* ⇅ [UPWARDS ARROW LEFTWARDS OF DOWNWARDS ARROW]*/
	{"udblac",                "\xc5\xb1"                }, /* ű [LATIN SMALL LETTER U WITH DOUBLE ACUTE]*/
	{"udhar",                 "\xe2\xa5\xae"            }, /* ⥮ [UPWARDS HARPOON WITH BARB LEFT BESIDE DOWNWARDS HARPOON WITH BARB RIGHT]*/
	{"ufisht",                "\xe2\xa5\xbe"            }, /* ⥾ [UP FISH TAIL]*/
	{"ufr",                   "\xf0\x9d\x94\xb2"        }, /* 𝔲 [MATHEMATICAL FRAKTUR SMALL U]*/
	{"ugrave",                "\xc3\xb9"                }, /* ù [LATIN SMALL LETTER U WITH GRAVE]*/
	{"uharl",                 "\xe2\x86\xbf"            }, /* ↿ [UPWARDS HARPOON WITH BARB LEFTWARDS]*/
	{"uharr",                 "\xe2\x86\xbe"            }, /* ↾ [UPWARDS HARPOON WITH BARB RIGHTWARDS]*/
	{"uhblk",                 "\xe2\x96\x80"            }, /* ▀ [UPPER HALF BLOCK]*/
	{"ulcorn",                "\xe2\x8c\x9c"            }, /* ⌜ [TOP LEFT CORNER]*/
	{"ulcorner",              "\xe2\x8c\x9c"            }, /* ⌜ [TOP LEFT CORNER]*/
	{"ulcrop",                "\xe2\x8c\x8f"            }, /* ⌏ [TOP LEFT CROP]*/
	{"ultri",                 "\xe2\x97\xb8"            }, /* ◸ [UPPER LEFT TRIANGLE]*/
	{"umacr",                 "\xc5\xab"                }, /* ū [LATIN SMALL LETTER U WITH MACRON]*/
	{"uml",                   "\xc2\xa8"                }, /* ¨ [DIAERESIS]*/
	{"uogon",                 "\xc5\xb3"                }, /* ų [LATIN SMALL LETTER U WITH OGONEK]*/
	{"uopf",                  "\xf0\x9d\x95\xa6"        }, /* 𝕦 [MATHEMATICAL DOUBLE-STRUCK SMALL U]*/
	{"uparrow",               "\xe2\x86\x91"            }, /* ↑ [UPWARDS ARROW]*/
	{"updownarrow",           "\xe2\x86\x95"            }, /* ↕ [UP DOWN ARROW]*/
	{"upharpoonleft",         "\xe2\x86\xbf"            }, /* ↿ [UPWARDS HARPOON WITH BARB LEFTWARDS]*/
	{"upharpoonright",        "\xe2\x86\xbe"            }, /* ↾ [UPWARDS HARPOON WITH BARB RIGHTWARDS]*/
	{"uplus",                 "\xe2\x8a\x8e"            }, /* ⊎ [MULTISET UNION]*/
	{"upsi",                  "\xcf\x85"                }, /* υ [GREEK SMALL LETTER UPSILON]*/
	{"upsilon",               "\xcf\x85"                }, /* υ [GREEK SMALL LETTER UPSILON]*/
	{"upuparrows",            "\xe2\x87\x88"            }, /* ⇈ [UPWARDS PAIRED ARROWS]*/
	{"urcorn",                "\xe2\x8c\x9d"            }, /* ⌝ [TOP RIGHT CORNER]*/
	{"urcorner",              "\xe2\x8c\x9d"            }, /* ⌝ [TOP RIGHT CORNER]*/
	{"urcrop",                "\xe2\x8c\x8e"            }, /* ⌎ [TOP RIGHT CROP]*/
	{"uring",                 "\xc5\xaf"                }, /* ů [LATIN SMALL LETTER U WITH RING ABOVE]*/
	{"urtri",                 "\xe2\x97\xb9"            }, /* ◹ [UPPER RIGHT TRIANGLE]*/
	{"uscr",                  "\xf0\x9d\x93\x8a"        }, /* 𝓊 [MATHEMATICAL SCRIPT SMALL U]*/
	{"utdot",                 "\xe2\x8b\xb0"            }, /* ⋰ [UP RIGHT DIAGONAL ELLIPSIS]*/
	{"utilde",                "\xc5\xa9"                }, /* ũ [LATIN SMALL LETTER U WITH TILDE]*/
	{"utri",                  "\xe2\x96\xb5"            }, /* ▵ [WHITE UP-POINTING SMALL TRIANGLE]*/
	{"utrif",                 "\xe2\x96\xb4"            }, /* ▴ [BLACK UP-POINTING SMALL TRIANGLE]*/
	{"uuarr",                 "\xe2\x87\x88"            }, /* ⇈ [UPWARDS PAIRED ARROWS]*/
	{"uuml",                  "\xc3\xbc"                }, /* ü [LATIN SMALL LETTER U WITH DIAERESIS]*/
	{"uwangle",               "\xe2\xa6\xa7"            }, /* ⦧ [OBLIQUE ANGLE OPENING DOWN]*/
	{"vArr",                  "\xe2\x87\x95"            }, /* ⇕ [UP DOWN DOUBLE ARROW]*/
	{"vBar",                  "\xe2\xab\xa8"            }, /* ⫨ [SHORT UP TACK WITH UNDERBAR]*/
	{"vBarv",                 "\xe2\xab\xa9"            }, /* ⫩ [SHORT UP TACK ABOVE SHORT DOWN TACK]*/
	{"vDash",                 "\xe2\x8a\xa8"            }, /* ⊨ [TRUE]*/
	{"vangrt",                "\xe2\xa6\x9c"            }, /* ⦜ [RIGHT ANGLE VARIANT WITH SQUARE]*/
	{"varepsilon",            "\xce\xb5"                }, /* ε [GREEK SMALL LETTER EPSILON]*/
	{"varkappa",              "\xcf\xb0"                }, /* ϰ [GREEK KAPPA SYMBOL]*/
	{"varnothing",            "\xe2\x88\x85"            }, /* ∅ [EMPTY SET]*/
	{"varphi",                "\xcf\x86"                }, /* φ [GREEK SMALL LETTER PHI]*/
	{"varpi",                 "\xcf\x96"                }, /* ϖ [GREEK PI SYMBOL]*/
	{"varpropto",             "\xe2\x88\x9d"            }, /* ∝ [PROPORTIONAL TO]*/
	{"varr",                  "\xe2\x86\x95"            }, /* ↕ [UP DOWN ARROW]*/
	{"varrho",                "\xcf\xb1"                }, /* ϱ [GREEK RHO SYMBOL]*/
	{"varsigma",              "\xcf\x82"                }, /* ς [GREEK SMALL LETTER FINAL SIGMA]*/
	{"varsubsetneq",          "\xe2\x8a\x8a\xef\xb8\x80"}, /* ⊊︀ [SUBSET OF WITH NOT EQUAL TO - variant with stroke through bottom members]*/
	{"varsubsetneqq",         "\xe2\xab\x8b\xef\xb8\x80"}, /* ⫋︀ [SUBSET OF ABOVE NOT EQUAL TO - variant with stroke through bottom members]*/
	{"varsupsetneq",          "\xe2\x8a\x8b\xef\xb8\x80"}, /* ⊋︀ [SUPERSET OF WITH NOT EQUAL TO - variant with stroke through bottom members]*/
	{"varsupsetneqq",         "\xe2\xab\x8c\xef\xb8\x80"}, /* ⫌︀ [SUPERSET OF ABOVE NOT EQUAL TO - variant with stroke through bottom members]*/
	{"vartheta",              "\xcf\x91"                }, /* ϑ [GREEK THETA SYMBOL]*/
	{"vartriangleleft",       "\xe2\x8a\xb2"            }, /* ⊲ [NORMAL SUBGROUP OF]*/
	{"vartriangleright",      "\xe2\x8a\xb3"            }, /* ⊳ [CONTAINS AS NORMAL SUBGROUP]*/
	{"vcy",                   "\xd0\xb2"                }, /* в [CYRILLIC SMALL LETTER VE]*/
	{"vdash",                 "\xe2\x8a\xa2"            }, /* ⊢ [RIGHT TACK]*/
	{"vee",                   "\xe2\x88\xa8"            }, /* ∨ [LOGICAL OR]*/
	{"veebar",                "\xe2\x8a\xbb"            }, /* ⊻ [XOR]*/
	{"veeeq",                 "\xe2\x89\x9a"            }, /* ≚ [EQUIANGULAR TO]*/
	{"vellip",                "\xe2\x8b\xae"            }, /* ⋮ [VERTICAL ELLIPSIS]*/
	{"verbar",                "\x7c"                    }, /* | [VERTICAL LINE]*/
	{"vert",                  "\x7c"                    }, /* | [VERTICAL LINE]*/
	{"vfr",                   "\xf0\x9d\x94\xb3"        }, /* 𝔳 [MATHEMATICAL FRAKTUR SMALL V]*/
	{"vltri",                 "\xe2\x8a\xb2"            }, /* ⊲ [NORMAL SUBGROUP OF]*/
	{"vnsub",                 "\xe2\x8a\x82\xe2\x83\x92"}, /* ⊂⃒ [SUBSET OF with vertical line]*/
	{"vnsup",                 "\xe2\x8a\x83\xe2\x83\x92"}, /* ⊃⃒ [SUPERSET OF with vertical line]*/
	{"vopf",                  "\xf0\x9d\x95\xa7"        }, /* 𝕧 [MATHEMATICAL DOUBLE-STRUCK SMALL V]*/
	{"vprop",                 "\xe2\x88\x9d"            }, /* ∝ [PROPORTIONAL TO]*/
	{"vrtri",                 "\xe2\x8a\xb3"            }, /* ⊳ [CONTAINS AS NORMAL SUBGROUP]*/
	{"vscr",                  "\xf0\x9d\x93\x8b"        }, /* 𝓋 [MATHEMATICAL SCRIPT SMALL V]*/
	{"vsubnE",                "\xe2\xab\x8b\xef\xb8\x80"}, /* ⫋︀ [SUBSET OF ABOVE NOT EQUAL TO - variant with stroke through bottom members]*/
	{"vsubne",                "\xe2\x8a\x8a\xef\xb8\x80"}, /* ⊊︀ [SUBSET OF WITH NOT EQUAL TO - variant with stroke through bottom members]*/
	{"vsupnE",                "\xe2\xab\x8c\xef\xb8\x80"}, /* ⫌︀ [SUPERSET OF ABOVE NOT EQUAL TO - variant with stroke through bottom members]*/
	{"vsupne",                "\xe2\x8a\x8b\xef\xb8\x80"}, /* ⊋︀ [SUPERSET OF WITH NOT EQUAL TO - variant with stroke through bottom members]*/
	{"vzigzag",               "\xe2\xa6\x9a"            }, /* ⦚ [VERTICAL ZIGZAG LINE]*/
	{"wcirc",                 "\xc5\xb5"                }, /* ŵ [LATIN SMALL LETTER W WITH CIRCUMFLEX]*/
	{"wedbar",                "\xe2\xa9\x9f"            }, /* ⩟ [LOGICAL AND WITH UNDERBAR]*/
	{"wedge",                 "\xe2\x88\xa7"            }, /* ∧ [LOGICAL AND]*/
	{"wedgeq",                "\xe2\x89\x99"            }, /* ≙ [ESTIMATES]*/
	{"weierp",                "\xe2\x84\x98"            }, /* ℘ [SCRIPT CAPITAL P]*/
	{"wfr",                   "\xf0\x9d\x94\xb4"        }, /* 𝔴 [MATHEMATICAL FRAKTUR SMALL W]*/
	{"wopf",                  "\xf0\x9d\x95\xa8"        }, /* 𝕨 [MATHEMATICAL DOUBLE-STRUCK SMALL W]*/
	{"wp",                    "\xe2\x84\x98"            }, /* ℘ [SCRIPT CAPITAL P]*/
	{"wr",                    "\xe2\x89\x80"            }, /* ≀ [WREATH PRODUCT]*/
	{"wreath",                "\xe2\x89\x80"            }, /* ≀ [WREATH PRODUCT]*/
	{"wscr",                  "\xf0\x9d\x93\x8c"        }, /* 𝓌 [MATHEMATICAL SCRIPT SMALL W]*/
	{"xcap",                  "\xe2\x8b\x82"            }, /* ⋂ [N-ARY INTERSECTION]*/
	{"xcirc",                 "\xe2\x97\xaf"            }, /* ◯ [LARGE CIRCLE]*/
	{"xcup",                  "\xe2\x8b\x83"            }, /* ⋃ [N-ARY UNION]*/
	{"xdtri",                 "\xe2\x96\xbd"            }, /* ▽ [WHITE DOWN-POINTING TRIANGLE]*/
	{"xfr",                   "\xf0\x9d\x94\xb5"        }, /* 𝔵 [MATHEMATICAL FRAKTUR SMALL X]*/
	{"xhArr",                 "\xe2\x9f\xba"            }, /* ⟺ [LONG LEFT RIGHT DOUBLE ARROW]*/
	{"xharr",                 "\xe2\x9f\xb7"            }, /* ⟷ [LONG LEFT RIGHT ARROW]*/
	{"xi",                    "\xce\xbe"                }, /* ξ [GREEK SMALL LETTER XI]*/
	{"xlArr",                 "\xe2\x9f\xb8"            }, /* ⟸ [LONG LEFTWARDS DOUBLE ARROW]*/
	{"xlarr",                 "\xe2\x9f\xb5"            }, /* ⟵ [LONG LEFTWARDS ARROW]*/
	{"xmap",                  "\xe2\x9f\xbc"            }, /* ⟼ [LONG RIGHTWARDS ARROW FROM BAR]*/
	{"xnis",                  "\xe2\x8b\xbb"            }, /* ⋻ [CONTAINS WITH VERTICAL BAR AT END OF HORIZONTAL STROKE]*/
	{"xodot",                 "\xe2\xa8\x80"            }, /* ⨀ [N-ARY CIRCLED DOT OPERATOR]*/
	{"xopf",                  "\xf0\x9d\x95\xa9"        }, /* 𝕩 [MATHEMATICAL DOUBLE-STRUCK SMALL X]*/
	{"xoplus",                "\xe2\xa8\x81"            }, /* ⨁ [N-ARY CIRCLED PLUS OPERATOR]*/
	{"xotime",                "\xe2\xa8\x82"            }, /* ⨂ [N-ARY CIRCLED TIMES OPERATOR]*/
	{"xrArr",                 "\xe2\x9f\xb9"            }, /* ⟹ [LONG RIGHTWARDS DOUBLE ARROW]*/
	{"xrarr",                 "\xe2\x9f\xb6"            }, /* ⟶ [LONG RIGHTWARDS ARROW]*/
	{"xscr",                  "\xf0\x9d\x93\x8d"        }, /* 𝓍 [MATHEMATICAL SCRIPT SMALL X]*/
	{"xsqcup",                "\xe2\xa8\x86"            }, /* ⨆ [N-ARY SQUARE UNION OPERATOR]*/
	{"xuplus",                "\xe2\xa8\x84"            }, /* ⨄ [N-ARY UNION OPERATOR WITH PLUS]*/
	{"xutri",                 "\xe2\x96\xb3"            }, /* △ [WHITE UP-POINTING TRIANGLE]*/
	{"xvee",                  "\xe2\x8b\x81"            }, /* ⋁ [N-ARY LOGICAL OR]*/
	{"xwedge",                "\xe2\x8b\x80"            }, /* ⋀ [N-ARY LOGICAL AND]*/
	{"yacute",                "\xc3\xbd"                }, /* ý [LATIN SMALL LETTER Y WITH ACUTE]*/
	{"yacy",                  "\xd1\x8f"                }, /* я [CYRILLIC SMALL LETTER YA]*/
	{"ycirc",                 "\xc5\xb7"                }, /* ŷ [LATIN SMALL LETTER Y WITH CIRCUMFLEX]*/
	{"ycy",                   "\xd1\x8b"                }, /* ы [CYRILLIC SMALL LETTER YERU]*/
	{"yen",                   "\xc2\xa5"                }, /* ¥ [YEN SIGN]*/
	{"yfr",                   "\xf0\x9d\x94\xb6"        }, /* 𝔶 [MATHEMATICAL FRAKTUR SMALL Y]*/
	{"yicy",                  "\xd1\x97"                }, /* ї [CYRILLIC SMALL LETTER YI]*/
	{"yopf",                  "\xf0\x9d\x95\xaa"        }, /* 𝕪 [MATHEMATICAL DOUBLE-STRUCK SMALL Y]*/
	{"yscr",                  "\xf0\x9d\x93\x8e"        }, /* 𝓎 [MATHEMATICAL SCRIPT SMALL Y]*/
	{"yucy",                  "\xd1\x8e"                }, /* ю [CYRILLIC SMALL LETTER YU]*/
	{"yuml",                  "\xc3\xbf"                }, /* ÿ [LATIN SMALL LETTER Y WITH DIAERESIS]*/
	{"zacute",                "\xc5\xba"                }, /* ź [LATIN SMALL LETTER Z WITH ACUTE]*/
	{"zcaron",                "\xc5\xbe"                }, /* ž [LATIN SMALL LETTER Z WITH CARON]*/
	{"zcy",                   "\xd0\xb7"                }, /* з [CYRILLIC SMALL LETTER ZE]*/
	{"zdot",                  "\xc5\xbc"                }, /* ż [LATIN SMALL LETTER Z WITH DOT ABOVE]*/
	{"zeetrf",                "\xe2\x84\xa8"            }, /* ℨ [BLACK-LETTER CAPITAL Z]*/
	{"zeta",                  "\xce\xb6"                }, /* ζ [GREEK SMALL LETTER ZETA]*/
	{"zfr",                   "\xf0\x9d\x94\xb7"        }, /* 𝔷 [MATHEMATICAL FRAKTUR SMALL Z]*/
	{"zhcy",                  "\xd0\xb6"                }, /* ж [CYRILLIC SMALL LETTER ZHE]*/
	{"zigrarr",               "\xe2\x87\x9d"            }, /* ⇝ [RIGHTWARDS SQUIGGLE ARROW]*/
	{"zopf",                  "\xf0\x9d\x95\xab"        }, /* 𝕫 [MATHEMATICAL DOUBLE-STRUCK SMALL Z]*/
	{"zscr",                  "\xf0\x9d\x93\x8f"        }  /* 𝓏 [MATHEMATICAL SCRIPT SMALL Z]*/
};

static GHashTable *
lsm_dom_get_entities (void)
{
	static GHashTable *entity_hash = NULL;
	int i;

	if (entity_hash != NULL)
		return entity_hash;

	entity_hash = g_hash_table_new_full (g_str_hash, g_str_equal, NULL, NULL);

	for (i = 0; i < G_N_ELEMENTS (lsm_dom_entities); i++)
			g_hash_table_insert (entity_hash,
					     (char *) lsm_dom_entities[i].name,
					     (char *) lsm_dom_entities[i].utf8);

	return entity_hash;
}

const char *
lsm_dom_get_entity (const char *name)
{
	const char *utf8;

	utf8 = g_hash_table_lookup (lsm_dom_get_entities (), name);

	if (utf8 == NULL)
		return name;

	return utf8;
}
