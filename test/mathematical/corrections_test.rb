require "test_helper"

class Mathematical::CorrectionsTest < Test::Unit::TestCase

  def setup
    @render = Mathematical::Render.new
  end

  def test_adjust_lt_gt
    simple_lt = '$|q| < 1$'
    assert_match /|q| \\lt 1/, @render.apply_corrections(simple_lt)

    simple_gt = '$|q| > 1$'
    assert_match /|q| \\gt 1/, @render.apply_corrections(simple_gt)
  end
end
