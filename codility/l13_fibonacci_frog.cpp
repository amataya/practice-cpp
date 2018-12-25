// Count the minimum number of jumps required for a frog to get to the other side of a river.
//
// The Fibonacci sequence is defined using the following recursive formula:
// F(0) = 0
// F(1) = 1
// F(M) = F(M - 1) + F(M - 2) if M >= 2
//
// A small frog wants to get to the other side of a river. The frog is
// initially located at one bank of the river (position −1) and wants to get to
// the other bank (position N). The frog can jump over any distance F(K),
// where F(K) is the K-th Fibonacci number. Luckily, there are many leaves on
// the river, and the frog can jump between the leaves, but only in the
// direction of the bank at position N.
//
// The leaves on the river are represented in an array A consisting of N
// integers. Consecutive elements of array A represent consecutive positions
// from 0 to N − 1 on the river. Array A contains only 0s and/or 1s:
//
// 0 represents a position without a leaf;
// 1 represents a position containing a leaf.
//
// The goal is to count the minimum number of jumps in which the frog can
// get to the other side of the river (from position −1 to position N).
// The frog can jump between positions −1 and N (the banks of the river)
// and every position containing a leaf.
//
// For example, consider array A such that:
// A[0] = 0
// A[1] = 0
// A[2] = 0
// A[3] = 1
// A[4] = 1
// A[5] = 0
// A[6] = 1
// A[7] = 0
// A[8] = 0
// A[9] = 0
// A[10] = 0
//
// The frog can make three jumps of length F(5) = 5, F(3) = 2 and F(5) = 5.
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given an array A consisting of N integers, returns the minimum number
// of jumps by which the frog can get to the other side of the river. If the
// frog cannot reach the other side of the river, the function should return −1.
//
// For example, given:
// A[0] = 0
// A[1] = 0
// A[2] = 0
// A[3] = 1
// A[4] = 1
// A[5] = 0
// A[6] = 1
// A[7] = 0
// A[8] = 0
// A[9] = 0
// A[10] = 0
//
// the function should return 3, as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [0..100,000];
// each element of array A is an integer that can have one of the following
// values: 0, 1.
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <list>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// The frog can jump in steps of Fibonacci sequence
// Since each move is based on the previous move this problems lends itself
// well to dynamic programming.
int min_jumps(const vector<int> &A)
{
    if (A.empty())  // The frog is already at its target position.
        return 1;

    // The frog is standing on the start position. It can step on onto the end
    // position. Imagine both these positions as leaf. It simplifies the problem.
    // However we don't want to change the input
    // A.insert(A.begin(), 1);
    // A.push_back(1);
    vector<bool> positions(A.size() + 2);
    positions[0] = true;
    positions[positions.size() - 1] = true;
    for(int i = 0; i < A.size(); ++i)
        positions[i+1] = A[i] == 1;

    const int N = positions.size(); // Total positions to cover
    const int INF = 100001;         // INF is an impossible position

    // The other bank is at position N. The frog can move in fibonacci size
    // steps only (instead of usual fixed size step). We will generate all
    // Fibonacci numbers <= N in descending order. Note that N must be >= 1.
    vector<int> steps;
    int a = 1, b = 1;
    steps.emplace_back(b);
    while (true)
    {
        b = a + b;
        a = b - a;
        if (b > N)
            break;
        steps.emplace_back(b);
    }

    vector<int> num_jumps(N, INF); // Jump count to reach indexed position
    num_jumps[0] = 0; // We already are at zeroth position, no jumps needed
    int prev = 0, min_jump_count = INF;
    for (int pos = 1; pos < N; ++pos)
    {
        min_jump_count = INF;
        if (positions[pos])  // Check if this is a leaf
        {
            for (const auto &jump : steps)
            {
                prev = pos - jump;
                if (prev < 0)
                    break;

                if (positions[prev] && num_jumps[prev] + 1 < min_jump_count)
                    min_jump_count = num_jumps[prev] + 1;
            }
        }
        num_jumps[pos] = min_jump_count;
    }
    return (num_jumps[N-1] == INF) ? -1 : num_jumps[N-1];
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Minimum number of Jumps", "[codility]")
{
    REQUIRE(min_jumps({0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0}) == 3);
}