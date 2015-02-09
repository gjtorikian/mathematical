require 'bundler/setup'
require 'mathematical'
require 'test/unit'
require 'mocha/test_unit'
require 'math-to-itex'

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
