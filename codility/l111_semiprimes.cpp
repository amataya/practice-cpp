//  Count the semiprime numbers in the given range [a..b]
//
// A prime is a positive integer X that has exactly two distinct divisors:
// 1 and X. The first few prime integers are 2, 3, 5, 7, 11 and 13.
//
// A semiprime is a natural number that is the product of two
// (not necessarily distinct) prime numbers. The first few semiprimes are
// 4, 6, 9, 10, 14, 15, 21, 22, 25, 26.
//
// You are given two non-empty arrays P and Q, each consisting of M integers.
// These arrays represent queries about the number of semiprimes within
// specified ranges.
//
// Query K requires you to find the number of semiprimes within the range
// (P[K], Q[K]), where 1 ≤ P[K] ≤ Q[K] ≤ N.
//
// For example, consider an integer N = 26 and arrays P, Q such that:
// P[0] = 1    Q[0] = 26
// P[1] = 4    Q[1] = 10
// P[2] = 16   Q[2] = 20
//
// The number of semiprimes within each of these ranges is as follows:
//
// (1, 26) is 10,
// (4, 10) is 4,
// (16, 20) is 0.
//
// Write a function:
//
// vector<int> solution(int N, vector<int> &P, vector<int> &Q);
//
// that, given an integer N and two non-empty arrays P and Q consisting of M
// integers, returns an array consisting of M elements specifying the consecutive
// answers to all the queries.
//
// For example, given an integer N = 26 and arrays P, Q such that:
// P[0] = 1    Q[0] = 26
// P[1] = 4    Q[1] = 10
// P[2] = 16   Q[2] = 20
//
// the function should return the values [10, 4, 0], as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// N is an integer within the range [1..50,000];
// M is an integer within the range [1..30,000];
// each element of arrays P, Q is an integer within the range [1..N];
// P[i] ≤ Q[i].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<int> semi_primes(int N, const vector<int> &P, const vector<int> &Q)
{
    if (N < 2)
        return {0};

    vector<bool> primes(N, true);
    primes[0] = false, primes[1] = false;
    const auto upperBound = static_cast<int>(sqrt(N));

    int i, j;
    for(i = 2; i <= upperBound; ++i)
    {
        if (primes[i])
            for (j = i * i; j <= N; j += i)
                primes[j] = false;
    }

    vector<bool> semi(N + 1);
    for(i = 2; i <= upperBound; ++i)
    {
        if (primes[i])
        {
            for (j = i * i; j <= N; j += i)
                if (primes[j/i]) // Prime Factorization
                    semi[j] = true;
        }
    }

    // Now that we have the semi primes we want an efficient method
    // to say how many semi-primes are between P[i] and Q[i].
    // We are trying to answer a range query so take the Prefix-sum approach.
    // We will calculate a running total.
    // The size of our table will be the maximum value of the range end
    const auto range_end = *max_element(Q.begin(), Q.end());
    vector<int> prefix(range_end + 1);
    for(i = 4; i <= range_end; ++i) // We know the first semiprime is 4
    {
        prefix[i] = prefix[i-1];        // Previous total to maintain running
        prefix[i] += semi[i] ? 1 : 0;   // If i is semi-prime then update total
    }

    vector<int> result(P.size());
    for(i = 0; i < P.size(); ++i)
        result[i] = prefix[Q[i]] - prefix[P[i] - 1];
    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Semiprimes", "[codility]")
{
    REQUIRE(semi_primes(26, {1, 4, 16}, {26, 10, 20}) == vector<int>{10, 4, 0});
}