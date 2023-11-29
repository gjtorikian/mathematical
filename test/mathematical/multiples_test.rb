# frozen_string_literal: true

require "test_helper"

class Mathematical
  class MultiplesTest < Minitest::Test
    def setup
      @render = Mathematical.new(base64: true)
    end

    def test_it_works_for_a_single_numbered_equation
      string = <<~STRING
        $$
        \begin{equation}
         f(x)=(x+a)(x+b)
        \end{equation}
        $$
      STRING

      output = @render.render([string])
      svg = output.first[:data]

      assert_equal(1, svg.scan(/svg\+xml;/).size, "should only contain one svg")
      assert_match("PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My", svg)
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

      assert_equal(1000, output.length)
      output.each do |data|
        assert_match("PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My", data[:data])
      end
    end

    def test_it_properly_accounts_for_equations
      skip "png tests are currently unsupported"
      inputs = []
      (1..2).each do |i|
        string = """
  $$
  \\begin{equation}
   f(#{i})=(x+a)(x+b)
  \\end{equation}
  $$
  """
        inputs << string
      end

      inputs.insert(1, "$test$")
      render = Mathematical.new({ format: :png })
      output = render.render(inputs)

      assert_equal(3, output.length)
      output.each_with_index do |data_hash, i|
        header = data_hash[:data].unpack("H*").first.slice(0, 18)
        File.open("#{fixtures_dir}/png/numeric_test_#{i + 1}.png", "w") { |f| f.write(data_hash[:data]) }

        assert_equal("89504e470d0a1a0a00", header)
      end
    end
  end
end
