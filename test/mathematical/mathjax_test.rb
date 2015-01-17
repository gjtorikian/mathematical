require 'test_helper'
require 'nokogiri'

class Mathematical::MathJaxTest < Test::Unit::TestCase

  render_svg = Mathematical::Render.new

  MATHJAX_TEST_TEST_DIR = File.join('ext', 'mathematical', 'mtex2MML', 'test', 'fixtures', 'MathJax')
  MATHJAX_TEST_TEX_DIR = File.join(MATHJAX_TEST_TEST_DIR, 'LaTeXToMathML-tex')

  SKIPPED = []
  Dir["#{MATHJAX_TEST_TEX_DIR}/**/*.tex"].each do |tex|
    define_method "test_#{tex}" do
      tex_contents = File.read(tex)
      data = nil
      assert_nothing_raised { data = render_svg.render(tex_contents) }

      render_mathml = Mathematical::Render.new({:format => "mathml"})
      mathml = render_mathml.render(tex_contents)['mathml']

      # TODO Lasem can't handle this node
      if mathml =~ /menclose/
        puts "\n\nSKIPPING #{tex}\n\n"
      else
        # assert the SVG actually rendered
        doc = Nokogiri::HTML(data['svg'])
        assert_empty doc.search(%(//svg[@width='0pt']))
        assert_empty doc.search(%(//svg[@height='0pt']))
      end
    end
  end
end
