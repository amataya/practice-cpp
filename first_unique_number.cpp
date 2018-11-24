// Find first unique number in an unsorted array of 32 bit numbers without using
// hash tables or array of counters.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <bitset>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int first_unique_number(vector<int> numbers)
{
    constexpr size_t range = 2^32 - 1;
    bitset<range> occurrence, frequency;
    for (const auto& n : numbers)
    {
        if(occurrence[n - 1])
            frequency.set(n - 1);
        occurrence.set(n - 1);
    }
    for (size_t i = 0; i < range; ++i)
        if (occurrence[i] && !frequency[i])
            return i + 1;
    return -1;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("First Unique number", "[bloomberg]")
{
    REQUIRE(first_unique_number({1, 1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 8}) == 4);
}