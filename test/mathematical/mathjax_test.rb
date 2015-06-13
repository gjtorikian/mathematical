require 'test_helper'
require 'nokogiri'

class Mathematical::MathJaxTest < MiniTest::Test

  render_svg = Mathematical.new

  SKIPPED = []
  Dir["#{MATHJAX_TEX_DIR}/**/*.txt"].each do |tex|
    define_method "test_#{tex}" do
      tex_contents = File.read(tex)
      data = render_svg.render(tex_contents)

      write_sample(tex_contents, File.basename(tex, '.txt')) if ENV['MATHEMATICAL_GENERATE_SAMPLE']

      # assert the SVG actually rendered
      doc = Nokogiri::HTML(data[:data])
      assert_empty doc.search(%(//svg[@width='0pt']))
      assert_empty doc.search(%(//svg[@height='0pt']))
    end
  end
end
