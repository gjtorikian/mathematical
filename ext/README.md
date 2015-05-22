Lasem aims to be a C/Gobject based SVG/Mathml renderer and editor, supporting CSS
style sheets (only rendering is implemented for now). It uses cairo and pango as
it's rendering abstraction layer, and then support numerous output formats: xlib,
PNG, SVG, PDF, PS, EPS... It's written by Emmanuel Pacaud.

Lasem was added as a Git submodule of this project.

Some documentation can be found here:

* http://blogs.gnome.org/emmanuel/category/lasem/
* https://git.gnome.org/browse/lasem/

### Notes

* In *autogen.sh*, rename `libtoolize` to `glibtoolize` for OS X
* In *configure.ac*, remove `GTK_DOC_CHECK`
* Debug with `-d dom,measure,update,render,viewport`

* * *

mtex2MML transforms itex (a dialect of LaTeX) into MathML. mtex2MML is developed by
me, but was forked from an original project by Paul Gartside and Jacques Distler.
