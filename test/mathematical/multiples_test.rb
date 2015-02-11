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

  def test_it_properly_accounts_for_equations
    inputs = []
    [1, 2].each do |i|
      string = """
  $$
  \\begin{equation}
   f(#{i})=(x+a)(x+b)
  \\end{equation}
  $$
  """
      inputs << string
    end

    inputs.insert(1, '$test$')
    render = Mathematical.new({:format => :png})
    output = render.render(inputs)
    assert_equal 3, output.length
    output.each_with_index do |data_hash, i|
      header = data_hash['png'].unpack('H*').first.slice(0, 18)
      File.open("#{fixtures_dir}/png/numeric_test_#{i + 1}.png", 'w') { |f| f.write(data_hash['png'])}
      assert_equal header, '89504e470d0a1a0a00'
    end
  end
end
