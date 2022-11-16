# frozen_string_literal: true

require "test_helper"

module Mathematical
  class BasicTest < MiniTest::Test
    def test_single_dollar
      render = Mathematical.new(delimiter: :DOLLAR, format: :mathml)

      fixture_tex = "$\\pi$"
      fixture_mml = File.read(File.join(MTEX2MML_FIXTURES_DIR, "delimiters", "single_dollar.html")).strip
      result = render.render(fixture_tex)
      output = result[:data]

      assert_equal(fixture_mml, output)
    end

    def test_double_dollar
      render = Mathematical.new(delimiter: :DOUBLE, format: :mathml)

      fixture_tex = "$$\\pi$$"
      fixture_mml = File.read(File.join(MTEX2MML_FIXTURES_DIR, "delimiters", "double_dollar.html")).strip
      result = render.render(fixture_tex)
      output = result[:data]

      assert_equal(fixture_mml, output)
    end

    def test_parens
      render = Mathematical.new(delimiter: :PARENS, format: :mathml)

      fixture_tex = "\\(\\pi\\)"
      fixture_mml = File.read(File.join(MTEX2MML_FIXTURES_DIR, "delimiters", "parens.html")).strip
      result = render.render(fixture_tex)
      output = result[:data]

      assert_equal(fixture_mml, output)
    end

    def test_brackets
      render = Mathematical.new(delimiter: :BRACKETS, format: :mathml)

      fixture_tex = "\\[\\pi\\]"
      fixture_mml = File.read(File.join(MTEX2MML_FIXTURES_DIR, "delimiters", "brackets.html")).strip
      result = render.render(fixture_tex)
      output = result[:data]

      assert_equal(fixture_mml, output)
    end

    def test_environments
      render = Mathematical.new(delimiter: :ENVIRONMENTS, format: :mathml)

      fixture_tex = "\\begin{equation}f(x)=(x+a)(x+b)\\end{equation}"
      fixture_mml = File.read(File.join(MTEX2MML_FIXTURES_DIR, "delimiters", "single_equation.html")).strip
      result = render.render(fixture_tex)
      output = result[:data]

      assert_equal(fixture_mml, output)
    end

    def test_mixed
      render = Mathematical.new(delimiter: [:BRACKETS, :DOUBLE], format: :mathml)

      fixture_tex = "\\[\\alpha\\] $$\\beta$$"
      fixture_mml = File.read(File.join(MTEX2MML_FIXTURES_DIR, "delimiters", "mixed.html")).strip
      result = render.filter(fixture_tex)
      output = result[:data]

      assert_equal(fixture_mml.strip, output)
    end
  end
end
