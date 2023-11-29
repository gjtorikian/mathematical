# frozen_string_literal: true

require "test_helper"
require "nokogiri"

class Mathematical
  class BasicTest < Minitest::Test
    def test_it_has_a_version
      assert(Mathematical::VERSION)
    end

    def test_multiple_calls
      render = Mathematical.new
      render.render('$\pi$')
      output = render.render('$\pi$')[:data]

      assert_equal(1, output.scan(/<svg/).size, "should only contain one svg")

      # assert the SVG actually rendered
      doc = Nokogiri::HTML(output)

      assert_empty(doc.search(%(//svg[@width='0pt'])))
      assert_empty(doc.search(%(//svg[@height='0pt'])))
    end

    def test_inline
      render = Mathematical.new(format: :mathml)

      fixture_tex = File.read(File.join(MTEX2MML_FIXTURES_DIR, "basic", "inline.txt"))
      fixture_mml = File.read(File.join(MTEX2MML_FIXTURES_DIR, "basic", "inline.html")).strip
      result = render.parse(fixture_tex)
      output = result[:data]

      assert_equal(fixture_mml, output)
    end

    def test_block
      render = Mathematical.new(format: :mathml)

      fixture_tex = File.read(File.join(MTEX2MML_FIXTURES_DIR, "basic", "block.txt"))
      fixture_mml = File.read(File.join(MTEX2MML_FIXTURES_DIR, "basic", "block.html")).strip
      result = render.parse(fixture_tex)
      output = result[:data]

      assert_equal(fixture_mml, output)
    end

    def test_filter_mathml
      render = Mathematical.new(format: :mathml)

      fixture_tex = File.read(File.join(MTEX2MML_FIXTURES_DIR, "basic", "filter.txt"))
      fixture_mml = File.read(File.join(MTEX2MML_FIXTURES_DIR, "basic", "filter.html")).strip
      result = render.filter(fixture_tex)
      output = result[:data]

      assert_equal(fixture_mml, output)
    end

    def test_text_filter_mathml
      render = Mathematical.new(format: :mathml)

      fixture_tex = File.read(File.join(MTEX2MML_FIXTURES_DIR, "basic", "text_filter.txt"))
      fixture_mml = File.read(File.join(MTEX2MML_FIXTURES_DIR, "basic", "text_filter.html")).strip
      result = render.text_filter(fixture_tex)
      output = result[:data]

      assert_equal(fixture_mml, output)
    end

    def test_text_filter_svg
      render = Mathematical.new(format: :svg)

      fixture_tex = File.read(File.join(MTEX2MML_FIXTURES_DIR, "basic", "text_filter.txt"))
      result = render.text_filter(fixture_tex)

      output = result[:data]

      assert_match(/Inline: <svg/, output)
      assert_match(/Block: <svg/, output)
      assert_match(/Markup: <svg/, output)
    end

    def test_strict_filter_mathml
      render = Mathematical.new(format: :mathml)

      fixture_tex = File.read(File.join(MTEX2MML_FIXTURES_DIR, "basic", "strict_filter.txt"))
      fixture_mml = File.read(File.join(MTEX2MML_FIXTURES_DIR, "basic", "strict_filter.html")).strip
      result = render.strict_filter(fixture_tex)
      output = result[:data]

      assert_equal(fixture_mml, output)
    end
  end
end
