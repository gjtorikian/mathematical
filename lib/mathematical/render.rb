CONFIG =
{
  :inlineMathSymbols => [   # The start/stop pairs for in-line math
    ['$','$'],
    ['\\(','\\)']
  ],

  :displayMathSymbols => [  # The start/stop pairs for display math
    ['$$','$$'],
    ['\\[','\\]']
  ]
}

module Mathematical
  class Render
    def initialize(config)
      @config = CONFIG.merge(config)
    end

    def patternQuote(pattern)
      pattern.gsub(/([\^$(){}+*?\-|\[\]\:\\])/,'\\$1')
    end

    def endPattern(pattern)
      Regexp.new("#{patternQuote(pattern)}|\\\\.|[{}]","g");
    end

    def createPatterns
      @config[:inlineMathSymbols].each do |inline_symbol|
        starts << patternQuote(inline_symbol[0])
        match[inline_symbol[0].to_sym] = {
          :mode => "",
          :end => inline_symbol[1],
          :pattern => endPattern(inline_symbol[i][1])
        }
      end
      @config[:displayMathSymbols].each do |inline_symbol|
        starts << patternQuote(inline_symbol[0])
        match[inline_symbol[0].to_sym] = {
          :mode => "; mode=display",
          :end => inline_symbol[1],
          :pattern => endPattern(inline_symbol[i][1])
        }
      end

      unless starts.empty?
        parts << starts.sort{ |a, b| sortLength(a, b) }.join("|")
      end
      @start = Regexp.new(part.join("|"), "g")

      return parts.length > 0
    end

    def render(contents)
      contents
    end
  end
end
