require "./lib/mathematical/parser"
require "./lib/mathematical/render"
require "./lib/mathematical/version"
require './lib/mathematical.bundle'

module Mathematical
  # Raised when missing binaries for images rendering.
  class CommandNotFoundError < Exception; end

  # Raised when the contents could not be parsed
  class ParseError < Exception; end
end
