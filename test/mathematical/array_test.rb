require "test_helper"

class Mathematical::ArrayTest < Test::Unit::TestCase

  def setup
    @render = Mathematical.new
  end

  def test_it_works_for_a_single_numbered_equation
    string = '''
$$
\begin{equation}
 f(x)=(x+a)(x+b)
\end{equation}
$$
'''

    require 'pp'
    # output = render.render([string])
    # pp output
    # svg = output.first['svg']
    # assert_equal 1, svg.scan(/<svg/).size, 'should only contain one svg'
  end
end
