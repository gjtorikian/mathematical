class Mathematical
  module Validator

    FORMAT_TYPES = [:svg, :png, :mathml].freeze
    RENDER_TYPES = [:parse, :filter, :text_filter, :strict_filter].freeze

    def validate_config(config)
      fail(TypeError, 'maxsize must be an integer!') unless config[:maxsize].is_a? Fixnum
      fail(TypeError, 'maxsize cannot be less than 0!') if config[:maxsize] < 0
      fail(TypeError, 'format must be a symbol!') unless config[:format].is_a? Symbol
      fail(TypeError, "format type must be one of the following formats: #{FORMAT_TYPES.join(', ')}") unless FORMAT_TYPES.include?(config[:format])
      if config[:delimiter].is_a?(Symbol)
        Configuration::Delimiters.option_exists?(config[:delimiter])
      elsif !config[:delimiter].is_a?(Numeric)
        fail(TypeError, 'delimiter type must be a valid symbol or integer')
      end
    end

    def validate_content(maths)
      if maths.is_a? Array
        maths.map { |m| validate_string(m) }
      else
        validate_string(maths)
      end
    end

    def validate_string(maths)
      fail(ArgumentError, 'input must be string!') unless maths.is_a?(String)
      maths.strip
    end
  end
end
