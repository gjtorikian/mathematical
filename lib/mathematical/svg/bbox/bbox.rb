module Mathematical
  class BBox < SVG
    def initialize(attrs)
      @type = "g"
      @h = @d = -BIGDIMEN
      @H = @D = 0
      @x = @y = 0
      @scale = 0
      @n = 0
      @element = create_element(attrs)
    end

    def create_element(attrs = {})
      if @type.is_a? String
        element = Nokogiri::XML::Node.new(@type, SVG.resulting_doc)
        element.add_namespace_definition(nil, SVGNS)
      else
        element = type
      end

      attrs.each { |key, value| element.set_attribute(key, value) }

      element
    end

    def add(svg, dx, dy, forcew, infront = nil)

    end
  end
end
