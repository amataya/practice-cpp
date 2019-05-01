//
// Given an array and integer m, had to find average of m groups in O(n).
// Example: A[] = {1, 2, 3, 4, 5}, m = 3
// Ans : avg(1,2,3), avg(2,3,4), avg(3,4,5)
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<int> average_of_groups(vector<int> numbers, int m)
{
    vector<int> averages(numbers.size() - m + 1);
    int sum = 0, count = 0, index = 0;
    for (int i = 0; i < numbers.size(); ++i)
    {
        sum += numbers[i];
        ++count;
        if (count == m)
        {
            averages[index++] = sum / count;
            sum -= numbers[i - --count];
        }
    }
    return averages;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Average of Groups", "[bloomberg]")
{
    REQUIRE(average_of_groups({1, 2, 3, 4, 5}, 3) == vector<int>{2, 3, 4});
    REQUIRE(average_of_groups({11, 17, 18, 5, 3, 2, 7, 6}, 4) ==
    vector<int>{12, 10, 7, 4, 4});
}