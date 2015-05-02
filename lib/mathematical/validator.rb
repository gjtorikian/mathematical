class Mathematical
  module Validator
    # explanation can be found at http://git.io/vJRBj
    DOLLAR_MATCHER = /(?<!\\)(?:((?<!\$)\${1,2}(?!\$))(.*?(\g<1>)?.*?)(?<!\\)(?(1)(?<!\$)\1(?!\$)))/xm

    FORMAT_TYPES = [:svg, :png, :mathml].freeze

    def validate_config(config)
      fail(TypeError, 'maxsize must be an integer!') unless config[:maxsize].is_a? Fixnum
      fail(TypeError, 'maxsize cannot be less than 0!') if config[:maxsize] < 0
      fail(TypeError, 'format must be a symbol!') unless config[:format].is_a? Symbol
      fail(TypeError, "format type must be one of the following formats: #{FORMAT_TYPES.join(', ')}") unless FORMAT_TYPES.include?(config[:format])
    end

    def validate_content(maths)
      if !maths.is_a?(String) && !maths.is_a?(Array)
        fail(TypeError, 'input must be a string or an array!')
      end

      if maths.is_a? String
        validate_string(maths)
      else
        validate_array(maths)
      end
    end

    def validate_string(maths)
      maths = maths.strip
      unless valid_math_string(maths)
        fail(ArgumentError, 'input must be in tex format (`$...$` or `$$...$$`)!')
      end

      maths
    end

    def validate_array(maths)
      maths.map do |m|
        unless m.is_a?(String)
          fail(ArgumentError, 'every element in array must be a string in tex format (`$...$` or `$$...$$`)!')
        end
        validate_string(m)
      end

      maths
    end

    def valid_math_string(maths)
      maths =~ DOLLAR_MATCHER
    end

  end
end
