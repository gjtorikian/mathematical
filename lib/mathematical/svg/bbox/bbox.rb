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

    def check(data)
      MML.fetch_element(data.child).to_svg(data.child)
      svg.mml = data if data.SVGcanStretch("Vertical")
      this.sh = svg.h if svg.h > this.sh
      this.sd = svg.d if svg.d > this.sd
    end

    def stretch

    end
  end
end
