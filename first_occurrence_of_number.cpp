//
// Given a sorted array, had to find the first occurrence of given number
// Example: [1, 2, 3, 4, 5], target = 3
// Answer: 2
// Example: [1, 1, 2, 3, 4, 5, 6, 6], target = 6
// Answer: 6
// Example: [2, 2, 2, 2, 2], target = 2
// Answer: 0
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int first_occurrence_of_number(vector<int> numbers, int target)
{
    int lo = 0, hi = numbers.size() - 1, mid = 0;
    while (lo <= hi)
    {
        mid = lo + (hi - lo) / 2;
        if (numbers[mid] == target)
        {
            while (mid - 1 >= 0 && numbers[mid - 1] == target)
                --mid;
            return mid;
        }
        else if (numbers[mid] > target)
            hi = mid - 1;
        else // numbers[mid] < target
            lo = mid + 1;
    }
    return -1;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("First occurrence of number in sorted array", "[bloomberg]")
{
    REQUIRE(first_occurrence_of_number({1, 2, 3, 4, 5}, 3) == 2);
    REQUIRE(first_occurrence_of_number({1, 1, 2, 3, 4, 5, 6, 6}, 6) == 6);
    REQUIRE(first_occurrence_of_number({2, 2, 2, 2, 2}, 2) == 0);
    REQUIRE(first_occurrence_of_number({-2, -1, -1, 2, 5, 7}, -1) == 1);
}