// You are given two non-empty linked lists representing two non-negative
// integers. The digits are stored in reverse order and each of their nodes
// contain a single digit. Add the two numbers and return it as a linked list.
//
// You may assume the two numbers do not contain any leading zero, except the
// number 0 itself.
//
// Example:
//
// Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
// Output: 7 -> 0 -> 8
// Explanation: 342 + 465 = 807.
//
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.h"
#include <vector>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode answer(0);
    ListNode *l3 = &answer;
    int carry = 0, sum = 0;
    while (l1 || l2)
    {
        sum = carry;
        if (l1)
        {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2)
        {
            sum += l2->val;
            l2 = l2->next;
        }

        l3->next = new ListNode(sum % 10);
        l3 = l3->next;
        carry = sum / 10;

    }
    if (carry > 0)
        l3->next = new ListNode(carry);

    return answer.next;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Add Two Numbers 1", "[leetcode]")
{
    ListNode* l1 = create_list({2, 4, 3});
    ListNode* l2 = create_list({5, 6, 4});
    ListNode* l3 = addTwoNumbers(l1, l2);
    REQUIRE(list_to_vector(l3) == vector<int>{7, 0, 8});
    destroy_list(l1);
    destroy_list(l2);
    destroy_list(l3);
}

TEST_CASE("Add Two Numbers - 2", "[leetcode]")
{
    ListNode* l1 = create_list({5});
    ListNode* l2 = create_list({5});
    ListNode* l3 = addTwoNumbers(l1, l2);
    REQUIRE(list_to_vector(l3) == vector<int>{0, 1});
    destroy_list(l1);
    destroy_list(l2);
    destroy_list(l3);
}

TEST_CASE("Add Two Numbers - 3", "[leetcode]")
{
    ListNode* l1 = create_list({1, 8});
    ListNode* l2 = create_list({0});
    ListNode* l3 = addTwoNumbers(l1, l2);
    REQUIRE(list_to_vector(l3) == vector<int>{1, 8});
    destroy_list(l1);
    destroy_list(l2);
    destroy_list(l3);
}

TEST_CASE("Add Two Numbers - 4", "[leetcode]")
{
    ListNode* l1 = create_list({9, 8});
    ListNode* l2 = create_list({1});
    ListNode* l3 = addTwoNumbers(l1, l2);
    REQUIRE(list_to_vector(l3) == vector<int>{0, 9});
    destroy_list(l1);
    destroy_list(l2);
    destroy_list(l3);
}