module Mathematical
  class MathElem < MML
    def self.to_svg(node)
      box = BBox.new({
              :stroke => "black", :fill => "black", :"stroke-width" => 0,
              :transform => "matrix(1 0 0 -1 0 0)"
            })
      require 'pry'
      # binding.pry
      box.add(node.child, 0, 0, true)
    end
  end
end
