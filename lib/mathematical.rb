require "mathematical/parser"
require "mathematical/render"
require "mathematical/version"

module Mathematical
  # Raised when missing binaries for images rendering.
  class CommandNotFoundError < Exception; end
end
