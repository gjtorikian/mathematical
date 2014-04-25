module Mathematical
  class HTML
    def self.fetch(name=nil)
      return Mathematical::HTML.subclasses if name.nil?
      Mathematical::HTML.subclasses.fetch(name)
    end

    def self.subclasses
      classes = {}

      ObjectSpace.each_object(Class) do |c|
        next unless c.superclass == self
        node_name = c.to_s.split(/::/)[1].downcase
        classes[node_name] = c
      end

      classes
    end
  end
end