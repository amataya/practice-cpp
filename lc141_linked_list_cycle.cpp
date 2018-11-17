//  Given a linked list, determine if it has a cycle in it.
// Follow up: Can you solve it without using extra space?
////////////////////////////////////////////////////////////////////////////////
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
struct ListNode {
    int val;
    ListNode *next = nullptr;
    ListNode(int x) : val(x) {}
};

void add_node(ListNode *h, int v)
{
    while (h->next != nullptr)
        h = h->next;
    h->next = new ListNode(v);
}
////////////////////////////////////////////////////////////////////////////////
bool hasCycle(ListNode *head)
{
    if (head == nullptr)
        return false;

    ListNode *walker = head, *runner = head;
    while (runner && runner->next)
    {
        walker = walker->next;
        runner = runner->next->next;
        if (walker == runner)
            return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Linked List Cycle", "[leetcode]")
{
    // Normal linked list
    ListNode *l = new ListNode(10);
    add_node(l, 11);
    add_node(l, 12);
    add_node(l, 13);
    add_node(l, 14);
    add_node(l, 15);
    REQUIRE_FALSE(hasCycle(l));

    // Create a cycle
    ListNode *t = l;
    while (t->next != nullptr)
        t = t->next;
    t->next = l;

    REQUIRE(hasCycle(l));
}