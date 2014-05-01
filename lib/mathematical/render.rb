module Mathematical
  class Render
    DEFAULT_OPTS = {

    }

    def initialize(opts = {})
      @config = DEFAULT_OPTS.merge(opts)
      @processer = Mathematical::Process.new(2)
    end


    def render(text)
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

        begin
          puts @processer.process(just_maths, "sss")
        rescue RuntimeError
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
