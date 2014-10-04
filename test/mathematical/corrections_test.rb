require "test_helper"

class Mathematical::CorrectionsTest < Test::Unit::TestCase

  def setup
    @render = Mathematical::Render.new
    @slash_maths = '''
$$
\dot{x} & = \sigma(y-x) \\\\
\dot{y} & = \rho x - y - xz \\\\
\dot{z} & = -\beta z + xy
$$
'''

    @aligned_maths = '''
$$
\begin{align}
\dot{x} & = \sigma(y-x) \\\\
\dot{y} & = \rho x - y - xz \\\\
\dot{z} & = -\beta z + xy
\end{align}
$$
'''
  end

  def test_expect_slashes_failures
    @render.expects(:apply_corrections).returns(@slash_maths)

    printed = capture_stderr do
      @render.render @slash_maths
    end
    assert_match /Failed to parse mtex/, printed
  end

  def test_adjust_aligned
    assert_no_match /align\}/, @render.apply_corrections(@aligned_maths)
  end

  def test_adjust_fracs
    simple_frac = '$\frac25$'
    assert_match /frac\{2\}\{5\}/, @render.apply_corrections(simple_frac)
  end

  def test_adjust_lt_gt
    simple_lt = '$|q| < 1$'
    assert_match /|q| \\lt 1/, @render.apply_corrections(simple_lt)

    simple_gt = '$|q| > 1$'
    assert_match /|q| \\gt 1/, @render.apply_corrections(simple_gt)
  end

  def test_adjust_limits
    integral = '\int\limits_{-\pi}^{\pi}'
    assert_equal '\int_{-\pi}^{\pi}', @render.apply_corrections(integral)
  end
end
