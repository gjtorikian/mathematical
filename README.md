# Mathematical

Convert mathematical equations to base64 encoded images.

![](https://i.imgur.com/JC7HT32.gif)

## Installation

Add this line to your application's Gemfile:

    gem 'mathematical'

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install mathematical

## Usage

The simplest way to do this is

``` ruby
Mathematical::Render.new.render(contents)
```

`contents` should just be a block of text, containing inline or display style math.

## Dependencies

Two dependencies are needed:

* [blahtexml](https://github.com/gvanas/blahtexml). This does all the conversion
from math to PNG. It's available for OS X (`make blahtex-mac`) and Linux (`make blahtex-linux`).
* [dvipng](http://sourceforge.net/projects/dvipng/). I'm on a Mac, and could not
for the life of me figure out how to build this. I ended up download [MacTex](https://www.tug.org/mactex/),
which is a *huge* package. `dvipng` is installed under */usr/texbin/dvipng*.

## Why did you...?

There are a smattering of Ruby, C, and Ruby+C libraries out there for converting
math equations to a variety of formats. There needs to be a sane way to show math
equations in the browser. The options are:

* MathML: With browser support for MathML under attack, it's unfortunately not a sustainable
solution
* MathJax. While extremely popular, I dislike the "stuttering" effect caused by
pages loading math. JavaScript shouldn't be used in situations where server-rendering
is a possibility, in my opinion.
* SVG: This would be a great choice, but, unfortunately, there are some [security concerns](http://www.hgi.ruhr-uni-bochum.de/media/hgi/veroeffentlichungen/2011/10/19/svgSecurity-ccs11.pdf) [PDF]
that make me nervous
* PNG: This is the format which `blahtexml` is capable of outputting. Working
with a binary format has the downside of requiring it to be *hosted* somewhere.

After considering these choices, I thought that a base64 encoded image made
the most sense. You get the benefit of browser compatibility without needing
to serve an image somewhere online.

## Further readings

* ftp://ftp.ams.org/ams/doc/amsmath/short-math-guide.pdf - a short math guide
* http://gva.noekeon.org/blahtexml/blahtexml-0.9-doc.pdf - the blahtex documentation
