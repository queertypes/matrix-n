#include <algorithm>
using namespace std;

int main()
{
  int arr[2] = {2,4};

  find_if(arr, arr+2, [](const int x) { return x > 2;} );

  return 0;
}
