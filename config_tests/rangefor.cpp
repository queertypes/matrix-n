int main()
{
  int arr[5] = {1,2,3,4,5};

  for(int& x : arr){
    x *= 2;
  }

  return 0;
}
