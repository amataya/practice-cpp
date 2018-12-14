#define CATCH_CONFIG_MAIN
#include "catch.hpp"


#include <string>
#include <cctype>

using namespace std;

bool is_similar(const string S, const string T)
{
    size_t n = 0, m = 0;
    while(n < S.size() && m < T.size())
    {
        while (isalpha(T[m]) && T[m] == S[n])
        {
            m++;
            n++;
            continue;
        }

        // Given we are here, we have a digit. Get the full number
        int num = 0;
        while (isdigit(T[m]))
        {
            num = (num * 10) + (T[m] - '0');
            m++;
        }
        cout << num  << "\n";
        m++;
        n++;
    }
    return true;
}

TEST_CASE("OCR", "[classic]")
{
    CHECK(is_similar("A2Le", "2pL1"));
}