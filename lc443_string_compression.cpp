////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <string>

using namespace std;
////////////////////////////////////////////////////////////////////////////////

int compress(vector<char> chars)
{
    if (chars.size() < 2)
        return chars.size();

   int count = 0, w = 0, r = 0;
   char current;
   while (r < chars.size())
   {
       count = 0;
       current = chars[r];
       while(r < chars.size() && chars[r] == current)
       {
           ++r;
           ++count;
       }
       chars[w++] = current;
       if (count == 1)
           continue;
       for (char c : to_string(count))
            chars[w++] = c;
   }
   return w;
}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Test String Compression", "[leetcode]")
{
    REQUIRE(compress({'a','b','b','b','b','b','b','b','b','b','b','b','b'})  == 4);
    REQUIRE(compress({'a'})  == 1);
    REQUIRE(compress({'a','a','b','b','c','c','c'}) == 6);
    REQUIRE(compress({'a','a','a','b','b','a','a'}) == 6);
    REQUIRE(compress({'a','b','c'}) == 3);
}
