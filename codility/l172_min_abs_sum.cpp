// Delta 2011 - Given array of integers, find the lowest absolute sum of elements.
//
// For a given array A of N integers and a sequence S of N integers from the
// set {−1, 1}, we define val(A, S) as follows:
//
// val(A, S) = |sum{ A[i]*S[i] for i = 0..N−1 }|
//
// (Assume that the sum of zero elements equals zero.)
//
// For a given array A, we are looking for such a sequence S that
// minimizes val(A,S).
//
// Write a function:
//
// int solution(vector<int> &A);
//
// that, given an array A of N integers, computes the minimum value of
// val(A,S) from all possible values of val(A, S) for all possible sequences
// S of N integers from the set {−1, 1}.
//
// For example, given array:
// A[0] =  1
// A[1] =  5
// A[2] =  2
// A[3] = -2
//
// your function should return 0, since for S = [−1, 1, −1, 1],
// val(A, S) = 0, which is the minimum possible value.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [0..20,000];
// each element of array A is an integer within the range [−100..100].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// I don't understand how either of the solutions are working
// This is a variation of subset sum problem
// https://en.wikipedia.org/wiki/Subset_sum_problem

// The problem asks you to find the lowest absolute sum of elements of the given
// array or their negatives.
// - Since we can arbitrarily choose to take the element or its negative, we can
// simplify the problem and replace each number with its absolute value.
// - Then the problem becomes dividing the numbers into two groups and making
// the difference between the sums of the two groups as small as possible.
// - Let K be the sum of all absolute values in A. We want to choose some of
// the numbers (absolute values) to make their sum as large as possible without
// exceeding K/2.
// - Let P be the sum of the first group, Q be the sum of the other group and
// P < Q, where Q + P = S and P <= K/2 <= Q. The larger the P, the smaller the
// difference Q - P.
// The dp table is of size K + 1. It is size of "sum", which means each index
// incrementally adds up to sum.
// We use this to ask whether the total denoted by index i, can be achieved using
// elements in A. So for example let A = [-2, 1, 2, 1] and sum of absolutes = 6.
// dp = [0, 0, 0, 0, 0, 0, 0]. We are asking if we can reach a sum of 3 using A's
// elements (answer = yes). We assume that sum of 0 is possible, so dp[0] = 1.
// Obviously from data all values will be true but the condition
// (j + A[i] <= sum) causes surprises and some values will be false.
int lowest_absolute_sum_v0(vector<int> A)
{
    int i, j, sum = 0;
    for (i = 0; i < A.size(); ++i)
    {
        A[i] = abs(A[i]);
        sum += A[i];
    }

    vector<bool> dp(sum + 1);
    dp[0] = true;
    for (i = 0; i < A.size(); ++i)
        for (j = sum; j >= 0; --j)
            dp[j + A[i]] = dp[j] && (j + A[i] <= sum);

    int result = sum;
    for (i = 0; i < (sum/2 + 1); ++i)
        if (dp[i])
            result = min(result, sum - 2 * i);

    return result;
}
////////////////////////////////////////////////////////////////////////////////
// Notice that the range of numbers is quite small (maximum 100). Hence, there
// must be a lot of duplicated numbers. Let count[i] denote the number of
// occurrences of the value i. We can improve the previous solution by
// processing all occurrences of the same value at once. First we calculate
// values count i. Then we create array dp such that
// - dp[j] = -1 if we cannot get the sum j
// - dp[j] >= 0 if we can get sum j
// Initially dp[j] = -1 for all j (except dp[0]). Then we scan through all the
// values appearing in A (a = A[i]), such that count[a] > 0.
// For every such 'a' we update 'dp' such that dp[j] denotes j 'a' left to use
// Note that if the previous value at dp[j] >= 0  then we can set
// dp[j] = count[a] as no more occurrence of 'a' is  needed to obtain the sum j.
// Otherwise we must obtain sum j - a first first and then use a number 'a' to
// get sum 'j'. In such a situation dp[j] = dp[j - a] - 1.
// Using this algorithm, we can mark all the sum values and choose the best one
// (closest to half of sum)
int lowest_absolute_sum(vector<int> A)
{
    int i, j, sumA = 0, maxA = -1;
    for (i = 0; i < A.size(); ++i)
    {
        A[i] = abs(A[i]);
        sumA += A[i];
        maxA = max(maxA, A[i]);
    }

    vector<int> occurrences(maxA + 1);
    for (i = 0; i < A.size(); ++i)
        ++occurrences[A[i]];

    const int halfSum = sumA/2 + 1;
    vector<int> possible(halfSum, -1);
    possible[0] = 0;
    for (auto num = 0; num < occurrences.size(); ++num)
    {
        if (occurrences[num] > 0)
        {
            for (j = 0; j < halfSum; ++j)
            {
                // Reachable from previous numbers?
                if (possible[j] >= 0)  // Yes
                    possible[j] = occurrences[num];
                // No but can be achieved with previous AND current
                else if (j >= num && possible[j - num] > 0)
                    possible[j] = possible[j - num] - 1;
            }
        }
    }

    // Divide the A into two parts: P and Q, with restriction P <= Q.
    // So P <= sumOfA // 2 <= Q. We want the largest possible P, so that
    // Q-P is minimized.
    int result = sumA;
    for (i = 0; i < halfSum; ++i)
        if (possible[i] >= 0)
            result = min(result, sumA - 2 * i);

    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Lowest Absolute Sum", "[codility]")
{
    REQUIRE(lowest_absolute_sum({1, 5, 2, -2}) == 0);
}