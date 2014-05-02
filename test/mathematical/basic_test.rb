require "test_helper"

class Mathematical::BasicTest < Test::Unit::TestCase

  def test_it_has_a_version
    assert Mathematical::VERSION
  end

  def test_it_does_not_error_on_unrecognized_commands
    render = Mathematical::Render.new
    output = nil
    assert_nothing_raised { output = render.render('$\align$') }
    assert_equal output, '$\align$'
  end

  def test_it_does_not_blow_up_on_bad_arguments
    # need to pass a hash here
    assert_raise TypeError do
      render = Mathematical::Render.new("not a hash")
    end

    # need to pass a string here
    render = Mathematical::Render.new
    assert_raise TypeError do
      Mathematical::Render.new.render(123)
    end
  end

  def test_it_does_not_blow_up_on_bad_options
    assert_raise TypeError do
      render = Mathematical::Render.new({:ppi => "not a number"})
    end

    assert_raise TypeError do
      render = Mathematical::Render.new({:zoom => "not a number"})
    end
  end
end
