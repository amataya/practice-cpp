// You are given N counters, initially set to 0, and you have two possible
// operations on them:
//
// increase(X) − counter X is increased by 1,
// max counter − all counters are set to the maximum value of any counter.
//
// A non-empty array A of M integers is given. This array represents
// consecutive operations:
//
// if A[K] = X, such that 1 ≤ X ≤ N, then operation K is increase(X),
// if A[K] = N + 1 then operation K is max counter.
//
// For example, given integer N = 5 and array A such that:
// A[0] = 3
// A[1] = 4
// A[2] = 4
// A[3] = 6
// A[4] = 1
// A[5] = 4
// A[6] = 4
//
// the values of the counters after each consecutive operation will be:
// (0, 0, 1, 0, 0)
// (0, 0, 1, 1, 0)
// (0, 0, 1, 2, 0)
// (2, 2, 2, 2, 2)
// (3, 2, 2, 2, 2)
// (3, 2, 2, 3, 2)
// (3, 2, 2, 4, 2)
//
// The goal is to calculate the value of every counter after all operations.
//
// Write a function:
//
//     vector<int> solution(int N, vector<int> &A);
//
// that, given an integer N and a non-empty array A consisting of M integers,
// returns a sequence of integers representing the values of the counters.
// Result array should be returned as a structure Results.
//
// For example, given:
// A[0] = 3
// A[1] = 4
// A[2] = 4
// A[3] = 6
// A[4] = 1
// A[5] = 4
// A[6] = 4
//
// the function should return [3, 2, 2, 4, 2], as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// N and M are integers within the range [1..100,000];
// each element of array A is an integer within the range [1..N + 1].
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// We could use lazy-write to improve the performance. When receiving the
// max_counter command, we record the current-max value, but do not change the
// list content. Only when we are going to return the list or increase a
// specific element, we will apply the stored value to the corresponding element
vector<int> max_counter(int N, vector<int> A)
{
    vector<int> result(N);
    int prev_max = 0,  // used value in previous max_counter command
        curr_max = 0;  // current maximum value of any counter
    for (const auto& cmd : A)
    {
        if (cmd >= 1 && cmd <= N)
        {
            // Optimization: Lazily update to prev max counter value so that
            // this update is correct
            if (prev_max > result[cmd - 1])
                result[cmd - 1] = prev_max;

            ++result[cmd - 1]; // apply increase(X) command

            if (curr_max < result[cmd - 1])
                curr_max = result[cmd - 1];
        }
        else  // max counter command - just store now for lazy write later
            prev_max = curr_max;
    }
    for(auto& e : result)  // Now update result
        if (e < prev_max)
            e = prev_max;
    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Max Counter", "[codility]")
{
    REQUIRE(max_counter(5, {3, 4, 4, 6, 1, 4, 4})
    == vector<int>{3, 2, 2, 4, 2});
}
