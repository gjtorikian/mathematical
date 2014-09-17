module Mathematical
  module Corrections

    def apply_corrections(maths)
      maths = adjust_slashes(maths)
      maths = adjust_alignment(maths)
      maths = adjust_frac(maths)
    end

    # seems to be a bug in itex@1.5.1 where the "Vertical spacing and page breaks in multiline display" (\\)
    # do not work, and yield an "unknown character" error
    def adjust_slashes(maths)
      maths.gsub(/\\\\/, "\\\\\\\\")
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
  end
end
