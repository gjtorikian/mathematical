require 'fileutils'
require 'base64'
require 'tempfile'

module Mathematical
  class Render
    DEFAULT_OPTS = {
      :ppi => 72.0,
      :zoom => 1.0
    }

    def initialize(opts = {})
      raise(TypeError, "opts must be a hash!") unless opts.is_a? Hash

      @config = DEFAULT_OPTS.merge(opts)
      begin
        @processer = Mathematical::Process.new(@config)
      rescue TypeError => e # some error in the C code
        raise
      end
    end

    def render(maths)
      raise(TypeError, "text must be a string!") unless maths.is_a? String

      # TODO: figure out how to write svgs without the tempfile
      tempfile = Tempfile.new('mathematical-temp.svg')
      result = nil

      begin
        svg_content = @processer.process(maths, tempfile.path)
        raise RuntimeError unless svg_content.is_a? String
        result = svg_content[xml_header.length..-1] # remove starting <?xml...> tag
      rescue RuntimeError => e # an error in the C code, probably a bad TeX parse
        $stderr.puts "#{e.message}: #{maths}"
        result = maths
      ensure
        tempfile.close
        tempfile.unlink
      end

      result
    end

    def xml_header
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    end
  end
end
