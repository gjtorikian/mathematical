require 'mathematical/mathematical'

require 'mathematical/corrections'
require 'mathematical/validator'
require 'mathematical/version'

require 'base64'

class Mathematical
  include Corrections
  include Validator

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

    validate_config(@config)

    @config[:formatInt] = FORMAT_TYPES.index(@config[:format])

    @processer = Mathematical::Process.new(@config)
  end

  def render(maths)
    maths = validate_content(maths)

    result_data = @processer.process(maths)
    fail RuntimeError if !result_data.is_a?(Hash) && !result_data.is_a?(Array)

    if result_data.is_a? Array
      result_data.map { |d| format_data(d) }
    else
      format_data(result_data)
    end
  end

  private

  def format_data(result_hash)
    # we passed in an array of math, and found an unprocessable element
    return result_hash if result_hash[:exception]

    case @config[:format]
    when :svg
      # remove starting <?xml...> tag
      result_hash[:data] = result_hash[:data][XML_HEADER.length..-1]
      result_hash[:data] = svg_to_base64(result_hash[:data]) if @config[:base64]

      result_hash
    when :png, :mathml # do nothing with these...for now?
      result_hash
    end
  end

  def svg_to_base64(contents)
    "data:image/svg+xml;base64,#{Base64.strict_encode64(contents)}"
  end
end
