require 'nokogiri'
require 'itextomml'

module Mathematical
  class Render
    DEFAULT_OPTS = {
      :font => "Auto",
      :linebreaks => {
        #  This controls the automatic breaking of expressions:
        #  when false, only process linebreak="newline",
        #  when true, line breaks are inserted automatically in long expressions.

        :automatic => false,

        # This controls how wide the lines of mathematics can be
        #
        # Use an explicit width like "30em" for a fixed width.
        # Use "container" to compute the size from the containing element.
        # Use "nn% container" for a portion of the container.
        # Use "nn%" for a portion of the window size.
        #
        # The container-based widths may be slower, and may not produce the
        # expected results if the layout width changes due to the removal
        # of previews or inclusion of mathematics during typesetting.

        :width => "container"
        }
    }

    def initialize(opts = {})
      @options = DEFAULT_OPTS.merge(opts)
      @itex = Itex2MML::Parser.new
      @svg = SVG.new(@options)
    end


    def render(text)
      text.gsub(Mathematical::Parser::REGEX) do |maths|
        if maths =~ /^\$(?!\$)/
          undecorated_maths = maths[1..-2]
          type = :inline
        elsif maths =~ /^\\\((?!\\\[)/
          undecorated_maths = maths[2..-4]
          type = :inline
        elsif maths =~ /^\\\[(?!\\\[)/
          undecorated_maths = maths[2..-4]
          type = :display
        elsif maths =~ /^\\begin(?!\\begin)/
          undecorated_maths = maths[16..-15]
          type = :display
        end

        tex = @itex.inline_filter('a')
        @tex_doc = Nokogiri::XML(tex)

        @svg.pre_translate
        @svg.translate(@tex_doc)

        tex
      end
    end
  end
end
