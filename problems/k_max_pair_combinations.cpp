// Given two arrays A & B of size N each.
// Find the maximum N elements from the sum combinations (Ai + Bj) formed from
// elements in array A and B.
//
// For example if A = [1,2], B = [3,4],  k = 2 then possible pair sums can be
// 1+3=4, 1+4=5, 2+3=5, 2+4=6
// and maximum 2 elements are 6, 5
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <set>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Instead of brute forcing through all the possible sum combinations we could
// find a way to limit our search space to possible candidate sum combinations.
// 1. Sort both arrays array A and array B.
// 2. Create a max heap i.e priority_queue in C++ to store the sum combinations
//    along with the indices of elements from both arrays A and B which make up
//    the sum. Heap is ordered by the sum.
// 3. Initialize the heap with the maximum possible sum combination i.e
//    (A[N – 1] + B[N – 1] where N is the size of array) and with the indices of
//    elements from both arrays (N – 1, N – 1). The tuple inside max heap will
//    be (A[N-1] + B[N – 1], N – 1, N – 1). Heap is ordered by first value
//    i.e sum of both elements.
// 4. Pop the heap to get the current largest sum and along with the indices of
//    the element that make up the sum. Let the tuple be (sum, i, j).
//   (i) Next insert (A[i – 1] + B[j], i – 1, j) and (A[i] + B[j – 1], i, j – 1)
//    into the max heap but make sure that the pair of indices
//    i.e (i – 1, j) and (i, j – 1) are not already present in the max heap.
//    To check this we can use set in C++.
//   (ii) Go back to 4 until K times.

vector<int> k_max_pair_combinations(vector<int> a, vector<int> b, const int k)
{
    vector<int> result(k);
    int i = 0, j = 0, sum = 0;
    pair<int, int> p;
    const int n = a.size();

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    // Max heap to get the highest sum. Element format: (sum, <idx-a, idx-b>)
    priority_queue<pair<int, pair<int, int>>> pq;

    // To ensure unique indices are being inserted into the queue
    set<pair<int, int>> indices;

    i = j = n - 1;
    p = make_pair(i, j);
    sum = a[i] + b[j];

    pq.push(make_pair(sum, p));
    indices.insert(p);

    for (int c = 0; c < k; ++c)
    {
        const auto& element = pq.top(); pq.pop();
        result[c] = element.first;
        i = element.second.first;
        j = element.second.second;

        p = make_pair(i - 1, j);
        if (indices.find(p) == indices.end())
        {
            sum = a[i - 1] + b[j];
            pq.push(make_pair(sum, p));
            indices.insert(p);
        }

        p = make_pair(i, j - 1);
        if (indices.find(p) == indices.end())
        {
            sum = a[i] + b[j - 1];
            pq.push(make_pair(sum, p));
            indices.insert(p);
        }
    }

    return result;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("k-max-pair-combo", "[problems]")
{
    REQUIRE(k_max_pair_combinations({1, 2}, {3, 4}, 2) == vector<int>{6, 5});
}