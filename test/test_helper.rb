require 'bundler/setup'
require 'mathematical'
require 'test/unit'
require 'mocha/test_unit'
require 'math-to-itex'

def fixtures_dir
  "test/mathematical/fixtures"
end

def capture_stderr(&blk)
  old = $stderr
  $stderr = fake = StringIO.new
  blk.call
  fake.string
ensure
  $stderr = old
end
