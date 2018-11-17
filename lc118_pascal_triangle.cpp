////////////////////////////////////////////////////////////////////////////////
// Given a non-negative integer numRows, generate the first numRows of Pascal's
// triangle.
// Input: 5
// Output:
// [
//      [1],
//     [1,1],
//    [1,2,1],
//   [1,3,3,1],
//  [1,4,6,4,1]
// ]
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////

// C(n, k) = n! / (n-k)! * k!
//         = [n * (n-1) *....* 1]  / [ ( (n-k) * (n-k-1) * .... * 1) *
//                                     ( k * (k-1) * .... * 1 ) ]
// After simplifying, we get
// C(n, k) = [n * (n-1) * .... * (n-k+1)] / [k * (k-1) * .... * 1]
//
// Also, C(n, k) = C(n, n-k)  // we can change r to n-r if r > n-r
int binomial_coefficient(int n, int k)
{
    int result = 1;
    // Since C(n, k) == C(n, n - k)
    if (k > n - k)
        k = n - k;
    for (int i = 0; i < k; ++i)
    {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> result;
    int c = 0, r = 0;
    while (r < numRows)
    {
        vector<int> row;
        for (c = 0; c <= r; ++c)
            row.push_back(binomial_coefficient(r, c));
        result.push_back(row);
        ++r;
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Test Pascal Triangle", "[leetcode]")
{
    REQUIRE(generate(5) == vector<vector<int>>{
        {1}, {1, 1}, {1, 2, 1}, {1, 3, 3, 1}, {1, 4, 6, 4, 1}});
}