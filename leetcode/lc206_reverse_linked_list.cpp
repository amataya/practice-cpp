////////////////////////////////////////////////////////////////////////////////
// Reverse a singly linked list.
// Example:
// Input: 1->2->3->4->5->NULL
// Output: 5->4->3->2->1->NULL
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "linked_list.h"
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
ListNode* reverseList(ListNode* head)
{
    ListNode reverse(0);
    ListNode* t = nullptr;
    while (head != nullptr)
    {
        t = head;
        head = head->next;
        t->next = reverse.next;
        reverse.next = t;
    }
    return reverse.next;
}

////////////////////////////////////////////////////////////////////////////////


TEST_CASE("Reverse Linked List", "[leetcode]")
{
    ListNode *l = new ListNode(1);
    l->next = new ListNode(2);
    l->next->next = new ListNode(3);
    l->next->next->next = new ListNode(4);
    l->next->next->next->next = new ListNode(5);

    ListNode* r = reverseList(l);
    REQUIRE(list_to_vector(r) == vector<int>{5, 4, 3, 2, 1});
}
