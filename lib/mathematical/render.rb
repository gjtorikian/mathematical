require 'fileutils'

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

      text.gsub(Mathematical::Parser::REGEX) do |maths|
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
          FileUtils.touch('file.svg')
          @processer.process(just_maths, 'file.svg')
          contents = File.read('file.svg')
          File.delete('file.svg')
        rescue RuntimeError => e # some error in the C code
          $stderr.puts e.message
          return just_maths
        end

        # if error = data.match("<error>(.+?)</error>")
        #   if data.match("<message>Unrecogni[sz]?ed command")
        #     return maths
        #   else
        #     raise ParseError, error
        #   end
        # elsif filename = data.match("<md5>(.+?)</md5>")
        #   filename = filename[1]
        #   depth = data.match("<depth>(.+?)</depth>")[1]
        #   "<img class=\"#{type.to_s}-math\" style=\"vertical-align: #{depth}px\" src=\"data:image/png;base64,#{png_to_base64(File.join(tmpdir, "#{filename}.png"))}\"/>"
        # end
      end
    end
  end
end
