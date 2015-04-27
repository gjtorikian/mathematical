# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'mathematical/version'

Gem::Specification.new do |spec|
  spec.name          = 'mathematical'
  spec.version       = Mathematical::VERSION
  spec.authors       = ['Garen Torikian']
  spec.email         = ['gjtorikian@gmail.com']
  spec.summary       = %w(Quickly convert math equations into beautiful SVGs/PNGs/MathML.)
  spec.description   = %w(A very fast way to turn LaTeX math equations into beautifully rendered SVGs, to embed on the web. This library is mostly written in C and is a general purpose wrapper to GNOME's Lasem.)
  spec.homepage      = 'https://github.com/gjtorikian/mathematical'
  spec.license       = 'MIT'

  spec.files         = %w(LICENSE.txt README.md Rakefile mathematical.gemspec)
  spec.files        += Dir.glob('lib/**/*.rb')
  spec.files        += Dir.glob('ext/**/*.{c,h}')
  spec.files        += Dir.glob('ext/**/extconf.rb')
  spec.test_files    = Dir.glob('test/**/*')
  spec.require_paths = %w(lib ext)
  spec.extensions    = ['ext/mathematical/extconf.rb']

  spec.add_development_dependency 'rake', '~> 0.9'
  spec.add_development_dependency 'rake-compiler', '~> 0.9'
  spec.add_development_dependency 'bundler', '~> 1.5'
  spec.add_development_dependency 'math-to-itex', '0.3.0'
  spec.add_development_dependency 'nokogiri', '~> 1.6'
end
