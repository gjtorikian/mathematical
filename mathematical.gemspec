# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'mathematical/version'

Gem::Specification.new do |spec|
  spec.name          = 'mathematical'
  spec.version       = Mathematical::VERSION
  spec.authors       = ['Garen Torikian']
  spec.email         = ['gjtorikian@gmail.com']
  spec.summary       = 'Quickly convert math equations into beautiful SVGs/PNGs/MathML.'
  spec.description   = 'A very fast way to turn TeX math equations into beautifully rendered SVGs, to embed on the web. This library is mostly written in C and is a general purpose wrapper to GNOME\'s Lasem.'
  spec.homepage      = 'https://github.com/gjtorikian/mathematical'
  spec.license       = 'MIT'

  spec.files         = %w(LICENSE.txt README.md Rakefile mathematical.gemspec)
  spec.files        += Dir.glob('lib/**/*.rb')
  spec.files        += Dir['ext/**/*'].reject { |f| f =~ /\.svg$|\.mml$|\.png$|\.o$/ }
  spec.test_files    = Dir.glob('test/**/*')
  spec.require_paths = %w(lib ext)
  spec.extensions    = ['ext/mathematical/extconf.rb']

  spec.add_dependency 'ruby-enum', '~> 0.4'

  spec.add_development_dependency 'rake', '~> 13.0'
  spec.add_development_dependency 'rake-compiler', '~> 1.0'
  spec.add_development_dependency 'minitest', '~> 5.6'
  spec.add_development_dependency 'math-to-itex', '~> 0.3'
  spec.add_development_dependency 'nokogiri', '~> 1.10'
  spec.add_development_dependency 'pry-byebug', '~> 3.4.0'
end
