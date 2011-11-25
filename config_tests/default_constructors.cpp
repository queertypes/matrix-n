struct Test
{
  Test() = default;
  Test(const Test&) = delete;
  Test& operator=(const Test&) = delete;
  ~Test() = default;
};

int main()
{
  Test x;

  return 0;
}
