require 'rbconfig'

module Mathematical
  class Render
    def initialize
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
    end


    def render(contents)
      run_blahtex
    end

    def run_blahtex #(tex, args)
      IO.popen(["bin/blahtex/#{@os}/blahtex", "--help"].join(' '), 'w+') do |blahtex|
        # blahtex.write tex
        # blahtex.close_write

        output = blahtex.read
        # blahtex.close_read

        # raise "Error running blahtex" unless $?.success?

        output
      end
    end
  end
end
