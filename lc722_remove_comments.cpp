////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <sstream>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<string> removeComments(vector<string> source)
{
    vector<string> result;
    stringstream ss;
    bool block_comment_open = false, skip = false;
    char c;
    int i = 0;
    for (const auto line : source)
    {
        i = 0;
        while (i < line.size())
        {
            c = line[i];
            skip = false;
            if (i + 1 < line.size())
            {
                if (block_comment_open)
                {
                    if (c == '*' && line[i + 1] == '/')
                    {
                        block_comment_open = false;
                        ++i;
                        skip = true;
                    }
                }
                else
                {
                    if (c == '/')
                    {
                        if (line[i + 1] == '/')
                        {
                            i = line.size();
                            skip = true;
                        }
                        else if (line[i + 1] == '*')
                        {
                            block_comment_open = true;
                            skip = true;
                            ++i;
                        }
                    }

                    if (!skip)
                        ss << c;
                }
            }
            else if (!block_comment_open)
                ss << c;
            ++i;
        }
        if (!block_comment_open)
        {
            const auto s = ss.str();
            if (s.size() > 0)
                result.emplace_back(s);
            ss.str("");
        }
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Test Remove Comments", "[leetcode]")
{
    REQUIRE(removeComments({"/*Test program */", "int main()", "{ ", "  // variable declaration ", "int a, b, c;",
                            "/* This is a test", "   multiline  ", "   comment for ", "   testing */",
                            "a = b + c;", "}"}) == vector<string>{"int main()","{ ", "  ",
                                                                  "int a, b, c;","a = b + c;","}"});

    REQUIRE(removeComments({"a/*comment", "line", "more_comment*/b"}) == vector<string>{"ab"});
    REQUIRE(removeComments({"void func(int k) {", "// this function does nothing /*",
                            " k = k*2/4;", " k = k/2;*/", "}"})
                            == vector<string>{"void func(int k) {"," k = k*2/4;"," k = k/2;*/","}"});
}