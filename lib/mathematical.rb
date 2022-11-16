# frozen_string_literal: true

require "mathematical/mathematical"

require "mathematical/configuration"
require "mathematical/corrections"
require "mathematical/validator"
require "mathematical/version"

require "base64"

class Mathematical
  include Corrections
  include Validator

  DEFAULT_OPTS = {
    ppi: 72.0,
    zoom: 1.0,
    base64: false,
    maxsize: 0,
    format: :svg,
    delimiter: [:DOLLAR, :DOUBLE],
  }

  XML_HEADER = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"

  MATH_MATCH = %r{<math xmlns.+?</math>}m

  def initialize(options = {})
    @config = DEFAULT_OPTS.merge(options)

    validate_config(@config)

    @config[:formatInt] = FORMAT_TYPES.index(@config[:format])

    @config[:delimiter] = if @config[:delimiter].is_a?(Symbol)
      Configuration::Delimiters.to_h[@config[:delimiter]]
    else
      @config[:delimiter].map do |delim|
        Configuration::Delimiters.to_h[delim]
      end.inject(0, :|)
    end

    @processer = Mathematical::Process.new(@config)
  end

  def parse(maths)
    maths = validate_content(maths)
    result_data = @processer.process(maths, RENDER_TYPES.find_index(:parse))
    result(result_data)
  end
  # TODO: deprecate this?
  alias_method :render, :parse

  def filter(maths)
    maths = validate_content(maths)
    result_data = @processer.process(maths, RENDER_TYPES.find_index(:filter))
    result(result_data)
  end

  def text_filter(maths)
    maths = validate_content(maths)
    widths = []
    heights = []
    result_data = @processer.process(maths, RENDER_TYPES.find_index(:text_filter))
    # TODO: can/should be optimized to not do two calls here, but I am thinking
    # about moving to Rust and don't have time to write safe C...
    if result_data[:data] && @config[:format] != :mathml
      result_data[:data].gsub!(MATH_MATCH) do |_match|
        result = @processer.process(maths, RENDER_TYPES.find_index(:parse))
        widths << result[:width]
        heights << result[:height]
        result[:data]
      end

      result_data[:width] = widths
      result_data[:height] = heights
    end

    result(result_data)
  end

  def strict_filter(maths)
    maths = validate_content(maths)
    result_data = @processer.process(maths, RENDER_TYPES.find_index(:strict_filter))
    result(result_data)
  end

  def result(result_data)
    raise(RuntimeError) if !result_data.is_a?(Hash) && !result_data.is_a?(Array)

    if result_data.is_a?(Array)
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
      result_hash[:data] = result_hash[:data].gsub(XML_HEADER, "")
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
