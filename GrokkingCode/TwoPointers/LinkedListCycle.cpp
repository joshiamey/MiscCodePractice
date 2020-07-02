/* Given the head of a Singly LinkedList that contains a cycle, 
write a function to find the starting node of the cycle. */

#include "ListNode.h"
class LinkedListCycle
{
private:
    /* data */
public:
    static bool hasCycle(ListNode *head, ListNode *&cycleHead)
    {
        ListNode *slow = head;
        ListNode *fast = head;
        bool hasCycle = false;

        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;

            if (slow == fast)
            {
                //found the cycle
                hasCycle = true;
                break;
            }
        }

        if (hasCycle)
        {
            // Calculate cycle length
            auto cyclelen = 0;
            auto curr = slow;

            do
            {
                curr = curr->next;
                ++cyclelen;
            } while (curr != slow);

            // Iterate ptr2 ahead by cyclelen nodes
            auto ptr1 = head;
            auto ptr2 = head;

            while (cyclelen > 0)
            {
                ptr2 = ptr2->next;
                --cyclelen;
            }

            // Iterate ptr1 and ptr2 until they meet
            while (ptr1 != ptr2)
            {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }

            cycleHead = ptr1;
        }

        return hasCycle;
    }
};

int main()
{
    ListNode *head = new ListNode(1);
    ListNode *curr = head;
    ListNode *tmp = nullptr;
    ListNode *cycle = nullptr;

    for (auto i = 2; i < 7; ++i)
    {
        curr->next = new ListNode(i);
        curr = curr->next;
        if (i == 4)
        {
            tmp = curr;
        }
    }

    curr->next = tmp;

    if (LinkedListCycle::hasCycle(head, cycle))
    {
        std::cout << "Cycle present in the linked list: " << std::endl;
        curr = cycle;
        do
        {
            std::cout << curr->val << "->";
            curr = curr->next;
        } while (curr != cycle);

        std::cout << cycle->val << std::endl;
    }
    else
    {
        std::cout << "Linked List does not have a cycle" << std::endl;
    }

    return 0;
}