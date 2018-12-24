// Count the number of different ways of climbing to the top of a ladder.
//
// You have to climb up a ladder. The ladder has exactly N rungs, numbered from
// 1 to N. With each step, you can ascend by one or two rungs. More precisely:
//
// with your first step you can stand on rung 1 or 2,
// if you are on rung K, you can move to rungs K + 1 or K + 2,
// finally you have to stand on rung N.
//
// Your task is to count the number of different ways of climbing to the top
// of the ladder.
//
// For example, given N = 4, you have five different ways of climbing,
// ascending by:
//
// 1, 1, 1 and 1 rung,
// 1, 1 and 2 rungs,
// 1, 2 and 1 rung,
// 2, 1 and 1 rungs, and
// 2 and 2 rungs.
//
// Given N = 5, you have eight different ways of climbing, ascending by:
//
// 1, 1, 1, 1 and 1 rung,
// 1, 1, 1 and 2 rungs,
// 1, 1, 2 and 1 rung,
// 1, 2, 1 and 1 rung,
// 1, 2 and 2 rungs,
// 2, 1, 1 and 1 rungs,
// 2, 1 and 2 rungs, and
// 2, 2 and 1 rung.
//
// The number of different ways can be very large, so it is sufficient to
// return the result modulo 2^P, for a given integer P.
//
// Write a function:
//
// vector<int> solution(vector<int> &A, vector<int> &B);
//
// that, given two non-empty arrays A and B of L integers, returns an array
// consisting of L integers specifying the consecutive answers; position I
// should contain the number of different ways of climbing the ladder
// with A[I] rungs modulo 2B[I].
//
// For example, given L = 5 and:
// A[0] = 4   B[0] = 3
// A[1] = 4   B[1] = 2
// A[2] = 5   B[2] = 4
// A[3] = 5   B[3] = 3
// A[4] = 1   B[4] = 1
//
// the function should return the sequence [5, 1, 8, 0, 1], as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// L is an integer within the range [1..50,000];
// each element of array A is an integer within the range [1..L];
// each element of array B is an integer within the range [1..30].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// For a given N rungs, the number of different ways of climbing is the (N+1)th
// element in the Fibonacci numbers.
// The interesting part is that it pushes the limit of C++ data types.
// According to problem formulation the number of steps in ladder can be
// as much as 30000. The number of ways will overflow long-long data type in C++.
// This led to surprises when solution was evaluated by Online Judge.
// However, it can be proved that recurrence F(n) = F(n-1) + F(n-2)
// works also under module transformation at any step.
// Therefore perform the modulo operation while computing the Fibonacci numbers.
// In Python, the range of integers is unlimited, or say only limited by the
// memory size. So the Python code could pass the test.

vector<int> climb_ladder(const vector<int> &A, const vector<int> &B)
{
    // Precompute the factor used in modulo
    int k = 0;
    const int maxP = *max_element(B.begin(), B.end());
    vector<int> factors(maxP + 1);  // 1-based indexing later
    for (k = 1; k <= maxP; ++k)
        factors[k] = static_cast<int>(pow(2, k));

    // Precompute the fibonacci sequence
    const int limit = *max_element(A.begin(), A.end());
    vector<int> ways(limit + 1);    // 1-based indexing later
    ways[0] = 1;
    ways[1] = 1;
    for (k = 2; k <= limit; ++k)
        ways[k] = (ways[k -1] + ways[k -2]) % factors[maxP];

    // Now generate the result
    int N = 0, P = 0;
    vector<int> result(A.size());
    for (size_t i = 0; i < A.size(); ++i)
    {
        N = A[i];
        P = B[i];
        result[i] = ways[N] % factors[P];
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Climb Ladder", "[codility]")
{
    REQUIRE(climb_ladder({4, 4, 5, 5, 1}, {3, 2, 4, 3, 1})
              == vector<int>{5, 1, 8, 0, 1} );
}