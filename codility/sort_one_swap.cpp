////////////////////////////////////////////////////////////////////////////////
// Scored 25% in this task :O
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
bool sort_one_swap(vector<int> A)
{
    if (A.size() < 2)
        return true;

    int count = 0, i = -1, j = -1, idx = 0, k = 0;
    for (idx = A.size() - 1; idx > 0; --idx)
    {
        if (A[idx] < A[idx - 1])
        {
            ++count;

            if (i == -1)
                i = idx - 1;
            for (k = A.size() - 1; k >= 0; --k)
            {
                if (A[i] > A[k])
                {
                    ++count;
                    j = k;
                    break;
                }
            }
        }
    }

    // More than 2 - you know what to do (may be redundant)
    if (count > 2)
        return false;

    // If all elements are sorted
    if (count == 0)
        return true;

    // Exactly 2 - Fantastic!
    if (count == 2)
        swap(A[i], A[j]);

    // One tricky case! {1, 2, 4, 3, 5}
    if (count == 1)
    {
        j = i;
        i = i - 1;
        swap(A[i], A[j]);
    }

    // It looks it would have been sorted but do a second check
    for (idx = 1; idx < A.size(); ++idx)
        if (A[idx] < A[idx - 1])
            return false;

    return true;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Sort By One Swap", "[codility]")
{
    REQUIRE(sort_one_swap({1, 5, 3, 3, 7}));
    REQUIRE(sort_one_swap({1, 3, 5}));
    REQUIRE_FALSE(sort_one_swap({1, 3, 5, 3, 4}));
    REQUIRE(sort_one_swap({1, 2, 4, 3, 5}));
    REQUIRE_FALSE(sort_one_swap({4, 1, 2, 3}));
}