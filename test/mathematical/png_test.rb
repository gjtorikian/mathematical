require "test_helper"
require 'benchmark'

class Mathematical::PNGTest < Test::Unit::TestCase
  def before
    File.delete("#{fixtures_dir}/png/pmatrix.png") if File.exists?("#{fixtures_dir}/png/pmatrix.png")
  end

  def test_it_creates_a_png
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
    render = Mathematical::Render.new({:format => "png"})
    data_hash = render.render(string)
    File.open("#{fixtures_dir}/png/pmatrix.png", "w") { |f| f.write(data_hash["png"])}
  end
end
