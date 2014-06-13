require 'fileutils'
require 'base64'
require 'tempfile'

module Mathematical
  class Render
    DEFAULT_OPTS = {
      :ppi => 72.0,
      :zoom => 1.0,
      :base64 => false,
      :maxsize => 0
    }

    def initialize(opts = {})
      @config = DEFAULT_OPTS.merge(opts)
      raise(TypeError, "maxsize must be an integer!") unless @config[:maxsize].is_a? Fixnum
      raise(TypeError, "maxsize cannot be less than 0!") if @config[:maxsize] < 0
      @processer = Mathematical::Process.new(@config)
    end

    def render(maths)
      raise(TypeError, "text must be a string!") unless maths.is_a? String
      raise(ArgumentError, "text must be in itex format (`$...$` or `$$...$$`)!") unless maths =~ /\A\${1,2}/

      # seems to be a bug in itex@1.5.1 where the "Vertical spacing and page breaks in multiline display" (\\)
      # do not work, and yield an "unknown character" error
      maths.gsub!(/\\\\/, "\\\\\\\\")

      maths.gsub!(/\\begin\{align\}/, "\\begin{aligned}")
      maths.gsub!(/\\end\{align\}/, "\\end{aligned}")

      begin
        raise RuntimeError unless svg_hash = @processer.process(maths)
        svg_hash["svg"] = svg_hash["svg"][xml_header.length..-1] # remove starting <?xml...> tag
        svg_hash["svg"] = svg_to_base64(svg_hash["svg"]) if @config[:base64]
        svg_hash
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
