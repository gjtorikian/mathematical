# frozen_string_literal: true

class Mathematical
  module Corrections
    def apply_corrections(maths)
      adjust_lt_gt(maths)
    end

    # from the itex website: http://bit.ly/1Et74ed
    # It is possible (though probably not recommended) to insert MathML markup
    # inside itex equations. So "<" and ">" are significant.
    # To obtain a less-than or greater-than sign, you should use \lt or \gt, respectively.
    def adjust_lt_gt(maths)
      maths.gsub(/</, '\lt').gsub(/>/, '\gt')
    end
  end
end
