constexpr unsigned int
returnFive()
{
   return 5;
}

int main()
{
  int arr[5 + returnFive()];

  return 0;
}
