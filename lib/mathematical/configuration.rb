require 'ruby-enum'

class Configuration
  class Delimiters
    include Ruby::Enum

    define :default, 0
    define :dollar, 1
    define :double, 2
    define :parens, 4
    define :brackets, 8
    define :environments, 16

    def self.option_exists?(option)
      unless Delimiters.keys.include?(option)
        fail TypeError, "delimiter type does not exist: #{option}"
      end
    end
  end
end
