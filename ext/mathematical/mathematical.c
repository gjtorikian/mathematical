 /****************************************************************************
 * Mathematical_rb Copyright(c) 2014, Garen J. Torikian, All rights reserved.
 * Originally Mimetex_rb Copyright(c) 2007, 32leaves.
 * --------------------------------------------------------------------------
 * This file is part of Mathematical_rb, which is free software. You may redistribute
 * and/or modify it under the terms of the GNU General Public License,
 * version 2 or later, as published by the Free Software Foundation.
 *      MATHEMATICAL_rb is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY, not even the implied warranty of MERCHANTABILITY.
 * See the GNU General Public License for specific details.
 *      By using Mathematical_rb, you warrant that you have read, understood and
 * agreed to these terms and conditions, and that you possess the legal
 * right and ability to enter into this agreement and to use Mathematical_rb
 * in accordance with it.
 *      Your Mathematical_rb distribution should contain a copy of the GNU General
 * Public License.  If not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA,
 * or point your browser to  http://www.gnu.org/licenses/gpl.html
 ****************************************************************************/

#include "ruby.h"
#include "mimetex.h"
#include <stdio.h>

#define MAXGIFSZ 131072
#define GIF 1

GLOBAL(raster,*bitmap_raster,NULL);

static VALUE rb_mMathematical;
static VALUE rb_cMathematicalProcess;
STATIC  FILE *msgfp;

int  MATHEMATICAL_GetPixel ( int x, int y ) {
  int  ipixel = y*bitmap_raster->width + x; /* pixel index for x,y-coords*/
  return (int)getlongbit(bitmap_raster->pixmap,ipixel); /*pixel = 0 or 1*/;
}

static VALUE MATHEMATICAL_init(VALUE self, int fontSize) {
  rb_iv_set(self, "@fontSize", fontSize);
  return self;
}

static VALUE MATHEMATICAL_process(VALUE self, VALUE rb_sLatexCode, VALUE rb_sFilename) {
  Check_Type (rb_sLatexCode, T_STRING);
  Check_Type (rb_sFilename, T_STRING);

  VALUE rb_sLatexCodeCopy;

  // Because plain duplication shares internal memory region.  You
  // have to call rb_str_modify() before modifying a string.
  rb_sLatexCodeCopy = rb_str_dup(rb_sLatexCode);
  rb_str_modify(rb_sLatexCodeCopy);

  int fontSize = FIX2INT(rb_iv_get(self, "@fontSize"));

  if(fontSize > 4 || fontSize < 1) fontSize = 2;

  subraster *sp = rasterize(StringValuePtr(rb_sLatexCodeCopy), fontSize);
  if(sp == NULL) rb_raise(rb_eRuntimeError, "Failed to rasterize");
  bitmap_raster = sp->image;
  char *gif_buffer = StringValuePtr(rb_sFilename);
  int gifSize = 0;
  int status = GIF_Create(gif_buffer, bitmap_raster->width, bitmap_raster->height, 2, 8);
  GIF_SetColor(1,0,0,0); /* foreground black if all 0 */

  if(status != 0) rb_raise(rb_eRuntimeError, "Could not create GIF image");
  GIF_SetTransparent(0);
  GIF_CompressImage(0, 0, -1, -1, MATHEMATICAL_GetPixel); /* emit gif */
  gifSize = GIF_Close();

  if(sp != NULL) delete_subraster(sp);  /* and free expression */

  return rb_str_new(gif_buffer, gifSize);
}

void Init_mathematical() {
  rb_mMathematical = rb_define_module("Mathematical");
  rb_cMathematicalProcess = rb_define_class_under(rb_mMathematical, "Process", rb_cObject);
  rb_define_method(rb_cMathematicalProcess, "initialize", MATHEMATICAL_init, 1);
  rb_define_method(rb_cMathematicalProcess, "process", MATHEMATICAL_process, 2);
}
