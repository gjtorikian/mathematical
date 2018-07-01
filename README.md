# Mathematical

Quickly convert math equations into beautiful SVGs (or PNGs/MathML).

[![Build Status](https://travis-ci.org/gjtorikian/mathematical.svg?branch=master)](https://travis-ci.org/gjtorikian/mathematical) [![Gem Version](https://badge.fury.io/rb/mathematical.svg)](http://badge.fury.io/rb/mathematical)

![Mathematical](https://i.imgur.com/JC7HT32.gif)

## Installation

Add this line to your application's Gemfile:

    gem 'mathematical'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install mathematical

**Note:** you'll probably need to run [`script/bootstrap`](script/bootstrap) to fetch all the necessary dependencies.

## Usage

The simplest way to do this is

``` ruby
require 'mathematical'

Mathematical.new.render(string_with_math)
```

`string_with_math` should just be a string of TeX math. The default delimiters are `$..$` for inline and `$$..$$` for display. These can be changed by options--see below.

The output will be a hash, with keys that depend on the format you want:

* If you asked for an SVG, you'll get:
  * `:width`: the width of the resulting image
  * `:height`: the height of the resulting image
  * `:data`: the actual string of SVG
* If you asked for a PNG, you'll get:
  * `:width`: the width of the resulting image
  * `:height`: the height of the resulting image
  * `:data`: the PNG data
* If you asked for MathML, you'll get:
  * `:data`: the MathML data
* If you pass in invalid TeX, you'll get:
  * `:data`: the original invalid TeX
  * `:exception`: the error class (with message)

**Note**: If you pass in invalid TeX, an error is not raised, but a message *is* printed to STDERR. It is the caller's responsibility to check for `:exception` and act on it.

`render` just converts a single equation. There are several other methods you can use:

* `filter`:  Given a string with a mix of TeX math and non-math elements, this returns a single string containing just the converted math elements.
* `text_filter`: Given a string with a mix of TeX math and non-math elements, this converts all the math and leaves the rest of the string unmodified.
* `strict_filter`:  Given a string with a mix of TeX math and non-math elements, this converts all the math and leaves the rest of the string unmodified. HTML tags are removed completely.

### Array of equations

Rather than just a string, you can also provide an array of math inputs:

``` ruby
inputs = []
inputs << '$\pi$'
inputs << '$not__thisisnotreal$'
inputs << '$\alpha$'

Mathematical.new.render(inputs)
```

This returns an array of hashes, rendering the indices. For example, for the above, you will receive the following output:

```
[ {:data => "...", :width => ... }, { :data => '$not__thisisnotreal$', :exception => "...", {:data => "...", :width => ... }]
```

That is, while the first and last elements are valid TeX math, the middle one is not, so the same string is returned. As with single strings, the error message is printed to STDERR, but not raised.

### Options

`Mathematical.new` takes an optional hash to define a few options:

| Name | Description | Default
|------|-------------|--------
| `:ppi` | A double determining the pixels per inch of the resulting SVG | `72.0`
| `:zoom` | A double determining the zoom level of the resulting SVG | `1.0`
| `:base64` | A boolean determining whether Mathematical's output should be a base64-encoded SVG string | `false`
| `:maxsize` | A numeral indicating the `MAXSIZE` the output string can be. | `unsigned long`
| `:format` | A symbol indicating whether you want an `:svg`, `:png`, or `:mathml` output. | `:svg`
| `:delimiter` | A symbol indicating whether you want an `:DOLLAR` for inline (`$..$`), `:DOUBLE` for display (`$$..$$`), `:PARENS` for inline (`\(..\)`), `:BRACKETS` for display (`[..\]`), or `:ENVIRONMENTS` for parsing bare `\\begin..\\end` environments. You can also pass in an array of symbols to have multiple delimiters considered. | `[:DOLLAR, :DOUBLE]`

Pass these in like this:

``` ruby
options = { :ppi => 200.0, :zoom => 5.0, :base64 => true }
renderer = Mathematical.new(options)
renderer.render('$a \ne b$')
```

### Supported commands and symbols

Check out [SUPPORTED.md on the mtex2MML website](https://github.com/gjtorikian/mtex2MML/blob/master/SUPPORTED.md).

**Note**: This library makes a few assumptions about the strings that you pass in. It assumes that `$..$` is inline math and `$$..$$` is display math.

## Building

Before building this gem, you must install the following libraries:

* Ruby 2.1 or higher (you'll need Ruby header files, so a `*-dev` version is also required)
* GNU make
* glib-2.0
* gdk-pixbuf-2.0
* xml2
* cairo
* pango
* [Dependencies for mtex2MML](https://github.com/gjtorikian/mtex2MML#building)

After cloning the repo, you can fetch dependencies and run the library by typing:

```
script/bootstrap
bundle exec rake compile
```

If there were no errors, you're done! Otherwise, make sure to follow the dependency instructions.

### Fonts and special notices for Mac OS X

Install the fonts with:

```
cd ~/Library/Fonts
curl -LO http://mirrors.ctan.org/fonts/cm/ps-type1/bakoma/ttf/cmex10.ttf \
     -LO http://mirrors.ctan.org/fonts/cm/ps-type1/bakoma/ttf/cmmi10.ttf \
     -LO http://mirrors.ctan.org/fonts/cm/ps-type1/bakoma/ttf/cmr10.ttf \
     -LO http://mirrors.ctan.org/fonts/cm/ps-type1/bakoma/ttf/cmsy10.ttf \
     -LO http://mirrors.ctan.org/fonts/cm/ps-type1/bakoma/ttf/esint10.ttf \
     -LO http://mirrors.ctan.org/fonts/cm/ps-type1/bakoma/ttf/eufm10.ttf \
     -LO http://mirrors.ctan.org/fonts/cm/ps-type1/bakoma/ttf/msam10.ttf \
     -LO http://mirrors.ctan.org/fonts/cm/ps-type1/bakoma/ttf/msbm10.ttf
```

## Troubleshooting

### Issues building Lasem

If you're having issues building Lasem, or have Lasem already preinstalled, you should set the `MATHEMATICAL_USE_SYSTEM_LASEM` environment variable to skip the build:

* If you use bundler:

        MATHEMATICAL_USE_SYSTEM_LASEM=1 bundle install

* If you use gem install:

        MATHEMATICAL_USE_SYSTEM_LASEM=1 gem install mathematical

### Issues building mtex2mml

If you're having issues building mtex2mml, or have mtex2mml already preinstalled, you should set the `MATHEMATICAL_USE_SYSTEM_MTEX2MML` environment variable to skip the build:

* If you use bundler:

        MATHEMATICAL_USE_SYSTEM_MTEX2MML=1 bundle install

* If you use gem install:

        MATHEMATICAL_USE_SYSTEM_MTEX2MML=1 gem install mathematical

## Benchmark

Run benchmarks with `bundle exec rake benchmark`:

```
Benchmarking....
Count: 3868 equations
Iterations: 1
                                               user     system      total        real
Rendering...                               3.280000   0.070000   3.350000 (  4.324458)
```

## History

There are a smattering of libraries written in various languages to convert math
into a variety of formats. But there needs to be a sane way to show math
equations in the browser. With browser support for MathML under attack, it's
unfortunately not a sustainable solution. A PNG or SVG representation of the
equation is the safest way to go.

Most advice suggests using [MathJax](http://www.mathjax.org/). While extremely popular
I dislike the "stuttering" effect caused by pages loading math. JavaScript
shouldn't be used in situations where server-rendering is a possibility, in my opinion.

To that end, I obsessed over the problem of server-side math rendering for over a
week. Here was my journey:

* I started out with [`blahtexml`](https://github.com/gvanas/blahtexml), which takes
TeX equations and converts them to PNG. This wasn't a bad idea, but it took too long;
for twelve equations, it took eight seconds. It was slow because it shelled out
to [`LaTeX`](http://www.latex-project.org/), *then* [`dvipng`](http://www.nongnu.org/dvipng/).

  In fact, as I discovered, most projects on the 'Net shell out to `LaTeX`, then
something else, which makes performance absolutely horrid. I had to find something
better, with preferably no dependency on `LaTeX`.

* [`mimetex`](http://www.forkosh.com/mimetex.html) was my next attempt. It looked
great: a pure C implementation that turned TeX equations into a rasterized representation,
and then into a PNG. The speed was there, but the output image was pretty jagged.
I tweaked the program to output BMPs, and tried to sharpen those with [`potrace`](http://potrace.sourceforge.net/),
but the results were less then pleasant. The "update" to `mimetex` is [`mathtex`](http://www.forkosh.com/mathtex.html),
but it, too, depends on `LaTeX` and `dvipng` binaries to produce images.

* [`pmml2svg`](http://pmml2svg.sourceforge.net/) had potential. It's a set of
XSLT stylesheets to convert MathML to SVG. Unfortunately, it relies on XSLT 2.0,
of which there are no Ruby bindings (at the time of this writing, April '14). It
had to rely on [Saxon](http://saxon.sourceforge.net/) and Java.

* [`tth`](http://hutchinson.belmont.ma.us/tth/) converts TeX to HTML, but the
output is aesthetically unpleasing, so I passed.

* Wikipedia uses [`texvc`](https://github.com/dlitz/texvc), which is written in OCaml,
a language I am utterly unfamiliar with. In any event, I could not get the code
to compile on my machine.

* It took me forever to finally compile [`gtkmathview`](https://github.com/khaledhosny/gtkmathview),
and when it did, I got a bunch of SVG images with screwed up fonts.

* [`dvisvgm`](http://dvisvgm.sourceforge.net/) worked well, but still depended
on two external binaries (`LaTeX` to convert the text to dvi, and `dvisvgm` to turn
it into SVG)

* At one point, I began to try and convert the MathJax code to Ruby to figure out
how it accomplished its `toSVG` methods. The MathJax codebase, while written by
geniuses, is incomprehensible, due in part to JavaScript's inability
to possess a coherent structure.

* Near the end of my wits, I mimicked the behavior of [`mathrender2`](https://github.com/quipper/mathrender2),
which uses [PhantomJS](http://phantomjs.org/) to embed MathJax onto a fake
HTML page. This produced exactly what I needed: a bunch of accurate SVG files with
no intermediate binaries. It was, unfortunately, a bit slow: for an arbitrary
composition of 880 equations, it took about eight seconds to complete. Could I
do better?

* I came across [Lasem](https://wiki.gnome.org/action/show/Projects/Lasem?action=show&redirect=Lasem),
which met every need. It has no external binary dependencies (only library packages),
can convert directly to SVG, and it's fast. The same arbitrary 880 equations were
rendered in moments.

And thus a wrapper was born.

## More math stuff

Check out [math-to-itex](https://github.com/gjtorikian/math-to-itex/), which quickly
parses out TeX notation from strings.

With it, you could do something fun like:

``` ruby
MathToItex(string).convert do |eq, type|
  svg_content = Mathematical.new(:base64 => true).render(eq)

  # create image tags of math with base64-encoded SVGs
  %|<img class="#{type.to_s}-math" data-math-type="#{type.to_s}-math" src="#{svg_content}"/>|
end
```
