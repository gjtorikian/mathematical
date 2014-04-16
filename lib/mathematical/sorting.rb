module Mathematical
  def sortLength(a, b)
    return b.length - a.length if a.length !== b.length
    return (a == b ? 0 : (a < b ? -1 : 1))
  end
end
