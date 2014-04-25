require 'nokogiri'
require 'itextomml'

module Mathematical
  class Render
    DEFAULT_OPTS = {
      :matchFontHeight => true,
      :scale => 100,
      :minScaleAdjust => 50,
      :linebreaks => {
        :automatic => false,
        :width => "container"
      },
    }

    def initialize(opts = {})
      @options = DEFAULT_OPTS.merge(opts)
      @itex = Itex2MML::Parser.new
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

        tex = @itex.inline_filter("$a$")
        @tex_doc = Nokogiri::XML(tex)

        puts Mathematical::HTML.fetch(@tex_doc.root.name).to_html(@tex_doc.root)
        # .each do |node|
        #   puts node
        #   if node.name == 'entry'
        #     node.children.each do |sub_e|
        #       at = sub_e.inner_text if sub_e.name == 'published'
        #       id = sub_e.inner_text if sub_e.name == 'id'
        #     end
        #   end

        # end
        tex
        # span = div = @doc.create_element("span", :class => "mathematical")
        # div.set_attribute("role", "textbox")
        # ex = 7.183333333333334
        # em = 16

        # scale = (@options[:matchFontHeight] ? ex/Mathematical::TeX[:x_height]/em : 1)
        # scale = ([@options[:minScaleAdjust]/100, scale].max * @options[:scale]).floor
        # @html.scale = scale/100
        # @html.fontSize = "#{scale}%"
        # @html.em = @html.outerEm = em
        # @em = em * scale/100
        # @html.ex = ex
        # linebreak = @options[:linebreaks][:automatic]
        # width = @options[:linebreaks][:width]
        # maxwidth = 100000

        # @html.lineWidth = (linebreak ? Mathematical::length2em(width, 1, maxwidth/em) : 1000000)
      end
    end
  end
end
