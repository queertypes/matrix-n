struct X {
  X& operator=(const X&& other) {}
};

int main()
{
  return 0;
}
