// A prime is a positive integer X that has exactly two distinct divisors:
// 1 and X. The first few prime integers are 2, 3, 5, 7, 11 and 13.
//
// A prime D is called a prime divisor of a positive integer P if there exists a
// positive integer K such that D * K = P. For example, 2 and 5 are prime
// divisors of 20.
//
// You are given two positive integers N and M. The goal is to check whether
// the sets of prime divisors of integers N and M are exactly the same.
//
// For example, given:
//
// N = 15 and M = 75, the prime divisors are the same: {3, 5};
// N = 10 and M = 30, the prime divisors aren't the same: {2, 5} is not
// equal to {2, 3, 5};
// N = 9 and M = 5, the prime divisors aren't the same: {3} is not equal to {5}.
//
// Write a function:
//
// int solution(vector<int> &A, vector<int> &B);
//
// that, given two non-empty arrays A and B of Z integers, returns the number of
// positions K for which the prime divisors of A[K] and B[K] are exactly the same.
//
// For example, given:
// A[0] = 15   B[0] = 75
// A[1] = 10   B[1] = 30
// A[2] = 3    B[2] = 5
//
// the function should return 1, because only one pair (15, 75) has the same
// set of prime divisors.
//
// Write an efficient algorithm for the following assumptions:
//
// Z is an integer within the range [1..6,000];
// each element of arrays A, B is an integer within the range [1..2,147,483,647].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int gcd(int a, int b)
{
    int c;
    while (b != 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

int same_prime_divisors(const vector<int> &A, const vector<int> &B)
{
    int counts = 0, a, b, c, d;
    for (auto i = 0; i < A.size(); ++i)
    {
        a = A[i];
        b = B[i];
        d = gcd(a, b);
        while ((c = gcd(a, d)) != 1)
            a /= c;
        while ((c = gcd(b, d)) != 1)
            b /= c;
        if (a == 1 && b == 1)
            ++counts;
    }
    return counts;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Same Prime Divisors", "[codility]")
{
    REQUIRE(same_prime_divisors({15, 10, 3}, {75, 30, 5}) == 1);
}