// A non-empty array A consisting of N integers is given. The product of
// triplet (P, Q, R) equates to A[P] * A[Q] * A[R] (0 ≤ P < Q < R < N).
//
// For example, array A such that:
// A[0] = -3
// A[1] = 1
// A[2] = 2
// A[3] = -2
// A[4] = 5
// A[5] = 6
//
// contains the following example triplets:
//
// (0, 1, 2), product is −3 * 1 * 2 = −6
// (1, 2, 4), product is 1 * 2 * 5 = 10
// (2, 4, 5), product is 2 * 5 * 6 = 60
//
// Your goal is to find the maximal product of any triplet.
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given a non-empty array A, returns the value of the maximal product of any triplet.
//
// For example, given array A such that:
// A[0] = -3
// A[1] = 1
// A[2] = 2
// A[3] = -2
// A[4] = 5
// A[5] = 6
//
// the function should return 60, as the product of triplet (2, 4, 5) is maximal.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [3..100,000];
// each element of array A is an integer within the range [−1,000..1,000].
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// We need to consider from both ends, since multiplying two -ve yield a +ve
// Fancy use of algorithm.
int max_product(vector<int> A)
{
    sort(A.begin(), A.end());
    const int val1 = accumulate(A.end() - 3, A.end(), 1, multiplies<>());
    const int val2 = A[A.size() - 1] * A[0] * A[1];
    return max(val1, val2);
}

// Without sorting - O(n)
int max_product2(const vector<int> A)
{
    int max_nums[3], min_nums[2];
    fill(max_nums, max_nums + 3, -1001);
    fill(min_nums, min_nums + 2, 1001);

    for (const auto &n : A)
    {
        if (n > max_nums[0])
        {
            swap(max_nums[2], max_nums[1]);
            swap(max_nums[1], max_nums[0]);
            max_nums[0] = n;
        }
        else if (n > max_nums[1])
        {
            swap(max_nums[2], max_nums[1]);
            max_nums[1] = n;
        }
        else if (n > max_nums[2])
        {
            max_nums[2] = n;
        }

        if (n < min_nums[0])
        {
            swap(min_nums[1], min_nums[0]);
            min_nums[0] = n;
        }
        else if (n < min_nums[1])
        {
            min_nums[1] = n;
        }
    }
    const int val1 = accumulate(max_nums, max_nums + 3, 1, multiplies<>());
    const int val2 = accumulate(min_nums, min_nums + 2, max_nums[0], multiplies<>());
    return max(val1, val2);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Max Triplet Product", "[codility]")
{
    REQUIRE(max_product({-3, 1, 2, -2, 5, 6}) == 60);
    REQUIRE(max_product({-3, 2, 2, -2, 5, 6}) == 60);
    REQUIRE(max_product({-5, 5, -5, 4}) == 125);
}

TEST_CASE("Max Triplet Product - No Sorting", "[codility]")
{
    REQUIRE(max_product2({-3, 1, 2, -2, 5, 6}) == 60);
    REQUIRE(max_product2({-3, 2, 2, -2, 5, 6}) == 60);
    REQUIRE(max_product2({-5, 5, -5, 4}) == 125);
}