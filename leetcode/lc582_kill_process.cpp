// Given n processes, each process has a unique PID (process id) and its
// PPID (parent process id).
// Each process only has one parent process, but may have one or more children
// processes. This is just like a tree structure. Only one process has PPID
// that is 0, which means this process has no parent process. All the PIDs will
// be distinct positive integers.
// We use two list of integers to represent a list of processes, where the first
// list contains PID for each process and the second list contains the
// corresponding PPID.
//
// Now given the two lists, and a PID representing a process you want to kill,
// return a list of PIDs of processes that will be killed in the end. You should
// assume that when a process is killed, all its children processes will be
// killed. No order is required for the final answer.
//
// Example 1:
//
// Input:
// pid =  [1, 3, 10, 5]
// ppid = [3, 0, 5, 3]
// kill = 5
// Output: [5,10]
// Explanation:
//            3
//          /   \
//         1     5
//              /
//             10
// Kill 5 will also kill 10.
//
// Note:
//     The given kill id is guaranteed to be one of the given PIDs.
//     n >= 1.
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <unordered_map>
#include <vector>
#include <list>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
vector<int> killProcess(vector<int> pid, vector<int> ppid, int kill)
{
    unordered_map<int, vector<int>> parentChildMap; // list=slow, vector=sup fast!
    for (size_t i = 0; i < pid.size(); ++i)
        parentChildMap[ppid[i]].push_back(pid[i]);

    vector<int> killed;
    list<int> queue;
    queue.push_back(kill);
    int p = 0;
    while (!queue.empty())
    {
        p = queue.front(); queue.pop_front();
        killed.push_back(p);
        for (const int n : parentChildMap[p])
            queue.push_back(n);
    }
    return killed;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Kill Process", "[leetcode]")
{
    REQUIRE( killProcess({1, 3, 10, 5}, {3, 0, 5, 3}, 5)== vector<int>{5, 10});
}