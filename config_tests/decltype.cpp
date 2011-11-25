template <typename L, typename R>
auto add(const L& lhs, const R& rhs) -> decltype(lhs+rhs)
{
  return lhs + rhs;
}

int main()
{
  add(1, 2.0);

  return 0;
}
