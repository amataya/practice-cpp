////////////////////////////////////////////////////////////////////////////////
// Say you have an array for which the ith element is the price of a given stock
// on day i. If you were only permitted to complete at most one transaction
// (i.e., buy one and sell one share of the stock), design an algorithm to find
// the maximum profit.
// Note that you cannot sell a stock before you buy one.
//
// Example 1:
// Input: [7,1,5,3,6,4]
// Output: 5
// Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6),
// profit = 6-1 = 5. Not 7-1 = 6, as selling price needs to be larger than
// buying price.
//
// Example 2:
// Input: [7,6,4,3,1]
// Output: 0
// Explanation: In this case, no transaction is done, i.e. max profit = 0.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include <climits>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int maxProfit(vector<int> prices)
{
    if (prices.size() == 0)
        return 0;
    int minP = prices[0];
    int profit = 0;
    for (int i = 1; i < prices.size(); ++i)
    {
        if (minP > prices[i])
            minP = prices[i];
        else
            profit = max(prices[i] - minP, profit);
    }
    return profit;
}

int maxProfit2(vector<int> prices)
{
    int maxCurr = 0, maxSoFar = 0;
    for (int i = 1; i < prices.size(); ++i)
    {
        maxCurr = max(0, maxCurr += prices[i] - prices[i - 1]);
        maxSoFar = max(maxSoFar, maxCurr);
    }
    return maxSoFar;
}

int maxProfit3(vector<int> prices)
{
    int minPrice = INT_MAX, maxProfit = 0;
    for (int i = 0; i < prices.size(); ++i)
    {
        minPrice = min(minPrice, prices[i]);
        maxProfit = max(maxProfit, prices[i] - minPrice);
    }
    return maxProfit;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Best time to buy and sell stocks 1", "[leetcode]")
{
    REQUIRE(maxProfit({7,1,5,3,6,4}) == 5);
    REQUIRE(maxProfit({7,6,4,3,1}) == 0);
}

TEST_CASE("Best time to buy and sell stocks 1 - Kadane", "[leetcode]")
{
    REQUIRE(maxProfit2({7,1,5,3,6,4}) == 5);
    REQUIRE(maxProfit2({7,6,4,3,1}) == 0);
}

TEST_CASE("Best time to buy and sell stocks 1 - Alternate", "[leetcode]")
{
    REQUIRE(maxProfit3({7,1,5,3,6,4}) == 5);
    REQUIRE(maxProfit3({7,6,4,3,1}) == 0);
}

