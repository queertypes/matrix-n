#include <vector>
using namespace std;

int main() {  
  vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for(auto iter = v.begin(), end = v.end(); iter != end; ++iter);

  return 0;
}