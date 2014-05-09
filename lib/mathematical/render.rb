require 'fileutils'
require 'base64'
require 'tempfile'

module Mathematical
  class Render
    DEFAULT_OPTS = {
      :ppi => 72.0,
      :zoom => 1.0,
      :base64 => false
    }

    def initialize(opts = {})
      @config = DEFAULT_OPTS.merge(opts)
      @processer = Mathematical::Process.new(@config)
    end

    def render(maths)
      raise(TypeError, "text must be a string!") unless maths.is_a? String
      raise(ArgumentError, "text must be in itex format (`$...$` or `$$...$$`)!") unless maths =~ /\A\${1,2}/

      # TODO: figure out how to write SVGs without the tempfile
      tempfile = Tempfile.new('mathematical-temp.svg')
      begin
        raise RuntimeError unless @processer.process(maths, tempfile.path)
        svg_content = File.open(tempfile.path, 'r') { |image_file| image_file.read }
        svg_content = svg_content[xml_header.length..-1] # remove starting <?xml...> tag
        @config[:base64] ? svg_to_base64(svg_content) : svg_content
      rescue ParseError, DocumentCreationError => e # an error in the C code, probably a bad TeX parse
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
