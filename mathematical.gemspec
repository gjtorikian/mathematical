# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'mathematical/version'

Gem::Specification.new do |spec|
  spec.name          = "mathematical"
  spec.version       = Mathematical::VERSION
  spec.authors       = ["Garen Torikian"]
  spec.email         = ["gjtorikian@gmail.com"]
  spec.summary       = %q{Quickly turn itex math equations into base64 SVGs.}
  spec.description   = %q{A very fast way to turn itex math equations into beautifully rendered base64 SVGs, to embed on the web. This library is a general purpose wrapper to GNOME's Lasem. }
  spec.homepage      = "https://github.com/gjtorikian/mathematical"
  spec.license       = "MIT"

  spec.files         = %w(LICENSE.txt README.md Rakefile mathematical.gemspec)
  spec.files         += Dir.glob("lib/**/*")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "bundler", "~> 1.5"
  spec.add_development_dependency "mocha", "~> 1.0"
end
