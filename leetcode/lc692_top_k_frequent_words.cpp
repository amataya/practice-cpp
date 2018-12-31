// Given a non-empty list of words, return the k most frequent elements.
//
// Your answer should be sorted by frequency from highest to lowest. If two
// words have the same frequency, then the word with the lower alphabetical
// order comes first.
//
// Example 1:
// Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
// Output: ["i", "love"]
// Explanation: "i" and "love" are the two most frequent words.
//     Note that "i" comes before "love" due to a lower alphabetical order.
//
// Example 2:
// Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny",
//         "is", "is"], k = 4
// Output: ["the", "is", "sunny", "day"]
// Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
//     with the number of occurrence being 4, 3, 2 and 1 respectively.
//
// Note:
//     You may assume k is always valid, 1 ≤ k ≤ number of unique elements.
//     Input words contain only lowercase letters.
//
// Follow up:
//     Try to solve it in O(n log k) time and O(n) extra space.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <utility>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<string> topKFrequent(vector<string> words, int k)
{
    unordered_map<string, int> wordFreq;
    for (const auto& w : words)
        wordFreq[w]++;

    auto comparator = [](const pair<string, int>& p1, const pair<string, int>& p2)
    {
        return (p1.second > p2.second) ||
               (p1.second == p2.second && p1.first < p2.first);
    };
    using pq_t = priority_queue<pair<string, int>,
        vector<pair<string, int>>,
        decltype(comparator)>;
    pq_t ordering(comparator);

    for (const auto& e : wordFreq)
    {
        ordering.emplace(e);
        if (ordering.size() > k)
            ordering.pop();
    }

    vector<string> result;
    while(!ordering.empty())
    {
        result.emplace_back(ordering.top().first);
        ordering.pop();
    }
    reverse(result.begin(), result.end());
    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Top K Frequent Words", "[leetcode]")
{
    REQUIRE(topKFrequent(vector<string>{"i", "love", "leetcode", "i",
                                        "love", "coding"}, 2) ==
                                        vector<string>{"i", "love"});

    REQUIRE(topKFrequent(vector<string>{"the", "day", "is", "sunny", "the",
                          "the", "the", "sunny", "is", "is"}, 4) ==
                          vector<string>{"the", "is", "sunny", "day"});
}