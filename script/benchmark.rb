#!/usr/bin/ruby
# frozen_string_literal: true

# Run with `bundle exec rake benchmark`

require "mathematical"
require "benchmark"
require "math-to-itex"

include Benchmark

ITERATIONS = 1

file = File.open("test/mathematical/fixtures/performance/big_file.text").read.to_s

puts "Benchmarking....\n"

equations = []
MathToItex(file).convert { |equation| equations << equation }
(1..ITERATIONS).each do
  equations += equations
end

puts "Count: #{equations.length} equations\n"
puts "Iterations: #{ITERATIONS}\n"

Benchmark.bm(40) do |x|
  x.report("Rendering...                             ") { Mathematical.new.render(equations) }
end
