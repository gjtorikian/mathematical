require 'test_helper'

class Mathematical::MathMLTest < MiniTest::Test

  def test_it_returns_mathml
    string = '''
    $$
\begin{pmatrix}
     1 & a_1 & a_1^2 & \cdots & a_1^n \\\\
     1 & a_2 & a_2^2 & \cdots & a_2^n \\\\
     \vdots  & \vdots& \vdots & \ddots & \vdots \\\\
     1 & a_m & a_m^2 & \cdots & a_m^n
     \end{pmatrix}
$$
'''
    render = Mathematical.new({:format => :mathml})
    mathml = render.render(string)[:data]

    assert_match %r{<math xmlns='http://www.w3.org/1998/Math/MathML' display='block'><semantics><mrow><mrow><mo>\(}, mathml
  end
end
