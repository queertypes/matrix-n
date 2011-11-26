#include <string>
#include <gtest/gtest.h>
#include <vector>
using namespace std;

TEST(test_string, string_compare)
{
  ASSERT_EQ("fis", "fis");
}

TEST(test_vector, vector_compare)
{
  vector<int> x = {1,2,3,4};
  vector<int> y = {1,2,3,4};

  ASSERT_EQ(x, y);  
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

