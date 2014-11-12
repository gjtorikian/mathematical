require "test_helper"

class Mathematical::MaliciousnessTest < Test::Unit::TestCase

  def test_it_does_not_error_on_unrecognized_commands
    render = Mathematical::Render.new
    output = nil
    # In mtex2MML, we raise a ParseError, but Mathematical suppresses it and returns the string.
    assert_nothing_raised { output = render.render('$not__thisisnotreal$') }
    assert output == '$not__thisisnotreal$'
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

    assert_raise TypeError do
      render = Mathematical::Render.new({:maxsize => "not a number"})
    end

    assert_raise TypeError do
      render = Mathematical::Render.new({:maxsize => -23})
    end

    assert_raise TypeError do
      render = Mathematical::Render.new({:maxsize => 5.3})
    end

    assert_raise TypeError do
      render = Mathematical::Render.new({:format => 123})
    end

    assert_raise TypeError do
      render = Mathematical::Render.new({:format => "something amazing"})
    end

    assert_raise Mathematical::MaxsizeError do
      render = Mathematical::Render.new({:maxsize => 2})
      render.render('$a \ne b$')
    end

    assert_nothing_raised RangeError do
      render = Mathematical::Render.new({:maxsize => 2147483647}) # signed long max
      render.render('$a \ne b$')
    end

    assert_raise RangeError do
      render = Mathematical::Render.new({:maxsize => 4294967295}) # unsigned long max
      render.render('$a \ne b$')
    end
  end

  def test_it_does_not_blow_up_on_bad_input
    assert_raise TypeError do
      render = Mathematical::Render.new.render(23)
    end

    assert_raise ArgumentError do
      render = Mathematical::Render.new.render("No dollars")
    end
  end

  def test_it_returns_unmodified_string_for_max_parsing
    render = Mathematical::Render.new
    output = nil
    # Much like above, this fails in mtx2MML, but should do nothing here
    text = '$\Huge \sqrt\sqrt\sqrt\sqrt\sqrt\sqrt\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}'
    assert_nothing_raised { output = render.render(text) }
    assert output == text
  end
end
