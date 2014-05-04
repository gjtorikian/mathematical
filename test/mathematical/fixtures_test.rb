require "test_helper"

class Mathematical::FixturesTest < Test::Unit::TestCase

  Dir['test/mathematical/fixtures/before/*.text'].each do |before|
    name = before.split('/').last

    define_method "test_#{name}" do
      source = File.read(before)

      actual = Mathematical::Render.new.render(source).rstrip

      expected_file = before.sub(/before/, "after").sub(/text/, "html")

      File.open(expected_file, "w") { |file| file.write(actual) } unless ENV['DEBUG_MATHEMATICAL'].nil?

      expected = File.read(expected_file).rstrip

      if source != expected
        assert(source != actual, "#{name} did not render anything")
      end

      diff = IO.popen("diff -u - #{expected_file}", 'r+') do |f|
        f.write actual
        f.close_write
        f.read
      end

      assert expected == actual, <<message
#{File.basename expected_file}'s contents don't match command output:
#{diff}
message
    end
  end
end
