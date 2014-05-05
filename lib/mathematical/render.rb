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

    def render(text)
      raise(TypeError, "text must be a string!") unless text.is_a? String

      # TODO: figure out how to write svgs without the tempfile
      tempfile = Tempfile.new('mathematical-temp.svg')
      text = text.gsub(Mathematical::Parser::REGEX) do |maths|
        if maths =~ /^\$(?!\$)/
          just_maths = maths[1..-2]
          type = :inline
        elsif maths =~ /^\\\((?!\\\[)/
          just_maths = maths[2..-4]
          type = :inline
        elsif maths =~ /^\\\[(?!\\\[)/
          just_maths = maths[2..-4]
          type = :display
        elsif maths =~ /^\\begin(?!\\begin)/
          just_maths = maths[16..-15]
          type = :display
        end

        # this is the format itex2MML expects
        if type == :inline
          just_maths = "$#{just_maths}$"
        else
          just_maths = "$$#{just_maths}$$"
        end

        begin
          svg_content = @processer.process(just_maths, tempfile.path)
          raise RuntimeError unless svg_content.is_a? String
          svg_content = svg_content[xml_header.length..-1] # remove starting <?xml...> tag
        rescue RuntimeError => e # an error in the C code, probably a bad TeX parse
          $stderr.puts "#{e.message}: #{maths}"
          next(maths)
        end

        "<img class=\"#{named_type(type)}\" data-math-type=\"#{named_type(type)}\" src=\"#{svg_to_base64(svg_content)}\"/>"
      end
      tempfile.close
      tempfile.unlink
      text
    end

    def svg_to_base64(contents)
      "data:image/svg+xml;base64,#{Base64.strict_encode64(contents)}"
    end

    def named_type(type)
      "#{type.to_s}-math"
    end

    def xml_header
      "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    end
  end
end
