require "test_helper"
require 'benchmark'

class Mathematical::BasicTest < Test::Unit::TestCase

  def test_it_handles_big_files
    assert_nothing_raised do
      big_file = File.read('test/mathematical/fixtures/performance/big_file.text')
      speed = Benchmark.realtime { Mathematical::Render.new.render(big_file) }
      assert_operator speed, :<=, 3
    end
  end
end
