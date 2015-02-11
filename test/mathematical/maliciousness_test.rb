require "test_helper"

class Mathematical::MaliciousnessTest < Test::Unit::TestCase

  def test_it_does_not_error_on_unrecognized_commands
    render = Mathematical.new
    output = nil
    # In mtex2MML, we raise a ParseError, but Mathematical suppresses it and returns the string.
    assert_nothing_raised { output = render.render('$not__thisisnotreal$') }
    assert output == '$not__thisisnotreal$'
  end

  def test_it_does_not_blow_up_on_bad_arguments
    # need to pass a hash here
    assert_raise TypeError do
      render = Mathematical.new("not a hash")
    end

    # need to pass a string here
    render = Mathematical.new
    assert_raise TypeError do
      Mathematical.new.render(123)
    end
  end

  def test_it_does_not_blow_up_on_bad_options
    assert_raise TypeError do
      render = Mathematical.new({:ppi => "not a number"})
    end

    assert_raise TypeError do
      render = Mathematical.new({:zoom => "not a number"})
    end

    assert_raise TypeError do
      render = Mathematical.new({:maxsize => "not a number"})
    end

    assert_raise TypeError do
      render = Mathematical.new({:maxsize => -23})
    end

    assert_raise TypeError do
      render = Mathematical.new({:maxsize => 5.3})
    end

    assert_raise TypeError do
      render = Mathematical.new({:format => 123})
    end

    assert_raise TypeError do
      render = Mathematical.new({:format => "something amazing"})
    end

    assert_raise Mathematical::MaxsizeError do
      render = Mathematical.new({:maxsize => 2})
      render.render('$a \ne b$')
    end

    assert_nothing_raised RangeError do
      render = Mathematical.new({:maxsize => 2147483647}) # signed long max
      render.render('$a \ne b$')
    end

    assert_raise RangeError do
      render = Mathematical.new({ :maxsize => 4_294_967_295 }) # unsigned long max
      render.render('$a \ne b$')
    end
  end

  def test_it_does_not_blow_up_on_bad_input
    assert_raise TypeError do
      Mathematical.new.render(23)
    end

    assert_raise ArgumentError do
      Mathematical.new.render('No dollars')
    end

    assert_raise ArgumentError do
      array = %w(foof poof)
      Mathematical.new.render(array)
    end

    assert_raise ArgumentError do
      array = ['$foof$', nil, '$poof$']
      Mathematical.new.render(array)
    end
  end

  def test_it_returns_unmodified_string_for_max_parsing
    render = Mathematical.new
    output = nil
    # Much like above, this fails in mtx2MML, but should do nothing here
    text = '$\Huge \sqrt\sqrt\sqrt\sqrt\sqrt\sqrt\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{\sqrt{}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}'
    assert_nothing_raised { output = render.render(text) }
    assert output == text
  end

  def test_it_parses_all_possible_array_elements
    render = Mathematical.new
    array = ['$foof$', '$/this___istotallyfake$', '$poof$']
    output = nil

    _, err = capture_subprocess_io do
      output = render.render(array)
    end

    assert_equal 3, output.length
    assert_equal Hash, output.first.class
    assert_equal Hash, output.last.class

    assert_equal '$/this___istotallyfake$', output[1][:data]
    assert_equal Mathematical::ParseError, output[1][:exception].class
    assert_match 'Failed to parse mtex', output[1][:exception].message

    # array errors also output to STDERR
    assert_match /Failed to parse mtex/, err
  end

  def test_it_passes_a_legible_error_for_maxsize
    output = nil
    render = Mathematical.new({:maxsize => 2})

    _, err = capture_subprocess_io do
      output = render.render(['$a \ne b$'])
    end

    assert_equal 1, output.length

    assert_equal '$a \ne b$', output[0][:data]
    assert_equal Mathematical::MaxsizeError, output[0][:exception].class
    assert_match 'Size of latex string is greater than the maxsize', output[0][:exception].message

    # array errors also output to STDERR
    assert_match /Size of latex string is greater than the maxsize/, err
  end
end
