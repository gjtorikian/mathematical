require "test_helper"
require 'benchmark'

class Mathematical::MathMLTest < Test::Unit::TestCase

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
    render = Mathematical::Render.new({:format => "mathml"})
    mathml = render.render(string)["mathml"]

    assert_match /<math xmlns='http:\/\/www.w3.org\/1998\/Math\/MathML' display='block'><semantics><mrow><mrow><mo>\(/, mathml
  end
end
