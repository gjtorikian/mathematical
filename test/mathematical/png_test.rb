# frozen_string_literal: true

# rubocop:disable Lint/ImplicitStringConcatenation

require "test_helper"

class Mathematical
  class PNGTest < Minitest::Test
    def before
      File.delete("#{fixtures_dir}/png/pmatrix.png") if File.exist?("#{fixtures_dir}/png/pmatrix.png")
    end

    def test_it_creates_a_png
      skip("png tests are currently unsupported")
      string = ""'
    $$
\begin{pmatrix}
     1 & a_1 & a_1^2 & \cdots & a_1^n \\\\
     1 & a_2 & a_2^2 & \cdots & a_2^n \\\\
     \vdots  & \vdots& \vdots & \ddots & \vdots \\\\
     1 & a_m & a_m^2 & \cdots & a_m^n
     \end{pmatrix}
$$
'""
      render = Mathematical.new({ format: :png })
      data_hash = render.render(string)
      header = data_hash[:data].unpack("H*").first.slice(0, 18)
      File.open("#{fixtures_dir}/png/pmatrix.png", "w") { |f| f.write(data_hash[:data]) }

      file_bytes = "89504e470d0a1a0a00"

      assert_equal(header, file_bytes)
    end
  end
end

# rubocop:enable Lint/ImplicitStringConcatenation
