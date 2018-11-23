// Format a number into currency
// Follow up: Support multiple styles
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
string format_number(int num)
{
    const int comma_positions[] = {3, 6, 9, 12, 15};
    string repr;
    int index = 0;
    while (num > 0)
    {
        if (repr.size() == comma_positions[index] + index)
        {
            repr.push_back(',');
            ++index;
        }
        repr.push_back(static_cast<char>(num % 10 + '0')); // To get ASCII code
        num /= 10;
    }
    reverse(repr.begin(), repr.end());
    return repr;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Format number into currency", "[bloomberg]")
{
    REQUIRE(format_number(123123123) == "123,123,123");
    REQUIRE(format_number(104450) == "104,450");
    REQUIRE(format_number(1234) == "1,234");
    REQUIRE(format_number(1) == "1");
}