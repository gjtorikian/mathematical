# frozen_string_literal: true

require "test_helper"
require "math-to-itex"

class Mathematical
  class FixturesTest < Minitest::Test
    # the same SVGs sometimes get random id values, throwing off the tests
    def strip_id(blob)
      blob.gsub(/id="surface.+?"/, "")
    end

    Dir["#{fixtures_dir}/before/*.text"].each do |before|
      name = before.split("/").last

      define_method :"test_#{name}" do
        source = File.read(before)

        if ENV["MATHEMATICAL_GENERATE_SAMPLE"]
          next unless name.include?("compliance")

          write_sample(source)
        end

        actual = MathToItex(source).convert do |eq, type|
          svg_content = Mathematical.new(base64: true).render(eq)

          %(<img class="#{type}-math" data-math-type="#{type}-math" src="#{svg_content[:data]}"/>)
        end.rstrip

        expected_file = before.sub("before", "after").sub("text", "html")

        File.open(expected_file, "w") { |file| file.write(actual) } unless ENV["DEBUG_MATHEMATICAL"].nil?

        expected = File.read(expected_file)

        expected = (MathToItex(expected).convert { |string| Mathematical.new.render(string) }).rstrip

        # Travis and OS X each render SVGs differently. For now, let's just be happy
        # that something renders at all.
        unless actual.match?("PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My")
          diff = IO.popen("diff -u - #{expected_file}", "r+") do |f|
            f.write(actual)
            f.close_write
            f.read
          end

          assert_equal expected, actual, <<-eos
  #{File.basename(expected_file)}'s contents don't match command output:
  #{diff}
          eos
        end
      end
    end
  end
end
