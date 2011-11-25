struct X {
  int x;
};

void F(X&& t) {}

int main()
{
  F(X());
  return 0;
}
