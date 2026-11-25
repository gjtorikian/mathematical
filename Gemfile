# frozen_string_literal: true

source "https://rubygems.org"

# Specify your gem's dependencies in mathematical.gemspec
gemspec

gem "rake", "~> 13.0"
gem "rake-compiler", "~> 1.2"
gem "rake-compiler-dock", "~> 1.11"

group :test do
  gem "math-to-itex", "~> 0.3"
  gem "minitest", "~> 5.6"
  gem "nokogiri", "~> 1.10"
end

group :lint do
  gem "rubocop", "~> 1.21"
  gem "rubocop-standard"
end

group :benchmark do
  gem "benchmark"
end
