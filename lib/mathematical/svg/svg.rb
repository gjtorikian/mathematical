module Mathematical
  # loosely corresponds to SVG/output/jax.js
  class SVG
    SVGNS   = "http://www.w3.org/2000/svg"
    XLINKNS = "http://www.w3.org/1999/xlink"

    CONFIG = {
      :styles => {
      #   ".MathJax_SVG": => {
      #     "display": => "inline",
      #     "font-style": => "normal",
      #     "font-weight": => "normal",
      #     "line-height": => "normal",
      #     "font-size": => "100%",
      #     "font-size-adjust": => "none",
      #     "text-indent": => 0,
      #     "text-align": => "left",
      #     "text-transform": => "none",
      #     "letter-spacing": => "normal",
      #     "word-spacing": => "normal",
      #     "word-wrap": => "normal",
      #     "white-space": => "nowrap",
      #     "float": => "none",
      #     "direction": => "ltr",
      #     border: => 0, padding: => 0, margin: => 0
      #   },
      #
      #   ".MathJax_SVG_Display": => {
      #     position: => "relative",
      #     display: => "block",
      #     width: => "100%"
      #   },
      #
      #   ".MathJax_SVG *": => {
      #     transition: => "none",
      #     "-webkit-transition": => "none",
      #     "-moz-transition": => "none",
      #     "-ms-transition": => "none",
      #     "-o-transition": => "none"
      #   },
      #
      #   ".mjx-svg-href": => {
      #     fill: => "blue", stroke: => "blue"
      #   },
      #
      #   ".MathJax_SVG_Processing": => {
      #     visibility: => "hidden", position: => "absolute", top: => 0, left: => 0,
      #     width: => 0, height: => 0, overflow: => "hidden", display: => "block"
      #   },
      #   ".MathJax_SVG_Processed": => {display: => "none!important"},
      #
      #   ".MathJax_SVG_ExBox": => {
      #     display: => "block", overflow: => "hidden",
      #     width: => "1px", height: => "60ex"
      #   },
      #
      #   "#MathJax_SVG_Tooltip": => {
      #     position: => "absolute", left: => 0, top: => 0,
      #     width: => "auto", height: => "auto",
      #     display: => "none"
      #   }
      }
    }

    TeX = {
      :x_height => 430.554,
      :quad => 1000,
      :num1 => 676.508,
      :num2 => 393.732,
      :num3 => 443.73,
      :denom1 => 685.951,
      :denom2 => 344.841,
      :sup1 => 412.892,
      :sup2 => 362.892,
      :sup3 => 288.888,
      :sub1 => 150,
      :sub2 => 247.217,
      :sup_drop => 386.108,
      :sub_drop => 50,
      :delim1 => 2390,
      :delim2 => 1000,
      :axis_height => 250,
      :rule_thickness => 60,
      :big_op_spacing1 => 111.111,
      :big_op_spacing2 => 166.666,
      :big_op_spacing3 => 200,
      :big_op_spacing4 => 600,
      :big_op_spacing5 => 100,
      :scriptspace => 100,
      :nulldelimiterspace => 120,
      :delimiterfactor => 901,
      :delimitershortfall => 100,   # originally 300,
      :min_rule_thickness => 1.25,  # in pixels
      :min_root_space =>      1.5     # in pixels
    }

    MATHSPACE = {
      :veryverythinmathspace => 1/18,
      :verythinmathspace => 2/18,
      :thinmathspace => 3/18,
      :mediummathspace => 4/18,
      :thickmathspace => 5/18,
      :verythickmathspace => 6/18,
      :veryverythickmathspace => 7/18,
      :negativeveryverythinmathspace => -1/18,
      :negativeverythinmathspace => -2/18,
      :negativethinmathspace => -3/18,
      :negativemediummathspace => -4/18,
      :negativethickmathspace => -5/18,
      :negativeverythickmathspace => -6/18,
      :negativeveryverythickmathspace => -7/18
    }

    BIGDIMEN = 10000000

    def initialize(opts)
      if !opts[:font].nil? && opts[:font] != "Auto"
        case opts.font
        when "TexWeb"
          @font_in_use = "TeX"
        when "STIX-Web"
          @font_in_use = "STIXWeb"
        when "Asana-Math"
          @font_in_use = "AsanaMathWeb"
        when "Gyre-Pagella"
          @font_in_use = "GyrePagellaWeb"
        when "Gyre-Termes"
          @font_in_use = "GyreTermesWeb"
        when "Latin-Modern"
          @font_in_use = "LatinModernWeb"
        when "Neo-Euler"
          @font_in_use = "NeoEulerWeb"
        else
          @font_in_use = "TeX"
        end
      else
        @font_in_use = "TeX"
      end
      # this.fontDir += "/" + this.fontInUse;
      # if (!this.require) {this.require = []}
      # this.require.push(this.fontDir+"/fontdata.js");

      @options = opts

      # MathJax does some DOM magic via Startup()
      @default_ex = 7.183333333333334
      @default_width = 1169
      @cwidth = 85 * @default_width
    end

    def pre_translate
      linebreak = @options[:linebreaks][:automatic]
      width = @options[:linebreaks][:width]

      if linebreak
        relwidth = !(width.match(/^\s*(\d+(\.\d*)?%\s*)?container\s*$/)).nil?
        if relwidth
          width = width.replace(/\s*container\s*/,"")
        else
          maxwidth = @default_width
        end
        width = "100%" if width == ""
      else
        maxwidth = 100000
      end

      @line_width = (linebreak ? self.length2em(width,1,maxwidth/@default_ex) : 1000000)
    end

    def translate(document)
      linebreak_width = @line_width * 1000
      @mml = MML.new
      MML.fetch_element(document.child).to_svg(document.child)
    end

    def post_translate

    end

    def self.length2em(length,mu,size = nil)
      length = String(length) if !length.is_a? String
      return "" if length.empty?
      return 1000 if length == MML.SIZE.NORMAL
      return 2000 if length == MML.SIZE.BIG
      return 710 if length == MML.SIZE.SMALL
      return BIGDIMEN if length == "infinity"
      return 1000 * self.MATHSPACE[length.to_sym] if length.match(/mathspace$/)

      match = length.match(/^\s*([-+]?(?:\.\d+|\d+(?:\.\d*)?))?(pt|em|ex|mu|px|pc|in|mm|cm|%)?/)
      m = (match[1]||"1").to_f * 1000
      unit = match[2]
      size = 1000 if size.nil?
      mu = 1 if mu.nil?
      return m if unit == "em"
      return m * self.TeX.x_height/1000 if unit == "ex"
      return m / 100 * size / 1000 if unit == "%"
      return m / @em if unit == "px"
      return m / 10 if unit == "pt"                             # 10 pt to an em
      return m * 1.2 if unit == "pc"                            # 12 pt to a pc
      return m * this.pxPerInch / @em if unit == "in"
      return m * this.pxPerInch / @em / 2.54 if unit == "cm" # 2.54 cm to an inch
      return m * this.pxPerInch / @em / 25.4 if unit == "mm" # 10 mm to a cm
      return m / 18 * mu if unit == "mu"

      return m*size / 1000  # relative to given size (or 1em as default)
    end

    def self.resulting_doc
      @resulting_doc ||= Nokogiri::XML::Document.new
    end

    def get_scale
      1
    end
  end
end
