require 'rbconfig'
require 'fileutils'
require 'tmpdir'
require 'shellwords'
require 'base64'

module Mathematical
  class Render
    DEFAULT_OPTS = {
      :html_png_resolution => 200
    }

    def initialize(opts = {})
      @os ||= (
        host_os = RbConfig::CONFIG['host_os']
        case host_os
        when /darwin|mac os/
          "macosx"
        when /linux/
          "linux"
        else
          raise Error, "unknown os: #{host_os.inspect}"
        end
      )

      opts = DEFAULT_OPTS.merge(opts)
      @temp_dir = Dir.mktmpdir
      @args = [
              '--png',
              '--use-preview-package',
              # '--shell-dvipng',
              # "'dvipng -D #{Shellwords.shellescape opts[:html_png_resolution].to_s}'",
             ]
    end


    def render(text)
      in_tmpdir do |tmpdir|
        @args << "--temp-directory #{Shellwords.shellescape tmpdir.first}"
        @args << "--png-directory #{Shellwords.shellescape tmpdir.first}"

        text.gsub(Mathematical::Parser::REGEX) do |maths|
          if maths =~ /^\$(?!\$)/
            maths = maths[1..-2]
            type = :inline
          else
            type = :display
          end

          data = run_blahtex(maths, type)
          if filename = data.match("<md5>(.+?)</md5>")[1]
            "<img class=\"#{type.to_s}-math\" src=\"data:image/png;base64,#{png_to_base64(File.join(tmpdir, "#{filename}.png"))}\"/>"
          end
        end
      end
    end

    def run_blahtex(tex, type)
      raise CommandNotFoundError, "Required commands missing: #{missing_commands.join(', ')} in PATH. (#{ENV['PATH']})" unless missing_commands.empty?
      @args << '--displaymath' if type == :equation

      IO.popen(["bin/blahtex/#{@os}/blahtex", *@args].join(' '), 'w+') do |blahtex|
        blahtex.write tex
        blahtex.close_write

        output = blahtex.read
        blahtex.close_read

        raise "Error running blahtex" unless $?.success?

        output
      end
    end

    def png_to_base64(path)
      File.open(path, 'r') { |image_file| Base64.encode64(image_file.read).gsub(/\n/, '') }
    end

private

    # Check toolchain availability and returns array of missing tools
    def missing_commands
      commands = []
      commands << "dvipng" unless can_run?("dvipng -v")
      commands
    end

    # Trial command and check if return code is zero
    def can_run?(command)
      `#{command} 2>&1`
      $?.exitstatus.zero?
    end

    def in_tmpdir
      path = FileUtils.mkdir_p Dir.tmpdir
      yield path
    ensure
      FileUtils.rm_rf( path )
    end
  end
end
