module Mathematical
  class MML
    INHERIT = "_inherit_"
    AUTO =  "_auto_"
    SIZE = {
      :INFINITY => "infinity",
      :SMALL => "small",
      :NORMAL => "normal",
      :BIG => "big"
    }

    def initialize(*args)
      @data = []
      @type = "base"
      @isToken = false,
      @defaults = {
        mathbackground: INHERIT,
        mathcolor: INHERIT,
        dir: INHERIT
      }
      @linebreakContainer = false
      append(args)
    end

    def append(*args)
      if !@inferRow.nil? && !@data.empty?
        @data[0].append(@data[0],args)
      else
        for a in args
          set_data(@data.length,a)
        end
      end
    end

    def set_data(a, b)

    end

    def math_elem
      @math_elem ||= MathElem.new
    end
  end
end
