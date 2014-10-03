require 'fileutils'
require 'base64'
require 'tempfile'

module Mathematical
  class Render
    include Corrections

    FORMAT_TYPES = %w(svg png)

    DEFAULT_OPTS = {
      :ppi => 72.0,
      :zoom => 1.0,
      :base64 => false,
      :maxsize => 0,
      :format => "svg"
    }

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
      raise(ArgumentError, "text must be in itex format (`$...$` or `$$...$$`)!") unless maths =~ /\A\${1,2}/

      maths = apply_corrections(maths)

      begin
        case @config[:format]
        when "svg"
          raise RuntimeError unless svg_hash = @processer.process(maths)
          svg_hash["svg"] = svg_hash["svg"][xml_header.length..-1] # remove starting <?xml...> tag
          svg_hash["svg"] = svg_to_base64(svg_hash["svg"]) if @config[:base64]
          svg_hash
        when "png"
          puts "A PNG, cool."
        end
      rescue ParseError, DocumentCreationError, DocumentReadError => e # an error in the C code, probably a bad TeX parse
        $stderr.puts "#{e.message}: #{maths}"
        maths
      end
    end

private

    def xml_header
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    end

    def svg_to_base64(contents)
      "data:image/svg+xml;base64,#{Base64.strict_encode64(contents)}"
    end
  end
end
