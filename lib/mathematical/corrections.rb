module Mathematical
  module Corrections

    def apply_corrections(maths)
      maths = adjust_alignment(maths)
      maths = adjust_frac(maths)
      maths = adjust_lt_gt(maths)
      maths = adjust_limits(maths)
    end

    # `{align}` *should* be valid, according to AMS-Latex, but it seems itex@1.5.1 does not like it.
    def adjust_alignment(maths)
      maths = maths.gsub(/\\begin\{align\}/, "\\begin{aligned}")
      maths.gsub(/\\end\{align\}/, "\\end{aligned}")
    end

    # seems like KaTeX/MathJax supports \frac\d\d, but itex does not
    def adjust_frac(maths)
      maths.gsub(/\\frac(\d)(\d)/, '\frac{\1}{\2}')
    end

    # from the itex website:
    # It is possible (though probably not recommended) to insert MathML markup
    # inside itex equations. So "<" and ">" are significant.
    # To obtain a less-than or greater-than sign, you should use \lt or \gt, respectively.
    def adjust_lt_gt(maths)
      maths.gsub(/</, '\lt').gsub(/>/, '\gt')
    end

    def adjust_limits(maths)
      maths.gsub(/\\int\\limits_/, '\int_')
    end
  end
end
