require 'bundler/setup'
require 'mathematical'
require 'minitest/autorun'
require 'minitest/pride'
require 'pp'

MTEX2MML_FIXTURES_DIR = File.join('ext', 'mathematical', 'mtex2MML', 'tests', 'fixtures')
MATHJAX_TEST_DIR = File.join(MTEX2MML_FIXTURES_DIR, 'MathJax')
MATHJAX_TEX_DIR = File.join(MATHJAX_TEST_DIR, 'LaTeXToMathML-tex')

def fixtures_dir
  'test/mathematical/fixtures'
end

def capture_stderr(&blk)
  old = $stderr
  $stderr = fake = StringIO.new
  blk.call
  fake.string
ensure
  $stderr = old
end

def write_base64svg_to_test_file(converted)

  text = """
  <html>

  <body>

  <img class=\"display-math\" data-math-type=\"display-math\" src=\"#{converted}\"/>

  </body>

  </html>
"""

  File.open('test.html', 'w') { |f| f.write(text) }
end

def write_svg_to_test_file(converted)

  text = """
  <html>

  <body>

  #{converted}

  </body>

  </html>
"""

  File.open('test.html', 'w') { |f| f.write(text) }
end

def write_sample(source, name = nil)
  return unless ENV['MATHEMATICAL_GENERATE_SAMPLE']
  MathToItex(source).convert do |eq, type|
    svg_content = Mathematical.new(:base64 => false).render(eq)
    # remove \ and $, remove whitespace, keep alphanums, remove extraneous - and trailing -
    filename = name || eq.gsub(/[\$\\]*/, '').gsub(/\s+/, '-').gsub(/[^a-zA-Z\d]/, '-').gsub(/-{2,}/, '-').gsub(/-$/, '')
    File.open("samples/fixtures/#{filename}.svg", 'w') { |file| file.write svg_content[:data] }
  end
end
