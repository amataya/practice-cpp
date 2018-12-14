////////////////////////////////////////////////////////////////////////////////
// Given an array A of N integers, returns the smallest positive integer
// (greater than 0) that does not occur in A.
// For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.
// Given A = [1, 2, 3], the function should return 4.
// Given A = [−1, −3], the function should return 1.
// Write an efficient algorithm for the following assumptions:
// - N is an integer within the range [1..100,000];
// - Each element of array A is an integer within the range [−1,000,000..1,000,000].
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////

int smallest_nonoccurring_number(vector<int> A)
{
    int mv = *max_element(A.begin(), A.end());
    mv = mv < 0 ? 0 : mv;
    vector<bool> visited(mv + 2);
    for (const auto &n : A)
        if (n > 0)
            visited[n] = true;
    for (int i = 1; i < int(visited.size()); ++i)
        if (!visited[i])
            return i;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Test Smallest Absent number", "[codility]")
{
    REQUIRE(smallest_nonoccurring_number({1, 2, 3}) == 4);
    REQUIRE(smallest_nonoccurring_number({1, 3, 6, 4, 1, 2}) == 5);
    REQUIRE(smallest_nonoccurring_number({-1, -3}) == 1);
}