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

    LENGTH = {
      :VERYVERYTHINMATHSPACE => "veryverythinmathspace",
      :VERYTHINMATHSPACE => "verythinmathspace",
      :THINMATHSPACE => "thinmathspace",
      :MEDIUMMATHSPACE => "mediummathspace",
      :THICKMATHSPACE => "thickmathspace",
      :VERYTHICKMATHSPACE => "verythickmathspace",
      :VERYVERYTHICKMATHSPACE => "veryverythickmathspace",
      :NEGATIVEVERYVERYTHINMATHSPACE => "negativeveryverythinmathspace",
      :NEGATIVEVERYTHINMATHSPACE => "negativeverythinmathspace",
      :NEGATIVETHINMATHSPACE => "negativethinmathspace",
      :NEGATIVEMEDIUMMATHSPACE => "negativemediummathspace",
      :NEGATIVETHICKMATHSPACE => "negativethickmathspace",
      :NEGATIVEVERYTHICKMATHSPACE => "negativeverythickmathspace",
      :NEGATIVEVERYVERYTHICKMATHSPACE => "negativeveryverythickmathspace"
    }

    TEXCLASS = {
      :ORD =>   0,
      :OP =>    1,
      :BIN =>   2,
      :REL =>   3,
      :OPEN =>  4,
      :CLOSE => 5,
      :PUNCT => 6,
      :INNER => 7,
      :VCENTER => 8,
      :NONE =>   -1
    }

    TEXSPACELENGTH = [
        "",
        LENGTH.THINMATHSPACE,
        LENGTH.MEDIUMMATHSPACE,
        LENGTH.THICKMATHSPACE
    ]

    # See TeXBook Chapter 18 (p. 170)
    TEXSPACE = [
      [ 0,-1, 2, 3, 0, 0, 0, 1], # ORD
      [-1,-1, 0, 3, 0, 0, 0, 1], # OP
      [ 2, 2, 0, 0, 2, 0, 0, 2], # BIN
      [ 3, 3, 0, 0, 3, 0, 0, 3], # REL
      [ 0, 0, 0, 0, 0, 0, 0, 0], # OPEN
      [ 0,-1, 2, 3, 0, 0, 0, 1], # CLOSE
      [ 1, 1, 0, 1, 1, 1, 1, 1], # PUNCT
      [ 1,-1, 2, 3, 1, 0, 1, 1]  # INNER
    ]

    WHITELIST = %w(math semantics)

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

    def self.fetch_element(node)
      name = node.name
      return unless WHITELIST.include? name
      eval("#{node.name.to_s.capitalize}Elem")
    end

    def handle_space(elem, svg)
      space = tex_spacing(elem)
      unless space.empty?
        svg.x += SVG.length2em(space, SVG.get_scale / svg.scale)
      end
    end

    def tex_spacing(elem)
      prev = TEXCLASS.NONE
      tex = elem.TEX_CLASS || TEXCLASS.ORD
      return "" if prev == TEXCLASS.NONE || tex == TEXCLASS.NONE
      prev = TEXCLASS.ORD if prev == MML.TEXCLASS.VCENTER
      tex  = TEXCLASS.ORD if tex  == MML.TEXCLASS.VCENTER
      space = TEXSPACE[prev][tex]
      TEXSPACELENGTH[Math.abs(space)]
    end
  end
end
