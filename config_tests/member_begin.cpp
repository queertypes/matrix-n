#include <vector>

int main()
{
  std::vector<int> x = {1,2,3,4};

  for (auto i = std::begin(x), end = std::end(x); i != end; ++i);
}

