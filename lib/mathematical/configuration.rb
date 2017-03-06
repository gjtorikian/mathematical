require 'ruby-enum'

class Configuration
  class Delimiters
    include Ruby::Enum

    define :DEFAULT, 0
    define :DOLLAR, 1
    define :DOUBLE, 2
    define :PARENS, 4
    define :BRACKETS, 8
    define :ENVIRONMENTS, 16

    def self.option_exists?(option)
      unless Delimiters.keys.include?(option)
        fail TypeError, "delimiter type does not exist: #{option}"
      end
    end
  end
end
