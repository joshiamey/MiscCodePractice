/* 
* Reverse a given linked list
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

class ReverseList
{
public:
    ListNode *reverse(ListNode *head)
    {
        ListNode *prev = nullptr;
        ListNode *curr = head;
        ListNode *next = nullptr;

        while (curr != nullptr)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        // Once the loop exits , prev pointer will
        // point towards the last element in the list
        // which will be the new head

        head = prev;

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

    ReverseList reverseList;

    for (auto i = 2; i < 11; ++i)
    {
        curr->next = new ListNode(i);
        curr = curr->next;
    }

    cout << reverseList.listNodeToString(head) << endl;

    head = reverseList.reverse(head);

    cout << reverseList.listNodeToString(head) << endl;

    return 0;
}