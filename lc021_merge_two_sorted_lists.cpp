////////////////////////////////////////////////////////////////////////////////
// Merge two sorted linked lists and return it as a new list.
// The new list should be made by splicing together the nodes of the first
// two lists.
//
// Example:
// Input: 1->2->4, 1->3->4
// Output: 1->1->2->3->4->4
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "utils.h"
#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    ListNode lst(0);
    ListNode* l3 = &lst;
    ListNode** t = nullptr;

    while (l1 && l2)
    {
        t = (l1->val <= l2->val) ? &l1 : &l2;
        l3->next = new ListNode((*t)->val);
        *t = (*t)->next;
        l3 = l3->next;
    }
    while (l1 != nullptr)
    {
        l3->next = new ListNode(l1->val);
        l1 = l1->next;
        l3 = l3->next;
    }
    while (l2 != nullptr)
    {
        l3->next = new ListNode(l2->val);
        l2 = l2->next;
        l3 = l3->next;
    }
    return lst.next;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Merge two sorted lists", "[leetcode]")
{
    ListNode *l1 = create_list({1, 2, 4});
    ListNode *l2 = create_list({1, 3, 4});
    ListNode *l3 = mergeTwoLists(l1, l2);
    REQUIRE(list_to_vector(l3) == vector<int>{1, 1, 2, 3, 4, 4});
    destroy_list(l1);
    destroy_list(l2);
    destroy_list(l3);

    ListNode *l4 = create_list({1, 2, 7, 8, 9, 10});
    ListNode *l5 = create_list({1, 3, 4});
    ListNode *l6 = mergeTwoLists(l4, l5);
    REQUIRE(list_to_vector(l6) == vector<int>{1, 1, 2, 3, 4, 7, 8, 9, 10});
    destroy_list(l4);
    destroy_list(l5);
    destroy_list(l6);
}
