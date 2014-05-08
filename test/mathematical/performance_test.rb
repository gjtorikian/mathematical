require "test_helper"
require 'benchmark'

class Mathematical::BasicTest < Test::Unit::TestCase
  using ::MathToItex

  def test_it_handles_big_files
    assert_nothing_raised do
      big_file = File.read('test/mathematical/fixtures/performance/big_file.text')
      speed = Benchmark.realtime do
        big_file.convert_to_itex do |equation|
          Mathematical::Render.new.render(equation)
        end
      end

      assert_operator speed, :<=, 5
    end
  end
end
