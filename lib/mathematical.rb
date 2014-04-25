require "./lib/mathematical/html/html"
require "./lib/mathematical/html/math"
require "./lib/mathematical/parser"
require "./lib/mathematical/render"
require "./lib/mathematical/version"

module Mathematical
  @html_doc = Nokogiri::HTML::Document.new

  # Raised when missing binaries for images rendering.
  class CommandNotFoundError < Exception; end

  # Raised when the contents could not be parsed
  class ParseError < Exception; end
end
