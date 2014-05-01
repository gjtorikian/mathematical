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
Mathematical::Render.new.render(string_with_math)
```

`text` should just be a string, containing inline or display style math. The
output will be all the math equations converted into base64 encoded images.
Inline math will have `class="inline-math"` set, and display math will have
`class="display-math"`.

### Matched math notations

Currently, the following formats are supported:

| inline formulas | displayed equations |
| ------------- |-------------|
| `$...$`      | `[...]`
| `(...)`      | `\begin{equation}...\end{equation}`

## Options

## Dependencies

## Why did you...?

There are a smattering of libraries written in various languages to convert math
into a variety of formats. But there needs to be a sane way to show math
equations in the browser. The options are:

* MathML: With browser support for MathML under attack, it's unfortunately not a sustainable
solution
* MathJax. While extremely popular, I dislike the "stuttering" effect caused by
pages loading math. JavaScript shouldn't be used in situations where server-rendering
is a possibility, in my opinion.
* SVG: This would be a great choice, but, unfortunately, there are some [security concerns](http://www.hgi.ruhr-uni-bochum.de/media/hgi/veroeffentlichungen/2011/10/19/svgSecurity-ccs11.pdf) [PDF]
that make me nervous
* PNG: This is the format which `blahtexml` is capable of outputting. Working
with a binary image has the downside of requiring it to be *hosted* somewhere.

After considering these choices, I thought that a base64 encoded image made
the most sense. You get the benefit of browser compatibility without needing
to serve an image somewhere online.

## Further readings

* ftp://ftp.ams.org/ams/doc/amsmath/short-math-guide.pdf - a short math guide
* http://gva.noekeon.org/blahtexml/blahtexml-0.9-doc.pdf - the blahtex documentation
