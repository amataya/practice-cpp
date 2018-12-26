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
long gcd(long a, long b)
{
    long c;
    while (b != 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

// Remove all prime divisors of x, which also exist in y and return the
// remaining part of x.
int remove_prime_divisors(int a, int b)
{
    long val;
    while (a != 1)
    {
        val = gcd(a, b);
        if (val == 1) // there are no more common divisors
            break;
        a /= val;
    }
    return a;
}

bool have_same_prime_divisors(int x, int y)
{
    const auto val = gcd(x, y);
    x = remove_prime_divisors(x, val);
    if (x != 1)
        return false;
    y = remove_prime_divisors(y, val);
    return y == 1;
}

int same_prime_divisors(const vector<int> &A, const vector<int> &B)
{
    int counts = 0;
    for (auto i = 0; i < A.size(); ++i)
        if (have_same_prime_divisors(A[i], B[i]))
            ++counts;
    return counts;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Same Prime Divisors", "[codility]")
{
    REQUIRE(same_prime_divisors({5, 10, 3}, {75, 30, 5}) == 1);
}