////////////////////////////////////////////////////////////////////////////////
// Scored 91% in this task
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <string>
#include <stack>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<string> splitter(const string &s, const char delimiter = ' ')
{
    const char* str = s.c_str();
    const char* start = nullptr;
    vector<string> tokens;
    do
    {
        for(start = str; *str && *str != delimiter; ++str);
        tokens.emplace_back(string(start, str));
    } while (0 != *str++);
    return tokens;
}

int word_machine(const string &s)
{
    const int ADD_OVERFLOW = 1048575, SUB_UNDERFLOW = 0, ERROR = -1;
    vector<string> operations = splitter(s);
    stack<int> machine;
    int number, op1, op2;
    for (const auto& opcode : operations)
    {
        if (opcode == "+")
        {
            if (machine.size() < 2)
                return ERROR;
            op1 = machine.top(); machine.pop();
            op2 = machine.top(); machine.pop();
            number = op1 + op2;
            if (number > ADD_OVERFLOW)
                return ERROR;
            machine.push(number);
        }
        else if (opcode == "-")
        {
            if (machine.size() < 2)
                return ERROR;
            op1 = machine.top(); machine.pop();
            op2 = machine.top(); machine.pop();
            number = op1 - op2;
            if (number < SUB_UNDERFLOW)
                return ERROR;
            machine.push(number);
        }
        else if (opcode == "DUP")
        {
            if (machine.empty())
                return ERROR;
            number = machine.top();
            machine.push(number);
        }
        else if (opcode == "POP")
        {
            if (machine.empty())
                return ERROR;
            machine.pop();
        }
        else
        {
            if (opcode[0] >= '0' && opcode[0] <= '9')
            {
                number = stoi(opcode);
                machine.push(number);
            }

        }
    }

    if (machine.empty())
        return ERROR;

    return machine.top();
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Word Machine", "[codility]")
{
    REQUIRE(word_machine("13 DUP 4 POP 5 DUP + DUP + -") == 7);
    REQUIRE(word_machine("5 6 + -") == -1);
    REQUIRE(word_machine("3 DUP 5 - -") == -1);
    REQUIRE(word_machine("3 DUP +") == 6);
    REQUIRE(word_machine("524288 DUP +") == -1);
    REQUIRE(word_machine("30 20 -") == -1);
    REQUIRE(word_machine("7 20 + POP") == -1);
}