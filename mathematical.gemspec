# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'mathematical/version'

Gem::Specification.new do |spec|
  spec.name          = "mathematical"
  spec.version       = Mathematical::VERSION
  spec.authors       = ["Garen Torikian"]
  spec.email         = ["gjtorikian@gmail.com"]
  spec.summary       = %q{Turn itex math equations into base64 SVGs.}
  spec.description   = %q{It's a fast and aesthetically pleasing mechanism to turn math equations into base64 SVGs, to embed on the web. It's a general purpose wrapper to GNOME's Lasem. }
  spec.homepage      = "https://github.com/gjtorikian/mathematical"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "bundler", "~> 1.5"
  spec.add_development_dependency "mocha", "~> 1.0"
end
