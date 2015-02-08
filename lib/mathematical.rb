require 'mathematical/mathematical'

require 'mathematical/corrections'
require 'mathematical/version'

require 'fileutils'
require 'base64'
require 'tempfile'

class Mathematical
  include Corrections

  FORMAT_TYPES = %w(svg png mathml)

  DEFAULT_OPTS = {
    ppi: 72.0,
    zoom: 1.0,
    base64: false,
    maxsize: 0,
    format: 'svg'
  }

  XML_HEADER = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"

  def initialize(opts = {})
    @config = DEFAULT_OPTS.merge(opts)

    validate_config

    @config[:formatInt] = FORMAT_TYPES.index(@config[:format])

    @processer = Mathematical::Process.new(@config)
  end

  def validate_config
    fail(TypeError, 'maxsize must be an integer!') unless @config[:maxsize].is_a? Fixnum
    fail(TypeError, 'maxsize cannot be less than 0!') if @config[:maxsize] < 0
    fail(TypeError, 'format must be a string!') unless @config[:format].is_a? String
    fail(TypeError, "format type must be one of the following formats: #{FORMAT_TYPES.join(', ')}") unless FORMAT_TYPES.include?(@config[:format])
  end

  def render(maths)
    maths = validate_content(maths)

    begin
      data_hash = @processer.process(maths)
      fail RuntimeError unless data_hash

      case @config[:format]
      when 'svg'
        # remove starting <?xml...> tag
        data_hash['svg'] = data_hash['svg'][XML_HEADER.length..-1]
        data_hash['svg'] = svg_to_base64(data_hash['svg']) if @config[:base64]
        data_hash
      when 'png', 'mathml'
        data_hash
      end
    rescue ParseError, DocumentCreationError, DocumentReadError => e
      # an error in the C code, probably a bad TeX parse
      $stderr.puts "#{e.message}: #{maths}"
      maths
    end
  end

  def validate_content(maths)
    if maths.is_a? String
      maths = maths.strip
      fail(ArgumentError, 'input must be in tex format (`$...$` or `$$...$$`)!') unless valid_math_string(maths)
    elsif maths.is_a? Array
      unless maths.all? { |m| m.is_a?(String) && valid_math_string(m) }
        fail(ArgumentError, 'every element in array must be a string in tex format (`$...$` or `$$...$$`)!')
      end
    else
      fail(TypeError, 'input must be a string or an array!')
    end

    apply_corrections(maths)
  end

  private

  def valid_math_string(maths)
    maths =~ /\A\${1,2}/
  end

  def svg_to_base64(contents)
    "data:image/svg+xml;base64,#{Base64.strict_encode64(contents)}"
  end
end
