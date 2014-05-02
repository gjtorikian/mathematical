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
      tempfile = Tempfile.new('foo')
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
          status = @processer.process(just_maths, tempfile.path)
          raise RuntimeError unless status
          svg_content = File.open(tempfile.path, 'r') { |image_file| image_file.read }
          svg_content = svg_content.lines.to_a[1..-1].join
        rescue RuntimeError => e # an error in the C code, probably a bad TeX parse
          $stderr.puts e.message
          return just_maths
        end

        "<img class=\"#{named_type(type)}\" data-math-type=\"#{named_type(type)}\" src=\"data:image/svg+xml;base64,#{svg_to_base64(svg_content)}\"/>"
      end
      tempfile.close
      tempfile.unlink
      text
    end

    def svg_to_base64(contents)
      Base64.strict_encode64(contents)
    end

    def named_type(type)
      "#{type.to_s}-math"
    end
  end
end
