/*
*Given the head of a LinkedList and a number ‘k’, 
* reverse every ‘k’ sized sub-list starting from the head.
* If, in the end, you are left with a sub-list with less than ‘k’ elements, reverse it too.
*  head->1->2->3->4->5->null
*           K=2
*  head->2->1->4->3->5->null
*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class ReverseKSubList
{
public:
    ListNode *reverseKSubList(ListNode *head, int k)
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;

        while (curr != nullptr)
        {
            ListNode *prevtail = prev; // Store the prev tail node of previous sublist in prevtail
            ListNode *currtail = curr; // Store the current pointer which will be tail after reversal in currtail

            for (auto i = 0; curr && (i < k); ++i)
            {
                ListNode *next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
            }

            // Connect the tail of the previous sublist to the
            // head of the new reversed list.
            if (prevtail != nullptr)
            {
                prevtail->next = prev;
            }
            else
            {
                // if prevtail was null that means attach head to prev
                // which is now head of the reversed list
                head = prev;
            }

            // Connect the current sublist to next sublist head
            currtail->next = curr;

            // point the prev to currtail of the current sublist
            prev = currtail;
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

    ReverseKSubList listKReverse;

    for (auto i = 2; i < 9; ++i)
    {
        curr->next = new ListNode(i);
        curr = curr->next;
    }

    cout << listKReverse.listNodeToString(head) << endl;

    head = listKReverse.reverseKSubList(head, 3);

    cout << listKReverse.listNodeToString(head) << endl;

    return 0;
}