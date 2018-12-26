// There are N chocolates in a circle. Count the number of chocolates
// you will eat.
//
// Two positive integers N and M are given. Integer N represents the number of
// chocolates arranged in a circle, numbered from 0 to N − 1.
//
// You start to eat the chocolates. After eating a chocolate you leave only a
// wrapper.
//
// You begin with eating chocolate number 0. Then you omit the next M − 1
// chocolates or wrappers on the circle, and eat the following one.
//
// More precisely, if you ate chocolate number X, then you will next eat the
// chocolate with number (X + M) modulo N (remainder of division).
//
// You stop eating when you encounter an empty wrapper.
//
// For example, given integers N = 10 and M = 4. You will eat the following
// chocolates: 0, 4, 8, 2, 6.
//
// The goal is to count the number of chocolates that you will eat, following
// the above rules.
//
// Write a function:
//
// int solution(int N, int M);
//
// that, given two positive integers N and M, returns the number of chocolates
// that you will eat.
//
// For example, given integers N = 10 and M = 4. the function should return 5,
// as explained above.
//
// Write an efficient algorithm for the following assumptions:
//
// N and M are integers within the range [1..1,000,000,000].
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int num_consumed_v0(int N, int M)
{
    vector<bool> eaten(N);
    int ate = 0, i = 0;
    while (!eaten[i])
    {
        eaten[i] = true;
        i = (i + M) % N; // According to description
        ++ate;
    }
    return ate;
}

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

// N and M meet at their LCM. Dividing this LCM by M gets the number of
// steps(chocolates) that can be eaten.
// The least common multiple (lcm) of two integers a and b is the smallest
// positive integer that is divisible by both a and b
// LCM(a, b) = (a x b) / gcd(a, b)
// Note the order of braces and use of long. With very large numbers, the
// original formula overflows C++ data types. On the other hand in Python
// int expand to available memory.
int num_consumed(int N, int M)
{
    const auto lcm = N * (M / gcd(N, M));
    return (lcm / M);
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("How many chocolates", "[codility]")
{
    REQUIRE(num_consumed(10, 4) == 5);
}