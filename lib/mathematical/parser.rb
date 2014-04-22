module Mathematical
  class Parser
    # https://stackoverflow.com/questions/14182879/regex-to-match-latex-equations
    REGEX = /
    (?<!\\)    # negative look-behind to make sure start is not escaped
    (?:       # start non-capture group for all possible match starts
        # group 1, match dollar signs only
        # single or double dollar sign enforced by look-arounds
        ((?<!\$)\${1,2}(?!\$))|
        # group 2, match escaped parenthesis
        (\\\()|
        # group 3, match escaped bracket
        (\\\[)|
        # group 4, match begin equation
        (\\begin\{equation\})
    )
    (.*?(\g<1>)?.*?)  # match everything in between including nested LaTeX equations
    (?<!\\)  # negative look-behind to make sure end is not escaped
        # if group 1 was start, match \1
        (?(1)(?<!\$)\1(?!\$)|
        # if group 2 was start, escaped parenthesis is end
        (?(2)\\\)|
        # if group 3 was start, escaped bracket is end
        (?(3)\\\]|
        # otherwise group 4 was start, match end equation
        \\end\{equation\}
    )))
    /x
  end
end
