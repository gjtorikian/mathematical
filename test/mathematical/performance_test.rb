require "test_helper"
require 'benchmark'

class Mathematical::BasicTest < Test::Unit::TestCase
  def test_it_handles_big_files
    assert_nothing_raised do
      big_file = File.read('test/mathematical/fixtures/performance/big_file.text')
      speed = Benchmark.realtime do
        MathToItex(big_file).convert { |equation| Mathematical.new.render(equation) }
      end

      assert_operator speed, :<=, 5
    end
  end
end
