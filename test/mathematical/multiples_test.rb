require "test_helper"

class Mathematical::MultiplesTest < Test::Unit::TestCase

  def setup
    @render = Mathematical.new(:base64 => true)
  end

  def test_it_works_for_a_single_numbered_equation
    string = '''
$$
\begin{equation}
 f(x)=(x+a)(x+b)
\end{equation}
$$
'''

    output = @render.render([string])
    svg = output.first['svg']

    assert_equal 1, svg.scan(/svg\+xml;/).size, 'should only contain one svg'
    assert_match 'PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My', svg
  end

  def test_it_works_for_many_equations
    inputs = []
    (1..1000).each do |i|
      string = """
  $$
  \\begin{equation}
   f(#{i})=(x+a)(x+b)
  \\end{equation}
  $$
  """
      inputs << string
    end

    output = @render.render(inputs)
    assert_equal 1000, output.length
    output.each do |data|
      assert_match 'PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My', data['svg']
    end
  end

      assert_match 'PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My', data['svg']
    end
  end
end
