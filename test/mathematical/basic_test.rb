require "test_helper"

class Mathematical::BasicTest < Test::Unit::TestCase

  def test_it_has_a_version
    assert Mathematical::VERSION
  end

  def test_it_does_not_error_on_unrecognized_commands
    render_stub = Mathematical::Render.new
    output = nil
    assert_nothing_raised { output = render_stub.render('$\h$') }
    assert_equal output, '$\h$'
  end
end
