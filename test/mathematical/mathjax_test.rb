require 'test_helper'
require 'nokogiri'

class Mathematical::MathJaxTest < MiniTest::Test

  render_svg = Mathematical.new

  MATHJAX_TEST_TEST_DIR = File.join('ext', 'mathematical', 'mtex2MML', 'tests', 'fixtures', 'MathJax')
  MATHJAX_TEST_TEX_DIR = File.join(MATHJAX_TEST_TEST_DIR, 'LaTeXToMathML-tex')

  SKIPPED = []
  Dir["#{MATHJAX_TEST_TEX_DIR}/**/*.text"].each do |tex|
    define_method "test_#{tex}" do
      tex_contents = File.read(tex)
      data = render_svg.render(tex_contents)

      # assert the SVG actually rendered
      doc = Nokogiri::HTML(data[:data])
      assert_empty doc.search(%(//svg[@width='0pt']))
      assert_empty doc.search(%(//svg[@height='0pt']))
    end
  end
end
