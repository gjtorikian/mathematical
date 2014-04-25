# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'mathematical/version'

Gem::Specification.new do |spec|
  spec.name          = "mathematical"
  spec.version       = Mathematical::VERSION
  spec.authors       = ["Garen Torikian"]
  spec.email         = ["gjtorikian@gmail.com"]
  spec.summary       = %q{Turn maths into PNGs.}
  spec.description   = %q{Turn maths into PNGs.}
  spec.homepage      = ""
  spec.license       = "MIT"
  spec.platform      = Gem::Platform::RUBY

  spec.files = Dir.glob("ext/**/*.{c,rb}") +
               Dir.glob("lib/**/*.rb")

  spec.extensions  = ["ext/mathematical/extconf.rb"]

  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_dependency "itextomml", "~> 1.5"
  spec.add_dependency "nokogiri",  "~> 1.6"

  spec.add_development_dependency "bundler", "~> 1.5"
  spec.add_development_dependency "rake"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "mocha", "~> 1.0"
  spec.add_development_dependency "pry", "~> 0.9"
  spec.add_development_dependency "pry-debugger", "~> 0.2"
end
