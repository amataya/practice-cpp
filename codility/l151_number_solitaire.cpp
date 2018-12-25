// In a given array, find the subset of maximal sum in which the distance
// between consecutive elements is at most 6.
//
// A game for one player is played on a board consisting of N consecutive
// squares, numbered from 0 to N − 1. There is a number written on each square.
// A non-empty array A of N integers contains the numbers written on the
// squares. Moreover, some squares can be marked during the game.
//
// At the beginning of the game, there is a pebble on square number 0 and this
// is the only square on the board which is marked. The goal of the game is to
// move the pebble to square number N − 1.
//
// During each turn we throw a six-sided die, with numbers from 1 to 6 on its
// faces, and consider the number K, which shows on the upper face after the
// die comes to rest. Then we move the pebble standing on square number I to
// square number I + K, providing that square number I + K exists. If square
// number I + K does not exist, we throw the die again until we obtain a
// valid move. Finally, we mark square number I + K.
//
// After the game finishes (when the pebble is standing on square number N − 1),
// we calculate the result. The result of the game is the sum of the numbers
// written on all marked squares.
//
// For example, given the following array:
// A[0] = 1
// A[1] = -2
// A[2] = 0
// A[3] = 9
// A[4] = -1
// A[5] = -2
//
// one possible game could be as follows:
//
// the pebble is on square number 0, which is marked;
// we throw 3; the pebble moves from square number 0 to square number 3;
// we mark square number 3;
// we throw 5; the pebble does not move, since there is no square number
// 8 on the board;
// we throw 2; the pebble moves to square number 5; we mark this square and
// the game ends.
//
// The marked squares are 0, 3 and 5, so the result of the game is
// 1 + 9 + (−2) = 8. This is the maximal possible result that can be achieved
// on this board.
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given a non-empty array A of N integers, returns the maximal result
// that can be achieved on the board represented by array A.
//
// For example, given the array
// A[0] = 1
// A[1] = -2
// A[2] = 0
// A[3] = 9
// A[4] = -1
// A[5] = -2
//
// the function should return 8, as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [2..100,000];
// each element of array A is an integer within the range [−10,000..10,000].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Forget the description - it is confusing and not well-written. Crap!
// You are trying to find a subsequence which is not contiguous, and in which
// the maximum distance between any two selected elements from original array
// is 6.
// This is a variation of maximum subarray problem (see l093)
// Sum[0] = arr[0]
// Sum[1] = max(Sum[0], arr[1])
// Sum[2] = max(Sum[0]+arr[2], Sum[1])
// ...
// Sum[i] = max(Sum[i-2]+arr[i], Sum[i-1]) when i>=2
// The caching is very neat here. Do it via a recursive implementation to
// understand solution.
int max_sum_non_contiguous_seq(const vector<int> &A)
{
    const int MAX_D = 6; // Maximum distance between two elements
    const auto n = A.size();
    vector<int> max_score(MAX_D, A[0]); // Table to track values
    // Since the distance is fixed we can be memory efficient by reusing slots
    // by modulating index with MAX_D to get the desired index
    for (size_t i = 1; i < n; ++i)
        max_score[i % MAX_D] = *max_element(max_score.begin(), max_score.end()) + A[i];
    return max_score[(n - 1) % MAX_D];
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Max sum non-continguous subsequence", "[codility]")
{
    REQUIRE(max_sum_non_contiguous_seq({1, -2, 0, 9, -1, -2}) == 8);
}