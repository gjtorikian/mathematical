require "test_helper"

class Mathematical::BasicTest < Test::Unit::TestCase

  def test_it_has_a_version
    assert Mathematical::VERSION
  end

  def test_it_errors_when_missing_commands
    render_stub = Mathematical::Render.new
    render_stub.stubs(:missing_commands).returns(["dvipng"])
    assert_raise(Mathematical::CommandNotFoundError) { render_stub.render("$a \\ne b$") }
  end
end
