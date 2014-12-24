require 'test_helper'

class Mathematical::MathJaxTest < Test::Unit::TestCase

  render = Mathematical::Render.new

  MATHJAX_TEST_TEST_DIR = File.join('ext', 'mathematical', 'mtex2MML', 'test', 'fixtures', 'MathJax')
  MATHJAX_TEST_TEX_DIR = File.join(MATHJAX_TEST_TEST_DIR, 'LaTeXToMathML-tex')

  Dir["#{MATHJAX_TEST_TEX_DIR}/**/*.tex"].each do |tex|
    define_method "test_#{tex}" do
      tex_contents = File.read(tex)
      assert_nothing_raised { render.render(tex_contents) }
    end
  end
end
