/* 
Reverse alternating K-element Sub-list (medium) #
Given the head of a LinkedList and a number ‘k’, reverse every alternating ‘k’ 
sized sub-list starting from the head.
If, in the end, you are left with a sub-list with less than ‘k’ elements, reverse it too. 
*/
#include <iostream>
#include <string>
using namespace std;

class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class ReverseAlternatingKSubList
{
public:
    ListNode *reverse(ListNode *head, int k)
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;

        while (curr != nullptr)
        {
            ListNode *prevsublisttail = prev; // Store the prev tail node of previous sublist in prevsublisttail
            ListNode *currsublisttail = curr; // Store the current pointer which will be tail after reversal in currsublisttail

            for (auto i = 0; curr && (i < k); ++i)
            {
                ListNode *next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            // Connect the tail of the previous sublist to the
            // head of the new reversed list.
            if (prevsublisttail != nullptr)
            {
                prevsublisttail->next = prev;
            }
            else
            {
                // if prevtail was null that means attach head to prev
                // which is now head of the reversed list
                head = prev;
            }

            // Connect the current sublist to next sublist head
            currsublisttail->next = curr;

            // point the prev to currsublisttail of the current sublist
            prev = currsublisttail;

            // Skip K noof nodes

            for (auto i = 0; curr && (i < k); ++i)
            {
                prev = curr;
                curr = curr->next;
            }
        }
        return head;
    }

    string listNodeToString(ListNode *node)
    {
        if (node == nullptr)
        {
            return "[]";
        }

        string result;
        while (node)
        {
            result += to_string(node->val) + "->";
            node = node->next;
        }
        return "[" + result.substr(0, result.length() - 2) + "]";
    }
};

int main()
{
    ListNode *head = new ListNode(1);
    ListNode *curr = head;

    ReverseAlternatingKSubList listAlternatingKReverse;

    for (auto i = 2; i < 11; ++i)
    {
        curr->next = new ListNode(i);
        curr = curr->next;
    }

    cout << listAlternatingKReverse.listNodeToString(head) << endl;

    head = listAlternatingKReverse.reverse(head, 4);

    cout << listAlternatingKReverse.listNodeToString(head) << endl;

    return 0;
}
