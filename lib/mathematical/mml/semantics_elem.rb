module Mathematical
  class SemanticsElem < MML
    TEX_CLASS = 0

    def self.to_svg(node)
      svg = BBox.new()

      unless node.child.nil?
        MML.handleSpace(self, svg)
        box.add(MML.fetch_element(node.child).to_svg(node.child))
      end
    end
  end
end
