require "test_helper"

class Mathematical::BasicTest < Test::Unit::TestCase

  def test_it_has_a_version
    assert Mathematical::VERSION
  end

  def test_multiple_calls
    render = Mathematical.new
    render.render('$\pi$')
    output = render.render('$\pi$')['svg']
    assert_equal 1, output.scan(/<svg/).size, 'should only contain one svg'
  end

end
