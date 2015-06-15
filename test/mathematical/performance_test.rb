require 'test_helper'
require 'benchmark'

class Mathematical::BasicTest < MiniTest::Test
  def test_it_handles_big_files
    big_file = File.read('test/mathematical/fixtures/performance/big_file.text')
    speed = Benchmark.realtime do
      assert_silent do
        Mathematical.new.filter(big_file)
      end
    end

    assert_operator speed, :<=, 5
  end
end
