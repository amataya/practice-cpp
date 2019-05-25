// Merge k sorted linked lists and return it as one sorted list. Analyze and
// describe its complexity.
//
// Example:
// Input:
// [
//   1->4->5,
//   1->3->4,
//   2->6
// ]
// Output: 1->1->2->3->4->4->5->6
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.h"
#include <vector>
#include <queue>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
ListNode* merge_k_lists(vector<ListNode*>& lists)
{
    if (lists.empty())
        return nullptr;

    if (lists.size() == 1)
        return lists[0];

    static const auto cmp = [](const ListNode *a, const ListNode *b) {
        return (a->val > b->val);
    };

    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

    for (const auto& l : lists)
        if (l)
            pq.push(l);

    ListNode lst(0);
    ListNode *top = nullptr, *node = &lst;

    while (!pq.empty())
    {
        top = pq.top(); pq.pop();
        if (top->next != nullptr)
        {
            pq.push(top->next);
            top->next = nullptr;
        }

        node->next = top;
        node = node->next;
    }
    return lst.next;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Merge-k-sorted-lists-1", "[leetcode]")
{
    ListNode *l1 = create_list({1, 4, 5});
    ListNode *l2 = create_list({1, 3, 4});
    ListNode *l3 = create_list({2, 6});
    vector<ListNode*> lists = {l1, l2, l3};
    ListNode *result = merge_k_lists(lists);
    REQUIRE(list_to_vector(result) == vector<int>{1, 1, 2, 3, 4, 4, 5, 6});
    destroy_list(result);
}

TEST_CASE("Merge-k-sorted-lists-2", "[leetcode]")
{
    vector<ListNode*> lists;
    ListNode *result = merge_k_lists(lists);
    REQUIRE(result == nullptr);
}

TEST_CASE("Merge-k-sorted-lists-3", "[leetcode]")
{
    ListNode *l1 = create_list({1, 4, 5});
    vector<ListNode*> lists = {l1};
    ListNode *result = merge_k_lists(lists);
    REQUIRE(result == l1);
    REQUIRE(list_to_vector(result) == vector<int>{1, 4, 5});
    destroy_list(result);
}

TEST_CASE("Merge-k-sorted-lists-4", "[leetcode]")
{
    vector<ListNode*> lists = {nullptr, nullptr};
    ListNode *result = merge_k_lists(lists);
    REQUIRE(result == nullptr);
}
