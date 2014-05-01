module Mathematical
  class MrowElem < MML
    TEX_CLASS = 0

    def self.to_svg(node)
      svg = BBox.new()
      MML.handleSpace(self, svg)

      for child in node.children
        unless child.child.nil?
          svg.check(child.child)
        end
        box.add(MML.fetch_element(node.child).to_svg(node.child))
      end
    end
  end
end
