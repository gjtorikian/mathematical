require 'mathematical/mathematical'

require 'mathematical/corrections'
require 'mathematical/version'

require 'base64'

class Mathematical
  include Corrections

  FORMAT_TYPES = [:svg, :png, :mathml]

  DEFAULT_OPTS = {
    :ppi => 72.0,
    :zoom => 1.0,
    :base64 => false,
    :maxsize => 0,
    :format => :svg
  }

  XML_HEADER = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"

  def initialize(opts = {})
    @config = DEFAULT_OPTS.merge(opts)

    validate_config

    @config[:formatInt] = FORMAT_TYPES.index(@config[:format])

    @processer = Mathematical::Process.new(@config)
  end

  def render(maths)
    maths = validate_content(maths)

    begin
      data = @processer.process(maths)
      fail RuntimeError if data.nil? || (!data.is_a?(Hash) && !data.is_a?(Array))

      if data.is_a? Array
        data.map { |d| format_data(d) }
      else
        format_data(data)
      end
    rescue ParseError, DocumentCreationError, DocumentReadError => e
      # an error in the C code, probably a bad TeX parse
      $stderr.puts "#{e.message}: #{maths}"
      maths
    end
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

  private

  def validate_config
    fail(TypeError, 'maxsize must be an integer!') unless @config[:maxsize].is_a? Fixnum
    fail(TypeError, 'maxsize cannot be less than 0!') if @config[:maxsize] < 0
    fail(TypeError, 'format must be a symbol!') unless @config[:format].is_a? Symbol
    fail(TypeError, "format type must be one of the following formats: #{FORMAT_TYPES.join(', ')}") unless FORMAT_TYPES.include?(@config[:format])
  end

  def validate_string(maths)
    maths = maths.strip
    unless valid_math_string(maths)
      fail(ArgumentError, 'input must be in tex format (`$...$` or `$$...$$`)!')
    end

    maths
  end

  def validate_array(maths)
    unless maths.all? { |m| m.is_a?(String) }
      fail(ArgumentError, 'every element in array must be a string in tex format (`$...$` or `$$...$$`)!')
    end

    maths = maths.map(&:strip)
    unless maths.all? { |m| valid_math_string(m) }
      fail(ArgumentError, 'every element in array must be a string in tex format (`$...$` or `$$...$$`)!')
    end

    maths
  end

  def valid_math_string(maths)
    maths =~ /\A\${1,2}/
  end

  def format_data(data)
    # we passed in an array of math, and found an unprocessable element
    return data unless data.is_a? Hash

    case @config[:format]
    when :svg
      # remove starting <?xml...> tag
      data['svg'] = data['svg'][XML_HEADER.length..-1]
      data['svg'] = svg_to_base64(data['svg']) if @config[:base64]

      data
    when :png, :mathml # do nothing with these...for now?
      data
    end
  end

  def svg_to_base64(contents)
    "data:image/svg+xml;base64,#{Base64.strict_encode64(contents)}"
  end
end
