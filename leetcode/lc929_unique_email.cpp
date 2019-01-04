// Every email consists of a local name and a domain name, separated by the
// @ sign.
//
// For example, in alice@leetcode.com, alice is the local name,
// and leetcode.com is the domain name.
//
// Besides lowercase letters, these emails may contain '.'s or '+'s.
//
// If you add periods ('.') between some characters in the local name part of
// an email address, mail sent there will be forwarded to the same address
// without dots in the local name.  For example, "alice.z@leetcode.com" and
// "alicez@leetcode.com" forward to the same email address.
// (Note that this rule does not apply for domain names.)
//
// If you add a plus ('+') in the local name, everything after the first plus
// sign will be ignored. This allows certain emails to be filtered,
// for example m.y+name@email.com will be forwarded to my@email.com.
// (Again, this rule does not apply for domain names.)
//
// It is possible to use both of these rules at the same time.
//
// Given a list of emails, we send one email to each address in the list.
// How many different addresses actually receive mails?
//
//
//
// Example 1:
//
// Input: ["test.email+alex@leetcode.com","test.e.mail+bob.cathy@leetcode.com",
//          "testemail+david@lee.tcode.com"]
// Output: 2
// Explanation: "testemail@leetcode.com" and "testemail@lee.tcode.com"
//              actually receive mails
// Note:
//     1 <= emails[i].length <= 100
//     1 <= emails.length <= 100
//     Each emails[i] contains exactly one '@' character.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int numUniqueEmails(const vector<string>& emails)
{
    set<string> addresses;
    size_t i = 0, j = 0, limit = 0, domain = 0;
    vector<char> address(100);

    for(const auto& email : emails)
    {
        limit = email.find('+');
        domain = email.find('@');
        limit = (limit == string::npos) ? domain : limit;

        for(i = 0, j = 0; i < limit; ++i)
        {
            if (email[i] == '.')
                continue;
            address[j++] = email[i];
        }

        for(limit = domain; limit < email.size(); ++limit)
            address[j++] = email[limit];

        const auto &target = string(address.begin(), address.begin() + j);
        addresses.insert(target);
    }
    return addresses.size();
}

int numUniqueEmails_v2(const vector<string>& emails)
{
    size_t loc;
    string name, domain;
    set<string> unique;
    for (const auto &e : emails)
    {
        loc = e.find('@');
        name = e.substr(0, loc);
        domain = e.substr(loc, e.size());
        name = e.substr(0, e.find('+'));
        name.erase(remove(name.begin(), name.end(), '.'), name.end());
        unique.insert(name + domain);
    }
    return unique.size();
}

// Apparently this makes the code performant
auto performant = []() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Unique email addresses", "[leetcode]")
{
    REQUIRE(numUniqueEmails({"test.email+alex@leetcode.com",
                             "test.e.mail+bob.cathy@leetcode.com",
                             "testemail+david@lee.tcode.com"}) == 2);
    REQUIRE(numUniqueEmails_v2({"test.email+alex@leetcode.com",
                                 "test.e.mail+bob.cathy@leetcode.com",
                                 "testemail+david@lee.tcode.com"}) == 2);
}