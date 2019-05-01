// A subarray of array a is defined as a contiguous block of a's elements having
// a length that is less than or equal to the length of the array. For example,
// the subarrays of array a = [1, 2, 3] are [1], [2], [3], [1, 2], [2, 3],
// and [1, 2, 3]. Given an integer, k = 3, the subarrays having elements that
// sum to a number ≤ k are [1], [2], and [1, 2]. The longest of these subarrays
// is [1, 2], which has a length of 2. Given an array, a, determine its longest
// subarray that sums to less than or equal to a given value k.
//
// Complete the function maxLength in the editor below. The function must
// return an integer that represents the length of the longest subarray of a
// that sums to a number ≤ k.
//
// maxLength has the following parameter(s):
//
// a[a[0],...a[n-1]]: an array of integers (assume positive)
// k: an integer
//
// Constraints
// 1 ≤ n ≤ 105
// 1 ≤ a[i] ≤ 103
// 1 ≤ k ≤ 109
//
// Sample Input 0
// 3
// 1
// 2
// 3
// 4
// Sample Output 0
// 2
// Explanation 0
// - The subarrays of [1, 2, 3] having elements that sum to a number ≤ (k = 4)
//   are [1], [2], [3], and [1, 2].
// - The longest of these is [1, 2], which has a length of 2. Return 2 as the
//   answer.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int maxLength(vector<int> nums, int k)
{
    int start = 0, end = 0, max_so_far = 0, index = 0, max_length = 0;
    while (index < nums.size())
    {
        max_so_far += nums[index];
        if (max_so_far <= k)
            end = index++;
        else
        {
            max_so_far -= (nums[start] + nums[index]);
            max_length = max(max_length, (end - start + 1));
            ++start;
        }
    }
    return max(max_length, (end - start + 1));
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Length of longest subsequence with given sum", "[bloomberg]")
{
    REQUIRE(maxLength({1, 2, 3}, 4) == 2);
    REQUIRE(maxLength({1, 1, 1, 2, 3}, 3) == 3);
    REQUIRE(maxLength({1, 1, 1, 2, 3}, 1000) == 5);
    REQUIRE(maxLength({3, 1, 2, 1}, 4) == 3);
}