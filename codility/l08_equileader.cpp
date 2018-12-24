// Find the index S such that the leaders of the sequences A[0], A[1], ..., A[S]
// and A[S + 1], A[S + 2], ..., A[N - 1] are the same.
//
// A non-empty array A consisting of N integers is given.
//
// The leader of this array is the value that occurs in more than half of the
// elements of A.
//
// An equileader is an index S such that 0 ≤ S < N − 1 and two sequences
// A[0], A[1], ..., A[S] and A[S + 1], A[S + 2], ..., A[N − 1]
// have leaders of the same value.
//
// For example, given array A such that:
// A[0] = 4
// A[1] = 3
// A[2] = 4
// A[3] = 4
// A[4] = 4
// A[5] = 2
//
// we can find two equileaders:
//
// 0, because sequences: (4) and (3, 4, 4, 4, 2) have the same leader, 4.
// 2, because sequences: (4, 3, 4) and (4, 4, 2) have the same leader, 4.
//
// The goal is to count the number of equileaders.
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given a non-empty array A consisting of N integers,
// returns the number of equileaders.
//
// For example, given:
// A[0] = 4
// A[1] = 3
// A[2] = 4
// A[3] = 4
// A[4] = 4
// A[5] = 2
//
// the function should return 2, as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [1..100,000];
// each element of array A is an integer within the range
// [−1,000,000,000..1,000,000,000].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int equileader(const vector<int> &A)
{
    // 1. Find most likely candidate for the leader. Uses Boyer-Moore Majority
    // Voting Algorithm
    int candidate = 0, i = 0;
    long times = 0;
    for (i = 0; i < A.size(); ++i)
    {
        // change candidate when count reaches 0
        if  (times == 0)
        {
            candidate = A[i];
            ++times;
        }
        else // count occurrences of candidate
            times += (A[i] == candidate) ? 1 : -1;
    }

    // 2. Verify that candidate occurs more than N/2 times
    int leader = INT_MIN;
    if (times > 0)
    {
        times = count(A.begin(), A.end(), candidate);
        if (times > A.size() / 2)
            leader = candidate;
    }

    if (leader == INT_MIN)
        return 0;

    // 3. There exists a leader now count the number of occurences
    // of this leader in all sequences.
    int count_equileader = 0;
    long count_left = 0,         // Leader count for the left sequence
         count_right = times;    // Leader count for the right sequence
    for(i = 0; i < A.size() - 1; ++i)
    {
        if (A[i] == leader)
        {
            ++count_left;
            --count_right;
        }

        // Verify that the dominant value in both sequences is the same
        if (count_left > (i + 1) / 2 &&
            count_right > (A.size() - i - 1) / 2)
            ++count_equileader;
    }
    return count_equileader;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Equileader", "[codility]")
{
    REQUIRE(equileader({4, 3, 4, 4, 4, 2}) == 2);
}