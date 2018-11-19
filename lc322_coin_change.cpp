// You are given coins of different denominations and a total amount of money
// amount. Write a function to compute the fewest number of coins that you need
// to make up that amount. If that amount of money cannot be made up by any
// combination of the coins, return -1.
//
// Example 1:
// Input: coins = [1, 2, 5], amount = 11
// Output: 3
// Explanation: 11 = 5 + 5 + 1
//
// Example 2:
// Input: coins = [2], amount = 3
// Output: -1
//
// Note:
// You may assume that you have an infinite number of each kind of coin.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <climits>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
int count(int amount, vector<int>& coins, int coinIndex)
{
    // If amount is less than 0 then no solution exists
    if (amount < 0)
        return 0;

    // If amount is 0 then there is 1 solution (do not include any coin)
    if (amount == 0)
        return 1;

    // If we have exceeded the available coins and amount is still left
    // then no solution exists
    if (coinIndex >= coins.size() && amount > 0)
        return 0;

    // Count with the current coin and without the current coin
    return count(amount - coins[coinIndex], coins, coinIndex) +
           count(amount, coins, coinIndex + 1);

}

int countWays(vector<int> coins, int amount)
{
    return count(amount, coins, 0);
}

// If the current amount could be satisfied by current coin, then we
// need only a single coin. This is reflected by
// curAmt - coins[curCoinId] will be 0 and so we add 1 to get 1 coin
// However it may be the case that before we came to this coin, we
// might have tried satisfying this amount with a different coin, in
// which case this slot would have a value. If this is the first coin,
// then this slot would have a maximum value.

// This is a bottom-up approach
// Let's define a table to keep track of min number of coins required for
// each additional unit of amount. table[i] will be storing the minimum
// number of coins required for i value. So table[amount] will have
// Initially we don't know the minimum number so set it to Maximum value.
// The if loops says if the amount is equal to the current coin then add 1 coin;
// however if it is greater find the solution of previous value and add 1 to it
// but only if solution exists
int coinChange(vector<int> coins, int amount)
{
    if (amount < 1) // Zero or negative amount - zero solution
        return 0;
    if (coins.size() == 0) // No coins, no solution
        return -1;

    vector<int> table(amount + 1, INT_MAX);
    table[0] = 0; // Base case. For 0 amount we require 0 coins.
    for (int curAmt = 1; curAmt <= amount; ++curAmt)
        for(const auto& coin : coins)
            if (curAmt - coin >= 0 && table[curAmt - coin] != INT_MAX)
                table[curAmt] = min(table[curAmt], table[curAmt - coin] + 1);
    return table[amount] == INT_MAX ? - 1 : table[amount];
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Coin change", "[leetcode]")
{
    REQUIRE(countWays({1, 2, 3}, 5) == 5);
    REQUIRE(coinChange({1, 2, 5}, 11) == 3);
    REQUIRE(coinChange({2}, 3) == -1);
    REQUIRE(coinChange({25, 10, 5}, 30) == 2);
    REQUIRE(coinChange({9, 6, 5, 1}, 11) == 2);
}