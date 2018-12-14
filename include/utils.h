#ifndef PRACTICE_UTILS_H
#define PRACTICE_UTILS_H

#include <vector>

////////////////////////////////////////////////////////////////////////////////
struct ListNode
{
    int val;
    ListNode *next = nullptr;
    ListNode(int x) : val(x) {}
};

ListNode* create_list(std::vector<int> numbers)
{
    ListNode l(0);
    ListNode* p = &l;
    for (const auto& n : numbers)
    {
        p->next = new ListNode(n);
        p = p->next;
    }
    return l.next;
}

void destroy_list(ListNode *l)
{
    ListNode* t = nullptr;
    while (l != nullptr)
    {
        t = l;
        l = l->next;
        t->next = nullptr;
        delete t;
    }
}

std::vector<int> list_to_vector(ListNode *l)
{
    std::vector<int> result;
    while (l != nullptr)
    {
        result.push_back(l->val);
        l = l->next;
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////

#endif //PRACTICE_UTILS_H
