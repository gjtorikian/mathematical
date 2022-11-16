# frozen_string_literal: true

require "ruby-enum"

class Configuration
  class Delimiters
    include Ruby::Enum

    define :DEFAULT, 0
    define :DOLLAR, 1
    define :DOUBLE, 2
    define :PARENS, 4
    define :BRACKETS, 8
    define :ENVIRONMENTS, 16

    class << self
      def option_exists?(option)
        unless Delimiters.key?(option)
          raise(TypeError, "delimiter type does not exist: #{option}")
        end
      end
  end
  end
end
