////////////////////////////////////////////////////////////////////////////////
// Count the number of prime numbers less than a non-negative number, n.
//
// Example:
// Input: 10
// Output: 4
// Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int countPrimes(int n)
{
    if (n < 2)
        return 0;

    vector<bool> primes(n, true);
    primes[0] = false, primes[1] = false;
    const int upperBound = static_cast<int>(sqrt(n));

    int i = 0, j = 0;
    for(i = 2; i <= upperBound; ++i)
    {
        if (primes[i])
            for (j = i * i; j < n; j += i)
                primes[j] = false;
    }
    int count = 0;
    for (const auto e: primes)
        if (e)
            ++count;
    return count;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Count Primes", "[leetcode]")
{
    REQUIRE(countPrimes(10) == 4);
}