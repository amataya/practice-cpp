//
// Write a function:
//
// int solution(int A, int B, int K);
//
// that, given three integers A, B and K, returns the number of integers
// within the range [A..B] that are divisible by K, i.e.:
//
// { i : A ≤ i ≤ B, i mod K = 0 }
//7
// For example, for A = 6, B = 11 and K = 2, your function should return 3,
// because there are three numbers divisible by 2 within the range [6..11],
// namely 6, 8 and 10.
//
// Write an efficient algorithm for the following assumptions:
//
// A and B are integers within the range [0..2,000,000,000];
// K is an integer within the range [1..2,000,000,000];
// A ≤ B.
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Two factors determine the answer:
//  - the size of the interval [A,B]
//  - whether or not K divides A affects the answer.
// First one is obvious, so let's try to understand the second one.
// Take K=10 as example. If A=20 and B=30 then the answer is 2. If A=21 and B=31
// then the answer is 1 despite the fact that the difference A-B is same.
// So if A is divisible by K then the answer will be 1 greater.
//
// Let rem = A % K (i.e. A = rem (mod K)), i.e. a = 0 if A is multiple of K
// Then we can say: A = rem + mK for some integer m. Here mK is the largest
// multiple of K that is less than or equal to A.
// The number of multiples of K in [A, B] is same as [mK, B] if A is multiple
// of K (rem == 0) and one less if rem > 0.
// Multiple of 3 (K) between 3 (A) and 30 (B) = floor((30 - 3) / 3) + 1;
// Now, the number of multiples of K in [mK, B] is equal to the number of
// multiples of K in the interval [0, B-mK], which is floor((B- mK)/K) + 1
// (the plus one is there because 0 is a multiple)
int count_divisibles(int A, int B, int K)
{
    // A - A % K = rem + mK - rem = mK;
    const int rem = A % K;
    const int mK = A - rem;
    if (rem == 0)
        return floor((B - A) / K) + 1;
    else
        return floor((B - mK) / K);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("count_divisibles", "[codility]")
{
    REQUIRE(count_divisibles(6, 11, 2) == 3);
}