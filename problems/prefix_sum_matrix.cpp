/*
 * We have a n x m matrix 'a'. Derive a nxm matrix 'b' such that for a 3x3 the
 * following relation holds
 *
 * b(0, 0) = a(0, 0)
 * b(0, 1) = a(0, 0) + a(0, 1)
 * b(0, 2) = a(0, 0) + a(0, 1) + a(0, 2)
 * b(1, 0) = a(0, 0) + a(1, 0)
 * b(1, 1) = a(0, 0) + a(0, 1) + a(1, 0) + a(1, 1)
 * b(1, 2) = a(0, 0) + a(0, 1) + a(0, 2) + a(1, 0) + a(1, 1) + a(1, 2)
 * b(2, 0) = a(0, 0) + a(1, 0) + a(2, 0)
 * b(2, 1) = a(0, 0) + a(0, 1) + a(1, 0) + a(1, 1) + a(2, 0) + a(2, 1)
 * b(2, 2) = a(0, 0) + a(0, 1) + a(0, 2) + a(1, 0) + a(1, 1) + a(1, 2) + a(2, 0)
 *
 * === a ===                 ====== b =======
 *      [0]  [1]  [2]            [0]  [1]  [2]
 * [0]  10   20   30        [0]  10   30   60
 * [1]  5    10   20        [1]  15   45   95
 * [2]  2    4    6         [2]  17   51   107
 *
 * --------------------------------------------
 * A simple solution is to find b[i][j] by traversing and adding values from
 * a[0][0] to a[i][j]. Time complexity of this solution is O(R * C * R * C).
 * An efficient solution is to use previously computed values to compute b[i][j].
 * b[2][2] = b[1][2] + b[2][1] -
 *           b[1][1] + a[2][2]
 *         = 95 + 51 - 45 + 6
 *         = 107
 * This gives the general formula:
 * b[i][j] = b[i-1][j] + b[i][j-1] - b[i-1][j-1] + a[i][j]
 *
 * Corner Cases (First row and first column)
 * If i = 0 and j = 0
 * b[i][j] = a[i][j]
 * If i = 0 and j > 0
 * b[i][j] = b[i][j-1] + a[i][j]
 * If i > 0 and j = 0
 * b[i][j] = b[i-1][j] + a[i][j]
 *
 * This problem is also known as prefix sum 2D.
 */

#define CATCH_CONFIG_MAIN

#include <vector>
#include "catch.hpp"

using namespace std;

vector<vector<int>> prefix_sum_matrix(const vector<vector<int>>& a)
{
    const size_t rows = a.size();
    const size_t cols = a[0].size();

    vector<vector<int>> b(rows, vector<int>(cols));
    int i, j;

    // Address corner cases
    b[0][0] = a[0][0];
    for (i = 1; i < cols; ++i)
        b[0][i] = b[0][i - 1] + a[0][i];
    for (j = 1; j < rows; ++j)
        b[j][0] = b[j - 1][0] + a[j][0];

    // Now fill rows and cols as per the derived formula
    for (i = 1; i < rows; ++i)
        for (j = 1; j < cols; ++j)
            b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + a[i][j];

    return b;
}

////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Prefix Sum 2D - TC1", "[GeeksforGeeks]")
{
    const vector<vector<int>> a = {
        {10, 20, 30},
        {5, 10, 20},
        {2, 4, 6}
    };
    const vector<vector<int>> expected = {
        {10, 30, 60},
        {15, 45, 95},
        {17, 51, 107}
    };
    REQUIRE(prefix_sum_matrix(a) == expected);
}

TEST_CASE("Prefix Sum 2D - TC2", "[GeeksforGeeks]")
{
    const vector<vector<int>> a = {
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1}};
    const vector<vector<int>> expected = {
        {1, 2, 3, 4, 5},
        {2, 4, 6, 8, 10},
        {3, 6, 9, 12, 15},
        {4, 8, 12, 16, 20}
    };
    REQUIRE(prefix_sum_matrix(a) == expected);
}