////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <bitset>

using namespace std;
////////////////////////////////////////////////////////////////////////////////

int max_binary_gap(int N)
{
#if INTPTR_MAX == INT32_MAX
#define INT_SIZE 32
#elif INTPTR_MAX == INT64_MAX
#define INT_SIZE 64
#endif

    bitset<INT_SIZE> input(N);
    int max = 0;
    if (input.count() > 1)
    {
        int prev = -1;
        for (int i = 0; i < input.size(); ++i)
        {
            if (input.test(i))
            {
                if (prev > -1 && (i - prev > 1))
                {
                    if ((i - prev) > max)
                        max = i - prev - 1;
                }
                prev = i;
            }
        }
    }
    return max;
}

////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Test Max Binary Gap", "[classic]")
{
    REQUIRE(max_binary_gap(1041) == 5);
    REQUIRE(max_binary_gap(32) == 0);
    REQUIRE(max_binary_gap(15) == 0);
}