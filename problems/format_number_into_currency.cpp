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
    stringstream ss;
    bool negative = false;
    int index = 0, insertions = 0;

    if (num < 0)
    {
        negative = true;
        num *= -1;
    }

    while (num > 0)
    {
        if (insertions == comma_positions[index] + index)
        {
            ss << ',';
            ++index;
            ++insertions;
        }
        ss << static_cast<char>(num % 10 + '0'); // To get ASCII code
        num /= 10;
        ++insertions;
    }

    if (negative)
        ss << '-';

    string number = ss.str();
    reverse(number.begin(), number.end());
    return number;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Format number into currency", "[bloomberg]")
{
    REQUIRE(format_number(123123123) == "123,123,123");
    REQUIRE(format_number(104450) == "104,450");
    REQUIRE(format_number(1234) == "1,234");
    REQUIRE(format_number(1) == "1");
    REQUIRE(format_number(-456789) == "-456,789");
}