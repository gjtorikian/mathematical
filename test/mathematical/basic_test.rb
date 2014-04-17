require "test_helper"

class Mathematical::BasicTest < Test::Unit::TestCase

  def test_it_has_a_version
    assert Mathematical::VERSION
  end

  def test_something_prints
    puts Mathematical::Render.new.render("wow")
  end
end
