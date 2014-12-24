require 'fileutils'
require 'base64'
require 'tempfile'

module Mathematical
  class Render
    include Corrections

    FORMAT_TYPES = %w(svg png mathml)

    DEFAULT_OPTS = {
      :ppi => 72.0,
      :zoom => 1.0,
      :base64 => false,
      :maxsize => 0,
      :format => "svg"
    }

    XML_HEADER = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"

    def initialize(opts = {})
      @config = DEFAULT_OPTS.merge(opts)

      raise(TypeError, "maxsize must be an integer!") unless @config[:maxsize].is_a? Fixnum
      raise(TypeError, "maxsize cannot be less than 0!") if @config[:maxsize] < 0
      raise(TypeError, "format must be a string!") unless @config[:format].is_a? String
      raise(TypeError, "format type must be one of the following formats: #{FORMAT_TYPES.join(', ')}") unless FORMAT_TYPES.include?(@config[:format])

      @processer = Mathematical::Process.new(@config)
    end

    def render(maths)
      raise(TypeError, "text must be a string!") unless maths.is_a? String
      maths = maths.strip
      raise(ArgumentError, "text must be in tex format (`$...$` or `$$...$$`)!") unless maths =~ /\A\${1,2}/

      maths = apply_corrections(maths)

      begin
        raise RuntimeError unless data_hash = @processer.process(maths)
        case @config[:format]
        when "svg"
          data_hash["svg"] = data_hash["svg"][XML_HEADER.length..-1] # remove starting <?xml...> tag
          data_hash["svg"] = svg_to_base64(data_hash["svg"]) if @config[:base64]
          data_hash
        when "png", "mathml"
          data_hash
        end
      rescue ParseError, DocumentCreationError, DocumentReadError => e # an error in the C code, probably a bad TeX parse
        $stderr.puts "#{e.message}: #{maths}"
        maths
      end
    end

private

    def svg_to_base64(contents)
      "data:image/svg+xml;base64,#{Base64.strict_encode64(contents)}"
    end
  end
end
