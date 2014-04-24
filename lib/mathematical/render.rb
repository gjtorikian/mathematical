require 'rbconfig'
require 'fileutils'
require 'tmpdir'
require 'base64'

module Mathematical
  class Render
    DEFAULT_OPTS = {
      :font_size => 4
    }

    def initialize(opts = {})
      @config = DEFAULT_OPTS.merge(opts)
      @processer = Mathematical::Process.new(@config[:font_size])
    end

    def render(text)
      in_tmpdir do |tmpdir|
        x = 0
        text.gsub(Mathematical::Parser::REGEX) do |maths|
          if maths =~ /^\$(?!\$)/
            just_maths = '\textstyle ' << maths[1..-2]
            type = "inline"
          elsif maths =~ /^\\\((?!\\\[)/
            just_maths = '\textstyle ' << maths[2..-4]
            type = "inline"
          elsif maths =~ /^\\\[(?!\\\[)/
            just_maths = '\displaystyle ' << maths[2..-4]
            type = "display"
          elsif maths =~ /^\\begin(?!\\begin)/
            just_maths = '\displaystyle ' << maths[16..-15]
            type = "display"
          end

          path = "output#{x}.gif"

          begin
            @processer.process(just_maths, path)
          rescue RuntimeError
            return maths
          end

          x += 1
          depth = -5
          "<img class=\"#{type}-math\" style=\"vertical-align: #{depth}px\" src=\"data:image/gif;base64,#{gif_to_base64(path)}\"/>"
        end
      end
    end

    def gif_to_base64(path)
      File.open(path, 'r') { |image_file| Base64.encode64(image_file.read).gsub(/\n/, '') }
    end

private

    def in_tmpdir
      path = FileUtils.mkdir_p Dir.tmpdir
      yield path
    ensure
      FileUtils.rm_rf( path )
    end
  end
end
