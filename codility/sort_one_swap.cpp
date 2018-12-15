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

    int i = 0, j = -1;
    vector<int> indices;
    for (i = 0; i < A.size() - 1; ++i)
        if (A[i] > A[i + 1])
            indices.emplace_back(i);

    // More than 2 - you know what to do
    if (indices.size() > 2)
        return false;

    // If all elements are sorted
    if (indices.empty())
        return true;

    // Exactly 2 - Fantastic!
    if (indices.size() == 2)
    {
        i = indices[0], j = indices[1];
        if (j + 1 < A.size()) // To handle tricky case of {5, 2, 3, 1}
            j += (A[i] < A[j + 1]) ? 0 : 1;
        swap(A[i], A[j]);
    }

    // One index only - tricky case! {1, 2, 4, 3, 5}
    if (indices.size() == 1)
    {
        i = indices[0], j = -1;
        for(int k = A.size() - 1; k > i; --k)
        {
            if(A[k] < A[i] && A[k - 1] <= A[i])
            {
                j = k;
                break;
            }
        }
        if (j != -1)
            swap(A[i], A[j]);
        else
            return false;
    }

    // It looks we have a sorted array but let's do a second check
    for (i = 1; i < A.size(); ++i)
        if (A[i] < A[i - 1])
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
    REQUIRE(sort_one_swap({5, 2, 3, 1}));
}