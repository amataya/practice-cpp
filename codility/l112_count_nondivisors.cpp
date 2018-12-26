//  Calculate the number of elements of an array that are not divisors of each element.
//
// You are given an array A consisting of N integers.
//
// For each number A[i] such that 0 ≤ i < N, we want to count the number of
// elements of the array that are not the divisors of A[i]. We say that these
// elements are non-divisors.
//
// For example, consider integer N = 5 and array A such that:
// A[0] = 3
// A[1] = 1
// A[2] = 2
// A[3] = 3
// A[4] = 6
//
// For the following elements:
//
// A[0] = 3, the non-divisors are: 2, 6,
// A[1] = 1, the non-divisors are: 3, 2, 3, 6,
// A[2] = 2, the non-divisors are: 3, 3, 6,
// A[3] = 3, the non-divisors are: 2, 6,
// A[4] = 6, there aren't any non-divisors.
//
// Write a function:
//
// vector<int> solution(vector<int> &A);
//
// that, given an array A consisting of N integers, returns a sequence
// of integers representing the amount of non-divisors.
//
// Result array should be returned as a vector of integers.
//
// For example, given:
// A[0] = 3
// A[1] = 1
// A[2] = 2
// A[3] = 3
// A[4] = 6
//
// the function should return [2, 4, 3, 2, 0], as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [1..50,000];
// each element of array A is an integer within the range [1..2 * N].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <unordered_map>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<int> non_divisors_v0(const vector<int> &A)
{
    if (A.size() < 2)
        return {0};

    vector<int> nondivisors(A.size());
    int i, j;
    for(i = 0; i < A.size(); ++i)
    {
        for (j = 0; j < A.size(); ++j)
            if (A[j] % A[i] > 0)
                nondivisors[j]++;
    }
    return nondivisors;
 }

// Using the Sieve of Eratosthenes, you generate divisors for all input elements
// of A. If a given number x is a divisor of element then N also is a divisor.
// After all divisors are computed, we simply subtract those
// (multiplied by their counts or 0) from the total number of elements in A.
vector<int> non_divisors(const vector<int> &A)
{
    if (A.size() < 2)
        return {0};

    unordered_map<int, int> counts;
    int max_value = -1; // using info from description
    for (const auto &e : A)
    {
        counts[e]++;
        max_value = max(max_value, e);
    }

    // Sieve of 'max_value' helps us to count the number of
    // all the divisors of all the numbers upto and including 'max_value'
    vector<int> divisors(max_value + 1);
    int i, j;
    for (i = 2; i * i <= max_value; ++i)
    {
        for(j = i * i; j <= max_value; j += i)
        {
            divisors[j] += counts[i];
            if (j/i != i)
                divisors[j] += counts[j/i];
        }
    }

    // Calculate the non-divisors
    vector<int> result(A.size());
    for(i = 0; i < A.size(); ++i)
    {
        j = A[i];
        // discount the counts of number itself
        result[i] = A.size() - (divisors[j] + counts[j]);
        if (j != 1) // also discount the counts of 1's
            result[i] -= counts[1];
    }

    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Count Non-divisors", "[codility]")
{
    REQUIRE(non_divisors({3, 1, 2, 3, 6}) == vector<int>{2, 4, 3, 2, 0});
}